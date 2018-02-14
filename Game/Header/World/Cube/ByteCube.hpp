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

/// \file       ByteCube.hpp
/// \date       11/02/2018
/// \project    Cardinal Engine
/// \package    World/Cube
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_BYTE_CUBE_HPP__
#define CARDINAL_ENGINE_BYTE_CUBE_HPP__

/// \class ByteCube
/// \brief Stores information about a cube
class ByteCube
{
public:

    static const int s_cubeSize = 4;
    static const unsigned char s_typeMask  = 0xF1; ///< 1111 0001
    static const unsigned char s_stateMask = 0xE;  ///< 0000 1110

public:

    /// \enum  EType
    /// \brief Represents the type of a cube
    enum EType : unsigned char
    {
        Air   = 0x0 << 1, ///< 0000 0000
        Dirt  = 0x1 << 1, ///< 0000 0010
        Grass = 0x2 << 1, ///< 0000 0100
        Water = 0x3 << 1, ///< 0000 0110
        Lava  = 0x4 << 1, ///< 0000 1000
        Rock  = 0x5 << 1  ///< 0000 1010
    };

    /// \brief Constructor
    inline ByteCube();

    /// \brief Shows the cube
    inline void Enable();

    /// \brief Hides the cube
    inline void Disable();

    /// \brief Sets the type of the cube
    /// \param bVisible The new type
    inline void SetType(EType type);

    /// \brief Tells if the cube is visible or not
    /// \return True or false
    inline bool IsVisible() const;

    /// \brief Returns the type of the cube
    /// \return The type of the cube
    inline EType GetType() const;

    /// \brief Tells if the block is solid or not
    /// \return True or false
    inline bool IsSolid() const;

private:

   unsigned char m_properties;
};

#include "World/Cube/Impl/ByteCube.inl"

#endif // !CARDINAL_ENGINE_BYTE_CUBE_HPP__