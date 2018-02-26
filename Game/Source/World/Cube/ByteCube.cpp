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

/// \file       ByteCube.cpp
/// \date       15/02/2018
/// \project    Cardinal Engine
/// \package    World/Cube
/// \author     Vincent STEHLY--CALISTO

#include "World/Cube/ByteCube.hpp"

/* static */ const float ByteCube::s_vertices[108] =
{
    -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f, /* Face LEFT   */
    -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f, /* Face BACK   */
     1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f, -1.0f, /* Face RIGHT  */
     1.0f, -1.0f, -1.0f,  1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f, /* Face FRONT  */
    -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, 1.0f,  1.0f,  1.0f,  -1.0f,  1.0f,  1.0f, /* Face TOP    */
    -1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f  /* Face BOTTOM */
};

/* static */ const float ByteCube::s_normals[108] =
{
   -1.0f,  0.0f,  0.0f, -1.0f,   0.0f,   0.0f, -1.0f,   0.0f,   0.0f,  -1.0f,   0.0f,   0.0f, -1.0f,   0.0f,   0.0f,  -1.0f,   0.0f,   0.0f, /* Face LEFT   */
    0.0f,  1.0f,  0.0f,  0.0f,   1.0f,   0.0f,  0.0f,   1.0f,   0.0f,   0.0f,   1.0f,   0.0f,  0.0f,   1.0f,   0.0f,   0.0f,   1.0f,   0.0f, /* Face FRONT  */
    1.0f,  0.0f,  0.0f,  1.0f,   0.0f,   0.0f,  1.0f,   0.0f,   0.0f,   1.0f,   0.0f,   0.0f,  1.0f,   0.0f,   0.0f,   1.0f,   0.0f,   0.0f, /* Face RIGHT  */
    0.0f, -1.0f,  0.0f,  0.0f,  -1.0f,   0.0f,  0.0f,  -1.0f,   0.0f,   0.0f,  -1.0f,   0.0f,  0.0f,  -1.0f,   0.0f,   0.0f,  -1.0f,   0.0f, /* Face BACK   */
    0.0f,  0.0f,  1.0f,  0.0f,   0.0f,   1.0f,  0.0f,   0.0f,   1.0f,   0.0f,   0.0f,   1.0f,  0.0f,   0.0f,   1.0f,   0.0f,   0.0f,   1.0f, /* Face TOP    */
    0.0f,  0.0f, -1.0f,  0.0f,   0.0f,  -1.0f,  0.0f,   0.0f,  -1.0f,   0.0f,   0.0f,  -1.0f,  0.0f,   0.0f,  -1.0f,   0.0f,   0.0f,  -1.0f, /* Face BOTTOM */
};