#include "Runtime/Physics/RigidBody.hpp"
#include "Runtime/Core/Assertion/Assert.hh"

namespace cardinal
{

/// \brief Constructor
RigidBody::RigidBody(btDynamicsWorld* world) :
    m_pWorld(world)
{
}

/// \brief Translate the physical body
void RigidBody::Translate(glm::vec3 const& translate)
{
    ASSERT_TRUE_MSG(IsInitialized() == true, "You must build the inner physics first (RigidBody.buildPhysics())");

    m_pBody->translate( btVector3(translate.x, translate.y, translate.z));
}

/// \brief Set body position
void RigidBody::SetPosition(glm::vec3 const& position)
{
    ASSERT_NOT_NULL_MSG(m_pShape, "You must first give a shape to the rigid body.");

    btTransform initialTransform;
    btQuaternion rotation = m_pBody->getWorldTransform().getRotation();

    initialTransform.setOrigin( btVector3(position.x, position.y, position.z));
    initialTransform.setRotation( rotation );

    m_pBody->setWorldTransform( initialTransform );
    m_pMotionState->setWorldTransform( initialTransform );
}


/// \brief Set body rotation
void RigidBody::SetRotation(glm::vec4 const& rotation)
{
    ASSERT_NOT_NULL_MSG(m_pShape, "You must first give a shape to the rigid body.");

    btTransform initialTransform;
    btVector3   position = m_pBody->getWorldTransform().getOrigin();

    initialTransform.setOrigin(position);
    initialTransform.setRotation(btQuaternion(rotation.x, rotation.y, rotation.z, rotation.w));

    m_pBody->setWorldTransform(initialTransform);
    m_pMotionState->setWorldTransform(initialTransform);
}

/// \brief Set the body shape
void RigidBody::SetShape(CollisionShape* shape)
{
    m_pShape = shape;
}

/// \brief Set body mass
void RigidBody::SetMass(float mass)
{
    ASSERT_TRUE_MSG(IsInitialized() == true, "You must build the inner physics first (RigidBody.buildPhysics())");

    m_pShape->SetMass(mass);
    glm::vec3 inertia = m_pShape->GetInertia();
    m_pBody->setMassProps(mass, btVector3(inertia.x, inertia.y, inertia.z) );
}

/// \brief Set body gravity
void RigidBody::SetGravity(glm::vec3& const gravity)
{
    ASSERT_NOT_NULL(m_pBody);
    m_pBody->setGravity( btVector3(gravity.x, gravity.y, gravity.z) );
}

/// \brief Set body restitution
void RigidBody::SetRestitution(float coef)
{
    ASSERT_NOT_NULL(m_pBody);
    m_pBody->setRestitution(coef);
}

/// \brief Set velocity
void RigidBody::SetLinearVelocity(glm::vec3& const velocity)
{
    ASSERT_NOT_NULL(m_pBody);

    m_pBody->setLinearVelocity(btVector3(velocity.x, velocity.y, velocity.z));
}

/// \brief Set velocity
glm::vec3& const RigidBody::GetLinearVelocity(void)
{
    ASSERT_NOT_NULL(m_pBody);

    btVector3 vel = m_pBody->getLinearVelocity();
    return glm::vec3(vel.x(), vel.y(), vel.z());
}

/// \brief Build physics body and return true on success
void RigidBody::BuildPhysics(bool hasInertia)
{
    ASSERT_TRUE_MSG(IsInitialized() == false && m_pShape != nullptr, "You must first give the rigid body a shape.");

    m_pMotionState = new btDefaultMotionState();

    glm::vec3 inertia;
    if (hasInertia == true)
        inertia = m_pShape->GetInertia();

    m_pBody = new btRigidBody(m_pShape->GetMass(), m_pMotionState, m_pShape->GetShape(), btVector3(inertia.x, inertia.y, inertia.z));
}

/// \brief Returns true if the body is initialized
bool RigidBody::IsInitialized(void) const
{
    return m_pBody != nullptr;
}

/// \brief Get body position
glm::vec3 RigidBody::GetPosition(void) const
{
    ASSERT_TRUE_MSG(IsInitialized() == true, "You must build the inner physics first (RigidBody.buildPhysics())");

    btVector3 pos = m_pBody->getWorldTransform().getOrigin();
    return glm::vec3(pos.x(), pos.y(), pos.z());
}

/// \brief Set sleeping threshold
void RigidBody::SetSleepingThreshold(float linear, float angular)
{
    ASSERT_NOT_NULL(m_pBody);
    m_pBody->setSleepingThresholds(btScalar(linear), btScalar(angular));
}

/// \brief Destructor
RigidBody::~RigidBody(void)
{
    delete m_pMotionState;
    delete m_pBody;
}

}