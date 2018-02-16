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

/// \file       World.hpp
/// \date       12/02/2018
/// \project    Cardinal Engine
/// \package    TODO
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_WORLD_HPP__
#define CARDINAL_ENGINE_WORLD_HPP__

#include "Runtime/Rendering/RenderingEngine.hpp"
#include "Runtime/Core/Maths/Noise/NYPerlin.hpp"
#include "World/Chunk/Chunk.hpp"
#include "Runtime/Rendering/Debug/Debug.hpp"
#define MAT_SIZE 4 //en nombre de chunks
#define MAT_HEIGHT 3 //en nombre de chunks
#define MAT_SIZE_CUBES (MAT_SIZE * WorldSettings::s_chunkSize)
#define MAT_HEIGHT_CUBES (MAT_HEIGHT * WorldSettings::s_chunkSize)

/// \class  World
/// \brief
class World
{
public :

    Chunk *** m_chunks;
    glm::vec3 position;
    float elapsed = 0.0f;

    ByteCube * GetCube(int x, int y, int z)
    {
        if (x < 0)x = 0;
        if (y < 0)y = 0;
        if (z < 0)z = 0;
        if (x >= MAT_SIZE   * WorldSettings::s_chunkSize)  x = (MAT_SIZE    * WorldSettings::s_chunkSize) - 1;
        if (y >= MAT_SIZE   * WorldSettings::s_chunkSize)  y = (MAT_SIZE    * WorldSettings::s_chunkSize) - 1;
        if (z >= MAT_HEIGHT * WorldSettings::s_chunkSize) z = (MAT_HEIGHT  * WorldSettings::s_chunkSize) - 1;

        return &(m_chunks[x /  WorldSettings::s_chunkSize][y /  WorldSettings::s_chunkSize][z /  WorldSettings::s_chunkSize].m_cubes[x % WorldSettings::s_chunkSize][y %  WorldSettings::s_chunkSize][z %  WorldSettings::s_chunkSize]);
    }

    void UpdateCameraPosition(glm::vec3 const& position, float dt)
    {
       /* elapsed += dt;

        if(elapsed < 0.25f)
        {
            return;
        }

        elapsed = 0.0f;*/

        this->position = position;
        for(int xx = 0; xx < MAT_SIZE; ++xx)
        {
            for(int y = 0; y < MAT_SIZE; ++y)
            {
                for(int z = 0; z < MAT_HEIGHT; ++z)
                {
                  // m_chunks[xx][y][z].BatchChunk(position);
                    cardinal::debug::DrawBox(glm::vec3(
                            (xx * WorldSettings::s_chunkSize * ByteCube::s_cubeSize) + (8.0f * ByteCube::s_cubeSize) - ByteCube::s_cubeSize / 2.0f,
                            ( y * WorldSettings::s_chunkSize * ByteCube::s_cubeSize) + (8.0f * ByteCube::s_cubeSize) - ByteCube::s_cubeSize / 2.0f,
                            ( z * WorldSettings::s_chunkSize * ByteCube::s_cubeSize) + (8.0f * ByteCube::s_cubeSize) - ByteCube::s_cubeSize / 2.0f),
                         16.0f * ByteCube::s_cubeSize,
                         16.0f * ByteCube::s_cubeSize, glm::vec3(1.0f, 0.5f, 0.7f));

                }
            }
        }
    }

    void GenerateWorld(cardinal::RenderingEngine & engine)
    {
        WorldBuffers::Initialize();

        // Allocating chunk
        m_chunks = new Chunk **[MAT_SIZE];
        for(int i = 0; i < MAT_SIZE; ++i)
        {
            m_chunks[i] =  new Chunk *[MAT_SIZE];
            for(int j = 0; j < MAT_SIZE; ++j)
            {
                m_chunks[i][j] = new Chunk[MAT_HEIGHT];
            }
        }



        float TweakA = 16.0f;
        float TweakB = 50.0f;
        float TweakC = 10.0f;


        NYPerlin perlin;
       // float TweakA = 16.0f;
       // float TweakB = 100.0f;
       // float TweakC = 300.0f;

        // 2D terrain
        for(int x = 0; x < MAT_SIZE_CUBES; ++x)
        {
            for(int y = 0; y < MAT_SIZE_CUBES; ++y)
            {
                for(int z = 0; z < MAT_HEIGHT_CUBES; ++z)
                {
                    ByteCube * cube = GetCube(x, y, z);

                    float modif = 0.04;
                    float sample = perlin.sample(modif*x, modif*y, modif*z);


                    sample /= pow((float)z / (float)16, TweakA) / TweakB + TweakC;

                   // glTranslated(x*Cube::s_CubeSize, y*Cube::s_CubeSize, z*Cube::s_CubeSize);
                    if (sample < 0.5f)
                    {
                        cube->SetType(ByteCube::EType::Air);
                        cube->Enable();
                    }
                    else
                    {
                        cube->SetType(ByteCube::EType::Dirt);
                        cube->Enable();
                    }
                }
            }
        }

        for(int xx = 0; xx < MAT_SIZE; ++xx)
        {
            for(int y = 0; y < MAT_SIZE; ++y)
            {
                for(int z = 0; z < MAT_HEIGHT; ++z)
                {
                    m_chunks[xx][y][z].Translate(glm::vec3(xx * 16 * ByteCube::s_cubeSize,
                                                            y * 16 * ByteCube::s_cubeSize,
                                                            z * 16 * ByteCube::s_cubeSize));
                    m_chunks[xx][y][z].Initialize(z, position);
                 //   m_chunks[xx][y][z].RegisterChunk(engine);
                }
            }
        }

        for(int xx = 0; xx < MAT_SIZE; ++xx)
        {
            for(int y = 0; y < MAT_SIZE; ++y)
            {
                for(int z = 0; z < MAT_HEIGHT; ++z)
                {
                    m_chunks[xx][y][z].RegisterChunkSolid(engine);
                }
            }
        }

        for(int xx = 0; xx < MAT_SIZE; ++xx)
        {
            for(int y = 0; y < MAT_SIZE; ++y)
            {
                for(int z = 0; z < MAT_HEIGHT; ++z)
                {
                  m_chunks[xx][y][z].RegisterChunkTransparent(engine);
                }
            }
        }
    }

};

#endif // !CARDINAL_ENGINE_WORLD_HPP__