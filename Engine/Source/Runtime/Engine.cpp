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

/// \file       Engine.cpp
/// \date       19/02/2018
/// \project    Cardinal Engine
/// \package    Runtime
/// \author     Vincent STEHLY--CALISTO

#include "Runtime/Engine.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Initializes Cardinal
bool Engine::Initialize()
{
    Logger::LogInfo("Cardinal initialization");
    m_pluginManager.Initialize();

    if (!m_renderingEngine.Initialize(1600, 900, "Cardinal", 10000.0f, false))
    {
        cardinal::Logger::LogError("Cannot initialize the engine, aborting");
        return false;
    }

    m_renderingEngine.SetPluginManager(&m_pluginManager);

    if(!m_soundEngine.Initialize())
    {
        cardinal::Logger::LogError("Cannot initialize the engine, aborting");
        return false;
    }

    Logger::LogInfo("Registering plugins ...");
    OnPluginRegistration();
    Logger::LogInfo("All plugins have been registered");

    Logger::LogInfo("Cardinal initialized");
}

/// \brief Starts the engine
void Engine::Start()
{
    GameLoop();
}

/// \brief Releases Cardinal
void Engine::Release()
{
    Logger::LogInfo("Releasing all engine resources ...");
    m_soundEngine.Shutdown();
    Logger::LogInfo("Engine successfully released");
}

/// \brief Main method of the engine
void Engine::GameLoop()
{
    // Getting GLFW context
    GLFWwindow * pContext = m_renderingEngine.GetWindow()->GetContext();

    // Creating the camera
    cardinal::Camera camera;
    m_renderingEngine.SetCamera(&camera);

    // Initializing timers
    double lag      = 0.0;
    double previous = glfwGetTime();

    double pluginsTimer = 0.0;
    double startPlugin  = 0.0;

    double renderingTimer = 0.0;
    double startRendering = 0.0f;

    // Game starts
    m_pluginManager.OnPlayStart();

    while (glfwGetKey(pContext, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(pContext) == 0)
    {
        double current = glfwGetTime();
        double elapsed = current - previous;
        previous       = current;

        lag += elapsed;

        // Processing events
        glfwPollEvents();

        // Fixed granularity
        while(lag >= SECONDS_PER_UPDATE)
        {
            // Pre-update
            startPlugin = glfwGetTime();
            m_pluginManager.OnPreUpdate();
            pluginsTimer += (glfwGetTime() - startPlugin);

            // Post-update
            startPlugin = glfwGetTime();
            m_pluginManager.OnPostUpdate((float)SECONDS_PER_UPDATE);
            pluginsTimer += (glfwGetTime() - startPlugin);

            // Retrieve elapsed time
            lag -= SECONDS_PER_UPDATE;
        }


        startRendering = glfwGetTime();

        // Rendering the frame
        m_renderingEngine.Render((float)(lag / SECONDS_PER_UPDATE));
        renderingTimer = (glfwGetTime() - startRendering);

        m_renderingEngine.UpdateEngineTime(0.0f, (float)renderingTimer, (float)pluginsTimer);

        pluginsTimer   = 0.0;
        renderingTimer = 0.0;
    }

    // Game stops
    m_pluginManager.OnPlayStop();
}

} // !namespace