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

/// \file       ProceduralBuildingRenderer.cpp
/// \date       07/03/2018
/// \project    Cardinal Engine
/// \package    City
/// \author     Vincent STEHLY--CALISTO

#include "Glew/include/GL/glew.h"
#include "City/ProceduralBuildingRenderer.hpp

/// \brief Default constructor
ProceduralBuildingRenderer::ProceduralBuildingRenderer() : cardinal::IRenderer()
{
    m_verticesObject = 0;
    m_normalsObject  = 0;
    m_uvsObject      = 0;
    m_elementsCount  = 0;
}

/// \brief Destructor
ProceduralBuildingRenderer::~ProceduralBuildingRenderer() // NOLINT
{
    // TODO
}

/// \brief Initializes the mesh
/// \param vertices The vertices of the mesh
/// \param normals The normals of the mesh
/// \param colors The uvs of the mesh
void ProceduralBuildingRenderer::Initialize(
        std::vector<glm::vec3>      const &vertices,
        std::vector<glm::vec3>      const &normals,
        std::vector<glm::vec2>      const &uvs)
{
    if (m_vao != 0)
    {
        glDeleteBuffers(1, &m_verticesObject);
        glDeleteBuffers(1, &m_normalsObject);
        glDeleteBuffers(1, &m_uvsObject);

        m_verticesObject = 0;
        m_normalsObject  = 0;
        m_uvsObject      = 0;
        m_elementsCount  = 0;
    }
    else if (m_vao == 0)
    {
        glGenVertexArrays(1, &m_vao);
    }

    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_verticesObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_verticesObject);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

    glGenBuffers(1, &m_normalsObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_normalsObject);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

    glGenBuffers(1, &m_uvsObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_uvsObject);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    m_elementsCount = static_cast<GLsizei>(vertices.size());
}

/// \brief Updates the mesh
/// \param vertices The vertices of the mesh
/// \param normals The normals of the mesh
/// \param uvs The uvs of the mesh
void ProceduralBuildingRenderer::Update(
        std::vector<glm::vec3>      const &vertices,
        std::vector<glm::vec3>      const &normals,
        std::vector<glm::vec2>      const &uvs)
{
    if (vertices.empty())
    {
        // Hot fix
        return;
    }

    if (m_elementsCount < vertices.size())
    {
        // The buffer is too small, we need to
        // recreates buffers
        Initialize(vertices, normals, uvs);
        return;
    }

    glBindVertexArray(m_vao);

    glBindBuffer   (GL_ARRAY_BUFFER, m_verticesObject);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(glm::vec3), &vertices[0]);

    glBindBuffer   (GL_ARRAY_BUFFER, m_normalsObject);
    glBufferSubData(GL_ARRAY_BUFFER, 0, normals.size() * sizeof(glm::vec3), &normals[0]);

    glBindBuffer   (GL_ARRAY_BUFFER, m_uvsObject);
    glBufferSubData(GL_ARRAY_BUFFER, 0, uvs.size() * sizeof(glm::vec2), &uvs[0]);

    m_elementsCount = static_cast<GLsizei>(vertices.size());

    glBindVertexArray(0);
}

/// \brief Sets the renderer shader
/// \param pShader The pointer on the shader
void ProceduralBuildingRenderer::SetShader(cardinal::IShader * pShader)
{
    m_pShader = pShader;
}

/// \brief Translates the model
/// \param Translation The translation vector
void ProceduralBuildingRenderer::Translate(glm::vec3 const &Translation)
{
    m_model = glm::translate(m_model, Translation);
}

/// \brief Sets the position of the mesh renderer
/// \param position The new position
void ProceduralBuildingRenderer::SetPosition(const glm::vec3 &position)
{
    m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, position);
}

/// \brief Base method implementation
/// \param PV The projection view matrix
void ProceduralBuildingRenderer::Draw(glm::mat4 const& P, glm::mat4 const& V, glm::vec3 const& light, std::vector<cardinal::PointLightStructure> const& pointLights)
{
    m_pShader->Begin(P * V * m_model, P, V, m_model, light, pointLights);

    glBindVertexArray(m_vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glDrawArrays(GL_TRIANGLES, 0, m_elementsCount);

    m_pShader->End();
}

} // !namespace