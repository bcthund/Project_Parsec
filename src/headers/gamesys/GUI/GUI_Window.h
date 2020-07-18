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
#include "GUI_Constraint.h"
//#include "GUI_ToolTip.h"
#include "GUI_Objects.h"
#include "../../core/Colors.h"

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
			class Window : public Base::Generic<Props_Window> {
//					friend class GUI_Container;
//					friend class Window;
				public:
					Window();
					Window(std::string n, Props_Window c);
					Window(Props &p,std::string n, Props_Window c);
					Window(std::string n, Props_Window *c);
					Window(Props &p,std::string n, Props_Window *c);
					~Window();

//					ToolTip toolTip;
					void init();
					void update();
//					void toggle()	{	con->visibility = !con->visibility;	}
//					void exec(bool bActive);
					void exec(iState eExternState=STATE_NONE);

				protected:
					VAO vao;
					void updateObjectState(iState eExternState);

			};

			Window::Window() {}

			Window::Window(std::string n, Props_Window c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= true;
				con				= new Props_Window();
				*con			= c;
			}

			Window::Window(Props &p, std::string n, Props_Window c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= true;
				con				= new Props_Window();
				*con			= c;
			}

			Window::Window(std::string n, Props_Window *c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= false;
				con				= c;
			}

			Window::Window(Props &p, std::string n, Props_Window *c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= false;
				con				= c;
			}

			Window::~Window() {
				if(bLocalCon && con != nullptr) delete con;
			}

			void Window::init() {
				if(bHasParent) con->exec(*parent);
				else con->exec();

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
				bInit = true;
			}

			void Window::update() {
				int iRadius = fmin(fmin(con->radius, con->size.x/2.0f), con->size.y/2.0f);
				con->setRadius(iRadius);
			}

			void Window::updateObjectState(iState eExternState) {

				if(eExternState!=STATE_NONE && !(eExternState&STATE_UPDATE)) eObjectState = eExternState;
				else eObjectState = STATE_NONE;

				if(!enabled()) eObjectState |= STATE_DISABLED;
			}

			void Window::exec(iState eExternState) {
				if(bInit) {
					if(con->visibility && ((parent!=nullptr && parent->visibility) || (parent==nullptr))) {
						// Update constaints in case they have changed
						if(bHasParent) con->exec(*parent);
						else con->exec();

						update();

						glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
						glDisable(GL_DEPTH_TEST);
						glDisable(GL_CULL_FACE);

						matrix->SetProjection(matrix->MM_ORTHO);
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
							colors.PushFront(*con->windowColor.back.active);
							colors.PushBack(*con->windowColor.border.active);
						}
						else if(eObjectState&STATE_HOVER) {
							colors.PushFront(*con->windowColor.back.highlight);
							colors.PushBack(*con->windowColor.border.highlight);
						}
						else {
							colors.PushFront(*con->windowColor.back.base);
							colors.PushBack(*con->windowColor.border.base);
						}

						// Enable border hover
						if(eObjectState&STATE_HOVER) border = con->borderHover;
						else border = con->borderNormal;

						matrix->Push();
							Vector2f vPos = con->getPos();
							matrix->Translate( vPos.x, vPos.y, 0.0 );

							Vector2f vSize = con->getSize();
							matrix->Scale(vSize.x, vSize.y, 1);

							matrix->SetTransform();
							shader->data.GLS_MENU.vPos				= con->getPos();
							shader->data.GLS_MENU.vSize				= con->getSize();
							shader->data.GLS_MENU.iRadius			= con->getRadius();
							shader->data.GLS_MENU.iBorder			= border;
							shader->data.GLS_MENU.bRoundBorder		= con->getRoundBorder();
							shader->data.GLS_MENU.bEnableStipple	= con->bEnableStipple;
							if(con->bEnableStipple) {
								shader->data.GLS_MENU.stipple = con->stipple;

								if(eObjectState&STATE_DISABLED) {
									if(eObjectState&STATE_HOVER)	shader->data.GLS_MENU.stippleColor = &gameVars->pallette.gui.disabled.stipple.hover;
									else							shader->data.GLS_MENU.stippleColor = &gameVars->pallette.gui.disabled.stipple.base;
								}
								else if(eObjectState&STATE_ACTIVE) shader->data.GLS_MENU.stippleColor = con->stippleColor.active;
								else if(eObjectState&STATE_HOVER) shader->data.GLS_MENU.stippleColor = con->stippleColor.highlight;
								else shader->data.GLS_MENU.stippleColor = con->stippleColor.base;
							}
							shader->getUniform(GLS_MENU);
							vao.Draw();
						matrix->Pop();

						matrix->SetProjection(matrix->MM_PERSPECTIVE);
						colors.PopFront();
						colors.PopBack();
						glEnable(GL_CULL_FACE);
						glEnable(GL_DEPTH_TEST);
					}
				}
			}
		}
	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_WINDOW_H_ */
