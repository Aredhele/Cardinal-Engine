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

/// \file       World.inl
/// \date       17/02/2018
/// \project    Cardinal Engine
/// \package    World/Impl
/// \author     Vincent STEHLY--CALISTO

/// \brief  Returns the cube at the given coordinates
/// \param  x The x coordinate
/// \param  y The y coordinate
/// \param  z The z coordinate
/// \return A pointer on the cube, could be nullptr
inline ByteCube * World::GetCube(int x, int y, int z)
{
    ASSERT_GT(x, 0);
    ASSERT_GT(y, 0);
    ASSERT_GT(z, 0);

    ASSERT_LT(x, WorldSettings::s_matSizeCubes);
    ASSERT_LT(y, WorldSettings::s_matSizeCubes);
    ASSERT_LT(z, WorldSettings::s_matHeightCubes);

    // Coordinates are conforms
    //return &(m_chunks[x /  WorldSettings::s_chunkSize]
    //                 [y /  WorldSettings::s_chunkSize]
    //                 [z /  WorldSettings::s_chunkSize]->m_cubes[x % WorldSettings::s_chunkSize]
    //                                                           [y % WorldSettings::s_chunkSize]
    //                                                           [z % WorldSettings::s_chunkSize]);
}
