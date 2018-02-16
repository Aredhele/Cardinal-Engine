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

/// \file       Window.cpp
/// \date       10/02/2018
/// \project    Cardinal Engine
/// \package    Rendering/Context
/// \author     Vincent STEHLY--CALISTO

#include "Glew/include/GL/glew.h"

#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Core/Assertion/Assert.hh"
#include "Runtime/Rendering/Context/Window.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Default constructor
Window::Window()
: m_pWindow(nullptr)
{
    // None
}

/// \brief  Constructor
/// \param  width The width of the window
/// \param  height The heigth of the window
/// \param  szTitle The title of the window
Window::Window(int width, int height, const char *szTitle)
: m_pWindow(nullptr)
{
    Initialize(width, height, szTitle);
}

/// \brief  Destructor
Window::~Window()
{
    Destroy();
}

/// \brief  Initializes the OpenGL context
/// \param  width The width of the window
/// \param  height The heigth of the window
/// \param  szTitle The title of the window
void Window::Initialize(int width, int height, const char *szTitle)
{
    // Pre-conditions
    ASSERT_GT(width,  0);
    ASSERT_GT(height, 0);

    ASSERT_LT(width, 1920);
    ASSERT_LT(height, 1080);

    if(m_pWindow != nullptr)
    {
        Destroy();
    }

    // Initializes GLFW
    if(!glfwInit())
    {
        Logger::LogError("Failed to initialize GLFW.");
        return;
    }
    else
    {
        Logger::LogInfo("GLFW successfully initialized.");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creates the OpenGL context in 3.3
    m_pWindow = glfwCreateWindow(width, height, szTitle, nullptr, nullptr);
    if(m_pWindow == nullptr)
    {
        Logger::LogError(
                "Unable to create the OpenGL context."
                "Your openGL version must be at least 3.3.");

        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(m_pWindow);
    glewExperimental = 1;
    if (glewInit() != GLEW_OK)
    {
        Logger::LogError("Failed to initialized glew");
        Destroy();
        return;
    }

    Logger::LogInfo("Context successfully initialized.");
    Logger::LogInfo("OpenGL Version %s", glGetString(GL_VERSION));

    // Post-conditions
    ASSERT_NOT_NULL(m_pWindow);
}

/// \brief Destroy the current OpenGL context
void Window::Destroy()
{
    if(m_pWindow != nullptr)
    {
        glfwDestroyWindow(m_pWindow);
        glfwTerminate();
    }
}

/// \brief  Returns the current glfw window
/// \return A pointer on the glfw window
GLFWwindow * Window::GetContext() const
{
    return m_pWindow;
}

} // !namespace




