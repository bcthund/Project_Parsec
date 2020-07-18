/*
 * FrameRate.h
 *
 *  Created on: Aug 28, 2019
 *      Author: bcthund
 */

#ifndef HEADERS_CORE_FRAMERATE_H_
#define HEADERS_CORE_FRAMERATE_H_

#include "ptimer.h"
#include "types.h"

namespace Core {

	class _FrameRate {
		private:
			PTimer timer;

			float fps;

		public:
			_FrameRate();
			virtual ~_FrameRate();
			void start();
			void update();
			void stop();
			uint getTicks();
			uint getSplitTicks();
			uint getSamples();
			float getStdDev();

			template <typename T>
			T getFPS();
	};

} /* namespace Core */

#endif /* HEADERS_CORE_FRAMERATE_H_ */
