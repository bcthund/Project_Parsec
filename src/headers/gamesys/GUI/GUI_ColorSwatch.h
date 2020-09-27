/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_COLOR_H_
#define HEADERS_GAMESYS_GUI_COLOR_H_

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
#include "../../core/Stipple.h"
#include "GUI_Constraint.h"
#include "GUI_ToolTip.h"
#include "GUI_Slider.h"
#include "GUI_Label.h"
#include "GUI_Window.h"

// FIXME: Center constraints according to sliders if they are enabled instead of on swatch.

namespace Core {
	namespace GUI {
		namespace Object {
			class ColorSwatch : public Base::Generic<Props_ColorSwatch> {
				public:
					ColorSwatch();
					ColorSwatch(std::string n, Color * ptr, Props_ColorSwatch &c);
					ColorSwatch(Props &p, std::string n, Color * ptr, Props_ColorSwatch &c);
					ColorSwatch(std::string n, Color * ptr, Props_ColorSwatch *c);
					ColorSwatch(Props &p, std::string n, Color * ptr, Props_ColorSwatch *c);
					virtual ~ColorSwatch();

					ToolTip toolTip;
					void init();
					void exec(iState eExternState=STATE_NONE);
					void execToolTip();

				protected:
					Color			* colorPtr;
					Slider<float>	* sliderR;
					Slider<float>	* sliderG;
					Slider<float>	* sliderB;
					Slider<float>	* sliderA;
					Label			* label;
					Window			* background;
					Window			swatch;
					void updateObjectState(iState eExternState);
			};

			ColorSwatch::ColorSwatch() {
				colorPtr		= nullptr;
				sliderR			= nullptr;
				sliderG			= nullptr;
				sliderB			= nullptr;
				sliderA			= nullptr;
				label			= nullptr;
				background		= nullptr;
			}

			ColorSwatch::ColorSwatch(std::string n, Color * ptr, Props_ColorSwatch &c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= true;
				con				= new Props_ColorSwatch();
				*con			= c;
				if(con->text == "") con->text = n;

				colorPtr		= ptr;
				sliderR			= nullptr;
				sliderG			= nullptr;
				sliderB			= nullptr;
				sliderA			= nullptr;
				label			= nullptr;
				background		= nullptr;
			}

			ColorSwatch::ColorSwatch(Props &p, std::string n, Color * ptr, Props_ColorSwatch &c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= true;
				con				= new Props_ColorSwatch();
				*con			= c;
				if(con->text == "") con->text = n;

				colorPtr		= ptr;
				sliderR			= nullptr;
				sliderG			= nullptr;
				sliderB			= nullptr;
				sliderA			= nullptr;
				label			= nullptr;
				background		= nullptr;
			}

			ColorSwatch::ColorSwatch(std::string n, Color * ptr, Props_ColorSwatch *c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

				colorPtr		= ptr;
				sliderR			= nullptr;
				sliderG			= nullptr;
				sliderB			= nullptr;
				sliderA			= nullptr;
				label			= nullptr;
				background		= nullptr;
			}

			ColorSwatch::ColorSwatch(Props &p, std::string n, Color * ptr, Props_ColorSwatch *c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

				colorPtr		= ptr;
				sliderR			= nullptr;
				sliderG			= nullptr;
				sliderB			= nullptr;
				sliderA			= nullptr;
				label			= nullptr;
				background		= nullptr;
			}


			ColorSwatch::~ColorSwatch() {
				if(bInit && con->bShowSlider) {
					delete sliderR;
					delete sliderG;
					delete sliderB;
					delete sliderA;
				}
				if(bLocalCon && con != nullptr) delete con;
				if(label!=nullptr) delete label;
				if(background!=nullptr) delete background;
			}

			void ColorSwatch::init() {
				this->id = IDs.create();

				if(bHasParent) con->exec(*parent);
				else con->exec();

				if(bHasParent) swatch = Window(*parent, name, con);
				else swatch = Window(name, con);
				swatch.con->colorBack.base = colorPtr;
				swatch.con->colorBack.highlight = colorPtr;
				swatch.init();

				if(con->bShowBackground) {
					con->background.setWidth(100, SIZE_CONSTRAINT_RELATIVE);
					con->background.setHeight(100, SIZE_CONSTRAINT_RELATIVE);
//					con->background.setBorder(con->border, con->roundBorder);
					con->background.setBorder(con->borderNormal, con->borderHover);
					con->background.setRadius(con->radius);
					con->background.disablePadding();
					con->background.enableStipple();
					con->background.setStipplePattern(&Core::stipple[Core::stipple.STIPPLE_CHECKERBOARD]);

					background = new Window(*con, name, &con->background);
					background->init();
				}

				if(con->bShowSlider) {
					float div = con->size.y/4.0f;
					int sliderHeight = div-3;
					int sliderSpacing = (div-1)/2.0f;

					con->slider.control.setHeight(sliderHeight, SIZE_CONSTRAINT_ABSOLUTE);

					con->slider.setY(sliderSpacing*3);
					sliderR = new Slider<float>(*con, "R", &colorPtr->r, con->slider);
					con->slider.setY(sliderSpacing);
					sliderG = new Slider<float>(*con, "G", &colorPtr->g, con->slider);
					con->slider.setY(-sliderSpacing);
					sliderB = new Slider<float>(*con, "B", &colorPtr->b, con->slider);
					con->slider.setY(-(sliderSpacing*3));
					sliderA = new Slider<float>(*con, "A", &colorPtr->a, con->slider);

					sliderR->init();
					sliderG->init();
					sliderB->init();
					sliderA->init();
				}

				if(con->bShowLabel) {
					label = new Label(*con, name, &con->label);
					label->init();
				}

				toolTip.init(*con, name);

				bInit = true;
			}

			void ColorSwatch::updateObjectState(iState eExternState) {

				if(!(eExternState&STATE_NONE) && !(eExternState&STATE_UPDATE)) {
					mState = Core::mouse->checkInput(gameVars->screen.activeProjection->half.x+con->pos.x, gameVars->screen.activeProjection->half.y-con->pos.y, con->size.x, con->size.y);
				}
				else this->mState = Core::_Mouse::MOUSE_NONE;

				if((eExternState!=STATE_NONE) && !(eExternState&STATE_UPDATE)) {
					eObjectState = eExternState;
				}
				else if (mState&Core::_Mouse::MOUSE_HOVER) {
					eObjectState = STATE_HOVER;
				}
				else eObjectState = STATE_NONE;
				if(!enabled()) eObjectState |= STATE_DISABLED;
			}

			void ColorSwatch::exec(iState eExternState) {
				if(bInit && con->visibility && ((parent!=nullptr && parent->visibility) || (parent==nullptr))) {
					// Update constaints in case they have changed
					if(bHasParent) con->exec(*parent);
					else con->exec();

					updateObjectState(eExternState);

					if(con->toolTip.bShow) toolTip.updateObjectState(eObjectState);
					else toolTip.updateObjectState(STATE_NONE);

					// TODO: Add to pallette? Or to constraints? Also look at mouse pressed (doesn't exist in states currently)
//					if(eObjectState&STATE_HOVER) {
////						con->setBorder(1);
//						swatch.border = con->borderHover;
//					}
//					else {
////						con->setBorder(0);
//						swatch.border = con->borderNormal;
//					}

					// Draw background first if enabled
					if(con->bShowBackground) background->exec();

					// Draw color swatch
					swatch.exec(eObjectState&STATE_HOVER);
//					swatch.exec();

					if(con->bShowSlider) {
						if(eObjectState&STATE_DISABLED) {
							sliderR->exec(STATE_DISABLED);
							sliderG->exec(STATE_DISABLED);
							sliderB->exec(STATE_DISABLED);
							sliderA->exec(STATE_DISABLED);
						}
						else {
							sliderR->exec();
							sliderG->exec();
							sliderB->exec();
							sliderA->exec();
						}
					}

					if(con->bShowLabel) label->exec();
				}
			}

			// TODO: Add to all objects with nested objects
			void ColorSwatch::execToolTip() {
				toolTip.exec();
				if(con->bShowSlider) {
					sliderR->execToolTip();
					sliderG->execToolTip();
					sliderB->execToolTip();
					sliderA->execToolTip();
				}
			}
		}
	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_COLOR_H_ */
