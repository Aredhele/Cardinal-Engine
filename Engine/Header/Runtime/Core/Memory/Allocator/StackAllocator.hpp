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

/// \file       StackAllocator.hpp
/// \date       18/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Core/Memory/Allocator
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_STACK_ALLOCATOR_HPP__
#define CARDINAL_ENGINE_STACK_ALLOCATOR_HPP__

#include "Runtime/Core/Assertion/Assert.hh"

/// \namespace cardinal
namespace cardinal
{

/// \class StackAllocator
/// \brief Simple stack allocator
class StackAllocator
{
public:

    /// \brief Constructor
    StackAllocator();

    /// \brief Destructor
    ~StackAllocator();

    /// \brief  Allocates nBytes at the top of the stack
    ///         and returns a pointer on the allocated memory
    /// \return A pointer on the allocated memory
    void Initialize(uint64 size);

    /// \brief Releases memory
    void Release();

    /// \brief  Resets the head
    /* inline */ void Clear();

    /// \brief  Allocates nBytes at the top of the stack
    ///         and returns a pointer on the allocated memory
    /// \return A pointer on the allocated memory
    /* inline */ void * Allocate(uint64 nBytes);

    /// \brief  Returns the size of the allocator
    /// \return The amout of allocated memory in bytes
    /* inline */ uint64 GetSize() const;

private:

    uint64  m_size;  ///< The size in bytes of the allocator
    uint64  m_head;  ///< The current position in the stack
    uchar * m_pData; ///< The memory buffer
};

} // !namespace

#include "Runtime/Core/Memory/Allocator/Impl/StackAllocator.inl"

#endif // !CARDINAL_ENGINE_STACK_ALLOCATOR_HPP__