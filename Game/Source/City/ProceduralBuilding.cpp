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

#include "Runtime/Rendering/RenderingEngine.hpp"
#include "Runtime/Rendering/Texture/TextureManager.hpp"
#include "Runtime/Rendering/Shader/Built-in/Standard/StandardShader.hpp"

/// \brief Constructor
ProceduralBuilding::ProceduralBuilding()
{
    Initialize();

    cardinal::StandardShader * pShader = new cardinal::StandardShader(); // NOLINT
    pShader->SetTexture(cardinal::TextureManager::GetTextureID("Block"));
    m_renderer.SetShader(pShader);

    cardinal::RenderingEngine::RegisterCustomRenderer(&m_renderer);
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

    m_offset  = 1.0f;
    m_elapsed = 0.0f;
}

/// \brief Generates the building
void ProceduralBuilding::Generate()
{
    // TMP
    int o = 3;
    int l = 20;
    int t = 14;
    int h = 14;

    // Floor
    for(int x = 0; x < l + o; ++x) // NOLINT
    {
        for(int y = 0; y < t + o; ++y)
        {
            m_building[x][y][0].SetType(ByteCube::EType::Stone);
        }
    }

    // Walls 1
    for(int x = o; x < l; ++x) // NOLINT
    {
        for(int z = 0; z < h; ++z)
        {
            m_building[x][o][z].SetType(ByteCube::EType::Brick);
        }
    }

    // Walls 2
    for(int x = o; x < l; ++x) // NOLINT
    {
        for(int z = 0; z < h; ++z)
        {
            m_building[x][t - 1][z].SetType(ByteCube::EType::Brick);
        }
    }

    // Walls 3
    for(int y = o; y < t; ++y) // NOLINT
    {
        for(int z = 0; z < h; ++z)
        {
            m_building[o][y][z].SetType(ByteCube::EType::Brick);
        }
    }

    // Walls 4
    for(int y = o; y < t; ++y) // NOLINT
    {
        for(int z = 0; z < h; ++z)
        {
            m_building[l - 1][y][z].SetType(ByteCube::EType::Brick);
        }
    }

    // Roof L-1
    // Walls 4
    for(int x = o; x < l; ++x) // NOLINT
    {
        for(int y = o; y < t; ++y)
        {
            m_building[x][y][h - 2].SetType(ByteCube::EType::Stone);
            m_building[x][y][h - 1].SetType(ByteCube::EType::Stone);
        }
    }

    // Roof L
    // Walls 4
    for(int x = o + 1; x < l - 1; ++x) // NOLINT
    {
        for(int y = o + 1; y < t - 1; ++y)
        {
            m_building[x][y][h - 1].SetType(ByteCube::EType::Air);
        }
    }

    // Door
    int sx = l / 2;
    int sy = t - 1;
    int sz = 1;
    int dw = 3;
    int dh = 3;

    for(int x = sx; x < sx + dw; ++x) // NOLINT
    {
        for(int z = sz; z < sz + dh; ++z)
        {
            m_building[x][sy][z].SetType(ByteCube::EType::Air);
        }
    }

    Batch();
    m_renderer.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
}

/// \brief Updates the geometry of the building
/// \param dt The elapsed time
void ProceduralBuilding::Update(float dt)
{
    m_elapsed += dt;
    if(m_elapsed >= 2.0f)
    {
        m_elapsed = 0.0f;
        m_offset *= -1.0f;
    }

    for(int i = 0; i < m_vertices.size(); ++i)
    {
        if(m_vertices[i].z >= ByteCube::s_cubeSize * 2)
        {
            m_vertices[i].z += m_offset * dt *  m_vertices[i].z * 0.2f;
        }
    }

    m_renderer.Update(m_vertices, m_normals, m_uvs);
}

/// \brief Batch geometry
void ProceduralBuilding::Batch()
{
    m_vertices.resize(BUILDING_MAX_SIZE * BUILDING_MAX_SIZE * BUILDING_MAX_HEIGHT * 36);
    m_normals.resize (BUILDING_MAX_SIZE * BUILDING_MAX_SIZE * BUILDING_MAX_HEIGHT * 36);
    m_uvs.resize     (BUILDING_MAX_SIZE * BUILDING_MAX_SIZE * BUILDING_MAX_HEIGHT * 36);

    size_t vertexIndex = 0;
    float half = ByteCube::s_cubeSize / 2.0f;
    float step = 1.0f / 16.0f;

    for (int x = 0; x < BUILDING_MAX_SIZE; ++x) // NOLINT
    {
        for (int y = 0; y < BUILDING_MAX_SIZE; ++y)
        {
            for (int z = 0; z < BUILDING_MAX_HEIGHT; ++z)
            {
                // Pre-conditions
                ByteCube const &cube = m_building[x][y][z];
                if (!cube.IsVisible() || !cube.IsSolid())
                {
                    continue;
                }

                // Face by face batching
                unsigned size   = BUILDING_MAX_SIZE;
                unsigned height = BUILDING_MAX_HEIGHT;
                for (unsigned nFace = 0; nFace < 6; ++nFace)
                {
                    // Visibility determination for faces
                    if ((nFace == 0 && x != 0 &&          m_building[x - 1][y][z].IsSolid()) ||
                        (nFace == 2 && x != size - 1 &&   m_building[x + 1][y][z].IsSolid()) ||
                        (nFace == 3 && y != 0 &&          m_building[x][y - 1][z].IsSolid()) ||
                        (nFace == 1 && y != size - 1 &&   m_building[x][y + 1][z].IsSolid()) ||
                        (nFace == 5 && z != 0 &&          m_building[x][y][z - 1].IsSolid()) ||
                        (nFace == 4 && z != height - 1 && m_building[x][y][z + 1].IsSolid()))
                    {
                        continue;
                    }

                    // Offset of the current cube
                    glm::vec3 offset(x * ByteCube::s_cubeSize, y * ByteCube::s_cubeSize, z * ByteCube::s_cubeSize);

                    size_t faceIndex = nFace * 18;

                    float UVx = UVManager::UV[cube.GetType() >> 1][nFace * 2 + 0] * step;
                    float UVy = UVManager::UV[cube.GetType() >> 1][nFace * 2 + 1] * step;

                    m_uvs[vertexIndex].x      = UVx + step;
                    m_uvs[vertexIndex].y      = UVy;
                    m_normals[vertexIndex].x  = ByteCube::s_normals[faceIndex + 0];
                    m_normals[vertexIndex].y  = ByteCube::s_normals[faceIndex + 1];
                    m_normals[vertexIndex].z  = ByteCube::s_normals[faceIndex + 2];
                    m_vertices[vertexIndex].x = ByteCube::s_vertices[faceIndex + 0] * half + offset.x;
                    m_vertices[vertexIndex].y = ByteCube::s_vertices[faceIndex + 1] * half + offset.y;
                    m_vertices[vertexIndex].z = ByteCube::s_vertices[faceIndex + 2] * half + offset.z;

                    vertexIndex += 1;
                    m_uvs[vertexIndex].x      = UVx + step;
                    m_uvs[vertexIndex].y      = UVy + step;
                    m_normals[vertexIndex].x  = ByteCube::s_normals[faceIndex + 3];
                    m_normals[vertexIndex].y  = ByteCube::s_normals[faceIndex + 4];
                    m_normals[vertexIndex].z  = ByteCube::s_normals[faceIndex + 5];
                    m_vertices[vertexIndex].x = ByteCube::s_vertices[faceIndex + 3] * half + offset.x;
                    m_vertices[vertexIndex].y = ByteCube::s_vertices[faceIndex + 4] * half + offset.y;
                    m_vertices[vertexIndex].z = ByteCube::s_vertices[faceIndex + 5] * half + offset.z;

                    vertexIndex += 1;
                    m_uvs[vertexIndex].x      = UVx;
                    m_uvs[vertexIndex].y      = UVy + step;
                    m_normals[vertexIndex].x  = ByteCube::s_normals[faceIndex + 6];
                    m_normals[vertexIndex].y  = ByteCube::s_normals[faceIndex + 7];
                    m_normals[vertexIndex].z  = ByteCube::s_normals[faceIndex + 8];
                    m_vertices[vertexIndex].x = ByteCube::s_vertices[faceIndex + 6] * half + offset.x;
                    m_vertices[vertexIndex].y = ByteCube::s_vertices[faceIndex + 7] * half + offset.y;
                    m_vertices[vertexIndex].z = ByteCube::s_vertices[faceIndex + 8] * half + offset.z;

                    vertexIndex += 1;
                    m_uvs[vertexIndex].x      = UVx;
                    m_uvs[vertexIndex].y      = UVy + step;
                    m_normals[vertexIndex].x  = ByteCube::s_normals[faceIndex + 9];
                    m_normals[vertexIndex].y  = ByteCube::s_normals[faceIndex + 10];
                    m_normals[vertexIndex].z  = ByteCube::s_normals[faceIndex + 11];
                    m_vertices[vertexIndex].x = ByteCube::s_vertices[faceIndex + 9]  * half + offset.x;
                    m_vertices[vertexIndex].y = ByteCube::s_vertices[faceIndex + 10] * half + offset.y;
                    m_vertices[vertexIndex].z = ByteCube::s_vertices[faceIndex + 11] * half + offset.z;

                    vertexIndex += 1;
                    m_uvs[vertexIndex].x      = UVx;
                    m_uvs[vertexIndex].y      = UVy;
                    m_normals[vertexIndex].x  = ByteCube::s_normals[faceIndex + 12];
                    m_normals[vertexIndex].y  = ByteCube::s_normals[faceIndex + 13];
                    m_normals[vertexIndex].z  = ByteCube::s_normals[faceIndex + 14];
                    m_vertices[vertexIndex].x = ByteCube::s_vertices[faceIndex + 12] * half + offset.x;
                    m_vertices[vertexIndex].y = ByteCube::s_vertices[faceIndex + 13] * half + offset.y;
                    m_vertices[vertexIndex].z = ByteCube::s_vertices[faceIndex + 14] * half + offset.z;

                    vertexIndex += 1;
                    m_uvs[vertexIndex].x      = UVx + step;
                    m_uvs[vertexIndex].y      = UVy;
                    m_normals[vertexIndex].x  = ByteCube::s_normals[faceIndex + 15];
                    m_normals[vertexIndex].y  = ByteCube::s_normals[faceIndex + 16];
                    m_normals[vertexIndex].z  = ByteCube::s_normals[faceIndex + 17];
                    m_vertices[vertexIndex].x = ByteCube::s_vertices[faceIndex + 15] * half + offset.x;
                    m_vertices[vertexIndex].y = ByteCube::s_vertices[faceIndex + 16] * half + offset.y;
                    m_vertices[vertexIndex].z = ByteCube::s_vertices[faceIndex + 17] * half + offset.z;

                    vertexIndex += 1;
                }
            }
        }
    }

    m_vertices.resize(vertexIndex);
    m_normals.resize (vertexIndex);
    m_uvs.resize     (vertexIndex);

    if (vertexIndex != 0)
    {
        m_renderer.Update(m_vertices, m_normals, m_uvs);
    }
}