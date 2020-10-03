/*
 * MapData.h
 *
 *  Created on: Sep 20, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_MAPDATA_H_
#define HEADERS_GAMESYS_MAPDATA_H_

#include "../core/core_functions.h"
#include "../core/vao.h"
#include "../core/texture.h"

namespace Core {
	namespace Sys {

		// Forward declare
		class t_MapInstance;

		namespace Map {

			struct Data {
				Data3f * vVerts;
				Data3f * vNorms;
				Data2f * vCoords;
				GLuint * vIndex;
				Vector3ui * vGroups;
				long numDrawVerts;
				long numVerts;
				long numFaces;
				VAO vao;
				float lowestHeight;

				Data() {
					numVerts = 0;
					numFaces = 0;
					numDrawVerts = 0;
					lowestHeight = 9999.0f;

					vVerts  = nullptr;
					vNorms  = nullptr;
					vCoords = nullptr;
					vIndex  = nullptr;
					vGroups = nullptr;
				}

				~Data() {
					delete[] vVerts;
					delete[] vNorms;
					delete[] vCoords;
					delete[] vIndex;
					delete[] vGroups;
				}

			};

			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

			// There only needs to be one of these per WorldMap
			// Pointer created by noise type so multiple definition CAN exist (water with a larger chunk size)
			struct t_ChunkData {
				bool bEnable;	// Enable these debug variables
				int chunk_resolution;
				float tex_scale;
				int chunk_size;
				float chunk_height_offset;
				float delta;
				int iMax;
				int iViewDistance;
//				float sea_level;

				void set_iMax() {
					iMax = iViewDistance/chunk_size;
				}

				t_ChunkData() {
					bEnable		= true;
					chunk_resolution = 16;
					tex_scale = 128.0f;
					chunk_size = 1024;
					chunk_height_offset = 0.0f;
					delta		= 32.0f;
//					sea_level	= -500.0f;

					set_iMax();
				}
			};

			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

			// TODO: Add Functions (Should be part of noise class)

			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

			// TODO: Noise should be in its own global class

			struct t_NoneParams {
				t_NoneParams() {}
			};

			struct t_SimplexParams {
//				t_SimplexFunctions functions;
//				void addFunction(eFunctionSource src, eFunctionTargetSimplex dst, float val) {
//					functions.add(t_SimplexFunction(src, dst, val));
//				}
//				float (*frequencyFunction)(float src);

				bool funcHeightEnable;
				float funcHeightUpperValue;
				float funcHeightLowerValue;

				float frequency, amplitude, lacunarity, persistance;
				int octaves;
				float power;
				float scale;
				float offset;

				t_SimplexParams() {
					frequency			= 0.00025f;
					amplitude			= 1.0f;
					lacunarity			= 2.9f;
					persistance			= 0.33f;
					power				= 1.0f;
					scale				= 875.0f;
					octaves				= 3;
					offset				= 0.0f;

					funcHeightEnable		= false;
					funcHeightUpperValue	= 8000.0f;
					funcHeightLowerValue	= 2000.0f;
				}
			};

			struct t_PerlinParams {

				struct t_PerlinOctaves {
					float frequency_x;
					float frequency_y;
					float amplitude;
					t_PerlinOctaves(float a, float f) {
						amplitude = a;
						frequency_x = f;
						frequency_y = f;
					}
					t_PerlinOctaves(float a, float fx, float fy) {
						amplitude = a;
						frequency_x = fx;
						frequency_y = fy;
					}
				};
				t_Vector1T<t_PerlinOctaves> octaveData;

				void addOctave(float amplitude, float frequency) {
					octaveData.add(t_PerlinOctaves(amplitude, frequency));
				}
				void addOctave(float amplitude, float frequency_x, float frequency_y) {
					octaveData.add(t_PerlinOctaves(amplitude, frequency_x, frequency_y));
				}
				int octaves() { return octaveData.size(); };
				float power;
				float scale;
				t_PerlinParams() {
					power		= 1.0f;
					scale		= 500.0f;
				}
			};

			struct t_FractalParams {
				float frequency,
					  lacunarity,
					  multiplier,
					  layers,
					  scale,
					  power;
				t_FractalParams() {
					frequency	= 0.00025f; //0.0006; //0.000076; //0.00025f;
					lacunarity	= 2.9f; //6.553f; //6.004; //6.75325; //8.0f;
					multiplier	= 0.33f; //0.139f; //0.150; //0.175; //0.175f;
					power		= 1.0f;
					scale		= 875.0f; //500.0f; //275.0f; //1750; //2500;
					layers		= 3;
				}
			};

			struct t_RidgedPerlinParams {

				bool bRiver;

				bool funcHeightUpperEnable;
				bool funcHeightLowerEnable;
				float funcHeightUpperValue;
				float funcHeightLowerValue;

				float frequency,				// First octave frequency
					  lacunarity,				// 1.5 to 3.5
					  seed,						// TODO: Implement as constructor after moved to global class
					  power,
					  scale,
					  offset;
				noise::NoiseQuality quality;	// QUALITY_FAST, QUALITY_STD, QUALITY_BEST
				int octaves;					// 1 to noise::module::RIDGED_MAX_OCTAVE

				t_RidgedPerlinParams(/*int seed*/) {
					bRiver = false;
					frequency	= 1.0f;
					lacunarity	= 1.5f;
					quality		= noise::QUALITY_STD;
					seed		= 0.0f;	// TODO: Implement as constructor after moved to global class
					octaves		= 3;
					power		= 1.0f;
					scale		= 1.0f;
					offset		= 0.0f;

					funcHeightUpperEnable	= false;
					funcHeightLowerEnable	= false;
					funcHeightUpperValue	= 8000.0f;
					funcHeightLowerValue	= 2000.0f;
				}
			};

			struct t_RidgedSimplexParams : public t_SimplexParams {
				float threshold;
				t_RidgedSimplexParams() {
					threshold = 0.5f;
				}
			};

			struct t_VoronoiParams {
				float frequency,
					  displacement,
					  scale,
					  power,
					  seed;				// TODO: Implement as constructor after moved to global class
				bool  bDistance;
				t_VoronoiParams() {
					frequency		= 1.0f;
					displacement	= 1.5f;
					power			= 1.0f;
					scale			= 1.0f;
					seed			= 0.0f;	// TODO: Implement as constructor after moved to global class
					bDistance		= true;
				}
			};

			struct t_BillowParams {
				float frequency,				// First octave frequency
					  lacunarity,				// 1.5 to 3.5
					  persistence,				//
					  seed,						// TODO: Implement as constructor after moved to global class
					  power,
					  scale,
					  offset;					// TODO: Add to all layers

				bool funcHeightEnable;
				float funcHeightUpperValue;
				float funcHeightLowerValue;

				noise::NoiseQuality quality;	// QUALITY_FAST, QUALITY_STD, QUALITY_BEST
				int octaves;					// 1 to noise::module::RIDGED_MAX_OCTAVE

				t_BillowParams(/*int seed*/) {
					frequency	= 1.0f;
					lacunarity	= 1.5f;
					persistence	= 1.0f;
					quality		= noise::QUALITY_STD;
					seed		= 0.0f;	// TODO: Implement as constructor after moved to global class
					octaves		= 3;
					power		= 1.0f;
					scale		= 1.0f;
					offset		= 0.0f;

					funcHeightEnable		= false;
					funcHeightUpperValue	= 8000.0f;
					funcHeightLowerValue	= 2000.0f;
				}
			};

			// TODO: Smoothstep either as Simplex option or additional type
			// TODO: Billow
			// TODO: Cylinders
			// TODO: Turbulence
			// TODO: Fractal Brownian Motion (Built-in in SimplexNoise class as .fractal, simplex is currently actually using this)

			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

			enum eNoiseType { NOISE_NONE,
							  NOISE_SIMPLEX,
							  NOISE_PERLIN,
							  NOISE_FRACTAL,
							  NOISE_RIDGED_SIMPLEX,
							  NOISE_RIDGED_PERLIN,
							  NOISE_VORONOI,
							  NOISE_BILLOW,
			};

			using t_NewVariantNoise = std::pair<eNoiseType, int>;

			using t_NewNone = t_VectorMap<t_NoneParams*>;
			using t_NewSimplex = t_VectorMap<t_SimplexParams*>;
			using t_NewPerlin = t_VectorMap<t_PerlinParams*>;
			using t_NewFractal = t_VectorMap<t_FractalParams*>;
			using t_NewRidgedSimplex = t_VectorMap<t_RidgedSimplexParams*>;
			using t_NewRidgedPerlin = t_VectorMap<t_RidgedPerlinParams*>;
			using t_NewVoronoi = t_VectorMap<t_VoronoiParams*>;
			using t_NewBillow = t_VectorMap<t_BillowParams*>;


			// TODO: Delete pointers
			struct t_Noise {
				friend MapSys;
				friend class Core::Sys::t_MapInstance;
				protected:
					t_ChunkData *parent;
					t_Vector1T<Map::t_NewNone*> 			none;
					t_Vector1T<Map::t_NewSimplex*>			simplex;
					t_Vector1T<Map::t_NewPerlin*>			perlin;
					t_Vector1T<Map::t_NewFractal*>			fractal;
					t_Vector1T<Map::t_NewRidgedSimplex*>	ridgedSimplex;
					t_Vector1T<Map::t_NewRidgedPerlin*>		ridgedPerlin;
					t_Vector1T<Map::t_NewVoronoi*>			voronoi;
					t_Vector1T<Map::t_NewBillow*>			billow;

					t_VectorMap<t_NewVariantNoise> layers;

				public:

					void * operator[](std::string name) {
						switch(layers[name].first) {
							case Map::NOISE_NONE:
								return &none;
								break;
							case Map::NOISE_SIMPLEX:
								return &simplex;
								break;
							case Map::NOISE_PERLIN:
								return &perlin;
								break;
							case Map::NOISE_FRACTAL:
								return &fractal;
								break;
							case Map::NOISE_RIDGED_SIMPLEX:
								return &ridgedSimplex;
								break;
							case Map::NOISE_RIDGED_PERLIN:
								return &ridgedPerlin;
								break;
							case Map::NOISE_VORONOI:
								return &voronoi;
								break;
							case Map::NOISE_BILLOW:
								return &billow;
								break;
						}
						return nullptr;
					}

					Map::t_NewNone &add(std::string name, Map::t_NewNone* noise) {
						int id = none.add(noise);
						layers.add(name, std::make_pair(NOISE_NONE, id));
						return *none[id];
					}

					Map::t_NewSimplex &add(std::string name, Map::t_NewSimplex* noise) {
						int id = simplex.add(noise);
						layers.add(name, std::make_pair(NOISE_SIMPLEX, id));
						return *simplex[id];
					}

					Map::t_NewPerlin &add(std::string name, Map::t_NewPerlin* noise) {
						int id = perlin.add(noise);
						layers.add(name, std::make_pair(NOISE_PERLIN, id));
						return *perlin[id];
					}

					Map::t_NewFractal &add(std::string name, Map::t_NewFractal* noise) {
						int id = fractal.add(noise);
						layers.add(name, std::make_pair(NOISE_FRACTAL, id));
						return *fractal[id];
					}

					Map::t_NewRidgedSimplex &add(std::string name, Map::t_NewRidgedSimplex* noise) {
						int id = ridgedSimplex.add(noise);
						layers.add(name, std::make_pair(NOISE_RIDGED_SIMPLEX, id));
						return *ridgedSimplex[id];
					}

					Map::t_NewRidgedPerlin &add(std::string name, Map::t_NewRidgedPerlin* noise) {
						int id = ridgedPerlin.add(noise);
						layers.add(name, std::make_pair(NOISE_RIDGED_PERLIN, id));
						return *ridgedPerlin[id];
					}

					Map::t_NewVoronoi &add(std::string name, Map::t_NewVoronoi* noise) {
						int id = voronoi.add(noise);
						layers.add(name, std::make_pair(NOISE_VORONOI, id));
						return *voronoi[id];
					}

					Map::t_NewBillow &add(std::string name, Map::t_NewBillow* noise) {
						int id = billow.add(noise);
						layers.add(name, std::make_pair(NOISE_BILLOW, id));
						return *billow[id];
					}




					// Get a generator by layer name, but must know the correct type
					Map::t_NewNone& getNone(std::string name) {
						return *none[layers[name].second];
					}

					Map::t_NewSimplex& getSimplex(std::string name) {
						return *simplex[layers[name].second];
					}

					Map::t_NewPerlin& getPerlin(std::string name) {
						return *perlin[layers[name].second];
					}

					Map::t_NewFractal& getFractal(std::string name) {
						return *fractal[layers[name].second];
					}

					Map::t_NewRidgedSimplex& getRidgedSimplex(std::string name) {
						return *ridgedSimplex[layers[name].second];
					}

					Map::t_NewRidgedPerlin& getRidgedPerlin(std::string name) {
						return *ridgedPerlin[layers[name].second];
					}

					Map::t_NewVoronoi& getVoronoi(std::string name) {
						return *voronoi[layers[name].second];
					}

					Map::t_NewBillow& getBillow(std::string name) {
						return *billow[layers[name].second];
					}

				t_Noise(t_ChunkData *p) { parent = p; }
				~t_Noise() {

					for (auto item : none )				delete item;
					for (auto item : simplex )			delete item;
					for (auto item : perlin )			delete item;
					for (auto item : fractal )			delete item;
					for (auto item : ridgedSimplex )	delete item;
					for (auto item : ridgedPerlin )		delete item;
					for (auto item : voronoi )			delete item;
					for (auto item : billow )			delete item;
				}
			};


			// TODO: Smoothstep either as Simplex option or additional type
//			struct t_Ridged {
//				t_ChunkData *parent;
//				t_VectorMap<t_RidgedParams> params;
//
//				t_Ridged(t_ChunkData *p) { parent = p; }
//			};























































		} /* namespace Map */
	} /* namespace Sys */
} /* namespace Core */

#endif /* HEADERS_GAMESYS_MAPDATA_H_ */
