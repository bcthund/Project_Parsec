/*
 * SystemTextures.h
 *
 *  Created on: Sep 6, 2019
 *      Author: bcthund
 */

#ifndef HEADERS_CORE_SYSTEMTEXTURES_H_
#define HEADERS_CORE_SYSTEMTEXTURES_H_

#include <cstdlib>
#include <iostream>
#include "texture.h"
#include "core_functions.h"

namespace Core {

	class _SystemTextures {
		public:
			_SystemTextures();
			virtual ~_SystemTextures();

			enum eTexList {
				TEX_TESTPATTERN = 0,
				TEX_WATER,
				TEX_DIRT,
				TEX_GRASSYDIRT,
				TEX_GRASS,
				TEX_GRASSYROCK,
				TEX_ROCK,
				TEX_CLIFF,
				TEX_LAST
				};

			bool load();
			bool calc();
//			void set(uint id);
//			void set(std::string s);
			void set(eTexList e);

		private:
			Texture		texture;
			uint		uiNumTextures;
			uint		uiRecordSize;
			std::string sFilename;
			std::string sDir;
			std::string sTexDir;
	};

} /* namespace Core */

#endif /* HEADERS_CORE_SYSTEMTEXTURES_H_ */
