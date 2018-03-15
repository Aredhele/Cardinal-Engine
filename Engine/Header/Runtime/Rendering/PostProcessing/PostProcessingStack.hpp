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

/// \file       PostProcessingStack.hpp
/// \date       02/03/2018 
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/PostProcessing
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_POST_PROCESSING_STACK_HPP__
#define CARDINAL_ENGINE_POST_PROCESSING_STACK_HPP__

#include <vector>

#include "Runtime/Platform/Configuration/Type.hh"
#include "Runtime/Rendering/PostProcessing/PostEffects/PostEffect.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/Identity.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/Mirror.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/Negative.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/Sepia.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/BoxBlur.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/GaussianBlur.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/Sharpen.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/EdgeDetection.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/DepthBuffer.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/GodRay.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/LightScattering.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/Bloom.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/Vignette.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/FXAA.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/ShadowMap.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/DepthOfField.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/Fog.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/Experimental/Experimental1.hpp"
#include "Runtime/Rendering/PostProcessing/PostEffects/Experimental/Experimental2.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \class PostProcessingStack
/// \brief Provides to the user a way to add post-processing effects
class PostProcessingStack
{
public:

    /// \brief Returns the wanted effects
    /// \param type The type of the effect
    /// \return A pointer on the effect
    PostEffect * GetPostEffect(PostEffect::EType type);

    /// \brief Enables or disable an effect
    /// \param type The type of the effect
    void SetEffectActive(PostEffect::EType type, bool bActive);

private:

    friend class RenderingEngine;

    /// \brief Constructor
    PostProcessingStack();

    /// \brief Destructor
    ~PostProcessingStack();

    /// \brief Initializes the post processing stack
    void Initialize();

    /// \brief Release the post processing stack
    void Release();

    /// \brief Called at the beginning of the frame
    void OnPostProcessingBegin(uint lightScatteringTextureID, uint shadowMapTextureID);

    /// \brief Called to render effects
    void OnPostProcessingRender();

    /// \brief Called at the end of the frame
    void OnPostProcessingEnd();

    /// \brief Called to draw a small GUI to tweak post effects
    void OnGUI();

    /// \brief Returns the current count of active shader
    /// \return The count of active shaders
    int GetActivePostProcessShaders() const;

private:

    // QUAD
    uint m_postProcessVao;
    uint m_postProcessQuadVbo;

    // FBO 1
    uint m_postProcessFbo;
    uint m_postProcessRbo;
    uint m_postProcessTexture;
    uint m_postProcessDepthTexture;

    // FBO 2
    uint m_postProcessFboBuffer;
    uint m_postProcessTextureBuffer;

    // PostEffects stack
    std::vector <PostEffect *> m_stack;

    // Light scattering
    uint m_lightScatteringTextureID;

    // Shadowing
    uint m_shadowMapTextureID;

    // ImGUI
    bool m_postProcessWindow;
};

} // !namespace 

#endif // !CARDINAL_ENGINE_POST_PROCESSING_STACK_HPP__