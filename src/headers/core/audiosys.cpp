#include <iostream>

//#include "SDL2/SDL.h"
//#include "SDL2/SDL_mixer.h"
//#include <stdlib.h>
//#include <unistd.h>
//#include <chrono>
//#include <thread>
#include "types.h"
#include "audiosys.h"

namespace Core {
//	int AudioSys::iBeat = 0;
	AudioSys *t_AudioInstance::parent = nullptr;

	AudioSys::AudioSys() {
		uiRecordSize	= 32;
		sDir			= "./system/";
		sAudioDir		= "./audio/effects/";
		sMusicDir		= "./audio/music/";
		iInit = INIT_NONE;
		iDecoders = 0;
		iChannels = 0;
//		Mix_SetPostMix(setBeat, NULL);
	}

	AudioSys::~AudioSys() {
	}

	bool AudioSys::init() {
		//            .................................................................Done
		Core::debug.log("Init Audio {\n");
		Core::debug.logIncreaseIndent();

		bool bFail = false;

		if(Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG) {
			Core::debug.log("Mix_Init: error\n");
			bFail = true;
		}
		else {
			Core::debug.log("Mix_Init: success\n");
			iInit=iInit&INIT_MIX_INIT;
		}

		if(SDL_Init(SDL_INIT_AUDIO)==-1) {
			Core::debug.log("SDL_Init: error\n");
			bFail = true;
		}
		else {
			Core::debug.log("Sdl_Init: success\n");
			iInit=iInit&INIT_SDL_INIT_AUDIO;
		}

		if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096)==-1) {
			Core::debug.log("Mix_OpenAudio: error\n");
			bFail = true;
		}
		else {
			Core::debug.log("Mix_OpenAudio: success\n");
			iInit=iInit&INIT_MIX_OPENAUDIO;
		}

		iDecoders = Mix_GetNumMusicDecoders();
		Core::debug.log("Decoders: "+std::to_string(iDecoders)+"\n");

		// FIXME: Add an enumeration for channels (0=Animations, 1=GUI_Buttons, 2=GUI_Sliders, etc)
		iChannels = 64;
		Mix_AllocateChannels(iChannels);
		Core::debug.log("Allocated channels: "+std::to_string(iChannels)+"\n");

		Core::debug.logDecreaseIndent();
		Core::debug.print("}\n");
		return iInit;
	}

	bool AudioSys::load() {
		MemBlock memBlock;

		// =============================
		//	Load Sounds
		// -----------------------------
		Core::debug.log("Load Sound Effects {\n");
		Core::debug.logIncreaseIndent();

		sFilename		= "audio.bin";
		readFile((sDir+sFilename), memBlock);

		for (uint d=0; d<memBlock.size; d+=uiRecordSize) {
			t_SoundDefinition *newSound = new t_SoundDefinition();

			int id		= (__uint16_t)( (__uint8_t)(memBlock.buffer[0+d])*256 + (__uint8_t)(memBlock.buffer[1+d]) );
			int spare	= (__uint16_t)( (__uint8_t)(memBlock.buffer[2+d])*256 + (__uint8_t)(memBlock.buffer[3+d]) );

			std::string sAudioFile = "";
			for (int i=4; i<32; i++)
				if (memBlock.buffer[i+d]!=0) sAudioFile+=(unsigned char)memBlock.buffer[i+d];
				else break;

			newSound->chunk = Mix_LoadWAV((sAudioDir+sAudioFile).c_str());
			if(newSound->chunk) {
				debug.log("["+std::to_string(id)+"] "+sAudioFile+"\n", debug().YELLOW);
				newSound->bLoad = true;
			}
			else {
				debug.log("["+std::to_string(id)+"] "+sAudioFile+" FAILED\n", debug().RED);
			}

			//sound.add(id, newSound);
			Sound.data.add(id, newSound);

		}

		Core::debug.logDecreaseIndent();
		Core::debug.log("}\n");

		// =============================
		//	Load Music
		// -----------------------------
		Core::debug.log("Load Music {\n");
		Core::debug.logIncreaseIndent();

		sFilename		= "music.bin";
		readFile((sDir+sFilename), memBlock);

		for (uint d=0; d<memBlock.size; d+=uiRecordSize) {
			t_MusicDefinition *newMusic = new t_MusicDefinition();

			int id		= (__uint16_t)( (__uint8_t)(memBlock.buffer[0+d])*256 + (__uint8_t)(memBlock.buffer[1+d]) );
			int spare	= (__uint16_t)( (__uint8_t)(memBlock.buffer[2+d])*256 + (__uint8_t)(memBlock.buffer[3+d]) );

			std::string sAudioFile = "";
			for (int i=4; i<32; i++)
				if (memBlock.buffer[i+d]!=0) sAudioFile+=(unsigned char)memBlock.buffer[i+d];
				else break;

			newMusic->music = Mix_LoadMUS((sMusicDir + sAudioFile).c_str());
			if(newMusic->music) {
				debug.log("["+std::to_string(id)+"] "+sAudioFile+"\n", debug().YELLOW);
				newMusic->bLoad = true;
			}
			else {
				debug.log("["+std::to_string(id)+"] "+sAudioFile+" FAILED\n", debug().RED);
			}

			Music.data.add(id, newMusic);

		}

		Core::debug.log("}\n");
		Core::debug.logDecreaseIndent();

		return true;
	}

	void AudioSys::SoundInterface::play(int iSample, int iLoop, bool bOverlap, int iChannel) {	// 0=play once (no loops), -1=first available channel
		if (!bMute) {
			if (iChannel>=0 && Mix_Paused(iChannel)) {
				Mix_Resume(iChannel);
			}
			else if ( (iChannel==-1) || (iChannel>=0 && !Mix_Playing(iChannel) && bOverlap) ) {
				Mix_HaltChannel(iChannel);
				Mix_PlayChannel(iChannel, data[iSample]->chunk, iLoop);
			}
		}
	}

	void AudioSys::SoundInterface::pause(int iChannel) {
		Mix_Pause(iChannel);
	}

	void AudioSys::SoundInterface::stop(int iChannel) {
		Mix_HaltChannel(iChannel);
	}

	void AudioSys::SoundInterface::mute() {
		bMute = true;
		Mix_Volume(-1, 0);
	}

	void AudioSys::SoundInterface::unmute() {
		bMute = false;
		Mix_Volume(-1, iVolume);
	}

	void AudioSys::SoundInterface::setVolume(int iVol) {
		if(!bMute) {
			iVolume = iVol;
			Mix_Volume(-1, iVolume);
		}
	}


	void AudioSys::MusicInterface::play(int iSample, int iLoop, int iFade) {
		if (!bMute) {
			if(Mix_PausedMusic()) {
				Mix_ResumeMusic();
			}
			else if(!Mix_PlayingMusic()) {											// If music isn't already playing
				if(data[iSample]->bLoad) {										// If this sample was successfully loaded
					if(iFade>0) {
						Mix_FadeInMusic(data[iSample]->music, iLoop, iFade);
					}
					else Mix_PlayMusic(data[iSample]->music, iLoop);			// Play the music!
				}
			}
		}
	}

	void AudioSys::MusicInterface::pause() {
		Mix_PauseMusic();
	}

	void AudioSys::MusicInterface::stop() {
		Mix_HaltMusic();
	}

	void AudioSys::MusicInterface::mute() {
		bMute = true;
		Mix_Volume(-1, 0);
	}

	void AudioSys::MusicInterface::unmute() {
		bMute = false;
		Mix_Volume(-1, iVolume);
	}

	void AudioSys::MusicInterface::setVolume(int iVol) {
		if(!bMute) {
			iVolume = iVol;
			Mix_Volume(-1, iVolume);
		}
	}

	//void AudioSys::getBeat(int chan, void *stream, int len, void *udata) {
//	void AudioSys::setBeat(void *udata, __uint8_t *stream, int len) {
//		//cout << len << "\t" << &stream << endl;
//		//printf("[%i] %i\n", len, *stream);
//		iBeat = *stream;
//		//cout << "[" << len << "]\t" << iBeat << endl;
//	}

//	__uint8_t AudioSys::getBeat() {
//		return iBeat;
//	}



	// ============================================================================================================================
	//	t_AudioInstance
	// ============================================================================================================================

	t_AudioInstance::t_AudioInstance() {
//		list.setSource("t_AnimationInstance");
		parent = &audioSys;
	}

	t_AudioInstance::~t_AudioInstance() {

	}

	void t_AudioInstance::add(std::string name, int iSample, int iLoop, bool bOverlap, int iChannel) {
		t_SoundItem *newSound = new t_SoundItem();
		newSound->iSample = iSample;
		newSound->loop = iLoop;
		newSound->iChannel = iChannel;
		newSound->bOverlap = bOverlap;
		sound.add(name, newSound);
	}

	void t_AudioInstance::remove(std::string name) {
		sound.remove(name);
	}

	void t_AudioInstance::play(std::string name) {
		parent->Sound.play(sound[name]->iSample, sound[name]->loop, sound[name]->bOverlap, sound[name]->iChannel);
	}

	void t_AudioInstance::pause(std::string name) {
		parent->Sound.pause(sound[name]->iChannel);
	}

	void t_AudioInstance::stop(std::string name) {
		parent->Sound.stop(sound[name]->iChannel);
	}






































}
