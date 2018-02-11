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

#include <chrono>
#include <iostream>
#include <Runtime/Header/Rendering/Optimization/VBOIndexer.hpp>
#include "World/Chunk.hpp"
#include "Core/Debug/Logger.hpp"

/* static */ std::vector<glm::vec3>      Chunk::s_chunkVertexBuffer;
/* static */ std::vector<glm::vec3>      Chunk::s_chunkColorBuffer;

/* static */ std::vector<unsigned short> Chunk::s_chunkIndexesBuffer;
/* static */ std::vector<glm::vec3>      Chunk::s_chunkIndexedVertexBuffer;
/* static */ std::vector<glm::vec3>      Chunk::s_chunkIndexedColorBuffer;

/* static */ const float Chunk::s_triangles[108] =
{

        -1.0f, -1.0f,  1.0f,    -1.0f,  1.0f, -1.0f,     -1.0f, -1.0f, -1.0f,    -1.0f, -1.0f,  1.0f,    -1.0f,  1.0f,  1.0f,    -1.0f,  1.0f, -1.0f, /* Face 1 */
        -1.0f,  1.0f,  1.0f,     1.0f,  1.0f, -1.0f,     -1.0f,  1.0f, -1.0f,    -1.0f,  1.0f,  1.0f,     1.0f,  1.0f,  1.0f,     1.0f,  1.0f, -1.0f, /* Face 2 */
         1.0f,  1.0f,  1.0f,     1.0f, -1.0f, -1.0f,      1.0f,  1.0f, -1.0f,     1.0f,  1.0f,  1.0f,     1.0f, -1.0f,  1.0f,     1.0f, -1.0f, -1.0f, /* Face 3 */
         1.0f, -1.0f,  1.0f,    -1.0f, -1.0f, -1.0f,      1.0f, -1.0f, -1.0f,     1.0f, -1.0f,  1.0f,    -1.0f, -1.0f,  1.0f,    -1.0f, -1.0f, -1.0f, /* Face 4 */
        -1.0f, -1.0f,  1.0f,     1.0f, -1.0f,  1.0f,      1.0f,  1.0f,  1.0f,     1.0f,  1.0f,  1.0f,    -1.0f,  1.0f,  1.0f,    -1.0f, -1.0f , 1.0f, /* Face 5 */
         1.0f,  1.0f, -1.0f,     1.0f, -1.0f, -1.0f,     -1.0f, -1.0f, -1.0f,    -1.0f, -1.0f, -1.0f,    -1.0f,  1.0f, -1.0f,     1.0f,  1.0f, -1.0f  /* Face 5 */
};

/// \brief Static initialization of buffers
void Chunk::InitializeBuffers()
{
    if(s_chunkVertexBuffer.size()  != s_vertexCount)
    {
        s_chunkVertexBuffer = std::vector<glm::vec3>(s_vertexCount);
        s_chunkColorBuffer  = std::vector<glm::vec3>(s_vertexCount);

        s_chunkIndexesBuffer.reserve       (s_vertexCount);
        s_chunkIndexedColorBuffer.reserve  (s_colorCount);
        s_chunkIndexedVertexBuffer.reserve (s_vertexCount);

        cardinal::Logger::LogInfo("Chunk static buffer initialized");
    }
}

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

void Chunk::Initialize()
{
    // TMP
    for(int x = 0; x < s_chunkSize; ++x)
    {
        for(int y = 0; y < s_chunkSize; ++y)
        {
            for(int z = 0; z< s_chunkSize; ++z)
            {
                int color = rand() % 4;

                if(color == 0)      m_cubes[x][y][z].SetType(Cube::EType::Dirt);
                else if(color == 1) m_cubes[x][y][z].SetType(Cube::EType::Grass);
                else if(color == 2) m_cubes[x][y][z].SetType(Cube::EType::Water);
                else if(color == 3) m_cubes[x][y][z].SetType(Cube::EType::Grass);
                else
                {
                    m_cubes[x][y][z].SetType(Cube::EType::Water);
                }
            }
        }
    }

    Batch();
}

/// \brief Builds the chunk vao
void Chunk::Batch()
{
    auto startT = std::chrono::steady_clock::now();

    glm::vec3 red  (1.0f, 0.0f, 0.0f);
    glm::vec3 green(0.0f, 1.0f, 0.0f);
    glm::vec3 blue (0.0f, 0.0f, 1.0f);

    // Always resize to the max capacity
    // to not reallocate the vector memory
    s_chunkVertexBuffer.resize(s_vertexCount);
    s_chunkColorBuffer.resize (s_vertexCount);

    // Static batching
    size_t vertexIndex = 0;
    float half         = Cube::s_CubeSize / 2.0f;

    for(unsigned x = 0; x < s_chunkSize; ++x) // NOLINT
    {
        for(unsigned y = 0; y < s_chunkSize; ++y)
        {
            for(unsigned z = 0; z < s_chunkSize; ++z)
            {
                // Pre-conditions
                Cube & cube = m_cubes[x][y][z];
                if(!cube.IsVisible() || !cube.IsSolid())
                {
                    continue;
                }

                // Gets cube color
                glm::vec3 color;
                switch(cube.GetType())
                {
                    case Cube::EType::Dirt:  color = red;   break;
                    case Cube::EType::Grass: color = green; break;
                    case Cube::EType::Water: color = blue;  break;
                    default: break;
                }

                // Face by face batching
                for(unsigned nFace = 0; nFace < 6; ++nFace)
                {
                    // Checks for face visibility
                    // Order :
                    if((nFace == 0 && x != 0               && m_cubes[x - 1][y][z].IsSolid()) ||
                       (nFace == 2 && x != s_chunkSize - 1 && m_cubes[x + 1][y][z].IsSolid()) ||
                       (nFace == 3 && y != 0               && m_cubes[x][y - 1][z].IsSolid()) ||
                       (nFace == 1 && y != s_chunkSize - 1 && m_cubes[x][y + 1][z].IsSolid()) ||
                       (nFace == 5 && z != 0               && m_cubes[x][y][z - 1].IsSolid()) ||
                       (nFace == 4 && z != s_chunkSize - 1 && m_cubes[x][y][z + 1].IsSolid()))
                    {
                        continue;
                    }

                    glm::vec3 offset
                    (
                        x * Cube::s_CubeSize,
                        y * Cube::s_CubeSize,
                        z * Cube::s_CubeSize
                    );

                    size_t faceIndex = nFace * 18;

                    // TODO : SIMD
                    s_chunkColorBuffer [vertexIndex]   = color;
                    s_chunkVertexBuffer[vertexIndex].x = s_triangles[faceIndex +  0] * half + offset.x;
                    s_chunkVertexBuffer[vertexIndex].y = s_triangles[faceIndex +  1] * half + offset.y;
                    s_chunkVertexBuffer[vertexIndex].z = s_triangles[faceIndex +  2] * half + offset.z;

                    vertexIndex += 1;
                    s_chunkColorBuffer [vertexIndex]   = color;
                    s_chunkVertexBuffer[vertexIndex].x = s_triangles[faceIndex +  3] * half + offset.x;
                    s_chunkVertexBuffer[vertexIndex].y = s_triangles[faceIndex +  4] * half + offset.y;
                    s_chunkVertexBuffer[vertexIndex].z = s_triangles[faceIndex +  5] * half + offset.z;

                    vertexIndex += 1;
                    s_chunkColorBuffer [vertexIndex]   = color;
                    s_chunkVertexBuffer[vertexIndex].x = s_triangles[faceIndex +  6] * half + offset.x;
                    s_chunkVertexBuffer[vertexIndex].y = s_triangles[faceIndex +  7] * half + offset.y;
                    s_chunkVertexBuffer[vertexIndex].z = s_triangles[faceIndex +  8] * half + offset.z;

                    vertexIndex += 1;
                    s_chunkColorBuffer [vertexIndex]   = color;
                    s_chunkVertexBuffer[vertexIndex].x = s_triangles[faceIndex +  9] * half + offset.x;
                    s_chunkVertexBuffer[vertexIndex].y = s_triangles[faceIndex + 10] * half + offset.y;
                    s_chunkVertexBuffer[vertexIndex].z = s_triangles[faceIndex + 11] * half + offset.z;

                    vertexIndex += 1;
                    s_chunkColorBuffer [vertexIndex]   = color;
                    s_chunkVertexBuffer[vertexIndex].x = s_triangles[faceIndex + 12] * half + offset.x;
                    s_chunkVertexBuffer[vertexIndex].y = s_triangles[faceIndex + 13] * half + offset.y;
                    s_chunkVertexBuffer[vertexIndex].z = s_triangles[faceIndex + 14] * half + offset.z;

                    vertexIndex += 1;
                    s_chunkColorBuffer [vertexIndex]   = color;
                    s_chunkVertexBuffer[vertexIndex].x = s_triangles[faceIndex + 15] * half + offset.x;
                    s_chunkVertexBuffer[vertexIndex].y = s_triangles[faceIndex + 16] * half + offset.y;
                    s_chunkVertexBuffer[vertexIndex].z = s_triangles[faceIndex + 17] * half + offset.z;

                    vertexIndex += 1;
                }
            }
        }
    }

    s_chunkVertexBuffer.resize(vertexIndex);
    s_chunkColorBuffer.resize (vertexIndex);

    // Indexing
    cardinal::VBOIndexer::Index(s_chunkVertexBuffer, s_chunkColorBuffer, s_chunkIndexesBuffer, s_chunkIndexedVertexBuffer, s_chunkIndexedColorBuffer);
    m_renderer.Initialize(s_chunkIndexesBuffer, s_chunkIndexedVertexBuffer, s_chunkIndexedColorBuffer);

    auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startT);
    auto elapsedUs = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - startT);
    std::cout << "Batched vertices : " << s_chunkVertexBuffer.size() << std::endl;
    std::cout << "Chunk batched in " << elapsedMs.count() << " ms" << std::endl;
    std::cout << "Chunk batched in " << elapsedUs.count() << " us" << std::endl;
    std::cout << "Output vertices : " << s_chunkIndexedVertexBuffer.size() << std::endl;

    s_chunkVertexBuffer.clear();
    s_chunkColorBuffer.clear();

    s_chunkIndexesBuffer.clear();
    s_chunkIndexedColorBuffer.clear();
    s_chunkIndexedVertexBuffer.clear();
}

/// \brief Returns the mesh renderer
cardinal::MeshRenderer *Chunk::GetMeshRenderer()
{
    return &m_renderer;
}

