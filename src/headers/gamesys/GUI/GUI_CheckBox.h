/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_CHECKBOX_H_
#define HEADERS_GAMESYS_GUI_CHECKBOX_H_

#include <iostream>
//#include "../core/core_functions.h"
#include "../../core/InputSys.h"
//#include "../core/vao.h"
//#include "../core/matrix.h"
//#include "../core/shader.h"
#include "GUI_Constraint.h"
#include "GUI_ToolTip.h"
#include "GUI_Objects.h"
#include "GUI_Window.h"
#include "GUI_Label.h"

namespace Core {
	namespace GUI {
		namespace Object {
			class CheckBox : public Base::Interactive<Props_CheckBox>, public Base::AudioFeedback {
				public:
					CheckBox();
					CheckBox(std::string n, bool b, Props_CheckBox &c);
					CheckBox(Props &p, std::string n, bool b, Props_CheckBox &c);
					CheckBox(std::string n, bool b, Props_CheckBox *c);
					CheckBox(Props &p, std::string n, bool b, Props_CheckBox *c);

					CheckBox(std::string n, bool *b, Props_CheckBox &c);
					CheckBox(Props &p, std::string n, bool *b, Props_CheckBox &c);
					CheckBox(std::string n, bool *b, Props_CheckBox *c);
					CheckBox(Props &p, std::string n, bool *b, Props_CheckBox *c);
					virtual ~CheckBox();

					ToolTip toolTip;
					void init();
					void exec(iState eExternState=STATE_NONE);
					void execToolTip();
					void updateNoFocus();

				private:
					Window box;
					Window check;
					Label  * label;
					void update();
					void updateObjectState(iState eExternState);
			};

			CheckBox::CheckBox() {
				label			= nullptr;
			}

			CheckBox::CheckBox(std::string n, bool b, Props_CheckBox &c) {
				name			= n;
				bIsGrouped		= (c.iGroup>0);
				label			= nullptr;

				bHasParent		= false;
				parent			= nullptr;

				bLocalState		= true;
				statePtr		= new bool(b);
				if(b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;

				bLocalCon		= true;
				con				= new Props_CheckBox();
				*con			= c;
				if(con->text == "") con->text = n;
			}

			CheckBox::CheckBox(Props &p, std::string n, bool b, Props_CheckBox &c) {
				name			= n;
				bIsGrouped		= (c.iGroup>0);
				label			= nullptr;

				bHasParent		= true;
				parent			= &p;

				bLocalState		= true;
				statePtr		= new bool(b);
				if(b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;

				bLocalCon		= true;
				con				= new Props_CheckBox();
				*con			= c;
				if(con->text == "") con->text = n;
			}

			CheckBox::CheckBox(std::string n, bool b, Props_CheckBox *c) {
				name			= n;
				bIsGrouped		= (c->iGroup>0);
				label			= nullptr;

				bHasParent		= false;
				parent			= nullptr;

				bLocalState		= true;
				statePtr		= new bool(b);
				if(b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;
			}

			CheckBox::CheckBox(Props &p, std::string n, bool b, Props_CheckBox *c) {
				name			= n;
				bIsGrouped		= (c->iGroup>0);
				label			= nullptr;

				bHasParent		= true;
				parent			= &p;

				bLocalState		= true;
				statePtr		= new bool(b);
				if(b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;
			}

			CheckBox::CheckBox(std::string n, bool *b, Props_CheckBox &c) {
				name			= n;
				bIsGrouped		= (c.iGroup>0);
				label			= nullptr;

				bHasParent		= false;
				parent			= nullptr;

				bLocalState		= false;
				statePtr		= b;
				if(*b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;

				bLocalCon		= true;
				con				= new Props_CheckBox();
				*con			= c;
				if(con->text == "") con->text = n;
			}

			CheckBox::CheckBox(Props &p, std::string n, bool *b, Props_CheckBox &c) {
				name			= n;
				bIsGrouped		= (c.iGroup>0);
				label			= nullptr;

				bHasParent		= true;
				parent			= &p;

				bLocalState		= false;
				statePtr		= b;
				if(*b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;

				bLocalCon		= true;
				con				= new Props_CheckBox();
				*con			= c;
				if(con->text == "") con->text = n;
			}

			CheckBox::CheckBox(std::string n, bool *b, Props_CheckBox *c) {
				name			= n;
				bIsGrouped		= (c->iGroup>0);
				label			= nullptr;

				bHasParent		= false;
				parent			= nullptr;

				bLocalState		= true;
				statePtr		= b;
				if(b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;
			}

			CheckBox::CheckBox(Props &p, std::string n, bool *b, Props_CheckBox *c) {
				name			= n;
				bIsGrouped		= (c->iGroup>0);
				label			= nullptr;

				bHasParent		= true;
				parent			= &p;

				bLocalState		= true;
				statePtr		= b;
				if(b) eObjectState	= STATE_ACTIVE;
				else  eObjectState	= STATE_NONE;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;
			}

			CheckBox::~CheckBox() {
				if(bLocalCon && con != nullptr) delete con;
				if(bLocalState && statePtr != nullptr) delete statePtr;
				if(label != nullptr) delete label;
			}

			void CheckBox::init() {
				this->id = IDs.create();

				//con->exec();
				if(bHasParent) {
					con->scroll.bind(*parent);
					con->exec(*parent);
				}
				else con->exec();
				update();

				// FIXME: Create SOUNDS enumeration
				initSound(1, 3, 4, 0, 0, true, true);

				// Create button window with contraints to parent if present
				if (bHasParent) box = Object::Window(*parent, name, con);
				else box = Object::Window(name, con);
				box.init();

				con->check.setOrigin(Core::GUI::CONSTRAIN_CENTER);
				con->check.setAnchor(Core::GUI::CONSTRAIN_CENTER);
				con->check.setBorder(1, true);
				con->check.setWidth(50, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
				con->check.setHeight(50, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
				con->check.disablePadding();
				check = Object::Window(*box.con, name, &con->check);
				check.init();

				label = new Label(*con, name, &con->label);
				label->init();

				toolTip.init(*con, name);

				bInit = true;
			}

			/**
			 * Update constraints
			 */
			void CheckBox::update() {
				int iRadius = fmin(fmin(con->radius, con->size.x/2.0f), con->size.y/2.0f);
				con->setRadius(iRadius);

				iRadius = fmin(fmin(con->radius*(0.5f), con->check.size.x/2.0f), con->check.size.y/2.0f);
				con->check.setRadius(iRadius);
			}

			void CheckBox::updateObjectState(iState eExternState) {
				// Check for external state change, return early
				checkStatePtr();

				if((eExternState!=STATE_NONE) && !(eExternState&STATE_UPDATE)) {
					eObjectState = eExternState;
				}
				else {
					if(!(eExternState&STATE_UPDATE)) {
						Vector2f vPos = con->getScrollPos();
						mState = Core::mouse->checkInput(gameVars->screen.half.x+vPos.x, gameVars->screen.half.y-vPos.y, con->size.x, con->size.y);
						//mState = Core::mouse->checkInput(gameVars->screen.half.x+con->pos.x, gameVars->screen.half.y-con->pos.y, con->size.x, con->size.y);
					}
					else this->mState = Core::_Mouse::MOUSE_NONE;

					if(enabled()) {
						if(con->bToggle) {
							if(bIsGrouped && (eObjectState&STATE_ACTIVE) && (Core::groups[con->iGroup].object!=name && Core::groups[con->iGroup].object!="")) {
								eObjectState = STATE_NONE;
								Sound_AbortState();
							}
							else if (mState&Core::_Mouse::MOUSE_LEFT) {
								if(eObjectState&STATE_ACTIVE) {
									if (!bIsGrouped || (bIsGrouped && !Core::groups[con->iGroup].bExclusive)) eObjectState = STATE_NONE;
									if(bIsGrouped && Core::groups[con->iGroup].object==name) Core::groups[con->iGroup].object = "";
									Sound_PlayOff();
								}
								else if(eObjectState&STATE_HOVER) {
									eObjectState = STATE_ACTIVE;
									if(bIsGrouped) Core::groups[con->iGroup].object = name;
									Sound_PlayOn();
								}
								else {
									// Do not report mouse click if group disabled
									mState = Core::_Mouse::MOUSE_NONE;
								}
							}
							else if (!(eObjectState&STATE_ACTIVE) && (mState&Core::_Mouse::MOUSE_NONE)) {
								eObjectState = STATE_NONE;
							}
						}
					}
					else this->eObjectState = STATE_NONE;

					// Allow mouse hover at any time (used for tooltips)
					if(!(eExternState&STATE_UPDATE)) {
						if(mState&Core::_Mouse::MOUSE_HOVER) eObjectState = eObjectState|STATE_HOVER;
						else eObjectState = eObjectState&~STATE_HOVER;
					}
				}

				if(!enabled()) eObjectState |= STATE_DISABLED;
				updateStatePtr();
			}

			void CheckBox::exec(iState eExternState) {
				if(bInit && con->visibility && ((parent!=nullptr && parent->visibility) || (parent==nullptr))) {

					//if((con->bFocusLock && !bFocusPresent) || !con->bFocusLock || (sActiveObject==name))
					updateObjectState(eExternState);

					if(con->toolTip.bShow) toolTip.updateObjectState(eObjectState);
					else toolTip.updateObjectState(STATE_NONE);

					update();

					// Always set the toggle state
					if(eObjectState&STATE_ACTIVE) *statePtr = true;
					else *statePtr = false;

					box.exec(eObjectState);
					if(eObjectState&STATE_ACTIVE) check.exec(STATE_ACTIVE);

					if(con->bShowLabel) label->exec(eObjectState);
				}
			}

			void CheckBox::execToolTip() {
				toolTip.exec();
			}

			/***
			 * \brief Calls to run when object not visible/not in focus.
			 * @tparam T
			 * @tparam T
			 */
			void CheckBox::updateNoFocus() {
				updateObjectState(STATE_UPDATE);
				updateStatePtr();
			}

		}
	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_CHECKBOX_H_ */
