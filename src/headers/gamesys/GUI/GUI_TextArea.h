/*
 * GUITextArea.h
 *
 *  Created on: Apr 2, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUITEXTAREA_H_
#define HEADERS_GAMESYS_GUITEXTAREA_H_

#include <iostream>
//#include "../core/core_functions.h"
//#include "../core/vao.h"
//#include "../core/matrix.h"
//#include "../core/shader.h"
#include "GUI_Constraint.h"
#include "GUI_ToolTip.h"
#include "GUI_Window.h"
#include "GUI_Text.h"
#include "GUI_Slider.h"
#include "GUI_Label.h"

namespace Core {
	namespace GUI {
		namespace Object {

			class TextArea : virtual public Base::Generic<Props_TextArea> {
				public:
					TextArea();
					TextArea(std::string n, Props_TextArea c);
					TextArea(Props &p, std::string n, Props_TextArea c);
					TextArea(std::string n, Props_TextArea *c);
					TextArea(Props &p, std::string n, Props_TextArea *c);
					virtual ~TextArea();
					ToolTip toolTip;
					void init();
					void exec(iState eExternState=STATE_NONE);

				protected:
					Window	win;				// Window object for background
					Text	text;
					Window	*scrollBarContainer;
					Button	*scrollUp;
					Button	*scrollDown;
					Label	*label;
					Slider<float>	*scrollBar;
					bool bScrollOneShot;
					void updateObjectState(iState eExternState);
			};

			TextArea::TextArea() {
				scrollBarContainer	= nullptr;
				scrollUp			= nullptr;
				scrollDown			= nullptr;
				bScrollOneShot		= false;
				scrollBar			= nullptr;
				label				= nullptr;
			}

			TextArea::TextArea(std::string n, Props_TextArea c) {
				name				= n;

				bHasParent			= false;
				parent				= nullptr;

				bLocalCon			= true;
				con					= new Props_TextArea();
				*con				= c;

				scrollBarContainer	= nullptr;
				scrollUp			= nullptr;
				scrollDown			= nullptr;
				bScrollOneShot		= false;
				scrollBar			= nullptr;
				label				= nullptr;
			}

			TextArea::TextArea(Props &p, std::string n, Props_TextArea c) {
				name				= n;

				bHasParent			= true;
				parent				= &p;

				bLocalCon			= true;
				con					= new Props_TextArea();
				*con				= c;

				scrollBarContainer	= nullptr;
				scrollUp			= nullptr;
				scrollDown			= nullptr;
				bScrollOneShot		= false;
				scrollBar			= nullptr;
				label				= nullptr;
			}

			TextArea::TextArea(std::string n, Props_TextArea *c) {
				name				= n;

				bHasParent			= false;
				parent				= nullptr;

				bLocalCon			= false;
				con					= c;

				scrollBarContainer	= nullptr;
				scrollUp			= nullptr;
				scrollDown			= nullptr;
				bScrollOneShot		= false;
				scrollBar			= nullptr;
				label				= nullptr;
			}

			TextArea::TextArea(Props &p, std::string n, Props_TextArea *c) {
				name				= n;

				bHasParent			= true;
				parent				= &p;

				bLocalCon			= false;
				con					= c;

				scrollBarContainer	= nullptr;
				scrollUp			= nullptr;
				scrollDown			= nullptr;
				bScrollOneShot		= false;
				scrollBar			= nullptr;
				label				= nullptr;
			}

			TextArea::~TextArea() {
				if(bLocalCon && con != nullptr) delete con;
				if(scrollBarContainer != nullptr) delete scrollBarContainer;
				if(scrollUp != nullptr) delete scrollUp;
				if(scrollDown != nullptr) delete scrollDown;
				if(scrollBar != nullptr) delete scrollBar;
				if(label != nullptr) delete label;
			}

			void TextArea::init() {

				if(con->enableScrolling) {
					con->setWidth(con->size.constraint.x-con->iScrollSize, con->size.constraint.xType);
				}

				// Create button window with contraints to parent if present
				if (bHasParent) win = Object::Window(*parent, name, con);
				else win = Object::Window(name, con);
				win.init();

				// Setup button contraints
				if(bHasParent) con->exec(*parent);
				else con->exec(*win.con);

				con->text.setAnchor(CONSTRAIN_CENTER);	// DO NOT CHANGE
				con->text.setOrigin(CONSTRAIN_TOP|CONSTRAIN_LEFT);
				con->text.setWidth(con->size.x, SIZE_CONSTRAINT_ABSOLUTE);
				con->text.setHeight(con->size.y, SIZE_CONSTRAINT_ABSOLUTE);
				con->text.setPos(0, 0);
				con->text.setPadding(con->vPadding);

				text = Text(win, name, &con->text);
				text.init();

				if(con->enableScrolling) {
					Props_Window cWin;
					cWin.setOrigin(CONSTRAIN_RIGHT);
					cWin.setAnchor(CONSTRAIN_LEFT);
					cWin.setWidth(con->iScrollSize, SIZE_CONSTRAINT_ABSOLUTE);
					cWin.setHeight(con->size.constraint.y, SIZE_CONSTRAINT_ABSOLUTE);
					cWin.setPos(0, 0);
					cWin.disablePadding();
					cWin.setBorder(0, false);
					cWin.setRadius(0);
					cWin.setColorWindowB(&colors[colors().Tan]);
					scrollBarContainer = new Window(*con, name, cWin);
					scrollBarContainer->init();

					Props_Button cButton;
					cButton.setWidth(100, SIZE_CONSTRAINT_RELATIVE);
					cButton.setHeight(con->iScrollSize, SIZE_CONSTRAINT_ABSOLUTE);
					cButton.setBorder(1, true);
					cButton.setRadius(3);
					cButton.setButtonType(Core::GUI::BUTTON_DEBOUNCE);

					cButton.setColorWindowBHA(	&Core::gameVars->pallette.gui.textArea.scroll.base,
												&Core::gameVars->pallette.gui.textArea.scroll.hover,
												&Core::gameVars->pallette.gui.textArea.scroll.active);

					cButton.setColorBorderBHA(	&Core::gameVars->pallette.gui.textArea.scrollBorder.base,
												&Core::gameVars->pallette.gui.textArea.scrollBorder.hover,
												&Core::gameVars->pallette.gui.textArea.scrollBorder.active);

					cButton.setColorTextBHA(	&Core::gameVars->pallette.gui.textArea.scrollText.base,
												&Core::gameVars->pallette.gui.textArea.scrollText.hover,
												&Core::gameVars->pallette.gui.textArea.scrollText.active);

					cButton.setPos(0, 0);
					cButton.setOrigin(CONSTRAIN_TOP);
					cButton.setAnchor(CONSTRAIN_TOP);
					scrollUp = new Button(*scrollBarContainer->con, "U", false, cButton);

					cButton.setPos(0, 0);
					cButton.setOrigin(CONSTRAIN_BOTTOM);
					cButton.setAnchor(CONSTRAIN_BOTTOM);
					scrollDown = new Button(*scrollBarContainer->con, "D", false, cButton);

					scrollUp->init();
					scrollDown->init();

					Props_Slider cSlider;
					cSlider = Props_Slider(SLIDER_VERTICAL);
					cSlider.setOrigin(CONSTRAIN_CENTER);
					cSlider.setAnchor(CONSTRAIN_CENTER);
					cSlider.setWidth(100, SIZE_CONSTRAINT_RELATIVE);
					cSlider.control.setWidth(con->iScrollSize, SIZE_CONSTRAINT_ABSOLUTE);
					cSlider.control.setHeight(con->iScrollSize, SIZE_CONSTRAINT_ABSOLUTE);
					cSlider.setHeight(scrollBarContainer->con->size.y-(2*con->iScrollSize), SIZE_CONSTRAINT_ABSOLUTE);
					cSlider.hideField();
					cSlider.hideLabel();
					cSlider.setMinMax(text.con->iMaxLines, 0);
					cSlider.setPos(0, 0);
					cSlider.setScrollSpeed(2.5f);

					scrollBar = new Slider<float>(*scrollBarContainer->con, name, &text.con->scrollPosition, cSlider);
					scrollBar->init();
				}

				if(con->bShowLabel) {
					label = new Label(*con, name, con->label);
					label->init();
				}

				toolTip.init(*con, name);

				bInit = true;
			}

			void TextArea::updateObjectState(iState eExternState) {

				if(!(eExternState&STATE_UPDATE)) {
					mState = Core::mouse->checkInput(gameVars->screen.half.x+con->pos.x, gameVars->screen.half.y-con->pos.y, con->size.x, con->size.y);
				}
				else this->mState = Core::_Mouse::MOUSE_NONE;

				if(eExternState!=STATE_NONE && !(eExternState&STATE_UPDATE)) {
					eObjectState = eExternState;
				}
				else if (mState == Core::_Mouse::MOUSE_HOVER) {
					eObjectState = STATE_HOVER;
				}
				else eObjectState = STATE_NONE;
				if(!enabled()) eObjectState |= STATE_DISABLED;
			}

			void TextArea::exec(iState eExternState) {
				if(bInit && con->visibility && ((parent!=nullptr && parent->visibility) || (parent==nullptr))) {

					updateObjectState(eExternState);

					if(con->toolTip.bShow) toolTip.updateObjectState(eObjectState);
					else toolTip.updateObjectState(STATE_NONE);

					// Update constraints
					if(bHasParent) con->exec(*parent);
					else con->exec(*win.con);


					if(con->text.size.isAutoSet()) {
						// Scroll Buttons
						if(con->enableScrolling) {
							// Draw button window
							if(!bScrollOneShot) {
								win.con->setWidth(con->size.x-con->iScrollSize, SIZE_CONSTRAINT_ABSOLUTE);
								bScrollOneShot = true;
							}
							win.exec(eObjectState);

							// Update external constraints and draw
							text.con->setWidth(con->size.x, SIZE_CONSTRAINT_ABSOLUTE);
							text.con->setHeight(con->size.y, SIZE_CONSTRAINT_ABSOLUTE);
							text.exec(eObjectState);

							if(con->bShowLabel) label->exec(eObjectState);

							scrollBarContainer->con->setHeight(con->size.constraint.y, SIZE_CONSTRAINT_ABSOLUTE);
							scrollBar->con->setMinMax(text.con->iMaxLines, 0);
							scrollBar->con->setHeight(scrollBarContainer->con->size.y-(2*con->iScrollSize), SIZE_CONSTRAINT_ABSOLUTE);

							if(!(eObjectState&STATE_DISABLED)) {
								scrollBarContainer->exec();
								scrollUp->exec();
								scrollDown->exec();
								scrollBar->exec();
							}
							else {
								scrollBarContainer->exec(STATE_DISABLED);
								scrollUp->exec(STATE_DISABLED);
								scrollDown->exec(STATE_DISABLED);
								scrollBar->exec(STATE_DISABLED);
							}

							// Check scroll buttons
							if(scrollUp->getState()) text.con->scrollUp();
							if(scrollDown->getState()) text.con->scrollDown();
						}
						else {
							// Draw button window
							if(bScrollOneShot) {
								win.con->setWidth(con->size.x+20, SIZE_CONSTRAINT_ABSOLUTE);
								bScrollOneShot = false;
							}
							win.exec(eObjectState);

							// Update external constraints and draw
							text.con->setWidth(con->size.x, SIZE_CONSTRAINT_ABSOLUTE);
							text.con->setHeight(con->size.y, SIZE_CONSTRAINT_ABSOLUTE);
							text.exec(eObjectState);

							if(con->bShowLabel) label->exec(eObjectState);
						}
					}
					else {
						// Text system determines auto size
						text.con->setWidth(con->size.x, SIZE_CONSTRAINT_ABSOLUTE);
						text.con->setHeight(con->size.y, SIZE_CONSTRAINT_ABSOLUTE);
						text.exec(eObjectState);
					}

					// Autosize
					if(con->size.constraint.xAuto) con->setWidth(con->text.size.x, SIZE_CONSTRAINT_ABSOLUTE);
					if(con->size.constraint.yAuto) con->setHeight(con->text.size.y, SIZE_CONSTRAINT_ABSOLUTE);
				}


			}
		}
	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUITEXTAREA_H_ */
