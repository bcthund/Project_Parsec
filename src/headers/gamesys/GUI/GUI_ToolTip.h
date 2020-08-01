/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_TOOLTIP_H_
#define HEADERS_GAMESYS_GUI_TOOLTIP_H_

#include <iostream>
#include "../../core/timer.h"
#include "../../core/InputSys.h"		// To position based on mouse location
#include "../../core/Colors.h"
#include "../../gamesys/gameVars.h"
#include "../../gamesys/TextSys.h"
#include "GUI_Constraint.h"
#include "GUI_Window.h"
#include "GUI_Text.h"
#include "GUI_Label.h"

namespace Core {
	namespace GUI {
		namespace Object {

			class ToolTip {
				public:
					ToolTip();
					virtual ~ToolTip();
					void init(Props &parent, std::string n);
					void exec();
					void updateObjectState(iState eExternState);
//					int	showDelay;	// ms
//					int hideDelay;	// ms
					iState eObjectState;

				protected:
					Window	win;				// Window object for background
					Text	text;
					Label	*label;
					Timer	timer;
					Props_TextArea *con;
					Props *parent;

					std::string name;
					bool bInit;
			};

			ToolTip::ToolTip() {
				con					= new Props_TextArea();

				label				= nullptr;
				//showDelay			= 500;
				//hideDelay			= 10000;
				eObjectState		= STATE_NONE;
				parent				= nullptr;
				bInit				= false;
			}

			ToolTip::~ToolTip() {
				if(con != nullptr) delete con;
				if(label != nullptr) delete label;
			}

			void ToolTip::init(Props &p, std::string n) {
				//this->id = IDs.create();

				name = n;

				parent = &p;

				// Create button window with contraints to parent if present
				con->setWidth(150, SIZE_CONSTRAINT_ABSOLUTE);
				con->setHeight(50, SIZE_CONSTRAINT_ABSOLUTE);
				con->colorBorder.active = &gameVars->pallette.gui.toolTip.textarea.border;		// TODO: move pallette to constraints with Set functions
				con->colorBack.active = &gameVars->pallette.gui.toolTip.textarea.background;	// TODO: move pallette to constraints with Set functions
				con->setPadding(0);
				con->setBorder(con->toolTip.border, con->toolTip.border);
				con->setRadius(con->toolTip.radius);
				con->setRoundBorder(con->toolTip.round);
				con->text.color.text().active = &gameVars->pallette.gui.toolTip.textarea.text;		// TODO: move pallette to constraints with Set functions
				con->autoWidth();
				con->autoHeight();
				con->showLabel();

				win = Object::Window(name, con);
				win.init();

				// Setup button contraints
				con->setAnchor(CONSTRAIN_BOTTOM_RIGHT);
				con->exec(*win.con);

				con->text.setBuffer(std::make_shared<std::string>(p.toolTip.Text));
				con->text.setAnchor(CONSTRAIN_CENTER);	// DO NOT CHANGE (No effect on multiline text anyway)
				con->text.setOrigin(CONSTRAIN_TOP|CONSTRAIN_LEFT);
				con->text.setWidth(con->size.x, SIZE_CONSTRAINT_ABSOLUTE);
				con->text.setHeight(con->size.y, SIZE_CONSTRAINT_ABSOLUTE);
				con->text.setPos(0, 0);
				con->text.bWordWrap = false;
				con->text.setPadding(con->toolTip.padding);
				con->text.autoWidth();
				con->text.autoHeight();

				text = Text(win, name, &con->text);
				text.init();

				if(con->bShowLabel) {
					label = new Label(*con, name, con->label);
					label->con->colorBorder.active = &gameVars->pallette.gui.toolTip.header.border;
					label->con->colorBack.active = &gameVars->pallette.gui.toolTip.header.background;
					label->con->colorText.active = &gameVars->pallette.gui.toolTip.header.text;
					label->con->showBackground();
					label->con->setBorder(1, 1);
					label->con->setRadius(0);
					label->con->setRoundBorder(false);
					label->con->autoHeight();
					label->con->setStipplePattern(&stipple[stipple.STIPPLE_SHADE_50]);
					label->con->setStippleColorA(&colors[colors().Gray50]);

					label->init();
				}

				bInit = true;
			}

			void ToolTip::updateObjectState(iState eExternState) {
				if((eExternState&STATE_HOVER) && !(eExternState&STATE_DISABLED)) {
					if(!timer.is_started()) {
						timer.start();
					}
					else {
						if (timer.split() >= parent->toolTip.showDelay && timer.split() < parent->toolTip.showDelay+parent->toolTip.hideDelay) {
							eObjectState = STATE_ACTIVE;
						}
						else {
							eObjectState = STATE_NONE;
						}
					}
				}
				else {
					timer.stop();
					eObjectState = STATE_NONE;
				}
			}

			void ToolTip::exec() {
				if(bInit && con->visibility) {
					if(eObjectState&STATE_ACTIVE) {
						if(con->text.size.isAutoSet()) {

							// Update constraints according to quadrants
							Vector2f pos = Vector2f(Core::mouse->x-Core::gameVars->screen.half.x, -Core::mouse->y+Core::gameVars->screen.half.y);
							int iOrigin = CONSTRAIN_CENTER;
							int iAnchor = CONSTRAIN_CENTER;

							if(pos.x>=0) {
								iOrigin = CONSTRAIN_CENTER;
								iAnchor = CONSTRAIN_RIGHT;
								pos.x -= con->toolTip.margin;
							}
							else {
								iOrigin = CONSTRAIN_CENTER;
								iAnchor = CONSTRAIN_LEFT;
								pos.x += con->toolTip.margin;
							}

							if(pos.y>=0) {
								iOrigin |= CONSTRAIN_CENTER;
								iAnchor |= CONSTRAIN_TOP;
								pos.y -= con->toolTip.margin;
								if(con->bShowLabel) pos.y -= label->con->size.y;
							}
							else {
								iOrigin |= CONSTRAIN_CENTER;
								iAnchor |= CONSTRAIN_BOTTOM;
								pos.y += con->toolTip.margin;
							}

							// Follow mouse
							//con->setPos(Core::mouse->x-Core::gameVars->screen.half.x, -Core::mouse->y+Core::gameVars->screen.half.y+2);
							con->setPos(pos);
							con->setOrigin(iOrigin);
							con->setAnchor(iAnchor);
							con->exec();
							win.exec(eObjectState);

							// Update external constraints and draw (tooltip shouldn't have any external modifications)
	//						text.con->setWidth(con->size.x, SIZE_CONSTRAINT_ABSOLUTE);
	//						text.con->setHeight(con->size.y, SIZE_CONSTRAINT_ABSOLUTE);
							text.exec(eObjectState);

							if(con->bShowLabel) label->exec(eObjectState);
						}
						else text.exec(eObjectState);

						// Autosize
						if(con->text.size.constraint.xAuto) {
							int maxX = std::max(con->text.size.x, name.length()*Core::gameVars->font.vSize.x+con->label.vPadding.left+con->label.vPadding.right);
//							con->setWidth(con->text.size.x, SIZE_CONSTRAINT_ABSOLUTE);
//							label->con->setWidth(con->text.size.x, SIZE_CONSTRAINT_ABSOLUTE);
							con->setWidth(maxX, SIZE_CONSTRAINT_ABSOLUTE);
							label->con->setWidth(maxX, SIZE_CONSTRAINT_ABSOLUTE);
						}
						if(con->text.size.constraint.yAuto) {
							con->setHeight(con->text.size.y, SIZE_CONSTRAINT_ABSOLUTE);
						}
					}
				}
			}



		} /* namespace Object */
	} /* namespace GUI */
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_ToolTip_H_ */
