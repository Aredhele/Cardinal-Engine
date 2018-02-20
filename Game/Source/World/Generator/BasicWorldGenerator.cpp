#include "World/Generator/BasicWorldGenerator.hpp"
#include "World/Generator/Noise/PerlinNoise.hpp"

World * BasicWorldGenerator::generateWorld()
{
    mp_currentWorld = new World();
    srand(6665);
    //Reset du monde
    mp_currentWorld->Initialize();
    generateHeights();

   /* //On charge les 4 coins
    load_pile(0,0,WorldSettings::s_matHeightCubes/2);
    load_pile(WorldSettings::s_matSizeCubes-1,0,WorldSettings::s_matHeightCubes/2);
    load_pile(WorldSettings::s_matSizeCubes-1,WorldSettings::s_matSizeCubes-1,WorldSettings::s_matHeightCubes/2);
    load_pile(0,WorldSettings::s_matSizeCubes-1,WorldSettings::s_matHeightCubes/2);

    //On génère a partir des 4 coins
    generate_piles(0,0,
                   WorldSettings::s_matSizeCubes-1,0,
                   WorldSettings::s_matSizeCubes-1,WorldSettings::s_matSizeCubes-1,
                   0,WorldSettings::s_matSizeCubes-1);
    smooth();*/
    mp_currentWorld->Batch();
    return mp_currentWorld;
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
void BasicWorldGenerator::load_pile(int x, int y, int height, bool onlyIfZero)
{
    if (mp_currentWorld->m_worldHeights[x][y] != 0) return;

	if (height < 1)
		height = 1;
	if (height >= WorldSettings::s_matHeightCubes)
		height = WorldSettings::s_matHeightCubes - 1;

    mp_currentWorld->m_worldHeights[x][y] = height;

	for (int z = 0; z<height; z++)
	{
		ByteCube* cube = mp_currentWorld->GetCube(x, y, z);
        cube->Enable();
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
	// The bloc is like that
	// 1   12   2
	// 41   c   23
	// 4   34   3
	// Stop if there isn't a cube between corners
	if ((x1 == x2 - 1 || x1 == x2) && (y1 == y4 - 1 || y1 == y4)) return;

	// Build the middle pile between each corner of the bloc
	int x1x2 = (x1 + x2) / 2;
	int y1y2 = (y1 + y2) / 2;
	int height12 = (mp_currentWorld->m_worldHeights[x1][y1] + mp_currentWorld->m_worldHeights[x2][y2]) / 2 + rand() % 3;
	load_pile(x1x2, y1y2, height12);
	int x2x3 = (x2 + x3) / 2;
	int y2y3 = (y2 + y3) / 2;
	int height23 = (mp_currentWorld->m_worldHeights[x2][y2] + mp_currentWorld->m_worldHeights[x3][y3]) / 2 + rand() % 3;
	load_pile(x2x3, y2y3, height23);
	int x3x4 = (x3 + x4) / 2;
	int y3y4 = (y3 + y4) / 2;
	int height34 = (mp_currentWorld->m_worldHeights[x3][y3] + mp_currentWorld->m_worldHeights[x4][y4]) / 2 + rand() % 3;
	load_pile(x3x4, y3y4, height34);
	int x4x1 = (x4 + x1) / 2;
	int y4y1 = (y4 + y1) / 2;
	int height41 = (mp_currentWorld->m_worldHeights[x4][y4] + mp_currentWorld->m_worldHeights[x1][y1]) / 2 + rand() % 3;
	load_pile(x4x1, y4y1, height41);

	// Build the pile on the center of the bloc
	int xcenter = (x4x1 + x2x3) / 2;
	int ycenter = (y4y1 + y2y3) / 2;
	int heightCenter = glm::max(0, (height41 + height23) / 2 + rand() % 3);
	load_pile(xcenter, ycenter, heightCenter);

	// Call recursively on the four new blocs created
	generate_piles(x1, y1, x1x2, y1y2, xcenter, ycenter, x4x1, y4y1, prof, profMax);
	generate_piles(x1x2, y1y2, x2, y2, x2x3, y2y3, xcenter, ycenter, prof, profMax);
	generate_piles(xcenter, ycenter, x2x3, y2y3, x3, y3, x3x4, y3y4, prof, profMax);
	generate_piles(x4x1, y4y1, xcenter, ycenter, x3x4, y3y4, x4, y4, prof, profMax);
}

void BasicWorldGenerator::smooth(void)
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
                    worldHeightsTemp[x][y] += worldHeightsTemp[i][j];
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
            load_pile(x, y, worldHeightsTemp[x][y], false);
        }
    }
}
