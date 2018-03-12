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

/// \file       LineRenderer.hpp
/// \date       12/03/2018
/// \project    Cardinal Engine
/// \package    Rendering/Renderer
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_LINE_RENDERER_HPP__
#define CARDINAL_ENGINE_LINE_RENDERER_HPP__

#include <vector>
#include "Glm/glm/glm.hpp"
#include "Glm/glm/ext.hpp"

#include "Runtime/Rendering/Renderer/IRenderer.hpp"
#include "Runtime/Platform/Configuration/Configuration.hh"

/// \namespace cardinal
namespace cardinal
{

/// \class  LineRenderer
/// \brief  Renders lines
class LineRenderer : public IRenderer
{
public:

    /// \brief Default constructor
    LineRenderer();

    /// \brief Destructor
    ~LineRenderer();

    /// \brief Sets the position of the line renderer
    /// \param position The new position
    void SetPosition(glm::vec3 const &position);

    /// \brief Translates the model
    /// \param Translation The translation vector
    void Translate(glm::vec3 const &Translation);

    /// \brief Sets the renderer shader
    /// \param pShader The pointer on the shader
    void SetShader(IShader *pShader);

    /// \brief Clears all lines
    void Clear();

    /// \brief Adds a line to the renderer
    /// \param start The start point
    /// \param end The end point
    void AddLine(glm::vec3 const& start, glm::vec3 const& end);

    /// \brief Base method implementation
    /// \param PV The projection view matrix
    void Draw(glm::mat4 const& P, glm::mat4 const& V, glm::vec3 const& light, std::vector<PointLightStructure> const& pointLights) final;

    /// \brief Called when the object is inspected
    void OnInspectorGUI() final;

private:

    friend class RenderingEngine;

    std::vector<glm::vec3> m_lines;
    uint                   m_verticesObject;
    uint                   m_maxElement;
};

}  // !namespace

#endif // !CARDINAL_ENGINE_LINE_RENDERER_HPP__