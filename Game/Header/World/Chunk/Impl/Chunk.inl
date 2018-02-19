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

/// \file       Chunk.inl
/// \date       17/02/2018
/// \project    Cardinal Engine
/// \package    World/Chunk/Impl
/// \author     Vincent STEHLY--CALISTO

// \brief Returns the chunk state
inline Chunk::EChunkState Chunk::GetState() const
{
   return m_state;
}

/// \brief Returns the chunk index
glm::tvec3<int> Chunk::GetChunkIndex() const
{
    return glm::tvec3<int>(m_chunkIndexX, m_chunkIndexY, m_chunkIndexZ);
}
