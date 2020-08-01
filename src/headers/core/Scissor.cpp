/*
 * Scissor.cpp
 *
 *  Created on: Aug 1, 2020
 *      Author: bcthund
 */

#include <core/Scissor.h>

namespace Core {

	c_Scissor::c_Scissor() {
		// TODO Auto-generated constructor stub

	}

	c_Scissor::~c_Scissor() {
		// TODO Auto-generated destructor stub
	}

//	c_Scissor::c_Scissor(const c_Scissor &other) {
//		// TODO Auto-generated constructor stub
//
//	}
//
//	c_Scissor::c_Scissor(c_Scissor &&other) {
//		// TODO Auto-generated constructor stub
//
//	}
//
//	c_Scissor& c_Scissor::operator=(const c_Scissor &other) {
//		// TODO Auto-generated method stub
//		return *this;
//	}
//
//	c_Scissor& c_Scissor::operator=(c_Scissor &&other) {
//		// TODO Auto-generated method stub
//		return *this;
//	}

	void c_Scissor::push(int x, int y, int w, int h) {
		push(std::make_pair(Vector2i(x, y), Vector2i(w, h)));
	}

	void c_Scissor::push(Vector2i v_pos, Vector2i v_size) {
		push(std::make_pair(v_pos, v_size));
	}

	void c_Scissor::push(t_Scissor pair) {
		//stack.add(
	}

	void c_Scissor::pop() {
	}

	c_Scissor::t_Scissor c_Scissor::get() {
	}


} /* namespace Core */
