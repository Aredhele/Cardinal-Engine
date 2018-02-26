#pragma once

#include <random>
#include <World/World.hpp>
#include "World/Generator/GenerationSettings.hpp"

class BasicWorldGenerator
{
public:
    BasicWorldGenerator();
    World* generateWorld();
    World* generateWorld(GenerationSettings settings);
    int m_seed;

private:
    World* mp_currentWorld = nullptr;
    GenerationSettings m_generationSettings;
    std::default_random_engine m_randomGenerator;


    void generate3DPerlinWorld();
    void generateFBNWorld();
    void generateHeights();
    void generateCaves();
    /// \brief Returns the sum of all air cube neighbors
    int sumNeighbors(int x, int y, int z);
    void buildStack(int x, int y, int height, bool onlyIfZero = true);
    //Creation du monde entier, en utilisant le mouvement brownien fractionnaire
    void generate_piles(int x1, int y1,
                        int x2, int y2,
                        int x3, int y3,
                        int x4, int y4, int prof = 0, int profMax = -1);
    void smooth();
};
