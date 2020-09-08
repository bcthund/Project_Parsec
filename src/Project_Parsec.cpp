//============================================================================
// Name        : Project_Parsec.cpp
// Author      : Brian ThunderEagle
// Version     :
// Copyright   : GNU General Public License, version 3
// Description : Hello World in C++, Ansi-style
//============================================================================
//Required Master Headers
//#include <stdlib.h>
//#include <curses.h>		//Used for debugging
//#include <iostream>			//IO Stream
//#include <string>
//#include <cstring>
//#include <stdio.h>
//#include <cstring>
//#include <fstream>			// File Stream
//#include <map>				// Provides string->int mapping
//#include <vector>
//#include <math.h>
//#include <cmath>			// Math functions
//#include <sstream>			// String Stream
//#include <new>
//#include <algorithm>		// Provides sort() and for_each()
//#include <random>			// Provides random number generator superior to rand()
//#include "/usr/include/c++/6/bits/random.h"	//Eclipse glitch, manually include after <random>
//#include "random.h"		//Eclipse glitch, manually include after <random>

//namespace RNG {
//	//random number generator setup
//	std::random_device r;
//	std::seed_seq seed{r(),r(),r(),r(),r(),r()};
//	std::mt19937 eng{seed};
//	/*
//	 * Use std::uniform_real_distribution<> dist(a, b);
//	 * to create a float between a and b
//	 *
//	 * Get a new value with dist(RNG::eng)
//	 */
//}

//SDL Headers
//#include <SDL2/SDL.h>
//#include <SDL2/SDL_image.h>

//OpenGL Core 4
//#define GL_GLEXT_PROTOTYPES 1		// Enable core profile
//#define GL_POINT_SPRITE 0x8861		// Hack to enable Point Sprites thus enabling gl_PointCoord operation
//#include "./my_includes/gl4/glcorearb.h"
//#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
//#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
//#define GL3_PROTOTYPES 1

#include "./headers/core.h"				// Must be after gameVars->h
//#include "./headers/settings.h"
#include "./game/runGame.h"
#include "./game/runAdmin.h"

int main(int argc, char* argv[]) {

	// Example for using arguments
//	if (argc < 2) {
//		cout << "!!!!!!!!!!!!!!!!" << endl << endl;
//		cout << "Error: Must specify terrain grid size of 3, 5, 7, or 9" << endl;
//		//std::terminate();
//		bRun = false;
//	}

	Core::Setup(argc, argv);
	_Game game;
	game.load();

	_Admin admin = _Admin(&game);
	admin.init();

	//std::cout << "<---------------------------" << Core::skeleton->vConnection[0]->x << ", " << Core::skeleton->vConnection[0]->y << ", " << Core::skeleton->vConnection[0]->z << std::endl;
	Core::glReport();

	// Start timers
	Core::timeSys->start();

	//std::srand(std::time(0));
//	std::srand((unsigned) time(0));

	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

	do {
		/*
		 * Check for SDL events
		 *
		 * Needs a way to update post-processing init()
		 * Post processing layer has predefined size
		 */
//		float width = 0;
//		float height = 0;
//		SDL_Event event;
//		while (SDL_PollEvent(&event))  {
//			switch (event.type)  {
//				case SDL_WINDOWEVENT: {
//						switch (event.window.event)  {
//							case SDL_WINDOWEVENT_SIZE_CHANGED:
//								width = event.window.data1;
//								height = event.window.data2;
//								std::cout << "(" << width << ", " << height << ")" << std::endl;
//
//								Core::gameVars->screen.res.x		= width;
//								Core::gameVars->screen.res.y		= height;
//								Core::gameVars->screen.fHalfW		= width/2.0f;
//								Core::gameVars->screen.fHalfH		= height/2.0f;
//								Core::gameVars->screen.origin[0]	= -Core::gameVars->screen.fHalfW;
//								Core::gameVars->screen.origin[1]	= Core::gameVars->screen.fHalfH;
//
//								//SDL_SetWindowSize(Core::glinit->window, width, height);
//								glViewport(0, 0, width, height);
//
//								Core::matrix->SetPerspective(	Core::gameVars->screen.degFov,
//																(float)Core::gameVars->screen.res.x/(float)Core::gameVars->screen.res.y,
//																Core::gameVars->screen.fNear,
//																Core::gameVars->screen.fFar);
//								Core::matrix->SetOrtho(Core::gameVars->screen.fHalfW, Core::gameVars->screen.fHalfH, 1000.0f, 1.0f);
//
//								// Init/Load/Calc Core Systems
//								Core::matrix->SetProjection(Core::matrix->MM_PERSPECTIVE);
//
//								break;
//						}
//					break;
//				}
//			}
//		}

		Core::framerate->start();
		//Core::profiles->startProfile(Core::profiles->builtIn.FrameRate);
		Core::profiles->startProfile(Core::profiles->builtIn.RunGame);
		Core::timeSys->Update();

//		SDL_PumpEvents();
//		Core::mouse->update(Core::gameVars->screen.half.x, Core::gameVars->screen.half.y);

		// Clear mouse events
		Core::mouse->wheel.up		= false;
		Core::mouse->wheel.down		= false;
		Core::mouse->wheel.right	= false;
		Core::mouse->wheel.left		= false;

		// TODO: Move into an overall API class, along with glinit
		// TODO: Call even processing functions (keyboard, mouse) Make kayboard and mouse classes global.
		/*
		 * Empty the SDL event queue
		 */
		while(SDL_PollEvent(Core::sdlEvent)) {
			switch(Core::sdlEvent->type) {
//				case SDL_AUDIODEVICEADDED:			std::cout << "SDL_AUDIODEVICEADDED" << std::endl; break;
//				case SDL_AUDIODEVICEREMOVED:		std::cout << "SDL_AUDIODEVICEREMOVED" << std::endl; break;
//				case SDL_CONTROLLERAXISMOTION:		std::cout << "SDL_CONTROLLERAXISMOTION" << std::endl; break;
//				case SDL_CONTROLLERBUTTONDOWN:		std::cout << "SDL_CONTROLLERBUTTONDOWN" << std::endl; break;
//				case SDL_CONTROLLERBUTTONUP:		std::cout << "SDL_CONTROLLERBUTTONUP" << std::endl; break;
//				case SDL_CONTROLLERDEVICEADDED:		std::cout << "SDL_CONTROLLERDEVICEADDED" << std::endl; break;
//				case SDL_CONTROLLERDEVICEREMOVED:	std::cout << "SDL_CONTROLLERDEVICEREMOVED" << std::endl; break;
//				case SDL_CONTROLLERDEVICEREMAPPED:	std::cout << "SDL_CONTROLLERDEVICEREMAPPED" << std::endl; break;
//				case SDL_DOLLARGESTURE:				std::cout << "SDL_DOLLARGESTURE" << std::endl; break;
//				case SDL_DOLLARRECORD:				std::cout << "SDL_DOLLARRECORD" << std::endl; break;
//				case SDL_DROPFILE:					std::cout << "SDL_DROPFILE" << std::endl; break;
//				case SDL_DROPTEXT:					std::cout << "SDL_DROPTEXT" << std::endl; break;
//				case SDL_DROPBEGIN:					std::cout << "SDL_DROPBEGIN" << std::endl; break;
//				case SDL_DROPCOMPLETE:				std::cout << "SDL_DROPCOMPLETE" << std::endl; break;
//				case SDL_FINGERMOTION:				std::cout << "SDL_FINGERMOTION" << std::endl; break;
//				case SDL_FINGERDOWN:				std::cout << "SDL_FINGERDOWN" << std::endl; break;
//				case SDL_FINGERUP:					std::cout << "SDL_FINGERUP" << std::endl; break;
//				case SDL_KEYDOWN:					std::cout << "SDL_KEYDOWN" << std::endl; break;
//				case SDL_KEYUP:						std::cout << "SDL_KEYUP" << std::endl; break;
//				case SDL_JOYAXISMOTION:				std::cout << "SDL_JOYAXISMOTION" << std::endl; break;
//				case SDL_JOYBALLMOTION:				std::cout << "SDL_JOYBALLMOTION" << std::endl; break;
//				case SDL_JOYHATMOTION:				std::cout << "SDL_JOYHATMOTION" << std::endl; break;
//				case SDL_JOYBUTTONDOWN:				std::cout << "SDL_JOYBUTTONDOWN" << std::endl; break;
//				case SDL_JOYBUTTONUP:				std::cout << "SDL_JOYBUTTONUP" << std::endl; break;
//				case SDL_JOYDEVICEADDED:			std::cout << "SDL_JOYDEVICEADDED" << std::endl; break;
//				case SDL_JOYDEVICEREMOVED:			std::cout << "SDL_JOYDEVICEREMOVED" << std::endl; break;
//				case SDL_MOUSEMOTION:				std::cout << "SDL_MOUSEMOTION" << std::endl; break;
//				case SDL_MOUSEBUTTONDOWN:			std::cout << "SDL_MOUSEBUTTONDOWN" << std::endl; break;
//				case SDL_MOUSEBUTTONUP:				std::cout << "SDL_MOUSEBUTTONUP" << std::endl; break;
				case SDL_MOUSEWHEEL:
//					std::cout << "SDL_MOUSEWHEEL - ";
					if(Core::sdlEvent->wheel.y > 0) {
						Core::mouse->wheel.up = true;
//						std::cout << "UP" << std::endl;
					}
					else if(Core::sdlEvent->wheel.y < 0) {
						Core::mouse->wheel.down = true;
//						std::cout << "DOWN" << std::endl;
					}

					if(Core::sdlEvent->wheel.x > 0) {
						Core::mouse->wheel.right = true;
//						std::cout << "RIGHT" << std::endl;
					}
					else if(Core::sdlEvent->wheel.x < 0) {
						Core::mouse->wheel.left = true;
//						std::cout << "LEFT" << std::endl;
					}
					break;

//				case SDL_MULTIGESTURE:				std::cout << "SDL_MULTIGESTURE" << std::endl; break;
//				case SDL_QUIT:						std::cout << "SDL_QUIT" << std::endl; break;
//				case SDL_SYSWMEVENT:				std::cout << "SDL_SYSWMEVENT" << std::endl; break;
//				case SDL_TEXTEDITING:				std::cout << "SDL_TEXTEDITING" << std::endl; break;
//				case SDL_TEXTINPUT:					std::cout << "SDL_TEXTINPUT" << std::endl; break;
//				case SDL_USEREVENT:					std::cout << "SDL_USEREVENT" << std::endl; break;
//				case SDL_WINDOWEVENT:				std::cout << "SDL_WINDOWEVENT" << std::endl; break;
//				default:							std::cout << "UNKNOWN EVENT" << std::endl; break;
			}
		}

		// Clear Console
//		Core::debug.update(500);
		Core::debug.update(0, true);
		Core::debug.bLogEnable = true;
		Core::debug.bPrintEnable = true;
//		std::cout << "\033[2J\033[1;1H";	// 2J=clear from top(J) to bottom(2); Position cursor at row 1, column 1

		if (Core::gameVars->runState.main_menu) {
			//MainMenu.run();
		}
		else if (Core::gameVars->runState.console) {
			//Console.run();
		}
//		else if (Core::gameVars->runState.admin) {
//			admin.run();
//		}
		else if	(Core::gameVars->runState.skill) {
			//Skill.run();
		}
		else if	(Core::gameVars->runState.endBattle) {
			//EndBattle.run();
		}
		else if (Core::gameVars->runState.book) {
			//Journal.run();
			//BattleScroll.run();
			//Grimoire.run();
		}
		else if	(Core::gameVars->runState.menu) {
			/*
			 * We don't want all of these to be open at the same time. We can be careful
			 * with programming to prevent opening multiples or we can rework this
			 * section so that the menu state hold true/false for the main menu but can
			 * also hold more than just boolean values to determine the other parts.
			 *
			 * The downside to this could mean that when you enter the battelscroll,
			 * journal, or grimoire and you escape out it will never take you back
			 * to the menu unless we again do some careful programming to track
			 * previous states.
			 *
			 * We could also have the menu state and an additional "books" state so
			 * that we could check for open books first, then leave the menu state
			 * active but won't be drawn until we exit the book state.
			 */
			//Menu.run(false);
		}
		else if (Core::gameVars->runState.event) {
			/*
			 * TODO: THIS SHOULD BE THE EVENT HANDLING SECTION
			 *
			 * We want events to take precedence over everything except the menu
			 * system. Events also needs access to every other state in the
			 * game so careful programming has to be done to handle events.
			 *
			 * Events need to access the world, city, dungeon, and battle areas
			 * as well as everything in gameVars, and other core components of
			 * the game.
			 *
			 * Core areas could include the matrix system to allow event
			 * transformations (screen skew, temporary displacement, etc.) which
			 * could be handled by putting a matrix.push here then add another
			 * event check and do a matrix.pop before the buffers are swapped.
			 *
			 * Other core areas could include the shaders header which has all
			 * of the variables for fog, ambient, diffuse, and specular colors
			 * as well as other related settings. We may move these to gameVars
			 * later if possible but it may be a circular definition problem
			 * to do that, this may not be the case anymore though.
			 * (shaders depends on gameVars which depends on shaders...etc)
			 *
			 * Although not implemented anymore, the shadow class is another
			 * core class that might need to be accessed in the future.
			 *
			 * The System headers should NOT need to be accessed.
			 *
			 * gameVars is the most important item to require access to because
			 * it is being setup to hold pointers to the current active
			 * data.
			 */

			//Talk.run(*gameVars);
		}
		else if (Core::gameVars->runState.battle) {
		}
		else if (Core::gameVars->runState.dungeon) {
		}
		else if (Core::gameVars->runState.city) {
		}
		else if (Core::gameVars->runState.world) {
			game.Run();
		}
		else Core::gameVars->runState.quit=true;

		// Draw on top of other states, allows other states to continue to run
		if (Core::gameVars->runState.admin) {
			admin.run();
		}

		Core::profiles->stopProfile(Core::profiles->builtIn.RunGame);
		Core::profiles->startProfile(Core::profiles->builtIn.SwapBuffers);
		SDL_GL_SwapWindow(Core::glinit->window);
		Core::profiles->stopProfile(Core::profiles->builtIn.SwapBuffers);
		//Core::profiles->stopProfile(Core::profiles->builtIn.FrameRate);
		Core::framerate->update();
	} while (!Core::gameVars->runState.quit);

	// Exit fullscreen
	if (SDL_GetWindowFlags(Core::glinit->window) & SDL_WINDOW_FULLSCREEN) SDL_SetWindowFullscreen(Core::glinit->window, 0);

	Core::Cleanup();

//	delete Core::gui;

	// Check Core namespace pointers
//	if(Core::matrix!=nullptr) delete Core::matrix;
//	if(Core::shader!=nullptr) delete Core::shader;
//	if(Core::postProcess!=nullptr) delete Core::postProcess;
//	if(Core::collision!=nullptr) delete Core::collision;
//	if(Core::helper!=nullptr) delete Core::helper;
//	if(Core::audioSys!=nullptr) delete Core::audioSys;
//
//	if(Core::iconSys!=nullptr) delete Core::iconSys;
//	if(Core::spriteSys!=nullptr) delete Core::spriteSys;
//	if(Core::textSys!=nullptr) delete Core::textSys;
//	if(Core::winSys!=nullptr) delete Core::winSys;
//	if(Core::menuSys!=nullptr) delete Core::menuSys;

	return 0;
}
