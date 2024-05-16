#include "terrain/HeightMapGenerator.h"

#include <ctime>
#include <random>

#include "MathIncludes.h"
#include "terrain/PerlinNoise.h"

HeightMap HeightMapGenerator::generate_height_map(int width, int height, float heightMultiplier, float scale, int octaves,
                                                  float persistance, float lacunarity, int seed)
{
    std::vector<std::vector<float>> values = HeightMapGenerator::generate_noise_map(width, height, scale, octaves,
        persistance, lacunarity, seed);

    float minValue = std::numeric_limits<float>::max();
    float maxValue = std::numeric_limits<float>::min();

    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            values[i][j] *= heightMultiplier;

            minValue = std::min(minValue, values[i][j]);
            maxValue = std::max(maxValue, values[i][j]);
        }
    }

    return HeightMap(values, minValue, maxValue);
}

std::vector<std::vector<float>> HeightMapGenerator::generate_noise_map(int width, int height, float scale, int octaves,
                                                          float persistance,
                                                          float lacunarity, int seed)
{
    std::mt19937 prng(seed);
    std::uniform_int_distribution<int> distribution(-100000, 100000);
    
    PerlinNoise pn(seed);
    std::vector<std::vector<float>> noiseMap(width, std::vector<float>(height));
    std::vector<Vector2f> octaveOffsets(octaves);

    float maxPossibleHeight = 0;
    float amplitude = 1;
    float frequency = 1;

    for (int i = 0; i < octaves; i++)
    {
        float offsetX = static_cast<float>(distribution(prng));
        float offsetY = static_cast<float>(distribution(prng));
        octaveOffsets[i] = {offsetX, offsetY};

        maxPossibleHeight += amplitude;
        amplitude *= persistance;
    }

    float maxLocalNoiseHeight = std::numeric_limits<float>::min();
    float minLocalNoiseHeight = std::numeric_limits<float>::max();

    float halfWidth = static_cast<float>(width) / 2.f;
    float halfHeight = static_cast<float>(height) / 2.f;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            amplitude = 1;
            frequency = 1;
            float noiseHeight = 0;

            for (int i = 0; i < octaves; i++)
            {
                float sampleX = (x - halfWidth + octaveOffsets[i].x) / scale * frequency;
                float sampleY = (y - halfHeight + octaveOffsets[i].y) / scale * frequency;

                float perlinValue = static_cast<float>(pn.noise(sampleX, sampleY, 0) * 2 - 1);

                noiseHeight += perlinValue * amplitude;

                amplitude *= persistance;
                frequency *= lacunarity;
            }

            if (noiseHeight > maxLocalNoiseHeight)
            {
                maxLocalNoiseHeight = noiseHeight;
            }

            if (noiseHeight < minLocalNoiseHeight)
            {
                minLocalNoiseHeight = noiseHeight;
            }

            noiseMap[x][y] = noiseHeight;
        }
    }

    return noiseMap;
}