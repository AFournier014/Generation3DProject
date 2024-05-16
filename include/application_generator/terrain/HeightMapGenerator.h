#ifndef HEIGHT_MAP_GENERATOR_H
#define HEIGHT_MAP_GENERATOR_H
#include <vector>

struct HeightMap
{
    std::vector<std::vector<float>> values;
    float minValue;
    float maxValue;

    HeightMap(const std::vector<std::vector<float>>& values, float minValue, float maxValue)
        : values(values), minValue(minValue), maxValue(maxValue)
    {
    }
};

class HeightMapGenerator
{
public:
    static HeightMap generate_height_map(int width, int height, float heightMultiplier, float scale, int octaves,
                                         float persistance, float lacunarity, int seed);
    static std::vector<std::vector<float>> generate_noise_map(int width, int height, float scale, int octaves,
                                                              float persistance, float lacunarity, int seed);
};

inline float GetRandF(float fMin, float fMax)
{
    return (fMax - fMin) * ((((float)rand()) / (float)RAND_MAX)) + fMin;
}

inline int GetRand(int min, int max)
{
    return min + (rand() % static_cast<int>(max - min + 1));
}

#endif // HEIGHT_MAP_GENERATOR_H
