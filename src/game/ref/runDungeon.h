/*
 * runDungeon.hpp
 *
 *  Created on: Jun 13, 2010
 *      Author: bcthund
 */

#ifndef RUNDUNGEON_HPP_
#define RUNDUNGEON_HPP_

//#include "./runDungeon/O2D.h"
//#include "./runDungeon/O3D.h"
//#include "./runDungeon/E2D.h"
//#include "./runDungeon/water.h"
//#include "./runDungeon/map.h"

class RunDungeon {
	private:
		Keyboard keyboard;

	protected:
		void getInput();
		void processInput();
		void update(bool shadowPass);
		void draw();
		void getHeight();
		void getJump();

	public:
		DungeonMap		map;
		//Water			water;
		//Atmosphere		atmosphere;
		//O2D 			o2d;
		//O3D_Dungeon	o3d;
		//E2D 			e2d;

		Atmosphere atmosphere;
		//Worldmap map;
		O2DD o2d;
		//O3D o3d;
		//E2D e2d;
		O3D_Dungeon o3d;
		Water water;

		RunDungeon();
		void run();
		bool load();
};

RunDungeon * Dungeon = new RunDungeon();

RunDungeon::RunDungeon(): water(atmosphere), o2d(map, atmosphere) {
	//water.iHeight = -32;
	keyboard.calc();
}

bool RunDungeon::load() {
	if (gameVars->debug.load) printf("\n\n ########################\n");
	if (gameVars->debug.load) printf("## LOADING DUNGEON ##\n");

	//################################
	//	Initialize Data Structures
	if (!map.init()) { printf("Error initializing Dungeon map.\n"); return 0; }		// CURRENTLY LOADS TEST MAP
	if (!atmosphere.init()) { printf("Error initializing sky.\n"); return 0; }
	//if (!atmosphere.skybox.init()) { printf("Error initializing sky.\n"); return 0; }
	//if (!atmosphere.sun.init()) { printf("Error initializing sky.\n"); return 0; }
	//if (!atmosphere.moon.init()) { printf("Error initializing moon.\n"); return 0; }
	//if (!atmosphere.sky.init()) { printf("Error initializing sky.\n"); return 0; }
	//if (!o3d.init()) { printf("Error initializing Dungeon o3d.\n"); return 0; }
	if (!water.init(0, -32, 0)) { printf("Error initializing water.\n"); return 0; }

	//################################
	//	Load Game Resources
	//if (!Map.load()) { printf("Error loading Dungeon map.\n"); return 0; }		// NOT IMPLEMENTED YET
	//if (!atmosphere.sky.load()) { printf("Error loading sky.\n"); return 0; }
	if (!o3d.load()) { printf("Error loading Dungeon o3d.\n"); return 0; }
	if (!atmosphere.skybox.load()) { printf("Error loading sky.\n"); return 0; }
	if (!atmosphere.sun.load()) { printf("Error loading sun.\n"); return 0; }
	if (!atmosphere.moon.load()) { printf("Error loading moon.\n"); return 0; }
	if (!water.load()) { printf("Error loading water.\n"); return 0; }

	//################################
	//	Do calculations and create the display lists
	if (!map.calc()) { printf("Error calculating Dungeon map.\n"); return 0; }		// Calculate geometry layout
	//if (!atmosphere.sky.calc()) { printf("Error calculating sky.\n"); return 0; }
	if (!o3d.calc()) { printf("Error calculating Dungeon o3d.\n"); return 0; }
	if (!atmosphere.skybox.calc()) { printf("Error calculating sky.\n"); return 0; }
	if (!atmosphere.sun.calc()) { printf("Error calculating sun.\n"); return 0; }
	if (!atmosphere.moon.calc()) { printf("Error calculating moon.\n"); return 0; }
	if (!water.calc()) { printf("Error calculating water.\n"); return 0; }
	return 1;
}

void RunDungeon::run() {
	glClear( gameVars->screen.clear );
	getInput();

	//cout << "Water Height: " << this->water.iHeight << endl;

	//Update the world content
	update(false);

	//Draw the standard debug HUD
	//if (gameVars->debug.time.debug) gameVars->timer.pTimer.start(gameSys.textSys.id["Debug"]);
	//runDebug(*gameVars);
	//if (gameVars->debug.time.debug) gameVars->timer.pTimer.stop(gameSys.textSys.id["Debug"]);

	draw();
}

void RunDungeon::update(bool shadowPass){
	//for (int i=0; i<GLS_LAST; i++) {
		//if (gameVars->shader.bCurrent[i]) {
			int i = GLS_FONT;
			Core.shader.use(i);
			Core.matrix.Push();
			//Draw Pre-Transform Geometry

			//Draw Rotation-Only Geometry
			Core.matrix.Rotate(gameVars->transform.dunRot[0], 1.0, 0.0, 0.0);
			Core.matrix.Rotate(gameVars->transform.dunRot[1], 0.0, 1.0, 0.0);

			//Draw Post-Transform Geometry
			Core.matrix.Translate(gameVars->transform.dunPos[0], gameVars->transform.dunPos[1]+gameVars->player.sheet.transform.currentHeight, gameVars->transform.dunPos[2]);
			//Core.matrix.Scale(0.5, 0.5, 0.5);
			Core.matrix.SetTransform();
			Core.shader.getUniform(i);

			//Draw the map
			glActiveTexture(GL_TEXTURE0);
			//gameVars->texture.terrain.Set("rocky_dirt.png");

			map.draw(atmosphere);

			//Draw 2D Objects
			//o2d.draw(gameVars, false);

			//Draw 3D Objects
			o3d.draw(atmosphere);
			
			//Draw 2D Event Objects
			//e2d.draw(gameVars, false);

			//Draw Water
			//Core.matrix.Translate(-1024, 0.0f, -1024);
			//Core.matrix.SetTransform();
			//Core.shader.getUniform(i);
			water.draw();

			Core.matrix.Pop();
		}
	//}
//}

void RunDungeon::draw() {
	//if(gameVars->screen.AutoFlush) glFlush();
	//if(gameVars->screen.AutoFinish) glFinish();
	//SDL_GL_SwapBuffers();
}

void RunDungeon::getInput() {
	if (gameVars->debug.lag) printf("PUMP EVENTS\n");
	//Event capturing
	SDL_PumpEvents();

	if (gameVars->debug.lag) printf("GET MOUSE STATE\n");
	//Get relative mouse movement
	SDL_GetMouseState(&gameVars->controls.mouse.x, &gameVars->controls.mouse.y);

	float tX, tY;
	tX = gameVars->controls.mouse.relX;
	tY = gameVars->controls.mouse.relY;
	gameVars->controls.mouse.relX = gameVars->controls.mouse.x-gameVars->screen.halfW;
	gameVars->controls.mouse.relY = gameVars->controls.mouse.y-gameVars->screen.halfH;
	if (gameVars->debug.mouse) printf("\nMouse: (%i, %i)", gameVars->controls.mouse.x-gameVars->screen.halfW, gameVars->controls.mouse.y-gameVars->screen.halfH);

	//if (tX != gameVars->controls.mouse.relX || tY != gameVars->controls.mouse.relY) {
		SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
		if (gameVars->controls.mouse.lock) SDL_WarpMouse(gameVars->screen.halfW, gameVars->screen.halfH);
		SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
	//}


	if (gameVars->debug.lag) printf("SHOW/HIDE CURSOR\n");
	if (gameVars->controls.mouse.hide) SDL_ShowCursor(SDL_DISABLE);
	else SDL_ShowCursor(SDL_ENABLE);

	if (gameVars->debug.lag) printf("GET KEY STATE\n");
	keyboard.event = SDL_GetKeyState(NULL);

	if (gameVars->debug.lag) printf("GET MOUSE CLICK\n");
	//if(SDL_GetMouseState(&gameVars->controls.mouse.x, &gameVars->controls.mouse.y)&SDL_BUTTON(1)) gameVars->controls.mouse.button.check[0]=true;
	//else gameVars->controls.mouse.button.check[0]=false;
	//gameSys.mouseSys.checkButton(gameVars, 0);

	//Left Mouse button
	if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)) gameVars->controls.mouse.button.check[0]=true;
	else gameVars->controls.mouse.button.check[0]=false;

	//Right Mouse button
	if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(3)) gameVars->controls.mouse.button.check[2]=true;
	else gameVars->controls.mouse.button.check[2]=false;

	if (gameVars->debug.lag) printf("EXECUTE INPUT COMMANDS\n");
	//Execute input commands
	keyboard.update();
	processInput();
	gameVars->controls.mouse.relX = 0;
	gameVars->controls.mouse.relY = 0;
}

void RunDungeon::processInput() {
	float moveMod=0.40;

	if (keyboard.bKey[gameVars->controls.key.open_journal]) { SDL_ShowCursor(SDL_ENABLE); gameVars->state.menu=true; }

	if (keyboard.bKey[gameVars->controls.key.sneak]){
		moveMod=0.40;
	}

	if (keyboard.bKey[gameVars->controls.key.run]){
		moveMod=10.00;
	}

	if (!keyboard.bKey[gameVars->controls.key.run] && !keyboard.bKey[gameVars->controls.key.sneak]) {
		moveMod=1;
	}

	//PLAYER MOVEMENT
	if (keyboard.bKey[gameVars->controls.key.strafe_left]){
		int iAirControl = 1;
		//if (gameVars->transform.dunPos[1] < gameVars->transform.groundHeight) iAirControl = 2;

		gameVars->transform.dunPos[0]+=(float)cos( gameVars->transform.dunRot[1] ) * ((gameVars->controls.moveSpeed / iAirControl)*moveMod);
		gameVars->transform.dunPos[2]+=(float)sin( gameVars->transform.dunRot[1] ) * ((gameVars->controls.moveSpeed / iAirControl)*moveMod);
	}
	if (keyboard.bKey[gameVars->controls.key.strafe_right]){
		int iAirControl = 1;
		//if (gameVars->transform.dunPos[1] < gameVars->transform.groundHeight) iAirControl = 2;

		gameVars->transform.dunPos[0]-=(float)cos( gameVars->transform.dunRot[1] ) * ((gameVars->controls.moveSpeed / iAirControl)*moveMod);
		gameVars->transform.dunPos[2]-=(float)sin( gameVars->transform.dunRot[1] ) * ((gameVars->controls.moveSpeed / iAirControl)*moveMod);
	}
	if (keyboard.bKey[gameVars->controls.key.turn_left]){
		gameVars->transform.dunRot[1]+=0.01;
	}
	if (keyboard.bKey[gameVars->controls.key.turn_right]){
		gameVars->transform.dunRot[1]-=0.01;
	}
	if (keyboard.bKey[gameVars->controls.key.move_forward]) {
		int iAirControl = 1;
		//if (gameVars->transform.dunPos[1] < gameVars->transform.groundHeight) iAirControl = 2;

		gameVars->transform.dunPos[0]-=(float)sin( gameVars->transform.dunRot[1] ) * ((gameVars->controls.moveSpeed / iAirControl)*moveMod);
		gameVars->transform.dunPos[2]+=(float)cos( gameVars->transform.dunRot[1] ) * ((gameVars->controls.moveSpeed / iAirControl)*moveMod);
	}
	if (keyboard.bKey[gameVars->controls.key.move_back]) {
		int iAirControl = 1;
		//if (gameVars->transform.dunPos[1] < gameVars->transform.groundHeight) iAirControl = 2;

		gameVars->transform.dunPos[0]+=(float)sin( gameVars->transform.dunRot[1] ) * ((gameVars->controls.moveSpeed / iAirControl) * moveMod);
		gameVars->transform.dunPos[2]-=(float)cos( gameVars->transform.dunRot[1] ) * ((gameVars->controls.moveSpeed / iAirControl) * moveMod);
	}
	if (keyboard.bKey[gameVars->controls.key.move_up]) {
		if (gameVars->controls.fly) gameVars->transform.dunPos[1]-=gameVars->controls.moveSpeed*moveMod;
	}
	if (keyboard.bKey[gameVars->controls.key.move_down]) {
		if (gameVars->controls.fly) gameVars->transform.dunPos[1]+=gameVars->controls.moveSpeed*moveMod;
	}


	if (keyboard.bKey[gameVars->controls.key.jump]) {
		//if (gameVars->transform.dunPos[1] == gameVars->transform.groundHeight) {
			//gameVars->transform.jumpPosition = 0.0;
			//gameVars->transform.jumpVelocity = 0.03;
			//gameVars->controls.jump = true;
		//}
	}

	if (keyboard.bKey[SDLK_BACKQUOTE]) {
		gameVars->state.console=true;
	}

	if (keyboard.bKey[SDLK_F1]) {
		gameVars->state.admin=true;
		SDL_ShowCursor(SDL_ENABLE);
		//gameVars->controls.mouse.lock=false;
		//gameVars->controls.mouse.hide=false;
		/*
		if (gameVars->lamp.avail) {
			if (gameVars->lamp.enable) {
				if (gameVars->debug.keyboard) printf("TURNING LAMP OFF\n");
				gameVars->lamp.enable=false;
				gameVars->lamp.loop=true;
				glDisable(GL_LIGHT1);
			}
			else {
				if (gameVars->debug.keyboard) printf("TURNING LAMP ON\n");
				gameVars->lamp.enable=true;
				gameVars->lamp.loop=true;
				glEnable(GL_LIGHT1);
			}
		}
		*/
	}
	if (keyboard.bKey[SDLK_F2]) {
		//glFinish();
		glFlush();
	}
	if (keyboard.bKey[SDLK_F3]) {
		Toggle(gameVars->state.dungeon);
		/*
		if (gameVars->screen.stereo.enable) {
			if (gameVars->debug.keyboard) printf("STEREO OFF\n");
			gameVars->screen.stereo.enable=false;
		}
		else  {
			if (gameVars->debug.keyboard) printf("STEREO ON\n");
			gameVars->screen.stereo.enable=true;
		}
		*/
	}
	if (keyboard.bKey[SDLK_F4]) {
		/*
		if (gameVars->debug.keyboard) printf("TOGGLE: Landscape Mode\n");

		if (imapMode == MODE_EXPLORE) {
			imapMode = MODE_LANDSCAPE;
			gameVars->shader.bCurrent[GLS_LINES] = true;
			gameVars->shader.bCurrent[GLS_NORMAL_LINE] = true;
			printf("TOGGLE: Landscape Mode: ON\n");
		}
		else {
			imapMode = MODE_EXPLORE;
			Core::shadow.bFinished = false;
			gameVars->shader.bCurrent[GLS_LINES] = false;
			gameVars->shader.bCurrent[GLS_NORMAL_LINE] = false;
			printf("TOGGLE: Landscape Mode: OFF\n");
		}*/
		/*
		if (!gameVars->Core::shadow.enable) {
			gameVars->shader.bCurrent[GLS_DIRECTIONAL] 			= 	false;
			gameVars->shader.bCurrent[GLS_DIR_SHADOW] 			= 	true;
			gameVars->Core::shadow.enable=true;
			update(gameVars, true);
		}
		else {
			gameVars->shader.bCurrent[GLS_DIRECTIONAL] 			= 	true;
			gameVars->shader.bCurrent[GLS_DIR_SHADOW] 			= 	false;
			static Matrix44f	mNew = { 1.0f, 0.0f, 0.0f, 0.0f,
										 0.0f, 1.0f, 0.0f, 0.0f,
										 0.0f, 0.0f, 1.0f, 0.0f,
										 0.0f, 0.0f, 0.0f, 1.0f };
			Core.matrix.SetModelView(mNew);
			gameVars->Core::shadow.enable=false;
		}
		*/
	}
	if (keyboard.bKey[SDLK_F5]) {
		gameVars->screen.clear = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
		glLineWidth(gameVars->screen.fLineWidth);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		gameVars->screen.ePolyMode = PM_FILL;
	}
	if (keyboard.bKey[SDLK_F6]) {
		gameVars->screen.clear = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
		glLineWidth(1.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		gameVars->screen.ePolyMode = PM_LINE;
	}

	if (!gameVars->screen.ePolyMode == PM_LINE) {
		if (keyboard.bKey[SDLK_EQUALS])	{ gameVars->screen.fLineWidth+=0.5; glLineWidth(gameVars->screen.fLineWidth); }
		if (keyboard.bKey[SDLK_MINUS])		{ gameVars->screen.fLineWidth-=0.5; glLineWidth(gameVars->screen.fLineWidth); }
	}

	if (keyboard.bKey[SDLK_F7]) {
		gameVars->screen.clear = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		gameVars->screen.ePolyMode = PM_POINT;
	}
	if (keyboard.bKey[SDLK_F8]) {
		/*
		if (gameVars->screen.blur.enable) {
			if (gameVars->debug.keyboard) printf("BLUR OFF\n");
			gameVars->screen.blur.enable=false;
		}
		else {
			if (gameVars->debug.keyboard) printf("BLUR ON\n");
			gameVars->screen.blur.enable=true;
		}
		*/
	}
	if (keyboard.bKey[SDLK_F9]) {
		if (gameVars->controls.fly) {
			if (gameVars->debug.keyboard) printf("FLY MODE OFF\n");
			gameVars->controls.fly=false;
		}
		else {
			if (gameVars->debug.keyboard) printf("FLY MODE ON\n");
			gameVars->controls.fly=true;
		}
	}

	if (keyboard.bKey[SDLK_F10]) {
		if (gameVars->controls.mouse.lock) {
			if (gameVars->debug.keyboard) printf("MOUSE UNLOCKED\n");
			gameVars->controls.mouse.lock=false;
		}
		else {
			if (gameVars->debug.keyboard) printf("MOUSE LOCKED\n");
			gameVars->controls.mouse.lock=true;
		}
	}

	if (keyboard.bKey[SDLK_F11]) {
		if (gameVars->controls.mouse.hide) {
			if (gameVars->debug.keyboard) printf("MOUSE SHOWN\n");
			gameVars->controls.mouse.hide=false;
		}
		else {
			if (gameVars->debug.keyboard) printf("MOUSE HIDDEN\n");
			gameVars->controls.mouse.hide=true;
		}
	}

	if (keyboard.bKey[SDLK_F12]) SDL_WM_ToggleFullScreen(Core.GlInit.screen);

	//Simulate mouse with keys
	if (!gameVars->controls.mouse.bEnable) {
		if (keyboard.bKey[gameVars->controls.key.mouse_left]) {
			gameVars->controls.mouse.relX=-1;
		}
		else if (keyboard.bKey[gameVars->controls.key.mouse_right]) {
			gameVars->controls.mouse.relX=1;
		}
		else gameVars->controls.mouse.relX=0;
		if (keyboard.bKey[gameVars->controls.key.mouse_up]) {
			gameVars->controls.mouse.relY=-1;
		}
		else if (keyboard.bKey[gameVars->controls.key.mouse_down]) {
			gameVars->controls.mouse.relY=1;
		}
		else gameVars->controls.mouse.relY=0;
	}

	if (gameVars->controls.mouse.relX<-gameVars->controls.mouse.deadX) {
		gameVars->transform.dunRot[1]+=(gameVars->controls.mouse.relX/1000)*gameVars->controls.mouse.sensX;
		if (M_RadToDeg(gameVars->transform.dunRot[1])>360) gameVars->transform.dunRot[1] = gameVars->transform.dunRot[1] - M_DegToRad(360);
		if (M_RadToDeg(gameVars->transform.dunRot[1]) < 0) gameVars->transform.dunRot[1] = gameVars->transform.dunRot[1] = M_DegToRad(360) + gameVars->transform.dunRot[1];
		if (gameVars->debug.mouse) printf("Look LEFT\n");
	}
	if (gameVars->controls.mouse.relX>gameVars->controls.mouse.deadX) {
		gameVars->transform.dunRot[1]+=(gameVars->controls.mouse.relX/1000)*gameVars->controls.mouse.sensX;
		if (M_RadToDeg(gameVars->transform.dunRot[1])>360) gameVars->transform.dunRot[1] = gameVars->transform.dunRot[1] - M_DegToRad(360);
		if (M_RadToDeg(gameVars->transform.dunRot[1]) < 0) gameVars->transform.dunRot[1] = gameVars->transform.dunRot[1] = M_DegToRad(360) + gameVars->transform.dunRot[1];
		if (gameVars->debug.mouse) printf("Look RIGHT\n");
	}
	if (gameVars->controls.mouse.relY<-gameVars->controls.mouse.deadY) {
		gameVars->transform.dunRot[0]+=(gameVars->controls.mouse.relY/1000)*gameVars->controls.mouse.sensY;
		if (gameVars->debug.mouse) printf("Look UP\n");
	}
	if (gameVars->controls.mouse.relY>gameVars->controls.mouse.deadY) {
		gameVars->transform.dunRot[0]+=(gameVars->controls.mouse.relY/1000)*gameVars->controls.mouse.sensY;
		if (gameVars->debug.mouse) printf("Look DOWN\n");
	}
}
#endif /* RUNDUNGEON_HPP_ */
