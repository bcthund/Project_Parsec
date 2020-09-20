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
				const int	CHANNEL_NONE			= -1,	///< Selects next available channel not on reserved list
							CHANNEL_0_SYSTEM		= 0,
							CHANNEL_1_GUI_ANIMATION	= 1,	///< Not currently used, multiple animations is possible so may not use
							CHANNEL_2_GUI_BUTTON	= 2,
							CHANNEL_3_GUI_SLIDER	= 3,
							CHANNEL_4_GUI_ICON		= 4,
							CHANNEL_5_GUI_CHECK		= 5,
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
			} CHANNEL;

			// Default Audio Samples
			struct s_Audio {
				const int	AUDIO_0					= 0,
							AUDIO_1					= 1,
							AUDIO_2					= 2,
							AUDIO_3					= 3,
							AUDIO_4					= 4,
							AUDIO_5					= 5,
							AUDIO_6					= 6,
							AUDIO_7					= 7,
							AUDIO_8					= 8,
							AUDIO_9					= 9,
							AUDIO_10				= 10,
							AUDIO_11				= 11,
							AUDIO_12				= 12,
							AUDIO_13				= 13,
							AUDIO_14				= 14,
							AUDIO_15				= 15,
							AUDIO_16				= 16,
							AUDIO_17				= 17,
							AUDIO_18				= 18,
							AUDIO_19				= 19,
							AUDIO_20				= 20,
							AUDIO_21				= 21,
							AUDIO_22				= 22,
							AUDIO_23				= 23,
							AUDIO_24				= 24,
							AUDIO_25				= 25,
							AUDIO_26				= 26,
							AUDIO_27				= 27,
							AUDIO_28				= 28,
							AUDIO_29				= 29,
							AUDIO_30				= 30,
							AUDIO_31				= 31;
			} AUDIO;

			// Default Music
			struct s_Music {
				const int	MUSIC_0_MainMenu				= 0,
							MUSIC_1							= 1,
							MUSIC_2							= 2,
							MUSIC_3							= 3,
							MUSIC_4							= 4,
							MUSIC_5							= 5,
							MUSIC_6							= 6,
							MUSIC_7							= 7,
							MUSIC_8							= 8,
							MUSIC_9							= 9,
							MUSIC_10_BattleLight			= 10,
							MUSIC_11_BattleNormal			= 11,
							MUSIC_12_BattleHeavy			= 12,
							MUSIC_13_BattleBoss				= 13,
							MUSIC_14_BattleSpecial			= 14,
							MUSIC_15_BattleImpossible		= 15,
							MUSIC_16_Battle_6				= 16,
							MUSIC_17_Battle_7				= 17,
							MUSIC_18_Battle_8				= 18,
							MUSIC_19_Battle_9				= 19,
							MUSIC_20_ExploreOcean			= 20,
							MUSIC_21_ExploreWetland			= 21,
							MUSIC_22_ExploreTemperateForest	= 22,
							MUSIC_23_ExploreTropicalForest	= 23,
							MUSIC_24_ExploreMountain		= 24,
							MUSIC_25_ExploreGrassland		= 25,
							MUSIC_26_ExploreDesert			= 26,
							MUSIC_27_ExplorePolar			= 27,
							MUSIC_28_Explore				= 28,
							MUSIC_29_Explore				= 29,
							MUSIC_30						= 30,
							MUSIC_31						= 31,
							MUSIC_32						= 32,
							MUSIC_33						= 33,
							MUSIC_34						= 34,
							MUSIC_35						= 35,
							MUSIC_36						= 36,
							MUSIC_37						= 37,
							MUSIC_38						= 38,
							MUSIC_39						= 39,
							MUSIC_40_Dungeon				= 40,
							MUSIC_41_Dungeon				= 41,
							MUSIC_42_Dungeon				= 42,
							MUSIC_43_Dungeon				= 43,
							MUSIC_44_Dungeon				= 44,
							MUSIC_45_Dungeon				= 45,
							MUSIC_46_Dungeon				= 46,
							MUSIC_47_Dungeon				= 47,
							MUSIC_48_Dungeon				= 48,
							MUSIC_49_Dungeon				= 49;
			} MUSIC;

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

			AudioSys::s_Audio & operator()()				{	return parent->AUDIO;	}		///< Get default audio index
			AudioSys::s_Channels & channel()				{	return parent->CHANNEL;	}		///< Get reserved channel number
			t_SoundItem& operator[](std::string name)		{	return *audio[name];	}		///< Get a sound item by name

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

			AudioSys::s_Music & operator()()				{	return parent->MUSIC;	}		///< Get default music index
			t_MusicItem& operator[](std::string name)		{	return *audio[name];		}

			t_MusicInstance();
			~t_MusicInstance();
	};





































}

#endif /* AUDIOSYS_H_ */
