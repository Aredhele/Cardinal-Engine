#include "Runtime/Physics/CollisionShape.hpp"

#include "Runtime/Core/Assertion/Assert.hh"

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
CapsuleShape::CapsuleShape(float radius, float height, float mass) :
    CollisionShape(mass),
    m_radius(radius),
    m_height(height)
{
    m_pShape = new btCapsuleShape(radius, height);
}

/// \brief Vertex Shape to represent any collider
VertexShape::VertexShape(float mass) :
    CollisionShape(mass)
{
   m_triangleMesh   = new btTriangleMesh();
}

void VertexShape::SetTriangles(std::vector<glm::vec3>& const verteces )
{
    ASSERT_NOT_NULL(m_triangleMesh);

    size_t size = verteces.size();

    for (size_t i = 0ul; i < size; i += 3)
    {
        m_triangleMesh->addTriangle( 
            btVector3(verteces[i].x, verteces[i].y, verteces[i].z),
            btVector3(verteces[i + 1].x, verteces[i+ 1].y, verteces[i+ 1].z),
            btVector3(verteces[i + 2].x, verteces[i+ 2].y, verteces[i+ 2].z)
            );
    }
    
    if (m_pShape != nullptr)
    {
        delete m_pShape;
    }

    m_pShape = new btBvhTriangleMeshShape(m_triangleMesh, true, true);
}

VertexShape::~VertexShape(void)
{
    CollisionShape::~CollisionShape();

    delete m_triangleMesh;
}

}