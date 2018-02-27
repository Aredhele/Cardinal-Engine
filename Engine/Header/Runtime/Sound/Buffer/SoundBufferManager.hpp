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

/// \file       SoundBufferManager.hpp
/// \date       28/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Sound/Buffer/
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_SOUND_BUFFER_MANAGER_HPP__
#define CARDINAL_ENGINE_SOUND_BUFFER_MANAGER_HPP__

#include <string>
#include <unordered_map>

#include "Runtime/Sound/Buffer/SoundBuffer.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \class SoundBufferManager
/// \brief Stores OpenAL buffer ID / Keys
class SoundBufferManager
{
public :

    /// \brief Registers a sound buffer in the manager from a key and a value
    /// \param bufferKey The key of the sound buffer
    /// \param buffer The buffer to register
    static void Register(std::string const& bufferKey, SoundBuffer const& buffer);

    /// \brief Unregisters a sound buffer in the manager
    ///        Frees the sound buffer in the memory
    /// \param bufferKey The buffer to unregister
    static void Unregister(std::string const& bufferKey);

    /// \brief Returns the buffer references by the given key
    /// \param bufferKey The key of the buffer
    /// \return The sound buffer
    static SoundBuffer GetBuffer(std::string const& bufferKey);

private:

    friend class SoundEngine;

    static SoundBufferManager * s_pInstance;

    /// \brief Initializes the buffer manager
    ///        Initializes the buffer instance
    static void Initialize();

    /// \brief Destroys the buffer manager
    ///        Destroys the buffer instance
    static void Shutdown  ();

private:

    /// \brief  Default constuctor
    SoundBufferManager();

    std::unordered_map<std::string, SoundBuffer> m_bufferIDs;
};

} // !namespace

#endif // !CARDINAL_ENGINE_SOUND_BUFFER_MANAGER_HPP__