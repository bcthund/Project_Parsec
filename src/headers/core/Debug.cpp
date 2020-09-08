/*
 * Debug.cpp
 *
 *  Created on: Jul 21, 2020
 *      Author: bcthund
 */

#include <core/Debug.h>
#include <iomanip>

namespace Core {

	_Debug::ConsoleColors _Debug::consoleColors;

	_Debug::_Debug() {
		// TODO Auto-generated constructor stub
		maxRate = 500;
		timerPrint.start();
		timerLog.start();
		bDrawLog = true;
		bDrawPrint = true;
		bLogEnable = true;
		bPrintEnable = true;

		//ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		//auto const w(WEXITSTATUS(std::system("exit `tput cols`")));
		//auto const h(WEXITSTATUS(std::system("exit `tput lines`")));
	}

	_Debug::~_Debug() {
		// TODO Auto-generated destructor stub
	}

	_Debug::ConsoleColors& _Debug::operator()() {
		return consoleColors;
	}

	void _Debug::logIncreaseIndent()   { sLogIndent.append("  "); }
	void _Debug::logDecreaseIndent()   { if(sLogIndent.length()>1) sLogIndent.pop_back(); sLogIndent.pop_back(); }
	void _Debug::printIncreaseIndent() { sPrintIndent.append("  "); }
	void _Debug::printDecreaseIndent() { if(sPrintIndent.length()>1) sPrintIndent.pop_back(); sPrintIndent.pop_back(); }

	/**
	 * \brief Check and reset timers per cycle, to be called at beginning of program loop
	 */
	void _Debug::update(int rate, bool bClear/*, bool bEnable*/) {
		//bLogEnable = bEnable;
		//bPrintEnable = bEnable;
		maxRate = rate;
		if(timerLog.get_splitdiff() > maxRate) {
			bDrawLog = true;
			bDrawPrint = true;
			if(bClear) std::cout << "\033[2J\033[1;1H";	// 2J=clear from top(J) to bottom(2); Position cursor at row 1, column 1
			if(!bLogEnable) exec(consoleColors.colors[consoleColors.RED]+"LOG SUPPRESSED\n"+consoleColors.colors[consoleColors.NC]);
			if(!bPrintEnable) exec(consoleColors.colors[consoleColors.RED]+"PRINT SUPPRESSED\n"+consoleColors.colors[consoleColors.NC]);
			timerLog.split();
		}
		else {
			bDrawLog = false;
			bDrawPrint = false;
		}
	}

	// TODO: Make into std::cout style
	//std::ostream & objOstream = std::cout;
	//objOstream << "Test sentence goes to console\n";

	/**
	 * \brief Print a message to console with a timestamp in ticks and an automatic newline
	 * @param buffer Text to be printed to console
	 * @param color Color from \p ConsoleColors to apply to text
	 */
	void _Debug::log(std::string buffer, ConsoleColors::eCOLOR color) {
//		if (bDrawLog && bLogEnable) {
		if (bLogEnable) {

			std::stringstream timeStamp;
			timeStamp << "[" << std::setw(6) << std::setfill(' ') << timerLog.get_ticks() << "]  ";
			//timeStamp << std::setw(10) << std::setfill(' ') << "";


//			while(timeStamp.str().length() < 16) {
//				timeStamp.append(" ");
//			}

			std::ostringstream out;
//			out << consoleColors.colors[color] << timeStamp << sLogIndent << buffer << consoleColors.colors[consoleColors.NC] << std::endl;
			out << consoleColors.colors[consoleColors.GREY] << timeStamp.str() << sLogIndent << consoleColors.colors[color] << buffer << consoleColors.colors[consoleColors.NC];
			//std::cout << consoleColors.colors[color] << timeStamp << sLogIndent << buffer << consoleColors.colors[consoleColors.NC] << std::endl;
			exec(out.str());
		}
	}

	/**
	 * \brief Print a simple message to the console, no newlines added
	 * @param buffer Text to be printed to console
	 * @param color Color from \p ConsoleColors to apply to text
	 */
	void _Debug::print(std::string buffer, ConsoleColors::eCOLOR color) {
		if (bDrawPrint && bPrintEnable) {
			std::ostringstream out;
			out << consoleColors.colors[color] << sPrintIndent << buffer << consoleColors.colors[consoleColors.NC];
			exec(out.str());
//			std::cout << consoleColors.colors[color] << sPrintIndent << buffer << consoleColors.colors[consoleColors.NC];
		}
	}

	void _Debug::exec(std::string buffer) {
		std::cout << buffer;
	}

} /* namespace Core */

































































