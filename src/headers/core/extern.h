/*
 * extern.h
 *
 *  Created on: Sep 7, 2019
 *      Author: bcthund
 */

#ifndef HEADERS_CORE_EXTERN_H_
#define HEADERS_CORE_EXTERN_H_

#include <iostream>
#include <SDL2/SDL.h>
//#include "matrix.h"

// TODO: Get rid of pointers, no reason to be using them here.

namespace Core {
	extern std::string sOffset;
//	extern class Matrix_System		*	matrix;
//	extern class _SystemTextures	*	sysTex;
//	extern class Shader_System		*	shader;
//	extern class _Helper			*	helper;

	//extern class GameSys::_GameTime	*	timeSys		= new GameSys::_GameTime();

	extern class c_Scissor				scissor;
	extern class _Debug					debug;
	extern class _Groups				groups;
	extern class _Mouse					*	mouse;
	extern class _State					*	state;
	extern class GlInit_System			*	glinit;
	extern class Matrix_System			*	matrix;
	extern class _SystemTextures		*	sysTex;
	extern class Shader_System			*	shader;
	extern class PostProcess			*	postProcess;
	extern class _Collision				*	collision;
	extern class _Helper				*	helper;
	extern class AudioSys				audioSys;
	extern class _Joint					*	skeleton;
	extern class _Profile				*   profiles;
	extern class _FrameRate				*	framerate;
	extern class _TimeSys				*	timeSys;
	extern class _Occlusion				*	occlusion;
//	extern class _Colors				*	colors;
	extern class _Colors				colors;
	extern class _ParticleEmitter		*	particles;
//	extern class Stipple				*	stipple;
	extern class Stipple				stipple;
	extern class _AnimationSys			animationSys;

	extern struct GameVars				*	gameVars;

	//namespace GameSys {
	namespace Sys {
		extern class MapSys				mapSys;
		extern class O2DSys				o2dSys;
		extern class O3DSys				o3dSys;
	}

	extern class _IconSys		*	iconSys;
	extern class _SpriteSys		*	spriteSys;
	extern class _TextSys		*	textSys;
//	extern class _WinSys		*	winSys;
//	extern class _MenuSys		*	menuSys;
	//}

	extern SDL_Event			* sdlEvent;
}

#endif /* HEADERS_CORE_EXTERN_H_ */
