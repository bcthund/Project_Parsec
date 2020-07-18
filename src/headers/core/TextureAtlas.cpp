/*
 * TextureAtlas.cpp
 *
 *  Created on: Dec 2, 2019
 *      Author: bcthund
 */

#include "TextureAtlas.h"

namespace Core {

	_TextureAtlas::_TextureAtlas() {
		iSize = 1;
		iSize = 1;
		maxIndex = 1;
		bEnable = false;
	}

	_TextureAtlas::~_TextureAtlas() {
	}

	void _TextureAtlas::SetSize(int s) {
		iSize = s;
		maxIndex = s * s;
		bEnable = true;
	}

	Vector2f _TextureAtlas::GetCoords(int index) {
		Vector2f c;

		/*
		 * Return texture coordinates for given atlas index
		 *
		 *   (C[0], C[1]) -> (x,y)
		 *               +------+
		 *               |      |
		 *               |      |
		 *               |      |
		 *               +------+ (C[2], C[3]) -> (x,y)
		 */

		int column = index%iSize;
		int row = index/iSize;
		c.x = column/(float)iSize;
		c.y = row/(float)iSize;

		//std::cout << "Col = " << column << ", Row = " << row << "(" << c.x << ", " << c.y << ") : " << "[" << iCols << ", " << iRows << "]" << std::endl;

		return c;
	}

	int _TextureAtlas::Width() {
		return iSize;
	}

	int _TextureAtlas::Height() {
		return iSize;
	}

} /* namespace Core */
