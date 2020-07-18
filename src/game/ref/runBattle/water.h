/*
 * O2D.h
 *
 *  Created on: Nov 1, 2010
 *      Author: bcthund
 */

#ifndef O2D_H_
#define O2D_H_

class O2D_BASE {
	private:
		//VAO vao[9][9][256];

	protected:

	public:
		O2dData data[9][9];
		O2DGroups group[9][9];
		Atmosphere &atmosphere;		//The parents atmosphere
		bool init();
		void clear();
		bool calc(bool bUpdate);
		void draw(int iShader, bool bSort);
		O2D_BASE(Atmosphere &a): atmosphere(a) {}
};

/*
 * O2D For world
 */
class O2D:public O2D_BASE {
	private:
		WorldMap &map;			//The parent MapData structure

	public:
		bool load(int iShift);
		void shift(int iShift);
		bool calc(bool bUpdate);
		O2D(WorldMap &m, Atmosphere &a): O2D_BASE(a), map(m) {}
		~O2D() {
			cout << "Destroy O2D...Done" << endl;
		}
};

void O2D_BASE::clear() {
	for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
		for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {
			data[x][z].idcount = -1;
		}
	}
}

class O2DD:public O2D_BASE {
	private:
		//float height(float iX, float iZ, int gX, int gZ, MapData &Map);
		DungeonMap &parent;			//The parent MapData structure

	protected:

	public:
		O2DD(DungeonMap &f, Atmosphere &a): O2D_BASE(a), parent(f) {}
};

bool O2D_BASE::init() {
	if (gameVars->debug.load) printf("## INIT O2D ##\n");
	if (gameVars->debug.load) printf("Nothing to do.\n");
	return true;
}

void O2D::shift(int iShift) {
	cout << endl << "Shifting o2d..." << endl;
	int iOffset = gameVars->screen.iGridOffset;
	int iGrid = gameVars->screen.iTerrainGrid-iOffset;
	//clear();
	switch (iShift) {
		case SHIFT_LAST:
			//Do Nothing for SHIFT_LAST
			// Others:
			//  * DEEPCOPY LIKE MAP
			//  * LOAD O2D
			//  * CALC O2D
			load(SHIFT_LAST);
			calc(false);
			break;
		case SHIFT_UP:
			//for (int x=0;x<=iGrid; x++) {
			//	for (int y=iOffset;y<=iGrid; y++) {
			//		CopyO2dData(&data[x][y], &data[x][y-iOffset]);
			//		cout << "Shifting From (" << x << "," << y << ") to (" << x << "," << y-iOffset  << ")" << endl;
			//	}
			//}
			load(SHIFT_UP);
			calc(true);
			break;
		case SHIFT_DOWN:
			//for (int x=0;x<=iGrid; x++) {
			//	for (int y=iGrid-iOffset;y>=0; y--) {
			//		CopyO2dData(&data[x][y], &data[x][y+iOffset]);
			//		cout << "Shifting From (" << x << "," << y << ") to (" << x << "," << y+iOffset  << ")" << endl;
			//	}
			//}
			load(SHIFT_DOWN);
			calc(true);
			break;
		case SHIFT_LEFT:
			//for (int y=0;y<=iGrid; y++) {
			//	for (int x=iOffset;x<=iGrid; x++) {
			//		CopyO2dData(&data[x][y], &data[x-iOffset][y]);
			//		cout << "Shifting From (" << x << "," << y << ") to (" << x-iOffset << "," << y  << ")" << endl;
			//	}
			//}
			load(SHIFT_LEFT);
			calc(true);
			break;
		case SHIFT_RIGHT:
			//for (int y=0;y<=iGrid; y++) {
			//	for (int x=iGrid-iOffset;x>=0; x--) {
			//		CopyO2dData(&data[x][y], &data[x+iOffset][y]);
			//		cout << "Shifting From (" << x << "," << y << ") to (" << x+iOffset << "," << y  << ")" << endl;
			//	}
			//}
			load(SHIFT_RIGHT);
			calc(true);
			break;
	}
}

bool O2D::load(int iShift=SHIFT_LAST) {
	try
	{
		//if (iShift==SHIFT_LAST) {
			//if (gameVars->debug.load) printf("\n ###################\n");
			if (gameVars->debug.load) printf("## LOAD O2D\n");
			bool bReadResult;
			MemBlock memBlock;
			std::string loadFile;
			std::stringstream *sStream = new std::stringstream;
			//################################
			//		Load Binary Map Data

			//The filename offset, ie. startX=100 then start loading from 98.
			int mapSx;
			int mapSz;
			int mapEx;
			int mapEz;
			int baseX;
			int baseZ;

			/*  WE DO NOT NEED TO MODIFY GAMEVARS, THIS IS DONE ELSEWHERE (map.h) */
			if (iShift==SHIFT_LAST) {
				mapSx=0;
				mapSz=0;
				mapEx=gameVars->screen.iTerrainGrid;
				mapEz=gameVars->screen.iTerrainGrid;
				baseX=0;
				baseZ=0;
			}
			else if (iShift==SHIFT_UP) {
				//Load (x=0:iGrid, y=iGrid)
				mapSx=0;								//Starting X coordinate
				mapSz=gameVars->screen.iTerrainGrid-1;	//Starting Z coordinate
				mapEx=gameVars->screen.iTerrainGrid;		//Ending X coordinate
				mapEz=gameVars->screen.iTerrainGrid;		//Ending Z coordinate
				baseX=0;
				baseZ=0;
			}
			else if (iShift==SHIFT_DOWN) {
				//Load (x=0:iGrid, y=0)
				mapSx=0;								//Starting X coordinate
				mapSz=0;								//Starting Z coordinate
				mapEx=gameVars->screen.iTerrainGrid;		//Ending X coordinate
				mapEz=1;								//Ending Z coordinate
				baseX=0;
				baseZ=0;
			}
			else if (iShift==SHIFT_LEFT) {
				//Load (x=iGrid, y=0:iGrid)
				mapSx=gameVars->screen.iTerrainGrid-1;	//Starting X coordinate
				mapSz=0;								//Starting Z coordinate
				mapEx=gameVars->screen.iTerrainGrid;		//Ending X coordinate
				mapEz=gameVars->screen.iTerrainGrid;		//Ending Z coordinate
				baseX=0;
				baseZ=0;
			}
			else if (iShift==SHIFT_RIGHT) {
				//Load (x=0 , y=0:iGrid)
				mapSx=0;								//Starting X coordinate
				mapSz=0;								//Starting Z coordinate
				mapEx=1;								//Ending X coordinate
				mapEz=gameVars->screen.iTerrainGrid;		//Ending Z coordinate
				baseX=0;
				baseZ=0;
			}

			//Temporary index value
			int iX, iZ;
			int idcount=0;

			for (int x=mapSx; x<mapEx; x++) {
				idcount=0;
				for (int z=mapSz; z<mapEz; z++) {
					iX=map.vBase[0]+x+baseX;
					iZ=map.vBase[1]+z+baseZ;
					idcount=0;

					//################################
					//		Load Binary Object Data
					sStream->str("");
					*sStream << map.dir << "o2d/" << iX << "-" << iZ << ".o2d";
					loadFile=sStream->str();
					if (gameVars->debug.load) cout << " -Loading " << loadFile << "...";
					//if (gameVars->debug.load) cout << gameVars->dir.o2d << iX << "-" << iZ << ".o2d" << endl;
					bReadResult = readFile(loadFile, memBlock);		//Read the data file into memory
					if (!bReadResult) {
						sStream->str("");
						*sStream << map.dir << "o2d/" << "0-0.o2d";
						loadFile=sStream->str();
						readFile(loadFile, memBlock);
					}

					if (memBlock.size <= 0) data[x][z].idcount = -1;
						for (int d=0; d<memBlock.size; d+=gameVars->recordSize.o2d) {
							data[x][z].idcount = idcount;
							data[x][z].id[idcount]		=	(	(unsigned char)memBlock.buffer[0+d]+
																						(unsigned char)memBlock.buffer[1+d]+
																						(unsigned char)memBlock.buffer[2+d]+
																						(unsigned char)memBlock.buffer[3+d]);

							data[x][z].x[idcount]		=		(unsigned char)memBlock.buffer[8+d]+1;
							data[x][z].x[idcount]		+=		(unsigned char)memBlock.buffer[9+d]+1;
							data[x][z].x[idcount]		+=		(unsigned char)memBlock.buffer[10+d]+1;
							data[x][z].x[idcount]		+=		(unsigned char)memBlock.buffer[11+d]+1;
							data[x][z].x[idcount]		+=		x*1024;

							data[x][z].z[idcount]		=		(unsigned char)memBlock.buffer[12+d]+1;
							data[x][z].z[idcount]		+=		(unsigned char)memBlock.buffer[13+d]+1;
							data[x][z].z[idcount]		+=		(unsigned char)memBlock.buffer[14+d]+1;
							data[x][z].z[idcount]		+=		(unsigned char)memBlock.buffer[15+d]+1;
							data[x][z].z[idcount]		+=		z*1024;

							/*
							 * Bits 16+17 are positive blending
							 * Bits 18+19 are negative blending
							 */
							data[x][z].blend[idcount]	=	(	(unsigned char)memBlock.buffer[16+d]+
																						(unsigned char)memBlock.buffer[17+d]-
																						(unsigned char)memBlock.buffer[18+d]-
																						(unsigned char)memBlock.buffer[19+d]);

							data[x][z].imgW[idcount]	=	(	(unsigned char)memBlock.buffer[20+d]+
																						(unsigned char)memBlock.buffer[21+d]+
																						(unsigned char)memBlock.buffer[22+d]+
																						(unsigned char)memBlock.buffer[23+d]+
																						(unsigned char)memBlock.buffer[24+d]+
																						(unsigned char)memBlock.buffer[25+d]+
																						(unsigned char)memBlock.buffer[26+d]+
																						(unsigned char)memBlock.buffer[27+d]+
																						(unsigned char)memBlock.buffer[28+d]+
																						(unsigned char)memBlock.buffer[29+d]+
																						(unsigned char)memBlock.buffer[30+d]+
																						(unsigned char)memBlock.buffer[31+d]+
																						(unsigned char)memBlock.buffer[32+d]+
																						(unsigned char)memBlock.buffer[33+d]+
																						(unsigned char)memBlock.buffer[34+d]+
																						(unsigned char)memBlock.buffer[35+d]+
																						(unsigned char)memBlock.buffer[36+d]+
																						(unsigned char)memBlock.buffer[37+d]+
																						(unsigned char)memBlock.buffer[38+d]+
																						(unsigned char)memBlock.buffer[39+d]+
																						(unsigned char)memBlock.buffer[40+d]+
																						(unsigned char)memBlock.buffer[41+d]+
																						(unsigned char)memBlock.buffer[42+d]+
																						(unsigned char)memBlock.buffer[43+d]+
																						(unsigned char)memBlock.buffer[44+d]+
																						(unsigned char)memBlock.buffer[45+d]+
																						(unsigned char)memBlock.buffer[46+d]+
																						(unsigned char)memBlock.buffer[47+d]+
																						(unsigned char)memBlock.buffer[48+d]+
																						(unsigned char)memBlock.buffer[49+d]+
																						(unsigned char)memBlock.buffer[50+d]+
																						(unsigned char)memBlock.buffer[51+d]);

							data[x][z].imgH[idcount]	=	(	(unsigned char)memBlock.buffer[52+d]+
																						(unsigned char)memBlock.buffer[53+d]+
																						(unsigned char)memBlock.buffer[54+d]+
																						(unsigned char)memBlock.buffer[55+d]+
																						(unsigned char)memBlock.buffer[56+d]+
																						(unsigned char)memBlock.buffer[57+d]+
																						(unsigned char)memBlock.buffer[58+d]+
																						(unsigned char)memBlock.buffer[59+d]+
																						(unsigned char)memBlock.buffer[60+d]+
																						(unsigned char)memBlock.buffer[61+d]+
																						(unsigned char)memBlock.buffer[62+d]+
																						(unsigned char)memBlock.buffer[63+d]+
																						(unsigned char)memBlock.buffer[64+d]+
																						(unsigned char)memBlock.buffer[65+d]+
																						(unsigned char)memBlock.buffer[66+d]+
																						(unsigned char)memBlock.buffer[67+d]+
																						(unsigned char)memBlock.buffer[68+d]+
																						(unsigned char)memBlock.buffer[69+d]+
																						(unsigned char)memBlock.buffer[60+d]+
																						(unsigned char)memBlock.buffer[71+d]+
																						(unsigned char)memBlock.buffer[72+d]+
																						(unsigned char)memBlock.buffer[73+d]+
																						(unsigned char)memBlock.buffer[74+d]+
																						(unsigned char)memBlock.buffer[75+d]+
																						(unsigned char)memBlock.buffer[76+d]+
																						(unsigned char)memBlock.buffer[77+d]+
																						(unsigned char)memBlock.buffer[78+d]+
																						(unsigned char)memBlock.buffer[79+d]+
																						(unsigned char)memBlock.buffer[80+d]+
																						(unsigned char)memBlock.buffer[81+d]+
																						(unsigned char)memBlock.buffer[82+d]+
																						(unsigned char)memBlock.buffer[83+d]);

							std::string tempImage = "";
							for (int count=84; count<gameVars->recordSize.o2d; count++) {
								if (memBlock.buffer[count+d]!=0) tempImage+=memBlock.buffer[count+d];
								else break;
							}
							data[x][z].image[idcount] = tempImage;

							//Print out the ID (Group #) for the textures required
							//printf("ImageID: %i\n", gameVars->texture.sprite.Get(o2dData[x][z].image[idcount]));
							idcount++;
						}
					if (gameVars->debug.load) std::cout << "Done." <<  std::endl;
				}
			}
			delete sStream;
		//}
		return true;
	}
	catch(...) {
		return false;
	}
}

bool O2D_BASE::calc(bool bUpdate=false) {
	try {
		if (gameVars->debug.load) printf("## CALC O2D ##\n");
		if (gameVars->debug.load) printf("Nothing to do.\n");
		return true;
	}
	catch(...) {
		return false;
	}
}

/*
bool O2D::calc(bool bUpdate=false) {
	//if (gameVars->debug.runworld_o2d_calc) cout << "============ O2D_BASE::calc"<< endl;
	if (gameVars->debug.load) printf("## CALC O2D ##\n");
	try {
		int iItemCount[255]	= {0};		//Current Item count for group
		Vector2f vCoords[] = { 0.0, 0.0,
							   0.0, 1.0,
							   1.0, 0.0,
							   1.0, 1.0 };

		const int num = 256*(gameVars->screen.iTerrainGrid*2);

		for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
			for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {

				// Temporary vector hold the points of each object
				//Vector4f * vVerts2 = new Vector4f[data[x][z].idcount];

				/*
				Vector4f vVerts[]	=	{	{	-1.0f,	1.0f,	0.0f, 0.0f	},
											{	-1.0f,	0.0f,	0.0f, 0.0f	},
											{	 1.0f,	1.0f,	0.0f, 0.0f	},
											{	 1.0f,	0.0f,	0.0f, 0.0f	}	};
				*/

				/*
				 * These points don't deally matter but we need to give some
				 *   sort of shape with unit lengths to be transformed. We
				 *   need 2 points because we are using GL_LINES to prevent
				 *   automatic vertical billboarding.
				 *//*
				Vector4f vVerts[]	=	{	{	0.0f,	0.0f,	0.0f,	0.0f	},
											{	0.0f,	0.0f,	0.0f,	0.0f	}	};

				/*
				 * Temporary vector
				 *
				 * Holds width and height data
				 *//*
				Vector4f * vExtra = new Vector4f[data[x][z].idcount];

				/*
				 * Temporary vector
				 *
				 * Holds actual position data
				 *//*
				Vector4f * vOffset = new Vector4f[data[x][z].idcount];

				cout << "Max Count: " << data[x][z].idcount << endl;

				//int iC = 0;
				for (int count=0; count < (data[x][z].idcount); count++) {
					cout << "Count: " << count << "...";
					float fW = data[x][z].imgW[count]/2;
					float fH = data[x][z].imgH[count];

					//Get and Set height
					float fT = map.getHeight(abs(data[x][z].x[count]), abs(data[x][z].z[count]), x, z);
					data[x][z].y[count] = fT;

					// Vertex 1
					vOffset[count][0] = data[x][z].x[count];
					vOffset[count][1] = fT;
					vOffset[count][2] = data[x][z].z[count];
					vOffset[count][3] = 0.0f;

					vExtra[count][0] = fW;
					vExtra[count][1] = fH;
					vExtra[count][2] = fT;
					vExtra[count][3] = 0.0f;

					//iC++;
					cout << vOffset[count][0] << ", " << vOffset[count][2] << "...";
					cout << "Done" << endl;
				}

				data[x][z].vao2.Begin(GL_LINES, 2, 1, data[x][z].idcount);
				data[x][z].vao2.CopyData(GLA_VERTEX, vVerts);
				data[x][z].vao2.CopyData(GLA_POSITION, vOffset);
				data[x][z].vao2.CopyData(GLA_EXTRA, vExtra);
				//data[x][z].vao.CopyData(GLA_TEXTURE, vCoords, 0);		//Generate texture coordinates in shader
				data[x][z].vao2.End();
			}
		}

		return true;
	}
	catch(...) {
		return false;
	}
}
*/

/*
 * O2D INSTANCING
 *
 * This first thing that needs to be done to to this
 *   is grouping the obects by texture. These
 *   textures also need a new piece of data that
 *   enables skewing.
 *
 * We already have a routine for setting up
 *   the VAO with the appropriate data.
 */

bool O2D::calc(bool bUpdate=false) {
	//if (gameVars->debug.runworld_o2d_calc) cout << "============ O2D_BASE::calc"<< endl;
	if (gameVars->debug.load) printf("## CALC O2D ##\n");
	try {
		//int iItemCount[255]	= {0};		//Current Item count for group

		/*
		 * Texture coordinates
		 */
		Vector2f vCoords[] = { 0.0, 0.0,
							   0.0, 1.0,
							   1.0, 0.0,
							   1.0, 1.0 };

		//const int num = 256*(gameVars->screen.iTerrainGrid*2);

		/*
		 * Need: a x,z grid of groups
		 * Need: groups == number of textures
		 *
		 * Have: Random list of items
		 */
		if(gameVars->debug.draw.o2d_instance) {
			for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
				for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {
					cout << "Grid: [" << x << "][" << z << "]" << endl;
					// data[x][z].image[count]
					// gameVars->texture.sprite.Get();
					// data[x][z].idcount;


					/*
					 * iGroups = Total number of texture groups
					 * iTex[GROUP] = actual texture id for the group
					 * iItem[GROUP] = number of items in this group
					 */
					int iGroups = 0,
						iTex[255] = {-1},
						iItems[255] = {0};

					// Determine number of object texture IDs and values
					for( int iCount=0; iCount <= data[x][z].idcount; iCount++ ) {

						//cout << "Checking Texture: " << data[x][z].image[iCount] << "...";
						bool bTagged = false;
						for(int t = 0; t<255; t++) {		// Iterate through our list of max texture groups
							if(iTex[t] == -1) {
								//cout << "Not Tagged...";
								bTagged = false;
								break;		// If we have reached an unset value then just exit, texture group not counted
							}
							else if(iTex[t] == gameVars->texture.sprite.Get(data[x][z].image[iCount])) {	// If the texture group list contains the texture id then...
								//cout << "Already Tagged...";
								bTagged = true;				// Texture already counted, don't add it to the list
								break;						// We have an answer, exit the loop
							}
						}

						/*
						 * If we found an uncounted texture group
						 *   then add it to the list
						 */
						if(!bTagged) {
							//cout << "Adding Texture " << data[x][z].image[iCount] << "...";
							iTex[iGroups] = gameVars->texture.sprite.Get(data[x][z].image[iCount]);		// Record texture unit
							//cout << "Adding Texture: " << data[x][z].image[iCount] << " : " << gameVars->texture.sprite.Get(data[x][z].image[iCount]) << endl;
							iGroups++;
						}
						else {
							//cout << "Texture Skipped" << endl;
						}
					}

					/*
					 * Determine the total number of items in each group
					 */
					for( int iCount=0; iCount <= data[x][z].idcount; iCount++ ) {		// Iterate through all obejcts
						for(int iGroup=0; iGroup<iGroups; iGroup++) {					// Iterate through all groups
							if(gameVars->texture.sprite.Get(data[x][z].image[iCount]) == iTex[iGroup]) {	// Does the current objects texture id match the current group texture id?
								iItems[iGroup]++;										// It does, so add to the total number of objects in this group
								//iItemId[iGroup] = iCount;
							}
						}
					}

					/*
					 * Get the actual item ID's for each item
					 *   in each group.
					 */
					int * iItemIds[iGroups];	// Up to 255 items per group
					for(int iGroup=0; iGroup<iGroups; iGroup++) {		// Iterate through all groups
						iItemIds[iGroup] = new int[iItems[iGroup]];		// Create array with the size of items in the group

						int iCurrent = 0;
						for( int iCount=0; iCount <= data[x][z].idcount; iCount++ ) {		// Iterate through all items
							if(gameVars->texture.sprite.Get(data[x][z].image[iCount]) == iTex[iGroup]) {		// If the items textureId matches the group textureId
								// Then add the items ID to the list
								iItemIds[iGroup][iCurrent] = iCount;
								iCurrent++;
							}
						}
					}

					// Debugging message
					// This all looks correct
					for(int i=0; i<iGroups; i++) {
						for(int t=0; t<iItems[i]; t++) {
							cout << "   Group[" << i << "][" << t << "]: Image=" << gameVars->texture.sprite.Get(iTex[i]) << " : " << iTex[i] << "; (" << data[x][z].x[iItemIds[i][t]] << ", " << data[x][z].z[iItemIds[i][t]] << "); (" << data[x][z].imgW[iItemIds[i][t]] << ", " << data[x][z].imgH[iItemIds[i][t]] << ")" << endl;
						}
					}
					cout << "--------------" << endl;

					/*
					 * Create VAO's
					 */
					group[x][z].vao = new VAO[iGroups];		//New VAO with size == number of groups

					//Store the number of groups
					group[x][z].iGroups = iGroups;

					// Create array for holding number of items
					group[x][z].iNum = new int[iGroups];

					// Create array for holding texture id's
					group[x][z].image = new int[iGroups];

					// Default throwaway vertex
					Vector4f vVerts[]	=	{	{	0.0f,	0.0f,	0.0f,	0.0f	},
												{	0.0f,	0.0f,	0.0f,	0.0f	}	};


					// Loop through all groups
					for(int iGroup=0; iGroup<iGroups; iGroup++) {		// Iterate through all groups
						cout << "   Group: " << iGroup;
						/*
						 * Temporary vector
						 * Holds width and height data
						 */
						Vector4f * vExtra = new Vector4f[iItems[iGroup]];	// Extra data == number of items in group

						cout << ", Items: " << iItems[iGroup];
						/*
						 * Temporary vector
						 *
						 * Holds actual position data
						 */
						Vector4f * vOffset = new Vector4f[iItems[iGroup]];	// Offset data == number of items in group

						// Store the number of items in the group
						group[x][z].iNum[iGroup] = iItems[iGroup];
						group[x][z].image[iGroup] = iTex[iGroup];

						cout << ", Num: " << group[x][z].iNum[iGroup];
						cout << ", Tex: " << group[x][z].image[iGroup] << endl;

						for (int count=0; count < iItems[iGroup]; count++) {
							cout << "      Item #" << count << "...";
							float fW = data[x][z].imgW[iItemIds[iGroup][count]]/2;
							float fH = data[x][z].imgH[iItemIds[iGroup][count]];
							float fT = map.getHeight(abs(data[x][z].x[iItemIds[iGroup][count]]), abs(data[x][z].z[iItemIds[iGroup][count]]), x, z);
							//data[x][z].y[count] = fT;

							// Vertex 1
							vOffset[count][0] = data[x][z].x[iItemIds[iGroup][count]];
							vOffset[count][1] = fT;
							vOffset[count][2] = data[x][z].z[iItemIds[iGroup][count]];
							vOffset[count][3] = 0.0f;

							vExtra[count][0] = fW;
							vExtra[count][1] = fH;
							vExtra[count][2] = 0.0f;
							vExtra[count][3] = 0.0f;

							//iC++;
							cout << "(" << vOffset[count][0] << ", " << vOffset[count][2] << ")...";
							cout << "Done" << endl;
						}

						//group[x][z].vao[iGroup].Begin(GL_LINES, 2, 1, iItems[iGroup]);
						group[x][z].vao[iGroup].Begin(GL_LINES, 2, 1, iItems[iGroup]);
						group[x][z].vao[iGroup].CopyData(GLA_VERTEX, vVerts);
						group[x][z].vao[iGroup].CopyData(GLA_POSITION, vOffset);
						group[x][z].vao[iGroup].CopyData(GLA_EXTRA, vExtra);
						//data[x][z].vao.CopyData(GLA_TEXTURE, vCoords, 0);		//Generate texture coordinates in shader
						group[x][z].vao[iGroup].End();
					}
				}
				cout << endl;
			}
		}


		/*
		 * Original, Non-Instancing Routine
		 */
		for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
			for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {

				// Temporary vector hold the points of each object
				Vector4f * vVerts2 = new Vector4f[data[x][z].idcount];

				// Temporary vector holds size data
				Vector4f * vSize = new Vector4f[data[x][z].idcount];

				for (int count=0; count <= data[x][z].idcount; count++) {
					float fW = data[x][z].imgW[count]/2;
					float fH = data[x][z].imgH[count];
					float fT = map.getHeight(abs(data[x][z].x[count]), abs(data[x][z].z[count]), x, z);

					// Fourth field used for randomization offset
					Vector4f vVerts[]	=	{	{	-fW,	fH,		0.0, count+1	},
												{	-fW,	0.0f,	0.0, count+1	},
												{	 fW,	fH,		0.0, count+1	},
												{	 fW,	0.0f,	0.0, count+1	}	};

					data[x][z].y[count] = fT;

					if (bUpdate) {
						new(&data[x][z].vao[count]) VAO();	//We need to create new VAO objects for this to work

						data[x][z].vao[count].Begin(GL_TRIANGLE_STRIP, 4, 1);
						data[x][z].vao[count].CopyData(GLA_VERTEX, vVerts);
						data[x][z].vao[count].CopyData(GLA_TEXTURE, vCoords, 0);
						data[x][z].vao[count].End();
					}
					else {
						data[x][z].vao[count].Begin(GL_TRIANGLE_STRIP, 4, 1);
						data[x][z].vao[count].CopyData(GLA_VERTEX, vVerts);
						data[x][z].vao[count].CopyData(GLA_TEXTURE, vCoords, 0);
						data[x][z].vao[count].End();
					}
				}
			}
		}

		return true;
	}
	catch(...) {
		return false;
	}
}


/*
void O2D_BASE::draw(int iShader, bool bSort=false) {
	glDisable(GL_CULL_FACE);
	Core.shader.use(iShader);

	// Standard Drawing routine (blending with shader)
	for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
		for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {
			//std::sort();
			for (int count=0; count <= data[x][z].idcount; count++) {

				/*
				 * Are we above the sea level?
				 * Prevent drawing 2D objects below water
				 *
				 * WE MAY REMOVE THIS FOR FUTURE FUNCTIONALITY
				 *//*
				//if (data[x][z].y[count] > gameVars->world.water.iHeight) {

					Core.matrix.Push();
						//Core.matrix.SetTransform();
						Core.shader.getUniform(atmosphere, iShader);
						gameVars->texture.sprite.Set(data[x][z].image[count]);
						data[x][z].vao2.Draw(GLM_DRAW_ARRAYS_INSTANCED, 0, data[x][z].idcount);
					Core.matrix.Pop();
				//}
			}
		}
	}
	glEnable(GL_CULL_FACE);
}
*/

void O2D_BASE::draw(int iShader, bool bSort=false) {
	//bool bInstance = true;
	glDisable(GL_CULL_FACE);
	Core.shader.use(iShader);

	// Distance Sorting
	/*
	Vector4i objects[gameVars->screen.iTerrainGrid*gameVars->screen.iTerrainGrid*257];

	int numObjects=0;
	for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
		for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {
			for (int count=0; count <= o2dData[x][z].idcount; count++) {
				o2dData[x][z].distance[count] = Hypot(Vector2f{-gameVars->transform.xPos, -gameVars->transform.zPos}, Vector2f{o2dData[x][z].offX[count], o2dData[x][z].offZ[count]});
				objects[numObjects] = { o2dData[x][z].distance[count], x, z, count };
				numObjects++;
			}
		}
	}

	for (int i = 0; i < numObjects; i++) {
		for (int j = 0; j < i; j++) {
			if (objects[i][0] > objects[j][0]) {
				Vector4i temp = { objects[i][0], objects[i][1], objects[i][2], objects[i][3] }; //swap
				memcpy(objects[i], objects[j], sizeof(Vector4i));
				memcpy(objects[j], temp, sizeof(Vector4i));
			}
		}
	}

	int count;
	int x;
	int z;
	for (int i = 0; i < numObjects; i++) {
		count = objects[i][3];
		x = objects[i][1];
		z = objects[i][2];

		Core.matrix.Push();
			//Core.matrix.Rotate(10, 0, 1, 0);
			//Core.matrix.SetTransform();
			Core.shader.getUniform(gameVars, GLS_FONT);
			gameVars->texture.sprite.Set(o2dData[x][z].image[count]);
			vao[x][z][count].Draw();
		Core.matrix.Pop();
	}*/
	//

	/*
	 * Get initial values
	 */
	Vector3f	vCamPos;
	vCamPos[0] = -gameVars->player.active->transform.pos[0];
	vCamPos[1] = 0.0f;
	vCamPos[2] = -gameVars->player.active->transform.pos[2];

	Vector3f	vUp = { 0.0, 1.0, 0.0};
	Vector3f	vLook, vRight;

	if(!gameVars->debug.draw.o2d_instance) {
		if(bSort) {
			/*
			 * Setup distance sorting
			 * This is a bubble sort, VERY SLOW! Over 50% framerate drop!
			 */
			Vector4i objects[gameVars->screen.iTerrainGrid*gameVars->screen.iTerrainGrid*257];
			int numObjects=0;
			for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
				for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {
					for (int count=0; count <= data[x][z].idcount; count++) {
						data[x][z].distance[count] = Hypot(-gameVars->player.active->transform.pos[0], -gameVars->player.active->transform.pos[2], data[x][z].x[count], data[x][z].z[count]);
						objects[numObjects][0] = data[x][z].distance[count];
						objects[numObjects][1] = x;
						objects[numObjects][2] = z;
						objects[numObjects][3] = count;
						numObjects++;
					}
				}
			}

			for (int i = 0; i < numObjects; i++) {
				for (int j = 0; j < i; j++) {
					if (objects[i][0] > objects[j][0]) {
						Vector4i temp = { objects[i][0], objects[i][1], objects[i][2], objects[i][3] }; //swap
						memcpy(objects[i], objects[j], sizeof(Vector4i));
						memcpy(objects[j], temp, sizeof(Vector4i));
					}
				}
			}

			/*
			 * Draw with distance sorting
			 */
			int count;
			int x;
			int z;
			for (int i = 0; i < numObjects; i++) {
				count = objects[i][3];
				x = objects[i][1];
				z = objects[i][2];

				Core.matrix.Push();
					Vector3f	vObjPos = { float(data[x][z].x[count]), float(data[x][z].blend[count]), float(data[x][z].z[count]) };
					Diff(vLook, vCamPos, vObjPos);
					Normalize(vLook);
					Cross(vRight, vUp, vLook);

					Matrix44f	mTemp = {	vRight[0], vRight[1], vRight[2], 0.0f,
											0.0f, 1.0f, 0.0f, 0.0f,
											vLook[0], vLook[1], vLook[2], 0.0f,
											vObjPos[0], vObjPos[1], vObjPos[2], 1.0f };

					Core.matrix.Apply(mTemp);
					Core.matrix.Translate(0.0f, data[x][z].y[count], 0.0f);
					Core.matrix.SetTransform();
					Core.shader.getUniform(atmosphere, iShader);

					gameVars->texture.sprite.Set(data[x][z].image[count]);

					data[x][z].vao[count].Draw();
				Core.matrix.Pop();
			}
		}
		else {
			// Standard Drawing routine (blending with shader)
			for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
				for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {
					//std::sort();
					for (int count=0; count <= data[x][z].idcount; count++) {

						/*
						 * Are we above the sea level?
						 * Prevent drawing 2D objects below water
						 *
						 * WE MAY REMOVE THIS FOR FUTURE FUNCTIONALITY
						 */
						if (data[x][z].y[count] > gameVars->world.water.iHeight) {


							Core.matrix.Push();
								// Billboarding quicky
								// look = camera_pos - object_pos
								// up = y(normalized)
								// right = up x look (cross product)

								Vector3f	vObjPos = { float(data[x][z].x[count]), float(data[x][z].blend[count]), float(data[x][z].z[count]) };
								Diff(vLook, vCamPos, vObjPos);
								Normalize(vLook);
								Cross(vRight, vUp, vLook);

								Matrix44f	mTemp = {	vRight[0], vRight[1], vRight[2], 0.0f,
														0.0f, 1.0f, 0.0f, 0.0f,
														vLook[0], vLook[1], vLook[2], 0.0f,
														vObjPos[0], vObjPos[1], vObjPos[2], 1.0f };

								Core.matrix.Apply(mTemp);
								Core.matrix.Translate(0.0f, data[x][z].y[count], 0.0f);
								Core.matrix.SetTransform();
								bool bSkew = false;
								if (data[x][z].image[count] == "tree4.png") bSkew = true;
								Core.shader.getUniform(atmosphere, iShader, bSkew);

								gameVars->texture.sprite.Set(data[x][z].image[count]);

								data[x][z].vao[count].Draw();
							Core.matrix.Pop();



							/*
							 * Non-Billboarding, Double-Draw mode
							 */
	/*
							Vector3f	vObjPos = { float(data[x][z].x[count]), float(data[x][z].blend[count]), float(data[x][z].z[count]) };
							Matrix44f	mTemp = {	1.0f, 0.0f, 0.0f, 0.0f,
													0.0f, 1.0f, 0.0f, 0.0f,
													0.0f, 0.0f, 1.0f, 0.0f,
													vObjPos[0], vObjPos[1], vObjPos[2], 1.0f };
							gameVars->texture.sprite.Set(data[x][z].image[count]);
							Core.matrix.Push();
							Core.matrix.Apply(mTemp);

								Core.matrix.Push();
									Core.matrix.Translate(0.0f, data[x][z].y[count], 0.0f);
									Core.matrix.SetTransform();
									Core.shader.getUniform(atmosphere, iShader);
									data[x][z].vao[count].Draw();
								Core.matrix.Pop();

								Core.matrix.Push();
									Core.matrix.Rotate(M_DegToRad(90), 0.0f, 1.0f, 0.0f);
									Core.matrix.Translate(0.0f, data[x][z].y[count], 0.0f);
									Core.matrix.SetTransform();
									Core.shader.getUniform(atmosphere, iShader);
									data[x][z].vao[count].Draw();
								Core.matrix.Pop();

								Core.matrix.Push();
									Core.matrix.Rotate(M_DegToRad(45), 0.0f, 1.0f, 0.0f);
									Core.matrix.Translate(0.0f, data[x][z].y[count], 0.0f);
									Core.matrix.SetTransform();
									Core.shader.getUniform(atmosphere, iShader);
									data[x][z].vao[count].Draw();
								Core.matrix.Pop();

								Core.matrix.Push();
									Core.matrix.Rotate(M_DegToRad(45), 0.0f, -1.0f, 0.0f);
									Core.matrix.Translate(0.0f, data[x][z].y[count], 0.0f);
									Core.matrix.SetTransform();
									Core.shader.getUniform(atmosphere, iShader);
									data[x][z].vao[count].Draw();
								Core.matrix.Pop();

							Core.matrix.Pop();
	*/
						}
					}
				}
			}
		}
	}
	else {
		//cout << "Instanced Drawing..." << endl;
		for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
			for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {
				//std::sort();
				for(int iGroup=0; iGroup<group[x][z].iGroups; iGroup++) {
					//for(int iItem=0; iItem<group[x][z].iNum[iGroup]; iItem++) {
					//cout << "Group: " << iGroup << ", Tex: " << group[x][z].image[iGroup];
						Core.matrix.Push();
							Core.shader.getUniform(atmosphere, iShader);
							gameVars->texture.sprite.Set(group[x][z].image[iGroup]);
							group[x][z].vao[iGroup].Draw(GLM_DRAW_ARRAYS_INSTANCED, 0, group[x][z].iNum[iGroup]);
						Core.matrix.Pop();
					//}
				}
			}
		}
	}
	glEnable(GL_CULL_FACE);
}


#endif /* O2D_H_ */
