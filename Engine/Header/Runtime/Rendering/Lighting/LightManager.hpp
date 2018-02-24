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

/// \file       LightManager.hpp
/// \date       23/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Lighting
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_LIGHT_MANAGER_HPP__
#define CARDINAL_ENGINE_LIGHT_MANAGER_HPP__

#include <vector>
#include "Runtime/Rendering/Lighting/LightStructure.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \class LightManager
/// \brief Stores all lights
class LightManager
{
public:

    /// \brief Initializes the light manager
    static void Initialize();

    /// \brief Shutdowns the light  manager
    static void Shutdown();

    /// \brief Creates a directional light in the engine
    static void CreateDirectionalLight();

    /// \brief Deletes the active directional light
    static void DeleteDirectionalLight();

    /// \brief Returns the directional light
    /// \return A pointer on the active directional light
    static class DirectionalLight * GetDirectionalLight();

    /// \brief  Allocates and returns a pointer on the new point light
    /// \return A pointer on the point light
    static class PointLight * AllocatePointLight();

    /// \brief Releases a point light
    /// \param pLight The pointer on the light to release
    static void ReleasePointLight(class PointLight *& pLight);

    /// \brief Searches the 4 nearest point lights from the given position
    /// \param A vector of point light structures
    static std::vector<PointLightStructure> GetNearestPointLights(glm::vec3 const& position);

private:

    friend class RenderingEngine;

    /// \brief Called just before rendering
    ////       to updates uniforms in shader
    static void OnRenderBegin();

private:

    static LightManager * s_pInstance;

private:

    class DirectionalLight *        m_pDirectional;
    std::vector<class PointLight *> m_pointLights;
};

} // !namespace

#endif // !CARDINAL_ENGINE_LIGHT_MANAGER_HPP__