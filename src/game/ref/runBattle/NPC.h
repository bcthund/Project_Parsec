/*
 * NPC.h
 *
 *  Created on: Nov 1, 2010
 *      Author: bcthund
 */

#ifndef NPC_H_
#define NPC_H_

class NPC {
	private:

	protected:

	public:
		NPC();
		//NPCData data[9][9];
		NPCSheet data[9][9];
		bool bLoad;
		bool init();
		bool load();
		bool calc();
		void draw(Atmosphere &a);
		void draw(Atmosphere &a, CharSheet &sheet);
		void draw(Atmosphere &a, CharSheet &sheet, CharSheet &lookAt);
		float height(float iX, float iZ, int gX, int gZ);
		int inline ApplyStatMod(int i);
		void LoadNpc(int x, int z, int id);
};

NPC::NPC() {
	bLoad = false;
}

bool NPC::init() {
	return true;
}

int inline NPC::ApplyStatMod(int i) {
	return 10*log(i)-26;
}

void NPC::LoadNpc(int x, int z, int id) {

	float	init_x					= 0,
			init_y					= 0,
			init_z					= 0,
			init_w					= 0,
			init_h					= 0,
			init_blend				= 0,
			mod_weight				= 0;

	std::string init_image			= "",
				init_name			= "";

	unsigned int	armor			= 0,
					weapon			= 0;

	unsigned int	str_aura		= 0,
					str_mind		= 0,
					fin_aura		= 0,
					fin_speed		= 0,
					mob_endurance	= 0,
					mob_speed		= 0,
					fat_endurance	= 0,
					fat_mind		= 0,
					vic_aura		= 0,
					vic_endurance	= 0,
					defense_mode	= 0,
					move_mode		= 0,
					attack_num		= 0,
					face			= 0,
					skill_dodge		= 0,
					skill_deflect	= 0,
					skill_block		= 0;

	/*
	 * Hard Coded NPC data
	 *
	 * This data is specific to this
	 * battle system and eventually needs
	 * to be made external to this system
	 */

	if (id==ENEMY1) {
		init_x			= 240;
		//init_y			= 0;		//Auto Calculated
		init_z			= 250;
	//	init_x			= rand() % 1025;
	//	init_z			= rand() % 1025;
		init_w			= 20;		//Character Width (meters * 16)
		init_h			= 48;		//Character height (meters * 16)
		init_blend		= 0;		//Offset into/out of ground
		mod_weight		= 1;		//Weight Modifier

		init_image		= "githyanki.png";		//Sprite image
		init_name		= "Zombie!";

		armor			= ARMOR_SKIN;			//Equipped Armor
		weapon			= WEAPON_HAND_00;		//Equipped Weapon

		str_aura		= 1;
		str_mind		= 1;
		fin_aura		= 1;
		fin_speed		= 100;
		mob_endurance	= 100;
		mob_speed		= 100;
		fat_endurance	= 60;
		fat_mind		= 1;
		vic_aura		= 1;
		vic_endurance	= 60;
		defense_mode	= GAME::MENU.DEFENSE.DODGE;
		move_mode		= GAME::MENU.MOVE.WALK;
		attack_num		= 1;
		face			= 3;
		skill_deflect	= 5;
		skill_dodge		= 5;
		skill_block		= 5;
	}

	if (id==ENEMY2) {
		init_x			= 250;
		//init_y			= 0;		//Auto Calculated
		init_z			= 250;
		//init_x			= rand() % 1025;
		//init_z			= rand() % 1025;
		init_w			= 28;		//Character Width (meters * 16)
		init_h			= 24;		//Character height (meters * 16)
		init_blend		= 0;		//Offset into/out of ground
		mod_weight		= 1;		//Weight Modifier

		init_image		= "sheep.png";		//Sprite image
		init_name		= "Sheep";

		armor			= ARMOR_FURR_MEDIUM;		//Equipped Armor
		weapon			= WEAPON_BITE_00;		//Equipped Weapon

		str_aura		= 1;
		str_mind		= 1;
		fin_aura		= 1;
		fin_speed		= 100;
		mob_endurance	= 100;
		mob_speed		= 100;
		fat_endurance	= 60;
		fat_mind		= 1;
		vic_aura		= 1;
		vic_endurance	= 60;
		defense_mode	= GAME::MENU.DEFENSE.DODGE;
		move_mode		= GAME::MENU.MOVE.WALK;
		attack_num		= 1;
		face			= 1;
		skill_deflect	= 5;
		skill_dodge		= 5;
		skill_block		= 5;
	}

	if (id==ENEMY3) {
		init_x			= 240;
		//init_y			= 0;		//Auto Calculated
		init_z			= 240;
		//init_x			= rand() % 1025;
		//init_z			= rand() % 1025;
		init_w			= 12;		//Character Width (meters * 16)
		init_h			= 8;		//Character height (meters * 16)
		init_blend		= 0;		//Offset into/out of ground
		mod_weight		= 1;		//Weight Modifier

		init_image		= "snail.png";		//Sprite image
		init_name		= "Snail";

		armor			= ARMOR_FURR_MEDIUM;		//Equipped Armor
		weapon			= WEAPON_BITE_00;		//Equipped Weapon

		str_aura		= 1;
		str_mind		= 1;
		fin_aura		= 1;
		fin_speed		= 100;
		mob_endurance	= 100;
		mob_speed		= 100;
		fat_endurance	= 60;
		fat_mind		= 1;
		vic_aura		= 1;
		vic_endurance	= 60;
		defense_mode	= GAME::MENU.DEFENSE.DODGE;
		move_mode		= GAME::MENU.MOVE.WALK;
		attack_num		= 1;
		face			= 2;
		skill_deflect	= 5;
		skill_dodge		= 5;
		skill_block		= 5;
	}

	if (id==ENEMY4) {
		init_x			= 260;
		//init_y		= 0;		//Auto Calculated
		init_z			= 260;
		//init_x			= rand() % 1025;
		//init_z			= rand() % 1025;
		init_w			= 19;		//Character Width (meters * 16)
		init_h			= 32;		//Character height (meters * 16)
		init_blend		= 0;		//Offset into/out of ground
		mod_weight		= 1;		//Weight Modifier

		init_image		= "squirrel.png";		//Sprite image
		init_name		= "Squirrel";

		armor			= ARMOR_FURR_MEDIUM;		//Equipped Armor
		weapon			= WEAPON_BITE_00;		//Equipped Weapon

		str_aura		= 10;
		str_mind		= 1;
		fin_aura		= 4;
		fin_speed		= 50;
		mob_endurance	= 10;
		mob_speed		= 60;
		fat_endurance	= 60;
		fat_mind		= 10;
		vic_aura		= 2;
		vic_endurance	= 20;
		defense_mode	= GAME::MENU.DEFENSE.DEFLECT;
		move_mode		= GAME::MENU.MOVE.WALK;
		attack_num		= 1;
		face			= 4;
		skill_deflect	= 5;
		skill_dodge		= 5;
		skill_block		= 5;
	}

	data[x][z].idcount++;

	//TEST NPC
	data[x][z].sheet[id].init.id									= id;
	data[x][z].sheet[id].init.x										= init_x;
	data[x][z].sheet[id].init.y										= 0;
	data[x][z].sheet[id].init.z										= init_z;
	//data[x][z].sheet[id].init[0].r								= 0;
	data[x][z].sheet[id].init.w										= init_w;
	data[x][z].sheet[id].init.h										= init_h;
	data[x][z].sheet[id].init.blend									= init_blend;
	data[x][z].sheet[id].init.image									= init_image;
	data[x][z].sheet[id].init.name									= init_name;

	if (data[x][z].sheet[id].init.isDead) data[x][z].sheet[id].init.isDead	= true;
	else data[x][z].sheet[id].init.isDead = false;

	data[x][z].sheet[id].transform.pos[0]							= data[x][z].sheet[id].init.x;
	data[x][z].sheet[id].transform.pos[1]							= data[x][z].sheet[id].init.y;
	data[x][z].sheet[id].transform.pos[2]							= data[x][z].sheet[id].init.z;

	data[x][z].sheet[id].items.armor.equipped						= armor;
	data[x][z].sheet[id].items.weapon.equipped						= weapon;

	//Attributes and Stats
	data[x][z].sheet[id].attributes.str.strength					= 0;
	data[x][z].sheet[id].attributes.str.aura						= str_aura;
	data[x][z].sheet[id].attributes.str.mind						= str_mind;

	data[x][z].sheet[id].attributes.fin.finesse						= 0;
	data[x][z].sheet[id].attributes.fin.aura						= fin_aura;
	data[x][z].sheet[id].attributes.fin.speed						= fin_speed;

	data[x][z].sheet[id].attributes.mob.mobility					= 0;
	data[x][z].sheet[id].attributes.mob.endurance					= mob_endurance;
	data[x][z].sheet[id].attributes.mob.speed						= mob_speed;

	data[x][z].sheet[id].attributes.fat.fatigue						= 0;
	data[x][z].sheet[id].attributes.fat.endurance					= fat_endurance;
	data[x][z].sheet[id].attributes.fat.mind						= fat_mind;

	data[x][z].sheet[id].attributes.vic.vicissitude					= 0;
	data[x][z].sheet[id].attributes.vic.aura						= vic_aura;
	data[x][z].sheet[id].attributes.vic.endurance					= vic_endurance;

	//Combat Checks
	data[x][z].sheet[id].combat_check.fortitude						= 0;
	data[x][z].sheet[id].combat_check.initiative					= 0;
	data[x][z].sheet[id].combat_check.reflex						= 0;
	data[x][z].sheet[id].combat_check.willpower						= 0;

	//Skill Checks
	data[x][z].sheet[id].skill_check.intelligence					= 0;
	data[x][z].sheet[id].skill_check.constitution					= 0;
	data[x][z].sheet[id].skill_check.charisma						= 0;
	data[x][z].sheet[id].skill_check.wisdom							= 0;
	data[x][z].sheet[id].skill_check.dynamism						= 0;
	data[x][z].sheet[id].skill_check.leadership						= 0;

	//Magic Checks
	data[x][z].sheet[id].magic_check.comprehension					= 0;
	data[x][z].sheet[id].magic_check.execution						= 0;
	data[x][z].sheet[id].magic_check.intensity						= 0;
	data[x][z].sheet[id].magic_check.mana							= 0;

	//Other Skills
	data[x][z].sheet[id].other_check.load							= 0;
	data[x][z].sheet[id].other_check.stamina						= 0;
	data[x][z].sheet[id].other_check.weight							= 0;

	//Loads
	data[x][z].sheet[id].load.heavy									= 0;
	data[x][z].sheet[id].load.medium								= 0;
	data[x][z].sheet[id].load.light									= 0;
	data[x][z].sheet[id].load.lift									= 0;
	data[x][z].sheet[id].load.raise									= 0;
	data[x][z].sheet[id].load.push									= 0;

	//Modifiers
	data[x][z].sheet[id].mod.attack_bonus							= 0;
	data[x][z].sheet[id].mod.combat_bonus							= 0;
	data[x][z].sheet[id].mod.hit_points								= 0;
	data[x][z].sheet[id].mod.to_hit									= 0;
	data[x][z].sheet[id].mod.weight									= mod_weight;


	//MAKE CALCULATIONS FROM LOADED VALUES
	data[x][z].sheet[id].stats.aura									= data[x][z].sheet[id].attributes.fin.aura
																		+ data[x][z].sheet[id].attributes.str.aura
																		+ data[x][z].sheet[id].attributes.vic.aura;
	data[x][z].sheet[id].stats.speed								= data[x][z].sheet[id].attributes.fin.speed
																		+ data[x][z].sheet[id].attributes.mob.speed;
	data[x][z].sheet[id].stats.endurance							= data[x][z].sheet[id].attributes.fat.endurance
																		+ data[x][z].sheet[id].attributes.mob.endurance
																		+ data[x][z].sheet[id].attributes.vic.endurance;
	data[x][z].sheet[id].stats.mind									= data[x][z].sheet[id].attributes.fat.mind
																		+ data[x][z].sheet[id].attributes.str.mind;
	data[x][z].sheet[id].mod.level									= data[x][z].sheet[id].stats.aura
																		+ data[x][z].sheet[id].stats.speed
																		+ data[x][z].sheet[id].stats.endurance
																		+ data[x][z].sheet[id].stats.mind;

	//USE MODULUS FOR SPECIALIZATION
	data[x][z].sheet[id].attributes.fat.fatigue						= ( data[x][z].sheet[id].attributes.fat.endurance
																		+ data[x][z].sheet[id].attributes.fat.mind )
																		/ 2;
	data[x][z].sheet[id].attributes.fat.mod							=	ApplyStatMod(data[x][z].sheet[id].attributes.fat.fatigue);

	data[x][z].sheet[id].attributes.fin.finesse						= ( data[x][z].sheet[id].attributes.fin.aura
																		+ data[x][z].sheet[id].attributes.fin.speed )
																		/ 2;
	data[x][z].sheet[id].attributes.fin.mod							=	ApplyStatMod(data[x][z].sheet[id].attributes.fin.finesse);

	data[x][z].sheet[id].attributes.mob.mobility					= ( data[x][z].sheet[id].attributes.mob.endurance
																		+ data[x][z].sheet[id].attributes.mob.speed )
																		/ 2;
	data[x][z].sheet[id].attributes.mob.mod							=	ApplyStatMod(data[x][z].sheet[id].attributes.mob.mobility);

	data[x][z].sheet[id].attributes.str.strength					= ( data[x][z].sheet[id].attributes.str.aura
																		+ data[x][z].sheet[id].attributes.str.mind )
																		/ 2;
	data[x][z].sheet[id].attributes.str.mod							=	ApplyStatMod(data[x][z].sheet[id].attributes.str.strength);

	data[x][z].sheet[id].attributes.vic.vicissitude					= ( data[x][z].sheet[id].attributes.vic.aura
																		+ data[x][z].sheet[id].attributes.vic.endurance )
																		/ 2;
	data[x][z].sheet[id].attributes.vic.mod							=	ApplyStatMod(data[x][z].sheet[id].attributes.vic.vicissitude);

	//Combat Checks
	data[x][z].sheet[id].combat_check.fortitude						= ApplyStatMod( data[x][z].sheet[id].stats.endurance	+	data[x][z].sheet[id].attributes.str.strength );
	data[x][z].sheet[id].combat_check.initiative					= ApplyStatMod( data[x][z].sheet[id].stats.mind		+	data[x][z].sheet[id].attributes.str.strength );
	data[x][z].sheet[id].combat_check.reflex						= ApplyStatMod( data[x][z].sheet[id].stats.speed		+	data[x][z].sheet[id].attributes.mob.mobility );
	data[x][z].sheet[id].combat_check.willpower						= ApplyStatMod( data[x][z].sheet[id].stats.aura		+	data[x][z].sheet[id].attributes.vic.vicissitude );

	//Skill Checks
	data[x][z].sheet[id].skill_check.intelligence					= ApplyStatMod( data[x][z].sheet[id].stats.mind		+	data[x][z].sheet[id].attributes.vic.vicissitude );
	data[x][z].sheet[id].skill_check.constitution					= ApplyStatMod( data[x][z].sheet[id].stats.mind		+	data[x][z].sheet[id].attributes.fat.fatigue );
	data[x][z].sheet[id].skill_check.charisma						= ApplyStatMod( data[x][z].sheet[id].stats.mind		+	data[x][z].sheet[id].attributes.fin.finesse );
	data[x][z].sheet[id].skill_check.wisdom							= ApplyStatMod( data[x][z].sheet[id].stats.aura		+	data[x][z].sheet[id].attributes.fin.finesse );

	//Other Skills
	data[x][z].sheet[id].other_check.load							= ((data[x][z].sheet[id].stats.endurance + data[x][z].sheet[id].attributes.str.strength) * 2);
	//data[x][z].sheet[id].other_check.mana							= ((data[x][z].sheet[id].attributes.fat.fatigue*4) * ((float(data[x][z].sheet[id].stats.mind)/100)+1));
	data[x][z].sheet[id].other_check.stamina						= ((data[x][z].sheet[id].attributes.fat.fatigue*4) * ((float(data[x][z].sheet[id].stats.endurance)/100)+1));
	data[x][z].sheet[id].other_check.weight							= (58 * log(data[x][z].sheet[id].stats.endurance+data[x][z].sheet[id].attributes.str.strength) + 20) * data[x][z].sheet[id].mod.weight;

	//Loads
	data[x][z].sheet[id].load.heavy									= 0.75	*	data[x][z].sheet[id].other_check.load;
	data[x][z].sheet[id].load.medium								= 0.50	*	data[x][z].sheet[id].other_check.load;
	data[x][z].sheet[id].load.light									= 0.25	*	data[x][z].sheet[id].other_check.load;
	data[x][z].sheet[id].load.raise						 			= 1		*	data[x][z].sheet[id].other_check.load;
	data[x][z].sheet[id].load.lift									= 2		*	data[x][z].sheet[id].other_check.load;
	data[x][z].sheet[id].load.push									= 3		*	data[x][z].sheet[id].other_check.load;

	//Modifiers
	data[x][z].sheet[id].mod.attack_bonus							= 20 * log(data[x][z].sheet[id].mod.level) - 82;
	data[x][z].sheet[id].mod.hit_points								= ( ( (float(data[x][z].sheet[id].stats.aura)/100)+1)
																		* (data[x][z].sheet[id].attributes.vic.vicissitude*4))
																		+ data[x][z].sheet[id].mod.level;
	data[x][z].sheet[id].mod.moveDistance							= (0.11*data[x][z].sheet[id].stats.speed)+1.90;

	//Skills
	if (data[x][z].sheet[id].skill_check.intelligence > data[x][z].sheet[id].skills.first) data[x][z].sheet[id].skills.max = data[x][z].sheet[id].skill_check.intelligence;
	else data[x][z].sheet[id].skills.max							= data[x][z].sheet[id].skills.first;
	data[x][z].sheet[id].skills.per									= data[x][z].sheet[id].skill_check.intelligence
																		+ data[x][z].sheet[id].skills.first;
	data[x][z].sheet[id].skills.id[CS.SKILL.BLOCK]					= skill_block;	// [Dynamism mod] + [Skill Level] + [Items/Effects]
	data[x][z].sheet[id].skills.id[CS.SKILL.DEFLECT]				= skill_deflect;
	data[x][z].sheet[id].skills.id[CS.SKILL.DODGE]					= skill_dodge;

	data[x][z].sheet[id].damage.hit_points							= data[x][z].sheet[id].mod.hit_points;
	data[x][z].sheet[id].damage.limb.head.durability				= 100;
	data[x][z].sheet[id].damage.limb.torso.durability				= 100;
	data[x][z].sheet[id].damage.limb.left_arm[UPPER].durability		= 100;
	data[x][z].sheet[id].damage.limb.left_arm[LOWER].durability		= 100;
	data[x][z].sheet[id].damage.limb.right_arm[UPPER].durability	= 100;
	data[x][z].sheet[id].damage.limb.right_arm[LOWER].durability	= 100;
	data[x][z].sheet[id].damage.limb.left_leg[UPPER].durability		= 100;
	data[x][z].sheet[id].damage.limb.left_leg[LOWER].durability		= 100;
	data[x][z].sheet[id].damage.limb.right_leg[UPPER].durability	= 100;
	data[x][z].sheet[id].damage.limb.right_leg[LOWER].durability	= 100;

	//data[x][z].sheet[id].status.choice.defense					=	defense_mode;
	//data[x][z].sheet[id].status.choice.move						=	move_mode;
	data[x][z].sheet[id].status.engage.attackNum					=	attack_num;
	data[x][z].sheet[id].status.move.iStance						=	GAME::MENU.MOVE.STANCE.STAND;
	data[x][z].sheet[id].status.iState								=	GAME::MENU.STATE.INIT;
	data[x][z].sheet[id].init.face									=   face;

	/*
	 * Setup inital cards
	 */
	data[x][z].sheet[id].status.iCards[0][0]						= GAME::CARDS.ICON.ONE_HEAD_TORSO;
	data[x][z].sheet[id].status.iCards[0][1]						= GAME::CARDS.ICON.ZERO;
	data[x][z].sheet[id].status.iCards[0][2]						= GAME::CARDS.ICON.BLANK;

	/*
	 * Spells
	 */
	data[x][z].sheet[id].magic.spells.bBookmark[0]					=	true;
	data[x][z].sheet[id].magic.spells.bBookmark[1]					=	true;
	data[x][z].sheet[id].magic.spells.bBookmark[2]					=	true;
	data[x][z].sheet[id].magic.spells.bBookmark[3]					=	true;
	data[x][z].sheet[id].magic.spells.bBookmark[4]					=	true;
	data[x][z].sheet[id].magic.spells.bBookmark[5]					=	false;
	data[x][z].sheet[id].magic.spells.bBookmark[6]					=	false;
	data[x][z].sheet[id].magic.spells.bBookmark[7]					=	false;

	data[x][z].sheet[id].magic.spells.iBookmark[0]					=	11;
	data[x][z].sheet[id].magic.spells.iBookmark[1]					=	7;
	data[x][z].sheet[id].magic.spells.iBookmark[2]					=	6;
	data[x][z].sheet[id].magic.spells.iBookmark[3]					=	8;
	data[x][z].sheet[id].magic.spells.iBookmark[4]					=	9;
	data[x][z].sheet[id].magic.spells.iBookmark[5]					=	10;
	data[x][z].sheet[id].magic.spells.iBookmark[6]					=	-1;
	data[x][z].sheet[id].magic.spells.iBookmark[7]					=	-1;

	//Spell blocks unlocked
	//12 maximum for NPC's, 8 max for players
	data[x][z].sheet[id].magic.spells.bSpellBlock[0][0]				=	true;
	data[x][z].sheet[id].magic.spells.bSpellBlock[0][1]				=	true;
	data[x][z].sheet[id].magic.spells.bSpellBlock[0][2]				=	true;
	data[x][z].sheet[id].magic.spells.bSpellBlock[0][3]				=	true;
	data[x][z].sheet[id].magic.spells.bSpellBlock[0][4]				=	false;

	data[x][z].sheet[id].magic.spells.bSpellBlock[1][0]				=	true;
	data[x][z].sheet[id].magic.spells.bSpellBlock[1][1]				=	true;
	data[x][z].sheet[id].magic.spells.bSpellBlock[1][2]				=	true;
	data[x][z].sheet[id].magic.spells.bSpellBlock[1][3]				=	false;
	data[x][z].sheet[id].magic.spells.bSpellBlock[1][4]				=	false;

	data[x][z].sheet[id].magic.spells.bSpellBlock[2][0]				=	true;
	data[x][z].sheet[id].magic.spells.bSpellBlock[2][1]				=	true;
	data[x][z].sheet[id].magic.spells.bSpellBlock[2][2]				=	false;
	data[x][z].sheet[id].magic.spells.bSpellBlock[2][3]				=	false;
	data[x][z].sheet[id].magic.spells.bSpellBlock[2][4]				=	false;

	data[x][z].sheet[id].magic.spells.bSpellBlock[3][0]				=	true;
	data[x][z].sheet[id].magic.spells.bSpellBlock[3][1]				=	true;
	data[x][z].sheet[id].magic.spells.bSpellBlock[3][2]				=	false;
	data[x][z].sheet[id].magic.spells.bSpellBlock[3][3]				=	false;
	data[x][z].sheet[id].magic.spells.bSpellBlock[3][4]				=	false;

	data[x][z].sheet[id].magic.spells.bSpellBlock[4][0]				=	true;
	data[x][z].sheet[id].magic.spells.bSpellBlock[4][1]				=	true;
	data[x][z].sheet[id].magic.spells.bSpellBlock[4][2]				=	false;
	data[x][z].sheet[id].magic.spells.bSpellBlock[4][3]				=	false;
	data[x][z].sheet[id].magic.spells.bSpellBlock[4][4]				=	false;

	data[x][z].sheet[id].magic.spells.iSpellBlock[0][0]				=	0;
}

bool NPC::load() {
	try {
		//Load NPC Information for current map
		int x=gameVars->screen.iGridOffset;
		int z=gameVars->screen.iGridOffset;

		LoadNpc(x, z, 0);
		LoadNpc(x, z, 1);
		LoadNpc(x, z, 2);
		LoadNpc(x, z, 3);

		bLoad = true;
		return true;
	}
	catch(...) {
		return false;
	}
}

float NPC::height(float iX, float iZ, int gX, int gZ) {
	//Define variables
		Vector3f a, b, c, d, p, q;
		float u, v, w, t;
		int opp, adj, h;
		int iResult;

		//Define the object position ray
		p[0] =  iX;
		p[1] =  -500;
		p[2] =  iZ;

		q[0] =  iX;
		q[1] =  500;
		q[2] =  iZ;

		//Set barycentrics to 0
		u = 0;
		v = 0;
		w = 0;
		t = 0;

	//Procedure Code Outline
	bool foundHeight=false;
	for (int i=0; i < world.map.mapData[gX][gZ].numFaces; i++) {
		//Get Triangle Data for current count
		//Get the triangle vertex data, for test point
		a[0] = world.map.mapData[gX][gZ].vVerts[int(world.map.mapData[gX][gZ].vGroups[i][0])][0]*16;
		a[1] = world.map.mapData[gX][gZ].vVerts[int(world.map.mapData[gX][gZ].vGroups[i][0])][1]*16;
		a[2] = world.map.mapData[gX][gZ].vVerts[int(world.map.mapData[gX][gZ].vGroups[i][0])][2]*16;

		//Check distance from object, if within 200 units { (Only check one vertex, this will suffice)
			//Distance Calculations
			opp = a[0] - iX;
			adj = a[2] - iZ;
			h = sqr(opp) + sqr(adj);
			h = sqrt(h);

			//If ray is inside triangle {
			if(h <= 50) {;
				//Get the rest of the triangle Data
				b[0] = world.map.mapData[gX][gZ].vVerts[int(world.map.mapData[gX][gZ].vGroups[i][1])][0]*16;
				b[1] = world.map.mapData[gX][gZ].vVerts[int(world.map.mapData[gX][gZ].vGroups[i][1])][1]*16;
				b[2] = world.map.mapData[gX][gZ].vVerts[int(world.map.mapData[gX][gZ].vGroups[i][1])][2]*16;
				c[0] = world.map.mapData[gX][gZ].vVerts[int(world.map.mapData[gX][gZ].vGroups[i][2])][0]*16;
				c[1] = world.map.mapData[gX][gZ].vVerts[int(world.map.mapData[gX][gZ].vGroups[i][2])][1]*16;
				c[2] = world.map.mapData[gX][gZ].vVerts[int(world.map.mapData[gX][gZ].vGroups[i][2])][2]*16;

				//Are we within the triangle?
				//Projection of triangle onto the xz plane, we don't care about the height right now
				Vector3f testA, testB,testC, testP;
				testA[0] = a[0];
				testA[1] = 0;
				testA[2] = a[2];
				testB[0] = b[0];
				testB[1] = 0;
				testB[2] = b[2];
				testC[0] = c[0];
				testC[1] = 0;
				testC[2] = c[2];
				testP[0] = p[0];
				testP[1] = 0;
				testP[2] = p[2];

				if (PointInTriangle(testP, testA, testB, testC)) {
					float temp;
					deepCopy(t, temp);
					iResult=IntersectTri(p, q, a, c, b, u, v, w, t);
					if (foundHeight) t = (t+temp)/2;
					//gameVars->transform.groundHeight = (100-(200*t));
					foundHeight=true;
					//printf("t=%f, %f, %f\n", t, (1000*t), -(500-(1000*t)));
				}
			}
		//if (foundHeight) break;
	}
	//if (foundHeight) return -(100-(200*t));
	if (foundHeight) return -(500-(1000*t));
	else return 0;
}

bool NPC::calc() {
	try {
		int iItemCount[255]	= {0};		//Current Item count for group

		//Standard Texture Coordinates
		Vector2f vCoords[] = { 1.0, 0.0,
							   0.0, 0.0,
							   0.0, 1.0,

							   1.0, 0.0,
							   0.0, 1.0,
							   1.0, 1.0 };


		//WE ONLY NEED THE CURRENT CHUNK
		for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
			for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {
			//int x=gameVars->screen.iGridOffset;
			//int z=gameVars->screen.iGridOffset;
			//const int num = gameVars->screen.iGridOffset;

			//printf("idCount=%i\n", data[x][z].idcount);

			for (int count=0; count < data[x][z].idcount; count++) {
				float fW = data[x][z].sheet[count].init.w/2;
				float fH = data[x][z].sheet[count].init.h;
				//printf("[%f, %f]", data[x][z].sheet[0].init[count].x, data[x][z].sheet[0].init[count].z);
				data[x][z].sheet[count].init.y = height(data[x][z].sheet[count].init.x, data[x][z].sheet[count].init.z, x, z);
				//printf("Height Calculated: %f", data[x][z].sheet[0].init[count].y);

				Vector3f vVerts[]	=	{	{	 fW,	fH,		0.0	},
											{	-fW,	fH,		0.0	},
											{	-fW,	0.0,	0.0	},

											{	 fW,	fH,		0.0	},
											{	-fW,	0.0,	0.0	},
											{	 fW,	0.0,	0.0	}	};

				data[x][z].sheet[count].init.vao.Begin(GL_TRIANGLES, 6, 1);
				data[x][z].sheet[count].init.vao.CopyData(GLA_VERTEX, vVerts);
				data[x][z].sheet[count].init.vao.CopyData(GLA_TEXTURE, vCoords, 0);
				data[x][z].sheet[count].init.vao.End();
			}
		} }
		return true;
	}
	catch(...) {
		return false;
	}
}

void NPC::draw(Atmosphere &a) {
	glDisable(GL_CULL_FACE);
	Core.shader.use(GLS_FONT);

		Vector3f	vCamPos;
		vCamPos[0] = -gameVars->player.active->transform.pos[0];
		vCamPos[1] = 0.0f;
		vCamPos[2] = -gameVars->player.active->transform.pos[2];
		Vector3f	vUp = { 0.0, 1.0, 0.0};
		Vector3f	vLook, vRight;

		// Standard Drawing routine (blending with shader)
		for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
			for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {
			//int x = gameVars->screen.iGridOffset;
			//int z = gameVars->screen.iGridOffset;
			float iGrid = gameVars->screen.iGridOffset*1024;
				for (int count=0; count < data[x][z].idcount; count++) {
					Core.matrix.Push();
						// Billboarding quicky
						// look = camera_pos - object_pos
						// up = y(normalized)
						// right = up x look (cross product)

						Vector3f	vObjPos = { float(data[x][z].sheet[count].init.x+iGrid), 0.0f, float(data[x][z].sheet[count].init.z+iGrid) };
						Diff(vLook, vCamPos, vObjPos);
						Normalize(vLook);
						Cross(vRight, vUp, vLook);

//Matrix44f	mTemp = {	1.0f, 0.0f, 0.0f, 0.0f,
//						0.0f, 1.0f, 0.0f, 0.0f,
//						0.0f, 0.0f, 1.0f, 0.0f,
//						vObjPos[0], vObjPos[1], vObjPos[2], 1.0f };

						Matrix44f	mTemp = {	vRight[0], vRight[1], vRight[2], 0.0f,
												0.0f, 1.0f, 0.0f, 0.0f,
												vLook[0], vLook[1], vLook[2], 0.0f,
												vObjPos[0], float(data[x][z].sheet[count].init.y+data[x][z].sheet[count].init.blend), vObjPos[2], 1.0f };

						Core.matrix.Apply(mTemp);
						Core.matrix.SetTransform();
						Core.shader.getUniform(GLS_FONT);

						gameVars->texture.sprite.Set(data[x][z].sheet[count].init.image);

						data[x][z].sheet[count].init.vao.Draw();
					Core.matrix.Pop();
				}
			}
		}
	glEnable(GL_CULL_FACE);
}

void NPC::draw(Atmosphere &a, CharSheet &sheet) {
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	Core.shader.use(GLS_FONT);

		/*
		 * Figure out what direction the npc should be facing
		 * which should always be his current target. We don't
		 * care who is targeting him.
		 */
		Vector3f	vObjPos = { -sheet.transform.pos[0], sheet.transform.pos[1], -sheet.transform.pos[2] };
		Matrix44f	mTemp = {	1.0f, 0.0f, 0.0f, 0.0f,
								0.0f, 1.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 1.0f, 0.0f,
								vObjPos[0], vObjPos[1]+sheet.init.blend-(sheet.init.h*0.25f), vObjPos[2], 1.0f };

		Vector3f vCamPos;
		vCamPos[0] = -sheet.status.target->transform.pos[0];
		vCamPos[1] = 0.0f;
		vCamPos[2] = -sheet.status.target->transform.pos[2];
		Vector3f	vUp = { 0.0, 1.0, 0.0};
		Vector3f	vLook, vRight;
		Diff(vLook, vCamPos, vObjPos);
		Normalize(vLook);
		Cross(vRight, vUp, vLook);

		Matrix44f	mLook = {	vRight[0],	vRight[1],	vRight[2],	0.0f,
								0.0f,		1.0f,		0.0f,		0.0f,
								vLook[0],	vLook[1],	vLook[2],	0.0f,
								0.0f,		0.0f,		0.0f,		1.0f };

		/*
		 * Lets get a waveform to vary the highlighting of the NPC
		 */
		float fWave = fabs(sin(gameVars->timer.frameRate.get_ticks()/1000));
		//cout << "WAVE: " << fWave << endl;

		/*
		 * Draw the npc
		 */
		Core.matrix.Push();
			Core.matrix.Apply(mTemp);
			Core.matrix.Apply(mLook);
			Core.matrix.Scale(1.5f, 1.5f, 1.5f);

			Vector4f vTempColor;

			vTempColor[0] = gameVars->font.vColor[0];
			vTempColor[1] = gameVars->font.vColor[1];
			vTempColor[2] = gameVars->font.vColor[2];
			vTempColor[3] = gameVars->font.vColor[3];

			gameVars->font.vColor[0] = 1.0;
			gameVars->font.vColor[1] = 0.0;
			gameVars->font.vColor[2] = 0.0;
			gameVars->font.vColor[3] = 1.0*fWave;

			Core.matrix.SetTransform();
			Core.shader.getUniform(GLS_FONT);
			//gameVars->texture.sprite.Set(sheet.init.image);
			gameVars->texture.sprite.Set("target.png");
			sheet.init.vao.Draw();

			gameVars->font.vColor[0] = vTempColor[0];
			gameVars->font.vColor[1] = vTempColor[1];
			gameVars->font.vColor[2] = vTempColor[2];
			gameVars->font.vColor[3] = vTempColor[3];
		Core.matrix.Pop();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
}

void NPC::draw(Atmosphere &a, CharSheet &sheet, CharSheet &lookAt) {
	glDisable(GL_CULL_FACE);
	//glDisable(GL_DEPTH_TEST);
	Core.shader.use(GLS_FONT);

		Vector3f	vObjPos = { -sheet.transform.pos[0], sheet.transform.pos[1], -sheet.transform.pos[2] };
		Matrix44f	mTemp = {	1.0f, 0.0f, 0.0f, 0.0f,
								0.0f, 1.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 1.0f, 0.0f,
								vObjPos[0], vObjPos[1]+sheet.init.blend, vObjPos[2], 1.0f };

		Vector3f vCamPos;
		vCamPos[0] = -lookAt.transform.pos[0];
		vCamPos[1] = 0.0f;
		vCamPos[2] = -lookAt.transform.pos[2];
		Vector3f	vUp = { 0.0, 1.0, 0.0};
		Vector3f	vLook, vRight;
		Diff(vLook, vCamPos, vObjPos);
		Normalize(vLook);
		Cross(vRight, vUp, vLook);

		Matrix44f	mLook = {	vRight[0],	vRight[1],	vRight[2],	0.0f,
								0.0f,		1.0f,		0.0f,		0.0f,
								vLook[0],	vLook[1],	vLook[2],	0.0f,
								0.0f,		0.0f,		0.0f,		1.0f };


		/*
		 * Draw the npc
		 */
		Core.matrix.Push();
			//if (!bb) Core.matrix.Rotate(mTemp, -sheet.transform.rot[1], 0, 1, 0);
			Core.matrix.Apply(mTemp);
			Core.matrix.Apply(mLook);
			Core.matrix.SetTransform();
			Core.shader.getUniform(GLS_FONT);
			gameVars->texture.sprite.Set(sheet.init.image);
			sheet.init.vao.Draw();
		Core.matrix.Pop();

		float fWave = sin((gameVars->timer.frameRate.get_ticks()/1000)*2)+5;
		//Vector3f	vObjPos = { -sheet.transform.pos[0], sheet.transform.pos[1]+sheet.init.blend+sheet.init.h+fWave, -sheet.transform.pos[2] };
		//Matrix44f	mTemp = {	1.0f, 0.0f, 0.0f, 0.0f,
		//						0.0f, 1.0f, 0.0f, 0.0f,
		//						0.0f, 0.0f, 1.0f, 0.0f,
		//						vObjPos[0], vObjPos[1]+sheet.init.blend, vObjPos[2], 1.0f };

		mTemp[13] += sheet.init.h+fWave;

		/*
		 * Draw the combat status card
		 */
		//glDisable(GL_DEPTH_TEST);
		Core.matrix.Push();
			Core.matrix.Apply(mTemp);

			//Undo known world rotations, forcing icon to face screen always
			Core.matrix.Rotate(gameVars->player.active->transform.rot[1], 0.0, -1.0, 0.0);
			Core.matrix.Rotate(gameVars->player.active->transform.rot[0], -1.0, 0.0, 0.0);

			//Core.matrix.Translate(0.0f, sheet.init.h+10, 0.0f);
			Core.matrix.Scale(0.10f, 0.15f, 0.0f);
			Core.matrix.SetTransform();
			Core.shader.getUniform(GLS_FONT);

			gameSys.iconSys.draw(0,sheet.status.iCards[0][0], sheet.status.iCards[0][1], sheet.status.iCards[0][2], "cards.png", GLS_FONT);
		Core.matrix.Pop();

	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}
#endif /* NPC_H_ */
