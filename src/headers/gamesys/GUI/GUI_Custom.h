/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_CUSTOM_H_
#define HEADERS_GAMESYS_GUI_CUSTOM_H_

//#include <iostream>
//#include "../core/core_functions.h"
//#include "../core/vao.h"
//#include "../core/matrix.h"
//#include "../core/shader.h"
#include "GUI_Constraint.h"
#include "GUI_Window.h"

// FIXME: Add nested containers
// FIXME: Add get functions for nexted containers

namespace Core {
	namespace GUI {

//		class Label {
//			public:
//				Constraints_Label *con;		// Contraints are relative to parent window
//				Constraints *parent;		// A parent window (container) is not required
//				Label();
//				Label(std::string n, Constraints_Label c);
//				Label(std::string n, Constraints_Label *c);
//				Label(Constraints &p, std::string n, Constraints_Label c);
//				Label(Constraints &p, std::string n, Constraints_Label *c);
//				virtual ~Label();
//				void init();
//				void exec(eState colorState=STATE_NONE);
//				std::string name;
//
//			private:
//				Window		win;				// Window object for background
//				bool		bInit;
//				bool		bHasParent;
//				bool		bLocalCon;
//		};
//
//		Label::Label() {
//			parent			= nullptr;
//			name			= "";
//			bHasParent		= false;
//			bInit			= false;
//			con				= nullptr;
//			bLocalCon		= false;
//		}
//
//		Label::Label(std::string n, Constraints_Label c) {
//			parent			= nullptr;
//			con				= new Constraints_Label();
//			*con			= c;
//			name			= n;
//			bHasParent		= false;
//			bInit			= false;
//			bLocalCon		= true;
//		}
//
//		Label::Label(Constraints &p, std::string n, Constraints_Label c) {
//			parent			= &p;
//			con				= new Constraints_Label();
//			*con			= c;
//			name			= n;
//			bHasParent		= true;
//			bInit			= false;
//			bLocalCon		= true;
//		}
//
//		Label::Label(std::string n, Constraints_Label *c) {
//			parent			= nullptr;
//			con				= c;
//			name			= n;
//			bHasParent		= false;
//			bInit			= false;
//			bLocalCon		= false;
//		}
//
//		Label::Label(Constraints &p, std::string n, Constraints_Label *c) {
//			parent			= &p;
//			con				= c;
//			name			= n;
//			bHasParent		= true;
//			bInit			= false;
//			bLocalCon		= false;
//		}
//
//		Label::~Label() {
//			if(bLocalCon && con != nullptr) delete con;
//		}
//
//		void Label::init() {
//			// Create button window with contraints to parent if present
//			if (bHasParent) win = Object::Window(*parent, name, con);
//			else win = Object::Window(name, con);
//			win.init();
//
//			con->exec();
//
//			bInit = true;
//		}
//
//		void Label::exec(eState colorState) {
//			if(bInit && ((parent!=nullptr && parent->visibility) || (parent==nullptr))) {
//				if(con->bAutoSizeLabelX) {
//					int maxSize = (name.length()*Core::gameVars->font.vSize.x)+(con->vPadding.left+con->vPadding.right);
//					con->setWidth(maxSize, SIZE_CONSTRAINT_ABSOLUTE);
//				}
//				if(con->bAutoSizeLabelY) {
//					con->setHeight(Core::gameVars->font.vSize.y+(con->vPadding.top+con->vPadding.bottom), SIZE_CONSTRAINT_ABSOLUTE);
//				}
//
//				// Update constraints
//				if(bHasParent) con->exec(*parent);
//				else con->exec();
//
//				// Draw button window
//				if(con->bShowBackground) win.exec();
//
//				// Draw button text
//				if(colorState==STATE_HOVER) 		colors->PushFront(*con->colorText.highlight);
//				else if(colorState==STATE_ACTIVE)	colors->PushFront(*con->colorText.highlight);
//				else 								colors->PushFront(*con->colorText.base);
//				textSys->draw(*con, name, CONSTRAIN_CENTER);
//				colors->PopFront();
//			}
//		}

	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_CUSTOM_H_ */
