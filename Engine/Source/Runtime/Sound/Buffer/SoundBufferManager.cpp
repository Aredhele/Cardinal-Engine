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

/// \file       SoundBufferManager.cpp
/// \date       28/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Sound/Buffer
/// \author     Vincent STEHLY--CALISTO

#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Core/Assertion/Assert.hh"
#include "Runtime/Sound/Buffer/SoundBufferManager.hpp"

/// \namespace cardinal
namespace cardinal
{

/* static */ SoundBufferManager * SoundBufferManager::s_pInstance = nullptr;

/// \brief Default constructor
SoundBufferManager::SoundBufferManager() // NOLINT
{
    // None
}

/// \brief Initializes the buffer manager
///        Initializes the buffer instance
/* static */ void SoundBufferManager::Initialize()
{
    if(SoundBufferManager::s_pInstance == nullptr)
    {
        SoundBufferManager::s_pInstance = new SoundBufferManager();
        Logger::LogInfo("Sound buffer manager successfully initialized");
    }
    else
    {
        Logger::LogWaring("The sound buffer manager is already initialized");
    }
}

/// \brief Destroys the buffer manager
///        Destroys the buffer instance
/* static */ void SoundBufferManager::Shutdown()
{
    if(SoundBufferManager::s_pInstance != nullptr)
    {
        delete SoundBufferManager::s_pInstance;
        SoundBufferManager::s_pInstance = nullptr;

        Logger::LogInfo("Sound buffer manager successfully destroyed");
    }
    else
    {
        Logger::LogWaring("The sound buffer manager is already destroyed");
    }
}

/// \brief Registers a sound buffer in the manager from a key and a value
/// \param bufferKey The key of the sound buffer
/// \param buffer The buffer to register
/* static */ void SoundBufferManager::Register(std::string const& bufferKey, SoundBuffer const& buffer)
{
    ASSERT_NE      (bufferKey, "");
    ASSERT_NOT_NULL(SoundBufferManager::s_pInstance);

    SoundBufferManager::s_pInstance->m_bufferIDs.emplace(bufferKey, buffer);
    Logger::LogInfo("Sound %s registered", bufferKey.c_str());
}

/// \brief Unregisters a sound buffer in the manager
///        Frees the sound buffer in the memory
/// \param bufferKey The buffer to unregister
/* static */ void SoundBufferManager::Unregister(std::string const& bufferKey)
{
    ASSERT_NE      (bufferKey, "");
    ASSERT_NOT_NULL(SoundBufferManager::s_pInstance);

    auto it = SoundBufferManager::s_pInstance->m_bufferIDs.find(bufferKey);
    if(it != SoundBufferManager::s_pInstance->m_bufferIDs.end())
    {
        SoundBufferManager::s_pInstance->m_bufferIDs.erase(it);
    }
}

/// \brief Returns the buffer ID references by the given key
/// \param bufferKey The key of the buffer
/// \return The sound buffer
/* static */  SoundBuffer SoundBufferManager::GetBuffer(std::string const& bufferKey)
{
    ASSERT_NOT_NULL(SoundBufferManager::s_pInstance);

    SoundBuffer buffer;
    auto it = SoundBufferManager::s_pInstance->m_bufferIDs.find(bufferKey);

    if(it != SoundBufferManager::s_pInstance->m_bufferIDs.end())
    {
        buffer = it->second;
    }
    else
    {
        Logger::LogError("Unable to find the sound buffer %s", bufferKey.c_str());
        // ASSERT_ALWAYS ?
    }

    return buffer;
}

} // !namespace