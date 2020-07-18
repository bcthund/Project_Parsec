/*
 * O3D_Dungeon.h
 *
 *  Created on: Nov 1, 2010
 *      Author: bcthund
 */

#ifndef O3D_Dungeon_H_
#define O3D_Dungeon_H_

class O3D_Dungeon {
	private:

	protected:

	public:
		O3D_Dungeon();
		O3dData o3dData[9];					//Only 9 objects can be loaded currently
		bool init();
		bool load();
		bool calc();
		void draw(Atmosphere &a, bool bShadow);
};

O3D_Dungeon::O3D_Dungeon() {
}

bool O3D_Dungeon::init() {
	return true;
}

bool O3D_Dungeon::load() {
	try {
		//if (gameVars->debug.load) printf("\n ###################\n");
		if (gameVars->debug.load) printf("## LOADING O3D_Dungeon\n");
		bool bReadResult;
		MemBlock memBlock;
		std::string loadFile;
		std::stringstream sStream;
		int idcount=0;

		//################################
		//		Load Binary Object Data
		sStream.str("");
		sStream << gameVars->dir.dgn << "0/0.o3d";
		loadFile=sStream.str();
		if (gameVars->debug.load) std::cout << " -Loading " << loadFile << "...";
		bReadResult = readFile(loadFile, memBlock);		//Read the data file into memory
		if (!bReadResult) {
			//printf("DEFAULT...");
			//sStream.str("");
			//sStream << gameVars->dir.o3d << "0-0.o3d";
			//loadFile=sStream.str();
			//readFile(loadFile, memBlock);
		}

		if (memBlock.size <= 0) {
			o3dData[0].idcount = -1;
			if (gameVars->debug.load) printf("NO DATA...\n");
		}
		else {
			if (gameVars->debug.load) printf("DATA[%i]...", memBlock.size);
			for (int d=0; d < memBlock.size; d+=gameVars->recordSize.o3d) {
				o3dData[0].id[idcount]		=	(	(unsigned char)memBlock.buffer[0+d]+
													(unsigned char)memBlock.buffer[1+d]+
													(unsigned char)memBlock.buffer[2+d]+
													(unsigned char)memBlock.buffer[3+d]);

//				printf("id: %i\n", o3dData[0].id[idcount]);

				o3dData[0].x[idcount]		=		(char)memBlock.buffer[4+d];
				o3dData[0].x[idcount]		+=		(char)memBlock.buffer[5+d];
				o3dData[0].x[idcount]		+=		(char)memBlock.buffer[6+d];
				o3dData[0].x[idcount]		+=		(char)memBlock.buffer[7+d];
				//o3dData[0].x[idcount]		+=		16;

//				printf("x: %f\n", o3dData[0].x[idcount]);

				o3dData[0].z[idcount]		=		(char)memBlock.buffer[8+d];
				o3dData[0].z[idcount]		+=		(char)memBlock.buffer[9+d];
				o3dData[0].z[idcount]		+=		(char)memBlock.buffer[10+d];
				o3dData[0].z[idcount]		+=		(char)memBlock.buffer[11+d];
				//o3dData[0].z[idcount]		+=		16;

//				printf("z: %f\n", o3dData[0].z[idcount]);

				o3dData[0].blend[idcount]	=	(	(char)memBlock.buffer[12+d]+
													(char)memBlock.buffer[13+d]+
													(char)memBlock.buffer[14+d]+
													(char)memBlock.buffer[15+d]);

//				printf("blend: %i\n", o3dData[0].blend[idcount]);

				/*
				o3dData[0].sx[idcount]		=		(char)memBlock.buffer[16+d];
				o3dData[0].sx[idcount]		+=		((float)memBlock.buffer[17+d])/100;
				o3dData[0].sy[idcount]		=		(char)memBlock.buffer[18+d];
				o3dData[0].sy[idcount]		+=		((float)memBlock.buffer[19+d])/100;
				o3dData[0].sz[idcount]		=		(char)memBlock.buffer[20+d];
				o3dData[0].sz[idcount]		+=		((float)memBlock.buffer[21+d])/100;
				*/

				o3dData[0].sx[idcount]		=		(char)memBlock.buffer[16+d];
				o3dData[0].sx[idcount]		+=		((float)memBlock.buffer[17+d]);
				o3dData[0].sy[idcount]		=		(char)memBlock.buffer[18+d];
				o3dData[0].sy[idcount]		+=		((float)memBlock.buffer[19+d]);
				o3dData[0].sz[idcount]		=		(char)memBlock.buffer[20+d];
				o3dData[0].sz[idcount]		+=		((float)memBlock.buffer[21+d]);

//				printf("sx: %f\n", o3dData[0].sx[idcount]);
//				printf("sy: %f\n", o3dData[0].sy[idcount]);
//				printf("sz: %f\n", o3dData[0].sz[idcount]);

				o3dData[0].rx[idcount]		=		(char)memBlock.buffer[22+d];
				o3dData[0].rx[idcount]		+=		((char)memBlock.buffer[23+d])/100;
				o3dData[0].ry[idcount]		=		(char)memBlock.buffer[24+d];
				o3dData[0].ry[idcount]		+=		((char)memBlock.buffer[25+d])/100;
				o3dData[0].rz[idcount]		=		(char)memBlock.buffer[26+d];
				o3dData[0].rz[idcount]		+=		((char)memBlock.buffer[27+d])/100;

//				printf("rx: %f\n", o3dData[0].rx[idcount]);
//				printf("ry: %f\n", o3dData[0].ry[idcount]);
//				printf("rz: %f\n", o3dData[0].rz[idcount]);

				std::string tempString = "";
				for (int count=28; count<60; count++) {
					if (memBlock.buffer[count+d]!=0) tempString+=memBlock.buffer[count+d];
					else break;
				}
				o3dData[0].image[idcount] = tempString;

//				printf("image: %s\n", tempString.c_str());

				tempString = "";
				for (int count=60; count<gameVars->recordSize.o3d; count++) {
					if (memBlock.buffer[count+d]!=0) tempString+=memBlock.buffer[count+d];
					else break;
				}
				o3dData[0].file[idcount] = tempString;

//				printf("file: %s\n", tempString.c_str());
				idcount++;

				o3dData[0].idcount = idcount;

//				printf("idcount: %i\n\n", o3dData[0].idcount);
			}
			if (gameVars->debug.load) printf("Done.\n");
		}
		if (gameVars->debug.load) std::cout << "Done." <<  std::endl;
		return true;
	}
	catch(...) {
		return false;
	}
	return false;
}

bool O3D_Dungeon::calc() {
	cout << "============ O3D::calc" << endl;
	std::string loadFile;
	std::stringstream sStream;
	try {
		for (int count=0; count < o3dData[0].idcount; count++) {
			sStream.str("");
			sStream << gameVars->dir.ply << o3dData[0].file[count];
			loadFile=sStream.str();
			if (gameVars->debug.load) std::cout << " -Loading " << loadFile << "...";
			//Core.ply.load(loadFile);
			PLY_Loader * pLoad = new PLY_Loader;
			pLoad->load(loadFile);

			if (gameVars->debug.dungeon_o3d_calc) cout << "[O3D# "<< count << "]" << endl;
			o3dData[0].vao[count].Begin(GL_TRIANGLES, pLoad->numDrawVerts, 1);
			//if (gameVars->debug.dungeon_o3d_calc) cout << "     CopyData: vVerts" << endl;
			o3dData[0].vao[count].CopyData(GLA_VERTEX,  pLoad->vVerts);
			//if (gameVars->debug.dungeon_o3d_calc) cout << "     CopyData: vNorms" << endl;
			o3dData[0].vao[count].CopyData(GLA_NORMAL,  pLoad->vNorms);
			//if(gameVars->debug.dungeon_o3d_calc) cout << "     CopyData: vCoords" << endl;
			o3dData[0].vao[count].CopyData(GLA_TEXTURE, pLoad->vCoords, 0);
			//if (gameVars->debug.dungeon_o3d_calc) cout << "     CopyData: vIndex" << endl;
			o3dData[0].vao[count].CopyData(GLA_INDEX,   pLoad->vIndex);
			o3dData[0].vao[count].End();
			delete pLoad;
		}
		return true;
	}
	catch (...) {
		return false;
	}
	return false;
}

void O3D_Dungeon::draw(Atmosphere &a, bool bShadow=false) {
	glDisable(GL_CULL_FACE);
	if (bShadow) Core.shader.use(GLS_DIRECTIONAL);
	else Core.shader.use(GLS_SHADED_TEX);
	for (int count=0; count < o3dData[0].idcount; count++) {
		Core.matrix.Push();
			gameVars->texture.sprite.Set(o3dData[0].image[count]);
			Core.matrix.Translate((o3dData[0].x[count]*32)+16, (o3dData[0].blend[count])+20, (o3dData[0].z[count]*32)+16);
			Core.matrix.Rotate(M_DegToRad(o3dData[0].rx[count]), 1, 0, 0);
			Core.matrix.Rotate(M_DegToRad(o3dData[0].ry[count]), 0, 1, 0);
			Core.matrix.Rotate(M_DegToRad(o3dData[0].rz[count]), 0, 0, 1);
			Core.matrix.Scale(o3dData[0].sx[count], o3dData[0].sy[count], o3dData[0].sz[count]);
			Core.matrix.SetTransform();
			if (bShadow) Core.shader.getUniform(GLS_DIRECTIONAL);
			else Core.shader.getUniform(GLS_SHADED_TEX);
			o3dData[0].vao[count].Draw(GLM_DRAW_ELEMENTS);
		Core.matrix.Pop();
	}
	glEnable(GL_CULL_FACE);
}
#endif /* O3D_Dungeon_H_ */
