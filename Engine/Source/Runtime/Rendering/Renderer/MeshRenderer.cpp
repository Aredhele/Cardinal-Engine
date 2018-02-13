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
/// \date       11/02/2018
/// \project    Cardinal Engine
/// \package    Rendering/Renderer
/// \author     Vincent STEHLY--CALISTO

#include "Runtime/Rendering/Texture/TextureLoader.hpp"
#include "Runtime/Rendering/Renderer/MeshRenderer.hpp"
#include "Runtime/Rendering/Optimization/VBOIndexer.hpp"
#include "Runtime/Rendering/Shader/ShaderCompiler.hpp"

#include "Glfw/glfw3.h"
#include "Runtime/Core/Debug/Logger.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Default constructor
MeshRenderer::MeshRenderer()
{
    // TODO
}

/// \brief Destructor
MeshRenderer::~MeshRenderer()
{
    // TODO
}

/// \brief Initializes the mesh
/// \param indexes The indexes of the mesh
/// \param vertices The vertices of the mesh
/// \param colors The colors of the mesh
void MeshRenderer::Initialize(
        std::vector<unsigned short> const& indexes,
        std::vector<glm::vec3>      const& vertices,
        std::vector<glm::vec2>      const& uvs)
{
    // TODO Assertions

    // Instrumentation
   // Logger::LogInfo("Begin mesh renderer initialization ...");

    double startTime = glfwGetTime();

    // Generating vao
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_indexesObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexesObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned short) ,&indexes[0], GL_STATIC_DRAW);

    glGenBuffers(1, &m_verticesObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_verticesObject);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);

    glGenBuffers(1, &m_uvsObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_uvsObject);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);

    m_elementsCount = static_cast<GLsizei>(indexes.size());

    // Loading shaders
    // TODO : Remove
    m_shaderID = ShaderCompiler::LoadShaders(
            "Resources/Shaders/vsbase.glsl",
            "Resources/Shaders/fsbase.glsl");

    m_matrixID = glGetUniformLocation(m_shaderID, "MVP");

 //   m_texture = TextureLoader::LoadBMPTexture("Resources/Textures/BlockAtlas.bmp");

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);

    double elapsed = glfwGetTime() - startTime;
 //   Logger::LogInfo("Mesh renderer initialization completed in %lf seconds", elapsed);
}

} // !namespace