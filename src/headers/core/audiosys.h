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

			t_AudioItem() {
				iSample			= 0;
				bActive			= false;
				bIsPaused		= false;
				bOverlap		= true;
				loop			= 1;
			}
	};

	class t_SoundItem : public t_AudioItem {
		public:
			int			iChannel;

			t_SoundItem() {
				t_AudioItem();
				iChannel		= -1;
			}
	};

	class t_MusicItem : public t_AudioItem {
		public:
			int			iFade;

			t_MusicItem() {
				t_AudioItem();
				iFade		= 0;
			}
	};

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
//					typedef std::pair<int, std::string> pair;
//					t_UMap<pair, t_SoundDefinition*> data;
//					t_UMap<int, t_SoundDefinition*> data;
//					t_VectorMap<t_SoundDefinition*> data;

					t_UMap<int, int> map_id;
					t_UMap<std::string, int> map_name;
					t_Vector1T<t_SoundDefinition*> data;
//					t_VectorMap<t_SoundDefinition*> data;
					AudioSys * parent;

				public:
					int iVolume;
					bool bMute;
					void add(int id, std::string name, t_SoundDefinition *newData);
					void play(int iSample, int iLoop=0, bool bOverlap=true, int iChannel=-1);
					void pause(int iChannel=-1);
					void stop(int iChannel=-1);
					void mute();
					void unmute();
					void setVolume(int iVol);
					t_SoundDefinition & operator[](int iSample)			{	return *data[map_id[iSample]];	}
					t_SoundDefinition & operator[](std::string name)	{	return *data[map_name[name]];	}
					SoundInterface(AudioSys * p) { parent = p; iVolume=128; bMute=false; }
//					~SoundInterface() { for (auto & item : data) delete item.second; }
					~SoundInterface() { for (auto & item : data) delete item; }
			};
			SoundInterface Sound = SoundInterface(this);

			class MusicInterface {
					friend class AudioSys;
				private:
//					t_PairMap<t_MusicDefinition*> data;
//					t_UMap<int, t_MusicDefinition*> data;
//					t_VectorMap<t_MusicDefinition*> data;

					t_UMap<int, int> map_id;
					t_UMap<std::string, int> map_name;
					t_Vector1T<t_MusicDefinition*> data;

					AudioSys * parent;

				public:
					int iVolume;
					bool bMute;
					void add(int id, std::string name, t_MusicDefinition *newData);
					void play(int iSample, int iLoop=-1, int iFade=0);
					void pause();
					void fadeOut(int iFade);
					void stop();
					void mute();
					void unmute();
					void setVolume(int iVol);
					t_MusicDefinition & operator[](int iSample)			{	return *data[map_id[iSample]];	}
					t_MusicDefinition & operator[](std::string name)	{	return *data[map_name[name]];	}
					MusicInterface(AudioSys * p) { parent = p; iVolume=128; bMute=false; }
//					~MusicInterface() { for (auto & item : data) delete item.second; }
					~MusicInterface() { for (auto & item : data) delete item; }
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
	class t_SoundInstance {
		public:
			static AudioSys *parent;

			t_UMap<std::string, t_SoundItem*> audio;

			void add(std::string name, int iSample, int iLoop, bool bOverlap, int iChannel=-1);
			void remove(std::string name);

			void play(std::string name);
			void pause(std::string name);
			void stop(std::string name);

			t_SoundItem& operator[](std::string name)		{	return *audio[name];		}

			t_SoundInstance();
			~t_SoundInstance();
	};

	class t_MusicInstance {
		public:
			static AudioSys *parent;

			t_UMap<std::string, t_MusicItem*> audio;

			void add(std::string name, int iSample, int iLoop, bool bOverlap, int iFade=0);
			void remove(std::string name);

			void play(std::string name);
			void pause();
			void stop();

			t_MusicItem& operator[](std::string name)		{	return *audio[name];		}

			t_MusicInstance();
			~t_MusicInstance();
	};





































}

#endif /* AUDIOSYS_H_ */
