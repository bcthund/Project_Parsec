/*
 * ScriptSys.h
 *
 *  Created on: Feb 24, 2011
 *      Author: bcthund
 */

#ifndef SCRIPTCLASS_H_
#define SCRIPTCLASS_H_

class ScriptSys {
	private:

	protected:
		void getInput(GameVars &gameVars);
		void processInput(GameVars &gameVars);
		void update();
		void draw();

	public:
		ScriptSys();
		bool init();
		bool load();
		bool ShowChoice(GameVars &gameVars);
} Script;

#endif /* SCRIPTSYS_H_ */
