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

/// \file       StackAllocator.cpp
/// \date       19/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Core/Memory/Allocator
/// \author     Vincent STEHLY--CALISTO

#include "Runtime/Core/Memory/Allocator/StackAllocator.hpp"

/// \namespace cardinal
namespace cardinal
{

/// \brief Constructor
StackAllocator::StackAllocator()
: m_size(0)
, m_head(0)
, m_pData(nullptr)
{
    // None
}

/// \brief Destructor
StackAllocator::~StackAllocator()
{
    Release();
}

/// \brief Initializes the stack allocator by allocating
///        size bytes
/// \param size The amount of bytes to allocate
void StackAllocator::Initialize(uint64 size)
{
    ASSERT_NE(size, 0);
    ASSERT_LT(size, 1024 * 1024 * 4); // 4 Mio max

    Release();

    m_head  = 0;
    m_size  = size;
    m_pData = new uchar[m_size];

    ASSERT_NOT_NULL(m_pData);
}

/// \brief Releases memory
void StackAllocator::Release()
{
    delete[] m_pData;

    m_head  = 0;
    m_size  = 0;
    m_pData = nullptr;
}

} // !namespace