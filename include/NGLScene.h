#ifndef NGLSCENE_H_
#define NGLSCENE_H_

#include <ngl/Transformation.h>
#include <ngl/Text.h>

// this must be included after NGL includes else we get a clash with gl libs
#include <QEvent>
#include <QOpenGLWidget>
#include <QResizeEvent>
#include <QSet>

#include "ScreenQuad.h"
#include "WindowParams.h"

#include <memory>

class NGLScene : public QOpenGLWidget
{
  Q_OBJECT  // Use of signals and slots
  public:
    NGLScene(QWidget *_parent);
    ~NGLScene() override;
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int _w, int _h) override;

  public slots:
    // Buttons

private:
    void keyPressEvent(QKeyEvent *_event) override;
    void mouseMoveEvent (QMouseEvent * _event) override;
    void mousePressEvent ( QMouseEvent *_event) override;
    void mouseReleaseEvent ( QMouseEvent *_event) override;
    void wheelEvent( QWheelEvent *_event) override;
    void timerEvent(QTimerEvent *_event) override;

    // Window parameters for mouse controls etc.
    WinParams m_win;

    std::unique_ptr<ScreenQuad> m_screenQuad;
    
    void loadMatricesToShader();
};

#endif