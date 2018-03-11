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

/// \file       ParticleSystem.cpp
/// \date       10/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Particle
/// \author     Vincent STEHLY--CALISTO

#include "Runtime/Core/Assertion/Assert.hh"
#include "Runtime/Rendering/Debug/Debug.hpp"
#include "Runtime/Rendering/Particle/ParticleSystem.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
ParticleSystem::ParticleSystem()
{
    m_pParticles       = nullptr;
    m_pEmissionShape   = nullptr;
    m_particleAmount   = 0;
    m_lastUsedParticle = 0;
    m_emissionRate     = 0;
    m_speed            = 1.0f;
    m_size             = 1.0f;
    m_lifeTime         = 0.0f;
    m_gravity          = glm::vec3(0.0f, 0.0f, -9.81);
    m_color            = glm::vec3(1.0f, 1.0f, 1.0f);
    m_position         = glm::vec3(0.0f);
}

/// \brief Destructor
ParticleSystem::~ParticleSystem() // NOLINT
{
    delete[] m_pParticles;
}

/// \brief Initializes the particle system
/// \param maxParticles The max amount of particles
/// \param emissionRate The number of particle to emit / s
/// \param lifeTime The life time of a particle in s
/// \param size The size of a particle
/// \param speed The start speed of a particle
/// \param gravity The gravity vector
/// \param color The color of particle
/// \param emissionShape The emission shape
void ParticleSystem::Initialize(int maxParticles, int emissionRate, float lifeTime, float size,  float speed, glm::vec3 const& gravity, glm::vec3 const& color, EmissionShape * pEmissionShape)
{
    m_particleAmount = maxParticles;
    m_pParticles     = new Particle[m_particleAmount];
    m_emissionRate   = emissionRate;
    m_lifeTime       = lifeTime;
    m_size           = size;
    m_gravity        = gravity;
    m_color          = color;
    m_speed          = speed;
    m_pEmissionShape = pEmissionShape;

    ASSERT_NOT_NULL(m_pEmissionShape);

    for(int i = 0; i < m_particleAmount; ++i)
    {
        m_pParticles[i].lifeTime = 0.0f;
    }

    m_renderer.Initialize(m_particleAmount);
    m_renderer.SetShader(&m_shader);
}

/// \brief Updates billboards
/// \param dt The elapsed time
void ParticleSystem::Update(float dt)
{
    int particleToEmit = (int)(dt * (float)m_emissionRate); // NOLINT

    // Emitting
    for(int i = 0; i < particleToEmit; ++i)
    {
        int index                 = GetNewParticle();
        Particle& currentParticle = m_pParticles[index];

        currentParticle.size     = m_size;
        currentParticle.lifeTime = m_lifeTime;
        currentParticle.position = m_pEmissionShape->GetStartPosition(m_position);
        currentParticle.color    = m_color;
        currentParticle.velocity = m_pEmissionShape->GetDirection(currentParticle.position) * m_speed;
    }

    // Simulate all particles
    int particlesCount = 0;
    for(int i = 0; i < m_particleAmount; i++)
    {
        Particle& currentParticle = m_pParticles[i];

        if(currentParticle.lifeTime > 0.0f)
        {
            // Decrease life
            currentParticle.lifeTime -= dt;
            if (currentParticle.lifeTime > 0.0f)
            {
                // Simple physics : gravity only, no collisions
                currentParticle.velocity += m_gravity * dt;
                currentParticle.position += currentParticle.velocity * dt;

                // Fill the GPU buffer
                m_renderer.billboardPositionBuffer[particlesCount * 4 + 0] = currentParticle.position.x;
                m_renderer.billboardPositionBuffer[particlesCount * 4 + 1] = currentParticle.position.y;
                m_renderer.billboardPositionBuffer[particlesCount * 4 + 2] = currentParticle.position.z;
                m_renderer.billboardPositionBuffer[particlesCount * 4 + 3] = currentParticle.size;

                m_renderer.billboardColorBuffer[particlesCount * 3 + 0] = currentParticle.color.x;
                m_renderer.billboardColorBuffer[particlesCount * 3 + 1] = currentParticle.color.y;
                m_renderer.billboardColorBuffer[particlesCount * 3 + 2] = currentParticle.color.z;
            }

            particlesCount++;
        }
    }

    // Update renderer
    m_renderer.SetElementCount(particlesCount);
    m_renderer.UpdateBuffer();

    if(m_pEmissionShape)
        m_pEmissionShape->DrawGizmo(m_position);
}

/// \brief Finds and returns a new particle
int ParticleSystem::GetNewParticle()
{
    for(int i = m_lastUsedParticle; i < m_particleAmount; i++)
    {
        if (m_pParticles[i].lifeTime <= 0.0f)
        {
            m_lastUsedParticle = i;
            return i;
        }
    }

    // The linear search failed from the last used particle index
    // Restarting
    for(int i = 0; i < m_lastUsedParticle; i++)
    {
        if (m_pParticles[i].lifeTime <= 0.0f)
        {
            m_lastUsedParticle = i;
            return i;
        }
    }

    // Not enough particles ...
    return 0;
}

/// \brief Sets the position of the particle system
/// \param position The new position
void ParticleSystem::SetPosition(glm::vec3 const& position)
{
    m_position = position;
}

} // !namespace