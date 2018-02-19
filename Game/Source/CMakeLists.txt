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

# Adds all runtime header
INCLUDE_DIRECTORIES(
        ${CARDINAL_GAME_DIR}/Header/
        ${CARDINAL_ENGINE_DIR}/Header/
        ${CARDINAL_THIRD_PARTY_DIR}/ImGUI/Header/
        ${CARDINAL_THIRD_PARTY_DIR}/Bullet3/src/)

# Gets all source files
FILE(GLOB_RECURSE GAME_SOURCES
        World/*.cpp
        Character/*.cpp)

FILE(GLOB_RECURSE GAME_HEADERS
        ${CARDINAL_GAME_DIR}/Header/World/*.hpp
        ${CARDINAL_GAME_DIR}/Header/Character/*.hpp)

# Compile game with the engine
ADD_EXECUTABLE(Game Main.cpp ${GAME_SOURCES} ${GAME_HEADERS})

# But tests depends on GTEST and GMOCK
ADD_DEPENDENCIES(Game CardinalEngine BulletDynamics BulletCollision LinearMath)

# Linking ...
TARGET_LINK_LIBRARIES(Game ${COMPILER_DEPENDENCIES} CardinalEngine ImGUI BulletDynamics BulletCollision LinearMath)

# Create an executable for PCG tests
ADD_EXECUTABLE(PCG_test PCG_main.cpp ${GAME_SOURCES} ${GAME_HEADERS})

# But tests depends on GTEST and GMOCK
ADD_DEPENDENCIES(PCG_test CardinalEngine BulletDynamics BulletCollision LinearMath)

# Linking ...
TARGET_LINK_LIBRARIES(PCG_test ${COMPILER_DEPENDENCIES} CardinalEngine ImGUI BulletDynamics BulletCollision LinearMath)

# Create an executable to test the physics simulation
ADD_EXECUTABLE(Physics Physics.cpp)

# But tests depends on GTEST and GMOCK
ADD_DEPENDENCIES(Physics CardinalEngine BulletDynamics BulletCollision LinearMath)

# Linking ...
TARGET_LINK_LIBRARIES(Physics ${COMPILER_DEPENDENCIES} CardinalEngine ImGUI BulletDynamics BulletCollision LinearMath)