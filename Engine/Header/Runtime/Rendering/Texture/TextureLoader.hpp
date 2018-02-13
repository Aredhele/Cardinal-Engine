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

/// \file       TextureLoader.hpp
/// \date       11/02/2018
/// \project    Cardinal Engine
/// \package    Rendering/Texture
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_TEXTURE_LOADER_HPP__
#define CARDINAL_ENGINE_TEXTURE_LOADER_HPP__

/// \namespace cardinal
#include "Glew/include/GL/glew.h"

namespace cardinal
{

/// \class  TextureLoader
/// \brief
class TextureLoader
{
public:

    /// TMP
    static GLuint LoadBMPTexture(char const* szPath);
};

} // !namespace

#endif // !CARDINAL_ENGINE_TEXTURE_LOADER_HPP__