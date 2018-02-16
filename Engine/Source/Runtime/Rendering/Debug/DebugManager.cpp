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

/// \file       DebugManager.cpp
/// \date       16/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Debug
/// \author     Vincent STEHLY--CALISTO

#include "Glew/include/GL/glew.h"
#include "Runtime/Core/Assertion/Assert.hh"
#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/Debug/DebugManager.hpp"

/// \namespace cardinal
namespace cardinal
{

/* static */ DebugManager * DebugManager::s_pInstance = nullptr;

// TODO : Remove magic number 5000
/// \brief Constructor, allocates buffers
DebugManager::DebugManager()
{
    m_vao         = 0;
    m_vbo         = 0;
    m_cbo         = 0;
    m_matrixID    = 0;
    m_shaderID    = 0;
    m_vertexCount = 0;

    // Getting color shader
    m_shaderID = ShaderManager::GetShaderID("UnlitColor");
    m_matrixID = glGetUniformLocation(m_shaderID, "MVP");

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers          (1, &m_vbo);
    glBindBuffer          (GL_ARRAY_BUFFER, m_vbo);
    glBufferData          (GL_ARRAY_BUFFER, 5000 * sizeof(glm::vec3), &m_vertices[0], GL_DYNAMIC_DRAW);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);

    glGenBuffers          (1, &m_cbo);
    glBindBuffer          (GL_ARRAY_BUFFER, m_cbo);
    glBufferData          (GL_ARRAY_BUFFER, 5000 * sizeof(glm::vec3), &m_colors[0], GL_DYNAMIC_DRAW);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

/// \brief Desutrctor, free buffers
DebugManager::~DebugManager()
{
    // TODO
}

/// \brief Adds a line to render for the next frame
/// \param start The start point of the line
/// \param end The end point
/// \param color The color of the line
/* static */ void DebugManager::AddLine(const glm::vec3 &start,
        const glm::vec3 &end,
        const glm::vec3 &color)
{
    ASSERT_NOT_NULL(s_pInstance);

    if(s_pInstance->m_vertexCount + 2 >= 5000)
    {
        Logger::LogWaring("Too many debug lines, ignoring current line");
        return;
    }

    s_pInstance->m_vertices[s_pInstance->m_vertexCount + 0] = start;
    s_pInstance->m_vertices[s_pInstance->m_vertexCount + 1] = end;
    s_pInstance->m_colors  [s_pInstance->m_vertexCount + 0] = color;
    s_pInstance->m_colors  [s_pInstance->m_vertexCount + 1] = color;

    s_pInstance->m_vertexCount += 2;
}

/// \brief Initializes the debug manager
///        Initializes the manager instance
/* static */ void DebugManager::Initialize()
{
    if(DebugManager::s_pInstance == nullptr)
    {
        DebugManager::s_pInstance = new DebugManager();
        Logger::LogInfo("Debug manager successfully initialized");
    }
    else
    {
        Logger::LogWaring("The debug manager is already initialized");
    }
}

/// \brief Destroys the debug manager
///        Destroys the manager instance
/* static */ void DebugManager::Shutdown()
{
    if(DebugManager::s_pInstance != nullptr)
    {
        delete DebugManager::s_pInstance;
        DebugManager::s_pInstance = nullptr;

        Logger::LogInfo("Debug manager successfully destroyed");
    }
    else
    {
        Logger::LogWaring("The debug manager is already destroyed");
    }
}

/// \brief Clears vertices and colors
/* static */ void DebugManager::Clear()
{
    ASSERT_NOT_NULL(DebugManager::s_pInstance);

    // Resets the counter
    DebugManager::s_pInstance->m_vertexCount = 0;
}

/// \brief Updates buffers and setup the shader
/* static */ void DebugManager::Draw(glm::mat4 const &PV)
{
    ASSERT_NOT_NULL(s_pInstance);

    if(s_pInstance->m_vertexCount == 0)
    {
        // There's nothing to draw
        return;
    }

    // Computes MVP matrix
    glm::mat4 MVP = PV * glm::mat4(1.0f);

    // Updates buffers
    glBindBuffer   (GL_ARRAY_BUFFER, s_pInstance->m_vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, s_pInstance->m_vertexCount * sizeof(glm::vec3), s_pInstance->m_vertices);

    glBindBuffer   (GL_ARRAY_BUFFER, s_pInstance->m_cbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, s_pInstance->m_vertexCount * sizeof(glm::vec3), s_pInstance->m_colors);

    glEnable (GL_MULTISAMPLE);
    glDisable(GL_BLEND);

    // Sets up shader
    glUseProgram      (s_pInstance->m_shaderID);
    glUniformMatrix4fv(s_pInstance->m_matrixID, 1, GL_FALSE, &MVP[0][0]);

    // Draws all lines
    glBindVertexArray(DebugManager::s_pInstance->m_vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_LINES, 0, s_pInstance->m_vertexCount);

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);

    glDisable(GL_MULTISAMPLE);
}

} // !namespace