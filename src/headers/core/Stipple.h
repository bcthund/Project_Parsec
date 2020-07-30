/*
 * Stipple.h
 *
 *  Created on: Apr 20, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_CORE_STIPPLE_H_
#define HEADERS_CORE_STIPPLE_H_

#include "core_functions.h"
#include "Colors.h"

namespace Core {

	const int MAX_STIPPLE = 256;

	struct Stipple_Pattern {
		std::string name;					///< Name of this stipple pattern for reference
		Vector2i 	size;					///< The size of the stipple pattern, maximum of 256 total points
		int 		pattern[MAX_STIPPLE];	///< Stipple pattern defined by 1 or 0

		Stipple_Pattern() {
			name = "";
			size = 0;
		}

		Stipple_Pattern(std::string name, Vector2i size, int pattern[]) {
			this->name = name;
			this->size = size;

			int iSize = std::min(size.x*size.y, MAX_STIPPLE);
			for(int i=0; i<iSize; i++) this->pattern[i] = pattern[i];

			if(iSize<MAX_STIPPLE) {
				for(int i=iSize; i<MAX_STIPPLE; i++) this->pattern[i] = 0;
			}
		}

		virtual ~Stipple_Pattern() {
		}
	};

	class Stipple {
		public:
			// FIXME: Put in struct and setup () operator overload for access
			static const std::string STIPPLE_NONE;
			static const std::string STIPPLE_ANSI31;
			static const std::string STIPPLE_ANGLE_THICK;
			static const std::string STIPPLE_ANGLE;
			static const std::string STIPPLE_BLOCKS;
			static const std::string STIPPLE_CHECKERBOARD;
			static const std::string STIPPLE_SAND;
			static const std::string STIPPLE_INSULATION;
			static const std::string STIPPLE_BOARD;
			static const std::string STIPPLE_ZIGZAG;
			static const std::string STIPPLE_WATER;
			static const std::string STIPPLE_GRASS;
			static const std::string STIPPLE_CHECKER;
			static const std::string STIPPLE_OCTAGONS;
			static const std::string STIPPLE_WAFFLE;
			static const std::string STIPPLE_PLUSSES;
			static const std::string STIPPLE_SHAKES;
			static const std::string STIPPLE_EARTH;
			static const std::string STIPPLE_HERRING;
			static const std::string STIPPLE_DOTS;
			static const std::string STIPPLE_GROUT;
			static const std::string STIPPLE_CROSSES;
			static const std::string STIPPLE_TILEPAT1;
			static const std::string STIPPLE_WOOD;
			static const std::string STIPPLE_GRADIENT_V;
			static const std::string STIPPLE_GRADIENT_H;
			static const std::string STIPPLE_SHADE_125;
			static const std::string STIPPLE_SHADE_25;
			static const std::string STIPPLE_SHADE_50;
			static const std::string STIPPLE_SHADE_75;
			static const std::string STIPPLE_SHINGLE;
			static const std::string STIPPLE_TILE_OFFSET;
			static const std::string STIPPLE_FENCE;

			static const std::string STIPPLE_SHALE;
			static const std::string STIPPLE_SANDSTONE;
			static const std::string STIPPLE_SLOT;
			static const std::string STIPPLE_LIMESTONE;
			static const std::string STIPPLE_SALT;
			static const std::string STIPPLE_PUMICE;

		private:
			std::vector<Stipple_Pattern> stipples;
			Map_si	  map;

		public:
			Stipple();
			virtual ~Stipple();
			void add(std::string name, Vector2i size, int pattern[]);
//			void setScale(std::string name, float *scale);
			void shiftUp(std::string name, int n=1);
			void shiftDown(std::string name, int n=1);
			void shiftLeft(std::string name, int n=1);
			void shiftRight(std::string name, int n=1);
			Stipple_Pattern * get(std::string name);
			Stipple_Pattern * get(int id);

//			Colors_Extended &operator()()				{	return this->Extended;	}
//			Stipple_Pattern &operator[](std::string name)		{	if(map.count(name)>0) return *colors[map[name]]; else throw std::runtime_error("Invalid Color: "+name);	}
			Stipple_Pattern &operator[](std::string name)		{	if(map.count(name)>0) return stipples[map[name]]; else throw std::runtime_error("Invalid Stipple Pattern Name: "+name);	}
			Stipple_Pattern &operator[](int id)					{	if(id<stipples.size()) return stipples[id]; else throw std::runtime_error("Invalid Stipple Pattern ID: "+id);	}
			//Stipple_Pattern &operator[](t_BIFS id)				{	if(id<stipples.size()) return stipples[id]; else throw std::runtime_error("Invalid Stipple Pattern ID: "+id);	}
//			Stipple_Pattern *operator[](std::string name)		{	if(map.count(name)>0) return &stipples[map[name]]; else throw std::runtime_error("Invalid Stipple Pattern: "+name);	}

	};

} /* namespace Core */

#endif /* HEADERS_CORE_STIPPLE_H_ */
























































