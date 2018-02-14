

#include "Glew/include/GL/glew.h"
#include "Runtime/Rendering/RenderingEngine.hpp"
#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Rendering/Debug/DebugLine.hpp"
#include <World/World.hpp>
#include <iostream>
#include "World/ByteCube.hpp"

void HandleInput(cardinal::Window & window, cardinal::Camera & camera, float dt);

int main()
{
    cardinal::RenderingEngine engine;
    cardinal::Camera camera;

    if (!engine.Initialize(1600, 900, "Cardinal", 10000.0f, false)) {
        return -1;
    }

    cardinal::Window *window = engine.GetWindow();
    engine.SetCamera(&camera);

    int fpsCounter = 0;
    std::string currentFPS = "0 FPS";
    double currentTime = glfwGetTime();
    double lastTime    = currentTime;
    double dLastTime   = currentTime;

    /*glm::vec3 color = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::vec3 start = glm::vec3(-9.5, 0.0f, -9.5f);

    std::vector<cardinal::DebugLine *> grid;
    for (int i = 0; i < 20; ++i) {
        cardinal::DebugLine *pLine = new cardinal::DebugLine(
                glm::vec3(-9.5 + 1.0f * i, 0.0f, -9.5f),
                glm::vec3(0.0f, 0.0f, 19.0f), color);
        grid.push_back(pLine);
    }

    for (int j = 0; j < 20; ++j) {
        cardinal::DebugLine *pLine = new cardinal::DebugLine(
                glm::vec3(-9.5f, 0.0f, -9.5f + 1.0f * j),
                glm::vec3(19.0f, 0.0f, 0.0f), color);
        grid.push_back(pLine);
    }*/

   Chunk::InitializeBuffers();
    //Chunk chunk;
    //hunk.Initialize();
   // engine.Register(chunk.GetMeshRenderer());

    World world;
   world.GenerateWorld(engine);

    // ByteCube cube;


    do {
        // Fixed delta time
        currentTime = glfwGetTime();

        // camera.LookAt(glm::vec3(0.0f));
        HandleInput(*window, camera,
                    static_cast<float>(currentTime - dLastTime));
        dLastTime = currentTime;

        if (currentTime - lastTime >= 1.0f) {
            currentFPS = std::to_string(fpsCounter) + " FPS";
            cardinal::Logger::LogInfo(currentFPS.c_str());

            fpsCounter = 0;
            lastTime = currentTime;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //for (cardinal::DebugLine *pLine : grid) {
       //     pLine->Render(engine.GetProjectionMatrix(), camera.GetViewMatrix());
       // }

        //engine.Render(0.0f);
        glfwPollEvents();
        engine.Render(0.0);
        fpsCounter++;
    } while (glfwGetKey(window->GetContext(), GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window->GetContext()) == 0);
}






































double lastMouseX = 0.0;
double lastMouseY = 0.0;

float speed = 50.0f;
float run = 30.0f;
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
    bool bAlt = false;
    if(glfwGetKey(window.GetContext(), GLFW_KEY_LEFT_ALT))
    {
        bAlt = true;
    }

    glm::vec2 mousePos    (mouseX, mouseY);
    glm::vec2 windowSize  (1024.0f, 768.0f);
    glm::vec2 windowCenter(windowSize.x /2, windowSize.y / 2);

    float maxMousePosRadius = glm::min(windowSize.x, windowSize.y) / 3.0f;

    float x = glm::distance(mousePos, windowCenter); // TODO

    if (glm::distance(mousePos, windowCenter) > maxMousePosRadius)
    {
        if(!bAlt)
            glfwSetCursorPos(window.GetContext(), 1024/2, 768/2);

        lastMouseX = windowCenter.x;
        lastMouseY = windowCenter.y;
    }
    else
    {
        lastMouseX = mousePos.x;
        lastMouseY = mousePos.y;
    }



    float speedCoeff = 1.0f;
    if(glfwGetKey(window.GetContext(), GLFW_KEY_LEFT_SHIFT))
    {
        speedCoeff = 2.0f;
    }

    // camera.LookAt(glm::vec3(0.0f));
    if (glfwGetKey(window.GetContext(), GLFW_KEY_W) == GLFW_PRESS) camera.Translate( camera.GetDirection() * dt * speed * speedCoeff);
    if (glfwGetKey(window.GetContext(), GLFW_KEY_S) == GLFW_PRESS) camera.Translate(-camera.GetDirection() * dt * speed * speedCoeff);
    if (glfwGetKey(window.GetContext(), GLFW_KEY_D) == GLFW_PRESS) camera.Translate( camera.GetRight() * dt * speed * speedCoeff);
    if (glfwGetKey(window.GetContext(), GLFW_KEY_A) == GLFW_PRESS) camera.Translate(-camera.GetRight() * dt * speed * speedCoeff);
}
