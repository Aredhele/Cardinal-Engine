#pragma once

#include "World/World.hpp"

class IWorldGenerator 
{
public:
    virtual World* generateWorld() = 0;

};
