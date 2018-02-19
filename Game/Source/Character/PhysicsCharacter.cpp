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

/// \file       PhysicsCharacter.cpp
/// \date       16/02/2018
/// \project    Cardinal Engine
/// \package    Character
/// \author     Vincent STEHLY--CALISTO


#include "World/Cube/ByteCube.hpp"
#include "World/Cube/UVManager.hpp"
#include "Header/Runtime/Rendering/Optimization/VBOIndexer.hpp"
#include "Header/Runtime/Rendering/Texture/TextureManager.hpp"
#include "World/WorldSettings.hpp"
#include "Character/PhysicsCharacter.hpp"
#include "Runtime/Rendering/Camera/Camera.hpp"
#include "Runtime/Rendering/Context/Window.hpp"
#include "Runtime/Rendering/RenderingEngine.hpp"
#include "Runtime/Rendering/Shader/Built-in/UnlitTextureShader.hpp"

/// \brief Constructor
PhysicsCharacter::PhysicsCharacter()
{
    m_pPositionText  = cardinal::RenderingEngine::AllocateTextRenderer();
    m_pDirectionText = cardinal::RenderingEngine::AllocateTextRenderer();

    m_pPositionText->Initialize();
    m_pDirectionText->Initialize();

    m_pPositionText->SetText( "Pos XYZ : 0.0f / 0.0f / 0.0f", 5, 500, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_pDirectionText->SetText("Dir XYZ : 0.0f / 0.0f / 0.0f", 5, 485, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    InitializeAvatar();
}

/// \brief Updates the character
/// \param pWindow The context
/// \param dt The elapsed time
void PhysicsCharacter::Update(cardinal::Window * pWindow, float dt)
{
    glm::tvec3<double> mouse;
    glm::tvec3<double> delta;
    glfwGetCursorPos(pWindow->GetContext(), &mouse.x, &mouse.y);

    delta = mouse - m_lastMouse;
    m_pCamera->Rotate  (static_cast<float>(-delta.x * m_sensitivity));
    m_pCamera->RotateUp(static_cast<float>(-delta.y * m_sensitivity));

    bool bFreeMouse = false;
    if(glfwGetKey(pWindow->GetContext(), GLFW_KEY_LEFT_ALT))
    {
        bFreeMouse = true;
    }

    glm::vec2 mousePos    (mouse.x, mouse.y);
    glm::vec2 windowSize  (1600.0f, 900.0f);
    glm::vec2 windowCenter(windowSize.x /2, windowSize.y / 2);

    float maxMousePosRadius = glm::min(windowSize.x, windowSize.y) / 2.0f;
    if (glm::distance(mousePos, windowCenter) > maxMousePosRadius)
    {
        if(!bFreeMouse)
        {
            glfwSetCursorPos(pWindow->GetContext(), windowCenter.x, windowCenter.y);
            m_lastMouse.x = windowCenter.x;
            m_lastMouse.y = windowCenter.y;
        }
    }
    else
    {
        m_lastMouse.x = mousePos.x;
        m_lastMouse.y = mousePos.y;
    }


    if(glfwGetKey(pWindow->GetContext(), GLFW_KEY_LEFT_SHIFT)) m_speedMultiplier = 2.0f;
    else                                                       m_speedMultiplier = 1.0f;

    // Camera debug controls
    if (glfwGetKey(pWindow->GetContext(), GLFW_KEY_W) == GLFW_PRESS) m_pCamera->Translate( m_pCamera->GetDirection() * dt * m_speed * m_speedMultiplier);
    if (glfwGetKey(pWindow->GetContext(), GLFW_KEY_S) == GLFW_PRESS) m_pCamera->Translate(-m_pCamera->GetDirection() * dt * m_speed * m_speedMultiplier);
    if (glfwGetKey(pWindow->GetContext(), GLFW_KEY_D) == GLFW_PRESS) m_pCamera->Translate( m_pCamera->GetRight() * dt * m_speed * m_speedMultiplier);
    if (glfwGetKey(pWindow->GetContext(), GLFW_KEY_A) == GLFW_PRESS) m_pCamera->Translate(-m_pCamera->GetRight() * dt * m_speed * m_speedMultiplier);

    // Avatar controls
    if (glfwGetKey(pWindow->GetContext(), GLFW_KEY_UP)            == GLFW_PRESS) Translate(glm::vec3( 1.0f,  0.0f,  0.0f) * dt * m_speed);
    if (glfwGetKey(pWindow->GetContext(), GLFW_KEY_DOWN)          == GLFW_PRESS) Translate(glm::vec3(-1.0f,  0.0f,  0.0f) * dt * m_speed);
    if (glfwGetKey(pWindow->GetContext(), GLFW_KEY_LEFT)          == GLFW_PRESS) Translate(glm::vec3( 0.0f, -1.0f,  0.0f) * dt * m_speed);
    if (glfwGetKey(pWindow->GetContext(), GLFW_KEY_RIGHT)         == GLFW_PRESS) Translate(glm::vec3( 0.0f,  1.0f,  0.0f) * dt * m_speed);
    if (glfwGetKey(pWindow->GetContext(), GLFW_KEY_SPACE)         == GLFW_PRESS) Translate(glm::vec3( 0.0f,  0.0f,  1.0f) * dt * m_speed);
    if (glfwGetKey(pWindow->GetContext(), GLFW_KEY_LEFT_CONTROL)  == GLFW_PRESS) Translate(glm::vec3( 0.0f,  0.0f, -1.0f) * dt * m_speed);

    std::string _pos = "Pos XYZ : " + std::to_string(m_pCamera->GetPosition().x) + " / " +
                       std::to_string(m_pCamera->GetPosition().y) + " / " +
                       std::to_string(m_pCamera->GetPosition().z);

    std::string _dir = "Dir  XYZ : " + std::to_string(m_pCamera->GetDirection().x) + " / " +
                       std::to_string(m_pCamera->GetDirection().y) + " / " +
                       std::to_string(m_pCamera->GetDirection().z);

    m_pPositionText->SetText ( _pos.c_str(), 5, 500, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_pDirectionText->SetText(_dir.c_str(), 5, 485, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

/// \brief Attaches a camera to the character
/// \param pCamera A pointer on the camera to attach
void PhysicsCharacter::AttachCamera(cardinal::Camera * pCamera)
{
    m_pCamera = pCamera;
}

/// \brief Returns the position of the avatar
glm::vec3 const &PhysicsCharacter::GetPosition() const
{
    return m_position;
}

/// \brief Translate the avatar
/// \param translation The translation vector
void PhysicsCharacter::Translate(const glm::vec3 &translation)
{
    m_position += translation;
    m_meshRenderer->Translate(translation);
}

/// \brief Initializes the avatar mesh
void PhysicsCharacter::InitializeAvatar()
{
    m_meshRenderer = cardinal::RenderingEngine::AllocateMeshRenderer();
    cardinal::UnlitTextureShader * pShader = new cardinal::UnlitTextureShader(); // NOLINT
    pShader->SetTexture(cardinal::TextureManager::GetTextureID("Block"));
    m_meshRenderer->SetShader(pShader);

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;

    for(size_t nVertex = 0; nVertex < 36; ++nVertex)
    {
        vertices.emplace_back(
                ByteCube::s_vertices[nVertex * 3 + 0] * 2.0f,
                ByteCube::s_vertices[nVertex * 3 + 1] * 2.0f,
                ByteCube::s_vertices[nVertex * 3 + 2] * 2.0f);
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
    std::vector<glm::vec2>      indexedUVs;

    cardinal::VBOIndexer::Index(vertices, uvs, indexes, indexedVertices, indexedUVs);
    m_meshRenderer->Initialize(indexes, indexedVertices, indexedUVs);

    m_position.x = 165.0f;
    m_position.y = 165.0f;
    m_position.z =  96.0f;

    m_meshRenderer->Translate(m_position);
}