/*
 * SkillTree.h
 *
 *  Created on: Jun 20, 2020
 *      Author: bcthund
 */

#ifndef GAME_RUNADMIN_SKILLTREE_H_
#define GAME_RUNADMIN_SKILLTREE_H_

void _Admin::initSkillTree() {
	Core::GUI::Props_Button con_button;
	con_button.setOrigin(Core::GUI::CONSTRAIN_BOTTOM);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
	con_button.setBorder(1, false);
	con_button.setRadius(0);
//		con_button.setGroup(4);		// FIXME: Make groups more intuitive (by name only preferred)
	con_button.setButtonType(Core::GUI::BUTTON_TOGGLE);

	// FIXME: Add an enable bit to buttons/checkboxes, sliders, fields, etc. Allows their functionality to be controlled externally.

	int y=20;
	std::string sWin = "Window 14-0";
	con_button.setWidth(600, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("Button A", false, con_button);

	y += 40;
	con_button.setWidth(150, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setPos(-225, y);	Core::gui["GameMenu"][sWin].Button.add("A-1000", false, con_button);
	con_button.setPos( -75, y);	Core::gui["GameMenu"][sWin].Button.add("A-0100", false, con_button);
	con_button.setPos(  75, y);	Core::gui["GameMenu"][sWin].Button.add("A-0010", false, con_button);
	con_button.setPos( 225, y);	Core::gui["GameMenu"][sWin].Button.add("A-0001", false, con_button);
	Core::gui["GameMenu"][sWin].Button["A-1000"].setEnableAPtr(Core::gui["GameMenu"][sWin].Button["Button A"].getPointer());
	Core::gui["GameMenu"][sWin].Button["A-0100"].setEnableAPtr(Core::gui["GameMenu"][sWin].Button["Button A"].getPointer());
	Core::gui["GameMenu"][sWin].Button["A-0010"].setEnableAPtr(Core::gui["GameMenu"][sWin].Button["Button A"].getPointer());
	Core::gui["GameMenu"][sWin].Button["A-0001"].setEnableAPtr(Core::gui["GameMenu"][sWin].Button["Button A"].getPointer());

	y += 40;
	con_button.setWidth(150, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setPos(-225, y);	Core::gui["GameMenu"][sWin].Button.add("A-2000", false, con_button);
	con_button.setPos( -75, y);	Core::gui["GameMenu"][sWin].Button.add("A-0200", false, con_button);
	con_button.setPos(  75, y);	Core::gui["GameMenu"][sWin].Button.add("A-0020", false, con_button);
	con_button.setPos( 225, y);	Core::gui["GameMenu"][sWin].Button.add("A-0002", false, con_button);
	Core::gui["GameMenu"][sWin].Button["A-2000"].setEnableAPtr(Core::gui["GameMenu"][sWin].Button["A-1000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["A-0200"].setEnableAPtr(Core::gui["GameMenu"][sWin].Button["A-0100"].getPointer());
	Core::gui["GameMenu"][sWin].Button["A-0020"].setEnableAPtr(Core::gui["GameMenu"][sWin].Button["A-0010"].getPointer());
	Core::gui["GameMenu"][sWin].Button["A-0002"].setEnableAPtr(Core::gui["GameMenu"][sWin].Button["A-0001"].getPointer());

	y += 40;
	con_button.setWidth(150, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setPos(-225, y);	Core::gui["GameMenu"][sWin].Button.add("A-3000", false, con_button);
	con_button.setPos( -75, y);	Core::gui["GameMenu"][sWin].Button.add("A-0300", false, con_button);
	con_button.setPos(  75, y);	Core::gui["GameMenu"][sWin].Button.add("A-0030", false, con_button);
	con_button.setPos( 225, y);	Core::gui["GameMenu"][sWin].Button.add("A-0003", false, con_button);
	Core::gui["GameMenu"][sWin].Button["A-3000"].setEnableAPtr(Core::gui["GameMenu"][sWin].Button["A-2000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["A-0300"].setEnableAPtr(Core::gui["GameMenu"][sWin].Button["A-0200"].getPointer());
	Core::gui["GameMenu"][sWin].Button["A-0030"].setEnableAPtr(Core::gui["GameMenu"][sWin].Button["A-0020"].getPointer());
	Core::gui["GameMenu"][sWin].Button["A-0003"].setEnableAPtr(Core::gui["GameMenu"][sWin].Button["A-0002"].getPointer());

	y += 40;
	con_button.setWidth(75, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
	con_button.setPos(-225, y);	Core::gui["GameMenu"][sWin].Button.add("B-1000", false, con_button);
	con_button.setPos(-150, y);	Core::gui["GameMenu"][sWin].Button.add("B-0100", false, con_button);
	con_button.setPos( -75, y);	Core::gui["GameMenu"][sWin].Button.add("B-0010", false, con_button);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("B-0001", false, con_button);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("C-1000", false, con_button);
	con_button.setPos(  75, y);	Core::gui["GameMenu"][sWin].Button.add("C-0100", false, con_button);
	con_button.setPos( 150, y);	Core::gui["GameMenu"][sWin].Button.add("C-0010", false, con_button);
	con_button.setPos( 225, y);	Core::gui["GameMenu"][sWin].Button.add("C-0001", false, con_button);

	y += 40;
	con_button.setWidth(75, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
	con_button.setPos(-225, y);	Core::gui["GameMenu"][sWin].Button.add("B-2000", false, con_button);
	con_button.setPos(-150, y);	Core::gui["GameMenu"][sWin].Button.add("B-0200", false, con_button);
	con_button.setPos( -75, y);	Core::gui["GameMenu"][sWin].Button.add("B-0020", false, con_button);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("B-0002", false, con_button);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("C-2000", false, con_button);
	con_button.setPos(  75, y);	Core::gui["GameMenu"][sWin].Button.add("C-0200", false, con_button);
	con_button.setPos( 150, y);	Core::gui["GameMenu"][sWin].Button.add("C-0020", false, con_button);
	con_button.setPos( 225, y);	Core::gui["GameMenu"][sWin].Button.add("C-0002", false, con_button);

	// Enable Pointers for B-1000 to C-0001
	Core::gui["GameMenu"][sWin].Button["B-1000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["A-3000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-1000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0200"].getPointer());

	Core::gui["GameMenu"][sWin].Button["B-0100"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["A-3000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0100"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-2000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0100"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0020"].getPointer());

	Core::gui["GameMenu"][sWin].Button["B-0010"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["A-0300"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0010"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0200"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0010"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0002"].getPointer());

	Core::gui["GameMenu"][sWin].Button["B-0001"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["A-0300"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0001"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0020"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0001"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-2000"].getPointer());

	Core::gui["GameMenu"][sWin].Button["C-1000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["A-0030"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-1000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0002"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-1000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0200"].getPointer());

	Core::gui["GameMenu"][sWin].Button["C-0100"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["A-0030"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0100"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-2000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0100"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0020"].getPointer());

	Core::gui["GameMenu"][sWin].Button["C-0010"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["A-0003"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0010"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0200"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0010"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0002"].getPointer());

	Core::gui["GameMenu"][sWin].Button["C-0001"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["A-0003"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0001"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0020"].getPointer());

	y += 40;
	con_button.setWidth(75, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
	con_button.setPos(-225, y);	Core::gui["GameMenu"][sWin].Button.add("B-3000", false, con_button);
	con_button.setPos(-150, y);	Core::gui["GameMenu"][sWin].Button.add("B-0300", false, con_button);
	con_button.setPos( -75, y);	Core::gui["GameMenu"][sWin].Button.add("B-0030", false, con_button);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("B-0003", false, con_button);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("C-3000", false, con_button);
	con_button.setPos(  75, y);	Core::gui["GameMenu"][sWin].Button.add("C-0300", false, con_button);
	con_button.setPos( 150, y);	Core::gui["GameMenu"][sWin].Button.add("C-0030", false, con_button);
	con_button.setPos( 225, y);	Core::gui["GameMenu"][sWin].Button.add("C-0003", false, con_button);

	// Enable Pointers for B-2000 to C-0002
	Core::gui["GameMenu"][sWin].Button["B-2000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-1000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-2000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0300"].getPointer());

	Core::gui["GameMenu"][sWin].Button["B-0200"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0100"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0200"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-3000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0200"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0030"].getPointer());

	Core::gui["GameMenu"][sWin].Button["B-0020"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0010"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0020"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0300"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0020"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0003"].getPointer());

	Core::gui["GameMenu"][sWin].Button["B-0002"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0001"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0002"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0030"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0002"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-3000"].getPointer());

	Core::gui["GameMenu"][sWin].Button["C-2000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-1000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-2000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0003"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-2000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0300"].getPointer());

	Core::gui["GameMenu"][sWin].Button["C-0200"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0100"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0200"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-3000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0200"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0030"].getPointer());

	Core::gui["GameMenu"][sWin].Button["C-0020"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0010"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0020"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0300"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0020"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0003"].getPointer());

	Core::gui["GameMenu"][sWin].Button["C-0002"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0001"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0002"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0030"].getPointer());

	y += 40;
	con_button.setWidth(75, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
	con_button.setPos(-225, y);	Core::gui["GameMenu"][sWin].Button.add("B-4000", false, con_button);
	con_button.setPos(-150, y);	Core::gui["GameMenu"][sWin].Button.add("B-0400", false, con_button);
	con_button.setPos( -75, y);	Core::gui["GameMenu"][sWin].Button.add("B-0040", false, con_button);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("B-0004", false, con_button);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("C-4000", false, con_button);
	con_button.setPos(  75, y);	Core::gui["GameMenu"][sWin].Button.add("C-0400", false, con_button);
	con_button.setPos( 150, y);	Core::gui["GameMenu"][sWin].Button.add("C-0040", false, con_button);
	con_button.setPos( 225, y);	Core::gui["GameMenu"][sWin].Button.add("C-0004", false, con_button);

	// Enable Pointers for B-3000 to C-0003
	Core::gui["GameMenu"][sWin].Button["B-3000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-2000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-3000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0400"].getPointer());

	Core::gui["GameMenu"][sWin].Button["B-0300"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0200"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0300"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-4000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0300"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0040"].getPointer());

	Core::gui["GameMenu"][sWin].Button["B-0030"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0020"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0030"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0400"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0030"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0004"].getPointer());

	Core::gui["GameMenu"][sWin].Button["B-0003"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0002"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0003"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0040"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0003"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-4000"].getPointer());

	Core::gui["GameMenu"][sWin].Button["C-3000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-2000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-3000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0004"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-3000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0400"].getPointer());

	Core::gui["GameMenu"][sWin].Button["C-0300"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0200"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0300"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-4000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0300"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0040"].getPointer());

	Core::gui["GameMenu"][sWin].Button["C-0030"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0020"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0030"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0400"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0030"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0004"].getPointer());

	Core::gui["GameMenu"][sWin].Button["C-0003"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0002"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0003"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0040"].getPointer());

	y += 40;
	con_button.setWidth(75, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
	con_button.setPos(-225, y);	Core::gui["GameMenu"][sWin].Button.add("B-5000", false, con_button);
	con_button.setPos(-150, y);	Core::gui["GameMenu"][sWin].Button.add("B-0500", false, con_button);
	con_button.setPos( -75, y);	Core::gui["GameMenu"][sWin].Button.add("B-0050", false, con_button);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("B-0005", false, con_button);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("C-5000", false, con_button);
	con_button.setPos(  75, y);	Core::gui["GameMenu"][sWin].Button.add("C-0500", false, con_button);
	con_button.setPos( 150, y);	Core::gui["GameMenu"][sWin].Button.add("C-0050", false, con_button);
	con_button.setPos( 225, y);	Core::gui["GameMenu"][sWin].Button.add("C-0005", false, con_button);

	// Enable Pointers for B-4000 to C-0004
	Core::gui["GameMenu"][sWin].Button["B-4000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-3000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-4000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0500"].getPointer());

	Core::gui["GameMenu"][sWin].Button["B-0400"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0300"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0400"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-5000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0400"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0050"].getPointer());

	Core::gui["GameMenu"][sWin].Button["B-0040"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0030"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0040"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0500"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0040"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0005"].getPointer());

	Core::gui["GameMenu"][sWin].Button["B-0004"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0003"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0004"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0050"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0004"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-5000"].getPointer());

	Core::gui["GameMenu"][sWin].Button["C-4000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-3000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-4000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0005"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-4000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0500"].getPointer());

	Core::gui["GameMenu"][sWin].Button["C-0400"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0300"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0400"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-5000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0400"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0050"].getPointer());

	Core::gui["GameMenu"][sWin].Button["C-0040"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0030"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0040"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0500"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0040"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0005"].getPointer());

	Core::gui["GameMenu"][sWin].Button["C-0004"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0003"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0004"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0050"].getPointer());

	y += 40;
	con_button.setWidth(75, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
	con_button.setPos(-225, y);	Core::gui["GameMenu"][sWin].Button.add("B-6000", false, con_button);
	con_button.setPos(-150, y);	Core::gui["GameMenu"][sWin].Button.add("B-0600", false, con_button);
	con_button.setPos( -75, y);	Core::gui["GameMenu"][sWin].Button.add("B-0060", false, con_button);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("B-0006", false, con_button);
	Core::gui["GameMenu"][sWin].Button["B-6000"].setEnableAPtr(Core::gui["GameMenu"][sWin].Button["B-5000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0600"].setEnableAPtr(Core::gui["GameMenu"][sWin].Button["B-0500"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0060"].setEnableAPtr(Core::gui["GameMenu"][sWin].Button["B-0050"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0006"].setEnableAPtr(Core::gui["GameMenu"][sWin].Button["B-0005"].getPointer());
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("C-6000", false, con_button);
	con_button.setPos(  75, y);	Core::gui["GameMenu"][sWin].Button.add("C-0600", false, con_button);
	con_button.setPos( 150, y);	Core::gui["GameMenu"][sWin].Button.add("C-0060", false, con_button);
	con_button.setPos( 225, y);	Core::gui["GameMenu"][sWin].Button.add("C-0006", false, con_button);
	Core::gui["GameMenu"][sWin].Button["C-6000"].setEnableAPtr(Core::gui["GameMenu"][sWin].Button["C-5000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0600"].setEnableAPtr(Core::gui["GameMenu"][sWin].Button["C-0500"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0060"].setEnableAPtr(Core::gui["GameMenu"][sWin].Button["C-0050"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0006"].setEnableAPtr(Core::gui["GameMenu"][sWin].Button["C-0005"].getPointer());

	// Enable Pointers for B-5000 to C-0005
	Core::gui["GameMenu"][sWin].Button["B-5000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-4000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-5000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0600"].getPointer());

	Core::gui["GameMenu"][sWin].Button["B-0500"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0400"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0500"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-6000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0500"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0060"].getPointer());

	Core::gui["GameMenu"][sWin].Button["B-0050"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0040"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0050"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0600"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0050"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0006"].getPointer());

	Core::gui["GameMenu"][sWin].Button["B-0005"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0004"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0005"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0060"].getPointer());
	Core::gui["GameMenu"][sWin].Button["B-0005"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-6000"].getPointer());

	Core::gui["GameMenu"][sWin].Button["C-5000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-4000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-5000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["B-0006"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-5000"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0600"].getPointer());

	Core::gui["GameMenu"][sWin].Button["C-0500"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0400"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0500"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-6000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0500"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0060"].getPointer());

	Core::gui["GameMenu"][sWin].Button["C-0050"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0040"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0050"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0600"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0050"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0006"].getPointer());

	Core::gui["GameMenu"][sWin].Button["C-0005"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0004"].getPointer());
	Core::gui["GameMenu"][sWin].Button["C-0005"].setEnableOPtr(Core::gui["GameMenu"][sWin].Button["C-0060"].getPointer());

	y += 40;
	con_button.setButtonType(Core::GUI::BUTTON_ONESHOT);
	con_button.setWidth(75, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
	con_button.setPos(-225, y);	Core::gui["GameMenu"][sWin].Button.add("Class 1", false, con_button);
	con_button.setPos(-150, y);	Core::gui["GameMenu"][sWin].Button.add("Class 2", false, con_button);
	con_button.setPos( -75, y);	Core::gui["GameMenu"][sWin].Button.add("Class 3", false, con_button);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("Class 4", false, con_button);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("Class 5", false, con_button);
	con_button.setPos(  75, y);	Core::gui["GameMenu"][sWin].Button.add("Class 6", false, con_button);
	con_button.setPos( 150, y);	Core::gui["GameMenu"][sWin].Button.add("Class 7", false, con_button);
	con_button.setPos( 225, y);	Core::gui["GameMenu"][sWin].Button.add("Class 8", false, con_button);

	// ========================
	//	WINDOW 14-1 : Class 1
	// ========================
	y = 20;
	sWin = "Window 14-1";
	con_button.setButtonType(Core::GUI::BUTTON_ONESHOT);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
	con_button.setWidth(600, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("BACK", false, con_button);
//		con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("B-0700", &Core::gameVars->debug.gui.bSkillButton, con_button);

	y += 40;
	con_button.setButtonType(Core::GUI::BUTTON_TOGGLE);
	con_button.setWidth(75, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
	con_button.setPos(-225, y);	Core::gui["GameMenu"][sWin].Button.add("D-1000", false, con_button);
	con_button.setPos(-150, y);	Core::gui["GameMenu"][sWin].Button.add("D-0100", false, con_button);
	con_button.setPos( -75, y);	Core::gui["GameMenu"][sWin].Button.add("D-0010", false, con_button);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("D-0001", false, con_button);
	Core::gui["GameMenu"][sWin].Button["D-1000"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-6000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0100"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-6000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0010"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-6000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0001"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-6000"].getPointer());
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("E-1000", false, con_button);
	con_button.setPos(  75, y);	Core::gui["GameMenu"][sWin].Button.add("E-0100", false, con_button);
	con_button.setPos( 150, y);	Core::gui["GameMenu"][sWin].Button.add("E-0010", false, con_button);
	con_button.setPos( 225, y);	Core::gui["GameMenu"][sWin].Button.add("E-0001", false, con_button);
	Core::gui["GameMenu"][sWin].Button["E-1000"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-6000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0100"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-6000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0010"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-6000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0001"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-6000"].getPointer());

	// ========================
	//	WINDOW 14-2 : Class 2
	// ========================
	y = 20;
	sWin = "Window 14-2";
	con_button.setButtonType(Core::GUI::BUTTON_ONESHOT);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
	con_button.setWidth(600, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("BACK", false, con_button);
//		con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("B-0700", &Core::gameVars->debug.gui.bSkillButton, con_button);

	y += 40;
	con_button.setButtonType(Core::GUI::BUTTON_TOGGLE);
	con_button.setWidth(75, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
	con_button.setPos(-225, y);	Core::gui["GameMenu"][sWin].Button.add("D-1000", false, con_button);
	con_button.setPos(-150, y);	Core::gui["GameMenu"][sWin].Button.add("D-0100", false, con_button);
	con_button.setPos( -75, y);	Core::gui["GameMenu"][sWin].Button.add("D-0010", false, con_button);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("D-0001", false, con_button);
	Core::gui["GameMenu"][sWin].Button["D-1000"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0600"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0100"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0600"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0010"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0600"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0001"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0600"].getPointer());
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("E-1000", false, con_button);
	con_button.setPos(  75, y);	Core::gui["GameMenu"][sWin].Button.add("E-0100", false, con_button);
	con_button.setPos( 150, y);	Core::gui["GameMenu"][sWin].Button.add("E-0010", false, con_button);
	con_button.setPos( 225, y);	Core::gui["GameMenu"][sWin].Button.add("E-0001", false, con_button);
	Core::gui["GameMenu"][sWin].Button["E-1000"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0600"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0100"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0600"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0010"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0600"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0001"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0600"].getPointer());

	// ========================
	//	WINDOW 14-3 : Class 3
	// ========================
	y = 20;
	sWin = "Window 14-3";
	con_button.setButtonType(Core::GUI::BUTTON_ONESHOT);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
	con_button.setWidth(600, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("BACK", false, con_button);
//		con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("B-0700", &Core::gameVars->debug.gui.bSkillButton, con_button);

	y += 40;
	con_button.setButtonType(Core::GUI::BUTTON_TOGGLE);
	con_button.setWidth(75, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
	con_button.setPos(-225, y);	Core::gui["GameMenu"][sWin].Button.add("D-1000", false, con_button);
	con_button.setPos(-150, y);	Core::gui["GameMenu"][sWin].Button.add("D-0100", false, con_button);
	con_button.setPos( -75, y);	Core::gui["GameMenu"][sWin].Button.add("D-0010", false, con_button);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("D-0001", false, con_button);
	Core::gui["GameMenu"][sWin].Button["D-1000"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0060"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0100"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0060"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0010"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0060"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0001"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0060"].getPointer());
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("E-1000", false, con_button);
	con_button.setPos(  75, y);	Core::gui["GameMenu"][sWin].Button.add("E-0100", false, con_button);
	con_button.setPos( 150, y);	Core::gui["GameMenu"][sWin].Button.add("E-0010", false, con_button);
	con_button.setPos( 225, y);	Core::gui["GameMenu"][sWin].Button.add("E-0001", false, con_button);
	Core::gui["GameMenu"][sWin].Button["E-1000"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0060"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0100"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0060"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0010"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0060"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0001"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0060"].getPointer());

	// ========================
	//	WINDOW 14-4 : Class 4
	// ========================
	y = 20;
	sWin = "Window 14-4";
	con_button.setButtonType(Core::GUI::BUTTON_ONESHOT);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
	con_button.setWidth(600, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("BACK", false, con_button);
//		con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("B-0700", &Core::gameVars->debug.gui.bSkillButton, con_button);

	y += 40;
	con_button.setButtonType(Core::GUI::BUTTON_TOGGLE);
	con_button.setWidth(75, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
	con_button.setPos(-225, y);	Core::gui["GameMenu"][sWin].Button.add("D-1000", false, con_button);
	con_button.setPos(-150, y);	Core::gui["GameMenu"][sWin].Button.add("D-0100", false, con_button);
	con_button.setPos( -75, y);	Core::gui["GameMenu"][sWin].Button.add("D-0010", false, con_button);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("D-0001", false, con_button);
	Core::gui["GameMenu"][sWin].Button["D-1000"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0006"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0100"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0006"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0010"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0006"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0001"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0006"].getPointer());
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("E-1000", false, con_button);
	con_button.setPos(  75, y);	Core::gui["GameMenu"][sWin].Button.add("E-0100", false, con_button);
	con_button.setPos( 150, y);	Core::gui["GameMenu"][sWin].Button.add("E-0010", false, con_button);
	con_button.setPos( 225, y);	Core::gui["GameMenu"][sWin].Button.add("E-0001", false, con_button);
	Core::gui["GameMenu"][sWin].Button["E-1000"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0006"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0100"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0006"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0010"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0006"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0001"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["B-0006"].getPointer());

	// ========================
	//	WINDOW 14-5 : Class 5
	// ========================
	y = 20;
	sWin = "Window 14-5";
	con_button.setButtonType(Core::GUI::BUTTON_ONESHOT);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
	con_button.setWidth(600, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("BACK", false, con_button);
//		con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("B-0700", &Core::gameVars->debug.gui.bSkillButton, con_button);

	y += 40;
	con_button.setButtonType(Core::GUI::BUTTON_TOGGLE);
	con_button.setWidth(75, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
	con_button.setPos(-225, y);	Core::gui["GameMenu"][sWin].Button.add("D-1000", false, con_button);
	con_button.setPos(-150, y);	Core::gui["GameMenu"][sWin].Button.add("D-0100", false, con_button);
	con_button.setPos( -75, y);	Core::gui["GameMenu"][sWin].Button.add("D-0010", false, con_button);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("D-0001", false, con_button);
	Core::gui["GameMenu"][sWin].Button["D-1000"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-6000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0100"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-6000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0010"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-6000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0001"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-6000"].getPointer());
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("E-1000", false, con_button);
	con_button.setPos(  75, y);	Core::gui["GameMenu"][sWin].Button.add("E-0100", false, con_button);
	con_button.setPos( 150, y);	Core::gui["GameMenu"][sWin].Button.add("E-0010", false, con_button);
	con_button.setPos( 225, y);	Core::gui["GameMenu"][sWin].Button.add("E-0001", false, con_button);
	Core::gui["GameMenu"][sWin].Button["E-1000"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-6000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0100"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-6000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0010"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-6000"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0001"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-6000"].getPointer());

	// ========================
	//	WINDOW 14-6 : Class 6
	// ========================
	y = 20;
	sWin = "Window 14-6";
	con_button.setButtonType(Core::GUI::BUTTON_ONESHOT);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
	con_button.setWidth(600, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("BACK", false, con_button);
//		con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("B-0700", &Core::gameVars->debug.gui.bSkillButton, con_button);

	y += 40;
	con_button.setButtonType(Core::GUI::BUTTON_TOGGLE);
	con_button.setWidth(75, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
	con_button.setPos(-225, y);	Core::gui["GameMenu"][sWin].Button.add("D-1000", false, con_button);
	con_button.setPos(-150, y);	Core::gui["GameMenu"][sWin].Button.add("D-0100", false, con_button);
	con_button.setPos( -75, y);	Core::gui["GameMenu"][sWin].Button.add("D-0010", false, con_button);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("D-0001", false, con_button);
	Core::gui["GameMenu"][sWin].Button["D-1000"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0600"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0100"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0600"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0010"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0600"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0001"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0600"].getPointer());
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("E-1000", false, con_button);
	con_button.setPos(  75, y);	Core::gui["GameMenu"][sWin].Button.add("E-0100", false, con_button);
	con_button.setPos( 150, y);	Core::gui["GameMenu"][sWin].Button.add("E-0010", false, con_button);
	con_button.setPos( 225, y);	Core::gui["GameMenu"][sWin].Button.add("E-0001", false, con_button);
	Core::gui["GameMenu"][sWin].Button["E-1000"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0600"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0100"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0600"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0010"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0600"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0001"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0600"].getPointer());

	// ========================
	//	WINDOW 14-7 : Class 7
	// ========================
	y = 20;
	sWin = "Window 14-7";
	con_button.setButtonType(Core::GUI::BUTTON_ONESHOT);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
	con_button.setWidth(600, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("BACK", false, con_button);
//		con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("B-0700", &Core::gameVars->debug.gui.bSkillButton, con_button);

	y += 40;
	con_button.setButtonType(Core::GUI::BUTTON_TOGGLE);
	con_button.setWidth(75, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
	con_button.setPos(-225, y);	Core::gui["GameMenu"][sWin].Button.add("D-1000", false, con_button);
	con_button.setPos(-150, y);	Core::gui["GameMenu"][sWin].Button.add("D-0100", false, con_button);
	con_button.setPos( -75, y);	Core::gui["GameMenu"][sWin].Button.add("D-0010", false, con_button);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("D-0001", false, con_button);
	Core::gui["GameMenu"][sWin].Button["D-1000"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0060"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0100"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0060"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0010"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0060"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0001"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0060"].getPointer());
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("E-1000", false, con_button);
	con_button.setPos(  75, y);	Core::gui["GameMenu"][sWin].Button.add("E-0100", false, con_button);
	con_button.setPos( 150, y);	Core::gui["GameMenu"][sWin].Button.add("E-0010", false, con_button);
	con_button.setPos( 225, y);	Core::gui["GameMenu"][sWin].Button.add("E-0001", false, con_button);
	Core::gui["GameMenu"][sWin].Button["E-1000"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0060"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0100"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0060"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0010"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0060"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0001"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0060"].getPointer());

	// ========================
	//	WINDOW 14-8 : Class 8
	// ========================
	y = 20;
	sWin = "Window 14-8";
	con_button.setButtonType(Core::GUI::BUTTON_ONESHOT);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
	con_button.setWidth(600, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("BACK", false, con_button);
//		con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("B-0700", &Core::gameVars->debug.gui.bSkillButton, con_button);

	y += 40;
	con_button.setButtonType(Core::GUI::BUTTON_TOGGLE);
	con_button.setWidth(75, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setHeight(40, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_RIGHT);
	con_button.setPos(-225, y);	Core::gui["GameMenu"][sWin].Button.add("D-1000", false, con_button);
	con_button.setPos(-150, y);	Core::gui["GameMenu"][sWin].Button.add("D-0100", false, con_button);
	con_button.setPos( -75, y);	Core::gui["GameMenu"][sWin].Button.add("D-0010", false, con_button);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("D-0001", false, con_button);
	Core::gui["GameMenu"][sWin].Button["D-1000"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0006"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0100"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0006"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0010"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0006"].getPointer());
	Core::gui["GameMenu"][sWin].Button["D-0001"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0006"].getPointer());
	con_button.setAnchor(Core::GUI::CONSTRAIN_BOTTOM_LEFT);
	con_button.setPos(   0, y);	Core::gui["GameMenu"][sWin].Button.add("E-1000", false, con_button);
	con_button.setPos(  75, y);	Core::gui["GameMenu"][sWin].Button.add("E-0100", false, con_button);
	con_button.setPos( 150, y);	Core::gui["GameMenu"][sWin].Button.add("E-0010", false, con_button);
	con_button.setPos( 225, y);	Core::gui["GameMenu"][sWin].Button.add("E-0001", false, con_button);
	Core::gui["GameMenu"][sWin].Button["E-1000"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0006"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0100"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0006"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0010"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0006"].getPointer());
	Core::gui["GameMenu"][sWin].Button["E-0001"].setEnableAPtr(Core::gui["GameMenu"]["Window 14-0"].Button["C-0006"].getPointer());
}


#endif /* GAME_RUNADMIN_SKILLTREE_H_ */
