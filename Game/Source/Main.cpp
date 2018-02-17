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
#include "Runtime/Rendering/RenderingEngine.hpp"
#include "Runtime/Rendering/Renderer/TextRenderer.hpp"

// Game
#include "World/World.hpp"
#include "Character/Character.hpp"

// Entry point
int main(int argc, char ** argv)
{
    cardinal::RenderingEngine engine;
    cardinal::Camera camera;

    if (!engine.Initialize(1600, 900, "Cardinal", 10000.0f, false))
    {
        cardinal::Logger::LogError("Cannot initialize the engine, aborting");
        return -1;
    }

    cardinal::Window * window = engine.GetWindow();
    engine.SetCamera(&camera);

    // Creates the character
    Character character; // NOLINT
    character.AttachCamera(&camera);

    double currentTime = glfwGetTime();
    double lastTime    = currentTime;

    World world;
    world.Initialize();

    // Game loop
    do
    {
        currentTime = glfwGetTime();
        float dt = static_cast<float>(currentTime - lastTime); // NOLINT

        lastTime = currentTime;

        // Update character
        character.Update(window, dt);
        world.Update(camera.GetPosition(), dt);

        // Debug only
        cardinal::debug::DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1000.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        cardinal::debug::DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1000.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
        cardinal::debug::DrawLine(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1000.0f), glm::vec3(0.0f, 0.0f, 1.0f));

        glfwPollEvents();
        engine.Render(0.0);

    } while (glfwGetKey(window->GetContext(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window->GetContext()) == 0);
}