/*
 * FractalNoise.cpp
 *
 *  Created on: Mar 29, 2020
 *      Author: bcthund
 */

#include "FractalNoise.h"

namespace Core {

	inline
	float smoothstep(const float &t)
	{
		return t * t * (3 - 2 * t);
	}

	template<typename T = float>
	inline T lerp(const T &lo, const T &hi, const T &t)
	{
		return lo * (1 - t) + hi * t;
	}

	FractalNoise::~FractalNoise() {
		// TODO Auto-generated destructor stub
	}

	FractalNoise::FractalNoise(unsigned seed)
    {
        std::mt19937 gen(seed);
        std::uniform_real_distribution<float> distrFloat;
        auto randFloat = std::bind(distrFloat, gen);

        // create an array of random values and initialize permutation table
        for (unsigned k = 0; k < kMaxTableSize; ++k) {
            r[k] = randFloat();
            permutationTable[k] = k;
        }

        // shuffle values of the permutation table
        std::uniform_int_distribution<unsigned> distrUInt;
        auto randUInt = std::bind(distrUInt, gen);
        for (unsigned k = 0; k < kMaxTableSize; ++k) {
            unsigned i = randUInt() & kMaxTableSizeMask;
            std::swap(permutationTable[k], permutationTable[i]);
            permutationTable[k + kMaxTableSize] = permutationTable[k];
        }

        maxNoise = 0.0f;
    }

    float FractalNoise::eval(Vector2f &p) const
    {
        int xi = std::floor(p.x);
        int yi = std::floor(p.y);

        float tx = p.x - xi;
        float ty = p.y - yi;

        int rx0 = xi & kMaxTableSizeMask;
        int rx1 = (rx0 + 1) & kMaxTableSizeMask;
        int ry0 = yi & kMaxTableSizeMask;
        int ry1 = (ry0 + 1) & kMaxTableSizeMask;

        // random values at the corners of the cell using permutation table
        const float & c00 = r[permutationTable[permutationTable[rx0] + ry0]];
        const float & c10 = r[permutationTable[permutationTable[rx1] + ry0]];
        const float & c01 = r[permutationTable[permutationTable[rx0] + ry1]];
        const float & c11 = r[permutationTable[permutationTable[rx1] + ry1]];

        // remapping of tx and ty using the Smoothstep function
        float sx = smoothstep(tx);
        float sy = smoothstep(ty);

        // linearly interpolate values along the x axis
        float nx0 = lerp(c00, c10, sx);
        float nx1 = lerp(c01, c11, sx);

        // linearly interpolate the nx0/nx1 along they y axis
        return lerp(nx0, nx1, sy);
    }

	double FractalNoise::getNoise(float x, float y, float frequency, float lacunarity, float multiplier, int layers) {
		Vector2f pNoise = Vector2f(x, y) * frequency;
		double noiseMap = 0.0f;
        float amplitude = 1;
        for (unsigned l = 0; l < layers; ++l) {
            noiseMap += eval(pNoise) * amplitude;
            pNoise *= lacunarity;
            amplitude *= multiplier;
        }
        if (noiseMap > maxNoise) maxNoise = noiseMap;	// Currently not used

        return noiseMap;
	}
} /* namespace Core */








































































