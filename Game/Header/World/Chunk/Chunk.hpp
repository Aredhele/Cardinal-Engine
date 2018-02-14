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

#include "World/Cube/ByteCube.hpp"
#include "Runtime/Rendering/Renderer/MeshRenderer.hpp"

/// \class Chunk
/// \brief Represents a world chunk of cube
class Chunk
{
public:

    static const unsigned s_chunkSize       = 16;
    static const unsigned s_chunkBlockCount = s_chunkSize * s_chunkSize * s_chunkSize;

    static const unsigned s_uvsCount    = s_chunkBlockCount * 24;
    static const unsigned s_vertexCount = s_chunkBlockCount * 36;

    static std::vector<glm::vec3> s_chunkVertexBuffer;
    static std::vector<glm::vec2> s_chunkUVsBuffer;

    static std::vector<unsigned short> s_chunkIndexesBuffer;
    static std::vector<glm::vec3>      s_chunkIndexedVertexBuffer;
    static std::vector<glm::vec2>      s_chunkIndexedUVsBuffer;

    static const float s_triangles[108];

public:

    /// \brief Static initialization of buffers
    static void InitializeBuffers();

    /// \brief Constructor
    Chunk();

    /// \brief Destructor
    ~Chunk();

    /// \brief Initializes a debug chunk
    void Initialize(int zz);
    void Generate(int zz);
    void SetCol(int x, int y, int z);

    /// TODO : Removes
    /// \brief Returns the mesh renderer
    cardinal::MeshRenderer * GetMeshRenderer();

    void Translate(glm::vec3 const& t)
    {
        tr = t;
        m_renderer.Translate(t);
    }
    ByteCube m_cubes[s_chunkSize][s_chunkSize][s_chunkSize];
private:

    /// \brief Builds the chunk vao
    void Batch();

private:

    glm::vec3 tr;
    cardinal::MeshRenderer m_renderer;
    //Cube m_cubes[s_chunkSize][s_chunkSize][s_chunkSize];
};

#endif // !CARDINAL_ENGINE_CHUNK_HPP__