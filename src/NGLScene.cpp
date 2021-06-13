#include <QMouseEvent>
#include <QGuiApplication>
#include <QTime>

#include <ngl/Transformation.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>

#include "NGLScene.h"

NGLScene::NGLScene(QWidget *_parent) : QOpenGLWidget(_parent)
{
  setFocusPolicy(Qt::ClickFocus);   // Wherever the user clicks, give keyboard focus to
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  this->resize(_parent->size());
}

NGLScene::~NGLScene()
{
  std::cout << "Shutting down NGL, removing VAO's and Shaders\n";
}

void NGLScene::resizeGL(int _w, int _h)
{
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}

void NGLScene::initializeGL()
{
  ngl::NGLInit::initialize();
  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);		// Grey Background
  glEnable(GL_DEPTH_TEST);                // Enable depth testing for drawing
  glEnable(GL_MULTISAMPLE);               // Enable multisampling for smoother drawing
  // we are creating a shader called RayMarch
  ngl::ShaderLib::createShaderProgram("RayMarch");
  // now we are going to create empty shaders for Frag and Vert
  ngl::ShaderLib::attachShader("RayMarchVertex", ngl::ShaderType::VERTEX);
  ngl::ShaderLib::attachShader("RayMarchFragment", ngl::ShaderType::FRAGMENT);
  // attach the source
  ngl::ShaderLib::loadShaderSource("RayMarchVertex", "shaders/RayMarchVertex.glsl");
  ngl::ShaderLib::loadShaderSource("RayMarchFragment", "shaders/RayMarchFragment.glsl");
  // compile the shaders
  ngl::ShaderLib::compileShader("RayMarchVertex");
  ngl::ShaderLib::compileShader("RayMarchFragment");
  // add them to the program
  ngl::ShaderLib::attachShaderToProgram("RayMarch", "RayMarchVertex");
  ngl::ShaderLib::attachShaderToProgram("RayMarch", "RayMarchFragment");
  ngl::ShaderLib::linkProgramObject("RayMarch");
  ngl::ShaderLib::use("RayMarch");
  ngl::ShaderLib::setUniform("mouse", ngl::Vec2(23, 23));
  ngl::ShaderLib::setUniform("cam_pos", ngl::Vec3(0.0f, 0.0f, 4.0f));
  ngl::ShaderLib::setUniform("time", 0.0f);

  m_screenQuad.reset(new ScreenQuad("RayMarch"));
  // as re-size is not explicitly called we need to do this.
  glViewport(0, 0, width(), height());
  startTimer(10);
}

void NGLScene::loadMatricesToShader()
{
  ngl::ShaderLib::setUniform("mouse", ngl::Vec2(m_win.spinXFace, m_win.spinYFace));
  ngl::ShaderLib::setUniform("cam_pos", ngl::Vec3(0.0f, 0.0f, 4.0f));
}

void NGLScene::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Clear the screen and depth buffer
  ngl::ShaderLib::use("RayMarch");
  loadMatricesToShader();
  m_screenQuad->draw();
}

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
    // escape key to quite
    case Qt::Key_Escape:
    {
      QGuiApplication::exit(EXIT_SUCCESS);
      break;
    }

    // turn on wirframe rendering
    case Qt::Key_W:
    {
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      break;
    }

    // turn off wire frame
    case Qt::Key_S:
    {
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      break;
    }

    // show full screen
    case Qt::Key_F:
    {
      showFullScreen();
      break;
    }

    // show windowed
    case Qt::Key_N:
    {
      showNormal();
      break;
    }

    default:
    {
      break;
    }
  }
  // finally update the GLWindow and re-draw
  update();
}

void NGLScene::timerEvent(QTimerEvent *_event)
{
  static float t = 0.0f;
  ngl::ShaderLib::use("RayMarch");
  ngl::ShaderLib::setUniform("time", t);
  t += 0.01f;

  if (t > 5.0f)
  {
    t = 0.0f;
  }

  update();
}
