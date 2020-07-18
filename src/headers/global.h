/*
 * global.h
 *
 *  Created on: Aug 24, 2019
 *      Author: bcthund
 */

#ifndef HEADERS_GLOBAL_H_
#define HEADERS_GLOBAL_H_

#include <iostream>
#include <iomanip>
#include <algorithm>

// A generic smart pointer class
template <class T>
class Ptr
{
   T *ptr;  // Actual pointer
public:
   // Constructor
   explicit Ptr(T *p = nullptr) { ptr = p; }

   // Destructor
   ~Ptr() { delete(ptr); }

   // Overloading dereferncing operator
   T & operator * () {  return *ptr; }

   // Overloding arrow operator so that members of T can be accessed
   // like a pointer (useful if T represents a class or struct or
   // union type)
   T * operator -> () { return ptr; }
};

//struct _Global {
//	std::string sOffset;
//	_Global() {
//		sOffset = "";
//	}
//} Global;

std::string str_rand( size_t length )
{
	auto randchar = []() -> char
	{
		const char charset[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[ rand() % max_index ];
	};
	std::string str(length,0);
	std::generate_n( str.begin(), length, randchar );
	return str;
}

std::string sOffset = "";

template <typename T> std::string to_string(T tValue, int precision=3) {
	std::string buffer;
	std::stringstream stream;
	stream << std::fixed << std::setprecision(precision) << tValue;
	buffer = stream.str();
	return buffer;
}

#endif /* HEADERS_GLOBAL_H_ */
