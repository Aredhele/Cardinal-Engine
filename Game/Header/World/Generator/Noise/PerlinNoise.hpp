#ifndef PERLIN_NOISE_HPP
#define PERLIN_NOISE_HPP

#include <vector>

class PerlinNoise
{
public:
    /// Constructor
    PerlinNoise(double p_amplitude = 6, double p_shift = 15);
    PerlinNoise(size_t p_seed, double p_amplitude = 6, double p_shift = 15);
    PerlinNoise(PerlinNoise& copy) = delete;

    /// Get a noise value
    double noise(double x, double y , double z);
    double octave(double x, double y, double z, int octaves, double persistence);

private:
    double m_amplitude;
    double m_shift;

    double fade(double t);
    double lerp(double t, double a, double b);
    double grad(int hash, double x, double y, double z);

    std::vector<int> m_permutation;
};

#endif // PERLIN_NOISE_HPP