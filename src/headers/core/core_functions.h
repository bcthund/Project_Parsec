/*
 * core_functions.h
 *
 *  Created on: Dec 15, 2018
 *      Author: bcthund
 */

#ifndef HEADERS_CORE_CORE_FUNCTIONS_H_
#define HEADERS_CORE_CORE_FUNCTIONS_H_ 1

#include "extern.h"
//#include <variant>	// Doesn't work
#include <any>
#include <iostream>
#include <fstream>
#include <cstring>
#include <assert.h>
#include <random>
#include <memory>
#include "types.h"
#include "state.h"
#include "SimplexNoise.h"

namespace Core {
//	class _CoreFunctions {
//		public:
		//static float M_DegToRad(float x) { return x*RADIAN; }
		//static float M_RadToDeg(float x) { return x*DEGREE; }

		/*
		 * Common Aliases
		 */
		#define cout(x) std::cout << "(x) "
		//#define pError std::cout << "(E) "
		//#define pWarn std::cout << "(W) "
		//#define pInfo std::cout << "(I) "

		/*
		 * Subtract a number of chracters from end of string
		 */
		static void PopStr(std::string &string, const int length){
			string.erase(string.length()-length, length);
		}

		/*
		 * Return the distnace between two vectors
		 * on the XZ-plane only knowing that the
		 * second vector is negative
		 */
		static float distanceXZpn(Vector3f a, Vector3f b) {
			Vector3f c = {	(a[0]+b[0]),
							0.0f,
							(a[2]+b[2])	};
			return sqrt((c[0]*c[0])+(c[1]*c[1])+(c[2]*c[2]));
		}

		static std::default_random_engine generator(1);		// Seed is 1

		static int roll(int min, int max) {

			std::uniform_int_distribution<int> distribution(min, max);
			return distribution(generator);
		}

		static float roll(float min, float max)
		{
			std::uniform_real_distribution<float> distribution(min, max);
			return distribution(generator);
		}

		static float roll(Vector2f v)
		{
			std::uniform_real_distribution<float> distribution(v.x, v.y);
			return distribution(generator);
		}

		static bool readFile(std::string someFile, MemBlock &memBlock) {
			std::ifstream myFile(someFile.c_str(), std::ifstream::in | std::ifstream::binary);
			if (myFile.is_open()) {
				myFile.seekg(0, std::ifstream::end);
				memBlock.size = myFile.tellg();
				//if( memBlock.buffer ) {                // this makes it safe, if you were already using a buffer
				//	delete[] memBlock.buffer;
				//}
				memBlock.buffer = new char[memBlock.size];
				myFile.seekg(0, std::ifstream::beg);
				myFile.read(memBlock.buffer, memBlock.size);
				myFile.close();
				return true;
			}
			else {
				return false;
				printf("Failed to open file.\n");
			}
			return false;
		}

		static std::string itoa(int value, unsigned int base) {
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

		static std::string * split(const char * src, char delim) {
			std::string * sWord = new std::string[24];
			char * cArray = new char[128];
			*cArray = 0;

			uint wordNum=0;
			for (uint i = 0; i < std::strlen(src); i++) {
				if (src[i]!=delim) {
					char temp[1] = { src[i] };
					std::strncat(cArray, temp, 1);
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

		static void toggle(bool &b) {
			if (b) b = false;
			else b = true;
		}
//	};
}

#endif /* HEADERS_CORE_CORE_FUNCTIONS_H_ */
