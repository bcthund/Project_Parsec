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
#include "./core/types.h"

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

//std::variant<int, float> MinIF(std::variant<int, float> a, std::variant<int, float> b) {
//	if(a<b) return a;
//	else return b;
//}

//std::variant<int, float> MinIF(std::variant<int, float> a, int b) {
//	if(a<b) return a;
//	else return std::variant<int, float>(b);
//}
//
//std::variant<int, float> MinIF(std::variant<int, float> a, float b) {
//	if(a<b) return a;
//	else return std::variant<int, float>(b);
//}

//std::variant<int, float> MaxIF(std::variant<int, float> a, std::variant<int, float> b) {
//	if(a>b) return a;
//	else return b;
//}

//std::variant<int, float> MaxIF(std::variant<int, float> a, int b) {
//	if(a>b) return a;
//	else return std::variant<int, float>(b);
//}
//
//std::variant<int, float> MaxIF(std::variant<int, float> a, float b) {
//	if(a>b) return a;
//	else return std::variant<int, float>(b);
//}

//std::string from_variant(Core::t_BIFS v) {
//	switch (v.index()) {
//		case 0:
//			return std::to_string(std::get<bool>(v));
//			break;
//		case 1:
//			return std::to_string(std::get<int>(v));
//			break;
//		case 2:
//			return std::to_string(std::get<float>(v));
//			break;
//		case 3:
//			return std::get<std::string>(v);
//			break;
//	}
//	return "[Undefined Type]";
//}

#endif /* HEADERS_GLOBAL_H_ */
