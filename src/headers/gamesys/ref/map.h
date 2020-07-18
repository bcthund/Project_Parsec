/*
 * map.h
 *
 *  Created on: Sep 19, 2010
 *      Author: bcthund
 */

#ifndef WORLDMAP_H_
#define WORLDMAP_H_

class WorldMap {
	private:

	protected:

	public:
		WorldMap(Atmosphere *a, std::string d): atmosphere(a), dir(d) {
			//mapData = new MapData*[9];
			//for(int i=0; i<9; i++) {
			//	mapData[i] = new MapData[9];
			//}
		}

		~WorldMap() {
			//       .................................................................Done
			cout << "Destroy WorldMap.................................................Not Implemented" << endl;
		}

		std::string dir;			//Directory location for this map
		Vector2i  vStart;
		Vector2ui vBase;
		MapData mapData[9][9];
		bool	bSkip[81];			// TODO: Temporary occlusion cull technique, skip drawing every other frame
		bool init();
		bool init(int iSx, int iSz);
		bool init(int iSx, int iSz, int iPx, int iPy, int iPz);
		bool load(int iShift);
		void shift(int iShift);
		void stitch(unsigned int iStitch, int x, int z);
		void updateNorms(int x, int z);
		bool calc(bool bUpdate);
		void modify(MOD_VAL eMod, float fNewVal);
		void update(int iGridx, int iGridz);
		void draw(int iShader);
		void reset(Atmosphere *a, std::string d);
		float getHeight(float x, float z);
		float getHeight(float iX, float iZ, int gX, int gZ);
		float * getHeight_Normal(float x, float z);
		Atmosphere *atmosphere;		//The parents atmosphere
};

float WorldMap::getHeight(float iX, float iZ, int gX, int gZ) {
	//Define variables
		Vector3f a, b, c, d, p, q;
		float u, v, w, t;
		int opp, adj, h;
		int iResult;

		iX = iX-(gX*1024);
		iZ = iZ-(gZ*1024);

		//Define the object position ray
		p[0] =  iX;
		p[1] =  -500;
		p[2] =  iZ;

		q[0] =  iX;
		q[1] =  500;
		q[2] =  iZ;

		//Set barycentrics to 0
		u = 0;
		v = 0;
		w = 0;
		t = 0;

	//Procedure Code Outline
	bool foundHeight=false;
	for (int i=0; i < mapData[gX][gZ].numFaces; i++) {
		//Get Triangle Data for current count
		//Get the triangle vertex data, for test point
		a[0] = mapData[gX][gZ].vVerts[int(mapData[gX][gZ].vGroups[i][0])][0]*16;
		a[1] = mapData[gX][gZ].vVerts[int(mapData[gX][gZ].vGroups[i][0])][1]*16;
		a[2] = mapData[gX][gZ].vVerts[int(mapData[gX][gZ].vGroups[i][0])][2]*16;

			//Check distance from object, if within 200 units { (Only check one vertex, this will suffice)
			//Distance Calculations
			opp = a[0] - iX;
			adj = a[2] - iZ;
			h = sqr(opp) + sqr(adj);
			h = sqrt(h);

			//If ray is inside triangle {
			if(h <= 50) {

				//Get the rest of the triangle Data
				b[0] = mapData[gX][gZ].vVerts[int(mapData[gX][gZ].vGroups[i][1])][0]*16;
				b[1] = mapData[gX][gZ].vVerts[int(mapData[gX][gZ].vGroups[i][1])][1]*16;
				b[2] = mapData[gX][gZ].vVerts[int(mapData[gX][gZ].vGroups[i][1])][2]*16;
				c[0] = mapData[gX][gZ].vVerts[int(mapData[gX][gZ].vGroups[i][2])][0]*16;
				c[1] = mapData[gX][gZ].vVerts[int(mapData[gX][gZ].vGroups[i][2])][1]*16;
				c[2] = mapData[gX][gZ].vVerts[int(mapData[gX][gZ].vGroups[i][2])][2]*16;

				//Are we within the triangle?
				//Projection of triangle onto the xz plane, we don't care about the height right now
				Vector3f testA, testB,testC, testP;
				testA[0] = a[0];
				testA[1] = 0;
				testA[2] = a[2];
				testB[0] = b[0];
				testB[1] = 0;
				testB[2] = b[2];
				testC[0] = c[0];
				testC[1] = 0;
				testC[2] = c[2];
				testP[0] = p[0];
				testP[1] = 0;
				testP[2] = p[2];

				if (PointInTriangle(testP, testA, testB, testC)) {
					float temp;
					deepCopy(t, temp);
					iResult=IntersectTri(p, q, a, c, b, u, v, w, t);
					if (foundHeight) t = (t+temp)/2;
					foundHeight=true;
				}
			}
	}
	if (foundHeight) return -(500-(1000*t));
	else return 0;
}

float WorldMap::getHeight(float x, float z) {
	float newHeight;

	//What terrain chunk/grid are we on? (Range depends on size of gameVars.iTerrainGrid)
	int xGrid = -(int)x/1024;
	int zGrid = -(int)z/1024;

	//xGrid = -xGrid;
	//zGrid = -zGrid;

	//What is our exact position on the terrain chunk (0-1023)
		float xPos = -(x+((float)xGrid*1024.0f));
		float yPos = -((float)zGrid*1024.0f);
		float zPos = -(z+((float)zGrid*1024.0f));

	//Define variables
		Vector3f a, b, c, d, p, q;
		float u, v, w, t;
		float opp, adj, h;
		int iResult;

		//Define the player position ray
		float iRayDepth = 5000;
		p[0] =  xPos;
		p[1] =  -iRayDepth;
		p[2] =  zPos;

		q[0] =  xPos;
		q[1] =  iRayDepth;
		q[2] =  zPos;

		//Set barycentrics to 0
		u = 0;
		v = 0;
		w = 0;
		t = 0;

	//Procedure Code Outline
	bool foundHeight = false;
	bool legalHeight = false;

	float fPos = (float)zPos/16.0f;
	int iQuad = 0;
	//int checkFaces = mapData[xGrid][zGrid].numFaces;

	//if(fPos<=1) iQuad=0;
	//else if(fPos>1 && fPos<=2) iQuad=1;

//	cout << "==================================" << endl;
	//cout << "x: " << x << "\tz: " << z << "\txGrid: " << xGrid << "\tzGrid: " << zGrid << "\txPos: " << xPos << "\tzPos: " << zPos << "\tfPos: " << fPos << "\tTest xPos: " << -(x) << endl;
	/*
	for(int i=0; i<64; i++) {
		if(fPos>=i && fPos<=(i+1)) {
			iQuad=i;
			break;
		}
	}
	*/
	iQuad = 63-(zPos/16);
//	cout << ", iQuad: " << iQuad;
	int iStartU	= (64*iQuad),
		iEndU	= (64*iQuad)+64,
		iStartL	= 4096+(64*iQuad),
		iEndL	= 4096+(64*iQuad)+64;

	/*
	 * Safety catches
	 */
	if(iStartU<0) iStartU=0;
	if(iStartL<0) iStartL=0;
	if(iEndU>8192) iEndU=8192;
	if(iEndL>8192) iEndL=8192;

//	cout << ", URange: (" << iStartU << ", " << iEndU << ")" << ", LRange: (" << iStartL << ", " << iEndL << ")" << endl;
//	cout << ", URange: (" << iStartU << ", " << iEndU << ")" << endl;

	//do {
		//for (int i=0; i < mapData[xGrid][zGrid].numFaces; i++) {
		/*
		 * Check upper triangles
		 */
		for (int i=iStartU; i < iEndU; i++) {
			//Get Triangle Data for current count
			//Get the triangle vertex data, for test point
			a[0] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][0])][0]*16;
			a[1] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][0])][1]*16;
			a[2] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][0])][2]*16;

			//Check distance from player, if within 200 units { (Only check one vertex, this will suffice)
			//Distance Calculations
			opp = a[0] - xPos;
			adj = a[2] - zPos;
			h = sqr(opp) + sqr(adj);
			h = sqrt(h);

			//If ray is inside triangle {
			if(h <= 100) {;
				//Get the rest of the triangle Data
				b[0] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][1])][0]*16;
				b[1] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][1])][1]*16;
				b[2] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][1])][2]*16;
				c[0] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][2])][0]*16;
				c[1] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][2])][1]*16;
				c[2] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][2])][2]*16;

			//	cout << "Checking: (" << a[0] << ", " << a[1] << ", " << a[2];
			//	cout << ") : (" << b[0] << ", " << b[1] << ", " << b[2];
			//	cout << ") : (" << c[0] << ", " << c[1] << ", " << c[2] << ")" << endl;

				//Projection of triangle onto the xz plane, we don't care about the height right now
				Vector3f testA, testB,testC, testP;
				testA[0] = a[0];
				testA[1] = 0;
				testA[2] = a[2];
				testB[0] = b[0];
				testB[1] = 0;
				testB[2] = b[2];
				testC[0] = c[0];
				testC[1] = 0;
				testC[2] = c[2];
				testP[0] = p[0];
				testP[1] = 0;
				testP[2] = p[2];

				/*
				 * Are we currently inside the projected triangle?
				 */
				if (PointInTriangle(testP, testA, testB, testC)) {
					/*
					 * We are inside the tested triangle
					 * Perform the intersection test to find our t value
					 * The t value is the intersection height of the triangle
					 * 	on the vertical ray.
					 */
					iResult=IntersectTri(p, q, a, c, b, u, v, w, t);
					newHeight = (iRayDepth-((2.0f*iRayDepth)*t));
					foundHeight=true;
				}
			}
			if (foundHeight) {
				//cout << "----------------------------> FOUND IN UPPER TRI!" << endl;
				break;
			}
		}

		/*
		 * Check lower triangles
		 */
		if (!foundHeight) {
			for (int i=iStartL; i < iEndL; i++) {
				//Get Triangle Data for current count
				//Get the triangle vertex data, for test point
				a[0] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][0])][0]*16;
				a[1] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][0])][1]*16;
				a[2] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][0])][2]*16;

				//Check distance from player, if within 200 units { (Only check one vertex, this will suffice)
				//Distance Calculations
				opp = a[0] - xPos;
				adj = a[2] - zPos;
				h = sqr(opp) + sqr(adj);
				h = sqrt(h);

				//If ray is inside triangle {
				if(h <= 100) {;
					//Get the rest of the triangle Data
					b[0] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][1])][0]*16;
					b[1] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][1])][1]*16;
					b[2] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][1])][2]*16;
					c[0] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][2])][0]*16;
					c[1] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][2])][1]*16;
					c[2] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][2])][2]*16;

				//	cout << "Checking: (" << a[0] << ", " << a[1] << ", " << a[2];
				//	cout << ") : (" << b[0] << ", " << b[1] << ", " << b[2];
				//	cout << ") : (" << c[0] << ", " << c[1] << ", " << c[2] << ")" << endl;

					//Projection of triangle onto the xz plane, we don't care about the height right now
					Vector3f testA, testB,testC, testP;
					testA[0] = a[0];
					testA[1] = 0;
					testA[2] = a[2];
					testB[0] = b[0];
					testB[1] = 0;
					testB[2] = b[2];
					testC[0] = c[0];
					testC[1] = 0;
					testC[2] = c[2];
					testP[0] = p[0];
					testP[1] = 0;
					testP[2] = p[2];

					/*
					 * Are we currently inside the projected triangle?
					 */
					if (PointInTriangle(testP, testA, testB, testC)) {
						/*
						 * We are inside the tested triangle
						 * Perform the intersection test to find our t value
						 * The t value is the intersection height of the triangle
						 * 	on the vertical ray.
						 */
						iResult=IntersectTri(p, q, a, c, b, u, v, w, t);
						newHeight = (iRayDepth-((2.0f*iRayDepth)*t));
						foundHeight=true;
					}
				}
				if (foundHeight) {
					//cout << "----------------------------> FOUND IN LOWER TRI!" << endl;
					break;
				}
			}
		}

		/*
		 * Last ditch effort, go through everything
		 */
		if (!foundHeight) {
			for (int i=0; i < mapData[xGrid][zGrid].numFaces; i++) {
				//Get Triangle Data for current count
				//Get the triangle vertex data, for test point
				a[0] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][0])][0]*16;
				a[1] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][0])][1]*16;
				a[2] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][0])][2]*16;

				//Check distance from player, if within 200 units { (Only check one vertex, this will suffice)
				//Distance Calculations
				opp = a[0] - xPos;
				adj = a[2] - zPos;
				h = sqr(opp) + sqr(adj);
				h = sqrt(h);

				//If ray is inside triangle {
				if(h <= 100) {;
					//Get the rest of the triangle Data
					b[0] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][1])][0]*16;
					b[1] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][1])][1]*16;
					b[2] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][1])][2]*16;
					c[0] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][2])][0]*16;
					c[1] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][2])][1]*16;
					c[2] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][2])][2]*16;

					//Projection of triangle onto the xz plane, we don't care about the height right now
					Vector3f testA, testB,testC, testP;
					testA[0] = a[0];
					testA[1] = 0;
					testA[2] = a[2];
					testB[0] = b[0];
					testB[1] = 0;
					testB[2] = b[2];
					testC[0] = c[0];
					testC[1] = 0;
					testC[2] = c[2];
					testP[0] = p[0];
					testP[1] = 0;
					testP[2] = p[2];

					/*
					 * Are we currently inside the projected triangle?
					 */
					if (PointInTriangle(testP, testA, testB, testC)) {
						/*
						 * We are inside the tested triangle
						 * Perform the intersection test to find our t value
						 * The t value is the intersection height of the triangle
						 * 	on the vertical ray.
						 */
						iResult=IntersectTri(p, q, a, c, b, u, v, w, t);
						newHeight = (iRayDepth-((2.0f*iRayDepth)*t));
						foundHeight=true;
					}
				}
				if (foundHeight) {
					//cout << "----------------------------> FOUND IN LAST DITCH!" << endl;
					break;
				}
			}
		}
	//} while(foundHeight==false);
	return newHeight;
}

float * WorldMap::getHeight_Normal(float x, float z) {
	float * vReturn = new float[4];
	float newHeight;

	//What terrain chunk/grid are we on? (Range depends on size of gameVars.iTerrainGrid)
	int xGrid = -(int)x/1024;
	int zGrid = -(int)z/1024;

	//What is our exact position on the terrain chunk (0-1023)
	int xPos = -(x+(xGrid*1024));
	int yPos = -(zGrid*1024);
	int zPos = -(z+(zGrid*1024));

	//Define variables
	Vector3f a, b, c, d, p, q;
	float u, v, w, t;
	int opp, adj, h;
	int iResult;

	//Define the player position ray
	int iRayDepth = 5000;
	p[0] =  xPos;
	p[1] =  -iRayDepth;
	p[2] =  zPos;

	q[0] =  xPos;
	q[1] =  iRayDepth;
	q[2] =  zPos;

	//Set barycentrics to 0
	u = 0;
	v = 0;
	w = 0;
	t = 0;

	//Procedure Code Outline
	bool foundHeight = false;
	bool legalHeight = false;

	float fPos = (float)zPos/16;
	int iQuad = 0;

//	cout << "==================================" << endl;
//	cout << "xPos: " << xPos << ", zPos: " << zPos << ", fPos: " << fPos;

	iQuad = 63-(zPos/16);
//	cout << ", iQuad: " << iQuad;
	int iStartU	= (64*iQuad),
		iEndU	= (64*iQuad)+64,
		iStartL	= 4096+(64*iQuad),
		iEndL	= 4096+(64*iQuad)+64;

	/*
	 * Safety catches
	 */
	if(iStartU<0) iStartU=0;
	if(iStartL<0) iStartL=0;
	if(iEndU>8192) iEndU=8192;
	if(iEndL>8192) iEndL=8192;

//	cout << ", URange: (" << iStartU << ", " << iEndU << ")" << ", LRange: (" << iStartL << ", " << iEndL << ")" << endl;
//	cout << ", URange: (" << iStartU << ", " << iEndU << ")" << endl;

	//do {
		//for (int i=0; i < mapData[xGrid][zGrid].numFaces; i++) {
		/*
		 * Check upper triangles
		 */
		for (int i=iStartU; i < iEndU; i++) {
			//Get Triangle Data for current count
			//Get the triangle vertex data, for test point
			a[0] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][0])][0]*16;
			a[1] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][0])][1]*16;
			a[2] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][0])][2]*16;

			//Check distance from player, if within 200 units { (Only check one vertex, this will suffice)
			//Distance Calculations
			opp = a[0] - xPos;
			adj = a[2] - zPos;
			h = sqr(opp) + sqr(adj);
			h = sqrt(h);

			//If ray is inside triangle {
			if(h <= 100) {;
				//Get the rest of the triangle Data
				b[0] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][1])][0]*16;
				b[1] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][1])][1]*16;
				b[2] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][1])][2]*16;
				c[0] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][2])][0]*16;
				c[1] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][2])][1]*16;
				c[2] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][2])][2]*16;

			//	cout << "Checking: (" << a[0] << ", " << a[1] << ", " << a[2];
			//	cout << ") : (" << b[0] << ", " << b[1] << ", " << b[2];
			//	cout << ") : (" << c[0] << ", " << c[1] << ", " << c[2] << ")" << endl;

				//Projection of triangle onto the xz plane, we don't care about the height right now
				Vector3f testA, testB,testC, testP;
				testA[0] = a[0];
				testA[1] = 0;
				testA[2] = a[2];
				testB[0] = b[0];
				testB[1] = 0;
				testB[2] = b[2];
				testC[0] = c[0];
				testC[1] = 0;
				testC[2] = c[2];
				testP[0] = p[0];
				testP[1] = 0;
				testP[2] = p[2];

				/*
				 * Are we currently inside the projected triangle?
				 */
				if (PointInTriangle(testP, testA, testB, testC)) {
					/*
					 * We are inside the tested triangle
					 * Perform the intersection test to find our t value
					 * The t value is the intersection height of the triangle
					 * 	on the vertical ray.
					 */
					iResult=IntersectTri(p, q, a, c, b, u, v, w, t);
					newHeight = (iRayDepth-((2*iRayDepth)*t));
					foundHeight=true;
				}
			}
			if (foundHeight) {
				//cout << "----------------------------> FOUND IN UPPER TRI! " << newHeight << endl;
				break;
			}
		}

		/*
		 * Check lower triangles
		 */
		if (!foundHeight) {
			for (int i=iStartL; i < iEndL; i++) {
				//Get Triangle Data for current count
				//Get the triangle vertex data, for test point
				a[0] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][0])][0]*16;
				a[1] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][0])][1]*16;
				a[2] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][0])][2]*16;

				//Check distance from player, if within 200 units { (Only check one vertex, this will suffice)
				//Distance Calculations
				opp = a[0] - xPos;
				adj = a[2] - zPos;
				h = sqr(opp) + sqr(adj);
				h = sqrt(h);

				//If ray is inside triangle {
				if(h <= 100) {;
					//Get the rest of the triangle Data
					b[0] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][1])][0]*16;
					b[1] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][1])][1]*16;
					b[2] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][1])][2]*16;
					c[0] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][2])][0]*16;
					c[1] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][2])][1]*16;
					c[2] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][2])][2]*16;

				//	cout << "Checking: (" << a[0] << ", " << a[1] << ", " << a[2];
				//	cout << ") : (" << b[0] << ", " << b[1] << ", " << b[2];
				//	cout << ") : (" << c[0] << ", " << c[1] << ", " << c[2] << ")" << endl;

					//Projection of triangle onto the xz plane, we don't care about the height right now
					Vector3f testA, testB,testC, testP;
					testA[0] = a[0];
					testA[1] = 0;
					testA[2] = a[2];
					testB[0] = b[0];
					testB[1] = 0;
					testB[2] = b[2];
					testC[0] = c[0];
					testC[1] = 0;
					testC[2] = c[2];
					testP[0] = p[0];
					testP[1] = 0;
					testP[2] = p[2];

					/*
					 * Are we currently inside the projected triangle?
					 */
					if (PointInTriangle(testP, testA, testB, testC)) {
						/*
						 * We are inside the tested triangle
						 * Perform the intersection test to find our t value
						 * The t value is the intersection height of the triangle
						 * 	on the vertical ray.
						 */
						iResult=IntersectTri(p, q, a, c, b, u, v, w, t);
						newHeight = (iRayDepth-((2*iRayDepth)*t));
						foundHeight=true;
					}
				}
				if (foundHeight) {
					//cout << "----------------------------> FOUND IN LOWER TRI! " << newHeight << endl;
					break;
				}
			}
		}

		/*
		 * Last ditch effort, go through everything
		 */
		if (!foundHeight) {
			for (int i=0; i < mapData[xGrid][zGrid].numFaces; i++) {
				//Get Triangle Data for current count
				//Get the triangle vertex data, for test point
				a[0] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][0])][0]*16;
				a[1] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][0])][1]*16;
				a[2] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][0])][2]*16;

				//Check distance from player, if within 200 units { (Only check one vertex, this will suffice)
				//Distance Calculations
				opp = a[0] - xPos;
				adj = a[2] - zPos;
				h = sqr(opp) + sqr(adj);
				h = sqrt(h);

				//If ray is inside triangle {
				if(h <= 100) {;
					//Get the rest of the triangle Data
					b[0] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][1])][0]*16;
					b[1] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][1])][1]*16;
					b[2] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][1])][2]*16;
					c[0] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][2])][0]*16;
					c[1] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][2])][1]*16;
					c[2] = mapData[xGrid][zGrid].vVerts[int(mapData[xGrid][zGrid].vGroups[i][2])][2]*16;

					//Projection of triangle onto the xz plane, we don't care about the height right now
					Vector3f testA, testB,testC, testP;
					testA[0] = a[0];
					testA[1] = 0;
					testA[2] = a[2];
					testB[0] = b[0];
					testB[1] = 0;
					testB[2] = b[2];
					testC[0] = c[0];
					testC[1] = 0;
					testC[2] = c[2];
					testP[0] = p[0];
					testP[1] = 0;
					testP[2] = p[2];

					/*
					 * Are we currently inside the projected triangle?
					 */
					if (PointInTriangle(testP, testA, testB, testC)) {
						/*
						 * We are inside the tested triangle
						 * Perform the intersection test to find our t value
						 * The t value is the intersection height of the triangle
						 * 	on the vertical ray.
						 */
						iResult=IntersectTri(p, q, a, c, b, u, v, w, t);
						newHeight = (iRayDepth-((2*iRayDepth)*t));
						foundHeight=true;
					}
				}
				if (foundHeight) {
					//cout << "----------------------------> FOUND IN LAST DITCH! " << newHeight << endl;
					break;
				}
			}
		}

	/*
	 * The values in a, b, and c should be the last successful
	 *   attempt to find a height so lets just use those
	 *   values.
	 *
	 * If the y-value is negative then the vertex rotation is
	 *   probably backwards so lets just flip the normal
	 *   180 degrees.
	 */
	p[0] = b[0]-a[0];
	p[1] = b[1]-a[1];
	p[2] = b[2]-a[2];

	q[0] = c[0]-a[0];
	q[1] = c[1]-a[1];
	q[2] = c[2]-a[2];

	float * vTemp = new float[3];
	vTemp = Cross(p, q, true);

	/*
	 * This doesn't work at all
	 * I thought the handedness of
	 * the coordinate system needed
	 * to be accounted for.
	 *
	if(vTemp[1]<0.0f) {
		vTemp[0] = -vTemp[0];
		vTemp[1] = -vTemp[1];
		vTemp[2] = -vTemp[2];
	}*/

	//cout << "p: " << p[0] << ", " << p[1] << ", " << p[2] << "; q: " << q[0] << ", " << q[1] << ", " << q[2] << endl;
	//cout << "vTemp: " << vTemp[0] << ", " << vTemp[1] << ", " << vTemp[2] << ", " << newHeight << endl;

	vReturn[0] = vTemp[0];
	vReturn[1] = vTemp[1];
	vReturn[2] = vTemp[2];
	vReturn[3] = newHeight;

	delete[] vTemp;

	//return newHeight;
	return vReturn;
}

void WorldMap::reset(Atmosphere *a, std::string d) {
	cout << "Resetting Map Data...";
	//new(&atmosphere) Atmosphere(a);
	atmosphere = a;
	dir = d;
	//mapData = new MapData*[9];
	//for(int i=0; i<9; i++) {
	//	mapData[i] = new MapData[9];
	//}
	cout << "Done" << endl;
}

/*
 * Load map starting location and player location from file
 */
bool WorldMap::init() {
	try {
		if (gameVars->debug.load) printf("## INIT MAP ##\n");
		bool bReadResult;
		MemBlock memBlock;
		std::string loadFile;
		std::stringstream  *sStream = new std::stringstream;
		sStream->str("");
		*sStream << dir << "map.bin";
		loadFile=sStream->str();
		if (gameVars->debug.load) std::cout << " -Loading " <<  loadFile << "...";
		bReadResult = readFile(loadFile, memBlock); //Read the data file into memory
		std::string temp2 = itoa((unsigned char)memBlock.buffer[0], 10);

		__int16_t uiMx	=	(	(unsigned int)(memBlock.buffer[0]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[0]&0x0F)*256 +
												(unsigned int)(memBlock.buffer[1]&0xF0)				+ (unsigned int)(memBlock.buffer[1]&0x0F) );

		__int16_t uiMz	=	(	(unsigned int)(memBlock.buffer[2]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[2]&0x0F)*256 +
												(unsigned int)(memBlock.buffer[3]&0xF0)				+ (unsigned int)(memBlock.buffer[3]&0x0F) );

        // Reserved spot (Scale)
//        __int16_t uiLx	=	(	(unsigned int)(memBlock.buffer[4]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[4]&0x0F)*256 +
//                                (unsigned int)(memBlock.buffer[5]&0xF0)		+ (unsigned int)(memBlock.buffer[5]&0x0F) );

		__int16_t uiLx	=	(	(unsigned int)(memBlock.buffer[6]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[6]&0x0F)*256 +
												(unsigned int)(memBlock.buffer[7]&0xF0)				+ (unsigned int)(memBlock.buffer[7]&0x0F) );

        // Reserved spot
//        __int16_t uiLx	=	(	(unsigned int)(memBlock.buffer[8]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[8]&0x0F)*256 +
//                                (unsigned int)(memBlock.buffer[9]&0xF0)		+ (unsigned int)(memBlock.buffer[9]&0x0F) );

		__int16_t uiLz	=	(	(unsigned int)(memBlock.buffer[10]&0xF0)*256  + (unsigned int)(memBlock.buffer[10]&0x0F)*256 +
												(unsigned int)(memBlock.buffer[11]&0xF0)			+ (unsigned int)(memBlock.buffer[11]&0x0F) );

		vStart[0] = uiMx;
		vStart[1] = uiMz;
		gameVars->player.active->transform.pos[0]=-uiLx;
		gameVars->player.active->transform.pos[2]=-uiLz;

		//vStart[0]=(unsigned char)memBlock.buffer[0]+(unsigned char)memBlock.buffer[1];
		//vStart[1]=(unsigned char)memBlock.buffer[2]+(unsigned char)memBlock.buffer[3];
		//gameVars->player.active->transform.pos[0]=-((unsigned char)memBlock.buffer[4]+(unsigned char)memBlock.buffer[5]+(unsigned char)memBlock.buffer[6]+(unsigned char)memBlock.buffer[7]);
		//gameVars->player.active->transform.pos[2]=-((unsigned char)memBlock.buffer[8]+(unsigned char)memBlock.buffer[9]+(unsigned char)memBlock.buffer[10]+(unsigned char)memBlock.buffer[11]);

		cout << "=================================> (" << gameVars->player.active->transform.pos[0] << ", " << gameVars->player.active->transform.pos[2] << ")" << endl;
		gameVars->player.active->transform.pos[0]-=gameVars->screen.iGridOffset*1024;
		gameVars->player.active->transform.pos[2]-=gameVars->screen.iGridOffset*1024;
		cout << "=================================> (" << gameVars->player.active->transform.pos[0] << ", " << gameVars->player.active->transform.pos[2] << ")" << endl;
		delete sStream;
		if (gameVars->debug.load) std::cout << "Done." <<  std::endl;
	}
	catch(...) {
		return false;
	}
	return true;
}

/*
 * Load map at location, start at center of map
 */
bool WorldMap::init(int iSx, int iSz) {
	try {
		if (gameVars->debug.load) printf("## INIT MAP ##\n");
		vStart[0]=iSx;
		vStart[1]=iSz;
		//gameVars->player.active->transform.pos[0]=-512;
		gameVars->player.active->transform.pos[1]=0;
		//gameVars->player.active->transform.pos[2]=-512;
		gameVars->player.active->transform.pos[0]-=gameVars->screen.iGridOffset*1024;
		gameVars->player.active->transform.pos[2]-=gameVars->screen.iGridOffset*1024;
	}
	catch(...) {
		return false;
	}
	return true;
}

/*
 * Loda map at location and position player on map (teleport)
 */
bool WorldMap::init(int iSx, int iSz, int iPx, int iPy, int iPz) {
	try {
		if (gameVars->debug.load) printf("## INIT MAP ##\n");
		vStart[0]=iSx;
		vStart[1]=iSz;
		gameVars->player.active->transform.pos[0]=-iPx;
		gameVars->player.active->transform.pos[1]=iPy;
		gameVars->player.active->transform.pos[2]=-iPz;
		gameVars->player.active->transform.pos[0]-=gameVars->screen.iGridOffset*1024;
		gameVars->player.active->transform.pos[2]-=gameVars->screen.iGridOffset*1024;
	}
	catch(...) {
		return false;
	}
	return true;
}

bool WorldMap::load(int iShift=SHIFT_LAST) {
	try {
		if (gameVars->debug.load) printf("## LOAD MAP ##\n");

		bool bReadResult;
		//std::string loadFile = "";

		//################################
		//		Load Binary Map Data

		//The filename offset, ie. vStart[0]=100 then start loading from 98.
		int mapSx;
		int mapSz;
		int mapEx;
		int mapEz;

		int iOffset = gameVars->screen.iGridOffset;
		int iGrid = gameVars->screen.iTerrainGrid-iOffset;

		if (iShift==SHIFT_LAST) {
			mapSx=0;
			mapSz=0;
			mapEx=gameVars->screen.iTerrainGrid;
			mapEz=gameVars->screen.iTerrainGrid;
			vBase[0] = vStart[0]-gameVars->screen.iGridOffset;
			vBase[1] = vStart[1]-gameVars->screen.iGridOffset;
		}
		else if (iShift==SHIFT_UP) {
			//Load (x=0:iGrid, y=iGrid)
			mapSx=0;
			mapSz=0;
			mapEx=gameVars->screen.iTerrainGrid;
			mapEz=gameVars->screen.iTerrainGrid;
			//mapSx=0;								//Starting X coordinate
			//mapSz=gameVars->screen.iTerrainGrid-1;	//Starting Z coordinate
			//mapEx=gameVars->screen.iTerrainGrid;		//Ending X coordinate
			//mapEz=gameVars->screen.iTerrainGrid;		//Ending Z coordinate
			vStart[1]+=iOffset;
			vBase[0] = vStart[0]-gameVars->screen.iGridOffset;
			vBase[1] = vStart[1]-gameVars->screen.iGridOffset;
		}
		else if (iShift==SHIFT_DOWN) {
			//Load (x=0:iGrid, y=0)
			mapSx=0;
			mapSz=0;
			mapEx=gameVars->screen.iTerrainGrid;
			mapEz=gameVars->screen.iTerrainGrid;
			//mapSx=0;								//Starting X coordinate
			//mapSz=0;								//Starting Z coordinate
			//mapEx=gameVars->screen.iTerrainGrid;		//Ending X coordinate
			//mapEz=1;								//Ending Z coordinate
			vStart[1]-=iOffset;
			vBase[0] = vStart[0]-gameVars->screen.iGridOffset;
			vBase[1] = vStart[1]-gameVars->screen.iGridOffset;
		}
		else if (iShift==SHIFT_LEFT) {
			//Load (x=iGrid, y=0:iGrid)
			mapSx=0;
			mapSz=0;
			mapEx=gameVars->screen.iTerrainGrid;
			mapEz=gameVars->screen.iTerrainGrid;
			//mapSx=gameVars->screen.iTerrainGrid-1;	//Starting X coordinate
			//mapSz=0;								//Starting Z coordinate
			//mapEx=gameVars->screen.iTerrainGrid;		//Ending X coordinate
			//mapEz=gameVars->screen.iTerrainGrid;		//Ending Z coordinate
			vStart[0]+=iOffset;
			vBase[0] = vStart[0]-gameVars->screen.iGridOffset;
			vBase[1] = vStart[1]-gameVars->screen.iGridOffset;
		}
		else if (iShift==SHIFT_RIGHT) {
			//Load (x=0 , y=0:iGrid)
			mapSx=0;
			mapSz=0;
			mapEx=gameVars->screen.iTerrainGrid;
			mapEz=gameVars->screen.iTerrainGrid;
			//mapSx=0;								//Starting X coordinate
			//mapSz=0;								//Starting Z coordinate
			//mapEx=1;								//Ending X coordinate
			//mapEz=gameVars->screen.iTerrainGrid;		//Ending Z coordinate
			vStart[0]-=iOffset;
			vBase[0] = vStart[0]-gameVars->screen.iGridOffset;
			vBase[1] = vStart[1]-gameVars->screen.iGridOffset;
		}

		//Temporary index value
		int iX, iZ;

		//====> LOAD VERTEX POINTS
		for (int x=mapSx; x<mapEx; x++) {
			for (int z=mapSz; z<mapEz; z++) {
				//MemBlock * memBlock = new MemBlock;
				std::stringstream *sStream = new std::stringstream;

				iX=vBase[0]+x;
				iZ=vBase[1]+z;

				sStream->str("");
				*sStream << dir << iX << "-" << iZ << ".ply";
				//loadFile=sStream->str();

				if (gameVars->debug.load) cout << "> Loading " <<  sStream->str() << "...";
				//bReadResult = readFile(sStream->str(), *memBlock);		//Read the data file into memory
				bReadResult = readFile(sStream->str());		//Read the data file into memory
				if (!bReadResult) {
					sStream->str("");
					// TODO: Get number of random maps from "map.bin" in the future
					int iRand = (rand() % 5);
					*sStream << dir << "default/" << iRand << ".ply";
					//loadFile=sStream->str();
					cout << "Doesn't exist, loading [" << dir << "default/" << iRand << ".ply]...";
				}

				//delete &mapData[x][z];
				//delete mapData[x][z];
				//mapData[x][z] = new MapData;

				//new(&mapData[x][z]) MapData();
				PLY_Loader pLoad; // = new PLY_Loader;
				pLoad.load(sStream->str(), mapData[x][z]);
				//delete pLoad;
				delete sStream;
				//delete memBlock;
				if (gameVars->debug.load) std::cout << "Done." <<  std::endl;

//				if(x==0 and z==1) {
//					cout << "--------------------------------------> " << x << ", " << z;
//					cout << ": Begin LOD Setup:" << endl;
//					for(int i=0; i<mapData[x][z].numVerts; i++) {
//
//						//cout << to_string(mapData[x][z].vVerts[i][0]) << " | ";
//
//						if( Cmpff(mapData[x][z].vVerts[i][0], 64.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 62.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 60.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 58.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 56.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 54.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 52.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 50.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 48.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 46.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 44.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 42.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 40.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 38.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 36.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 34.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 32.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 30.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 28.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 26.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 24.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 22.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 20.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 18.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 16.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 14.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 12.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0], 10.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0],  8.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0],  6.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0],  4.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0],  2.0f) ||
//							Cmpff(mapData[x][z].vVerts[i][0],  0.0f) ) {
//
//							if( Cmpff(mapData[x][z].vVerts[i][2], 64.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 62.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 60.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 58.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 56.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 54.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 52.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 50.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 48.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 46.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 44.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 42.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 40.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 38.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 36.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 34.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 32.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 30.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 28.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 26.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 24.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 22.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 20.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 18.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 16.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 14.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 12.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2], 10.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2],  8.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2],  6.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2],  4.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2],  2.0f) ||
//								Cmpff(mapData[x][z].vVerts[i][2],  0.0f) ) {
//
//								cout << i << " (" << -mapData[x][z].vVerts[i][0] << ", " << mapData[x][z].vVerts[i][2] << ")" << endl;
//							}
//						}
//					}
//					cout << endl;
//				}
			}
		}
		return true;
	}
	catch(...) {
		return false;
	}
}

void WorldMap::shift(int iShift=SHIFT_LAST) {
	int iOffset = gameVars->screen.iGridOffset;
	int iGrid = gameVars->screen.iTerrainGrid-iOffset;
	if (iShift!=SHIFT_LAST) {
		switch (iShift) {
			case SHIFT_UP:
			/*
			for (int x=0;x<=iGrid; x++) {
				for (int y=iOffset;y<=iGrid; y++) {
					deepCopyMapData(&mapData[x][y], &mapData[x][y-iOffset]);
				}
			}*/
			load(SHIFT_UP);
			calc(false);
			break;
			case SHIFT_DOWN:
			/*
			for (int x=0;x<=iGrid; x++) {
				for (int y=iGrid-iOffset;y>=0; y--) {
					//deepCopyMapData(&mapData[x][y], &mapData[x][y+iOffset]);
				}
			}*/
			load(SHIFT_DOWN);
			calc(false);
			break;
			case SHIFT_LEFT:
			/*
			for (int y=0;y<=iGrid; y++) {
				for (int x=iOffset;x<=iGrid; x++) {
					//deepCopyMapData(&mapData[x][y], &mapData[x-iOffset][y]);
				}
			}*/
			load(SHIFT_LEFT);
			calc(false);
			break;
			case SHIFT_RIGHT:
			/*
			for (int y=0;y<=iGrid; y++) {
				for (int x=iGrid-iOffset;x>=0; x--) {
					//deepCopyMapData(&mapData[x][y], &mapData[x+iOffset][y]);
				}
			}*/
			load(SHIFT_RIGHT);
			calc(false);
			break;
		}
	}
}

void WorldMap::updateNorms(int x, int z) {
//Update the normals with the new mapData[][] information after modification
}

void WorldMap::stitch(unsigned int iStitch, int x, int z) {
	if (iStitch != STITCH_LAST) {
		switch (iStitch) {
			case STITCH_LEFT:
				cout << "Left...";
				//LEFT
				for (int x1=0; x1<=64; x1++) {
					int a_count=0;
					int b_count=0;
					int a_match[16] = {0x7FFF};
					int b_match[16] = {0x7FFF};

					for (int i=1; i<mapData[x][z].numVerts; i++) {
						if (Cmpfi(mapData[x][z].vVerts[i][0],0, 0.4f)) {
							if(Cmpfi(mapData[x][z].vVerts[i][2],x1, 0.4f)) {
								mapData[x][z].vVerts[i][0]=0;
								mapData[x][z].vVerts[i][2]=x1;
								a_match[a_count] = i;
								a_count++;
							}
						}
					}
					for (int i=0; i<mapData[x-1][z].numVerts; i++) {
						if (Cmpfi(mapData[x-1][z].vVerts[i][0],64, 0.4f)) {
							if (Cmpfi(mapData[x-1][z].vVerts[i][2],x1, 0.4f)) {
								mapData[x-1][z].vVerts[i][0]=64;
								mapData[x-1][z].vVerts[i][2]=x1;
								b_match[b_count] = i;
								b_count++;
							}
						}
					}

					//Calculate Differences
					float t=0;
					bool bFail=false;
					for (int a=0; a<a_count; a++) {
						if (!Cmpff(mapData[x][z].vVerts[a_match[a]][1], t, 50.0f)) bFail = true;
						if (a_match[a]!=0x7FFF) t = t + mapData[x][z].vVerts[a_match[a]][1];
					}
					for (int b=0; b<b_count; b++) {
						if (!Cmpff(mapData[x-1][z].vVerts[b_match[b]][1], t, 50.0f)) bFail = true;
						if (b_match[b]!=0x7FFF) t = t + mapData[x-1][z].vVerts[b_match[b]][1];
					}

					if(!bFail) {
						t = t/(a_count+b_count);
						//t = t/2;
						//Apply Stitching
						for (int a=0; a<a_count; a++) {
							if (a_match[a]!=0x7FFF) mapData[x][z].vVerts[a_match[a]][1]=t;
						}
						for (int b=0; b<b_count; b++) {
							if (b_match[b]!=0x7FFF) mapData[x-1][z].vVerts[b_match[b]][1]=t;
						}

						//Recalculate Normals
						for (int ax=0; ax<=2; ax++) {
							//Calculate Differences
							t=0;
							for (int a=0; a<a_count; a++) {
								if (a_match[a]!=0x7FFF) t = t + mapData[x][z].vNorms[a_match[a]][ax];
							}
							for (int b=0; b<b_count; b++) {
								if (a_match[b]!=0x7FFF) t = t + mapData[x-1][z].vNorms[b_match[b]][ax];
							}
							t = t/(a_count+b_count);
							//t = t/2;

							//Apply Stitching
							for (int a=0; a<a_count; a++) {
								if (a_match[a]!=0x7FFF) mapData[x][z].vNorms[a_match[a]][ax]=t;
							}
							for (int b=0; b<b_count; b++) {
								if (a_match[b]!=0x7FFF) mapData[x-1][z].vNorms[b_match[b]][ax]=t;
							}
						}
					}
				}
				break;

			case STITCH_TOP:
				cout << "Top...";
				//TOP
				for (int x1=1; x1<=64; x1++) {
					int a_count=0;
					int b_count=0;
					int a_match[16] = {0x7FFF};
					int b_match[16] = {0x7FFF};

					for (int i=0; i<mapData[x][z].numVerts; i++) {
						if (Cmpfi(mapData[x][z].vVerts[i][0],x1, 0.4f)) {
							if (Cmpfi(mapData[x][z].vVerts[i][2],0, 0.4f)) {
								mapData[x][z].vVerts[i][0]=x1;
								mapData[x][z].vVerts[i][2]=0;
								a_match[a_count] = i;
								a_count++;
							}
						}
					}
					for (int i=0; i<mapData[x][z-1].numVerts; i++) {
						if (Cmpfi(mapData[x][z-1].vVerts[i][0],x1, 0.4f)) {
							if (Cmpfi(mapData[x][z-1].vVerts[i][2],64, 0.4f)) {
								mapData[x][z-1].vVerts[i][0]=x1;
								mapData[x][z-1].vVerts[i][2]=64;
								b_match[b_count] = i;
								b_count++;
							}
						}
					}

					//Calculate Differences
					float t=0;
					for (int a=0; a<a_count; a++) {
						if (a_match[a]!=0x7FFF) t = t + mapData[x][z].vVerts[a_match[a]][1];
					}
					for (int b=0; b<b_count; b++) {
						if (a_match[b]!=0x7FFF) t = t + mapData[x][z-1].vVerts[b_match[b]][1];
					}
					t = t/(a_count+b_count);
					//t = t/2;

					//Apply Stitching
					for (int a=0; a<a_count; a++) {
						if (a_match[a]!=0x7FFF) mapData[x][z].vVerts[a_match[a]][1]=t;
					}
					for (int b=0; b<b_count; b++) {
						if (a_match[b]!=0x7FFF) mapData[x][z-1].vVerts[b_match[b]][1]=t;
					}

					//Recalculate Normals
					//Calculate Differences
					for (int ax=0; ax<=2; ax++) {
						t=0;
						for (int a=0; a<a_count; a++) {
							if (a_match[a]!=0x7FFF) t = t + mapData[x][z].vNorms[a_match[a]][ax];
						}
						for (int b=0; b<b_count; b++) {
							if (a_match[b]!=0x7FFF) t = t + mapData[x][z-1].vNorms[b_match[b]][ax];
						}
						t = t/(a_count+b_count);
						//t = t/2;

						//Apply Stitching
						for (int a=0; a<a_count; a++) {
							if (a_match[a]!=0x7FFF) mapData[x][z].vNorms[a_match[a]][ax]=t;
						}
						for (int b=0; b<b_count; b++) {
							if (a_match[b]!=0x7FFF) mapData[x][z-1].vNorms[b_match[b]][ax]=t;
						}
					}

				}
				break;

			case STITCH_RIGHT:
				cout << "Right...";
				//RIGHT
				/* GLITCH CAUSED HERE!!!
				 * GLITCH CAUSED HERE!!!
				 * 		If (int x1=0) is used then a glitch occurrs with a triangle spike going into the sky
				 * GLITCH CAUSED HERE!!!
				 * GLITCH CAUSED HERE!!!
				 */
				for (int x1=0; x1<=64; x1++) {
					int a_count=0;
					int b_count=0;
					int a_match[16] = {0x7FFF};
					int b_match[16] = {0x7FFF};

					/* GLITCH CAUSED HERE!!!
					 * GLITCH CAUSED HERE!!!
					 * 		The following block of code makes the glitch
					 * 		appear by setting the values equal to what
					 * 		they are compared to.
					 * GLITCH CAUSED HERE!!!
					 * GLITCH CAUSED HERE!!!
					 */
					for (int i=0; i<mapData[x][z].numVerts; i++) {
						if (Cmpfi(mapData[x][z].vVerts[i][0],64, 0.4f)) {
							if (Cmpfi(mapData[x][z].vVerts[i][2],x1, 0.4f)) {
								mapData[x][z].vVerts[i][0]=64;
								mapData[x][z].vVerts[i][2]=x1;
								a_match[a_count] = i;
								a_count++;
							}
						}
					}
					for (int i=0; i<mapData[x+1][z].numVerts; i++) {
						if (Cmpfi(mapData[x+1][z].vVerts[i][0],0, 0.4f)) {
							if (Cmpfi(mapData[x+1][z].vVerts[i][2],x1, 0.4f)) {
								mapData[x+1][z].vVerts[i][0]=0;
								mapData[x+1][z].vVerts[i][2]=x1;
								b_match[b_count] = i;
								b_count++;
							}
						}
					}

					//Calculate Differences
					float t=0;
					bool bFail = false;
					for (int a=0; a<a_count; a++) {
						if (!Cmpff(mapData[x][z].vVerts[a_match[a]][1], t, 50.0f)) bFail = true;
						if (a_match[a]!=0x7FFF) t = t + mapData[x][z].vVerts[a_match[a]][1];
					}
					for (int b=0; b<b_count; b++) {
						if (!Cmpff(mapData[x+1][z].vVerts[b_match[b]][1], t, 50.0f)) bFail = true;
						if (a_match[b]!=0x7FFF) t = t + mapData[x+1][z].vVerts[b_match[b]][1];
					}

					if(!bFail) {
						t = t/(a_count+b_count);
						//t = t/2;
						//Apply Stitching
						for (int a=0; a<a_count; a++) {
							if (a_match[a]!=0x7FFF) mapData[x][z].vVerts[a_match[a]][1]=t;
						}
						for (int b=0; b<b_count; b++) {
							if (a_match[b]!=0x7FFF) mapData[x+1][z].vVerts[b_match[b]][1]=t;
						}

						//Recalculate Normals
						//Calculate Differences
						for (int ax=0; ax<=2; ax++) {
							t=0;
							for (int a=0; a<a_count; a++) {
								if (a_match[a]!=0x7FFF) t = t + mapData[x][z].vNorms[a_match[a]][ax];
							}
							for (int b=0; b<b_count; b++) {
								if (a_match[b]!=0x7FFF) t = t + mapData[x+1][z].vNorms[b_match[b]][ax];
							}
							t = t/(a_count+b_count);
							//t = t/2;

							//Apply Stitching
							for (int a=0; a<a_count; a++) {
								if (a_match[a]!=0x7FFF) mapData[x][z].vNorms[a_match[a]][ax]=t;
							}
							for (int b=0; b<b_count; b++) {
								if (a_match[b]!=0x7FFF) mapData[x+1][z].vNorms[b_match[b]][ax]=t;
							}
						}
					}
				}
				break;

			case STITCH_BOTTOM:
				cout << "Bottom...";
				//BOTTOM
				for (int x1=1; x1<=64; x1++) {
					int a_count=0;
					int b_count=0;
					int a_match[16] = {0x7FFF};
					int b_match[16] = {0x7FFF};

					for (int i=0; i<mapData[x][z].numVerts; i++) {
						if (Cmpfi(mapData[x][z].vVerts[i][0],x1, 0.4f)) {
							if (Cmpfi(mapData[x][z].vVerts[i][2],64, 0.4f)) {
								mapData[x][z].vVerts[i][0]=x1;
								mapData[x][z].vVerts[i][2]=64;
								a_match[a_count] = i;
								a_count++;
							}
						}
					}
					for (int i=0; i<mapData[x][z+1].numVerts; i++) {
						if (Cmpfi(mapData[x][z+1].vVerts[i][0],x1, 0.4f)) {
							if (Cmpfi(mapData[x][z+1].vVerts[i][2],0, 0.4f)) {
								mapData[x][z+1].vVerts[i][0]=x1;
								mapData[x][z+1].vVerts[i][2]=0;
								b_match[b_count] = i;
								b_count++;
							}
						}
					}

					//Calculate Differences
					float t;
					for (int a=0; a<a_count; a++) {
						if (a_match[a]!=0x7FFF) t = t + mapData[x][z].vVerts[a_match[a]][1];
					}
					for (int b=0; b<b_count; b++) {
						if (a_match[b]!=0x7FFF) t = t + mapData[x][z+1].vVerts[b_match[b]][1];
					}
					t = t/(a_count+b_count);
					//t = t/2;

					//Apply Stitching
					for (int a=0; a<a_count; a++) {
						if (a_match[a]!=0x7FFF) mapData[x][z].vVerts[a_match[a]][1]=t;
					}
					for (int b=0; b<b_count; b++) {
						if (a_match[b]!=0x7FFF) mapData[x][z+1].vVerts[b_match[b]][1]=t;
					}

					//Recalculate Normals
					//Calculate Differences
					for (int ax=0; ax<=2; ax++) {
						t=0;
						for (int a=0; a<a_count; a++) {
							if (a_match[a]!=0x7FFF) t = t + mapData[x][z].vNorms[a_match[a]][ax];
						}
						for (int b=0; b<b_count; b++) {
							if (a_match[b]!=0x7FFF) t = t + mapData[x][z+1].vNorms[b_match[b]][ax];
						}
						t = t/(a_count+b_count);
						//t = t/2;

						//Apply Stitching
						for (int a=0; a<a_count; a++) {
							if (a_match[a]!=0x7FFF) mapData[x][z].vNorms[a_match[a]][ax]=t;
						}
						for (int b=0; b<b_count; b++) {
							if (a_match[b]!=0x7FFF) mapData[x][z+1].vNorms[b_match[b]][ax]=t;
						}
					}

				}
				break;
		}
	}
}

bool WorldMap::calc(bool bUpdate=false) {
//Do general map calculations, this is done one time at map loading
	if (gameVars->debug.load) std::cout << "## CALC MAP ##" << endl;
	//if (gameVars->debug.runworld_map_calc) cout << "============ WolrdMap::calc"<< endl;

	//TODO: Make this faster if still used

//	cout << "Stitching disabled: map.h, 1324" << endl;

	if(gameVars->debug.stitchMap) {
		int iG = gameVars->screen.iTerrainGrid-1;
		for (int x=0; x<=iG; x++) {
			for (int z=0; z<=iG; z++) {
				cout << "Stitch: " << x << ", " << z << " : ";
				if (x==0 && z==0) 						{ stitch(STITCH_RIGHT,	x, z);	stitch(STITCH_BOTTOM,	x, z);	}
				else if (x==iG && z==0)  				{ stitch(STITCH_LEFT,	x, z);	stitch(STITCH_BOTTOM,	x, z);	}
				else if (x==0 && z==iG)  				{ stitch(STITCH_TOP,	x, z);	stitch(STITCH_RIGHT,	x, z);	}
				else if (x==iG && z==iG)  				{ stitch(STITCH_LEFT,	x, z);	stitch(STITCH_TOP,		x, z);	}
				else if (x>0 && x<iG && z>0 && z<iG)	{ stitch(STITCH_LEFT,	x, z);	stitch(STITCH_RIGHT,	x, z);	stitch(STITCH_TOP,	x, z);	stitch(STITCH_BOTTOM, x, z);	}
				cout << "Done." << endl;
			}
		}
	}

//RECALCULATE NORMALS
//Do we need to do this? Lets try setting up the phong shader first

	//Register the data
	for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
		for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {
			if (bUpdate) {
				// todo: Make sure this works, added the * due to a compiler warning
				new(*&mapData[x][z].vao) VAO();	//We need to create new VAO objects for this to work
				//delete mapData[x][z].vao;
				//mapData[x][z].vao = new VAO;

				//mapData[x][z].vao->Begin(GL_TRIANGLES, mapData[x][z].numDrawVerts, 8);
				//mapData[x][z].vao->CopyData(GLA_VERTEX, mapData[x][z].vVerts);
				//mapData[x][z].vao->CopyData(GLA_NORMAL, mapData[x][z].vNorms);
				//mapData[x][z].vao->CopyData(GLA_TEXTURE, mapData[x][z].vCoords, 0);
				//mapData[x][z].vao->CopyData(GLA_INDEX, mapData[x][z].vIndex);
				//mapData[x][z].vao->End();
			}
			else {

				/*
				 * New VAO created in mapdata struct with reset function
				 * called from ply_loader.
				 */
				//if(mapData[x][z].vao->bStarted) {
					//cout << "Destroy Old World...";
					//new(&mapData[x][z].vao) VAO();
					//new(&mapData[x][z].vao) VAO();
	//				mapData[x][z].vao = new VAO();
					//cout << "Done" << endl;
				//}
				//delete mapData[x][z].vao;
				//mapData[x][z].vao = new VAO;

				// TODO: LOD testing, redefine index array
				uint uiINDEXES_02;
				if(x==0 && z==2) {
					cout << "Remap Index for LOD test..." << endl;
					ushort * vNew;
					vNew = new ushort[mapData[x][z].numDrawVerts];
					const uint uiMAPSIZE			= 64;								// Number of quads to a side
					const uint uiLOD					= 2;								// Inverse LOD value, higher = lower detail
					const uint uiVOFFSET			= 256;							// Vertical index offset for one quad
					const uint uiVNEXT				= 256 * (uiLOD-1);	// Vertical index offset for LOD
										 uiINDEXES_02		= 6 * ((uiMAPSIZE/uiLOD)*(uiMAPSIZE/uiLOD));

					uint c = 0;
					for(uint yy=0; yy<uiMAPSIZE-1; yy+=uiLOD) {		// == row
						for(uint xx=0; xx<256; xx+=(4*uiLOD)) {
							uint i = xx + ( yy * (uiVOFFSET) );
							vNew[c]			= i;													// 0			//
							vNew[c+1]		= i+(1+uiVNEXT);							// 769		//
							vNew[c+2]		= i+(4*uiLOD-2);							// 14			//

							vNew[c+3] 	= i+(4*uiLOD-2);							// 14			//
							vNew[c+4]		= i+(1+uiVNEXT);							// 769		//
							vNew[c+5]		= i+((4*uiLOD-1)+uiVNEXT);		// 783		//

							c+=6;
						}
					}
					mapData[x][z].vIndex = vNew;
					cout << "Done" << endl;
				}

				uint uiINDEXES_01;
				if(x==0 && z==1) {
					cout << "Remap Index for LOD test..." << endl;
					ushort * vNew;
					vNew = new ushort[mapData[x][z].numDrawVerts];
					const uint uiMAPSIZE			= 64;								// Number of quads to a side
					const uint uiLOD					= 4;								// Inverse LOD value, higher = lower detail
					const uint uiVOFFSET			= 256;							// Vertical index offset for one quad
					const uint uiVNEXT				= 256 * (uiLOD-1);	// Vertical index offset for LOD
										 uiINDEXES_01		= 6 * ((uiMAPSIZE/uiLOD)*(uiMAPSIZE/uiLOD));

					uint c = 0;
					for(uint yy=0; yy<uiMAPSIZE-1; yy+=uiLOD) {		// == row
						for(uint xx=0; xx<256; xx+=(4*uiLOD)) {
							uint i = xx + ( yy * (uiVOFFSET) );
							vNew[c]			= i;													// 0			//
							vNew[c+1]		= i+(1+uiVNEXT);							// 769		//
							vNew[c+2]		= i+(4*uiLOD-2);							// 14			//

							vNew[c+3] 	= i+(4*uiLOD-2);							// 14			//
							vNew[c+4]		= i+(1+uiVNEXT);							// 769		//
							vNew[c+5]		= i+((4*uiLOD-1)+uiVNEXT);		// 783		//

							c+=6;
						}
					}
					mapData[x][z].vIndex = vNew;
					cout << "Done" << endl;
				}

				uint uiINDEXES_00;
				if(x==0 && z==0) {
					cout << "Remap Index for LOD test..." << endl;
					ushort * vNew;
					vNew = new ushort[mapData[x][z].numDrawVerts];
					const uint uiMAPSIZE			= 64;								// Number of quads to a side
					const uint uiLOD					= 8;								// Inverse LOD value, higher = lower detail
					const uint uiVOFFSET			= 256;							// Vertical index offset for one quad
					const uint uiVNEXT				= 256 * (uiLOD-1);	// Vertical index offset for LOD
										 uiINDEXES_00		= 6 * ((uiMAPSIZE/uiLOD)*(uiMAPSIZE/uiLOD));

					uint c = 0;
					for(uint yy=0; yy<uiMAPSIZE-1; yy+=uiLOD) {		// == row
						for(uint xx=0; xx<256; xx+=(4*uiLOD)) {
							uint i = xx + ( yy * (uiVOFFSET) );
							vNew[c]			= i;													// 0			//
							vNew[c+1]		= i+(1+uiVNEXT);							// 769		//
							vNew[c+2]		= i+(4*uiLOD-2);							// 14			//

							vNew[c+3] 	= i+(4*uiLOD-2);							// 14			//
							vNew[c+4]		= i+(1+uiVNEXT);							// 769		//
							vNew[c+5]		= i+((4*uiLOD-1)+uiVNEXT);		// 783		//

							c+=6;
						}
					}
					mapData[x][z].vIndex = vNew;
					cout << "Done" << endl;
				}

				uint uiINDEXES_10;
				if(x==1 && z==0) {
					cout << "Remap Index for LOD test..." << endl;
					ushort * vNew;
					vNew = new ushort[mapData[x][z].numDrawVerts];
					const uint uiMAPSIZE			= 64;								// Number of quads to a side
					const uint uiLOD					= 16;								// Inverse LOD value, higher = lower detail
					const uint uiVOFFSET			= 256;							// Vertical index offset for one quad
					const uint uiVNEXT				= 256 * (uiLOD-1);	// Vertical index offset for LOD
										 uiINDEXES_10		= 6 * ((uiMAPSIZE/uiLOD)*(uiMAPSIZE/uiLOD));

					uint c = 0;
					for(uint yy=0; yy<uiMAPSIZE-1; yy+=uiLOD) {		// == row
						for(uint xx=0; xx<256; xx+=(4*uiLOD)) {
							uint i = xx + ( yy * (uiVOFFSET) );
							vNew[c]			= i;													// 0			//
							vNew[c+1]		= i+(1+uiVNEXT);							// 769		//
							vNew[c+2]		= i+(4*uiLOD-2);							// 14			//

							vNew[c+3] 	= i+(4*uiLOD-2);							// 14			//
							vNew[c+4]		= i+(1+uiVNEXT);							// 769		//
							vNew[c+5]		= i+((4*uiLOD-1)+uiVNEXT);		// 783		//

							c+=6;
						}
					}
					mapData[x][z].vIndex = vNew;
					cout << "Done" << endl;
				}

				mapData[x][z].vao->Begin(GL_TRIANGLES, mapData[x][z].numDrawVerts, 8);
				mapData[x][z].vao->CopyData(GLA_VERTEX, mapData[x][z].vVerts);
				mapData[x][z].vao->CopyData(GLA_NORMAL, mapData[x][z].vNorms);
				mapData[x][z].vao->CopyData(GLA_TEXTURE, mapData[x][z].vCoords, 0);
				if(x==0 && z==0) {
					mapData[x][z].vao->CopyData(GLA_INDEX, mapData[x][z].vIndex, uiINDEXES_00);
				} else if(x==0 && z==1) {
					mapData[x][z].vao->CopyData(GLA_INDEX, mapData[x][z].vIndex, uiINDEXES_01);
				} else if(x==0 && z==2) {
					mapData[x][z].vao->CopyData(GLA_INDEX, mapData[x][z].vIndex, uiINDEXES_02);
				} else if(x==1 && z==0) {
					mapData[x][z].vao->CopyData(GLA_INDEX, mapData[x][z].vIndex, uiINDEXES_10);
				} else {
					mapData[x][z].vao->CopyData(GLA_INDEX, mapData[x][z].vIndex);
				}

				mapData[x][z].vao->End();
				cout << "Done" << endl;
			}
		}
	}
	if (gameVars->debug.load) printf("DONE");

	//std::terminate();

	//We really can't fail here unless something external is modified, go ahead and return a success
	return true;
}

void WorldMap::modify(MOD_VAL eMod, float fNewVal) {
//Modify the values stored in mapData[][]
}

void WorldMap::update(int iGridx, int iGridz) {
// Put the new mapData[][] values in to the VAO
}

void WorldMap::draw(int iShader) {
	glActiveTexture(GL_TEXTURE0);
	gameVars->texture.terrain.Set("dirt1.png");

	glActiveTexture(GL_TEXTURE1);
	gameVars->texture.terrain.Set("grass1.png");

	glActiveTexture(GL_TEXTURE2);
	gameVars->texture.terrain.Set("rocky1.png");

	glActiveTexture(GL_TEXTURE3);
	gameVars->texture.terrain.Set("cliff1.png");

	glActiveTexture(GL_TEXTURE4);
	gameVars->texture.terrain.Set("dirt2.png");

	glActiveTexture(GL_TEXTURE5);
	gameVars->texture.terrain.Set("grass2.png");

	glActiveTexture(GL_TEXTURE6);
	gameVars->texture.terrain.Set("rocky2.png");

	glActiveTexture(GL_TEXTURE7);
	gameVars->texture.terrain.Set("cliff2.png");

	glActiveTexture(GL_TEXTURE8);
	atmosphere->water.tex.Set(atmosphere->water.sWorld);

	glActiveTexture(GL_TEXTURE0);

	Core.shader.use(iShader);
	for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
		for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {
			Core.matrix.Push();
				Core.matrix.Translate(x*1024*gameVars->screen.iScale, 0, z*1024*gameVars->screen.iScale);
				Core.matrix.Scale(16*gameVars->screen.iScale, 16*gameVars->screen.iScale, 16*gameVars->screen.iScale);
				Core.matrix.SetTransform();
				Core.shader.getUniform(*atmosphere, iShader);
				//	if(bOcclude) occlusion.StartQuery("World Map", iNum);
						mapData[x][z].vao->Draw(GLM_DRAW_ELEMENTS);
				//	if(bOcclude) occlusion.EndQuery("World Map", iNum);
			Core.matrix.Pop();
		}
	}
}
#endif /* WORLDMAP_H_ */
