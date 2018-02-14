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

/// \file       UVManager.cpp
/// \date       14/02/2018
/// \project    Cardinal Engine
/// \package    World/Cube
/// \author     Vincent STEHLY--CALISTO

#include "World/Cube/UVManager.hpp"

/// \brief Face order
///        Left, Front, Right, Back, Top, Bottom
/* static */ unsigned char UVManager::UV[6][12] =
{
        { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, ///< Air
        { 2, 15,  2, 15,  2, 15,  2, 15,  2, 15,  2, 15}, ///< Dirt
        { 3, 15,  3, 15,  3, 15,  3, 15,  0, 15,  2, 15}, ///< Grass
        { 0 }, ///< Water
        { 0 }, ///< Lava
        { 8, 11,  8, 11,  8, 11,  8, 11,  8, 11,  8, 11}  ///< Rock
};