/*
 * timer.hpp
 *
 *  Created on: May 19, 2010
 *      Author: Brian ThunderEagle
 *
 *      A basic timer
 */

#ifndef TIMER_HPP_
#define TIMER_HPP_

namespace Core {
	class Timer
	{
		private:
			int pausedTicks;	//The ticks stored when the timer was paused

			bool paused;		//The timer status
			bool started;		//The timer status
			int splitTicks;	//Stores the split time marker

		public:
			int startTicks;	//The clock time when the timer started
			int rate, rateMod;

			//Initializes variables
			Timer();

			//The various clock actions
			void set(float fTime);
			void start();
			void stop();
			void pause();
			void unpause();
			int split();
			int get_split();
			int get_splitdiff();
			void reset();

			//Gets the timer's time
			int	get_ticks();
	//		uint	get_MilliSeconds() {
	//			uint uiCurrentTicks = get_ticks();
	//
	//			return 0;
	//		}
	//		uint	get_Seconds() {
	//
	//			return 0;
	//		}
	//		uint	get_Hours() {
	//			uint currentDays = get_Days();
	//			return currentDays * 24;
	//		}
	//		uint	get_Days() {
	//			return 0;
	//		}

			//Checks the status of the timer
			bool is_started();
			bool is_paused();
	};
}

#endif /* TIMER_HPP_ */
