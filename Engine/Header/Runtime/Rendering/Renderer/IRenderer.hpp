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

/// \file       IRenderer.hpp
/// \date       18/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Renderer
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_I_RENDERER_HPP__
#define CARDINAL_ENGINE_I_RENDERER_HPP__

#include "Runtime/Rendering/Shader/IShader.hpp"
#include "Runtime/Platform/Configuration/Type.hh"

/// \namespace cardinal
namespace cardinal
{

/// \class IRenderer
/// \brief Base class for all renderers
class IRenderer
{
public:

    /// \brief Default constructor
    IRenderer();

    /// \brief Called to render the object
    /// \param PV The projection view matrix
    /// TODO
    virtual void Draw(glm::mat4 const& P, glm::mat4 const& V, glm::vec3 const& light, std::vector<PointLightStructure> const& pointLights) = 0;

    /// \brief Returns the position of the renderer
    glm::vec3 const& GetPosition() const;

    /// \brief Returns the count of element to be draw
    int GetElementCount() const;

protected:

    friend class RenderingEngine;

    uint      m_vao;            ///< All renderers have at least one vao
    IShader * m_pShader;        ///< All renderers have at least one shader
    glm::vec3 m_position;       ///< The position of the renderer
    glm::mat4 m_model;          ///< The model of the renderer
    int       m_elementsCount;  ///< The count of element to be draw
    bool      m_isIndexed;      ///< Tells if the renderer contains indexed data
    bool      m_isInstantiated; ///< Tells if the renderer contains instantiated data
};

} // !namespace

#endif // !CARDINAL_ENGINE_I_RENDERER_HPP__