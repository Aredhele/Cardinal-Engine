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

/// \file       TextRenderer.cpp
/// \date       11/02/2018
/// \project    Cardinal Engine
/// \package    Rendering/Renderer
/// \author     Vincent STEHLY--CALISTO

#include <iostream>
#include "Glew/include/GL/glew.h"

#include "Runtime/Rendering/Renderer/TextRenderer.hpp"
#include "Runtime/Rendering/Texture/TextureManager.hpp"
#include "Runtime/Rendering/Shader/Built-in/TextShader.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Default constructor
TextRenderer::TextRenderer() : IRenderer()
{
    m_vertexObject   = 0;
    m_uvsObject      = 0;
    m_vertexCount    = 0;
}

/// \brief Destructor
TextRenderer::~TextRenderer() // NOLINT
{
    delete m_pShader;

    // TODO : Delete buffers
}

/// \brief Initializes the text renderer
void TextRenderer::Initialize()
{
    // Initialize texture
    m_pShader = new TextShader();

    // Initialize VBO
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vertexObject);
    glGenBuffers(1, &m_uvsObject);

    glBindVertexArray(0);

    // Default text
    SetText("Text", 0, 0, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

/// \brief Sets the renderer shader
/// \param pShader The pointer on the shader
void TextRenderer::SetShader(IShader * pShader)
{
    m_pShader = pShader;
}

/// \brief Updates the text
/// \param szText The text to display
/// \param x The x coordinate (screen space)
/// \param y The y coordinate (screen space)
/// \param size The size of the text
/// \param color The color of the text
void TextRenderer::SetText(const char * szText, int x, int y, int size, glm::vec4 const& color)
{
    size_t length = strlen(szText);
    ((TextShader *)m_pShader)->SetColor(color);

    // Fill buffers
    std::vector<glm::vec2> UVs;
    std::vector<glm::vec2> vertices;

    float charShift = 0.0f;
    for (size_t i = 0; i < length; i++)
    {
        glm::vec2 vertex_up_left    = glm::vec2(x + i * size,        y + size);
        glm::vec2 vertex_up_right   = glm::vec2(x + i * size + size, y + size);
        glm::vec2 vertex_down_right = glm::vec2(x + i * size + size, y);
        glm::vec2 vertex_down_left  = glm::vec2(x + i * size,        y);

        if(i != 0)
        {
            vertex_up_left.x    -=  (size / 1.7f) * i + charShift;
            vertex_up_right.x   -=  (size / 1.7f) * i + charShift;
            vertex_down_right.x -=  (size / 1.7f) * i + charShift;
            vertex_down_left.x  -=  (size / 1.7f) * i + charShift;
        }

        if     (szText[i] == 'i') charShift += (size / 5.0f);
        else if(szText[i] == '.') charShift += (size / 5.0f);
        else if(szText[i] == 'm') charShift -= (size / 8.0f);
        else if(szText[i] == 'r') charShift += (size / 8.0f);

        vertices.push_back(vertex_up_left);
        vertices.push_back(vertex_down_left);
        vertices.push_back(vertex_up_right);

        vertices.push_back(vertex_down_right);
        vertices.push_back(vertex_up_right);
        vertices.push_back(vertex_down_left);

        char character = szText[i];
        float uv_x = (character % 16) / 16.0f;
        float uv_y = (character / 16) / 16.0f;

        glm::vec2 uv_up_left    = glm::vec2(uv_x,                 uv_y);
        glm::vec2 uv_up_right   = glm::vec2(uv_x + 1.0f / 16.0f,  uv_y);
        glm::vec2 uv_down_right = glm::vec2(uv_x + 1.0f / 16.0f, (uv_y + 1.0f / 16.0f));
        glm::vec2 uv_down_left  = glm::vec2(uv_x ,               (uv_y + 1.0f / 16.0f));

        UVs.push_back(uv_up_left);
        UVs.push_back(uv_down_left);
        UVs.push_back(uv_up_right);

        UVs.push_back(uv_down_right);
        UVs.push_back(uv_up_right);
        UVs.push_back(uv_down_left);
    }

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexObject);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, m_uvsObject);
    glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    m_vertexCount = static_cast<uint>(vertices.size());
}

/// \brief Base method implementation
/// \param PV The projection view matrix
void TextRenderer::Draw(glm::mat4 const& P, glm::mat4 const& V, glm::vec3 const& light)
{
    m_pShader->Begin(P * V * glm::mat4(1.0f), V, glm::mat4(1.0f), light);

    glBindVertexArray(m_vao);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLES, 0, m_vertexCount);

    m_pShader->End();
}

} // !namespace