/*
 * debug.h
 *
 *  Created on: Aug 2, 2015
 *      Author: bcthund
 */

#ifndef DEBUG_H_
#define DEBUG_H_

/*
 * Also used for card information, this gets the actual text for the given
 * 		limb damage so we can write the information to the screen.
 */
std::string RunBattle::GetAttackStat(unsigned int iC, unsigned int iT) {
	std::string message;
	switch (iT) {
		case GAME::WEAPON.TYPE.BLADE:
			switch (iC) {
				case ONE:
					message += "has a Cut";
					break;
				case TWO:
					message += "has a Laceration";
					break;
				case THREE:
					message += "has a Deep Laceration";
					break;
				case FOUR:
					message += "has been Cleaved";
					break;
			}
			break;
		case GAME::WEAPON.TYPE.BLUNT:
			switch (iC) {
				case ONE:
					message += "has a Deep Bruise";
					break;
				case TWO:
					message += "has a Bruised Bone";
					break;
				case THREE:
					message += "has a Cracked Bone";
					break;
				case FOUR:
					message += "has been Crushed";
					break;
			}
			break;
		case GAME::WEAPON.TYPE.AXE:
			switch (iC) {
				case ONE:
					message += "has a Gash";
					break;
				case TWO:
					message += "has a Fracture";
					break;
				case THREE:
					message += "has a Bone Splinter";
					break;
				case FOUR:
					message += "has been Hewed";
					break;
			}
			break;
		case GAME::WEAPON.TYPE.SPEAR:
			switch (iC) {
				case ONE:
					message += "has been Sliced";
					break;
				case TWO:
					message += "has been Poked";
					break;
				case THREE:
					message += "has been Stabbed";
					break;
				case FOUR:
					message += "has been Impailed";
					break;
			}
			break;
		case GAME::WEAPON.TYPE.ARROW:
			switch (iC) {
				case ONE:
					message += "has been Nicked";
					break;
				case TWO:
					message += "has been Pricked";
					break;
				case THREE:
					message += "has been Punctured";
					break;
				case FOUR:
					message += "has been Skewered";
					break;
			}
			break;

		case GAME::WEAPON.TYPE.JAW:
			switch (iC) {
				case ONE:
					message += "has been Bitten";
					break;
				case TWO:
					message += "has been Compressed";
					break;
				case THREE:
					message += "has been Torn";
					break;
				case FOUR:
					message += "has been Mutilated";
					break;
			}
			break;

		case GAME::WEAPON.TYPE.CLAW:
			switch (iC) {
				case ONE:
					message += "has been Chafed";
					break;
				case TWO:
					message += "has been Scuffed";
					break;
				case THREE:
					message += "has been Scratched";
					break;
				case FOUR:
					message += "has been Mauled";
					break;
			}
			break;

		case GAME::WEAPON.TYPE.HAND:
			switch (iC) {
				case ONE:
					message += "has been Slapped";
					break;
				case TWO:
					message += "has been Bruised";
					break;
				case THREE:
					message += "has been Deeply Bruised";
					break;
				case FOUR:
					message += "Bone has been Bruised";
					break;
			}
			break;
	}
	return message;
}

/*
 * Debugging function
 * Shows the relevant character sheet data for the current target.
 */
void RunBattle::ShowStats() {

	float fScreenHeight	= gameVars->screen.h;
	float fScreenWidth	= gameVars->screen.w;
	int X = gameVars->screen.iGridOffset;
	int Z = gameVars->screen.iGridOffset;
	//Draw Manu
	#define x 0
	#define y 1
	#define w 2
	#define h 3


	Vector4f c;

	/*
	 * Attacker
	 */
	c[x]=(fScreenWidth / gameVars->font.vSize[0]) - 31;
	c[y]=0;
	c[w]=30;
	c[h]=24;
	gameSys.drawWindow(c[x], c[y], c[w], c[h], false, true, vTint);

	gameSys.textSys.draw(c[x]+1, ++c[y], 7, "Stats: ", gameVars->player.active->init.name);

	//gameSys.drawText(c[x]+1, ++c[y], "Player Stats");

	int i1 = 12;
	int i2 = 16;
	int i3 = 20;
	int i4 = 24;

	/*
	 * Attacker
	 */
	gameSys.drawText(c[x]+2, ++c[y], "Hit Points");
		if(gameVars->player.active->damage.hit_points<gameVars->player.active->mod.hit_points) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.hit_points, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.hit_points, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "Upper Left Arm");
		if(gameVars->player.active->damage.limb.left_arm[UPPER].durability<100) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.limb.left_arm[UPPER].durability, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.limb.left_arm[UPPER].durability, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "Upper Right Arm");
		if(gameVars->player.active->damage.limb.right_arm[UPPER].durability<100) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.limb.right_arm[UPPER].durability, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.limb.right_arm[UPPER].durability, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "Lower Left Arm");
		if(gameVars->player.active->damage.limb.left_arm[LOWER].durability<100) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.limb.left_arm[LOWER].durability, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.limb.left_arm[LOWER].durability, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "Lower Right Arm");
		if(gameVars->player.active->damage.limb.right_arm[LOWER].durability<100) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.limb.right_arm[LOWER].durability, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.limb.right_arm[LOWER].durability, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "Upper Left Leg");
		if(gameVars->player.active->damage.limb.left_leg[UPPER].durability<100) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.limb.left_leg[UPPER].durability, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.limb.left_leg[UPPER].durability, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "Upper Right Leg");
		if(gameVars->player.active->damage.limb.right_leg[UPPER].durability<100) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.limb.right_leg[UPPER].durability, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.limb.right_leg[UPPER].durability, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "Lower Left Leg");
		if(gameVars->player.active->damage.limb.left_leg[LOWER].durability<100) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.limb.left_leg[LOWER].durability, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.limb.left_leg[LOWER].durability, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "Lower Right Leg");
		if(gameVars->player.active->damage.limb.right_leg[LOWER].durability<100) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.limb.right_leg[LOWER].durability, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.limb.right_leg[LOWER].durability, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "Torso");
		if(gameVars->player.active->damage.limb.torso.durability<100) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.limb.torso.durability, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.limb.torso.durability, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "Head");
		if(gameVars->player.active->damage.limb.head.durability<100) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.limb.head.durability, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->damage.limb.head.durability, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "moveDistance");
		gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->mod.moveDistance, 10), gameVars->color.green);

	int A,B,C,D;
	std::string type;
	/*
	switch(gameVars->weapon[gameVars->player.active->status.target->items.weapon.equipped].type) {
		case GAME::WEAPON.TYPE.BLADE:
			A = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].blade][ZERO];
			B = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].blade][ONE];
			C = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].blade][TWO];
			D = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].blade][THREE];
			type = "BLADE";
			break;
		case GAME::WEAPON.TYPE.BLUNT:
			A = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].blunt][ZERO];
			B = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].blunt][ONE];
			C = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].blunt][TWO];
			D = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].blunt][THREE];
			type = "BLUNT";
			break;
		case GAME::WEAPON.TYPE.AXE:
			A = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].axe][ZERO];
			B = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].axe][ONE];
			C = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].axe][TWO];
			D = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].axe][THREE];
			type = "AXE";
			break;
		case GAME::WEAPON.TYPE.SPEAR:
			A = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].spear][ZERO];
			B = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].spear][ONE];
			C = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].spear][TWO];
			D = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].spear][THREE];
			type = "SPEAR";
			break;
		case GAME::WEAPON.TYPE.ARROW:
			A = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].arrow][ZERO];
			B = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].arrow][ONE];
			C = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].arrow][TWO];
			D = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].arrow][THREE];
			type = "ARROW";
			break;
		case GAME::WEAPON.TYPE.JAW:
			A = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].jaw][ZERO];
			B = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].jaw][ONE];
			C = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].jaw][TWO];
			D = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].jaw][THREE];
			type = "JAW";
			break;
		case GAME::WEAPON.TYPE.CLAW:
			A = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].claw][ZERO];
			B = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].claw][ONE];
			C = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].claw][TWO];
			D = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].claw][THREE];
			type = "CLAW";
			break;
		case GAME::WEAPON.TYPE.HAND:
			A = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].hand][ZERO];
			B = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].hand][ONE];
			C = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].hand][TWO];
			D = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->items.armor.equipped].hand][THREE];
			type = "HAND";
			break;
	}
	*/

	gameSys.drawText(c[x]+1, ++++c[y], "Armor");
		//gameSys.drawText(c[x]+i1, c[y], gameVars->armor.type[gameVars->player.active->items.armor.equipped].name);
	gameSys.drawText(c[x]+2, ++c[y], type);
		gameSys.drawText(c[x]+i1, c[y], itoa(A, 10), gameVars->color.green);
		gameSys.drawText(c[x]+i2, c[y], itoa(B, 10), gameVars->color.green);
		gameSys.drawText(c[x]+i3, c[y], itoa(C, 10), gameVars->color.green);
		gameSys.drawText(c[x]+i4, c[y], itoa(D, 10), gameVars->color.green);

	gameSys.drawText(c[x]+1, ++++c[y], "Weapon");
		gameSys.drawText(c[x]+i1, c[y], gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iRight_Hand].id].name, gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "Critical");
		gameSys.drawText(c[x]+i1, c[y], itoa(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iRight_Hand].id].weapon->limb_1, 10), gameVars->color.green);
		gameSys.drawText(c[x]+i2, c[y], itoa(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iRight_Hand].id].weapon->limb_2, 10), gameVars->color.green);
		gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iRight_Hand].id].weapon->limb_3, 10), gameVars->color.green);
		gameSys.drawText(c[x]+i4, c[y], itoa(gameVars->items[gameVars->player.active->inventory.list[gameVars->player.active->inventory.equipped.equipment.iRight_Hand].id].weapon->limb_4, 10), gameVars->color.green);

	// TODO: the switch statements are incorrect here, the equipped item references the id of the inventory item, which references the item in the item database.

	int iChop   = 0;
	switch(gameVars->weapon[gameVars->player.active->inventory.equipped.equipment.iRight_Hand].chop) {
		case DAMAGE_CRITICAL_ZERO:
			iChop = 0;
			break;
		case DAMAGE_CRITICAL_ONE:
			iChop = 1;
			break;
		case DAMAGE_CRITICAL_TWO:
			iChop = 2;
			break;
		case DAMAGE_CRITICAL_THREE:
			iChop = 3;
			break;
		case DAMAGE_CRITICAL_FOUR:
			iChop = 4;
			break;
	}

	int iSwing  = 0;
	switch(gameVars->weapon[gameVars->player.active->inventory.equipped.equipment.iRight_Hand].swing) {
		case DAMAGE_CRITICAL_ZERO:
			iSwing = 0;
			break;
		case DAMAGE_CRITICAL_ONE:
			iSwing = 1;
			break;
		case DAMAGE_CRITICAL_TWO:
			iSwing = 2;
			break;
		case DAMAGE_CRITICAL_THREE:
			iSwing = 3;
			break;
		case DAMAGE_CRITICAL_FOUR:
			iSwing = 4;
			break;
	}

	int iThrust = 0;
	switch(gameVars->weapon[gameVars->player.active->inventory.equipped.equipment.iRight_Hand].thrust) {
		case DAMAGE_CRITICAL_ZERO:
			iThrust = 0;
			break;
		case DAMAGE_CRITICAL_ONE:
			iThrust = 1;
			break;
		case DAMAGE_CRITICAL_TWO:
			iThrust = 2;
			break;
		case DAMAGE_CRITICAL_THREE:
			iThrust = 3;
			break;
		case DAMAGE_CRITICAL_FOUR:
			iThrust = 4;
			break;
	}

	gameSys.drawText(c[x]+2, ++c[y], "Damage");
		gameSys.drawText(c[x]+i1, c[y], itoa(gameVars->weapon[gameVars->player.active->inventory.equipped.equipment.iRight_Hand].damage, 10), gameVars->color.green);
	gameSys.drawText(c[x]+i2, c[y], "Chop");
		gameSys.drawText(c[x]+i4, c[y], itoa(iChop, 10), gameVars->color.green);

	gameSys.drawText(c[x]+2, ++c[y], "Range");
		gameSys.drawText(c[x]+i1, c[y], itoa(gameVars->weapon[gameVars->player.active->inventory.equipped.equipment.iRight_Hand].range, 10), gameVars->color.green);
	gameSys.drawText(c[x]+i2, c[y], "Swing");
		gameSys.drawText(c[x]+i4, c[y], itoa(iSwing, 10), gameVars->color.green);

	gameSys.drawText(c[x]+2, ++c[y], "KD");
		gameSys.drawText(c[x]+i1, c[y], itoa(gameVars->weapon[gameVars->player.active->inventory.equipped.equipment.iRight_Hand].kd, 10), gameVars->color.green);
	gameSys.drawText(c[x]+i2, c[y], "Thrust");
		gameSys.drawText(c[x]+i4, c[y], itoa(iThrust, 10), gameVars->color.green);


	/*
	 * TARGET
	 */
	c[x]=(fScreenWidth / gameVars->font.vSize[0]) - 31;
	c[y]=24;
	c[w]=30;
	c[h]=24;
	gameSys.drawWindow(c[x], c[y], c[w], c[h], false, true, vTint);

	gameSys.textSys.draw(c[x]+1, ++c[y], 7, "Stats: ", gameVars->player.active->status.target->init.name);
	//gameSys.drawText(c[x]+1, ++c[y], "Enemy Stats");

	i1 = 12;
	i2 = 16;
	i3 = 20;
	i4 = 24;

	gameSys.drawText(c[x]+2, ++c[y], "Hit Points");
		if(gameVars->player.active->status.target->damage.hit_points<100) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.hit_points, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.hit_points, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "Upper Left Arm");
		if(gameVars->player.active->status.target->damage.limb.left_arm[UPPER].durability<100) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.limb.left_arm[UPPER].durability, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.limb.left_arm[UPPER].durability, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "Upper Right Arm");
		if(gameVars->player.active->status.target->damage.limb.right_arm[UPPER].durability<100) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.limb.right_arm[UPPER].durability, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.limb.right_arm[UPPER].durability, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "Lower Left Arm");
		if(gameVars->player.active->status.target->damage.limb.left_arm[LOWER].durability<100) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.limb.left_arm[LOWER].durability, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.limb.left_arm[LOWER].durability, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "Lower Right Arm");
		if(gameVars->player.active->status.target->damage.limb.right_arm[LOWER].durability<100) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.limb.right_arm[LOWER].durability, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.limb.right_arm[LOWER].durability, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "Upper Left Leg");
		if(gameVars->player.active->status.target->damage.limb.left_leg[UPPER].durability<100) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.limb.left_leg[UPPER].durability, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.limb.left_leg[UPPER].durability, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "Upper Right Leg");
		if(gameVars->player.active->status.target->damage.limb.right_leg[UPPER].durability<100) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.limb.right_leg[UPPER].durability, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.limb.right_leg[UPPER].durability, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "Lower Left Leg");
		if(gameVars->player.active->status.target->damage.limb.left_leg[LOWER].durability<100) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.limb.left_leg[LOWER].durability, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.limb.left_leg[LOWER].durability, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "Lower Right Leg");
		if(gameVars->player.active->status.target->damage.limb.right_leg[LOWER].durability<100) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.limb.right_leg[LOWER].durability, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.limb.right_leg[LOWER].durability, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "Torso");
		if(gameVars->player.active->status.target->damage.limb.torso.durability<100) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.limb.torso.durability, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.limb.torso.durability, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "Head");
		if(gameVars->player.active->status.target->damage.limb.head.durability<100) gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.limb.head.durability, 10), gameVars->color.yellow);
		else gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->damage.limb.head.durability, 10), gameVars->color.green);
	gameSys.drawText(c[x]+2, ++c[y], "moveDistance");
		gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->player.active->status.target->mod.moveDistance, 10), gameVars->color.green);

	A = 0;
	B = 0;
	C = 0;
	D = 0;
	type = "";
	/*
	switch(gameVars->weapon[gameVars->player.active->items.weapon.equipped].type) {
		case GAME::WEAPON.TYPE.BLADE:
			A = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].blade][ZERO];
			B = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].blade][ONE];
			C = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].blade][TWO];
			D = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].blade][THREE];
			type = "BLADE";
			break;
		case GAME::WEAPON.TYPE.BLUNT:
			A = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].blunt][ZERO];
			B = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].blunt][ONE];
			C = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].blunt][TWO];
			D = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].blunt][THREE];
			type = "BLUNT";
			break;
		case GAME::WEAPON.TYPE.AXE:
			A = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].axe][ZERO];
			B = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].axe][ONE];
			C = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].axe][TWO];
			D = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].axe][THREE];
			type = "AXE";
			break;
		case GAME::WEAPON.TYPE.SPEAR:
			A = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].spear][ZERO];
			B = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].spear][ONE];
			C = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].spear][TWO];
			D = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].spear][THREE];
			type = "SPEAR";
			break;
		case GAME::WEAPON.TYPE.ARROW:
			A = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].arrow][ZERO];
			B = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].arrow][ONE];
			C = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].arrow][TWO];
			D = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].arrow][THREE];
			type = "ARROW";
			break;
		case GAME::WEAPON.TYPE.JAW:
			A = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].jaw][ZERO];
			B = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].jaw][ONE];
			C = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].jaw][TWO];
			D = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].jaw][THREE];
			type = "JAW";
			break;
		case GAME::WEAPON.TYPE.CLAW:
			A = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].claw][ZERO];
			B = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].claw][ONE];
			C = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].claw][TWO];
			D = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].claw][THREE];
			type = "CLAW";
			break;
		case GAME::WEAPON.TYPE.HAND:
			A = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].hand][ZERO];
			B = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].hand][ONE];
			C = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].hand][TWO];
			D = gameVars->armor.res[gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].hand][THREE];
			type = "HAND";
			break;
	}
	*/

	gameSys.drawText(c[x]+1, ++++c[y], "Armor");
		//gameSys.drawText(c[x]+i1, c[y], gameVars->armor.type[gameVars->player.active->status.target->items.armor.equipped].name);
	gameSys.drawText(c[x]+2, ++c[y], type);
		gameSys.drawText(c[x]+i1, c[y], itoa(A, 10), gameVars->color.green);
		gameSys.drawText(c[x]+i2, c[y], itoa(B, 10), gameVars->color.green);
		gameSys.drawText(c[x]+i3, c[y], itoa(C, 10), gameVars->color.green);
		gameSys.drawText(c[x]+i4, c[y], itoa(D, 10), gameVars->color.green);

	gameSys.drawText(c[x]+1, ++++c[y], "Weapon");
		gameSys.drawText(c[x]+i1, c[y], gameVars->items[gameVars->player.active->status.target->inventory.list[gameVars->player.active->status.target->inventory.equipped.equipment.iRight_Hand].id].name);
	gameSys.drawText(c[x]+2, ++c[y], "Critical");
		gameSys.drawText(c[x]+i1, c[y], itoa(gameVars->items[gameVars->player.active->status.target->inventory.list[gameVars->player.active->status.target->inventory.equipped.equipment.iRight_Hand].id].weapon->limb_1, 10), gameVars->color.green);
		gameSys.drawText(c[x]+i2, c[y], itoa(gameVars->items[gameVars->player.active->status.target->inventory.list[gameVars->player.active->status.target->inventory.equipped.equipment.iRight_Hand].id].weapon->limb_2, 10), gameVars->color.green);
		gameSys.drawText(c[x]+i3, c[y], itoa(gameVars->items[gameVars->player.active->status.target->inventory.list[gameVars->player.active->status.target->inventory.equipped.equipment.iRight_Hand].id].weapon->limb_3, 10), gameVars->color.green);
		gameSys.drawText(c[x]+i4, c[y], itoa(gameVars->items[gameVars->player.active->status.target->inventory.list[gameVars->player.active->status.target->inventory.equipped.equipment.iRight_Hand].id].weapon->limb_4, 10), gameVars->color.green);

	iChop   = 0;
	switch(gameVars->weapon[gameVars->player.active->status.target->inventory.equipped.equipment.iRight_Hand].chop) {
		case DAMAGE_CRITICAL_ZERO:
			iChop = 0;
			break;
		case DAMAGE_CRITICAL_ONE:
			iChop = 1;
			break;
		case DAMAGE_CRITICAL_TWO:
			iChop = 2;
			break;
		case DAMAGE_CRITICAL_THREE:
			iChop = 3;
			break;
		case DAMAGE_CRITICAL_FOUR:
			iChop = 4;
			break;
	}

	iSwing  = 0;
	switch(gameVars->weapon[gameVars->player.active->status.target->inventory.equipped.equipment.iRight_Hand].swing) {
		case DAMAGE_CRITICAL_ZERO:
			iSwing = 0;
			break;
		case DAMAGE_CRITICAL_ONE:
			iSwing = 1;
			break;
		case DAMAGE_CRITICAL_TWO:
			iSwing = 2;
			break;
		case DAMAGE_CRITICAL_THREE:
			iSwing = 3;
			break;
		case DAMAGE_CRITICAL_FOUR:
			iSwing = 4;
			break;
	}

	iThrust = 0;
	switch(gameVars->weapon[gameVars->player.active->status.target->inventory.equipped.equipment.iRight_Hand].thrust) {
		case DAMAGE_CRITICAL_ZERO:
			iThrust = 0;
			break;
		case DAMAGE_CRITICAL_ONE:
			iThrust = 1;
			break;
		case DAMAGE_CRITICAL_TWO:
			iThrust = 2;
			break;
		case DAMAGE_CRITICAL_THREE:
			iThrust = 3;
			break;
		case DAMAGE_CRITICAL_FOUR:
			iThrust = 4;
			break;
	}

	gameSys.drawText(c[x]+2, ++c[y], "Damage");
		gameSys.drawText(c[x]+i1, c[y], itoa(gameVars->weapon[gameVars->player.active->status.target->inventory.equipped.equipment.iRight_Hand].damage, 10), gameVars->color.green);
	gameSys.drawText(c[x]+i2, c[y], "Chop");
		gameSys.drawText(c[x]+i4, c[y], itoa(iChop, 10), gameVars->color.green);

	gameSys.drawText(c[x]+2, ++c[y], "Range");
		gameSys.drawText(c[x]+i1, c[y], itoa(gameVars->weapon[gameVars->player.active->status.target->inventory.equipped.equipment.iRight_Hand].range, 10), gameVars->color.green);
	gameSys.drawText(c[x]+i2, c[y], "Swing");
		gameSys.drawText(c[x]+i4, c[y], itoa(iSwing, 10), gameVars->color.green);

	gameSys.drawText(c[x]+2, ++c[y], "KD");
		gameSys.drawText(c[x]+i1, c[y], itoa(gameVars->weapon[gameVars->player.active->status.target->inventory.equipped.equipment.iRight_Hand].kd, 10), gameVars->color.green);
	gameSys.drawText(c[x]+i2, c[y], "Thrust");
		gameSys.drawText(c[x]+i4, c[y], itoa(iThrust, 10), gameVars->color.green);

	#undef x
	#undef y
	#undef w
	#undef h
}

#endif /* DEBUG_H_ */
