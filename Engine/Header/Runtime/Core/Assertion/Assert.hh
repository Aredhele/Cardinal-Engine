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

/// \file       Assert.hh
/// \date       10/02/2018
/// \project    Cardinal Engine
/// \package    Core/Assertion
/// \author     Vincent STEHLY--CALISTO

#ifndef CARDINAL_ENGINE_ASSERT_HH__
#define CARDINAL_ENGINE_ASSERT_HH__

#include <string>
#include <cstring>

#include "Runtime/Platform/Configuration/Configuration.hh"

/// \namespace  cardinal
namespace cardinal
{

/// \namespace  impl
/// \brief      Implementation details
namespace impl
{

/// \brief  Displays the assertion message
void assert_print(const char * szName,
                  const char * szExpr,
                  const char * szMsg,
                  const char * szFile,
                  const char * szFunc,
                  int32 line);

/// \brief  Checks if the expression is true
void assert_true(bool bExpr,
                 const char * szExpr,
                 const char * szMsg,
                 const char * szFile,
                 const char * szFunc,
                 int32 line);

/// \brief  Checks sif the expression is false
void assert_false(bool bExpr,
                  const char * szExpr,
                  const char * szMsg,
                  const char * szFile,
                  const char * szFunc,
                  int32 line);

/// \brief  Checks if rhs and lhs are equal
template <class T, class U>
void assert_equal(const T & lhs,
                  const U & rhs,
                  const char * szLhs,
                  const char * szRhs,
                  const char * szMsg,
                  const char * szFile,
                  const char * szFunc,
                  int32 line);

/// \brief  Checks if rhs and lhs are different
template <class T, class U>
void assert_non_equal(const T & lhs,
                      const U & rhs,
                      const char * szLhs,
                      const char * szRhs,
                      const char * szMsg,
                      const char * szFile,
                      const char * szFunc,
                      int32 line);

/// \brief  Checks if ptr is null pointer
void assert_is_null(void * ptr,
                    const char * szExpr,
                    const char * szMsg,
                    const char * szFile,
                    const char * szFunc,
                    int32 line);

/// \brief  Checks if ptr is not null pointer
void assert_is_not_null(void * ptr,
                        const char * szExpr,
                        const char * szMsg,
                        const char * szFile,
                        const char * szFunc,
                        int32 line);

/// \brief  Checks if rhs is greater than lhs
template <class T, class U>
void assert_is_greater_than(const T & lhs,
                            const U & rhs,
                            const char * szLhs,
                            const char * szRhs,
                            const char * szMsg,
                            const char * szFile,
                            const char * szFunc,
                            int32 line);

/// \brief  Checks if rhs is lower than lhs
template <class T, class U>
void assert_is_lower_than(const T & lhs,
                          const U & rhs,
                          const char * szLhs,
                          const char * szRhs,
                          const char * szMsg,
                          const char * szFile,
                          const char * szFunc,
                          int32 line);

}  // namespace impl

}  // namespace cardinal

#ifdef CARDINAL_DEBUG

#   define ASSERT_TRUE(EXPR) \
        cardinal::impl::assert_true(EXPR, #EXPR, "None", \
             __FILE__, __func__, __LINE__);

#   define ASSERT_FALSE(EXPR) \
        cardinal::impl::assert_false(EXPR, #EXPR, "None", \
            __FILE__, __func__, __LINE__);

#   define ASSERT_EQ(LHS, RHS) \
        cardinal::impl::assert_equal(LHS, RHS, #LHS, #RHS, "None", \
            __FILE__, __func__, __LINE__);

#   define ASSERT_NE(LHS, RHS) \
        cardinal::impl::assert_non_equal(LHS, RHS, #LHS, #RHS, "None", \
            __FILE__, __func__, __LINE__);

#   define ASSERT_NULL(PTR) \
        cardinal::impl::assert_is_null(PTR, #PTR, "None", \
            __FILE__, __func__, __LINE__);

#   define ASSERT_NOT_NULL(PTR) \
        cardinal::impl::assert_is_not_null(PTR, #PTR, "None", \
            __FILE__, __func__, __LINE__);

#   define ASSERT_GT(LHS, RHS) \
        cardinal::impl::assert_is_greater_than(LHS, RHS, #LHS, #RHS, "None", \
            __FILE__, __func__, __LINE__);

#   define ASSERT_LT(LHS, RHS) \
        cardinal::impl::assert_is_lower_than(LHS, RHS, #LHS, #RHS, "None", \
            __FILE__, __func__, __LINE__);

#   define ASSERT_TRUE_MSG(EXPR, MSG) \
        cardinal::impl::assert_true(EXPR, #EXPR, MSG, \
             __FILE__, __func__, __LINE__);

#   define ASSERT_FALSE_MSG(EXPR, MSG) \
        cardinal::impl::assert_false(EXPR, #EXPR, MSG, \
            __FILE__, __func__, __LINE__);

#   define ASSERT_EQ_MSG(LHS, RHS, MSG) \
        cardinal::impl::assert_equal(LHS, RHS, #LHS, #RHS, MSG, \
            __FILE__, __func__, __LINE__);

#   define ASSERT_NE_MSG(LHS, RHS, MSG) \
        cardinal::impl::assert_non_equal(LHS, RHS, #LHS, #RHS, MSG, \
            __FILE__, __func__, __LINE__);

#   define ASSERT_NULL_MSG(PTR, MSG) \
        cardinal::impl::assert_is_null(PTR, #PTR, MSG, \
            __FILE__, __func__, __LINE__);

#   define ASSERT_NOT_NULL_MSG(PTR, MSG) \
        cardinal::impl::assert_is_not_null(PTR, #PTR, MSG, \
            __FILE__, __func__, __LINE__);

#   define ASSERT_GT_MSG(LHS, RHS, MSG) \
        cardinal::impl::assert_is_greater_than(LHS, RHS, #LHS, #RHS, MSG, \
            __FILE__, __func__, __LINE__);

#   define ASSERT_LT_MSG(LHS, RHS, MSG) \
        cardinal::impl::assert_is_lower_than(LHS, RHS, #LHS, #RHS, MSG, \
            __FILE__, __func__, __LINE__);

#else

#   define ASSERT_TRUE
#   define ASSERT_FALSE
#   define ASSERT_EQ
#   define ASSERT_NE
#   define ASSERT_NULL
#   define ASSERT_NOT_NULL
#   define ASSERT_GT
#   define ASSERT_LT

#   define ASSERT_TRUE_MSG
#   define ASSERT_FALSE_MSG
#   define ASSERT_EQ_MSG
#   define ASSERT_NE_MSG
#   define ASSERT_NULL_MSG
#   define ASSERT_NOT_NULL_MSG
#   define ASSERT_GT_MSG
#   define ASSERT_LT_MSG

#endif // DEBUG

//  Includes implementation of assertions
#   include "Runtime/Core/Assertion/Impl/Assert.inl"

#endif // !CARDINAL_ENGINE_ASSERT_HH__