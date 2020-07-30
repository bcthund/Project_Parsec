/*
 * _TextSys.h
 *
 *  Created on: Sep 18, 2010
 *      Author: bcthund
 */

#ifndef _TextSys_H_
#define _TextSys_H_

#include <iostream>
#include <iomanip>
#include <sstream>

#include "../core/matrix.h"
#include "../core/shader.h"
#include "../core/core_functions.h"
#include "../core/Colors.h"
#include "../gamesys/GUI/GUI_Constraint.h"

// FIXME: Variables appear to be drawn wrong, harder to read than normal text

namespace Core {
//	namespace GameSys {
		class _TextSys {
			private:
			static const int CHARS = 256;
			static const int SPACECHAR = 94;

			Timer cursorBlink;
			bool bBlinkState;

			Map_si	mapChar;
//			Matrix_System * matrix;
//			Shader_System * shader;
//			GLfloat (*pArray)[2];
			Vector24f pArray;
			Texture texture;
			VAO vao[CHARS];
//			Vector4f tempColor;
			uint uiNumTextures,
				 uiRecordSize;
			std::string sFilename,
						sDir,
						sTexDir;
			Vector24f setTexCoords(int n);
			void start(int x, int y, int fontNum, Core::_Colors::_ACTIVE_COLOR eColor/*=Core::_Colors::COLOR_FRONT*/);
			void update();
			void stop();

//			void drawTimer(std::string buffer);
//			void drawTimer(int l);
			void drawText(std::string buffer);
//			void drawVariable(float *fPtr, bool drawDec);
//			void drawVariable(int *iPtr);
//			void drawVariable(uint *uiPtr);
//			void drawVariable(bool *bPtr);

			public:
			_TextSys(/*Matrix_System &m, Shader_System &s*/);

			int getIndex(char myChar);
			int getIndex(std::string sChar);
			bool load();
			bool init();
//			void timer(int x, int y, Map_si m, std::string name, int z);

//			void draw(int x, int y, std::string buffer);
//			void draw(int x, int y, std::string buffer, Vector4f fontColor);

			// FIXME: Remove drawing methods NOT using constraints
			void draw(float x, float y, std::string buffer, GUI::iConstrain anchor=Core::GUI::CONSTRAIN_CENTER, GUI::iConstrain origin=GUI::CONSTRAIN_TOP|GUI::CONSTRAIN_LEFT);
			void draw(GUI::Props *con, std::string buffer);
			void draw(GUI::Props *con, std::string buffer, GUI::iConstrain anchor);
//			void draw(GUI::Props c, std::string buffer, GUI::iAnchor anchor);
//			void draw(Vector2f pos, std::string buffer, GUI::iAnchor anchor=Core::GUI::ANCHOR_CENTER, GUI::iOrigin origin=GUI::ORIGIN_TOP|GUI::ORIGIN_LEFT);
			void draw2(float x, float y, std::string buffer, GUI::iConstrain anchor=Core::GUI::CONSTRAIN_CENTER, GUI::iConstrain origin=GUI::CONSTRAIN_TOP|GUI::CONSTRAIN_LEFT);

			void drawMulti(GUI::Props_Text *con, GUI::iConstrain anchor=Core::GUI::CONSTRAIN_LEFT);
//			void drawMulti(GUI::Props_Text *con, std::string buffer, GUI::iConstrain anchor=Core::GUI::CONSTRAIN_LEFT);

//
//			void drawTextSpecial(std::string sChar);
//			void drawSpecial(int x, int y, std::string sChar);
//			void drawSpecial(int x, int y, std::string sChar, Vector4f fontColor);
//
//			//Draw Auto Variables

			template<typename T>
			void drawVar(GUI::Props c, std::string buffer, T t, int precision, GUI::iConstrain anchor);
			template<typename T>
			void drawVar(int x, int y, std::string buffer, T t, int precision, GUI::iConstrain anchor=Core::GUI::CONSTRAIN_CENTER, GUI::iConstrain origin=GUI::CONSTRAIN_TOP|GUI::CONSTRAIN_LEFT);
			template<typename T>
			void drawVar2(int x, int y, std::string buffer, T t, int precision, GUI::iConstrain anchor=Core::GUI::CONSTRAIN_CENTER, GUI::iConstrain origin=GUI::CONSTRAIN_TOP|GUI::CONSTRAIN_LEFT);

//			void draw(int x, int y, int z, std::string buffer, float *fPtr, bool drawDec);
//			void draw(int x, int y, int z, std::string buffer, float *fPtr, Vector4f fontColor, bool drawDec);
//			void draw(int x, int y, float *fPtr, bool drawDec);
//			void draw(int x, int y, float *fPtr, Vector4f fontColor, bool drawDec);
//
//			void draw(int x, int y, int z, std::string buffer, int   *iPtr);
//			void draw(int x, int y, int z, std::string buffer, int   *iPtr, Vector4f fontColor);
//			void draw(int x, int y, int   *iPtr);
//			void draw(int x, int y, int   *iPtr, Vector4f fontColor);
//			void draw(int x, int y, uint  *uiPtr, Vector4f fontColor);
//			void draw(int x, int y, uint  *uiPtr);
//
//			void draw(int x, int y, int z, std::string buffer, bool  *bPtr);
//			void draw(int x, int y, int z, std::string buffer, bool  *bPtr, Vector4f fontColor);
//			void draw(int x, int y, bool  *bPtr);
//			void draw(int x, int y, bool  *bPtr, Vector4f fontColor);
//
//			void draw(int x, int y, int z, std::string buffer, std::string sPtr);
		};

		_TextSys::_TextSys(/*Matrix_System &m, Shader_System &s*/) {
			uiNumTextures	= 10;
			uiRecordSize	= 32;
			sFilename		= "font.bin";
			sDir			= "./system/";
			sTexDir			= "./texture/system/";

			cursorBlink.start();
			bBlinkState = false;
		}

		/** ******************************************************************************************************************************
		 *
		 * @return
		 * ****************************************************************************************************************************** */
		bool _TextSys::load() {
			try {
				std::string theImage;
				Core::MemBlock memBlock;

				//            .................................................................Done
				std::cout << "Load TextSys.....................................................";
				//if (Core::gameVars->debug.load) cout << endl;
				texture.Begin(uiNumTextures);

				readFile((sDir+sFilename).c_str(), memBlock);

				for (uint d=0; d<memBlock.size; d+=uiRecordSize) {
					int theId = 0;
					for (int i=0; i<4; i++) theId+=(unsigned char)memBlock.buffer[i+d];

					theImage = "";
					for (int i=4; i<32; i++) {
						if (memBlock.buffer[i+d]!=0) theImage+=(unsigned char)memBlock.buffer[i+d];
						else break;
					}

					texture.Load(sTexDir, theImage, theId, false, GL_LINEAR_MIPMAP_LINEAR, GL_CLAMP_TO_EDGE);		// This filtering works best, especially for odd font sizes
				}
				//if (Core::gameVars->debug.load) cout << "..";
				std::cout << "Done" << std::endl;
				return true;
			}
			catch(...) {
				std::cout << "Failed" << std::endl;
				return false;
			}
		}

		/** ******************************************************************************************************************************
		 *
		 * @param n
		 * @return
		 * ****************************************************************************************************************************** */
		Vector24f _TextSys::setTexCoords(int n) {
			Vector24f vChar;
//			GLfloat vChar[4][2];
			int ny = n/16;
			int nx = n-(16*ny);
			vChar[0][0] = 0.0625*nx;
			vChar[0][1] = 0.0625*ny;
			vChar[1][0] = 0.0625*nx;
			vChar[1][1] = 0.0625*(ny+1);
			vChar[2][0] = 0.0625*(nx+1);
			vChar[2][1] = 0.0625*(ny+1);
			vChar[3][0] = 0.0625*(nx+1);
			vChar[3][1] = 0.0625*ny;
			return vChar;
		}

		/** ******************************************************************************************************************************
		 *
		 * @return
		 * ****************************************************************************************************************************** */
		bool _TextSys::init() {
			try {
				//            .................................................................Done
				std::cout << "Init TextSys.....................................................";
				// Temporary texture coords
				struct _Font {
				Vector24f	a,  A,
							b,  B,
							c,  C,
							d,  D,
							e,  E,
							f,  F,
							g,  G,
							h,  H,
							i,  I,
							j,  J,
							k,  K,
							l,  L,
							m,  M,
							n,  N,
							o,  O,
							p,  P,
							q,  Q,
							r,  R,
							s,  S,
							t,  T,
							u,  U,
							v,  V,
							w,  W,
							x,  X,
							y,  Y,
							z,  Z,
							num0,  num5,
							num1,  num6,
							num2,  num7,
							num3,  num8,
							num4,  num9,
							SPACE, LESS,
							EXCLAIM, EQUALS,
							QUOTE, GREATER,
							COLON, SEMICOLON,
							AT,  QUESTION,
							NULLCHAR, PIPE,
							LBRACE, RBRACE,
							TILDE, BACKSLASH,
							LBRACKET, RBRACKET,
							CARET, UNDERSCORE,
							QUOTEDBL, BACKQUOTE,
							HASH,  DOLLAR,
							PERCENT, AMPERSAND,
							LPAREN, RPAREN,
							ASTERISK, PLUS,
							COMMA, MINUS,
							PERIOD, SLASH,
							PLUSMINUS,

							X00, X01, X02, X03, X04, X05, X06, X07,
							X08, X09, X0A, X0B, X0C, X0D, X0E, X0F,

							X10, X11, X12, X13, X14, X15, X16, X17,
							X18, X19, X1A, X1B, X1C, X1D, X1E, X1F,

							X7F,

							X80, X81, X82, X83, X84, X85, X86, X87,
							X88, X89, X8A, X8B, X8C, X8D, X8E, X8F,

							X90, X91, X92, X93, X94, X95, X96, X97,
							X98, X99, X9A, X9B, X9C, X9D, X9E, X9F,

							XA0, XA1, XA2, XA3, XA4, XA5, XA6, XA7,
							XA8, XA9, XAA, XAB, XAC, XAD, XAE, XAF,

							XB0, XB1, XB2, XB3, XB4, XB5, XB6, XB7,
							XB8, XB9, XBA, XBB, XBC, XBD, XBE, XBF,

							XC0, XC1, XC2, XC3, XC4, XC5, XC6, XC7,
							XC8, XC9, XCA, XCB, XCC, XCD, XCE, XCF,

							XD0, XD1, XD2, XD3, XD4, XD5, XD6, XD7,
							XD8, XD9, XDA, XDB, XDC, XDD, XDE, XDF,

							XE0, XE1, XE2, XE3, XE4, XE5, XE6, XE7,
							XE8, XE9, XEA, XEB, XEC, XED, XEE, XEF,

							XF0, XF1, XF2, XF3, XF4, XF5, XF6, XF7,
							XF8, XF9, XFA, XFB, XFC, XFD, XFE, XFF;
			} font;


			// FIXME: Copying to font.<charname> then copying to pArray, then creating VAO from that is more complex than need be. Streamline.


				// Top-Left
				// Bottom-Left
				// Top-Right
				// Bottom-Right
				int n = 32;				// 32
				int ny = n/16;			// 2
				int nx = n-(16*ny);		// 0
//				font.PLUSMINUS[0][0] = 0.0000;
//				font.PLUSMINUS[0][1] = 0.1250;
//
//				font.PLUSMINUS[1][0] = 0.0000;
//				font.PLUSMINUS[1][1] = 0.1875;
//
//				font.PLUSMINUS[2][0] = 0.0625;
//				font.PLUSMINUS[2][1] = 0.1875;
//
//				font.PLUSMINUS[3][0] = 0.0625;
//				font.PLUSMINUS[3][1] = 0.1250;

				font.PLUSMINUS[0][0] = 0.0625*nx;			// 0.0000
				font.PLUSMINUS[0][1] = 0.0625*ny;			// 0.1250

				font.PLUSMINUS[1][0] = 0.0625*nx;			// 0.0000
				font.PLUSMINUS[1][1] = 0.0625*(ny+1);		// 0.1875

				font.PLUSMINUS[2][0] = 0.0625*(nx+1);		// 0.0625
				font.PLUSMINUS[2][1] = 0.0625*(ny+1);		// 0.1875

				font.PLUSMINUS[3][0] = 0.0625*(nx+1);		// 0.0625
				font.PLUSMINUS[3][1] = 0.0625*ny;			// 0.1250

				font.X00 = setTexCoords(0x00);
				font.X01 = setTexCoords(0x01);
				font.X02 = setTexCoords(0x02);
				font.X03 = setTexCoords(0x03);
				font.X04 = setTexCoords(0x04);
				font.X05 = setTexCoords(0x05);
				font.X06 = setTexCoords(0x06);
				font.X07 = setTexCoords(0x07);
				font.X08 = setTexCoords(0x08);
				font.X09 = setTexCoords(0x09);
				font.X0A = setTexCoords(0x0A);
				font.X0B = setTexCoords(0x0B);
				font.X0C = setTexCoords(0x0C);
				font.X0D = setTexCoords(0x0D);
				font.X0E = setTexCoords(0x0E);
				font.X0F = setTexCoords(0x0F);

				font.X10 = setTexCoords(0x10);
				font.X11 = setTexCoords(0x11);
				font.X12 = setTexCoords(0x12);
				font.X13 = setTexCoords(0x13);
				font.X14 = setTexCoords(0x14);
				font.X15 = setTexCoords(0x15);
				font.X16 = setTexCoords(0x16);
				font.X17 = setTexCoords(0x17);
				font.X18 = setTexCoords(0x18);
				font.X19 = setTexCoords(0x19);
				font.X1A = setTexCoords(0x1A);
				font.X1B = setTexCoords(0x1B);
				font.X1C = setTexCoords(0x1C);
				font.X1D = setTexCoords(0x1D);
				font.X1E = setTexCoords(0x1E);
				font.X1F = setTexCoords(0x1F);

				font.X80 = setTexCoords(0x80);
				font.X81 = setTexCoords(0x81);
				font.X82 = setTexCoords(0x82);
				font.X83 = setTexCoords(0x83);
				font.X84 = setTexCoords(0x84);
				font.X85 = setTexCoords(0x85);
				font.X86 = setTexCoords(0x86);
				font.X87 = setTexCoords(0x87);
				font.X88 = setTexCoords(0x88);
				font.X89 = setTexCoords(0x89);
				font.X8A = setTexCoords(0x8A);
				font.X8B = setTexCoords(0x8B);
				font.X8C = setTexCoords(0x8C);
				font.X8D = setTexCoords(0x8D);
				font.X8E = setTexCoords(0x8E);
				font.X8F = setTexCoords(0x8F);

				font.X90 = setTexCoords(0x90);
				font.X91 = setTexCoords(0x91);
				font.X92 = setTexCoords(0x92);
				font.X93 = setTexCoords(0x93);
				font.X94 = setTexCoords(0x94);
				font.X95 = setTexCoords(0x95);
				font.X96 = setTexCoords(0x96);
				font.X97 = setTexCoords(0x97);
				font.X98 = setTexCoords(0x98);
				font.X99 = setTexCoords(0x99);
				font.X9A = setTexCoords(0x9A);
				font.X9B = setTexCoords(0x9B);
				font.X9C = setTexCoords(0x9C);
				font.X9D = setTexCoords(0x9D);
				font.X9E = setTexCoords(0x9E);
				font.X9F = setTexCoords(0x9F);

				font.XA0 = setTexCoords(0xA0);
				font.XA1 = setTexCoords(0xA1);
				font.XA2 = setTexCoords(0xA2);
				font.XA3 = setTexCoords(0xA3);
				font.XA4 = setTexCoords(0xA4);
				font.XA5 = setTexCoords(0xA5);
				font.XA6 = setTexCoords(0xA6);
				font.XA7 = setTexCoords(0xA7);
				font.XA8 = setTexCoords(0xA8);
				font.XA9 = setTexCoords(0xA9);
				font.XAA = setTexCoords(0xAA);
				font.XAB = setTexCoords(0xAB);
				font.XAC = setTexCoords(0xAC);
				font.XAD = setTexCoords(0xAD);
				font.XAE = setTexCoords(0xAE);
				font.XAF = setTexCoords(0xAF);

				font.XB0 = setTexCoords(0xB0);
				font.XB1 = setTexCoords(0xB1);
				font.XB2 = setTexCoords(0xB2);
				font.XB3 = setTexCoords(0xB3);
				font.XB4 = setTexCoords(0xB4);
				font.XB5 = setTexCoords(0xB5);
				font.XB6 = setTexCoords(0xB6);
				font.XB7 = setTexCoords(0xB7);
				font.XB8 = setTexCoords(0xB8);
				font.XB9 = setTexCoords(0xB9);
				font.XBA = setTexCoords(0xBA);
				font.XBB = setTexCoords(0xBB);
				font.XBC = setTexCoords(0xBC);
				font.XBD = setTexCoords(0xBD);
				font.XBE = setTexCoords(0xBE);
				font.XBF = setTexCoords(0xBF);

				font.XC0 = setTexCoords(0xC0);
				font.XC1 = setTexCoords(0xC1);
				font.XC2 = setTexCoords(0xC2);
				font.XC3 = setTexCoords(0xC3);
				font.XC4 = setTexCoords(0xC4);
				font.XC5 = setTexCoords(0xC5);
				font.XC6 = setTexCoords(0xC6);
				font.XC7 = setTexCoords(0xC7);
				font.XC8 = setTexCoords(0xC8);
				font.XC9 = setTexCoords(0xC9);
				font.XCA = setTexCoords(0xCA);
				font.XCB = setTexCoords(0xCB);
				font.XCC = setTexCoords(0xCC);
				font.XCD = setTexCoords(0xCD);
				font.XCE = setTexCoords(0xCE);
				font.XCF = setTexCoords(0xCF);

				font.XD0 = setTexCoords(0xD0);
				font.XD1 = setTexCoords(0xD1);
				font.XD2 = setTexCoords(0xD2);
				font.XD3 = setTexCoords(0xD3);
				font.XD4 = setTexCoords(0xD4);
				font.XD5 = setTexCoords(0xD5);
				font.XD6 = setTexCoords(0xD6);
				font.XD7 = setTexCoords(0xD7);
				font.XD8 = setTexCoords(0xD8);
				font.XD9 = setTexCoords(0xD9);
				font.XDA = setTexCoords(0xDA);
				font.XDB = setTexCoords(0xDB);
				font.XDC = setTexCoords(0xDC);
				font.XDD = setTexCoords(0xDD);
				font.XDE = setTexCoords(0xDE);
				font.XDF = setTexCoords(0xDF);

				font.XE0 = setTexCoords(0xE0);
				font.XE1 = setTexCoords(0xE1);
				font.XE2 = setTexCoords(0xE2);
				font.XE3 = setTexCoords(0xE3);
				font.XE4 = setTexCoords(0xE4);
				font.XE5 = setTexCoords(0xE5);
				font.XE6 = setTexCoords(0xE6);
				font.XE7 = setTexCoords(0xE7);
				font.XE8 = setTexCoords(0xE8);
				font.XE9 = setTexCoords(0xE9);
				font.XEA = setTexCoords(0xEA);
				font.XEB = setTexCoords(0xEB);
				font.XEC = setTexCoords(0xEC);
				font.XED = setTexCoords(0xED);
				font.XEE = setTexCoords(0xEE);
				font.XEF = setTexCoords(0xEF);

				font.XF0 = setTexCoords(0xF0);
				font.XF1 = setTexCoords(0xF1);
				font.XF2 = setTexCoords(0xF2);
				font.XF3 = setTexCoords(0xF3);
				font.XF4 = setTexCoords(0xF4);
				font.XF5 = setTexCoords(0xF5);
				font.XF6 = setTexCoords(0xF6);
				font.XF7 = setTexCoords(0xF7);
				font.XF8 = setTexCoords(0xF8);
				font.XF9 = setTexCoords(0xF9);
				font.XFA = setTexCoords(0xFA);
				font.XFB = setTexCoords(0xFB);
				font.XFC = setTexCoords(0xFC);
				font.XFD = setTexCoords(0xFD);
				font.XFE = setTexCoords(0xFE);
				font.XFF = setTexCoords(0xFF);

				font.EXCLAIM[0][0] = 0.0625;
				font.EXCLAIM[0][1] = 0.1250;
				font.EXCLAIM[1][0] = 0.0625;
				font.EXCLAIM[1][1] = 0.1875;
				font.EXCLAIM[2][0] = 0.1250;
				font.EXCLAIM[2][1] = 0.1875;
				font.EXCLAIM[3][0] = 0.1250;
				font.EXCLAIM[3][1] = 0.1250;

				font.QUOTEDBL[0][0] = 0.1250;
				font.QUOTEDBL[0][1] = 0.1250;
				font.QUOTEDBL[1][0] = 0.1250;
				font.QUOTEDBL[1][1] = 0.1875;
				font.QUOTEDBL[2][0] = 0.1875;
				font.QUOTEDBL[2][1] = 0.1875;
				font.QUOTEDBL[3][0] = 0.1875;
				font.QUOTEDBL[3][1] = 0.1250;

				font.HASH[0][0] = 0.1875;
				font.HASH[0][1] = 0.1250;
				font.HASH[1][0] = 0.1875;
				font.HASH[1][1] = 0.1875;
				font.HASH[2][0] = 0.2500;
				font.HASH[2][1] = 0.1875;
				font.HASH[3][0] = 0.2500;
				font.HASH[3][1] = 0.1250;

				font.DOLLAR[0][0] = 0.2500;
				font.DOLLAR[0][1] = 0.1250;
				font.DOLLAR[1][0] = 0.2500;
				font.DOLLAR[1][1] = 0.1875;
				font.DOLLAR[2][0] = 0.3125;
				font.DOLLAR[2][1] = 0.1875;
				font.DOLLAR[3][0] = 0.3125;
				font.DOLLAR[3][1] = 0.1250;

				font.PERCENT[0][0] = 0.3125;
				font.PERCENT[0][1] = 0.1250;
				font.PERCENT[1][0] = 0.3125;
				font.PERCENT[1][1] = 0.1875;
				font.PERCENT[2][0] = 0.3750;
				font.PERCENT[2][1] = 0.1875;
				font.PERCENT[3][1] = 0.3750;
				font.PERCENT[3][1] = 0.1250;

				font.AMPERSAND[0][0] = 0.3750;
				font.AMPERSAND[0][1] = 0.1250;
				font.AMPERSAND[1][0] = 0.3750;
				font.AMPERSAND[1][1] = 0.1875;
				font.AMPERSAND[2][0] = 0.4375;
				font.AMPERSAND[2][1] = 0.1875;
				font.AMPERSAND[3][0] = 0.4375;
				font.AMPERSAND[3][1] = 0.1250;

				font.QUOTE[0][0] = 0.4375;
				font.QUOTE[0][1] = 0.1250;
				font.QUOTE[1][0] = 0.4375;
				font.QUOTE[1][1] = 0.1875;
				font.QUOTE[2][0] = 0.5000;
				font.QUOTE[2][1] = 0.1875;
				font.QUOTE[3][0] = 0.5000;
				font.QUOTE[3][1] = 0.1250;

				font.LPAREN[0][0] = 0.5000;
				font.LPAREN[0][1] = 0.1250;
				font.LPAREN[1][0] = 0.5000;
				font.LPAREN[1][1] = 0.1875;
				font.LPAREN[2][0] = 0.5625;
				font.LPAREN[2][1] = 0.1875;
				font.LPAREN[3][0] = 0.5625;
				font.LPAREN[3][1] = 0.1250;

				font.RPAREN[0][0] = 0.5625;
				font.RPAREN[0][1] = 0.1250;
				font.RPAREN[1][0] = 0.5625;
				font.RPAREN[1][1] = 0.1875;
				font.RPAREN[2][0] = 0.6250;
				font.RPAREN[2][1] = 0.1875;
				font.RPAREN[3][0] = 0.6250;
				font.RPAREN[3][1] = 0.1250;

				font.ASTERISK[0][0] = 0.6250;
				font.ASTERISK[0][1] = 0.1250;
				font.ASTERISK[1][0] = 0.6250;
				font.ASTERISK[1][1] = 0.1875;
				font.ASTERISK[2][0] = 0.6875;
				font.ASTERISK[2][1] = 0.1875;
				font.ASTERISK[3][0] = 0.6875;
				font.ASTERISK[3][1] = 0.1250;

				font.PLUS[0][0] = 0.6875;
				font.PLUS[0][1] = 0.1250;
				font.PLUS[1][0] = 0.6875;
				font.PLUS[1][1] = 0.1875;
				font.PLUS[2][0] = 0.7500;
				font.PLUS[2][1] = 0.1875;
				font.PLUS[3][0] = 0.7500;
				font.PLUS[3][1] = 0.1250;

				font.COMMA[0][0] = 0.7500;
				font.COMMA[0][1] = 0.1250;
				font.COMMA[1][0] = 0.7500;
				font.COMMA[1][1] = 0.1875;
				font.COMMA[2][0] = 0.8125;
				font.COMMA[2][1] = 0.1875;
				font.COMMA[3][0] = 0.8125;
				font.COMMA[3][1] = 0.1250;

				font.MINUS[0][0] = 0.8125;
				font.MINUS[0][1] = 0.1250;
				font.MINUS[1][0] = 0.8125;
				font.MINUS[1][1] = 0.1875;
				font.MINUS[2][0] = 0.8750;
				font.MINUS[2][1] = 0.1875;
				font.MINUS[3][0] = 0.8750;
				font.MINUS[3][1] = 0.1250;

				font.PERIOD[0][0] = 0.8750;
				font.PERIOD[0][1] = 0.1250;
				font.PERIOD[1][0] = 0.8750;
				font.PERIOD[1][1] = 0.1875;
				font.PERIOD[2][0] = 0.9375;
				font.PERIOD[2][1] = 0.1875;
				font.PERIOD[3][0] = 0.9375;
				font.PERIOD[3][1] = 0.1250;

				font.SLASH[0][0] = 0.9375;
				font.SLASH[0][1] = 0.1250;
				font.SLASH[1][0] = 0.9375;
				font.SLASH[1][1] = 0.1875;
				font.SLASH[2][0] = 1.0000;
				font.SLASH[2][1] = 0.1875;
				font.SLASH[3][0] = 1.0000;
				font.SLASH[3][1] = 0.1250;

				font.num0[0][0] = 0.0000;
				font.num0[0][1] = 0.1875;
				font.num0[1][0] = 0.0000;
				font.num0[1][1] = 0.2500;
				font.num0[2][0] = 0.0625;
				font.num0[2][1] = 0.2500;
				font.num0[3][0] = 0.0625;
				font.num0[3][1] = 0.1875;

				font.num1[0][0] = 0.0625;
				font.num1[0][1] = 0.1875;
				font.num1[1][0] = 0.0625;
				font.num1[1][1] = 0.2500;
				font.num1[2][0] = 0.1250;
				font.num1[2][1] = 0.2500;
				font.num1[3][0] = 0.1250;
				font.num1[3][1] = 0.1875;

				font.num2[0][0] = 0.1250;
				font.num2[0][1] = 0.1875;
				font.num2[1][0] = 0.1250;
				font.num2[1][1] = 0.2500;
				font.num2[2][0] = 0.1875;
				font.num2[2][1] = 0.2500;
				font.num2[3][0] = 0.1875;
				font.num2[3][1] = 0.1875;

				font.num3[0][0] = 0.1875;
				font.num3[0][1] = 0.1875;
				font.num3[1][0] = 0.1875;
				font.num3[1][1] = 0.2500;
				font.num3[2][0] = 0.2500;
				font.num3[2][1] = 0.2500;
				font.num3[3][0] = 0.2500;
				font.num3[3][1] = 0.1875;

				font.num4[0][0] = 0.2500;
				font.num4[0][1] = 0.1875;
				font.num4[1][0] = 0.2500;
				font.num4[1][1] = 0.2500;
				font.num4[2][0] = 0.3125;
				font.num4[2][1] = 0.2500;
				font.num4[3][0] = 0.3125;
				font.num4[3][1] = 0.1875;

				font.num5[0][0] = 0.3125;
				font.num5[0][1] = 0.1875;
				font.num5[1][0] = 0.3125;
				font.num5[1][1] = 0.2500;
				font.num5[2][0] = 0.3750;
				font.num5[2][1] = 0.2500;
				font.num5[3][0] = 0.3750;
				font.num5[3][1] = 0.1875;

				font.num6[0][0] = 0.3750;
				font.num6[0][1] = 0.1875;
				font.num6[1][0] = 0.3750;
				font.num6[1][1] = 0.2500;
				font.num6[2][0] = 0.4375;
				font.num6[2][1] = 0.2500;
				font.num6[3][0] = 0.4375;
				font.num6[3][1] = 0.1875;

				font.num7[0][0] = 0.4375;
				font.num7[0][1] = 0.1875;
				font.num7[1][0] = 0.4375;
				font.num7[1][1] = 0.2500;
				font.num7[2][0] = 0.5000;
				font.num7[2][1] = 0.2500;
				font.num7[3][0] = 0.5000;
				font.num7[3][1] = 0.1875;

				font.num8[0][0] = 0.5000;
				font.num8[0][1] = 0.1875;
				font.num8[1][0] = 0.5000;
				font.num8[1][1] = 0.2500;
				font.num8[2][0] = 0.5625;
				font.num8[2][1] = 0.2500;
				font.num8[3][0] = 0.5625;
				font.num8[3][1] = 0.1875;

				font.num9[0][0] = 0.5625;
				font.num9[0][1] = 0.1875;
				font.num9[1][0] = 0.5625;
				font.num9[1][1] = 0.2500;
				font.num9[2][0] = 0.6250;
				font.num9[2][1] = 0.2500;
				font.num9[3][0] = 0.6250;
				font.num9[3][1] = 0.1875;

				font.COLON[0][0] = 0.6250;
				font.COLON[0][1] = 0.1875;
				font.COLON[1][0] = 0.6250;
				font.COLON[1][1] = 0.2500;
				font.COLON[2][0] = 0.6875;
				font.COLON[2][1] = 0.2500;
				font.COLON[3][0] = 0.6875;
				font.COLON[3][1] = 0.1875;

				font.SEMICOLON[0][0] = 0.6875;
				font.SEMICOLON[0][1] = 0.1875;
				font.SEMICOLON[1][0] = 0.6875;
				font.SEMICOLON[1][1] = 0.2500;
				font.SEMICOLON[2][0] = 0.7500;
				font.SEMICOLON[2][1] = 0.2500;
				font.SEMICOLON[3][0] = 0.7500;
				font.SEMICOLON[3][1] = 0.1875;

				font.LESS[0][0] = 0.7500;
				font.LESS[0][1] = 0.1875;
				font.LESS[1][0] = 0.7500;
				font.LESS[1][1] = 0.2500;
				font.LESS[2][0] = 0.8125;
				font.LESS[2][1] = 0.2500;
				font.LESS[3][0] = 0.8125;
				font.LESS[3][1] = 0.1875;

				font.EQUALS[0][0] = 0.8125;
				font.EQUALS[0][1] = 0.1875;
				font.EQUALS[1][0] = 0.8125;
				font.EQUALS[1][1] = 0.2500;
				font.EQUALS[2][0] = 0.8750;
				font.EQUALS[2][1] = 0.2500;
				font.EQUALS[3][0] = 0.8750;
				font.EQUALS[3][1] = 0.1875;

				font.GREATER[0][0] = 0.8750;
				font.GREATER[0][1] = 0.1875;
				font.GREATER[1][0] = 0.8750;
				font.GREATER[1][1] = 0.2500;
				font.GREATER[2][0] = 0.9375;
				font.GREATER[2][1] = 0.2500;
				font.GREATER[3][0] = 0.9375;
				font.GREATER[3][1] = 0.1875;

				font.QUESTION[0][0] = 0.9375;
				font.QUESTION[0][1] = 0.1875;
				font.QUESTION[1][0] = 0.9375;
				font.QUESTION[1][1] = 0.2500;
				font.QUESTION[2][0] = 1.0000;
				font.QUESTION[2][1] = 0.2500;
				font.QUESTION[3][0] = 1.0000;
				font.QUESTION[3][1] = 0.1875;

				font.AT[0][0] = 0.0000;
				font.AT[0][1] = 0.2500;
				font.AT[1][0] = 0.0000;
				font.AT[1][1] = 0.3125;
				font.AT[2][0] = 0.0625;
				font.AT[2][1] = 0.3125;
				font.AT[3][0] = 0.0625;
				font.AT[3][1] = 0.2500;

				font.A[0][0] = 0.0625;
				font.A[0][1] = 0.2500;
				font.A[1][0] = 0.0625;
				font.A[1][1] = 0.3125;
				font.A[2][0] = 0.1250;
				font.A[2][1] = 0.3125;
				font.A[3][0] = 0.1250;
				font.A[3][1] = 0.2500;

				font.B[0][0] = 0.1250;
				font.B[0][1] = 0.2500;
				font.B[1][0] = 0.1250;
				font.B[1][1] = 0.3125;
				font.B[2][0] = 0.1875;
				font.B[2][1] = 0.3125;
				font.B[3][0] = 0.1875;
				font.B[3][1] = 0.2500;

				font.C[0][0] = 0.1875;
				font.C[0][1] = 0.2500;
				font.C[1][0] = 0.1875;
				font.C[1][1] = 0.3125;
				font.C[2][0] = 0.2500;
				font.C[2][1] = 0.3125;
				font.C[3][0] = 0.2500;
				font.C[3][1] = 0.2500;

				font.D[0][0] = 0.2500;
				font.D[0][1] = 0.2500;
				font.D[1][0] = 0.2500;
				font.D[1][1] = 0.3125;
				font.D[2][0] = 0.3125;
				font.D[2][1] = 0.3125;
				font.D[3][0] = 0.3125;
				font.D[3][1] = 0.2500;

				font.E[0][0] = 0.3125;
				font.E[0][1] = 0.2500;
				font.E[1][0] = 0.3125;
				font.E[1][1] = 0.3125;
				font.E[2][0] = 0.3750;
				font.E[2][1] = 0.3125;
				font.E[3][0] = 0.3750;
				font.E[3][1] = 0.2500;

				font.F[0][0] = 0.3750;
				font.F[0][1] = 0.2500;
				font.F[1][0] = 0.3750;
				font.F[1][1] = 0.3125;
				font.F[2][0] = 0.4375;
				font.F[2][1] = 0.3125;
				font.F[3][0] = 0.4375;
				font.F[3][1] = 0.2500;

				font.G[0][0] = 0.4375;
				font.G[0][1] = 0.2500;
				font.G[1][0] = 0.4375;
				font.G[1][1] = 0.3125;
				font.G[2][0] = 0.5000;
				font.G[2][1] = 0.3125;
				font.G[3][0] = 0.5000;
				font.G[3][1] = 0.2500;

				font.H[0][0] = 0.5000;
				font.H[0][1] = 0.2500;
				font.H[1][0] = 0.5000;
				font.H[1][1] = 0.3125;
				font.H[2][0] = 0.5625;
				font.H[2][1] = 0.3125;
				font.H[3][0] = 0.5625;
				font.H[3][1] = 0.2500;

				font.I[0][0] = 0.5625;
				font.I[0][1] = 0.2500;
				font.I[1][0] = 0.5625;
				font.I[1][1] = 0.3125;
				font.I[2][0] = 0.6250;
				font.I[2][1] = 0.3125;
				font.I[3][0] = 0.6250;
				font.I[3][1] = 0.2500;

				font.J[0][0] = 0.6250;
				font.J[0][1] = 0.2500;
				font.J[1][0] = 0.6250;
				font.J[1][1] = 0.3125;
				font.J[2][0] = 0.6875;
				font.J[2][1] = 0.3125;
				font.J[3][0] = 0.6875;
				font.J[3][1] = 0.2500;

				font.K[0][0] = 0.6875;
				font.K[0][1] = 0.2500;
				font.K[1][0] = 0.6875;
				font.K[1][1] = 0.3125;
				font.K[2][0] = 0.7500;
				font.K[2][1] = 0.3125;
				font.K[3][0] = 0.7500;
				font.K[3][1] = 0.2500;

				font.L[0][0] = 0.7500;
				font.L[0][1] = 0.2500;
				font.L[1][0] = 0.7500;
				font.L[1][1] = 0.3125;
				font.L[2][0] = 0.8125;
				font.L[2][1] = 0.3125;
				font.L[3][0] = 0.8125;
				font.L[3][1] = 0.2500;

				font.M[0][0] = 0.8125;
				font.M[0][1] = 0.2500;
				font.M[1][0] = 0.8125;
				font.M[1][1] = 0.3125;
				font.M[2][0] = 0.8750;
				font.M[2][1] = 0.3125;
				font.M[3][0] = 0.8750;
				font.M[3][1] = 0.2500;

				font.N[0][0] = 0.8750;
				font.N[0][1] = 0.2500;
				font.N[1][0] = 0.8750;
				font.N[1][1] = 0.3125;
				font.N[2][0] = 0.9375;
				font.N[2][1] = 0.3125;
				font.N[3][0] = 0.9375;
				font.N[3][1] = 0.2500;

				font.O[0][0] = 0.9375;
				font.O[0][1] = 0.2500;
				font.O[1][0] = 0.9375;
				font.O[1][1] = 0.3125;
				font.O[2][0] = 1.0000;
				font.O[2][1] = 0.3125;
				font.O[3][0] = 1.0000;
				font.O[3][1] = 0.2500;

				font.P[0][0] = 0.0000;
				font.P[0][1] = 0.3125;
				font.P[1][0] = 0.0000;
				font.P[1][1] = 0.3750;
				font.P[2][0] = 0.0625;
				font.P[2][1] = 0.3750;
				font.P[3][0] = 0.0625;
				font.P[3][1] = 0.3125;

				font.Q[0][0] = 0.0625;
				font.Q[0][1] = 0.3125;
				font.Q[1][0] = 0.0625;
				font.Q[1][1] = 0.3750;
				font.Q[2][0] = 0.1250;
				font.Q[2][1] = 0.3750;
				font.Q[3][0] = 0.1250;
				font.Q[3][1] = 0.3125;

				font.R[0][0] = 0.1250;
				font.R[0][1] = 0.3125;
				font.R[1][0] = 0.1250;
				font.R[1][1] = 0.3750;
				font.R[2][0] = 0.1875;
				font.R[2][1] = 0.3750;
				font.R[3][0] = 0.1875;
				font.R[3][1] = 0.3125;

				font.S[0][0] = 0.1875;
				font.S[0][1] = 0.3125;
				font.S[1][0] = 0.1875;
				font.S[1][1] = 0.3750;
				font.S[2][0] = 0.2500;
				font.S[2][1] = 0.3750;
				font.S[3][0] = 0.2500;
				font.S[3][1] = 0.3125;

				font.T[0][0] = 0.2500;
				font.T[0][1] = 0.3125;
				font.T[1][0] = 0.2500;
				font.T[1][1] = 0.3750;
				font.T[2][0] = 0.3125;
				font.T[2][1] = 0.3750;
				font.T[3][0] = 0.3125;
				font.T[3][1] = 0.3125;

				font.U[0][0] = 0.3125;
				font.U[0][1] = 0.3125;
				font.U[1][0] = 0.3125;
				font.U[1][1] = 0.3750;
				font.U[2][0] = 0.3750;
				font.U[2][1] = 0.3750;
				font.U[3][0] = 0.3750;
				font.U[3][1] = 0.3125;

				font.V[0][0] = 0.3750;
				font.V[0][1] = 0.3125;
				font.V[1][0] = 0.3750;
				font.V[1][1] = 0.3750;
				font.V[2][0] = 0.4375;
				font.V[2][1] = 0.3750;
				font.V[3][0] = 0.4375;
				font.V[3][1] = 0.3125;

				font.W[0][0] = 0.4375;
				font.W[0][1] = 0.3125;
				font.W[1][0] = 0.4375;
				font.W[1][1] = 0.3750;
				font.W[2][0] = 0.5000;
				font.W[2][1] = 0.3750;
				font.W[3][0] = 0.5000;
				font.W[3][1] = 0.3125;

				font.X[0][0] = 0.5000;
				font.X[0][1] = 0.3125;
				font.X[1][0] = 0.5000;
				font.X[1][1] = 0.3750;
				font.X[2][0] = 0.5625;
				font.X[2][1] = 0.3750;
				font.X[3][0] = 0.5625;
				font.X[3][1] = 0.3125;

				font.Y[0][0] = 0.5625;
				font.Y[0][1] = 0.3125;
				font.Y[1][0] = 0.5625;
				font.Y[1][1] = 0.3750;
				font.Y[2][0] = 0.6250;
				font.Y[2][1] = 0.3750;
				font.Y[3][0] = 0.6250;
				font.Y[3][1] = 0.3125;

				font.Z[0][0] = 0.6250;
				font.Z[0][1] = 0.3125;
				font.Z[1][0] = 0.6250;
				font.Z[1][1] = 0.3750;
				font.Z[2][0] = 0.6875;
				font.Z[2][1] = 0.3750;
				font.Z[3][0] = 0.6875;
				font.Z[3][1] = 0.3125;

				font.LBRACKET[0][0] = 0.6875;
				font.LBRACKET[0][1] = 0.3125;
				font.LBRACKET[1][0] = 0.6875;
				font.LBRACKET[1][1] = 0.3750;
				font.LBRACKET[2][0] = 0.7500;
				font.LBRACKET[2][1] = 0.3750;
				font.LBRACKET[3][0] = 0.7500;
				font.LBRACKET[3][1] = 0.3125;

				font.BACKSLASH[0][0] = 0.7500;
				font.BACKSLASH[0][1] = 0.3125;
				font.BACKSLASH[1][0] = 0.7500;
				font.BACKSLASH[1][1] = 0.3750;
				font.BACKSLASH[2][0] = 0.8125;
				font.BACKSLASH[2][1] = 0.3750;
				font.BACKSLASH[3][0] = 0.8125;
				font.BACKSLASH[3][1] = 0.3125;

				font.RBRACKET[0][0] = 0.8125;
				font.RBRACKET[0][1] = 0.3125;
				font.RBRACKET[1][0] = 0.8125;
				font.RBRACKET[1][1] = 0.3750;
				font.RBRACKET[2][0] = 0.8750;
				font.RBRACKET[2][1] = 0.3750;
				font.RBRACKET[3][0] = 0.8750;
				font.RBRACKET[3][1] = 0.3125;

				font.CARET[0][0] = 0.8750;
				font.CARET[0][1] = 0.3125;
				font.CARET[1][0] = 0.8750;
				font.CARET[1][1] = 0.3750;
				font.CARET[2][0] = 0.9375;
				font.CARET[2][1] = 0.3750;
				font.CARET[3][0] = 0.9375;
				font.CARET[3][1] = 0.3125;

				font.UNDERSCORE[0][0] = 0.9375;
				font.UNDERSCORE[0][1] = 0.3125;
				font.UNDERSCORE[1][0] = 0.9375;
				font.UNDERSCORE[1][1] = 0.3750;
				font.UNDERSCORE[2][0] = 1.0000;
				font.UNDERSCORE[2][1] = 0.3750;
				font.UNDERSCORE[3][0] = 1.0000;
				font.UNDERSCORE[3][1] = 0.3125;

				font.BACKQUOTE[0][0] = 0.0000;
				font.BACKQUOTE[0][1] = 0.3750;
				font.BACKQUOTE[1][0] = 0.0000;
				font.BACKQUOTE[1][1] = 0.4375;
				font.BACKQUOTE[2][0] = 0.0625;
				font.BACKQUOTE[2][1] = 0.4375;
				font.BACKQUOTE[3][0] = 0.0625;
				font.BACKQUOTE[3][1] = 0.3750;

				font.a[0][0] = 0.0625;
				font.a[0][1] = 0.3750;
				font.a[1][0] = 0.0625;
				font.a[1][1] = 0.4375;
				font.a[2][0] = 0.1250;
				font.a[2][1] = 0.4375;
				font.a[3][0] = 0.1250;
				font.a[3][1] = 0.3750;

				font.b[0][0] = 0.1250;
				font.b[0][1] = 0.3750;
				font.b[1][0] = 0.1250;
				font.b[1][1] = 0.4375;
				font.b[2][0] = 0.1875;
				font.b[2][1] = 0.4375;
				font.b[3][0] = 0.1875;
				font.b[3][1] = 0.3750;

				font.c[0][0] = 0.1875;
				font.c[0][1] = 0.3750;
				font.c[1][0] = 0.1875;
				font.c[1][1] = 0.4375;
				font.c[2][0] = 0.2500;
				font.c[2][1] = 0.4375;
				font.c[3][0] = 0.2500;
				font.c[3][1] = 0.3750;

				font.d[0][0] = 0.2500;
				font.d[0][1] = 0.3750;
				font.d[1][0] = 0.2500;
				font.d[1][1] = 0.4375;
				font.d[2][0] = 0.3125;
				font.d[2][1] = 0.4375;
				font.d[3][0] = 0.3125;
				font.d[3][1] = 0.3750;

				font.e[0][0] = 0.3125;
				font.e[0][1] = 0.3750;
				font.e[1][0] = 0.3125;
				font.e[1][1] = 0.4375;
				font.e[2][0] = 0.3750;
				font.e[2][1] = 0.4375;
				font.e[3][0] = 0.3750;
				font.e[3][1] = 0.3750;

				font.f[0][0] = 0.3750;
				font.f[0][1] = 0.3750;
				font.f[1][0] = 0.3750;
				font.f[1][1] = 0.4375;
				font.f[2][0] = 0.4375;
				font.f[2][1] = 0.4375;
				font.f[3][0] = 0.4375;
				font.f[3][1] = 0.3750;

				font.g[0][0] = 0.4375;
				font.g[0][1] = 0.3750;
				font.g[1][0] = 0.4375;
				font.g[1][1] = 0.4375;
				font.g[2][0] = 0.5000;
				font.g[2][1] = 0.4375;
				font.g[3][0] = 0.5000;
				font.g[3][1] = 0.3750;

				font.h[0][0] = 0.5000;
				font.h[0][1] = 0.3750;
				font.h[1][0] = 0.5000;
				font.h[1][1] = 0.4375;
				font.h[2][0] = 0.5625;
				font.h[2][1] = 0.4375;
				font.h[3][0] = 0.5625;
				font.h[3][1] = 0.3750;

				font.i[0][0] = 0.5625;
				font.i[0][1] = 0.3750;
				font.i[1][0] = 0.5625;
				font.i[1][1] = 0.4375;
				font.i[2][0] = 0.6250;
				font.i[2][1] = 0.4375;
				font.i[3][0] = 0.6250;
				font.i[3][1] = 0.3750;

				font.j[0][0] = 0.6250;
				font.j[0][1] = 0.3750;
				font.j[1][0] = 0.6250;
				font.j[1][1] = 0.4375;
				font.j[2][0] = 0.6875;
				font.j[2][1] = 0.4375;
				font.j[3][0] = 0.6875;
				font.j[3][1] = 0.3750;

				font.k[0][0] = 0.6875;
				font.k[0][1] = 0.3750;
				font.k[1][0] = 0.6875;
				font.k[1][1] = 0.4375;
				font.k[2][0] = 0.7500;
				font.k[2][1] = 0.4375;
				font.k[3][0] = 0.7500;
				font.k[3][1] = 0.3750;

				font.l[0][0] = 0.7500;
				font.l[0][1] = 0.3750;
				font.l[1][0] = 0.7500;
				font.l[1][1] = 0.4375;
				font.l[2][0] = 0.8125;
				font.l[2][1] = 0.4375;
				font.l[3][0] = 0.8125;
				font.l[3][1] = 0.3750;

				font.m[0][0] = 0.8125;
				font.m[0][1] = 0.3750;
				font.m[1][0] = 0.8125;
				font.m[1][1] = 0.4375;
				font.m[2][0] = 0.8750;
				font.m[2][1] = 0.4375;
				font.m[3][0] = 0.8750;
				font.m[3][1] = 0.3750;

				font.n[0][0] = 0.8750;
				font.n[0][1] = 0.3750;
				font.n[1][0] = 0.8750;
				font.n[1][1] = 0.4375;
				font.n[2][0] = 0.9375;
				font.n[2][1] = 0.4375;
				font.n[3][0] = 0.9375;
				font.n[3][1] = 0.3750;

				font.o[0][0] = 0.9375;
				font.o[0][1] = 0.3750;
				font.o[1][0] = 0.9375;
				font.o[1][1] = 0.4375;
				font.o[2][0] = 1.0000;
				font.o[2][1] = 0.4375;
				font.o[3][0] = 1.0000;
				font.o[3][1] = 0.3750;

				font.p[0][0] = 0.0000;
				font.p[0][1] = 0.4375;
				font.p[1][0] = 0.0000;
				font.p[1][1] = 0.5000;
				font.p[2][0] = 0.0625;
				font.p[2][1] = 0.5000;
				font.p[3][0] = 0.0625;
				font.p[3][1] = 0.4375;

				font.q[0][0] = 0.0625;
				font.q[0][1] = 0.4375;
				font.q[1][0] = 0.0625;
				font.q[1][1] = 0.5000;
				font.q[2][0] = 0.1250;
				font.q[2][1] = 0.5000;
				font.q[3][0] = 0.1250;
				font.q[3][1] = 0.4375;

				font.r[0][0] = 0.1250;
				font.r[0][1] = 0.4375;
				font.r[1][0] = 0.1250;
				font.r[1][1] = 0.5000;
				font.r[2][0] = 0.1875;
				font.r[2][1] = 0.5000;
				font.r[3][0] = 0.1875;
				font.r[3][1] = 0.4375;

				font.s[0][0] = 0.1875;
				font.s[0][1] = 0.4375;
				font.s[1][0] = 0.1875;
				font.s[1][1] = 0.5000;
				font.s[2][0] = 0.2500;
				font.s[2][1] = 0.5000;
				font.s[3][0] = 0.2500;
				font.s[3][1] = 0.4375;

				font.t[0][0] = 0.2500;
				font.t[0][1] = 0.4375;
				font.t[1][0] = 0.2500;
				font.t[1][1] = 0.5000;
				font.t[2][0] = 0.3125;
				font.t[2][1] = 0.5000;
				font.t[3][0] = 0.3125;
				font.t[3][1] = 0.4375;

				font.u[0][0] = 0.3125;
				font.u[0][1] = 0.4375;
				font.u[1][0] = 0.3125;
				font.u[1][1] = 0.5000;
				font.u[2][0] = 0.3750;
				font.u[2][1] = 0.5000;
				font.u[3][0] = 0.3750;
				font.u[3][1] = 0.4375;

				font.v[0][0] = 0.3750;
				font.v[0][1] = 0.4375;
				font.v[1][0] = 0.3750;
				font.v[1][1] = 0.5000;
				font.v[2][0] = 0.4375;
				font.v[2][1] = 0.5000;
				font.v[3][0] = 0.4375;
				font.v[3][1] = 0.4375;

				font.w[0][0] = 0.4375;
				font.w[0][1] = 0.4375;
				font.w[1][0] = 0.4375;
				font.w[1][1] = 0.5000;
				font.w[2][0] = 0.5000;
				font.w[2][1] = 0.5000;
				font.w[3][0] = 0.5000;
				font.w[3][1] = 0.4375;

				font.x[0][0] = 0.5000;
				font.x[0][1] = 0.4375;
				font.x[1][0] = 0.5000;
				font.x[1][1] = 0.5000;
				font.x[2][0] = 0.5625;
				font.x[2][1] = 0.5000;
				font.x[3][0] = 0.5625;
				font.x[3][1] = 0.4375;

				font.y[0][0] = 0.5625;
				font.y[0][1] = 0.4375;
				font.y[1][0] = 0.5625;
				font.y[1][1] = 0.5000;
				font.y[2][0] = 0.6250;
				font.y[2][1] = 0.5000;
				font.y[3][0] = 0.6250;
				font.y[3][1] = 0.4375;

				font.z[0][0] = 0.6250;
				font.z[0][1] = 0.4375;
				font.z[1][0] = 0.6250;
				font.z[1][1] = 0.5000;
				font.z[2][0] = 0.6875;
				font.z[2][1] = 0.5000;
				font.z[3][0] = 0.6875;
				font.z[3][1] = 0.4375;

				font.LBRACE[0][0] = 0.6875;
				font.LBRACE[0][1] = 0.4375;
				font.LBRACE[1][0] = 0.6875;
				font.LBRACE[1][1] = 0.5000;
				font.LBRACE[2][0] = 0.7500;
				font.LBRACE[2][1] = 0.5000;
				font.LBRACE[3][0] = 0.7500;
				font.LBRACE[3][1] = 0.4375;

				font.PIPE[0][0] = 0.7500;
				font.PIPE[0][1] = 0.4375;
				font.PIPE[1][0] = 0.7500;
				font.PIPE[1][1] = 0.5000;
				font.PIPE[2][0] = 0.8125;
				font.PIPE[2][1] = 0.5000;
				font.PIPE[3][0] = 0.8125;
				font.PIPE[3][1] = 0.4375;

				font.RBRACE[0][0] = 0.8125;
				font.RBRACE[0][1] = 0.4375;
				font.RBRACE[1][0] = 0.8125;
				font.RBRACE[1][1] = 0.5000;
				font.RBRACE[2][0] = 0.8750;
				font.RBRACE[2][1] = 0.5000;
				font.RBRACE[3][0] = 0.8750;
				font.RBRACE[3][1] = 0.4375;

				font.TILDE[0][0] = 0.8750;
				font.TILDE[0][1] = 0.4375;
				font.TILDE[1][0] = 0.8750;
				font.TILDE[1][1] = 0.5000;
				font.TILDE[2][0] = 0.9375;
				font.TILDE[2][1] = 0.5000;
				font.TILDE[3][0] = 0.9375;
				font.TILDE[3][1] = 0.4375;

				font.NULLCHAR[0][0] = 0.9375;
				font.NULLCHAR[0][1] = 0.4375;
				font.NULLCHAR[1][0] = 0.9375;
				font.NULLCHAR[1][1] = 0.5000;
				font.NULLCHAR[2][0] = 1.0000;
				font.NULLCHAR[2][1] = 0.5000;
				font.NULLCHAR[3][0] = 1.0000;
				font.NULLCHAR[3][1] = 0.4375;

				// This temp array determines the VAO index for each character
				std::string temp[CHARS]={	"\x00",	"\x01",	"\x02",	"\x03",	"\x04",	"\x05",	"\x06",	"\x07",	"\x08",	"\x09",	"\x0A",	"\x0B",	"\x0C",	"\x0D",	"\x0E",	"\x0F",
											"\x10",	"\x11",	"\x12",	"\x13",	"\x14",	"\x15",	"\x16",	"\x17",	"\x18",	"\x19",	"\x1A",	"\x1B",	"\x1C",	"\x1D",	"\x1E",	"\x1F",
											" ",	"!",	"\"",	"#",	"$",	"%",	"&",	"'",	"(",	")",	"*",	"+",	",",	"-",	".",	"/",
											"0",	"1",	"2",	"3",	"4",	"5",	"6",	"7",	"8",	"9",	":",	";",	"<",	"=",	">",	"?",
											"@",	"A",	"B",	"C",	"D",	"E",	"F",	"G",	"H",	"I",	"J",	"K",	"L",	"M",	"N",	"O",
											"P",	"Q",	"R",	"S",	"T",	"U",	"V",	"W",	"X",	"Y",	"Z",	"[",	"\\",	"]",	"^",	"_",
											"`",	"a",	"b",	"c",	"d",	"e",	"f",	"g",	"h",	"i",	"j",	"k",	"l",	"m",	"n",	"o",
											"p",	"q",	"r",	"s",	"t",	"u",	"v",	"w",	"x",	"y",	"z",	"{",	"|",	"}",	"~",	"\x7f",
											"\x80",	"\x81",	"\x82",	"\x83",	"\x84",	"\x85",	"\x86",	"\x87",	"\x88",	"\x89",	"\x8A",	"\x8B",	"\x8C",	"\x8D",	"\x8E",	"\x8F",
											"\x90",	"\x91",	"\x92",	"\x93",	"\x94",	"\x95",	"\x96",	"\x97",	"\x98",	"\x99",	"\x9A",	"\x9B",	"\x9C",	"\x9D",	"\x9E",	"\x9F",
											"\xA0",	"\xA1",	"\xA2",	"\xA3",	"\xA4",	"\xA5",	"\xA6",	"\xA7",	"\xA8",	"\xA9",	"\xAA",	"\xAB",	"\xAC",	"\xAD",	"\xAE",	"\xAF",
											"\xB0",	"\xB1",	"\xB2",	"\xB3",	"\xB4",	"\xB5",	"\xB6",	"\xB7",	"\xB8",	"\xB9",	"\xBA",	"\xBB",	"\xBC",	"\xBD",	"\xBE",	"\xBF",
											"\xC0",	"\xC1",	"\xC2",	"\xC3",	"\xC4",	"\xC5",	"\xC6",	"\xC7",	"\xC8",	"\xC9",	"\xCA",	"\xCB",	"\xCC",	"\xCD",	"\xCE",	"\xCF",
											"\xD0",	"\xD1",	"\xD2",	"\xD3",	"\xD4",	"\xD5",	"\xD6",	"\xD7",	"\xD8",	"\xD9",	"\xDA",	"\xDB",	"\xDC",	"\xDD",	"\xDE",	"\xDF",
											"\xE0",	"\xE1",	"\xE2",	"\xE3",	"\xE4",	"\xE5",	"\xE6",	"\xE7",	"\xE8",	"\xE9",	"\xEA",	"\xEB",	"\xEC",	"\xED",	"\xEE",	"\xEF",
											"\xF0",	"\xF1",	"\xF2",	"\xF3",	"\xF4",	"\xF5",	"\xF6",	"\xF7",	"\xF8",	"\xF9",	"\xFA",	"\xFB",	"\xFC",	"\xFD",	"\xFE",	"\xFF"
				};

				// Create a string<->uint mapping for VAO index
				for (uint n=0; n<CHARS; n++) {
					mapChar.insert(std::make_pair(temp[n], n));
				}

				/*
				 * Find the texture coordinates for each
				 * character in the array and assign it
				 * to the VAO.
				 */
				for (uint i=0; i<CHARS; i++) {
					if (temp[i]=="0") { pArray=font.num0; goto pArraySet; }
					else if (temp[i]=="1") { pArray=font.num1; goto pArraySet; }
					else if (temp[i]=="2") { pArray=font.num2; goto pArraySet; }
					else if (temp[i]=="3") { pArray=font.num3; goto pArraySet; }
					else if (temp[i]=="4") { pArray=font.num4; goto pArraySet; }
					else if (temp[i]=="5") { pArray=font.num5; goto pArraySet; }
					else if (temp[i]=="6") { pArray=font.num6; goto pArraySet; }
					else if (temp[i]=="7") { pArray=font.num7; goto pArraySet; }
					else if (temp[i]=="8") { pArray=font.num8; goto pArraySet; }
					else if (temp[i]=="9") { pArray=font.num9; goto pArraySet; }

					else if (temp[i]=="\x00") { pArray=font.X00;	goto pArraySet; }
					else if (temp[i]=="\x01") { pArray=font.X01;	goto pArraySet; }
					else if (temp[i]=="\x02") { pArray=font.X02;	goto pArraySet; }
					else if (temp[i]=="\x03") { pArray=font.X03;	goto pArraySet; }
					else if (temp[i]=="\x04") { pArray=font.X04;	goto pArraySet; }
					else if (temp[i]=="\x05") { pArray=font.X05;	goto pArraySet; }
					else if (temp[i]=="\x06") { pArray=font.X06;	goto pArraySet; }
					else if (temp[i]=="\x07") { pArray=font.X07;	goto pArraySet; }
					else if (temp[i]=="\x08") { pArray=font.X08;	goto pArraySet; }
					else if (temp[i]=="\x09") { pArray=font.X09;	goto pArraySet; }
					else if (temp[i]=="\x0A") { pArray=font.X0A;	goto pArraySet; }
					else if (temp[i]=="\x0B") { pArray=font.X0B;	goto pArraySet; }
					else if (temp[i]=="\x0C") { pArray=font.X0C;	goto pArraySet; }
					else if (temp[i]=="\x0D") { pArray=font.X0D;	goto pArraySet; }
					else if (temp[i]=="\x0E") { pArray=font.X0E;	goto pArraySet; }
					else if (temp[i]=="\x0F") { pArray=font.X0F;	goto pArraySet; }

					else if (temp[i]=="\x10") { pArray=font.X10;	goto pArraySet; }
					else if (temp[i]=="\x11") { pArray=font.X11;	goto pArraySet; }
					else if (temp[i]=="\x12") { pArray=font.X12;	goto pArraySet; }
					else if (temp[i]=="\x13") { pArray=font.X13;	goto pArraySet; }
					else if (temp[i]=="\x14") { pArray=font.X14;	goto pArraySet; }
					else if (temp[i]=="\x15") { pArray=font.X15;	goto pArraySet; }
					else if (temp[i]=="\x16") { pArray=font.X16;	goto pArraySet; }
					else if (temp[i]=="\x17") { pArray=font.X17;	goto pArraySet; }
					else if (temp[i]=="\x18") { pArray=font.X18;	goto pArraySet; }
					else if (temp[i]=="\x19") { pArray=font.X19;	goto pArraySet; }
					else if (temp[i]=="\x1A") { pArray=font.X1A;	goto pArraySet; }
					else if (temp[i]=="\x1B") { pArray=font.X1B;	goto pArraySet; }
					else if (temp[i]=="\x1C") { pArray=font.X1C;	goto pArraySet; }
					else if (temp[i]=="\x1D") { pArray=font.X1D;	goto pArraySet; }
					else if (temp[i]=="\x1E") { pArray=font.X1E;	goto pArraySet; }
					else if (temp[i]=="\x1F") { pArray=font.X1F;	goto pArraySet; }

					else if (temp[i]=="\x80") { pArray=font.X80;	goto pArraySet; }
					else if (temp[i]=="\x81") { pArray=font.X81;	goto pArraySet; }
					else if (temp[i]=="\x82") { pArray=font.X82;	goto pArraySet; }
					else if (temp[i]=="\x83") { pArray=font.X83;	goto pArraySet; }
					else if (temp[i]=="\x84") { pArray=font.X84;	goto pArraySet; }
					else if (temp[i]=="\x85") { pArray=font.X85;	goto pArraySet; }
					else if (temp[i]=="\x86") { pArray=font.X86;	goto pArraySet; }
					else if (temp[i]=="\x87") { pArray=font.X87;	goto pArraySet; }
					else if (temp[i]=="\x88") { pArray=font.X88;	goto pArraySet; }
					else if (temp[i]=="\x89") { pArray=font.X89;	goto pArraySet; }
					else if (temp[i]=="\x8A") { pArray=font.X8A;	goto pArraySet; }
					else if (temp[i]=="\x8B") { pArray=font.X8B;	goto pArraySet; }
					else if (temp[i]=="\x8C") { pArray=font.X8C;	goto pArraySet; }
					else if (temp[i]=="\x8D") { pArray=font.X8D;	goto pArraySet; }
					else if (temp[i]=="\x8E") { pArray=font.X8E;	goto pArraySet; }
					else if (temp[i]=="\x8F") { pArray=font.X8F;	goto pArraySet; }

					else if (temp[i]=="\x90") { pArray=font.X90;	goto pArraySet; }
					else if (temp[i]=="\x91") { pArray=font.X91;	goto pArraySet; }
					else if (temp[i]=="\x92") { pArray=font.X92;	goto pArraySet; }
					else if (temp[i]=="\x93") { pArray=font.X93;	goto pArraySet; }
					else if (temp[i]=="\x94") { pArray=font.X94;	goto pArraySet; }
					else if (temp[i]=="\x95") { pArray=font.X95;	goto pArraySet; }
					else if (temp[i]=="\x96") { pArray=font.X96;	goto pArraySet; }
					else if (temp[i]=="\x97") { pArray=font.X97;	goto pArraySet; }
					else if (temp[i]=="\x98") { pArray=font.X98;	goto pArraySet; }
					else if (temp[i]=="\x99") { pArray=font.X99;	goto pArraySet; }
					else if (temp[i]=="\x9A") { pArray=font.X9A;	goto pArraySet; }
					else if (temp[i]=="\x9B") { pArray=font.X9B;	goto pArraySet; }
					else if (temp[i]=="\x9C") { pArray=font.X9C;	goto pArraySet; }
					else if (temp[i]=="\x9D") { pArray=font.X9D;	goto pArraySet; }
					else if (temp[i]=="\x9E") { pArray=font.X9E;	goto pArraySet; }
					else if (temp[i]=="\x9F") { pArray=font.X9F;	goto pArraySet; }

					else if (temp[i]=="\xA0") { pArray=font.XA0;	goto pArraySet; }
					else if (temp[i]=="\xA1") { pArray=font.XA1;	goto pArraySet; }
					else if (temp[i]=="\xA2") { pArray=font.XA2;	goto pArraySet; }
					else if (temp[i]=="\xA3") { pArray=font.XA3;	goto pArraySet; }
					else if (temp[i]=="\xA4") { pArray=font.XA4;	goto pArraySet; }
					else if (temp[i]=="\xA5") { pArray=font.XA5;	goto pArraySet; }
					else if (temp[i]=="\xA6") { pArray=font.XA6;	goto pArraySet; }
					else if (temp[i]=="\xA7") { pArray=font.XA7;	goto pArraySet; }
					else if (temp[i]=="\xA8") { pArray=font.XA8;	goto pArraySet; }
					else if (temp[i]=="\xA9") { pArray=font.XA9;	goto pArraySet; }
					else if (temp[i]=="\xAA") { pArray=font.XAA;	goto pArraySet; }
					else if (temp[i]=="\xAB") { pArray=font.XAB;	goto pArraySet; }
					else if (temp[i]=="\xAC") { pArray=font.XAC;	goto pArraySet; }
					else if (temp[i]=="\xAD") { pArray=font.XAD;	goto pArraySet; }
					else if (temp[i]=="\xAE") { pArray=font.XAE;	goto pArraySet; }
					else if (temp[i]=="\xAF") { pArray=font.XAF;	goto pArraySet; }

					else if (temp[i]=="\xB0") { pArray=font.XB0;	goto pArraySet; }
					else if (temp[i]=="\xB1") { pArray=font.XB1;	goto pArraySet; }
					else if (temp[i]=="\xB2") { pArray=font.XB2;	goto pArraySet; }
					else if (temp[i]=="\xB3") { pArray=font.XB3;	goto pArraySet; }
					else if (temp[i]=="\xB4") { pArray=font.XB4;	goto pArraySet; }
					else if (temp[i]=="\xB5") { pArray=font.XB5;	goto pArraySet; }
					else if (temp[i]=="\xB6") { pArray=font.XB6;	goto pArraySet; }
					else if (temp[i]=="\xB7") { pArray=font.XB7;	goto pArraySet; }
					else if (temp[i]=="\xB8") { pArray=font.XB8;	goto pArraySet; }
					else if (temp[i]=="\xB9") { pArray=font.XB9;	goto pArraySet; }
					else if (temp[i]=="\xBA") { pArray=font.XBA;	goto pArraySet; }
					else if (temp[i]=="\xBB") { pArray=font.XBB;	goto pArraySet; }
					else if (temp[i]=="\xBC") { pArray=font.XBC;	goto pArraySet; }
					else if (temp[i]=="\xBD") { pArray=font.XBD;	goto pArraySet; }
					else if (temp[i]=="\xBE") { pArray=font.XBE;	goto pArraySet; }
					else if (temp[i]=="\xBF") { pArray=font.XBF;	goto pArraySet; }

					else if (temp[i]=="\xC0") { pArray=font.XC0;	goto pArraySet; }
					else if (temp[i]=="\xC1") { pArray=font.XC1;	goto pArraySet; }
					else if (temp[i]=="\xC2") { pArray=font.XC2;	goto pArraySet; }
					else if (temp[i]=="\xC3") { pArray=font.XC3;	goto pArraySet; }
					else if (temp[i]=="\xC4") { pArray=font.XC4;	goto pArraySet; }
					else if (temp[i]=="\xC5") { pArray=font.XC5;	goto pArraySet; }
					else if (temp[i]=="\xC6") { pArray=font.XC6;	goto pArraySet; }
					else if (temp[i]=="\xC7") { pArray=font.XC7;	goto pArraySet; }
					else if (temp[i]=="\xC8") { pArray=font.XC8;	goto pArraySet; }
					else if (temp[i]=="\xC9") { pArray=font.XC9;	goto pArraySet; }
					else if (temp[i]=="\xCA") { pArray=font.XCA;	goto pArraySet; }
					else if (temp[i]=="\xCB") { pArray=font.XCB;	goto pArraySet; }
					else if (temp[i]=="\xCC") { pArray=font.XCC;	goto pArraySet; }
					else if (temp[i]=="\xCD") { pArray=font.XCD;	goto pArraySet; }
					else if (temp[i]=="\xCE") { pArray=font.XCE;	goto pArraySet; }
					else if (temp[i]=="\xCF") { pArray=font.XCF;	goto pArraySet; }

					else if (temp[i]=="\xD0") { pArray=font.XD0;	goto pArraySet; }
					else if (temp[i]=="\xD1") { pArray=font.XD1;	goto pArraySet; }
					else if (temp[i]=="\xD2") { pArray=font.XD2;	goto pArraySet; }
					else if (temp[i]=="\xD3") { pArray=font.XD3;	goto pArraySet; }
					else if (temp[i]=="\xD4") { pArray=font.XD4;	goto pArraySet; }
					else if (temp[i]=="\xD5") { pArray=font.XD5;	goto pArraySet; }
					else if (temp[i]=="\xD6") { pArray=font.XD6;	goto pArraySet; }
					else if (temp[i]=="\xD7") { pArray=font.XD7;	goto pArraySet; }
					else if (temp[i]=="\xD8") { pArray=font.XD8;	goto pArraySet; }
					else if (temp[i]=="\xD9") { pArray=font.XD9;	goto pArraySet; }
					else if (temp[i]=="\xDA") { pArray=font.XDA;	goto pArraySet; }
					else if (temp[i]=="\xDB") { pArray=font.XDB;	goto pArraySet; }
					else if (temp[i]=="\xDC") { pArray=font.XDC;	goto pArraySet; }
					else if (temp[i]=="\xDD") { pArray=font.XDD;	goto pArraySet; }
					else if (temp[i]=="\xDE") { pArray=font.XDE;	goto pArraySet; }
					else if (temp[i]=="\xDF") { pArray=font.XDF;	goto pArraySet; }

					else if (temp[i]=="\xE0") { pArray=font.XE0;	goto pArraySet; }
					else if (temp[i]=="\xE1") { pArray=font.XE1;	goto pArraySet; }
					else if (temp[i]=="\xE2") { pArray=font.XE2;	goto pArraySet; }
					else if (temp[i]=="\xE3") { pArray=font.XE3;	goto pArraySet; }
					else if (temp[i]=="\xE4") { pArray=font.XE4;	goto pArraySet; }
					else if (temp[i]=="\xE5") { pArray=font.XE5;	goto pArraySet; }
					else if (temp[i]=="\xE6") { pArray=font.XE6;	goto pArraySet; }
					else if (temp[i]=="\xE7") { pArray=font.XE7;	goto pArraySet; }
					else if (temp[i]=="\xE8") { pArray=font.XE8;	goto pArraySet; }
					else if (temp[i]=="\xE9") { pArray=font.XE9;	goto pArraySet; }
					else if (temp[i]=="\xEA") { pArray=font.XEA;	goto pArraySet; }
					else if (temp[i]=="\xEB") { pArray=font.XEB;	goto pArraySet; }
					else if (temp[i]=="\xEC") { pArray=font.XEC;	goto pArraySet; }
					else if (temp[i]=="\xED") { pArray=font.XED;	goto pArraySet; }
					else if (temp[i]=="\xEE") { pArray=font.XEE;	goto pArraySet; }
					else if (temp[i]=="\xEF") { pArray=font.XEF;	goto pArraySet; }

					else if (temp[i]=="\xF0") { pArray=font.XF0;	goto pArraySet; }
					else if (temp[i]=="\xF1") { pArray=font.XF1;	goto pArraySet; }
					else if (temp[i]=="\xF2") { pArray=font.XF2;	goto pArraySet; }
					else if (temp[i]=="\xF3") { pArray=font.XF3;	goto pArraySet; }
					else if (temp[i]=="\xF4") { pArray=font.XF4;	goto pArraySet; }
					else if (temp[i]=="\xF5") { pArray=font.XF5;	goto pArraySet; }
					else if (temp[i]=="\xF6") { pArray=font.XF6;	goto pArraySet; }
					else if (temp[i]=="\xF7") { pArray=font.XF7;	goto pArraySet; }
					else if (temp[i]=="\xF8") { pArray=font.XF8;	goto pArraySet; }
					else if (temp[i]=="\xF9") { pArray=font.XF9;	goto pArraySet; }
					else if (temp[i]=="\xFA") { pArray=font.XFA;	goto pArraySet; }
					else if (temp[i]=="\xFB") { pArray=font.XFB;	goto pArraySet; }
					else if (temp[i]=="\xFC") { pArray=font.XFC;	goto pArraySet; }
					else if (temp[i]=="\xFD") { pArray=font.XFD;	goto pArraySet; }
					else if (temp[i]=="\xFE") { pArray=font.XFE;	goto pArraySet; }
					else if (temp[i]=="\xFF") { pArray=font.XFF;	goto pArraySet; }

					else if (temp[i]=="±") { pArray=font.PLUSMINUS;	goto pArraySet; }
					else if (temp[i]=="!") { pArray=font.EXCLAIM;	goto pArraySet; }
					else if (temp[i]=="@") { pArray=font.AT;		goto pArraySet; }
					else if (temp[i]=="#") { pArray=font.HASH;		goto pArraySet; }
					else if (temp[i]=="$") { pArray=font.DOLLAR;	goto pArraySet; }
					else if (temp[i]=="%") { pArray=font.PERCENT;	goto pArraySet; }
					else if (temp[i]=="^") { pArray=font.CARET;		goto pArraySet; }
					else if (temp[i]=="&") { pArray=font.AMPERSAND; goto pArraySet; }
					else if (temp[i]=="*") { pArray=font.ASTERISK;	goto pArraySet; }
					else if (temp[i]=="(") { pArray=font.LPAREN;	goto pArraySet; }
					else if (temp[i]==")") { pArray=font.RPAREN;	goto pArraySet; }

					else if (temp[i]=="a") { pArray=font.a; goto pArraySet; }
					else if (temp[i]=="A") { pArray=font.A; goto pArraySet; }
					else if (temp[i]=="b") { pArray=font.b; goto pArraySet; }
					else if (temp[i]=="B") { pArray=font.B; goto pArraySet; }
					else if (temp[i]=="c") { pArray=font.c; goto pArraySet; }
					else if (temp[i]=="C") { pArray=font.C; goto pArraySet; }
					else if (temp[i]=="d") { pArray=font.d; goto pArraySet; }
					else if (temp[i]=="D") { pArray=font.D; goto pArraySet; }
					else if (temp[i]=="e") { pArray=font.e; goto pArraySet; }
					else if (temp[i]=="E") { pArray=font.E; goto pArraySet; }
					else if (temp[i]=="f") { pArray=font.f; goto pArraySet; }
					else if (temp[i]=="F") { pArray=font.F; goto pArraySet; }
					else if (temp[i]=="g") { pArray=font.g; goto pArraySet; }
					else if (temp[i]=="G") { pArray=font.G; goto pArraySet; }
					else if (temp[i]=="h") { pArray=font.h; goto pArraySet; }
					else if (temp[i]=="H") { pArray=font.H; goto pArraySet; }
					else if (temp[i]=="i") { pArray=font.i; goto pArraySet; }
					else if (temp[i]=="I") { pArray=font.I; goto pArraySet; }
					else if (temp[i]=="j") { pArray=font.j; goto pArraySet; }
					else if (temp[i]=="J") { pArray=font.J; goto pArraySet; }
					else if (temp[i]=="k") { pArray=font.k; goto pArraySet; }
					else if (temp[i]=="K") { pArray=font.K; goto pArraySet; }
					else if (temp[i]=="l") { pArray=font.l; goto pArraySet; }
					else if (temp[i]=="L") { pArray=font.L; goto pArraySet; }
					else if (temp[i]=="m") { pArray=font.m; goto pArraySet; }
					else if (temp[i]=="M") { pArray=font.M; goto pArraySet; }
					else if (temp[i]=="n") { pArray=font.n; goto pArraySet; }
					else if (temp[i]=="N") { pArray=font.N; goto pArraySet; }
					else if (temp[i]=="o") { pArray=font.o; goto pArraySet; }
					else if (temp[i]=="O") { pArray=font.O; goto pArraySet; }
					else if (temp[i]=="p") { pArray=font.p; goto pArraySet; }
					else if (temp[i]=="P") { pArray=font.P; goto pArraySet; }
					else if (temp[i]=="q") { pArray=font.q; goto pArraySet; }
					else if (temp[i]=="Q") { pArray=font.Q; goto pArraySet; }
					else if (temp[i]=="r") { pArray=font.r; goto pArraySet; }
					else if (temp[i]=="R") { pArray=font.R; goto pArraySet; }
					else if (temp[i]=="s") { pArray=font.s; goto pArraySet; }
					else if (temp[i]=="S") { pArray=font.S; goto pArraySet; }
					else if (temp[i]=="t") { pArray=font.t; goto pArraySet; }
					else if (temp[i]=="T") { pArray=font.T; goto pArraySet; }
					else if (temp[i]=="u") { pArray=font.u; goto pArraySet; }
					else if (temp[i]=="U") { pArray=font.U; goto pArraySet; }
					else if (temp[i]=="v") { pArray=font.v; goto pArraySet; }
					else if (temp[i]=="V") { pArray=font.V; goto pArraySet; }
					else if (temp[i]=="w") { pArray=font.w; goto pArraySet; }
					else if (temp[i]=="W") { pArray=font.W; goto pArraySet; }
					else if (temp[i]=="x") { pArray=font.x; goto pArraySet; }
					else if (temp[i]=="X") { pArray=font.X; goto pArraySet; }
					else if (temp[i]=="y") { pArray=font.y; goto pArraySet; }
					else if (temp[i]=="Y") { pArray=font.Y; goto pArraySet; }
					else if (temp[i]=="z") { pArray=font.z; goto pArraySet; }
					else if (temp[i]=="Z") { pArray=font.Z; goto pArraySet; }

					else if (temp[i]=="~") { pArray=font.TILDE;			goto pArraySet; }
					else if (temp[i]=="`") { pArray=font.BACKQUOTE;		goto pArraySet; }
					else if (temp[i]=="_") { pArray=font.UNDERSCORE;	goto pArraySet; }
					else if (temp[i]=="-") { pArray=font.MINUS;			goto pArraySet; }
					else if (temp[i]=="+") { pArray=font.PLUS;			goto pArraySet; }
					else if (temp[i]=="=") { pArray=font.EQUALS;		goto pArraySet; }
					else if (temp[i]=="{") { pArray=font.LBRACE;		goto pArraySet; }
					else if (temp[i]=="[") { pArray=font.LBRACKET;		goto pArraySet; }
					else if (temp[i]=="}") { pArray=font.RBRACE;		goto pArraySet; }
					else if (temp[i]=="]") { pArray=font.RBRACKET;		goto pArraySet; }
					else if (temp[i]=="|") { pArray=font.PIPE;			goto pArraySet; }
					else if (temp[i]=="\\"){ pArray=font.BACKSLASH;		goto pArraySet; }
					else if (temp[i]==":") { pArray=font.COLON;			goto pArraySet; }
					else if (temp[i]==";") { pArray=font.SEMICOLON;		goto pArraySet; }
					else if (temp[i]=="\""){ pArray=font.QUOTEDBL;		goto pArraySet; }
					else if (temp[i]=="\'"){ pArray=font.QUOTE;			goto pArraySet; }
					else if (temp[i]=="<") { pArray=font.LESS;			goto pArraySet; }
					else if (temp[i]==",") { pArray=font.COMMA;			goto pArraySet; }
					else if (temp[i]==">") { pArray=font.GREATER;		goto pArraySet; }
					else if (temp[i]==".") { pArray=font.PERIOD;		goto pArraySet; }
					else if (temp[i]=="?") { pArray=font.QUESTION;		goto pArraySet; }
					else if (temp[i]=="/") { pArray=font.SLASH;			goto pArraySet; }
					//else if (temp[i]==" ") { pArray=font.SPACE;			goto pArraySet; }	// Spaces are not drawn, ignore coords
					else pArray=font.NULLCHAR;
					pArraySet:

					//Standard font quad, CCW:CAB-BDC
					float iHalf_W = (Core::gameVars->font.vSize[0]/2);
					float iHalf_H = (Core::gameVars->font.vSize[1]/2);
					Data3f vVerts[] = { {-iHalf_W, -iHalf_H, 0},
										{ iHalf_W,  iHalf_H, 0},
										{-iHalf_W,  iHalf_H, 0},
										{-iHalf_W, -iHalf_H, 0},
										{ iHalf_W, -iHalf_H, 0},
										{ iHalf_W,  iHalf_H, 0 }};

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
			catch(...) {
				std::cout << "Failed" << std::endl;
				return false;
			}
		}

		/** ******************************************************************************************************************************
		 *
		 * @param x
		 * @param y
		 * @param fontNum
		 * @param eColor
		 * ****************************************************************************************************************************** */
		void _TextSys::start(int x, int y, int fontNum, Core::_Colors::_ACTIVE_COLOR eColor) {
			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			matrix->SetProjection(matrix->MM_ORTHO);
			shader->use(GLS_FONT);
			glDisable(GL_DEPTH_TEST);
			matrix->Push();
			matrix->Translate( (Core::gameVars->font.vSize[0]*x)+Core::gameVars->font.screenCoords[0], (-Core::gameVars->font.vSize[1]*y)+Core::gameVars->font.screenCoords[1], 0.0 );
			glActiveTexture(0);
			texture.Set(fontNum);
			colors.SetActive(eColor);
		}

		/** ******************************************************************************************************************************
		 *
		 * ****************************************************************************************************************************** */
		void _TextSys::update() {
			matrix->SetTransform();
			shader->getUniform(GLS_FONT);
		}

		/** ******************************************************************************************************************************
		 *
		 * ****************************************************************************************************************************** */
		void _TextSys::stop() {
			matrix->Pop();
			matrix->SetProjection(matrix->MM_PERSPECTIVE);
			glEnable(GL_DEPTH_TEST);
		}

		/** ******************************************************************************************************************************
		 *
		 * @param myChar
		 * @return
		 * ****************************************************************************************************************************** */
		int _TextSys::getIndex(char myChar) {
			std::string sChar = std::string(1, myChar);
			//std::string sChar = ""+myChar;

			if (sChar==" ") return SPACECHAR;
			else return mapChar[sChar];
		}

		/** ******************************************************************************************************************************
		 *
		 * @param sChar
		 * @return
		 * ****************************************************************************************************************************** */
		int _TextSys::getIndex(std::string sChar) {
			return mapChar[sChar];
		}

		//Draw any text to any position on screen
//		void _TextSys::draw(int x, int y, std::string buffer, Vector4f fontColor) {
//			colors->PushFront(fontColor);
//			draw(x, y, buffer);
//			colors->PopFront();
//		}

//		void _TextSys::draw(int x, int y, std::string buffer) {
//			start(x, y, Core::gameVars->font.iTexNum, Core::_Colors::COLOR_FRONT);
//			drawText(buffer);
//			stop();
//		}

		/** ******************************************************************************************************************************
		 * Draw text at character position given by \p x and \p y.
		 *
		 * @param x Character horizontal screen coordinate
		 * @param y Character vertical screen coordinate
		 * @param buffer Text to draw
		 * @param anchor Text anchor
		 * @param origin Text origin
		 * ****************************************************************************************************************************** */
		void _TextSys::draw2(float x, float y, std::string buffer, GUI::iConstrain anchor, GUI::iConstrain origin) {
			GUI::Props c;
			c.setOrigin(origin);
//			c.setAnchor(anchor);
			c.setPos(x*Core::gameVars->font.vSize.x, y*Core::gameVars->font.vSize.y);
//			c.setWidth(0, GUI::SIZE_CONSTRAINT_ABSOLUTE);
//			c.setHeight(0, GUI::SIZE_CONSTRAINT_ABSOLUTE);
			c.setWidth(buffer.length()*Core::gameVars->font.vSize.x, GUI::SIZE_CONSTRAINT_ABSOLUTE);
			c.setHeight(Core::gameVars->font.vSize.y, GUI::SIZE_CONSTRAINT_ABSOLUTE);
			c.exec();
			draw(&c, buffer, anchor);
		}

		/** ******************************************************************************************************************************
		 * Draw text at exact position given by \p x and \p y.
		 *
		 * @param x Exact horizontal screen coordinate
		 * @param y Exact vertical screen coordinate
		 * @param buffer Text to draw
		 * @param anchor Text anchor
		 * @param origin Text origin
		 * ****************************************************************************************************************************** */
		void _TextSys::draw(float x, float y, std::string buffer, GUI::iConstrain anchor, GUI::iConstrain origin) {
			GUI::Props c;
			c.setOrigin(origin);
//			c.setAnchor(anchor);
			c.setPos(x, y);
//			c.setWidth(0, GUI::SIZE_CONSTRAINT_ABSOLUTE);
//			c.setHeight(0, GUI::SIZE_CONSTRAINT_ABSOLUTE);
			c.setWidth(buffer.length()*Core::gameVars->font.vSize.x, GUI::SIZE_CONSTRAINT_ABSOLUTE);
			c.setHeight(Core::gameVars->font.vSize.y, GUI::SIZE_CONSTRAINT_ABSOLUTE);
			c.exec();
			draw(&c, buffer, anchor);
		}

		void _TextSys::draw(GUI::Props *con, std::string buffer) {
			draw(con, buffer, con->anchor);
		}

		/** ******************************************************************************************************************************
		 * Position based on Props, override anchor point.
		 * This is primarily used by other functions such as
		 * 	GUI slider that uses constraints for position
		 * 	information but label and values use their own
		 * 	anchor points.
		 * This function expects the position to be based on text center point
		 *
		 * @param c Text constraints from the calling object
		 * @param buffer Text to be drawn
		 * @param anchor Anchor point for the text relative to position of \p c. This anchor may not match the anchor in \p c.
		 * ****************************************************************************************************************************** */
		void _TextSys::draw(GUI::Props *con, std::string buffer, GUI::iConstrain anchor) {
			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			matrix->SetProjection(matrix->MM_ORTHO);
			shader->use(GLS_FONT);
			glDisable(GL_DEPTH_TEST);
			matrix->Push();
			{
				Vector2f vAnchor, vSize;

				vSize.x = Core::gameVars->font.vSize.x;
				vSize.y = Core::gameVars->font.vSize.y;

				vAnchor.x = 0.0f;
				vAnchor.y = -vSize.y/2.0f;

				float fHalfBuffer = buffer.length()/2.0f;

				vAnchor.x -= vSize.x*fHalfBuffer-(vSize.x/2.0f);
				vAnchor.y += vSize.y/2.0f;
				if(anchor&GUI::CONSTRAIN_LEFT)		vAnchor.x += (vSize.x*fHalfBuffer)+con->vPadding.left;
				if(anchor&GUI::CONSTRAIN_RIGHT)		vAnchor.x -= (vSize.x*fHalfBuffer)+con->vPadding.right;
				if(anchor&GUI::CONSTRAIN_TOP)		vAnchor.y -= (vSize.y/2.0f)+con->vPadding.top;
				if(anchor&GUI::CONSTRAIN_BOTTOM)	vAnchor.y += (vSize.y/2.0f)+con->vPadding.bottom;

				//Vector2f vPos = con->getScrollPos();
//				Core::debug.log("vPos = ("+std::to_string(vPos.x)+", "+std::to_string(vPos.y)+")");

				Vector2f vPos = con->getPos();
				if(con->scroll.getEnabled()) {
					vPos.x += con->scroll.getX();
					vPos.y += con->scroll.getY();
				}
				matrix->Translate(int(vPos.x+vAnchor.x), int(vPos.y+vAnchor.y), 0.0f);
				glActiveTexture(0);
				texture.Set(Core::gameVars->font.iTexNum);
				colors.SetActive(Core::_Colors::COLOR_FRONT);

				if(con->size.isAutoSet()) drawText(buffer);

//				// AutoSize - Do Last so above can detect this calculation hasen't been made yet in a previous cycle
//				if(con->size.constraint.xAuto) {
//					int maxSize = (buffer.length()*Core::gameVars->font.vSize.x)+(con->vPadding.left+con->vPadding.right);
//					con->setWidth(maxSize, GUI::SIZE_CONSTRAINT_ABSOLUTE);
//				}
//				if(con->size.constraint.yAuto) con->setHeight(Core::gameVars->font.vSize.y+(con->vPadding.top+con->vPadding.bottom), GUI::SIZE_CONSTRAINT_ABSOLUTE);
//				if(con->size.constraint.xAuto || con->size.constraint.yAuto) con->exec();

			}
			matrix->Pop();
			matrix->SetProjection(matrix->MM_PERSPECTIVE);
			glEnable(GL_DEPTH_TEST);
		}

		/** ******************************************************************************************************************************
		 * Draw text on multiple lines constrained by the size defined in \p con. Word wrapping occurs at spaces and newline characters.
		 *
		 * @param con Text constraints from the calling object
		 * @param buffer Text to be drawn
		 * @param anchor Anchor point for the text relative to position of \p con. This anchor may not match the anchor in \p con.
		 * ****************************************************************************************************************************** */

		void _TextSys::drawMulti(GUI::Props_Text *con, GUI::iConstrain anchor) {
			if(con->bufferPtr->length() > 0) {
				// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
				// 	Caclulate con->limit.x and con->limit.y
				// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//				con->limit.x = (con->size.x-(con->padding*2))/Core::gameVars->font.vSize.x;
//				con->limit.y = (con->size.y-(con->padding*3)-(Core::gameVars->font.vSize.y*2))/(Core::gameVars->font.vSize.y+con->iLineSpacing);
				if(con->bWordWrap) {
					con->limit.x = (con->size.x-(con->vPadding.left+con->vPadding.right))/Core::gameVars->font.vSize.x;
//					con->limit.y = (con->size.y-(con->vPadding.top+con->vPadding.bottom)-(Core::gameVars->font.vSize.y*2))/(Core::gameVars->font.vSize.y+con->iLineSpacing);
//					con->limit.y = (con->size.y-(con->vPadding.top+con->vPadding.bottom)-(Core::gameVars->font.vSize.y*2))/(Core::gameVars->font.vSize.y);
					con->limit.y = (con->size.y-(con->vPadding.top+con->vPadding.bottom))/(Core::gameVars->font.vSize.y);
				}
				else {
					con->limit.x = gameVars->screen.res.x;
					con->limit.y = gameVars->screen.res.y;
				}
				//con->limit.y = con->size.y-(con->vPadding.top+con->vPadding.bottom);
				//con->limit.y = con->size.y-con->vPadding.top; //+con->vPadding.bottom);
				//-(Core::gameVars->font.vSize.y*2))/(Core::gameVars->font.vSize.y+con->iLineSpacing)

				if(con->limit.y > Core::gameVars->font.vMax.y) con->limit.y = Core::gameVars->font.vMax.y;

				int iLines = 0;
				int iChars = 0;
				int lineChars[256];
				int lineMaxChars[256];
				std::string sWord[256];						// Maximum of 256 lines
				std::string word;

				char currentCursor;
				if(con->bOverwrite) currentCursor = Core::gameVars->font.cCursorO;
				else currentCursor = Core::gameVars->font.cCursorI;

				for(int i=0; i<=con->bufferPtr->length(); i++) {

					// Insert cursor into buffer
					if(con->bEnableCursor && i==con->iCursorPosition) {
						word += currentCursor;
					}

					if((*con->bufferPtr)[i] == '\n' || (*con->bufferPtr)[i] == ' ' || i==con->bufferPtr->length()) {
						if(con->bWordWrap && (iChars >= con->limit.x) ) {
							// Current line is done, save data and move on
							lineChars[iLines] = i-iChars;
							lineMaxChars[iLines] = iChars-word.length()-1;
							iChars = 0;
							iLines++;

							if((*con->bufferPtr)[i] == '\n') {
								sWord[iLines] += word;
								word = "";
								iChars = sWord[iLines].length();
								if(sWord[iLines].find_first_of(currentCursor) != std::string::npos) iChars -= 1;

								sWord[iLines] += word;
								lineChars[iLines] = i-iChars;
								lineMaxChars[iLines] = iChars;
								iLines++;
								iChars = 0;
								word = "";
							}
							else if(i==con->bufferPtr->length()) {
								sWord[iLines] += word;
								lineChars[iLines] = i-iChars;
								lineMaxChars[iLines] = iChars;
							}
							else {
								sWord[iLines] += word+' ';
								word = "";
								iChars = sWord[iLines].length();
								if(sWord[iLines].find_first_of(currentCursor) != std::string::npos) iChars -= 1;
							}

						}
						else if((*con->bufferPtr)[i] == '\n') {
							// Word is complete and within limit.x, add to line and continue to next word.
							sWord[iLines] += word;
							lineChars[iLines] = i-iChars;
							lineMaxChars[iLines] = iChars;
							iLines++;
							iChars = 0;
							word = "";
						}
						else if(i==con->bufferPtr->length()) {
							sWord[iLines] += word;
							lineChars[iLines] = i-iChars;
							lineMaxChars[iLines] = iChars;
						}
						else {
							// Word is complete and within limit.x, add to line and continue to next word.
							sWord[iLines] += word+' ';
							iChars += 1;
							word = "";
						}
					}
					else {
						// Word is not complete, add character to word and continue to next character
						word += (*con->bufferPtr)[i];
						iChars++;
					}
				}

				int iCursorLine = 0;
				if(con->bEnableCursor) {
					// Figure out what line the cursor is really on
					for(int l=0; l<=iLines; l++) {
						iCursorLine = l;
						for(int i=0; i<sWord[l].length(); i++) {
							con->iCursorChars = i;
							if(sWord[l][i] == currentCursor) goto FoundCursor;
						}
					}
					FoundCursor:

//					con->iCursorPosition = lineChars[iCursorLine]+con->iCursorChars;

					// Figure out and store the up/down cursor positions
					if(iCursorLine>0 && iCursorLine<=iLines-1) {
						con->iUpChars = lineChars[iCursorLine-1]+std::min(con->iCursorChars, lineMaxChars[iCursorLine-1]);
						con->iDownChars = std::min(lineChars[iCursorLine+1]+std::min(con->iCursorChars, lineMaxChars[iCursorLine+1]), (int)con->bufferPtr->length());
					}
					else if(iCursorLine>iLines-1) {
						con->iUpChars = lineChars[iCursorLine-1]+std::min(con->iCursorChars, lineMaxChars[iCursorLine-1]);
						con->iDownChars = con->bufferPtr->length();
					}
					else {
						con->iUpChars = 0;
						con->iDownChars = lineChars[iCursorLine+1]+con->iCursorChars;
					}
					if(iCursorLine<con->scrollPosition) con->scrollPosition = iCursorLine;
				}

				// Update external data
				if(con->scrollPosition>iLines) con->scrollPosition = iLines;
				if(con->iMaxLines!=iLines) con->iMaxLines = iLines;

				// Draw text if Sizing correct
				if(con->size.isAutoSet()) {
					// Draw each string on a new line
					bool bBreak = false;
					float linePos = 0.0f;
					if(con->scroll.getEnabled()) linePos = con->scroll.getY();
					//Vector2f vPos = con->getPos();
					//if(con->scroll.getEnabled()) {
					//	vPos.x += con->scroll.getX();
					//	vPos.y += con->scroll.getY();
					//}
					//matrix->Translate( vPos.x, vPos.y, 0.0f );

					for(int i=con->scrollPosition; i<=iLines; i++) {

						if( i-con->scrollPosition >= (con->limit.y-2) ) {
							bBreak = true;
						}

						if(sWord[i]=="") sWord[i]=" ";

						// FIXME: Scrolling - pixel scrolling makes text go too high
						// FIXME: Linespacing causes issues, probably related to aboce problem with pixel scrolling
						//linePos = -(i-0.5-con->scrollPosition)*(Core::gameVars->font.vSize.y+con->iLineSpacing);
	//					linePos = -(i-1-con->scrollPosition)*(Core::gameVars->font.vSize.y+con->iLineSpacing);
	//					linePos = -(i-0.5-con->scrollPosition)*(Core::gameVars->font.vSize.y+con->iLineSpacing);
	//					linePos = -(i-1-con->scrollPosition)*(Core::gameVars->font.vSize.y+con->iLineSpacing);
						linePos = -(i-1-con->scrollPosition)*(Core::gameVars->font.vSize.y);
						matrix->Push();
							matrix->Translate(0.0f, linePos-Core::gameVars->font.vSize.y, 0.0f);
							draw(con, sWord[i], anchor);
						matrix->Pop();

						if(bBreak) {
							if(con->bEnableCursor) if(iCursorLine>i) con->scrollPosition += iCursorLine-i;
							goto AbortText;
						}
					}
				}

				AbortText: ;

				// AutoSize - Do Last so above can detect this calculation hasen't been made yet in a previous cycle
				if(con->size.constraint.xAuto) {
					int iCharWidth = 0;
					for(int i=0; i<=iLines; i++) iCharWidth = std::max(iCharWidth, (int)sWord[i].length());
					con->setWidth((iCharWidth)*(gameVars->font.vSize.x)+con->vPadding.left+(con->vPadding.right));
				}
				if(con->size.constraint.yAuto) con->setHeight((iLines+1)*(gameVars->font.vSize.y)+con->vPadding.top+con->vPadding.bottom);
				if(con->size.constraint.xAuto || con->size.constraint.yAuto) con->exec();

			}
		}

		/** ******************************************************************************************************************************
		 *
		 * @tparam T
		 * @tparam T
		 * @param c
		 * @param buffer
		 * @param t
		 * @param precision
		 * @param anchor
		 * ***************************************************************************************************************************** */
		template<typename T>
		void _TextSys::drawVar(GUI::Props c,
							   std::string buffer,
							   T t,
							   int precision,
							   GUI::iConstrain anchor) {

			std::string vBuffer;
			std::stringstream stream;
			stream << std::fixed << std::setprecision(precision) << t;
			vBuffer = stream.str();

			buffer += vBuffer;
			draw(&c, buffer);

		}

		/** ******************************************************************************************************************************
		 *
		 * @tparam T
		 * @tparam T
		 * @param x
		 * @param y
		 * @param buffer
		 * @param t
		 * @param precision
		 * @param anchor
		 * @param origin
		 * ****************************************************************************************************************************** */
		template<typename T>
		void _TextSys::drawVar(int x,
							int y,
							std::string buffer,
							T t,
							int precision,
							GUI::iConstrain anchor,
							GUI::iConstrain origin) {

			std::string vBuffer;
			std::stringstream stream;
			stream << std::fixed << std::setprecision(precision) << t;
			vBuffer = stream.str();;

			buffer += vBuffer;
			draw(x, y, buffer, anchor, origin);
		}

		/** ******************************************************************************************************************************
		 *
		 * @tparam T
		 * @tparam T
		 * @param x
		 * @param y
		 * @param buffer
		 * @param t
		 * @param precision
		 * @param anchor
		 * @param origin
		 * ****************************************************************************************************************************** */
		template<typename T>
		void _TextSys::drawVar2(int x,
							int y,
							std::string buffer,
							T t,
							int precision,
							GUI::iConstrain anchor,
							GUI::iConstrain origin) {
			drawVar(x*Core::gameVars->font.vSize.x, y*Core::gameVars->font.vSize.y, buffer, t, precision, anchor, origin);
		}


		// TODO: Draw Special Characters
//		void _TextSys::drawSpecial(int x, int y, std::string sChar, Vector4f fontColor) {
//			colors->PushFront(fontColor);
//			drawSpecial(x, y, sChar);
//			colors->PopFront();
//		}

//		void _TextSys::drawSpecial(int x, int y, std::string sChar) {
//			start(x, y, Core::gameVars->font.iTexNum, Core::_Colors::COLOR_FRONT);
//			drawTextSpecial(sChar);
//			stop();
//		}

		/** ******************************************************************************************************************************
		 *	\brief Base drawing command. This is private and should not be called directly.
		 *
		 * @param buffer
		 * ****************************************************************************************************************************** */
		void _TextSys::drawText(std::string buffer) {
			for (uint i=0; i<buffer.length(); i++) {
				// TODO: Duplicate to other functions -> SKIP DRAWING SPACES, index 94 (SPACECHAR)
				if(buffer[i] == Core::gameVars->font.cCursorI || buffer[i] == Core::gameVars->font.cCursorO) {
					if(cursorBlink.split()>=250) {	// FIXME: Parameterize blink rate
						bBlinkState = !bBlinkState;
						cursorBlink.start();
					}

					if(bBlinkState) Core::colors.PushFront(Core::colors[Core::colors().Black]);		// TODO: Add to color pallette
					else Core::colors.PushFront(Core::colors[Core::colors().White]);				// TODO: Add to color pallette

					update();
					vao[getIndex(buffer[i])].Draw();
					Core::colors.PopFront();
				}
				else if(getIndex(buffer[i])!=SPACECHAR) {
					update();
					vao[getIndex(buffer[i])].Draw();
					matrix->Translate( Core::gameVars->font.vSize[0], 0.0, 0.0 );
				}
				else matrix->Translate( Core::gameVars->font.vSize[0], 0.0, 0.0 );
			}
		}

//		void _TextSys::drawTextSpecial(std::string sChar) {
//			//for (uint i=0; i<buffer.length(); i++) {
//				update();
//				// SKIP DRAWING SPACES, index 94 (SPACECHAR)
//				//if(getIndex(buffer[i])!=SPACECHAR) vao[getIndex(buffer[i])].Draw();
//				vao[getIndex(sChar)].Draw();
//				matrix->Translate( Core::gameVars->font.vSize[0], 0.0, 0.0 );
//			//}
//		}
}
#endif /* _TextSys_H_ */
