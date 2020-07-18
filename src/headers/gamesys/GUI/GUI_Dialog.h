/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_DIALOG_H_
#define HEADERS_GAMESYS_GUI_DIALOG_H_

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
#include "../core/core_functions.h"
//#include "GUI_Window.h"

namespace Core {
	namespace GUI {
		namespace Object {
			class Dialog {		// TODO: Dialog; OK, OK_CANCEL, etc
				public:
					enum eDialogType { DIALOG_OK, DIALOG_OK_CANCEL, DIALOG_YES_NO };
					Dialog(eDialogType e, std::string t, std::string m, Vector2f p, Vector2f s, std::string b1="b1", std::string b2="b2");
					virtual ~Dialog();
					void init();
					void exec();

				private:
					eDialogType eType;
					std::string sTitle, sMessage, sButton1, sButton2;
					Vector2f vPos;
					Vector2f vSize;
//					Window window;
			};

			Dialog::Dialog(eDialogType e, std::string t, std::string m, Vector2f p, Vector2f s, std::string b1, std::string b2) {
				eType = e;
				sTitle = t;
				sMessage = m;
				if(b1=="b1") {
					switch (eType) {
						case DIALOG_OK:
							b1 = "OK";
							break;
						case DIALOG_OK_CANCEL:
							b1 = "OK";
							break;
						case DIALOG_YES_NO:
							b1 = "YES";
							break;
					}
				}
				if(b2=="b2") {
					switch (eType) {
						case DIALOG_OK:
							b2 = "";
							break;
						case DIALOG_OK_CANCEL:
							b2 = "CANCEL";
							break;
						case DIALOG_YES_NO:
							b2 = "NO";
							break;
					}
				}
			}

			Dialog::~Dialog() {
			}

			void Dialog::init() {
//				con.exec();
//
//				// TODO: get pos/size from constraints and update quad. This might result in lag long term, maybe just make windows static.
//
//				float iHalf_W = 0.5;
//				float iHalf_H = 0.5;
//				Data3f vVerts[] = { {-iHalf_W, -iHalf_H, 0},
//									{ iHalf_W,  iHalf_H, 0},
//									{-iHalf_W,  iHalf_H, 0},
//
//									{-iHalf_W, -iHalf_H, 0},
//									{ iHalf_W, -iHalf_H, 0},
//									{ iHalf_W,  iHalf_H, 0 }};
//
//				float gridCoord[4];
//				gridCoord[0] = 0.000f;
//				gridCoord[1] = 0.000f;
//				gridCoord[2] = 1.000f;
//				gridCoord[3] = 1.000f;
//
//				Data2f vTexture[6] = { { gridCoord[0], gridCoord[3] },
//									   { gridCoord[2], gridCoord[1] },
//									   { gridCoord[0], gridCoord[1] },
//									   { gridCoord[0], gridCoord[3] },
//									   { gridCoord[2], gridCoord[3] },
//									   { gridCoord[2], gridCoord[1] } };
//
//				vao.Begin(GL_TRIANGLES, 6, 6, 1);
//				vao.CopyData(GLA_VERTEX, vVerts);
//				vao.CopyData(GLA_TEXTURE, vTexture, 0);
//				vao.End();
			}

			void Dialog::exec() {
				// Draw Window
//				window.exec();

				// Draw Dialog Content


//				// Update constraints
//				con.exec();
//
//				glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
//				glDisable(GL_DEPTH_TEST);
//				glDisable(GL_CULL_FACE);
//
//				matrix->SetProjection(matrix->MM_ORTHO);
//				shader->use(GLS_MENU);
//
//				colors->SetActive(colors->COLOR_FRONT);	// Select color layer
//				colors->PushFront(colors->orange);		// Change current layer color
//
//				matrix->Push();
//					Vector2f vPos = con.getPos();
//					matrix->Translate( vPos.x, vPos.y, 0.0 );
//
//					Vector2f vSize = con.getSize();
//					matrix->Scale(vSize.x, vSize.y, 1);
//
//					matrix->SetTransform();
//					shader->data.GLS_MENU.vPos = con.getScreenPos();
//					shader->data.GLS_MENU.vSize = con.getSize();
//					shader->data.GLS_MENU.iRadius = con.getRadius();
//					shader->data.GLS_MENU.iBorder = con.getBorder();
//					shader->data.GLS_MENU.bRoundBorder = con.getRoundBorder();
//					shader->getUniform(GLS_MENU);
//					vao.Draw();
//				matrix->Pop();
//
//				matrix->SetProjection(matrix->MM_PERSPECTIVE);
//				colors->PopFront();
//				glEnable(GL_CULL_FACE);
//				glEnable(GL_DEPTH_TEST);
			}
		}
	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_DIALOG_H_ */
