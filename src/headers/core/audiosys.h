/*
 * System.h
 *
 *  Created on: Feb 21, 2011
 *      Author: bcthund
 */

#ifndef AUDIOSYS_H_
#define AUDIOSYS_H_

#include <iostream>
#include "core_functions.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
//#include <stdlib.h>
//#include <unistd.h>
//#include <chrono>
//#include <thread>

namespace Core {

	class t_AudioItem {
		public:
			uint		iSample;
			bool		bActive;
			bool		bIsPaused;
			bool		bOverlap;
			int			loop;
			int			iChannel;

			t_AudioItem() {
				iSample			= 0;
				bActive			= false;
				bIsPaused		= false;
				bOverlap		= true;
				loop			= 1;
				iChannel		= -1;
			}
	};
	typedef t_AudioItem t_SoundItem;
	typedef t_AudioItem t_MusicItem;

	class AudioSys {
		private:
			int iInit;							// Has the sound system been successfully initialized? (see enum below)
			uint 		uiRecordSize;
			std::string sFilename,
						sDir,
						sAudioDir,
						sMusicDir,
						sTexDir;
//			static int iBeat;					// Stores the current mixed audio stream (used to shake title)
			enum	{ INIT_NONE=0, INIT_MIX_INIT=1, INIT_SDL_INIT_AUDIO=2, INIT_MIX_OPENAUDIO=4 };
			int iDecoders,
				iChannels;
			//void getBeat(int chan, void *stream, int len, void *udata);
			static void setBeat(void *udata, __uint8_t *stream, int len);
			void loadSound(int iCount, std::string sLoad);

			struct t_SoundDefinition {
				Mix_Chunk *chunk;
				bool bLoad;

				t_SoundDefinition() {
					chunk = nullptr;
					bLoad = false;
				}

				~t_SoundDefinition() {
					if(chunk != nullptr) Mix_FreeChunk(chunk);
					bLoad = false;
				}

			};

			struct t_MusicDefinition {
				Mix_Music *music;
				bool bLoad;

				t_MusicDefinition() {
					music = nullptr;
					bLoad = false;
				}

				~t_MusicDefinition() {
					if(music != nullptr) Mix_FreeMusic(music);
				}

			};

//			bool bMuteSound,
//				 bMuteMusic;

//			bool bMute;

		protected:
			//friend class GameSys;

		public:
//			struct s_ {
//			}

			// TODO: REWORK TO BE UNIVERSAL
			//enum { MUSIC_NONE, MUSIC_MAINMENU, MUSIC_WORLDEXPLORE, MUSIC_WORLDBATTLE };

			AudioSys();
			~AudioSys();

			class SoundInterface {
					friend class AudioSys;
				private:
					t_UMap<int, t_SoundDefinition*> data;
					AudioSys * parent;

				public:
					int iVolume;
					bool bMute;
					void play(int iSample, int iLoop=0, bool bOverlap=true, int iChannel=-1);
					void pause(int iChannel=-1);
					void stop(int iChannel=-1);
					void mute();
					void unmute();
					void setVolume(int iVol);
					t_SoundDefinition & operator[](int iSample)		{	return *data[iSample];	}
					SoundInterface(AudioSys * p) { parent = p; iVolume=128; bMute=false; }
					~SoundInterface() { for (auto & item : data) delete item.second; }
			};
			SoundInterface Sound = SoundInterface(this);

			class MusicInterface {
					friend class AudioSys;
				private:
					t_UMap<int, t_MusicDefinition*> data;
					AudioSys * parent;

				public:
					int iVolume;
					bool bMute;
					void play(int iSample, int iLoop=-1, int iFade=0);
					void pause();
					// TODO: void fadeOutMusic(__uint8_t ui, int ms);
					void stop();
					void mute();
					void unmute();
					void setVolume(int iVol);
					t_MusicDefinition & operator[](int iSample)		{	return *data[iSample];	}
					MusicInterface(AudioSys * p) { parent = p; iVolume=128; bMute=false; }
					~MusicInterface() { for (auto & item : data) delete item.second; }
			};
			MusicInterface Music = MusicInterface(this);

			bool load();
			bool init();
//			__uint8_t getBeat();
	};

	/** *******************************************************************************************************************
	 *
	 * @brief
	 *
	 ******************************************************************************************************************** */
	class t_AudioInstance {
		public:
			static AudioSys *parent;

			t_UMap<std::string, t_SoundItem*> sound;
			t_UMap<std::string, t_MusicItem*> music;

			void add(std::string name, int iSample, int iLoop, bool bOverlap, int iChannel);
			void remove(std::string name);

			void play(std::string name);
			void pause(std::string name);
			void stop(std::string name);

//			T& operator[](int id)				{	return *list[id];		}
//			T& operator[](std::string name)		{	return *list[name];		}

			t_AudioInstance();
			~t_AudioInstance();
	};





































}

#endif /* AUDIOSYS_H_ */
