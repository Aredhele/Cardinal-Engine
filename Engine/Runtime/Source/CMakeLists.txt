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
INCLUDE_DIRECTORIES(${CARDINAL_ENGINE_DIR}/Runtime/Header)

# Compile all tests
ADD_LIBRARY(CardinalEngine STATIC
        Core/Debug/Logger.cpp
        Core/Maths/Noise/PerlinNoise.cpp
        Rendering/Context/Window.cpp
        Rendering/Debug/DebugCube.cpp
        Rendering/Shader/ShaderCompiler.cpp
        Rendering/Camera/Camera.cpp
        Rendering/Debug/DebugLine.cpp
        Rendering/Optimization/VBOIndexer.cpp
        Rendering/RenderingEngine.cpp
        Rendering/Renderer/MeshRenderer.cpp
        Rendering/Texture/TextureLoader.cpp)

# But tests depends on GTEST and GMOCK
ADD_DEPENDENCIES(CardinalEngine glfw glew)

# Linking ...
TARGET_LINK_LIBRARIES(CardinalEngine ${COMPILER_DEPENDENCIES} glfw glew ${PLATFORM_DEPENDENCIES})