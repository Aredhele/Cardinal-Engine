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

/// \file       Main.cpp
/// \date       16/02/2018
/// \project    Cardinal Engine
/// \author     Vincent STEHLY--CALISTO

// Engine

#include <iostream>
#include <World/WorldSettings.hpp>
#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Physics/PhysicsEngine.hpp"
#include "Runtime/Rendering/Debug/Debug.hpp"
#include "Runtime/Rendering/RenderingEngine.hpp"
#include "Runtime/Rendering/Renderer/TextRenderer.hpp"
#include "World/Cube/ByteCube.hpp"
#include "Character/PhysicsCharacter.hpp"

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw_gl3.h"

// Entry point
int main(int argc, char ** argv)
{
    cardinal::RenderingEngine renderingEngine;
    cardinal::PhysicsEngine   physicEngine; // NOLINT
    cardinal::Camera camera;

    if (!renderingEngine.Initialize(1600, 900, "Cardinal", 10000.0f, false))
    {
        cardinal::Logger::LogError("Cannot initialize the rendering engine, aborting");
        return -1;
    }

    if(!physicEngine.Initialize(glm::vec3(0.0f, -9.81, 0.0f)))
    {
        cardinal::Logger::LogError("Cannot initialize the physic engine, aborting");
        return -1;
    }

    cardinal::Window * window = renderingEngine.GetWindow();
    renderingEngine.SetCamera(&camera);

    PhysicsCharacter character;
    character.AttachCamera(&camera);

    double currentTime = glfwGetTime();
    double lastTime    = currentTime;

    do
    {
        glfwPollEvents();

        // Triggering ImGUI
        ImGui_ImplGlfwGL3_NewFrame();

        currentTime = glfwGetTime();
        float dt = static_cast<float>(currentTime - lastTime); // NOLINT

        lastTime = currentTime;
        character.Update(window, dt);

        // Debug only
        cardinal::debug::DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1000.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        cardinal::debug::DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1000.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        cardinal::debug::DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1000.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        physicEngine.Update();
        renderingEngine.Render(0.0);

    } while (glfwGetKey(window->GetContext(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window->GetContext()) == 0);
}