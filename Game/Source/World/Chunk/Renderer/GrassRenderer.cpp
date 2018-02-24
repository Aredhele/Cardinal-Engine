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

/// \file       GrassRenderer.cpp
/// \date       15/02/2018
/// \project    Cardinal Engine
/// \package    World/Chunk/Renderer
/// \author     Vincent STEHLY--CALISTO

#include <algorithm>
#include <Header/Runtime/Rendering/RenderingEngine.hpp>


#include "World/Cube/UVManager.hpp"
#include "World/Chunk/Renderer/GrassRenderer.hpp"
#include "Runtime/Rendering/Optimization/VBOIndexer.hpp"
#include "Runtime/Rendering/Shader/Built-in/Unlit/UnlitTransparentShader.hpp"

GrassRenderer::GrassRenderer()
{
    if(m_renderer == nullptr)
    {
       // m_renderer = cardinal::RenderingEngine::AllocateRenderer();
    }
}

/// \brief Static batching for grass cubes
/// \param pCubes The cubes of the chunk
void GrassRenderer::Batch(ByteCube pCubes[WorldSettings::s_chunkSize][WorldSettings::s_chunkSize][WorldSettings::s_chunkSize], glm::vec3 const& position)
{
    auto batchingBegin = std::chrono::steady_clock::now();

    // Resizing the vector to ensure that the current size
    // is large enough to hold all vertices and UVs
    WorldBuffers::s_chunkVertexBuffer.resize(WorldSettings::s_chunkVertexCount);
    WorldBuffers::s_chunkUVsBuffer.resize   (WorldSettings::s_chunkVertexCount);
    WorldBuffers::s_grassBuffer.resize      (WorldSettings::s_chunkBlockCount * 2);

    size_t triangleIndex = 0;
    float half           = ByteCube::s_cubeSize / 2.0f;

    for(uint x = 0; x < WorldSettings::s_chunkSize; ++x) // NOLINT
    {
        for(uint y = 0; y < WorldSettings::s_chunkSize; ++y)
        {
            for(uint z = 0; z < WorldSettings::s_chunkSize; ++z)
            {
                // Pre-conditions
                ByteCube const& cube = pCubes[x][y][z];
                if(cube.GetType() != ByteCube::EType::Grass1)
                {
                    continue;
                }

                // Face by face batching
                for(unsigned nFace = 0; nFace < 2; ++nFace)
                {
                    // Offset of the current cube
                    glm::vec3 offset(
                            x * ByteCube::s_cubeSize,
                            y * ByteCube::s_cubeSize,
                            z * ByteCube::s_cubeSize);

                    size_t faceIndex = nFace * 18;

                    float UVx =  UVManager::UV[cube.GetType() >> 1][nFace * 2 + 0] * WorldSettings::s_textureStep;
                    float UVy =  UVManager::UV[cube.GetType() >> 1][nFace * 2 + 1] * WorldSettings::s_textureStep;

                    WorldBuffers::s_grassBuffer[triangleIndex].uv[0].x     = UVx;
                    WorldBuffers::s_grassBuffer[triangleIndex].uv[0].y     = UVy;
                    WorldBuffers::s_grassBuffer[triangleIndex].vertex[0].x = Grass::s_vertices[faceIndex +  0] * half + offset.x;
                    WorldBuffers::s_grassBuffer[triangleIndex].vertex[0].y = Grass::s_vertices[faceIndex +  1] * half + offset.y;
                    WorldBuffers::s_grassBuffer[triangleIndex].vertex[0].z = Grass::s_vertices[faceIndex +  2] * half + offset.z;

                    WorldBuffers::s_grassBuffer[triangleIndex].uv[1].x     = UVx + WorldSettings::s_textureStep;
                    WorldBuffers::s_grassBuffer[triangleIndex].uv[1].y     = UVy;
                    WorldBuffers::s_grassBuffer[triangleIndex].vertex[1].x = Grass::s_vertices[faceIndex +  3] * half + offset.x;
                    WorldBuffers::s_grassBuffer[triangleIndex].vertex[1].y = Grass::s_vertices[faceIndex +  4] * half + offset.y;
                    WorldBuffers::s_grassBuffer[triangleIndex].vertex[1].z = Grass::s_vertices[faceIndex +  5] * half + offset.z;

                    WorldBuffers::s_grassBuffer[triangleIndex].uv[2].x     = UVx + WorldSettings::s_textureStep;
                    WorldBuffers::s_grassBuffer[triangleIndex].uv[2].y     = UVy + WorldSettings::s_textureStep;
                    WorldBuffers::s_grassBuffer[triangleIndex].vertex[2].x = Grass::s_vertices[faceIndex +  6] * half + offset.x;
                    WorldBuffers::s_grassBuffer[triangleIndex].vertex[2].y = Grass::s_vertices[faceIndex +  7] * half + offset.y;
                    WorldBuffers::s_grassBuffer[triangleIndex].vertex[2].z = Grass::s_vertices[faceIndex +  8] * half + offset.z;

                    triangleIndex++;
                    WorldBuffers::s_grassBuffer[triangleIndex].uv[0].x     = UVx + WorldSettings::s_textureStep;
                    WorldBuffers::s_grassBuffer[triangleIndex].uv[0].y     = UVy + WorldSettings::s_textureStep;
                    WorldBuffers::s_grassBuffer[triangleIndex].vertex[0].x = Grass::s_vertices[faceIndex +  9] * half + offset.x;
                    WorldBuffers::s_grassBuffer[triangleIndex].vertex[0].y = Grass::s_vertices[faceIndex + 10] * half + offset.y;
                    WorldBuffers::s_grassBuffer[triangleIndex].vertex[0].z = Grass::s_vertices[faceIndex + 11] * half + offset.z;

                    WorldBuffers::s_grassBuffer[triangleIndex].uv[1].x     = UVx;
                    WorldBuffers::s_grassBuffer[triangleIndex].uv[1].y     = UVy + WorldSettings::s_textureStep;
                    WorldBuffers::s_grassBuffer[triangleIndex].vertex[1].x = Grass::s_vertices[faceIndex + 12] * half + offset.x;
                    WorldBuffers::s_grassBuffer[triangleIndex].vertex[1].y = Grass::s_vertices[faceIndex + 13] * half + offset.y;
                    WorldBuffers::s_grassBuffer[triangleIndex].vertex[1].z = Grass::s_vertices[faceIndex + 14] * half + offset.z;

                    WorldBuffers::s_grassBuffer[triangleIndex].uv[2].x     = UVx;
                    WorldBuffers::s_grassBuffer[triangleIndex].uv[2].y     = UVy;
                    WorldBuffers::s_grassBuffer[triangleIndex].vertex[2].x = Grass::s_vertices[faceIndex + 15] * half + offset.x;
                    WorldBuffers::s_grassBuffer[triangleIndex].vertex[2].y = Grass::s_vertices[faceIndex + 16] * half + offset.y;
                    WorldBuffers::s_grassBuffer[triangleIndex].vertex[2].z = Grass::s_vertices[faceIndex + 17] * half + offset.z;

                    triangleIndex++;
                }
            }
        }
    }

    // Resize triangles
    WorldBuffers::s_grassBuffer.resize(triangleIndex);

    // We have to sort to avoid transparency depth glitch
    // Compute camera-triangle distance for all grass object
    for(size_t nTriangle = 0; nTriangle < triangleIndex; ++nTriangle)
    {
        glm::vec3 direction = (WorldBuffers::s_grassBuffer[nTriangle].GetCenter() + m_model) - position;
        WorldBuffers::s_grassBuffer[nTriangle].squareDistance =
                        direction.x * direction.x +
                        direction.y * direction.y +
                        direction.z * direction.z;
    }

    // Sorting
    std::sort(WorldBuffers::s_grassBuffer.begin(), WorldBuffers::s_grassBuffer.end());

    // Flatten grass object into buffers
    size_t vertexIndex   = 0;
    for(size_t nTriangle = 0; nTriangle < triangleIndex; ++nTriangle)
    {
       // std::cout << "Distance : " << WorldBuffers::s_grassBuffer[nTriangle].squareDistance << std::endl;
        WorldBuffers::s_chunkUVsBuffer[vertexIndex + 0]    = WorldBuffers::s_grassBuffer[nTriangle].uv[0];
        WorldBuffers::s_chunkUVsBuffer[vertexIndex + 1]    = WorldBuffers::s_grassBuffer[nTriangle].uv[1];
        WorldBuffers::s_chunkUVsBuffer[vertexIndex + 2]    = WorldBuffers::s_grassBuffer[nTriangle].uv[2];
        WorldBuffers::s_chunkVertexBuffer[vertexIndex + 0] = WorldBuffers::s_grassBuffer[nTriangle].vertex[0];
        WorldBuffers::s_chunkVertexBuffer[vertexIndex + 1] = WorldBuffers::s_grassBuffer[nTriangle].vertex[1];
        WorldBuffers::s_chunkVertexBuffer[vertexIndex + 2] = WorldBuffers::s_grassBuffer[nTriangle].vertex[2];
        vertexIndex += 3;
    }

    WorldBuffers::s_chunkVertexBuffer.resize(vertexIndex);
    WorldBuffers::s_chunkUVsBuffer.resize   (vertexIndex);

    // Indexing
    cardinal::VBOIndexer::Index(
            WorldBuffers::s_chunkVertexBuffer,
            WorldBuffers::s_chunkUVsBuffer,
            WorldBuffers::s_chunkIndexesBuffer,
            WorldBuffers::s_chunkIndexedVertexBuffer,
            WorldBuffers::s_chunkIndexedUVsBuffer);

    /*m_renderer->Initialize(
            WorldBuffers::s_chunkIndexesBuffer,
            WorldBuffers::s_chunkIndexedVertexBuffer,
            WorldBuffers::s_chunkIndexedUVsBuffer);*/


    m_renderer->SetShader(new cardinal::UnlitTransparentShader()); // TODO fix memory leak

    auto elapsedMs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - batchingBegin);
    // std::cout << "Grass Chunk batched in " << elapsedMs.count() << " ms" << std::endl;

    WorldBuffers::s_chunkUVsBuffer.clear();
    WorldBuffers::s_chunkVertexBuffer.clear();
    WorldBuffers::s_chunkIndexesBuffer.clear();
    WorldBuffers::s_chunkIndexedUVsBuffer.clear();
    WorldBuffers::s_chunkIndexedVertexBuffer.clear();
}

/// \brief Translate the chunk grass renderer
void GrassRenderer::Translate(glm::vec3 const &translation)
{
    m_model += translation;
    m_renderer->Translate(translation);
}
