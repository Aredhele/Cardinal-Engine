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
/* static */ unsigned char UVManager::UV[19][12] =
{
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, ///< Air
    { 2, 15,  2, 15,  2, 15,  2, 15,  2, 15,  2, 15}, ///< Dirt
    { 3, 15,  3, 15,  3, 15,  3, 15,  0, 15,  2, 15}, ///< Grass
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, ///< Water
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0}, ///< Lava
    { 1, 15,  1, 15,  1, 15,  1, 15,  1, 15,  1, 15}, ///< Rock
    {13, 10, 13, 10,  0,  0,  0,  0,  0,  0,  0,  0}, ///< Grass detail 1
    { 4, 14,  4, 14,  4, 14,  4, 14,  5, 14,  5, 14}, ///< Wood texture 1
    { 4, 12,  4, 12,  4, 12,  4, 12,  4, 12,  4, 12}, ///< Leaf texture 1
    { 0, 13,  0, 13,  0, 13,  0, 13,  0, 13,  0, 13}, ///< Gold
    { 2, 13,  2, 13,  2, 13,  2, 13,  2, 13,  2, 13}, ///< Coal
    { 3, 12,  3, 12,  3, 12,  3, 12,  3, 12,  3, 12}, ///< Redstone
    { 2, 12,  2, 12,  2, 12,  2, 12,  2, 12,  2, 12}, ///< Diamond
    { 1, 13,  1, 13,  1, 13,  1, 13,  1, 13,  1, 13}, ///< Emerald
    { 4, 11,  4, 11,  4, 11,  4, 11,  2, 11,  2, 15}, ///< Snow
    { 1, 14,  1, 14,  1, 14,  1, 14,  1, 14,  1, 14}, ///< Bedrock
    { 2, 14,  2, 14,  2, 14,  2, 14,  2, 14,  2, 14}, ///< Sand
    { 3, 11,  3, 11,  3, 11,  3, 11,  3, 11,  3, 11}, ///< Ice
    { 4, 15,  4, 15,  4, 15,  4, 15,  4, 15,  4, 15}  ///< Wood Plank
};
