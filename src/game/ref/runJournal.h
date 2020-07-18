/*
 * runMenu.h
 *
 *  Created on: Sep 28, 2010
 *      Author: bcthund
 */

#ifndef RUNJOURNAL_H_
#define RUNJOURNAL_H_

class RunJournal {
	private:
		enum MENUSTATES { TAB1, TAB2, TAB3, TAB4, TAB5, TAB6, TAB7, TAB8, TAB9, TAB10, TAB11, TAB12 };
		int menuState;
		int iInvStart;		// Inventory scrolling, should be reset when pressing tabs
		Keyboard keyboard;
		bool bShowMouse;			// Draw the custom journal cursor, default true
		void changeTab(MENUSTATES m);
		bool bOpen;					// Was the journal just opened? (Reset when Journal closed)
		void close();

	protected:
		void toggle(bool &myBool);
		void getInput();
		void processInput();
		void update();
		void draw();

	public:
		/*
		struct MenuState {
			//Primary Modes
			bool tab1,
				 tab2,
				 tab3,
				 tab4,
				 tab5,
				 tab6,
				 tab7,
				 tab8,
				 tab9,
				 tab10,
				 tab11,
				 tab12;

			//Secondary Modes
			bool show_choice;
		} menuState;
		*/
		RunJournal();
		bool init();
		bool load();
		void run();
} Journal;

//RunJournal * Journal = new(RunJournal);

RunJournal::RunJournal() {
	bShowMouse = true;
	menuState = TAB2;
	iInvStart = 0;
	keyboard.calc();
	bOpen = false;
	/*
	menuState.tab1		= true;
	menuState.tab2		= false;
	menuState.tab3		= false;
	menuState.tab4		= false;
	menuState.tab5		= false;
	menuState.tab6		= false;
	menuState.tab7		= false;
	menuState.tab8		= false;
	menuState.tab9		= false;
	menuState.tab10		= false;
	menuState.tab11		= false;
	menuState.tab12		= false;
	*/
}

bool RunJournal::init() {
	return true;
}

bool RunJournal::load() {
	return true;
}

void RunJournal::close() {
	gameSys.audioSys.playSound(gameSys.audioSys.SOUNDS.JOURNAL.CLOSE);
	gameVars->state.book=false;
	bOpen = false;
	//Menu.reset();
	SDL_WarpMouse(gameVars->screen.halfW, gameVars->screen.halfH);
}

inline void RunJournal::changeTab(MENUSTATES m) {
	cout << menuState << " ? " << m << endl;

				if(menuState<m) gameSys.audioSys.playSound(gameSys.audioSys.SOUNDS.JOURNAL.PREV);
	else	if(menuState>m)	gameSys.audioSys.playSound(gameSys.audioSys.SOUNDS.JOURNAL.NEXT);

	menuState=m;
	gameVars->player.active->inventory.iSelected=-1;
	iInvStart=0;
}

void RunJournal::run() {
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glClear( gameVars->screen.clear );

	if(!bOpen) {
		gameSys.audioSys.playSound(gameSys.audioSys.SOUNDS.JOURNAL.OPEN);
		bOpen = true;
	}

	//Set default colors and presets
	Vector4f vFont, vVal, vNI, vTitle;

		//CopyVector4f(gameVars->color.tan ,vFont);
	vFont = gameVars->color.tan;
		//CopyVector4f(gameVars->color.grey ,vVal);
		vVal = gameVars->color.grey;
		//CopyVector4f(gameVars->color.red ,vNI);
		vNI = gameVars->color.red;
		//CopyVector4f(gameVars->color.yellow ,vTitle);
		vTitle = gameVars->color.yellow;
	Vector4f tint        = {0.54, 0.45, 0.25, 1.0};
		//CopyVector4f(gameVars->color.brown ,tint);
		tint = gameVars->color.brown;
	Vector4f selected    = {0.54, 0.45, 0.25, 1.0};
		//CopyVector4f(gameVars->color.brown ,selected);
		selected = gameVars->color.brown;
	Vector4f deselected  = {0.74, 0.65, 0.45, 1.0};
		//CopyVector4f(gameVars->color.tan ,deselected);
		deselected = gameVars->color.tan;

	// Inventory hilighting
	Vector4f	inv_normal,
						inv_hover_normal	= { 1.0f, 0.875f, 0.70f, 1.0},
						inv_select			= { 0.875f, 1.0f, 0.70f, 1.0},
						inv_hover_select	= { 0.87f, 1.0f, 0.87f, 1.0},
						inv_text,
						inv_des,
						holster_text,
						holster_back		= { 0.9f, 0.775f, 0.60f, 1.0};

		//CopyVector4f(gameVars->color.transparent, inv_normal);
		inv_normal = gameVars->color.transparent;
		//CopyVector4f(gameVars->color.tan, holster_text);
		holster_text = gameVars->color.tan;
		////CopyVector4f(gameVars->color.grey, inv_hover_normal);
		////CopyVector4f(gameVars->color.yellow, inv_select);
		////CopyVector4f(gameVars->color.orange, inv_hover_select);
		//CopyVector4f(gameVars->color.white, inv_text);
		inv_text = gameVars->color.white;
		//CopyVector4f(gameVars->color.tan, inv_des);
		inv_des = gameVars->color.tan;

	Vector4f tab1_color,
			 tab2_color,
			 tab3_color,
			 tab4_color,
			 tab5_color,
			 tab6_color,
			 tab7_color,
			 tab8_color,
			 tab9_color,
			 tab10_color,
			 tab11_color,
			 tab12_color;

	//CopyVector4f(deselected, tab1_color);
	//CopyVector4f(deselected, tab2_color);
	//CopyVector4f(deselected, tab3_color);
	//CopyVector4f(deselected, tab4_color);
	//CopyVector4f(deselected, tab5_color);
	//CopyVector4f(deselected, tab6_color);
	//CopyVector4f(deselected, tab7_color);
	//CopyVector4f(deselected, tab8_color);
	//CopyVector4f(deselected, tab9_color);
	//CopyVector4f(deselected, tab10_color);
	//CopyVector4f(deselected, tab11_color);
	//CopyVector4f(deselected, tab12_color);

	tab1_color = deselected;
	tab2_color = deselected;
	tab3_color = deselected;
	tab4_color = deselected;
	tab5_color = deselected;
	tab6_color = deselected;
	tab7_color = deselected;
	tab8_color = deselected;
	tab9_color = deselected;
	tab10_color = deselected;
	tab11_color = deselected;
	tab12_color = deselected;

	/*
	 * Draw the world as it last was
	 *
	 * This would be nice to do if possible, otherwise
	 * we need to find a way to capture the last screen
	 * before the menu was opened.
	 *
	 * We could also continue to ignore clearing the screen
	 *  but that isnt as graceful and could lead to problems
	 *  with other parts.
	 *
	 * To get this to work we need to make all of the matrix
	 *  transformations that we would normally do, draw the
	 *  scenery and then draw our journal as we normally would.
	 */
	//world.run.Draw(GLS_DIR_PHONG);
	world.Update(false);		//Calls for a screen draw of the world, includes transformations

	/*
	 * Set the active colors
	 * Such as the currently selected tab
	 */

	switch (menuState) {
		case TAB1:
			//CopyVector4f(selected, tab1_color);
			tab1_color = selected;
			break;
		case TAB2:
			//CopyVector4f(selected, tab2_color);
			tab2_color = selected;
			break;
		case TAB3:
			//CopyVector4f(selected, tab3_color);
			tab3_color = selected;
			break;
		case TAB4:
			//CopyVector4f(selected, tab4_color);
			tab4_color = selected;
			break;
		case TAB5:
			//CopyVector4f(selected, tab5_color);
			tab5_color = selected;
			break;
		case TAB6:
			//CopyVector4f(selected, tab6_color);
			tab6_color = selected;
			break;
		case TAB7:
			//CopyVector4f(selected, tab7_color);
			tab7_color = selected;
			break;
		case TAB8:
			//CopyVector4f(selected, tab8_color);
			tab8_color = selected;
			break;
		case TAB9:
			//CopyVector4f(selected, tab9_color);
			tab9_color = selected;
			break;
		case TAB10:
			//CopyVector4f(selected, tab10_color);
			tab10_color = selected;
			break;
		case TAB11:
			//CopyVector4f(selected, tab11_color);
			tab11_color = selected;
			break;
		case TAB12:
			//CopyVector4f(selected, tab12_color);
			tab12_color = selected;
			break;
	}

	/*
	 * Draw the base journal
	 * First lets draw the tabs on the left
	 * Then draw the tabs on the right
	 * last draw the actual journal space, ready for the tab data
	 */
	int iTabX = 6,	//Tab starting X
		iTabY = 2,	//Tab starting Y
		iTabW = (gameVars->font.vMax[0])/10,	//Tab Width
		iTabH = 4,	//Tab Height
		iTabA = 8,	//Width Offset
		iTextX = 5,	//Text starting X
		iTextY = 2;	//Text starting Y

	// LEFT TABS
	if (gameSys.checkIcon2(iTabX, 		iTabY,  7, 4, 1, "journal.png", true, true)&MOUSE_LEFT)		{ changeTab(TAB1);	}	gameSys.drawText(iTabX+1, iTabY+1, "Stats", gameVars->color.white);
	if (gameSys.checkIcon2(iTabX+=8,	iTabY,  6, 4, 1, "journal.png", true, true)&MOUSE_LEFT)		{ changeTab(TAB2);	}	gameSys.drawText(iTabX+1, iTabY+1, "Team", gameVars->color.white);
	if (gameSys.checkIcon2(iTabX+=7,	iTabY,  7, 4, 1, "journal.png", true, true)&MOUSE_LEFT)		{ changeTab(TAB3);	}	gameSys.drawText(iTabX+1, iTabY+1, "Stuff", gameVars->color.white);
	if (gameSys.checkIcon2(iTabX+=8,	iTabY,  5, 4, 1, "journal.png", true, true)&MOUSE_LEFT)		{ changeTab(TAB4);	}	gameSys.drawText(iTabX+1, iTabY+1, "Log", gameVars->color.white);
	if (gameSys.checkIcon2(iTabX+=6,	iTabY,  7, 4, 1, "journal.png", true, true)&MOUSE_LEFT)		{ changeTab(TAB5);	}	gameSys.drawText(iTabX+1, iTabY+1, "Terra", gameVars->color.white);
	if (gameSys.checkIcon2(iTabX+=8,	iTabY,  7, 4, 1, "journal.png", true, true)&MOUSE_LEFT)		{ changeTab(TAB6);	}	gameSys.drawText(iTabX+1, iTabY+1, "Notes", gameVars->color.white);

	iTabX=(gameVars->font.vMax[0]/2)+4;
	iTextX = iTabX+1;
	// RIGHT TABS
	if (gameSys.checkIcon2(iTabX,			iTabY,  6, 4, 1, "journal.png", true, true)&MOUSE_LEFT)		{ changeTab(TAB7);	}	gameSys.drawText(iTabX+1, iTabY+1, "Gear", gameVars->color.white);
	if (gameSys.checkIcon2(iTabX+=7,	iTabY,  10, 4, 1, "journal.png", true, true)&MOUSE_LEFT)	{ changeTab(TAB8);	}	gameSys.drawText(iTabX+1, iTabY+1, "Clothing", gameVars->color.white);
	if (gameSys.checkIcon2(iTabX+=11,	iTabY,  9, 4, 1, "journal.png", true, true)&MOUSE_LEFT)		{ changeTab(TAB9);	}	gameSys.drawText(iTabX+1, iTabY+1, "Quilted", gameVars->color.white);
	if (gameSys.checkIcon2(iTabX+=10,	iTabY,  8, 4, 1, "journal.png", true, true)&MOUSE_LEFT)		{ changeTab(TAB10);	}	gameSys.drawText(iTabX+1, iTabY+1, "Maille", gameVars->color.white);
	if (gameSys.checkIcon2(iTabX+=9,	iTabY,  7, 4, 1, "journal.png", true, true)&MOUSE_LEFT)		{ changeTab(TAB11);	}	gameSys.drawText(iTabX+1, iTabY+1, "Plate", gameVars->color.white);
	if (gameSys.checkIcon2(iTabX+=8,	iTabY,  7, 4, 1, "journal.png", true, true)&MOUSE_LEFT)		{ changeTab(TAB12);	}	gameSys.drawText(iTabX+1, iTabY+1, "Limbs", gameVars->color.white);

	/*
	 * MAIN JOURNAL, All pages layout
	 */

	/*
	gameSys.winSys.draw			(0,  iTabH-1, gameVars->font.vMax[0]+1, gameVars->font.vMax[1]-5, tint);
	// Vertical Divider
	gameSys.winSys.drawVLine	((gameVars->font.vMax[0]/2),  iTabH, gameVars->font.vMax[1]-7, tint);
	gameSys.winSys.drawSingle	((gameVars->font.vMax[0]/2),  iTabH-1, 1,  1, 2, tint);
	gameSys.winSys.drawSingle	((gameVars->font.vMax[0]/2),  gameVars->font.vMax[1]-3, 1,  1, 7, tint);
	//Page 1: Horizontal divider
	gameSys.winSys.drawHLine	(1,  10, (gameVars->font.vMax[0]/2)-1, tint);
	gameSys.winSys.drawSingle	(0, 10, 1,  1, 10, tint);
	gameSys.winSys.drawSingle	((gameVars->font.vMax[0]/2), 10, 1,  1, 11, tint);
	*/

	gameSys.drawSprite(0,4,gameVars->screen.w-(gameVars->font.vSize[1]),gameVars->screen.h-(12*gameVars->font.vSize[2]),"journal.png", false, true);

	/*
	 * Draw the appropriate tab data
	 */

	int cx=6,	// Starting X
		cy=iTabH+2,	// Starting Y
		os1=5,	// Offset constant
		os2=10,	// Offset constant
		os3=15,	// Offset constant
		os4=20,	// Offset constant
		os5=25,	// Offset constant
		hX,
		hY,
		hW;

	/*
	 * All Pages
	 */
	//gameSys.winSys.draw(cx, cy, 8, 6, tint);
	//gameSys.textSys.draw(cx+2, cy+1, "ICON", vTitle);	//Icon Placeholder
	gameSys.drawIcon(cx, cy, 64, 64, gameVars->player.active->init.face, "faces.png", false, true, gameVars->color.journal.inventory_icon);

	cx=15;
	gameSys.drawText(cx,   cy, "Name:", vFont);			gameSys.drawText(cx+os3, cy, gameVars->player.active->init.name, vVal);
	gameSys.drawText(cx, ++cy, "Role:", vFont);			gameSys.drawText(cx+os3, cy, gameVars->player.active->init.sRole, vVal);
	gameSys.drawText(cx, ++cy, "Race:", vFont);			gameSys.drawText(cx+os3, cy, gameVars->player.active->init.sRace, vVal);
	gameSys.drawText(cx, ++cy, "Profession:", vFont);	gameSys.drawText(cx+os3, cy, gameVars->player.active->init.sProfession, vVal);
	gameSys.drawText(cx, ++cy, "Level:", vFont);		gameSys.textSys.draw(cx+os3, cy, &gameVars->player.active->mod.level, vVal);
	gameSys.drawText(cx, ++cy, "Stature:", vFont);		gameSys.drawVariable(cx+os3, cy, gameVars->player.active->init.h, vVal, false);
	gameSys.drawIcon(cx+34, cy-4, 64, 64, 2, "journal.png", true, true, gameVars->color.journal.inventory_icon);		// SKILL WHEEL
	gameSys.winSys.drawHLine(cx-10, cy+1, 48, gameVars->color.black, GAME::SYSTEM.WINSYS.DRAWMODE.BORDER_ONLY);

	// Prepare offsets for tab data
	cx=6;
	cy=15;

	/*
	 * Predefined Routines
	 */
	//### Left Page Start
	//cx=3;
	//cy=11;

	//### Right Page Start
	//cx=(gameVars->font.vMax[0]/2)+2;
	//cy=5;

	//### Horizontal Divider
	//int hX = (gameVars->font.vMax[0]/2),
	//	hY = 30,
	//	hW = (gameVars->font.vMax[0]/2);
	//gameSys.winSys.drawHLine	(hW+1,  hY, hW-1, tint);
	//gameSys.winSys.drawSingle	(hX, hY, 1,  1, 10, tint);
	//gameSys.winSys.drawSingle	(hX, hY, 1,  1, 11, tint);

	//### Icon Placeholder
	//gameSys.winSys.draw(cx, cy, 8, 5, tint);	gameSys.textSys.draw(cx+2, cy+2, "ICON", vTitle);	//Icon Placeholder

	int uiArmorBlade	= 0,
		uiArmorBlunt	= 0,
		uiArmorAxe		= 0,
		uiArmorSpear	= 0,
		uiArmorArrow	= 0,
		uiArmorClaw		= 0,
		uiArmorJaw		= 0,
		uiArmorHand		= 0;

	bool  bTemp = true;
	int   iTemp = 35565;
	float fTemp = 2.45;

	switch (menuState) {
		case TAB1:
			/*
			 * PAGE 1: BASE
			 */

			gameSys.drawText(cx,   cy, "Interaction", vTitle);
			gameSys.drawText(cx, ++cy, "Lift   [   ]", vFont);		gameSys.textSys.draw(cx+8, cy, &gameVars->player.active->load.lift, vVal);
			gameSys.drawText(cx, ++cy, "Raise  [   ]", vFont);		gameSys.textSys.draw(cx+8, cy, &gameVars->player.active->load.raise, vVal);
			gameSys.drawText(cx, ++cy, "Push   [   ]", vFont);		gameSys.textSys.draw(cx+8, cy, &gameVars->player.active->load.push, vVal);

			cx=21;
			cy=13;
			gameSys.drawText(cx,   cy, "Torso Resistances (w/o Bonus)", vTitle);


// This doesn't really work as the armor is too complex to list this information
//
//			gameVars->armor[gameVars->player.active->inventory.equipped.maille.iTorso]
//
//			uiArmorBlade	=	gameVars->armor[gameVars->player.active->items.armor[0].torso].blade +
//											gameVars->armor[gameVars->player.active->items.armor[1].torso].blade +
//											gameVars->armor[gameVars->player.active->items.armor[2].torso].blade +
//											gameVars->armor[gameVars->player.active->items.armor[3].torso].blade +
//											gameVars->armor[gameVars->player.active->items.armor[4].torso].blade;
//
//			uiArmorBlunt	=	gameVars->armor[gameVars->player.active->items.armor[0].torso].blunt +
//											gameVars->armor[gameVars->player.active->items.armor[1].torso].blunt +
//											gameVars->armor[gameVars->player.active->items.armor[2].torso].blunt +
//											gameVars->armor[gameVars->player.active->items.armor[3].torso].blunt +
//											gameVars->armor[gameVars->player.active->items.armor[4].torso].blunt;
//
//			uiArmorAxe		=	gameVars->armor[gameVars->player.active->items.armor[0].torso].axe +
//											gameVars->armor[gameVars->player.active->items.armor[1].torso].axe +
//											gameVars->armor[gameVars->player.active->items.armor[2].torso].axe +
//											gameVars->armor[gameVars->player.active->items.armor[3].torso].axe +
//											gameVars->armor[gameVars->player.active->items.armor[4].torso].axe;
//
//			uiArmorSpear	=	gameVars->armor[gameVars->player.active->items.armor[0].torso].spear +
//											gameVars->armor[gameVars->player.active->items.armor[1].torso].spear +
//											gameVars->armor[gameVars->player.active->items.armor[2].torso].spear +
//											gameVars->armor[gameVars->player.active->items.armor[3].torso].spear +
//											gameVars->armor[gameVars->player.active->items.armor[4].torso].spear;
//
//			uiArmorArrow	=	gameVars->armor[gameVars->player.active->items.armor[0].torso].arrow +
//											gameVars->armor[gameVars->player.active->items.armor[1].torso].arrow +
//											gameVars->armor[gameVars->player.active->items.armor[2].torso].arrow +
//											gameVars->armor[gameVars->player.active->items.armor[3].torso].arrow +
//											gameVars->armor[gameVars->player.active->items.armor[4].torso].arrow;
//
//			uiArmorClaw		=	gameVars->armor[gameVars->player.active->items.armor[0].torso].claw +
//											gameVars->armor[gameVars->player.active->items.armor[1].torso].claw +
//											gameVars->armor[gameVars->player.active->items.armor[2].torso].claw +
//											gameVars->armor[gameVars->player.active->items.armor[3].torso].claw +
//											gameVars->armor[gameVars->player.active->items.armor[4].torso].claw;
//
//			uiArmorJaw		=	gameVars->armor[gameVars->player.active->items.armor[0].torso].jaw +
//											gameVars->armor[gameVars->player.active->items.armor[1].torso].jaw +
//											gameVars->armor[gameVars->player.active->items.armor[2].torso].jaw +
//											gameVars->armor[gameVars->player.active->items.armor[3].torso].jaw +
//											gameVars->armor[gameVars->player.active->items.armor[4].torso].jaw;
//
//			uiArmorHand		=	gameVars->armor[gameVars->player.active->items.armor[0].torso].hand +
//											gameVars->armor[gameVars->player.active->items.armor[1].torso].hand +
//											gameVars->armor[gameVars->player.active->items.armor[2].torso].hand +
//											gameVars->armor[gameVars->player.active->items.armor[3].torso].hand +
//											gameVars->armor[gameVars->player.active->items.armor[4].torso].hand;


	//		gameSys.textSys.draw(cx, ++cy, "Blade  [   ]", vFont);		gameSys.textSys.draw(cx+8, cy, &gameVars->armor[gameVars->player.active->items.armor.equipped].blade, vVal);
	//		gameSys.textSys.draw(cx, ++cy, "Blunt  [   ]", vFont);		gameSys.textSys.draw(cx+8, cy, &gameVars->armor[gameVars->player.active->items.armor.equipped].blunt, vVal);
	//		gameSys.textSys.draw(cx, ++cy, "Axe    [   ]", vFont);		gameSys.textSys.draw(cx+8, cy, &gameVars->armor[gameVars->player.active->items.armor.equipped].axe, vVal);
	//		gameSys.textSys.draw(cx, ++cy, "Spear  [   ]", vFont);		gameSys.textSys.draw(cx+8, cy, &gameVars->armor[gameVars->player.active->items.armor.equipped].spear, vVal);
	//		gameSys.textSys.draw(cx, ++cy, "Arrow  [   ]", vFont);		gameSys.textSys.draw(cx+8, cy, &gameVars->armor[gameVars->player.active->items.armor.equipped].arrow, vVal);

			gameSys.drawText(cx, ++cy, "Blade  [   ]", vFont);		gameSys.textSys.draw(cx+8, cy, &uiArmorBlade, vVal);
			gameSys.drawText(cx, ++cy, "Blunt  [   ]", vFont);		gameSys.textSys.draw(cx+8, cy, &uiArmorBlunt, vVal);
			gameSys.drawText(cx, ++cy, "Axe    [   ]", vFont);		gameSys.textSys.draw(cx+8, cy, &uiArmorAxe, vVal);
			gameSys.drawText(cx, ++cy, "Spear  [   ]", vFont);		gameSys.textSys.draw(cx+8, cy, &uiArmorSpear, vVal);
			gameSys.drawText(cx, ++cy, "Arrow  [   ]", vFont);		gameSys.textSys.draw(cx+8, cy, &uiArmorArrow, vVal);
			gameSys.drawText(cx, ++cy, "Claw   [   ]", vFont);		gameSys.textSys.draw(cx+8, cy, &uiArmorClaw, vVal);
			gameSys.drawText(cx, ++cy, "Jaw    [   ]", vFont);		gameSys.textSys.draw(cx+8, cy, &uiArmorJaw, vVal);
			gameSys.drawText(cx, ++cy, "Hand   [   ]", vFont);		gameSys.textSys.draw(cx+8, cy, &uiArmorHand, vVal);

			cx=36;
			cy=13;
			gameSys.drawText(cx,   cy, "Weapon", vTitle);
			gameSys.drawText(cx, ++cy, "Chop   [   ]", vFont);		gameSys.textSys.draw(cx+8,   cy, &gameVars->weapon[gameVars->player.active->inventory.equipped.equipment.iRight_Hand].chop, vVal);
			gameSys.drawText(cx, ++cy, "Swing  [   ]", vFont);		gameSys.textSys.draw(cx+8,   cy, &gameVars->weapon[gameVars->player.active->inventory.equipped.equipment.iRight_Hand].swing, vVal);
			gameSys.drawText(cx, ++cy, "Thrust [   ]", vFont);		gameSys.textSys.draw(cx+8,   cy, &gameVars->weapon[gameVars->player.active->inventory.equipped.equipment.iRight_Hand].thrust, vVal);

			/*
			 * PAGE 1: STATS
			 */
			cx=6;
			cy=23;
			gameSys.drawText(cx, cy,   "Stats", vTitle);
			gameSys.drawText(cx, ++cy, "Specialization:", vFont);		gameSys.drawText(cx+os3, cy, "Not Implemented", vNI);
			gameSys.drawText(cx, ++cy, "Aura      [   ]", vFont);		gameSys.textSys.draw(cx+11,   cy, &gameVars->player.active->stats.aura, vVal);
			gameSys.drawText(cx, ++cy, "Speed     [   ]", vFont);		gameSys.textSys.draw(cx+11,   cy, &gameVars->player.active->stats.speed, vVal);
			gameSys.drawText(cx, ++cy, "Endurance [   ]", vFont);		gameSys.textSys.draw(cx+11,   cy, &gameVars->player.active->stats.endurance, vVal);
			gameSys.drawText(cx, ++cy, "Mind      [   ]", vFont);		gameSys.textSys.draw(cx+11,   cy, &gameVars->player.active->stats.mind, vVal);

			//gameVars->player.active->
			//gameVars->player.active->

			/*
			 * PAGE 1: ATTRIBUTES
			 */
			cx=6;
			cy=31;
			gameSys.drawText(cx, cy,   "Attributes", vTitle);
			gameSys.drawText(cx, ++cy, "Strength", vFont);
			gameSys.drawText(cx, ++cy, "Finesse", vFont);
			gameSys.drawText(cx, ++cy, "Mobility", vFont);
			gameSys.drawText(cx, ++cy, "Fatigue", vFont);
			gameSys.drawText(cx, ++cy, "Vicissitude", vFont);

			cx=23;
			cy=32;
			gameSys.drawText(cx, cy,   "Base", vFont);
			gameSys.drawText(cx, ++cy, "[   ]", vFont);		gameSys.textSys.draw(cx+1,   cy, &gameVars->player.active->attributes.str.max, vVal);
			gameSys.drawText(cx, ++cy, "[   ]", vFont);		gameSys.textSys.draw(cx+1,   cy, &gameVars->player.active->attributes.fin.max, vVal);
			gameSys.drawText(cx, ++cy, "[   ]", vFont);		gameSys.textSys.draw(cx+1,   cy, &gameVars->player.active->attributes.mob.max, vVal);
			gameSys.drawText(cx, ++cy, "[   ]", vFont);		gameSys.textSys.draw(cx+1,   cy, &gameVars->player.active->attributes.fat.max, vVal);
			gameSys.drawText(cx, ++cy, "[   ]", vFont);		gameSys.textSys.draw(cx+1,   cy, &gameVars->player.active->attributes.vic.max, vVal);

			cx=30;
			cy=32;
			gameSys.drawText(cx, cy,   "Current", vFont);
			gameSys.drawText(cx, ++cy, " [   ]", vFont);	gameSys.textSys.draw(cx+2,   cy, &gameVars->player.active->attributes.str.strength, vVal);
			gameSys.drawText(cx, ++cy, " [   ]", vFont);	gameSys.textSys.draw(cx+2,   cy, &gameVars->player.active->attributes.fin.finesse, vVal);
			gameSys.drawText(cx, ++cy, " [   ]", vFont);	gameSys.textSys.draw(cx+2,   cy, &gameVars->player.active->attributes.mob.mobility, vVal);
			gameSys.drawText(cx, ++cy, " [   ]", vFont);	gameSys.textSys.draw(cx+2,   cy, &gameVars->player.active->attributes.fat.fatigue, vVal);
			gameSys.drawText(cx, ++cy, " [   ]", vFont);	gameSys.textSys.draw(cx+2,   cy, &gameVars->player.active->attributes.vic.vicissitude, vVal);

			cx=40;
			cy=32;
			gameSys.drawText(cx, cy,   "Limbo", vFont);
			gameSys.drawText(cx, ++cy, "[   ]", vFont);		gameSys.textSys.draw(cx+1,   cy, &gameVars->player.active->attributes.str.limbo, vVal);
			gameSys.drawText(cx, ++cy, "[   ]", vFont);		gameSys.textSys.draw(cx+1,   cy, &gameVars->player.active->attributes.fin.limbo, vVal);
			gameSys.drawText(cx, ++cy, "[   ]", vFont);		gameSys.textSys.draw(cx+1,   cy, &gameVars->player.active->attributes.mob.limbo, vVal);
			gameSys.drawText(cx, ++cy, "[   ]", vFont);		gameSys.textSys.draw(cx+1,   cy, &gameVars->player.active->attributes.fat.limbo, vVal);
			gameSys.drawText(cx, ++cy, "[   ]", vFont);		gameSys.textSys.draw(cx+1,   cy, &gameVars->player.active->attributes.vic.limbo, vVal);

			/*
			 * PAGE 2: DERIVED ATTRIBUTES
			 */
			cx=(gameVars->font.vMax[0]/2)+4;
			cy=7;
			gameSys.drawText(cx, cy,   "Derived Attributes", vTitle);
			gameSys.drawText(cx+os3, ++cy, "Base   Current", vFont);
			gameSys.drawText(cx, ++cy, "Hit Points     [   ]   [   ]", vFont);		gameSys.drawText(cx+16, cy, "n/i", vNI);		gameSys.textSys.draw(cx+24, cy, &gameVars->player.active->mod.hit_points, vVal);
			gameSys.drawText(cx, ++cy, "Reflex         [   ]   [   ]", vFont);		gameSys.drawText(cx+16, cy, "n/i", vNI);		gameSys.textSys.draw(cx+24, cy, &gameVars->player.active->combat_check.reflex, vVal);
			gameSys.drawText(cx, ++cy, "Fortitude      [   ]   [   ]", vFont);		gameSys.drawText(cx+16, cy, "n/i", vNI);		gameSys.textSys.draw(cx+24, cy, &gameVars->player.active->combat_check.fortitude, vVal);
			gameSys.drawText(cx, ++cy, "Initiative     [   ]   [   ]", vFont);		gameSys.drawText(cx+16, cy, "n/i", vNI);		gameSys.textSys.draw(cx+24, cy, &gameVars->player.active->combat_check.initiative, vVal);
			gameSys.drawText(cx, ++cy, "Willpower      [   ]   [   ]", vFont);		gameSys.drawText(cx+16, cy, "n/i", vNI);		gameSys.textSys.draw(cx+24, cy, &gameVars->player.active->combat_check.willpower, vVal);
			gameSys.drawText(cx, ++cy, "Constitution   [   ]   [   ]", vFont);		gameSys.drawText(cx+16, cy, "n/i", vNI);		gameSys.textSys.draw(cx+24, cy, &gameVars->player.active->skill_check.constitution, vVal);
			gameSys.drawText(cx, ++cy, "Intelligence   [   ]   [   ]", vFont);		gameSys.drawText(cx+16, cy, "n/i", vNI);		gameSys.textSys.draw(cx+24, cy, &gameVars->player.active->skill_check.intelligence, vVal);
			gameSys.drawText(cx, ++cy, "Wisdom         [   ]   [   ]", vFont);		gameSys.drawText(cx+16, cy, "n/i", vNI);		gameSys.textSys.draw(cx+24, cy, &gameVars->player.active->skill_check.wisdom, vVal);
			gameSys.drawText(cx, ++cy, "Charisma       [   ]   [   ]", vFont);		gameSys.drawText(cx+16, cy, "n/i", vNI);		gameSys.textSys.draw(cx+24, cy, &gameVars->player.active->skill_check.charisma, vVal);
			gameSys.drawText(cx, ++cy, "Max Load       [   ]   [   ]", vFont);		gameSys.drawText(cx+16, cy, "n/i", vNI);		gameSys.textSys.draw(cx+24, cy, &gameVars->player.active->other_check.load, vVal);
			gameSys.drawText(cx, ++cy, "Stamina        [   ]   [   ]", vFont);		gameSys.drawText(cx+16, cy, "n/i", vNI);		gameSys.textSys.draw(cx+24, cy, &gameVars->player.active->other_check.stamina, vVal);
			gameSys.drawText(cx, ++cy, "Weight         [   ]   [   ]", vFont);		gameSys.drawText(cx+16, cy, "n/i", vNI);		gameSys.textSys.draw(cx+24, cy, &gameVars->player.active->other_check.weight, vVal);
			gameSys.drawText(cx, ++cy, "Mana           [   ]   [   ]", vFont);		gameSys.drawText(cx+16, cy, "n/i", vNI);		//gameSys.textSys.draw(cx+24, cy, &gameVars->player.active->other_check.mana, vVal);
			gameSys.drawText(cx, ++cy, "Presence       [   ]   [   ]", vFont);		gameSys.drawText(cx+16, cy, "n/i", vNI);		gameSys.drawText(cx+24, cy, "n/i", vNI);
			gameSys.drawText(cx, ++cy, "Leadership     [   ]   [   ]", vFont);		gameSys.drawText(cx+16, cy, "n/i", vNI);		gameSys.drawText(cx+24, cy, "n/i", vNI);
			gameSys.drawText(cx, ++cy, "Hunger         [   ]   [   ]", vFont);		gameSys.drawText(cx+16, cy, "n/i", vNI);		gameSys.drawText(cx+24, cy, "n/i", vNI);
			gameSys.drawText(cx, ++cy, "Comprehension  [   ]   [   ]", vFont);		gameSys.drawText(cx+16, cy, "n/i", vNI);		gameSys.drawText(cx+24, cy, "n/i", vNI);
			gameSys.drawText(cx, ++cy, "Execution      [   ]   [   ]", vFont);		gameSys.drawText(cx+16, cy, "n/i", vNI);		gameSys.drawText(cx+24, cy, "n/i", vNI);
			gameSys.drawText(cx, ++cy, "Intensity      [   ]   [   ]", vFont);		gameSys.drawText(cx+16, cy, "n/i", vNI);		gameSys.drawText(cx+24, cy, "n/i", vNI);
			gameSys.drawText(cx, ++cy, "Crafting       [   ]   [   ]", vFont);		gameSys.drawText(cx+16, cy, "n/i", vNI);		gameSys.drawText(cx+24, cy, "n/i", vNI);

			//Page 2: Horizontal divider
			hX = (gameVars->font.vMax[0]/2);
			hY = 30;
			hW = (gameVars->font.vMax[0]/2);
			gameSys.drawSprite(hX+1, hY, gameVars->screen.halfW-(5*gameVars->font.vSize[1]), 3*gameVars->font.vSize[2], "divider.png", false, true, tint);

			cy=32;
			gameSys.drawText(cx, ++cy, "Advantages:", vFont);			gameSys.drawText(cx+os4, cy, "Not Implemented", vNI);
			++cy;
			gameSys.drawText(cx, ++cy, "Disadvantages:", vFont);		gameSys.drawText(cx+os4, cy, "Not Implemented", vNI);
			++cy;
			gameSys.drawText(cx, ++cy, "Natural Abilities:", vFont);	gameSys.drawText(cx+os4, cy, "Not Implemented", vNI);
			break;
		case TAB2:
			{
				/*
				 * ################# PAGE 1 #################
				 *
				 * TODO: The "cohorts" list should be scrollable using the same indexing value as
				 * 				used for the inventory system. Some extra checks will need to be put in
				 * 				place so as not to access invalid/unallocated memory.
				 *
				 * TODO: Possibly show the cards for each party member for a quick overview.
				 */

				/*

				for(int i=0; i<=gameVars->player.active->inventory.iCount; i++) {
					if (gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeFlag == GAME::ITEMS.TYPE.ARMOR) {
						if (gameVars->armor[gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeId].iType == GAME::ARMOR.TYPE.VESTMENT) {

							// Delay printing of inventory until scrolled position
							if( iCount < iInvStart) {
									iCount++;
							}
							else if (iCount < iInvStart+10) {
								if (gameVars->player.active->inventory.iSelected == i) {
									if (gameSys.drawWindow(	cx,	cy,	iW, 5, true, true, inv_select, inv_hover_select, GAME::SYSTEM.WINSYS.DRAWMODE.SELECTION)&MOUSE_LEFT) { gameVars->player.active->inventory.iSelected = -1; };
								}
								else {
									if (gameSys.drawWindow(	cx,	cy,	iW, 5, true, true, inv_normal, inv_hover_normal)&MOUSE_LEFT) { gameVars->player.active->inventory.iSelected = i; };
								}

								// Overlay equipped icon
								if ( ( gameVars->player.active->inventory.equipped.vestment.iHead == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iTorso == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iNeck == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iLegs == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iLeft_Arm == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iLeft_Hand == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iLeft_Leg == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iLeft_Foot == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iRight_Arm == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iRight_Hand == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iRight_Leg == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iRight_Foot == i ) ) {

									gameSys.drawIcon(	cx+1,
																		cy+1,
																		32,
																		32,
																		gameVars->items[gameVars->player.active->inventory.list[i].id].iIcon,
																		gameVars->items[gameVars->player.active->inventory.list[i].id].sTex,
																		false,
																		true,
																		gameVars->color.green);

									gameSys.drawText(cx+5, cy+1, gameVars->items[gameVars->player.active->inventory.list[i].id].name, inv_text);
									gameSys.drawText(cx+5, cy+2, gameVars->armor[gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeId].name, inv_text);
									gameSys.drawText(cx+5, cy+3, GAME::MATERIAL.NAMES[gameVars->items[gameVars->player.active->inventory.list[i].id].iMaterial], inv_text);
									gameSys.drawText(cx+(iW/2), cy+1, gameVars->items[gameVars->player.active->inventory.list[i].id].sDes, inv_des);

									gameSys.drawIcon(	cx+1, cy+1, 32, 32, 6,	"journal.png", 	false, true);		// R. Arm
								}
								else {
									gameSys.drawIcon(	cx+1,
																		cy+1,
																		32,
																		32,
																		gameVars->items[gameVars->player.active->inventory.list[i].id].iIcon,
																		gameVars->items[gameVars->player.active->inventory.list[i].id].sTex,
																		false,
																		true,
																		gameVars->color.white);

									gameSys.drawText(cx+5, cy+1, gameVars->items[gameVars->player.active->inventory.list[i].id].name, inv_text);
									gameSys.drawText(cx+5, cy+2, gameVars->armor[gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeId].name, inv_text);
									gameSys.drawText(cx+5, cy+3, GAME::MATERIAL.NAMES[gameVars->items[gameVars->player.active->inventory.list[i].id].iMaterial], inv_text);
									gameSys.drawText(cx+(iW/2), cy+1, gameVars->items[gameVars->player.active->inventory.list[i].id].sDes, inv_des);
								}
								cy+=4;
								iCount++;
							}
						}
					}
				}
				 */

				cx=6;
				cy=15;

				int iP = 3;																// Padding
				int iW = (gameVars->font.vMax[0]/2)-(2*iP)+1;


				if(iInvStart > 11) iInvStart = 11;
				int iInvEnd = iInvStart + 5;
				if(iInvEnd > 11) iInvEnd = 11;

				for(int i=iInvStart; i<=iInvEnd; i++) {
					CharSheet * sheet = gameVars->player.sheet.cohort.sheet[i];

					if (gameVars->player.sheet.cohort.iSelected == i) {
						if (gameSys.drawWindow(	cx-2,	cy-1,	iW, 7, true, true, inv_select, inv_hover_select, GAME::SYSTEM.WINSYS.DRAWMODE.SELECTION)&MOUSE_LEFT) {
								gameVars->player.sheet.cohort.iSelected = -1;
								gameVars->player.active = &gameVars->player.sheet;
								gameVars->player.sheet.cohort.iSelected = -1;
						}
					}
					else {
						if (gameSys.drawWindow(	cx-2,	cy-1,	iW, 7, true, true, inv_normal, inv_hover_normal)&MOUSE_LEFT) {
								gameVars->player.sheet.cohort.iSelected = i;
								gameVars->player.active = gameVars->player.sheet.cohort.sheet[i];
								gameVars->player.sheet.cohort.iSelected = i;
						}
					}
					//gameSys.drawWindow(	cx-1,	cy-1,	iW, 7, true, true, inv_normal, inv_hover_normal);

					//string iNum = itoa(i, 10);
					gameSys.drawText( cx-1, 	cy+2, itoa(i+1, 10),				gameVars->color.white);
					gameSys.checkIcon(cx+=1,  cy, 64, 64, sheet->init.face, "faces.png", true, true, gameVars->color.journal.inventory_icon);
					gameSys.drawText(	cx+=7,	cy, "Name:", vFont);					gameSys.drawText(cx+os3, cy, sheet->init.name,				gameVars->color.white);
					gameSys.drawText(	cx,		++cy, "Role:", vFont);					gameSys.drawText(cx+os3, cy, sheet->init.sRole,				gameVars->color.white);
					gameSys.drawText(	cx,		++cy, "Race:", vFont);					gameSys.drawText(cx+os3, cy, sheet->init.sRace,				gameVars->color.white);
					gameSys.drawText(	cx,		++cy, "Profession:", vFont);		gameSys.drawText(cx+os3, cy, sheet->init.sProfession, gameVars->color.white);
					cx=6;	cy+=3;
				}

				/*
				 * ################# PAGE 2 #################
				 *
				 * TODO: Create 11x11 (or close) grid for cohort positioning with the center always equal to
				 * 				the primary character, not the selected character.
				 *
				 * TODO: Need to handle multiple cases here:
				 *
				 * 1) Reassigning: Moving a cohort to a new unused location
				 * 2) Swapping: Swapping a cohort to a location already occupied
				 * 3) Handling Leader: Leader cannot be moved
				 *
				 * TODO: Rework to use new placement variables
				 */

				//cx=(gameVars->font.vMax[0]/2)+6;
				int iSize = 32;
				//cx=(gameVars->screen.w/2)+(iSize);
				cx=(gameVars->screen.w/2)+(gameVars->screen.w/4)-(iSize*5)-(iSize/2);
				cy=gameVars->font.vSize[1]*10;
				int iX = -5,
						iY = -5;
				for(int x=cx; x<cx+(11*iSize); x+=iSize) {
						iY = -5;
					for(int y=cy; y<cy+(11*iSize); y+=iSize) {
						if((iX==0) && (iY==0)) {
							gameSys.drawIcon(	x,	y, iSize, iSize, 9, "journal.png", true, false, gameVars->color.journal.inventory_icon);
						}
						else {
							int iCohort = 0;
							bool bSet = false;
							for(int i=0; i<gameVars->player.sheet.cohort.iNum; ++i) {
								if((gameVars->player.sheet.cohort.sheet[i]->cohort.vPlacement[0] == iX) && (gameVars->player.sheet.cohort.sheet[i]->cohort.vPlacement[1] == iY)) {
									bSet = true;
									iCohort = i;
								}
							}

							if(bSet) {
								if(gameSys.checkIcon(	x,	y, iSize, iSize, iCohort+17, "journal.png", true, false, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {
									cout << "Swap Cohort? Else Assign!" << endl;
									if(gameVars->player.sheet.cohort.iSelected >= 0) {
										int iSwapX = gameVars->player.sheet.cohort.sheet[gameVars->player.sheet.cohort.iSelected]->cohort.vPlacement[0],
												iSwapY = gameVars->player.sheet.cohort.sheet[gameVars->player.sheet.cohort.iSelected]->cohort.vPlacement[1];
										gameVars->player.sheet.cohort.sheet[gameVars->player.sheet.cohort.iSelected]->cohort.vPlacement[0] = iX;
										gameVars->player.sheet.cohort.sheet[gameVars->player.sheet.cohort.iSelected]->cohort.vPlacement[1] = iY;

										gameVars->player.sheet.cohort.sheet[iCohort]->cohort.vPlacement[0] = iSwapX;
										gameVars->player.sheet.cohort.sheet[iCohort]->cohort.vPlacement[1] = iSwapY;
									}
								}
							}
							else {
								if(gameSys.checkIcon(	x,	y, iSize, iSize, 16, "journal.png", true, false, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {
									cout << "Assign Cohort!" << endl;
									if(gameVars->player.sheet.cohort.iSelected >= 0) {
										gameVars->player.sheet.cohort.sheet[gameVars->player.sheet.cohort.iSelected]->cohort.vPlacement[0] = iX;
										gameVars->player.sheet.cohort.sheet[gameVars->player.sheet.cohort.iSelected]->cohort.vPlacement[1] = iY;
									}
								}
							}
//							if(gameSys.checkIcon(	x,	y, iSize, iSize, gameVars->player.sheet.cohort.iPlacement[iX][iY]+17, "journal.png", true, false)&MOUSE_LEFT) {
//								if(gameVars->player.sheet.cohort.iSelected >= 0) {
//									bool bClear = false;
//									bool bSwap = false;
//
//									for(int xx=0; xx<11; xx++) {
//										for(int yy=0; yy<11; yy++) {
//											if(gameVars->player.sheet.cohort.iPlacement[xx][yy] == gameVars->player.sheet.cohort.iSelected) {
//												if (gameVars->player.sheet.cohort.iPlacement[iX][iY] >= 0) {
//													iSwapX = xx;
//													iSwapY = yy;
//													bSwap = true;
//												}
//												else {
//														// TODO: This technically should not be allowed, all
//														//	cohorts NEED to forced to be placed eventually.
//														//
//														// TODO: -1 is the iD reserved for the leader of the group
//														gameVars->player.sheet.cohort.iPlacement[xx][yy] = -1;
//
//												}
//												bClear = true;
//											}
//											if(bClear) break;
//										}
//										if(bClear) break;
//									}
//
//									if (bSwap) {
//										gameVars->player.sheet.cohort.iPlacement[iSwapX][iSwapY] = gameVars->player.sheet.cohort.iPlacement[iX][iY];
//										gameVars->player.sheet.cohort.sheet[gameVars->player.sheet.cohort.iPlacement[iX][iY]]->cohort.iX = iSwapX;
//										gameVars->player.sheet.cohort.sheet[gameVars->player.sheet.cohort.iPlacement[iX][iY]]->cohort.iY = iSwapY;
//									}
//									gameVars->player.sheet.cohort.iPlacement[iX][iY] = gameVars->player.sheet.cohort.iSelected;
//								}
//							}
						}
						iY++;
					}
					iX++;
				}
			}
			break;
		case TAB3:
			// Float print debugging
			//gameSys.drawText(cx,   cy, "Torso Resistances (w/o Bonus)", vTitle);
			//gameSys.textSys.draw(cx+24, cy, &gameVars->player.active->other_check.weight, vVal);
			//gameSys.drawVariable(cx, cy, bTemp, tint);
			//gameSys.drawVariable(cx, ++cy, iTemp, tint);
			//gameSys.drawVariable(cx, ++cy, fTemp, tint, false);
			//gameSys.drawVariable(cx, ++cy, fTemp, tint, true);

			{
				// Left Page
				cx=6;
				cy=15;

				int iP = 3;																// Padding
				int iW = (gameVars->font.vMax[0]/2)-(2*iP)+1;


				//if(iInvStart > 11) iInvStart = 11;
				//int iInvEnd = iInvStart + 5;
				//if(iInvEnd > 11) iInvEnd = 11;

				//for(int i=iInvStart; i<=iInvEnd; i++) {
				iW = 12;
				for(int i = 0; i<12; i++) {
					CharSheet * sheet = gameVars->player.sheet.cohort.sheet[i];

					if(i==0) {
						cy = 15;
						cx = 4;
					}

					if(i==2) {
						cy = 15;
						cx = 12;
					}

					if(i==4) {
						cy = 15;
						cx = 20;
					}

					if(i==6) {
						cy = 15;
						cx = 28;
					}

					if(i==8) {
						cy = 15;
						cx = 36;
					}

					if(i==10) {
						cy = 15;
						cx = 44;
					}

					if (gameVars->player.sheet.cohort.iSelected == i) {
						if (gameSys.drawWindow(	cx,	cy-1,	8, 7, true, true, inv_select, inv_hover_select, GAME::SYSTEM.WINSYS.DRAWMODE.SELECTION)&MOUSE_LEFT) {
							gameVars->player.sheet.cohort.iSelected = -1;
							gameVars->player.active = &gameVars->player.sheet;
							gameVars->player.sheet.cohort.iSelected = -1;
						}
					}
					else {
						if (gameSys.drawWindow(	cx,	cy-1,	8, 7, true, true, inv_normal, inv_hover_normal)&MOUSE_LEFT) {
							gameVars->player.sheet.cohort.iSelected = i;
							gameVars->player.active = gameVars->player.sheet.cohort.sheet[i];
							gameVars->player.sheet.cohort.iSelected = i;
						}
					}
					gameSys.drawIcon(	cx+1,   cy, 	64, 64, sheet->init.face, "faces.png", false, true, gameVars->color.journal.inventory_icon);
					cy+=7;

					//gameSys.drawText( cx-1, 	cy+2, itoa(i+1, 10),				gameVars->color.white);
					//gameSys.drawIcon(	cx+1,   cy, 	64, 64, sheet->init.face, "faces.png", true, true);
					//gameSys.drawText(	cx-3,	  cy+6, 	"Name:", vFont);				gameSys.drawText(cx+4, cy+6, sheet->init.name,				gameVars->color.white);
					//gameSys.drawText(cx, cy+5, sheet->init.name,				gameVars->color.white);

				}

				// Right Page
				int iCount = 0;														// Current list count, used for scrolling
				iP = 1;																		// Padding
				iW = (gameVars->font.vMax[0]/2)-(2*iP)-2;	// Useable page width
				cx=(gameVars->font.vMax[0]/2)+iP+2;
				cy=7;

				/*
				 * TODO: Add Filters here
				 */
				if(gameSys.checkText(cx, cy, 	 "Wearables", true)&MOUSE_LEFT) cout << "Click!" << endl;
				if(gameSys.checkText(cx, cy+1, "Armour", true)&MOUSE_LEFT) cout << "Click!" << endl;
				if(gameSys.checkText(cx, cy+2, "Vestments", true)&MOUSE_LEFT) cout << "Click!" << endl;
				if(gameSys.checkText(cx, cy+3, "Quilted", true)&MOUSE_LEFT) cout << "Click!" << endl;
				if(gameSys.checkText(cx, cy+4, "Maille", true)&MOUSE_LEFT) cout << "Click!" << endl;
				if(gameSys.checkText(cx, cy+5, "Plate", true)&MOUSE_LEFT) cout << "Click!" << endl;

				cx+=12;
				if(gameSys.checkText(cx, cy, 	 "Arms", true)&MOUSE_LEFT) cout << "Click!" << endl;
				if(gameSys.checkText(cx, cy+1, "One Hand", true)&MOUSE_LEFT) cout << "Click!" << endl;
				if(gameSys.checkText(cx, cy+2, "Two Hand", true)&MOUSE_LEFT) cout << "Click!" << endl;
				if(gameSys.checkText(cx, cy+3, "One Half", true)&MOUSE_LEFT) cout << "Click!" << endl;
				if(gameSys.checkText(cx, cy+4, "Shield", true)&MOUSE_LEFT) cout << "Click!" << endl;
				if(gameSys.checkText(cx, cy+5, "Jewelry", true)&MOUSE_LEFT) cout << "Click!" << endl;

				cx+=12;
				if(gameSys.checkText(cx, cy, 	 "Magical", true)&MOUSE_LEFT) cout << "Click!" << endl;
				if(gameSys.checkText(cx, cy+1, "Imbued", true)&MOUSE_LEFT) cout << "Click!" << endl;
				if(gameSys.checkText(cx, cy+2, "Wands", true)&MOUSE_LEFT) cout << "Click!" << endl;
				if(gameSys.checkText(cx, cy+3, "Staff", true)&MOUSE_LEFT) cout << "Click!" << endl;
				if(gameSys.checkText(cx, cy+4, "Grenades", true)&MOUSE_LEFT) cout << "Click!" << endl;
				if(gameSys.checkText(cx, cy+5, "Oils", true)&MOUSE_LEFT) cout << "Click!" << endl;

				cx+=12;
				if(gameSys.checkText(cx, cy, 	 "Misc", true)&MOUSE_LEFT) cout << "Click!" << endl;
				if(gameSys.checkText(cx, cy+1, "Consumable", true)&MOUSE_LEFT) cout << "Click!" << endl;
				if(gameSys.checkText(cx, cy+2, "Ingredient", true)&MOUSE_LEFT) cout << "Click!" << endl;
				if(gameSys.checkText(cx, cy+3, "Monetary", true)&MOUSE_LEFT) cout << "Click!" << endl;
				if(gameSys.checkText(cx, cy+4, "Keys", true)&MOUSE_LEFT) cout << "Click!" << endl;
				if(gameSys.checkText(cx, cy+5, "Other", true)&MOUSE_LEFT) cout << "Click!" << endl;

				cx=(gameVars->font.vMax[0]/2)+iP;
				cy=13;

				CharSheet * sheet;
				if(gameVars->player.sheet.cohort.iSelected == -1) sheet = gameVars->player.active;
				else sheet = gameVars->player.sheet.cohort.sheet[gameVars->player.sheet.cohort.iSelected];

				for(int i=0; i<sheet->inventory.iCount; i++) {
					// Delay printing of inventory until scrolled position
					if( iCount < iInvStart) {
							iCount++;
					}
					else if (iCount < iInvStart+10) {

						// Select/Deselect item on click
						if (sheet->inventory.iSelected == i) {
							if (gameSys.drawWindow(	cx,	cy,	iW, 5, true, true, inv_select, inv_hover_select, GAME::SYSTEM.WINSYS.DRAWMODE.SELECTION)&MOUSE_LEFT) { sheet->inventory.iSelected = -1; };
						}
						else {
							if (gameSys.drawWindow(	cx,	cy,	iW, 5, true, true, inv_normal, inv_hover_normal)&MOUSE_LEFT) { sheet->inventory.iSelected = i; };
						}

						gameSys.drawIcon(	cx+1,
															cy+1,
															32,
															32,
															gameVars->items[sheet->inventory.list[i].id].iIcon,
															gameVars->items[sheet->inventory.list[i].id].sTex,
															false,
															true,
															gameVars->color.journal.inventory_icon);

						gameSys.drawText(cx+5, cy+1, gameVars->items[sheet->inventory.list[i].id].name, inv_text);
						//if(bShield) gameSys.drawText(cx+5, cy+2, gameVars->items[gameVars->player.active->inventory.list[i].id].shield->name, inv_text);
						//else gameSys.drawText(cx+5, cy+2, GAME::WEAPON.TYPE.to_str(gameVars->weapon[gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeId].type), inv_text);
						//gameSys.drawText(cx+5, cy+3, GAME::MATERIAL.NAMES[gameVars->items[gameVars->player.active->inventory.list[i].id].iMaterial], inv_text);
						gameSys.drawText(cx+5, cy+2, gameVars->items[sheet->inventory.list[i].id].sDes, inv_des, 45, 2);

						cy+=4;
						iCount++;
					}
				}
			}
			break;
		case TAB4:
			break;
		case TAB5:
			break;
		case TAB6:
			break;
		case TAB7:
			// =========================
			// Inventory / Weapons
			// =========================

			// Draw variable, no interaction
			//gameSys.drawVariable(cx, cy, bTemp, tint);
			//gameSys.drawVariable(cx, ++cy, iTemp, tint);
			//gameSys.drawVariable(cx, ++cy, fTemp, tint, false);
			//gameSys.drawVariable(cx, ++cy, fTemp, tint, true);

			// Draw text
			//gameSys.drawText(x, y, sBuffer, fColor);

			// Draw an icon, no interaction
			//gameSys.drawIcon(cx, cy, 64, 64, 0, "faces.png", false, true);

			// Draw a rectangular window, no interaction
			//gameSys.drawWindow(		sSet.x-suiX,	sSet.y+10,	suiY, 13, false, true, vBack);

			// Draw an image, no interaction
			//gameSys.drawSprite(0,4,gameVars->screen.w-(gameVars->font.vSize[1]),gameVars->screen.h-(12*gameVars->font.vSize[2]),"journal.png", false, true);

			// Draw rectangular window with embedded text, detects mouse input
			//if (gameSys.drawTextWindow(	sSet.x-42,	sSet.y,	13, 3,	"Stance",	true, true, backSelected,	textSelected,	backHover,	textHover2)&MOUSE_LEFT)

			// Draw an image that detects mouse click/hover
			//gameSys.checkSprite(x,y,w,h,sTex,bHighligh,btextOffset,fBackcolor,fBackHcolor);

			// Draw Text that detects a mouse click/hover
			//if (gameSys.menuSys.draw(sSet.x-suiX+1,	sSet.y+13,	"Topaz of Charm")&MOUSE_LEFT);

			// Draw an Icon that detects mouse clicks/hover
			//if (gameSys.checkIcon(sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 34, "wm_icons_subdued.png", true, true)) { eS=GAME::MENU.MOVE.STANCE.KNEEL; exit(true); }	//KNEEL
			//gameSys.checkIcon(x, y, w, h, id, sTex, bHighlight, bTextoffset, fBackColor, fBackHColor);
			//if (gameSys.checkIcon(x, y, w, h, id, ".png", bHighlight, bTextOffset <, fBackColor, fBackHColor>)) { }

			// LEFT PAGE
			// Inventory Listing
			// Weapons only
			// This needs multi-page/scrolling support, maybe add
			//  a button that increases the starting index by the
			//  amount that can be displayed on one screen.
			{
				int iCount = 0;														// Current list count, used for scrolling
				int iP = 3;																// Padding
				int iW = (gameVars->font.vMax[0]/2)-(2*iP)+1;	// Useable page width
				cx=iP;
				cy=13;
				for(int i=0; i<gameVars->player.active->inventory.iCount; i++) {
					if (	(gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeFlag == GAME::ITEMS.TYPE.WEAPON) ||
								(gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeFlag == GAME::ITEMS.TYPE.SHIELD)) {

						// Determine if the item we are looking at is a shield, take note for later reference
						bool bShield = false;
						if(gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeFlag == GAME::ITEMS.TYPE.SHIELD) bShield = true;

						// Delay printing of inventory until scrolled position
						if( iCount < iInvStart) {
								iCount++;
						}
						else if (iCount < iInvStart+10) {

							// Select/Deselect item on click
							if (gameVars->player.active->inventory.iSelected == i) {
								if (gameSys.drawWindow(	cx,	cy,	iW, 5, true, true, inv_select, inv_hover_select, GAME::SYSTEM.WINSYS.DRAWMODE.SELECTION)&MOUSE_LEFT) { gameVars->player.active->inventory.iSelected = -1; };
							}
							else {
								if (gameSys.drawWindow(	cx,	cy,	iW, 5, true, true, inv_normal, inv_hover_normal)&MOUSE_LEFT) { gameVars->player.active->inventory.iSelected = i; };
							}

							// Overlay equipped icon
							if ( ( gameVars->player.active->inventory.equipped.equipment.iHead == i ) ||
									 ( gameVars->player.active->inventory.equipped.equipment.iTorso == i ) ||
									 ( gameVars->player.active->inventory.equipped.equipment.iNeck == i ) ||
									 ( gameVars->player.active->inventory.equipped.equipment.iLegs == i ) ||
									 ( gameVars->player.active->inventory.equipped.equipment.iLeft_Arm == i ) ||
									 ( gameVars->player.active->inventory.equipped.equipment.iLeft_Hand == i ) ||
									 ( gameVars->player.active->inventory.equipped.equipment.iLeft_Leg == i ) ||
									 ( gameVars->player.active->inventory.equipped.equipment.iRight_Arm == i ) ||
									 ( gameVars->player.active->inventory.equipped.equipment.iRight_Hand == i )) {

								gameSys.drawIcon(	cx+1,
																	cy+1,
																	32,
																	32,
																	gameVars->items[gameVars->player.active->inventory.list[i].id].iIcon,
																	gameVars->items[gameVars->player.active->inventory.list[i].id].sTex,
																	false,
																	true,
																	gameVars->color.green);



								gameSys.drawText(cx+5, cy+1, gameVars->items[gameVars->player.active->inventory.list[i].id].name, inv_text);

								if(bShield) gameSys.drawText(cx+5, cy+2, gameVars->items[gameVars->player.active->inventory.list[i].id].shield->name, inv_text);
								else gameSys.drawText(cx+5, cy+2, GAME::WEAPON.TYPE.to_str(gameVars->weapon[gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeId].type), inv_text);

								gameSys.drawText(cx+5, cy+3, GAME::MATERIAL.NAMES[gameVars->items[gameVars->player.active->inventory.list[i].id].iMaterial], inv_text);
								gameSys.drawText(cx+(iW/2), cy+1, gameVars->items[gameVars->player.active->inventory.list[i].id].sDes, inv_des, 25, 3);

								gameSys.drawIcon(	cx+1, cy+1, 32, 32, 6,	"journal.png", 	false, true);		// R. Arm
							}
							else {
								gameSys.drawIcon(	cx+1,
																	cy+1,
																	32,
																	32,
																	gameVars->items[gameVars->player.active->inventory.list[i].id].iIcon,
																	gameVars->items[gameVars->player.active->inventory.list[i].id].sTex,
																	false,
																	true,
																	gameVars->color.journal.inventory_icon);

								gameSys.drawText(cx+5, cy+1, gameVars->items[gameVars->player.active->inventory.list[i].id].name, inv_text);

								if(bShield) gameSys.drawText(cx+5, cy+2, gameVars->items[gameVars->player.active->inventory.list[i].id].shield->name, inv_text);
								else gameSys.drawText(cx+5, cy+2, GAME::WEAPON.TYPE.to_str(gameVars->weapon[gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeId].type), inv_text);

								gameSys.drawText(cx+5, cy+3, GAME::MATERIAL.NAMES[gameVars->items[gameVars->player.active->inventory.list[i].id].iMaterial], inv_text);
								gameSys.drawText(cx+(iW/2), cy+1, gameVars->items[gameVars->player.active->inventory.list[i].id].sDes, inv_des, 25, 3);
							}
							cy+=4;
							iCount++;
						}
					}
				}

				// RIGHT PAGE
				/*
				 * TODO: Do not allow same weapon in mutliple slots
				 *
				 * TODO: Item Hover details
				 */
				cx=(gameVars->font.vMax[0]/2)+7;
				cy=10;

				// Card and body
				{
				int iScale = 484;
				gameSys.drawIcon(cx, cy-3, iScale, iScale, 56, "cards.png", false, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(cx, cy-3, iScale, iScale, 25, "cards.png", false, true, gameVars->color.journal.inventory_icon);
				}

				// Temporary icon number
				int 		iHead				= 7,
								iNeck				= 7,
								iLeft_Arm		= 7,
								iLeft_Hand	= 7,
								iRight_Arm	= 7,
								iRight_Hand	= 7,
								iLeft_Leg		= 7,
								iRight_Leg	= 7;

				// Temporary icon texture file
				string	sHead				= "journal.png",
								sNeck				= "journal.png",
								sLeft_Arm		= "journal.png",
								sLeft_Hand	= "journal.png",
								sRight_Arm	= "journal.png",
								sRight_Hand	= "journal.png",
								sLeft_Leg		= "journal.png",
								sRight_Leg	= "journal.png";

				// Set the Head/Neck slot
				if(gameVars->player.active->inventory.equipped.equipment.iHead != -1) {
					int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iHead].id;
					iHead = gameVars->items[i].iIcon;
					sHead = gameVars->items[i].sTex;
				}
				// Determine if Head/Neck slot is two handed and occupy second slot
				if((gameVars->player.active->inventory.equipped.equipment.iHead != -1) && (gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iHead].id].weapon->hand == GAME::WEAPON.HAND.TWO)) {
					int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iHead].id;
					iNeck = gameVars->items[i].iIcon;
					sNeck = gameVars->items[i].sTex;
				}
				else {		// Only set second slot if two handed weapon is NOT equipped
					if(gameVars->player.active->inventory.equipped.equipment.iNeck != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iNeck].id;
						iNeck = gameVars->items[i].iIcon;
						sNeck = gameVars->items[i].sTex;
					}
				}

				// Right Arm/Left Arm
				if(gameVars->player.active->inventory.equipped.equipment.iRight_Arm != -1) {
					int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iRight_Arm].id;
					iRight_Arm = gameVars->items[i].iIcon;
					sRight_Arm = gameVars->items[i].sTex;
				}
				if((gameVars->player.active->inventory.equipped.equipment.iRight_Arm != -1) && (gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iRight_Arm].id].weapon->hand == GAME::WEAPON.HAND.TWO)) {
					int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iRight_Arm].id;
					iLeft_Arm = gameVars->items[i].iIcon;
					sLeft_Arm = gameVars->items[i].sTex;
				}
				else {
					if(gameVars->player.active->inventory.equipped.equipment.iLeft_Arm != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iLeft_Arm].id;
						iLeft_Arm = gameVars->items[i].iIcon;
						sLeft_Arm = gameVars->items[i].sTex;
					}
				}

				// Right Hand/Left Hand
				if(gameVars->player.active->inventory.equipped.equipment.iRight_Hand != -1) {
					int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iRight_Hand].id;
					iRight_Hand = gameVars->items[i].iIcon;
					sRight_Hand = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.equipment.iRight_Hand != -1 && (gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iRight_Hand].id].weapon->hand == GAME::WEAPON.HAND.TWO)) {
					int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iRight_Hand].id;
					iLeft_Hand = gameVars->items[i].iIcon;
					sLeft_Hand = gameVars->items[i].sTex;
				}
				else {
					if(gameVars->player.active->inventory.equipped.equipment.iLeft_Hand != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iLeft_Hand].id;
						iLeft_Hand = gameVars->items[i].iIcon;
						sLeft_Hand = gameVars->items[i].sTex;
					}
				}

				// Left Leg
				if(gameVars->player.active->inventory.equipped.equipment.iLeft_Leg != -1) {
					int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iLeft_Leg].id;
					iLeft_Leg = gameVars->items[i].iIcon;
					sLeft_Leg = gameVars->items[i].sTex;
				}

				// Left inventory slots
				cx=(gameVars->font.vMax[0]/2)+15;
				cy=10;

				// HEAD
				if(gameSys.checkIcon(		cx, cy,    64, 64, iHead,				sHead, 				true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// Head
					// TODO: If equipping two handed weapon, then unequip second slot
					if(gameVars->player.active->inventory.iSelected == -1) gameVars->player.active->inventory.iSelected = gameVars->player.active->inventory.equipped.equipment.iHead;
					else if(gameVars->player.active->inventory.iSelected == gameVars->player.active->inventory.equipped.equipment.iHead) gameVars->player.active->inventory.equipped.equipment.iHead = -1;
					else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iTypeFlag != GAME::ITEMS.TYPE.SHIELD) {
						if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].weapon->hand == GAME::WEAPON.HAND.TWO) gameVars->player.active->inventory.equipped.equipment.iNeck = -1;
						gameVars->player.active->inventory.equipped.equipment.iHead = gameVars->player.active->inventory.iSelected;
					}
				}

				// RIGHT ARM
				if(gameSys.checkIcon(		cx,   cy+=7, 64, 64, iRight_Arm,	sRight_Arm, 	true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// R. Arm
					if(gameVars->player.active->inventory.iSelected == -1) gameVars->player.active->inventory.iSelected = gameVars->player.active->inventory.equipped.equipment.iRight_Arm;
					else if(gameVars->player.active->inventory.iSelected == gameVars->player.active->inventory.equipped.equipment.iRight_Arm) gameVars->player.active->inventory.equipped.equipment.iRight_Arm = -1;
					else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iTypeFlag != GAME::ITEMS.TYPE.SHIELD) {
						if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].weapon->hand == GAME::WEAPON.HAND.TWO) gameVars->player.active->inventory.equipped.equipment.iLeft_Arm = -1;
						gameVars->player.active->inventory.equipped.equipment.iRight_Arm = gameVars->player.active->inventory.iSelected;
					}
				}

				// RIGHT HAND
				if(gameSys.checkIcon(		cx,   cy+=7, 64, 64, iRight_Hand,	sRight_Hand,	true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// R. Hand
					if(gameVars->player.active->inventory.iSelected == -1) gameVars->player.active->inventory.iSelected = gameVars->player.active->inventory.equipped.equipment.iRight_Hand;
					else if(gameVars->player.active->inventory.iSelected == gameVars->player.active->inventory.equipped.equipment.iRight_Hand) gameVars->player.active->inventory.equipped.equipment.iRight_Hand = -1;
					else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iTypeFlag != GAME::ITEMS.TYPE.SHIELD) {
						if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].weapon->hand == GAME::WEAPON.HAND.TWO) gameVars->player.active->inventory.equipped.equipment.iLeft_Hand = -1;
						gameVars->player.active->inventory.equipped.equipment.iRight_Hand = gameVars->player.active->inventory.iSelected;
					}
				}

				// Right inventory slots
				cx=(gameVars->font.vMax[0]/2)+37;
				cy=10;

				// NECK
				if(gameSys.checkIcon(		cx, cy,    64, 64, iNeck,				sNeck,				true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {
					if(gameVars->player.active->inventory.equipped.equipment.iHead != -1) {
						if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iHead].id].weapon->hand == GAME::WEAPON.HAND.TWO) {
							gameVars->player.active->inventory.equipped.equipment.iHead = -1;
							gameVars->player.active->inventory.equipped.equipment.iNeck = -1;
						}
					}

					if(gameVars->player.active->inventory.iSelected == -1) gameVars->player.active->inventory.iSelected = gameVars->player.active->inventory.equipped.equipment.iNeck;
					else if(gameVars->player.active->inventory.iSelected == gameVars->player.active->inventory.equipped.equipment.iNeck) gameVars->player.active->inventory.equipped.equipment.iNeck = -1;
					else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iTypeFlag == GAME::ITEMS.TYPE.SHIELD) gameVars->player.active->inventory.equipped.equipment.iNeck = gameVars->player.active->inventory.iSelected;
				}

				// LEFT ARM
				if(gameSys.checkIcon(		cx,   cy+=7, 64, 64, iLeft_Arm,		sLeft_Arm,		true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {
					if(gameVars->player.active->inventory.equipped.equipment.iRight_Arm != -1) {
						if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iRight_Arm].id].weapon->hand == GAME::WEAPON.HAND.TWO) {
							gameVars->player.active->inventory.equipped.equipment.iLeft_Arm = -1;
							gameVars->player.active->inventory.equipped.equipment.iRight_Arm = -1;
						}
					}

					if(gameVars->player.active->inventory.iSelected == -1) gameVars->player.active->inventory.iSelected = gameVars->player.active->inventory.equipped.equipment.iLeft_Arm;
					else if(gameVars->player.active->inventory.iSelected == gameVars->player.active->inventory.equipped.equipment.iLeft_Arm) gameVars->player.active->inventory.equipped.equipment.iLeft_Arm = -1;
					else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iTypeFlag == GAME::ITEMS.TYPE.SHIELD) gameVars->player.active->inventory.equipped.equipment.iLeft_Arm = gameVars->player.active->inventory.iSelected;
				}

				// LEFT HAND
				if(gameSys.checkIcon(		cx,   cy+=7, 64, 64, iLeft_Hand,	sLeft_Hand,		true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// L. Hand
					if(gameVars->player.active->inventory.equipped.equipment.iRight_Hand != -1) {
						if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iRight_Hand].id].weapon->hand == GAME::WEAPON.HAND.TWO) {
							gameVars->player.active->inventory.equipped.equipment.iLeft_Hand = -1;
							gameVars->player.active->inventory.equipped.equipment.iRight_Hand = -1;
						}
					}

					if(gameVars->player.active->inventory.iSelected == -1) gameVars->player.active->inventory.iSelected = gameVars->player.active->inventory.equipped.equipment.iLeft_Hand;
					else if(gameVars->player.active->inventory.iSelected == gameVars->player.active->inventory.equipped.equipment.iLeft_Hand) gameVars->player.active->inventory.equipped.equipment.iLeft_Hand = -1;
					else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iTypeFlag == GAME::ITEMS.TYPE.SHIELD) gameVars->player.active->inventory.equipped.equipment.iLeft_Hand = gameVars->player.active->inventory.iSelected;
				}

				// LEFT LEG
				if(gameSys.checkIcon(		cx, cy+=7, 64, 64, iLeft_Leg,		sLeft_Leg,		true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// L. Leg

					// TODO: Only allow daggers here, will need to add a dagger to the damage types probably
					if(gameVars->player.active->inventory.iSelected == -1) gameVars->player.active->inventory.iSelected = gameVars->player.active->inventory.equipped.equipment.iLeft_Leg;
					else if(gameVars->player.active->inventory.iSelected == gameVars->player.active->inventory.equipped.equipment.iLeft_Leg) gameVars->player.active->inventory.equipped.equipment.iLeft_Leg = -1;
					else if((gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iTypeFlag == GAME::ITEMS.TYPE.WEAPON) &&
									(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].weapon->type == GAME::WEAPON.TYPE.BLADE) &&
									(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].weapon->range <= 1.0f) ) {
						gameVars->player.active->inventory.equipped.equipment.iLeft_Leg = gameVars->player.active->inventory.iSelected;
					}
				}

				// Left side holsters
				cx=(gameVars->font.vMax[0]/2)+3;
				cy=7;
				gameSys.drawWindow(	cx++, cy++, 9, 12, false, true, holster_back);
				gameSys.drawText(		cx, 	cy, "Potions", holster_text);
				gameSys.drawIcon(		cx, 	cy+=1, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				cx+=4; cy-=6;
				gameSys.drawIcon(		cx, 	cy,    32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);

				cx-=5;
				cy+=4;
				gameSys.drawWindow(	cx++, cy++, 9, 12, false, true, holster_back);
				gameSys.drawText(		cx, 	cy, "Wands", holster_text);
				gameSys.drawIcon(		cx, 	cy+=1, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				cx+=4; cy-=6;
				gameSys.drawIcon(		cx, 	cy,    32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);

				cx-=5;
				cy+=4;
				gameSys.drawWindow(	cx++, cy++, 9, 21, false, true, holster_back);
				gameSys.drawText(		cx, 	cy, "Arrows", holster_text);
				gameSys.drawIcon(		cx, 	cy+=1, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				cx+=4; cy-=15;
				gameSys.drawIcon(		cx, 	cy,    32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);

				// Assessory Slots
				cx=(gameVars->font.vMax[0]/2)+12;
				cy=45;
				gameSys.drawWindow(	cx++,		cy++, 34, 8, false, true, holster_back);
				gameSys.drawIcon(		cx,			cy, 32, 32, 5, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx+=4,	cy, 32, 32, 5, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx+=4,	cy, 32, 32, 5, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx+=4,	cy, 32, 32, 5, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx+=4,	cy, 32, 32, 5, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx+=4,	cy, 32, 32, 5, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx+=4,	cy, 32, 32, 5, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx+=4,	cy, 32, 32, 5, "01_num.png", true, true, gameVars->color.journal.inventory_icon);

				cx-=28;
				cy+=3;
				gameSys.drawIcon(		cx,			cy, 32, 32, 5, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx+=4,	cy, 32, 32, 5, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx+=4,	cy, 32, 32, 5, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx+=4,	cy, 32, 32, 5, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx+=4,	cy, 32, 32, 5, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx+=4,	cy, 32, 32, 5, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx+=4,	cy, 32, 32, 5, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx+=4,	cy, 32, 32, 5, "01_num.png", true, true);

				// Right Holsters
				cx=(gameVars->font.vMax[0]/2)+46;
				cy=7;
				gameSys.drawWindow(	cx++, cy++, 9, 12, false, true, holster_back);
				gameSys.drawText(		cx, 	cy, "Nades", holster_text);
				gameSys.drawIcon(		cx, 	cy+=1, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				cx+=4; cy-=6;
				gameSys.drawIcon(		cx, 	cy,    32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);

				cx-=5;
				cy+=4;
				gameSys.drawWindow(	cx++, cy++, 9, 12, false, true, holster_back);
				gameSys.drawText(		cx, 	cy, "Inbued", holster_text);
				gameSys.drawIcon(		cx, 	cy+=1, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				cx+=4; cy-=6;
				gameSys.drawIcon(		cx, 	cy,    32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);

				cx-=5;
				cy+=4;
				gameSys.drawWindow(	cx++, cy++, 9, 21, false, true, holster_back);
				gameSys.drawText(		cx, 	cy, "Bolts", holster_text);
				gameSys.drawIcon(		cx, 	cy+=1, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				cx+=4; cy-=15;
				gameSys.drawIcon(		cx, 	cy,    32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
				gameSys.drawIcon(		cx, 	cy+=3, 32, 32, 19, "01_num.png", true, true, gameVars->color.journal.inventory_icon);
			}
			break;
		case TAB8:
			{
				// =========================
				// Vestments
				// =========================
				// LEFT PAGE
				// Inventory Listing
				// Weapons only
				// This needs multi-page/scrolling support, maybe add
				//  a button that increases the starting index by the
				//  amount that can be displayed on one screen.
				int iCount = 0;														// Current list count, used for scrolling
				int iP = 3;																// Padding
				int iW = (gameVars->font.vMax[0]/2)-(2*iP)+1;	// Useable page width
				cx=iP;
				cy=13;
				for(int i=0; i<gameVars->player.active->inventory.iCount; i++) {
					if (gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeFlag == GAME::ITEMS.TYPE.ARMOR) {
						if (gameVars->armor[gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeId].iType == GAME::ARMOR.TYPE.VESTMENT) {

							// Delay printing of inventory until scrolled position
							if( iCount < iInvStart) {
									iCount++;
							}
							else if (iCount < iInvStart+10) {
								if (gameVars->player.active->inventory.iSelected == i) {
									if (gameSys.drawWindow(	cx,	cy,	iW, 5, true, true, inv_select, inv_hover_select, GAME::SYSTEM.WINSYS.DRAWMODE.SELECTION)&MOUSE_LEFT) { gameVars->player.active->inventory.iSelected = -1; };
								}
								else {
									if (gameSys.drawWindow(	cx,	cy,	iW, 5, true, true, inv_normal, inv_hover_normal)&MOUSE_LEFT) { gameVars->player.active->inventory.iSelected = i; };
								}

								// Overlay equipped icon
								if ( ( gameVars->player.active->inventory.equipped.vestment.iHead == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iTorso == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iNeck == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iLegs == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iLeft_Arm == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iLeft_Hand == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iLeft_Leg == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iLeft_Foot == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iRight_Arm == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iRight_Hand == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iRight_Leg == i ) ||
										 ( gameVars->player.active->inventory.equipped.vestment.iRight_Foot == i ) ) {

									gameSys.drawIcon(	cx+1,
																		cy+1,
																		32,
																		32,
																		gameVars->items[gameVars->player.active->inventory.list[i].id].iIcon,
																		gameVars->items[gameVars->player.active->inventory.list[i].id].sTex,
																		false,
																		true,
																		gameVars->color.green);

									gameSys.drawText(cx+5, cy+1, gameVars->items[gameVars->player.active->inventory.list[i].id].name, inv_text);
									gameSys.drawText(cx+5, cy+2, gameVars->armor[gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeId].name, inv_text);
									gameSys.drawText(cx+5, cy+3, GAME::MATERIAL.NAMES[gameVars->items[gameVars->player.active->inventory.list[i].id].iMaterial], inv_text);
									gameSys.drawText(cx+(iW/2), cy+1, gameVars->items[gameVars->player.active->inventory.list[i].id].sDes, inv_des, 25, 3);

									gameSys.drawIcon(	cx+1, cy+1, 32, 32, 6,	"journal.png", 	false, true);		// R. Arm
								}
								else {
									gameSys.drawIcon(	cx+1,
																		cy+1,
																		32,
																		32,
																		gameVars->items[gameVars->player.active->inventory.list[i].id].iIcon,
																		gameVars->items[gameVars->player.active->inventory.list[i].id].sTex,
																		false,
																		true,
																		gameVars->color.journal.inventory_icon);

									gameSys.drawText(cx+5, cy+1, gameVars->items[gameVars->player.active->inventory.list[i].id].name, inv_text);
									gameSys.drawText(cx+5, cy+2, gameVars->armor[gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeId].name, inv_text);
									gameSys.drawText(cx+5, cy+3, GAME::MATERIAL.NAMES[gameVars->items[gameVars->player.active->inventory.list[i].id].iMaterial], inv_text);
									gameSys.drawText(cx+(iW/2), cy+1, gameVars->items[gameVars->player.active->inventory.list[i].id].sDes, inv_des, 25, 3);
								}
								cy+=4;
								iCount++;
							}
						}
					}
				}

				// RIGHT PAGE
				/*
				 * TODO: Item Hover details
				 */
				cx=(gameVars->font.vMax[0]/2)+7;
				cy=10;

				// Card and body
				{
					int iScale = 484;
					gameSys.drawIcon(cx, cy-3, iScale, iScale, 56, "cards.png", false, true, gameVars->color.journal.inventory_icon);
					gameSys.drawIcon(cx, cy-3, iScale, iScale, 25, "cards.png", false, true, gameVars->color.journal.inventory_icon);
				}

				// Temporary icon number
				int 		iHead				= 7,
								iTorso			= 7,
								iNeck				= 7,
								iLegs				= 7,
								iLeft_Arm		= 7,
								iLeft_Hand	= 7,
								iRight_Arm	= 7,
								iRight_Hand	= 7,
								iLeft_Leg		= 7,
								iLeft_Foot	= 7,
								iRight_Leg	= 7,
								iRight_Foot	= 7;

				// Temporary icon texture file
				string	sHead				= "journal.png",
								sTorso			= "journal.png",
								sNeck				= "journal.png",
								sLegs				= "journal.png",
								sLeft_Arm		= "journal.png",
								sLeft_Hand	= "journal.png",
								sRight_Arm	= "journal.png",
								sRight_Hand	= "journal.png",
								sLeft_Leg		= "journal.png",
								sLeft_Foot	= "journal.png",
								sRight_Leg	= "journal.png",
								sRight_Foot	= "journal.png";

				if(gameVars->player.active->inventory.equipped.vestment.iHead != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.vestment.iHead].id;
						iHead = gameVars->items[i].iIcon;
						sHead = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.vestment.iTorso != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.vestment.iTorso].id;
						iTorso = gameVars->items[i].iIcon;
						sTorso = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.vestment.iNeck != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.vestment.iNeck].id;
						iNeck = gameVars->items[i].iIcon;
						sNeck = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.vestment.iLegs != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.vestment.iLegs].id;
						iLegs = gameVars->items[i].iIcon;
						sLegs = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.vestment.iLeft_Arm != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.vestment.iLeft_Arm].id;
						iLeft_Arm = gameVars->items[i].iIcon;
						sLeft_Arm = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.vestment.iLeft_Hand != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.vestment.iLeft_Hand].id;
						iLeft_Hand = gameVars->items[i].iIcon;
						sLeft_Hand = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.vestment.iLeft_Leg != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.vestment.iLeft_Leg].id;
						iLeft_Leg = gameVars->items[i].iIcon;
						sLeft_Leg = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.vestment.iLeft_Foot != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.vestment.iLeft_Foot].id;
						iLeft_Foot = gameVars->items[i].iIcon;
						sLeft_Foot = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.vestment.iRight_Arm != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.vestment.iRight_Arm].id;
						iRight_Arm = gameVars->items[i].iIcon;
						sRight_Arm = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.vestment.iRight_Hand != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.vestment.iRight_Hand].id;
						iRight_Hand = gameVars->items[i].iIcon;
						sRight_Hand = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.vestment.iRight_Leg != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.vestment.iRight_Leg].id;
						iRight_Leg = gameVars->items[i].iIcon;
						sRight_Leg = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.vestment.iRight_Foot != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.vestment.iRight_Foot].id;
						iRight_Foot = gameVars->items[i].iIcon;
						sRight_Foot = gameVars->items[i].sTex;
				}

				string sHover = "";			// Text to display for mouse hover
				// Left inventory slots
				cx=(gameVars->font.vMax[0]/2)+15;
				cy=10;

				// Head
				uint uiStatus = gameSys.checkIcon(		cx+4, cy,    64, 64, iHead,				sHead, 				true, true, gameVars->color.journal.inventory_icon);
				if(uiStatus&MOUSE_LEFT) {
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.vestment.iHead = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.HEAD)
								gameVars->player.active->inventory.equipped.vestment.iHead = gameVars->player.active->inventory.iSelected;
				}
				else if(uiStatus&MOUSE_HOVER) {
					if(gameVars->player.active->inventory.equipped.vestment.iHead > -1) {
						sHover	= "Name: " + gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.vestment.iHead].id].name + "\n" +
											"Type: " + gameVars->armor[gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.vestment.iHead].id].iTypeId].name + "\n" +
											"Material: " + GAME::MATERIAL.NAMES[gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.vestment.iHead].id].iMaterial] + "\n";


						//gameSys.drawText(cx+5, cy+1, gameVars->items[gameVars->player.active->inventory.list[i].id].name, inv_text);
						//gameSys.drawText(cx+5, cy+2, gameVars->armor[gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeId].name, inv_text);
						//gameSys.drawText(cx+5, cy+3, GAME::MATERIAL.NAMES[gameVars->items[gameVars->player.active->inventory.list[i].id].iMaterial], inv_text);
						//gameSys.drawText(cx+(iW/2), cy+1, gameVars->items[gameVars->player.active->inventory.list[i].id].sDes, inv_des, 25, 3);

					}
				}

				uiStatus = gameSys.checkIcon(		cx,   cy+=7, 64, 64, iRight_Arm,	sRight_Arm, 	true, true, gameVars->color.journal.inventory_icon);
				if(uiStatus&MOUSE_LEFT) {		// R. Arm
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.vestment.iRight_Arm = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.RIGHT_ARM)
								gameVars->player.active->inventory.equipped.vestment.iRight_Arm = gameVars->player.active->inventory.iSelected;
				}
				else if(uiStatus&MOUSE_HOVER) {
						cout << "HOVER!" << endl;
				}

				uiStatus = gameSys.checkIcon(		cx,   cy+=7, 64, 64, iRight_Hand,	sRight_Hand,	true, true, gameVars->color.journal.inventory_icon);
				if(uiStatus&MOUSE_LEFT) {		// R. Hand
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.vestment.iRight_Hand = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.RIGHT_HAND)
								gameVars->player.active->inventory.equipped.vestment.iRight_Hand = gameVars->player.active->inventory.iSelected;
				}
				else if(uiStatus&MOUSE_HOVER) {
						cout << "HOVER!" << endl;
				}

				uiStatus = gameSys.checkIcon(		cx+3, cy+=7, 64, 64, iRight_Leg,	sRight_Leg,		true, true, gameVars->color.journal.inventory_icon);
				if(uiStatus&MOUSE_LEFT) {		// R. Leg
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.vestment.iRight_Leg = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.RIGHT_LEG)
								gameVars->player.active->inventory.equipped.vestment.iRight_Leg = gameVars->player.active->inventory.iSelected;
				}
				else if(uiStatus&MOUSE_HOVER) {
						cout << "HOVER!" << endl;
				}

				uiStatus = gameSys.checkIcon(		cx+3, cy+=7, 64, 64, iRight_Foot,	sRight_Foot,	true, true, gameVars->color.journal.inventory_icon);
				if(uiStatus&MOUSE_LEFT) {		// R. Foot
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.vestment.iRight_Foot = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.RIGHT_FOOT)
								gameVars->player.active->inventory.equipped.vestment.iRight_Foot = gameVars->player.active->inventory.iSelected;
				}

				// Right inventory slots
				cx=(gameVars->font.vMax[0]/2)+37;
				cy=10;
				uiStatus = gameSys.checkIcon(		cx-4, cy,    64, 64, iNeck,				sNeck,				true, true, gameVars->color.journal.inventory_icon);
				if(uiStatus&MOUSE_LEFT) {		// Neck
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.vestment.iNeck = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.NECK)
								gameVars->player.active->inventory.equipped.vestment.iNeck = gameVars->player.active->inventory.iSelected;
				}
				else if(uiStatus&MOUSE_HOVER) {
						cout << "HOVER!" << endl;
				}

				uiStatus = gameSys.checkIcon(		cx,   cy+=7, 64, 64, iLeft_Arm,		sLeft_Arm,		true, true, gameVars->color.journal.inventory_icon);
				if(uiStatus&MOUSE_LEFT) {		// L. Arm
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.vestment.iLeft_Arm = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.LEFT_ARM)
								gameVars->player.active->inventory.equipped.vestment.iLeft_Arm = gameVars->player.active->inventory.iSelected;
				}
				else if(uiStatus&MOUSE_HOVER) {
						cout << "HOVER!" << endl;
				}

				uiStatus = gameSys.checkIcon(		cx,   cy+=7, 64, 64, iLeft_Hand,	sLeft_Hand,		true, true, gameVars->color.journal.inventory_icon);
				if(uiStatus&MOUSE_LEFT) {		// L. Hand
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.vestment.iLeft_Hand = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.LEFT_HAND)
								gameVars->player.active->inventory.equipped.vestment.iLeft_Hand = gameVars->player.active->inventory.iSelected;
				}
				else if(uiStatus&MOUSE_HOVER) {
						cout << "HOVER!" << endl;
				}

				uiStatus = gameSys.checkIcon(		cx-3, cy+=7, 64, 64, iLeft_Leg,		sLeft_Leg,		true, true, gameVars->color.journal.inventory_icon);
				if(uiStatus&MOUSE_LEFT) {		// L. Leg
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.vestment.iLeft_Leg = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.LEFT_LEG)
								gameVars->player.active->inventory.equipped.vestment.iLeft_Leg = gameVars->player.active->inventory.iSelected;
				}
				else if(uiStatus&MOUSE_HOVER) {
						cout << "HOVER!" << endl;
				}

				uiStatus = gameSys.checkIcon(		cx-3, cy+=7, 64, 64, iLeft_Foot,	sLeft_Foot,		true, true, gameVars->color.journal.inventory_icon);
				if(uiStatus&MOUSE_LEFT) {		// L. Foot
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.vestment.iLeft_Foot = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.LEFT_FOOT)
								gameVars->player.active->inventory.equipped.vestment.iLeft_Foot = gameVars->player.active->inventory.iSelected;
				}
				else if(uiStatus&MOUSE_HOVER) {
						cout << "HOVER!" << endl;
				}

				uiStatus =

				// Center Slots
				cx=(gameVars->font.vMax[0]/2)+26;
				cy=18;
				uiStatus = gameSys.checkIcon(		cx,		cy, 		64, 64, iTorso,			sTorso,				true, true, gameVars->color.journal.inventory_icon);
				if(uiStatus&MOUSE_LEFT) {		// Torso
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.vestment.iTorso = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.TORSO)
								gameVars->player.active->inventory.equipped.vestment.iTorso = gameVars->player.active->inventory.iSelected;
				}
				else if(uiStatus&MOUSE_HOVER) {
						cout << "HOVER!" << endl;
				}

				uiStatus = gameSys.checkIcon(		cx, 	cy+=10, 64, 64, iLegs,			sLegs,				true, true, gameVars->color.journal.inventory_icon);
				if(uiStatus&MOUSE_LEFT) {		// Legs
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.vestment.iLegs = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.LEGS)
								gameVars->player.active->inventory.equipped.vestment.iLegs = gameVars->player.active->inventory.iSelected;
				}
				else if(uiStatus&MOUSE_HOVER) {
						cout << "HOVER!" << endl;
				}

				if(sHover != "") {
					cx=(gameVars->font.vMax[0]/2)+15;
					cy=10;
					gameSys.drawTextWindow(	cx-13,	cy+35,	52,	7,	sHover,	false, true);
				}
			}
			break;
		case TAB9:
			{
				int iCount = 0;														// Current list count, used for scrolling
				int iP = 3;																// Padding
				int iW = (gameVars->font.vMax[0]/2)-(2*iP)+1;	// Useable page width
				cx=iP;
				cy=13;
				for(int i=0; i<gameVars->player.active->inventory.iCount; i++) {
					if (gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeFlag == GAME::ITEMS.TYPE.ARMOR) {
						if (gameVars->armor[gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeId].iType == GAME::ARMOR.TYPE.QUILTED) {
							// Delay printing of inventory until scrolled position
							if( iCount < iInvStart) {
									iCount++;
							}
							else if (iCount < iInvStart+10) {
								if (gameVars->player.active->inventory.iSelected == i) {
									if (gameSys.drawWindow(	cx,	cy,	iW, 5, true, true, inv_select, inv_hover_select, GAME::SYSTEM.WINSYS.DRAWMODE.SELECTION)&MOUSE_LEFT) { gameVars->player.active->inventory.iSelected = -1; };
								}
								else {
									if (gameSys.drawWindow(	cx,	cy,	iW, 5, true, true, inv_normal, inv_hover_normal)&MOUSE_LEFT) { gameVars->player.active->inventory.iSelected = i; };
								}

								// Overlay equipped icon
								if ( ( gameVars->player.active->inventory.equipped.quilted.iHead == i ) ||
										 ( gameVars->player.active->inventory.equipped.quilted.iTorso == i ) ||
										 ( gameVars->player.active->inventory.equipped.quilted.iNeck == i ) ||
										 ( gameVars->player.active->inventory.equipped.quilted.iLegs == i ) ||
										 ( gameVars->player.active->inventory.equipped.quilted.iLeft_Arm == i ) ||
										 ( gameVars->player.active->inventory.equipped.quilted.iLeft_Hand == i ) ||
										 ( gameVars->player.active->inventory.equipped.quilted.iLeft_Leg == i ) ||
										 ( gameVars->player.active->inventory.equipped.quilted.iLeft_Foot == i ) ||
										 ( gameVars->player.active->inventory.equipped.quilted.iRight_Arm == i ) ||
										 ( gameVars->player.active->inventory.equipped.quilted.iRight_Hand == i ) ||
										 ( gameVars->player.active->inventory.equipped.quilted.iRight_Leg == i ) ||
										 ( gameVars->player.active->inventory.equipped.quilted.iRight_Foot == i ) ) {

										gameSys.drawIcon(	cx+1,
																			cy+1,
																			32,
																			32,
																			gameVars->items[gameVars->player.active->inventory.list[i].id].iIcon,
																			gameVars->items[gameVars->player.active->inventory.list[i].id].sTex,
																			false,
																			true,
																			gameVars->color.green);

										gameSys.drawIcon(	cx+1, cy+1, 32, 32, 6,	"journal.png", 	false, true);		// R. Arm
								}
								else {
										gameSys.drawIcon(	cx+1,
																			cy+1,
																			32,
																			32,
																			gameVars->items[gameVars->player.active->inventory.list[i].id].iIcon,
																			gameVars->items[gameVars->player.active->inventory.list[i].id].sTex,
																			false,
																			true,
																			gameVars->color.journal.inventory_icon);
								}

								gameSys.drawText(cx+5, cy+1, gameVars->items[gameVars->player.active->inventory.list[i].id].name, inv_text);
								gameSys.drawText(cx+5, cy+2, gameVars->armor[gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeId].name, inv_text);
								gameSys.drawText(cx+5, cy+3, GAME::MATERIAL.NAMES[gameVars->items[gameVars->player.active->inventory.list[i].id].iMaterial], inv_text);
								gameSys.drawText(cx+(iW/2), cy+1, gameVars->items[gameVars->player.active->inventory.list[i].id].sDes, inv_des, 25, 3);

								cy+=4;
								iCount++;
							}
						}
					}
				}

				// RIGHT PAGE
				/*
				 * TODO: Item Hover details
				 */
				cx=(gameVars->font.vMax[0]/2)+7;
				cy=10;

				// Card and body
				{
					int iScale = 484;
					gameSys.drawIcon(cx, cy-3, iScale, iScale, 56, "cards.png", false, true, gameVars->color.journal.inventory_icon);
					gameSys.drawIcon(cx, cy-3, iScale, iScale, 25, "cards.png", false, true, gameVars->color.journal.inventory_icon);
				}

				// Temporary icon number
				int 		iHead				= 7,
								iTorso			= 7,
								iNeck				= 7,
								iLegs				= 7,
								iLeft_Arm		= 7,
								iLeft_Hand	= 7,
								iRight_Arm	= 7,
								iRight_Hand	= 7,
								iLeft_Leg		= 7,
								iLeft_Foot	= 7,
								iRight_Leg	= 7,
								iRight_Foot	= 7;

				// Temporary icon texture file
				string	sHead				= "journal.png",
								sTorso			= "journal.png",
								sNeck				= "journal.png",
								sLegs				= "journal.png",
								sLeft_Arm		= "journal.png",
								sLeft_Hand	= "journal.png",
								sRight_Arm	= "journal.png",
								sRight_Hand	= "journal.png",
								sLeft_Leg		= "journal.png",
								sLeft_Foot	= "journal.png",
								sRight_Leg	= "journal.png",
								sRight_Foot	= "journal.png";

				if(gameVars->player.active->inventory.equipped.quilted.iHead != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.quilted.iHead].id;
						iHead = gameVars->items[i].iIcon;
						sHead = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.quilted.iTorso != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.quilted.iTorso].id;
						iTorso = gameVars->items[i].iIcon;
						sTorso = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.quilted.iNeck != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.quilted.iNeck].id;
						iNeck = gameVars->items[i].iIcon;
						sNeck = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.quilted.iLegs != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.quilted.iLegs].id;
						iLegs = gameVars->items[i].iIcon;
						sLegs = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.quilted.iLeft_Arm != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.quilted.iLeft_Arm].id;
						iLeft_Arm = gameVars->items[i].iIcon;
						sLeft_Arm = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.quilted.iLeft_Hand != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.quilted.iLeft_Hand].id;
						iLeft_Hand = gameVars->items[i].iIcon;
						sLeft_Hand = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.quilted.iLeft_Leg != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.quilted.iLeft_Leg].id;
						iLeft_Leg = gameVars->items[i].iIcon;
						sLeft_Leg = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.quilted.iLeft_Foot != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.quilted.iLeft_Foot].id;
						iLeft_Foot = gameVars->items[i].iIcon;
						sLeft_Foot = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.quilted.iRight_Arm != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.quilted.iRight_Arm].id;
						iRight_Arm = gameVars->items[i].iIcon;
						sRight_Arm = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.quilted.iRight_Hand != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.quilted.iRight_Hand].id;
						iRight_Hand = gameVars->items[i].iIcon;
						sRight_Hand = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.quilted.iRight_Leg != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.quilted.iRight_Leg].id;
						iRight_Leg = gameVars->items[i].iIcon;
						sRight_Leg = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.quilted.iRight_Foot != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.quilted.iRight_Foot].id;
						iRight_Foot = gameVars->items[i].iIcon;
						sRight_Foot = gameVars->items[i].sTex;
				}

				// Left inventory slots
				cx=(gameVars->font.vMax[0]/2)+15;
				cy=10;
				if(gameSys.checkIcon(		cx+4, cy,    64, 64, iHead,				sHead, 				true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// Head
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.quilted.iHead = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.HEAD)
								gameVars->player.active->inventory.equipped.quilted.iHead = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx,   cy+=7, 64, 64, iRight_Arm,	sRight_Arm, 	true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// R. Arm
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.quilted.iRight_Arm = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.RIGHT_ARM)
								gameVars->player.active->inventory.equipped.quilted.iRight_Arm = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx,   cy+=7, 64, 64, iRight_Hand,	sRight_Hand,	true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// R. Hand
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.quilted.iRight_Hand = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.RIGHT_HAND)
								gameVars->player.active->inventory.equipped.quilted.iRight_Hand = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx+3, cy+=7, 64, 64, iRight_Leg,	sRight_Leg,		true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// R. Leg
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.quilted.iRight_Leg = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.RIGHT_LEG)
								gameVars->player.active->inventory.equipped.quilted.iRight_Leg = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx+3, cy+=7, 64, 64, iRight_Foot,	sRight_Foot,	true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// R. Foot
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.quilted.iRight_Foot = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.RIGHT_FOOT)
								gameVars->player.active->inventory.equipped.quilted.iRight_Foot = gameVars->player.active->inventory.iSelected;
				}

				// Right inventory slots
				cx=(gameVars->font.vMax[0]/2)+37;
				cy=10;
				if(gameSys.checkIcon(		cx-4, cy,    64, 64, iNeck,				sNeck,				true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// Neck
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.quilted.iNeck = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.NECK)
								gameVars->player.active->inventory.equipped.quilted.iNeck = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx,   cy+=7, 64, 64, iLeft_Arm,		sLeft_Arm,		true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// L. Arm
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.quilted.iLeft_Arm = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.LEFT_ARM)
								gameVars->player.active->inventory.equipped.quilted.iLeft_Arm = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx,   cy+=7, 64, 64, iLeft_Hand,	sLeft_Hand,		true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// L. Hand
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.quilted.iLeft_Hand = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.LEFT_HAND)
								gameVars->player.active->inventory.equipped.quilted.iLeft_Hand = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx-3, cy+=7, 64, 64, iLeft_Leg,		sLeft_Leg,		true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// L. Leg
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.quilted.iLeft_Leg = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.LEFT_LEG)
								gameVars->player.active->inventory.equipped.quilted.iLeft_Leg = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx-3, cy+=7, 64, 64, iLeft_Foot,	sLeft_Foot,		true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// L. Foot
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.quilted.iLeft_Foot = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.LEFT_FOOT)
								gameVars->player.active->inventory.equipped.quilted.iLeft_Foot = gameVars->player.active->inventory.iSelected;
				}

				// Center Slots
				cx=(gameVars->font.vMax[0]/2)+26;
				cy=18;
				if(gameSys.checkIcon(		cx,		cy, 		64, 64, iTorso,			sTorso,				true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// Torso
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.quilted.iTorso = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.TORSO)
								gameVars->player.active->inventory.equipped.quilted.iTorso = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx, 	cy+=10, 64, 64, iLegs,			sLegs,				true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// Legs
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.quilted.iLegs = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.LEGS)
								gameVars->player.active->inventory.equipped.quilted.iLegs = gameVars->player.active->inventory.iSelected;
				}
			}
			break;
		case TAB10:
			{
				int iCount = 0;														// Current list count, used for scrolling
				int iP = 3;																// Padding
				int iW = (gameVars->font.vMax[0]/2)-(2*iP)+1;	// Useable page width
				cx=iP;
				cy=13;
				for(int i=0; i<gameVars->player.active->inventory.iCount; i++) {
					if (gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeFlag == GAME::ITEMS.TYPE.ARMOR) {
						if (gameVars->armor[gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeId].iType == GAME::ARMOR.TYPE.MAILLE) {
							//gameSys.drawWindow(	cx,	cy,	32, 5, false, true, inv_normal, inv_hover);

							// Delay printing of inventory until scrolled position
							if( iCount < iInvStart) {
									iCount++;
							}
							else if (iCount < iInvStart+10) {
								if (gameVars->player.active->inventory.iSelected == i) {
									if (gameSys.drawWindow(	cx,	cy,	iW, 5, true, true, inv_select, inv_hover_select, GAME::SYSTEM.WINSYS.DRAWMODE.SELECTION)&MOUSE_LEFT) { gameVars->player.active->inventory.iSelected = -1; };
								}
								else {
									if (gameSys.drawWindow(	cx,	cy,	iW, 5, true, true, inv_normal, inv_hover_normal)&MOUSE_LEFT) { gameVars->player.active->inventory.iSelected = i; };
								}

								// Overlay equipped icon
								if ( ( gameVars->player.active->inventory.equipped.maille.iHead == i ) ||
										 ( gameVars->player.active->inventory.equipped.maille.iTorso == i ) ||
										 ( gameVars->player.active->inventory.equipped.maille.iNeck == i ) ||
										 ( gameVars->player.active->inventory.equipped.maille.iLegs == i ) ||
										 ( gameVars->player.active->inventory.equipped.maille.iLeft_Arm == i ) ||
										 ( gameVars->player.active->inventory.equipped.maille.iLeft_Hand == i ) ||
										 ( gameVars->player.active->inventory.equipped.maille.iLeft_Leg == i ) ||
										 ( gameVars->player.active->inventory.equipped.maille.iLeft_Foot == i ) ||
										 ( gameVars->player.active->inventory.equipped.maille.iRight_Arm == i ) ||
										 ( gameVars->player.active->inventory.equipped.maille.iRight_Hand == i ) ||
										 ( gameVars->player.active->inventory.equipped.maille.iRight_Leg == i ) ||
										 ( gameVars->player.active->inventory.equipped.maille.iRight_Foot == i ) ) {

										gameSys.drawIcon(	cx+1,
																			cy+1,
																			32,
																			32,
																			gameVars->items[gameVars->player.active->inventory.list[i].id].iIcon,
																			gameVars->items[gameVars->player.active->inventory.list[i].id].sTex,
																			false,
																			true,
																			gameVars->color.green);

										gameSys.drawIcon(	cx+1, cy+1, 32, 32, 6,	"journal.png", 	false, true);		// R. Arm
								}
								else {
										gameSys.drawIcon(	cx+1,
																			cy+1,
																			32,
																			32,
																			gameVars->items[gameVars->player.active->inventory.list[i].id].iIcon,
																			gameVars->items[gameVars->player.active->inventory.list[i].id].sTex,
																			false,
																			true,
																			gameVars->color.journal.inventory_icon);
								}

								gameSys.drawText(cx+5, cy+1, gameVars->items[gameVars->player.active->inventory.list[i].id].name, inv_text);
								gameSys.drawText(cx+5, cy+2, gameVars->armor[gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeId].name, inv_text);
								gameSys.drawText(cx+5, cy+3, GAME::MATERIAL.NAMES[gameVars->items[gameVars->player.active->inventory.list[i].id].iMaterial], inv_text);
								gameSys.drawText(cx+(iW/2), cy+1, gameVars->items[gameVars->player.active->inventory.list[i].id].sDes, inv_des, 25, 3);

								cy+=4;
								iCount++;
							}
						}
					}
				}

				// RIGHT PAGE
				/*
				 * TODO: Item Hover details
				 */
				cx=(gameVars->font.vMax[0]/2)+7;
				cy=10;

				// Card and body
				{
					int iScale = 484;
					gameSys.drawIcon(cx, cy-3, iScale, iScale, 56, "cards.png", false, true, gameVars->color.journal.inventory_icon);
					gameSys.drawIcon(cx, cy-3, iScale, iScale, 25, "cards.png", false, true, gameVars->color.journal.inventory_icon);
				}

				// Temporary icon number
				int 		iHead				= 7,
								iTorso			= 7,
								iNeck				= 7,
								iLegs				= 7,
								iLeft_Arm		= 7,
								iLeft_Hand	= 7,
								iRight_Arm	= 7,
								iRight_Hand	= 7,
								iLeft_Leg		= 7,
								iLeft_Foot	= 7,
								iRight_Leg	= 7,
								iRight_Foot	= 7;

				// Temporary icon texture file
				string	sHead				= "journal.png",
								sTorso			= "journal.png",
								sNeck				= "journal.png",
								sLegs				= "journal.png",
								sLeft_Arm		= "journal.png",
								sLeft_Hand	= "journal.png",
								sRight_Arm	= "journal.png",
								sRight_Hand	= "journal.png",
								sLeft_Leg		= "journal.png",
								sLeft_Foot	= "journal.png",
								sRight_Leg	= "journal.png",
								sRight_Foot	= "journal.png";

				if(gameVars->player.active->inventory.equipped.maille.iHead != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.maille.iHead].id;
						iHead = gameVars->items[i].iIcon;
						sHead = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.maille.iTorso != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.maille.iTorso].id;
						iTorso = gameVars->items[i].iIcon;
						sTorso = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.maille.iNeck != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.maille.iNeck].id;
						iNeck = gameVars->items[i].iIcon;
						sNeck = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.maille.iLegs != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.maille.iLegs].id;
						iLegs = gameVars->items[i].iIcon;
						sLegs = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.maille.iLeft_Arm != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.maille.iLeft_Arm].id;
						iLeft_Arm = gameVars->items[i].iIcon;
						sLeft_Arm = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.maille.iLeft_Hand != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.maille.iLeft_Hand].id;
						iLeft_Hand = gameVars->items[i].iIcon;
						sLeft_Hand = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.maille.iLeft_Leg != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.maille.iLeft_Leg].id;
						iLeft_Leg = gameVars->items[i].iIcon;
						sLeft_Leg = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.maille.iLeft_Foot != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.maille.iLeft_Foot].id;
						iLeft_Foot = gameVars->items[i].iIcon;
						sLeft_Foot = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.maille.iRight_Arm != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.maille.iRight_Arm].id;
						iRight_Arm = gameVars->items[i].iIcon;
						sRight_Arm = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.maille.iRight_Hand != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.maille.iRight_Hand].id;
						iRight_Hand = gameVars->items[i].iIcon;
						sRight_Hand = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.maille.iRight_Leg != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.maille.iRight_Leg].id;
						iRight_Leg = gameVars->items[i].iIcon;
						sRight_Leg = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.maille.iRight_Foot != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.maille.iRight_Foot].id;
						iRight_Foot = gameVars->items[i].iIcon;
						sRight_Foot = gameVars->items[i].sTex;
				}

				// Left inventory slots
				cx=(gameVars->font.vMax[0]/2)+15;
				cy=10;
				if(gameSys.checkIcon(		cx+4, cy,    64, 64, iHead,				sHead, 				true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// Head
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.maille.iHead = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.HEAD)
								gameVars->player.active->inventory.equipped.maille.iHead = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx,   cy+=7, 64, 64, iRight_Arm,	sRight_Arm, 	true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// R. Arm
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.maille.iRight_Arm = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.RIGHT_ARM)
								gameVars->player.active->inventory.equipped.maille.iRight_Arm = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx,   cy+=7, 64, 64, iRight_Hand,	sRight_Hand,	true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// R. Hand
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.maille.iRight_Hand = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.RIGHT_HAND)
								gameVars->player.active->inventory.equipped.maille.iRight_Hand = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx+3, cy+=7, 64, 64, iRight_Leg,	sRight_Leg,		true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// R. Leg
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.maille.iRight_Leg = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.RIGHT_LEG)
								gameVars->player.active->inventory.equipped.maille.iRight_Leg = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx+3, cy+=7, 64, 64, iRight_Foot,	sRight_Foot,	true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// R. Foot
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.maille.iRight_Foot = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.RIGHT_FOOT)
								gameVars->player.active->inventory.equipped.maille.iRight_Foot = gameVars->player.active->inventory.iSelected;
				}

				// Right inventory slots
				cx=(gameVars->font.vMax[0]/2)+37;
				cy=10;
				if(gameSys.checkIcon(		cx-4, cy,    64, 64, iNeck,				sNeck,				true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// Neck
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.maille.iNeck = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.NECK)
								gameVars->player.active->inventory.equipped.maille.iNeck = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx,   cy+=7, 64, 64, iLeft_Arm,		sLeft_Arm,		true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// L. Arm
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.maille.iLeft_Arm = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.LEFT_ARM)
								gameVars->player.active->inventory.equipped.maille.iLeft_Arm = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx,   cy+=7, 64, 64, iLeft_Hand,	sLeft_Hand,		true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// L. Hand
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.maille.iLeft_Hand = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.LEFT_HAND)
								gameVars->player.active->inventory.equipped.maille.iLeft_Hand = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx-3, cy+=7, 64, 64, iLeft_Leg,		sLeft_Leg,		true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// L. Leg
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.maille.iLeft_Leg = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.LEFT_LEG)
								gameVars->player.active->inventory.equipped.maille.iLeft_Leg = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx-3, cy+=7, 64, 64, iLeft_Foot,	sLeft_Foot,		true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// L. Foot
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.maille.iLeft_Foot = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.LEFT_FOOT)
								gameVars->player.active->inventory.equipped.maille.iLeft_Foot = gameVars->player.active->inventory.iSelected;
				}

				// Center Slots
				cx=(gameVars->font.vMax[0]/2)+26;
				cy=18;
				if(gameSys.checkIcon(		cx,		cy, 		64, 64, iTorso,			sTorso,				true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// Torso
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.maille.iTorso = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.TORSO)
								gameVars->player.active->inventory.equipped.maille.iTorso = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx, 	cy+=10, 64, 64, iLegs,			sLegs,				true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// Legs
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.maille.iLegs = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.LEGS)
								gameVars->player.active->inventory.equipped.maille.iLegs = gameVars->player.active->inventory.iSelected;
				}
				}
			break;
		case TAB11:
			{
				int iCount = 0;																// Current list count, used for scrolling
				int iP = 3;																		// Padding
				int iW = (gameVars->font.vMax[0]/2)-(2*iP)+1;	// Useable page width
				cx=iP;
				cy=13;
				for(int i=0; i<gameVars->player.active->inventory.iCount; i++) {
					if (gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeFlag == GAME::ITEMS.TYPE.ARMOR) {
						if (gameVars->armor[gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeId].iType == GAME::ARMOR.TYPE.PLATE) {

							// Delay printing of inventory until scrolled position
							if( iCount < iInvStart) {
									iCount++;
							}
							else if (iCount < iInvStart+10) {
								if (gameVars->player.active->inventory.iSelected == i) {
									if (gameSys.drawWindow(	cx,	cy,	iW, 5, true, true, inv_select, inv_hover_select, GAME::SYSTEM.WINSYS.DRAWMODE.SELECTION)&MOUSE_LEFT) { gameVars->player.active->inventory.iSelected = -1; };
								}
								else {
									if (gameSys.drawWindow(	cx,	cy,	iW, 5, true, true, inv_normal, inv_hover_normal)&MOUSE_LEFT) { gameVars->player.active->inventory.iSelected = i; };
								}

								// Overlay equipped icon
								if ( ( gameVars->player.active->inventory.equipped.plate.iHead == i ) ||
										 ( gameVars->player.active->inventory.equipped.plate.iTorso == i ) ||
										 ( gameVars->player.active->inventory.equipped.plate.iNeck == i ) ||
										 ( gameVars->player.active->inventory.equipped.plate.iLegs == i ) ||
										 ( gameVars->player.active->inventory.equipped.plate.iLeft_Arm == i ) ||
										 ( gameVars->player.active->inventory.equipped.plate.iLeft_Hand == i ) ||
										 ( gameVars->player.active->inventory.equipped.plate.iLeft_Leg == i ) ||
										 ( gameVars->player.active->inventory.equipped.plate.iLeft_Foot == i ) ||
										 ( gameVars->player.active->inventory.equipped.plate.iRight_Arm == i ) ||
										 ( gameVars->player.active->inventory.equipped.plate.iRight_Hand == i ) ||
										 ( gameVars->player.active->inventory.equipped.plate.iRight_Leg == i ) ||
										 ( gameVars->player.active->inventory.equipped.plate.iRight_Foot == i ) ) {

										gameSys.drawIcon(	cx+1,
																			cy+1,
																			32,
																			32,
																			gameVars->items[gameVars->player.active->inventory.list[i].id].iIcon,
																			gameVars->items[gameVars->player.active->inventory.list[i].id].sTex,
																			false,
																			true,
																			gameVars->color.green);

										gameSys.drawIcon(	cx+1, cy+1, 32, 32, 6,	"journal.png", 	false, true);		// R. Arm
								}
								else {
										gameSys.drawIcon(	cx+1,
																			cy+1,
																			32,
																			32,
																			gameVars->items[gameVars->player.active->inventory.list[i].id].iIcon,
																			gameVars->items[gameVars->player.active->inventory.list[i].id].sTex,
																			false,
																			true,
																			gameVars->color.journal.inventory_icon);
								}

								gameSys.drawText(cx+5, cy+1, gameVars->items[gameVars->player.active->inventory.list[i].id].name, inv_text);
								gameSys.drawText(cx+5, cy+2, gameVars->armor[gameVars->items[gameVars->player.active->inventory.list[i].id].iTypeId].name, inv_text);
								gameSys.drawText(cx+5, cy+3, GAME::MATERIAL.NAMES[gameVars->items[gameVars->player.active->inventory.list[i].id].iMaterial], inv_text);
								gameSys.drawText(cx+(iW/2), cy+1, gameVars->items[gameVars->player.active->inventory.list[i].id].sDes, inv_des, 25, 3);

								cy+=4;
								iCount++;
							}
						}
					}
				}

				// RIGHT PAGE
				/*
				 * TODO: Item Hover details
				 */
				cx=(gameVars->font.vMax[0]/2)+7;
				cy=10;

				// Card and body
				{
					int iScale = 484;
					gameSys.drawIcon(cx, cy-3, iScale, iScale, 56, "cards.png", false, true, gameVars->color.journal.inventory_icon);
					gameSys.drawIcon(cx, cy-3, iScale, iScale, 25, "cards.png", false, true, gameVars->color.journal.inventory_icon);
				}

				// Temporary icon number
				int 		iHead				= 7,
								iTorso			= 7,
								iNeck				= 7,
								iLegs				= 7,
								iLeft_Arm		= 7,
								iLeft_Hand	= 7,
								iRight_Arm	= 7,
								iRight_Hand	= 7,
								iLeft_Leg		= 7,
								iLeft_Foot	= 7,
								iRight_Leg	= 7,
								iRight_Foot	= 7;

				// Temporary icon texture file
				string	sHead				= "journal.png",
								sTorso			= "journal.png",
								sNeck				= "journal.png",
								sLegs				= "journal.png",
								sLeft_Arm		= "journal.png",
								sLeft_Hand	= "journal.png",
								sRight_Arm	= "journal.png",
								sRight_Hand	= "journal.png",
								sLeft_Leg		= "journal.png",
								sLeft_Foot	= "journal.png",
								sRight_Leg	= "journal.png",
								sRight_Foot	= "journal.png";

				if(gameVars->player.active->inventory.equipped.plate.iHead != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.plate.iHead].id;
						iHead = gameVars->items[i].iIcon;
						sHead = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.plate.iTorso != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.plate.iTorso].id;
						iTorso = gameVars->items[i].iIcon;
						sTorso = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.plate.iNeck != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.plate.iNeck].id;
						iNeck = gameVars->items[i].iIcon;
						sNeck = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.plate.iLegs != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.plate.iLegs].id;
						iLegs = gameVars->items[i].iIcon;
						sLegs = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.plate.iLeft_Arm != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.plate.iLeft_Arm].id;
						iLeft_Arm = gameVars->items[i].iIcon;
						sLeft_Arm = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.plate.iLeft_Hand != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.plate.iLeft_Hand].id;
						iLeft_Hand = gameVars->items[i].iIcon;
						sLeft_Hand = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.plate.iLeft_Leg != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.plate.iLeft_Leg].id;
						iLeft_Leg = gameVars->items[i].iIcon;
						sLeft_Leg = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.plate.iLeft_Foot != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.plate.iLeft_Foot].id;
						iLeft_Foot = gameVars->items[i].iIcon;
						sLeft_Foot = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.plate.iRight_Arm != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.plate.iRight_Arm].id;
						iRight_Arm = gameVars->items[i].iIcon;
						sRight_Arm = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.plate.iRight_Hand != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.plate.iRight_Hand].id;
						iRight_Hand = gameVars->items[i].iIcon;
						sRight_Hand = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.plate.iRight_Leg != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.plate.iRight_Leg].id;
						iRight_Leg = gameVars->items[i].iIcon;
						sRight_Leg = gameVars->items[i].sTex;
				}
				if(gameVars->player.active->inventory.equipped.plate.iRight_Foot != -1) {
						int i = gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.plate.iRight_Foot].id;
						iRight_Foot = gameVars->items[i].iIcon;
						sRight_Foot = gameVars->items[i].sTex;
				}

				// Left inventory slots
				cx=(gameVars->font.vMax[0]/2)+15;
				cy=10;
				if(gameSys.checkIcon(		cx+4, cy,    64, 64, iHead,				sHead, 				true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// Head
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.plate.iHead = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.HEAD)
								gameVars->player.active->inventory.equipped.plate.iHead = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx,   cy+=7, 64, 64, iRight_Arm,	sRight_Arm, 	true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// R. Arm
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.plate.iRight_Arm = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.RIGHT_ARM)
								gameVars->player.active->inventory.equipped.plate.iRight_Arm = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx,   cy+=7, 64, 64, iRight_Hand,	sRight_Hand,	true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// R. Hand
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.plate.iRight_Hand = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.RIGHT_HAND)
								gameVars->player.active->inventory.equipped.plate.iRight_Hand = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx+3, cy+=7, 64, 64, iRight_Leg,	sRight_Leg,		true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// R. Leg
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.plate.iRight_Leg = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.RIGHT_LEG)
								gameVars->player.active->inventory.equipped.plate.iRight_Leg = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx+3, cy+=7, 64, 64, iRight_Foot,	sRight_Foot,	true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// R. Foot
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.plate.iRight_Foot = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.RIGHT_FOOT)
								gameVars->player.active->inventory.equipped.plate.iRight_Foot = gameVars->player.active->inventory.iSelected;
				}

				// Right inventory slots
				cx=(gameVars->font.vMax[0]/2)+37;
				cy=10;
				if(gameSys.checkIcon(		cx-4, cy,    64, 64, iNeck,				sNeck,				true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// Neck
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.plate.iNeck = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.NECK)
								gameVars->player.active->inventory.equipped.plate.iNeck = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx,   cy+=7, 64, 64, iLeft_Arm,		sLeft_Arm,		true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// L. Arm
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.plate.iLeft_Arm = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.LEFT_ARM)
								gameVars->player.active->inventory.equipped.plate.iLeft_Arm = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx,   cy+=7, 64, 64, iLeft_Hand,	sLeft_Hand,		true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// L. Hand
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.plate.iLeft_Hand = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.LEFT_HAND)
								gameVars->player.active->inventory.equipped.plate.iLeft_Hand = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx-3, cy+=7, 64, 64, iLeft_Leg,		sLeft_Leg,		true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// L. Leg
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.plate.iLeft_Leg = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.LEFT_LEG)
								gameVars->player.active->inventory.equipped.plate.iLeft_Leg = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx-3, cy+=7, 64, 64, iLeft_Foot,	sLeft_Foot,		true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// L. Foot
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.plate.iLeft_Foot = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.LEFT_FOOT)
								gameVars->player.active->inventory.equipped.plate.iLeft_Foot = gameVars->player.active->inventory.iSelected;
				}

				// Center Slots
				cx=(gameVars->font.vMax[0]/2)+26;
				cy=18;
				if(gameSys.checkIcon(		cx,		cy, 		64, 64, iTorso,			sTorso,				true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// Torso
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.plate.iTorso = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.TORSO)
								gameVars->player.active->inventory.equipped.plate.iTorso = gameVars->player.active->inventory.iSelected;
				}
				if(gameSys.checkIcon(		cx, 	cy+=10, 64, 64, iLegs,			sLegs,				true, true, gameVars->color.journal.inventory_icon)&MOUSE_LEFT) {		// Legs
						if(gameVars->player.active->inventory.iSelected == -1)
								gameVars->player.active->inventory.equipped.plate.iLegs = -1;
						else if(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.iSelected].id].iBodyPart == GAME::ITEMS.BODYPART.LEGS)
								gameVars->player.active->inventory.equipped.plate.iLegs = gameVars->player.active->inventory.iSelected;
				}
			}
			break;
		case TAB12:
			{
				cx=(gameVars->font.vMax[0]/2);
				cy=7;

				// Card and body
				int iScale = 600;
				gameSys.drawIcon(cx, cy, iScale, iScale, 56, "cards.png", false, true);

				// Calculate cumulative damage card
				int head  = gameVars->player.active->damage.limb.head.durability,
						torso = gameVars->player.active->damage.limb.torso.durability,
						larm  = gameVars->player.active->damage.limb.left_arm[0].durability,
						rarm  = gameVars->player.active->damage.limb.right_arm[0].durability,
						lhand = gameVars->player.active->damage.limb.left_arm[1].durability,
						rhand = gameVars->player.active->damage.limb.right_arm[1].durability,
						lleg  = gameVars->player.active->damage.limb.left_leg[0].durability,
						rleg  = gameVars->player.active->damage.limb.right_leg[0].durability,
						lfoot = gameVars->player.active->damage.limb.left_leg[1].durability,
						rfoot = gameVars->player.active->damage.limb.right_leg[1].durability;

				int	card_head		= 0,
						card_torso	= 0,
						card_larm		= 0,
						card_rarm		= 0,
						card_lhand	= 0,
						card_rhand	= 0,
						card_lleg		= 0,
						card_rleg		= 0,
						card_lfoot	= 0,
						card_rfoot	= 0,
						card_lleg_c = 63,
						card_rleg_c = 63;

						 if(head>=100)				 card_head = 0;
				else if(head>=66 && head <100)   card_head = 1;
				else if(head>=33 && head <66)    card_head = 2;
				else if(head>0   && head <33)    card_head = 3;
				else if(head==0) 			     card_head = 4;

						 if(torso>=100)				 card_torso = 5;
				else if(torso>=66 && torso <100) card_torso = 6;
				else if(torso>=33 && torso <66)  card_torso = 7;
				else if(torso>0   && torso <33)  card_torso = 8;
				else if(torso==0) 			     card_torso = 9;

						 if(larm>=100)				 card_larm = 10;
				else if(larm>=66 && larm <100)   card_larm = 11;
				else if(larm>=33 && larm <66)    card_larm = 12;
				else if(larm>0   && larm <33)    card_larm = 13;
				else if(larm==0) 			     card_larm = 14;

						 if(rarm>=100)				 card_rarm = 15;
				else if(rarm>=66 && rarm <100)   card_rarm = 16;
				else if(rarm>=33 && rarm <66)    card_rarm = 17;
				else if(rarm>0   && rarm <33)    card_rarm = 18;
				else if(rarm==0) 			     card_rarm = 19;

						 if(lhand>=100)				 card_lhand = 20;
				else if(lhand>=66 && lhand <100) card_lhand = 21;
				else if(lhand>=33 && lhand <66)  card_lhand = 22;
				else if(lhand>0   && lhand <33)  card_lhand = 23;
				else if(lhand==0) 			     card_lhand = 24;

						 if(rhand>=100)				 card_rhand = 25;
				else if(rhand>=66 && rhand <100) card_rhand = 26;
				else if(rhand>=33 && rhand <66)  card_rhand = 27;
				else if(rhand>0   && rhand <33)  card_rhand = 28;
				else if(rhand==0) 			     card_rhand = 29;

						 if(lleg>=100)				 card_lleg = 30;
				else if(lleg>=66 && lleg <100)   card_lleg = 31;
				else if(lleg>=33 && lleg <66)    card_lleg = 32;
				else if(lleg>0   && lleg <33)    card_lleg = 33;
				else if(lleg==0) 			     card_lleg = 34;

						 if(rleg>=100)				 card_rleg = 35;
				else if(rleg>=66 && rleg <100)   card_rleg = 36;
				else if(rleg>=33 && rleg <66)    card_rleg = 37;
				else if(rleg>0   && rleg <33)    card_rleg = 38;
				else if(rleg==0) 			     card_rleg = 39;

						 if(lfoot>=100)				 card_lfoot = 40;
				else if(lfoot>=66 && lfoot <100) card_lfoot = 41;
				else if(lfoot>=33 && lfoot <66)  card_lfoot = 42;
				else if(lfoot>0   && lfoot <33)  card_lfoot = 43;
				else if(lfoot==0) 			     card_lfoot = 44;

						 if(rfoot>=100)				 card_rfoot = 45;
				else if(rfoot>=66 && rfoot <100) card_rfoot = 46;
				else if(rfoot>=33 && rfoot <66)  card_rfoot = 47;
				else if(rfoot>0   && rfoot <33)  card_rfoot = 48;
				else if(rfoot==0) 			     card_rfoot = 49;

				if((lleg<100 || lfoot <100) && (rleg==100 && rfoot==100)) {
					card_rleg_c = 50;
				}

				if((rleg<100 || rfoot <100) && (lleg==100 && lfoot==100)) {
					card_lleg_c = 51;
				}

				//uint IconSys::draw(uint x, uint y, float w, float h, uint id, std::string sTex, bool bHighlight, bool textOffset) {
				//gameSys.checkIcon(cx, cy, iScale, iScale, 0, "cards.png", false, true, gameVars->color.white);

				gameSys.drawIcon(cx, cy, iScale, iScale, card_head,  "cumulative.png", false, true, gameVars->color.white);
				gameSys.drawIcon(cx, cy, iScale, iScale, card_torso, "cumulative.png", false, true, gameVars->color.white);
				gameSys.drawIcon(cx, cy, iScale, iScale, card_larm,  "cumulative.png", false, true, gameVars->color.white);
				gameSys.drawIcon(cx, cy, iScale, iScale, card_rarm,  "cumulative.png", false, true, gameVars->color.white);
				gameSys.drawIcon(cx, cy, iScale, iScale, card_lhand, "cumulative.png", false, true, gameVars->color.white);
				gameSys.drawIcon(cx, cy, iScale, iScale, card_rhand, "cumulative.png", false, true, gameVars->color.white);
				gameSys.drawIcon(cx, cy, iScale, iScale, card_lleg,  "cumulative.png", false, true, gameVars->color.white);
				gameSys.drawIcon(cx, cy, iScale, iScale, card_rleg,  "cumulative.png", false, true, gameVars->color.white);
				gameSys.drawIcon(cx, cy, iScale, iScale, card_lfoot, "cumulative.png", false, true, gameVars->color.white);
				gameSys.drawIcon(cx, cy, iScale, iScale, card_rfoot, "cumulative.png", false, true, gameVars->color.white);
			}
			break;
	}

	getInput();

	// Other final drawing routines
	update();

	//Flip the buffers
	//draw();
}

void RunJournal::update() {
	// Draw the custom cursor
	if(bShowMouse) {
			gameSys.drawSprite(gameVars->controls.mouse.x,gameVars->controls.mouse.y,64,100,"quill2.png",false,false);
	}
//	if (menuState.show_choice) {
//		Script::showChoice.run(gameVars);
//	}
}

void RunJournal::getInput() {
	//Event capturing
	SDL_PumpEvents();

	//Get relative mouse movement
	SDL_GetMouseState(&gameVars->controls.mouse.x, &gameVars->controls.mouse.y);
	gameVars->controls.mouse.relX=gameVars->controls.mouse.x-gameVars->screen.halfW;
	gameVars->controls.mouse.relY=gameVars->controls.mouse.y-gameVars->screen.halfH;
	//SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
	//if (gameVars->controls.mouse.lock) SDL_WarpMouse(gameVars->screen.halfW, gameVars->screen.halfH);
	//SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
	//if (gameVars->controls.mouse.hide) SDL_ShowCursor(SDL_DISABLE);
	//else SDL_ShowCursor(SDL_ENABLE);

	keyboard.event = SDL_GetKeyState(NULL);
	//if (gameVars->controls.keyboard.event[SDLK_ESCAPE]) gameVars->state.quit=true;

	/* Used as a mask when testing buttons in buttonstate
   Button 1:	Left mouse button
   Button 2:	Middle mouse button
   Button 3:	Right mouse button
   Button 4:	Mouse wheel up	 (may also be a real button)
   Button 5:	Mouse wheel down (may also be a real button)
 */
	if (gameVars->debug.lag) printf("GET MOUSE CLICK\n");
	if(SDL_GetMouseState(&gameVars->controls.mouse.x, &gameVars->controls.mouse.y)&SDL_BUTTON(1)) gameVars->controls.mouse.button.check[0]=true;
	else gameVars->controls.mouse.button.check[0]=false;
	gameSys.mouseSys.checkButton(0);

	if(SDL_GetMouseState(&gameVars->controls.mouse.x, &gameVars->controls.mouse.y)&SDL_BUTTON(3)) gameVars->controls.mouse.button.check[3]=true;
	else gameVars->controls.mouse.button.check[3]=false;
	gameSys.mouseSys.checkButton(3);

	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_MOUSEBUTTONDOWN:
				if ( event.button.button == SDL_BUTTON_WHEELUP )
				{
						//cout << "Mousewheel Up!" << endl;
						iInvStart -= 1;
						if(iInvStart<0) iInvStart = 0;
				}
				if ( event.button.button == SDL_BUTTON_WHEELDOWN )
				{
						//cout << "Mousewheel Down!" << endl;
						iInvStart += 1;
						if(iInvStart>gameVars->player.active->inventory.iCount) iInvStart = gameVars->player.active->inventory.iCount-1;
				}
		}
	}

	if(SDL_GetMouseState(&gameVars->controls.mouse.x, &gameVars->controls.mouse.y)&SDL_BUTTON(4)) gameVars->controls.mouse.button.check[4]=true;
	else gameVars->controls.mouse.button.check[4]=false;
	gameSys.mouseSys.checkButton(4);

	if(SDL_GetMouseState(&gameVars->controls.mouse.x, &gameVars->controls.mouse.y)&SDL_BUTTON(5)) gameVars->controls.mouse.button.check[5]=true;
	else gameVars->controls.mouse.button.check[5]=false;
	gameSys.mouseSys.checkButton(5);

	//Execute input commands
	//GameSys::Input::keyboard.repeat(gameVars, gameVars->controls.keyboard.event);
	keyboard.update();
	processInput();
}

void RunJournal::processInput() {

	if(gameVars->controls.mouse.button.check[3]) {
		gameVars->player.active->inventory.iSelected = -1;
	}

	if (keyboard.bKey[SDLK_ESCAPE])	{
		close();
	}
	if (keyboard.bKey[SDLK_LCTRL])		{ }
	if (keyboard.bKey[SDLK_LSHIFT])	{ }
	if (!keyboard.bKey[SDLK_LSHIFT] && !keyboard.bKey[SDLK_LCTRL]) { }

	//PLAYER MOVEMENT
	if (keyboard.bKey[SDLK_a]) { }
	if (keyboard.bKey[SDLK_d]) { }
	if (keyboard.bKey[SDLK_q]) { gameVars->state.quit=true; }
	if (keyboard.bKey[SDLK_e]) { }
	if (keyboard.bKey[SDLK_w]) { }
	if (keyboard.bKey[SDLK_s]) { }
	if (keyboard.bKey[SDLK_r]) { }
	if (keyboard.bKey[SDLK_f]) { }

	if (keyboard.bKey[SDLK_DELETE])	{ }

	if (keyboard.bKey[SDLK_INSERT])	{ }

	if (keyboard.bKey[SDLK_PAGEUP])	{
			iInvStart -= 10;
			if(iInvStart<0) iInvStart = 0;
	}
	if (keyboard.bKey[SDLK_PAGEDOWN])	{
			iInvStart += 10;
			if(iInvStart>gameVars->player.active->inventory.iCount) iInvStart = gameVars->player.active->inventory.iCount-10;
	}

	if (keyboard.bKey[SDLK_HOME])		{ }
	if (keyboard.bKey[SDLK_END])		{ }

	if (keyboard.bKey[SDLK_EQUALS])	{ }
	if (keyboard.bKey[SDLK_MINUS])		{ }

	if (keyboard.bKey[SDLK_BACKQUOTE]) { }

	if (keyboard.bKey[SDLK_F1])		{ }
	if (keyboard.bKey[SDLK_F2])		{ }
	if (keyboard.bKey[SDLK_F3])		{ }
	if (keyboard.bKey[SDLK_F4])		{ }
	if (keyboard.bKey[SDLK_F5])		{ }
	if (keyboard.bKey[SDLK_F6])		{ }
	if (keyboard.bKey[SDLK_F7])		{ }
	if (keyboard.bKey[SDLK_F8])		{ }
	if (keyboard.bKey[SDLK_F9])		{ }
	if (keyboard.bKey[SDLK_F10])		{ }
	if (keyboard.bKey[SDLK_F11])		{ }
	if (keyboard.bKey[SDLK_F12])		{ }

	if (gameVars->controls.mouse.relX<-gameVars->controls.mouse.deadX)	{ }
	if (gameVars->controls.mouse.relX>gameVars->controls.mouse.deadX)		{ }
	if (gameVars->controls.mouse.relY<-gameVars->controls.mouse.deadY)	{ }
	if (gameVars->controls.mouse.relY>gameVars->controls.mouse.deadY)		{ }
}

void RunJournal::draw() {
	SDL_GL_SwapBuffers();
}

void RunJournal::toggle(bool &myBool) {
	if (myBool) myBool=false;
	else myBool=true;
}

#endif /* RUNJOURNAL_H_ */
