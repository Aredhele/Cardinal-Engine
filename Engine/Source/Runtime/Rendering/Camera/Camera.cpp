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

/// \file       Camera.cpp
/// \date       10/02/2018
/// \project    Cardinal Engine
/// \package    Rendering/Camera
/// \author     Vincent STEHLY--CALISTO

#include "Glm/glm/ext.hpp"
#include "ImGUI/Header/ImGUI/imgui.h"
#include "Runtime/Rendering/Camera/Camera.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
Camera::Camera()
{
    m_fov = 45.0f;

    m_up        = glm::vec3(   0.0f,   0.0f,    1.0f);
    m_right     = glm::vec3(   1.0f,   0.0f,    0.0f);
    m_lookAt    = glm::vec3( 165.0f, 165.0f,   96.0f);
    m_position  = glm::vec3(-229.0f, -42.0f,  439.0f);
    m_direction = glm::vec3(   0.0f,   0.0f,    1.0f);

    m_viewMatrix  = glm::lookAt(m_position, m_lookAt, m_up);
    inspectorName = "Main Camera";
}

/// \brief Destructor
Camera::~Camera() // NOLINT
{
    // None
}

/// \brief Updates all reference vectors
void Camera::UpdateVectors()
{
    m_direction  = m_lookAt;
    m_direction -= m_position;
    m_direction  = glm::normalize(m_direction);

    m_up    = glm::vec3(0.0f, 0.0f, 1.0f);
    m_right = glm::cross(m_direction, m_up);
    m_right = glm::normalize(m_right);

    m_up = glm::cross(m_right, m_direction);
    m_up = glm::normalize(m_up);

    m_viewMatrix = glm::lookAt(m_position, m_lookAt + m_direction, m_up);
}

/// Transformations
/// \brief Sets the position of the camera
/// \param position The new position
void Camera::SetPosition(glm::vec3 const& position)
{
    m_position = position;
    UpdateVectors();
}

void Camera::SetDirection(const glm::vec3 &direction)
{
    m_direction = direction;
    UpdateVectors();
}

/// \brief Translates the camera
/// \param position The offset
void Camera::Translate(glm::vec3 const& translation)
{
    m_position += translation;
    m_lookAt   += translation;
    UpdateVectors();
}

/// \brief Rotates right-left
/// \param angle The angle to add
void Camera::Rotate(float angle)
{
    m_lookAt -= m_position;
    m_lookAt  = glm::rotate(m_lookAt, angle, m_up);
    m_lookAt += m_position;

    UpdateVectors();
}

/// \brief Rotates up-down
/// \param angle The angle to add
void Camera::RotateUp(float angle)
{
    m_lookAt -= m_position;
    m_lookAt  = glm::rotate(m_lookAt, angle, m_right);
    m_lookAt += m_position;

    UpdateVectors();
}

/// \brief Rotates right-left
/// \param angle The angle to add
void Camera::RotateAround(float angle)
{
    m_position -= m_lookAt;
    m_position = glm::rotate(m_position, angle, m_up);
    m_position += m_lookAt;

    UpdateVectors();
}

/// \brief Rotates up-down
/// \param angle The angle to add
void Camera::RotateUpAround(float angle)
{
    m_position -= m_lookAt;
    m_position = glm::rotate(m_position, angle, m_right);
    m_position += m_lookAt;

    UpdateVectors();
}

/// \brief Forces the camera to look at the target
void Camera::LookAt(const glm::vec3& target)
{
    m_lookAt = target;
    UpdateVectors();
}

/// \brief Returns the position of the camera
glm::vec3 const& Camera::GetPosition() const
{
    return m_position;
}

/// \brief Returns the direction of the camera
glm::vec3 const& Camera::GetDirection() const
{
    return m_direction;
}

/// \brief Returns the right vector
glm::vec3 const& Camera::GetRight() const
{
    return m_right;
}

/// \brief Returns the up vector
glm::vec3 const& Camera::GetUp() const
{
    return m_up;
}

/// \brief Returns the view matrix
glm::mat4 const& Camera::GetViewMatrix() const
{
    return m_viewMatrix;
}

/// \brief Called when the object is inspected
void Camera::OnInspectorGUI()
{
    ImGui::Text(inspectorName.c_str());
    if(ImGui::InputFloat3("Position###Camera_position", &m_position[0], 3))    UpdateVectors();
    if(ImGui::InputFloat3("Direction###Camera_direction", &m_direction[0], 3)) UpdateVectors();

    ImGui::TextDisabled("\nUp     : %f %f %f", m_up.x,    m_up.y,    m_up.z);
    ImGui::TextDisabled(  "Right  : %f %f %f", m_right.x, m_right.y, m_right.z);
    ImGui::TextDisabled(  "Target : %f %f %f", m_lookAt.x, m_lookAt.y, m_lookAt.z);
}

} // !namespace