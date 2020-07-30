/*
 * timer.hpp
 *
 *  Created on: May 19, 2010
 *      Author: Brian ThunderEagle
 *
 *      A basic timer
 */

#include <iostream>
//#define GL_GLEXT_PROTOTYPES 1		// Enable core profile
//#define GL_POINT_SPRITE 0x8861		// Hack to enable Point Sprites thus enabling gl_PointCoord operation
//#include "./headers/gl4/glcorearb.h"
//#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
//#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
//#include "./headers/core/types.h"
#include <SDL2/SDL.h>
#include "timer.h"

namespace Core {
	Timer::Timer() {
		//Initialize the variables
		startTicks = 0;
		pausedTicks = 0;
		paused = false;
		started = false;
		splitTicks = 0;
		rate = 0;
		rateMod = 0;
	}

	void Timer::start() {
		//Start the timer
		started = true;

		//Unpause the timer
		paused = false;

		//Get the current clock time
		startTicks = SDL_GetTicks();
		splitTicks = startTicks;
	}

	void Timer::set(float fTime) {
		//Start the timer
		started = true;

		//Unpause the timer
		paused = false;

		//Get the current clock time
		startTicks = fTime + SDL_GetTicks();
		splitTicks = startTicks;
	}

	void Timer::stop() {
		//Stop the timer
		started = false;

		//Unpause the timer
		paused = false;
	}

	void Timer::pause() {
		//If the timer is running and isn't already paused
		if( ( started == true ) && ( paused == false ) ) {
			//Pause the timer
			paused = true;

			//Calculate the paused ticks
			pausedTicks = SDL_GetTicks() - startTicks;
		}
	}

	void Timer::unpause() {
		//If the timer is paused
		if( paused == true ) {
			//Unpause the timer
			paused = false;

			//Reset the starting ticks
			startTicks = SDL_GetTicks() - pausedTicks;

			//Reset the paused ticks
			pausedTicks = 0;
		}
	}

	int Timer::get_ticks() {
		//If the timer is running
		if( started == true ) {
			//If the timer is paused
			if( paused == true ) {
				//Return the number of ticks when the timer was paused
				return pausedTicks;
			}
			else {
				//Return the current time minus the start time
				return SDL_GetTicks() - startTicks;
			}
		}

		//If the timer isn't running
		return 0;
	}

	bool Timer::is_started() {
		return started;
	}

	bool Timer::is_paused() {
		return paused;
	}

	int Timer::split() {
		splitTicks=SDL_GetTicks() - startTicks;
		return splitTicks;
	}

	int Timer::get_split() {
		return splitTicks;
	}

	int Timer::get_splitdiff() {
		return (Timer::get_ticks()-splitTicks);
	}

	void Timer::reset() {
		startTicks = SDL_GetTicks();
		splitTicks = startTicks;
		pausedTicks = 0;
	}
}
