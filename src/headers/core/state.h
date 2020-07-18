/*
 * state.h
 *
 *  Created on: Aug 29, 2019
 *      Author: bcthund
 */

#ifndef HEADERS_CORE_STATE_H_
#define HEADERS_CORE_STATE_H_

#include "SDL2/SDL.h"
#include "types.h"
//#include "core_functions.h"

namespace Core {
	class _State {
		public:
			_State();
			~_State();

			float fWorldScale;
			float fGravity;

		private:

	};
}


#endif /* HEADERS_CORE_STATE_H_ */
