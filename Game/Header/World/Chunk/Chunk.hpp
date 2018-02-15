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

#include "Runtime/Rendering/RenderingEngine.hpp"

#include "World/Chunk/Renderer/GrassRenderer.hpp"
#include "World/Chunk/Renderer/TerrainRenderer.hpp"

/// \class Chunk
/// \brief Represents a world chunk of cube
class Chunk
{
public:

    /// \brief Constructor
    Chunk();

    /// \brief Destructor
    ~Chunk();

    /// \brief Initializes a debug chunk
    void Initialize(int zz,  glm::vec3 const& position);
    void Generate(int zz);

    /// TODO : Removes
    /// \brief Returns the mesh renderer
    void RegisterChunkSolid(cardinal::RenderingEngine & engine)
    {
        engine.Register(m_terrainRenderer.GetMeshRenderer());
    }

    /// TODO : Removes
    /// \brief Returns the mesh renderer
    void RegisterChunkTransparent(cardinal::RenderingEngine & engine)
    {
        engine.Register(m_grassRenderer.GetMeshRenderer());
    }

    void Translate(glm::vec3 const& t)
    {
        m_terrainRenderer.Translate(t);
        m_grassRenderer.Translate(t);
    }

    /// \brief The cubes in the chunks
    ByteCube m_cubes[WorldSettings::s_chunkSize]
                    [WorldSettings::s_chunkSize]
                    [WorldSettings::s_chunkSize];
//private:

    /// \brief Builds the chunk vao
    void BatchChunk( glm::vec3 const& position);

private:

    GrassRenderer   m_grassRenderer;
    TerrainRenderer m_terrainRenderer;
};

#endif // !CARDINAL_ENGINE_CHUNK_HPP__