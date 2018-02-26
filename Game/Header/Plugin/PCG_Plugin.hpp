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

/// \file       PCG_Plugin.hpp
/// \date       26/02/2018
/// \project    Cardinal Engine
/// \package    Plugin
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_PCG_PLUGIN_HPP__
#define CARDINAL_ENGINE_PCG_PLUGIN_HPP__

// Engine
#include "Runtime/Engine.hpp"


#include "World/Generator/GUI/GeneratorGUI.hpp"

// Game
#include "World/World.hpp"
#include "Character/Character.hpp"

/// \brief Plugin for procedural generation
/// \class PCG_Plugin
class PCG_Plugin : public cardinal::Plugin
{
public:

    static PCG_Plugin * s_pPlugin;

public:

    /// \brief Constructor
    PCG_Plugin();

    /// \brief Called when the game begins
    void OnPlayStart() final;

    /// \brief Called when the game stops
    void OnPlayStop () final;

    /// \brief Called just before the engine update
    void OnPreUpdate() final;

    /// \brief Called after the engine update
    /// \param dt The elapsed time in seconds
    void OnPostUpdate(float dt) final;

private:
    GeneratorGUI m_gui;
    World *   m_pWorld;
    Character m_character;
};

#endif // !CARDINAL_ENGINE_PCG_PLUGIN_HPP__

