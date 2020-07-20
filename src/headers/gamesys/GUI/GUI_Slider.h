/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_SLIDER_H_
#define HEADERS_GAMESYS_GUI_SLIDER_H_

#include <iostream>
//#include "../core/core_functions.h"
//#include "../core/vao.h"
//#include "../core/matrix.h"
//#include "../core/shader.h"
#include "GUI_Constraint.h"
#include "GUI_ToolTip.h"
#include "GUI_Window.h"
#include "GUI_Field.h"
#include "GUI_Label.h"


/*
 * Draw a button with text
 * 	- Use a Window as the structure
 * 	- Watch for mouse click events
 * 	- If in button bounds then return true
 * 	- Focus depends on parent window
 */

namespace Core {
	namespace GUI {
		namespace Object {
			template <typename T>
			class Slider : public Base::Interactive<Props_Slider, T>, public Base::AudioFeedback {
					friend class AnySlider;
				public:
					Slider();
					Slider(std::string n, T *ptr, Props_Slider c);
					Slider(std::string n, T *ptr, Props_Slider *c);
					Slider(Props &p, std::string n, T *ptr, Props_Slider c);
					Slider(Props &p, std::string n, T *ptr, Props_Slider *c);

					Slider(std::string n, T t, Props_Slider c);
					Slider(std::string n, T t, Props_Slider *c);
					Slider(Props &p, std::string n, T t, Props_Slider c);
					Slider(Props &p, std::string n, T t, Props_Slider *c);
					virtual ~Slider();

					ToolTip toolTip;
					void init();
					void exec(iState eExternState=STATE_NONE);
					void execToolTip();
					void updateNoFocus();

				protected:
					Window slider, control;
					Object::Field<T>	*field;		///< Show field value and allow editing if enabled
					Object::Label		*label;		///< Show slider name if enabled
					float	minPos,					///< Exact screen coordinate for minimum position
							maxPos,					///< Exact screen coordinate for maximum position
							spanPos,				///< Difference of min and max positions
							spanValue;				///< Difference ofmin and max values (from constraints)
					T		lastValue;				///< Value at the last cycle, used to determine bValueChanged
					Vector2f currentPos;			///< Current slider position based on currentValue
					bool bHasFocus;
					void update();
					void setValue();
					void setValue(T f);
					void updateScrollMouse();
					void updateObjectState(iState eExternState);
					float getNormalized(T fCurrent, float fMin, float fMax);
					float getValueFromPos(float f);
					float getPosFromValue(T f);
					void updateControlPos();
			};

			template <class T> Slider<T>::Slider() {
				minPos				= 0.0f;
				maxPos				= 100.0f;
				spanPos				= 100.0f;
				spanValue			= 0.0f;
				currentPos			= Vector2f(0.0f);
				bHasFocus			= false;
				field				= nullptr;
				label				= nullptr;
			}

			template <class T> Slider<T>::Slider(std::string n, T *ptr, Props_Slider c) {
				currentPos			= Vector2f(0.0f);
				bHasFocus			= false;
				minPos				= 0.0f;
				maxPos				= 100.0f;
				spanPos				= 100.0f;
				spanValue			= 0.0f;
				field				= nullptr;
				label				= nullptr;
				this->name			= n;

				this->bHasParent	= false;
				this->parent		= nullptr;

				this->bLocalValue	= false;
				this->valuePtr		= ptr;

				this->bLocalCon		= true;
				this->con			= new Props_Slider();
				*this->con			= c;
			}

			template <class T> Slider<T>::Slider(std::string n, T *ptr, Props_Slider *c) {
				currentPos			= Vector2f(0.0f);
				bHasFocus			= false;
				minPos				= 0.0f;
				maxPos				= 100.0f;
				spanPos				= 100.0f;
				spanValue			= 0.0f;
				field				= nullptr;
				label				= nullptr;
				this->name			= n;

				this->bHasParent	= false;
				this->parent		= nullptr;

				this->bLocalValue	= false;
				this->valuePtr		= ptr;

				this->bLocalCon		= false;
				this->con			= c;
			}

			template <class T> Slider<T>::Slider(Props &p, std::string n, T *ptr, Props_Slider c) {
				currentPos			= Vector2f(0.0f);
				bHasFocus			= false;
				minPos				= 0.0f;
				maxPos				= 100.0f;
				spanPos				= 100.0f;
				spanValue			= 0.0f;
				field				= nullptr;
				label				= nullptr;
				this->name			= n;

				this->bHasParent	= true;
				this->parent		= &p;

				this->bLocalValue	= false;
				this->valuePtr		= ptr;

				this->bLocalCon		= true;
				this->con			= new Props_Slider();
				*this->con			= c;
			}

			template <class T> Slider<T>::Slider(Props &p, std::string n, T *ptr, Props_Slider *c) {
				currentPos			= Vector2f(0.0f);
				bHasFocus			= false;
				minPos				= 0.0f;
				maxPos				= 100.0f;
				spanPos				= 100.0f;
				spanValue			= 0.0f;
				field				= nullptr;
				label				= nullptr;
				this->name			= n;

				this->bHasParent	= true;
				this->parent		= &p;

				this->bLocalValue	= false;
				this->valuePtr		= ptr;

				this->bLocalCon		= false;
				this->con			= c;
			}















			template <class T> Slider<T>::Slider(std::string n, T *ptr, Props_Slider c) {
				currentPos			= Vector2f(0.0f);
				bHasFocus			= false;
				minPos				= 0.0f;
				maxPos				= 100.0f;
				spanPos				= 100.0f;
				spanValue			= 0.0f;
				field				= nullptr;
				label				= nullptr;
				this->name			= n;

				this->bHasParent	= false;
				this->parent		= nullptr;

				this->bLocalValue	= false;
				this->valuePtr		= ptr;

				this->bLocalCon		= true;
				this->con			= new Props_Slider();
				*this->con			= c;
			}

			template <class T> Slider<T>::Slider(std::string n, T *ptr, Props_Slider *c) {
				currentPos			= Vector2f(0.0f);
				bHasFocus			= false;
				minPos				= 0.0f;
				maxPos				= 100.0f;
				spanPos				= 100.0f;
				spanValue			= 0.0f;
				field				= nullptr;
				label				= nullptr;
				this->name			= n;

				this->bHasParent	= false;
				this->parent		= nullptr;

				this->bLocalValue	= false;
				this->valuePtr		= ptr;

				this->bLocalCon		= false;
				this->con			= c;
			}

			template <class T> Slider<T>::Slider(Props &p, std::string n, T *ptr, Props_Slider c) {
				currentPos			= Vector2f(0.0f);
				bHasFocus			= false;
				minPos				= 0.0f;
				maxPos				= 100.0f;
				spanPos				= 100.0f;
				spanValue			= 0.0f;
				field				= nullptr;
				label				= nullptr;
				this->name			= n;

				this->bHasParent	= true;
				this->parent		= &p;

				this->bLocalValue	= false;
				this->valuePtr		= ptr;

				this->bLocalCon		= true;
				this->con			= new Props_Slider();
				*this->con			= c;
			}

			template <class T> Slider<T>::Slider(Props &p, std::string n, T *ptr, Props_Slider *c) {
				currentPos			= Vector2f(0.0f);
				bHasFocus			= false;
				minPos				= 0.0f;
				maxPos				= 100.0f;
				spanPos				= 100.0f;
				spanValue			= 0.0f;
				field				= nullptr;
				label				= nullptr;
				this->name			= n;

				this->bHasParent	= true;
				this->parent		= &p;

				this->bLocalValue	= false;
				this->valuePtr		= ptr;

				this->bLocalCon		= false;
				this->con			= c;
			}
















			template <class T> Slider<T>::~Slider() {
				if(this->bLocalCon && this->con != nullptr) delete this->con;
				if(label != nullptr) delete label;
				if(field != nullptr) delete field;
			}

			template <class T> void Slider<T>::init() {
				// Setup contraints
				if(this->bHasParent) this->con->exec(*this->parent);
				else this->con->exec();

				// FIXME: Create SOUNDS enumeration
				initSound(3, 7, 8, -1, 0, false, true);

				update();
				setValue(*this->valuePtr);

				float offset = std::round((this->con->size.y+1)/2.0f);

				// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
				// 			Setup Label
				// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
				if(this->con->bShowLabel) {
					this->con->label.enablePadding(PADDING_POSITION);
					label = new Object::Label(*this->con, this->name, this->con->label);
					label->init();
				}

				// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
				// 			Setup Field
				// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
				if(this->con->bShowField) {
					int iFieldAnchor;

					if(this->con->minValue < this->con->maxValue) this->con->field.setMinMax(this->con->minValue, this->con->maxValue);
					else this->con->field.setMinMax(this->con->maxValue, this->con->minValue);

					if(this->con->bExactSize) {
						this->con->field.setWidth(this->con->iFieldSize, SIZE_CONSTRAINT_ABSOLUTE);
					}
					else {
						// Determine maximum field size
						int l1 = to_string(this->con->maxValue).length();
						int l2 = to_string(this->con->minValue).length();
						int maxSize = 0;
						if(l1>l2) maxSize = l1;
						else maxSize = l2;
						maxSize = (maxSize*Core::gameVars->font.vSize.x)+(this->con->field.vPadding.left+this->con->field.vPadding.right);
						if(maxSize<this->con->iFieldSize) maxSize = this->con->iFieldSize;
						this->con->field.setWidth(maxSize, SIZE_CONSTRAINT_ABSOLUTE);
					}

					this->con->field.setHeight(Core::gameVars->font.vSize.y+(this->con->field.vPadding.top+this->con->field.vPadding.bottom), SIZE_CONSTRAINT_ABSOLUTE);
					this->con->field.setToolTip(this->con->toolTip.Text);

					this->con->field.enablePadding(PADDING_POSITION);
					field = new Object::Field<T>(*this->con, this->name+"_Field", this->valuePtr, this->con->field);	// Must add "_Field" or conflict occurs with active object states
					field->init();
				}

				// Update position according to field and label, this is a one-time thing


				// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
				// 			Setup VAO
				// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
				if(this->bHasParent) slider = Window(*this->parent, this->name, this->con);
				else slider = Window(this->name, this->con);
				slider.init();

				control = Window(*this->con, this->name, &this->con->control);
				control.init();

				this->toolTip.init(*this->con, this->name);

				this->bInit = true;
			}

			template <class T> void Slider<T>::update() {
				if(this->con->orientation == Core::GUI::SLIDER_HORIZONTAL) {
					minPos = this->con->pos.x-(this->con->size.x/2.0f);
					maxPos = this->con->pos.x+(this->con->size.x/2.0f);
					spanPos = abs(maxPos - minPos)-this->con->control.size.x;
					spanValue = abs(this->con->maxValue - this->con->minValue);
				}
				else if(this->con->orientation == Core::GUI::SLIDER_VERTICAL) {
					minPos = -this->con->pos.y+(this->con->size.y/2.0f);
					maxPos = -this->con->pos.y-(this->con->size.y/2.0f);
					spanPos = abs(minPos - maxPos)-this->con->control.size.y;
					spanValue = abs(this->con->maxValue - this->con->minValue);
				}
			}

			template <class T> float Slider<T>::getNormalized(T fCurrent, float fMin, float fMax) {
				float f = fmin( fmax( (fCurrent-fMin)/(fMax-fMin), 0.0f), 1.0f);
				return f;
			}

			template <class T> float Slider<T>::getValueFromPos(float f) {
				float f1, f2, f3, f4, f5;
				if(this->con->orientation == Core::GUI::SLIDER_HORIZONTAL)	{
					if(this->con->minValue<this->con->maxValue) {
						f1 = getNormalized(f-Core::gameVars->screen.half.x, minPos, maxPos);
					}
					else {
						f1 = getNormalized(f-Core::gameVars->screen.half.x, maxPos, minPos);
					}
				}
				else if(this->con->orientation == Core::GUI::SLIDER_VERTICAL)	{
					if(this->con->minValue<this->con->maxValue) {
						f1 = getNormalized(f-Core::gameVars->screen.half.y, minPos, maxPos);
					}
					else {
						f1 = getNormalized(f-Core::gameVars->screen.half.y, maxPos, minPos);
					}
				}

				f2 = spanValue;
					if(this->con->minValue<this->con->maxValue) {
						f3 = this->con->minValue;
					}
					else {
						f3 = this->con->maxValue;
					}
				f4 = 0.0f;
				f5 = f1 * f2 + f3 - f4;

				return int(f5/this->con->fMinimumStep)*this->con->fMinimumStep;
			}

			template <class T> float Slider<T>::getPosFromValue(T f) {
				float f1, f2, f3, f4, f5;
				f1 = getNormalized(f, this->con->minValue, this->con->maxValue);

				if(this->con->orientation == Core::GUI::SLIDER_HORIZONTAL) {
					f2 = spanPos;
					f4 = this->con->size.x/2.0f;
				}
				else if(this->con->orientation == Core::GUI::SLIDER_VERTICAL) {
					f2 = spanPos;
					f4 = this->con->size.y/2.0f;
				}

				f3 = 0.0f;
				f5 = f1 * f2 + f3 - f4;
				return f5;
			}

			template <class T> void Slider<T>::setValue() {
				setValue(*this->valuePtr);
			}

			template <class T> void Slider<T>::setValue(T f) {
				if(this->con->minValue<this->con->maxValue)	*this->valuePtr = fmax( fmin( f, this->con->maxValue ), this->con->minValue );
				else										*this->valuePtr = fmax( fmin( f, this->con->minValue ), this->con->maxValue );

				if(this->con->orientation == Core::GUI::SLIDER_HORIZONTAL) {
					currentPos.x = getPosFromValue(*this->valuePtr)+(this->con->control.size.x/2.0f);
					currentPos.y = 0.0f;
				}
				else if(this->con->orientation == Core::GUI::SLIDER_VERTICAL) {
					currentPos.x = 0.0f;
					currentPos.y = getPosFromValue(*this->valuePtr)+(this->con->control.size.y/2.0f);
				}
			}

			template <class T> void Slider<T>::updateControlPos() {
				if(this->con->orientation == Core::GUI::SLIDER_HORIZONTAL)	*this->valuePtr = getValueFromPos(Core::mouse->x);
				else if(this->con->orientation == Core::GUI::SLIDER_VERTICAL)	*this->valuePtr = getValueFromPos(Core::mouse->y);
				setValue();
			}

			/*
			 * Returns true if value has changed since last
			 * time read. Immediately resets for one shot
			 * operation.
			 */
//			template <class T> bool Slider<T>::valueChanged() {
//				if(bValueChanged) {
//					bValueChanged = false;
//					return true;
//				}
//				return false;
//			}

			template <class T> void Slider<T>::updateScrollMouse() {

				Core::_Mouse::MOUSE_STATE wheel = Core::mouse->checkWheel();

				if(wheel != Core::_Mouse::MOUSE_NONE) {
					T modVal = (spanValue/spanPos);		// Default, move by 1 pixel worth of value

					const Uint8 *keyState = SDL_GetKeyboardState(NULL);
					if (keyState[SDL_SCANCODE_LSHIFT] || keyState[SDL_SCANCODE_RSHIFT])		modVal *= 10;
					else if (keyState[SDL_SCANCODE_LCTRL] || keyState[SDL_SCANCODE_RCTRL])	modVal /= 10;

					modVal *= this->con->scrollSpeed;
					modVal = int(modVal/this->con->fMinimumStep)*this->con->fMinimumStep;

					if(modVal < this->con->fMinimumStep)		modVal = this->con->fMinimumStep;
					if(this->con->minValue > this->con->maxValue)	modVal = -modVal;

					switch(wheel) {
						case Core::_Mouse::MOUSE_WHEEL_UP:		*this->valuePtr += modVal;	break;
						case Core::_Mouse::MOUSE_WHEEL_DOWN:	*this->valuePtr -= modVal;	break;
					}
				}
			}

			template <> void Slider<int>::updateScrollMouse() {
				int modVal = std::fmax(spanValue/spanPos, 1.0f);

				const Uint8 *keyState = SDL_GetKeyboardState(NULL);
				if (keyState[SDL_SCANCODE_LSHIFT] || keyState[SDL_SCANCODE_RSHIFT])		modVal *= 10;
				else if (keyState[SDL_SCANCODE_LCTRL] || keyState[SDL_SCANCODE_RCTRL])	modVal /= 10;

				if(con->minValue>con->maxValue) 	modVal = -modVal;

				Core::_Mouse::MOUSE_STATE wheel = Core::mouse->checkWheel();
				if(wheel == Core::_Mouse::MOUSE_WHEEL_UP)		*valuePtr += (modVal*con->scrollSpeed);
				if(wheel == Core::_Mouse::MOUSE_WHEEL_DOWN)		*valuePtr -= (modVal*con->scrollSpeed);
			}

			template <class T> void Slider<T>::updateObjectState(iState eExternState) {
				if(eExternState!=STATE_NONE && !(eExternState&STATE_UPDATE)) {
					this->eObjectState = eExternState;
				}
				else {
					if(!(eExternState&STATE_UPDATE)) {
						this->mState = Core::mouse->checkInput(gameVars->screen.half.x+this->con->pos.x, gameVars->screen.half.y-this->con->pos.y, std::max(this->con->size.x, this->con->control.size.x), std::max(this->con->size.y, this->con->control.size.y));
					}
					else this->mState = Core::_Mouse::MOUSE_NONE;

					if(this->enabled()) {
						// Modify slider value by mouse wheel
						if(this->mState == Core::_Mouse::MOUSE_HOVER) {
							updateScrollMouse();
						}

						if(!this->bHasFocus && (this->mState==Core::_Mouse::MOUSE_LEFT || this->mState==Core::_Mouse::MOUSE_LEFT_DOWN)) {
							bHasFocus = true;
							this->bFocusPresent = true;
							this->sActiveObject = this->name;
							this->eObjectState = STATE_ACTIVE;
							Sound_PlayOn();
						}
						else if(bHasFocus && (this->eObjectState&STATE_ACTIVE) && Core::mouse->checkState()!=Core::_Mouse::MOUSE_LEFT_DOWN) {
							bHasFocus = false;
							this->bFocusPresent = false;
							if(this->sActiveObject == this->name) this->sActiveObject = "";
							this->eObjectState = STATE_NONE;
							Sound_PlayOff();
						}
						else if(!bHasFocus && !(this->eObjectState&STATE_ACTIVE) && this->mState==Core::_Mouse::MOUSE_HOVER) {
							this->eObjectState = STATE_HOVER;
						}
						else if (!(this->eObjectState&STATE_ACTIVE) || ((this->eObjectState&STATE_ACTIVE) && !this->bFocusPresent) ) {
							this->eObjectState = STATE_NONE;
						}
					}
					else this->eObjectState = STATE_NONE;

					// Allow mouse hover at any time (used for tooltips)
					if(!(eExternState&STATE_UPDATE)) {
						if(this->mState==Core::_Mouse::MOUSE_HOVER) this->eObjectState = this->eObjectState|STATE_HOVER;
						else this->eObjectState = this->eObjectState&~STATE_HOVER;
					}
				}

				if(!this->enabled()) this->eObjectState |= STATE_DISABLED;
			}

			template <class T> void Slider<T>::exec(iState eExternState) {
				if(this->bInit && this->con->visibility && ((this->parent!=nullptr && this->parent->visibility) || (this->parent==nullptr))) {
					/*
					 * Update constraints
					 */
					if(this->bHasParent) this->con->exec(*this->parent);
					else this->con->exec();

					/*
					 * Update slider min/max values
					 *	- This only matters if contraints have changed (future proof, resizable windows)
					 */
					update();
					if(!this->bFocusPresent || (this->sActiveObject==this->name)) {
						updateObjectState(eExternState);

						if(this->con->toolTip.bShow) this->toolTip.updateObjectState(this->eObjectState);
						else this->toolTip.updateObjectState(STATE_NONE);
					}

					/*
					 * Check if slider update in progress according to LAST saved state.
					 * 	- Requires that min/max values be updated via update()
					 * 	- If not moving slider then update value in case changed externally
					 */
					if(this->eObjectState&STATE_ACTIVE) {
						updateControlPos();
//						bValueChanged = true;
					}
					else setValue();

					// Check if value has changed
					if(lastValue != *this->valuePtr) {
						this->bValueChanged = true;
					}
					lastValue = *this->valuePtr;

					// Draw Slider
					slider.exec(this->eObjectState);

					// Draw Control
					control.con->setPos(currentPos);
					control.exec(this->eObjectState);

					// Draw Label
					if(this->con->bShowLabel)	label->exec(this->eObjectState);

					// Draw Value
					if(this->con->bShowField)	field->exec(this->eObjectState);
				}
			}

			// TODO: Add to all objects with nested objects
			template <class T> void Slider<T>::execToolTip() {
				toolTip.exec();
				if(this->con->bShowField) field->toolTip.exec();
			}

			/***
			 * \brief Calls to run when object not visible/not in focus.
			 * @tparam T
			 * @tparam T
			 */
			template <class T> void Slider<T>::updateNoFocus() {
				if(bHasFocus) {
					bHasFocus = false;
					this->bFocusPresent = false;
					this->eObjectState = STATE_NONE;
				}
				updateObjectState(STATE_UPDATE);
				if(this->con->bShowField) field->updateNoFocus();
			}

			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// 			Draw Value
			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			class AnySlider {
//					friend class GUI_Container;
//					friend class GUI_Container::SliderInterface;
				private:
					enum{NONE, FLOAT, INT} tag=NONE;
					union {
						Object::Slider<float>	* f;
						Object::Slider<int>		* i;
					};
//					void set(std::string n, float * fPtr, Props_Slider c)						{	tag = FLOAT;	f = new Object::Slider<float>(n, fPtr, c);		}
//					void set(std::string n, float * fPtr, Props_Slider *c)					{	tag = FLOAT;	f = new Object::Slider<float>(n, fPtr, c);		}
//					void set(std::string n, int * iPtr, Props_Slider c)						{	tag = INT;		i = new Object::Slider<int>(n, iPtr, c);		}
//					void set(std::string n, int * iPtr, Props_Slider *c)						{	tag = INT;		i = new Object::Slider<int>(n, iPtr, c);		}
//					void set(Props &p, std::string n, float * fPtr, Props_Slider c)		{	tag = FLOAT;	f = new Object::Slider<float>(p, n, fPtr, c);	}
//					void set(Props &p, std::string n, float * fPtr, Props_Slider *c)	{	tag = FLOAT;	f = new Object::Slider<float>(p, n, fPtr, c);	}
//					void set(Props &p, std::string n, int * iPtr, Props_Slider c)		{	tag = INT;		i = new Object::Slider<int>(p, n, iPtr, c);		}
//					void set(Props &p, std::string n, int * iPtr, Props_Slider *c)		{	tag = INT;		i = new Object::Slider<int>(p, n, iPtr, c);		}

				public:
					// FIXME: Make these private somehow?
					void set(std::string n, float * fPtr, Props_Slider c)						{	tag = FLOAT;	f = new Object::Slider<float>(n, fPtr, c);		}
					void set(std::string n, float * fPtr, Props_Slider *c)					{	tag = FLOAT;	f = new Object::Slider<float>(n, fPtr, c);		}
					void set(std::string n, int * iPtr, Props_Slider c)						{	tag = INT;		i = new Object::Slider<int>(n, iPtr, c);		}
					void set(std::string n, int * iPtr, Props_Slider *c)						{	tag = INT;		i = new Object::Slider<int>(n, iPtr, c);		}
					void set(Props &p, std::string n, float * fPtr, Props_Slider c)		{	tag = FLOAT;	f = new Object::Slider<float>(p, n, fPtr, c);	}
					void set(Props &p, std::string n, float * fPtr, Props_Slider *c)	{	tag = FLOAT;	f = new Object::Slider<float>(p, n, fPtr, c);	}
					void set(Props &p, std::string n, int * iPtr, Props_Slider c)		{	tag = INT;		i = new Object::Slider<int>(p, n, iPtr, c);		}
					void set(Props &p, std::string n, int * iPtr, Props_Slider *c)		{	tag = INT;		i = new Object::Slider<int>(p, n, iPtr, c);		}

					Object::Slider<float>	* getF() { if(tag==FLOAT) return f; else return nullptr; }
					Object::Slider<int>		* getI() { if(tag==INT) return i; else return nullptr; }

//					std::any * get() {
//						switch(tag) {
//							case FLOAT:		return f; break;
//							case INT:		return i; break;
//						}
//						return nullptr;
//					}

//					auto * get() {
//						struct result {
//							operator Object::Slider<float>() {	return f;	}
//							operator Object::Slider<int>() {	return i;	}
//						};
//						return result{ this };
//					}

					AnySlider() {
						tag=NONE;
					}

					void setPointer(float * fPtr) {
						tag = FLOAT;
						f->valuePtr = fPtr;
						f->field->setPointer(fPtr);
					}

					void setPointer(int * iPtr) {
						tag = INT;
						i->valuePtr = iPtr;
						i->field->setPointer(iPtr);
					}

					void init() {
						switch(tag) {
							case FLOAT:	f->init(); break;
							case INT:	i->init(); break;
						}
					}

					void exec() {
						switch(tag) {
							case FLOAT:	f->exec(); break;
							case INT:	i->exec(); break;
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

					Core::_Mouse::MOUSE_STATE state() {
						switch(tag) {
							case FLOAT:	return f->mState; break;
							case INT:	return i->mState; break;
						}
						return Core::_Mouse::MOUSE_NONE;
					}

					bool valueChanged() {
						switch(tag) {
							case FLOAT: return f->valueChanged(); break;
							case INT: return i->valueChanged(); break;
						}
						return false;
					}

					~AnySlider() {
						switch(tag) {
							case FLOAT:
								delete f;
								break;
							case INT:
								delete i;
								break;
						}
					}
			};
		}
	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_SLIDER_H_ */
