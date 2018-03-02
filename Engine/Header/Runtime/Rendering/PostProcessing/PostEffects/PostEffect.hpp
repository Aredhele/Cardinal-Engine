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

#include "Runtime/Platform/Configuration/Type.hh"

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
        Mirror
    };

    /// \brief Enables or disable the effect
    /// \param bActive The new state
    void SetActive(bool bActive);

    /// \brief Tells if the effect is active
    /// \return True or false
    bool IsActive() const;

protected:

    EType m_type;
    bool  m_bIsActive;

    uint  m_slot;
    uint  m_shaderID;
};

} // !namespace

#endif // !CARDINAL_ENGINE_POST_EFFECT_HPP__