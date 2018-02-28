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

/// \file       AudioSource.cpp
/// \date       28/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Sound/Source
/// \author     Vincent STEHLY--CALISTO

#include "Runtime/Sound/Source/AudioSource.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor, generate OpenAL buffer
AudioSource::AudioSource()
{
    m_sourceID = 0;
    alGenSources(1, &m_sourceID);

    m_bLoop    = false;
    m_volume   = 0.5f;
    m_pitch    = 1.0f;
    m_position = glm::vec3(0.0f);
    m_velocity = glm::vec3(0.0f);
}

/// \brief Destructor
AudioSource::~AudioSource()
{
    alDeleteBuffers(1, &m_sourceID);
}

/// \brief Plays the sound
void AudioSource::Play()
{
    alSourcePlay(m_sourceID);
}

/// \brief Stops the sound
void AudioSource::Stop()
{
    alSourceStop(m_sourceID);
}

/// \brief Pauses the sound
void AudioSource::Pause()
{
    alSourcePause(m_sourceID);
}

/// \briefs Sets the loop attribute
/// \param bLoop Is the audio looping ?
void AudioSource::SetLooping(bool bLoop)
{
    m_bLoop = bLoop;
    alSourcei(m_sourceID, AL_LOOPING, (int)m_bLoop);
}

/// \brief Sets the volume [0, 1]
/// \param volume The new volume
void AudioSource::SetVolume(float volume)
{
    m_volume = volume;
    alBufferf(m_sourceID, AL_GAIN, volume);
}

/// \brief Sets the pitch
/// \param pitch The new pitch
void AudioSource::SetPitch(float pitch)
{
    m_pitch = pitch;
    alBufferf(m_sourceID, AL_PITCH, m_pitch);
}

/// \brief Sets the position of the audio source
/// \param position The new position
void AudioSource::SetPosition(glm::vec3 const &position)
{
    m_position = position;
    alBuffer3f(m_sourceID, AL_POSITION, m_position.x, m_position.y, m_position.z);
}

/// \brief Sets the velocity of the audio source
/// \param velocity The new velocity
void AudioSource::SetVelocity(glm::vec3 const &velocity)
{
    m_velocity = velocity;
    alBuffer3f(m_sourceID, AL_POSITION, m_velocity.x, m_velocity.y, m_velocity.z);
}

/// \brief Sets the sound buffer of the audio source
void AudioSource::SetSoundBuffer(SoundBuffer const &buffer)
{
    m_buffer = buffer;

    SetPitch(m_pitch);
    SetLooping(m_bLoop);
    SetVolume(m_volume);
    SetPosition(m_position);
    SetVelocity(m_velocity);
}

/// \brief Tells is the source is playing
/// \return True or false
bool AudioSource::IsPlaying() const
{
    ALint state;
    alGetSourcei(m_sourceID, AL_SOURCE_STATE, &state);

    return (state == AL_PLAYING);
}

/// \brief Tells if the source is looping
/// \return True or false
bool AudioSource::IsLooping() const
{
    return m_bLoop;
}

/// \brief Returns the current volume
float AudioSource::GetVolume() const
{
    return m_volume;
}

/// \brief Returns the current pitch
float AudioSource::GetPitch() const
{
    return m_pitch;
}

/// \brief Returns the current position
glm::vec3 const& AudioSource::GetPosition() const
{
    return m_position;
}

/// \brief Returns the current velocity
glm::vec3 const &AudioSource::GetVelocity() const
{
    return m_velocity;
}

} // !namespace