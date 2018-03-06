#include "Runtime/Physics/RigidBody.hpp"

namespace cardinal
{

/// \brief Constructor
RigidBody::RigidBody(btDynamicsWorld* world, btCollisionShape* shape, glm::vec3 const& position, glm::vec4 const& rotation, float mass, glm::vec3 const& fallInertia) :
    m_rotation(rotation),
    m_mass(mass),
    m_pWorld(world),
    m_pShape(shape)
{
    // Build default motion state
    m_pMotionState = new btDefaultMotionState(
            btTransform(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w), 
            btVector3(position.x, position.y, position.z))
        );

    // Build rigid body info
    btRigidBody::btRigidBodyConstructionInfo
        groundRigidBodyCI(btScalar(mass), m_pMotionState, m_pShape, btVector3(fallInertia.x, fallInertia.y, fallInertia.z));

    // Build the rigid body
    m_pBody = new btRigidBody(groundRigidBodyCI);
//
//m_pMotionState =
//        new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 50, 0)));
//btScalar bmass = 1;
//    btVector3 bfallInertia(0, 0, 0);
//    m_pShape = new btSphereShape(1);
//    m_pShape->calculateLocalInertia(mass, bfallInertia);
//    btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(bmass, m_pMotionState, m_pShape, bfallInertia);
//    m_pBody = new btRigidBody(fallRigidBodyCI);
    
}

/// \brief Translate the physical body
void RigidBody::Translate(glm::vec3 const& translate)
{
    m_pBody->translate( btVector3(translate.x, translate.y, translate.z));
}

/// \brief Set body position
void RigidBody::SetPosition(glm::vec3 const& position)
{
    btTransform initialTransform;

    initialTransform.setOrigin( btVector3(position.x, position.y, position.z));
    initialTransform.setRotation( btQuaternion(m_rotation.x, m_rotation.y, m_rotation.z, m_rotation.w));

    m_pBody->setWorldTransform(initialTransform);
    m_pMotionState->setWorldTransform(initialTransform);
}

/// \brief Get body position
glm::vec3 RigidBody::GetPosition(void) const
{
    btVector3 pos = m_pBody->getWorldTransform().getOrigin();
    return glm::vec3(pos.x(), pos.y(), pos.z());
}

/// \brief Destructor
RigidBody::~RigidBody(void)
{
    delete m_pMotionState;
    delete m_pBody;
}

}