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

/// \file       GrassRenderer.hpp
/// \date       14/02/2018
/// \project    Cardinal Engine
/// \package    World/Chunk
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_GRASS_RENDERER_HPP__
#define CARDINAL_ENGINE_GRASS_RENDERER_HPP__

#include"Runtime/Rendering/Renderer/MeshRenderer.hpp"

/// \class GrassRenderer
/// \brief Renders all the grass in the chunk
class GrassRenderer
{
public:


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


private:

    glm::vec3              m_model;
    cardinal::MeshRenderer m_renderer;
};

#endif // !CARDINAL_ENGINE_GRASS_RENDERER_HPP__