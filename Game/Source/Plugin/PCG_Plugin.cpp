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

/// \file       PCG_Plugin.cpp
/// \date       26/02/2018
/// \project    Cardinal Engine
/// \package    Plugin
/// \author     Vincent STEHLY--CALISTO

// Engine
#include "Runtime/Sound/SoundEngine.hpp"
#include "Runtime/Sound/Listener/AudioListener.hpp"

#include "Runtime/Rendering/Lighting/Lighting.hh"
#include "Runtime/Rendering/Particle/ParticleSystem.hpp"
#include "Runtime/Rendering/Particle/EmissionShape/Cone.hpp"
#include "Runtime/Rendering/Particle/EmissionShape/Plane.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/Mirror.hpp"

#include "Runtime/Rendering/Debug/Debug.hpp"

#include "ImGUI/imgui.h"

// Game
#include "Plugin/PCG_Plugin.hpp"
#include "World/Generator/BasicWorldGenerator.hpp"

/* static */ PCG_Plugin * PCG_Plugin::s_pPlugin = nullptr;

/// \brief Hook to register user plugin from the static libraries
void OnPluginRegistration()
{
    ASSERT_NULL(PCG_Plugin::s_pPlugin);

    // Creating a new pcg plugin instance
    PCG_Plugin::s_pPlugin = new PCG_Plugin();

    // Finally registering the plugin into the engine
    cardinal::PluginManager::RegisterPlugin(PCG_Plugin::s_pPlugin);
}

/// \brief Constructor
PCG_Plugin::PCG_Plugin() : m_generatorGui(), m_worldGenerator()
{
    m_pWorld = nullptr;
}

/// \brief Called when the game begins
void PCG_Plugin::OnPlayStart()
{
    // Configure engine here
    // Lighting
    cardinal::LightManager::CreateDirectionalLight();
    //cardinal::LightManager::GetDirectionalLight()->SetPosition(glm::vec3(525.0f, 20.0f, 307.0f));
    cardinal::LightManager::GetDirectionalLight()->SetPosition(glm::vec3(128.0f, 128.0f, 300.0f));
    cardinal::LightManager::GetDirectionalLight()->SetDirection(glm::vec3(-0.5f, -0.5f, -0.5f));

    // Gizmos
    cardinal::DebugManager::EnableGizmo(cardinal::DebugManager::EGizmo::DirectionalLight);
    cardinal::DebugManager::EnableGizmo(cardinal::DebugManager::EGizmo::Cone);
    cardinal::DebugManager::EnableGizmo(cardinal::DebugManager::EGizmo::Grid);
    cardinal::DebugManager::EnableGizmo(cardinal::DebugManager::EGizmo::Axis);
    cardinal::DebugManager::EnableGizmo(cardinal::DebugManager::EGizmo::PointLight);

    // Post-processing
    cardinal::RenderingEngine::SetPostProcessingActive(true);
    cardinal::PostProcessingStack * pStack = cardinal::RenderingEngine::GetPostProcessingStack();
    pStack->SetEffectActive(cardinal::PostEffect::FXAA, true);

    cardinal::Camera * pCamera = cardinal::RenderingEngine::GetMainCamera();
    pCamera->SetPosition (glm::vec3(189.0f, 23.0f, 193.0f));
    pCamera->SetDirection(glm::vec3(0.371f, 0.917f, 0.0143f));
    pCamera->LookAt      (glm::vec3(257.0f, 194.0f, 193.0f));

    // VR
    // cardinal::RenderingEngine::InitializeStereoscopicRendering();
    // m_pHMD = cardinal::RenderingEngine::GetHMD();
    // ASSERT_NOT_NULL(m_pHMD);

    // Setting up the game
    m_pWorld = m_worldGenerator.generateWorld();

    // Camera and Character
    m_cameraManager.SetCamera(cardinal::RenderingEngine::GetMainCamera());
    m_cameraManager.SetCharacter(&m_character);
    m_character.SetPosition(glm::vec3(100,100,2200));
    m_character.AttachCamera(m_cameraManager.GetCamera());

    // Particle system
    /// cardinal::ParticleSystem * pSystem = cardinal::RenderingEngine::AllocateParticleSystem();
    /// pSystem->Initialize(200000, 5000, 3.0f, 0.5f, 30.0f, glm::vec3(0.0f, 0.0f, -13.0f), glm::vec3(1.0f), new cardinal::Cone(4.0f, 2.0f));
    /// pSystem->SetPosition(glm::vec3(-10.0f, -1.0f, 0.0f));

    /// cardinal::PointLight * pLight = cardinal::LightManager::AllocatePointLight();
    /// pLight->SetPosition(glm::vec3(100.0f, 20.0f, 300.0f));
    /// pLight->SetRange(20);
    /// pLight->SetIntensity(1.0f);
    /// pLight->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
}

/// \brief Called when the game stops
void PCG_Plugin::OnPlayStop()
{

}

/// \brief Called just before the engine update
void PCG_Plugin::OnPreUpdate()
{
    // TODO
}

/// \brief Called after the engine update
/// \param dt The elapsed time in seconds
void PCG_Plugin::OnPostUpdate(float dt)
{
    m_character.Update(cardinal::RenderingEngine::GetWindow(), dt);
    m_cameraManager.Update(cardinal::RenderingEngine::GetWindow(), dt);

    cardinal::Camera * pCamera = cardinal::RenderingEngine::GetMainCamera();
}

/// \brief Called when it's time to render the GUI
void PCG_Plugin::OnGUI()
{
    static bool a = true;
    //ImGui::ShowDemoWindow(&a);
    m_generatorGui.setGenerator(&m_worldGenerator);
    m_generatorGui.drawGUI(&a);
    // TODO
}
