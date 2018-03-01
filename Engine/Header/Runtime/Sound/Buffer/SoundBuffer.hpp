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

/// \file       SoundBuffer.hpp
/// \date       28/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Sound/Buffer
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_SOUND_BUFFER_HPP__
#define CARDINAL_ENGINE_SOUND_BUFFER_HPP__

#include"OpenAL/include/AL/al.h"

/// \namespace cardinal
namespace cardinal
{
    
/// \class SoundBuffer
/// \brief Stores information on a sound buffer
class SoundBuffer
{
public:

    /// \brief Constructor
    SoundBuffer();

    /// \brief Initializes the buffer
    /// \param bufferID The OpenAL sound buffer ID
    /// \param format The sound data format
    /// \param frequency The frequency of the sound data
    /// \param size Data size
    void Initialize(ALuint bufferID, ALenum format, ALsizei frequency, ALsizei size);

    /// \brief Returns the id of the OpenAL buffer
    /// \return The OpenAL buffer ID
    ALuint GetID() const;

    /// \brief Returns the format of the audio
    /// \return The audio format
    ALenum GetFormat() const;

    /// \brief Returns the frequency of the audio
    /// \return The audio Frequency
    ALsizei GetFrequency() const;

    /// \brief Returns the size of the buffer
    /// \return The buffer size
    ALsizei GetSize() const;

private:

    ALuint  m_bufferID;  ///< The OpenAL sound buffer ID
    ALenum  m_format;    ///< The sound data format
    ALsizei m_frequency; ///< The frequency of the sound data
    ALsizei m_size;      ///< Data size
};

} // !namespace 

#endif // !CARDINAL_ENGINE_SOUND_BUFFER_HPP__