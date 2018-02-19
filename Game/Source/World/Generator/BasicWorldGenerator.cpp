#include "World/Generator/BasicWorldGenerator.hpp"
#include "World/Generator/Noise/PerlinNoise.hpp"

World * BasicWorldGenerator::generateWorld()
{
    mp_currentWorld = new World();
    srand(6665);
    //Reset du monde
    mp_currentWorld->Initialize();
    generateHeights();
}

void BasicWorldGenerator::generateHeights()
{
	PerlinNoise pn;
	for (int x = 0; x<WorldSettings::s_matSizeCubes; x++)
		for (int y = 0; y < WorldSettings::s_matSizeCubes; y++)
		{
			double noise = pn.noise(((double)x) / WorldSettings::s_matSizeCubes, ((double)y) / WorldSettings::s_matSizeCubes, 10);
			load_pile(x, y, WorldSettings::s_matHeightCubes * noise);
		}
}

/// Generate a cube pile
void BasicWorldGenerator::load_pile(int x, int y, int height)
{
	if (height < 1)
		height = 1;
	if (height >= WorldSettings::s_matHeightCubes)
		height = WorldSettings::s_matHeightCubes - 1;

	for (int z = 0; z<height; z++)
	{
		ByteCube* cube = mp_currentWorld->GetCube(x, y, z);
		if (z>0)
			cube->SetType(ByteCube::EType::Dirt);
		else
            cube->SetType(ByteCube::EType::Water);
	}

	if (height - 1>0)
	{
        ByteCube* cube = mp_currentWorld->GetCube(x, y, height - 1);
		cube->Enable();
        cube->SetType(ByteCube::EType::Grass);
	}

	for (int z = height; z<WorldSettings::s_matHeightCubes; z++)
	{
        ByteCube* cube = mp_currentWorld->GetCube(x, y, z);cube->Enable();
        cube->SetType(ByteCube::EType::Air);
	}
}
