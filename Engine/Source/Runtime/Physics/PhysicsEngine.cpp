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

/// \file       PhysicsEngine.cpp
/// \date       19/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Physics
/// \author     Vincent STEHLY--CALISTO

#include <chrono>

#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Core/Assertion/Assert.hh"
#include "Runtime/Physics/PhysicsEngine.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief TODO
bool PhysicsEngine::Initialize(glm::vec3 const& gravity)
{
    auto beginPhysicsInit = std::chrono::steady_clock::now();
    Logger::LogInfo("Initializing the physics engine ...");
    Logger::LogInfo("Initializing Bullet3 physics ...");

    m_pCollisionCongifuration     = new btDefaultCollisionConfiguration();
    m_pCollisionDispatcher        = new btCollisionDispatcher(m_pCollisionCongifuration);
    m_pBroadphaseInterface        = new btDbvtBroadphase();
    m_pSequentialConstraintSolver = new btSequentialImpulseConstraintSolver();

    m_pDynamicWorld = new btDiscreteDynamicsWorld(
            m_pCollisionDispatcher,
            m_pBroadphaseInterface,
            m_pSequentialConstraintSolver,
            m_pCollisionCongifuration);

    m_pDynamicWorld->setGravity(btVector3(gravity.x, gravity.y, gravity.z));

    auto endPhysicsInit = std::chrono::steady_clock::now();
    auto elapsed        = std::chrono::duration_cast<std::chrono::milliseconds>(endPhysicsInit - beginPhysicsInit);
    Logger::LogInfo("Bullet3 successfully initialized");
    Logger::LogInfo("Physics engine initialized in %d ms", elapsed);

    return true;
}

/// \brief TODO
void PhysicsEngine::Update()
{
    ASSERT_NOT_NULL(m_pDynamicWorld);
    m_pDynamicWorld->stepSimulation(1 / 60.0f, 1, 10);
}

/// \brief TODO
void PhysicsEngine::Shutdown()
{
    // TODO
}

/// \brief TODO
btRigidBody * PhysicsEngine::AllocateRigidbody()
{
    //  TODO
    return nullptr;
}

/// \brief TODO
void PhysicsEngine::ReleaseRigidbody(btRigidBody *&pBody)
{

}

} // !namespace
