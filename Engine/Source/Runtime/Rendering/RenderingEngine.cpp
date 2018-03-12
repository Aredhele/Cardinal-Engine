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

#ifndef _USE_MATH_DEFINES
#	define _USE_MATH_DEFINES
#endif

#include <cmath>

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
#include "Runtime/Rendering/Hierarchy/Hierarchy.hpp"
#include "Runtime/Rendering/Shader/ShaderManager.hpp"
#include "Runtime/Rendering/Shader/ShaderCompiler.hpp"
#include "Runtime/Rendering/Renderer/MeshRenderer.hpp"
#include "Runtime/Rendering/Renderer/TextRenderer.hpp"
#include "Runtime/Rendering/Texture/TextureLoader.hpp"
#include "Runtime/Rendering/Texture/TextureManager.hpp"
#include "Runtime/Rendering/Particle/ParticleSystem.hpp"
#include "Runtime/Rendering/Lighting/LightManager.hpp"
#include "Runtime/Rendering/Lighting/Lights/PointLight.hpp"
#include "Runtime/Rendering/Lighting/Lights/DirectionalLight.hpp"

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

    ShaderManager::Register("IdentityPostProcess", ShaderCompiler::LoadShaders(
            "Resources/Shaders/PostProcessing/IdentityVertexShader.glsl",
            "Resources/Shaders/PostProcessing/IdentityFragmentShader.glsl"));

    ShaderManager::Register("MirrorPostProcess", ShaderCompiler::LoadShaders(
            "Resources/Shaders/PostProcessing/MirrorVertexShader.glsl",
            "Resources/Shaders/PostProcessing/MirrorFragmentShader.glsl"));

    ShaderManager::Register("NegativePostProcess", ShaderCompiler::LoadShaders(
            "Resources/Shaders/PostProcessing/NegativeVertexShader.glsl",
            "Resources/Shaders/PostProcessing/NegativeFragmentShader.glsl"));

    ShaderManager::Register("SepiaPostProcess", ShaderCompiler::LoadShaders(
            "Resources/Shaders/PostProcessing/SepiaVertexShader.glsl",
            "Resources/Shaders/PostProcessing/SepiaFragmentShader.glsl"));

    ShaderManager::Register("BoxBlurPostProcess", ShaderCompiler::LoadShaders(
            "Resources/Shaders/PostProcessing/BoxBlurVertexShader.glsl",
            "Resources/Shaders/PostProcessing/BoxBlurFragmentShader.glsl"));

    ShaderManager::Register("GaussianBlurPostProcess", ShaderCompiler::LoadShaders(
            "Resources/Shaders/PostProcessing/GaussianBlurVertexShader.glsl",
            "Resources/Shaders/PostProcessing/GaussianBlurFragmentShader.glsl"));

    ShaderManager::Register("SharpenPostProcess", ShaderCompiler::LoadShaders(
            "Resources/Shaders/PostProcessing/SharpenVertexShader.glsl",
            "Resources/Shaders/PostProcessing/SharpenFragmentShader.glsl"));

    ShaderManager::Register("EdgeDetectionPostProcess", ShaderCompiler::LoadShaders(
            "Resources/Shaders/PostProcessing/EdgeDetectionVertexShader.glsl",
            "Resources/Shaders/PostProcessing/EdgeDetectionFragmentShader.glsl"));

    ShaderManager::Register("DepthBufferPostProcess", ShaderCompiler::LoadShaders(
            "Resources/Shaders/PostProcessing/DepthBufferVertexShader.glsl",
            "Resources/Shaders/PostProcessing/DepthBufferFragmentShader.glsl"));

    ShaderManager::Register("GodRayPostProcess", ShaderCompiler::LoadShaders(
            "Resources/Shaders/PostProcessing/GodRayVertexShader.glsl",
            "Resources/Shaders/PostProcessing/GodRayFragmentShader.glsl"));

    ShaderManager::Register("LightScattering", ShaderCompiler::LoadShaders(
            "Resources/Shaders/Utils/LightScatteringVertexShader.glsl",
            "Resources/Shaders/Utils/LightScatteringFragmentShader.glsl"));

    ShaderManager::Register("BloomPostProcess", ShaderCompiler::LoadShaders(
            "Resources/Shaders/PostProcessing/BloomVertexShader.glsl",
            "Resources/Shaders/PostProcessing/BloomFragmentShader.glsl"));

    ShaderManager::Register("VignettePostProcess", ShaderCompiler::LoadShaders(
            "Resources/Shaders/PostProcessing/VignetteVertexShader.glsl",
            "Resources/Shaders/PostProcessing/VignetteFragmentShader.glsl"));

    ShaderManager::Register("FXAAPostProcess", ShaderCompiler::LoadShaders(
            "Resources/Shaders/PostProcessing/FXAAVertexShader.glsl",
            "Resources/Shaders/PostProcessing/FXAAFragmentShader.glsl"));

    ShaderManager::Register("Experimental1PostProcess", ShaderCompiler::LoadShaders(
            "Resources/Shaders/PostProcessing/Experimental/ExperimentalVertexShader_1.glsl",
            "Resources/Shaders/PostProcessing/Experimental/ExperimentalFragmentShader_1.glsl"));

    ShaderManager::Register("Experimental2PostProcess", ShaderCompiler::LoadShaders(
            "Resources/Shaders/PostProcessing/Experimental/ExperimentalVertexShader_2.glsl",
            "Resources/Shaders/PostProcessing/Experimental/ExperimentalFragmentShader_2.glsl"));

    ShaderManager::Register("ShadowMap", ShaderCompiler::LoadShaders(
            "Resources/Shaders/Shadow/ShadowMapVertexShader.glsl",
            "Resources/Shaders/Shadow/ShadowMapFragmentShader.glsl"));

    ShaderManager::Register("VRMirror", ShaderCompiler::LoadShaders(
            "Resources/Shaders/VR/VRMirrorVertexShader.glsl",
            "Resources/Shaders/VR/VRMirrorFragmentShader.glsl"));

    ShaderManager::Register("ParticleShader", ShaderCompiler::LoadShaders(
            "Resources/Shaders/Particle/ParticleVertexShader.glsl",
            "Resources/Shaders/Particle/ParticleFragmentShader.glsl"));

    // Debug
    DebugManager::Initialize();

    // Configures OpenGL pipeline
    glEnable   (GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable   (GL_CULL_FACE);
    glCullFace (GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_MULTISAMPLE);

    // TODO : Makes clear color configurable
    m_clearColor = glm::vec3(0.0f, 0.709f, 0.866f);
    glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, 1.0f);

    // TODO : Removes magic values
    m_projectionMatrix = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 10000.0f);
    // m_projectionMatrix = glm::ortho(0.0f, 1600.0f, 0.0f, 900.0f, -0.1f, 1000.0f);

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
    m_debugTime    = true;
    m_triangleCounter = 0;
    m_triangleSecond  = 0;
    m_currentTriangle = 0;
    m_bIsPostProcessingEnabled = false;
    m_bStereoscopicRendering   = false;
    m_pHMD                     = nullptr;

    m_postProcessingStack.Initialize();

    // Initializing light scattering frame buffer
    glGenFramebuffers(1, &m_lightScatteringFbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_lightScatteringFbo);

    glGenTextures  (1, &m_lightScatteringTexture);
    glBindTexture  (GL_TEXTURE_2D, m_lightScatteringTexture);
    glTexImage2D   (GL_TEXTURE_2D, 0, GL_RGB, 1600, 900, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_lightScatteringTexture, 0);

    // Attaching the list of buffers to draw
    GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);

    // Re-bind physical buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Shadow mapping
    m_shadowMapFbo = 0;
    glGenFramebuffers(1, &m_shadowMapFbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_shadowMapFbo);

    // Depth texture
    m_shadowMapTexture = 0;
    glGenTextures  (1, &m_shadowMapTexture);
    glBindTexture  (GL_TEXTURE_2D, m_shadowMapTexture);
    glTexImage2D   (GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_shadowMapTexture, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        Logger::LogError("Unable to create the shadow maps");
        return false;
    }

    // Re-bind physical buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Initializes ImGUI
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui_ImplGlfwGL3_Init(m_window.GetContext(), true);

    // Setup style
    ImGui::StyleColorsDark();

    Logger::LogInfo("Rendering engine successfully initialized in %3.4lf s.", glfwGetTime());
}

/// \brief Initializes VR rendering
bool RenderingEngine::InitStereoscopicRendering()
{
    // Loading the SteamVR Runtime
    vr::EVRInitError eError = vr::VRInitError_None;
    m_pHMD                  = vr::VR_Init( &eError, vr::VRApplication_Scene );

    if (eError != vr::VRInitError_None)
    {
        m_pHMD = nullptr;
        char buf[1024];
        sprintf_s(buf, sizeof(buf), "Unable to init VR runtime: %s", vr::VR_GetVRInitErrorAsEnglishDescription(eError));
        Logger::LogError("VR_Init Failed : %s", buf);
        return false;
    }
    else
    {
        Logger::LogInfo("VR_Init successful, HMD initialized");
    }

    m_pRenderModels = (vr::IVRRenderModels *)vr::VR_GetGenericInterface( vr::IVRRenderModels_Version, &eError );
    if( !m_pRenderModels)
    {
        m_pHMD = nullptr;
        vr::VR_Shutdown();

        char buf[1024];
        sprintf_s( buf, sizeof( buf ), "Unable to get render model interface: %s", vr::VR_GetVRInitErrorAsEnglishDescription( eError ));
        Logger::LogError("VR_Init Failed : %s", buf);
        return false;
    }
    else
    {
        Logger::LogInfo("vr::IVRRenderModels successful");
    }

    m_strDriver  = "No Driver";
    m_strDisplay = "No Display";

    vr::EVRInitError peError = vr::VRInitError_None;

    if (!vr::VRCompositor())
    {
        Logger::LogError("Compositor initialization failed");
        return false;
    }
    else
    {
        Logger::LogInfo("Compositor initialized");
    }

    m_strDriver  = GetTrackedDeviceString(m_pHMD, vr::k_unTrackedDeviceIndex_Hmd, vr::Prop_TrackingSystemName_String);
    m_strDisplay = GetTrackedDeviceString(m_pHMD, vr::k_unTrackedDeviceIndex_Hmd, vr::Prop_SerialNumber_String);

    Logger::LogInfo("VR driver  : %s", m_strDriver.c_str());
    Logger::LogInfo("VR display : %s", m_strDisplay.c_str());

    m_nRenderWidth  = 0;
    m_nRenderHeight = 0;

    m_pHMD->GetRecommendedRenderTargetSize(&m_nRenderWidth, &m_nRenderHeight);

    Logger::LogInfo("VR FBO recommended width  : %u", m_nRenderWidth);
    Logger::LogInfo("VR FBO recommended height : %u", m_nRenderHeight);

    CreateVRFrameBuffer(m_nRenderWidth, m_nRenderHeight, leftEyeDesc );
    CreateVRFrameBuffer(m_nRenderWidth, m_nRenderHeight, rightEyeDesc);

    m_mat4ProjectionLeft  = GetHMDMatrixProjectionEye(vr::Eye_Left);
    m_mat4ProjectionRight = GetHMDMatrixProjectionEye(vr::Eye_Right);
    m_mat4eyePosLeft      = GetHMDMatrixPoseEye      (vr::Eye_Left);
    m_mat4eyePosRight     = GetHMDMatrixPoseEye      (vr::Eye_Right);

    // Quad to render HMD frames (left - right)
    // VAO for the quad
    glGenVertexArrays(1, &m_HMDVao);
    glBindVertexArray(m_HMDVao);

    // Quad vertices
    static const GLfloat g_quad_vertex_buffer_data[] =
    {
            -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, -1.0f,  1.0f, 0.0f,
            -1.0f,  1.0f, 0.0f, 1.0f, -1.0f, 0.0f,  1.0f,  1.0f, 0.0f,
    };

    glGenBuffers(1, &m_HMDVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_HMDVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);

    // Unbind vao
    glBindVertexArray(0);

    return true;
}

/// \brief Creates fbo
bool RenderingEngine::CreateVRFrameBuffer(int nWidth, int nHeight, FramebufferDesc &framebufferDesc)
{
    glGenFramebuffers(1, &framebufferDesc.m_nRenderFramebufferId );
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferDesc.m_nRenderFramebufferId);

    glGenRenderbuffers(1, &framebufferDesc.m_nDepthBufferId);
    glBindRenderbuffer(GL_RENDERBUFFER, framebufferDesc.m_nDepthBufferId);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH_COMPONENT, nWidth, nHeight );
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER,	framebufferDesc.m_nDepthBufferId );

    glGenTextures(1, &framebufferDesc.m_nRenderTextureId );
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, framebufferDesc.m_nRenderTextureId );
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGBA8, nWidth, nHeight, (GLboolean)true);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, framebufferDesc.m_nRenderTextureId, 0);

    glGenFramebuffers(1, &framebufferDesc.m_nResolveFramebufferId );
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferDesc.m_nResolveFramebufferId);

    glGenTextures(1, &framebufferDesc.m_nResolveTextureId );
    glBindTexture(GL_TEXTURE_2D, framebufferDesc.m_nResolveTextureId );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, framebufferDesc.m_nResolveTextureId, 0);

    // check FBO status
    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        Logger::LogError("Unable to create VR FBO");
        return false;
    }

    glBindFramebuffer( GL_FRAMEBUFFER, 0 );

    return true;
}

/// \brief Returns the right matrix for the right eye
glm::mat4 RenderingEngine::GetHMDMatrixProjectionEye(vr::Hmd_Eye nEye)
{
    if (!m_pHMD)
        return glm::mat4(1.0f);

    vr::IVRSystem *vr_sys = vr::VRSystem();

#if defined(__GNUC__) && defined(_WIN32)
    typedef void (vr::IVRSystem::*FuncPtr)(vr::HmdMatrix44_t *, vr::EVREye, float, float);
    FuncPtr get_projection_matrix = reinterpret_cast<FuncPtr>(&vr::IVRSystem::GetProjectionMatrix); // NOLINT

    vr::HmdMatrix44_t mat {};
    (vr_sys->*get_projection_matrix)(&mat, nEye, 0.1f, 1000.0f);
#else
    vr::HmdMatrix44_t mat = m_pHMD->GetProjectionMatrix(nEye, 0.1, 1000.0f);
#endif

    return glm::mat4(
            mat.m[0][0], mat.m[1][0], mat.m[2][0], mat.m[3][0],
            mat.m[0][1], mat.m[1][1], mat.m[2][1], mat.m[3][1],
            mat.m[0][2], mat.m[1][2], mat.m[2][2], mat.m[3][2],
            mat.m[0][3], mat.m[1][3], mat.m[2][3], mat.m[3][3]);
}

/// \brief Returns the transform of an eye
glm::mat4 RenderingEngine::GetHMDMatrixPoseEye(vr::Hmd_Eye nEye)
{
    if (!m_pHMD)
        return glm::mat4(1.0f);

    vr::IVRSystem *vr_sys = vr::VRSystem();

#if defined(__GNUC__) && defined(_WIN32)
    typedef void (vr::IVRSystem::*FuncPtr)(vr::HmdMatrix34_t *, vr::EVREye);
    FuncPtr get_eye_to_head_transform = reinterpret_cast<FuncPtr>(&vr::IVRSystem::GetEyeToHeadTransform); // NOLINT

    vr::HmdMatrix34_t mat {};
    (vr_sys->*get_eye_to_head_transform)(&mat, nEye);
#else
    vr::HmdMatrix34_t mat = m_pHMD->GetEyeToHeadTransform( nEye );
#endif

    glm::mat4 matrixObj(
            mat.m[0][0], mat.m[1][0], mat.m[2][0], 0.0,
            mat.m[0][1], mat.m[1][1], mat.m[2][1], 0.0,
            mat.m[0][2], mat.m[1][2], mat.m[2][2], 0.0,
            mat.m[0][3], mat.m[1][3], mat.m[2][3], 1.0f
    );

    return glm::inverse(matrixObj);
}

/// \brief ...
void RenderingEngine::ShutdownStereoscopicRendering()
{
    if(m_pHMD)
    {
        vr::VR_Shutdown();
        m_pHMD = nullptr;
    }
}

/// \brief Returns the wanted string
std::string RenderingEngine::GetTrackedDeviceString( vr::IVRSystem *pHmd, vr::TrackedDeviceIndex_t unDevice, vr::TrackedDeviceProperty prop, vr::TrackedPropertyError *peError)
{
    uint32_t unRequiredBufferLen = pHmd->GetStringTrackedDeviceProperty( unDevice, prop, nullptr, 0, peError );
    if( unRequiredBufferLen == 0 )
        return "";

    char *pchBuffer = new char[ unRequiredBufferLen ];
    unRequiredBufferLen = pHmd->GetStringTrackedDeviceProperty( unDevice, prop, pchBuffer, unRequiredBufferLen, peError );
    std::string sResult = pchBuffer;
    delete [] pchBuffer;
    return sResult;
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
    // Triggering ImGUI
    ImGui_ImplGlfwGL3_NewFrame();

    RenderHierarchy();
    m_pPluginManager->OnGUI();
    m_postProcessingStack.OnGUI();

    // Gets the projection matrix
    glm::mat4 Projection     = m_projectionMatrix;
    glm::mat4 View           = m_pCamera->GetViewMatrix();
    glm::mat4 ProjectionView = Projection * View;

    DirectionalLight * pLight                = LightManager::GetDirectionalLight();
    std::vector<PointLight *> const& pLights = LightManager::GetPointLights();

    // Shadow mapping
    if(pLight != nullptr)
    {
        glm::mat4 depthProjectionMatrix  = glm::ortho(-100.0f, 100.0f, -100.0f, 100.0f, 0.1f, 5000.0f);
        glm::mat4 depthViewMatrix        = glm::lookAt(-pLight->GetDirection(), glm::vec3(0,0,0), glm::vec3(0, 0, 1));
        glm::mat4 depthModelMatrix       = glm::mat4(1.0);
        glm::mat4 depthMVP               = depthProjectionMatrix * depthViewMatrix * depthModelMatrix;

        uint shadowMapShader = (uint)ShaderManager::GetShaderID("ShadowMap");
        int  shadowMVPID     = glGetUniformLocation(shadowMapShader, "depthMVP");

        // Shader start
        glUseProgram(shadowMapShader);
        glUniformMatrix4fv(shadowMVPID, 1, GL_FALSE, &depthMVP[0][0]);

        // FBO start
        glBindFramebuffer(GL_FRAMEBUFFER, m_shadowMapFbo);
        glViewport(0, 0, 1024, 1024);
        glClear(GL_DEPTH_BUFFER_BIT);

        size_t rendererCount = m_renderers.size();
        for (int nRenderer = 0; nRenderer < rendererCount; ++nRenderer)
        {
            m_triangleCounter += m_renderers[nRenderer]->GetElementCount();
            m_currentTriangle += m_renderers[nRenderer]->GetElementCount();

            glBindVertexArray(m_renderers[nRenderer]->m_vao);
            glEnableVertexAttribArray(0);

            if(m_renderers[nRenderer]->m_isInstantiated)
                glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, m_renderers[nRenderer]->m_elementsCount);
            else if(m_renderers[nRenderer]->m_isIndexed)
                glDrawElements(GL_TRIANGLES, m_renderers[nRenderer]->m_elementsCount, GL_UNSIGNED_SHORT, nullptr);
            else
                glDrawArrays(GL_TRIANGLES, 0, m_renderers[nRenderer]->m_elementsCount);

            glBindVertexArray(0);
        }

        // FBO end
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Shader end
        glUseProgram(0);
    }

    // Post-processing begin
    if(m_bIsPostProcessingEnabled)
    {
        uint lightScatteringID = (uint)ShaderManager::GetShaderID("LightScattering");

        glUseProgram(lightScatteringID);
        int colorLocation  = glGetUniformLocation(lightScatteringID, "fragmentColor");
        int matrixLocation = glGetUniformLocation(lightScatteringID, "MVP");

        // Light scattering pass begin
        glBindFramebuffer(GL_FRAMEBUFFER, m_lightScatteringFbo);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, 1.0f);

        glViewport(0, 0, 1600, 900);

        // Light scattering pass
        if(pLight != nullptr)
        {
            glm::mat4 model = glm::scale(pLight->m_model, glm::vec3(10.0f, 10.0f, 10.0f));
            glm::mat4 MVP   = ProjectionView * model;

            glUniform3f       (colorLocation,  1.0f, 1.0f, 1.0f);
            glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &MVP[0][0]);

            glBindVertexArray(pLight->m_vao);
            glEnableVertexAttribArray(0);

            glDrawArrays(GL_TRIANGLES, 0, pLight->m_elementsCount);

            glBindVertexArray(0);
        }

        glUniform3f       (colorLocation,  0.0f, 0.0f, 0.0f);

        size_t rendererCount = m_renderers.size();
        for (int nRenderer = 0; nRenderer < rendererCount; ++nRenderer)
        {
            m_triangleCounter += m_renderers[nRenderer]->GetElementCount();
            m_currentTriangle += m_renderers[nRenderer]->GetElementCount();

            glm::mat4 MVP  = ProjectionView * m_renderers[nRenderer]->m_model;

            glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, &MVP[0][0]);

            glBindVertexArray(m_renderers[nRenderer]->m_vao);
            glEnableVertexAttribArray(0);

            if(m_renderers[nRenderer]->m_isInstantiated)
                glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, m_renderers[nRenderer]->m_elementsCount);
            else if(m_renderers[nRenderer]->m_isIndexed)
                glDrawElements(GL_TRIANGLES, m_renderers[nRenderer]->m_elementsCount, GL_UNSIGNED_SHORT, nullptr);
            else
                glDrawArrays(GL_TRIANGLES, 0, m_renderers[nRenderer]->m_elementsCount);

            glBindVertexArray(0);
        }

        // Light scattering pass end
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        m_postProcessingStack.OnPostProcessingBegin(m_lightScatteringTexture, m_shadowMapTexture);
    }
    else
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, 1600, 900);
    }

    // Clearing buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Lighting
    LightManager::OnRenderBegin();

    if(m_bStereoscopicRendering)
    {
        RenderStereoTarget();

        vr::Texture_t leftEyeTexture = {(void*)(uintptr_t)leftEyeDesc.m_nResolveTextureId, vr::TextureType_OpenGL, vr::ColorSpace_Gamma };
        vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture );
        vr::Texture_t rightEyeTexture = {(void*)(uintptr_t)rightEyeDesc.m_nResolveTextureId, vr::TextureType_OpenGL, vr::ColorSpace_Gamma };
        vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture );
        // vr::VRCompositor()->ShowMirrorWindow(); (No need anymore)

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, 1600, 900);

        // Clears the buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        uint shaderID = (uint)ShaderManager::GetShaderID("VRMirror");
        glUseProgram(shaderID);

        int leftEyeID  = glGetUniformLocation(shaderID, "leftEyeTexture");
        int rightEyeID = glGetUniformLocation(shaderID, "rightEyeTexture");

        glActiveTexture(GL_TEXTURE0);
        glBindTexture  (GL_TEXTURE_2D, leftEyeDesc.m_nResolveTextureId);
        glUniform1i(leftEyeID,  0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture  (GL_TEXTURE_2D, rightEyeDesc.m_nResolveTextureId);
        glUniform1i(rightEyeID, 1);

        glBindVertexArray(m_HMDVao);
        glEnableVertexAttribArray(0);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDisableVertexAttribArray(0);

        glUseProgram(0);
    }
    else
    {
        // Draw
        size_t rendererCount = m_renderers.size();
        for (int nRenderer = 0; nRenderer < rendererCount; ++nRenderer)
        {
            m_triangleCounter += m_renderers[nRenderer]->GetElementCount();
            m_currentTriangle += m_renderers[nRenderer]->GetElementCount();
            m_renderers[nRenderer]->Draw(Projection, View, glm::vec3(0.0f, 0.0f, 0.0f), LightManager::GetNearestPointLights(m_renderers[nRenderer]->GetPosition()));
        }
    }

    // Cleanup
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);

#ifdef CARDINAL_DEBUG
    DebugManager::Draw(ProjectionView);
#endif

    if(m_bIsPostProcessingEnabled)
    {
        m_postProcessingStack.OnPostProcessingRender();
        m_postProcessingStack.OnPostProcessingEnd();
    }

    DisplayDebugWindow(step);
    m_currentTriangle = 0;

    // Draw ImGUI
    ImGui::Render();
    ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

    // Display
    glfwSwapBuffers(m_window.GetContext());
}

/// \brief Renders the scene in stereo
void RenderingEngine::RenderStereoTarget()
{
    UpdateHMDPositions();

    glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, 1.0f);
    glEnable(GL_MULTISAMPLE);

    // Left Eye
    glBindFramebuffer(GL_FRAMEBUFFER, leftEyeDesc.m_nRenderFramebufferId);
    glViewport(0, 0, m_nRenderWidth, m_nRenderHeight);
    RenderScene(vr::Eye_Left);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glDisable(GL_MULTISAMPLE);

    glBindFramebuffer(GL_READ_FRAMEBUFFER, leftEyeDesc.m_nRenderFramebufferId);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, leftEyeDesc.m_nResolveFramebufferId );

    glBlitFramebuffer(0, 0, m_nRenderWidth, m_nRenderHeight, 0, 0, m_nRenderWidth, m_nRenderHeight,
                       GL_COLOR_BUFFER_BIT,
                       GL_LINEAR);

    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    glEnable(GL_MULTISAMPLE);

    // Right Eye
    glBindFramebuffer( GL_FRAMEBUFFER, rightEyeDesc.m_nRenderFramebufferId );
    glViewport(0, 0, m_nRenderWidth, m_nRenderHeight );
    RenderScene(vr::Eye_Right);
    glBindFramebuffer( GL_FRAMEBUFFER, 0);

    glDisable(GL_MULTISAMPLE);

    glBindFramebuffer(GL_READ_FRAMEBUFFER, rightEyeDesc.m_nRenderFramebufferId );
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, rightEyeDesc.m_nResolveFramebufferId );

    glBlitFramebuffer(0, 0, m_nRenderWidth, m_nRenderHeight, 0, 0, m_nRenderWidth, m_nRenderHeight,
                       GL_COLOR_BUFFER_BIT,
                       GL_LINEAR);

    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

glm::mat4 RenderingEngine::ConvertOpenVRMatrixToGLM( const vr::HmdMatrix34_t &matPose )
{
    glm::mat4 matrixObj(
            matPose.m[0][0], matPose.m[1][0], matPose.m[2][0], 0.0,
            matPose.m[0][1], matPose.m[1][1], matPose.m[2][1], 0.0,
            matPose.m[0][2], matPose.m[1][2], matPose.m[2][2], 0.0,
            matPose.m[0][3], matPose.m[1][3], matPose.m[2][3], 1.0f
    );
    return matrixObj;
}

/// \brief Updates HMD matrix positions
void RenderingEngine::UpdateHMDPositions()
{
    if ( !m_pHMD )
        return;

    vr::VRCompositor()->WaitGetPoses(m_rTrackedDevicePose, vr::k_unMaxTrackedDeviceCount, NULL, 0 );

    m_iValidPoseCount = 0;
    m_strPoseClasses = "";
    for ( int nDevice = 0; nDevice < vr::k_unMaxTrackedDeviceCount; ++nDevice )
    {
        if ( m_rTrackedDevicePose[nDevice].bPoseIsValid )
        {
            m_iValidPoseCount++;
            m_rmat4DevicePose[nDevice] = ConvertOpenVRMatrixToGLM(m_rTrackedDevicePose[nDevice].mDeviceToAbsoluteTracking);
            if (m_rDevClassChar[nDevice]==0)
            {
                switch (m_pHMD->GetTrackedDeviceClass(nDevice))
                {
                    case vr::TrackedDeviceClass_Controller:        m_rDevClassChar[nDevice] = 'C'; break;
                    case vr::TrackedDeviceClass_HMD:               m_rDevClassChar[nDevice] = 'H'; break;
                    case vr::TrackedDeviceClass_Invalid:           m_rDevClassChar[nDevice] = 'I'; break;
                    case vr::TrackedDeviceClass_GenericTracker:    m_rDevClassChar[nDevice] = 'G'; break;
                    case vr::TrackedDeviceClass_TrackingReference: m_rDevClassChar[nDevice] = 'T'; break;
                    default:                                       m_rDevClassChar[nDevice] = '?'; break;
                }
            }
            m_strPoseClasses += m_rDevClassChar[nDevice];
        }
    }

    if ( m_rTrackedDevicePose[vr::k_unTrackedDeviceIndex_Hmd].bPoseIsValid )
    {
        m_mat4HMDPose = m_rmat4DevicePose[vr::k_unTrackedDeviceIndex_Hmd];
        m_mat4HMDPose = glm::inverse(m_mat4HMDPose);
    }
}

/// \brief Renders the scene for a particular eye
void RenderingEngine::RenderScene(vr::Hmd_Eye nEye)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // Draw
    size_t rendererCount = m_renderers.size();
    for (int nRenderer = 0; nRenderer < rendererCount; ++nRenderer)
    {
        m_triangleCounter += m_renderers[nRenderer]->GetElementCount();
        m_currentTriangle += m_renderers[nRenderer]->GetElementCount();

        // Hot code
        glm::mat4 hmdViewMatrix = GetHMDMatrixPoseEye(nEye) * glm::translate(m_mat4HMDPose, glm::vec3(-200.0f, -300.0f, 200.0f));
        hmdViewMatrix           = glm::rotate(hmdViewMatrix, -(float)M_PI_2,   glm::vec3(1.0f, 0.0f, 0.0f));
        m_renderers[nRenderer]->Draw(GetHMDMatrixProjectionEye(nEye), hmdViewMatrix, glm::vec3(0.0f, 0.0f, 0.0f), LightManager::GetNearestPointLights(m_renderers[nRenderer]->GetPosition()));
    }
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

/// \brief Initializes the VR rendering
/* static */ bool RenderingEngine::InitializeStereoscopicRendering()
{
    ASSERT_NOT_NULL(RenderingEngine::s_pInstance);
    bool ret = s_pInstance->InitStereoscopicRendering();

    if(ret)
    {
        s_pInstance->m_bStereoscopicRendering = true;
        return true;
    }

    s_pInstance->m_bStereoscopicRendering = false;
    return false;
}

/// \brief Returns a pointer on the HMD
/// \return A pointer on the current HMD
/* static */ vr::IVRSystem *RenderingEngine::GetHMD()
{
    ASSERT_NOT_NULL(RenderingEngine::s_pInstance);
    return s_pInstance->m_pHMD;
}

/// \brief Register a custom renderer in the engine
/// \param pRenderer The renderer to register
/* static */ void RenderingEngine::RegisterCustomRenderer(IRenderer * pRenderer)
{
    ASSERT_NOT_NULL(RenderingEngine::s_pInstance);
    RenderingEngine::s_pInstance->m_renderers.push_back((IRenderer *)pRenderer);
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
/* static */ void RenderingEngine::ReleaseRenderer(IRenderer *& pRenderer)
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

/// \brief Allocates and return a pointer on a particle system
///        Registers the system into the engine
/* static */ ParticleSystem * RenderingEngine::AllocateParticleSystem()
{
    ASSERT_NOT_NULL(RenderingEngine::s_pInstance);

    ParticleSystem * pSystem = new ParticleSystem(); // NOLINT
    RenderingEngine::s_pInstance->m_paricleSystems.push_back(pSystem);

    // Auto-registration of the internal renderer
    RegisterCustomRenderer(&pSystem->m_renderer);

    return pSystem;
}

/// \brief Deallocates the given system
/// \param pSystem The particle system to deallocate
/* static */ void RenderingEngine::ReleaseParticleSystem(ParticleSystem *& pSystem)
{
    ASSERT_NOT_NULL(RenderingEngine::s_pInstance);

    int index = -1;
    size_t count = RenderingEngine::s_pInstance->m_paricleSystems.size();
    for (size_t nSystem = 0; nSystem < count; ++nSystem)
    {
        if (RenderingEngine::s_pInstance->m_paricleSystems[nSystem] == pSystem)
        {
            index = static_cast<int>(nSystem);
            break;
        }
    }

    if (index != -1)
    {
        RenderingEngine::s_pInstance->m_paricleSystems.erase(
                RenderingEngine::s_pInstance->m_paricleSystems.begin() + index);
    }

    // Auto-removal of the internal renderer
    IRenderer * pRenderer = &pSystem->m_renderer;
    ReleaseRenderer(pRenderer);

    delete pSystem;
    pSystem = nullptr;
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

/// \brief Sets the state of the post-processing
/// \param bActive The new state
/* static */ void RenderingEngine::SetPostProcessingActive(bool bActive)
{
    ASSERT_NOT_NULL(RenderingEngine::s_pInstance);
    s_pInstance->m_bIsPostProcessingEnabled = bActive;
}

/// \brief Tells if the post-processing is active or not
/// \return True or false
/* static */ bool RenderingEngine::IsPostProcessingActive()
{
    ASSERT_NOT_NULL(RenderingEngine::s_pInstance);
    return s_pInstance->m_bIsPostProcessingEnabled;
}

/// \brief Returns a pointer on the post-processing stack
/// \return A pointer on the post-processing stack
/* static */ PostProcessingStack *RenderingEngine::GetPostProcessingStack()
{
    ASSERT_NOT_NULL(RenderingEngine::s_pInstance);
    return &(s_pInstance->m_postProcessingStack);
}

/// \brief Displays a window with debug information
/// \param step The current step
void RenderingEngine::DisplayDebugWindow(float step)
{
    if (m_debugWindow)
    {
        ImGui::Begin        ("Cardinal debug", &m_debugWindow);
        ImGui::SetWindowPos ("Cardinal debug", ImVec2(10.0f, 10.0f));
        ImGui::SetWindowSize("Cardinal debug", ImVec2(250.0f, 455.0f));

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
        ImGui::Text("Plugin : %lu", m_pPluginManager->GetPluginCount());

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

        // Post-processing
        ImGui::Text("\nPost-processing");
        ImGui::Text("Active shaders : %d", m_postProcessingStack.GetActivePostProcessShaders());

        // Camera
        glm::vec3 const& position  = m_pCamera->GetPosition();
        glm::vec3 const& direction = m_pCamera->GetDirection();
        ImGui::Text("\nMain camera");
        ImGui::Text("Pos xyz : %4.2lf %4.2lf %4.2lf", position.x,  position.y,  position.z);
        ImGui::Text("Dir xyz : %4.2lf %4.2lf %4.2lf", direction.x, direction.y, direction.z);

        ImGui::End();
    }

    if(m_debugTime)
    {
        ImGui::Begin        ("Engine debug", &m_debugTime);
        ImGui::SetWindowPos ("Engine debug", ImVec2(530.0f, 10.0f));
        ImGui::SetWindowSize("Engine debug", ImVec2(580.0f, 50.0f));

        // Computes percentage
        float timeSum = m_renderingTime + m_audioTime + m_pluginTime;

        float renderingPercent = (m_renderingTime / timeSum) * 100.0f;
        float audioPercent     = (m_audioTime     / timeSum) * 100.0f;
        float pluginPercent    = (m_pluginTime    / timeSum) * 100.0f;

        if(renderingPercent >= 99.0f)
        {
            renderingPercent = 100.0f;
        }

        ImGui::Text("Rendering %.3f (%.2f %)\t Audio %.3f (%.2f %)\t Plugins %.3f (%.2f %)",
                    m_renderingTime, renderingPercent,
                    m_audioTime,     audioPercent,
                    m_pluginTime,    pluginPercent);

        ImGui::End();
    }
}

/// \brief Called each frame
/// \param dt The elapsed time
void RenderingEngine::Update(float dt)
{
    DebugManager::Clear();

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

    for(ParticleSystem * pSystem : m_paricleSystems)
    {
        pSystem->Update(dt);
    }
}

/// \brief Updates the values of the time passed into other engine parts
void RenderingEngine::UpdateEngineTime(float audioTime, float renderingTime, float pluginTime)
{
    m_audioTime     = audioTime;
    m_pluginTime    = pluginTime;
    m_renderingTime = renderingTime;
}

/// \brief Returns the projection view matrix
/* static */ glm::mat4 const& RenderingEngine::GetProjectionMatrix()
{
    ASSERT_NOT_NULL(RenderingEngine::s_pInstance);
    return s_pInstance->m_projectionMatrix;
}

/// \brief Returns the view matrix
/* static */ glm::mat4 RenderingEngine::GetViewMatrix()
{
    ASSERT_NOT_NULL(RenderingEngine::s_pInstance);
    return s_pInstance->m_pCamera->GetViewMatrix();
}

/// \brief Called to render the hierarchy
void RenderingEngine::RenderHierarchy()
{
    // ImGui::ShowDemoWindow(&m_debugWindow);

    ImGui::Begin        ("Scene explorer", &m_debugWindow);
    ImGui::SetWindowPos ("Scene explorer", ImVec2(1300, 10));
    ImGui::SetWindowSize("Scene explorer", ImVec2(290, 500));

    ImGui::TextColored(ImVec4(1,1,0,1), "Hierarchy\n\n");

    std::vector<Inspector *>  items;
    std::vector<const char *> cnames;

    // Camera
    items.emplace_back(m_pCamera);

    // Lights
    if(LightManager::GetDirectionalLight() != nullptr)
        items.emplace_back(LightManager::GetDirectionalLight());

    std::vector <PointLight*> pointLights = LightManager::GetPointLights();
    for(PointLight * pLight : pointLights)
        items.emplace_back(pLight);

    // Particles
    for(ParticleSystem * pSystem : m_paricleSystems)
        items.emplace_back(pSystem);

    // Renderer
    for(IRenderer * pRenderer : m_renderers)
        items.emplace_back(pRenderer);

    // Generating names
    for(Inspector * pInspector : items)
        cnames.emplace_back(pInspector->inspectorName.c_str());

    static int listbox_item_current = 0;

    ImGui::PushItemWidth(280);
    ImGui::ListBox("###Hierarchy", &listbox_item_current, cnames.data(), (int)cnames.size(), 14);
    ImGui::PopItemWidth();

    ImGui::TextColored(ImVec4(1,1,0,1), "Inspector\n\n");

    ImGui::BeginChild("");
    items[listbox_item_current]->OnInspectorGUI();
    ImGui::EndChild();

    ImGui::End();
}

} // !namespace