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

/// \brief Initializes the particle system with
///        the give amount of particles
void ParticleSystem::Initialize(uint64 amount)
{
    m_amount     = 0;
    m_pParticles = nullptr;

#ifdef CARDINAL_USE_GCC
    char * pBuffer = (char *)_mm_malloc(amount * sizeof(Particle), 8); // NOLINT
    m_pParticles = (Particle *)pBuffer; // NOLINT
    memset(m_pParticles, 0, amount * sizeof(Particle));

    m_amount = amount;
#endif
}

/// \brief Updates the particle system
/// \param dt The elapsed time
void ParticleSystem::Update(float dt)
{
#ifdef CARDINAL_USE_GCC
    __m128 gravity = _mm_set_ps(-9.81f * dt, -9.81f * dt, -9.81f * dt, -9.81f * dt);

    for(int i = 0; i < m_amount; i += 16)
    {
        __m128 v1 =  _mm_set_ps(m_pParticles[i +  0].velocity.z, m_pParticles[i +  1].velocity.z, m_pParticles[i +  2].velocity.z, m_pParticles[i +  3].velocity.z);
        __m128 v2 =  _mm_set_ps(m_pParticles[i +  4].velocity.z, m_pParticles[i +  5].velocity.z, m_pParticles[i +  6].velocity.z, m_pParticles[i +  7].velocity.z);
        __m128 v3 =  _mm_set_ps(m_pParticles[i +  8].velocity.z, m_pParticles[i +  9].velocity.z, m_pParticles[i + 10].velocity.z, m_pParticles[i + 11].velocity.z);
        __m128 v4 =  _mm_set_ps(m_pParticles[i + 12].velocity.z, m_pParticles[i + 13].velocity.z, m_pParticles[i + 14].velocity.z, m_pParticles[i + 15].velocity.z);

        __m128 r1 = _mm_add_ps(v1, gravity);
        __m128 r2 = _mm_add_ps(v2, gravity);
        __m128 r3 = _mm_add_ps(v3, gravity);
        __m128 r4 = _mm_add_ps(v4, gravity);

        float unit[16];

        _mm_store_ps(&unit[ 0], r1);
        _mm_store_ps(&unit[ 4], r2);
        _mm_store_ps(&unit[ 8], r3);
        _mm_store_ps(&unit[12], r4);

        m_pParticles[i +  0].velocity.z = unit[ 0];
        m_pParticles[i +  1].velocity.z = unit[ 1];
        m_pParticles[i +  2].velocity.z = unit[ 2];
        m_pParticles[i +  3].velocity.z = unit[ 3];
        m_pParticles[i +  4].velocity.z = unit[ 4];
        m_pParticles[i +  5].velocity.z = unit[ 5];
        m_pParticles[i +  6].velocity.z = unit[ 6];
        m_pParticles[i +  7].velocity.z = unit[ 7];
        m_pParticles[i +  8].velocity.z = unit[ 8];
        m_pParticles[i +  9].velocity.z = unit[ 9];
        m_pParticles[i + 10].velocity.z = unit[10];
        m_pParticles[i + 11].velocity.z = unit[11];
        m_pParticles[i + 12].velocity.z = unit[12];
        m_pParticles[i + 13].velocity.z = unit[13];
        m_pParticles[i + 14].velocity.z = unit[14];
        m_pParticles[i + 15].velocity.z = unit[15];
    }

#endif
}

} // !namespace