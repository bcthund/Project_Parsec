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
		Core::debug.log("Construct PTimer {");

		SDL_Init(SDL_INIT_TIMER);
//		iTimers			= 0;
//		iMaxTimers		= 100;
//		buffer			= new std::string[iMaxTimers];
//		started			= new bool[iMaxTimers];
//		splitTicks		= new uint[iMaxTimers];
//		startTicks		= new uint[iMaxTimers];
//		stopTicks		= new uint[iMaxTimers];
//		splitAverage	= new float[iMaxTimers];
//		splitMax		= new float[iMaxTimers];
//		splitMin		= new float[iMaxTimers];
//		splitNum		= new uint[iMaxTimers];
//		uiSamples		= new uint[iMaxTimers];
//		uiSamplesMem	= new uint[iMaxTimers];
//		fAverageMem		= new float[iMaxTimers];
//		rsStdDev		= new RunningStat[iMaxTimers];
//		uiTicksMem		= new uint[iMaxTimers];

		Core::debug.print(" Done ", Core::debug().GREEN);
		Core::debug.print("}\n");
	}

	PTimer::~PTimer() {
		Core::debug.log("Destroy PTimer {");

//		delete [] buffer;
//		delete [] started;
//		delete [] splitTicks;
//		delete [] startTicks;
//		delete [] stopTicks;
//		delete [] splitAverage;
//		delete [] splitMax;
//		delete [] splitMin;
//		delete [] splitNum;
//		delete [] uiSamples;
//		delete [] uiSamplesMem;
//		delete [] fAverageMem;
//		delete [] rsStdDev;
//		delete [] uiTicksMem;
		for (auto &item : timers) {
			delete item;
		}

		Core::debug.print(" Done ", Core::debug().GREEN);
		Core::debug.print("}\n");
	}

	int PTimer::addTimer(std::string s) {
		t_PTimer *newTimer = new t_PTimer();

		newTimer->buffer		= "";
		newTimer->started		= false;
		newTimer->splitTicks	= 0;
		newTimer->startTicks	= 0;
		newTimer->stopTicks		= 0;
		newTimer->splitAverage	= 0;
		newTimer->splitMax		= 0.0f;
		newTimer->splitMin		= 99.0f;
		newTimer->splitNum		= 0;
		newTimer->uiSamples		= 0;
		newTimer->uiSamplesMem	= 0;
		newTimer->fAverageMem	= 0;
		newTimer->uiTicksMem	= 0;

		timers.add(s, newTimer);

		return timers.getID(s);
	}

	std::string PTimer::getSplitTickString(std::string name)	{	return timers[name]->buffer;	}
	std::string PTimer::getSplitTickString(uint id)				{	return timers[id]->buffer;			}
	uint PTimer::getSplitTicks(std::string name)				{	return timers[name]->splitTicks;	}
	uint PTimer::getSplitTicks(uint id)							{	return timers[id]->splitTicks;		}
	uint PTimer::getTicks(std::string name)						{	return SDL_GetTicks() - timers[name]->startTicks;	}
	uint PTimer::getTicks(uint id)								{	return SDL_GetTicks() - timers[id]->startTicks;		}

	void PTimer::start(std::string name) {
		if (!timers[name]->started) {
			timers[name]->started = true;
			timers[name]->startTicks = SDL_GetTicks();
		}
	}

	void PTimer::start(uint id) {
		if (!timers[id]->started) {
			timers[id]->started = true;
			timers[id]->startTicks = SDL_GetTicks();
		}
	}

	void PTimer::update(std::string name) {
		uint id = timers.getID(name);
		update(id);
	}

	void PTimer::update(uint id) {
		timers[id]->splitTicks=SDL_GetTicks() - timers[id]->startTicks;
		timers[id]->buffer=itoa(timers[id]->splitTicks, 10);

		// Track Max
		if (timers[id]->splitTicks > timers[id]->splitMax) timers[id]->splitMax = timers[id]->splitTicks;

		// Track Min
		if (timers[id]->splitTicks < timers[id]->splitMin) timers[id]->splitMin = timers[id]->splitTicks;

		// Find average (bad method, us rsStdDev class)
		timers[id]->splitAverage = (timers[id]->splitAverage + timers[id]->splitTicks) / 2;

		timers[id]->rsStdDev.Push(timers[id]->splitTicks);

		timers[id]->uiSamples += 1;
	}

	uint PTimer::stop(std::string name, bool bReset) {
		uint id = timers.getID(name);
		return stop(id, bReset);
	}

	uint PTimer::stop(uint id, bool bReset) {
		timers[id]->started = false;
		timers[id]->splitTicks=SDL_GetTicks() - timers[id]->startTicks;
		timers[id]->buffer=itoa(timers[id]->splitTicks, 10);

		// Add to times taken
	//	splitNum[id]++;

		// Track Max
		if (timers[id]->splitTicks > timers[id]->splitMax) timers[id]->splitMax = timers[id]->splitTicks;

		// Track Min
		if (timers[id]->splitTicks < timers[id]->splitMin) timers[id]->splitMin = timers[id]->splitTicks;

		// Find average (bad method, us rsStdDev class)
		timers[id]->splitAverage = (timers[id]->splitAverage + timers[id]->splitTicks) / 2;

		timers[id]->rsStdDev.Push(timers[id]->splitTicks);

		uint uiCurrentSamples = timers[id]->uiSamples;

		if (!bReset) timers[id]->uiSamples += 1;
		else timers[id]->uiSamples = 0;

		return uiCurrentSamples;
	}

	float PTimer::GetStdDev(std::string name) {
		return timers[name]->rsStdDev.StandardDeviation();
	}

	float PTimer::GetMax(std::string name) {
		return timers[name]->splitMax;
	}

	float PTimer::GetMin(std::string name) {
		return timers[name]->splitMin;
	}

	uint PTimer::GetSamples(std::string name) {
		return timers[name]->uiSamples;
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
		uint uiSplitMem = SDL_GetTicks() - timers[name]->uiTicksMem;

		//std::cout << std::to_string(SDL_GetTicks()) << " : " << std::to_string(uiSplitMem) << std::endl;

		if((timers[name]->uiSamples >= timers[name]->uiSamplesMem+uiUpdateSamples) || (uiSplitMem >= uiUpdateTicks)) {
			timers[name]->uiSamplesMem = timers[name]->uiSamples;
			timers[name]->uiTicksMem = SDL_GetTicks();
			//fAverageMem[id] = splitAverage[id];
			timers[name]->fAverageMem = timers[name]->rsStdDev.Mean();
			//std::cout << std::to_string(splitAverage[id]) << " : " << std::to_string(rsStdDev[id].Mean()) << " : " << std::to_string(rsStdDev[id].Variance()) << std::endl;
		}

		return timers[name]->fAverageMem;
	}

	void PTimer::ResetMin() {
		for(auto &item : timers) {
			item->splitMin = 99.0f;
		}
	}

	void PTimer::ResetMin(std::string name) {
		timers[name]->splitMin = 99.0f;
	}

	void PTimer::ResetMax() {
		for(auto &item : timers) {
			item->splitMax = 0;
		}
	}

	void PTimer::ResetMax(std::string name) {
		timers[name]->splitMax = 0;
	}

	void PTimer::ResetAverage() {
		for(auto &item : timers) {
			item->splitAverage = 0;
		}
	}

	void PTimer::ResetAverage(std::string name) {
		timers[name]->splitAverage = 0;
	}

	void PTimer::ResetStdDev() {
		for(auto &item : timers) {
			item->rsStdDev.Clear();
		}
	}

	void PTimer::ResetStdDev(std::string name) {
		timers[name]->rsStdDev.Clear();
	}

	void PTimer::ResetSamples() {
		for(auto &item : timers) {
			item->uiSamples = 0;
		}
	}

	void PTimer::ResetSamples(std::string name) {
		timers[name]->uiSamples = 0;
	}
}
