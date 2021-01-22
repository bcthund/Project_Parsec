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

		enum e_Interface {
			INTERFACE_TERRAIN			= 1,
			INTERFACE_WATER				= 2,
			INTERFACE_MOISTURE			= 4,
			INTERFACE_ALTITUDE_OFFSET	= 8,
			INTERFACE_O2D_TREE			= 16,
			INTERFACE_O2D_FLORA			= 32,
			INTERFACE_O3D				= 64
		};
		using i_Interface = int;

//		class t_MapBase;
		class t_MapInstance {
			friend class t_MapBase;
			private:
				Core::Noise::t_Noise *terrainNoise;
				Core::Noise::t_Noise *waterNoise;
				Core::Noise::t_Noise *moistureNoise;
				Core::Noise::t_Noise *altitudeNoise;
				Core::Noise::t_Noise *treeNoise;

			public:
				t_UMap<std::string, t_MapBase*> chunks;
				void setNoise(e_Interface interface, Core::Noise::t_Noise *noise);
				t_MapInstance();
				~t_MapInstance();
		};

		/**
		 * @brief Defines all the components in a single map Chunk
		 *
		 */
		class t_MapBase {
			public:
				t_MapInstance *parent;
				unsigned int x, z;		///< Used to determine distance and load O2D, O3D, etc.
				float		 distance;
				bool		 bDraw;		///< Controls drawing according to distance value

//				void load(Core::Noise::t_Noise *terrainNoise,
//						  Core::Noise::t_Noise *waterNoise,
//						  Core::Noise::t_Noise *moistureNoise,
//						  Core::Noise::t_Noise *altitudeNoise,
//						  Core::Noise::t_Noise *treeNoise);
				void setOffset(std::string offset);
				float update(Vector2f a=Vector2f(0.0f));	///< Perform updates to chunk data and return current chunk distance
				void load(i_Interface e);
				void load(i_Interface e, std::string offset);
//				void load(	std::string offset,
//							Core::Noise::t_Noise *terrainNoise,
//							Core::Noise::t_Noise *waterNoise,
//							Core::Noise::t_Noise *moistureNoise,
//							Core::Noise::t_Noise *altitudeNoise,
//							Core::Noise::t_Noise *treeNoise);
				void calc();
				void calc(i_Interface e);
				void drawTerrain();
				void drawWater();
				void drawO2D(Vector3f &vCamPos, _Lights &lights, t_UniformLocations &uniforms);
				void drawO3D(_Lights &lights, t_UniformLocations &uniforms);

				struct t_TerrainInterface {
					t_MapBase * parent;
					Map::Data	data;
					t_TerrainInterface(t_MapBase * p) { parent = p; }
				};
				t_TerrainInterface Terrain = t_TerrainInterface(this);

				struct t_WaterInterface {
					t_MapBase * parent;
					Map::Data	data;
					t_WaterInterface(t_MapBase * p) { parent = p; }
				};
				t_TerrainInterface Water = t_TerrainInterface(this);

				struct t_O2DInterface {
					t_MapBase * parent;
					O2D::Data data;
					t_O2DInterface(t_MapBase * p) { parent = p; }
				};
				t_O2DInterface O2D = t_O2DInterface(this);

				struct t_O3DInterface {
					t_MapBase * parent;
					O3D::Data data;
					t_O3DInterface(t_MapBase * p) { parent = p; }
				};
				t_O3DInterface O3D = t_O3DInterface(this);

				t_MapBase(t_MapInstance *p);
				t_MapBase(std::string offset, t_MapInstance *p);
				~t_MapBase();
		};

		t_MapBase::t_MapBase(t_MapInstance *p) {
			parent			= p;
			x				= 0;
			z				= 0;
			distance		= 0;
			bDraw			= true;
		}

		t_MapBase::t_MapBase(std::string offset, t_MapInstance *p) {
			parent = p;
			x = 0;
			z = 0;
			setOffset(offset);
		}

		t_MapBase::~t_MapBase() {
			for(auto item : O2D.data) delete item;
			for(auto item : O3D.data) delete item;
		}

		void t_MapBase::setOffset(std::string offset) {
			std::stringstream ssx;
			ssx << std::hex << offset.substr(0, 4);
			ssx >> x;

			std::stringstream ssz;
			ssz << std::hex << offset.substr(5, 4);
			ssz >> z;

			update();
		}

		/**
		 * @brief Update this chunks distance from player position
		 * @param pos Position in terrain chunks
		 * @return Return the calculated distance
		 */
		float t_MapBase::update(Vector2f pos) {
			Vector2f vB;
			vB.x = int(x-32768);
			vB.y = int(z-32768);
			distance = (vB-pos).length();
			return distance;
		}

		// TODO: Make load() function take only 1 noise, and an enum to specify what the noise is for (Terrain, Water, Moisture, Altitude, etc)
		void t_MapBase::load(i_Interface e) {

			if(e&INTERFACE_TERRAIN) {
				Sys::mapSys.load(x, z, Terrain.data, parent->terrainNoise);
			}

			if(e&INTERFACE_MOISTURE) {
				Sys::mapSys.load(x, z, Terrain.data, 0, parent->moistureNoise);
			}

			if(e&INTERFACE_ALTITUDE_OFFSET) {
				Sys::mapSys.load(x, z, Terrain.data, 1, parent->altitudeNoise);
			}

			if(e&INTERFACE_WATER) {
				if(Terrain.data.lowestHeight <= parent->waterNoise->parent->chunk_height_offset) {
					Sys::mapSys.load(x, z, Water.data, parent->waterNoise);
//					Sys::mapSys.calc(Water.data);
				}
			}

			if(e&INTERFACE_O2D_TREE) {
				Sys::o2dSys.load(x, z, O2D.data, parent->treeNoise, parent->terrainNoise, parent->moistureNoise);
				Sys::o2dSys.calc(O2D.data, gameVars->player.active->transform.pos, parent->treeNoise->parent->chunk_size);
				//Sys::o2dSys.calc(O2D.data, gameVars->player.active->transform.pos, treeNoise->parent->chunk_size);
			}
//			if(e&INTERFACE_O2D_FLORA) {
//
//			}
			if(e&INTERFACE_O3D) {
				Sys::o3dSys.load(x, z, O3D.data, parent->terrainNoise);
				Sys::o3dSys.calc(O3D.data, *parent->terrainNoise->parent);
			}

//			Sys::mapSys.calc(Terrain.data);

		}

		void t_MapBase::load(i_Interface e, std::string offset) {
			setOffset(offset);
			load(e);
		}

		void t_MapBase::calc() {
			calc(	INTERFACE_TERRAIN|
					INTERFACE_MOISTURE|
					INTERFACE_ALTITUDE_OFFSET|
					INTERFACE_WATER|
					INTERFACE_O2D_TREE|
					INTERFACE_O2D_FLORA|
					INTERFACE_O3D	);
		}

		void t_MapBase::calc(i_Interface e) {
			if(e&INTERFACE_TERRAIN || e&INTERFACE_MOISTURE || e&INTERFACE_ALTITUDE_OFFSET) {
				Sys::mapSys.calc(Terrain.data);
			}

			if(e&INTERFACE_WATER) {
				Sys::mapSys.calc(Water.data);
			}

//			if(e&INTERFACE_O2D_TREE) {
//				Sys::o2dSys.calc(O2D.data, gameVars->player.active->transform.pos, treeNoise->parent->chunk_size);
//			}
//			if(e&INTERFACE_O2D_FLORA) {
//
//			}
//			if(e&INTERFACE_O3D) {
//				Sys::o3dSys.calc(O3D.data, *terrainNoise->parent);
//			}
		}

		void t_MapBase::drawTerrain() {
			Terrain.data.vao.Draw(GLM_DRAW_ELEMENTS);
		}

		void t_MapBase::drawWater() {
			Water.data.vao.Draw(GLM_DRAW_ELEMENTS);
		}

		void t_MapBase::drawO2D(Vector3f &vCamPos, _Lights &lights, t_UniformLocations &uniforms) {
			Vector3f	vObjPos;
			Core::shader->vars.GLS_PHONG_O2D.vCamPos = vCamPos;

			for ( auto const &item : O2D.data ) {
				vObjPos = { float(item->x)*Core::gameVars->screen.fScale,
							float(item->y)*Core::gameVars->screen.fScale,
							float(item->z)*Core::gameVars->screen.fScale	};

				Core::shader->vars.GLS_PHONG_O2D.vObjPos = vObjPos;
				Core::shader->setUniform(GLS_PHONG_O2D, lights, uniforms);

				item->vao.Draw();
			}
		}

		void t_MapBase::drawO3D(_Lights &lights, t_UniformLocations &uniforms) {
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
						if(collision->bUpdateRequest[0]) {
							collision->Ray(Core::mouse->rays[1].pos, Core::mouse->rays[1].dir, *item->bV, true);
						}

						// Must be separate to draw complete tests
						if(item->bV->cdata.result == true) {
							item->bV->Draw(item->posMod, true, &Core::colors[colors().Yellow]);
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
			}
			glEnable(GL_CULL_FACE);
		}



		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


		t_MapInstance::t_MapInstance() {
			terrainNoise	= nullptr;
			waterNoise		= nullptr;
			moistureNoise	= nullptr;
			altitudeNoise	= nullptr;
			treeNoise		= nullptr;
		}

//		t_MapInstance::t_MapInstance(std::string offset) {
//			x = 0;
//			z = 0;
//			setOffset(offset);
//		}

		t_MapInstance::~t_MapInstance() {
			//for (auto chunk : chunks) delete chunk.second;
		}

		void t_MapInstance::setNoise(e_Interface interface, Core::Noise::t_Noise *noise) {
			switch(interface) {
				case INTERFACE_TERRAIN:
					terrainNoise = noise;
					break;
				case INTERFACE_WATER:
					waterNoise = noise;
					break;
				case INTERFACE_MOISTURE:
					moistureNoise = noise;
					break;
				case INTERFACE_ALTITUDE_OFFSET:
					altitudeNoise = noise;
					break;
				case INTERFACE_O2D_TREE:
					treeNoise = noise;
					break;
				case INTERFACE_O2D_FLORA:
					break;
				case INTERFACE_O3D:
					break;
			}
		}



































































	} /* namespace Sys */
} /* namespace Core */

#endif /* HEADERS_GAMESYS_MAPINSTANCE_H_ */
