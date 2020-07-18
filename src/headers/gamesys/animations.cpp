#include <iostream>

#include "../gl4/glcorearb.h"

#include "../core/core_functions.h"
//#include "../core/types.h"
#include "../core/audiosys.h"
#include "../core/matrix.h"
#include "../core/shader.h"

#include "animations.h"

//#include "gameVars.h"

namespace Core {
	namespace GameSys {
//		AnimationSys::AnimationSys(/*Matrix_System *m,*/ AudioSys &a) {
//		//	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! CONSTRUCT ANIMATION SYSTEM !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
//		//	// This doesn't seem to be getting called for some reason, use init() instead
//		////	timer.start();
//		////	//texture.Begin(128);		// Maximum of 128 animations
//		////	iLoaded = 0;
//
//			//cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! CONSTRUCT ANIMATION SYSTEM !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
//			audioSys		= &a;
//			//matrix			= m;
//			uiNumTextures	= 64;
//			uiRecordSize	= 32;
//			sFilename		= "animations.bin";
//			sDir			= "./system/";
//			sTexDir			= "./texture/animations/";
//			iLoaded			= 0;
//		}
//
//		AnimationSys::~AnimationSys() {
//			for(int iA=0; iA<iLoaded; ++iA) {
//				delete[] animation[iA].vao;
//			}
//		}
//
//		bool AnimationSys::isAnimating(bool bWorld) {
//			bool bAnimating = false;
//			for(int i=0; i<32; ++i) {
//				if(running[i].bActive) {
//					bAnimating = true;
//					break;										// We don't care if there is any more animations in progress, one is enough
//				}
//			}
//			return bAnimating;
//		}
//
//		bool AnimationSys::init() {
//			//            .................................................................Done
//			std::cout << "Init Animations..................................................";
//			timer.start();
//			texture.Begin(uiNumTextures);
//			iLoaded = 0;
//			std::cout << "Done" << std::endl;
//			return true;
//		}
//
//		bool AnimationSys::load() {
//			try {
//				//            .................................................................Done
//				std::cout << "Load Animations..................................................";
//				MemBlock memBlock;
//				std::string theImage;
//
//				readFile((sDir+sFilename), memBlock);
//
//				iLoaded = 0;
//				for (uint d=0; d<memBlock.size; d+=uiRecordSize) {
//					int id			= 0,
//						frames		= 0;
//
//					id		= (__uint16_t)( (__uint8_t)(memBlock.buffer[0+d])*256 + (__uint8_t)(memBlock.buffer[1+d]) );
//					frames	= (__uint16_t)( (__uint8_t)(memBlock.buffer[2+d])*256 + (__uint8_t)(memBlock.buffer[3+d]) );
//
//					theImage = "";
//					for (int i=4; i<32; i++)
//						if (memBlock.buffer[i+d]!=0) theImage+=(unsigned char)memBlock.buffer[i+d];
//						else break;
//
//					//if (Core::gameVars.debug.load) cout << "[" << id << "] " << theImage << std::endl;
//
//					std::cout << std::endl;
//					std::cout << "ID     = " << id << std::endl;
//					std::cout << "Frames = " << frames << std::endl;
//					std::cout << "Image  = " << theImage << std::endl << std::endl;
//
//					animation[iLoaded].id		= id;
//					animation[iLoaded].frames	= frames;
//					animation[iLoaded].image	= theImage;
//					texture.Load(sTexDir, theImage, id, false, GL_NEAREST);
//
//					++iLoaded;
//				}
//				std::cout << "Done" << std::endl;
//				return true;
//			}
//			catch(...) {
//				std::cout << "Failed" << std::endl;
//				return false;
//			}
//		}
//
//		bool AnimationSys::calc() {
//			try {
//				//            .................................................................Done
//				std::cout << "Calc Animations..................................................";
//				for(int iA=0; iA<iLoaded; ++iA) {
//					Vector4f gridCoord[animation[iA].frames];
//					float iy1=0.0000f,
//								iy2=1.0f/float(animation[iA].frames);
//					for(int i=0;i<animation[iA].frames;i++) {
//						gridCoord[i][0] = 0.0f;
//						gridCoord[i][1] = iy1;
//						gridCoord[i][2] = 1.0f;
//						gridCoord[i][3] = iy1+=iy2;
//					}
//
//					animation[iA].vao = new VAO[animation[iA].frames];
//
//					//cout << "Calculating Texture Coords" << std::endl;
//					for (int iF=0; iF<animation[iA].frames; ++iF) {
//
//						//Standard font quad, CCW:CAB-BDC
//						float iHalf_W = 0.5f;
//						float iHalf_H = 0.5f;
//
//						// Origin at center (better for animations)
//						Data3f vVerts[] = { {-iHalf_W, -iHalf_H, 0},
//											{ iHalf_W,  iHalf_H, 0},
//											{-iHalf_W,  iHalf_H, 0},
//											{-iHalf_W, -iHalf_H, 0},
//											{ iHalf_W, -iHalf_H, 0},
//											{ iHalf_W,  iHalf_H, 0}		};
//
//		// Origin at botton center
//		//				Vector3f vVerts[] = { {-iHalf_W,	0.0f,	0},
//		//															{ iHalf_W,	1.0f,	0},
//		//															{-iHalf_W,  1.0f,	0},
//		//															{-iHalf_W,	0.0f,	0},
//		//															{ iHalf_W,	0.0f,	0},
//		//															{ iHalf_W,  1.0f,	0}		};
//
//						Data2f vTexture[11];
//						vTexture[0][0] = gridCoord[iF][0];
//						vTexture[0][1] = gridCoord[iF][3];
//						vTexture[1][0] = gridCoord[iF][2];
//						vTexture[1][1] = gridCoord[iF][1];
//						vTexture[2][0] = gridCoord[iF][0];
//						vTexture[2][1] = gridCoord[iF][1];
//						vTexture[3][0] = gridCoord[iF][0];
//						vTexture[3][1] = gridCoord[iF][3];
//						vTexture[4][0] = gridCoord[iF][2];
//						vTexture[4][1] = gridCoord[iF][3];
//						vTexture[5][0] = gridCoord[iF][2];
//						vTexture[5][1] = gridCoord[iF][1];
//
//						animation[iA].vao[iF].Begin(GL_TRIANGLES, 6, 6, 1);
//						animation[iA].vao[iF].CopyData(GLA_VERTEX, vVerts);
//						animation[iA].vao[iF].CopyData(GLA_TEXTURE, vTexture, 0);
//						animation[iA].vao[iF].End();
//					}
//				}
//				std::cout << "Done" << std::endl;
//				return true;
//			}
//			catch(...) {
//				std::cout << "Failed" << std::endl;
//				return false;
//			}
//		}
//
//		void AnimationSys::startAnimation(float w, float h, Vector3f camera, Vector3f target, int iA, int loop, uint rate, int iSample=999, bool bMoveOrigin=true) {
//			Vector2f size = {w, h};
//			startAnimation(size, camera, target, iA, loop, rate, iSample, bMoveOrigin);
//		}
//
//		void AnimationSys::startAnimation(Vector2f size, Vector3f camera, Vector3f target, int iA, int loop, uint rate, int iSample=999, bool bMoveOrigin=false) {
//			for(int i=0; i<32; ++i) {
//				if(!running[i].bActive) {
//					running[i].id			= iA;												// Store the active animation id
//					running[i].bActive		= true;												// Flag the animation as active
//					animation[iA].rate		= rate;												// Update the requested rate !!! WARNING !!! Overwrites ALL animations playing with this id
//					running[i].ticks		= timer.get_ticks();								// Get the current clock time
//					running[i].currentFrame	= 0;												// Start at frame 0
//					running[i].loop			= loop;												// Set the number of loops
//					animation[iA].iSample	= iSample;											// Store the sound effect to play
//					running[i].camera		= camera;
//					running[i].target		= target;
//					running[i].size			= size;
//					if(bMoveOrigin) running[i].target[1] = running[i].target[1]-(size[1]/2);	// Move the animation origin for sprites (move to bottom center)
//					//drawWorld();																// Go ahead and draw the first frame now
//					return;																		// Finished, we only setup the animation ONE time in the first available slot
//				}
//			}
//		}
//
//		/*
//		 * Draw all active animations
//		 */
//		bool AnimationSys::drawWorld(float fScale, bool bVerticalBB) {
//			for(int iA=0; iA<32; ++iA) {
//				if(running[iA].bActive) {
//
//					// Play sound first or we may miss it
//					if((running[iA].currentFrame==0) && (animation[running[iA].id].iSample!=999)) audioSys->playSound(animation[running[iA].id].iSample);
//
//					bool bDraw = true;
//					if(timer.get_ticks()>=(running[iA].ticks+animation[running[iA].id].rate)) {
//						++running[iA].currentFrame;
//						running[iA].ticks		= timer.get_ticks();
//					}
//
//					if(running[iA].currentFrame >= animation[running[iA].id].frames) {
//						--running[iA].loop;
//						if(running[iA].loop>0) running[iA].currentFrame = 0;
//						else {
//							running[iA].bActive = false;
//							bDraw = false;
//						}
//					}
//
//					if(bDraw) drawWorld(iA, fScale, bVerticalBB);
//				}
//			}
//			return false;
//		}
//
//		bool AnimationSys::drawWorld(int iA, float fScale, bool bVerticalBB) {
//			glDisable(GL_CULL_FACE);
//			//glDisable(GL_DEPTH_TEST);
//			//glEnable(GL_POLYGON_OFFSET_FILL);
//			//glPolygonOffset(-0.5f, -0.1f);
//
//		// If not already positioned properly, this code can be used
//		//	matrix->Push();
//		//		matrix->Rotate(Core::gameVars.player.active->transform.rot[0], 1.0, 0.0, 0.0);
//		//		matrix->Rotate(Core::gameVars.player.active->transform.rot[1], 0.0, 1.0, 0.0);
//		//		matrix->Translate(Core::gameVars.player.active->transform.pos[0]*Core::gameVars.screen.iScale, (Core::gameVars.player.active->transform.pos[1]-Core::gameVars.player.active->transform.currentHeight), Core::gameVars.player.active->transform.pos[2]*Core::gameVars.screen.iScale);
//		//		//matrix->Translate(Core::gameVars.player.active->transform.pos[0], map.getHeight(Core::gameVars.player.active->transform.pos[0], Core::gameVars.player.active->transform.pos[2])-Core::gameVars.player.active->transform.currentHeight, Core::gameVars.player.active->transform.pos[2]);
//		//		matrix->SetTransform();
//
//			matrix->Push();
//
//				matrix->Rotate(gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
//				matrix->Rotate(gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
//				matrix->Translate(gameVars.player.active->transform.pos[0], Core::gameVars.player.active->transform.pos[1], Core::gameVars.player.active->transform.pos[2]);
//
//				shader->use(GLS_FONT);
//
//				Vector3f vCamPos;
//				vCamPos[0] = -(running[iA].camera[0]*fScale);
//				vCamPos[1] = 0.0f;
//				vCamPos[2] = -(running[iA].camera[2]*fScale);
//				Vector3f	vUp = { 0.0, 1.0, 0.0};
//				Vector3f	vLook, vRight, vObjPos;
//				float fY = 0.0f;
//				if (bVerticalBB) {
//					vObjPos = Vector3f( float(running[iA].target[0]*fScale), float(running[iA].target[1]*fScale), float(running[iA].target[2]*fScale) );
//					//vObjPos = vTarget;
//					fY = 0.0f;
//				}
//				else {
//					vObjPos = Vector3f( float(running[iA].target[0]*fScale), 0.0f, float(running[iA].target[2]*fScale) );
//					//vObjPos = vTarget;
//					fY = (running[iA].target[1]*fScale);
//				}
//
//				vLook = vCamPos - vObjPos;
//				Core::gmath.Normalize(vLook);
//				Core::gmath.Cross(vRight, vUp, vLook);
//
//				Matrix44f	mLook = {	vRight[0],	vRight[1],	 vRight[2],		0.0f,
//											 0.0f,		 1.0f,		  0.0f,		0.0f,
//										 vLook[0],	 vLook[1],	  vLook[2],		0.0f,
//									   vObjPos[0],		   fY,	vObjPos[2],		1.0f	};
//
//				matrix->Push();
//					matrix->Apply(mLook);
//					matrix->Scale(running[iA].size[0]*fScale, running[iA].size[1]*fScale, 0.0f);
//					matrix->SetTransform();
//					shader->getUniform(GLS_FONT);
//
//					//texture.Set(animation[iA].image);
//					texture.Set(animation[running[iA].id].image);
//					animation[running[iA].id].vao[running[iA].currentFrame].Draw();
//				matrix->Pop();
//			matrix->Pop();
//
//			//glPolygonOffset(1.0f, 1.0f);
//			//glDisable(GL_POLYGON_OFFSET_FILL);
//			//glEnable(GL_DEPTH_TEST);
//			glEnable(GL_CULL_FACE);
//			return true;
//		}
	}
}
