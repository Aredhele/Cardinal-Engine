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

/// \file       DirectionalLight.cpp
/// \date       23/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Lighting
/// \author     Vincent STEHLY--CALISTO

#include "Runtime/Rendering/Lighting/Lights/DirectionalLight.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
DirectionalLight::DirectionalLight()
{
    // Basics settings
    SetPosition(glm::vec3(16.0f, 16.0f, 16.0f));
    SetLightIntensity  (0.8f);
    SetAmbientIntensity(0.3f);
    SetLightColor  (glm::vec3(1.0f, 1.0f, 1.0f));
    SetAmbientColor(glm::vec3(1.0f, 1.0f, 1.0f));
}

/// \brief Sets the light intensity
/// \param intensity The intensity of the light
void DirectionalLight::SetLightIntensity(float intensity)
{
    m_lightIntensity = intensity;
}

/// \brief Sets the intensity of the ambient
/// \param intensity The intensity of the ambient
void DirectionalLight::SetAmbientIntensity(float intensity)
{
    m_ambientIntensity = intensity;
}

/// \brief Sets the position of the light
/// \param position The new position
void DirectionalLight::SetPosition(glm::vec3 const &position)
{
    m_position = position;
}

/// \brief Sets the light color
/// \param color The  new color
void DirectionalLight::SetLightColor(glm::vec3 const &color)
{
    m_lightColor = color;
}

/// \brief Sets the ambient color
/// \param color The new color
void DirectionalLight::SetAmbientColor(glm::vec3 const &color)
{
    m_ambientColor = color;
}

/// \brief Returns the light intensity
/// \return The intensity of the light
float DirectionalLight::GetLightIntensity() const
{
    return m_lightIntensity;
}

/// \brief Returns the ambient intensity
/// \return The ambient intensity
float DirectionalLight::GetAmbientIntensity() const
{
    return m_ambientIntensity;
}

/// \brief Returns the position of the light
/// \return The current position
glm::vec3 const &DirectionalLight::GetPosition() const
{
    return m_position;
}

/// \brief Returns the color of the light
/// \return The color of the light
glm::vec3 const &DirectionalLight::GetLightColor() const
{
    return m_lightColor;
}

/// \brief Returns the color of the ambient
/// \return The ambient color
glm::vec3 const &DirectionalLight::GetAmbientColor() const
{
    return m_ambientColor;
}

} // !namespace