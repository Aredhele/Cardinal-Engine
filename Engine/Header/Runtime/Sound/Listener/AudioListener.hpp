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

/// \file       AudioListener.hpp
/// \date       28/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Sound/Listener
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_AUDIO_LISTENER_HPP__
#define CARDINAL_ENGINE_AUDIO_LISTENER_HPP__

#include "Glm/glm/glm.hpp"
#include "OpenAL/include/AL/al.h"

/// \namespace cardinal
namespace cardinal
{

/// \class AudioListener
class AudioListener
{
public:

    /// \brief Sets the position of the audio listener
    /// \param position The new position
    void SetPosition(glm::vec3 const& position);

    /// \brief Sets the direction of the listener
    /// \param direction The direction of the listener
    void SetDirection(glm::vec3 const& direction);

    /// \brief Returns the position of the audio listener
    /// \return the position of the listener
    glm::vec3 const& GetPosition() const;

private:

    friend class SoundEngine;

    /// \brief Constructor
    AudioListener();

private:

    glm::vec3 m_position;
    glm::vec3 m_direction;
};

} // !namespace

#endif // !CARDINAL_ENGINE_AUDIO_LISTENER_HPP__