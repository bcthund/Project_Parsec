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
#include "GUI_Label.h"

// TODO: Allow pie to have an arbitrary size instead of just 100%
//			- Item sizes are translated into 1% slices for drawing

namespace Core {
	namespace GUI {
		namespace Object {

			class t_PieItem {
				friend class PieChart;
				private:
//					std::string label;
					int *value;
					bool bLocal;
//					Stipple_Pattern	* stipple;
//					Window base;
//					Window window;
//					Label label;

				public:
					Color *color;
					Window *base;
					Window *window;
					Label *label;

					t_PieItem() {
//						label = "Undefined";
						value = new int(0);
						bLocal = true;

						int iColor = colors().FIRST + std::rand() % (colors.colors.size()-(colors().FIRST+1));
						color = &colors[iColor];

						base = nullptr;
						window = nullptr;
						label = nullptr;
//						stipple = nullptr;
					}

					t_PieItem(std::string l, int iValue, Color &c) {
//						this->label = l;
						this->value = new int(iValue);
						this->bLocal = true;
						this->color = &c;

						base = nullptr;
						window = nullptr;
						label = nullptr;
//						stipple = nullptr;
					}

					t_PieItem(std::string l, int *iValue, Color &c) {
//						this->label = l;
						this->value = iValue;
						this->bLocal = false;
						this->color = &c;

						base = nullptr;
						window = nullptr;
						label = nullptr;
//						stipple = nullptr;
					}

					t_PieItem(const t_PieItem &src) {
						bLocal = src.bLocal;
						value = src.value;
						color = src.color;
						base = src.base;
						window = src.window;
						label = src.label;
//						stipple = src.stipple;
					}

					t_PieItem &operator=(const t_PieItem &src) {
						bLocal = src.bLocal;
						value = src.value;
						color = src.color;
						base = src.base;
						window = src.window;
						label = src.label;
//						stipple = src.stipple;
						return *this;
					}

					~t_PieItem(){
						if(bLocal && value!=nullptr) delete value;
						if(base != nullptr) delete base;
						if(window != nullptr) delete window;
						if(label != nullptr) delete label;
					}

					void setValuePtr(int *ptr) {
						if(bLocal) delete value;
						bLocal = false;
						value = ptr;
					}

//					void setLabel(std::string l)		{	label = l;	}
					void setValue(int n)				{	*value = n;		}
					void setColor(Color &c)				{	color = &c;		}
					int getValue()						{	return *value;	}
					int & getValuePtr()					{	return *value;	}
			};

//			class t_PieItem {
//				friend class PieChart;
//				private:
//					std::string label;
//					int *value;
//					bool bLocal;
//					Color *color;
//
//				public:
//					t_PieItem() {
//						label = "Undefined";
//						value = new int(0);
//						bLocal = true;
//
//						// TODO: Randomize default colors?
////						int iLastColor = colors.colors.size() - 2;	// Last color by default is transparent, skip that one (user added colors will break this)
////						int iColor = std::rand() % iLastColor;
//						//std::srand(std::time(0));
//						//std::srand(1024);
//						int iColor = std::rand() % (colors.colors.size()-2);
////						std::random_device r;
////						std::default_random_engine e1(r());
////						std::uniform_int_distribution<int>(0,colors.colors.size()-2);
////						int iColor =
//						//color = &colors[colors().Green];
//						color = &colors[iColor];
//					}
//
//					t_PieItem(std::string l, int iValue, Color &c) {
//						this->label = l;
//						this->value = new int(iValue);
//						this->bLocal = true;
//						this->color = &c;
//					}
//
//					t_PieItem(std::string l, int *iValue, Color &c) {
//						this->label = l;
//						this->value = iValue;
//						this->bLocal = false;
//						this->color = &c;
//					}
//
//					~t_PieItem(){
//						if(bLocal && value!=nullptr) delete value;
//					}
//
//					void setValuePtr(int *ptr) {
//						if(bLocal) delete value;
//						bLocal = false;
//						value = ptr;
//					}
//
//					void setLabel(std::string l)		{	label = l;	}
//					void setValue(int n)				{	*value = n;		}
//					void setColor(Color &c)				{	color = &c;		}
//					int getValue()						{	return *value;	}
//					int & getValuePtr()					{	return *value;	}
//			};

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
//					ColorSwatch& getItem(std::string label);

				protected:
					VAO vao;
					Core::t_VectorMap<t_PieItem*> items;
//					Core::t_VectorMap<ColorSwatch*> items;
					Window	*legend;
					Label	*label;

					void updateObjectState(iState eExternState);
					void updateScrollMouse();
			};

			PieChart::PieChart() {
				legend			= nullptr;
				label			= nullptr;
			}

			PieChart::PieChart(std::string n, Props_PieChart &c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= true;
				con				= new Props_PieChart();
				*con			= c;
				if(con->text == "") con->text = n;

				legend			= nullptr;
				label			= nullptr;
			}

			PieChart::PieChart(std::string n, Props_PieChart *c) {
				name			= n;

				bHasParent		= false;
				parent			= nullptr;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

				legend			= nullptr;
				label			= nullptr;
			}

			PieChart::PieChart(Props &p, std::string n, Props_PieChart &c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= true;
				con				= new Props_PieChart();
				*con			= c;
				if(con->text == "") con->text = n;

				legend			= nullptr;
				label			= nullptr;
			}

			PieChart::PieChart(Props &p, std::string n, Props_PieChart *c) {
				name			= n;

				bHasParent		= true;
				parent			= &p;

				bLocalCon		= false;
				con				= c;
				if(con->text == "") con->text = n;

				legend			= nullptr;
				label			= nullptr;
			}

			PieChart::~PieChart() {
				if(bLocalCon && con != nullptr) delete con;
				if(legend != nullptr) delete legend;
				if(label != nullptr) delete label;
			}

			void PieChart::init() {
				// Initialize srand for random color assignment
				std::srand((unsigned) time(0));

				// ==========================================
				//	Configure Pie Size and Radius
				// ------------------------------------------
				int iMaxRadius = std::max(con->size.constraint.x, con->size.constraint.y);
				con->setWidth(iMaxRadius);
				con->setHeight(iMaxRadius);
				con->setRadius(iMaxRadius/2);

				// ==========================================
				//	Preliminary setup
				// ------------------------------------------
				this->id = IDs.create();
				if(bHasParent) {
					if(!con->scroll.getEnabled() && con->scroll.isScrollable()) con->scroll.bind(*parent);
					con->exec(*parent);
				}
				else {
					con->exec();
				}

				// ==========================================
				//	Setup legend title
				// ------------------------------------------
				label = new Label(*con, name, &con->label);
				label->init();

				// ==========================================
				//	Setup legend list
				// ------------------------------------------
				legend = new Object::Window(*con, name+"_List", &con->propLegend);
				legend->con->enablePadding(PADDING_ALL);
				legend->init();

				// Set width to largest
				if(legend->con->size.x > label->con->size.x) {
					label->con->setWidth(legend->con->size.x);
					label->con->exec();
				}
				else {
					legend->con->setWidth(label->con->size.x);
					legend->con->exec();
				}

				// Get legend item data prepped
				con->propLegendItem.exec();

				// ==========================================
				//	Create Triangle Wedge
				// ------------------------------------------
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

				// ==========================================
				//	Create temporary test items
				// ------------------------------------------
				addItem("Undefined", 0, colors[colors().Gray50]);	// 0 %
				addItem("Test 0", 8);		// 8 %
				addItem("Test 1", 2);		// 10 %
				addItem("Test 2", 5);		// 15 %
				addItem("Test 3", 1);		// 16 %
				addItem("Test 4", 30);		// 46 %
				addItem("Test 5", 10);		// 56 %
				addItem("Test 6", 38);		// 94 %

				items["Undefined"]->window->con->setStipplePattern(&stipple[stipple.STIPPLE_DOTS]);
				items["Test 2"]->window->con->setStipplePattern(&stipple[stipple.STIPPLE_CROSSES]);
				items["Test 4"]->window->con->setStipplePattern(&stipple[stipple.STIPPLE_INSULATION]);
				items["Test 6"]->window->con->setStipplePattern(&stipple[stipple.STIPPLE_SHAKES]);


				// ==========================================
				//	Setup Tooltip
				// ------------------------------------------
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
				newData->setValue(iValue);
				newData->base = new Window(*legend->con, label, con->propLegendItem);
				newData->base->init();

				Props_Window pWin;
				pWin.setOrigin(CONSTRAIN_LEFT);
				pWin.setAnchor(CONSTRAIN_LEFT);
				pWin.setWidth(25);
				pWin.setHeight(15);
				pWin.setPadding(-5);
				pWin.colorBack.base = newData->color;
//				pWin.disableStipple();
				newData->window = new Window(*newData->base->con, label, pWin);
				newData->window->init();

				Props_Label * pLabel = new Props_Label();;
				pLabel->setOrigin(CONSTRAIN_RIGHT);
				pLabel->setAnchor(CONSTRAIN_LEFT);
				newData->label = new Label(*newData->window->con, label, pLabel);
				newData->label->init();

				items.add(label, newData);

				// Prep for next item
				con->propLegendItem.modPos(0, -con->propLegendItem.size.y);
			}

			/**
			 * @brief Add an item to the list with \p title and \p iValue
			 * @param title Name of item
			 * @param iValue Value of item
			 */
			void PieChart::addItem(std::string label, int iValue, Color &color) {
				t_PieItem * newData = new t_PieItem();
				newData->setValue(iValue);
				newData->setColor(color);
				newData->base = new Window(*legend->con, label, con->propLegendItem);
				newData->base->init();

				Props_Window pWin;
				pWin.setOrigin(CONSTRAIN_LEFT);
				pWin.setAnchor(CONSTRAIN_LEFT);
				pWin.setWidth(25);
				pWin.setHeight(15);
				pWin.setPadding(-5);
				pWin.colorBack.base = newData->color;
				newData->window = new Window(*newData->base->con, label, pWin);
				newData->window->init();

				Props_Label * pLabel = new Props_Label();;
				pLabel->setOrigin(CONSTRAIN_RIGHT);
				pLabel->setAnchor(CONSTRAIN_LEFT);
				newData->label = new Label(*newData->window->con, label, pLabel);
				newData->label->init();

				items.add(label, newData);

				// Prep for next item
				con->propLegendItem.modPos(0, -con->propLegendItem.size.y);

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
//			ColorSwatch& PieChart::getItem(std::string label) {
				return *items[label];
			}

			void PieChart::update() {
//				if (con->bResizeRadius) {
//					int iRadius = fmin(fmin(con->radius, con->size.x/2.0f), con->size.y/2.0f);
//					con->setRadius(iRadius);
//				}

				// TODO: Update legend dimensions (take into account title)
				if(items.size()>0) {
					int iHeight = items.size();
	//				int iScrollHeight = scrollUp->con->size.y + scrollDown->con->size.y;
	//				legend->con->setHeight(iScrollHeight + ((iHeight)*con->itemButton.size.y+itemList->con->vPadding.top_bottom()), SIZE_CONSTRAINT_ABSOLUTE);
					// TODO: Move legend items into their own container
					legend->con->setHeight( ((iHeight)*con->propLegendItem.size.y + legend->con->vPadding.top_bottom()), SIZE_CONSTRAINT_ABSOLUTE);

					// TODO: Set width to largest
	//				if(legend->con->size.x > label->con->size.x) {
	//					label->con->setWidth(legend->con->size.x);
	//				}
	//				else {
	//					legend->con->setWidth(label->con->size.x);
	//				}

					// TODO: Temporary test
	//				for(auto item : items) {
	//					item->label->con->setOrigin(CONSTRAIN_LEFT);
	//					item->label->con->setAnchor(CONSTRAIN_RIGHT);
	//					item->label->con->setBorder(1, 1);
	//				}
				}

				// TODO: Set undefined range
//				if(items.size()>1) {
//					int iRem = 100;
//					for(int n=2; n<items.size(); n++) iRem -= items[n]->getValue();
//					items["Undefined"]->setValue(iRem);
//				}
//				else {
//					items["Undefined"]->setValue(100);
//				}
			}

			// TODO: Update with Triangle detection? Lots of triangles to check.
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

						update();

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
//							matrix->Rotate(Degrees(3.6).toRadians(), 0, 0, 1);

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

							int index = 1;	// Current item index
							int pre = 0;	// Total from previous item
							for(int n=0; n<100; n++) {
								matrix->Rotate(Degrees(3.6).toRadians(), 0, 0, -1);

								// Make sure item exists
								if(index<items.size()) {
									colors.PushFront(items[index]->color);

									//debug.log("["+items[index]->window->name+"]"+std::to_string(items[index]->window->con->stipple));
									shader->data.GLS_MENU.bEnableStipple = items[index]->window->con->bEnableStipple;
									if(items[index]->window->con->bEnableStipple) {
										//shader->data.GLS_MENU.stipple = con->stipple;
										shader->data.GLS_MENU.stipple = items[index]->window->con->stipple;
									}

									// Prep for next item
									if(n >= (pre+items[index]->getValue())) {
										pre += items[index]->getValue();
										index++;
									}
								}
								else {
									// Undefined Area, fill remaining space
									//colors.PushFront(colors[colors().Gray50]);
									//shader->data.GLS_MENU.stipple = &stipple[stipple.STIPPLE_DOTS];
									colors.PushFront(items["Undefined"]->color);
									shader->data.GLS_MENU.bEnableStipple = items["Undefined"]->window->con->bEnableStipple;
									shader->data.GLS_MENU.stipple = items["Undefined"]->window->con->stipple;

								}

//								//debug.log("["+items[index]->window->name+"]"+std::to_string(items[index]->window->con->stipple));
//								shader->data.GLS_MENU.bEnableStipple = items[index]->window->con->bEnableStipple;
//								if(items[index]->window->con->bEnableStipple) {
//									//shader->data.GLS_MENU.stipple = con->stipple;
//									shader->data.GLS_MENU.stipple = items[index]->window->con->stipple;
//								}

								matrix->SetTransform();
								shader->getUniform(GLS_MENU);
								vao.Draw();
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

						label->exec();
						legend->exec(STATE_NONE);

						// TODO: Draw Legend Colors and Labels
						matrix->Push();
						for(auto item: items) {
							item->base->exec();
							item->window->exec();
							item->label->exec();
//							matrix->Translate( 0.0, -50, 0.0 );
//							debug.log(item->label->name);
						}
						matrix->Pop();
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
