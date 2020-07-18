/*
 * runMenu.h
 *
 *  Created on: Sep 28, 2010
 *      Author: bcthund
 */

#ifndef RUNMAINMENU_H_
#define RUNMAINMENU_H_

class RunMainMenu {
	private:
		Keyboard keyboard;

//		Vector4f	color_tomes_normal	= {1.0, 1.0, 1.0, 1.0},
//							color_tomes_hidden	= {1.0, 1.0, 1.0, 0.0},
//							color_tomes_hover	= {2.0, 2.0, 2.0, 1.0};
		enum _CHOICES { CHOICE_NONE, CHOICE_NEW, CHOICE_LOAD, CHOICE_OPTION, CHOICE_QUIT };

	protected:
		void toggle(bool &myBool);
		void getInput();
		void processInput();
		void update();
		void draw();
		void choice(int iChoice);

	public:
		int eS;
		bool init();
		bool load();
		void reset();
		void set();
		void run();
		//void run(bool bWorld);
		//void run(bool bOperations, bool bStatus, bool bIntent, bool bActionIcon, bool bWorld);
		RunMainMenu();
} MainMenu;

RunMainMenu::RunMainMenu() {
//	eS = 0;
//	bShowMouse = true;

	//CopyVector4f(gameVars->color.transparent, inv_normal);
	//CopyVector4f(gameVars->color.tan, holster_text);
	//CopyVector4f(gameVars->color.grey, inv_hover_normal);
	//CopyVector4f(gameVars->color.yellow, inv_select);
	//CopyVector4f(gameVars->color.orange, inv_hover_select);
	//CopyVector4f(gameVars->color.white, inv_text);

	keyboard.calc();
}

bool RunMainMenu::init() {
	return true;
}

bool RunMainMenu::load() {
	return true;
}

void RunMainMenu::reset() {
	//eS = GAME::MENU.STATE.INIT;
}

void RunMainMenu::choice(int iChoice) {
	switch(iChoice) {
		case CHOICE_NEW:
			gameSys.audioSys.stopMusic();
			gameVars->state.main_menu = false;
			break;
		case CHOICE_LOAD:
			cout << "Not Implemented" << endl;
			break;
		case CHOICE_OPTION:
			cout << "Not Implemented" << endl;
			break;
		case CHOICE_QUIT:
			gameSys.audioSys.stopMusic();
			gameVars->state.quit = true;
			break;
	}
	//ToggleMouse(false);
}

void RunMainMenu::set() {
//	eS = GAME::MENU.STATE.INIT;
}

//void RunMainMenu::run(bool bOperations, bool bIntent, bool bStatus, bool bActionIcon, bool bWorld=false) {
//	gameVars->menu.bOperations=bOperations;
//	gameVars->menu.bIntent=bIntent;
//	gameVars->menu.bStatus=bStatus;
//	gameVars->menu.bActionIcon=bActionIcon;
//	run(bWorld);
//}

void RunMainMenu::run() {

	gameSys.audioSys.playMusic(0, -1, 1000);
	//Set default colors and presets
//	Vector4f vFont, vVal, vNI, vTitle,
//			 textNormal		= { 0.71,	0.48,	0.24,	1.0 },
//			 textHover		= { 1.0,	0.68,	0,		1.0 },
//			 textHover2		= { 1.0,	0.00,	0.00,	1.0 },
//			 textSelected	= { 1.0,	0.52,	0,		1.0 },
//			 textDeselected	= { 0.4,	0.37,	0.31,	0.7 },
//			 backNormal		= { 0.45,	0.45,	0.45,	1.0 },
//			 backHover		= { 0.55,	0.55,	0.55,	1.0 },
//			 backSelected	= { 0.75,	0.75,	0.75,	1.0 },
//			 backDeselected	= { 0.25,	0.25,	0.25,	0.7 };
//	CopyVector4f(gameVars->color.tan ,vFont);
//	CopyVector4f(gameVars->color.grey ,vVal);
//	CopyVector4f(gameVars->color.red ,vNI);
//	CopyVector4f(gameVars->color.yellow ,vTitle);
//	Vector4f tint        = {1.00, 0.518, 0.00, 1.0};
//	Vector4f selected    = {1.00, 1.00, 1.00, 1.0};
//	Vector4f deselected  = {0.80, 0.70, 0.70, 0.8};
//	Vector2f vC = {((-gameVars->font.screenCoords[0]-32)/gameVars->font.vSize[0]), ((gameVars->font.screenCoords[1]-32)/gameVars->font.vSize[1])};
//	//Vector2f vC = {-gameVars->font.screenCoords[0], gameVars->font.screenCoords[1]};
//	Vector2f vF = {gameVars->font.vSize[0], gameVars->font.vSize[1]};

//	gameSys.checkIcon(1, 1, 64, 64, 52, "wm_icons_subdued.png", true, true, color_tomes_hidden, color_tomes_normal);
//	gameSys.checkIcon(gameVars->font.vMax[0]-8, 1, 64, 64, 53, "wm_icons_subdued.png", true, true, color_tomes_hidden, color_tomes_normal);
//
//	gameSys.checkIcon(1, gameVars->font.vMax[1]-7, 64, 64, 54, "wm_icons_subdued.png", true, true, color_tomes_hidden, color_tomes_normal);
//	gameSys.checkIcon(gameVars->font.vMax[0]-8, gameVars->font.vMax[1]-7, 64, 64, 55, "wm_icons_subdued.png", true, true, color_tomes_hidden, color_tomes_normal);

	glClearColor(	gameVars->screen.vClearColorCurrent[0],
								gameVars->screen.vClearColorCurrent[1],
								gameVars->screen.vClearColorCurrent[2],
								gameVars->screen.vClearColorCurrent[3]	);
	glClear( gameVars->screen.clear );

	// Draw Background
	gameSys.drawSprite(0, 0, 1280, 720, "mm_background.png", false, false);

	// Draw Title
//	int iX = (rand() % 4) - 2,
//			iY = (rand() % 4) - 2;
	int iBeat = gameSys.audioSys.getBeat()/30;
//	int iX = ((rand() % 2)-1) * iBeat,
//			iY = ((rand() % 2)-1) * iBeat;
	float iX = (float)gameSys.audioSys.getBeat()/30.0f,
				iY = (float)gameSys.audioSys.getBeat()/30.0f;

	//cout << iBeat << "\t" << iX << "\t" << iY << endl;

	gameSys.drawSprite(280+(iX/2), 50+(iY/2), 720-iX, 240-iY, "mm_title.png", false, false);
	//gameSys.drawSprite(280+iX, 50+iY, 720, gameSys.audioSys.getBeat(), "mm_title.png", false, false);

	// Draw Buttons
	//if(gameSys.checkText(10, 2, "Start", true, true)&MOUSE_LEFT) gameVars->state.main_menu = false;
	//if(gameSys.drawTextWindow(10, 2, 50, 20, "Start", true, true)&MOUSE_LEFT) gameVars->state.main_menu = false;
	//if(gameSys.checkIcon(10, 2, 100, 50, 0, "mainmenu.png", true, true)&MOUSE_LEFT);
	if(gameSys.checkSprite(58,   668, 265, 44, "mm_new.png",    true, false, gameVars->color.white, gameVars->color.green)&MOUSE_LEFT) choice(CHOICE_NEW);
	if(gameSys.checkSprite(430,  668, 185, 44, "mm_load.png",   true, false, gameVars->color.white, gameVars->color.green)&MOUSE_LEFT) choice(CHOICE_LOAD);
	if(gameSys.checkSprite(700,  668, 231, 44, "mm_option.png", true, false, gameVars->color.white, gameVars->color.green)&MOUSE_LEFT) choice(CHOICE_OPTION);
	if(gameSys.checkSprite(1066, 668, 171, 44, "mm_quit.png",   true, false, gameVars->color.white, gameVars->color.green)&MOUSE_LEFT) choice(CHOICE_QUIT);

	SDL_ShowCursor(SDL_DISABLE);
	getInput();

	update();
}

void RunMainMenu::update() {
}

void RunMainMenu::getInput() {
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

	gameSys.drawSprite(gameVars->controls.mouse.x, gameVars->controls.mouse.y, 64, 100, "dagger.png", false, false);

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

void RunMainMenu::processInput() {
	if (keyboard.bKey[SDLK_ESCAPE])	{
		//gameVars->state.main_menu = false;
		exit(CHOICE_QUIT);
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
	if (keyboard.bKey[SDLK_o]) { }
	if (keyboard.bKey[SDLK_u]) { }

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
	if (keyboard.bKey[SDLK_F10])	{ }
	if (keyboard.bKey[SDLK_F11])	{ }
	if (keyboard.bKey[SDLK_F12])	{ }

	if (gameVars->controls.mouse.relX<-gameVars->controls.mouse.deadX)	{ }
	if (gameVars->controls.mouse.relX>gameVars->controls.mouse.deadX)		{ }
	if (gameVars->controls.mouse.relY<-gameVars->controls.mouse.deadY)	{ }
	if (gameVars->controls.mouse.relY>gameVars->controls.mouse.deadY)		{ }
}

void RunMainMenu::draw() {
	SDL_GL_SwapBuffers();
}

void RunMainMenu::toggle(bool &myBool) {
	if (myBool) myBool=false;
	else myBool=true;
}

#endif /* RUNMENU_H_ */
