/*
 * E2D.h
 *
 *  Created on: Nov 1, 2010
 *      Author: bcthund
 */

#ifndef E2D_H_
#define E2D_H_

class E2D_BASE {
	private:

	protected:

	public:
		E2D_BASE(Atmosphere &a);
		//~E2D_BASE() { cout << "Destroy E2D...Done" << endl; }
		E2dData data[9][9];
		//E2dData data[9][9];
		//E2DGroups gameVars->data.world.e2dGroup[256];
		//vector3f E2DgameVars->data.world.e2dGroup[256];
		bool init();
		void clear();
		//void shift(int iShift);
		//bool load(int iShift);
		bool calc(bool bUpdate);
		void draw(int iShader);
		Atmosphere &atmosphere;
};

E2D_BASE::E2D_BASE(Atmosphere &a): atmosphere(a) {
}

class E2D: public E2D_BASE {
	private:
		WorldMap &map;			//The parent MapData structure

	public:
		bool load(int iShift);
		void shift(int iShift);
		bool calc(bool bUpdate);
		void execute();
		void loadEvent(Vector4ui vEvent);
		E2D(WorldMap &m, Atmosphere &a): E2D_BASE(a), map(m) {}
		~E2D() {
			//       .................................................................Done
			cout << "Destroy E2D......................................................Not Implemented" << endl;
		}
};

void E2D_BASE::clear() {
	for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
		for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {
			data[x][z].idcount = -1;
		}
	}
}

bool E2D_BASE::init() {
	if (gameVars->debug.load) printf("## INIT E2D ##\n");
	return true;
}

void E2D::shift(int iShift) {
	cout << endl << "Shifting e2d..." << endl;
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
			//		CopyE2dData(&data[x][y], &data[x][y-iOffset]);
			//		cout << "Shifting From (" << x << "," << y << ") to (" << x << "," << y-iOffset  << ")" << endl;
			//	}
			//}
			load(SHIFT_UP);
			calc(true);
			break;
		case SHIFT_DOWN:
			//for (int x=0;x<=iGrid; x++) {
			//	for (int y=iGrid-iOffset;y>=0; y--) {
			//		CopyE2dData(&data[x][y], &data[x][y+iOffset]);
			//		cout << "Shifting From (" << x << "," << y << ") to (" << x << "," << y+iOffset  << ")" << endl;
			//	}
			//}
			load(SHIFT_DOWN);
			calc(true);
			break;
		case SHIFT_LEFT:
			//for (int y=0;y<=iGrid; y++) {
			//	for (int x=iOffset;x<=iGrid; x++) {
			//		CopyE2dData(&data[x][y], &data[x-iOffset][y]);
			//		cout << "Shifting From (" << x << "," << y << ") to (" << x-iOffset << "," << y  << ")" << endl;
			//	}
			//}
			load(SHIFT_LEFT);
			calc(true);
			break;
		case SHIFT_RIGHT:
			//for (int y=0;y<=iGrid; y++) {
			//	for (int x=iGrid-iOffset;x>=0; x--) {
			//		CopyE2dData(&data[x][y], &data[x+iOffset][y]);
			//		cout << "Shifting From (" << x << "," << y << ") to (" << x+iOffset << "," << y  << ")" << endl;
			//	}
			//}
			load(SHIFT_RIGHT);
			calc(true);
			break;
	}
}

bool E2D::load(int iShift=SHIFT_LAST) {
	try {
		//if (gameVars->debug.load) printf("\n ###################\n");
		if (gameVars->debug.load) printf("## LOAD E2D\n");

		//Variables
		bool bReadResult;
		MemBlock memBlock;
		std::string loadFile;
		std::stringstream *sStream = new std::stringstream;

		//Setup proper Shift loading
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

		//cout << "[" << mapSx << "," << mapSz << "," << mapEx << "," << mapEz << "," << baseX << "," << baseZ << "]" << endl;

		for (int x=mapSx; x<mapEx; x++) {
			idcount=0;
			//cout << "...LOADING x..." << endl;
			for (int z=mapSz; z<mapEz; z++) {
				iX=map.vBase[0]+x+baseX;
				iZ=map.vBase[1]+z+baseZ;
				idcount=0;

				//cout << "...LOADING z..." << endl;

				//################################
				//		Load Binary Object Data
				sStream->str("");
				*sStream << map.dir << "e2d/" << iX << "-" << iZ << ".e2d";
				loadFile=sStream->str();
				if (gameVars->debug.load) std::cout << " -Loading " << loadFile << "...";
				bReadResult = readFile(loadFile, memBlock);		//Read the data file into memory
				if (!bReadResult) {
					sStream->str("");
					*sStream << map.dir << "e2d/" << "0-0.e2d";
					loadFile=sStream->str();
					readFile(loadFile, memBlock);
				}

				if (memBlock.size <= 0) data[x][z].idcount = -1;
				for (int d=0; d<memBlock.size; d+=gameVars->recordSize.e2d) {
					if (gameVars->debug.load) std::cout << "Event #" << data[x][z].id[idcount] << "...";
					//cout << "   > " << idcount << "," << data[x][z].id[idcount] << "," <<  data[x][z].image[idcount] << endl;

					//Set the number of loaded objects
					data[x][z].idcount = idcount;

					//Object and Event ID number
					data[x][z].id[idcount]		=	(	(unsigned char)memBlock.buffer[0+d]+
																			(unsigned char)memBlock.buffer[1+d]+
																			(unsigned char)memBlock.buffer[2+d]+
																			(unsigned char)memBlock.buffer[3+d]);

					//Rotation in degrees
					data[x][z].r[idcount]		=		(unsigned char)memBlock.buffer[4+d];
					data[x][z].r[idcount]		+=		(unsigned char)memBlock.buffer[5+d];
					data[x][z].r[idcount]		+=		(unsigned char)memBlock.buffer[6+d];
					data[x][z].r[idcount]		+=		(unsigned char)memBlock.buffer[7+d];
					data[x][z].r[idcount] 		=		M_DegToRad(data[x][z].r[idcount]);

					//x position
					float xLocal					=		(unsigned char)memBlock.buffer[8+d]+1;
					xLocal							+=		(unsigned char)memBlock.buffer[9+d]+1;
					xLocal							+=		(unsigned char)memBlock.buffer[10+d]+1;
					xLocal							+=		(unsigned char)memBlock.buffer[11+d]+1;
					float xGlobal = xLocal + (x*1024);
					data[x][z].x[idcount] = xGlobal;

					//z position
					float zLocal					=		(unsigned char)memBlock.buffer[12+d]+1;
					zLocal							+=		(unsigned char)memBlock.buffer[13+d]+1;
					zLocal							+=		(unsigned char)memBlock.buffer[14+d]+1;
					zLocal							+=		(unsigned char)memBlock.buffer[15+d]+1;
					float zGlobal = zLocal + (z*1024);
					data[x][z].z[idcount] = zGlobal;
					/*
					data[x][z].x[idcount]		=		(unsigned char)memBlock.buffer[8+d]+1;
					data[x][z].x[idcount]		+=		(unsigned char)memBlock.buffer[9+d]+1;
					data[x][z].x[idcount]		+=		(unsigned char)memBlock.buffer[10+d]+1;
					data[x][z].x[idcount]		+=		(unsigned char)memBlock.buffer[11+d]+1;

					//z position
					data[x][z].z[idcount]		=		(unsigned char)memBlock.buffer[12+d]+1;
					data[x][z].z[idcount]		+=		(unsigned char)memBlock.buffer[13+d]+1;
					data[x][z].z[idcount]		+=		(unsigned char)memBlock.buffer[14+d]+1;
					data[x][z].z[idcount]		+=		(unsigned char)memBlock.buffer[15+d]+1;
					*/

					//Blending of object into ground (Up, Down shift)
					data[x][z].blend[idcount]		=	(	(unsigned char)memBlock.buffer[16+d]+
																					(unsigned char)memBlock.buffer[17+d]+
																					(unsigned char)memBlock.buffer[18+d]+
																					(unsigned char)memBlock.buffer[19+d]);

					//Width of the object
					data[x][z].imgW[idcount]		=	(	(unsigned char)memBlock.buffer[20+d]+
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
					float fImgW = data[x][z].imgW[idcount];

					//Height of the object
					data[x][z].imgH[idcount]		=	(	(unsigned char)memBlock.buffer[52+d]+
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
					float fImgH = data[x][z].imgH[idcount];

					//Texture to use for object (Loaded from 'sprite.bin')
					std::string tempImage = "";
					for (int count=84; count<gameVars->recordSize.e2d; count++) {
						if (memBlock.buffer[count+d]!=0) tempImage+=memBlock.buffer[count+d];
						else break;
					}
					data[x][z].image[idcount] = tempImage;

					//Calculate the Center of Object(coo)
					data[x][z].coo[idcount][0] = xGlobal;
					data[x][z].coo[idcount][1] = data[x][z].imgH[idcount]/2;
					data[x][z].coo[idcount][2] = zGlobal;
					//printf("\nCOO[%i] = %f, %f, %f\n", idcount, data[x][z].coo[idcount][0], data[x][z].coo[idcount][1], data[x][z].coo[idcount][2]);

					//Calculate the Range of Interaction(roi)
					Vector3f vRoi = {fImgW/2, 0, fImgH/2};
					float fRoi = pyth(vRoi);
					data[x][z].roi[idcount] = fRoi;
					//printf("\nROI[%i] = %f\n", idcount, fRoi);

					//For storing the current distance to this event objects 'coo'
					Vector3f fPlayerPos = { -gameVars->player.active->transform.pos[0], -gameVars->player.active->transform.pos[1], -gameVars->player.active->transform.pos[2] };
					calcDistance(fPlayerPos, data[x][z].coo[idcount], data[x][z].distance[idcount]);
					//printf("\nPlayerPos[%i] = %f, %f, %f\n", idcount, fPlayerPos[0], fPlayerPos[1], fPlayerPos[2]);
					//printf("\nDistance[%i] = %f\n", idcount, data[x][z].distance[idcount]);

					//Print out the ID (Group #) for the textures required
					//printf("ImageID: %i\n", gameVars->texture.sprite.Get(data[x][z].image[idcount]));
					idcount++;
				}
				if (gameVars->debug.load) std::cout << "Done." <<  std::endl;
			}
		}
		return true;
	}
	catch(...) {
		return false;
	}
}

bool E2D_BASE::calc(bool bUpdate=false) {
	try {
		if (gameVars->debug.load) printf("## CALC E2D ##\n");
		return true;
	}
	catch(...) {
		return false;
	}
}

bool E2D::calc(bool bUpdate=false) {
	//if (gameVars->debug.runworld_e2d_calc) cout << "============ E2D_BASE::calc"<< endl;
	if (gameVars->debug.load) printf("## CALC E2D ##\n");
	try {
		int iItemCount[255]	= {0};		//Current Item count for group
		//Vector3f vPos[255][255];	//255 groups with 255 items MAX
		Data2f vCoords[] = { {1.0, 0.0},
							   {0.0, 0.0},
							   {0.0, 1.0},

							   {1.0, 0.0},
							   {0.0, 1.0},
							   {1.0, 1.0} };

		const int num = 256*(gameVars->screen.iTerrainGrid*2);

		for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
			for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {
				for (int count=0; count <= data[x][z].idcount; count++) {
					float fW = data[x][z].imgW[count]/2;
					float fH = data[x][z].imgH[count];

					Data3f vVerts[]	=	{	{	 fW,	fH,		0.0	},
												{	-fW,	fH,		0.0	},
												{	-fW,	0.0,	0.0	},

												{	 fW,	fH,		0.0	},
												{	-fW,	0.0,	0.0	},
												{	 fW,	0.0,	0.0	}	};

					if (gameVars->debug.load) cout << " [" << count << "] Map[" << x << "][" << z << "]...";
					if (bUpdate) {
						new(&data[x][z].vao[count]) VAO();
						data[x][z].vao[count].Begin(GL_TRIANGLES, 6, 1);
						data[x][z].vao[count].ReplaceData(GLA_VERTEX, vVerts);
						data[x][z].vao[count].ReplaceData(GLA_TEXTURE, vCoords, 0);
						data[x][z].vao[count].End();
					}
					else {
						data[x][z].vao[count].Begin(GL_TRIANGLES, 6, 1);
						//if (gameVars->debug.runworld_e2d_calc) cout << "     CopyData: vVerts" << endl;
						data[x][z].vao[count].CopyData(GLA_VERTEX, vVerts);
						//if (gameVars->debug.runworld_e2d_calc) cout << "     CopyData: vCoords" << endl;
						data[x][z].vao[count].CopyData(GLA_TEXTURE, vCoords, 0);
						data[x][z].vao[count].End();
					}
					if (gameVars->debug.load) cout << "Done" << endl;
				}
			}
		}

// ============================================ CONDITIONAL JUMP DEPENDS ON UNINITIALIZED VALUE ????
		//for (int x=0; gameVars->data.world.e2dGroup[x].count > 0; x++) {
		//	for (int y=0; y < gameVars->data.world.e2dGroup[x].count; y++) {
		//		//printf("gameVars->data.world.e2dGroup[%i]; Item[%i]; (%f, %f)\n", x, y, gameVars->data.world.e2dGroup[x].vPos[y][0], gameVars->data.world.e2dGroup[x].vPos[y][2]);
		//		gameVars->vao.world.e2dInst[x].CopyData(GLA_POSITION, gameVars->data.world.e2dGroup[x].vPos);
		//		gameVars->vao.world.e2dInst[x].End();
		//	}
		//}

		return true;
	}
	catch(...) {
		return false;
	}
}

void E2D_BASE::draw(int iShader) {
	glDisable(GL_CULL_FACE);
	Core.shader.use(iShader);
		Vector3f	vCamPos;

		vCamPos[0] = -gameVars->player.active->transform.pos[0];
		vCamPos[1] = 0.0f;
		vCamPos[2] = -gameVars->player.active->transform.pos[2];

		// Standard Drawing routine (blending with shader)
		for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
			for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {
				for (int count=0; count <= data[x][z].idcount; count++) {
					Core.matrix.Push();
						Vector3f	vObjPos = { float(data[x][z].x[count]), float(data[x][z].blend[count]), float(data[x][z].z[count]) };
						Matrix44f	mTemp = {	1.0f, 0.0f, 0.0f, 0.0f,
												0.0f, 1.0f, 0.0f, 0.0f,
												0.0f, 0.0f, 1.0f, 0.0f,
												vObjPos[0], vObjPos[1], vObjPos[2], 1.0f };

						Core.matrix.Apply(mTemp);
						Core.matrix.Rotate(data[x][z].r[count], 0, 1, 0);
						Core.matrix.SetTransform();
						Core.shader.getUniform(atmosphere, iShader);

						gameVars->texture.sprite.Set(data[x][z].image[count]);

						//data[x][z].vao[count].Draw(GLM_DRAW_ARRAYS_INSTANCED);
						data[x][z].vao[count].Draw();
					Core.matrix.Pop();

					//Update this objects distance value (playerPos must be positive values here, actual position is negative)
					Vector3f fPlayerPos = { -gameVars->player.active->transform.pos[0], -gameVars->player.active->transform.pos[1], -gameVars->player.active->transform.pos[2] };
					calcDistance(fPlayerPos, data[x][z].coo[count], data[x][z].distance[count]);
//					if (data[x][z].distance[count] <= data[x][z].roi[count]+gameVars->player.active->transform.reach) {
//					// Check for "Active" events here
//					// "Active" events are those that require no interation to be activated other than being within range
//						printf("Event[%i] within range! Press [Enter] to activate.\n", count);
//					}
//					else {
//						printf("Event[%i] outside range. [%f]\n", count, data[x][z].distance[count]);
//					}
				}
			}
		}
	glEnable(GL_CULL_FACE);
}

void E2D::execute() {
	Vector4ui iClosest = { 255, 500, 0, 0 };	//[0]=id; [1]=distance; [2]=xCoord; [3]=zCoord;

	// Loop through current location
	for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
		for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {
			for (int count=0; count <= data[x][z].idcount; count++) {
				if (data[x][z].distance[count] <= 500) {
					//Update this objects distance value again, and store the id if it is closer than the last event and within range
					Vector3f fPlayerPos = { -gameVars->player.active->transform.pos[0], -gameVars->player.active->transform.pos[1], -gameVars->player.active->transform.pos[2] };
					calcDistance(fPlayerPos, data[x][z].coo[count], data[x][z].distance[count]);
					//printf("Distance[%i] = %i: ", count, int(data[x][z].distance[count]));
					if (data[x][z].distance[count] <= data[x][z].roi[count]+gameVars->player.active->transform.reach) {
						//printf("Event[%i] within range: ", count);

						// Check current event and update if closer
						if (data[x][z].distance[count] < iClosest[1]) {
							iClosest[0] = count;
							iClosest[1] = data[x][z].distance[count];
							iClosest[2] = map.vBase[0]+x;
							iClosest[3] = map.vBase[1]+z;

							//startX-((iGridsize-1)/2)
							//printf("Closer than last event[%i, %i]: ", iClosest[2], iClosest[3]);
						}
					}
				}
				//else printf("Event detected outside max distance: ");
			}
		}
	}
	//Execute the nearest VALID event if id+=255 (255 = no events)
	if (iClosest[0] == 255) printf("No valid events detected.");
	else {
		//To execute the event here, open the corresponding ".elf" file, offset to the correct event id location
		//Each event has 128 bytes of data, the event type determines what data needs to be retrieved.
		//This is essentially a loading location, lag could possibly occur from this method but requires less
		//memory to store information.
		printf("Closest Event\n ID: %i\n Distance: %i\n", iClosest[0], iClosest[1]);

		loadEvent(iClosest);
	}
}

void E2D::loadEvent(Vector4ui vEvent) {

	#define id 0
	#define dist 1
	#define xMap 2
	#define zMap 3

	if (gameVars->debug.load) printf("\n ###################\n");
	if (gameVars->debug.load) printf("## LOADING ELF\n");
	bool bReadResult;
	MemBlock memBlock;
	std::string loadFile;
	std::stringstream *sStream = new std::stringstream;

	//################################
	//		Load Binary Object Data
	sStream->str("");
	*sStream << map.dir << "elf/" << vEvent[xMap] << "-" << vEvent[zMap] << ".elf";
	loadFile=sStream->str();
	if (gameVars->debug.load) std::cout << " -Loading " << loadFile << "...";
	bReadResult = readFile(loadFile, memBlock);		//Read the data file into memory
	if (!bReadResult) {
		sStream->str("");
		*sStream << map.dir << "elf/" << "0-0.elf";
		loadFile=sStream->str();
		readFile(loadFile, memBlock);
	}

	if (memBlock.size <= 0) printf("Error! No event data in file, aborting.\n");
	else {
		printf("Found event data. \nNarrowing results and extracting data...");

		int iRecord = vEvent[id]*gameVars->recordSize.elf;

		int iType						=	(	(unsigned char)memBlock.buffer[4+iRecord]+
												(unsigned char)memBlock.buffer[5+iRecord]+
												(unsigned char)memBlock.buffer[6+iRecord]+
												(unsigned char)memBlock.buffer[7+iRecord]);

		printf("iRecord = %i\n", iRecord);
		printf("iType = %i\n", iType);
		int iDungeonId;

		switch (iType) {
			case 0:		// No event action
				break;
			case 1:		// Teleport to Dungeon
				iDungeonId				=	(	(unsigned char)memBlock.buffer[8+iRecord]+
												(unsigned char)memBlock.buffer[9+iRecord]+
												(unsigned char)memBlock.buffer[10+iRecord]+
												(unsigned char)memBlock.buffer[11+iRecord]);
				printf("Teleporting to dungeon[%i]...\n", iDungeonId);
				gameVars->state.dungeon = true;
				break;
			case 2:		//	Teleport to City
				printf("Teleporting to city...");
				break;
			case 3:		//	Teleport to World
				printf("Teleporting to world...");
				break;
			default:
				printf("Invalid Event Type[%i], Aborting.\n", iType);
				break;
		}

		/*
		data[x][z].id[idcount]		=	(	(unsigned char)memBlock.buffer[0+d]+
												(unsigned char)memBlock.buffer[1+d]+
												(unsigned char)memBlock.buffer[2+d]+
												(unsigned char)memBlock.buffer[3+d]);

		//Rotation in degrees
		data[x][z].r[idcount]		=		(unsigned char)memBlock.buffer[4+d];
		data[x][z].r[idcount]		+=		(unsigned char)memBlock.buffer[5+d];
		data[x][z].r[idcount]		+=		(unsigned char)memBlock.buffer[6+d];
		data[x][z].r[idcount]		+=		(unsigned char)memBlock.buffer[7+d];
		data[x][z].r[idcount] 		=		M_DegToRad(data[x][z].r[idcount]);
		*/
	}

	#undef id
	#undef dist
	#undef xMap
	#undef zMap
}
#endif /* E2D_H_ */
