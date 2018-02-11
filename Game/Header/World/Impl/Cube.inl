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

/// \file       Cube.inl
/// \date       11/02/2018
/// \project    Cardinal Engine
/// \package    World/Impl
/// \author     Vincent STEHLY--CALISTO

/// \brief Constructor
inline Cube::Cube()
{
    m_bIsVisible = true;
    m_type       = EType::Air;
}

/// \brief Sets the visible state of the cube
/// \param bVisible The state
inline void Cube::SetVisible(bool bVisible)
{
    m_bIsVisible = bVisible;
}

/// \brief Sets the type of the cube
/// \param bVisible The new type
inline void Cube::SetType(Cube::EType type)
{
    m_type = type;
}

/// \brief Tells if the cube is visible or not
/// \return True or false
inline bool Cube::IsVisible() const
{
    return m_bIsVisible;
}

/// \brief Returns the type of the cube
/// \return The type of the cube
inline Cube::EType Cube::GetType() const
{
    m_type;
}

/// \brief Tells if the block is solid or not
/// \return True or false
inline bool Cube::IsSolid() const
{
    return (m_type!= EType::Air);
}