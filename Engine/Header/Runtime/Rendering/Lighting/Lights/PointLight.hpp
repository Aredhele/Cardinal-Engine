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

/// \file       PointLight.hpp
/// \date       24/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/Lighting/Lights
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_POINT_LIGHT_HPP__
#define CARDINAL_ENGINE_POINT_LIGHT_HPP__

#include "Glm/glm/vec3.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \class PointLight
/// \brief Light with a certain range
class PointLight
{
public:

    /// \brief Sets the range of the light (in engine unit)
    /// \param range The new range
    void SetRange(float range);

    /// \brief Sets the intensity of the light
    /// \param intensity The new intensity
    void SetIntensity(float intensity);

    /// \brief Sets the position of the light
    /// \param position The new position
    void SetPosition(glm::vec3 const& position);

    /// \brief Sets the color of the light
    /// \param color The new color
    void SetColor(glm::vec3 const& color);

    /// \brief  Returns the range of the light
    /// \return The range of the light
    float GetRange() const;

    /// \brief Return the intensity of the light
    /// \return The intensity of the light
    float GetIntensity() const;

    /// \brief  Returns the position of the light
    /// \return The position of the light
    glm::vec3 const& GetPosition() const;

    /// \brief Returns the color of the light
    /// \return The color of the light
    glm::vec3 const& GetColor() const;

private:

    friend class LightManager;

    /// \brief Constructor
    PointLight();

    /// \brief Destructor
    ~PointLight();

private:

    float     m_range;
    float     m_intensity;
    glm::vec3 m_position;
    glm::vec3 m_color;
};

} // !namespace

#endif // !CARDINAL_ENGINE_POINT_LIGHT_HPP__