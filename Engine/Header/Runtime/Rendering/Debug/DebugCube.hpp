/// Copyright (C) 2018-2019, Cardinal Engine
/// Vincent STEHLY--CALISTO, vincentstehly@hotmail.fr
///
/// This program is free software; you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation; either version 2 of the License, or
/// (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program; if not, write to the Free Software Foundation, Inc.,
/// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

/// \file       DebugCube.hpp
/// \date       10/02/2018
/// \project    Cardinal Engine
/// \package    Core/Debug
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_DEBUG_CUBE_HPP__
#define CARDINAL_ENGINE_DEBUG_CUBE_HPP__

#include "Glm/glm/glm.hpp"
#include "Glew/include/GL/glew.h"

/// \namespace cardinal
namespace cardinal
{

/// \class DebugCube
/// \brief Simple 3D cube for debug purpose
class DebugCube
{
public :

    glm::vec3 position;
    glm::mat4 model;

    static const float s_vertex_buffer[108];
    static const float s_color_buffer [108];

public:

    /// \brief  Constructor
    DebugCube();

    /// \brief  Destructor
    ~DebugCube();

    void Translate(glm::vec3 const& translation);

    /// \brief  Renders the cube
    void Render(glm::mat4 const& P, glm::mat4 const& V);

private:

    GLuint m_vbo;
    GLuint m_cbo;
    GLuint m_vao;
    GLuint m_shader;
    GLint  m_matrixID;
};

} // !namespace

#endif // !CARDINAL_ENGINE_DEBUG_CUBE_HPP__
