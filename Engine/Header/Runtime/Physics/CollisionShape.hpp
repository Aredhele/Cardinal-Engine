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

/// \file       CollisionShape.hpp
/// \date       08/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Physics
/// \author     Ervan SILVERT


#ifndef CARDINAL_ENGINE_COLLISION_SHAPE_HPP
#define CARDINAL_ENGINE_COLLISION_SHAPE_HPP


#include <vector>

#include "Glm/glm/glm.hpp"
#include "btBulletDynamicsCommon.h"


namespace cardinal
{

class CollisionShape
{
    public:

        /// \brief Constructor of box shape
        CollisionShape(float mass);

        /// \brief Set mass
        void                SetMass(float mass);

        /// \brief Returns Local inertia
        glm::vec3           GetInertia(void) const;

        /// \brief Returns Current mass
        float               GetMass(void) const;

        /// \brief Return the inner shape
        btCollisionShape*   GetShape(void) const;

        /// \brief Destructor
        virtual ~CollisionShape();

    protected:
        btCollisionShape*   m_pShape            = nullptr;
        btScalar            m_inertia;
        float               m_mass              = 0;
};

/// \Brief Box Shape to represent a box collider
class BoxShape : public CollisionShape
{
    public:
    /// \brief Box Constructor
    BoxShape(glm::vec3 halfExtends, float mass);

    protected:
    glm::vec3 m_halfExtents;
};


/// \brief Shpere Shape to represent a shpere collider
class SphereShape : public CollisionShape
{
public:
    /// \brief Constructor
    SphereShape(float radius, float mass);

protected:
    float m_radius;
};

/// \brief Shpere Shape to represent a shpere collider
class CapsuleShape : public CollisionShape
{
public:
    /// \brief Constructor
    CapsuleShape(float radius, float height, float mass);

protected:
    float m_radius;
    float m_height;
};



/// \brief Vertex Shape to represent any collider
class VertexShape : public CollisionShape
{
public:
    /// \brief Constructor
    VertexShape(float mass);
    
    /// \biref Set triangle of collision shapes
    void SetTriangles(std::vector<glm::vec3> const&);
    
    /// \brief Destructors
    ~VertexShape() override;

protected:
    btTriangleMesh         * m_triangleMesh;
};

}

#endif // !CARDINAL_ENGINE_COLLISION_SHAPE_HPP