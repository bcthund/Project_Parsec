/*
 * ScriptSys.h
 *
 *  Created on: Feb 24, 2011
 *      Author: bcthund
 */

#ifndef SCRIPTFUNC_H_
#define SCRIPTFUNC_H_

GameSys::ScriptSys::ScriptSys() {
}

bool GameSys::ScriptSys::init() {
	return true;
}

bool GameSys::ScriptSys::load() {
	return true;
}

bool GameSys::ScriptSys::ShowChoice(GameVars &gameVars) {
	//gameSys.drawWindow(15,  10, 30, 5, false, true);
	gameSys.winSys.drawHDiv(2,  4, 48);
	gameSys.winSys.drawSingle(1,  4, 1,  1,   10);
	gameSys.winSys.drawSingle(50, 4, 1,  1,   11);
	gameSys.textSys.draw(2, 2, "Menu");
	if (gameSys.menuSys.draw(17, 12, "Yes"))	{ return true; }
	if (gameSys.menuSys.draw(22, 12, "No"))	{ return false; }

	return false;
}

void GameSys::ScriptSys::getInput(GameVars &gameVars) {

}

void GameSys::ScriptSys::processInput(GameVars &gameVars) {

}

void GameSys::ScriptSys::update() {

}

void GameSys::ScriptSys::draw() {

}

#endif /* SCRIPTSYS_H_ */
