/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_FIELD_H_
#define HEADERS_GAMESYS_GUI_FIELD_H_

#include <iostream>
//#include "../core/core_functions.h"
//#include "../core/vao.h"
//#include "../core/matrix.h"
//#include "../core/shader.h"
//#include "../../core/InputSys.h"
#include "../../core/Colors.h"
#include "../../gamesys/gameVars.h"
#include "GUI_Constraint.h"
#include "GUI_ToolTip.h"
#include "GUI_Window.h"

namespace Core {
	namespace GUI {
		namespace Object {
			class FieldBase {
				public:
					static Core::_Keyboard keyboard;	//
//					static bool bFocusPresent;			// True if ANY slider has focus, only one can have focus at a time
					static bool bKeyboardInit;

					FieldBase() {
						if(!bKeyboardInit) {
							keyboard.calc(Core::_Keyboard::KEYTYPE_ONESHOT);
							bKeyboardInit = true;
						}
					}
			};
			Core::_Keyboard FieldBase::keyboard	= Core::_Keyboard();
//			bool FieldBase::bFocusPresent		= false;
			bool FieldBase::bKeyboardInit		= false;

			template <class T>
//			class Field : public FieldBase, public Base::Interactive<Props_Field, T> {
			class Field : public FieldBase, public Base::Interactive<Props_Field> {
					friend class AnyField;
				public:
					Field();
					Field(std::string n, T *tPtr, Props_Field &c);
					Field(std::string n, T *tPtr, Props_Field *c);
					Field(Props &p, std::string n, T *tPtr, Props_Field &c);
					Field(Props &p, std::string n, T *tPtr, Props_Field *c);

					Field(std::string n, T t, Props_Field &c);
					Field(std::string n, T t, Props_Field *c);
					Field(Props &p, std::string n, T t, Props_Field &c);
					Field(Props &p, std::string n, T t, Props_Field *c);

					virtual ~Field();

					T *valuePtr;
					bool bLocalValue;
					void setValuePtr(T *ptr);
					T * getValuePtr();
					T getValue();

					ToolTip toolTip;
					void init();
					void exec(iState eExternState=STATE_NONE);
					void execToolTip();
					void updateNoFocus();	// Calls to run when object not visible/not in focus.

				private:
					Window win;					// Window object for background
					std::string sEditVar;
					bool bHasFocus;
					std::string lastValue;				///< Value at the last cycle, used to determine bValueChanged
					bool getFocus() {	return bHasFocus;	};
					void execEditStart();
					void execEditInput();
					void execEditInputGlobal();
					void updateObjectState(iState eExternState);
					std::string execEdit();
					void execEditSet();
			};

			template <class T> Field<T>::Field() {
				bHasFocus		= false;
				valuePtr		= nullptr;
				bLocalValue		= true;
			}

			template <class T> Field<T>::Field(std::string n, T *tPtr, Props_Field &c) {
				bHasFocus				= false;
				this->name				= n;

				this->bHasParent		= false;
				this->parent			= nullptr;

				this->bLocalState		= true;
				this->statePtr			= new bool(false);

				this->bLocalValue		= false;
				this->valuePtr			= tPtr;

				this->bLocalCon			= true;
				this->con				= new Props_Field();
				*this->con				= c;
				if(this->con->text == "") this->con->text = n;
			}

			template <class T> Field<T>::Field(std::string n, T *tPtr, Props_Field *c) {
				bHasFocus				= false;
				this->name				= n;

				this->bHasParent		= false;
				this->parent			= nullptr;

				this->bLocalState		= true;
				this->statePtr			= new bool(false);

				this->bLocalValue		= false;
				this->valuePtr			= tPtr;

				this->bLocalCon			= false;
				this->con				= c;
				if(this->con->text == "") this->con->text = n;
			}

			template <class T> Field<T>::Field(Props &p, std::string n, T *tPtr, Props_Field &c) {
				bHasFocus				= false;
				this->name				= n;

				this->bHasParent		= true;
				this->parent			= &p;

				this->bLocalState		= true;
				this->statePtr			= new bool(false);

				this->bLocalValue		= false;
				this->valuePtr			= tPtr;

				this->bLocalCon			= true;
				this->con				= new Props_Field();
				*this->con				= c;
				if(this->con->text == "") this->con->text = n;
			}

			template <class T> Field<T>::Field(Props &p, std::string n, T *tPtr, Props_Field *c) {
				bHasFocus				= false;
				this->name				= n;

				this->bHasParent		= true;
				this->parent			= &p;

				this->bLocalState		= true;
				this->statePtr			= new bool(false);

				this->bLocalValue		= false;
				this->valuePtr			= tPtr;

				this->bLocalCon			= false;
				this->con				= c;
				if(this->con->text == "") this->con->text = n;
			}

			template <class T> Field<T>::Field(std::string n, T t, Props_Field &c) {
				bHasFocus				= false;
				this->name				= n;

				this->bHasParent		= false;
				this->parent			= nullptr;

				this->bLocalState		= true;
				this->statePtr			= new bool(false);

				this->bLocalValue		= true;
				this->valuePtr			= new T(t);

				this->bLocalCon			= true;
				this->con				= new Props_Field();
				*this->con				= c;
				if(this->con->text == "") this->con->text = n;
			}

			template <class T> Field<T>::Field(std::string n, T t, Props_Field *c) {
				bHasFocus				= false;
				this->name				= n;

				this->bHasParent		= false;
				this->parent			= nullptr;

				this->bLocalState		= true;
				this->statePtr			= new bool(false);

				this->bLocalValue		= true;
				this->valuePtr			= new T(t);

				this->bLocalCon			= false;
				this->con				= c;
				if(this->con->text == "") this->con->text = n;
			}

			template <class T> Field<T>::Field(Props &p, std::string n, T t, Props_Field &c) {
				bHasFocus				= false;
				this->name				= n;

				this->bHasParent		= true;
				this->parent			= &p;

				this->bLocalState		= true;
				this->statePtr			= new bool(false);

				this->bLocalValue		= true;
				this->valuePtr			= new T(t);

				this->bLocalCon			= true;
				this->con				= new Props_Field();
				*this->con				= c;
				if(this->con->text == "") this->con->text = n;
			}

			template <class T> Field<T>::Field(Props &p, std::string n, T t, Props_Field *c) {
				bHasFocus				= false;
				this->name				= n;

				this->bHasParent		= true;
				this->parent			= &p;

				this->bLocalState		= true;
				this->statePtr			= new bool(false);

				this->bLocalValue		= true;
				this->valuePtr			= new T(t);

				this->bLocalCon			= false;
				this->con				= c;
				if(this->con->text == "") this->con->text = n;
			}

			template <class T> Field<T>::~Field() {
				if(this->bLocalCon && this->con != nullptr) delete this->con;
			}

			template <class T> void Field<T>::setValuePtr(T *ptr)	{
				if(bLocalValue && valuePtr != nullptr) delete valuePtr;
				bLocalValue = false;
				valuePtr = ptr;
			}

			template <class T> T * Field<T>::getValuePtr()	{
				return valuePtr;
			}

			template <class T> T Field<T>::getValue()	{
				return *valuePtr;
			}

			/*
			 * Initialize required data, create pointer
			 */
			template <class T> void Field<T>::init() {
				this->id = IDs.create();

				if (this->bHasParent) {
					this->con->scroll.bind(*this->parent);
					this->con->exec(*this->parent);
					win = Object::Window(*this->parent, this->name, this->con);
				}
				else {
					this->con->exec();
					win = Object::Window(this->name, this->con);
				}
				win.init();

				this->con->exec(*win.con);
				this->toolTip.init(*this->con, this->name);

				this->bInit = true;
			}

			/*
			 * Copy current value into edit buffer (numeric specialization)
			 */
			template <class T> void Field<T>::execEditStart() {
				std::stringstream stream;
				stream << std::fixed << std::setprecision(this->con->precision) << *this->valuePtr;
				sEditVar = stream.str();
			}

			/*
			 * Copy current value into edit buffer (string specialization)
			 */
			template <> void Field<std::string>::execEditStart() {
				sEditVar = *valuePtr;
			}

			template <class T> void Field<T>::execEditInputGlobal() {
				SDL_PumpEvents();
				keyboard.event = SDL_GetKeyboardState(NULL);
				keyboard.update();
				if (keyboard.keys[SDLK_ESCAPE].bActive) {
					bHasFocus = false;
					this->bFocusPresent = false;
					this->eObjectState = STATE_NONE;
				}
			}

			/*
			 * Numeric template specialization
			 */
			template <class T> void Field<T>::execEditInput() {

				execEditInputGlobal();

				// Prevent editing if max field size reached (field size in pixels, not characters)
				int lengthBuffer = ((sEditVar.length()+1)*Core::gameVars->font.vSize.x)+(this->con->vPadding.left+this->con->vPadding.right);
				if(lengthBuffer < this->con->size.constraint.xMax) keyboard.editBuffer(sEditVar, Core::_Keyboard::EDIT_WD|Core::_Keyboard::EDIT_NUMERIC);
				else keyboard.editBuffer(sEditVar, Core::_Keyboard::EDIT_DELETE|Core::_Keyboard::EDIT_NUMERIC);

				if (keyboard.keys[SDLK_RETURN].bActive || keyboard.keys[SDLK_KP_ENTER].bActive) {
					try {
						*this->valuePtr = fmax(fmin(std::stof(sEditVar), this->con->maxValue), this->con->minValue);
					}
					catch(...) {
						*this->valuePtr = 0.0f;
					}
					bHasFocus = false;
					this->bFocusPresent = false;
					this->eObjectState = STATE_NONE;
				}
			}

			/*
			 * String template specialization
			 */
			template <> void Field<std::string>::execEditInput() {

				execEditInputGlobal();

				keyboard.editBuffer(sEditVar, Core::_Keyboard::EDIT_WD);

				if (keyboard.keys[SDLK_RETURN].bActive || keyboard.keys[SDLK_KP_ENTER].bActive) {
					try {
						*valuePtr = sEditVar;
					}
					catch(...) {
						*valuePtr = "Error";
					}
					bHasFocus = false;
					bFocusPresent = false;
					eObjectState = STATE_NONE;
				}
			}

			/*
			 * Numeric template specialization
			 */
			template <class T> std::string Field<T>::execEdit() {
				if(bHasFocus && this->con->bEditable) {
					execEditInput();
					return sEditVar;
				}
				else {
					return to_string(*this->valuePtr, this->con->precision);
				}
			}

			/*
			 * String template specialization
			 */
			template <> std::string Field<std::string>::execEdit() {
				if(bHasFocus && this->con->bEditable) {
					execEditInput();
					return sEditVar;
				}
				else return *valuePtr;
			}

			template <class T> void Field<T>::updateObjectState(iState eExternState) {
				checkStatePtr();

				if(eExternState!=STATE_NONE && !(eExternState&STATE_UPDATE)) this->eObjectState = eExternState;
				else {

					if(!(eExternState&STATE_UPDATE)) {
						Vector2f vPos = this->con->getScrollPos();
						this->mState = Core::mouse->checkInput(gameVars->screen.half.x+vPos.x, gameVars->screen.half.y-vPos.y, this->con->size.x, this->con->size.y);
						//this->mState = Core::mouse->checkInput(gameVars->screen.half.x+this->con->pos.x, gameVars->screen.half.y-this->con->pos.y, this->con->size.x, this->con->size.y);
					}
					else this->mState = Core::_Mouse::MOUSE_NONE;

					if(this->enabled() && this->con->bEditable && !(eExternState&STATE_ACTIVE)) {
						if(!this->bFocusPresent && (this->mState&Core::_Mouse::MOUSE_LEFT)) {
							bHasFocus = true;
							this->bFocusPresent = true;
							this->sActiveObject = this->id;
							this->eObjectState = STATE_ACTIVE;

							execEditStart();
						}
						else if ( !(this->eObjectState&STATE_ACTIVE) || ((this->eObjectState&STATE_ACTIVE) && !this->bFocusPresent) ) {
							this->eObjectState = STATE_NONE;
							if(this->sActiveObject == this->id) this->sActiveObject = "";
						}
					}
					else this->eObjectState = STATE_NONE;
				}

				// Allow mouse hover at any time (used for tooltips)
				if(!(eExternState&STATE_UPDATE)) {
					if(this->mState&Core::_Mouse::MOUSE_HOVER) this->eObjectState = this->eObjectState|STATE_HOVER;
					else this->eObjectState = this->eObjectState&~STATE_HOVER;
				}

				// If mouse hover, then automatically set focus to suspend other objects (will suspend window scrolling)
				if(this->eObjectState&STATE_HOVER) {
					bScrollFocus	= true;
					sScrollObject	= id;
				}
				else if(sScrollObject == id) {
					bScrollFocus	= false;
					sScrollObject	= "";
				}

				if(!this->enabled()) this->eObjectState |= STATE_DISABLED;
				updateStatePtr();
			}

			/*
			 * Execute slider logic routine
			 */
			template <class T> void Field<T>::exec(iState eExternState) {
				if(this->bInit && this->con->visibility && ((this->parent!=nullptr && this->parent->visibility) || (this->parent==nullptr))) {

					std::string vBuffer = execEdit();

					if(this->con->size.isAutoSet()) {
						// Update constraints
						if(this->bHasParent) this->con->exec(*this->parent);
						else this->con->exec();

						if((con->bFocusLock && !bFocusPresent) || !con->bFocusLock || (sActiveObject==id)) {
							updateObjectState(eExternState);

							if(this->con->toolTip.bShow) this->toolTip.updateObjectState(this->eObjectState);
							else this->toolTip.updateObjectState(STATE_NONE);
						}

						// Draw button window
						win.exec(this->eObjectState);

						// Check if value has changed FIXME: This should be in Interactive class in a function somehow
						if(lastValue != vBuffer) this->bStateChanged = true;
						lastValue = vBuffer;

						// Draw button text
						if((this->eObjectState&STATE_HOVER) && !bHasFocus)	colors.PushFront(*this->con->colorText.highlight);
						else if(this->eObjectState&STATE_ACTIVE)			colors.PushFront(*this->con->colorText.active);
						else												colors.PushFront(*this->con->colorText.base);

						textSys->draw(this->con, vBuffer, CONSTRAIN_CENTER);
						colors.PopFront();
					}
					else {
						textSys->draw(this->con, vBuffer, CONSTRAIN_CENTER);
					}

					// Autosize
					if(this->con->size.constraint.xAuto) {
//						int maxSize = (vBuffer.length()*Core::gameVars->font.vSize.x)+(this->con->vPadding.left+this->con->vPadding.right);
						int lengthBuffer = (vBuffer.length()*Core::gameVars->font.vSize.x)+(this->con->vPadding.left+this->con->vPadding.right);
						int maxSize = std::max(this->con->size.constraint.xMin, std::min(this->con->size.constraint.xMax , lengthBuffer ) );
						this->con->setWidth(maxSize, GUI::SIZE_CONSTRAINT_ABSOLUTE);
					}
					if(this->con->size.constraint.yAuto) this->con->setHeight(Core::gameVars->font.vSize.y+(this->con->vPadding.top+this->con->vPadding.bottom), GUI::SIZE_CONSTRAINT_ABSOLUTE);
					if(this->con->size.constraint.xAuto || this->con->size.constraint.yAuto) this->con->exec();

				}
			}

			template <class T> void Field<T>::execToolTip() {
				toolTip.exec();
			}

			/***
			 * \brief Calls to run when object not visible/not in focus.
			 * @tparam T
			 * @tparam T
			 */
			template <class T> void Field<T>::updateNoFocus() {
				if(bHasFocus) {
					bHasFocus = false;
					this->bFocusPresent = false;
					this->eObjectState = STATE_NONE;
					std::string vBuffer = execEdit();
				}

				updateObjectState(STATE_UPDATE);
			}


			/*
			 * Allow mapping to any field template from within GUI base class
			 */
			class AnyField {
				private:
					enum{NONE, FLOAT, INT, STRING} tag=NONE;
					union {
						Object::Field<float>		* f;
						Object::Field<int>			* i;
						Object::Field<std::string>	* s;
					};

				public:
					AnyField() {	tag=NONE;	}
					void set(std::string n, float * fPtr, Props_Field &c)					{	tag = FLOAT;	c.bNumeric = true;		f = new Object::Field<float>(n, fPtr, c);	}
					void set(std::string n, float * fPtr, Props_Field *c)					{	tag = FLOAT;	c->bNumeric = true;		f = new Object::Field<float>(n, fPtr, c);	}
					void set(std::string n, float fVal, Props_Field *c)						{	tag = FLOAT;	c->bNumeric = true;		f = new Object::Field<float>(n, fVal, c);	}
					void set(std::string n, int * iPtr, Props_Field &c)						{	tag = INT;		c.bNumeric = true;		i = new Object::Field<int>(n, iPtr, c);	}
					void set(std::string n, int * iPtr, Props_Field *c)						{	tag = INT;		c->bNumeric = true;		i = new Object::Field<int>(n, iPtr, c);	}
					void set(std::string n, int iVal, Props_Field *c)						{	tag = INT;		c->bNumeric = true;		i = new Object::Field<int>(n, iVal, c);	}
					void set(std::string n, std::string * sPtr, Props_Field &c)				{	tag = STRING;	c.bNumeric = false;		s = new Object::Field<std::string>(n, sPtr, c);	}
					void set(std::string n, std::string * sPtr, Props_Field *c)				{	tag = STRING;	c->bNumeric = false;	s = new Object::Field<std::string>(n, sPtr, c);	}
					void set(std::string n, std::string sVal, Props_Field *c)				{	tag = STRING;	c->bNumeric = false;	s = new Object::Field<std::string>(n, sVal, c);	}


					void set(Props &p, std::string n, float * fPtr, Props_Field &c)			{	tag = FLOAT;	c.bNumeric = true;		f = new Object::Field<float>(p, n, fPtr, c);	}
					void set(Props &p, std::string n, float * fPtr, Props_Field *c)			{	tag = FLOAT;	c->bNumeric = true;		f = new Object::Field<float>(p, n, fPtr, c);	}
					void set(Props &p, std::string n, float fVal, Props_Field *c)			{	tag = FLOAT;	c->bNumeric = true;		f = new Object::Field<float>(p, n, fVal, c);	}
					void set(Props &p, std::string n, int * iPtr, Props_Field &c)			{	tag = INT;		c.bNumeric = true;		i = new Object::Field<int>(p, n, iPtr, c);	}
					void set(Props &p, std::string n, int * iPtr, Props_Field *c)			{	tag = INT;		c->bNumeric = true;		i = new Object::Field<int>(p, n, iPtr, c);	}
					void set(Props &p, std::string n, int iVal, Props_Field *c)				{	tag = INT;		c->bNumeric = true;		i = new Object::Field<int>(p, n, iVal, c);	}
					void set(Props &p, std::string n, std::string * sPtr, Props_Field &c)	{	tag = STRING;	c.bNumeric = false;		s = new Object::Field<std::string>(p, n, sPtr, c);	}
					void set(Props &p, std::string n, std::string * sPtr, Props_Field *c)	{	tag = STRING;	c->bNumeric = false;	s = new Object::Field<std::string>(p, n, sPtr, c);	}
					void set(Props &p, std::string n, std::string sVal, Props_Field *c)		{	tag = STRING;	c->bNumeric = false;	s = new Object::Field<std::string>(p, n, sVal, c);	}

					Object::Field<float> * getF() { if(tag==FLOAT) return f; else return nullptr; }
					Object::Field<int> * getI() { if(tag==INT) return i; else return nullptr; }
					Object::Field<std::string> * getS() { if(tag==STRING) return s; else return nullptr; }

					template <typename T> Object::Field<T> * get() {
						switch(tag) {
							case FLOAT:		return f; break;
							case INT:		return i; break;
							case STRING:	return s; break;
						}
						return nullptr;
					}

					void init() {
						switch(tag) {
							case FLOAT:		f->init(); break;
							case INT:		i->init(); break;
							case STRING:	s->init(); break;
						}
					}

					void exec(iState eExternState=STATE_NONE) {
						switch(tag) {
							case FLOAT:		f->exec(eExternState); break;
							case INT:		i->exec(eExternState); break;
							case STRING:	s->exec(eExternState); break;
						}
					}

					void execToolTip() {
						switch(tag) {
							case FLOAT:	f->execToolTip(); break;
							case INT:	i->execToolTip(); break;
						}
					}

					void updateNoFocus() {
						switch(tag) {
							case FLOAT:	f->updateNoFocus(); break;
							case INT:	i->updateNoFocus(); break;
						}
					}

					void setPointer(float * fPtr) {
						tag = FLOAT;
						f->setValuePtr(fPtr);
						//f->valuePtr = fPtr;
//						f->setPointer(fPtr);
					}

					void setPointer(int * iPtr) {
						tag = INT;
						i->setValuePtr(iPtr);
						//i->valuePtr = iPtr;
//						i->setPointer(iPtr);
					}

					int state() {
						switch(tag) {
							case FLOAT:		return f->mState; break;
							case INT:		return i->mState; break;
							case STRING:	return s->mState; break;
						}
						return 0;
					}

					~AnyField() {
						switch(tag) {
							case FLOAT:
								delete f;
								break;
							case INT:
								delete i;
								break;
							case STRING:
								delete s;
								break;
						}
					}
			};

		}
	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_FIELD_H_ */
