#include <iostream>

#include "core_functions.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
//#include <stdlib.h>
//#include <unistd.h>
//#include <chrono>
//#include <thread>
#include "audiosys.h"

namespace Core {
	int AudioSys::iBeat = 0;

	AudioSys::AudioSys() {
		iInit = INIT_NONE;
		iDecoders = 0;
		iChannels = 0;
		bMute = false;
		//if(!Mix_RegisterEffect(MIX_CHANNEL_POST, getBeat, NULL, NULL)) {
		Mix_SetPostMix(setBeat, NULL);
		//	cout << "Mix_RegisterEffect error: " << Mix_GetError() << endl;
		//}
	}

	AudioSys::~AudioSys() {

		// Handled locally in struct
//		for(int iCount=0; iCount<128; iCount++) {
//			if(musicItem[iCount].sample != nullptr) delete musicItem[iCount].sample;
//		}
	}

	bool AudioSys::init() {
		//            .................................................................Done
		Core::debug.log("Init Audio {");

		bool bFail = false;

		if(Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG) {
			//cout << "   Mix_Init error: " << Mix_GetError() << endl;
			bFail = true;
		}
		else {
			//cout << "   Mix_Init success." << endl;
			iInit=iInit&INIT_MIX_INIT;
		}

		if(SDL_Init(SDL_INIT_AUDIO)==-1) {
			//cout << "   SDL_Init error: " << SDL_GetError() << endl;
			bFail = true;
		}
		else {
			//cout << "   Sdl_Init success." << endl;
			iInit=iInit&INIT_SDL_INIT_AUDIO;
		}

		if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096)==-1) {
		//if(Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048)==-1) {
			//cout << "   Mix_OpenAudio error: " << Mix_GetError() << endl;
			bFail = true;
		}
		else {
			//cout << "   Mix_OpenAudio success." << endl;
			iInit=iInit&INIT_MIX_OPENAUDIO;
		}

		iDecoders = Mix_GetNumMusicDecoders();
		//cout << "   Maximum number of music decoders: " << iDecoders << endl;
		//for(int i=0; i<iDecoders; ++i) {
		//	cout << "      [" << i << "] " << Mix_GetMusicDecoder(i) << endl;
		//}

		// FIXME: Add an enumeration for channels (0=Animations, 1=GUI_Buttons, 2=GUI_Sliders, etc)
		iChannels = 64;
		Mix_AllocateChannels(iChannels);
		//cout << "   Allocated " << iChannels << " mixing channels." << endl;

		if (bFail) Core::debug.print(" Failed", Core::debug().RED);
		else Core::debug.print(" Done ", Core::debug().GREEN);
		Core::debug.print("}\n");
		return iInit;
	}

	bool AudioSys::load() {

		Core::debug.log("Load Sound Effects {\n");
		Core::debug.logIncreaseIndent();

		__uint8_t iCount	= 0;
		std::string sDir				= "./audio/effects/";
		std::string sFile			= "";

		// Load Sound Effects
		iCount = 0;			sFile = "battle_hit.ogg";			loadSound(iCount, sDir+sFile);
		iCount = 1;			sFile = "click1.ogg";				loadSound(iCount, "./audio/gui/"+sFile);
		iCount = 2;			sFile = "click2.ogg";				loadSound(iCount, "./audio/gui/"+sFile);

		iCount = 3;			sFile = "check1.ogg";				loadSound(iCount, "./audio/gui/"+sFile);
		iCount = 4;			sFile = "check2.ogg";				loadSound(iCount, "./audio/gui/"+sFile);

		iCount = 5;			sFile = "icon1.ogg";				loadSound(iCount, "./audio/gui/"+sFile);
		iCount = 6;			sFile = "icon2.ogg";				loadSound(iCount, "./audio/gui/"+sFile);

		iCount = 7;			sFile = "slider1.ogg";				loadSound(iCount, "./audio/gui/"+sFile);
		iCount = 8;			sFile = "slider2.ogg";				loadSound(iCount, "./audio/gui/"+sFile);

//		iCount = SOUNDS.BATTLE.SWORD_HIT;			sFile = "battle_hit.ogg";			loadSound(iCount, sDir+sFile);
//		iCount = SOUNDS.BATTLE.GLANCE;				sFile = "battle_glance.ogg";		loadSound(iCount, sDir+sFile);
//		iCount = SOUNDS.BATTLE.DODGE;				sFile = "battle_dodge.ogg";			loadSound(iCount, sDir+sFile);
//		iCount = SOUNDS.BATTLE.DEFLECT;				sFile = "battle_deflect.ogg";		loadSound(iCount, sDir+sFile);
//		iCount = SOUNDS.BATTLE.BLOCK;				sFile = "battle_block.ogg";			loadSound(iCount, sDir+sFile);
//		iCount = SOUNDS.JOURNAL.OPEN;				sFile = "journal_open.ogg";			loadSound(iCount, sDir+sFile);
//		iCount = SOUNDS.JOURNAL.CLOSE;				sFile = "journal_close.ogg";		loadSound(iCount, sDir+sFile);
//		iCount = SOUNDS.JOURNAL.NEXT;				sFile = "journal_next.ogg";			loadSound(iCount, sDir+sFile);
//		iCount = SOUNDS.JOURNAL.PREV;				sFile = "journal_prev.ogg";			loadSound(iCount, sDir+sFile);

		//******************************************************************************************************************************

		Core::debug.logDecreaseIndent();
		Core::debug.log("}\n");
		Core::debug.log("Load Music {\n");
		Core::debug.logIncreaseIndent();

		// Load Music
		iCount = 0;
		sDir	= "./audio/music/";
		sFile = "Sneaky Adventure.mp3";
		musicItem[iCount].music = Mix_LoadMUS((sDir + sFile).c_str());

		Core::debug.log("["+std::to_string(iCount)+"] "+sFile+" (Incomplete Loader)\n", Core::debug().RED);

//		if(!musicItem[iCount].sample) {
//			cout << "[" << (int)iCount << "] Error loading '"<< (sDir + sFile) << "': " << Mix_GetError() << endl;
//		}
//		else {
//			cout << "   [" << (int)iCount << "] '" << (sDir + sFile) << "'" << endl;
//			musicItem[iCount].bLoad = true;
//		}
		if(musicItem[iCount].music) musicItem[iCount].bLoad = true;

//		++iCount;
//		sFile = "Vanishing.ogg";
//		musicItem[iCount].sample = Mix_LoadMUS((sDir + sFile).c_str());
//		if(!musicItem[iCount].sample) {
//			cout << "[" << (int)iCount << "] Error loading '"<< (sDir + sFile) << "': " << Mix_GetError() << endl;
//		}
//		else {
//			cout << "   [" << (int)iCount << "] '" << (sDir + sFile) << "'" << endl;
//			musicItem[iCount].bLoad = true;
//		}
//
//		++iCount;
//		sFile = "Killers.ogg";
//		musicItem[iCount].sample = Mix_LoadMUS((sDir + sFile).c_str());
//		if(!musicItem[iCount].sample) {
//			cout << "[" << (int)iCount << "] Error loading '"<< (sDir + sFile) << "': " << Mix_GetError() << endl;
//		}
//		else {
//			cout << "   [" << (int)iCount << "] '" << (sDir + sFile) << "'" << endl;
//			musicItem[iCount].bLoad = true;
//		}

		// TODO: Load audio from file
	//	try {
	//		if (gameVars->debug.load) printf("\n ###################\n");
	//		if (gameVars->debug.load) printf("## LOADING ICONS\n");
	//		MemBlock *memBlock = new MemBlock;
	//		std::string theImage;
	//		gameVars->texture.icons.Begin(gameVars->texture.uiNumTextures);
	//		std::ifstream myFile((char*)"icons.bin", std::ifstream::in | std::ifstream::binary);
	//		if (myFile.is_open()) {
	//			if( memBlock->buffer ) {
	//				delete[] memBlock->buffer;
	//				memBlock->buffer = NULL;
	//			}
	//			myFile.seekg(0, std::ifstream::end);
	//			memBlock->size = myFile.tellg();
	//			memBlock->buffer = new char[memBlock->size];
	//			myFile.seekg(0, std::ifstream::beg);
	//			myFile.read(memBlock->buffer, memBlock->size);
	//			myFile.close();
	//		}
	//		else memBlock->size = 0;
	//
	//		for (int d=0; d<memBlock->size; d+=gameVars->recordSize.imageId) {
	//			int theId=0;
	//			for (int i=0; i<4; i++) theId+=(unsigned char)memBlock->buffer[i+d];
	//
	//			theImage = "";
	//			for (int i=4; i<32; i++)
	//				if (memBlock->buffer[i+d]!=0) theImage+=(unsigned char)memBlock->buffer[i+d];
	//				else break;
	//
	//			if (gameVars->debug.load) printf(" [%i] %s\n", theId, theImage.c_str());
	//			gameVars->texture.icons.Load(gameVars->dir.icons, theImage, theId, false, GL_NEAREST);
	//		}
	//		delete memBlock;
	//
	//		return true;
	//	}
	//	catch(...) {
	//		return false;
	//	}

		Core::debug.log("}\n");
		Core::debug.logDecreaseIndent();

		return true;
	}

	void AudioSys::loadSound(int iCount, std::string sLoad) {
		Core::debug.log("["+std::to_string(iCount)+"] "+sLoad+" (Incomplete Loader)\n", Core::debug().RED);

		soundItem[iCount].chunk = Mix_LoadWAV(sLoad.c_str());
		//if(!soundItem[iCount].sample) cout << "[" << iCount << "] Error loading '"<< sLoad << "': " << Mix_GetError() << endl;
		//else { cout << "   [" << iCount << "] '" << sLoad << "'" << endl; soundItem[iCount].bLoad = true; }

		if(soundItem[iCount].chunk) soundItem[iCount].bLoad = true;

		// Preview sound after loading
	//	playSound(iCount, 0, -1);
	//	Timer t;
	//	t.start();
	//	int i = t.get_ticks();
	//	while(t.get_ticks()<(i+500));
	}

	void AudioSys::playSound(int iSample, int iLoop, bool bOverlap, int iChannel) {	// 0=play once (no loops), -1=first available channel
		if(bOverlap || !Mix_Playing(iChannel)) {
			Mix_HaltChannel(iChannel);
			Mix_PlayChannel(iChannel, soundItem[iSample].chunk, iLoop);
		}
	}

	void AudioSys::playMusic(int iSample, int iLoop, int iFade) {
		if (!bMute) {
			if(!Mix_PlayingMusic()) {																	// If music isn't already playing
				if(musicItem[iSample].bLoad) {													// If this sample was successfully loaded
					if(iFade>0) {
						Mix_FadeInMusic(musicItem[iSample].music, iLoop, iFade);
					}
					else Mix_PlayMusic(musicItem[iSample].music, iLoop);			// Play the music!
				}
			}
		}
	}

	void AudioSys::playMusic(__uint8_t ui) {
//		if (!bMute) {
//			switch(ui) {
//				case MUSIC_WORLDEXPLORE: {
//					// todo: Randomize all available music
//					//int iRand = rand() %
//				}
//				break;
//				case MUSIC_WORLDBATTLE: {
//
//				}
//				break;
//			}
//		}
	}

	void AudioSys::fadeOutMusic(__uint8_t ui, int ms=1000) {
//		if (!bMute) {
//			switch(ui) {
//				case MUSIC_WORLDEXPLORE: {
//					Mix_FadeOutMusic(ms);
//				}
//				break;
//				case MUSIC_WORLDBATTLE: {
//					Mix_FadeOutMusic(ms);
//				}
//				break;
//			}
//		}
	}

	void AudioSys::stopMusic() {
		Mix_HaltMusic();
	}

	//void AudioSys::getBeat(int chan, void *stream, int len, void *udata) {
	void AudioSys::setBeat(void *udata, __uint8_t *stream, int len) {
		//cout << len << "\t" << &stream << endl;
		//printf("[%i] %i\n", len, *stream);
		iBeat = *stream;
		//cout << "[" << len << "]\t" << iBeat << endl;
	}

	__uint8_t AudioSys::getBeat() {
		return iBeat;
	}
}
