/*
 * Noise.cpp
 *
 *  Created on: Oct 3, 2020
 *      Author: bcthund
 */

#include <core/Noise.h>

namespace Core {
	namespace Noise {
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		//	Modes
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		double applyMode(double src, double dst, eModes mode) {
			switch(mode) {
				case MODE_ADD:
					return dst+src;
					break;
				case MODE_SUBTRACT:
					return dst-src;
					break;
				case MODE_DIVIDE:
					return dst/src;
					break;
				case MODE_MULTIPLY:
					return dst*src;
					break;
				case MODE_MODULUS:
					return std::fmod(dst, src);
					break;
				default:
					return 0.0f;
			}
		}

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		//	Functions
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		double applyFunction(double currentValue, double newValue, /*eFunctions function,*/ t_FunctionParams &paramsStruct) {
			switch(paramsStruct.function) {
				case FUNCTION_REMAP: {
					t_FunctionParams::u_Type::t_Remap &params = *(t_FunctionParams::u_Type::t_Remap*)paramsStruct[paramsStruct.function];
//					paramsStruct.types.remap
					return ((newValue-params.fMin)/(params.fMax-params.fMin) * (params.fNewMax-params.fNewMin) + (params.fNewMin) );
				}
				case FUNCTION_REMAP_ABOVE: {
					t_FunctionParams::u_Type::t_RemapAbove &params = *(t_FunctionParams::u_Type::t_RemapAbove*)paramsStruct[paramsStruct.function];
					if(newValue>=params.threshold)
						return ((newValue-params.fMin)/(params.fMax-params.fMin) * (params.fNewMax-params.fNewMin) + (params.fNewMin) );
					return newValue;
				}
				case FUNCTION_REMAP_BELOW: {
					t_FunctionParams::u_Type::t_RemapBelow &params = *(t_FunctionParams::u_Type::t_RemapBelow*)paramsStruct[paramsStruct.function];
					if(newValue<=params.threshold)
						return ((newValue-params.fMin)/(params.fMax-params.fMin) * (params.fNewMax-params.fNewMin) + (params.fNewMin) );
					return newValue;
				}
				case FUNCTION_POWER: {
					t_FunctionParams::u_Type::t_Power &params = *(t_FunctionParams::u_Type::t_Power*)paramsStruct[paramsStruct.function];
//					#define signbit_p1_or_n1(x)  ((signbit(x) ?  -1 : 1)
//					int sign = 1;
//					if(e1<0) sign = -1;
//					int sign = (std::signbit(newValue) ?  -1 : 1);
					return (std::signbit(newValue) ?  -1 : 1) * std::pow(abs(newValue), params.value);
				}
				case FUNCTION_REPLACE_ABOVE: {
					t_FunctionParams::u_Type::t_ReplaceAbove &params = *(t_FunctionParams::u_Type::t_ReplaceAbove*)paramsStruct[paramsStruct.function];
					if(newValue>0.8) return params.value;
					return newValue;
				}
				case FUNCTION_REPLACE_BELOW: {
					t_FunctionParams::u_Type::t_ReplaceBelow &params = *(t_FunctionParams::u_Type::t_ReplaceBelow*)paramsStruct[paramsStruct.function];
					if(newValue<0.5) return params.value;
					return newValue;
				}
				case FUNCTION_CLAMP_ABOVE: {
					t_FunctionParams::u_Type::t_ClampAbove &params = *(t_FunctionParams::u_Type::t_ClampAbove*)paramsStruct[paramsStruct.function];
					return fmin(newValue, params.threshold);
				}
				case FUNCTION_CLAMP_BELOW: {
					t_FunctionParams::u_Type::t_ClampBelow &params = *(t_FunctionParams::u_Type::t_ClampBelow*)paramsStruct[paramsStruct.function];
					return fmax(newValue, params.threshold);
				}
				case FUNCTION_FADE_ABOVE: {
					t_FunctionParams::u_Type::t_FadeAbove &params = *(t_FunctionParams::u_Type::t_FadeAbove*)paramsStruct[paramsStruct.function];
					if(params.clamp) {
						if(currentValue<params.threshold) return newValue;
						else if(currentValue>=params.threshold && currentValue<(params.threshold+params.fadeRange)) {
							return newValue * ((-params.maxValue/params.fadeRange)*(currentValue-(params.threshold+params.fadeRange)));
						}
						else return 0.0f;
					}
					else return newValue * ((-params.maxValue/params.fadeRange)*(currentValue-(params.threshold+params.fadeRange)));
					return newValue;
				}
				case FUNCTION_FADE_BELOW: {
					t_FunctionParams::u_Type::t_FadeBelow &params = *(t_FunctionParams::u_Type::t_FadeBelow*)paramsStruct[paramsStruct.function];
					if(params.clamp) {
						if(currentValue>params.threshold) return newValue;
						else if(currentValue<=params.threshold && currentValue>(params.threshold-params.fadeRange)) {
							return newValue * ((params.maxValue/params.fadeRange)*(currentValue-(params.threshold-params.fadeRange)));
						}
						else return 0.0f;
					}
					else return newValue * ((params.maxValue/params.fadeRange)*(currentValue-(params.threshold-params.fadeRange)));
					return newValue;
				}
				case FUNCTION_FADE_PARABOLA: {
					t_FunctionParams::u_Type::t_FadeParabola &params = *(t_FunctionParams::u_Type::t_FadeParabola*)paramsStruct[paramsStruct.function];
					if(params.clamp) {
						if(currentValue>=params.lowerThreshold && currentValue<=params.upperThreshold) {
							float a = params.maxValue/((params.inflectionPoint-params.lowerThreshold)*(params.inflectionPoint-params.upperThreshold));
							float b = ((currentValue-params.lowerThreshold)*(currentValue-params.upperThreshold));
							return a*b;
						}
						else return 0.0f;
					}
					else {
						float a = params.maxValue/((params.inflectionPoint-params.lowerThreshold)*(params.inflectionPoint-params.upperThreshold));
						float b = ((currentValue-params.lowerThreshold)*(currentValue-params.upperThreshold));
						return a*b;
					}
					return newValue;
				}
				case FUNCTION_SCALE: {
					t_FunctionParams::u_Type::t_Scale &params = *(t_FunctionParams::u_Type::t_Scale*)paramsStruct[paramsStruct.function];
					return newValue * params.value;
				}
				case FUNCTION_ABSOLUTE: {
//					t_FunctionParams::u_Type::t_Absolute &params = paramsStruct[paramsStruct.function];
					return abs(newValue);
				}
				case FUNCTION_ONE_MINUS: {
//					t_FunctionParams::u_Type::t_Invert &params = paramsStruct[paramsStruct.function];
					return 1-newValue;
				}
				case FUNCTION_OFFSET: {
					t_FunctionParams::u_Type::t_Offset &params = *(t_FunctionParams::u_Type::t_Offset*)paramsStruct[paramsStruct.function];
					return newValue+params.value;
				}
//				case FUNCTION_CULL_ABOVE:
//					break;
//				case FUNCTION_CULL_BELOW:
//					break;
//				case FUNCTION_TURBULENCE:
//					break;
				default:
					return newValue;
			}
		}

		/**
		 * @brief
		 * @param src The current value to perform operations on
		 * @param dst The previous value used for reference in some functions
		 * @param params The full struct of all functions to be applied
		 * @return
		 */
		double applyFunctions(double src, double dst, t_BaseParams &params) {
			double dReturn = src;
			for( auto &function : params.functions ) {
				dReturn = applyFunction(dst, dReturn, *function);
			}
			return dReturn;
		}

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		//	Noise Class
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		void * t_Noise::operator[](std::string name) {
			switch(layers[name].first) {
				case NOISE_NONE:
					return &none;
					break;
				case NOISE_SIMPLEX:
					return &simplex;
					break;
				case NOISE_PERLIN:
					return &perlin;
					break;
				case NOISE_FRACTAL:
					return &fractal;
					break;
//				case NOISE_RIDGED_SIMPLEX:
//					return &ridgedSimplex;
//					break;
				case NOISE_RIDGED_PERLIN:
					return &ridgedPerlin;
					break;
				case NOISE_VORONOI:
					return &voronoi;
					break;
				case NOISE_BILLOW:
					return &billow;
					break;
			}
			return nullptr;
		}

		t_None &t_Noise::add(std::string name, t_None* noise) {
			int id = none.add(noise);
			layers.add(name, std::make_pair(NOISE_NONE, id));
			return *none[id];
		}

		t_Simplex &t_Noise::add(std::string name, t_Simplex* noise) {
			int id = simplex.add(noise);
			layers.add(name, std::make_pair(NOISE_SIMPLEX, id));
			return *simplex[id];
		}

		t_Perlin &t_Noise::add(std::string name, t_Perlin* noise) {
			int id = perlin.add(noise);
			layers.add(name, std::make_pair(NOISE_PERLIN, id));
			return *perlin[id];
		}

		t_Fractal &t_Noise::add(std::string name, t_Fractal* noise) {
			int id = fractal.add(noise);
			layers.add(name, std::make_pair(NOISE_FRACTAL, id));
			return *fractal[id];
		}

//		t_RidgedSimplex &t_Noise::add(std::string name, t_RidgedSimplex* noise) {
//			int id = ridgedSimplex.add(noise);
//			layers.add(name, std::make_pair(NOISE_RIDGED_SIMPLEX, id));
//			return *ridgedSimplex[id];
//		}

		t_RidgedPerlin &t_Noise::add(std::string name, t_RidgedPerlin* noise) {
			int id = ridgedPerlin.add(noise);
			layers.add(name, std::make_pair(NOISE_RIDGED_PERLIN, id));
			return *ridgedPerlin[id];
		}

		t_Voronoi &t_Noise::add(std::string name, t_Voronoi* noise) {
			int id = voronoi.add(noise);
			layers.add(name, std::make_pair(NOISE_VORONOI, id));
			return *voronoi[id];
		}

		t_Billow &t_Noise::add(std::string name, t_Billow* noise) {
			int id = billow.add(noise);
			layers.add(name, std::make_pair(NOISE_BILLOW, id));
			return *billow[id];
		}




		// Get a generator by layer name, but must know the correct type
		t_None& t_Noise::getNone(std::string name) {
			return *none[layers[name].second];
		}

		t_Simplex& t_Noise::getSimplex(std::string name) {
			return *simplex[layers[name].second];
		}

		t_Perlin& t_Noise::getPerlin(std::string name) {
			return *perlin[layers[name].second];
		}

		t_Fractal& t_Noise::getFractal(std::string name) {
			return *fractal[layers[name].second];
		}

//		t_RidgedSimplex& t_Noise::getRidgedSimplex(std::string name) {
//			return *ridgedSimplex[layers[name].second];
//		}

		t_RidgedPerlin& t_Noise::getRidgedPerlin(std::string name) {
			return *ridgedPerlin[layers[name].second];
		}

		t_Voronoi& t_Noise::getVoronoi(std::string name) {
			return *voronoi[layers[name].second];
		}

		t_Billow& t_Noise::getBillow(std::string name) {
			return *billow[layers[name].second];
		}

		t_Noise::t_Noise(Sys::Map::t_ChunkData *p) {
			parent = p;
		}

		t_Noise::~t_Noise() {
			for (auto item : none )				delete item;
			for (auto item : simplex )			delete item;
			for (auto item : perlin )			delete item;
			for (auto item : fractal )			delete item;
//			for (auto item : ridgedSimplex )	delete item;
			for (auto item : ridgedPerlin )		delete item;
			for (auto item : voronoi )			delete item;
			for (auto item : billow )			delete item;
		}



	} /* namespace Noise */
} /* namespace Core */
