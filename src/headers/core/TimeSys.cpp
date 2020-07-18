/*
 * GameTime.cpp
 *
 *  Created on: Aug 31, 2019
 *      Author: bcthund
 */

#include "TimeSys.h"

namespace Core {
	_TimeSys::_TimeSys():	iDay(355),
							iYear(5621),
							iHour(0),
							iMinute(0),
							iSecond(0),
							fFactor(0.001),
							//fFactor(0.1),
							fTimeRaw(0),
							fSSummer(0.0f),
							fSSpring(0.0f),
							fSFall(0.0f),
							fSWinter(0.0f),
							iSeason(SUMMER),
							fDay(0.0f),
							fHour(0.0f) {}

	_TimeSys::~_TimeSys() {
	}

	/*
	 * SEASONS
	 *
	 * The iSeason variable holds the current season numbered 0-4
	 *   using the enum list to identify the season. These seasons
	 *   can then be used to select the atmosphere data that is
	 *   used, and the world textures used.
	 *
	 * To do texture fading (if used) the GetSeasonFactors() function
	 *   will calculate the fade factors between the two seasons.
	 *   Because we have a leading and trailing season to deal
	 *   with we may have to choose a side and start a fade at
	 *   the beginning or end of a season instead of split
	 *   between the two.
	 *
	 * The UpdateDay() function will set the iSeason and be turned
	 *   into a general update function and the angle will be
	 *   returned in a separate function.
	 */
	void _TimeSys::SetSeasonFactors() {
		//float fReturn = 0.0f;

//					float fSeasonDays = 368/4;
//					float fCurrentDays = 368 - (fSeasonDays * iSeason);

		/*
		 * (iDay-(fSeasonDays*iSeason))/fSeasonDays
		 *
		 * This gives us a normalized value that is stretched
		 *   across the entire season. We now need to adjust
		 *   the value to get a factor that only applies to
		 *   a final range of values for fSeasonDays
		 *
		 * If we use the final 10 days for fading:
		 *   Range = (fSeasonDays-10) to (fSeasonDays)
		 *   If ( ( iDay - (fSeasonDays * iSeason) ) >= (fSeasonDays-10) ) then calculate factor, else return 1.0f;
		 *
		 */

		float fDay = (float)iDay,
					first = 0.0f,
					x_1 = -15,
					y_1 =  0,
					y_2 =  1,
					x_2 = -5,
					m   = (y_2-y_1) / (x_2-x_1);

		// Fall
		fSFall = fmax(0.0f, fmin(1.0f, m*(fDay-x_1-270)+y_1));
		if (fSFall >= 1.0f) fSFall = fmax(0.0f, fmin(1.0f, -m*(fDay-x_1-370)+y_1));

		// Summer
		fSSummer = fmax(0.0f, fmin(1.0f, m*(fDay-x_1-180)+y_1));
		if (fSSummer >= 1.0f) fSSummer = fmax(0.0f, fmin(1.0f, -m*(fDay-x_1-280)+y_1));

		// Spring
		fSSpring =  fmax(0.0f, fmin(1.0f, m*(fDay-x_1-90)+y_1));
		if (fSSpring >= 1.0f) fSSpring = fmax(0.0f, fmin(1.0f, -m*(fDay-x_1-190)+y_1));

		// Winter
		fSWinter = fmax(0.0f, fmin(1.0f, -m*(fDay-x_1-100)+y_1));
		if (fSWinter <= 0.0f) fSWinter = fmax(0.0f, fmin(1.0f, m*(fDay-x_1-360)+y_1));

//					float fDay = (float)iDay;
//					fSSpring 							= fmax(0.0f, fmin(1.0f, (-0.00075)*(pow(fDay-125, 2))+2));
//					fSSummer 							= fmax(0.0f, fmin(1.0f, (-0.00075)*(pow(fDay-215, 2))+2));
//					fSFall 	 							= fmax(0.0f, fmin(1.0f, (-0.00075)*(pow(fDay-305, 2))+2));
//					if(iDay<=80) fSWinter = fmax(0.0f, fmin(1.0f, (-0.00075)*(pow(fDay-35, 2))+2));
//					else fSWinter					= fmax(0.0f, fmin(1.0f, (-0.00075)*(pow(fDay-395, 2))+2));

//					cout << "[" << iDay << "]" << fSSpring << " : " << fSSummer << " : " << fSFall << " : " << fSWinter << std::endl;

		//return fSFactor;
	}

	/*
	 * Gets the text for the current season
	 */
	std::string _TimeSys::GetSeasonStr() {
		switch(iSeason) {
			case SPRING:
				return "Spring";
				break;
			case SUMMER:
				return "Summer";
				break;
			case FALL:
				return "Fall";
				break;
			case WINTER:
				return "Winter";
				break;
		}
		return "Unknown!";
	}

	float _TimeSys::Update() {
		UpdateTime();
		UpdateDay();
		UpdateSeason();
		SetSeasonFactors();
		return fTimeRaw;
	}

	/*
	 * Check if the day has lapsed
	 * Return the sun angle
	 */
	void _TimeSys::UpdateDay() {
		if(fTimeRaw > 360) {
			reset();
			if(iDay<360) iDay++;
			else {
				iDay = 1;
				iYear++;
			}
		}
		fDay = (float)iDay + fTimeRaw/359.0f;	// Because we start at day 1, only use 359 degrees
		//fHour = (float)iHour + fTimeRaw/15.0f;
		fHour = fTimeRaw/15.0f;
		//std::cout << "fHour = " << fHour << std::endl;
		//std::cout << "fTimeRaw = " << fTimeRaw << std::endl << std::endl;
	}

	/*
	 * This simply updates the values so they can be read properly
	 */
	void _TimeSys::UpdateTime(){
		fTimeRaw = (get_ticks()*fFactor);
		iHour = (fTimeRaw)/15;
		iMinute = (fTimeRaw*4)-(iHour*60);
		iSecond = ((get_ticks()*fFactor)*240)-(iHour*60*60)-(iMinute*60);
	}

	void _TimeSys::UpdateTime(float fTime){
		iHour = (fTime)/15;
		iMinute = (fTime*4)-(iHour*60);
		iSecond = ((get_ticks()*fFactor)*240)-(iHour*60*60)-(iMinute*60);
	}

	void _TimeSys::UpdateSeason(){
		if( (iDay>=0)	&& (iDay<=80) )		iSeason = WINTER;
		if( (iDay>=81)	&& (iDay<=173) )	iSeason = SPRING;
		if( (iDay>=174)	&& (iDay<=267) )	iSeason = SUMMER;
		if( (iDay>=268)	&& (iDay<=358) )	iSeason = FALL;
		if( (iDay>=359)	&& (iDay<=368) )	iSeason = WINTER;
	}

	/*
	 * Get time values
	 */
	int _TimeSys::GetHour() {
		return iHour;
	}
	int _TimeSys::GetMinute() {
		return iMinute;
	}
	int _TimeSys::GetSecond() {
		return iSecond;
	}
	//float GetMillisecond() {
	//	return (get_ticks()*fFactor)-(GetSecond()*60);
	//}
	int _TimeSys::GetHour(float fTime) {
		iHour = fTime/15;
		return iHour;
	}
	int _TimeSys::GetMinute(float fTime) { //32
		iMinute = (fTime*4)-(GetHour(fTime)*60);
		return iMinute;
	}
	int _TimeSys::GetSecond(float fTime) { //
		iSecond = (fTime*240)-(GetHour(fTime)*60*60)-(GetMinute(fTime)*60);
		return iSecond;
	}
	int _TimeSys::GetMinutes() {
		return (get_ticks()*fFactor)*4;
	}
	int _TimeSys::GetSeconds() {
		return (get_ticks()*fFactor)*240;
	}
} /* namespace Core */
