/*
 * System.h
 *
 *  Created on: Feb 21, 2011
 *      Author: bcthund
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

namespace Core {
	namespace GameSys {
		/* Passthrough routines to draw multiple systems at once
		 *  and make calling routines easier to use. Need to
		 *  move the menuSys function calls to here so that we
		 *  can get rid of the two seperate header files.
		 *
		 *  There are two types of functions:
		 *  	draw<type>:	Only draw, highlight if desired
		 *  	check<type>:	Draw, highlight, and return checkClick results
		 *
		 *  The check version is necessary so that multiple layers of
		 *   drawing commands can be controlled so they do not interfere.
		 *   This problem was realized when the Journal background was
		 *   returning a check value when an Icon was being clicked
		 *   on. The mouse delay was then causing the icon to never
		 *   trigger.
		 *
		 *  Therefore it should be noted that layered drawings could
		 *   behave unexpectedly when checking for mouse clicks.
		 *   However hovering always works.
		 */
		uint drawWindow(		int x,
								int y,
								int w,
								int h,
								bool bHighlight,
								bool textOffset,
								Core::Color backColor,
								Core::Color backHColor,
								short int iBorder=Core::GameSys::_WinSys::DRAWMODE.NORMAL);
		uint drawWindow(		int x,
								int y,
								int w,
								int h,
								bool bHighlight,
								bool textOffset,
								short int iBorder);

		void drawIcon(			uint x,
								uint y,
								float w,
								float h,
								uint id,
								std::string sTex,
								bool bHighlight,
								bool textOffset,
								Core::Color backColor,
								Core::Color backHColor);
		void drawIcon(			uint x,
								uint y,
								float w,
								float h,
								uint id,
								std::string sTex,
								bool bHighlight,
								bool textOffset);

		uint checkIcon2(		uint x,
								uint y,
								uint w,
								uint h,
								uint id,
								std::string sTex,
								bool bHighlight,
								bool textOffset,
								Core::Color backColor,
								Core::Color backHColor);
		uint checkIcon2(		uint x,
								uint y,
								uint w,
								uint h,
								uint id,
								std::string sTex,
								bool bHighlight,
								bool textOffset);

		uint checkIcon(			uint x,
								uint y,
								float w,
								float h,
								uint id,
								std::string sTex,
								bool bHighlight,
								bool textOffset,
								Core::Color backColor,
								Core::Color backHColor);
		uint checkIcon(			uint x,
								uint y,
								float w,
								float h,
								uint id,
								std::string sTex,
								bool bHighlight = true,
								bool textOffset = false);

		void drawCard(			int id0,
								int id1,
								int id2,
								int id3,
								std::string sTex,
								SHADER_PROGRAMS iShader);

		void drawWindow(		int x,
								int y,
								int w,
								int h,
								bool textOffset,
								Core::Color backColor,
								short int iBorder);
		void drawWindow(		int x,
								int y,
								int w,
								int h,
								bool textOffset,
								short int iBorder);

		void drawText(			int x,
								int y,
								std::string buffer,
								Core::Color fontColor,
								int xLimit,
								int yLimit);
		void drawText(			int x,
								int y,
								std::string buffer,
								int xLimit,
								int yLimit);

		void drawVariable(		int x,
								int y,
								bool bP,
								Core::Color fontColor);
		void drawVariable(		int x,
								int y,
								bool bP);

		void drawVariable(		int x,
								int y,
								int iP,
								Core::Color fontColor);
		void drawVariable(		int x,
								int y,
								int iP);

		void drawVariable(		int x,
								int y,
								uint iP,
								Core::Color fontColor);
		void drawVariable(		int x,
								int y,
								uint iP);

		void drawVariable(		int x,
								int y,
								float fP,
								Core::Color fontColor,
								bool bDec);
		void drawVariable(		int x,
								int y,
								float fP,
								bool bDec);

		void checkVariable(		int x,
								int y,
								bool bP,
								Core::Color fontColor);
		void checkVariable(		int x,
								int y,
								bool bP);

		void checkVariable(		int x,
								int y,
								int iP,
								Core::Color fontColor);
		void checkVariable(		int x,
								int y,
								int iP);

		void checkVariable(		int x,
								int y,
								float fP,
								Core::Color fontColor,
								bool bDec);
		void checkVariable(		int x,
								int y,
								float fP,
								bool bDec);

		uint drawTextWindow(	int x,
								int y,
								int w,
								int h,
								std::string sText,
								bool bHighlight,
								bool textOffset,
								Core::Color backColor,
								Core::Color frontColor,
								Core::Color backHColor,
								Core::Color frontHColor,
								short int iBorder);
		uint drawTextWindow(	int x,
								int y,
								int w,
								int h,
								std::string sText,
								bool bHighlight,
								bool textOffset,
								short int iBorder);

		uint checkText(			int x,
								int y,
								std::string sText,
								bool bHighlight,
								bool textOffset,
								Core::Color frontColor,
								Core::Color frontHColor);
		uint checkText(			int x,
								int y,
								std::string sText,
								bool bHighlight,
								bool textOffset);

//		void drawVariable(	int x,
//												int y,
//												... );


		// Used for 3D drawing routines with external matrix
		// Not sure if this is used anymore
		//void draw3DSprite(		std::string sTex,
		//						int iShader);

		void drawSprite(	uint x,
							uint y,
							float w,
							float h,
							std::string sTex,
							bool bHighlight,
							bool textOffset,
							Core::Color backColor,
							Core::Color backHColor);
		void drawSprite(	uint x,
							uint y,
							float w,
							float h,
							std::string sTex,
							bool bHighlight,
							bool textOffset,
							Core::Color frontColor);
		void drawSprite(	uint x,
							uint y,
							float w,
							float h,
							std::string sTex,
							bool bHighlight,
							bool textOffset);

		uint checkSprite(	uint x,
							uint y,
							float w,
							float h,
							std::string sTex,
							bool bHighlight,
							bool textOffset,
							Core::Color backColor,
							Core::Color backHColor);
		uint checkSprite(	uint x,
							uint y,
							float w,
							float h,
							std::string sTex,
							bool bHighlight,
							bool textOffset);

		uint checkMenu( 	uint x,
							uint y,
							std::string s);

//		/*
//		 * Draw an animation only
//		 */
//		void drawAnimation(			float x,
//									float y,
//									Core::Vector3f camera,
//									Core::Vector3f target,
//									int iA,
//									int loop,
//									__uint16_t rate,
//									bool bMoveOrigin=true);
//
//		/*
//		 * Draw an animation with a linked sound effect
//		 */
//		void playAnimation(			float x,
//									float y,
//									Core::Vector3f camera,
//									Core::Vector3f target,
//									int iA,
//									int loop,
//									__uint16_t rate,
//									int *iSample,
//									bool bMoveOrigin=true);

		//gameSys.drawWindow(	cx-2,	cy-1,	iW, 7, true, true, inv_select, inv_hover_select, GAME::SYSTEM.WINSYS.DRAWMODE.SELECTION)

		//uint checkWindow( uint x,)
		//									uint y,
		//									int w

		// TODO: Disabled for now, need to rework
		//	#include "./MenuSys/MenuFunc.h"
		//	#include "./ScriptSys/ScriptFunc.h"

		//	uint GameSys::checkMenu(uint x, uint y, string s) {
		//		return menuSys.draw(x, y, s);
		//	}

		uint drawWindow(	int x,															// Starting position of window
								int y,															// Starting position of window
								int w,															// Width of window
								int h,															// Height of window
								bool bHighlight,											// Highlight on mouseover?
								bool textOffset,											// Absolute or texture grid positioning?
								Core::Color backColor,	// Window standard color
								Core::Color backHColor,		// Window mouseover color
								short int iBorder) {										// Boder only?
			colors.PushBack(backColor);
			colors.PushBackHighlight(backHColor);
			uint r = drawWindow(x, y, w, h, bHighlight, textOffset, iBorder);
			colors.PopBack();
			colors.PopBackHighlight();
			return r;
		}

		uint drawWindow(	int x,															// Starting position of window
							int y,															// Starting position of window
							int w,															// Width of window
							int h,															// Height of window
							bool bHighlight,												// Highlight on mouseover?
							bool textOffset,												// Absolute or texture grid positioning?
							short int iBorder=Core::GameSys::_WinSys::DRAWMODE.NORMAL) {										// Boder only?

			//uint checkClick = MOUSE_NONE;
			uint checkClick = Core::_Mouse::MOUSE_NONE;

//			vWindowColor[0] = backColor[0];
//			vWindowColor[1] = backColor[1];
//			vWindowColor[2] = backColor[2];
//			vWindowColor[3] = backColor[3];

			// TODO: [GameSys] Fix highlight
			if (bHighlight) {
				if (textOffset) {
					if (Core::mouse->checkOver(x*Core::gameVars->font.vSize[0]+Core::gameVars->font.vHalfSize[0],y*Core::gameVars->font.vSize[1]+Core::gameVars->font.vHalfSize[1], (w-1)*Core::gameVars->font.vSize[0],(h-1)*Core::gameVars->font.vSize[1])) {
//						vWindowColor[0] = backHColor[0];
//						vWindowColor[1] = backHColor[1];
//						vWindowColor[2] = backHColor[2];
//						vWindowColor[3] = backHColor[3];
						colors.SetActive(colors.COLOR_BACK_HIGHLIGHT);
					}
				}
				else {
					if (Core::mouse->checkOver(x,y,w,h)) {
//						vWindowColor[0] = backHColor[0];
//						vWindowColor[1] = backHColor[1];
//						vWindowColor[2] = backHColor[2];
//						vWindowColor[3] = backHColor[3];
						colors.SetActive(colors.COLOR_BACK_HIGHLIGHT);
					}
				}
			}
			else colors.SetActive(colors.COLOR_BACK);

			winSys->draw(x, y, w, h, textOffset, iBorder);

			if (textOffset) checkClick=Core::mouse->checkInput(x*Core::gameVars->font.vSize[0]+Core::gameVars->font.vHalfSize[0], y*Core::gameVars->font.vSize[1]+Core::gameVars->font.vHalfSize[1], (w-1)*Core::gameVars->font.vSize[0],(h-1)*Core::gameVars->font.vSize[1]);
			else checkClick=Core::mouse->checkInput(x, y, w, h);

			return checkClick;
		}

		uint drawTextWindow(	int x,																								// Starting position of window
									int y,																								// Starting position of window
									int w,																								// Width of window
									int h,																								// Height of window
									std::string sText,																		// Text to print in window
									bool bHighlight,																// Highlight on mouseover?
									bool textOffset,																	// Absolute or texture grid positioning?
									Core::Color backColor,			// Window standard color
									Core::Color frontColor,			// Text normal color
									Core::Color backHColor,				// Window mouseover color
									Core::Color frontHColor,				// Text mouseover color
									short int iBorder=Core::GameSys::_WinSys::DRAWMODE.NORMAL) {										// Border only?

			colors.PushFront(frontColor);
			colors.PushFrontHighlight(frontHColor);
			colors.PushBack(backColor);
			colors.PushBackHighlight(backHColor);
			uint r = drawTextWindow(x, y, w, h, sText, bHighlight, textOffset, iBorder);
			colors.PopFront();
			colors.PopFrontHighlight();
			colors.PopBack();
			colors.PopBackHighlight();
			return r;
		}

		uint drawTextWindow(	int x,																								// Starting position of window
									int y,																								// Starting position of window
									int w,																								// Width of window
									int h,																								// Height of window
									std::string sText,																		// Text to print in window
									bool bHighlight,																// Highlight on mouseover?
									bool textOffset,																	// Absolute or texture grid positioning?
									short int iBorder=Core::GameSys::_WinSys::DRAWMODE.NORMAL) {										// Border only?

			uint checkClick = Core::_Mouse::MOUSE_NONE;;

			// TODO: [GameSys] Fix highlight
//			vWindowColor[0] = backColor[0];
//			vWindowColor[1] = backColor[1];
//			vWindowColor[2] = backColor[2];
//			vWindowColor[3] = backColor[3];
//
//			vTextColor[0] = frontColor[0];
//			vTextColor[1] = frontColor[1];
//			vTextColor[2] = frontColor[2];
//			vTextColor[3] = frontColor[3];
//
//			if (bHighlight) {
//				if (textOffset) {
//					if (Core::mouse->checkOver(x*Core::gameVars->font.vSize[0]+Core::gameVars->font.vHalfSize[0],y*Core::gameVars->font.vSize[1]+Core::gameVars->font.vHalfSize[1], (w-1)*Core::gameVars->font.vSize[0],(h-1)*Core::gameVars->font.vSize[1])) {
//						vWindowColor[0] = backHColor[0];
//						vWindowColor[1] = backHColor[1];
//						vWindowColor[2] = backHColor[2];
//						vWindowColor[3] = backHColor[3];
//
//						vTextColor[0] = frontHColor[0];
//						vTextColor[1] = frontHColor[1];
//						vTextColor[2] = frontHColor[2];
//						vTextColor[3] = frontHColor[3];
//					}
//				}
//				else {
//					if (Core::mouse->checkOver(x,y,w,h)) {
//						vWindowColor[0] = backHColor[0];
//						vWindowColor[1] = backHColor[1];
//						vWindowColor[2] = backHColor[2];
//						vWindowColor[3] = backHColor[3];
//
//						vTextColor[0] = frontHColor[0];
//						vTextColor[1] = frontHColor[1];
//						vTextColor[2] = frontHColor[2];
//						vTextColor[3] = frontHColor[3];
//					}
//				}
//			}

			winSys->draw(x, y, w, h, textOffset, iBorder);
			//textSys.draw(x+1, y+1, sText, vTextColor);
			drawText(x+1, y+1, sText, 1024, 1024);				// must specify xLimit and yLimit here for some reason

			if (textOffset) checkClick=Core::mouse->checkInput(x*Core::gameVars->font.vSize[0]+Core::gameVars->font.vHalfSize[0], y*Core::gameVars->font.vSize[1]+Core::gameVars->font.vHalfSize[1], (w-1)*Core::gameVars->font.vSize[0],(h-1)*Core::gameVars->font.vSize[1]);
			else checkClick=Core::mouse->checkInput(x, y, w, h);

			return checkClick;
		}

		uint checkText(	int x,																								// Starting position of window
								int y,																								// Starting position of window
								std::string sText,																		// Text to print in window
								bool bHighlight,																// Highlight on mouseover?
								bool textOffset,																	// Absolute or texture grid positioning?
								Core::Color frontColor,			// Text normal color
								Core::Color frontHColor) {			// Text mouseover color
			colors.PushFront(frontColor);
			colors.PushFrontHighlight(frontHColor);
			uint r = checkText(x, y, sText, bHighlight, textOffset);
			colors.PopFront();
			colors.PopFrontHighlight();
			return r;
		}

		uint checkText(	int x,																								// Starting position of window
								int y,																								// Starting position of window
								std::string sText,																		// Text to print in window
								bool bHighlight,																// Highlight on mouseover?
								bool textOffset) {			// Text mouseover color

			return menuSys->draw(	x,	y,	sText);
		}

		void drawIcon(	uint x,
								uint y,
								float w,
								float h,
								uint id,
								std::string sTex,
								bool bHighlight,
								bool textOffset,
								Core::Color backColor,
								Core::Color backHColor) {
			colors.PushBack(backColor);
			colors.PushBackHighlight(backHColor);
			drawIcon(x, y, w, h, id, sTex, bHighlight, textOffset);
			colors.PopBack();
			colors.PopBackHighlight();
		}

		void drawIcon(	uint x,
								uint y,
								float w,
								float h,
								uint id,
								std::string sTex,
								bool bHighlight,
								bool textOffset) {
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
			 */

			uint checkClick;

			// TODO: [GameSys] Fix highlight
//			vWindowColor[0] = backColor[0];
//			vWindowColor[1] = backColor[1];
//			vWindowColor[2] = backColor[2];
//			vWindowColor[3] = backColor[3];
//
//			if (bHighlight) {
//				if (textOffset) {
//					if (Core::mouse->checkOver(x*Core::gameVars->font.vSize[0],y*Core::gameVars->font.vSize[1],w,h)) {
//						vWindowColor[0] = backHColor[0];
//						vWindowColor[1] = backHColor[1];
//						vWindowColor[2] = backHColor[2];
//						vWindowColor[3] = backHColor[3];
//					}
//				}
//				else {
//					if (Core::mouse->checkOver(x,y,w,h)) {
//						vWindowColor[0] = backHColor[0];
//						vWindowColor[1] = backHColor[1];
//						vWindowColor[2] = backHColor[2];
//						vWindowColor[3] = backHColor[3];
//					}
//				}
//			}


			iconSys->draw(x, y, w, h, id, sTex, textOffset);
		}

		uint checkIcon2(	uint x,
								uint y,
								uint w,		// Character width
								uint h,		// Character Height
								uint id,
								std::string sTex,
								bool bHighlight,
								bool textOffset,
								Core::Color backColor,
								Core::Color backHColor) {
			colors.PushBack(backColor);
			colors.PushBackHighlight(backHColor);
			uint r = checkIcon2(x, y, w, h, id, sTex, bHighlight, textOffset);
			colors.PopBack();
			colors.PopBackHighlight();
			return r;
		}

		uint checkIcon2(	uint x,
								uint y,
								uint w,		// Character width
								uint h,		// Character Height
								uint id,
								std::string sTex,
								bool bHighlight,
								bool textOffset) {

			return checkIcon(	x, y, w*Core::gameVars->font.vSize[0], h*Core::gameVars->font.vSize[1], id, sTex, bHighlight, textOffset);
		}

		uint checkIcon(	uint x,
								uint y,
								float w,
								float h,
								uint id,
								std::string sTex,
								bool bHighlight,
								bool textOffset,
								Core::Color backColor,
								Core::Color backHColor) {

			colors.PushBack(backColor);
			colors.PushBackHighlight(backHColor);
			uint r = checkIcon(x, y, w, h, id, sTex, bHighlight, textOffset);
			colors.PopBack();
			colors.PopBackHighlight();
			return r;
		}

		uint checkIcon(	uint x,
								uint y,
								float w,
								float h,
								uint id,
								std::string sTex,
								bool bHighlight,
								bool textOffset) {
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
			 */

			uint checkClick;

			// TODO: [GameSys] Fix highlight
//			vWindowColor[0] = backColor[0];
//			vWindowColor[1] = backColor[1];
//			vWindowColor[2] = backColor[2];
//			vWindowColor[3] = backColor[3];
//
//			if (bHighlight) {
//				if (textOffset) {
//					if (Core::mouse->checkOver(x*Core::gameVars->font.vSize[0],y*Core::gameVars->font.vSize[1],w,h)) {
//						vWindowColor[0] = backHColor[0];
//						vWindowColor[1] = backHColor[1];
//						vWindowColor[2] = backHColor[2];
//						vWindowColor[3] = backHColor[3];
//					}
//				}
//				else {
//					if (Core::mouse->checkOver(x,y,w,h)) {
//						vWindowColor[0] = backHColor[0];
//						vWindowColor[1] = backHColor[1];
//						vWindowColor[2] = backHColor[2];
//						vWindowColor[3] = backHColor[3];
//					}
//				}
//			}

			iconSys->draw(x, y, w, h, id, sTex, textOffset);

			if (textOffset) checkClick=Core::mouse->checkInput(x*Core::gameVars->font.vSize[0], y*Core::gameVars->font.vSize[1], w, h);
			else checkClick=Core::mouse->checkInput(x, y, w, h);

			return checkClick;
		}

//		void drawCard(	int id0,
//								int id1,
//								int id2,
//								int id3,
//								std::string sTex,
//								SHADER_PROGRAMS iShader=GLS_FONT) {
//			iconSys->draw(id0, id1, id2, id3, sTex, iShader);
//		}


		void drawText(	int x,
								int y,
								std::string buffer,
								Core::Color fontColor,
								int xLimit = 128,
								int yLimit = 128) {
			colors.PushFront(fontColor);
			drawText(x, y, buffer, xLimit, yLimit);
			colors.PopFront();
		}

		void drawText(	int x,
								int y,
								std::string buffer,
								int xLimit = 128,
								int yLimit = 128) {

			//fontColor = Core::gameVars->color.white;

			// TODO: [GameSys] Fix drawText newline handling (See various notes below)
			// ****: Do not continue if length is zero
			if(buffer.length() > 0) {
				if(yLimit > 256) yLimit = 256;

				// ****: Implement xLimit and yLimit
				// xLimit is a limit to the number of characters per line
				// yLimit is a limit to the number of lines
				// The final line should append ... as the final three characters

				// TODO: Split string by newlines
				int iLines = 0;
				int iChars = 0;
				int iTrackLines = 0;						// Actual number of lines
				std::string sWord[256];						// Maximum of 256 lines
				for(int i=0; i<buffer.length(); i++) {
					// ****: Split line according to xLimit
					if(buffer[i] == '\n') {							// Have we encountered a newline?
						iChars = 0;									// Reset the number of characters on this line
						iLines++;									// Increase the line count
						sWord[iLines] = "";							// Set the new line to null
						sWord[iLines] += buffer[i];					// Add the first character for the new line
					}
					else if(iChars >= xLimit) {						// Have we reached the character limit?
						iChars = 0;									// Reset the number of characters on this line
						iLines++;									// Increase the line count
						sWord[iLines] = "";							// Set the new line to null
						sWord[iLines] += buffer[i];					// Add the first character for the new line
					}
					else {											// We haven't reached a newline or limit
						sWord[iLines] += buffer[i];					// Add the character to the line
						iChars++;									// Increase the character count for this line
					}
				}

				// ****: Iterate through each line until
				//				yLimit is reached. Replace final
				//				three characters of line with
				//				... and abort printing remaining
				//
				// ****: Split according to spaces, need to track
				//				number of characters per word or possibly
				//				split the buffer by word then add the
				//				length of each word plus spaces until a
				//				newline or character limit is reached.
				//				If the current word would exceed the
				//				character limit then put it on the next
				//				line.

				// Draw each string on a new line
				bool bBreak = false;
				for(int i=0; i<=iLines; i++) {											// Iterate through ALL lines
					if( i >= (yLimit-1) ) {														// Have we reached the requested limit of lines?
						bBreak = true;																	// Reached limit, set break flag
						int iLength = sWord[i].length();								// Get the current line length
						int iDiff = xLimit - iLength;										// Determine the difference between the line length and requested limit
						if(iDiff > 3) {																	// If the difference is greater than 3 then...
							//sWord[i].append(3, '.');										// Do nothing, this adds extra dots that aren't needed
						}
						else {																					// Otherwise add three dots
							//sWord[i].append(iDiff, '.');								// This causes a segfault, not sure why it was here in the first place.
							int iRem = 3-iDiff;
							if (iRem > 1) {
								for(int j=0; j<iRem; j++) {
									sWord[i][iLength-j] = '.';
								}
							}
							else {
								sWord[i][iLength] = '.';
							}
						}
					}
					textSys->draw(x, y+i, sWord[i]);
					if(bBreak) break;
				}
			}
		}

		/*
		void GameSys::draw3DSprite(		std::string sTex,
										int iShader) {
			spriteSys.draw(sTex, iShader);
		}
		*/

		//void GameSys::drawSprite(		uint x,
		//														uint y,
		//														float s,
		//														std::string sTex,
		//														bool bHighlight=false,
		//														bool textOffset=false,
		//														Core::Vector4f backColor=Core::Vector4f{1.0, 1.0, 1.0, 1.0},
		//														Core::Vector4f backHColor=Core::gameVars->font.vHighlight) {
		//
		//	/*
		//	 * Convert pixel size into a scale size, we may
		//	 *  lose some precision here but it shouldn't
		//	 *  be a big deal for icons.
		//	 */
		//	w=w/64;
		//	h=h/64;
		//
		//	/*
		//	 * If highlighting is enabled
		//	 * Then check if mouse is hovering over icon:
		//	 *    - When textOffset mode is enabled
		//	 *    - When textOffset mode is disabled
		//	 */
		//
		//	uint checkClick;
		//
		//	vWindowColor[0] = backColor[0];
		//	vWindowColor[1] = backColor[1];
		//	vWindowColor[2] = backColor[2];
		//	vWindowColor[3] = backColor[3];
		//
		//	if (bHighlight) {
		//		if (textOffset) {
		//			if (checkOver(x*Core::gameVars->font.vSize[0]+Core::gameVars->font.vHalfSize[0],y*Core::gameVars->font.vSize[1]+Core::gameVars->font.vHalfSize[1],w*64,h*64)) {
		//				vWindowColor[0] = backHColor[0];
		//				vWindowColor[1] = backHColor[1];
		//				vWindowColor[2] = backHColor[2];
		//				vWindowColor[3] = backHColor[3];
		//			}
		//		}
		//		else {
		//			if (checkOver(x,y,w,h)) {
		//				vWindowColor[0] = backHColor[0];
		//				vWindowColor[1] = backHColor[1];
		//				vWindowColor[2] = backHColor[2];
		//				vWindowColor[3] = backHColor[3];
		//			}
		//		}
		//	}
		//
		//	spriteSys.draw(x, y, w, h, sTex, bHighlight, textOffset, vWindowColor);
		//}

		void drawSprite(		uint x,
									uint y,
									float w,
									float h,
									std::string sTex,
									bool bHighlight,
									bool textOffset,
									Core::Color frontColor,
									Core::Color frontHColor) {
			colors.PushFront(frontColor);
			colors.PushFrontHighlight(frontHColor);
			drawSprite(x, y, w, h, sTex, bHighlight, textOffset);
			colors.PopFront();
			colors.PopFrontHighlight();
		}

		void drawSprite(		uint x,
								uint y,
								float w,
								float h,
								std::string sTex,
								bool bHighlight,
								bool textOffset,
								Core::Color frontColor) {
			colors.PushFront(frontColor);
			drawSprite(x, y, w, h, sTex, bHighlight, textOffset);
			colors.PopFront();
		}

		void drawSprite(		uint x,
								uint y,
								float w,
								float h,
								std::string sTex,
								bool bHighlight,
								bool textOffset) {

			/*
			 * Convert pixel size into a scale size, we may
			 *  lose some precision here but it shouldn't
			 *  be a big deal for icons.
			 */
			w=w/64;
			h=h/64;

			/*
			 * If highlighting is enabled
			 * Then check if mouse is hovering over icon:
			 *    - When textOffset mode is enabled
			 *    - When textOffset mode is disabled
			 */

			uint checkClick;

			// TODO: [GameSys] Fix highlight
//			vWindowColor[0] = backColor[0];
//			vWindowColor[1] = backColor[1];
//			vWindowColor[2] = backColor[2];
//			vWindowColor[3] = backColor[3];
//
//			if (bHighlight) {
//				if (textOffset) {
//					if (Core::mouse->checkOver(x*Core::gameVars->font.vSize[0]+Core::gameVars->font.vHalfSize[0],y*Core::gameVars->font.vSize[1]+Core::gameVars->font.vHalfSize[1],w*64,h*64)) {
//						vWindowColor[0] = backHColor[0];
//						vWindowColor[1] = backHColor[1];
//						vWindowColor[2] = backHColor[2];
//						vWindowColor[3] = backHColor[3];
//					}
//				}
//				else {
//					if (Core::mouse->checkOver(x,y,w,h)) {
//						vWindowColor[0] = backHColor[0];
//						vWindowColor[1] = backHColor[1];
//						vWindowColor[2] = backHColor[2];
//						vWindowColor[3] = backHColor[3];
//					}
//				}
//			}

			//Core::spriteSys->draw(x, y, w, h, sTex, textOffset, vWindowColor);
			Core::spriteSys->draw(x, y, w, h, sTex, textOffset);
		}

		uint checkSprite(	uint x,
									uint y,
									float w,
									float h,
									std::string sTex,
									bool bHighlight,
									bool textOffset,
									Core::Color backColor,
									Core::Color backHColor) {
			colors.PushBack(backColor);
			colors.PushBackHighlight(backHColor);
			uint r = checkSprite(x, y, w, h, sTex, bHighlight, textOffset);
			colors.PopBack();
			colors.PopBackHighlight();
			return r;
		}

		uint checkSprite(	uint x,
									uint y,
									float w,
									float h,
									std::string sTex,
									bool bHighlight,
									bool textOffset) {

			/*
			 * Convert pixel size into a scale size, we may
			 *  lose some precision here but it shouldn't
			 *  be a big deal for icons.
			 */
			if(textOffset) {
				w=w/64;
				h=h/64;
			}

			/*
			 * If highlighting is enabled
			 * Then check if mouse is hovering over icon:
			 *    - When textOffset mode is enabled
			 *    - When textOffset mode is disabled
			 */

			uint checkClick;

			// TODO: [GameSys] Fix highlight
//			vWindowColor[0] = backColor[0];
//			vWindowColor[1] = backColor[1];
//			vWindowColor[2] = backColor[2];
//			vWindowColor[3] = backColor[3];
//
//			if (bHighlight) {
//				if (textOffset) {
//					if (Core::mouse->checkOver(x*Core::gameVars->font.vSize[0]+Core::gameVars->font.vHalfSize[0],y*Core::gameVars->font.vSize[1]+Core::gameVars->font.vHalfSize[1],w*64,h*64)) {
//						vWindowColor[0] = backHColor[0];
//						vWindowColor[1] = backHColor[1];
//						vWindowColor[2] = backHColor[2];
//						vWindowColor[3] = backHColor[3];
//					}
//				}
//				else {
//					if (Core::mouse->checkOver(x,y,w,h)) {
//						vWindowColor[0] = backHColor[0];
//						vWindowColor[1] = backHColor[1];
//						vWindowColor[2] = backHColor[2];
//						vWindowColor[3] = backHColor[3];
//					}
//				}
//			}

			Core::spriteSys->draw(x, y, w/64, h/64, sTex, textOffset);

			if (textOffset) checkClick=Core::mouse->checkInput(x*Core::gameVars->font.vSize[0]+Core::gameVars->font.vHalfSize[0], y*Core::gameVars->font.vSize[1]+Core::gameVars->font.vHalfSize[1], w*64, h*64);
			else checkClick=Core::mouse->checkInput(x, y, w, h);

			return checkClick;
		}

//		void drawVariable(	int x,
//									int y,
//									bool bP,
//									Core::Vector4f fontColor) {
//			colors.PushFront(fontColor);
//			textSys->draw(x, y, &bP);
//			colors.PopFront();
//		}
//		void drawVariable(	int x,
//									int y,
//									bool bP) {
//			textSys->draw(x, y, &bP);
//		}
//
//		void drawVariable(	int x,
//									int y,
//									int iP,
//									Core::Vector4f fontColor) {
//			colors.PushFront(fontColor);
//			textSys->draw(x, y, &iP);
//			colors.PopFront();
//		}
//		void drawVariable(	int x,
//									int y,
//									int iP) {
//			textSys->draw(x, y, &iP);
//		}
//
//		void drawVariable(	int x,
//									int y,
//									uint uiP,
//									Core::Vector4f fontColor) {
//			colors.PushFront(fontColor);
//			textSys->draw(x, y, &uiP);
//			colors.PopFront();
//		}
//		void drawVariable(	int x,
//									int y,
//									uint uiP) {
//			textSys->draw(x, y, &uiP);
//		}
//
//		void drawVariable(	int x,
//									int y,
//									float fP,
//									Core::Vector4f fontColor,
//									bool bDec=true) {
//			colors.PushFront(fontColor);
//			textSys->draw(x, y, &fP);
//			colors.PopFront();
//		}
//		void drawVariable(	int x,
//									int y,
//									float fP,
//									bool bDec=true) {
//			textSys->draw(x, y, &fP);
//		}

//		void drawAnimation(	float x,
//										float y,
//										Core::Vector3f camera,
//										Core::Vector3f target,
//										int iA,
//										int loop,
//										__uint16_t rate,
//										bool bMoveOrigin) {
//			GameSys::gameSys.animationSys.startAnimation(x, y, camera, target, iA, loop, rate, nullptr, bMoveOrigin);
//		}
//
//		void playAnimation(	float x,
//										float y,
//										Core::Vector3f camera,
//										Core::Vector3f target,
//										int iA,
//										int loop,
//										__uint16_t rate,
//										int *iSample,
//										bool bMoveOrigin) {
//			GameSys::gameSys.animationSys.startAnimation(x, y, camera, target, iA, loop, rate, iSample, bMoveOrigin);
//		}

		/*
		 * TODO: Create clickable/hoverable variable drawing routines
		 *
		 * See drawTextWindow() and checkText() for possible solution.
		 * We want to give the same standard customization available in
		 * 	other functions with respect to font color and hover color.
		 */
		//uint GameSys::checkText(		int x,																								// Starting position of window
		//														int y,																								// Starting position of window
		//														std::string sText,																		// Text to print in window
		//														bool bHighlight=false,																// Highlight on mouseover?
		//														bool textOffset=true,																	// Absolute or texture grid positioning?
		//														Core::Vector4f frontColor=Core::Vector4f{1.0, 1.0, 1.0, 1.0},			// Text normal color
		//														Core::Vector4f frontHColor=Core::gameVars->font.vHighlight) {			// Text mouseover color
		//
		//	return menuSys.draw(	x,	y,	sText);

		//	if ((checkInput(x, y, buffer.length(), Core::gameVars->font.vSize)==MOUSE_LEFT) && !gettingInput) {
		//		if (*bPtr) *bPtr=false;
		//		else *bPtr=true;
		//		return true;
		//	}
		//	else {
		//		gameSys.textSys.draw(x, y, z, buffer, bPtr, fontColor);
		//		return false;
		//	}

		//	if (textOffset) checkClick=checkInput(x*Core::gameVars->font.vSize[0], y*Core::gameVars->font.vSize[1], w, h);
		//	else checkClick=checkInput(x, y, w, h);

		//uint GameSys::drawTextWindow(	int x,																								// Starting position of window
		//															int y,																								// Starting position of window
		//															int w,																								// Width of window
		//															int h,																								// Height of window
		//															std::string sText,																		// Text to print in window
		//															bool bHighlight=false,																// Highlight on mouseover?
		//															bool textOffset=true,																	// Absolute or texture grid positioning?
		//															Core::Vector4f backColor=Core::Vector4f{1.0, 1.0, 1.0, 1.0},			// Window standard color
		//															Core::Vector4f frontColor=Core::Vector4f{1.0, 1.0, 1.0, 1.0},			// Text normal color
		//															Core::Vector4f backHColor=Core::gameVars->font.vHighlight,				// Window mouseover color
		//															Core::Vector4f frontHColor=Core::gameVars->font.vHighlight,				// Text mouseover color
		//															short int iBorder=GAME::SYSTEM.WINSYS.DRAWMODE.NORMAL) {										// Border only?
		//
		//	uint checkClick = MOUSE_NONE;
		//
		//	vWindowColor[0] = backColor[0];
		//	vWindowColor[1] = backColor[1];
		//	vWindowColor[2] = backColor[2];
		//	vWindowColor[3] = backColor[3];
		//
		//	vTextColor[0] = frontColor[0];
		//	vTextColor[1] = frontColor[1];
		//	vTextColor[2] = frontColor[2];
		//	vTextColor[3] = frontColor[3];
		//
		//	if (bHighlight) {
		//		if (textOffset) {
		//			if (checkOver(x*Core::gameVars->font.vSize[0]+Core::gameVars->font.vHalfSize[0],y*Core::gameVars->font.vSize[1]+Core::gameVars->font.vHalfSize[1], (w-1)*Core::gameVars->font.vSize[0],(h-1)*Core::gameVars->font.vSize[1])) {
		//				vWindowColor[0] = backHColor[0];
		//				vWindowColor[1] = backHColor[1];
		//				vWindowColor[2] = backHColor[2];
		//				vWindowColor[3] = backHColor[3];
		//
		//				vTextColor[0] = frontHColor[0];
		//				vTextColor[1] = frontHColor[1];
		//				vTextColor[2] = frontHColor[2];
		//				vTextColor[3] = frontHColor[3];
		//			}
		//		}
		//		else {
		//			if (checkOver(x,y,w,h)) {
		//				vWindowColor[0] = backHColor[0];
		//				vWindowColor[1] = backHColor[1];
		//				vWindowColor[2] = backHColor[2];
		//				vWindowColor[3] = backHColor[3];
		//
		//				vTextColor[0] = frontHColor[0];
		//				vTextColor[1] = frontHColor[1];
		//				vTextColor[2] = frontHColor[2];
		//				vTextColor[3] = frontHColor[3];
		//			}
		//		}
		//	}
		//
		//	winSys.draw(x, y, w, h, textOffset, vWindowColor, iBorder);
		//	//textSys.draw(x+1, y+1, sText, vTextColor);
		//	drawText(x+1, y+1, sText, vTextColor, 1024, 1024);				// must specify xLimit and yLimit here for some reason
		//
		//	if (textOffset) checkClick=checkInput(x*Core::gameVars->font.vSize[0]+Core::gameVars->font.vHalfSize[0], y*Core::gameVars->font.vSize[1]+Core::gameVars->font.vHalfSize[1], (w-1)*Core::gameVars->font.vSize[0],(h-1)*Core::gameVars->font.vSize[1]);
		//	else checkClick=checkInput(x, y, w, h);
		//
		//	return checkClick;

		//void GameSys::checkVariable(	int x,
		//															int y,
		//															bool bP,
		//															bool bHighlight=false,																// Highlight on mouseover?
		//															Core::Vector4f frontColor=Core::Vector4f{1.0, 1.0, 1.0, 1.0},			// Text normal color
		//															Core::Vector4f frontHColor=Core::gameVars->font.vHighlight) {			// Text mouseover color
		//
		//	uint checkClick = MOUSE_NONE;
		//
		//	vTextColor[0] = frontColor[0];
		//	vTextColor[1] = frontColor[1];
		//	vTextColor[2] = frontColor[2];
		//	vTextColor[3] = frontColor[3];
		//
		//	checkInput(x, y, buffer.length(), Core::gameVars->font.vSize);
		//
		//	if (bHighlight) {
		//		if (checkOver(x*Core::gameVars->font.vSize[0]+Core::gameVars->font.vHalfSize[0],y*Core::gameVars->font.vSize[1]+Core::gameVars->font.vHalfSize[1], (w-1)*Core::gameVars->font.vSize[0],(h-1)*Core::gameVars->font.vSize[1])) {
		//			vTextColor[0] = frontHColor[0];
		//			vTextColor[1] = frontHColor[1];
		//			vTextColor[2] = frontHColor[2];
		//			vTextColor[3] = frontHColor[3];
		//		}
		//	}
		//
		//	winSys.draw(x, y, w, h, textOffset, vWindowColor, iBorder);
		//	//textSys.draw(x+1, y+1, sText, vTextColor);
		//	drawText(x+1, y+1, sText, vTextColor, 1024, 1024);				// must specify xLimit and yLimit here for some reason
		//
		//	if (textOffset) checkClick=checkInput(x*Core::gameVars->font.vSize[0]+Core::gameVars->font.vHalfSize[0], y*Core::gameVars->font.vSize[1]+Core::gameVars->font.vHalfSize[1], (w-1)*Core::gameVars->font.vSize[0],(h-1)*Core::gameVars->font.vSize[1]);
		//	else checkClick=checkInput(x, y, w, h);
		//
		//	return checkClick;
		//
		//	menuSys.draw()
		//
		//	//textSys.draw(x, y, &bP, fontColor);
		//}
		//
		//void GameSys::checkVariable(		int x,
		//																int y,
		//																int iP,
		//																Core::Vector4f fontColor) {
		//	textSys.draw(x, y, &iP, fontColor);
		//}
		//
		//void GameSys::checkVariable(		int x,
		//																int y,
		//																float fP,
		//																Core::Vector4f fontColor,
		//																bool bDec) {
		//	textSys.draw(x, y, &fP, fontColor);
		//}

		/*
		void GameSys::drawVariable(		int x,
										int y,
										bool *bP) {
			textSys.draw(x, y, bP);
		}

		void GameSys::drawVariable(		int x,
										int y,
										bool *bP,
										Core::Vector4f fontColor) {
			textSys.draw(x, y, bP, fontColor);
		}

		void GameSys::drawVariable(		int x,
										int y,
										int *iP,
										Core::Vector4f fontColor) {
			textSys.draw(x, y, iP, fontColor);
		}

		void GameSys::drawVariable(		int x,
										int y,
										float *fP,
										Core::Vector4f fontColor,
										bool bDec) {
			textSys.draw(x, y, fP, fontColor);
		}
		*/

		// TODO: Auto drawVariable routine, this might be difficult to implement.
		//
		//	drawVariable(x, y, n, t1, v1, t2, v2, ... , tn, vn, c)
		//
		//  x: horizontal position
		//  y: vertical position
		//  n: number of arguments not including c
		//  t1: type for argument 1
		//  v1: value for argument 1
		//  t2: type for argument 2
		//  v2: value for argument 2
		//       ...
		//  tn: type for argument n
		//  vn: value for argument n
		//  Core::Vector4f
		//void GameSys::drawVariable(int x, int y, ... ) {
		//	va_list attributeList;
		//	Core::Vector4f fontColor = { 1.0, 1.0, 1.0, 1.0 };
		//	try {
		//		va_start(attributeList, y);
		//		//char *szNextArg;
		//		int iArgCount = va_arg(attributeList, int);		// n
		//		for (int i=0; i < iArgCount; i++) {
		//
		//			int index = va_arg(attributeList, int);		// tn
		//			switch (index) {
		//				case TYPE_BOOL:
		//					//bool *bP = va_arg(attributeList, bool*);	// vn if bool
		//					//textSys.draw(x, y, bP, fontColor);
		//					break;
		//				case TYPE_INT:
		//					//int *iP = va_arg(attributeList, int*);		// vn if int
		//					//textSys.draw(x, y, iP, fontColor);
		//					break;
		//				case TYPE_FLOAT:
		//					//float *fP = va_arg(attributeList, float*);	// vn if float
		//					//textSys.draw(x, y, fP, fontColor);
		//					break;
		//			}
		//		}
		//		va_end(attributeList);
		//		//if (debug) printf("[Done]\n");
		//	}
		//	catch( char * str ) {
		//		//if (debug) printf("[Failed]: %s\n", str);
		//		abort();
		//	}
		//}

		//##################################################################################################
		//##################################################################################################
		//##################################################################################################

	}
}
#endif /* SYSTEM_H_ */
