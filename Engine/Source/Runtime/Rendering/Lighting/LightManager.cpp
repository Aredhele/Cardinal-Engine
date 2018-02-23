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

/// \file       LightManager.cpp
/// \date       23/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Lighting
/// \author     Vincent STEHLY--CALISTO

#include <Header/Runtime/Rendering/Shader/Built-in/Lit/LitTextureShader.hpp>
#include "Glew/include/GL/glew.h"

#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Core/Assertion/Assert.hh"
#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/Lighting/LightManager.hpp"
#include "Runtime/Rendering/Lighting/Lights/DirectionalLight.hpp"

/// \namespace cardinal
namespace cardinal
{

/* static */ LightManager * LightManager::s_pInstance = nullptr;

/// \brief Initializes the light manager
/* static */ void LightManager::Initialize()
{
    if(LightManager::s_pInstance == nullptr)
    {
        LightManager::s_pInstance = new LightManager();
        Logger::LogInfo("Light manager successfully initialized");
    }
    else
    {
        Logger::LogWaring("The light manager is already initialized");
    }
}

/// \brief Shutdowns the light  manager
/* static */ void LightManager::Shutdown()
{
    if(LightManager::s_pInstance != nullptr)
    {
        delete LightManager::s_pInstance;
        LightManager::s_pInstance = nullptr;

        Logger::LogInfo("Light manager successfully destroyed");
    }
    else
    {
        Logger::LogWaring("The light manager is already destroyed");
    }
}

/// \brief Creates a directional light in the engine
/* static */ void LightManager::CreateDirectionalLight()
{
    ASSERT_NOT_NULL(s_pInstance);
    ASSERT_NULL_MSG(s_pInstance->m_pDirectional, "Please delete the current directional light before creating a new one.");
    s_pInstance->m_pDirectional = new DirectionalLight();
}

/// \brief Deletes the active directional light
/* static */ void LightManager::DeleteDirectionalLight()
{
    ASSERT_NOT_NULL(s_pInstance);
    delete s_pInstance->m_pDirectional;
    s_pInstance->m_pDirectional = nullptr;
}

/// \brief Returns the directional light
/// \return A pointer on the active directional light
/* static */ DirectionalLight * LightManager::GetDirectional()
{
    ASSERT_NOT_NULL(s_pInstance);
    return s_pInstance->m_pDirectional;
}

/// \brief Called just before rendering
/* static */ void LightManager::OnRenderBegin()
{
    ASSERT_NOT_NULL(s_pInstance);

    float lightIntensity   = 0.0f;
    float ambientIntensity = 0.2;
    glm::vec3 position    (0.0f, 0.0f, 0.0f);
    glm::vec3 lightColor  (1.0f, 1.0f, 1.0f);

    // Updates uniforms
    if(s_pInstance->m_pDirectional != nullptr)
    {
        lightIntensity   = s_pInstance->m_pDirectional->GetLightIntensity();
        ambientIntensity = s_pInstance->m_pDirectional->GetAmbientIntensity();
        position         = s_pInstance->m_pDirectional->GetPosition();
        lightColor       = s_pInstance->m_pDirectional->GetLightColor();
    }

    uint shaderID = (uint)ShaderManager::GetShaderID("LitTexture");

    glUseProgram (shaderID);
    glUniform1f  (LitTextureShader::s_lightIntensity,   lightIntensity);
    glUniform1f  (LitTextureShader::s_ambientIntensity, ambientIntensity);
    glUniform3f  (LitTextureShader::s_lightPosition,    position.x,     position.y,     position.z);
    glUniform3f  (LitTextureShader::s_lightColor,       lightColor.x,   lightColor.y,   lightColor.z);
}

} // !namespace