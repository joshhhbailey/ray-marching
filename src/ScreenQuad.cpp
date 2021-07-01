#include "ScreenQuad.h"

#include <iostream>

#include <ngl/ShaderLib.h>

ScreenQuad::ScreenQuad()
{
  static ngl::Vec3 vertexData[] = {
                                  // Vertices
                                  ngl::Vec3(-1.0f, -1.0f, 0.0f),
                                  ngl::Vec3(1.0f, -1.0f, 0.0f),
                                  ngl::Vec3(1.0f, 1.0f, 0.0f),
                                  ngl::Vec3(1.0f, 1.0f, 0.0f),
                                  ngl::Vec3(-1.0f, -1.0f, 0.0f),
                                  ngl::Vec3(-1.0f, 1.0f, 0.0f),
                                  
                                  // UVs
                                  ngl::Vec3(0.0f, 1.0f, 0.0f),
                                  ngl::Vec3(1.0f, 1.0f, 0.0f),
                                  ngl::Vec3(1.0f, 0.0f, 0.0f),
                                  ngl::Vec3(1.0f, 0.0f, 0.0f),
                                  ngl::Vec3(0.0f, 1.0f, 0.0f),
                                  ngl::Vec3(0.0f, 0.0f, 0.0f)
                                  };

  std::cout << "Building VAO...\n";
  m_vao = ngl::VAOFactory::createVAO(ngl::simpleVAO, GL_TRIANGLES);
  m_vao->bind();
  m_vao->setData(ngl::SimpleVAO::VertexData(12 * sizeof(ngl::Vec3), vertexData[0].m_x));
  m_vao->setVertexAttributePointer(0, 3, GL_FLOAT, 0, 0);       // Vertices
  m_vao->setVertexAttributePointer(1, 3, GL_FLOAT, 0, 6 * 3);   // Normals
  m_vao->setNumIndices(6);
  m_vao->unbind();
  std::cout << "VAO built!\n";
}

ScreenQuad::~ScreenQuad()
{
  m_vao->removeVAO();
}

void ScreenQuad::draw(const std::string &_shader)
{
  ngl::ShaderLib::use(_shader);
  m_vao->bind();
  m_vao->draw();
  m_vao->unbind();
}
