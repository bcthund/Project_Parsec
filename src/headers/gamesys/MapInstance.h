/*
 * MapInstance.h
 *
 *  Created on: Sep 20, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_MAPINSTANCE_H_
#define HEADERS_GAMESYS_MAPINSTANCE_H_

#include "../core/types.h"
#include "../core/core_functions.h"
//#include "./O2D.h"
#include "./O2D_Data.h"
#include "./O3D.h"
#include "./MapData.h"
#include "../core/Noise.h"

namespace Core {
	namespace Sys {

		/**
		 * @brief Defines all the components in a single map Chunk
		 *
		 */
		class t_MapInstance {
			private:
//				t_Vector1T<Map::Simplex> *simplex;

			public:
				unsigned int x, z;		///< Used to determine distance and load O2D, O3D, etc.
				float		 distance;
				bool		 bDraw;		///< Controls drawing according to distance value
//				static MapSys mapSys;

//				void load(Map::Simplex *simplex, Map::Simplex *simplexWater);
//				void load(Map::t_Simplex *noise);
//				void load(Map::t_Perlin *noise);
//				void load(Map::t_Fractal *noise);
//				void load(Map::t_Ridged *noise);
				void load(Core::Noise::t_Noise *terrainNoise,
						  Core::Noise::t_Noise *waterNoise,
						  Core::Noise::t_Noise *moistureNoise,
						  Core::Noise::t_Noise *altitudeNoise,
						  Core::Noise::t_Noise *treeNoise);
				void setOffset(std::string offset);
				float update(Vector3f a=Vector3f(0.0f), int terrain_size=1);	///< Perform updates to chunk data and return current chunk distance
//				void load(std::string offset, Map::Simplex *simplex, Map::Simplex *simplexWater);
//				void load(std::string offset, Map::t_Simplex *noise);
//				void load(std::string offset, Map::t_Perlin  *noise);
//				void load(std::string offset, Map::t_Fractal *noise);
//				void load(std::string offset, Map::t_Ridged  *noise);
				void load(	std::string offset,
							Core::Noise::t_Noise *terrainNoise,
							Core::Noise::t_Noise *waterNoise,
							Core::Noise::t_Noise *moistureNoise,
							Core::Noise::t_Noise *altitudeNoise,
							Core::Noise::t_Noise *treeNoise);
				void drawTerrain();
				void drawWater();
				void drawO2D(Vector3f &vCamPos, _Lights &lights, t_UniformLocations &uniforms);

				struct t_TerrainInterface {
					t_MapInstance * parent;
					Map::Data	data;
//					void draw(Core::SHADER_PROGRAMS iShader);
					t_TerrainInterface(t_MapInstance * p) { parent = p; }
				};
				t_TerrainInterface Terrain = t_TerrainInterface(this);

				struct t_WaterInterface {
					t_MapInstance * parent;
					Map::Data	data;
//					void draw(Core::SHADER_PROGRAMS iShader);
					t_WaterInterface(t_MapInstance * p) { parent = p; }
				};
				t_TerrainInterface Water = t_TerrainInterface(this);

				struct t_O2DInterface {
					t_MapInstance * parent;
					O2D::Data data;		// TODO: Delete pointers
					t_O2DInterface(t_MapInstance * p) { parent = p; }
				};
				t_O2DInterface O2D = t_O2DInterface(this);

				struct t_O3DInterface {
					t_MapInstance * parent;
					_O3DData data;
					t_O3DInterface(t_MapInstance * p) { parent = p; }
				};
				t_O3DInterface O3D = t_O3DInterface(this);

				t_MapInstance();
				t_MapInstance(std::string offset);
				~t_MapInstance();
		};

		t_MapInstance::t_MapInstance() {
			x = 0;
			z = 0;
			distance = 0;
			bDraw = true;
		}

		t_MapInstance::t_MapInstance(std::string offset) {
			x = 0;
			z = 0;
			setOffset(offset);
//			calcDistance();
		}

		t_MapInstance::~t_MapInstance() {
		}

		void t_MapInstance::setOffset(std::string offset) {
//			debug.log("Setting Map Offset: ");
			std::stringstream ssx;
			ssx << std::hex << offset.substr(0, 4);
			ssx >> x;
//			debug.print(ssx.str()+", ");

			std::stringstream ssz;
			ssz << std::hex << offset.substr(5, 4);
			ssz >> z;

			update();
//			debug.print(ssz.str()+"\n");
		}

		// when a=[0,0], player is at starting position
		float t_MapInstance::update(Vector3f pos, int terrain_size) {
			// Convert player coords to grid chunks
			Vector2f vA;
			vA.x = -pos.x/terrain_size;
			vA.y = -pos.z/terrain_size;

			// Rounding
			if(vA.x<0) vA.x-=1.0f; else vA.x+=1.0f;
			if(vA.y<0) vA.y-=1.0f; else vA.y+=1.0f;

			// Calculate distance in grid chunks
			Vector2f vB;
			vB.x = int(x-32768);
			vB.y = int(z-32768);
			distance = (vB-vA).length();
//			debug.log(std::to_string(distance)+" ["+std::to_string(aX)+", "+std::to_string(aZ)+"] ["+std::to_string(bX)+", "+std::to_string(bZ)+"]\n");
			return distance;
		}

//		void t_MapInstance::load(Map::t_Simplex *simplexTerrain, Map::Simplex *simplexWater) {
////			debug.log("Loading Map: ("+std::to_string(x)+"), ("+std::to_string(z)+")\n");
//			Sys::mapSys.load(x*simplexTerrain->terrain_size, z*simplexTerrain->terrain_size, Terrain.data, simplexTerrain);
//			Sys::mapSys.calc(Terrain.data);
//
//			// TODO: Water
//			Sys::mapSys.load(x*simplexWater->terrain_size, z*simplexWater->terrain_size, Water.data, simplexWater);
//			Sys::mapSys.calc(Water.data);
//
//			// TODO: O2D
//			// TODO: O3D
//		}

		// TODO: Make load() function take only 1 noise, and an enum to specify what the noise is for (Terrain, Water, Moisture, Altitude, etc)
		void t_MapInstance::load(	Core::Noise::t_Noise *terrainNoise,
									Core::Noise::t_Noise *waterNoise,
									Core::Noise::t_Noise *moistureNoise,
									Core::Noise::t_Noise *altitudeNoise,
									Core::Noise::t_Noise *treeNoise)
		{
//			x = (x-32768) * noise->parent->chunk_size;
//			z = (z-32768) * noise->parent->chunk_size;

			Sys::mapSys.load(x, z, Terrain.data, terrainNoise);
			Sys::mapSys.load(x, z, Terrain.data, 0, moistureNoise);
			Sys::mapSys.load(x, z, Terrain.data, 1, altitudeNoise);
//			Sys::mapSys.load(x, z, Terrain.data, 2, undefinedNoise);
			Sys::mapSys.calc(Terrain.data);

			// TODO: Load O2D Objects (Trees/Flora)
			//treeNoise
			//Sys::o2dSys.load(x, z, Terrain.data, O2D.data, treeNoise);
			Sys::o2dSys.load(x, z, terrainNoise, O2D.data, treeNoise);
			Sys::o2dSys.calc(O2D.data);

			if(Terrain.data.lowestHeight <= waterNoise->parent->chunk_height_offset) {
				Sys::mapSys.load(x, z, Water.data, waterNoise);
				Sys::mapSys.calc(Water.data);
			}
		}

		void t_MapInstance::load(	std::string offset,
									Core::Noise::t_Noise *terrainNoise,
									Core::Noise::t_Noise *waterNoise,
									Core::Noise::t_Noise *moistureNoise,
									Core::Noise::t_Noise *altitudeNoise,
									Core::Noise::t_Noise *treeNoise)
		{
			setOffset(offset);
			load(terrainNoise, waterNoise, moistureNoise, altitudeNoise, treeNoise);
		}

//		void t_MapInstance::update() {
//		}

		void t_MapInstance::drawTerrain() {
			Terrain.data.vao.Draw(GLM_DRAW_ELEMENTS);
		}

		void t_MapInstance::drawWater() {
			Water.data.vao.Draw(GLM_DRAW_ELEMENTS);
		}

		void t_MapInstance::drawO2D(Vector3f &vCamPos, _Lights &lights, t_UniformLocations &uniforms) {
//			Vector3f	vCamPos;
//			vCamPos[0] = -Core::gameVars->player.active->transform.pos[0];
//			vCamPos[1] = 0.0f;
//			vCamPos[2] = -Core::gameVars->player.active->transform.pos[2];
//			vCamPos[0] = 0.0f;
//			vCamPos[1] = 0.0f;
//			vCamPos[2] = 0.0f;

			for ( auto const &item : O2D.data ) {
//				debug.log("DRAW: Tree at ("+std::to_string(item->x)+", "+std::to_string(item->y)+", "+std::to_string(item->z)+") with dimensions ("+std::to_string(item->w)+", "+std::to_string(item->h)+")\n", debug().purple);
				// TODO: Translate
				Core::matrix->Push();

//					matrix->Translate(	item->x,
//										item->y,
//										item->z	);

//					matrix->Rotate(Core::gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
//					matrix->Rotate(Core::gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
//					matrix->Translate(Core::gameVars->player.active->transform.pos[0], Core::gameVars->player.active->transform.pos[1], Core::gameVars->player.active->transform.pos[2]);
//
//					matrix->SetTransform();

//					Data2f vCoords[] = { {0.0, 0.0},
//										 {0.0, 1.0},
//										 {1.0, 0.0},
//										 {1.0, 1.0} };
//
//					float fW = item->w/2.0f;
//					float fH = item->h/2.0f;
//
//					Data4f vVerts[]	=	{	{	-fW,	fH,		0.0,	0.0f	},
//											{	-fW,	0.0f,	0.0,	0.0f	},
//											{	 fW,	fH,		0.0,	0.0f	},
//											{	 fW,	0.0f,	0.0,	0.0f	}	};
//
//					item->vao.Begin(GL_TRIANGLE_STRIP, 4, 4, 1);
//					item->vao.CopyData(GLA_VERTEX, vVerts);
//					item->vao.CopyData(GLA_TEXTURE, vCoords, 0);
//					item->vao.End();

					Vector3f	vObjPos = { float(item->x)*Core::gameVars->screen.fScale,
											float(item->y)*Core::gameVars->screen.fScale,
											float(item->z)*Core::gameVars->screen.fScale
										  };

					Core::shader->vars.GLS_PHONG_O2D.vObjPos = vObjPos;
					Core::shader->vars.GLS_PHONG_O2D.vCamPos = vCamPos;
					Core::shader->setUniform(GLS_PHONG_O2D, lights, uniforms);
//					data.texture[count].Set(data.image[count]);

//					item->vao.Draw(GLM_DRAW_ELEMENTS);
					item->vao.Draw();
				Core::matrix->Pop();
			}
		}

//		void t_MapInstance::t_TerrainInterface::draw(Core::SHADER_PROGRAMS iShader) {
//		}
//
//		void t_MapInstance::t_WaterInterface::draw(Core::SHADER_PROGRAMS iShader) {
//		}








































































	} /* namespace Sys */
} /* namespace Core */

#endif /* HEADERS_GAMESYS_MAPINSTANCE_H_ */
