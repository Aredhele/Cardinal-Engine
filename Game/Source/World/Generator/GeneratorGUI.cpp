#include "World/Generator/GUI/GeneratorGUI.hpp"

const FastNoise::NoiseType GeneratorGUI::NOISE_TYPES [] = {FastNoise::NoiseType::Value, FastNoise::NoiseType::Perlin, FastNoise::NoiseType::Simplex, FastNoise::NoiseType::Cubic, FastNoise::NoiseType::Cellular, FastNoise::NoiseType::WhiteNoise, FastNoise::NoiseType::ValueFractal, FastNoise::NoiseType::PerlinFractal, FastNoise::NoiseType::SimplexFractal, FastNoise::NoiseType::CubicFractal};

const FastNoise::Interp GeneratorGUI::INTERPOLATION_TYPES [] = { FastNoise::Interp::Hermite, FastNoise::Interp::Linear, FastNoise::Interp::Quintic };

const FastNoise::FractalType GeneratorGUI::FRACTAL_TYPES[] = { FastNoise::FractalType::Billow, FastNoise::FractalType::FBM, FastNoise::FractalType::RigidMulti };

const FastNoise::CellularDistanceFunction GeneratorGUI::CELLULAR_DIST_FUNCS[] = { FastNoise::CellularDistanceFunction::Euclidean, FastNoise::CellularDistanceFunction::Manhattan, FastNoise::CellularDistanceFunction::Natural };

const FastNoise::CellularReturnType GeneratorGUI::CELLULAR_RETURN_TYPES[] = { FastNoise::CellularReturnType::CellValue, FastNoise::CellularReturnType::Distance, FastNoise::CellularReturnType::Distance2, FastNoise::CellularReturnType::Distance2Add, FastNoise::CellularReturnType::Distance2Div, FastNoise::CellularReturnType::Distance2Mul, FastNoise::CellularReturnType::Distance2Sub, FastNoise::CellularReturnType::NoiseLookup };

void GeneratorGUI::drawGUI(bool * isDrawing)
{
    ImGui::Begin("World Generator");
    drawGeneralSettings();
    drawCellularSettings();
    drawFractalSettings();
    if (ImGui::Button("Generate") && mp_worldGenerator != nullptr) {
        mp_worldGenerator->regenerateWorld(m_generatorSettings);
    }
    ImGui::End();
}

void GeneratorGUI::drawFractalSettings()
{
    if (!m_isDrawingFractalSettings) return;
    if (ImGui::CollapsingHeader("Fractal Settings")) {
        if (ImGui::Combo("Fractal type", &m_fractalType_idx, "Billow\0FBM\0RigidMulti\0")) {
            m_generatorSettings.fractalType = FRACTAL_TYPES[m_fractalType_idx];
        }
        ImGui::InputInt("Octaves", &m_generatorSettings.octaves);
        ImGui::InputFloat("Lacunarity", &m_generatorSettings.lacunarity);
        ImGui::InputFloat("Gain", &m_generatorSettings.gain);
    }
}

void GeneratorGUI::drawGeneralSettings() {
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
        if (ImGui::Combo("Interpolation type", &m_interpType_idx, "Hermite\0Linear\0Quintic\0")) {
            m_generatorSettings.interpolationType = INTERPOLATION_TYPES[m_interpType_idx];
        }
    }
}

void GeneratorGUI::drawCellularSettings()
{
    if (!m_isDrawingCellularSettings) return;
    if (ImGui::CollapsingHeader("Cellular Settings")) {
        if (ImGui::Combo("Distance function", &m_distanceFunction_idx, "Euclidean\0Manhattan\0Natural\0")) {
            m_generatorSettings.distanceFunction = CELLULAR_DIST_FUNCS[m_distanceFunction_idx];
        }
        if (ImGui::Combo("Return type", &m_returnType_idx, "CellValue\0Distance\0Distance2\0Distance2Add\0Distance2Div\0Distance2Mul\0Distance2Sub\0NoiseLookup")) {
            m_generatorSettings.returnType = CELLULAR_RETURN_TYPES[m_returnType_idx];
        }
    }
}

void GeneratorGUI::setGenerator(BasicWorldGenerator* generator) {
    mp_worldGenerator = generator;
}
