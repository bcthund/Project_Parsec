/*
 * System.h
 *
 *  Created on: Feb 21, 2011
 *      Author: bcthund
 */

#ifndef ANIMATIONS_H_
#define ANIMATIONS_H_

#define GL_GLEXT_PROTOTYPES 1		// Enable core profile
#define GL_POINT_SPRITE 0x8861		// Hack to enable Point Sprites thus enabling gl_PointCoord operation
#include "gl4_5/glcorearb.h"
#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF

#include "../core/core_functions.h"
//#include "../core/matrix.h"
//#include "../core/shader.h"
//#include "../core/texture.h"
//#include "../core/timer.h"
//#include "../core/vao.h"
#include "../core/audiosys.h"

namespace Core {
	namespace GameSys {
		class AnimationSys {
			private:
				//bool bAnimating;							// Is an animation currently playing? Used to prevent player input during animation.
				Timer timer;
				Texture texture;
				int iLoaded;										// Total number of loaded animations
				AudioSys *audioSys;
				uint uiNumTextures,
					 uiRecordSize;
				std::string sFilename,
							sDir,
							sTexDir;

				struct _AnimationList {
					uint			id;								// Animation id
					std::string		image;							// Animation image file
					uint			frames;							// Number of frames for this animation
					uint			rate;							// Update rate of animation in milliseconds
					int				iSample;					// Sound to play with animation
					Core::VAO		*vao;						// Custom VAO built from "frames" value (will be an array the size of the number of frames)

					_AnimationList() {
						id						= 0;
						iSample       			= 999;
						frames					= 0;
						rate					= 1000;
						vao						= nullptr;
					}
				} animation[128];									// 128 animations to load

				struct _RunningAnimations {
					uint		id;								// ID of animation playing
					uint		currentFrame;					// Current frame of animation
					bool		bActive;						// Animation is active, used to draw first frame without regard to timer;
																	// 	* Also use to signal Animation slot is finished/available for a new animation to play
					int			loop;
					float		ticks;							// ??? current frame start ticks
					Vector2f	size;							// Size of animation set with startAnimation()
					Vector3f	camera,							// Billboard direction set with startAnimation()
								target;							// Location to draw animation set with startAnimation()

					_RunningAnimations() {
						id						= 0;
						currentFrame			= 0;
						bActive					= false;
						loop					= 1;
						ticks					= 0;
					}
				} running[32],			// Lets only allow 32 concurrent animations
				  world[128];			// We load animations in the world here, allow up to 128 for now




			protected:
				friend class GameSys;
				//friend class AudioSys;

			public:
				AnimationSys(AudioSys &a);
				~AnimationSys();
//				// TODO: Load these associations from file, the number is equal to the id of the animation which is also equal to its array index (typically iA in this file)
//				struct _ANIMATIONS {
//					__uint16_t	SWORD_HIT	= 0,
//								BLOCK		= 1,
//								GLANCE		= 2,
//								DODGE		= 3,
//								DEFLECT		= 4;
//				} ANIMATIONS;
				bool init();
				bool load();
				bool calc();
				/*
				 * size/x,y...........Specifies the size of the animation
				 * camera.............Location to billboard animation towards
				 * target.............Location to draw animation at
				 * iA.................Animation id number to draw
				 * bMoveOrigin(true)..Translate center location for world sprites (world sprites have origin at bottom center, animations at true center, this fixes that unless a specific location is wanted for the animation)
				 * rate(60)...........Time between frame updates in milliseconds, 60 by default. Setting this value overwrites the loaded value.
				 */
				//void startAnimation(float x, float y, Vector3f camera, Vector3f target, int iA, __uint8_t loop, bool bMoveOrigin);
				//void startAnimation(Vector2f size, Vector3f camera, Vector3f target, int iA, __uint8_t loop, bool bMoveOrigin);
				void startAnimation(	float w,
										float h,
										Vector3f camera,
										Vector3f target,
										int iA,
										int loop,
										uint rate,
										int iSample,
										bool bMoveOrigin);				// TODO: Implement world animations, add bWorld to parameters before bMoveOrigin

				void startAnimation(	Vector2f size,
										Vector3f camera,
										Vector3f target,
										int iA,
										int loop,
										uint rate,
										int iSample,
										bool bMoveOrigin);				// TODO: Implement world animations, add bWorld to parameters before bMoveOrigin

				bool drawWorld(float fScale, bool bVerticalBB = false);
				bool drawWorld(int iA, float fScale, bool bVerticalBB = false);
				bool isAnimating(bool bWorld=false);
				//bool drawWorld(Shader_System &shader, Vector2f wh, Vector3f camera, Vector3f target, int iA);
		};

AnimationSys::AnimationSys(/*Matrix_System *m,*/ AudioSys &a) {
		//	cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! CONSTRUCT ANIMATION SYSTEM !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
		//	// This doesn't seem to be getting called for some reason, use init() instead
		////	timer.start();
		////	//texture.Begin(128);		// Maximum of 128 animations
		////	iLoaded = 0;

			//cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! CONSTRUCT ANIMATION SYSTEM !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
			audioSys		= &a;
			//matrix			= m;
			uiNumTextures	= 64;
			uiRecordSize	= 32;
			sFilename		= "animations.bin";
			sDir			= "./system/";
			sTexDir			= "./texture/animations/";
			iLoaded			= 0;
		}

		AnimationSys::~AnimationSys() {
			for(int iA=0; iA<iLoaded; ++iA) {
				delete[] animation[iA].vao;
			}
		}

		bool AnimationSys::isAnimating(bool bWorld) {
			bool bAnimating = false;
			for(int i=0; i<32; ++i) {
				if(running[i].bActive) {
					bAnimating = true;
					break;										// We don't care if there is any more animations in progress, one is enough
				}
			}
			return bAnimating;
		}

		bool AnimationSys::init() {
			//            .................................................................Done
			std::cout << "Init Animations..................................................";
			timer.start();
			texture.Begin(uiNumTextures);
			iLoaded = 0;
			std::cout << "Done" << std::endl;
			return true;
		}

		bool AnimationSys::load() {
			try {
				//            .................................................................Done
				std::cout << "Load Animations..................................................";
				MemBlock memBlock;
				std::string theImage;

				readFile((sDir+sFilename), memBlock);

				iLoaded = 0;
				for (uint d=0; d<memBlock.size; d+=uiRecordSize) {
					int id			= 0,
						frames		= 0;

					id		= (__uint16_t)( (__uint8_t)(memBlock.buffer[0+d])*256 + (__uint8_t)(memBlock.buffer[1+d]) );
					frames	= (__uint16_t)( (__uint8_t)(memBlock.buffer[2+d])*256 + (__uint8_t)(memBlock.buffer[3+d]) );

					theImage = "";
					for (int i=4; i<32; i++)
						if (memBlock.buffer[i+d]!=0) theImage+=(unsigned char)memBlock.buffer[i+d];
						else break;

					//if (Core::gameVars.debug.load) cout << "[" << id << "] " << theImage << std::endl;

//					std::cout << std::endl;
//					std::cout << "ID     = " << id << std::endl;
//					std::cout << "Frames = " << frames << std::endl;
//					std::cout << "Image  = " << theImage << std::endl << std::endl;

					animation[iLoaded].id		= id;
					animation[iLoaded].frames	= frames;
					animation[iLoaded].image	= theImage;
					texture.Load(sTexDir, theImage, id, false, GL_NEAREST);

					++iLoaded;
				}
				std::cout << "Done" << std::endl;
				return true;
			}
			catch(...) {
				std::cout << "Failed" << std::endl;
				return false;
			}
		}

		bool AnimationSys::calc() {
			try {
				//            .................................................................Done
				std::cout << "Calc Animations..................................................";
				for(int iA=0; iA<iLoaded; ++iA) {
					Vector4f gridCoord[animation[iA].frames];
					float iy1=0.0000f,
								iy2=1.0f/float(animation[iA].frames);
					for(int i=0;i<animation[iA].frames;i++) {
						gridCoord[i][0] = 0.0f;
						gridCoord[i][1] = iy1;
						gridCoord[i][2] = 1.0f;
						gridCoord[i][3] = iy1+=iy2;
					}

					animation[iA].vao = new VAO[animation[iA].frames];

					//cout << "Calculating Texture Coords" << std::endl;
					for (int iF=0; iF<animation[iA].frames; ++iF) {

						//Standard font quad, CCW:CAB-BDC
						float iHalf_W = 0.5f;
						float iHalf_H = 0.5f;

						// Origin at center (better for animations)
						Data3f vVerts[] = { {-iHalf_W, -iHalf_H, 0},
											{ iHalf_W,  iHalf_H, 0},
											{-iHalf_W,  iHalf_H, 0},
											{-iHalf_W, -iHalf_H, 0},
											{ iHalf_W, -iHalf_H, 0},
											{ iHalf_W,  iHalf_H, 0}		};

		// Origin at botton center
		//				Vector3f vVerts[] = { {-iHalf_W,	0.0f,	0},
		//															{ iHalf_W,	1.0f,	0},
		//															{-iHalf_W,  1.0f,	0},
		//															{-iHalf_W,	0.0f,	0},
		//															{ iHalf_W,	0.0f,	0},
		//															{ iHalf_W,  1.0f,	0}		};

						Data2f vTexture[11];
						vTexture[0][0] = gridCoord[iF][0];
						vTexture[0][1] = gridCoord[iF][3];
						vTexture[1][0] = gridCoord[iF][2];
						vTexture[1][1] = gridCoord[iF][1];
						vTexture[2][0] = gridCoord[iF][0];
						vTexture[2][1] = gridCoord[iF][1];
						vTexture[3][0] = gridCoord[iF][0];
						vTexture[3][1] = gridCoord[iF][3];
						vTexture[4][0] = gridCoord[iF][2];
						vTexture[4][1] = gridCoord[iF][3];
						vTexture[5][0] = gridCoord[iF][2];
						vTexture[5][1] = gridCoord[iF][1];

						animation[iA].vao[iF].Begin(GL_TRIANGLES, 6, 6, 1);
						animation[iA].vao[iF].CopyData(GLA_VERTEX, vVerts);
						animation[iA].vao[iF].CopyData(GLA_TEXTURE, vTexture, 0);
						animation[iA].vao[iF].End();
					}
				}
				std::cout << "Done" << std::endl;
				return true;
			}
			catch(...) {
				std::cout << "Failed" << std::endl;
				return false;
			}
		}

		void AnimationSys::startAnimation(float w, float h, Vector3f camera, Vector3f target, int iA, int loop, uint rate, int iSample=999, bool bMoveOrigin=true) {
			Vector2f size = {w, h};
			startAnimation(size, camera, target, iA, loop, rate, iSample, bMoveOrigin);
		}

		void AnimationSys::startAnimation(Vector2f size, Vector3f camera, Vector3f target, int iA, int loop, uint rate, int iSample=999, bool bMoveOrigin=false) {
			for(int i=0; i<32; ++i) {
				if(!running[i].bActive) {
					running[i].id			= iA;												// Store the active animation id
					running[i].bActive		= true;												// Flag the animation as active
					animation[iA].rate		= rate;												// Update the requested rate !!! WARNING !!! Overwrites ALL animations playing with this id
					running[i].ticks		= timer.get_ticks();								// Get the current clock time
					running[i].currentFrame	= 0;												// Start at frame 0
					running[i].loop			= loop;												// Set the number of loops
					animation[iA].iSample	= iSample;											// Store the sound effect to play
					running[i].camera		= camera;
					running[i].target		= target;
					running[i].size			= size;
					if(bMoveOrigin) running[i].target[1] = running[i].target[1]-(size[1]/2);	// Move the animation origin for sprites (move to bottom center)
					//drawWorld();																// Go ahead and draw the first frame now
					return;																		// Finished, we only setup the animation ONE time in the first available slot
				}
			}
		}

		/*
		 * Draw all active animations
		 */
		bool AnimationSys::drawWorld(float fScale, bool bVerticalBB) {
			for(int iA=0; iA<32; ++iA) {
				if(running[iA].bActive) {

					// Play sound first or we may miss it
					if((running[iA].currentFrame==0) && (animation[running[iA].id].iSample!=999)) audioSys->playSound(animation[running[iA].id].iSample);

					bool bDraw = true;
					if(timer.get_ticks()>=(running[iA].ticks+animation[running[iA].id].rate)) {
						++running[iA].currentFrame;
						running[iA].ticks		= timer.get_ticks();
					}

					if(running[iA].currentFrame >= animation[running[iA].id].frames) {
						--running[iA].loop;
						if(running[iA].loop>0) running[iA].currentFrame = 0;
						else {
							running[iA].bActive = false;
							bDraw = false;
						}
					}

					if(bDraw) drawWorld(iA, fScale, bVerticalBB);
				}
			}
			return false;
		}

		bool AnimationSys::drawWorld(int iA, float fScale, bool bVerticalBB) {
			glDisable(GL_CULL_FACE);
			//glDisable(GL_DEPTH_TEST);
			//glEnable(GL_POLYGON_OFFSET_FILL);
			//glPolygonOffset(-0.5f, -0.1f);

		// If not already positioned properly, this code can be used
		//	matrix->Push();
		//		matrix->Rotate(Core::gameVars.player.active->transform.rot[0], 1.0, 0.0, 0.0);
		//		matrix->Rotate(Core::gameVars.player.active->transform.rot[1], 0.0, 1.0, 0.0);
		//		matrix->Translate(Core::gameVars.player.active->transform.pos[0]*Core::gameVars.screen.iScale, (Core::gameVars.player.active->transform.pos[1]-Core::gameVars.player.active->transform.currentHeight), Core::gameVars.player.active->transform.pos[2]*Core::gameVars.screen.iScale);
		//		//matrix->Translate(Core::gameVars.player.active->transform.pos[0], map.getHeight(Core::gameVars.player.active->transform.pos[0], Core::gameVars.player.active->transform.pos[2])-Core::gameVars.player.active->transform.currentHeight, Core::gameVars.player.active->transform.pos[2]);
		//		matrix->SetTransform();

			matrix->Push();

				matrix->Rotate(Core::gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
				matrix->Rotate(Core::gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
				matrix->Translate(Core::gameVars->player.active->transform.pos[0], Core::gameVars->player.active->transform.pos[1], Core::gameVars->player.active->transform.pos[2]);

				shader->use(GLS_FONT);

				Vector3f vCamPos;
				vCamPos[0] = -(running[iA].camera[0]*fScale);
				vCamPos[1] = 0.0f;
				vCamPos[2] = -(running[iA].camera[2]*fScale);
				Vector3f	vUp = { 0.0, 1.0, 0.0};
				Vector3f	vLook, vRight, vObjPos;
				float fY = 0.0f;
				if (bVerticalBB) {
					vObjPos = Vector3f( float(running[iA].target[0]*fScale), float(running[iA].target[1]*fScale), float(running[iA].target[2]*fScale) );
					//vObjPos = vTarget;
					fY = 0.0f;
				}
				else {
					vObjPos = Vector3f( float(running[iA].target[0]*fScale), 0.0f, float(running[iA].target[2]*fScale) );
					//vObjPos = vTarget;
					fY = (running[iA].target[1]*fScale);
				}

				vLook = vCamPos - vObjPos;
				Core::gmath.Normalize(vLook);
				Core::gmath.Cross(vRight, vUp, vLook);

				Matrix44f	mLook = {	vRight[0],	vRight[1],	 vRight[2],		0.0f,
											 0.0f,		 1.0f,		  0.0f,		0.0f,
										 vLook[0],	 vLook[1],	  vLook[2],		0.0f,
									   vObjPos[0],		   fY,	vObjPos[2],		1.0f	};

				matrix->Push();
					matrix->Apply(mLook);
					matrix->Scale(running[iA].size[0]*fScale, running[iA].size[1]*fScale, 0.0f);
					matrix->SetTransform();
					shader->getUniform(GLS_FONT);

					//texture.Set(animation[iA].image);
					texture.Set(animation[running[iA].id].image);
					animation[running[iA].id].vao[running[iA].currentFrame].Draw();
				matrix->Pop();
			matrix->Pop();

			//glPolygonOffset(1.0f, 1.0f);
			//glDisable(GL_POLYGON_OFFSET_FILL);
			//glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			return true;
		}
	}
}
#endif /* ANIMATIONS_H_ */
