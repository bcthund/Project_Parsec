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

		/**
		 * @brief Contains the entire definition for the world inclusing atmosphere, lighting, and all map chunks
		 */
		class _World {
			private:

			public:
				int iViewDistance;
				Atmosphere					atmosphere;
				_Lights						lights;
				t_UMap<std::string, t_MapInstance*>	map;		///< Index = 0xFFFFFFFF where the first 0xFFFF is the X-grid and the second 0xFFFF is the Y grid
				_World();
				~_World();

				void init();			///< Initialize all members
				void load();			///< Load initial terrain, O2D, and O3D
				void update();			///< Update terrain, O2D and O3D according to chunk status (distance check)
				void draw();			///< Draw all currently defined chunks
		};

		_World::_World() {
			iViewDistance = 4096;

			// TODO: Allow stting these values when _World defined (add constructor)
			// TODO: These should probably be local so there can bu multiple worlds (i.e. voids) with unique settings
			// TODO: These likely won't have any effect here because mapSys hasn't been initialized anywhere yet
//			Core::t_MapInstance::mapSys.init();
//			Core::t_MapInstance::mapSys.simplex.res					= 256;
//			Core::t_MapInstance::mapSys.simplex.tex_scale				= 128.0f;
//			Core::t_MapInstance::mapSys.simplex.terrain_size			= 1024;
//			Core::t_MapInstance::mapSys.simplex.terrain_height_offset	= 0.0f;
//			Core::t_MapInstance::mapSys.simplex.delta					= 32.0f;
//			Core::t_MapInstance::mapSys.simplex.frequency				= 0.00025f;
//			Core::t_MapInstance::mapSys.simplex.amplitude				= 1.0f;
//			Core::t_MapInstance::mapSys.simplex.lacunarity				= 2.9f;
//			Core::t_MapInstance::mapSys.simplex.persistance			= 0.33f;
//			Core::t_MapInstance::mapSys.simplex.power					= 1.0f;
//			Core::t_MapInstance::mapSys.simplex.scale					= 1.0f;		//875.0f;
//			Core::t_MapInstance::mapSys.simplex.octaves				= 3;
		}

		_World::~_World() {
			for (auto item : map) delete item.second;
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

			// TODO: Load initial maps out to distance
			t_MapInstance *newMap = new t_MapInstance("0100_0100");
			map.add("0100_0100", newMap);
			map["0100_0100"]->load();

			newMap = new t_MapInstance("0101_0100");
			map.add("0101_0100", newMap);
			map["0101_0100"]->load();
		}

		void _World::update() {
			atmosphere.update(atmosphere.MODE_SATELLITE);
			atmosphere.update(atmosphere.MODE_FLORA);
		}

		void _World::draw() {
			atmosphere.skybox.exosphere.draw();



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

			int x=0, z=0;
			glEnable(GL_CULL_FACE);
			Core::matrix->Push();
				// Move chunk according to player
				matrix->Rotate(Core::gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
				matrix->Rotate(Core::gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
				matrix->Translate(Core::gameVars->player.active->transform.pos[0], Core::gameVars->player.active->transform.pos[1], Core::gameVars->player.active->transform.pos[2]);

				// Move chunk into place (Do in loader so lighting works easily)
				Core::matrix->Scale(1*Core::gameVars->screen.fScale, 1*Core::gameVars->screen.fScale, 1*Core::gameVars->screen.fScale);
				//matrix->Translate(x*1024*Core::gameVars->screen.fScale, 0.0f, z*1024*Core::gameVars->screen.fScale);
				matrix->Translate(	x*Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].terrain_size*Core::gameVars->screen.fScale,
									0.0f,
									z*Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].terrain_size*Core::gameVars->screen.fScale);

				matrix->SetTransform();

				shader->use(Core::GLS_PHONG);
				shader->getUniform(Core::GLS_PHONG, &lights);

				map["0100_0100"]->draw(Core::GLS_PHONG, lights);

				// Draw vertex normals (~6fps drop)
				if(Core::gameVars->debug.gui.b5) {
					glLineWidth(1.0f);
					shader->use(GLS_NORMAL_LINE2);
					shader->getUniform(GLS_NORMAL_LINE2);
					map["0100_0100"]->draw(Core::GLS_PHONG, lights);
				}

				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			Core::matrix->Pop();

			x=1, z=0;
			glEnable(GL_CULL_FACE);
			Core::matrix->Push();
				// Move chunk according to player
				matrix->Rotate(Core::gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
				matrix->Rotate(Core::gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
				matrix->Translate(Core::gameVars->player.active->transform.pos[0], Core::gameVars->player.active->transform.pos[1], Core::gameVars->player.active->transform.pos[2]);

				// Move chunk into place (Do in loader so lighting works easily)
				Core::matrix->Scale(1*Core::gameVars->screen.fScale, 1*Core::gameVars->screen.fScale, 1*Core::gameVars->screen.fScale);
				matrix->Translate(	x*Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].terrain_size*Core::gameVars->screen.fScale,
									0.0f,
									z*Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].terrain_size*Core::gameVars->screen.fScale);
				matrix->SetTransform();

				shader->use(Core::GLS_PHONG);
				shader->getUniform(Core::GLS_PHONG, &lights);

				map["0101_0100"]->draw(Core::GLS_PHONG, lights);

				// Draw vertex normals (~6fps drop)
				if(Core::gameVars->debug.gui.b5) {
					glLineWidth(1.0f);
					shader->use(GLS_NORMAL_LINE2);
					shader->getUniform(GLS_NORMAL_LINE2);
					map["0101_0100"]->draw(Core::GLS_PHONG, lights);
				}

				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			Core::matrix->Pop();

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
