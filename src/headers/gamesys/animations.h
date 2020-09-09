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
#include "../core/texture.h"
#include "../core/audiosys.h"
#include "../gamesys/GUI/GUI_Constraint.h"

namespace Core {
	class t_AnimationItem2D {
		public:
			uint		id;								// ID of animation playing
			uint		currentFrame;					// Current frame of animation
			bool		bActive;						// Animation is active, used to draw first frame without regard to timer;
			bool		bIsPaused;
			int			loop;
			int			currentLoop;
			float		ticks;							// ??? current frame start ticks
			Vector2f	size;							// Size of animation set with startAnimation()
			bool		bDraw;
			uint		rate;							// Update rate of animation in milliseconds
			int			iSample;						// Sound to play with animation
			bool		bSamplePlayed;
			bool		bAutoDestruct;

			// Needs a parent reference, but parent is template
//			void start()	{}
//			void pause()	{}
//			void stop()		{}
//			void update()	{}

			t_AnimationItem2D() {
				id				= 0;
				currentFrame	= 0;
				bActive			= false;
				bIsPaused		= false;
				loop			= 1;
				currentLoop		= 1;
				ticks			= 0;
				bDraw			= false;
				rate			= 100;
				iSample			= -1;
				bSamplePlayed	= false;
				bAutoDestruct	= false;
			}
	};

	class t_AnimationItem3D : public t_AnimationItem2D {
		public:
			Vector3f	*camera,						// Billboard direction set with startAnimation()
						*target;						// Location to draw animation set with startAnimation()
			bool		bLocalTarget;

			void setCameraTarget(Vector3f *vCam, Vector3f *vTar) {
				camera = vCam;
				target = vTar;
				bLocalTarget = false;
			}

			void setCameraTarget(Vector3f *vCam, Vector3f vTar) {
				camera = vCam;
				if(bLocalTarget) delete target;
				target = new Vector3f(vTar[0], vTar[1], vTar[2]);
				bLocalTarget = true;
			}

			t_AnimationItem3D() {
				t_AnimationItem2D();
				camera			= nullptr;
				target			= nullptr;
				bLocalTarget	= false;
			}

			~t_AnimationItem3D() {
				//~t_AnimationItem2D();
				if(bLocalTarget) delete target;
			}
	};

	/** *******************************************************************************************************************
	 *
	 * @brief
	 *
	 ******************************************************************************************************************** */
	class _AnimationSys {
		private:
			t_AudioInstance	audio;
			//AudioSys 	*audioSys;
//				Texture		texture;
			uint 		uiRecordSize;
			std::string sFilename,
						sDir,
						sTexDir;

			struct t_AnimationDefinition {
				uint			id;							// Animation id
				std::string		image;						// Animation image file
				uint			frames;						// Number of frames for this animation
				Texture			texture;
				Core::VAO		*vao;						// Custom VAO built from "frames" value (will be an array the size of the number of frames)

				t_AnimationDefinition() {
					id						= 0;
					frames					= 0;
					vao						= nullptr;
				}
			};

			t_VectorMap<t_AnimationDefinition*> data;

		protected:
//				friend class GameSys;
			//friend class AudioSys;

		public:
			Timer timer;
			//_AnimationSys();
//			_AnimationSys(AudioSys &a);
			_AnimationSys();
			~_AnimationSys();
//				// TODO: Load these associations from file, the number is equal to the id of the animation which is also equal to its array index (typically iA in this file)
//				struct _ANIMATIONS {
//					__uint16_t	SWORD_HIT	= 0,
//								BLOCK		= 1,
//								GLANCE		= 2,
//								DODGE		= 3,
//								DEFLECT		= 4;
//				} ANIMATIONS;
			void init();
			void load();
			void calc();
			t_AnimationDefinition& get(int id)						{	return *data[id];		}
			t_AnimationDefinition& get(std::string name)			{	return *data[name];		}

			t_AnimationDefinition& operator[](int id)				{	return *data[id];		}
			t_AnimationDefinition& operator[](std::string name)		{	return *data[name];		}

	};

//	_AnimationSys::_AnimationSys(/*Matrix_System *m,*/ AudioSys &a) {
	_AnimationSys::_AnimationSys() {
		uiRecordSize	= 32;
		sFilename		= "animations.bin";
		sDir			= "./system/";
		sTexDir			= "./texture/animations/";
	}

	_AnimationSys::~_AnimationSys() {
		for(auto & item : data) {
			delete item;
		}
	}

	void _AnimationSys::init() {
		//            .................................................................Done
		debug.log("Init Animations {");
		data.setSource("_AnimationSys");
		timer.start();
		debug.print("}\n");
	}

	void _AnimationSys::load() {
		debug.log("Load Animations {\n");
		debug.logIncreaseIndent();
		MemBlock memBlock;
		std::string theImage;
		readFile((sDir+sFilename), memBlock);

		for (uint d=0; d<memBlock.size; d+=uiRecordSize) {
			t_AnimationDefinition *newData = new t_AnimationDefinition();

			newData->id		= (__uint16_t)( (__uint8_t)(memBlock.buffer[0+d])*256 + (__uint8_t)(memBlock.buffer[1+d]) );
			newData->frames	= (__uint16_t)( (__uint8_t)(memBlock.buffer[2+d])*256 + (__uint8_t)(memBlock.buffer[3+d]) );

			theImage = "";
			for (int i=4; i<32; i++)
				if (memBlock.buffer[i+d]!=0) theImage+=(unsigned char)memBlock.buffer[i+d];
				else break;

			newData->image	= theImage;
			newData->texture.Begin(1);
			newData->texture.Load(sTexDir, theImage, 0, false, GL_NEAREST);

			data.add(newData->image, newData);

			debug.log("["+std::to_string(newData->id)+"] "+newData->image+" ("+std::to_string(newData->frames)+" frames)\n", debug().YELLOW);
		}
		debug.logDecreaseIndent();
		debug.log("}\n");
	}

	void _AnimationSys::calc() {
		debug.log("Calc Animations {");

		for(auto &item : data) {
			Vector4f gridCoord[item->frames];
			float iy1=0.0000f,
						iy2=1.0f/float(item->frames);
			for(int i=0;i<item->frames;i++) {
				gridCoord[i][0] = 0.0f;
				gridCoord[i][1] = iy1;
				gridCoord[i][2] = 1.0f;
				gridCoord[i][3] = iy1+=iy2;
			}

			item->vao = new VAO[item->frames];

			//cout << "Calculating Texture Coords" << std::endl;
			for (int iF=0; iF<item->frames; ++iF) {

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

				item->vao[iF].Begin(GL_TRIANGLES, 6, 6, 1);
				item->vao[iF].CopyData(GLA_VERTEX, vVerts);
				item->vao[iF].CopyData(GLA_TEXTURE, vTexture, 0);
				item->vao[iF].End();
			}
		}
		debug.print("}\n");
	}



	/** *******************************************************************************************************************
	 *
	 * @brief
	 *
	 ******************************************************************************************************************** */
	template <typename T>
	class t_AnimationInstance {
		public:
			//t_VectorMap<T*> list;
			t_UMap<std::string, T*> list;
			t_AudioInstance audio;

			/*
			 * size/x,y...........Specifies the size of the animation
			 * camera.............Location to billboard animation towards
			 * target.............Location to draw animation at
			 * iA.................Animation id number to draw
			 * bMoveOrigin(true)..Translate center location for world sprites (world sprites have origin at bottom center, animations at true center, this fixes that unless a specific location is wanted for the animation)
			 * rate(60)...........Time between frame updates in milliseconds, 60 by default. Setting this value overwrites the loaded value.
			 */

			T& add(std::string name, std::string sAnimation, float x, float y, int loop, uint rate=100, int iSample=-1);
			void start(std::string name);
			void stop(std::string name);
			void pause(std::string name);
			void remove(std::string name);
			void update();
			void update(std::string name);
			void draw();
			void draw(std::string name, float fScale=1.0f);
			void draw(std::string name, Core::GUI::Props_Animation &prop);
//				void draw(std::string name, float fScale, bool bVerticalBB=false);

			T& operator[](int id)				{	return *list[id];		}
			T& operator[](std::string name)		{	return *list[name];		}

			t_AnimationInstance();
			~t_AnimationInstance();
	};

	template <typename T> t_AnimationInstance<T>::t_AnimationInstance() {
		list.setSource("t_AnimationInstance");
	}

	template <typename T> t_AnimationInstance<T>::~t_AnimationInstance() {
		for(auto &item : list) {
			delete item.second;
		}
	}

	template <typename T> T& t_AnimationInstance<T>::add(std::string name, std::string sAnimation, float x, float y, int loop, uint rate, int iSample) {
		T *type = new T;
		type->id				= animationSys[sAnimation].id;							// Store the id of the global animation
		type->bActive			= false;											// Flag the animation as inactive, use start() to enable
		type->rate				= rate;												// Update the requested rate
		type->ticks				= 0;
		type->currentFrame		= 0;												// Start at frame 0
		type->loop				= loop;												// Set the number of loops (-1 = infinite)
		type->currentLoop		= 0;
		type->iSample			= iSample;											// Store the sound effect to play
		type->size.x			= x;
		type->size.y			= y;
		list.add(name, type);
		return *list[name];
	}

	template <typename T> void t_AnimationInstance<T>::start(std::string name) {
		if(!list[name]->bActive || list[name]->bIsPaused) {
			list[name]->bActive			= true;
			list[name]->ticks			= animationSys.timer.get_ticks();
			if(!list[name]->bIsPaused) {
				list[name]->bSamplePlayed	= false;
				list[name]->currentFrame	= 0;
				list[name]->currentLoop		= 0;
			}
			list[name]->bIsPaused		= false;
		}
	}

	template <typename T> void t_AnimationInstance<T>::pause(std::string name) {
		list[name]->bActive			= false;
		list[name]->bIsPaused		= true;
	}

	template <typename T> void t_AnimationInstance<T>::stop(std::string name) {
		list[name]->bSamplePlayed	= false;
		list[name]->bActive			= false;
		list[name]->ticks			= 0;
		list[name]->currentFrame	= 0;
		list[name]->currentLoop		= 0;
	}

	template <typename T> void t_AnimationInstance<T>::remove(std::string name) {
		delete list[name];
		list.remove(name);
	}

	template <typename T> void t_AnimationInstance<T>::update() {
		for(auto &item : list) {
			update(list.getName(item->id));
		}
	}

	template <typename T> void t_AnimationInstance<T>::update(std::string name) {
		if(list[name]->bActive) {
			if(animationSys.timer.get_ticks()>=(list[name]->ticks+list[name]->rate)) {
				++list[name]->currentFrame;
				list[name]->ticks		= animationSys.timer.get_ticks();
			}

			if(list[name]->currentFrame >= animationSys[list[name]->id].frames) {
				if(list[name]->loop == -1) list[name]->currentFrame=0;
				else {
					--list[name]->currentLoop;
					if(list[name]->currentLoop>0) list[name]->currentFrame = 0;
					else list[name]->bActive = false;
				}
			}

			if(!list[name]->bActive && list[name]->bAutoDestruct) list.remove(name);

		} /*bActive*/

	}

	template <typename T> void t_AnimationInstance<T>::draw() {
		for(auto &item : list) {
			draw(list.getName(item->id));
		}
	}

	template <> void t_AnimationInstance<t_AnimationItem2D>::draw(std::string name, float fScale) {

		if( list[name]->bActive || list[name]->bIsPaused ) {

			if( (!list[name]->bSamplePlayed) && (list[name]->iSample>=0) && (list[name]->currentFrame==0) ) {
				list[name]->bSamplePlayed = true;
				//audioSys->playSound(list[name]->iSample);
				// TODO: audio.play("temp");
			}

			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_CULL_FACE);
			matrix->SetProjection(matrix->MM_ORTHO);

			shader->use(GLS_FONT);
			matrix->Push();
				matrix->Scale(list[name]->size[0], list[name]->size[1], 0.0f);
				matrix->SetTransform();
				shader->getUniform(GLS_FONT);

				animationSys[list[name]->id].texture.Set(animationSys[list[name]->id].image);
				animationSys[list[name]->id].vao[list[name]->currentFrame].Draw();
			matrix->Pop();

			matrix->SetProjection(matrix->MM_PERSPECTIVE);
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
		}
	}

	template <> void t_AnimationInstance<t_AnimationItem2D>::draw(std::string name, Core::GUI::Props_Animation &prop) {

		if( list[name]->bActive || list[name]->bIsPaused ) {

			if( (!list[name]->bSamplePlayed) && (list[name]->iSample>=0) && (list[name]->currentFrame==0) ) {
				list[name]->bSamplePlayed = true;
//				audioSys->playSound(list[name]->iSample);
				// TODO: audio.play("temp");
			}

			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_CULL_FACE);
			matrix->SetProjection(matrix->MM_ORTHO);

			shader->use(GLS_FONT);
			matrix->Push();

				Vector2f vPos;
				vPos = prop.getPos();
				matrix->Translate( vPos.x, vPos.y, 0.0 );
				Vector2f vScale;
				vScale = prop.getSize();
				matrix->Scale(vScale.x, vScale.y, 0.0f);

				// animation scale ignored
//					matrix->Scale(list[name]->size[0], list[name]->size[1], 0.0f);
				matrix->SetTransform();
				shader->getUniform(GLS_FONT);

				animationSys[list[name]->id].texture.Set(animationSys[list[name]->id].image);
				animationSys[list[name]->id].vao[list[name]->currentFrame].Draw();
			matrix->Pop();

			matrix->SetProjection(matrix->MM_PERSPECTIVE);
			glEnable(GL_CULL_FACE);
			glEnable(GL_DEPTH_TEST);
		}
	}

	template <> void t_AnimationInstance<t_AnimationItem3D>::draw(std::string name, float fScale) {
		if( list[name]->bActive || list[name]->bIsPaused ) {
			glDisable(GL_CULL_FACE);
			matrix->Push();

				matrix->Rotate(Core::gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
				matrix->Rotate(Core::gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
				matrix->Translate(Core::gameVars->player.active->transform.pos[0], Core::gameVars->player.active->transform.pos[1], Core::gameVars->player.active->transform.pos[2]);

				shader->use(GLS_FONT);

				Vector3f vCamPos;
				vCamPos[0] = -((*list[name]->camera)[0] * fScale);
//				vCamPos[1] =  ((*list[name]->camera)[1]);
				vCamPos[1] =  0.0f;
				vCamPos[2] = -((*list[name]->camera)[2] * fScale);
				Vector3f	vUp = { 0.0, 1.0, 0.0};
				Vector3f	vLook, vRight, vObjPos;
				float fY = 0.0f;
//				if (bVerticalBB) {
//					vObjPos = Vector3f( float((*list[name]->target)[0]*fScale), float((*list[name]->target)[1]*fScale), float((*list[name]->target)[2]*fScale) );
//					fY = 0.0f;
//					vObjPos = Vector3f( float((*list[name]->target)[0]), float((*list[name]->target)[1]), float((*list[name]->target)[2]) );
//					fY = ((*list[name]->target)[1]);
//					fY = 0.0f;
//				}
//				else {
//					vObjPos = Vector3f( float((*list[name]->target)[0]*fScale), 0.0f, float((*list[name]->target)[2]*fScale) );
//					fY = ((*list[name]->target)[1]*fScale);
					vObjPos = Vector3f( float((*list[name]->target)[0] * fScale), 0.0f, float((*list[name]->target)[2] * fScale) );
					fY = ((*list[name]->target)[1] * fScale);
//				}

				vLook = vCamPos - vObjPos;
				Core::gmath.Normalize(vLook);
				Core::gmath.Cross(vRight, vUp, vLook);

				Matrix44f	mLook = {	vRight[0],	vRight[1],	 vRight[2],		0.0f,
											 0.0f,		 1.0f,		  0.0f,		0.0f,
										 vLook[0],	 vLook[1],	  vLook[2],		0.0f,
									   vObjPos[0],		   fY,	vObjPos[2],		1.0f	};

				matrix->Push();
					matrix->Apply(mLook);
//					matrix->Scale(list[name]->size[0]*fScale, list[name]->size[1]*fScale, 0.0f);
					matrix->Scale(list[name]->size[0] * fScale, list[name]->size[1] * fScale, 0.0f);
					matrix->SetTransform();
					shader->getUniform(GLS_FONT);

					//texture.Set(animation[iA].image);
					animationSys[list[name]->id].texture.Set(animationSys[list[name]->id].image);
					animationSys[list[name]->id].vao[list[name]->currentFrame].Draw();
				matrix->Pop();
			matrix->Pop();

			glEnable(GL_CULL_FACE);
		}

	}
}
#endif /* ANIMATIONS_H_ */
