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
    static const unsigned char s_typeMask  = 0x01; ///< 0000 0001
    static const unsigned char s_stateMask = 0xFE; ///< 1111 1110

    static const float s_vertices[108];
    static const float s_normals [108];

public:

    /// \enum  EType
    /// \brief Represents the type of a cube
    enum EType : unsigned char
    {
        Air          = 0x00 << 1, ///< 0000 0000
        Dirt         = 0x01 << 1, ///< 0000 0010
        Grass        = 0x02 << 1, ///< 0000 0100
        Water        = 0x03 << 1, ///< 0000 0110
        Lava         = 0x04 << 1, ///< 0000 1000
        Rock         = 0x05 << 1, ///< 0000 1010
        Grass1       = 0x06 << 1, ///< 0000 1100
        Wood1        = 0x07 << 1, ///< 0000 1110
        Leaf1        = 0x08 << 1, ///< 0001 0000
        Gold         = 0x09 << 1, ///< 0001 0010
        Coal         = 0x0A << 1, ///< 0001 0100
        Redstone     = 0x0B << 1, ///< 0001 0110
        Diamond      = 0x0C << 1, ///< 0001 1000
        Emerald      = 0x0D << 1, ///< 0001 1010
        Snow         = 0x0E << 1, ///< 0001 1100
        Bedrock      = 0x0F << 1, ///< 0001 1110
        Sand         = 0x10 << 1, ///< 0010 0000
        Ice          = 0x11 << 1, ///< 0010 0010
        WoodPlank    = 0x12 << 1, ///< 0010 0100
        Brick        = 0x13 << 1, ///< 0010 0110
        Stone        = 0x14 << 1, ///< 0010 1000
        Bush         = 0x15 << 1, ///< 0010 1010
        Grass2       = 0x16 << 1, ///< 0010 1100
        Grass3       = 0x17 << 1, ///< 0010 1110
        Grass4       = 0x18 << 1, ///< 0011 0000
        Grass5       = 0x1A << 1, ///< 0011 0010
        Grass6       = 0x1B << 1, ///< 0011 0100
        RedFlower    = 0x1C << 1, ///< 0011 0110
        YellowFlower = 0x1D << 1, ///< 0011 1000

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

    /// \brief Tells if the block has transparency
    /// \return True or false
    inline bool IsTransparent() const;

private:

   unsigned char m_properties;

#ifdef CARDINAL_DEBUG
    EType m_debugType;
#endif
};

#include "World/Cube/Impl/ByteCube.inl"

#endif // !CARDINAL_ENGINE_BYTE_CUBE_HPP__