/*
 * WorldMap.h
 *
 *  Created on: Aug 29, 2019
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_WORLDMAP_H_
#define HEADERS_GAMESYS_WORLDMAP_H_


#include "../core/extern.h"
#include "../core/core_functions.h"
#include "./MapInstance.h"
//#include "O2D.h"
//#include "O3D.h"

/*
 * TODO: WorldMap Items
 * 		[ ] Lights
 * 			[ ] Load from file
 * 			[ ] Player Flashlight
 * 				[ ] Move with player
 * 				[ ] Rotate with player
 * 			[ ] Player Omni Light
 * 				[ ] Move with player
 *
 *		[ ] O3D
 *			[ ] Load from file
 *
 *		[ ] O2D
 *			[ ] Load from file
 *
 *		[ ] Gravity
 *		[ ] Ground Height
 *		[ ] Load Map from file
 *			[ ] Initial Load
 *			[ ] Settings Load
 *			[ ] Atmosphere Load
 *				[ ] Water
 *				[ ] Weather
 *				[ ] Flora
 *			[ ] O2D Load
 *			[ ] O3D Load
 *			[ ] E2D Load
 *			[ ] Edge of map detection, load new map
 */

namespace Core {
	namespace Sys {

		struct {
			struct s_COMMON {
				const int SCALE_POWER		= 5;
				const int SCALE				= pow(2, SCALE_POWER);
				const int CHUNK_SIZE		= 1024 * SCALE; //32768;//65536; //1024 * SCALE;
				const int VIEW_DISTANCE		= CHUNK_SIZE*16;
			};

			struct : public s_COMMON {
				const int CHUNK_RESOLUTION	= 8 * SCALE_POWER;
				const float TEXTURE_SCALE	= 10.0f * SCALE_POWER;
				const float HEIGHT_OFFSET	= 1000.0f;
				const float DELTA			= 32.0f * SCALE;
			} TERRAIN;

			struct : public s_COMMON {
				const int CHUNK_RESOLUTION	= 1;
				const float TEXTURE_SCALE	= 1.0f * SCALE_POWER;
				const float HEIGHT_OFFSET	= 0.0f;
				const float DELTA			= 32.0f * SCALE_POWER;
			} WATER;
		} CONST_SIMPLEX;

//		struct {
//			struct s_COMMON {
//				const int CHUNK_SIZE		= 16384;
//				const int VIEW_DISTANCE		= CHUNK_SIZE*8;
//			};
//
//			struct : public s_COMMON {
//				const int CHUNK_RESOLUTION	= 16;
//				const float TEXTURE_SCALE	= 10.0f;
//				const float HEIGHT_OFFSET	= 0.0f;
//				const float DELTA			= 64.0f;
//			} TERRAIN;
//
//			struct : public s_COMMON {
//				const int CHUNK_RESOLUTION	= 1;
//				const float TEXTURE_SCALE	= 1.0f;
//				const float HEIGHT_OFFSET	= -500.0f;
//				const float DELTA			= 1.0f;
//			} WATER;
//		} CONST_SIMPLEX;

		/**
		 * @brief Contains the entire definition for the world inclusing atmosphere, lighting, and all map chunks
		 */
		class _World {
			private:

			public:
//				int iViewDistance;
				Atmosphere					atmosphere;
				_Lights						lights;
//				t_Vector1T<Map::Simplex>	simplex;
				t_UMap<std::string, Map::t_ChunkData*> chunkSettings;
				t_UMap<std::string, Map::t_Simplex*> simplex;
				t_UMap<std::string, t_MapInstance*>	map;		///< Index = 0xFFFFFFFF where the first 0xFFFF is the X-grid and the second 0xFFFF is the Y grid
//				int iMax;										///< Maximum view distance in chunks
//				void set_iMax();
				_World();
				~_World();

				void init();			///< Initialize all members
				void load();			///< Load initial terrain, O2D, and O3D
				void update();			///< Update terrain, O2D and O3D according to chunk status (distance check)
				void draw();			///< Draw all currently defined chunks
		};

		_World::_World() {
			// Default values
			chunkSettings.add("Terrain", new Map::t_ChunkData);
			chunkSettings["Terrain"]->iViewDistance = CONST_SIMPLEX.TERRAIN.VIEW_DISTANCE;
			chunkSettings["Terrain"]->chunk_resolution = CONST_SIMPLEX.TERRAIN.CHUNK_RESOLUTION;
			chunkSettings["Terrain"]->chunk_size = CONST_SIMPLEX.TERRAIN.CHUNK_SIZE;
			chunkSettings["Terrain"]->set_iMax();
			Map::t_Simplex *newSimplex = new Map::t_Simplex(chunkSettings["Terrain"]);
			simplex.add("Terrain", newSimplex);

			chunkSettings.add("Water", new Map::t_ChunkData);
			chunkSettings["Water"]->iViewDistance = CONST_SIMPLEX.TERRAIN.VIEW_DISTANCE;
			chunkSettings["Water"]->chunk_resolution = CONST_SIMPLEX.TERRAIN.CHUNK_RESOLUTION;
			chunkSettings["Water"]->chunk_size = CONST_SIMPLEX.TERRAIN.CHUNK_SIZE;
			chunkSettings["Water"]->set_iMax();
			newSimplex = new Map::t_Simplex(chunkSettings["Water"]);
			simplex.add("Water", newSimplex);
		}

		_World::~_World() {
			for (auto item : map) delete item.second;
			for (auto item : simplex) delete item.second;
		}

		void _World::init() {
			atmosphere.init();
			lights.init();
		}

		void _World::load() {
			atmosphere.load();
			atmosphere.calc();

			lights.load();
			lights.calc(Core::gameVars->screen.fScale);

			simplex["Water"]->parent->chunk_resolution			= CONST_SIMPLEX.WATER.CHUNK_RESOLUTION;
			simplex["Water"]->parent->chunk_size				= CONST_SIMPLEX.WATER.CHUNK_SIZE;
			simplex["Water"]->parent->tex_scale					= CONST_SIMPLEX.WATER.TEXTURE_SCALE;
			simplex["Water"]->parent->chunk_height_offset		= CONST_SIMPLEX.WATER.HEIGHT_OFFSET;
			simplex["Water"]->parent->delta						= CONST_SIMPLEX.WATER.DELTA;

			simplex["Water"]->params.add("Base", Map::t_SimplexParams());
			simplex["Water"]->params["Base"].frequency			= 0.00013f;
			simplex["Water"]->params["Base"].amplitude			= 1.0f;
			simplex["Water"]->params["Base"].lacunarity			= 2.0f;
			simplex["Water"]->params["Base"].persistance		= 2.0f;
			simplex["Water"]->params["Base"].power				= 1.0f;
			simplex["Water"]->params["Base"].scale				= 100.0f;
			simplex["Water"]->params["Base"].octaves			= 2;

			simplex["Terrain"]->parent->chunk_resolution		= CONST_SIMPLEX.TERRAIN.CHUNK_RESOLUTION;
			simplex["Terrain"]->parent->chunk_size				= CONST_SIMPLEX.TERRAIN.CHUNK_SIZE;
			simplex["Terrain"]->parent->tex_scale				= CONST_SIMPLEX.TERRAIN.TEXTURE_SCALE;
			simplex["Terrain"]->parent->chunk_height_offset		= CONST_SIMPLEX.TERRAIN.HEIGHT_OFFSET;
			simplex["Terrain"]->parent->delta					= CONST_SIMPLEX.TERRAIN.DELTA;

			simplex["Terrain"]->params.add("Base", Map::t_SimplexParams());
			simplex["Terrain"]->params["Base"].frequency		= 0.00013f;
			simplex["Terrain"]->params["Base"].amplitude		= 1.0f;
			simplex["Terrain"]->params["Base"].lacunarity		= 2.0f;
			simplex["Terrain"]->params["Base"].persistance		= 2.0f;
			simplex["Terrain"]->params["Base"].power			= 3.0f;
			simplex["Terrain"]->params["Base"].scale			= 250.0f; //100.0f;
			simplex["Terrain"]->params["Base"].octaves			= 4; //3;

			simplex["Terrain"]->params.add("Hills", Map::t_SimplexParams());
			simplex["Terrain"]->params["Hills"].frequency		= 0.00008f;
			simplex["Terrain"]->params["Hills"].amplitude		= 2.0f;
			simplex["Terrain"]->params["Hills"].lacunarity		= 2.2f;
			simplex["Terrain"]->params["Hills"].persistance		= 1.8f;
			simplex["Terrain"]->params["Hills"].power			= 3.0f;
			simplex["Terrain"]->params["Hills"].scale			= 1000.0f;
			simplex["Terrain"]->params["Hills"].octaves			= 2; //2;

			simplex["Terrain"]->params.add("Valleys", Map::t_SimplexParams());
			simplex["Terrain"]->params["Valleys"].frequency		= 0.000005f;
			simplex["Terrain"]->params["Valleys"].amplitude		= 5.0f;
			simplex["Terrain"]->params["Valleys"].lacunarity	= 1.8f; //2.8f;
			simplex["Terrain"]->params["Valleys"].persistance	= -1.0f;
			simplex["Terrain"]->params["Valleys"].power			= 3.0f; //3.0f;
			simplex["Terrain"]->params["Valleys"].scale			= -500.0f;
			simplex["Terrain"]->params["Valleys"].octaves		= 3; //4;

			simplex["Terrain"]->params.add("Mountain", Map::t_SimplexParams());
			simplex["Terrain"]->params["Mountain"].frequency	= 0.00001f;
			simplex["Terrain"]->params["Mountain"].amplitude	= 100.0f;
			simplex["Terrain"]->params["Mountain"].lacunarity	= 1.025f;
			simplex["Terrain"]->params["Mountain"].persistance	= 0.025f;
			simplex["Terrain"]->params["Mountain"].power		= 4.0f;
			simplex["Terrain"]->params["Mountain"].scale		= 20000.0f;
			simplex["Terrain"]->params["Mountain"].octaves		= 4; //1;

			simplex["Terrain"]->params.add("Continent", Map::t_SimplexParams());
			simplex["Terrain"]->params["Continent"].frequency	= 0.000001f;
			simplex["Terrain"]->params["Continent"].amplitude	= 1.0f;
			simplex["Terrain"]->params["Continent"].lacunarity	= 0.025f;
			simplex["Terrain"]->params["Continent"].persistance	= 0.025f;
			simplex["Terrain"]->params["Continent"].power		= 3.0f;
			simplex["Terrain"]->params["Continent"].scale		= 100000.0f;
			simplex["Terrain"]->params["Continent"].octaves		= 1; //1;

			//simplex["Terrain"]->params.add("Ocean", Map::Simplex::t_NoiseParams());

			//iMax = iViewDistance/simplex["Terrain"]->terrain_size;
			chunkSettings["Terrain"]->set_iMax();
			for(int x=-chunkSettings["Terrain"]->iMax; x<chunkSettings["Terrain"]->iMax; x++) {
				for(int z=-chunkSettings["Terrain"]->iMax; z<chunkSettings["Terrain"]->iMax; z++) {

					int dist = std::sqrt((x*x)+(z*z));
					if(dist < chunkSettings["Terrain"]->iMax) {
//						debug.log("Distance = "+std::to_string(dist)+"/"+std::to_string(simplex["Terrain"]->iMax)+": ");
						std::stringstream ssx, ssz;
						ssx << std::setfill ('0') << std::setw(4);
						ssx << std::hex << (x+32768);

						ssz << std::setfill ('0') << std::setw(4);
						ssz << std::hex << (z+32768);

						std::string mapName = ssx.str() + "_" + ssz.str();

						t_MapInstance *newMap = new t_MapInstance(mapName);		// NOTE: mapName translates into the map offset here
						map.add(mapName, newMap);

						// Will load center map at different resolution
//						if(x==0 && z==0) simplex["Terrain"]->res = 32;
//						else simplex["Terrain"]->res = 8;

//						map[mapName]->load(simplex["Terrain"], simplex["Water"]);
						map[mapName]->load(simplex["Terrain"]);
					}
				}
			}

			// TESTING: Change view distance for distance calculation visualization (grass/dirt texture)
//			simplex["Terrain"]->iViewDistance = 1024*8;

		}

//		void _World::set_iMax() {
//			iMax = iViewDistance/simplex["Terrain"]->terrain_size;
//		}

		// TODO: Idea
		void _World::update() {
			atmosphere.update(atmosphere.MODE_SATELLITE);
//			atmosphere.update(atmosphere.MODE_FLORA);


			chunkSettings["Terrain"]->delta = CONST_SIMPLEX.TERRAIN.DELTA;
			chunkSettings["Terrain"]->set_iMax();	// In case parameters have changed
			//int iMax = iViewDistance/simplex["Terrain"]->terrain_size;

			t_Vector1T<std::string> removeMaps;

			// Update distance for all chunks according to players current position
			for ( auto chunk : map ) {
				chunk.second->update(gameVars->player.active->transform.pos, chunkSettings["Terrain"]->chunk_size);
				chunk.second->bDraw = chunk.second->distance<chunkSettings["Terrain"]->iMax;

				// TODO: Remove chunks beyond visibility
				//	- Start a timer when bDraw active
				//	- If timer expires, then drop chunk (prevents player from turning around needed to reload maps for a limited time)

				//if(chunk.second->distance>iMax) debug.log("Chunk '"+chunk.first+"' is outside max range. ("+std::to_string(chunk.second->distance)+">"+std::to_string(iMax)+")\n");
				if(chunk.second->distance>chunkSettings["Terrain"]->iMax) {
//					debug.log("Chunk '"+chunk.first+"' is outside max range. ("+std::to_string(chunk.second->distance)+">"+std::to_string(simplex["Terrain"]->iMax)+")\n");
					//std::string removeMap = chunk.first;
					//map.remove(removeMap);
					removeMaps.add(chunk.first);
				}
			}

			// Drop maps outside view range
			if(removeMaps.size()>0) {
				for (auto removeMap : removeMaps ) {
					delete map[removeMap];
					map.remove(removeMap);
				}
			}

			// Check for new chunks in range
			for(int x=-chunkSettings["Terrain"]->iMax; x<chunkSettings["Terrain"]->iMax; x++) {
				for(int z=-chunkSettings["Terrain"]->iMax; z<chunkSettings["Terrain"]->iMax; z++) {
					// Get players current chunk
					Vector2f vA;
					vA.x = -gameVars->player.active->transform.pos.x/chunkSettings["Terrain"]->chunk_size;
					vA.y = -gameVars->player.active->transform.pos.z/chunkSettings["Terrain"]->chunk_size;

					// Rounding
					if(vA.x<0) vA.x-=1.0f; else vA.x+=1.0f;
					if(vA.y<0) vA.y-=1.0f; else vA.y+=1.0f;

					// Get offset chunk
					Vector2f vB;
					vB.x = x+int(vA.x);
					vB.y = z+int(vA.y);

					// Get mapName, needed to check if loaded or load new
					std::stringstream ssx, ssz;
					ssx << std::setfill ('0') << std::setw(4);
					ssx << std::hex << int(vB.x+32768);
					ssz << std::setfill ('0') << std::setw(4);
					ssz << std::hex << int(vB.y+32768);
					std::string mapName = ssx.str() + "_" + ssz.str();

//					debug.log(" Player Chunk = ("+std::to_string(vA.x)+","+std::to_string(vA.y)+")\n");
//					debug.log("Terrain Chunk = ("+std::to_string(x)+","+std::to_string(z)+")\n");
//					debug.log(" Offset Chunk = ("+std::to_string(vB.x)+","+std::to_string(vB.y)+") ["+ssx.str()+", "+ssz.str()+"]: ");
//					debug.log(" Offset Chunk = ("+std::to_string(vB.x)+","+std::to_string(vB.y)+") ["+mapName+"]: ");

					// Check if chunk is already loaded
					if(!map.checkKey(mapName, false)) {
						// Calculate distance from current chunk to new chunk
						float distance = (vB-vA).length();

						// Check if new chunk is in valid range
						if(distance < chunkSettings["Terrain"]->iMax) {
							// Load new chunk
							t_MapInstance *newMap = new t_MapInstance(mapName);		// NOTE: mapName translates into the map offset here
							map.add(mapName, newMap);
//							map[mapName]->load(simplex["Terrain"], simplex["Water"]);
							map[mapName]->load(simplex["Terrain"]);
						}
					}
				}
			}




		}

		void _World::draw() {
			atmosphere.skybox.exosphere.draw();

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			glActiveTexture(GL_TEXTURE0);
			Core::sysTex->set(Core::sysTex->TEX_DIRT1);

			glActiveTexture(GL_TEXTURE1);
			Core::sysTex->set(Core::sysTex->TEX_DIRT2);

			glActiveTexture(GL_TEXTURE2);
			Core::sysTex->set(Core::sysTex->TEX_GRASS1);

			glActiveTexture(GL_TEXTURE3);
			Core::sysTex->set(Core::sysTex->TEX_GRASS2);

			glActiveTexture(GL_TEXTURE4);
			Core::sysTex->set(Core::sysTex->TEX_ROCKY1);

			glActiveTexture(GL_TEXTURE5);
			Core::sysTex->set(Core::sysTex->TEX_ROCKY2);

			glActiveTexture(GL_TEXTURE6);
			Core::sysTex->set(Core::sysTex->TEX_CLIFF1);

			glActiveTexture(GL_TEXTURE7);
			Core::sysTex->set(Core::sysTex->TEX_CLIFF2);

			glActiveTexture(GL_TEXTURE8);
			Core::sysTex->set(Core::sysTex->TEX_MUD1);

			glActiveTexture(GL_TEXTURE9);
			Core::sysTex->set(Core::sysTex->TEX_MUD2);

			glActiveTexture(GL_TEXTURE10);
			Core::sysTex->set(Core::sysTex->TEX_SNOW1);

			glActiveTexture(GL_TEXTURE11);
			Core::sysTex->set(Core::sysTex->TEX_SNOW2);

			glActiveTexture(GL_TEXTURE12);
			Core::sysTex->set(Core::sysTex->TEX_WATER);

//			glEnable(GL_CULL_FACE);
//			glDisable(GL_CULL_FACE);
			Core::matrix->Push();
				// Move chunk according to player
				matrix->Rotate(Core::gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
				matrix->Rotate(Core::gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
				matrix->Translate(Core::gameVars->player.active->transform.pos[0]-(chunkSettings["Terrain"]->chunk_size/2),
								  Core::gameVars->player.active->transform.pos[1],
								  Core::gameVars->player.active->transform.pos[2]-(chunkSettings["Terrain"]->chunk_size/2));

				// Move chunk into place (Do in loader so lighting works easily)
				Core::matrix->Scale(1*Core::gameVars->screen.fScale, 1*Core::gameVars->screen.fScale, 1*Core::gameVars->screen.fScale);
				//matrix->Translate(x*1024*Core::gameVars->screen.fScale, 0.0f, z*1024*Core::gameVars->screen.fScale);

				//shader->use(Core::GLS_PHONG);
//				Core::SHADER_PROGRAMS eShader = Core::GLS_PHONG;
//				Core::SHADER_PROGRAMS eShader = Core::GLS_FLAT;
//				shader->use(eShader);

				float fPreScale = chunkSettings["Terrain"]->chunk_size*Core::gameVars->screen.fScale;

				for ( auto chunk : map ) {
//					if(chunk.second->bDraw) {	// Will hide terrain outside view range
						Core::matrix->Push();

//							if(chunk.second->distance>simplex["Terrain"]->iMax) Core::sysTex->set(Core::sysTex->TEX_DIRT);
//							else Core::sysTex->set(Core::sysTex->TEX_GRASS);

							// TODO: Pass this to shader, translating here causes issues with lights repeating
							int iX = chunk.second->x-32768;
							int iZ = chunk.second->z-32768;
							matrix->Translate(	iX*fPreScale,
												0.0f,
												iZ*fPreScale);


							matrix->SetTransform();
							shader->use(Core::GLS_PHONG);
							shader->getUniform(Core::GLS_PHONG, &lights);
							chunk.second->drawTerrain();

	//						debug.log("Drawing '"+chunk.first+"'\n");

							// Draw vertex normals (~6fps drop)
	//						if(Core::gameVars->debug.gui.b5) {
	//							glLineWidth(1.0f);
	//							shader->use(GLS_NORMAL_LINE2);
	//							shader->getUniform(GLS_NORMAL_LINE2);
	//							chunk.second->draw(Core::GLS_PHONG);
	//						}

						Core::matrix->Pop();
//					}
				}

				for ( auto chunk : map ) {
						Core::matrix->Push();
							int iX = chunk.second->x-32768;
							int iZ = chunk.second->z-32768;
							matrix->Translate(	iX*fPreScale,
												0.0f,
												iZ*fPreScale);

							matrix->SetTransform();
							shader->use(Core::GLS_WATER);
							shader->getUniform(Core::GLS_WATER, &lights);
							chunk.second->drawWater();
						Core::matrix->Pop();
				}
			Core::matrix->Pop();

//			x=1, z=0;
//			glEnable(GL_CULL_FACE);
//			Core::matrix->Push();
//				// Move chunk according to player
//				matrix->Rotate(Core::gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
//				matrix->Rotate(Core::gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
//				matrix->Translate(Core::gameVars->player.active->transform.pos[0], Core::gameVars->player.active->transform.pos[1], Core::gameVars->player.active->transform.pos[2]);
//
//				// Move chunk into place (Do in loader so lighting works easily)
//				Core::matrix->Scale(1*Core::gameVars->screen.fScale, 1*Core::gameVars->screen.fScale, 1*Core::gameVars->screen.fScale);
//				matrix->Translate(	x*simplex["Terrain"]->terrain_size*Core::gameVars->screen.fScale,
//									0.0f,
//									z*simplex["Terrain"]->terrain_size*Core::gameVars->screen.fScale);
//				matrix->SetTransform();
//
//				shader->use(Core::GLS_PHONG);
//				shader->getUniform(Core::GLS_PHONG, &lights);
//
//				map["0101_0100"]->draw(Core::GLS_PHONG, lights);
//
//				// Draw vertex normals (~6fps drop)
//				if(Core::gameVars->debug.gui.b5) {
//					glLineWidth(1.0f);
//					shader->use(GLS_NORMAL_LINE2);
//					shader->getUniform(GLS_NORMAL_LINE2);
//					map["0101_0100"]->draw(Core::GLS_PHONG, lights);
//				}
//
//				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//			Core::matrix->Pop();
//
//			x=0, z=1;
//			glEnable(GL_CULL_FACE);
//			Core::matrix->Push();
//				// Move chunk according to player
//				matrix->Rotate(Core::gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
//				matrix->Rotate(Core::gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
//				matrix->Translate(Core::gameVars->player.active->transform.pos[0], Core::gameVars->player.active->transform.pos[1], Core::gameVars->player.active->transform.pos[2]);
//
//				// Move chunk into place (Do in loader so lighting works easily)
//				Core::matrix->Scale(1*Core::gameVars->screen.fScale, 1*Core::gameVars->screen.fScale, 1*Core::gameVars->screen.fScale);
//				matrix->Translate(	x*simplex["Terrain"]->terrain_size*Core::gameVars->screen.fScale,
//									0.0f,
//									z*simplex["Terrain"]->terrain_size*Core::gameVars->screen.fScale);
//				matrix->SetTransform();
//
//				shader->use(Core::GLS_PHONG);
//				shader->getUniform(Core::GLS_PHONG, &lights);
//
//				map["0100_0101"]->draw(Core::GLS_PHONG, lights);
//
//				// Draw vertex normals (~6fps drop)
//				if(Core::gameVars->debug.gui.b5) {
//					glLineWidth(1.0f);
//					shader->use(GLS_NORMAL_LINE2);
//					shader->getUniform(GLS_NORMAL_LINE2);
//					map["0100_0101"]->draw(Core::GLS_PHONG, lights);
//				}
//
//				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//			Core::matrix->Pop();
//
//
//			x=1, z=1;
//			glEnable(GL_CULL_FACE);
//			Core::matrix->Push();
//				// Move chunk according to player
//				matrix->Rotate(Core::gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
//				matrix->Rotate(Core::gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
//				matrix->Translate(Core::gameVars->player.active->transform.pos[0], Core::gameVars->player.active->transform.pos[1], Core::gameVars->player.active->transform.pos[2]);
//
//				// Move chunk into place (Do in loader so lighting works easily)
//				Core::matrix->Scale(1*Core::gameVars->screen.fScale, 1*Core::gameVars->screen.fScale, 1*Core::gameVars->screen.fScale);
//				matrix->Translate(	x*simplex["Terrain"]->terrain_size*Core::gameVars->screen.fScale,
//									0.0f,
//									z*simplex["Terrain"]->terrain_size*Core::gameVars->screen.fScale);
//				matrix->SetTransform();
//
//				shader->use(Core::GLS_PHONG);
//				shader->getUniform(Core::GLS_PHONG, &lights);
//
//				map["0101_0101"]->draw(Core::GLS_PHONG, lights);
//
//				// Draw vertex normals (~6fps drop)
//				if(Core::gameVars->debug.gui.b5) {
//					glLineWidth(1.0f);
//					shader->use(GLS_NORMAL_LINE2);
//					shader->getUniform(GLS_NORMAL_LINE2);
//					map["0101_0101"]->draw(Core::GLS_PHONG, lights);
//				}
//
//				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//			Core::matrix->Pop();


		}


























//		class _WorldMap {
//			public:
//				_O2D * o2d;
//				_O3D * o3d;
//				_WorldMap(	/*Matrix_System	&inMatrix,*/
//							/*Shader_System	&inShader,*/
//							_Collision		&inCollision,
//							_Helper			&inHelper);
//				virtual ~_WorldMap();
//				bool load();
//				bool calc();
//				void draw();
//				_Lights			* lights;		// TODO: Lights Temp Public, add access functions
//				Atmosphere		* atmosphere;
//				MapSys			* map;
//				//_Occlusion		* occlusion;
//				//_Occlusion		* occlusion2;
//
//			private:
//				/*Matrix_System 	* matrix;*/
//				/*Shader_System 	* shader;*/
//				//_Lights			* lights;
//				_Collision		* collision;
//				_Helper			* helper;
//		};
//
//		_WorldMap::_WorldMap(	/*Matrix_System	&inMatrix,*/
//								/*Shader_System	&inShader,*/
//								_Collision		&inCollision,
//								_Helper			&inHelper) {
//
//			Core::debug.log("Construct World {\n");
//			Core::debug.logIncreaseIndent();
//
//			collision = &inCollision;
//			helper = &inHelper;
//			std::cout << sOffset; lights = new _Lights();
//
//			map = new MapSys();
//
//			o2d	= new _O2D(*matrix, *shader);
//			o3d = new _O3D(*matrix, *shader, *collision, *helper);
//
//			atmosphere = new Atmosphere();
//			//std::cout << sOffset; occlusion = new _Occlusion();
//			//std::cout << sOffset; occlusion2 = new _Occlusion();
//
//			lights->init();
//			atmosphere->init();
//			map->init();
//			//o2d->init();
//			//o3d->init();
//
//			Core::debug.logDecreaseIndent();
//			Core::debug.log("}\n");
//		}
//
//		_WorldMap::~_WorldMap() {
//			Core::debug.log("Destruct World {\n");
//			Core::debug.logIncreaseIndent();
//			delete map;
//			delete o2d;
//			delete o3d;
//			delete lights;
//			delete atmosphere;
//			//std::cout << sOffset; delete occlusion;
//			//std::cout << sOffset; delete occlusion2;
//			Core::debug.logDecreaseIndent();
//			Core::debug.log("}\n");
//		}
//
//		bool _WorldMap::load() {
//			Core::debug.log("Load World {\n");
//			Core::debug.logIncreaseIndent();
//			lights->load();
//			map->load();
//			o2d->load();
//			o3d->load();
//			atmosphere->load();
//			Core::debug.logDecreaseIndent();
//			Core::debug.log("}\n");
//			return true;
//		}
//
//		bool _WorldMap::calc() {
//			Core::debug.log("Calc World {\n");
//			Core::debug.logIncreaseIndent();
//			lights->calc(Core::gameVars->screen.fScale);
//			map->calc();
//			o2d->calc();
//			o3d->calc();
//
//			//atmosphere->skybox.calc();
//			atmosphere->calc();
//
//			Core::debug.logDecreaseIndent();
//			Core::debug.log("}\n");
//			return true;
//		}
//
//		void _WorldMap::draw() {
//			atmosphere->update(atmosphere->MODE_SATELLITE);
//			atmosphere->update(atmosphere->MODE_FLORA);
//
//			// Draw atmosphere
//			atmosphere->skybox.exosphere.draw();
//
//			// Draw Map (After atmosphere, before objects)
//			//map->draw(GLS_PHONG);	// TODO: lights for map for GLS_PHONG
////			map->draw(GLS_FONT);
//			map->draw(Core::GLS_PHONG, *lights);
//
//			// Draw scenery before satellites to allow occlusion to work
//			o2d->draw(Core::GLS_PHONG_O2D, *lights);
//			o3d->draw(Core::GLS_PHONG, *lights);
//
//			// Pseudo distance sorting of satellites (only makes sense for two satellites)
//			float fMoonDistActual = (atmosphere->satellite->getPosition("Moon")+atmosphere->satellite->getPosition("Sun")).length();
//			if (fMoonDistActual>atmosphere->satellite->getPosition("Sun").length()) {
//				atmosphere->draw(atmosphere->MODE_SATELLITE, "Moon");	// TODO: [Atmosphere] Add a target setting for satellites? Pointer to any existing object (Vector3f) or create new pointer for fixed position
//				atmosphere->draw(atmosphere->MODE_SATELLITE, "Sun");
//			}
//			else {
//				atmosphere->draw(atmosphere->MODE_SATELLITE, "Sun");
//				atmosphere->draw(atmosphere->MODE_SATELLITE, "Moon");	// TODO: [Atmosphere] Add a target setting for satellites? Pointer to any existing object (Vector3f) or create new pointer for fixed position
//			}
//
//			// Draw after other objects for proper alpha blending
//			// TODO: Move Flora to particle emitter class
//			atmosphere->draw(atmosphere->MODE_FLORA, "Flora");
//		}


















	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_WORLDMAP_H_ */
