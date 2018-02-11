/// Copyright (C) 2018-2019 Cardinal Engine
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
/// \date       08/02/2018
/// \project    Cardinal Engine
/// \author     Vincent STEHLY--CALISTO

#include "Rendering/RenderingEngine.hpp"
#include "Platform/Configuration/Configuration.hh"

double lastMouseX = 0.0;
double lastMouseY = 0.0;

float speed = 15.0f;
float mouseSensitivity = 0.002f;

void HandleInput(cardinal::Window & window, cardinal::Camera & camera, float dt)
{
    double mouseX = 0.0;
    double mouseY = 0.0;
    glfwGetCursorPos(window.GetContext(), &mouseX, &mouseY);

    double deltaX = mouseX - lastMouseX;
    double deltaY = mouseY - lastMouseY;

    camera.Rotate  (static_cast<float>(-deltaX * mouseSensitivity));
    camera.RotateUp(static_cast<float>(-deltaY * mouseSensitivity));

    glm::vec2 mousePos    (mouseX, mouseY);
    glm::vec2 windowSize  (1024.0f, 768.0f);
    glm::vec2 windowCenter(windowSize.x /2, windowSize.y / 2);

    float maxMousePosRadius = glm::min(windowSize.x, windowSize.y) / 3.0f;

    float x = glm::distance(mousePos, windowCenter); // TODO

    if (glm::distance(mousePos, windowCenter) > maxMousePosRadius)
    {
        glfwSetCursorPos(window.GetContext(), 1024/2, 768/2);
        lastMouseX = windowCenter.x;
        lastMouseY = windowCenter.y;
    }
    else
    {
        lastMouseX = mousePos.x;
        lastMouseY = mousePos.y;
    }

    // camera.LookAt(glm::vec3(0.0f));
    if (glfwGetKey(window.GetContext(), GLFW_KEY_W) == GLFW_PRESS) camera.Translate( camera.GetDirection() * dt * speed);
    if (glfwGetKey(window.GetContext(), GLFW_KEY_S) == GLFW_PRESS) camera.Translate(-camera.GetDirection() * dt * speed);
    if (glfwGetKey(window.GetContext(), GLFW_KEY_D) == GLFW_PRESS) camera.Translate( camera.GetRight() * dt * speed);
    if (glfwGetKey(window.GetContext(), GLFW_KEY_A) == GLFW_PRESS) camera.Translate(-camera.GetRight() * dt * speed);
}

/// \brief  Cardinal Engine entry point
int Cardinal_EntryPoint(int argc, char ** argv)
{
    cardinal::RenderingEngine engine;
    cardinal::Camera camera;

    if(!engine.Initialize(1024, 768, "Cardinal", 60.0f, false))
    {
        return -1;
    }

    cardinal::Window * window = engine.GetWindow();
    engine.SetCamera(&camera);

    do
    {
        glfwPollEvents();


        engine.Render(0.0f);
    }
    while( glfwGetKey(window->GetContext(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window->GetContext()) == 0 );

    return 0;
}