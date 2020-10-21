/*
 * _O3D.h
 *
 *  Created on: Nov 1, 2010
 *      Author: bcthund
 */

#ifndef _O3D_H_
#define _O3D_H_

#include <iostream>
#include <sstream>

//#include "../core/bounding_volume.h"
#include "../core/core_functions.h"
//#include "../core/matrix.h"
//#include "../core/shader.h"
//#include "../core/helper.h"
#include "O3D_Data.h"

/** \class _O3D
 *
 * Used to draw 3D objects to
 * the scene.
 *
 */

namespace Core {
	namespace Sys {

		class O3DSys {
			private:
				static t_UniformLocations uniforms;

				uint uiRecordSize;
				std::string sFileDir;
				std::string sTexDir;

			protected:

			public:
				void init(Core::_Lights &lights);
				void load(int x, int z, O3D::Data &o3d, Core::Noise::t_Noise *heightNoise);
				void calc(O3D::Data &o3d, Core::Sys::Map::t_ChunkData &chunkData);
				void draw(Core::_Lights &lights);
				O3DSys() {
					Core::debug.log("Construct O3D {");
					uiRecordSize = 96;
					sTexDir = "./texture/o3d/";
					sFileDir = "./ply/";
					//idcount = -1;
					Core::debug.print(" Done ", Core::debug().GREEN);
					Core::debug.print("}\n");
				}
				~O3DSys() {
					Core::debug.log("Destroy O3D {");
					Core::debug.print(" Done ", Core::debug().GREEN);
					Core::debug.print("}\n");
				}
		};
		t_UniformLocations O3DSys::uniforms;

		void O3DSys::init(Core::_Lights &lights) {
			Core::debug.log("Init O3D {");
			if(!uniforms.bInit) shader->getUniform(GLS_PHONG, lights, uniforms);
			Core::debug.print(" Done ", Core::debug().GREEN);
			Core::debug.print("}\n");
		}

		void O3DSys::load(int x, int z, O3D::Data &o3d, Core::Noise::t_Noise *heightNoise) {

			float fX = (x-32768) * heightNoise->parent->chunk_size;
			float fZ = (z-32768) * heightNoise->parent->chunk_size;
			float chunkScale = heightNoise->parent->chunk_size/1024.0f;

			std::stringstream ssx, ssz;
			ssx << std::setfill ('0') << std::setw(4);
			ssx << std::hex << int(x);
			ssz << std::setfill ('0') << std::setw(4);
			ssz << std::hex << int(z);
			std::string mapName = ssx.str() + "-" + ssz.str();

			bool bReadResult;
			MemBlock memBlock;
			std::string loadFile;
			std::stringstream sStream;

//			//################################
//			//		Load Binary Object Data
			sStream.str("");
			sStream << "./region/prime/o3d/" << mapName << ".o3d";
			loadFile=sStream.str();
			bReadResult = readFile(loadFile, memBlock);		//Read the data file into memory

			if(bReadResult) {
				Core::debug.log("Load O3D: '"+mapName+"'");

				for (int d=0; d<memBlock.size; d+=uiRecordSize) {
					O3D::t_O3D_Item *newItem = new O3D::t_O3D_Item();

					newItem->id			= (	(unsigned int)(memBlock.buffer[0+d]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[0+d]&0x0F)*256 +
											(unsigned int)(memBlock.buffer[1+d]&0xF0)		+ (unsigned int)(memBlock.buffer[1+d]&0x0F) );

					newItem->pos.x		= (	(unsigned int)(memBlock.buffer[2+d]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[2+d]&0x0F)*256 +
											(unsigned int)(memBlock.buffer[3+d]&0xF0)		+ (unsigned int)(memBlock.buffer[3+d]&0x0F) );
					newItem->pos.x		= (newItem->pos.x * chunkScale) + fX;

					newItem->pos.z		= (	(unsigned int)(memBlock.buffer[4+d]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[4+d]&0x0F)*256 +
											(unsigned int)(memBlock.buffer[5+d]&0xF0)		+ (unsigned int)(memBlock.buffer[5+d]&0x0F) );
					newItem->pos.z		= (newItem->pos.z * chunkScale) + fZ;

					newItem->bvType		= _BOUNDING_VOLUME::_BOUNDING_VOLUME_TYPE(	(unsigned int)(memBlock.buffer[6+d]&0xF0) 	+ (unsigned int)(memBlock.buffer[6+d]&0x0F) );
					newItem->bV->iType	= newItem->bvType;

					// memBlock.buffer[7] unused

					newItem->pos.y		= 0.0f;
					newItem->pos.y		-= (__int16_t)((unsigned int)(memBlock.buffer[8+d]&0xF0) 	+ (unsigned int)(memBlock.buffer[8+d]&0x0F));
					newItem->pos.y		+= (__int16_t)((unsigned int)(memBlock.buffer[9+d]&0xF0) 	+ (unsigned int)(memBlock.buffer[9+d]&0x0F));
					newItem->pos.y		*= chunkScale;
					newItem->pos.y		+= Core::Noise::getNoise(newItem->pos.x, newItem->pos.z, heightNoise) + heightNoise->parent->chunk_height_offset;

					newItem->scale.x	= (	(unsigned int)(memBlock.buffer[10+d]&0x0F)*256	+ (unsigned int)(memBlock.buffer[10+d]&0xF0)*256 +
											(unsigned int)(memBlock.buffer[11+d]&0x0F)		+ (unsigned int)(memBlock.buffer[11+d]&0xF0) )*16;

					newItem->scale.y	= (	(unsigned int)(memBlock.buffer[12+d]&0x0F)*256	+ (unsigned int)(memBlock.buffer[12+d]&0xF0)*256 +
											(unsigned int)(memBlock.buffer[13+d]&0x0F)		+ (unsigned int)(memBlock.buffer[13+d]&0xF0) )*16;

					newItem->scale.z	= (	(unsigned int)(memBlock.buffer[14+d]&0x0F)*256	+ (unsigned int)(memBlock.buffer[14+d]&0xF0)*256 +
											(unsigned int)(memBlock.buffer[15+d]&0x0F)		+ (unsigned int)(memBlock.buffer[15+d]&0xF0) )*16;

					newItem->rot.x		= (	(unsigned int)(memBlock.buffer[16+d]&0xF0)*256	+ (unsigned int)(memBlock.buffer[16+d]&0x0F)*256 +
											(unsigned int)(memBlock.buffer[17+d]&0xF0)		+ (unsigned int)(memBlock.buffer[17+d]&0x0F) );

					newItem->rot.y		= (	(unsigned int)(memBlock.buffer[18+d]&0xF0)*256	+ (unsigned int)(memBlock.buffer[18+d]&0x0F)*256 +
											(unsigned int)(memBlock.buffer[19+d]&0xF0)		+ (unsigned int)(memBlock.buffer[19+d]&0x0F) );

					newItem->rot.z		= (	(unsigned int)(memBlock.buffer[20+d]&0xF0)*256	+ (unsigned int)(memBlock.buffer[20+d]&0x0F)*256 +
											(unsigned int)(memBlock.buffer[21+d]&0xF0)		+ (unsigned int)(memBlock.buffer[21+d]&0x0F) );

					std::string theImage = "";
					for (int count=22; count<60; count++) {
						if (memBlock.buffer[count+d]!=0) theImage+=memBlock.buffer[count+d];
						else break;
					}
					newItem->file = theImage;

					theImage = "";
					for (int count=60; count<uiRecordSize; count++) {
						if (memBlock.buffer[count+d]!=0) theImage+=memBlock.buffer[count+d];
						else break;
					}
					newItem->image = theImage;

					newItem->texture.Begin(4);		// Room for all 4 mappings (image, bump, spec, ambo)
					newItem->texture.Load(sTexDir, theImage, 0);

					o3d.add(newItem);
				}
				Core::debug.print("\n");
			}
		}

		void O3DSys::calc(O3D::Data &o3d, Core::Sys::Map::t_ChunkData &chunkData) {
			std::string loadFile;
			std::stringstream sStream;

			for(auto &item : o3d) {
				sStream.str("");
				sStream << sFileDir << item->file;
				loadFile=sStream.str();

				Core::debug.log("Calc O3D: '"+loadFile+"'\n");

				PLY_Loader pLoad;
				pLoad.load(loadFile);

				// ##############################
				// Get bounding volume ready
				// TODO: Only load bounding volume if bvType is not NONE
				item->bV->fPadding *= Core::gameVars->screen.fScale;
				item->bV->Start(item->scale);

				// Find min and max vertex positions, this is good for OBB only
				for (int i=0; i<pLoad.numVerts; i++) {
					item->bV->CheckMinMaxOBB(Vector3f(pLoad.vVerts[i][0]*Core::gameVars->screen.fScale, pLoad.vVerts[i][1]*Core::gameVars->screen.fScale, pLoad.vVerts[i][2]*Core::gameVars->screen.fScale));
				}

				// Figure out the zero point (center of model)
				item->bV->CalcOBB();

				// Find furthest point from center, needed for Sphere and Cylinder to completely contain model
				//for (int i=0; i<pLoad.numVerts; i++) {
				//	item->bV->CheckXYZ(Vector3f(pLoad.vVerts[i][0]*Core::gameVars->screen.fScale, pLoad.vVerts[i][1]*Core::gameVars->screen.fScale, pLoad.vVerts[i][2]*Core::gameVars->screen.fScale));
				//}
				item->bV->SetRotation(item->rot);

				Vector3f offsetPos = item->pos;
				offsetPos.x -= chunkData.chunk_size/2.0f;
				offsetPos.z -= chunkData.chunk_size/2.0f;
				item->pos = offsetPos;
				item->bV->SetPosition(offsetPos);
//				debug.log("  - bV Position = ("+std::to_string(offsetPos.x)+", "+std::to_string(offsetPos.y)+", "+std::to_string(offsetPos.z)+")\n");

				// ##############################
				// Apply transformations to objects now
				matrix->Push();
					matrix->SetIdentity();
					matrix->Rotate(Degrees(item->rot.x).toRadians(), -1.0, 0.0, 0.0);
					matrix->Rotate(Degrees(item->rot.y).toRadians(), 0.0, -1.0, 0.0);
					matrix->Rotate(Degrees(item->rot.z).toRadians(), 0.0, 0.0, -1.0);
					Matrix44f mTransform = matrix->GetModelView();
					for(int vert=0; vert<pLoad.numVerts; vert++) {
						pLoad.vVerts[vert][0] *= item->scale.x*Core::gameVars->screen.fScale;
						pLoad.vVerts[vert][1] *= item->scale.y*Core::gameVars->screen.fScale;
						pLoad.vVerts[vert][2] *= item->scale.z*Core::gameVars->screen.fScale;

						Vector4f vVertex = Vector4f(pLoad.vVerts[vert][0], pLoad.vVerts[vert][1], pLoad.vVerts[vert][2], 1.0f);
						Vector4f vTVertex = mTransform * vVertex;
						pLoad.vVerts[vert][0] = vTVertex.x;
						pLoad.vVerts[vert][1] = vTVertex.y;
						pLoad.vVerts[vert][2] = vTVertex.z;

						// Build AABB after rotations have been performed, but before translations
						item->bV->CheckMinMaxAABB(Vector3f(pLoad.vVerts[vert][0], pLoad.vVerts[vert][1], pLoad.vVerts[vert][2]));

						Vector4f vNormal = Vector4f(pLoad.vNorms[vert][0], pLoad.vNorms[vert][1], pLoad.vNorms[vert][2], 1.0f);
						Vector4f vTNormal = mTransform * vNormal;
						pLoad.vNorms[vert][0] = vTNormal.x;
						pLoad.vNorms[vert][1] = vTNormal.y;
						pLoad.vNorms[vert][2] = vTNormal.z;

						pLoad.vVerts[vert][0] += item->pos.x*Core::gameVars->screen.fScale;
						pLoad.vVerts[vert][1] += item->pos.y*Core::gameVars->screen.fScale;
						pLoad.vVerts[vert][2] += item->pos.z*Core::gameVars->screen.fScale;
					}
				matrix->Pop();
				item->bV->CalcAABB();
				item->bV->Finish();

				item->vao.Begin(GL_TRIANGLES, pLoad.numVerts, pLoad.numDrawVerts, 1);
				item->vao.CopyData(GLA_VERTEX, pLoad.vVerts);
				item->vao.CopyData(GLA_NORMAL, pLoad.vNorms);
				item->vao.CopyData(GLA_TEXTURE, pLoad.vCoords, 0);
				item->vao.CopyData(GLA_INDEX, pLoad.vIndex, pLoad.numDrawVerts);
				item->vao.End();
			}
		}










	} /* sys namespace*/
} /* Core namespace */
#endif /* _O3D_H_ */
