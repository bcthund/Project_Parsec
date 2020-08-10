/*
 * types.h
 *
 *  Created on: Feb 27, 2018
 *      Author: bcthund
 */

#ifndef SRC_HEADERS_CORE_TYPES_H_
#define SRC_HEADERS_CORE_TYPES_H_

#include <iostream>
#include <sstream>
#include <cstdio>
#include <map>
#include <cmath>
#include <vector>
#include <variant>

namespace Core {
	//#define RADIAN (0.017453292519943296)
	//#define DEGREE (57.2957795130823229)
	//inline float M_DegToRad(float x) { return x*RADIAN; }
	//inline float M_RadToDeg(float x) { return x*DEGREE; }
	//#define M_DegToRad(x) x*RADIAN
	//#define M_RadToDeg(x) x*DEGREE

	//Vector2i operator+=(const Vector2i& rhs)	{	x += rhs.x;		y += rhs.y;		return *this;	}

//	std::string operator-=(const int length) {
//		std::string temp = std::string(*this);
//		temp.erase(temp.length()-length, length);
//		return temp;
//	}

	// VAO drawing modes
	enum DRAWING_MODES { 	GLM_BASE=0,
							GLM_DRAW,
							GLM_DRAW_ARRAYS,
							GLM_DRAW_ELEMENTS,
							GLM_DRAW_RANGE,
							GLM_DRAW_RANGE_ELEMENTS,
							GLM_DRAW_ARRAYS_INSTANCED,
							GLM_LAST };

	//Shader binding attributes
	enum GLT_SHADER_ATTRIBUTE { GLA_VERTEX	= 0,	// Vertex Data
								GLA_COLOR,			// Colors
								GLA_NORMAL,			// Normals
								GLA_INDEX,			// Index positions
								GLA_TEXTURE,		//
								GLA_TEXTURE0,		//
								GLA_TEXTURE1,		//
								GLA_TEXTURE2,		//
								GLA_TEXTURE3,		//
								GLA_POSITION,		// Position data for instanced arrays
								GLA_EXTRA,			// Extra data for instaced arrays
								GLA_LAST};


//	template<typename K, typename V>
//    static std::map<V, K> reverse_map(const std::map<K, V>& m) {
//        std::map<V, K> r;
//        for (const auto& kv : m)
//            r[kv.second] = kv.first;
//        return r;
//    }

	typedef std::map< std::string, uint > Map_si;
	typedef std::map< uint, std::string > Map_is;
//	typedef std::pair<std::string, uint> mapPair;

	//#ifndef M_PI
	//#define M_PI (3.14159265358979323846)
	//#endif

	#define RADIAN (0.017453292519943296)
	#define DEGREE (57.2957795130823229)

	//inline float M_DegToRad(float x) { return x*RADIAN; }
	//inline float M_RadToDeg(float x) { return x*DEGREE; }

//	typedef struct _SI {
////			template<typename T>
////			T get() {
////				if(bString) return (T)name;
////				else return (T)id;
////			}
//
//			std::string name;
//			int id;
//			bool bString,
//				 bInt;
//
//			_SI() {
//				this->id = 0;
//				bString = false;
//				bInt = true;
//			}
//
//			_SI(std::string name) {
//				this->name = name;
//				id = 0;
//				bString = true;
//				bInt = false;
//			}
//
//			_SI(int id) {
//				this->name = "";
//				this->id = id;
//				bString = false;
//				bInt = true;
//			}
//			_SI& operator= (std::string rhs)	{	this->name = rhs; bString = true; bInt = false;		return *this;	}
//			_SI& operator= (int rhs)			{	this->name = rhs; bString = false; bInt = true;		return *this;	}
//
//	} _SI;

	typedef struct Degrees {
		float degrees;
		float toRadians() { return degrees*RADIAN; }
		Degrees() {
			degrees = 0.0f;
		}
		Degrees(float f) {
			degrees = f;
		}
	} Degrees;

	typedef struct Radians {
		float radians;
		float toDegrees() { return radians*DEGREE; }
		Radians() {
			radians = 0.0f;
		}
		Radians(float f) {
			radians = f;
		}
	} Radians;

	typedef struct MemBlock {
		char * buffer;
		uint size;
		MemBlock() {
			buffer = nullptr;
			size = 0;
		}
		~MemBlock() {
			delete [] buffer;
		}
	} MemBlock;

	typedef int Data2i[2];
	typedef struct Vector2i {
		const int last = 1;
		Data2i data = {0};
		int &x = data[0],
			&y = data[1];
//		int &x,
//			&y;

		int			area()			{	return data[0]*data[1];	}
		float		length()		{	return sqrtf((x*x)+(y*y));	}
		float		sudoLength()	{	return (x*x)+(y*y);	}
		Vector2i	normal()		{	Vector2i r;	r = *this * (1.0/length());	return r; }
		Vector2i	invert()		{	Vector2i r;	r = *this * -1;				return r; }

		friend Vector2i operator+(Vector2i lhs, const Vector2i& rhs) {	Vector2i r;		r.x = lhs.x + rhs.x;	r.y = lhs.y + rhs.y;	return r;	}
		friend Vector2i operator+(Vector2i lhs, const int& rhs)		 {	Vector2i r;		r.x = lhs.x + rhs;		r.y = lhs.y + rhs;		return r;	}
		friend Vector2i operator-(Vector2i lhs, const Vector2i& rhs) {	Vector2i r;		r.x = lhs.x - rhs.x;	r.y = lhs.y - rhs.y;	return r;	}
		friend Vector2i operator-(Vector2i lhs, const int& rhs)	 	 {	Vector2i r;		r.x = lhs.x - rhs;		r.y = lhs.y - rhs;		return r;	}
		friend Vector2i operator*(Vector2i lhs, const Vector2i& rhs) {	Vector2i r;		r.x = lhs.x * rhs.x;	r.y = lhs.y * rhs.y;	return r;	}
		friend Vector2i operator*(Vector2i lhs, const int& rhs) 	 {	Vector2i r;		r.x = lhs.x * rhs;		r.y = lhs.y * rhs;		return r;	}
		friend Vector2i operator/(Vector2i lhs, const Vector2i& rhs) {	Vector2i r;		r.x = lhs.x / rhs.x;	r.y = lhs.y / rhs.y;	return r;	}
		friend Vector2i operator/(Vector2i lhs, const int& rhs)	 	 {	Vector2i r;		r.x = lhs.x / rhs;		r.y = lhs.y / rhs;		return r;	}

		Vector2i operator= (const Vector2i& rhs)	{	x = rhs.x;		y = rhs.y;		x = data[0];	y = data[1];	return *this;	}
		Vector2i operator+=(const Vector2i& rhs)	{	x += rhs.x;		y += rhs.y;		x = data[0];	y = data[1];	return *this;	}
		Vector2i operator-=(const Vector2i& rhs)	{	x -= rhs.x;		y -= rhs.y;		x = data[0];	y = data[1];	return *this;	}
		Vector2i operator*=(const Vector2i& rhs) 	{	x *= rhs.x;		y *= rhs.y;		x = data[0];	y = data[1];	return *this;	}
		Vector2i operator= (const int& rhs)			{	x = rhs;		y = rhs;		x = data[0];	y = data[1];	return *this;	}
		Vector2i operator+=(const int& rhs) 		{	x += rhs;		y += rhs;		x = data[0];	y = data[1];	return *this;	}
		Vector2i operator-=(const int& rhs) 		{	x -= rhs;		y -= rhs;		x = data[0];	y = data[1];	return *this;	}
		Vector2i operator*=(const int& rhs) 		{	x *= rhs;		y *= rhs;		x = data[0];	y = data[1];	return *this;	}
		Vector2i operator++()						{	x++;			y ++;			x = data[0];	y = data[1];	return *this;	}
		Vector2i operator--()						{	x--;			y --;			x = data[0];	y = data[1];	return *this;	}
		int		 &operator[](int i)					{	if(i>last) i=last;				return data[i]; }

		Vector2i() : x(data[0]), y(data[1]) {
//			data[0] = 0;
//			data[1] = 0;
//			x = data[0];
//			y = data[1];
			x = 0;
			y = 0;
		}

		Vector2i(const int &v) : x(data[0]), y(data[1]) {
//			data[0] = v;
//			data[1] = v;
//			x = data[0];
//			y = data[1];
			x = v;
			y = v;
		}

		Vector2i(const int &iX, const int &iY) : x(data[0]), y(data[1]) {
//			data[0] = iX;
//			data[1] = iY;
//			x = data[0];
//			y = data[1];
			x = iX;
			y = iY;
		}

//		Vector2i(const Vector2i &v) {
//			data[0] = v[0];
//			data[1] = v[1];
//		}

	} Vector2i;

	typedef struct Vector2ui {
		const int last = 1;
		uint data[2] = {0};
		uint &x = data[0],
			 &y = data[1];

		float		length()		{	return sqrtf((x*x)+(y*y));	}
		float		sudoLength()	{	return (x*x)+(y*y);	}
		Vector2ui	normal()		{	Vector2ui r;	r = *this * (1.0/length());	return r; }
		Vector2ui	invert()		{	Vector2ui r;	r = *this * -1;				return r; }

		friend Vector2ui operator+(Vector2ui lhs, const Vector2ui& rhs) {	Vector2ui r;		r.x = lhs.x + rhs.x;	r.y = lhs.y + rhs.y;	return r;	}
		friend Vector2ui operator+(Vector2ui lhs, const uint& rhs)		{	Vector2ui r;		r.x = lhs.x + rhs;		r.y = lhs.y + rhs;		return r;	}
		friend Vector2ui operator-(Vector2ui lhs, const Vector2ui& rhs) {	Vector2ui r;		r.x = lhs.x - rhs.x;	r.y = lhs.y - rhs.y;	return r;	}
		friend Vector2ui operator-(Vector2ui lhs, const uint& rhs)	 	{	Vector2ui r;		r.x = lhs.x - rhs;		r.y = lhs.y - rhs;		return r;	}
		friend Vector2ui operator*(Vector2ui lhs, const Vector2ui& rhs) {	Vector2ui r;		r.x = lhs.x * rhs.x;	r.y = lhs.y * rhs.y;	return r;	}
		friend Vector2ui operator*(Vector2ui lhs, const uint& rhs)		{	Vector2ui r;		r.x = lhs.x * rhs;		r.y = lhs.y * rhs;		return r;	}
		friend Vector2ui operator/(Vector2ui lhs, const Vector2ui& rhs) {	Vector2ui r;		r.x = lhs.x / rhs.x;	r.y = lhs.y / rhs.y;	return r;	}
		friend Vector2ui operator/(Vector2ui lhs, const uint& rhs)	 	{	Vector2ui r;		r.x = lhs.x / rhs;		r.y = lhs.y / rhs;		return r;	}

		Vector2ui operator= (const Vector2ui& rhs)	{	x = rhs.x;		y = rhs.y;		return *this;	}
		Vector2ui operator+=(const Vector2ui& rhs)	{	x += rhs.x;		y += rhs.y;		return *this;	}
		Vector2ui operator-=(const Vector2ui& rhs)	{	x -= rhs.x;		y -= rhs.y;		return *this;	}
		Vector2ui operator*=(const Vector2ui& rhs) 	{	x *= rhs.x;		y *= rhs.y;		return *this;	}
		Vector2ui operator= (const uint& rhs)		{	x = rhs;		y = rhs;		return *this;	}
		Vector2ui operator+=(const uint& rhs) 		{	x += rhs;		y += rhs;		return *this;	}
		Vector2ui operator-=(const uint& rhs) 		{	x -= rhs;		y -= rhs;		return *this;	}
		Vector2ui operator*=(const uint& rhs) 		{	x *= rhs;		y *= rhs;		return *this;	}
		Vector2ui operator++()						{	x++;			y ++;			return *this;	}
		Vector2ui operator--()						{	x--;			y --;			return *this;	}
		uint	 &operator[](int i)					{	if(i>last) i=last;				return data[i]; }

		Vector2ui() {
			data[0] = 0;
			data[1] = 0;
		}

		Vector2ui(uint v) {
			data[0] = v;
			data[1] = v;
		}

		Vector2ui(uint x, uint y) {
			data[0] = x;
			data[1] = y;
		}
	} Vector2ui;

	typedef struct Vector2b {
		const int last = 1;
		bool data[2] = {0};
		bool &x = data[0],
			 &y = data[1];

		Vector2b operator= (const Vector2b& rhs)	{	x = rhs.x;		y = rhs.y;		return *this;	}
		Vector2b operator= (const bool& rhs)		{	x = rhs;		y = rhs;		return *this;	}
		bool	&operator[](int i)					{	if(i>last) i=last;				return data[i]; }

		Vector2b() {
			data[0] = 0;
			data[1] = 0;
		}

		Vector2b(bool v) {
			data[0] = v;
			data[1] = v;
		}

		Vector2b(bool x, bool y) {
			data[0] = x;
			data[1] = y;
		}

		Vector2b(const Vector2b &v) {
			data[0] = v.x;
			data[1] = v.y;
		}
	} Vector2b;

	//
	//std::vector<cVector> vertices(100);
	//const float* data = &(vertices[0].x);
	//
	//struct Vector3 {
	//  union {
	//    struct {
	//      float x,y,z;
	//    };
	//    float v [3];
	//  };
	//
	//  ...
	//
	//  Vector3 (float x_, float y_, float z_) : x (x_), y (y_), z (z_) { };
	//
	//  float Norm      (void) { return sqrt ((x * x) + (y * y) + (z * z)); }
	//  void  Normalize (void) {
	//    float norm = Norm ();
	//
	//    v [0] /= norm;
	//    v [1] /= norm;
	//    v [2] /= norm;
	//  }
	//};
	typedef float Data2f[2];		// Vector of two floats used to send data to opengl
	typedef struct Vector2f {
		const int last = 1;
		Data2f data = {0};
		float &x = data[0],
			  &y = data[1];

		float		length()		{	return sqrtf((x*x)+(y*y));	}
		float		sudoLength()	{	return (x*x)+(y*y);	}
		Vector2f	normal()		{	Vector2f r;	r = *this * (1.0/length());	return r; }
		Vector2f	invert()		{	Vector2f r;	r = *this * -1;				return r; }

		friend Vector2f operator+(Vector2f lhs, const Vector2f& rhs)	{	Vector2f r;		r.x = lhs.x + rhs.x;	r.y = lhs.y + rhs.y;	return r;	}
		friend Vector2f operator+(Vector2f lhs, const float& rhs)		{	Vector2f r;		r.x = lhs.x + rhs;		r.y = lhs.y + rhs;		return r;	}
		friend Vector2f operator-(Vector2f lhs, const Vector2f& rhs)	{	Vector2f r;		r.x = lhs.x - rhs.x;	r.y = lhs.y - rhs.y;	return r;	}
		friend Vector2f operator-(Vector2f lhs, const float& rhs)		{	Vector2f r;		r.x = lhs.x - rhs;		r.y = lhs.y - rhs;		return r;	}
		friend Vector2f operator*(Vector2f lhs, const Vector2f& rhs)	{	Vector2f r;		r.x = lhs.x * rhs.x;	r.y = lhs.y * rhs.y;	return r;	}
		friend Vector2f operator*(Vector2f lhs, const float& rhs)		{	Vector2f r;		r.x = lhs.x * rhs;		r.y = lhs.y * rhs;		return r;	}
		friend Vector2f operator/(Vector2f lhs, const Vector2f& rhs)	{	Vector2f r;		r.x = lhs.x / rhs.x;	r.y = lhs.y / rhs.y;	return r;	}
		friend Vector2f operator/(Vector2f lhs, const float& rhs)		{	Vector2f r;		r.x = lhs.x / rhs;		r.y = lhs.y / rhs;		return r;	}

		Vector2f operator= (const Vector2f& rhs)	{	x = rhs.x;		y = rhs.y;		return *this;	}
		Vector2f operator+=(const Vector2f& rhs)	{	x += rhs.x;		y += rhs.y;		return *this;	}
		Vector2f operator-=(const Vector2f& rhs)	{	x -= rhs.x;		y -= rhs.y;		return *this;	}
		Vector2f operator*=(const Vector2f& rhs) 	{	x *= rhs.x;		y *= rhs.y;		return *this;	}
		Vector2f operator= (const float& rhs)		{	x = rhs;		y = rhs;		return *this;	}
		Vector2f operator+=(const float& rhs) 		{	x += rhs;		y += rhs;		return *this;	}
		Vector2f operator-=(const float& rhs) 		{	x -= rhs;		y -= rhs;		return *this;	}
		Vector2f operator*=(const float& rhs) 		{	x *= rhs;		y *= rhs;		return *this;	}
		Vector2f operator++()						{	x++;			y ++;			return *this;	}
		Vector2f operator--()						{	x--;			y --;			return *this;	}
		float	&operator[](int i)					{	if(i>last) i=last;				return data[i]; }

		Vector2f() {
			data[0] = 0;
			data[1] = 0;
		}

		Vector2f(float v) {
			data[0] = v;
			data[1] = v;
		}

		Vector2f(Data2f d) {
			data[0] = d[0];
			data[1] = d[1];
		}

		Vector2f(float x, float y) {
			data[0] = x;
			data[1] = y;
		}
	} Vector2f;

	typedef struct Vector24f {
		Vector2f	a, b, c, d;

		Vector2f	&operator[](int i) {
			switch(i) {
				case(0):
					return a;
					break;
				case(1):
					return b;
					break;
				case(2):
					return c;
					break;
				case(3):
					return d;
					break;
			}
			return a;
		}
	} Vector24f;

	typedef struct Vector3b {
		const int last = 2;
		bool data[3] = {0};
		bool &x = data[0],
			 &y = data[1],
			 &z = data[2];

		Vector3b operator= (const Vector3b& rhs)					{	x = rhs.x;		y = rhs.y;		z = rhs.z;	return *this;	}
		Vector3b operator= (const bool& rhs)						{	x = rhs;		y = rhs;		z = rhs;	return *this;	}
		bool	&operator[](int i)									{	if(i>last) i=last;							return data[i]; }

		Vector3b() {
			data[0] = 0;
			data[1] = 0;
			data[2] = 0;
		}

		Vector3b(bool v) {
			data[0] = v;
			data[1] = v;
			data[2] = v;
		}

		Vector3b(bool x, bool y, bool z) {
			data[0] = x;
			data[1] = y;
			data[2] = z;
		}

		Vector3b(const Vector3b &v) {
			data[0] = v.x;
			data[1] = v.y;
			data[2] = v.z;
		}
	} Vector3b;

	typedef struct Vector3i {
		const int last = 2;
		int data[3] = {0};
		int &x = data[0],
			&y = data[1],
			&z = data[2];
		int &r = data[0],
			&g = data[1],
			&b = data[2];

		float		length()		{	return sqrtf((x*x)+(y*y)+(z*z));	}
		float		sudoLength()	{	return (x*x)+(y*y)+(z*z);	}
		Vector3i	normal()		{	Vector3i r;	r = *this * (1.0/length());	return r; }
		Vector3i	invert()		{	Vector3i r;	r = *this * -1;				return r; }

		friend Vector3i operator+(Vector3i lhs, const Vector3i& rhs)	{	Vector3i r;		r.x = lhs.x + rhs.x;	r.y = lhs.y + rhs.y;	r.z = lhs.z + rhs.z;	return r;	}
		friend Vector3i operator+(Vector3i lhs, const int& rhs)			{	Vector3i r;		r.x = lhs.x + rhs;		r.y = lhs.y + rhs;		r.z = lhs.z + rhs;		return r;	}
		friend Vector3i operator-(Vector3i lhs, const Vector3i& rhs)	{	Vector3i r;		r.x = lhs.x - rhs.x;	r.y = lhs.y - rhs.y;	r.z = lhs.z - rhs.z;	return r;	}
		friend Vector3i operator-(Vector3i lhs, const int& rhs)			{	Vector3i r;		r.x = lhs.x - rhs;		r.y = lhs.y - rhs;		r.z = lhs.z - rhs;		return r;	}
		friend Vector3i operator*(Vector3i lhs, const Vector3i& rhs)	{	Vector3i r;		r.x = lhs.x * rhs.x;	r.y = lhs.y * rhs.y;	r.z = lhs.z * rhs.z;	return r;	}
		friend Vector3i operator*(Vector3i lhs, const int& rhs)			{	Vector3i r;		r.x = lhs.x * rhs;		r.y = lhs.y * rhs;		r.z = lhs.z * rhs;		return r;	}
		friend Vector3i operator/(Vector3i lhs, const Vector3i& rhs)	{	Vector3i r;		r.x = lhs.x / rhs.x;	r.y = lhs.y / rhs.y;	r.z = lhs.z / rhs.z;	return r;	}
		friend Vector3i operator/(Vector3i lhs, const int& rhs)			{	Vector3i r;		r.x = lhs.x / rhs;		r.y = lhs.y / rhs;		r.z = lhs.z / rhs;		return r;	}

		Vector3i operator= (const Vector3i& rhs)	{	x = rhs.x;		y = rhs.y;		z = rhs.z;		return *this;	}
		Vector3i operator+=(const Vector3i& rhs)	{	x += rhs.x;		y += rhs.y;		z += rhs.z;		return *this;	}
		Vector3i operator-=(const Vector3i& rhs)	{	x -= rhs.x;		y -= rhs.y;		z -= rhs.z;		return *this;	}
		Vector3i operator*=(const Vector3i& rhs) 	{	x *= rhs.x;		y *= rhs.y;		z *= rhs.z;		return *this;	}
		Vector3i operator= (const int& rhs)			{	x = rhs;		y = rhs;		z = rhs;		return *this;	}
		Vector3i operator+=(const int& rhs) 		{	x += rhs;		y += rhs;		z += rhs;		return *this;	}
		Vector3i operator-=(const int& rhs) 		{	x -= rhs;		y -= rhs;		z -= rhs;		return *this;	}
		Vector3i operator*=(const int& rhs) 		{	x *= rhs;		y *= rhs;		z *= rhs;		return *this;	}
		Vector3i operator++()						{	x++;			y ++;			z ++;			return *this;	}
		Vector3i operator--()						{	x--;			y --;			z --;			return *this;	}
		int		&operator[](int i)					{	if(i>last) i=last;					return data[i]; }

		Vector3i() {
			data[0] = 0;
			data[1] = 0;
			data[2] = 0;
		}

		Vector3i(int v) {
			data[0] = v;
			data[1] = v;
			data[2] = v;
		}

		Vector3i(int x, int y, int z) {
			data[0] = x;
			data[1] = y;
			data[2] = z;
		}
	} Vector3i;

	typedef struct Vector3ui {
		const int last = 2;
		uint data[3] = {0};
		uint &x = data[0],
			 &y = data[1],
			 &z = data[2];
		uint &r = data[0],
			 &g = data[1],
			 &b = data[2];

		float		length()		{	return sqrtf((x*x)+(y*y)+(z*z));	}
		float		sudoLength()	{	return (x*x)+(y*y)+(z*z);	}
		Vector3ui	normal()		{	Vector3ui r;	r = *this * (1.0/length());	return r; }
		Vector3ui	invert()		{	Vector3ui r;	r = *this * -1;				return r; }

		friend Vector3ui operator+(Vector3ui lhs, const Vector3ui& rhs)	{	Vector3ui r;		r.x = lhs.x + rhs.x;	r.y = lhs.y + rhs.y;	r.z = lhs.z + rhs.z;	return r;	}
		friend Vector3ui operator+(Vector3ui lhs, const uint& rhs)		{	Vector3ui r;		r.x = lhs.x + rhs;		r.y = lhs.y + rhs;		r.z = lhs.z + rhs;		return r;	}
		friend Vector3ui operator-(Vector3ui lhs, const Vector3ui& rhs)	{	Vector3ui r;		r.x = lhs.x - rhs.x;	r.y = lhs.y - rhs.y;	r.z = lhs.z - rhs.z;	return r;	}
		friend Vector3ui operator-(Vector3ui lhs, const uint& rhs)		{	Vector3ui r;		r.x = lhs.x - rhs;		r.y = lhs.y - rhs;		r.z = lhs.z - rhs;		return r;	}
		friend Vector3ui operator*(Vector3ui lhs, const Vector3ui& rhs)	{	Vector3ui r;		r.x = lhs.x * rhs.x;	r.y = lhs.y * rhs.y;	r.z = lhs.z * rhs.z;	return r;	}
		friend Vector3ui operator*(Vector3ui lhs, const uint& rhs)		{	Vector3ui r;		r.x = lhs.x * rhs;		r.y = lhs.y * rhs;		r.z = lhs.z * rhs;		return r;	}
		friend Vector3ui operator/(Vector3ui lhs, const Vector3ui& rhs)	{	Vector3ui r;		r.x = lhs.x / rhs.x;	r.y = lhs.y / rhs.y;	r.z = lhs.z / rhs.z;	return r;	}
		friend Vector3ui operator/(Vector3ui lhs, const uint& rhs)		{	Vector3ui r;		r.x = lhs.x / rhs;		r.y = lhs.y / rhs;		r.z = lhs.z / rhs;		return r;	}

		Vector3ui operator= (const Vector3ui& rhs)	{	x = rhs.x;		y = rhs.y;		z = rhs.z;		return *this;	}
		Vector3ui operator+=(const Vector3ui& rhs)	{	x += rhs.x;		y += rhs.y;		z += rhs.z;		return *this;	}
		Vector3ui operator-=(const Vector3ui& rhs)	{	x -= rhs.x;		y -= rhs.y;		z -= rhs.z;		return *this;	}
		Vector3ui operator*=(const Vector3ui& rhs) 	{	x *= rhs.x;		y *= rhs.y;		z *= rhs.z;		return *this;	}
		Vector3ui operator= (const uint& rhs)		{	x = rhs;		y = rhs;		z = rhs;		return *this;	}
		Vector3ui operator+=(const uint& rhs) 		{	x += rhs;		y += rhs;		z += rhs;		return *this;	}
		Vector3ui operator-=(const uint& rhs) 		{	x -= rhs;		y -= rhs;		z -= rhs;		return *this;	}
		Vector3ui operator*=(const uint& rhs) 		{	x *= rhs;		y *= rhs;		z *= rhs;		return *this;	}
		Vector3ui operator++()						{	x++;			y ++;			z ++;			return *this;	}
		Vector3ui operator--()						{	x--;			y --;			z --;			return *this;	}
		uint	 &operator[](int i)					{	if(i>last) i=last;					return data[i]; }

		Vector3ui() {
			data[0] = 0;
			data[1] = 0;
			data[2] = 0;
		}

		Vector3ui(uint v) {
			data[0] = v;
			data[1] = v;
			data[2] = v;
		}

		Vector3ui(uint x, uint y, uint z) {
			data[0] = x;
			data[1] = y;
			data[2] = z;
		}
	} Vector3ui;

	typedef float Data3f[3];		// Vector of three floats
	typedef struct Vector3f {
		const int last = 2;
		float data[3] = {0};
		float &x = data[0],
			  &y = data[1],
			  &z = data[2];
		float &r = data[0],
			  &g = data[1],
			  &b = data[2];

		float		length()		{	return sqrtf((x*x)+(y*y)+(z*z));	}
		float		sudoLength()	{	return (x*x)+(y*y)+(z*z);	}

		//inline void ScaleVector3(Vector3f v, const float scale) { v[0] *= scale; v[1] *= scale; v[2] *= scale; }
		//inline void NormalizeVector3(Vector3f u) { ScaleVector3(u, 1.0f / GetVectorLength3(u)); }
//		inline void Normalize(Vector3f &i) {
//			float mag = sqrt(i[0]*i[0]+i[1]*i[1]+i[2]*i[2]);
//			i[0] = i[0]/mag;
//			i[1] = i[1]/mag;
//			i[2] = i[2]/mag;
//		}
		Vector3f	normal()		{
			//Vector3f r;
			//r[0] = data[0] / length();
			//r[1] = data[1] / length();
			//r[2] = data[2] / length();
			return *this/length();
		}
		Vector3f	invert()		{	Vector3f r;	r = *this * -1;				return r; }

		//friend Vector3f operator-(const Vector3f& in)	{	in.x = -in.x;	in.y = -in.y;	in.z = -in.z; return in;	}
		friend Vector3f operator+(Vector3f lhs, const Vector3f& rhs)	{	Vector3f r;		r.x = lhs.x + rhs.x;	r.y = lhs.y + rhs.y;	r.z = lhs.z + rhs.z;	return r;	}
		friend Vector3f operator+(Vector3f lhs, const float& rhs)		{	Vector3f r;		r.x = lhs.x + rhs;		r.y = lhs.y + rhs;		r.z = lhs.z + rhs;		return r;	}
		friend Vector3f operator-(Vector3f lhs, const Vector3f& rhs)	{	Vector3f r;		r.x = lhs.x - rhs.x;	r.y = lhs.y - rhs.y;	r.z = lhs.z - rhs.z;	return r;	}
		friend Vector3f operator-(Vector3f lhs, const float& rhs)		{	Vector3f r;		r.x = lhs.x - rhs;		r.y = lhs.y - rhs;		r.z = lhs.z - rhs;		return r;	}
		friend Vector3f operator*(Vector3f lhs, const Vector3f& rhs)	{	Vector3f r;		r.x = lhs.x * rhs.x;	r.y = lhs.y * rhs.y;	r.z = lhs.z * rhs.z;	return r;	}
		friend Vector3f operator*(Vector3f lhs, const float& rhs)		{	Vector3f r;		r.x = lhs.x * rhs;		r.y = lhs.y * rhs;		r.z = lhs.z * rhs;		return r;	}
		friend Vector3f operator/(Vector3f lhs, const Vector3f& rhs)	{	Vector3f r;		r.x = lhs.x / rhs.x;	r.y = lhs.y / rhs.y;	r.z = lhs.z / rhs.z;	return r;	}
		friend Vector3f operator/(Vector3f lhs, const float& rhs)		{	Vector3f r;		r.x = lhs.x / rhs;		r.y = lhs.y / rhs;		r.z = lhs.z / rhs;		return r;	}

		Vector3f operator= (const Vector3f& rhs)	{	x = rhs.x;		y = rhs.y;		z = rhs.z;		return *this;	}
		Vector3f operator+=(const Vector3f& rhs)	{	x += rhs.x;		y += rhs.y;		z += rhs.z;		return *this;	}
		Vector3f operator-=(const Vector3f& rhs)	{	x -= rhs.x;		y -= rhs.y;		z -= rhs.z;		return *this;	}
		Vector3f operator*=(const Vector3f& rhs) 	{	x *= rhs.x;		y *= rhs.y;		z *= rhs.z;		return *this;	}
		Vector3f operator= (const float& rhs)		{	x = rhs;		y = rhs;		z = rhs;		return *this;	}
		Vector3f operator+=(const float& rhs) 		{	x += rhs;		y += rhs;		z += rhs;		return *this;	}
		Vector3f operator-=(const float& rhs) 		{	x -= rhs;		y -= rhs;		z -= rhs;		return *this;	}
		Vector3f operator*=(const float& rhs) 		{	x *= rhs;		y *= rhs;		z *= rhs;		return *this;	}
		Vector3f operator++()						{	x++;			y ++;			z ++;			return *this;	}
		Vector3f operator--()						{	x--;			y --;			z --;			return *this;	}
		float	&operator[](int i)					{	if(i>last) i=last;					return data[i]; }

		Vector3f() {
			data[0] = 0;
			data[1] = 0;
			data[2] = 0;
		}

		Vector3f(float f) {
			data[0] = f;
			data[1] = f;
			data[2] = f;
		}

		Vector3f(Data3f p) {
			data[0] = p[0];
			data[1] = p[1];
			data[2] = p[2];
		}

		Vector3f(float x, float y, float z) {
			data[0] = x;
			data[1] = y;
			data[2] = z;
		}
	} Vector3f;

	typedef struct Vector4i {
		const int last = 3;
		int data[4] = {0};
//		int &x = data[0],
//			&y = data[1],
//			&z = data[2],
//			&w = data[3];
		int &r = data[0],
			&g = data[1],
			&b = data[2],
			&a = data[3];
		int &top	= data[0],
			&bottom	= data[1],
			&left	= data[2],
			&right	= data[3];

		float		length()		{	return sqrtf((data[0]*data[0])+(data[1]*data[1])+(data[2]*data[2]+(data[3]*data[3])));	}
		float		sudoLength()	{	return (data[0]*data[0])+(data[1]*data[1])+(data[2]*data[2]+(data[3]*data[3]));	}
		Vector4i	normal()		{	Vector4i r;	r = *this * (1.0/length());	return r; }
		Vector4i	invert()		{	Vector4i r;	r = *this * -1;				return r; }
		int			top_bottom()	{	return data[0]+data[1]; }
		int			left_right()	{	return data[2]+data[3]; }

		friend Vector4i operator+(Vector4i lhs, const Vector4i& rhs)	{	Vector4i r;		r.data[0] = lhs.data[0] + rhs.data[0];	r.data[1] = lhs.data[1] + rhs.data[1];	r.data[2] = lhs.data[2] + rhs.data[2];	r.data[3] = lhs.data[3] + rhs.data[3];	return r;	}
		friend Vector4i operator+(Vector4i lhs, const int& rhs)			{	Vector4i r;		r.data[0] = lhs.data[0] + rhs;		r.data[1] = lhs.data[1] + rhs;		r.data[2] = lhs.data[2] + rhs;		r.data[3] = lhs.data[3] + rhs;		return r;	}
		friend Vector4i operator-(Vector4i lhs, const Vector4i& rhs)	{	Vector4i r;		r.data[0] = lhs.data[0] - rhs.data[0];	r.data[1] = lhs.data[1] - rhs.data[1];	r.data[2] = lhs.data[2] - rhs.data[2];	r.data[3] = lhs.data[3] - rhs.data[3];	return r;	}
		friend Vector4i operator-(Vector4i lhs, const int& rhs)			{	Vector4i r;		r.data[0] = lhs.data[0] - rhs;		r.data[1] = lhs.data[1] - rhs;		r.data[2] = lhs.data[2] - rhs;		r.data[3] = lhs.data[3] - rhs;		return r;	}
		friend Vector4i operator*(Vector4i lhs, const Vector4i& rhs)	{	Vector4i r;		r.data[0] = lhs.data[0] * rhs.data[0];	r.data[1] = lhs.data[1] * rhs.data[1];	r.data[2] = lhs.data[2] * rhs.data[2];	r.data[3] = lhs.data[3] * rhs.data[3];	return r;	}
		friend Vector4i operator*(Vector4i lhs, const int& rhs)			{	Vector4i r;		r.data[0] = lhs.data[0] * rhs;		r.data[1] = lhs.data[1] * rhs;		r.data[2] = lhs.data[2] * rhs;		r.data[3] = lhs.data[3] * rhs;		return r;	}
		friend Vector4i operator/(Vector4i lhs, const Vector4i& rhs)	{	Vector4i r;		r.data[0] = lhs.data[0] / rhs.data[0];	r.data[1] = lhs.data[1] / rhs.data[1];	r.data[2] = lhs.data[2] / rhs.data[2];	r.data[3] = lhs.data[3] / rhs.data[3];	return r;	}
		friend Vector4i operator/(Vector4i lhs, const int& rhs)			{	Vector4i r;		r.data[0] = lhs.data[0] / rhs;		r.data[1] = lhs.data[1] / rhs;		r.data[2] = lhs.data[2] / rhs;		r.data[3] = lhs.data[3] / rhs;		return r;	}

		Vector4i operator= (const Vector4i& rhs)	{	data[0] = rhs.data[0];		data[1] = rhs.data[1];		data[2] = rhs.data[2];		data[3] = rhs.data[3];		return *this;	}
		Vector4i operator+=(const Vector4i& rhs)	{	data[0] += rhs.data[0];		data[1] += rhs.data[1];		data[2] += rhs.data[2];		data[3] += rhs.data[3];		return *this;	}
		Vector4i operator-=(const Vector4i& rhs)	{	data[0] -= rhs.data[0];		data[1] -= rhs.data[1];		data[2] -= rhs.data[2];		data[3] -= rhs.data[3];		return *this;	}
		Vector4i operator*=(const Vector4i& rhs) 	{	data[0] *= rhs.data[0];		data[1] *= rhs.data[1];		data[2] *= rhs.data[2];		data[3] *= rhs.data[3];		return *this;	}
		Vector4i operator= (const int& rhs)			{	data[0] = rhs;		data[1] = rhs;		data[2] = rhs;		data[3] = rhs;		return *this;	}
		Vector4i operator+=(const int& rhs) 		{	data[0] += rhs;		data[1] += rhs;		data[2] += rhs;		data[3] += rhs;		return *this;	}
		Vector4i operator-=(const int& rhs) 		{	data[0] -= rhs;		data[1] -= rhs;		data[2] -= rhs;		data[3] -= rhs;		return *this;	}
		Vector4i operator*=(const int& rhs) 		{	data[0] *= rhs;		data[1] *= rhs;		data[2] *= rhs;		data[3] *= rhs;		return *this;	}
		Vector4i operator++()						{	data[0]++;			data[1] ++;			data[2] ++;			data[3] ++;			return *this;	}
		Vector4i operator--()						{	data[0]--;			data[1] --;			data[2] --;			data[3] --;			return *this;	}
		int		&operator[](int i)					{	if(i>last) i=last;					return data[i]; }
		int& x() { return data[0]; }
		int& y() { return data[1]; }
		int& z() { return data[2]; }
		int& w() { return data[3]; }

		Vector4i() {
			data[0] = 0;
			data[1] = 0;
			data[2] = 0;
			data[3] = 0;
		}

		Vector4i(int v) {
			data[0] = v;
			data[1] = v;
			data[2] = v;
			data[3] = v;
		}

		Vector4i(int x, int y, int z, int w) {
			data[0] = x;
			data[1] = y;
			data[2] = z;
			data[3] = w;
		}
	} Vector4i;

	typedef struct VColor : public Vector4i {
//		const int last = 3;
//		int data[4];
//		int &x = data[0],
//			&y = data[1],
//			&z = data[2],
//			&w = data[3];
		int &r = data[0],
			&g = data[1],
			&b = data[2],
			&a = data[3];

//		float		length()		{	return sqrtf((x*x)+(y*y)+(z*z));	}
//		float		sudoLength()	{	return (x*x)+(y*y)+(z*z);	}
//		Vector4i	normal()		{	Vector4i r;	r = *this * (1.0/length());	return r; }
//		Vector4i	invert()		{	Vector4i r;	r = *this * -1;				return r; }
//
//		friend Vector4i operator+(Vector4i lhs, const Vector4i& rhs)	{	Vector4i r;		r.x = lhs.x + rhs.x;	r.y = lhs.y + rhs.y;	r.z = lhs.z + rhs.z;	r.w = lhs.w + rhs.w;	return r;	}
//		friend Vector4i operator+(Vector4i lhs, const int& rhs)			{	Vector4i r;		r.x = lhs.x + rhs;		r.y = lhs.y + rhs;		r.z = lhs.z + rhs;		r.w = lhs.w + rhs;		return r;	}
//		friend Vector4i operator-(Vector4i lhs, const Vector4i& rhs)	{	Vector4i r;		r.x = lhs.x - rhs.x;	r.y = lhs.y - rhs.y;	r.z = lhs.z - rhs.z;	r.w = lhs.w - rhs.w;	return r;	}
//		friend Vector4i operator-(Vector4i lhs, const int& rhs)			{	Vector4i r;		r.x = lhs.x - rhs;		r.y = lhs.y - rhs;		r.z = lhs.z - rhs;		r.w = lhs.w - rhs;		return r;	}
//		friend Vector4i operator*(Vector4i lhs, const Vector4i& rhs)	{	Vector4i r;		r.x = lhs.x * rhs.x;	r.y = lhs.y * rhs.y;	r.z = lhs.z * rhs.z;	r.w = lhs.w * rhs.w;	return r;	}
//		friend Vector4i operator*(Vector4i lhs, const int& rhs)			{	Vector4i r;		r.x = lhs.x * rhs;		r.y = lhs.y * rhs;		r.z = lhs.z * rhs;		r.w = lhs.w * rhs;		return r;	}
//		friend Vector4i operator/(Vector4i lhs, const Vector4i& rhs)	{	Vector4i r;		r.x = lhs.x / rhs.x;	r.y = lhs.y / rhs.y;	r.z = lhs.z / rhs.z;	r.w = lhs.w / rhs.w;	return r;	}
//		friend Vector4i operator/(Vector4i lhs, const int& rhs)			{	Vector4i r;		r.x = lhs.x / rhs;		r.y = lhs.y / rhs;		r.z = lhs.z / rhs;		r.w = lhs.w / rhs;		return r;	}
//
//		Vector4i operator= (const Vector4i& rhs)	{	x = rhs.x;		y = rhs.y;		z = rhs.z;		w = rhs.w;		return *this;	}
//		Vector4i operator+=(const Vector4i& rhs)	{	x += rhs.x;		y += rhs.y;		z += rhs.z;		w += rhs.w;		return *this;	}
//		Vector4i operator-=(const Vector4i& rhs)	{	x -= rhs.x;		y -= rhs.y;		z -= rhs.z;		w -= rhs.w;		return *this;	}
//		Vector4i operator*=(const Vector4i& rhs) 	{	x *= rhs.x;		y *= rhs.y;		z *= rhs.z;		w *= rhs.w;		return *this;	}
//		Vector4i operator= (const int& rhs)			{	x = rhs;		y = rhs;		z = rhs;		w = rhs;		return *this;	}
//		Vector4i operator+=(const int& rhs) 		{	x += rhs;		y += rhs;		z += rhs;		w += rhs;		return *this;	}
//		Vector4i operator-=(const int& rhs) 		{	x -= rhs;		y -= rhs;		z -= rhs;		w -= rhs;		return *this;	}
//		Vector4i operator*=(const int& rhs) 		{	x *= rhs;		y *= rhs;		z *= rhs;		w *= rhs;		return *this;	}
//		Vector4i operator++()						{	x++;			y ++;			z ++;			w ++;			return *this;	}
//		Vector4i operator--()						{	x--;			y --;			z --;			w --;			return *this;	}
//		int		&operator[](int i)					{	if(i>last) i=last;					return data[i]; }
//
//		Vector4i() {
//			data[0] = 0;
//			data[1] = 0;
//			data[2] = 0;
//			data[3] = 0;
//		}
//
//		Vector4i(int v) {
//			data[0] = v;
//			data[1] = v;
//			data[2] = v;
//			data[3] = v;
//		}
//
//		Vector4i(int x, int y, int z, int w) {
//			data[0] = x;
//			data[1] = y;
//			data[2] = z;
//			data[3] = w;
//		}
	} VColor;

//	typedef struct VPadding {
//		Vector4i data = Vector4i(0);
//		int &top	= data.x,
//			&bottom	= data.y,
//			&left	= data.z,
//			&right	= data.w;
//
//		VPadding() {
//			data = Vector4i(0);
//		}
//
//		VPadding(int v) {
//			data = Vector4i(v);
//		}
//
//		VPadding(int x, int y, int z, int w) {
//			data = Vector4i(x, y, z, w);
//		}
//	} VPadding;

	typedef struct Vector4ui {
		const int last = 3;
		uint data[4] = {0};
		uint &x = data[0],
			 &y = data[1],
			 &z = data[2],
			 &w = data[3];
		uint &r = data[0],
			 &g = data[1],
			 &b = data[2],
			 &a = data[3];

		float		length()		{	return sqrtf((x*x)+(y*y)+(z*z));	}
		float		sudoLength()	{	return (x*x)+(y*y)+(z*z);	}
		Vector4ui	normal()		{	Vector4ui r;	r = *this * (1.0/length());	return r; }
		Vector4ui	invert()		{	Vector4ui r;	r = *this * -1;				return r; }

		friend Vector4ui operator+(Vector4ui lhs, const Vector4ui& rhs) {	Vector4ui r;		r.x = lhs.x + rhs.x;	r.y = lhs.y + rhs.y;	r.z = lhs.z + rhs.z;	r.w = lhs.w + rhs.w;	return r;	}
		friend Vector4ui operator-(Vector4ui lhs, const Vector4ui& rhs) {	Vector4ui r;		r.x = lhs.x - rhs.x;	r.y = lhs.y - rhs.y;	r.z = lhs.z - rhs.z;	r.w = lhs.w - rhs.w;	return r;	}
		friend Vector4ui operator*(Vector4ui lhs, const Vector4ui& rhs) {	Vector4ui r;		r.x = lhs.x * rhs.x;	r.y = lhs.y * rhs.y;	r.z = lhs.z * rhs.z;	r.w = lhs.w * rhs.w;	return r;	}
		friend Vector4ui operator/(Vector4ui lhs, const Vector4ui& rhs) {	Vector4ui r;		r.x = lhs.x / rhs.x;	r.y = lhs.y / rhs.y;	r.z = lhs.z / rhs.z;	r.w = lhs.w / rhs.w;	return r;	}

		Vector4ui operator= (const Vector4ui& rhs)	{	x = rhs.x;		y = rhs.y;		z = rhs.z;		w = rhs.w;		return *this;	}
		Vector4ui operator+=(const Vector4ui& rhs)	{	x += rhs.x;		y += rhs.y;		z += rhs.z;		w += rhs.w;		return *this;	}
		Vector4ui operator-=(const Vector4ui& rhs)	{	x -= rhs.x;		y -= rhs.y;		z -= rhs.z;		w -= rhs.w;		return *this;	}
		Vector4ui operator*=(const Vector4ui& rhs) 	{	x *= rhs.x;		y *= rhs.y;		z *= rhs.z;		w *= rhs.w;		return *this;	}
		Vector4ui operator+=(const uint& rhs) 		{	x += rhs;		y += rhs;		z += rhs;		w += rhs;		return *this;	}
		Vector4ui operator-=(const uint& rhs) 		{	x -= rhs;		y -= rhs;		z -= rhs;		w -= rhs;		return *this;	}
		Vector4ui operator*=(const uint& rhs) 		{	x *= rhs;		y *= rhs;		z *= rhs;		w *= rhs;		return *this;	}
		Vector4ui operator++()						{	x++;			y ++;			z ++;			w ++;			return *this;	}
		Vector4ui operator--()						{	x--;			y --;			z --;			w --;			return *this;	}
		uint	 &operator[](int i)					{	if(i>last) i=last;					return data[i]; }

		Vector4ui() {
			data[0] = 0;
			data[1] = 0;
			data[2] = 0;
			data[3] = 0;
		}

		Vector4ui(uint v) {
			data[0] = v;
			data[1] = v;
			data[2] = v;
			data[3] = v;
		}

		Vector4ui(uint x, uint y, uint z, uint w) {
			data[0] = x;
			data[1] = y;
			data[2] = z;
			data[3] = w;
		}
	} Vector4ui;

	typedef float Data4f[4];		// Vector of four floats
	typedef struct Vector4f {
		const int last = 3;
		Data4f data = {0};
		float &x = data[0],
			  &y = data[1],
			  &z = data[2],
			  &w = data[3];
		float &r = data[0],
			  &g = data[1],
			  &b = data[2],
			  &a = data[3];

		float		length()		{	return sqrtf((x*x)+(y*y)+(z*z));	}
		float		sudoLength()	{	return (x*x)+(y*y)+(z*z);	}
		Vector4f	normal()		{	Vector4f r;	r = *this * (1.0/length());	return r; }
		Vector4f	invert()		{	Vector4f r;	r = *this * -1;				return r; }

		friend Vector4f operator-(const Vector4f& in)	{	Vector4f r;		r.x = -in.x;	r.y = -in.y;	r.z = -in.z;	r.w = -in.w;	return r;	}
		friend Vector4f operator+(Vector4f lhs, const Vector4f& rhs)	{	Vector4f r;		r.x = lhs.x + rhs.x;	r.y = lhs.y + rhs.y;	r.z = lhs.z + rhs.z;	r.w = lhs.w + rhs.w;	return r;	}
		friend Vector4f operator-(Vector4f lhs, const Vector4f& rhs)	{	Vector4f r;		r.x = lhs.x - rhs.x;	r.y = lhs.y - rhs.y;	r.z = lhs.z - rhs.z;	r.w = lhs.w - rhs.w;	return r;	}
		friend Vector4f operator*(Vector4f lhs, const Vector4f& rhs)	{	Vector4f r;		r.x = lhs.x * rhs.x;	r.y = lhs.y * rhs.y;	r.z = lhs.z * rhs.z;	r.w = lhs.w * rhs.w;	return r;	}
		friend Vector4f operator/(Vector4f lhs, const Vector4f& rhs)	{	Vector4f r;		r.x = lhs.x / rhs.x;	r.y = lhs.y / rhs.y;	r.z = lhs.z / rhs.z;	r.w = lhs.w / rhs.w;	return r;	}
		friend Vector4f operator+(Vector4f lhs, const float& rhs)		{	Vector4f r;		r.x = lhs.x + rhs;		r.y = lhs.y + rhs;		r.z = lhs.z + rhs;		r.w = lhs.w + rhs;		return r;	}
		friend Vector4f operator-(Vector4f lhs, const float& rhs)		{	Vector4f r;		r.x = lhs.x - rhs;		r.y = lhs.y - rhs;		r.z = lhs.z - rhs;		r.w = lhs.w - rhs;		return r;	}
		friend Vector4f operator*(Vector4f lhs, const float& rhs)		{	Vector4f r;		r.x = lhs.x * rhs;		r.y = lhs.y * rhs;		r.z = lhs.z * rhs;		r.w = lhs.w * rhs;		return r;	}
		friend Vector4f operator/(Vector4f lhs, const float& rhs)		{	Vector4f r;		r.x = lhs.x / rhs;		r.y = lhs.y / rhs;		r.z = lhs.z / rhs;		r.w = lhs.w / rhs;		return r;	}

		Vector4f operator= (const Vector4f& rhs)	{	x = rhs.x;		y = rhs.y;		z = rhs.z;		w = rhs.w;		return *this;	}
		Vector4f operator+=(const Vector4f& rhs)	{	x += rhs.x;		y += rhs.y;		z += rhs.z;		w += rhs.w;		return *this;	}
		Vector4f operator-=(const Vector4f& rhs)	{	x -= rhs.x;		y -= rhs.y;		z -= rhs.z;		w -= rhs.w;		return *this;	}
		Vector4f operator*=(const Vector4f& rhs) 	{	x *= rhs.x;		y *= rhs.y;		z *= rhs.z;		w *= rhs.w;		return *this;	}
		Vector4f operator= (const float& rhs)		{	x = rhs;		y = rhs;		z = rhs;		w = rhs;		return *this;	}
		Vector4f operator+=(const float& rhs) 		{	x += rhs;		y += rhs;		z += rhs;		w += rhs;		return *this;	}
		Vector4f operator-=(const float& rhs) 		{	x -= rhs;		y -= rhs;		z -= rhs;		w -= rhs;		return *this;	}
		Vector4f operator*=(const float& rhs) 		{	x *= rhs;		y *= rhs;		z *= rhs;		w *= rhs;		return *this;	}
		Vector4f operator++()						{	x++;			y ++;			z ++;			w ++;			return *this;	}
		Vector4f operator--()						{	x--;			y --;			z --;			w --;			return *this;	}
		float	&operator[](int i)					{	if(i>last) i=last;					return data[i]; }

		Vector4f() {
			data[0] = 0;
			data[1] = 0;
			data[2] = 0;
			data[3] = 0;
		}

		Vector4f(Data4f d) {
			data[0] = d[0];
			data[1] = d[1];
			data[2] = d[2];
			data[3] = d[3];
		}

		Vector4f(Vector3f v, float f) {
			data[0] = v.x;
			data[1] = v.y;
			data[2] = v.z;
			data[3] = f;
		}

		Vector4f(float f) {
			data[0] = f;
			data[1] = f;
			data[2] = f;
			data[3] = f;
		}

		Vector4f(float x, float y, float z, float w) {
			data[0] = x;
			data[1] = y;
			data[2] = z;
			data[3] = w;
		}
	} Vector4f;

	typedef struct Color {
		const int last = 3;
		Data4f data = {0};
		float &r = data[0],
			  &g = data[1],
			  &b = data[2],
			  &a = data[3];

//		float		length()		{	return sqrtf((r*r)+(g*g)+(b*b));	}
//		float		sudoLength()	{	return (r*r)+(g*g)+(b*b);	}
//		Color		normal()		{	Color r;	r = *this * (1.0/length());	return r; }
		Color		invert()		{	Color r;	r = *this * -1;				return r; }

//		friend Color operator-(const Color& in)					{	Color r;		r.r = -in.r;			r.g = -in.g;			r.b = -in.b;			r.a = -in.a;			return r;	}
//		friend Color operator+(Color lhs, const Color& rhs)		{	Color r;		r.r = lhs.r + rhs.r;	r.g = lhs.g + rhs.g;	r.b = lhs.b + rhs.b;	r.a = lhs.a + rhs.a;	return r;	}
//		friend Color operator-(Color lhs, const Color& rhs)		{	Color r;		r.r = lhs.r - rhs.r;	r.g = lhs.g - rhs.g;	r.b = lhs.b - rhs.b;	r.a = lhs.a - rhs.a;	return r;	}
//		friend Color operator*(Color lhs, const Color& rhs)		{	Color r;		r.r = lhs.r * rhs.r;	r.g = lhs.g * rhs.g;	r.b = lhs.b * rhs.b;	r.a = lhs.a * rhs.a;	return r;	}
//		friend Color operator/(Color lhs, const Color& rhs)		{	Color r;		r.r = lhs.r / rhs.r;	r.g = lhs.g / rhs.g;	r.b = lhs.b / rhs.b;	r.a = lhs.a / rhs.a;	return r;	}
//		friend Color operator+(Color lhs, const float& rhs)		{	Color r;		r.r = lhs.r + rhs;		r.g = lhs.g + rhs;		r.b = lhs.b + rhs;		r.a = lhs.a + rhs;		return r;	}
//		friend Color operator-(Color lhs, const float& rhs)		{	Color r;		r.r = lhs.r - rhs;		r.g = lhs.g - rhs;		r.b = lhs.b - rhs;		r.a = lhs.a - rhs;		return r;	}
//		friend Color operator*(Color lhs, const float& rhs)		{	Color r;		r.r = lhs.r * rhs;		r.g = lhs.g * rhs;		r.b = lhs.b * rhs;		r.a = lhs.a * rhs;		return r;	}
//		friend Color operator/(Color lhs, const float& rhs)		{	Color r;		r.r = lhs.r / rhs;		r.g = lhs.g / rhs;		r.b = lhs.b / rhs;		r.a = lhs.a / rhs;		return r;	}

		friend Color operator-(const Color& in)					{	Color r;		r.r = -in.r;			r.g = -in.g;			r.b = -in.b;			r.a = -in.a;			return r;	}
		friend Color operator+(Color lhs, const Color& rhs)		{	Color r;		r.r = lhs.r + rhs.r;	r.g = lhs.g + rhs.g;	r.b = lhs.b + rhs.b;	r.a = lhs.a + rhs.a;	return r;	}
		friend Color operator-(Color lhs, const Color& rhs)		{	Color r;		r.r = lhs.r - rhs.r;	r.g = lhs.g - rhs.g;	r.b = lhs.b - rhs.b;	r.a = lhs.a - rhs.a;	return r;	}
		friend Color operator*(Color lhs, const Color& rhs)		{	Color r;		r.r = lhs.r * rhs.r;	r.g = lhs.g * rhs.g;	r.b = lhs.b * rhs.b;	r.a = lhs.a * rhs.a;	return r;	}
		friend Color operator/(Color lhs, const Color& rhs)		{	Color r;		r.r = lhs.r / rhs.r;	r.g = lhs.g / rhs.g;	r.b = lhs.b / rhs.b;	r.a = lhs.a / rhs.a;	return r;	}
		friend Color operator+(Color lhs, const float& rhs)		{	Color r;		r.r = lhs.r + rhs;		r.g = lhs.g + rhs;		r.b = lhs.b + rhs;		r.a = lhs.a + rhs;		return r;	}
		friend Color operator-(Color lhs, const float& rhs)		{	Color r;		r.r = lhs.r - rhs;		r.g = lhs.g - rhs;		r.b = lhs.b - rhs;		r.a = lhs.a - rhs;		return r;	}
		friend Color operator*(Color lhs, const float& rhs)		{	Color r;		r.r = lhs.r * rhs;		r.g = lhs.g * rhs;		r.b = lhs.b * rhs;		r.a = lhs.a * rhs;		return r;	}
		friend Color operator/(Color lhs, const float& rhs)		{	Color r;		r.r = lhs.r / rhs;		r.g = lhs.g / rhs;		r.b = lhs.b / rhs;		r.a = lhs.a / rhs;		return r;	}

//		Color operator= (const Color& rhs)		{	r = rhs.r;		g = rhs.g;		b = rhs.b;		a = rhs.a;		return *this;	}
//		Color operator+=(const Color& rhs)		{	r += rhs.r;		g += rhs.g;		b += rhs.b;		a += rhs.a;		return *this;	}
//		Color operator-=(const Color& rhs)		{	r -= rhs.r;		g -= rhs.g;		b -= rhs.b;		a -= rhs.a;		return *this;	}
//		Color operator*=(const Color& rhs)		{	r *= rhs.r;		g *= rhs.g;		b *= rhs.b;		a *= rhs.a;		return *this;	}
//		Color operator= (const float& rhs)		{	r = rhs;		g = rhs;		b = rhs;		a = rhs;		return *this;	}
//		Color operator+=(const float& rhs) 		{	r += rhs;		g += rhs;		b += rhs;		a += rhs;		return *this;	}
//		Color operator-=(const float& rhs) 		{	r -= rhs;		g -= rhs;		b -= rhs;		a -= rhs;		return *this;	}
//		Color operator*=(const float& rhs) 		{	r *= rhs;		g *= rhs;		b *= rhs;		a *= rhs;		return *this;	}
//		Color operator++()						{	r++;			g ++;			b ++;			a ++;			return *this;	}
//		Color operator--()						{	r--;			g --;			b --;			a --;			return *this;	}

//		Color operator= (const Color *rhs)		{
//			std::cout << "Assign Base: (" << std::to_string(rhs.r) << ","
//										  << std::to_string(rhs.g) << ","
//										  << std::to_string(rhs.b) << ","
//										  << std::to_string(rhs.a) << "); ("
//										  << std::to_string(data[0]) << ","
//										  << std::to_string(data[1]) << ","
//										  << std::to_string(data[2]) << ","
//										  << std::to_string(data[3]) << ")";
//		}

		Color operator= (const Color& rhs)		{
			data[0] = rhs.r;	data[1] = rhs.g;	data[2] = rhs.b;	data[3] = rhs.a;


//			std::cout << "Assign Base: (" << std::to_string(rhs.r) << ","
//										  << std::to_string(rhs.g) << ","
//										  << std::to_string(rhs.b) << ","
//										  << std::to_string(rhs.a) << "); ("
//										  << std::to_string(data[0]) << ","
//										  << std::to_string(data[1]) << ","
//										  << std::to_string(data[2]) << ","
//										  << std::to_string(data[3]) << ")\n";

			return *this;
		}
		Color operator+=(const Color& rhs)		{	data[0] += rhs.r;	data[1] += rhs.g;	data[2] += rhs.b;	data[3] += rhs.a;	return *this;	}
		Color operator-=(const Color& rhs)		{	data[0] -= rhs.r;	data[1] -= rhs.g;	data[2] -= rhs.b;	data[3] -= rhs.a;	return *this;	}
		Color operator*=(const Color& rhs)		{	data[0] *= rhs.r;	data[1] *= rhs.g;	data[2] *= rhs.b;	data[3] *= rhs.a;	return *this;	}
		Color operator= (const float& rhs)		{	data[0] = rhs;		data[1] = rhs;		data[2] = rhs;		data[3] = rhs;		return *this;	}
		Color operator+=(const float& rhs) 		{	data[0] += rhs;		data[1] += rhs;		data[2] += rhs;		data[3] += rhs;		return *this;	}
		Color operator-=(const float& rhs) 		{	data[0] -= rhs;		data[1] -= rhs;		data[2] -= rhs;		data[3] -= rhs;		return *this;	}
		Color operator*=(const float& rhs) 		{	data[0] *= rhs;		data[1] *= rhs;		data[2] *= rhs;		data[3] *= rhs;		return *this;	}
		Color operator++()						{	r++;				data[1] ++;			data[2] ++;			data[3] ++;			return *this;	}
		Color operator--()						{	r--;				data[1] --;			data[2] --;			data[3] --;			return *this;	}
		float	&operator[](int i)				{	if(i>last) i=last;					return data[i]; }

		Color() {
			data[0] = 0;
			data[1] = 0;
			data[2] = 0;
			data[3] = 0;
		}

		Color(Color *c) {
			data[0] = c->data[0];
			data[1] = c->data[1];
			data[2] = c->data[2];
			data[3] = c->data[3];
		}

		Color(const Color &c) {
			data[0] = c.data[0];
			data[1] = c.data[1];
			data[2] = c.data[2];
			data[3] = c.data[3];
		}

//		Color(const Color c) {
//			data[0] = c[0];
//			data[1] = c[1];
//			data[2] = c[2];
//			data[3] = c[3];
//		}

		Color(Data4f d) {
			data[0] = d[0];
			data[1] = d[1];
			data[2] = d[2];
			data[3] = d[3];
		}

		Color(float f) {
			data[0] = f;
			data[1] = f;
			data[2] = f;
			data[3] = f;
		}

		Color(float r, float g, float b, float a) {
			data[0] = r;
			data[1] = g;
			data[2] = b;
			data[3] = a;
		}
	} Color;

	typedef struct Matrix33f {
		const int last = 9;
		float data[9] = {0};
		float 	&a0 = data[0],		&a1 = data[1],		&a2 = data[2],
				&b0 = data[3],		&b1 = data[4],		&b2 = data[5],
				&c0 = data[6],		&c1 = data[7],		&c2 = data[8];

		Matrix33f GetNormalMatrix() {
			Matrix33f r;
			r = this->Inverse();
			r = r.Transpose();
			return r;
		}

		Matrix33f Transpose() {
			Matrix33f r;
			r[0]  = a0;		r[1]  = b0;		r[2]  = c0;
			r[3]  = a1;		r[4]  = b1;		r[5]  = c1;
			r[6]  = a2;		r[7]  = b2;		r[8]  = c2;
			return r;
		}

		Matrix33f Inverse() {
			Matrix33f r;

			//Determinant
			float	dA = 1/((data[0]*data[4]*data[8]) +
							(data[3]*data[7]*data[2]) +
							(data[6]*data[1]*data[5]) -
							(data[0]*data[7]*data[5]) -
							(data[6]*data[4]*data[2]) -
							(data[3]*data[1]*data[8]));

			//Minors
			float	M11 = (data[4]*data[8])-(data[5]*data[7]),
					M12 = (data[3]*data[8])-(data[5]*data[6]),
					M13 = (data[3]*data[7])-(data[4]*data[6]),
					M21 = (data[1]*data[8])-(data[2]*data[7]),
					M22 = (data[0]*data[8])-(data[2]*data[6]),
					M23 = (data[0]*data[7])-(data[1]*data[6]),
					M31 = (data[1]*data[5])-(data[2]*data[4]),
					M32 = (data[0]*data[5])-(data[2]*data[3]),
					M33 = (data[0]*data[4])-(data[1]*data[3]);

			//Output Results
			r[0] = dA*M11;
			r[1] = dA*M12;
			r[2] = dA*M13;
			r[3] = dA*M21;
			r[4] = dA*M22;
			r[5] = dA*M23;
			r[6] = dA*M31;
			r[7] = dA*M32;
			r[8] = dA*M33;
			return r;
		}

		Matrix33f operator= (const float& rhs)		{
			a0 = rhs;		a1 = rhs;		a2 = rhs;
			b0 = rhs;		b1 = rhs;		b2 = rhs;
			c0 = rhs;		c1 = rhs;		c2 = rhs;
			return *this;
		}

		Matrix33f operator= (const Matrix33f& rhs)	{
			a0 = rhs.a0;		a1 = rhs.a1;		a2 = rhs.a2;
			b0 = rhs.b0;		b1 = rhs.b1;		b2 = rhs.b2;
			c0 = rhs.c0;		c1 = rhs.c1;		c2 = rhs.c2;
			return *this;
		}

		friend Matrix33f operator+(Matrix33f lhs, const float& rhs)		{
			Matrix33f r;
			r.a0 = lhs.a0 + rhs;		r.a1 = lhs.a1 + rhs;		r.a2 = lhs.a2 + rhs;
			r.b0 = lhs.b0 + rhs;		r.b1 = lhs.b1 + rhs;		r.b2 = lhs.b2 + rhs;
			r.c0 = lhs.c0 + rhs;		r.c1 = lhs.c1 + rhs;		r.c2 = lhs.c2 + rhs;
			return r;
		}

		friend Matrix33f operator+(Matrix33f lhs, const Matrix33f& rhs)	{
			Matrix33f r;
			r.a0 = lhs.a0 + rhs.a0;		r.a1 = lhs.a1 + rhs.a1;		r.a2 = lhs.a2 + rhs.a2;
			r.b0 = lhs.b0 + rhs.b0;		r.b1 = lhs.b1 + rhs.b1;		r.b2 = lhs.b2 + rhs.b2;
			r.c0 = lhs.c0 + rhs.c0;		r.c1 = lhs.c1 + rhs.c1;		r.c2 = lhs.c2 + rhs.c2;
			return r;
		}

		friend Matrix33f operator-(Matrix33f lhs, const float& rhs)		{
			Matrix33f r;
			r.a0 = lhs.a0 - rhs;		r.a1 = lhs.a1 - rhs;		r.a2 = lhs.a2 - rhs;
			r.b0 = lhs.b0 - rhs;		r.b1 = lhs.b1 - rhs;		r.b2 = lhs.b2 - rhs;
			r.c0 = lhs.c0 - rhs;		r.c1 = lhs.c1 - rhs;		r.c2 = lhs.c2 - rhs;
			return r;
		}

		friend Matrix33f operator-(Matrix33f lhs, const Matrix33f& rhs)	{
			Matrix33f r;
			r.a0 = lhs.a0 - rhs.a0;		r.a1 = lhs.a1 - rhs.a1;		r.a2 = lhs.a2 - rhs.a2;
			r.b0 = lhs.b0 - rhs.b0;		r.b1 = lhs.b1 - rhs.b1;		r.b2 = lhs.b2 - rhs.b2;
			r.c0 = lhs.c0 - rhs.c0;		r.c1 = lhs.c1 - rhs.c1;		r.c2 = lhs.c2 - rhs.c2;
			return r;
		}

		friend Matrix33f operator/(Matrix33f lhs, const float& rhs)		{
			Matrix33f r;
			r.a0 = lhs.a0 / rhs;		r.a1 = lhs.a1 / rhs;		r.a2 = lhs.a2 / rhs;
			r.b0 = lhs.b0 / rhs;		r.b1 = lhs.b1 / rhs;		r.b2 = lhs.b2 / rhs;
			r.c0 = lhs.c0 / rhs;		r.c1 = lhs.c1 / rhs;		r.c2 = lhs.c2 / rhs;
			return r;
		}

		friend Matrix33f operator*(Matrix33f lhs, const float& rhs)		{
			Matrix33f r;
			r.a0 = lhs.a0 * rhs;		r.a1 = lhs.a1 * rhs;		r.a2 = lhs.a2 * rhs;
			r.b0 = lhs.b0 * rhs;		r.b1 = lhs.b1 * rhs;		r.b2 = lhs.b2 * rhs;
			r.c0 = lhs.c0 * rhs;		r.c1 = lhs.c1 * rhs;		r.c2 = lhs.c2 * rhs;
			return r;
		}

		friend Vector3f operator*(Matrix33f lhs, const Vector3f& rhs)	{
			Vector3f r;
			r[0] = (lhs.a0*rhs.x)+(lhs.a1*rhs.y)+(lhs.a2*rhs.z);
			r[1] = (lhs.b0*rhs.x)+(lhs.b1*rhs.y)+(lhs.b2*rhs.z);
			r[2] = (lhs.c0*rhs.x)+(lhs.c1*rhs.y)+(lhs.c2*rhs.z);
			return r;
		}

		friend Matrix33f operator*(Matrix33f lhs, Matrix33f& rhs) {
			Matrix33f r;
			#define A(row,col)  lhs[(col<<2)+row]
			#define B(row,col)  rhs[(col<<2)+row]
			#define P(row,col)  r[(col<<2)+row]

			for (int i = 0; i < 3; i++) {
				float ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2);
				P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0);
				P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1);
				P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2);
			}
			return r;

			#undef A
			#undef B
			#undef P
		}

		Matrix33f operator*=(float& rhs) 		{	*this = *this * rhs;		return *this;	}
		Vector3f operator*=(Vector3f& rhs) 		{	Vector3f r = *this * rhs;	return r;	}

		float&	 operator[](int i)				{	if(i>last) i=last;			return data[i]; }

		Matrix33f() {
			data[0]  = 1;		data[1]  = 0;		data[2]  = 0;
			data[3]  = 0;		data[4]  = 1;		data[5]  = 0;
			data[6]  = 0;		data[7]  = 0;		data[8] = 1;
		}

		Matrix33f(float v) {
			data[0]  = v;		data[1]  = v;		data[2]  = v;
			data[3]  = v;		data[4]  = v;		data[5]  = v;
			data[6]  = v;		data[7]  = v;		data[8] = v;
		}

		Matrix33f(	float a,	float b,	float c,
					float d,	float e,	float f,
					float g,	float h,	float i) {
			data[0]  = a;		data[1]  = b;		data[2]  = c;
			data[3]  = d;		data[4]  = e;		data[5]  = f;
			data[6]  = g;		data[7]  = h;		data[8] = i;
		}
	} Matrix33f;

	//typedef float Data44f[16];		// Vector of two floats used to send data to opengl
	/*
	 * 		[a0][a1][a2][a3]
	 * 		[b0][b1][b2][b3]
	 * 		[c0][c1][c2][c3]
	 * 		[d0][d1][d2][d3]
	 */
	typedef struct Matrix44f {
		const int last = 15;
		float data[16] = {0};
		float 	&a0 = data[0],		&a1 = data[1],		&a2 = data[2],		&a3 = data[3],
				&b0 = data[4],		&b1 = data[5],		&b2 = data[6],		&b3 = data[7],
				&c0 = data[8],		&c1 = data[9],		&c2 = data[10],		&c3 = data[11],
				&d0 = data[12],		&d1 = data[13],		&d2 = data[14],		&d3 = data[15];

		Matrix44f GetNormalMatrix() {
			Matrix44f r;
			r = this->Inverse();
			r = r.Transpose();
			return r;
		}

		Matrix44f Transpose() {
			Matrix44f r;
			r[0]  = a0;		r[1]  = b0;		r[2]  = c0;		r[3]  = d0;
			r[4]  = a1;		r[5]  = b1;		r[6]  = c1;		r[7]  = d1;
			r[8]  = a2;		r[9]  = b2;		r[10] = c2;		r[11] = d2;
			r[12] = a3;		r[13] = b3;		r[14] = c3;		r[15] = d3;
			return r;
		}

		Matrix44f Inverse() {
			Matrix44f inv, r;
			float det;

			inv[0] =   data[5]  * data[10] * data[15] -
					   data[5]  * data[11] * data[14] -
					   data[9]  * data[6]  * data[15] +
					   data[9]  * data[7]  * data[14] +
					   data[13] * data[6]  * data[11] -
					   data[13] * data[7]  * data[10];

			inv[4] =  -data[4]  * data[10] * data[15] +
					   data[4]  * data[11] * data[14] +
					   data[8]  * data[6]  * data[15] -
					   data[8]  * data[7]  * data[14] -
					   data[12] * data[6]  * data[11] +
					   data[12] * data[7]  * data[10];

			inv[8] =   data[4]  * data[9]  * data[15] -
					   data[4]  * data[11] * data[13] -
					   data[8]  * data[5]  * data[15] +
					   data[8]  * data[7]  * data[13] +
					   data[12] * data[5]  * data[11] -
					   data[12] * data[7]  * data[9];

			inv[12] = -data[4]  * data[9]  * data[14] +
					   data[4]  * data[10] * data[13] +
					   data[8]  * data[5]  * data[14] -
					   data[8]  * data[6]  * data[13] -
					   data[12] * data[5]  * data[10] +
					   data[12] * data[6]  * data[9];

			inv[1] =  -data[1]  * data[10] * data[15] +
					   data[1]  * data[11] * data[14] +
					   data[9]  * data[2]  * data[15] -
					   data[9]  * data[3]  * data[14] -
					   data[13] * data[2]  * data[11] +
					   data[13] * data[3]  * data[10];

			inv[5] =   data[0]  * data[10] * data[15] -
					   data[0]  * data[11] * data[14] -
					   data[8]  * data[2]  * data[15] +
					   data[8]  * data[3]  * data[14] +
					   data[12] * data[2]  * data[11] -
					   data[12] * data[3]  * data[10];

			inv[9] =  -data[0]  * data[9]  * data[15] +
					   data[0]  * data[11] * data[13] +
					   data[8]  * data[1]  * data[15] -
					   data[8]  * data[3]  * data[13] -
					   data[12] * data[1]  * data[11] +
					   data[12] * data[3]  * data[9];

			inv[13] =  data[0]  * data[9]  * data[14] -
					   data[0]  * data[10] * data[13] -
					   data[8]  * data[1]  * data[14] +
					   data[8]  * data[2]  * data[13] +
					   data[12] * data[1]  * data[10] -
					   data[12] * data[2]  * data[9];

			inv[2] =   data[1]  * data[6]  * data[15] -
					   data[1]  * data[7]  * data[14] -
					   data[5]  * data[2]  * data[15] +
					   data[5]  * data[3]  * data[14] +
					   data[13] * data[2]  * data[7]  -
					   data[13] * data[3]  * data[6];

			inv[6] =  -data[0]  * data[6]  * data[15] +
					   data[0]  * data[7]  * data[14] +
					   data[4]  * data[2]  * data[15] -
					   data[4]  * data[3]  * data[14] -
					   data[12] * data[2]  * data[7]  +
					   data[12] * data[3]  * data[6];

			inv[10] =  data[0]  * data[5]  * data[15] -
					   data[0]  * data[7]  * data[13] -
					   data[4]  * data[1]  * data[15] +
					   data[4]  * data[3]  * data[13] +
					   data[12] * data[1]  * data[7]  -
					   data[12] * data[3]  * data[5];

			inv[14] = -data[0]  * data[5]  * data[14] +
					   data[0]  * data[6]  * data[13] +
					   data[4]  * data[1]  * data[14] -
					   data[4]  * data[2]  * data[13] -
					   data[12] * data[1]  * data[6]  +
					   data[12] * data[2]  * data[5];

			inv[3] =  -data[1]  * data[6]  * data[11] +
					   data[1]  * data[7]  * data[10] +
					   data[5]  * data[2]  * data[11] -
					   data[5]  * data[3]  * data[10] -
					   data[9]  * data[2]  * data[7]  +
					   data[9]  * data[3]  * data[6];

			inv[7] =   data[0]  * data[6]  * data[11] -
					   data[0]  * data[7]  * data[10] -
					   data[4]  * data[2]  * data[11] +
					   data[4]  * data[3]  * data[10] +
					   data[8]  * data[2]  * data[7]  -
					   data[8]  * data[3]  * data[6];

			inv[11] = -data[0]  * data[5]  * data[11] +
					   data[0]  * data[7]  * data[9]  +
					   data[4]  * data[1]  * data[11] -
					   data[4]  * data[3]  * data[9]  -
					   data[8]  * data[1]  * data[7]  +
					   data[8]  * data[3]  * data[5];

			inv[15] =  data[0]  * data[5]  * data[10] -
					   data[0]  * data[6]  * data[9]  -
					   data[4]  * data[1]  * data[10] +
					   data[4]  * data[2]  * data[9]  +
					   data[8]  * data[1]  * data[6]  -
					   data[8]  * data[2]  * data[5];

			det = data[0] * inv[0] + data[1] * inv[4] + data[2] * inv[8] + data[3] * inv[12];

			if (det == 0)	return Matrix44f();

			det = 1.0 / det;
			//for (uint n = 0; n < 16; n++)	r[n] = inv[n] * det;
			r = inv * det;
			return r;
		}

		/*
		 * This only creates a rotation matrix and sets this
		 * matrix as that rotation matrix which can then be
		 * applied to vectors.
		 */
		Matrix44f Rotate(Radians angle, float x, float y, float z)
		{
			Matrix44f mRotate = { 1.0f, 0.0f, 0.0f, 0.0f,
								  0.0f, 1.0f, 0.0f, 0.0f,
								  0.0f, 0.0f, 1.0f, 0.0f,
								  0.0f, 0.0f, 0.0f, 1.0f };

			float mag, s, c;
			float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

			s = float(sin(angle.radians));
			c = float(cos(angle.radians));

			mag = float(sqrt( x*x + y*y + z*z ));

			// Identity matrix
			if (mag == 0.0f) {
				return *this;
			}

			// Rotation matrix is normalized
			x /= mag;
			y /= mag;
			z /= mag;

			#define M(row,col)  mRotate[col*4+row]
				xx = x * x;
				yy = y * y;
				zz = z * z;
				xy = x * y;
				yz = y * z;
				zx = z * x;
				xs = x * s;
				ys = y * s;
				zs = z * s;
				one_c = 1.0f - c;

				M(0,0) = (one_c * xx) + c;
				M(0,1) = (one_c * xy) - zs;
				M(0,2) = (one_c * zx) + ys;
				M(0,3) = 0.0f;

				M(1,0) = (one_c * xy) + zs;
				M(1,1) = (one_c * yy) + c;
				M(1,2) = (one_c * yz) - xs;
				M(1,3) = 0.0f;

				M(2,0) = (one_c * zx) - ys;
				M(2,1) = (one_c * yz) + xs;
				M(2,2) = (one_c * zz) + c;
				M(2,3) = 0.0f;

				M(3,0) = 0.0f;
				M(3,1) = 0.0f;
				M(3,2) = 0.0f;
				M(3,3) = 1.0f;
			#undef M

//			data[0]  = data[0]  * mRotate.a0;	data[1]  = data[1]  * mRotate.a1;	data[2]  = data[2]  * mRotate.a2;	data[3]  = data[3]  * mRotate.a3;
//			data[4]  = data[4]  * mRotate.b0;	data[5]  = data[5]  * mRotate.b1;	data[6]  = data[6]  * mRotate.b2;	data[7]  = data[7]  * mRotate.b3;
//			data[8]  = data[8]  * mRotate.c0;	data[9]  = data[9]  * mRotate.c1;	data[10] = data[10] * mRotate.c2;	data[11] = data[11] * mRotate.c3;
//			data[12] = data[12] * mRotate.d0;	data[13] = data[13] * mRotate.d1;	data[14] = data[14] * mRotate.d2;	data[15] = data[15] * mRotate.d3;

//		std::cout << "angle: " << angle.radians << " | mag: " << mag << "(" << x << ", " << y << ", " << z << ")" << std::endl;

			data[0]  = mRotate.a0;	data[1]  = mRotate.a1;	data[2]  = mRotate.a2;	data[3]  = mRotate.a3;
			data[4]  = mRotate.b0;	data[5]  = mRotate.b1;	data[6]  = mRotate.b2;	data[7]  = mRotate.b3;
			data[8]  = mRotate.c0;	data[9]  = mRotate.c1;	data[10] = mRotate.c2;	data[11] = mRotate.c3;
			data[12] = mRotate.d0;	data[13] = mRotate.d1;	data[14] = mRotate.d2;	data[15] = mRotate.d3;

			return *this;
		}

		Matrix44f operator= (const float& rhs)		{
			a0 = rhs;		a1 = rhs;		a2 = rhs;		a3 = rhs;
			b0 = rhs;		b1 = rhs;		b2 = rhs;		b3 = rhs;
			c0 = rhs;		c1 = rhs;		c2 = rhs;		c3 = rhs;
			d0 = rhs;		d1 = rhs;		d2 = rhs;		d3 = rhs;
			return *this;
		}

		Matrix44f operator= (const Matrix44f& rhs)	{
			a0 = rhs.a0;		a1 = rhs.a1;		a2 = rhs.a2;		a3 = rhs.a3;
			b0 = rhs.b0;		b1 = rhs.b1;		b2 = rhs.b2;		b3 = rhs.b3;
			c0 = rhs.c0;		c1 = rhs.c1;		c2 = rhs.c2;		c3 = rhs.c3;
			d0 = rhs.d0;		d1 = rhs.d1;		d2 = rhs.d2;		d3 = rhs.d3;
			return *this;
		}

		friend Matrix44f operator+(Matrix44f lhs, const float& rhs)		{
			Matrix44f r;
			r.a0 = lhs.a0 + rhs;		r.a1 = lhs.a1 + rhs;		r.a2 = lhs.a2 + rhs;		r.a3 = lhs.a3 + rhs;
			r.b0 = lhs.b0 + rhs;		r.b1 = lhs.b1 + rhs;		r.b2 = lhs.b2 + rhs;		r.b3 = lhs.b3 + rhs;
			r.c0 = lhs.c0 + rhs;		r.c1 = lhs.c1 + rhs;		r.c2 = lhs.c2 + rhs;		r.c3 = lhs.c3 + rhs;
			r.d0 = lhs.d0 + rhs;		r.d1 = lhs.d1 + rhs;		r.d2 = lhs.d2 + rhs;		r.d3 = lhs.d3 + rhs;
			return r;
		}

		friend Matrix44f operator+(Matrix44f lhs, const Matrix44f& rhs)	{
			Matrix44f r;
			r.a0 = lhs.a0 + rhs.a0;		r.a1 = lhs.a1 + rhs.a1;		r.a2 = lhs.a2 + rhs.a2;		r.a3 = lhs.a3 + rhs.a3;
			r.b0 = lhs.b0 + rhs.b0;		r.b1 = lhs.b1 + rhs.b1;		r.b2 = lhs.b2 + rhs.b2;		r.b3 = lhs.b3 + rhs.b3;
			r.c0 = lhs.c0 + rhs.c0;		r.c1 = lhs.c1 + rhs.c1;		r.c2 = lhs.c2 + rhs.c2;		r.c3 = lhs.c3 + rhs.c3;
			r.d0 = lhs.d0 + rhs.d0;		r.d1 = lhs.d1 + rhs.d1;		r.d2 = lhs.d2 + rhs.d2;		r.d3 = lhs.d3 + rhs.d3;
			return r;
		}

		friend Matrix44f operator-(Matrix44f lhs, const float& rhs)		{
			Matrix44f r;
			r.a0 = lhs.a0 - rhs;		r.a1 = lhs.a1 - rhs;		r.a2 = lhs.a2 - rhs;		r.a3 = lhs.a3 - rhs;
			r.b0 = lhs.b0 - rhs;		r.b1 = lhs.b1 - rhs;		r.b2 = lhs.b2 - rhs;		r.b3 = lhs.b3 - rhs;
			r.c0 = lhs.c0 - rhs;		r.c1 = lhs.c1 - rhs;		r.c2 = lhs.c2 - rhs;		r.c3 = lhs.c3 - rhs;
			r.d0 = lhs.d0 - rhs;		r.d1 = lhs.d1 - rhs;		r.d2 = lhs.d2 - rhs;		r.d3 = lhs.d3 - rhs;
			return r;
		}

		friend Matrix44f operator-(Matrix44f lhs, const Matrix44f& rhs)	{
			Matrix44f r;
			r.a0 = lhs.a0 - rhs.a0;		r.a1 = lhs.a1 - rhs.a1;		r.a2 = lhs.a2 - rhs.a2;		r.a3 = lhs.a3 - rhs.a3;
			r.b0 = lhs.b0 - rhs.b0;		r.b1 = lhs.b1 - rhs.b1;		r.b2 = lhs.b2 - rhs.b2;		r.b3 = lhs.b3 - rhs.b3;
			r.c0 = lhs.c0 - rhs.c0;		r.c1 = lhs.c1 - rhs.c1;		r.c2 = lhs.c2 - rhs.c2;		r.c3 = lhs.c3 - rhs.c3;
			r.d0 = lhs.d0 - rhs.d0;		r.d1 = lhs.d1 - rhs.d1;		r.d2 = lhs.d2 - rhs.d2;		r.d3 = lhs.d3 - rhs.d3;
			return r;
		}

		friend Matrix44f operator/(Matrix44f lhs, const float& rhs)		{
			Matrix44f r;
			r.a0 = lhs.a0 / rhs;		r.a1 = lhs.a1 / rhs;		r.a2 = lhs.a2 / rhs;		r.a3 = lhs.a3 / rhs;
			r.b0 = lhs.b0 / rhs;		r.b1 = lhs.b1 / rhs;		r.b2 = lhs.b2 / rhs;		r.b3 = lhs.b3 / rhs;
			r.c0 = lhs.c0 / rhs;		r.c1 = lhs.c1 / rhs;		r.c2 = lhs.c2 / rhs;		r.c3 = lhs.c3 / rhs;
			r.d0 = lhs.d0 / rhs;		r.d1 = lhs.d1 / rhs;		r.d2 = lhs.d2 / rhs;		r.d3 = lhs.d3 / rhs;
			return r;
		}

		friend Matrix44f operator*(Matrix44f lhs, const float& rhs)		{
			Matrix44f r;
			r.a0 = lhs.a0 * rhs;		r.a1 = lhs.a1 * rhs;		r.a2 = lhs.a2 * rhs;		r.a3 = lhs.a3 * rhs;
			r.b0 = lhs.b0 * rhs;		r.b1 = lhs.b1 * rhs;		r.b2 = lhs.b2 * rhs;		r.b3 = lhs.b3 * rhs;
			r.c0 = lhs.c0 * rhs;		r.c1 = lhs.c1 * rhs;		r.c2 = lhs.c2 * rhs;		r.c3 = lhs.c3 * rhs;
			r.d0 = lhs.d0 * rhs;		r.d1 = lhs.d1 * rhs;		r.d2 = lhs.d2 * rhs;		r.d3 = lhs.d3 * rhs;
			return r;
		}

		friend Vector4f operator*(Matrix44f lhs, const Vector4f& rhs)	{
			float x = (lhs.data[0] *rhs.x)+(lhs.data[1] *rhs.y)+(lhs.data[2] *rhs.z)+(lhs.data[3] *rhs.w);
			float y = (lhs.data[4] *rhs.x)+(lhs.data[5] *rhs.y)+(lhs.data[6] *rhs.z)+(lhs.data[7] *rhs.w);
			float z = (lhs.data[8] *rhs.x)+(lhs.data[9] *rhs.y)+(lhs.data[10]*rhs.z)+(lhs.data[11]*rhs.w);
			float w = (lhs.data[12]*rhs.x)+(lhs.data[13]*rhs.y)+(lhs.data[14]*rhs.z)+(lhs.data[15]*rhs.w);
			return Vector4f(x, y, z, w);
		}

		friend Vector4f operator*(Matrix44f lhs, const Data4f& rhs)	{
			float x = (lhs.data[0] *rhs[0])+(lhs.data[1] *rhs[1])+(lhs.data[2] *rhs[2])+(lhs.data[3] *rhs[3]);
			float y = (lhs.data[4] *rhs[0])+(lhs.data[5] *rhs[1])+(lhs.data[6] *rhs[2])+(lhs.data[7] *rhs[3]);
			float z = (lhs.data[8] *rhs[0])+(lhs.data[9] *rhs[1])+(lhs.data[10]*rhs[2])+(lhs.data[11]*rhs[3]);
			float w = (lhs.data[12]*rhs[0])+(lhs.data[13]*rhs[1])+(lhs.data[14]*rhs[2])+(lhs.data[15]*rhs[3]);
			return Vector4f(x, y, z, w);
		}

		friend Matrix44f operator*(Matrix44f lhs, Matrix44f& rhs) {
			Matrix44f r;
			#define A(row,col)  lhs[(col<<2)+row]
			#define B(row,col)  rhs[(col<<2)+row]
			#define P(row,col)  r[(col<<2)+row]

			for (int i = 0; i < 4; i++) {
				float ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
				P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0) + ai3 * B(3,0);
				P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1) + ai3 * B(3,1);
				P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2) + ai3 * B(3,2);
				P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3 * B(3,3);
			}
			return r;

			#undef A
			#undef B
			#undef P
		}

		Matrix44f operator*=(float& rhs) 		{	*this = *this * rhs;		return *this;	}
		Vector4f operator*=(Vector4f& rhs) 		{	Vector4f r = *this * rhs;	return r;	}

		float&	 operator[](int i)				{	if(i>last) i=last;			return data[i]; }

		Matrix44f() {
			data[0]  = 1;		data[1]  = 0;		data[2]  = 0;		data[3]  = 0;
			data[4]  = 0;		data[5]  = 1;		data[6]  = 0;		data[7]  = 0;
			data[8]  = 0;		data[9]  = 0;		data[10] = 1;		data[11] = 0;
			data[12] = 0;		data[13] = 0;		data[14] = 0;		data[15] = 1;
		}

//		Matrix44f(float * f) {
//			data[0]  = f[0];	data[1]  = f[1];	data[2]  = f[2];	data[3]  = f[3];
//			data[4]  = f[4];	data[5]  = f[5];	data[6]  = f[6];	data[7]  = f[7];
//			data[8]  = f[8];	data[9]  = f[9];	data[10] = f[10];	data[11] = f[11];
//			data[12] = f[12];	data[13] = f[13];	data[14] = f[14];	data[15] = f[15];
//		}

		Matrix44f(float v) {
			data[0]  = v;		data[1]  = v;		data[2]  = v;		data[3]  = v;
			data[4]  = v;		data[5]  = v;		data[6]  = v;		data[7]  = v;
			data[8]  = v;		data[9]  = v;		data[10] = v;		data[11] = v;
			data[12] = v;		data[13] = v;		data[14] = v;		data[15] = v;
		}

		Matrix44f(	float a,	float b,	float c,	float d,
					float e,	float f,	float g,	float h,
					float i,	float j,	float k,	float l,
					float m,	float n,	float o,	float p) {
			data[0]  = a;		data[1]  = b;		data[2]  = c;		data[3]  = d;
			data[4]  = e;		data[5]  = f;		data[6]  = g;		data[7]  = h;
			data[8]  = i;		data[9]  = j;		data[10] = k;		data[11] = l;
			data[12] = m;		data[13] = n;		data[14] = o;		data[15] = p;
		}
	} Matrix44f;


	typedef std::variant<bool, int, float, std::string> t_BIFS;
	typedef std::variant<bool, int, float> t_BIF;


//	typedef struct _t_BIFS : public std::variant<bool, int, float, std::string> {
//		std::string to_string() {
//			switch (this->index()) {
//				case 0:
//					return std::to_string(std::get<bool>(*this));
//					break;
//				case 1:
//					return std::to_string(std::get<int>(*this));
//					break;
//				case 2:
//					return std::to_string(std::get<float>(*this));
//					break;
//				case 3:
//					return std::get<std::string>(*this);
//					break;
//			}
//			return "[Undefined Type]";
//		}
//	} t_BIFS;

	template <typename KEY, typename VALUE>
	class t_Map {
		private:
			Map_si map;

		public:
			t_Map() {}
			virtual ~t_Map() {}

			bool checkKey(KEY key, bool bThrow=true) {
				if(map.count(key)>0) return true;
				else {
					if (bThrow) {

						// FIXME: Create a throwRuntimeError() function that accepts '<<'

						std::ostringstream sMessage;
						sMessage << "Invalid Key in t_Map: '" << key << "'";
						throw std::runtime_error(sMessage.str());
					}
					else return false;
				}
			}

			virtual VALUE & operator[](KEY key)	{
				checkKey(key);
				return map[key];
			}

//			int	operator()(std::string name) {
//				checkName(name);
//				return groups[map[name]].index;
//			}

			virtual void add(KEY key, VALUE value, bool bThrow=true) {
				if(!checkKey(key, false)) {
					map.insert(make_pair(key, value));
				}
				else if(bThrow) {
					std::ostringstream sMessage;
					sMessage << "Duplicate Key in t_Map: '" << key << "'";
					throw std::runtime_error(sMessage.str());
				}

			}

			virtual void remove(KEY key, bool bThrow=true) {
				if(checkKey(key, false)) {
					map.erase(key);
				}
				else if(bThrow) {
					std::ostringstream sMessage;
					sMessage << "Duplicate Key in t_Map: '" << key << "'";
					throw std::runtime_error(sMessage.str());
				}

			}

			virtual VALUE & get(KEY key)	{
				checkKey(key);
				return map[key];
			}

			KEY getName(VALUE value) {
				for (const auto& item : map) {
					if(item.second == value) return item.first;
				}
				return KEY();
			}

			int size() {
				return map.size();
			}

			/*
			 * Allow Iteration
			 *
			 * Example:
			 * 	t_Vector<T> items;
			 * 	for(auto item : items) {}
			 */
//			typedef VALUE* iterator;
//			typedef const VALUE* const_iterator;
//			iterator begin() 		{ return &map[0]; }
//			iterator end() 			{ return &map[map.size()]; }
//			const_iterator begin() 	const	{ return &map[0]; }
//			const_iterator end() 	const	{ return &map[map.size()]; }
	};

	// TODO: Implement copy/move/assignment constructor
	template <typename T>
	class t_Vector1T {
		private:
			std::vector<T> typeList;

		public:
			t_Vector1T() {}
			virtual ~t_Vector1T() {}

			bool checkID(int id, bool bThrow=true) {
				if(id >= 0 && id < typeList.size()) return true;
				else {
					if (bThrow) throw std::runtime_error("Invalid ID: '"+std::to_string(id)+"'");
					else return false;
				}
			}

			virtual T & operator[](int id)	{
				checkID(id);
				return typeList[id];
			}

			virtual T & add(T t) {
				typeList.push_back(t);
				int id = typeList.size() - 1;
				return typeList[id];

			}

			virtual void remove(int id, bool bThrow=true) {
				if(checkID(id, false)) {
					typeList.erase(typeList.begin() + id);
				}
				else {
					if(bThrow) throw std::runtime_error("ID in t_Vector doesn't exist: '"+std::to_string(id)+"'");
				}

			}

			virtual T & get(int id)	{
				checkID(id);
				return typeList[id];
			}

			int size() {
				return typeList.size();
			}

			t_Vector1T(const t_Vector1T &src) {
				for (auto & item : src) {
					add(item);
				}
			}

			t_Vector1T &operator=(const t_Vector1T &&src) {
				for (auto & item : src) {
					add(item);
				}
				return *this;
			}

			/*
			 * Allow Iteration
			 *
			 * Example:
			 * 	t_Vector<T> items;
			 * 	for(auto item : items) {
			 * 		// Work with 'item'
			 * 	}
			 */
			typedef T* iterator;
			typedef const T* const_iterator;
			iterator begin() 		{ return &typeList[0]; }
			iterator end() 			{ return &typeList[typeList.size()]; }
			const_iterator begin() 	const	{ return &typeList[0]; }
			const_iterator end() 	const	{ return &typeList[typeList.size()]; }
	};

//	template<unsigned N>
//	struct FixedString {
//		char buf[N + 1]{};
//		constexpr FixedString(char const* s) {
//			for (unsigned i = 0; i != N; ++i) buf[i] = s[i];
//		}
//		constexpr operator char const*() const { return buf; }
//	};
//	template<unsigned N> FixedString(char const (&)[N]) -> FixedString<N - 1>;

//	template<class MyString = typestring_is("Hello!")>

	// TODO: Implement copy/move/assignment constructor
//	char sErrorSource[] = "Undefined";
//	template <typename T, char *T_ErrorSource="Undefined">
//	template <typename T, FixedString S>
	template <typename T>
	class t_VectorMap {
		private:
			std::string sErrorSource;
			std::vector<T> typeList;
			Map_si map;

		public:
//			t_VectorMap(std::string source) {
			t_VectorMap() {
				sErrorSource = "Undefined";
			}
			t_VectorMap(std::string source) {
				sErrorSource = source;
			}
			virtual ~t_VectorMap() {}

			bool checkName(std::string name, bool bThrow=true) {
				if(map.count(name)>0) return true;
				else {
					if (bThrow) throw std::runtime_error("["+std::string(sErrorSource)+"] Invalid Item Name: '"+name+"'");
					else return false;
				}
			}

			bool checkID(int id, bool bThrow=true) {
				if(id >= 0 && id < typeList.size()) return true;
				else {
					if (bThrow) throw std::runtime_error("["+std::string(sErrorSource)+"] Invalid ID: '"+std::to_string(id)+"'");
					else return false;
				}
			}

			virtual T & operator[](std::string name)	{
				checkName(name);
				return typeList[map[name]];
			}

			virtual T & operator[](int id)	{
				checkID(id);
				return typeList[id];
			}

			virtual void setSource(std::string source) {
				sErrorSource = source;
			}

//			int	operator()(std::string name) {
//				checkName(name);
//				return groups[map[name]].index;
//			}
//
//			int	operator()(int id) {
//				checkID(id);
//				return groups[id].index;
//			}

			virtual T & add(std::string name, T t, bool bThrow=true) {
				if(!checkName(name, false)) {
					//typeList.emplace_back(t);
					typeList.push_back(t);
					int id = typeList.size() - 1;
					map.insert(make_pair(name, id));
					return typeList[map[name]];
				}
				else {
					if(bThrow) throw std::runtime_error("Duplicate name in t_Vector: '"+name+"'");
					else return typeList[map[name]];
				}

			}

			virtual void remove(std::string name, bool bThrow=true) {
				if(checkName(name, false)) {
					typeList.erase(typeList.begin() + map[name]);
					map.erase(name);
				}
				else {
					if(bThrow) throw std::runtime_error("Name in t_Vector doesn't exist: '"+name+"'");
				}

			}

			virtual T & get(std::string name)	{
				checkName(name);
				return typeList[map[name]];
			}

			virtual T & get(int id)	{
				checkID(id);
				return typeList[id];
			}

			int getID(std::string name) {
				return map[name];
			}

			std::string getName(int id) {
				for (const auto& item : map) {
					if(item.second == id) return item.first;
				}
				return "";
			}

			int size() {
				return typeList.size();
			}

			/*
			 * Allow Iteration
			 *
			 * Example:
			 * 	t_Vector<T> items;
			 * 	for(auto item : items) {}
			 */
			typedef T* iterator;
			typedef const T* const_iterator;
			iterator begin() 		{ return &typeList[0]; }
			iterator end() 			{ return &typeList[typeList.size()]; }
			const_iterator begin() 	const	{ return &typeList[0]; }
			const_iterator end() 	const	{ return &typeList[typeList.size()]; }
	};

	typedef std::pair<std::string, Core::t_BIFS> t_ComboBoxItem;
	typedef std::vector<t_ComboBoxItem> t_ComboBoxItems;

	/**
	 * \brief Allows an object to return multiple different states
	 *
	 * @tparam T
	 */
	class t_DataSet {
		public:
			t_VectorMap< std::vector<t_BIFS>> states;
			t_DataSet() {}

			std::vector<t_BIFS> & operator[](std::string name)	{ return states[name]; }
			std::vector<t_BIFS> & operator[](int n)	{ return states[n]; }

			/**
			 * @brief Create a new group but do not add any values to it
			 *
			 * @param name Name of the group
			 */
			void addGroup(std::string name) {
				std::vector<t_BIFS> base;
				states.add(name, base);
			}

			/**
			 * @brief Create a group name or use the existing one with the given name and add a value at the next index.
			 * 		  The index cannot be chosen, so group items with a pattern to the index values must be constructed
			 * 		  in the same order.
			 *
			 * @param name The name of the group to create or use if already existing
			 * @param value The variant value to add to the group
			 */
			void addGroupState(std::string name, t_BIFS value) {
				std::vector<t_BIFS> base;
				states.add(name, base, false);	// Do not throw error, just continue...
				states[name].push_back(value);	//  and add element to existing group
			}

			/**
			 * @brief Create a group name or use the existing one with the given name and add a list of values starting
			 * 		  at the next available index.
			 * 		  The index cannot be chosen, so group items with a pattern to the index values must be constructed
			 * 		  in the same order.
			 *
			 * @param name The name of the group to create or use if already existing
			 * @param base A vector of variants to add to the group
			 */
			void addGroupStates(std::string name, std::vector<t_BIFS> base) { states.add(name, base); }
			void addState(std::string name, t_BIFS value) { states[name].push_back(value); }

			// Constructors/Operators
			t_DataSet(const t_DataSet &other) {
				states = other.states;
			}

			t_DataSet(t_DataSet &&other) {
				states = other.states;
//				for(auto items : other) {
//					for(auto item : items) {
//						item
//					}
//				}
			}

			t_DataSet& operator=(const t_DataSet &other) {
				states = other.states;
				return *this;
			}

			t_DataSet& operator=(t_DataSet &&other) {
				states = other.states;
				return *this;
			}

			// Allow iteration using
			// for(auto item : items) {}
			typedef std::vector<t_BIFS>* iterator;
			iterator begin() 		{ return &states[0]; }
			iterator end() 			{ return &states[states.size()]; }
//			typedef const std::vector<t_BIFS>* const_iterator;
//			const_iterator begin() 	const	{ return &states[0]; }
//			const_iterator end() 	const	{ return &states[states.size()]; }
	};




















































	//	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=  settings.h   =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	//	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	//	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	//	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	//	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl << endl;
	//
	//	Vector2i v1 = Vector2i(5, 10);	cout << "v1: "			<< v1.x		<< ", "	<< v1.y		<< endl;
	//	Vector2i v2 = Vector2i(2, 3);	cout << "v2: "			<< v2.x		<< ", "	<< v2.y		<< endl;
	//	Vector2i v3 = v1 + v2;			cout << "Add: "			<< v3.x		<< ", "	<< v3.y		<< endl;
	//	Vector2i v4 = v1 - v2;			cout << "Subtract: "	<< v4.x		<< ", "	<< v4.y		<< endl;
	//	Vector2i v5 = v1 * v2;			cout << "Multiply: "	<< v5.x		<< ", "	<< v5.y		<< endl;
	//	Vector2i v6 = v1 / v2;			cout << "Divide: "		<< v6.x		<< ", "	<< v6.y		<< endl;
	//	Vector2i v10;	v10 = v1;		cout << "Assign v1: "	<< v10.x	<< ", "	<< v10.y	<< endl;
	//
	//	//float fLength = v3.length();
	//	//cout << "v3 length: " << fLength << endl << endl;
	//	cout << endl;
	//
	//	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	//	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	//	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	//	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	//	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
}
#endif /* SRC_HEADERS_CORE_TYPES_H_ */
