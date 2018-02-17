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

/// \file       World.cpp
/// \date       17/02/2018
/// \project    Cardinal Engine
/// \package    World
/// \author     Vincent STEHLY--CALISTO

#include <iostream>
#include "World/World.hpp"

/// \brief Default constructor
World::World()
{
    m_chunks = nullptr;

    m_worldText       = cardinal::RenderingEngine::AllocateTextRenderer();
    m_cubeText        = cardinal::RenderingEngine::AllocateTextRenderer();
    m_chunkText       = cardinal::RenderingEngine::AllocateTextRenderer();
    m_playerCubeText  = cardinal::RenderingEngine::AllocateTextRenderer();
    m_playerChunkText = cardinal::RenderingEngine::AllocateTextRenderer();

    m_worldText->Initialize();
    m_cubeText->Initialize();
    m_chunkText->Initialize();
    m_playerCubeText->Initialize();
    m_playerChunkText->Initialize();

    m_worldText->SetText("World info",          730, 580, 14, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_cubeText->SetText ("Cubes count  : 0",    680, 560, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_chunkText->SetText("Chunks count : 0",    680, 545, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_playerChunkText->SetText("Cube : 0 0 0",  680, 530, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_playerCubeText->SetText ("Chunk : 0 0 0", 680, 515, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
}

/// \brief Destructor
World::~World() // NOLINT
{
    // TODO : Delete chunks
}

/// \brief Updates the world from the character position
/// \param position The position of the character
/// \param dt The elasped time
void World::Update(const glm::vec3 &position, float dt)
{
    // Updating debug text
    // Computing player position
    int posX = (int)position.x / ByteCube::s_cubeSize;
    int posY = (int)position.y / ByteCube::s_cubeSize;
    int posZ = (int)position.z / ByteCube::s_cubeSize;

    int chunkX = posX / (int)WorldSettings::s_chunkSize;
    int chunkY = posY / (int)WorldSettings::s_chunkSize;
    int chunkZ = posZ / (int)WorldSettings::s_chunkSize;

    glm::tvec3<int> currentPosition(chunkX, chunkY, chunkZ);

    std::string _cube  = "Cube : "  + std::to_string(posX)   + " " + std::to_string(posY)   + " " + std::to_string(posZ);
    std::string _chunk = "Chunk : " + std::to_string(chunkX) + " " + std::to_string(chunkY) + " " + std::to_string(chunkZ);

    m_playerChunkText->SetText(_cube.c_str(),  680, 530, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_playerCubeText->SetText (_chunk.c_str(), 680, 515, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    // Debug draw
    for(uint x = 0; x < WorldSettings::s_matSize; ++x)
    {
        for(uint y = 0; y < WorldSettings::s_matSize; ++y)
        {
            for(uint z = 0; z < WorldSettings::s_matHeight; ++z)
            {
                glm::vec3 boxColor;
                glm::tvec3<int> chunkIndex = m_chunks[x][y][z]->GetChunkIndex();

                if(chunkIndex.x == chunkX && chunkIndex.y == chunkY && chunkIndex.z == chunkZ)
                {
                    boxColor = glm::vec3(1.0f, 0.0f, 0.0f);
                }
                else if(m_chunks[x][y][z]->GetState() == Chunk::EChunkState::Generated)
                {
                    boxColor = glm::vec3(0.0f, 1.0f, 0.0f);
                }

                int chunkSize = (int)WorldSettings::s_chunkSize; // NOLINT
                cardinal::debug::DrawBox(glm::vec3(
                        (chunkIndex.x * (chunkSize * ByteCube::s_cubeSize)) + (8.0f * ByteCube::s_cubeSize) - ByteCube::s_cubeSize / 2.0f,
                        (chunkIndex.y * (chunkSize * ByteCube::s_cubeSize)) + (8.0f * ByteCube::s_cubeSize) - ByteCube::s_cubeSize / 2.0f,
                        (chunkIndex.z * (chunkSize * ByteCube::s_cubeSize)) + (8.0f * ByteCube::s_cubeSize) - ByteCube::s_cubeSize / 2.0f),
                                chunkSize * ByteCube::s_cubeSize,
                                chunkSize * ByteCube::s_cubeSize, boxColor);

            }
        }
    }

    // Checking delta position
    glm::tvec3<int> delta = currentPosition - m_lastPlayerPos;
    m_lastPlayerPos       = currentPosition;

    CheckChunkDelta(delta);
}

/// \brief Creates the initial world
/// \param position The initial player position
void World::Initialize(glm::vec3 const& position)
{
    WorldBuffers::Initialize();

    cardinal::Logger::LogInfo("Allocating chunks ....");

    // Allocating memory for chunks
    m_chunks = new Chunk ***[WorldSettings::s_matSize];
    for(int i = 0; i < WorldSettings::s_matSize; ++i)
    {
        m_chunks[i] =  new Chunk **[WorldSettings::s_matSize];
        for(int j = 0; j < WorldSettings::s_matSize; ++j)
        {
            m_chunks[i][j] = new Chunk *[WorldSettings::s_matHeight];

            for(int k = 0; k < WorldSettings::s_matHeight; ++k)
            {
                m_chunks[i][j][k] = new Chunk();
                m_chunks[i][j][k]->Initialize(i, j, k);
            }
        }
    }

    cardinal::Logger::LogInfo("%d chunks allocated",
                              WorldSettings::s_matSize *
                              WorldSettings::s_matSize *
                              WorldSettings::s_matHeight);

    // Settings debug text
    std::string _cubes  = "Cubes count  : " + std::to_string(WorldSettings::s_matSize * WorldSettings::s_matSize * WorldSettings::s_matHeight * WorldSettings::s_chunkBlockCount);
    std::string _chunks = "Chunks count : " + std::to_string(WorldSettings::s_matSize * WorldSettings::s_matSize * WorldSettings::s_matHeight);

    m_cubeText->SetText (_cubes.c_str(),  680, 560, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    m_chunkText->SetText(_chunks.c_str(), 680, 545, 12, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

    int chunkX = ((int)position.x / ByteCube::s_cubeSize) / (int)WorldSettings::s_chunkSize;
    int chunkY = ((int)position.y / ByteCube::s_cubeSize) / (int)WorldSettings::s_chunkSize;
    int chunkZ = ((int)position.z / ByteCube::s_cubeSize) / (int)WorldSettings::s_chunkSize;

    m_lastPlayerPos.x = chunkX;
    m_lastPlayerPos.y = chunkY;
    m_lastPlayerPos.z = chunkZ;
}

/// \brief Checks if the player changed of chunks
/// \param delta The delta position (in chunks unit)
void World::CheckChunkDelta(glm::tvec3<int> const& delta)
{
    // The player is now one chunk further on X
    if(delta.x == 1)
    {
        UpdateChunksXPositive();
    }
    // The player is now one chunk less on X
    else if(delta.x == -1)
    {
        UpdateChunksXNegative();
    }
    // The player is now one chunk further on Y
    else if(delta.y == 1)
    {
        UpdateChunksYPositive();
    }
    // The player is now one chunk less on Y
    else if(delta.y == -1)
    {
        UpdateChunksYNegative();
    }
    // The player is now one chunk further on Z
    else if(delta.z == 1)
    {
        UpdateChunksZPositive();
    }
    // The player is now one chunk less on Z
    else if(delta.z == -1)
    {
        UpdateChunksZNegative();
    }
}

/// \briefs If this method is called, all last chunks
///         will translate on X
void World::UpdateChunksXPositive()
{
    // Buffering all last pointers
    std::vector<Chunk *> pointerBuffer;
    pointerBuffer.reserve(WorldSettings::s_matSize * WorldSettings::s_matHeight);

    // Push all pointers that will be moved in the buffer
    for(uint y = 0; y < WorldSettings::s_matSize; ++y)
    {
        for(uint z = 0; z < WorldSettings::s_matHeight; ++z)
        {
            pointerBuffer.push_back(m_chunks[0][y][z]);
        }
    }

    // Translate pointers
    for(uint x = 1; x < WorldSettings::s_matSize; ++x)
    {
        for(uint y = 0; y < WorldSettings::s_matSize; ++y)
        {
            for(uint z = 0; z < WorldSettings::s_matHeight; ++z)
            {
                m_chunks[x - 1][y][z] = m_chunks[x][y][z];
            }
        }
    }

    // Updating front pointers
    // Push all pointers that will be moved in the buffer
    size_t index = 0;
    for(uint y = 0; y < WorldSettings::s_matSize; ++y)
    {
        for(uint z = 0; z < WorldSettings::s_matHeight; ++z)
        {
            glm::tvec3<int> previousPosition =  m_chunks[WorldSettings::s_matSize - 1][y][z]->GetChunkIndex();

            m_chunks[WorldSettings::s_matSize - 1][y][z] = pointerBuffer.at(index++);
            m_chunks[WorldSettings::s_matSize - 1][y][z]->Initialize(previousPosition.x + 1, previousPosition.y, previousPosition.z);
        }
    }
}

/// \briefs If this method is called, all last chunks
///         will translate on -X
void World::UpdateChunksXNegative()
{
    // Buffering all last pointers
    std::vector<Chunk *> pointerBuffer;
    pointerBuffer.reserve(WorldSettings::s_matSize * WorldSettings::s_matHeight);

    // Push all pointers that will be moved in the buffer
    for(uint y = 0; y < WorldSettings::s_matSize; ++y)
    {
        for(uint z = 0; z < WorldSettings::s_matHeight; ++z)
        {
            pointerBuffer.push_back(m_chunks[WorldSettings::s_matSize - 1][y][z]);
        }
    }

    // Translate pointers
    for(int x = WorldSettings::s_matSize - 2; x >= 0; x--)
    {
        for(int y = WorldSettings::s_matSize - 1; y >= 0; y--)
        {
            for(int z = WorldSettings::s_matHeight - 1; z >= 0; z--)
            {
                m_chunks[x + 1][y][z] = m_chunks[x][y][z];
            }
        }
    }

    // Updating front pointers
    // Push all pointers that will be moved in the buffer
    size_t index = 0;
    for(uint y = 0; y < WorldSettings::s_matSize; ++y)
    {
        for(uint z = 0; z < WorldSettings::s_matHeight; ++z)
        {
            glm::tvec3<int> previousPosition =  m_chunks[0][y][z]->GetChunkIndex();

            m_chunks[0][y][z] = pointerBuffer.at(index++);
            m_chunks[0][y][z]->Initialize(previousPosition.x - 1, previousPosition.y, previousPosition.z);
        }
    }
}

void World::UpdateChunksYPositive()
{
    // Buffering all last pointers
    std::vector<Chunk *> pointerBuffer;
    pointerBuffer.reserve(WorldSettings::s_matSize * WorldSettings::s_matHeight);

    // Push all pointers that will be moved in the buffer
    for(uint x = 0; x < WorldSettings::s_matSize; ++x)
    {
        for(uint z = 0; z < WorldSettings::s_matHeight; ++z)
        {
            pointerBuffer.push_back(m_chunks[x][0][z]);
        }
    }

    // Translate pointers
    for(uint x = 0; x < WorldSettings::s_matSize; ++x)
    {
        for(uint y = 1; y < WorldSettings::s_matSize; ++y)
        {
            for(uint z = 0; z < WorldSettings::s_matHeight; ++z)
            {
                m_chunks[x][y - 1][z] = m_chunks[x][y][z];
            }
        }
    }

    // Updating front pointers
    // Push all pointers that will be moved in the buffer
    size_t index = 0;
    for(uint x = 0; x < WorldSettings::s_matSize; ++x)
    {
        for(uint z = 0; z < WorldSettings::s_matHeight; ++z)
        {
            glm::tvec3<int> previousPosition =  m_chunks[x][WorldSettings::s_matSize - 1][z]->GetChunkIndex();

            m_chunks[x][WorldSettings::s_matSize - 1][z] = pointerBuffer.at(index++);
            m_chunks[x][WorldSettings::s_matSize - 1][z]->Initialize(previousPosition.x, previousPosition.y + 1, previousPosition.z);
        }
    }
}

void World::UpdateChunksYNegative()
{
    // Buffering all last pointers
    std::vector<Chunk *> pointerBuffer;
    pointerBuffer.reserve(WorldSettings::s_matSize * WorldSettings::s_matHeight);

    // Push all pointers that will be moved in the buffer
    for(uint x = 0; x < WorldSettings::s_matSize; ++x)
    {
        for(uint z = 0; z < WorldSettings::s_matHeight; ++z)
        {
            pointerBuffer.push_back(m_chunks[x][WorldSettings::s_matSize - 1][z]);
        }
    }

    // Translate pointers
    for(int x = WorldSettings::s_matSize - 1; x >= 0; x--)
    {
        for(int y = WorldSettings::s_matSize - 2; y >= 0; y--)
        {
            for(int z = WorldSettings::s_matHeight - 1; z >= 0; z--)
            {
                m_chunks[x][y + 1][z] = m_chunks[x][y][z];
            }
        }
    }

    // Updating front pointers
    // Push all pointers that will be moved in the buffer
    size_t index = 0;
    for(uint x = 0; x < WorldSettings::s_matSize; ++x)
    {
        for(uint z = 0; z < WorldSettings::s_matHeight; ++z)
        {
            glm::tvec3<int> previousPosition =  m_chunks[x][0][z]->GetChunkIndex();

            m_chunks[x][0][z] = pointerBuffer.at(index++);
            m_chunks[x][0][z]->Initialize(previousPosition.x, previousPosition.y - 1, previousPosition.z);
        }
    }
}

void World::UpdateChunksZPositive()
{
    // Buffering all last pointers
    std::vector<Chunk *> pointerBuffer;
    pointerBuffer.reserve(WorldSettings::s_matSize * WorldSettings::s_matSize);

    // Push all pointers that will be moved in the buffer
    for(uint x = 0; x < WorldSettings::s_matSize; ++x)
    {
        for(uint y = 0; y < WorldSettings::s_matSize; ++y)
        {
            pointerBuffer.push_back(m_chunks[x][y][0]);
        }
    }

    // Translate pointers
    for(uint x = 0; x < WorldSettings::s_matSize; ++x)
    {
        for(uint y = 0; y < WorldSettings::s_matSize; ++y)
        {
            for(uint z = 1; z < WorldSettings::s_matHeight; ++z)
            {
                m_chunks[x][y][z - 1] = m_chunks[x][y][z];
            }
        }
    }

    // Updating front pointers
    // Push all pointers that will be moved in the buffer
    size_t index = 0;
    for(uint x = 0; x < WorldSettings::s_matSize; ++x)
    {
        for(uint y = 0; y < WorldSettings::s_matSize; ++y)
        {
            glm::tvec3<int> previousPosition =  m_chunks[x][y][WorldSettings::s_matHeight - 1]->GetChunkIndex();

            m_chunks[x][y][WorldSettings::s_matHeight - 1] = pointerBuffer.at(index++);
            m_chunks[x][y][WorldSettings::s_matHeight - 1]->Initialize(previousPosition.x, previousPosition.y, previousPosition.z + 1);
        }
    }
}

void World::UpdateChunksZNegative()
{
    // Buffering all last pointers
    std::vector<Chunk *> pointerBuffer;
    pointerBuffer.reserve(WorldSettings::s_matSize * WorldSettings::s_matSize);

    // Push all pointers that will be moved in the buffer
    for(uint x = 0; x < WorldSettings::s_matSize; ++x)
    {
        for(uint y = 0; y < WorldSettings::s_matSize; ++y)
        {
            pointerBuffer.push_back(m_chunks[x][y][WorldSettings::s_matHeight - 1]);
        }
    }

    // Translate pointers
    for(int x = WorldSettings::s_matSize - 1; x >= 0; x--)
    {
        for(int y = WorldSettings::s_matSize - 1; y >= 0; y--)
        {
            for(int z = WorldSettings::s_matHeight - 2; z >= 0; z--)
            {
                m_chunks[x][y][z + 1] = m_chunks[x][y][z];
            }
        }
    }

    // Updating front pointers
    // Push all pointers that will be moved in the buffer
    size_t index = 0;
    for(uint x = 0; x < WorldSettings::s_matSize; ++x)
    {
        for(uint y = 0; y < WorldSettings::s_matSize; ++y)
        {
            glm::tvec3<int> previousPosition =  m_chunks[x][y][0]->GetChunkIndex();

            m_chunks[x][y][0] = pointerBuffer.at(index++);
            m_chunks[x][y][0]->Initialize(previousPosition.x, previousPosition.y, previousPosition.z - 1);
        }
    }
}
