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

/// \file       AudioLoader.hpp
/// \date       27/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Sound/Loader
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_AUDIO_LOADER_HPP__
#define CARDINAL_ENGINE_AUDIO_LOADER_HPP__

#include "OpenAL/include/AL/al.h"

/// \namespace cardinal
namespace cardinal
{
    
/// \class AudioLoader
/// \brief Loads audio files
class AudioLoader
{
public:

    /// \brief Load PCM data of a wave file
    /// \param szFile The file path
    /// \param pBuffer The buffer pointer
    /// \param size The size of the buffer
    /// \param frequency The frequency of the sound
    /// \param format The audio format
    /// \return True or false
    static bool LoadWave(const char * szFile, ALuint * pBuffer, ALsizei * pSize, ALsizei * pFrequency, ALenum * pFormat);
};

} // !namespace

#endif // !CARDINAL_ENGINE_AUDIO_LOADER_HPP__