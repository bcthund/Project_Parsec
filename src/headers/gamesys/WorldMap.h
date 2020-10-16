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
 *	- Fix Shaders getUniform function
 *		- glGetUniformLocation is an expensive function, two options to fix
 *		- update
 *			- Create an "updateUniform" function
 *			- Only most important variables are set, textures are not for example
 *		- uniform struct
 *			- Create a uniform struct that holds ids
 *			- Set the location ids in the struct by passing to getUniform()
 *			- Set the data with a setUniform() method that only makes calls to glUniform{1|2|3|4}{f|i|ui}v
 *
 *	- Moisture
 *		- Create 3-6 3D textures for levels of dry to wet
 *		- Moisture data translates into moisture level
 *			- Scale by number of levels
 *			- Value determines the current biome as well as fade to other biomes
 *			- ex: 3.5 would be biome 3, 3.8 would be biome 3 fading into biome 4
 *			- Each 3D texture for a biome is an array of textures for elevation
 */



namespace Core {
	namespace Sys {

		struct {
			struct s_COMMON {
				const int SCALE_POWER		= 5;
				const int SCALE				= pow(2, SCALE_POWER);
				const int CHUNK_SIZE		= 1024 * SCALE; //32768;//65536; //1024 * SCALE;
//				const int CHUNK_SIZE		= 2048 * SCALE; //32768;//65536; //1024 * SCALE;
//				const int VIEW_DISTANCE		= CHUNK_SIZE*16;
				const int VIEW_DISTANCE		= CHUNK_SIZE*8;
			} GENERIC;

			struct : public s_COMMON {
				const int CHUNK_RESOLUTION	= 8 * SCALE_POWER;
				const float TEXTURE_SCALE	= 20.0f * SCALE_POWER;
				//const float HEIGHT_OFFSET	= -2500.0f;
				const float HEIGHT_OFFSET	= -500.0f;
//				const float DELTA			= 32.0f * SCALE;
				const float DELTA			= CHUNK_SIZE / CHUNK_RESOLUTION;
			} TERRAIN;

			struct : public s_COMMON {
				const int CHUNK_RESOLUTION	= 1;
				const float TEXTURE_SCALE	= 10.0f * SCALE_POWER;
				const float HEIGHT_OFFSET	= 0.0f;
				//const float DELTA			= 32.0f * SCALE;
				const float DELTA			= CHUNK_SIZE / CHUNK_RESOLUTION;
			} WATER;

			struct : public s_COMMON {
				const int CHUNK_RESOLUTION	= 64 * SCALE_POWER;
				const float TEXTURE_SCALE	= 1.0f * SCALE_POWER;
				const float HEIGHT_OFFSET	= 0.0f;
//				const float DELTA			= 32.0f * SCALE;
				const float DELTA			= CHUNK_SIZE / CHUNK_RESOLUTION;
			} TREES;
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

				// Noise needs chunkSettings pointer to implement
				struct t_LayerData {
					t_UniformLocations* uniforms;
					Map::t_ChunkData* chunkSettings;
					Noise::t_Noise*	noise;
					t_LayerData() {
						uniforms = new t_UniformLocations();
						chunkSettings = new Map::t_ChunkData();
						noise = new Noise::t_Noise(chunkSettings);
					}

					t_LayerData(Map::t_ChunkData* chunkSettingsPtr) {
						uniforms = new t_UniformLocations();
						chunkSettings = chunkSettingsPtr;
						noise = new Noise::t_Noise(chunkSettings);
					}
				};
				t_UMap<std::string, t_LayerData*> data;

//				t_UMap<std::string, t_UniformLocations> uniforms;

//				t_UMap<std::string, Map::t_ChunkData*> chunkSettings;		///< Layers of chunk settings
//				t_UMap<std::string, Noise::t_Noise*> noise;					///< Layers of noise, each can have it's own chunk settings
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
//			noise.setSource("WorldMap: t_Noise");

			{
				t_LayerData *newData = new t_LayerData();
				data.add("Terrain", newData);
				data["Terrain"]->chunkSettings->iViewDistance = CONST_SIMPLEX.TERRAIN.VIEW_DISTANCE;
				data["Terrain"]->chunkSettings->chunk_resolution = CONST_SIMPLEX.TERRAIN.CHUNK_RESOLUTION;
				data["Terrain"]->chunkSettings->chunk_size = CONST_SIMPLEX.TERRAIN.CHUNK_SIZE;
				data["Terrain"]->chunkSettings->tex_scale = CONST_SIMPLEX.TERRAIN.TEXTURE_SCALE;
				data["Terrain"]->chunkSettings->delta = CONST_SIMPLEX.TERRAIN.DELTA;
				data["Terrain"]->chunkSettings->chunk_height_offset = CONST_SIMPLEX.TERRAIN.HEIGHT_OFFSET;
				data["Terrain"]->chunkSettings->set_iMax();

				data.add("Moisture", new t_LayerData(data["Terrain"]->chunkSettings));
				data.add("Altitude", new t_LayerData(data["Terrain"]->chunkSettings));
//				data.add("Trees", new t_LayerData(data["Terrain"]->chunkSettings));
			}
//			{
//				t_LayerData *newData = new t_LayerData(data["Terrain"]->chunkSettings);
//				data.add("Moisture", newData);
//			}
//			{
//				t_LayerData *newData = new t_LayerData(data["Terrain"]->chunkSettings);
//				data.add("Altitude", newData);
//			}
//			{
//				t_LayerData *newData = new t_LayerData(data["Terrain"]->chunkSettings);
//				data.add("Trees", newData);
//			}
			{
				t_LayerData *newData = new t_LayerData();
				data.add("Trees", newData);
				data["Trees"]->chunkSettings->iViewDistance = CONST_SIMPLEX.TREES.VIEW_DISTANCE;
				data["Trees"]->chunkSettings->chunk_resolution = CONST_SIMPLEX.TREES.CHUNK_RESOLUTION;
				data["Trees"]->chunkSettings->chunk_size = CONST_SIMPLEX.TREES.CHUNK_SIZE;
				data["Trees"]->chunkSettings->tex_scale = CONST_SIMPLEX.TREES.TEXTURE_SCALE;
				data["Trees"]->chunkSettings->delta = CONST_SIMPLEX.TREES.DELTA;
				data["Trees"]->chunkSettings->chunk_height_offset = CONST_SIMPLEX.TREES.HEIGHT_OFFSET;
				data["Trees"]->chunkSettings->set_iMax();
			}
			{
				t_LayerData *newData = new t_LayerData();
				data.add("Water", newData);
				data["Water"]->chunkSettings->iViewDistance = CONST_SIMPLEX.WATER.VIEW_DISTANCE;
				data["Water"]->chunkSettings->chunk_resolution = CONST_SIMPLEX.WATER.CHUNK_RESOLUTION;
				data["Water"]->chunkSettings->chunk_size = CONST_SIMPLEX.WATER.CHUNK_SIZE;
				data["Water"]->chunkSettings->tex_scale = CONST_SIMPLEX.WATER.TEXTURE_SCALE;
				data["Water"]->chunkSettings->delta = CONST_SIMPLEX.WATER.DELTA;
				data["Water"]->chunkSettings->chunk_height_offset = CONST_SIMPLEX.WATER.HEIGHT_OFFSET;
				data["Water"]->chunkSettings->set_iMax();
			}
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
			Core::debug.glErrorCheck("WorldMap", 250);
			atmosphere.calc();
			Core::debug.glErrorCheck("WorldMap", 252);

			lights.load();
			Core::debug.glErrorCheck("WorldMap", 255);
			lights.calc(Core::gameVars->screen.fScale);
			Core::debug.glErrorCheck("WorldMap", 257);

			// River Idea: Create a copy of the world, shift down by a certain amount and draw with water texture
			// Then apply the river layer (ridged noise) to map to expose rivers
			// Only terrain above sea level should be copied
			// Ocean would be generated as flat only where world has ANY points below sea level.

			// [YES] Fractal Borwnian: Mountains/Continents [Simplex Test - Good Continents + Mountains in one shot (Actually Fractal Brownian Noise)]
			Noise::t_Fractal *newFractal0 = new Noise::t_Fractal();
			Noise::t_Fractal &layer0 = data["Terrain"]->noise->add("Layer0", newFractal0);
			layer0.add("Mountains", new Noise::t_FractalParams());
			layer0["Mountains"]->frequency			= 0.000001f;
			layer0["Mountains"]->amplitude			= 1.0f;
			layer0["Mountains"]->lacunarity			= 2.5f;
			layer0["Mountains"]->persistence		= 0.50f;
			layer0["Mountains"]->octaves			= 12;
//			layer0["Mountains"]->octaves			= 1;layer0["Mountains"]->octaves			= 12;
			layer0["Mountains"]->seed				= 100;
			layer0["Mountains"]->AddFunction.Power(2.5f);
			layer0["Mountains"]->AddFunction.RemapBelow(0.0f, -10.0f, 0.0f, -1.0f, 0.0f);				// Underwater terrain gets scaled to offset multiply layer
			layer0["Mountains"]->AddFunction.RemapBelow(-0.5f, -2.5f, -0.5f, -10.0f, -0.5f);		// Underwater terrain gets scaled to offset multiply layer
			layer0["Mountains"]->AddFunction.Scale(300000.0f);
			layer0["Mountains"]->AddFunction.Offset(5000.0f);

			// [YES] Ridged-Multi: Peaks
			Noise::t_RidgedPerlin *newRidgedPerlin1 = new Noise::t_RidgedPerlin();
			Noise::t_RidgedPerlin &layer1 = data["Terrain"]->noise->add("Layer1", newRidgedPerlin1);
			layer1.add("Peaks", new Noise::t_RidgedPerlinParams());
			layer1["Peaks"]->frequency				= 0.00001f;
			layer1["Peaks"]->lacunarity				= 1.5f;
//			layer1["Peaks"]->quality				= noise::QUALITY_BEST;
			layer1["Peaks"]->quality				= noise::QUALITY_STD;
//			layer1["Peaks"]->quality				= noise::QUALITY_FAST;
			layer1["Peaks"]->octaves				= 3;
			layer1["Peaks"]->seed					= 1024.0f;
			layer1["Peaks"]->AddFunction.Power(2.0f);
			layer1["Peaks"]->AddFunction.Remap(0.0f, 1.0f);
			layer1["Peaks"]->AddFunction.FadeBelow(10000.0f, 12000.0f, 1.0f, true);	// Ridges fade down to sea level
			layer1["Peaks"]->AddFunction.FadeAbove(55000.0f, 10000.0f, 1.0f, true);	// Ridges only go so high in mountains, prevents obscene peaks
			layer1["Peaks"]->AddFunction.Scale(10000.0f);

			// [YES] Multiply by layer, but do not touch underwater layer
			Noise::t_Perlin *newPerlin = new Noise::t_Perlin();
			Noise::t_Perlin &layer2 = data["Terrain"]->noise->add("Layer2", newPerlin);
			layer2.add("Continent", new Noise::t_PerlinParams());
			layer2["Continent"]->mode					= Noise::MODE_MULTIPLY;
			layer2["Continent"]->seed					= 4096.0f;
			layer2["Continent"]->frequency				= 0.000001f;
			layer2["Continent"]->lacunarity				= 2.5f;
			layer2["Continent"]->persistence			= 0.5f;
			layer2["Continent"]->quality				= noise::QUALITY_FAST;
			layer2["Continent"]->octaves				= 1;
			layer2["Continent"]->AddFunction.Remap(0.0f, 1.0f, -1.0f, 1.0f);	// Modify previous layers by 25-100%

			// [NO] Ridged-Multi: Lakes
//			Noise::t_RidgedPerlin *newRidgedPerlin4 = new Noise::t_RidgedPerlin();
//			Noise::t_RidgedPerlin &layer3 = noise["Terrain"]->add("Layer3", newRidgedPerlin4);
//			layer3.add("Underwater", new Noise::t_RidgedPerlinParams());
//			layer3["Underwater"]->frequency				= 0.00002f;
//			layer3["Underwater"]->lacunarity			= 2.5f;
////			layer3["Underwater"]->quality				= noise::QUALITY_BEST;
//			layer3["Underwater"]->quality				= noise::QUALITY_STD;
//			layer3["Underwater"]->octaves				= 3;
//			layer3["Underwater"]->seed					= 911.0f;
//			layer3["Underwater"]->AddFunction.Power(2.0f);
//			layer3["Underwater"]->AddFunction.FadeAbove(-1000.0f, 2500.0f, 1.0f, true);
//			layer3["Underwater"]->AddFunction.Scale(-10000.0f);

			// Moisture
			Noise::t_Fractal *newFractal1 = new Noise::t_Fractal();
			Noise::t_Fractal &layer4 = data["Moisture"]->noise->add("Layer4", newFractal1);
			layer4.add("Moisture", new Noise::t_FractalParams());
			layer4["Moisture"]->frequency		= 0.000001f;
//			layer4["Moisture"]->frequency		= 0.0001f;
			layer4["Moisture"]->amplitude		= 1.0f;
			layer4["Moisture"]->lacunarity		= 1.5f;
			layer4["Moisture"]->persistence		= 0.250f;
			layer4["Moisture"]->octaves			= 2;
			layer4["Moisture"]->seed				= 1;
			layer4["Moisture"]->AddFunction.Remap(-0.125f, 1.0f, -1.0f, 1.0f);
			layer4["Moisture"]->AddFunction.Scale(5.0f);

			// Altitude Offset Layer for Texturing
//			Noise::t_RidgedPerlin *newAltitude = new Noise::t_RidgedPerlin();
//			Noise::t_RidgedPerlin &layer5 = data["Altitude"]->noise->add("Layer5", newAltitude);
//			layer5.add("Altitude", new Noise::t_RidgedPerlinParams());
//			layer5["Altitude"]->frequency		= 0.00001f;
//			layer5["Altitude"]->lacunarity		= 2.5f;
//			layer5["Altitude"]->quality			= noise::QUALITY_STD;
//			layer5["Altitude"]->octaves			= 4;
//			layer5["Altitude"]->seed			= 222;
//			layer5["Altitude"]->AddFunction.Power(2.0f);
//			layer5["Altitude"]->AddFunction.Remap(0.0f, 0.5f, -1.0f, 1.0f);
////			layer5["Altitude"]->AddFunction.Remap(0.0f, 1.0f, -1.0f, 1.0f);
////			layer5["Altitude"]->AddFunction.Scale(5.0f);

			// TODO: Tree Placement
			Noise::t_Fractal *newTreeNoise = new Noise::t_Fractal();
			Noise::t_Fractal &layer6 = data["Trees"]->noise->add("Layer6", newTreeNoise);
			layer6.add("Trees", new Noise::t_FractalParams());
			layer6["Trees"]->frequency		= 0.01f;
			layer6["Trees"]->amplitude		= 1.0f;
			layer6["Trees"]->lacunarity		= 1.5f;
			layer6["Trees"]->persistence	= 0.250f;
			layer6["Trees"]->octaves		= 2;
			layer6["Trees"]->seed			= 1;
			//layer6["Trees"]->AddFunction.Remap(-0.125f, 1.0f, -1.0f, 1.0f);
			//layer6["Trees"]->AddFunction.Scale(5.0f);


			// [NO] Ridged-Multi: Rivers (Still needs work)
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


			// [NO] Perlin Test
//			Noise::t_Perlin *newPerlin = new Noise::t_Perlin();
//			Noise::t_Perlin &layer0 = noise["Terrain"]->add("Layer0", newPerlin);
//			layer0.add("PerlinTest", new Noise::t_PerlinParams());
//			layer0["PerlinTest"]->seed				= 42.0f;
//			layer0["PerlinTest"]->frequency			= 0.00000001f;
//			layer0["PerlinTest"]->lacunarity		= 2.5f;
//			layer0["PerlinTest"]->quality			= noise::QUALITY_STD;
//			layer0["PerlinTest"]->octaves			= 6;
//			layer0["PerlinTest"]->persistance		= 1.75f;
//			layer0["PerlinTest"]->AddFunction.Power(2.0f);
//			layer0["PerlinTest"]->AddFunction.Scale(1000.0f);

			// [NO] Voronoi Test
//			Noise::t_Voronoi *newVoronoi = new Noise::t_Voronoi();
//			Noise::t_Voronoi &layer3 = noise["Terrain"]->add("Layer3", newVoronoi);
//			layer3.add("Voronoi", new Noise::t_VoronoiParams());
//			layer3["Voronoi"]->seed						= 420.0f;
//			layer3["Voronoi"]->frequency				= 0.0001f;
//			layer3["Voronoi"]->displacement				= 0.0f;
//			layer3["Voronoi"]->bDistance				= true;
//			layer3["Voronoi"]->AddFunction.Power(2.0f);
//			layer3["Voronoi"]->AddFunction.Scale(1000.0f);

			// [NO] Billow Test
//			Noise::t_Billow *newBillow = new Noise::t_Billow();
//			Noise::t_Billow &layer4 = noise["Terrain"]->add("Layer4", newBillow);
//			layer4.add("Billow", new Noise::t_BillowParams());
//			layer4["Billow"]->seed					= 4096.0f;
//			layer4["Billow"]->frequency				= 0.000025f;
//			layer4["Billow"]->lacunarity			= 1.5f;
//			layer4["Billow"]->persistence			= 1.5f;
//			layer4["Billow"]->quality				= noise::QUALITY_BEST;
//			layer4["Billow"]->octaves				= 3;
//			layer4["Billow"]->AddFunction.Power(3.0f);
//			layer4["Billow"]->AddFunction.Scale(100.0f);
//			layer4["Billow"]->AddFunction.Offset(1000.0f);


			data["Terrain"]->chunkSettings->set_iMax();
			for(int x=-data["Terrain"]->chunkSettings->iMax; x<data["Terrain"]->chunkSettings->iMax; x++) {
				for(int z=-data["Terrain"]->chunkSettings->iMax; z<data["Terrain"]->chunkSettings->iMax; z++) {

					int dist = std::sqrt((x*x)+(z*z));
					if(dist < data["Terrain"]->chunkSettings->iMax) {
						std::stringstream ssx, ssz;
						ssx << std::setfill ('0') << std::setw(4);
						ssx << std::hex << (x+32768);

						ssz << std::setfill ('0') << std::setw(4);
						ssz << std::hex << (z+32768);

						std::string mapName = ssx.str() + "_" + ssz.str();

						t_MapInstance *newMap = new t_MapInstance(mapName);		// NOTE: mapName translates into the map offset here
						map.add(mapName, newMap);
						map[mapName]->load(data["Terrain"]->noise, data["Water"]->noise, data["Moisture"]->noise, data["Altitude"]->noise, data["Trees"]->noise);
//						map[mapName]->load(data["Terrain"]->noise, data["Water"]->noise, data["Moisture"]->noise, data["Altitude"]->noise, nullptr);
					}
				}
			}

			// TESTING: Change view distance for distance calculation visualization (grass/dirt texture)
//			simplex["Terrain"]->iViewDistance = 1024*8;

		}

		void _World::update() {
			atmosphere.update(atmosphere.MODE_SATELLITE);
//			atmosphere.update(atmosphere.MODE_FLORA);

			data["Terrain"]->chunkSettings->delta = CONST_SIMPLEX.TERRAIN.DELTA;
			data["Terrain"]->chunkSettings->set_iMax();	// In case parameters have changed

			// Update distance for all chunks according to players current position
			// Keep track of maps that are outside range and will be removed
			t_Vector1T<std::string> removeMaps;
			for ( auto chunk : map ) {
				chunk.second->update(gameVars->player.active->transform.pos, data["Terrain"]->chunkSettings->chunk_size);
				chunk.second->bDraw = chunk.second->distance<data["Terrain"]->chunkSettings->iMax;

				// TODO: Remove chunks beyond visibility
				//	- Start a timer when bDraw active
				//	- If timer expires, then drop chunk (prevents player from turning around needed to reload maps for a limited time)

				if(chunk.second->distance>data["Terrain"]->chunkSettings->iMax) {
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
			for(int x=-data["Terrain"]->chunkSettings->iMax; x<data["Terrain"]->chunkSettings->iMax; x++) {
				for(int z=-data["Terrain"]->chunkSettings->iMax; z<data["Terrain"]->chunkSettings->iMax; z++) {
					// Get players current chunk
					Vector2f vA;
					vA.x = -gameVars->player.active->transform.pos.x/data["Terrain"]->chunkSettings->chunk_size;
					vA.y = -gameVars->player.active->transform.pos.z/data["Terrain"]->chunkSettings->chunk_size;

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
						if(distance < data["Terrain"]->chunkSettings->iMax) {
							// Load new chunk
							t_MapInstance *newMap = new t_MapInstance(mapName);		// NOTE: mapName translates into the map offset here
							map.add(mapName, newMap);
							map[mapName]->load(data["Terrain"]->noise, data["Water"]->noise, data["Moisture"]->noise, data["Altitude"]->noise, data["Trees"]->noise);
//							map[mapName]->load(data["Terrain"]->noise, data["Water"]->noise, data["Moisture"]->noise, data["Altitude"]->noise, nullptr);
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
			glEnable(GL_TEXTURE_3D);

//			glActiveTexture(GL_TEXTURE0);
//			Core::sysTex->set(Core::sysTex->TEX_DIRT1);
//
//			glActiveTexture(GL_TEXTURE1);
//			Core::sysTex->set(Core::sysTex->TEX_DIRT2);
//
//			glActiveTexture(GL_TEXTURE2);
//			Core::sysTex->set(Core::sysTex->TEX_GRASS1);
//
//			glActiveTexture(GL_TEXTURE3);
//			Core::sysTex->set(Core::sysTex->TEX_GRASS2);
//
//			glActiveTexture(GL_TEXTURE4);
//			Core::sysTex->set(Core::sysTex->TEX_ROCKY1);
//
//			glActiveTexture(GL_TEXTURE5);
//			Core::sysTex->set(Core::sysTex->TEX_ROCKY2);
//
//			glActiveTexture(GL_TEXTURE6);
//			Core::sysTex->set(Core::sysTex->TEX_CLIFF1);
//
//			glActiveTexture(GL_TEXTURE7);
//			Core::sysTex->set(Core::sysTex->TEX_CLIFF2);
//
//			glActiveTexture(GL_TEXTURE8);
//			Core::sysTex->set(Core::sysTex->TEX_MUD1);
//
//			glActiveTexture(GL_TEXTURE9);
//			Core::sysTex->set(Core::sysTex->TEX_MUD2);
//
//			glActiveTexture(GL_TEXTURE10);
//			Core::sysTex->set(Core::sysTex->TEX_SNOW1);
//
//			glActiveTexture(GL_TEXTURE11);
//			Core::sysTex->set(Core::sysTex->TEX_SNOW2);
//
//			glActiveTexture(GL_TEXTURE12);
//			Core::sysTex->set(Core::sysTex->TEX_BEACH1);
//
//			glActiveTexture(GL_TEXTURE13);
//			Core::sysTex->set(Core::sysTex->TEX_BEACH2);
//
//			glActiveTexture(GL_TEXTURE14);
//			Core::sysTex->set(Core::sysTex->TEX_SAND1);
//
//			glActiveTexture(GL_TEXTURE15);
//			Core::sysTex->set(Core::sysTex->TEX_SAND2);

			glActiveTexture(GL_TEXTURE0);
			Core::sysTex->set(Core::sysTex->TEX_3D);

			glActiveTexture(GL_TEXTURE1);
			Core::sysTex->set(Core::sysTex->TEX_3D+1);

			glActiveTexture(GL_TEXTURE2);
			Core::sysTex->set(Core::sysTex->TEX_3D+2);

			glActiveTexture(GL_TEXTURE3);
			Core::sysTex->set(Core::sysTex->TEX_3D+3);

			glActiveTexture(GL_TEXTURE4);
			Core::sysTex->set(Core::sysTex->TEX_3D+4);

//			glActiveTexture(GL_TEXTURE29);
//			Core::sysTex->set(Core::sysTex->TEX_ATLAS_00);
//
//			glActiveTexture(GL_TEXTURE30);
//			Core::sysTex->set(Core::sysTex->TEX_MOISTURE2);
//
			glActiveTexture(GL_TEXTURE31);
			Core::sysTex->set(Core::sysTex->TEX_WATER);

			shader->use(Core::GLS_PHONG);
			shader->getUniform(Core::GLS_PHONG, lights, *data["Terrain"]->uniforms);
			shader->getUniform(Core::GLS_WATER, lights, *data["Water"]->uniforms);

			glDisable(GL_CULL_FACE);
			Core::matrix->Push();
				// Move chunk according to player
				matrix->Rotate(Core::gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
				matrix->Rotate(Core::gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
				matrix->Translate(Core::gameVars->player.active->transform.pos[0]-(data["Terrain"]->chunkSettings->chunk_size/2),
								  Core::gameVars->player.active->transform.pos[1],
								  Core::gameVars->player.active->transform.pos[2]-(data["Terrain"]->chunkSettings->chunk_size/2));

				// Move chunk into place (Do in loader so lighting works easily)
				Core::matrix->Scale(1*Core::gameVars->screen.fScale, 1*Core::gameVars->screen.fScale, 1*Core::gameVars->screen.fScale);

				float fPreScale = data["Terrain"]->chunkSettings->chunk_size*Core::gameVars->screen.fScale;

//				shader->use(Core::GLS_PHONG);
//				shader->getUniform(Core::GLS_PHONG, &lights);

				for ( auto const &chunk : map ) {
//					if(chunk.second->bDraw) {	// Will hide terrain outside view range
						Core::matrix->Push();

							// TODO: Pass this to shader, translating here causes issues with lights repeating
							int iX = chunk.second->x-32768;
							int iZ = chunk.second->z-32768;
							matrix->Translate(	iX*fPreScale,
												0.0f,
												iZ*fPreScale);


							matrix->SetTransform();
//							shader->use(Core::GLS_PHONG);
//							shader->getUniform(Core::GLS_PHONG, &lights);
							shader->setUniform(Core::GLS_PHONG, lights, *data["Terrain"]->uniforms);
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

//				shader->use(Core::GLS_WATER);
//				shader->getUniform(Core::GLS_WATER, &lights);

				for ( auto const &chunk : map ) {
						Core::matrix->Push();
							int iX = chunk.second->x-32768;
							int iZ = chunk.second->z-32768;
							matrix->Translate(	iX*fPreScale,
												0.0f,
												iZ*fPreScale);

							matrix->SetTransform();
//							shader->use(Core::GLS_WATER);
//							shader->getUniform(Core::GLS_WATER, &lights);
							shader->setUniform(Core::GLS_WATER, lights, *data["Water"]->uniforms);
							chunk.second->drawWater();
						Core::matrix->Pop();
				}
			Core::matrix->Pop();
			glEnable(GL_CULL_FACE);
			glDisable(GL_TEXTURE_3D);
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
