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

#include "Character/Character.hpp"
#include "Runtime/Rendering/Camera/Camera.hpp"
#include "Runtime/Rendering/Context/Window.hpp"
#include "Runtime/Rendering/RenderingEngine.hpp"

/// \brief Constructor
Character::Character()
{
    m_pPositionText  = cardinal::RenderingEngine::AllocateTextRenderer();
    m_pDirectionText = cardinal::RenderingEngine::AllocateTextRenderer();

    m_pPositionText->Initialize();
    m_pDirectionText->Initialize();

    m_pPositionText->SetText( "Pos XYZ : 0.0f / 0.0f / 0.0f", 5, 500, 12);
    m_pDirectionText->SetText("Dir XYZ : 0.0f / 0.0f / 0.0f", 5, 485, 12);
}

/// \brief Updates the character
/// \param pWindow The context
/// \param dt The elapsed time
void Character::Update(cardinal::Window * pWindow, float dt)
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

    if (glfwGetKey(pWindow->GetContext(), GLFW_KEY_W) == GLFW_PRESS) m_pCamera->Translate( m_pCamera->GetDirection() * dt * m_speed * m_speedMultiplier);
    if (glfwGetKey(pWindow->GetContext(), GLFW_KEY_S) == GLFW_PRESS) m_pCamera->Translate(-m_pCamera->GetDirection() * dt * m_speed * m_speedMultiplier);
    if (glfwGetKey(pWindow->GetContext(), GLFW_KEY_D) == GLFW_PRESS) m_pCamera->Translate( m_pCamera->GetRight() * dt * m_speed * m_speedMultiplier);
    if (glfwGetKey(pWindow->GetContext(), GLFW_KEY_A) == GLFW_PRESS) m_pCamera->Translate(-m_pCamera->GetRight() * dt * m_speed * m_speedMultiplier);

    std::string _pos = "Pos XYZ : " + std::to_string(m_pCamera->GetPosition().x) + " / " +
                                      std::to_string(m_pCamera->GetPosition().y) + " / " +
                                      std::to_string(m_pCamera->GetPosition().z);

    std::string _dir = "Dir XYZ  : " + std::to_string(m_pCamera->GetDirection().x) + " / " +
                                       std::to_string(m_pCamera->GetDirection().y) + " / " +
                                       std::to_string(m_pCamera->GetDirection().z);

    m_pPositionText->SetText( _pos.c_str(), 5, 500, 12);
    m_pDirectionText->SetText(_dir.c_str(), 5, 485, 12);
}

/// \brief Attaches a camera to the character
/// \param pCamera A pointer on the camera to attach
void Character::AttachCamera(cardinal::Camera * pCamera)
{
    m_pCamera = pCamera;
}
