/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_BUTTON_H_
#define HEADERS_GAMESYS_GUI_BUTTON_H_

/*
 * Creates GUI instances for particular objects that can be
 * used as a building block for a full GUI.
 *
 * These classes draw the objects and handle IO, as well as
 * 	providing "focus" tracking.
 * 		- Focus may be achieved with a static INT that
 * 			contains an ID. The ID will represent the
 * 			active object.
 * 		- Focus should be handled with a "history" so when
 * 			an object releases focus the previous object in
 * 			history gets focus back.
 */

#include <iostream>
#include "../../core/Groups.h"
#include "../../core/InputSys.h"
#include "../../core/Colors.h"
#include "../../gamesys/gameVars.h"
#include "GUI_Constraint.h"
#include "GUI_Objects.h"
#include "GUI_Window.h"
#include "GUI_ToolTip.h"

namespace Core {
	namespace GUI {
		namespace Object {
			class Button : virtual public Base::Interactive<Props_Button>, public Base::AudioFeedback {
				public:
					Button();
					Button(std::string n, bool b, Props_Button &c);
					Button(std::string n, bool b, Props_Button *c);
					Button(Props &p, std::string n, bool b, Props_Button &c);
					Button(Props &p, std::string n, bool b, Props_Button *c);

					Button(std::string n, bool *b, Props_Button &c);
					Button(std::string n, bool *b, Props_Button *c);
					Button(Props &p, std::string n, bool *b, Props_Button &c);
					Button(Props &p, std::string n, bool *b, Props_Button *c);

					virtual ~Button();

					ToolTip toolTip;
					void init();
					void exec(iState eExternState=STATE_NONE);
					void execToolTip();
					void updateNoFocus();

				private:
//					Window win;
					//mState			= Core::_Mouse::MOUSE_NONE;
				public:
					Window win;
					void updateObjectState(iState eExternState);
//					void updateScroll();
			};

			Button::Button() {}

			Button::Button(std::string n, bool b, Props_Button &c) {
				name			= n;

				bRepeatStatus	= false;
				bIsGrouped		= (c.iGroup>0);

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= true;
				con				= new Props_Button();
				*con			= c;
				if(con->text == "") con->text = n;

				bLocalState		= true;
				statePtr		= new bool(b);
				if(b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;
			}

			Button::Button(Props &p, std::string n, bool b, Props_Button &c) {
				name			= n;
				bRepeatStatus	= false;
				bIsGrouped		= (c.iGroup>0);

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= true;
				con				= new Props_Button();
				*con			= c;
				if(con->text == "") con->text = n;

				bLocalState		= true;
				statePtr		= new bool(b);
				if(b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;
			}

			Button::Button(std::string n, bool b, Props_Button *c) {
				name			= n;
				bRepeatStatus	= false;
				bIsGrouped		= (c->iGroup>0);

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

				bLocalState		= true;
				statePtr		= new bool(b);
				if(b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;
			}

			Button::Button(Props &p, std::string n, bool b, Props_Button *c) {
				name			= n;
				bRepeatStatus	= false;
				bIsGrouped		= (c->iGroup>0);

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= false;
				con				= c;

				bLocalState		= true;
				statePtr		= new bool(b);
				if(b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;
			}

			Button::Button(std::string n, bool *b, Props_Button &c) {
				name			= n;
				bRepeatStatus	= false;
				bIsGrouped		= (c.iGroup>0);

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= true;
				con				= new Props_Button();
				*con			= c;
				if(con->text == "") con->text = n;

				bLocalState		= false;
				statePtr		= b;
				if(*b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;
			}

			Button::Button(Props &p, std::string n, bool *b, Props_Button &c) {
				name			= n;

				bRepeatStatus	= false;
				bIsGrouped		= (c.iGroup>0);

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= true;
				con				= new Props_Button();
				*con			= c;
				if(con->text == "") con->text = n;

				bLocalState		= false;
				statePtr		= b;
				if(*b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;
			}

			Button::Button(std::string n, bool *b, Props_Button *c) {
				name			= n;
				bRepeatStatus	= false;
				bIsGrouped		= (c->iGroup>0);

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

				bLocalState		= false;
				statePtr		= b;
				if(*b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;
			}

			Button::Button(Props &p, std::string n, bool *b, Props_Button *c) {
				name			= n;
				bRepeatStatus	= false;
				bIsGrouped		= (c->iGroup>0);

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

				bLocalState		= false;
				statePtr		= b;
				if(*b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;
			}

			Button::~Button() {
				if(bLocalCon && con != nullptr) delete con;
			}

			void Button::init() {
				this->id = IDs.create();

				initSound(audio.channel().CHANNEL_2_GUI_BUTTON, 1, 2, 0, 0, true, true);

				if(bHasParent) {
					con->scroll.bind(*parent);
					con->exec(*parent);
				}
				else con->exec();

				// Create button window with contraints to parent if present
				if (bHasParent) win = Object::Window(*parent, name, con);
				else win = Object::Window(name, con);
				win.init();

				// Other items
				timeFocusDebounce.start();
				toolTip.init(*con, name);

				bInit = true;
			}

			void Button::updateObjectState(iState eExternState) {
				// Check for external state change
				checkStatePtr();

				// Check external object state or update button state
				if((eExternState!=STATE_NONE) && !(eExternState&STATE_UPDATE)) {
					eObjectState = eExternState;
				}
				else {
					if(!(eExternState&STATE_UPDATE)) {
						Vector2f vPos = con->getScrollPos();
						mState = Core::mouse->checkInput(gameVars->screen.half.x+vPos.x, gameVars->screen.half.y-vPos.y, con->size.x, con->size.y);
						//mState = Core::mouse->checkInput(gameVars->screen.half.x+con->pos.x, gameVars->screen.half.y-con->pos.y, con->size.x, con->size.y);
					}
					else mState = Core::_Mouse::MOUSE_NONE;

					if(enabled()) {
						if(con->buttonType==BUTTON_ONESHOT)  {
							if ( (mState&Core::_Mouse::MOUSE_LEFT) && !bRepeatStatus) {
								eObjectState = STATE_ACTIVE;
								bRepeatStatus = true;
								Sound_PlayOn();
							}
							else if (mState&Core::_Mouse::MOUSE_HOVER) {
								eObjectState = STATE_HOVER;
								bRepeatStatus = false;
							}
							else if (bRepeatStatus) {
								eObjectState = STATE_NONE;
							}
							else if (mState == Core::_Mouse::MOUSE_NONE) {
								eObjectState = STATE_NONE;
								bRepeatStatus = false;
								Sound_PlayOff();
							}
						}
						else if(con->buttonType==BUTTON_TOGGLE) {
							if(bIsGrouped && (eObjectState&STATE_ACTIVE) && (Core::groups[con->iGroup].object!=id && Core::groups[con->iGroup].object!="")) {
								eObjectState = STATE_NONE;
								Sound_AbortState();
							}
							else if (mState&Core::_Mouse::MOUSE_LEFT) {
								if(eObjectState&STATE_ACTIVE) {
									if (!bIsGrouped || (bIsGrouped && !Core::groups[con->iGroup].bExclusive)) eObjectState = STATE_NONE;
									if(bIsGrouped && Core::groups[con->iGroup].object==id) Core::groups[con->iGroup].object = "";
									Sound_PlayOff();
								}
								else if(!(eObjectState&STATE_ACTIVE)) {
									eObjectState = STATE_ACTIVE;
									if(bIsGrouped) Core::groups[con->iGroup].object = id;
									Sound_PlayOn();
								}
								else {
									// Do not report mouse click if group disabled
									mState = Core::_Mouse::MOUSE_NONE;
								}
							}
							else if (!(eObjectState&STATE_ACTIVE) && (mState&Core::_Mouse::MOUSE_HOVER)) {
								eObjectState = STATE_HOVER;
							}
							else if (!(eObjectState&STATE_ACTIVE) && (mState == Core::_Mouse::MOUSE_NONE)) {
								eObjectState = STATE_NONE;
							}
						}
						else {
							if ((mState&Core::_Mouse::MOUSE_LEFT_DOWN) && !bRepeatStatus) {
								eObjectState = STATE_ACTIVE;
								bRepeatStatus = true;
								Sound_PlayOn();

								if(con->buttonType==BUTTON_DEBOUNCE) {
									debounceTimer.start();
								}
							}
							else if ((mState&Core::_Mouse::MOUSE_LEFT_DOWN) && bRepeatStatus) {
								eObjectState = STATE_NONE;
								if(con->buttonType==BUTTON_DEBOUNCE) {
									if (debounceTimer.split() >= con->debounceTime) eObjectState = STATE_ACTIVE;
								}
							}
							else if (mState&Core::_Mouse::MOUSE_HOVER) {
								eObjectState = STATE_HOVER;
								bRepeatStatus = false;
							}
							else if (mState == Core::_Mouse::MOUSE_NONE) {
								eObjectState = STATE_NONE;
								bRepeatStatus = false;
							}
						}
					}
					else {
						eObjectState = STATE_NONE;
					}

					// Allow mouse hover at any time (used for tooltips)
					if(!(eExternState&STATE_UPDATE)) {
						if(mState&Core::_Mouse::MOUSE_HOVER) eObjectState = eObjectState|STATE_HOVER;
						else eObjectState = eObjectState&~STATE_HOVER;
					}

					// Report if mouse is in button space (debounce turning off)
					if(!(mState&Core::_Mouse::MOUSE_NONE)) { eObjectState = eObjectState|STATE_FOCUS; timeFocusDebounce.split(); }
					else if (timeFocusDebounce.get_splitdiff() > iFocusDebounce) eObjectState = eObjectState&~STATE_FOCUS;
				}

				if(!enabled()) eObjectState |= STATE_DISABLED;

				updateStatePtr();
			}

			void Button::exec(iState eExternState) {
				if(bInit) {
					if(con->visibility && ((parent!=nullptr && parent->visibility) || (parent==nullptr))) {

						// Update constraints
						if(bHasParent) con->exec(*parent);
						else con->exec();

						if((con->bFocusLock && !bFocusPresent) || !con->bFocusLock || (sActiveObject==id)) {
							updateObjectState(eExternState);
							if(con->toolTip.bShow) toolTip.updateObjectState(eObjectState);
							else toolTip.updateObjectState(STATE_NONE);
						}

						// Draw button window
						win.exec(eObjectState);

						// Draw button text
						if(eObjectState&STATE_DISABLED) {
							if(eObjectState&STATE_HOVER)	colors.PushFront(gameVars->pallette.gui.disabled.text.hover);
							else							colors.PushFront(gameVars->pallette.gui.disabled.text.base);
						}
						else if(eObjectState&STATE_ACTIVE) colors.PushFront(*con->colorText.active);
						else if(eObjectState&STATE_HOVER) colors.PushFront(*con->colorText.highlight);
						else colors.PushFront(*con->colorText.base);

						textSys->draw(con, con->text, con->eLabelAnchor);
						colors.PopFront();
					}
				}
			}

			void Button::execToolTip() {
				toolTip.exec();
			}

			/***
			 * \brief Calls to run when object not visible/not in focus. This function is especially
			 * 		  important for Buttons because of the call to updateValuePtr();
			 */
			void Button::updateNoFocus() {
				updateObjectState(STATE_UPDATE);
				updateStatePtr();
			}

		}
	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_BUTTON_H_ */
