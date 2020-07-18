
/*
 * glinit.h
 *
 *  Created on: Jan 28, 2014
 *      Author: bcthund
 */

#ifndef GLINIT_H_
#define GLINIT_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define GL_GLEXT_PROTOTYPES 1		// Enable core profile
//#define GL_POINT_SPRITE 0x8861		// Hack to enable Point Sprites thus enabling gl_PointCoord operation
#include "gl4_5/glcorearb.h"
#include "core_functions.h"

namespace Core {

	class GlInit_System {
		private:
			Vector4f vClearColor;
		protected:
		public:
			SDL_Window * window;
			SDL_GLContext context;
			void init(std::string cCaption, GLuint uiWidth, GLuint uiHeight, GLuint uiBpp, bool bMS, Vector4f vClearColor);
			void EnableAdditiveBlending();
			void DisableAdditiveBlending();
			void RestoreClearColor();
			~GlInit_System();
	};

}
#endif /* GLINIT_H_ */
