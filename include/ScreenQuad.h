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
    ScreenQuad();
    ~ScreenQuad();
    void draw(const std::string &_shader);

  private:
    std::unique_ptr<ngl::AbstractVAO> m_vao;
};

#endif  // _SCREEN_QUAD_H_