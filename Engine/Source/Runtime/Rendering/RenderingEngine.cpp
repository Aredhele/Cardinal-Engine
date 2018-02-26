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

#include <chrono>
#include <iostream>
#include "windows.h"
#include "psapi.h"

#include "Glew/include/GL/glew.h"

#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Core/Assertion/Assert.hh"

#include "Runtime/Rendering/Shader/IShader.hpp"
#include "Runtime/Rendering/RenderingEngine.hpp"
#include "Runtime/Core/Plugin/PluginManager.hpp"
#include "Runtime/Rendering/Debug/DebugManager.hpp"
#include "Header/Runtime/Rendering/Debug/Debug.hpp"
#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/Shader/ShaderCompiler.hpp"
#include "Runtime/Rendering/Renderer/MeshRenderer.hpp"
#include "Runtime/Rendering/Renderer/TextRenderer.hpp"
#include "Runtime/Rendering/Texture/TextureLoader.hpp"
#include "Runtime/Rendering/Texture/TextureManager.hpp"

#include "Runtime/Rendering/Lighting/LightManager.hpp"
#include "Runtime/Rendering/Lighting/Lights/PointLight.hpp"
#include "Runtime/Rendering/Lighting/Lights/DirectionalLight.hpp"

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw_gl3.h"
#include "ImGUI/imgui_internal.h"

/// \namespace cardinal
namespace cardinal
{

/* static */ RenderingEngine *RenderingEngine::s_pInstance = nullptr;

/// \brief Initializes the rendering engine from parameters
/// \param width The width of the window
/// \param height The height of the window
/// \param szTitle The title of the window
/// \param fps The fps limit
/// \param bInterpolate Should the engine interpolate frame ?
bool RenderingEngine::Initialize(int width, int height, const char *szTitle,
                                 float fps, bool bInterpolate)
{
    Logger::LogInfo("Initializing the Rendering Engine ...");
    Logger::LogInfo("Initializing OpenGL context ...");
    m_window.Initialize(width, height, szTitle);

    if (m_window.GetContext() == nullptr)
    {
        Logger::LogError("Failed to initialize the rendering engine. Aborting.");
        return false;
    }

    // Texture initializes
    TextureManager::Initialize();
    TextureLoader::Initialize();

    // IShader initializes
    ShaderManager::Initialize();

    // Lighting
    LightManager::Initialize();

    // Loads Textures
    TextureLoader::LoadTexture("SAORegular", "Resources/Textures/SAORegular.bmp");
    TextureLoader::LoadTexture("Block",      "Resources/Textures/BlockAtlas_2048.bmp");

    ShaderManager::Register("LitTexture", ShaderCompiler::LoadShaders(
            "Resources/Shaders/Lit/LitTextureVertexShader.glsl",
            "Resources/Shaders/Lit/LitTextureFragmentShader.glsl"));

    ShaderManager::Register("UnlitColor", ShaderCompiler::LoadShaders(
            "Resources/Shaders/Unlit/UnlitColorVertexShader.glsl",
            "Resources/Shaders/Unlit/UnlitColorFragmentShader.glsl"));

    ShaderManager::Register("UnlitTexture", ShaderCompiler::LoadShaders(
            "Resources/Shaders/Unlit/UnlitTextureVertexShader.glsl",
            "Resources/Shaders/Unlit/UnlitTextureFragmentShader.glsl"));

    ShaderManager::Register("UnlitTransparent", ShaderCompiler::LoadShaders(
            "Resources/Shaders/Unlit/UnlitTransparentVertexShader.glsl",
            "Resources/Shaders/Unlit/UnlitTransparentFragmentShader.glsl"));

    ShaderManager::Register("Text", ShaderCompiler::LoadShaders(
            "Resources/Shaders/Text/TextVertexShader.glsl",
            "Resources/Shaders/Text/TextFragmentShader.glsl"));

    ShaderManager::Register("Standard", ShaderCompiler::LoadShaders(
            "Resources/Shaders/Standard/StandardVertexShader.glsl",
            "Resources/Shaders/Standard/StandardFragmentShader.glsl"));

    // Debug
    DebugManager::Initialize();

    // Configures OpenGL pipeline
    glEnable   (GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable   (GL_CULL_FACE);
    glCullFace (GL_BACK);
    glFrontFace(GL_CCW);

    // TODO : Makes clear color configurable
    glClearColor(0.0f, 0.709f, 0.866f, 1.0f);

    // TODO : Removes magic values
    m_projectionMatrix = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 10000.0f);

    m_frameDelta   = 1.0 / fps;
    m_frameTime    = 0.0;
    m_frameLag     = 0.0,
    m_currentTime  = 0.0;
    m_previousTime = 0.0;
    m_elapsedTime  = 0.0;
    m_frameCount   = 0;
    m_currentFps   = 0;
    m_fpsCounter   = 0;
    s_pInstance    = this;
    m_debugWindow  = true;
    m_triangleCounter = 0;
    m_triangleSecond  = 0;
    m_currentTriangle = 0;

    // Initializes ImGUI
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfwGL3_Init(m_window.GetContext(), true);

    // io.NavFlags |= ImGuiNavFlags_EnableKeyboard;  // Enable Keyboard Controls
    // io.NavFlags |= ImGuiNavFlags_EnableGamepad;   // Enable Gamepad Controls

    // Setup style
    ImGui::StyleColorsDark();
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

    if (m_elapsedTime >= 1.0f)
    {
        m_currentFps  = m_fpsCounter / m_elapsedTime;
        m_elapsedTime = 0.0f;
        m_fpsCounter   = 0;

        m_triangleSecond  = m_triangleCounter;
        m_triangleCounter = 0;
    }

    if (m_frameLag < m_frameDelta)
    {
        return;
    }

    // Keeping the frame time overflow
    // for the next frame
    m_frameLag -= m_frameDelta;

    // Starts instrumentation on frame
    double beginFrame = glfwGetTime();

    RenderFrame(step);

    // Computes the total frame time
    m_frameTime = glfwGetTime() - beginFrame;

    // We rendered a new frame, inc. the counter
    m_frameCount++;
    m_fpsCounter++;
}

/// \brief Frame rendering implementation
/// \param step The normalized progression in the frame
void RenderingEngine::RenderFrame(float step)
{
    // Clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Triggering ImGUI
    ImGui_ImplGlfwGL3_NewFrame();
    m_pPluginManager->OnGUI();

    // Gets the projection matrix
    glm::mat4 Projection     = m_projectionMatrix;
    glm::mat4 View           = m_pCamera->GetViewMatrix();
    glm::mat4 ProjectionView = Projection * View;

    // Start debug draw
    DirectionalLight * pLight = LightManager::GetDirectionalLight();
    if(pLight != nullptr)
    {
        debug::DrawDirectionalLight(pLight->GetPosition(), pLight->GetDirection(), glm::vec3(1.0f, 1.0f, 1.0f), 1.0f);
    }

    std::vector<PointLight *> const& pLights = LightManager::GetPointLights();
    for(const PointLight* pPointLight : pLights)
    {
        debug::DrawPointLight(pPointLight->GetPosition(), glm::vec3(1.0f), 32, pPointLight->GetRange(), 1.0f);
    }
    // End debug draw

    // Lighting
    LightManager::OnRenderBegin();

    // Draw
    size_t rendererCount = m_renderers.size();
    for (int nRenderer = 0; nRenderer < rendererCount; ++nRenderer)
    {
        m_triangleCounter += m_renderers[nRenderer]->GetElementCount();
        m_currentTriangle += m_renderers[nRenderer]->GetElementCount();
        m_renderers[nRenderer]->Draw(Projection, View, glm::vec3(0.0f, 0.0f, 0.0f), LightManager::GetNearestPointLights(m_renderers[nRenderer]->GetPosition()));
    }

    // Cleanup
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);

#ifdef CARDINAL_DEBUG
    DebugManager::Draw(ProjectionView);
    DebugManager::Clear();

    DisplayDebugWindow(step);
#endif

    m_currentTriangle = 0;

    // Draw ImGUI
    ImGui::Render();
    ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

    // Display
    glfwSwapBuffers(m_window.GetContext());
}

/// \brief Sets the current camera
void RenderingEngine::SetCamera(Camera *pCamera)
{
    m_pCamera = pCamera;
}

/// \brief Sets the plugin manager
/// \param pManager The plugin manager pointer
void RenderingEngine::SetPluginManager(PluginManager * pManager)
{
    ASSERT_NOT_NULL(pManager);
    m_pPluginManager = pManager;
}

/// \brief Shutdown the engine
void RenderingEngine::Shutdown()
{
    LightManager::Shutdown();
    ShaderManager::Shutdown();
    TextureManager::Shutdown();

    // Shutting down ImGUI
    ImGui_ImplGlfwGL3_Shutdown();
    ImGui::DestroyContext();
}

/// \brief TMP
glm::mat4 const &RenderingEngine::GetProjectionMatrix()
{
    return m_projectionMatrix;
}

/// \brief Allocates and return a pointer on a renderer
///        Registers the renderer into the engine
/* static */ MeshRenderer *RenderingEngine::AllocateMeshRenderer()
{
    ASSERT_NOT_NULL(RenderingEngine::s_pInstance);

    MeshRenderer *pRenderer = new MeshRenderer(); // NOLINT
    RenderingEngine::s_pInstance->m_renderers.push_back((IRenderer *)pRenderer);

    return pRenderer;
}

/// \brief Allocates and return a pointer on a renderer
///        Registers the renderer into the engine
/*static */ TextRenderer * RenderingEngine::AllocateTextRenderer()
{
    ASSERT_NOT_NULL(RenderingEngine::s_pInstance);

    TextRenderer *pRenderer = new TextRenderer(); // NOLINT
    RenderingEngine::s_pInstance->m_renderers.push_back((IRenderer *)pRenderer);

    return pRenderer;
}

/// \brief Deallocates a renderer
///        Unregisters the renderer
/// \param pRenderer The renderer to release
/* static */ void RenderingEngine::ReleaseRenderer(class IRenderer *&pRenderer)
{
    ASSERT_NOT_NULL(RenderingEngine::s_pInstance);

    int index = -1;
    size_t count = RenderingEngine::s_pInstance->m_renderers.size();
    for (size_t nRenderer = 0; nRenderer < count; ++nRenderer)
    {
        if (RenderingEngine::s_pInstance->m_renderers[nRenderer] == pRenderer)
        {
            index = static_cast<int>(nRenderer);
            break;
        }
    }

    if (index != -1)
    {
        RenderingEngine::s_pInstance->m_renderers.erase(
                RenderingEngine::s_pInstance->m_renderers.begin() + index);
    }

    delete pRenderer;
    pRenderer = nullptr;
}

/// \brief Returns the main camera
/// \return A pointer on the main camera
/* static */ Camera *RenderingEngine::GetMainCamera()
{
    ASSERT_NOT_NULL(RenderingEngine::s_pInstance);
    return s_pInstance->m_pCamera;
}

/// \brief Returns a pointer on the window
/* static */ Window *RenderingEngine::GetWindow()
{
    ASSERT_NOT_NULL(RenderingEngine::s_pInstance);
    return &s_pInstance->m_window;
}

/// \brief Displays a window with debug information
/// \param step The current step
void RenderingEngine::DisplayDebugWindow(float step)
{
    if (m_debugWindow)
    {
        ImGui::Begin       ("Cardinal debug", &m_debugWindow);
        ImGui::SetWindowPos("Cardinal debug", ImVec2(10.0f, 10.0f));

        // Header
        ImGuiContext & context = *ImGui::GetCurrentContext();

        context.FontSize = 16;
        ImGui::TextColored(ImVec4(0.0f, 0.9f, 0.0f, 1.0f), "Cardinal v0.2");
        context.FontSize = 14;

        ImGui::Text("\nPlatform");
        ImGui::Text((char *)glGetString(GL_VERSION));
        ImGui::Text((char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
        ImGui::Text((char *)glGetString(GL_RENDERER));

        // Getting global memory info
        MEMORYSTATUSEX status {};
        status.dwLength = sizeof(MEMORYSTATUSEX);
        GlobalMemoryStatusEx(&status);

        // For current usage
        PROCESS_MEMORY_COUNTERS pmc {};
        GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));

        const float Gio = 1024.0f * 1024.0f * 1024.0f;
        float totalRam     = ((float)status.ullTotalPhys) / Gio;
        float availableRam = ((float)status.ullAvailPhys) / Gio;
        float inUseRam     = ((float)pmc.WorkingSetSize)  / Gio;

        ImGui::Text("System : %2.2lf / %2.2lf Gio", availableRam,  totalRam);
        ImGui::Text("In use : %2.5lf Gio", inUseRam);

        // FPS
        ImGui::Text("\nRendering");
        std::string sFPS = "FPS   : " + std::to_string(m_currentFps);
        if(m_currentFps >= 60) ImGui::TextColored(ImVec4(0.0f, 0.9f, 0.0f, 1.0f), sFPS.c_str());
        else                   ImGui::TextColored(ImVec4(0.9f, 0.0f, 0.0f, 1.0f), sFPS.c_str());

        // Others
        ImGui::Text("Frame : %llu", m_frameCount);
        ImGui::Text("Time  : %lf",  m_frameTime);
        ImGui::Text("Lerp  : %lf",  step);
        ImGui::Text("Tri/f : %llu", m_currentTriangle);
        ImGui::Text("Tri/s : %llu", m_triangleSecond);

        // Camera
        glm::vec3 const& position  = m_pCamera->GetPosition();
        glm::vec3 const& direction = m_pCamera->GetDirection();
        ImGui::Text("\nMain camera");
        ImGui::Text("Pos xyz : %4.2lf %4.2lf %4.2lf", position.x,  position.y,  position.z);
        ImGui::Text("Dir xyz : %4.2lf %4.2lf %4.2lf", direction.x, direction.y, direction.z);

        ImGui::End();
    }
}

} // !namespace