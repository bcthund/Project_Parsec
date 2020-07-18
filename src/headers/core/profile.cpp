/*
 * profile.cpp
 *
 *  Created on: Jun 17, 2019
 *      Author: bcthund
 *
 */

#include "profile.h"

namespace Core {

	_Profile::_Profile() {

		// Default Profiles
		for (int n=0; n<builtIn.Last; n++) {
			addProfile(n);
		}
		bEnable = true;
	}

	_Profile::~_Profile() {
	}

	void _Profile::addProfile(std::string s) {
		int iResult = timer.addTimer(s);
	}

	void _Profile::startProfile(std::string s) {
		if (bEnable) timer.start(s);
	}

	void _Profile::stopProfile(std::string s) {
		if (bEnable) timer.stop(s);
	}

	uint _Profile::getTime(std::string s) {
		if (bEnable) return timer.getSplitTicks(s);
		else return 0;
	}

	float _Profile::getAverage(std::string s, int n) {
		if (bEnable) return timer.GetAverage(s, n);
		else return 0;
	}

	float _Profile::getStdDev(std::string s) {
		if (bEnable) return timer.GetStdDev(s);
		else return 0;
	}

	uint _Profile::getSamples(std::string s) {
		if (bEnable) return timer.GetSamples(s);
		else return 0;
	}

	uint _Profile::getMin(std::string s) {
		if (bEnable) return timer.GetMin(s);
		else return 0;
	}

	uint _Profile::getMax(std::string s) {
		if (bEnable) return timer.GetMax(s);
		else return 0;
	}











	void _Profile::addProfile(int p) {
		int iResult = timer.addTimer(builtIn.sNames[p]);
	}

	void _Profile::startProfile(int p) {
		if (bEnable) timer.start(builtIn.sNames[p]);
	}

	void _Profile::stopProfile(int p) {
		if (bEnable) timer.stop(builtIn.sNames[p]);
	}

	void _Profile::runProfile(int p, bool b) {
		if(b) timer.start(builtIn.sNames[p]);
		else timer.stop(builtIn.sNames[p]);
	}

	uint _Profile::getTime(int p) {
		if (bEnable) return timer.getSplitTicks(builtIn.sNames[p]);
		else return 0;
	}

	float _Profile::getAverage(int p, int n) {
		if (bEnable) return timer.GetAverage(builtIn.sNames[p], n);
		else return 0;
	}

	float _Profile::getStdDev(int p) {
		if (bEnable) return timer.GetStdDev(builtIn.sNames[p]);
		else return 0;
	}

	uint _Profile::getSamples(int p) {
		if (bEnable) return timer.GetSamples(builtIn.sNames[p]);
		else return 0;
	}

	uint _Profile::getMin(int p) {
		if (bEnable) return timer.GetMin(builtIn.sNames[p]);
		else return 0;
	}

	uint _Profile::getMax(int p) {
		if (bEnable) return timer.GetMax(builtIn.sNames[p]);
		else return 0;
	}






	void _Profile::reset() {
		timer.ResetAverage();
		timer.ResetMax();
		timer.ResetMin();
		timer.ResetStdDev();
		timer.ResetSamples();
	}

} /* namespace Core */
