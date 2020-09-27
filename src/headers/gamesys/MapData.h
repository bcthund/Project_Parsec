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

				Data() {
					numVerts = 0;
					numFaces = 0;
					numDrawVerts = 0;

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

			// TODO: Add enum to have layers affect one another
			// Lower layers can affect upper layers only
			// I.E. The base layer determines a height, that height can then be used to control a parameter for the second layer

			// Parameter to modify
			//  - Position is applied based on current x, z coordinates
			//  - Height is applied using the current stacked value of all previous layers
			enum eSimplexLayerFunction {
				POSITION_FREQUENCY,
				POSITION_AMPLITUDE,
				POSITION_LACUNARITY,
				POSITION_PERSISTANCE,
				POSITION_POWER,
				POSITION_SCALE,
				POSITION_OCTAVES,
				HEIGHT_FREQUENCY,
				HEIGHT_AMPLITUDE,
				HEIGHT_LACUNARITY,
				HEIGHT_PERSISTANCE,
				HEIGHT_POWER,
				HEIGHT_SCALE,
				HEIGHT_OCTAVES
			};

			// One of the choices from eSimplexLayerFunction
			// and a weight value as a percentage to modify the
			// base value by.
			struct t_SimplexFunction {
				eSimplexLayerFunction eType;
				float fMin;
				float fMax;
				float fWeight;
			};

			struct t_SimplexParams {
				float frequency, amplitude, lacunarity, persistance;
				int octaves;
				float power;
				float scale;

				// TODO: Implement
//				t_SimplexParams<t_SimplexFunction> function;

				t_SimplexParams() {
					frequency	= 0.00025f; //0.0006; //0.000076; //0.00025f;
					amplitude	= 1.0f;
					lacunarity	= 2.9f; //6.553f; //6.004; //6.75325; //8.0f;
					persistance	= 0.33f; //0.139f; //0.150; //0.175; //0.175f;
					power		= 1.0f;
					scale		= 875.0f; //500.0f; //275.0f; //1750; //2500;
					octaves		= 3;
				}
			};

			struct t_PerlinParams {
				t_PerlinParams() {}
			};

			struct t_FractalParams {
				t_FractalParams() {}
			};

			struct t_RidgedParams {
				t_RidgedParams() {}
			};

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

					set_iMax();
				}
			};

			// TODO: Smoothstep either as Simplex option or additional type
			struct t_Simplex {
				t_ChunkData *parent;
				t_VectorMap<t_SimplexParams> params;

				t_Simplex(t_ChunkData *p) { parent = p; }
			};

			struct t_Perlin {
				t_ChunkData *parent;
				t_VectorMap<t_PerlinParams> params;

				t_Perlin(t_ChunkData *p) { parent = p; }
			};

			struct t_Fractal {
				t_ChunkData *parent;
				t_VectorMap<t_FractalParams> params;

				t_Fractal(t_ChunkData *p) { parent = p; }
			};

			struct t_Ridged {
				t_ChunkData *parent;
				t_VectorMap<t_RidgedParams> params;

				t_Ridged(t_ChunkData *p) { parent = p; }
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
