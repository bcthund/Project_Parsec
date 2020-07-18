/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_LABEL_H_
#define HEADERS_GAMESYS_GUI_LABEL_H_

#include <iostream>
//#include "../../core/core_functions.h"
//#include "../../core/vao.h"
//#include "../../core/matrix.h"
//#include "../../core/shader.h"
//#include "../../core/InputSys.h"
#include "../../core/Colors.h"
#include "../../gamesys/gameVars.h"
#include "../../gamesys/TextSys.h"
#include "GUI_Constraint.h"
//#include "GUI_ToolTip.h"
#include "GUI_Window.h"

namespace Core {
	namespace GUI {
		namespace Object {
			class Label : public Base::Generic<Props_Label> {
				public:
					Label();
					Label(std::string n, Props_Label c);
					Label(Props &p, std::string n, Props_Label c);
					Label(std::string n, Props_Label *c);
					Label(Props &p, std::string n, Props_Label *c);
					virtual ~Label();

//					ToolTip toolTip;
					void init();
					void exec(iState eExternState=STATE_NONE);

				private:
					Window		win;
					void updateObjectState(iState eExternState);
			};

			Label::Label() {}

			Label::Label(std::string n, Props_Label c) {
				name			= n;
				bInit			= false;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= true;
				con				= new Props_Label();
				*con			= c;
			}

			Label::Label(Props &p, std::string n, Props_Label c) {
				name			= n;
				bInit			= false;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= true;
				con				= new Props_Label();
				*con			= c;
			}

			Label::Label(std::string n, Props_Label *c) {
				name			= n;
				bInit			= false;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= false;
				con				= c;
			}

			Label::Label(Props &p, std::string n, Props_Label *c) {
				name			= n;
				bInit			= false;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= false;
				con				= c;
			}

			Label::~Label() {
				if(bLocalCon && con != nullptr) delete con;
			}

			void Label::init() {
				// Create button window with contraints to parent if present
				if (bHasParent) win = Object::Window(*parent, name, con);
				else win = Object::Window(name, con);

				win.init();
				con->exec();

				bInit = true;
			}

			void Label::updateObjectState(iState eExternState) {
				if(eExternState!=STATE_NONE && !(eExternState&STATE_UPDATE)) {
					eObjectState = eExternState;
				}
				else eObjectState = STATE_NONE;
				if(!enabled()) eObjectState |= STATE_DISABLED;
			}

			void Label::exec(iState eExternState) {
				if(bInit && con->visibility && ((parent!=nullptr && parent->visibility) || (parent==nullptr))) {
					if(con->size.isAutoSet()) {
						//if(!bFocusPresent) updateObjectState(eExternState);
						updateObjectState(eExternState);

						// Update constraints
						if(bHasParent) con->exec(*parent);
						else con->exec();

						// Draw button window
						if(con->bShowBackground) win.exec(eObjectState);

						// Draw button text
						if(eObjectState&STATE_DISABLED) {
							if(eObjectState&STATE_HOVER)	colors.PushFront(gameVars->pallette.gui.disabled.text.hover);
							else							colors.PushFront(gameVars->pallette.gui.disabled.text.base);
						}
						else if(eObjectState&STATE_HOVER) 		colors.PushFront(*con->colorText.highlight);
						else if(eObjectState&STATE_ACTIVE)		colors.PushFront(*con->colorText.highlight);
						else 									colors.PushFront(*con->colorText.base);
						textSys->draw(con, name, CONSTRAIN_CENTER);
						colors.PopFront();
					}
					else textSys->draw(con, name, CONSTRAIN_CENTER);

					// Autosize
					if(con->size.constraint.xAuto) {
						int maxSize = std::max(con->size.constraint.xMin, std::min(con->size.constraint.xMax , int(name.length()*Core::gameVars->font.vSize.x)+(con->vPadding.left+con->vPadding.right) ) );
						con->setWidth(maxSize, GUI::SIZE_CONSTRAINT_ABSOLUTE);
					}
					if(con->size.constraint.yAuto) con->setHeight(Core::gameVars->font.vSize.y+(con->vPadding.top+con->vPadding.bottom), GUI::SIZE_CONSTRAINT_ABSOLUTE);
					if(con->size.constraint.xAuto || con->size.constraint.yAuto) con->exec();

				}
			}
		}
	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_Label_H_ */
