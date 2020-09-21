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

	struct MapData {
		Data3f * vVerts;
		Data3f * vNorms;
		Data2f * vCoords;
		GLuint * vIndex;
		Vector3ui * vGroups;
		long numDrawVerts;
		long numVerts;
		long numFaces;
		VAO vao;

		MapData() {
			numVerts = 0;
			numFaces = 0;
			numDrawVerts = 0;

			vVerts  = nullptr;
			vNorms  = nullptr;
			vCoords = nullptr;
			vIndex  = nullptr;
			vGroups = nullptr;
		}

		~MapData() {
			delete[] vVerts;
			delete[] vNorms;
			delete[] vCoords;
			delete[] vIndex;
			delete[] vGroups;
		}

	};

} /* namespace Core */

#endif /* HEADERS_GAMESYS_MAPDATA_H_ */
