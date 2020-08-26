/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_LINE_H_
#define HEADERS_GAMESYS_GUI_LINE_H_

#include <iostream>
#include "../../core/InputSys.h"
#include "../../core/Colors.h"
#include "../../gamesys/gameVars.h"
#include "../../gamesys/SpriteSys.h"
#include "GUI_Constraint.h"

namespace Core {
	namespace GUI {
		namespace Object {

			class Line : public Base::Generic<Props_Line> {
				public:
					Line();
					Line(std::string n, Vector2f A, Vector2f B, Props_Line &c);
					Line(std::string n, Vector2f *A, Vector2f *B, Props_Line &c);
					Line(Props &p, std::string n, Vector2f A, Vector2f B, Props_Line &c);
					Line(Props &p, std::string n, Vector2f *A, Vector2f *B, Props_Line &c);

					Line(std::string n, Vector2f A, Vector2f B, Props_Line *c);
					Line(std::string n, Vector2f *A, Vector2f *B, Props_Line *c);
					Line(Props &p, std::string n, Vector2f A, Vector2f B, Props_Line *c);
					Line(Props &p, std::string n, Vector2f *A, Vector2f *B, Props_Line *c);
					virtual ~Line();

//					ToolTip toolTip;
					void init();
					void exec(iState eExternState=STATE_NONE);
					void setPointA(Vector2f v) {	*pointA = v;	}
					void setPointB(Vector2f v) {	*pointB = v;	}
//					void execToolTip();

				private:
//					Window win;
					void updateObjectState(iState eExternState);
					Vector2f *pointA;
					Vector2f *pointB;
					bool bLocalA,
						 bLocalB;
			};

			Line::Line() {
				pointA = nullptr;
				pointB = nullptr;
				bLocalA = false;
				bLocalB = false;
			}

			Line::Line(std::string n, Vector2f A, Vector2f B, Props_Line &c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= true;
				con				= new Props_Line();
				*con			= c;
				if(con->text == "") con->text = n;

				pointA = new Vector2f(A);
				pointB = new Vector2f(B);
				bLocalA = true;
				bLocalB = true;
			}

			Line::Line(std::string n, Vector2f *A, Vector2f *B, Props_Line &c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= true;
				con				= new Props_Line();
				*con			= c;
				if(con->text == "") con->text = n;

				pointA = A;
				pointB = B;
				bLocalA = false;
				bLocalB = false;
			}

			Line::Line(Props &p, std::string n, Vector2f A, Vector2f B, Props_Line &c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= true;
				con				= new Props_Line();
				*con			= c;
				if(con->text == "") con->text = n;

				pointA = new Vector2f(A);
				pointB = new Vector2f(B);
				bLocalA = true;
				bLocalB = true;
			}

			Line::Line(Props &p, std::string n, Vector2f *A, Vector2f *B, Props_Line &c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= true;
				con				= new Props_Line();
				*con			= c;
				if(con->text == "") con->text = n;

				pointA = A;
				pointB = B;
				bLocalA = false;
				bLocalB = false;
			}

			Line::Line(std::string n, Vector2f A, Vector2f B, Props_Line *c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

				pointA = new Vector2f(A);
				pointB = new Vector2f(B);
				bLocalA = true;
				bLocalB = true;
			}

			Line::Line(std::string n, Vector2f *A, Vector2f *B, Props_Line *c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

				pointA = A;
				pointB = B;
				bLocalA = false;
				bLocalB = false;
			}

			Line::Line(Props &p, std::string n, Vector2f A, Vector2f B, Props_Line *c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

				pointA = new Vector2f(A);
				pointB = new Vector2f(B);
				bLocalA = true;
				bLocalB = true;
			}

			Line::Line(Props &p, std::string n, Vector2f *A, Vector2f *B, Props_Line *c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

				pointA = A;
				pointB = B;
				bLocalA = false;
				bLocalB = false;
			}

			Line::~Line() {
				if(bLocalCon && con != nullptr) delete con;
				if(bLocalA && pointA != nullptr) delete pointA;
				if(bLocalB && pointB != nullptr) delete pointB;
			}

			/** ******************************************************************************************************************************
			 *
			 * ****************************************************************************************************************************** */
			void Line::init() {
				this->id = IDs.create();

				if(bHasParent) {
					con->scroll.bind(*parent);
					con->exec(*parent);
				}
				else con->exec();

				// Create button window with contraints to parent if present
//				if (bHasParent) win = Object::Window(*parent, name, con);
//				else win = Object::Window(name, con);
//				win.init();

//				toolTip.init(*con, name);

				bInit = true;
			}

			void Line::updateObjectState(iState eExternState) {
//				// Uncomment if object state can be set externally
//				//checkStatePtr();

				// Generic state handler
				if((eExternState!=STATE_NONE) && !(eExternState&STATE_UPDATE)) {
					eObjectState = eExternState;
				}
				else {
//					if(!(eExternState&STATE_UPDATE)) {
//						if(parent!=nullptr && parent->scroll.getEnabled()) {
//							Vector2f vPos = con->getScrollPos();
//							mState = Core::mouse->checkInput(gameVars->screen.half.x+vPos.x, gameVars->screen.half.y-vPos.y, con->size.x, con->size.y);
//						}
//						else {
//							mState = Core::mouse->checkInput(gameVars->screen.half.x+con->pos.x, gameVars->screen.half.y-con->pos.y, con->size.x, con->size.y);
//						}
//					}
//					else mState = Core::_Mouse::MOUSE_NONE;
//
////					// Object specific logic
//					if(enabled()) {
//						if(con->scroll.isScrollable() && (mState&Core::_Mouse::MOUSE_HOVER)) {
//							updateScrollMouse();
//						}
//						eObjectState = STATE_NONE;
//					}
//					else {
						eObjectState = STATE_NONE;
//					}
				}

//				// Report if mouse is in button space
//				if(!(mState&Core::_Mouse::MOUSE_NONE)) eObjectState = eObjectState|STATE_FOCUS;
//				else eObjectState = eObjectState&~STATE_FOCUS;

				if(!enabled()) eObjectState |= STATE_DISABLED;

//				// Update the state value according to object state results
//				//updateStatePtr();
			}

			/** ******************************************************************************************************************************
			 *
			 * ****************************************************************************************************************************** */
			void Line::exec(iState eExternState) {
				if(bInit && con->visibility && ((parent!=nullptr && parent->visibility) || (parent==nullptr))) {

					updateObjectState(eExternState);

//					if(con->toolTip.bShow) toolTip.updateObjectState(eObjectState);
//					else toolTip.updateObjectState(STATE_NONE);

//					// Update constraints
//					if(bHasParent) con->exec(*parent);
//					else con->exec();

					Core::matrix->Push();
						Vector2f vPos;
						if(con->scroll.isScrollable() && (parent!=nullptr && parent->scroll.getEnabled())) vPos = con->getScrollPos();
						else vPos = con->getPos();

						Core::matrix->Translate( vPos.x, vPos.y, 0.0f );
						Core::matrix->SetProjection(Core::matrix->MM_ORTHO);

						if(eObjectState&STATE_DISABLED) {
							if(eObjectState&STATE_HOVER)	Core::helper->drawLine(*pointA, *pointB, con->borderHover, 1.0f, gameVars->pallette.gui.disabled.text.hover, gameVars->pallette.gui.disabled.text.hover);
							else							Core::helper->drawLine(*pointA, *pointB, con->borderNormal, 1.0f, gameVars->pallette.gui.disabled.text.base, gameVars->pallette.gui.disabled.text.base);
						}
						else if(eObjectState&STATE_HOVER) 	Core::helper->drawLine(*pointA, *pointB, con->borderHover, 1.0f, con->colorA.highlight, con->colorB.highlight);
						else if(eObjectState&STATE_ACTIVE)	Core::helper->drawLine(*pointA, *pointB, con->borderNormal, 1.0f, con->colorA.active,	con->colorB.active);
						else 								Core::helper->drawLine(*pointA, *pointB, con->borderNormal, 1.0f, con->colorA.base,		con->colorB.base);

					Core::matrix->Pop();

				}
			}

//			void Line::execToolTip() {
//				toolTip.exec();
//			}


		} /* namespace Object */
	} /* namespace GUI */
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_LINE_H_ */
