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

/// \file       PostProcessingStack.cpp
/// \date       02/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/PostProcessing
/// \author     Vincent STEHLY--CALISTO


#include "Glew/include/GL/glew.h"

#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Rendering/PostProcessing/PostProcessingStack.hpp"

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw_gl3.h"
#include "ImGUI/imgui_internal.h"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
PostProcessingStack::PostProcessingStack()
{
    m_postProcessVao          = 0;
    m_postProcessFbo          = 0;
    m_postProcessRbo          = 0;
    m_postProcessQuadVbo      = 0;
    m_postProcessTexture      = 0;
    m_postProcessDepthTexture = 0;
    m_shadowMapTextureID      = 0;
}

/// \brief Initializes the post processing stack
PostProcessingStack::~PostProcessingStack() // NOLINT
{
    // None
}

/// \brief Destructor
void PostProcessingStack::Initialize()
{
    Logger::LogInfo("Initializing the post-processing stack");

    // Generating the frame buffer object
    glGenFramebuffers(1, &m_postProcessFbo);
    glBindFramebuffer(GL_FRAMEBUFFER, m_postProcessFbo);

    glGenTextures  (1, &m_postProcessTexture);
    glBindTexture  (GL_TEXTURE_2D, m_postProcessTexture);
    glTexImage2D   (GL_TEXTURE_2D, 0, GL_RGB, 1600, 900, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // FBO to render the depth buffer
    m_postProcessRbo = 0;
    glGenRenderbuffers       (1, &m_postProcessRbo);
    glBindRenderbuffer       (GL_RENDERBUFFER, m_postProcessRbo);
    glRenderbufferStorage    (GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1600, 900);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_postProcessRbo);

    // Texture for the depth texture
    glGenTextures(1, &m_postProcessDepthTexture);
    glBindTexture(GL_TEXTURE_2D, m_postProcessDepthTexture);
    glTexImage2D (GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, 1600, 900, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Binding buffer
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_postProcessTexture,      0);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,  m_postProcessDepthTexture, 0);

    // Attaching the list of buffers to draw
    GLenum DrawBuffers[2] = {GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT};
    glDrawBuffers(2, DrawBuffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        Logger::LogError("Error while creating the post-processing buffers");
    }

    // VAO for the quad
    glGenVertexArrays(1, &m_postProcessVao);
    glBindVertexArray(m_postProcessVao);

    // Quad vertices
    static const GLfloat g_quad_vertex_buffer_data[] =
            {
                    -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, -1.0f,  1.0f, 0.0f,
                    -1.0f,  1.0f, 0.0f, 1.0f, -1.0f, 0.0f,  1.0f,  1.0f, 0.0f,
            };

    glGenBuffers(1, &m_postProcessQuadVbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_postProcessQuadVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)nullptr);

    // Unbind vao
    glBindVertexArray(0);

    // Generating the frame buffer object buffer
    glGenFramebuffers(1, &m_postProcessFboBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_postProcessFboBuffer);

    glGenTextures  (1, &m_postProcessTextureBuffer);
    glBindTexture  (GL_TEXTURE_2D, m_postProcessTextureBuffer);
    glTexImage2D   (GL_TEXTURE_2D, 0, GL_RGB, 1600, 900, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    // Binding buffer
    glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_postProcessTextureBuffer, 0);

    // Attaching the list of buffers to draw
    DrawBuffers[0] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, DrawBuffers);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        Logger::LogError("Error while creating the post-processing buffers");
    }

    m_stack.push_back(new Identity());
    m_stack.push_back(new LightScattering());
    m_stack.push_back(new DepthBuffer());
    m_stack.push_back(new ShadowMap());
    m_stack.push_back(new Mirror());
    m_stack.push_back(new Negative());
    m_stack.push_back(new Sepia());
    m_stack.push_back(new BoxBlur());
    m_stack.push_back(new GaussianBlur());
    m_stack.push_back(new Sharpen());
    m_stack.push_back(new EdgeDetection());
    m_stack.push_back(new GodRay());
    m_stack.push_back(new Bloom());
    m_stack.push_back(new Vignette());
    m_stack.push_back(new FXAA());
    m_stack.push_back(new Experimental1());
    m_stack.push_back(new Experimental2());

    m_postProcessWindow = true;
    Logger::LogInfo("Post-processing stack successfully initialized");
}


/// \brief Release the post processing stack
void PostProcessingStack::Release()
{
    // None
}

/// \brief Called at the beginning of the frame
void PostProcessingStack::OnPostProcessingBegin(uint lightScatteringTextureID, uint shadowMapTextureID)
{
    m_lightScatteringTextureID = lightScatteringTextureID;
    m_shadowMapTextureID       = shadowMapTextureID;

    glBindFramebuffer(GL_FRAMEBUFFER, m_postProcessFbo);
    glViewport(0, 0, 1600, 900);
}

/// \brief Called to render effects
void PostProcessingStack::OnPostProcessingRender()
{
    bool bSwapped = true;

    glBindFramebuffer     (GL_FRAMEBUFFER, m_postProcessFboBuffer);
    glViewport            (0, 0, 1600, 900);
    glFramebufferTexture2D(GL_FRAMEBUFFER , GL_COLOR_ATTACHMENT0 , GL_TEXTURE_2D, m_postProcessTextureBuffer, 0);

    // Processing the stack
    int effectCount = static_cast<int>(m_stack.size());    // NOLINT
    for(int nEffect = 0; nEffect < effectCount; ++nEffect) // NOLINT
    {
        if(m_stack[nEffect]->IsActive())
        {
            if(bSwapped)
            {
                glFramebufferTexture2D(GL_FRAMEBUFFER , GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_postProcessTextureBuffer, 0);
                m_stack[nEffect]->ApplyEffect(m_postProcessTexture, m_postProcessDepthTexture, m_lightScatteringTextureID, m_shadowMapTextureID);
                bSwapped = false;
            }
            else
            {
                glFramebufferTexture2D(GL_FRAMEBUFFER , GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_postProcessTexture, 0);
                m_stack[nEffect]->ApplyEffect(m_postProcessTextureBuffer, m_postProcessDepthTexture, m_lightScatteringTextureID, m_shadowMapTextureID);
                bSwapped = true;
            }

            glBindVertexArray(m_postProcessVao);
            glEnableVertexAttribArray(0);

            glDrawArrays(GL_TRIANGLES, 0, 6);

            glDisableVertexAttribArray(0);
            glBindVertexArray(0);
        }
    }

    // Render the texture on the physical frame buffer
    // Binding physical buffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, 1600, 900);

    // Clears the buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if(bSwapped)
        m_stack[0]->ApplyEffect(m_postProcessTexture, m_postProcessDepthTexture, m_lightScatteringTextureID, m_shadowMapTextureID);
    else
        m_stack[0]->ApplyEffect(m_postProcessTextureBuffer, m_postProcessDepthTexture, m_lightScatteringTextureID, m_shadowMapTextureID);

    glBindVertexArray(m_postProcessVao);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(0);
}

/// \brief Called at the end of the frame
void PostProcessingStack::OnPostProcessingEnd()
{
    // None
}

/// \brief Returns the wanted effects
/// \param type The type of the effect
/// \return A pointer on the effect
PostEffect * PostProcessingStack::GetPostEffect(PostEffect::EType type)
{
    PostEffect * pEffect = nullptr;
    int effectCount = static_cast<int>(m_stack.size());    // NOLINT
    for(int nEffect = 0; nEffect < effectCount; ++nEffect) // NOLINT
    {
        if(m_stack[nEffect]->m_type == type)
        {
            pEffect = m_stack[nEffect];
            break;
        }
    }

    return pEffect;
}

/// \brief Enables or disable an effect
/// \param type The type of the effect
void PostProcessingStack::SetEffectActive(PostEffect::EType type, bool bActive)
{
    int effectCount = static_cast<int>(m_stack.size());    // NOLINT
    for(int nEffect = 0; nEffect < effectCount; ++nEffect) // NOLINT
    {
        if(m_stack[nEffect]->m_type == type)
        {
            m_stack[nEffect]->SetActive(bActive);
        }
    }
}

/// \brief Called to draw a small GUI to tweak post effects
void PostProcessingStack::OnGUI()
{
    ImGui::Begin        ("Post Processing Stack", &m_postProcessWindow);
    ImGui::SetWindowPos ("Post Processing Stack", ImVec2(270.0f, 10.0f));
    ImGui::SetWindowSize("Post Processing Stack", ImVec2(250.0f, 455.0f));

    int effectCount = static_cast<int>(m_stack.size());    // NOLINT
    for(int nEffect = 0; nEffect < effectCount; ++nEffect) // NOLINT
    {
        if (ImGui::CollapsingHeader(m_stack[nEffect]->GetName().c_str()))
        {
            m_stack[nEffect]->OnGUI();
        }
    }

    ImGui::End();
}

/// \brief Returns the current count of active shader
int PostProcessingStack::GetActivePostProcessShaders() const
{
    int sum = 0;
    int effectCount = static_cast<int>(m_stack.size());    // NOLINT
    for(int nEffect = 0; nEffect < effectCount; ++nEffect) // NOLINT
    {
       if(m_stack[nEffect]->IsActive()) sum++;
    }

    return sum;
}

} // !namespace