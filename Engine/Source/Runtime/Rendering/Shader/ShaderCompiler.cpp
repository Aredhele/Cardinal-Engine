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

/// \file       ShaderCompiler.cpp
/// \date       10/02/2018
/// \project    Cardinal Engine
/// \package    Rendering/Shader
/// \author     Vincent STEHLY--CALISTO

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "Glew/include/GL/glew.h"
#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Rendering/Shader/ShaderCompiler.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Loads a shader from the given paths
/// \param czVertexShader The path to the vertex shader
/// \param csFragmentShader The path to the fragment shader
int ShaderCompiler::LoadShaders(
        const char * czVertexShader,
        const char * csFragmentShader)
{
    GLuint VertexShaderID   = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    std::string VertexShaderCode;
    std::string FragmentShaderCode;

    std::ifstream VertexShaderStream(czVertexShader, std::ios::in);
    if(VertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();

        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }
    else
    {
        Logger::LogError("Impossible to open %s. Are you in the right directory ?", czVertexShader);
        getchar();
        return 0;
    }

    // Read the Fragment IShader code from the file
    std::ifstream FragmentShaderStream(csFragmentShader, std::ios::in);
    if(FragmentShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();

        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }
    else
    {
        Logger::LogError("Impossible to open %s. Are you in the right directory ?", csFragmentShader);
        getchar();
        return 0;
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex IShader
    Logger::LogInfo("Compiling shader : %s", czVertexShader);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource (VertexShaderID, 1, &VertexSourcePointer , nullptr);
    glCompileShader(VertexShaderID);

    // Check Vertex IShader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if ( InfoLogLength > 0 )
    {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
        Logger::LogError("%s", &VertexShaderErrorMessage[0]);
    }

    // Compile Fragment IShader
    Logger::LogInfo("Compiling shader : %s", csFragmentShader);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource (FragmentShaderID, 1, &FragmentSourcePointer , nullptr);
    glCompileShader(FragmentShaderID);

    // Check Fragment IShader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 )
    {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
        Logger::LogError("%s", &FragmentShaderErrorMessage[0]);
    }

    // Link the program
    GLuint ProgramID = glCreateProgram();

    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram (ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if ( InfoLogLength > 0 )
    {
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        Logger::LogError("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

/// \brief Loads a shader from the given paths
/// \param czVertexShader The path to the vertex shader
/// \param csFragmentShader The path to the fragment shader
int ShaderCompiler::LoadShaders(
        const char * czVertexShader,
        const char * szGeometryShader,
        const char * csFragmentShader)
{
    GLuint VertexShaderID   = glCreateShader(GL_VERTEX_SHADER);
    GLuint GeometryShaderID  = glCreateShader(GL_GEOMETRY_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    std::string VertexShaderCode;
    std::string GeometryShaderCode;
    std::string FragmentShaderCode;

    std::ifstream VertexShaderStream(czVertexShader, std::ios::in);
    if(VertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();

        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }
    else
    {
        Logger::LogError("Impossible to open %s. Are you in the right directory ?", czVertexShader);
        getchar();
        return 0;
    }

    // Read the Fragment IShader code from the file
    std::ifstream GeometryShaderStream(szGeometryShader, std::ios::in);
    if(GeometryShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << GeometryShaderStream.rdbuf();

        GeometryShaderCode = sstr.str();
        GeometryShaderStream.close();
    }
    else
    {
        Logger::LogError("Impossible to open %s. Are you in the right directory ?", csFragmentShader);
        getchar();
        return 0;
    }

    // Read the Fragment IShader code from the file
    std::ifstream FragmentShaderStream(csFragmentShader, std::ios::in);
    if(FragmentShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();

        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }
    else
    {
        Logger::LogError("Impossible to open %s. Are you in the right directory ?", csFragmentShader);
        getchar();
        return 0;
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    // Compile Vertex IShader
    Logger::LogInfo("Compiling shader : %s", czVertexShader);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource (VertexShaderID, 1, &VertexSourcePointer , nullptr);
    glCompileShader(VertexShaderID);

    // Check Vertex IShader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if ( InfoLogLength > 0 )
    {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
        Logger::LogError("%s", &VertexShaderErrorMessage[0]);
    }

    // Compile Geometry IShader
    Logger::LogInfo("Compiling shader : %s", szGeometryShader);
    char const * GeometrySourcePointer = GeometryShaderCode.c_str();
    glShaderSource (GeometryShaderID, 1, &GeometrySourcePointer , nullptr);
    glCompileShader(GeometryShaderID);

    // Check Fragment IShader
    glGetShaderiv(GeometryShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(GeometryShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 )
    {
        std::vector<char> GeometryShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(GeometryShaderID, InfoLogLength, nullptr, &GeometryShaderErrorMessage[0]);
        Logger::LogError("%s", &GeometryShaderErrorMessage[0]);
    }


    // Compile Fragment IShader
    Logger::LogInfo("Compiling shader : %s", csFragmentShader);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource (FragmentShaderID, 1, &FragmentSourcePointer , nullptr);
    glCompileShader(FragmentShaderID);

    // Check Fragment IShader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 )
    {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
        Logger::LogError("%s", &FragmentShaderErrorMessage[0]);
    }

    // Link the program
    GLuint ProgramID = glCreateProgram();

    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, GeometryShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram (ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);

    if ( InfoLogLength > 0 )
    {
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        Logger::LogError("%s\n", &ProgramErrorMessage[0]);
    }

    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, GeometryShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(GeometryShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

} // !namespace

