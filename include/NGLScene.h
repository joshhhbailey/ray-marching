/// \brief Handles logic for OpenGL context
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef NGLSCENE_H_
#define NGLSCENE_H_

// this must be included after NGL includes else we get a clash with gl libs
#include <QtWidgets/QOpenGLWidget>
#include <QElapsedTimer>

#include <memory>

#include "ScreenQuad.h"
#include "WindowParams.h"

class NGLScene : public QOpenGLWidget
{
  public:
    NGLScene();
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int _w, int _h) override;
    bool compileShaderCode(QString _shaderCode, bool _shaderEditor);
    std::vector<GLchar> getShaderErrorMessage() { return m_shaderErrorMessage; }
    QString getBoilerPlateCode() { return m_boilerPlateCode; }
    bool getShaderEditor() { return m_shaderEditor; }

    float getCompilationTime() { return (m_compilationTime.elapsed() / 1000.0f); }
    qint64 pauseTime();
    void unpauseTime(qint64 _pausedTime);

private:
    void keyPressEvent(QKeyEvent *_event) override;
    void mouseMoveEvent(QMouseEvent * _event) override;
    void mousePressEvent(QMouseEvent *_event) override;
    void timerEvent(QTimerEvent *_event) override;

    void buildShaders();
    void updateUniforms();
    void resetUniforms();

    WinParams m_win;
    std::unique_ptr<ScreenQuad> m_screenQuad;

    // Shader buffers
    std::string m_currentShader = "ShaderProgram_A";
    std::string m_nextShader = "ShaderProgram_B";
    std::string m_nextFragment = "Fragment_B";

    std::vector<GLchar> m_shaderErrorMessage;
    QString m_boilerPlateCode =
      "#version 410 core"
      "\n"
      "layout (location = 0) out vec4 fragColour;\n"
      "\n"
      "in vec2 iUV;\n"
      "uniform float iTime;\n"
      "uniform vec2 iMouse;\n"
      "\n";

    // Compilation timer
    QElapsedTimer m_compilationTime;
    bool m_pauseTime = false;
    qint64 m_pausedTime = 0;
    
    // WHAT COMPILED?: true = Shader Editor, false = Node Editor
    bool m_shaderEditor = true;
};

#endif  // _NGLSCENE_H