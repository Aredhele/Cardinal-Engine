#pragma once

#include "World/Generator/IWorldGenerator.hpp"

class BasicWorldGenerator : public IWorldGenerator
{
public:
    World* generateWorld() override;
private:
    World* mp_currentWorld;

    void generateHeights();
    void load_pile(int x, int y, int height);
};
