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

/// \file       EighthBlockRenderer.cpp
/// \date       14/03/2018
/// \project    Cardinal Engine
/// \package    World/Chunk/Renderer
/// \author     Vincent STEHLY--CALISTO

#include <Header/Runtime/Rendering/Shader/Built-in/Unlit/UnlitTextureShader.hpp>
#include <Header/Runtime/Rendering/RenderingEngine.hpp>
#include <Header/Runtime/Rendering/Texture/TextureManager.hpp>
#include <World/Chunk/Chunk.hpp>
#include <Header/Runtime/Rendering/Shader/Built-in/Lit/LitTextureShader.hpp>
#include <Header/Runtime/Rendering/Debug/Debug.hpp>
#include <Header/Runtime/Rendering/Shader/Built-in/Standard/StandardShader.hpp>
#include <World/Chunk/Renderer/EighthBlockRenderer.hpp>
#include "World/Cube/UVManager.hpp"
#include "Runtime/Rendering/Optimization/VBOIndexer.hpp"

/// TODO
EighthBlockRenderer::EighthBlockRenderer()
{
    m_renderer = cardinal::RenderingEngine::AllocateMeshRenderer();
    cardinal::StandardShader * pShader = new cardinal::StandardShader(); // NOLINT
    pShader->SetTexture(cardinal::TextureManager::GetTextureID("Block"));
    m_renderer->SetShader(pShader);
}

/// \brief Static batching for terrain cubes
/// \param pCubes The cubes of the chunk
void EighthBlockRenderer::Batch(ByteCube pCubes[WorldSettings::s_chunkSize][WorldSettings::s_chunkSize][WorldSettings::s_chunkSize], Chunk * neighbors[6])
{
    // Resizing the vector to ensure that the current size
    // is large enough to hold all vertices and UVs
    WorldBuffers::s_chunkVertexBuffer.resize   (WorldSettings::s_chunkVertexCount);
    WorldBuffers::s_chunkNormalBuffer.resize   (WorldSettings::s_chunkVertexCount);
    WorldBuffers::s_chunkUVsBuffer.resize      (WorldSettings::s_chunkVertexCount);

    size_t vertexIndex = 0;
    float half         = ByteCube::s_cubeSize / 2.0f;

    for(uint x = 0; x < WorldSettings::s_chunkSize; ++x) // NOLINT
    {
        for(uint y = 0; y < WorldSettings::s_chunkSize; ++y)
        {
            for(uint z = 0; z < WorldSettings::s_chunkSize; ++z)
            {
                // Pre-conditions
                ByteCube const& cube = pCubes[x][y][z];
                if(!cube.IsVisible() || !cube.IsHeighthBlock())
                {
                    continue;
                }

                // Face by face batching
                unsigned size = WorldSettings::s_chunkSize;
                for(unsigned nFace = 0; nFace < 6; ++nFace)
                {
                    // Offset of the current cube
                    glm::vec3 offset(
                            x * ByteCube::s_cubeSize,
                            y * ByteCube::s_cubeSize,
                            z * ByteCube::s_cubeSize);

                    size_t faceIndex = nFace * 18;

                    float UVx =  UVManager::UV[cube.GetType() >> 1][nFace * 2 + 0] * WorldSettings::s_textureStep;
                    float UVy =  UVManager::UV[cube.GetType() >> 1][nFace * 2 + 1] * WorldSettings::s_textureStep;

                    WorldBuffers::s_chunkUVsBuffer   [vertexIndex].x = UVx + WorldSettings::s_textureStep;
                    WorldBuffers::s_chunkUVsBuffer   [vertexIndex].y = UVy;
                    WorldBuffers::s_chunkNormalBuffer[vertexIndex].x = ByteCube::s_normals [faceIndex + 0];
                    WorldBuffers::s_chunkNormalBuffer[vertexIndex].y = ByteCube::s_normals [faceIndex + 1];
                    WorldBuffers::s_chunkNormalBuffer[vertexIndex].z = ByteCube::s_normals [faceIndex + 2];
                    WorldBuffers::s_chunkVertexBuffer[vertexIndex].x = ByteCube::s_verticesE[faceIndex +  0] * half + offset.x;
                    WorldBuffers::s_chunkVertexBuffer[vertexIndex].y = ByteCube::s_verticesE[faceIndex +  1] * half + offset.y;
                    WorldBuffers::s_chunkVertexBuffer[vertexIndex].z = ByteCube::s_verticesE[faceIndex +  2] * half + offset.z;

                    vertexIndex += 1;
                    WorldBuffers::s_chunkUVsBuffer   [vertexIndex].x = UVx + WorldSettings::s_textureStep;
                    WorldBuffers::s_chunkUVsBuffer   [vertexIndex].y = UVy + WorldSettings::s_textureStep;
                    WorldBuffers::s_chunkNormalBuffer[vertexIndex].x = ByteCube::s_normals [faceIndex + 3];
                    WorldBuffers::s_chunkNormalBuffer[vertexIndex].y = ByteCube::s_normals [faceIndex + 4];
                    WorldBuffers::s_chunkNormalBuffer[vertexIndex].z = ByteCube::s_normals [faceIndex + 5];
                    WorldBuffers::s_chunkVertexBuffer[vertexIndex].x = ByteCube::s_verticesE[faceIndex +  3] * half + offset.x;
                    WorldBuffers::s_chunkVertexBuffer[vertexIndex].y = ByteCube::s_verticesE[faceIndex +  4] * half + offset.y;
                    WorldBuffers::s_chunkVertexBuffer[vertexIndex].z = ByteCube::s_verticesE[faceIndex +  5] * half + offset.z;
                    vertexIndex += 1;
                    WorldBuffers::s_chunkUVsBuffer   [vertexIndex].x = UVx;
                    WorldBuffers::s_chunkUVsBuffer   [vertexIndex].y = UVy+ WorldSettings::s_textureStep;
                    WorldBuffers::s_chunkNormalBuffer[vertexIndex].x = ByteCube::s_normals [faceIndex + 6];
                    WorldBuffers::s_chunkNormalBuffer[vertexIndex].y = ByteCube::s_normals [faceIndex + 7];
                    WorldBuffers::s_chunkNormalBuffer[vertexIndex].z = ByteCube::s_normals [faceIndex + 8];
                    WorldBuffers::s_chunkVertexBuffer[vertexIndex].x = ByteCube::s_verticesE[faceIndex +  6] * half + offset.x;
                    WorldBuffers::s_chunkVertexBuffer[vertexIndex].y = ByteCube::s_verticesE[faceIndex +  7] * half + offset.y;
                    WorldBuffers::s_chunkVertexBuffer[vertexIndex].z = ByteCube::s_verticesE[faceIndex +  8] * half + offset.z;

                    vertexIndex += 1;
                    WorldBuffers::s_chunkUVsBuffer   [vertexIndex].x = UVx;
                    WorldBuffers::s_chunkUVsBuffer   [vertexIndex].y = UVy + WorldSettings::s_textureStep;
                    WorldBuffers::s_chunkNormalBuffer[vertexIndex].x = ByteCube::s_normals [faceIndex +  9];
                    WorldBuffers::s_chunkNormalBuffer[vertexIndex].y = ByteCube::s_normals [faceIndex + 10];
                    WorldBuffers::s_chunkNormalBuffer[vertexIndex].z = ByteCube::s_normals [faceIndex + 11];
                    WorldBuffers::s_chunkVertexBuffer[vertexIndex].x = ByteCube::s_verticesE[faceIndex +  9] * half + offset.x;
                    WorldBuffers::s_chunkVertexBuffer[vertexIndex].y = ByteCube::s_verticesE[faceIndex + 10] * half + offset.y;
                    WorldBuffers::s_chunkVertexBuffer[vertexIndex].z = ByteCube::s_verticesE[faceIndex + 11] * half + offset.z;

                    vertexIndex += 1;
                    WorldBuffers::s_chunkUVsBuffer   [vertexIndex].x = UVx;
                    WorldBuffers::s_chunkUVsBuffer   [vertexIndex].y = UVy;
                    WorldBuffers::s_chunkNormalBuffer[vertexIndex].x = ByteCube::s_normals [faceIndex + 12];
                    WorldBuffers::s_chunkNormalBuffer[vertexIndex].y = ByteCube::s_normals [faceIndex + 13];
                    WorldBuffers::s_chunkNormalBuffer[vertexIndex].z = ByteCube::s_normals [faceIndex + 14];
                    WorldBuffers::s_chunkVertexBuffer[vertexIndex].x = ByteCube::s_verticesE[faceIndex + 12] * half + offset.x;
                    WorldBuffers::s_chunkVertexBuffer[vertexIndex].y = ByteCube::s_verticesE[faceIndex + 13] * half + offset.y;
                    WorldBuffers::s_chunkVertexBuffer[vertexIndex].z = ByteCube::s_verticesE[faceIndex + 14] * half + offset.z;

                    vertexIndex += 1;
                    WorldBuffers::s_chunkUVsBuffer   [vertexIndex].x = UVx + WorldSettings::s_textureStep;
                    WorldBuffers::s_chunkUVsBuffer   [vertexIndex].y = UVy;
                    WorldBuffers::s_chunkNormalBuffer[vertexIndex].x = ByteCube::s_normals [faceIndex + 15];
                    WorldBuffers::s_chunkNormalBuffer[vertexIndex].y = ByteCube::s_normals [faceIndex + 16];
                    WorldBuffers::s_chunkNormalBuffer[vertexIndex].z = ByteCube::s_normals [faceIndex + 17];
                    WorldBuffers::s_chunkVertexBuffer[vertexIndex].x = ByteCube::s_verticesE[faceIndex + 15] * half + offset.x;
                    WorldBuffers::s_chunkVertexBuffer[vertexIndex].y = ByteCube::s_verticesE[faceIndex + 16] * half + offset.y;
                    WorldBuffers::s_chunkVertexBuffer[vertexIndex].z = ByteCube::s_verticesE[faceIndex + 17] * half + offset.z;
                    vertexIndex += 1;
                }
            }
        }
    }

    WorldBuffers::s_chunkVertexBuffer.resize(vertexIndex);
    WorldBuffers::s_chunkNormalBuffer.resize(vertexIndex);
    WorldBuffers::s_chunkUVsBuffer.resize   (vertexIndex);

    cardinal::VBOIndexer::Index(
            WorldBuffers::s_chunkVertexBuffer,
            WorldBuffers::s_chunkNormalBuffer,
            WorldBuffers::s_chunkUVsBuffer,
            WorldBuffers::s_chunkIndexesBuffer,
            WorldBuffers::s_chunkIndexedVertexBuffer,
            WorldBuffers::s_chunkIndexedNormalBuffer,
            WorldBuffers::s_chunkIndexedUVsBuffer);

    if (WorldBuffers::s_chunkIndexesBuffer.size() != 0) // NOLINT
    {
        m_renderer->Initialize(
                WorldBuffers::s_chunkIndexesBuffer,
                WorldBuffers::s_chunkIndexedVertexBuffer,
                WorldBuffers::s_chunkIndexedNormalBuffer,
                WorldBuffers::s_chunkIndexedUVsBuffer);
    }

    WorldBuffers::s_chunkUVsBuffer.clear();
    WorldBuffers::s_chunkNormalBuffer.clear();
    WorldBuffers::s_chunkVertexBuffer.clear();
    WorldBuffers::s_chunkIndexesBuffer.clear();
    WorldBuffers::s_chunkIndexedUVsBuffer.clear();
    WorldBuffers::s_chunkIndexedVertexBuffer.clear();
    WorldBuffers::s_chunkIndexedNormalBuffer.clear();
}

/// \brief Translate the chunk terrain renderer
void EighthBlockRenderer::SetPosition(glm::vec3 const& position)
{
    m_model = position;
    m_renderer->SetPosition(position);
}
