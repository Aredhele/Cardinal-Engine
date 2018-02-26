#include "World/Generator/BasicWorldGenerator.hpp"
#include <random>
#include <World/Generator/CellularAutomata.hpp>
#include "World/Generator/Noise/FastNoise.h"

World * BasicWorldGenerator::generateWorld(GenerationSettings settings)
{
    if (mp_currentWorld == nullptr)
        mp_currentWorld = new World();
    m_generationSettings = settings;
    m_seed = m_generationSettings.seed;
    m_randomGenerator = std::default_random_engine(m_seed);
    //Reset du monde
    mp_currentWorld->Initialize();
    generateHeights();
    //generateCaves();
    mp_currentWorld->Batch();
    return mp_currentWorld;
}

void BasicWorldGenerator::generateHeights()
{
    FastNoise noiseGenerator(m_seed);
    noiseGenerator.SetNoiseType(m_generationSettings.noiseType);
    noiseGenerator.SetFractalOctaves(m_generationSettings.octaves);
	for (int x = 0; x<WorldSettings::s_matSizeCubes; x++)
		for (int y = 0; y < WorldSettings::s_matSizeCubes; y++)
		{
			double noise = noiseGenerator.GetNoise(x, y);
			buildStack(x, y, WorldSettings::s_matHeightCubes * abs(noise));
		}
}

/// Generate a cube pile
void BasicWorldGenerator::buildStack(int x, int y, int height, bool onlyIfZero)
{
    if (mp_currentWorld->m_worldHeights[x][y] != 0 && onlyIfZero) return;

	if (height < 1)
		height = 1;
	if (height >= WorldSettings::s_matHeightCubes)
		height = WorldSettings::s_matHeightCubes - 1;

    mp_currentWorld->m_worldHeights[x][y] = height;

	for (int z = 0; z<height; z++)
	{
		ByteCube* cube = mp_currentWorld->GetCube(x, y, z);
        cube->Enable();
        cube->SetType(ByteCube::EType::Grass);
	}

	if (height - 1>0)
	{
        ByteCube* cube = mp_currentWorld->GetCube(x, y, height - 1);
		cube->Enable();
        cube->SetType(ByteCube::EType::Grass);
	}

	for (int z = height; z<WorldSettings::s_matHeightCubes; z++)
	{
        ByteCube* cube = mp_currentWorld->GetCube(x, y, z);
        cube->Enable();
        cube->SetType(ByteCube::EType::Air);
	}
}

void BasicWorldGenerator::generate_piles(int x1, int y1,
					int x2, int y2,
					int x3, int y3,
					int x4, int y4, int prof, int profMax)
{
    if (prof == profMax) return;
    prof++;
	// The bloc is like that
	// 1   12   2
	// 41   c   23
	// 4   34   3
	// Stop if there isn't a cube between corners
	if ((x1 == x2 - 1 || x1 == x2) && (y1 == y4 - 1 || y1 == y4)) return;

    int **& worldHeights = mp_currentWorld->m_worldHeights;
    double s = sqrt(WorldSettings::s_matHeightCubes);

	// Build the middle pile between each corner of the bloc
	int x1x2 = (x1 + x2) / 2;
	int y1y2 = (y1 + y2) / 2;
    std::normal_distribution<double> distribution((worldHeights[x1][y1] + worldHeights[x2][y2]) / 2, s);
	int height12 = round(distribution(m_randomGenerator));
	buildStack(x1x2, y1y2, height12);
	int x2x3 = (x2 + x3) / 2;
	int y2y3 = (y2 + y3) / 2;
    distribution = std::normal_distribution<double>((worldHeights[x2][y2] + worldHeights[x3][y3]) / 2, s);
	int height23 = round(distribution(m_randomGenerator));
	buildStack(x2x3, y2y3, height23);
	int x3x4 = (x3 + x4) / 2;
	int y3y4 = (y3 + y4) / 2;
    distribution = std::normal_distribution<double>((worldHeights[x3][y3] + worldHeights[x4][y4]) / 2 , s);
	int height34 = round(distribution(m_randomGenerator));
	buildStack(x3x4, y3y4, height34);
	int x4x1 = (x4 + x1) / 2;
	int y4y1 = (y4 + y1) / 2;
    distribution = std::normal_distribution<double>((worldHeights[x4][y4] + worldHeights[x1][y1]) / 2, s);
	int height41 = round(distribution(m_randomGenerator));
	buildStack(x4x1, y4y1, height41);

	// Build the pile on the center of the bloc
	int xcenter = (x4x1 + x2x3) / 2;
	int ycenter = (y4y1 + y2y3) / 2;
    distribution = std::normal_distribution<double>((height41 + height23) / 2, s);
	int heightCenter = round(distribution(m_randomGenerator));
	buildStack(xcenter, ycenter, heightCenter);

	// Call recursively on the four new blocs created
	generate_piles(x1, y1, x1x2, y1y2, xcenter, ycenter, x4x1, y4y1, prof, profMax);
	generate_piles(x1x2, y1y2, x2, y2, x2x3, y2y3, xcenter, ycenter, prof, profMax);
	generate_piles(xcenter, ycenter, x2x3, y2y3, x3, y3, x3x4, y3y4, prof, profMax);
	generate_piles(x4x1, y4y1, xcenter, ycenter, x3x4, y3y4, x4, y4, prof, profMax);
}

void BasicWorldGenerator::smooth()
{
    int sizeWidow = 4;
    int worldHeightsTemp[WorldSettings::s_matSizeCubes][WorldSettings::s_matSizeCubes];
    memset(worldHeightsTemp, 0x00, sizeof(int)*WorldSettings::s_matSizeCubes*WorldSettings::s_matSizeCubes);
    for (int x = 0; x<WorldSettings::s_matSizeCubes; x++)
    {
        for (int y = 0; y<WorldSettings::s_matSizeCubes; y++)
        {
            //on moyenne sur une distance
            int nb = 0;
            for (int i = (x - sizeWidow < 0 ? 0 : x - sizeWidow);
                 i < (x + sizeWidow >= WorldSettings::s_matSizeCubes ? WorldSettings::s_matSizeCubes - 1 : x + sizeWidow); i++)
            {
                for (int j = (y - sizeWidow < 0 ? 0 : y - sizeWidow);
                     j <(y + sizeWidow >= WorldSettings::s_matSizeCubes ? WorldSettings::s_matSizeCubes - 1 : y + sizeWidow); j++)
                {
                    worldHeightsTemp[x][y] += mp_currentWorld->m_worldHeights[i][j];
                    nb++;
                }
            }
            if (nb)
                worldHeightsTemp[x][y] /= nb;
        }
    }

    //On reset les piles
    for (int x = 0; x<WorldSettings::s_matSizeCubes; x++)
    {
        for (int y = 0; y<WorldSettings::s_matSizeCubes; y++)
        {
            buildStack(x, y, worldHeightsTemp[x][y], false);
        }
    }
}

void BasicWorldGenerator::generate3DPerlinWorld() {
    FastNoise noiseGenerator(m_seed);
    noiseGenerator.SetNoiseType(FastNoise::PerlinFractal);
    noiseGenerator.SetFractalOctaves(4);
    for (int x = 0; x<WorldSettings::s_matSizeCubes; x++)
        for (int y = 0; y < WorldSettings::s_matSizeCubes; y++)
        {
            for (int z = 0; z < WorldSettings::s_matHeightCubes; z++)
            {
                double noise = noiseGenerator.GetNoise(x, y, z);
                if (noise > 0)
                    mp_currentWorld->GetCube(x, y, z)->SetType(ByteCube::EType::Grass);
                mp_currentWorld->GetCube(x, y, z)->Enable();
            }
        }
}

void BasicWorldGenerator::generateFBNWorld() {
    //On charge les 4 coins
    buildStack(0,0,WorldSettings::s_matHeightCubes/2);
    buildStack(WorldSettings::s_matSizeCubes-1,0,WorldSettings::s_matHeightCubes/2);
    buildStack(WorldSettings::s_matSizeCubes-1,WorldSettings::s_matSizeCubes-1,WorldSettings::s_matHeightCubes/2);
    buildStack(0,WorldSettings::s_matSizeCubes-1,WorldSettings::s_matHeightCubes/2);

    //On génère a partir des 4 coins
    generate_piles(0,0,
                   WorldSettings::s_matSizeCubes-1,0,
                   WorldSettings::s_matSizeCubes-1,WorldSettings::s_matSizeCubes-1,
                   0,WorldSettings::s_matSizeCubes-1, 0, 10);
    smooth();
}

void BasicWorldGenerator::generateCaves() {
    int iter = 50;
    int x =50  , y = 50, z = 52;
    mp_currentWorld->GetCube(x, y, z)->SetType(ByteCube::EType::Dirt);
    FastNoise noiseGeneratorX(rand());
    noiseGeneratorX.SetNoiseType(FastNoise::PerlinFractal);
    noiseGeneratorX.SetFractalOctaves(1);
    FastNoise noiseGeneratorY(rand());
    noiseGeneratorY.SetNoiseType(FastNoise::PerlinFractal);
    noiseGeneratorY.SetFractalOctaves(1);
    FastNoise noiseGeneratorZ(rand());
    noiseGeneratorZ.SetNoiseType(FastNoise::PerlinFractal);
    noiseGeneratorZ.SetFractalOctaves(1);
    for (int i = 0; i < iter; ++i) {
        double noiseX = noiseGeneratorX.GetNoise(x, y, z);
        double noiseY = noiseGeneratorY.GetNoise(x, y, z);
        double noiseZ = noiseGeneratorZ.GetNoise(x, y, z);
        if (noiseX < -0.33)
            x += 1;
        else if (noiseX > 0.33)
            x -= 1;
        if (noiseY < -0.33)
            y += 1;
        else if (noiseY > 0.33)
            y -= 1;
        if (noiseZ < -0.66)
            z += 1;
        else if (noiseZ > 0)
            z -= 1;
        mp_currentWorld->GetCube(x, y, z)->SetType(ByteCube::EType::Dirt);
    }
}

void BasicWorldGenerator::generateCavesWithCA() {
    CellularAutomata ca;
    Cell *** cells = ca.generate3DWorld(WorldSettings::s_matHeightCubes,
                                        WorldSettings::s_matHeightCubes,
                                        WorldSettings::s_matHeightCubes);

    for (int x = 0; x<WorldSettings::s_matHeightCubes; x++)
        for (int y = 0; y < WorldSettings::s_matHeightCubes; y++)
            for (int z = 0; z < WorldSettings::s_matHeightCubes; z++)
            {
                if (cells[x][y][z].currentState) {
                    mp_currentWorld->GetCube(x, y, z)->SetType(ByteCube::EType::Air);
                }
                else {
                    mp_currentWorld->GetCube(x, y, z)->SetType(ByteCube::EType::Grass);
                }
            }
}

BasicWorldGenerator::BasicWorldGenerator()
{

}

World* BasicWorldGenerator::generateWorld()
{
    m_generationSettings = GenerationSettings();
    return generateWorld(m_generationSettings);
}


