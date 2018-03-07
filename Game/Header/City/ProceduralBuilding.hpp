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

/// \file       ProceduralBuilding.hpp
/// \date       07/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Sound
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_PROCEDURAL_BUILDING_HPP
#define CARDINAL_ENGINE_PROCEDURAL_BUILDING_HPP

#include "World/Cube/ByteCube.hpp"

#define BUILDING_MAX_SIZE   16
#define BUILDING_MAX_HEIGHT 16

/// \class ProceduralBuilding
/// \brief Procedural building system using sockets
class ProceduralBuilding
{
public:


private:

    ByteCube m_building[BUILDING_MAX_SIZE][BUILDING_MAX_SIZE][BUILDING_MAX_HEIGHT];
};

#endif // !CARDINAL_ENGINE_PROCEDURAL_BUILDING_HPP