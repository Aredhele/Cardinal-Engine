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

#include "Runtime/Platform/Configuration/Type.hh"

/// \namespace cardinal
namespace cardinal
{

/// \class PostProcessingStack
/// \brief Provides to the user a way to add post-processing effects
class PostProcessingStack
{
public:


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

private:

    uint m_postProcessVao;
    uint m_postProcessFbo;
    uint m_postProcessRbo;
    uint m_postProcessQuadVbo;
    uint m_postProcessTexture;
    uint m_postProcessDepthTexture;
};
    
} // !namespace 

#endif // !CARDINAL_ENGINE_POST_PROCESSING_STACK_HPP__