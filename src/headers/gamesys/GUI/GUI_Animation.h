/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_ANIMATION_H_
#define HEADERS_GAMESYS_GUI_ANIMATION_H_

#include <iostream>
#include "../../core/core_functions.h"
#include "../../core/vao.h"
#include "../../core/matrix.h"
#include "../../core/shader.h"
#include "../../gamesys/gameVars.h"
#include "../../core/Colors.h"
#include "../../gamesys/animations.h"
#include "GUI_Constraint.h"
//#include "GUI_ToolTip.h"
#include "GUI_Objects.h"
#include "GUI_Window.h"
#include "GUI_Label.h"
#include "GUI_Line.h"

namespace Core {
	namespace GUI {
		namespace Object {

			class Animation : virtual public Base::Generic<Props_Animation> {
				public:
					Animation();
					Animation(std::string n, Props_Animation &c);
					Animation(std::string n, Props_Animation *c);
					Animation(Props &p,std::string n, Props_Animation &c);
					Animation(Props &p,std::string n, Props_Animation *c);
					~Animation();
//					Props_Window& operator[](std::string label);

//					ToolTip toolTip;															///< Tooltip info for this object
					void init();																///< Initialize thie object and its children
					void update();																///< Update local constraints, values, etc.
					void exec(iState eExternState=STATE_NONE);									///< Execute this object, draw if initialized
//					void execToolTip();															///< Execute the tooltip, called externally
//					void addItem(std::string label, int iValue);								///< Add a pie/legend item using a specific value
//					void addItem(std::string label, int iValue, Color &base, Color &hover);		///< Add a pie/legend item using a specific value and use custom color
//					void addItem(std::string label, int *iValuePtr);							///< Add a pie/legend item using a pointer to a value
//					void addItem(std::string label, int *iValuePtr, Color &base, Color &hover);	///< Add a pie/legend item using a pointer to a value and use custom color
//					void addItems(t_PieItems vItems);											///< Add a list of items in a single call
//					void removeItem(std::string label);											///< Remove an item from the pie/legend
//					t_PieItem& getItem(std::string label);										///< Get a pie/legend item reference, so it can be modified/updated externally

				protected:
					static Core::GameSys::AnimationSys *animation;
					static bool bAnimationLoaded;
//					VAO vao;																	///< Definition for a single 1% triangle wedge
//					Core::t_VectorMap<t_PieItem*> items;										///< List of pie/legend items
//					Window	*legend;															///< Legend window container
					Window	*win;
					Label	*label;																///< Object title, displayed as legend title bar
//					Label	*percent;															///< Object to show percent value for highlighted wedge
//					Line	*line;
//					static Timer blink;															///< Timer for blinking wedge highlight
//					static bool	bBlinkState;													///< Current toggle state of blinking wedge highlight
//					int iTotal;																	///< Total of all items, used for auto values
//					float fX, fY;

					void updateObjectState(iState eExternState);								///< Update the internal state of the object (eObjectState)
					void updateInput();															///< Update internal state and/or local values from keyboard/mouse input
			};

			Core::GameSys::AnimationSys *Animation::animation = new Core::GameSys::AnimationSys(*Core::audioSys);
			bool Animation::bAnimationLoaded = false;

//			Timer Animation::blink;
//			bool  Animation::bBlinkState;

			Animation::Animation() {
//				legend			= nullptr;
				label			= nullptr;
				win				= nullptr;
//				percent			= nullptr;
//				line			= nullptr;
//				bBlinkState		= false;
//				iTotal			= 0;
//				fX				= 0.0f;
//				fY				= 0.0f;
			}

			Animation::Animation(std::string n, Props_Animation &c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= true;
				con				= new Props_Animation();
				*con			= c;
				if(con->text == "") con->text = n;

//				legend			= nullptr;
				label			= nullptr;
				win				= nullptr;
//				percent			= nullptr;
//				line			= nullptr;
//				bBlinkState		= false;
//				iTotal			= 0;
//				fX				= 0.0f;
//				fY				= 0.0f;
			}

			Animation::Animation(std::string n, Props_Animation *c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

//				legend			= nullptr;
				label			= nullptr;
				win				= nullptr;
//				percent			= nullptr;
//				line			= nullptr;
//				bBlinkState		= false;
//				iTotal			= 0;
//				fX				= 0.0f;
//				fY				= 0.0f;
			}

			Animation::Animation(Props &p, std::string n, Props_Animation &c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= true;
				con				= new Props_Animation();
				*con			= c;
				if(con->text == "") con->text = n;

//				legend			= nullptr;
				label			= nullptr;
				win				= nullptr;
//				percent			= nullptr;
//				line			= nullptr;
//				bBlinkState		= false;
//				iTotal			= 0;
//				fX				= 0.0f;
//				fY				= 0.0f;
			}

			Animation::Animation(Props &p, std::string n, Props_Animation *c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

//				legend			= nullptr;
				label			= nullptr;
				win				= nullptr;
//				percent			= nullptr;
//				line			= nullptr;
//				bBlinkState		= false;
//				iTotal			= 0;
//				fX				= 0.0f;
//				fY				= 0.0f;
			}

			Animation::~Animation() {
				if(bLocalCon && con != nullptr) delete con;
//				if(legend != nullptr) delete legend;
				if(label != nullptr) delete label;
			}

//			Props_Window& Animation::operator[](std::string label) {
//				return *items[label]->colorBox->con;
//			}

			void Animation::init() {
				// Initialize
				if(!bAnimationLoaded) {
					animation->init();
					animation->load();
					animation->calc();
					bAnimationLoaded = true;

					// Start temporary looping animation
//					animation->startAnimation(128, 128, Vector3f(), Core::Vector3f(), 0, 10000, 100, 999, false);
					animation->startAnimation(200, 200, Vector3f(), Core::Vector3f(), 1, 10000, 10, 999, false);
//					animation->startAnimation(1000, 1000, Vector3f(), Core::Vector3f(), 0, 10000, 100, 999, false);
				}

				// TEMPORARY
				con->iAnimation = 1;

				// ==========================================
				//	Preliminary setup
				// ------------------------------------------
				this->id = IDs.create();
				if(bHasParent) {
					if(!con->scroll.getEnabled() && con->scroll.isScrollable()) con->scroll.bind(*parent);
					con->exec(*parent);
				}
				else {
					con->exec();
				}

				// ==========================================
				//	Setup container window
				// ------------------------------------------
				if (bHasParent) win = new Window(*parent, name, con);
				else win = new Window(name, con);
				win->init();

				// ==========================================
				//	Setup legend title
				// ------------------------------------------
				label = new Label(*win->con, name, &con->propLabel);
//				label = new Label(*con, name, &con->propLabel);
				label->init();

				// ==========================================
				//	Finalize
				// ------------------------------------------
//				toolTip.init(*con, name);
				bInit = true;
			}

			void Animation::update() {

			}

			void Animation::updateObjectState(iState eExternState) {
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

////					// Object specific logic
//					if(enabled()) {
//						if(con->scroll.isScrollable() && (mState&Core::_Mouse::MOUSE_HOVER)) {
//							updateScrollMouse();
//						}
						eObjectState = STATE_NONE;
//					}
//					else {
//						eObjectState = STATE_NONE;
//					}
				}

//				// Report if mouse is in button space
//				if(!(mState&Core::_Mouse::MOUSE_NONE)) eObjectState = eObjectState|STATE_FOCUS;
//				else eObjectState = eObjectState&~STATE_FOCUS;

				if(!enabled()) eObjectState |= STATE_DISABLED;

//				// Update the state value according to object state results
//				//updateStatePtr();
			}


			void Animation::updateInput() {
//				if(parent!=nullptr && parent->scroll.getEnabled()) {
//				}
//				else {
//					if(con->scroll.getEnabled() && !bFocusPresent && !bScrollFocus) {
//						Core::_Mouse::MOUSE_STATE wheel = Core::mouse->checkWheel();
//						if(wheel != Core::_Mouse::MOUSE_NONE) {
//
//							int modVal = 50;
//
//							const Uint8 *keyState = SDL_GetKeyboardState(NULL);
//							if (keyState[SDL_SCANCODE_LSHIFT] || keyState[SDL_SCANCODE_RSHIFT])		modVal = 100;
//							else if (keyState[SDL_SCANCODE_LCTRL] || keyState[SDL_SCANCODE_RCTRL])	modVal = 1;
//
//							switch(wheel) {
//								case Core::_Mouse::MOUSE_WHEEL_UP:		iScrollIndex -= modVal;	break;
//								case Core::_Mouse::MOUSE_WHEEL_DOWN:	iScrollIndex += modVal;	break;
//							}
//
//							iScrollIndex = std::max(iScrollIndex, 0);
//							iScrollIndex = std::min(iScrollIndex, activeContainer->scroll.iMaxScroll);
//						}
//					}
//					else if(!con->scroll.getEnabled()) {
//						iScrollIndex = 0;
//					}
//
//					con->scroll.getYRef() = iScrollIndex;
//					con->scroll.getXRef() = 0;
//				}
			}

			void Animation::exec(iState eExternState) {
				if(bInit) {
					if(con->visibility && ((parent!=nullptr && parent->visibility) || (parent==nullptr))) {

						// ==========================================
						//	Other Update Routines
						// ------------------------------------------
						update();

						// ==========================================
						//	Update Object State
						// ------------------------------------------
//						if((con->bFocusLock && !bFocusPresent) || !con->bFocusLock || (sActiveObject==id)) {
							updateObjectState(eExternState);
//
//							if(this->con->toolTip.bShow) this->toolTip.updateObjectState(this->eObjectState);
//							else this->toolTip.updateObjectState(STATE_NONE);
//						}

						// ==========================================
						//	Update Constraints
						// ------------------------------------------
						if(bHasParent) con->exec(*parent);
						else con->exec();

						// ==========================================
						//	Draw Background
						// ------------------------------------------
//						if(con->bShowBackground) win.exec(eObjectState);

						// ==========================================
						//	Set Color
						// ------------------------------------------
//						if(eObjectState&STATE_DISABLED) {
//							if(eObjectState&STATE_HOVER)	colors.PushFront(gameVars->pallette.gui.disabled.text.hover);
//							else							colors.PushFront(gameVars->pallette.gui.disabled.text.base);
//						}
//						else if(eObjectState&STATE_HOVER) 		colors.PushFront(*con->colorText.highlight);
//						else if(eObjectState&STATE_ACTIVE)		colors.PushFront(*con->colorText.highlight);
//						else 									colors.PushFront(*con->colorText.base);

						// ==========================================
						//	Draw Objects
						// ------------------------------------------
						label->exec();
						win->exec(STATE_NONE);

						//animation->draw(0);

//						con->iAnimation = 0;
//						animation->draw(*con);

//						con->iAnimation = 1;
						animation->draw(*con);
						//if(con->bShowBackground) win.exec(eObjectState);



//						textSys->draw(con, con->text, CONSTRAIN_CENTER);
//						textSys->draw(con, con->text);
//						colors.PopFront();
					}
				}
			}

			/**
			 * @brief Draw tooltip
			 */
//			void Animation::execToolTip() {
//				toolTip.exec();
//			}

			/***
			 * \brief Calls to run when object not visible/not in focus. This function is especially
			 * 		  important for Buttons because of the call to updateValuePtr();
			 */
//			void Animation::updateNoFocus() {
//				updateObjectState(STATE_UPDATE);
//				updateStatePtr();
//
//				scrollUp->updateNoFocus();
//				scrollDown->updateNoFocus();
//			}

















		} /* namespace Object */
	} /* namespace GUI */
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_ANIMATION_H_ */
