/*
 * Path.h
 *
 *  Created on: Dec 19, 2018
 *      Author: bcthund
 *
 *  Description: For created and managing interpolated paths. This can be used
 *  			 for things such as object animations and will return data
 *  			 specific to the current timeframe. The path can include things
 *  			 such as rotations.
 */

#ifndef HEADERS_CORE_PATH_H_
#define HEADERS_CORE_PATH_H_

#include <vector>
//#include "../gl4/glcorearb.h"
#include "core_functions.h"
//#include "matrix.h"
//#include "shader.h"

namespace Core {

	class _PathLinear {
		public:
			float startTime;		// The time path animation was started
			float finishTime;		// The desired end time for path animation
			Vector3f start;			// The starting location
			Vector3f finish;		// The finish location
	};

	class _PathArc : _PathLinear {
		public:
			Vector3f center;			// The intermediate location
	};

//	class _PathCircular : _PathArc {
//		public:
//			Vector3f radius;			// The
//	};

	class _Path {
		public:
			_Path();
			virtual ~_Path();
			std::vector<_PathLinear>	linear;
			std::vector<_PathArc>		arc;
//			std::vector<_PathCircular>	circular;
	};

} /* namespace Core */

#endif /* HEADERS_CORE_PATH_H_ */
