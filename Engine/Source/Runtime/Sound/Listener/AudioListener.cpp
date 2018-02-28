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

/// \file       AudioListener.cpp
/// \date       28/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Sound/Listener
/// \author     Vincent STEHLY--CALISTO

#include "Runtime/Sound/Listener/AudioListener.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
AudioListener::AudioListener()
{
    m_position = glm::vec3(0.0f);
}

/// \brief Sets the position of the audio listener
/// \param position The new position
void AudioListener::SetPosition(glm::vec3 const& position)
{
    m_position = position;
    alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    alListener3f(AL_POSITION, m_position.x, m_position.y, m_position.z);
}

/// \brief Returns the position of the audio listener
/// \return the position of the listener
glm::vec3 const& AudioListener::GetPosition() const
{
    return m_position;
}

} // !namespace