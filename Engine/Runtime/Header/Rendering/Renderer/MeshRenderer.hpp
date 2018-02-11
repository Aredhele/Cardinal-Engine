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

/// \file       MeshRenderer.hpp
/// \date       11/02/2018
/// \project    Cardinal Engine
/// \package    Rendering/Renderer
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_MESH_RENDERER_HPP__
#define CARDINAL_ENGINE_MESH_RENDERER_HPP__

#include <vector>
#include "Glm/glm/glm.hpp"
#include "Glew/include/GL/glew.h"

/// \namespace cardinal
namespace cardinal
{

/// \class  MeshRenderer
/// \brief  Renderer for 3D objects
class MeshRenderer
{
public :

    /// \brief Default constructor
    MeshRenderer();

    /// \brief Destructor
    ~MeshRenderer();

    /// \brief Initializes the mesh
    /// \param vertices The vertices of the mesh
    /// \param colors The colors of the mesh
    void Initialize(
            std::vector<glm::vec3> const& vertices,
            std::vector<glm::vec3> const& colors);

private:

    friend class RenderingEngine;

    GLuint    m_vao;
    GLuint    m_indexesObject;
    GLuint    m_verticesObject;
    GLuint    m_colorsObject;
    GLuint    m_shaderID;
    GLint     m_matrixID;
    GLsizei   m_elementsCount;
    glm::mat4 m_model;

    // TODO : Shader ID
    // TODO : Replace vco for uvs
};

} // !namespace

#endif // !CARDINAL_ENGINE_MESH_RENDERER_HPP__