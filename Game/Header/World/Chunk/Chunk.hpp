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

/// \file       Chunk.hpp
/// \date       11/02/2018
/// \project    Cardinal Engine
/// \package    World/Chunk
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_CHUNK_HPP__
#define CARDINAL_ENGINE_CHUNK_HPP__

// Engine
#include <thread>
#include "Runtime/Rendering/RenderingEngine.hpp"

// Game
#include "World/Cube/ByteCube.hpp"
#include "World/WorldSettings.hpp"
#include "World/Chunk/Renderer/TerrainRenderer.hpp"

/// \class Chunk
/// \brief Represents a chunk in the world
class Chunk
{
public:

    /// \brief Represents the state of the chunk
    enum EChunkState
    {
        Generated,
        Generating
    };

    /// \brief The cubes in the chunks
    ByteCube m_cubes[WorldSettings::s_chunkSize]
    [WorldSettings::s_chunkSize]
    [WorldSettings::s_chunkSize];

    /// \brief Constructor
    Chunk();

    /// \brief Destructor
    ~Chunk();

    /// \brief Initializes the chunk at the given world
    ///        chunk coordinates
    void Initialize(int chunkIndexX, int chunkIndexY, int chunkIndexZ);

    /// \brief Returns the chunk state
    inline EChunkState GetState() const;

    /// \brief Returns the chunk index
    inline glm::tvec3<int> GetChunkIndex() const;

    /// \brief Batch the cubes do display them
    /// \remark Should be called whenever a chunk cube state changes
    void Batch();

private:

    double        m_debugTime;

    EChunkState m_state;
    int         m_chunkIndexX;
    int         m_chunkIndexY;
    int         m_chunkIndexZ;



    TerrainRenderer m_terrainRenderer;
};

#include "World/Chunk/Impl/Chunk.inl"

#endif // !CARDINAL_ENGINE_CHUNK_HPP__
