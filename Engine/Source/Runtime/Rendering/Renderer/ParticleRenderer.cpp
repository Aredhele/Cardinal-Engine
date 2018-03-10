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

/// \file       ParticleRenderer.cpp
/// \date       10/03/2018
/// \project    Cardinal Engine
/// \package    Rendering/Renderer
/// \author     Vincent STEHLY--CALISTO

#include "Glew/include/GL/glew.h"
#include "Runtime/Rendering/Renderer/ParticleRenderer.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Default constructor
ParticleRenderer::ParticleRenderer() : IRenderer()
{
    m_billboardVertexBuffer   = 0;
    m_billboardPositionBuffer = 0;
    m_billboardColorBuffer    = 0;
    m_elementsCount           = 0;
}

/// \brief Destructor
ParticleRenderer::~ParticleRenderer() // NOLINT
{
    // TODO
}

/// \brief Initializes the renderer
void ParticleRenderer::Initialize(int particleAmount)
{
    const GLfloat g_vertex_buffer_data[] =
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
    };

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    m_billboardVertexBuffer = 0;
    glGenBuffers(1, &m_billboardVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_billboardVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);
    glVertexAttribDivisor(0, 0);

    m_billboardPositionBuffer = 0;
    glGenBuffers(1, &m_billboardPositionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_billboardPositionBuffer);
    glBufferData(GL_ARRAY_BUFFER, particleAmount * 4 * sizeof(GLfloat), nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,0, (void*)0);
    glVertexAttribDivisor(1, 1);

    m_billboardColorBuffer = 0;
    glGenBuffers(1, &m_billboardColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_billboardColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, particleAmount * sizeof(glm::vec3), nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);
    glVertexAttribDivisor(2, 1);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

/// \brief Sets the renderer shader
/// \param pShader The pointer on the shader
void ParticleRenderer::SetShader(IShader * pShader)
{
    m_pShader = pShader;
}

/// \brief Sets the color of particles
void ParticleRenderer::SetColor(glm::vec3 const& color)
{
    // TODO
}

/// \brief Base method implementation
/// \param PV The projection view matrix
void ParticleRenderer::Draw(glm::mat4 const& P, glm::mat4 const& V, glm::vec3 const& light, std::vector<PointLightStructure> const& pointLights)
{
    m_pShader->Begin(P * V * m_model, P, V, m_model, light, pointLights);

    glBindVertexArray(m_vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, m_elementsCount);

    m_pShader->End();
}

} // !namespace