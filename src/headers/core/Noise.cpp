/*
 * Noise.cpp
 *
 *  Created on: Oct 3, 2020
 *      Author: bcthund
 */

#include <core/Noise.h>
//#include "core_functions.h"
//#include "../gamesys/MapData.h"
//#include "../core/SimplexNoise.h"
//#include <libnoise/noise.h>

namespace Core {
	namespace Noise {

		unsigned seed1 = 42;
		unsigned seed2 = 1024;
		unsigned seed3 = 420;
		unsigned seed4 = 4096;

		std::minstd_rand0 rng1 = std::minstd_rand0(seed1);
		std::minstd_rand0 rng2 = std::minstd_rand0(seed2);
		std::minstd_rand0 rng3 = std::minstd_rand0(seed3);
		std::minstd_rand0 rng4 = std::minstd_rand0(seed4);

		noise::module::Perlin genPerlin;
		noise::module::RidgedMulti genRidged;
		noise::module::Voronoi genVoronoi;
		noise::module::Billow genBillow;
		SimplexNoise genSimplex;

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
					return ((newValue-params.fMin)/(params.fMax-params.fMin) * (params.fNewMax-params.fNewMin) + (params.fNewMin) );
				}
				case FUNCTION_REMAP_ABOVE: {
					t_FunctionParams::u_Type::t_RemapAbove &params = *(t_FunctionParams::u_Type::t_RemapAbove*)paramsStruct[paramsStruct.function];
					if(newValue>=params.threshold) {
						return ((newValue-params.fMin)/(params.fMax-params.fMin) * (params.fNewMax-params.fNewMin) + (params.fNewMin) );
					}
					return newValue;
				}
				case FUNCTION_REMAP_BELOW: {
					t_FunctionParams::u_Type::t_RemapBelow &params = *(t_FunctionParams::u_Type::t_RemapBelow*)paramsStruct[paramsStruct.function];
					if(newValue<=params.threshold) {
						return ((newValue-params.fMin)/(params.fMax-params.fMin) * (params.fNewMax-params.fNewMin) + (params.fNewMin) );
					}
					return newValue;
				}
				case FUNCTION_POWER: {
					t_FunctionParams::u_Type::t_Power &params = *(t_FunctionParams::u_Type::t_Power*)paramsStruct[paramsStruct.function];
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
//				case NOISE_SIMPLEX:
//					return &simplex;
//					break;
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

//		t_Simplex &t_Noise::add(std::string name, t_Simplex* noise) {
//			int id = simplex.add(noise);
//			layers.add(name, std::make_pair(NOISE_SIMPLEX, id));
//			return *simplex[id];
//		}

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

//		t_Simplex& t_Noise::getSimplex(std::string name) {
//			return *simplex[layers[name].second];
//		}

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
//			for (auto item : simplex )			delete item;
			for (auto item : perlin )			delete item;
			for (auto item : fractal )			delete item;
//			for (auto item : ridgedSimplex )	delete item;
			for (auto item : ridgedPerlin )		delete item;
			for (auto item : voronoi )			delete item;
			for (auto item : billow )			delete item;
		}







		//		noise::module::Perlin genPerlin;
//		noise::module::RidgedMulti genRidged;
//		noise::module::Voronoi genVoronoi;
//		noise::module::Billow genBillow;
//		SimplexNoise genSimplex;
		double getNoise(float x, float z, Core::Noise::t_Noise *noise)
//		double getNoise(	float x,
//							float z,
//							Core::Noise::t_Noise *noise,
//							noise::module::Perlin genPerlin,
//							noise::module::RidgedMulti genRidged,
//							noise::module::Voronoi genVoronoi,
//							noise::module::Billow genBillow,
//							SimplexNoise genSimplex,
//							std::minstd_rand0 rng1,
//							std::minstd_rand0 rng2,
//							std::minstd_rand0 rng3,
//							std::minstd_rand0 rng4	)
		{
			double dHeight = 0.0f;


			for ( auto layer : noise->layers ) {
				Core::Noise::eNoiseType type	= layer.first;
				int index				= layer.second;

				switch(type) {
//					case Core::Noise::NOISE_SIMPLEX:
//					{
//						for( auto const &param : *noise->simplex[index] ) {
//							double  e1 = 0.0f,
//									e2 = 0.0f;
//
////							SimplexNoise simNoise1 = SimplexNoise( param->frequency, param->amplitude, param->lacunarity, param->persistance );
//							SimplevTexCoordsxNoise simNoise1 = SimplexNoise( 0.0001f, 1.0f, 1.0f, 1.0f );
////							SimplexNoise simNoise1;
//							e1 = simNoise1.noise(x, z);
//							e2 = Core::Noise::applyFunctions(e1, dHeight, *param);
//							dHeight = Core::Noise::applyMode(e2, dHeight, param->mode);
//
////							// Octaves
////							// TODO: Fix octave implementation (octaves and frequency built in to getPerlin())
////							float amplitudeTotal = 0.0f;
////							for(int n=0; n<param->octaves(); n++) {
////								e1 = param->octaveData[n].amplitude * genPerlin.GetValue(x, z, 0) / 2.0 + 0.5;
////								amplitudeTotal += param->octaveData[n].amplitude;
////							}
////							e2 /= amplitudeTotal;
////
////							e2 = Core::Noise::applyFunctions(e1, dHeight, *param);
////							dHeight = Core::Noise::applyMode(e2, dHeight, param->mode);
//						}
//						break;
//					}
					case Core::Noise::NOISE_PERLIN:
					{
						// Layers
						for( auto const &param : *noise->perlin[index] ) {

							double  e1 = 0.0f,
									e2 = 0.0f;

							Core::Noise::rng1 = std::minstd_rand0(param->seed);
							Core::Noise::genPerlin.SetSeed(Core::Noise::rng1());
							genPerlin.SetFrequency(param->frequency);
							genPerlin.SetLacunarity(param->lacunarity);
							genPerlin.SetNoiseQuality(param->quality);
							genPerlin.SetOctaveCount(param->octaves);
							genPerlin.SetPersistence(param->persistence);

							e1 = genPerlin.GetValue(x, z, 0);
							e2 = Core::Noise::applyFunctions(e1, dHeight, *param);
							dHeight = Core::Noise::applyMode(e2, dHeight, param->mode);
						}
						break;
					}
					case Core::Noise::NOISE_FRACTAL:
					{
						for( auto const &param : *noise->fractal[index] ) {
							double e1 = 0.0f;
							double e2 = 0.0f;
//							SimplexNoise simNoise1 = SimplexNoise( param->frequency, param->amplitude, param->lacunarity, param->persistance );

							genSimplex.setAmplitude(param->amplitude);
							genSimplex.setFrequency(param->frequency);
							genSimplex.setLacunarity(param->lacunarity);
							genSimplex.setPersiistence(param->persistence);
							genSimplex.setSeed(param->seed);
//							e1 = genSimplex.fractal( param->octaves, x, z, dHeight);
							e1 = genSimplex.fractal( param->octaves, x, z, 0);
							//e1 = simNoise1.fractal( param->octaves, x, z, 0);
							e2 = Core::Noise::applyFunctions(e1, dHeight, *param);
							dHeight = Core::Noise::applyMode(e2, dHeight, param->mode);
						}
						break;
					}

//					case Core::Noise::NOISE_RIDGED_SIMPLEX:
//					{
//						double nx = x/(noise->parent->chunk_size*2) - 0.5, ny = z/(noise->parent->chunk_size*2) - 0.5;
//						for( auto const &param : *noise->ridgedSimplex[index] ) {
//							double e1 = 0.0f;
//							double e2 = 0.0f;
//							double e3 = 0.0f;
//							SimplexNoise simNoise1 = SimplexNoise( param->frequency, param->amplitude, param->lacunarity, param->persistance );
////							e1 = (param->threshold - abs(simNoise1.fractal( x, z, dHeight)));
////							e1 = (param->threshold - abs(simNoise1.fractal( param->octaves, x, z, dHeight/20000.0f)));
////							e1 = (param->threshold - abs(simNoise1.fractal( param->octaves, x, z)));
//							e1 = (param->threshold - abs(simNoise1.fractal( param->octaves, nx, ny)));
//
//							int sign = 1;
//							if(e1<0) sign = -1;
//							e2 = e1;
//							e3 += sign * ((std::pow(abs(e2), param->power)*param->scale));
//
//							if(param->funcHeightEnable) {
//								if(dHeight<(param->funcHeightLowerValue)) {
//									dHeight += e3 * fmax(fmin((dHeight/param->funcHeightLowerValue), 1.0f), 0.0f);
//								}
//								else if(dHeight>(param->funcHeightUpperValue)) {
//									dHeight += e3 * fmax(fmin((1.0f-(dHeight/(param->funcHeightUpperValue*2.0f))), 1.0f), 0.0f);
//								}
//								else dHeight += e3;
//							}
//							else dHeight += e3;
//
//						}
//						break;
//					}

					case Core::Noise::NOISE_RIDGED_PERLIN:
					{
						// Layers
						for( auto const &param : *noise->ridgedPerlin[index] ) {

							double  e1 = 0.0f,
									e2 = 0.0f,
									e3 = 0.0f;

							rng2 = std::minstd_rand0(param->seed);
							genRidged.SetSeed(rng2());
							genRidged.SetFrequency(param->frequency);
							genRidged.SetLacunarity(param->lacunarity);
							genRidged.SetNoiseQuality(param->quality);
							genRidged.SetOctaveCount(param->octaves);

							e1 = genRidged.GetValue(x, z, 0);
							e2 = Core::Noise::applyFunctions(e1, dHeight, *param);
							dHeight = Core::Noise::applyMode(e2, dHeight, param->mode);
						}
						break;
					}

					case Core::Noise::NOISE_VORONOI:
					{
						// Layers
						for( auto const &param : *noise->voronoi[index] ) {

							double  e1 = 0.0f,
									e2 = 0.0f,
									e3 = 0.0f;

							rng3 = std::minstd_rand0(param->seed);
							genVoronoi.SetSeed(rng3());
							genVoronoi.SetFrequency(param->frequency);
							genVoronoi.SetDisplacement(param->displacement);
							genVoronoi.EnableDistance(param->bDistance);

							e1 = genVoronoi.GetValue(x, z, 0);
							e2 = Core::Noise::applyFunctions(e1, dHeight, *param);
							dHeight = Core::Noise::applyMode(e2, dHeight, param->mode);

						}
						break;
					}

					case Core::Noise::NOISE_BILLOW:
					{
						// Layers
						for( auto const &param : *noise->billow[index] ) {

							double  e1 = 0.0f,
									e2 = 0.0f,
									e3 = 0.0f;

							rng4 = std::minstd_rand0(param->seed);
							genBillow.SetSeed(rng4());
							genBillow.SetFrequency(param->frequency);
							genBillow.SetLacunarity(param->lacunarity);
							genBillow.SetPersistence(param->persistence);
							genBillow.SetNoiseQuality(param->quality);
							genBillow.SetOctaveCount(param->octaves);

							e1 = genBillow.GetValue(x, z, 0);
							e2 = Core::Noise::applyFunctions(e1, dHeight, *param);
							dHeight = Core::Noise::applyMode(e2, dHeight, param->mode);
						}
						break;
					}

					default:	// NOISE_NONE
						debug.log("Load NONE");
				}

			}

			return dHeight;
		}






















































	} /* namespace Noise */
} /* namespace Core */
