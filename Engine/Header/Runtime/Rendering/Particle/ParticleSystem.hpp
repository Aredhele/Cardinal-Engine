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
#include "Runtime/Rendering/Particle/EmissionShape/EmissionShape.hpp"
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
        float lifeTime;
    };

public:

    /// \brief Initializes the particle system
    /// \param maxParticles The max amount of particles
    /// \param emissionRate The number of particle to emit / s
    /// \param lifeTime The life time of a particle in s
    /// \param size The size of a particle
    /// \param speed The start speed of a particle
    /// \param gravity The gravity vector
    /// \param color The color of particle
    /// \param emissionShape The emission shape
    void Initialize(int maxParticles, int emissionRate, float lifeTime, float size, float speed, glm::vec3 const& gravity, glm::vec3 const& color, EmissionShape * pEmissionShape);

    /// \brief Sets the position of the particle system
    /// \param position The new position
    void SetPosition(glm::vec3 const& position);

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
    EmissionShape *  m_pEmissionShape;
    glm::vec3        m_gravity;
    glm::vec3        m_color;
    glm::vec3        m_position;
    int              m_lastUsedParticle;
    int              m_particleAmount;
    int              m_emissionRate;
    float            m_lifeTime;
    float            m_size;
    float            m_speed;
};

} // !namespace

#endif // !CARDINAL_ENGINE_PARTICLE_SYSTEM_HPP__