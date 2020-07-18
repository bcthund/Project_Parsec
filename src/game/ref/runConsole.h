/*
 * runConsole.h
 *
 *  Created on: Jun 13, 2010
 *      Author: bcthund
 */

#ifndef RUNCONSOLE_H_
#define RUNCONSOLE_H_

class RunConsole {
	private:
		GLuint index;
		GLfloat (*pArray)[2];
		std::string loadFile;
		std::string theImage;
		std::string tempImage;
		int tempID;
		GLenum texture_format;
		GLint nOfColors;
		MemBlock memBlock;
		typedef std::map< std::string, float* > FloatList;
		typedef std::map< std::string, int* > IntList;
		typedef std::map< std::string, bool* > BoolList;
		FloatList *floatList;
		IntList *intList;
		BoolList *boolList;
		Keyboard keyboard;

	protected:
		void start(int x, int y);
		void stop();
		void update();
		void draw();
		void execScript();
		void showCommands();
		void shuffleBuffer(std::string command);

	public:
		RunConsole();
		bool init();
		bool load();
		bool calc();
		void run();
		void input();
} Console;

//RunConsole * Console = new(RunConsole);

RunConsole::RunConsole() {
	pArray = { NULL };
	tempID = 0;
	nOfColors = 0;
	index = 0;
	texture_format = GL_RGBA;
	floatList = new FloatList;
	intList = new IntList;
	boolList = new BoolList;

	keyboard.calc();
}

bool RunConsole::init() {
	return true;
}

bool RunConsole::load() {
	return true;
}

bool RunConsole::calc() {
	//Create display list for console background
	int iW = gameVars->screen.w;
	int iH = -gameVars->font.consoleLines*gameVars->font.vSize[1];

	// Create buffer area box
	Data3f *vVerts = new Data3f[6];
	vVerts[0][0] = 0.0;
	vVerts[0][1] = iH;
	vVerts[0][2] = 0.0;

	vVerts[1][0] = iW;
	vVerts[1][1] = 0.0;
	vVerts[1][2] = 0.0;

	vVerts[2][0] = 0.0;
	vVerts[2][1] = 0.0;
	vVerts[2][2] = 0.0;

	vVerts[3][0] = 0.0;
	vVerts[3][1] = iH;
	vVerts[3][2] = 0.0;

	vVerts[4][0] = iW;
	vVerts[4][1] = iH;
	vVerts[4][2] = 0.0;

	vVerts[5][0] = iW;
	vVerts[5][1] = 0.0;
	vVerts[5][2] = 0.0;

	Data2f *vTexture = new Data2f[6];
	vTexture[0][0] = 0.0;
	vTexture[0][1] = 0.875;

	vTexture[1][0] = 1.0;
	vTexture[1][1] = 0.0;

	vTexture[2][0] = 0.0;
	vTexture[2][1] = 0.0;

	vTexture[3][0] = 0.0;
	vTexture[3][1] = 0.875;

	vTexture[4][0] = 1.0;
	vTexture[4][1] = 0.875;

	vTexture[5][0] = 1.0;
	vTexture[5][1] = 0.0;

	gameVars->vao.system.console[0].Begin(GL_TRIANGLES, 6, 1);
	gameVars->vao.system.console[0].CopyData(GLA_VERTEX, vVerts);
	gameVars->vao.system.console[0].CopyData(GLA_TEXTURE, vTexture, 0);
	gameVars->vao.system.console[0].End();

	// Create text area box
	vVerts = new Data3f[6];
	vVerts[0][0] = 0.0;
	vVerts[0][1] = -gameVars->font.vSize[1];
	vVerts[0][2] = 0.0;

	vVerts[1][0] = iW;
	vVerts[1][1] = 0.0;
	vVerts[1][2] = 0.0;

	vVerts[2][0] = 0.0;
	vVerts[2][1] = 0.0;
	vVerts[2][2] = 0.0;

	vVerts[3][0] = 0.0;
	vVerts[3][1] = -gameVars->font.vSize[1];
	vVerts[3][2] = 0.0;

	vVerts[4][0] = iW;
	vVerts[4][1] = -gameVars->font.vSize[1];
	vVerts[4][2] = 0.0;

	vVerts[5][0] = iW;
	vVerts[5][1] = 0.0;
	vVerts[5][2] = 0.0;

	vTexture = new Data2f[6];
	vTexture[0][0] = 0.0;
	vTexture[0][1] = 1.0;

	vTexture[1][0] = 1.0;
	vTexture[1][1] = 0.875;

	vTexture[2][0] = 0.0;
	vTexture[2][1] = 0.875;

	vTexture[3][0] = 0.0;
	vTexture[3][1] = 1.0;

	vTexture[4][0] = 1.0;
	vTexture[4][1] = 1.0;

	vTexture[5][0] = 1.0;
	vTexture[5][1] = 0.875;

	gameVars->vao.system.console[1].Begin(GL_TRIANGLES, 6, 1);
	gameVars->vao.system.console[1].CopyData(GLA_VERTEX, vVerts);
	gameVars->vao.system.console[1].CopyData(GLA_TEXTURE, vTexture, 0);
	gameVars->vao.system.console[1].End();

	//Transform
	floatList->insert(std::make_pair("gameVars->player.active->transform.pos[0]",			&gameVars->player.active->transform.pos[0]));
	floatList->insert(std::make_pair("gameVars->player.active->transform.pos[1]",			&gameVars->player.active->transform.pos[1]));
	floatList->insert(std::make_pair("gameVars->player.active->transform.pos[2]",			&gameVars->player.active->transform.pos[2]));
	floatList->insert(std::make_pair("gameVars->player.active->transform.rot[0]",			&gameVars->player.active->transform.rot[0]));
	floatList->insert(std::make_pair("gameVars->player.active->transform.rot[1]",			&gameVars->player.active->transform.rot[1]));
	//floatList->insert(std::make_pair("gameVars->transform.yRotBB",		&gameVars->transform.yRotBB));
	//floatList->insert(std::make_pair("gameVars->transform.eyeHeight",	&gameVars->transform.eyeHeight));
	//floatList->insert(std::make_pair("gameVars->transform.heightMod",	&gameVars->transform.heightMod));
	//floatList->insert(std::make_pair("gameVars->transform.startX",		&gameVars->transform.startX));
	//floatList->insert(std::make_pair("gameVars->transform.startZ",		&gameVars->transform.startZ));

	//Sky
	intList->insert(std::make_pair(	"gameVars->sky.num", 				&gameVars->sky.num));
	floatList->insert(std::make_pair("gameVars->sky.sunDir",				&gameVars->sky.sunDir));

	//Lamp
	//boolList->insert(std::make_pair(	"gameVars->lamp.enable",			&gameVars->lamp.enable));
	//boolList->insert(std::make_pair(	"gameVars->lamp.loop",			&gameVars->lamp.loop));
	//boolList->insert(std::make_pair(	"gameVars->lamp.avail",			&gameVars->lamp.avail));

	//Light
	//floatList.insert(std::make_pair("gameVars->light.ambientLight",	&gameVars->light.startZ));
	//floatList.insert(std::make_pair("gameVars->light.startZ",			&gameVars->light.startZ));
	//floatList.insert(std::make_pair("gameVars->light.startZ",			&gameVars->light.startZ));
	//floatList.insert(std::make_pair("gameVars->light.startZ",			&gameVars->light.startZ));
	//floatList.insert(std::make_pair("gameVars->light.startZ",			&gameVars->light.startZ));
	//floatList.insert(std::make_pair("gameVars->light.startZ",			&gameVars->light.startZ));
	//intList.insert(std::make_pair(	"gameVars->light.num", 			&gameVars->light.num));
	//boolList.insert(std::make_pair(	"gameVars->light.enable",		&gameVars->light.enable));
	//boolList.insert(std::make_pair(	"gameVars->light.night",			&gameVars->light.night));

	//Dir
	//Add a stringList

	//Screen
	intList->insert(std::make_pair(	"gameVars->screen.w", 				&gameVars->screen.w));
	intList->insert(std::make_pair(	"gameVars->screen.h", 				&gameVars->screen.h));
	intList->insert(std::make_pair(	"gameVars->screen.bpp", 				&gameVars->screen.bpp));
	intList->insert(std::make_pair(	"gameVars->screen.frameRate", 		&gameVars->screen.frameRate));
	intList->insert(std::make_pair(	"gameVars->screen.halfW", 			&gameVars->screen.halfW));
	intList->insert(std::make_pair(	"gameVars->screen.halfH", 			&gameVars->screen.halfH));
	intList->insert(std::make_pair(	"gameVars->screen.clear", 			&gameVars->screen.clear));
		//Blur
		//boolList->insert(std::make_pair("gameVars->screen.blur.enable", 			&gameVars->screen.blur.enable));
		//intList->insert(std::make_pair(	"gameVars->screen.blur.passes", 			&gameVars->screen.blur.passes));
		//intList->insert(std::make_pair(	"gameVars->screen.blur.pass", 			&gameVars->screen.blur.pass));
		//Stereo
		//boolList->insert(std::make_pair("gameVars->screen.stereo.enable", 		&gameVars->screen.stereo.enable));
		//intList->insert(std::make_pair(	"gameVars->screen.stereo.passes", 		&gameVars->screen.stereo.passes));
		//intList->insert(std::make_pair(	"gameVars->screen.stereo.pass", 			&gameVars->screen.stereo.pass));

	//Controls
	boolList->insert(std::make_pair(	"gameVars->controls.fly",		&gameVars->controls.fly));
	floatList->insert(std::make_pair(	"gameVars->controls.moveSpeed",	&gameVars->controls.moveSpeed));
		//Mouse
		intList->insert(std::make_pair(	"gameVars->controls.mouse.x", 			&gameVars->controls.mouse.x));
		intList->insert(std::make_pair(	"gameVars->controls.mouse.y", 			&gameVars->controls.mouse.y));
		floatList->insert(std::make_pair("gameVars->controls.mouse.sensX",		&gameVars->controls.mouse.sensX));
		floatList->insert(std::make_pair("gameVars->controls.mouse.sensY",		&gameVars->controls.mouse.sensY));
		intList->insert(std::make_pair(	"gameVars->controls.mouse.deadX", 		&gameVars->controls.mouse.deadX));
		intList->insert(std::make_pair(	"gameVars->controls.mouse.deadY", 		&gameVars->controls.mouse.deadY));
		floatList->insert(std::make_pair("gameVars->controls.mouse.relX",		&gameVars->controls.mouse.relX));
		floatList->insert(std::make_pair("gameVars->controls.mouse.relY",		&gameVars->controls.mouse.relY));
		boolList->insert(std::make_pair(	"gameVars->controls.mouse.lock",		&gameVars->controls.mouse.lock));
		boolList->insert(std::make_pair(	"gameVars->controls.mouse.hide",		&gameVars->controls.mouse.hide));

	//Font
	//intList->insert(std::make_pair(	"gameVars->font.size", 				&gameVars->font.size));
	intList->insert(std::make_pair(	"gameVars->font.consoleLines", 		&gameVars->font.consoleLines));

	//Debug
	boolList->insert(std::make_pair(	"gameVars->debug.init",			&gameVars->debug.init));
	boolList->insert(std::make_pair(	"gameVars->debug.load",			&gameVars->debug.load));
	boolList->insert(std::make_pair(	"gameVars->debug.lamp",			&gameVars->debug.lamp));
	boolList->insert(std::make_pair(	"gameVars->debug.mouse",			&gameVars->debug.mouse));
	boolList->insert(std::make_pair(	"gameVars->debug.keyboard",		&gameVars->debug.keyboard));
	boolList->insert(std::make_pair(	"gameVars->debug.temp",			&gameVars->debug.temp));
	boolList->insert(std::make_pair(	"gameVars->debug.shadow",		&gameVars->debug.shadow));
	boolList->insert(std::make_pair(	"gameVars->debug.bb",			&gameVars->debug.bb));
	boolList->insert(std::make_pair(	"gameVars->debug.map",			&gameVars->debug.map));
	boolList->insert(std::make_pair(	"gameVars->debug.lag",			&gameVars->debug.lag));
	boolList->insert(std::make_pair(	"gameVars->debug.sky",			&gameVars->debug.sky));
	boolList->insert(std::make_pair(	"gameVars->debug.fps",			&gameVars->debug.fps));
		//Time
		boolList->insert(std::make_pair(	"gameVars->debug.time.timers",		&gameVars->debug.time.timers));
		boolList->insert(std::make_pair(	"gameVars->debug.time.load",			&gameVars->debug.time.load));
		boolList->insert(std::make_pair(	"gameVars->debug.time.gameLoop",		&gameVars->debug.time.gameLoop));
		boolList->insert(std::make_pair(	"gameVars->debug.time.debug",		&gameVars->debug.time.debug));
		boolList->insert(std::make_pair(	"gameVars->debug.time.runWorld",		&gameVars->debug.time.runWorld));
		boolList->insert(std::make_pair(	"gameVars->debug.time.input",		&gameVars->debug.time.input));
		boolList->insert(std::make_pair(	"gameVars->debug.time.gameUpdate",	&gameVars->debug.time.gameUpdate));
		boolList->insert(std::make_pair(	"gameVars->debug.time.motionBlur",	&gameVars->debug.time.motionBlur));
		boolList->insert(std::make_pair(	"gameVars->debug.time.gameDraw",		&gameVars->debug.time.gameDraw));

	//RecordSize
	intList->insert(std::make_pair(	"gameVars->recordSize.map", 			&gameVars->recordSize.map));
//	intList->insert(std::make_pair(	"gameVars->recordSize.object", 		&gameVars->recordSize.object));
	intList->insert(std::make_pair(	"gameVars->recordSize.event", 		&gameVars->recordSize.event));
	intList->insert(std::make_pair(	"gameVars->recordSize.data", 		&gameVars->recordSize.data));
	intList->insert(std::make_pair(	"gameVars->recordSize.image", 		&gameVars->recordSize.image));
	intList->insert(std::make_pair(	"gameVars->recordSize.font", 		&gameVars->recordSize.font));
	intList->insert(std::make_pair(	"gameVars->recordSize.system", 		&gameVars->recordSize.system));

	//State
	boolList->insert(std::make_pair(	"gameVars->state.quit",			&gameVars->state.quit));
	boolList->insert(std::make_pair(	"gameVars->state.console",		&gameVars->state.console));
	boolList->insert(std::make_pair(	"gameVars->state.admin",			&gameVars->state.admin));
	boolList->insert(std::make_pair(	"gameVars->state.menu",			&gameVars->state.menu));
	boolList->insert(std::make_pair(	"gameVars->state.battle",		&gameVars->state.battle));
	boolList->insert(std::make_pair(	"gameVars->state.dungeon",		&gameVars->state.dungeon));
	boolList->insert(std::make_pair(	"gameVars->state.city",			&gameVars->state.city));
	boolList->insert(std::make_pair(	"gameVars->state.world",			&gameVars->state.world));


	return true;
}

void RunConsole::start(int x, int y) {
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	Core.matrix.SetProjection(MM_ORTHO);
	Core.shader.use(GLS_FONT);
	glDisable(GL_DEPTH_TEST);
	Core.matrix.Push();
	Core.matrix.Translate( (gameVars->font.vSize[0]*x)+gameVars->font.screenCoords[0], (-gameVars->font.vSize[1]*y)+gameVars->font.screenCoords[1], 0.0 );
	gameVars->texture.system.menu.Set(0);
}

void RunConsole::stop() {
	Core.matrix.Pop();
	Core.matrix.SetProjection(MM_PERSPECTIVE);
	glEnable(GL_DEPTH_TEST);
}

void RunConsole::run() {
	//glClear( GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT );
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ACCUM_BUFFER_BIT);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glClear( GL_DEPTH_BUFFER_BIT );
	if (gameVars->debug.lag) printf("PUMP EVENTS\n");			//Get Events
	SDL_PumpEvents();
	if (gameVars->debug.lag) printf("GET MOUSE STATE\n");		//Get relative mouse movement
	SDL_GetMouseState(&gameVars->controls.mouse.x, &gameVars->controls.mouse.y);
	if (gameVars->debug.mouse) printf("\nMouse: (%i, %i)", gameVars->controls.mouse.x-gameVars->screen.halfW, gameVars->controls.mouse.y-gameVars->screen.halfH);
	SDL_ShowCursor(SDL_ENABLE);

	if (gameVars->debug.lag) printf("GET KEY STATE\n");
	keyboard.event = SDL_GetKeyState(NULL);
	//if (gameVars->controls.keyboard.event[SDLK_ESCAPE]) gameVars->state.quit=true;

	if (gameVars->debug.lag) printf("SET KEY STATE\n");

	if (gameVars->debug.lag) printf("EXECUTE INPUT COMMANDS\n");
	//Execute input commands
	keyboard.update();
	input();
	keyboard.buffer();

	//Update the screen
	update();

	//Flip buffers
	//draw();
}

void RunConsole::input() {
	if (keyboard.bKey[SDLK_RETURN]){
		execScript();
	}

	if (keyboard.bKey[SDLK_TAB]) {
		showCommands();
	}

	if (keyboard.bKey[SDLK_BACKQUOTE]){
		gameVars->state.console=false;
		SDL_WarpMouse(gameVars->screen.halfW, gameVars->screen.halfH);
	}
}

void RunConsole::update() {
	world.Update(false);

	//Draw screen capture
//		glRotatef(180, 0.0,1.0,0.0);
		//glBindTexture(GL_TEXTURE_2D, gameVars->image.consoleBG[0]);
//		glCallList(gameVars->display.system.console[0]);

	//Draw console window
		start(0, 0);
			Core.matrix.Translate(-gameVars->font.vHalfSize[0], gameVars->font.vHalfSize[1], 0.0);
			Core.matrix.SetTransform();
			Core.shader.getUniform(GLS_FONT);
			gameVars->vao.system.console[0].Draw();
		stop();
		start(0, 0);
			Core.matrix.Translate(-gameVars->font.vHalfSize[0], gameVars->font.vHalfSize[1]-gameVars->font.consoleLines*gameVars->font.vSize[1], 0.0);
			Core.matrix.SetTransform();
			Core.shader.getUniform(GLS_FONT);
			gameVars->vao.system.console[1].Draw();
		stop();

	//Draw current command
		gameSys.drawText(1, gameVars->font.consoleLines, keyboard.command);

	//Draw command buffer
		for(int l=0; l<keyboard.maxBuffer; l++) {
			if (keyboard.commandBuffer[l] != "") {
				gameSys.drawText(1, (gameVars->font.consoleLines-1)-l, keyboard.commandBuffer[l]);
			}
		}

	//Draw the standard debug HUD
	//if (gameVars->debug.time.debug) gameVars->timer.pTimer.start(gameSys.textSys.id["Debug"]);
	//if (gameVars->debug.time.debug) runDebug(*gameVars);
	//if (gameVars->debug.time.debug) gameVars->timer.pTimer.stop(gameSys.textSys.id["Debug"]);
}

void RunConsole::draw() {
	//SDL_GL_SwapBuffers();
}

void RunConsole::execScript() {
	char newCommand[48]= { 0 };
	char assign=0;
	std::string command;
	float arg[8] = { 0 };
	std::string originalCommand=keyboard.command.c_str();
	FloatList::const_iterator itFloat;
	IntList::const_iterator itInt;
	BoolList::const_iterator itBool;
	std::string::size_type loc;

	//Shuffle buffer
	shuffleBuffer(keyboard.command);

	if (originalCommand == "TOO SLOW!") {
		shuffleBuffer("Press ALT+F4 to increase your speed!");
	}

	if (originalCommand == "What the FUCK!") {
		shuffleBuffer("I KNOW! Get a grip!");
	}

	//Split the command and arguments
	sscanf(originalCommand.c_str(), "%s %c %f %f %f %f %f %f %f %f", newCommand, &assign, &arg[0], &arg[1], &arg[2], &arg[3], &arg[4], &arg[5], &arg[6], &arg[7]);
	command=(std::string)newCommand;

	if (command=="exit") gameVars->state.quit=true;

	//Find and execute command
	for (itFloat = floatList->begin(); itFloat != floatList->end(); ++itFloat) {
		loc=itFloat->first.find(command.c_str(), 0);
		if (loc == 0 && (itFloat->first.length()==command.length())) {
			if (assign == '=') *itFloat->second=arg[0];
			command.append(" = "+itoa(*itFloat->second, 10));
		}
	}

	for (itInt = intList->begin(); itInt != intList->end(); ++itInt) {
		loc=itInt->first.find(command.c_str(), 0);
		if (loc == 0 && (itInt->first.length()==command.length())) {
			if (assign == '=') *itInt->second=arg[0];
			command.append(" = "+itoa(*itInt->second, 10));
		}
	}

	for (itBool = boolList->begin(); itBool != boolList->end(); ++itBool) {
		loc=itBool->first.find(command.c_str(), 0);
		if (loc == 0 && (itBool->first.length()==command.length())) {
			if (assign == '=') *itBool->second=arg[0];
			command.append(" = "+itoa(*itBool->second, 10));
		}
	}

	keyboard.command="";
}

void RunConsole::shuffleBuffer(std::string command) {
	for (int i=keyboard.maxBuffer; i>0; i--) {
		keyboard.commandBuffer[i]=keyboard.commandBuffer[i-1];
	}
	keyboard.commandBuffer[0]=command.c_str();
}

void RunConsole::showCommands() {
	std::string storeString[100];
	FloatList::const_iterator itFloat;
	IntList::const_iterator itInt;
	BoolList::const_iterator itBool;
	std::string::size_type loc;
	int count=1;

	//Search for matching commands
	for (itFloat = floatList->begin(); itFloat != floatList->end(); ++itFloat) {
		loc=itFloat->first.find(keyboard.command.c_str(), 0);
		if (loc == 0) { storeString[count]=itFloat->first.c_str(); count++; }
	}

	for (itInt = intList->begin(); itInt != intList->end(); ++itInt) {
		loc=itInt->first.find(keyboard.command.c_str(), 0);
		if (loc == 0) { storeString[count]=itInt->first.c_str(); count++; }
	}

	for (itBool = boolList->begin(); itBool != boolList->end(); ++itBool) {
		loc=itBool->first.find(keyboard.command.c_str(), 0);
		if (loc == 0) { storeString[count]=itBool->first.c_str(); count++; }
	}

	if (count>keyboard.maxBuffer) { count=keyboard.maxBuffer-2; keyboard.commandBuffer[1]="Buffer Overflow: Too Many Commands"; }
	if (count>1) {
		for (int i=keyboard.maxBuffer; i>count-1; i--) {
			keyboard.commandBuffer[i]=keyboard.commandBuffer[i-count];
		}
		keyboard.commandBuffer[count]="    [ Commands ]";
		for (int i=0; i<count; i++) {
			keyboard.commandBuffer[i]=storeString[i];
		}
	}
	else {
		shuffleBuffer("> No commands found");
	}
}
#endif /* RUNCONSOLE_H_ */
