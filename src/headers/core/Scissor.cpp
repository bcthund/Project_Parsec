/*
 * Scissor.cpp
 *
 *  Created on: Aug 1, 2020
 *      Author: bcthund
 */

#include <core/Scissor.h>

namespace Core {

	c_Scissor::c_Scissor() { bEnabled = false; }
	c_Scissor::~c_Scissor() {}

	//c_Scissor::c_Scissor(const c_Scissor &other) {
	//	// TODO Auto-generated constructor stub
	//}

	c_Scissor::c_Scissor(c_Scissor &&other) {
		bEnabled = other.bEnabled;
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
		bEnabled = other.bEnabled;
		for (auto & item : other) {
			stack.add(item);
		}
		return *this;
	}

	void c_Scissor::checkStack(bool bMin, bool bMax) {
		if(bMin && stack.size()<=0) throw std::runtime_error("glScissor call made on empty stack");
		if(bMax && stack.size()>=MAX_STACK) throw std::runtime_error("Scissor stack overflow (stack>"+std::to_string(MAX_STACK)+"), are you missing a call to pop()?");
	}

	bool c_Scissor::enabled() {
		return bEnabled;
	}

	void c_Scissor::push(int x, int y, int w, int h, bool b_enable) {
		checkStack(false, true);
		t_Scissor tmp = { x, y, w, h };
		stack.add(tmp);
		if(b_enable) enable();
	}

//	void c_Scissor::push(Vector2i v_pos, Vector2i v_size, bool b_enable) {
////		t_Scissor tmp = { v_pos, v_size };
////		push(tmp, b_enable);
//		//push(t_Scissor(v_pos, v_size), b_enable);
//		//push(std::make_pair(v_pos, v_size), b_enable);
//		push(t_Scissor(v_pos, v_size), b_enable);
//	}

//	void c_Scissor::push(t_Scissor pair, bool b_enable) {
//		if(stack.size()<MAX_STACK) {
//			stack.add(pair);
//			if(b_enable) enable();
//		}
//		else throw std::runtime_error("Scissor stack overflow (stack>"+std::to_string(MAX_STACK)+"), are you missing a call to pop()?");
//	}

	void c_Scissor::pop(bool b_disable) {
		checkStack();
		stack.remove(stack.size()-1);

		if(b_disable) disable();
	}

	c_Scissor::t_Scissor & c_Scissor::get() {
		checkStack();
		return stack[stack.size()-1];
	}

	void c_Scissor::setActive(bool b) {
		checkStack();
		stack[stack.size()-1].bActive = b;
	}

	bool c_Scissor::getActive() {
		checkStack();
		return stack[stack.size()-1].bActive;
	}

	bool c_Scissor::checkInput(int x, int y, const Vector2f &res) {
		checkStack();

		Vector2f vMouse = { float(x), float(y) };
		Vector2f vP1 = { (float)stack[stack.size()-1].x, res.y-((float)stack[stack.size()-1].y+(float)stack[stack.size()-1].h) };
		Vector2f vP2 = { (float)stack[stack.size()-1].x+(float)stack[stack.size()-1].w, res.y-(float)stack[stack.size()-1].y };

		if (Core::gmath.PointQuad2d(vMouse, vP1, vP2)) stack[stack.size()-1].bActive = true;
		else stack[stack.size()-1].bActive = false;

		return stack[stack.size()-1].bActive;
	}

	void c_Scissor::enable() {
		checkStack();
		glScissor(stack[stack.size()-1].x, stack[stack.size()-1].y, stack[stack.size()-1].w, stack[stack.size()-1].h);
		glEnable(GL_SCISSOR_TEST);
		bEnabled = true;
	}

	void c_Scissor::disable() {
		glDisable(GL_SCISSOR_TEST);
		bEnabled = false;
	}

} /* namespace Core */
