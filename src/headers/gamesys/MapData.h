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

























































		} /* namespace Map */
	} /* namespace Sys */
} /* namespace Core */

#endif /* HEADERS_GAMESYS_MAPDATA_H_ */
