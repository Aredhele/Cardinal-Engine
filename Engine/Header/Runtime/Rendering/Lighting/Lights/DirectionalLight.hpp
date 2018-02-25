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

/// \file       DirectionalLight.hpp
/// \date       23/02/2018 
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Lighting
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_DIRECTIONAL_LIGHT_HPP__
#define CARDINAL_ENGINE_DIRECTIONAL_LIGHT_HPP__

#include "Glm/glm/vec3.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \class DirectionalLight
/// \brief Stores directional light information
class DirectionalLight
{
public:

    /// \brief Sets the light intensity
    /// \param intensity The intensity of the light
    void SetLightIntensity(float intensity);

    /// \brief Sets the intensity of the ambient
    /// \param intensity The intensity of the ambient
    void SetAmbientIntensity(float intensity);

    /// \brief Sets the position of the light
    /// \param position The new position
    void SetPosition(glm::vec3 const& position);

    /// \brief Sets the direction of the light
    /// \param direction The new direction
    void SetDirection(glm::vec3 const& direction);

    /// \brief Sets the light color
    /// \param color The  new color
    void SetLightColor(glm::vec3 const& color);

    /// \brief Sets the ambient color
    /// \param color The new color
    void SetAmbientColor(glm::vec3 const& color);

    /// \brief Returns the light intensity
    /// \return The intensity of the light
    float GetLightIntensity() const;

    /// \brief Returns the ambient intensity
    /// \return The ambient intensity
    float GetAmbientIntensity() const;

    /// \brief Returns the position of the light
    /// \return The current position
    glm::vec3 const& GetPosition() const;

    /// \brief Returns the direction of the light
    /// \param The direction of the light
    glm::vec3 const& GetDirection() const;

    /// \brief Returns the color of the light
    /// \return The color of the light
    glm::vec3 const& GetLightColor()   const;

    /// \brief Returns the color of the ambient
    /// \return The ambient color
    glm::vec3 const& GetAmbientColor() const;

private:

    friend class LightManager;

    /// \brief Constructor
    DirectionalLight ();

    /// \brief Destructor
    ~DirectionalLight() = default;

private:

    float     m_lightIntensity;
    float     m_ambientIntensity;

    glm::vec3 m_lightColor;
    glm::vec3 m_ambientColor;
    glm::vec3 m_position;
    glm::vec3 m_direction;
};

} // !namespace 

#endif // !CARDINAL_ENGINE_DIRECTIONAL_LIGHT_HPP__