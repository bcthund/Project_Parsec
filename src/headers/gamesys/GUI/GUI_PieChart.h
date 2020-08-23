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
#include "GUI_Window.h"
#include "GUI_Label.h"

// TODO: Allow pie to have an arbitrary size instead of just 100%
//			- Item sizes are translated into 1% slices for drawing

// TODO: Draw lines between wedges after line is implemented into GUI

namespace Core {
	namespace GUI {
		namespace Object {

			class t_PieItem {
				friend class PieChart;
				private:
					int *value;
					bool bLocal;

				public:
					// TODO: Remove color, use window for color. Will need to define in constructor
//					Color *color;
					Props_Window pWin;
					Window *base;
					Window *colorBox;
					Label *label;

					t_PieItem() {
						value = new int(0);
						bLocal = true;

//						int iColor = colors().FIRST + std::rand() % (colors.colors.size()-(colors().FIRST+1));
//						color = &colors[iColor];

						base = nullptr;
						colorBox = nullptr;
						label = nullptr;

//						pWin.colorBack.base = &colors[iColor];
						//window = new Window(*newData->base->con, label, pWin);
						//window->init();
					}

//					t_PieItem(std::string l, int iValue, Color &c) {
//						this->value = new int(iValue);
//						this->bLocal = true;
////						this->color = &c;
//
//						base = nullptr;
//						colorBox = nullptr;
//						label = nullptr;
//					}
//
//					t_PieItem(std::string l, int *iValue, Color &c) {
//						this->value = iValue;
//						this->bLocal = false;
////						this->color = &c;
//
//						base = nullptr;
//						colorBox = nullptr;
//						label = nullptr;
//					}
//
//					t_PieItem(const t_PieItem &src) {
//						bLocal = src.bLocal;
//						value = src.value;
////						color = src.color;
//						base = src.base;
//						colorBox = src.colorBox;
//						label = src.label;
//					}
//
//					t_PieItem &operator=(const t_PieItem &src) {
//						bLocal = src.bLocal;
//						value = src.value;
////						color = src.color;
//						base = src.base;
//						colorBox = src.colorBox;
//						label = src.label;
//						return *this;
//					}
//
//					~t_PieItem(){
//						if(bLocal && value!=nullptr) delete value;
//						if(base != nullptr) delete base;
//						if(colorBox != nullptr) delete colorBox;
//						if(label != nullptr) delete label;
//					}

					void setValuePtr(int *ptr) {
						if(bLocal) delete value;
						bLocal = false;
						value = ptr;
					}

					void setValue(int n)				{	*value = n;		}
//					void setColor(Color &c)				{	color = &c;		}
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

//					ToolTip toolTip;															///< Tooltip info for this object
					void init();																///< Initialize thie object and its children
					void update();																///< Update local constraints, values, etc.
					void exec(iState eExternState=STATE_NONE);									///< Execute this object, draw if initialized
					void execToolTip();															///< Execute the tooltip, called externally
					void addItem(std::string label, int iValue);								///< Add a pie/legend item using a specific value
					void addItem(std::string label, int iValue, Color &base, Color &hover);		///< Add a pie/legend item using a specific value and use custom color
					void addItem(std::string label, int *iValuePtr);							///< Add a pie/legend item using a pointer to a value
					void addItem(std::string label, int *iValuePtr, Color &base, Color &hover);	///< Add a pie/legend item using a pointer to a value and use custom color
					void removeItem(std::string label);											///< Remove an item from the pie/legend
					t_PieItem& getItem(std::string label);										///< Get a pie/legend item reference, so it can be modified/updated externally

				protected:
					VAO vao;																	///< Definition for a single 1% triangle wedge
					Core::t_VectorMap<t_PieItem*> items;										///< List of pie/legend items
					Window	*legend;															///< Legend window container
					Label	*label;																///< Object title, displayed as legend title bar
					static Timer blink;															///< Timer for blinking wedge highlight
					static bool	bBlinkState;													///< Current toggle state of blinking wedge highlight

					void updateObjectState(iState eExternState);								///< Update the internal state of the object (eObjectState)
					void updateInput();															///< Update internal state and/or local values from keyboard/mouse input
			};

			Timer PieChart::blink;
			bool  PieChart::bBlinkState;

			PieChart::PieChart() {
				legend			= nullptr;
				label			= nullptr;
				bBlinkState		= false;
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
				bBlinkState		= false;
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
				bBlinkState		= false;
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
				bBlinkState		= false;
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
				bBlinkState		= false;
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
				//	Configure Pie Size from Radius
				// ------------------------------------------
				con->setWidth(con->radius*2);
				con->setHeight(con->radius*2);

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
//				if(legend->con->size.x > label->con->size.x) {
//					label->con->setWidth(legend->con->size.x);
//					label->con->exec();
//				}
//				else {
//					legend->con->setWidth(label->con->size.x);
//					legend->con->exec();
//				}
//				update();

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
				//	Create default undefined item
				// ------------------------------------------
				//addItem("Undefined", 0, colors[colors().Gray50], colors[colors().Gray80]);	// 0 %
				addItem("Undefined", 0, colors[colors().Gray50], colors[colors().Bright_green]);	// 0 %
				items["Undefined"]->colorBox->con->setStipplePattern(&stipple[stipple.STIPPLE_DOTS]);

				// ==========================================
				//	Create temporary test items
				// ------------------------------------------
//				addItem("Test 0", 8);		// 8 %
//				addItem("Test 1", 2);		// 10 %
//				addItem("Test 2", 5);		// 15 %
//				addItem("Test 3", 1);		// 16 %
//				addItem("Test 4", 30);		// 46 %
//				addItem("Test 5", 10);		// 56 %
//				addItem("Test 6", 38);		// 94 %

//				items["Test 2"]->colorBox->con->setStipplePattern(&stipple[stipple.STIPPLE_CROSSES]);
//				items["Test 4"]->colorBox->con->setStipplePattern(&stipple[stipple.STIPPLE_INSULATION]);
//				items["Test 6"]->colorBox->con->setStipplePattern(&stipple[stipple.STIPPLE_SHAKES]);

				// ==========================================
				//	Setup Tooltip
				// ------------------------------------------
//				toolTip.init(*con, name);

				// ==========================================
				//	Update
				// ------------------------------------------
//				update();

				blink.start();
//				timeFocusDebounce.start();
				bInit = true;
			}

			/**
			 * @brief Add an item to the list with \p title and \p iValue
			 * @param title Name of item
			 * @param iValue Value of item
			 */
			void PieChart::addItem(std::string label, int iValue) {
				int iColor = colors().FIRST + std::rand() % (colors.colors.size()-(colors().FIRST+1));
				addItem(label, iValue, colors[iColor], colors[colors().Bright_green]);
			}

			/**
			 * @brief Add an item to the list with \p title and \p iValue
			 * @param title Name of item
			 * @param iValue Value of item
			 */
			void PieChart::addItem(std::string label, int iValue, Color &base, Color &hover) {
				t_PieItem * newData = new t_PieItem();
				newData->setValue(iValue);
				newData->base = new Window(*legend->con, label, con->propLegendItem);
				newData->base->init();

				newData->colorBox = new Window(*newData->base->con, label, con->propColorBox);
				newData->colorBox->con->colorBack.base = &base;
				newData->colorBox->con->colorBack.active = &hover;
				newData->colorBox->con->colorBack.highlight = &hover;
				newData->colorBox->init();

				Props_Label * pLabel = new Props_Label();;
				pLabel->setOrigin(CONSTRAIN_RIGHT);
				pLabel->setAnchor(CONSTRAIN_LEFT);
				newData->label = new Label(*newData->colorBox->con, label, pLabel);
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
			void PieChart::addItem(std::string label, int *iValuePtr) {
				int iColor = colors().FIRST + std::rand() % (colors.colors.size()-(colors().FIRST+1));
				addItem(label, iValuePtr, colors[iColor], colors[colors().Bright_green]);
			}

			/**
			 * @brief Add an item to the list with \p title and \p iValue
			 * @param title Name of item
			 * @param iValue Value of item
			 */
			void PieChart::addItem(std::string label, int *iValuePtr, Color &base, Color &hover) {
				t_PieItem * newData = new t_PieItem();
				newData->setValuePtr(iValuePtr);
				newData->base = new Window(*legend->con, label, con->propLegendItem);
				newData->base->init();

				newData->colorBox = new Window(*newData->base->con, label, con->propColorBox);
				newData->colorBox->con->colorBack.base = &base;
				newData->colorBox->con->colorBack.active = &hover;
				newData->colorBox->con->colorBack.highlight = &hover;
				newData->colorBox->init();

				Props_Label * pLabel = new Props_Label();;
				pLabel->setOrigin(CONSTRAIN_RIGHT);
				pLabel->setAnchor(CONSTRAIN_LEFT);
				newData->label = new Label(*newData->colorBox->con, label, pLabel);
				newData->label->init();

				items.add(label, newData);

				// Prep for next item
				con->propLegendItem.modPos(0, -con->propLegendItem.size.y);
			}

			/**
			 * @brief Add a list of items all at once
			 * @param vItems Vector of <title, value> pairs to set
			 */
			// TODO: Implement addItems (direct value only)
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
				if(label != "Undefined") items.remove(label);
			}

			t_PieItem& PieChart::getItem(std::string label) {
				return *items[label];
			}

			void PieChart::update() {
				// Update pie dimensions in case resized (maybe use radius only? disable width/height in props)
				con->setWidth(con->radius*2);
				con->setHeight(con->radius*2);

				// Calculate and Set legend height
				if(items.size()>0) {
					int iHeight = items.size();
					legend->con->setHeight( ((iHeight)*con->propLegendItem.size.y + legend->con->vPadding.top_bottom()), SIZE_CONSTRAINT_ABSOLUTE);
				}

				// ==========================================
				//	Calculate and Set legend width
				// ------------------------------------------
				int iWidth = 0;

				// Start with title width
//				if(legend->con->size.x > label->con->size.x) iWidth = legend->con->size.x;
//				else iWidth = label->con->size.x;
				iWidth = label->con->size.x;

				// Find widest legend item including padding (this is effectively the minimum width)
				if(items.size()>0) {
					for(auto item : items) {
						int iItemWidth =	std::abs(item->base->con->vPadding.left_right()) +
											item->colorBox->con->size.x +
											std::abs(item->colorBox->con->vPadding.left_right()) +
											item->label->con->size.x +
											std::abs(item->label->con->vPadding.left_right());

						iWidth = std::max(iWidth, iItemWidth);
					}
				}

				// If autowidth then set, otherwise just check as minimum width
				if(con->bLegendAutoWidth) {
					label->con->setWidth(iWidth, SIZE_CONSTRAINT_ABSOLUTE);
					legend->con->setWidth(iWidth, SIZE_CONSTRAINT_ABSOLUTE);
				}
				else {
					if( (legend->con->size.x < iWidth) || (label->con->size.x < iWidth) ) {
						label->con->setWidth(iWidth, SIZE_CONSTRAINT_ABSOLUTE);
						legend->con->setWidth(iWidth, SIZE_CONSTRAINT_ABSOLUTE);
					}
				}

				// Set undefined range (For legend)
				int iRem = 100;
				if(items.size()>1) {
					for(int n=2; n<items.size(); n++) iRem -= items[n]->getValue();
				}
				items["Undefined"]->setValue(iRem);
			}

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


			void PieChart::updateInput() {
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

						// Allow update only if No object active or this object active
//						if((con->bFocusLock && !bFocusPresent) || !con->bFocusLock || (sActiveObject==id)) {
//							updateObjectState(eExternState);
//
//							if(this->con->toolTip.bShow) this->toolTip.updateObjectState(this->eObjectState);
//							else this->toolTip.updateObjectState(STATE_NONE);
//						}

						matrix->Push();

							// Only scroll this item if the parent has scrolling enabled
							Vector2f vSize = con->getSize()/2.0f;

							Vector2f vPos;
							if(con->scroll.isScrollable() && (parent!=nullptr && parent->scroll.getEnabled())) vPos = con->getScrollPos();
							else vPos = con->getPos();

							matrix->Translate( vPos.x, vPos.y, 0.0 );
							matrix->Scale(vSize.x, vSize.y, 1);

							shader->data.GLS_MENU.vPos				= vPos;
							shader->data.GLS_MENU.vSize				= con->getSize();
							shader->data.GLS_MENU.iRadius			= con->getRadius();
							shader->data.GLS_MENU.bRoundBorder		= con->getRoundBorder();

							int index = 1;	// Current item index
							int pre = 0;	// Total from previous item
							for(int n=0; n<100; n++) {
								matrix->Rotate(Degrees(3.6).toRadians(), 0, 0, -1);

								// Make sure item exists
								if(index<items.size()) {

									if(bBlinkState && ((items[index]->base->eObjectState&STATE_HOVER) || (items[index]->base->eObjectState&STATE_ACTIVE)) ) {
										colors.PushFront(items[index]->colorBox->con->colorBack.highlight);
										colors.PushBack(items[index]->colorBox->con->colorBorder.highlight);
										border = con->borderHover;
									}
									else {
										colors.PushFront(items[index]->colorBox->con->colorBack.base);
										colors.PushBack(items[index]->colorBox->con->colorBorder.base);
										border = con->borderNormal;
									}

									shader->data.GLS_MENU.iBorder = border;
									shader->data.GLS_MENU.bEnableStipple = items[index]->colorBox->con->bEnableStipple;
									if(items[index]->colorBox->con->bEnableStipple) {
										shader->data.GLS_MENU.stipple = items[index]->colorBox->con->stipple;
										shader->data.GLS_MENU.stippleColor = items["Undefined"]->colorBox->con->stippleColor.base;
									}

									// Prep for next item
									if(n >= (pre+items[index]->getValue())) {
										pre += items[index]->getValue();
										index++;
									}
								}
								else {
									// Undefined Area, fill remaining space
									if(bBlinkState && ((items["Undefined"]->base->eObjectState&STATE_HOVER) || (items["Undefined"]->base->eObjectState&STATE_ACTIVE)) ) {
										colors.PushFront(items["Undefined"]->colorBox->con->colorBack.highlight);
										colors.PushBack(items["Undefined"]->colorBox->con->colorBorder.highlight);
										border = con->borderHover;
									}
									else {
										colors.PushFront(items["Undefined"]->colorBox->con->colorBack.base);
										colors.PushBack(items["Undefined"]->colorBox->con->colorBorder.base);
										border = con->borderNormal;
									}

									shader->data.GLS_MENU.iBorder = border;
									shader->data.GLS_MENU.bEnableStipple = items["Undefined"]->colorBox->con->bEnableStipple;
									shader->data.GLS_MENU.stipple = items["Undefined"]->colorBox->con->stipple;
									shader->data.GLS_MENU.stippleColor = items["Undefined"]->colorBox->con->stippleColor.base;
								}

								matrix->SetTransform();
								shader->getUniform(GLS_MENU);
								vao.Draw();
								colors.PopFront();
							}

							// Draw all slices same color
							//  - keep for possible future reference, draws a nice circle
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

						if(con->bShowLegend) {
							label->exec();
							legend->exec(STATE_NONE);

							// Draw Legend Colors and Labels, skip Undefined if no value
							int n = 1;
							if(items["Undefined"]->getValue()>0) n = 0;

							for( ; n<items.size(); n++) {
								items[n]->base->exec(STATE_NONE);
								items[n]->colorBox->exec(STATE_NONE);
								items[n]->label->exec(STATE_NONE);
							}

							// Update highlight blink
							if(blink.get_splitdiff() > con->iBlinkRate) {
								blink.split();
								bBlinkState = !bBlinkState;
							}
						}

					}
				}
			}

			/**
			 * @brief Draw tooltip
			 */
//			void PieChart::execToolTip() {
//				toolTip.exec();
//			}

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
