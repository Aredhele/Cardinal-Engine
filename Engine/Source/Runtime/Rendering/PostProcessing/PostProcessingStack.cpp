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
}

/// \brief Initializes the post processing stack
PostProcessingStack::~PostProcessingStack()
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

    glGenTextures(1, &m_postProcessTexture);
    glBindTexture(GL_TEXTURE_2D, m_postProcessTexture);

    // TMP : Fixed screen size
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGB, 1600, 900, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    // Texture filtering low preset
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

    Logger::LogInfo("Post-processing stack successfully initialized");
}


/// \brief Release the post processing stack
void PostProcessingStack::Release()
{

}

} // !namespace