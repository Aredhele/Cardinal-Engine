#include "World/Generator/GUI/GeneratorGUI.hpp"

const FastNoise::NoiseType GeneratorGUI::NOISE_TYPES [] = {FastNoise::NoiseType::Value, FastNoise::NoiseType::Perlin, FastNoise::NoiseType::Simplex, FastNoise::NoiseType::Cubic, FastNoise::NoiseType::Cellular, FastNoise::NoiseType::WhiteNoise, FastNoise::NoiseType::ValueFractal, FastNoise::NoiseType::PerlinFractal, FastNoise::NoiseType::SimplexFractal, FastNoise::NoiseType::CubicFractal};

void GeneratorGUI::drawGUI()
{
    ImGui::Begin("World Generator");
    if (ImGui::CollapsingHeader("General Settings"))
    {
        if (ImGui::Combo("Noise type", &m_noiseType_idx, "Value\0Perlin\0Simplex\0Cubic\0Cellular\0WhiteNoise\0ValueFractal\0PerlinFractal\0SimplexFractal\0CubicFractal\0")) {
            m_isDrawingCellularSettings = false;
            m_isDrawingFractalSettings = false;
            if (m_noiseType_idx == 4) {
                m_isDrawingCellularSettings = true;
            } else if (m_noiseType_idx > 4) {
                m_isDrawingFractalSettings = true;
            }
            m_generatorSettings.noiseType = NOISE_TYPES[m_noiseType_idx];
        }
        ImGui::InputInt("Seed", &m_generatorSettings.seed);
        ImGui::InputFloat("Frequency", &m_generatorSettings.frequency);
        ImGui::Combo("Interpolation type", &m_interpType_idx, "Classic\0Dark\0Light\0");
    }
    drawCellularSettings(&m_isDrawingCellularSettings);
    drawFractalSettings(&m_isDrawingFractalSettings);
    ImGui::End();
}

void GeneratorGUI::drawFractalSettings(bool* isDrawing)
{
    if (!*isDrawing) return;
    if (ImGui::CollapsingHeader("Fractal Settings")) {
        ImGui::Combo("Fractal type", &m_fractalType_idx, "Classic\0Dark\0Light\0");
        ImGui::InputInt("Octaves", &m_generatorSettings.octaves);
        ImGui::InputFloat("Lacunarity", &m_generatorSettings.lacunarity);
        ImGui::InputFloat("Gain", &m_generatorSettings.gain);
    }
}

void GeneratorGUI::drawCellularSettings(bool* isDrawing)
{
    if (!*isDrawing) return;
    if (ImGui::CollapsingHeader("Cellular Settings")) {
        ImGui::Combo("Distance function", &m_distanceFunction_idx, "Classic\0Dark\0Light\0");
        ImGui::Combo("Return type", &m_returnType_idx, "Classic\0Dark\0Light\0");
    }
}
