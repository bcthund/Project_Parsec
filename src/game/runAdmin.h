/*
 * runAdmin.h
 *
 *  Created on: Sep 18, 2010
 *      Author: bcthund
 */

#ifndef RUNADMIN_H_
#define RUNADMIN_H_

#include <iostream>
#include "../headers/core/core_functions.h"
#include "../headers/core/types.h"
#include "../headers/core/Groups.h"

/** \class _Admin
 *
 * This class is a primary game class that runs when the
 * admin menu is opened. It opens on top of all other
 * systems but allows other systems to still run. This
 * allows variables to be adjusted when the game world
 * is still being drawn allowing real-time feedback of
 * things such as the terrain generator.
 *
 */

class _Admin {
	private:

		// Special enum structure for managing menu levels
		enum eADMIN_MENU {	ADMIN_MAIN,
							ADMIN_GAMESTATE,
							ADMIN_TIMERS,
							ADMIN_SCREEN,
								SCREEN_BLUR,
								SCREEN_STEREO,
							ADMIN_RENDER,
							ADMIN_FONT,
								FONT_COLOR_1,
								FONT_COLOR_2,
								FONT_COLOR_3,
								FONT_COLOR_4,
							ADMIN_TRANSFORM,
							ADMIN_GAMETIME,
							ADMIN_ATMOSPHERE,
								ATMOSPHERE_SUN,
								ATMOSPHERE_MOON,
								ATMOSPHERE_RAIN,
								ATMOSPHERE_SNOW,
								ATMOSPHERE_HAIL,
								ATMOSPHERE_FLORA,
								ATMOSPHERE_UWFLORA,
								ATMOSPHERE_GRASS,
								ATMOSPHERE_WATER,
							ADMIN_CONTROLS,
								CONTROLS_MOUSE,
								CONTROLS_KEYBOARD,
								CONTROLS_WORLDMENU,
								CONTROLS_JOURNAL,
								CONTROLS_BATTLESCROLL,
								CONTROLS_GRIMOIRE,
								CONTROLS_VORNICHT,
								CONTROLS_SKILLWHEEL,
								CONTROLS_FKEYS,
							ADMIN_CHARSHEET,
								CHARSHEET_SHEET1,
								CHARSHEET_SHEET2,
								CHARSHEET_DAMAGE,
								CHARSHEET_MAGIC,
							ADMIN_SHADER,
							ADMIN_DIR,
							ADMIN_SIZE,
							ADMIN_DEBUG };

		_Game				*game;
		Core::_Keyboard		keyboard;

		GLenum				eMenu;
		std::string			command;
		static const int	ONESHOTS = 64;
		bool				bOneShot[ONESHOTS];
		bool				bHasFocus;
		bool				bFirstRun;
		int					iBy;			// Position of the back button
		int					iVx;			// Position of variables
		int					iTx;			// Position of text

		void ProcessInput();
		void GetInput();
		void draw();
		struct t_AutoPos {
			struct {
				int start;
				int pos;
				int add;
				int interval;
				int count;
				int step;
				int stepCount;
			} x, y;

			t_AutoPos() {
				x.count		= 0;
				x.start		= 0;
				x.pos		= 0;
				x.add		= 0;
				x.interval	= 0;
				x.step		= 0;
				x.stepCount	= 0;

				y.count		= 0;
				y.start		= 0;
				y.pos		= 0;
				y.add		= 0;
				y.interval	= 0;
				y.step		= 0;
				y.stepCount	= 0;
			}

			void SetX(int reset, int pos, int add, int interval, int step=0) {
				x.count		= 0;
				x.start		= reset;
				x.pos		= pos;
				x.add		= add;
				x.interval	= interval;
				x.step		= step;
				x.stepCount	= 0;
			}

			void SetY(int reset, int pos, int add, int interval, int step=0) {
				y.count		= 0;
				y.start		= reset;
				y.pos		= pos;
				y.add		= add;
				y.interval	= interval;
				y.step		= step;
				y.stepCount	= 0;
			}

			int AddX() {
				int ret = x.pos;
				if(x.stepCount>=x.step-1) {
					if(x.count<x.interval-1) {
						x.pos += x.add;
						x.count++;
					}
					else {
						x.pos = x.start;
						x.count = 0;
					}
					x.stepCount = 0;
				}
				else {
					x.stepCount++;
				}
//				return x.pos;
				return ret;
			}

			int AddY() {
				int ret = y.pos;
				if(y.stepCount>=y.step-1) {
					if(y.count<y.interval-1) {
						y.pos += y.add;
						y.count++;
					}
					else {
						y.pos = y.start;
						y.count = 0;
					}
					y.stepCount = 0;
				}
				else {
					y.stepCount++;
				}
				return ret;
//				return y.pos;
			}

		} AutoPos;

	public:
		_Admin(_Game *gamePtr);
		void init();
		void initSkillTree();
		void initColors();
		void run();
		bool bInit;
};

_Admin::_Admin(_Game *gamePtr) :
					eMenu(ADMIN_MAIN),
					iBy(53),
					iTx(3),
					iVx(24) {

	bInit = false;
	game = gamePtr;

	bHasFocus = true;
	bFirstRun = true;

	for(int n=0; n<ONESHOTS; n++) {
		bOneShot[n] = false;
	}

	keyboard.calc(Core::_Keyboard::KEYTYPE_ONESHOT);
}

#include "runAdmin/SkillTree.h"
//#include "runAdmin/Colors.h"

/** ******************************************************************************************************************************
 *
 *  ****************************************************************************************************************************** */
void _Admin::init() {
	// GUI - Master container

	if (!bOneShot[0]) {
		std::cout << "GUI: Loading #00: Master Container ............................. ";
		//std::cout << "...............................................................";
		Core::gui.createGUI("GameMenu");
		bOneShot[0] = true;
		std::cout << "Done" << std::endl;
	}

	// Blank Window, parameter testing
	if (!bOneShot[1]) {
		std::cout << "GUI: Loading #01: Windows ...................................... ";
		//std::cout << "...............................................................";
		Core::GUI::Props_Window cMaster;
		cMaster.setOrigin(Core::GUI::CONSTRAIN_TOP_RIGHT);
		cMaster.setAnchor(Core::GUI::CONSTRAIN_TOP_RIGHT);
		cMaster.setPos(-10, -10);
		cMaster.setWidth(500, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
//		cMaster.setWidth(40, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		cMaster.setHeight(550, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		cMaster.setPadding(10);
		cMaster.setVisibility(true);
		Core::gui["GameMenu"].add("Window 0", cMaster);

		cMaster.setVisibility(false);
		cMaster.setScrollable();
		Core::gui["GameMenu"].add("Window 1", cMaster);
		Core::gui["GameMenu"].add("Window 3", cMaster);
		Core::gui["GameMenu"].add("Window 4", cMaster);
		Core::gui["GameMenu"].add("Window 5", cMaster);
		Core::gui["GameMenu"].add("Window 6", cMaster);
		Core::gui["GameMenu"].add("Window 7", cMaster);
		Core::gui["GameMenu"].add("Window 8", cMaster);
		Core::gui["GameMenu"].add("Window 9", cMaster);
		Core::gui["GameMenu"].add("Window 10", cMaster);
		cMaster.setStipple(true);
		Core::gui["GameMenu"].add("Window 12", cMaster);
		cMaster.setStipple(false);
		Core::gui["GameMenu"].add("Window 11", cMaster);
		Core::gui["GameMenu"].add("Window 13", cMaster);
		Core::gui["GameMenu"].add("Window 14", cMaster);
		cMaster.setWidth(1050, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		Core::gui["GameMenu"].add("Window 15", cMaster);
		cMaster.setWidth(500, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		Core::gui["GameMenu"].add("Window 16", cMaster);
		Core::gui["GameMenu"].add("Window 17", cMaster);
		Core::gui["GameMenu"].add("Window 18", cMaster);
//		cMaster.setScrollable();
		Core::gui["GameMenu"].add("Window 19", cMaster);
//		cMaster.resetScrollable();
		Core::gui["GameMenu"].add("Window 20", cMaster);
		Core::gui["GameMenu"].add("Window 21", cMaster);


		cMaster.setOrigin(Core::GUI::CONSTRAIN_TOP_RIGHT);
		cMaster.setAnchor(Core::GUI::CONSTRAIN_TOP_RIGHT);
		cMaster.setPos(-510, -10);
		cMaster.setWidth(750, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
//		cMaster.setWidth(50, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		cMaster.setHeight(550, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		Core::gui["GameMenu"].add("Window 14-0", cMaster);

//		cMaster.setOrigin(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
//		cMaster.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
//		cMaster.setHeight(150, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		Core::gui["GameMenu"].add("Window 14-1", cMaster);
		Core::gui["GameMenu"].add("Window 14-2", cMaster);
		Core::gui["GameMenu"].add("Window 14-3", cMaster);
		Core::gui["GameMenu"].add("Window 14-4", cMaster);
		Core::gui["GameMenu"].add("Window 14-5", cMaster);
		Core::gui["GameMenu"].add("Window 14-6", cMaster);
		Core::gui["GameMenu"].add("Window 14-7", cMaster);
		Core::gui["GameMenu"].add("Window 14-8", cMaster);
		bOneShot[1] = true;
		std::cout << "Done" << std::endl;
	}

//	throw std::runtime_error("Abort");


	if (!bOneShot[2]) {
		std::cout << "GUI: Loading #02: Button window ................................ ";
		//std::cout << "...............................................................";
		Core::GUI::Props_Window con;
		con.setOrigin(Core::GUI::CONSTRAIN_TOP_RIGHT);
		con.setAnchor(Core::GUI::CONSTRAIN_TOP_RIGHT);
		con.setPos(-10, -560);
		con.setWidth(500, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
//		con.setWidth(40, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		con.setHeight(100, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		con.setBorder(1, true);
		con.setRadius(5);
		con.setVisibility(true);
		con.setPadding(5);
		con.setStipple(true);
		con.setStipplePattern(&Core::stipple[Core::stipple.STIPPLE_DOTS]);
		Core::gui["GameMenu"].add("Window 2", con);
//		Core::gui->Window.add("Window 2", con);		// General Buttons Menu
		bOneShot[2] = true;
		std::cout << "Done" << std::endl;
	}

	// Label Testing
	if (!bOneShot[3]) {
		std::cout << "GUI: Loading #03: Label ........................................ ";
		//std::cout << "...............................................................";
		Core::GUI::Props_Label con;
		con.setOrigin(Core::GUI::CONSTRAIN_TOP|Core::GUI::CONSTRAIN_CENTER);
		con.setAnchor(Core::GUI::CONSTRAIN_TOP);
		con.setPos(0, 0);
		con.setWidth(100, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		con.setHeight(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		con.enablePadding(Core::GUI::PADDING_ALL);
		con.setMinWidth(100);
		con.showBackground();
		con.colorBack.base = &Core::colors[Core::colors().Gray_web];
//		con.setLabelAutoSize(true, true);
		//con.autoWidth(false);
		//con.autoHeight(true);

//		Core::gui->Label.addTo("Window 0", "Window 0", con);
		Core::gui["GameMenu"]["Window 0"].Label.add("Window 0", con);
		Core::gui["GameMenu"]["Window 1"].Label.add("Window 1", con);
		Core::gui["GameMenu"]["Window 3"].Label.add("Window 3", con);
		Core::gui["GameMenu"]["Window 4"].Label.add("Window 4", con);
		Core::gui["GameMenu"]["Window 5"].Label.add("Window 5", con);
		Core::gui["GameMenu"]["Window 6"].Label.add("Window 6", con);
		Core::gui["GameMenu"]["Window 7"].Label.add("Window 7", con);
		Core::gui["GameMenu"]["Window 8"].Label.add("Window 8", con);
		Core::gui["GameMenu"]["Window 9"].Label.add("Window 9", con);
		Core::gui["GameMenu"]["Window 10"].Label.add("Window 10", con);
		Core::gui["GameMenu"]["Window 11"].Label.add("Window 11", con);
		Core::gui["GameMenu"]["Window 12"].Label.add("Window 12", con);
		Core::gui["GameMenu"]["Window 13"].Label.add("Window 13", con);
		Core::gui["GameMenu"]["Window 14"].Label.add("Window 14", con);
		Core::gui["GameMenu"]["Window 14-1"].Label.add("Window 14-1", con);
		Core::gui["GameMenu"]["Window 15"].Label.add("Window 15", con);
		Core::gui["GameMenu"]["Window 16"].Label.add("Window 16", con);
		Core::gui["GameMenu"]["Window 17"].Label.add("Window 17", con);
		Core::gui["GameMenu"]["Window 18"].Label.add("Window 18", con);
		Core::gui["GameMenu"]["Window 19"].Label.add("Window 19", con);
		Core::gui["GameMenu"]["Window 20"].Label.add("Window 20", con);
		Core::gui["GameMenu"]["Window 21"].Label.add("Window 21", con);

		bOneShot[3] = true;
		std::cout << "Done" << std::endl;
		std::cout << "Skipping #04-19" << std::endl;
	}

	// Button Testing
	if (!bOneShot[20]) {
		std::cout << "GUI: Loading #20: Menu Buttons ................................. ";
		//std::cout << "...............................................................";
		// Accept Button
		Core::GUI::Props_Button con_button;
		con_button.setHeight(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);				// Exact button height
		con_button.setBorder(1, true);
		con_button.setRadius(10);
		con_button.setButtonType(Core::GUI::BUTTON_TOGGLE);
		con_button.setOrigin(Core::GUI::CONSTRAIN_LEFT|Core::GUI::CONSTRAIN_BOTTOM);
		con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM|Core::GUI::CONSTRAIN_LEFT);		// Center of button
		con_button.setPos(5, 5);
		con_button.setWidth(150, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);				// Exact button width
		Core::gui["GameMenu"]["Window 3"].Button.add("Toggle Simplex", &Core::gameVars->debug.gui.b1, con_button);
		Core::gui["GameMenu"]["Window 4"].Button.add("Toggle Fractal", &Core::gameVars->debug.gui.b2, con_button);

		con_button.modPos(155, 0);
		Core::gui["GameMenu"]["Window 3"].Button.add("Show Norms", &Core::gameVars->debug.gui.b5, con_button);
		//Core::gui["GameMenu"]["Window 4"].Button.add("Update Fractal", &Core::gameVars->debug.gui.b4, con_button);

		con_button.setButtonType(Core::GUI::BUTTON_ONESHOT);
		con_button.modPos(155, 0);
		Core::gui["GameMenu"]["Window 3"].Button.add("Update Simplex", &Core::gameVars->debug.gui.b3, con_button);
		Core::gui["GameMenu"]["Window 4"].Button.add("Update Fractal", &Core::gameVars->debug.gui.b4, con_button);

		// Navigation buttons
		con_button.setButtonType(Core::GUI::BUTTON_TOGGLE);
		con_button.setOrigin(Core::GUI::CONSTRAIN_TOP);
		con_button.setAnchor(Core::GUI::CONSTRAIN_TOP);
		con_button.setWidth(20, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		con_button.setHeight(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		con_button.setBorder(1, true);
		con_button.setRadius(10);
		con_button.setGroup(Core::groups.add("Menu Buttons", true));
		con_button.enablePadding(Core::GUI::PADDING_ALL);
		con_button.enableToolTip();

		con_button.setToolTip("\xB2Modify Simplex Noise generator\n"\
							  "values for terrain.\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2\xB2");
		con_button.setPos( -196,   0);	Core::gui["GameMenu"]["Window 2"].Button.add("Simplex",			false, con_button);
		con_button.setToolTip("Modify Fractal Noise generator\n"\
							  "values for terrain.");
		con_button.setPos(  -98,   0);	Core::gui["GameMenu"]["Window 2"].Button.add("Fractal",			false, con_button);
		con_button.setToolTip("What is this?");
		con_button.setPos(    0,   0);	Core::gui["GameMenu"]["Window 2"].Button.add("Labels",			false, con_button);
		con_button.setToolTip("Adjust lighting values for\n"\
							  "all light sources.");
		con_button.setPos(   98,   0);	Core::gui["GameMenu"]["Window 2"].Button.add("Lighting",		false, con_button);
		con_button.setToolTip("Sample skill tree with classes and\n"\
							  "branching to simulate ideas from the\n"\
							  "original skill wheel.");
		con_button.setPos(  196,   0);	Core::gui["GameMenu"]["Window 2"].Button.add("Skill Tree",		false, con_button);

		con_button.setToolTip("CheckBox testing, as well as parent\n"\
							  "and value settings by adjusting the\n"\
							  "origin and anchor of a label.");
		con_button.setPos( -196, -20);	Core::gui["GameMenu"]["Window 2"].Button.add("CheckBox", 		false, con_button);
		con_button.setToolTip("Variations in sliders label and field\n"\
							  "positions, as well as min/max values,\n"\
							  "and horizontal and vertical orientations.");
		con_button.setPos(  -98, -20);	Core::gui["GameMenu"]["Window 2"].Button.add("Sliders",			false, con_button);
		con_button.setToolTip("Static text box as well as an\n"\
							  "editable text box. Also shows\n"\
							  "scrollbar with scroll buttons.");
		con_button.setPos(    0, -20);	Core::gui["GameMenu"]["Window 2"].Button.add("Text Boxes",		false, con_button);
		con_button.setToolTip("Example of color swatches that adjust\n"\
							  "window and button pallette.");
		con_button.setPos(   98, -20);	Core::gui["GameMenu"]["Window 2"].Button.add("Colors",			false, con_button);
		con_button.setToolTip("Display of all available built in\n"\
							  "colors in HUE grid.");
		con_button.setPos(  196, -20);	Core::gui["GameMenu"]["Window 2"].Button.add("ColorBox",		false, con_button);

		con_button.setToolTip("Adjustment of window constraints\n"\
							  "inclduing border style, and window\n"\
							  "padding.");
		con_button.setPos( -196, -40);	Core::gui["GameMenu"]["Window 2"].Button.add("Settings",		false, con_button);
		con_button.setToolTip("Simple icons that can be toggled.");
		con_button.setPos(  -98, -40);	Core::gui["GameMenu"]["Window 2"].Button.add("Icons",			false, con_button);
		con_button.setToolTip("Images that do not have interactive\n"\
							  "capabilities.");
		con_button.setPos(    0, -40);	Core::gui["GameMenu"]["Window 2"].Button.add("Images",			false, con_button);
		con_button.setToolTip("All available stipple decoration\n"\
							  "patterns that can be applied to\n"\
							  "any window. Windows are the base\n"\
							  "of nearly all objects.");
		con_button.setPos(   98, -40);	Core::gui["GameMenu"]["Window 2"].Button.add("Stipple",			false, con_button);
		con_button.setToolTip("Preliminary design for a color chooser\n"\
							  "showing all available built-in colors.");
		con_button.setPos(  196, -40);	Core::gui["GameMenu"]["Window 2"].Button.add("ColorPicker",		false, con_button);

		con_button.setToolTip("Window with object set outside the window\n"\
							  "to show scissoring effect on components.");
		con_button.setPos( -196, -60);	Core::gui["GameMenu"]["Window 2"].Button.add("Scissor",			false, con_button);
		con_button.setToolTip("None.");
		con_button.setPos(  -98, -60);	Core::gui["GameMenu"]["Window 2"].Button.add("Progress Bar",	false, con_button);
		con_button.setToolTip("None.");
		con_button.setPos(    0, -60);	Core::gui["GameMenu"]["Window 2"].Button.add("ComboBox",		false, con_button);
		con_button.setToolTip("None.");
		con_button.setPos(   98, -60);	Core::gui["GameMenu"]["Window 2"].Button.add("Spare 4",			false, con_button);
		con_button.setToolTip("None.");
		con_button.setPos(  196, -60);	Core::gui["GameMenu"]["Window 2"].Button.add("Spare 5",			false, con_button);



		Core::gui["GameMenu"]["Window 2"].Button["Labels"].setEnableA(false, 0);

		bOneShot[20] = true;
		std::cout << "Done" << std::endl;
	}

	// No parent button (Toggle Menu)
////	if (!bOneShot[21]) {
////		std::cout << "Loading #21: Toggle Menu Button ... ";
////		Core::GUI::Props_Button con_button;
////		con_button.setOrigin(Core::GUI::CONSTRAIN_BOTTOM|Core::GUI::CONSTRAIN_RIGHT);
////		con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM|Core::GUI::CONSTRAIN_RIGHT);		// Center of button
////		con_button.setPos(-20, 20);
////		con_button.setWidth(120, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);				// Exact button width
////		con_button.setHeight(30, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);				// Exact button height
////		con_button.setBorder(1, true);
////		con_button.setRadius(10);
//////		con_button.setOneShot(true);
////		con_button.setButtonType(Core::GUI::BUTTON_ONESHOT);
////		Core::gui->Button.addTo("Toggle Menu", con_button);
////		bOneShot[21] = true;
////		std::cout << "Done" << std::endl;
////	}

	// Slider Simplex
	if (!bOneShot[22]) {
		std::cout << "GUI: Loading #22: Simplex Sliders .............................. ";
		//std::cout << "...............................................................";
		Core::GUI::Props_Slider con;
		con.setOrigin(Core::GUI::CONSTRAIN_CENTER|Core::GUI::CONSTRAIN_BOTTOM);
		con.setAnchor(Core::GUI::CONSTRAIN_CENTER);					// Center of button
		con.setWidth(50, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		con.setHeight(4, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		con.showField();
		con.showLabel();
		con.setPrecision(5);
		con.setX(25);
		con.control.setWidth(8, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		con.control.setHeight(16, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);

		//
		con.setY(490);
		con.setMinMax(0, 1);
		con.setStep(1.0f, 2.0f, 10.0f);
		Core::gui["GameMenu"]["Window 3"].Slider.add("Simplex Generator", &Core::gameVars->debug.noise.iCurrentSimplex, con);

		//
		con.setY(440);
		con.setMinMax(8.0f, 2048.0f);
		con.setStep(1.0f, 2.0f, 10.0f);
		Core::gui["GameMenu"]["Window 3"].Slider.add("Resolution", &Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].res, con);

		//
		con.setY(410);
		con.setMinMax(1.0f, 1000.0f);
		con.setStep(1.0f, 2.0f, 10.0f);
		Core::gui["GameMenu"]["Window 3"].Slider.add("Tex Scale", &Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].tex_scale, con);

		//
		con.setY(380);
		con.setMinMax(1.0f, 100000.0f);
		con.setStep(1.0f, 10.0f, 100.0f);
		Core::gui["GameMenu"]["Window 3"].Slider.add("Terrain Size", &Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].terrain_size, con);

		// Offset X
		con.setY(350);
		con.setMinMax(-10000.0f, 10000.0f);
		con.setStep(1.0f, 10.0f, 100.0f);
		Core::gui["GameMenu"]["Window 3"].Slider.add("Terrain Height", &Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].terrain_height_offset, con);

		// Offset X
		con.setY(300);
		con.setMinMax(-10000.0f, 10000.0f);
		con.setStep(1.0f, 10.0f, 100.0f);
		Core::gui["GameMenu"]["Window 3"].Slider.add("Offset X", &Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].offset.x, con);

		// Offset Y
		con.setY(270);
		con.setMinMax(-10000.0f, 10000.0f);
		con.setStep(1.0f, 10.0f, 100.0f);
		Core::gui["GameMenu"]["Window 3"].Slider.add("Offset Y", &Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].offset.y, con);

		// Delta
		con.setY(240);
		con.setMinMax(1.0f, 100.0f);
		con.setStep(1.0f, 2.0f, 10.0f);
		Core::gui["GameMenu"]["Window 3"].Slider.add("Delta", &Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].delta, con);

		// Frequency
		con.setY(210);
		con.setMinMax(-0.001f, 0.001f);
		con.setStep(0.00001f, 0.00005f, 0.0001f);
		Core::gui["GameMenu"]["Window 3"].Slider.add("Frequency", &Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].frequency, con);

		// Lacunarity
		con.setY(180);
		con.setMinMax(-10.0f, 10.0f);
		con.setStep(0.01f, 0.1f, 1.0f);
		Core::gui["GameMenu"]["Window 3"].Slider.add("Lacunarity", &Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].lacunarity, con);

		// Persistance
		con.setY(150);
		con.setMinMax(-1.0f, 1.0f);
		con.setStep(0.001f, 0.01f, 0.1f);
		Core::gui["GameMenu"]["Window 3"].Slider.add("Persistance", &Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].persistance, con);

		// Scale
		con.setY(120);
		con.setMinMax(0.1f, 5000.0f);
		con.setStep(1.0f, 10.0f, 100.0f);
		Core::gui["GameMenu"]["Window 3"].Slider.add("Scale", &Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].scale, con);

		// Octaves
		con.setY(90);
		con.setMinMax(1.0f, 10.0f);
		con.setStep(1.0f, 10.0f, 100.0f);
		Core::gui["GameMenu"]["Window 3"].Slider.add("Octaves", &Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].octaves, con);

		// World Scale
		con.setY(40);
		con.setMinMax(1.0f, 10.0f);
		con.setStep(0.01f, 0.1f, 1.0f);
		Core::gui["GameMenu"]["Window 3"].Slider.add("World Scale 1", &Core::gameVars->screen.fScale, con);

		Core::gui["GameMenu"]["Window 3"].Slider["World Scale 1"].getF()->setEnableA(false, 0);

		bOneShot[22] = true;
		std::cout << "Done" << std::endl;
	}

	// Slider Fractal
	if (!bOneShot[23]) {
		std::cout << "GUI: Loading #23: Fractal Sliders .............................. ";
		//std::cout << "...............................................................";
		Core::GUI::Props_Slider con;
		con.setOrigin(Core::GUI::CONSTRAIN_CENTER|Core::GUI::CONSTRAIN_BOTTOM);
		con.setAnchor(Core::GUI::CONSTRAIN_CENTER);					// Center of button
		con.setWidth(50, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		con.setHeight(4, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		con.showField();
		con.showLabel();
		con.setPrecision(5);

		//
		con.setY(440);
		con.setMinMax(64.0f, 2048.0f);
		con.setStep(1.0f, 10.0f, 100.0f);
		Core::gui["GameMenu"]["Window 4"].Slider.add("Resolution", &Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].res, con);

		//
		con.setY(410);
		con.setMinMax(1.0f, 1000.0f);
		con.setStep(1.0f, 10.0f, 100.0f);
		Core::gui["GameMenu"]["Window 4"].Slider.add("Tex Scale", &Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].tex_scale, con);

		//
		con.setY(380);
		con.setMinMax(1.0f, 100000.0f);
		con.setStep(1.0f, 10.0f, 100.0f);
		Core::gui["GameMenu"]["Window 4"].Slider.add("Terrain Size", &Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].terrain_size, con);

		// Offset X
		con.setY(350);
		con.setMinMax(-10000.0f, 10000.0f);
		con.setStep(1.0f, 10.0f, 100.0f);
		Core::gui["GameMenu"]["Window 4"].Slider.add("Terrain Height", &Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].terrain_height_offset, con);

		// Offset X
		con.setY(300);
		con.setMinMax(-10000.0f, 10000.0f);
		con.setStep(1.0f, 10.0f, 100.0f);
		Core::gui["GameMenu"]["Window 4"].Slider.add("Offset X", &Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].offset.x, con);

		// Offset Y
		con.setY(270);
		con.setMinMax(-10000.0f, 10000.0f);
		con.setStep(1.0f, 10.0f, 100.0f);
		Core::gui["GameMenu"]["Window 4"].Slider.add("Offset Y", &Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].offset.y, con);

		// Delta
		con.setY(240);
		con.setMinMax(1.0f, 32.0f);
		con.setStep(1.0f, 2.0f, 10.0f);
		Core::gui["GameMenu"]["Window 4"].Slider.add("Delta", &Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].delta, con);

		// Frequency
		con.setY(210);
		con.setMinMax(0.00001f, 0.00005f);
		con.setStep(0.000001f, 0.00001f, 0.0001f);
		Core::gui["GameMenu"]["Window 4"].Slider.add("Frequency", &Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].frequency, con);

		// Lacunarity
		con.setY(180);
		con.setMinMax(0.1f, 10.0f);
		con.setStep(0.01f, 0.1f, 1.0f);
		Core::gui["GameMenu"]["Window 4"].Slider.add("Lacunarity", &Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].lacunarity, con);

		// Multiplier
		con.setY(150);
		con.setMinMax(0.1f, 1.0f);
		con.setStep(0.001f, 0.01f, 0.1f);
		Core::gui["GameMenu"]["Window 4"].Slider.add("Multiplier", &Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].multiplier, con);

		// Scale
		con.setY(120);
		con.setMinMax(0.1f, 5000.0f);
		con.setStep(1.0f, 10.0f, 100.0f);
		Core::gui["GameMenu"]["Window 4"].Slider.add("Scale", &Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].scale, con);

		// Octaves
		con.setY(90);
		con.setMinMax(1.0f, 10.0f);
		con.setStep(1.0f, 1.0f, 1.0f);
		Core::gui["GameMenu"]["Window 4"].Slider.add("Layers", &Core::gameVars->debug.noise.fractal[Core::gameVars->debug.noise.iCurrentFractal].layers, con);

		// World Scale
		con.setY(40);
		con.setMinMax(1.0f, 10.0f);
		con.setStep(0.01f, 0.1f, 1.0f);
		Core::gui["GameMenu"]["Window 4"].Slider.add("World Scale 1", &Core::gameVars->screen.fScale, con);

		bOneShot[23] = true;
		std::cout << "Done" << std::endl;
		std::cout << "Skipping #24-29" << std::endl;
	}

	// Slider - Lighting
	if (!bOneShot[30]) {
		std::cout << "GUI: Loading #30: Lighting Sliders ............................. ";
		//std::cout << "...............................................................";
		Core::GUI::Props_Slider con;
		con.setOrigin(Core::GUI::CONSTRAIN_CENTER|Core::GUI::CONSTRAIN_BOTTOM);
		con.setAnchor(Core::GUI::CONSTRAIN_CENTER);						// Center of button
		con.setPos(0, 75);
		con.setWidth(200, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);			// Sets width of slider
		con.setHeight(4, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);			// Sets height of control
		con.showField();
		con.showLabel();

		con.setY(75);
		con.setMinMax(0.0f, 2.0f);
		con.setStep(1.0f);
		con.setToolTip("Select active light source.");
		Core::gui["GameMenu"]["Window 1"].Slider.add("DebugLight", &game->iDebugLight, con);

		Core::GUI::Props_Field field;
		field.setOrigin(Core::GUI::CONSTRAIN_CENTER|Core::GUI::CONSTRAIN_BOTTOM);
		field.setAnchor(Core::GUI::CONSTRAIN_CENTER);
		field.setPos(50, 45);
		field.setWidth(74, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		field.setHeight(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		field.setBorder(1, false);
		field.setRadius(0);
		Core::gui["GameMenu"]["Window 1"].Field.add("DebugLight 1", &game->iDebugLight, field);
		Core::gui["GameMenu"]["Window 1"].Field["DebugLight 1"].getI()->setEnableA(false, 0);

		field.modPos(0, 50);
		field.setPadding(5);
		field.autoWidth();
		field.autoHeight();
		field.setMinMaxWidth(50, 150);
		Core::gui["GameMenu"]["Window 1"].Field.add("DebugLight 2", &game->iDebugLight, field);
		Core::gui["GameMenu"]["Window 1"].Field["DebugLight 2"].getI()->setEnableA(false, 0);

		// Position
		con.setToolTip("None");
		con.setStep(1.0f, 10.0f, 100.0f);
		con.setY(300);
		con.setMinMax(-1000.0f, 1000.0f);
		Core::gui["GameMenu"]["Window 1"].Slider.add("Light Pos X", &game->world->lights->GetPos(game->iDebugLight).x, con);

		con.setY(275);
		con.setMinMax(-1000.0f, 1000.0f);
		Core::gui["GameMenu"]["Window 1"].Slider.add("Light Pos Y", &game->world->lights->GetPos(game->iDebugLight).y, con);

		con.setY(250);
		con.setMinMax(-1000.0f, 1000.0f);
		Core::gui["GameMenu"]["Window 1"].Slider.add("Light Pos Z", &game->world->lights->GetPos(game->iDebugLight).z, con);

		// Direction
		con.setStep(0.01f, 0.1f, 1.0f);
		con.setY(200);
		con.setMinMax(-1.0f, 1.0f);
		Core::gui["GameMenu"]["Window 1"].Slider.add("Light Dir X", &game->world->lights->GetDir(game->iDebugLight).x, con);

		con.setY(175);
		con.setMinMax(-1.0f, 1.0f);
		Core::gui["GameMenu"]["Window 1"].Slider.add("Light Dir Y", &game->world->lights->GetDir(game->iDebugLight).y, con);

		con.setY(150);
		con.setMinMax(-1.0f, 1.0f);
		Core::gui["GameMenu"]["Window 1"].Slider.add("Light Dir Z", &game->world->lights->GetDir(game->iDebugLight).z, con);

		bOneShot[30] = true;
		std::cout << "Done" << std::endl;
	}

	// Slider - Vertical Testing
	if (!bOneShot[31]) {
		std::cout << "GUI: Loading #31: Slider Testing ............................... ";
		//std::cout << "...............................................................";
		Core::GUI::Props_Slider con;
		con.setOrigin(Core::GUI::CONSTRAIN_TOP|Core::GUI::CONSTRAIN_CENTER);
		con.setAnchor(Core::GUI::CONSTRAIN_CENTER);
		con.setWidth(200, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);			// Sets width of slider
		con.setHeight(4, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);			// Sets height of control
		con.showField();
		con.showLabel();

		con.setStep(1.0f, 10.0f, 100.0f);
		con.setMinMax(-1000.0f, 1000.0f);

		con.setPos(0, -70);
		con.label.setOrigin(Core::GUI::CONSTRAIN_TOP);
		con.label.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
		con.field.setOrigin(Core::GUI::CONSTRAIN_BOTTOM);
		con.field.setAnchor(Core::GUI::CONSTRAIN_TOP);
		Core::gui["GameMenu"]["Window 5"].Slider.add("X - Horizontal T", &game->world->lights->GetPos(game->iDebugLight).x, con);

		con.setPos(0, -120);
		con.label.setOrigin(Core::GUI::CONSTRAIN_LEFT);
		con.label.setAnchor(Core::GUI::CONSTRAIN_RIGHT);
		con.field.setOrigin(Core::GUI::CONSTRAIN_RIGHT);
		con.field.setAnchor(Core::GUI::CONSTRAIN_LEFT);
		Core::gui["GameMenu"]["Window 5"].Slider.add("X - Horizontal M", &game->world->lights->GetPos(game->iDebugLight).x, con);

		con.setMinMax(1000.0f, -1000.0f);
		con.setPos(0, -170);
		con.label.setOrigin(Core::GUI::CONSTRAIN_BOTTOM);
		con.label.setAnchor(Core::GUI::CONSTRAIN_TOP);
		con.field.setOrigin(Core::GUI::CONSTRAIN_TOP);
		con.field.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
		Core::gui["GameMenu"]["Window 5"].Slider.add("X - Horizontal B", &game->world->lights->GetPos(game->iDebugLight).x, con);

		con.swapOrientation();

		con.setMinMax(-1000.0f, 1000.0f);
		con.setPos(-180, -350);
		con.label.setOrigin(Core::GUI::CONSTRAIN_TOP);
		con.label.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
		con.field.setOrigin(Core::GUI::CONSTRAIN_BOTTOM);
		con.field.setAnchor(Core::GUI::CONSTRAIN_TOP);
		Core::gui["GameMenu"]["Window 5"].Slider.add("X - Vertical T", &game->world->lights->GetPos(game->iDebugLight).x, con);

		con.setPos(0, -350);
		con.label.setOrigin(Core::GUI::CONSTRAIN_LEFT);
		con.label.setAnchor(Core::GUI::CONSTRAIN_RIGHT);
		con.field.setOrigin(Core::GUI::CONSTRAIN_RIGHT);
		con.field.setAnchor(Core::GUI::CONSTRAIN_LEFT);
		Core::gui["GameMenu"]["Window 5"].Slider.add("X - Vertical M", &game->world->lights->GetPos(game->iDebugLight).x, con);

		con.setMinMax(1000.0f, -1000.0f);
		con.setPos(180, -350);
		con.label.setOrigin(Core::GUI::CONSTRAIN_BOTTOM);
		con.label.setAnchor(Core::GUI::CONSTRAIN_TOP);
		con.field.setOrigin(Core::GUI::CONSTRAIN_TOP);
		con.field.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
		Core::gui["GameMenu"]["Window 5"].Slider.add("X - Vertical B", &game->world->lights->GetPos(game->iDebugLight).x, con);

		bOneShot[31] = true;
		std::cout << "Done" << std::endl;
	}

	// TextArea Testing
	if (!bOneShot[32]) {
		std::cout << "GUI: Loading #32: Text Area .................................... ";
		//std::cout << "...............................................................";

		Core::GUI::Props_TextArea c;
		c.setOrigin(Core::GUI::CONSTRAIN_LEFT);
		c.setAnchor(Core::GUI::CONSTRAIN_LEFT);
		c.setWidth(200, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		c.setHeight(250, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		c.setPos(150, 0);
		c.showLabel();
		c.setLineSpacing(0);
		c.setBuffer("\xC9\xCD\xCD\xCD\xCD\xCD\xBB\n"\
					"\xBA\xB0\xB0\xB0\xB0\xB0\xBA\n"\
					"\xBA\xB0\xB1\xB1\xB1\xB0\xBA\n"\
					"\xBA\xB0\xB1\xB2\xB1\xB0\xBA\n"\
					"\xBA\xB0\xB1\xB1\xB1\xB0\xBA\n"\
					"\xBA\xB0\xB0\xB0\xB0\xB0\xBA\n"\
					"\xC8\xCD\xCD\xCD\xCD\xCD\xBC\n"\
					"");
		Core::gui["GameMenu"]["Window 6"].TextArea.add("TextArea 0", c);



		c.setWidth(400, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		c.setHeight(400, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		c.setPos(0, -20);
		c.setScrolling(true);
		c.text.setWordWrap(true);
		(*Core::gameVars->debug.gui.buffer) =	"Testing special characters: '\xB0\xB1\xB2', '\xC9\xCD\xCD\xCD\xCD\xBB'\n\n"\
												"\x01\x02\x03\x04\x05\x06\n\x10\x11\x12\x13\x14\x15\x16\x17\x18\x19\x1A\x1B\x1C\x1D\x1E\x1F\n\n"\
												"Here is some text without any formatting characters (newlines) "\
												"so it should print all of the text and word wrap all on its own. "\
												"I will continue adding text so we can go beyond the limit of our "\
												"textArea which should result in ellipses automatically. Now I am "\
												"adding in some newlines to make sure they are working. I am putting "\
												"two newlines back to back to separate paragraphs.\n\nSome more "\
												"text also needs to be added for the possible addition of scroll "\
												"bars. They will work by scrolling one line at a time and not with "\
												"per pixel scrolling as that will just add complications.\n\n"\
												"Scrolling should stop when the last line becomes the first line "\
												"in the text box. There will only be scrolling buttons, not actual "\
												"bars that slide.\n\nThis is a test for multiple newlines, there "\
												"should be an empty space above this line.";

		c.setBuffer(Core::gameVars->debug.gui.buffer);
		Core::gui["GameMenu"]["Window 6"].TextEdit.add("TextArea 1", c);

		Core::GUI::Props_Slider con;
		con.setOrigin(Core::GUI::CONSTRAIN_TOP|Core::GUI::CONSTRAIN_CENTER);
		con.setAnchor(Core::GUI::CONSTRAIN_TOP);
		con.setWidth(200, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		con.setHeight(4, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		con.showField();
		con.showLabel();
		con.setMinMax(100.0f, 350.0f);
		con.setPos(0, -40);
		con.setStep(1.0f, 10.0f, 100.0f);
		Core::gui["GameMenu"]["Window 6"].Slider.add("textArea Width", &Core::gui["GameMenu"]["Window 6"].TextEdit("TextArea 1").size.constraint.x, con);

		con.setOrigin(Core::GUI::CONSTRAIN_RIGHT|Core::GUI::CONSTRAIN_CENTER);
		con.setAnchor(Core::GUI::CONSTRAIN_RIGHT);
		con.swapOrientation();
		con.setHeight(300, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		con.setPos(-50, 0);
		con.setMinMax(100.0f, 400.0f);
		con.label.setOrigin(Core::GUI::CONSTRAIN_TOP);
		con.label.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
		con.field.setOrigin(Core::GUI::CONSTRAIN_BOTTOM);
		con.field.setAnchor(Core::GUI::CONSTRAIN_TOP);
		Core::gui["GameMenu"]["Window 6"].Slider.add("textArea Height", &Core::gui["GameMenu"]["Window 6"].TextEdit("TextArea 1").size.constraint.y, con);

		// Toggle scroll bars
		Core::GUI::Props_Button cButton;
		cButton.setOrigin(Core::GUI::CONSTRAIN_LEFT|Core::GUI::CONSTRAIN_BOTTOM);
		cButton.setAnchor(Core::GUI::CONSTRAIN_BOTTOM|Core::GUI::CONSTRAIN_LEFT);
		cButton.setWidth(100, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		cButton.setHeight(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		cButton.setBorder(1, true);
		cButton.setRadius(10);
		cButton.setButtonType(Core::GUI::BUTTON_TOGGLE);
		cButton.setPos(5, 5);
		Core::gui["GameMenu"]["Window 6"].Button.add("Scrolling", &Core::gui["GameMenu"]["Window 6"].TextEdit("TextArea 1").enableScrolling, cButton);
		cButton.setPos(110, 5);
		Core::gui["GameMenu"]["Window 6"].Button.add("Enable", true, cButton);
//		Core::gui["GameMenu"]["Window 6"].TextEdit["TextArea 1"].setEnableAPtr(Core::gui["GameMenu"]["Window 6"].Button["Enable"].getPointer(), 0);
		Core::gui["GameMenu"]["Window 6"].TextEdit["TextArea 1"].setEnableAPtr(Core::gui["GameMenu"]["Window 6"].Button["Enable"].getStatePtr(), 0);

//		cButton.setWidth(75, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		cButton.setPos(215, 5);
		Core::gui["GameMenu"]["Window 6"].Button.add("AutoWidth", &Core::gui["GameMenu"]["Window 6"].TextEdit("TextArea 1").size.constraint.xAuto , cButton);
		cButton.setPos(320, 5);
		Core::gui["GameMenu"]["Window 6"].Button.add("AutoHeight", &Core::gui["GameMenu"]["Window 6"].TextEdit("TextArea 1").size.constraint.yAuto, cButton);

		bOneShot[32] = true;
		std::cout << "Done" << std::endl;
	}

	// ColorSwatch Testing
	if (!bOneShot[33]) {
		std::cout << "GUI: Loading #33: Color Swatch ................................. ";
		//std::cout << "...............................................................";
		Core::GUI::Props_ColorSwatch cColor;
		cColor.setOrigin(Core::GUI::CONSTRAIN_TOP|Core::GUI::CONSTRAIN_LEFT);
		cColor.setAnchor(Core::GUI::CONSTRAIN_TOP|Core::GUI::CONSTRAIN_LEFT);
		cColor.setWidth(100, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		cColor.setHeight(60, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		cColor.setBorder(1, 1);
		cColor.setRadius(3);
		cColor.setPadding(0);
		cColor.slider.setWidth(200);

		cColor.setPos(0,  -50);		Core::gui["GameMenu"]["Window 7"].ColorSwatch.add("Swatch 1", &Core::gameVars->pallette.gui.window.background.base, cColor);
		cColor.setPos(0, -130);		Core::gui["GameMenu"]["Window 7"].ColorSwatch.add("Swatch 2", &Core::gameVars->pallette.gui.window.border.base, cColor);

		cColor.setPos(0, -290);		Core::gui["GameMenu"]["Window 7"].ColorSwatch.add("Swatch 3", &Core::gameVars->pallette.gui.button.background.base, cColor);
		cColor.setPos(0, -370);		Core::gui["GameMenu"]["Window 7"].ColorSwatch.add("Swatch 4", &Core::gameVars->pallette.gui.button.background.hover, cColor);
		cColor.setPos(0, -450);		Core::gui["GameMenu"]["Window 7"].ColorSwatch.add("Swatch 5", &Core::gameVars->pallette.gui.button.background.active, cColor);
		Core::gui["GameMenu"]["Window 7"].ColorSwatch["Swatch 5"].setEnableA(false, 0);

		bOneShot[33] = true;
		std::cout << "Done" << std::endl;
	}

	// Checkbox Testing
	if (!bOneShot[34]) {
		std::cout << "GUI: Loading #34: Checkbox ..................................... ";
		//std::cout << "...............................................................";
		// Objects to be controlled by checkbox
		Core::GUI::Props_TextArea c1;
		c1.setOrigin(Core::GUI::CONSTRAIN_TOP);
		c1.setAnchor(Core::GUI::CONSTRAIN_TOP);
		c1.setWidth(300, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		c1.setHeight(100, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		c1.setBorder(1, true);
		c1.setRadius(10);
		c1.Props::setPadding(4);
		c1.setVisibility(false);
		c1.setPos(0, -150);

		c1.setBuffer("You selected Checkbox #1!\n\nCongratulations you win!");
		Core::gui["GameMenu"]["Window 8"].TextArea.add("CheckText 1", c1);

		c1.setBuffer("You selected Checkbox #2!\n\nYou die instantly!");
		Core::gui["GameMenu"]["Window 8"].TextArea.add("CheckText 2", c1);

		c1.setBuffer("You selected Checkbox #3!\n\nYou have been cursed with 'Rick Syndrome' and will intermittantly belch every time you speak!");
		Core::gui["GameMenu"]["Window 8"].TextArea.add("CheckText 3", c1);

		Core::GUI::Props_CheckBox c;
		c.setOrigin(Core::GUI::CONSTRAIN_CENTER|Core::GUI::CONSTRAIN_TOP);
		c.setAnchor(Core::GUI::CONSTRAIN_CENTER|Core::GUI::CONSTRAIN_TOP);
		c.setWidth(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		c.setHeight(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		c.label.setOrigin(Core::GUI::CONSTRAIN_LEFT);
		c.label.setAnchor(Core::GUI::CONSTRAIN_RIGHT);
		c.setBorder(1, true);
		c.setRadius(0);
		//c.setGroup(2);
		c.setGroup(Core::groups.add("Checkbox Sample", false));

		c.setPos(0, -40);
		Core::gui["GameMenu"]["Window 8"].CheckBox.add("Check 1", &Core::gui["GameMenu"]["Window 8"].TextArea["CheckText 1"].con->visibility, c);

		c.setPos(0, -70);
		Core::gui["GameMenu"]["Window 8"].CheckBox.add("Check 2", &Core::gui["GameMenu"]["Window 8"].TextArea["CheckText 2"].con->visibility, c);

		c.setPos(100, -70);
		Core::gui["GameMenu"]["Window 8"].CheckBox.add("Check 4", false, c);
		Core::gui["GameMenu"]["Window 8"].CheckBox["Check 4"].setEnableA(false, 0);

		c.setPos(0, -100);
		Core::gui["GameMenu"]["Window 8"].CheckBox.add("Check 3", &Core::gui["GameMenu"]["Window 8"].TextArea["CheckText 3"].con->visibility, c);

		Core::GUI::Object::CheckBox *checkBox;
		c.setOrigin(Core::GUI::CONSTRAIN_CENTER);
		c.setAnchor(Core::GUI::CONSTRAIN_CENTER);
		//c.setGroup(0);
		c.setPos(0, -70);
		c.label.disablePadding();
		c.label.autoWidth();
		c.label.autoHeight();
		c.setWidth(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		c.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
//		c.setOnValue(Core::GUI::CONSTRAIN_CENTER, 0);
//		c.setOnValue(Core::GUI::CONSTRAIN_CENTER, 1);
//		c.setOnValue(0, 2);
//		c.setOnValue(0, 3);
		//c.setGroup(3);
		c.setGroup(Core::groups.add("Check States Sample", true));
		c.setRadius(20);
		c.setPadding(-10);
		checkBox = &Core::gui["GameMenu"]["Window 8"].CheckBox.add("Check Sample", false, c);
		checkBox->dataSet.addGroupState("ON", Core::GUI::CONSTRAIN_CENTER);
		checkBox->dataSet.addGroupState("ON", Core::GUI::CONSTRAIN_CENTER);
		checkBox->dataSet.addGroupState("ON", 0);
		checkBox->dataSet.addGroupState("ON", 0);

		Core::GUI::Props_CheckBox cLabelPos;
		cLabelPos.setAnchor(Core::GUI::CONSTRAIN_CENTER);
		cLabelPos.setWidth(25, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		cLabelPos.setHeight(25, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		cLabelPos.hideLabel();
		cLabelPos.setBorder(1, true);
		cLabelPos.setRadius(0);
		//cLabelPos.setGroup(3);
		cLabelPos.setGroup(Core::groups["Check States Sample"]);

		cLabelPos.setOrigin(Core::GUI::CONSTRAIN_TOP);
		cLabelPos.setAnchor(Core::GUI::CONSTRAIN_CENTER);
		cLabelPos.setPos(0, 0);
//		cLabelPos.setOnValue(Core::GUI::CONSTRAIN_TOP, 0);
//		cLabelPos.setOnValue(Core::GUI::CONSTRAIN_BOTTOM, 1);
//		cLabelPos.setOnValue(0, 2);
//		cLabelPos.setOnValue(10, 3);
		Core::gui["GameMenu"]["Window 8"].CheckBox.add("CSAM T", false, cLabelPos, &Core::gui["GameMenu"]["Window 8"].CheckBox("Check Sample")).dataSet.addGroupStates("ON", std::vector<Core::t_BIFS>{Core::GUI::CONSTRAIN_TOP, Core::GUI::CONSTRAIN_BOTTOM, 0, 10});

		cLabelPos.setOrigin(Core::GUI::CONSTRAIN_BOTTOM);
		cLabelPos.setAnchor(Core::GUI::CONSTRAIN_CENTER);
		cLabelPos.setPos(0, 0);
//		cLabelPos.setOnValue(Core::GUI::CONSTRAIN_BOTTOM, 0);
//		cLabelPos.setOnValue(Core::GUI::CONSTRAIN_TOP, 1);
//		cLabelPos.setOnValue(0, 2);
//		cLabelPos.setOnValue(-10, 3);
		Core::gui["GameMenu"]["Window 8"].CheckBox.add("CSAM B", false, cLabelPos, &Core::gui["GameMenu"]["Window 8"].CheckBox("Check Sample")).dataSet.addGroupStates("ON", std::vector<Core::t_BIFS>{Core::GUI::CONSTRAIN_BOTTOM, Core::GUI::CONSTRAIN_TOP, 0, -10});

		cLabelPos.setOrigin(Core::GUI::CONSTRAIN_LEFT);
		cLabelPos.setAnchor(Core::GUI::CONSTRAIN_CENTER);
		cLabelPos.setPos(0, 0);
//		cLabelPos.setOnValue(Core::GUI::CONSTRAIN_LEFT, 0);
//		cLabelPos.setOnValue(Core::GUI::CONSTRAIN_RIGHT, 1);
//		cLabelPos.setOnValue(-10, 2);
//		cLabelPos.setOnValue(0, 3);
		Core::gui["GameMenu"]["Window 8"].CheckBox.add("CSAM L", true, cLabelPos, &Core::gui["GameMenu"]["Window 8"].CheckBox("Check Sample")).dataSet.addGroupStates("ON", std::vector<Core::t_BIFS>{Core::GUI::CONSTRAIN_LEFT, Core::GUI::CONSTRAIN_RIGHT, -10, 0});

		cLabelPos.setOrigin(Core::GUI::CONSTRAIN_RIGHT);
		cLabelPos.setAnchor(Core::GUI::CONSTRAIN_CENTER);
		cLabelPos.setPos(0, 0);
//		cLabelPos.setOnValue(Core::GUI::CONSTRAIN_RIGHT, 0);
//		cLabelPos.setOnValue(Core::GUI::CONSTRAIN_LEFT, 1);
//		cLabelPos.setOnValue(10, 2);
//		cLabelPos.setOnValue(0, 3);
		checkBox = &Core::gui["GameMenu"]["Window 8"].CheckBox.add("CSAM R", false, cLabelPos, &Core::gui["GameMenu"]["Window 8"].CheckBox("Check Sample"));
		checkBox->dataSet.addGroupStates("ON", std::vector<Core::t_BIFS>{Core::GUI::CONSTRAIN_RIGHT, Core::GUI::CONSTRAIN_LEFT, 10, 0});

		cLabelPos.setOrigin(Core::GUI::CONSTRAIN_TOP_LEFT);
		cLabelPos.setAnchor(Core::GUI::CONSTRAIN_CENTER);
		cLabelPos.setPos(0, 0);
//		cLabelPos.setOnValue(Core::GUI::CONSTRAIN_TOP_LEFT, 0);
//		cLabelPos.setOnValue(Core::GUI::CONSTRAIN_BOTTOM_RIGHT, 1);
//		cLabelPos.setOnValue(-10, 2);
//		cLabelPos.setOnValue(10, 3);
		checkBox = &Core::gui["GameMenu"]["Window 8"].CheckBox.add("CSAM TL", false, cLabelPos, &Core::gui["GameMenu"]["Window 8"].CheckBox("Check Sample"));
		checkBox->dataSet.addGroupState("ON", Core::GUI::CONSTRAIN_TOP_LEFT);
		checkBox->dataSet.addGroupState("ON", Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
		checkBox->dataSet.addGroupState("ON", -10);
		checkBox->dataSet.addGroupState("ON", 10);

		cLabelPos.setOrigin(Core::GUI::CONSTRAIN_TOP_RIGHT);
		cLabelPos.setAnchor(Core::GUI::CONSTRAIN_CENTER);
		cLabelPos.setPos(0, 0);
//		cLabelPos.setOnValue(Core::GUI::CONSTRAIN_TOP_RIGHT, 0);
//		cLabelPos.setOnValue(Core::GUI::CONSTRAIN_BOTTOM_LEFT, 1);
//		cLabelPos.setOnValue(10, 2);
//		cLabelPos.setOnValue(10, 3);
		checkBox = &Core::gui["GameMenu"]["Window 8"].CheckBox.add("CSAM TR", false, cLabelPos, &Core::gui["GameMenu"]["Window 8"].CheckBox("Check Sample"));
		checkBox->dataSet.addGroupState("ON", Core::GUI::CONSTRAIN_TOP_RIGHT);
		checkBox->dataSet.addGroupState("ON", Core::GUI::CONSTRAIN_BOTTOM_LEFT);
		checkBox->dataSet.addGroupState("ON", 10);
		checkBox->dataSet.addGroupState("ON", 10);

		cLabelPos.setOrigin(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
		cLabelPos.setAnchor(Core::GUI::CONSTRAIN_CENTER);
		cLabelPos.setPos(0, 0);
//		cLabelPos.setOnValue(Core::GUI::CONSTRAIN_BOTTOM_LEFT, 0);
//		cLabelPos.setOnValue(Core::GUI::CONSTRAIN_TOP_RIGHT, 1);
//		cLabelPos.setOnValue(-10, 2);
//		cLabelPos.setOnValue(-10, 3);
		checkBox = &Core::gui["GameMenu"]["Window 8"].CheckBox.add("CSAM BL", false, cLabelPos, &Core::gui["GameMenu"]["Window 8"].CheckBox("Check Sample"));
		checkBox->dataSet.addGroupState("ON", Core::GUI::CONSTRAIN_BOTTOM_LEFT);
		checkBox->dataSet.addGroupState("ON", Core::GUI::CONSTRAIN_TOP_RIGHT);
		checkBox->dataSet.addGroupState("ON", -10);
		checkBox->dataSet.addGroupState("ON", -10);

		cLabelPos.setOrigin(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
		cLabelPos.setAnchor(Core::GUI::CONSTRAIN_CENTER);
		cLabelPos.setPos(0, 0);
//		cLabelPos.setOnValue(Core::GUI::CONSTRAIN_BOTTOM_RIGHT, 0);
//		cLabelPos.setOnValue(Core::GUI::CONSTRAIN_TOP_LEFT, 1);
//		cLabelPos.setOnValue(10, 2);
//		cLabelPos.setOnValue(-10, 3);
		checkBox = &Core::gui["GameMenu"]["Window 8"].CheckBox.add("CSAM BR", false, cLabelPos, &Core::gui["GameMenu"]["Window 8"].CheckBox("Check Sample"));
		checkBox->dataSet.addGroupState("ON", Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
		checkBox->dataSet.addGroupState("ON", Core::GUI::CONSTRAIN_TOP_LEFT);
		checkBox->dataSet.addGroupState("ON", 10);
		checkBox->dataSet.addGroupState("ON", -10);

		Core::GUI::Props_Slider con;
		con.setOrigin(Core::GUI::CONSTRAIN_BOTTOM);
		con.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
		con.setWidth(60, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		con.setHeight(4, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		con.showField();
		con.showLabel();
		con.label.setOrigin(Core::GUI::CONSTRAIN_LEFT);
		con.label.setAnchor(Core::GUI::CONSTRAIN_RIGHT);
		con.label.setPos(0, 0);
		con.field.setOrigin(Core::GUI::CONSTRAIN_RIGHT);
		con.field.setAnchor(Core::GUI::CONSTRAIN_LEFT);
		con.field.setPadding(4);
		con.field.setPos(0, 0);

		con.setPos(0, 90);
		con.setMinMax(8, 100);
		con.setStep(2.0f, 4.0f, 8.0f);
		Core::gui["GameMenu"]["Window 8"].Slider.add("Width", &Core::gui["GameMenu"]["Window 8"].CheckBox("Check Sample").size.constraint.x, con);

		con.setPos(0, 60);
		con.setMinMax(8, 100);
		con.setStep(2.0f, 4.0f, 8.0f);
		Core::gui["GameMenu"]["Window 8"].Slider.add("Height", &Core::gui["GameMenu"]["Window 8"].CheckBox("Check Sample").size.constraint.y, con);

		con.setPos(0, 30);
		con.setMinMax(0, 100);
		con.setStep(1.0f, 2.0f, 4.0f);
		Core::gui["GameMenu"]["Window 8"].Slider.add("Radius", &Core::gui["GameMenu"]["Window 8"].CheckBox("Check Sample").radius, con);

		bOneShot[34] = true;
		std::cout << "Done" << std::endl;
	}

	/*
	 * Overall window size
	 *
	 * This will only work for one window with the current setup. Would need
	 * to create pointer for the base window and all should use that same
	 * constraint set to make this work for all windows.
	 */
	if (!bOneShot[35]) {
		std::cout << "GUI: Loading #35: Window Settings .............................. ";
		//std::cout << "...............................................................";
		Core::GUI::Props_Slider con;
		con.setOrigin(Core::GUI::CONSTRAIN_TOP|Core::GUI::CONSTRAIN_CENTER);
		con.setAnchor(Core::GUI::CONSTRAIN_TOP);
		con.setWidth(80, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		con.setHeight(4, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		con.showField();
		con.showLabel();
		con.setMinMax(100.0f, 1000.0f);
		con.setPos(0, -40);
		con.label.setOrigin(Core::GUI::CONSTRAIN_TOP_LEFT);
		con.label.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
		con.label.setPos(0, 0);
		con.field.setAnchor(Core::GUI::CONSTRAIN_TOP_RIGHT);
		con.field.setOrigin(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
		con.field.setPos(0, 0);
		con.setStep(2.0f, 10.0f, 100.0f);
		Core::gui["GameMenu"]["Window 9"].Slider.add("Window Width", &Core::gui["GameMenu"]["Window 9"].con->size.constraint.x, con);

		con.label.setOrigin(Core::GUI::CONSTRAIN_LEFT);
		con.label.setAnchor(Core::GUI::CONSTRAIN_RIGHT);
		con.field.setOrigin(Core::GUI::CONSTRAIN_RIGHT);
		con.field.setAnchor(Core::GUI::CONSTRAIN_LEFT);
		con.setPos(-50, -120);
		con.setWidth(40, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		con.setMinMax(0, 100);
		con.setStep(1.0f, 5.0f, 10.0f);
		Core::gui["GameMenu"]["Window 9"].Slider.add("Font", &Core::gameVars->font.iPointSize, con);

		con.modPos(0, -25);
		con.setMinMax(2, 100);
		con.setStep(1.0f, 5.0f, 10.0f);
		Core::gui["GameMenu"]["Window 9"].Slider.add("Radius", Core::gui["GameMenu"]["Window 9"].con->radius, con);

		con.modPos(0, -25);
		con.setMinMax(0, 100);
		con.setStep(1.0f, 5.0f, 10.0f);
		Core::gui["GameMenu"]["Window 9"].Slider.add("Border", Core::gui["GameMenu"]["Window 9"].con->borderNormal, con);

		con.modPos(0, -25);
		con.setMinMax(0, 100);
		con.setStep(1.0f, 5.0f, 10.0f);
		Core::gui["GameMenu"]["Window 9"].Slider.add("Pad: T", Core::gui["GameMenu"]["Window 9"].con->vPadding.top, con);

		con.modPos(0, -25);
		con.setMinMax(0, 100);
		con.setStep(1.0f, 5.0f, 10.0f);
		Core::gui["GameMenu"]["Window 9"].Slider.add("Pad: B", Core::gui["GameMenu"]["Window 9"].con->vPadding.bottom, con);

		con.modPos(0, -25);
		con.setMinMax(0, 100);
		con.setStep(1.0f, 5.0f, 10.0f);
		Core::gui["GameMenu"]["Window 9"].Slider.add("Pad: L", Core::gui["GameMenu"]["Window 9"].con->vPadding.left, con);

		con.modPos(0, -25);
		con.setMinMax(0, 100);
		con.setStep(1.0f, 5.0f, 10.0f);
		Core::gui["GameMenu"]["Window 9"].Slider.add("Pad: R", Core::gui["GameMenu"]["Window 9"].con->vPadding.right, con);

		con.modPos(0, -25);
		con.setMinMax(0, 10000);
		con.setStep(10.0f, 100.0f, 1000.0f);
		Core::gui["GameMenu"]["Window 9"].Slider.add("Show Tip", &Core::GUI::Props::ToolTip::showDelay, con);

		con.modPos(0, -25);
		con.setMinMax(0, 30000);
		con.setStep(10.0f, 100.0f, 1000.0f);
		Core::gui["GameMenu"]["Window 9"].Slider.add("Hide Tip", &Core::GUI::Props::ToolTip::hideDelay, con);

		con.setOrigin(Core::GUI::CONSTRAIN_RIGHT|Core::GUI::CONSTRAIN_CENTER);
		con.setAnchor(Core::GUI::CONSTRAIN_RIGHT);
		con.swapOrientation();
		con.setHeight(70, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		con.setPos(-60, -20);
		con.setMinMax(100.0f, 550.0f);
		con.label.setOrigin(Core::GUI::CONSTRAIN_TOP);
		con.label.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
		con.field.setOrigin(Core::GUI::CONSTRAIN_BOTTOM);
		con.field.setAnchor(Core::GUI::CONSTRAIN_TOP);
		con.setStep(1.0f, 5.0f, 10.0f);
		Core::gui["GameMenu"]["Window 9"].Slider.add("Window Height", &Core::gui["GameMenu"]["Window 9"].con->size.constraint.y, con);

		Core::GUI::Props_Button cButton;
		cButton.setOrigin(Core::GUI::CONSTRAIN_BOTTOM);
		cButton.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
		cButton.setWidth(130, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		cButton.setHeight(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		cButton.setBorder(1, true);
		cButton.setRadius(10);
		cButton.setButtonType(Core::GUI::BUTTON_TOGGLE);
		cButton.setPos(5, 5);
		Core::gui["GameMenu"]["Window 9"].Button.add("Round Border", &Core::gui["GameMenu"]["Window 9"].con->roundBorder, cButton);
		cButton.modPos(130, 0);
		Core::gui["GameMenu"]["Window 9"].Button.add("Tooltips", &Core::GUI::Props::ToolTip::bShowGlobal, cButton);
		cButton.modPos(-260, 0);
		Core::gui["GameMenu"]["Window 9"].Button.add("Enable Settings", &Core::GUI::Props::bGlobalSettings, cButton);

//		Core::GUI::Props_Button cButton2;
//		cButton2.setOrigin(Core::GUI::CONSTRAIN_BOTTOM);
//		cButton2.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
//		cButton2.setWidth(150, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
//		cButton2.setHeight(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
//		cButton2.setBorder(1, true);
//		cButton2.setRadius(10);
//		cButton2.setButtonType(Core::GUI::BUTTON_TOGGLE);
//		cButton2.setPos(165, 5);
//		Core::gui["GameMenu"]["Window 9"].Button.add("Tooltips", &Core::GUI::Props::ToolTip::bShowGlobal, cButton2);

		bOneShot[35] = true;
		std::cout << "Done" << std::endl;
	}

	/*
	 * Icons
	 */
	if (!bOneShot[36]) {
		std::cout << "GUI: Loading #36: Icons ........................................ ";
		//std::cout << "...............................................................";

		Core::GUI::Props_Icon cIcon;
		cIcon.setOrigin(Core::GUI::CONSTRAIN_TOP);
		cIcon.setAnchor(Core::GUI::CONSTRAIN_TOP);
		cIcon.setWidth(150, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		cIcon.setHeight(150, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		cIcon.setButtonType(Core::GUI::BUTTON_TOGGLE);
		cIcon.setImage("1800_icons_2.svg");
		cIcon.setIconIDs(0, 0, 0);
		cIcon.setPos(0, -40);

		Core::gui["GameMenu"]["Window 10"].Icon.add("Icon Test", &Core::gui["GameMenu"]["Window 10"].con->bEnableStipple, cIcon);

		cIcon.setOrigin(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
		cIcon.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
		cIcon.setWidth(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		cIcon.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);

		cIcon.showBackground();
		cIcon.setPos(0, 250);		cIcon.setIconIDs(1, 1, 1);		Core::gui["GameMenu"]["Window 10"].Icon.add("Icon Test 1", false, cIcon);
		cIcon.setPos(0, 200);		cIcon.setIconIDs(2, 2, 2);		Core::gui["GameMenu"]["Window 10"].Icon.add("Icon Test 2", false, cIcon);
		cIcon.setPos(0, 150);		cIcon.setIconIDs(3, 3, 3);		Core::gui["GameMenu"]["Window 10"].Icon.add("Icon Test 3", false, cIcon);
		cIcon.setPos(0, 100);		cIcon.setIconIDs(4, 4, 4);		Core::gui["GameMenu"]["Window 10"].Icon.add("Icon Test 4", false, cIcon);
		cIcon.setPos(0,  50);		cIcon.setIconIDs(5, 5, 5);		Core::gui["GameMenu"]["Window 10"].Icon.add("Icon Test 5", false, cIcon);
		cIcon.setPos(0,   0);		cIcon.setIconIDs(6, 6, 6);		Core::gui["GameMenu"]["Window 10"].Icon.add("Icon Test 6", false, cIcon);

		Core::gui["GameMenu"]["Window 10"].Icon["Icon Test 6"].setEnableA(false, 0);

		// TODO: Try implementing a window with: Icon, Text...scrolling??? Like old inventory list.

		bOneShot[36] = true;
		std::cout << "Done" << std::endl;
	}

	/*
	 * Sprite
	 */
	if (!bOneShot[37]) {
		std::cout << "GUI: Loading #37: Sprites ...................................... ";
		//std::cout << "...............................................................";

		Core::GUI::Props_Sprite cSprite;
//		cSprite.setOrigin(Core::GUI::CONSTRAIN_TOP|Core::GUI::CONSTRAIN_CENTER);
//		cSprite.setOrigin(Core::GUI::CONSTRAIN_LEFT|Core::GUI::CONSTRAIN_CENTER);
		cSprite.setOrigin(Core::GUI::CONSTRAIN_TOP);
		cSprite.setAnchor(Core::GUI::CONSTRAIN_TOP);
//		cSprite.setOrigin(Core::GUI::CONSTRAIN_BOTTOM);
//		cSprite.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
		cSprite.setWidth(100, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		cSprite.setHeight(50, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
//		cSprite.setHeight(550, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
//		cSprite.setHeight(100, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		cSprite.setBorder(1, true);
		cSprite.setRadius(10);
//		cSprite.setPos(0, -20);
		cSprite.setPos(0, 0);
		cSprite.setPadding(20);
		cSprite.enablePadding(Core::GUI::PADDING_ALL);
		cSprite.setImage("TestPattern.png");
		Core::gui["GameMenu"]["Window 11"].Sprite.add("Icon Test", cSprite);

		Core::GUI::Props_Slider con;
		con.setOrigin(Core::GUI::CONSTRAIN_BOTTOM);
		con.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
		con.setWidth(50, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		con.setHeight(4, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		con.showField();
		con.showLabel();
		con.disablePadding();
//		con.label.setOrigin(Core::GUI::CONSTRAIN_TOP_LEFT);
//		con.label.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
//		con.label.setPos(0, 0);
//		con.field.setAnchor(Core::GUI::CONSTRAIN_TOP_RIGHT);
//		con.field.setOrigin(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
//		con.field.setPos(0, 0);

		con.setPos(-10, 80);
		con.setMinMax(0, 100);
		con.setStep(1.0f, 5.0f, 10.0f);
		Core::gui["GameMenu"]["Window 11"].Slider.add("Top", &Core::gui["GameMenu"]["Window 11"].con->vPadding.top, con);

		con.modPos(0, -20);
		con.setMinMax(0, 100);
		con.setStep(1.0f, 5.0f, 10.0f);
		Core::gui["GameMenu"]["Window 11"].Slider.add("Bottom", &Core::gui["GameMenu"]["Window 11"].con->vPadding.bottom, con);

		con.modPos(0, -20);
		con.setMinMax(0, 100);
		con.setStep(1.0f, 5.0f, 10.0f);
		Core::gui["GameMenu"]["Window 11"].Slider.add("Left", &Core::gui["GameMenu"]["Window 11"].con->vPadding.left, con);

		con.modPos(0, -20);
		con.setMinMax(0, 100);
		con.setStep(1.0f, 5.0f, 10.0f);
		Core::gui["GameMenu"]["Window 11"].Slider.add("Right", &Core::gui["GameMenu"]["Window 11"].con->vPadding.right, con);


		bOneShot[37] = true;
		std::cout << "Done" << std::endl;
	}

	/*
	 * Stipple
	 */
	if (!bOneShot[38]) {
		std::cout << "GUI: Loading #38: Stipple ...................................... ";
		//std::cout << "...............................................................";
		Core::GUI::Props_CheckBox c;
		c.setOrigin(Core::GUI::CONSTRAIN_TOP_LEFT);
		c.setAnchor(Core::GUI::CONSTRAIN_TOP_LEFT);
		c.setWidth(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		c.setHeight(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		c.label.setOrigin(Core::GUI::CONSTRAIN_RIGHT);
		c.label.setAnchor(Core::GUI::CONSTRAIN_LEFT);
		c.label.enablePadding(Core::GUI::PADDING_POSITION);
		c.label.setPos(10, 0);
		c.label.showBackground();
		c.setBorder(1, true);
		c.setRadius(10);
		//c.setGroup(2);
		c.setGroup(Core::groups.add("Stipple Group"));




		c.setPos(0, -22);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_ANSI31, false, c).dataSet.addGroupState("ON",			1);
		c.setPos(0, -44);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_ANGLE_THICK, false, c).dataSet.addGroupState("ON",	2);
		c.setPos(0, -66);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_ANGLE, false, c).dataSet.addGroupState("ON", 			3);
		c.setPos(0, -88);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_BLOCKS, false, c).dataSet.addGroupState("ON", 		4);
		c.setPos(0, -110);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_CHECKERBOARD, false, c).dataSet.addGroupState("ON",	5);
		c.setPos(0, -132);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_SAND, false, c).dataSet.addGroupState("ON", 			6);
		c.setPos(0, -154);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_INSULATION, false, c).dataSet.addGroupState("ON", 	7);
		c.setPos(0, -176);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_BOARD, false, c).dataSet.addGroupState("ON", 			8);
		c.setPos(0, -198);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_ZIGZAG, false, c).dataSet.addGroupState("ON", 		9);
		c.setPos(0, -220);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_WATER, false, c).dataSet.addGroupState("ON", 			10);
		c.setPos(0, -242);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_GRASS, false, c).dataSet.addGroupState("ON", 			11);
		c.setPos(0, -264);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_CHECKER, false, c).dataSet.addGroupState("ON",		12);
		c.setPos(0, -286);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_OCTAGONS, false, c).dataSet.addGroupState("ON",	 	13);
		c.setPos(0, -308);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_WAFFLE, false, c).dataSet.addGroupState("ON", 		14);
		c.setPos(0, -330);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_PLUSSES, false, c).dataSet.addGroupState("ON", 		15);
		c.setPos(0, -352);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_SHAKES, false, c).dataSet.addGroupState("ON", 		16);
		c.setPos(0, -374);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_EARTH, false, c).dataSet.addGroupState("ON", 			17);
		c.setPos(0, -396);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_HERRING, false, c).dataSet.addGroupState("ON",		18);
		c.setPos(0, -418);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_DOTS, false, c).dataSet.addGroupState("ON", 			19);

		c.setOrigin(Core::GUI::CONSTRAIN_TOP_RIGHT);
		c.setAnchor(Core::GUI::CONSTRAIN_TOP_RIGHT);
		c.label.setOrigin(Core::GUI::CONSTRAIN_LEFT);
		c.label.setAnchor(Core::GUI::CONSTRAIN_RIGHT);
		c.label.setPos(-10, 0);
		c.setPos(0, -22);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_GROUT, false, c).dataSet.addGroupState("ON", 			20);
		c.setPos(0, -44);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_CROSSES, false, c).dataSet.addGroupState("ON", 		21);
		c.setPos(0, -66);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_TILEPAT1, false, c).dataSet.addGroupState("ON", 		22);
		c.setPos(0, -88);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_WOOD, false, c).dataSet.addGroupState("ON", 			23);
		c.setPos(0, -110);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_GRADIENT_V, false, c).dataSet.addGroupState("ON", 	24);
		c.setPos(0, -132);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_GRADIENT_H, false, c).dataSet.addGroupState("ON", 	25);
		c.setPos(0, -154);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_SHADE_125, false, c).dataSet.addGroupState("ON", 		26);
		c.setPos(0, -176);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_SHADE_25, false, c).dataSet.addGroupState("ON", 		27);
		c.setPos(0, -198);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_SHADE_50, false, c).dataSet.addGroupState("ON", 		28);
		c.setPos(0, -220);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_SHADE_75, false, c).dataSet.addGroupState("ON", 		29);
		c.setPos(0, -242);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_SHINGLE, false, c).dataSet.addGroupState("ON", 		30);
		c.setPos(0, -264);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_TILE_OFFSET, false, c).dataSet.addGroupState("ON", 	31);
		c.setPos(0, -286);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_FENCE, false, c).dataSet.addGroupState("ON", 			32);
		c.setPos(0, -308);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_SHALE, false, c).dataSet.addGroupState("ON", 			33);
		c.setPos(0, -330);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_SANDSTONE, false, c).dataSet.addGroupState("ON", 		34);
		c.setPos(0, -352);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_SLOT, false, c).dataSet.addGroupState("ON", 			35);
		c.setPos(0, -374);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_LIMESTONE, false, c).dataSet.addGroupState("ON", 		36);
		c.setPos(0, -396);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_SALT, false, c).dataSet.addGroupState("ON", 			37);
		c.setPos(0, -418);	Core::gui["GameMenu"]["Window 12"].CheckBox.add(Core::stipple.STIPPLE_PUMICE, false, c).dataSet.addGroupState("ON", 		38);





		Core::GUI::Props_Slider con;
		con.setOrigin(Core::GUI::CONSTRAIN_BOTTOM);
		con.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
		con.setWidth(90, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		con.setHeight(4, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		con.showField();
		con.showLabel();
		con.label.setOrigin(Core::GUI::CONSTRAIN_TOP_LEFT);
		con.label.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
		con.label.setPos(0, 0);
		con.field.setAnchor(Core::GUI::CONSTRAIN_TOP_RIGHT);
		con.field.setOrigin(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
		con.field.setPos(0, 0);
		// TODO: Scale Stipple Slider

		Core::GUI::Props_ColorSwatch cColor;
		cColor.setOrigin(Core::GUI::CONSTRAIN_BOTTOM|Core::GUI::CONSTRAIN_LEFT);
		cColor.setAnchor(Core::GUI::CONSTRAIN_BOTTOM|Core::GUI::CONSTRAIN_LEFT);
		cColor.setWidth(100, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		cColor.setHeight(60, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		cColor.setBorder(1, 1);
		cColor.setRadius(3);
		cColor.setPadding(0);
		cColor.slider.setWidth(200);
		cColor.setPos(5,  10);
		Core::gui["GameMenu"]["Window 12"].ColorSwatch.add("Stipple Color", &Core::gameVars->pallette.gui.window.stipple.base, cColor);

		bOneShot[38] = true;
		std::cout << "Done" << std::endl;
	}

	/*
	 * Color Boxes
	 */
	if (!bOneShot[39]) {
		std::cout << "GUI: Loading #39: Colors ....................................... ";

		//initColors();

		bOneShot[39] = true;
		std::cout << "Done" << std::endl;
	}

	/*
	 * Color Boxes
	 */
	if (!bOneShot[40]) {
		std::cout << "GUI: Loading #40: Colors 2...................................... ";
//		//std::cout << "...............................................................";
//
		bOneShot[40] = true;
		std::cout << "Done" << std::endl;
	}

	if (!bOneShot[41]) {
		std::cout << "GUI: Loading #41: Skill Tree ................................... ";
		//std::cout << "...............................................................";

		initSkillTree();

		bOneShot[41] = true;
		std::cout << "Done" << std::endl;
	}

	if (!bOneShot[42]) {
		std::cout << "GUI: Loading #42: Scissor Test ................................. ";
		//std::cout << "...............................................................";

		Core::GUI::Props_TextArea c;
		c.setOrigin(Core::GUI::CONSTRAIN_CENTER);
		c.setAnchor(Core::GUI::CONSTRAIN_CENTER);
		c.setWidth(200, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		c.setHeight(250, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		c.setPos(-250, 250);
		c.showLabel();
		c.setLineSpacing(0);
		c.setBuffer("\xC9\xCD\xCD\xCD\xCD\xCD\xBB\n"\
					"\xBA\xB0\xB0\xB0\xB0\xB0\xBA\n"\
					"\xBA\xB0\xB1\xB1\xB1\xB0\xBA\n"\
					"\xBA\xB0\xB1\xB2\xB1\xB0\xBA\n"\
					"\xBA\xB0\xB1\xB1\xB1\xB0\xBA\n"\
					"\xBA\xB0\xB0\xB0\xB0\xB0\xBA\n"\
					"\xC8\xCD\xCD\xCD\xCD\xCD\xBC\n"\
					"");
		Core::gui["GameMenu"]["Window 17"].TextArea.add("TextArea", c);


		Core::GUI::Props_Sprite cSprite;
		cSprite.setOrigin(Core::GUI::CONSTRAIN_CENTER);
		cSprite.setAnchor(Core::GUI::CONSTRAIN_CENTER);
		cSprite.setWidth(300, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		cSprite.setHeight(300, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		cSprite.setBorder(1, true);
		cSprite.setRadius(10);
		cSprite.setPos(250, -250);
		cSprite.enablePadding(Core::GUI::PADDING_ALL);
		cSprite.setImage("TestPattern.png");
		Core::gui["GameMenu"]["Window 17"].Sprite.add("Sprite", cSprite);

		{
			Core::GUI::Props_Window Slider_Window;
			Slider_Window.setOrigin(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
			Slider_Window.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
			Slider_Window.setWidth(500, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
			Slider_Window.setHeight(100, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
			Slider_Window.setPadding(10);
			Slider_Window.disablePadding();
			Slider_Window.disableScissor();
			Slider_Window.setBorder(1, 2);
			Slider_Window.setRadius(10);
			Slider_Window.setPos(-5, 0);
			Slider_Window.resetScrollable();
			Core::gui["GameMenu"]["Window 17"].add("Position", Slider_Window);

			Core::GUI::Props_Slider con;
			con.setOrigin(Core::GUI::CONSTRAIN_TOP);
			con.setAnchor(Core::GUI::CONSTRAIN_TOP);
			con.setWidth(60, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
			con.setHeight(15, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
			con.control.setHeight(80, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
			con.showLabel();
			con.showField();

			con.setPos(0, 0);		con.setMinMax(-500, 500);		con.setStep(1.0f, 10.0f, 100.0f);
			Core::gui["GameMenu"]["Window 17"]["Position"].Slider.add("TextArea: X", &Core::gui["GameMenu"]["Window 17"].TextArea("TextArea").pos.constraint.x, con);
			con.modPos(0, -20);		con.setMinMax(-500, 500);		con.setStep(1.0f, 10.0f, 100.0f);
			Core::gui["GameMenu"]["Window 17"]["Position"].Slider.add("TextArea: Y", &Core::gui["GameMenu"]["Window 17"].TextArea("TextArea").pos.constraint.y, con);
			con.modPos(0, -20);		con.setMinMax(-500, 500);		con.setStep(1.0f, 10.0f, 100.0f);
			Core::gui["GameMenu"]["Window 17"]["Position"].Slider.add("Sprite: X", &Core::gui["GameMenu"]["Window 17"].Sprite("Sprite").pos.constraint.x, con);
			con.modPos(0, -20);		con.setMinMax(-500, 500);		con.setStep(1.0f, 10.0f, 100.0f);
			Core::gui["GameMenu"]["Window 17"]["Position"].Slider.add("Sprite: Y", &Core::gui["GameMenu"]["Window 17"].Sprite("Sprite").pos.constraint.y, con);

			// Padding adjustment
			Slider_Window.setOrigin(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
			Slider_Window.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
//			Slider_Window.setPos(-5, 105);
			Slider_Window.modPos(0, 105);
			Slider_Window.resetScrollable();
//			Slider_Window.enableScissor();
			Core::gui["GameMenu"]["Window 17"].add("Padding", Slider_Window);

			con.setPos(0, 0);		con.setMinMax(-100, 100);		con.setStep(1.0f, 10.0f, 100.0f);
			Core::gui["GameMenu"]["Window 17"]["Padding"].Slider.add("Padding: T", &Core::gui["GameMenu"]["Window 17"].con->vPadding.top, con);
			con.modPos(0, -20);		con.setMinMax(-100, 100);		con.setStep(1.0f, 10.0f, 100.0f);
			Core::gui["GameMenu"]["Window 17"]["Padding"].Slider.add("Padding: B", &Core::gui["GameMenu"]["Window 17"].con->vPadding.bottom, con);
			con.modPos(0, -20);		con.setMinMax(-100, 100);		con.setStep(1.0f, 10.0f, 100.0f);
			Core::gui["GameMenu"]["Window 17"]["Padding"].Slider.add("Padding: L", &Core::gui["GameMenu"]["Window 17"].con->vPadding.left, con);
			con.modPos(0, -20);		con.setMinMax(-100, 100);		con.setStep(1.0f, 10.0f, 100.0f);
			Core::gui["GameMenu"]["Window 17"]["Padding"].Slider.add("Padding: R", &Core::gui["GameMenu"]["Window 17"].con->vPadding.right, con);
		}

		bOneShot[42] = true;
		std::cout << "Done" << std::endl;
	}

	if (!bOneShot[43]) {
		std::cout << "GUI: Loading #43: Progress Bar ................................. ";
		//std::cout << "...............................................................";

		// Standalone slider (internal value)
		Core::GUI::Props_Slider con;
		con.setOrigin(Core::GUI::CONSTRAIN_BOTTOM);
		con.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
		con.setWidth(60, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		con.setHeight(10, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		con.control.setHeight(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		con.showLabel();
		con.showField();
		con.setPos(0, 10);		con.setMinMax(0, 100);		con.setStep(1.0f, 2.0f, 10.0f);
		con.setToolTip("This slider is using an internal value and not tied\n"\
					   "to a value directly. The Progress Bars are tied to this\n"\
					   "Sliders internal value instead.");
		Core::gui["GameMenu"]["Window 18"].Slider.add("Progress", 25, con);

		Core::GUI::Props_ProgressBar prop;
		prop.setOrigin(Core::GUI::CONSTRAIN_TOP);
		prop.setAnchor(Core::GUI::CONSTRAIN_TOP);
		prop.setWidth(100, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		prop.setHeight(50, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		prop.setPos(0, -40);
		prop.setPadding(5);
		prop.disableScissor();
		prop.setToolTip("This is a standard progress bar using only\n"\
						"the most basic setup.");
//		Core::gui["GameMenu"]["Window 18"].ProgressBar.add("Progress Bar 1", 25, prop);
		Core::gui["GameMenu"]["Window 18"].ProgressBar.add("Progress Bar 1", &Core::gui["GameMenu"]["Window 18"].Slider["Progress"].getI()->getValuePtr(), prop);

		prop.setOrigin(Core::GUI::CONSTRAIN_TOP);
		prop.setAnchor(Core::GUI::CONSTRAIN_TOP);
		prop.setWidth(100, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		prop.setHeight(50, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		prop.modPos(0, -60);
		prop.setPadding(5);
		prop.disableScissor();
		prop.empty.setHeight(75, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		prop.empty.setBorder(1, 1);
		prop.empty.setRadius(10);
		prop.empty.setPadding(0);
		prop.empty.setStipplePattern(&Core::stipple[Core::stipple.STIPPLE_DOTS]);
		prop.empty.colorBack.base = &Core::colors[Core::colors().Red];
		prop.empty.colorBack.highlight = &Core::colors[Core::colors().Pink];
		prop.empty.colorBack.active = &Core::colors[Core::colors().Red];
		prop.fill.setBorder(1, 1);
		prop.fill.setRadius(10);
		prop.fill.colorBack.base = &Core::colors[Core::colors().Green];
		prop.fill.colorBack.highlight = &Core::colors[Core::colors().Light_green];
		prop.fill.colorBack.active = &Core::colors[Core::colors().Green];
		prop.field.colorBorder.base = &Core::colors[Core::colors().White];
		prop.field.colorBorder.highlight = &Core::colors[Core::colors().White];
		prop.field.colorBorder.active = &Core::colors[Core::colors().White];
		prop.field.colorBack.base = &Core::colors[Core::colors().White];
		prop.field.colorBack.highlight = &Core::colors[Core::colors().White];
		prop.field.colorBack.active = &Core::colors[Core::colors().White];
		prop.setToolTip("This progress bar is using custom colors and\n"\
						"modifications to the slider style. The stipple\n"\
						"pattern has been changed and the fill bar has\n"\
						"been given a border. To do this the padding on\n"\
						"the empty bar has been reduced to 0 so the fill\n"\
						"bar is being drawn on top of the empty bar.");
//		Core::gui["GameMenu"]["Window 18"].ProgressBar.add("Progress Bar 2", Core::gui["GameMenu"]["Window 18"].ProgressBar["Progress Bar 1"].getPointer(), prop);
		Core::gui["GameMenu"]["Window 18"].ProgressBar.add("Progress Bar 2", &Core::gui["GameMenu"]["Window 18"].Slider["Progress"].getI()->getValuePtr(), prop);

		// TODO: Add a slider to set progress amount
//		Core::GUI::Props_Slider con;
//		con.setOrigin(Core::GUI::CONSTRAIN_BOTTOM);
//		con.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
//		con.setWidth(60, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
//		con.setHeight(10, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
//		con.control.setHeight(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
//		con.showLabel();
//		con.showField();
//		con.setPos(0, 10);		con.setMinMax(0, 100);		con.setStep(1.0f);
//		Core::gui["GameMenu"]["Window 18"].Slider.add("Progress", Core::gui["GameMenu"]["Window 18"].ProgressBar["Progress Bar 1"].getPointer(), con);

		bOneShot[43] = true;
		std::cout << "Done" << std::endl;
	}


	if (!bOneShot[44]) {
		std::cout << "GUI: Loading #44: ComboBox ..................................... ";
		//std::cout << "...............................................................";

		Core::GUI::Props_ComboBox prop;
		prop.setOrigin(Core::GUI::CONSTRAIN_TOP_LEFT);
		prop.setAnchor(Core::GUI::CONSTRAIN_TOP_LEFT);
		//prop.setWidth(100, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		//prop.setHeight(100, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		prop.setPos(0, -40);
		prop.setToolTip("This is a ComboBox test that should show the\n"\
						"currently selected item and also when a button\n"\
						"is pressed a list is shown with alternate options\n"\
						"to choose from. This combo box uses default\n"\
						"settings which include an auto-hide of the item\n"\
						"list when the mouse leaves the combo box area.");

		using namespace Core::GUI::Object;
		using namespace std;
		using namespace Core;

		Core::gui["GameMenu"]["Window 19"].ComboBox.add("ComboBox1", prop).addItems(t_ComboBoxItems{make_pair("Item 0",1),
																								    make_pair("Item 1",2),
																									make_pair("Item 2",4),
																									make_pair("Item 3",8),
																									make_pair("Item 4",16),
																									make_pair("Item 5",32) });

		//Core::gui["GameMenu"]["Window 19"].ComboBox.add("ComboBox1", prop);

		//Core::gui["GameMenu"]["Window 19"].ComboBox.add("ComboBox1", prop).addItems(std::vector{std::pair<std::string, Core::t_BIFS>("test", 1)});

//		Core::gui["GameMenu"]["Window 19"].ComboBox.add("ComboBox1", prop);
		//Core::gui["GameMenu"]["Window 19"].ComboBox["ComboBox1"].addItem("Item 1", 2);
		//Core::gui["GameMenu"]["Window 19"].ComboBox["ComboBox1"].addItem("Item 2", 4);
		//Core::gui["GameMenu"]["Window 19"].ComboBox["ComboBox1"].addItem("Item 3", 8);
		//Core::gui["GameMenu"]["Window 19"].ComboBox["ComboBox1"].addItem("Item 4", 16);
		//Core::gui["GameMenu"]["Window 19"].ComboBox["ComboBox1"].addItem("Item 5", 32);


		prop.setOrigin(Core::GUI::CONSTRAIN_TOP_RIGHT);
		prop.setAnchor(Core::GUI::CONSTRAIN_TOP_RIGHT);
		prop.setWidth(200, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		prop.itemList.setPadding(1);
		//prop.setHeight(100, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		prop.setPos(0, -40);
		//prop.setPadding(0);
		prop.setToolTip("This is another combo box to showcase a larger\n"\
						"list of items with scrolling capability. This\n"\
						"combo box also has:\n\n"\
						" - Two different methods of adding items to the list\n"\
						" - Uses auto width/height\n"\
						" - Doesn't auto hide item list\n"\
						" - itemList padding set to 1 (border size)\n"\
						" - No border on up/down buttons");

		prop.autoWidth();
		prop.autoHeight();
		prop.setAutoHide(false);
		prop.scrollButton.setBorder(0, 0);
		//prop.item.autoHeight();	// FIXME: Doesn't work, likely because itemList sets height first and never updates after autoheight calculated

		// Adding some initial items at ComboBox creation
		Core::gui["GameMenu"]["Window 19"].ComboBox.add("ComboBox2", prop).addItems(t_ComboBoxItems{make_pair("Test Object 1", 1),
																									make_pair("Test Object 2", 2),
																									make_pair("Test Object 3", 3),
																									make_pair("Test Object 4", 4),
																									make_pair("Test Object 5", 5) });

		// Adding additional list items after ComboBox creation
		Core::gui["GameMenu"]["Window 19"].ComboBox["ComboBox2"].addItem("Test Object 6", 6);
		Core::gui["GameMenu"]["Window 19"].ComboBox["ComboBox2"].addItem("Test Object 7", 7);
		Core::gui["GameMenu"]["Window 19"].ComboBox["ComboBox2"].addItem("Test Object 8", 8);
		Core::gui["GameMenu"]["Window 19"].ComboBox["ComboBox2"].addItem("Test Object 9", 9);
		Core::gui["GameMenu"]["Window 19"].ComboBox["ComboBox2"].addItem("Test Object 10", 10);
		Core::gui["GameMenu"]["Window 19"].ComboBox["ComboBox2"].addItem("Test Object 11", 11);
		Core::gui["GameMenu"]["Window 19"].ComboBox["ComboBox2"].addItem("Test Object 12", 12);
		Core::gui["GameMenu"]["Window 19"].ComboBox["ComboBox2"].addItem("Test Object 13", 13);
		Core::gui["GameMenu"]["Window 19"].ComboBox["ComboBox2"].addItem("Test Object 14", 14);
		Core::gui["GameMenu"]["Window 19"].ComboBox["ComboBox2"].addItem("Test Object 15", 15);


		// Config/test buttons
		Core::GUI::Props_Button cButton;
		cButton.setOrigin(Core::GUI::CONSTRAIN_BOTTOM);
		cButton.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
		cButton.setWidth(200, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		cButton.setHeight(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		cButton.setBorder(1, true);
		cButton.setRadius(10);
		cButton.setButtonType(Core::GUI::BUTTON_ONESHOT);
		cButton.setPos(5, 5);
		cButton.setText("Erase Test Object 5");
		cButton.setToolTip("This button test the following two steps:\n"\
						   "  - First the button will remove the item named 'Test Object 5'\n"\
						   "  - Pressing a second time will call a fault reporting that the item doesn't exist");
		Core::gui["GameMenu"]["Window 19"].Button.add("Erase Test", false, cButton);
		//cButton.modPos(130, 0);
		//cButton.text = "WTF 2";
		//Core::gui["GameMenu"]["Window 19"].Button.add("NOP 2", false, cButton);
		//cButton.modPos(-260, 0);
		//cButton.text = "WTF 3";
		//Core::gui["GameMenu"]["Window 19"].Button.add("NOP 1", false, cButton);

		// Test Slider
		Core::GUI::Props_Slider con;
		con.setOrigin(Core::GUI::CONSTRAIN_BOTTOM);
		con.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);					// Center of button
		con.setWidth(50, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		con.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		con.control.setWidth(50, Core::GUI::SIZE_CONSTRAINT_RELATIVE);
		con.control.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
		con.showField();
		con.showLabel();
		con.setPrecision(5);
		con.setX(0);
		con.setY(200);
		con.setMinMax(0, 1);
		con.setStep(1.0f, 1.0f, 1.0f);
		con.setText("Testing");
		Core::gui["GameMenu"]["Window 19"].Slider.add("Switch Test", 0, con);

		bOneShot[44] = true;
		std::cout << "Done" << std::endl;
	}

	bInit = true;
}

/** ******************************************************************************************************************************
 *
 * ****************************************************************************************************************************** */
void _Admin::run() {
	/*
	 * Setup Complete - Run GUI
	 */
	if(bInit) {
		SDL_ShowCursor(SDL_ENABLE);
		glClear( GL_DEPTH_BUFFER_BIT );
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		bHasFocus = !Core::gui["GameMenu"].isActive();
		GetInput();
		Core::gui.exec("GameMenu");

		if(Core::gui["GameMenu"]["Window 19"].Button["Erase Test"].getState()) {
			Core::debug.log("ERASE");
			Core::gui["GameMenu"]["Window 19"].ComboBox["ComboBox2"].removeItem("Test Object 5");
		}

//		Core::debug.log("Global: Active Object: "+Core::GUI::Object::Base::c_Generic_Base::sActiveObject+", "+std::to_string(Core::GUI::Object::Base::c_Generic_Base::bFocusPresent));
//		Core::debug.log("Global: Scroll Object: "+Core::GUI::Object::Base::c_Generic_Base::sScrollObject+", "+std::to_string(Core::GUI::Object::Base::c_Generic_Base::bScrollFocus));

		// TESTING: Variant example and type deduction
//		std::variant<int, float, std::string> intFloatString;
//		intFloatString = "test";
//		std::cout << "intFloatString index = " << intFloatString.index() << "\n";

		// Draw Mouse State
		//Core::debug.log("  Check: "+std::to_string(Core::mouse->button.check[SDL_BUTTON_LEFT]));
		//Core::debug.log("Pressed: "+std::to_string(Core::mouse->button.pressed[SDL_BUTTON_LEFT]));
		//Core::debug.log(" Repeat: "+std::to_string(Core::mouse->button.repeat[SDL_BUTTON_LEFT]));
		//Core::debug.log("   Held: "+std::to_string(Core::mouse->button.held[SDL_BUTTON_LEFT]));

		// Draw ComboBox current values
//		Core::debug.log(Core::from_variant(Core::gui["GameMenu"]["Window 19"].ComboBox["ComboBox1"].getDataSetValue()), Core::debug.consoleColors.RED);
//		Core::debug.log(Core::from_variant(Core::gui["GameMenu"]["Window 19"].ComboBox["ComboBox2"].getDataSetValue()), Core::debug.consoleColors.RED);

		//Core::debug.log("Slider State: "+std::to_string(Core::gui["GameMenu"]["Window 5"].Slider["X - Vertical M"].getF()->getState()), Core::debug.consoleColors.RED);

		//Core::debug.log(std::to_string(Core::gui["GameMenu"]["Window 19"].ComboBox["ComboBox1"].getItem()), Core::debug.consoleColors.RED);
		//Core::debug.log(std::to_string(Core::gui["GameMenu"]["Window 19"].ComboBox["ComboBox2"].getItem()), Core::debug.consoleColors.RED);

//		Core::debug.log(std::to_string(Core::gui["GameMenu"]["Window 2"].Button["Simplex"].getState()), Core::debug.consoleColors.GREEN);
//		Core::debug.log(std::to_string(Core::gui["GameMenu"]["Window 2"].Button["Fractal"].getState()), Core::debug.consoleColors.GREEN);
//		Core::debug.log(std::to_string(Core::gui["GameMenu"]["Window 2"].Button["Sliders"].getState()), Core::debug.consoleColors.GREEN);
//		Core::debug.log(std::to_string(Core::gui["GameMenu"]["Window 2"].Button["Text Boxes"].getState()), Core::debug.consoleColors.GREEN);
//		Core::debug.log(std::to_string(Core::gui["GameMenu"]["Window 2"].Button["Colors"].getState()), Core::debug.consoleColors.GREEN);
//		Core::debug.log(std::to_string(Core::gui["GameMenu"]["Window 2"].Button["CheckBox"].getState()), Core::debug.consoleColors.GREEN);
//		Core::debug.log(std::to_string(Core::gui["GameMenu"]["Window 2"].Button["Settings"].getState()), Core::debug.consoleColors.GREEN);
//		Core::debug.log(std::to_string(Core::gui["GameMenu"]["Window 2"].Button["Icons"].getState()), Core::debug.consoleColors.GREEN);
//		Core::debug.log(std::to_string(Core::gui["GameMenu"]["Window 2"].Button["Images"].getState()), Core::debug.consoleColors.GREEN);
//		Core::debug.log(std::to_string(Core::gui["GameMenu"]["Window 2"].Button["Stipple"].getState()), Core::debug.consoleColors.GREEN);
//		Core::debug.log(std::to_string(Core::gui["GameMenu"]["Window 2"].Button["Labels"].getState()), Core::debug.consoleColors.GREEN);
//		Core::debug.log(std::to_string(Core::gui["GameMenu"]["Window 2"].Button["ColorBox"].getState()), Core::debug.consoleColors.GREEN);
//		Core::debug.log(std::to_string(Core::gui["GameMenu"]["Window 2"].Button["ColorPicker"].getState()), Core::debug.consoleColors.GREEN);
//		Core::debug.log(std::to_string(Core::gui["GameMenu"]["Window 2"].Button["Scissor"].getState()), Core::debug.consoleColors.GREEN);
//		Core::debug.log(std::to_string(Core::gui["GameMenu"]["Window 2"].Button["Progress Bar"].getState()), Core::debug.consoleColors.GREEN);
//		Core::debug.log(std::to_string(Core::gui["GameMenu"]["Window 2"].Button["ComboBox"].getState()), Core::debug.consoleColors.GREEN);
//		Core::debug.log(std::to_string(Core::gui["GameMenu"]["Window 2"].Button["Lighting"].getState()), Core::debug.consoleColors.GREEN);
//		Core::debug.log(std::to_string(Core::gui["GameMenu"]["Window 2"].Button["Skill Tree"].getState()), Core::debug.consoleColors.GREEN);


		// DEBUG: Print all groups and active objects to console
//		for(int n=0; n<Core::groups.count(); n++) {
//			Core::debug.log(Core::groups[n].name, Core::debug.consoleColors.GREEN);
//			//if(Core::groups[n].name == "Menu Buttons") {
//				Core::debug.log("  "+Core::groups[n].object, Core::debug.consoleColors.green);
//			//}
//		}

		/*
		 * Tie Window Properties to Settings Sliders
		 */
		if(Core::GUI::Props::bGlobalSettings) {
			for(int n=0; n<=21; n++) {
				if( n != 2 ) {
					std::string sWindow = "Window "+std::to_string(n);
					//std::cout << "sWindow = " << sWindow << "\n";
					Core::gui["GameMenu"][sWindow].con->radius			= Core::gui["GameMenu"]["Window 9"].Slider["Radius"].getI()->getValuePtr();
					Core::gui["GameMenu"][sWindow].con->borderNormal	= Core::gui["GameMenu"]["Window 9"].Slider["Border"].getI()->getValuePtr();
					Core::gui["GameMenu"][sWindow].con->vPadding.top	= Core::gui["GameMenu"]["Window 9"].Slider["Pad: T"].getI()->getValuePtr();
					Core::gui["GameMenu"][sWindow].con->vPadding.bottom	= Core::gui["GameMenu"]["Window 9"].Slider["Pad: B"].getI()->getValuePtr();
					Core::gui["GameMenu"][sWindow].con->vPadding.left	= Core::gui["GameMenu"]["Window 9"].Slider["Pad: L"].getI()->getValuePtr();
					Core::gui["GameMenu"][sWindow].con->vPadding.right	= Core::gui["GameMenu"]["Window 9"].Slider["Pad: R"].getI()->getValuePtr();
				}
			}
		}

		/*
		 * Group states
		 */
		// Stipple Pattern
		Core::gui["GameMenu"]["Window 12"].con->setStipplePattern( &Core::stipple[std::get<int>(Core::gui["GameMenu"]["Window 12"].CheckBox.groupState("Stipple Group"))] );

		// Checkbox Sample
		//Core::gui["GameMenu"]["Window 8"].CheckBox("Check Sample").label.setOrigin(Core::gui["GameMenu"]["Window 8"].CheckBox.groupState("Check States Sample", 0));
		Core::gui["GameMenu"]["Window 8"].CheckBox("Check Sample").label.setOrigin(
				std::get<int>(Core::gui["GameMenu"]["Window 8"].CheckBox.groupState("Check States Sample", 0))
		);

		//Core::gui["GameMenu"]["Window 8"].CheckBox("Check Sample").label.setAnchor(Core::gui["GameMenu"]["Window 8"].CheckBox.groupState("Check States Sample", 1));
		Core::gui["GameMenu"]["Window 8"].CheckBox("Check Sample").label.setAnchor(
			std::get<int>(Core::gui["GameMenu"]["Window 8"].CheckBox.groupState("Check States Sample", 1))
		);

		//Core::gui["GameMenu"]["Window 8"].CheckBox("Check Sample").label.setPos(Core::gui["GameMenu"]["Window 8"].CheckBox.groupState("Check States Sample", 2), Core::gui["GameMenu"]["Window 8"].CheckBox.groupState(3, 3));
		Core::gui["GameMenu"]["Window 8"].CheckBox("Check Sample").label.setPos(
			std::get<int>(Core::gui["GameMenu"]["Window 8"].CheckBox.groupState("Check States Sample", 2)),
			std::get<int>(Core::gui["GameMenu"]["Window 8"].CheckBox.groupState("Check States Sample", 3))
		);

		/*
		 * Update pointers for simplex noise generator selectionc
		 */
		if(Core::gui["GameMenu"]["Window 3"].Slider["Simplex Generator"].stateChanged()) {
			Core::gui["GameMenu"]["Window 3"].Slider["Resolution"]		.setPointer(&Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].res);
			Core::gui["GameMenu"]["Window 3"].Slider["Tex Scale"]		.setPointer(&Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].tex_scale);
			Core::gui["GameMenu"]["Window 3"].Slider["Terrain Size"]	.setPointer(&Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].terrain_size);
			Core::gui["GameMenu"]["Window 3"].Slider["Terrain Height"]	.setPointer(&Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].terrain_height_offset);
			Core::gui["GameMenu"]["Window 3"].Slider["Offset X"]		.setPointer(&Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].offset.x);
			Core::gui["GameMenu"]["Window 3"].Slider["Offset Y"]		.setPointer(&Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].offset.y);
			Core::gui["GameMenu"]["Window 3"].Slider["Delta"]			.setPointer(&Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].delta);
			Core::gui["GameMenu"]["Window 3"].Slider["Frequency"]		.setPointer(&Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].frequency);
			Core::gui["GameMenu"]["Window 3"].Slider["Lacunarity"]		.setPointer(&Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].lacunarity);
			Core::gui["GameMenu"]["Window 3"].Slider["Persistance"]		.setPointer(&Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].persistance);
			Core::gui["GameMenu"]["Window 3"].Slider["Scale"]			.setPointer(&Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].scale);
			Core::gui["GameMenu"]["Window 3"].Slider["Octaves"]			.setPointer(&Core::gameVars->debug.noise.simplex[Core::gameVars->debug.noise.iCurrentSimplex].octaves);
		}

		/*
		 * Change slider pointers for lighting
		 */
//		if(Core::gui["GameMenu"]["Window 5"].Slider["DebugLight"].state()==Core::_Mouse::MOUSE_LEFT_DOWN || Core::gui["GameMenu"]["Window 5"].Slider["DebugLight"].state()==Core::_Mouse::MOUSE_LEFT) {
		if(Core::gui["GameMenu"]["Window 1"].Slider["DebugLight"].stateChanged()) {
			Core::gui["GameMenu"]["Window 1"].Slider["Light Pos X"].setPointer(&game->world->lights->GetPos(game->iDebugLight).x);
			Core::gui["GameMenu"]["Window 1"].Slider["Light Pos Y"].setPointer(&game->world->lights->GetPos(game->iDebugLight).y);
			Core::gui["GameMenu"]["Window 1"].Slider["Light Pos Z"].setPointer(&game->world->lights->GetPos(game->iDebugLight).z);
			Core::gui["GameMenu"]["Window 1"].Slider["Light Dir X"].setPointer(&game->world->lights->GetDir(game->iDebugLight).x);
			Core::gui["GameMenu"]["Window 1"].Slider["Light Dir Y"].setPointer(&game->world->lights->GetDir(game->iDebugLight).y);
			Core::gui["GameMenu"]["Window 1"].Slider["Light Dir Z"].setPointer(&game->world->lights->GetDir(game->iDebugLight).z);
		}
		game->world->o3d->data.items[game->iDebugObject].posMod = game->world->lights->GetPos(game->iDebugLight);
		game->world->o3d->data.items[game->iDebugObject].rotMod = game->world->lights->GetDir(game->iDebugLight);

		// Update map noise
		if(Core::gameVars->debug.gui.b1 || Core::gameVars->debug.gui.b2 || Core::gameVars->debug.gui.b3 || Core::gameVars->debug.gui.b4) {
			game->world->map->update();
		}

		Core::gameVars->font.update();	// FIXME: Make font standalone class and fix resize
	////	Core::textSys->init();			// FIXME: Needs either a VAO update, or scaling based on font size

		// Manage visible windows
		// FIXME: Make getState() and getObjectState easier to identify (ex: active() and state())

		Core::gui["GameMenu"]["Window 0"].hide();
		Core::gui["GameMenu"]["Window 1"].hide();
		Core::gui["GameMenu"]["Window 3"].hide();
		Core::gui["GameMenu"]["Window 4"].hide();
		Core::gui["GameMenu"]["Window 5"].hide();
		Core::gui["GameMenu"]["Window 6"].hide();
		Core::gui["GameMenu"]["Window 7"].hide();
		Core::gui["GameMenu"]["Window 8"].hide();
		Core::gui["GameMenu"]["Window 9"].hide();
		Core::gui["GameMenu"]["Window 10"].hide();
		Core::gui["GameMenu"]["Window 11"].hide();
		Core::gui["GameMenu"]["Window 12"].hide();
		Core::gui["GameMenu"]["Window 13"].hide();
		Core::gui["GameMenu"]["Window 14"].hide();
		if(!Core::gui["GameMenu"]["Window 2"].Button["Skill Tree"].getState()) {
			Core::gui["GameMenu"]["Window 14-0"].hide();
			Core::gui["GameMenu"]["Window 14-1"].hide();
			Core::gui["GameMenu"]["Window 14-2"].hide();
			Core::gui["GameMenu"]["Window 14-3"].hide();
			Core::gui["GameMenu"]["Window 14-4"].hide();
			Core::gui["GameMenu"]["Window 14-5"].hide();
			Core::gui["GameMenu"]["Window 14-6"].hide();
			Core::gui["GameMenu"]["Window 14-7"].hide();
			Core::gui["GameMenu"]["Window 14-8"].hide();
		}
		Core::gui["GameMenu"]["Window 15"].hide();
		Core::gui["GameMenu"]["Window 16"].hide();
		Core::gui["GameMenu"]["Window 17"].hide();
		Core::gui["GameMenu"]["Window 18"].hide();
		Core::gui["GameMenu"]["Window 19"].hide();
		Core::gui["GameMenu"]["Window 20"].hide();
		Core::gui["GameMenu"]["Window 21"].hide();

		if(Core::gui["GameMenu"]["Window 2"].Button["Simplex"].getState())				Core::gui["GameMenu"]["Window 3"].show();
		else if(Core::gui["GameMenu"]["Window 2"].Button["Fractal"].getState())			Core::gui["GameMenu"]["Window 4"].show();
		else if(Core::gui["GameMenu"]["Window 2"].Button["Sliders"].getState())			Core::gui["GameMenu"]["Window 5"].show();
		else if(Core::gui["GameMenu"]["Window 2"].Button["Text Boxes"].getState())		Core::gui["GameMenu"]["Window 6"].show();
		else if(Core::gui["GameMenu"]["Window 2"].Button["Colors"].getState())			Core::gui["GameMenu"]["Window 7"].show();
		else if(Core::gui["GameMenu"]["Window 2"].Button["CheckBox"].getState())		Core::gui["GameMenu"]["Window 8"].show();
		else if(Core::gui["GameMenu"]["Window 2"].Button["Settings"].getState())		Core::gui["GameMenu"]["Window 9"].show();
		else if(Core::gui["GameMenu"]["Window 2"].Button["Icons"].getState())			Core::gui["GameMenu"]["Window 10"].show();
		else if(Core::gui["GameMenu"]["Window 2"].Button["Images"].getState())			Core::gui["GameMenu"]["Window 11"].show();
		else if(Core::gui["GameMenu"]["Window 2"].Button["Stipple"].getState())			Core::gui["GameMenu"]["Window 12"].show();
		else if(Core::gui["GameMenu"]["Window 2"].Button["Labels"].getState())			Core::gui["GameMenu"]["Window 13"].show();
		else if(Core::gui["GameMenu"]["Window 2"].Button["ColorBox"].getState())		Core::gui["GameMenu"]["Window 15"].show();
		else if(Core::gui["GameMenu"]["Window 2"].Button["ColorPicker"].getState())		Core::gui["GameMenu"]["Window 16"].show();
		else if(Core::gui["GameMenu"]["Window 2"].Button["Scissor"].getState())			Core::gui["GameMenu"]["Window 17"].show();
		else if(Core::gui["GameMenu"]["Window 2"].Button["Progress Bar"].getState())	Core::gui["GameMenu"]["Window 18"].show();
		else if(Core::gui["GameMenu"]["Window 2"].Button["ComboBox"].getState())		Core::gui["GameMenu"]["Window 19"].show();
		else if(Core::gui["GameMenu"]["Window 2"].Button["Lighting"].getState())		Core::gui["GameMenu"]["Window 1"].show();
		else if(Core::gui["GameMenu"]["Window 2"].Button["Skill Tree"].getState()) {
			Core::gui["GameMenu"]["Window 14"].show();
			// These are oneshot controlled windows
			if(		Core::gui["GameMenu"]["Window 14-1"].Button["BACK"].getState() ||
					Core::gui["GameMenu"]["Window 14-2"].Button["BACK"].getState() ||
					Core::gui["GameMenu"]["Window 14-3"].Button["BACK"].getState() ||
					Core::gui["GameMenu"]["Window 14-4"].Button["BACK"].getState() ||
					Core::gui["GameMenu"]["Window 14-5"].Button["BACK"].getState() ||
					Core::gui["GameMenu"]["Window 14-6"].Button["BACK"].getState() ||
					Core::gui["GameMenu"]["Window 14-7"].Button["BACK"].getState() ||
					Core::gui["GameMenu"]["Window 14-8"].Button["BACK"].getState()) {
				Core::gui["GameMenu"]["Window 14-0"].show();
				Core::gui["GameMenu"]["Window 14-1"].hide();
				Core::gui["GameMenu"]["Window 14-2"].hide();
				Core::gui["GameMenu"]["Window 14-3"].hide();
				Core::gui["GameMenu"]["Window 14-4"].hide();
				Core::gui["GameMenu"]["Window 14-5"].hide();
				Core::gui["GameMenu"]["Window 14-6"].hide();
				Core::gui["GameMenu"]["Window 14-7"].hide();
				Core::gui["GameMenu"]["Window 14-8"].hide();
			}
			else if(Core::gui["GameMenu"]["Window 14-0"].Button["Class 1"].getState() ||
					Core::gui["GameMenu"]["Window 14-0"].Button["Class 2"].getState() ||
					Core::gui["GameMenu"]["Window 14-0"].Button["Class 3"].getState() ||
					Core::gui["GameMenu"]["Window 14-0"].Button["Class 4"].getState() ||
					Core::gui["GameMenu"]["Window 14-0"].Button["Class 5"].getState() ||
					Core::gui["GameMenu"]["Window 14-0"].Button["Class 6"].getState() ||
					Core::gui["GameMenu"]["Window 14-0"].Button["Class 7"].getState() ||
					Core::gui["GameMenu"]["Window 14-0"].Button["Class 8"].getState()) {
				Core::gui["GameMenu"]["Window 14-0"].hide();
				Core::gui["GameMenu"]["Window 14-1"].hide();
				Core::gui["GameMenu"]["Window 14-2"].hide();
				Core::gui["GameMenu"]["Window 14-3"].hide();
				Core::gui["GameMenu"]["Window 14-4"].hide();
				Core::gui["GameMenu"]["Window 14-5"].hide();
				Core::gui["GameMenu"]["Window 14-6"].hide();
				Core::gui["GameMenu"]["Window 14-7"].hide();
				Core::gui["GameMenu"]["Window 14-8"].hide();
			}

			if(Core::gui["GameMenu"]["Window 14-0"].Button["Class 1"].getState())		Core::gui["GameMenu"]["Window 14-1"].show();
			else if(Core::gui["GameMenu"]["Window 14-0"].Button["Class 2"].getState())	Core::gui["GameMenu"]["Window 14-2"].show();
			else if(Core::gui["GameMenu"]["Window 14-0"].Button["Class 3"].getState())	Core::gui["GameMenu"]["Window 14-3"].show();
			else if(Core::gui["GameMenu"]["Window 14-0"].Button["Class 4"].getState())	Core::gui["GameMenu"]["Window 14-4"].show();
			else if(Core::gui["GameMenu"]["Window 14-0"].Button["Class 5"].getState())	Core::gui["GameMenu"]["Window 14-5"].show();
			else if(Core::gui["GameMenu"]["Window 14-0"].Button["Class 6"].getState())	Core::gui["GameMenu"]["Window 14-6"].show();
			else if(Core::gui["GameMenu"]["Window 14-0"].Button["Class 7"].getState())	Core::gui["GameMenu"]["Window 14-7"].show();
			else if(Core::gui["GameMenu"]["Window 14-0"].Button["Class 8"].getState())	Core::gui["GameMenu"]["Window 14-8"].show();
			else if(!Core::gui["GameMenu"]["Window 14-0"].visible() &&
					!Core::gui["GameMenu"]["Window 14-1"].visible() &&
					!Core::gui["GameMenu"]["Window 14-2"].visible() &&
					!Core::gui["GameMenu"]["Window 14-3"].visible() &&
					!Core::gui["GameMenu"]["Window 14-4"].visible() &&
					!Core::gui["GameMenu"]["Window 14-5"].visible() &&
					!Core::gui["GameMenu"]["Window 14-6"].visible() &&
					!Core::gui["GameMenu"]["Window 14-7"].visible() &&
					!Core::gui["GameMenu"]["Window 14-8"].visible()) {
				Core::gui["GameMenu"]["Window 14-0"].show();
				Core::gui["GameMenu"]["Window 14-1"].hide();
				Core::gui["GameMenu"]["Window 14-2"].hide();
				Core::gui["GameMenu"]["Window 14-3"].hide();
				Core::gui["GameMenu"]["Window 14-4"].hide();
				Core::gui["GameMenu"]["Window 14-5"].hide();
				Core::gui["GameMenu"]["Window 14-6"].hide();
				Core::gui["GameMenu"]["Window 14-7"].hide();
				Core::gui["GameMenu"]["Window 14-8"].hide();
			}
		}
	}
	else {
		bHasFocus = false;
		GetInput();
		std::cout << "GUI not configured! Call Init();\n";
	}
}

void _Admin::GetInput() {
	SDL_PumpEvents();
	Core::mouse->update(Core::gameVars->screen.half.x, Core::gameVars->screen.half.y);

	// TODO: Add a ReturnFocus function, uses a timeout
	keyboard.event = SDL_GetKeyboardState(NULL);
	keyboard.update();

	/*
	 * Skip a cycle, prevents carryover from calling routine (runGame->Admin causes duplicate F1 first time)
	 * This happens because this module has its own copy of "keyboard"
	 *
	 * Also only process input if we have focus. events are still processed which allows oneshot key presses
	 * 	to be detected as already pressed when focus returns instead of detected as a new keypress. Repeat
	 * 	keys have no way of being detected in the same fashion.
	 *
	 * Focus is used in GUIs to capture the keyboard/mouse input
	 */
	if(!bFirstRun && bHasFocus) ProcessInput();
	else bFirstRun = false;
}

void _Admin::ProcessInput() {

//	std::cout << "ProcessInput - Admin" << std::endl;

	if (keyboard.keys[SDLK_ESCAPE].bActive) {
		Core::gameVars->runState.quit=true;
	}
	if (keyboard.keys[SDLK_RETURN].bActive){
//		Core::menuSys->gettingInput=false;
	}
	if (keyboard.keys[SDLK_LCTRL].bActive){
	}
	if (keyboard.keys[SDLK_LSHIFT].bActive){
	}
	if (!keyboard.keys[SDLK_LSHIFT].bActive && !keyboard.keys[SDLK_LCTRL].bActive) {
	}
	if (keyboard.keys[SDLK_a].bActive){
	}
	if (keyboard.keys[SDLK_d].bActive){
	}
	if (keyboard.keys[SDLK_q].bActive){
	}
	if (keyboard.keys[SDLK_e].bActive){
	}
	if (keyboard.keys[SDLK_w].bActive) {
	}
	if (keyboard.keys[SDLK_s].bActive) {
	}
	if (keyboard.keys[SDLK_r].bActive) {
	}
	if (keyboard.keys[SDLK_f].bActive) {
	}
	if (keyboard.keys[SDLK_DELETE].bActive) {
	}
	if (keyboard.keys[SDLK_PAGEDOWN].bActive) {
	}
	if (keyboard.keys[SDLK_INSERT].bActive) {
	}
	if (keyboard.keys[SDLK_PAGEUP].bActive) {
	}
	if (keyboard.keys[SDLK_HOME].bActive) {
	}
	if (keyboard.keys[SDLK_END].bActive) {
	}
	if (keyboard.keys[SDLK_EQUALS].bActive) {
	}
	if (keyboard.keys[SDLK_MINUS].bActive) {
	}
	if (keyboard.keys[SDLK_BACKQUOTE].bActive) {
//		printf(">Entering Console...\n");
//		gameVars->state.console=true;
	}
	if (keyboard.keys[SDLK_F1].bActive) {
		Core::gameVars->runState.admin=false;
//		bShowOneShot = false;
		Core::mouse->ToggleMouse(SDL_TRUE);
		//SDL_WarpMouseInWindow(Core::glinit->window, Core::gameVars->screen.fHalfW, Core::gameVars->screen.fHalfH);
		//SDL_ShowCursor(SDL_DISABLE);
	}
	if (keyboard.keys[SDLK_F2].bActive) {
	}
	if (keyboard.keys[SDLK_F3].bActive) {
	}
	if (keyboard.keys[SDLK_F4].bActive) {
	}
	if (keyboard.keys[SDLK_F5].bActive) {
	}
	if (keyboard.keys[SDLK_F6].bActive) {
	}
	if (keyboard.keys[SDLK_F7].bActive) {
	}
	if (keyboard.keys[SDLK_F8].bActive) {
	}
	if (keyboard.keys[SDLK_F9].bActive) {
	}
	if (keyboard.keys[SDLK_F10].bActive) {
	}
	if (keyboard.keys[SDLK_F11].bActive) {
	}
	if (keyboard.keys[SDLK_F12].bActive) {
	}
//	if (gameVars->controls.mouse.relX<-gameVars->controls.mouse.deadX) {
//	}
//	if (gameVars->controls.mouse.relX>gameVars->controls.mouse.deadX) {
//	}
//	if (gameVars->controls.mouse.relY<-gameVars->controls.mouse.deadY) {
//	}
//	if (gameVars->controls.mouse.relY>gameVars->controls.mouse.deadY) {
//	}
}

void _Admin::draw(){
	//SDL_GL_SwapBuffers();
}
/*	============================ MENU ADDITION SAMPLE ============================

	else if (eMenu==ADMIN_) {
		gameSys.drawText(13, 2, "> Timers");

		int cy = 3;
		gameSys.menuSys.draw(3, ++cy, iVx, "Manual Sun",	&gameVars->debug.manual_sun);
		gameSys.menuSys.draw(3, ++cy, iVx, "Load",				&gameVars->debug.time.load);
		gameSys.menuSys.draw(3, ++cy, iVx, "GameLoop",		&gameVars->debug.time.gameLoop);
		gameSys.menuSys.draw(3, ++cy, iVx, "Debug",			&gameVars->debug.time.debug);
		gameSys.menuSys.draw(3, ++cy, iVx, "runWorld",		&gameVars->debug.time.runWorld);
		gameSys.menuSys.draw(3, ++cy, iVx, "Input",			&gameVars->debug.time.input);
		gameSys.menuSys.draw(3, ++cy, iVx, "GameUpdate",	&gameVars->debug.time.gameUpdate);
		gameSys.menuSys.draw(3, ++cy, iVx, "MotionBlur",	&gameVars->debug.time.motionBlur);
		gameSys.menuSys.draw(3, ++cy, iVx, "GameDraw",		&gameVars->debug.time.gameDraw);

		gameSys.menuSys.draw(3, cy+=2, iVx, "Capture",		&gameVars->debug.time.capture);
		gameSys.menuSys.draw(3, ++cy, iVx, "Window",			&gameVars->debug.time.window);
		gameSys.menuSys.draw(3, ++cy, iVx, "Command",		&gameVars->debug.time.command);
		gameSys.menuSys.draw(3, ++cy, iVx, "Buffer",			&gameVars->debug.time.buffer);

		if (gameSys.menuSys.draw(3, iBy, "< Back")==MOUSE_LEFT) eMenu=ADMIN_MAIN;
	}

 */
#endif /* RUNADMIN_H_ */
