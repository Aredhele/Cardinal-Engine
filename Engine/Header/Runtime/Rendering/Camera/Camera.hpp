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

/// \file       Camera.hpp
/// \date       10/02/2018 
/// \project    Cardinal Engine
/// \package    Rendering/Camera
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_CAMERA_HPP__
#define CARDINAL_ENGINE_CAMERA_HPP__

#include "Glm/glm/glm.hpp"
#include "Glm/glm/ext.hpp"
#include "Runtime/Rendering/Hierarchy/Inspector.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \class Camera
/// \brief Engine camera
class Camera : public Inspector
{
public :

    /// \brief Constructor
    Camera();

    /// \brief Destructor
    ~Camera();

    /// Transformations
    /// \brief Sets the position of the camera
    /// \param position The new position
    void SetPosition(glm::vec3 const& position);

    /// \brief Translates the camera
    /// \param position The offset
    void Translate(glm::vec3 const& translation);

    /// \brief Rotates right-left
    /// \param angle The angle to add
    void Rotate(float angle);

    /// \brief Rotates up-down
    /// \param angle The angle to add
    void RotateUp(float angle);

    /// \brief Rotates right-left
    /// \param angle The angle to add
    void RotateAround(float angle);

    /// \brief Rotates up-down
    /// \param angle The angle to add
    void RotateUpAround(float angle);

    /// \brief Forces the camera to look at the target
    void LookAt(glm::vec3 const & target);

    /// \brief Returns the position of the camera
    glm::vec3 const& GetPosition() const;

    /// \brief Returns the direction of the camera
    glm::vec3 const& GetDirection() const;

    /// \brief Returns the right vector
    glm::vec3 const& GetRight() const;

    /// \brief Returns the up vector
    glm::vec3 const& GetUp() const;

    /// \brief Returns the view matrix
    glm::mat4 const& GetViewMatrix() const;

    /// \brief Called when the object is inspected
    void OnInspectorGUI() final;

private:

    /// \brief Updates all reference vectors
    void UpdateVectors();

private:

    float m_fov;

    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_lookAt;

    glm::vec3 m_position;
    glm::vec3 m_direction;

    glm::mat4 m_viewMatrix;
};

} // !namespace

#endif // !CARDINAL_ENGINE_CAMERA_HPP__