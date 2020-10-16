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
//#include "../core/types.h"
#include "../core/Noise.h"
#include "../core/core_functions.h"
#include "../core/vao.h"
#include "../core/texture.h"
#include "./MapData.h"
#include <libnoise/noise.h>
#include "../core/SimplexNoise.h"
//#include "../core/FractalNoise.h"

namespace Core {
	namespace Sys {
		class MapSys {
			private:

//				typedef std::variant<Map::t_Simplex*, Map::t_Perlin*, Map::t_Fractal*, Map::t_Ridged*> t_VariantNoise;
//				void generateTerrainChunk(Map::Data &map, float SIZE, int VERTEX_COUNT, eTerrainType eType=TERRAIN_PERLIN, int iTexScale=1, float fHeightOffset=0.0f);
				//void generateTerrainChunk(int x, int z, Map::Data &map, Map::Simplex *simplex);

				// TODO: Noise handler should be its own global class
				// Setup Perlin Noise
//				unsigned seed1 = 42;
//				unsigned seed2 = 1024;
//				unsigned seed3 = 420;
//				unsigned seed4 = 4096;
//				std::minstd_rand0 rng1;
//				std::minstd_rand0 rng2;
//				std::minstd_rand0 rng3;
//				std::minstd_rand0 rng4;
//				noise::module::Perlin genPerlin;
//				noise::module::RidgedMulti genRidged;
//				noise::module::Voronoi genVoronoi;
//				noise::module::Billow genBillow;
//				SimplexNoise genSimplex;
//				noise::module::Perlin gen2;
//				noise::module::Perlin gen3;
//				double RidgedNoise(double nx, double ny) {
//					//return 2 * (0.5f - abs(0.5f - PerlinNoise(nx, ny)));
//					return genRidged.GetValue(nx, ny, 0) / 2.0 + 0.5;
//				}

//				double applyHeightFunction(double height, double e2, Map::t_SimplexFunctions *functions);
//				double applyFunction(double height, double e2, Map::t_PerlinFunctions *functions);
//				double applyFunction(double height, double e2, Map::t_FractalFunctions *functions);

//				double noise1(double nx, double ny) { return gen1.GetValue(nx, ny, 0) / 2.0 + 0.5; }
//				double noise2(double nx, double ny) { return gen2.GetValue(nx, ny, 0) / 2.0 + 0.5; }
//				double noise3(double nx, double ny) { return gen3.GetValue(nx, ny, 0) / 2.0 + 0.5; }
				bool bInit;


			protected:


			public:
				struct _Simplex {
					int res;
					float tex_scale;
					int terrain_size;
					float terrain_height_offset;

					Vector2f offset;
					float frequency, amplitude, lacunarity, persistance;
					int octaves;
					float power;
					float scale;
					float delta;
					_Simplex() {
						res = 256;
						tex_scale = 128.0f;
						terrain_size = 16384;
						terrain_height_offset = 0.0f;

						delta		= 32.0f;
						frequency	= 0.00025f; //0.0006; //0.000076; //0.00025f;
						amplitude	= 1.0f;
						lacunarity	= 2.9f; //6.553f; //6.004; //6.75325; //8.0f;
						persistance	= 0.33f; //0.139f; //0.150; //0.175; //0.175f;
						power		= 1.0f;
						scale		= 875.0f; //500.0f; //275.0f; //1750; //2500;
						octaves		= 3;
					}
				} simplex;

				MapSys() {
					Core::debug.log("Construct MapSys {");
//					mapData = nullptr;
					//gen1 = PerlinNoise(rng1());
					//gen2 = PerlinNoise(rng2());
					bInit = false;
					Core::debug.print(" Done ", Core::debug().GREEN);
					Core::debug.print("}\n");
				}
				~MapSys() {
					Core::debug.log("Destroy MapSys {");
//					for (int n=0; n<data.iSize; n++) {
////						mapData[n] = new VAO[data.iSize];
//						delete[] mapData[n];
//					}
//					delete[] mapData;
					Core::debug.print(" Done ", Core::debug().GREEN);
					Core::debug.print("}\n");
				}

//				struct _MapSysData {
//					int			iSize;			// (1=1x1 DO NOT USE), 2=3x3, 3=5x5...n=(n*2-1)x(n*2-1)
//
//					_MapSysData() {
//						iSize = 3;
//					}
//				} data;

				std::string dir;				// Directory location for map
//				VAO ** mapData;
//				Map::Data terrainChunk[4];		// Generic terrain chunk (TODO: LOD array)
				Texture tex;					// TODO: Map specific textures
				bool init();
//				void load(int x, int z, Map::Data &chunk, Map::t_VariantNoise noise);
				void load(int x, int z, Map::Data &chunk, Core::Noise::t_Noise *noise);
//				void loadData(int x, int z, Data3f &chunkData, int index, Core::Noise::t_Noise *noise);
				void load(int x, int z, Map::Data &chunk, int index, Core::Noise::t_Noise *noise);
				void calc(Map::Data &ref);
//				void update(int x, int z, Map::Data &chunk, Map::t_VariantNoise noise);
				void update(int x, int z, Map::Data &chunk, Core::Noise::t_Noise *noise);
//				double getElevation(float x, float z, Map::t_VariantNoise noise);
//				double getElevation(float x, float z, Core::Noise::t_Noise *noise);
		};

		bool MapSys::init() {
			Core::debug.log("Init MapSys {");

			if(!bInit) {
//				rng1 = std::minstd_rand0(seed1);
//				rng2 = std::minstd_rand0(seed2);
//				rng3 = std::minstd_rand0(seed3);
//				rng4 = std::minstd_rand0(seed4);
//
//				genPerlin.SetSeed(rng1());
//				genRidged.SetSeed(rng2());
//				genVoronoi.SetSeed(rng3());
//				genBillow.SetSeed(rng4());
//				gen2.SetSeed(rng2());
//				gen3.SetSeed(rng3());
				bInit = true;
			}

			// TODO: Pointer cleanup
//			mapData = new VAO*[data.iSize];
//			for (int n=0; n<data.iSize; n++) {
//				mapData[n] = new VAO[data.iSize];
//			}
//			else {
//				mapData = new VAO;
//			}

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
			Core::debug.print(" Done ", Core::debug().GREEN);
			Core::debug.print("}\n");
			return true;
		}


		/*
		 * Original
		 * 		Author: ThinMatrix
		 * 		Title: OpenGL Game Tutorial 14: Simple Terrain
		 * 		Address: https://www.dropbox.com/s/47qk4yrz5v9lb61/Terrain%20Generation%20Code.txt?dl=0
		 * 		Modified: 2020-03-04
		 * 		Description: Generate terrain grid of size, resolution, and texture scale.
		 * 		Modified: Uses noise generators to change height values
		 *
		 * Size = physical size of chunk (1024 typical)
		 * Vertex_Count = Number of vertices per side (can be used for LOD?)
		 */
//		void MapSys::load(int x, int z, Map::Data &chunk, Map::t_VariantNoise noise) {
////		std::variant<Map::t_Simplex, Map::t_Perlin, Map::t_Fractal, Map::t_Ridged>
//
//			// Pointer to correct parent
//			// Pointer to correct elevation function
//
////			double (*getNoiseElevation)(float, float, void *);
////			getNoiseElevation = &getElevation;
//
////			double (*getNoiseElevation)(float x, float z, Map::t_Simplex *noise);
////			getNoiseElevation = &getElevation;
////			double (*getNoiseElevation)(float x, float z, Map::t_Perlin *noise);
////			double (*getNoiseElevation)(float x, float z, Map::t_Fractal *noise);
////			double (*getNoiseElevation)(float x, float z, Map::t_Ridged *noise);
//
//			Map::t_ChunkData *chunkData;
//
//			switch(noise.index()) {
//				case Map::NOISE_SIMPLEX:
//					chunkData = std::get<Map::t_Simplex*>(noise)->parent;
//					break;
//				case Map::NOISE_PERLIN:
//					chunkData = std::get<Map::t_Perlin*>(noise)->parent;
//					break;
//				case Map::NOISE_FRACTAL:
//					chunkData = std::get<Map::t_Fractal*>(noise)->parent;
//					break;
//				case Map::NOISE_RIDGED:
//					chunkData = std::get<Map::t_Ridged*>(noise)->parent;
//					break;
//			}
//
//			float SIZE			= chunkData->chunk_size;
//			int VERTEX_COUNT	= chunkData->chunk_resolution+1;
//			int iTexScale		= chunkData->tex_scale;
//			float fHeightOffset	= chunkData->chunk_height_offset;
//			float DELTA			= chunkData->delta;
//
//			chunk.numVerts = VERTEX_COUNT * VERTEX_COUNT;
//			chunk.numDrawVerts = 6*(VERTEX_COUNT-1)*(VERTEX_COUNT-1);
//			chunk.vVerts = new Data3f[chunk.numVerts];
//			chunk.vNorms = new Data3f[chunk.numVerts];
//			chunk.vCoords = new Data2f[chunk.numVerts];
//			chunk.vIndex = new GLuint[chunk.numDrawVerts];
//
//			long vertexPointer = 0;
//			for(int i=0;i<VERTEX_COUNT;i++){
//				for(int j=0;j<VERTEX_COUNT;j++){
//
//					// Vertex
//					chunk.vVerts[vertexPointer][0] = ((float)j/((float)VERTEX_COUNT - 1) * SIZE);
//					chunk.vVerts[vertexPointer][2] = ((float)i/((float)VERTEX_COUNT - 1) * SIZE);
//					chunk.vVerts[vertexPointer][1] = getElevation(chunk.vVerts[vertexPointer][0]+x, chunk.vVerts[vertexPointer][2]+z, noise) + fHeightOffset;
//
//					Vector3f modelXOffset,
//							 modelYOffset,
//							 modelXGrad,
//							 modelYGrad,
//							 A, B, C, BA, CA, Dir, Norm;
//
//							A = chunk.vVerts[vertexPointer];
//
//							B.x = A.x+DELTA;
//							B.z = A.z+DELTA;
//							B.y = getElevation(B.x+x, B.z+z, noise) + fHeightOffset;
//
//							C.x = A.x+DELTA;
//							C.z = A.z-DELTA;
//							C.y = getElevation(C.x+x, C.z+z, noise) + fHeightOffset;
//
//							BA = B - A;
//							CA = C - A;
//							Dir = Core::gmath.Cross(BA, CA);
//							Norm = Dir/Dir.length();
//
////						default:
////							chunk.vNorms[vertexPointer][0] = 0;
////							chunk.vNorms[vertexPointer][1] = 1;
////							chunk.vNorms[vertexPointer][2] = 0;
//
//					// Normals - What is expected to work but DOES NOT
//					chunk.vNorms[vertexPointer][0] = Norm.x;
//					chunk.vNorms[vertexPointer][1] = Norm.y;
//					chunk.vNorms[vertexPointer][2] = Norm.z;
//
//					// Texture
//					chunk.vCoords[vertexPointer][0] = (float)j/((float)VERTEX_COUNT - 1) * (float)iTexScale;
//					chunk.vCoords[vertexPointer][1] = (float)i/((float)VERTEX_COUNT - 1) * (float)iTexScale;
//					vertexPointer++;
//				}
//			}
//			long pointer = 0;
//			for(uint gz=0;gz<VERTEX_COUNT-1;gz++){
//				for(uint gx=0;gx<VERTEX_COUNT-1;gx++){
//					uint topLeft = (gz*VERTEX_COUNT)+gx;
//					uint topRight = topLeft + 1;
//					uint bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
//					uint bottomRight = bottomLeft + 1;
//					chunk.vIndex[pointer++] = topLeft;			//std::cout << "[(" << chunk.vIndex[pointer-1];
//					chunk.vIndex[pointer++] = bottomLeft;		//std::cout << ", " << chunk.vIndex[pointer-1];
//					chunk.vIndex[pointer++] = topRight;			//std::cout << ", " << chunk.vIndex[pointer-1];
//					chunk.vIndex[pointer++] = topRight;			//std::cout << ")(" << chunk.vIndex[pointer-1];
//					chunk.vIndex[pointer++] = bottomLeft;		//std::cout << ", " << chunk.vIndex[pointer-1];
//					chunk.vIndex[pointer++] = bottomRight;		//std::cout << ", " << chunk.vIndex[pointer-1] << ")]" << std::endl;
//				}
//			}
//		}

		// TODO: Load additional data (i.e. moisture)
		// Data3f provides 3 floats per vertex
		//void MapSys::loadData(int x, int z, Data3f *chunkData, int index, Core::Noise::t_Noise *noise) {
		void MapSys::load(int x, int z, Map::Data &chunk, int index, Core::Noise::t_Noise *noise) {
			x = (x-32768) * noise->parent->chunk_size;
			z = (z-32768) * noise->parent->chunk_size;

			float SIZE			= noise->parent->chunk_size;
			int VERTEX_COUNT	= noise->parent->chunk_resolution+1;
//			int iTexScale		= noise->parent->tex_scale;
//			float fHeightOffset	= noise->parent->chunk_height_offset;
//			float DELTA			= noise->parent->delta;
//			chunk.vData = new Data3f[VERTEX_COUNT * VERTEX_COUNT];

//			debug.log("Loading Moisture...\n");

			long vertexPointer = 0;
			for(int i=0;i<VERTEX_COUNT;i++){
				for(int j=0;j<VERTEX_COUNT;j++){

//					if(i==0 && j==0) {

					// Vertex
//					chunkData[vertexPointer][0] = ((float)j/((float)VERTEX_COUNT - 1) * SIZE);
//					chunkData[vertexPointer][2] = ((float)i/((float)VERTEX_COUNT - 1) * SIZE);

//					chunk.vVerts[vertexPointer][0] = ((float)j/((float)VERTEX_COUNT - 1) * SIZE);
//					chunk.vVerts[vertexPointer][2] = ((float)i/((float)VERTEX_COUNT - 1) * SIZE);
//					chunk.vVerts[vertexPointer][1] = getElevation(chunk.vVerts[vertexPointer][0]+x, chunk.vVerts[vertexPointer][2]+z, noise) + fHeightOffset;

//					float fX = ((float)j/((float)VERTEX_COUNT - 1) * SIZE);
//					float fZ = ((float)i/((float)VERTEX_COUNT - 1) * SIZE);
//					chunk.vData[vertexPointer][index] = getElevation(fX+x, fZ+z, noise) + fHeightOffset;

					// vVerts should already have been defined by this point
					//chunk.vData[vertexPointer][index] = getElevation(chunk.vVerts[vertexPointer][0]+x, chunk.vVerts[vertexPointer][2]+z, noise) + fHeightOffset;

//					chunk.vData[vertexPointer][0]

					chunk.vData[vertexPointer][index] = Core::Noise::getNoise(chunk.vVerts[vertexPointer][0]+x, chunk.vVerts[vertexPointer][2]+z, noise);

//					chunk.vData[vertexPointer][index] /= 150000;
//					chunk.vData[vertexPointer][index] = (chunk.vData[vertexPointer][index] / 2.0f) + 0.5f;
//					debug.log("("+std::to_string(i)+", "+std::to_string(j)+") = "+std::to_string(chunk.vData[vertexPointer][index])+"\n");
//					}
					vertexPointer++;
				}
			}

//			long vertexPointer = 0;
//			for(int i=0;i<VERTEX_COUNT;i++){
//				for(int j=0;j<VERTEX_COUNT;j++){
//
//					// Vertex
//					chunkData[vertexPointer][0] = ((float)j/((float)VERTEX_COUNT - 1) * SIZE);
//					chunkData[vertexPointer][2] = ((float)i/((float)VERTEX_COUNT - 1) * SIZE);
//					chunkData[vertexPointer][1] = getElevation(chunkData[vertexPointer][0]+x, chunkData[vertexPointer][2]+z, noise) + fHeightOffset;
//
//					vertexPointer++;
//				}
//			}
//			long pointer = 0;
//			for(uint gz=0;gz<VERTEX_COUNT-1;gz++){
//				for(uint gx=0;gx<VERTEX_COUNT-1;gx++){
//					uint topLeft = (gz*VERTEX_COUNT)+gx;
//					uint topRight = topLeft + 1;
//					uint bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
//					uint bottomRight = bottomLeft + 1;
//					chunkData[pointer++] = topLeft;
//					chunkData[pointer++] = bottomLeft;
//					chunkData[pointer++] = topRight;
//					chunkData[pointer++] = topRight;
//					chunkData[pointer++] = bottomLeft;
//					chunkData[pointer++] = bottomRight;
//				}
//			}

		}

		void MapSys::load(int x, int z, Map::Data &chunk, Core::Noise::t_Noise *noise) {

			x = (x-32768) * noise->parent->chunk_size;
			z = (z-32768) * noise->parent->chunk_size;

			float SIZE			= noise->parent->chunk_size;
			int VERTEX_COUNT	= noise->parent->chunk_resolution+1;
			int iTexScale		= noise->parent->tex_scale;
			float fHeightOffset	= noise->parent->chunk_height_offset;
			float DELTA			= noise->parent->delta;

			chunk.numVerts = VERTEX_COUNT * VERTEX_COUNT;
			chunk.numDrawVerts = 6*(VERTEX_COUNT-1)*(VERTEX_COUNT-1);
			chunk.vVerts = new Data3f[chunk.numVerts];
			chunk.vNorms = new Data3f[chunk.numVerts];
			chunk.vCoords = new Data2f[chunk.numVerts];
			chunk.vIndex = new GLuint[chunk.numDrawVerts];
			chunk.vData = new Data3f[chunk.numVerts];

			long vertexPointer = 0;
			for(int i=0;i<VERTEX_COUNT;i++){
				for(int j=0;j<VERTEX_COUNT;j++){

					// Vertex
					chunk.vVerts[vertexPointer][0] = ((float)j/((float)VERTEX_COUNT - 1) * SIZE);
					chunk.vVerts[vertexPointer][2] = ((float)i/((float)VERTEX_COUNT - 1) * SIZE);
					chunk.vVerts[vertexPointer][1] = Core::Noise::getNoise(chunk.vVerts[vertexPointer][0]+x, chunk.vVerts[vertexPointer][2]+z, noise) + fHeightOffset;

					// Clear extra data
					chunk.vData[vertexPointer][0] = 0.0f;
					chunk.vData[vertexPointer][1] = 0.0f;
					chunk.vData[vertexPointer][2] = 0.0f;
					chunk.vData[vertexPointer][2] = chunk.vVerts[vertexPointer][1] - fHeightOffset;

					// Determine normal using Delta points
					// TODO: Update this to use less lookups
					//			- In the building loop, use the already calculated points to determine normal from geometry instead of noise
					Vector3f modelXOffset,
							 modelYOffset,
							 modelXGrad,
							 modelYGrad,
							 A, B, C, BA, CA, Dir, Norm;

							A = chunk.vVerts[vertexPointer];

							B.x = A.x+DELTA;
							B.z = A.z+DELTA;
							B.y = Core::Noise::getNoise(B.x+x, B.z+z, noise) + fHeightOffset;

							C.x = A.x+DELTA;
							C.z = A.z-DELTA;
							C.y = Core::Noise::getNoise(C.x+x, C.z+z, noise) + fHeightOffset;

							BA = B - A;
							CA = C - A;
							Dir = Core::gmath.Cross(BA, CA);
							Norm = Dir/Dir.length();

					// Normals - What is expected to work but DOES NOT
					chunk.vNorms[vertexPointer][0] = Norm.x;
					chunk.vNorms[vertexPointer][1] = Norm.y;
					chunk.vNorms[vertexPointer][2] = Norm.z;

					// Texture
					chunk.vCoords[vertexPointer][0] = (float)j/((float)VERTEX_COUNT - 1) * (float)iTexScale;
					chunk.vCoords[vertexPointer][1] = (float)i/((float)VERTEX_COUNT - 1) * (float)iTexScale;

//					float s,
//						  t;
//					if(j%2==0) s = 0.0f;
//					else s = 1.0f;
//
//					if(i%2==0) t = 0.0f;
//					else t = 1.0f;
//					chunk.vCoords[vertexPointer][0] = s;
//					chunk.vCoords[vertexPointer][1] = t;

					// Update the lowest point on the chunk
					chunk.lowestHeight = fmin(chunk.lowestHeight, fmin(chunk.vVerts[vertexPointer][1], fmin(B.y, C.y)));

					vertexPointer++;
				}
			}

			long pointer = 0;
			for(uint gz=0;gz<VERTEX_COUNT-1;gz++){
				for(uint gx=0;gx<VERTEX_COUNT-1;gx++){

					// TODO: Calculate Normals Here, per triangle (2-triangles here per quad)
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
				}
			}
		}

//		void MapSys::load(int x, int z, Map::Data &chunk, Map::t_Perlin *noise) {
//		}
//
//		void MapSys::load(int x, int z, Map::Data &chunk, Map::t_Fractal *noise) {
//		}
//
//		void MapSys::load(int x, int z, Map::Data &chunk, Map::t_Ridged *noise) {
//		}


		/*
		 * TODO: Calc(); Do general map calculations. (including LOD management?)
		 */
		void MapSys::calc(Map::Data &ref) {
//			Core::debug.log("Calc Map {");

			ref.vao.Begin(GL_TRIANGLES, ref.numVerts, ref.numDrawVerts, 1);
			ref.vao.CopyData(GLA_VERTEX, ref.vVerts);
			ref.vao.CopyData(GLA_NORMAL, ref.vNorms);
			ref.vao.CopyData(GLA_TEXTURE, ref.vCoords, 0);
			ref.vao.CopyData(GLA_INDEX, ref.vIndex, ref.numDrawVerts);
			ref.vao.CopyData(GLA_DATA1, ref.vData);
			ref.vao.End();

//			Core::debug.print(" Done ", Core::debug().GREEN);
//			Core::debug.print("}\n");
		}

//		void MapSys::update(int x, int z, Map::Data &ref, Map::t_VariantNoise noise) {
//			load( x, z, ref, noise);
//
//			ref.vao.Begin(GL_TRIANGLES, ref.numVerts, ref.numDrawVerts, 1);
//			ref.vao.CopyData(GLA_VERTEX, ref.vVerts);
//			ref.vao.CopyData(GLA_NORMAL, ref.vNorms);
//			ref.vao.CopyData(GLA_TEXTURE, ref.vCoords, 0);
//			ref.vao.CopyData(GLA_INDEX, ref.vIndex, ref.numDrawVerts);
//			ref.vao.End();
//		}

		void MapSys::update(int x, int z, Map::Data &ref, Core::Noise::t_Noise *noise) {
			load( x, z, ref, noise);

			ref.vao.Begin(GL_TRIANGLES, ref.numVerts, ref.numDrawVerts, 1);
			ref.vao.CopyData(GLA_VERTEX, ref.vVerts);
			ref.vao.CopyData(GLA_NORMAL, ref.vNorms);
			ref.vao.CopyData(GLA_TEXTURE, ref.vCoords, 0);
			ref.vao.CopyData(GLA_INDEX, ref.vIndex, ref.numDrawVerts);
			ref.vao.CopyData(GLA_DATA1, ref.vData);
			ref.vao.End();
		}

//		double MapSys::getElevation(float x, float z, Map::t_VariantNoise noise) {
//			double e1 = 0.0f;
//			switch(noise.index()) {
//				case Map::NOISE_SIMPLEX:
//				{
//					// TODO: Implement simplex modification functions
//					for( auto const &layer : std::get<Map::t_Simplex*>(noise)->params ) {
//						double e1a = 0.0f;
//						double e1b = 0.0f;
//						SimplexNoise simNoise1 = SimplexNoise( layer.frequency, layer.amplitude, layer.lacunarity, layer.persistance );
//						e1a = simNoise1.fractal( layer.octaves, x, z);
//						e1b += (std::pow(e1a, layer.power)*layer.scale);
//						e1 += e1b;
//					}
//					break;
//				}
//				case Map::NOISE_PERLIN:
//				{
////					double nx = x/(w*2) - 0.5, ny = z/(h*2) - 0.5;
////					double e1 = (gameVars->debug.noise.perlin.octave1 * noise1( 1 * nx,  1 * ny)
////							   + gameVars->debug.noise.perlin.octave2 * noise1( 2 * nx,  2 * ny)
////							   + gameVars->debug.noise.perlin.octave3 * noise1( 4 * nx,  4 * ny)
////							   + gameVars->debug.noise.perlin.octave4 * noise1( 8 * nx,  8 * ny)
////							   + gameVars->debug.noise.perlin.octave5 * noise1(16 * nx, 16 * ny)
////							   + gameVars->debug.noise.perlin.octave6 * noise1(32 * nx, 32 * ny));
////					e1 /= ( gameVars->debug.noise.perlin.octave1+
////							gameVars->debug.noise.perlin.octave2+
////							gameVars->debug.noise.perlin.octave3+
////							gameVars->debug.noise.perlin.octave4+
////							gameVars->debug.noise.perlin.octave5+
////							gameVars->debug.noise.perlin.octave6 );
////					e1 = std::pow(e1, gameVars->debug.noise.perlin.power)*gameVars->debug.noise.perlin.scale;
//					break;
//				}
//				case Map::NOISE_FRACTAL:
//				{
//					FractalNoise noise1;
//					e1 = noise1.getNoise(	x,
//											z,
//											gameVars->debug.noise.fractal[gameVars->debug.noise.iCurrentFractal].frequency,
//											gameVars->debug.noise.fractal[gameVars->debug.noise.iCurrentFractal].lacunarity,
//											gameVars->debug.noise.fractal[gameVars->debug.noise.iCurrentFractal].multiplier,
//											gameVars->debug.noise.fractal[gameVars->debug.noise.iCurrentFractal].layers);
//
//					e1 = e1*gameVars->debug.noise.fractal[gameVars->debug.noise.iCurrentFractal].scale;
//					break;
//				}
//				case Map::NOISE_RIDGED:
//					break;
//			}
//
//			return e1;
//		}

		// TODO: This should be in the noise class as a getNoise() method. We will need this for O2D and Flora eventually
//		double MapSys::getElevation(float x, float z, Core::Noise::t_Noise *noise) {
//			double dHeight = 0.0f;
//
//
//			for ( auto layer : noise->layers ) {
//				Core::Noise::eNoiseType type	= layer.first;
//				int index				= layer.second;
//
//				switch(type) {
////					case Core::Noise::NOISE_SIMPLEX:
////					{
////						for( auto const &param : *noise->simplex[index] ) {
////							double  e1 = 0.0f,
////									e2 = 0.0f;
////
//////							SimplexNoise simNoise1 = SimplexNoise( param->frequency, param->amplitude, param->lacunarity, param->persistance );
////							SimplevTexCoordsxNoise simNoise1 = SimplexNoise( 0.0001f, 1.0f, 1.0f, 1.0f );
//////							SimplexNoise simNoise1;
////							e1 = simNoise1.noise(x, z);
////							e2 = Core::Noise::applyFunctions(e1, dHeight, *param);
////							dHeight = Core::Noise::applyMode(e2, dHeight, param->mode);
////
//////							// Octaves
//////							// TODO: Fix octave implementation (octaves and frequency built in to getPerlin())
//////							float amplitudeTotal = 0.0f;
//////							for(int n=0; n<param->octaves(); n++) {
//////								e1 = param->octaveData[n].amplitude * genPerlin.GetValue(x, z, 0) / 2.0 + 0.5;
//////								amplitudeTotal += param->octaveData[n].amplitude;
//////							}
//////							e2 /= amplitudeTotal;
//////
//////							e2 = Core::Noise::applyFunctions(e1, dHeight, *param);
//////							dHeight = Core::Noise::applyMode(e2, dHeight, param->mode);
////						}
////						break;
////					}
//					case Core::Noise::NOISE_PERLIN:
//					{
//						// Layers
//						for( auto const &param : *noise->perlin[index] ) {
//
//							double  e1 = 0.0f,
//									e2 = 0.0f;
//
//							rng1 = std::minstd_rand0(param->seed);
//							genPerlin.SetSeed(rng1());
//							genPerlin.SetFrequency(param->frequency);
//							genPerlin.SetLacunarity(param->lacunarity);
//							genPerlin.SetNoiseQuality(param->quality);
//							genPerlin.SetOctaveCount(param->octaves);
//							genPerlin.SetPersistence(param->persistence);
//
//							e1 = genPerlin.GetValue(x, z, 0);
//							e2 = Core::Noise::applyFunctions(e1, dHeight, *param);
//							dHeight = Core::Noise::applyMode(e2, dHeight, param->mode);
//						}
//						break;
//					}
//					case Core::Noise::NOISE_FRACTAL:
//					{
//						for( auto const &param : *noise->fractal[index] ) {
//							double e1 = 0.0f;
//							double e2 = 0.0f;
////							SimplexNoise simNoise1 = SimplexNoise( param->frequency, param->amplitude, param->lacunarity, param->persistance );
//
//							genSimplex.setAmplitude(param->amplitude);
//							genSimplex.setFrequency(param->frequency);
//							genSimplex.setLacunarity(param->lacunarity);
//							genSimplex.setPersiistence(param->persistence);
//							genSimplex.setSeed(param->seed);
////							e1 = genSimplex.fractal( param->octaves, x, z, dHeight);
//							e1 = genSimplex.fractal( param->octaves, x, z, 0);
//							//e1 = simNoise1.fractal( param->octaves, x, z, 0);
//							e2 = Core::Noise::applyFunctions(e1, dHeight, *param);
//							dHeight = Core::Noise::applyMode(e2, dHeight, param->mode);
//						}
//						break;
//					}
//
////					case Core::Noise::NOISE_RIDGED_SIMPLEX:
////					{
////						double nx = x/(noise->parent->chunk_size*2) - 0.5, ny = z/(noise->parent->chunk_size*2) - 0.5;
////						for( auto const &param : *noise->ridgedSimplex[index] ) {
////							double e1 = 0.0f;
////							double e2 = 0.0f;
////							double e3 = 0.0f;
////							SimplexNoise simNoise1 = SimplexNoise( param->frequency, param->amplitude, param->lacunarity, param->persistance );
//////							e1 = (param->threshold - abs(simNoise1.fractal( x, z, dHeight)));
//////							e1 = (param->threshold - abs(simNoise1.fractal( param->octaves, x, z, dHeight/20000.0f)));
//////							e1 = (param->threshold - abs(simNoise1.fractal( param->octaves, x, z)));
////							e1 = (param->threshold - abs(simNoise1.fractal( param->octaves, nx, ny)));
////
////							int sign = 1;
////							if(e1<0) sign = -1;
////							e2 = e1;
////							e3 += sign * ((std::pow(abs(e2), param->power)*param->scale));
////
////							if(param->funcHeightEnable) {
////								if(dHeight<(param->funcHeightLowerValue)) {
////									dHeight += e3 * fmax(fmin((dHeight/param->funcHeightLowerValue), 1.0f), 0.0f);
////								}
////								else if(dHeight>(param->funcHeightUpperValue)) {
////									dHeight += e3 * fmax(fmin((1.0f-(dHeight/(param->funcHeightUpperValue*2.0f))), 1.0f), 0.0f);
////								}
////								else dHeight += e3;
////							}
////							else dHeight += e3;
////
////						}
////						break;
////					}
//
//					case Core::Noise::NOISE_RIDGED_PERLIN:
//					{
//						// Layers
//						for( auto const &param : *noise->ridgedPerlin[index] ) {
//
//							double  e1 = 0.0f,
//									e2 = 0.0f,
//									e3 = 0.0f;
//
//							rng2 = std::minstd_rand0(param->seed);
//							genRidged.SetSeed(rng2());
//							genRidged.SetFrequency(param->frequency);
//							genRidged.SetLacunarity(param->lacunarity);
//							genRidged.SetNoiseQuality(param->quality);
//							genRidged.SetOctaveCount(param->octaves);
//
//							e1 = genRidged.GetValue(x, z, 0);
//							e2 = Core::Noise::applyFunctions(e1, dHeight, *param);
//							dHeight = Core::Noise::applyMode(e2, dHeight, param->mode);
//						}
//						break;
//					}
//
//					case Core::Noise::NOISE_VORONOI:
//					{
//						// Layers
//						for( auto const &param : *noise->voronoi[index] ) {
//
//							double  e1 = 0.0f,
//									e2 = 0.0f,
//									e3 = 0.0f;
//
//							rng3 = std::minstd_rand0(param->seed);
//							genVoronoi.SetSeed(rng3());
//							genVoronoi.SetFrequency(param->frequency);
//							genVoronoi.SetDisplacement(param->displacement);
//							genVoronoi.EnableDistance(param->bDistance);
//
//							e1 = genVoronoi.GetValue(x, z, 0);
//							e2 = Core::Noise::applyFunctions(e1, dHeight, *param);
//							dHeight = Core::Noise::applyMode(e2, dHeight, param->mode);
//
//						}
//						break;
//					}
//
//					case Core::Noise::NOISE_BILLOW:
//					{
//						// Layers
//						for( auto const &param : *noise->billow[index] ) {
//
//							double  e1 = 0.0f,
//									e2 = 0.0f,
//									e3 = 0.0f;
//
//							rng4 = std::minstd_rand0(param->seed);
//							genBillow.SetSeed(rng4());
//							genBillow.SetFrequency(param->frequency);
//							genBillow.SetLacunarity(param->lacunarity);
//							genBillow.SetPersistence(param->persistence);
//							genBillow.SetNoiseQuality(param->quality);
//							genBillow.SetOctaveCount(param->octaves);
//
//							e1 = genBillow.GetValue(x, z, 0);
//							e2 = Core::Noise::applyFunctions(e1, dHeight, *param);
//							dHeight = Core::Noise::applyMode(e2, dHeight, param->mode);
//						}
//						break;
//					}
//
//					default:	// NOISE_NONE
//						debug.log("Load NONE");
//				}
//
//			}
//
//			return dHeight;
//		}



//		double MapSys::applyFunction(float x, float y, double height, double e2, Map::t_SimplexFunctions *functions) {
//			double rVal = 0.0f;
//			double e3 = e2;
//
//			for( auto function : *functions ) {
//				if(function.src == Map::SRC_HEIGHT) {
//					switch(function.dst) {
//						case Map::DST_SIMPLEX_AMPLITUDE:
//							break;
//						case Map::DST_SIMPLEX_FREQUENCY:
//							break;
//						case Map::DST_SIMPLEX_HEIGHT:
//							break;
//						case Map::DST_SIMPLEX_LACUNARITY:
//							break;
//						case Map::DST_SIMPLEX_OCTAVES:
//							break;
//						case Map::DST_SIMPLEX_PERSISTANCE:
//							break;
//						case Map::DST_SIMPLEX_POWER:
//							break;
//						case Map::DST_SIMPLEX_SCALE:
//							break;
//						//dst = function.apply(src, dst);
//					}
//				}
//			}

//			enum eFunctionSource {
//				SRC_POSITION,
//				SRC_HEIGHT
//			};
//
//			enum eFunctionTargetSimplex {
//				SIMPLEX_DST_FREQUENCY,
//				SIMPLEX_DST_AMPLITUDE,
//				SIMPLEX_DST_LACUNARITY,
//				SIMPLEX_DST_PERSISTANCE,
//				SIMPLEX_DST_POWER,
//				SIMPLEX_DST_SCALE,
//				SIMPLEX_DST_OCTAVES,
//				SIMPLEX_DST_HEIGHT
//			};
//		}













































	}
}

#endif /* WORLDMAP_H_ */
