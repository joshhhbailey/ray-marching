/// \brief Creates a surface for the fragment shader to be projected to
/// \author Josh Bailey
/// \date 19/08/21 Updated to NCCA Coding standard

#ifndef SCREENQUAD_H_
#define SCREENQUAD_H_

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

#endif  // _SCREENQUAD_H_