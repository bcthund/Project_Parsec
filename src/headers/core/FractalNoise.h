/*
 * FractalNoise.h
 *
 *  Created on: Mar 29, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_CORE_FRACTALNOISE_H_
#define HEADERS_CORE_FRACTALNOISE_H_

#include "core_functions.h"
//#include <cmath>
//#include <cstdio>
//#include <random>
#include <functional>
//#include <algorithm>
//#include <utility>
//#include <iostream>
//#include <fstream>

namespace Core {
	class FractalNoise {
		public:
			FractalNoise(unsigned seed = 2016);
			virtual ~FractalNoise();
			float eval(Vector2f &p) const;
			double getNoise(float x, float y, float frequency, float lacunarity, float multiplier, int layers);

			float maxNoise;

			static const unsigned kMaxTableSize = 256;
			static const unsigned kMaxTableSizeMask = kMaxTableSize - 1;
			float r[kMaxTableSize];
			unsigned permutationTable[kMaxTableSize * 2];
	};

} /* namespace Core */

#endif /* HEADERS_CORE_FRACTALNOISE_H_ */
