/*
 * functions.hpp
 *
 *  Created on: May 23, 2010
 *      Author: bcthund
 */

#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_

#include <cstring>
#include <fstream>
#include <algorithm>
#include "types.h"

namespace Core {
	std::string itoa(int value, unsigned int base) {
		const char * digitMap = "0123456789abcdef";
		std::string buf;

		// Guard:
		if (base == 0 || base > 16) {
			// Error: may add more trace/log output here
			return buf;
		}

		// Take care of negative int:
		std::string sign;
		int _value = value;

		// Check for case when input is zero:
		if (_value == 0) return "0";

		//cout << value << endl;

		if (value < 0) {
			_value = -value;
			sign = "-";
		}

		// Translating number to string with base:
		for (int i = 30; _value && i ; --i) {
			buf = digitMap[ _value % base ] + buf;
			_value /= base;
		}

		//delete digitMap;

		return sign.append(buf);
	}

	std::string ftoa(float value, unsigned int base) {
		const char * digitMap = "0123456789abcdef";
		std::string buf;

		// Guard:
		if (base == 0 || base > 16) {
			// Error: may add more trace/log output here
			return buf;
		}

		// Take care of negative int:
		std::string sign;
		float _value = value;

		// Check for case when input is zero:
		if (_value == 0.0f) return "0";

		//cout << value << endl;

		if (value < 0.0f) {
			_value = -value;
			sign = "-";
		}

		uint uiPart1 = (uint)_value;
		uint uiPart2 = (uint)(_value*10000);

		//Add decimal values
		if (uiPart2 > 0) {

			for (int i = 30; uiPart2 && i ; --i) {
				buf = digitMap[ uiPart2 % base ] + buf;
				uiPart2 /= base;
			}

			//Precision up to 4 zeros
			if (_value-uiPart1 < 0.1 && _value-uiPart1!=0.0f) {
				buf = "0" + buf;
				if (_value-uiPart1 < 0.01) {
					buf = "0" + buf;
					if (_value-uiPart1 < 0.001) {
						buf = "0" + buf;
						if (_value-uiPart1 < 0.0001) {
							buf = "0" + buf;
						}
					}
				}
			}

			buf = "." + buf;
		}


		// Translating number to string with base:
		if (uiPart1==0.0f) {
			buf = "0" + buf;
		} else {
			for (int i = 30; uiPart1 && i ; --i) {
				buf = digitMap[ uiPart1 % base ] + buf;
				uiPart1 /= base;
			}
		}

		return sign.append(buf);
	}

	std::string * split(const char * src, char delim) {
	   std::string * sWord = new std::string[24];
	   char * cArray = new char[128];
	   *cArray = 0;

	   uint wordNum=0;
	   for (uint i = 0; i < strlen(src); i++) {
		  if (src[i]!=delim) {
			 char temp[1] = { src[i] };
			 strncat(cArray, temp, 1);
		  }
		  else {
			 sWord[wordNum] = cArray;
			 *cArray = 0;
			 wordNum++;
		  }
	   }
	   sWord[wordNum] = cArray;
	   sWord[wordNum+1] = "LAST";

	   delete[] cArray;
	   return sWord;
	}

//	std::string str_rand( size_t length )
//	{
//		auto randchar = []() -> char
//		{
//			const char charset[] =
//			"0123456789"
//			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//			"abcdefghijklmnopqrstuvwxyz";
//			const size_t max_index = (sizeof(charset) - 1);
//			return charset[ rand() % max_index ];
//		};
//		std::string str(length,0);
//		std::generate_n( str.begin(), length, randchar );
//		return str;
//	}
}
#endif /* FUNCTIONS_HPP_ */
