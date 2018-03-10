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
    m_maxParticleAmount       = 0;

    billboardColorBuffer      = nullptr;
    billboardPositionBuffer   = nullptr;
}

/// \brief Destructor
ParticleRenderer::~ParticleRenderer() // NOLINT
{
    delete[] billboardColorBuffer;
    delete[] billboardPositionBuffer;
}

/// \brief Initializes the renderer
/// \param particleAmount The max amount of particles
void ParticleRenderer::Initialize(int maxParticleAmount)
{
    const GLfloat g_vertex_buffer_data[] =
    {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
    };

    m_maxParticleAmount     = (uint)maxParticleAmount;
    billboardColorBuffer    = new float[maxParticleAmount * 3];
    billboardPositionBuffer = new float[maxParticleAmount * 4];

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
    glBufferData(GL_ARRAY_BUFFER, maxParticleAmount * 4 * sizeof(GLfloat), nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE,0, (void*)0);
    glVertexAttribDivisor(1, 1);

    m_billboardColorBuffer = 0;
    glGenBuffers(1, &m_billboardColorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_billboardColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, maxParticleAmount * sizeof(glm::vec3), nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);
    glVertexAttribDivisor(2, 1);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

/// \brief Sets the currentElementCount
void ParticleRenderer::SetElementCount(int count)
{
    m_elementsCount = count;
}

/// \brief Sets the renderer shader
/// \param pShader The pointer on the shader
void ParticleRenderer::SetShader(IShader * pShader)
{
    m_pShader = pShader;
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

/// \brief Updates positions and color buffers
void ParticleRenderer::UpdateBuffer()
{
    glBindVertexArray(m_vao);

    glBindBuffer   (GL_ARRAY_BUFFER, m_billboardPositionBuffer);
    glBufferData   (GL_ARRAY_BUFFER, m_maxParticleAmount * 4 * sizeof(GLfloat), nullptr, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_elementsCount * sizeof(GLfloat) * 4, billboardPositionBuffer);

    glBindBuffer   (GL_ARRAY_BUFFER, m_billboardColorBuffer);
    glBufferData   (GL_ARRAY_BUFFER, m_maxParticleAmount * 4 * sizeof(GLubyte), nullptr, GL_STREAM_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_elementsCount * sizeof(GLubyte) * 4, billboardColorBuffer);

    glBindVertexArray(0);
}

} // !namespace