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

/// \file       SoundEngine.hpp
/// \date       27/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Sound
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_SOUND_ENGINE_HPP__
#define CARDINAL_ENGINE_SOUND_ENGINE_HPP__

#include "OpenAL/include/AL/al.h"
#include "OpenAL/include/AL/alc.h"

/// \namespace cardinal
namespace cardinal
{

/// \class SoundEngine
/// \brief The sound engine using OpenAL
class SoundEngine
{
public:

private:

    friend class Engine;

    /// \brief Initializes the sound engine
    /// \return True or false
    bool Initialize();

    /// \brief Shutdowns the sound engine
    void Shutdown();

private:

    static SoundEngine * s_pInstance;

    ALCdevice          * m_pDevice;
    ALCcontext         * m_pContext;
};

} // !namespace

#endif // !CARDINAL_ENGINE_SOUND_ENGINE_HPP__