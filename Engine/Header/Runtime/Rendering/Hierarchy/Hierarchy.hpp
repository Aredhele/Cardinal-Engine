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

/// \file       Hierarchy.hpp
/// \date       11/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Renderer/Hierarchy
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_HIERARCHY_HPP__
#define CARDINAL_ENGINE_HIERARCHY_HPP__

#include <string>
#include "Runtime/Rendering/Hierarchy/Inspector.hpp"

/// \namespace cardinal
namespace cardinal
{

struct HierarchyPair
{
    explicit HierarchyPair(Inspector * target, std::string const& name)
    {
        m_pTarget = target;
        m_name    = name;
    }

    Inspector *  m_pTarget;
    std::string  m_name;
};

} // !namespace

#endif // !CARDINAL_ENGINE_HIERARCHY_HPP__