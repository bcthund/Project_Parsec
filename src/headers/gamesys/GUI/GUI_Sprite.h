/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_SPRITE_H_
#define HEADERS_GAMESYS_GUI_SPRITE_H_

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
#include "../../core/InputSys.h"
#include "../../core/Colors.h"
#include "../../gamesys/gameVars.h"
#include "../../gamesys/SpriteSys.h"
#include "GUI_Constraint.h"
#include "GUI_ToolTip.h"
#include "GUI_Window.h"

namespace Core {
	namespace GUI {
		namespace Object {
			class Sprite : public Base::Generic<Props_Sprite> {
				public:
					Sprite();
					Sprite(std::string n, Props_Sprite c);
					Sprite(Props &p, std::string n, Props_Sprite c);
					Sprite(std::string n, Props_Sprite *c);
					Sprite(Props &p, std::string n, Props_Sprite *c);

					virtual ~Sprite();

					ToolTip toolTip;
					void init();
					void exec(iState eExternState=STATE_NONE);
					void execToolTip();

				private:
					Window win;
					void updateObjectState(iState eExternState);
			};

			Sprite::Sprite() {}

			Sprite::Sprite(std::string n, Props_Sprite c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= true;
				con				= new Props_Sprite();
				*con			= c;
				if(con->text == "") con->text = n;
			}

			Sprite::Sprite(Props &p, std::string n, Props_Sprite c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= true;
				con				= new Props_Sprite();
				*con			= c;
				if(con->text == "") con->text = n;
			}

			Sprite::Sprite(std::string n, Props_Sprite *c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;
			}

			Sprite::Sprite(Props &p, std::string n, Props_Sprite *c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;
			}

			Sprite::~Sprite() {
				if(bLocalCon && con != nullptr) delete con;
			}

			/** ******************************************************************************************************************************
			 *
			 * ****************************************************************************************************************************** */
			void Sprite::init() {
				// Create button window with contraints to parent if present
				if (bHasParent) win = Object::Window(*parent, name, con);
				else win = Object::Window(name, con);
				win.init();

				// Setup button contraints
				if(bHasParent) con->exec(*parent);
				else con->exec();

				toolTip.init(*con, name);

				bInit = true;
			}

			void Sprite::updateObjectState(iState eExternState) {

				if(!(eExternState&STATE_UPDATE)) {
					mState = Core::mouse->checkInput(gameVars->screen.half.x+con->pos.x, gameVars->screen.half.y-con->pos.y, con->size.x, con->size.y);
				}
				else mState = Core::_Mouse::MOUSE_NONE;

				if(eExternState!=STATE_NONE && !(eExternState&STATE_UPDATE)) eObjectState = eExternState;
				else if (mState&Core::_Mouse::MOUSE_HOVER) eObjectState = STATE_HOVER;
				else eObjectState = STATE_NONE;

				if(!enabled()) eObjectState |= STATE_DISABLED;
			}

			/** ******************************************************************************************************************************
			 *
			 * ****************************************************************************************************************************** */
			void Sprite::exec(iState eExternState) {
				if(bInit && con->visibility && ((parent!=nullptr && parent->visibility) || (parent==nullptr))) {

					updateObjectState(eExternState);

					if(con->toolTip.bShow) toolTip.updateObjectState(eObjectState);
					else toolTip.updateObjectState(STATE_NONE);

					// Update constraints
					if(bHasParent) con->exec(*parent);
					else con->exec();

					// Draw button window
					win.exec(eObjectState);

					if(eObjectState&STATE_DISABLED) {
						if(eObjectState&STATE_HOVER)	colors.PushFront(gameVars->pallette.gui.disabled.base.hover);
						else							colors.PushFront(gameVars->pallette.gui.disabled.base.base);
					}
					else 								colors.PushFront(*con->colorSprite.base);
					spriteSys->draw(con, con->spriteImage);
					colors.PopFront();
				}
			}

			void Sprite::execToolTip() {
				toolTip.exec();
			}

		}
	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_SPRITE_H_ */
