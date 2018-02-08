# Copyright (C) 2018-2019 Cardinal Engine
# Vincent STEHLY--CALISTO, vincentstehly@hotmail.fr

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

# Path
SET(CARDINAL_ROOT_DIR        ${CMAKE_SOURCE_DIR})
SET(CARDINAL_BIN_DIR         ${CARDINAL_ROOT_DIR}/Bin)
SET(CARDINAL_BIN_DIR_DBG     ${CARDINAL_BIN_DIR}/Debug)
SET(CARDINAL_BIN_DIR_REL     ${CARDINAL_BIN_DIR}/Release)
SET(CARDINAL_LIB_DIR         ${CARDINAL_ROOT_DIR}/Lib)
SET(CARDINAL_LIB_DIR_DBG     ${CARDINAL_LIB_DIR}/Debug)
SET(CARDINAL_LIB_DIR_REL     ${CARDINAL_LIB_DIR}/Release)
SET(CARDINAL_ENGINE_DIR      ${CARDINAL_ROOT_DIR}/Engine)
SET(CARDINAL_THIRD_PARTY_DIR ${CARDINAL_ENGINE_DIR}/ThirdParty)
SET(CARDINAL_UNIT_TEST_DIR   ${CARDINAL_THIRD_PARTY_DIR}/UnitTest)
SET(CARDINAL_SDL_DIR         ${CARDINAL_THIRD_PARTY_DIR}/SDL2)

# Include
SET(CARDINAL_GTEST_INC_DIR   ${CARDINAL_UNIT_TEST_DIR}/GoogleTest/include)
SET(CARDINAL_GMOCK_INC_DIR   ${CARDINAL_UNIT_TEST_DIR}/GoogleMock/include)

# Name
SET(CARDINAL_RUNTIME CARDINALRuntime)
SET(CARDINAL_EDITOR  CARDINALEditor)