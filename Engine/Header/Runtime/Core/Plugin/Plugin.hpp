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

/// \file       Plugin.hpp
/// \date       25/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Core/Plugin
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_PLUGIN_HPP__
#define CARDINAL_ENGINE_PLUGIN_HPP__

/// \namespace cardinal
namespace cardinal
{

/// \class Plugin
/// \brief Interface for engine plugins
class Plugin
{
public:

    /// \brief Called when the game begins
    virtual void OnPlayStart() = 0;

    /// \brief Called when the game stops
    virtual void OnPlayStop () = 0;

    /// \brief Called just before the engine update
    virtual void OnPreUpdate() = 0;

    /// \brief Called after the engine update
    virtual void OnPostUpdate(float dt) = 0;

    /// \brief Called to render GUI
    virtual void OnGUI() = 0;
};

} // !namespace

/// \brief Hook to register user plugin from the static libraries
extern "C" void OnPluginRegistration();

#endif // !CARDINAL_ENGINE_PLUGIN_HPP__