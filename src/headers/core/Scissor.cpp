/*
 * Scissor.cpp
 *
 *  Created on: Aug 1, 2020
 *      Author: bcthund
 */

#include <core/Scissor.h>

namespace Core {

	c_Scissor::c_Scissor() {}
	c_Scissor::~c_Scissor() {}

	//c_Scissor::c_Scissor(const c_Scissor &other) {
	//	// TODO Auto-generated constructor stub
	//}

	c_Scissor::c_Scissor(c_Scissor &&other) {
		for (auto & item : other) {
			stack.add(item);
		}
	}

	//c_Scissor& c_Scissor::operator=(const c_Scissor &other) {
	//	for (auto & item : other) {
	//		stack.add(item);
	//	}
	//	return *this;
	//}

	c_Scissor& c_Scissor::operator=(c_Scissor &&other) {
		for (auto & item : other) {
			stack.add(item);
		}
		return *this;
	}

	void c_Scissor::push(int x, int y, int w, int h, bool b_enable) {
//		t_Scissor tmp = std::make_pair(Vector2i(x, y), Vector2i(w, h));
//		push(tmp, b_enable);
		push(std::make_pair(Vector2i(x, y), Vector2i(w, h)), b_enable);
	}

	void c_Scissor::push(Vector2i v_pos, Vector2i v_size, bool b_enable) {
		push(std::make_pair(v_pos, v_size), b_enable);
	}

	void c_Scissor::push(t_Scissor pair, bool b_enable) {
		if(stack.size()<MAX_STACK) {
			stack.add(pair);
			if(b_enable) enable();
		}
		else throw std::runtime_error("Scissor stack overflow (stack>"+std::to_string(MAX_STACK)+"), are you missing a call to pop()?");
	}

	void c_Scissor::pop(bool b_disable) {
		if(stack.size()>0) stack.remove(stack.size()-1);
		else throw std::runtime_error("Scissor stack underflow, you called pop() more than push()");

		if(b_disable) disable();
	}

	c_Scissor::t_Scissor c_Scissor::get() {
		if(stack.size()>0) return stack[stack.size()-1];
		else throw std::runtime_error("get() requested on an empty scissor stack.");
	}

	void c_Scissor::enable() {
		if(stack.size()>0) {
			glScissor(stack[stack.size()-1].first.x, stack[stack.size()-1].first.y, stack[stack.size()-1].second.x, stack[stack.size()-1].second.y);
			glEnable(GL_SCISSOR_TEST);
		}
		else throw std::runtime_error("glScissor enable() requested on empty stack");
	}

	void c_Scissor::disable() {
		glDisable(GL_SCISSOR_TEST);
	}

} /* namespace Core */
