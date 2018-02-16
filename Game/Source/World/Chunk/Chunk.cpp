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

void Chunk::Initialize(int zz, glm::vec3 const& position)
{
    Generate(zz);
    BatchChunk(position);
}

bool Chunk::IsZ7Free(int x, int y, int z)
{
    if(z + 7 >= WorldSettings::s_chunkSize)
    {
        return false;
    }

    if(m_cubes[x][y][z + 1].GetType() == ByteCube::EType::Air &&
       m_cubes[x][y][z + 2].GetType() == ByteCube::EType::Air &&
       m_cubes[x][y][z + 3].GetType() == ByteCube::EType::Air &&
       m_cubes[x][y][z + 4].GetType() == ByteCube::EType::Air &&
       m_cubes[x][y][z + 5].GetType() == ByteCube::EType::Air &&
       m_cubes[x][y][z + 6].GetType() == ByteCube::EType::Air &&
       m_cubes[x][y][z + 7].GetType() == ByteCube::EType::Air)
    {
        return true;
    }
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
                    bool grass = false;
                    if(m_cubes[x][y][maxZ + 1].GetType() == ByteCube::EType::Air)
                    {
                        int rgrass = rand() % 20;
                        if(rgrass >= 15)
                        {
                            grass = true;
                            m_cubes[x][y][maxZ + 1].SetType(ByteCube::EType::Grass1);
                        }
                    }

                    if(!grass)
                    {
                        if(IsZ7Free(x, y, maxZ))
                        {
                            int rgrass = rand() % 200;
                            if(rgrass >= 180)
                            {
                                m_cubes[x][y][maxZ + 1].SetType(ByteCube::EType::Wood1);
                                m_cubes[x][y][maxZ + 2].SetType(ByteCube::EType::Wood1);
                                m_cubes[x][y][maxZ + 3].SetType(ByteCube::EType::Wood1);
                                m_cubes[x][y][maxZ + 4].SetType(ByteCube::EType::Wood1);
                                m_cubes[x][y][maxZ + 5].SetType(ByteCube::EType::Wood1);

                                m_cubes[x][y][maxZ + 6].SetType(ByteCube::EType::Leaf1);
                                m_cubes[x][y][maxZ + 7].SetType(ByteCube::EType::Leaf1);




                                if(x - 1 < WorldSettings::s_chunkSize)
                                {
                                    m_cubes[x - 1][y][maxZ + 5].SetType(ByteCube::EType::Leaf1);
                                    m_cubes[x - 1][y][maxZ + 6].SetType(ByteCube::EType::Leaf1);
                                    m_cubes[x - 1][y][maxZ + 7].SetType(ByteCube::EType::Leaf1);
                                }

                                if(x - 2 < WorldSettings::s_chunkSize)
                                {
                                    m_cubes[x - 2][y][maxZ + 5].SetType(ByteCube::EType::Leaf1);
                                    m_cubes[x - 2][y][maxZ + 6].SetType(ByteCube::EType::Leaf1);
                                    m_cubes[x - 2][y][maxZ + 7].SetType(ByteCube::EType::Leaf1);
                                }

                                if(y - 1 < WorldSettings::s_chunkSize)
                                {
                                    m_cubes[x][y - 1][maxZ + 5].SetType(ByteCube::EType::Leaf1);
                                    m_cubes[x][y - 1][maxZ + 6].SetType(ByteCube::EType::Leaf1);
                                    m_cubes[x][y - 1][maxZ + 7].SetType(ByteCube::EType::Leaf1);
                                }

                                if(y - 2 < WorldSettings::s_chunkSize)
                                {
                                    m_cubes[x][y - 2][maxZ + 5].SetType(ByteCube::EType::Leaf1);
                                    m_cubes[x][y - 2][maxZ + 6].SetType(ByteCube::EType::Leaf1);
                                    m_cubes[x][y - 2][maxZ + 7].SetType(ByteCube::EType::Leaf1);
                                }

                                if(x + 1 < WorldSettings::s_chunkSize)
                                {
                                    m_cubes[x + 1][y][maxZ + 5].SetType(ByteCube::EType::Leaf1);
                                    m_cubes[x + 1][y][maxZ + 6].SetType(ByteCube::EType::Leaf1);
                                    m_cubes[x + 1][y][maxZ + 7].SetType(ByteCube::EType::Leaf1);
                                }

                                if(x + 2 < WorldSettings::s_chunkSize)
                                {
                                    m_cubes[x + 2][y][maxZ + 5].SetType(ByteCube::EType::Leaf1);
                                    m_cubes[x + 2][y][maxZ + 6].SetType(ByteCube::EType::Leaf1);
                                    m_cubes[x + 2][y][maxZ + 7].SetType(ByteCube::EType::Leaf1);
                                }

                                if(y + 1 < WorldSettings::s_chunkSize)
                                {
                                    m_cubes[x][y + 1][maxZ + 5].SetType(ByteCube::EType::Leaf1);
                                    m_cubes[x][y + 1][maxZ + 6].SetType(ByteCube::EType::Leaf1);
                                    m_cubes[x][y + 1][maxZ + 7].SetType(ByteCube::EType::Leaf1);
                                }

                                if(y + 2 < WorldSettings::s_chunkSize)
                                {
                                    m_cubes[x][y + 2][maxZ + 5].SetType(ByteCube::EType::Leaf1);
                                    m_cubes[x][y + 2][maxZ + 6].SetType(ByteCube::EType::Leaf1);
                                    m_cubes[x][y + 2][maxZ + 7].SetType(ByteCube::EType::Leaf1);
                                }



                            }


                        }
                    }
                }
            }

        }
    }

   // m_terrainRenderer.Batch(m_cubes);
   // m_grassRenderer.Batch(m_cubes, glm::vec3(1.0f));
}

void Chunk::BatchChunk(glm::vec3 const& position)
{
    m_terrainRenderer.Batch(m_cubes);
    m_grassRenderer.Batch(m_cubes, position);
}

