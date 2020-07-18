/*
 * TextureAtlas.h
 *
 *  Created on: Dec 2, 2019
 *      Author: bcthund
 */

#ifndef HEADERS_CORE_TEXTUREATLAS_H_
#define HEADERS_CORE_TEXTUREATLAS_H_

#include "types.h"

namespace Core {
	class _TextureAtlas {
		private:

		public:
			_TextureAtlas();
			virtual ~_TextureAtlas();

			bool bEnable;
			int iSize;		// Square atlas only, keep it simple
			int maxIndex;
			void SetSize(int s);
			int Width();
			int Height();
			int Count() { return iSize*iSize; }

			Vector2f GetCoords(int index);
	};

} /* namespace Core */

#endif /* HEADERS_CORE_TEXTUREATLAS_H_ */
