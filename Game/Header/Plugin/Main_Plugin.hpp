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

/// \file       Main_Plugin.hpp
/// \date       26/02/2018
/// \project    Cardinal Engine
/// \package    Plugin
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_MAIN_PLUGIN_HPP__
#define CARDINAL_ENGINE_MAIN_PLUGIN_HPP__

// Engine
#include "Runtime/Engine.hpp"

// Game
#include "World/World.hpp"
#include "Character/Character.hpp"
#include "Rendering/CameraManager.hpp"

/// \brief Plugin for procedural generation
/// \class Main_Plugin
class Main_Plugin : public cardinal::Plugin
{
public:

    static Main_Plugin * s_pPlugin;

public:

    /// \brief Constructor
    Main_Plugin();

    /// \brief Called when the game begins
    void OnPlayStart() final;

    /// \brief Called when the game stops
    void OnPlayStop () final;

    /// \brief Called just before the engine update
    void OnPreUpdate() final;

    /// \brief Called after the engine update
    /// \param dt The elapsed time in seconds
    void OnPostUpdate(float dt) final;

    /// \brief Called when it's time to render the GUI
    void OnGUI() final;

private:

    World *         m_pWorld;               ///< The game world
    Character       m_character;            ///< The game character
    CameraManager   m_cameraManager;        ///< The camera manager
    
    bool            m_debugWindow = false;  ///< True to enable debug window
};

#endif // !CARDINAL_ENGINE_MAIN_PLUGIN_HPP__

