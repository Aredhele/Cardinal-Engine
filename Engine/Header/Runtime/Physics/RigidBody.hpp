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
/// \date       05/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Physics
/// \author     Ervan SILVERT

#ifndef CARDINAL_ENGINE_RIGIDBODY_HPP
#define CARDINAL_ENGINE_RIGIDBODY_HPP

#include "Glm/glm/glm.hpp"
#include "btBulletDynamicsCommon.h"

namespace cardinal
{
/// \class RigidBody
/// \brief Encapsulates bullet3 RigidBody class
class RigidBody 
{
public:

    /// \brief Constructor
    RigidBody(btDynamicsWorld* world, btCollisionShape* shape, glm::vec3 const& position, glm::vec4 const& rotation, float mass, glm::vec3 const& fallInertia = glm::vec3(0,0,0));

    /// \brief Translate the physical body
    void Translate(glm::vec3 const& translate);

    /// \brief Set body position
    void SetPosition(glm::vec3 const& position);

    /// \brief Get body position
    glm::vec3 GetPosition(void) const;

    /// \brief Destructor
    virtual ~RigidBody(void);

protected:
friend class PhysicsEngine;

    inline btRigidBody* GetBody(void) const
    {return m_pBody;}

    glm::vec4               m_rotation;
    float                   m_mass;

    btDynamicsWorld         * m_pWorld          = nullptr;
    btRigidBody             * m_pBody           = nullptr;
    btCollisionShape        * m_pShape          = nullptr;
    btDefaultMotionState    * m_pMotionState    = nullptr;

};



} // !cardinal

#endif // ! CARDINAL_ENGINE_RIGIDBODY_HPP