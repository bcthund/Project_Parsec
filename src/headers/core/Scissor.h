/*
 * Scissor.h
 *
 *  Created on: Aug 1, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_CORE_SCISSOR_H_
#define HEADERS_CORE_SCISSOR_H_

#include "types.h"
//#include "core_functions.h"

namespace Core {

	class c_Scissor {
	public:
		c_Scissor();
		virtual ~c_Scissor();
//		c_Scissor(const c_Scissor &other);
//		c_Scissor(c_Scissor &&other);
//		c_Scissor& operator=(const c_Scissor &other);
//		c_Scissor& operator=(c_Scissor &&other);

		typedef std::pair<Vector2i, Vector2i> t_Scissor;
		t_Vector1T<t_Scissor> stack;

		void push(int x, int y, int w, int h);			///< Push scissor coords to stack
		void push(Vector2i v_pos, Vector2i v_size);		///< Push scissor coords to stack
		void push(t_Scissor pair);						///< Push scissor coords to stack
		void pop();										///< Pop scissor coords from stack
		t_Scissor get();								///< Get scissor coords from top of stack
	};

} /* namespace Core */

#endif /* HEADERS_CORE_SCISSOR_H_ */
