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
#include "./O2D.h"
#include "./O3D.h"
#include "./MapData.h"
//#include "./MapSys.h"

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

				void load(Map::Simplex &simplex);
				void setOffset(std::string offset);
				float calcDistance(Vector3f a=Vector3f(0.0f), int terrain_size=1);
				void load(std::string offset, Map::Simplex &simplex);
//				void update();
				void draw(Core::SHADER_PROGRAMS iShader);

				struct t_TerrainInterface {
					t_MapInstance * parent;
					Map::Data	data;
//					void update();
					void draw();
					t_TerrainInterface(t_MapInstance * p) { parent = p; }
				};
				t_TerrainInterface Terrain = t_TerrainInterface(this);

				struct t_O2DInterface {
					t_MapInstance * parent;
					_O2DData data;
//					void update();
					void draw();
					t_O2DInterface(t_MapInstance * p) { parent = p; }
				};
				t_O2DInterface O2D = t_O2DInterface(this);

				struct t_O3DInterface {
					t_MapInstance * parent;
					_O3DData data;
//					void update();
					void draw();
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
			debug.log("Setting Map Offset: ");
			std::stringstream ssx;
			ssx << std::hex << offset.substr(0, 4);
			ssx >> x;
			debug.print(ssx.str()+", ");

			std::stringstream ssz;
			ssz << std::hex << offset.substr(5, 4);
			ssz >> z;

			calcDistance();
			debug.print(ssz.str()+"\n");
		}

		// when a=[0,0], player is at starting position
		float t_MapInstance::calcDistance(Vector3f a, int terrain_size) {
			// Convert player coords to grid chunks
//			int aX = -(a.x+(terrain_size/2.0f))/terrain_size,
//				aZ = -(a.z+(terrain_size/2.0f))/terrain_size;
			float aX = -a.x/terrain_size,
				  aZ = -a.z/terrain_size;
//			Vector2f vA = Vector2f(aX, aZ);
			Vector2f vA;
			vA.x = aX;
			vA.y = aZ;

			// Calculate distance in grid chunks
			int bX = x-32768,
				bZ = z-32768;
//			Vector2f vB = Vector2f(bX, bZ);
			Vector2f vB;
			vB.x = bX;
			vB.y = bZ;
//			distance = abs(sqrt(aX*aX+aZ*aZ)-sqrt(bX*bX+bZ*bZ));//-a.length();
			//distance = sqrt(aX*aX+aZ*aZ)-sqrt(bX*bX+bZ*bZ);//-a.length();
			distance = (vB-vA).length();
//			debug.log(std::to_string(distance)+" ["+std::to_string(aX)+", "+std::to_string(aZ)+"] ["+std::to_string(bX)+", "+std::to_string(bZ)+"]\n");
			return distance;
		}

		void t_MapInstance::load(Map::Simplex &simplex) {
			debug.log("Loading Map: ("+std::to_string(x)+"), ("+std::to_string(z)+")\n");
			Sys::mapSys.load(x*simplex.terrain_size, z*simplex.terrain_size, Terrain.data, simplex);
			Sys::mapSys.calc(Terrain.data);
		}

		void t_MapInstance::load(std::string offset, Map::Simplex &simplex) {
			setOffset(offset);
			load(simplex);
		}

//		void t_MapInstance::update() {
//		}

		void t_MapInstance::draw(Core::SHADER_PROGRAMS iShader) {
//		void MapSys::draw(Core::SHADER_PROGRAMS iShader, Core::_Lights &lights) {
//			glActiveTexture(GL_TEXTURE0);
//			Core::sysTex->set(Core::sysTex->TEX_TESTPATTERN);
//			Core::sysTex->set(Core::sysTex->TEX_DIRT);
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
//
//			Core.shader.use(iShader);
//			std::cout << "Drawing Map...";
//			for (int x=0; x<data.iSize; x++) {
//				for (int z=0; z<data.iSize; z++) {

			/*
			 * Temporary drawing routine
			 */
//			int x=0, z=0;
//					glEnable(GL_CULL_FACE);
//					Core::matrix->Push();
//						// Center World
//
//						// Move chunk according to player
//						matrix->Rotate(Core::gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
//						matrix->Rotate(Core::gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
//						matrix->Translate(Core::gameVars->player.active->transform.pos[0], Core::gameVars->player.active->transform.pos[1], Core::gameVars->player.active->transform.pos[2]);
//
//						// Move chunk into place (Do in loader so lighting works easily)
//						Core::matrix->Scale(1*Core::gameVars->screen.fScale, 1*Core::gameVars->screen.fScale, 1*Core::gameVars->screen.fScale);
//						matrix->Translate(x*1024*Core::gameVars->screen.fScale, 0.0f, z*1024*Core::gameVars->screen.fScale);
//						matrix->SetTransform();
//
//						shader->use(iShader);
//						shader->getUniform(iShader, &lights);
//
//						//mapData[0][0].Draw(GLM_DRAW_ELEMENTS);
//						//Terrain.draw();
						Terrain.data.vao.Draw(GLM_DRAW_ELEMENTS);
//
//						// Draw vertex normals (~6fps drop)
//						if(Core::gameVars->debug.gui.b5) {
//							glLineWidth(1.0f);
//							shader->use(GLS_NORMAL_LINE2);
//							shader->getUniform(GLS_NORMAL_LINE2);
//							//mapData[0][0].Draw(GLM_DRAW_ELEMENTS);
//							Terrain.data.vao.Draw(GLM_DRAW_ELEMENTS);
//						}
//
//						//glActiveTexture(GL_TEXTURE0);	Core::sysTex->set(Core::sysTex->TEX_WATER);
//						//mapData[0][1].Draw(GLM_DRAW_ELEMENTS);
//
//						//glActiveTexture(GL_TEXTURE0);	Core::sysTex->set(Core::sysTex->TEX_ROCK);
//						//mapData[1][0].Draw(GLM_DRAW_ELEMENTS);
//
//						//glActiveTexture(GL_TEXTURE0);	Core::sysTex->set(Core::sysTex->TEX_DIRT);
//						//mapData[1][1].Draw(GLM_DRAW_ELEMENTS);
//
//						glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//					Core::matrix->Pop();
//					glEnable(GL_CULL_FACE);
//					glDisable(GL_CULL_FACE);
//				}
//			}



//					Core.matrix.Push();
//						Core.matrix.Translate(x*1024*gameVars->screen.iScale, 0, z*1024*gameVars->screen.iScale);
//						Core.matrix.Scale(16*gameVars->screen.iScale, 16*gameVars->screen.iScale, 16*gameVars->screen.iScale);
//						Core.matrix.SetTransform();
//						Core.shader.getUniform(*atmosphere, iShader);
//						//	if(bOcclude) occlusion.StartQuery("World Map", iNum);
//								mapData[x][z].vao->Draw(GLM_DRAW_ELEMENTS);
//						//	if(bOcclude) occlusion.EndQuery("World Map", iNum);
//					Core.matrix.Pop();
//				}
//				std::cout << std::endl;
//			}
//			std::cout << "Done" << std::endl;
		}



	} /* namespace Sys */
} /* namespace Core */

#endif /* HEADERS_GAMESYS_MAPINSTANCE_H_ */
