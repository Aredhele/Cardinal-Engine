#pragma once

#include "World/Generator/Noise/FastNoise.h"

struct GenerationSettings
{
    // General settings
    FastNoise::NoiseType noiseType = FastNoise::NoiseType::PerlinFractal;
    int seed = 0;
    float frequency = 0.01;
    FastNoise::Interp interpolationType = FastNoise::Interp::Hermite;
    bool gradientPerturb = false;

    // Fractal settings
    FastNoise::FractalType fractalType = FastNoise::FractalType::FBM;
    int octaves = 1;
    float lacunarity = 2.0;
    float gain = 0.5; // persistence

    // Cellular settings
    FastNoise::CellularDistanceFunction distanceFunction = FastNoise::CellularDistanceFunction::Euclidean;
    FastNoise::CellularReturnType returnType = FastNoise::CellularReturnType::CellValue;

    // Grandient perturb settings
    float gradientPertubAmplitude;
    float gradientPerturbFrequency;
};
