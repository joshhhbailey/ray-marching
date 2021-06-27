#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>

#include <iostream>

#include "Window.h"

int main(int argc, char **argv)
{
  // Create Qt application
  QApplication app(argc, argv);
  app.setStyle(QStyleFactory::create("fusion"));
  app.setPalette(*Window::darkPalette());

  QSurfaceFormat format;
  format.setSamples(4);

  #if defined(__APPLE__)
      // Latest version (4.1) before deprecation
      format.setMajorVersion(4);
      format.setMinorVersion(1);
  #else
      format.setMajorVersion(4);
      format.setMinorVersion(3);
  #endif
  
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setDepthBufferSize(24);
  QSurfaceFormat::setDefaultFormat(format);

  // Create application window
  Window window;
  window.resize(1024, 720);
  window.show();

  return app.exec();
}
