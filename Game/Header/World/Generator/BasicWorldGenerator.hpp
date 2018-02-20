#pragma once

#include "World/Generator/IWorldGenerator.hpp"

class BasicWorldGenerator : public IWorldGenerator
{
public:
    World* generateWorld() override;
private:
    World* mp_currentWorld;

    void generateHeights();
    void load_pile(int x, int y, int height, bool onlyIfZero = true);
    //Creation du monde entier, en utilisant le mouvement brownien fractionnaire
    void generate_piles(int x1, int y1,
                        int x2, int y2,
                        int x3, int y3,
                        int x4, int y4, int prof = 0, int profMax = -1);
    void smooth();
};
