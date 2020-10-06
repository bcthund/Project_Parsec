/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_WINDOW_H_
#define HEADERS_GAMESYS_GUI_WINDOW_H_

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
#include "../../core/core_functions.h"
#include "../../core/vao.h"
#include "../../core/matrix.h"
#include "../../core/shader.h"
#include "../../gamesys/gameVars.h"
#include "../../core/Colors.h"
#include "GUI_Constraint.h"
//#include "GUI_ToolTip.h"
#include "GUI_Objects.h"

/*
 * FIXME: Add window decorations (Border and Corner Stipple patterns) How?
 * 	- Could add 5-8 more stipple patterns (seems like a lot of data to pass)
 * 	- 4 patterns for each corner (1 pattern and transform code?)
 * 	- 4 patterns for each edge (1 pattern and transform code?)
 * 	- Whenever drawing the border use the stipple pattern, and that's it
 *
 */

namespace Core {
	namespace GUI {
		namespace Object {
			// Dummy class for containers
//			class Container : virtual public Base::Generic<Props_Container>, virtual public Window {
//				Container() { iScrollIndex	= 0; }
//
//				Container(std::string n, Props_Container &c) {
//					name			= n;
//
//					bHasParent		= false;
//					parent			= nullptr;
//
//					bLocalCon		= true;
//					con				= new Props_Container();
//					*con			= c;
//					if(con->text == "") con->text = n;
//
//					iScrollIndex	= 0;
//				}
//
//				Container(Props &p, std::string n, Props_Container &c) {
//					name			= n;
//
//					bHasParent		= true;
//					parent			= &p;
//
//					bLocalCon		= true;
//					con				= new Props_Container();
//					*con			= c;
//					if(con->text == "") con->text = n;
//
//					iScrollIndex	= 0;
//				}
//
//				Container(std::string n, Props_Container *c) {
//					name			= n;
//
//					bHasParent		= false;
//					parent			= nullptr;
//
//					bLocalCon		= false;
//					con				= c;
//					if(con->text == "") con->text = n;
//
//					iScrollIndex	= 0;
//				}
//
//				Container(Props &p, std::string n, Props_Container *c) {
//					name			= n;
//
//					bHasParent		= true;
//					parent			= &p;
//
//					bLocalCon		= false;
//					con				= c;
//					if(con->text == "") con->text = n;
//
//					iScrollIndex	= 0;
//				}
//
//				~Container() {
//					if(bLocalCon && con != nullptr) delete con;
//				}
//			};

			class Window : virtual public Base::Generic<Props_Window> {
//					friend class GUI_Container;
//					friend class Window;
				public:
					Window();
//					Window(const Window src);
					Window(std::string n, Props_Window &c);
					Window(Props &p,std::string n, Props_Window &c);
					Window(std::string n, Props_Window *c);
					Window(Props &p,std::string n, Props_Window *c);
					~Window();

//					ToolTip toolTip;
					void init();
					void update();
//					void toggle()	{	con->visibility = !con->visibility;	}
//					void exec(bool bActive);
					iState exec(iState eExternState=STATE_NONE);

				protected:
					VAO vao;
					int iScrollIndex;
					void updateObjectState(iState eExternState);
					void updateScrollMouse();
					void checkScrollVisibility();
			};

			Window::Window() { iScrollIndex	= 0; }

//			Window::Window(const Window src) {
//				Base::Generic<Props_Window>.Generic<Props_Window>(src);
//
//			}

			Window::Window(std::string n, Props_Window &c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= true;
				con				= new Props_Window();
				*con			= c;
				if(con->text == "") con->text = n;

				iScrollIndex	= 0;
			}

			Window::Window(Props &p, std::string n, Props_Window &c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= true;
				con				= new Props_Window();
				*con			= c;
				if(con->text == "") con->text = n;

				iScrollIndex	= 0;
			}

			Window::Window(std::string n, Props_Window *c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

				iScrollIndex	= 0;
			}

			Window::Window(Props &p, std::string n, Props_Window *c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

				iScrollIndex	= 0;
			}

			Window::~Window() {
				if(bLocalCon && con != nullptr) delete con;
			}

			void Window::init() {
				this->id = IDs.create();

				if(bHasParent) {
					if(!con->scroll.getEnabled() && con->scroll.isScrollable()) con->scroll.bind(*parent);
					con->exec(*parent);
				}
				else {
					con->exec();
				}

				float iHalf_W = 0.5;
				float iHalf_H = 0.5;
				Data3f vVerts[] = { {-iHalf_W, -iHalf_H, 0},
									{ iHalf_W,  iHalf_H, 0},
									{-iHalf_W,  iHalf_H, 0},

									{-iHalf_W, -iHalf_H, 0},
									{ iHalf_W, -iHalf_H, 0},
									{ iHalf_W,  iHalf_H, 0 }};

				float gridCoord[4];
				gridCoord[0] = 0.000f;
				gridCoord[1] = 0.000f;
				gridCoord[2] = 1.000f;
				gridCoord[3] = 1.000f;

				Data2f vTexture[6] = { { gridCoord[0], gridCoord[3] },
									   { gridCoord[2], gridCoord[1] },
									   { gridCoord[0], gridCoord[1] },
									   { gridCoord[0], gridCoord[3] },
									   { gridCoord[2], gridCoord[3] },
									   { gridCoord[2], gridCoord[1] } };

				vao.Begin(GL_TRIANGLES, 6, 6, 1);
				vao.CopyData(GLA_VERTEX, vVerts);
				vao.CopyData(GLA_TEXTURE, vTexture, 0);
				vao.End();

				timeFocusDebounce.start();
				bInit = true;
//				debug.log("[5-3]: Window::init()");
			}

			void Window::update() {
				if (con->bResizeRadius) {
					int iRadius = fmin(fmin(con->radius, con->size.x/2.0f), con->size.y/2.0f);
					con->setRadius(iRadius);
				}
			}

//			void Window::updateObjectState(iState eExternState) {
//				// Default - ALWAYS do this
//				if(eExternState!=STATE_NONE && !(eExternState&STATE_UPDATE)) eObjectState = eExternState;
//				else eObjectState = STATE_NONE;
//
//				mState = Core::mouse->checkInput(gameVars->screen.activeProjection->half.x+con->pos.x, gameVars->screen.activeProjection->half.y-con->pos.y, con->size.x, con->size.y);
//				// Report if mouse is in button space (debounce turning off)
//				if(mState!=Core::_Mouse::MOUSE_NONE) { eObjectState = eObjectState|STATE_FOCUS; timeFocusDebounce.split(); }
//				else if (timeFocusDebounce.get_splitdiff() > iFocusDebounce) eObjectState = eObjectState&~STATE_FOCUS;
//
//				// TODO: Manage mouse scrolling
//				// TODO: Scrolling adjusts iScrollIndex but does nothing here
//				// TODO: iScrollIndex is used by children using this as parent to offset their position
//				// TODO: Children should automatically adjust position based on parent data
//				// TODO: By default window scrolling is disabled because windows are used by so many objects as a base
//				// TODO: Make sure scissor does not move (it shouldn't but be sure)
//
//				if(!enabled()) eObjectState |= STATE_DISABLED;
//			}

			void Window::updateObjectState(iState eExternState) {
				// Uncomment if object state can be set externally
				//checkStatePtr();

				// Generic state handler
				if((eExternState!=STATE_NONE) && !(eExternState&STATE_UPDATE)) {
					eObjectState = eExternState;
				}
				else {
					if(!(eExternState&STATE_UPDATE)) {
						if(parent!=nullptr && parent->scroll.getEnabled()) {
							Vector2f vPos = con->getScrollPos();
							mState = Core::mouse->checkInput(gameVars->screen.activeProjection->half.x+vPos.x, gameVars->screen.activeProjection->half.y-vPos.y, con->size.x, con->size.y);
						}
						else {
							mState = Core::mouse->checkInput(gameVars->screen.activeProjection->half.x+con->pos.x, gameVars->screen.activeProjection->half.y-con->pos.y, con->size.x, con->size.y);
						}
					}
					else mState = Core::_Mouse::MOUSE_NONE;

//					// Object specific logic
					if(enabled()) {
						if(con->scroll.isScrollable() && (mState&Core::_Mouse::MOUSE_HOVER)) {
							updateScrollMouse();
						}
						eObjectState = STATE_NONE;

						if(this->mState&Core::_Mouse::MOUSE_HOVER) this->eObjectState = this->eObjectState|STATE_HOVER;
						else this->eObjectState = this->eObjectState&~STATE_HOVER;

					}
					else {
						eObjectState = STATE_NONE;
					}
				}

				// Report if mouse is in button space
				if(!(mState&Core::_Mouse::MOUSE_NONE)) eObjectState = eObjectState|STATE_FOCUS;
				else eObjectState = eObjectState&~STATE_FOCUS;

				if(!enabled()) eObjectState |= STATE_DISABLED;

				// Update the state value according to object state results
				//updateStatePtr();
			}


			void Window::updateScrollMouse() {
				if(parent!=nullptr && parent->scroll.getEnabled()) {
				}
				else {
					if(con->scroll.getEnabled() && !bFocusPresent && !bScrollFocus) {
						Core::_Mouse::MOUSE_STATE wheel = Core::mouse->checkWheel();
						if(wheel != Core::_Mouse::MOUSE_NONE) {

							int modVal = 50;

							const Uint8 *keyState = SDL_GetKeyboardState(NULL);
							if (keyState[SDL_SCANCODE_LSHIFT] || keyState[SDL_SCANCODE_RSHIFT])		modVal = 100;
							else if (keyState[SDL_SCANCODE_LCTRL] || keyState[SDL_SCANCODE_RCTRL])	modVal = 5;

							switch(wheel) {
								case Core::_Mouse::MOUSE_WHEEL_UP:		iScrollIndex -= modVal;	break;
								case Core::_Mouse::MOUSE_WHEEL_DOWN:	iScrollIndex += modVal;	break;
							}

							iScrollIndex = std::max(iScrollIndex, 0);
							iScrollIndex = std::min(iScrollIndex, activeContainer->scroll.iMaxScroll);
						}
					}
					else if(!con->scroll.getEnabled()) {
						iScrollIndex = 0;
					}

					con->scroll.getYRef() = iScrollIndex;
					con->scroll.getXRef() = 0;
				}
			}

			/**
			 * @brief Check if this objects position is greater than max scroll value
			 */
			void Window::checkScrollVisibility() {
				Vector2f vPos = con->getPos();
				vPos.x += Core::gameVars->screen.activeProjection->half.x;
				vPos.y = Core::gameVars->screen.activeProjection->half.y - vPos.y;

				activeContainer->scroll.iMaxScroll = std::max(activeContainer->scroll.iMaxScroll, int(vPos.y));
//				activeContainer->scroll.iMaxScroll = std::max(activeContainer->scroll.iMaxScroll, int(vPos.y-(con->size.y)));
			}

			iState Window::exec(iState eExternState) {
				if(bInit) {
					if(con->visibility && ((parent!=nullptr && parent->visibility) || (parent==nullptr))) {
						// Check scroll visibility
						if(Core::scissor.getActive()) checkScrollVisibility();

						// Update constaints in case they have changed
						if(bHasParent) con->exec(*parent);
						else con->exec();

						update();

						if(con->bTextured && con->tex != nullptr) {
							glActiveTexture(0);
	//						sysTex->set(sysTex->TEX_GRASS);
//							sysTex->set(sysTex->TEX_GRASSYROCK);
							con->tex->Set(con->texRef);
						}

						glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
						glDisable(GL_DEPTH_TEST);
						glDisable(GL_CULL_FACE);

						matrix->setProjection(matrix->MM_ORTHO, "ortho");
						shader->use(GLS_MENU);

						//if(!bFocusPresent) updateObjectState(eExternState);
						updateObjectState(eExternState);

						if(eObjectState&STATE_DISABLED) {
							if(eObjectState&STATE_HOVER) {
								colors.PushFront(gameVars->pallette.gui.disabled.base.hover);
								colors.PushBack(gameVars->pallette.gui.disabled.border.hover);
							}
							else {
								colors.PushFront(gameVars->pallette.gui.disabled.base.base);
								colors.PushBack(gameVars->pallette.gui.disabled.border.base);
							}
						}
						else if(eObjectState&STATE_ACTIVE) {
							colors.PushFront(*con->colorBack.active);
							colors.PushBack(*con->colorBorder.active);
						}
						else if(eObjectState&STATE_HOVER) {
							colors.PushFront(*con->colorBack.highlight);
							colors.PushBack(*con->colorBorder.highlight);
						}
						else {
							colors.PushFront(*con->colorBack.base);
							colors.PushBack(*con->colorBorder.base);
						}

						// Enable border hover
						if(eObjectState&STATE_HOVER) border = con->borderHover;
						else border = con->borderNormal;

						matrix->Push();

							// Only scroll this item if the parent has scrolling enabled
							Vector2f vPos;
							if(con->scroll.isScrollable() && (parent!=nullptr && parent->scroll.getEnabled())) vPos = con->getScrollPos();
							else vPos = con->getPos();
							matrix->Translate( vPos.x, vPos.y, 0.0 );

							Vector2f vSize = con->getSize();
							matrix->Scale(vSize.x, vSize.y, 1);

							matrix->SetTransform();
							//shader->data.GLS_MENU.vPos				= con->getPos();
							shader->vars.GLS_MENU.vPos				= vPos;
							shader->vars.GLS_MENU.vSize				= con->getSize();
							shader->vars.GLS_MENU.iRadius			= con->getRadius();
							shader->vars.GLS_MENU.iBorder			= border;
							shader->vars.GLS_MENU.bRoundBorder		= con->getRoundBorder();
							shader->vars.GLS_MENU.bEnableStipple	= con->bEnableStipple;

							shader->vars.GLS_MENU.bTextured		= (con->bTextured && con->tex != nullptr);
							if(con->bTextured) {
								shader->vars.GLS_MENU.fScroll	= (con->getScrollPos().y/vSize.y)*con->fTextureScrollRate;
							}
							else shader->vars.GLS_MENU.fScroll	= 0.0f;

							if(con->bEnableStipple) {
								shader->vars.GLS_MENU.stipple = con->stipple;

								if(eObjectState&STATE_DISABLED) {
									if(eObjectState&STATE_HOVER)	shader->vars.GLS_MENU.stippleColor = &gameVars->pallette.gui.disabled.stipple.hover;
									else							shader->vars.GLS_MENU.stippleColor = &gameVars->pallette.gui.disabled.stipple.base;
								}
								else if(eObjectState&STATE_ACTIVE) shader->vars.GLS_MENU.stippleColor = con->stippleColor.active;
								else if(eObjectState&STATE_HOVER) shader->vars.GLS_MENU.stippleColor = con->stippleColor.highlight;
								else shader->vars.GLS_MENU.stippleColor = con->stippleColor.base;
							}
							shader->getUniform(GLS_MENU);
							vao.Draw();
						matrix->Pop();

						matrix->setProjection(matrix->MM_PERSPECTIVE, "standard");
						colors.PopFront();
						colors.PopBack();
						glEnable(GL_CULL_FACE);
						glEnable(GL_DEPTH_TEST);
					}

					return eObjectState;
				}

				return STATE_NONE;
			}




		}
	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_WINDOW_H_ */
