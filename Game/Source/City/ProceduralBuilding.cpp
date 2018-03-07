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

/// \file       ProceduralBuilding.cpp
/// \date       07/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Sound
/// \author     Vincent STEHLY--CALISTO

#include <vector>
#include "Glm/glm/glm.hpp"
#include "City/ProceduralBuilding.hpp"

/// \brief Constructor
ProceduralBuilding::ProceduralBuilding()
{
    Initialize();
}

/// \brief Initializes the building before generation
void ProceduralBuilding::Initialize()
{
    for(int x = 0; x < BUILDING_MAX_SIZE; ++x) // NOLINT
    {
        for(int y = 0; y < BUILDING_MAX_SIZE; ++y)
        {
            for(int z = 0; z < BUILDING_MAX_HEIGHT; ++z)
            {
                m_building[x][y][z].Enable();
                m_building[x][y][z].SetType(ByteCube::EType::Air);
            }
        }
    }
}

/// \brief Generates the building
void ProceduralBuilding::Generate()
{
    // TMP
    int l = 16;
    int t = 10;
    int h = 14;

    // Floor
    for(int x = 0; x < l; ++x) // NOLINT
    {
        for(int y = 0; y < t; ++y)
        {
            m_building[x][y][0].SetType(ByteCube::EType::Rock);
        }
    }

    // Walls 1
    for(int x = 0; x < l; ++x) // NOLINT
    {
        for(int z = 0; z < h; ++z)
        {
            m_building[x][0][0].SetType(ByteCube::EType::Rock);
        }
    }

    // Walls 2
    for(int x = 0; x < l; ++x) // NOLINT
    {
        for(int z = 0; z < h; ++z)
        {
            m_building[x][t - 1][z].SetType(ByteCube::EType::Rock);
        }
    }

    // Walls 3
    for(int y = 0; y < t; ++y) // NOLINT
    {
        for(int z = 0; z < h; ++z)
        {
            m_building[0][y][z].SetType(ByteCube::EType::Rock);
        }
    }

    // Walls 4
    for(int y = 0; y < t; ++y) // NOLINT
    {
        for(int z = 0; z < h; ++z)
        {
            m_building[l - 1][y][z].SetType(ByteCube::EType::Rock);
        }
    }
}

/// \brief Batch geometry
void ProceduralBuilding::Batch()
{
    std::vector <glm::vec3> vertices;
    std::vector <glm::vec3> normals;
    std::vector <glm::vec2> uvs;


}