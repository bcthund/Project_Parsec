/*
 * _O3D.h
 *
 *  Created on: Nov 1, 2010
 *      Author: bcthund
 */

#ifndef _O3D_Data_H_
#define _O3D_Data_H_

#include <iostream>
#include <sstream>

#include "../core/core_functions.h"
#include "../core/vao.h"
#include "../core/texture.h"
#include "../core/bounding_volume.h"
//#include "../core/matrix.h"
//#include "../core/shader.h"
//#include "../core/helper.h"


/** \class _O3D
 *
 * Used to draw 3D objects to
 * the scene.
 *
 */

namespace Core {
	namespace Sys {
		namespace O3D {

			struct t_O3D_Item {
				int id;
				Vector3f pos;
				Vector3f scale;
				Vector3f rot;

//				Vector3f translate;		// To allow object to be moved
				Vector3f posMod, rotMod;

				//float blend;
				std::string image;
//				std::string bump;
//				std::string spec;
//				std::string ambo;
				std::string file;
				Texture texture;
				float distance;
				VAO vao;
				_BOUNDING_VOLUME::_BOUNDING_VOLUME_TYPE bvType;
				_BOUNDING_VOLUME * bV;

				t_O3D_Item() {
					id			= 0;
					//blend		= 0;
					//pos			= Vector3f();
					//scale		= Vector3f();
					//rot			= Vector3f();
					distance 	= 0.0f;
					image		= "";
//					bump		= "";
//					spec		= "";
//					ambo		= "";
					file		= "";
					//vao		= VAO();
					//bV		= _BOUNDING_VOLUME();
					bvType		= _BOUNDING_VOLUME::BOUNDING_VOLUME_NONE;
					//bV = nullptr;
					bV			= new _BOUNDING_VOLUME(posMod);
				}

				~t_O3D_Item() {
//					delete[] id;
//					delete[] blend;
//					delete[] pos;
//					delete[] scale;
//					delete[] rot;
//					delete[] distance;
//					delete[] image;
//					delete[] bump;
//					delete[] spec;
//					delete[] ambo;
//					delete[] file;
//					delete[] vao;
					//if(bV != nullptr)	delete bV;
					delete bV;
//					delete[] bvType;
				}
			};

			using Data = t_Vector1T<t_O3D_Item*>;

		} /* O3D namespace */
	} /* Sys namespace */

























//		struct _O3DData {
//			int id;
//			Vector3f pos;
//			Vector3f scale;
//			Vector3f rot;
//
////			Vector3f translate;		// To allow object to be moved
//			Vector3f posMod, rotMod;
//
//			//float blend;
//			std::string image;
//			std::string bump;
//			std::string spec;
//			std::string ambo;
//			std::string file;
//			Texture texture;
//			float distance;
//			VAO vao;
//			_BOUNDING_VOLUME::_BOUNDING_VOLUME_TYPE bvType;
//
//			_BOUNDING_VOLUME * bV;
//
//			_O3DData() {
//				id			= 0;
//				//blend		= 0;
//				//pos			= Vector3f();
//				//scale		= Vector3f();
//				//rot			= Vector3f();
//				distance 	= 0.0f;
//				image		= "";
//				bump		= "";
//				spec		= "";
//				ambo		= "";
//				file		= "";
//				//vao			= VAO();
//				//bV			= _BOUNDING_VOLUME();
//				bvType		= _BOUNDING_VOLUME::BOUNDING_VOLUME_NONE;
//				//bV = nullptr;
//				bV = new _BOUNDING_VOLUME(posMod);
//			}
//
//			~_O3DData() {
////				delete[] id;
////				delete[] blend;
////				delete[] pos;
////				delete[] scale;
////				delete[] rot;
////				delete[] distance;
////				delete[] image;
////				delete[] bump;
////				delete[] spec;
////				delete[] ambo;
////				delete[] file;
////				delete[] vao;
//				//if(bV != nullptr)	delete bV;
//				delete bV;
////				delete[] bvType;
//			}
//		};

//		class _O3D {
//			private:
//				static t_UniformLocations uniforms;
//				Matrix_System 	* matrix;
//				Shader_System 	* shader;
//				_Collision		* collision;
//				_Helper			* helper;
//				//_O3DData data;
//				uint uiRecordSize;
//				std::string sFileDir;
//				std::string sTexDir;
//
//			protected:
//
//			public:
//				//int idcount;
//
//				struct _O3DCollection {
//					static int idcount;
//					const int last = 1024;
//					_O3DData * items;		// TODO: This probably shouldn't be public but needed for testing
//					_O3DData& operator[](int i) { if(i>last) i=last; return items[i]; }
//
//					_O3DCollection() {
//						items = new _O3DData[1024];
//					}
//
//					~_O3DCollection() {
//						delete [] items;
//					}
//				} data;
//
//				bool init(Core::_Lights &lights);
//				bool load();
//				bool calc();
//				void draw(Core::_Lights &lights);
//				_O3D(Matrix_System &m, Shader_System &s, _Collision &c, _Helper &h) {
//					Core::debug.log("Construct O3D {");
//					matrix = &m;
//					shader = &s;
//					collision = &c;
//					helper = &h;
//					uiRecordSize = 96;
//					sTexDir = "./texture/o3d/";
//					sFileDir = "./ply/";
//					//idcount = -1;
//					Core::debug.print(" Done ", Core::debug().GREEN);
//					Core::debug.print("}\n");
//				}
//				~_O3D() {
//					Core::debug.log("Destroy O3D {");
//					Core::debug.print(" Done ", Core::debug().GREEN);
//					Core::debug.print("}\n");
//				}
//		};
//
//		int _O3D::_O3DCollection::idcount = -1;
//		t_UniformLocations _O3D::uniforms;
//
//
//		bool _O3D::init(Core::_Lights &lights) {
//			Core::debug.log("Init O3D {");
//			if(!uniforms.bInit) shader->getUniform(GLS_PHONG, lights, uniforms);
//			Core::debug.print(" Done ", Core::debug().GREEN);
//			Core::debug.print("}\n");
//			return true;
//		}
//
//		bool _O3D::load() {
//			Core::debug.log("Load O3D {\n");
//			Core::debug.logIncreaseIndent();
//
//			bool bReadResult;
//			MemBlock memBlock;
//			std::string loadFile;
//			std::stringstream sStream;
//			int item=0;
//
//			//################################
//			//		Load Binary Object Data
//			sStream.str("");
//			sStream << "./region/prime/o3d/100.o3d";
//			loadFile=sStream.str();
//			bReadResult = readFile(loadFile, memBlock);		//Read the data file into memory
//
//			if (memBlock.size <= 0) data.idcount = -1;
//			else {
//				for (int d=0; d<memBlock.size; d+=uiRecordSize) {
//					data.idcount = item;	// idcount is static
//
//					//if (Core::gameVars->debug.load) std::cout << idcount << ".";
//
//					data[item].id				=	(	(unsigned int)(memBlock.buffer[0+d]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[0+d]&0x0F)*256 +
//														(unsigned int)(memBlock.buffer[1+d]&0xF0)		+ (unsigned int)(memBlock.buffer[1+d]&0x0F) );
//
//					data[item].pos.x			=	(	(unsigned int)(memBlock.buffer[2+d]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[2+d]&0x0F)*256 +
//														(unsigned int)(memBlock.buffer[3+d]&0xF0)		+ (unsigned int)(memBlock.buffer[3+d]&0x0F) );
//
//					data[item].pos.z			=	(	(unsigned int)(memBlock.buffer[4+d]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[4+d]&0x0F)*256 +
//														(unsigned int)(memBlock.buffer[5+d]&0xF0)		+ (unsigned int)(memBlock.buffer[5+d]&0x0F) );
//
//					data[item].bvType			=	_BOUNDING_VOLUME::_BOUNDING_VOLUME_TYPE(	(unsigned int)(memBlock.buffer[6+d]&0xF0) 		+ (unsigned int)(memBlock.buffer[6+d]&0x0F) );
//					data[item].bV->iType = data[item].bvType;
//					//data[item].bV->init()
//
//					// memBlock.buffer[7] unused
//
//					data[item].pos.y			=	(__int16_t)(	(unsigned int)(memBlock.buffer[8+d]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[8+d]&0x0F)*256 +
//																	(unsigned int)(memBlock.buffer[9+d]&0xF0)		+ (unsigned int)(memBlock.buffer[9+d]&0x0F) );
//
//					//float fT = map.getHeight(abs(data[idcount].x[idcount]), abs(data[idcount].z[idcount]), x, z);
//					//data[idcount].blend[idcount] += fT;
//
//					data[item].scale.x		=	(	(unsigned int)(memBlock.buffer[10+d]&0x0F)*256	+ (unsigned int)(memBlock.buffer[10+d]&0xF0)*256 +
//														(unsigned int)(memBlock.buffer[11+d]&0x0F)		+ (unsigned int)(memBlock.buffer[11+d]&0xF0) )*16;
//
//					data[item].scale.y		=	(	(unsigned int)(memBlock.buffer[12+d]&0x0F)*256	+ (unsigned int)(memBlock.buffer[12+d]&0xF0)*256 +
//														(unsigned int)(memBlock.buffer[13+d]&0x0F)		+ (unsigned int)(memBlock.buffer[13+d]&0xF0) )*16;
//
//					data[item].scale.z		=	(	(unsigned int)(memBlock.buffer[14+d]&0x0F)*256	+ (unsigned int)(memBlock.buffer[14+d]&0xF0)*256 +
//														(unsigned int)(memBlock.buffer[15+d]&0x0F)		+ (unsigned int)(memBlock.buffer[15+d]&0xF0) )*16;
//
//					data[item].rot.x			=	(	(unsigned int)(memBlock.buffer[16+d]&0xF0)*256	+ (unsigned int)(memBlock.buffer[16+d]&0x0F)*256 +
//														(unsigned int)(memBlock.buffer[17+d]&0xF0)		+ (unsigned int)(memBlock.buffer[17+d]&0x0F) );
//
//					data[item].rot.y			=	(	(unsigned int)(memBlock.buffer[18+d]&0xF0)*256	+ (unsigned int)(memBlock.buffer[18+d]&0x0F)*256 +
//														(unsigned int)(memBlock.buffer[19+d]&0xF0)		+ (unsigned int)(memBlock.buffer[19+d]&0x0F) );
//
//					data[item].rot.z			=	(	(unsigned int)(memBlock.buffer[20+d]&0xF0)*256	+ (unsigned int)(memBlock.buffer[20+d]&0x0F)*256 +
//														(unsigned int)(memBlock.buffer[21+d]&0xF0)		+ (unsigned int)(memBlock.buffer[21+d]&0x0F) );
//
//					std::string theImage = "";
//					for (int count=22; count<60; count++) {
//						if (memBlock.buffer[count+d]!=0) theImage+=memBlock.buffer[count+d];
//						else break;
//					}
//					data[item].file = theImage;
//
//					theImage = "";
//					for (int count=60; count<uiRecordSize; count++) {
//						if (memBlock.buffer[count+d]!=0) theImage+=memBlock.buffer[count+d];
//						else break;
//					}
//					data[item].image = theImage;
//
//					// TODO: Check for duplicate images
//					data[item].texture.Begin(4);		// Room for all 4 mappings (image, bump, spec, ambo)
//					data[item].texture.Load(sTexDir, theImage, 0);
//
//					Core::debug.log("["+std::to_string(item)+"] "+data[item].file+"\n", Core::debug().YELLOW);
//
//					item++;
//				}
//			}
//
//			Core::debug.logDecreaseIndent();
//			Core::debug.log("}\n");
//			return true;
//		}
//
//		bool _O3D::calc() {
//			Core::debug.log("Calc O3D {");
//
//			std::string loadFile;
//			std::stringstream sStream;
//			//string buffer = "";
//
//			if (data.idcount != -1) {
//				for (int item=0; item <= data.idcount; item++) {
//					sStream.str("");
//					sStream << sFileDir << data[item].file;
//					loadFile=sStream.str();
//
//					//PLY_Loader * pLoad = new PLY_Loader;
//					PLY_Loader pLoad;
//					pLoad.load(loadFile);
//
//					//if (Core::gameVars->debug.load) std::cout << count << ".";
//
//					// ##############################
//					// Get bounding volume ready
//					data[item].bV->fPadding *= Core::gameVars->screen.fScale;
//					data[item].bV->Start(data[item].scale);
//					//data[item].bV->Start(Vector3f(1.0f));
//
//					// Find min and max vertex positions, this is good for OBB only
//					for (int i=0; i<pLoad.numVerts; i++) {
//						data[item].bV->CheckMinMaxOBB(Vector3f(pLoad.vVerts[i][0]*Core::gameVars->screen.fScale, pLoad.vVerts[i][1]*Core::gameVars->screen.fScale, pLoad.vVerts[i][2]*Core::gameVars->screen.fScale));
//						//data[item].bV->CheckXYZ(Vector3f(pLoad.vVerts[i][0]*Core::gameVars->screen.fScale, pLoad.vVerts[i][1]*Core::gameVars->screen.fScale, pLoad.vVerts[i][2]*Core::gameVars->screen.fScale));
//					}
//
//					// Figure out the zero point (center of model)
//					data[item].bV->CalcOBB();
//
//					// Find furthest point from center, needed for Sphere and Cylinder to completely contain model
//					//for (int i=0; i<pLoad.numVerts; i++) {
//					//	data[item].bV->CheckXYZ(Vector3f(pLoad.vVerts[i][0]*Core::gameVars->screen.fScale, pLoad.vVerts[i][1]*Core::gameVars->screen.fScale, pLoad.vVerts[i][2]*Core::gameVars->screen.fScale));
//					//}
//					data[item].bV->SetRotation(data[item].rot);
//					data[item].bV->SetPosition(data[item].pos*Core::gameVars->screen.fScale);
//					//data[item].bV->Finish();
//
//					// ##############################
//					// Apply transformations to objects now
//					matrix->Push();
//						matrix->SetIdentity();
//						matrix->Rotate(Degrees(data[item].rot.x).toRadians(), -1.0, 0.0, 0.0);
//						matrix->Rotate(Degrees(data[item].rot.y).toRadians(), 0.0, -1.0, 0.0);
//						matrix->Rotate(Degrees(data[item].rot.z).toRadians(), 0.0, 0.0, -1.0);
//						 Matrix44f mTransform = matrix->GetModelView();
//						for(int vert=0; vert<pLoad.numVerts; vert++) {
//							pLoad.vVerts[vert][0] *= data[item].scale.x*Core::gameVars->screen.fScale;
//							pLoad.vVerts[vert][1] *= data[item].scale.y*Core::gameVars->screen.fScale;
//							pLoad.vVerts[vert][2] *= data[item].scale.z*Core::gameVars->screen.fScale;
//
//							Vector4f vVertex = Vector4f(pLoad.vVerts[vert][0], pLoad.vVerts[vert][1], pLoad.vVerts[vert][2], 1.0f);
//							Vector4f vTVertex = mTransform * vVertex;
//							pLoad.vVerts[vert][0] = vTVertex.x;
//							pLoad.vVerts[vert][1] = vTVertex.y;
//							pLoad.vVerts[vert][2] = vTVertex.z;
//
//							// Build AABB after rotations have been performed, but before translations
//							data[item].bV->CheckMinMaxAABB(Vector3f(pLoad.vVerts[vert][0], pLoad.vVerts[vert][1], pLoad.vVerts[vert][2]));
//
//							Vector4f vNormal = Vector4f(pLoad.vNorms[vert][0], pLoad.vNorms[vert][1], pLoad.vNorms[vert][2], 1.0f);
//							Vector4f vTNormal = mTransform * vNormal;
//							pLoad.vNorms[vert][0] = vTNormal.x;
//							pLoad.vNorms[vert][1] = vTNormal.y;
//							pLoad.vNorms[vert][2] = vTNormal.z;
//
//							pLoad.vVerts[vert][0] += data[item].pos.x*Core::gameVars->screen.fScale;
//							pLoad.vVerts[vert][1] += data[item].pos.y*Core::gameVars->screen.fScale;
//							pLoad.vVerts[vert][2] += data[item].pos.z*Core::gameVars->screen.fScale;
//						}
//					matrix->Pop();
//					data[item].bV->CalcAABB();
//					data[item].bV->Finish(*matrix);
//
////						if (bUpdate) {
////							//glFlush();
////							//glFinish();
////							//SDL_GL_SwapBuffers();
////							//glFlush();
////							//glFinish();
////							new(&data[item].vao) VAO();
////
////							//delete data[item].vao;
////							//data[item].vao = new VAO();
////
////							//cout << "Update data[item]...";
////
////							//data[item].vao.Reset();
////							data[item].vao.Begin(GL_TRIANGLES, pLoad->numDrawVerts, 1);
////							data[item].vao.CopyData(GLA_VERTEX, pLoad->vVerts);				// !!! THIS IS WHERE THE FREEZING IS HAPPENING !!!
////							data[item].vao.CopyData(GLA_NORMAL, pLoad->vNorms);
////							data[item].vao.CopyData(GLA_TEXTURE, pLoad->vCoords, 0);
////							data[item].vao.CopyData(GLA_INDEX, pLoad->vIndex);
////							data[item].vao.End();
////						}
////						else {
//						data[item].vao.Begin(GL_TRIANGLES, pLoad.numVerts, pLoad.numDrawVerts, 1);
//						data[item].vao.CopyData(GLA_VERTEX, pLoad.vVerts);
//						data[item].vao.CopyData(GLA_NORMAL, pLoad.vNorms);
//						data[item].vao.CopyData(GLA_TEXTURE, pLoad.vCoords, 0);
//						data[item].vao.CopyData(GLA_INDEX, pLoad.vIndex, pLoad.numDrawVerts);
//						data[item].vao.End();
////						}
//
//					//delete pLoad;
//
//					//cout << buffer << endl;
//				}
//			}
//
//			Core::debug.print(" Done ", Core::debug().GREEN);
//			Core::debug.print("}\n");
//			return true;
//		}
//
//		void _O3D::draw(Core::_Lights &lights) {
//			glDisable(GL_CULL_FACE);
//			glActiveTexture(GL_TEXTURE0);
//			shader->use(GLS_PHONG);
//			for (int item=0; item <= data.idcount; item++) {
//				matrix->Push();
//					data[item].texture.Set(data[item].image);
//
//					//glActiveTexture(GL_TEXTURE0);
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
//
//					//glActiveTexture(GL_TEXTURE0);
//
//					//glActiveTexture(GL_TEXTURE1);
//					//Core::gameVars->texture.sprite.Set("normal_00.png");
//					//Core::gameVars->texture.sprite.Set(data.image[count]);
//
//					//glActiveTexture(GL_TEXTURE0);
//
//					matrix->Rotate(Core::gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
//					matrix->Rotate(Core::gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
//					matrix->Translate(Core::gameVars->player.active->transform.pos[0], Core::gameVars->player.active->transform.pos[1], Core::gameVars->player.active->transform.pos[2]);
//					matrix->SetTransform();
//
//					matrix->Push();
//						matrix->Translate(data[item].posMod);
//						//matrix->Rotate(data[item].rotMod);
//
////						Vector3f from	= Vector3f(0.0f),
////								 to		= data[item].rotMod;
////
////						Vector3f forward	= from - to;
////						forward = forward.normal();
////						Vector3f tmp		= Vector3f(0, 1, 0);
////						Vector3f right		= Core::gmath.Cross(tmp.normal(), forward);
////						Vector3f up			= Core::gmath.Cross(forward, right);
////
////						Matrix44f	mlookAt = {	right[0],	right[1],	right[2],	0.0f,
////												up[0], 		up[1],		up[2],		0.0f,
//////												0.0f,		0.0f,		0.0f,		0.0f,
////												forward[0],	forward[1],	forward[2],	0.0f,
////												from[0],	from[1],	from[2],	1.0f	};
////
////						matrix->Apply(mlookAt);
//
//						matrix->Scale(Core::gameVars->screen.fScale);
//						matrix->SetTransform();
//						shader->setUniform(GLS_PHONG, lights, uniforms);
//						data[item].vao.Draw(GLM_DRAW_ELEMENTS);
//
//
//
////						shader->getUniform(iShader, &lights);
////						data[item].vao.Draw(GLM_DRAW_ELEMENTS);
//						helper->drawLine(Vector3f(0.0f), data[item].rotMod, 2.5f, 100.0f, Core::colors[colors().Yellow], Core::colors[colors().Black]);
//
//						// Draw bounding volume if mouse ray intersects
//						if(collision->bUpdateRequest[0]) collision->Ray(Core::mouse->rays[1].pos, Core::mouse->rays[1].dir, *data[item].bV, true);
//
//						// Must be separate to draw complete tests
//						if(data[item].bV->cdata.result == true) {
//							data[item].bV->Draw(*matrix, *shader, *helper, data[item].posMod, true);
//
////							glPolygonMode(GL_FRONT_AND_BACK, Core::gameVars->screen.iPolygonMode);
//						}
//					matrix->Pop();
//
////					helper->drawLine(Vector3f(0.0f), data[item].rotMod, 2.5f, 50.0f, Core::colors->yellow, Core::colors->black);
//
//					matrix->Push();
//						// Move to object position for origin drawing
//						matrix->Translate(data[item].pos);
//						matrix->Rotate(Degrees(data[item].rot.x).toRadians(), -1.0, 0.0, 0.0);
//						matrix->Rotate(Degrees(data[item].rot.y).toRadians(), 0.0, -1.0, 0.0);
//						matrix->Rotate(Degrees(data[item].rot.z).toRadians(), 0.0, 0.0, -1.0);
////						matrix->Scale(25.0f);
//						matrix->Scale(Core::gameVars->screen.fScale);
//						matrix->SetTransform();
//						shader->use(GLS_LINES);
//						shader->getUniform(GLS_LINES);
//						glPolygonMode(GL_FRONT_AND_BACK, GL_LINES);
//						helper->drawPosition(2.0f, 25.0f);
//						glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//					matrix->Pop();
//
////						glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
////
////						// Draw bounding volume if mouse ray intersects
////						if(collision->bUpdateRequest[0]) collision->Ray(Core::mouse->rays[1].pos, Core::mouse->rays[1].dir, *data[item].bV, true);
////
////						// Must be separate to draw complete tests
////						if(data[item].bV->cdata.result == true) {
////							data[item].bV->Draw(*matrix, *shader, *helper, data[item].translate, true);
////							glPolygonMode(GL_FRONT_AND_BACK, Core::gameVars->screen.iPolygonMode);
////						}
//				matrix->Pop();
//			}
//			glEnable(GL_CULL_FACE);
//			if(collision->bUpdateRequest[0]) collision->bUpdateRequest[0] = false;
//		}
//	}
}
#endif /* _O3D_Data_H_ */
