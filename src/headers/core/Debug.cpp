/*
 * Debug.cpp
 *
 *  Created on: Jul 21, 2020
 *      Author: bcthund
 */

#include <core/Debug.h>

namespace Core {

	_Debug::ConsoleColors _Debug::consoleColors;

	_Debug::_Debug() {
		// TODO Auto-generated constructor stub
		maxRate = 500;
		timerPrint.start();
		timerLog.start();
		bDrawLog = true;
		bDrawPrint = true;

		//ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		//auto const w(WEXITSTATUS(std::system("exit `tput cols`")));
		//auto const h(WEXITSTATUS(std::system("exit `tput lines`")));
	}

	_Debug::~_Debug() {
		// TODO Auto-generated destructor stub
	}

	void _Debug::logIncreaseIndent()   { sLogIndent.append(" "); }
	void _Debug::logDecreaseIndent()   { if(sLogIndent.length()>0) sLogIndent.pop_back(); }
	void _Debug::printIncreaseIndent() { sPrintIndent.append(" "); }
	void _Debug::printDecreaseIndent() { if(sPrintIndent.length()>0) sPrintIndent.pop_back(); }

	/**
	 * \brief Check and reset timers per cycle, to be called at beginning of program loop
	 */
	void _Debug::update(int rate, bool bClear) {
		maxRate = rate;
		if(timerLog.get_splitdiff() > maxRate) {
			bDrawLog = true;
			bDrawPrint = true;
			if(bClear) std::cout << "\033[2J\033[1;1H";	// 2J=clear from top(J) to bottom(2); Position cursor at row 1, column 1
			timerLog.split();
		}
		else {
			bDrawLog = false;
			bDrawPrint = false;
		}

		//if(timerPrint.get_splitdiff() > maxRate) {
		//	bDrawPrint = true;
		//	timerPrint.split();
		//}
		//else bDrawPrint = false;
	}

	/**
	 * \brief Print a message to console with a timestamp in ticks and an automatic newline
	 * @param buffer Text to be printed to console
	 * @param color Color from \p ConsoleColors to apply to text
	 */
	void _Debug::log(std::string buffer, ConsoleColors::eCOLOR color) {
		if (bDrawLog) {
			std::string timeStamp = "["+std::to_string(timerLog.get_ticks())+"]: ";
			while(timeStamp.length() < 16) {
				timeStamp.append(" ");
			}

			std::cout << consoleColors.colors[color] << timeStamp << sLogIndent << buffer << consoleColors.colors[consoleColors.NC] << std::endl;
		}
	}

	/**
	 * \brief Print a simple message to the console, no newlines added
	 * @param buffer Text to be printed to console
	 * @param color Color from \p ConsoleColors to apply to text
	 */
	void _Debug::print(std::string buffer, ConsoleColors::eCOLOR color) {
		if (bDrawPrint) {
			std::cout << consoleColors.colors[color] << sPrintIndent << buffer << consoleColors.colors[consoleColors.NC];
		}
	}

} /* namespace Core */
