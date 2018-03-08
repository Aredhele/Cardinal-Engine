#include "Runtime/Physics/CollisionShape.hpp"

namespace cardinal
{

/// \bief Constructor
CollisionShape::CollisionShape(float mass) : 
    m_mass(mass)
{
}

/// \brief Set the shape mass
void CollisionShape::SetMass(float mass)
{
    m_mass = mass;
}


/// \brief Returns Local inertia
glm::vec3 CollisionShape::GetInertia(void) const
{
    btVector3 inertia;
    m_pShape->calculateLocalInertia(m_mass, inertia);

    return glm::vec3( inertia.x(), inertia.y(), inertia.z() );
}

/// \brief Returns Current mass
float CollisionShape::GetMass(void) const
{
    return m_mass;
}
/// \brief Return the inner shape
btCollisionShape* CollisionShape::GetShape(void) const
{
    return m_pShape;
}

/// \bief Destrucotr
CollisionShape::~CollisionShape(void)
{
    delete m_pShape;
}



/// \Brief Box Shape to represent a box collider
BoxShape::BoxShape(glm::vec3 halfExtents, float mass) :
    CollisionShape(mass),
    m_halfExtents(halfExtents)
{
    m_pShape = new btBoxShape(btVector3(halfExtents.x, halfExtents.y, halfExtents.z));
}

/// \brief Vertex Shape to represent any collider
SphereShape::SphereShape(float radius, float mass) :
    CollisionShape(mass),
    m_radius(radius)
{
    m_pShape = new btSphereShape(radius);
}

/// \brief Vertex Shape to represent any collider
VertexShape::VertexShape(float mass) :
    CollisionShape(mass)
{
    //m_pShape = new btBoxShape(btvector3(halfExtents.x, halfExtents.y, halfExtents.z));
}
}