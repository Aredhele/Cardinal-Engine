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

/// \file       ShaderCompiler.hpp
/// \date       10/02/2018
/// \project    Cardinal Engine
/// \package    Rendering/Shader
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_SHADER_COMPILER_HPP__
#define CARDINAL_ENGINE_SHADER_COMPILER_HPP__

#include "Runtime/Platform/Configuration/Configuration.hh"

/// \namespace cardinal
namespace cardinal
{

/// \class  ShaderCompiler
/// \brief  Tool to compile shaders
class ShaderCompiler
{
public :

    /// \brief Loads a shader from the given paths
    /// \param czVertexShader The path to the vertex shader
    /// \param csFragmentShader The path to the fragment shader
    static int LoadShaders(const char * czVertexShader,const char * csFragmentShader);

    // TODO
    /// \brief Loads a shader from the given paths
    /// \param czVertexShader The path to the vertex shader
    /// \param csFragmentShader The path to the fragment shader
    static int LoadShaders(const char * czVertexShader, const char * szGeometryShader, const char * csFragmentShader);
};

} // !namespace

#endif // !CARDINAL_ENGINE_SHADER_COMPILER_HPP__