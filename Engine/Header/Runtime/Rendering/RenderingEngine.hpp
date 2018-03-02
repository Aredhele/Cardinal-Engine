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
#include "Runtime/Platform/Configuration/Configuration.hh"

#include "Runtime/Rendering/Context/Window.hpp"
#include "Runtime/Rendering/Camera/Camera.hpp"
#include "Runtime/Rendering/PostProcessing/PostProcessingStack.hpp"

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

    /// \brief Sets the plugin manager
    /// \param pManager The plugin manager pointer
    void SetPluginManager(class PluginManager * pManager);

    /// Returns the projection matrix
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

    /// \brief Returns the main camera
    /// \return A pointer on the main camera
    static Camera * GetMainCamera();

    /// \brief  Returns a pointer on the window
    /// \return A pointer on the window
    static Window * GetWindow();

    /// \brief Sets the state of the post-processing
    /// \param bActive The new state
    static void SetPostProcessingActive(bool bActive);

    /// \brief Tells if the post-processing is active or not
    /// \return True or false
    static bool IsPostProcessingActive();

    /// \brief Returns a pointer on the post-processing stack
    /// \return A pointer on the post-processing stack
    static PostProcessingStack * GetPostProcessingStack();

private:

    /// \brief Frame rendering implementation
    /// \param step The normalized progression in the frame
    void RenderFrame(float step);

    /// \brief Displays a window with debug information
    /// \param step The current step
    void DisplayDebugWindow(float step);

private:

    static RenderingEngine * s_pInstance;

private:

    Window   m_window;
    Camera * m_pCamera;
    class PluginManager * m_pPluginManager;

    bool m_debugWindow;
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
    uint64_t  m_currentTriangle;
    uint64_t  m_triangleCounter;
    uint64_t  m_triangleSecond;
    glm::mat4 m_projectionMatrix;

    // Rendering objects
    std::vector<class IRenderer*> m_renderers;

    // Post-processing
    bool                m_bIsPostProcessingEnabled;
    PostProcessingStack m_postProcessingStack;
};

} // !namespace

#endif // !CARDINAL_ENGINE_RENDERING_ENGINE_HPP__
