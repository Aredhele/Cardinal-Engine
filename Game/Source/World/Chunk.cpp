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
#include "Runtime/Rendering/Optimization/VBOIndexer.hpp"
#include "Runtime/Core/Maths/Noise/PerlinNoise.hpp"
#include "World/Chunk.hpp"
#include "Runtime/Core/Debug/Logger.hpp"
#include "World/World.hpp"


/* static */ std::vector<glm::vec3>      Chunk::s_chunkVertexBuffer;
/* static */ std::vector<glm::vec2>      Chunk::s_chunkUVsBuffer;

/* static */ std::vector<unsigned short> Chunk::s_chunkIndexesBuffer;
/* static */ std::vector<glm::vec3>      Chunk::s_chunkIndexedVertexBuffer;
/* static */ std::vector<glm::vec2>      Chunk::s_chunkIndexedUVsBuffer;

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
        s_chunkUVsBuffer    = std::vector<glm::vec2>(s_vertexCount);

        s_chunkIndexesBuffer.reserve       (s_vertexCount);
        s_chunkIndexedUVsBuffer.reserve    (s_uvsCount);
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
    Generate();
    Batch();
}

void Chunk::Generate()
{
    /*NYPerlin perlin;

    float TweakA = 5.0f;
    float TweakB = 2.0f;
    float TweakC = 3.0f;

    // 2D terrain
    for(int x = 0; x < s_chunkSize; ++x)
    {
        for(int y = 0; y < s_chunkSize; ++y)
        {
            for(int z = 0; z < s_chunkSize; ++z)
            {
                Cube & cube = m_cubes[x][y][z];

                float modif = 0.04;

                float sample = perlin.sample(modif*x, modif*y, modif*z);

                sample /= pow((float)z / (float)s_chunkSize, TweakA) / TweakB + TweakC;

                glTranslated(x*Cube::s_CubeSize, y*Cube::s_CubeSize, z*Cube::s_CubeSize);
                if (sample < 0.5f)
                {
                    cube.SetType(Cube::EType::Water);
                    cube.SetVisible(true);
                }
                else
                {
                    cube.SetType(Cube::EType::Dirt);
                    cube.SetVisible(true);
                }
            }

            //float z = cardinal::PerlinNoise::Sample2D(tr.x + x, tr.z + y, 40.0f) * 16.0f;
            //SetCol(x, y, static_cast<int>(z));
        }
    }*/
}

void Chunk::SetCol(int x, int y, int z)
{
    z += 8;
    for(int i = 0; i < s_chunkSize; ++i)
    {
        if(i < z)
        {
            m_cubes[x][i][y].SetType(Cube::EType::Dirt);
        }
        else if(i == z)
        {

            m_cubes[x][i][y].SetType(Cube::EType::Grass);

        }
        else
        {
            m_cubes[x][i][y].SetType(Cube::EType::Air);
        }
    }
}

/// \brief Builds the chunk vao
void Chunk::Batch()
{
    auto startT = std::chrono::steady_clock::now();

    glm::vec3 red  (1.0f, 0.0f, 0.0f);
    glm::vec3 green(0.0f, 1.0f, 0.0f);
    glm::vec3 blue (0.0f, 0.0f, 1.0f);

    float textureStep = 1.0f / 16.0f;

    glm::vec2 uv1;
    glm::vec2 uv2;
    glm::vec2 uv3;
    glm::vec2 uv4;

    // Always resize to the max capacity
    // to not reallocate the vector memory
    s_chunkVertexBuffer.resize(s_vertexCount);
    s_chunkUVsBuffer.resize (s_vertexCount);

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

                // Sets cube uvs
                glm::vec3 color;
                switch(cube.GetType())
                {
                    case Cube::EType::Dirt:
                    {
                        uv1 = glm::vec2(2.0f * textureStep, 15.0f * textureStep);
                        uv2 = glm::vec2(3.0f * textureStep, 15.0f * textureStep);
                        uv3 = glm::vec2(3.0f * textureStep, 1.0f);
                        uv4 = glm::vec2(2.0f * textureStep, 1.0f);

                    }   break;
                    case Cube::EType::Grass:
                    {
                        uv1 = glm::vec2(0.0f, 15.0f * textureStep);
                        uv2 = glm::vec2(textureStep, 15.0f * textureStep);
                        uv3 = glm::vec2(textureStep, 1.0f);
                        uv4 = glm::vec2(0.0f, 1.0f);
                        break;
                    }
                    case Cube::EType::Water:
                    {
                        uv1 = glm::vec2(0.0f, 15.0f * textureStep);
                        uv2 = glm::vec2(textureStep, 15.0f * textureStep);
                        uv3 = glm::vec2(textureStep, 1.0f);
                        uv4 = glm::vec2(0.0f, 1.0f);
                        break;
                    }
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
                    s_chunkUVsBuffer   [vertexIndex]   = uv1;
                    s_chunkVertexBuffer[vertexIndex].x = s_triangles[faceIndex +  0] * half + offset.x;
                    s_chunkVertexBuffer[vertexIndex].y = s_triangles[faceIndex +  1] * half + offset.y;
                    s_chunkVertexBuffer[vertexIndex].z = s_triangles[faceIndex +  2] * half + offset.z;

                    vertexIndex += 1;
                    s_chunkUVsBuffer [vertexIndex]     = uv2;
                    s_chunkVertexBuffer[vertexIndex].x = s_triangles[faceIndex +  3] * half + offset.x;
                    s_chunkVertexBuffer[vertexIndex].y = s_triangles[faceIndex +  4] * half + offset.y;
                    s_chunkVertexBuffer[vertexIndex].z = s_triangles[faceIndex +  5] * half + offset.z;

                    vertexIndex += 1;
                    s_chunkUVsBuffer [vertexIndex]     = uv3;
                    s_chunkVertexBuffer[vertexIndex].x = s_triangles[faceIndex +  6] * half + offset.x;
                    s_chunkVertexBuffer[vertexIndex].y = s_triangles[faceIndex +  7] * half + offset.y;
                    s_chunkVertexBuffer[vertexIndex].z = s_triangles[faceIndex +  8] * half + offset.z;

                    vertexIndex += 1;
                    s_chunkUVsBuffer [vertexIndex]     = uv3;
                    s_chunkVertexBuffer[vertexIndex].x = s_triangles[faceIndex +  9] * half + offset.x;
                    s_chunkVertexBuffer[vertexIndex].y = s_triangles[faceIndex + 10] * half + offset.y;
                    s_chunkVertexBuffer[vertexIndex].z = s_triangles[faceIndex + 11] * half + offset.z;

                    vertexIndex += 1;
                    s_chunkUVsBuffer [vertexIndex]     = uv4;
                    s_chunkVertexBuffer[vertexIndex].x = s_triangles[faceIndex + 12] * half + offset.x;
                    s_chunkVertexBuffer[vertexIndex].y = s_triangles[faceIndex + 13] * half + offset.y;
                    s_chunkVertexBuffer[vertexIndex].z = s_triangles[faceIndex + 14] * half + offset.z;

                    vertexIndex += 1;
                    s_chunkUVsBuffer [vertexIndex]     = uv1;
                    s_chunkVertexBuffer[vertexIndex].x = s_triangles[faceIndex + 15] * half + offset.x;
                    s_chunkVertexBuffer[vertexIndex].y = s_triangles[faceIndex + 16] * half + offset.y;
                    s_chunkVertexBuffer[vertexIndex].z = s_triangles[faceIndex + 17] * half + offset.z;

                    vertexIndex += 1;
                }
            }
        }
    }

    s_chunkVertexBuffer.resize(vertexIndex);
    s_chunkUVsBuffer.resize (vertexIndex);

    // Indexing
    cardinal::VBOIndexer::Index(s_chunkVertexBuffer, s_chunkUVsBuffer, s_chunkIndexesBuffer, s_chunkIndexedVertexBuffer, s_chunkIndexedUVsBuffer);
    m_renderer.Initialize(s_chunkIndexesBuffer, s_chunkIndexedVertexBuffer, s_chunkIndexedUVsBuffer);

    auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - startT);
    auto elapsedUs = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - startT);
   // std::cout << "Batched vertices : " << s_chunkVertexBuffer.size() << std::endl;
   // std::cout << "Chunk batched in " << elapsedMs.count() << " ms" << std::endl;
   // std::cout << "Chunk batched in " << elapsedUs.count() << " us" << std::endl;
   // std::cout << "Output vertices : " << s_chunkIndexedVertexBuffer.size() << std::endl;

    s_chunkVertexBuffer.clear();
    s_chunkUVsBuffer.clear();

    s_chunkIndexesBuffer.clear();
    s_chunkIndexedUVsBuffer.clear();
    s_chunkIndexedVertexBuffer.clear();
}

/// \brief Returns the mesh renderer
cardinal::MeshRenderer *Chunk::GetMeshRenderer()
{
    return &m_renderer;
}

