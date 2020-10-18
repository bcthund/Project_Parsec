/*
 * O2D.h
 *
 *  Created on: Nov 1, 2010
 *      Author: bcthund
 */

#ifndef O2D_H_
#define O2D_H_

//#include <iostream>
//#include <sstream>
//#include "../core/matrix.h"
//#include "../core/shader.h"
#include "../core/core_functions.h"
//#include "../core/vao.h"
//#include "../core/texture.h"
#include "O2D_Data.h"

/** \class _O2D
 *
 * Used to draw 2D billboarding objects to
 * the scene.
 *
 */

namespace Core {
	namespace Sys {


//		namespace O2D {
//			struct Data {
//				int   * blend;   		// The depth offset of the object
//				float * r;   			// Rotation for static objects (events)
//				float * x;   			// X Position of the object on the map (coord)
//				float * y;    			// Y Calculated height
//				float * z;    			// Z Position of the object on the map (coord)
//				int   * id;    			// ID number, unique to this object (not used for tiles)
//				float * imgW;			// Image width for the image this object uses
//				float * imgH;			// Image height for the image this object uses
//				float * distance;  		// The most current distance from this object
//				std::string * image;	// Image name this object requests (texture)
//				int idcount;   			// Actual objects loaded
//				VAO * vao;
//				Texture * texture;
//
//				Data() {
//					blend 		= new int[1024];
//					r 			= new float[1024];
//					x 			= new float[1024];
//					y 			= new float[1024];
//					z 			= new float[1024];
//					id 			= new int[1024];
//					imgW 		= new float[1024];
//					imgH 		= new float[1024];
//					distance 	= new float[1024];
//					image 		= new std::string[1024];
//					idcount 	= -1;
//					vao 		= new VAO[1024];
//					texture		= new Texture[1024];
//				}
//
//				~Data() {
//					delete[] blend;
//					delete[] r;
//					delete[] x;
//					delete[] y;
//					delete[] z;
//					delete[] id;
//					delete[] imgW;
//					delete[] imgH;
//					delete[] distance;
//					delete[] image;
//					delete[] vao;
//					delete[] texture;
//				}
//			};
//		} /* namespace O2D */












		/*
		 * TODO: Rework the O2DSys class to be like the MapSys class
		 *
		 * 	- The load() method should load into a given chunk reference according to a given noise pattern
		 * 	- The noise elevation method from MapSys needs to be moved to noise class
		 * 	- draw() should remain here if possible to keep WorldMap simple
		 * 	- Need to have threshold settings for noise, possibly based on another noise function such as the terrain moisture and altitude
		 * 	- As a side note, billboarding doesn't change affect normal causing lighting issues that need to be addressed
		 *
		 */

		class O2DSys {
			private:
				static t_UniformLocations uniforms;
//				Matrix_System 	* matrix;
//				Shader_System 	* shader;
//				O2DSysData data;
//				O2DSysGroup group;		// For instancing
				//Texture texture;
				//VAO vao[64];
				//Vector4f tempColor,
				//		 currentColor,
				//		 gridCoord[64];
//				uint uiRecordSize;
//				std::string sTexDir;
				bool bInit;

			protected:

			public:
//				O2DSys(Matrix_System &m, Shader_System &s);
				O2DSys();
				~O2DSys();
				bool init(Core::_Lights &lights);
//				void load(int x, int z, Map::Data &chunk, O2D::Data &o2d, Core::Noise::t_Noise *noise);
//				void load(int x, int z, O2D::Data &o2d, Core::Noise::t_Noise *noise, Core::Noise::t_Noise *heightNoise);
				void load(int x, int z, O2D::Data &o2d, Core::Noise::t_Noise *noise, Core::Noise::t_Noise *heightNoise, Core::Noise::t_Noise *moistureNoise);

//				bool compare_O2D_Distance(const O2D::t_O2D_Item &a, const O2D::t_O2D_Item &b);
				void calc(O2D::Data &o2d, Vector3f pos, int terrain_size);
				//void draw(SHADER_PROGRAMS iShader, Core::_Lights &lights, bool bBB, bool bSort);
				void draw(Core::_Lights &lights, bool bBB, bool bSort);
				//O2D_BASE(Atmosphere &a): atmosphere(a) {}
		};
		t_UniformLocations O2DSys::uniforms;

//		O2DSys::O2DSys(Matrix_System &m, Shader_System &s) {
		O2DSys::O2DSys() {
			Core::debug.log("Construct O2DSys {");
			bInit = false;
			Core::debug.print(" Done ", Core::debug().GREEN);
			Core::debug.print("}\n");
		}

		O2DSys::~O2DSys() {
			Core::debug.log("Destroy O2DSys {");
			Core::debug.print(" Done ", Core::debug().GREEN);
			Core::debug.print("}\n");
		}

		bool O2DSys::init(Core::_Lights &lights) {
			Core::debug.log("Init O2DSys {");
//			if(!uniforms.bInit) shader->getUniform(GLS_PHONGO2DSys, lights, uniforms);
			Core::debug.print(" Done ", Core::debug().GREEN);
			Core::debug.print("}\n");
			return true;
		}

//		void MapSys::load(int x, int z, Map::Data &chunk, int index, Core::Noise::t_Noise *noise) {
//		void MapSys::load(int x, int z, Map::Data &chunk, Core::Noise::t_Noise *noise) {
		/*
		 *	- x/z is the current chunk coordinates, provided in the range of 0-65535 and remapped to -32768 to +32768
		 *	- chunk is used to get height placement for O2D
		 *	- chunk can also be used to get moisture data (need a way to specify this, or is it automatic? What if we want to use this for other 2D objects?)
		 *	- o2d is a reference to the chunk data to be returned
		 *	- noise is the noise generator for this chunk
		 */
//		void O2DSys::load(int x, int z, Map::Data &chunk, O2D::Data &o2d, Core::Noise::t_Noise *noise) {
		void O2DSys::load(int x, int z, O2D::Data &o2d, Core::Noise::t_Noise *noise, Core::Noise::t_Noise *heightNoise, Core::Noise::t_Noise *moistureNoise) {
//			Core::debug.log("Load O2D {\n");
//			Core::debug.logIncreaseIndent();

			x = (x-32768) * noise->parent->chunk_size;
			z = (z-32768) * noise->parent->chunk_size;

			float SIZE			= noise->parent->chunk_size;
			int VERTEX_COUNT	= noise->parent->chunk_resolution+1;
//				int iTexScale		= noise->parent->tex_scale;
//				float fHeightOffset	= noise->parent->chunk_height_offset;
//				float DELTA			= noise->parent->delta;
//				chunk.vData = new Data3f[VERTEX_COUNT * VERTEX_COUNT];

//				float SIZE			= noise->parent->chunk_size;
//				int VERTEX_COUNT	= noise->parent->chunk_resolution+1;
//				int iTexScale		= noise->parent->tex_scale;
//				float fHeightOffset	= noise->parent->chunk_height_offset;
//				float DELTA			= noise->parent->delta;
//
//				parent.numVerts = VERTEX_COUNT * VERTEX_COUNT;
//				parent.numDrawVerts = 6*(VERTEX_COUNT-1)*(VERTEX_COUNT-1);
//				parent.vVerts = new Data3f[parent.numVerts];
//				parent.vNorms = new Data3f[parent.numVerts];
//				parent.vCoords = new Data2f[parent.numVerts];
//				parent.vIndex = new GLuint[parent.numDrawVerts];
//				parent.vData = new Data3f[parent.numVerts];

			/*
			 * TODO: Process to Implement
			 * 	Preliminary:
			 * 		[X] Rework O2DData for VectorMap use
			 * 		[X] Move getElevation() from MapSys to getNoise() in Noise class
			 * 		[ ] Use random value based on x/z seed for width/height. Seed should allow repeatability.
			 * 		[X] Sample noise at vertex positions
			 * 		[X] Check if value above threshold
			 * 		[X] Add O2D object
			 * 		[X] Get height from heightNoise (this might be expensive)
			 * 		[X] Ignore objects below 0.0 + chunk_height_offset (water level)
			 * 		[X] Check moisture noise
			 * 		[X] Use moisture to determine threshold (treeNoise > 1-(moistureNoise/10))
			 * 		[ ] Add randomization to x/z coordinates
			 * 		[X] Height should modify the threshold as well, higher altitudes have less trees
			 * 		[ ] Sea Level offset should be added (customizable)
			 * 		[ ] Only load trees for chunks in range
			 * 		[ ] Distance Sorting
			 * 			[ ] only sort current to start
			 * 			[ ] sort only objects in front of player
			 * 			[ ] sort adacent chunks
			 */

			long vertexPointer = 0;
			for(int i=0;i<VERTEX_COUNT;i++){
				for(int j=0;j<VERTEX_COUNT;j++){

					float fX = ((float)j/((float)VERTEX_COUNT - 1) * SIZE) + x;
					float fZ = ((float)i/((float)VERTEX_COUNT - 1) * SIZE) + z;

					float fHeight = Core::Noise::getNoise(fX, fZ, heightNoise) + noise->parent->chunk_height_offset;
					if(fHeight>100.0f) {
						float fNoise = Core::Noise::getNoise(fX, fZ, noise);
						float fMoisture = Core::Noise::getNoise(fX, fZ, moistureNoise);

						// (vVertex.y+2500)/50000
						float fHeightNorm = 1.0f-(fHeight+0.0f)/50000.0f;
//						if(fNoise>((1.0f-(fMoisture/10.0f)*fHeightNorm) )) {
						if(fNoise>((1.0f-((fMoisture/5.0f)-0.2f)*fHeightNorm) )) {
//							debug.log("HeightNorm = "+std::to_string(fHeightNorm)+"\n");
							O2D::t_O2D_Item *newItem = new O2D::t_O2D_Item();
							newItem->x = fX;
							newItem->z = fZ;
							newItem->y = fHeight;
							newItem->w = 1000.0f;
							newItem->h = 3000.0f;
							o2d.add(newItem);
						}
					}
					//debug.print("["+std::to_string(noiseVal)+"]");

//					getElevation(chunk.vVerts[vertexPointer][0]+x, chunk.vVerts[vertexPointer][2]+z, noise) + fHeightOffset;

//					// Vertex
//					chunk.vVerts[vertexPointer][0] = ((float)j/((float)VERTEX_COUNT - 1) * SIZE);
//					chunk.vVerts[vertexPointer][2] = ((float)i/((float)VERTEX_COUNT - 1) * SIZE);
//					chunk.vVerts[vertexPointer][1] = getElevation(chunk.vVerts[vertexPointer][0]+x, chunk.vVerts[vertexPointer][2]+z, noise) + fHeightOffset;
//
//					// Clear extra data
//					chunk.vData[vertexPointer][0] = 0.0f;
//					chunk.vData[vertexPointer][1] = 0.0f;
//					chunk.vData[vertexPointer][2] = 0.0f;
//					chunk.vData[vertexPointer][2] = chunk.vVerts[vertexPointer][1] - fHeightOffset;
//
//					// Determine normal using Delta points
//					// TODO: Update this to use less lookups
//					//			- In the building loop, use the already calculated points to determine normal from geometry instead of noise
//					Vector3f modelXOffset,
//							 modelYOffset,
//							 modelXGrad,
//							 modelYGrad,
//							 A, B, C, BA, CA, Dir, Norm;
//
//							A = chunk.vVerts[vertexPointer];
//
//							B.x = A.x+DELTA;
//							B.z = A.z+DELTA;
//							B.y = getElevation(B.x+x, B.z+z, noise) + fHeightOffset;
//
//							C.x = A.x+DELTA;
//							C.z = A.z-DELTA;
//							C.y = getElevation(C.x+x, C.z+z, noise) + fHeightOffset;
//
//							BA = B - A;
//							CA = C - A;
//							Dir = Core::gmath.Cross(BA, CA);
//							Norm = Dir/Dir.length();
//
//					// Normals - What is expected to work but DOES NOT
//					chunk.vNorms[vertexPointer][0] = Norm.x;
//					chunk.vNorms[vertexPointer][1] = Norm.y;
//					chunk.vNorms[vertexPointer][2] = Norm.z;
//
//					// Texture
//					chunk.vCoords[vertexPointer][0] = (float)j/((float)VERTEX_COUNT - 1) * (float)iTexScale;
//					chunk.vCoords[vertexPointer][1] = (float)i/((float)VERTEX_COUNT - 1) * (float)iTexScale;
//
//					// Update the lowest point on the chunk
//					chunk.lowestHeight = fmin(chunk.lowestHeight, fmin(chunk.vVerts[vertexPointer][1], fmin(B.y, C.y)));

					vertexPointer++;
				}
//				debug.print("\n\n");
			}

//			long pointer = 0;
//			for(uint gz=0;gz<VERTEX_COUNT-1;gz++){
//				for(uint gx=0;gx<VERTEX_COUNT-1;gx++){
//
//					// TODO: Calculate Normals Here, per triangle (2-triangles here per quad)
//					uint topLeft = (gz*VERTEX_COUNT)+gx;
//					uint topRight = topLeft + 1;
//					uint bottomLeft = ((gz+1)*VERTEX_COUNT)+gx;
//					uint bottomRight = bottomLeft + 1;
//					chunk.vIndex[pointer++] = topLeft;			//std::cout << "[(" << chunk.vIndex[pointer-1];
//					chunk.vIndex[pointer++] = bottomLeft;		//std::cout << ", " << chunk.vIndex[pointer-1];
//					chunk.vIndex[pointer++] = topRight;			//std::cout << ", " << chunk.vIndex[pointer-1];
//					chunk.vIndex[pointer++] = topRight;			//std::cout << ")(" << chunk.vIndex[pointer-1];
//					chunk.vIndex[pointer++] = bottomLeft;		//std::cout << ", " << chunk.vIndex[pointer-1];
//					chunk.vIndex[pointer++] = bottomRight;		//std::cout << ", " << chunk.vIndex[pointer-1] << ")]" << std::endl;
//				}
//			}






//			bool bReadResult;
//			MemBlock memBlock;
//			std::string loadFile;
//			std::stringstream sStream;
//
//			int idcount=0;
//
//			//################################
//			//		Load Binary Object Data
//			sStream.str("");
//			sStream << "./region/prime/o2d/100.o2d";
//			loadFile=sStream.str();
//
//			bReadResult = readFile(loadFile, memBlock);		//Read the data file into memory
//			if (!bReadResult) {
//				sStream.str("");
//				sStream << "./region/prime/o2d/0.o2d";
//				loadFile=sStream.str();
//				readFile(loadFile, memBlock);
//			}
//
//			if (memBlock.size <= 0) data.idcount = -1;
//			for (int d=0; d<memBlock.size; d+=uiRecordSize) {
//				data.idcount = idcount;
//
//				data.id[idcount]			=	(	(unsigned int)(memBlock.buffer[0+d]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[0+d]&0x0F)*256 +
//													(unsigned int)(memBlock.buffer[1+d]&0xF0)		+ (unsigned int)(memBlock.buffer[1+d]&0x0F) );
//
//				data.x[idcount]				=	(	(unsigned int)(memBlock.buffer[2+d]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[2+d]&0x0F)*256 +
//													(unsigned int)(memBlock.buffer[3+d]&0xF0)		+ (unsigned int)(memBlock.buffer[3+d]&0x0F) );
//
//				data.z[idcount]				=	(	(unsigned int)(memBlock.buffer[4+d]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[4+d]&0x0F)*256 +
//													(unsigned int)(memBlock.buffer[5+d]&0xF0)		+ (unsigned int)(memBlock.buffer[5+d]&0x0F) );
//
//				// 6-7 not used
//
//				data.blend[idcount]			=	(__int16_t)(	(unsigned int)(memBlock.buffer[8+d]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[8+d]&0x0F)*256 +
//																(unsigned int)(memBlock.buffer[9+d]&0xF0)		+ (unsigned int)(memBlock.buffer[9+d]&0x0F) );
//
//				data.imgW[idcount]		=	(	(unsigned int)(memBlock.buffer[10+d]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[10+d]&0x0F)*256 +
//												(unsigned int)(memBlock.buffer[11+d]&0xF0)		+ (unsigned int)(memBlock.buffer[11+d]&0x0F) );
//
//				data.imgH[idcount]		=	(	(unsigned int)(memBlock.buffer[12+d]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[12+d]&0x0F)*256 +
//												(unsigned int)(memBlock.buffer[13+d]&0xF0)		+ (unsigned int)(memBlock.buffer[13+d]&0x0F) );
//
//				std::string tempImage = "";
//				for (int count=14; count<uiRecordSize; count++) {
//					if (memBlock.buffer[count+d]!=0) tempImage+=memBlock.buffer[count+d];
//					else break;
//				}
//				data.image[idcount] = tempImage;
//
//				// TODO: Check for duplicate images
//				data.texture[idcount].Begin(1);		// 1 texture per O2D
//				data.texture[idcount].Load(sTexDir, tempImage, 0);
//
//				Core::debug.log("["+std::to_string(idcount)+"] "+tempImage+"\n", Core::debug().YELLOW);
//
//				idcount++;
//			}

//			Core::debug.logDecreaseIndent();
//			Core::debug.log("}\n");
		}

//		bool O2DSys::compare_O2D_Distance(const O2D::t_O2D_Item &a, const O2D::t_O2D_Item &b)
//		{
//			return a.distance < b.distance;
//		}

		bool compare_O2D_Distance(const O2D::t_O2D_Item *a, const O2D::t_O2D_Item *b)
		{
			return a->distance < b->distance;
		}

		void O2DSys::calc(O2D::Data &o2d, Vector3f pos, int terrain_size) {
//			Core::debug.log("Calc O2D {\n");
//			Core::debug.logIncreaseIndent();

			// Distance Sorting
			// TODO: Need to sort chunks as well
			for(auto &item : o2d ) {
//				// Convert player coords to grid chunks
//				Vector2f vA;
//				vA.x = -pos.x/terrain_size;
//				vA.y = -pos.z/terrain_size;
//
//				// Rounding
//				if(vA.x<0) vA.x-=1.0f; else vA.x+=1.0f;
//				if(vA.y<0) vA.y-=1.0f; else vA.y+=1.0f;
//
//				// Calculate distance in grid chunks
//				Vector2f vB;
//				vB.x = int(x-32768);
//				vB.y = int(z-32768);
//
//				distance = (vB-vA).length();

				Vector2f vA;
				vA.x = pos.x;
				vA.y = pos.z;

				Vector2f vB;
				vB.x = item->x;
				vB.y = item->z;

				item->distance = (vB-vA).length();
//				debug.log("Tree@("+std::to_string(item->x)+", "+std::to_string(item->z)+"); Distance = "+std::to_string(item->distance)+"\n");
			}

//			std::sort(o2d.begin(), o2d.end(), compare_O2D_Distance);

			Data2f vCoords[] = { {0.0, 0.0},
								 {0.0, 1.0},
								 {1.0, 0.0},
								 {1.0, 1.0} };

			for(auto &item : o2d ) {
//				debug.log("CALC: Tree at ("+std::to_string(item->x)+", "+std::to_string(item->y)+", "+std::to_string(item->z)+") with dimensions ("+std::to_string(item->w)+", "+std::to_string(item->h)+")\n", debug().purple);

				float fW = item->w/2.0f;
				float fH = item->h/2.0f;

				// FIXME: What is this and is it still used? (Fourth field used for randomization offset)
				Data4f vVerts[]	=	{	{	-fW,	fH,		0.0,	1.0f	},
										{	-fW,	0.0f,	0.0,	1.0f	},
										{	 fW,	fH,		0.0,	1.0f	},
										{	 fW,	0.0f,	0.0,	1.0f	}	};

				item->vao.Begin(GL_TRIANGLE_STRIP, 4, 4, 1);
				item->vao.CopyData(GLA_VERTEX, vVerts);
				item->vao.CopyData(GLA_TEXTURE, vCoords, 0);
				item->vao.End();
			}

//			/*
//			 * Texture coordinates
//			 */

//
//			for (int count=0; count <= data.idcount; count++) {
//				float fW = (data.imgW[count]/2)*Core::gameVars->screen.fScale;
//				float fH = (data.imgH[count])*Core::gameVars->screen.fScale;
//				float fT = 0.0f;				// Get mapHeight here when a world is present
//
//				// Fourth field used for randomization offset
//
//				data.y[count] = fT*Core::gameVars->screen.fScale;
//
//				data.vao[count].Begin(GL_TRIANGLE_STRIP, 4, 4, 1);
//				data.vao[count].CopyData(GLA_VERTEX, vVerts);
//				data.vao[count].CopyData(GLA_TEXTURE, vCoords, 0);
//				data.vao[count].End();
//			}
//
//			Core::debug.print(" Done ", Core::debug().GREEN);
//			Core::debug.logDecreaseIndent();
//			Core::debug.print("}\n");
//			return true;
		}


		void O2DSys::draw(Core::_Lights &lights, bool bBB=true, bool bSort=false) {
//			glDisable(GL_CULL_FACE);
//			shader->use(GLS_PHONGO2DSys);
//
//			Vector3f	vCamPos;
//			vCamPos[0] = -Core::gameVars->player.active->transform.pos[0];
//			vCamPos[1] = 0.0f;
//			vCamPos[2] = -Core::gameVars->player.active->transform.pos[2];
//
//			Vector3f	vUp = { 0.0, 1.0, 0.0};
//			Vector3f	vLook, vRight;
//
//			// TODO: Distance sorting
//
//			glActiveTexture(0);
//			for (int count=0; count <= data.idcount; count++) {
//				matrix->Push();
//					matrix->Rotate(Core::gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
//					matrix->Rotate(Core::gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
//					matrix->Translate(Core::gameVars->player.active->transform.pos[0], Core::gameVars->player.active->transform.pos[1], Core::gameVars->player.active->transform.pos[2]);
//					matrix->SetTransform();
//
//					Vector3f	vObjPos = { float(data.x[count])*Core::gameVars->screen.fScale,
//											(float(data.blend[count])+float(data.y[count]))*Core::gameVars->screen.fScale,
//											float(data.z[count])*Core::gameVars->screen.fScale
//										  };
//
//					shader->vars.GLS_PHONGO2DSys.vObjPos = vObjPos;
//					shader->vars.GLS_PHONGO2DSys.vCamPos = vCamPos;
//					shader->setUniform(GLS_PHONGO2DSys, lights, uniforms);
//					data.texture[count].Set(data.image[count]);
//					data.vao[count].Draw();
//
//				matrix->Pop();
//			}
//			glEnable(GL_CULL_FACE);
		}





























































	} /* namespace Sys */
} /* namespace Core */

#endif /* O2D_H_ */
