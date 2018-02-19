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
/// \package    World
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_WORLD_HPP__
#define CARDINAL_ENGINE_WORLD_HPP__

// Engine
#include <Header/Runtime/Rendering/Renderer/TextRenderer.hpp>
#include "Runtime/Core/Assertion/Assert.hh"
#include "Runtime/Rendering/Debug/Debug.hpp"

// World
#include "World/Chunk/Chunk.hpp"
#include "World/WorldBuffers.hpp"
#include "World/WorldSettings.hpp"
#include "World/Cube/ByteCube.hpp"

/// \class World
/// \brief Main class, manages world generation
class World
{
public:

    Chunk ****      m_chunks;

    /// \brief Default constructor
    World();

    /// \brief Destructor
    ~World();

    /// \brief  Returns the cube at the given coordinates
    /// \param  x The x coordinate
    /// \param  y The y coordinate
    /// \param  z The z coordinate
    /// \return A pointer on the cube, could be nullptr
    inline ByteCube * GetCube(int x, int y, int z);

    /// \brief Updates the world from the character position
    /// \param position The position of the character
    /// \param dt The elapsed time
    void Update(glm::vec3 const& position, float dt);

    /// \brief Creates the initial world
    void Initialize();

    /// \brief Batch all the chunks
    /// \remark Should be called whenever a cube state of the world changes
    void Batch();

private:

    void GetNeighbors(int x, int y, int z, Chunk * neighbors[6]);

private:

    cardinal::TextRenderer * m_worldText;
    cardinal::TextRenderer * m_cubeText;
    cardinal::TextRenderer * m_chunkText;
};

#include "World/Impl/World.inl"

#endif // !CARDINAL_ENGINE_WORLD_HPP__
