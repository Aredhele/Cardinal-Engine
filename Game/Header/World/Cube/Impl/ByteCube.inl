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
inline ByteCube::ByteCube()
{
    m_properties  = EType::Air | 0x1;

#ifdef CARDINAL_DEBUG
    m_debugType = EType::Air;
#endif
}

/// \brief Shows the cube
inline void ByteCube::Enable()
{
    m_properties = (m_properties & s_stateMask) | (unsigned char)0x1;
}

/// \brief Hides the cube
inline void ByteCube::Disable()
{
    m_properties &= s_stateMask;
}

/// \brief Tells if the cube is visible or not
/// \return True or false
inline bool ByteCube::IsVisible() const
{
    return (bool)(m_properties & 1);
}

/// \brief Returns the type of the cube
/// \return The type of the cube
inline ByteCube::EType ByteCube::GetType() const
{
    return (ByteCube::EType)(m_properties & s_stateMask);
}

/// \brief Sets the type of the cube
/// \param bVisible The new type
inline  void ByteCube::SetType(ByteCube::EType type)
{
    m_properties = (m_properties & s_typeMask) | type;

#ifdef CARDINAL_DEBUG
   m_debugType = type;
#endif
}

/// \brief Tells if the block is solid or not
/// \return True or false
inline bool ByteCube::IsSolid() const
{
    return (GetType() != EType::Air && GetType() != EType::Grass1);
}


