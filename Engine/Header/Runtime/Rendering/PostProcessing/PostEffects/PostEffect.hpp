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

/// \file       PostEffect.hpp
/// \date       02/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/PostProcessing/PostEffects
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_POST_EFFECT_HPP__
#define CARDINAL_ENGINE_POST_EFFECT_HPP__

#include <string>
#include "Runtime/Platform/Configuration/Type.hh"

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_glfw_gl3.h"
#include "ImGUI/imgui_internal.h"

/// \namespace cardinal
namespace cardinal
{

/// \class PostEffect
/// \brief
class PostEffect
{
public:

    /// \enum The type of the post-effect
    enum EType
    {
        Identity,
        Mirror,
        Negative,
        Sepia,
        BoxBlur,
        GaussianBlur,
        Sharpen,
        EdgeDetection,
        DepthBuffer,
        GodRay,
        LightScattering,
        Bloom,
        Vignette,
        Experimental1,
        Experimental2
    };

    /// \brief Returns the name of the post effect
    std::string const& GetName() const;

protected:

    friend class PostProcessingStack;

    /// \brief Constructor
    /// \param type The type of the effect
    /// \param name The name of the post-effect
    PostEffect(EType type, std::string const& name);

    /// \brief Enables or disable the effect
    /// \param bActive The new state
    void SetActive(bool bActive);

    /// \brief Tells if the effect is active
    /// \return True or false
    bool IsActive() const;

    /// \brief Applies the effect from the given textures
    /// \param colorTexture The color texture
    /// \param depthTexture The depth buffer texture
    /// \param lightScatteringTexture The result of the light scattering pass
    virtual void ApplyEffect(uint colorTexture, uint depthTexture, uint lightScatteringTexture) = 0;

    /// \brief Called to display the GUI
    virtual void OnGUI() = 0;

protected:

    EType       m_type;
    bool        m_bIsActive;
    std::string m_name;

    uint  m_shaderID;
    int   m_colorTextureID;
    int   m_depthTextureID;
};

} // !namespace

#endif // !CARDINAL_ENGINE_POST_EFFECT_HPP__