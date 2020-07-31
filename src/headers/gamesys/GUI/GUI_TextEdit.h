/*
 * GUITextArea.h
 *
 *  Created on: Apr 2, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUITEXTEDIT_H_
#define HEADERS_GAMESYS_GUITEXTEDIT_H_

#include <iostream>
#include "../../core/InputSys.h"
#include "../../gamesys/gameVars.h"
#include "GUI_Constraint.h"
#include "GUI_Window.h"
#include "GUI_TextArea.h"
#include "GUI_Slider.h"
#include "GUI_Label.h"

namespace Core {
	namespace GUI {
		namespace Object {

			/** \class TextEditBase
			 *  \brief Keyboard control and TextEdit object focus tracking
			 *
			 *  Creates a keyboard object to allow input while editing that is
			 *  used across all instances of TextEdit objects. Also keeps track
			 *  of if any TextEdit objects are currently active preventing
			 *  others from also being edited at the same time.
			 *
			 */
			class TextEditBase {
				public:
					static Core::_Keyboard keyboard;	//
					static bool bKeyboardInit;

					TextEditBase() {
						if(!bKeyboardInit) {
							keyboard.calc(Core::_Keyboard::KEYTYPE_DEBOUNCE);
							bKeyboardInit = true;
						}
					}
			};
			Core::_Keyboard TextEditBase::keyboard	= Core::_Keyboard();
			bool TextEditBase::bKeyboardInit		= false;

			/** \class TextEdit
			 *  \brief A copy of TextArea with cursor tracking and editing capability.
			 *
			 */
//			class TextEdit : public Base::Interactive<Props_TextArea, std::string>, public TextEditBase {
			class TextEdit : public Base::Interactive<Props_TextArea>, public TextEditBase {
				public:
					TextEdit();
					TextEdit(std::string n, Props_TextArea &c);
					TextEdit(Props &p, std::string n, Props_TextArea &c);
					TextEdit(std::string n, Props_TextArea *c);
					TextEdit(Props &p, std::string n, Props_TextArea *c);
					virtual ~TextEdit();

//					T *valuePtr;
//					bool bLocalValue;
//					void setValuePtr(T *ptr);
//					T * getValuePtr();

					void init();
					void exec(iState eExternState=STATE_NONE);
					void updateNoFocus();

				private:
					Window	win;				// Window object for background
					Text	text;
					Window	*scrollBarContainer;
					Button	*scrollUp;
					Button	*scrollDown;
					Label	*label;
					Slider<float>	*scrollBar;
					bool bScrollOneShot;
					bool bHasFocus;
					std::string sEditBuffer;
					void execEdit();
					void updateObjectState(iState eExternState);

			};

			TextEdit::TextEdit() {
				sEditBuffer			= "";
				bHasFocus			= false;
				scrollBarContainer	= nullptr;
				scrollUp			= nullptr;
				scrollDown			= nullptr;
				bScrollOneShot		= false;
				scrollBar			= nullptr;
				label				= nullptr;
			}

			TextEdit::TextEdit(std::string n, Props_TextArea &c) {
				name				= n;

				bHasParent			= false;
				parent				= nullptr;

				bLocalCon			= true;
				con					= new Props_TextArea();
				*con				= c;
//				if(con->text == "") con->text = n;

				bLocalState			= true;
				statePtr			= new bool(false);

				sEditBuffer			= "";
				bHasFocus			= false;
				scrollBarContainer	= nullptr;
				scrollUp			= nullptr;
				scrollDown			= nullptr;
				bScrollOneShot		= false;
				scrollBar			= nullptr;
				label				= nullptr;
			}

			TextEdit::TextEdit(Props &p, std::string n, Props_TextArea &c) {
				name				= n;

				bHasParent			= true;
				parent				= &p;

				bLocalCon			= true;
				con					= new Props_TextArea();
				*con				= c;
//				if(con->text == "") con->text = n;

				bLocalState			= true;
				statePtr			= new bool(false);

				sEditBuffer			= "";
				bHasFocus			= false;
				scrollBarContainer	= nullptr;
				scrollUp			= nullptr;
				scrollDown			= nullptr;
				bScrollOneShot		= false;
				scrollBar			= nullptr;
				label				= nullptr;
			}

			TextEdit::TextEdit(std::string n, Props_TextArea *c) {
				name				= n;

				bHasParent			= false;
				parent				= nullptr;

				bLocalCon			= false;
				con					= c;
//				if(con->text == "") con->text = n;

				bLocalState			= true;
				statePtr			= new bool(false);

				sEditBuffer			= "";
				bHasFocus			= false;
				scrollBarContainer	= nullptr;
				scrollUp			= nullptr;
				scrollDown			= nullptr;
				bScrollOneShot		= false;
				scrollBar			= nullptr;
				label				= nullptr;
			}

			TextEdit::TextEdit(Props &p, std::string n, Props_TextArea *c) {
				name				= n;

				bHasParent			= true;
				parent				= &p;

				bLocalCon			= false;
				con					= c;
//				if(con->text == "") con->text = n;

				bLocalState			= true;
				statePtr			= new bool(false);

				sEditBuffer			= "";
				bHasFocus			= false;
				scrollBarContainer	= nullptr;
				scrollUp			= nullptr;
				scrollDown			= nullptr;
				bScrollOneShot		= false;
				scrollBar			= nullptr;
				label				= nullptr;
			}

			TextEdit::~TextEdit() {
			}

			void TextEdit::init() {
				// Textedit window MUST disable padding, text takes into account padding
//				con->disablePadding();
//				con->setPadding(0);

				if(bHasParent) {
					con->scroll.bind(*parent);
					con->exec(*parent);
				}
				else con->exec();

				if(con->enableScrolling) {
					con->setWidth(con->size.constraint.x-con->iScrollSize, con->size.constraint.xType);
				}

				// Create button window with contraints to parent if present
				if (bHasParent) win = Object::Window(*parent, name, con);
				else win = Object::Window(name, con);
				win.init();

				con->text.setAnchor(CONSTRAIN_CENTER);	// DO NOT CHANGE
				con->text.setOrigin(CONSTRAIN_TOP|CONSTRAIN_LEFT);
				con->text.setWidth(con->size.x, SIZE_CONSTRAINT_ABSOLUTE);
				con->text.setHeight(con->size.y, SIZE_CONSTRAINT_ABSOLUTE);
				con->text.setPos(0, 0);
//				con->text.setPadding(con->vPadding);
//				con->text.setPadding(4);

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
					cWin.colorBack.base = &colors[colors().Tan];
					scrollBarContainer = new Window(*con, name, cWin);
					scrollBarContainer->init();

					Props_Button cButton;
					cButton.setWidth(100, SIZE_CONSTRAINT_RELATIVE);
					cButton.setHeight(con->iScrollSize, SIZE_CONSTRAINT_ABSOLUTE);
					cButton.setBorder(1, true);
					cButton.setRadius(3);
					cButton.setButtonType(Core::GUI::BUTTON_DEBOUNCE);

					cButton.colorBack.base			= &Core::gameVars->pallette.gui.textArea.scroll.base;
					cButton.colorBack.highlight		= &Core::gameVars->pallette.gui.textArea.scroll.hover;
					cButton.colorBack.active		= &Core::gameVars->pallette.gui.textArea.scroll.active;

					cButton.colorBorder.base		= &Core::gameVars->pallette.gui.textArea.scrollBorder.base;
					cButton.colorBorder.highlight	= &Core::gameVars->pallette.gui.textArea.scrollBorder.hover;
					cButton.colorBorder.active		= &Core::gameVars->pallette.gui.textArea.scrollBorder.active;

					cButton.colorText.base			= &Core::gameVars->pallette.gui.textArea.scrollText.base;
					cButton.colorText.highlight		= &Core::gameVars->pallette.gui.textArea.scrollText.hover;
					cButton.colorText.active		= &Core::gameVars->pallette.gui.textArea.scrollText.active;

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

					scrollBar = new Slider<float>(*scrollBarContainer->con, name+"_Scrollbar", &text.con->scrollPosition, cSlider);
					scrollBar->init();
				}

				if(con->bShowLabel) {
					label = new Label(*con, name, con->label);
					label->init();
				}

				bInit = true;
			}

			void TextEdit::execEdit() {
				if(bHasFocus) {
					SDL_PumpEvents();
					keyboard.event = SDL_GetKeyboardState(NULL);
					keyboard.update();
					if (keyboard.keys[SDLK_ESCAPE].bActive) {
						bHasFocus = false;
						bFocusPresent = false;
						eObjectState = STATE_NONE;
						(*con->text.bufferPtr) = sEditBuffer;
					}

					con->text.bOverwrite = keyboard.keys[SDLK_INSERT].bActive;

					bool bShift	= keyboard.keys[SDLK_LSHIFT].bActive || keyboard.keys[SDLK_RSHIFT].bActive;
					bool bCtrl	= keyboard.keys[SDLK_LCTRL].bActive || keyboard.keys[SDLK_RCTRL].bActive;
					bool bAlt	= keyboard.keys[SDLK_LALT].bActive || keyboard.keys[SDLK_RALT].bActive;

					int iModVal = 1;
					if(bShift) iModVal = 10;

					if (keyboard.keys[SDLK_RIGHT].bActive)	con->text.iCursorPosition = std::min(con->text.iCursorPosition+iModVal, (int)con->text.bufferPtr->length());
					if (keyboard.keys[SDLK_LEFT].bActive)	con->text.iCursorPosition = std::max(con->text.iCursorPosition-iModVal, 0);
					if (keyboard.keys[SDLK_HOME].bActive)	con->text.iCursorPosition = 0;
					if (keyboard.keys[SDLK_END].bActive)	con->text.iCursorPosition = con->text.bufferPtr->length();
					if (keyboard.keys[SDLK_UP].bActive)		con->text.iCursorPosition = con->text.iUpChars;
					if (keyboard.keys[SDLK_DOWN].bActive)	con->text.iCursorPosition = con->text.iDownChars;

					keyboard.editBufferAt(con->text.bufferPtr, false, &con->text.iCursorPosition, con->text.bOverwrite);

					if (keyboard.keys[SDLK_RETURN].bActive || keyboard.keys[SDLK_KP_ENTER].bActive) {
						if (bAlt) {
							bHasFocus = false;
							bFocusPresent = false;
							eObjectState = STATE_NONE;
						}
						else {
							keyboard.insertBufferAt(con->text.bufferPtr, &con->text.iCursorPosition, '\n', false);
						}
					}
				}
			}

			void TextEdit::updateObjectState(iState eExternState) {
				checkStatePtr();

				if(eExternState!=STATE_NONE && !(eExternState&STATE_UPDATE)) {
					eObjectState = eExternState;
				}
				else {
					// Check button input - Do this first so we can modify colors accordingly.
//					mState = Core::mouse->checkInput(gameVars->screen.half.x+con->pos.x, gameVars->screen.half.y-con->pos.y, con->size.x, con->size.y);
					if(!(eExternState&STATE_UPDATE)) {
						Vector2f vPos = con->getScrollPos();
						mState = Core::mouse->checkInput(gameVars->screen.half.x+vPos.x, gameVars->screen.half.y-vPos.y, con->size.x, con->size.y);
						//mState = Core::mouse->checkInput(gameVars->screen.half.x+con->pos.x, gameVars->screen.half.y-con->pos.y, con->size.x, con->size.y);
					}
					else this->mState = Core::_Mouse::MOUSE_NONE;

					if(enabled()) {
						if(!bFocusPresent && (mState&Core::_Mouse::MOUSE_LEFT)) {
							bHasFocus = true;
							bFocusPresent = true;
							sActiveObject = this->name;
							eObjectState = STATE_ACTIVE;
							sEditBuffer = *con->text.bufferPtr;
							con->text.iCursorPosition = con->text.bufferPtr->length();
						}
						else if ( !(eObjectState&STATE_ACTIVE) || ((eObjectState&STATE_ACTIVE) && !bFocusPresent) )	{
							eObjectState = STATE_NONE;
							if(sActiveObject == this->name) sActiveObject = "";
						}
					}
					else this->eObjectState = STATE_NONE;

					// Allow mouse hover at any time (used for tooltips)
					if(!(eExternState&STATE_UPDATE)) {
						if((mState&Core::_Mouse::MOUSE_HOVER)) eObjectState = eObjectState|STATE_HOVER;
						else eObjectState = eObjectState&~STATE_HOVER;
					}

				}

				if(!enabled()) eObjectState |= STATE_DISABLED;

				updateStatePtr();
			}

			void TextEdit::exec(iState eExternState) {
				if(bInit && con->visibility && ((parent!=nullptr && parent->visibility) || (parent==nullptr))) {

					// Copy constraints
					con->text.size.constraint.xAuto = con->size.constraint.xAuto;
					con->text.size.constraint.yAuto = con->size.constraint.yAuto;

					if((con->bFocusLock && !bFocusPresent) || !con->bFocusLock || (sActiveObject==name)) updateObjectState(eExternState);

					// Update constraints
					if(bHasParent) con->exec(*parent);
					else con->exec();

					if(eObjectState&STATE_ACTIVE) con->text.bEnableCursor = true;
					else con->text.bEnableCursor = false;

					// Draw button window
					win.exec(eObjectState);

					execEdit();

					// Scroll Buttons
					if(con->enableScrolling) {
						// Draw button window
						if(!bScrollOneShot) {
							win.con->setWidth(con->size.x-con->iScrollSize, SIZE_CONSTRAINT_ABSOLUTE);
							bScrollOneShot = true;
						}
						win.exec(eObjectState);

						// Update constraints, needed for autosize and direct external modifications
						if(con->text.size.isAutoSet()) {
							text.con->setWidth(con->size.x, SIZE_CONSTRAINT_ABSOLUTE);
							text.con->setHeight(con->size.y, SIZE_CONSTRAINT_ABSOLUTE);
						}
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

						// Update constraints, needed for autosize and direct external modifications
						if(con->text.size.isAutoSet()) {
							text.con->setWidth(con->size.x, SIZE_CONSTRAINT_ABSOLUTE);
							text.con->setHeight(con->size.y, SIZE_CONSTRAINT_ABSOLUTE);
						}
						text.exec(eObjectState);
						text.exec(eObjectState);

						if(con->bShowLabel) label->exec(eObjectState);
					}

					// Autosize (Needs some extra padding on textbox, not really sure why but probably due to scrolling implementation)
					if(con->size.constraint.xAuto) con->setWidth(con->text.size.x, SIZE_CONSTRAINT_ABSOLUTE);
					if(con->size.constraint.yAuto) con->setHeight(con->text.size.y+gameVars->font.vSize.y, SIZE_CONSTRAINT_ABSOLUTE);

				}
			}

			/***
			 * \brief Calls to run when object not visible/not in focus.
			 * @tparam T
			 * @tparam T
			 */
			void TextEdit::updateNoFocus() {
				if(bHasFocus) {
					bHasFocus = false;
					bFocusPresent = false;
					eObjectState = STATE_NONE;
					(*con->text.bufferPtr) = sEditBuffer;	// Revert Changes
				}

				updateObjectState(STATE_UPDATE);
			}

		}
	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUITEXTEDIT_H_ */
