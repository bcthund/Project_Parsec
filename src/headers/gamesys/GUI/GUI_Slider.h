/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_SLIDER_H_
#define HEADERS_GAMESYS_GUI_SLIDER_H_

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
			template <typename T>
//			class Slider : public Base::Interactive<Props_Slider, T>, public Base::AudioFeedback {
			class Slider : public Base::Interactive<Props_Slider>, public Base::AudioFeedback {
					friend class AnySlider;
				public:
					Slider();
					Slider(std::string n, T *ptr, Props_Slider &c);
					Slider(std::string n, T *ptr, Props_Slider *c);
					Slider(Props &p, std::string n, T *ptr, Props_Slider &c);
					Slider(Props &p, std::string n, T *ptr, Props_Slider *c);

					Slider(std::string n, T t, Props_Slider &c);
					Slider(std::string n, T t, Props_Slider *c);
					Slider(Props &p, std::string n, T t, Props_Slider &c);
					Slider(Props &p, std::string n, T t, Props_Slider *c);
					virtual ~Slider();

					T *valuePtr;
					bool bLocalValue;
					void setValuePtr(T *ptr);
					T & getValuePtr();
					T getValue();

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
				valuePtr			= nullptr;
				bLocalValue			= true;
			}

			template <class T> Slider<T>::Slider(std::string n, T *ptr, Props_Slider &c) {
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

				this->bLocalState	= true;
				this->statePtr		= new bool(false);

				this->bLocalValue	= false;
				this->valuePtr		= ptr;

				this->bLocalCon		= true;
				this->con			= new Props_Slider();
				*this->con			= c;
				if(this->con->text == "") this->con->text = n;
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

				this->bLocalState	= true;
				this->statePtr		= new bool(false);

				this->bLocalValue	= false;
				this->valuePtr		= ptr;

				this->bLocalCon		= false;
				this->con			= c;
				if(this->con->text == "") this->con->text = n;
			}

			template <class T> Slider<T>::Slider(Props &p, std::string n, T *ptr, Props_Slider &c) {
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

				this->bLocalState	= true;
				this->statePtr		= new bool(false);

				this->bLocalValue	= false;
				this->valuePtr		= ptr;

				this->bLocalCon		= true;
				this->con			= new Props_Slider();
				*this->con			= c;
				if(this->con->text == "") this->con->text = n;
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

				this->bLocalState	= true;
				this->statePtr		= new bool(false);

				this->bLocalValue	= false;
				this->valuePtr		= ptr;

				this->bLocalCon		= false;
				this->con			= c;
				if(this->con->text == "") this->con->text = n;
			}

			template <class T> Slider<T>::Slider(std::string n, T t, Props_Slider &c) {
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

				this->bLocalState	= true;
				this->statePtr		= new bool(false);

				this->bLocalValue	= true;
				this->valuePtr		= new T(t);

				this->bLocalCon		= true;
				this->con			= new Props_Slider();
				*this->con			= c;
				if(this->con->text == "") this->con->text = n;
			}

			template <class T> Slider<T>::Slider(std::string n, T t, Props_Slider *c) {
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

				this->bLocalState	= true;
				this->statePtr		= new bool(false);

				this->bLocalValue	= true;
				this->valuePtr		= new T(t);

				this->bLocalCon		= false;
				this->con			= c;
				if(this->con->text == "") this->con->text = n;
			}

			template <class T> Slider<T>::Slider(Props &p, std::string n, T t, Props_Slider &c) {
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

				this->bLocalState	= true;
				this->statePtr		= new bool(false);

				this->bLocalValue	= true;
				this->valuePtr		= new T(t);

				this->bLocalCon		= true;
				this->con			= new Props_Slider();
				*this->con			= c;
				if(this->con->text == "") this->con->text = n;
			}

			template <class T> Slider<T>::Slider(Props &p, std::string n, T t, Props_Slider *c) {
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

				this->bLocalState	= true;
				this->statePtr		= new bool(false);

				this->bLocalValue	= true;
				this->valuePtr		= new T(t);

				this->bLocalCon		= false;
				this->con			= c;
				if(this->con->text == "") this->con->text = n;
			}

			template <class T> Slider<T>::~Slider() {
				if(this->bLocalCon && this->con != nullptr) delete this->con;
				if(this->bLocalValue && this->valuePtr != nullptr) delete this->valuePtr;
				if(label != nullptr) delete label;
				if(field != nullptr) delete field;
			}

			template <class T> void Slider<T>::setValuePtr(T *ptr)	{
				if(bLocalValue && valuePtr != nullptr) delete valuePtr;
				bLocalValue = false;
				valuePtr = ptr;
			}

			template <class T> T & Slider<T>::getValuePtr()	{
				return *valuePtr;
			}

			template <class T> T Slider<T>::getValue()	{
				return *valuePtr;
			}

			template <class T> void Slider<T>::init() {
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

				initSound(audio.channel().CHANNEL_3_GUI_SLIDER, audio().AUDIO_6_GUI_SLIDER_ON, audio().AUDIO_7_GUI_SLIDER_OFF, -1, 0, true, true);

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
					if(this->con->toolTip.bShow) this->con->field.setToolTip(this->con->toolTip.Text);

					this->con->field.enablePadding(PADDING_POSITION);
					field = new Object::Field<T>(*this->con, this->name+"_Field", this->valuePtr, this->con->field);	// Must add "_Field" or conflict occurs with active object states
					field->init();
				}

				// Update position according to field and label, this is a one-time thing


				// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
				// 			Slider and Control
				// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
				if(this->bHasParent) slider = Window(*this->parent, this->name, this->con);
				else slider = Window(this->name, this->con);
				slider.init();

//				control = Window(*this->con, this->name, &this->con->control);
				//this->con->control.scroll.bind(*this->con);
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
				float f0, f1, f2, f3, f4, f5;
				f0 = f;
				if(this->con->orientation == Core::GUI::SLIDER_HORIZONTAL)	{
					if(parent!=nullptr && parent->scroll.getEnabled()) f0 += con->scroll.getX();
					if(this->con->minValue<this->con->maxValue) {
						f1 = getNormalized(f0-Core::gameVars->screen.activeProjection->half.x, minPos, maxPos);
					}
					else {
						f1 = getNormalized(f0-Core::gameVars->screen.activeProjection->half.x, maxPos, minPos);
					}
				}
				else if(this->con->orientation == Core::GUI::SLIDER_VERTICAL)	{
					if(parent!=nullptr && parent->scroll.getEnabled()) f0 += con->scroll.getY();
					if(this->con->minValue<this->con->maxValue) {
						f1 = getNormalized(f0-Core::gameVars->screen.activeProjection->half.y, minPos, maxPos);
					}
					else {
						f1 = getNormalized(f0-Core::gameVars->screen.activeProjection->half.y, maxPos, minPos);
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

				return int(f5/this->con->vStep[0])*this->con->vStep[0];		// Constrain value to minimum step size
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

			template <class T> void Slider<T>::updateScrollMouse() {

				Core::_Mouse::MOUSE_STATE wheel = Core::mouse->checkWheel();

				if(wheel != Core::_Mouse::MOUSE_NONE) {
					T modVal = this->con->vStep[1];

					const Uint8 *keyState = SDL_GetKeyboardState(NULL);
					if (keyState[SDL_SCANCODE_LSHIFT] || keyState[SDL_SCANCODE_RSHIFT])		modVal = this->con->vStep[2];
					else if (keyState[SDL_SCANCODE_LCTRL] || keyState[SDL_SCANCODE_RCTRL])	modVal = this->con->vStep[0];

					if(this->con->minValue > this->con->maxValue) 	modVal = -modVal;

					switch(wheel) {
						case Core::_Mouse::MOUSE_WHEEL_UP:		*this->valuePtr += modVal;	break;
						case Core::_Mouse::MOUSE_WHEEL_DOWN:	*this->valuePtr -= modVal;	break;
					}
				}
			}

			template <class T> void Slider<T>::updateObjectState(iState eExternState) {
				if((eExternState!=STATE_NONE) && !(eExternState&STATE_UPDATE)) {
					this->eObjectState = eExternState;
				}
				else {
					if(!(eExternState&STATE_UPDATE)) {
						Vector2f vPos = slider.con->getScrollPos();
						Core::_Mouse::iMouseState test1 = Core::mouse->checkInput(gameVars->screen.activeProjection->half.x+vPos.x, gameVars->screen.activeProjection->half.y-vPos.y, slider.con->size.x, slider.con->size.y);

						vPos = control.con->getScrollPos();
						Core::_Mouse::iMouseState test2 = Core::mouse->checkInput(gameVars->screen.activeProjection->half.x+vPos.x, gameVars->screen.activeProjection->half.y-vPos.y, control.con->size.x, control.con->size.y);
						mState = test1 | test2;

						//Vector2f vPos = this->con->getScrollPos();
						//this->mState = Core::mouse->checkInput(gameVars->screen.activeProjection->half.x+vPos.x, gameVars->screen.activeProjection->half.y-vPos.y, this->con->size.x, this->con->size.y);
						//this->mState = Core::mouse->checkInput(gameVars->screen.activeProjection->half.x+this->con->pos.x, gameVars->screen.activeProjection->half.y-this->con->pos.y, std::max(this->con->size.x, this->con->control.size.x), std::max(this->con->size.y, this->con->control.size.y));
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
							Sound_StopOff();
							Sound_PlayOn();
						}
						else if(bHasFocus && (this->eObjectState&STATE_ACTIVE) && Core::mouse->checkState()!=Core::_Mouse::MOUSE_LEFT_DOWN) {
							bHasFocus = false;
							this->bFocusPresent = false;
							if(this->sActiveObject == this->id) this->sActiveObject = "";
							this->eObjectState = STATE_NONE;
							Sound_StopOn();
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
//						bValueChanged = true;
					}
					else setValue();

					// Check if value has changed
					if(lastValue != *this->valuePtr) {
						this->bStateChanged = true;
					}
					lastValue = *this->valuePtr;

					// Draw Slider
					slider.exec(this->eObjectState);

					// Draw Control
					control.con->setPos(currentPos);
					control.exec(this->eObjectState);
					//control.exec(STATE_NONE);

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
					void set(std::string n, float * fPtr, Props_Slider &c)				{	tag = FLOAT;	f = new Object::Slider<float>(n, fPtr, c);		}
					void set(std::string n, float * fPtr, Props_Slider *c)				{	tag = FLOAT;	f = new Object::Slider<float>(n, fPtr, c);		}
					void set(std::string n, int * iPtr, Props_Slider &c)				{	tag = INT;		i = new Object::Slider<int>(n, iPtr, c);		}
					void set(std::string n, int * iPtr, Props_Slider *c)				{	tag = INT;		i = new Object::Slider<int>(n, iPtr, c);		}

					void set(std::string n, float fVal, Props_Slider &c)				{	tag = FLOAT;	f = new Object::Slider<float>(n, fVal, c);			}
					void set(std::string n, float fVal, Props_Slider *c)				{	tag = FLOAT;	f = new Object::Slider<float>(n, fVal, c);			}
					void set(std::string n, int iVal, Props_Slider &c)					{	tag = INT;		i = new Object::Slider<int>(n, iVal, c);			}
					void set(std::string n, int iVal, Props_Slider *c)					{	tag = INT;		i = new Object::Slider<int>(n, iVal, c);			}

					void set(Props &p, std::string n, float * fPtr, Props_Slider &c)	{	tag = FLOAT;	f = new Object::Slider<float>(p, n, fPtr, c);	}
					void set(Props &p, std::string n, float * fPtr, Props_Slider *c)	{	tag = FLOAT;	f = new Object::Slider<float>(p, n, fPtr, c);	}
					void set(Props &p, std::string n, int * iPtr, Props_Slider &c)		{	tag = INT;		i = new Object::Slider<int>(p, n, iPtr, c);		}
					void set(Props &p, std::string n, int * iPtr, Props_Slider *c)		{	tag = INT;		i = new Object::Slider<int>(p, n, iPtr, c);		}

					void set(Props &p, std::string n, float fVal, Props_Slider &c)		{	tag = FLOAT;	f = new Object::Slider<float>(p, n, fVal, c);		}
					void set(Props &p, std::string n, float fVal, Props_Slider *c)		{	tag = FLOAT;	f = new Object::Slider<float>(p, n, fVal, c);		}
					void set(Props &p, std::string n, int iVal, Props_Slider &c)		{	tag = INT;		i = new Object::Slider<int>(p, n, iVal, c);		}
					void set(Props &p, std::string n, int iVal, Props_Slider *c)		{	tag = INT;		i = new Object::Slider<int>(p, n, iVal, c);		}

					Object::Slider<float>	* getF() {
						if(tag==FLOAT) return f;
						else throw std::runtime_error("Slider is not defined as float, did you mean to use getI()?");
					}
					Object::Slider<int>		* getI() {
						if(tag==INT) return i;
						else throw std::runtime_error("Slider is not defined as int, did you mean to use getF()?");
					}

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
						f->field->setValuePtr(fPtr);
					}

					void setPointer(int * iPtr) {
						tag = INT;
						i->valuePtr = iPtr;
						i->field->setValuePtr(iPtr);
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

					Core::_Mouse::iMouseState state() {
						switch(tag) {
							case FLOAT:	return f->mState; break;
							case INT:	return i->mState; break;
						}
						return Core::_Mouse::MOUSE_NONE;
					}

					bool stateChanged() {
						switch(tag) {
							case FLOAT: return f->stateChanged(); break;
							case INT: return i->stateChanged(); break;
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
