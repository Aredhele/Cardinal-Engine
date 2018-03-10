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

/// \file       VR_Plugin.hpp
/// \date       10/03/2018
/// \project    Cardinal Engine
/// \package    Plugin
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_VR_PLUGIN_HPP__
#define CARDINAL_ENGINE_VR_PLUGIN_HPP__

// Engine
#include "Runtime/Engine.hpp"
#include "OpenVR/headers/openvr.h"

// Game
#include "Character/Character.hpp"
#include "Rendering/CameraManager.hpp"
#include "City/ProceduralBuilding.hpp"

/// \brief Plugin to test stereoscopic rendering
/// \class VR_Plugin
class VR_Plugin : public cardinal::Plugin
{
public:

    static VR_Plugin * s_pPlugin;

public:

    /// \brief Constructor
    VR_Plugin();

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

    /// \brief Process HMD events
    void ProcessVREvent(vr::VREvent_t const& event);

    /// \brief Render some debug lines for controllers axes
    void RenderControllerAxes();

private:

    Character               m_character;
    CameraManager           m_cameraManager;
    ProceduralBuilding      m_building;
    vr::IVRSystem *         m_pHMD;
    vr::TrackedDevicePose_t m_rTrackedDevicePose [ vr::k_unMaxTrackedDeviceCount ];
    glm::mat4               m_rmat4DevicePose    [ vr::k_unMaxTrackedDeviceCount ];
    bool                    m_rbShowTrackedDevice[ vr::k_unMaxTrackedDeviceCount ];
    int                     m_iTrackedControllerCount;
};

#endif // !CARDINAL_ENGINE_VR_PLUGIN_HPP__

