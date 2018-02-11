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

/// \file       DebugCube.cpp
/// \date       10/02/2018
/// \project    Cardinal Engine
/// \package    Core/Debug
/// \author     Vincent STEHLY--CALISTO

#include "Glm/glm/ext.hpp"
#include "Rendering/Debug/DebugLine.hpp"
#include "Rendering/Shader/ShaderCompiler.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief  Constructor
DebugLine::DebugLine(glm::vec3 const& pos, glm::vec3 const& dir, glm::vec3 const& color)
{
    position  = pos;
    direction = dir;
    model = glm::mat4(1.0f);

    float vertex_buffer[6] =
    {
            position.x, position.y, position.z,
            position.x + direction.x,
            position.y + direction.y,
            position.z + direction.z
    };

    float color_buffer[6] =
    {
        color.x, color.y, color.z,
        color.x, color.y, color.z
    };

    m_vbo = 0;
    m_cbo = 0;
    m_vao = 0;
    m_shader = 0;

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_buffer), vertex_buffer, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);

    glGenBuffers(1, &m_cbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_cbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color_buffer), color_buffer, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);

    m_shader   = cardinal::ShaderCompiler::LoadShaders("Resources/Shaders/vsbase.glsl", "Resources/Shaders/fsbase.glsl");
    m_matrixID = glGetUniformLocation(m_shader, "MVP");

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

/// \brief  Destructor
DebugLine::~DebugLine()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_cbo);
    glDeleteProgram(m_shader);
    glDeleteVertexArrays(1, &m_vao);
}

/// \brief  Renders the cube
void DebugLine::Render(glm::mat4 const& P, glm::mat4 const& V)
{
    glm::mat4 MVP = P * V * model;

    glUseProgram(m_shader);
    glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &MVP[0][0]);

    glBindVertexArray(m_vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_LINES, 0, 2);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

} // !namespace