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

/// \file       AudioLoader.cpp
/// \date       27/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Sound/Loader
/// \author     Vincent STEHLY--CALISTO

#include <cstdio>
#include <Header/Runtime/Core/Debug/Logger.hpp>
#include "Runtime/Sound/Loader/AudioLoader.hpp"
#include "Runtime/Sound/Format/WaveFormat.hpp"

/// \namespace cardinal
namespace cardinal
{

// TODO : Refactor loader
/// \brief Load PCM data of a wave file
/// \param szFile The file path
/// \param pBuffer The buffer pointer
/// \param size The size of the buffer
/// \param frequency The frequency of the sound
/// \param format The audio format
/// \return True or false
bool AudioLoader::LoadWave(const char * szFile, ALuint * pBuffer, ALsizei * pSize, ALsizei * pFrequency, ALenum * pFormat)
{
    FILE * soundFile = nullptr;
    wave::Header waveHeader {};
    wave::Format waveFormat {};
    wave::Data   waveData   {};

    unsigned char* data;

    soundFile = fopen(szFile, "rb");
    if (!soundFile)
    {
        Logger::LogError("Unable to open the following file : %s", szFile);
        return false;
    }

    fread(&waveHeader, sizeof(wave::Header), 1, soundFile);

    // TODO : Optimize
    if ((waveHeader.chunkID[0] != 'R' || waveHeader.chunkID[1] != 'I' || waveHeader.chunkID[2] != 'F' || waveHeader.chunkID[3] != 'F') &&
        (waveHeader.format[0]  != 'W' || waveHeader.format[1]  != 'A' || waveHeader.format[2]  != 'V' || waveHeader.format[3]  != 'E'))
    {
        Logger::LogError("Invalid riff/wave header for the file : %s", szFile);
        fclose(soundFile);
        return false;
    }

    fread(&waveFormat, sizeof(wave::Format), 1, soundFile);

    // TODO : Optimize
    if (waveFormat.subChunkID[0] != 'f' || waveFormat.subChunkID[1] != 'm' || waveFormat.subChunkID[2] != 't' || waveFormat.subChunkID[3] != ' ')
    {
        Logger::LogError("Invalid wave header for the file : %s", szFile);
        fclose(soundFile);
        return false;
    }

    if (waveFormat.subChunkSize > 16)
        fseek(soundFile, sizeof(short), SEEK_CUR);

    fread(&waveData, sizeof(wave::Data), 1, soundFile);

    if (waveData.subChunkID[0] != 'd' || waveData.subChunkID[1] != 'a' || waveData.subChunkID[2] != 't' || waveData.subChunkID[3] != 'a')
    {
        Logger::LogError("Invalid wave header for the file : %s", szFile);
        fclose(soundFile);
        return false;
    }

    data = new unsigned char[waveData.subChunk2Size];

    if (!fread(data, (size_t)waveData.subChunk2Size, 1, soundFile))
    {
        Logger::LogError("Invalid wave data for the file : %s", szFile);
        fclose(soundFile);
        return false;
    }

    *pSize      = waveData.subChunk2Size;
    *pFrequency = waveFormat.sampleRate;

    if (waveFormat.numChannels == 1)
    {
        if      (waveFormat.bitsPerSample == 8 ) *pFormat = AL_FORMAT_MONO8;
        else if (waveFormat.bitsPerSample == 16) *pFormat = AL_FORMAT_MONO16;
    }
    else if (waveFormat.numChannels == 2)
    {
        if      (waveFormat.bitsPerSample == 8 ) *pFormat = AL_FORMAT_STEREO8;
        else if (waveFormat.bitsPerSample == 16) *pFormat = AL_FORMAT_STEREO16;
    }

    alGenBuffers(1, pBuffer);
    alBufferData(*pBuffer, *pFormat, (void*)data, *pSize, *pFrequency);

    delete[] data;

    fclose(soundFile);
    return true;
}

} // !namespace