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

/// \file       Demo_Plugin.cpp
/// \date       15/03/2018
/// \project    Cardinal Engine
/// \package    Plugin
/// \author     Vincent STEHLY--CALISTO

#include "Plugin/Demo_Plugin.hpp"

#include "Runtime/Core/Plugin/PluginManager.hpp"
#include "Runtime/Rendering/Lighting/Lighting.hh"
#include "Runtime/Rendering/Debug/DebugManager.hpp"
#include "Runtime/Rendering/Particle/EmissionShape/Plane.hpp"

/* static */ Demo_Plugin * Demo_Plugin::s_pPlugin = nullptr;

void OnPluginRegistration()
{
    ASSERT_NULL(Demo_Plugin::s_pPlugin);
    Demo_Plugin::s_pPlugin = new Demo_Plugin();

    cardinal::PluginManager::RegisterPlugin(Demo_Plugin::s_pPlugin);
}

void Demo_Plugin::OnPlayStart()
{
    cardinal::Camera * pCamera = cardinal::RenderingEngine::GetMainCamera();
    pCamera->SetPosition(glm::vec3(189.0f, 23.0f, 193.0f));
    pCamera->SetDirection(glm::vec3(0.37f, 0.91f, 0.01f));
    pCamera->LookAt(glm::vec3(257.0f, 194.0f, 193.0f));

    cardinal::LightManager::CreateDirectionalLight();
    cardinal::LightManager::GetDirectionalLight()->SetPosition(glm::vec3(128.0f, 128.0f, 300.0f));
    cardinal::LightManager::GetDirectionalLight()->SetDirection(glm::vec3(-0.5f, -0.5f, -0.5f));

    cardinal::DebugManager::EnableGizmo(cardinal::DebugManager::EGizmo::DirectionalLight);
    cardinal::DebugManager::EnableGizmo(cardinal::DebugManager::EGizmo::Grid);
    cardinal::DebugManager::EnableGizmo(cardinal::DebugManager::EGizmo::Axis);
    cardinal::DebugManager::EnableGizmo(cardinal::DebugManager::EGizmo::Cone);

    cardinal::RenderingEngine::SetPostProcessingActive(true);
    cardinal::PostProcessingStack * pPostProcessingStack = cardinal::RenderingEngine::GetPostProcessingStack();
    pPostProcessingStack->SetEffectActive(cardinal::PostEffect::EType::FXAA, true);

    m_pSystem = cardinal::RenderingEngine::AllocateParticleSystem();
    m_pSystem->Initialize(200000, 5000, 10.0f, 0.5f, 0.0f, glm::vec3(0.0f, 0.0f, -13.0f), glm::vec3(1.0f), new cardinal::Plane(512.0f, 512.0f));
    m_pSystem->SetPosition(glm::vec3(0.0f, 0.0f, 400.0f));

    // m_pHMD = nullptr;
    // cardinal::RenderingEngine::InitializeStereoscopicRendering();
    // m_pHMD = cardinal::RenderingEngine::GetHMD();
    // ASSERT_NOT_NULL(m_pHMD);

    m_pWorld = m_worldGenerator.generateWorld();

    m_cameraManager.SetCamera(pCamera);
    m_cameraManager.SetCharacter(&m_character);

    m_character.SetPosition(glm::vec3(100.0f, 100.0f, 2200.0f));
    m_character.AttachCamera(pCamera);
}

void Demo_Plugin::OnPlayStop()
{

}

void Demo_Plugin::OnPreUpdate()
{

}

void Demo_Plugin::OnPostUpdate(float dt)
{
    m_character.Update(cardinal::RenderingEngine::GetWindow(), dt);
    m_cameraManager.Update(cardinal::RenderingEngine::GetWindow(), dt);
}

void Demo_Plugin::OnGUI()
{

}