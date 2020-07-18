/*
 * MenuClass.h
 *
 *  Created on: Mar 6, 2016
 *      Author: bcthund
 */

#ifndef MENUCLASS_H_
#define MENUCLASS_H_

#include <SDL2/SDL.h>
#include "../core/core_functions.h"

namespace Core {
	namespace GameSys {
		class _MenuSys {
			private:
				_TextSys	* textSys;

			protected:
				uint checkInput(int x, int y, int bufferLength, Vector2f fontSize);
				uint checkOver(int x, int y, int bufferLength, Vector2f fontSize);

			public:
				_MenuSys(_TextSys &t);
				bool gettingInput;
				bool isFloat, isInt, isString;
				int *iPtrTemp;
				float *fPtrTemp;
				std::string *sPtrTemp;
				Vector4f v4f_defFontCol;	//Default Font Color
				float fMouseDelay, fMouseDelayConst;	//Delay for repeat mouse clicks
				std::string sBuffer;
				Timer timer;

				uint draw(int x, int y, std::string buffer);
				uint draw(int x, int y, std::string buffer, Color fontColor1);
				uint draw(int x, int y, std::string buffer, Color fontColor1, Color fontColor2);
				//bool draw(int x, int y, std::string buffer, Vector2f fontSize);

				bool draw(int x, int y, int z, std::string buffer, float *fPtr, bool drawDec);
				bool draw(int x, int y, int z, std::string buffer, int *iPtr);
				bool draw(int x, int y, int z, std::string buffer, bool *bPtr);
				bool draw(int x, int y, int z, std::string buffer, std::string *sPtr);

				bool draw(int x, int y, int z, std::string buffer, float *fPtr, Color fontColor, bool drawDec);
				bool draw(int x, int y, int z, std::string buffer, int *iPtr, Color fontColor);
				bool draw(int x, int y, int z, std::string buffer, bool *bPtr, Color fontColor);
				bool draw(int x, int y, int z, std::string buffer, std::string *sPtr, Color fontColor);

				bool draw(int x, int y, int z, std::string buffer, float *fPtr, Color fontColor, Color hlColor, bool drawDec);
				bool draw(int x, int y, int z, std::string buffer, int *iPtr, Color fontColor, Color hlColor);
				bool draw(int x, int y, int z, std::string buffer, bool *bPtr, Color fontColor, Color hlColor);
				bool draw(int x, int y, int z, std::string buffer, std::string *sPtr, Color fontColor, Color hlColor);

		};

		_MenuSys::_MenuSys(_TextSys &t){
			textSys = &t;
			iPtrTemp = nullptr;
			fPtrTemp = nullptr;
			sPtrTemp = nullptr;
			gettingInput = false;
			isFloat = false;
			isInt = false;
			isString = false;
			fMouseDelay=0;
			fMouseDelayConst=100;
			timer.start();
		}

		//##########################
		// Text Only
		// FIXME: [MenuSys] Fix colors to use _Colors() system
		uint _MenuSys::draw(int x, int y, std::string buffer) {
			Color fontColor1 = {0.0, 1.0, 0.0, 1.0};		// Hover color
			Color fontColor2 = {1.0, 1.0, 1.0, 1.0};		// Normal color
			return draw(x, y, buffer, fontColor1, fontColor2);
		}

		uint _MenuSys::draw(int x, int y, std::string buffer, Color fontColor1) {
			Color fontColor2 = {1.0, 1.0, 1.0, 1.0};		// Normal color
			return draw(x, y, buffer, fontColor1, fontColor2);
		}

		uint _MenuSys::draw(int x, int y, std::string buffer, Color fontColor1, Color fontColor2) {
			uint checkHover = checkOver(x, y, buffer.length(), Core::gameVars->font.vSize);
			if (checkHover == Core::mouse->MOUSE_HOVER) {
				textSys->draw(x, y, buffer);	// TODO: Replaced fontcolor setting function
			}
			else {
				textSys->draw(x, y, buffer);	// TODO: Replaced fontcolor setting function
			}

			uint checkClick = checkInput(x, y, buffer.length(), Core::gameVars->font.vSize);
			if (checkClick) return checkClick;
			return checkHover;
		}

		//##########################
		// Pointer Based Variables
		//

		bool _MenuSys::draw(int x, int y, int z, std::string buffer, float *fPtr, Color fontColor, Color hlColor, bool drawDec=true) {
			colors.PushFront(fontColor);
			colors.PushFrontHighlight(hlColor);
			bool bReturn = draw(x, y, z, buffer, fPtr, drawDec);
			colors.PopFront();
			colors.PopFrontHighlight();
			return bReturn;
		}

		bool _MenuSys::draw(int x, int y, int z, std::string buffer, float *fPtr, Color fontColor, bool drawDec=true) {
			colors.PushFront(fontColor);
			bool bReturn = draw(x, y, z, buffer, fPtr, drawDec);
			colors.PopFront();
			return bReturn;
		}

		bool _MenuSys::draw(int x, int y, int z, std::string buffer, float *fPtr, bool drawDec=true) {
			uint uiInput = checkInput(x, y, buffer.length(), Core::gameVars->font.vSize);
			if ((uiInput==Core::mouse->MOUSE_LEFT) && !gettingInput) {
				gettingInput=true;
				isFloat=true;

				std::string fBuffer;
				int intPart = (int)*fPtr;
				uint decPart = ((uint)(*fPtr*10000)%10000);
				fBuffer = itoa(intPart, 10);
				fBuffer += "." + itoa(decPart, 10);
				fPtrTemp=fPtr;

				// Put the value into the buffer so that it can be edited
				sBuffer = fBuffer;
				sBuffer = std::to_string(*fPtr);

//				std::cout << "Mouse Clicked @ (" << Core << ", " <<  << ")" << std::endl;

				return true;
			}
			else {
				// TODO: [MenuSys] Highlight on mouseover (call different draw routine with active highlight color)
//				if(uiInput==Core::mouse->STATE.MOUSE_HOVER) {
//					fontColor = hlColor;
//				}
				buffer += " = "+std::to_string(*fPtr);
				textSys->draw(x, y, buffer);	// TODO: replaced draw *float drawing function
				return false;
			}
		}

		bool _MenuSys::draw(int x, int y, int z, std::string buffer, int *iPtr, Color fontColor, Color hlColor) {
			colors.PushFront(fontColor);
			colors.PushFrontHighlight(hlColor);
			bool bReturn = draw(x, y, z, buffer, iPtr);
			colors.PopFront();
			colors.PopFrontHighlight();
			return bReturn;
		}
		
		bool _MenuSys::draw(int x, int y, int z, std::string buffer, int *iPtr, Color fontColor) {
			colors.PushFront(fontColor);
			bool bReturn = draw(x, y, z, buffer, iPtr);
			colors.PopFront();
			return bReturn;
		}

		bool _MenuSys::draw(int x, int y, int z, std::string buffer, int *iPtr) {
			uint uiInput = checkInput(x, y, buffer.length(), Core::gameVars->font.vSize);
			if ((uiInput==Core::mouse->MOUSE_LEFT) && !gettingInput) {
				gettingInput=true;
				isInt=true;
				iPtrTemp=iPtr;

				// Put the value into the buffer so that it can be edited
				sBuffer = itoa(*iPtr, 10);

				return true;
			}
			else {
				// TODO: [MenuSys] Highlight on mouseover (call different draw routine with active highlight color)
//				if(uiInput==Core::mouse->STATE.MOUSE_HOVER) {
//					fontColor = hlColor;
//				}
				buffer += " = "+std::to_string(*iPtr);
				textSys->draw(x, y, buffer);// TODO: Replaced *int drawing function
				return false;
			}
			return 0;
		}

		bool _MenuSys::draw(int x, int y, int z, std::string buffer, bool *bPtr, Color fontColor, Color hlColor) {
			colors.PushFront(fontColor);
			colors.PushFrontHighlight(hlColor);
			bool bReturn = draw(x, y, z, buffer, bPtr, Core::colors[colors().Green]);
			colors.PopFront();
			colors.PopFrontHighlight();
			return bReturn;
		}
		
		bool _MenuSys::draw(int x, int y, int z, std::string buffer, bool *bPtr, Color fontColor) {
			colors.PushFront(fontColor);
			bool bReturn = draw(x, y, z, buffer, bPtr, fontColor, Core::colors[colors().Green]);
			colors.PopFront();
			return bReturn;
		}
		
		bool _MenuSys::draw(int x, int y, int z, std::string buffer, bool *bPtr) {
			uint uiInput = checkInput(x, y, buffer.length(), Core::gameVars->font.vSize);
			if ((uiInput==Core::mouse->MOUSE_LEFT) && !gettingInput) {
				if (*bPtr) *bPtr=false;
				else *bPtr=true;
				return true;
			}
			else {
				// TODO: [MenuSys] Highlight on mouseover (call different draw routine with active highlight color)
//				if(uiInput==Core::mouse->STATE.MOUSE_HOVER) {
//					fontColor = hlColor;
//				}
				buffer += " = "+std::to_string(*bPtr);
				textSys->draw(x, y, buffer);	// TODO: Replaced *bool drawing function
				return false;
			}
		}

		bool _MenuSys::draw(int x, int y, int z, std::string buffer, std::string *sPtr, Color fontColor, Color hlColor) {
			colors.PushFront(fontColor);
			colors.PushFrontHighlight(hlColor);
			bool bReturn = draw(x, y, z, buffer, sPtr);
			colors.PopFront();
			colors.PopFrontHighlight();
			return bReturn;
		}
		
		bool _MenuSys::draw(int x, int y, int z, std::string buffer, std::string *sPtr, Color fontColor) {
			colors.PushFront(fontColor);
			bool bReturn = draw(x, y, z, buffer, sPtr);
			colors.PopFront();
			return bReturn;
		}

		bool _MenuSys::draw(int x, int y, int z, std::string buffer, std::string *sPtr) {
			uint uiInput = checkInput(x, y, buffer.length(), Core::gameVars->font.vSize);
			if ((uiInput==Core::mouse->MOUSE_LEFT) && !gettingInput) {
				gettingInput=true;
				isString=true;
				sPtrTemp=sPtr;

				// Put the value into the buffer so that it can be edited
				sBuffer = *sPtr;

				return true;
			}
			else {
				// TODO: [MenuSys] Highlight on mouseover (call different draw routine with active highlight color)
//				if(uiInput==Core::mouse->STATE.MOUSE_HOVER) {
//					fontColor = hlColor;
//				}
				textSys->draw(x,   y, buffer);
				textSys->draw(x+z, y, *sPtr);
				return false;
			}
			return 0;
		}
		
		// TODO: Switch to InputSys version of checkInput
		uint _MenuSys::checkInput(int x, int y, int bufferLength, Vector2f fontSize) {
			/*
			if (Core::mouse->button.pressed[0] && !gettingInput) {
				Vector2f vMouse = {  float(Core::mouse->x), float(Core::mouse->y) };
				Vector2f vP1    = {  x*(float)Core::gameVars->font.vSize[0], y*(float)Core::gameVars->font.vSize[1] };
				Vector2f vP2    = { (x*(float)Core::gameVars->font.vSize[0])+((float)Core::gameVars->font.vSize[0]*bufferLength), (y*(float)Core::gameVars->font.vSize[1])+(float)Core::gameVars->font.vSize[1] };

				if (PointQuad2d(vMouse, vP1, vP2)) return Core::mouse->STATE.MOUSE_LEFT;
			}
			return Core::mouse->STATE.MOUSE_NONE;
			*/
			Vector2f vMouse = Vector2f(float(Core::mouse->x), float(Core::mouse->y) );
			Vector2f vP1    = {  x*(float)Core::gameVars->font.vSize[0], y*(float)Core::gameVars->font.vSize[1] };
			Vector2f vP2    = { (x*(float)Core::gameVars->font.vSize[0])+((float)Core::gameVars->font.vSize[0]*bufferLength), (y*(float)Core::gameVars->font.vSize[1])+(float)Core::gameVars->font.vSize[1] };

			if (Core::gmath.PointQuad2d(vMouse, vP1, vP2)) {
				if (Core::mouse->button.pressed[SDL_BUTTON_LEFT]) {

//					std::cout << "Mouse Click Detected:" << std::endl;
//					std::cout << "\tvMouse = (" << vMouse.x << ", " << vMouse.y << ")" << std::endl;
//					std::cout << "\tvP1    = (" << vP1.x << ", " << vP1.y << ")" << std::endl;
//					std::cout << "\tvP2    = (" << vP2.x << ", " << vP2.y << ")" << std::endl << std::endl;

					if (timer.get_ticks()>(fMouseDelay+fMouseDelayConst)) {
						fMouseDelay = timer.get_ticks();
						return Core::mouse->MOUSE_LEFT;
					}
				}
				else {
					return Core::mouse->MOUSE_HOVER;
				}
			}
			return Core::mouse->MOUSE_NONE;
		}

		// TODO: Switch to InputSys version of checkInput
		uint _MenuSys::checkOver(int x, int y, int bufferLength, Vector2f fontSize) {
			Vector2f vMouse = {  float(Core::mouse->x), float(Core::mouse->y) };
			Vector2f vP1    = {  x*(float)Core::gameVars->font.vSize[0], y*(float)Core::gameVars->font.vSize[1] };
			Vector2f vP2    = { (x*(float)Core::gameVars->font.vSize[0])+((float)Core::gameVars->font.vSize[0]*bufferLength), (y*(float)Core::gameVars->font.vSize[1])+(float)Core::gameVars->font.vSize[1] };

			if (Core::gmath.PointQuad2d(vMouse, vP1, vP2)) return Core::mouse->MOUSE_HOVER;
			else return Core::mouse->MOUSE_NONE;
		}

		//uint GameSys::checkInput(int x, int y, float w, float h) {
		//	Vector2f vMouse = { float(Core::mouse->x), float(Core::mouse->y) };
		//	Vector2f vP1    = { (float)x, (float)y };
		//	Vector2f vP2    = { (float)x+w, (float)y+h };
		//
		//	if (Core::mouse->button.pressed[0]) {
		//		if (PointQuad2d(vMouse, vP1, vP2)) {
		//			if (Core::gameVars->timer.frameRate.get_ticks()>(fMouseDelay+fMouseDelayConst)) {
		//				fMouseDelay = Core::gameVars->timer.frameRate.get_ticks();
		//				return Core::mouse->STATE.MOUSE_LEFT;
		//			}
		//		}
		//	}
		//	else if (PointQuad2d(vMouse, vP1, vP2)) {
		//			return Core::mouse->STATE.MOUSE_HOVER;
		//	}
		//	return Core::mouse->STATE.MOUSE_NONE;
		//}

		//uint GameSys::checkOver(int x, int y, float w, float h) {
		//	Vector2f vMouse = { float(Core::mouse->x), float(Core::mouse->y) };
		//	Vector2f vP1    = { (float)x, (float)y };
		//	Vector2f vP2    = { (float)x+w, (float)y+h };
		//
		//	if (PointQuad2d(vMouse, vP1, vP2)) return Core::mouse->STATE.MOUSE_HOVER;
		//	else return Core::mouse->STATE.MOUSE_NONE;
		//}

	}
}


#endif /* MENUCLASS_H_ */
