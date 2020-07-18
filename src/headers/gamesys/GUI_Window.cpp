/*
 * GUI.cpp
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#include "GUI_Window.h"

namespace Core {
	namespace GameSys {
		namespace GUIObject {
//			Window::Window(Vector2f p, Vector2f s) {
//				vPos = p;
//				vSize = s;
//			}
//
//			Window::~Window() {
//			}
//
//			void Window::init() {
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
//				std::cout << "===================================> Window Created!" << std::endl;
//				std::cout << "===================================> Window Created!" << std::endl;
//				std::cout << "===================================> Window Created!" << std::endl;
//			}
//
//			void Window::exec() {
//				glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
//				glDisable(GL_DEPTH_TEST);
//				glDisable(GL_CULL_FACE);
//
//				matrix->SetProjection(matrix->MM_ORTHO);
//				shader->use(GLS_FONT);
//
//				glActiveTexture(GL_TEXTURE0);
//				Core::sysTex->set(Core::sysTex->TEX_TESTPATTERN);
//
//				matrix->Push();
//					matrix->Translate( vPos.x, vPos.y, 0.0 );
//					matrix->Scale(vSize.x, vSize.y, 1);
//					matrix->SetTransform();
//					shader->getUniform(GLS_FONT);
//					vao.Draw();
//				matrix->Pop();
//
//				matrix->SetProjection(matrix->MM_PERSPECTIVE);
//				glEnable(GL_CULL_FACE);
//				glEnable(GL_DEPTH_TEST);
//			}
//
//			void Window::close() {
//			}
		}
	}
} /* namespace Core */
