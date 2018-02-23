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

/// \file       RenderingEngine.hpp
/// \date       09/02/2018
/// \project    Cardinal Engine
/// \package    Core/Rendering
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_RENDERING_ENGINE_HPP__
#define CARDINAL_ENGINE_RENDERING_ENGINE_HPP__

#include <vector>
#include "Runtime/Rendering/Context/Window.hpp"
#include "Runtime/Rendering/Camera/Camera.hpp"

/// \namespace cardinal
namespace cardinal
{

namespace beta
{
    class BetaRenderer;
}

/// \class  RenderingEngine
/// \brief  Main rendering class
class RenderingEngine
{
public:

    /// Initializes the rendering engine from parameters
    /// \param width The width of the window
    /// \param height The height of the window
    /// \param szTitle The title of the window
    /// \param fps The fps limit
    /// \param bInterpolate Should the engine interpolate frame ?
    bool Initialize(int width, int height, char const* szTitle, float fps, bool bInterpolate);

    /// \brief Sets the current camera
    void SetCamera(Camera * pCamera);

    /// \brief Renders the frame
    /// \param step The normalized progression in the frame
    void Render(float step);

    /// \brief Shutdown the engine
    void Shutdown();

    /// \brief  Returns a pointer on the window
    Window * GetWindow();

    /// TMP
    glm::mat4 const& GetProjectionMatrix();

public:

    /// \brief Allocates and return a pointer on a renderer
    ///        Registers the renderer into the engine
    static class MeshRenderer * AllocateMeshRenderer();

    /// \brief Allocates and return a pointer on a renderer
    ///        Registers the renderer into the engine
    static class TextRenderer * AllocateTextRenderer();

    /// \brief Deallocates a renderer
    ///        Unregisters the renderer
    /// \param pRenderer The renderer to release
    static void ReleaseRenderer(class IRenderer *& pRenderer);

private:

    /// \brief Frame rendering implementation
    /// \param step The normalized progression in the frame
    void RenderFrame(float step);

private:

    static RenderingEngine * s_pInstance;

private:

    Window   m_window;
    Camera * m_pCamera;

    bool m_bInterpolate;

    double m_frameDelta;
    double m_frameTime;
    double m_frameLag;
    double m_currentTime;
    double m_previousTime;
    double m_currentFps;
    double m_elapsedTime;

    uint64_t  m_fpsCounter;
    uint64_t  m_frameCount;
    glm::mat4 m_projectionMatrix;

    std::vector<class IRenderer*> m_renderers;

    class TextRenderer * m_pEngineName;
    class TextRenderer * m_pCurrentFPS;
    class TextRenderer * m_pTotalFPS;
    class TextRenderer * m_pFrameTime;
};

} // !namespace

#endif // !CARDINAL_ENGINE_RENDERING_ENGINE_HPP__
