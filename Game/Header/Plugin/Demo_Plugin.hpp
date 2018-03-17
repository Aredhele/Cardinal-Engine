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

/// \file       Demo_Plugin.hpp
/// \date       15/03/2018
/// \project    Cardinal Engine
/// \package    Plugin
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_DEMO_PLUGIN_HPP__
#define CARDINAL_ENGINE_DEMO_PLUGIN_HPP__

#include "Runtime/Core/Plugin/Plugin.hpp"
#include "Runtime/Rendering/Particle/ParticleSystem.hpp"

#include "World/World.hpp"
#include "World/Generator/BasicWorldGenerator.hpp"

#include "Character/Character.hpp"
#include "Rendering/CameraManager.hpp"

class Demo_Plugin : public cardinal::Plugin // NOLINT
{
public:

    static Demo_Plugin * s_pPlugin;

public:

    void OnPlayStart()          final;
    void OnPlayStop()           final;
    void OnPreUpdate()          final;
    void OnPostUpdate(float dt) final;
    void OnGUI()                final;

private:

    World *             m_pWorld;
    BasicWorldGenerator m_worldGenerator;

    Character     m_character;
    CameraManager m_cameraManager;

    cardinal::ParticleSystem * m_pSystem;
    vr::IVRSystem *            m_pHMD;
};

#endif // !CARDINAL_ENGINE_DEMO_PLUGIN_HPP__