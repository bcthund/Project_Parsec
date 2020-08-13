/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_SLIDER2D_H_
#define HEADERS_GAMESYS_GUI_SLIDER2D_H_

#include <iostream>
#include "../../core/Colors.h"
#include "../../gamesys/gameVars.h"
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
			class Slider2D : public Base::Interactive<Props_Slider2D>, public Base::AudioFeedback {
				public:
					Slider2D();
					Slider2D(std::string n, int *xPtr, int *yPtr, Props_Slider2D &c);
					Slider2D(std::string n, int *xPtr, int *yPtr, Props_Slider2D *c);
					Slider2D(Props &p, std::string n, int *xPtr, int *yPtr, Props_Slider2D &c);
					Slider2D(Props &p, std::string n, int *xPtr, int *yPtr, Props_Slider2D *c);

					Slider2D(std::string n, int xVal, int yVal, Props_Slider2D &c);
					Slider2D(std::string n, int xVal, int yVal, Props_Slider2D *c);
					Slider2D(Props &p, std::string n, int xVal, int yVal, Props_Slider2D &c);
					Slider2D(Props &p, std::string n, int xVal, int yVal, Props_Slider2D *c);
					virtual ~Slider2D();

					int *xValuePtr;
					int *yValuePtr;
					bool bLocalXValue;
					bool bLocalYValue;
//					void setX_ValuePtr(int *xPtr);
//					int & getX_ValuePtr();
//					void setY_ValuePtr(int *yPtr);
//					int & getY_ValuePtr();
//					int getValue();

					ToolTip toolTip;
					void init();
					void exec(iState eExternState=STATE_NONE);
					void execToolTip();
					void updateNoFocus();

				protected:
					Window slider, control;
					Object::Label		*label;		///< Show slider name if enabled
					float	minPos,					///< Exact screen coordinate for minimum position
							maxPos,					///< Exact screen coordinate for maximum position
							spanPos,				///< Difference of min and max positions
							spanValue;				///< Difference ofmin and max values (from constraints)
					int		lastValue;				///< Value at the last cycle, used to determine bValueChanged
					Vector2f currentPos;			///< Current slider position based on currentValue
					bool bHasFocus;
					void update();
//					void setValue();
//					void setValue(T f);
					void updateScrollMouse();
					void updateObjectState(iState eExternState);
//					float getNormalized(T fCurrent, float fMin, float fMax);
//					float getValueFromPos(float f);
//					float getPosFromValue(T f);
					void updateControlPos();
			};

			Slider2D::Slider2D() {
				minPos				= 0.0f;
				maxPos				= 100.0f;
				spanPos				= 100.0f;
				spanValue			= 0.0f;
				currentPos			= Vector2f(0.0f);
				bHasFocus			= false;
				label				= nullptr;
				xValuePtr			= nullptr;
				bLocalXValue		= true;
				yValuePtr			= nullptr;
				bLocalYValue		= true;
				lastValue			= 0;
			}

			Slider2D::Slider2D(std::string n, int *xPtr, int *yPtr, Props_Slider2D &c) {
				lastValue			= 0;
				currentPos			= Vector2f(0.0f);
				bHasFocus			= false;
				minPos				= 0.0f;
				maxPos				= 100.0f;
				spanPos				= 100.0f;
				spanValue			= 0.0f;
				label				= nullptr;
				this->name			= n;

				this->bHasParent	= false;
				this->parent		= nullptr;

				this->bLocalState	= true;
				this->statePtr		= new bool(false);

				this->bLocalXValue	= false;
				this->xValuePtr		= xPtr;
				this->bLocalYValue	= false;
				this->yValuePtr		= yPtr;

				this->bLocalCon		= true;
				this->con			= new Props_Slider2D();
				*this->con			= c;
				if(this->con->text == "") this->con->text = n;
			}

			Slider2D::Slider2D(std::string n, int *xPtr, int *yPtr, Props_Slider2D *c) {
				lastValue			= 0;
				currentPos			= Vector2f(0.0f);
				bHasFocus			= false;
				minPos				= 0.0f;
				maxPos				= 100.0f;
				spanPos				= 100.0f;
				spanValue			= 0.0f;
				label				= nullptr;
				this->name			= n;

				this->bHasParent	= false;
				this->parent		= nullptr;

				this->bLocalState	= true;
				this->statePtr		= new bool(false);

				this->bLocalXValue	= false;
				this->xValuePtr		= xPtr;
				this->bLocalYValue	= false;
				this->yValuePtr		= yPtr;

				this->bLocalCon		= false;
				this->con			= c;
				if(this->con->text == "") this->con->text = n;
			}

			Slider2D::Slider2D(Props &p, std::string n, int *xPtr, int *yPtr, Props_Slider2D &c) {
				lastValue			= 0;
				currentPos			= Vector2f(0.0f);
				bHasFocus			= false;
				minPos				= 0.0f;
				maxPos				= 100.0f;
				spanPos				= 100.0f;
				spanValue			= 0.0f;
				label				= nullptr;
				this->name			= n;

				this->bHasParent	= true;
				this->parent		= &p;

				this->bLocalState	= true;
				this->statePtr		= new bool(false);

				this->bLocalXValue	= false;
				this->xValuePtr		= xPtr;
				this->bLocalYValue	= false;
				this->yValuePtr		= yPtr;

				this->bLocalCon		= true;
				this->con			= new Props_Slider2D();
				*this->con			= c;
				if(this->con->text == "") this->con->text = n;
			}

			Slider2D::Slider2D(Props &p, std::string n, int *xPtr, int *yPtr, Props_Slider2D *c) {
				lastValue			= 0;
				currentPos			= Vector2f(0.0f);
				bHasFocus			= false;
				minPos				= 0.0f;
				maxPos				= 100.0f;
				spanPos				= 100.0f;
				spanValue			= 0.0f;
				label				= nullptr;
				this->name			= n;

				this->bHasParent	= true;
				this->parent		= &p;

				this->bLocalState	= true;
				this->statePtr		= new bool(false);

				this->bLocalXValue	= false;
				this->xValuePtr		= xPtr;
				this->bLocalYValue	= false;
				this->yValuePtr		= yPtr;

				this->bLocalCon		= false;
				this->con			= c;
				if(this->con->text == "") this->con->text = n;
			}

			Slider2D::Slider2D(std::string n, int xVal, int yVal, Props_Slider2D &c) {
				lastValue			= 0;
				currentPos			= Vector2f(0.0f);
				bHasFocus			= false;
				minPos				= 0.0f;
				maxPos				= 100.0f;
				spanPos				= 100.0f;
				spanValue			= 0.0f;
				label				= nullptr;
				this->name			= n;

				this->bHasParent	= false;
				this->parent		= nullptr;

				this->bLocalState	= true;
				this->statePtr		= new bool(false);

				this->bLocalXValue	= true;
				this->xValuePtr		= new int(xVal);
				this->bLocalYValue	= true;
				this->yValuePtr		= new int(yVal);


				this->bLocalCon		= true;
				this->con			= new Props_Slider2D();
				*this->con			= c;
				if(this->con->text == "") this->con->text = n;
			}

			Slider2D::Slider2D(std::string n, int xVal, int yVal, Props_Slider2D *c) {
				lastValue			= 0;
				currentPos			= Vector2f(0.0f);
				bHasFocus			= false;
				minPos				= 0.0f;
				maxPos				= 100.0f;
				spanPos				= 100.0f;
				spanValue			= 0.0f;
				label				= nullptr;
				this->name			= n;

				this->bHasParent	= false;
				this->parent		= nullptr;

				this->bLocalState	= true;
				this->statePtr		= new bool(false);

				this->bLocalXValue	= true;
				this->xValuePtr		= new int(xVal);
				this->bLocalYValue	= true;
				this->yValuePtr		= new int(yVal);

				this->bLocalCon		= false;
				this->con			= c;
				if(this->con->text == "") this->con->text = n;
			}

			Slider2D::Slider2D(Props &p, std::string n, int xVal, int yVal, Props_Slider2D &c) {
				lastValue			= 0;
				currentPos			= Vector2f(0.0f);
				bHasFocus			= false;
				minPos				= 0.0f;
				maxPos				= 100.0f;
				spanPos				= 100.0f;
				spanValue			= 0.0f;
				label				= nullptr;
				this->name			= n;

				this->bHasParent	= true;
				this->parent		= &p;

				this->bLocalState	= true;
				this->statePtr		= new bool(false);

				this->bLocalXValue	= true;
				this->xValuePtr		= new int(xVal);
				this->bLocalYValue	= true;
				this->yValuePtr		= new int(yVal);

				this->bLocalCon		= true;
				this->con			= new Props_Slider2D();
				*this->con			= c;
				if(this->con->text == "") this->con->text = n;
			}

			Slider2D::Slider2D(Props &p, std::string n, int xVal, int yVal, Props_Slider2D *c) {
				lastValue			= 0;
				currentPos			= Vector2f(0.0f);
				bHasFocus			= false;
				minPos				= 0.0f;
				maxPos				= 100.0f;
				spanPos				= 100.0f;
				spanValue			= 0.0f;
				label				= nullptr;
				this->name			= n;

				this->bHasParent	= true;
				this->parent		= &p;

				this->bLocalState	= true;
				this->statePtr		= new bool(false);

				this->bLocalXValue	= true;
				this->xValuePtr		= new int(xVal);
				this->bLocalYValue	= true;
				this->yValuePtr		= new int(yVal);

				this->bLocalCon		= false;
				this->con			= c;
				if(this->con->text == "") this->con->text = n;
			}

			Slider2D::~Slider2D() {
				if(this->bLocalCon && this->con != nullptr) delete this->con;
				if(this->bLocalXValue && this->xValuePtr != nullptr) delete this->xValuePtr;
				if(this->bLocalYValue && this->yValuePtr != nullptr) delete this->yValuePtr;
				if(label != nullptr) delete label;
			}

//			void Slider2D::setValuePtr(T *ptr)	{
//				if(bLocalValue && valuePtr != nullptr) delete valuePtr;
//				bLocalValue = false;
//				valuePtr = ptr;
//			}

//			int & Slider2D::getValuePtr()	{
//				return *valuePtr;
//			}

//			int Slider2D::getValue()	{
//				return *valuePtr;
//			}

			void Slider2D::init() {
				this->id = IDs.create();

				// Setup contraints
//				if(this->bHasParent) this->con->exec(*this->parent);
//				else this->con->exec();

				if(bHasParent) {
					//if(!con->scroll.getEnabled()) con->scroll.bind(*parent);
					con->scroll.bind(*parent);
					con->exec(*parent);
				}
				else con->exec();

				// FIXME: Create SOUNDS enumeration
				initSound(3, 7, 8, -1, 0, false, true);

				update();
//				setValue(*this->valuePtr);

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
				// 			Slider and Control
				// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
				if(this->bHasParent) slider = Window(*this->parent, this->name, this->con);
				else slider = Window(this->name, this->con);
				slider.init();

				control = Window(*this->con, this->name, &this->con->control);
				control.init();

				this->toolTip.init(*this->con, this->name);

				this->bInit = true;
			}

			void Slider2D::update() {
//				if(this->con->orientation == Core::GUI::SLIDER_HORIZONTAL) {
//					minPos = this->con->pos.x-(this->con->size.x/2.0f);
//					maxPos = this->con->pos.x+(this->con->size.x/2.0f);
//					spanPos = abs(maxPos - minPos)-this->con->control.size.x;
//					spanValue = abs(this->con->maxValue - this->con->minValue);
//				}
//				else if(this->con->orientation == Core::GUI::SLIDER_VERTICAL) {
//					minPos = -this->con->pos.y+(this->con->size.y/2.0f);
//					maxPos = -this->con->pos.y-(this->con->size.y/2.0f);
//					spanPos = abs(minPos - maxPos)-this->con->control.size.y;
//					spanValue = abs(this->con->maxValue - this->con->minValue);
//				}
			}

//			float Slider2D::getNormalized(T fCurrent, float fMin, float fMax) {
//				float f = fmin( fmax( (fCurrent-fMin)/(fMax-fMin), 0.0f), 1.0f);
//				return f;
//			}

//			float Slider2D::getValueFromPos(float f) {
//				float f0, f1, f2, f3, f4, f5;
//				f0 = f;
//				if(this->con->orientation == Core::GUI::SLIDER_HORIZONTAL)	{
//					if(parent!=nullptr && parent->scroll.getEnabled()) f0 += con->scroll.getX();
//					if(this->con->minValue<this->con->maxValue) {
//						f1 = getNormalized(f0-Core::gameVars->screen.half.x, minPos, maxPos);
//					}
//					else {
//						f1 = getNormalized(f0-Core::gameVars->screen.half.x, maxPos, minPos);
//					}
//				}
//				else if(this->con->orientation == Core::GUI::SLIDER_VERTICAL)	{
//					if(parent!=nullptr && parent->scroll.getEnabled()) f0 += con->scroll.getY();
//					if(this->con->minValue<this->con->maxValue) {
//						f1 = getNormalized(f0-Core::gameVars->screen.half.y, minPos, maxPos);
//					}
//					else {
//						f1 = getNormalized(f0-Core::gameVars->screen.half.y, maxPos, minPos);
//					}
//				}
//
//				f2 = spanValue;
//					if(this->con->minValue<this->con->maxValue) {
//						f3 = this->con->minValue;
//					}
//					else {
//						f3 = this->con->maxValue;
//					}
//				f4 = 0.0f;
//				f5 = f1 * f2 + f3 - f4;
//
//				return int(f5/this->con->vStep[0])*this->con->vStep[0];		// Constrain value to minimum step size
//			}

//			float Slider2D::getPosFromValue(T f) {
//				float f1, f2, f3, f4, f5;
//				f1 = getNormalized(f, this->con->minValue, this->con->maxValue);
//
//				if(this->con->orientation == Core::GUI::SLIDER_HORIZONTAL) {
//					f2 = spanPos;
//					f4 = this->con->size.x/2.0f;
//				}
//				else if(this->con->orientation == Core::GUI::SLIDER_VERTICAL) {
//					f2 = spanPos;
//					f4 = this->con->size.y/2.0f;
//				}
//
//				f3 = 0.0f;
//				f5 = f1 * f2 + f3 - f4;
//				return f5;
//			}

//			void Slider2D::setValue() {
//				setValue(*this->valuePtr);
//			}

//			void Slider2D::setValue(T f) {
//				if(this->con->minValue<this->con->maxValue)	*this->valuePtr = fmax( fmin( f, this->con->maxValue ), this->con->minValue );
//				else										*this->valuePtr = fmax( fmin( f, this->con->minValue ), this->con->maxValue );
//
//				if(this->con->orientation == Core::GUI::SLIDER_HORIZONTAL) {
//					currentPos.x = getPosFromValue(*this->valuePtr)+(this->con->control.size.x/2.0f);
//					currentPos.y = 0.0f;
//				}
//				else if(this->con->orientation == Core::GUI::SLIDER_VERTICAL) {
//					currentPos.x = 0.0f;
//					currentPos.y = getPosFromValue(*this->valuePtr)+(this->con->control.size.y/2.0f);
//				}
//			}

			void Slider2D::updateControlPos() {
//				if(this->con->orientation == Core::GUI::SLIDER_HORIZONTAL)	*this->valuePtr = getValueFromPos(Core::mouse->x);
//				else if(this->con->orientation == Core::GUI::SLIDER_VERTICAL)	*this->valuePtr = getValueFromPos(Core::mouse->y);
//				setValue();
			}

			void Slider2D::updateScrollMouse() {
//
//				Core::_Mouse::MOUSE_STATE wheel = Core::mouse->checkWheel();
//
//				if(wheel != Core::_Mouse::MOUSE_NONE) {
//					T modVal = this->con->vStep[1];
//
//					const Uint8 *keyState = SDL_GetKeyboardState(NULL);
//					if (keyState[SDL_SCANCODE_LSHIFT] || keyState[SDL_SCANCODE_RSHIFT])		modVal = this->con->vStep[2];
//					else if (keyState[SDL_SCANCODE_LCTRL] || keyState[SDL_SCANCODE_RCTRL])	modVal = this->con->vStep[0];
//
//					if(this->con->minValue > this->con->maxValue) 	modVal = -modVal;
//
//					switch(wheel) {
//						case Core::_Mouse::MOUSE_WHEEL_UP:		*this->valuePtr += modVal;	break;
//						case Core::_Mouse::MOUSE_WHEEL_DOWN:	*this->valuePtr -= modVal;	break;
//					}
//				}
			}

			void Slider2D::updateObjectState(iState eExternState) {
				if((eExternState!=STATE_NONE) && !(eExternState&STATE_UPDATE)) {
					this->eObjectState = eExternState;
				}
				else {
					if(!(eExternState&STATE_UPDATE)) {
						Vector2f vPos = slider.con->getScrollPos();
						Core::_Mouse::iMouseState test1 = Core::mouse->checkInput(gameVars->screen.half.x+vPos.x, gameVars->screen.half.y-vPos.y, slider.con->size.x, slider.con->size.y);

						vPos = control.con->getScrollPos();
						Core::_Mouse::iMouseState test2 = Core::mouse->checkInput(gameVars->screen.half.x+vPos.x, gameVars->screen.half.y-vPos.y, control.con->size.x, control.con->size.y);
						mState = test1 | test2;
					}
					else this->mState = Core::_Mouse::MOUSE_NONE;

					if(this->enabled()) {
						// Modify slider value by mouse wheel
						if(this->mState&Core::_Mouse::MOUSE_HOVER) {
							updateScrollMouse();
						}

						if(!this->bHasFocus && ((this->mState&Core::_Mouse::MOUSE_LEFT) || (this->mState&Core::_Mouse::MOUSE_LEFT_DOWN))) {
							bHasFocus = true;
							this->bFocusPresent = true;
							this->sActiveObject = this->id;
							this->eObjectState = STATE_ACTIVE;
							Sound_PlayOn();
						}
						else if(bHasFocus && (this->eObjectState&STATE_ACTIVE) && Core::mouse->checkState()!=Core::_Mouse::MOUSE_LEFT_DOWN) {
							bHasFocus = false;
							this->bFocusPresent = false;
							if(this->sActiveObject == this->id) this->sActiveObject = "";
							this->eObjectState = STATE_NONE;
							Sound_PlayOff();
						}
						else if(!bHasFocus && !(this->eObjectState&STATE_ACTIVE) && (this->mState&Core::_Mouse::MOUSE_HOVER)) {
							this->eObjectState = STATE_HOVER;
						}
						else if (!(this->eObjectState&STATE_ACTIVE) || ((this->eObjectState&STATE_ACTIVE) && !this->bFocusPresent) ) {
							this->eObjectState = STATE_NONE;
						}
					}
					else this->eObjectState = STATE_NONE;

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
				}

				if(!this->enabled()) this->eObjectState |= STATE_DISABLED;

				updateStatePtr();
			}

			void Slider2D::exec(iState eExternState) {
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
					if((this->con->bFocusLock && !this->bFocusPresent) || !this->con->bFocusLock || (this->sActiveObject==this->id)) {
						updateObjectState(eExternState);

						if(this->con->toolTip.bShow) this->toolTip.updateObjectState(this->eObjectState);
						else this->toolTip.updateObjectState(STATE_NONE);
					}

					/*
					 * Check if slider update in progress according to LAST saved state.
					 * 	- Requires that min/max values be updated via update()
					 * 	- If not moving slider then update value in case changed externally
					 */
//					if(this->eObjectState&STATE_ACTIVE) {
//						updateControlPos();
//					}
//					else setValue();

					// Check if value has changed
//					if(lastValue != *this->valuePtr) {
//						this->bStateChanged = true;
//					}
//					lastValue = *this->valuePtr;

					debug.log("Drawing Slider2D");

					// Draw Slider
					slider.exec(this->eObjectState);

					// Draw Control
					control.con->setPos(currentPos);
					control.exec(this->eObjectState);
					//control.exec(STATE_NONE);

					// Draw Label
					if(this->con->bShowLabel)	label->exec(this->eObjectState);
				}
			}

			// TODO: Add to all objects with nested objects
			void Slider2D::execToolTip() {
				toolTip.exec();
			}

			/***
			 * \brief Calls to run when object not visible/not in focus.
			 * @tparam T
			 * @tparam T
			 */
			void Slider2D::updateNoFocus() {
//				if(bHasFocus) {
//					bHasFocus = false;
//					this->bFocusPresent = false;
//					this->eObjectState = STATE_NONE;
//				}
//				updateObjectState(STATE_UPDATE);
//				if(this->con->bShowField) field->updateNoFocus();
			}










		}
	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_SLIDER2D_H_ */
