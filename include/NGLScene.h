#ifndef NGLSCENE_H_
#define NGLSCENE_H_

#include <ngl/Transformation.h>
#include <ngl/Text.h>

// this must be included after NGL includes else we get a clash with gl libs
#include <QtWidgets/QOpenGLWidget>

#include "ScreenQuad.h"
#include "WindowParams.h"

#include <memory>

class NGLScene : public QOpenGLWidget
{
  public:
    NGLScene();
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int _w, int _h) override;

private:
    void keyPressEvent(QKeyEvent *_event) override;
    void mouseMoveEvent(QMouseEvent * _event) override;
    void mousePressEvent(QMouseEvent *_event) override;
    void mouseReleaseEvent(QMouseEvent *_event) override;
    void wheelEvent(QWheelEvent *_event) override;
    void timerEvent(QTimerEvent *_event) override;

    void loadMatricesToShader();

    WinParams m_win;
    std::unique_ptr<ScreenQuad> m_screenQuad;
};

#endif