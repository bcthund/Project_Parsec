/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_COMBOBOX_H_
#define HEADERS_GAMESYS_GUI_COMBOBOX_H_

#include <iostream>
#include "../../core/core_functions.h"
#include "../../core/functions.h"
//#include "../../core/vao.h"
//#include "../../core/matrix.h"
//#include "../../core/shader.h"
#include "../../core/InputSys.h"
#include "../../core/Colors.h"
#include "../../gamesys/gameVars.h"
#include "../../gamesys/TextSys.h"
#include "GUI_Constraint.h"
//#include "GUI_ToolTip.h"
#include "GUI_Objects.h"
#include "GUI_Window.h"
#include <variant>

namespace Core {
	namespace GUI {

		using namespace Core::GUI;

		namespace Object {
			class ComboBox : public Base::Interactive<Props_ComboBox> {
				public:
					ComboBox();
					ComboBox(std::string n, Props_ComboBox c);
					ComboBox(std::string n, Props_ComboBox *c);
					ComboBox(Props &p, std::string n, Props_ComboBox c);
					ComboBox(Props &p, std::string n, Props_ComboBox *c);
					virtual ~ComboBox();

					void addItem(std::string title, t_BIFS iValue);
					void addItems(t_ComboBoxItems vItems);
					void removeItem(std::string title);
					void setSelected(std::string name);
					void setSelected(int id);

					t_BIFS getDataSetValue(int n=0);
					t_DataSet &getDataSet(int n);

					Object::Button * selectedItem;
					Window * itemList;
					Object::Button * scrollUp;
					Object::Button * scrollDown;

					Core::t_Vector<Object::Button*> items;
					Object::Button & operator[](std::string name);
					Object::Button & operator()();

					ToolTip toolTip;
					void init();
					void exec(iState eExternState=STATE_NONE);
					void execToolTip();
					void updateNoFocus();

				private:
					//Window		win;
					int			iSelected;
					bool		bSelecting;
					int			iLastValue;
					int			iScrollIndex;
					void updateScrollMouse();
					void updateObjectState(iState eExternState);
					void updateScroll();
			};

			ComboBox::ComboBox() {
				selectedItem	= nullptr;
				itemList		= nullptr;
				iSelected		= 0;
				bSelecting		= false;
				iLastValue		= 0;
				iScrollIndex	= 0;
				scrollUp		= nullptr;
				scrollDown		= nullptr;
			}

			ComboBox::ComboBox(std::string n, Props_ComboBox c) {
				name			= n;
				bInit			= false;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= true;
				con				= new Props_ComboBox();
				*con			= c;
				if(con->text == "") con->text = n;

				bLocalState		= true;
				statePtr		= new bool(false);

				selectedItem	= nullptr;
				itemList		= nullptr;
				iSelected		= 0;
				bSelecting		= false;
				iLastValue		= 0;
				iScrollIndex	= 0;
				scrollUp		= nullptr;
				scrollDown		= nullptr;
			}

			ComboBox::ComboBox(Props &p, std::string n, Props_ComboBox c) {
				name			= n;
				bInit			= false;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= true;
				con				= new Props_ComboBox();
				*con			= c;
				if(con->text == "") con->text = n;

				bLocalState		= true;
				statePtr		= new bool(false);

				selectedItem	= nullptr;
				itemList		= nullptr;
				iSelected		= 0;
				bSelecting		= false;
				iLastValue		= 0;
				iScrollIndex	= 0;
				scrollUp		= nullptr;
				scrollDown		= nullptr;
			}

			ComboBox::ComboBox(std::string n, Props_ComboBox *c) {
				name			= n;
				bInit			= false;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

				bLocalState		= true;
				statePtr		= new bool(false);

				selectedItem	= nullptr;
				itemList		= nullptr;
				iSelected		= 0;
				bSelecting		= false;
				iLastValue		= 0;
				iScrollIndex	= 0;
				scrollUp		= nullptr;
				scrollDown		= nullptr;
			}

			ComboBox::ComboBox(Props &p, std::string n, Props_ComboBox *c) {
				name			= n;
				bInit			= false;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

				bLocalState		= true;
				statePtr		= new bool(false);

				selectedItem	= nullptr;
				itemList		= nullptr;
				iSelected		= 0;
				bSelecting		= false;
				iLastValue		= 0;
				iScrollIndex	= 0;
				scrollUp		= nullptr;
				scrollDown		= nullptr;
			}

			ComboBox::~ComboBox() {
				if(bLocalCon && con != nullptr) delete con;
				if(selectedItem != nullptr) delete selectedItem;
				if(itemList != nullptr) delete itemList;
				for(int n=items.size()-1; n>=0; n--) {
					delete items[n];
				}
			}

			Object::Button & ComboBox::operator[](std::string name)	{
				return *items[name];
			}

			Object::Button & ComboBox::operator()()	{
				return *items[iSelected];
			}

			void ComboBox::setSelected(std::string name) {
				iSelected = items.getID(name);
			}

			void ComboBox::setSelected(int id) {
				iSelected = id;
			}

			void ComboBox::init() {
				if (bHasParent) con->exec(*parent);
				else con->exec();

				selectedItem = new Object::Button(*parent, name+"_Selected", false, con);
				selectedItem->init();

				itemList = new Object::Window(*selectedItem->con, name+"_List", &con->itemList);
				itemList->con->setNoInput(false);
				itemList->con->setWidth(selectedItem->con->size.x, selectedItem->con->size.constraint.xType);
				itemList->con->disableScissor();
				itemList->init();

				// Preliminary setup for items to be added
				con->item.setPos(0, 0);
				con->item.setGroup(Core::groups.add(name+"_ComboBoxItem", true));
				con->item.exec();

				scrollUp = new Object::Button(con->itemList, "Scroll Up", false, con->scroll);
				scrollUp->con->setButtonType(BUTTON_DEBOUNCE);
				scrollUp->con->setText("\x1E");	// Up Arrow
				scrollUp->init();

				scrollDown = new Object::Button(con->itemList, "Scroll Down", false, con->scroll);
				scrollDown->con->setButtonType(BUTTON_DEBOUNCE);
				scrollDown->con->setText("\x1F");	// Down arrow
				scrollDown->init();

				toolTip.init(*con, name);

				bInit = true;
			}

			void ComboBox::addItem(std::string title, t_BIFS iValue) {
				Object::Button * data = new Object::Button(con->itemList, title, false, con->item);		// Creates a NEW copy of button constraints so On/Off values can be kept separate
				data->dataSet.addGroupState(data->sOnState, iValue);
				data->init();

				items.add(title, data);

				// Prep for next item
				con->item.modPos(0, -con->item.size.y);
				con->item.exec();
			}

			void ComboBox::addItems(t_ComboBoxItems vItems) {

				for (auto const& vItem : std::as_const(vItems)) {
					Object::Button * data = new Object::Button(con->itemList, vItem.first, false, con->item);	// Creates a NEW copy of button constraints so On/Off values can be kept separate
					data->dataSet.addGroupState(data->sOnState, vItem.second);
					data->init();

					items.add(vItem.first, data);

					// Prep for next item
					con->item.modPos(0, -con->item.size.y);
					con->item.exec();
				}
			}

			void ComboBox::removeItem(std::string title) {
				items.remove(title);
			}

			/**
			 * \brief Get the custom return states (overridden from Interactive class)
			 * @param n Return state index
			 * @return Value of returnState at index \p n
			 */
			t_BIFS ComboBox::getDataSetValue(int n) {
				// Only ON state is used
				// Make sure selected item even exists, will also detect no items in list
				// Do not fault if items don't exist, simply return a value of 0
				if(iSelected <= items.size()-1) return items[iSelected]->dataSet[sOnState][n];
				else return 0;
			}

			/**
			 * \brief Gets the entire dataset for an object as a reference so it can be modified
			 * @return Return the entire dataset for this object
			 */
			t_DataSet &ComboBox::getDataSet(int n) {
				return items[n]->dataSet;
			}

			void ComboBox::updateObjectState(iState eExternState) {
				// Uncomment if object state can be set externally
				//checkStatePtr();

				// Generic state handler
				if(eExternState!=STATE_NONE && !(eExternState&STATE_UPDATE)) eObjectState = eExternState;
				else {
					if(!(eExternState&STATE_UPDATE)) {
						Vector2f vPos = con->getScrollPos();
						Core::_Mouse::iMouseState test1 = Core::mouse->checkInput(gameVars->screen.half.x+vPos.x, gameVars->screen.half.y-vPos.y, con->size.x, con->size.y);

						vPos = con->itemList.getScrollPos();
						Core::_Mouse::iMouseState test2 = Core::mouse->checkInput(gameVars->screen.half.x+vPos.x, gameVars->screen.half.y-vPos.y, con->itemList.size.x, con->itemList.size.y);
//						mState = Core::_Mouse::iMouseState(test1 | test2);
						mState = test1 | test2;
					}
					else mState = Core::_Mouse::MOUSE_NONE;

					// Object specific logic
					if(enabled()) {
						if(mState&Core::_Mouse::MOUSE_HOVER) {
							updateScrollMouse();
						}
						eObjectState = STATE_NONE;
					}
					else eObjectState = STATE_NONE;
				}

				// Allow mouse hover at any time (used for tooltips)
				if(!(eExternState&STATE_UPDATE)) {
					if(mState&Core::_Mouse::MOUSE_HOVER) eObjectState = eObjectState|STATE_HOVER;
					else eObjectState = eObjectState&~STATE_HOVER;
				}

				// Report if mouse is in button space
				if(!(mState&Core::_Mouse::MOUSE_NONE)) eObjectState = eObjectState|STATE_FOCUS;
				else eObjectState = eObjectState&~STATE_FOCUS;

				if(!enabled()) eObjectState |= STATE_DISABLED;

				// Update the state value according to object state results
				updateStatePtr();
			}

			void ComboBox::updateScrollMouse() {
				Core::_Mouse::MOUSE_STATE wheel = Core::mouse->checkWheel();
				if(wheel != Core::_Mouse::MOUSE_NONE) {
					switch(wheel) {
						case Core::_Mouse::MOUSE_WHEEL_UP:		iScrollIndex -= 1;	break;
						case Core::_Mouse::MOUSE_WHEEL_DOWN:	iScrollIndex += 1;	break;
					}

					iScrollIndex = std::max(iScrollIndex, 0);
					iScrollIndex = std::min(iScrollIndex, items.size()-con->iListLength);
				}
			}

			/**
			 * @brief Update all children according to parent scroll state
			 *
			 */
			void ComboBox::updateScroll() {
				if(parent!=nullptr) {
					con->bEnableScroll = parent->bEnableScroll;
					con->pos.yOffset = parent->pos.yOffset;

					selectedItem->con->bEnableScroll = parent->bEnableScroll;
					selectedItem->con->pos.yOffset = parent->pos.yOffset;

					itemList->con->bEnableScroll = parent->bEnableScroll;
					itemList->con->pos.yOffset = parent->pos.yOffset;

					scrollUp->con->bEnableScroll = parent->bEnableScroll;
					scrollUp->con->pos.yOffset = parent->pos.yOffset;

					scrollDown->con->bEnableScroll = parent->bEnableScroll;
					scrollDown->con->pos.yOffset = parent->pos.yOffset;

					for(int n=0; n<items.size(); n++) {
						items[n]->con->bEnableScroll = parent->bEnableScroll;
						items[n]->con->pos.yOffset = parent->pos.yOffset;
					}
				}
			}

			void ComboBox::exec(iState eExternState) {
				if(bInit && con->visibility && ((parent!=nullptr && parent->visibility) || (parent==nullptr))) {
					if(items.size()>0) {
						updateScroll();

						//if(!Base::Interactive_Base::bFocusPresent) updateObjectState(eExternState);
						updateObjectState(eExternState);

						if(con->toolTip.bShow) toolTip.updateObjectState(eObjectState);
						else toolTip.updateObjectState(STATE_NONE);

						// Update constraints
						if(bHasParent) con->exec(*parent);
						else con->exec();

						// Make sure selected item is active (this is really just visual)
						items[iSelected]->setState(true);

						// Update selected item
//						selectedItem->name = items[iSelected]->name;
						selectedItem->con->text = items[iSelected]->con->text;
						selectedItem->exec(STATE_NONE);

						// Visibility and size
						itemList->con->visibility = selectedItem->getState();

						// Manage itemList visibility
						if(selectedItem->getState() && !bSelecting) bSelecting = true;
						else if(con->bAutoHide && (!(selectedItem->eObjectState&STATE_FOCUS) && !(itemList->eObjectState&STATE_FOCUS)) && bSelecting) {
							selectedItem->setState(false);
							bSelecting = false;
						}
						else if(!con->bAutoHide) {
							if((!(selectedItem->eObjectState&STATE_FOCUS) && !(itemList->eObjectState&STATE_FOCUS)) && bSelecting && Core::mouse->button.held[SDL_BUTTON_LEFT]) {
								selectedItem->setState(false);
								bSelecting = false;
							}
						}

						// Draw itemList and items
						if(bSelecting) {
//							// Detect scroll button status
							int iMem = iScrollIndex;
							if(scrollUp->getState())   { iScrollIndex -= 1; }
							if(scrollDown->getState()) { iScrollIndex += 1; }
							if(iMem != iScrollIndex) {
								// Make sure within limits
								iScrollIndex = std::max(iScrollIndex, 0);
								iScrollIndex = std::min(iScrollIndex, items.size()-con->iListLength);
							}

							// Draw adjusted itemList window
							int iHeight = std::min(items.size(), con->iListLength);
							int iScrollHeight = scrollUp->con->size.y + scrollDown->con->size.y;
							itemList->con->setHeight(iScrollHeight + ((iHeight)*con->item.size.y+itemList->con->vPadding.top_bottom()), SIZE_CONSTRAINT_ABSOLUTE);
							itemList->exec(STATE_NONE);

							// Draw up button
							int xPos = 0,
								yPos = 0;
							scrollUp->setEnabled(iScrollIndex>0);
							scrollUp->con->setPos(xPos, yPos);
							scrollUp->exec(STATE_NONE);
							yPos -= scrollUp->con->size.y;

							// Draw items
							for(int n=0; n<items.size(); n++) {

								int iMaxIndex = iScrollIndex+con->iListLength;
								if(Core::inRange<int>(n, iScrollIndex, iMaxIndex, false, true)) {
									items[n]->con->setPos(xPos, yPos);
									items[n]->exec(STATE_NONE);

									// Prep for next item
									yPos -= con->item.size.y;
								}
								else items[n]->updateNoFocus();

								if(items[n]->getState()) iSelected = n;
							}

							// Draw down button
							scrollDown->setEnabled((iScrollIndex+con->iListLength)<items.size());
							scrollDown->con->setPos(xPos, yPos);
							scrollDown->exec(STATE_NONE);

							// Check if value has changed
							if(iLastValue != iSelected) {
								bStateChanged = true;
							}
							iLastValue = iSelected;
						}

						// Autosize
						if(this->con->size.constraint.xAuto) {
							int lengthBuffer = 0;
							for(auto item : items) lengthBuffer = std::max(lengthBuffer, int(item->con->text.length()));

							// Find out what has larger constraints and use that
							int maxSizeSelected	= int(lengthBuffer*Core::gameVars->font.vSize.x)+(con->vPadding.left+con->vPadding.right);
							int maxSizeList 	= int(lengthBuffer*Core::gameVars->font.vSize.x)+(itemList->con->vPadding.left+itemList->con->vPadding.right)+(con->item.vPadding.left+con->item.vPadding.right);
							int maxSize = std::max(maxSizeSelected, maxSizeList);

							// Set selected item and list width
							con->setWidth(maxSize, SIZE_CONSTRAINT_ABSOLUTE);
							itemList->con->setWidth(maxSize, SIZE_CONSTRAINT_ABSOLUTE);
						}
						if(this->con->size.constraint.yAuto) {
							con->setHeight(Core::gameVars->font.vSize.y+(this->con->vPadding.top+this->con->vPadding.bottom), SIZE_CONSTRAINT_ABSOLUTE);
						}
						//if(this->con->size.constraint.xAuto || this->con->size.constraint.yAuto) this->con->exec();
					}
					else {
						selectedItem->con->text = "No Items Available";
						selectedItem->setState(false);
						selectedItem->exec(STATE_UPDATE);
					}
				}
			}

			void ComboBox::execToolTip() {
				toolTip.exec();
			}

			/***
			 * \brief Calls to run when object not visible/not in focus. This function is especially
			 * 		  important for Buttons because of the call to updateValuePtr();
			 */
			void ComboBox::updateNoFocus() {
				updateObjectState(STATE_UPDATE);
				updateStatePtr();

				scrollUp->updateNoFocus();
				scrollDown->updateNoFocus();
			}















		}
	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_COMBOBOX_H_ */
