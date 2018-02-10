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

/// \file       Window.hpp
/// \date       09/02/2018
/// \project    Cardinal Engine
/// \package    Core/Rendering/Context
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_WINDOW_HPP__
#define CARDINAL_ENGINE_WINDOW_HPP__

#include "Glew/include/GL/glew.h"
#include "Glfw/include/GLFW/glfw3.h"

/// \namespace cardinal
namespace cardinal
{

/// \class  Window
/// \brief
class Window
{
public:

    /// \brief Default constructor
    explicit Window();

    /// \brief  Constructor
    /// \param  width The width of the window
    /// \param  height The heigth of the window
    /// \param  szTitle The title of the window
    explicit Window(int width, int height, const char * szTitle);

    /// \brief  Destructor
    ~Window();

    /// \brief  Initializes the OpenGL context
    /// \param  width The width of the window
    /// \param  height The heigth of the window
    /// \param  szTitle The title of the window
    void Initialize(int width, int height, const char * szTitle);

    /// \brief  Returns the current glfw window
    /// \return A pointer on the glfw window
    GLFWwindow * GetContext() const;

private:

    /// \brief Destroy the current OpenGL context
    void Destroy();

private:

    GLFWwindow * m_pWindow;
};

} // !namespace

#endif // !CARDINAL_ENGINE_WINDOW_HPP__