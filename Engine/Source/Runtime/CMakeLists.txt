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
INCLUDE_DIRECTORIES(${CARDINAL_ENGINE_DIR}/Header/)

# Compile all tests
ADD_LIBRARY(CardinalEngine STATIC
        Core/Debug/Logger.cpp
        Core/Maths/Noise/PerlinNoise.cpp
        Core/Memory/Allocator/StackAllocator.cpp
        Rendering/Context/Window.cpp
        Rendering/Debug/DebugBox.cpp
        Rendering/Debug/DebugLine.cpp
        Rendering/Debug/DebugRay.cpp
        Rendering/Debug/DebugManager.cpp
        Rendering/Camera/Camera.cpp
        Rendering/Optimization/VBOIndexer.cpp
        Rendering/RenderingEngine.cpp
        Rendering/Renderer/IRenderer.cpp
        Rendering/Renderer/TextRenderer.cpp
        Rendering/Renderer/MeshRenderer.cpp
        Rendering/Texture/TextureLoader.cpp
        Rendering/Texture/TextureManager.cpp
        Rendering/Texture/TextureImporter.cpp
        Rendering/Shader/IShader.cpp
        Rendering/Shader/ShaderManager.cpp
        Rendering/Shader/ShaderCompiler.cpp
        Rendering/Shader/Built-in/TextShader.cpp
        Rendering/Shader/Built-in/UnlitColorShader.cpp
        Rendering/Shader/Built-in/UnlitTextureShader.cpp
        Rendering/Shader/Built-in/UnlitTransparentShader.cpp)

# But tests depends on GTEST and GMOCK
ADD_DEPENDENCIES(CardinalEngine glfw glew ResourcesCopy)

# Linking ...
TARGET_LINK_LIBRARIES(CardinalEngine ${COMPILER_DEPENDENCIES} glfw glew ${PLATFORM_DEPENDENCIES})

ADD_CUSTOM_TARGET(ResourcesCopy)

# Copy all resources on engine build
ADD_CUSTOM_COMMAND(TARGET ResourcesCopy PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CARDINAL_ENGINE_DIR}/Resources ${CARDINAL_BIN_OUTPUT}/Resources
        COMMENT "[INFO] Copying shared files ...")