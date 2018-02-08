# Copyright (C) 2017-2018 Disparity Engine

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# he Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

# Adds all runtime header
INCLUDE_DIRECTORIES(${CARDINAL_ENGINE_DIR}/Runtime/Header)

# Compile all tests
ADD_EXECUTABLE(CARDINAL_TEST_UNIT_TEST
        UnitTestTest.cpp)

# But tests depends on GTEST and GMOCK
ADD_DEPENDENCIES(CARDINAL_TEST_UNIT_TEST gtest)

# Linking ...
TARGET_LINK_LIBRARIES(CARDINAL_TEST_UNIT_TEST gtest gtest_main)