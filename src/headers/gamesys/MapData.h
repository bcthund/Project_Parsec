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

			struct t_NoiseParams {
				float frequency, amplitude, lacunarity, persistance;
				int octaves;
				float power;
				float scale;

				// TODO: Implement
				t_Vector1T<t_SimplexFunction> function;

				t_NoiseParams() {
					frequency	= 0.00025f; //0.0006; //0.000076; //0.00025f;
					amplitude	= 1.0f;
					lacunarity	= 2.9f; //6.553f; //6.004; //6.75325; //8.0f;
					persistance	= 0.33f; //0.139f; //0.150; //0.175; //0.175f;
					power		= 1.0f;
					scale		= 875.0f; //500.0f; //275.0f; //1750; //2500;
					octaves		= 3;
				}
			};

			struct Simplex {
				bool bEnable;	// Enable these debug variables
				int res;
				float tex_scale;
				int terrain_size;
				float terrain_height_offset;
				float delta;
				int iMax;
				int iViewDistance;

//				t_UMap<std::string, t_NoiseParams> params;
				t_VectorMap<t_NoiseParams> params;

				void set_iMax() {
					iMax = iViewDistance/terrain_size;
				}

				Simplex() {
					bEnable		= true;

//					res = 256;
					res = 8;
					tex_scale = 128.0f;
//					terrain_size = 16384;
					terrain_size = 1024;
					terrain_height_offset = 0.0f;

					delta		= 32.0f;

					set_iMax();

					//params.add(t_NoiseParams());
//					frequency	= 0.00025f; //0.0006; //0.000076; //0.00025f;
//					amplitude	= 1.0f;
//					lacunarity	= 2.9f; //6.553f; //6.004; //6.75325; //8.0f;
//					persistance	= 0.33f; //0.139f; //0.150; //0.175; //0.175f;
//					power		= 1.0f;
//					scale		= 875.0f; //500.0f; //275.0f; //1750; //2500;
//					octaves		= 3;
				}
			};


		} /* namespace Map */
	} /* namespace Sys */
} /* namespace Core */

#endif /* HEADERS_GAMESYS_MAPDATA_H_ */
