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

/// \file       Character.cpp
/// \date       16/02/2018
/// \project    Cardinal Engine
/// \package    Character
/// \author     Vincent STEHLY--CALISTO


#include <World/Cube/ByteCube.hpp>
#include <World/Cube/UVManager.hpp>
#include <Header/Runtime/Rendering/Optimization/VBOIndexer.hpp>
#include <Header/Runtime/Rendering/Texture/TextureManager.hpp>
#include <Header/Runtime/Physics/PhysicsEngine.hpp>
#include <Header/Runtime/Physics/CollisionShape.hpp>
#include <Header/Runtime/Physics/RigidBody.hpp>
#include <World/WorldSettings.hpp>
#include "Character/Character.hpp"
#include "Runtime/Rendering/Camera/Camera.hpp"
#include "Runtime/Rendering/Context/Window.hpp"
#include "Runtime/Rendering/RenderingEngine.hpp"
#include "Runtime/Rendering/Shader/Built-in/Unlit/UnlitTextureShader.hpp"
#include "Runtime/Core/Debug/Logger.hpp"

/// \brief Constructor
Character::Character()
{
    // Visual
    InitializeAvatar();

    // Physics
    m_pBody = cardinal::PhysicsEngine::AllocateRigidbody();

    m_pBody->SetShape       ( new cardinal::BoxShape(glm::vec3(2, 2, 2), 45));
    m_pBody->BuildPhysics   ();

    m_pBody->SetPosition    ( glm::vec3(0, 0, 0));
    m_pBody->SetRotation    ( glm::vec4(0, 0, 0, 1));
    
    cardinal::PhysicsEngine::AddRigidbody(m_pBody);
}

/// \brief Updates the character
/// \param pWindow The context
/// \param dt The elapsed time
void Character::Update(cardinal::Window * pWindow, float dt)
{
    // Camera debug controls
    glm::vec3 velocity(0, 0, m_pBody->GetLinearVelocity().z);

    if (glfwGetKey(pWindow->GetContext(), GLFW_KEY_W) == GLFW_PRESS) velocity += ( m_pCamera->GetDirection() * dt * m_speed * m_speedMultiplier);
    if (glfwGetKey(pWindow->GetContext(), GLFW_KEY_S) == GLFW_PRESS) velocity += (-m_pCamera->GetDirection() * dt * m_speed * m_speedMultiplier);
    if (glfwGetKey(pWindow->GetContext(), GLFW_KEY_D) == GLFW_PRESS) velocity += ( m_pCamera->GetRight() * dt * m_speed * m_speedMultiplier);
    if (glfwGetKey(pWindow->GetContext(), GLFW_KEY_A) == GLFW_PRESS) velocity += (-m_pCamera->GetRight() * dt * m_speed * m_speedMultiplier);
    m_pBody->SetLinearVelocity(velocity);
    cardinal::Logger::LogInfo("Velocity = %f,%f,%f", velocity.x, velocity.y, velocity.z);


}

/// \brief Returns the position of the avatar
glm::vec3 Character::GetPosition() const
{
   return m_pBody->GetPosition();
}

/// \brief Sets the position of the avatar
void Character::SetPosition(glm::vec3 position)
{
    m_pBody->SetPosition(position);
    m_meshRenderer->SetPosition(position);
}

/// \brief Sets the position of the avatar
void Character::AttachCamera(const cardinal::Camera* camera)
{
    m_pCamera = camera;
}


/// \brief Translate the avatar
/// \param translation The translation vector
void Character::Translate(const glm::vec3 &translation)
{
    m_pBody->Translate(translation);
    m_meshRenderer->Translate(translation);
}

/// \brief Initializes the avatar mesh
void Character::InitializeAvatar()
{
    m_meshRenderer = cardinal::RenderingEngine::AllocateMeshRenderer();
    cardinal::UnlitTextureShader * pShader = new cardinal::UnlitTextureShader(); // NOLINT
    pShader->SetTexture(cardinal::TextureManager::GetTextureID("Block"));
    m_meshRenderer->SetShader(pShader);

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> uvs;

    for(size_t nVertex = 0; nVertex < 36; ++nVertex)
    {
        vertices.emplace_back(
            ByteCube::s_vertices[nVertex * 3 + 0] * 2.0f,
            ByteCube::s_vertices[nVertex * 3 + 1] * 2.0f,
            ByteCube::s_vertices[nVertex * 3 + 2] * 2.0f);

        normals.emplace_back(
            ByteCube::s_normals[nVertex * 3 + 0],
            ByteCube::s_normals[nVertex * 3 + 1],
            ByteCube::s_normals[nVertex * 3 + 2]);
    }

    for(size_t nFace = 0; nFace < 6; ++nFace)
    {
        // Dirt cube
        float UVx = UVManager::UV[0][nFace * 2 + 0] * WorldSettings::s_textureStep;
        float UVy = UVManager::UV[0][nFace * 2 + 1] * WorldSettings::s_textureStep;

        uvs.emplace_back(UVx, UVy);
        uvs.emplace_back(UVx + WorldSettings::s_textureStep, UVy);
        uvs.emplace_back(UVx + WorldSettings::s_textureStep, UVy + WorldSettings::s_textureStep);
        uvs.emplace_back(UVx + WorldSettings::s_textureStep, UVy + WorldSettings::s_textureStep);
        uvs.emplace_back(UVx, UVy + WorldSettings::s_textureStep);
        uvs.emplace_back(UVx, UVy);
    }

    // Indexing
    std::vector<unsigned short> indexes;
    std::vector<glm::vec3>      indexedVertices;
    std::vector<glm::vec3>      indexedNormals;
    std::vector<glm::vec2>      indexedUVs;

    cardinal::VBOIndexer::Index(vertices, normals, uvs, indexes, indexedVertices, indexedNormals, indexedUVs);
    m_meshRenderer->Initialize(indexes, indexedVertices, indexedNormals, indexedUVs);
}