/*
 * runBattleScroll.h
 *
 *  Created on: Jul 26, 2015
 *      Author: bcthund
 */

#ifndef RUNBATTLESCROLL_H_
#define RUNBATTLESCROLL_H_

class RunBattleScroll {
	private:
		enum MENUSTATES { BSSTATE_INIT = 0, BSSTATE_HISTORY = 1 };
		int menuState,
			menuSelection;
		Keyboard keyboard;

	protected:
		void toggle(bool &myBool);
		void getInput();
		void processInput();
		void update();
		void draw();

	public:
		RunBattleScroll();
		bool init();
		bool load();
		void run();
} BattleScroll;

//RunBattleScroll * BattleScroll = new(RunBattleScroll);

RunBattleScroll::RunBattleScroll() {
	menuState = BSSTATE_INIT;
	menuSelection = 0;
	keyboard.calc();
}

bool RunBattleScroll::init() {
	return true;
}

bool RunBattleScroll::load() {
	return true;
}

void RunBattleScroll::run() {
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glClear( gameVars->screen.clear );

	//Set default colors and presets
	Vector4f vFont, vVal, vNI, vTitle, vWhite, vRed, vTemp;
//		CopyVector4f(gameVars->color.tan ,vFont);
//		CopyVector4f(gameVars->color.grey ,vVal);
//		CopyVector4f(gameVars->color.red ,vNI);
//		CopyVector4f(gameVars->color.yellow ,vTitle);
//		CopyVector4f(gameVars->color.white ,vWhite);
//		CopyVector4f(gameVars->color.red ,vRed);
//		CopyVector4f(gameVars->color.white ,vTemp);

		vFont = gameVars->color.tan;
		vVal = gameVars->color.grey;
		vNI = gameVars->color.red;
		vTitle = gameVars->color.yellow;
		vWhite = gameVars->color.white;
		vRed = gameVars->color.red;
		vTemp = gameVars->color.white;
	Vector4f tint        = {1.00, 0.518, 0.00, 1.0};
	Vector4f selected    = {0.50, 1.00, 0.50, 1.0};
	Vector4f deselected  = {1.00, 0.50, 0.50, 1.0};

	Vector2f vC = {((-gameVars->font.screenCoords[0]-32)/gameVars->font.vSize[0]), ((gameVars->font.screenCoords[1]-32)/gameVars->font.vSize[1])};
	Vector2f vF = {gameVars->font.vSize[0], gameVars->font.vSize[1]};

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

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glClear( gameVars->screen.clear );

	/*
	 * Draw the world as it last was
	 */
	if (gameVars->state.battle) {
		//Battle.draw(*gameVars->player.active);
		Battle.draw();
	}
	else {
		world.Update(false);
	}

	gameSys.drawSprite(1,1,gameVars->screen.w-(3*gameVars->font.vSize[1]),gameVars->screen.h-(20*gameVars->font.vSize[2]),"battle_scroll.png", false, true);

	int cx	= 15,
		cy	= 4,
		os3	= 13;

	if(menuState == BSSTATE_INIT) {
		/*
		 * Draw the battle scroll for all enemies
		 *  up to the first 6 closest enemies. Selection
		 *  of target is possible from the battle scroll.
		 *
		 * Need to implement a restriction to 6 enemies
		 *  and calculate the distance still to determine
		 *  which 6 to show.
		 */
		if(Battle.numEnemy>0) {
			for(int i=0; i<Battle.numEnemy; i++) {

				/*
				 * Calculate offsets for each enemy on
				 *  the battle scroll.
				 */
				if(i==0) {
					cx	= 15;
					cy	= 4;
				}
				else if(i==1) {
					cy	+= 2;
				}
				else if(i==2) {
					cy	+= 2;
				}
				else if(i==3) {
					cy	+= 2;
				}
				else if(i==4) {
					cy	+= 2;
				}
				else if(i==5) {
					cy	+= 2;
				}
				else if(i==6) {
					cx	+= 50;
					cy	= 4;
				}
				else if(i==7) {
					cy	+= 2;
				}
				else if(i==8) {
					cy	+= 2;
				}
				else if(i==9) {
					cy	+= 2;
				}
				else if(i==10) {
					cy	+= 2;
				}
				else if(i==11) {
					cy	+= 2;
				}


				if(Battle.enemies[i]->init.id == gameVars->player.active->status.target->init.id) {
					gameSys.drawIcon(cx-8, cy, 64, 64, Battle.enemies[i]->init.face, "faces.png", true, true, selected);
				}
				else {
					if(Battle.enemies[i]->init.isDead) vTemp = vRed; //CopyVector4f(vRed, vTemp);
					else vTemp = vWhite; //CopyVector4f(vWhite, vTemp);

					if(gameSys.checkIcon(cx-8, cy, 64, 64, Battle.enemies[i]->init.face, "faces.png", true, true, vTemp)==MOUSE_LEFT) {
						gameVars->player.active->status.target = Battle.enemies[i];
					}
				}

				// Calculate cumulative damage card
				int head  = Battle.enemies[i]->damage.limb.head.durability,
						torso = Battle.enemies[i]->damage.limb.torso.durability,
						larm  = Battle.enemies[i]->damage.limb.left_arm[0].durability,
						rarm  = Battle.enemies[i]->damage.limb.right_arm[0].durability,
						lhand = Battle.enemies[i]->damage.limb.left_arm[1].durability,
						rhand = Battle.enemies[i]->damage.limb.right_arm[1].durability,
						lleg  = Battle.enemies[i]->damage.limb.left_leg[0].durability,
						rleg  = Battle.enemies[i]->damage.limb.right_leg[0].durability,
						lfoot = Battle.enemies[i]->damage.limb.left_leg[1].durability,
						rfoot = Battle.enemies[i]->damage.limb.right_leg[1].durability;

				int	card_head	= 0,
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
				if(gameSys.checkIcon(cx-1, cy, 64, 64, 0, "cards.png", false, true, vWhite)==MOUSE_LEFT) {
					menuState = BSSTATE_HISTORY;
					menuSelection = i;	// Enemy ID
					//cout << "CLICK!" << endl;
				}

				//cx = 120;
				//cy = 40;

				//cx = (gameVars->font.vSize[0]*15)-gameVars->font.vHalfSize[0];
				//cy = (gameVars->font.vSize[1]*5)-gameVars->font.vHalfSize[1];
				gameSys.drawIcon(cx-1,   cy, 64, 64, card_head,  "cumulative.png", false, true, vWhite);
				gameSys.drawIcon(cx-1,   cy, 64, 64, card_torso, "cumulative.png", false, true, vWhite);
				gameSys.drawIcon(cx-1,   cy, 64, 64, card_larm,  "cumulative.png", false, true, vWhite);
				gameSys.drawIcon(cx-1,   cy, 64, 64, card_rarm,  "cumulative.png", false, true, vWhite);
				gameSys.drawIcon(cx-1,   cy, 64, 64, card_lhand, "cumulative.png", false, true, vWhite);
				gameSys.drawIcon(cx-1,   cy, 64, 64, card_rhand, "cumulative.png", false, true, vWhite);
				gameSys.drawIcon(cx-1,   cy, 64, 64, card_lleg,  "cumulative.png", false, true, vWhite);
				gameSys.drawIcon(cx-1,   cy, 64, 64, card_rleg,  "cumulative.png", false, true, vWhite);
				gameSys.drawIcon(cx-1,   cy, 64, 64, card_lfoot, "cumulative.png", false, true, vWhite);
				gameSys.drawIcon(cx-1,   cy, 64, 64, card_rfoot, "cumulative.png", false, true, vWhite);

				gameSys.drawText(cx+5,   cy, "Name:", vFont);				gameSys.drawText(cx+os3, cy, Battle.enemies[i]->init.name, vWhite);
				gameSys.drawText(cx+5, ++cy, "Level:", vFont);			gameSys.textSys.draw(cx+os3, cy, &Battle.enemies[i]->mod.level, vWhite);
				gameSys.drawText(cx+5, ++cy, "Race:", vFont);				gameSys.drawText(cx+os3, cy, Battle.enemies[i]->init.sRace, vWhite);
				gameSys.drawText(cx+5, ++cy, "Role:", vFont);				gameSys.drawText(cx+os3, cy, Battle.enemies[i]->init.sRole, vWhite);
				gameSys.drawText(cx+5, ++cy, "State:", vFont);			gameSys.drawText(cx+os3, cy, Battle.enemies[i]->init.sState, vWhite);
				gameSys.drawText(cx,   ++cy, "Profession:", vFont);	gameSys.drawText(cx+os3, cy, Battle.enemies[i]->init.sProfession, vWhite);
//				gameSys.drawText(cx,   ++cy, "Equipment:", vFont);		gameSys.drawText(cx+os3, cy, gameVars->weapon[Battle.enemies[i]->items.weapon.equipped].name, vWhite);

			}
		}
		else {
			gameSys.drawText(7, 5, "No previous or current battle information.\nEnter a battle to populate this list.");
		}
	}
	else {
		/*
		 * Draw the battle scroll history screen for
		 *  the selected enemy number.
		 */

		// Calculate cumulative damage card
		int head  = Battle.enemies[menuSelection]->damage.limb.head.durability,
				torso = Battle.enemies[menuSelection]->damage.limb.torso.durability,
				larm  = Battle.enemies[menuSelection]->damage.limb.left_arm[0].durability,
				rarm  = Battle.enemies[menuSelection]->damage.limb.right_arm[0].durability,
				lhand = Battle.enemies[menuSelection]->damage.limb.left_arm[1].durability,
				rhand = Battle.enemies[menuSelection]->damage.limb.right_arm[1].durability,
				lleg  = Battle.enemies[menuSelection]->damage.limb.left_leg[0].durability,
				rleg  = Battle.enemies[menuSelection]->damage.limb.right_leg[0].durability,
				lfoot = Battle.enemies[menuSelection]->damage.limb.left_leg[1].durability,
				rfoot = Battle.enemies[menuSelection]->damage.limb.right_leg[1].durability;

		int	card_head	= 0,
			card_torso	= 0,
			card_larm	= 0,
			card_rarm	= 0,
			card_lhand	= 0,
			card_rhand	= 0,
			card_lleg	= 0,
			card_rleg	= 0,
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

		if(gameSys.checkIcon(	cx-1,	cy,  64, 64, 0,			 			"cards.png",			false, true, vWhite)==MOUSE_LEFT) menuState = BSSTATE_INIT;
		gameSys.drawIcon(		cx-1,   cy,  64, 64, card_head,		"cumulative.png",	false, true, vWhite);
		gameSys.drawIcon(		cx-1,   cy,  64, 64, card_torso,	"cumulative.png",	false, true, vWhite);
		gameSys.drawIcon(		cx-1,   cy,  64, 64, card_larm,		"cumulative.png",	false, true, vWhite);
		gameSys.drawIcon(		cx-1,   cy,  64, 64, card_rarm,		"cumulative.png",	false, true, vWhite);
		gameSys.drawIcon(		cx-1,   cy,  64, 64, card_lhand,	"cumulative.png",	false, true, vWhite);
		gameSys.drawIcon(		cx-1,   cy,  64, 64, card_rhand,	"cumulative.png",	false, true, vWhite);
		gameSys.drawIcon(		cx-1,   cy,  64, 64, card_lleg,		"cumulative.png",	false, true, vWhite);
		gameSys.drawIcon(		cx-1,   cy,  64, 64, card_rleg,		"cumulative.png",	false, true, vWhite);
		gameSys.drawIcon(		cx-1,   cy,  64, 64, card_lfoot,	"cumulative.png",	false, true, vWhite);
		gameSys.drawIcon(		cx-1,   cy,  64, 64, card_rfoot,	"cumulative.png",	false, true, vWhite);

		gameSys.drawIcon(		cx-8,   cy, 64, 64, Battle.enemies[menuSelection]->init.face, "faces.png", true, true);
		gameSys.drawText(		cx+5,   cy, "Name:", vFont);				gameSys.drawText(cx+os3, cy, Battle.enemies[menuSelection]->init.name, vWhite);
		gameSys.drawText(		cx+5, ++cy, "Level:", vFont);				gameSys.textSys.draw(cx+os3, cy, &Battle.enemies[menuSelection]->mod.level, vWhite);					// TODO: Fix this so that it can be called like the other simplified lines here
		gameSys.drawText(		cx+5, ++cy, "Race:", vFont);				gameSys.drawText(cx+os3, cy, Battle.enemies[menuSelection]->init.sRace, vWhite);
		gameSys.drawText(		cx+5, ++cy, "Role:", vFont);				gameSys.drawText(cx+os3, cy, Battle.enemies[menuSelection]->init.sRole, vWhite);
		gameSys.drawText(		cx+5, ++cy, "State:", vFont);				gameSys.drawText(cx+os3, cy, Battle.enemies[menuSelection]->init.sState, vWhite);
		gameSys.drawText(		cx,   ++cy, "Profession:", vFont);	gameSys.drawText(cx+os3, cy, Battle.enemies[menuSelection]->init.sProfession, vWhite);
		gameSys.drawText(		cx,   ++cy, "Equipment:", vFont);		gameSys.drawText(cx+os3, cy, gameVars->weapon[Battle.enemies[menuSelection]->inventory.equipped.equipment.iRight_Hand].name, vWhite);
		cy+=2;
		cx-=8;

		/*
		 * Draw the history cards
		 */
		for(int i=0; i<16; i++) {
			gameSys.drawIcon(cx-1, cy, 64, 64, 0,  "cards.png", false, true, vWhite);
			gameSys.drawIcon(cx-1, cy, 64, 64, Battle.enemies[menuSelection]->status.iCards[i][0],  "cards.png", false, true, vWhite);
			gameSys.drawIcon(cx-1, cy, 64, 64, Battle.enemies[menuSelection]->status.iCards[i][1],  "cards.png", false, true, vWhite);
			gameSys.drawIcon(cx-1, cy, 64, 64, Battle.enemies[menuSelection]->status.iCards[i][2],  "cards.png", false, true, vWhite);
			cx+=6;
		}
	}

	getInput();
	update();
	//draw();
}

void RunBattleScroll::update() {
//	if (menuState.show_choice) {
//		Script::showChoice.run(gameVars);
//	}
	//if(bShowMouse) {
			gameSys.drawSprite(gameVars->controls.mouse.x, gameVars->controls.mouse.y, 64, 100, "quill2.png", false, false);
	//}
}

void RunBattleScroll::getInput() {
	//Event capturing
	SDL_PumpEvents();

	//Get relative mouse movement
	SDL_GetMouseState(&gameVars->controls.mouse.x, &gameVars->controls.mouse.y);
	gameVars->controls.mouse.relX=gameVars->controls.mouse.x-gameVars->screen.halfW;
	gameVars->controls.mouse.relY=gameVars->controls.mouse.y-gameVars->screen.halfH;

	keyboard.event = SDL_GetKeyState(NULL);

	//if (gameVars->debug.lag) printf("GET MOUSE CLICK\n");
	if(SDL_GetMouseState(&gameVars->controls.mouse.x, &gameVars->controls.mouse.y)&SDL_BUTTON(1)) gameVars->controls.mouse.button.check[0]=true;
	else gameVars->controls.mouse.button.check[0]=false;
	gameSys.mouseSys.checkButton(0);

	//Execute input commands
	keyboard.update();
	processInput();
}

void RunBattleScroll::processInput() {
	if (keyboard.bKey[SDLK_ESCAPE])	{
		if(menuState == BSSTATE_HISTORY) menuState = BSSTATE_INIT;
		else {
			gameVars->state.book=false;
			SDL_WarpMouse(gameVars->screen.halfW, gameVars->screen.halfH);
		}
		//Menu.reset();
		//SDL_WarpMouse(gameVars->screen.halfW, gameVars->screen.halfH);
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

void RunBattleScroll::draw() {
	SDL_GL_SwapBuffers();
}

void RunBattleScroll::toggle(bool &myBool) {
	if (myBool) myBool=false;
	else myBool=true;
}

#endif /* RUNBATTLESCROLL_H_ */
