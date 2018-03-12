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

/// \file       LineRenderer.cpp
/// \date       12/03/2018
/// \project    Cardinal Engine
/// \package    Rendering/Renderer
/// \author     Vincent STEHLY--CALISTO

#include "Glew/include/GL/glew.h"
#include "ImGUI/Header/ImGUI/imgui.h"

#include "Runtime/Rendering/Renderer/LineRenderer.hpp"
#include "Runtime/Rendering/Texture/TextureManager.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Default constructor
LineRenderer::LineRenderer() : IRenderer()
{
    m_verticesObject = 0;
    m_elementsCount  = 0;
    m_maxElement     = 1024;

    inspectorName = "Line Renderer";

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_verticesObject);
    glBindBuffer(GL_ARRAY_BUFFER, m_verticesObject);
    glBufferData(GL_ARRAY_BUFFER, m_maxElement * sizeof(glm::vec3), nullptr, GL_STREAM_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) nullptr);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    m_elementsCount = 0;
}

/// \brief Destructor
LineRenderer::~LineRenderer() // NOLINT
{
    // TODO
}

/// \brief Sets the renderer shader
/// \param pShader The pointer on the shader
void LineRenderer::SetShader(IShader * pShader)
{
    m_pShader = pShader;
}

/// \brief Translates the model
/// \param Translation The translation vector
void LineRenderer::Translate(glm::vec3 const &Translation)
{
    m_model = glm::translate(m_model, Translation);
}

/// \brief Sets the position of the mesh renderer
/// \param position The new position
void LineRenderer::SetPosition(const glm::vec3 &position)
{
    m_model = glm::mat4(1.0f);
    m_model = glm::translate(m_model, position);
}

/// \brief Clears all lines
void LineRenderer::Clear()
{
    m_lines.clear();
    m_elementsCount = 0;
}

/// \brief Adds a line to the renderer
/// \param start The start point
/// \param end The end point
void LineRenderer::AddLine(glm::vec3 const &start, glm::vec3 const &end)
{
    m_lines.push_back(start);
    m_lines.push_back(end);
    m_elementsCount += 2;

    // Quick buffer updates
    glBindVertexArray(m_vao);

    glBindBuffer   (GL_ARRAY_BUFFER, m_verticesObject);
    glBufferSubData(GL_ARRAY_BUFFER, (m_elementsCount - 2) * sizeof(glm::vec3), m_elementsCount * sizeof(glm::vec3), &m_lines[m_elementsCount - 2]);

    glBindVertexArray(0);
}

/// \brief Base method implementation
/// \param PV The projection view matrix
void LineRenderer::Draw(glm::mat4 const& P, glm::mat4 const& V, glm::vec3 const& light, std::vector<PointLightStructure> const& pointLights)
{
    if(m_elementsCount == 0)
    {
        // Early exit
        return;
    }

    m_pShader->Begin(P * V * m_model, P, V, m_model, light, pointLights);

    glBindVertexArray(m_vao);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_LINES, 0, m_elementsCount);

    m_pShader->End();
}

/// \brief Called when the object is inspected
void LineRenderer::OnInspectorGUI()
{
    if(ImGui::CollapsingHeader("Renderer"))
    {
        ImGui::Text(inspectorName.c_str());

        glm::vec3 position(m_model[3][0], m_model[3][1], m_model[3][2]);
        if(ImGui::InputFloat3("Position###LineRenderer_position", &position[0], 3))
        {
            SetPosition(position);
        }

        // Lines
        ImGui::BeginChild("");
        for(glm::vec3 const& vertex : m_lines)
        {
            // TODO : ImGui::InputFloat3()
        }
        ImGui::EndChild();

        ImGui::TextDisabled("\nVao : %u", m_vao);
        ImGui::TextDisabled("Vertex buffer ID  : %u", m_verticesObject);
    }
}

} // !namespace