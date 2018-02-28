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


#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Core/Assertion/Assert.hh"

#include "Runtime/Sound/SoundEngine.hpp"
#include "Runtime/Sound/Loader/AudioLoader.hpp"
#include "Runtime/Sound/Buffer/SoundBufferManager.hpp"

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

    SoundBufferManager::Initialize();

    alcMakeContextCurrent(m_pContext);
    Logger::LogInfo("Setting the sound context : OK");

    Logger::LogInfo("Sound engine successfully initialized");
    return true;
}

/// \brief Shutdowns the sound engine
void SoundEngine::Shutdown()
{
    SoundBufferManager::Shutdown();
    alcDestroyContext(m_pContext);
    alcCloseDevice(m_pDevice);
}

/// \brief Loads an audio buffer into the engine
/// \param file The path of the file
/// \param fileID The id of the buffer
/// \return True or false
/* static */ bool SoundEngine::CreateSoundBuffer(const char * file, const char * audioID)
{
    ALuint  bufferID   = 0;
    ALenum  format     = 0;
    ALsizei frequency  = 0;
    ALsizei size       = 0;

    if(!AudioLoader::LoadWave(file, &bufferID, &size, &frequency, &format))
    {
        Logger::LogError("Unable to create the sound buffer, aborting.");
        return false;
    }

    SoundBuffer soundBuffer;
    soundBuffer.Initialize(bufferID, format, frequency, size);

    SoundBufferManager::Register(audioID, soundBuffer);
}

/// \brief Creates an audio listener in the engine
/* static */ void SoundEngine::CreateAudioListener()
{
    ASSERT_NOT_NULL(s_pInstance);

    if(s_pInstance->m_pAudioListener == nullptr)
    {
        s_pInstance->m_pAudioListener = new AudioListener();
    }
}

/// \brief Returns the audio listener
/// \return A pointer on the listener
/* static */ AudioListener * SoundEngine::GetAudioListener()
{
    ASSERT_NOT_NULL(s_pInstance);
    return s_pInstance->m_pAudioListener;
}

/// \brief Allocates an audio source
/// \return A pointer on a audio source
/* static */ AudioSource * SoundEngine::AllocateAudioSource()
{
    ASSERT_NOT_NULL(SoundEngine::s_pInstance);

    AudioSource * pSource = new AudioSource(); // NOLINT
    SoundEngine::s_pInstance->m_audioSources.push_back(pSource);

    return pSource;
}

/// \brief Releases an audio source
/// \param pSource The pointer on the audio source to release
/* static */ void SoundEngine::ReleaseAudioSource(AudioSource *& pSource)
{
    ASSERT_NOT_NULL(SoundEngine::s_pInstance);

    int index = -1;
    size_t count = SoundEngine::s_pInstance->m_audioSources.size();
    for (size_t nSources = 0; nSources < count; ++nSources)
    {
        if (SoundEngine::s_pInstance->m_audioSources[nSources] == pSource)
        {
            index = static_cast<int>(nSources);
            break;
        }
    }

    if (index != -1)
    {
        SoundEngine::s_pInstance->m_audioSources.erase(
                SoundEngine::s_pInstance->m_audioSources.begin() + index);
    }

    delete pSource;
    pSource = nullptr;
}

} // !namespace