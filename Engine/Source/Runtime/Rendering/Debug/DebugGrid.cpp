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

/// \file       DebugGrid.cpp
/// \date       25/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Debug
/// \author     Vincent STEHLY--CALISTO

#include <vector>

#include <ThirdParty/Glm/glm/glm.hpp>
#include <ThirdParty/Glew/include/GL/glew.h>

#include "Runtime/Rendering/Debug/DebugGrid.hpp"
#include "Runtime/Rendering/Shader/ShaderManager.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Initializes the grid from parameters
/// \param size The number of lines on X & Y
/// \param spacing The space between two cols & rows
/// \param color The colors of lines
void DebugGrid::Initialize(int size, float spacing, glm::vec3 const& color)
{
    m_vao         = 0;
    m_vbo         = 0;
    m_cbo         = 0;
    m_matrixID    = 0;
    m_shaderID    = 0;
    m_vertexCount = 0;

    // Getting color shader
    m_shaderID = static_cast<uint>(ShaderManager::GetShaderID("UnlitColor"));
    m_matrixID = glGetUniformLocation(m_shaderID, "MVP");

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;

    for(int i = 0; i < size; ++i)
    {
        float d = i * spacing - size * spacing / 2.0f;
        vertices.emplace_back(i * spacing - size * spacing / 2.0f, -size * spacing / 2.0f, 0.0f);
        vertices.emplace_back(i * spacing - size * spacing / 2.0f, +size * spacing / 2.0f, 0.0f);
        vertices.emplace_back(-size * spacing / 2.0f, i * spacing - size * spacing / 2.0f, 0.0f);
        vertices.emplace_back(+size * spacing / 2.0f, i * spacing - size * spacing / 2.0f, 0.0f);

        colors.push_back(color);
        colors.push_back(color);
        colors.push_back(color);
        colors.push_back(color);
    }

    m_vertexCount = static_cast<uint>(vertices.size());

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers          (1, &m_vbo);
    glBindBuffer          (GL_ARRAY_BUFFER, m_vbo);
    glBufferData          (GL_ARRAY_BUFFER, m_vertexCount * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);

    glGenBuffers          (1, &m_cbo);
    glBindBuffer          (GL_ARRAY_BUFFER, m_cbo);
    glBufferData          (GL_ARRAY_BUFFER, m_vertexCount * sizeof(glm::vec3), &colors[0], GL_STATIC_DRAW);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

/// \brief Draws the grid
/// \param PV The projection view matrix
void DebugGrid::Draw(glm::mat4 const& PV)
{
    // Computes MVP matrix
    glm::mat4 MVP = PV * glm::mat4(1.0f);

    glEnable (GL_MULTISAMPLE);
    glDisable(GL_BLEND);

    // Sets up shader
    glUseProgram      (m_shaderID);
    glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &MVP[0][0]);

    // Draws all lines
    glBindVertexArray(m_vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_LINES, 0, m_vertexCount);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

    glDisable(GL_MULTISAMPLE);
}


} // !namespace