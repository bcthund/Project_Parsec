/*
 * WorldMap.h
 *
 *  Created on: Aug 29, 2019
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_WORLDMAP_H_
#define HEADERS_GAMESYS_WORLDMAP_H_


#include "../core/extern.h"
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
	namespace GameSys {
		class _WorldMap {
			public:
				_O2D * o2d;
				_O3D * o3d;
				_WorldMap(	/*Matrix_System	&inMatrix,*/
							/*Shader_System	&inShader,*/
							_Collision		&inCollision,
							_Helper			&inHelper);
				virtual ~_WorldMap();
				bool load();
				bool calc();
				void draw();
				_Lights			* lights;		// TODO: Lights Temp Public, add access functions
				Atmosphere		* atmosphere;
				MapSys			* map;
				//_Occlusion		* occlusion;
				//_Occlusion		* occlusion2;

			private:
				/*Matrix_System 	* matrix;*/
				/*Shader_System 	* shader;*/
				//_Lights			* lights;
				_Collision		* collision;
				_Helper			* helper;
		};

		_WorldMap::_WorldMap(	/*Matrix_System	&inMatrix,*/
								/*Shader_System	&inShader,*/
								_Collision		&inCollision,
								_Helper			&inHelper) {
			std::cout << "Construct World {" << std::endl;
			Core::sOffset = "    ";
			/*matrix = &inMatrix;*/
			/*shader = &inShader;*/
			collision = &inCollision;
			helper = &inHelper;
			std::cout << sOffset; lights = new _Lights();

			map = new MapSys();

			o2d	= new _O2D(*matrix, *shader);
			o3d = new _O3D(*matrix, *shader, *collision, *helper);

			atmosphere = new Atmosphere();
			//std::cout << sOffset; occlusion = new _Occlusion();
			//std::cout << sOffset; occlusion2 = new _Occlusion();

			lights->init();
			atmosphere->init();
			map->init();
			//o2d->init();
			//o3d->init();

			Core::sOffset = "";
			std::cout << "}" << std::endl;
		}

		_WorldMap::~_WorldMap() {
			std::cout << "Destruct World {" << std::endl;
			Core::sOffset = "    ";
			std::cout << sOffset; delete map;
			std::cout << sOffset; delete o2d;
			std::cout << sOffset; delete o3d;
			std::cout << sOffset; delete lights;
			std::cout << sOffset; delete atmosphere;
			//std::cout << sOffset; delete occlusion;
			//std::cout << sOffset; delete occlusion2;
			Core::sOffset = "";
			std::cout << "}" << std::endl;
		}

		bool _WorldMap::load() {
			std::cout << "Load World {" << std::endl;
			Core::sOffset = "    ";
			lights->load();
			map->load();
			o2d->load();
			o3d->load();
			atmosphere->load();
			Core::sOffset = "";
			std::cout << "}" << std::endl;
			return true;
		}

		bool _WorldMap::calc() {
			std::cout << "Calc World {" << std::endl;
			Core::sOffset = "    ";
			lights->calc(Core::gameVars->screen.fScale);
			map->calc();
			o2d->calc();
			o3d->calc();

			//atmosphere->skybox.calc();
			atmosphere->calc();

			Core::sOffset = "";
			std::cout << "}" << std::endl;
			return true;
		}

		void _WorldMap::draw() {
			atmosphere->update(atmosphere->MODE_SATELLITE);
			atmosphere->update(atmosphere->MODE_FLORA);

			// Draw atmosphere
			//atmosphere->skybox.exosphere.draw();

			// Draw Map (After atmosphere, before objects)
			//map->draw(GLS_PHONG);	// TODO: lights for map for GLS_PHONG
//			map->draw(GLS_FONT);
			map->draw(Core::GLS_PHONG, *lights);

			// Draw scenery before satellites to allow occlusion to work
			o2d->draw(Core::GLS_PHONG_O2D, *lights);
			o3d->draw(Core::GLS_PHONG, *lights);

			// Pseudo distance sorting of satellites (only makes sense for two satellites)
//			float fMoonDistActual = (atmosphere->satellite->getPosition("Moon")+atmosphere->satellite->getPosition("Sun")).length();
//			if (fMoonDistActual>atmosphere->satellite->getPosition("Sun").length()) {
//				atmosphere->draw(atmosphere->MODE_SATELLITE, "Moon");	// TODO: [Atmosphere] Add a target setting for satellites? Pointer to any existing object (Vector3f) or create new pointer for fixed position
//				atmosphere->draw(atmosphere->MODE_SATELLITE, "Sun");
//			}
//			else {
//				atmosphere->draw(atmosphere->MODE_SATELLITE, "Sun");
//				atmosphere->draw(atmosphere->MODE_SATELLITE, "Moon");	// TODO: [Atmosphere] Add a target setting for satellites? Pointer to any existing object (Vector3f) or create new pointer for fixed position
//			}

			// Draw after other objects for proper alpha blending
			// TODO: Move Flora to particle emitter class
//			atmosphere->draw(atmosphere->MODE_FLORA, "Flora");
		}
	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_WORLDMAP_H_ */
