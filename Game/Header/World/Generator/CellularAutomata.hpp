#pragma once

#include <cstdlib>

class Cell {
public:
    bool previousState = 0;
    bool currentState = 0;
};

class CellularAutomata {

    // TODO destroy cells
public:
    Cell ***& generate3DWorld(int sizeX, int sizeY, int sizeZ) {
        // Generate cells randomly
        m_sizeX = sizeX;
        m_sizeY = sizeY;
        m_sizeZ = sizeZ;
        m_cells = new Cell **[sizeX];
        for (int x = 0; x<sizeX; x++)
        {
            m_cells[x] = new Cell *[sizeY];
            for (int y = 0; y < sizeY; y++)
            {
                m_cells[x][y] = new Cell[sizeZ];
                for (int z = 0; z < sizeZ; z++)
                {
                    Cell& cell = m_cells[x][y][z];
                    if (rand() / (double) RAND_MAX < 0.5) {
                        cell.currentState = false;
                        cell.previousState = false;
                    }
                    else {
                        cell.currentState = true;
                        cell.previousState = true;
                    }
                }
            }
        }

        int iter = 20;
        for (int i = 0; i < iter; i++) {
            for (int x = 0; x < sizeX; x++)
                for (int y = 0; y < sizeY; y++)
                    for (int z = 0; z < sizeZ; z++) {
                        Cell &cell = m_cells[x][y][z];
                        cell.previousState = cell.currentState;
                    }
            for (int x = 0; x<sizeX; x++) {
                for (int y = 0; y < sizeY; y++)
                    for (int z = 0; z < sizeZ; z++) {
                        Cell &cell = m_cells[x][y][z];
                        int sum = sumNeighbors(x, y, z);
                        if (sum > 14) {
                            cell.currentState = true;
                        } else if (sum < 13){
                            cell.currentState = false;
                        }
                    }
            }

        }
        return m_cells;
    }

    int sumNeighbors(int _x, int _y, int _z) {
        int sum = 0;

        int count = 0;
        for (int x = _x - 1; x <= _x + 1; x++) {
            for (int y = _y - 1; y <= _y + 1; y++) {
                for (int z = _z - 1; z <= _z + 1; z++) {
                    // Cube is in bounds
                    if (x > 0 && x < m_sizeX &&
                        y > 0 && y < m_sizeY &&
                        z > 0 && z < m_sizeZ)
                    {
                        Cell& cell = m_cells[x][y][z];
                        // Don't want to count the original cube
                        if (x != _x || y != _y || z != _z) {
                            if (m_cells[x][y][z].previousState)
                                sum++;
                        }
                    }
                }
            }
        }
        return sum;
    }

private:
    int m_sizeX;
    int m_sizeY;
    int m_sizeZ;
    Cell *** m_cells;

};
