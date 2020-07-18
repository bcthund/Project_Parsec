/*
 * map.h
 *
 *  Created on: Sep 19, 2010
 *      Author: bcthund
 */

#ifndef DUNGEONMAP_H_
#define DUNGEONMAP_H_

class DungeonMap {
	private:

	protected:

	public:
		#define NumPossiblePlanes 4096
		VAO dungeonMap;
		Data3f vNorms    [NumPossiblePlanes];
		Data2f vTex	   [NumPossiblePlanes];
		int vMapData[5]    [NumPossiblePlanes];
		Data3f vMapVerts [NumPossiblePlanes];
		GLushort uiMapIndex[NumPossiblePlanes];
		Data3f vMapNorms [NumPossiblePlanes];
		Vector2ui vXRange;				//X plane Wall Draw Ranges
		Vector2ui vYRange;				//Y plane Wall Draw Ranges
		Vector2ui vZRange;				//Z plane Wall Draw Ranges
		Vector2ui vDRange;				//Diagonal Wall Draw Ranges
		int iMapNums;
		bool init();
		bool load();
		bool calc();
		void draw(Atmosphere &a);
		#undef NumPossiblePlanes
};

bool DungeonMap::init() {
	iMapNums = 0;		//Set the number of loaded Nums to 0
	try {
		//Create a temporary map in memory
		#define x 0
		#define y 1
		#define z 2
		#define p 3
		#define t 4

		//=============================== X-Plane

		//(XYZ Orientation \/)
		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 0;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 0;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = 0;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 0;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 0;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 0;
		vMapData[iMapNums][t] = 0;
		iMapNums++;
		//(XYZ ORIENTATION /\)

		//Diagonal Walls
		vDRange[0] = iMapNums;
		vMapData[iMapNums][p] = 4;
		vMapData[iMapNums][x] = -7;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 4;
		vMapData[iMapNums][x] = -5;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 3;
		vMapData[iMapNums][x] = -5;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 3;
		vMapData[iMapNums][x] = -7;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;
		vDRange[1] = iMapNums;

		vXRange[0] = iMapNums;
		//First Floor
		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		//Hole
			vMapData[iMapNums][p] = 0;
			vMapData[iMapNums][x] = -1;
			vMapData[iMapNums][y] = 0;
			vMapData[iMapNums][z] = 0;
			vMapData[iMapNums][t] = 1;
			iMapNums++;
		//

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -4;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -4;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -7;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -7;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -7;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -2;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -5;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -2;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -6;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -2;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -7;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -2;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -8;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -2;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -9;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 3;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -5;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 3;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -6;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 3;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -7;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 3;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -8;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 3;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -9;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 2;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 3;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -0;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 3;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 4;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 4;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 5;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 5;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -0;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -0;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -0;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -4;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -4;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		//Lower Level
		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -8;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -7;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -6;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 2;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -8;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 2;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -7;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 2;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -6;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 0;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -5;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -5;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -2;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -4;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 3;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -4;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -4;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 5;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -4;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 5;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -5;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -5;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 0;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -5;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -5;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -5;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 6;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 6;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 0;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 6;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 6;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 6;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -4;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 4;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 5;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 4;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -4;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 5;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 5;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 5;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = -2;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 6;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 0;
		vMapData[iMapNums][x] = 3;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 6;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vXRange[1] = iMapNums;


		//=============================== Z-Plane
		vYRange[0] = iMapNums;
		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 2;
		vMapData[iMapNums][x] = -2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 2;
		vMapData[iMapNums][x] = -3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 2;
		vMapData[iMapNums][x] = -4;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 3;
		vMapData[iMapNums][x] = -2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 3;
		vMapData[iMapNums][x] = -3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 3;
		vMapData[iMapNums][x] = -4;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -9;
		vMapData[iMapNums][x] = -2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -9;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -9;
		vMapData[iMapNums][x] = -0;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -9;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -9;
		vMapData[iMapNums][x] = 2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -4;
		vMapData[iMapNums][x] = -2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -4;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -4;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -4;
		vMapData[iMapNums][x] = 2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -2;
		vMapData[iMapNums][x] = 2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -2;
		vMapData[iMapNums][x] = 3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -2;
		vMapData[iMapNums][x] = 4;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -1;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -1;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -0;
		vMapData[iMapNums][x] = 3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = -0;
		vMapData[iMapNums][x] = 4;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 2;
		vMapData[iMapNums][x] = 3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 4;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 4;
		vMapData[iMapNums][x] = 0;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 4;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 4;
		vMapData[iMapNums][x] = 2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 4;
		vMapData[iMapNums][x] = 3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 1;
		vMapData[iMapNums][x] = -5;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		//Hole
		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 1;
		vMapData[iMapNums][x] = -6;
		vMapData[iMapNums][t] = 1;
		iMapNums++;
		//

		//vMapData[iMapNums][p] = 1;
		//vMapData[iMapNums][y] = 0;
		//vMapData[iMapNums][z] = 1;
		//vMapData[iMapNums][x] = -6;
		//vMapData[iMapNums][t] = 0;
		//iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 1;
		vMapData[iMapNums][x] = -7;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 4;
		vMapData[iMapNums][x] = -5;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 4;
		vMapData[iMapNums][x] = -6;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][y] = 0;
		vMapData[iMapNums][z] = 4;
		vMapData[iMapNums][x] = -7;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		//Lower Level
		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -8;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = 0;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -8;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -8;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -5;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -5;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = -2;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -4;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -4;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -4;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = 2;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -4;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = -4;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = -3;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = 3;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = 4;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = -5;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = 5;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = -1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = -5;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 4;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = 5;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 4;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = -3;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 6;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = -4;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 6;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = 3;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 6;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = 4;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 6;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = -2;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 7;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 7;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = 0;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 7;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 7;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 1;
		vMapData[iMapNums][x] = 2;
		vMapData[iMapNums][y] = -1;
		vMapData[iMapNums][z] = 7;
		vMapData[iMapNums][t] = 0;
		iMapNums++;
		vYRange[1] = iMapNums;

		//=============================== Y-Plane
		vZRange[0] = iMapNums;
		for (int ix = -2; ix <= 2; ix++) {
			for (int iz = -9; iz <= -5; iz++) {
				if ((ix == 0) && (iz == -7)) {			//Hole in floor
					//vMapData[iMapNums][p] = 2;
					//vMapData[iMapNums][x] = ix;
					//vMapData[iMapNums][y] = 0;
					//vMapData[iMapNums][z] = iz;
					//vMapData[iMapNums][t] = 1;
					//iMapNums++;
				}
				else {
					vMapData[iMapNums][p] = 2;
					vMapData[iMapNums][x] = ix;
					vMapData[iMapNums][y] = 0;
					vMapData[iMapNums][z] = iz;
					vMapData[iMapNums][t] = 0;
					iMapNums++;
				}
			}
		}

		for (int ix = -2; ix <= 2; ix++) {
			for (int iz = -4; iz <= -4; iz++) {
				vMapData[iMapNums][p] = 2;
				vMapData[iMapNums][x] = ix;
				vMapData[iMapNums][y] = 0;
				vMapData[iMapNums][z] = iz;
				vMapData[iMapNums][t] = 0;
				iMapNums++;
			}
		}

		for (int ix = -4; ix <= 4; ix++) {
			for (int iz = -3; iz <= 5; iz++) {
				vMapData[iMapNums][p] = 2;
				vMapData[iMapNums][x] = ix;
				vMapData[iMapNums][y] = 0;
				vMapData[iMapNums][z] = iz;
				vMapData[iMapNums][t] = 0;
				iMapNums++;
			}
		}

		for (int ix = -5; ix <= -5; ix++) {
			for (int iz = -1; iz <= 3; iz++) {
				vMapData[iMapNums][p] = 2;
				vMapData[iMapNums][x] = ix;
				vMapData[iMapNums][y] = 0;
				vMapData[iMapNums][z] = iz;
				vMapData[iMapNums][t] = 0;
				iMapNums++;
			}
		}

		for (int ix = 5; ix <= 5; ix++) {
			for (int iz = -1; iz <= 3; iz++) {
				vMapData[iMapNums][p] = 2;
				vMapData[iMapNums][x] = ix;
				vMapData[iMapNums][y] = 0;
				vMapData[iMapNums][z] = iz;
				vMapData[iMapNums][t] = 0;
				iMapNums++;
			}
		}

		for (int ix = -2; ix <= 2; ix++) {
			for (int iz = 6; iz <= 6; iz++) {
				vMapData[iMapNums][p] = 2;
				vMapData[iMapNums][x] = ix;
				vMapData[iMapNums][y] = 0;
				vMapData[iMapNums][z] = iz;
				vMapData[iMapNums][t] = 0;
				iMapNums++;
			}
		}

		for (int ix = -7; ix <= -6; ix++) {
			for (int iz = 1; iz <= 3; iz++) {
				vMapData[iMapNums][p] = 2;
				vMapData[iMapNums][x] = ix;
				vMapData[iMapNums][y] = 0;
				vMapData[iMapNums][z] = iz;
				vMapData[iMapNums][t] = 0;
				iMapNums++;
			}
		}

		//Ceiling
		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -2;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -9;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -9;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -0;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -9;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -9;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 2;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -9;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -2;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -8;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -8;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -0;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -8;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -8;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 2;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -8;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -2;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -7;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -7;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -7;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 2;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -7;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -2;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -6;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -6;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -0;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -6;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -6;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 2;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -6;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -2;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -5;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -5;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -0;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -5;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -5;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 2;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -5;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -0;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -4;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -0;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -0;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -0;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -0;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -0;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -0;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -0;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -0;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -0;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -1;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -0;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 1;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 2;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 2;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 2;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -0;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 2;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 2;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 2;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 3;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 3;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 3;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 3;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 4;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 4;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -7;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -7;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -7;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -6;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -6;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -6;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -5;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 1;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -5;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -5;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 3;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -4;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -3;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = -2;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = 2;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		vMapData[iMapNums][p] = 2;
		vMapData[iMapNums][x] = 0;
		vMapData[iMapNums][y] = 1;
		vMapData[iMapNums][z] = -7;
		vMapData[iMapNums][t] = 0;
		iMapNums++;

		//Lower Level
		for (int ix = -1; ix <= 1; ix++) {
			for (int iz = -8; iz <= -6; iz++) {
				vMapData[iMapNums][p] = 2;
				vMapData[iMapNums][x] = ix;
				vMapData[iMapNums][y] = -1;
				vMapData[iMapNums][z] = iz;
				vMapData[iMapNums][t] = 0;
				iMapNums++;
			}
		}

		for (int ix = 0; ix <= 0; ix++) {
			for (int iz = -5; iz <= -5; iz++) {
				vMapData[iMapNums][p] = 2;
				vMapData[iMapNums][x] = ix;
				vMapData[iMapNums][y] = -1;
				vMapData[iMapNums][z] = iz;
				vMapData[iMapNums][t] = 0;
				iMapNums++;
			}
		}

		for (int ix = -2; ix <= 2; ix++) {
			for (int iz = -4; iz <= -4; iz++) {
				vMapData[iMapNums][p] = 2;
				vMapData[iMapNums][x] = ix;
				vMapData[iMapNums][y] = -1;
				vMapData[iMapNums][z] = iz;
				vMapData[iMapNums][t] = 0;
				iMapNums++;
			}
		}

		for (int ix = -4; ix <= 4; ix++) {
			for (int iz = -3; iz <= 5; iz++) {
				vMapData[iMapNums][p] = 2;
				vMapData[iMapNums][x] = ix;
				vMapData[iMapNums][y] = -1;
				vMapData[iMapNums][z] = iz;
				vMapData[iMapNums][t] = 0;
				iMapNums++;
			}
		}

		for (int ix = -5; ix <= -5; ix++) {
			for (int iz = -1; iz <= 3; iz++) {
				vMapData[iMapNums][p] = 2;
				vMapData[iMapNums][x] = ix;
				vMapData[iMapNums][y] = -1;
				vMapData[iMapNums][z] = iz;
				vMapData[iMapNums][t] = 0;
				iMapNums++;
			}
		}

		for (int ix = 5; ix <= 5; ix++) {
			for (int iz = -1; iz <= 3; iz++) {
				vMapData[iMapNums][p] = 2;
				vMapData[iMapNums][x] = ix;
				vMapData[iMapNums][y] = -1;
				vMapData[iMapNums][z] = iz;
				vMapData[iMapNums][t] = 0;
				iMapNums++;
			}
		}

		for (int ix = -2; ix <= 2; ix++) {
			for (int iz = 6; iz <= 6; iz++) {
				vMapData[iMapNums][p] = 2;
				vMapData[iMapNums][x] = ix;
				vMapData[iMapNums][y] = -1;
				vMapData[iMapNums][z] = iz;
				vMapData[iMapNums][t] = 0;
				iMapNums++;
			}
		}

		vZRange[1] = iMapNums;

		//Create default geometry (temporary data)
		int iVertex = 0;
		for (int i=0; i<iMapNums; i++) {
			vTex[iVertex][0]   = 0;
			vTex[iVertex][1]   = 0;
			vTex[iVertex+1][0] = 1;
			vTex[iVertex+1][1] = 0;
			vTex[iVertex+2][0] = 0;
			vTex[iVertex+2][1] = 1;
			vTex[iVertex+3][0] = 1;
			vTex[iVertex+3][1] = 1;

			vNorms[iVertex][0] = 0.5f;
			vNorms[iVertex][1] = 0.0f;
			vNorms[iVertex][2] = 0.0f;
			vNorms[iVertex+1][0] = 0.5f;
			vNorms[iVertex+1][1] = 0.0f;
			vNorms[iVertex+1][2] = 0.0f;
			vNorms[iVertex+2][0] = 0.5f;
			vNorms[iVertex+2][1] = 0.0f;
			vNorms[iVertex+2][2] = 0.0f;
			vNorms[iVertex+3][0] = 0.5f;
			vNorms[iVertex+3][1] = 0.0f;
			vNorms[iVertex+3][2] = 0.0f;

			iVertex+=4;
		}
		#undef p
		#undef x
		#undef y
		#undef z
		#undef t
		return true;
	}
	catch(...) {
		return false;
	}
	return false;
}

bool DungeonMap::load() {
	bool bReadResult;
	std::string loadFile = "";
	MemBlock memBlock;
	std::stringstream *sStream = new std::stringstream;

	try {
		delete sStream;
		return true;
	}
	catch(...) {
		delete sStream;
		return false;
	}

/*
	try {
		if (gameVars->debug.load) printf("\n\n ################\n");
		if (gameVars->debug.load) printf("## LOADING DUNGEON ##\n");

		//################################
		//		Load Binary Map Data


		//Temporary index value
		int iX, iY;
		int vertexId=0;

		//====> LOAD VERTEX POINTS
		for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
			vertexId=0;
			for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {
				iX=mapSX+x;
				iY=mapSY+z;
				vertexId=0;

				sStream->str("");
				*sStream << gameVars->dir.map << iX << "-" << iY << ".map";
				loadFile=sStream->str();

				if (gameVars->debug.load) std::cout << "> Loading " <<  loadFile << "...";
				bReadResult = readFile(loadFile, memBlock);		//Read the data file into memory
				if (!bReadResult) {
					sStream->str("");
					*sStream << gameVars->dir.map << "0-0.map";
					loadFile=sStream->str();
					readFile(loadFile, memBlock);
				}

				for (int d=0; d<memBlock.size; d+=gameVars->recordSize.map) {
					float tempX=(unsigned char)memBlock.buffer[0+d]+(unsigned char)memBlock.buffer[1+d]+(unsigned char)memBlock.buffer[2+d]+(unsigned char)memBlock.buffer[3+d];

					//Get the height of this point
					unsigned char tempYc[4];
					tempYc[0]=(unsigned char)memBlock.buffer[8+d];
					tempYc[1]=(unsigned char)memBlock.buffer[9+d];
					tempYc[2]=(unsigned char)memBlock.buffer[10+d];
					tempYc[3]=(unsigned char)memBlock.buffer[11+d];

					unsigned int tempY=0;
					tempY = tempYc[0] + tempYc[1] + tempYc[2] + tempYc[3];

					float tempZ=(unsigned char)memBlock.buffer[4+d]+(unsigned char)memBlock.buffer[5+d]+(unsigned char)memBlock.buffer[6+d]+(unsigned char)memBlock.buffer[7+d];

					mapData[x][z].vVerts[vertexId][0]   = tempX+(x*1000);
					mapData[x][z].vVerts[vertexId][1]   = tempY;
					mapData[x][z].vVerts[vertexId][2]   = tempZ+(z*1000);
					//vVerts[vertexId] = { tempX+(x*1010), tempY, tempZ+(z*1010) };
					//printf("[%i]\n", vertexId);
					//printf("%f, %f, %f\n", mapData[x][z].vVerts[vertexId][0], mapData[x][z].vVerts[vertexId][1], mapData[x][z].vVerts[vertexId][2]);
					vertexId++;
				}
				if (gameVars->debug.load) std::cout << "Done." <<  std::endl;
			}
		}

		//====> Create Texture Coord Array
		bool texFlip = false;
		int count=0;
		vertexId=0;
		for (int i=0; i<=20299; i++) {
			if (!texFlip) {
				vCoord1[vertexId][0]	= 	0.0;
				vCoord1[vertexId][1]	= 	0.0;

				vCoord1[vertexId+1][0]	= 	0.0;
				vCoord1[vertexId+1][1]	= 	1.0;
			}
			else {
				vCoord1[vertexId][0]	= 	1.0;
				vCoord1[vertexId][1]	= 	1.0;

				vCoord1[vertexId+1][0]	= 	1.0;
				vCoord1[vertexId+1][1]	= 	0.0;
			}

			if (count==50) {
				count=0;
				vertexId++;
				if (texFlip) texFlip=false;
				else texFlip=true;
			}
			else {
				vertexId+=2;
				count++;
			}
		}

		//Create Index Array
		int res=1;
		count=0;
		vertexId=0;
		for (uint i=0; i<=10099; i++) {
			uiIndex1[vertexId] = i+(101*res);
			uiIndex1[vertexId+1] = i;

			if (count==(100/res)) {
				uiIndex1[vertexId+2] = 0xFFFF;
				i+=101*(res-1);
				vertexId+=3;
				count=0;
			}
			else {
				i+=(res-1);
				vertexId+=2;
				count++;
			}
		}

		delete sStream;
		return true;
	}
	catch(...) {
		delete sStream;
		return false;
	}
	*/
	return false;
}

bool DungeonMap::calc() {
	try {
		//index 0xFFFF = Primitive Restart
		//gameVars->vao.world.map[x][z].Begin(GL_TRIANGLE_STRIP, 20299, 1);
		//gameVars->vao.world.map[x][z].CopyData(GLA_VERTEX,  mapData[x][z].vVerts);
		//gameVars->vao.world.map[x][z].CopyData(GLA_TEXTURE, vCoord1, 0);
		//gameVars->vao.world.map[x][z].CopyData(GLA_INDEX,   uiIndex1);
		//gameVars->vao.world.map[x][z].CopyData(GLA_NORMAL,  mapData[x][z].vNorms);
		//gameVars->vao.world.map[x][z].End();

		#define x 0
		#define y 1
		#define z 2
		#define p 3
		#define t 4
		int iV=0;
		Data3f vPoints[4];
		for(int i=0; i<iMapNums; i++) {
			vPoints[0][x] = 0;			vPoints[0][y] = 0;			vPoints[0][z] = 0;
			vPoints[1][x] = 0;			vPoints[1][y] = 0;			vPoints[1][z] = 0;
			vPoints[2][x] = 0;			vPoints[2][y] = 0;			vPoints[2][z] = 0;
			vPoints[3][x] = 0;			vPoints[3][y] = 0;			vPoints[3][z] = 0;
			if (vMapData[i][t] == 0) {		//Basic Wall
				switch(vMapData[i][p]) {
					case 0:		//x plane
						vPoints[0][x] = 0   + (vMapData[i][x]*32);
						vPoints[0][y] = 40  + (vMapData[i][y]*40);
						vPoints[0][z] = 32  + (vMapData[i][z]*32);

						vPoints[1][x] = 0   + (vMapData[i][x]*32);
						vPoints[1][y] = 40  + (vMapData[i][y]*40);
						vPoints[1][z] = 0   + (vMapData[i][z]*32);

						vPoints[2][x] = 0   + (vMapData[i][x]*32);
						vPoints[2][y] = 0   + (vMapData[i][y]*40);
						vPoints[2][z] = 32  + (vMapData[i][z]*32);

						vPoints[3][x] = 0   + (vMapData[i][x]*32);
						vPoints[3][y] = 0   + (vMapData[i][y]*40);
						vPoints[3][z] = 0   + (vMapData[i][z]*32);
						break;
					case 1:		//z plane
						vPoints[0][x] = 0   + (vMapData[i][x]*32);
						vPoints[0][y] = 40  + (vMapData[i][y]*40);
						vPoints[0][z] = 0   + (vMapData[i][z]*32);

						vPoints[1][x] = 32  + (vMapData[i][x]*32);
						vPoints[1][y] = 40  + (vMapData[i][y]*40);
						vPoints[1][z] = 0   + (vMapData[i][z]*32);

						vPoints[2][x] = 0   + (vMapData[i][x]*32);
						vPoints[2][y] = 0   + (vMapData[i][y]*40);
						vPoints[2][z] = 0   + (vMapData[i][z]*32);

						vPoints[3][x] = 32  + (vMapData[i][x]*32);
						vPoints[3][y] = 0   + (vMapData[i][y]*40);
						vPoints[3][z] = 0   + (vMapData[i][z]*32);
						break;
					case 2:		//y plane
						vPoints[0][x] = 0   + (vMapData[i][x]*32);
						vPoints[0][y] = 0   + (vMapData[i][y]*40);
						vPoints[0][z] = 0   + (vMapData[i][z]*32);

						vPoints[1][x] = 32  + (vMapData[i][x]*32);
						vPoints[1][y] = 0   + (vMapData[i][y]*40);
						vPoints[1][z] = 0   + (vMapData[i][z]*32);

						vPoints[2][x] = 0   + (vMapData[i][x]*32);
						vPoints[2][y] = 0   + (vMapData[i][y]*40);
						vPoints[2][z] = 32  + (vMapData[i][z]*32);

						vPoints[3][x] = 32  + (vMapData[i][x]*32);
						vPoints[3][y] = 0   + (vMapData[i][y]*40);
						vPoints[3][z] = 32  + (vMapData[i][z]*32);
						break;
					case 3:		//z plane, diagonal wall style 1
						vPoints[0][x] = 0   + (vMapData[i][x]*32);
						vPoints[0][y] = 40  + (vMapData[i][y]*40);
						vPoints[0][z] = 0   + (vMapData[i][z]*32);

						vPoints[1][x] = 32  + (vMapData[i][x]*32);
						vPoints[1][y] = 40  + (vMapData[i][y]*40);
						vPoints[1][z] = 32  + (vMapData[i][z]*32);

						vPoints[2][x] = 0   + (vMapData[i][x]*32);
						vPoints[2][y] = 0   + (vMapData[i][y]*40);
						vPoints[2][z] = 0   + (vMapData[i][z]*32);

						vPoints[3][x] = 32  + (vMapData[i][x]*32);
						vPoints[3][y] = 0   + (vMapData[i][y]*40);
						vPoints[3][z] = 32  + (vMapData[i][z]*32);
						break;
					case 4:		//z plane, diagonal wall style 2
						vPoints[0][x] = 0   + (vMapData[i][x]*32);
						vPoints[0][y] = 40  + (vMapData[i][y]*40);
						vPoints[0][z] = 32  + (vMapData[i][z]*32);

						vPoints[1][x] = 32  + (vMapData[i][x]*32);
						vPoints[1][y] = 40  + (vMapData[i][y]*40);
						vPoints[1][z] = 0   + (vMapData[i][z]*32);

						vPoints[2][x] = 0   + (vMapData[i][x]*32);
						vPoints[2][y] = 0   + (vMapData[i][y]*40);
						vPoints[2][z] = 32  + (vMapData[i][z]*32);

						vPoints[3][x] = 32  + (vMapData[i][x]*32);
						vPoints[3][y] = 0   + (vMapData[i][y]*40);
						vPoints[3][z] = 0   + (vMapData[i][z]*32);
						break;
					default:
						printf("Error! Plane type incorrect.\n");
						break;
				}
			}
			else if (vMapData[i][t] == 1) {		//Hole
				switch(vMapData[i][p]) {
					case 0:		//x plane
						vPoints[0][x] = 0   + (vMapData[i][x]*32);
						vPoints[0][y] = 24  + (vMapData[i][y]*40);
						vPoints[0][z] = 24  + (vMapData[i][z]*32);

						vPoints[1][x] = 0   + (vMapData[i][x]*32);
						vPoints[1][y] = 24  + (vMapData[i][y]*40);
						vPoints[1][z] = 8   + (vMapData[i][z]*32);

						vPoints[2][x] = 0   + (vMapData[i][x]*32);
						vPoints[2][y] = 8   + (vMapData[i][y]*40);
						vPoints[2][z] = 24  + (vMapData[i][z]*32);

						vPoints[3][x] = 0   + (vMapData[i][x]*32);
						vPoints[3][y] = 8   + (vMapData[i][y]*40);
						vPoints[3][z] = 8   + (vMapData[i][z]*32);
						break;
					case 1:		//z plane
						vPoints[0][x] = 8   + (vMapData[i][x]*32);
						vPoints[0][y] = 24  + (vMapData[i][y]*40);
						vPoints[0][z] = 0   + (vMapData[i][z]*32);

						vPoints[1][x] = 24  + (vMapData[i][x]*32);
						vPoints[1][y] = 24  + (vMapData[i][y]*40);
						vPoints[1][z] = 0   + (vMapData[i][z]*32);

						vPoints[2][x] = 8   + (vMapData[i][x]*32);
						vPoints[2][y] = 8   + (vMapData[i][y]*40);
						vPoints[2][z] = 0   + (vMapData[i][z]*32);

						vPoints[3][x] = 24  + (vMapData[i][x]*32);
						vPoints[3][y] = 8   + (vMapData[i][y]*40);
						vPoints[3][z] = 0   + (vMapData[i][z]*32);
						break;
					case 2:		//y plane
						vPoints[0][x] = 8   + (vMapData[i][x]*32);
						vPoints[0][y] = 0   + (vMapData[i][y]*40);
						vPoints[0][z] = 8   + (vMapData[i][z]*32);

						vPoints[1][x] = 24  + (vMapData[i][x]*32);
						vPoints[1][y] = 0   + (vMapData[i][y]*40);
						vPoints[1][z] = 8   + (vMapData[i][z]*32);

						vPoints[2][x] = 8   + (vMapData[i][x]*32);
						vPoints[2][y] = 0   + (vMapData[i][y]*40);
						vPoints[2][z] = 24  + (vMapData[i][z]*32);

						vPoints[3][x] = 24  + (vMapData[i][x]*32);
						vPoints[3][y] = 0   + (vMapData[i][y]*40);
						vPoints[3][z] = 24  + (vMapData[i][z]*32);
						break;
					case 3:		//z plane, diagonal wall style 1
						vPoints[0][x] = 0   + (vMapData[i][x]*32);
						vPoints[0][y] = 0   + (vMapData[i][y]*40);
						vPoints[0][z] = 0   + (vMapData[i][z]*32);

						vPoints[1][x] = 0   + (vMapData[i][x]*32);
						vPoints[1][y] = 0   + (vMapData[i][y]*40);
						vPoints[1][z] = 0   + (vMapData[i][z]*32);

						vPoints[2][x] = 0   + (vMapData[i][x]*32);
						vPoints[2][y] = 0   + (vMapData[i][y]*40);
						vPoints[2][z] = 0   + (vMapData[i][z]*32);

						vPoints[3][x] = 0   + (vMapData[i][x]*32);
						vPoints[3][y] = 0   + (vMapData[i][y]*40);
						vPoints[3][z] = 0   + (vMapData[i][z]*32);
						break;
					case 4:		//z plane, diagonal wall style 2
						vPoints[0][x] = 0   + (vMapData[i][x]*32);
						vPoints[0][y] = 0   + (vMapData[i][y]*40);
						vPoints[0][z] = 0   + (vMapData[i][z]*32);

						vPoints[1][x] = 0   + (vMapData[i][x]*32);
						vPoints[1][y] = 0   + (vMapData[i][y]*40);
						vPoints[1][z] = 0   + (vMapData[i][z]*32);

						vPoints[2][x] = 0   + (vMapData[i][x]*32);
						vPoints[2][y] = 0   + (vMapData[i][y]*40);
						vPoints[2][z] = 0   + (vMapData[i][z]*32);

						vPoints[3][x] = 0   + (vMapData[i][x]*32);
						vPoints[3][y] = 0   + (vMapData[i][y]*40);
						vPoints[3][z] = 0   + (vMapData[i][z]*32);
						break;
					default:
						printf("Error! Plane type incorrect.\n");
						break;
				}
			}
			vMapVerts[iV][x]   = vPoints[0][x];
			vMapVerts[iV][y]   = vPoints[0][y];
			vMapVerts[iV][z]   = vPoints[0][z];
			vMapVerts[iV+1][x] = vPoints[1][x];
			vMapVerts[iV+1][y] = vPoints[1][y];
			vMapVerts[iV+1][z] = vPoints[1][z];
			vMapVerts[iV+2][x] = vPoints[2][x];
			vMapVerts[iV+2][y] = vPoints[2][y];
			vMapVerts[iV+2][z] = vPoints[2][z];
			vMapVerts[iV+3][x] = vPoints[3][x];
			vMapVerts[iV+3][y] = vPoints[3][y];
			vMapVerts[iV+3][z] = vPoints[3][z];
			iV+=4;
		}

		int iIndex=0;
		for (int i=0; i<iMapNums*5; i+=5) {
			uiMapIndex[i] = iIndex;
			uiMapIndex[i+1] = iIndex+1;
			uiMapIndex[i+2] = iIndex+2;
			uiMapIndex[i+3] = iIndex+3;
			uiMapIndex[i+4] = 0xFFFF;
			iIndex+=4;
		}

		#undef p
		#undef x
		#undef y
		#undef z
		#undef t


		dungeonMap.Begin(GL_TRIANGLE_STRIP, 5*iMapNums);
		dungeonMap.CopyData(GLA_VERTEX,  vMapVerts);
		dungeonMap.CopyData(GLA_INDEX,   uiMapIndex);
		dungeonMap.CopyData(GLA_NORMAL,  vNorms);
		dungeonMap.CopyData(GLA_TEXTURE, vTex, 0);
		dungeonMap.End();
		return true;
	}
	catch(...) {
		return false;
	}
	return false;
}

void DungeonMap::draw(Atmosphere &a) {
	try {
		glDisable(GL_CULL_FACE);
		Vector3f	vObjPos = { 0, 0, 0 };

		Matrix44f	mTemp = {	1.0f, 0.0f, 0.0f, 0.0f,
								0.0f, 1.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 1.0f, 0.0f,
								vObjPos[0], vObjPos[1], vObjPos[2], 1.0f };

		Core.matrix.Push();
			Core.shader.use(GLS_FONT);
			Core.shader.getUniform(GLS_FONT);

			gameVars->texture.terrain.Set("dwall_06.png");		//UNSAFE IMAGE
			//gameVars->texture.terrain.Set("dwall_03.png");	//SAFE IMAGE
			//dungeonMap.Draw(GLM_DRAW_RANGE_ELEMENTS, 30, 20);	//REFERENCE, DO NOT DELETE
			dungeonMap.Draw(GLM_DRAW_RANGE_ELEMENTS, vDRange[0]*10, (vDRange[1]-vDRange[0])*5);

			gameVars->texture.terrain.Set("dwall_03.png");
			//dungeonMap.Draw(GLM_DRAW_RANGE_ELEMENTS, (vXRange[0]+1)*5, (vXRange[1]*5));
			dungeonMap.Draw(GLM_DRAW_RANGE_ELEMENTS, vXRange[0]*10, (vXRange[1]-vXRange[0])*5);

			gameVars->texture.terrain.Set("dwall_05.png");
			//dungeonMap.Draw(GLM_DRAW_RANGE_ELEMENTS, (vYRange[0]*4)+2, (vYRange[1]*4)+2);
			dungeonMap.Draw(GLM_DRAW_RANGE_ELEMENTS, vYRange[0]*10, (vYRange[1]-vYRange[0])*5);

			gameVars->texture.terrain.Set("dwall_04.png");
			//dungeonMap.Draw(GLM_DRAW_RANGE_ELEMENTS, vZRange[0]*5, vZRange[1]*5);
			dungeonMap.Draw(GLM_DRAW_RANGE_ELEMENTS, vZRange[0]*10, (vZRange[1]-vZRange[0])*5);

		Core.matrix.Pop();

		//DRAW THE DEBUG COORDINATE PLANES
		Core.matrix.Push();
			Core.shader.use(GLS_SHADED_TEX_ALPHA);
			Core.matrix.Apply(mTemp);
			Core.matrix.Scale(0.25, 0.25, 0.25);
			Core.matrix.Translate(0, 24, 0);
			//Core::Matrix.Rotate(M_DegToRad(90), 0, 1, 0);
			Core.matrix.SetTransform();
			Core.shader.getUniform(GLS_SHADED_TEX_ALPHA);

				#define x 0
				#define y 1
				#define z 2

				//Calculate averages for geometry
				Vector3f vXAvg, vYAvg, vZAvg;
				Vector3f fDist;
				Vector3ui iTrack = { x, y, z };
				Average(vXAvg, vMapVerts[0], vMapVerts[1], vMapVerts[2], vMapVerts[3]);
				Average(vYAvg, vMapVerts[4], vMapVerts[5], vMapVerts[6], vMapVerts[7]);
				Average(vZAvg, vMapVerts[8], vMapVerts[9], vMapVerts[10], vMapVerts[11]);

				//Calculate distance from player
				Vector3f vCurrentPos = { gameVars->transform.dunPos[x], gameVars->transform.dunPos[y], gameVars->transform.dunPos[z]};
				vXAvg[x] = vXAvg[x] - 16;
				vXAvg[y] = vXAvg[y] - 16;
				vXAvg[z] = vXAvg[z] - 16;
				calcDistance(vCurrentPos, vXAvg, fDist[x]);

				vYAvg[x] = vYAvg[x] - 16;
				vYAvg[y] = vYAvg[y] - 16;
				vYAvg[z] = vYAvg[z] - 16;
				calcDistance(vCurrentPos, vYAvg, fDist[y]);

				vZAvg[x] = vZAvg[x] - 32;
				vZAvg[y] = vZAvg[y] + 16;
				vZAvg[z] = vZAvg[z] - 32;
				calcDistance(vCurrentPos, vZAvg, fDist[z]);

				//Sort farthest to closest
				// TODO: New Vector3ui type breaks this, fix bubble sort function
				//BubbleSortTrack(fDist, iTrack, 3);

				//Draw in order
				switch (iTrack[0]) {
					case x:
						gameVars->texture.terrain.Set("xplane.png");
						dungeonMap.Draw(GLM_DRAW_RANGE, 4, 4);
						break;
					case y:
						gameVars->texture.terrain.Set("yplane.png");
						dungeonMap.Draw(GLM_DRAW_RANGE, 0, 4);
						break;
					case z:
						gameVars->texture.terrain.Set("zplane.png");
						dungeonMap.Draw(GLM_DRAW_RANGE, 8, 4);
						break;
				}

				switch (iTrack[1]) {
					case x:
						gameVars->texture.terrain.Set("xplane.png");
						dungeonMap.Draw(GLM_DRAW_RANGE, 4, 4);
						break;
					case y:
						gameVars->texture.terrain.Set("yplane.png");
						dungeonMap.Draw(GLM_DRAW_RANGE, 0, 4);
						break;
					case z:
						gameVars->texture.terrain.Set("zplane.png");
						dungeonMap.Draw(GLM_DRAW_RANGE, 8, 4);
						break;
				}

				switch (iTrack[2]) {
					case x:
						gameVars->texture.terrain.Set("xplane.png");
						dungeonMap.Draw(GLM_DRAW_RANGE, 4, 4);
						break;
					case y:
						gameVars->texture.terrain.Set("yplane.png");
						dungeonMap.Draw(GLM_DRAW_RANGE, 0, 4);
						break;
					case z:
						gameVars->texture.terrain.Set("zplane.png");
						dungeonMap.Draw(GLM_DRAW_RANGE, 8, 4);
						break;
				}

				#undef x
				#undef y
				#undef z

		Core.matrix.Pop();
		glEnable(GL_CULL_FACE);
	}
	catch(...) {

	}
}
#endif /* DUNGEONMAP_H_ */
