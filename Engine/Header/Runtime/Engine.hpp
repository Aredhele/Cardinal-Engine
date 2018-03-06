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

/// \file       Engine.hpp
/// \date       19/02/2018
/// \project    Cardinal Engine
/// \package    Runtime
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_ENGINE_HPP__
#define CARDINAL_ENGINE_ENGINE_HPP__

// Third party
#include "ImGUI/Header/ImGUI/imgui.h"
#include "ImGUI/Header/ImGUI/imgui_impl_glfw_gl3.h"

#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Sound/SoundEngine.hpp"
#include "Runtime/Core/Assertion/Assert.hh"
#include "Runtime/Core/Plugin/PluginManager.hpp"
#include "Runtime/Rendering/RenderingEngine.hpp"
#include "Runtime/Rendering/Debug/DebugManager.hpp"
#include "Runtime/Physics/PhysicsEngine.hpp"
#include "Runtime/Platform/Configuration/Configuration.hh"

/// \namespace cardinal
namespace cardinal
{

/// \class Engine
/// \brief TODO
class Engine
{
public:

    /// \brief Initializes Cardinal
    bool Initialize();

    /// \brief Starts the engine
    void Start();

    /// \brief Releases Cardinal
    void Release();

private:

    /// \brief Main method of the engine
    void GameLoop();

private:

    SoundEngine     m_soundEngine;
    PluginManager   m_pluginManager;
    RenderingEngine m_renderingEngine;
    PhysicsEngine   m_physicsEngine;

    static constexpr const double SECONDS_PER_UPDATE = 1.0 / 60.0;
};

} // !namespace

#endif // !CARDINAL_ENGINE_ENGINE_HPP__