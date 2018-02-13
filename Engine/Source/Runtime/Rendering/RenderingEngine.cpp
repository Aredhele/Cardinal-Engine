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

/// \file       RenderingEngine.cpp
/// \date       11/02/2018
/// \project    Cardinal Engine
/// \package    Rendering
/// \author     Vincent STEHLY--CALISTO

#include "Glew/include/GL/glew.h"
#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Rendering/RenderingEngine.hpp"
#include "Runtime/Rendering/Renderer/MeshRenderer.hpp"
#include "Runtime/Rendering/Texture/TextureLoader.hpp"
#include "Runtime/Rendering/Texture/TextureManager.hpp"

/// \namespace cardinal
namespace cardinal
{

/// Initializes the rendering engine from parameters
/// \param width The width of the window
/// \param height The height of the window
/// \param szTitle The title of the window
/// \param fps The fps limit
/// \param bInterpolate Should the engine interpolate frame ?
bool RenderingEngine::Initialize(int width, int height, const char * szTitle, float fps, bool bInterpolate)
{
    Logger::LogInfo("Initializing the Rendering Engine ...");
    Logger::LogInfo("Initializing OpenGL context ...");
    m_window.Initialize(width, height, szTitle);

    if(m_window.GetContext() == nullptr)
    {
        Logger::LogError("Failed to initialize the rendering engine. Aborting.");
        return false;
    }

    // Allocates memory
    // TODO

    // Loads Textures & Compiles shaders
    TextureManager::Initialize();
    TextureLoader::Initialize();

    // Configures OpenGL pipeline
    glDepthFunc(GL_LESS);
    glEnable   (GL_CULL_FACE);
    glEnable   (GL_DEPTH_TEST);

    // TODO : Makes clear color configurable
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // TODO : Removes magic values
    m_projectionMatrix = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 1000.0f);

    m_frameDelta   = 1.0 / fps;
    m_frameTime    = 0.0;
    m_frameLag     = 0.0,
    m_currentTime  = 0.0;
    m_previousTime = 0.0;
    m_elapsedTime  = 0.0;
    m_frameCount   = 0;
    m_currentFps   = 0;
    m_fpsCounter   = 0;

    Logger::LogInfo("Rendering engine successfully initialized in %3.4lf s.", glfwGetTime());
}

/// \brief Renders the frame
/// \param step The progression into the current frame
void RenderingEngine::Render(float step)
{
    // Getting the current elapsed time
    m_currentTime = glfwGetTime();

    double elapsed = m_currentTime - m_previousTime;

    m_frameLag    += elapsed;
    m_elapsedTime += elapsed;
    m_previousTime = m_currentTime;

    if(m_elapsedTime >= 1.0f)
    {
        m_currentFps  = m_fpsCounter / m_elapsedTime;
        m_elapsedTime = 0.0f;
        m_fpsCounter  = 0;

        Logger::LogInfo("%3.3lf FPS", m_currentFps);
    }

    if(m_frameLag < m_frameDelta)
    {
        return;
    }

    // Keeping the frame time overflow
    // for the next frame
    m_frameLag    -= m_frameDelta;

    // Starts instrumentation on frame
    double beginFrame = glfwGetTime();

    RenderFrame(step);

    // Computes the total frame time
    m_frameTime = glfwGetTime() - beginFrame;

    // We render a new frame, inc. the counter
    m_frameCount++;
    m_fpsCounter++;
}

/// \brief Frame rendering implementation
/// \param step The normalized progression in the frame
void RenderingEngine::RenderFrame(float step)
{
    // TODO

    // Gets the projection matrix
    glm::mat4 Projection = m_projectionMatrix;

    // Gets the view matrix
    glm::mat4 View = m_pCamera->GetViewMatrix();

    // Creates Projection View
    glm::mat4 ProjectView = Projection * View;

    glDisable(GL_MULTISAMPLE);

    // Draw
    size_t rendererCount = m_meshRenderer.size();
    for(int nRenderer = 0; nRenderer < rendererCount; ++nRenderer)
    {
        // Buffers the renderer
        MeshRenderer * pRenderer = m_meshRenderer[nRenderer];

        // Create MVP matrix and setup shaders
        glm::mat4 MVP = ProjectView * pRenderer->m_model;

        // TODO : ShaderManager
        glUseProgram(pRenderer->m_shaderID);
        glUniformMatrix4fv(pRenderer->m_matrixID, 1, GL_FALSE, &MVP[0][0]);

        // Render it
        glBindVertexArray(pRenderer->m_vao);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glDrawElements(GL_TRIANGLES, pRenderer->m_elementsCount, GL_UNSIGNED_SHORT, nullptr);
    }

    glEnable(GL_MULTISAMPLE);

    // Cleanup
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);

    //  Display
    glfwSwapBuffers(m_window.GetContext());
}

/// \brief Sets the current camera
void RenderingEngine::SetCamera(Camera * pCamera)
{
    m_pCamera = pCamera;
}

/// \brief Shutdow the engine
void RenderingEngine::Shutdow()
{
    // TODO
    TextureManager::Shutdown();
}

/// \brief Returns a pointer on the window
Window * RenderingEngine::GetWindow()
{
    return &m_window;
}

/// \brief TMP
glm::mat4 const &RenderingEngine::GetProjectionMatrix()
{
    return m_projectionMatrix;
}

/// \brief TMP
void RenderingEngine::Register(class MeshRenderer *pRenderer)
{
    m_meshRenderer.push_back(pRenderer);
}

} // !namespace
