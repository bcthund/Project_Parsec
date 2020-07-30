/*
 * map.h
 *
 *  Created on: Sep 19, 2010
 *      Author: bcthund
 */

#ifndef WORLDMAP_H_
#define WORLDMAP_H_

/*
 * This class loads and manages a grid of terrain chunks.
 *
 * Provided functions:
 * 	- float getHeight(x, y)
 * 	- float getHeight(x, y, gX, gY)
 * 	- float * getHeight(x, y, gX, gY)
 */

#include <chrono>	// Used for random Seed for Map perlin (temporary)
#include <libnoise/noise.h>
#include "../core/core_functions.h"
#include "../core/vao.h"
#include "../core/texture.h"
#include "../core/FractalNoise.h"

namespace Core {
	namespace GameSys {
		// New MapData struct for VAO use
		struct MapData {
			Data3f * vVerts;
			Data3f * vNorms;
			Data2f * vCoords;
//			GLushort * vIndex;
			GLuint * vIndex;
			Vector3ui * vGroups;
			long numDrawVerts;
			long numVerts;
			long numFaces;
//			VAO * vao;

//			void reset(int vert, int face) {
//				/*
//				 * THIS MIGHT CAUSE PROBLEMS!!! But the VAO isn't destroyed
//				 * if we don't do this.
//				 */
//				delete vao;
//				delete [] vVerts;
//				delete [] vNorms;
//				delete [] vCoords;
//				delete [] vIndex;
//				delete [] vGroups;
//
//				numVerts = vert;
//				numFaces = face;
//				numDrawVerts = face*3;
//
//				vVerts = new Data3f[vert];
//				vNorms = new Data3f[vert];
//				vCoords = new Data2f[vert];
//				vIndex = new ushort[face*3];
//				vGroups = new Vector3ui[vert];
//				vao = new VAO;
//			}

			MapData() {
				numVerts = 0;
				numFaces = 0;
				numDrawVerts = 0;

				vVerts  = nullptr;
				vNorms  = nullptr;
				vCoords = nullptr;
				vIndex  = nullptr;
				vGroups = nullptr;
//				vao = new VAO;
			}

			~MapData() {
				delete[] vVerts;
				delete[] vNorms;
				delete[] vCoords;
				delete[] vIndex;
				delete[] vGroups;
//				delete vao;
			}

		};

		class MapSys {
			private:
				enum eTerrainType { TERRAIN_FLAT, TERRAIN_PERLIN, TERRAIN_SIMPLEX, TERRAIN_FRACTAL };
				//void generateTerrainChunk(MapData &map, float SIZE, Vector2i OFFSET, int VERTEX_COUNT);
				void generateTerrainChunk(MapData &map, float SIZE, int VERTEX_COUNT, eTerrainType eType=TERRAIN_PERLIN, int iTexScale=1, float fHeightOffset=0.0f);

				// Setup Perlin Noise
				//unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
				//std::string str = "Planet Test";
				//std::seed_seq seed2{1,2,3,4,5};
				//std::seed_seq seed2{str.begin(), str.end()};
				unsigned seed1 = 42;
				unsigned seed2 = 1024;
				unsigned seed3 = 420;
				std::minstd_rand0 rng1;
				std::minstd_rand0 rng2;
				std::minstd_rand0 rng3;
				noise::module::Perlin gen1;
				noise::module::Perlin gen2;
				noise::module::Perlin gen3;
				double noise1(double nx, double ny) { return gen1.GetValue(nx, ny, 0) / 2.0 + 0.5; }
				double noise2(double nx, double ny) { return gen2.GetValue(nx, ny, 0) / 2.0 + 0.5; }
				double noise3(double nx, double ny) { return gen3.GetValue(nx, ny, 0) / 2.0 + 0.5; }
//				double noise1(double nx, double ny) { return gen1.GetValue(nx, ny, 0); }
//				double noise2(double nx, double ny) { return gen2.GetValue(nx, ny, 0); }

//				const int RES = 256;
//				const float TEX_SCALE = 128.0f;
//				const int TERRAIN_SIZE = 16384;
				const eTerrainType TERRAIN_TYPE = TERRAIN_SIMPLEX;
//				const float TERRAIN_HEIGHT_OFFSET = -500.0f;
//				const eTerrainType TERRAIN_TYPE = TERRAIN_PERLIN;

//for (var y = 0; y < height; y++) {
//  for (var x = 0; x < width; x++) {
//    var nx = x/width - 0.5, ny = y/height - 0.5;
//    var e = (0.55 * noise1( 1 * nx,  1 * ny)
//           + 0.69 * noise1( 2 * nx,  2 * ny)
//           + 0.19 * noise1( 4 * nx,  4 * ny)
//           + 0.24 * noise1( 8 * nx,  8 * ny)
//           + 0.17 * noise1(16 * nx, 16 * ny)
//           + 0.20 * noise1(32 * nx, 32 * ny));
//    e /= (0.55+0.69+0.19+0.24+0.17+0.20);
//    e = Math.pow(e, 9.24);
//    var m = (1.00 * noise2( 1 * nx,  1 * ny)
//           + 0.50 * noise2( 2 * nx,  2 * ny)
//           + 0.24 * noise2( 4 * nx,  4 * ny)
//           + 0.52 * noise2( 8 * nx,  8 * ny)
//           + 0.09 * noise2(16 * nx, 16 * ny)
//           + 0.00 * noise2(32 * nx, 32 * ny));
//    m /= (1.00+0.50+0.24+0.52+0.09+0.00);
//    /* draw biome(e, m) at x,y */
//  }
//}

			protected:

			public:
				MapSys() {
					mapData = nullptr;
					//gen1 = PerlinNoise(rng1());
					//gen2 = PerlinNoise(rng2());
				}
				~MapSys() {
					std::cout << "Destroy Map......................................................";
					for (int n=0; n<data.iSize; n++) {
//						mapData[n] = new VAO[data.iSize];
						delete[] mapData[n];
					}
					delete[] mapData;
					std::cout << "Done" << std::endl;
				}
//				enum eMapShift { SHIFT_NONE, SHIFT_NORTH, SHIFT_SOUTH, SHIFT_EAST, SHIFT_WEST, SHIFT_LAST };
		//		WorldMap(Atmosphere *a, std::string d): atmosphere(a), dir(d) {
					//mapData = new MapData*[9];
					//for(int i=0; i<9; i++) {
					//	mapData[i] = new MapData[9];
					//}
		//		}

		//		~WorldMap() {
					//       .................................................................Done
		//			cout << "Destroy WorldMap.................................................Not Implemented" << endl;
		//		}

				struct _MapSysData {
//					Vector2f 	vfStartPos;
//					Vector2i 	viStartMap;		// I.E. Planet ID, change to string?
					int			iSize;			// (1=1x1 DO NOT USE), 2=3x3, 3=5x5...n=(n*2-1)x(n*2-1)
					//int			iOffset;

					_MapSysData() {
						iSize = 3;
						//iOffset = 0;
					}
				} data;

				std::string dir;			// Directory location for map
		//		Vector2i  vStart;
		//		Vector2ui vBase;
//				MapData mapData[9][9];		// Hardcoded max map size
				VAO ** mapData;
				MapData terrainChunk[4];		// Generic terrain chunk (TODO: LOD array)
				Texture tex;				// Map specific textures
		//		bool	bSkip[81];			// TODO: Temporary occlusion cull technique, skip drawing every other frame
				bool init();
		//		bool init(int iSx, int iSz);
		//		bool init(int iSx, int iSz, int iPx, int iPy, int iPz);
				bool load();
		//		void shift(int iShift);
		//		void stitch(unsigned int iStitch, int x, int z);
		//		void updateNorms(int x, int z);
				bool calc();
		//		void modify(MOD_VAL eMod, float fNewVal);
				void update();
				void draw(Core::SHADER_PROGRAMS iShader, Core::_Lights &lights);
		//		void reset(Atmosphere *a, std::string d);
				double getPerlinElevation(float x, float z, float w, float h);
				double getPerlinMoisture(float x, float z, float w, float h);
				double getSimplexElevation(float x, float z);		// w and h for convenience, not used
				double getSimplexElevation(float x, float z, float freq, float amp, float lac, float per, int oct);
				double getFractalElevation(float x, float z);
		//		float getHeight(float x, float z);
		//		float getHeight(float iX, float iZ, int gX, int gZ);
		//		float * getHeight_Normal(float x, float z);
		//		Atmosphere *atmosphere;		//The parents atmosphere
		};

		/*
		 * TODO: reset(); Reset in preparation for new map data
		 */
		//void MapSys::reset(Atmosphere *a, std::string d) {
		//	cout << "Resetting Map Data...";
		//	//new(&atmosphere) Atmosphere(a);
		//	atmosphere = a;
		//	dir = d;
		//	//mapData = new MapData*[9];
		//	//for(int i=0; i<9; i++) {
		//	//	mapData[i] = new MapData[9];
		//	//}
		//	cout << "Done" << endl;
		//}

		/*
		 * TODO: init(); Load map starting location and player location from file
		 */
		bool MapSys::init() {
			try {
				//            .................................................................Done
//				std::cout << sOffset << "Init Map.........................................................";
				std::cout << sOffset << "Init Map.........................................................Not Implemented" << std::endl;

				rng1 = std::minstd_rand0(seed1);
				rng2 = std::minstd_rand0(seed2);
				rng3 = std::minstd_rand0(seed3);

				gen1.SetSeed(rng1());
				gen2.SetSeed(rng2());
				gen3.SetSeed(rng3());

				//std:: cout << gen1.GetValue(1,1,0) << ", " << gen1.GetValue(1,2,0) << ", " << gen1.GetValue(0.5,1,0) << ", " << gen1.GetValue(0.5,0.5,0) << ", " << gen1.GetValue(0.25,2,0) << std::endl;
				//std:: cout << noise1(1.0f,1.0f) << ", " << noise1(1.0f,2.0f) << ", " << noise1(0.5f,1.0f) << ", " << noise1(0.5f,0.5f) << ", " << noise1(0.25f,2.0f) << std::endl;

				// TODO: Pointer cleanup
//				if (data.iSize > 1) {
				mapData = new VAO*[data.iSize];
				for (int n=0; n<data.iSize; n++) {
					mapData[n] = new VAO[data.iSize];
				}
//				}
//				else {
//					mapData = new VAO;
//				}

//		//		bool bReadResult;
//		//		MemBlock memBlock;
//		//		std::string loadFile;
//		//		std::stringstream  *sStream = new std::stringstream;
//		//		sStream->str("");
//		//		*sStream << dir << "map.bin";
//		//		loadFile=sStream->str();
//		//		if (gameVars->debug.load) std::cout << " -Loading " <<  loadFile << "...";
//		//		bReadResult = readFile(loadFile, memBlock); //Read the data file into memory
//		//		std::string temp2 = itoa((unsigned char)memBlock.buffer[0], 10);
//		//
//		//		__int16_t uiMx	=	(	(unsigned int)(memBlock.buffer[0]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[0]&0x0F)*256 +
//		//												(unsigned int)(memBlock.buffer[1]&0xF0)				+ (unsigned int)(memBlock.buffer[1]&0x0F) );
//		//
//		//		__int16_t uiMz	=	(	(unsigned int)(memBlock.buffer[2]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[2]&0x0F)*256 +
//		//												(unsigned int)(memBlock.buffer[3]&0xF0)				+ (unsigned int)(memBlock.buffer[3]&0x0F) );
//		//
//		//        // Reserved spot (Scale)
//		////        __int16_t uiLx	=	(	(unsigned int)(memBlock.buffer[4]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[4]&0x0F)*256 +
//		////                                (unsigned int)(memBlock.buffer[5]&0xF0)		+ (unsigned int)(memBlock.buffer[5]&0x0F) );
//		//
//		//		__int16_t uiLx	=	(	(unsigned int)(memBlock.buffer[6]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[6]&0x0F)*256 +
//		//												(unsigned int)(memBlock.buffer[7]&0xF0)				+ (unsigned int)(memBlock.buffer[7]&0x0F) );
//		//
//		//        // Reserved spot
//		////        __int16_t uiLx	=	(	(unsigned int)(memBlock.buffer[8]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[8]&0x0F)*256 +
//		////                                (unsigned int)(memBlock.buffer[9]&0xF0)		+ (unsigned int)(memBlock.buffer[9]&0x0F) );
//		//
//		//		__int16_t uiLz	=	(	(unsigned int)(memBlock.buffer[10]&0xF0)*256  + (unsigned int)(memBlock.buffer[10]&0x0F)*256 +
//		//												(unsigned int)(memBlock.buffer[11]&0xF0)			+ (unsigned int)(memBlock.buffer[11]&0x0F) );
//		//
//		//		vStart[0] = uiMx;
//		//		vStart[1] = uiMz;
//		//		gameVars->player.active->transform.pos[0]=-uiLx;
//		//		gameVars->player.active->transform.pos[2]=-uiLz;
//		//
//		//		//vStart[0]=(unsigned char)memBlock.buffer[0]+(unsigned char)memBlock.buffer[1];
//		//		//vStart[1]=(unsigned char)memBlock.buffer[2]+(unsigned char)memBlock.buffer[3];
//		//		//gameVars->player.active->transform.pos[0]=-((unsigned char)memBlock.buffer[4]+(unsigned char)memBlock.buffer[5]+(unsigned char)memBlock.buffer[6]+(unsigned char)memBlock.buffer[7]);
//		//		//gameVars->player.active->transform.pos[2]=-((unsigned char)memBlock.buffer[8]+(unsigned char)memBlock.buffer[9]+(unsigned char)memBlock.buffer[10]+(unsigned char)memBlock.buffer[11]);
//		//
//		//		cout << "=================================> (" << gameVars->player.active->transform.pos[0] << ", " << gameVars->player.active->transform.pos[2] << ")" << endl;
//		//		gameVars->player.active->transform.pos[0]-=gameVars->screen.iGridOffset*1024;
//		//		gameVars->player.active->transform.pos[2]-=gameVars->screen.iGridOffset*1024;
//		//		cout << "=================================> (" << gameVars->player.active->transform.pos[0] << ", " << gameVars->player.active->transform.pos[2] << ")" << endl;
//		//		delete sStream;
//				std::cout << "Done" << std::endl;
			}
			catch(...) {
				cout(E) << "MapSys::init()" << std::endl;
				return false;
			}
			return true;
		}

		/*
		 * Create generic terrain chunks
		 */
		bool MapSys::load() {
			try {
				//            .................................................................Done
				std::cout << sOffset << "Load Map.........................................................";
//				// Load Single Map
//				MemBlock memBlock;
//				std::stringstream *sStream = new std::stringstream;
//				sStream->str("");
//				*sStream << dir << 100 << "-" << 100 << ".ply";
//				std::cout << "> Loading " <<  sStream->str() << "...";
//				std::cout << "Done." <<  std::endl;
//				bool bReadResult = readFile(sStream->str(), memBlock);		//Read the data file into memory
//				if (!bReadResult) {
//					std::cout << "Doesn't exist, abort";
//				}
//				else {
//					PLY_Loader pLoad;
//					pLoad.load(sStream->str());
//					mapData[0][0]
//				}
//				delete sStream;

//				generateTerrainChunk(terrainChunk[0], 1024, Vector2i(0), 129);				//1024 actual size (scale), 1025 vertices for 1024 quads
//				generateTerrainChunk(terrainChunk[1], 1024, Vector2i(1024,0), 129);			//1024 actual size (scale), 1025 vertices for 1024 quads
//				generateTerrainChunk(terrainChunk[2], 1024, Vector2i(0,1024), 129);			//1024 actual size (scale), 1025 vertices for 1024 quads
//				generateTerrainChunk(terrainChunk[3], 1024, Vector2i(1024, 1024), 129);		//1024 actual size (scale), 1025 vertices for 1024 quads

//				generateTerrainChunk(terrainChunk[0], 8192, 129);
//				generateTerrainChunk(terrainChunk[0], 8192, 257);
//				generateTerrainChunk(terrainChunk[0], 8192, 1025);
//				generateTerrainChunk(terrainChunk[0], 16384, 1025);
//				generateTerrainChunk(terrainChunk[0], 16384, 2049);

				/*
				 * Simulate loading entire world (first load essentially)
				 */
				Core::profiles->startProfile(Core::profiles->builtIn.MapSys_GeneratePerlin);
				std::cout << std::endl;
				std::cout << "====================================================" << std::endl;
				std::cout << "==========       Generating Terrain       ==========" << std::endl;
				std::cout << "====================================================" << std::endl;
//				int i3count = std::pow(3,2);
//				std::cout << "3x3(" << i3count << ").";
//				for (int n=0; n<i3count; n++) {
//					generateTerrainChunk(terrainChunk[0], 2048, 2048, TERRAIN_PERLIN, 1);
//					generateTerrainChunk(terrainChunk[0], 16384, 512, TERRAIN_SIMPLEX, 1);

					switch(TERRAIN_TYPE) {
						case TERRAIN_PERLIN:
							generateTerrainChunk(terrainChunk[0], 2048, 2048, TERRAIN_PERLIN, 1);
//							generateTerrainChunk(	terrainChunk[0],
//											Core::gameVars->debug.noise.perlin[Core::gameVars->debug.noise.iCurrentSimplex].terrain_size,
//											Core::gameVars->debug.noise.perlin[Core::gameVars->debug.noise.iCurrentSimplex].res+1,
//											TERRAIN_TYPE,
//											Core::gameVars->debug.noise.perlin[Core::gameVars->debug.noise.iCurrentSimplex].tex_scale,
//											Core::gameVars->debug.noise.perlin[Core::gameVars->debug.noise.iCurrentSimplex].terrain_height_offset);
							break;
						case TERRAIN_SIMPLEX:
							generateTerrainChunk(	terrainChunk[0],
											Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].terrain_size,
											Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].res+1,
											TERRAIN_TYPE,
											Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].tex_scale,
											Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].terrain_height_offset);
							break;
						case TERRAIN_FRACTAL:
							generateTerrainChunk(	terrainChunk[0],
											Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].terrain_size,
											Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].res+1,
											TERRAIN_TYPE,
											Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].tex_scale,
											Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].terrain_height_offset);
							break;
					}
//					std::cout << n << ".";
//				}
//				int i5count = std::pow(5,2)-std::pow(5-2,2);
//				std::cout << "Done" << std::endl << "5x5(" << i5count << ").";
//				for (int n=0; n<i5count; n++) {
//					generateTerrainChunk(terrainChunk[1], 16384, 257, TERRAIN_SIMPLEX, 1, -500);
//					std::cout << n << ".";
//				}
//				int i7count = std::pow(7,2)-std::pow(7-2,2);
//				std::cout << "Done" << std::endl << "7x7(" << i7count << ").";
//				for (int n=0; n<i7count; n++) {
//					generateTerrainChunk(terrainChunk[2], 16384, 129, TERRAIN_SIMPLEX, 1, -1000);
//					std::cout << n << ".";
//				}
//				int i9count = std::pow(9,2)-std::pow(9-2,2);
//				std::cout << "Done" << std::endl << "9x9(" << i9count << ").";
//				for (int n=0; n<i9count; n++) {
//					generateTerrainChunk(terrainChunk[3], 16384, 65, TERRAIN_SIMPLEX, 1, -1500);
//					std::cout << n << ".";
//				}
				std::cout << "Done" << std::endl;
				Core::profiles->stopProfile(Core::profiles->builtIn.MapSys_GeneratePerlin);
				std::cout << std::endl;
				std::cout << "Elapsed Time = " << Core::profiles->getTime(Core::profiles->builtIn.MapSys_GeneratePerlin) << std::endl;
				std::cout << "====================================================" << std::endl;


				//generateTerrainChunk(terrainChunk[1], 1024, 33, TERRAIN_FLAT, 1000, 250);

//				generateTerrainChunk(terrainChunk[0], 1024, 257);	// 256x256
//				generateTerrainChunk(terrainChunk[0], 1024, 129);	// 128x128
//				generateTerrainChunk(terrainChunk[1], 1024, 65);	// 64x64
//				generateTerrainChunk(terrainChunk[2], 1024, 33);	// 32x32
//				generateTerrainChunk(terrainChunk[3], 1024, 17);	// 16x16

				std::cout << "Done" << std::endl;
				return true;
			}
			catch(...) {
				cout(E) << "MapSys::load()" << std::endl;
				return false;
			}
		}

		/*
		 * Original
		 * 		Author: ThinMatrix
		 * 		Title: OpenGL Game Tutorial 14: Simple Terrain
		 * 		Address: https://www.dropbox.com/s/47qk4yrz5v9lb61/Terrain%20Generation%20Code.txt?dl=0
		 * 		Modified: 2020-03-04
		 *
		 * Size = physical size of chunk (1024 typical)
		 * Vertex_Count = Number of vertices per side (can be used for LOD?)
		 */
		//void MapSys::generateTerrainChunk(MapData &chunk, float SIZE, Vector2i OFFSET, int VERTEX_COUNT){
		void MapSys::generateTerrainChunk(MapData &chunk, float SIZE, int VERTEX_COUNT, eTerrainType eType, int iTexScale, float fHeightOffset){
			//int count = VERTEX_COUNT * VERTEX_COUNT;
			chunk.numVerts = VERTEX_COUNT * VERTEX_COUNT;
			chunk.numDrawVerts = 6*(VERTEX_COUNT-1)*(VERTEX_COUNT-1);

			//float * vertices = new float[count * 3];
			chunk.vVerts = new Data3f[chunk.numVerts];

			//float * normals = new float[count * 3];
			chunk.vNorms = new Data3f[chunk.numVerts];

			//float * textureCoords = new float[count*2];
			chunk.vCoords = new Data2f[chunk.numVerts];

			//int * indices = new int[6*(VERTEX_COUNT-1)*(VERTEX_COUNT-1)];
//			chunk.vIndex = new GLushort[chunk.numDrawVerts];
			chunk.vIndex = new GLuint[chunk.numDrawVerts];


//			float delta = (1.0f/((float)VERTEX_COUNT - 1) * SIZE) * 2.0F;
//			float delta = 4096.0f;


			long vertexPointer = 0;
			for(int i=0;i<VERTEX_COUNT;i++){
				for(int j=0;j<VERTEX_COUNT;j++){

					// Vertex
					chunk.vVerts[vertexPointer][0] = ((float)j/((float)VERTEX_COUNT - 1) * SIZE);
					chunk.vVerts[vertexPointer][2] = ((float)i/((float)VERTEX_COUNT - 1) * SIZE);
					switch(eType) {
						case TERRAIN_PERLIN:
							chunk.vVerts[vertexPointer][1] = getPerlinElevation(chunk.vVerts[vertexPointer][0], chunk.vVerts[vertexPointer][2], 1024, 1024) + fHeightOffset;
							break;
						case TERRAIN_SIMPLEX:
							chunk.vVerts[vertexPointer][1] = getSimplexElevation(chunk.vVerts[vertexPointer][0], chunk.vVerts[vertexPointer][2]) + fHeightOffset;
							break;
						case TERRAIN_FRACTAL:
							chunk.vVerts[vertexPointer][1] = getFractalElevation(chunk.vVerts[vertexPointer][0], chunk.vVerts[vertexPointer][2]) + fHeightOffset;
							break;
						default:
							chunk.vVerts[vertexPointer][1] = fHeightOffset;
					}

					Vector3f modelXOffset,
							 modelYOffset,
							 modelXGrad,
							 modelYGrad,
							 A, B, C, BA, CA, Dir, Norm;

					switch(eType) {
						case TERRAIN_PERLIN:
							A = chunk.vVerts[vertexPointer];

							B.x = A.x+Core::gameVars->debug.noise.simplex[0].delta;
							B.z = A.z+Core::gameVars->debug.noise.simplex[0].delta;
							B.y = getPerlinElevation(B.x, B.z, 1024, 1024) + fHeightOffset;

							C.x = A.x+Core::gameVars->debug.noise.simplex[0].delta;
							C.z = A.z-Core::gameVars->debug.noise.simplex[0].delta;
							C.y = getPerlinElevation(C.x, C.z, 1024, 1024) + fHeightOffset;

							BA = B - A;
							CA = C - A;
							Dir = Core::gmath.Cross(BA, CA);
							Norm = Dir/Dir.length();
							break;
						case TERRAIN_SIMPLEX:
							A = chunk.vVerts[vertexPointer];

							B.x = A.x+Core::gameVars->debug.noise.simplex[0].delta;
							B.z = A.z+Core::gameVars->debug.noise.simplex[0].delta;
							B.y = getSimplexElevation(B.x, B.z) + fHeightOffset;

							C.x = A.x+Core::gameVars->debug.noise.simplex[0].delta;
							C.z = A.z-Core::gameVars->debug.noise.simplex[0].delta;
							C.y = getSimplexElevation(C.x, C.z) + fHeightOffset;

							BA = B - A;
							CA = C - A;
							Dir = Core::gmath.Cross(BA, CA);
							Norm = Dir/Dir.length();
							break;
						case TERRAIN_FRACTAL:
							A = chunk.vVerts[vertexPointer];

							B.x = A.x+Core::gameVars->debug.noise.fractal[0].delta;
							B.z = A.z+Core::gameVars->debug.noise.fractal[0].delta;
							B.y = getFractalElevation(B.x, B.z) + fHeightOffset;

							C.x = A.x+Core::gameVars->debug.noise.fractal[0].delta;
							C.z = A.z-Core::gameVars->debug.noise.fractal[0].delta;
							C.y = getFractalElevation(C.x, C.z) + fHeightOffset;

							BA = B - A;
							CA = C - A;
							Dir = Core::gmath.Cross(BA, CA);
							Norm = Dir/Dir.length();
							break;
						default:
							chunk.vNorms[vertexPointer][0] = 0;
							chunk.vNorms[vertexPointer][1] = 1;
							chunk.vNorms[vertexPointer][2] = 0;
					}

//					if (i==30 && j==50) {
//					std::cout << "A = (" << A.x << ", " << A.y << ", " << A.z << ")" << std::endl;
//					std::cout << "B = (" << B.x << ", " << B.y << ", " << B.z << ")" << std::endl;
//					std::cout << "C = (" << C.x << ", " << C.y << ", " << C.z << ")" << std::endl;
//					std::cout << "BA = (" << BA.x << ", " << BA.y << ", " << BA.z << ")" << std::endl;
//					std::cout << "CA = (" << CA.x << ", " << CA.y << ", " << CA.z << ")" << std::endl;
//					std::cout << "Dir = (" << Dir.x << ", " << Dir.y << ", " << Dir.z << ")" << std::endl;
//					std::cout << "Norm = (" << Norm.x << ", " << Norm.y << ", " << Norm.z << ")" << std::endl << std::endl;
//					}

					// Normals - What is expected to work but DOES NOT
					chunk.vNorms[vertexPointer][0] = Norm.x;
					chunk.vNorms[vertexPointer][1] = Norm.y;
					chunk.vNorms[vertexPointer][2] = Norm.z;

					// Texture
					chunk.vCoords[vertexPointer][0] = (float)j/((float)VERTEX_COUNT - 1) * (float)iTexScale;
					chunk.vCoords[vertexPointer][1] = (float)i/((float)VERTEX_COUNT - 1) * (float)iTexScale;
					vertexPointer++;
				}
			}
			long pointer = 0;
			for(uint gz=0;gz<VERTEX_COUNT-1;gz++){
				for(uint gx=0;gx<VERTEX_COUNT-1;gx++){
					uint topLeft = (gz*VERTEX_COUNT)+gx;
					uint topRight = topLeft + 1;
					uint bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
					uint bottomRight = bottomLeft + 1;
					chunk.vIndex[pointer++] = topLeft;			//std::cout << "[(" << chunk.vIndex[pointer-1];
					chunk.vIndex[pointer++] = bottomLeft;		//std::cout << ", " << chunk.vIndex[pointer-1];
					chunk.vIndex[pointer++] = topRight;			//std::cout << ", " << chunk.vIndex[pointer-1];
					chunk.vIndex[pointer++] = topRight;			//std::cout << ")(" << chunk.vIndex[pointer-1];
					chunk.vIndex[pointer++] = bottomLeft;		//std::cout << ", " << chunk.vIndex[pointer-1];
					chunk.vIndex[pointer++] = bottomRight;		//std::cout << ", " << chunk.vIndex[pointer-1] << ")]" << std::endl;

//					std::cout << "[(" << topLeft << ", " << bottomLeft << ", " << topRight << ")(" << topRight << ", " << bottomLeft << ", " << bottomRight << ")]" << std::endl << std::endl;
				}
			}

//			std::cout << std::endl;
//			std::cout << std::endl;
//			std::cout << "numDrawVerts = " << chunk.numDrawVerts << ", ";
//			std::cout << "pointer = " << pointer << std::endl;
		}


		/*
		 * TODO: Calc(); Do general map calculations. (including LOD management?)
		 */
		bool MapSys::calc() {
			//            .................................................................Done
			std::cout << sOffset << "Calc Map.........................................................";


//			std::cout << sOffset << "\t Perlin Noise Test...";

//			int height = 1024,
//				width  = 1024;
//
//			// e = elevation
//			// m = moisture (biome)
//			for (int y = 0; y < height; y++) {
//			  for (int x = 0; x < width; x++) {
//				int nx = x/width - 0.5, ny = y/height - 0.5;
//				double e = (0.55 * noise1( 1 * nx,  1 * ny)
//					      + 0.69 * noise1( 2 * nx,  2 * ny)
//					      + 0.19 * noise1( 4 * nx,  4 * ny)
//					      + 0.24 * noise1( 8 * nx,  8 * ny)
//					      + 0.17 * noise1(16 * nx, 16 * ny)
//					      + 0.20 * noise1(32 * nx, 32 * ny));
//				e /= (0.55+0.69+0.19+0.24+0.17+0.20);
//				e = std::pow(e, 9.24);
//				double m = (1.00 * noise2( 1 * nx,  1 * ny)
//					      + 0.50 * noise2( 2 * nx,  2 * ny)
//					      + 0.24 * noise2( 4 * nx,  4 * ny)
//					      + 0.52 * noise2( 8 * nx,  8 * ny)
//					      + 0.09 * noise2(16 * nx, 16 * ny)
//					      + 0.00 * noise2(32 * nx, 32 * ny));
//				m /= (1.00+0.50+0.24+0.52+0.09+0.00);
//				/* draw biome(e, m) at x,y */
//			  }
//			}


//			std::cout << std::endl;

//			for (int x=0; x<data.iSize; x++) {
//				for (int z=0; z<data.iSize; z++) {
//
////					if(x==0 and z==0) {
////						std::cout << "[" << x << ", " << z << "] - " << terrainChunk.numVerts << ", " << terrainChunk.numDrawVerts << std::endl;
////						std::cout << "\t" << "(" << terrainChunk.vVerts[0][0] << ", " << terrainChunk.vVerts[0][1] << ", " << terrainChunk.vVerts[0][2] << ")" << std::endl;
////						std::cout << "\t" << "(" << terrainChunk.vVerts[1][0] << ", " << terrainChunk.vVerts[1][1] << ", " << terrainChunk.vVerts[1][2] << ")" << std::endl;
////						std::cout << "\t" << "(" << terrainChunk.vVerts[2][0] << ", " << terrainChunk.vVerts[2][1] << ", " << terrainChunk.vVerts[2][2] << ")" << std::endl;
////						std::cout << "\t" << "(" << terrainChunk.vVerts[3][0] << ", " << terrainChunk.vVerts[3][1] << ", " << terrainChunk.vVerts[3][2] << ")" << std::endl;
////						std::cout << "\t" << "(" << terrainChunk.vVerts[4][0] << ", " << terrainChunk.vVerts[4][1] << ", " << terrainChunk.vVerts[4][2] << ")" << std::endl;
////						std::cout << "\t" << "(" << terrainChunk.vVerts[5][0] << ", " << terrainChunk.vVerts[5][1] << ", " << terrainChunk.vVerts[5][2] << ")" << std::endl;
//
////						std::cout << "\t" << "(" << terrainChunk.vIndex[0] << ") - ";
////						std::cout << "(" << terrainChunk.vVerts[0][0] << ", " << terrainChunk.vVerts[0][1] << ", " << terrainChunk.vVerts[0][2] << ")" << std::endl;
////
////						std::cout << "\t" << "(" << terrainChunk.vIndex[1] << ") - ";
////						std::cout << "(" << terrainChunk.vVerts[1025][0] << ", " << terrainChunk.vVerts[1025][1] << ", " << terrainChunk.vVerts[1025][2] << ")" << std::endl;
////
////						std::cout << "\t" << "(" << terrainChunk.vIndex[2] << ") - ";
////						std::cout << "(" << terrainChunk.vVerts[1][0] << ", " << terrainChunk.vVerts[1][1] << ", " << terrainChunk.vVerts[1][2] << ")" << std::endl;
////
////						std::cout << "\t" << "(" << terrainChunk.vIndex[3] << ") - ";
////						std::cout << "(" << terrainChunk.vVerts[1][0] << ", " << terrainChunk.vVerts[1][1] << ", " << terrainChunk.vVerts[1][2] << ")" << std::endl;
////
////						std::cout << "\t" << "(" << terrainChunk.vIndex[4] << ") - ";
////						std::cout << "(" << terrainChunk.vVerts[1025][0] << ", " << terrainChunk.vVerts[1025][1] << ", " << terrainChunk.vVerts[1025][2] << ")" << std::endl;
////
////						std::cout << "\t" << "(" << terrainChunk.vIndex[5] << ") - ";
////						std::cout << "(" << terrainChunk.vVerts[1026][0] << ", " << terrainChunk.vVerts[1026][1] << ", " << terrainChunk.vVerts[1026][2] << ")" << std::endl;
////					}
//
//					mapData[x][z].Begin(GL_TRIANGLES, terrainChunk.numVerts, terrainChunk.numDrawVerts, 1);
//					mapData[x][z].CopyData(GLA_VERTEX, terrainChunk.vVerts);
//					mapData[x][z].CopyData(GLA_NORMAL, terrainChunk.vNorms);
//					mapData[x][z].CopyData(GLA_TEXTURE, terrainChunk.vCoords, 0);
//					mapData[x][z].CopyData(GLA_INDEX, terrainChunk.vIndex);
//					mapData[x][z].End();
//				}
//			}

			mapData[0][0].Begin(GL_TRIANGLES, terrainChunk[0].numVerts, terrainChunk[0].numDrawVerts, 1);
			mapData[0][0].CopyData(GLA_VERTEX, terrainChunk[0].vVerts);
			mapData[0][0].CopyData(GLA_NORMAL, terrainChunk[0].vNorms);
			mapData[0][0].CopyData(GLA_TEXTURE, terrainChunk[0].vCoords, 0);
			mapData[0][0].CopyData(GLA_INDEX, terrainChunk[0].vIndex, terrainChunk[0].numDrawVerts);
//			mapData[0][0].CopyData(GLA_INDEX, terrainChunk[0].vIndex);
			mapData[0][0].End();

//			mapData[0][1].Begin(GL_TRIANGLES, terrainChunk[1].numVerts, terrainChunk[1].numDrawVerts, 1);
//			mapData[0][1].CopyData(GLA_VERTEX, terrainChunk[1].vVerts);
//			mapData[0][1].CopyData(GLA_NORMAL, terrainChunk[1].vNorms);
//			mapData[0][1].CopyData(GLA_TEXTURE, terrainChunk[1].vCoords, 0);
//			mapData[0][1].CopyData(GLA_INDEX, terrainChunk[1].vIndex, terrainChunk[1].numDrawVerts);
////			mapData[0][1].CopyData(GLA_INDEX, terrainChunk[1].vIndex);
//			mapData[0][1].End();
//
//			mapData[1][0].Begin(GL_TRIANGLES, terrainChunk[2].numVerts, terrainChunk[2].numDrawVerts, 1);
//			mapData[1][0].CopyData(GLA_VERTEX, terrainChunk[2].vVerts);
//			mapData[1][0].CopyData(GLA_NORMAL, terrainChunk[2].vNorms);
//			mapData[1][0].CopyData(GLA_TEXTURE, terrainChunk[2].vCoords, 0);
//			mapData[1][0].CopyData(GLA_INDEX, terrainChunk[2].vIndex, terrainChunk[2].numDrawVerts);
////			mapData[1][0].CopyData(GLA_INDEX, terrainChunk[2].vIndex);
//			mapData[1][0].End();
//
//			mapData[1][1].Begin(GL_TRIANGLES, terrainChunk[3].numVerts, terrainChunk[3].numDrawVerts, 1);
//			mapData[1][1].CopyData(GLA_VERTEX, terrainChunk[3].vVerts);
//			mapData[1][1].CopyData(GLA_NORMAL, terrainChunk[3].vNorms);
//			mapData[1][1].CopyData(GLA_TEXTURE, terrainChunk[3].vCoords, 0);
//			mapData[1][1].CopyData(GLA_INDEX, terrainChunk[3].vIndex, terrainChunk[3].numDrawVerts);
////			mapData[1][1].CopyData(GLA_INDEX, terrainChunk[3].vIndex);
//			mapData[1][1].End();


//
//			//Register the data
//			for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
//				for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {
//					if (bUpdate) {
//						// todo: Make sure this works, added the * due to a compiler warning
//						new(*&mapData[x][z].vao) VAO();	//We need to create new VAO objects for this to work
//						//delete mapData[x][z].vao;
//						//mapData[x][z].vao = new VAO;
//
//						//mapData[x][z].vao->Begin(GL_TRIANGLES, mapData[x][z].numDrawVerts, 8);
//						//mapData[x][z].vao->CopyData(GLA_VERTEX, mapData[x][z].vVerts);
//						//mapData[x][z].vao->CopyData(GLA_NORMAL, mapData[x][z].vNorms);
//						//mapData[x][z].vao->CopyData(GLA_TEXTURE, mapData[x][z].vCoords, 0);
//						//mapData[x][z].vao->CopyData(GLA_INDEX, mapData[x][z].vIndex);
//						//mapData[x][z].vao->End();
//					}
//					else {
//
//						/*
//						 * New VAO created in mapdata struct with reset function
//						 * called from ply_loader.
//						 */
//						//if(mapData[x][z].vao->bStarted) {
//							//cout << "Destroy Old World...";
//							//new(&mapData[x][z].vao) VAO();
//							//new(&mapData[x][z].vao) VAO();
//			//				mapData[x][z].vao = new VAO();
//							//cout << "Done" << endl;
//						//}
//						//delete mapData[x][z].vao;
//						//mapData[x][z].vao = new VAO;
//
//						// TODO: LOD Testing, redefine index array
//		//				uint uiINDEXES_02;
//		//				if(x==0 && z==2) {
//		//					cout << "Remap Index for LOD test..." << endl;
//		//					ushort * vNew;
//		//					vNew = new ushort[mapData[x][z].numDrawVerts];
//		//					const uint uiMAPSIZE			= 64;					// Number of quads to a side
//		//					const uint uiLOD				= 2;					// Inverse LOD value, higher = lower detail
//		//					const uint uiVOFFSET			= 256;					// Vertical index offset for one quad
//		//					const uint uiVNEXT				= 256 * (uiLOD-1);		// Vertical index offset for LOD
//		//										 uiINDEXES_02		= 6 * ((uiMAPSIZE/uiLOD)*(uiMAPSIZE/uiLOD));
//		//
//		//					uint c = 0;
//		//					for(uint yy=0; yy<uiMAPSIZE-1; yy+=uiLOD) {				// == row
//		//						for(uint xx=0; xx<256; xx+=(4*uiLOD)) {
//		//							uint i = xx + ( yy * (uiVOFFSET) );
//		//							vNew[c]			= i;							// 0			//
//		//							vNew[c+1]		= i+(1+uiVNEXT);				// 769		//
//		//							vNew[c+2]		= i+(4*uiLOD-2);				// 14			//
//		//
//		//							vNew[c+3] 	= i+(4*uiLOD-2);					// 14			//
//		//							vNew[c+4]		= i+(1+uiVNEXT);				// 769		//
//		//							vNew[c+5]		= i+((4*uiLOD-1)+uiVNEXT);		// 783		//
//		//
//		//							c+=6;
//		//						}
//		//					}
//		//					mapData[x][z].vIndex = vNew;
//		//					cout << "Done" << endl;
//		//				}
//		//
//		//				uint uiINDEXES_01;
//		//				if(x==0 && z==1) {
//		//					cout << "Remap Index for LOD test..." << endl;
//		//					ushort * vNew;
//		//					vNew = new ushort[mapData[x][z].numDrawVerts];
//		//					const uint uiMAPSIZE			= 64;					// Number of quads to a side
//		//					const uint uiLOD					= 4;				// Inverse LOD value, higher = lower detail
//		//					const uint uiVOFFSET			= 256;					// Vertical index offset for one quad
//		//					const uint uiVNEXT				= 256 * (uiLOD-1);		// Vertical index offset for LOD
//		//										 uiINDEXES_01		= 6 * ((uiMAPSIZE/uiLOD)*(uiMAPSIZE/uiLOD));
//		//
//		//					uint c = 0;
//		//					for(uint yy=0; yy<uiMAPSIZE-1; yy+=uiLOD) {				// == row
//		//						for(uint xx=0; xx<256; xx+=(4*uiLOD)) {
//		//							uint i = xx + ( yy * (uiVOFFSET) );
//		//							vNew[c]			= i;							// 0			//
//		//							vNew[c+1]		= i+(1+uiVNEXT);				// 769		//
//		//							vNew[c+2]		= i+(4*uiLOD-2);				// 14			//
//		//
//		//							vNew[c+3] 	= i+(4*uiLOD-2);					// 14			//
//		//							vNew[c+4]		= i+(1+uiVNEXT);				// 769		//
//		//							vNew[c+5]		= i+((4*uiLOD-1)+uiVNEXT);		// 783		//
//		//
//		//							c+=6;
//		//						}
//		//					}
//		//					mapData[x][z].vIndex = vNew;
//		//					cout << "Done" << endl;
//		//				}
//		//
//		//				uint uiINDEXES_00;
//		//				if(x==0 && z==0) {
//		//					cout << "Remap Index for LOD test..." << endl;
//		//					ushort * vNew;
//		//					vNew = new ushort[mapData[x][z].numDrawVerts];
//		//					const uint uiMAPSIZE			= 64;					// Number of quads to a side
//		//					const uint uiLOD					= 8;				// Inverse LOD value, higher = lower detail
//		//					const uint uiVOFFSET			= 256;					// Vertical index offset for one quad
//		//					const uint uiVNEXT				= 256 * (uiLOD-1);		// Vertical index offset for LOD
//		//										 uiINDEXES_00		= 6 * ((uiMAPSIZE/uiLOD)*(uiMAPSIZE/uiLOD));
//		//
//		//					uint c = 0;
//		//					for(uint yy=0; yy<uiMAPSIZE-1; yy+=uiLOD) {				// == row
//		//						for(uint xx=0; xx<256; xx+=(4*uiLOD)) {
//		//							uint i = xx + ( yy * (uiVOFFSET) );
//		//							vNew[c]			= i;							// 0			//
//		//							vNew[c+1]		= i+(1+uiVNEXT);				// 769		//
//		//							vNew[c+2]		= i+(4*uiLOD-2);				// 14			//
//		//
//		//							vNew[c+3] 	= i+(4*uiLOD-2);					// 14			//
//		//							vNew[c+4]		= i+(1+uiVNEXT);				// 769		//
//		//							vNew[c+5]		= i+((4*uiLOD-1)+uiVNEXT);		// 783		//
//		//
//		//							c+=6;
//		//						}
//		//					}
//		//					mapData[x][z].vIndex = vNew;
//		//					cout << "Done" << endl;
//		//				}
//		//
//		//				uint uiINDEXES_10;
//		//				if(x==1 && z==0) {
//		//					cout << "Remap Index for LOD test..." << endl;
//		//					ushort * vNew;
//		//					vNew = new ushort[mapData[x][z].numDrawVerts];
//		//					const uint uiMAPSIZE			= 64;					// Number of quads to a side
//		//					const uint uiLOD					= 16;				// Inverse LOD value, higher = lower detail
//		//					const uint uiVOFFSET			= 256;					// Vertical index offset for one quad
//		//					const uint uiVNEXT				= 256 * (uiLOD-1);		// Vertical index offset for LOD
//		//										 uiINDEXES_10		= 6 * ((uiMAPSIZE/uiLOD)*(uiMAPSIZE/uiLOD));
//		//
//		//					uint c = 0;
//		//					for(uint yy=0; yy<uiMAPSIZE-1; yy+=uiLOD) {				// == row
//		//						for(uint xx=0; xx<256; xx+=(4*uiLOD)) {
//		//							uint i = xx + ( yy * (uiVOFFSET) );
//		//							vNew[c]			= i;							// 0			//
//		//							vNew[c+1]		= i+(1+uiVNEXT);				// 769		//
//		//							vNew[c+2]		= i+(4*uiLOD-2);				// 14			//
//		//
//		//							vNew[c+3] 	= i+(4*uiLOD-2);					// 14			//
//		//							vNew[c+4]		= i+(1+uiVNEXT);				// 769		//
//		//							vNew[c+5]		= i+((4*uiLOD-1)+uiVNEXT);		// 783		//
//		//
//		//							c+=6;
//		//						}
//		//					}
//		//					mapData[x][z].vIndex = vNew;
//		//					cout << "Done" << endl;
//		//				}
//
//						mapData[x][z].vao->Begin(GL_TRIANGLES, mapData[x][z].numDrawVerts, 8);
//						mapData[x][z].vao->CopyData(GLA_VERTEX, mapData[x][z].vVerts);
//						mapData[x][z].vao->CopyData(GLA_NORMAL, mapData[x][z].vNorms);
//						mapData[x][z].vao->CopyData(GLA_TEXTURE, mapData[x][z].vCoords, 0);
//						// TODO: LOD Testing, load arrays
//		//				if(x==0 && z==0) {
//		//					mapData[x][z].vao->CopyData(GLA_INDEX, mapData[x][z].vIndex, uiINDEXES_00);
//		//				} else if(x==0 && z==1) {
//		//					mapData[x][z].vao->CopyData(GLA_INDEX, mapData[x][z].vIndex, uiINDEXES_01);
//		//				} else if(x==0 && z==2) {
//		//					mapData[x][z].vao->CopyData(GLA_INDEX, mapData[x][z].vIndex, uiINDEXES_02);
//		//				} else if(x==1 && z==0) {
//		//					mapData[x][z].vao->CopyData(GLA_INDEX, mapData[x][z].vIndex, uiINDEXES_10);
//		//				} else {
//							mapData[x][z].vao->CopyData(GLA_INDEX, mapData[x][z].vIndex);
//		//				}
//
//						mapData[x][z].vao->End();
//						cout << "Done" << endl;
//					}
//				}
//			}

			std::cout << "Done" << std::endl;
			return true;
		}

		void MapSys::update() {

//			std::cout << "Updating map...";

//			generateTerrainChunk(	terrainChunk[0],
//									Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].terrain_size,
//									Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].res+1,
//									TERRAIN_TYPE,
//									Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].tex_scale,
//									Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].terrain_height_offset);

//			generateTerrainChunk(	terrainChunk[0],
//									Core::gameVars->debug.noise.simplex[0].terrain_size,
//									Core::gameVars->debug.noise.simplex[0].res+1,
//									TERRAIN_TYPE,
//									Core::gameVars->debug.noise.simplex[0].tex_scale,
//									Core::gameVars->debug.noise.simplex[0].terrain_height_offset);

			switch(TERRAIN_TYPE) {
				case TERRAIN_PERLIN:
					generateTerrainChunk(terrainChunk[0], 2048, 2048, TERRAIN_PERLIN, 1);
//							generateTerrainChunk(	terrainChunk[0],
//							Core::gameVars->debug.noise.perlin[Core::gameVars->debug.noise.iCurrentSimplex].terrain_size,
//							Core::gameVars->debug.noise.perlin[Core::gameVars->debug.noise.iCurrentSimplex].res+1,
//							TERRAIN_TYPE,
//							Core::gameVars->debug.noise.perlin[Core::gameVars->debug.noise.iCurrentSimplex].tex_scale,
//							Core::gameVars->debug.noise.perlin[Core::gameVars->debug.noise.iCurrentSimplex].terrain_height_offset);
					break;
				case TERRAIN_SIMPLEX:
					generateTerrainChunk(	terrainChunk[0],
											Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].terrain_size,
											Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].res+1,
											TERRAIN_TYPE,
											Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].tex_scale,
											Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].terrain_height_offset);
					break;
				case TERRAIN_FRACTAL:
					generateTerrainChunk(	terrainChunk[0],
											Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].terrain_size,
											Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].res+1,
											TERRAIN_TYPE,
											Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].tex_scale,
											Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].terrain_height_offset);
					break;
			}

//			generateTerrainChunk(terrainChunk[0], 1024, 129);
//			generateTerrainChunk(terrainChunk[1], 1024, 65);
//			generateTerrainChunk(terrainChunk[2], 1024, 33);
//			generateTerrainChunk(terrainChunk[3], 1024, 17);

			mapData[0][0].Begin(GL_TRIANGLES, terrainChunk[0].numVerts, terrainChunk[0].numDrawVerts, 1);
			mapData[0][0].CopyData(GLA_VERTEX, terrainChunk[0].vVerts);
			mapData[0][0].CopyData(GLA_NORMAL, terrainChunk[0].vNorms);
			mapData[0][0].CopyData(GLA_TEXTURE, terrainChunk[0].vCoords, 0);
			mapData[0][0].CopyData(GLA_INDEX, terrainChunk[0].vIndex, terrainChunk[0].numDrawVerts);
			mapData[0][0].End();

//			mapData[0][1].Begin(GL_TRIANGLES, terrainChunk[1].numVerts, terrainChunk[1].numDrawVerts, 1);
//			mapData[0][1].CopyData(GLA_VERTEX, terrainChunk[1].vVerts);
//			mapData[0][1].End();
//
//			mapData[1][0].Begin(GL_TRIANGLES, terrainChunk[2].numVerts, terrainChunk[2].numDrawVerts, 1);
//			mapData[1][0].CopyData(GLA_VERTEX, terrainChunk[2].vVerts);
//			mapData[1][0].End();
//
//			mapData[1][1].Begin(GL_TRIANGLES, terrainChunk[3].numVerts, terrainChunk[3].numDrawVerts, 1);
//			mapData[1][1].CopyData(GLA_VERTEX, terrainChunk[3].vVerts);
//			mapData[1][1].End();

//			std::cout << "Done" << std::endl;
		}

		double MapSys::getPerlinElevation(float x, float z, float w, float h) {
			double nx = x/(w*2) - 0.5, ny = z/(h*2) - 0.5;
			double e1 = (gameVars->debug.noise.perlin.octave1 * noise1( 1 * nx,  1 * ny)
					   + gameVars->debug.noise.perlin.octave2 * noise1( 2 * nx,  2 * ny)
					   + gameVars->debug.noise.perlin.octave3 * noise1( 4 * nx,  4 * ny)
					   + gameVars->debug.noise.perlin.octave4 * noise1( 8 * nx,  8 * ny)
					   + gameVars->debug.noise.perlin.octave5 * noise1(16 * nx, 16 * ny)
					   + gameVars->debug.noise.perlin.octave6 * noise1(32 * nx, 32 * ny));
			e1 /= ( gameVars->debug.noise.perlin.octave1+
					gameVars->debug.noise.perlin.octave2+
					gameVars->debug.noise.perlin.octave3+
					gameVars->debug.noise.perlin.octave4+
					gameVars->debug.noise.perlin.octave5+
					gameVars->debug.noise.perlin.octave6 );
			e1 = std::pow(e1, gameVars->debug.noise.perlin.power)*gameVars->debug.noise.perlin.scale;

			// Lower water regions
			//double e2 = 0.0f;
//			double e2 = (0.50 * noise3( 1 * nx,  1 * ny));	// Lakes attempt
//			e2 /= (0.50);
//			e2 = -std::pow(e2, 4.60)*10000;
//			SimplexNoise simNoise = SimplexNoise(0.1f, 0.5f, 0.25f, 0.75f);
//			double e2 = -simNoise.fractal(5, x, z);
			//return (e1+e2);
			return e1;
		}

		double MapSys::getPerlinMoisture(float x, float z, float w, float h) {
			return 0.0f;
		}

		/*
		 * TODO: Elevation layering...
		 * TODO: Add 1 octave layer for better areas of water, very small frequency
		 */
//		double MapSys::getSimplexElevation(float x, float z, float freq, float amp, float lac, float per, int oct) {
//			SimplexNoise simNoise = SimplexNoise( freq,
//												  amp,
//												  lac, //+((x+Core::gameVars->debug.noise.simplex.offset.x+z+Core::gameVars->debug.noise.simplex.offset.y)/1000.0f),
//												  per );
//			double e = simNoise.fractal(oct, x+Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].offset.x, z+Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].offset.y);
//			e = std::pow(e, gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].power)*gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].scale;
//			return e;
//		}

		double MapSys::getSimplexElevation(float x, float z) {
//			SimplexNoise simNoise = SimplexNoise( gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].frequency,
//												  gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].amplitude,
//												  gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].lacunarity, //+((x+Core::gameVars->debug.noise.simplex.offset.x+z+Core::gameVars->debug.noise.simplex.offset.y)/1000.0f),
//												  gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].persistance );
//			double e1 = simNoise.fractal(gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].octaves, x+Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].offset.x, z+Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].offset.y);
//			e1 = std::pow(e1, gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].power)*gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].scale;

			SimplexNoise simNoise1 = SimplexNoise( gameVars->debug.noise.simplex[0].frequency,
												   gameVars->debug.noise.simplex[0].amplitude,
												   gameVars->debug.noise.simplex[0].lacunarity, //+((x+Core::gameVars->debug.noise.simplex.offset.x+z+Core::gameVars->debug.noise.simplex.offset.y)/1000.0f),
												   gameVars->debug.noise.simplex[0].persistance );
			double e1 = simNoise1.fractal(	gameVars->debug.noise.simplex[0].octaves,
											x+Core::gameVars->debug.noise.simplex[0].offset.x,
											z+Core::gameVars->debug.noise.simplex[0].offset.y);
			e1 = std::pow(e1, gameVars->debug.noise.simplex[0].power)*gameVars->debug.noise.simplex[0].scale;

			SimplexNoise simNoise2 = SimplexNoise( gameVars->debug.noise.simplex[1].frequency,
												   gameVars->debug.noise.simplex[1].amplitude,
												   gameVars->debug.noise.simplex[1].lacunarity, //+((x+Core::gameVars->debug.noise.simplex.offset.x+z+Core::gameVars->debug.noise.simplex.offset.y)/1000.0f),
												   gameVars->debug.noise.simplex[1].persistance );
			double e2 = simNoise2.fractal(	gameVars->debug.noise.simplex[1].octaves,
											x+Core::gameVars->debug.noise.simplex[1].offset.x,
											z+Core::gameVars->debug.noise.simplex[1].offset.y);
			e2 = std::pow(e2, gameVars->debug.noise.simplex[1].power)*gameVars->debug.noise.simplex[1].scale;

			double e3 = e1+e2;

			return e3;
		}

		double MapSys::getFractalElevation(float x, float z) {

			FractalNoise noise1;
			double e1 = noise1.getNoise(x,
										z,
										gameVars->debug.noise.fractal[gameVars->debug.noise.iCurrentFractal].frequency,
										gameVars->debug.noise.fractal[gameVars->debug.noise.iCurrentFractal].lacunarity,
										gameVars->debug.noise.fractal[gameVars->debug.noise.iCurrentFractal].multiplier,
										gameVars->debug.noise.fractal[gameVars->debug.noise.iCurrentFractal].layers);

//			e1 = std::pow(e1, gameVars->debug.noise.fractal[0].power)*gameVars->debug.noise.simplex[0].scale;
			e1 = e1*gameVars->debug.noise.fractal[gameVars->debug.noise.iCurrentFractal].scale;

			return e1;

//			SimplexNoise simNoise1 = SimplexNoise( gameVars->debug.noise.simplex[0].frequency,
//												   gameVars->debug.noise.simplex[0].amplitude,
//												   gameVars->debug.noise.simplex[0].lacunarity, //+((x+Core::gameVars->debug.noise.simplex.offset.x+z+Core::gameVars->debug.noise.simplex.offset.y)/1000.0f),
//												   gameVars->debug.noise.simplex[0].persistance );
//			double e1 = simNoise1.fractal(	gameVars->debug.noise.simplex[0].octaves,
//											x+Core::gameVars->debug.noise.simplex[0].offset.x,
//											z+Core::gameVars->debug.noise.simplex[0].offset.y);
//			e1 = std::pow(e1, gameVars->debug.noise.simplex[0].power)*gameVars->debug.noise.simplex[0].scale;
//
//			SimplexNoise simNoise2 = SimplexNoise( gameVars->debug.noise.simplex[1].frequency,
//												   gameVars->debug.noise.simplex[1].amplitude,
//												   gameVars->debug.noise.simplex[1].lacunarity, //+((x+Core::gameVars->debug.noise.simplex.offset.x+z+Core::gameVars->debug.noise.simplex.offset.y)/1000.0f),
//												   gameVars->debug.noise.simplex[1].persistance );
//			double e2 = simNoise2.fractal(	gameVars->debug.noise.simplex[1].octaves,
//											x+Core::gameVars->debug.noise.simplex[1].offset.x,
//											z+Core::gameVars->debug.noise.simplex[1].offset.y);
//			e2 = std::pow(e2, gameVars->debug.noise.simplex[1].power)*gameVars->debug.noise.simplex[1].scale;
//
//			double e3 = e1+e2;
//
//			return e3;
		}



		/*
		 * TODO: draw(); Draw all maps
		 */
		void MapSys::draw(Core::SHADER_PROGRAMS iShader, Core::_Lights &lights) {
			glActiveTexture(GL_TEXTURE0);
//			Core::sysTex->set(Core::sysTex->TEX_TESTPATTERN);
			Core::sysTex->set(Core::sysTex->TEX_DIRT);
//			Core::sysTex->set(Core::sysTex->TEX_GRASS);
//			gameVars->texture.terrain.Set("dirt1.png");
//
//			glActiveTexture(GL_TEXTURE1);
//			gameVars->texture.terrain.Set("grass1.png");
//
//			glActiveTexture(GL_TEXTURE2);
//			gameVars->texture.terrain.Set("rocky1.png");
//
//			glActiveTexture(GL_TEXTURE3);
//			gameVars->texture.terrain.Set("cliff1.png");
//
//			glActiveTexture(GL_TEXTURE4);
//			gameVars->texture.terrain.Set("dirt2.png");
//
//			glActiveTexture(GL_TEXTURE5);
//			gameVars->texture.terrain.Set("grass2.png");
//
//			glActiveTexture(GL_TEXTURE6);
//			gameVars->texture.terrain.Set("rocky2.png");
//
//			glActiveTexture(GL_TEXTURE7);
//			gameVars->texture.terrain.Set("cliff2.png");
//
//			glActiveTexture(GL_TEXTURE8);
//			atmosphere->water.tex.Set(atmosphere->water.sWorld);
//
//			glActiveTexture(GL_TEXTURE0);
//
//			Core.shader.use(iShader);
//			std::cout << "Drawing Map...";
//			for (int x=0; x<data.iSize; x++) {
//				for (int z=0; z<data.iSize; z++) {

			/*
			 * Temporary drawing routine
			 */
			int x=0, z=0;
//			for (int x=0; x<data.iSize; x++) {
//				for (int z=0; z<data.iSize; z++) {
//					std::cout << "[" << x << "," << z << "]";
//					glDisable(GL_CULL_FACE);
					glEnable(GL_CULL_FACE);
					Core::matrix->Push();
						// Center World

						// Move chunk according to player
						matrix->Rotate(Core::gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
						matrix->Rotate(Core::gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
						matrix->Translate(Core::gameVars->player.active->transform.pos[0], Core::gameVars->player.active->transform.pos[1], Core::gameVars->player.active->transform.pos[2]);

						// Move chunk into place (Do in loader so lighting works easily)
//						matrix->Translate(x*1024*Core::gameVars->screen.fScale, 0.0f, z*1024*Core::gameVars->screen.fScale);
						//Core::matrix->Scale(10*Core::gameVars->screen.fScale, 10*Core::gameVars->screen.fScale, 10*Core::gameVars->screen.fScale);
						//Core::matrix->Scale(10*Core::gameVars->screen.fScale, 1*Core::gameVars->screen.fScale, 10*Core::gameVars->screen.fScale);
						Core::matrix->Scale(1*Core::gameVars->screen.fScale, 1*Core::gameVars->screen.fScale, 1*Core::gameVars->screen.fScale);
						matrix->Translate(x*1024*Core::gameVars->screen.fScale, 0.0f, z*1024*Core::gameVars->screen.fScale);
						matrix->SetTransform();

//						glPolygonMode(GL_BACK, GL_LINE);
//						glPolygonMode(GL_FRONT, GL_FILL);

						shader->use(iShader);
						shader->getUniform(iShader, &lights);

//						shader->use(GLS_FONT);
//						shader->getUniform(GLS_FONT);
						mapData[0][0].Draw(GLM_DRAW_ELEMENTS);

						// Draw vertex normals (~6fps drop)
						if(Core::gameVars->debug.gui.b5) {
							glLineWidth(1.0f);
							shader->use(GLS_NORMAL_LINE2);
							shader->getUniform(GLS_NORMAL_LINE2);
							mapData[0][0].Draw(GLM_DRAW_ELEMENTS);
						}

						//glActiveTexture(GL_TEXTURE0);	Core::sysTex->set(Core::sysTex->TEX_WATER);
						//mapData[0][1].Draw(GLM_DRAW_ELEMENTS);

						//glActiveTexture(GL_TEXTURE0);	Core::sysTex->set(Core::sysTex->TEX_ROCK);
						//mapData[1][0].Draw(GLM_DRAW_ELEMENTS);

						//glActiveTexture(GL_TEXTURE0);	Core::sysTex->set(Core::sysTex->TEX_DIRT);
						//mapData[1][1].Draw(GLM_DRAW_ELEMENTS);

						glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					Core::matrix->Pop();
//					glEnable(GL_CULL_FACE);
//					glDisable(GL_CULL_FACE);
//				}
//			}



//					Core.matrix.Push();
//						Core.matrix.Translate(x*1024*gameVars->screen.iScale, 0, z*1024*gameVars->screen.iScale);
//						Core.matrix.Scale(16*gameVars->screen.iScale, 16*gameVars->screen.iScale, 16*gameVars->screen.iScale);
//						Core.matrix.SetTransform();
//						Core.shader.getUniform(*atmosphere, iShader);
//						//	if(bOcclude) occlusion.StartQuery("World Map", iNum);
//								mapData[x][z].vao->Draw(GLM_DRAW_ELEMENTS);
//						//	if(bOcclude) occlusion.EndQuery("World Map", iNum);
//					Core.matrix.Pop();
//				}
//				std::cout << std::endl;
//			}
//			std::cout << "Done" << std::endl;
		}
	}
}

#endif /* WORLDMAP_H_ */
