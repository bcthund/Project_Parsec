/*
 * Noise.h
 *
 *  Created on: Oct 3, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_CORE_NOISE_H_
#define HEADERS_CORE_NOISE_H_

#include "core_functions.h"
#include "../gamesys/MapData.h"
//#include "../gamesys/O2D_Data.h"
#include "../core/SimplexNoise.h"
#include <libnoise/noise.h>

namespace Core {

	namespace Noise {

//		extern unsigned seed1;
//		extern unsigned seed2;
//		extern unsigned seed3;
//		extern unsigned seed4;
//
//		extern std::minstd_rand0 rng1;
//		extern std::minstd_rand0 rng2;
//		extern std::minstd_rand0 rng3;
//		extern std::minstd_rand0 rng4;
//
//		extern noise::module::Perlin genPerlin;
//		extern noise::module::RidgedMulti genRidged;
//		extern noise::module::Voronoi genVoronoi;
//		extern noise::module::Billow genBillow;
//		extern SimplexNoise genSimplex;

//		rng1 = std::minstd_rand0(seed1);
//		rng2 = std::minstd_rand0(seed2);
//		rng3 = std::minstd_rand0(seed3);
//		rng4 = std::minstd_rand0(seed4);

//		genPerlin.SetSeed(rng1());
//		genRidged.SetSeed(rng2());
//		genVoronoi.SetSeed(rng3());
//		genBillow.SetSeed(rng4());

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		//	Modes
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// *  	- Modes
		// * 			- Add (currently default)
		// * 			- Subtract (Gets rid of need to specift negative scale?)
		// * 			- Divide
		// * 			- Multiply (Can act as a mask)
		enum eModes {
			MODE_ADD,
			MODE_SUBTRACT,
			MODE_DIVIDE,
			MODE_MULTIPLY,
			MODE_MODULUS
		};

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		//	Functions
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// *  	- Functions
		// *			- REMAP .............. Implement function option ([0-1] or [-1 to 1])
		// *			- REMAP_ABOVE ........ Implement function option (Remap Range - Upper [Replace Upper with rescale])
		// *			- REMAP_BELOW ........ Implement function option (Remap Range - Lower [Replace Lower with rescale])
		// *			- [DONT USE THIS] .... Implement function option (Height for z parameter)
		// *			- POWER .............. Implement function (Power, remove from standard params and make a function option)
		// *			- REPLACE_ABOVE ...... Implement function option (Replace Upper)
		// *			- REPLACE_BELOW ...... Implement function option (Replace Lower)
		// *			- CLAMP_ABOVE ........ Implement function option (Clamp Upper)
		// *			- CLAMP_BELOW ........ Implement function option (Clamp Lower)
		// *			- FADE_ABOVE ......... Implement function option (Upper Fade - Based on parent height [Will need to be reworked, as layer style allows this to run before or after scaling])
		// *			- FADE_BELOW ......... Implement function option (Lower Fade - Based on parent height [Will need to be reworked, as layer style allows this to run before or after scaling])
		// *			- SCALE .............. Implement function option (Scale, remove from standard params and make a function option)
		// *			- CULL_ABOVE ......... Implement function option (Cull Above)
		// *			- CULL_BELOW ......... Implement function option (Cull Below)
		// *			- TURBULENCE ......... Turbulence

		enum eFunctions {
			FUNCTION_NONE,
			FUNCTION_ABSOLUTE,
			FUNCTION_CLAMP_ABOVE,
			FUNCTION_CLAMP_BELOW,
			FUNCTION_FADE_ABOVE,
			FUNCTION_FADE_BELOW,
			FUNCTION_FADE_PARABOLA,
			FUNCTION_OFFSET,
			FUNCTION_ONE_MINUS,
			FUNCTION_POWER,
			FUNCTION_REMAP,
			FUNCTION_REMAP_ABOVE,
			FUNCTION_REMAP_BELOW,
			FUNCTION_REPLACE_ABOVE,
			FUNCTION_REPLACE_BELOW,
			FUNCTION_SCALE,
//			FUNCTION_CULL_ABOVE,
//			FUNCTION_CULL_BELOW,
//			FUNCTION_TURBULENCE
		};

		struct t_FunctionParams {
			eFunctions function;

			union u_Type {
				struct t_Absolute {
					// Placeholder
				} absolute;

				struct t_ClampAbove {
					float threshold;
				} clamp_above;

				struct t_ClampBelow {
					float threshold;
				} clamp_below;

				struct t_FadeAbove {
					float threshold,
						  fadeRange,
						  maxValue;
					bool clamp;
				} fade_above;

				struct t_FadeBelow {
					float threshold,
						  fadeRange,
						  maxValue;
					bool clamp;
				} fade_below;

				struct t_FadeParabola {
					float lowerThreshold,
						  upperThreshold,
						  inflectionPoint,
						  maxValue;
					bool clamp;
				} fade_parabola;

				struct t_Offset {
					float value;
				} offset;

				struct t_OneMinus {
					// Placeholder
				} oneMinus;

				struct t_Power {
					float value;
				} power;

				struct t_Remap {
					float fMin,
						  fMax,
						  fNewMin,
						  fNewMax;
				} remap;

				struct t_RemapAbove {
					float threshold,
						  fMin,
						  fMax,
						  fNewMin,
						  fNewMax;
				} remap_above;

				struct t_RemapBelow {
					float threshold,
						  fMin,
						  fMax,
						  fNewMin,
						  fNewMax;
				} remap_below;

				struct t_ReplaceAbove {
					float threshold;
					float value;
				} replace_above;

				struct t_ReplaceBelow {
					float threshold;
					float value;
				} replace_below;

				struct t_Scale {
					float value;
				} scale;

				// Placeholder; Probably not implemented here
//				struct t_CullAbove {
//					t_CullAbove() {
//					}
//				} cull_above;

				// Placeholder; Probably not implemented here
//				struct t_CullBelow {
//					t_CullBelow() {
//					}
//				} cull_below;

				// Placeholder; Possibly not implemented here (Requires a source noise module)
//				struct t_Turbulence {
//					t_Turbulence() {
//					}
//				} turbulence;
			} types;

			void * operator[](eFunctions function) {
				switch(function) {
					case FUNCTION_ABSOLUTE:
						return &types.absolute;
						break;
					case FUNCTION_CLAMP_ABOVE:
						return &types.clamp_above;
						break;
					case FUNCTION_CLAMP_BELOW:
						return &types.clamp_below;
						break;
					case FUNCTION_FADE_ABOVE:
						return &types.fade_above;
						break;
					case FUNCTION_FADE_BELOW:
						return &types.fade_below;
						break;
					case FUNCTION_FADE_PARABOLA:
						return &types.fade_parabola;
						break;
					case FUNCTION_OFFSET:
						return &types.offset;
						break;
					case FUNCTION_ONE_MINUS:
						return &types.oneMinus;
						break;
					case FUNCTION_POWER:
						return &types.power;
						break;
					case FUNCTION_REMAP:
						return &types.remap;
						break;
					case FUNCTION_REMAP_ABOVE:
						return &types.remap_above;
						break;
					case FUNCTION_REMAP_BELOW:
						return &types.remap_below;
						break;
					case FUNCTION_REPLACE_ABOVE:
						return &types.replace_above;
						break;
					case FUNCTION_REPLACE_BELOW:
						return &types.replace_below;
						break;
					case FUNCTION_SCALE:
						return &types.scale;
						break;
					default:
						return nullptr;
				}
			}

			t_FunctionParams(eFunctions newFunction=FUNCTION_NONE) {
				function = newFunction;
			}
		};

		double applyFunction(double currentValue, double newValue, /*eFunctions function,*/ t_FunctionParams &params);
		struct t_BaseParams;
		double applyFunctions(double src, double dst, t_BaseParams &params);

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		//	Parameters
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

		using t_FunctionList = t_Vector1T<t_FunctionParams*>;
		struct t_BaseParams {
			t_FunctionList functions;
//			t_FunctionParams &addFunction(t_FunctionParams *functionParams) {
//				return functions[functions.add(functionParams)];
//			}

			struct t_AddFunction {
				private:
				t_FunctionList &parent;

				public:
				void Absolute() {
					t_FunctionParams *newFunction = new t_FunctionParams(FUNCTION_ABSOLUTE);
//					newFunction->types. = {  };
					parent.add(newFunction);
				}

				void ClampAbove(float threshold=1.0f) {
					t_FunctionParams *newFunction = new t_FunctionParams(FUNCTION_CLAMP_ABOVE);
					newFunction->types.clamp_above = { threshold };
					parent.add(newFunction);
				}

				void ClampBelow(float threshold=0.0f) {
					t_FunctionParams *newFunction = new t_FunctionParams(FUNCTION_CLAMP_BELOW);
					newFunction->types.clamp_below = { threshold };
					parent.add(newFunction);
				}

				void FadeAbove(float threshold, float fadeRange, float maxValue=1.0f, bool clamp=true) {
					t_FunctionParams *newFunction = new t_FunctionParams(FUNCTION_FADE_ABOVE);
					newFunction->types.fade_above = { threshold, fadeRange, maxValue, clamp };
					parent.add(newFunction);
				}

				void FadeBelow(float threshold, float fadeRange, float maxValue=1.0f, bool clamp=true) {
					t_FunctionParams *newFunction = new t_FunctionParams(FUNCTION_FADE_BELOW);
					newFunction->types.fade_below = { threshold, fadeRange, maxValue, clamp };
					parent.add(newFunction);
				}

				void FadeParabola(float lowerThreshold, float upperThreshold, float inflectionPoint, float maxValue=1.0f, bool clamp=true) {
					t_FunctionParams *newFunction = new t_FunctionParams(FUNCTION_FADE_PARABOLA);
					newFunction->types.fade_parabola = { lowerThreshold, upperThreshold, inflectionPoint, maxValue, clamp };
					parent.add(newFunction);
				}

				void Offset(float value) {
					t_FunctionParams *newFunction = new t_FunctionParams(FUNCTION_OFFSET);
					newFunction->types.offset = { value };
					parent.add(newFunction);
				}

				void OneMinus() {
					t_FunctionParams *newFunction = new t_FunctionParams(FUNCTION_ONE_MINUS);
//					newFunction->types. = {  };
					parent.add(newFunction);
				}

				void Power(float value) {
					t_FunctionParams *newFunction = new t_FunctionParams(FUNCTION_POWER);
					newFunction->types.power = { value };
					parent.add(newFunction);
				}

				void Remap(float fNewMin, float fNewMax, float fMin=0.0f, float fMax=1.0f) {
					t_FunctionParams *newFunction = new t_FunctionParams(FUNCTION_REMAP);
					newFunction->types.remap = { fMin, fMax, fNewMin, fNewMax };
					parent.add(newFunction);
				}

				void RemapAbove(float threshold, float fNewMin, float fNewMax, float fMin=0.0f, float fMax=1.0f) {
					t_FunctionParams *newFunction = new t_FunctionParams(FUNCTION_REMAP_ABOVE);
					newFunction->types.remap_above = { threshold, fMin, fMax, fNewMin, fNewMax };
					parent.add(newFunction);
				}

				void RemapBelow(float threshold, float fNewMin, float fNewMax, float fMin=0.0f, float fMax=1.0f) {
					t_FunctionParams *newFunction = new t_FunctionParams(FUNCTION_REMAP_BELOW);
					newFunction->types.remap_below = { threshold, fMin, fMax, fNewMin, fNewMax };
					parent.add(newFunction);
				}

				void ReplaceAbove(float threshold, float value) {
					t_FunctionParams *newFunction = new t_FunctionParams(FUNCTION_REPLACE_ABOVE);
					newFunction->types.replace_above = { threshold, value };
					parent.add(newFunction);
				}

				void ReplaceBelow(float threshold, float value) {
					t_FunctionParams *newFunction = new t_FunctionParams(FUNCTION_REPLACE_BELOW);
					newFunction->types.replace_below = { threshold, value };
					parent.add(newFunction);
				}

				void Scale(float value) {
					t_FunctionParams *newFunction = new t_FunctionParams(FUNCTION_SCALE);
					newFunction->types.scale = { value };
					parent.add(newFunction);
				}

				t_AddFunction(t_FunctionList *p) : parent(*p) {  }
			};
			t_AddFunction AddFunction = t_AddFunction(&functions);


			eModes mode;

			t_BaseParams() {
				mode = MODE_ADD;
			}

			~t_BaseParams() {
				for (auto function : functions) delete function;
			}
		};

		struct t_NoneParams : virtual public t_BaseParams {
			t_NoneParams() {}
		};

//		struct t_SimplexParams : virtual public t_BaseParams {
//			t_SimplexParams() {
//			}
//		};

		struct t_PerlinParams : virtual public t_BaseParams {
			float frequency, lacunarity, persistence, seed;
			int octaves;
			noise::NoiseQuality quality;

			t_PerlinParams() {
				frequency			= 0.00025f;
				lacunarity			= 2.9f;
				persistence			= 0.33f;
				octaves				= 3;
				seed				= 0.0f;
				quality				= noise::QUALITY_STD;
			}
		};

		struct t_FractalParams : virtual public t_BaseParams {
			float frequency, amplitude, lacunarity, persistence;
			int octaves;
			unsigned seed;

			t_FractalParams() {
				frequency			= 0.00025f;
				amplitude			= 1.0f;
				lacunarity			= 2.9f;
				persistence			= 0.33f;
				octaves				= 3;
				seed				= 0;
			}
		};

		struct t_RidgedPerlinParams : virtual public t_BaseParams {
			float frequency,				// First octave frequency
				  lacunarity,				// 1.5 to 3.5
				  seed;
			noise::NoiseQuality quality;	// QUALITY_FAST, QUALITY_STD, QUALITY_BEST
			int octaves;					// 1 to noise::module::RIDGED_MAX_OCTAVE

			t_RidgedPerlinParams(/*int seed*/) {
				frequency	= 1.0f;
				lacunarity	= 1.5f;
				quality		= noise::QUALITY_STD;
				seed		= 0.0f;	// TODO: Implement as constructor after moved to global class
				octaves		= 3;
			}
		};

//		struct t_RidgedSimplexParams : public t_SimplexParams {
//			float threshold;
//			t_RidgedSimplexParams() {
//				threshold = 0.5f;
//			}
//		};

		struct t_VoronoiParams : virtual public t_BaseParams {
			float frequency,
				  displacement,
				  seed;				// TODO: Implement as constructor after moved to global class
			bool  bDistance;
			t_VoronoiParams() {
				frequency		= 1.0f;
				displacement	= 1.5f;
				seed			= 0.0f;	// TODO: Implement as constructor after moved to global class
				bDistance		= true;
			}
		};

		struct t_BillowParams : virtual public t_BaseParams {
			float frequency,				// First octave frequency
				  lacunarity,				// 1.5 to 3.5
				  persistence,				//
				  seed;

			noise::NoiseQuality quality;	// QUALITY_FAST, QUALITY_STD, QUALITY_BEST
			int octaves;					// 1 to noise::module::RIDGED_MAX_OCTAVE

			t_BillowParams(/*int seed*/) {
				frequency	= 1.0f;
				lacunarity	= 1.5f;
				persistence	= 1.0f;
				quality		= noise::QUALITY_STD;
				seed		= 0.0f;	// TODO: Implement as constructor after moved to global class
				octaves		= 3;
			}
		};

		// TODO: Smoothstep either as Simplex option or additional type
		// TODO: Cylinders
		// TODO: Turbulence
		// TODO: Fractal Brownian Motion (Built-in in SimplexNoise class as .fractal, simplex is currently actually using this)

		double applyMode(double src, double dst, eModes mode);

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		//	Noise Class
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

		enum eNoiseType { NOISE_NONE,
//						  NOISE_SIMPLEX,
						  NOISE_PERLIN,
						  NOISE_FRACTAL,
//						  NOISE_RIDGED_SIMPLEX,
						  NOISE_RIDGED_PERLIN,
						  NOISE_VORONOI,
						  NOISE_BILLOW,
		};

		using t_VariantNoise = std::pair<eNoiseType, int>;

		using t_None = t_VectorMap<t_NoneParams*>;
//		using t_Simplex = t_VectorMap<t_SimplexParams*>;
		using t_Perlin = t_VectorMap<t_PerlinParams*>;
		using t_Fractal = t_VectorMap<t_FractalParams*>;
//		using t_RidgedSimplex = t_VectorMap<t_RidgedSimplexParams*>;
		using t_RidgedPerlin = t_VectorMap<t_RidgedPerlinParams*>;
		using t_Voronoi = t_VectorMap<t_VoronoiParams*>;
		using t_Billow = t_VectorMap<t_BillowParams*>;

		class t_Noise {
			friend class Core::Sys::MapSys;
			friend class Core::Sys::t_MapInstance;
			friend class Core::Sys::t_MapBase;
			friend class Core::Sys::O2DSys;
			friend class Core::Sys::O3DSys;
			friend double getNoise(float x, float z, Core::Noise::t_Noise *noise);
			protected:
				Sys::Map::t_ChunkData *parent;
				t_Vector1T<t_None*> 			none;
//				t_Vector1T<t_Simplex*>			simplex;
				t_Vector1T<t_Perlin*>			perlin;
				t_Vector1T<t_Fractal*>			fractal;
//				t_Vector1T<t_RidgedSimplex*>	ridgedSimplex;
				t_Vector1T<t_RidgedPerlin*>		ridgedPerlin;
				t_Vector1T<t_Voronoi*>			voronoi;
				t_Vector1T<t_Billow*>			billow;

				t_VectorMap<t_VariantNoise> layers;

			public:
				void * operator[](std::string name);

				t_None &add(std::string name, t_None* noise);
//				t_Simplex &add(std::string name, t_Simplex* noise);
				t_Perlin &add(std::string name, t_Perlin* noise);
				t_Fractal &add(std::string name, t_Fractal* noise);
//				t_RidgedSimplex &add(std::string name, t_RidgedSimplex* noise);
				t_RidgedPerlin &add(std::string name, t_RidgedPerlin* noise);
				t_Voronoi &add(std::string name, t_Voronoi* noise);
				t_Billow &add(std::string name, t_Billow* noise);

				// Get a generator by layer name, but must know the correct type
				t_None& getNone(std::string name);
//				t_Simplex& getSimplex(std::string name);
				t_Perlin& getPerlin(std::string name);
				t_Fractal& getFractal(std::string name);
//				t_RidgedSimplex& getRidgedSimplex(std::string name);
				t_RidgedPerlin& getRidgedPerlin(std::string name);
				t_Voronoi& getVoronoi(std::string name);
				t_Billow& getBillow(std::string name);

				t_Noise(Sys::Map::t_ChunkData *p);
				~t_Noise();
		};

		extern double getNoise(float x, float z, Core::Noise::t_Noise *noise);

////		noise::module::Perlin genPerlin;
////		noise::module::RidgedMulti genRidged;
////		noise::module::Voronoi genVoronoi;
////		noise::module::Billow genBillow;
////		SimplexNoise genSimplex;
//		double getNoise(float x, float z, Core::Noise::t_Noise *noise)
////		double getNoise(	float x,
////							float z,
////							Core::Noise::t_Noise *noise,
////							noise::module::Perlin genPerlin,
////							noise::module::RidgedMulti genRidged,
////							noise::module::Voronoi genVoronoi,
////							noise::module::Billow genBillow,
////							SimplexNoise genSimplex,
////							std::minstd_rand0 rng1,
////							std::minstd_rand0 rng2,
////							std::minstd_rand0 rng3,
////							std::minstd_rand0 rng4	)
//		{
//			double dHeight = 0.0f;
//
//
//			for ( auto layer : noise->layers ) {
//				Core::Noise::eNoiseType type	= layer.first;
//				int index				= layer.second;
//
//				switch(type) {
////					case Core::Noise::NOISE_SIMPLEX:
////					{
////						for( auto const &param : *noise->simplex[index] ) {
////							double  e1 = 0.0f,
////									e2 = 0.0f;
////
//////							SimplexNoise simNoise1 = SimplexNoise( param->frequency, param->amplitude, param->lacunarity, param->persistance );
////							SimplevTexCoordsxNoise simNoise1 = SimplexNoise( 0.0001f, 1.0f, 1.0f, 1.0f );
//////							SimplexNoise simNoise1;
////							e1 = simNoise1.noise(x, z);
////							e2 = Core::Noise::applyFunctions(e1, dHeight, *param);
////							dHeight = Core::Noise::applyMode(e2, dHeight, param->mode);
////
//////							// Octaves
//////							// TODO: Fix octave implementation (octaves and frequency built in to getPerlin())
//////							float amplitudeTotal = 0.0f;
//////							for(int n=0; n<param->octaves(); n++) {
//////								e1 = param->octaveData[n].amplitude * genPerlin.GetValue(x, z, 0) / 2.0 + 0.5;
//////								amplitudeTotal += param->octaveData[n].amplitude;
//////							}
//////							e2 /= amplitudeTotal;
//////
//////							e2 = Core::Noise::applyFunctions(e1, dHeight, *param);
//////							dHeight = Core::Noise::applyMode(e2, dHeight, param->mode);
////						}
////						break;
////					}
//					case Core::Noise::NOISE_PERLIN:
//					{
//						// Layers
//						for( auto const &param : *noise->perlin[index] ) {
//
//							double  e1 = 0.0f,
//									e2 = 0.0f;
//
//							Core::Noise::rng1 = std::minstd_rand0(param->seed);
//							Core::Noise::genPerlin.SetSeed(Core::Noise::rng1());
//							genPerlin.SetFrequency(param->frequency);
//							genPerlin.SetLacunarity(param->lacunarity);
//							genPerlin.SetNoiseQuality(param->quality);
//							genPerlin.SetOctaveCount(param->octaves);
//							genPerlin.SetPersistence(param->persistence);
//
//							e1 = genPerlin.GetValue(x, z, 0);
//							e2 = Core::Noise::applyFunctions(e1, dHeight, *param);
//							dHeight = Core::Noise::applyMode(e2, dHeight, param->mode);
//						}
//						break;
//					}
//					case Core::Noise::NOISE_FRACTAL:
//					{
//						for( auto const &param : *noise->fractal[index] ) {
//							double e1 = 0.0f;
//							double e2 = 0.0f;
////							SimplexNoise simNoise1 = SimplexNoise( param->frequency, param->amplitude, param->lacunarity, param->persistance );
//
//							genSimplex.setAmplitude(param->amplitude);
//							genSimplex.setFrequency(param->frequency);
//							genSimplex.setLacunarity(param->lacunarity);
//							genSimplex.setPersiistence(param->persistence);
//							genSimplex.setSeed(param->seed);
////							e1 = genSimplex.fractal( param->octaves, x, z, dHeight);
//							e1 = genSimplex.fractal( param->octaves, x, z, 0);
//							//e1 = simNoise1.fractal( param->octaves, x, z, 0);
//							e2 = Core::Noise::applyFunctions(e1, dHeight, *param);
//							dHeight = Core::Noise::applyMode(e2, dHeight, param->mode);
//						}
//						break;
//					}
//
////					case Core::Noise::NOISE_RIDGED_SIMPLEX:
////					{
////						double nx = x/(noise->parent->chunk_size*2) - 0.5, ny = z/(noise->parent->chunk_size*2) - 0.5;
////						for( auto const &param : *noise->ridgedSimplex[index] ) {
////							double e1 = 0.0f;
////							double e2 = 0.0f;
////							double e3 = 0.0f;
////							SimplexNoise simNoise1 = SimplexNoise( param->frequency, param->amplitude, param->lacunarity, param->persistance );
//////							e1 = (param->threshold - abs(simNoise1.fractal( x, z, dHeight)));
//////							e1 = (param->threshold - abs(simNoise1.fractal( param->octaves, x, z, dHeight/20000.0f)));
//////							e1 = (param->threshold - abs(simNoise1.fractal( param->octaves, x, z)));
////							e1 = (param->threshold - abs(simNoise1.fractal( param->octaves, nx, ny)));
////
////							int sign = 1;
////							if(e1<0) sign = -1;
////							e2 = e1;
////							e3 += sign * ((std::pow(abs(e2), param->power)*param->scale));
////
////							if(param->funcHeightEnable) {
////								if(dHeight<(param->funcHeightLowerValue)) {
////									dHeight += e3 * fmax(fmin((dHeight/param->funcHeightLowerValue), 1.0f), 0.0f);
////								}
////								else if(dHeight>(param->funcHeightUpperValue)) {
////									dHeight += e3 * fmax(fmin((1.0f-(dHeight/(param->funcHeightUpperValue*2.0f))), 1.0f), 0.0f);
////								}
////								else dHeight += e3;
////							}
////							else dHeight += e3;
////
////						}
////						break;
////					}
//
//					case Core::Noise::NOISE_RIDGED_PERLIN:
//					{
//						// Layers
//						for( auto const &param : *noise->ridgedPerlin[index] ) {
//
//							double  e1 = 0.0f,
//									e2 = 0.0f,
//									e3 = 0.0f;
//
//							rng2 = std::minstd_rand0(param->seed);
//							genRidged.SetSeed(rng2());
//							genRidged.SetFrequency(param->frequency);
//							genRidged.SetLacunarity(param->lacunarity);
//							genRidged.SetNoiseQuality(param->quality);
//							genRidged.SetOctaveCount(param->octaves);
//
//							e1 = genRidged.GetValue(x, z, 0);
//							e2 = Core::Noise::applyFunctions(e1, dHeight, *param);
//							dHeight = Core::Noise::applyMode(e2, dHeight, param->mode);
//						}
//						break;
//					}
//
//					case Core::Noise::NOISE_VORONOI:
//					{
//						// Layers
//						for( auto const &param : *noise->voronoi[index] ) {
//
//							double  e1 = 0.0f,
//									e2 = 0.0f,
//									e3 = 0.0f;
//
//							rng3 = std::minstd_rand0(param->seed);
//							genVoronoi.SetSeed(rng3());
//							genVoronoi.SetFrequency(param->frequency);
//							genVoronoi.SetDisplacement(param->displacement);
//							genVoronoi.EnableDistance(param->bDistance);
//
//							e1 = genVoronoi.GetValue(x, z, 0);
//							e2 = Core::Noise::applyFunctions(e1, dHeight, *param);
//							dHeight = Core::Noise::applyMode(e2, dHeight, param->mode);
//
//						}
//						break;
//					}
//
//					case Core::Noise::NOISE_BILLOW:
//					{
//						// Layers
//						for( auto const &param : *noise->billow[index] ) {
//
//							double  e1 = 0.0f,
//									e2 = 0.0f,
//									e3 = 0.0f;
//
//							rng4 = std::minstd_rand0(param->seed);
//							genBillow.SetSeed(rng4());
//							genBillow.SetFrequency(param->frequency);
//							genBillow.SetLacunarity(param->lacunarity);
//							genBillow.SetPersistence(param->persistence);
//							genBillow.SetNoiseQuality(param->quality);
//							genBillow.SetOctaveCount(param->octaves);
//
//							e1 = genBillow.GetValue(x, z, 0);
//							e2 = Core::Noise::applyFunctions(e1, dHeight, *param);
//							dHeight = Core::Noise::applyMode(e2, dHeight, param->mode);
//						}
//						break;
//					}
//
//					default:	// NOISE_NONE
//						debug.log("Load NONE");
//				}
//
//			}
//
//			return dHeight;
//		}



	} /* namespace Noise */
} /* namespace Core */

#endif /* HEADERS_CORE_NOISE_H_ */









//
//
//
//// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//			// TODO: Add Functions (Should be part of noise class)
//
//			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//			// TODO: Noise should be in its own global class
//
//			struct t_NoneParams {
//				t_NoneParams() {}
//			};
//
//			struct t_SimplexParams {
////				t_SimplexFunctions functions;
////				void addFunction(eFunctionSource src, eFunctionTargetSimplex dst, float val) {
////					functions.add(t_SimplexFunction(src, dst, val));
////				}
////				float (*frequencyFunction)(float src);
//
//				bool funcHeightEnable;
//				float funcHeightUpperValue;
//				float funcHeightLowerValue;
//
//				float frequency, amplitude, lacunarity, persistance;
//				int octaves;
//				float power;
//				float scale;
//				float offset;
//
//				t_SimplexParams() {
//					frequency			= 0.00025f;
//					amplitude			= 1.0f;
//					lacunarity			= 2.9f;
//					persistance			= 0.33f;
//					power				= 1.0f;
//					scale				= 875.0f;
//					octaves				= 3;
//					offset				= 0.0f;
//
//					funcHeightEnable		= false;
//					funcHeightUpperValue	= 8000.0f;
//					funcHeightLowerValue	= 2000.0f;
//				}
//			};
//
//			struct t_PerlinParams {
//
//				struct t_PerlinOctaves {
//					float frequency_x;
//					float frequency_y;
//					float amplitude;
//					t_PerlinOctaves(float a, float f) {
//						amplitude = a;
//						frequency_x = f;
//						frequency_y = f;
//					}
//					t_PerlinOctaves(float a, float fx, float fy) {
//						amplitude = a;
//						frequency_x = fx;
//						frequency_y = fy;
//					}
//				};
//				t_Vector1T<t_PerlinOctaves> octaveData;
//
//				void addOctave(float amplitude, float frequency) {
//					octaveData.add(t_PerlinOctaves(amplitude, frequency));
//				}
//				void addOctave(float amplitude, float frequency_x, float frequency_y) {
//					octaveData.add(t_PerlinOctaves(amplitude, frequency_x, frequency_y));
//				}
//				int octaves() { return octaveData.size(); };
//				float power;
//				float scale;
//				t_PerlinParams() {
//					power		= 1.0f;
//					scale		= 500.0f;
//				}
//			};
//
//			struct t_FractalParams {
//				float frequency,
//					  lacunarity,
//					  multiplier,
//					  layers,
//					  scale,
//					  power;
//				t_FractalParams() {
//					frequency	= 0.00025f; //0.0006; //0.000076; //0.00025f;
//					lacunarity	= 2.9f; //6.553f; //6.004; //6.75325; //8.0f;
//					multiplier	= 0.33f; //0.139f; //0.150; //0.175; //0.175f;
//					power		= 1.0f;
//					scale		= 875.0f; //500.0f; //275.0f; //1750; //2500;
//					layers		= 3;
//				}
//			};
//
//			struct t_RidgedPerlinParams {
//
//				bool bRiver;
//
//				bool funcHeightUpperEnable;
//				bool funcHeightLowerEnable;
//				float funcHeightUpperValue;
//				float funcHeightLowerValue;
//
//				float frequency,				// First octave frequency
//					  lacunarity,				// 1.5 to 3.5
//					  seed,						// TODO: Implement as constructor after moved to global class
//					  power,
//					  scale,
//					  offset;
//				noise::NoiseQuality quality;	// QUALITY_FAST, QUALITY_STD, QUALITY_BEST
//				int octaves;					// 1 to noise::module::RIDGED_MAX_OCTAVE
//
//				t_RidgedPerlinParams(/*int seed*/) {
//					bRiver = false;
//					frequency	= 1.0f;
//					lacunarity	= 1.5f;
//					quality		= noise::QUALITY_STD;
//					seed		= 0.0f;	// TODO: Implement as constructor after moved to global class
//					octaves		= 3;
//					power		= 1.0f;
//					scale		= 1.0f;
//					offset		= 0.0f;
//
//					funcHeightUpperEnable	= false;
//					funcHeightLowerEnable	= false;
//					funcHeightUpperValue	= 8000.0f;
//					funcHeightLowerValue	= 2000.0f;
//				}
//			};
//
//			struct t_RidgedSimplexParams : public t_SimplexParams {
//				float threshold;
//				t_RidgedSimplexParams() {
//					threshold = 0.5f;
//				}
//			};
//
//			struct t_VoronoiParams {
//				float frequency,
//					  displacement,
//					  scale,
//					  power,
//					  seed;				// TODO: Implement as constructor after moved to global class
//				bool  bDistance;
//				t_VoronoiParams() {
//					frequency		= 1.0f;
//					displacement	= 1.5f;
//					power			= 1.0f;
//					scale			= 1.0f;
//					seed			= 0.0f;	// TODO: Implement as constructor after moved to global class
//					bDistance		= true;
//				}
//			};
//
//			struct t_BillowParams {
//				float frequency,				// First octave frequency
//					  lacunarity,				// 1.5 to 3.5
//					  persistence,				//
//					  seed,						// TODO: Implement as constructor after moved to global class
//					  power,
//					  scale,
//					  offset;					// TODO: Add to all layers
//
//				bool funcHeightEnable;
//				float funcHeightUpperValue;
//				float funcHeightLowerValue;
//
//				noise::NoiseQuality quality;	// QUALITY_FAST, QUALITY_STD, QUALITY_BEST
//				int octaves;					// 1 to noise::module::RIDGED_MAX_OCTAVE
//
//				t_BillowParams(/*int seed*/) {
//					frequency	= 1.0f;
//					lacunarity	= 1.5f;
//					persistence	= 1.0f;
//					quality		= noise::QUALITY_STD;
//					seed		= 0.0f;	// TODO: Implement as constructor after moved to global class
//					octaves		= 3;
//					power		= 1.0f;
//					scale		= 1.0f;
//					offset		= 0.0f;
//
//					funcHeightEnable		= false;
//					funcHeightUpperValue	= 8000.0f;
//					funcHeightLowerValue	= 2000.0f;
//				}
//			};
//
//			// TODO: Smoothstep either as Simplex option or additional type
//			// TODO: Billow
//			// TODO: Cylinders
//			// TODO: Turbulence
//			// TODO: Fractal Brownian Motion (Built-in in SimplexNoise class as .fractal, simplex is currently actually using this)
//
//			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//			enum eNoiseType { NOISE_NONE,
//							  NOISE_SIMPLEX,
//							  NOISE_PERLIN,
//							  NOISE_FRACTAL,
//							  NOISE_RIDGED_SIMPLEX,
//							  NOISE_RIDGED_PERLIN,
//							  NOISE_VORONOI,
//							  NOISE_BILLOW,
//			};
//
//			using t_VariantNoise = std::pair<eNoiseType, int>;
//
//			using t_None = t_VectorMap<t_NoneParams*>;
//			using t_Simplex = t_VectorMap<t_SimplexParams*>;
//			using t_Perlin = t_VectorMap<t_PerlinParams*>;
//			using t_Fractal = t_VectorMap<t_FractalParams*>;
//			using t_RidgedSimplex = t_VectorMap<t_RidgedSimplexParams*>;
//			using t_RidgedPerlin = t_VectorMap<t_RidgedPerlinParams*>;
//			using t_Voronoi = t_VectorMap<t_VoronoiParams*>;
//			using t_Billow = t_VectorMap<t_BillowParams*>;
//
//
//			// TODO: Delete pointers
//			struct t_Noise {
//				friend MapSys;
//				friend class Core::Sys::t_MapInstance;
//				protected:
//					t_ChunkData *parent;
//					t_Vector1T<Map::t_None*> 			none;
//					t_Vector1T<Map::t_Simplex*>			simplex;
//					t_Vector1T<Map::t_Perlin*>			perlin;
//					t_Vector1T<Map::t_Fractal*>			fractal;
//					t_Vector1T<Map::t_RidgedSimplex*>	ridgedSimplex;
//					t_Vector1T<Map::t_RidgedPerlin*>		ridgedPerlin;
//					t_Vector1T<Map::t_Voronoi*>			voronoi;
//					t_Vector1T<Map::t_Billow*>			billow;
//
//					t_VectorMap<t_VariantNoise> layers;
//
//				public:
//
//					void * operator[](std::string name) {
//						switch(layers[name].first) {
//							case Map::NOISE_NONE:
//								return &none;
//								break;
//							case Map::NOISE_SIMPLEX:
//								return &simplex;
//								break;
//							case Map::NOISE_PERLIN:
//								return &perlin;
//								break;
//							case Map::NOISE_FRACTAL:
//								return &fractal;
//								break;
//							case Map::NOISE_RIDGED_SIMPLEX:
//								return &ridgedSimplex;
//								break;
//							case Map::NOISE_RIDGED_PERLIN:
//								return &ridgedPerlin;
//								break;
//							case Map::NOISE_VORONOI:
//								return &voronoi;
//								break;
//							case Map::NOISE_BILLOW:
//								return &billow;
//								break;
//						}
//						return nullptr;
//					}
//
//					Map::t_None &add(std::string name, Map::t_None* noise) {
//						int id = none.add(noise);
//						layers.add(name, std::make_pair(NOISE_NONE, id));
//						return *none[id];
//					}
//
//					Map::t_Simplex &add(std::string name, Map::t_Simplex* noise) {
//						int id = simplex.add(noise);
//						layers.add(name, std::make_pair(NOISE_SIMPLEX, id));
//						return *simplex[id];
//					}
//
//					Map::t_Perlin &add(std::string name, Map::t_Perlin* noise) {
//						int id = perlin.add(noise);
//						layers.add(name, std::make_pair(NOISE_PERLIN, id));
//						return *perlin[id];
//					}
//
//					Map::t_Fractal &add(std::string name, Map::t_Fractal* noise) {
//						int id = fractal.add(noise);
//						layers.add(name, std::make_pair(NOISE_FRACTAL, id));
//						return *fractal[id];
//					}
//
//					Map::t_RidgedSimplex &add(std::string name, Map::t_RidgedSimplex* noise) {
//						int id = ridgedSimplex.add(noise);
//						layers.add(name, std::make_pair(NOISE_RIDGED_SIMPLEX, id));
//						return *ridgedSimplex[id];
//					}
//
//					Map::t_RidgedPerlin &add(std::string name, Map::t_RidgedPerlin* noise) {
//						int id = ridgedPerlin.add(noise);
//						layers.add(name, std::make_pair(NOISE_RIDGED_PERLIN, id));
//						return *ridgedPerlin[id];
//					}
//
//					Map::t_Voronoi &add(std::string name, Map::t_Voronoi* noise) {
//						int id = voronoi.add(noise);
//						layers.add(name, std::make_pair(NOISE_VORONOI, id));
//						return *voronoi[id];
//					}
//
//					Map::t_Billow &add(std::string name, Map::t_Billow* noise) {
//						int id = billow.add(noise);
//						layers.add(name, std::make_pair(NOISE_BILLOW, id));
//						return *billow[id];
//					}
//
//
//
//
//					// Get a generator by layer name, but must know the correct type
//					Map::t_None& getNone(std::string name) {
//						return *none[layers[name].second];
//					}
//
//					Map::t_Simplex& getSimplex(std::string name) {
//						return *simplex[layers[name].second];
//					}
//
//					Map::t_Perlin& getPerlin(std::string name) {
//						return *perlin[layers[name].second];
//					}
//
//					Map::t_Fractal& getFractal(std::string name) {
//						return *fractal[layers[name].second];
//					}
//
//					Map::t_RidgedSimplex& getRidgedSimplex(std::string name) {
//						return *ridgedSimplex[layers[name].second];
//					}
//
//					Map::t_RidgedPerlin& getRidgedPerlin(std::string name) {
//						return *ridgedPerlin[layers[name].second];
//					}
//
//					Map::t_Voronoi& getVoronoi(std::string name) {
//						return *voronoi[layers[name].second];
//					}
//
//					Map::t_Billow& getBillow(std::string name) {
//						return *billow[layers[name].second];
//					}
//
//				t_Noise(t_ChunkData *p) { parent = p; }
//				~t_Noise() {
//
//					for (auto item : none )				delete item;
//					for (auto item : simplex )			delete item;
//					for (auto item : perlin )			delete item;
//					for (auto item : fractal )			delete item;
//					for (auto item : ridgedSimplex )	delete item;
//					for (auto item : ridgedPerlin )		delete item;
//					for (auto item : voronoi )			delete item;
//					for (auto item : billow )			delete item;
//				}
//			};
//
//
//			// TODO: Smoothstep either as Simplex option or additional type
////			struct t_Ridged {
////				t_ChunkData *parent;
////				t_VectorMap<t_RidgedParams> params;
////
////				t_Ridged(t_ChunkData *p) { parent = p; }
////			};
