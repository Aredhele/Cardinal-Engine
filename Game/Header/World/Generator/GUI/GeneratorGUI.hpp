#pragma once

#include <World/Generator/BasicWorldGenerator.hpp>
#include "ImGUI/imgui.h"
#include "World/Generator/GenerationSettings.hpp"

class GeneratorGUI
{
public:

    void drawGUI(bool * isDrawing);
    void setGenerator(BasicWorldGenerator* generator);

private:

    static const FastNoise::NoiseType NOISE_TYPES[];
    static const FastNoise::Interp INTERPOLATION_TYPES[];
    static const FastNoise::FractalType FRACTAL_TYPES[];
    static const FastNoise::CellularDistanceFunction CELLULAR_DIST_FUNCS[];
    static const FastNoise::CellularReturnType CELLULAR_RETURN_TYPES[];

    GenerationSettings m_generatorSettings;
    BasicWorldGenerator* mp_worldGenerator = nullptr;

    int m_noiseType_idx = 0;
    int m_interpType_idx = 0;
    int m_fractalType_idx = 0;
    int m_distanceFunction_idx = 0;
    int m_returnType_idx = 0;

    bool m_isDrawingFractalSettings = false;
    bool m_isDrawingCellularSettings = false;
    bool m_isDrawingGradientPerturbSettings = false;

    void drawGeneralSettings();
    void drawFractalSettings();
    void drawCellularSettings();
    void drawGradientPerturbSettings();
};
