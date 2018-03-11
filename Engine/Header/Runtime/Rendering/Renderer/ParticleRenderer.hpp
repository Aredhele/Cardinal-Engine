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

/// \file       ParticleRenderer.hpp
/// \date       10/03/2018
/// \project    Cardinal Engine
/// \package    Rendering/Renderer
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_PARTICLE_RENDERER_HPP__
#define CARDINAL_ENGINE_PARTICLE_RENDERER_HPP__

#include <vector>
#include "Glm/glm/glm.hpp"
#include "Glm/glm/ext.hpp"

#include "Runtime/Rendering/Renderer/IRenderer.hpp"
#include "Runtime/Platform/Configuration/Configuration.hh"

/// \namespace cardinal
namespace cardinal
{

/// \class  ParticleRenderer
/// \brief  Renders instantiated particles
class ParticleRenderer : public IRenderer
{
public :

    /// \brief Default constructor
    ParticleRenderer();

    /// \brief Destructor
    ~ParticleRenderer();

    /// \brief Initializes the renderer
    /// \param particleAmount The max amount of particles
    void Initialize(int maxParticleAmount);

    /// \brief Sets the renderer shader
    /// \param pShader The pointer on the shader
    void SetShader(IShader * pShader);

    /// \brief Sets the currentElementCount
    void SetElementCount(int count);

    /// \brief Updates positions and color buffer
    void UpdateBuffer();

    /// \brief Base method implementation
    /// \param PV The projection view matrix
    void Draw(glm::mat4 const& P, glm::mat4 const& V, glm::vec3 const& light, std::vector<PointLightStructure> const& pointLights) final;

    /// \brief Called when the object is inspected
    void OnInspectorGUI() final;

    float * billboardColorBuffer;
    float * billboardPositionBuffer;

private:

    friend class RenderingEngine;

    uint m_billboardVertexBuffer;
    uint m_billboardPositionBuffer;
    uint m_billboardColorBuffer;
    uint m_maxParticleAmount;
};

}  // !namespace

#endif // !CARDINAL_ENGINE_PARTICLE_RENDERER_HPP__