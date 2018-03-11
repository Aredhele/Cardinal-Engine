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

#include "Runtime/Rendering/Particle/ParticleSystem.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
ParticleSystem::ParticleSystem()
{
    m_pParticles       = nullptr;
    m_particleAmount   = 0;
    m_lastUsedParticle = 0;
    m_emissionRate     = 0;
    m_lifeTime         = 0.0f;
}

/// \brief Destructor
ParticleSystem::~ParticleSystem() // NOLINT
{
    delete[] m_pParticles;
}

/// \brief None
void ParticleSystem::Initialize()
{
    m_pParticles     = new Particle[100000];
    m_particleAmount = 100000;
    m_emissionRate   = 100;
    m_lifeTime       = 6.0f;
    m_size           = 10.0f;

    for(int i = 0; i < m_particleAmount; ++i)
    {
        m_pParticles[i].lifeTime = 0.0f;
        m_pParticles[i].color    = glm::vec3(1.0f, 1.0f, 1.0f);
    }

    m_renderer.Initialize(100000);
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
        int index = GetNewParticle();
        Particle& currentParticle = m_pParticles[index];

        float spread = 2.5f;
        glm::vec3 randDir = glm::vec3(
                (rand() % 2000 - 1000.0f) / 1000.0f,  // NOLINT
                (rand() % 2000 - 1000.0f) / 1000.0f,  // NOLINT
                (rand() % 2000 - 1000.0f) / 1000.0f); // NOLINT

        glm::vec3 randColor = glm::vec3(
                (rand() % 1000) / 1000.0f,  // NOLINT
                (rand() % 1000) / 1000.0f,  // NOLINT
                (rand() % 1000) / 1000.0f); // NOLINT

        currentParticle.size     = m_size;
        currentParticle.lifeTime = m_lifeTime;
        currentParticle.position = glm::vec3(0.0f, 0.0f, 0.0f);
        currentParticle.color    = randColor;
        currentParticle.velocity = glm::vec3(0.0f, 0.0f, 20.0f) + randDir * spread;
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
                currentParticle.velocity += glm::vec3(0.0f, 0.0f, -9.81f) * dt;
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

} // !namespace