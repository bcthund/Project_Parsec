/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_H_
#define HEADERS_GAMESYS_GUI_H_

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

/*
 * TODO: [X] Color swatch - Block with a Vector4f pointer to show a color. Simply a specialized window class.
 * TODO: [X] Checkbox/Radio with grouping (box with smaller filled box)
 * TODO: [X] Text Area - Like a text box but without editing capabilities for a lighter class (base class?)
 * TODO: [X] Scrollbar (buttons)
 * TODO: [X] Text Box - A multiline text editor/viewer with text wrapping (needs cursor management)
 * TODO: [X] Icon - For tool buttons
 * TODO: [X] Add function to set default GUI instead of passing it in every function
 * TODO: [X] Add function to set default Window instead of passing it in every function
 * TODO: [X] Sprite (Image)
 * TODO: [X] Group windows by GUI (already done), but additionally group all other objects by window so object names don't conflict
 * TODO: [X] Add groupState to Buttons
 * TODO: [X] Add groupState to Icons
 * TODO: [X] (Slider Not Finished) Move VAO out of individual objects and into base class so all use the same VAO
 * TODO: [X] Padding - Padding can be different on left/right, adjust centering/size based on padding. (Also do for vertical)
 * TODO: [X] Appears to be fixed, now tied to containers automatically through use of exec() function.
 * TODO: [X] Move all object ADD/manage functions into GUI_Container class. Should allow nested usage.
 * TODO: [X] Overload () or [] operator for GUI_Container to quickly access containers
 * TODO: [X] Add Container access functions (add, get, etc) to Containers
 * TODO: [X] Add Windows to GUI_Container (Just because, not really used directly but should be available)
 * TODO: [X] Audio sounds (Tie to GUI container, button click sounds, window open/close sounds)
 * TODO: [X] Clean up all existing GUI Objects
 * TODO: [X] Tie internal object components enable to parent enable. (eExternState essentially handles this)
 * TODO: [X] Make bEnable an array of conditions to be met
 * TODO: [E] Make all interactive items (button, icon, checkbox) as Integer items, then tie to returnState. Effectively makes all items multistate 'ready', but not implemented.
 * 				- This breaks getPointer functionality returning a boolean to control things such as bEnable. Would have to make bEnable int and wastes a lot of memory to do that.
 * TODO: [E] Add a hover state to returnState.
 * 				- Requires above implementation which cannot be done easily
 * TODO: [-] Function to tie buttons/icons/checkboxes together by way of eObjectState?
 * TODO: [X] Expand bEnable to have AND set and an OR set to allow better enable logic.
 * 				- All logic will work with ((enAND[0] && enAND[1] && ... enAND[7]) && (enOR[0] || enOR[1] || ... enOR[7])
 * 				- ANDs and ORs do not mix, all conditions must be met. (enAND && enOR)
 * TODO: [X] When an interactive item goes out of focus (window closed), revert changes and exit editing. May require external function call like updateValuePtr in GUI_Container.exec()
 * 				- Generally speaking, can't use ANY controls while an object is active, but this has been implemented anyways.
 * TODO: [X] If any item has focus, then disable object state updates for ALL other objects.
 * TODO: [X] Hover doesn't work on fields when tied to sliders and the slider is disabled
 * TODO: [X] Add STATE_UPDATE logic to all interactive objects
 * TODO: [c] valuePtr should be set from eObjectState
 * TODO: [X] Tooltip, create a base that is added to windows. On hover (if enabled) tooltip is shown, anchored to mouse.
 * 				[X] Floating text box
 * 				[X] Show box only when hovering over object (start with buttons only)
 * 				[X] Update Props according to quadrants
 * 				[X] Allow object to enable/disable tooltip (still only buttons)
 * 				[X] Draw tooltips in GUI_Container.h as separate function call
 * 				[X] Add tooltips to other GUI objects (add to Generic class in GUI_Objects.h?)
 * 				[X] Color Pallette settings for toolTip
 * 				[X] Implement label header, specifies name of calling object
 * TODO: [X] Autosize width/height for text based objects
 * 				[X] Option for auto Width (If word wrap enabled, then simply check if current size is smaller than a line of text.)
 * 				[X] Option for auto Height
 * TODO: [X] Check all object accesses ( map.count(key) > 0 )
 * 				[ ] Expand to non GUI objects using mappings
 * TODO: [X] Add execToolTip() function to all objects. Needs to call nested toolTip.exec() functions.
 * TODO: [X] Add mstate mouse hover detection like in Button class.
 * TODO: [X] Add mouse state reset to all objects
 * TODO: [X] Plain Text (Use existing GUI_Text class) (TextArea already exists)
 * TODO: [X] Add AutoSize logic and include conditions to prevent drawing until sizing is complete
 * 				[X] Autosize to multiline text
 * 				[X] Autosize to labels - general single line text
 * 				[X] Autosize Fields
 * TODO: [X] Fix padding, especially when using relative size Props. (See Window settings label when adjusting window padding)
 * 				[X] Adjust width according to parent size and padding
 * 				[X] Center on parent
 * 				[X] Adjust center according to padding
 * 				[X] Add border size to padding (100% object should draw over border)
 * TODO: [C] Sliders won't release mouse when using integers.
 * 				- Apparently only for the DebugLight slider.
 * 				- Field interference?
 * 				- Conflict with a disabled field?
 * 				- Problem went away???
 * TODO: [E] Add a window background, with autosizing if possible, to Sliders
 * 				- Abort, this really isn't necessary and can't be automated so not worth it.
 * TODO: [X] Rename Props to Props (Properties) which is more accurate
 * TODO: [X] Disabling Fields on Sliders cause segfault (FIXED: execToolTip()/updateNoFocus() wasn't checking if field was enabled))
 * TODO: [ ] Implement Scissoring on all objects
 * 				- Scissoring window is the objects window minus any padding.
 * 					- Objects drawn outside the window will no longer be visible
 * 					- Don't apply scissor to additional objects such as labels and fields.
 * 				- Scissor coordinates calculated in constrants exec?
 * 				[X] Allow scissoring to be disabled (So you can draw additional windows with another window as parent)
 * 				[ ] Scissor stack
 * TODO: [X] Modify tooltip autosize to also look at label size
 * 				- The name of the tooltip, if shown, may be wider than the set tooltip text.
 * TODO: [E] Centering should take into account label and field on sliders if possible (don't think this is possible with the current setup)
 * 				- Can't do this, breaks slider alignment. Slider size should always be absolute
 * TODO: [E] Add a label header (like in tooltips) to windows.
 * 				- Cyclical problem with using a window to draw a label before window defined
 * TODO: [X] Add mouse hover detection to windows
 * 				- Interferes with other items for some reason. Likely relate to eObjectState but seems tied to mState.
 * TODO: [ ] Progress Bar/Progress Spinner (classic spinning /|\-/|\- style)
 * 				[X] Show horizontal progress
 * 				[X] Allow progress percentage overlay (field)
 * 				[X] Create progress pallette
 * 				[X] Move progress bar properties into primary ProgressBar property to allow customization.
 * 				[X] Make progress percentage toggleable
 * 				[ ] Make Field read-only (see TODO item below)
 * TODO: [ ] Allow fields to be ready only without disable, this will allow custom coloring.
 * TODO: [ ] Update constraints colors to be in struct for cleaner access
 * TODO: [ ] Allow sliders to have locally defined values instead of just pointers
 * TODO: [ ] Fix slider CTRL mod to allow minimum step at least. Sometimes no movement on sliders using CTRL.
 * 				- General mod calculations should be fixed, minimum step should be the CTRL value.
 * 				- Maybe add a maximum step for SHIFT value?
 * 				- In that case, add a normal step value.
 * 				- setStep(min, normal, max)
 * TODO: [ ] Drop down (Combo Box)
 * 				[ ] Create new class
 * 					[ ] Add Constraint definition
 * 					[ ] Add to Containers
 * 				[ ] Modify Props_Addon_ReturnState to allow multiple types, instead of just int
 * 				[ ] Vector of Props_Addon_ReturnState as Items
 * 				[ ] Map name of Props_Addon_ReturnState<->Vector
 * 				[ ] Create a selected item pointer to Props_Addon_ReturnState
 * 					[ ] Default to first item (index 0)
 * 					[ ] Allow specifying default index on creation (similar to bool starting state in buttons)
 * 				[ ] "getState" returns value from currently selected item
 * 				[ ] Draw Selected Item
 * 					[ ] Window
 * 					[ ] Label with transparent background
 * 					[ ] Highlight Label on mouse hover
 * 				[ ] Draw Item list
 * 					[ ] Draw window
 * 					[ ] Draw labels for each Item
 * 					[ ] Highlight Label on mouse hover
 * 					[ ] Set to selected when clicked
 * 				[ ] Item List size
 * 					[ ] Number of items to show
 * 					[ ] Current scrollIndex
 * 					[ ] Scrollbar tied to scrollIndex
 * 				[ ] Hide Item List
 * 					[ ] Show dropdoen button
 * 					[ ] Pressing dropdown button toggles item list visibility
 * TODO: [ ] Pie Chart
 * 				[ ] Draw triangles for each quantity, larger than circle area
 * 				[ ] Use shader to procedurally drop fragments outside circle area
 * 				[ ] Allow donut style as well, drop outer circle and smaller inner circle
 * 				[ ] Legend anchored externally to chart (L/TL/T/TR/R/BR/B/BL)
 * TODO: [ ] Slider2D - Like a slider but uses a point in 2D space controlling 2 values at once
 * 				[ ] Box for selection area (window using standard Props)
 * 				[ ] X-Axis Range (min, max), integer only
 * 				[ ] Y-Axis Range (min, max), integer only
 * 				[ ] Track mouse and mapped X-Y values (relative (0,0) is always bottom left.)
 * 				[ ] Show point (slider control, square) on current value coordinates
 * 				[ ] Clicking mouse/holding mouse sets values
 * TODO: [ ] Animation - Use animation system except draw with Props system to screen.
 * 				- Animation can be repeating or one-shot controlled
 * TODO: [ ] Scrolling Window - This might be difficult
 * 				[X] Scrolling text window
 * 				[-] Scrolling window with objects would be quite difficult. Would have to do clipping somwhow, not worth the trouble.
 * 				[ ] Can use glScissor and glEnable/Disable(GL_SCISSOR_TEST). Use Window minus padding for drawable area.
 * TODO: [ ] GUI focus handing like button groups, GUI name defines focus group.
 * 				- Group focus allows window layers that won't interfere with each other.
 * 				- Focus is set/reset by code conditions. (Button opens GUI and activates focus, Close button closes GUI and releases focus. Use a STACK.)
 * 				[ ] Create a GUI stack
 * 					- Vector of strings (name of GUI) [STACK]
 * 					- Map of name to vector index
 * 				[ ] GUI.Push(<string>) function to add GUI name to stack
 * 				[ ] GUI.Pop() function removes current GUI from top of stack
 * 				[ ] Add a GUI.exec() function to execute GUIs on the GUI stack
 * 					[ ] Execute stack in order
 * 					[ ] Only top of stack accepts input
 *
 * --------------------------------------------------------------------------------------------------
 *
 * TODO: [ ] (FIX) Implement copy/assignment constructors for all objects to prevent errant pointer destruction
 * 				- AndOrBase shows memory leaks
 * TODO: [ ] Fix GUI memory leaks
 *
 * --------------------------------------------------------------------------------------------------
 * Items below here are low priority or difficult to implement and can be done later
 * --------------------------------------------------------------------------------------------------
 * TODO: [ ] Spinner - Addon to numeric fields instead of separate object?
 * TODO: [ ] Level Indicator (Possible same as progress bar but with min/max settings)
 * TODO: [ ] Lines (expand with pos/length/angle, two points, etc)
 */

#include <vector>
#include <type_traits>
//#include <iostream>
//#include "../core/core_functions.h"
//#include "GUI_Constraint.h"
#include "GUI_Container.h"
//#include "GUI_Master.h"

namespace Core {
	namespace GUI {
		class GUI {
			private:
				std::vector<GUI_Container*> guis;
				Map_si	  mapGUI;

			public:
				GUI();
				virtual ~GUI();
				GUI_Container	* activeGUI;
				void createGUI(std::string guiName);
				void createGUI(std::string guiName, Props_Window c);
				Props * getGUI();
				Props * getGUI(std::string guiName);
				void setActiveGUI(std::string guiName);
				bool hasFocus() { return iGUIFocus>0; };	// This GUI instance has focus
				void exec(std::string guiName);
				static int iGUIFocus;	// If ANY GUI element has focus, then ignore input elsewhere. (Don't fire your gun while clicking on menu)

				/**
				 * \brief Returns the GUI with the given name
				 * @param guiName
				 * @return
				 */
				GUI_Container	&operator[](const std::string &guiName)	{	return *guis[mapGUI[guiName]];	}
		};

		int GUI::iGUIFocus = 0;

		GUI::GUI() {
			std::cout << "Construct GUI System.............................................";
			activeGUI = nullptr;
			std::cout << "Done" << std::endl;
		}

		GUI::~GUI() {
			std::cout << "Destroy GUI System...............................................";
			for (auto & gui : guis) {
				delete gui;
			}
			std::cout << "Done" << std::endl;
		}

		/** ******************************************************************************************************************************
		 *
		 * @param guiName
		 * ****************************************************************************************************************************** */
		void GUI::createGUI(std::string guiName) {
			Props_Window c;
			c.setOrigin(CONSTRAIN_CENTER);
			c.setAnchor(CONSTRAIN_CENTER);
			c.setPos(0, 0);
			c.setWidth(Core::gameVars->screen.res.x, SIZE_CONSTRAINT_ABSOLUTE);
			c.setHeight(Core::gameVars->screen.res.y, SIZE_CONSTRAINT_ABSOLUTE);
			c.setPadding(0);
			c.setColorWindowB(&colors[colors().Transparent]);
			c.setColorBorderB(&colors[colors().Transparent]);
			c.bNoInput = true;

			GUI_Container * gui = new GUI_Container(guiName, c);
			gui->init();
			guis.push_back(gui);
			uint id = guis.size()-1;
			mapGUI.insert(make_pair(guiName, id));
			setActiveGUI(guiName);
		}

		/** ******************************************************************************************************************************
		 *
		 * @param guiName
		 * @param c
		 * ****************************************************************************************************************************** */
		void GUI::createGUI(std::string guiName, Props_Window c) {
//			GUI_Master * gui = new GUI_Master(guiName, c);
			GUI_Container * gui = new GUI_Container(guiName, c);
			gui->init();
			guis.push_back(gui);
			uint id = guis.size()-1;
			mapGUI.insert(make_pair(guiName, id));
			setActiveGUI(guiName);
		}

		/** ******************************************************************************************************************************
		 *
		 * @return
		 * ****************************************************************************************************************************** */
		Props * GUI::getGUI() {
			return activeGUI->con;
		}

		/** ******************************************************************************************************************************
		 *
		 * @param guiName
		 * @return
		 * ****************************************************************************************************************************** */
		Props * GUI::getGUI(std::string guiName) {
			uint guiID = mapGUI[guiName];
			return guis[guiID]->con;
		}

		/** ******************************************************************************************************************************
		 *
		 * @param windowName
		 * @param c
		 * ****************************************************************************************************************************** */
//		void GUI::createContainer(std::string containerName, Props_Window c) {
//
//			try {
//				GUI_Container * container;
//				container = new GUI_Container(*activeGUI->con, containerName, c);
//				activeGUI->containers.push_back(container);
//				uint id = activeGUI->containers.size()-1;
//				activeGUI->mapContainer.insert(make_pair(containerName, id));
//				setActiveContainer(containerName);
//			}
//			catch(...) {
//				std::cout << "Error creating Window Container, has a GUI been created and set active?" << std::endl;
//			}
//		}

		/** ******************************************************************************************************************************
		 *
		 * @return
		 * ****************************************************************************************************************************** */
//		GUI_Container * GUI::getContainer() {
//			return activeContainer;
//		}

		/** ******************************************************************************************************************************
		 *
		 * @param windowName
		 * @return
		 * ****************************************************************************************************************************** */
//		GUI_Container * GUI::getContainer(std::string containerName) {
//			return activeGUI->containers[activeGUI->mapContainer[containerName]];
//		}

		/** ******************************************************************************************************************************
		 *
		 * @param guiName
		 * @param windowName
		 * @return
		 * ****************************************************************************************************************************** */
//		GUI_Container * GUI::getContainer(std::string guiName, std::string containerName) {
//			uint guiID = mapGUI[guiName];
//			uint containerID = guis[guiID]->mapContainer[containerName];
//			return guis[guiID]->containers[containerID];
//		}

		/** ******************************************************************************************************************************
		 * \brief Set the active GUI/Window pair
		 * @param guiName
		 * @param windowName
		 *
		 * This is the normal way of setting the active GUI and window. When changing
		 * the GUI alone the activeContainer is not updated, therfore this function
		 * allows both to be set at the same time.
		 * ****************************************************************************************************************************** */
//		void GUI::setActive(std::string guiName, std::string containerName) {
//			activeGUI = guis[mapGUI[guiName]];
//			setActiveContainer(containerName);
//		}

		/** ******************************************************************************************************************************
		 * \brief Set the active window
		 * @param windowName
		 *
		 * This will set the active window reference with respect to the currently
		 * active GUI.
		 * ****************************************************************************************************************************** */
//		void GUI::setActiveContainer(std::string containerName) {
//			activeContainer = activeGUI->containers[activeGUI->mapContainer[containerName]];
//		}

		/** ******************************************************************************************************************************
		 * \brief Set the active GUI
		 * @param guiName
		 *
		 * This will set the active GUI but not the active window. This is useful
		 * for adding new window containers to a GUI but will not update the
		 * active window unless a new one is added.
		 * ****************************************************************************************************************************** */
		void GUI::setActiveGUI(std::string guiName) {
			activeGUI = guis[mapGUI[guiName]];
		}

		/*
		 * ==========================================================
		 *						Container
		 * ==========================================================
		 */
//		void GUI::ContainerInterface::pushData(std::string name, Object::Container *data) {
//			gui->activeContainer->containers.push_back(data);
//			uint id = gui->activeContainer->containers.size()-1;
//			gui->activeContainer->mapContainer.insert(make_pair(name, id));
//		}
//
//		void GUI::ContainerInterface::add(std::string containerName, Props c, Props *p) {
//			Object::Container * container;
//			if(p!=nullptr) container = new Object::Container(*p, c);
//			else container = new Object::Container(c);
//			container->init();
//			pushData(containerName, container);
//		}
//
//		void GUI::ContainerInterface::add(std::string containerName, Props *c, Props *p) {
//			Object::Container * container;
//			if(p!=nullptr) container = new Object::Container(*p, c);
//			else container = new Object::Container(c);
//			container->init();
//			pushData(containerName, container);
//		}

//		void GUI::ContainerInterface::hide(std::string containerName) {
//			uint containerID = gui->activeGUI->mapContainer[containerName];
//			gui->activeGUI->containers[containerID]->hide();
//		}

//		void GUI::ContainerInterface::show(std::string containerName) {
//			uint containerID = gui->activeGUI->mapContainer[containerName];
//			gui->activeGUI->containers[containerID]->show();
//		}

//		void GUI::ContainerInterface::toggle(std::string containerName) {
//			uint containerID = gui->activeContainer->mapContainer[containerName];
//			gui->activeContainer->containers[containerID]->toggle();
//		}
//
//		bool GUI::ContainerInterface::visible(std::string containerName) {
//			uint containerID = gui->activeContainer->mapContainer[containerName];
//			return gui->activeContainer->containers[containerID]->con->visibility;
//		}
//
//		Props * GUI::ContainerInterface::get(std::string containerName) {
//			uint containerID = gui->activeContainer->mapContainer[containerName];
//			return gui->activeContainer->containers[containerID]->con;
//		}
//
//		Props * GUI::ContainerInterface::get(std::string windowName, std::string containerName) {
//			uint windowID = gui->activeGUI->mapMasterWindow[windowName];
//			uint containerID = gui->activeGUI->masterWindows[windowID]->mapContainer[containerName];
//			return gui->activeContainer->containers[containerID]->con;
//		}
//
//		Props * GUI::ContainerInterface::get(std::string guiName, std::string windowName, std::string containerName) {
//			uint guiID = gui->mapGUI[guiName];
//			uint windowID = gui->guis[guiID]->mapMasterWindow[windowName];
//			uint containerID = gui->activeGUI->masterWindows[windowID]->mapContainer[containerName];
//			return gui->activeContainer->containers[containerID]->con;
//		}

		/*
		 * ==========================================================
		 *						Global
		 * ==========================================================
		 */
		void GUI::exec(std::string guiName) {
			uint guiID = mapGUI[guiName];

			// FIXME: Fine tune focus state, restrict input when editing fields (escape exits game when it should just cancel edit)
			// FIXME: Focus state sometimes gets stuck?
			/*
			 * Make focus send a masked value containing FOCUS_FIELD, FOCUS_TEXTEDIT, etc. Other
			 * 	objects can then also see this to prevent multiple objects from getting focus.
			 * External routine can then check this focus state to determine if local input
			 * 	should be disabled or not.
			 *
			 * GUIFocus should be static across ALL GUIs.
			 * Possibly create a separate focus just for different GUIs...not sure for what purpose but might be needed in future
			 *
			 */
			// Reset focus state
			iGUIFocus = 0;

			guis[guiID]->exec();

//			for (auto & container : guis[guiID]->containers) {
//
//				std::cout << "Executing Container '" << container->name << "' ";
//				std::cout << "(" << container->con->pos.constraint.x << ", " << container->con->pos.constraint.y << ")";
//				std::cout << "(" << container->con->pos.x << ", " << container->con->pos.y << ")";
//				container->exec();
//				std::cout << " Done\n";
//			}
		}
	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_H_ */
