/*
 * Scissor.h
 *
 *  Created on: Aug 1, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_CORE_SCISSOR_H_
#define HEADERS_CORE_SCISSOR_H_

//#include "core_functions.h"
#include "types.h"
#define GL_GLEXT_PROTOTYPES 1		// Enable core profile
#include "gl4_5/glcorearb.h"

namespace Core {

	class c_Scissor {
	public:
		c_Scissor();
		virtual ~c_Scissor();
		c_Scissor(const c_Scissor &other);
		c_Scissor(c_Scissor &&other);
		c_Scissor& operator=(const c_Scissor &other);
		c_Scissor& operator=(c_Scissor &&other);

		const int MAX_STACK = 1000;
		typedef std::pair<Vector2i, Vector2i> t_Scissor;
		t_Vector1T<t_Scissor> stack;

		void push(int x, int y, int w, int h, bool b_enable=true);			///< Push scissor coords to stack
		void push(Vector2i v_pos, Vector2i v_size, bool b_enable=true);		///< Push scissor coords to stack
		void push(t_Scissor pair, bool b_enable=true);						///< Push scissor coords to stack
		void pop(bool b_disable=false);										///< Pop scissor coords from stack
		void enable();														///< Execute the current stack
		void disable();														///< Disable glScissor (do not change stack)
		t_Scissor get();													///< Get scissor coords from top of stack

		typedef t_Scissor* iterator;
		typedef const t_Scissor* const_iterator;
		iterator begin() 		{ return &stack[0]; }
		iterator end() 			{ return &stack[stack.size()]; }
		//const_iterator begin() 	const	{ return &stack[0]; }
		//const_iterator end() 	const	{ return &stack[stack.size()]; }
	};

} /* namespace Core */

#endif /* HEADERS_CORE_SCISSOR_H_ */
