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

/// \file       PluginManager.hpp
/// \date       25/02/2018 
/// \project    Cardinal Engine
/// \package    Runtime/Core/Plugin
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_PLUGIN_MANAGER_HPP__
#define CARDINAL_ENGINE_PLUGIN_MANAGER_HPP__

#include <vector>
#include "Runtime/Core/Plugin/Plugin.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \class PluginManager
/// \brief 
class PluginManager
{
public:

    /// \brief Registers a plugin in the engine
    /// \param pPlugin The plugin to register
    static void RegisterPlugin  (Plugin * pPlugin);

    /// \brief Unregisters a plugin from the engine
    /// \param pPlugin The plugin to unregister
    static void UnregisterPlugin(Plugin * pPlugin);

private:

    friend class Engine;
    friend class RenderingEngine;

    /// \brief Initializes the plugin manager
    void Initialize();

    /// \brief Releases the plugin manager
    void Release();

    /// \brief Returns the current registered plugin count
    size_t GetPluginCount() const;

    /// \brief Called when the game begins
    void OnPlayStart();

    /// \brief Called when the game stops
    void OnPlayStop();

    /// \brief Called before the engine update
    void OnPreUpdate();

    /// \brief Called after the engine update
    /// \param dt The elapsed time in seconds
    void OnPostUpdate(float dt);

    /// \brief Called when it's time to render the GUI
    void OnGUI();

    std::vector<Plugin *>  m_plugins;
    static PluginManager * s_pInstance;
};
    
} // !namespace 

#endif // !CARDINAL_ENGINE_PLUGIN_MANAGER_HPP__