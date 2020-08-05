/*
 * ptimer.h
 *
 *  Created on: Sep 6, 2010
 *      Author: bcthund
 *
 *      This is a Precise Timer class, it can be used for timing processes in milliseconds
 */

#ifndef PTIMER_H_
#define PTIMER_H_

#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
#include <string>
#include "types.h"
#include "core_functions.h"
#include "RunningStat.h"

namespace Core {
	/*
	 * Process Timer
	 *
	 * Used to track time that a process has taken and
	 * 	keep running statistics on it.
	 */
	class PTimer
	{
		protected:
			typedef struct t_PTimer {
				bool		started;		///< Has the timer been started
				uint		startTicks;		///< Time when the timer starts
				uint		stopTicks;		///< Time when timer stopped
				uint		splitTicks;		///< Time difference after timer stopped
				float		splitAverage;	///< Running average for timer
				float		splitMax;		///<
				float		splitMin;		///<
				uint		splitNum;		///< Number of times timer value taken
				std::string	buffer;			///<
				uint		uiSamples;		///< Number of samples taken
				uint		uiSamplesMem;	///< Number of samples at last update
				float		fAverageMem;	///< Average reported at last update
				RunningStat	rsStdDev;		///< Statistics Class, used for standard deviation
				uint		uiTicksMem;		///< Ticks at time of last update
			} t_PTimer;

		public:
			PTimer();
			~PTimer();

			t_VectorMap<t_PTimer*> timers;

			int addTimer(std::string s);		// Next available timer
			std::string getSplitTickString(uint id);
			std::string getSplitTickString(std::string name);
			uint getSplitTicks(uint id);
			uint getSplitTicks(std::string name);
			uint getTicks(uint id);
			uint getTicks(std::string name);
			void start(uint id);
			void start(std::string name);
			void update(uint id);
			void update(std::string name);
			uint stop(uint id, bool bReset=false);
			uint stop(std::string name, bool bReset=false);
			float GetMax(std::string name);
			float GetMin(std::string name);
			uint GetSamples(std::string name);
			float GetStdDev(std::string name);
			float GetAverage(std::string name, uint uiUpdateRate=500, uint uiUpdateTicks=500);
			void ResetMin();
			void ResetMin(std::string name);
			void ResetMax();
			void ResetMax(std::string name);
			void ResetAverage();
			void ResetAverage(std::string name);
			void ResetStdDev();
			void ResetStdDev(std::string name);
			void ResetSamples();
			void ResetSamples(std::string name);
	};
}

#endif /* PTIMER_H_ */
