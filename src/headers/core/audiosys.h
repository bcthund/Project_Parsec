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
			bool		bOverlap;
			int			loop;

			t_AudioItem() {
				iSample			= 0;
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
			int iInit,							// Has the sound system been successfully initialized? (see enum below)
				iReservedChannels;
			uint 		uiRecordSize;
			std::string sFilename,
						sDir,
						sAudioDir,
						sMusicDir,
						sTexDir;
//			static int iBeat;					// Stores the current mixed audio stream (used to shake title)
			enum	{	INIT_NONE=0,
						INIT_MIX_INIT=1,
						INIT_SDL_INIT_AUDIO=2,
						INIT_MIX_OPENAUDIO=4 };

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

		protected:

		public:
			AudioSys();
			~AudioSys();

			// Reserved Channels map (name as used)
			struct s_Channels {
				const int	CHANNEL_NONE			= -1,
							CHANNEL_SYSTEM			= 0,
							CHANNEL_GUI_ANIMATION	= 1,	///< Not currently used, multiple animations is possible so may not use
							CHANNEL_GUI_BUTTON		= 2,
							CHANNEL_GUI_SLIDER		= 3,
							CHANNEL_GUI_ICON		= 4,
							CHANNEL_GUI_CHECK		= 5,
							CHANNEL_6				= 6,
							CHANNEL_7				= 7,
							CHANNEL_8				= 8,
							CHANNEL_9				= 9,
							CHANNEL_10				= 10,
							CHANNEL_11				= 11,
							CHANNEL_12				= 12,
							CHANNEL_13				= 13,
							CHANNEL_14				= 14,
							CHANNEL_15				= 15,
							CHANNEL_16				= 16,
							CHANNEL_17				= 17,
							CHANNEL_18				= 18,
							CHANNEL_19				= 19,
							CHANNEL_20				= 20,
							CHANNEL_21				= 21,
							CHANNEL_22				= 22,
							CHANNEL_23				= 23,
							CHANNEL_24				= 24,
							CHANNEL_25				= 25,
							CHANNEL_26				= 26,
							CHANNEL_27				= 27,
							CHANNEL_28				= 28,
							CHANNEL_29				= 29,
							CHANNEL_30				= 30,
							CHANNEL_31				= 31;
			} channels;

			class SoundInterface {
					friend class AudioSys;
				private:

					t_UMap<int, int> map_id;
					t_UMap<std::string, int> map_name;
					t_Vector1T<t_SoundDefinition*> data;

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
//					s_Channels & operator()()							{	return parent->channels;	}
					t_SoundDefinition & operator[](int iSample)			{	return *data[map_id[iSample]];	}
					t_SoundDefinition & operator[](std::string name)	{	return *data[map_name[name]];	}
					SoundInterface(AudioSys * p) { parent = p; iVolume=128; bMute=false; }
					~SoundInterface() { for (auto & item : data) delete item; }
			};
			SoundInterface Sound = SoundInterface(this);

			class MusicInterface {
					friend class AudioSys;
				private:
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
					~MusicInterface() { for (auto & item : data) delete item; }
			};
			MusicInterface Music = MusicInterface(this);

			bool load();
			bool init();
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

			AudioSys::s_Channels & operator()()				{	return parent->channels;	}
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
