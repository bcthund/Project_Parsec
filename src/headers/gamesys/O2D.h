/*
 * O2D.h
 *
 *  Created on: Nov 1, 2010
 *      Author: bcthund
 */

#ifndef O2D_H_
#define O2D_H_

#include <iostream>
#include <sstream>

#include "../core/matrix.h"
#include "../core/shader.h"
#include "../core/core_functions.h"
#include "../core/vao.h"
#include "../core/texture.h"

/** \class _O2D
 *
 * Used to draw 2D billboarding objects to
 * the scene.
 *
 */

namespace Core {
	namespace GameSys {
		struct _O2DData {
			int   * blend;   		// The depth offset of the object
			float * r;   			// Rotation for static objects (events)
			float * x;   			// X Position of the object on the map (coord)
			float * y;    			// Y Calculated height
			float * z;    			// Z Position of the object on the map (coord)
			int   * id;    			// ID number, unique to this object (not used for tiles)
			float * imgW;			// Image width for the image this object uses
			float * imgH;			// Image height for the image this object uses
			float * distance;  		// The most current distance from this object
			std::string * image;	// Image name this object requests (texture)
			int idcount;   			// Actual objects loaded
			VAO * vao;
			Texture * texture;

			_O2DData() {
				blend 		= new int[1024];
				r 			= new float[1024];
				x 			= new float[1024];
				y 			= new float[1024];
				z 			= new float[1024];
				id 			= new int[1024];
				imgW 		= new float[1024];
				imgH 		= new float[1024];
				distance 	= new float[1024];
				image 		= new std::string[1024];
				idcount 	= -1;
				vao 		= new VAO[1024];
				texture		= new Texture[1024];
			}

			~_O2DData() {
				delete[] blend;
				delete[] r;
				delete[] x;
				delete[] y;
				delete[] z;
				delete[] id;
				delete[] imgW;
				delete[] imgH;
				delete[] distance;
				delete[] image;
				delete[] vao;
				delete[] texture;
			}
		};

		struct _O2DGroup {
			int iGroups;	// Number of groups
			int * iNum;			// number of items in this group === Number of instances
			int * image;
			VAO * vao;

			_O2DGroup() {
				iNum = nullptr;
				image = nullptr;
				iGroups = 0;
				vao = nullptr;
			}

			~_O2DGroup() {
				delete[] iNum;
				delete[] image;
				delete[] vao;
			}
		};

		class _O2D {
			private:
				Matrix_System 	* matrix;
				Shader_System 	* shader;
				_O2DData data;
				_O2DGroup group;		// For instancing
				//Texture texture;
				//VAO vao[64];
				//Vector4f tempColor,
				//		 currentColor,
				//		 gridCoord[64];
				uint uiRecordSize;
				std::string sTexDir;

			protected:

			public:
				_O2D(Matrix_System &m, Shader_System &s);
				~_O2D();
				bool init();
				bool load();
				bool calc();
				void draw(SHADER_PROGRAMS iShader, Core::_Lights &lights, bool bBB, bool bSort);
				//O2D_BASE(Atmosphere &a): atmosphere(a) {}
		};

		_O2D::_O2D(Matrix_System &m, Shader_System &s) {
			matrix = &m;
			shader = &s;
			uiRecordSize	= 60;
			sTexDir			= "./texture/o2d/";
		}

		_O2D::~_O2D() {
			Core::debug.log("Destroy O2D {");
			Core::debug.print(" Not Implemented ", Core::debug().RED);
			Core::debug.print("}\n");
		}

		bool _O2D::init() {
			Core::debug.log("Init O2D {");
			Core::debug.print(" Done ", Core::debug().GREEN);
			Core::debug.print("}\n");
			return true;
		}

		bool _O2D::load() {
			Core::debug.log("Load O2D {\n");
			Core::debug.logIncreaseIndent();
			bool bReadResult;
			MemBlock memBlock;
			std::string loadFile;
			std::stringstream sStream;

			int idcount=0;

			//################################
			//		Load Binary Object Data
			sStream.str("");
			sStream << "./region/prime/o2d/100.o2d";
			loadFile=sStream.str();

			bReadResult = readFile(loadFile, memBlock);		//Read the data file into memory
			if (!bReadResult) {
				sStream.str("");
				sStream << "./region/prime/o2d/0.o2d";
				loadFile=sStream.str();
				readFile(loadFile, memBlock);
			}

			if (memBlock.size <= 0) data.idcount = -1;
			for (int d=0; d<memBlock.size; d+=uiRecordSize) {
				data.idcount = idcount;

				data.id[idcount]			=	(	(unsigned int)(memBlock.buffer[0+d]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[0+d]&0x0F)*256 +
													(unsigned int)(memBlock.buffer[1+d]&0xF0)		+ (unsigned int)(memBlock.buffer[1+d]&0x0F) );

				data.x[idcount]				=	(	(unsigned int)(memBlock.buffer[2+d]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[2+d]&0x0F)*256 +
													(unsigned int)(memBlock.buffer[3+d]&0xF0)		+ (unsigned int)(memBlock.buffer[3+d]&0x0F) );

				data.z[idcount]				=	(	(unsigned int)(memBlock.buffer[4+d]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[4+d]&0x0F)*256 +
													(unsigned int)(memBlock.buffer[5+d]&0xF0)		+ (unsigned int)(memBlock.buffer[5+d]&0x0F) );

				// 6-7 not used

				data.blend[idcount]			=	(__int16_t)(	(unsigned int)(memBlock.buffer[8+d]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[8+d]&0x0F)*256 +
																(unsigned int)(memBlock.buffer[9+d]&0xF0)		+ (unsigned int)(memBlock.buffer[9+d]&0x0F) );

				data.imgW[idcount]		=	(	(unsigned int)(memBlock.buffer[10+d]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[10+d]&0x0F)*256 +
												(unsigned int)(memBlock.buffer[11+d]&0xF0)		+ (unsigned int)(memBlock.buffer[11+d]&0x0F) );

				data.imgH[idcount]		=	(	(unsigned int)(memBlock.buffer[12+d]&0xF0)*256 	+ (unsigned int)(memBlock.buffer[12+d]&0x0F)*256 +
												(unsigned int)(memBlock.buffer[13+d]&0xF0)		+ (unsigned int)(memBlock.buffer[13+d]&0x0F) );

				std::string tempImage = "";
				for (int count=14; count<uiRecordSize; count++) {
					if (memBlock.buffer[count+d]!=0) tempImage+=memBlock.buffer[count+d];
					else break;
				}
				data.image[idcount] = tempImage;

				// TODO: Check for duplicate images
				data.texture[idcount].Begin(1);		// 1 texture per O2D
				data.texture[idcount].Load(sTexDir, tempImage, 0);

				Core::debug.log("["+std::to_string(idcount)+"] "+tempImage+"\n", Core::debug().YELLOW);

				idcount++;
			}

			Core::debug.logDecreaseIndent();
			Core::debug.log("}\n");
			return true;
		}

		/*
		 * TODO: O2D INSTANCING
		 *
		 * This first thing that needs to be done to to this
		 *   is grouping the objects by texture. These
		 *   textures also need a new piece of data that
		 *   enables skewing.
		 *
		 * We already have a routine for setting up
		 *   the VAO with the appropriate data.
		 */

		bool _O2D::calc() {
			Core::debug.log("Calc O2D {");
			//int iItemCount[255]	= {0};		//Current Item count for group

			/*
			 * Texture coordinates
			 */
			Data2f vCoords[] = { {0.0, 0.0},
								 {0.0, 1.0},
								 {1.0, 0.0},
								 {1.0, 1.0} };

			/*
			 * TODO: Implement instancing again
			 *
			 * Need: a x,z grid of groups
			 * Need: groups == number of textures
			 *
			 * Have: Random list of items
			 */
//			if(Core::gameVars->screen.bInstance) {
//				for (int x=0; x<Core::gameVars->screen.iTerrainGrid; x++) {
//					for (int z=0; z<Core::gameVars->screen.iTerrainGrid; z++) {
//						cout << "Grid: [" << x << "][" << z << "]" << endl;
//						// data.image[count]
//						// Core::gameVars->texture.sprite.Get();
//						// data.idcount;
//
//
//						/*
//						 * iGroups = Total number of texture groups
//						 * iTex[GROUP] = actual texture id for the group
//						 * iItem[GROUP] = number of items in this group
//						 */
//						int iGroups = 0,
//							iTex[255] = {-1},
//							iItems[255] = {0};
//
//						// Determine number of object texture IDs and values
//						for( int iCount=0; iCount <= data.idcount; iCount++ ) {
//
//							//cout << "Checking Texture: " << data.image[iCount] << "...";
//							bool bTagged = false;
//							for(int t = 0; t<255; t++) {		// Iterate through our list of max texture groups
//								if(iTex[t] == -1) {
//									//cout << "Not Tagged...";
//									bTagged = false;
//									break;		// If we have reached an unset value then just exit, texture group not counted
//								}
//								else if(iTex[t] == Core::gameVars->texture.sprite.Get(data.image[iCount])) {	// If the texture group list contains the texture id then...
//									//cout << "Already Tagged...";
//									bTagged = true;				// Texture already counted, don't add it to the list
//									break;						// We have an answer, exit the loop
//								}
//							}
//
//							/*
//							 * If we found an uncounted texture group
//							 *   then add it to the list
//							 */
//							if(!bTagged) {
//								//cout << "Adding Texture " << data.image[iCount] << "...";
//								iTex[iGroups] = Core::gameVars->texture.sprite.Get(data.image[iCount]);		// Record texture unit
//								//cout << "Adding Texture: " << data.image[iCount] << " : " << Core::gameVars->texture.sprite.Get(data.image[iCount]) << endl;
//								iGroups++;
//							}
//							else {
//								//cout << "Texture Skipped" << endl;
//							}
//						}
//
//						/*
//						 * Determine the total number of items in each group
//						 */
//						for( int iCount=0; iCount <= data.idcount; iCount++ ) {		// Iterate through all obejcts
//							for(int iGroup=0; iGroup<iGroups; iGroup++) {					// Iterate through all groups
//								if(Core::gameVars->texture.sprite.Get(data.image[iCount]) == iTex[iGroup]) {	// Does the current objects texture id match the current group texture id?
//									iItems[iGroup]++;										// It does, so add to the total number of objects in this group
//									//iItemId[iGroup] = iCount;
//								}
//							}
//						}
//
//						/*
//						 * Get the actual item ID's for each item
//						 *   in each group.
//						 */
//						int * iItemIds[iGroups];	// Up to 255 items per group
//						for(int iGroup=0; iGroup<iGroups; iGroup++) {		// Iterate through all groups
//							iItemIds[iGroup] = new int[iItems[iGroup]];		// Create array with the size of items in the group
//
//							int iCurrent = 0;
//							for( int iCount=0; iCount <= data.idcount; iCount++ ) {		// Iterate through all items
//								if(Core::gameVars->texture.sprite.Get(data.image[iCount]) == iTex[iGroup]) {		// If the items textureId matches the group textureId
//									// Then add the items ID to the list
//									iItemIds[iGroup][iCurrent] = iCount;
//									iCurrent++;
//								}
//							}
//						}
//
//						// Debugging message
//						// This all looks correct
//	//					for(int i=0; i<iGroups; i++) {
//	//						for(int t=0; t<iItems[i]; t++) {
//	//							cout << "   Group[" << i << "][" << t << "]: Image=" << Core::gameVars->texture.sprite.Get(iTex[i]) << " : " << iTex[i] << "; (" << data.x[iItemIds[i][t]] << ", " << data.z[iItemIds[i][t]] << "); (" << data.imgW[iItemIds[i][t]] << ", " << data.imgH[iItemIds[i][t]] << ")" << endl;
//	//						}
//	//					}
//	//					cout << "--------------" << endl;
//						for(int i=0; i<iGroups; i++) {
//							//for(int t=0; t<iItems[i]; t++) {
//								cout << "   Group[" << i << "]: Image=" << Core::gameVars->texture.sprite.Get(iTex[i]) << endl;
//							//}
//						}
//
//						/*
//						 * Create VAO's
//						 */
//						group[x][z].vao = new VAO[iGroups];		//New VAO with size == number of groups
//
//						//Store the number of groups
//						group[x][z].iGroups = iGroups;
//
//						// Create array for holding number of items
//						group[x][z].iNum = new int[iGroups];
//
//						// Create array for holding texture id's
//						group[x][z].image = new int[iGroups];
//
//						// Default throwaway vertex
//						Data4f vVerts[]	=	{	{	0.0f,	0.0f,	0.0f,	0.0f	},
//													{	0.0f,	0.0f,	0.0f,	0.0f	}	};
//
//						// Loop through all groups
//						for(int iGroup=0; iGroup<iGroups; iGroup++) {		// Iterate through all groups
//	//						cout << "   Group: " << iGroup;
//							/*
//							 * Temporary vector
//							 * Holds width and height data
//							 */
//							Data4f * vExtra = new Data4f[iItems[iGroup]];	// Extra data == number of items in group
//
//	//						cout << ", Items: " << iItems[iGroup];
//							/*
//							 * Temporary vector
//							 *
//							 * Holds actual position data
//							 */
//							Data4f * vOffset = new Data4f[iItems[iGroup]];	// Offset data == number of items in group
//
//							// Store the number of items in the group
//							group[x][z].iNum[iGroup] = iItems[iGroup];
//							group[x][z].image[iGroup] = iTex[iGroup];
//
//	//						cout << ", Num: " << group[x][z].iNum[iGroup];
//	//						cout << ", Tex: " << group[x][z].image[iGroup] << endl;
//
//							//bool bValid = true;
//							int i = 0;
//							for (int count=0; count < iItems[iGroup]; count++) {
//								//bValid=true;
//	//							cout << "      Item #" << count << "...";
//								float fW = data.imgW[iItemIds[iGroup][count]]/2;
//								float fH = data.imgH[iItemIds[iGroup][count]];
//								float fT = map.getHeight(abs(data.x[iItemIds[iGroup][count]]), abs(data.z[iItemIds[iGroup][count]]), x, z);
//								// TODO: If the height is below water then discard this object
//								//if(fT<atmosphere.water.fFloor) bValid = false;
//
//								if(fT>=atmosphere.water.fFloor) {
//									// Vertex 1
//									vOffset[i][0] = data.x[iItemIds[iGroup][count]]*Core::gameVars->screen.iScale;
//									vOffset[i][1] = fT*Core::gameVars->screen.iScale;
//									vOffset[i][2] = data.z[iItemIds[iGroup][count]]*Core::gameVars->screen.iScale;
//									vOffset[i][3] = 0.0f;
//
//									vExtra[i][0] = fW;
//									vExtra[i][1] = fH;
//									vExtra[i][2] = 0.0f;			// TODO: Add blending into this instancing routine
//									vExtra[i][3] = 0.0f;			// TODO: Use flora as example to draw O2D with proper billboarding
//
//									++i;
//								}
//								//iC++;
//	//							cout << "(" << vOffset[count][0] << ", " << vOffset[count][2] << ")...";
//	//							cout << "Done" << endl;
//							}
//							iItems[iGroup] = i;
//
//							//group[x][z].vao[iGroup].Begin(GL_LINES, 2, 1, iItems[iGroup]);
//							group[x][z].vao[iGroup].Begin(GL_LINES, 2, 1, iItems[iGroup]);
//							group[x][z].vao[iGroup].CopyData(GLA_VERTEX, vVerts);
//							group[x][z].vao[iGroup].CopyData(GLA_POSITION, vOffset);
//							group[x][z].vao[iGroup].CopyData(GLA_EXTRA, vExtra);
//							//data.vao.CopyData(GLA_TEXTURE, vCoords, 0);		//Generate texture coordinates in shader
//							group[x][z].vao[iGroup].End();
//						}
//					}
//	//				cout << endl;
//				}
//			}

			/*
			 * Original, Non-Instancing Routine
			 */
			// Temporary vector hold the points of each object
			//Vector4f * vVerts2 = new Vector4f[data.idcount];

			// Temporary vector holds size data
			//Vector4f * vSize = new Vector4f[data.idcount];

			for (int count=0; count <= data.idcount; count++) {
				float fW = (data.imgW[count]/2)*Core::gameVars->screen.fScale;
				float fH = (data.imgH[count])*Core::gameVars->screen.fScale;
				float fT = 0.0f;				// Get mapHeight here when a world is present

				// Fourth field used for randomization offset
				Data4f vVerts[]	=	{	{	-fW,	fH,		0.0, (float)(count+1)	},
										{	-fW,	0.0f,	0.0, (float)(count+1)	},
										{	 fW,	fH,		0.0, (float)(count+1)	},
										{	 fW,	0.0f,	0.0, (float)(count+1)	}	};

				data.y[count] = fT*Core::gameVars->screen.fScale;

				// TODO: May need to redo the bUpdate
				//if (bUpdate) {
				//	new(&data.vao[count]) VAO();	//We need to create new VAO objects for this to work
				//	data.vao[count].Begin(GL_TRIANGLE_STRIP, 4, 1);
				//	data.vao[count].CopyData(GLA_VERTEX, vVerts);
				//	data.vao[count].CopyData(GLA_TEXTURE, vCoords, 0);
				//	data.vao[count].End();
				//}
				//else {
					data.vao[count].Begin(GL_TRIANGLE_STRIP, 4, 4, 1);
					data.vao[count].CopyData(GLA_VERTEX, vVerts);
					data.vao[count].CopyData(GLA_TEXTURE, vCoords, 0);
					data.vao[count].End();
				//}
			}

			Core::debug.print(" Done ", Core::debug().GREEN);
			Core::debug.print("}\n");
			return true;
		}


		/*
		void O2D_BASE::draw(int iShader, bool bSort=false) {
			glDisable(GL_CULL_FACE);
			shader.use(iShader);

			// Standard Drawing routine (blending with shader)
			for (int x=0; x<Core::gameVars->screen.iTerrainGrid; x++) {
				for (int z=0; z<Core::gameVars->screen.iTerrainGrid; z++) {
					//std::sort();
					for (int count=0; count <= data.idcount; count++) {

						/*
						 * Are we above the sea level?
						 * Prevent drawing 2D objects below water
						 *
						 * WE MAY REMOVE THIS FOR FUTURE FUNCTIONALITY
						 *//*
						//if (data.y[count] > Core::gameVars->world.water.iHeight) {

							matrix.Push();
								//matrix.SetTransform();
								shader.getUniform(atmosphere, iShader);
								Core::gameVars->texture.sprite.Set(data.image[count]);
								data.vao2.Draw(GLM_DRAW_ARRAYS_INSTANCED, 0, data.idcount);
							matrix.Pop();
						//}
					}
				}
			}
			glEnable(GL_CULL_FACE);
		}
		*/

		void _O2D::draw(SHADER_PROGRAMS iShader, Core::_Lights &lights, bool bBB=true, bool bSort=false) {
			//bool bInstance = true;
			glDisable(GL_CULL_FACE);
			shader->use(iShader);

			Vector3f	vCamPos;
			vCamPos[0] = -Core::gameVars->player.active->transform.pos[0];
			vCamPos[1] = 0.0f;
			vCamPos[2] = -Core::gameVars->player.active->transform.pos[2];

			Vector3f	vUp = { 0.0, 1.0, 0.0};
			Vector3f	vLook, vRight;

			/*
			 * TODO: Distance sorting
			 * TODO: Instancing
			 */

	//		if(!Core::gameVars->screen.bInstance) {
	//			if(bSort) {
	//				/*
	//				 * Setup distance sorting
	//				 * This is a bubble sort, VERY SLOW! Over 50% framerate drop!
	//				 */
	//				Vector4i objects[Core::gameVars->screen.iTerrainGrid*Core::gameVars->screen.iTerrainGrid*257];
	//				int numObjects=0;
	//				for (int x=0; x<Core::gameVars->screen.iTerrainGrid; x++) {
	//					for (int z=0; z<Core::gameVars->screen.iTerrainGrid; z++) {
	//						for (int count=0; count <= data.idcount; count++) {
	//							data.distance[count] = Hypot(-Core::gameVars->player.active->transform.pos[0], -Core::gameVars->player.active->transform.pos[2], data.x[count], data.z[count]);
	//							objects[numObjects][0] = data.distance[count];
	//							objects[numObjects][1] = x;
	//							objects[numObjects][2] = z;
	//							objects[numObjects][3] = count;
	//							numObjects++;
	//						}
	//					}
	//				}
	//
	//				for (int i = 0; i < numObjects; i++) {
	//					for (int j = 0; j < i; j++) {
	//						if (objects[i][0] > objects[j][0]) {
	//							Vector4i temp = { objects[i][0], objects[i][1], objects[i][2], objects[i][3] }; //swap
	//							objects[i] = objects[j];
	//							objects[j] = temp;
	//							// Updated to use new Vector4i class type over typedef
	//							//memcpy(objects[i], objects[j], sizeof(Vector4i));
	//							//memcpy(objects[j], temp, sizeof(Vector4i));
	//
	//						}
	//					}
	//				}
	//
	//				/*
	//				 * Draw with distance sorting
	//				 */
	//				int count;
	//				int x;
	//				int z;
	//				for (int i = 0; i < numObjects; i++) {
	//					count = objects[i][3];
	//					x = objects[i][1];
	//					z = objects[i][2];
	//
	//					matrix.Push();
	//						Vector3f	vObjPos = { float(data.x[count]), float(data.blend[count]), float(data.z[count]) };
	//						//Diff(vLook, vCamPos, vObjPos);
	//						vLook = vCamPos - vObjPos;
	//						Normalize(vLook);
	//						Cross(vRight, vUp, vLook);
	//
	//						Matrix44f	mTemp = {	vRight[0], vRight[1], vRight[2], 0.0f,
	//												0.0f, 1.0f, 0.0f, 0.0f,
	//												vLook[0], vLook[1], vLook[2], 0.0f,
	//												vObjPos[0], vObjPos[1], vObjPos[2], 1.0f };
	//
	//						matrix.Apply(mTemp);
	//						matrix.Translate(0.0f, data.y[count], 0.0f);
	//						matrix.SetTransform();
	//						shader.getUniform(atmosphere, iShader);
	//
	//						Core::gameVars->texture.sprite.Set(data.image[count]);
	//
	//						data.vao[count].Draw();
	//					matrix.Pop();
	//				}
	//			}
	//			else {
					// Standard Drawing routine (blending with shader)
	//				for (int x=0; x<Core::gameVars->screen.iTerrainGrid; x++) {
	//					for (int z=0; z<Core::gameVars->screen.iTerrainGrid; z++) {
							//std::sort();
							for (int count=0; count <= data.idcount; count++) {
									matrix->Push();


										matrix->Rotate(Core::gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
										matrix->Rotate(Core::gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
										matrix->Translate(Core::gameVars->player.active->transform.pos[0], Core::gameVars->player.active->transform.pos[1], Core::gameVars->player.active->transform.pos[2]);
										matrix->SetTransform();




										Vector3f	vObjPos = { float(data.x[count])*Core::gameVars->screen.fScale,
																(float(data.blend[count])+float(data.y[count]))*Core::gameVars->screen.fScale,
																float(data.z[count])*Core::gameVars->screen.fScale
															  };

										shader->getUniform(iShader, &lights, 2, vObjPos, vCamPos);
										glActiveTexture(0);
										data.texture[count].Set(data.image[count]);
										data.vao[count].Draw();

									matrix->Pop();
							}
	//					}
	//				}
	//			}
	//		}
		// TODO: Reimplement instancing
	//		else {
	//			//cout << "Instanced Drawing..." << endl;
	//			for (int x=0; x<Core::gameVars->screen.iTerrainGrid; x++) {
	//				for (int z=0; z<Core::gameVars->screen.iTerrainGrid; z++) {
	//					//std::sort();
	//					for(int iGroup=0; iGroup<group[x][z].iGroups; iGroup++) {
	//						//for(int iItem=0; iItem<group[x][z].iNum[iGroup]; iItem++) {
	//						//cout << "Group: " << iGroup << ", Tex: " << group[x][z].image[iGroup];
	//							matrix.Push();
	//								shader.getUniform(atmosphere, iShader);
	//								Core::gameVars->texture.sprite.Set(group[x][z].image[iGroup]);
	//								group[x][z].vao[iGroup].Draw(GLM_DRAW_ARRAYS_INSTANCED, 0, group[x][z].iNum[iGroup]);
	//							matrix.Pop();
	//						//}
	//					}
	//				}
	//			}
	//		}
			glEnable(GL_CULL_FACE);
		}
	}
}

#endif /* O2D_H_ */
