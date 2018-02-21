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

/// \file       WorldSettings.hpp
/// \date       15/02/2018
/// \project    Cardinal Engine
/// \package    World
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_WORLD_SETTINGS_HPP__
#define CARDINAL_ENGINE_WORLD_SETTINGS_HPP__

#include "Runtime/Platform/Configuration/Type.hh"

/// \brief Anonymous namespace to avoid duplicated declaration
namespace
{

/// \class WorldSettings
/// \brief Stores world global settings
class WorldSettings
{
public:

    static const uint s_chunkSize;
    static const uint s_chunkBlockCount;
    static const uint s_chunkUVsCount;
    static const uint s_chunkVertexCount;

    static const uint s_matSize;
    static const uint s_matHeight;
    static const uint s_matSizeCubes;
    static const uint s_matHeightCubes;

    static const float s_textureStep;
};

/* static */  const uint WorldSettings::s_chunkSize        = 16;
/* static */  const uint WorldSettings::s_chunkBlockCount  = 16 * 16 * 16;
/* static */  const uint WorldSettings::s_chunkUVsCount    = WorldSettings::s_chunkBlockCount * 24;
/* static */  const uint WorldSettings::s_chunkVertexCount = WorldSettings::s_chunkBlockCount * 36;

/* static */  const uint WorldSettings::s_matSize        = 10;
/* static */  const uint WorldSettings::s_matHeight      = 10;
/* static */  const uint WorldSettings::s_matSizeCubes   = WorldSettings::s_matSize * WorldSettings::s_chunkSize;
/* static */  const uint WorldSettings::s_matHeightCubes = WorldSettings::s_matHeight * WorldSettings::s_chunkSize;

/* static */  const float WorldSettings::s_textureStep = 1.0f / 16.0f;
}

#endif // !CARDINAL_ENGINE_WORLD_SETTINGS_HPP__
