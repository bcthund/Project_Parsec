/*
 * GameTime.h
 *
 *  Created on: Aug 31, 2019
 *      Author: bcthund
 */

/*
* We need to track seasons somehow
*
* We can add subsystems into the Timer class
*   to track days, months, years, etc. We can
*   then use that data to determine the season.
*
* Once we know the season we need to change
*   the textures and atmosphere data that
*   goes with it. We can do this as an instant
*   update which would be easiest. Or we can
*   use multiple 3D textures or texture arrays
*   to load two overlapping seasons at the same
*   time and fade between the two according to
*   some algorithm. This would look better but
*   will also have a performance cost.
*/

#ifndef HEADERS_GAMESYS_GAMETIME_H_
#define HEADERS_GAMESYS_GAMETIME_H_

#include <iostream>
#include <math.h>
#include "../core/timer.h"

namespace Core {
	class _TimeSys : public Timer {
		public:
			_TimeSys();
			virtual ~_TimeSys();

			enum _SEASONS { SPRING, SUMMER, FALL, WINTER, SEASON_LAST };
			float	fFactor;		// Day speed factor
			int		iDay;
			int 	iYear;
			int 	iSeason;
			int 	iHour;
			int 	iMinute;
			int 	iSecond;
			float	fSWinter,
					fSSpring,
					fSSummer,
					fSFall;
			float	fTimeRaw,
					fDay,
					fHour;

			float Update();
			void SetSeasonFactors();
			std::string GetSeasonStr();
			void UpdateDay();
			void UpdateTime();
			void UpdateTime(float fTime);
			void UpdateSeason();
			int GetHour();
			int GetMinute();
			int GetSecond();
			int GetHour(float fTime);
			int GetMinute(float fTime);
			int GetSecond(float fTime);
			int GetMinutes();
			int GetSeconds();
	};
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GAMETIME_H_ */
