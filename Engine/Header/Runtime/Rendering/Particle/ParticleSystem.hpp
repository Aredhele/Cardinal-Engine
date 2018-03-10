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

/// \file       ParticleSystem.hpp
/// \date       08/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Particle
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_PARTICLE_SYSTEM_HPP__
#define CARDINAL_ENGINE_PARTICLE_SYSTEM_HPP__

#include "Glm/glm/vec3.hpp"
#include "Runtime/Platform/Configuration/Type.hh"
#include "Runtime/Rendering/Renderer/ParticleRenderer.hpp"
#include "Runtime/Rendering/Shader/Built-in/Particle/ParticleShader.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \class ParticleSystem
/// \brief System of basic particles
class ParticleSystem
{
private:

    struct Particle
    {
        glm::vec3 position;
        glm::vec3 velocity;
        glm::vec3 color;

        float size;
        float angle;
        float weight;
        float lifeTime;
    };

public:

    void Initialize();

private:

    friend class RenderingEngine;

    /// \brief Constructor
    ParticleSystem();

    /// \brief Destructor
    ~ParticleSystem();

    /// \brief Updates billboards
    /// \param dt The elapsed time
    void Update(float dt);

    /// \brief Finds and returns a new particle
    int GetNewParticle();

private:

    Particle *       m_pParticles;
    ParticleRenderer m_renderer;
    ParticleShader   m_shader;
    int              m_lastUsedParticle;
    int              m_particleAmount;
    int              m_emissionRate;
    float            m_lifeTime;
    float            m_size;
};

} // !namespace

#endif // !CARDINAL_ENGINE_PARTICLE_SYSTEM_HPP__