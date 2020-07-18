/*
 * FrameRate.cpp
 *
 *  Created on: Aug 28, 2019
 *      Author: bcthund
 */

#include "SDL2/SDL.h"
#include "FrameRate.h"

namespace Core {
	_FrameRate::_FrameRate() {
		timer.addTimer("FPS");
		fps = 0.0f;
	}

	_FrameRate::~_FrameRate() {
	}

	void _FrameRate::start() {
		timer.start("FPS");
	}

	void _FrameRate::update() {
		//std::cout << "  Ticks: " << getTicks() << std::endl;
		//std::cout << "Samples: " << getSamples() << std::endl;
		//std::cout << (float)getSamples()/((float)getTicks()/1000.0f) << std::endl;
		timer.update("FPS");
		if (getTicks() >= 1000) {
			uint samples = timer.stop("FPS", true);

			// Update FrameRate value
			fps = (float)samples/((float)getTicks()/1000.0f);
		}

	}

	void _FrameRate::stop() {
		timer.stop("FPS");
	}

	uint _FrameRate::getTicks() {
		return timer.getTicks("FPS");
		//return PTimer::getTicks("FPS");
	}

	uint _FrameRate::getSplitTicks() {
		return timer.getSplitTicks("FPS");
		//return PTimer::getSplitTicks("FPS");
	}

	uint _FrameRate::getSamples() {
		return timer.GetSamples("FPS");
		//return PTimer::GetSamples("FPS");
	}

	float _FrameRate::getStdDev() {
		return timer.GetStdDev("FPS")/1000.0f;
		//return PTimer::GetStdDev("FPS");
	}

	template <typename T>
	T _FrameRate::getFPS() {
		return (T)fps;
	}

	template int	_FrameRate::getFPS<int>();
	template uint	_FrameRate::getFPS<uint>();
	template float	_FrameRate::getFPS<float>();

} /* namespace Core */
































