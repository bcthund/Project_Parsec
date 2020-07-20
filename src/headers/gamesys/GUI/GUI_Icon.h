/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_ICON_H_
#define HEADERS_GAMESYS_GUI_ICON_H_

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
//#include "../core/core_functions.h"
//#include "../core/vao.h"
//#include "../core/matrix.h"
//#include "../core/shader.h"
//#include "../core/timer.h"
//#include "../../core/InputSys.h"
#include "../../core/Colors.h"
#include "../../gamesys/gameVars.h"
#include "../../gamesys/IconSys.h"
#include "GUI_Constraint.h"
#include "GUI_ToolTip.h"
#include "GUI_Objects.h"
#include "GUI_Window.h"

namespace Core {
	namespace GUI {
		namespace Object {
			class Icon : public Base::Interactive<Props_Icon, bool>, public Base::AudioFeedback {
				public:
					Icon();
					Icon(std::string n, bool b, Props_Icon c);
					Icon(std::string n, bool b, Props_Icon *c);
					Icon(Props &p, std::string n, bool b, Props_Icon c);
					Icon(Props &p, std::string n, bool b, Props_Icon *c);

					Icon(std::string n, bool *b, Props_Icon c);
					Icon(std::string n, bool *b, Props_Icon *c);
					Icon(Props &p, std::string n, bool *b, Props_Icon c);
					Icon(Props &p, std::string n, bool *b, Props_Icon *c);
					virtual ~Icon();

					ToolTip toolTip;
					void init();
					void exec(iState eExternState=STATE_NONE);
					void execToolTip();
					void updateNoFocus();

				private:
					Window background;
					Label	*label;
					void updateObjectState(iState eExternState);
			};

			Icon::Icon() {
				label = nullptr;
			}

			Icon::Icon(std::string n, bool b, Props_Icon c) {
				name			= n;
				label			= nullptr;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= true;
				con				= new Props_Icon();
				*con			= c;
				bIsGrouped		= (c.iGroup>0);

				bLocalValue		= true;
				valuePtr		= new bool(b);
				if(b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;
			}

			Icon::Icon(Props &p, std::string n, bool b, Props_Icon c) {
				name			= n;
				label			= nullptr;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= true;
				con				= new Props_Icon();
				*con			= c;
				bIsGrouped		= (c.iGroup>0);

				bLocalValue		= true;
				valuePtr		= new bool(b);
				if(b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;
			}

			Icon::Icon(std::string n, bool b, Props_Icon *c) {
				name			= n;
				label			= nullptr;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= false;
				con				= c;
				bIsGrouped		= (c->iGroup>0);

				bLocalValue		= true;
				valuePtr		= new bool(b);
				if(b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;
			}

			Icon::Icon(Props &p, std::string n, bool b, Props_Icon *c) {
				name			= n;
				label			= nullptr;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= false;
				con				= c;
				bIsGrouped		= (c->iGroup>0);

				bLocalValue		= true;
				valuePtr		= new bool(b);
				if(b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;
			}

			Icon::Icon(std::string n, bool *b, Props_Icon c) {
				name			= n;
				label			= nullptr;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= true;
				con				= new Props_Icon();
				*con			= c;
				bIsGrouped		= (c.iGroup>0);

				bLocalValue		= false;
				valuePtr		= b;
				if(*b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;
			}

			Icon::Icon(Props &p, std::string n, bool *b, Props_Icon c) {
				name			= n;
				label			= nullptr;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= true;
				con				= new Props_Icon();
				*con			= c;
				bIsGrouped		= (c.iGroup>0);

				bLocalValue		= false;
				valuePtr		= b;
				if(*b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;
			}

			Icon::Icon(std::string n, bool *b, Props_Icon *c) {
				name			= n;
				label			= nullptr;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= false;
				con				= c;
				bIsGrouped		= (c->iGroup>0);

				bLocalValue		= false;
				valuePtr		= b;
				if(*b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;
			}

			Icon::Icon(Props &p, std::string n, bool *b, Props_Icon *c) {
				name			= n;
				label			= nullptr;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= false;
				con				= c;
				bIsGrouped		= (c->iGroup>0);

				bLocalValue		= false;
				valuePtr		= b;
				if(*b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;
			}

			Icon::~Icon() {
				if(bLocalCon && con != nullptr) delete con;
				if(bLocalValue && valuePtr != nullptr) delete valuePtr;
				if(label != nullptr) delete label;
			}

			/** ******************************************************************************************************************************
			 *
			 * ****************************************************************************************************************************** */
			void Icon::init() {
				Interactive::init(con);

				// FIXME: Create SOUNDS enumeration
				initSound(2, 5, 6, 0, 0, true, true);

				// Setup button contraints
				if(bHasParent) con->exec(*parent);
				else con->exec();

				con->background.setPadding(5);
//				con->background.setWidth(con->size.constraint.x+(con->background.border*2), con->size.constraint.xType);	// FIXME ? Use only normal border?
//				con->background.setHeight(con->size.constraint.y+(con->background.border*2), con->size.constraint.yType);	// FIXME ? Use only normal border?
				con->background.setWidth(con->size.constraint.x, con->size.constraint.xType);
				con->background.setHeight(con->size.constraint.y, con->size.constraint.yType);
				background = Object::Window(*con, name, &con->background);
				background.init();

				if(con->bShowLabel) {
					label = new Label(*con, name, con->label);
					label->init();
				}

				toolTip.init(*con, name);

				bInit = true;
			}

			/** ******************************************************************************************************************************
			 *
			 * ****************************************************************************************************************************** */
			void Icon::updateObjectState(iState eExternState) {
				// Check for external state change, return early
				if(*valuePtr && !(this->eObjectState&STATE_ACTIVE)) {
					this->eObjectState = STATE_ACTIVE;
				}
				else if(*valuePtr==*returnState[0].off && (this->eObjectState&STATE_ACTIVE)) {
					this->eObjectState = STATE_NONE;
				}

				if(eExternState!=STATE_NONE && !(eExternState&STATE_UPDATE)) {
					eObjectState = eExternState;
				}
				else {
					if(!(eExternState&STATE_UPDATE)) {
						mState = Core::mouse->checkInput(gameVars->screen.half.x+con->pos.x, gameVars->screen.half.y-con->pos.y, con->size.x, con->size.y);
					}
					else this->mState = Core::_Mouse::MOUSE_NONE;

					if(enabled()) {
						if(con->buttonType==BUTTON_ONESHOT)  {
							if ( (mState == Core::_Mouse::MOUSE_LEFT) && !bRepeatStatus) {
								eObjectState = STATE_ACTIVE;
								bRepeatStatus = true;
								Sound_PlayOn();
							}
							else if (mState == Core::_Mouse::MOUSE_HOVER) {
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
							if(bIsGrouped && (eObjectState&STATE_ACTIVE) && (sGroupObject[con->iGroup]!=name && sGroupObject[con->iGroup]!="")) {
								eObjectState = STATE_NONE;
								Sound_AbortState();
							}
							else if (mState == Core::_Mouse::MOUSE_LEFT) {
								if(eObjectState&STATE_ACTIVE) {
									eObjectState = STATE_NONE;
									if(sGroupObject[con->iGroup]==name) sGroupObject[con->iGroup] = "";
									Sound_PlayOff();
								}
								else if(eObjectState&STATE_HOVER) {
									eObjectState = STATE_ACTIVE;
									sGroupObject[con->iGroup] = name;
									Sound_PlayOn();
								}
								else {
									// Do not report mouse click if group disabled
									mState = Core::_Mouse::MOUSE_NONE;
								}
							}
							else if (!(eObjectState&STATE_ACTIVE) && mState == Core::_Mouse::MOUSE_HOVER) {
								eObjectState = STATE_HOVER;
							}
							else if (!(eObjectState&STATE_ACTIVE) && mState == Core::_Mouse::MOUSE_NONE) {
								eObjectState = STATE_NONE;
//								Sound_PlayOff();
							}
						}
						else {
							if (mState == Core::_Mouse::MOUSE_LEFT_DOWN && !bRepeatStatus) {
								eObjectState = STATE_ACTIVE;
								bRepeatStatus = true;
								Sound_PlayOn();

								if(con->buttonType==BUTTON_DEBOUNCE) {
									debounceTimer.start();
								}
							}
							else if (mState == Core::_Mouse::MOUSE_LEFT_DOWN && bRepeatStatus) {
								eObjectState = STATE_NONE;
								if(con->buttonType==BUTTON_DEBOUNCE) {
									if (debounceTimer.split() >= con->debounceTime) eObjectState = STATE_ACTIVE;
								}
							}
							else if (mState == Core::_Mouse::MOUSE_HOVER) {
								eObjectState = STATE_HOVER;
								bRepeatStatus = false;
							}
							else if (mState == Core::_Mouse::MOUSE_NONE) {
								eObjectState = STATE_NONE;
								bRepeatStatus = false;
								Sound_PlayOff();
							}
						}
					}
					else this->eObjectState = STATE_NONE;

					// Allow mouse hover at any time (used for tooltips)
					if(!(eExternState&STATE_UPDATE)) {
						if(mState==Core::_Mouse::MOUSE_HOVER) eObjectState = eObjectState|STATE_HOVER;
						else eObjectState = eObjectState&~STATE_HOVER;
					}
				}

				// Allow mouse hover when active
				if( (this->eObjectState&STATE_ACTIVE) && (mState==Core::_Mouse::MOUSE_HOVER) ) {
					this->eObjectState = this->eObjectState | STATE_HOVER;
				}
				else if( (this->eObjectState&STATE_ACTIVE) && (this->eObjectState&STATE_HOVER) && (mState!=Core::_Mouse::MOUSE_HOVER) ) {
					this->eObjectState = STATE_ACTIVE;
				}

				if(!enabled()) eObjectState |= STATE_DISABLED;
				updateValuePtr();
			}

			/** ******************************************************************************************************************************
			 *
			 * ****************************************************************************************************************************** */
			void Icon::exec(iState eExternState) {
				if(bInit && con->visibility && ((parent!=nullptr && parent->visibility) || (parent==nullptr))) {
					// Update constraints
					if(bHasParent) con->exec(*parent);
					else con->exec();

					if(!bFocusPresent) {
						updateObjectState(eExternState);

						if(con->toolTip.bShow) toolTip.updateObjectState(eObjectState);
						else toolTip.updateObjectState(STATE_NONE);
					}

					// Draw button window
					if(con->bShowBackground) background.exec(eObjectState);

					// Draw Icon
					int iconID = con->iconID.base;

					if(eObjectState&STATE_DISABLED) {
						if(eObjectState&STATE_HOVER)	colors.PushFront(gameVars->pallette.gui.disabled.text.hover);
						else							colors.PushFront(gameVars->pallette.gui.disabled.text.base);
					}
					else if(eObjectState&STATE_ACTIVE) { colors.PushFront(*con->color.icon().active); iconID = con->iconID.active; }
					else if(eObjectState&STATE_HOVER) { colors.PushFront(*con->color.icon().highlight); iconID = con->iconID.highlight; }
					else colors.PushFront(*con->color.icon().base);

					iconSys->draw(con, con->iconAtlas, iconID, 64);
					colors.PopFront();

					// Draw Label if enabled (Draw last so appears on top of icon)
					if(con->bShowLabel) label->exec();
				}
			}

			void Icon::execToolTip() {
				toolTip.exec();
			}

			/***
			 * \brief Calls to run when object not visible/not in focus. This function is especially
			 * 		  important for Buttons because of the call to updateValuePtr();
			 * @tparam T
			 * @tparam T
			 */
			void Icon::updateNoFocus() {
				updateObjectState(STATE_UPDATE);
				updateValuePtr();
			}

		}
	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_ICON_H_ */
