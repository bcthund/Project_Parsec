/*
 * Scissor.h
 *
 *  Created on: Aug 1, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_CORE_SCISSOR_H_
#define HEADERS_CORE_SCISSOR_H_

#include "core_functions.h"
#include "types.h"
#include "gmath.h"
#define GL_GLEXT_PROTOTYPES 1		// Enable core profile
#include "gl4_5/glcorearb.h"

namespace Core {

//	typedef struct t_Scissor {
//		Vector2i first, second;
//
//		t_Scissor &make_pair(Vector2i f, Vector2i s) {
//			first = f;
//			second = s;
//			return *this;
//		}
//
//		Vector2i & operator[](int index)	{
//			switch (index) {
//				case 0: return first; break;
//				case 1: return second; break;
//				default: throw std::runtime_error("Invalid t_Scissor index: '"+std::to_string(index)+"'");
//			}
//		}
//
//		t_Scissor() {
//			first = 0;
//			second = 0;
//		}
//
//		t_Scissor(Vector2i f, Vector2i s) {
//			first = f;
//			second = s;
//		}
//
//		t_Scissor(int x, int y, int w, int h) {
//			first = Vector2i(x, y);
//			second = Vector2i(w, h);
//		}
//	} t_Scissor;

	class c_Scissor {
	public:
//		typedef struct t_Scissor {
//			Vector2i first, second;
//
//			t_Scissor &make_pair(Vector2i f, Vector2i s) {
//				first = f;
//				second = s;
//				return *this;
//			}
//
//			Vector2i & operator[](int index)	{
//				switch (index) {
//					case 0: return first; break;
//					case 1: return second; break;
//					default: throw std::runtime_error("Invalid t_Scissor index: '"+std::to_string(index)+"'");
//				}
//			}
//
//			t_Scissor() {
//				first = 0;
//				second = 0;
//			}
//
//			t_Scissor(Vector2i f, Vector2i s) {
//				first = f;
//				second = s;
//			}
//
//			t_Scissor(int x, int y, int w, int h) {
//				Vector2i xy = Vector2i(x, y);
//				Vector2i wh = Vector2i(w, h);
//				first = xy;
//				second = wh;
//			}
//
//			t_Scissor &operator=(const t_Scissor &src) {
//				first = src.first;
//				second = src.second;
//				return *this;
//			}
//
//		} t_Scissor;

		typedef struct t_Scissor {
			int x, y, w, h;		///< Coordinates and size of scissor area (bottom-left origin)
			bool bActive;		///< Is the stack item active. Can be set by external logic for additional use of data (ie. mouse in area)
			 t_DataSet data;	///< Extra data for stack

			t_Scissor() {
				data.addGroupState("Scrolling", false);
				x = 0;
				y = 0;
				w = 0;
				h = 0;
				bActive = true;
			}

			t_Scissor(int iX, int iY, int iW, int iH, bool bScrolling=false) {
				x = iX;
				y = iY;
				w = iW;
				h = iH;
				bActive = true;
			}

			t_Scissor& operator=(const t_Scissor &src) {
				data = src.data;
				bActive = src.bActive;
				x = src.x;
				y = src.y;
				w = src.w;
				h = src.h;
				return *this;
			}

		} t_Scissor;

		c_Scissor();
		virtual ~c_Scissor();
		c_Scissor(const c_Scissor &other);
		c_Scissor(c_Scissor &&other);
		c_Scissor& operator=(const c_Scissor &other);
		c_Scissor& operator=(c_Scissor &&other);

		bool bEnabled;
		const int MAX_STACK = 1000;
		//typedef std::pair<Vector2i, Vector2i> t_Scissor;
//		typedef Vector4i t_Scissor;
		t_Vector1T<t_Scissor> stack;

		void checkStack(bool bMin=true, bool bMax=true);
		bool enabled();
		void push(int x, int y, int w, int h, bool b_enable=true);			///< Push scissor coords to stack
		//void push(Vector2i v_pos, Vector2i v_size, bool b_enable=true);		///< Push scissor coords to stack
		//void push(t_Scissor pair, bool b_enable=true);						///< Push scissor coords to stack
		void pop(bool b_disable=false);										///< Pop scissor coords from stack
		void enable();														///< Execute the current stack
		void disable();														///< Disable glScissor (do not change stack)
		t_Scissor & get();													///< Get scissor coords from top of stack
		void setActive(bool b);												///< Set the current stack bActive state
		bool getActive();													///< Get the current stack bActive state
		bool checkInput(int x, int y, const Vector2f &res);										///< Set the current stack bActive state according to input coords (ie. mouse hover)

		typedef t_Scissor* iterator;
		typedef const t_Scissor* const_iterator;
		iterator begin() 		{ return &stack[0]; }
		iterator end() 			{ return &stack[stack.size()]; }
		//const_iterator begin() 	const	{ return &stack[0]; }
		//const_iterator end() 	const	{ return &stack[stack.size()]; }
	};

} /* namespace Core */

#endif /* HEADERS_CORE_SCISSOR_H_ */
