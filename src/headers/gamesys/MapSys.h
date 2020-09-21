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
//#include "../core/types.h"
#include "../core/core_functions.h"
#include "../core/vao.h"
#include "../core/texture.h"
#include "../core/FractalNoise.h"
#include "./MapData.h"

namespace Core {
	namespace Sys {

		class MapSys {
			private:
				enum eTerrainType { TERRAIN_FLAT, TERRAIN_PERLIN, TERRAIN_SIMPLEX, TERRAIN_FRACTAL };
//				void generateTerrainChunk(Map::Data &map, float SIZE, int VERTEX_COUNT, eTerrainType eType=TERRAIN_PERLIN, int iTexScale=1, float fHeightOffset=0.0f);
				void generateTerrainChunk(int x, int z, Map::Data &map, Map::Simplex &simplex);

				// Setup Perlin Noise
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
				const eTerrainType TERRAIN_TYPE = TERRAIN_SIMPLEX;
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

				std::string dir;			// Directory location for map
//				VAO ** mapData;
//				Map::Data terrainChunk[4];		// Generic terrain chunk (TODO: LOD array)
				Texture tex;				// Map specific textures
				bool init();
				bool load(int x, int z, Map::Data &ref, Map::Simplex &simplex);
				bool calc(Map::Data &ref);
				void update(int x, int z, Map::Data &ref, Map::Simplex &simplex);
//				void draw(Core::SHADER_PROGRAMS iShader, Core::_Lights &lights);
				double getPerlinElevation(float x, float z, float w, float h);
				double getPerlinMoisture(float x, float z, float w, float h);
				double getSimplexElevation(float x, float z, Map::Simplex &simplex);
//				double getSimplexElevation(float x, float z, float freq, float amp, float lac, float per, int oct);
				double getFractalElevation(float x, float z);
		};

		bool MapSys::init() {
			Core::debug.log("Init MapSys {");

			if(!bInit) {
				rng1 = std::minstd_rand0(seed1);
				rng2 = std::minstd_rand0(seed2);
				rng3 = std::minstd_rand0(seed3);

				gen1.SetSeed(rng1());
				gen2.SetSeed(rng2());
				gen3.SetSeed(rng3());
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
		 * Create generic terrain chunks
		 */
		bool MapSys::load(int x, int z, Map::Data &ref, Map::Simplex &simplex) {
			Core::debug.log("Load MapSys {");

			/*
			 * Simulate loading entire world (first load essentially)
			 */
			Core::profiles->startProfile(Core::profiles->builtIn.MapSys_GeneratePerlin);

//				switch(TERRAIN_TYPE) {
//					case TERRAIN_PERLIN:
//						generateTerrainChunk(ref, 2048, 2048, TERRAIN_PERLIN, 1);
//						break;
//					case TERRAIN_SIMPLEX:
//						generateTerrainChunk(	ref,
//										Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].terrain_size,
//										Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].res+1,
//										TERRAIN_TYPE,
//										Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].tex_scale,
//										Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].terrain_height_offset);
						generateTerrainChunk( x, z, ref, simplex);
//						break;
//					case TERRAIN_FRACTAL:
//						generateTerrainChunk(	ref,
//										Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].terrain_size,
//										Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].res+1,
//										TERRAIN_TYPE,
//										Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].tex_scale,
//										Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].terrain_height_offset);
//						break;
//				}

			Core::profiles->stopProfile(Core::profiles->builtIn.MapSys_GeneratePerlin);

			Core::debug.print(" Done, Generation time = "+std::to_string(Core::profiles->getTime(Core::profiles->builtIn.MapSys_GeneratePerlin))+" ", Core::debug().GREEN);
			Core::debug.print("}\n");
			return true;
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
		//void MapSys::generateTerrainChunk(Map::Data &chunk, float SIZE, int VERTEX_COUNT, eTerrainType eType, int iTexScale, float fHeightOffset){
		void MapSys::generateTerrainChunk(int x, int z, Map::Data &chunk, Map::Simplex &simplex){

			// TODO: Allow eType to be changed
			float SIZE			= simplex.terrain_size;
			int VERTEX_COUNT	= simplex.res+1;
			eTerrainType eType	= TERRAIN_SIMPLEX;
			int iTexScale		= simplex.tex_scale;
			float fHeightOffset	= simplex.terrain_height_offset;
			float DELTA			= simplex.delta;


			chunk.numVerts = VERTEX_COUNT * VERTEX_COUNT;
			chunk.numDrawVerts = 6*(VERTEX_COUNT-1)*(VERTEX_COUNT-1);
			chunk.vVerts = new Data3f[chunk.numVerts];
			chunk.vNorms = new Data3f[chunk.numVerts];
			chunk.vCoords = new Data2f[chunk.numVerts];
			chunk.vIndex = new GLuint[chunk.numDrawVerts];


			long vertexPointer = 0;
			for(int i=0;i<VERTEX_COUNT;i++){
				for(int j=0;j<VERTEX_COUNT;j++){

					// Vertex
					chunk.vVerts[vertexPointer][0] = ((float)j/((float)VERTEX_COUNT - 1) * SIZE);
					chunk.vVerts[vertexPointer][2] = ((float)i/((float)VERTEX_COUNT - 1) * SIZE);
//					switch(eType) {
//						case TERRAIN_PERLIN:
//							chunk.vVerts[vertexPointer][1] = getPerlinElevation(chunk.vVerts[vertexPointer][0], chunk.vVerts[vertexPointer][2], 1024, 1024) + fHeightOffset;
//							break;
//						case TERRAIN_SIMPLEX:
							chunk.vVerts[vertexPointer][1] = getSimplexElevation(chunk.vVerts[vertexPointer][0]+x, chunk.vVerts[vertexPointer][2]+z, simplex) + fHeightOffset;
//							break;
//						case TERRAIN_FRACTAL:
//							chunk.vVerts[vertexPointer][1] = getFractalElevation(chunk.vVerts[vertexPointer][0], chunk.vVerts[vertexPointer][2]) + fHeightOffset;
//							break;
//						default:
//							chunk.vVerts[vertexPointer][1] = fHeightOffset;
//					}

					Vector3f modelXOffset,
							 modelYOffset,
							 modelXGrad,
							 modelYGrad,
							 A, B, C, BA, CA, Dir, Norm;

//					switch(eType) {
//						case TERRAIN_PERLIN:
//							A = chunk.vVerts[vertexPointer];
//
//							B.x = A.x+Core::gameVars->debug.noise.simplex[0].delta;
//							B.z = A.z+Core::gameVars->debug.noise.simplex[0].delta;
//							B.y = getPerlinElevation(B.x, B.z, 1024, 1024) + fHeightOffset;
//
//							C.x = A.x+Core::gameVars->debug.noise.simplex[0].delta;
//							C.z = A.z-Core::gameVars->debug.noise.simplex[0].delta;
//							C.y = getPerlinElevation(C.x, C.z, 1024, 1024) + fHeightOffset;
//
//							BA = B - A;
//							CA = C - A;
//							Dir = Core::gmath.Cross(BA, CA);
//							Norm = Dir/Dir.length();
//							break;
//						case TERRAIN_SIMPLEX:
							A = chunk.vVerts[vertexPointer];

							B.x = A.x+DELTA;
							B.z = A.z+DELTA;
							B.y = getSimplexElevation(B.x+x, B.z+z, simplex) + fHeightOffset;

							C.x = A.x+DELTA;
							C.z = A.z-DELTA;
							C.y = getSimplexElevation(C.x+x, C.z+z, simplex) + fHeightOffset;

							BA = B - A;
							CA = C - A;
							Dir = Core::gmath.Cross(BA, CA);
							Norm = Dir/Dir.length();
//							break;
//						case TERRAIN_FRACTAL:
//							A = chunk.vVerts[vertexPointer];
//
//							B.x = A.x+Core::gameVars->debug.noise.fractal[0].delta;
//							B.z = A.z+Core::gameVars->debug.noise.fractal[0].delta;
//							B.y = getFractalElevation(B.x, B.z) + fHeightOffset;
//
//							C.x = A.x+Core::gameVars->debug.noise.fractal[0].delta;
//							C.z = A.z-Core::gameVars->debug.noise.fractal[0].delta;
//							C.y = getFractalElevation(C.x, C.z) + fHeightOffset;
//
//							BA = B - A;
//							CA = C - A;
//							Dir = Core::gmath.Cross(BA, CA);
//							Norm = Dir/Dir.length();
//							break;
//						default:
//							chunk.vNorms[vertexPointer][0] = 0;
//							chunk.vNorms[vertexPointer][1] = 1;
//							chunk.vNorms[vertexPointer][2] = 0;
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
				}
			}

		}


		/*
		 * TODO: Calc(); Do general map calculations. (including LOD management?)
		 */
		bool MapSys::calc(Map::Data &ref) {
			Core::debug.log("Calc Map {");

			ref.vao.Begin(GL_TRIANGLES, ref.numVerts, ref.numDrawVerts, 1);
			ref.vao.CopyData(GLA_VERTEX, ref.vVerts);
			ref.vao.CopyData(GLA_NORMAL, ref.vNorms);
			ref.vao.CopyData(GLA_TEXTURE, ref.vCoords, 0);
			ref.vao.CopyData(GLA_INDEX, ref.vIndex, ref.numDrawVerts);
			ref.vao.End();

			Core::debug.print(" Done ", Core::debug().GREEN);
			Core::debug.print("}\n");
			return true;
		}

		void MapSys::update(int x, int z, Map::Data &ref, Map::Simplex &simplex) {

//			switch(TERRAIN_TYPE) {
//				case TERRAIN_PERLIN:
//					generateTerrainChunk(ref, 2048, 2048, TERRAIN_PERLIN, 1);
//
//					break;
//				case TERRAIN_SIMPLEX:
//					generateTerrainChunk(	ref,
//											Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].terrain_size,
//											Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].res+1,
//											TERRAIN_TYPE,
//											Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].tex_scale,
//											Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].terrain_height_offset);
					generateTerrainChunk( x, z, ref, simplex);
//					break;
//				case TERRAIN_FRACTAL:
//					generateTerrainChunk(	ref,
//											Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].terrain_size,
//											Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].res+1,
//											TERRAIN_TYPE,
//											Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].tex_scale,
//											Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].terrain_height_offset);
//					break;
//			}

			ref.vao.Begin(GL_TRIANGLES, ref.numVerts, ref.numDrawVerts, 1);
			ref.vao.CopyData(GLA_VERTEX, ref.vVerts);
			ref.vao.CopyData(GLA_NORMAL, ref.vNorms);
			ref.vao.CopyData(GLA_TEXTURE, ref.vCoords, 0);
			ref.vao.CopyData(GLA_INDEX, ref.vIndex, ref.numDrawVerts);
			ref.vao.End();

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

			return e1;
		}

		double MapSys::getPerlinMoisture(float x, float z, float w, float h) {
			return 0.0f;
		}

		double MapSys::getSimplexElevation(float x, float z, Map::Simplex &simplex) {

			double e1 = 0.0f;

			for( auto const &layer : simplex.params ) {
				double e1a = 0.0f;
				double e1b = 0.0f;
				SimplexNoise simNoise1 = SimplexNoise( layer.frequency,
													   layer.amplitude,
													   layer.lacunarity, //+((x+Core::gameVars.debug.noise.simplex.offset.x+z+Core::gameVars.debug.noise.simplex.offset.y)/1000.0f),
													   layer.persistance );

				e1a = simNoise1.fractal(	layer.octaves,
										x,
										z);

				e1b += (std::pow(e1a, layer.power)*layer.scale);

				e1 += e1b;

//				debug.log("["+	std::to_string(e1a)+"]["+
//								std::to_string(e1b)+"] "+
//								std::to_string(layer.frequency)+", "+
//								std::to_string(layer.amplitude)+", "+
//								std::to_string(layer.lacunarity)+", "+
//								std::to_string(layer.persistance)+", "+
//								std::to_string(layer.octaves)+", "+
//								std::to_string(layer.scale)+", "+
//								std::to_string(layer.power)+"\n");
			}

			return e1;
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
		}







	}
}

#endif /* WORLDMAP_H_ */
