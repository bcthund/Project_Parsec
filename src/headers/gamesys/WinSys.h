/*
 * _WinSys.h
 *
 *  Created on: Sep 19, 2010
 *      Author: bcthund
 */

#ifndef _WinSys_H_
#define _WinSys_H_

#include <iostream>
//#include "../texture.h"

#include "../core/matrix.h"
#include "../core/shader.h"
#include "../core/Colors.h"
#include "../core/core_functions.h"

// TODO: REMOVE THIS CLASS, NO LONGER NEEDED WITH NEW GUI

namespace Core {
	namespace GameSys {
		class _WinSys {
			private:
//				Matrix_System * matrix;
//				Shader_System * shader;
//				Vector4f tempColor;
				Vector4f currentColor,
						 cFrontColor,	// Current front(text) color
						 cBackColor;	// Curreent back(window) color
				uint uiNumTextures,
					 uiRecordSize;
				std::string sFilename,
							sDir,
							sTexDir;
				GLuint index;
				GLfloat (*pArray)[2];
				VAO vao[26];
				Texture texture;
				float fMouseDelay, fMouseDelayConst;	//Delay for repeat mouse clicks
				void start(int x, int y, short int iBorder, Core::_Colors::_ACTIVE_COLOR eColor=Core::_Colors::COLOR_FRONT);
				void update();
				void stop();

			struct Coords {
				GLfloat a00[4][2];
				GLfloat a01[4][2];
				GLfloat a02[4][2];
				GLfloat a03[4][2];
				GLfloat a04[4][2];
				GLfloat a05[4][2];
				GLfloat a06[4][2];
				GLfloat a07[4][2];
				GLfloat a08[4][2];
				GLfloat a09[4][2];
				GLfloat a10[4][2];
				GLfloat a11[4][2];
				GLfloat a12[4][2];
				GLfloat a13[4][2];
				GLfloat a14[4][2];
				GLfloat a15[4][2];
				GLfloat a16[4][2];
				GLfloat a17[4][2];
				GLfloat a18[4][2];
				GLfloat a19[4][2];
				GLfloat a20[4][2];
				GLfloat a21[4][2];
				GLfloat a22[4][2];
				GLfloat a23[4][2];
				GLfloat a24[4][2];

			} coords;

			protected:
			friend class _GameSys;

			public:
			static struct _DRAWMODE {
				enum LIST {	NORMAL = 0,			// Draw background with border
							BORDER_ONLY,		// Draw border only
							NO_BORDER,			// Draw background only
							SELECTION	};		// Draw selection border (border only)
			} DRAWMODE;

			_WinSys(/*Matrix_System &m, Shader_System &s*/);
			bool load();
			bool calc();

			void draw(int x, int y, int w, int h, bool textOffset, Color backColor, short int iBorder);

			void drawT(int x, int y, int w, short int iBorder);
			void drawT(int x, int y, int w, Color fontColor, short int iBorder);
			void drawB(int x, int y, int w, short int iBorder);
			void drawB(int x, int y, int w, Color fontColor, short int iBorder);
			void drawL(int x, int y, int h, short int iBorder);
			void drawL(int x, int y, int h, Color fontColor, short int iBorder);
			void drawR(int x, int y, int h, short int iBorder);
			void drawR(int x, int y, int h, Color fontColor, short int iBorder);

			void drawTBorder(int x, int y, int w, short int iBorder);
			void drawTBorder(int x, int y, int w, Color fontColor, short int iBorder);
			void drawiBorder(int x, int y, int w, short int iBorder);
			void drawiBorder(int x, int y, int w, Color fontColor, short int iBorder);
			void drawLBorder(int x, int y, int h, short int iBorder);
			void drawLBorder(int x, int y, int h, Color fontColor, short int iBorder);
			void drawRBorder(int x, int y, int h, short int iBorder);
			void drawRBorder(int x, int y, int h, Color fontColor, short int iBorder);

			void drawHSpace(int x, int y, int w, short int iBorder);
			void drawHSpace(int x, int y, int w, Color fontColor, short int iBorder);
			void drawVSpace(int x, int y, int h, short int iBorder);
			void drawVSpace(int x, int y, int h, Color fontColor, short int iBorder);

			void drawHLine(int x, int y, int w, short int iBorder);
			void drawHLine(int x, int y, int w, Color fontColor, short int iBorder);
			void drawVLine(int x, int y, int w, short int iBorder);
			void drawVLine(int x, int y, int w, Color fontColor, short int iBorder);

			void drawH(int x, int y, int w, short int iBorder);
			void drawH(int x, int y, int w, Color fontColor, short int iBorder);
			void drawV(int x, int y, int w, short int iBorder);
			void drawV(int x, int y, int w, Color fontColor, short int iBorder);

			void drawHDiv(int x, int y, int w, short int iBorder);
			void drawHDiv(int x, int y, int w, Color fontColor, short int iBorder);
			void drawVDiv(int x, int y, int h, short int iBorder);
			void drawVDiv(int x, int y, int h, Color fontColor, short int iBorder);

			void drawSingle(int x, int y, int w, int h, int what, short int iBorder);
			void drawSingle(int x, int y, int w, int h, int what, Color fontColor, short int iBorder);
		};

		_WinSys::_WinSys(/*Matrix_System &m, Shader_System &s*/) {
//			matrix = &m;
//			shader = &s;

			index = 0;
			pArray = { 0 };
			fMouseDelay=0;
			fMouseDelayConst	= 100;
			//Menu System
		//	texture_format = GL_RGBA;
			uiNumTextures		= 5;
			uiRecordSize		= 32;
			sFilename			= "win.bin";
			sDir				= "./system/";
			sTexDir				= "./texture/system/";

		}

		bool _WinSys::load() {
			try
			{
				//            .................................................................Done
				std::cout << "Load WinSys......................................................";
				MemBlock memBlock;
				std::string theImage;
				texture.Begin(uiNumTextures);
				readFile((sDir+sFilename), memBlock);

				for (int d=0; d<memBlock.size; d+=uiRecordSize) {
					int theId = 0;
					for (int i=0; i<4; i++) theId+=(unsigned char)memBlock.buffer[i+d];

					theImage = "";
					for (int i=4; i<32; i++)
						if (memBlock.buffer[i+d]!=0) theImage+=(unsigned char)memBlock.buffer[i+d];
						else break;

					texture.Load(sTexDir, theImage, theId, false);
				}
				std::cout << "Done" << std::endl;
				return true;
			}
			catch(...) {
				std::cout << "Failed" << std::endl;
				return false;
			}
		}

		bool _WinSys::calc() {
			try {
				//            .................................................................Done
				std::cout << "Calc WinSys......................................................";
				coords.a00[0][0] = 0.00;
				coords.a00[0][1] = 0.00;
				coords.a00[1][0] = 0.00;
				coords.a00[1][1] = 0.20;
				coords.a00[2][0] = 0.20;
				coords.a00[2][1] = 0.20;
				coords.a00[3][0] = 0.20;
				coords.a00[3][1] = 0.00;

				coords.a01[0][0] = 0.20;
				coords.a01[0][1] = 0.00;
				coords.a01[1][0] = 0.20;
				coords.a01[1][1] = 0.20;
				coords.a01[2][0] = 0.40;
				coords.a01[2][1] = 0.20;
				coords.a01[3][0] = 0.40;
				coords.a01[3][1] = 0.00;

				coords.a02[0][0] = 0.40;
				coords.a02[0][1] = 0.00;
				coords.a02[1][0] = 0.40;
				coords.a02[1][1] = 0.20;
				coords.a02[2][0] = 0.60;
				coords.a02[2][1] = 0.20;
				coords.a02[3][0] = 0.60;
				coords.a02[3][1] = 0.00;

				coords.a03[0][0] = 0.60;
				coords.a03[0][1] = 0.00;
				coords.a03[1][0] = 0.60;
				coords.a03[1][1] = 0.20;
				coords.a03[2][0] = 0.80;
				coords.a03[2][1] = 0.20;
				coords.a03[3][0] = 0.80;
				coords.a03[3][1] = 0.00;

				coords.a04[0][0] = 0.80;
				coords.a04[0][1] = 0.00;
				coords.a04[1][0] = 0.80;
				coords.a04[1][1] = 0.20;
				coords.a04[2][0] = 1.00;
				coords.a04[2][1] = 0.20;
				coords.a04[3][0] = 1.00;
				coords.a04[3][1] = 0.00;

				coords.a05[0][0] = 0.00;
				coords.a05[0][1] = 0.20;
				coords.a05[1][0] = 0.00;
				coords.a05[1][1] = 0.40;
				coords.a05[2][0] = 0.20;
				coords.a05[2][1] = 0.40;
				coords.a05[3][0] = 0.20;
				coords.a05[3][1] = 0.20;

				coords.a06[0][0] = 0.20;
				coords.a06[0][1] = 0.20;
				coords.a06[1][0] = 0.20;
				coords.a06[1][1] = 0.40;
				coords.a06[2][0] = 0.40;
				coords.a06[2][1] = 0.40;
				coords.a06[3][0] = 0.40;
				coords.a06[3][1] = 0.20;

				coords.a07[0][0] = 0.40;
				coords.a07[0][1] = 0.20;
				coords.a07[1][0] = 0.40;
				coords.a07[1][1] = 0.40;
				coords.a07[2][0] = 0.60;
				coords.a07[2][1] = 0.40;
				coords.a07[3][0] = 0.60;
				coords.a07[3][1] = 0.20;

				coords.a08[0][0] = 0.60;
				coords.a08[0][1] = 0.20;
				coords.a08[1][0] = 0.60;
				coords.a08[1][1] = 0.40;
				coords.a08[2][0] = 0.80;
				coords.a08[2][1] = 0.40;
				coords.a08[3][0] = 0.80;
				coords.a08[3][1] = 0.20;

				coords.a09[0][0] = 0.80;
				coords.a09[0][1] = 0.20;
				coords.a09[1][0] = 0.80;
				coords.a09[1][1] = 0.40;
				coords.a09[2][0] = 1.00;
				coords.a09[2][1] = 0.40;
				coords.a09[3][0] = 1.00;
				coords.a09[3][1] = 0.20;

				coords.a10[0][0] = 0.00;
				coords.a10[0][1] = 0.40;
				coords.a10[1][0] = 0.00;
				coords.a10[1][1] = 0.60;
				coords.a10[2][0] = 0.20;
				coords.a10[2][1] = 0.60;
				coords.a10[3][0] = 0.20;
				coords.a10[3][1] = 0.40;

				coords.a11[0][0] = 0.20;
				coords.a11[0][1] = 0.40;
				coords.a11[1][0] = 0.20;
				coords.a11[1][1] = 0.60;
				coords.a11[2][0] = 0.40;
				coords.a11[2][1] = 0.60;
				coords.a11[3][0] = 0.40;
				coords.a11[3][1] = 0.40;

				coords.a12[0][0] = 0.40;
				coords.a12[0][1] = 0.40;
				coords.a12[1][0] = 0.40;
				coords.a12[1][1] = 0.60;
				coords.a12[2][0] = 0.60;
				coords.a12[2][1] = 0.60;
				coords.a12[3][0] = 0.60;
				coords.a12[3][1] = 0.40;

				coords.a13[0][0] = 0.60;
				coords.a13[0][1] = 0.40;
				coords.a13[1][0] = 0.60;
				coords.a13[1][1] = 0.60;
				coords.a13[2][0] = 0.80;
				coords.a13[2][1] = 0.60;
				coords.a13[3][0] = 0.80;
				coords.a13[3][1] = 0.40;

				coords.a14[0][0] = 0.80;
				coords.a14[0][1] = 0.40;
				coords.a14[1][0] = 0.80;
				coords.a14[1][1] = 0.60;
				coords.a14[2][0] = 1.00;
				coords.a14[2][1] = 0.60;
				coords.a14[3][0] = 1.00;
				coords.a14[3][1] = 0.40;

				coords.a15[0][0] = 0.00;
				coords.a15[0][1] = 0.60;
				coords.a15[1][0] = 0.00;
				coords.a15[1][1] = 0.80;
				coords.a15[2][0] = 0.20;
				coords.a15[2][1] = 0.80;
				coords.a15[3][0] = 0.20;
				coords.a15[3][1] = 0.60;

				coords.a16[0][0] = 0.20;
				coords.a16[0][1] = 0.60;
				coords.a16[1][0] = 0.20;
				coords.a16[1][1] = 0.80;
				coords.a16[2][0] = 0.40;
				coords.a16[2][1] = 0.80;
				coords.a16[3][0] = 0.40;
				coords.a16[3][1] = 0.60;

				coords.a17[0][0] = 0.40;
				coords.a17[0][1] = 0.60;
				coords.a17[1][0] = 0.40;
				coords.a17[1][1] = 0.80;
				coords.a17[2][0] = 0.60;
				coords.a17[2][1] = 0.80;
				coords.a17[3][0] = 0.60;
				coords.a17[3][1] = 0.60;

				coords.a18[0][0] = 0.60;
				coords.a18[0][1] = 0.60;
				coords.a18[1][0] = 0.60;
				coords.a18[1][1] = 0.80;
				coords.a18[2][0] = 0.80;
				coords.a18[2][1] = 0.80;
				coords.a18[3][0] = 0.80;
				coords.a18[3][1] = 0.60;

				coords.a19[0][0] = 0.80;
				coords.a19[0][1] = 0.60;
				coords.a19[1][0] = 0.80;
				coords.a19[1][1] = 0.80;
				coords.a19[2][0] = 1.00;
				coords.a19[2][1] = 0.80;
				coords.a19[3][0] = 1.00;
				coords.a19[3][1] = 0.60;

				coords.a20[0][0] = 0.00;
				coords.a20[0][1] = 0.80;
				coords.a20[1][0] = 0.00;
				coords.a20[1][1] = 1.00;
				coords.a20[2][0] = 0.20;
				coords.a20[2][1] = 1.00;
				coords.a20[3][0] = 0.20;
				coords.a20[3][1] = 0.80;

				coords.a21[0][0] = 0.20;
				coords.a21[0][1] = 0.80;
				coords.a21[1][0] = 0.20;
				coords.a21[1][1] = 1.00;
				coords.a21[2][0] = 0.40;
				coords.a21[2][1] = 1.00;
				coords.a21[3][0] = 0.40;
				coords.a21[3][1] = 0.80;

				coords.a22[0][0] = 0.40;
				coords.a22[0][1] = 0.80;
				coords.a22[1][0] = 0.40;
				coords.a22[1][1] = 1.00;
				coords.a22[2][0] = 0.60;
				coords.a22[2][1] = 1.00;
				coords.a22[3][0] = 0.60;
				coords.a22[3][1] = 0.80;

				coords.a23[0][0] = 0.60;
				coords.a23[0][1] = 0.80;
				coords.a23[1][0] = 0.60;
				coords.a23[1][1] = 1.00;
				coords.a23[2][0] = 0.80;
				coords.a23[2][1] = 1.00;
				coords.a23[3][0] = 0.80;
				coords.a23[3][1] = 0.80;

				coords.a24[0][0] = 0.80;
				coords.a24[0][1] = 0.80;
				coords.a24[1][0] = 0.80;
				coords.a24[1][1] = 1.00;
				coords.a24[2][0] = 1.00;
				coords.a24[2][1] = 1.00;
				coords.a24[3][0] = 1.00;
				coords.a24[3][1] = 0.80;

				//Standard font quad, CCW:CAB-BDC
				float iHalf_W = (Core::gameVars->font.vSize[0]/2);
				float iHalf_H = (Core::gameVars->font.vSize[1]/2);
				Data3f vVerts[] = { {-iHalf_W, -iHalf_H, 0},
									  { iHalf_W,  iHalf_H, 0},
									  {-iHalf_W,  iHalf_H, 0},
									  {-iHalf_W, -iHalf_H, 0},
									  { iHalf_W, -iHalf_H, 0},
									  { iHalf_W,  iHalf_H, 0 }};

				for (int i=0; i<25; i++) {
			//		Core::gameVars->display.system.vao[i]=1000+i;
					switch(i) {
						case 0:  pArray=coords.a00;  break;
						case 1:  pArray=coords.a01;  break;
						case 2:  pArray=coords.a02;  break;
						case 3:  pArray=coords.a03;  break;
						case 4:  pArray=coords.a04;  break;

						case 5:  pArray=coords.a05;  break;
						case 6:  pArray=coords.a06;  break;
						case 7:  pArray=coords.a07;  break;
						case 8:  pArray=coords.a08;  break;
						case 9:  pArray=coords.a09;  break;

						case 10: pArray=coords.a10;  break;
						case 11: pArray=coords.a11;  break;
						case 12: pArray=coords.a12;  break;
						case 13: pArray=coords.a13;  break;
						case 14: pArray=coords.a14;  break;

						case 15: pArray=coords.a15;  break;
						case 16: pArray=coords.a16;  break;
						case 17: pArray=coords.a17;  break;
						case 18: pArray=coords.a18;  break;
						case 19: pArray=coords.a19;  break;

						case 20: pArray=coords.a20;  break;
						case 21: pArray=coords.a21;  break;
						case 22: pArray=coords.a22;  break;
						case 23: pArray=coords.a23;  break;
						case 24: pArray=coords.a24;  break;
					}

					Data2f vTexture[11];
					vTexture[0][0] = pArray[1][0];
					vTexture[0][1] = pArray[1][1];

					vTexture[1][0] = pArray[3][0];
					vTexture[1][1] = pArray[3][1];

					vTexture[2][0] = pArray[0][0];
					vTexture[2][1] = pArray[0][1];

					vTexture[3][0] = pArray[1][0];
					vTexture[3][1] = pArray[1][1];

					vTexture[4][0] = pArray[2][0];
					vTexture[4][1] = pArray[2][1];

					vTexture[5][0] = pArray[3][0];
					vTexture[5][1] = pArray[3][1];

					vao[i].Begin(GL_TRIANGLES, 6, 6, 1);
					vao[i].CopyData(GLA_VERTEX, vVerts);
					vao[i].CopyData(GLA_TEXTURE, vTexture, 0);
					vao[i].End();
				}
				std::cout << "Done" << std::endl;
				return true;
			}
			catch (...) {
				std::cout << "Failed" << std::endl;
				return false;
			}
		}

		void _WinSys::start(int x, int y, short int iBorder, Core::_Colors::_ACTIVE_COLOR eColor) {
			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			matrix->SetProjection(matrix->MM_ORTHO);
			shader->use(GLS_FONT);

			glDisable(GL_DEPTH_TEST);
			matrix->Push();
			matrix->Translate( (Core::gameVars->font.vSize[0]*x)+Core::gameVars->font.screenCoords[0], (-Core::gameVars->font.vSize[1]*y)+Core::gameVars->font.screenCoords[1], 0.0 );

			// TODO: [WinSys] Fix border draw mode
//			if(iBorder==DRAWMODE.BORDER_ONLY) {
//				texture.Set("menu_border.png");
//			}
//			else if(iBorder==DRAWMODE.SELECTION) {
//				texture.Set("menu_select.png");
//			}
//			else {
				texture.Set("menu.png");
//			}
			colors.SetActive(eColor);
		}

		void _WinSys::update() {
			matrix->SetTransform();
			//Core::shader->getUniform(GLS_SHADED_TEX, Core::gameVars->player.active->transform.pos, Core::gameVars->font.vColor);
			shader->getUniform(GLS_FONT);
		}

		//MEMORYLEAK
		void _WinSys::stop() {
			matrix->Pop();
			matrix->SetProjection(matrix->MM_PERSPECTIVE);
			glEnable(GL_DEPTH_TEST);
		}

		void _WinSys::drawSingle(int x, int y, int w, int h, int index, Color fontColor, short int iBorder=DRAWMODE.NORMAL) {
			colors.PushFront(fontColor);
			drawSingle(x, y, w, h, index, iBorder);
			colors.PopFront();
		}

		void _WinSys::drawSingle(int x, int y, int w, int h, int index, short int iBorder=DRAWMODE.NORMAL) {
			start(x, y, iBorder);
			for (int iH=1; iH<=h; iH++) {
				for (int iW=1; iW<=w; iW++) {
					update();
					vao[index].Draw();
					matrix->Translate( Core::gameVars->font.vSize[0], 0.0, 0.0 );
				}
				stop();
				start(x, y+iH, iBorder);
			}
			stop();
		}

		//uint _WinSys::draw(int x, int y, int w, int h, bool textOffset, Vector4f backColor) {
		//	return draw(x, y, w, h, false, textOffset, backColor, Core::gameVars->font.color.white);
		//}

		void _WinSys::draw(	int x,
							int y,
							int w,
							int h,
							bool textOffset,
							Color backColor=Color{1.0, 1.0, 1.0, 1.0},
							short int iBorder=DRAWMODE.NORMAL) {
			//for (int i=0;i<4;i++) tempColor[i]=Core::gameVars->font.vColor[i];

			// TODO: [WinSys] Implement Back Color
			cBackColor[0] = backColor[0];
			cBackColor[1] = backColor[1];
			cBackColor[2] = backColor[2];
			cBackColor[3] = backColor[3];

			start(x, y, iBorder);
			for (int iH=1; iH<=h; iH++) {
				for (int iW=1; iW<=w; iW++) {
					if (iW==1 && iH==1) index=0;
					else if (iW==w && iH==1) index=1;
					else if (iW==1 && iH==h) index=5;
					else if (iW==w && iH==h) index=6;
					else if (iW==1 && iH<h && iH>1) index=15;
					else if (iW==w && iH<h && iH>1) index=16;
					else if (iH==1 && iW<w && iW>1) index=3;
					else if (iH==h && iW<w && iW>1) index=8;
					else index=24;

					update();
					vao[index].Draw();
					matrix->Translate( Core::gameVars->font.vSize[0], 0.0, 0.0 );
				}
				stop();

				// TODO: [WinSys] Implement Back Color
				start(x, y+iH, iBorder);
			}
			stop();
		}

		/*
		void _WinSys::draw(	int x,
							int y,
							int w,
							int h,
							bool bHighlight,
							bool textOffset,
							Vector4f backColor=Vector4f{1.0, 1.0, 1.0, 1.0},
							Vector4f backHColor=Vector4f{1.0, 1.0, 1.0, 1.0}) {
			// backColor = Window color
			// frontColor = Text color
			// backHColor = Window mouseover color
			// frontHColor = Text mouseover color
			for (int i=0;i<4;i++) tempColor[i]=Core::gameVars->font.vColor[i];
			//uint checkClick;
			bool bHL = false;

			cBackColor[0] = backColor[0];
			cBackColor[1] = backColor[1];
			cBackColor[2] = backColor[2];
			cBackColor[3] = backColor[3];

			if (bHighlight) {
				if (textOffset) {
					if (checkOver(x*Core::gameVars->font.vSize[0]+Core::gameVars->font.vHalfSize[0],y*Core::gameVars->font.vSize[1]+Core::gameVars->font.vHalfSize[1], (w-1)*Core::gameVars->font.vSize[0],(h-1)*Core::gameVars->font.vSize[1])) {
						cBackColor[0] = backHColor[0];
						cBackColor[1] = backHColor[1];
						cBackColor[2] = backHColor[2];
						cBackColor[3] = backHColor[3];
					}
				}
				else {
					if (checkOver(x,y,w,h)) {
						cBackColor[0] = backHColor[0];
						cBackColor[1] = backHColor[1];
						cBackColor[2] = backHColor[2];
						cBackColor[3] = backHColor[3];
					}
				}
			}

			start(x, y, cBackColor);
			//start(x, y, fontColor);
			for (int iH=1; iH<=h; iH++) {
				for (int iW=1; iW<=w; iW++) {
					if (iW==1 && iH==1) index=0;
					else if (iW==w && iH==1) index=1;
					else if (iW==1 && iH==h) index=5;
					else if (iW==w && iH==h) index=6;
					else if (iW==1 && iH<h && iH>1) index=15;
					else if (iW==w && iH<h && iH>1) index=16;
					else if (iH==1 && iW<w && iW>1) index=3;
					else if (iH==h && iW<w && iW>1) index=8;
					else index=24;

					update();
					vao[index].Draw();
					matrix->Translate( Core::gameVars->font.vSize[0], 0.0, 0.0 );
				}
				stop();
				start(x, y+iH, cBackColor);
			}
			stop();

			//if (textOffset) checkClick=checkInput(x*Core::gameVars->font.vSize[0]+Core::gameVars->font.vHalfSize[0], y*Core::gameVars->font.vSize[1]+Core::gameVars->font.vHalfSize[1], (w-1)*Core::gameVars->font.vSize[0],(h-1)*Core::gameVars->font.vSize[1]);
			//else checkClick=checkInput(x, y, w, h);

			//return checkClick;
		}
		*/
		/*
		uint _WinSys::draw(	int x,
							int y,
							int w,
							int h,
							std::string sText,
							bool bHighlight,
							bool textOffset,
							Vector4f backColor,
							Vector4f frontColor,
							Vector4f backHColor,
							Vector4f frontHColor) {

			// backColor = Window color
			// frontColor = Text color
			// backHColor = Window mouseover color
			// frontHColor = Text mouseover color
			for (int i=0;i<4;i++) tempColor[i]=Core::gameVars->font.vColor[i];

			/*
			 * Convert pixel size into a scale size, we may
			 *  lose some precision here but it shouldn't
			 *  be a big deal for icons.
			 */
			//w=w/64;
			//h=h/64;

			/*
			 * If highlighting is enabled
			 * Then check if mouse is hovering over icon:
			 *    - When textOffset mode is enabled
			 *    - When textOffset mode is disabled
			 *//*
			uint checkClick;
			bool bHL = false;

			if (bHighlight) {
				if (textOffset) {
					if (checkOver(x*Core::gameVars->font.vSize[0]+Core::gameVars->font.vHalfSize[0],y*Core::gameVars->font.vSize[1]+Core::gameVars->font.vHalfSize[1], (w-1)*Core::gameVars->font.vSize[0],(h-1)*Core::gameVars->font.vSize[1])) bHL = true;
				}
				else {
					if (checkOver(x,y,w,h)) bHL = true;
				}

				if(bHL) {
					cBackColor[0] = backHColor[0];
					cBackColor[1] = backHColor[1];
					cBackColor[2] = backHColor[2];
					cBackColor[3] = backHColor[3];

					cFrontColor[0] = frontHColor[0];
					cFrontColor[1] = frontHColor[1];
					cFrontColor[2] = frontHColor[2];
					cFrontColor[3] = frontHColor[3];
				}
			}
			else {
				cBackColor[0] = backColor[0];
				cBackColor[1] = backColor[1];
				cBackColor[2] = backColor[2];
				cBackColor[3] = backColor[3];

				cFrontColor[0] = frontColor[0];
				cFrontColor[1] = frontColor[1];
				cFrontColor[2] = frontColor[2];
				cFrontColor[3] = frontColor[3];
			}

			start(x, y, cBackColor);
			//start(x, y, fontColor);
			for (int iH=1; iH<=h; iH++) {
				for (int iW=1; iW<=w; iW++) {
					if (iW==1 && iH==1) index=0;
					else if (iW==w && iH==1) index=1;
					else if (iW==1 && iH==h) index=5;
					else if (iW==w && iH==h) index=6;
					else if (iW==1 && iH<h && iH>1) index=15;
					else if (iW==w && iH<h && iH>1) index=16;
					else if (iH==1 && iW<w && iW>1) index=3;
					else if (iH==h && iW<w && iW>1) index=8;
					else index=24;

					update();
					vao[index].Draw();
					matrix->Translate( Core::gameVars->font.vSize[0], 0.0, 0.0 );
				}
				stop();
				start(x, y+iH, cBackColor);
			}
			stop();

			//gameSys.textSys.draw(x,	y, sText, cFrontColor);

			if (textOffset) checkClick=checkInput(x*Core::gameVars->font.vSize[0]+Core::gameVars->font.vHalfSize[0], y*Core::gameVars->font.vSize[1]+Core::gameVars->font.vHalfSize[1], (w-1)*Core::gameVars->font.vSize[0],(h-1)*Core::gameVars->font.vSize[1]);
			else checkClick=checkInput(x, y, w, h);

			return checkClick;
		}
		*/

		void _WinSys::drawT(int x, int y, int w, Color fontColor, short int iBorder=DRAWMODE.NORMAL) {
			colors.PushFront(fontColor);
			drawT(x, y, w, iBorder);
			colors.PopFront();
		}

		void _WinSys::drawT(int x, int y, int w, short int iBorder=DRAWMODE.NORMAL) {
			start(x, y, iBorder);
			for (int iW=1; iW<=w; iW++) {
				if (iW==1) index=0;
				else if (iW==w) index=1;
				else index=3;

				update();
				vao[index].Draw();
				matrix->Translate( Core::gameVars->font.vSize[0], 0.0, 0.0 );
			}
			stop();
		}

		void _WinSys::drawB(int x, int y, int w, Color fontColor, short int iBorder=DRAWMODE.NORMAL) {
			colors.PushFront(fontColor);
			drawB(x, y, w, iBorder);
			colors.PopFront();
		}

		void _WinSys::drawB(int x, int y, int w, short int iBorder=DRAWMODE.NORMAL) {
			start(x, y, iBorder);
			for (int iW=1; iW<=w; iW++) {
				if (iW==1) index=5;
				else if (iW==w) index=6;
				else index=8;

				update();
				vao[index].Draw();
				matrix->Translate( Core::gameVars->font.vSize[0], 0.0, 0.0 );
			}
			stop();
		}

		void _WinSys::drawL(int x, int y, int h, Color fontColor, short int iBorder=DRAWMODE.NORMAL) {
			colors.PushFront(fontColor);
			drawL(x, y, h, iBorder);
			colors.PopFront();
		}

		void _WinSys::drawL(int x, int y, int h, short int iBorder=DRAWMODE.NORMAL) {
			start(x, y, iBorder);
			for (int iH=1; iH<=h; iH++) {
				if (iH==1) index=4;
				else if (iH==h) index=14;
				else index=9;

				update();
				vao[index].Draw();
				matrix->Translate( 0.0, -Core::gameVars->font.vSize[1], 0.0 );
			}
			stop();
		}

		void _WinSys::drawR(int x, int y, int h, Color fontColor, short int iBorder=DRAWMODE.NORMAL) {
			colors.PushFront(fontColor);
			drawR(x, y, h, iBorder);
			colors.PopFront();
		}

		void _WinSys::drawR(int x, int y, int h, short int iBorder=DRAWMODE.NORMAL) {
			start(x, y, iBorder);
			for (int iH=1; iH<=h; iH++) {
				if (iH==1) index=4;
				else if (iH==h) index=14;
				else index=9;

				update();
				vao[index].Draw();
				matrix->Translate( 0.0, -Core::gameVars->font.vSize[1], 0.0 );
			}
			stop();
		}

		void _WinSys::drawTBorder(int x, int y, int w, Color fontColor, short int iBorder=DRAWMODE.NORMAL) {
			colors.PushFront(fontColor);
			drawTBorder(x, y, w, iBorder);
			colors.PopFront();
		}

		void _WinSys::drawTBorder(int x, int y, int w, short int iBorder=DRAWMODE.NORMAL) {
			start(x, y, iBorder);
			for (int iW=1; iW<=w; iW++) {
				index=3;

				update();
				vao[index].Draw();
				matrix->Translate( Core::gameVars->font.vSize[0], 0.0, 0.0 );
			}
			stop();
		}

		void _WinSys::drawiBorder(int x, int y, int w, Color fontColor, short int iBorder=DRAWMODE.NORMAL) {
			colors.PushFront(fontColor);
			drawiBorder(x, y, w, iBorder);
			colors.PopFront();
		}

		void _WinSys::drawiBorder(int x, int y, int w, short int iBorder=DRAWMODE.NORMAL) {
			start(x, y, iBorder);
			for (int iW=1; iW<=w; iW++) {
				index=8;

				update();
				vao[index].Draw();
				matrix->Translate( Core::gameVars->font.vSize[0], 0.0, 0.0 );
			}
			stop();
		}

		void _WinSys::drawLBorder(int x, int y, int h, Color fontColor, short int iBorder=DRAWMODE.NORMAL) {
			colors.PushFront(fontColor);
			drawLBorder(x, y, h, iBorder);
			colors.PopFront();
		}

		void _WinSys::drawLBorder(int x, int y, int h, short int iBorder=DRAWMODE.NORMAL) {
			start(x, y, iBorder);
			for (int iH=1; iH<=h; iH++) {
				index=15;

				update();
				vao[index].Draw();
				matrix->Translate( 0.0, -Core::gameVars->font.vSize[1], 0.0 );
			}
			stop();
		}

		void _WinSys::drawRBorder(int x, int y, int h, Color fontColor, short int iBorder=DRAWMODE.NORMAL) {
			colors.PushFront(fontColor);
			drawRBorder(x, y, h, iBorder);
			colors.PopFront();
		}

		void _WinSys::drawRBorder(int x, int y, int h, short int iBorder=DRAWMODE.NORMAL) {
			start(x, y, iBorder);
			for (int iH=1; iH<=h; iH++) {
				index=16;

				update();
				vao[index].Draw();
				matrix->Translate( 0.0, -Core::gameVars->font.vSize[1], 0.0 );
			}
			stop();
		}

		void _WinSys::drawHSpace(int x, int y, int w, Color fontColor, short int iBorder=DRAWMODE.NORMAL) {
			colors.PushFront(fontColor);
			drawHSpace(x, y, w, iBorder);
			colors.PopFront();
		}

		void _WinSys::drawHSpace(int x, int y, int w, short int iBorder=DRAWMODE.NORMAL) {
			start(x, y, iBorder);
			for (int iW=1; iW<=w; iW++) {
				if (iW==1) index=15;
				else if (iW==w) index=16;
				else index=24;

				update();
				vao[index].Draw();
				matrix->Translate( Core::gameVars->font.vSize[0], 0.0, 0.0 );
			}
			stop();
		}

		void _WinSys::drawVSpace(int x, int y, int h, Color fontColor, short int iBorder=DRAWMODE.NORMAL) {
			colors.PushFront(fontColor);
			drawVSpace(x, y, h, iBorder);
			colors.PopFront();
		}

		void _WinSys::drawVSpace(int x, int y, int h, short int iBorder=DRAWMODE.NORMAL) {
			start(x, y, iBorder);
			for (int iH=1; iH<=h; iH++) {
				if (iH==1) index=3;
				else if (iH==h) index=8;
				else index=24;

				update();
				vao[index].Draw();
				matrix->Translate( 0.0, -Core::gameVars->font.vSize[1], 0.0 );
			}
			stop();
		}

		void _WinSys::drawHLine(int x, int y, int w, Color fontColor, short int iBorder=DRAWMODE.NORMAL) {
			colors.PushFront(fontColor);
			drawHLine(x, y, w, iBorder);
			colors.PopFront();
		}

		void _WinSys::drawHLine(int x, int y, int w, short int iBorder=DRAWMODE.NORMAL) {
			start(x, y, iBorder);
			for (int iW=1; iW<=w; iW++) {
				index=21;

				update();
				vao[index].Draw();
				matrix->Translate( Core::gameVars->font.vSize[0], 0.0, 0.0 );
			}
			stop();
		}

		void _WinSys::drawVLine(int x, int y, int h, Color fontColor, short int iBorder=DRAWMODE.NORMAL) {
			colors.PushFront(fontColor);
			drawVLine(x, y, h, iBorder);
			colors.PopFront();
		}

		void _WinSys::drawVLine(int x, int y, int h, short int iBorder=DRAWMODE.NORMAL) {
			start(x, y, iBorder);
			for (int iH=1; iH<=h; iH++) {
				index=9;

				update();
				vao[index].Draw();
				matrix->Translate( 0.0, -Core::gameVars->font.vSize[1], 0.0 );
			}
			stop();
		}

		void _WinSys::drawHDiv(int x, int y, int w, Color fontColor, short int iBorder=DRAWMODE.NORMAL) {
			colors.PushFront(fontColor);
			drawHDiv(x, y, w, iBorder);
			colors.PopFront();
		}

		void _WinSys::drawHDiv(int x, int y, int w, short int iBorder=DRAWMODE.NORMAL) {
			start(x, y, iBorder);

			update();
			vao[10].Draw();
			matrix->Translate( Core::gameVars->font.vSize[0], 0.0, 0.0 );

			for (int iW=2; iW<w; iW++) {
				index=21;

				update();
				vao[index].Draw();
				matrix->Translate( Core::gameVars->font.vSize[0], 0.0, 0.0 );
			}

			update();
			vao[11].Draw();
			matrix->Translate( Core::gameVars->font.vSize[0], 0.0, 0.0 );

			stop();
		}

		void _WinSys::drawVDiv(int x, int y, int h, Color fontColor, short int iBorder=DRAWMODE.NORMAL) {
			colors.PushFront(fontColor);
			drawVDiv(x, y, h, iBorder);
			colors.PopFront();
		}

		void _WinSys::drawVDiv(int x, int y, int h, short int iBorder=DRAWMODE.NORMAL) {
			start(x, y, iBorder);

			update();
			vao[2].Draw();
			matrix->Translate( 0.0, -Core::gameVars->font.vSize[1], 0.0 );

			for (int iH=2; iH<h; iH++) {
				index=9;

				update();
				vao[index].Draw();
				matrix->Translate( 0.0, -Core::gameVars->font.vSize[1], 0.0 );
			}

			update();
			vao[7].Draw();
			matrix->Translate( 0.0, -Core::gameVars->font.vSize[1], 0.0 );

			stop();
		}

		/*
		uint _WinSys::checkInput(int x, int y, float w, float h) {
			if (Core::gameVars->controls.mouse.button.pressed[0]) {
				Vector2f vMouse = { float(Core::gameVars->controls.mouse.x), float(Core::gameVars->controls.mouse.y) };
				Vector2f vP1    = { (float)x, (float)y };
				Vector2f vP2    = { (float)x+w, (float)y+h };

				if (PointQuad2d(vMouse, vP1, vP2)) {
					if (Core::gameVars->timer.frameRate.get_ticks()>(fMouseDelay+fMouseDelayConst)) {
						fMouseDelay = Core::gameVars->timer.frameRate.get_ticks();
						return MOUSE_LEFT;
					}
				}
			}
			return MOUSE_NONE;
		}

		uint _WinSys::checkOver(int x, int y, float w, float h) {
			Vector2f vMouse = { float(Core::gameVars->controls.mouse.x), float(Core::gameVars->controls.mouse.y) };
			Vector2f vP1    = { (float)x, (float)y };
			Vector2f vP2    = { (float)x+w, (float)y+h };

			if (PointQuad2d(vMouse, vP1, vP2)) return MOUSE_HOVER;
			else return MOUSE_NONE;
		}
		 */
	}
}
#endif /* _WinSys_H_ */
