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

/// \file       Chunk.cpp
/// \date       11/02/2018
/// \project    Cardinal Engine
/// \package    World
/// \author     Vincent STEHLY--CALISTO

#include <iostream>
#include "World/Chunk/Chunk.hpp"

/// \brief Constructor
Chunk::Chunk()
{
    // TODO
}

/// \brief Destructor
Chunk::~Chunk() // NOLINT
{
    // TODO
}

void Chunk::Initialize(int zz)
{
    Generate(zz);
    BatchChunk();
}

void Chunk::Generate(int zz)
{
    for(unsigned x = 0; x < WorldSettings::s_chunkSize; ++x) // NOLINT
    {
        for (unsigned y = 0; y < WorldSettings::s_chunkSize; ++y)
        {
            int maxZ = -1;
            for (unsigned z = 0; z < WorldSettings::s_chunkSize; ++z)
            {
                if(m_cubes[x][y][z].GetType() != ByteCube::EType::Air)
                {
                    maxZ = z;
                }

                if(zz * WorldSettings::s_chunkSize + z  <= 16 && m_cubes[x][y][z].GetType() != ByteCube::EType::Air)
                {
                    int tz = zz * WorldSettings::s_chunkSize + z;

                    float ratio = (1.0f - (tz / 16.0f)) * 100.0f;

                    int rz = rand() % 100;

                    if(ratio > rz)
                        m_cubes[x][y][z].SetType(ByteCube::EType::Rock);
                }
            }

            if(maxZ != -1)
            {
                m_cubes[x][y][maxZ].SetType(ByteCube::EType::Grass);

                if(maxZ + 1 < WorldSettings::s_chunkSize)
                {
                    if(m_cubes[x][y][maxZ + 1].GetType() == ByteCube::EType::Air)
                    {
                        int rgrass = rand() % 5;
                        if(rgrass > 3)
                        {
                            m_cubes[x][y][maxZ + 1].SetType(ByteCube::EType::Grass1);
                        }
                    }
                }
            }

        }
    }
}

void Chunk::BatchChunk()
{
    m_terrainRenderer.Batch(m_cubes);
    m_grassRenderer.Batch(m_cubes);
}

