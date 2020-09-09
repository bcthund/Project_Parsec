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

//					ToolTip toolTip;															///< Tooltip info for this object
					void init();																///< Initialize thie object and its children
					void update();																///< Update local constraints, values, etc.
					void exec(iState eExternState=STATE_NONE);									///< Execute this object, draw if initialized
					void start();
					void pause();
					void stop();
//					void execToolTip();															///< Execute the tooltip, called externally

				protected:
//					static Core::GameSys::AnimationSys *animation;								///< Outdated animation system (but works)

					// TODO: Make static (one map for all animations)
					static Core::t_AnimationInstance<Core::t_AnimationItem2D>	animationInstance;	///< New animation system

					Window	*win;
					Label	*label;																///< Object title, displayed as legend title bar

					void updateObjectState(iState eExternState);								///< Update the internal state of the object (eObjectState)
					void updateInput();															///< Update internal state and/or local values from keyboard/mouse input
			};

			Core::t_AnimationInstance<Core::t_AnimationItem2D> Animation::animationInstance;

			Animation::Animation() {
				label			= nullptr;
				win				= nullptr;
			}

			Animation::Animation(std::string n, Props_Animation &c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= true;
				con				= new Props_Animation();
				*con			= c;
				if(con->text == "") con->text = n;

				label			= nullptr;
				win				= nullptr;
			}

			Animation::Animation(std::string n, Props_Animation *c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

				label			= nullptr;
				win				= nullptr;
			}

			Animation::Animation(Props &p, std::string n, Props_Animation &c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= true;
				con				= new Props_Animation();
				*con			= c;
				if(con->text == "") con->text = n;

				label			= nullptr;
				win				= nullptr;
			}

			Animation::Animation(Props &p, std::string n, Props_Animation *c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

				label			= nullptr;
				win				= nullptr;
			}

			Animation::~Animation() {
				if(bLocalCon && con != nullptr) delete con;
				if(label != nullptr) delete label;
			}

			void Animation::init() {
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
				label->init();

				// ==========================================
				//	Setup animation
				// ------------------------------------------
				animationInstance.add(this->id, con->sAnimationImage, 1, 1, con->iLoop, con->iUpdateRate, con->iSample);
				if(con->bStartAnimation) animationInstance.start(this->id);

				// ==========================================
				//	Finalize
				// ------------------------------------------
//				toolTip.init(*con, name);
				bInit = true;
			}

			void Animation::update() {
				// Update any possible changes
				animationInstance[this->id].rate = con->iUpdateRate;
				animationInstance[this->id].iSample = con->iSample;
				animationInstance[this->id].loop = con->iLoop;
				animationInstance[this->id].id = animationSys[con->sAnimationImage].id;

				animationInstance.update(this->id);
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

//					// Object specific logic
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

			void Animation::start() {
				//if(!animation2[this->id].bActive ||
				animationInstance.start(this->id);
			}

			void Animation::pause() {
				animationInstance.pause(this->id);
			}

			void Animation::stop() {
				animationInstance.stop(this->id);
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
						//	Draw Supplemental
						// ------------------------------------------
						if(con->bShowLabel) label->exec();
						if(con->bShowBackground) win->exec(STATE_NONE);

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

						matrix->Push();
							Vector2f vPos;
							if(con->scroll.isScrollable() && (parent!=nullptr && parent->scroll.getEnabled())) vPos = con->getScrollPos();
							else vPos = con->getPos();
							matrix->Translate( vPos.x, vPos.y, 0.0 );

							Vector2f vSize = con->getSize();
							matrix->Scale(vSize.x, vSize.y, 1);

							matrix->SetTransform();
							animationInstance.draw(this->id);
						matrix->Pop();

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
