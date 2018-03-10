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

/// \file       VR_Plugin.cpp
/// \date       10/03/2018
/// \project    Cardinal Engine
/// \package    Plugin
/// \author     Vincent STEHLY--CALISTO

// Engine
#include "Runtime/Rendering/Lighting/Lighting.hh"

// Game
#include "Plugin/VR_plugin.hpp"

/* static */ VR_Plugin * VR_Plugin::s_pPlugin = nullptr;

/// \brief Hook to register user plugin from the static libraries
void OnPluginRegistration()
{
    ASSERT_NULL(VR_Plugin::s_pPlugin);

    // Creating a new pcg plugin instance
    VR_Plugin::s_pPlugin = new VR_Plugin();

    // Finally registering the plugin into the engine
    cardinal::PluginManager::RegisterPlugin(VR_Plugin::s_pPlugin);
}

/// \brief Constructor
VR_Plugin::VR_Plugin()
{
    // None
}

/// \brief Called when the game begins
void VR_Plugin::OnPlayStart()
{
    // Configure engine here
    // Lighting
    cardinal::LightManager::CreateDirectionalLight();
    cardinal::LightManager::GetDirectionalLight()->SetPosition(glm::vec3(520.0f, 20.0f, 307.0f));
    cardinal::LightManager::GetDirectionalLight()->SetDirection(glm::vec3(-0.5f, -0.5f, -0.5f));

    // Post-processing
    cardinal::RenderingEngine::SetPostProcessingActive(true);

    // Gizmos
    cardinal::DebugManager::EnableGizmo(cardinal::DebugManager::EGizmo::DirectionalLight);
    cardinal::DebugManager::EnableGizmo(cardinal::DebugManager::EGizmo::Grid);
    cardinal::DebugManager::EnableGizmo(cardinal::DebugManager::EGizmo::Axis);

    // VR
    cardinal::RenderingEngine::InitializeStereoscopicRendering();
    m_pHMD = cardinal::RenderingEngine::GetHMD();
    ASSERT_NOT_NULL(m_pHMD);

    m_cameraManager.SetCamera(cardinal::RenderingEngine::GetMainCamera());
    m_cameraManager.SetCharacter(&m_character);

    m_building.Initialize();
    m_building.Generate();
    m_building.Batch();
}

/// \brief Called when the game stops
void VR_Plugin::OnPlayStop()
{
    // TODO
}

/// \brief Called just before the engine update
void VR_Plugin::OnPreUpdate()
{
    // TODO
}

/// \brief Called after the engine update
/// \param dt The elapsed time in seconds
void VR_Plugin::OnPostUpdate(float dt)
{
    m_character.Update(cardinal::RenderingEngine::GetWindow(), dt);
    m_cameraManager.Update(cardinal::RenderingEngine::GetWindow(), dt);

    vr::VREvent_t event {};
    while(m_pHMD->PollNextEvent(&event, sizeof(event)))
    {
        ProcessVREvent(event);
    }

    // Process SteamVR controller state
    for( vr::TrackedDeviceIndex_t unDevice = 0; unDevice < vr::k_unMaxTrackedDeviceCount; unDevice++ )
    {
        vr::VRControllerState_t state {};
        if( m_pHMD->GetControllerState( unDevice, &state, sizeof(state) ) )
        {
            // m_rbShowTrackedDevice[ unDevice ] = state.ulButtonPressed == 0;
        }
    }
}

/// \brief Called when it's time to render the GUI
void VR_Plugin::OnGUI()
{
    // None
}

/// \brief Process HMD events
void VR_Plugin::ProcessVREvent(vr::VREvent_t const& event)
{

}
