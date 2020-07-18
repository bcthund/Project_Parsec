/*
 * runMenu.h
 *
 *  Created on: Sep 28, 2010
 *      Author: bcthund
 */

#ifndef RUNMENU_H_
#define RUNMENU_H_

class RunMenu {
	private:
		Keyboard keyboard;
		// Inventory highlighting
		bool bShowMouse;				// Draw the custom cursor
		Vector4f	color_tomes_normal	= {1.0, 1.0, 1.0, 1.0},
					color_tomes_hidden	= {1.0, 1.0, 1.0, 0.0},
					color_tomes_hover	= {2.0, 2.0, 2.0, 1.0};

	protected:
		void toggle(bool &myBool);
		void getInput();
		void processInput();
		void update();
		void draw();
		void exit(bool bSet);

	public:
		enum INTENTSTATES { EI_INIT,
							EI_STANCE, EI_DEFENSE, EI_MOVEMENT, EI_INTENT, EI_SKILL, EI_ITEMS, EI_WEAPON,
							EI_LAST
		};
		int eS, eI;
		bool init();
		bool load();
		void reset();
		void set();
		void run(bool bWorld);
		void run(bool bOperations, bool bStatus, bool bIntent, bool bActionIcon, bool bWorld);
		RunMenu();
} Menu;

//RunMenu * Menu = new(RunMenu);

RunMenu::RunMenu() {
	eS = 0;
	eI = 0;
	bShowMouse = true;

	//CopyVector4f(gameVars->color.transparent, inv_normal);
	//CopyVector4f(gameVars->color.tan, holster_text);
	//CopyVector4f(gameVars->color.grey, inv_hover_normal);
	//CopyVector4f(gameVars->color.yellow, inv_select);
	//CopyVector4f(gameVars->color.orange, inv_hover_select);
	//CopyVector4f(gameVars->color.white, inv_text);

	keyboard.calc();
}

bool RunMenu::init() {
	return true;
}

bool RunMenu::load() {
	return true;
}

void RunMenu::reset() {
	gameVars->menu.bOperations	= 1;
	gameVars->menu.bIntent		= 0;
	gameVars->menu.bStatus		= 1;
	gameVars->menu.bActionIcon	= 1;
	eS = GAME::MENU.STATE.INIT;
	eI = EI_INIT;
}

void RunMenu::exit(bool bSet=false) {
	if (bSet) {
		gameVars->player.active->status.iState = eS;
		gameVars->player.active->status.iExec = eS;
	}
	eS = GAME::MENU.STATE.INIT;
	eI = EI_INIT;
	gameVars->state.menu=false;
	ToggleMouse(false);
}

void RunMenu::set() {
	gameVars->player.active->status.iState = eS;
	eS = GAME::MENU.STATE.INIT;
	eI = EI_INIT;
}

void RunMenu::run(bool bOperations, bool bIntent, bool bStatus, bool bActionIcon, bool bWorld=false) {
	gameVars->menu.bOperations=bOperations;
	gameVars->menu.bIntent=bIntent;
	gameVars->menu.bStatus=bStatus;
	gameVars->menu.bActionIcon=bActionIcon;
	run(bWorld);
}

void RunMenu::run(bool bWorld=false) {
	//Set default colors and presets
	Vector4f vFont, vVal, vNI, vTitle,
			 textNormal		= { 0.71,	0.48,	0.24,	1.0 },
			 textHover		= { 1.0,	0.68,	0,		1.0 },
			 textHover2		= { 1.0,	0.00,	0.00,	1.0 },
			 textSelected	= { 1.0,	0.52,	0,		1.0 },
			 textDeselected	= { 0.4,	0.37,	0.31,	0.7 },
			 backNormal		= { 0.45,	0.45,	0.45,	1.0 },
			 backHover		= { 0.55,	0.55,	0.55,	1.0 },
			 backSelected	= { 0.75,	0.75,	0.75,	1.0 },
			 backDeselected	= { 0.25,	0.25,	0.25,	0.7 };
//	CopyVector4f(gameVars->color.tan ,vFont);
//	CopyVector4f(gameVars->color.grey ,vVal);
//	CopyVector4f(gameVars->color.red ,vNI);
//	CopyVector4f(gameVars->color.yellow ,vTitle);

	vFont = gameVars->color.tan;
	vVal = gameVars->color.grey;
	vNI = gameVars->color.red;
	vTitle = gameVars->color.yellow;



	//Vector4f tint        = {0.54, 0.45, 0.25, 1.0};

	//Orange: 255, 132, 0 (1.0, 0.518, 0.0)
	Vector4f tint        = {1.00, 0.518, 0.00, 1.0};
	Vector4f selected    = {1.00, 1.00, 1.00, 1.0};
	Vector4f deselected  = {0.80, 0.70, 0.70, 0.8};
	//Vector4f selected    = {0.80, 1.00, 0.80, 1.0};
	//Vector4f deselected  = {0.60, 0.50, 0.50, 0.8};
	//Vector4f selected    = {1.0, 1.0, 1.0, 1.0};
	//Vector4f deselected  = {1.0, 1.0, 1.0, 1.0};

	Vector2f vC = {((-gameVars->font.screenCoords[0]-32)/gameVars->font.vSize[0]), ((gameVars->font.screenCoords[1]-32)/gameVars->font.vSize[1])};
	//Vector2f vC = {-gameVars->font.screenCoords[0], gameVars->font.screenCoords[1]};

	Vector2f vF = {gameVars->font.vSize[0], gameVars->font.vSize[1]};

	//int * iExec  = &gameVars->player.active->status.iExec;
	//int * iState = &gameVars->player.active->status.iState;

	struct SSET {
		int		b;		//Base position
		uint	x,		//x pos
				y,		//y pos
				oa,		//a offset
				ob;		//b offset
		float	w,		//width
				h,		//height
				sa,		//a scale
				sb,		//b scale
				sc,		//b scale
				sd;		//b scale
	} sSet;

	if(!bWorld) {
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glClear( gameVars->screen.clear );

		/*
		 * Draw the world as it last was
		 */
		if (gameVars->state.battle) {
			//Battle.draw(*gameVars->player.active);
			Battle.draw();
			//if (Battle.iPlayer==PLAYER) Battle.draw(*gameVars, gameVars->player.sheet, Battle.npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[0]);
			//else if (Battle.iPlayer==ENEMY1) Battle.draw(*gameVars, Battle.npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[0], gameVars->player.sheet);
			//else if (Battle.iPlayer==ENEMY2) Battle.draw(*gameVars, Battle.npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[1], gameVars->player.sheet);
			//else if (Battle.iPlayer==ENEMY3) Battle.draw(*gameVars, Battle.npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[2], gameVars->player.sheet);
			//else if (Battle.iPlayer==ENEMY4) Battle.draw(*gameVars, Battle.npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[3], gameVars->player.sheet);
		}
		else {
			world.Update(false);		//Calls for a screen draw of the world, includes transformations
		}
	}
	//gameSys.winSys.draw			(0,  iTabH-1, gameVars->font.vMax[0]+1, gameVars->font.vMax[1]-5, tint);
	// Vertical Divider
	//gameSys.winSys.drawVLine	((gameVars->font.vMax[0]/2),  iTabH, gameVars->font.vMax[1]-7, tint);
	//gameSys.winSys.drawSingle	((gameVars->font.vMax[0]/2),  iTabH-1, 1,  1, 2, tint);
	//gameSys.winSys.drawSingle	((gameVars->font.vMax[0]/2),  gameVars->font.vMax[1]-3, 1,  1, 7, tint);
	//Page 1: Horizontal divider
	//gameSys.winSys.drawHLine	(1,  10, (gameVars->font.vMax[0]/2)-1, tint);
	//gameSys.winSys.drawSingle	(0, 10, 1,  1, 10, tint);
	//gameSys.winSys.drawSingle	((gameVars->font.vMax[0]/2), 10, 1,  1, 11, tint);

	//gameSys.spriteSys.draw(0,3,gameVars->screen.w-(gameVars->font.vSize[1]),gameVars->screen.h-(10*gameVars->font.vSize[2]),"journal.png", false, true);

	//Center
	//Left
	//Right
	//Top
	//Bottom

	//if (gameVars->menu.bIntent || gameVars->menu.bOperations) {
	//	SDL_ShowCursor(SDL_ENABLE);
	//}

	//Initial Settings
	sSet.b=0;
	sSet.x = vC[0];
	sSet.y = vC[1];
	sSet.oa = -4;
	sSet.ob = 7;
	sSet.w = vF[0];
	sSet.h = vF[1];
	sSet.sa = 6;
	sSet.sb = 3;


	gameSys.checkIcon(1, 1, 64, 64, 52, "wm_icons_subdued.png", true, true, color_tomes_hidden, color_tomes_normal);
	gameSys.checkIcon(gameVars->font.vMax[0]-8, 1, 64, 64, 53, "wm_icons_subdued.png", true, true, color_tomes_hidden, color_tomes_normal);

	gameSys.checkIcon(1, gameVars->font.vMax[1]-7, 64, 64, 54, "wm_icons_subdued.png", true, true, color_tomes_hidden, color_tomes_normal);
	gameSys.checkIcon(gameVars->font.vMax[0]-8, gameVars->font.vMax[1]-7, 64, 64, 55, "wm_icons_subdued.png", true, true, color_tomes_hidden, color_tomes_normal);

	//if (gameVars->state.battle==true) {
	if (gameVars->menu.bOperations) {

		if (gameSys.checkIcon(sSet.x+sSet.oa, sSet.y+sSet.oa, sSet.w*sSet.sb, sSet.h*sSet.sb, 5, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) { gameVars->state.book=S_JOURNAL; }		//Journal
		if (gameSys.checkIcon(sSet.x+sSet.ob, sSet.y+sSet.oa, sSet.w*sSet.sb, sSet.h*sSet.sb, 6, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) { gameVars->state.book=S_BATTLESCROLL; }	//Battle Scroll
		if (gameSys.checkIcon(sSet.x+sSet.oa, sSet.y+sSet.ob, sSet.w*sSet.sb, sSet.h*sSet.sb, 7, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) { gameVars->state.book=S_GRIMOIRE; }	//Grimoire
		//if (gameSys.checkIcon(sSet.x+sSet.ob, sSet.y+sSet.ob, sSet.w*sSet.sb, sSet.h*sSet.sb, 8, "wm_icons_subdued.png", true, true)) { eS=GAME::MENU.STATE.INIT; }	//Extra
		if (gameSys.checkIcon(sSet.x+sSet.ob, sSet.y+sSet.ob, sSet.w*sSet.sb, sSet.h*sSet.sb, 8, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) { gameVars->player.active->status.iState=GAME::MENU.STATE.SKIP; exit(false); }	//Extra

		if (eS==GAME::MENU.STATE.INIT) {
			if (gameVars->state.world && !gameVars->state.battle) {
				/*
				 * CENTER
				 */
				gameSys.drawIcon(sSet.x,         sSet.y,		 sSet.w*sSet.sa, sSet.h*sSet.sa, gameVars->player.active->init.face, "faces.png", true, true);
				gameSys.drawIcon(sSet.x+sSet.oa, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 1, "wm_icons_subdued.png", false, true, deselected);
				gameSys.drawIcon(sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 2, "wm_icons_subdued.png", false, true, deselected);
				gameSys.drawIcon(sSet.x,         sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 3, "wm_icons_subdued.png", false, true, deselected);
				if (gameSys.checkIcon(sSet.x,     sSet.y+sSet.ob, sSet.w*sSet.sa, sSet.h*sSet.sb, 4, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) {
					gameVars->menu.bOperations=false;
					gameVars->menu.bIntent=true;
					gameVars->menu.bStatus=true;
				}	//INTENTION
			}
			else {
				/*
				 * CENTER
				 */
				//if (gameSys.checkIcon(sSet.x,         sSet.y,		 sSet.w*sSet.sa, sSet.h*sSet.sa, gameVars->player.active->init.face, "faces.png", true, true)) { eS=GAME::MENU.STATE.SKIP; exit(true); };

				if (gameSys.checkIcon(sSet.x,         sSet.y,		 sSet.w*sSet.sa, sSet.h*sSet.sa, gameVars->player.active->init.face, "faces.png", true, true)&MOUSE_LEFT) {
					if (gameVars->player.active->status.iIntent==GAME::MENU.INTENT.STANCE)		{ gameVars->player.active->status.iState=GAME::MENU.INTENT.STANCE; exit(false); }
					if (gameVars->player.active->status.iIntent==GAME::MENU.INTENT.CAST_SPELL)	{ gameVars->player.active->status.iState=GAME::MENU.INTENT.CAST_SPELL; exit(false); }
					if (gameVars->player.active->status.iIntent==GAME::MENU.INTENT.MELEE) 		{ gameVars->player.active->status.iState=GAME::MENU.INTENT.MELEE; exit(false); }
				}

				if (gameSys.checkIcon(sSet.x+sSet.oa, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 1, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) eS=GAME::MENU.CAST.INIT;
				if (gameSys.checkIcon(sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 2, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) eS=GAME::MENU.ENGAGE.INIT;
				if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 3, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) eS=GAME::MENU.MOVE.INIT;
				if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.ob, sSet.w*sSet.sa, sSet.h*sSet.sb, 4, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) {
					gameVars->menu.bOperations=false;
					gameVars->menu.bIntent=true;
					gameVars->menu.bStatus=true;
				}	//INTENTION
			}
		}

		/*
		 * ENGAGE MENU STRUCTURE
		 */
		if (eS==GAME::MENU.ENGAGE.INIT || eS==GAME::MENU.ENGAGE.CHOP.INIT || eS==GAME::MENU.ENGAGE.SWING.INIT || eS==GAME::MENU.ENGAGE.THRUST.INIT) {
			// CENTER
			gameSys.drawIcon(sSet.x,        	 sSet.y,             sSet.w*sSet.sa, sSet.h*sSet.sa, gameVars->player.active->init.face, "faces.png", false, true);
			gameSys.drawIcon(sSet.x+sSet.oa,     sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 1, "wm_icons_subdued.png", false, true, deselected);
			if (gameSys.checkIcon(sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 2, "wm_icons_highlighted.png",   true, true, selected)&MOUSE_LEFT) eS=GAME::MENU.STATE.INIT;
			gameSys.drawIcon(sSet.x,             sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 3, "wm_icons_subdued.png", false, true, deselected);
			gameSys.drawIcon(sSet.x,             sSet.y+sSet.ob, sSet.w*sSet.sa, sSet.h*sSet.sb, 4, "wm_icons_subdued.png", false, true, deselected);
		}


		if (eS==GAME::MENU.ENGAGE.INIT) {
			// ENGAGE
			sSet.b=13;	sSet.x = vC[0]+sSet.b;	sSet.y = vC[1]+2;	sSet.sa = 2;	sSet.sb = 3;
			gameSys.drawIcon(		sSet.x,			sSet.y,         sSet.w*sSet.sa, sSet.h*sSet.sa, 9, "wm_icons_subdued.png", true, true);
			sSet.x = vC[0]+sSet.b-2;	sSet.y = vC[1];	sSet.sa = 6;
			if (gameSys.checkIcon(	sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 10, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) eS=GAME::MENU.ENGAGE.SWING.INIT;
			if (gameSys.checkIcon(	sSet.x,         sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 11, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) eS=GAME::MENU.ENGAGE.CHOP.INIT;
			if (gameSys.checkIcon(	sSet.x,         sSet.y+sSet.ob, sSet.w*sSet.sa, sSet.h*sSet.sb, 12, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) eS=GAME::MENU.ENGAGE.THRUST.INIT;
		}

		if ( eS==GAME::MENU.ENGAGE.CHOP.INIT ||
			 eS==GAME::MENU.ENGAGE.SWING.INIT ||
			 eS==GAME::MENU.ENGAGE.THRUST.INIT ) {
			//ENGAGE
			sSet.b=13;	sSet.x = vC[0]+sSet.b;	sSet.y = vC[1]+2;	sSet.sa = 2;	sSet.sb = 3;
			gameSys.drawIcon(sSet.x,             sSet.y,         sSet.w*sSet.sa, sSet.h*sSet.sa, 9, "wm_icons_subdued.png", true, true);
			sSet.x = vC[0]+sSet.b-2;	sSet.y = vC[1];	sSet.sa = 6;

			if (eS==GAME::MENU.ENGAGE.CHOP.INIT) {
				if (gameSys.checkIcon(sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 10, "wm_icons_subdued.png", 	true, true, deselected)&MOUSE_LEFT) eS=GAME::MENU.ENGAGE.SWING.INIT;
				if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 11, "wm_icons_highlighted.png", true, true, selected)&MOUSE_LEFT) eS=GAME::MENU.ENGAGE.CHOP.INIT;
				if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.ob, sSet.w*sSet.sa, sSet.h*sSet.sb, 12, "wm_icons_subdued.png", true, true, deselected)&MOUSE_LEFT) eS=GAME::MENU.ENGAGE.THRUST.INIT;
			}
			else if (eS==GAME::MENU.ENGAGE.SWING.INIT) {
				if (gameSys.checkIcon(sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 10, "wm_icons_highlighted.png", true, true, selected)&MOUSE_LEFT) eS=GAME::MENU.ENGAGE.SWING.INIT;
				if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 11, "wm_icons_subdued.png", true, true, deselected)&MOUSE_LEFT) eS=GAME::MENU.ENGAGE.CHOP.INIT;
				if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.ob, sSet.w*sSet.sa, sSet.h*sSet.sb, 12, "wm_icons_subdued.png", true, true, deselected)&MOUSE_LEFT) eS=GAME::MENU.ENGAGE.THRUST.INIT;
			}
			else if (eS==GAME::MENU.ENGAGE.THRUST.INIT) {
				if (gameSys.checkIcon(sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 10, "wm_icons_subdued.png", true, true, deselected)&MOUSE_LEFT) eS=GAME::MENU.ENGAGE.SWING.INIT;
				if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 11, "wm_icons_subdued.png", true, true, deselected)&MOUSE_LEFT) eS=GAME::MENU.ENGAGE.CHOP.INIT;
				if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.ob, sSet.w*sSet.sa, sSet.h*sSet.sb, 12, "wm_icons_highlighted.png",  true, true, selected)&MOUSE_LEFT) eS=GAME::MENU.ENGAGE.THRUST.INIT;
			}

			//ATTACK (HIGH/MID/LOW)
			sSet.b=24;	sSet.x = vC[0]+sSet.b;	sSet.y = vC[1]+2;	sSet.sa = 2;	sSet.sb = 3;
			gameSys.drawIcon(sSet.x,             sSet.y,         sSet.w*sSet.sa, sSet.h*sSet.sa, 13, "wm_icons_subdued.png", true, true);
			sSet.x = vC[0]+sSet.b-2;	sSet.y = vC[1];	sSet.sa = 6;
			if (eS==GAME::MENU.ENGAGE.CHOP.INIT) {
				if (gameSys.checkIcon(sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 14, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) { eS=GAME::MENU.ENGAGE.CHOP.MID;  exit(true); }
				if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 15, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) { eS=GAME::MENU.ENGAGE.CHOP.HIGH; exit(true); }
				if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.ob, sSet.w*sSet.sa, sSet.h*sSet.sb, 16, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) { eS=GAME::MENU.ENGAGE.CHOP.LOW;  exit(true); }
			}
			else if (eS==GAME::MENU.ENGAGE.SWING.INIT) {
				if (gameSys.checkIcon(sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 14, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) { eS=GAME::MENU.ENGAGE.SWING.MID;  exit(true); }
				if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 15, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) { eS=GAME::MENU.ENGAGE.SWING.HIGH; exit(true); }
				if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.ob, sSet.w*sSet.sa, sSet.h*sSet.sb, 16, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) { eS=GAME::MENU.ENGAGE.SWING.LOW;  exit(true); }
			}
			else if (eS==GAME::MENU.ENGAGE.THRUST.INIT) {
				if (gameSys.checkIcon(sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 14, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) { eS=GAME::MENU.ENGAGE.THRUST.MID;  exit(true); }
				if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 15, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) { eS=GAME::MENU.ENGAGE.THRUST.HIGH; exit(true); }
				if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.ob, sSet.w*sSet.sa, sSet.h*sSet.sb, 16, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) { eS=GAME::MENU.ENGAGE.THRUST.LOW;  exit(true); }
			}

		}

		// CAST MENU STRUCTURE
		if ( eS==GAME::MENU.CAST.INIT ||
			 eS==GAME::MENU.CAST.MAGICAL.INIT ||
			 eS==GAME::MENU.CAST.MAGICAL.WAND ||
			 eS==GAME::MENU.CAST.MAGICAL.IMBUE ||
			 eS==GAME::MENU.CAST.MAGICAL.STAFF ||
			 eS==GAME::MENU.CAST.ALCHEMY.INIT ||
			 eS==GAME::MENU.CAST.ALCHEMY.APPLY ||
			 eS==GAME::MENU.CAST.ALCHEMY.CONSUME ||
			 eS==GAME::MENU.CAST.ALCHEMY.TOSS ) {
			//CENTER
			gameSys.drawIcon(sSet.x,         sSet.y,             sSet.w*sSet.sa, sSet.h*sSet.sa, gameVars->player.active->init.face, "faces.png", false, true);
			if (gameSys.checkIcon(sSet.x+sSet.oa, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 1, "wm_icons_highlighted.png",   true, true, selected)&MOUSE_LEFT) eS=GAME::MENU.STATE.INIT;
			gameSys.drawIcon(sSet.x+sSet.ob,     sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 2, "wm_icons_subdued.png", false, true, deselected);
			gameSys.drawIcon(sSet.x,             sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 3, "wm_icons_subdued.png", false, true, deselected);
			gameSys.drawIcon(sSet.x,             sSet.y+sSet.ob, sSet.w*sSet.sa, sSet.h*sSet.sb, 4, "wm_icons_subdued.png", false, true, deselected);
		}

		if (eS==GAME::MENU.CAST.INIT) {
			//CAST
			sSet.b=-9;	sSet.x = vC[0]+sSet.b;	sSet.y = vC[1]+2;	sSet.sa = 2;	sSet.sb = 3;
			gameSys.drawIcon(sSet.x,             sSet.y,         sSet.w*sSet.sa, sSet.h*sSet.sa, 17, "wm_icons_subdued.png", true, true);
			sSet.x = vC[0]+sSet.b-2;	sSet.y = vC[1];	sSet.sa = 6;
			if (gameSys.checkIcon(sSet.x+sSet.oa, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 18, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) { eS=GAME::MENU.CAST.SPELL; exit(true); }	//Spell
			if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 19, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) eS=GAME::MENU.CAST.MAGICAL.INIT;
			if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.ob, sSet.w*sSet.sa, sSet.h*sSet.sb, 20, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) eS=GAME::MENU.CAST.ALCHEMY.INIT;
		}

		if ( eS==GAME::MENU.CAST.MAGICAL.INIT ||
			 eS==GAME::MENU.CAST.MAGICAL.WAND ||
			 eS==GAME::MENU.CAST.MAGICAL.IMBUE ||
			 eS==GAME::MENU.CAST.MAGICAL.STAFF ) {
			//CAST
			sSet.b=-9;	sSet.x = vC[0]+sSet.b;	sSet.y = vC[1]+2;	sSet.sa = 2;	sSet.sb = 3;
			gameSys.drawIcon(sSet.x,             sSet.y,         sSet.w*sSet.sa, sSet.h*sSet.sa, 17, "wm_icons_subdued.png", false, true, deselected);
			sSet.x = vC[0]+sSet.b-2;	sSet.y = vC[1];	sSet.sa = 6;
			gameSys.drawIcon(sSet.x+sSet.oa,     sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 18, "wm_icons_subdued.png", false, true, deselected);
			if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 19, "wm_icons_highlighted.png",   true, true, selected)&MOUSE_LEFT) eS=GAME::MENU.CAST.INIT;
			gameSys.drawIcon(sSet.x,             sSet.y+sSet.ob, sSet.w*sSet.sa, sSet.h*sSet.sb, 20, "wm_icons_subdued.png", false, true, deselected);

			//MAGICAL
			sSet.b=-9;	sSet.x = vC[0]+sSet.b;	sSet.y = vC[1]-9;	sSet.sa = 2;	sSet.sb = 3;
			gameSys.drawIcon(sSet.x,             sSet.y,         sSet.w*sSet.sa, sSet.h*sSet.sa, 21, "wm_icons_subdued.png", true, true);
			sSet.x = vC[0]+sSet.b-2;	sSet.y = vC[1]-11;	sSet.sa = 6;

			if (eS==GAME::MENU.CAST.MAGICAL.WAND) {
				gameSys.drawIcon(sSet.x+sSet.oa, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 22, "wm_icons_highlighted.png", true, true, selected);	//WAND
				if (gameSys.checkIcon(sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 23, "wm_icons_subdued.png", true, true, deselected)&MOUSE_LEFT) eS=GAME::MENU.CAST.MAGICAL.IMBUE;	//IMBUE
				if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 24, "wm_icons_subdued.png", true, true, deselected)&MOUSE_LEFT) eS=GAME::MENU.CAST.MAGICAL.STAFF;	//STAFF

				short int suiX = -30;
				short int suiY = 23;
				Vector4f vBack = {0.45, 0.45, 0.45, 1.0};
				Vector4f vTitle = {1.0, 0.68, 0, 1.0};
				gameSys.drawWindow(		sSet.x-suiX,	sSet.y+10,	suiY, 13, false, true, vBack);
				gameSys.drawText(		sSet.x-suiX+1,	sSet.y+11,	"Wand", vTitle);
				gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y+12,	suiY-2, vBack);
				if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y+13,	"Weaken")&MOUSE_LEFT);
				if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y+14,	"Free Action")&MOUSE_LEFT);
				if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y+15,	"Free Bowel Action")&MOUSE_LEFT);
				if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y+16,	"Quick Action")&MOUSE_LEFT);
				if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y+17,	"Open")&MOUSE_LEFT);
				if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y+18,	"Banish")&MOUSE_LEFT);
				if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y+19,	"Leetch")&MOUSE_LEFT);
				if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y+20,	"Dispel Curse")&MOUSE_LEFT);
				if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y+21,	"Sleep")&MOUSE_LEFT);
			}
			else if (eS==GAME::MENU.CAST.MAGICAL.IMBUE) {
				if (gameSys.checkIcon(sSet.x+sSet.oa, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 22, "wm_icons_subdued.png", true, true, deselected)&MOUSE_LEFT) eS=GAME::MENU.CAST.MAGICAL.WAND;	//WAND
				gameSys.drawIcon(sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 23, "wm_icons_highlighted.png", true, true, selected);	//IMBUE
				if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 24, "wm_icons_subdued.png", true, true, deselected)&MOUSE_LEFT) eS=GAME::MENU.CAST.MAGICAL.STAFF;	//STAFF

				short int suiX = -30;
				short int suiY = 23;
				Vector4f vBack = {0.45, 0.45, 0.45, 1.0};
				Vector4f vTitle = {1.0, 0.68, 0, 1.0};
				gameSys.drawWindow(				sSet.x-suiX,	sSet.y+10,	suiY, 9, false, true, vBack);
				gameSys.drawText(				sSet.x-suiX+1,	sSet.y+11,	"Imbued", vTitle);
				gameSys.winSys.drawHLine(			sSet.x-suiX+1,	sSet.y+12,	suiY-2, vBack);
				if (gameSys.menuSys.draw(sSet.x-suiX+1,	sSet.y+13,	"Topaz of Charm")&MOUSE_LEFT);
				if (gameSys.menuSys.draw(sSet.x-suiX+1,	sSet.y+14,	"Quartz of Lightening")&MOUSE_LEFT);
				if (gameSys.menuSys.draw(sSet.x-suiX+1,	sSet.y+15,	"Jade of Footstop")&MOUSE_LEFT);
				if (gameSys.menuSys.draw(sSet.x-suiX+1,	sSet.y+16,	"Emerald of hate")&MOUSE_LEFT);
				if (gameSys.menuSys.draw(sSet.x-suiX+1,	sSet.y+17,	"Tin ingot of Strength")&MOUSE_LEFT);
			}
			else if (eS==GAME::MENU.CAST.MAGICAL.STAFF) {
				if (gameSys.checkIcon(sSet.x+sSet.oa, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 22, "wm_icons_subdued.png", true, true, deselected)&MOUSE_LEFT) eS=GAME::MENU.CAST.MAGICAL.WAND;	//WAND
				if (gameSys.checkIcon(sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 23, "wm_icons_subdued.png", true, true, deselected)&MOUSE_LEFT) eS=GAME::MENU.CAST.MAGICAL.IMBUE;	//IMBUE
				gameSys.drawIcon(sSet.x,         sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 24, "wm_icons_highlighted.png", true, true, selected);	//STAFF

				short int suiX = -30;
				short int suiY = 23;
				Vector4f vBack = {0.45, 0.45, 0.45, 1.0};
				Vector4f vTitle = {1.0, 0.68, 0, 1.0};
				gameSys.drawWindow(				sSet.x-suiX,	sSet.y+10,	suiY, 5, false, true, vBack);
				gameSys.drawText(				sSet.x-suiX+1,	sSet.y+11,	"Staff", vTitle);
				gameSys.winSys.drawHLine(			sSet.x-suiX+1,	sSet.y+12,	suiY-2, vBack);
				if (gameSys.menuSys.draw(sSet.x-suiX+1,	sSet.y+13,	"Sceptor of Domination")&MOUSE_LEFT);
			}
			else {
				if (gameSys.checkIcon(sSet.x+sSet.oa, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 22, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) eS=GAME::MENU.CAST.MAGICAL.WAND;	//WAND
				if (gameSys.checkIcon(sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 23, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) eS=GAME::MENU.CAST.MAGICAL.IMBUE;	//IMBUE
				if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 24, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) eS=GAME::MENU.CAST.MAGICAL.STAFF;	//STAFF
			}
		}

		if ( eS==GAME::MENU.CAST.ALCHEMY.INIT ||
			 eS==GAME::MENU.CAST.ALCHEMY.TOSS ||
			 eS==GAME::MENU.CAST.ALCHEMY.APPLY ||
			 eS==GAME::MENU.CAST.ALCHEMY.CONSUME ) {
			//CAST
			sSet.b=-9;	sSet.x = vC[0]+sSet.b;	sSet.y = vC[1]+2;	sSet.sa = 2;	sSet.sb = 3;
			gameSys.drawIcon(sSet.x,             sSet.y,         sSet.w*sSet.sa, sSet.h*sSet.sa, 17, "wm_icons_subdued.png", false, true, deselected);
			sSet.x = vC[0]+sSet.b-2;	sSet.y = vC[1];	sSet.sa = 6;
			gameSys.drawIcon(sSet.x+sSet.oa,     sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 18, "wm_icons_subdued.png", false, true, deselected);
			gameSys.drawIcon(sSet.x,             sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 19, "wm_icons_subdued.png", false, true, deselected);
			if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.ob, sSet.w*sSet.sa, sSet.h*sSet.sb, 20, "wm_icons_highlighted.png",   true, true, selected)&MOUSE_LEFT) eS=GAME::MENU.CAST.INIT;

			//ALCHEMY
			sSet.b=-9;	sSet.x = vC[0]+sSet.b;	sSet.y = vC[1]+13;	sSet.sa = 2;	sSet.sb = 3;
			gameSys.drawIcon(sSet.x,             sSet.y,         sSet.w*sSet.sa, sSet.h*sSet.sa, 25, "wm_icons_subdued.png", true, true);
			sSet.x = vC[0]+sSet.b-2;	sSet.y = vC[1]+11;	sSet.sa = 6;

			if (eS==GAME::MENU.CAST.ALCHEMY.TOSS) {
				gameSys.drawIcon(sSet.x+sSet.oa, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 26, "wm_icons_highlighted.png", true, true, selected);		//TOSS
				if (gameSys.checkIcon(sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 27, "wm_icons_subdued.png", true, true, deselected)&MOUSE_LEFT) eS=GAME::MENU.CAST.ALCHEMY.APPLY;		//APPLY
				if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.ob, sSet.w*sSet.sa, sSet.h*sSet.sb, 28, "wm_icons_subdued.png", true, true, deselected)&MOUSE_LEFT) eS=GAME::MENU.CAST.ALCHEMY.CONSUME;	//CONSUME

				short int suiX = -30;
				short int suiY = 23;
				Vector4f vBack = {0.45, 0.45, 0.45, 1.0};
				Vector4f vTitle = {1.0, 0.68, 0, 1.0};
				gameSys.drawWindow(				sSet.x-suiX,	sSet.y-11,	suiY, 7, false, true, vBack);
				gameSys.drawText(				sSet.x-suiX+1,	sSet.y-10,	"Toss", vTitle);
				gameSys.winSys.drawHLine(			sSet.x-suiX+1,	sSet.y-9,	suiY-2, vBack);
				if (gameSys.menuSys.draw(sSet.x-suiX+1,	sSet.y-8,	"Nade of Pepper Powder")&MOUSE_LEFT);
				if (gameSys.menuSys.draw(sSet.x-suiX+1,	sSet.y-7,	"Nade of Lightening")&MOUSE_LEFT);
				if (gameSys.menuSys.draw(sSet.x-suiX+1,	sSet.y-6,	"Nade of Thunder")&MOUSE_LEFT);
			}
			else if (eS==GAME::MENU.CAST.ALCHEMY.APPLY) {
				if (gameSys.checkIcon(sSet.x+sSet.oa, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 26, "wm_icons_subdued.png", true, true, deselected)&MOUSE_LEFT) eS=GAME::MENU.CAST.ALCHEMY.TOSS;		//TOSS
				gameSys.drawIcon(sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 27, "wm_icons_highlighted.png", true, true, selected);		//APPLY
				if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.ob, sSet.w*sSet.sa, sSet.h*sSet.sb, 28, "wm_icons_subdued.png", true, true, deselected)&MOUSE_LEFT) eS=GAME::MENU.CAST.ALCHEMY.CONSUME;	//CONSUME

				short int suiX = -30;
				short int suiY = 23;
				Vector4f vBack = {0.45, 0.45, 0.45, 1.0};
				Vector4f vTitle = {1.0, 0.68, 0, 1.0};
				gameSys.drawWindow(				sSet.x-suiX,	sSet.y-11,	suiY, 7, false, true, vBack);
				gameSys.drawText(				sSet.x-suiX+1,	sSet.y-10,	"Apply", vTitle);
				gameSys.winSys.drawHLine(			sSet.x-suiX+1,	sSet.y-9,	suiY-2, vBack);
				if (gameSys.menuSys.draw(sSet.x-suiX+1,	sSet.y-8,	"Toxic Oil")&MOUSE_LEFT);
				if (gameSys.menuSys.draw(sSet.x-suiX+1,	sSet.y-7,	"Healing Salve")&MOUSE_LEFT);
				if (gameSys.menuSys.draw(sSet.x-suiX+1,	sSet.y-6,	"Spray Paint")&MOUSE_LEFT);
			}
			else if (eS==GAME::MENU.CAST.ALCHEMY.CONSUME) {
				if (gameSys.checkIcon(sSet.x+sSet.oa, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 26, "wm_icons_subdued.png", true, true, deselected)&MOUSE_LEFT) eS=GAME::MENU.CAST.ALCHEMY.TOSS;		//TOSS
				if (gameSys.checkIcon(sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 27, "wm_icons_subdued.png", true, true, deselected)&MOUSE_LEFT) eS=GAME::MENU.CAST.ALCHEMY.APPLY;		//APPLY
				gameSys.drawIcon(sSet.x,         sSet.y+sSet.ob, sSet.w*sSet.sa, sSet.h*sSet.sb, 28, "wm_icons_highlighted.png", true, true, selected);	//CONSUME

				short int suiX = -30;
				short int suiY = 23;
				Vector4f vBack = {0.45, 0.45, 0.45, 1.0};
				Vector4f vTitle = {1.0, 0.68, 0, 1.0};
				gameSys.drawWindow(				sSet.x-suiX,	sSet.y-14,	suiY, 10, false, true, vBack);
				gameSys.drawText(				sSet.x-suiX+1,	sSet.y-13,	"Consume", vTitle);
				gameSys.winSys.drawHLine(			sSet.x-suiX+1,	sSet.y-12,	suiY-2, vBack);
				if (gameSys.menuSys.draw(sSet.x-suiX+1,	sSet.y-11,	"Nash")&MOUSE_LEFT);
				if (gameSys.menuSys.draw(sSet.x-suiX+1,	sSet.y-10,	"Watermelon")&MOUSE_LEFT);
				if (gameSys.menuSys.draw(sSet.x-suiX+1,	sSet.y-9,	"Root of Histue")&MOUSE_LEFT);
				if (gameSys.menuSys.draw(sSet.x-suiX+1,	sSet.y-8,	"Potion of soothing")&MOUSE_LEFT);
				if (gameSys.menuSys.draw(sSet.x-suiX+1,	sSet.y-7,	"Potion of cure disease")&MOUSE_LEFT);
				if (gameSys.menuSys.draw(sSet.x-suiX+1,	sSet.y-6,	"Potion of cure poison")&MOUSE_LEFT);
			}
			else
			{
				if (gameSys.checkIcon(sSet.x+sSet.oa, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 26, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) eS=GAME::MENU.CAST.ALCHEMY.TOSS;		//TOSS
				if (gameSys.checkIcon(sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 27, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) eS=GAME::MENU.CAST.ALCHEMY.APPLY;		//APPLY
				if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.ob, sSet.w*sSet.sa, sSet.h*sSet.sb, 28, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) eS=GAME::MENU.CAST.ALCHEMY.CONSUME;	//CONSUME
			}
		}

		//MOVE MENU STRUCTURE
		if (eS==GAME::MENU.MOVE.INIT || eS==GAME::MENU.MOVE.STANCE.INIT) {
			//CENTER
			gameSys.drawIcon(sSet.x,         sSet.y,             sSet.w*sSet.sa, sSet.h*sSet.sa, gameVars->player.active->init.face, "faces.png", false, true);
			gameSys.drawIcon(sSet.x+sSet.oa,     sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 1, "wm_icons_subdued.png", false, true, deselected);
			gameSys.drawIcon(sSet.x+sSet.ob,     sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 2, "wm_icons_subdued.png", false, true, deselected);
			if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 3, "wm_icons_highlighted.png",   true, true, selected)&MOUSE_LEFT) eS=GAME::MENU.STATE.INIT;
			gameSys.drawIcon(sSet.x,             sSet.y+sSet.ob, sSet.w*sSet.sa, sSet.h*sSet.sb, 4, "wm_icons_subdued.png", false, true, deselected);
		}

		if (eS==GAME::MENU.MOVE.INIT) {
			//MOVE
			sSet.b=2;	sSet.x = vC[0]+sSet.b;	sSet.y = vC[1]-9;	sSet.sa = 2;	sSet.sb = 3;
			gameSys.drawIcon(sSet.x,             sSet.y,         sSet.w*sSet.sa, sSet.h*sSet.sa, 29, "wm_icons_subdued.png", true, true);
			sSet.x = vC[0]+sSet.b-2;	sSet.y = vC[1]-11;	sSet.sa = 6;
			if (gameSys.checkIcon(sSet.x+sSet.oa, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 30, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) {
				gameVars->player.active->status.move.iSpeed = GAME::MENU.MOVE.RUN;
				eS=GAME::MENU.MOVE.RUN;
				exit(true);
			}
			if (gameSys.checkIcon(sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 31, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) {
				eS=GAME::MENU.MOVE.STANCE.INIT;
			}
			if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 32, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) {
				gameVars->player.active->status.move.iSpeed = GAME::MENU.MOVE.WALK;
				eS=GAME::MENU.MOVE.WALK;
				exit(true);
			}
		}

		if (eS==GAME::MENU.MOVE.STANCE.INIT) {
			//MOVE
			sSet.b=2;	sSet.x = vC[0]+sSet.b;	sSet.y = vC[1]-9;	sSet.sa = 2;	sSet.sb = 3;
			gameSys.drawIcon(sSet.x,             sSet.y,         sSet.w*sSet.sa, sSet.h*sSet.sa, 29, "wm_icons_subdued.png", false, true, deselected);
			sSet.x = vC[0]+sSet.b-2;	sSet.y = vC[1]-11;	sSet.sa = 6;
			gameSys.drawIcon(sSet.x+sSet.oa,     sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 30, "wm_icons_subdued.png", false, true, deselected);
			if (gameSys.checkIcon(sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 31, "wm_icons_highlighted.png",   true, true, selected)&MOUSE_LEFT) eS=GAME::MENU.MOVE.INIT;
			gameSys.drawIcon(sSet.x,             sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 32, "wm_icons_subdued.png", false, true, deselected);

			//STANCE
			sSet.b=17;	sSet.x = vC[0]+sSet.b;	sSet.y = vC[1]-9;	sSet.sa = 2;	sSet.sb = 3;
			gameSys.drawIcon(sSet.x,         sSet.y,             sSet.w*sSet.sa, sSet.h*sSet.sa, 33, "wm_icons_subdued.png", true, true);
			sSet.x = vC[0]+sSet.b-2;	sSet.y = vC[1]-11;	sSet.sa = 6;
			if (gameSys.checkIcon(sSet.x+sSet.ob, sSet.y,         sSet.w*sSet.sb, sSet.h*sSet.sa, 34, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) { eS=GAME::MENU.MOVE.STANCE.KNEEL; exit(true); }	//KNEEL
			if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.oa, sSet.w*sSet.sa, sSet.h*sSet.sb, 35, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) { eS=GAME::MENU.MOVE.STANCE.STAND; exit(true); }	//STAND
			if (gameSys.checkIcon(sSet.x,         sSet.y+sSet.ob, sSet.w*sSet.sa, sSet.h*sSet.sb, 36, "wm_icons_subdued.png", true, true)&MOUSE_LEFT) { eS=GAME::MENU.MOVE.STANCE.PRONE; exit(true); }	//PRONE
		}
	}

	/* ==========================================================
	 *
	 *  INTENTIONS WINDOW/BAR
	 *
	 */
	//if(gameVars->state.battle==false || eS==ES_INTENTION) {
	if (gameVars->menu.bIntent) {
		sSet.x = vC[0]-3;
		//sSet.y = vC[1]+22;
		sSet.y = gameVars->font.vMax[1]-6;
		sSet.w = vF[0];
		sSet.h = vF[1];
		sSet.sc = 12;
		sSet.sd = 2;

		//Spacers
		//gameSys.drawIcon(sSet.x-30,      sSet.y-2,       sSet.w*sSet.sd, sSet.h*sSet.sd, 51, "wm_icons_subdued.png", false, true);
		//gameSys.drawIcon(sSet.x-16,      sSet.y-2,       sSet.w*sSet.sd, sSet.h*sSet.sd, 51, "wm_icons_subdued.png", false, true);
		//gameSys.drawIcon(sSet.x-2,       sSet.y-2,       sSet.w*sSet.sd, sSet.h*sSet.sd, 51, "wm_icons_subdued.png", false, true);
		//gameSys.drawIcon(sSet.x+12,      sSet.y-2,       sSet.w*sSet.sd, sSet.h*sSet.sd, 51, "wm_icons_subdued.png", false, true);
		//gameSys.drawIcon(sSet.x+26,      sSet.y-2,       sSet.w*sSet.sd, sSet.h*sSet.sd, 51, "wm_icons_subdued.png", false, true);
		//gameSys.drawIcon(sSet.x+40,      sSet.y-2,       sSet.w*sSet.sd, sSet.h*sSet.sd, 51, "wm_icons_subdued.png", false, true);

		//Buttons


		Vector4f vBack = { backNormal[0], backNormal[1], backNormal[2], backNormal[3] };
		Vector4f vText = { textNormal[0], textNormal[1], textNormal[2], textNormal[3] };

		if(eI!=EI_INIT) {
			vBack[0] = backDeselected[0];
			vBack[1] = backDeselected[1];
			vBack[2] = backDeselected[2];
			vBack[3] = backDeselected[3];

			vText[0] = textDeselected[0];
			vText[1] = textDeselected[1];
			vText[2] = textDeselected[2];
			vText[3] = textDeselected[3];
		}


		if (eI==EI_STANCE) {	if (gameSys.drawTextWindow(	sSet.x-42,	sSet.y,	13, 3,	"Stance",	true, true, backSelected,	textSelected,	backHover,	textHover2)&MOUSE_LEFT) eI=EI_INIT; }
		else { 					if (gameSys.drawTextWindow(	sSet.x-42,	sSet.y,	13, 3,	"Stance",	true, true, vBack,			vText,			backHover,	textHover)&MOUSE_LEFT) eI=EI_STANCE; }

		if (eI==EI_DEFENSE) {	if (gameSys.drawTextWindow(	sSet.x-28,	sSet.y,	13, 3,	"Defense",	true, true, backSelected,	textSelected,	backHover,	textHover2)&MOUSE_LEFT) eI=EI_INIT; }
		else {					if (gameSys.drawTextWindow(	sSet.x-28,	sSet.y,	13, 3,	"Defense",	true, true, vBack,			vText,			backHover,	textHover)&MOUSE_LEFT) eI=EI_DEFENSE; }

		if (eI==EI_MOVEMENT) {	if (gameSys.drawTextWindow(	sSet.x-14,	sSet.y,	13, 3,	"Movement",	true, true, backSelected,	textSelected,	backHover,	textHover2)&MOUSE_LEFT) eI=EI_INIT; }
		else {					if (gameSys.drawTextWindow(	sSet.x-14,	sSet.y,	13, 3,	"Movement",	true, true, vBack,			vText,			backHover,	textHover)&MOUSE_LEFT) eI=EI_MOVEMENT; }

		//if (eI==EI_INTENT);
		//else {  }

		if (eI==EI_SKILL) {		if (gameSys.drawTextWindow(	sSet.x+14,	sSet.y,	13, 3,	"Skills",	true, true, backSelected,	textSelected,	backHover,	textHover2)&MOUSE_LEFT) eI=EI_INIT; }
		else {					if (gameSys.drawTextWindow(	sSet.x+14,	sSet.y,	13, 3,	"Skills",	true, true, vBack,			vText,			backHover,	textHover)&MOUSE_LEFT) eI=EI_SKILL; }

		if (eI==EI_ITEMS) {		if (gameSys.drawTextWindow(	sSet.x+28,	sSet.y,	13, 3,	"Items",	true, true, backSelected,	textSelected,	backHover,	textHover2)&MOUSE_LEFT) eI=EI_INIT; }
		else {					if (gameSys.drawTextWindow(	sSet.x+28,	sSet.y,	13, 3,	"Items",	true, true, vBack,			vText,			backHover,	textHover)&MOUSE_LEFT) eI=EI_ITEMS; }

		if (eI==EI_WEAPON) {	if (gameSys.drawTextWindow(	sSet.x+42,	sSet.y,	13, 3,	"Weapons",	true, true, backSelected,	textSelected,	backHover,	textHover2)&MOUSE_LEFT) eI=EI_INIT; }
		else {					if (gameSys.drawTextWindow(	sSet.x+42,	sSet.y,	13, 3,	"Weapons",	true, true, vBack,			vText,			backHover,	textHover)&MOUSE_LEFT) eI=EI_WEAPON; }


		if (eI==EI_INIT) {
			//if (gameSys.drawTextWindow(		sSet.x-42,	sSet.y+4,	13, 3,	"Stance",	true, true, backNormal, textNormal, backHover, textHover) == MOUSE_LEFT) eI=EI_STANCE;
			//if (gameSys.drawTextWindow(		sSet.x-28,	sSet.y+4,	13, 3,	"Defense",	true, true, backNormal, textNormal, backHover, textHover) == MOUSE_LEFT) eI=EI_DEFENSE;
			//if (gameSys.drawTextWindow(		sSet.x-14,	sSet.y+4,	13, 3,	"Movement",	true, true, backNormal, textNormal, backHover, textHover) == MOUSE_LEFT) eI=EI_MOVEMENT;
			//if (gameSys.drawTextWindow(		sSet.x+14,	sSet.y+4,	13, 3,	"Skills",	true, true, backNormal, textNormal, backHover, textHover) == MOUSE_LEFT) eI=EI_SKILL;
			//if (gameSys.drawTextWindow(		sSet.x+28,	sSet.y+4,	13, 3,	"Items",	true, true, backNormal, textNormal, backHover, textHover) == MOUSE_LEFT) eI=EI_ITEMS;
			//if (gameSys.drawTextWindow(		sSet.x+42,	sSet.y+4,	13, 3,	"Weapons",	true, true, backNormal, textNormal, backHover, textHover) == MOUSE_LEFT) eI=EI_WEAPON;
		}

		if (eI==EI_STANCE) {
			//if (gameSys.drawTextWindow(		sSet.x-42,	sSet.y,	13, 3,	"Stance",	true, true, backSelected,   textSelected,   backHover, textHover2) == MOUSE_LEFT) eI=EI_STANCE;
			//if (gameSys.drawTextWindow(		sSet.x-28,	sSet.y,	13, 3,	"Defense",	true, true, backDeselected, textDeselected, backHover, textHover) == MOUSE_LEFT)  eI=EI_DEFENSE;
			//if (gameSys.drawTextWindow(		sSet.x-14,	sSet.y,	13, 3,	"Movement",	true, true, backDeselected, textDeselected, backHover, textHover) == MOUSE_LEFT)  eI=EI_MOVEMENT;
			//if (gameSys.drawTextWindow(		sSet.x+14,	sSet.y,	13, 3,	"Skills",	true, true, backDeselected, textDeselected, backHover, textHover) == MOUSE_LEFT)  eI=EI_SKILL;
			//if (gameSys.drawTextWindow(		sSet.x+28,	sSet.y,	13, 3,	"Items",	true, true, backDeselected, textDeselected, backHover, textHover) == MOUSE_LEFT)  eI=EI_ITEMS;
			//if (gameSys.drawTextWindow(		sSet.x+42,	sSet.y,	13, 3,	"Weapons",	true, true, backDeselected, textDeselected, backHover, textHover) == MOUSE_LEFT)  eI=EI_WEAPON;

			short int suiX = 42;
			Vector4f vBack = {0.45, 0.45, 0.45, 1.0};
			Vector4f vTitle = {1.0, 0.68, 0, 1.0};
			gameSys.drawWindow(			sSet.x-suiX,	sSet.y-12,	13, 12, false, true, vBack);
			gameSys.drawText(			sSet.x-suiX+1,	sSet.y-11,	"Standard", vTitle);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-10,	11, vBack);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-9,	"Stand")&MOUSE_LEFT) gameVars->player.active->status.move.iStance = GAME::MENU.MOVE.STANCE.STAND;
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-8,	"Kneel")&MOUSE_LEFT) gameVars->player.active->status.move.iStance = GAME::MENU.MOVE.STANCE.KNEEL;
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-7,	"Prone")&MOUSE_LEFT) gameVars->player.active->status.move.iStance = GAME::MENU.MOVE.STANCE.PRONE;
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-6,	11, vBack);
			gameSys.drawText(			sSet.x-suiX+1,	sSet.y-5,	"Special", vTitle);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-4,	11, vBack);
		}

		if (eI==EI_DEFENSE) {
			//if (gameSys.drawTextWindow(		sSet.x-42,	sSet.y,	13, 3,	"Stance",	true, true, backDeselected, textDeselected, backHover, textHover) == MOUSE_LEFT) eI=EI_STANCE;
			//if (gameSys.drawTextWindow(		sSet.x-28,	sSet.y,	13, 3,	"Defense",	true, true, backSelected,   textSelected,   backHover, textHover2) == MOUSE_LEFT)  eI=EI_DEFENSE;
			//if (gameSys.drawTextWindow(		sSet.x-14,	sSet.y,	13, 3,	"Movement",	true, true, backDeselected, textDeselected, backHover, textHover) == MOUSE_LEFT)  eI=EI_MOVEMENT;
			//if (gameSys.drawTextWindow(		sSet.x+14,	sSet.y,	13, 3,	"Skills",	true, true, backDeselected, textDeselected, backHover, textHover) == MOUSE_LEFT)  eI=EI_SKILL;
			//if (gameSys.drawTextWindow(		sSet.x+28,	sSet.y,	13, 3,	"Items",	true, true, backDeselected, textDeselected, backHover, textHover) == MOUSE_LEFT)  eI=EI_ITEMS;
			//if (gameSys.drawTextWindow(		sSet.x+42,	sSet.y,	13, 3,	"Weapons",	true, true, backDeselected, textDeselected, backHover, textHover) == MOUSE_LEFT)  eI=EI_WEAPON;

			short int suiX = 28;
			Vector4f vBack = {0.45, 0.45, 0.45, 1.0};
			Vector4f vTitle = {1.0, 0.68, 0, 1.0};
			gameSys.drawWindow(			sSet.x-suiX,	sSet.y-8,	13, 8, false, true, vBack);
			gameSys.drawText(			sSet.x-suiX+1,	sSet.y-7,	"Type", vTitle);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-6,	11, vBack);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-5,	"Dodge")&MOUSE_LEFT) gameVars->player.active->status.defense.iMode = GAME::MENU.DEFENSE.DODGE;
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-4,	"Deflect")&MOUSE_LEFT) gameVars->player.active->status.defense.iMode = GAME::MENU.DEFENSE.DEFLECT;
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-3,	"Block")&MOUSE_LEFT) gameVars->player.active->status.defense.iMode = GAME::MENU.DEFENSE.BLOCK;
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-2,	"Glance")&MOUSE_LEFT) gameVars->player.active->status.defense.iMode = GAME::MENU.DEFENSE.NONE;
		}

		if (eI==EI_MOVEMENT) {
			//if (gameSys.drawTextWindow(		sSet.x-42,	sSet.y,	13, 3,	"Stance",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_STANCE;
			//if (gameSys.drawTextWindow(		sSet.x-28,	sSet.y,	13, 3,	"Defense",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_DEFENSE;
			//if (gameSys.drawTextWindow(		sSet.x-14,	sSet.y,	13, 3,	"Movement",	true, true, backSelected,	textSelected,	backHover,	textHover2) == MOUSE_LEFT)	eI=EI_MOVEMENT;
			//if (gameSys.drawTextWindow(		sSet.x+14,	sSet.y,	13, 3,	"Skills",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_SKILL;
			//if (gameSys.drawTextWindow(		sSet.x+28,	sSet.y,	13, 3,	"Items",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_ITEMS;
			//if (gameSys.drawTextWindow(		sSet.x+42,	sSet.y,	13, 3,	"Weapons",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_WEAPON;

			short int suiX = 14;
			Vector4f vBack = {0.45, 0.45, 0.45, 1.0};
			Vector4f vTitle = {1.0, 0.68, 0, 1.0};
			gameSys.drawWindow(			sSet.x-suiX,	sSet.y-11,	13, 11, false, true, vBack);
			gameSys.drawText(			sSet.x-suiX+1,	sSet.y-10,	"Standard", vTitle);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-9,	11, vBack);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-8,	"Walk")&MOUSE_LEFT) gameVars->player.active->status.move.iSpeed = GAME::MENU.MOVE.WALK;
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-7,	"Run")&MOUSE_LEFT) gameVars->player.active->status.move.iSpeed = GAME::MENU.MOVE.RUN;
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-6,	11, vBack);
			gameSys.drawText(			sSet.x-suiX+1,	sSet.y-5,	"Recourse", vTitle);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-4,	11, vBack);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-3,	"Sneak")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-2,	"Crawl")&MOUSE_LEFT);
		}

		if (eI==EI_INTENT) {
			//if (gameSys.drawTextWindow(		sSet.x-42,	sSet.y,	13, 3,	"Stance",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_STANCE;
			//if (gameSys.drawTextWindow(		sSet.x-28,	sSet.y,	13, 3,	"Defense",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_DEFENSE;
			//if (gameSys.drawTextWindow(		sSet.x-14,	sSet.y,	13, 3,	"Movement",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_MOVEMENT;
			//if (gameSys.drawTextWindow(		sSet.x+14,	sSet.y,	13, 3,	"Skills",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_SKILL;
			//if (gameSys.drawTextWindow(		sSet.x+28,	sSet.y,	13, 3,	"Items",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_ITEMS;
			//if (gameSys.drawTextWindow(		sSet.x+42,	sSet.y,	13, 3,	"Weapons",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_WEAPON;

			short int suiX = 1;
			short int suiY = 15;
			Vector4f vBack = {0.45, 0.45, 0.45, 1.0};
			Vector4f vTitle = {1.0, 0.68, 0, 1.0};
			gameSys.drawWindow(			sSet.x-suiX,	sSet.y-39,	suiY, 39, false, true, vBack);
			gameSys.drawText(			sSet.x-suiX+1,	sSet.y-38,	"Neutral", vTitle);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-37,	suiY-2, vBack);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-36,	"Observe")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-35,	"Touch")&MOUSE_LEFT);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-34,	suiY-2, vBack);
			gameSys.drawText(			sSet.x-suiX+1,	sSet.y-33,	"General", vTitle);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-32,	suiY-2, vBack);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-31,	"Loiter")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-30,	"Sit")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-29,	"Sleep")&MOUSE_LEFT);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-28,	suiY-2, vBack);
			gameSys.drawText(			sSet.x-suiX+1,	sSet.y-27,	"Action", vTitle);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-26,	suiY-2, vBack);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-25,	"Archery")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-24,	"Throw Weapon")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-23,	"Toss Grenade")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-22,	"Apply")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-21,	"Consume")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-20,	"Cast Spell")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-19,	"Cast Staff")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-18,	"Cast Wand")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-17,	"Cast Imbued")&MOUSE_LEFT);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-16,	suiY-2, vBack);
			gameSys.drawText(			sSet.x-suiX+1,	sSet.y-15,	"Engagement", vTitle);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-14,	suiY-2, vBack);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-13,	"Wield")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-12,	"Threaten")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-11,	"Fight")&MOUSE_LEFT);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-10,	suiY-2, vBack);
			gameSys.drawText(			sSet.x-suiX+1,	sSet.y-9,	"Negation", vTitle);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-8,	suiY-2, vBack);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-7,	"Climb")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-6,	"Spy")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-5,	"Pickpocket")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-4,	"Pick lock")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-3,	"Poison")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-2,	"Assasinate")&MOUSE_LEFT);
		}

		if (eI==EI_SKILL) {
			//if (gameSys.drawTextWindow(		sSet.x-42,	sSet.y,	13, 3,	"Stance",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_STANCE;
			//if (gameSys.drawTextWindow(		sSet.x-28,	sSet.y,	13, 3,	"Defense",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_DEFENSE;
			//if (gameSys.drawTextWindow(		sSet.x-14,	sSet.y,	13, 3,	"Movement",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_MOVEMENT;
			//if (gameSys.drawTextWindow(		sSet.x+14,	sSet.y,	13, 3,	"Skills",	true, true, backSelected,	textSelected,	backHover,	textHover2) == MOUSE_LEFT)	eI=EI_SKILL;
			//if (gameSys.drawTextWindow(		sSet.x+28,	sSet.y,	13, 3,	"Items",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_ITEMS;
			//if (gameSys.drawTextWindow(		sSet.x+42,	sSet.y,	13, 3,	"Weapons",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_WEAPON;

			short int suiX = -14;
			short int suiY = 28;
			Vector4f vBack = {0.45, 0.45, 0.45, 1.0};
			Vector4f vTitle = {1.0, 0.68, 0, 1.0};
			gameSys.drawWindow(			sSet.x-suiX,	sSet.y-31,	suiY, 31, false, true, vBack);
			gameSys.drawText(			sSet.x-suiX+1,	sSet.y-30,	"Skill", vTitle);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-29,	suiY-2, vBack);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-28,	"*Dim")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-27,	"*Sing")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-26,	"*Fists of Punching")&MOUSE_LEFT);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-25,	suiY-2, vBack);
			gameSys.drawText(			sSet.x-suiX+1,	sSet.y-24,	"Ability", vTitle);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-23,	suiY-2, vBack);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-22,	"*Berserk")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-21,	"*Shout")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-20,	"*Read")&MOUSE_LEFT);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-19,	suiY-2, vBack);
			gameSys.drawText(			sSet.x-suiX+1,	sSet.y-18,	"Talent", vTitle);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-17,	suiY-2, vBack);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-16,	"*Canine Surprise")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-15,	"*Eye Stare")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-14,	"*Poop")&MOUSE_LEFT);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-13,	suiY-2, vBack);
			gameSys.drawText(			sSet.x-suiX+1,	sSet.y-12,	"Perk", vTitle);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-11,	suiY-2, vBack);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-10,	"*Enric's Torso Splitter")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-9,	"*Impressation")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-8,	"*Dual Wield")&MOUSE_LEFT);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-7,	suiY-2, vBack);
			gameSys.drawText(			sSet.x-suiX+1,	sSet.y-6,	"Lernids", vTitle);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-5,	suiY-2, vBack);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-4,	"*Oration")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-3,	"*Quiet Movement")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-2,	"*Chest Thump")&MOUSE_LEFT);
		}

		if (eI==EI_ITEMS) {
			//if (gameSys.drawTextWindow(		sSet.x-42,	sSet.y,	13, 3,	"Stance",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_STANCE;
			//if (gameSys.drawTextWindow(		sSet.x-28,	sSet.y,	13, 3,	"Defense",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_DEFENSE;
			//if (gameSys.drawTextWindow(		sSet.x-14,	sSet.y,	13, 3,	"Movement",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_MOVEMENT;
			//if (gameSys.drawTextWindow(		sSet.x+14,	sSet.y,	13, 3,	"Skills",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_SKILL;
			//if (gameSys.drawTextWindow(		sSet.x+28,	sSet.y,	13, 3,	"Items",	true, true, backSelected,	textSelected,	backHover,	textHover2) == MOUSE_LEFT)	eI=EI_ITEMS;
			//if (gameSys.drawTextWindow(		sSet.x+42,	sSet.y,	13, 3,	"Weapons",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_WEAPON;

			short int suiX = -28;
			Vector4f vBack = {0.45, 0.45, 0.45, 1.0};
			Vector4f vTitle = {1.0, 0.68, 0, 1.0};
			gameSys.drawWindow(			sSet.x-suiX,	sSet.y-7,	13, 7, false, true, vBack);
			gameSys.drawText(			sSet.x-suiX+1,	sSet.y-6,	"Stuff", vTitle);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-5,	11, vBack);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-4,	"*Compass")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-3,	"*Cigar")&MOUSE_LEFT);
			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-2,	"*Quest Key")&MOUSE_LEFT);
		}

		if (eI==EI_WEAPON) {
			//if (gameSys.drawTextWindow(		sSet.x-42,	sSet.y,	13, 3,	"Stance",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_STANCE;
			//if (gameSys.drawTextWindow(		sSet.x-28,	sSet.y,	13, 3,	"Defense",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_DEFENSE;
			//if (gameSys.drawTextWindow(		sSet.x-14,	sSet.y,	13, 3,	"Movement",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_MOVEMENT;
			//if (gameSys.drawTextWindow(		sSet.x+14,	sSet.y,	13, 3,	"Skills",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_SKILL;
			//if (gameSys.drawTextWindow(		sSet.x+28,	sSet.y,	13, 3,	"Items",	true, true, backDeselected,	textDeselected,	backHover,	textHover) == MOUSE_LEFT)	eI=EI_ITEMS;
			//if (gameSys.drawTextWindow(		sSet.x+42,	sSet.y,	13, 3,	"Weapons",	true, true, backSelected,	textSelected,	backHover,	textHover2) == MOUSE_LEFT)	eI=EI_WEAPON;

			short int suiX = -42;
			Vector4f vBack = {0.45, 0.45, 0.45, 1.0};
			Vector4f vTitle = {1.0, 0.68, 0, 1.0};
			gameSys.drawWindow(			sSet.x-suiX,	sSet.y-11,	13, 11, false, true, vBack);
			gameSys.drawText(			sSet.x-suiX+1,	sSet.y-10,	"Equipment", vTitle);
			gameSys.winSys.drawHLine(	sSet.x-suiX+1,	sSet.y-9,	11, vBack);

			// If slot click, swap with right hand (primary weapon)
			int iTemp = gameVars->player.active->inventory.equipped.equipment.iRight_Hand;
			if(gameVars->player.active->inventory.equipped.equipment.iHead > -1) {
				if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-8,	gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iHead].id].name)&MOUSE_LEFT) {
						gameVars->player.active->inventory.equipped.equipment.iRight_Hand = gameVars->player.active->inventory.equipped.equipment.iHead;
						gameVars->player.active->inventory.equipped.equipment.iHead = iTemp;
				}
			}
			if(gameVars->player.active->inventory.equipped.equipment.iNeck > -1) {
				if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-7,	gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iNeck].id].name)&MOUSE_LEFT) {
						gameVars->player.active->inventory.equipped.equipment.iRight_Hand = gameVars->player.active->inventory.equipped.equipment.iNeck;
						gameVars->player.active->inventory.equipped.equipment.iNeck = iTemp;
				}
			}
			if(gameVars->player.active->inventory.equipped.equipment.iLeft_Arm > -1) {
				if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-6,	gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iLeft_Arm].id].name)&MOUSE_LEFT) {
						gameVars->player.active->inventory.equipped.equipment.iRight_Hand = gameVars->player.active->inventory.equipped.equipment.iLeft_Arm;
						gameVars->player.active->inventory.equipped.equipment.iLeft_Arm = iTemp;
				}
			}
			if(gameVars->player.active->inventory.equipped.equipment.iLeft_Hand > -1) {
				if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-5,	gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iLeft_Hand].id].name)&MOUSE_LEFT) {
						gameVars->player.active->inventory.equipped.equipment.iRight_Hand = gameVars->player.active->inventory.equipped.equipment.iLeft_Hand;
						gameVars->player.active->inventory.equipped.equipment.iLeft_Hand = iTemp;
				}
			}
			if(gameVars->player.active->inventory.equipped.equipment.iRight_Arm > -1) {
				if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-4,	gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iRight_Arm].id].name)&MOUSE_LEFT) {
						gameVars->player.active->inventory.equipped.equipment.iRight_Hand = gameVars->player.active->inventory.equipped.equipment.iRight_Arm;
						gameVars->player.active->inventory.equipped.equipment.iRight_Arm = iTemp;
				}
			}
			if(gameVars->player.active->inventory.equipped.equipment.iLeft_Leg > -1) {
				if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-3,	gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iLeft_Leg].id].name)&MOUSE_LEFT) {
						gameVars->player.active->inventory.equipped.equipment.iRight_Hand = gameVars->player.active->inventory.equipped.equipment.iLeft_Leg;
						gameVars->player.active->inventory.equipped.equipment.iLeft_Leg = iTemp;
				}
			}
			if(gameVars->player.active->inventory.equipped.equipment.iRight_Leg > -1) {
				if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-2,	gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iRight_Leg].id].name)&MOUSE_LEFT) {
						gameVars->player.active->inventory.equipped.equipment.iRight_Hand = gameVars->player.active->inventory.equipped.equipment.iRight_Leg;
						gameVars->player.active->inventory.equipped.equipment.iRight_Leg = iTemp;
				}
			}
//			if(gameVars->player.active->inventory.equipped.equipment.iRight_Hand > -1) {
//				if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-4,	gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iRight_Hand].id].name)	== MOUSE_LEFT) {
//						//gameVars->player.active->inventory.equipped.equipment.iRight_Hand = gameVars->player.active->inventory.equipped.equipment.iRight_Hand;
//						//gameVars->player.active->inventory.equipped.equipment.iRight_Hand = iTemp;
//				}
//			}
//			if (gameSys.menuSys.draw(	sSet.x-suiX+1,	sSet.y-2,	"*Oink")		== MOUSE_LEFT)	gameVars->player.active->inventory.equipped.equipment.iRight_Hand = GAME::WEAPON.BASE.OINK;
		}
	}

	if (gameVars->menu.bStatus) {
		sSet.x = vC[0]-3;
		sSet.y = gameVars->font.vMax[1]-3;
		sSet.w = vF[0];
		sSet.h = vF[1];
		sSet.sb = 2;
		sSet.sc = 12;

		int iStance		= gameVars->player.active->status.move.iStance,
			iDefense	= gameVars->player.active->status.defense.iMode,
			iMovement	= gameVars->player.active->status.move.iSpeed,
			iWeapon		= gameVars->player.active->inventory.equipped.equipment.iRight_Hand;

		std::string sStance, sDefense, sMovement, sWeapon;

		if(iStance == GAME::MENU.MOVE.STANCE.STAND)			sStance = "Stand";
		else if(iStance == GAME::MENU.MOVE.STANCE.KNEEL)	sStance = "Kneel";
		else if(iStance == GAME::MENU.MOVE.STANCE.SIT)		sStance = "Sit";
		else if(iStance == GAME::MENU.MOVE.STANCE.PRONE)	sStance = "Prone";

		if(iDefense == GAME::MENU.DEFENSE.NONE)				sDefense = "Glance";
		else if(iDefense == GAME::MENU.DEFENSE.BLOCK)		sDefense = "Block";
		else if(iDefense == GAME::MENU.DEFENSE.DODGE)		sDefense = "Dodge";
		else if(iDefense == GAME::MENU.DEFENSE.DEFLECT)		sDefense = "Deflect";

		if(iMovement == GAME::MENU.MOVE.RUN)				sMovement = "Run";
		else if(iMovement == GAME::MENU.MOVE.WALK)			sMovement = "Walk";

		//sWeapon = gameVars->weapon[iWeapon].name;
		sWeapon = gameVars->items[gameVars->player.active->inventory.list[iWeapon].id].name;

		//Reports
		gameSys.drawTextWindow(	sSet.x-42,	sSet.y,	13,	3,	sStance,	true, true,	backNormal, textNormal, backHover, textHover);
		gameSys.drawTextWindow(	sSet.x-28,	sSet.y,	13, 3,	sDefense,	true, true,	backNormal, textNormal, backHover, textHover);
		gameSys.drawTextWindow(	sSet.x-14,	sSet.y,	13, 3,	sMovement,	true, true,	backNormal, textNormal, backHover, textHover);
		gameSys.drawTextWindow(	sSet.x+14,	sSet.y,	13, 3,	"Skills",	true, true,	backNormal, textNormal, backHover, textHover);
		gameSys.drawTextWindow(	sSet.x+28,	sSet.y,	13, 3,	"Items",	true, true,	backNormal, textNormal, backHover, textHover);
		gameSys.drawTextWindow(	sSet.x+42,	sSet.y,	13, 3,	sWeapon,	true, true,	backNormal, textNormal, backHover, textHover);
	}

	if (gameVars->menu.bActionIcon) {
		sSet.x = vC[0]-1;
		sSet.y = gameVars->font.vMax[1]-6;
		sSet.w = vF[0];
		sSet.h = vF[1];
		//sSet.sa = 12;

		//Intent Icon
		//if (gameSys.checkIcon(sSet.x-3,	 sSet.y,         sSet.w*14, sSet.h*6, 40, "wm_icons_subdued.png", true, true)) {
		//if (gameSys.drawWindow(sSet.x-3,	 sSet.y,         (sSet.w*14)/gameVars->font.vSize[0], (sSet.h*6)/gameVars->font.vSize[1], true, true, backNormal, backHover)) {

		std::string sText = "";
		if (gameVars->player.active->status.iIntent == GAME::MENU.INTENT.CAST_SPELL) {
			sText =  "Spell";
		}
		else if (gameVars->player.active->status.iIntent == GAME::MENU.INTENT.MELEE) {
			sText =  "Melee";
		}
		else {
			sText =  "Unkown or\nNot set";
		}

		if (gameSys.drawTextWindow(	sSet.x-3,
									sSet.y,
									(sSet.w*14)/gameVars->font.vSize[0],
									(sSet.h*6)/gameVars->font.vSize[1],
									sText,
									true,
									true,
									backNormal,
									textNormal,
									backHover,
									textHover)&MOUSE_LEFT) {
			if( eI == EI_INTENT ) eI=EI_INIT;
			else eI = EI_INTENT;

			if (gameVars->player.active->status.iIntent==GAME::MENU.INTENT.STANCE)		{ gameVars->player.active->status.iState=GAME::MENU.INTENT.STANCE; exit(false); }
			if (gameVars->player.active->status.iIntent==GAME::MENU.INTENT.CAST_SPELL)	{ gameVars->player.active->status.iState=GAME::MENU.INTENT.CAST_SPELL; exit(false); }
			if (gameVars->player.active->status.iIntent==GAME::MENU.INTENT.MELEE) 		{ gameVars->player.active->status.iState=GAME::MENU.INTENT.MELEE; exit(false); }
		}

		/*
		if (gameVars->player.active->status.iIntent == GAME::MENU.INTENT.CAST_SPELL) {
			gameSys.textSys.draw(sSet.x-1, sSet.y+2, "Spell");
		}
		else if (gameVars->player.active->status.iIntent == GAME::MENU.INTENT.MELEE) {
			gameSys.textSys.draw(sSet.x-1, sSet.y+2, "Melee");
		}
		else {
			gameSys.textSys.draw(sSet.x-1, sSet.y+2, "Unknown");
		}
		*/
	}

	if(!bWorld) {
		getInput();
		update();			// Other final draw routines
		//draw();
	}
}

void RunMenu::update() {
	if(bShowMouse) {
			gameSys.drawSprite(gameVars->controls.mouse.x,gameVars->controls.mouse.y,64,64,"dagger.png",false,false);
	}
}

void RunMenu::getInput() {
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

	if (gameVars->debug.lag) printf("GET MOUSE CLICK\n");
	if(SDL_GetMouseState(&gameVars->controls.mouse.x, &gameVars->controls.mouse.y)&SDL_BUTTON(1)) gameVars->controls.mouse.button.check[0]=true;
	else gameVars->controls.mouse.button.check[0]=false;
	gameSys.mouseSys.checkButton(0);

	//Execute input commands
	//GameSys::Input::keyboard.repeat(gameVars, gameVars->controls.keyboard.event);
	keyboard.update();
	processInput();
}

void RunMenu::processInput() {
	if (keyboard.bKey[SDLK_ESCAPE])	{
		//keyboard.reset();
		eS=GAME::MENU.STATE.INIT;
		eI=EI_INIT;
		gameVars->menu.bActionIcon=true;
		gameVars->menu.bIntent=false;
		gameVars->menu.bStatus=false;
		gameVars->menu.bOperations=false;
		gameVars->state.menu=false;
		ToggleMouse(false);
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
	if (keyboard.bKey[SDLK_o]) {
		eS=GAME::MENU.STATE.INIT;
		eI=EI_INIT;
		gameVars->menu.bOperations=true;
		gameVars->menu.bIntent=false;
		if(gameVars->state.battle) gameVars->menu.bStatus=true;
		else gameVars->menu.bStatus=false;
		gameVars->menu.bActionIcon=true;
	}
	if (keyboard.bKey[SDLK_u]) {
		eS=GAME::MENU.STATE.INIT;
		eI=EI_INIT;
		gameVars->menu.bOperations=false;
		gameVars->menu.bIntent=true;
		gameVars->menu.bStatus=true;
		gameVars->menu.bActionIcon=true;
	}

	if (keyboard.bKey[SDLK_DELETE])	{ }
	if (keyboard.bKey[SDLK_PAGEDOWN])	{ }

	if (keyboard.bKey[SDLK_INSERT])	{ }
	if (keyboard.bKey[SDLK_PAGEUP])	{ }

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

void RunMenu::draw() {
	SDL_GL_SwapBuffers();
}

void RunMenu::toggle(bool &myBool) {
	if (myBool) myBool=false;
	else myBool=true;
}

#endif /* RUNMENU_H_ */
