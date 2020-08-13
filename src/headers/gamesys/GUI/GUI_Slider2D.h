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

					void setX_ValuePtr(int *xPtr);
					int & getX_ValuePtr();
					int getX_Value();

					void setY_ValuePtr(int *yPtr);
					int & getY_ValuePtr();
					int getY_Value();

					ToolTip toolTip;
					void init();
					void exec(iState eExternState=STATE_NONE);
					void execToolTip();
					void updateNoFocus();

				protected:
					Window slider, control;
					Object::Label		*label;		///< Show slider name if enabled
					float	xMinPos,					///< Exact screen coordinate for minimum position
							xMaxPos,					///< Exact screen coordinate for maximum position
							yMinPos,
							yMaxPos,
							xSpanPos,				///< Difference of min and max positions
							ySpanPos,
							xSpanValue,				///< Difference ofmin and max values (from constraints)
							ySpanValue;
					int		lastValue;				///< Value at the last cycle, used to determine bValueChanged
					Vector2f currentPos;			///< Current slider position based on currentValue
					bool bHasFocus;
					void update();

					void setX_Value();
					void setX_Value(int xVal);
					void setY_Value();
					void setY_Value(int yVal);

					void updateScrollMouse();
					void updateObjectState(iState eExternState);

					float getNormalized(int iCurrent, int iMin, int iMax);

					int getX_ValueFromPos(int xVal);
					int getY_ValueFromPos(int yVal);
					void updateControlPos();
					void updateInput();
			};

			Slider2D::Slider2D() {
				xMinPos				= 0.0f;
				xMaxPos				= 100.0f;
				xSpanPos			= 100.0f;
				yMinPos				= 0.0f;
				yMaxPos				= 100.0f;
				ySpanPos			= 100.0f;
				xSpanValue			= 0.0f;
				ySpanValue			= 0.0;
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
				xMinPos				= 0.0f;
				xMaxPos				= 100.0f;
				xSpanPos			= 100.0f;
				yMinPos				= 0.0f;
				yMaxPos				= 100.0f;
				ySpanPos			= 100.0f;
				xSpanValue			= 0.0f;
				ySpanValue			= 0.0;
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
				xMinPos				= 0.0f;
				xMaxPos				= 100.0f;
				xSpanPos			= 100.0f;
				yMinPos				= 0.0f;
				yMaxPos				= 100.0f;
				ySpanPos			= 100.0f;
				xSpanValue			= 0.0f;
				ySpanValue			= 0.0;
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
				xMinPos				= 0.0f;
				xMaxPos				= 100.0f;
				xSpanPos			= 100.0f;
				yMinPos				= 0.0f;
				yMaxPos				= 100.0f;
				ySpanPos			= 100.0f;
				xSpanValue			= 0.0f;
				ySpanValue			= 0.0;
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
				xMinPos				= 0.0f;
				xMaxPos				= 100.0f;
				xSpanPos			= 100.0f;
				yMinPos				= 0.0f;
				yMaxPos				= 100.0f;
				ySpanPos			= 100.0f;
				xSpanValue			= 0.0f;
				ySpanValue			= 0.0;
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
				xMinPos				= 0.0f;
				xMaxPos				= 100.0f;
				xSpanPos			= 100.0f;
				yMinPos				= 0.0f;
				yMaxPos				= 100.0f;
				ySpanPos			= 100.0f;
				xSpanValue			= 0.0f;
				ySpanValue			= 0.0;
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
				xMinPos				= 0.0f;
				xMaxPos				= 100.0f;
				xSpanPos			= 100.0f;
				yMinPos				= 0.0f;
				yMaxPos				= 100.0f;
				ySpanPos			= 100.0f;
				xSpanValue			= 0.0f;
				ySpanValue			= 0.0;
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
				xMinPos				= 0.0f;
				xMaxPos				= 100.0f;
				xSpanPos			= 100.0f;
				yMinPos				= 0.0f;
				yMaxPos				= 100.0f;
				ySpanPos			= 100.0f;
				xSpanValue			= 0.0f;
				ySpanValue			= 0.0;
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
				xMinPos				= 0.0f;
				xMaxPos				= 100.0f;
				xSpanPos			= 100.0f;
				yMinPos				= 0.0f;
				yMaxPos				= 100.0f;
				ySpanPos			= 100.0f;
				xSpanValue			= 0.0f;
				ySpanValue			= 0.0;
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

			int & Slider2D::getX_ValuePtr() 		{	return *xValuePtr;	}
			int Slider2D::getX_Value()				{	return *xValuePtr;	}
			void Slider2D::setX_ValuePtr(int *xPtr) {
				if(bLocalXValue && xValuePtr != nullptr)
					delete xValuePtr;
				bLocalXValue = false;
				xValuePtr = xPtr;
			}

			int & Slider2D::getY_ValuePtr()			{	return *yValuePtr;	}
			int Slider2D::getY_Value()				{	return *yValuePtr;	}
			void Slider2D::setY_ValuePtr(int *yPtr) {
				if(bLocalYValue && yValuePtr != nullptr)
					delete yValuePtr;
				bLocalYValue = false;
				yValuePtr = yPtr;
			}

			void Slider2D::init() {
				this->id = IDs.create();

				// Setup contraints
				if(bHasParent) {
					con->scroll.bind(*parent);
					con->exec(*parent);
				}
				else con->exec();

				// FIXME: Create SOUNDS enumeration
				initSound(3, 7, 8, -1, 0, false, true);

				update();
				setX_Value(*this->xValuePtr);
				setY_Value(*this->yValuePtr);

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
				xMinPos = this->con->pos.x-(this->con->size.x/2.0f);
				xMaxPos = this->con->pos.x+(this->con->size.x/2.0f);
				xSpanPos = abs(xMaxPos - xMinPos)-this->con->control.size.x;
				xSpanValue = abs(this->con->xMaxValue - this->con->xMinValue);

				yMinPos = -this->con->pos.y+(this->con->size.y/2.0f);
				yMaxPos = -this->con->pos.y-(this->con->size.y/2.0f);
				ySpanPos = abs(yMinPos - yMaxPos)-this->con->control.size.y;
				ySpanValue = abs(this->con->yMaxValue - this->con->yMinValue);
			}

			void Slider2D::setX_Value() {
				setX_Value(*this->xValuePtr);
			}

			void Slider2D::setY_Value() {
				setY_Value(*this->yValuePtr);
			}

			void Slider2D::setX_Value(int xVal) {
				if(this->con->xMinValue<this->con->xMaxValue)	*this->xValuePtr = std::max( std::min( xVal, this->con->xMaxValue ), this->con->xMinValue );
				else											*this->xValuePtr = std::max( std::min( xVal, this->con->xMinValue ), this->con->xMaxValue );

				float f1 = getNormalized(*this->xValuePtr, this->con->xMinValue, this->con->xMaxValue);
				int i2 = xSpanPos;
				int i3 = 0.0f;
				int i4 = this->con->size.x/2.0f;
				int i5 = f1 * i2 + i3 - i4;

				currentPos.x = i5+(this->con->control.size.x/2.0f);
			}

			void Slider2D::setY_Value(int yVal) {
				if(this->con->yMinValue<this->con->yMaxValue)	*this->yValuePtr = std::max( std::min( yVal, this->con->yMaxValue ), this->con->yMinValue );
				else											*this->yValuePtr = std::max( std::min( yVal, this->con->yMinValue ), this->con->yMaxValue );

				float f1 = getNormalized(*this->yValuePtr, this->con->yMinValue, this->con->yMaxValue);
				int i2 = ySpanPos;
				int i3 = 0.0f;
				int i4 = this->con->size.y/2.0f;
				int i5 = f1 * i2 + i3 - i4;

				currentPos.y = i5+(this->con->control.size.y/2.0f);
			}

			float Slider2D::getNormalized(int iCurrent, int iMin, int iMax) {
				float f = fmin( fmax( float(iCurrent-iMin)/float(iMax-iMin), 0.0f), 1.0f);
				return f;
			}

			void Slider2D::updateControlPos() {
				*this->xValuePtr = getX_ValueFromPos(Core::mouse->x);
				*this->yValuePtr = getY_ValueFromPos(Core::mouse->y);
				setX_Value();
				setY_Value();
			}

			int Slider2D::getX_ValueFromPos(int xVal) {
				int i0, i2, i3, i4, i5;
				float f1;
				i0 = xVal;

				if(parent!=nullptr && parent->scroll.getEnabled()) i0 += con->scroll.getX();
				if(this->con->xMinValue<this->con->xMaxValue)
					f1 = getNormalized(i0-Core::gameVars->screen.half.x, xMinPos, xMaxPos);
				else
					f1 = getNormalized(i0-Core::gameVars->screen.half.x, xMaxPos, xMinPos);

				i2 = xSpanValue;

				if(this->con->xMinValue<this->con->xMaxValue)
					i3 = this->con->xMinValue;
				else
					i3 = this->con->xMaxValue;

				i4 = 0.0f;
				i5 = f1 * i2 + i3 - i4;

//				debug.log("X: i0 = "+std::to_string(i0)+", f1 = "+std::to_string(f1)+", i2 = "+std::to_string(i2)+", i3 = "+std::to_string(i3)+", i4 = "+std::to_string(i4)+", i5 = "+std::to_string(i5));
				return int(i5/this->con->vStep[0])*this->con->vStep[0];		// Constrain value to minimum step size
//				return i5;
			}

			int Slider2D::getY_ValueFromPos(int yVal) {
				int i0, i2, i3, i4, i5;
				float f1;
				i0 = yVal;

				if(parent!=nullptr && parent->scroll.getEnabled()) i0 += con->scroll.getY();
				if(this->con->yMinValue<this->con->yMaxValue)
					f1 = getNormalized(i0-Core::gameVars->screen.half.y, yMinPos, yMaxPos);
				else
					f1 = getNormalized(i0-Core::gameVars->screen.half.y, yMaxPos, yMinPos);

				i2 = ySpanValue;

				if(this->con->yMinValue<this->con->yMaxValue)
					i3 = this->con->yMinValue;
				else
					i3 = this->con->yMaxValue;

				i4 = 0.0f;
				i5 = f1 * i2 + i3 - i4;

//				debug.log("Y: i0 = "+std::to_string(i0)+", f1 = "+std::to_string(f1)+", i2 = "+std::to_string(i2)+", i3 = "+std::to_string(i3)+", i4 = "+std::to_string(i4)+", i5 = "+std::to_string(i5));
				return int(i5/this->con->vStep[0])*this->con->vStep[0];		// Constrain value to minimum step size
//				return i5;
			}

			void Slider2D::updateInput() {

				// If THIS object is active, then monitor for input
//				if(this->bFocusPresent && (this->sActiveObject == this->id)) {
					SDL_PumpEvents();
					keyboard.event = SDL_GetKeyboardState(NULL);
					keyboard.update();

					int xModVal = this->con->vStep[1];
					int yModVal = this->con->vStep[1];

					const Uint8 *keyState = SDL_GetKeyboardState(NULL);
					if (keyState[SDL_SCANCODE_LSHIFT] || keyState[SDL_SCANCODE_RSHIFT]) {
						xModVal = this->con->vStep[2];
						yModVal = this->con->vStep[2];
					}
					else if (keyState[SDL_SCANCODE_LCTRL] || keyState[SDL_SCANCODE_RCTRL]) {
						xModVal = this->con->vStep[0];
						yModVal = this->con->vStep[0];
					}

					if(this->con->xMinValue > this->con->xMaxValue)	xModVal = -xModVal;
					if(this->con->yMinValue > this->con->yMaxValue)	yModVal = -yModVal;

					//case Core::_Mouse::MOUSE_WHEEL_DOWN:	*this->valuePtr -= modVal;	break;

					if (keyboard.keys[SDLK_LEFT].bActive) {
						*this->xValuePtr -= xModVal;
					}
					if (keyboard.keys[SDLK_RIGHT].bActive) {
						*this->xValuePtr += xModVal;
					}

					if (keyboard.keys[SDLK_UP].bActive) {
						*this->yValuePtr += yModVal;
					}
					if (keyboard.keys[SDLK_DOWN].bActive) {
						*this->yValuePtr -= yModVal;
					}
//				}

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
							updateInput();
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
//					debug.log("x = "+std::to_string(*this->xValuePtr)+", xMin = "+std::to_string(xMinPos)+", xMax = "+std::to_string(xMaxPos)+", xSpanPos = "+std::to_string(xSpanPos)+", xSpanVal = "+std::to_string(xSpanValue));
//					debug.log("y = "+std::to_string(*this->yValuePtr)+", yMin = "+std::to_string(yMinPos)+", yMax = "+std::to_string(yMaxPos)+", ySpanPso = "+std::to_string(ySpanPos)+", ySpanVal = "+std::to_string(ySpanValue));


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
					if(this->eObjectState&STATE_ACTIVE) {
						updateControlPos();
					}
					else {
						setX_Value();
						setY_Value();
					}

					// Check if value has changed
//					if(lastValue != *this->valuePtr) {
//						this->bStateChanged = true;
//					}
//					lastValue = *this->valuePtr;

					// Draw Slider
					slider.exec(this->eObjectState);

					// Draw Control
					control.con->setPos(currentPos);
					control.exec(this->eObjectState);

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
