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

/// \file       AudioSource.hpp
/// \date       27/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Sound/Source
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_AUDIO_SOURCE_HPP__
#define CARDINAL_ENGINE_AUDIO_SOURCE_HPP__

#include "Glm/glm/vec3.hpp"
#include "Runtime/Sound/Buffer/SoundBuffer.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \class AudioSource
/// \brief 3D audio sources
class AudioSource
{
public:

    /// \brief Plays the sound
    void Play();

    /// \brief Stops the sound
    void Stop();

    /// \brief Pauses the sound
    void Pause();

    /// \briefs Sets the loop attribute
    /// \param bLoop Is the audio looping ?
    void SetLooping(bool bLoop);

    /// \brief Sets the volume [0, 1]
    /// \param volume The new volume
    void SetVolume (float volume);

    /// \brief Sets the pitch
    /// \param pitch The new pitch
    void SetPitch(float pitch);

    /// \brief Sets the position of the audio source
    /// \param position The new position
    void SetPosition(glm::vec3 const& position);

    /// \brief Sets the velocity of the audio source
    /// \param velocity The new velocity
    void SetVelocity(glm::vec3 const& velocity);

    /// \brief Sets the sound buffer of the audio source
    void SetSoundBuffer(SoundBuffer const& buffer);

    /// \brief Tells is the source is playing
    /// \return True or false
    bool IsPlaying()  const;

    /// \brief Tells if the source is looping
    /// \return True or false
    bool IsLooping()  const;

    /// \brief Returns the current volume
    float GetVolume() const;

    /// \brief Returns the current pitch
    float GetPitch()  const;

    /// \brief Returns the current position
    glm::vec3 const& GetPosition() const;

    /// \brief Returns the current velocity
    glm::vec3 const& GetVelocity() const;

private:

    friend class SoundEngine;

    /// \brief Constructor
    AudioSource();

    /// \brief Destructor
    ~AudioSource();

private:

    bool        m_bLoop;     ///< Am I looping ?
    float       m_volume;    ///< The volume
    float       m_pitch;     ///< The pitch
    ALuint      m_sourceID;  ///< The OpenAL ID of the audio source
    glm::vec3   m_position;  ///< The position of the audio source
    glm::vec3   m_velocity;  ///< The velocity of the audio source
    SoundBuffer m_buffer;    ///< The sound buffer
};

} // !namespace

#endif // !CARDINAL_ENGINE_AUDIO_SOURCE_HPP__