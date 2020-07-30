/*
 * GUIText.h
 *
 *  Created on: Apr 2, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUITEXT_H_
#define HEADERS_GAMESYS_GUITEXT_H_

#include <iostream>
#include "GUI_Constraint.h"
#include "GUI_Window.h"

/*
 * This is more of a base class for other classes for drawing contrained text
 * 	and cannot be called directly for GUI drawing. It is called by other objects
 * 	such as text areas to draw text that needs to be constrained to a parent object.
 */

namespace Core {
	namespace GUI {
		namespace Object {
			class Text : public Base::Generic<Props_Text> {
				public:
					Text();
					Text(std::string n, Props_Text c);
					Text(Window &p, std::string n, Props_Text c);
					Text(std::string n, Props_Text *c);
					Text(Window &p, std::string n, Props_Text *c);
					virtual ~Text();
					void init();
					void exec(iState eExternState=STATE_NONE);

				private:
					Window *parent;
					void updateObjectState(iState eExternState);
			};

			Text::Text() {
				parent = nullptr;
			}

			Text::Text(std::string n, Props_Text c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= true;
				con				= new Props_Text();
				*con			= c;
				if(con->text == "") con->text = n;
			}

			Text::Text(Window &p, std::string n, Props_Text c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= true;
				con				= new Props_Text();
				*con			= c;
				if(con->text == "") con->text = n;
			}

			Text::Text(std::string n, Props_Text *c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;
			}

			Text::Text(Window &p, std::string n, Props_Text *c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;
			}

			Text::~Text() {
				if(bLocalCon && con != nullptr) delete con;
			}

			void Text::init() {
				if(bHasParent) {
					con->scroll.bind(*parent->con);
					con->exec(*parent->con);
				}
				else con->exec();

				//if (bHasParent) con->exec(*parent->con);
				//else con->exec();

				bInit = true;
			}

			void Text::updateObjectState(iState eExternState) {
				if(eExternState!=STATE_NONE && !(eExternState&STATE_UPDATE)) {
					eObjectState = eExternState;
				}
				else eObjectState = STATE_NONE;
				if(!enabled()) eObjectState |= STATE_DISABLED;
			}

			void Text::exec(iState eExternState) {
				if(bInit && con->visibility && ((parent!=nullptr && parent->con->visibility) || (parent==nullptr))) {

					if(con->size.isAutoSet()) {

						//if(!bFocusPresent) updateObjectState(eExternState);
						updateObjectState(eExternState);

						// Update constraints
						if(bHasParent) con->exec(*parent->con);
						else con->exec();

						// Draw button text
						if(eObjectState&STATE_DISABLED) {
							if(eObjectState&STATE_HOVER)	colors.PushFront(gameVars->pallette.gui.disabled.text.hover);
							else							colors.PushFront(gameVars->pallette.gui.disabled.text.base);
						}
						else if(eObjectState&STATE_HOVER) 	colors.PushFront(*con->color.text().highlight);
						else if(eObjectState&STATE_ACTIVE)	colors.PushFront(*con->color.text().active);
						else 								colors.PushFront(*con->color.text().base);

						textSys->drawMulti(con, CONSTRAIN_TOP|CONSTRAIN_LEFT);
						colors.PopFront();
					}
					else textSys->drawMulti(con, CONSTRAIN_TOP|CONSTRAIN_LEFT);
				}
			}
		}
	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUITEXT_H_ */
