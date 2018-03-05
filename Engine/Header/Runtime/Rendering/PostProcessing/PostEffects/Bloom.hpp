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

/// \file       Bloom.hpp
/// \date       05/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/PostProcessing/PostEffects
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_BLOOM_HPP__
#define CARDINAL_ENGINE_BLOOM_HPP__

#include <ThirdParty/Glm/glm/vec3.hpp>
#include "Runtime/Rendering/PostProcessing/PostEffects/PostEffect.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \class Bloom
/// \brief Basic glow effect
class Bloom : public PostEffect
{
public:

    // None

private:

    friend class PostProcessingStack;

    /// \brief Constructor
    Bloom();

    /// \brief Destructor
    ~Bloom();

    /// \brief Applies the effect from the given textures
    /// \param colorTexture The color texture
    /// \param depthTexture The depth buffer texture
    /// \param lightScatteringTexture The result of the light scattering pass
    void ApplyEffect(uint colorTexture, uint depthTexture, uint lightScatteringTexture) final;

    /// \brief Called to draw the GUI
    void OnGUI() final;

private:

    glm::vec3 m_color;
    float     m_quality;
    int       m_sampleCount;

    int       m_colorID;
    int       m_qualityID;
    int       m_sampleCountID;
};

} // !namespace

#endif // !CARDINAL_ENGINE_BLOOM_HPP__