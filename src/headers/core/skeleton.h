/*
 * skeleton.h
 *
 *  Created on: Dec 21, 2018
 *      Author: bcthund
 */

#ifndef HEADERS_CORE_SKELETON_H_
#define HEADERS_CORE_SKELETON_H_

#include <vector>
//#include "../gl4/glcorearb.h"
//#include "core_functions.h"
//#include "texture.h"
//#include "matrix.h"
//#include "shader.h"
//#include "helper.h"
//#include "bounding_volume.h"
//#include "vao.h"
//#include "../gamesys/O3D.h"
//#include "types.h"
#include "joint.h"

namespace Core {

	class _Skeleton {
		public:
			_Skeleton();
			virtual ~_Skeleton();
			std::vector<_Joint>		children;
	};

} /* namespace Core */

#endif /* HEADERS_CORE_SKELETON_H_ */
