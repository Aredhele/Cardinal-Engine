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

/// \file       MeshRenderer.cpp
/// \date       23/02/2018
/// \project    Cardinal Engine
/// \package    Rendering/Renderer
/// \author     Vincent STEHLY--CALISTO

#include "Glew/include/GL/glew.h"

#include "Runtime/Rendering/Renderer/MeshRenderer.hpp"
#include "Runtime/Rendering/Texture/TextureManager.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Default constructor
MeshRenderer::MeshRenderer() : IRenderer()
{
    m_indexesObject  = 0;
    m_verticesObject = 0;
    m_normalsObject  = 0;
    m_uvsObject      = 0;
    m_elementsCount  = 0;
}

/// \brief Destructor
MeshRenderer::~MeshRenderer() // NOLINT
{
    // TODO
}

/// \brief Initializes the mesh
/// \param indexes The indexes of the mesh
/// \param vertices The vertices of the mesh
/// \param normals The normals of the mesh
/// \param colors The uvs of the mesh
void MeshRenderer::Initialize(
        std::vector<unsigned short> const &indexes,
        std::vector<glm::vec3>      const &vertices,
        std::vector<glm::vec3>      const &normals,
        std::vector<glm::vec2>      const &uvs)
{
    if (m_vao != 0)
    {
        glDeleteBuffers(1, &m_indexesObject);
        glDeleteBuffers(1, &m_verticesObject);
        glDeleteBuffers(1, &m_normalsObject);
        glDeleteBuffers(1, &m_uvsObject);

        m_indexesObject  = 0;
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

    glGenBuffers(1, &m_indexesObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexesObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned short), &indexes[0], GL_STATIC_DRAW);

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

    m_elementsCount = static_cast<GLsizei>(indexes.size());
}

/// \brief Updates the mesh
/// \param indexes The indexes of the mesh
/// \param vertices The vertices of the mesh
/// \param normals The normals of the mesh
/// \param uvs The uvs of the mesh
void MeshRenderer::Update(
        std::vector<unsigned short> const &indexes,
        std::vector<glm::vec3>      const &vertices,
        std::vector<glm::vec3>      const &normals,
        std::vector<glm::vec2>      const &uvs)
{
    if (indexes.empty())
    {
        // Hot fix
        return;
    }

    if (m_elementsCount < indexes.size())
    {
        // The buffer is too small, we need to
        // recreates buffers
        Initialize(indexes, vertices, normals, uvs);
        return;
    }

    glBindVertexArray(m_vao);

    glBindBuffer   (GL_ELEMENT_ARRAY_BUFFER, m_indexesObject);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indexes.size() * sizeof(unsigned short), &indexes[0]);

    glBindBuffer   (GL_ARRAY_BUFFER, m_verticesObject);
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(glm::vec3), &vertices[0]);

    glBindBuffer   (GL_ARRAY_BUFFER, m_normalsObject);
    glBufferSubData(GL_ARRAY_BUFFER, 0, normals.size() * sizeof(glm::vec3), &normals[0]);

    glBindBuffer   (GL_ARRAY_BUFFER, m_uvsObject);
    glBufferSubData(GL_ARRAY_BUFFER, 0, uvs.size() * sizeof(glm::vec2), &uvs[0]);

    m_elementsCount = static_cast<GLsizei>(indexes.size());

    glBindVertexArray(0);
}

/// \brief Sets the renderer shader
/// \param pShader The pointer on the shader
void MeshRenderer::SetShader(IShader * pShader)
{
    m_pShader = pShader;
}

/// \brief Translates the model
/// \param Translation The translation vector
void MeshRenderer::Translate(glm::vec3 const &Translation)
{
    m_model = glm::translate(m_model, Translation);
}

/// \brief Sets the position of the mesh renderer
/// \param position The new position
void MeshRenderer::SetPosition(const glm::vec3 &position)
{
    m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, position);
}

/// \brief Base method implementation
/// \param PV The projection view matrix
void MeshRenderer::Draw(glm::mat4 const& P, glm::mat4 const& V, glm::vec3 const& light, std::vector<PointLightStructure> const& pointLights)
{
    m_pShader->Begin(P * V * m_model, P, V, m_model, light, pointLights);

    glBindVertexArray(m_vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glDrawElements(GL_TRIANGLES, m_elementsCount, GL_UNSIGNED_SHORT, nullptr);

    m_pShader->End();
}

} // !namespace