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

/// \file       PostEffect.cpp
/// \date       02/03/2018
/// \project    Cardinal Engine
/// \package    Runtime/Rendering/PostProcessing/PostEffects
/// \author     Vincent STEHLY--CALISTO

#include "Runtime/Rendering/PostProcessing/PostEffects/PostEffect.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
/// \param type The type of the effect
/// \param name The name of the post-effect
PostEffect::PostEffect(PostEffect::EType type, std::string const& name)
{
    m_type      = type;
    m_bIsActive = false;
    m_name      = name;
    m_shaderID  = 0;

    m_colorTextureID = -1;
    m_depthTextureID = -1;
}

/// \brief Returns the name of the post effect
std::string const& PostEffect::GetName() const
{
    return m_name;
}

/// \brief Enables or disable the effect
/// \param bActive The new state
void PostEffect::SetActive(bool bActive)
{
    m_bIsActive = bActive;
}

/// \brief Tells if the effect is active
/// \return True or false
bool PostEffect::IsActive() const
{
    return m_bIsActive;
}

} // !namespace