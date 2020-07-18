/*
 * runGrimoire.h
 *
 *  Created on: Jul 26, 2015
 *      Author: bcthund
 */

#ifndef RUNGRIMOIRE_H_
#define RUNGRIMOIRE_H_

class RunGrimoire {
	private:
		enum MENUSTATES { TAB1, TAB2, TAB3, TAB4, TAB5, TAB6, TAB7, TAB8, TAB9, TAB10, TAB11, TAB12 };
		int menuState;
		Keyboard keyboard;

	protected:
		void toggle(bool &myBool);
		void getInput();
		void processInput();
		void update();
		void draw();

	public:
		RunGrimoire();
		bool init();
		bool load();
		void run();
} Grimoire;

//RunGrimoire * Grimoire = new(RunGrimoire);

RunGrimoire::RunGrimoire() {
	menuState = TAB1;
	keyboard.calc();
}

bool RunGrimoire::init() {
	return true;
}

bool RunGrimoire::load() {
	return true;
}

void RunGrimoire::run() {
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glClear( gameVars->screen.clear );

	//Set default colors and presets
	Vector4f tint        = {1.00, 0.518, 0.00, 1.0};
	Vector4f selected    = {1.00, 1.00, 1.00, 1.0};
	Vector4f deselected  = {0.80, 0.70, 0.70, 0.8};

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

	gameSys.drawSprite(4,1,gameVars->screen.w-(8*gameVars->font.vSize[1]),gameVars->screen.h-(gameVars->font.vSize[2]),"grimoire.png", false, true);

	getInput();
	update();
	//draw();
}

void RunGrimoire::update() {
//	if (menuState.show_choice) {
//		Script::showChoice.run(gameVars);
//	}
}

void RunGrimoire::getInput() {
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

void RunGrimoire::processInput() {
	if (keyboard.bKey[SDLK_ESCAPE])	{
		gameVars->state.book=false;
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

void RunGrimoire::draw() {
	SDL_GL_SwapBuffers();
}

void RunGrimoire::toggle(bool &myBool) {
	if (myBool) myBool=false;
	else myBool=true;
}

#endif /* RUNGRIMOIRE_H_ */
