# Cardinal Engine
Cardinal Engine is an experimental game engine programmed for a project at 
the <a href="http://www.enjmin.fr/">Enjmin</a>, the national school of video games. 
The main goal of the project was to learn about rendering and procedural generation 
in video games. Cardinal Engine is fully written in C++ with OpenGL 3 and use some third party 
libraries :
* Glew
* Glfw 
* Glm
* OpenAL
* OpenVR
* Bullet3
* ImGui
* Google Test

The project is under CMake 3.2 and is compatible (tested) with Microsoft
Visual Studio 2017 (CMake support), CLion (tested) and more. The engine is currently 
compiling on Windows and has a theoretical compatibility with Linux and Mac if the right
flags are passed to CMake because the project contains only sources.

## Usage

This section will enumerate all engine-side implemented features. 

#### Plugins
Because the engine was designed to create procedural voxel worlds, the code of 
the project has been quickly split into two main parts : Engine and Game.
To achieve that, the game part is compiled separately into a plugin that can
be registered and called from the engine.

The first thing to do to create a plugin is to create a class that will extend
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

#### Virtual Reality

The engine supports stereoscopic rendering with OpenVR. It allows you to see the world in
VR through an HMD (Tested with an HTC Vive). To enable stereoscopic rendering just type 
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

Note : In VR, the post-processing is disabled but there is at least the MSAA (x4).

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

## Gallery

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