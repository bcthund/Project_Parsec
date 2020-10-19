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
				float update(Vector2f a=Vector2f(0.0f), int terrain_size=1);	///< Perform updates to chunk data and return current chunk distance
//				float update(Vector2i a=Vector2i(0.0f), int terrain_size=1);	///< Perform updates to chunk data and return current chunk distance
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
				void drawO3D(_Lights &lights, t_UniformLocations &uniforms);

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
					O3D::Data data;
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
		float t_MapInstance::update(Vector2f pos, int terrain_size) {
			// Convert player coords to grid chunks
//			Vector2f vA;
//			vA.x = pos.x;
//			vA.y = pos.z;
//			vA.x = (-pos.x)/terrain_size;
//			vA.y = (-pos.z)/terrain_size;
//			vA.x = (-pos.x+(terrain_size/2))/terrain_size;
//			vA.y = (-pos.z+(terrain_size/2))/terrain_size;
//			vA.x = -pos.x+(terrain_size/2);
//			vA.y = -pos.z+(terrain_size/2);
//			vA = vA/terrain_size;

			// Rounding
//			if(vA.x<0) vA.x-=1.0f; else vA.x+=1.0f;
//			if(vA.y<0) vA.y-=1.0f; else vA.y+=1.0f;

			// Calculate distance in grid chunks
			Vector2f vB;
			vB.x = int(x-32768);
			vB.y = int(z-32768);
			distance = (vB-pos).length();
//			debug.log(std::to_string(distance)+" ["+std::to_string(aX)+", "+std::to_string(aZ)+"] ["+std::to_string(bX)+", "+std::to_string(bZ)+"]\n");
			return distance;
		}

//		float t_MapInstance::update(Vector2f pos, int terrain_size) {
//			// Convert player coords to grid chunks
//			Vector2f vA;
//			vA.x = -pos.x;
//			vA.y = -pos.y;
////			vA.x = (-pos.x)/terrain_size;
////			vA.y = (-pos.z)/terrain_size;
////			vA.x = (-pos.x+(terrain_size/2))/terrain_size;
////			vA.y = (-pos.z+(terrain_size/2))/terrain_size;
////			vA.x = -pos.x+(terrain_size/2);
////			vA.y = -pos.z+(terrain_size/2);
////			vA = vA/terrain_size;
//
//			// Rounding
////			if(vA.x<0) vA.x-=1.0f; else vA.x+=1.0f;
////			if(vA.y<0) vA.y-=1.0f; else vA.y+=1.0f;
//
//			// Calculate distance in grid chunks
//			Vector2i vB;
//			vB.x = int(x-32768);
//			vB.y = int(z-32768);
//			distance = (vB-vA).length();
////			debug.log(std::to_string(distance)+" ["+std::to_string(aX)+", "+std::to_string(aZ)+"] ["+std::to_string(bX)+", "+std::to_string(bZ)+"]\n");
//			return distance;
//		}

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
			Sys::o2dSys.load(x, z, O2D.data, treeNoise, terrainNoise, moistureNoise);
			//Sys::o2dSys.calc(O2D.data, gameVars->player.active->transform.pos, terrainNoise->parent->chunk_size);
			Sys::o2dSys.calc(O2D.data, gameVars->player.active->transform.pos, treeNoise->parent->chunk_size);

			Sys::o3dSys.load(x, z, O3D.data);
			Sys::o3dSys.calc(O3D.data);

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
			Vector3f	vObjPos;
			Core::shader->vars.GLS_PHONG_O2D.vCamPos = vCamPos;

			for ( auto const &item : O2D.data ) {
//				Vector3f	vObjPos = { float(item->x)*Core::gameVars->screen.fScale,
//										float(item->y)*Core::gameVars->screen.fScale,
//										float(item->z)*Core::gameVars->screen.fScale
//									  };
				vObjPos = { float(item->x)*Core::gameVars->screen.fScale,
							float(item->y)*Core::gameVars->screen.fScale,
							float(item->z)*Core::gameVars->screen.fScale	};

				Core::shader->vars.GLS_PHONG_O2D.vObjPos = vObjPos;
				Core::shader->setUniform(GLS_PHONG_O2D, lights, uniforms);

				item->vao.Draw();
			}
		}

		void t_MapInstance::drawO3D(_Lights &lights, t_UniformLocations &uniforms) {
			glDisable(GL_CULL_FACE);

			for(auto &item : O3D.data) {
//				matrix->Push();
					glActiveTexture(GL_TEXTURE29);
					item->texture.Set(item->image);
//					//gameVars->texture.sprite.Set(_O3Ddata.image[count]);
//
//					//glActiveTexture(GL_TEXTURE1);
//					//data.texture.sprite.Set("bump.png");
//
//					//glActiveTexture(GL_TEXTURE2);
//					//data.texture.sprite.Set("spec.png");
//
//					//glActiveTexture(GL_TEXTURE3);
//					//data.texture.sprite.Set("ambo.png");

					matrix->Push();
						matrix->Translate(item->posMod);
						matrix->Scale(Core::gameVars->screen.fScale);
						matrix->SetTransform();
						shader->use(GLS_PHONG);
						shader->setUniform(GLS_PHONG_O3D, lights, uniforms);
						item->vao.Draw(GLM_DRAW_ELEMENTS);

//						helper->drawLine(Vector3f(0.0f), item->rotMod, 2.5f, 100.0f, Core::colors[colors().Yellow], Core::colors[colors().Black]);

						// Draw bounding volume if mouse ray intersects
						if(collision->bUpdateRequest[0]) collision->Ray(Core::mouse->rays[1].pos, Core::mouse->rays[1].dir, *item->bV, true);

						// Must be separate to draw complete tests
						if(item->bV->cdata.result == true) {
							item->bV->Draw(*matrix, *shader, *helper, item->posMod, true, &Core::colors[colors().Yellow]);
						}
					matrix->Pop();

					matrix->Push();
						// Move to object position for origin drawing
						matrix->Translate(item->pos);
						matrix->Rotate(Degrees(item->rot.x).toRadians(), -1.0, 0.0, 0.0);
						matrix->Rotate(Degrees(item->rot.y).toRadians(), 0.0, -1.0, 0.0);
						matrix->Rotate(Degrees(item->rot.z).toRadians(), 0.0, 0.0, -1.0);
						matrix->Scale(Core::gameVars->screen.fScale);
						matrix->SetTransform();
						shader->use(GLS_LINES);
						shader->getUniform(GLS_LINES);
						glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
						helper->drawPosition(2.0f, 25.0f);
						glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					matrix->Pop();

//					matrix->Push();
//						matrix->Translate(item->posMod);
//						matrix->Scale(Core::gameVars->screen.fScale);
//						matrix->SetTransform();
//						shader->use(GLS_PHONG);
//						shader->setUniform(GLS_PHONG_O3D, lights, uniforms);
////						item->vao.Draw(GLM_DRAW_ELEMENTS);
//
////						helper->drawLine(Vector3f(0.0f), item->rotMod, 2.5f, 100.0f, Core::colors[colors().Yellow], Core::colors[colors().Black]);
////						Core::debug.glErrorCheck("MapInstance", 299);
//
//						// Draw bounding volume if mouse ray intersects
//						if(collision->bUpdateRequest[0]) collision->Ray(Core::mouse->rays[1].pos, Core::mouse->rays[1].dir, *item->bV, true);
////
//						// Must be separate to draw complete tests
//						if(item->bV->cdata.result == true) {
//							item->bV->Draw(*matrix, *shader, *helper, item->posMod, true);
//						}
//					matrix->Pop();

//				matrix->Pop();
			}
			glEnable(GL_CULL_FACE);
//			if(collision->bUpdateRequest[0]) collision->bUpdateRequest[0] = false;
		}

//		void t_MapInstance::t_TerrainInterface::draw(Core::SHADER_PROGRAMS iShader) {
//		}
//
//		void t_MapInstance::t_WaterInterface::draw(Core::SHADER_PROGRAMS iShader) {
//		}








































































	} /* namespace Sys */
} /* namespace Core */

#endif /* HEADERS_GAMESYS_MAPINSTANCE_H_ */
