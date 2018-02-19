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

/// \file       PhysicsEngine.hpp
/// \date       19/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Physics
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_PHYSICS_ENGINE_HPP__
#define CARDINAL_ENGINE_PHYSICS_ENGINE_HPP__

#include "Glm/glm/glm.hpp"
#include "btBulletDynamicsCommon.h"

/// \namespace cardinal
namespace cardinal
{

/// \class PhysicsEngine
/// \brief Encapsulates Bullet3 physics
class PhysicsEngine
{
public:

    /// \brief TODO
    void Initialize(glm::vec3 const& gravity);

    /// \brief TODO
    void Shutdown();

public:

    /// \brief TODO
    static btRigidBody * AllocateRigidbody();

    /// \brief TODO
    static void ReleaseRigidbody(btRigidBody *& pBody);

private:

    static PhysicsEngine * s_pInstance;

private:

    btDynamicsWorld                     * m_pDynamicWorld;
    btBroadphaseInterface               * m_pBroadphaseInterface;
    btCollisionDispatcher               * m_pCollisionDispatcher;
    btDefaultCollisionConfiguration     * m_pCollisionCongifuration;
    btSequentialImpulseConstraintSolver * m_pSequentialConstraintSolver;
};

} // !namespace

#endif // !CARDINAL_ENGINE_PHYSICS_ENGINE_HPP__

