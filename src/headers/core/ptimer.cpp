#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
#include <string>

#include "SDL2/SDL.h"

#include "types.h"
#include "core_functions.h"
#include "ptimer.h"

namespace Core {
	PTimer::PTimer() {
		//            .................................................................Done
		std::cout << "Construct PTimer.................................................";
		SDL_Init(SDL_INIT_TIMER);
		iTimers			= 0;
		iMaxTimers		= 100;
		buffer			= new std::string[iMaxTimers];
		started			= new bool[iMaxTimers];
		splitTicks		= new uint[iMaxTimers];
		startTicks		= new uint[iMaxTimers];
		stopTicks		= new uint[iMaxTimers];
		splitAverage	= new float[iMaxTimers];
		splitMax		= new float[iMaxTimers];
		splitMin		= new float[iMaxTimers];
		splitNum		= new uint[iMaxTimers];
		uiSamples		= new uint[iMaxTimers];
		uiSamplesMem	= new uint[iMaxTimers];
		fAverageMem		= new float[iMaxTimers];
		rsStdDev		= new RunningStat[iMaxTimers];
		uiTicksMem		= new uint[iMaxTimers];

		std::cout << "Done" << std::endl;
	}

	PTimer::~PTimer() {
		//       .................................................................Done
		std::cout << "Destroy PTimer...................................................";
		delete [] buffer;
		delete [] started;
		delete [] splitTicks;
		delete [] startTicks;
		delete [] stopTicks;
		delete [] splitAverage;
		delete [] splitMax;
		delete [] splitMin;
		delete [] splitNum;
		delete [] uiSamples;
		delete [] uiSamplesMem;
		delete [] fAverageMem;
		delete [] rsStdDev;
		delete [] uiTicksMem;
		std::cout << "Done" << std::endl;
	}

	// Add a timer to the next available index
	int PTimer::addTimer(std::string s) {
		if (iTimers < iMaxTimers) {
			iTimers++;
			//started[iTimers] = new bool;
			buffer[iTimers]			= "";
			started[iTimers]		= false;
			splitTicks[iTimers]		= 0;
			startTicks[iTimers]		= 0;
			stopTicks[iTimers]		= 0;
			splitAverage[iTimers]	= 0;
			splitMax[iTimers]		= 0.0f;
			splitMin[iTimers]		= 99.0f;
			splitNum[iTimers]		= 0;
			uiSamples[iTimers]		= 0;
			uiSamplesMem[iTimers]	= 0;
			fAverageMem[iTimers]	= 0;
			uiTicksMem[iTimers]		= 0;

			TimerId.insert(std::make_pair(s, iTimers));
			return 1;
		}
		else {
			return 0;
		}
	}

	std::string PTimer::getSplitTickString(std::string name) {
		uint id = TimerId[name];
		return getSplitTickString(id);
	}

	std::string PTimer::getSplitTickString(uint id) {
		return buffer[id];
	}

	uint PTimer::getSplitTicks(std::string name) {
		uint id = TimerId[name];
		return getSplitTicks(id);
	}

	uint PTimer::getSplitTicks(uint id) {
		return splitTicks[id];
	}

	uint PTimer::getTicks(std::string name) {
		uint id = TimerId[name];
		return getTicks(id);
	}

	uint PTimer::getTicks(uint id) {
		return SDL_GetTicks() - startTicks[id];
	}

	void PTimer::start(std::string name) {
		uint id = TimerId[name];
		start(id);
	}

	void PTimer::start(uint id) {
		if (!started[id]) {
			//Start the timer
			started[id] = true;

			//Get the current clock time
			startTicks[id] = SDL_GetTicks();
			//splitTicks[id] = startTicks[id];
		}
	}

	void PTimer::update(std::string name) {
		uint id = TimerId[name];
		update(id);
	}

	void PTimer::update(uint id) {
		splitTicks[id]=SDL_GetTicks() - startTicks[id];
		buffer[id]=itoa(splitTicks[id], 10);

		// Track Max
		if (splitTicks[id] > splitMax[id]) splitMax[id] = splitTicks[id];

		// Track Min
		if (splitTicks[id] < splitMin[id]) splitMin[id] = splitTicks[id];

		// Find average (bad method, us rsStdDev class)
		splitAverage[id] = (splitAverage[id] + splitTicks[id]) / 2;

		rsStdDev[id].Push(splitTicks[id]);

		uiSamples[id] += 1;
	}

	uint PTimer::stop(std::string name, bool bReset) {
		uint id = TimerId[name];
		return stop(id, bReset);
	}

	uint PTimer::stop(uint id, bool bReset) {
		started[id] = false;
		splitTicks[id]=SDL_GetTicks() - startTicks[id];
		buffer[id]=itoa(splitTicks[id], 10);

		// Add to times taken
	//	splitNum[id]++;

		// Track Max
		if (splitTicks[id] > splitMax[id]) splitMax[id] = splitTicks[id];

		// Track Min
		if (splitTicks[id] < splitMin[id]) splitMin[id] = splitTicks[id];

		// Find average (bad method, us rsStdDev class)
		splitAverage[id] = (splitAverage[id] + splitTicks[id]) / 2;

		rsStdDev[id].Push(splitTicks[id]);

		uint uiCurrentSamples = uiSamples[id];

		if (!bReset) uiSamples[id] += 1;
		else uiSamples[id] = 0;

		return uiCurrentSamples;
	}

	float PTimer::GetStdDev(std::string name) {
		uint id = TimerId[name];
		return rsStdDev[id].StandardDeviation();
	}

	float PTimer::GetMax(std::string name) {
		uint id = TimerId[name];
		return splitMax[id];
	}

	float PTimer::GetMin(std::string name) {
		uint id = TimerId[name];
		return splitMin[id];
	}

	uint PTimer::GetSamples(std::string name) {
		uint id = TimerId[name];
		return uiSamples[id];
	}

	float PTimer::GetAverage(std::string name, uint uiUpdateSamples, uint uiUpdateTicks) {

		/*
		 * TODO: limit return rate
		 *
		 * If n samples have not passed since last call, then return same value as last time
		 * If n smaples have passed, then update call samples and return value
		 *
		 * TODO: make this update limit apply to everything?
		 */

		uint id = TimerId[name];
		uint uiSplitMem = SDL_GetTicks() - uiTicksMem[id];

		//std::cout << std::to_string(SDL_GetTicks()) << " : " << std::to_string(uiSplitMem) << std::endl;

		if((uiSamples[id] >= uiSamplesMem[id]+uiUpdateSamples) || (uiSplitMem >= uiUpdateTicks)) {
			uiSamplesMem[id] = uiSamples[id];
			uiTicksMem[id] = SDL_GetTicks();
			//fAverageMem[id] = splitAverage[id];
			fAverageMem[id] = rsStdDev[id].Mean();
			//std::cout << std::to_string(splitAverage[id]) << " : " << std::to_string(rsStdDev[id].Mean()) << " : " << std::to_string(rsStdDev[id].Variance()) << std::endl;
		}

		return fAverageMem[id];
	}

	void PTimer::ResetMin() {
		for(uint i=0; i<=iTimers; i++) {
			splitMin[i] = 99.0f;
		}
	}

	void PTimer::ResetMin(std::string name) {
		uint id = TimerId[name];
		splitMin[id] = 99.0f;
	}

	void PTimer::ResetMax() {
		for(uint i=0; i<=iTimers; i++) {
			splitMax[i] = 0;
		}
	}

	void PTimer::ResetMax(std::string name) {
		uint id = TimerId[name];
		splitMax[id] = 0;
	}

	void PTimer::ResetAverage() {
		for(uint i=0; i<=iTimers; i++) {
			splitAverage[i] = 0;
		}
	}

	void PTimer::ResetAverage(std::string name) {
		uint id = TimerId[name];
		splitAverage[id] = 0;
	}

	void PTimer::ResetStdDev() {
		for(uint i=0; i<=iTimers; i++) {
			rsStdDev[i].Clear();
		}
	}

	void PTimer::ResetStdDev(std::string name) {
		uint id = TimerId[name];
		rsStdDev[id].Clear();
	}

	void PTimer::ResetSamples() {
		for(uint i=0; i<=iTimers; i++) {
			uiSamples[i] = 0;
		}
	}

	void PTimer::ResetSamples(std::string name) {
		uint id = TimerId[name];
		uiSamples[id] = 0;
	}
}
