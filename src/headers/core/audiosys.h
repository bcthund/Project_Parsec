/*
 * System.h
 *
 *  Created on: Feb 21, 2011
 *      Author: bcthund
 */

#ifndef AUDIOSYS_H_
#define AUDIOSYS_H_

#include <iostream>

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
//#include <stdlib.h>
//#include <unistd.h>
//#include <chrono>
//#include <thread>

namespace Core {
	class AudioSys {
		private:
			int iInit;							// Has the sound system been successfully initialized? (see enum below)
			static int iBeat;					// Stores the current mixed audio stream (used to shake title)
			enum	{ INIT_NONE=0, INIT_MIX_INIT=1, INIT_SDL_INIT_AUDIO=2, INIT_MIX_OPENAUDIO=4 };
			int iDecoders,
				iChannels;
			//void getBeat(int chan, void *stream, int len, void *udata);
			static void setBeat(void *udata, __uint8_t *stream, int len);
			void loadSound(int iCount, std::string sLoad);

			struct _ChunkItem {
				Mix_Chunk *chunk;
//				Mix_Chunk sample;
				bool bLoad;

				_ChunkItem() {
					chunk = nullptr;
					bLoad = false;
				}

				~_ChunkItem() {
					if(chunk != nullptr) Mix_FreeChunk(chunk);
					bLoad = false;
				}

			} soundItem[128];

			struct _MusicItem {
				Mix_Music *music;
				bool bLoad;

				_MusicItem() {
					music = nullptr;
					bLoad = false;
				}

				~_MusicItem() {
					if(music != nullptr) Mix_FreeMusic(music);
				}

			} musicItem[128];

			bool bMute;

		protected:
			//friend class GameSys;

		public:
			// TODO: REWORK TO BE UNIVERSAL
			//enum { MUSIC_NONE, MUSIC_MAINMENU, MUSIC_WORLDEXPLORE, MUSIC_WORLDBATTLE };

			AudioSys();
			~AudioSys();
			void playSound(int iSample, int iLoop=0, bool bOverlap=true, int iChannel=-1);
			void playMusic(int iSample, int iLoop=-1, int iFade=0);
			void playMusic(__uint8_t ui);
			void fadeOutMusic(__uint8_t ui, int ms);
			void stopMusic();
			bool load();
			bool init();
			void Mute() { bMute = true; }
			void Unmute() { bMute = false; }
			__uint8_t getBeat();
	};
}

#endif /* AUDIOSYS_H_ */
