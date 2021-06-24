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

  // Create application window
  Window window;
  window.resize(1024, 720);
  window.show();

  return app.exec();
}
