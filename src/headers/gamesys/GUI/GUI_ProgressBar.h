/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_PROGRESSBAR_H_
#define HEADERS_GAMESYS_GUI_PROGRESSBAR_H_

#include <iostream>
#include "../../core/Colors.h"
#include "../../gamesys/gameVars.h"
#include "GUI_Constraint.h"
#include "GUI_Window.h"
#include "GUI_Field.h"

namespace Core {
	namespace GUI {
		namespace Object {
			class ProgressBar : public Base::Generic<Props_ProgressBar> {
				public:
					ProgressBar();
					ProgressBar(std::string n, int progress, Props_ProgressBar &c);
					ProgressBar(Props &p, std::string n, int progress, Props_ProgressBar &c);
					ProgressBar(std::string n, int progress, Props_ProgressBar *c);
					ProgressBar(Props &p, std::string n, int progress, Props_ProgressBar *c);

					ProgressBar(std::string n, int *progress, Props_ProgressBar &c);
					ProgressBar(Props &p, std::string n, int *progress, Props_ProgressBar &c);
					ProgressBar(std::string n, int *progress, Props_ProgressBar *c);
					ProgressBar(Props &p, std::string n, int *progress, Props_ProgressBar *c);
					virtual ~ProgressBar();

					ToolTip toolTip;
					void init();
					void exec(iState eExternState=STATE_NONE);
					void execToolTip();
					void setPointer(int *ptr) {
						if(bLocalValue && valuePtr != nullptr) delete valuePtr;
						bLocalValue = false;
						valuePtr = ptr;
						field.setPointer(valuePtr);
					}
					int* getPointer() {	return valuePtr;	}

				private:
					Window		winBack,
								winProgress,
								winNoProgress;
					AnyField	field;
					int		*	valuePtr;
					bool		bLocalValue;
					void updateObjectState(iState eExternState);
			};

			ProgressBar::ProgressBar() {
				bLocalValue		= false;
				valuePtr		= nullptr;
			}

			ProgressBar::ProgressBar(std::string n, int progress, Props_ProgressBar &c) {
				name			= n;
				bInit			= false;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= true;
				con				= new Props_ProgressBar();
				*con			= c;
				if(con->text == "") con->text = n;

				bLocalValue		= true;
				valuePtr		= new int(progress);
			}

			ProgressBar::ProgressBar(Props &p, std::string n, int progress, Props_ProgressBar &c) {
				name			= n;
				bInit			= false;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= true;
				con				= new Props_ProgressBar();
				*con			= c;
				if(con->text == "") con->text = n;

				bLocalValue		= true;
				valuePtr		= new int(progress);
			}

			ProgressBar::ProgressBar(std::string n, int progress, Props_ProgressBar *c) {
				name			= n;
				bInit			= false;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

				bLocalValue		= true;
				valuePtr		= new int(progress);
			}

			ProgressBar::ProgressBar(Props &p, std::string n, int progress, Props_ProgressBar *c) {
				name			= n;
				bInit			= false;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

				bLocalValue		= true;
				valuePtr		= new int(progress);
			}

			ProgressBar::ProgressBar(std::string n, int *progress, Props_ProgressBar &c) {
				name			= n;
				bInit			= false;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= true;
				con				= new Props_ProgressBar();
				*con			= c;
				if(con->text == "") con->text = n;

				bLocalValue		= false;
				valuePtr		= progress;
			}

			ProgressBar::ProgressBar(Props &p, std::string n, int *progress, Props_ProgressBar &c) {
				name			= n;
				bInit			= false;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= true;
				con				= new Props_ProgressBar();
				*con			= c;
				if(con->text == "") con->text = n;

				bLocalValue		= false;
				valuePtr		= progress;
			}

			ProgressBar::ProgressBar(std::string n, int *progress, Props_ProgressBar *c) {
				name			= n;
				bInit			= false;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

				bLocalValue		= false;
				valuePtr		= progress;
			}

			ProgressBar::ProgressBar(Props &p, std::string n, int *progress, Props_ProgressBar *c) {
				name			= n;
				bInit			= false;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

				bLocalValue		= false;
				valuePtr		= progress;
			}

			ProgressBar::~ProgressBar() {
				if(bLocalCon && con != nullptr) delete con;
				if(bLocalValue && valuePtr != nullptr) delete valuePtr;
			}

			void ProgressBar::init() {
				//con->exec();
				if(bHasParent) {
					con->scroll.bind(*parent);
					con->exec(*parent);
				}
				else con->exec();

				// Create button window with contraints to parent if present
				if (bHasParent) winBack = Object::Window(*parent, name, con);
				else winBack = Object::Window(name, con);
				winBack.init();

				// TODO: [Properties] NoProgress: Border, radius, stipple pattern, enable stipple; Progress: border, height(normally 100% relative); Field: show, width

				// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
				// 		Progress Bar Empty
				// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
				{
//					Props_Window props;
//					props.setOrigin(CONSTRAIN_CENTER);
//					props.setAnchor(CONSTRAIN_CENTER);
//					props.setWidth(100, SIZE_CONSTRAINT_RELATIVE);
//					props.setHeight(100, SIZE_CONSTRAINT_RELATIVE);
//					props.setBorder(1, 1);
//					props.setRadius(0);
//					props.setPadding(1);
//					props.enablePadding(Core::GUI::PADDING_ALL);
//					props.disableScissor();
//					props.setStipplePattern(&Core::stipple[Core::stipple.STIPPLE_ANSI31]);
//					props.enableStipple();
//					props.setColorWindowBHA(con->progressColor.empty.base, con->progressColor.empty.base, con->progressColor.empty.base);
//					props.setColorBorderBHA(con->progressColor.border.base, con->progressColor.border.base, con->progressColor.border.base);
//					winNoProgress = Object::Window(*winBack.con, "Progress", props);
					winNoProgress = Object::Window(*winBack.con, "Progress", con->empty);
					winNoProgress.init();
				}

				// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
				// 		Progress Bar
				// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
				{
//					Props_Window props;
//					props.setOrigin(CONSTRAIN_LEFT);
//					props.setAnchor(CONSTRAIN_LEFT);
					con->fill.setWidth(*valuePtr, SIZE_CONSTRAINT_RELATIVE);
//					props.setHeight(100, SIZE_CONSTRAINT_RELATIVE);
//					props.setBorder(0, 0);
//					props.setRadius(0);
//					props.setPadding(0);
//					props.setColorWindowBHA(con->progressColor.fill.base, con->progressColor.fill.base, con->progressColor.fill.base);
//					winProgress = Object::Window(*winNoProgress.con, "NoProgress", props);
					winProgress = Object::Window(*winNoProgress.con, "NoProgress", con->fill);
					winProgress.init();
				}

				// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
				// 		Progress Bar
				// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
				{
//					Props_Field props;
//					props.setOrigin(CONSTRAIN_CENTER);
//					props.setAnchor(CONSTRAIN_CENTER);
//					props.autoWidth();
//					props.autoHeight();
//					props.setPadding(5);
//					props.setMinWidth(3*Core::gameVars->font.vSize.x+5+5);
					field = Object::AnyField();
					field.set(*winNoProgress.con, "Progress Field", valuePtr, con->field);
					field.init();
				}

				toolTip.init(*con, name);

				bInit = true;
			}

			void ProgressBar::updateObjectState(iState eExternState) {
				if(!(eExternState&STATE_UPDATE)) {
					Vector2f vPos = con->getScrollPos();
					mState = Core::mouse->checkInput(gameVars->screen.half.x+vPos.x, gameVars->screen.half.y-vPos.y, con->size.x, con->size.y);
					//mState = Core::mouse->checkInput(gameVars->screen.half.x+con->pos.x, gameVars->screen.half.y-con->pos.y, con->size.x, con->size.y);
				}
				else this->mState = Core::_Mouse::MOUSE_NONE;

				if(eExternState!=STATE_NONE && !(eExternState&STATE_UPDATE)) eObjectState = eExternState;
				else if (mState&Core::_Mouse::MOUSE_HOVER) eObjectState = STATE_HOVER;
				else eObjectState = STATE_NONE;

				if(!enabled()) eObjectState |= STATE_DISABLED;
			}

			void ProgressBar::exec(iState eExternState) {
				if(bInit && con->visibility && ((parent!=nullptr && parent->visibility) || (parent==nullptr))) {
					updateObjectState(eExternState);
					if(con->toolTip.bShow) toolTip.updateObjectState(eObjectState);
					else toolTip.updateObjectState(STATE_NONE);

					// Update constraints
					if(bHasParent) con->exec(*parent);
					else con->exec();

					winProgress.con->setWidth(*valuePtr, SIZE_CONSTRAINT_RELATIVE);

					winBack.exec(eObjectState);
					winNoProgress.exec(eObjectState);
					winProgress.exec(eObjectState);
					field.exec(eObjectState);
				}
			}

			void ProgressBar::execToolTip() {
				toolTip.exec();
			}




		}
	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_PROGRESSBAR_H_ */
