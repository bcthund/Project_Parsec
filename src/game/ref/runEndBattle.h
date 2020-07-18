/*
 * RunEndBattle.h
 *
 *  Created on: Jul 26, 2015
 *      Author: bcthund
 */

#ifndef RUNENDBATTLE_H_
#define RUNENDBATTLE_H_

class RunEndBattle {
	private:
		Keyboard keyboard;

	protected:
		void toggle(bool &myBool);
		void getInput();
		void processInput();
		void update();
		void draw();

	public:
		RunEndBattle();
		bool init();
		bool load();
		void run();
} EndBattle;

//RunEndBattle * BattleScroll = new(RunEndBattle);

RunEndBattle::RunEndBattle() {
	keyboard.calc();
}

bool RunEndBattle::init() {
	return true;
}

bool RunEndBattle::load() {
	return true;
}

void RunEndBattle::run() {
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glClear( gameVars->screen.clear );
	SDL_ShowCursor(SDL_ENABLE);

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
	//Vector2f vC = {-gameVars->font.screenCoords[0], gameVars->font.screenCoords[1]};

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

	//gameSys.spriteSys.draw( 4, 0, gameVars->screen.w-(8*gameVars->font.vSize[1]), gameVars->screen.h-(gameVars->font.vSize[2]),"battle_scroll.png", false, false);
	gameSys.drawSprite(1,1,gameVars->screen.w-(3*gameVars->font.vSize[1]),gameVars->screen.h-(20*gameVars->font.vSize[2]),"battle_scroll.png", false, true);

	int cx	= 15,
		cy	= 6,
		os3	= 13;

	for(int i=0; i<Battle.numEnemy; i++) {
		if(i==0) {
			cx	= 20;
			cy	= 8;
		}
		else if(i==1) {
			cy	+= 5;
		}
		else if(i==2) {
			cy	+= 5;
		}
		else if(i==3) {
			cx	+= 60;
			cy	= 8;
		}
		else if(i==4) {
			cy	+= 5;
		}
		else if(i==5) {
			cy	+= 5;
		}


		if(Battle.enemies[i]->init.isDead) vTemp = vRed; //CopyVector4f(vRed, vTemp);
		else vTemp = vWhite; //CopyVector4f(vWhite, vTemp);

		if(gameSys.checkIcon(cx-8, cy, 64, 64, Battle.enemies[i]->init.face, "faces.png", true, true, vTemp)) {
			gameVars->player.active->status.target = Battle.enemies[i];
		}

		gameSys.drawText(cx,   cy, "Name:", vFont);				gameSys.drawText(cx+os3, cy, Battle.enemies[i]->init.name, vWhite);
		gameSys.drawText(cx, ++cy, "State:", vFont);			gameSys.drawText(cx+os3, cy, "Dead", vWhite);

		gameSys.drawWindow(cx, ++cy, 30, 8, false, true, vVal);

		cy += 6;
	}

	getInput();
	update();
	//draw();
}

void RunEndBattle::update() {
//	if (menuState.show_choice) {
//		Script::showChoice.run(gameVars);
//	}
}

void RunEndBattle::getInput() {
	//Event capturing
	SDL_PumpEvents();

	//Get relative mouse movement
	SDL_GetMouseState(&gameVars->controls.mouse.x, &gameVars->controls.mouse.y);
	gameVars->controls.mouse.relX=gameVars->controls.mouse.x-gameVars->screen.halfW;
	gameVars->controls.mouse.relY=gameVars->controls.mouse.y-gameVars->screen.halfH;

	keyboard.event = SDL_GetKeyState(NULL);

	if (gameVars->debug.lag) printf("GET MOUSE CLICK\n");
	if(SDL_GetMouseState(&gameVars->controls.mouse.x, &gameVars->controls.mouse.y)&SDL_BUTTON(1)) gameVars->controls.mouse.button.check[0]=true;
	else gameVars->controls.mouse.button.check[0]=false;
	gameSys.mouseSys.checkButton(0);

	//Execute input commands
	keyboard.update();
	processInput();
}

void RunEndBattle::processInput() {
	if (keyboard.bKey[SDLK_ESCAPE])	{
		gameVars->state.endBattle=false;
		gameSys.audioSys.stopMusic();
		//Menu.reset();
		SDL_WarpMouse(gameVars->screen.halfW, gameVars->screen.halfH);
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

void RunEndBattle::draw() {
	SDL_GL_SwapBuffers();
}

void RunEndBattle::toggle(bool &myBool) {
	if (myBool) myBool=false;
	else myBool=true;
}

#endif /* RUNENDBATTLE_H_ */
