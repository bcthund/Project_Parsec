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
#include "../core/Noise.h"
#include "./MapInstance.h"
//#include "O2D.h"
//#include "O3D.h"

/*
 * TODO: WorldMap Punch List
 *
 *  - Noise Class
 *  	- Generic Items
 *  		- Make the noise items in MapData a global class
 *  		- Finish adding extra noise generators
 *  		- Add Turbulence option
 *  		- Add Terrain Blending?
 *
 * 		- Add a mode for layers
 * 			- Add (currently default)
 * 			- Subtract (Gets rid of need to specift negative scale?)
 * 			- Divide
 * 			- Multiply (Can act as a mask)
 *
 *  	- Functions
 *			- Implement function option ([0-1] or [-1 to 1])
 *			- Implement function option (Height for z parameter)
 *			- Implement function (Power, remove from standard params and make a function option)
 *			- Implement function option (Remap Range - Upper [Replace Upper with rescale])
 *			- Implement function option (Remap Range - Lower [Replace Lower with rescale])
 *			- Implement function option (Replace Upper)
 *			- Implement function option (Replace Lower)
 *			- Implement function option (Clamp Upper)
 *			- Implement function option (Clamp Lower)
 *			- Implement function option (Lower Fade - Based on parent height [Will need to be reworked, as layer style allows this to run before or after scaling])
 *				- Fade Distance
 *			- Implement function option (Upper Fade - Based on parent height [Will need to be reworked, as layer style allows this to run before or after scaling])
 *				- Fade Distance
 *			- Implement function option (Scale, remove from standard params and make a function option)
 *			- Implement function option (Cull Above)
 *			- Implement function option (Cull Below)
 *
 *
 *  - Rivers
 *  	- Option 1: Geometry Based
 *  		- Create rivers noise geometry
 *  		- Scale river depth
 *  		- Apply river to primary terrain
 *  			- Store terrain heights for each river vertex
 *  			- Ignore river vertices above threshold
 *  		- Cull and update river geometry
 *  			- Discard vertices not representing riverbed
 *  			- Raise riverbed to water height
 *  			- Apply Terrain height previously recorded
 *  		- Draw water
 *  			- Draw new geometry on top of terrain with water texture
 *
 *  	- Option 2: Texture Based
 *  		- Add a texture override option for noise layer
 *  		- Add a texture index for each vertex (Similar to what will be the moisture layer)
 *  		- Create river noise with water texture override for height range (above, below, both?)
 *  		- Apply river noise to terrain
 *  			- River noise applied to height
 *  			- River override texture applied
 *
 *
 *
 *
 */



namespace Core {
	namespace Sys {

		struct {
			struct s_COMMON {
				const int SCALE_POWER		= 5;
				const int SCALE				= pow(2, SCALE_POWER);
				const int CHUNK_SIZE		= 1024 * SCALE; //32768;//65536; //1024 * SCALE;
//				const int CHUNK_SIZE		= 2048 * SCALE; //32768;//65536; //1024 * SCALE;
				const int VIEW_DISTANCE		= CHUNK_SIZE*16;
//				const int VIEW_DISTANCE		= CHUNK_SIZE*4;
			} GENERIC;

			struct : public s_COMMON {
				const int CHUNK_RESOLUTION	= 8 * SCALE_POWER;
				const float TEXTURE_SCALE	= 10.0f * SCALE_POWER;
				//const float HEIGHT_OFFSET	= -2500.0f;
				const float HEIGHT_OFFSET	= -500.0f;
//				const float DELTA			= 32.0f * SCALE;
				const float DELTA			= CHUNK_SIZE / CHUNK_RESOLUTION;
			} TERRAIN;

			struct : public s_COMMON {
				const int CHUNK_RESOLUTION	= 1;
				const float TEXTURE_SCALE	= 1.0f * SCALE_POWER;
				const float HEIGHT_OFFSET	= 0.0f;
				//const float DELTA			= 32.0f * SCALE;
				const float DELTA			= CHUNK_SIZE / CHUNK_RESOLUTION;
			} WATER;
		} CONST_SIMPLEX;

		/**
		 * @brief Contains the entire definition for the world inclusing atmosphere, lighting, and all map chunks
		 */
		class _World {
			private:

			public:
//				int iViewDistance;
				Atmosphere					atmosphere;
				_Lights						lights;

				t_UMap<std::string, Map::t_ChunkData*> chunkSettings;		///< Layers of chunk settings
				t_UMap<std::string, Noise::t_Noise*> noise;					///< Layers of noise, each can have it's own chunk settings
//				t_UMap<std::string, Map::t_Noise*> terrainNoise;

//				t_UMap<std::string, Map::t_ChunkData*> chunkSettingsWater;
//				t_UMap<std::string, Map::t_Noise*> waterNoise;

				t_UMap<std::string, t_MapInstance*>	map;		///< Index = 0xFFFFFFFF where the first 0xFFFF is the X-grid and the second 0xFFFF is the Y grid
				_World();
				~_World();

				void init();			///< Initialize all members
				void load();			///< Load initial terrain, O2D, and O3D
				void update();			///< Update terrain, O2D and O3D according to chunk status (distance check)
				void draw();			///< Draw all currently defined chunks
		};

		_World::_World() {
			noise.setSource("WorldMap: t_Noise");
			// Default values
			chunkSettings.add("Terrain", new Map::t_ChunkData);
			chunkSettings["Terrain"]->iViewDistance = CONST_SIMPLEX.TERRAIN.VIEW_DISTANCE;
			chunkSettings["Terrain"]->chunk_resolution = CONST_SIMPLEX.TERRAIN.CHUNK_RESOLUTION;
			chunkSettings["Terrain"]->chunk_size = CONST_SIMPLEX.TERRAIN.CHUNK_SIZE;
			chunkSettings["Terrain"]->tex_scale = CONST_SIMPLEX.TERRAIN.TEXTURE_SCALE;
			chunkSettings["Terrain"]->delta = CONST_SIMPLEX.TERRAIN.DELTA;
			chunkSettings["Terrain"]->chunk_height_offset = CONST_SIMPLEX.TERRAIN.HEIGHT_OFFSET;
//			chunkSettings["Terrain"]->sea_level = 0.0f;
			chunkSettings["Terrain"]->set_iMax();

			Noise::t_Noise *newTerrainNoise = new Noise::t_Noise(chunkSettings["Terrain"]);
			noise.add("Terrain", newTerrainNoise);

			chunkSettings.add("Water", new Map::t_ChunkData);
			chunkSettings["Water"]->iViewDistance = CONST_SIMPLEX.WATER.VIEW_DISTANCE;
			chunkSettings["Water"]->chunk_resolution = CONST_SIMPLEX.WATER.CHUNK_RESOLUTION;
			chunkSettings["Water"]->chunk_size = CONST_SIMPLEX.WATER.CHUNK_SIZE;
			chunkSettings["Water"]->tex_scale = CONST_SIMPLEX.WATER.TEXTURE_SCALE;
			chunkSettings["Water"]->delta = CONST_SIMPLEX.WATER.DELTA;
			chunkSettings["Water"]->chunk_height_offset = CONST_SIMPLEX.WATER.HEIGHT_OFFSET;
//			chunkSettings["Water"]->sea_level = 0.0f;
			chunkSettings["Water"]->set_iMax();

			Noise::t_Noise *newWaterNoise = new Noise::t_Noise(chunkSettings["Water"]);
			noise.add("Water", newWaterNoise);
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

			// TODO: Water
//			simplex["Water"]->parent->chunk_resolution			= CONST_SIMPLEX.WATER.CHUNK_RESOLUTION;
//			simplex["Water"]->parent->chunk_size				= CONST_SIMPLEX.WATER.CHUNK_SIZE;
//			simplex["Water"]->parent->tex_scale					= CONST_SIMPLEX.WATER.TEXTURE_SCALE;
//			simplex["Water"]->parent->chunk_height_offset		= CONST_SIMPLEX.WATER.HEIGHT_OFFSET;
//			simplex["Water"]->parent->delta						= CONST_SIMPLEX.WATER.DELTA;
//
//			simplex["Water"]->params.add("Base", Map::t_SimplexParams());
//			simplex["Water"]->params["Base"].frequency			= 0.00013f;
//			simplex["Water"]->params["Base"].amplitude			= 1.0f;
//			simplex["Water"]->params["Base"].lacunarity			= 2.0f;
//			simplex["Water"]->params["Base"].persistance		= 2.0f;
//			simplex["Water"]->params["Base"].power				= 1.0f;
//			simplex["Water"]->params["Base"].scale				= 100.0f;
//			simplex["Water"]->params["Base"].octaves			= 2;

			// River Idea: Create a copy of the world, shift down by a certain amount and draw with water texture
			// Then apply the river layer (ridged noise) to map to expose rivers
			// Only terrain above sea level should be copied
			// Ocean would be generated as flat only where world has ANY points below sea level.
			//	- this can be detected when the map is generated by checking heights

			/*
			 * between certain range
			 *
			 * max(e1 + threshold, 1.0f)
			 *
			 *
			 *
			 */

			// Fractal Borwnian: Mountains/Continents [Simplex Test - Good Continents + Mountains in one shot (Actually Fractal Brownian Noise)]
			Noise::t_Simplex *newSimplex = new Noise::t_Simplex();
			Noise::t_Simplex &layer0 = noise["Terrain"]->add("Layer0", newSimplex);
			layer0.add("Mountains", new Noise::t_SimplexParams());
			//layer0["Mountains"]->frequency			= 0.0000005f;
			layer0["Mountains"]->frequency			= 0.000001f;
			layer0["Mountains"]->amplitude			= 10.0f;
			layer0["Mountains"]->lacunarity			= 2.5f;
			layer0["Mountains"]->persistance		= 0.50f;
			layer0["Mountains"]->power				= 2.5f;
			layer0["Mountains"]->scale				= 200000.0f;
			layer0["Mountains"]->octaves			= 12; //1;
			layer0["Mountains"]->offset				= 2000.0f;

			// TODO: Multiply by noise layer to restrict mountains randomly
			// TODO: Need to add functions for this

			// Ridged-Multi: Peaks
			Noise::t_RidgedPerlin *newRidgedPerlin1 = new Noise::t_RidgedPerlin();
			Noise::t_RidgedPerlin &layer1 = noise["Terrain"]->add("Layer1", newRidgedPerlin1);
			layer1.add("Peaks", new Noise::t_RidgedPerlinParams());
			layer1["Peaks"]->frequency				= 0.00001f;
			layer1["Peaks"]->lacunarity				= 1.5f;
//			layer1["Peaks"]->quality				= noise::QUALITY_BEST;
			layer1["Peaks"]->quality				= noise::QUALITY_STD;
			layer1["Peaks"]->octaves				= 3;
			layer1["Peaks"]->power					= 2.0f;
			layer1["Peaks"]->scale					= 15000.0f;
			layer1["Peaks"]->seed					= 1024.0f;
			layer1["Peaks"]->bRiver					= false;
			layer1["Peaks"]->funcHeightUpperEnable	= false;
			layer1["Peaks"]->funcHeightLowerEnable	= true;
			layer1["Peaks"]->funcHeightUpperValue 	= 30000;
			layer1["Peaks"]->funcHeightLowerValue 	= 8000;

			// Ridged-Multi: Lakes
			Noise::t_RidgedPerlin *newRidgedPerlin4 = new Noise::t_RidgedPerlin();
			Noise::t_RidgedPerlin &layer4 = noise["Terrain"]->add("Layer4", newRidgedPerlin4);
			layer4.add("Underwater", new Noise::t_RidgedPerlinParams());
			layer4["Underwater"]->frequency				= 0.00002f;
			layer4["Underwater"]->lacunarity				= 2.5f;
//			layer4["Underwater"]->quality				= noise::QUALITY_BEST;
			layer4["Underwater"]->quality				= noise::QUALITY_STD;
			layer4["Underwater"]->octaves				= 3;
			layer4["Underwater"]->power					= 2.0f;
			layer4["Underwater"]->scale					= -10000.0f;
			//layer4["Underwater"]->offset				= -1000.0f;
			layer4["Underwater"]->seed					= 911.0f;
			layer4["Underwater"]->funcHeightUpperEnable	= true;
			layer4["Underwater"]->funcHeightLowerEnable	= false;
			layer4["Underwater"]->funcHeightUpperValue 	= 1500;
			layer4["Underwater"]->funcHeightLowerValue 	= 2500;

//			layer1.add("Valleys", new Noise::t_RidgedPerlinParams());
//			layer1["Valleys"]->frequency				= 0.5f;
//			layer1["Valleys"]->lacunarity				= 1.5f;
////			layer1["Valleys"]->quality					= noise::QUALITY_BEST;
//			layer1["Valleys"]->quality					= noise::QUALITY_STD;
//			layer1["Valleys"]->octaves					= 6;
//			layer1["Valleys"]->power					= 2.0f;
//			layer1["Valleys"]->scale					= -2000.0f;
//			layer1["Valleys"]->seed						= 2048.0f;
//			layer1["Valleys"]->bRiver					= false;
//			layer1["Valleys"]->funcHeightUpperEnable	= false;
//			layer1["Valleys"]->funcHeightLowerEnable	= true;
//			layer1["Valleys"]->funcHeightUpperValue		= 20000;
//			layer1["Valleys"]->funcHeightLowerValue 	= 10000;

			// Ridged-Multi: Rivers (Still needs work)
//			layer1.add("Rivers", new Map::t_RidgedPerlinParams());
//			layer1["Rivers"]->frequency				= 0.00002f;
//			layer1["Rivers"]->lacunarity			= 1.5f;
////			layer1["Rivers"]->quality				= noise::QUALITY_BEST;
//			layer1["Rivers"]->quality				= noise::QUALITY_STD;
////			layer1["Rivers"]->quality				= noise::QUALITY_FAST;
//			layer1["Rivers"]->octaves				= 1;
//			layer1["Rivers"]->power					= 10.0f;
//			layer1["Rivers"]->scale					= -40000.0f;
//			layer1["Rivers"]->funcHeightUpperEnable	= true;
//			layer1["Rivers"]->funcHeightLowerEnable	= true;
//			layer1["Rivers"]->funcHeightUpperValue 	= 12000;
//			layer1["Rivers"]->funcHeightLowerValue 	= 500;
//			layer1["Rivers"]->bRiver				= true;



















			// Voronoi Test
//			Map::t_NewVoronoi *newVoronoi = new Map::t_NewVoronoi();
//			Map::t_NewVoronoi &layer3 = noise["Terrain"]->add("Layer3", newVoronoi);
//			layer3.add("Voronoi", new Map::t_VoronoiParams());
//			layer3["Voronoi"]->frequency				= 10.0f;
//			layer3["Voronoi"]->displacement				= 0.0f;
//			layer3["Voronoi"]->bDistance				= true;
//			layer3["Voronoi"]->power					= 2.0f;
//			layer3["Voronoi"]->scale					= 10000.0f;

			// Billow Test
//			Map::t_NewBillow *newBillow = new Map::t_NewBillow();
//			Map::t_NewBillow &layer4 = noise["Terrain"]->add("Layer4", newBillow);
//			layer4.add("Billow", new Map::t_BillowParams());
//			layer4["Billow"]->frequency				= 0.25f;
//			layer4["Billow"]->lacunarity			= 1.5f;
//			layer4["Billow"]->quality				= noise::QUALITY_BEST;
//			layer4["Billow"]->octaves				= 3;
//			layer4["Billow"]->power					= 3.0f;
//			layer4["Billow"]->scale					= 5000.0f;
//			layer4["Billow"]->offset				= 1000.0f;
//			layer4["Billow"]->funcHeightUpperValue 	= 12000;
//			layer4["Billow"]->funcHeightLowerValue 	= 2500;

//			Map::t_NewRidgedPerlin *newRidgedPerlin = new Map::t_NewRidgedPerlin();
//			Map::t_NewRidgedPerlin &layer1 = noise["Terrain"]->add("Layer1", newRidgedPerlin);
//			layer1.add("Peaks", new Map::t_RidgedPerlinParams());
//			layer1["Peaks"]->frequency		= 0.5f;
//			layer1["Peaks"]->lacunarity	= 1.5f;
//			layer1["Peaks"]->quality		= noise::QUALITY_STD;
//			layer1["Peaks"]->octaves		= 3;
//			layer1["Peaks"]->power			= 3.0f;
//			layer1["Peaks"]->scale			= 10000.0f;
//			layer1["Peaks"]->funcHeightEnable = true;
//			layer1["Peaks"]->funcHeightUpperValue = 10000;
//			layer1["Peaks"]->funcHeightLowerValue = 2000;




//			Map::t_NewSimplex *newSimplex2 = new Map::t_NewSimplex();
//			Map::t_NewSimplex &layer2 = noise["Terrain"]->add("Layer2", newSimplex2);
//			layer2.add("Continent", new Map::t_SimplexParams());
//			layer2["Continent"]->frequency		= 0.0000001f;
//			layer2["Continent"]->amplitude		= 1.0f;
//			layer2["Continent"]->lacunarity		= 0.025f;
//			layer2["Continent"]->persistance	= 0.025f;
//			layer2["Continent"]->power			= 3.0f;
//			layer2["Continent"]->scale			= 10000.0f;
//			layer2["Continent"]->octaves		= 1; //1;

			// Perlin Test
//			Map::t_NewPerlin *newPerlin = new Map::t_NewPerlin();
//			Map::t_NewPerlin &layer0 = noise["Terrain"]->add("Layer0", newPerlin);
//			layer0.add("PerlinTest", new Map::t_PerlinParams());
//			layer0["PerlinTest"]->power = 3.6f;
//			layer0["PerlinTest"]->scale = 10000.0f;
//			layer0["PerlinTest"]->addOctave(1.0f,  1);
//			layer0["PerlinTest"]->addOctave(0.48f, 2);
//			layer0["PerlinTest"]->addOctave(0.23f, 4);
//			layer0["PerlinTest"]->addOctave(0.10f, 8);
//			layer0["PerlinTest"]->addOctave(0.04f, 16);
//			layer0["PerlinTest"]->addOctave(0.02f, 32);

//			Map::t_NewPerlin *newPerlin = new Map::t_NewPerlin();
//			Map::t_NewPerlin &layer0 = noise["Terrain"]->add("Layer0", newPerlin);
//			layer0.add("PerlinTest", new Map::t_PerlinParams());
//			layer0["PerlinTest"]->power = 4.0f;
//			layer0["PerlinTest"]->scale = -10000.0f;
//			layer0["PerlinTest"]->addOctave(1.0f,  0.25);

			// Fractal Test - HORRIBLY SLOW, DON'T USE
//			Map::t_NewFractal *newFractal = new Map::t_NewFractal();
//			Map::t_NewFractal &layer0 = noise["Terrain"]->add("Layer0", newFractal);
//			layer0.add("FractalTest", new Map::t_FractalParams());
//			layer0["FractalTest"]->frequency	= 0.00025f;
//			layer0["FractalTest"]->lacunarity	= 2.9f;
//			layer0["FractalTest"]->multiplier	= 0.33f;
//			layer0["FractalTest"]->power		= 1.0f;
//			layer0["FractalTest"]->scale		= 875.0f;
//			layer0["FractalTest"]->layers		= 3;

			// Ridged Test
//			Map::t_NewRidged *newRidged = new Map::t_NewRidged();
//			Map::t_NewRidged &layer0 = noise["Terrain"]->add("Layer0", newRidged);
//			layer0.add("RidgedTest", new Map::t_RidgedParams());
//			layer0["RidgedTest"]->frequency		= 0.00001f;
//			layer0["RidgedTest"]->amplitude		= 100.0f;
//			layer0["RidgedTest"]->lacunarity	= 0.025f;
//			layer0["RidgedTest"]->persistance	= 1.025f;
//			layer0["RidgedTest"]->power			= 3.0f;
//			layer0["RidgedTest"]->scale			= 2000.0f;
//			layer0["RidgedTest"]->octaves		= 1; //1;



			// River Attempt
//			Map::t_NewRidgedSimplex *newRidgedSimplex = new Map::t_NewRidgedSimplex();
//			Map::t_NewRidgedSimplex &layer1 = noise["Terrain"]->add("Layer1", newRidgedSimplex);
//			layer1.add("RiverTest", new Map::t_RidgedSimplexParams());
//			layer1["RiverTest"]->frequency		= 0.000005f;
//			layer1["RiverTest"]->amplitude		= 1.0f;
//			layer1["RiverTest"]->lacunarity		= 1.5250f;
//			layer1["RiverTest"]->persistance	= 0.1f;
//			layer1["RiverTest"]->power			= 20.0f;
//			layer1["RiverTest"]->scale			= -8000.0f;
//			layer1["RiverTest"]->octaves		= 1; //1;
////			layer1["RiverTest"]->threshold		= 1.125f;
//			layer1["RiverTest"]->threshold		= 1.0f;
//			layer1["RiverTest"]->funcHeightEnable = true;
//			layer1["RiverTest"]->funcHeightUpperValue = 8000;
//			layer1["RiverTest"]->funcHeightLowerValue = 2000;


//			// Ridged Test - Better Moutains?
//			Map::t_NewRidgedPerlin *newRidgedPerlin = new Map::t_NewRidgedPerlin();
//			Map::t_NewRidgedPerlin &layer2 = noise["Terrain"]->add("Layer2", newRidgedPerlin);
//			layer2.add("MountainTest", new Map::t_RidgedPerlinParams());
//			layer2["MountainTest"]->power = 3.0f;
//			layer2["MountainTest"]->scale = 10000.0f;
//			layer2["MountainTest"]->addOctave(1.0f,  1);

			// Ridged Test - Better Valleys?
//			layer2.add("ValleyTest", new Map::t_RidgedPerlinParams());
//			layer2["ValleyTest"]->power = 2.0f;
//			layer2["ValleyTest"]->scale = -2000.0f;
//			layer2["ValleyTest"]->addOctave(1.0f,  1);







//			Map::t_NewSimplex *newSimplex = new Map::t_NewSimplex();
//			Map::t_NewSimplex &layer0 = noise["Terrain"]->add("Layer0", newSimplex);
			// EXAMPLE: Map::t_NewSimplex* layer0b = (Map::t_NewSimplex*)(*noise["Terrain"])["Layer0"];
//			layer0.add("Bumpy", new Map::t_SimplexParams());
			// EXMAPLE: noise["Terrain"]->getSimplex("Layer0")["Bumpy"]->frequency = 0.00013f;
//			layer0["Bumpy"]->frequency			= 0.00013f;
//			layer0["Bumpy"]->amplitude			= 1.0f;
//			layer0["Bumpy"]->lacunarity			= 2.0f;
//			layer0["Bumpy"]->persistance		= 2.0f;
//			layer0["Bumpy"]->power				= 3.0f;
//			layer0["Bumpy"]->scale				= 250.0f;
//			layer0["Bumpy"]->octaves			= 4;
//
//			layer0.add("Hills", new Map::t_SimplexParams());
//			layer0["Hills"]->frequency			= 0.00008f;
//			layer0["Hills"]->amplitude			= 2.0f;
//			layer0["Hills"]->lacunarity			= 2.2f;
//			layer0["Hills"]->persistance		= 1.8f;
//			layer0["Hills"]->power				= 3.0f;
//			layer0["Hills"]->scale				= 1000.0f;
//			layer0["Hills"]->octaves			= 2; //2;
//
//			layer0.add("Valleys", new Map::t_SimplexParams());
//			layer0["Valleys"]->frequency		= 0.000005f;
//			layer0["Valleys"]->amplitude		= 5.0f;
//			layer0["Valleys"]->lacunarity		= 1.8f; //2.8f;
//			layer0["Valleys"]->persistance		= -1.0f;
//			layer0["Valleys"]->power			= 3.0f; //3.0f;
//			layer0["Valleys"]->scale			= -500.0f;
//			layer0["Valleys"]->octaves			= 3; //4;

//			layer0.add("Mountain", new Map::t_SimplexParams());
//			layer0["Mountain"]->frequency		= 0.00001f;
//			layer0["Mountain"]->amplitude		= 100.0f;
//			layer0["Mountain"]->lacunarity		= 1.025f;
//			layer0["Mountain"]->persistance		= 0.025f;
//			layer0["Mountain"]->power			= 4.0f;
//			layer0["Mountain"]->scale			= 20000.0f;
//			layer0["Mountain"]->octaves			= 4; //1;

//			Map::t_NewRidged *newRidged = new Map::t_NewRidged();
//			Map::t_NewRidged &layer1 = noise["Terrain"]->add("Layer1", newRidged);
//			layer1.add("Mountain", new Map::t_RidgedParams());
//			layer1["Mountain"]->frequency		= 0.00001f;
//			layer1["Mountain"]->amplitude		= 100.0f;
//			layer1["Mountain"]->lacunarity		= 1.025f;
//			layer1["Mountain"]->persistance		= 0.025f;
//			layer1["Mountain"]->power			= 4.0f;
//			layer1["Mountain"]->scale			= 20000.0f;
//			layer1["Mountain"]->octaves			= 4; //1;

//			layer0.add("Continent", new Map::t_SimplexParams());
//			layer0["Continent"]->frequency		= 0.000001f;
//			layer0["Continent"]->amplitude		= 1.0f;
//			layer0["Continent"]->lacunarity		= 0.025f;
//			layer0["Continent"]->persistance	= 0.025f;
//			layer0["Continent"]->power			= 3.0f;
//			layer0["Continent"]->scale			= 100000.0f;
//			layer0["Continent"]->octaves		= 1; //1;

// Probably not needed
//			Map::t_NewSimplex *newSimplex2 = new Map::t_NewSimplex();
//			Map::t_NewSimplex &layer2 = noise["Terrain"]->add("Layer2", newSimplex2);
//			layer2.add("Continent", new Map::t_SimplexParams());
//			layer2["Continent"]->frequency			= 0.0000005f;
//			layer2["Continent"]->amplitude			= 1.0f;
//			layer2["Continent"]->lacunarity			= 0.025f;
//			layer2["Continent"]->persistance		= 0.025f;
//			layer2["Continent"]->power				= 3.0f;
//			layer2["Continent"]->scale				= 10000.0f;
//			layer2["Continent"]->octaves			= 1; //1;


			chunkSettings["Terrain"]->set_iMax();
			for(int x=-chunkSettings["Terrain"]->iMax; x<chunkSettings["Terrain"]->iMax; x++) {
				for(int z=-chunkSettings["Terrain"]->iMax; z<chunkSettings["Terrain"]->iMax; z++) {

					int dist = std::sqrt((x*x)+(z*z));
					if(dist < chunkSettings["Terrain"]->iMax) {
						std::stringstream ssx, ssz;
						ssx << std::setfill ('0') << std::setw(4);
						ssx << std::hex << (x+32768);

						ssz << std::setfill ('0') << std::setw(4);
						ssz << std::hex << (z+32768);

						std::string mapName = ssx.str() + "_" + ssz.str();

						t_MapInstance *newMap = new t_MapInstance(mapName);		// NOTE: mapName translates into the map offset here
						map.add(mapName, newMap);
						map[mapName]->load(noise["Terrain"], noise["Water"]);
					}
				}
			}

			// TESTING: Change view distance for distance calculation visualization (grass/dirt texture)
//			simplex["Terrain"]->iViewDistance = 1024*8;

		}

		void _World::update() {
			atmosphere.update(atmosphere.MODE_SATELLITE);
//			atmosphere.update(atmosphere.MODE_FLORA);

			chunkSettings["Terrain"]->delta = CONST_SIMPLEX.TERRAIN.DELTA;
			chunkSettings["Terrain"]->set_iMax();	// In case parameters have changed

			// Update distance for all chunks according to players current position
			// Keep track of maps that are outside range and will be removed
			t_Vector1T<std::string> removeMaps;
			for ( auto chunk : map ) {
				chunk.second->update(gameVars->player.active->transform.pos, chunkSettings["Terrain"]->chunk_size);
				chunk.second->bDraw = chunk.second->distance<chunkSettings["Terrain"]->iMax;

				// TODO: Remove chunks beyond visibility
				//	- Start a timer when bDraw active
				//	- If timer expires, then drop chunk (prevents player from turning around needed to reload maps for a limited time)

				if(chunk.second->distance>chunkSettings["Terrain"]->iMax) {
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

					// Check if chunk is already loaded
					if(!map.checkKey(mapName, false)) {
						// Calculate distance from current chunk to new chunk
						float distance = (vB-vA).length();

						// Check if new chunk is in valid range
						if(distance < chunkSettings["Terrain"]->iMax) {
							// Load new chunk
							t_MapInstance *newMap = new t_MapInstance(mapName);		// NOTE: mapName translates into the map offset here
							map.add(mapName, newMap);
							map[mapName]->load(noise["Terrain"], noise["Water"]);
						}
					}
				}
			}




		}

		void _World::draw() {
			atmosphere.skybox.exosphere.draw();


			// Pseudo distance sorting of satellites (only makes sense for two satellites)
			float fMoonDistActual = (atmosphere.satellite->getPosition("Moon")+atmosphere.satellite->getPosition("Sun")).length();
			if (fMoonDistActual>atmosphere.satellite->getPosition("Sun").length()) {
				atmosphere.draw(atmosphere.MODE_SATELLITE, "Moon");	// TODO: [Atmosphere] Add a target setting for satellites? Pointer to any existing object (Vector3f) or create new pointer for fixed position
				atmosphere.draw(atmosphere.MODE_SATELLITE, "Sun");
			}
			else {
				atmosphere.draw(atmosphere.MODE_SATELLITE, "Sun");
				atmosphere.draw(atmosphere.MODE_SATELLITE, "Moon");	// TODO: [Atmosphere] Add a target setting for satellites? Pointer to any existing object (Vector3f) or create new pointer for fixed position
			}


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
			Core::sysTex->set(Core::sysTex->TEX_BEACH1);

			glActiveTexture(GL_TEXTURE13);
			Core::sysTex->set(Core::sysTex->TEX_BEACH2);

			glActiveTexture(GL_TEXTURE14);
			Core::sysTex->set(Core::sysTex->TEX_SAND1);

			glActiveTexture(GL_TEXTURE15);
			Core::sysTex->set(Core::sysTex->TEX_SAND2);

			glActiveTexture(GL_TEXTURE31);
			Core::sysTex->set(Core::sysTex->TEX_WATER);

			glDisable(GL_CULL_FACE);
			Core::matrix->Push();
				// Move chunk according to player
				matrix->Rotate(Core::gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
				matrix->Rotate(Core::gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
				matrix->Translate(Core::gameVars->player.active->transform.pos[0]-(chunkSettings["Terrain"]->chunk_size/2),
								  Core::gameVars->player.active->transform.pos[1],
								  Core::gameVars->player.active->transform.pos[2]-(chunkSettings["Terrain"]->chunk_size/2));

				// Move chunk into place (Do in loader so lighting works easily)
				Core::matrix->Scale(1*Core::gameVars->screen.fScale, 1*Core::gameVars->screen.fScale, 1*Core::gameVars->screen.fScale);

				float fPreScale = chunkSettings["Terrain"]->chunk_size*Core::gameVars->screen.fScale;

				for ( auto chunk : map ) {
//					if(chunk.second->bDraw) {	// Will hide terrain outside view range
						Core::matrix->Push();

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
			glEnable(GL_CULL_FACE);
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
