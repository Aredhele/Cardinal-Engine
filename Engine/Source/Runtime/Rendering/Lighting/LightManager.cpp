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

#include "Glew/include/GL/glew.h"

#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Core/Assertion/Assert.hh"

#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/Shader/Built-in/Lit/LitTextureShader.hpp"
#include "Runtime/Rendering/Shader/Built-in/Standard/StandardShader.hpp"

#include "Runtime/Rendering/Lighting/LightManager.hpp"
#include "Runtime/Rendering/Lighting/Lights/PointLight.hpp"
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
/* static */ DirectionalLight * LightManager::GetDirectionalLight()
{
    ASSERT_NOT_NULL(s_pInstance);
    return s_pInstance->m_pDirectional;
}

/// \brief Called just before rendering
/* static */ void LightManager::OnRenderBegin()
{
    ASSERT_NOT_NULL(s_pInstance);

    float lightIntensity   = 0.2f;
    float ambientIntensity = 0.2;
    glm::vec3 direction   (-0.5f, -0.5f, -0.5f);
    glm::vec3 lightColor  (1.0f,   1.0f,  1.0f);

    // Updates uniforms
    if(s_pInstance->m_pDirectional != nullptr)
    {
        lightIntensity   = s_pInstance->m_pDirectional->GetLightIntensity();
        ambientIntensity = s_pInstance->m_pDirectional->GetAmbientIntensity();
        direction        = s_pInstance->m_pDirectional->GetDirection();
        lightColor       = s_pInstance->m_pDirectional->GetLightColor();
    }

    glUseProgram ((uint)ShaderManager::GetShaderID("LitTexture"));
    glUniform1f  (LitTextureShader::s_lightIntensity,   lightIntensity);
    glUniform1f  (LitTextureShader::s_ambientIntensity, ambientIntensity);
    glUniform3f  (LitTextureShader::s_lightDirection,   direction.x,    direction.y,    direction.z);
    glUniform3f  (LitTextureShader::s_lightColor,       lightColor.x,   lightColor.y,   lightColor.z);

    glUseProgram ((uint)ShaderManager::GetShaderID("Standard"));
    glUniform1f  (StandardShader::s_lightIntensity,     lightIntensity);
    glUniform1f  (StandardShader::s_ambientIntensity,   ambientIntensity);
    glUniform3f  (StandardShader::s_lightDirection,     direction.x,    direction.y,    direction.z);
    glUniform3f  (StandardShader::s_lightColor,         lightColor.x,   lightColor.y,   lightColor.z);
}

/// \brief Returns all points lights
/// \return A vector of point lights
/* static */ std::vector<class PointLight *> const LightManager::GetPointLights()
{
    ASSERT_NOT_NULL(s_pInstance);
    return s_pInstance->m_pointLights;
}

/// \brief  Allocates and returns a pointer on the new point light
/// \return A pointer on the point light
/* static */ PointLight * LightManager::AllocatePointLight()
{
    ASSERT_NOT_NULL(s_pInstance);
    s_pInstance->m_pointLights.push_back(new PointLight());

    return s_pInstance->m_pointLights.back();
}

/// \brief Releases a point light
/// \param pLight The pointer on the light to release
/* static */ void LightManager::ReleasePointLight(PointLight *& pLight)
{
    ASSERT_NOT_NULL(s_pInstance);

    int index = -1;
    size_t count = LightManager::s_pInstance->m_pointLights.size();
    for (size_t nLight = 0; nLight < count; ++nLight)
    {
        if (LightManager::s_pInstance->m_pointLights[nLight] == pLight)
        {
            index = static_cast<int>(nLight);
            break;
        }
    }

    if (index != -1)
    {
        LightManager::s_pInstance->m_pointLights.erase(
                LightManager::s_pInstance->m_pointLights.begin() + index);
    }

    delete pLight;
    pLight = nullptr;
}

/// \brief Searches the 4 nearest point lights from the given position
/// \param A vector of point light structures
/* static */
std::vector<PointLightStructure> LightManager::GetNearestPointLights(glm::vec3 const& position)
{
    ASSERT_NOT_NULL(s_pInstance);
    std::vector<PointLightStructure> lights;

    int index = -1;
    size_t count = LightManager::s_pInstance->m_pointLights.size();
    for (size_t nLight = 0; nLight < count; ++nLight)
    {
        if(lights.size() != 4) // TODO Get only nearest and consider a max range
        {
            lights.emplace_back(PointLightStructure
            {
                s_pInstance->m_pointLights[nLight]->GetRange(),
                s_pInstance->m_pointLights[nLight]->GetIntensity(),
                s_pInstance->m_pointLights[nLight]->GetColor(),
                s_pInstance->m_pointLights[nLight]->GetPosition(),
            });
        }
    }

    return lights;
}

} // !namespace