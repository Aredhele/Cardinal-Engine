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

#include <Runtime/Header/Rendering/Renderer/MeshRenderer.hpp>
#include "Rendering/RenderingEngine.hpp"
#include "Platform/Configuration/Configuration.hh"
#include <Runtime/Header/Rendering/Debug/DebugLine.hpp>
#include <Runtime/Header/Core/Debug/Logger.hpp>

double lastMouseX = 0.0;
double lastMouseY = 0.0;

float speed = 15.0f;
float mouseSensitivity = 0.002f;

static const GLfloat g_vertex_buffer_data[] = {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
};

static const GLfloat g_color_buffer_data[] = {
        0.583f,  0.771f,  0.014f,
        0.609f,  0.115f,  0.436f,
        0.327f,  0.483f,  0.844f,
        0.822f,  0.569f,  0.201f,
        0.435f,  0.602f,  0.223f,
        0.310f,  0.747f,  0.185f,
        0.597f,  0.770f,  0.761f,
        0.559f,  0.436f,  0.730f,
        0.359f,  0.583f,  0.152f,
        0.483f,  0.596f,  0.789f,
        0.559f,  0.861f,  0.639f,
        0.195f,  0.548f,  0.859f,
        0.014f,  0.184f,  0.576f,
        0.771f,  0.328f,  0.970f,
        0.406f,  0.615f,  0.116f,
        0.676f,  0.977f,  0.133f,
        0.971f,  0.572f,  0.833f,
        0.140f,  0.616f,  0.489f,
        0.997f,  0.513f,  0.064f,
        0.945f,  0.719f,  0.592f,
        0.543f,  0.021f,  0.978f,
        0.279f,  0.317f,  0.505f,
        0.167f,  0.620f,  0.077f,
        0.347f,  0.857f,  0.137f,
        0.055f,  0.953f,  0.042f,
        0.714f,  0.505f,  0.345f,
        0.783f,  0.290f,  0.734f,
        0.722f,  0.645f,  0.174f,
        0.302f,  0.455f,  0.848f,
        0.225f,  0.587f,  0.040f,
        0.517f,  0.713f,  0.338f,
        0.053f,  0.959f,  0.120f,
        0.393f,  0.621f,  0.362f,
        0.673f,  0.211f,  0.457f,
        0.820f,  0.883f,  0.371f,
        0.982f,  0.099f,  0.879f
};

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

    int fpsCounter = 0;
    std::string currentFPS = "0 FPS";
    double currentTime = glfwGetTime();
    double lastTime    = currentTime;
    double dLastTime   = currentTime;

    glfwSetInputMode(window->GetContext(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetInputMode(window->GetContext(), GLFW_STICKY_KEYS, GL_TRUE);

    std::vector<glm::vec3> vertices;
    for(int i = 0; i < 108;  i += 3)
    {
        vertices.emplace_back(
                g_vertex_buffer_data[i + 0],
                g_vertex_buffer_data[i + 1],
                g_vertex_buffer_data[i + 2]);
    }

    std::vector<glm::vec3> colors;
    for(int i = 0; i < 108;  i += 3)
    {
        colors.emplace_back(
               1.0f,
               1.0f,
               1.0f);
    }

    cardinal::MeshRenderer renderer;
    renderer.Initialize(vertices, colors);
    engine.Register(&renderer);

    do
    {
        // Fixed delta time
        currentTime = glfwGetTime();

        // camera.LookAt(glm::vec3(0.0f));
        HandleInput(*window, camera, static_cast<float>(currentTime - dLastTime));
        dLastTime = currentTime;

        if(currentTime - lastTime >= 1.0f)
        {
            currentFPS = std::to_string(fpsCounter) + " FPS";
            cardinal::Logger::LogInfo(currentFPS.c_str());

            fpsCounter = 0;
            lastTime = currentTime;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(cardinal::DebugLine * pLine : grid)
        {
            pLine->Render(engine.GetProjectionMatrix(), camera.GetViewMatrix());
        }

        //engine.Render(0.0f);
        glfwPollEvents();
        engine.Render(0.0);
        fpsCounter++;
    }
    while( glfwGetKey(window->GetContext(), GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window->GetContext()) == 0 );

    return 0;
}