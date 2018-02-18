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

/// \file       StackAllocator.inl
/// \date       18/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Core/Memory/Allocator
/// \author     Vincent STEHLY--CALISTO

/// \namespace cardinal
namespace cardinal
{

/// \brief  Allocates nBytes at the top of the stack
///         and returns a pointer on the allocated memory
/// \return A pointer on the allocated memory
inline void * StackAllocator::Allocate(uint64 nBytes)
{
    ASSERT_LT      (m_head + nBytes, m_size);
    ASSERT_NOT_NULL(m_pData);

    void * pointer = m_pData + m_head;
    m_head += nBytes;

    return pointer;
}

/// \brief  Resets the head
inline void StackAllocator::Clear()
{
    m_head = 0;
}

/// \brief  Returns the size of the allocator
/// \return The amout of allocated memory in bytes
inline uint64 StackAllocator::GetSize() const
{
    return m_size;
}

} // !namespace