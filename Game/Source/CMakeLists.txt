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
        ${CARDINAL_ENGINE_DIR}/Header/
        ${CARDINAL_GAME_DIR}/Header)

# Compile game with the engine
ADD_EXECUTABLE(Game
        Main.cpp
        World/Chunk/Chunk.cpp
        World/Cube/UVManager.cpp)

# But tests depends on GTEST and GMOCK
ADD_DEPENDENCIES(Game CardinalEngine)

# Linking ...
TARGET_LINK_LIBRARIES(Game ${COMPILER_DEPENDENCIES} CardinalEngine)