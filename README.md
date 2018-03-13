# Cardinal Engine
Cardinal Engine is an experimental game engine programmed **in one month** for a project at 
the <a href="http://www.enjmin.fr/">**Enjmin**</a>, the national school of video games. 
The main goal of the project was to learn about rendering and procedural generation 
in video games. Cardinal Engine is fully written in **C++ with OpenGL 3** and use some third party 
libraries :
* Glew
* **Glfw** 
* Glm
* OpenAL
* **OpenVR**
* Bullet3
* ImGui
* Google Test

The project is under CMake 3.2 and is compatible (tested) with Microsoft
Visual Studio 2017 (CMake support), CLion (tested) and more. The engine is currently 
compiling on Windows and has a theoretical compatibility with Linux and Mac if the right
flags are passed to CMake because the project contains only sources.

#### Summary

 <ul>
  <li><a href="#Features">Features</a></li>
  <li><a href="#Usage">Usage</a></li>
  <ul>
        <li><a href="#Plugins">Plugins</a></li>
        <li><a href="#Log">Log</a></li>
        <li><a href="#Rendering">Rendering</a></li>
        <li><a href="#Lighting">Lighting</a></li>
        <li><a href="#Virtual Reality">Virtual Reality</a></li>
        <li><a href="#Gizmos">Gizmos</a></li>
  </ul>
  <li><a href="#Gallery">Gallery</a></li>
</ul> 


<div id="Features"></div>

### Features

#### General
* **Plugins**
* Independent game loop
* Message logger
* Assertion utilities
* ImGui support
* **Hierarchy and Inspector**
    * Inspection of instantiated objects
    * Modification of attributes in real time

#### Rendering
* **Virtual Reality**
    * OpenVR
    * **Working with HTC Vive**
    * Custom mirror window


* **Post-processing**
    * **Post-processing stack**
    * Blur (Box blur, Gaussian blur)
    * Kernel (Edge detection, Sharpen)
    * Debug (Depth buffer, Light scattering pass)
    * Utility (Mirror, Negative, Identity)
    * Sepia tone
    * Vignette
    * **Bloom**
    * **God rays**
    * **FXAA**
    
  
* Renderer
    * MeshRenderer
    * LineRenderer
    * TextRenderer
    * **ParticleRenderer**
 
 
* Built-in shaders
    * Unlit / Lit (Color, Texture, Transparent, Line)
    * Particle
    * Text
    * **Standard** (Diffuse + point lights)
    
   
* **Particle system**
    * Customisable particle system
    * **GPU Instantiation based**
    
    
* VBO indexing


* **Lighting**
    * Directional light
    * Point light


* Debug
    * **Gizmos** (Box, Cone, lights etc.)
    * Lines
    * Rays    

#### Audio
* OpenAL
* Wav file loading
* **Audio listener**
* **Audio source**

<div id="Usage"></div>

## Usage

This section will enumerate all engine-side implemented features. 

<div id="Plugins"></div>

#### Plugins
Because the engine was designed to create procedural voxel worlds, the code of 
the project has been quickly split into two main parts : Engine and Game.
To achieve that, the game part is compiled separately into a plugin that can
be registered later and called by the engine.

The first thing to do is to create a class that will extend
the engine plugin interface and implements virtual pure methods.

Code
```cpp
#include "Runtime/Core/Plugin/Plugin.hpp"

class MyPlugin : public cardinal::Plugin
{
public:

    static MyPlugin * s_pPlugin;

public:

    /// \brief Called when the game begins
    void OnPlayStart() final;

    /// \brief Called when the game stops
    void OnPlayStop () final;

    /// \brief Called just before the engine update
    void OnPreUpdate() final;

    /// \brief Called after the engine update
    /// \param dt The elapsed time in seconds
    void OnPostUpdate(float dt) final;

    /// \brief Called when it's time to render the GUI
    void OnGUI() final;
};
```

Then to register your plugin into the engine, you have to implement a function 
called "OnPluginRegistration()". This function will be called after the engine 
initialization so it is already safe.

Code
```cpp
/// \brief Hook to register user plugin from the static libraries
void OnPluginRegistration()
{
    // Creating our plugin instance
    MyPlugin::s_pPlugin = new MyPlugin();

    // Engine plugin registration
    cardinal::PluginManager::RegisterPlugin(MyPlugin::s_pPlugin);
    
    // After this call, plugin virtual methods will be call automatically
}
```

<div id="Log"></div>

#### Log

At any time in your code you can log debug messages using the engine built-in log 
system. There are 4 log levels : User, Info, Warning and Error.

Code
```cpp
#include "Runtime/Core/Debug/Logger.hpp"

...

cardinal::Logger::LogUser   ("Foo %d", foo); // Write in stdout with [User] tag
cardinal::Logger::LogInfo   ("Foo %d", foo); // Write in stdout with [Info] tag
cardinal::Logger::LogWarning("Foo %d", foo); // Write in stdout with [Warn] tag
cardinal::Logger::LogError  ("Foo %d", foo); // Write in stderr with [Erro] tag
```

Output example

<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/10/3/1520382473-readme-1.png" width="409" height="89" />
</p>


<div id="Rendering"></div>

#### Rendering

The engine has 4 types of renderers that extends the renderer interface IRenderer :
**MeshRenderer, LineRenderer, TextRenderer and ParticleRenderer**. Each renderer can be
allocated by calling the appropriate function in the Rendering Engine. Calling one of
those functions will return a pointer on a initialized renderer ready to be used. 
The renderer will be **autonomous** and there is nothing more to do, you can send
your vertices, normals and uvs to the renderer and your mesh will be drawn.

Code

```cpp
#include "Runtime/Rendering/Renderer/MeshRenderer.hpp"

/// \brief Called when the game begins
void MyPlugin::OnPlayStart()
{
    ...
    
    // Full setup example
    // Loads a bmp texture from a file and registers it as the given ID
    TextureLoader::LoadTexture("MyTextureID", "Resources/Textures/MyTexture.bmp");
    
    // Getting back our texture from its ID
    uint myTextureID = cardinal::TextureManager::GetTextureID("MyTextureID");
    
    // Creating our shader
    cardinal::StandardShader * pShader = new cardinal::StandardShader();
    
    // Setting the texture of the shader
    pShader->SetTexture(myTextureID);
    
    // Allocating the renderer in one call
    MeshRenderer * pMeshRenderer = cardinal::RenderingEngine::AllocateMeshRenderer();
    
    // Initializing by passing all the geometry 
    pMeshRenderer->Initialize(...);
    
    // Finally
    pMeshRenderer->SetShader(pShader);
    
    // To release a renderer after usage
    cardinal::RenderingEngine::ReleaseRenderer(pMeshRenderer);
    
    ...
}
```

<div id="Lighting"></div>

#### Lighting

It is possible to illuminate the scene with two kinds of lights : Directional, Point.
Just like renderers, there is only one function to call.

Code

```cpp
#include "Runtime/Rendering/Lighting/Lighting.hh"

/// \brief Called when the game begins
void MyPlugin::OnPlayStart()
{
    // Creating the directional light
    cardinal::LightManager::CreateDirectionalLight();
    
    // Getting an access on it 
    cardinal::DirectionalLight * pDirectional = cardinal::LightManager::GetDirectionalLight();
    
    // The position is debug purpose only
    pDirectional->SetPosition(glm::vec3(128.0f, 128.0f, 300.0f));
    pDirectional->SetDirection(glm::vec3(-0.5f, -0.5f, -0.5f)); 
    
    // For point lights
    cardinal::PointLight * pPoint = cardina::LightManager::AllocatePointLight();
    
    pPoint->SetRange(20);
    pPoint->SetIntensity(1.0f);
    pPoint->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
    pPoint->SetPosition(glm::vec3(100.0f, 20.0f, 300.0f));
}   
```

Output (Gizmos enabled)

<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/11/2/1520943832-cardinal-engine-83.jpg" width="768" height="432" />
</p>

<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/11/2/1520943830-cardinal-engine-84.jpg" width="768" height="432" />
</p>

<div id="Virtual Reality"></div>

#### Virtual Reality

The engine supports **stereoscopic rendering with OpenVR**. It allows you to see the world in
VR through an **HMD** (Tested with an **HTC Vive**). To enable stereoscopic rendering just write 
the following lines at the beginning of your code.

Code
```cpp
/// \brief Called when the game begins
void MyPlugin::OnPlayStart()
{
    cardinal::RenderingEngine::InitializeStereoscopicRendering();
    vr::IVRSystem * pHMD = cardinal::RenderingEngine::GetHMD();
    
    // Always check pointers
    ASSERT_NOT_NULL(pHMD);
}
```

The first call will initialize VR rendering and start SteamVR. It might fail if SteamVR is not
installed or if there is no HMD connected. The engine embeds his own system to mirror the frames
that are sent to the HMD before the pass of the SteamVR compositor.

Output
<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/11/1/1520822401-cardinal-engine-67.png" width="768" height="432" />
</p>

Note : In VR, the post-processing is disabled but there is at least the MSAA (x4). You can watch a
<a href="https://www.youtube.com/watch?v=nuETZs1WaYo">short video</a>  showing this feature.

<div id="Particle system"></div>

#### Particle system

Cardinal Engine has it own basic particle system **GPU instantiation based**. So it allows you to deal
with a lot of particles at the same time. The only emission shape available is the cone. 
Particle systems can be created through code and modified with the GUI.

Code

```cpp
#include "Runtime/Rendering/Particle/ParticleSystem.hpp"

// Allocating a particle system
cardinal::ParticleSystem * pSystem = cardinal::RenderingEngine::AllocateParticleSystem();

// Initializing the particle system with the following parameters
// Max particle, Emission rate, Life time, Size, Speed, Gravity, Color, Shape
pSystem->Initialize(200000, 5000, 3.0f, 0.5f, 30.0f, glm::vec3(0.0f, 0.0f, -13.0f), glm::vec3(1.0f), new cardinal::Cone(4.0f, 2.0f));

// Setting the position of the particle system
pSystem->SetPosition(glm::vec3(0.0f, 0.0f, 300.0f));
```

Output 

<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/11/1/1520875924-cardinal-engine-80.jpg" width="768" height="432" />
</p>

<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/11/1/1520876102-cardinal-engine-81.jpg" width="768" height="432" />
</p>

Note : Here is a <a href="https://youtu.be/DPy669-xMyU">short video</a> 
demonstrating the modification of the particle system through the inspector.

<div id="Gizmos"></div>

#### Gizmos

At any time, you can request the engine to draw debug information. The engine only supports
gizmos for built-in components :
* Box
* Ray
* Line
* Axis
* Grid
* Cone
* Point Light
* Directional Light

To enable or disable a gizmo, just call on small function :

```cpp
#include "Runtime/Rendering/Debug/Debug.hpp"
#include "Runtime/Rendering/Debug/DebugManager.hpp"

/// \brief Called when the game begins
void MyPlugin::OnPlayStart()
{
    // Tells to the engine to draw debug boxes and lines
    cardinal::DebugManager::EnableGizmo(cardinal::DebugManager::EGizmo::Box);
    cardinal::DebugManager::EnableGizmo(cardinal::DebugManager::EGizmo::Line);
}

/// \brief Called after the engine update
/// \param dt The elapsed time in seconds
void MyPlugin::OnPostUpdate(float dt)
{
    // Asks the engine to draw a white box in 0, 0, 0 with a size of 8
    cardinal::debug::DrawBox(glm::vec3(0.0f), 8.0f, 8.0f, glm::vec(1.0f));
    
    // Asks the engine to draw a white line starting at 0, 0, 0 
    // and ending at 8, 8, 8
    cardinal::debug::DrawLine(glm::vec3(0.0f), glm::vec3(8.0f), glm::vec3(1.0f));
}
```

Note : You can also enable or disable gizmos directly from the game with the
gizmos window.

<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/11/1/1520868995-cardinal-engine-79.jpg" width="180" height="260" />
</p>

<div id="Gallery"></div>

## Gallery

<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/11/2/1520944633-cardinal-engine-64.png" width="768" height="432" />
</p>

<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/11/2/1520944612-cardinal-engine-77.png" width="768" height="432" />
</p>

<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/11/2/1520944591-cardinal-engine-82.jpg" width="768" height="432" />
</p>

<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/10/3/1520383633-gallery-1.png" width="768" height="432" />
</p>

<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/10/3/1520384521-gallery-2.jpg" width="768" height="432" />
</p>

<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/10/3/1520384523-gallery-3.jpg" width="768" height="432" />
</p>

<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/10/3/1520383634-gallery-4.png" width="768" height="432" />
</p>

<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/10/3/1520383599-gallery-5.png" width="768" height="432" />
</p>

<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/10/3/1520383832-gallery-6.png" width="768" height="432" />
</p>

<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/10/3/1520383637-gallery-7.png" width="768" height="432" />
</p>

<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/10/3/1520383915-gallery-8.png" width="768" height="432" />
</p>

<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/10/3/1520383915-gallery-10.png" width="768" height="432" />
</p>

<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/10/3/1520383889-gallery-11.png" width="768" height="432" />
</p>

<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/10/3/1520383907-gallery-12.png" width="768" height="432" />
</p>

<p align="center">
  <img src="http://image.noelshack.com/fichiers/2018/11/2/1520945123-cardinal-engine-76.jpg" width="768" height="432" />
</p>