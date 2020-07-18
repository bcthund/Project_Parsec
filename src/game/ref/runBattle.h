/*
 * runBattle.h
 *
 *  Created on: Jul 22, 2013
 *      Author: bcthund
 */

#ifndef RUNBATTLE_H_
#define RUNBATTLE_H_

//#include "./runBattle/world.npc.h"

class RunBattle {
	private:
		bool bUpdateRound;				// Signal that the round needs to be updated, used to allow animation completion before round update
		//Battle Stages
		void Initial			(int mode, CharSheet &sheet);		// Show initial menu
		void ExecInitial		(int mode, CharSheet &sheet);
		void Move				(int mode, CharSheet &sheet);			// Show movement menu
		void ExecMove			();
		void ChangeStance		(int mode, CharSheet &sheet);
		void ExecChangeStance	(int mode);
		void Engage				(int mode, CharSheet &sheet);			// Show engage menu
		void ExecEngage			(int mode, CharSheet &sheet);
		void Attack				(int mode, CharSheet &sheet);			// Show attack menu
		void ExecAttack			(int mode);	//We need to know who is attacking who here hence the passing of "player" and "enemy"
		void ExecAttack			(int mode, CharSheet &player, unsigned int eNum);	//We need to know who is attacking who here hence the passing of "player" and "enemy"
		void UpdateCards		(CharSheet &sheet);
		void RunMagic			();			// Show magic menu
		void ExecMagic			();
		void Defend				(int mode, CharSheet &sheet);			// Show defense menu
		void ExecDefend			(int mode, CharSheet &sheet);
		void Enemy				(int mode, CharSheet &sheet);			// Enemy turn, includes defend chance
		void ExecEnemy			(int mode);
		bool Between			(int i, int a, int b);
		void UpdateRound		(bool bSkip);
		void NextTarget();

		void Message(std::string s);	// Display battle message
		void DebugMenu(CharSheet &sheet, int iPrev, int iNext);
		void EndBattle();
		void UpdateMovement(CharSheet &sheet);
		void ChangeWeapon(CharSheet &sheet);
		void ExecChangeWeapon(int mode, CharSheet &sheet);
		void ShowAttackStats(CharSheet &sheet);
		void ShowEnemyStats(CharSheet &sheet);
		void ShowPlayerStats(CharSheet &sheet);
		void ShowStats();
		std::string GetAttackStat(unsigned int iC, unsigned int iT);
		CharSheet::_Magic	TempMagic[2];
		Keyboard keyboard;

		enum _CRITICALS { CRITICAL_ZERO, CRITICAL_ONE, CRITICAL_TWO, CRITICAL_THREE, CRITICAL_FOUR };


		/*
		 * Spell Management
		 */
		void Shift_Spells(int x, int y);

		Vector4f	vTint,			//Current Tint
							vTintBase,		//Original Tint
							vSelected,		//Active selection
							vHighlight,		//Mouseover color
							vDisabled;		//Disabled interaction
		bool bNext;

	protected:
		void getInput();
		void processInput(uint key);
		void processInput();
		void update();
		void getHeight();
		void getJump();
		bool CheckDeath(CharSheet &sheet);

	public:
		void setTarget();
		void setTarget(CharSheet &sheet, CharSheet &target);
		void ResetRound();
		void ResetRound(CharSheet &sheet, bool firstLoad);
		RunBattle();
		~RunBattle() {
			//delete[] enemies;
		}
		bool bInit;
		CharSheet ** enemies;
		//CharSheet * enemies[12];																										// TODO: ONLY 12 ENEMIES CAN EXIST CURRENTLY, should be able to extend this
		//CharSheet enemies[32];
		int iPlayer;				//Cycles through players, uses BIT_Numbers
		int numEnemy;				//The number of enemies in this battle
		void run();
		void run(CharSheet &CSattacker);
		//void run(CharSheet &CSattacker, CharSheet &CStarget);
		void init(int iNum);
		void init(CharSheet &sheet, int iNum);
		void setActive();
		void setActive(CharSheet &active);
		void setActive(CharSheet &active, CharSheet &target);
		void initSheet(int mode, CharSheet &sheet);
		void initSheet(CharSheet &sheet, CharSheet &target);
		void initSheet(CharSheet &sheet);
		void initSheet(CharSheet &sheet, CharSheet &target, int iNum);
		void draw();
		void draw(CharSheet &CSattacker, CharSheet &CStarget);
} Battle;

//RunBattle * Battle = new(RunBattle);

RunBattle::RunBattle() {
	bUpdateRound = false;
	iPlayer = PLAYER;		//BIT_ZERO is player one
	bInit = false;
	bNext = false;
	numEnemy = ZERO;			//BIT_ZERO means no enemies in this battle

	enemies = nullptr;

	vTint[0]		= 1.0;
	vTint[1]		= 1.0;
	vTint[2]		= 1.0;
	vTint[3]		= 1.0;

	vTintBase[0]	= 1.0;
	vTintBase[1]	= 1.0;
	vTintBase[2]	= 1.0;
	vTintBase[3]	= 1.0;

	vHighlight[0]	= 1.0;
	vHighlight[1]	= 0.5;
	vHighlight[2]	= 0.5;
	vHighlight[3]	= 1.0;

	vSelected[0]	= 0.5;
	vSelected[1]	= 2.0;
	vSelected[2]	= 0.5;
	vSelected[3]	= 1.0;

	//Not currently used
	vDisabled[0]	= 0.5;
	vDisabled[1]	= 0.5;
	vDisabled[2]	= 0.5;
	vDisabled[3]	= 0.5;

	keyboard.calc();
}

/*
 * Initial setup of battle
 */
void RunBattle::init(int iNum) {
	numEnemy = iNum;																																													// OLD BATTLE METHOD
	enemies = new CharSheet*[iNum];																																						// OLD BATTLE METHOD
	//for(int i=0; i<32; i++) {
		//enemies[i] = new CharSheet;
		//new(&enemies[i]) CharSheet;
	//}
	//gameVars->player.active = &sheet;
}

void RunBattle::initSheet(CharSheet &sheet, CharSheet &target, int iNum) {
	//memcpy(&enemies[iNum], sheet, sizeof(CharSheet));

	enemies[iNum] = &sheet;

	//enemies[iNum] = new CharSheet(sheet);
//	new(&enemies[iNum]) CharSheet(sheet);																																			// OLD BATTLE METHOD

	//ToggleMouse(false);

	//Create a new ID for this NPC in the battle system, this is used to track targets
	enemies[iNum]->init.id = iNum;

	enemies[iNum]->status.target = &target;
	//enemies[iNum].status.iTarget = -1;

	enemies[iNum]->status.move.allow = false;
	enemies[iNum]->status.move.x = 0;
	enemies[iNum]->status.move.z = 0;
	enemies[iNum]->status.move.now = 0;
	enemies[iNum]->status.move.max = 0;

	enemies[iNum]->status.engage.attackNum = 1;

	//Get the current magic state
	TempMagic[0] = enemies[iNum]->magic;									//Active player magic settings
	TempMagic[1] = enemies[iNum]->status.target->magic;	//Target player magic settings
	//TempMagic[1] = enemies[iNum].status.target->magic;	//Target player magic settings
	enemies[iNum]->status.iState = GAME::MENU.STATE.INIT;
	enemies[iNum]->status.iExec = -1;

	//Translate the enemy (NPC) into proper position
	// We are currently randomizing the starting position
	//enemies[iNum].transform.pos[0] = -(rand() % 1025) + (gameVars->screen.iGridOffset* -1024);
	//enemies[iNum].transform.pos[2] = -(rand() % 1025) + (gameVars->screen.iGridOffset* -1024);
//	enemies[iNum]->transform.pos[0] = -enemies[iNum]->transform.pos[0] + (gameVars->screen.iGridOffset* -1024);
//	enemies[iNum]->transform.pos[2] = -enemies[iNum]->transform.pos[2] + (gameVars->screen.iGridOffset* -1024);

	/*
	 * Randomize enemy to be CLOSE to player
	 */
//	std::uniform_int_distribution<> range(-48, 48);
//	int iResult = range(RNG::eng);
//	enemies[iNum]->transform.pos[0] = gameVars->player.active->transform.pos[0] + range(RNG::eng);
//	enemies[iNum]->transform.pos[2] = gameVars->player.active->transform.pos[2] + range(RNG::eng);
//
//	enemies[iNum]->transform.pos[1] = world.map.getHeight(enemies[iNum]->transform.pos[0], enemies[iNum]->transform.pos[2]);
//	//enemies[iNum].transform.pos[0] = -enemies[iNum].transform.pos[0] + (gameVars->screen.iGridOffset* -1024);
//	//enemies[iNum].transform.pos[2] = -enemies[iNum].transform.pos[2] + (gameVars->screen.iGridOffset* -1024);
//	enemies[iNum]->transform.rot[0] = 0;
//	enemies[iNum]->transform.rot[1] = 0;
//	enemies[iNum]->transform.rot[2] = 0;

	//cout << "InitSheet[" << iNum << "]: " << enemies[iNum].init.name << endl << endl;
	//cout << "(" << enemies[iNum].transform.pos[0] << "," << enemies[iNum].transform.pos[1] << "," << enemies[iNum].transform.pos[2] << ")" << endl;
}

void RunBattle::initSheet(CharSheet &sheet) {
	//memcpy(&enemies[iNum], &sheet, sizeof(CharSheet));
	//ToggleMouse(false);

	sheet.status.target = enemies[0];
	//sheet.status.iTarget = 0;

	sheet.status.move.allow = false;
	sheet.status.move.x = 0;
	sheet.status.move.z = 0;
	sheet.status.move.now = 0;
	sheet.status.move.max = 0;

	sheet.status.engage.attackNum = 1;

	//Get the current magic state
	TempMagic[0] = sheet.magic;					//Active player magic settings
	TempMagic[1] = sheet.status.target->magic;	//Target player magic settings
	TempMagic[1] = sheet.status.target->magic;	//Target player magic settings
	sheet.status.iState = GAME::MENU.STATE.INIT;
	sheet.status.iExec = -1;

	//Translate the enemy (NPC) into proper position
	//rand() % 1025;
	// We are currently randomizing the starting position
	//enemies[iNum].transform.pos[0] = -(rand() % 1025) + (gameVars->screen.iGridOffset* -1024);
	//enemies[iNum].transform.pos[2] = -(rand() % 1025) + (gameVars->screen.iGridOffset* -1024);
	//enemies[iNum].transform.pos[1] = -world.map.getHeight(enemies[iNum].transform.pos[0], enemies[iNum].transform.pos[2]);
	//enemies[iNum].transform.pos[0] = -enemies[iNum].transform.pos[0] + (gameVars->screen.iGridOffset* -1024);
	//enemies[iNum].transform.pos[2] = -enemies[iNum].transform.pos[2] + (gameVars->screen.iGridOffset* -1024);
	//enemies[iNum].transform.rot[0] = 0;
	//enemies[iNum].transform.rot[1] = 0;
	//enemies[iNum].transform.rot[2] = 0;

	//cout << "InitSheet[" << iNum << "]: " << enemies[iNum].init.name << endl << endl;
	//cout << "(" << enemies[iNum].transform.pos[0] << "," << enemies[iNum].transform.pos[1] << "," << enemies[iNum].transform.pos[2] << ")" << endl;
}

/*
void RunBattle::initSheet(CharSheet &sheet, CharSheet &target) {
	//memcpy(&enemies[iNum], &sheet, sizeof(CharSheet));
	//ToggleMouse(false);

	sheet.status.target = &target;
	sheet.status.iTarget = -1;

	sheet.status.move.allow = false;
	sheet.status.move.x = 0;
	sheet.status.move.z = 0;
	sheet.status.move.now = 0;
	sheet.status.move.max = 0;

	sheet.status.engage.attackNum = 1;

	//Get the current magic state
	TempMagic[0] = sheet.magic;					//Active player magic settings
	TempMagic[1] = sheet.status.target->magic;	//Target player magic settings
	TempMagic[1] = sheet.status.target->magic;	//Target player magic settings
	sheet.status.iState = GAME::MENU.STATE.INIT;
	sheet.status.iExec = -1;

	//Translate the enemy (NPC) into proper position
	//rand() % 1025;
	// We are currently randomizing the starting position
	//enemies[iNum].transform.pos[0] = -(rand() % 1025) + (gameVars->screen.iGridOffset* -1024);
	//enemies[iNum].transform.pos[2] = -(rand() % 1025) + (gameVars->screen.iGridOffset* -1024);
	//enemies[iNum].transform.pos[1] = -world.map.getHeight(enemies[iNum].transform.pos[0], enemies[iNum].transform.pos[2]);
	//enemies[iNum].transform.pos[0] = -enemies[iNum].transform.pos[0] + (gameVars->screen.iGridOffset* -1024);
	//enemies[iNum].transform.pos[2] = -enemies[iNum].transform.pos[2] + (gameVars->screen.iGridOffset* -1024);
	//enemies[iNum].transform.rot[0] = 0;
	//enemies[iNum].transform.rot[1] = 0;
	//enemies[iNum].transform.rot[2] = 0;

	//cout << "InitSheet[" << iNum << "]: " << enemies[iNum].init.name << endl << endl;
	//cout << "(" << enemies[iNum].transform.pos[0] << "," << enemies[iNum].transform.pos[1] << "," << enemies[iNum].transform.pos[2] << ")" << endl;
}
*/

/*
 * Initializes the posistion data and calls an update to ResetRound to set initial
 * 		values for battle.
 *
 * Mode ONE simply means, this is a player character and our world position should be used
 * 		- We should store the players position in his character sheet at all
 * 		  times so we don't have to do this.
 *
 * Mode TWO means this is an enemy and their stored starting position should be used
 * 		- We need to correct for the current map grid, otherwise we wouldn't need this
 *
 */
/*
void RunBattle::initSheet(int mode, CharSheet &sheet) {
	if(mode == ONE) {
		ResetRound(sheet, true);
		//player is always the primary player, enemy is always the second player.
		//Holds the starting position of the player
		//sheet.transform.pos[0] = gameVars->transform.worldPos[0];
		//sheet.transform.pos[1] = gameVars->transform.worldPos[1];
		//sheet.transform.pos[2] = gameVars->transform.worldPos[2];
		//sheet.transform.rot[0] = gameVars->transform.worldRot[0];
		//sheet.transform.rot[1] = gameVars->transform.worldRot[1];
		//sheet.transform.rot[2] = gameVars->transform.worldRot[2];
	}
	else if (mode == TWO) {
		ResetRound(sheet, true);
		//Translate the enemy (NPC) into proper position
		sheet.transform.pos[0] = -sheet.transform.pos[0] + (gameVars->screen.iGridOffset* -1024);
		sheet.transform.pos[2] = -sheet.transform.pos[2] + (gameVars->screen.iGridOffset* -1024);
		sheet.transform.rot[0] = 0;
		sheet.transform.rot[1] = 0;
		sheet.transform.rot[2] = 0;
		cout << "(" << sheet.transform.pos[0] << "," << sheet.transform.pos[1] << "," << sheet.transform.pos[2] << ")" << endl;
		//bInit = true;
	}
}
*/

/*
 * Setup the new active player and target
 * This is important when the player changes
 *   target in the future
 *
 * TODO: THIS PARTICULAR OVERRIDE IS NOT CURRENTLY USED
 */
void RunBattle::setActive(CharSheet &active, CharSheet &target) {
	/*
	 * If this has already been initialized this round
	 * then do not get settings.
	 */

	if(!bNext) {
		/*
		 * Set the active player in gameVars so other systems know who is in control
		 */
		gameVars->player.active = &active;
		gameVars->player.active->status.target = &target;

		/*
		 * Set the temporary holders for magic to be applied this turn
		 */
		TempMagic[0] = gameVars->player.active->magic;					//Active player magic settings
		TempMagic[1] = gameVars->player.active->status.target->magic;	//Target player magic settings
		bNext = true;
	}
}

/*
 * In case we don't care about setting the
 *   target.
 */
void RunBattle::setActive(CharSheet &active) {
	/*
	 * If this has already been initialized this round
	 * then do not get settings.
	 */

	if(!bNext) {
		/*
		 * Set the active player in gameVars so other systems know who is in control
		 */
		gameVars->player.active = &active;
		cout << "Active player set to " << gameVars->player.active->init.name << endl;
		if(gameVars->player.active->status.target->init.isDead) {
				cout << "Target [" << gameVars->player.active->status.target->init.name << "] is dead, advancing target." << endl;
				NextTarget();
		}
		//gameVars->player.active->status.target = &target;

		/*
		 * Set the temporary holders for magic to be applied this turn
		 */
		TempMagic[0] = gameVars->player.active->magic;					//Active player magic settings
		TempMagic[1] = gameVars->player.active->status.target->magic;	//Target player magic settings
		bNext = true;
	}
}

void RunBattle::setActive() {
	/*
	 * If this has already been initialized this round
	 * then do not get settings.
	 */

	if(!bNext) {
		/*
		 * Set the active player in gameVars so other systems know who is in control
		 */
		gameVars->player.active = enemies[iPlayer];
		cout << "Active player set to " << gameVars->player.active->init.name << endl;
		if(gameVars->player.active->status.target->init.isDead) {
				cout << "Target [" << gameVars->player.active->status.target->init.name << "] is dead, advancing target." << endl;
				NextTarget();
		}
		//gameVars->player.active->status.target = &target;

		/*
		 * Set the temporary holders for magic to be applied this turn
		 */
		TempMagic[0] = gameVars->player.active->magic;					//Active player magic settings
		TempMagic[1] = gameVars->player.active->status.target->magic;	//Target player magic settings
		bNext = true;
	}
}

/*
 * Called every time a participant is loaded to set initial values
 *
 * Called at the end of turn to reset the participants values and
 * 		increase the iPlayer count, which will be the next player
 * 		in line to attack.
 *
 * In the future we should try to implement some sort of initiative
 * 		check to determine the order of each player.
 *
 * 		Concept Method 1
 * 		Initiative checks should first compare the (Sum of players)
 * 		to (Sum of enemies)	initiatives. This determines which team
 * 		goes first. Then check the teams initiatives with each other
 * 		to determine the order of each member.
 *
 * 		Concept Method 2
 * 		Use the initiative check as a "Time" counter. Every round decreses
 * 		the inititive of each player by one. If their inititive reaches zero
 * 		then it is their turn, and their initive is set back to max.
 * 		Certain actions can add to a players inititive which actually
 * 		increases the amount of time before they can go again. This is
 * 		equivelant to starting from zero and adding but it is easier to check
 * 		for zero than to check against what the players max initiative is.
 *
 * We might need to handle status effects here, at some point we need to update
 * 		the character sheets with current status effect information. However
 * 		we need to do this for each character so we might have to do this
 * 		before runBattle is called.
 */
void RunBattle::UpdateRound(bool bSkip=false) {
	if (gameVars->player.active->status.engage.attackNum > 1 && bSkip==false) {
		gameVars->player.active->status.engage.attackNum--;
		gameVars->player.active->status.iState = GAME::MENU.STATE.INTENT;
		gameVars->player.active->status.iExec = -1;
		//player.status.choice.engage = BC_ENGAGE_INIT;
		//player.status.engage.attack = BC_ATTACK_INIT;
	}
	else {
		//player.status.state = ES_INIT;
		//ResetRound(*gameVars->player.active, false);
		ResetRound();
	}
	bUpdateRound = false;
}

void RunBattle::setTarget() {
	for(int i=0; i<numEnemy; i++) {
		enemies[i]->status.target = &gameVars->player.sheet;
	}
}

void RunBattle::setTarget(CharSheet &sheet, CharSheet &target) {
	sheet.status.target = &target;
}

/*
 * This resets the current players settings for his next round
 *   and gets the next player ready by setting them active.
 *
 * This is called every time a final action is made by the
 *   current player via the intentions button.
 */
void RunBattle::ResetRound() {
	/*
	 * Hide the mouse by default
	 */
	ToggleMouse(false);

	/*
	 * Reset movement settings
	 */
	gameVars->player.active->status.move.allow = false;
	gameVars->player.active->status.move.x = 0;
	gameVars->player.active->status.move.z = 0;
	gameVars->player.active->status.move.now = 0;
	gameVars->player.active->status.move.max = 0;
	gameVars->player.active->status.engage.attackNum = 1;

	/*
	 * Allow new Active player via setActive(*)
	 * Do we really need this???
	 */
	bNext = false;

	/*
	 * If we are off balance, reduce the number of rounds value
	 */
	if(gameVars->player.active->status.effect.off_balance) gameVars->player.active->status.effect.off_balance--;

	/*
	 * Get the current magic state
	 * !!! I don't remember what this is for exactly !!!
	 */
	TempMagic[0] = gameVars->player.active->magic;					//Active player magic settings
	TempMagic[1] = gameVars->player.active->status.target->magic;	//Target player magic settings

	/*
	 * Reset the menu system selection for the player
	 * Each player has his own copy of menu interactions
	 */
	gameVars->player.active->status.iState = GAME::MENU.STATE.INIT;
	gameVars->player.active->status.iExec = -1;

	/*
	 * This currently advances through the players
	 *   in order but we want to decide on the next
	 *   player by using their current initiative.
	 *
	 * In the ResetRound() function we need to make
	 *   some sort of calculation that sets some sort
	 *   of value that determines when that character
	 *   will get a chance to take action.
	 *
	 * One possibility is to sort all the players
	 *   by their initiative check value and simply
	 *   use that as their order. But this has
	 *   limitations on taking more turns that the
	 *   enemy.
	 *
	 * Another possibility is to set a time value
	 *   based on the initiative check and whenever
	 *   that time is passed the player is allowed
	 *   to take action. This could result in multiple
	 *   characters taking action all at the same time
	 *   which might be a good thing but might require
	 *   some careful reprogramming of the active
	 *   player pointer.
	 */
	++iPlayer;
	if (iPlayer >= numEnemy) iPlayer = PLAYER;
	cout << "Player Counter = " << iPlayer << endl;

	/*
	 * Set the new active player
	 */
	if (iPlayer == PLAYER) setActive(gameVars->player.sheet);
	else setActive();
};

/*
 * This should actually be part of the setup(initSheet) portion
 *   and the above version should be used to reset the round because
 *   the only important sheet should be the active sheet.
 */
void RunBattle::ResetRound(CharSheet &sheet, bool firstLoad=false) {
	//sheet.status.mouseLook = false;
	ToggleMouse(false);

	if (firstLoad) {
		/*
		 * Default to the active player as the target
		 *
		 * We can probably add some decisions here on target
		 *   selection in the future.
		 */

		// OVERRIDES PLAYER TARGET
		// MUST SET MANUALLY FOR NOW
		//sheet.status.target = gameVars->player.active;
	}

	sheet.status.move.allow = false;
	sheet.status.move.x = 0;
	sheet.status.move.z = 0;
	sheet.status.move.now = 0;
	sheet.status.move.max = 0;

	sheet.status.engage.attackNum = 1;

	//Allow new Active player via setActive(*)
	bNext = false;

	//If we are off balance, reduce the number of rounds value
	if(sheet.status.effect.off_balance) sheet.status.effect.off_balance--;
	//Get the current magic state
	TempMagic[0] = sheet.magic;					//Active player magic settings
	if (!firstLoad) TempMagic[1] = sheet.status.target->magic;	//Target player magic settings
	//TempMagic[1] = sheet.status.target->magic;	//Target player magic settings
	sheet.status.iState = GAME::MENU.STATE.INIT;
	sheet.status.iExec = -1;
	if (!firstLoad) {
		/*
		 * This currently advances through the players
		 *   in order but we want to decide on the next
		 *   player by using their current initiative.
		 *
		 * In the ResetRound() function we need to make
		 *   some sort of calculation that sets some sort
		 *   of value that determines when that character
		 *   will get a chance to take action.
		 *
		 * One possibility is to sort all the players
		 *   by their initiative check value and simply
		 *   use that as their order. But this has
		 *   limitations on taking more turns that the
		 *   enemy.
		 *
		 * Another possibility is to set a time value
		 *   based on the initiative check and whenever
		 *   that time is passed the player is allowed
		 *   to take action. This could result in multiple
		 *   characters taking action all at the same time
		 *   which might be a good thing but might require
		 *   some careful reprogramming of the active
		 *   player pointer.
		 */
		++iPlayer;
		if (iPlayer >= numEnemy) iPlayer = PLAYER;
		cout << "Player Counter = " << iPlayer << endl;
	}

	if (iPlayer == PLAYER) setActive(gameVars->player.sheet);
	else setActive();
};

/*
 * All enemies are dead and battle has ended
 *
 * We should call the loot screen at this point, which will be
 * 		the only opportunity to loot corpses. We don't want to
 * 		store loot all over the place constantly.
 */
void RunBattle::EndBattle() {
	//delete[] enemies;
	gameVars->state.battle = false;
	gameVars->state.endBattle = true;
	gameVars->battle.newBattle = true;
	//gameVars->transform.currentHeight = gameVars->transform.eyeHeight;
	gameVars->player.active->transform.currentHeight = gameVars->player.active->transform.eyeHeight;
	gameVars->player.active = &gameVars->player.sheet;	//Set control back to the primary player
	SDL_WarpMouse(gameVars->screen.halfW, gameVars->screen.halfH);
}

/*
 * We need to check if the given character sheet signals death. If they are
 * 		dead then just simply return true so we can handle that situtation.
 *
 * We might need to add more here to manage the death of a character, such as
 * 		updating their character sheet. We might want to include an "IsDead"
 * 		boolean value for the sheet so we can avoid calling this function
 * 		in looping routines.
 * 		NOTE: isDead is already in the sheet, we just need to check for this
 * 			  in the loop before calling this function.
 */
bool RunBattle::CheckDeath(CharSheet &sheet) {
	//CHECK IF ENEMY OR PLAYER IS ALIVE! Do this before doing ANYTHING else
	if ((sheet.damage.hit_points <= 0) || (sheet.init.isDead)) {

		/*
		 * This if statement prevents re-printing the enemy is dead
		 *
		 * If the current participant is dead then we should call ResetRound to proceed
		 * 		NOTE: This should not be done here
		 *
		 * We should check if all enemies are dead, if they are then we can end the battle
		 * 		NOTE: This should not be done here
		 *
		 */
		if(sheet.init.isDead != true) {
			std::cout << "[" << sheet.init.id << "]" << sheet.init.name << " is DEAD!!!" << std::endl;
			sheet.init.isDead = true;
		}
		//EndBattle(gameVars);
		return true;
	}
	return false;
}

void RunBattle::NextTarget() {
//	cout << "Advancing Target...";
//	int iFail = gameVars->player.active->init.id;	//We don't want to target ourself
//	int iNext = gameVars->player.active->status.target->init.id+1;
//	if(iNext >= numEnemy) iNext = -1;
//	if(iNext == iFail) iNext++;
//	if(iNext == -1) gameVars->player.active->status.target = &gameVars->player.sheet;
//	else gameVars->player.active->status.target = &enemies[iNext];

	int iNext = gameVars->player.active->status.target->init.id+1;
	//int iFail = gameVars->player.active->init.id;	//We don't want to target ourself
	//if(iNext == iFail) iNext++;
	if(iNext >= numEnemy) iNext = -1;

	int iCheck = 0;
	bool bGood = false;
	while(iNext >= 0 && bGood==false) {
		if(enemies[iNext]->init.isDead) {
			cout << "? Target [" << enemies[iNext]->init.name << "] is dead, advancing target." << endl;
			iNext++;
			//if(iNext == iFail) iNext++;
			if(iNext >= numEnemy) {
					iNext = -1;
					bGood = true;
			}

			iCheck++;
			if(iCheck>numEnemy) EndBattle();		// All enemies are dead, force battle end
		}
		else bGood = true;
	}

	if(iNext == -1) gameVars->player.active->status.target = &gameVars->player.sheet;
	else gameVars->player.active->status.target = enemies[iNext];

	cout << "Targeted " << gameVars->player.active->status.target->init.name << endl;
}

//void RunBattle::run(CharSheet &CSattacker, CharSheet &CStarget) {
//void RunBattle::run(CharSheet &CSattacker) {
void RunBattle::run() {
	if(!gameSys.animationSys.isAnimating()) {		// only allow player input while not animating
//	if(gameSys.animationSys.isAnimating()) {
//		gameSys.animationSys.drawWorld();
//	}

		if(bUpdateRound) UpdateRound(false);
		/*
		 * Set the active player in gameVars so other systems know who is in control
		 */
		//gameVars->player.active = &CSattacker;
		//gameVars->player.active->status.target = &CStarget;

		/*
		 * We need to combine these CheckDeath() calls into the CheckDeath() subroutine, we want
		 * 		to automatically increase the iPlayer value if we are dead, and we want to change
		 * 		the target if the target is dead.
		 */

		if (CheckDeath(*gameVars->player.active)) {
			//cout << "This player is Dead!\n" << endl;
			UpdateRound(false);
		}
		//if (CheckDeath(*gameVars->player.active->status.target)) cout << "Enemy is dead!\n" << endl;

		/*
		 * If at least one enemy is still
		 * alive then keep running battle
		 */
		bool bAlive = false;
		for(int i=0; i<numEnemy;i++) {
			if(!CheckDeath(*enemies[i])) {
				bAlive = true;
				break;
			}
		}
		if(!bAlive) {
			EndBattle();
		}

		//draw();

		/*
		 * We need to get the input for the correct playerChar here so the proper sheets are updated
		 * We also need to run the Battle update routine with the correct sheets depending on
		 * whos turn it is.
		 */

		update();

		/*
		 * For debugging purposes we want to show all of the attack stats for the battle
		 * Currently we only show the current player and enemy one
		 * This should check for which players turn it is and draw the appropriate data in the future
		 *
		 * Note: THIS IS FOR DEBUGGING ONLY, a stripped down version will be used for real battles
		 */
		//Need to track what enemy we have selected to do these properly, for now default ot enemy1
		//ShowAttackStats(gameVars, CStarget);

		//if (gameVars->player.active->status.iState != GAME::MENU.CAST.SPELL) ShowStats();
		//ShowPlayerStats(gameVars, CSattacker);
		//ShowEnemyStats(gameVars, CStarget);

		getInput();
	}
//	} else {
//		gameSys.animationSys.drawWorld();
//	}
	//else draw();
	draw();
	if (gameVars->player.active->status.iState != GAME::MENU.CAST.SPELL) ShowStats();
}

void RunBattle::update(){
	/*
	 * Menu default color
	 * We might want to change this to be controlled better
	 */
	vTint[0] = 0.0;
	vTint[1] = 0.0;
	vTint[2] = 0.0;
	vTint[3] = 0.5;

	/*
	 * This structure checks for what the current state of battle is and calls
	 * 		the appropriate menu drawing function. This also send the proper
	 * 		data to each function so every character uses the same routines.
	 */

	//Message("Running Battle", gameVars);

	//cout << "State:" << player.status.state << endl;
	if (gameVars->player.active->status.iState==GAME::MENU.STATE.SKIP) {
		cout << "Execute Skip Intent" << endl;
		UpdateRound(true);
	}
	else if( gameVars->player.active->status.iState==GAME::MENU.STATE.INIT) {

		/*
		 * Movement change only occurrs at the beginning
		 * of the next round.
		 */
		cout << "Execute Move Intent...";
		gameVars->player.active->status.iState=GAME::MENU.STATE.INTENT;
		if (gameVars->player.active->status.iExec!=GAME::MENU.MOVE.WALK && gameVars->player.active->status.iExec!=GAME::MENU.MOVE.RUN) gameVars->player.active->status.iExec=GAME::MENU.MOVE.WALK;
		else gameVars->player.active->status.iExec = GAME::MENU.MOVE.WALK;
		ExecMove();
	}
	else if( gameVars->player.active->status.iState==GAME::MENU.MOVE.STANCE.STAND ||
			 gameVars->player.active->status.iState==GAME::MENU.MOVE.STANCE.KNEEL ||
			 gameVars->player.active->status.iState==GAME::MENU.MOVE.STANCE.SIT ||
			 gameVars->player.active->status.iState==GAME::MENU.MOVE.STANCE.PRONE ) {

		cout << "Set Stance Intent" << endl;
		gameVars->player.active->status.iIntent=GAME::MENU.INTENT.STANCE;
		gameVars->player.active->status.iState=GAME::MENU.STATE.INTENT;		//Intent Icon set waiting for confirmation
		gameVars->state.menu = true;
	}
	else if( gameVars->player.active->status.iState==GAME::MENU.INTENT.STANCE ) {
		cout << "Execute Stance Intent" << endl;
		ExecChangeStance(gameVars->player.active->status.iState);
		//UpdateRound(false);
		bUpdateRound = true;
	}
	else if( gameVars->player.active->status.iState==GAME::MENU.ENGAGE.CHOP.HIGH   ||
			 gameVars->player.active->status.iState==GAME::MENU.ENGAGE.CHOP.MID    ||
			 gameVars->player.active->status.iState==GAME::MENU.ENGAGE.CHOP.LOW    ||
			 gameVars->player.active->status.iState==GAME::MENU.ENGAGE.SWING.HIGH  ||
			 gameVars->player.active->status.iState==GAME::MENU.ENGAGE.SWING.MID   ||
			 gameVars->player.active->status.iState==GAME::MENU.ENGAGE.SWING.LOW   ||
			 gameVars->player.active->status.iState==GAME::MENU.ENGAGE.THRUST.HIGH ||
			 gameVars->player.active->status.iState==GAME::MENU.ENGAGE.THRUST.MID  ||
			 gameVars->player.active->status.iState==GAME::MENU.ENGAGE.THRUST.LOW  ) {

		cout << "Set Melee Intent" << endl;
		gameVars->player.active->status.iState=GAME::MENU.STATE.INTENT;
		gameVars->player.active->status.iIntent=GAME::MENU.INTENT.MELEE;
		gameVars->state.menu = true;
	}
	else if( gameVars->player.active->status.iState==GAME::MENU.INTENT.MELEE ) {
		cout << "Exec Melee Intent" << endl;
		if(gameVars->player.active->status.engage.attackNum > 0) {
			ExecAttack(gameVars->player.active->status.iExec);	//WE ARE FORCED TO ATTACK ENEMY1 RIGHT NOW
			//UpdateRound(false);
			bUpdateRound = true;
		}
		else {
			cout << "No attacks left!";
			if (gameVars->player.active->status.move.iSpeed == GAME::MENU.MOVE.RUN) {
				cout << " Cannot attack while running!" << endl;
			}
			else cout << endl;

			gameVars->player.active->status.iState==GAME::MENU.INTENT.INIT;
		}
	}
	else if( gameVars->player.active->status.iState==GAME::MENU.CAST.SPELL) {
		gameVars->player.active->status.iIntent=GAME::MENU.INTENT.CAST_SPELL;
		//gameVars->player.active->status.iState=GAME::MENU.STATE.INTENT;
		RunMagic();
	}
	else if (gameVars->player.active->status.iState==GAME::MENU.INTENT.CAST_SPELL) {
		cout << "Exec Magic Intent" << endl;
		ExecMagic();
		//UpdateRound(false);
		bUpdateRound = true;
	}
}

/*
 * This is used to determine what range a value is in and is currently only used to
 * 		display the proper text for limb damages. This will be used for "Card"
 * 		information in the future if we use cards or some other similar system.
 */
bool RunBattle::Between(int i, int a, int b) {
	if (i >= a) {
		if (i <= b) {
			return true;
		}
		else return false;
	}
	else return false;
}

#include "./runBattle/debug.h"

void RunBattle::ExecMove() {
	//cout << "mode:" << mode << endl;
	//gameVars->player.active->status.choice.move = mode;
	gameVars->player.active->status.move.now = 0;
	//gameVars->player.active->status.move.x = gameVars->transform.worldPos[0];
	//gameVars->player.active->status.move.z = gameVars->transform.worldPos[2];
	gameVars->player.active->status.move.x = gameVars->player.active->transform.pos[0];
	gameVars->player.active->status.move.z = gameVars->player.active->transform.pos[2];
	gameVars->player.active->status.move.allow = false;

	/*
	 * Are we set to walking or running?
	 */
	if(gameVars->player.active->status.move.iSpeed == GAME::MENU.MOVE.WALK) {
		cout << "walking" << endl;
		if (gameVars->player.active->status.effect.off_balance) gameVars->player.active->status.move.max = gameVars->player.active->mod.moveDistance/2;
		else gameVars->player.active->status.move.max = gameVars->player.active->mod.moveDistance;
		gameVars->player.active->status.move.allow = true;
		gameVars->player.active->status.engage.attackNum = 1;
		gameVars->player.active->status.move.fMoveMod = 1.0;		//THIS SHOULD BE SET ACCORDING TO PLAYER STATS
		SDL_WarpMouse(gameVars->screen.halfW, gameVars->screen.halfH);
	}
	else if(gameVars->player.active->status.move.iSpeed == GAME::MENU.MOVE.RUN) {
		cout << "running" << endl;
		if (gameVars->player.active->status.effect.off_balance) gameVars->player.active->status.move.max = gameVars->player.active->mod.moveDistance;
		else gameVars->player.active->status.move.max = gameVars->player.active->mod.moveDistance*2;
		gameVars->player.active->status.move.allow = true;
		gameVars->player.active->status.engage.attackNum = 0;
		gameVars->player.active->status.move.fMoveMod = 2.0;		//THIS SHOULD BE SET ACCORDING TO PLAYER STATS
		SDL_WarpMouse(gameVars->screen.halfW, gameVars->screen.halfH);
	}


	/*
	if (gameVars->player.active->status.iExec==GAME::MENU.MOVE.WALK) {
			cout << "walking" << endl;
			if (gameVars->player.active->status.effect.off_balance) gameVars->player.active->status.move.max = gameVars->player.active->mod.moveDistance/2;
			else gameVars->player.active->status.move.max = gameVars->player.active->mod.moveDistance;
			gameVars->player.active->status.move.iSpeed = GAME::MENU.MOVE.WALK;

			gameVars->player.active->status.move.allow = true;
			//gameVars->player.active->status.mouseLook = true;

			//ToggleMouse(true);

			gameVars->player.active->status.engage.attackNum = 1;
			gameVars->player.active->status.move.fMoveMod = 1.0;		//THIS SHOULD BE SET ACCORDING TO PLAYER STATS
			SDL_WarpMouse(gameVars->screen.halfW, gameVars->screen.halfH);
	}
	else if (gameVars->player.active->status.iExec==GAME::MENU.MOVE.RUN) {
			cout << "running" << endl;
			if (gameVars->player.active->status.effect.off_balance) gameVars->player.active->status.move.max = gameVars->player.active->mod.moveDistance;
			else gameVars->player.active->status.move.max = gameVars->player.active->mod.moveDistance*2;
			gameVars->player.active->status.move.iSpeed = GAME::MENU.MOVE.RUN;

			gameVars->player.active->status.move.allow = true;
			//gameVars->player.active->status.mouseLook = true;
			//ToggleMouse(true);

			gameVars->player.active->status.engage.attackNum = 0;
			gameVars->player.active->status.move.fMoveMod = 2.0;		//THIS SHOULD BE SET ACCORDING TO PLAYER STATS
			SDL_WarpMouse(gameVars->screen.halfW, gameVars->screen.halfH);
	}
	*/

		/*
		case BC_MOVE_STANCE:
			gameVars->player.active->status.engage.attackNum = 1;
			gameVars->player.active->status.mouseLook = false;
			gameVars->player.active->status.move.max = 0;
		break;
		case BC_MOVE_FORGO:
			gameVars->player.active->status.engage.attackNum = 2;
			gameVars->player.active->status.mouseLook = false;
			gameVars->player.active->status.move.max = 0;
			gameVars->player.active->status.state = BC_STATE_ENGAGE;
		break;
		*/
}

void RunBattle::ExecChangeStance(int mode) {
	cout << "Changing Stance...";

	/*
	 * Movement not allowed after making a stance change
	 */
	//gameVars->player.active->status.engage.attackNum = 1;
	gameVars->player.active->status.move.max = 0;

	/*
	 * Apply the appropriate stance change
	 */
	if (mode==GAME::MENU.MOVE.STANCE.STAND) {
			cout << "Standing" << endl;
			//gameVars->transform.currentHeight = gameVars->transform.eyeHeight;
			gameVars->player.active->transform.currentHeight = gameVars->player.active->transform.eyeHeight;
			gameVars->player.active->status.move.iStance = GAME::MENU.MOVE.STANCE.STAND;
	}
	else if (mode==GAME::MENU.MOVE.STANCE.KNEEL) {
			cout << "Kneeling" << endl;
			//gameVars->transform.currentHeight = gameVars->transform.eyeHeight/2;
			gameVars->player.active->transform.currentHeight = gameVars->player.active->transform.eyeHeight/2;
			gameVars->player.active->status.move.iStance = GAME::MENU.MOVE.STANCE.KNEEL;
	}
	else if (mode==GAME::MENU.MOVE.STANCE.SIT) {
			cout << "Sitting" << endl;
			//gameVars->transform.currentHeight = gameVars->transform.eyeHeight/3;
			gameVars->player.active->transform.currentHeight = gameVars->player.active->transform.eyeHeight/3;
			gameVars->player.active->status.move.iStance = GAME::MENU.MOVE.STANCE.SIT;
	}
	else if (mode==GAME::MENU.MOVE.STANCE.PRONE) {
			cout << "Going Prone" << endl;
			//gameVars->transform.currentHeight = -1;
			gameVars->player.active->transform.currentHeight = 1;
			gameVars->player.active->status.move.iStance = GAME::MENU.MOVE.STANCE.PRONE;
	}
}

void RunBattle::ExecChangeWeapon(int mode, CharSheet &sheet) {
	//sheet.inventory.equipped.equipment.iRight_Hand = mode;
	//sheet.status.choice.engage = BC_ENGAGE_INIT;
	//sheet.status.engage.attack = BC_ATTACK_INIT;
}

void RunBattle::ExecAttack(int mode) {
	cout << "======================================" << endl;
	//CALCULATE ENEMY DISTANCE FROM PLAYER AND STORE

	CharSheet & player = *gameVars->player.active;
	CharSheet & enemy = *gameVars->player.active->status.target;

	struct Pos {
		Vector3f enemy, player;
		float d;
	} pos;

	pos.enemy[0] = enemy.transform.pos[0];
	pos.enemy[1] = enemy.transform.pos[1];
	pos.enemy[2] = enemy.transform.pos[2];

	cout << "Enemy: " << pos.enemy[0] << ", " << pos.enemy[1] << ", " << pos.enemy[2] << endl;

//	int iGx = player.transform.pos[0]-(uint(player.transform.pos[0]/1024)*1024),
//			iGz = player.transform.pos[0]-(uint(player.transform.pos[2]/1024)*1024);

//	int iGx = player.transform.pos[0]/1024.0f,
//			iGy = player.transform.pos[1],
//			iGz = player.transform.pos[2]/1024.0f;
//
//	cout << "Grid: " << iGx << ", " << iGy << ", " << iGz << endl;
//
//	iGx = iGx * 1024;
//	iGy = iGy/gameVars->screen.iScale;
//	iGz = iGz * 1024;
//
//	cout << "Grid: " << iGx << ", " << iGy << ", " << iGz << endl;
//
//	iGx = player.transform.pos[0] - iGx;
//	//iGy = player.transform.pos[1] - iGy;
//	iGz = player.transform.pos[2] - iGz;
//
//	cout << "Grid: " << iGx << ", " << iGy << ", " << iGz << endl;

	pos.player[0] = player.transform.pos[0];
	pos.player[1] = player.transform.pos[1];
	pos.player[2] = player.transform.pos[2];

//	pos.player[0] = iGx;
//	pos.player[1] = iGy;
//	pos.player[2] = iGz;

	cout << "Player: " << pos.player[0] << ", " << pos.player[1] << ", " << pos.player[2] << endl;

	if (pos.enemy[0]<0) pos.enemy[0]*=-1;
	if (pos.enemy[1]<0) pos.enemy[1]*=-1;
	if (pos.enemy[2]<0) pos.enemy[2]*=-1;

	if (pos.player[0]<0) pos.player[0]*=-1;
	if (pos.player[1]<0) pos.player[1]*=-1;
	if (pos.player[2]<0) pos.player[2]*=-1;

	Vector3f tP;
	//tP[0] = abs(player.transform.pos[0])-abs(enemy.transform.pos[0]);
	//tP[1] = abs(player.transform.pos[1])-abs(enemy.transform.pos[1]);
	//tP[2] = abs(player.transform.pos[2])-abs(enemy.transform.pos[2]);

	tP[0] = pos.player[0]-pos.enemy[0];
	tP[1] = pos.player[1]-pos.enemy[1];
	tP[2] = pos.player[2]-pos.enemy[2];
	pos.d = sqrt(sqr(tP[0])+sqr(tP[1])+sqr(tP[2]))/16;

	//printf("player: %f %f %f\n", pos.player[0], pos.player[1], pos.player[2]);
	//printf("enemy: %f %f %f\n", pos.enemy[0], pos.enemy[1], pos.enemy[2]);
	printf("Distance: %f\n", pos.d);

	//Check reach
	//if (pos.d <= gameVars->weapon[gameVars->items[player.inventory.equipped.equipment.iRight_Hand].iTypeId].range) {
	if (pos.d <= gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].weapon->range) {
		//Determine enemy defense

		//Check of "defense" skill vs attack style (chop, swing, thrust)
		//If success, then failed hit

		//if hit success, Determine limb that was hit
		int	iHead, iTorso, iArm, iLeg, a, b ,c;
		enemy.status.engage.limbHit = DAMAGE_NONE;
		if (mode==GAME::MENU.ENGAGE.CHOP.HIGH) {
				//Dodge
				cout << "Mode: Chop, High" << endl;
				iHead  = 50;
				iTorso = 35;
				iArm   = 10;
				iLeg   = 5;
		}
		else if (mode==GAME::MENU.ENGAGE.CHOP.MID) {
				//Dodge
				cout << "Mode: Chop, Mid" << endl;
				iHead  = 10;
				iTorso = 50;
				iArm   = 35;
				iLeg   = 5;
		}
		else if (mode==GAME::MENU.ENGAGE.CHOP.LOW) {
				//Dodge
				cout << "Mode: Chop, Low" << endl;
				iHead  = 5;
				iTorso = 20;
				iArm   = 10;
				iLeg   = 65;
		}
		else if (mode==GAME::MENU.ENGAGE.SWING.HIGH) {
				//Block
				cout << "Mode: Swing, High" << endl;
				iHead  = 50;
				iTorso = 20;
				iArm   = 20;
				iLeg   = 10;
		}
		else if (mode==GAME::MENU.ENGAGE.SWING.MID) {
				//Block
				cout << "Mode: Swing, Mid" << endl;
				iHead  = 10;
				iTorso = 50;
				iArm   = 30;
				iLeg   = 10;
		}
		else if (mode==GAME::MENU.ENGAGE.SWING.LOW) {
				//Block
				cout << "Mode: Swing, Low" << endl;
				iHead  = 5;
				iTorso = 20;
				iArm   = 10;
				iLeg   = 65;
		}
		else if (mode==GAME::MENU.ENGAGE.THRUST.HIGH) {
				//Deflect
				cout << "Mode: Thrust, High" << endl;
				iHead  = 60;
				iTorso = 20;
				iArm   = 15;
				iLeg   = 5;
		}
		else if (mode==GAME::MENU.ENGAGE.THRUST.MID) {
				//Deflect
				cout << "Mode: Thrust, Mid" << endl;
				iHead  = 10;
				iTorso = 65;
				iArm   = 20;
				iLeg   = 5;
		}
		else if (mode==GAME::MENU.ENGAGE.THRUST.LOW) {
				//Deflect
				cout << "Mode: Thrust, Low" << endl;
				iHead  = 5;
				iTorso = 10;
				iArm   = 5;
				iLeg   = 70;
		}

		int r = rand()%100;
		//Determine which limb was hit
		a=iHead; b=iHead+iTorso; c=iHead+iTorso+iArm;

		if ((r>=0)&&(r<a)) enemy.status.engage.limbHit |= DAMAGE_LIMB_HEAD;
		if ((r>=a)&&(r<b)) enemy.status.engage.limbHit |= DAMAGE_LIMB_TORSO;
		if ((r>=b)&&(r<c)) enemy.status.engage.limbHit |= DAMAGE_LIMB_ARM;
		if ((r>=c)) enemy.status.engage.limbHit |= DAMAGE_LIMB_LEG;

		r = rand()%2;
		//Determine left/ride side if leg or arm was hit
		if ((enemy.status.engage.limbHit & DAMAGE_LIMB_ARM) || (enemy.status.engage.limbHit & DAMAGE_LIMB_LEG)) {
			if (r == 0) enemy.status.engage.limbHit|=DAMAGE_LIMB_LEFT;
			else enemy.status.engage.limbHit|=DAMAGE_LIMB_RIGHT;
		}

		r = rand()%2;
		//Determine if upper or lower leg/arm was hit
		if ((enemy.status.engage.limbHit & DAMAGE_LIMB_ARM) || (enemy.status.engage.limbHit & DAMAGE_LIMB_LEG)) {
			if (r == 0) enemy.status.engage.limbHit|=DAMAGE_LIMB_UPPER;
			else enemy.status.engage.limbHit|=DAMAGE_LIMB_LOWER;
		}

		string sLimb = "";
		switch(enemy.status.engage.limbHit) {
				case (DAMAGE_LIMB_ARM+DAMAGE_LIMB_LEFT+DAMAGE_LIMB_UPPER):	sLimb = "Upper Left Arm";		break;
				case (DAMAGE_LIMB_ARM+DAMAGE_LIMB_RIGHT+DAMAGE_LIMB_UPPER):	sLimb = "Upper Right Arm";	break;
				case (DAMAGE_LIMB_ARM+DAMAGE_LIMB_LEFT+DAMAGE_LIMB_LOWER):	sLimb = "Lower Left Arm";		break;
				case (DAMAGE_LIMB_ARM+DAMAGE_LIMB_RIGHT+DAMAGE_LIMB_LOWER):	sLimb = "Lower Right Arm";	break;
				case (DAMAGE_LIMB_LEG+DAMAGE_LIMB_LEFT+DAMAGE_LIMB_UPPER):	sLimb = "Upper Left Leg";		break;
				case (DAMAGE_LIMB_LEG+DAMAGE_LIMB_RIGHT+DAMAGE_LIMB_UPPER):	sLimb = "Upper Right Leg";	break;
				case (DAMAGE_LIMB_LEG+DAMAGE_LIMB_LEFT+DAMAGE_LIMB_LOWER):	sLimb = "Lower Left Leg";		break;
				case (DAMAGE_LIMB_LEG+DAMAGE_LIMB_RIGHT+DAMAGE_LIMB_LOWER):	sLimb = "Lower Right Leg";	break;
				case (DAMAGE_LIMB_HEAD):																		sLimb = "Head";							break;
				case (DAMAGE_LIMB_TORSO):																		sLimb = "Torso";						break;
			}
		cout << "Limb Check = [r:" << r << "][a:" << a << " b:" << b << " c:" << c << "]" << " >> " << sLimb << endl;

		int iCurrentArmor[5] = {0};

		switch (enemy.status.engage.limbHit) {
			case (DAMAGE_LIMB_HEAD):
				iCurrentArmor[0] = enemy.inventory.equipped.base.iHead;									// Natural Armor
				iCurrentArmor[1] = enemy.inventory.equipped.vestment.iHead;							// Vestment
				iCurrentArmor[2] = enemy.inventory.equipped.quilted.iHead;							// Quilted
				iCurrentArmor[3] = enemy.inventory.equipped.maille.iHead;								// Maille
				iCurrentArmor[4] = enemy.inventory.equipped.plate.iHead;								// Plate
				break;

			case (DAMAGE_LIMB_TORSO):
				iCurrentArmor[0] = enemy.inventory.equipped.base.iTorso;
				iCurrentArmor[1] = enemy.inventory.equipped.vestment.iTorso;
				iCurrentArmor[2] = enemy.inventory.equipped.quilted.iTorso;
				iCurrentArmor[3] = enemy.inventory.equipped.maille.iTorso;
				iCurrentArmor[4] = enemy.inventory.equipped.plate.iTorso;
				break;

			case (DAMAGE_LIMB_ARM + DAMAGE_LIMB_LEFT + DAMAGE_LIMB_UPPER):
				iCurrentArmor[0] = enemy.inventory.equipped.base.iLeft_Arm;
				iCurrentArmor[1] = enemy.inventory.equipped.vestment.iLeft_Arm;
				iCurrentArmor[2] = enemy.inventory.equipped.quilted.iLeft_Arm;
				iCurrentArmor[3] = enemy.inventory.equipped.maille.iLeft_Arm;
				iCurrentArmor[4] = enemy.inventory.equipped.plate.iLeft_Arm;
				break;

			case (DAMAGE_LIMB_ARM + DAMAGE_LIMB_LEFT + DAMAGE_LIMB_LOWER):
				iCurrentArmor[0] = enemy.inventory.equipped.base.iLeft_Hand;
				iCurrentArmor[1] = enemy.inventory.equipped.vestment.iLeft_Hand;
				iCurrentArmor[2] = enemy.inventory.equipped.quilted.iLeft_Hand;
				iCurrentArmor[3] = enemy.inventory.equipped.maille.iLeft_Hand;
				iCurrentArmor[4] = enemy.inventory.equipped.plate.iLeft_Hand;
				break;

			case (DAMAGE_LIMB_ARM + DAMAGE_LIMB_RIGHT + DAMAGE_LIMB_UPPER):
				iCurrentArmor[0] = enemy.inventory.equipped.base.iRight_Arm;
				iCurrentArmor[1] = enemy.inventory.equipped.vestment.iRight_Arm;
				iCurrentArmor[2] = enemy.inventory.equipped.quilted.iRight_Arm;
				iCurrentArmor[3] = enemy.inventory.equipped.maille.iRight_Arm;
				iCurrentArmor[4] = enemy.inventory.equipped.plate.iRight_Arm;
				break;

			case (DAMAGE_LIMB_ARM + DAMAGE_LIMB_RIGHT + DAMAGE_LIMB_LOWER):
				iCurrentArmor[0] = enemy.inventory.equipped.base.iRight_Hand;
				iCurrentArmor[1] = enemy.inventory.equipped.vestment.iRight_Hand;
				iCurrentArmor[2] = enemy.inventory.equipped.quilted.iRight_Hand;
				iCurrentArmor[3] = enemy.inventory.equipped.maille.iRight_Hand;
				iCurrentArmor[4] = enemy.inventory.equipped.plate.iRight_Hand;
				break;

			case (DAMAGE_LIMB_LEG + DAMAGE_LIMB_LEFT + DAMAGE_LIMB_UPPER):
				iCurrentArmor[0] = enemy.inventory.equipped.base.iLeft_Leg;
				iCurrentArmor[1] = enemy.inventory.equipped.vestment.iLeft_Leg;
				iCurrentArmor[2] = enemy.inventory.equipped.quilted.iLeft_Leg;
				iCurrentArmor[3] = enemy.inventory.equipped.maille.iLeft_Leg;
				iCurrentArmor[4] = enemy.inventory.equipped.plate.iLeft_Leg;
				break;

			case (DAMAGE_LIMB_LEG + DAMAGE_LIMB_LEFT + DAMAGE_LIMB_LOWER):
				iCurrentArmor[0] = enemy.inventory.equipped.base.iLeft_Foot;
				iCurrentArmor[1] = enemy.inventory.equipped.vestment.iLeft_Foot;
				iCurrentArmor[2] = enemy.inventory.equipped.quilted.iLeft_Foot;
				iCurrentArmor[3] = enemy.inventory.equipped.maille.iLeft_Foot;
				iCurrentArmor[4] = enemy.inventory.equipped.plate.iLeft_Foot;
				break;

			case (DAMAGE_LIMB_LEG + DAMAGE_LIMB_RIGHT + DAMAGE_LIMB_UPPER):
				iCurrentArmor[0] = enemy.inventory.equipped.base.iRight_Leg;
				iCurrentArmor[1] = enemy.inventory.equipped.vestment.iRight_Leg;
				iCurrentArmor[2] = enemy.inventory.equipped.quilted.iRight_Leg;
				iCurrentArmor[3] = enemy.inventory.equipped.maille.iRight_Leg;
				iCurrentArmor[4] = enemy.inventory.equipped.plate.iRight_Leg;
				break;

			case (DAMAGE_LIMB_LEG + DAMAGE_LIMB_RIGHT + DAMAGE_LIMB_LOWER):
				iCurrentArmor[0] = enemy.inventory.equipped.base.iRight_Foot;
				iCurrentArmor[1] = enemy.inventory.equipped.vestment.iRight_Foot;
				iCurrentArmor[2] = enemy.inventory.equipped.quilted.iRight_Foot;
				iCurrentArmor[3] = enemy.inventory.equipped.maille.iRight_Foot;
				iCurrentArmor[4] = enemy.inventory.equipped.plate.iRight_Foot;
				break;
		}

		//Determine enemy armor protection
		int iZero, iOne, iTwo, iThree, iFour;
		//printf("TYPE: %i...", gameVars->weapon[gameVars->items[player.inventory.equipped.equipment.iRight_Hand].iTypeId].type);
		int iResistanceLevel = 0;
		cout << "Attackers Weapon: " << gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].weapon->name << endl;
		cout << "Weapon Damage Type: ";
		switch(gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].weapon->type) {
			case GAME::WEAPON.TYPE.BLADE:
				cout << "Blade" << endl;
				iResistanceLevel = 0;

				if(iCurrentArmor[4] > -1) {
					/*
					 * Primary resistance levels
					 */
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[4]].id].armor->blade;

cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[4]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					/*
					 * If wearing Plate armor AND wearing Maille
					 *   If the Maille has a bonus for THIS weapon
					 *     Determine if the bonus is full or half
					 *       If Half bonus then average current Resistance + Next Resistance (Let decimal drop w/o rounding)
					 *         Increase Plate Resistance Level for THIS weapon
					 */
					if(iCurrentArmor[3] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->bBonus & ARMOR_BONUS_BLADE) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->bFull[BLADE];
cout << "  Maille Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					/*
					 * If wearing Plate armor AND wearing Quilted
					 *   If the Quilted has a bonus for THIS weapon
					 *     Determine if the bonus is full or half
					 *       If Half bonus then average current Resistance + Next Resistance (Let decimal drop w/o rounding)
					 *         Increase Plate Resistance Level for THIS weapon
					 */
					if(iCurrentArmor[2] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bBonus & ARMOR_BONUS_BLADE) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bFull[BLADE];
cout << "  Quilted Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					/*
					 * If wearing Plate armor AND wearing Vestments
					 *   If the Vestment has a bonus for THIS weapon
					 *     Determine if the bonus is full or half
					 *       If Half bonus then average current Resistance + Next Resistance (Let decimal drop w/o rounding)
					 *         Increase Plate Resistance Level for THIS weapon
					 */
					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_BLADE) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[BLADE];
cout << "  Vestment Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					/*
					 *
					 * If wearing Plate armor AND wearing Natural (always true)
					 *   If the Natural has a bonus for THIS weapon
					 *     Determine if the bonus is full or half
					 *       If Half bonus then average current Resistance + Next Resistance (Let decimal drop w/o rounding)
					 *         Increase Plate Resistance Level for THIS weapon
					 */
					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_BLADE) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[BLADE];
cout << "  Natural Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[3] > -1) {
					/*
					 * Primary resistance levels
					 */
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->blade;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					/*
					 * If wearing Maille armor AND wearing Quilted
					 *   If the Quilted has a bonus for THIS weapon
					 *     Determine if the bonus is full or half
					 *       If Half bonus then average current Resistance + Next Resistance (Let decimal drop w/o rounding)
					 *         Increase Maille Resistance Level for THIS weapon
					 */
					if(iCurrentArmor[2] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bBonus & ARMOR_BONUS_BLADE) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bFull[BLADE];
cout << "  Quilted Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					/*
					 * If wearing Maille armor AND wearing Vestments
					 *   If the Vestment has a bonus for THIS weapon
					 *     Determine if the bonus is full or half
					 *       If Half bonus then average current Resistance + Next Resistance (Let decimal drop w/o rounding)
					 *         Increase Maille Resistance Level for THIS weapon
					 */
					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_BLADE) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[BLADE];
cout << "  Vestment Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					/*
					 * If wearing Maille armor AND wearing Natural (always true)
					 *   If the Natural has a bonus for THIS weapon
					 *     Determine if the bonus is full or half
					 *       If Half bonus then average current Resistance + Next Resistance (Let decimal drop w/o rounding)
					 *         Increase Maille Resistance Level for THIS weapon
					 */
					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_BLADE) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[BLADE];
cout << "  Natural Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[2] > -1) {
					/*
					 * Primary resistance levels
					 */
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->blade;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					/*
					 * If wearing Quilted armor AND wearing Vestments
					 *   If the Vestment has a bonus for THIS weapon
					 *     Determine if the bonus is full or half
					 *       If Half bonus then average current Resistance + Next Resistance (Let decimal drop w/o rounding)
					 *         Increase Quilted Resistance Level for THIS weapon
					 */
					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_BLADE) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[BLADE];
cout << "  Vestment Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					/* If wearing Quilted armor AND wearing Natural (always true)
					 *   If the Natural has a bonus for THIS weapon
					 *     Determine if the bonus is full or half
					 *       If Half bonus then average current Resistance + Next Resistance (Let decimal drop w/o rounding)
					 *         Increase Quilted Resistance Level for THIS weapon
					 */
					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_BLADE) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[BLADE];
cout << "  Natural Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[1] > -1) {
					/*
					 * Primary resistance levels
					 */
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->blade;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					/*
					 * If wearing Vestments AND wearing Natural (always true)
					 *   If the Natural has a bonus for THIS weapon
					 *     Determine if the bonus is full or half
					 *       If Half bonus then average current Resistance + Next Resistance (Let decimal drop w/o rounding)
					 *         Increase Vestments Resistance Level for THIS weapon
					 */
					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_BLADE) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[BLADE];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else {
					/*
					 * Primary resistance levels
					 */
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->blade;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
				}
				break;
			case GAME::WEAPON.TYPE.BLUNT:
				cout << "Blunt" << endl;
				iResistanceLevel = 0;

				if(iCurrentArmor[4] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[4]].id].armor->blunt;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[4]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					if(iCurrentArmor[3] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->bBonus & ARMOR_BONUS_BLUNT) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->bFull[BLUNT];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[2] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bBonus & ARMOR_BONUS_BLUNT) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bFull[BLUNT];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_BLUNT) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[BLUNT];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_BLUNT) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[BLUNT];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[3] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->blunt;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					if(iCurrentArmor[2] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bBonus & ARMOR_BONUS_BLUNT) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bFull[BLUNT];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_BLUNT) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[BLUNT];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_BLUNT) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[BLUNT];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[2] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->blunt;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_BLUNT) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[BLUNT];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_BLUNT) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[BLUNT];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[1] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->blunt;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_BLUNT) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[BLUNT];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->blunt;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
				}

				break;
			case GAME::WEAPON.TYPE.AXE:
				cout << "Axe" << endl;
				iResistanceLevel = 0;

				if(iCurrentArmor[4] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[4]].id].armor->axe;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[4]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					if(iCurrentArmor[3] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->bBonus & ARMOR_BONUS_AXE) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->bFull[AXE];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[2] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bBonus & ARMOR_BONUS_AXE) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bFull[AXE];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_AXE) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[AXE];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_AXE) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[AXE];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[3] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->axe;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					if(iCurrentArmor[2] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bBonus & ARMOR_BONUS_AXE) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bFull[AXE];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_AXE) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[AXE];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_AXE) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[AXE];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[2] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->axe;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_AXE) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[AXE];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_AXE) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[AXE];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[1] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->axe;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_AXE) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[AXE];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->axe;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
				}

				break;
			case GAME::WEAPON.TYPE.SPEAR:
				cout << "Spear" << endl;
				iResistanceLevel = 0;

				if(iCurrentArmor[4] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[4]].id].armor->spear;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[4]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					if(iCurrentArmor[3] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->bBonus & ARMOR_BONUS_SPEAR) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->bFull[SPEAR];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[2] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bBonus & ARMOR_BONUS_SPEAR) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bFull[SPEAR];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_SPEAR) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[SPEAR];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_SPEAR) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[SPEAR];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[3] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->spear;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					if(iCurrentArmor[2] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bBonus & ARMOR_BONUS_SPEAR) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bFull[SPEAR];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_SPEAR) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[SPEAR];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_SPEAR) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[SPEAR];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[2] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->spear;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_SPEAR) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[SPEAR];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_SPEAR) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[SPEAR];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[1] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->spear;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_SPEAR) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[SPEAR];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->spear;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
				}

				break;
			case GAME::WEAPON.TYPE.ARROW:
				cout << "Arrow" << endl;
				iResistanceLevel = 0;

				if(iCurrentArmor[4] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[4]].id].armor->arrow;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[4]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					if(iCurrentArmor[3] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->bBonus & ARMOR_BONUS_ARROW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->bFull[ARROW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[2] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bBonus & ARMOR_BONUS_ARROW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bFull[ARROW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_ARROW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[ARROW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_ARROW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[ARROW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[3] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->arrow;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					if(iCurrentArmor[2] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bBonus & ARMOR_BONUS_ARROW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bFull[ARROW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_ARROW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[ARROW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_ARROW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[ARROW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[2] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->arrow;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_ARROW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[ARROW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_ARROW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[ARROW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[1] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->arrow;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_ARROW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[ARROW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->arrow;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
				}

				break;
			case GAME::WEAPON.TYPE.JAW:
				cout << "Jaw" << endl;
				iResistanceLevel = 0;

				if(iCurrentArmor[4] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[4]].id].armor->jaw;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[4]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					if(iCurrentArmor[3] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->bBonus & ARMOR_BONUS_JAW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->bFull[JAW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[2] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bBonus & ARMOR_BONUS_JAW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bFull[JAW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_JAW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[JAW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_JAW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[JAW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[3] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->jaw;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					if(iCurrentArmor[2] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bBonus & ARMOR_BONUS_JAW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bFull[JAW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_JAW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[JAW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_JAW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[JAW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[2] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->jaw;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_JAW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[JAW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_JAW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[JAW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[1] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->jaw;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_JAW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[JAW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->jaw;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
				}

				break;
			case GAME::WEAPON.TYPE.CLAW:
				cout << "Claw" << endl;
				iResistanceLevel = 0;

				if(iCurrentArmor[4] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[4]].id].armor->claw;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[4]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					if(iCurrentArmor[3] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->bBonus & ARMOR_BONUS_CLAW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->bFull[CLAW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[2] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bBonus & ARMOR_BONUS_CLAW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bFull[CLAW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_CLAW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[CLAW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_CLAW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[CLAW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[3] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->claw;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					if(iCurrentArmor[2] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bBonus & ARMOR_BONUS_CLAW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bFull[CLAW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_CLAW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[CLAW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_CLAW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[CLAW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[2] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->claw;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_CLAW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[CLAW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_CLAW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[CLAW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[1] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->claw;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_CLAW) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[CLAW];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->claw;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
				}

				break;
			case GAME::WEAPON.TYPE.HAND:
				cout << "Hand" << endl;
				iResistanceLevel = 0;

				if(iCurrentArmor[4] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[4]].id].armor->hand;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[4]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					if(iCurrentArmor[3] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->bBonus & ARMOR_BONUS_HAND) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->bFull[HAND];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[2] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bBonus & ARMOR_BONUS_HAND) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bFull[HAND];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_HAND) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[HAND];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_HAND) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[HAND];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[3] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->hand;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[3]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					if(iCurrentArmor[2] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bBonus & ARMOR_BONUS_HAND) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->bFull[HAND];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_HAND) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[HAND];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_HAND) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[HAND];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[2] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->hand;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[2]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;

					if(iCurrentArmor[1] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bBonus & ARMOR_BONUS_HAND) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->bFull[HAND];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}

					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_HAND) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[HAND];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else if(iCurrentArmor[1] > -1) {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->hand;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[1]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
					if(iCurrentArmor[0] > -1) {
						if(gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bBonus & ARMOR_BONUS_HAND) {
							iResistanceLevel += gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->bFull[HAND];
cout << "  Bonus Applied[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
						}
					}
				}
				else {
					iResistanceLevel  = gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->hand;
cout << "  Starting Resistance[" << gameVars->items[enemy.inventory.list[iCurrentArmor[0]].id].armor->name << "]: " << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << endl;
				}

				break;
			default:
				cout << "NONE" << endl;
				break;
		}

		iZero  = GAME::ARMOR.RESISTANCE[iResistanceLevel][CRITICAL_ZERO];
		iOne   = GAME::ARMOR.RESISTANCE[iResistanceLevel][CRITICAL_ONE];
		iTwo   = GAME::ARMOR.RESISTANCE[iResistanceLevel][CRITICAL_TWO];
		iThree = GAME::ARMOR.RESISTANCE[iResistanceLevel][CRITICAL_THREE];
		iFour  = GAME::ARMOR.RESISTANCE[iResistanceLevel][CRITICAL_FOUR];

		//Determine Weapon Limitations
		cout << "Attack Motion: ";
		int maxCritical, limb_1, limb_2, limb_3, limb_4, damage;
		if (mode==GAME::MENU.ENGAGE.CHOP.HIGH || mode==GAME::MENU.ENGAGE.CHOP.MID || mode==GAME::MENU.ENGAGE.CHOP.LOW) {
			maxCritical = gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].weapon->chop;
			cout << "Chop: Max = ";
		}
		else if (mode==GAME::MENU.ENGAGE.SWING.HIGH || mode==GAME::MENU.ENGAGE.SWING.MID || mode==GAME::MENU.ENGAGE.SWING.LOW) {
			maxCritical = gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].weapon->swing;
			cout << "Swing: Max = ";
		}
		else if (mode==GAME::MENU.ENGAGE.THRUST.HIGH || mode==GAME::MENU.ENGAGE.THRUST.MID || mode==GAME::MENU.ENGAGE.THRUST.LOW) {
			maxCritical = gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].weapon->thrust;
			cout << "Thrust: Max = ";
		}
		else {
			cout << "MAX NOT SET!!! ERROR! No damage will be done. [mode = " << mode << "] : ";
		}

		string sMxCrit = "";
		switch (maxCritical) {
			case DAMAGE_CRITICAL_ONE:		sMxCrit = "Critical One";		break;
			case DAMAGE_CRITICAL_TWO:		sMxCrit = "Critical Two";		break;
			case DAMAGE_CRITICAL_THREE:	sMxCrit = "Critical Three";	break;
			case DAMAGE_CRITICAL_FOUR:	sMxCrit = "Critical Four";		break;
		}
		cout << sMxCrit << endl;

		limb_1 = gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].weapon->limb_1;
		limb_2 = gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].weapon->limb_2;
		limb_3 = gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].weapon->limb_3;
		limb_4 = gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].weapon->limb_4;
		damage = gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].weapon->damage;

		//Caclulate critical hit
		r = rand()%100;
		enemy.status.engage.iCritical = DAMAGE_NONE;

		a=iOne; b=iOne+iTwo; c=iOne+iTwo+iThree;
		cout << "Critical Check = [r:" << r << "][a:" << a << " b:" << b << " c:" << c << "] >> ";
		if ((r>=0)&&(r<a)) {
			cout << "DAMAGE_CRITICAL_ONE" << endl;
			enemy.status.engage.iCritical = DAMAGE_CRITICAL_ONE;
		}
		else if ((r>=a)&&(r<b)) {
			cout << "DAMAGE_CRITICAL_TWO" << endl;
			enemy.status.engage.iCritical = DAMAGE_CRITICAL_TWO;
		}
		else if ((r>=b)&&(r<c)) {
			cout << "DAMAGE_CRITICAL_THREE" << endl;
			enemy.status.engage.iCritical = DAMAGE_CRITICAL_THREE;
		}
		else if ((r>=c)) {
			cout << "DAMAGE_CRITICAL_FOUR" << endl;
			enemy.status.engage.iCritical = DAMAGE_CRITICAL_FOUR;
		}

		//Check critical against weapon limitations and modify accordingly
		if (enemy.status.engage.iCritical > maxCritical) enemy.status.engage.iCritical = maxCritical;

		enemy.status.engage.applyLimbDamage = 0;
		enemy.status.engage.applyHealthDamage = 0;
		//Find actual damage
		cout << "Capped Critical Type: ";
		switch(enemy.status.engage.iCritical) {
			case DAMAGE_CRITICAL_ONE:
				cout << "One" << endl;
				enemy.status.engage.applyLimbDamage		= limb_1;
				enemy.status.engage.applyHealthDamage	= damage + limb_1;
				break;
			case DAMAGE_CRITICAL_TWO:
				cout << "Two" << endl;
				enemy.status.engage.applyLimbDamage		= limb_2;
				enemy.status.engage.applyHealthDamage	= damage + limb_2;
				break;
			case DAMAGE_CRITICAL_THREE:
				cout << "Three" << endl;
				enemy.status.engage.applyLimbDamage		= limb_3;
				enemy.status.engage.applyHealthDamage	= damage + limb_3;
				break;
			case DAMAGE_CRITICAL_FOUR:
				cout << "Four" << endl;
				enemy.status.engage.applyLimbDamage		= limb_4;
				enemy.status.engage.applyHealthDamage	= damage + limb_4;
				break;
			default:
				cout << "NONE" << endl;
				break;
		}

		/*
		 * Extra Limb Damage from weapon Die and Face
		 */
		cout << "Initial Limb Damage Value: " << enemy.status.engage.applyLimbDamage << endl;
		for(int i=0; i < gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].weapon->die; i++) {
			std::uniform_int_distribution<> rand(0, gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].weapon->face);
			int iRand = rand(RNG::eng);

			enemy.status.engage.applyLimbDamage   += iRand;
			enemy.status.engage.applyHealthDamage += iRand;

			cout << "Bonus damage applied, Die #" << i << ": " << iRand << endl;
		}
		cout << "Final Limb Damage Value: " << enemy.status.engage.applyLimbDamage << endl;

		/*
		 * Chance to Defend
		 * We need to calculate the defense characteristics
		 * 		depending on what mode of defense the target is in.
		 *
		 * If the character is off-balance, and a second off-balance occurs, then
		 * 		we should set the off-bablance rounds to zero and set the stance
		 * 		to "knockdown", i.e. "prone".
		 *
		 * Weapon speed is a special value that is attacked here in the Chance to Defend
		 * 		section. It is based on the weight of the weapon and the strength of the
		 * 		attacker resulting in the speed the attacker can actually swing the weapon.
		 *
		 * Dodge:	self.skill.dodge							[+	Items/Effects]		vs.		attacker.weapon.speed (attacker.strength / weapon.weight[kg] = 20)
		 * Deflect: self.skill.deflect	+	self.weapon.weight	[+	Items/Effects]		vs.		attacker.weapon.weight + attacker.finesse
		 * Block:	self.skill.block	+	self.speed			[+	Items/Effects]		vs.		attacker.weapon.speed + attacker.finesse
		 *
		 */
		int ctdRand = rand() % 101;
		enum _CTD { CTD_NONE=0, CTD_DODGE=1, CTD_DEFLECT=2, CTD_BLOCK=4 };
		int ctdSuccess = CTD_NONE;

		/*
		 * Enemy is not in defense mode therefore:
		 *   -fail to defend
		 *   -no off_balance time
		 */
		cout << "Chance to defend...";
		if (enemy.status.defense.iMode==GAME::MENU.DEFENSE.NONE) {
			cout << "No defense" << endl;
			player.status.effect.off_balance = 0;
			ctdSuccess = CTD_NONE;
		}

		/*
		 * Enemy has a defensive stance
		 */
		/*
		 * THE WEIGHT HAS BEEN MOVED TO THE ITEM DEFINITION
		 *   AND THE CODE NEEDS TO BE REDONE TO LOOK AT THE
		 *   ITEM IN THE CHARACTERS INVENTORY INSTEAD OF THE
		 *   BASE WEAPON DATA.
		 *
		 *  TODO: These commands can be simplified by taking the 0.75 modifier and setting that value into
		 *  			a variable in the if statements. Then just multiply that modifier in the standard if
		 *  			statement. This should allow the simplification of the ctdSuccess if necessary and also
		 *  			allows the sound effect to be played here.
		 */
		if (enemy.status.defense.iMode==GAME::MENU.DEFENSE.DODGE) {
			cout << "Dodging...";
			if (ctdRand < ((float)enemy.skills.id[CS.SKILL.DODGE]/(float)enemy.skills.rankMod)*100) {
				if (player.status.effect.off_balance) {
					if (enemy.skills.id[CS.SKILL.DODGE] > ((float)player.attributes.str.strength/((float)gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].iWeight/1000)*0.75)) {
						player.status.effect.off_balance = 0;
						cout << "Success...Attacker stance changed.";
						ExecChangeStance(GAME::MENU.MOVE.STANCE.KNEEL);
						ctdSuccess = CTD_DODGE;
					}
					//else cout << "Failed.";
				}
				else {
					if (enemy.skills.id[CS.SKILL.DODGE] > ((float)player.attributes.str.strength/((float)gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].iWeight/1000))) {
						player.status.effect.off_balance = 2;
						cout << "Success...Attacker knocked off balance.";
						ctdSuccess = CTD_DODGE;
					}
					//else cout << "Failed.";
				}
			}
			//else cout << "Fail?";
			//cout << endl;
		}
		else if (enemy.status.defense.iMode==GAME::MENU.DEFENSE.DEFLECT) {
			cout << "Deflecting...";
			if (ctdRand < ((float)enemy.skills.id[CS.SKILL.DEFLECT]/(float)enemy.skills.rankMod)*100) {
				if (player.status.effect.off_balance) {
					if ((enemy.skills.id[CS.SKILL.DEFLECT]+gameVars->items[enemy.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].iWeight) > ((gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].iWeight+player.attributes.fin.mod))*0.75) {
						player.status.effect.off_balance = 0;
						cout << "Success...Attacker stance changed.";
						ExecChangeStance(GAME::MENU.MOVE.STANCE.KNEEL);
						ctdSuccess = CTD_DEFLECT;
					}
					//else cout << "Failed.";
				}
				else {
					if ((enemy.skills.id[CS.SKILL.DEFLECT]+gameVars->items[enemy.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].iWeight) > (gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].iWeight+player.attributes.fin.mod)) {
						player.status.effect.off_balance = 2;
						cout << "Success...Attacker knocked off balance.";
						ctdSuccess = CTD_DEFLECT;
					}
					//else cout << "Failed.";
				}
			}
			//else cout << "Fail?";
			//cout << endl;
		}
		else if (enemy.status.defense.iMode==GAME::MENU.DEFENSE.BLOCK) {
			cout << "Blocking...";
			if (ctdRand < ((float)enemy.skills.id[CS.SKILL.BLOCK]/(float)enemy.skills.rankMod)*100) {
				//cout << "Target: " << (enemy.skills.id[CS.SKILL.BLOCK]+enemy.stats.speedMod) << endl;
				//cout << "Attacker: " << (((float)player.attributes.str.strength/((float)gameVars->weapon[gameVars->items[player.inventory.equipped.equipment.iRight_Hand].iTypeId].weight/1000))+player.attributes.fin.mod) << endl;
				if (player.status.effect.off_balance) {
					if ((enemy.skills.id[CS.SKILL.BLOCK]+enemy.stats.speedMod) > (((float)player.attributes.str.strength/((float)gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].iWeight/1000))+player.attributes.fin.mod)*0.75) {
						++player.status.effect.off_balance;
						cout << "Success...Off balance increased.";
						ctdSuccess = CTD_BLOCK;
					}
					//else cout << "Failed.";
				}
				else {
					if ((enemy.skills.id[CS.SKILL.BLOCK]+enemy.stats.speedMod) > (((float)player.attributes.str.strength/((float)gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].iWeight/1000))+player.attributes.fin.mod)) {
						player.status.effect.off_balance = 2;
						cout << "Success...Attacker knocked off balance.";
						ctdSuccess = CTD_BLOCK;
					}
					//else cout << "Failed.";
				}
			}
			//else cout << "Fail?";
			cout << endl;
		}

		if(ctdSuccess&CTD_DODGE) {
			//cout << "Playing Dodge sound effect." << endl;
			//gameSys.audioSys.playSound(gameSys.audioSys.SOUNDS.BATTLE.DODGE);
			gameSys.playAnimation(enemy.init.w, enemy.init.h, player.transform.pos, enemy.transform.pos, gameSys.animationSys.ANIMATIONS.DODGE, 1, 10, &gameSys.audioSys.SOUNDS.BATTLE.DODGE);
		}
		else if(ctdSuccess&CTD_DEFLECT) {
			//cout << "Playing Deflect sound effect." << endl;
			//gameSys.audioSys.playSound(gameSys.audioSys.SOUNDS.BATTLE.DEFLECT);
			gameSys.playAnimation(enemy.init.w, enemy.init.h, player.transform.pos, enemy.transform.pos, gameSys.animationSys.ANIMATIONS.DEFLECT, 1, 10, &gameSys.audioSys.SOUNDS.BATTLE.DEFLECT);
		}
		else if(ctdSuccess&CTD_BLOCK) {
			//cout << "Playing Block sound effect." << endl;
			//gameSys.audioSys.playSound(gameSys.audioSys.SOUNDS.BATTLE.BLOCK);
			//gameSys.animationSys.startAnimation(enemy.init.w, enemy.init.h, player.transform.pos, enemy.transform.pos, gameSys.animationSys.ANIMATIONS.BLOCK, 1, 30);
			gameSys.playAnimation(enemy.init.w, enemy.init.h, player.transform.pos, enemy.transform.pos, gameSys.animationSys.ANIMATIONS.BLOCK, 1, 30, &gameSys.audioSys.SOUNDS.BATTLE.BLOCK);
		}

		/*
		 * Chance to Glance
		 * IFF Chance to defend fails, we calculate if a glance occurs.
		 * [weapon vs. armor]
		 */
		if(ctdSuccess == CTD_NONE) {
			cout << "Failed!" << endl;	//Chance to Defend failed
			cout << "Chance to Glance...";
			float fGlance = 0;
			int iCrit = 0;

			switch(enemy.status.engage.iCritical) {
				case DAMAGE_CRITICAL_ONE:
					iCrit = 0;
					break;
				case DAMAGE_CRITICAL_TWO:
					iCrit = 1;
					break;
				case DAMAGE_CRITICAL_THREE:
					iCrit = 2;
					break;
				case DAMAGE_CRITICAL_FOUR:
					iCrit = 3;
					break;
			}

			enemy.status.engage.iType = gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].weapon->type;
			switch(enemy.status.engage.iType) {
			case (GAME::WEAPON.TYPE.BLADE):
				fGlance = GAME::ARMOR.RESISTANCE[iResistanceLevel][iCrit] * gameVars->items[enemy.inventory.list[iCurrentArmor[iCrit]].id].armor->glance;
				break;
			case (GAME::WEAPON.TYPE.BLUNT):
				fGlance = GAME::ARMOR.RESISTANCE[iResistanceLevel][iCrit] * gameVars->items[enemy.inventory.list[iCurrentArmor[iCrit]].id].armor->glance;
				break;
			case (GAME::WEAPON.TYPE.AXE):
				fGlance = GAME::ARMOR.RESISTANCE[iResistanceLevel][iCrit] * gameVars->items[enemy.inventory.list[iCurrentArmor[iCrit]].id].armor->glance;
				break;
			case (GAME::WEAPON.TYPE.SPEAR):
				fGlance = GAME::ARMOR.RESISTANCE[iResistanceLevel][iCrit] * gameVars->items[enemy.inventory.list[iCurrentArmor[iCrit]].id].armor->glance;
				break;
			case (GAME::WEAPON.TYPE.ARROW):
				fGlance = GAME::ARMOR.RESISTANCE[iResistanceLevel][iCrit] * gameVars->items[enemy.inventory.list[iCurrentArmor[iCrit]].id].armor->glance;
				break;
			case (GAME::WEAPON.TYPE.JAW):
				fGlance = GAME::ARMOR.RESISTANCE[iResistanceLevel][iCrit] * gameVars->items[enemy.inventory.list[iCurrentArmor[iCrit]].id].armor->glance;
				break;
			case (GAME::WEAPON.TYPE.CLAW):
				fGlance = GAME::ARMOR.RESISTANCE[iResistanceLevel][iCrit] * gameVars->items[enemy.inventory.list[iCurrentArmor[iCrit]].id].armor->glance;
				break;
			case (GAME::WEAPON.TYPE.HAND):
				fGlance = GAME::ARMOR.RESISTANCE[iResistanceLevel][iCrit] * gameVars->items[enemy.inventory.list[iCurrentArmor[iCrit]].id].armor->glance;
				break;
			}
			//fGlance = 50;

			int ctgRand = rand() % 101;
			cout << "[res=" << GAME::ARMOR.RESISTANCE[iResistanceLevel][iCrit] << ", fGlance=" << fGlance << ", ctgRand=" << ctgRand << "]...";

			if (ctgRand < fGlance) {
				ctdSuccess = true;
				cout << "Attack Glanced! No damage done...Defender off balance!" << endl;
				//gameSys.audioSys.playSound(gameSys.audioSys.SOUNDS.BATTLE.GLANCE);
				//gameSys.animationSys.startAnimation(enemy.init.w, enemy.init.h, player.transform.pos, enemy.transform.pos, gameSys.animationSys.ANIMATIONS.GLANCE, 1, 30);
				gameSys.playAnimation(enemy.init.w, enemy.init.h, player.transform.pos, enemy.transform.pos, gameSys.animationSys.ANIMATIONS.GLANCE, 1, 30, &gameSys.audioSys.SOUNDS.BATTLE.GLANCE);
				player.status.effect.off_balance = 2;
			}
			else cout << "Failed." << endl;
		}

		if (!ctdSuccess)	//Was a chance to defend successful?
		{
			//Apply damage!!!
			printf("Apply Damage...");

			//#0: 100
			//#1: 80-99
			//#2: 50-79
			//#3:  1-49
			//#4:  0
			/*
			 * Most of the code below is for keeping track of attack types and
			 * 	updating the attack history. We might be able to make this
			 * 	simpler in the future.
			 */

			switch(enemy.status.engage.limbHit) {
				case (DAMAGE_LIMB_ARM+DAMAGE_LIMB_LEFT+DAMAGE_LIMB_UPPER):
					enemy.damage.limb.left_arm[UPPER].durability -= enemy.status.engage.applyLimbDamage;
					if (enemy.damage.limb.left_arm[UPPER].durability < 0) enemy.damage.limb.left_arm[UPPER].durability = 0;
					printf("Upper Left Arm Damaged\n");
					break;
				case (DAMAGE_LIMB_ARM+DAMAGE_LIMB_RIGHT+DAMAGE_LIMB_UPPER):
					enemy.damage.limb.right_arm[UPPER].durability -= enemy.status.engage.applyLimbDamage;
					if (enemy.damage.limb.right_arm[UPPER].durability < 0) enemy.damage.limb.right_arm[UPPER].durability = 0;
					printf("Upper Right Arm Damaged\n");
					break;
				case (DAMAGE_LIMB_ARM+DAMAGE_LIMB_LEFT+DAMAGE_LIMB_LOWER):
					enemy.damage.limb.left_arm[LOWER].durability -= enemy.status.engage.applyLimbDamage;
					if (enemy.damage.limb.left_arm[LOWER].durability < 0) enemy.damage.limb.left_arm[LOWER].durability = 0;
					printf("Lower Left Arm Damaged\n");
					break;
				case (DAMAGE_LIMB_ARM+DAMAGE_LIMB_RIGHT+DAMAGE_LIMB_LOWER):
					enemy.damage.limb.right_arm[LOWER].durability -= enemy.status.engage.applyLimbDamage;
					if (enemy.damage.limb.right_arm[LOWER].durability < 0) enemy.damage.limb.right_arm[LOWER].durability = 0;
					printf("Lower Right Arm Damaged\n");
					break;
				case (DAMAGE_LIMB_LEG+DAMAGE_LIMB_LEFT+DAMAGE_LIMB_UPPER):
					enemy.damage.limb.left_leg[UPPER].durability -= enemy.status.engage.applyLimbDamage;
					//enemy.damage.limb.left_leg[UPPER].weapon = player.inventory.equipped.equipment.iRight_Hand;
					if (enemy.damage.limb.left_leg[UPPER].durability < 0) enemy.damage.limb.left_leg[UPPER].durability = 0;
					//if ((enemy.damage.limb.left_leg[UPPER].durability<100)&&(enemy.damage.limb.left_leg[UPPER].durability>=80)) enemy.damage.limb.left_leg[UPPER].status[ZERO] = player.inventory.equipped.equipment.iRight_Hand;
					//else if ((enemy.damage.limb.left_leg[UPPER].durability<80)&&(enemy.damage.limb.left_leg[UPPER].durability>=50)) enemy.damage.limb.left_leg[UPPER].status[ONE] = player.inventory.equipped.equipment.iRight_Hand;
					//else if ((enemy.damage.limb.left_leg[UPPER].durability<50)&&(enemy.damage.limb.left_leg[UPPER].durability>=1)) enemy.damage.limb.left_leg[UPPER].status[TWO] = player.inventory.equipped.equipment.iRight_Hand;
					//else if ((enemy.damage.limb.left_leg[UPPER].durability<1)) enemy.damage.limb.left_leg[UPPER].status[THREE] = player.inventory.equipped.equipment.iRight_Hand;
					printf("Upper Left Leg Damaged\n");
					break;
				case (DAMAGE_LIMB_LEG+DAMAGE_LIMB_RIGHT+DAMAGE_LIMB_UPPER):
					enemy.damage.limb.right_leg[UPPER].durability -= enemy.status.engage.applyLimbDamage;
					//enemy.damage.limb.right_leg[UPPER].weapon = player.inventory.equipped.equipment.iRight_Hand;
					if (enemy.damage.limb.right_leg[UPPER].durability < 0) enemy.damage.limb.right_leg[UPPER].durability = 0;
					//if ((enemy.damage.limb.right_leg[UPPER].durability<100)&&(enemy.damage.limb.right_leg[UPPER].durability>=80)) enemy.damage.limb.right_leg[UPPER].status[ZERO] = player.inventory.equipped.equipment.iRight_Hand;
					//else if ((enemy.damage.limb.right_leg[UPPER].durability<80)&&(enemy.damage.limb.right_leg[UPPER].durability>=50)) enemy.damage.limb.right_leg[UPPER].status[ONE] = player.inventory.equipped.equipment.iRight_Hand;
					//else if ((enemy.damage.limb.right_leg[UPPER].durability<50)&&(enemy.damage.limb.right_leg[UPPER].durability>=1)) enemy.damage.limb.right_leg[UPPER].status[TWO] = player.inventory.equipped.equipment.iRight_Hand;
					//else if ((enemy.damage.limb.right_leg[UPPER].durability<1)) enemy.damage.limb.right_leg[UPPER].status[THREE] = player.inventory.equipped.equipment.iRight_Hand;
					printf("Upper Right Leg Damaged\n");
					break;
				case (DAMAGE_LIMB_LEG+DAMAGE_LIMB_LEFT+DAMAGE_LIMB_LOWER):
					enemy.damage.limb.left_leg[LOWER].durability -= enemy.status.engage.applyLimbDamage;
					//enemy.damage.limb.left_leg[LOWER].weapon = player.inventory.equipped.equipment.iRight_Hand;
					if (enemy.damage.limb.left_leg[LOWER].durability < 0) enemy.damage.limb.left_leg[LOWER].durability = 0;
					//if ((enemy.damage.limb.left_leg[LOWER].durability<100)&&(enemy.damage.limb.left_leg[LOWER].durability>=80)) enemy.damage.limb.left_leg[LOWER].status[ZERO] = player.inventory.equipped.equipment.iRight_Hand;
					//else if ((enemy.damage.limb.left_leg[LOWER].durability<80)&&(enemy.damage.limb.left_leg[LOWER].durability>=50)) enemy.damage.limb.left_leg[LOWER].status[ONE] = player.inventory.equipped.equipment.iRight_Hand;
					//else if ((enemy.damage.limb.left_leg[LOWER].durability<50)&&(enemy.damage.limb.left_leg[LOWER].durability>=1)) enemy.damage.limb.left_leg[LOWER].status[TWO] = player.inventory.equipped.equipment.iRight_Hand;
					//else if ((enemy.damage.limb.left_leg[LOWER].durability<1)) enemy.damage.limb.left_leg[LOWER].status[THREE] = player.inventory.equipped.equipment.iRight_Hand;
					printf("Lower Left Leg Damaged\n");
					break;
				case (DAMAGE_LIMB_LEG+DAMAGE_LIMB_RIGHT+DAMAGE_LIMB_LOWER):
					enemy.damage.limb.right_leg[LOWER].durability -= enemy.status.engage.applyLimbDamage;
					//enemy.damage.limb.right_leg[LOWER].weapon = player.inventory.equipped.equipment.iRight_Hand;
					if (enemy.damage.limb.right_leg[LOWER].durability < 0) enemy.damage.limb.right_leg[LOWER].durability = 0;
					//if ((enemy.damage.limb.right_leg[LOWER].durability<100)&&(enemy.damage.limb.right_leg[LOWER].durability>=80)) enemy.damage.limb.right_leg[LOWER].status[ZERO] = player.inventory.equipped.equipment.iRight_Hand;
					//else if ((enemy.damage.limb.right_leg[LOWER].durability<80)&&(enemy.damage.limb.right_leg[LOWER].durability>=50)) enemy.damage.limb.right_leg[LOWER].status[ONE] = player.inventory.equipped.equipment.iRight_Hand;
					//else if ((enemy.damage.limb.right_leg[LOWER].durability<50)&&(enemy.damage.limb.right_leg[LOWER].durability>=1)) enemy.damage.limb.right_leg[LOWER].status[TWO] = player.inventory.equipped.equipment.iRight_Hand;
					//else if ((enemy.damage.limb.right_leg[LOWER].durability<1)) enemy.damage.limb.right_leg[LOWER].status[THREE] = player.inventory.equipped.equipment.iRight_Hand;
					printf("Lower Right Leg Damaged\n");
					break;
				case (DAMAGE_LIMB_HEAD):
					enemy.damage.limb.head.durability -= enemy.status.engage.applyLimbDamage;
					//enemy.damage.limb.head.weapon = player.inventory.equipped.equipment.iRight_Hand;
					if (enemy.damage.limb.head.durability < 0) enemy.damage.limb.head.durability = 0;
					//if ((enemy.damage.limb.head.durability<100)&&(enemy.damage.limb.head.durability>=80)) enemy.damage.limb.head.status[ZERO] = player.inventory.equipped.equipment.iRight_Hand;
					//else if ((enemy.damage.limb.head.durability<80)&&(enemy.damage.limb.head.durability>=50)) enemy.damage.limb.head.status[ONE] = player.inventory.equipped.equipment.iRight_Hand;
					//else if ((enemy.damage.limb.head.durability<50)&&(enemy.damage.limb.head.durability>=1)) enemy.damage.limb.head.status[TWO] = player.inventory.equipped.equipment.iRight_Hand;
					//else if ((enemy.damage.limb.head.durability<1)) enemy.damage.limb.head.status[THREE] = player.inventory.equipped.equipment.iRight_Hand;
					printf("Head Damaged\n");
					break;
				case (DAMAGE_LIMB_TORSO):
					enemy.damage.limb.torso.durability -= enemy.status.engage.applyLimbDamage;
					//enemy.damage.limb.torso.weapon = player.inventory.equipped.equipment.iRight_Hand;
					if (enemy.damage.limb.torso.durability < 0) enemy.damage.limb.torso.durability = 0;
					//if ((enemy.damage.limb.torso.durability<100)&&(enemy.damage.limb.torso.durability>=80)) enemy.damage.limb.torso.status[ZERO] = player.inventory.equipped.equipment.iRight_Hand;
					//else if ((enemy.damage.limb.torso.durability<80)&&(enemy.damage.limb.torso.durability>=50)) enemy.damage.limb.torso.status[ONE] = player.inventory.equipped.equipment.iRight_Hand;
					//else if ((enemy.damage.limb.torso.durability<50)&&(enemy.damage.limb.torso.durability>=1)) enemy.damage.limb.torso.status[TWO] = player.inventory.equipped.equipment.iRight_Hand;
					//else if ((enemy.damage.limb.torso.durability<1)) enemy.damage.limb.torso.status[THREE] = player.inventory.equipped.equipment.iRight_Hand;
					printf("Torso Damaged");
					if (enemy.status.engage.iCritical&DAMAGE_CRITICAL_FOUR) {
						printf(", CRITICAL HIT!\n");
						enemy.status.engage.applyHealthDamage	+=	gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].weapon->critical_static + (gameVars->items[player.inventory.list[player.inventory.equipped.equipment.iRight_Hand].id].weapon->critical_percent * enemy.damage.hit_points);
					}
					else printf("\n");

					//fprintf(stderr, "Armor type:\n");
					//fprintf(stderr, "\tSkin:\t%s\n", 	gameVars->armor[enemy.items.armor[0].torso].name.c_str());
					//fprintf(stderr, "\tCloth:\t%s\n", 	gameVars->armor[enemy.items.armor[1].torso].name.c_str());
					//fprintf(stderr, "\tPadded:\t%s\n", 	gameVars->armor[enemy.items.armor[2].torso].name.c_str());
					//fprintf(stderr, "\tMaille:\t%s\n", 	gameVars->armor[enemy.items.armor[3].torso].name.c_str());
					//fprintf(stderr, "\tPlate:\t%s\n", 	gameVars->armor[enemy.items.armor[4].torso].name.c_str());
					break;
			}

			//General status updates
			enemy.damage.hit_points -= enemy.status.engage.applyHealthDamage;

			//gameVars->armor[ID]
			cout << "Armor resistance is:\t" << GAME::ARMOR.RESISTANCE.to_str(iResistanceLevel) << "[" << iResistanceLevel << "]" << endl ;
//			cout << "Armor resistances:\t" << GAME::ARMOR.RESISTANCE[iResistanceLevel][CRITICAL_ZERO] << "\t" \
//					 << GAME::ARMOR.RESISTANCE[iResistanceLevel][CRITICAL_ONE] << "\t" \
//					 << GAME::ARMOR.RESISTANCE[iResistanceLevel][CRITICAL_TWO] << "\t" \
//					 << GAME::ARMOR.RESISTANCE[iResistanceLevel][CRITICAL_THREE] << "\t" \
//					 << GAME::ARMOR.RESISTANCE[iResistanceLevel][CRITICAL_FOUR] << endl;

			cout << "Armor Resistance:\t" << iOne << ",\t" << iTwo << ",\t" << iThree << ",\t" << iFour << endl;
			cout << "Weapon Damages:\t\t" << limb_1 << ",\t" << limb_2 << ",\t" << limb_3 << ",\t" << limb_4 << "\t[base damage=" << damage << "]" << endl;
			cout << "----- Attack Summary -----" << endl;
			cout << "   Target:\t" << enemy.init.name << endl;
			switch (enemy.status.engage.iCritical) {
				case DAMAGE_CRITICAL_ONE:		cout << "   Critical Value:\t1" << endl;	break;
				case DAMAGE_CRITICAL_TWO:		cout << "   Critical Value:\t2" << endl;	break;
				case DAMAGE_CRITICAL_THREE:	cout << "   Critical Value:\t3" << endl;	break;
				case DAMAGE_CRITICAL_FOUR:	cout << "   Critical Value:\t4" << endl;	break;
			}
			cout << "   Damage to Limb:\t" << enemy.status.engage.applyLimbDamage << endl;
			cout << "   Damage to Health:\t" << enemy.status.engage.applyHealthDamage << endl;
			cout << "--------------------------" << endl;

			//gameSys.audioSys.playSound(gameSys.audioSys.SOUNDS.BATTLE.SWORD_HIT);
			//gameSys.animationSys.startAnimation(enemy.init.w, enemy.init.h, player.transform.pos, enemy.transform.pos, gameSys.animationSys.ANIMATIONS.SWORD_HIT, 3, 60, &gameSys.audioSys.SOUNDS.BATTLE.SWORD_HIT);
			gameSys.playAnimation(enemy.init.w, enemy.init.h, player.transform.pos, enemy.transform.pos, gameSys.animationSys.ANIMATIONS.SWORD_HIT, 1, 60, &gameSys.audioSys.SOUNDS.BATTLE.SWORD_HIT);
			//gameSys.playAnimation(x, y, camera, target, ia, loop, rate, sample, move);

			//Update Cards
			UpdateCards(enemy);
		}

		/*
		 * Test for knockback
		 *
		 * [(enemy_height-player_height) / (enemy_height+player_height)] * (100-player_fortitude)
		 */
		cout << "Checking for knockback...";
		float fKnockBack = fabs(((enemy.transform.eyeHeight-player.transform.eyeHeight) / (enemy.transform.eyeHeight+player.transform.eyeHeight)) * (100-player.combat_check.fortitude));
		std::uniform_int_distribution<> rand(0, 100);
		int iRand = rand(RNG::eng);
		cout << "[" << iRand << "] <= [" << fKnockBack << "]...";
		if(iRand <= fKnockBack) {
			/*
			 * TODO:
			 * Knocks enemy back to limit of
			 * attackers attack radius
			 */
			cout << "SUCCESS!" << endl;
		} else cout << "FAIL!" << endl;

	}
	else {
		std::cout << "OUT OF RANGE!!!" << std::endl;
		player.status.engage.attackNum++;		//Allow repeat opportunity
	}

	//Do we have more attack opportunities?
	/*
	if (player.status.engage.attackNum > 1) {
		player.status.engage.attackNum--;
		player.status.choice.engage = BC_ENGAGE_INIT;
		player.status.engage.attack = BC_ATTACK_INIT;
	}
	else player.status.state = BC_STATE_MAGIC;
	*/

	//cout << "===================================" << endl;
	//cout << "attackNum=" << player.status.engage.attackNum << endl;

	//cout << "State A:" << player.status.state << endl;

	//UpdateRound(player, false);

	//cout << "State B:" << player.status.state << endl;
	//cout << "attackNum=" << player.status.engage.attackNum << endl;
}

void RunBattle::UpdateCards(CharSheet &sheet) {
	int iNewCard = 0;
	/*
	 * Shift cards by one, dropping the last card
	 * Then set the first card equal to the last
	 * attack.
	 *
	 * We also need to do a check above for
	 * a defense success.
	 */
	for(int i=14; i>=0; i--) {
		sheet.status.iCards[i+1][0] = sheet.status.iCards[i][0];
		sheet.status.iCards[i+1][1] = sheet.status.iCards[i][1];
		sheet.status.iCards[i+1][2] = sheet.status.iCards[i][2];
	}

	sheet.status.iCards[0][0] = GAME::CARDS.ICON.BLANK;
	sheet.status.iCards[0][1] = GAME::CARDS.ICON.BLANK;
	sheet.status.iCards[0][2] = GAME::CARDS.ICON.BLANK;

	/*
	 * Convert battle damage into card values (icon id values)
	 */
	switch(sheet.status.engage.iType) {
		case GAME::WEAPON.TYPE.BLADE:sheet.status.iCards[0][0] = GAME::CARDS.ICON.BLADE; break;
		case GAME::WEAPON.TYPE.BLUNT:sheet.status.iCards[0][0] = GAME::CARDS.ICON.BLUNT; break;
		case GAME::WEAPON.TYPE.AXE:  sheet.status.iCards[0][0] = GAME::CARDS.ICON.AXE;   break;
		case GAME::WEAPON.TYPE.SPEAR:sheet.status.iCards[0][0] = GAME::CARDS.ICON.SPEAR; break;
		case GAME::WEAPON.TYPE.ARROW:sheet.status.iCards[0][0] = GAME::CARDS.ICON.ARROW; break;
		case GAME::WEAPON.TYPE.JAW:  sheet.status.iCards[0][0] = GAME::CARDS.ICON.JAW;   break;
		case GAME::WEAPON.TYPE.CLAW: sheet.status.iCards[0][0] = GAME::CARDS.ICON.CLAW;  break;
		case GAME::WEAPON.TYPE.HAND: sheet.status.iCards[0][0] = GAME::CARDS.ICON.HAND;  break;
	}

	switch(sheet.status.engage.limbHit) {
		case (DAMAGE_LIMB_ARM+DAMAGE_LIMB_LEFT+DAMAGE_LIMB_UPPER):
			switch(sheet.status.engage.iCritical) {
				case (DAMAGE_CRITICAL_ONE):  sheet.status.iCards[0][1] = GAME::CARDS.ICON.ONE_LEFT_ARM_UPPER; break;
				case (DAMAGE_CRITICAL_TWO):  sheet.status.iCards[0][1] = GAME::CARDS.ICON.TWO_LEFT_ARM_UPPER; break;
				case (DAMAGE_CRITICAL_THREE):sheet.status.iCards[0][1] = GAME::CARDS.ICON.THREE_LEFT_ARM_UPPER; break;
				case (DAMAGE_CRITICAL_FOUR): sheet.status.iCards[0][1] = GAME::CARDS.ICON.FOUR_LEFT_ARM_UPPER; break;
			}
			break;
		case (DAMAGE_LIMB_ARM+DAMAGE_LIMB_RIGHT+DAMAGE_LIMB_UPPER):
			switch(sheet.status.engage.iCritical) {
				case (DAMAGE_CRITICAL_ONE):  sheet.status.iCards[0][1] = GAME::CARDS.ICON.ONE_RIGHT_ARM_UPPER; break;
				case (DAMAGE_CRITICAL_TWO):  sheet.status.iCards[0][1] = GAME::CARDS.ICON.TWO_RIGHT_ARM_UPPER; break;
				case (DAMAGE_CRITICAL_THREE):sheet.status.iCards[0][1] = GAME::CARDS.ICON.THREE_RIGHT_ARM_UPPER; break;
				case (DAMAGE_CRITICAL_FOUR): sheet.status.iCards[0][1] = GAME::CARDS.ICON.FOUR_RIGHT_ARM_UPPER; break;
			}
			break;
		case (DAMAGE_LIMB_ARM+DAMAGE_LIMB_LEFT+DAMAGE_LIMB_LOWER):
			switch(sheet.status.engage.iCritical) {
				case (DAMAGE_CRITICAL_ONE):  sheet.status.iCards[0][1] = GAME::CARDS.ICON.ONE_LEFT_ARM_LOWER; break;
				case (DAMAGE_CRITICAL_TWO):  sheet.status.iCards[0][1] = GAME::CARDS.ICON.TWO_LEFT_ARM_LOWER; break;
				case (DAMAGE_CRITICAL_THREE):sheet.status.iCards[0][1] = GAME::CARDS.ICON.THREE_LEFT_ARM_LOWER; break;
				case (DAMAGE_CRITICAL_FOUR): sheet.status.iCards[0][1] = GAME::CARDS.ICON.FOUR_LEFT_ARM_LOWER; break;
			}
			break;
		case (DAMAGE_LIMB_ARM+DAMAGE_LIMB_RIGHT+DAMAGE_LIMB_LOWER):
			switch(sheet.status.engage.iCritical) {
				case (DAMAGE_CRITICAL_ONE):  sheet.status.iCards[0][1] = GAME::CARDS.ICON.ONE_RIGHT_ARM_LOWER; break;
				case (DAMAGE_CRITICAL_TWO):  sheet.status.iCards[0][1] = GAME::CARDS.ICON.TWO_RIGHT_ARM_LOWER; break;
				case (DAMAGE_CRITICAL_THREE):sheet.status.iCards[0][1] = GAME::CARDS.ICON.THREE_RIGHT_ARM_LOWER; break;
				case (DAMAGE_CRITICAL_FOUR): sheet.status.iCards[0][1] = GAME::CARDS.ICON.FOUR_RIGHT_ARM_LOWER; break;
			}
			break;
		case (DAMAGE_LIMB_LEG+DAMAGE_LIMB_LEFT+DAMAGE_LIMB_UPPER):
			switch(sheet.status.engage.iCritical) {
				case (DAMAGE_CRITICAL_ONE):  sheet.status.iCards[0][1] = GAME::CARDS.ICON.ONE_LEFT_LEG_UPPER; break;
				case (DAMAGE_CRITICAL_TWO):  sheet.status.iCards[0][1] = GAME::CARDS.ICON.TWO_LEFT_LEG_UPPER; break;
				case (DAMAGE_CRITICAL_THREE):sheet.status.iCards[0][1] = GAME::CARDS.ICON.THREE_LEFT_LEG_UPPER; break;
				case (DAMAGE_CRITICAL_FOUR): sheet.status.iCards[0][1] = GAME::CARDS.ICON.FOUR_LEFT_LEG_UPPER; break;
			}
			break;
		case (DAMAGE_LIMB_LEG+DAMAGE_LIMB_RIGHT+DAMAGE_LIMB_UPPER):
			switch(sheet.status.engage.iCritical) {
				case (DAMAGE_CRITICAL_ONE):  sheet.status.iCards[0][1] = GAME::CARDS.ICON.ONE_RIGHT_LEG_UPPER; break;
				case (DAMAGE_CRITICAL_TWO):  sheet.status.iCards[0][1] = GAME::CARDS.ICON.TWO_RIGHT_LEG_UPPER; break;
				case (DAMAGE_CRITICAL_THREE):sheet.status.iCards[0][1] = GAME::CARDS.ICON.THREE_RIGHT_LEG_UPPER; break;
				case (DAMAGE_CRITICAL_FOUR): sheet.status.iCards[0][1] = GAME::CARDS.ICON.FOUR_RIGHT_LEG_UPPER; break;
			}
			break;
		case (DAMAGE_LIMB_LEG+DAMAGE_LIMB_LEFT+DAMAGE_LIMB_LOWER):
			switch(sheet.status.engage.iCritical) {
				case (DAMAGE_CRITICAL_ONE):  sheet.status.iCards[0][1] = GAME::CARDS.ICON.ONE_LEFT_LEG_LOWER; break;
				case (DAMAGE_CRITICAL_TWO):  sheet.status.iCards[0][1] = GAME::CARDS.ICON.TWO_LEFT_LEG_LOWER; break;
				case (DAMAGE_CRITICAL_THREE):sheet.status.iCards[0][1] = GAME::CARDS.ICON.THREE_LEFT_LEG_LOWER; break;
				case (DAMAGE_CRITICAL_FOUR): sheet.status.iCards[0][1] = GAME::CARDS.ICON.FOUR_LEFT_LEG_LOWER; break;
			}
			break;
		case (DAMAGE_LIMB_LEG+DAMAGE_LIMB_RIGHT+DAMAGE_LIMB_LOWER):
			switch(sheet.status.engage.iCritical) {
				case (DAMAGE_CRITICAL_ONE):  sheet.status.iCards[0][1] = GAME::CARDS.ICON.ONE_RIGHT_LEG_LOWER; break;
				case (DAMAGE_CRITICAL_TWO):  sheet.status.iCards[0][1] = GAME::CARDS.ICON.TWO_RIGHT_LEG_LOWER; break;
				case (DAMAGE_CRITICAL_THREE):sheet.status.iCards[0][1] = GAME::CARDS.ICON.THREE_RIGHT_LEG_LOWER; break;
				case (DAMAGE_CRITICAL_FOUR): sheet.status.iCards[0][1] = GAME::CARDS.ICON.FOUR_RIGHT_LEG_LOWER; break;
			}
			break;
		case (DAMAGE_LIMB_HEAD):
			switch(sheet.status.engage.iCritical) {
				case (DAMAGE_CRITICAL_ONE):  sheet.status.iCards[0][1] = GAME::CARDS.ICON.ONE_HEAD; break;
				case (DAMAGE_CRITICAL_TWO):  sheet.status.iCards[0][1] = GAME::CARDS.ICON.TWO_HEAD; break;
				case (DAMAGE_CRITICAL_THREE):sheet.status.iCards[0][1] = GAME::CARDS.ICON.THREE_HEAD; break;
				case (DAMAGE_CRITICAL_FOUR): sheet.status.iCards[0][1] = GAME::CARDS.ICON.FOUR_HEAD; break;
			}
			break;
		case (DAMAGE_LIMB_TORSO):
			switch(sheet.status.engage.iCritical) {
				case (DAMAGE_CRITICAL_ONE):  sheet.status.iCards[0][1] = GAME::CARDS.ICON.ONE_TORSO; break;
				case (DAMAGE_CRITICAL_TWO):  sheet.status.iCards[0][1] = GAME::CARDS.ICON.TWO_TORSO; break;
				case (DAMAGE_CRITICAL_THREE):sheet.status.iCards[0][1] = GAME::CARDS.ICON.THREE_TORSO; break;
				case (DAMAGE_CRITICAL_FOUR): sheet.status.iCards[0][1] = GAME::CARDS.ICON.FOUR_TORSO; break;
			}
			break;
	}

	switch(sheet.status.engage.iCritical) {
		case (DAMAGE_CRITICAL_ONE):  sheet.status.iCards[0][2] = GAME::CARDS.ICON.ONE; break;
		case (DAMAGE_CRITICAL_TWO):  sheet.status.iCards[0][2] = GAME::CARDS.ICON.TWO; break;
		case (DAMAGE_CRITICAL_THREE):sheet.status.iCards[0][2] = GAME::CARDS.ICON.THREE; break;
		case (DAMAGE_CRITICAL_FOUR): sheet.status.iCards[0][2] = GAME::CARDS.ICON.FOUR; break;
	}

	//cout << "Type = " << sheet.status.iCards[0][0] << endl;
	//cout << "Limb = " << sheet.status.iCards[0][1] << endl;
	//cout << "Crit = " << sheet.status.iCards[0][2] << endl << endl;

	//sheet.status.iCards[0][0] = sheet.status.engage.iType;
	//sheet.status.iCards[0][1] = sheet.status.engage.limbHit;
	//sheet.status.iCards[0][2] = sheet.status.engage.iCritical;
}

void RunBattle::Shift_Spells(int x, int y) {
	for(int z=y;z<4;z++) {
		if(z<4) {
			TempMagic[0].spells.iSpellBlock[x][z]=TempMagic[0].spells.iSpellBlock[x][z+1];
			TempMagic[0].spells.iSpellBlock[x][z+1]=-1;
		}
		else if(z==4) TempMagic[0].spells.iSpellBlock[x][z]=-1;
	}
}

void RunBattle::RunMagic() {
	/*
	 * Show the mouse cursor
	 */
	ToggleMouse(true);

	//Icon Presets
	int iDown	 = 2,	//Down Arrow
		iUp		 = 1,	//Up Arrow
		iBlank	 = 0,	//Blank Unlocked Box
		iLock	 = 3,	//Locked Box
		iUnknown = 4,	//Unknown spell (?)
		iSet	 = 0;	//Variable icon setting

	std::string  sIconFile = "spell_system.png";	//Current icon file

	//Save original highlight color
	gameVars->font.vTempColor[0]=gameVars->font.vHighlight[0];
	gameVars->font.vTempColor[1]=gameVars->font.vHighlight[1];
	gameVars->font.vTempColor[2]=gameVars->font.vHighlight[2];
	gameVars->font.vTempColor[3]=gameVars->font.vHighlight[3];

	//Set new default highlight color
	gameVars->font.vHighlight[0] = vHighlight[0];
	gameVars->font.vHighlight[1] = vHighlight[1];
	gameVars->font.vHighlight[2] = vHighlight[2];
	gameVars->font.vHighlight[3] = vHighlight[3];

	Vector2f vC = {((-gameVars->font.screenCoords[0]-32)/gameVars->font.vSize[0]), ((gameVars->font.screenCoords[1]-32)/gameVars->font.vSize[1])};
	//Vector2f vC = {-gameVars->font.screenCoords[0], gameVars->font.screenCoords[1]};

	Vector2f vF = {gameVars->font.vSize[0], gameVars->font.vSize[1]};

	//Easy access Aliases
	int  (*iBookmark)					= TempMagic[0].spells.iBookmark;
	bool (*bBookmark)					= TempMagic[0].spells.bBookmark;
	int  (*iSelectedSpell)		= &TempMagic[0].spells.iSelectedSpell;
	bool (*bSpellBlock)[5]		= TempMagic[0].spells.bSpellBlock;
	int  (*iSpellBlock)[5]		= TempMagic[0].spells.iSpellBlock;
	//CharSheet (*csCaster)		= &gameVars->player.active->magic.spells.csCaster;
	//CharSheet (*csTarget)		= &gameVars->player.active->magic.spells.csTarget;

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
		Battle.draw();
	}
	else {
		world.Update(false);
	}

	//Draw Spell Battle Page
	gameSys.drawSprite(1,-1,gameVars->screen.w-(3*gameVars->font.vSize[1]),gameVars->screen.h-(2*gameVars->font.vSize[2]),"magic_battle.png", false, true);

	/*
	 * BOOKMARKS
	 *
	 * These spells need to come from the active
	 * players list of bookmarked spells
	 */
	sSet.x = 6;
	sSet.y = 8;
	sSet.w = 64;
	sSet.h = 64;

	gameSys.drawText(sSet.x, sSet.y-2, "Bookmarks: ");
	if(*iSelectedSpell>-1) {
		gameSys.drawText(sSet.x+11, sSet.y-2, gameVars->spell[iBookmark[*iSelectedSpell]].name);
	}

	int iX=0,
			iY=0;
	for(int i=0; i<TempMagic[0].spells.iMaxBookmark; i++) {
		// If the current spell is already selected then
		// set the tint, otherwise use the normal tint
		if (*iSelectedSpell==i) {
			vTint[0] = vSelected[0];
			vTint[1] = vSelected[1];
			vTint[2] = vSelected[2];
			vTint[3] = vSelected[3];
		}
		else {
			vTint[0] = vTintBase[0];
			vTint[1] = vTintBase[1];
			vTint[2] = vTintBase[2];
			vTint[3] = vTintBase[3];
		}

		// If the bookmark is available to the player
		// then draw the icon to the screen, otherwise
		// draw the disabled icon
		if (bBookmark[i]) {

			// If the icon is clicked on then check if the
			// icon is already selected and disable the selected
			// icon, otherwise enable the selection.
			if (gameSys.checkIcon(sSet.x+iX,		sSet.y+iY,	sSet.w, sSet.h, iBookmark[i],  "spells.png", true, true, vTint)) {
				if (*iSelectedSpell==i) *iSelectedSpell=-1;
				else *iSelectedSpell=i;
			}
		}
		else gameSys.drawIcon(sSet.x+iX,	sSet.y+iY,	sSet.w, sSet.h, iLock,  "spell_system.png", false, true, vTint);
		iX+=8;
		if(iX>24) {
			iX=0;
			iY+=6;
		}
	}

	/*
	 * Wands
	 *
	 * The equipped wands need to be checked for their
	 * imbuement type which can be either mental or
	 * physical. Mental is used in the mind battle while
	 * physical is used in normal battle. Mental wands
	 * are listed here with a maximum of 6.
	 */
	sSet.x = 6;
	sSet.y = 30;
	sSet.w = 64;
	sSet.h = 64;

	gameSys.drawText(sSet.x, sSet.y-2, "Wands");
	//if(*iSelectedWand>-1) {
	//	gameSys.drawText(sSet.x, sSet.y-1, gameVars->spell[iBookmark[*iSelectedSpell]].name);
	//}

	iX=0;
	iY=0;
	for(int i=0; i<6; i++) {
		// Temporary faux wand drawing
		gameSys.drawIcon(sSet.x+iX,	sSet.y+iY,	sSet.w, sSet.h, i+6,  "spells.png", false, true, vTint);

		// If the current wand is already selected then
		// set the tint, otherwise use the normal tint
//		if (*iSelectedWand==i) {
//			vTint[0] = vSelected[0];
//			vTint[1] = vSelected[1];
//			vTint[2] = vSelected[2];
//			vTint[3] = vSelected[3];
//		}
//		else {
//			vTint[0] = vTintBase[0];
//			vTint[1] = vTintBase[1];
//			vTint[2] = vTintBase[2];
//			vTint[3] = vTintBase[3];
//		}

		// If the bookmark is available to the player
		// then draw the icon to the screen, otherwise
		// draw the disabled icon
//		if (bBookmark[i]) {
//
//			// If the icon is clicked on then check if the
//			// icon is already selected and disable the selected
//			// icon, otherwise enable the selection.
//			if (gameSys.checkIcon(sSet.x+iX,		sSet.y+iY,	sSet.w, sSet.h, iBookmark[i],  "spells.png", true, true, vTint)) {
//				if (*iSelectedWand==i) *iSelectedWand=-1;
//				else *iSelectedWand=i;
//			}
//		}
//		else gameSys.drawIcon(sSet.x+iX,	sSet.y+iY,	sSet.w, sSet.h, iLock,  "spell_system.png", false, true, vTint);
		iX+=8;
		if(iX>18) {
			iX=0;
			iY+=6;
		}
	}

	/*
	 * LOWER SPELL BLOCKS (ATTACKER)
	 *
	 * The upper 4 blocks may be locked
	 * 	depending on the attackers skills
	 * 	and needs to be checked
	 *
	 * The lower line is the active spell
	 * 	list and needs to be read from the
	 * 	attackers active spell list.
	 *
	 * The active spells need a target
	 * 	for each one, make sure to have
	 * 	a pointer to a target for the
	 * 	active spell list.
	 */

	sSet.x = 40;
	sSet.y = 29;
	sSet.w = 32;
	sSet.h = 32;

	gameSys.drawText(sSet.x, sSet.y+19, gameVars->player.active->init.name);

	for(int x=0; x<12; x++) {
		for(int y=0; y<5; y++) {
			/*
			 * If the spell block has been enabled
			 * then check if it is the first in the
			 * column or not. If its the first in
			 * the column then exit loop, otherwise
			 * iterate through the column and draw
			 * the icons accordingly.
			 */
			if(bSpellBlock[x][y]) {
				if(y>0) {
					gameSys.drawIcon(sSet.x,  sSet.y+=2,	sSet.w, sSet.h, iUp, 	"spell_system.png", false, true, vTint);
					sSet.y += 2;
				}

				/*
				 * Determine icon to draw is spell is already selected
				 * for this block
				 */
				if(iSpellBlock[x][y]>-1) {
					iSet = iSpellBlock[x][y];
					sIconFile = "spells.png";
				}
				else {
					iSet = iBlank;
					sIconFile = "spell_system.png";
				}

				/*
				 * If the icon is clicked on then set or
				 * unset the block accordingly. If the
				 * block is already set then just disable
				 * that spell. If the block is empty then
				 * apply the selected spell to that block.
				 *
				 * Therefore it takes two clicks to overwrite
				 * and active spell block.
				 */
				if (gameSys.checkIcon(sSet.x,  sSet.y,	sSet.w, sSet.h, iSet,	sIconFile, true, true, vTint)) {

					/*
					 * IFF the icon before this one has
					 * been already set, then allow the
					 * next row icon to be set
					 */
					if (y==0 || iSpellBlock[x][y-1]>-1) {

						/*
						 * If a spell is selected from the bookmarks
						 * then proceed...
						 */
						if (*iSelectedSpell>-1) {
							/*
							 * If the current spell block has a spell
							 * on it, then disable that spell, otherwise
							 * apply the currently selected spell
							 */
							if (iSpellBlock[x][y]>-1) {
								Shift_Spells(x, y);		//Shift Spells Up
							}
							else {
								iSpellBlock[x][y]=iBookmark[*iSelectedSpell];
								//*iSelectedSpell=-1;	//Unselect the spell (Do we want to do this?)
							}
						}
						else {
							if (iSpellBlock[x][y]>-1) {
								/*
								 * If a spell is deselected and other spells
								 * are wating in line then we need to shift
								 * all of them up a slot
								 */
								Shift_Spells(x, y);
							}
						}
					}
				}
			}
			else {
				if(y==0) {
					//BREAK OUT OF LOOP
					//NO OTHER COLUMNS SHOULD BE UNLOCKED
					y=5;
					x=12;
				}
				else {
					gameSys.drawIcon(sSet.x,  sSet.y+=2,	sSet.w, sSet.h, iUp, 	"spell_system.png", false, true, vTint);
					gameSys.drawIcon(sSet.x,  sSet.y+=2,	sSet.w, sSet.h, iLock,	"spell_system.png", false, true, vTint);
				}
			}
		}
		sSet.y = 29;
		sSet.x +=6;
	}


	/*
	 * UPPER SPELL BLOCKS (Target)
	 *
	 * The upper 4 blocks may be locked
	 * 	depending on the targets skills
	 * 	and needs to be checked
	 *
	 * The lower line is the active spell
	 * 	list and needs to be read from the
	 * 	targets active spell list.
	 *
	 * The active spells need a target
	 * 	for each one, make sure to have
	 * 	a pointer to a target for the
	 * 	active spell list
	 */

	iBookmark				= TempMagic[1].spells.iBookmark;
	bBookmark				= TempMagic[1].spells.bBookmark;
	iSelectedSpell	= &TempMagic[1].spells.iSelectedSpell;
	bSpellBlock			= TempMagic[1].spells.bSpellBlock;
	iSpellBlock			= TempMagic[1].spells.iSpellBlock;

	sSet.x = 40;
	sSet.y = 23;
	sSet.w = 32;
	sSet.h = 32;

	gameSys.drawText(sSet.x, sSet.y-17, gameVars->player.active->status.target->init.name);

	for(int x=0; x<12; x++) {
		for(int y=0; y<5; y++) {
			if(bSpellBlock[x][y]) {
				if(y>0) {
					gameSys.drawIcon(sSet.x,  sSet.y-=2,	sSet.w, sSet.h, iDown, 	"spell_system.png", false, true, vTint);
					sSet.y -= 2;
				}

				/*
				 * Determine icon to draw if spell is already selected
				 * for this block
				 */
				if(iSpellBlock[x][y]>-1) {
					iSet = iUnknown;
				}
				else {
					iSet = iBlank;
				}

				gameSys.drawIcon(sSet.x,  sSet.y,	sSet.w, sSet.h, iSet,	"spell_system.png", false, true, vTint);
			}
			else {
				if(y==0) {
					//BREAK OUT OF LOOP
					//NO OTHER COLUMNS SHOULD BE UNLOCKED
					y=5;
					x=12;
				}
				else {
					gameSys.drawIcon(sSet.x,  sSet.y-=2,	sSet.w, sSet.h, iDown, 	"spell_system.png", false, true, vTint);
					gameSys.drawIcon(sSet.x,  sSet.y-=2,	sSet.w, sSet.h, iLock,	"spell_system.png", false, true, vTint);
				}
			}
		}
		sSet.y = 23;
		sSet.x +=6;
	}

	gameSys.winSys.drawHLine(40, 26, 68, gameVars->color.black, GAME::SYSTEM.WINSYS.DRAWMODE.BORDER_ONLY);
	gameSys.winSys.drawHLine(40, 27, 68, gameVars->color.black, GAME::SYSTEM.WINSYS.DRAWMODE.BORDER_ONLY);

	gameVars->font.vHighlight[0]=gameVars->font.vTempColor[0];
	gameVars->font.vHighlight[1]=gameVars->font.vTempColor[1];
	gameVars->font.vHighlight[2]=gameVars->font.vTempColor[2];
	gameVars->font.vHighlight[3]=gameVars->font.vTempColor[3];
}

void RunBattle::ExecMagic() {

}

void RunBattle::ExecDefend(int mode, CharSheet &sheet) {
	/*
	sheet.status.choice.defense = mode;
	switch(mode) {
		case BC_MAGIC_CHARGE:
		break;
		case BC_MAGIC_HACK:
		break;
		case BC_MAGIC_DEFENSE:
		break;
		case BC_MAGIC_FORGO:
		break;
	}
	sheet.status.choice.engage = BC_ENGAGE_INIT;
	*/
}

void RunBattle::draw() {
	/*
	 * Get the current participants transformation information
	 * 		so we can draw the scene correctly.
	 */
	//Vector3f rot;
	//rot[0] = CSattacker.transform.rot[0];
	//rot[1] = CSattacker.transform.rot[1];
	//rot[2] = CSattacker.transform.rot[2];

	//pos[0] = CSattacker.transform.pos[0];
	//pos[1] = CSattacker.transform.pos[1];
	//pos[2] = CSattacker.transform.pos[2];

	//Update the world geometry
	if (iPlayer==PLAYER) {
		//gameVars->transform.worldPos[0] = CSattacker.transform.pos[0];
		//gameVars->transform.worldPos[1] = CSattacker.transform.pos[1];
		//gameVars->transform.worldPos[2] = CSattacker.transform.pos[2];
	}

	/*
	 * We are using the draw routines from the RunWorld class, this allows us to use the current
	 * state of the game world as our background
	 *
	 * This needs to be added to menu areas as well to prevent "bleeding" (z-buffer error)
	 */
	world.Update(gameVars->controls.bThirdPerson);
	//world.Draw(world.DRAW_SKY+world.DRAW_MAP+world.DRAW_O3D+world.DRAW_E2D+world.DRAW_O2D+world.DRAW_WATER, true);

	//DRAW ALL SHADER LAYERS
	//for (int i=0; i<GLS_LAST; i++) {
		//if (gameVars->shader.bCurrent[i]) {
			//Core.shader.use(i);
			Core.matrix.Push();

				if(gameVars->controls.bThirdPerson) Core.matrix.Translate(0, -10, -100);		//3rd person view

				Core.matrix.Rotate(gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
				Core.matrix.Rotate(gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
				Core.matrix.Translate(gameVars->player.active->transform.pos[0]*gameVars->screen.iScale, gameVars->player.active->transform.pos[1]-gameVars->player.active->transform.currentHeight, gameVars->player.active->transform.pos[2]*gameVars->screen.iScale);
				Core.matrix.SetTransform();
				//Core.shader.getUniform(i);

				glActiveTexture(GL_TEXTURE0);

				/*
				 * Convert 3rd person offset into rectangular coords
				 */
				Vector3f fAR = Vector3f(gameVars->player.active->transform.rot[0], gameVars->player.active->transform.rot[1], 0.0f);
				float	t = (fAR[1]);
				float	p = (fAR[0]);
				float	d = sqrt((100*100)+(10*10));
				float	y = d*sin(p)*cos(t),
						x = d*sin(t),
						z = d*cos(t)*cos(p);

				//cout << "MOD: " << x << ", " << y << ", " << z << endl;
				//Vector4f fActive =  { gameVars->player.active->transform.pos[0]+x, gameVars->player.active->transform.pos[1]-y, gameVars->player.active->transform.pos[2]-z, 0.0f };
	//			Vector4f fActive =  { gameVars->player.active->transform.pos[0], gameVars->player.active->transform.pos[1], gameVars->player.active->transform.pos[2], 0.0f };

				/*
				 * Get data needed for sorting
				 */
				/*
				Vector4f vSorted[5];

				//vSorted[0][0] = gameVars->player.active->transform.pos[0];
				//vSorted[0][1] = gameVars->player.active->transform.pos[1];
				//vSorted[0][2] = gameVars->player.active->transform.pos[2];
				//vSorted[0][3] = 0;

				vSorted[0][0] = gameVars->player.active->transform.pos[0];
				vSorted[0][1] = gameVars->player.active->transform.pos[1];
				vSorted[0][2] = gameVars->player.active->transform.pos[2];
				vSorted[0][3] = 0;

				if(numEnemy>=ENEMY1) {
					vSorted[1][0] = world.npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[ENEMY1].transform.pos[0];
					vSorted[1][1] = world.npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[ENEMY1].transform.pos[1];
					vSorted[1][2] = world.npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[ENEMY1].transform.pos[2];
					vSorted[1][3] = 1;
				}

				if(numEnemy>=ENEMY2) {
					vSorted[2][0] = world.npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[ENEMY2].transform.pos[0];
					vSorted[2][1] = world.npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[ENEMY2].transform.pos[1];
					vSorted[2][2] = world.npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[ENEMY2].transform.pos[2];
					vSorted[2][3] = 2;
				}

				if(numEnemy>=ENEMY3) {
					vSorted[3][0] = world.npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[ENEMY3].transform.pos[0];
					vSorted[3][1] = world.npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[ENEMY3].transform.pos[1];
					vSorted[3][2] = world.npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[ENEMY3].transform.pos[2];
					vSorted[3][3] = 3;
				}

				if(numEnemy>=ENEMY4) {
					vSorted[4][0] = world.npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[ENEMY4].transform.pos[0];
					vSorted[4][1] = world.npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[ENEMY4].transform.pos[1];
					vSorted[4][2] = world.npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[ENEMY4].transform.pos[2];
					vSorted[4][3] = 4;
				}

				bool bSort = false;
				do {
					bSort=true;
					if( Length(vSorted[0], fActive) < Length(vSorted[1], fActive) ) {
						Vector4f temp = {	vSorted[0][0],
											vSorted[0][1],
											vSorted[0][2],
											vSorted[0][3]	};

						vSorted[0][0] = vSorted[1][0];
						vSorted[0][1] = vSorted[1][1];
						vSorted[0][2] = vSorted[1][2];
						vSorted[0][3] = vSorted[1][3];

						vSorted[1][0] = temp[0];
						vSorted[1][1] = temp[1];
						vSorted[1][2] = temp[2];
						vSorted[1][3] = temp[3];
						bSort=false;
					}

					if(numEnemy>=ENEMY2) {
						if( Length(vSorted[1], fActive) < Length(vSorted[2], fActive) ) {
							Vector4f temp = {	vSorted[1][0],
												vSorted[1][1],
												vSorted[1][2],
												vSorted[1][3]	};

							//vSorted[1] = vSorted[2];
							//vSorted[2] = temp;

							vSorted[1][0] = vSorted[2][0];
							vSorted[1][1] = vSorted[2][1];
							vSorted[1][2] = vSorted[2][2];
							vSorted[1][3] = vSorted[2][3];

							vSorted[2][0] = temp[0];
							vSorted[2][1] = temp[1];
							vSorted[2][2] = temp[2];
							vSorted[2][3] = temp[3];

							bSort=false;
						}
					}

					if(numEnemy>=ENEMY3) {
						if( Length(vSorted[2], fActive) < Length(vSorted[3], fActive) ) {
							Vector4f temp = {	vSorted[2][0],
												vSorted[2][1],
												vSorted[2][2],
												vSorted[2][3]	};

							//vSorted[2] = vSorted[3];
							//vSorted[3] = temp;

							vSorted[2][0] = vSorted[3][0];
							vSorted[2][1] = vSorted[3][1];
							vSorted[2][2] = vSorted[3][2];
							vSorted[2][3] = vSorted[3][3];

							vSorted[3][0] = temp[0];
							vSorted[3][1] = temp[1];
							vSorted[3][2] = temp[2];
							vSorted[3][3] = temp[3];

							bSort=false;
						}
					}

					if(numEnemy>=ENEMY4) {
						if( Length(vSorted[3], fActive) < Length(vSorted[4], fActive) ) {
							Vector4f temp = {	vSorted[3][0],
												vSorted[3][1],
												vSorted[3][2],
												vSorted[3][3]	};

							//vSorted[3] = vSorted[4];
							//vSorted[4] = temp;

							vSorted[3][0] = vSorted[4][0];
							vSorted[3][1] = vSorted[4][1];
							vSorted[3][2] = vSorted[4][2];
							vSorted[3][3] = vSorted[4][3];

							vSorted[4][0] = temp[0];
							vSorted[4][1] = temp[1];
							vSorted[4][2] = temp[2];
							vSorted[4][3] = temp[3];

							bSort=false;
						}
					}

				} while (bSort==false);

				CharSheet * csSorted[5];

				for(int i=0; i<5; i++) {
					if( vSorted[i][3] == 0 ) csSorted[i] = &gameVars->player.sheet;
					else if( vSorted[i][3] == 1 ) csSorted[i] = &world.npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[ENEMY1];
					else if( vSorted[i][3] == 2 ) csSorted[i] = &world.npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[ENEMY2];
					else if( vSorted[i][3] == 3 ) csSorted[i] = &world.npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[ENEMY3];
					else if( vSorted[i][3] == 4 ) csSorted[i] = &world.npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[ENEMY4];
				}
				*/

				//player.draw();

				/*
				 * Draw the active players current target
				 *
				 * We draw this first because we want the actual target
				 *   to be drawn over this highlighted version
				 *
				 * We might also want to draw the target card here and
				 *   only that one card, this will help pinpoint the
				 *   current target.
				 */
				world.npc.draw(world.atmosphere, *gameVars->player.active->status.target, false);

				/*
				 * Draw all of the active players in battle
				 * Always billboard towards the players current target
				 */
//				if(!gameVars->controls.bThirdPerson) gameVars->player.active->init.bActive = true;
//				world.npc.draw(world.atmosphere, gameVars->player.sheet, *gameVars->player.sheet.status.target, false);
//				for(int i=0; i<numEnemy; i++) {
//					if(!enemies[i]->init.isDead) {
//						world.npc.draw(world.atmosphere, *enemies[i], *enemies[i]->status.target, false);
//					}
//					//cout << "Drawing " << enemies[i].init.name << ", targeting " << enemies[i].status.target->init.name << endl;
//				}
//				if(!gameVars->controls.bThirdPerson) gameVars->player.active->init.bActive = false;

				/*
				 * Draw the card for the current target
				 * We draw this here so that it is on
				 * top of the target
				 */
				world.npc.draw(world.atmosphere, *gameVars->player.active->status.target, true);

				// Draw animations if active
				if(gameSys.animationSys.isAnimating()) gameSys.animationSys.drawWorld();
			//	gameVars->player.active->init.bActive = true;	//This disables the active player from being drawn, we need this if we don't have third person enabled
			//	world.npc.draw(world.atmosphere, *csSorted[0], *csSorted[0]->status.target);
			//	if(numEnemy>=ENEMY1) world.npc.draw(world.atmosphere, *csSorted[1], *csSorted[1]->status.target);
			//	if(numEnemy>=ENEMY2) world.npc.draw(world.atmosphere, *csSorted[2], *csSorted[2]->status.target);
			//	if(numEnemy>=ENEMY3) world.npc.draw(world.atmosphere, *csSorted[3], *csSorted[3]->status.target);
			//	if(numEnemy>=ENEMY4) world.npc.draw(world.atmosphere, *csSorted[4], *csSorted[4]->status.target);
			//	gameVars->player.active->init.bActive = false;	//This resets the default value of the active tag in case the active player changes later

			Core.matrix.Pop();
		//}
	//}

	//SDL_GL_SwapBuffers();
}

void RunBattle::getInput() {
	//Event capturing
	SDL_PumpEvents();


	if (gameVars->controls.mouse.bEnable) {
		//Get relative mouse movement
		SDL_GetMouseState(&gameVars->controls.mouse.x, &gameVars->controls.mouse.y);

		float tX, tY;
		tX=gameVars->controls.mouse.relX;
		tY=gameVars->controls.mouse.relY;
		gameVars->controls.mouse.relX=gameVars->controls.mouse.x-gameVars->screen.halfW;
		gameVars->controls.mouse.relY=gameVars->controls.mouse.y-gameVars->screen.halfH;

		SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
		if (gameVars->controls.mouse.lock) SDL_WarpMouse(gameVars->screen.halfW, gameVars->screen.halfH);
		SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);

		if (gameVars->controls.mouse.hide) SDL_ShowCursor(SDL_DISABLE);
		else SDL_ShowCursor(SDL_ENABLE);
	}
	else {
		SDL_ShowCursor(SDL_ENABLE);

		gameVars->controls.mouse.relX = 0;
		gameVars->controls.mouse.relY = 0;

		if(SDL_GetMouseState(&gameVars->controls.mouse.x, &gameVars->controls.mouse.y)&SDL_BUTTON(1)) gameVars->controls.mouse.button.check[0]=true;
		else gameVars->controls.mouse.button.check[0]=false;
	}

	keyboard.event = SDL_GetKeyState(NULL);

	//Left Mouse button
	if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)) gameVars->controls.mouse.button.check[0]=true;
	else gameVars->controls.mouse.button.check[0]=false;

	//Right Mouse button
	if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(3)) gameVars->controls.mouse.button.check[2]=true;
	else gameVars->controls.mouse.button.check[2]=false;

	//Execute input commands
	gameSys.mouseSys.checkButton(0);

	keyboard.update();
	processInput();
}

void RunBattle::UpdateMovement(CharSheet &sheet) {
		//Update allowed movement
		float tx, tz, tt;
		if (sheet.status.move.now < sheet.status.move.max) {
			//tx = gameVars->transform.worldPos[0]-sheet.status.move.x;
			//tz = gameVars->transform.worldPos[2]-sheet.status.move.z;
			tx = sheet.transform.pos[0]-sheet.status.move.x;
			tz = sheet.transform.pos[2]-sheet.status.move.z;
			tt = sqrt(sqr(tx)+sqr(tz))/16;
			sheet.status.move.x = abs(sheet.transform.pos[0]);
			sheet.status.move.z = abs(sheet.transform.pos[2]);
			//status.move.now += tt;
			sheet.status.move.now = tt;
		}
		printf("i: %f,%f, f: %f,%f\n", sheet.transform.pos[0], sheet.transform.pos[2], sheet.status.move.x, sheet.status.move.z);
		printf("Max: %i, Now: %f\n", sheet.status.move.max, sheet.status.move.now);
		if (sheet.status.move.now >= sheet.status.move.max) {
			sheet.status.move.allow = false;
			//sheet.status.mouseLook = false;
			ToggleMouse(false);
		}
}

void RunBattle::processInput(uint key) {
	keyboard.bKey[key] = true;
	processInput();
}

void RunBattle::processInput() {
	//float moveMod;
	if(gameVars->player.active->status.iState == GAME::MENU.CAST.SPELL) {
		if (keyboard.bKey[SDLK_ESCAPE]) {
			gameVars->player.active->status.iState=GAME::MENU.STATE.INIT;
			gameVars->player.active->status.iIntent = GAME::MENU.INTENT.CAST_SPELL;
			gameVars->state.menu = true;
		}
	}
	else {
		if (keyboard.bKey[SDLK_ESCAPE]) {
			EndBattle();
		}

		if (keyboard.bKey[gameVars->controls.key.open_menu]) {
			//SDL_ShowCursor(SDL_ENABLE);
			gameVars->menu.bActionIcon=true;
			gameVars->menu.bStatus=true;
			gameVars->menu.bIntent=false;
			gameVars->menu.bOperations=true;
			gameVars->state.menu=true;
		}

		if (keyboard.bKey[gameVars->controls.key.open_intent]) {
			//SDL_ShowCursor(SDL_ENABLE);
			gameVars->menu.bActionIcon=true;
			gameVars->menu.bStatus=true;
			gameVars->menu.bIntent=true;
			gameVars->menu.bOperations=false;
			gameVars->state.menu=true;
		}

		if (keyboard.bKey[SDLK_SPACE]) {
			NextTarget();
		}

		if (keyboard.bKey[SDLK_RETURN]){
			printf("Cannot execute events during battle!");
		}

		if (keyboard.bKey[SDLK_TAB]) {
			//Toggle(sheet.status.mouseLook);
			//SDL_WarpMouse(gameVars->screen.halfW, gameVars->screen.halfH);
			ToggleMouse();
		}

		if (keyboard.bKey[SDLK_LCTRL]){
			//moveMod=0.40;
		}

		if (keyboard.bKey[SDLK_LSHIFT]){
			//moveMod=10.00;
		}

		if (!keyboard.bKey[SDLK_LSHIFT] && !keyboard.bKey[SDLK_LCTRL]) {
			//moveMod=1;
		}

		if (keyboard.bKey[SDLK_b]){
			gameVars->state.battle=false;
			SDL_WarpMouse(gameVars->screen.halfW, gameVars->screen.halfH);
		}

		//PLAYER MOVEMENT
		if (gameVars->player.active->status.move.allow && gameVars->controls.mouse.bEnable) {
			bool bMoved = false;
			if (keyboard.bKey[gameVars->controls.key.strafe_left]){
				int iAirControl = 1;
				//if (gameVars->player.active->transform.pos[1] < gameVars->transform.groundHeight) iAirControl = 2;

				gameVars->player.active->transform.pos[0]+=(float)cos( gameVars->player.active->transform.rot[1] ) * ((gameVars->controls.moveSpeed / iAirControl)*gameVars->player.active->status.move.fMoveMod);
				gameVars->player.active->transform.pos[2]+=(float)sin( gameVars->player.active->transform.rot[1] ) * ((gameVars->controls.moveSpeed / iAirControl)*gameVars->player.active->status.move.fMoveMod);

				bMoved = true;
			}
			if (keyboard.bKey[gameVars->controls.key.strafe_right]){
				int iAirControl = 1;
				//if (gameVars->player.active->transform.pos[1] < gameVars->transform.groundHeight) iAirControl = 2;

				gameVars->player.active->transform.pos[0]-=(float)cos( gameVars->player.active->transform.rot[1] ) * ((gameVars->controls.moveSpeed / iAirControl)*gameVars->player.active->status.move.fMoveMod);
				gameVars->player.active->transform.pos[2]-=(float)sin( gameVars->player.active->transform.rot[1] ) * ((gameVars->controls.moveSpeed / iAirControl)*gameVars->player.active->status.move.fMoveMod);

				bMoved = true;
			}
			if (keyboard.bKey[gameVars->controls.key.move_forward]) {
				int iAirControl = 1;
				//if (gameVars->player.active->transform.pos[1] < gameVars->transform.groundHeight) iAirControl = 2;

				gameVars->player.active->transform.pos[0]-=(float)sin( gameVars->player.active->transform.rot[1] ) * ((gameVars->controls.moveSpeed / iAirControl)*gameVars->player.active->status.move.fMoveMod);
				gameVars->player.active->transform.pos[2]+=(float)cos( gameVars->player.active->transform.rot[1] ) * ((gameVars->controls.moveSpeed / iAirControl)*gameVars->player.active->status.move.fMoveMod);

				bMoved = true;
			}
			if (keyboard.bKey[gameVars->controls.key.move_back]) {
				int iAirControl = 1;
				//if (gameVars->player.active->transform.pos[1] < gameVars->transform.groundHeight) iAirControl = 2;

				gameVars->player.active->transform.pos[0]+=(float)sin( gameVars->player.active->transform.rot[1] ) * ((gameVars->controls.moveSpeed / iAirControl) * gameVars->player.active->status.move.fMoveMod);
				gameVars->player.active->transform.pos[2]-=(float)cos( gameVars->player.active->transform.rot[1] ) * ((gameVars->controls.moveSpeed / iAirControl) * gameVars->player.active->status.move.fMoveMod);

				bMoved = true;
			}
			if (keyboard.bKey[gameVars->controls.key.move_up]) {
				if (gameVars->controls.fly) gameVars->player.active->transform.pos[1]-=gameVars->controls.moveSpeed*gameVars->player.active->status.move.fMoveMod;
			}
			if (keyboard.bKey[gameVars->controls.key.move_down]) {
				if (gameVars->controls.fly) gameVars->player.active->transform.pos[1]+=gameVars->controls.moveSpeed*gameVars->player.active->status.move.fMoveMod;
			}

			float tx, tz, tt;
			if (bMoved) {
				tx = abs(gameVars->player.active->transform.pos[0])-abs(gameVars->player.active->status.move.x);
				tz = abs(gameVars->player.active->transform.pos[2])-abs(gameVars->player.active->status.move.z);
				tt = sqrt(sqr(tx)+sqr(tz))/16;
				gameVars->player.active->status.move.x = gameVars->player.active->transform.pos[0];
				gameVars->player.active->status.move.z = gameVars->player.active->transform.pos[2];
				gameVars->player.active->status.move.now += tt;
				gameVars->player.active->transform.pos[1] = world.map.getHeight(gameVars->player.active->transform.pos[0], gameVars->player.active->transform.pos[2])*gameVars->screen.iScale;
			}
			//printf("i: %f,%f, f: %f,%f\n", gameVars->transform.worldPos[0], gameVars->transform.worldPos[2], status.move.x, status.move.z);
			//printf("Max: %i, Now: %f\n", status.move.max, status.move.now);
			if (gameVars->player.active->status.move.now >= gameVars->player.active->status.move.max) {
				gameVars->player.active->status.move.allow = false;
				//gameVars->player.active->status.mouseLook = false;
				ToggleMouse(false);
			}
		}


		if (keyboard.bKey[gameVars->controls.key.jump]) {
			//if (gameVars->player.active->transform.pos[1] == gameVars->transform.groundHeight) {
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
		}
		if (keyboard.bKey[SDLK_F2]) {
			//printf("Force Flush and Finish GL commands\n");
			//glFlush();
			//glFinish();
		}
		if (keyboard.bKey[SDLK_F3]) {
		}
		if (keyboard.bKey[SDLK_F4]) {
			EndBattle();
		}
		if (keyboard.bKey[SDLK_F5]) {
			gameVars->screen.clear = GL_DEPTH_BUFFER_BIT;
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
			if (gameVars->controls.mouse.bEnable) {
				gameVars->controls.mouse.bEnable = false;
			}
			else {
				gameVars->controls.mouse.bEnable = true;
			}
		}
		if (keyboard.bKey[SDLK_F9]) {
			Toggle(gameVars->controls.fly);
		}

		if (keyboard.bKey[SDLK_F10]) {
			Toggle(gameVars->controls.mouse.lock);
		}

		if (keyboard.bKey[SDLK_F11]) {
			Toggle(gameVars->controls.mouse.hide);
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
			gameVars->player.active->transform.rot[1]+=(gameVars->controls.mouse.relX/1000)*gameVars->controls.mouse.sensX;
			if (M_RadToDeg(gameVars->player.active->transform.rot[1])>360) gameVars->player.active->transform.rot[1] = gameVars->player.active->transform.rot[1] - M_DegToRad(360);
			if (M_RadToDeg(gameVars->player.active->transform.rot[1]) < 0) gameVars->player.active->transform.rot[1] = gameVars->player.active->transform.rot[1] = M_DegToRad(360) + gameVars->player.active->transform.rot[1];
		}
		if (gameVars->controls.mouse.relX>gameVars->controls.mouse.deadX) {
			gameVars->player.active->transform.rot[1]+=(gameVars->controls.mouse.relX/1000)*gameVars->controls.mouse.sensX;
			if (M_RadToDeg(gameVars->player.active->transform.rot[1])>360) gameVars->player.active->transform.rot[1] = gameVars->player.active->transform.rot[1] - M_DegToRad(360);
			if (M_RadToDeg(gameVars->player.active->transform.rot[1]) < 0) gameVars->player.active->transform.rot[1] = gameVars->player.active->transform.rot[1] = M_DegToRad(360) + gameVars->player.active->transform.rot[1];
		}
		if (gameVars->controls.mouse.relY<-gameVars->controls.mouse.deadY) {
			gameVars->player.active->transform.rot[0]+=(gameVars->controls.mouse.relY/1000)*gameVars->controls.mouse.sensY;
		}
		if (gameVars->controls.mouse.relY>gameVars->controls.mouse.deadY) {
			gameVars->player.active->transform.rot[0]+=(gameVars->controls.mouse.relY/1000)*gameVars->controls.mouse.sensY;
		}
	}
}
#endif /* RUNBATTLE_H_ */
