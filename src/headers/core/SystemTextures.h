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
				TEX_BOULDER,
				TEX_CLIFF1,
				TEX_CLIFF2,
				TEX_DIRT1,
				TEX_DIRT2,
				TEX_GRASS1,
				TEX_GRASS2,
				TEX_MUD1,
				TEX_MUD2,
				TEX_ROCK,
				TEX_ROCKY_DIRT,
				TEX_ROCKY_GRASS,
				TEX_ROCKY1,
				TEX_ROCKY2,
				TEX_SNOW1,
				TEX_SNOW2,
				TEX_BEACH1,
				TEX_BEACH2,
				TEX_SAND1,
				TEX_SAND2,
				TEX_LAST
				};

			bool load();
			bool calc();
//			void set(uint id);
//			void set(std::string s);
			void set(eTexList e);
			Texture& get();

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
