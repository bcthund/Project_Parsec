/*
 * runVoid.hpp
 *
 *  Created on: Jun 13, 2010
 *      Author: bcthund
 */

#ifndef RUNSKILL_HPP_
#define RUNSKILL_HPP_

class _Skill {
	private:
		Keyboard keyboard;

		void GetInput();
		void ProcessInput();
		VAO ** vao[7];	// 268 pieces to each skill wedge total

	public:
		bool load();
		bool calc();
		void Run();
		float GetHeight();
		void Update();
		void Draw();

		_Skill() {
			keyboard.calc();
			//keyboard.calc(SDLK_c, false);

			vao[0] = new VAO*[2];
			for(int i=0; i<2; i++) vao[0][i] = new VAO[4];

			vao[1] = new VAO*[10];
			for(int i=0; i<10; i++) vao[1][i] = new VAO[16];

			vao[2] = new VAO*[8];
			for(int i=0; i<8; i++) vao[2][i] = new VAO[8];

			vao[3] = new VAO*[6];
			for(int i=0; i<6; i++) vao[3][i] = new VAO[4];

			vao[4] = new VAO*[4];
			for(int i=0; i<4; i++) vao[4][i] = new VAO[2];

			vao[5] = new VAO*[3];
			for(int i=0; i<3; i++) vao[5][i] = new VAO[1];

			vao[6] = new VAO*[1];
			for(int i=0; i<1; i++) vao[6][i] = new VAO[1];
		}

} Skill;

bool _Skill::load() {
	/*
	 * Load skill wheel wedges
	 * into approproate VAOs
	 */

	MemBlock memBlock;
	std::string theImage;

	//if (gameVars->debug.load) printf("\n ###################\n");
	//if (gameVars->debug.load) std::cout << "## LOAD SKYBOX ##" << endl;
	//skybox.tex.Begin(NUM_TEXTURES);
	//std::string	sDirectory		= "./texture/atmosphere/";
	//char * cFilename			= (char*)"skybox.bin";
	//int	iRecordSize				= 32;
	//readFile(cFilename, memBlock); //Read the data file into memory
	// Iterate through each record in the file
	//for (int d=0; d<memBlock.size; d+=iRecordSize) {
	//	int theId = 0;
	//	for (int i=0; i<4; i++) theId+=(unsigned char)memBlock.buffer[i+d];
	//	theImage = "";
	//	for (int i=4; i<32; i++) if (memBlock.buffer[i+d]!=0) theImage+=(unsigned char)memBlock.buffer[i+d]; else break;
	//	if (gameVars->debug.load) std::cout << " [" << theId << "] " <<  theImage << endl;
	//	skybox.tex.Load(sDirectory, theImage, theId, true, (GLenum)GL_NEAREST, (GLenum)GL_REPEAT);
	//}


	int i=0;
	for(int y=0; y<2; y++) {
		for(int x=0; x<4; x++) {
			std::string loadFile;
			std::stringstream sStream;
			PLY_Loader loadPly;

			sStream.str("");
			sStream << "./ply/" << i << "/" << i << "_" << y << "-" << x << ".ply";
			loadFile=sStream.str();
			//if (gameVars->debug.load) std::cout << " -Loading " <<  loadFile << "...";
			loadPly.load(loadFile);
			vao[i][y][x].Begin(GL_TRIANGLES,		loadPly.numDrawVerts, 1);
			vao[i][y][x].CopyData(GLA_VERTEX,		loadPly.vVerts);
			vao[i][y][x].CopyData(GLA_NORMAL,		loadPly.vNorms);
			vao[i][y][x].CopyData(GLA_TEXTURE,		loadPly.vCoords, 0);
			vao[i][y][x].CopyData(GLA_INDEX,		loadPly.vIndex);
			vao[i][y][x].End();
		}
	}


	/*
	{
		std::string loadFile;
		std::stringstream sStream;
		PLY_Loader loadPly;

		sStream.str("./ply/troposphere.ply");
		loadFile=sStream.str();
		//cout << "LOADING ATMOSPHERE PLY FILE: " << loadFile << endl;
		if (gameVars->debug.load) std::cout << " -Loading " <<  loadFile << "...";
		loadPly.load(loadFile);
		if (gameVars->debug.load) std::cout << "[" <<  loadPly.numDrawVerts << "]...";
		skybox.troposphere.vao.Begin(GL_TRIANGLES,		loadPly.numDrawVerts, 1);
		skybox.troposphere.vao.CopyData(GLA_VERTEX,		loadPly.vVerts);
		skybox.troposphere.vao.CopyData(GLA_NORMAL,		loadPly.vNorms);
		skybox.troposphere.vao.CopyData(GLA_TEXTURE,	loadPly.vCoords, 0);
		skybox.troposphere.vao.CopyData(GLA_INDEX,		loadPly.vIndex);
		skybox.troposphere.vao.End();
		cout << "Done" << endl;
	}
	*/

	return true;
}

bool _Skill::calc() {
	/*
	 * Currently nothing to do here
	 */
	return true;
}

//This is the primary function of this class
//This function calls all other functions in the class in the proper order
void _Skill::Run() {
	//if (!gameVars->state.battle) {
		GetInput();
	//}

	Update();
}

//This function updates the opengl pipeline with our current geometry
void _Skill::Update() {

	/*
	 * Important variable updates
	 */


	/*
	 * Draw results
	 */
	Draw();
}

void _Skill::Draw() {
	//Core.matrix.Push();
	//	Core.matrix.Rotate(gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
	//	Core.matrix.Rotate(gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
	//	Core.matrix.Scale(atmosphere.skybox.thermosphere.fScale);
	//	Core.matrix.Apply(atmosphere.water.mTransform);
	//	Core.matrix.SetTransform();
	//	Core.shader.use(GLS_THERMOSPHERE);
	//	Core.shader.getUniform(atmosphere, GLS_THERMOSPHERE);
	//	atmosphere.skybox.thermosphere.draw();
	//Core.matrix.Pop();
}

void _Skill::GetInput() {
	if (gameVars->debug.lag) printf("PUMP EVENTS\n");
	//Event capturing
	SDL_PumpEvents();

	if (gameVars->debug.lag) printf("GET MOUSE STATE\n");
	//Get relative mouse movement
	SDL_GetMouseState(&gameVars->controls.mouse.x, &gameVars->controls.mouse.y);

	//Is mouse control enabled?
	if (gameVars->controls.mouse.bEnable) {
		gameVars->controls.mouse.relX=gameVars->controls.mouse.x-gameVars->screen.halfW;
		gameVars->controls.mouse.relY=gameVars->controls.mouse.y-gameVars->screen.halfH;
		if (gameVars->debug.mouse) printf("\nMouse: (%i, %i)", gameVars->controls.mouse.x-gameVars->screen.halfW, gameVars->controls.mouse.y-gameVars->screen.halfH);

		SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
		if (gameVars->controls.mouse.lock) SDL_WarpMouse(gameVars->screen.halfW, gameVars->screen.halfH);
		SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);

		if (gameVars->debug.lag) printf("SHOW/HIDE CURSOR\n");
		if (gameVars->controls.mouse.hide) SDL_ShowCursor(SDL_DISABLE);
		else SDL_ShowCursor(SDL_ENABLE);
	}
	else SDL_ShowCursor(SDL_ENABLE);

	//gameVars->controls.keyboard.event = SDL_GetKeyState(NULL);
	keyboard.event = SDL_GetKeyState(NULL);

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
	//gameSys.keySys.repeat(gameVars->controls.keyboard.event);
	keyboard.update();
	ProcessInput();
}

void _Skill::ProcessInput() {
	if (keyboard.bKey[SDLK_ESCAPE]) {
		gameVars->state.admin=true;
		SDL_ShowCursor(SDL_ENABLE);
	}

	if (keyboard.bKey[SDLK_TAB]) {
		ToggleMouse();
	}

	if (keyboard.bKey[gameVars->controls.key.open_journal]) { SDL_ShowCursor(SDL_ENABLE); gameVars->state.book=S_JOURNAL; }

	if (keyboard.bKey[gameVars->controls.key.open_intent]) {
		SDL_ShowCursor(SDL_ENABLE);
		gameVars->state.menu=true;
		gameVars->menu.bOperations=false;
		gameVars->menu.bIntent=true;
		gameVars->menu.bStatus=true;
		gameVars->menu.bActionIcon=true;
		ToggleMouse(true);
	}

	if (keyboard.bKey[gameVars->controls.key.open_menu]) {
		SDL_ShowCursor(SDL_ENABLE);
		gameVars->state.menu=true;
		gameVars->menu.bOperations=true;
		gameVars->menu.bIntent=false;
		gameVars->menu.bStatus=false;
		gameVars->menu.bActionIcon=true;
		ToggleMouse(true);
	}

	if (keyboard.bKey[gameVars->controls.key.activate]){
	}

	if (keyboard.bKey[gameVars->controls.key.sneak]){
	}

	if (keyboard.bKey[gameVars->controls.key.run]){
	}

	if (!keyboard.bKey[gameVars->controls.key.run] && !keyboard.bKey[gameVars->controls.key.sneak]) {
	}

	if (keyboard.bKey[gameVars->controls.key.strafe_left]){
	}
	if (keyboard.bKey[gameVars->controls.key.strafe_right]){
	}

	if (keyboard.bKey[gameVars->controls.key.move_forward]) {
	}
	if (keyboard.bKey[gameVars->controls.key.move_back]) {
	}

	if (keyboard.bKey[gameVars->controls.key.change_stance]) {
	}

	if (keyboard.bKey[gameVars->controls.key.move_up]) {
	}
	if (keyboard.bKey[gameVars->controls.key.move_down]) {
	}


	if (keyboard.bKey[gameVars->controls.key.jump]) {
	}

	if (keyboard.bKey[SDLK_BACKQUOTE]) {
		gameVars->state.console=true;
	}

	if (keyboard.bKey[SDLK_EQUALS]) {
	}

	if (keyboard.bKey[SDLK_MINUS]) {
	}

	if (keyboard.bKey[SDLK_1]) {
	}

	if (keyboard.bKey[SDLK_2]) {
	}

	if (keyboard.bKey[SDLK_3]) {
	}

	if (keyboard.bKey[SDLK_4]) {
	}

	if (keyboard.bKey[SDLK_9]) {
	}

	if (keyboard.bKey[SDLK_0]) {
	}

	if (keyboard.bKey[SDLK_F1]) {
		gameVars->state.admin=true;
	}
	if (keyboard.bKey[SDLK_F2]) {
	}
	if (keyboard.bKey[SDLK_F3]) {
	}
	if (keyboard.bKey[SDLK_F4]) {
	}
	if (keyboard.bKey[SDLK_F5]) {
	}
	if (keyboard.bKey[SDLK_F6]) {
	}
	if (keyboard.bKey[SDLK_F7]) {
	}
	if (keyboard.bKey[SDLK_F8]) {
		if (gameVars->controls.mouse.bEnable) {
			gameVars->controls.mouse.bEnable = false;
		}
		else {
			gameVars->controls.mouse.bEnable = true;
		}
	}
	if (keyboard.bKey[SDLK_F9]) {
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
}
#endif /* RUNSKILL_HPP_ */
