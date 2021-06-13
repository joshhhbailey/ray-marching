#ifndef SCREEN_QUAD_H_
#define SCREEN_QUAD_H_

#include <ngl/SimpleVAO.h>
#include <ngl/VAOFactory.h>
#include <ngl/Vec2.h>
#include <ngl/Vec3.h>

#include <string>

class ScreenQuad
{
  public:
    ScreenQuad(const std::string &_shader);
    ~ScreenQuad();
    void draw();

  private:
    std::unique_ptr<ngl::AbstractVAO> m_vao;
    std::string m_shader;
};

#endif  // _SCREEN_QUAD_H_