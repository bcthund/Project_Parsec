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

//				if(!(eExternState&STATE_UPDATE)) {
//					Vector2f vPos = con->getScrollPos();
//					mState = Core::mouse->checkInput(gameVars->screen.half.x+vPos.x, gameVars->screen.half.y-vPos.y, con->size.x, con->size.y);
//					//mState = Core::mouse->checkInput(gameVars->screen.half.x+con->pos.x, gameVars->screen.half.y-con->pos.y, con->size.x, con->size.y);
//				}
//				else mState = Core::_Mouse::MOUSE_NONE;
//
//				if((eExternState!=STATE_NONE) && !(eExternState&STATE_UPDATE)) eObjectState = eExternState;
//				else if (mState&Core::_Mouse::MOUSE_HOVER) eObjectState = STATE_HOVER;
//				else eObjectState = STATE_NONE;
//
//				if(!enabled()) eObjectState |= STATE_DISABLED;
			}

			/** ******************************************************************************************************************************
			 *
			 * ****************************************************************************************************************************** */
			void Line::exec(iState eExternState) {
				if(bInit && con->visibility && ((parent!=nullptr && parent->visibility) || (parent==nullptr))) {

//					debug.log("Drawing Line - "+name+" @ ("+std::to_string(pointA->x)+", "+std::to_string(pointA->y)+")-("+std::to_string(pointB->x)+", "+std::to_string(pointB->y)+")");

//					updateObjectState(eExternState);
//
//					if(con->toolTip.bShow) toolTip.updateObjectState(eObjectState);
//					else toolTip.updateObjectState(STATE_NONE);
//
//					// Update constraints
//					if(bHasParent) con->exec(*parent);
//					else con->exec();
//
//					// Draw button window
//					win.exec(eObjectState);
//
//					if(eObjectState&STATE_DISABLED) {
//						if(eObjectState&STATE_HOVER)	colors.PushFront(gameVars->pallette.gui.disabled.base.hover);
//						else							colors.PushFront(gameVars->pallette.gui.disabled.base.base);
//					}
//					else 								colors.PushFront(*con->colorSprite.base);
//					spriteSys->draw(con, con->spriteImage);
//					colors.PopFront();

					//Core::helper->drawLine(*pointA, *pointB, 10.0f, 1.0f, colors[colors().Acid_green], colors[colors().Yellow]);

					Core::matrix->Push();
//						Vector2f vPos;
//						if(con->scroll.isScrollable() && (parent!=nullptr && parent->scroll.getEnabled())) vPos = con->getScrollPos();
//						else vPos = con->getPos();

//						Vector2f vPos = con->getPos();
//						Core::matrix->Translate( vPos.x, vPos.y, 0.0 );

						Core::matrix->SetProjection(Core::matrix->MM_ORTHO);
	//					Core::Vector3f a = { 0, 0, 0 };
	//					Core::Vector3f b = { Core::gameVars->screen.half.x, Core::gameVars->screen.half.y, 0 };
//						Core::Vector2f a = { 0, 0 };
//						Core::Vector2f b = { (int)Core::gameVars->screen.half.x, (int)Core::gameVars->screen.half.y };
						//Core::Color colorA = { 1, 0, 0, 1};
						//Core::Color colorB = { 0, 1, 0, 1};
	//					Core::helper->drawLine(a, b, 2.0f, 1, colors[colors().Acid_green], colors[colors().Yellow]);
	//					Core::helper->drawLine(a, b, 2.0f, 1, colors[colors().Acid_green], colors[colors().Yellow]);



						Core::helper->drawLine(*pointA, *pointB, 1.0f, 1.0f, colors[colors().Black], colors[colors().Black]);
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
