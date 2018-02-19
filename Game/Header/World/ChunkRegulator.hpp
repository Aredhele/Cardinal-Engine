//
// Created by kelle on 19/02/2018.
//

#ifndef CARDINALENGINE_CHUNKREGULATOR_HPP
#define CARDINALENGINE_CHUNKREGULATOR_HPP


#include <ThirdParty/Glm/glm/vec3.hpp>
#include <Header/Runtime/Rendering/Renderer/TextRenderer.hpp>
#include <World/Cube/ByteCube.hpp>
#include <World/Chunk/Chunk.hpp>
#include "WorldSettings.hpp"
#include "World.hpp"

// TODO Call the generator to generate a new chunk.

// DONT USE THIS CLASS FOR NOW

/// \class ChunkRegulator
/// \brief Manage the generation of non generated chunk of the world
class ChunkRegulator {
public:

    ChunkRegulator(World* world);

/// \brief Updates the world from the character position
/// \param position The position of the character
/// \param dt The elasped time
    void Update(const glm::vec3 &position, float dt)
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
                    glm::tvec3<int> chunkIndex = mp_world->m_chunks[x][y][z]->GetChunkIndex();

                    if(chunkIndex.x == chunkX && chunkIndex.y == chunkY && chunkIndex.z == chunkZ)
                    {
                        boxColor = glm::vec3(1.0f, 0.0f, 0.0f);
                    }
                    else if(mp_world->m_chunks[x][y][z]->GetState() == Chunk::EChunkState::Generated)
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
private:

    World* mp_world;
    cardinal::TextRenderer * m_playerCubeText;
    cardinal::TextRenderer * m_playerChunkText;

    glm::tvec3<int> m_lastPlayerPos;

/// \brief Checks if the player changed of chunks
/// \param delta The delta position (in chunks unit)
    void CheckChunkDelta(glm::tvec3<int> const& delta)
    {
        // The player is now one chunk further on X
        if(delta.x == 1)
        {
            UpdateChunksXPositive();
        }
        // The player is now one chunk less on X
        if(delta.x == -1)
        {
            UpdateChunksXNegative();
        }
        // The player is now one chunk further on Y
        if(delta.y == 1)
        {
            UpdateChunksYPositive();
        }
        // The player is now one chunk less on Y
        if(delta.y == -1)
        {
            UpdateChunksYNegative();
        }
        // The player is now one chunk further on Z
        if(delta.z == 1)
        {
            UpdateChunksZPositive();
        }
        // The player is now one chunk less on Z
        if(delta.z == -1)
        {
            UpdateChunksZNegative();
        }
    }

/// \briefs If this method is called, all last chunks
///         will translate on X
    void UpdateChunksXPositive()
    {
        // Buffering all last pointers
        std::vector<Chunk *> pointerBuffer;
        pointerBuffer.reserve(WorldSettings::s_matSize * WorldSettings::s_matHeight);

        // Push all pointers that will be moved in the buffer
        for(uint y = 0; y < WorldSettings::s_matSize; ++y)
        {
            for(uint z = 0; z < WorldSettings::s_matHeight; ++z)
            {
                pointerBuffer.push_back(mp_world->m_chunks[0][y][z]);
            }
        }

        // Translate pointers
        for(uint x = 1; x < WorldSettings::s_matSize; ++x)
        {
            for(uint y = 0; y < WorldSettings::s_matSize; ++y)
            {
                for(uint z = 0; z < WorldSettings::s_matHeight; ++z)
                {
                    mp_world->m_chunks[x - 1][y][z] = mp_world->m_chunks[x][y][z];
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
                glm::tvec3<int> previousPosition =  mp_world->m_chunks[WorldSettings::s_matSize - 1][y][z]->GetChunkIndex();

                mp_world->m_chunks[WorldSettings::s_matSize - 1][y][z] = pointerBuffer.at(index++);
                //std::thread t1(&Chunk::Initialize, m_chunks[WorldSettings::s_matSize - 1][y][z], previousPosition.x + 1, previousPosition.y, previousPosition.z);
                //t1.detach();
                mp_world->m_chunks[WorldSettings::s_matSize - 1][y][z]->Initialize(previousPosition.x + 1, previousPosition.y, previousPosition.z);
            }
        }
    }

/// \briefs If this method is called, all last chunks
///         will translate on -X
    void UpdateChunksXNegative()
    {
        // Buffering all last pointers
        std::vector<Chunk *> pointerBuffer;
        pointerBuffer.reserve(WorldSettings::s_matSize * WorldSettings::s_matHeight);

        // Push all pointers that will be moved in the buffer
        for(uint y = 0; y < WorldSettings::s_matSize; ++y)
        {
            for(uint z = 0; z < WorldSettings::s_matHeight; ++z)
            {
                pointerBuffer.push_back(mp_world->m_chunks[WorldSettings::s_matSize - 1][y][z]);
            }
        }

        // Translate pointers
        for(int x = WorldSettings::s_matSize - 2; x >= 0; x--)
        {
            for(int y = WorldSettings::s_matSize - 1; y >= 0; y--)
            {
                for(int z = WorldSettings::s_matHeight - 1; z >= 0; z--)
                {
                    mp_world->m_chunks[x + 1][y][z] = mp_world->m_chunks[x][y][z];
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
                glm::tvec3<int> previousPosition =  mp_world->m_chunks[0][y][z]->GetChunkIndex();

                mp_world->m_chunks[0][y][z] = pointerBuffer.at(index++);
                mp_world->m_chunks[0][y][z]->Initialize(previousPosition.x - 1, previousPosition.y, previousPosition.z);
            }
        }
    }

    void UpdateChunksYPositive()
    {
        // Buffering all last pointers
        std::vector<Chunk *> pointerBuffer;
        pointerBuffer.reserve(WorldSettings::s_matSize * WorldSettings::s_matHeight);

        // Push all pointers that will be moved in the buffer
        for(uint x = 0; x < WorldSettings::s_matSize; ++x)
        {
            for(uint z = 0; z < WorldSettings::s_matHeight; ++z)
            {
                pointerBuffer.push_back(mp_world->m_chunks[x][0][z]);
            }
        }

        // Translate pointers
        for(uint x = 0; x < WorldSettings::s_matSize; ++x)
        {
            for(uint y = 1; y < WorldSettings::s_matSize; ++y)
            {
                for(uint z = 0; z < WorldSettings::s_matHeight; ++z)
                {
                    mp_world->m_chunks[x][y - 1][z] = mp_world->m_chunks[x][y][z];
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
                glm::tvec3<int> previousPosition =  mp_world->m_chunks[x][WorldSettings::s_matSize - 1][z]->GetChunkIndex();

                mp_world->m_chunks[x][WorldSettings::s_matSize - 1][z] = pointerBuffer.at(index++);
                mp_world->m_chunks[x][WorldSettings::s_matSize - 1][z]->Initialize(previousPosition.x, previousPosition.y + 1, previousPosition.z);
            }
        }
    }

    void UpdateChunksYNegative()
    {
        // Buffering all last pointers
        std::vector<Chunk *> pointerBuffer;
        pointerBuffer.reserve(WorldSettings::s_matSize * WorldSettings::s_matHeight);

        // Push all pointers that will be moved in the buffer
        for(uint x = 0; x < WorldSettings::s_matSize; ++x)
        {
            for(uint z = 0; z < WorldSettings::s_matHeight; ++z)
            {
                pointerBuffer.push_back(mp_world->m_chunks[x][WorldSettings::s_matSize - 1][z]);
            }
        }

        // Translate pointers
        for(int x = WorldSettings::s_matSize - 1; x >= 0; x--)
        {
            for(int y = WorldSettings::s_matSize - 2; y >= 0; y--)
            {
                for(int z = WorldSettings::s_matHeight - 1; z >= 0; z--)
                {
                    mp_world->m_chunks[x][y + 1][z] = mp_world->m_chunks[x][y][z];
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
                glm::tvec3<int> previousPosition =  mp_world->m_chunks[x][0][z]->GetChunkIndex();

                mp_world->m_chunks[x][0][z] = pointerBuffer.at(index++);
                mp_world->m_chunks[x][0][z]->Initialize(previousPosition.x, previousPosition.y - 1, previousPosition.z);
            }
        }
    }

    void UpdateChunksZPositive()
    {
        // Buffering all last pointers
        std::vector<Chunk *> pointerBuffer;
        pointerBuffer.reserve(WorldSettings::s_matSize * WorldSettings::s_matSize);

        // Push all pointers that will be moved in the buffer
        for(uint x = 0; x < WorldSettings::s_matSize; ++x)
        {
            for(uint y = 0; y < WorldSettings::s_matSize; ++y)
            {
                pointerBuffer.push_back(mp_world->m_chunks[x][y][0]);
            }
        }

        // Translate pointers
        for(uint x = 0; x < WorldSettings::s_matSize; ++x)
        {
            for(uint y = 0; y < WorldSettings::s_matSize; ++y)
            {
                for(uint z = 1; z < WorldSettings::s_matHeight; ++z)
                {
                    mp_world->m_chunks[x][y][z - 1] = mp_world->m_chunks[x][y][z];
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
                glm::tvec3<int> previousPosition =  mp_world->m_chunks[x][y][WorldSettings::s_matHeight - 1]->GetChunkIndex();

                mp_world->m_chunks[x][y][WorldSettings::s_matHeight - 1] = pointerBuffer.at(index++);
                mp_world->m_chunks[x][y][WorldSettings::s_matHeight - 1]->Initialize(previousPosition.x, previousPosition.y, previousPosition.z + 1);
            }
        }
    }

    void UpdateChunksZNegative()
    {
        // Buffering all last pointers
        std::vector<Chunk *> pointerBuffer;
        pointerBuffer.reserve(WorldSettings::s_matSize * WorldSettings::s_matSize);

        // Push all pointers that will be moved in the buffer
        for(uint x = 0; x < WorldSettings::s_matSize; ++x)
        {
            for(uint y = 0; y < WorldSettings::s_matSize; ++y)
            {
                pointerBuffer.push_back(mp_world->m_chunks[x][y][WorldSettings::s_matHeight - 1]);
            }
        }

        // Translate pointers
        for(int x = WorldSettings::s_matSize - 1; x >= 0; x--)
        {
            for(int y = WorldSettings::s_matSize - 1; y >= 0; y--)
            {
                for(int z = WorldSettings::s_matHeight - 2; z >= 0; z--)
                {
                    mp_world->m_chunks[x][y][z + 1] = mp_world->m_chunks[x][y][z];
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
                glm::tvec3<int> previousPosition =  mp_world->m_chunks[x][y][0]->GetChunkIndex();

                mp_world->m_chunks[x][y][0] = pointerBuffer.at(index++);
                mp_world->m_chunks[x][y][0]->Initialize(previousPosition.x, previousPosition.y, previousPosition.z - 1);
            }
        }
    }
};


#endif //CARDINALENGINE_CHUNKREGULATOR_HPP
