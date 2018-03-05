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
        ${CARDINAL_THIRD_PARTY_DIR}/ImGUI/Header/
        ${CARDINAL_THIRD_PARTY_DIR}/Bullet3/src/
        ${CARDINAL_THIRD_PARTY_DIR}/OpenAL/include/)

# Compile all tests
ADD_LIBRARY(CardinalEngine STATIC
        Main.cpp
        Engine.cpp
        Core/Debug/Logger.cpp
        Core/Memory/Allocator/StackAllocator.cpp
        Core/Plugin/PluginManager.cpp
        Sound/SoundEngine.cpp
        Sound/Buffer/SoundBuffer.cpp
        Sound/Buffer/SoundBufferManager.cpp
        Sound/Listener/AudioListener.cpp
        Sound/Loader/AudioLoader.cpp
        Sound/Source/AudioSource.cpp
        Physics/PhysicsEngine.cpp
        Rendering/Mesh/Cube.cpp
        Rendering/Context/Window.cpp
        Rendering/Debug/DebugBox.cpp
        Rendering/Debug/DebugGrid.cpp
        Rendering/Debug/DebugLine.cpp
        Rendering/Debug/DebugRay.cpp
        Rendering/Debug/DebugGizmos.cpp
        Rendering/Debug/DebugManager.cpp
        Rendering/Camera/Camera.cpp
        Rendering/Optimization/VBOIndexer.cpp
        Rendering/RenderingEngine.cpp
        Rendering/Renderer/IRenderer.cpp
        Rendering/Renderer/TextRenderer.cpp
        Rendering/Renderer/MeshRenderer.cpp
        Rendering/Lighting/LightManager.cpp
        Rendering/Lighting/Lights/PointLight.cpp
        Rendering/Lighting/Lights/DirectionalLight.cpp
        Rendering/Texture/TextureLoader.cpp
        Rendering/Texture/TextureManager.cpp
        Rendering/Texture/TextureImporter.cpp
        Rendering/Shader/IShader.cpp
        Rendering/Shader/ShaderManager.cpp
        Rendering/Shader/ShaderCompiler.cpp
        Rendering/Shader/Built-in/Lit/LitColorShader.cpp
        Rendering/Shader/Built-in/Lit/LitTextureShader.cpp
        Rendering/Shader/Built-in/Lit/LitTransparentShader.cpp
        Rendering/Shader/Built-in/Text/TextShader.cpp
        Rendering/Shader/Built-in/Unlit/UnlitColorShader.cpp
        Rendering/Shader/Built-in/Unlit/UnlitTextureShader.cpp
        Rendering/Shader/Built-in/Unlit/UnlitTransparentShader.cpp
        Rendering/Shader/Built-in/Standard/StandardShader.cpp
        Rendering/PostProcessing/PostProcessingStack.cpp
        Rendering/PostProcessing/PostEffects/PostEffect.cpp
        Rendering/PostProcessing/PostEffects/Identity.cpp
        Rendering/PostProcessing/PostEffects/Mirror.cpp
        Rendering/PostProcessing/PostEffects/Negative.cpp
        Rendering/PostProcessing/PostEffects/Sepia.cpp
        Rendering/PostProcessing/PostEffects/BoxBlur.cpp
        Rendering/PostProcessing/PostEffects/GaussianBlur.cpp
        Rendering/PostProcessing/PostEffects/Sharpen.cpp
        Rendering/PostProcessing/PostEffects/EdgeDetection.cpp
        Rendering/PostProcessing/PostEffects/DepthBuffer.cpp
        Rendering/PostProcessing/PostEffects/GodRay.cpp
        Rendering/PostProcessing/PostEffects/LightScattering.cpp
        Rendering/PostProcessing/PostEffects/Bloom.cpp
        Rendering/PostProcessing/PostEffects/Vignette.cpp
        Rendering/PostProcessing/PostEffects/Experimental/Experimental1.cpp
        Rendering/PostProcessing/PostEffects/Experimental/Experimental2.cpp)

# But tests depends on GTEST and GMOCK
ADD_DEPENDENCIES(CardinalEngine glfw glew ResourcesCopy ImGUI)

# Linking ...
TARGET_LINK_LIBRARIES(CardinalEngine ${COMPILER_DEPENDENCIES} glfw glew ImGUI OpenAL ${PLATFORM_DEPENDENCIES})

ADD_CUSTOM_TARGET(ResourcesCopy)

# Copy all resources on engine build
ADD_CUSTOM_COMMAND(TARGET ResourcesCopy PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CARDINAL_ENGINE_DIR}/Resources ${CARDINAL_BIN_OUTPUT}/Resources
        COMMENT "[INFO] Copying shared files ...")
