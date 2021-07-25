#include <QMouseEvent>
#include <QGuiApplication>
#include <QTime>

#include <ngl/Transformation.h>
#include <ngl/NGLInit.h>
#include <ngl/VAOPrimitives.h>
#include <ngl/ShaderLib.h>

#include "NGLScene.h"

#include <iostream>
#include <math.h>

NGLScene::NGLScene()
{
  setFocusPolicy(Qt::FocusPolicy::ClickFocus);
}

void NGLScene::buildShaders()
{
  // Create shader programs
  ngl::ShaderLib::createShaderProgram("ShaderProgram_A");
  ngl::ShaderLib::createShaderProgram("ShaderProgram_B");

  // Create empty shaders
  ngl::ShaderLib::attachShader("Vertex", ngl::ShaderType::VERTEX);
  ngl::ShaderLib::attachShader("Fragment_A", ngl::ShaderType::FRAGMENT);
  ngl::ShaderLib::attachShader("Fragment_B", ngl::ShaderType::FRAGMENT);

  // Attach shader code
  ngl::ShaderLib::loadShaderSource("Vertex", "shaders/DefaultVertex.glsl");
  ngl::ShaderLib::loadShaderSource("Fragment_A", "shaders/DefaultFragment.glsl");

  // Compile the shaders
  ngl::ShaderLib::compileShader("Vertex");
  ngl::ShaderLib::compileShader("Fragment_A");

  // Attach shaders to shader program
  ngl::ShaderLib::attachShaderToProgram("ShaderProgram_A", "Vertex");
  ngl::ShaderLib::attachShaderToProgram("ShaderProgram_B", "Vertex");
  ngl::ShaderLib::attachShaderToProgram("ShaderProgram_A", "Fragment_A");

  // Link and use shader program A (B is not complete)
  ngl::ShaderLib::linkProgramObject("ShaderProgram_A");
  ngl::ShaderLib::use("ShaderProgram_A");

  resetUniforms();
}

void NGLScene::initializeGL()
{
  ngl::NGLInit::initialize();
  glClearColor(0.4f, 0.4f, 0.4f, 1.0f);		// Grey Background
  glEnable(GL_DEPTH_TEST);                // Enable depth testing for drawing
  glEnable(GL_MULTISAMPLE);               // Enable multisampling for smoother drawing

  buildShaders();                         // Set up shader buffers
  m_screenQuad.reset(new ScreenQuad());   // Create quad to draw shaders to
  glViewport(0, 0, width(), height());    // Set viewport
  startTimer(10);

  m_compilationTime.start();
}

void NGLScene::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   // Clear the screen and depth buffer
  ngl::ShaderLib::use(m_currentShader);
  updateUniforms();
  m_screenQuad->draw(m_currentShader);
  //std::cout << (m_compilationTime.elapsed() / 1000.0f) << std::endl;
}

void NGLScene::resizeGL(int _w, int _h)
{
  m_win.m_winWidth = static_cast<int>(_w * devicePixelRatio());
  m_win.m_winHeight = static_cast<int>(_h * devicePixelRatio());
}

bool NGLScene::compileShaderCode(QString _shaderCode)
{
  std::cout << "Compiling shader code...\n";
  //qDebug("%s", qUtf8Printable(_shaderCode));
  
  // Load shader code from text edit field into unused shader
  ngl::ShaderLib::loadShaderSourceFromString(m_nextFragment, _shaderCode.toStdString());

  // Get shader ID
  GLuint id = ngl::ShaderLib::getShaderID(m_nextFragment);

  // Compile shader
  glCompileShader(id);

  // Check if shader compiled successfully
  GLint isCompiled = 0;
  glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);

  if (isCompiled == GL_TRUE)
  {
    std::cout << "Fragment shader compiled succesfully!\n";

    // Swap shader buffers
    ngl::ShaderLib::attachShaderToProgram(m_nextShader, m_nextFragment);
    ngl::ShaderLib::linkProgramObject(m_nextShader);
    ngl::ShaderLib::use(m_nextShader);

    // Swap shader variables
    if (m_currentShader == "ShaderProgram_A")
    {
      m_currentShader = "ShaderProgram_B";
      m_nextShader = "ShaderProgram_A";
      m_nextFragment = "Fragment_A";
    }
    else
    {
      m_currentShader = "ShaderProgram_A";
      m_nextShader = "ShaderProgram_B";
      m_nextFragment = "Fragment_B";
    }
  }
  else
  {
    // Shader compilation failed
    std::cout << "Fragment shader failed compilation!\n";

    GLint maxLength = 0;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
    std::vector<GLchar> errorLog(maxLength);
    glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
    m_shaderErrorMessage = errorLog;
    return false;
  }
  // Reset shader inputs
  m_pausedTime = 0;
  m_pauseTime = false;
  m_compilationTime.start();
  resetUniforms();
  return true;
}

void NGLScene::updateUniforms()
{
  if (!m_pauseTime)
  {
    ngl::ShaderLib::setUniform("iTime", float((m_compilationTime.elapsed() + m_pausedTime) / 1000.0f));
    ngl::ShaderLib::setUniform("iMouse", ngl::Vec2(m_win.m_mouseXPos, m_win.m_mouseYPos));
  }
}

void NGLScene::resetUniforms()
{
  ngl::ShaderLib::setUniform("iTime", float(0.0f));
  ngl::ShaderLib::setUniform("iMouse", ngl::Vec2(0.0f, 0.0f));
}

qint64 NGLScene::pauseTime()
{
  m_pauseTime = true;
  return m_compilationTime.elapsed();
}

void NGLScene::unpauseTime(qint64 _pausedTime)
{
  m_pauseTime = false;
  m_pausedTime = _pausedTime;
  m_compilationTime.restart();
}

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  switch (_event->key())
  {
    // Quit application
    case Qt::Key_Escape:
    {
      QGuiApplication::exit(EXIT_SUCCESS);
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
  update();
}

void NGLScene::mouseMoveEvent(QMouseEvent* _event)
{
  if (_event->buttons() == Qt::LeftButton)
  {
    // Clamp mouse position to OpenGL window dimensions
    m_win.m_mouseXPos = std::clamp(_event->x(), 0, m_win.m_winWidth);
    m_win.m_mouseYPos = std::clamp(_event->y(), 0, m_win.m_winHeight);

    update();
  }
}

void NGLScene::mousePressEvent(QMouseEvent* _event)
{
  if (_event->button() == Qt::LeftButton)
  {
    m_win.m_mouseXPos = _event->x();
    m_win.m_mouseYPos = _event->y();
  }
}