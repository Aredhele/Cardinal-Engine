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
/// \date       23/02/2018
/// \project    Cardinal Engine
/// \package    Rendering/Renderer
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_MESH_RENDERER_HPP__
#define CARDINAL_ENGINE_MESH_RENDERER_HPP__

#include <vector>
#include "Glm/glm/glm.hpp"
#include "Glm/glm/ext.hpp"

#include "Runtime/Rendering/Renderer/IRenderer.hpp"
#include "Runtime/Platform/Configuration/Configuration.hh"

/// \namespace cardinal
namespace cardinal
{

/// \class  MeshRenderer
/// \brief  Renders 3D objects
class MeshRenderer : public IRenderer
{
public :

    /// \brief Default constructor
    MeshRenderer();

    /// \brief Destructor
    ~MeshRenderer();

    /// \brief Initializes the mesh
    /// \param indexes The indexes of the mesh
    /// \param normals The normals of the mesh
    /// \param vertices The vertices of the mesh
    /// \param uvs The uvs of the mesh
    void Initialize(std::vector<unsigned short> const &indexes,
                    std::vector<glm::vec3>      const &vertices,
                    std::vector<glm::vec3>      const &normals,
                    std::vector<glm::vec2>      const &uvs);

    /// \brief Updates the mesh
    /// \param indexes The indexes of the mesh
    /// \param normals The normals of the mesh
    /// \param vertices The vertices of the mesh
    /// \param uvs The uvs of the mesh
    void Update(std::vector<unsigned short> const &indexes,
                std::vector<glm::vec3>      const &vertices,
                std::vector<glm::vec3>      const &normals,
                std::vector<glm::vec2>      const &uvs);

    /// \brief Sets the position of the mesh renderer
    /// \param position The new position
    void SetPosition(glm::vec3 const &position);

    /// \brief Translates the model
    /// \param Translation The translation vector
    void Translate(glm::vec3 const &Translation);

    /// \brief Sets the renderer shader
    /// \param pShader The pointer on the shader
    void SetShader(IShader *pShader);

    /// \brief Base method implementation
    /// \param PV The projection view matrix
    void Draw(glm::mat4 const& P, glm::mat4 const& V, glm::vec3 const& light, std::vector<PointLightStructure> const& pointLights) final;

private:

    friend class RenderingEngine;

    uint m_indexesObject;
    uint m_verticesObject;
    uint m_normalsObject;
    uint m_uvsObject;
};

}  // !namespace

#endif // !CARDINAL_ENGINE_MESH_RENDERER_HPP__