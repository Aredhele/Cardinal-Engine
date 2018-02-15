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

/// \file       Grass.inl
/// \date       15/02/2018
/// \project    Cardinal Engine
/// \package    World/Chunk/Detail/Impl
/// \author     Vincent STEHLY--CALISTO

/// \brief Returns the center position of the triangles
inline glm::vec3 Grass::GetCenter()
{
    return glm::vec3(
            (vertex[0].x + vertex[1].x + vertex[2].x) / 3.0f,
            (vertex[0].y + vertex[1].y + vertex[2].y) / 3.0f,
            (vertex[0].z + vertex[1].z + vertex[2].z) / 3.0f);
}

/// \brief Comparison method for std::sort
inline bool Grass::operator<(const Grass& right) const
{
   return squareDistance > right.squareDistance;
}
