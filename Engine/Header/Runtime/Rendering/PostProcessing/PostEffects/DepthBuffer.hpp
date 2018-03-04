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

/// \file       DepthBuffer.hpp
/// \date       04/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/PostProcessing/PostEffects
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_DEPTH_BUFFER_HPP__
#define CARDINAL_ENGINE_DEPTH_BUFFER_HPP__

#include "Runtime/Rendering/PostProcessing/PostEffects/PostEffect.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \class DepthBuffer
/// \brief Not really a post effect, but displays the depth buffer
class DepthBuffer : public PostEffect
{
public:

    // None

private:

    friend class PostProcessingStack;

    /// \brief Constructor
    DepthBuffer();

    /// \brief Destructor
    ~DepthBuffer();

    /// \brief Applies the effect from the given textures
    /// \param colorTexture The color texture
    /// \param depthTexture The depth buffer texture
    void ApplyEffect(uint colorTexture, uint depthTexture) final;
};

} // !namespace

#endif // !CARDINAL_ENGINE_DEPTH_BUFFER_HPP__