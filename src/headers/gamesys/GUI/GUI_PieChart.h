/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_PIECHART_H_
#define HEADERS_GAMESYS_GUI_PIECHART_H_

#include <iostream>
#include "../../core/core_functions.h"
#include "../../core/vao.h"
#include "../../core/matrix.h"
#include "../../core/shader.h"
#include "../../gamesys/gameVars.h"
#include "../../core/Colors.h"
#include "GUI_Constraint.h"
//#include "GUI_ToolTip.h"
#include "GUI_Objects.h"

// TODO: Allow pie to have an arbitrary size instead of just 100%
//			- Item sizes are translated into 1% slices for drawing

namespace Core {
	namespace GUI {
		namespace Object {

			class t_PieItem {
				friend class PieChart;
				private:
					std::string label;
					int *value;
					bool bLocal;
					Color *color;

				public:
					t_PieItem() {
						label = "Undefined";
						value = new int(0);
						bLocal = true;

						// TODO: Randomize default colors?
//						int iLastColor = colors.colors.size() - 2;	// Last color by default is transparent, skip that one (user added colors will break this)
//						int iColor = std::rand() % iLastColor;
						//std::srand(std::time(0));
						//std::srand(1024);
						int iColor = std::rand() % (colors.colors.size()-2);
//						std::random_device r;
//						std::default_random_engine e1(r());
//						std::uniform_int_distribution<int>(0,colors.colors.size()-2);
//						int iColor =
						//color = &colors[colors().Green];
						color = &colors[iColor];
					}

					t_PieItem(std::string l, int iValue, Color &c) {
						this->label = l;
						this->value = new int(iValue);
						this->bLocal = true;
						this->color = &c;
					}

					t_PieItem(std::string l, int *iValue, Color &c) {
						this->label = l;
						this->value = iValue;
						this->bLocal = false;
						this->color = &c;
					}

					~t_PieItem(){
						if(bLocal && value!=nullptr) delete value;
					}

					void setValuePtr(int *ptr) {
						if(bLocal) delete value;
						bLocal = false;
						value = ptr;
					}

					void setLabel(std::string l)		{	label = l;	}
					void setValue(int n)				{	*value = n;		}
					void setColor(Color &c)				{	color = &c;		}
					int getValue()						{	return *value;	}
					int & getValuePtr()					{	return *value;	}
			};

			class PieChart : virtual public Base::Generic<Props_PieChart> {
				public:
					PieChart();
					PieChart(std::string n, Props_PieChart &c);
					PieChart(std::string n, Props_PieChart *c);
					PieChart(Props &p,std::string n, Props_PieChart &c);
					PieChart(Props &p,std::string n, Props_PieChart *c);
					~PieChart();

					ToolTip toolTip;
					void init();
					void update();
					void exec(iState eExternState=STATE_NONE);
					void execToolTip();
					void addItem(std::string label, int iValue);
					void addItem(std::string label, int iValue, Color &color);
					void addItem(std::string label, int *iValue);
					void addItem(std::string label, int *iValue, Color &color);
					void removeItem(std::string label);
					t_PieItem& getItem(std::string label);

				protected:
					VAO vao;
					Core::t_VectorMap<t_PieItem*> items;

					void updateObjectState(iState eExternState);
					void updateScrollMouse();
			};

			PieChart::PieChart() {  }

			PieChart::PieChart(std::string n, Props_PieChart &c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= true;
				con				= new Props_PieChart();
				*con			= c;
				if(con->text == "") con->text = n;
			}

			PieChart::PieChart(std::string n, Props_PieChart *c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;
			}

			PieChart::PieChart(Props &p, std::string n, Props_PieChart &c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= true;
				con				= new Props_PieChart();
				*con			= c;
				if(con->text == "") con->text = n;
			}

			PieChart::PieChart(Props &p, std::string n, Props_PieChart *c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;
			}

			PieChart::~PieChart() {
				if(bLocalCon && con != nullptr) delete con;
			}

			void PieChart::init() {
				std::srand((unsigned) time(0));

				this->id = IDs.create();

				if(bHasParent) {
					if(!con->scroll.getEnabled() && con->scroll.isScrollable()) con->scroll.bind(*parent);
					con->exec(*parent);
				}
				else {
					con->exec();
				}

				// TODO: use largest of width/height for actual radius. Set smaller to larger value for proper border drawing
				int iMaxRadius = std::max(con->size.x, con->size.y);
				con->setWidth(iMaxRadius);
				con->setHeight(iMaxRadius);

				// TODO: set border radius width/height divided by 2
				con->setRadius(iMaxRadius/2);

				float fRadius = 1.0f;;
				float fR = Degrees(1.8).toRadians();
				float fX = std::sin(fR) * fRadius;
				float fY = std::cos(fR) * fRadius;
				Data3f vVerts[] = { { 0.0f, 0.0f, 0},
									{   fX,  fY, 0},
									{  -fX,  fY, 0} };

				Data2f vTexture[3] = { { 0.5f, 0.0f },
									   { 1.0f, 1.0f },
									   { 0.0f, 1.0f } };

				vao.Begin(GL_TRIANGLES, 3, 3, 1);
				vao.CopyData(GLA_VERTEX, vVerts);
				vao.CopyData(GLA_TEXTURE, vTexture, 0);
				vao.End();

				addItem("Test 1", 10);	// 10 %
				addItem("Test 2", 35);	// 45 %
				addItem("Test 3", 48);	// 83 %

				toolTip.init(*con, name);

//				timeFocusDebounce.start();
				bInit = true;
			}

			/**
			 * @brief Add an item to the list with \p title and \p iValue
			 * @param title Name of item
			 * @param iValue Value of item
			 */
			void PieChart::addItem(std::string label, int iValue) {
				t_PieItem * newData = new t_PieItem();
				newData->setLabel(label);
				newData->setValue(iValue);
				items.add(label, newData);
			}

			/**
			 * @brief Add an item to the list with \p title and \p iValue
			 * @param title Name of item
			 * @param iValue Value of item
			 */
			void PieChart::addItem(std::string label, int iValue, Color &color) {
				t_PieItem * newData = new t_PieItem();
				newData->setLabel(label);
				newData->setValue(iValue);
				newData->setColor(color);
				items.add(label, newData);
			}

			/**
			 * @brief Add an item to the list with \p title and \p iValue
			 * @param title Name of item
			 * @param iValue Value of item
			 */
//			void PieChart::addItem(std::string label, int *iValue, Color &color) {
//				Object::Button * data = new Object::Button(con->itemList, title, false, con->itemButton);
//				data->con->setText(title);
//				data->init();
//
//				items.add(title, data);
//
//				// Prep for next item
//				con->itemButton.modPos(0, -con->itemButton.size.y);
//				con->itemButton.exec();
//			}

			/**
			 * @brief Add a list of items all at once
			 * @param vItems Vector of <title, value> pairs to set
			 */
//			void ComboBox::addItems(t_ComboBoxItems vItems) {
//				for (auto const& vItem : std::as_const(vItems)) {
//					addItem(vItem.first, vItem.second);
//				}
//			}

			/**
			 * @brief Remove an item defined by \p title from list
			 * @param title Name of item to remove
			 */
			void PieChart::removeItem(std::string label) {
				items.remove(label);
			}

			t_PieItem& PieChart::getItem(std::string label) {
				return *items[label];
			}

			void PieChart::update() {
//				if (con->bResizeRadius) {
//					int iRadius = fmin(fmin(con->radius, con->size.x/2.0f), con->size.y/2.0f);
//					con->setRadius(iRadius);
//				}
			}

////			void PieChart::updateObjectState(iState eExternState) {
////				// Default - ALWAYS do this
////				if(eExternState!=STATE_NONE && !(eExternState&STATE_UPDATE)) eObjectState = eExternState;
////				else eObjectState = STATE_NONE;
////
////				mState = Core::mouse->checkInput(gameVars->screen.half.x+con->pos.x, gameVars->screen.half.y-con->pos.y, con->size.x, con->size.y);
////				// Report if mouse is in button space (debounce turning off)
////				if(mState!=Core::_Mouse::MOUSE_NONE) { eObjectState = eObjectState|STATE_FOCUS; timeFocusDebounce.split(); }
////				else if (timeFocusDebounce.get_splitdiff() > iFocusDebounce) eObjectState = eObjectState&~STATE_FOCUS;
////
////				// TODO: Manage mouse scrolling
////				// TODO: Scrolling adjusts iScrollIndex but does nothing here
////				// TODO: iScrollIndex is used by children using this as parent to offset their position
////				// TODO: Children should automatically adjust position based on parent data
////				// TODO: By default window scrolling is disabled because windows are used by so many objects as a base
////				// TODO: Make sure scissor does not move (it shouldn't but be sure)
////
////				if(!enabled()) eObjectState |= STATE_DISABLED;
////			}

			void PieChart::updateObjectState(iState eExternState) {
//				// Uncomment if object state can be set externally
//				//checkStatePtr();
//
//				// Generic state handler
//				if((eExternState!=STATE_NONE) && !(eExternState&STATE_UPDATE)) {
//					eObjectState = eExternState;
//				}
//				else {
//					if(!(eExternState&STATE_UPDATE)) {
//						if(parent!=nullptr && parent->scroll.getEnabled()) {
//							Vector2f vPos = con->getScrollPos();
//							mState = Core::mouse->checkInput(gameVars->screen.half.x+vPos.x, gameVars->screen.half.y-vPos.y, con->size.x, con->size.y);
//						}
//						else {
//							mState = Core::mouse->checkInput(gameVars->screen.half.x+con->pos.x, gameVars->screen.half.y-con->pos.y, con->size.x, con->size.y);
//						}
//					}
//					else mState = Core::_Mouse::MOUSE_NONE;
//
////					// Object specific logic
//					if(enabled()) {
//						if(con->scroll.isScrollable() && (mState&Core::_Mouse::MOUSE_HOVER)) {
//							updateScrollMouse();
//						}
//						eObjectState = STATE_NONE;
//					}
//					else {
//						eObjectState = STATE_NONE;
//					}
//				}
//
//				// Report if mouse is in button space
//				if(!(mState&Core::_Mouse::MOUSE_NONE)) eObjectState = eObjectState|STATE_FOCUS;
//				else eObjectState = eObjectState&~STATE_FOCUS;
//
//				if(!enabled()) eObjectState |= STATE_DISABLED;
//
//				// Update the state value according to object state results
//				//updateStatePtr();
			}

			void PieChart::updateScrollMouse() {
//				if(parent!=nullptr && parent->scroll.getEnabled()) {
//				}
//				else {
//					if(con->scroll.getEnabled() && !bFocusPresent && !bScrollFocus) {
//						Core::_Mouse::MOUSE_STATE wheel = Core::mouse->checkWheel();
//						if(wheel != Core::_Mouse::MOUSE_NONE) {
//
//							int modVal = 50;
//
//							const Uint8 *keyState = SDL_GetKeyboardState(NULL);
//							if (keyState[SDL_SCANCODE_LSHIFT] || keyState[SDL_SCANCODE_RSHIFT])		modVal = 100;
//							else if (keyState[SDL_SCANCODE_LCTRL] || keyState[SDL_SCANCODE_RCTRL])	modVal = 1;
//
//							switch(wheel) {
//								case Core::_Mouse::MOUSE_WHEEL_UP:		iScrollIndex -= modVal;	break;
//								case Core::_Mouse::MOUSE_WHEEL_DOWN:	iScrollIndex += modVal;	break;
//							}
//
//							iScrollIndex = std::max(iScrollIndex, 0);
//							iScrollIndex = std::min(iScrollIndex, activeContainer->scroll.iMaxScroll);
//						}
//					}
//					else if(!con->scroll.getEnabled()) {
//						iScrollIndex = 0;
//					}
//
//					con->scroll.getYRef() = iScrollIndex;
//					con->scroll.getXRef() = 0;
//				}
			}

			void PieChart::exec(iState eExternState) {
				if(bInit) {
					if(con->visibility && ((parent!=nullptr && parent->visibility) || (parent==nullptr))) {


						// Update constaints in case they have changed
						if(bHasParent) con->exec(*parent);
						else con->exec();

//						update();

						glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
						glDisable(GL_DEPTH_TEST);
						glDisable(GL_CULL_FACE);

						matrix->SetProjection(matrix->MM_ORTHO);
						shader->use(GLS_MENU);
//						Core::sysTex->set(Core::sysTex->TEX_TESTPATTERN);

						//if(!bFocusPresent) updateObjectState(eExternState);
//						updateObjectState(eExternState);

						// Allow update only if No object active or this object active
						if((con->bFocusLock && !bFocusPresent) || !con->bFocusLock || (sActiveObject==id)) {
							updateObjectState(eExternState);

							if(this->con->toolTip.bShow) this->toolTip.updateObjectState(this->eObjectState);
							else this->toolTip.updateObjectState(STATE_NONE);
						}



//						if(eObjectState&STATE_DISABLED) {
//							if(eObjectState&STATE_HOVER) {
//								colors.PushFront(gameVars->pallette.gui.disabled.base.hover);
//								colors.PushBack(gameVars->pallette.gui.disabled.border.hover);
//							}
//							else {
//								colors.PushFront(gameVars->pallette.gui.disabled.base.base);
//								colors.PushBack(gameVars->pallette.gui.disabled.border.base);
//							}
//						}
//						else if(eObjectState&STATE_ACTIVE) {
//							colors.PushFront(*con->colorBack.active);
//							colors.PushBack(*con->colorBorder.active);
//						}
//						else if(eObjectState&STATE_HOVER) {
//							colors.PushFront(*con->colorBack.highlight);
//							colors.PushBack(*con->colorBorder.highlight);
//						}
//						else {
//							colors.PushFront(*con->colorBack.base);
//							colors.PushBack(*con->colorBorder.base);
//						}
//						colors.PushFront(colors[colors().Green]);
						colors.PushBack(colors[colors().Black]);

						// Enable border hover
						if(eObjectState&STATE_HOVER) border = con->borderHover;
						else border = con->borderNormal;

						matrix->Push();

							// Only scroll this item if the parent has scrolling enabled
							Vector2f vSize = con->getSize()/2.0f;
							Vector2f vPos = con->getPos();
							matrix->Translate( vPos.x, vPos.y, 0.0 );
							matrix->Scale(vSize.x, vSize.y, 1);

							shader->data.GLS_MENU.vPos				= vPos;
							shader->data.GLS_MENU.vSize				= con->getSize();
							shader->data.GLS_MENU.iRadius			= con->getRadius();
							shader->data.GLS_MENU.iBorder			= border;
							shader->data.GLS_MENU.bRoundBorder		= con->getRoundBorder();
							shader->data.GLS_MENU.bEnableStipple	= con->bEnableStipple;
							if(con->bEnableStipple) {
								shader->data.GLS_MENU.stipple = con->stipple;

								if(eObjectState&STATE_DISABLED) {
									if(eObjectState&STATE_HOVER)	shader->data.GLS_MENU.stippleColor = &gameVars->pallette.gui.disabled.stipple.hover;
									else							shader->data.GLS_MENU.stippleColor = &gameVars->pallette.gui.disabled.stipple.base;
								}
								else if(eObjectState&STATE_ACTIVE) shader->data.GLS_MENU.stippleColor = con->stippleColor.active;
								else if(eObjectState&STATE_HOVER) shader->data.GLS_MENU.stippleColor = con->stippleColor.highlight;
								else shader->data.GLS_MENU.stippleColor = con->stippleColor.base;
							}

							int index = 0;	// Current item index
							int pre = 0;	// Total from previous item
							for(int n=0; n<100; n++) {
								// Make sure item exists
								if(index<items.size()) {
									colors.PushFront(items[index]->color);

									if(n >= (pre+items[index]->getValue())) {
										pre += items[index]->getValue();
										index++;
									}
								}
								else {
									// Undefined Area, fill remaining space
									colors.PushFront(colors[colors().Gray50]);
								}

								matrix->SetTransform();
								shader->getUniform(GLS_MENU);
								vao.Draw();
								matrix->Rotate(Degrees(3.6).toRadians(), 0, 0, -1);
								colors.PopFront();
							}

//							for(int n=0; n<100; n++) {
//								matrix->SetTransform();
//								shader->getUniform(GLS_MENU);
//								vao.Draw();
//								matrix->Rotate(Degrees(3.6).toRadians(), 0, 0, -1);
//								colors.GetFrontPtr().r += 0.01f;
//								colors.GetFrontPtr().b -= 0.01f;
//							}
						matrix->Pop();
						matrix->SetProjection(matrix->MM_PERSPECTIVE);
						colors.PopBack();
						glEnable(GL_CULL_FACE);
						glEnable(GL_DEPTH_TEST);
					}
				}
			}

			/**
			 * @brief Draw tooltip
			 */
			void PieChart::execToolTip() {
				toolTip.exec();
			}

			/***
			 * \brief Calls to run when object not visible/not in focus. This function is especially
			 * 		  important for Buttons because of the call to updateValuePtr();
			 */
//			void PieChart::updateNoFocus() {
//				updateObjectState(STATE_UPDATE);
//				updateStatePtr();
//
//				scrollUp->updateNoFocus();
//				scrollDown->updateNoFocus();
//			}

















		} /* namespace Object */
	} /* namespace GUI */
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_PIECHART_H_ */
