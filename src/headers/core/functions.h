/*
 * functions.hpp
 *
 *  Created on: May 23, 2010
 *      Author: bcthund
 */

#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_

//#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>
#include "types.h"

namespace Core {

	std::string from_variant(Core::t_BIFS v) {
		switch (v.index()) {
			case 0:
				return std::to_string(std::get<bool>(v));
				break;
			case 1:
				return std::to_string(std::get<int>(v));
				break;
			case 2:
				return std::to_string(std::get<float>(v));
				break;
			case 3:
				return std::get<std::string>(v);
				break;
		}
		return "[Undefined Type]";
	}

	template <typename T>
	inline bool inRange(T value, T a, T b, bool aExclusive=false, bool bExclusive=false) {
		bool aResult;
		if(aExclusive) aResult = (value>a);
		else aResult = (value>=a);

		bool bResult;
		if(bExclusive) bResult = (value<b);
		else bResult = (value<=b);

		return (aResult && bResult);
	}


	// ===========================================================================================================
	//			OLD UNUSED FUNCTIONS
	// ===========================================================================================================

	/*
	 * Toggle a simple boolean value
	 */
//	inline void toggle(bool &b) {
//		if(b) b = false;
//		else b = true;
//	}

//	inline void swap(float &a, float &b) {
//		float c = a;
//		a = b;
//		b = c;
//	}

//	inline float max(float &a, float &b) {
//		if(a>b) return a;
//		else return b;
//	}

//	inline float min(float &a, float &b) {
//		if(a<b) return a;
//		else return b;
//	}

//	/*
//	 * Return the distance between two vectors
//	 * on the XZ-plane only, knowing that both
//	 * vectors are positive
//	 */
//	inline float distanceXZpp(Vector3f a, Vector3f b) {
//		Vector3f c = {	(a[0]-b[0]),
//						0.0f,
//						(a[2]-b[2])	};
//		return sqrt((c[0]*c[0])+(c[1]*c[1])+(c[2]*c[2]));
//	}

	/*
	inline float distanceXZpn(float * a, Vector3f b) {
		Vector3f c = {	(a[0]+b[0]),
						0.0f,
						(a[2]+b[2])	};
		return sqrt((c[0]*c[0])+(c[1]*c[1])+(c[2]*c[2]));
	}
	*/

//	/*
//	 * Return the distnace between two vectors
//	 * on the XZ-plane only knowing that both
//	 * vectors are negative
//	 */
//	inline float distanceXZnn(Vector3f a, Vector3f b) {
//		Vector3f c = {	(a[0]+b[0]),
//						0.0f,
//						(a[2]+b[2])	};
//		return sqrt((c[0]*c[0])+(c[1]*c[1])+(c[2]*c[2]));
//	}

//	/*
//	 * Return the distnace between two vectors
//	 * on the XZ-plane only knowing that the
//	 * first vector is negative
//	 */
//	inline float distanceXZnp(Vector3f a, Vector3f b) {
//		Vector3f c = {	(-a[0]+b[0]),
//						0.0f,
//						(-a[2]+b[2])	};
//		return sqrt((c[0]*c[0])+(c[1]*c[1])+(c[2]*c[2]));
//	}

//	inline bool Cmpff(float a, float b, float e=0.0001f)	{	return (fabs(a - b) < e);	}
//	inline bool Cmpfi(float a, int b, float e=0.01f)		{	return (fabs(a - b) < e);	}
//	inline bool Cmpii(int a, int b, int e=0)				{	return (abs(a - b) < e);	}


	//	// TODO: Should be in matrix class
	//	inline void Inverse(Matrix33f i, Matrix33f &o) {
	//
	//		float	A=i[0],
	//				B=i[1],
	//				C=i[2],
	//				D=i[3],
	//				E=i[4],
	//				F=i[5],
	//				G=i[6],
	//				H=i[7],
	//				I=i[8];
	//
	//		//Determinant
	//		float	dA = (A*E*I) + (D*H*C) + (G*B*F) - (A*H*F) - (G*E*C) - (D*B*I);
	//
	//		//Minors
	//		float	M11 = (E*I)-(F*H),
	//				M12 = (D*I)-(F*G),
	//				M13 = (D*H)-(E*G),
	//				M21 = (B*I)-(C*H),
	//				M22 = (A*I)-(C*G),
	//				M23 = (A*H)-(B*G),
	//				M31 = (B*F)-(C*E),
	//				M32 = (A*F)-(C*D),
	//				M33 = (A*E)-(B*D);
	//
	//		//Output Results
	//		o[0] = dA*M11;
	//		o[1] = dA*M12;
	//		o[2] = dA*M13;
	//		o[3] = dA*M21;
	//		o[4] = dA*M22;
	//		o[5] = dA*M23;
	//		o[6] = dA*M31;
	//		o[7] = dA*M32;
	//		o[8] = dA*M33;
	//	}
	//
	//	inline void Transpose(Matrix33f &i) {
	//		float	A=i[0],
	//				B=i[1],
	//				C=i[2],
	//				D=i[3],
	//				E=i[4],
	//				F=i[5],
	//				G=i[6],
	//				H=i[7],
	//				I=i[8];
	//
	//		i[0] = A;
	//		i[1] = D;
	//		i[2] = G;
	//		i[3] = B;
	//		i[4] = E;
	//		i[5] = H;
	//		i[6] = C;
	//		i[7] = F;
	//		i[8] = I;
	//	}

//	inline void BubbleSort(float *array,int length)//Bubble sort function
//	{
//		int i,j;
//		for(i=0;i<length;i++)
//		{
//			for(j=0;j<i;j++)
//			{
//				if(array[i]>array[j])
//				{
//					float temp=array[i]; //swap
//					array[i]=array[j];
//					array[j]=temp;
//				}
//
//			}
//
//		}
//
//	}

//	inline void BubbleSortTrack(float *array, unsigned int *track, int length)//Bubble sort function
//	{
//		int i,j;
//		for(i=0;i<length;i++)
//		{
//			for(j=0;j<i;j++)
//			{
//				if(array[i]>array[j])
//				{
//					float temp=array[i]; //swap
//					array[i]=array[j];
//					array[j]=temp;
//
//					float temp2=track[i]; //swap
//					track[i]=track[j];
//					track[j]=temp2;
//				}
//
//			}
//
//		}
//
//	}

	//	float Abs(float f) {
	//		if (f<0) return f*-1;
	//		else return f;
	//	}

//	std::string itoa(int value, unsigned int base) {
//		const char * digitMap = "0123456789abcdef";
//		std::string buf;
//
//		// Guard:
//		if (base == 0 || base > 16) {
//			// Error: may add more trace/log output here
//			return buf;
//		}
//
//		// Take care of negative int:
//		std::string sign;
//		int _value = value;
//
//		// Check for case when input is zero:
//		if (_value == 0) return "0";
//
//		//cout << value << endl;
//
//		if (value < 0) {
//			_value = -value;
//			sign = "-";
//		}
//
//		// Translating number to string with base:
//		for (int i = 30; _value && i ; --i) {
//			buf = digitMap[ _value % base ] + buf;
//			_value /= base;
//		}
//
//		//delete digitMap;
//
//		return sign.append(buf);
//	}
	//
	//	std::string ftoa(float value, unsigned int base) {
	//		const char * digitMap = "0123456789abcdef";
	//		std::string buf;
	//
	//		// Guard:
	//		if (base == 0 || base > 16) {
	//			// Error: may add more trace/log output here
	//			return buf;
	//		}
	//
	//		// Take care of negative int:
	//		std::string sign;
	//		float _value = value;
	//
	//		// Check for case when input is zero:
	//		if (_value == 0.0f) return "0";
	//
	//		//cout << value << endl;
	//
	//		if (value < 0.0f) {
	//			_value = -value;
	//			sign = "-";
	//		}
	//
	//		uint uiPart1 = (uint)_value;
	//		uint uiPart2 = (uint)(_value*10000);
	//
	//		//Add decimal values
	//		if (uiPart2 > 0) {
	//
	//			for (int i = 30; uiPart2 && i ; --i) {
	//				buf = digitMap[ uiPart2 % base ] + buf;
	//				uiPart2 /= base;
	//			}
	//
	//			//Precision up to 4 zeros
	//			if (_value-uiPart1 < 0.1 && _value-uiPart1!=0.0f) {
	//				buf = "0" + buf;
	//				if (_value-uiPart1 < 0.01) {
	//					buf = "0" + buf;
	//					if (_value-uiPart1 < 0.001) {
	//						buf = "0" + buf;
	//						if (_value-uiPart1 < 0.0001) {
	//							buf = "0" + buf;
	//						}
	//					}
	//				}
	//			}
	//
	//			buf = "." + buf;
	//		}
	//
	//
	//		// Translating number to string with base:
	//		if (uiPart1==0.0f) {
	//			buf = "0" + buf;
	//		} else {
	//			for (int i = 30; uiPart1 && i ; --i) {
	//				buf = digitMap[ uiPart1 % base ] + buf;
	//				uiPart1 /= base;
	//			}
	//		}
	//
	//		return sign.append(buf);
	//	}

//	std::string * split(const char * src, char delim) {
//	   std::string * sWord = new std::string[24];
//	   char * cArray = new char[128];
//	   *cArray = 0;
//
//	   uint wordNum=0;
//	   for (uint i = 0; i < strlen(src); i++) {
//		  if (src[i]!=delim) {
//			 char temp[1] = { src[i] };
//			 strncat(cArray, temp, 1);
//		  }
//		  else {
//			 sWord[wordNum] = cArray;
//			 *cArray = 0;
//			 wordNum++;
//		  }
//	   }
//	   sWord[wordNum] = cArray;
//	   sWord[wordNum+1] = "LAST";
//
//	   delete[] cArray;
//	   return sWord;
//	}
//
//	inline void Toggle(bool &b) {
//		if (b==true) b=false;
//		else b=true;
//	}
//
//	inline void deepCopy(float from, float &to) {
//		to = *new float(from);
//	}

//		std::string str_rand( size_t length )
//		{
//			auto randchar = []() -> char
//			{
//				const char charset[] =
//				"0123456789"
//				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//				"abcdefghijklmnopqrstuvwxyz";
//				const size_t max_index = (sizeof(charset) - 1);
//				return charset[ rand() % max_index ];
//			};
//			std::string str(length,0);
//			std::generate_n( str.begin(), length, randchar );
//			return str;
//		}

		//inline void CopyMatrix33f(Matrix33f src, Matrix33f dest) {
		//	dest[0] = *new float(src[0]);
		//	dest[1] = *new float(src[1]);
		//	dest[2] = *new float(src[2]);
		//	dest[3] = *new float(src[3]);
		//	dest[4] = *new float(src[4]);
		//	dest[5] = *new float(src[5]);
		//	dest[6] = *new float(src[6]);
		//	dest[7] = *new float(src[7]);
		//	dest[8] = *new float(src[8]);
		//}
		//
		//inline void CopyMatrix44f(Matrix44f src, Matrix44f dest) {
		//	dest[0] = *new float(src[0]);
		//	dest[1] = *new float(src[1]);
		//	dest[2] = *new float(src[2]);
		//	dest[3] = *new float(src[3]);
		//	dest[4] = *new float(src[4]);
		//	dest[5] = *new float(src[5]);
		//	dest[6] = *new float(src[6]);
		//	dest[7] = *new float(src[7]);
		//	dest[8] = *new float(src[8]);
		//	dest[9] = *new float(src[9]);
		//	dest[10] = *new float(src[10]);
		//	dest[11] = *new float(src[11]);
		//	dest[12] = *new float(src[12]);
		//	dest[13] = *new float(src[13]);
		//	dest[14] = *new float(src[14]);
		//	dest[15] = *new float(src[15]);
		//}

//		inline bool readFile(std::string someFile, MemBlock &memBlock) {
//		 std::ifstream myFile(someFile.c_str(), std::ifstream::in | std::ifstream::binary);
//		 if (myFile.is_open()) {
//		  myFile.seekg(0, std::ifstream::end);
//		  memBlock.size = myFile.tellg();
//		  //if( memBlock.buffer ) {                // this makes it safe, if you were already using a buffer
//		  //	delete[] memBlock.buffer;
//		  //}
//		  memBlock.buffer = new char[memBlock.size];
//		  myFile.seekg(0, std::ifstream::beg);
//		  myFile.read(memBlock.buffer, memBlock.size);
//		  myFile.close();
//		  return true;
//		 }
//		 else {
//		  return false;
//		  printf("Failed to open file.\n");
//		 }
//		 return false;
//		}
//
//		inline bool readFile(std::string someFile) {
//		 std::ifstream myFile(someFile.c_str(), std::ifstream::in | std::ifstream::binary);
//		 if (myFile.is_open()) {
//			/*
//		  myFile.seekg(0, std::ifstream::end);
//		  memBlock.size = myFile.tellg();
//		  if( memBlock.buffer ) {                // this makes it safe, if you were already using a buffer
//			delete[] memBlock.buffer;
//		  }
//		  memBlock.buffer = new char[memBlock.size];
//		  myFile.seekg(0, std::ifstream::beg);
//		  myFile.read(memBlock.buffer, memBlock.size);
//		  myFile.close();
//		  //delete[] memBlock.buffer;
//		   */
//		  return true;
//		 }
//		 else {
//		  return false;
//		  printf("Failed to open file.\n");
//		 }
//		 return false;
//		}
}
#endif /* FUNCTIONS_HPP_ */
