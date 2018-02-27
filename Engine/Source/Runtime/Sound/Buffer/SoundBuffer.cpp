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

/// \file       SoundBuffer.cpp
/// \date       28/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Sound/Buffer
/// \author     Vincent STEHLY--CALISTO

#include "Runtime/Sound/Buffer/SoundBuffer.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Initializes the buffer
/// \param bufferID The OpenAL sound buffer ID
/// \param format The sound data format
/// \param frequency The frequency of the sound data
/// \param size Data size
void SoundBuffer::Initialize(ALuint bufferID, ALenum format, ALsizei frequency, ALsizei size)
{
    m_bufferID  = bufferID;
    m_format    = format;
    m_frequency = frequency;
    m_size      = size;
}
/// \brief Returns the id of the OpenAL buffer
/// \return The OpenAL buffer ID
ALuint SoundBuffer::GetID() const
{
    return m_bufferID;
}

/// \brief Returns the format of the audio
/// \return The audio format
ALenum SoundBuffer::GetFormat() const
{
    return m_format;
}

/// \brief Returns the frequency of the audio
/// \return The audio Frequency
ALsizei SoundBuffer::GetFrequency() const
{
    return m_frequency;
}

/// \brief Returns the size of the buffer
/// \return The buffer size
ALsizei SoundBuffer::GetSize() const
{
    return m_size;
}

} // !namespace