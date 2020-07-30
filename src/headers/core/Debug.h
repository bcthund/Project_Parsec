/*
 * Debug.h
 *
 *  Created on: Jul 21, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_CORE_DEBUG_H_
#define HEADERS_CORE_DEBUG_H_

#include <iostream>
#include "timer.h"
#include <sys/ioctl.h> //ioctl() and TIOCGWINSZ
#include <unistd.h> // for STDOUT_FILENO
//#include "core_functions.h"

namespace Core {
	class _Debug {
		private:
			typedef struct {
				std::string colors[32] = {
					"\033[0m",
					"\033[0;30m",
					"\033[1;30m",
					"\033[0;31m",
					"\033[1;31m",
					"\033[0;32m",
					"\033[1;32m",
					"\033[0;33m",
					"\033[1;33m",
					"\033[0;35m",
					"\033[1;35m",
					"\033[0;37m",
					"\033[1;37m",
					"\033[0;34m",
					"\033[1;34m",
					"\033[0;36m",
					"\033[1;36m"
				};

				enum eCOLOR {
					NC = 0,
					grey,
					GREY,
					red,
					RED,
					green,
					GREEN,
					yellow,
					YELLOW,
					purple,
					PURPLE,
					white,
					WHITE,
					blue,
					BLUE,
					cyan,
					CYAN
				};
			} ConsoleColors;

		public:
			_Debug();
			static ConsoleColors consoleColors;

			Timer timerPrint,
				  timerLog;
			int maxRate;
			bool bDrawLog, bDrawPrint;
			struct winsize size;

			void update(int rate=500, bool bClear=true);
			void log(std::string buffer, ConsoleColors::eCOLOR color=ConsoleColors::eCOLOR(consoleColors.GREEN));
			void print(std::string buffer, ConsoleColors::eCOLOR color=ConsoleColors::eCOLOR(consoleColors.NC));
			virtual ~_Debug();
	};
	//_Debug::consoleColors = 0;

} /* namespace Core */

#endif /* HEADERS_CORE_DEBUG_H_ */
