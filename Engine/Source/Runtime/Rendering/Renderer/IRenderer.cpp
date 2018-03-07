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

/// \file       IRenderer.cpp
/// \date       18/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Renderer
/// \author     Vincent STEHLY--CALISTO

#include "Runtime/Rendering/Renderer/IRenderer.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
IRenderer::IRenderer()
: m_vao(0)
, m_pShader(nullptr)
, m_elementsCount(0)
{
    m_model     = glm::mat4(1.0f);
    m_isIndexed = true;
}

/// \brief Returns the position of the renderer
glm::vec3 const &IRenderer::GetPosition() const
{
    return m_position;
}

/// \brief Returns the count of element to be draw
int IRenderer::GetElementCount() const
{
    return m_elementsCount;
}

} // !namespace