
#pragma once

#include "Glm/glm/glm.hpp"
#include "GLm/glm/ext.hpp"

class NYPerlin
{
public :
    glm::vec3 * _Dirs;
    int _Width;
    int _Size;
    float resolution = 2.0f;
    NYPerlin()
    {
        _Width = 50;
        _Size = _Width*_Width*_Width;
        _Dirs = new glm::vec3[_Size];
        for (int i = 0; i < _Size; i++)
        {
            _Dirs[i].x = glm::linearRand(0.0f, 10000.0f);
            _Dirs[i].y = glm::linearRand(0.0f, 10000.0f);
            _Dirs[i].z = glm::linearRand(0.0f, 10000.0f);
        }
    }

    float lerp(float a, float b, float alpha) {
        float alphaSmooth = alpha * (3 * alpha - 2 * alpha*alpha);
        return (1 - alphaSmooth)*a + alphaSmooth * b;
    }
public:

    float sample(float xBase, float yBase, float zBase)
    {
        float x = xBase;
        float y = yBase;
        float z = zBase;

        while (x > _Width)
            x -= _Width;
        while (y > _Width)
            y -= _Width;
        while (z > _Width)
            z -= _Width;


        int x1 = floor(x);
        int x2 = floor(x) + 1;
        int y1 = floor(y);
        int y2 = floor(y) + 1;
        int z1 = floor(z);
        int z2 = floor(z) + 1;
        float dx = x - x1;
        float dy = y - y1;
        float dz = z - z1;

        glm::vec3 pos(x, y, z);
        glm::vec3 sommets[8];
        //plan X2
        sommets[0] = glm::vec3(x2, y1, z1);
        sommets[1] = glm::vec3(x2, y1, z2);
        sommets[2] = glm::vec3(x2, y2, z2);
        sommets[3] = glm::vec3(x2, y2, z1);

        //plan X1
        sommets[4] = glm::vec3(x1, y1, z1);
        sommets[5] = glm::vec3(x1, y1, z2);
        sommets[6] = glm::vec3(x1, y2, z2);
        sommets[7] = glm::vec3(x1, y2, z1);

        float angles[8];
        for (int i = 0; i < 8; i++)
        {
           /* int index   = (int)(sommets[i].x * _Width * _Width + sommets[i].y * _Width + sommets[i].z);
            glm::vec3 a = pos - sommets[i];
            glm::vec3 b = _Dirs[index];

            angles[i] = a.x * b. x + a.y * b.y + a.z * b.z;*/


          angles[i] = glm::dot(
                    pos - sommets[i],
                    _Dirs[ (int)(  sommets[i].x * _Width * _Width
                                 + sommets[i].y * _Width + sommets[i].z)]);
        }

        //plan X2
        float ybas = lerp(angles[0], angles[3],dy);
        float yhaut = lerp(angles[1], angles[2], dy);
        float mid2 = lerp(ybas, yhaut, dz);

        //plan X1
        ybas = lerp(angles[4], angles[7], dy);
        yhaut = lerp(angles[5], angles[6], dy);
        float mid1 = lerp(ybas, yhaut, dz);

        float res = lerp(mid1, mid2, dx);

        res = (res + 1) / resolution;


        return res;
    }
};

