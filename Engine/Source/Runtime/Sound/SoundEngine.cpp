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

/// \file       SoundEngine.cpp
/// \date       27/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Sound
/// \author     Vincent STEHLY--CALISTO

#include "Runtime/Sound/SoundEngine.hpp"
#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Core/Assertion/Assert.hh"

/// \namespace cardinal
namespace cardinal
{

/* static */ SoundEngine * SoundEngine::s_pInstance = nullptr;

/// \brief Initializes the sound engine
/// \return True or false
bool SoundEngine::Initialize()
{
    ASSERT_NULL(SoundEngine::s_pInstance);
    Logger::LogInfo("Initializing the sound engine ...");

    m_pDevice  = nullptr;
    m_pContext = nullptr;

    m_pDevice = alcOpenDevice(nullptr);
    if(m_pDevice == nullptr)
    {
        Logger::LogInfo("Getting sound device      : Failed");
        return false;
    }
    else
    {
        Logger::LogInfo("Getting sound device      : OK");
    }

    m_pContext = alcCreateContext(m_pDevice, nullptr);
    if(m_pContext == nullptr)
    {
        Logger::LogInfo("Creating sound context    : Failed");
        return false;
    }
    else
    {
        Logger::LogInfo("Creating sound context    : OK");
    }

    alcMakeContextCurrent(m_pContext);
    Logger::LogInfo("Setting the sound context : OK");

    Logger::LogInfo("Sound engine successfully initialized");
    return true;
}

/// \brief Shutdowns the sound engine
void SoundEngine::Shutdown()
{
    alcDestroyContext(m_pContext);
    alcCloseDevice(m_pDevice);
}

/// \brief Loads an audio file into the engine
/// \param file The path of the file
/// \param fileID The id of the audio
/// \return True or false
/* static */ bool SoundEngine::LoadAudio(const char * file, const char * audioID)
{
    return false;
}

} // !namespace