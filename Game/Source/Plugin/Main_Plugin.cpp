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

/// \file       Main_Plugin.cpp
/// \date       26/02/2018
/// \project    Cardinal Engine
/// \package    Plugin
/// \author     Vincent STEHLY--CALISTO

#include "Plugin/Main_Plugin.hpp"
#include "World/Generator/BasicWorldGenerator.hpp"

/* static */ Main_Plugin * Main_Plugin::s_pPlugin = nullptr;

/// \brief Hook to register user plugin from the static libraries
void OnPluginRegistration()
{
    ASSERT_NULL(Main_Plugin::s_pPlugin);

    // Creating a new main plugin instance
    Main_Plugin::s_pPlugin = new Main_Plugin();

    // Finally registering the plugin into the engine
    cardinal::PluginManager::RegisterPlugin(Main_Plugin::s_pPlugin);
}

/// \brief Constructor
Main_Plugin::Main_Plugin() : m_cameraManager()
{
    m_pWorld = nullptr;
}

/// \brief Called when the game begins
void Main_Plugin::OnPlayStart()
{
    // Configure engine here
    cardinal::DebugManager::EnableGizmo(cardinal::DebugManager::EGizmo::Grid);
    cardinal::DebugManager::EnableGizmo(cardinal::DebugManager::EGizmo::Axis);

    // Setting up the game
    BasicWorldGenerator bwg;
    m_pWorld = bwg.generateWorld();

    // Camera management
    m_cameraManager.SetCamera(cardinal::RenderingEngine::GetMainCamera());
    m_cameraManager.SetCharacter(&m_character);
}

/// \brief Called when the game stops
void Main_Plugin::OnPlayStop()
{
    // TODO
}

/// \brief Called just before the engine update
void Main_Plugin::OnPreUpdate()
{
    // TODO
}

/// \brief Called after the engine update
/// \param dt The elapsed time in seconds
void Main_Plugin::OnPostUpdate(float dt)
{
    // Character update
    m_character.Update(cardinal::RenderingEngine::GetWindow(), dt);

    // Camera manager update
    m_cameraManager.Update(cardinal::RenderingEngine::GetWindow(), dt);
}

/// \brief Called when it's time to render the GUI
void Main_Plugin::OnGUI()
{
    if (glfwGetKey(cardinal::RenderingEngine::GetWindow()->GetContext(), GLFW_KEY_F11) == GLFW_PRESS)
        m_debugWindow = !m_debugWindow;

    if (!m_debugWindow)
        return;

    // Game camera
    cardinal::Camera* pCamera = cardinal::RenderingEngine::GetMainCamera();

    // Debug window
    ImGui::SetNextWindowSize(ImVec2(300,150));
    ImGui::Begin("Camera Information");

    ImGui::Text(("Position :\t" + std::to_string((int)pCamera->GetPosition().x)     + "," + std::to_string((int)pCamera->GetPosition().y)   + "," + std::to_string((int)pCamera->GetPosition().z)   ).c_str() );
    ImGui::Text(("Direction:\t" + std::to_string(pCamera->GetDirection().x)         + "," + std::to_string(pCamera->GetDirection().y)       + "," + std::to_string(pCamera->GetDirection().z)       ).c_str() );
    ImGui::Text(("Character:\t" + std::to_string((int)m_character.GetPosition().x)  + "," + std::to_string((int)m_character.GetPosition().y)+ "," + std::to_string((int)m_character.GetPosition().z)).c_str() );

    ImGui::End();
}

