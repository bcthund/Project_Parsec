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

			struct Simplex {
				bool bEnable;	// Enable these debug variables
				int res;
				float tex_scale;
				int terrain_size;
				float terrain_height_offset;
				float delta;

				struct t_NoiseParams {
					float frequency, amplitude, lacunarity, persistance;
					int octaves;
					float power;
					float scale;

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

//				t_UMap<std::string, t_NoiseParams> params;
				t_VectorMap<t_NoiseParams> params;

				Simplex() {
					bEnable		= true;

//					res = 256;
					res = 32;
					tex_scale = 128.0f;
//					terrain_size = 16384;
					terrain_size = 1024;
					terrain_height_offset = 0.0f;

					delta		= 32.0f;

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
