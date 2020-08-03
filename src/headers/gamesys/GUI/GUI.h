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
 *  [ ] Incomplete
 * 	[X] Complete
 *  [/] Partially implemented
 *  [E] Error in trying to implement
 *
 *
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
 * 			- This breaks getPointer functionality returning a boolean to control things such as bEnable. Would have to make bEnable int and wastes a lot of memory to do that.
 * TODO: [E] Add a hover state to returnState.
 * 			- Requires above implementation which cannot be done easily
 * TODO: [X] Expand bEnable to have AND set and an OR set to allow better enable logic.
 * 			- All logic will work with ((enAND[0] && enAND[1] && ... enAND[7]) && (enOR[0] || enOR[1] || ... enOR[7])
 * 			- ANDs and ORs do not mix, all conditions must be met. (enAND && enOR)
 * TODO: [X] When an interactive item goes out of focus (window closed), revert changes and exit editing. May require external function call like updateValuePtr in GUI_Container.exec()
 * 			- Generally speaking, can't use ANY controls while an object is active, but this has been implemented anyways.
 * TODO: [X] If any item has focus, then disable object state updates for ALL other objects.
 * TODO: [X] Hover doesn't work on fields when tied to sliders and the slider is disabled
 * TODO: [X] Add STATE_UPDATE logic to all interactive objects
 * TODO: [c] valuePtr should be set from eObjectState
 * TODO: [X] Tooltip, create a base that is added to windows. On hover (if enabled) tooltip is shown, anchored to mouse.
 * 			[X] Floating text box
 * 			[X] Show box only when hovering over object (start with buttons only)
 * 			[X] Update Props according to quadrants
 * 			[X] Allow object to enable/disable tooltip (still only buttons)
 * 			[X] Draw tooltips in GUI_Container.h as separate function call
 * 			[X] Add tooltips to other GUI objects (add to Generic class in GUI_Objects.h?)
 * 			[X] Color Pallette settings for toolTip
 * 			[X] Implement label header, specifies name of calling object
 * TODO: [X] Autosize width/height for text based objects
 * 			[X] Option for auto Width (If word wrap enabled, then simply check if current size is smaller than a line of text.)
 * 			[X] Option for auto Height
 * TODO: [X] Add execToolTip() function to all objects. Needs to call nested toolTip.exec() functions.
 * TODO: [X] Add mstate mouse hover detection like in Button class.
 * TODO: [X] Add mouse state reset to all objects
 * TODO: [X] Plain Text (Use existing GUI_Text class) (TextArea already exists)
 * TODO: [X] Add AutoSize logic and include conditions to prevent drawing until sizing is complete
 * 			[X] Autosize to multiline text
 * 			[X] Autosize to labels - general single line text
 * 			[X] Autosize Fields
 * TODO: [X] Fix padding, especially when using relative size Props. (See Window settings label when adjusting window padding)
 * 			[X] Adjust width according to parent size and padding
 * 			[X] Center on parent
 * 			[X] Adjust center according to padding
 * 			[X] Add border size to padding (100% object should draw over border)
 * TODO: [C] Sliders won't release mouse when using integers.
 * 			- Apparently only for the DebugLight slider.
 * 			- Field interference?
 * 			- Conflict with a disabled field?
 * 			- Problem went away???
 * TODO: [E] Add a window background, with autosizing if possible, to Sliders
 * 			- Abort, this really isn't necessary and can't be automated so not worth it.
 * TODO: [X] Rename Props to Props (Properties) which is more accurate
 * TODO: [X] Disabling Fields on Sliders cause segfault (FIXED: execToolTip()/updateNoFocus() wasn't checking if field was enabled))
 * TODO: [X] Modify tooltip autosize to also look at label size
 * 				- The name of the tooltip, if shown, may be wider than the set tooltip text.
 * TODO: [E] Centering should take into account label and field on sliders if possible (don't think this is possible with the current setup)
 * 				- Can't do this, breaks slider alignment. Slider size should always be absolute
 * TODO: [E] Add a label header (like in tooltips) to windows.
 * 				- Cyclical problem with using a window to draw a label before window defined
 * TODO: [X] Add mouse hover detection to windows
 * 				- Interferes with other items for some reason. Likely relate to eObjectState but seems tied to mState.
 * TODO: [X] Progress Bar/Progress Spinner (classic spinning /|\-/|\- style)
 * 			[X] Show horizontal progress
 * 			[X] Allow progress percentage overlay (field)
 * 			[X] Create progress pallette
 * 			[X] Move progress bar properties into primary ProgressBar property to allow customization.
 * 			[X] Make progress percentage toggleable
 * 			[X] Make Field read-only (see TODO item below)
 * TODO: [X] Allow fields to be ready only without disable, this will allow custom coloring.
 * TODO: [X] Autoheight on textarea incorrect, drops last line.
 * TODO: [X] Update constraints colors to be in struct for cleaner access
 * TODO: [X] Allow sliders to have locally defined values instead of just pointers
 * TODO: [X] Tooltip Fixes
 * 			[X] Make tooltip bShowGlobal pointer capable so we can tie it to a button, should probably be static as well.
 * 			[X] Move show/hide delays into base Props, and make static. All tooltips should use same settings.
 * 			[X] Fields on sliders show tooltip even when not set
 *
 * TODO: [X] Fix slider CTRL mod to allow minimum step at least. Sometimes no movement on sliders using CTRL.
 * 			- General mod calculations should be fixed, minimum step should be the CTRL value.
 * 			- Maybe add a maximum step for SHIFT value?
 * 			- In that case, add a normal step value.
 * 			- setStep(min, normal, max)
 *
 * TODO: [X] Fields Fixes
 * 			[X] Allow local values
 *
 * TODO: [X] Drop down (Combo Box)
 * 			[X] Create new class
 * 				[X] Add Constraint definition
 * 				[X] Add to Containers
 * 			[X] Items should all be buttons
 * 				[X] Selected item should be a button showing current item, clicking button opens item list
 * 				[X] Buttons should be grouped so only one can be active, therefore item selection is automatic by group
 * 			[X] Fix grouping
 * 				[X] Revamp group system to allow adding by name, discard int groups
 * 				[X] Add an option to buttons to require at least one item set
 * 					[X] Do a check in group logic, do not allow button deactivation by mouse, can only activate a different button
 * 			[X] Draw Selected Item
 * 				[X] Button
 * 				[X] Clicking button opens item list
 * 			[X] Draw Item list
 * 				[X] Draw window container
 * 				[X] Draw button for each item
 * 				[X] Highlight Label on mouse hover
 * 				[X] Set to selected when clicked
 * 			[X] Rework Integration
 * 				[X] A starting item should be specified at creation with add() funciton
 * 				[X] Auto size? If not then disable auto size access.
 * 				[X] Enable/Disable autohide
 * 					[X] If mouseclick while !STATE_FOCUS, close list
 * 				[X] Add [] overload for modifying existing item list (Button access)
 * 				[X] Add () overload to get current item
 * 				[X] Add function to set selected item
 * 				[X] Item list should overlap by border size (prevents auto-hide issues)
 * 					- Fixed by adjusting gmath tests to be properly inclusive
 * 			[X] Item List size
 * 				[X] Auto size according to number of items (preliminary setup before adding restrictions below)
 * 				[X] Number of items to show
 * 				[X] Current scrollIndex
 * 				[X] Indicator that more items are on list (up/down)
 * 					[X] When items exist down, last item is replaced with a down indicator
 * 						- Item added to beginning of list
 * 					[X] When items exist up, first item is replaced with a up indicator
 * 						- Item added to end of list
 * 					[X] Indicators are repeating buttons for scrolling
 * 					[X] Mousewheel can scroll items
 * 			[X] Add autohide
 * 				[X] Monitor focus of itemList
 * 				[X] If mouse hover, then mouse leaves, auto hide.
 * 			[X] Access Functions
 * 				[X] Add new item
 * 				[X] Remove item (maybe not do this, possible complications?)
 * 				[X] SetItem (set item return states)
 * 				[X] GetItem (get the selected item return states)
 * 			[X] Additional Fixes
 * 				[X] STATE_ACTIVE should be used for showing list and selecting items
 *
 * TODO: [X] Fix progress bar not working, likely related to valuePtr changes
 *
 * TODO: [X] Modify Props_Addon_ReturnState to allow multiple types, instead of just int
 * 			[X] Fix buttons to return bool state by default, separate from returnState
 * 				[X] change return state to rely only on STATE_ACTIVE bit
 * 				[X] How to integrate valuePtr?
 * 					[X] Make valuePtr a BOOL only, remove valuePtr template from Interactive class
 * 					[X] Always use bool for object state, even sliders
 * 					[X] Sliders have an additional internal valuePtr for controlled value (can still use returnStates separately)
 * 					[X] Sliders return true whenever they are actively being changed
 * 				[X] updateValuePtr() needs to be fixed/removed...
 * 			[X] Fix DataSets
 * 				[X] Allow Set On Off states using (...) [Using std::vector for type safe]
 * 				[X] Change DataSet to vector
 * 				[X] Change DataSet to std::variant
 * 				[X] Update groupState() return in GUI_Container
 * 				[X] Objects need to specify the dataset return key (name of dataset object) absolutely required for groups.
 * 				[X] Every object has its own "On/Off" state designations
 * 			[X] Use a separate access function for returnState
 * 			[X] Change interactive class to return bool state (Template)
 * 			[X] If bool state is true then return on values for returnState
 * 			[X] If bool state is false then return off values for returnState
 *
 * TODO: [X] All items such as buttons, get their text from their object name, separate into object name and text
 * 			[X] Buttons
 * 			[X] Labels
 * 			[X] CheckBox
 * 			[X] ColorSwatch
 * 			[X] ComboBox
 * 			[X] Field
 * 			[X] Icon
 * 			[X] ProgressBar
 * 			[X] Slider
 * 			[X] Sprite
 * 			[X] Text?
 * 			[X] TextArea?
 * 			[X] TextEdit?
 *
 * TODO: [ ] Scrolling Window - This might be difficult
 * 			[X] Scrolling text window
 * 			[X] Can use glScissor and glEnable/Disable(GL_SCISSOR_TEST). Use Window minus padding for drawable area.
 * 			[ ] Apply scrolling (per-pixel) to windows
 * 				[X] Create x/y offset pointers
 * 					[X] If object has a parent, then assign pointers to parent object
 * 					[X] If object doesn't have parent, then create local copy to be used as a parent
 * 					[X] Now all children automatically have the parent window scroll offset
 * 				[X] Enable Disable scrolling
 * 					[X] Mouse based scrolling
 * 					[X] External control (disable mouse but still update scrolling data) (Use to make a slide-in window?)
 *				[X] Manage wheel mouse scrolling
 * 				[X] Add check to glScissor area, ignore input outside scissor area for nested objects
 * 					[X] Use the STATE_FOCUS concept. if mouse is in glScissor area then enable objects.
 * 						- bActive added to scissor stack items, set with checkInput function
 * 				[X] Scroll position (int)
 * 				[ ] Maximum scroll position
 * 					[ ] Auto-calc somehow?
 * 					[X] Set by user
 * 				[X] Window scrolling disabled when any object is active
 * 					[X] If Interactive_Base::bFocusPresent then don't scroll
 * 					[X] If an object has hover (slider, field, etc) then don't scroll (add new static to Base::Interactive)
 * 					[X] Make ComboBox report active state
 * 					[X] Duplicate object names break scroll lock, need to create some sort of unique object ID (timestamp?)
 * 					[X] Make object IDs part of a global static database so we can check for duplicates (use t_Vector)
 *
 * TODO: [X] Change Props to pass by reference in GUI_Container
 *
 * TODO: [ ] Keyboard Control
 * 			[ ] Add a global GUI keyboard (static)
 * 			[ ] Generally disabled until an object requests interaction
 *
 * TODO: [ ] Update objects to use AnyType
 * 			- This is difficult to implement with pointers to non-AnyType values
 * 			  so this should probably not be done and just keep original system.
 * 			[E] Fields (t_BIFS)
 * 			[E] Sliders	(t_BIF, can we implement Bool? Would be a cool way to make a slider switch, but int essentially already does this)
 * 			[ ] Separate slider into separate type definitions?
 * 				- Copies of Slider such as SliderInt, SliderFloat, SliderBool instead of AnySlider.
 * 			[ ] Separate fields in to FieldInt, FieldBool, FieldFloat, FieldString
 * 			[ ] Or use GUI_Container templates for access to each type
 *
 * TODO: [ ] Slider2D - Like a slider but uses a point in 2D space controlling 2 values at once
 * 			[ ] Box for selection area (window using standard Props)
 * 			[ ] X-Axis Range (min, max), integer only
 * 			[ ] Y-Axis Range (min, max), integer only
 * 			[ ] Track mouse and mapped X-Y values (relative (0,0) is always bottom left.)
 * 			[ ] Show point (slider control, square) on current value coordinates
 * 			[ ] Clicking mouse/holding mouse sets values
 * 			[ ] Create float version
 *
 * TODO: [ ] Pie Chart
 * 			[ ] Draw triangles for each quantity, larger than circle area
 * 			[ ] Use shader to procedurally drop fragments outside circle area
 * 			[ ] Allow donut style as well, drop outer circle and smaller inner circle
 * 			[ ] Legend anchored externally to chart (L/TL/T/TR/R/BR/B/BL)
 *
 * TODO: [ ] Animation - Use animation system except draw with Props system to screen.
 * 			  - Animation can be repeating or one-shot controlled
 *
 * TODO: [ ] Check all object init() functions
 * 			[ ] Make sure all nested properties are being assigned by reference and not making local copies
 *
 * TODO: [ ] Change Map_si (t_Vector)
 * 			[X] Change from type to class containing both mapping and template vector for data type 'std::vector<T>'
 * 			[X] Create addItem(string/int)
 * 			[ ] Create removeItem(string/int)
 * 			[X] Create getID(string)
 * 			[ ] Create getString(id)
 * 			[X] Create getSize() function to return exact size
 * 			[X] Implement throw() for invalid access
 * 			[ ] Implement into systems using Map_si
 * 				[ ] Core
 * 					[ ] Colors
 * 					[ ] FBO
 * 					[ ] Occlusion
 * 					[ ] Particles
 * 					[ ] PTimer
 * 					[ ] Stipple
 * 					[ ] Texture
 * 				[ ] GameSys
 * 					[ ] Flora (flora is currently broken in the particle system)
 * 					[ ] Satellite
 * 					[X] GUI
 * 					[X] GUI_Container
 * 					[X] GUI_ComboBox
 * 					[ ] TextSys
 *
 * TODO: [X] Create a Scissor coordinates stack
 *			[X] Push onto stack
 *				- Includes enable/disable
 *				- A disable stack does not require x,y,w,h
 *			[X] Pop from stack
 *			[X] exec stack
 *				- If nothing on stack, do not enable
 *
 * TODO: [ ] Window padding should automatically take border size into account?
 * 			- How does this work for negative? Ignore border?
 *
 * TODO: [ ] Add STATE_FOCUS handler to all objects
 *
 * TODO: [ ] Object Sprites
 * 				[X] Allow a window to use a texture sprite instead of drawing generic quad
 * 					- Can already kinda be done with invisible window and 100% relative sprite
 * 				[ ] Allow buttons to use sprites with base, active, and hover states. Maybe create a new button class? (ImageButton)
 *
 * TODO: [ ] Implement Scissoring on all objects
 * 			- Scissoring window is the objects window minus any padding.
 * 				- Objects drawn outside the window will no longer be visible
 * 				- Don't apply scissor to additional objects such as labels and fields.
 * 			- Scissor coordinates calculated in constrants exec?
 * 			[X] Allow scissoring to be disabled (So you can draw additional windows with another window as parent)
 * 			[ ] Scissor stack
 * 				[ ] Create a simple Scissor class
 * 				[ ] Use a Push and coordinates to set the current scissor area
 * 				[ ] Use Pop to return to the previous scissor area
 * 				[ ] Monitor for overflow/underflow of push/pop
 * 				[ ] Add an enable/disable option; Global and per stack item, so a Push can simply disable scissor for that item
 *
 * TODO: [ ] GUI focus handing like button groups, GUI name defines focus group.
 * 			- Group focus allows window layers that won't interfere with each other.
 * 			- Focus is set/reset by code conditions. (Button opens GUI and activates focus, Close button closes GUI and releases focus. Use a STACK.)
 * 			[ ] Create a GUI stack
 * 				- Vector of strings (name of GUI) [STACK]
 * 				- Map of name to vector index
 * 			[ ] GUI.Push(<string>) function to add GUI name to stack
 * 			[ ] GUI.Pop() function removes current GUI from top of stack
 * 			[ ] Add a GUI.exec() function to execute GUIs on the GUI stack
 * 				[ ] Execute stack in order
 * 				[ ] Only top of stack accepts input
 *
 * TODO: [ ] Add copy constructor and assignment operator to all Props
 * 			  - Copy: <class>(const <class> &src) { var = new <class>; *var = src; }
 * 			  - Assignment: <class> &operator=(const <class> &src) { var = new <class>; *var = src; return *this; }
 * 			  - Inherited Assignment: <class>::operator=(src);
 * 			[ ] t_DataSet
 * 			[ ] t_Vector
 * 			[ ] Buttons
 * 			[ ] Labels
 * 			[ ] CheckBox
 * 			[ ] ColorSwatch
 * 			[ ] ComboBox
 * 			[ ] Field
 * 			[ ] Icon
 * 			[ ] ProgressBar
 * 			[ ] Slider
 * 			[ ] Sprite
 * 			[ ] Text
 * 			[ ] TextArea
 * 			[ ] TextEdit
 * 			[ ] Container
 * 			[ ] Window
 * 			[ ] GUI
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
				Core::t_VectorMap<GUI_Container*> guis;		///< Master GUI containers
				//Core::t_Vector<std::string> IDs;			///< Unique object IDs
//				static std::vector<std::string> IDs;		///< Unique object IDs

			public:
				GUI();
				virtual ~GUI();
				GUI_Container	* activeGUI;
				void createGUI(std::string guiName);
				void createGUI(std::string guiName, Props_Window &c);
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
				GUI_Container	&operator[](const std::string &guiName)	{	return *guis[guiName];	}
		};

		int GUI::iGUIFocus = 0;
//		std::vector<std::string> GUI::IDs;

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
			c.colorBack.base = &colors[colors().Transparent];
			c.colorBorder.base = &colors[colors().Transparent];
			c.bNoInput = true;

			GUI_Container * gui = new GUI_Container(guiName, c);
			gui->init();
			guis.add(guiName, gui);
			setActiveGUI(guiName);
		}

		/** ******************************************************************************************************************************
		 *
		 * @param guiName
		 * @param c
		 * ****************************************************************************************************************************** */
		void GUI::createGUI(std::string guiName, Props_Window &c) {
			GUI_Container * gui = new GUI_Container(guiName, c);
			guis.add(guiName, gui);
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
			return guis[guiName]->con;
		}

		/** ******************************************************************************************************************************
		 * \brief Set the active GUI
		 * @param guiName
		 *
		 * This will set the active GUI but not the active window. This is useful
		 * for adding new window containers to a GUI but will not update the
		 * active window unless a new one is added.
		 * ****************************************************************************************************************************** */
		void GUI::setActiveGUI(std::string guiName) {
			activeGUI = guis[guiName];
		}

		void GUI::exec(std::string guiName) {
			//uint guiID = mapGUI[guiName];

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

			guis[guiName]->exec();
		}
	}

































} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_H_ */





























