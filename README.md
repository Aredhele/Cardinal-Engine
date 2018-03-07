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
the project has been quickly split into two main parts : Engine and Game
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
