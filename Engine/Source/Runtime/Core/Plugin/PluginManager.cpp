/// Copyright (C) 2018-2019, Cardinal Engine
/// Vincent STEHLY--CALISTO, vincentstehly@hotmail.fr
///
/// This program is free software; you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation; either version 2 of the License, or
/// (at your option) any later version.
///
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program; if not, write to the Free Software Foundation, Inc.,
/// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

/// \file       PluginManager.cpp
/// \date       25/02/2018
/// \project    Cardinal Engine
/// \package    Runtime/Core/Plugin
/// \author     Vincent STEHLY--CALISTO

#include "Runtime/Core/Debug/Logger.hpp"
#include "Runtime/Core/Assertion/Assert.hh"
#include "Runtime/Core/Plugin/PluginManager.hpp"

/// \namespace cardinal
namespace cardinal
{

/* static */ PluginManager * PluginManager::s_pInstance = nullptr;

/// \brief Initializes the plugin manager
void PluginManager::Initialize()
{
    if(PluginManager::s_pInstance == nullptr)
    {
        PluginManager::s_pInstance = this;
        Logger::LogInfo("Initializing the plugin manager");
    }
    else
    {
        Logger::LogWaring("The plugin manager is already initialized");
    }
}

/// \brief Releases the plugin manager
void PluginManager::Release()
{
    if(PluginManager::s_pInstance != nullptr)
    {
        PluginManager::s_pInstance = nullptr;
        Logger::LogInfo("Plugin manager successfully destroyed");
    }
    else
    {
        Logger::LogWaring("The plugin manager is already destroyed");
    }
}

/// \brief Called when the game begins
void PluginManager::OnPlayStart()
{
    size_t pluginCount = m_plugins.size();
    for(size_t nPlugin = 0; nPlugin < pluginCount; ++nPlugin)
    {
        ASSERT_NOT_NULL(m_plugins[nPlugin]);
        m_plugins[nPlugin]->OnPlayStart();
    }
}

/// \brief Called when the game stops
void PluginManager::OnPlayStop()
{
    size_t pluginCount = m_plugins.size();
    for(size_t nPlugin = 0; nPlugin < pluginCount; ++nPlugin)
    {
        ASSERT_NOT_NULL(m_plugins[nPlugin]);
        m_plugins[nPlugin]->OnPlayStop();
    }
}

/// \brief Called before the engine update
void PluginManager::OnPreUpdate()
{
    size_t pluginCount = m_plugins.size();
    for(size_t nPlugin = 0; nPlugin < pluginCount; ++nPlugin)
    {
        ASSERT_NOT_NULL(m_plugins[nPlugin]);
        m_plugins[nPlugin]->OnPreUpdate();
    }
}

/// \brief Called after the engine update
/// \param dt The elapsed time in seconds
void PluginManager::OnPostUpdate(float dt)
{
    size_t pluginCount = m_plugins.size();
    for(size_t nPlugin = 0; nPlugin < pluginCount; ++nPlugin)
    {
        ASSERT_NOT_NULL(m_plugins[nPlugin]);
        m_plugins[nPlugin]->OnPostUpdate(dt);
    }
}

/// \brief Registers a plugin in the engine
/// \param pPlugin The plugin to register
/* static */ void PluginManager::RegisterPlugin(Plugin * pPlugin)
{
    ASSERT_NOT_NULL(s_pInstance);
    size_t pluginCount = s_pInstance->m_plugins.size();
    for(size_t nPlugin = 0; nPlugin < pluginCount; ++nPlugin)
    {
        if(s_pInstance->m_plugins[nPlugin] ==pPlugin)
        {
            Logger::LogWaring("You attempt to register your plugin twice. "
                              "Ignoring registering.");

            return;
        }
    }

    s_pInstance->m_plugins.push_back(pPlugin);
    Logger::LogInfo("Plugin 0x%x registered !", pPlugin);
}

/// \brief Unregisters a plugin from the engine
/// \param pPlugin The plugin to unregister
/* static */ void PluginManager::UnregisterPlugin(cardinal::Plugin * pPlugin)
{
    ASSERT_NOT_NULL(s_pInstance);

    int index = -1;
    size_t count = PluginManager::s_pInstance->m_plugins.size();
    for (size_t nPlugin = 0; nPlugin < count; ++nPlugin)
    {
        if (s_pInstance->m_plugins[nPlugin] == pPlugin)
        {
            index = static_cast<int>(nPlugin);
            break;
        }
    }

    if (index != -1)
    {
        s_pInstance->m_plugins.erase(s_pInstance->m_plugins.begin() + index);
        Logger::LogInfo("Plugin 0x%x unregistered !", pPlugin);
    }
}

} // !namespace


