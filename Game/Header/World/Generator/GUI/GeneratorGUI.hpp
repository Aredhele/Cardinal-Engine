#pragma once

#include "ImGUI/imgui.h"
#include "World/Generator/GenerationSettings.hpp"

class GeneratorGUI
{
public:
    GenerationSettings m_generatorSettings;

    void drawGUI();

private:

    static const FastNoise::NoiseType NOISE_TYPES [];

    int m_noiseType_idx = 0;
    int m_interpType_idx = 0;
    int m_fractalType_idx = 0;
    int m_distanceFunction_idx = 0;
    int m_returnType_idx = 0;

    bool m_isDrawingFractalSettings = false;
    bool m_isDrawingCellularSettings = false;


    void drawFractalSettings(bool * isDrawing);

    void drawCellularSettings(bool * isDrawing);
};
