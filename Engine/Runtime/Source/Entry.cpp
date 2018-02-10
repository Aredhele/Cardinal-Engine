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

#include <vector>
#include "Core/Debug/Logger.hpp"
#include "Platform/Configuration/Configuration.hh"

#include "Rendering/Camera/Camera.hpp"
#include "Rendering/Context/Window.hpp"
#include "Rendering/Debug/DebugLine.hpp"
#include "Rendering/Debug/DebugCube.hpp"
#include "Rendering/Shader/ShaderCompiler.hpp"

#include "Glm/glm/ext.hpp"

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
    cardinal::Window window(1024, 768, "Cardinal");
    cardinal::Camera camera;

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 View       = camera.GetViewMatrix();

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glm::vec3 color = glm::vec3(0.5f, 0.5f,  0.5f);
    glm::vec3 start = glm::vec3(-9.5, 0.0f, -9.5f);

    std::vector<cardinal::DebugLine*> grid;
    for(int i = 0; i < 20; ++i)
    {
        cardinal::DebugLine * pLine = new cardinal::DebugLine(glm::vec3(-9.5 + 1.0f * i, 0.0f, -9.5f), glm::vec3(0.0f,  0.0f,  19.0f),  color);
        grid.push_back(pLine);
    }

    for(int j = 0; j < 20; ++j)
    {
        cardinal::DebugLine * pLine = new cardinal::DebugLine(glm::vec3(-9.5f, 0.0f, -9.5f + 1.0f * j), glm::vec3(19.0f,  0.0f,  0.0f),  color);
        grid.push_back(pLine);
    }


    // Test
    cardinal::DebugCube cube_1;
    cardinal::DebugLine line_1(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(3.0f, 0.0f,  0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    cardinal::DebugLine line_2(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -3.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    cardinal::DebugLine line_3(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 3.0f,  0.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    // Measure time/ FPS
    int fpsCounter = 0;
    std::string currentFPS = "0 FPS";
    double currentTime = glfwGetTime();
    double lastTime    = currentTime;
    double dLastTime   = currentTime;

    glfwSetInputMode(window.GetContext(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetInputMode(window.GetContext(), GLFW_STICKY_KEYS, GL_TRUE);

    do
    {
        // Fixed delta time
        currentTime = glfwGetTime();

        HandleInput(window, camera, static_cast<float>(currentTime - dLastTime));
        dLastTime = currentTime;

        if(currentTime - lastTime >= 1.0f)
        {
            currentFPS = std::to_string(fpsCounter) + " FPS";
            cardinal::Logger::LogInfo(currentFPS.c_str());

            fpsCounter = 0;
            lastTime = currentTime;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //cube_1.Render(Projection, camera.GetViewMatrix());
        line_1.Render(Projection, camera.GetViewMatrix());
        line_2.Render(Projection, camera.GetViewMatrix());
        line_3.Render(Projection, camera.GetViewMatrix());

        for(cardinal::DebugLine * pLine : grid)
        {
            pLine->Render(Projection, camera.GetViewMatrix());
        }

        glfwPollEvents();
        glfwSwapBuffers(window.GetContext());

        fpsCounter++;
    }
    while( glfwGetKey(window.GetContext(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window.GetContext()) == 0 );

    return 0;
}