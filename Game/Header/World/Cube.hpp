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

/// \file       Cube.hpp
/// \date       11/02/2018
/// \project    Cardinal Engine
/// \package    World
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_CUBE_HPP__
#define CARDINAL_ENGINE_CUBE_HPP__

/// \class Cube
/// \brief Stores information about a cube
class Cube
{
public:

    static const int s_CubeSize = 4;

public:

    /// \enum  EType
    /// \brief Represents the type of a cube
    enum class EType
    {
        Air   = 0x0,
        Dirt  = 0x1,
        Grass = 0x2,
        Water = 0x3
    };

    /// \brief Constructor
    inline Cube();

    /// \brief Sets the visible state of the cube
    /// \param bVisible The state
    inline void SetVisible(bool bVisible);

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

    EType m_type;
    bool  m_bIsVisible;
};

#include "Impl/Cube.inl"

#endif // !CARDINAL_ENGINE_CUBE_HPP__