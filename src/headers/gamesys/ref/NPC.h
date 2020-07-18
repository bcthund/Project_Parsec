/*
 * NPC.h
 *
 *  Created on: Nov 1, 2010
 *      Author: bcthund
 */

#ifndef NPC_H_
#define NPC_H_

class _NPC {
	private:
		float init_sx, init_sz;

	protected:

	public:
		WorldMap &map;
		_NPC(WorldMap &m): map(m) {

			init_sx = 0;
			init_sz = 0;

//			float fMax=0,
//						fMin=1024;
//
//			for(int i=0; i<10000000; ++i) {
//				init_sx			= (rand() % (1023-64))+32;
//				init_sz			= (rand() % (1023-64))+32;
//				fMin = std::min(fMin, init_sx);
//				fMax = std::max(fMax, init_sx);
//			}
//
//			cout << "=====================================================================" << endl;
//			cout << "=====================================================================" << endl;
//			cout << "=====================================================================" << endl;
//			cout << "=====================================================================" << endl;
//			cout << "=====================================================================" << endl;
//			cout << "=====================================================================" << endl;
//			cout << "=====================================================================" << endl;
//			cout << "Min: " << fMin << "\t\tMax: " << fMax << endl;
//			cout << "=====================================================================" << endl;
//			cout << "=====================================================================" << endl;
//			cout << "=====================================================================" << endl;
//			cout << "=====================================================================" << endl;
//			cout << "=====================================================================" << endl;
//			cout << "=====================================================================" << endl;
//			cout << "=====================================================================" << endl;

			bLoad = false;
		}
		/*
		 * This contains up to 256 character sheets per map
		 *
		 * Use this to load available mobs to memory, then when
		 * 	spawning occurs randomly create a group from the
		 * 	available sheets of up to 12 enemies. The enemies
		 * 	and their group is stored into another container
		 * 	as a copy in the "runVoid" class to preserve
		 * 	the original data.
		 *
		 */
		NPCSheet data[9][9];

		bool bLoad;
		bool init();
		bool load();
		//bool calc(MapData mapData[][9]);
		bool calc();
		void draw(Atmosphere &a);
		void draw(Atmosphere &a, CharSheet &sheet, bool bCard);
		void draw(Atmosphere &a, CharSheet &sheet, CharSheet &lookAt, bool bCard);
		void update();
		void reload();
		void reload(int x, int z);
		float height(float iX, float iZ, int gX, int gZ);
		int inline ApplyStatMod(int i);
		void LoadNpc(int x, int z, int id);
};

bool _NPC::init() {
	init_sx			= (rand() % (1023-64))+32;
	init_sz			= (rand() % (1023-64))+32;
	return true;
}

int inline _NPC::ApplyStatMod(int i) {
	return 10*log(i)-26;
}

/*
 *
 */
void _NPC::LoadNpc(int x, int z, int id) {

	float	init_x					= 0,
				init_y					= 0,
				init_z					= 0,
				init_w					= 0,
				init_h					= 0,
				init_blend				= 0,
				init_eyeHeight			= 0,
				mod_weight				= 0;

	std::string init_image			= "",
							init_name			= "",
							init_orientation	= "",
							init_state			= "",
							init_race			= "",
							init_class			= "";

	unsigned int	armor_head[5],
								armor_torso[5],
								armor_L_arm[5],
								armor_R_arm[5],
								armor_L_hand[5],
								armor_R_hand[5],
								armor_L_leg[5],
								armor_R_leg[5],
								armor_legs[5],
								armor_neck[5],
								armor_L_foot[5],
								armor_R_foot[5],
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
								skill_dodge		= 20,
								skill_deflect	= 10,
								skill_block		= 10;

	/*
	 * Hard Coded NPC data
	 *
	 * This data is specific to this
	 * battle system and eventually needs
	 * to be made external to this system
	 */

	/* Starting position of npc group
	 *
	 * NPCs are then spawned in an area
	 * 	around this location.
	 */

	if (id==ENEMY1) {
		//init_x			= 240;
		//init_y		= 0;		//Auto Calculated
		//init_z			= 250;
		init_x			= rand() % 32;
		init_z			= rand() % 32;
		init_w			= 8;
		init_h			= 26.82+12;
		init_blend		= 0;		//Offset into/out of ground
		init_eyeHeight  = 26.82-2;	// (2/16) meters ==> 4.92 inches
		mod_weight		= 1;		//Weight Modifier

		init_image		= "man_arngrad.png";		//Sprite image
		init_name		= "Man Arngrad";
		init_orientation = "Aggravated";
		init_state		= "Engaging";
		init_race		= "Human";
		init_class		= "Mercenary";

//		armor_head[0]		= GAME::ARMOR.BASE.SKIN;
//		armor_torso[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_arm[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_arm[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_hand[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_hand[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_leg[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_leg[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_foot[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_foot[0]	= GAME::ARMOR.BASE.SKIN;
		armor_head[0]		= -1;
		armor_torso[0]	= -1;
		armor_L_arm[0]	= -1;
		armor_R_arm[0]	= -1;
		armor_L_hand[0]	= -1;
		armor_R_hand[0]	= -1;
		armor_L_leg[0]	= -1;
		armor_R_leg[0]	= -1;
		armor_legs[0]		= -1;
		armor_neck[0]		= -1;
		armor_L_foot[0]	= -1;
		armor_R_foot[0]	= -1;

		armor_head[1]		= -1;
		armor_torso[1]	= 15;
		armor_L_arm[1]	= 16;
		armor_R_arm[1]	= 17;
		armor_L_hand[1]	= -1;
		armor_R_hand[1]	= -1;
		armor_L_leg[1]	= -1;
		armor_R_leg[1]	= -1;
		armor_legs[1]		= -1;
		armor_neck[1]		= -1;
		armor_L_foot[1]	= -1;
		armor_R_foot[1]	= -1;

		armor_head[2]		= -1;
		armor_torso[2]	= -1;
		armor_L_arm[2]	= -1;
		armor_R_arm[2]	= -1;
		armor_L_hand[2]	= -1;
		armor_R_hand[2]	= -1;
		armor_L_leg[2]	= -1;
		armor_R_leg[2]	= -1;
		armor_legs[2]		= 65;
		armor_neck[2]		= -1;
		armor_L_foot[2]	= 19;
		armor_R_foot[2]	= 20;

		armor_head[3]		= -1;
		armor_torso[3]	= 46;
		armor_L_arm[3]	= -1;
		armor_R_arm[3]	= -1;
		armor_L_hand[3]	= -1;
		armor_R_hand[3]	= -1;
		armor_L_leg[3]	= -1;
		armor_R_leg[3]	= -1;
		armor_legs[3]		= -1;
		armor_neck[3]		= -1;
		armor_L_foot[3]	= -1;
		armor_R_foot[3]	= -1;

		armor_head[4]		= 52;
		armor_torso[4]	= -1;
		armor_L_arm[4]	= -1;
		armor_R_arm[4]	= -1;
		armor_L_hand[4]	= -1;
		armor_R_hand[4]	= -1;
		armor_L_leg[4]	= -1;
		armor_R_leg[4]	= -1;
		armor_legs[4]		= -1;
		armor_neck[4]		= -1;
		armor_L_foot[4]	= -1;
		armor_R_foot[4]	= -1;
		weapon					= 66;

		str_aura		= 15;
		str_mind		= 15;
		fin_aura		= 25;
		fin_speed		= 25;
		mob_endurance	= 15;
		mob_speed		= 15;
		fat_endurance	= 5;
		fat_mind		= 5;
		vic_aura		= 10;
		vic_endurance	= 10;
		defense_mode	= GAME::MENU.DEFENSE.DEFLECT;
		move_mode		= GAME::MENU.MOVE.WALK;
		attack_num		= 1;
		face			= 13;
		skill_deflect	= 7;
		skill_dodge		= 5;
		skill_block		= 5;
	}

	if (id==ENEMY2) {
		//init_x			= 250;
		//init_y			= 0;		//Auto Calculated
		//init_z			= 250;
		init_x			= rand() % 32;
		init_z			= rand() % 32;
		init_w			= 20;
		init_h			= 28;
		init_blend		= 0;		//Offset into/out of ground
		init_eyeHeight  = 28-2;
		mod_weight		= 1;		//Weight Modifier

		init_image		= "girl_longostomous.png";		//Sprite image
		init_name		= "Girl Long Ostomous";
		init_orientation = "Aggravated";
		init_state		= "Engaging";
		init_race		= "Human";
		init_class		= "Mercenary";

//		armor_head[0]		= GAME::ARMOR.BASE.SKIN;
//		armor_torso[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_arm[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_arm[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_hand[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_hand[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_leg[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_leg[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_foot[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_foot[0]	= GAME::ARMOR.BASE.SKIN;
		armor_head[0]		= -1;
		armor_torso[0]	= -1;
		armor_L_arm[0]	= -1;
		armor_R_arm[0]	= -1;
		armor_L_hand[0]	= -1;
		armor_R_hand[0]	= -1;
		armor_L_leg[0]	= -1;
		armor_R_leg[0]	= -1;
		armor_legs[0]		= -1;
		armor_neck[0]		= -1;
		armor_L_foot[0]	= -1;
		armor_R_foot[0]	= -1;

		armor_head[1]		= -1;
		armor_torso[1]	= -1;
		armor_L_arm[1]	= -1;
		armor_R_arm[1]	= -1;
		armor_L_hand[1]	= -1;
		armor_R_hand[1]	= -1;
		armor_L_leg[1]	= -1;
		armor_R_leg[1]	= -1;
		armor_legs[1]		= -1;
		armor_neck[1]		= -1;
		armor_L_foot[1]	= -1;
		armor_R_foot[1]	= -1;

		armor_head[2]		= -1;
		armor_torso[2]	= 33;
		armor_L_arm[2]	= -1;
		armor_R_arm[2]	= -1;
		armor_L_hand[2]	= -1;
		armor_R_hand[2]	= -1;
		armor_L_leg[2]	= -1;
		armor_R_leg[2]	= -1;
		armor_legs[2]		= 65;
		armor_neck[2]		= -1;
		armor_L_foot[2]	= -1;
		armor_R_foot[2]	= -1;

		armor_head[3]		= -1;
		armor_torso[3]	= -1;
		armor_L_arm[3]	= -1;
		armor_R_arm[3]	= -1;
		armor_L_hand[3]	= -1;
		armor_R_hand[3]	= -1;
		armor_L_leg[3]	= -1;
		armor_R_leg[3]	= -1;
		armor_legs[3]		= -1;
		armor_neck[3]		= -1;
		armor_L_foot[3]	= -1;
		armor_R_foot[3]	= -1;

		armor_head[4]		= 52;
		armor_torso[4]	= -1;
		armor_L_arm[4]	= -1;
		armor_R_arm[4]	= -1;
		armor_L_hand[4]	= -1;
		armor_R_hand[4]	= -1;
		armor_L_leg[4]	= -1;
		armor_R_leg[4]	= -1;
		armor_legs[4]		= -1;
		armor_neck[4]		= -1;
		armor_L_foot[4]	= -1;
		armor_R_foot[4]	= -1;
		weapon					= 62;		//Equipped Weapon

		str_aura		= 10;
		str_mind		= 10;
		fin_aura		= 20;
		fin_speed		= 20;
		mob_endurance	= 20;
		mob_speed		= 20;
		fat_endurance	= 10;
		fat_mind		= 10;
		vic_aura		= 5;
		vic_endurance	= 5;
		defense_mode	= GAME::MENU.DEFENSE.BLOCK;
		move_mode		= GAME::MENU.MOVE.WALK;
		attack_num		= 1;
		face			= 14;
		skill_deflect	= 7;
		skill_dodge		= 5;
		skill_block		= 12;
	}

	if (id==ENEMY3) {
		//init_x			= 240;
		//init_y			= 0;		//Auto Calculated
		//init_z			= 240;
		init_x			= rand() % 32;
		init_z			= rand() % 32;
		init_w			= 16;
		init_h			= 30;
		init_blend		= 0;		//Offset into/out of ground
		init_eyeHeight  = 30-2;
		mod_weight		= 1;		//Weight Modifier

		init_image		= "man_hammer.png";		//Sprite image
		init_name		= "Man Hammer";
		init_orientation = "Neutral";
		init_state		= "Engaging";
		init_race		= "Human";
		init_class		= "Barbarian";

//		armor_head[0]		= GAME::ARMOR.BASE.SKIN;
//		armor_torso[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_arm[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_arm[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_hand[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_hand[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_leg[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_leg[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_foot[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_foot[0]	= GAME::ARMOR.BASE.SKIN;
		armor_head[0]		= -1;
		armor_torso[0]	= -1;
		armor_L_arm[0]	= -1;
		armor_R_arm[0]	= -1;
		armor_L_hand[0]	= -1;
		armor_R_hand[0]	= -1;
		armor_L_leg[0]	= -1;
		armor_R_leg[0]	= -1;
		armor_legs[0]		= -1;
		armor_neck[0]		= -1;
		armor_L_foot[0]	= -1;
		armor_R_foot[0]	= -1;

		armor_head[1]		= -1;
		armor_torso[1]	= -1;
		armor_L_arm[1]	= -1;
		armor_R_arm[1]	= -1;
		armor_L_hand[1]	= -1;
		armor_R_hand[1]	= -1;
		armor_L_leg[1]	= -1;
		armor_R_leg[1]	= -1;
		armor_legs[1]		= -1;
		armor_neck[1]		= -1;
		armor_L_foot[1]	= -1;
		armor_R_foot[1]	= -1;

		armor_head[2]		= -1;
		armor_torso[2]	= -1;
		armor_L_arm[2]	= -1;
		armor_R_arm[2]	= -1;
		armor_L_hand[2]	= -1;
		armor_R_hand[2]	= -1;
		armor_L_leg[2]	= -1;
		armor_R_leg[2]	= -1;
		armor_legs[2]		= 65;
		armor_neck[2]		= -1;
		armor_L_foot[2]	= 19;
		armor_R_foot[2]	= 20;

		armor_head[3]		= -1;
		armor_torso[3]	= 43;
		armor_L_arm[3]	= -1;
		armor_R_arm[3]	= -1;
		armor_L_hand[3]	= 37;
		armor_R_hand[3]	= 38;
		armor_L_leg[3]	= -1;
		armor_R_leg[3]	= -1;
		armor_legs[3]		= -1;
		armor_neck[3]		= -1;
		armor_L_foot[3]	= -1;
		armor_R_foot[3]	= -1;

		armor_head[4]		= 52;
		armor_torso[4]	= -1;
		armor_L_arm[4]	= -1;
		armor_R_arm[4]	= -1;
		armor_L_hand[4]	= -1;
		armor_R_hand[4]	= -1;
		armor_L_leg[4]	= -1;
		armor_R_leg[4]	= -1;
		armor_legs[4]		= -1;
		armor_neck[4]		= -1;
		armor_L_foot[4]	= -1;
		armor_R_foot[4]	= -1;
		weapon					= 61;

		str_aura		= 30;
		str_mind		= 30;
		fin_aura		= 10;
		fin_speed		= 10;
		mob_endurance	= 25;
		mob_speed		= 25;
		fat_endurance	= 1;
		fat_mind		= 1;
		vic_aura		= 15;
		vic_endurance	= 15;
		defense_mode	= GAME::MENU.DEFENSE.BLOCK;
		move_mode		= GAME::MENU.MOVE.WALK;
		attack_num		= 1;
		face			= 19;
		skill_deflect	= 5;
		skill_dodge		= 5;
		skill_block		= 15;
	}

	if (id==ENEMY4) {
		//init_x			= 260;
		//init_y		= 0;		//Auto Calculated
		//init_z			= 260;
		init_x			= rand() % 32;
		init_z			= rand() % 32;
		init_w			= 13;
		init_h			= 33;
		init_blend		= 0;		//Offset into/out of ground
		init_eyeHeight  = 33-2;
		mod_weight		= 1;		//Weight Modifier

		init_image		 = "axeman.png";		//Sprite image
		init_name		 = "Axe Man";
		init_orientation = "Aggravated";
		init_state		 = "Engaging";
		init_race		 = "Throgg";
		init_class		 = "Mercenary";

//		armor_head[0]		= GAME::ARMOR.BASE.SKIN;
//		armor_torso[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_arm[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_arm[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_hand[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_hand[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_leg[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_leg[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_foot[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_foot[0]	= GAME::ARMOR.BASE.SKIN;
		armor_head[0]		= -1;
		armor_torso[0]	= -1;
		armor_L_arm[0]	= -1;
		armor_R_arm[0]	= -1;
		armor_L_hand[0]	= -1;
		armor_R_hand[0]	= -1;
		armor_L_leg[0]	= -1;
		armor_R_leg[0]	= -1;
		armor_legs[0]		= -1;
		armor_neck[0]		= -1;
		armor_L_foot[0]	= -1;
		armor_R_foot[0]	= -1;

		armor_head[1]		= -1;
		armor_torso[1]	= 15;
		armor_L_arm[1]	= -1;
		armor_R_arm[1]	= -1;
		armor_L_hand[1]	= 10;
		armor_R_hand[1]	= 11;
		armor_L_leg[1]	= -1;
		armor_R_leg[1]	= -1;
		armor_legs[1]		= 14;
		armor_neck[1]		= -1;
		armor_L_foot[1]	= 58;
		armor_R_foot[1]	= 59;

		armor_head[2]		= 21;
		armor_torso[2]	= 32;
		armor_L_arm[2]	= -1;
		armor_R_arm[2]	= -1;
		armor_L_hand[2]	= -1;
		armor_R_hand[2]	= -1;
		armor_L_leg[2]	= -1;
		armor_R_leg[2]	= -1;
		armor_legs[2]		= -1;
		armor_neck[2]		= -1;
		armor_L_foot[2]	= -1;
		armor_R_foot[2]	= -1;

		armor_head[3]		= 34;
		armor_torso[3]	= 43;
		armor_L_arm[3]	= -1;
		armor_R_arm[3]	= -1;
		armor_L_hand[3]	= -1;
		armor_R_hand[3]	= -1;
		armor_L_leg[3]	= -1;
		armor_R_leg[3]	= -1;
		armor_legs[3]		= 41;
		armor_neck[3]		= -1;
		armor_L_foot[3]	= -1;
		armor_R_foot[3]	= -1;

		armor_head[4]		= -1;
		armor_torso[4]	= 49;
		armor_L_arm[4]	= -1;
		armor_R_arm[4]	= -1;
		armor_L_hand[4]	= 47;
		armor_R_hand[4]	= 48;
		armor_L_leg[4]	= -1;
		armor_R_leg[4]	= -1;
		armor_legs[4]		= -1;
		armor_neck[4]		= -1;
		armor_L_foot[4]	= -1;
		armor_R_foot[4]	= -1;
		weapon					= 60;		//Equipped Weapon

		str_aura		= 15;
		str_mind		= 15;
		fin_aura		= 15;
		fin_speed		= 15;
		mob_endurance	= 10;
		mob_speed		= 10;
		fat_endurance	= 45;
		fat_mind		= 45;
		vic_aura		= 15;
		vic_endurance	= 15;
		defense_mode	= GAME::MENU.DEFENSE.DEFLECT;
		move_mode		= GAME::MENU.MOVE.WALK;
		attack_num		= 1;
		face			= 25;
		skill_deflect	= 10;
		skill_dodge		= 1;
		skill_block		= 5;
	}

	/*
	if (id==4) {
		init_x			= 260;
		//init_y		= 0;		//Auto Calculated
		init_z			= 260;
		//init_x			= rand() % 1023;
		//init_z			= rand() % 1023;
		init_w			= 120;
		init_h			= 292;
		init_blend		= 0;		//Offset into/out of ground
		init_eyeHeight  = 292-150;
		mod_weight		= 1;		//Weight Modifier

		init_image		= "crygate.png";		//Sprite image
		init_name		= "Crygate";

		armor_head[0]	= GAME::ARMOR.BASE.SKIN;
		armor_torso[0]	= GAME::ARMOR.BASE.SKIN;
		armor_L_arm[0]	= GAME::ARMOR.BASE.SKIN;
		armor_R_arm[0]	= GAME::ARMOR.BASE.SKIN;
		armor_L_hand[0]	= GAME::ARMOR.BASE.SKIN;
		armor_R_hand[0]	= GAME::ARMOR.BASE.SKIN;
		armor_L_leg[0]	= GAME::ARMOR.BASE.SKIN;
		armor_R_leg[0]	= GAME::ARMOR.BASE.SKIN;
		armor_L_foot[0]	= GAME::ARMOR.BASE.SKIN;
		armor_R_foot[0]	= GAME::ARMOR.BASE.SKIN;

		armor_head[1]	= -1;
		armor_torso[1]	= -1;
		armor_L_arm[1]	= -1;
		armor_R_arm[1]	= -1;
		armor_L_hand[1]	= -1;
		armor_R_hand[1]	= -1;
		armor_L_leg[1]	= -1;
		armor_R_leg[1]	= -1;
		armor_L_foot[1]	= -1;
		armor_R_foot[1]	= -1;

		armor_head[2]	= -1;
		armor_torso[2]	= -1;
		armor_L_arm[2]	= -1;
		armor_R_arm[2]	= -1;
		armor_L_hand[2]	= -1;
		armor_R_hand[2]	= -1;
		armor_L_leg[2]	= -1;
		armor_R_leg[2]	= -1;
		armor_L_foot[2]	= -1;
		armor_R_foot[2]	= -1;

		armor_head[3]	= -1;
		armor_torso[3]	= -1;
		armor_L_arm[3]	= -1;
		armor_R_arm[3]	= -1;
		armor_L_hand[3]	= -1;
		armor_R_hand[3]	= -1;
		armor_L_leg[3]	= -1;
		armor_R_leg[3]	= -1;
		armor_L_foot[3]	= -1;
		armor_R_foot[3]	= -1;

		armor_head[4]	= GAME::ARMOR.BASE.CRYGATE;
		armor_torso[4]	= GAME::ARMOR.BASE.CRYGATE;
		armor_L_arm[4]	= GAME::ARMOR.BASE.CRYGATE;
		armor_R_arm[4]	= GAME::ARMOR.BASE.CRYGATE;
		armor_L_hand[4]	= GAME::ARMOR.BASE.CRYGATE;
		armor_R_hand[4]	= GAME::ARMOR.BASE.CRYGATE;
		armor_L_leg[4]	= GAME::ARMOR.BASE.CRYGATE;
		armor_R_leg[4]	= GAME::ARMOR.BASE.CRYGATE;
		armor_L_foot[4]	= GAME::ARMOR.BASE.CRYGATE;
		armor_R_foot[4]	= GAME::ARMOR.BASE.CRYGATE;
		weapon			= GAME::WEAPON.BASE.CRYGATE_TENTACLE;		//Equipped Weapon

		str_aura		= 150;
		str_mind		= 150;
		fin_aura		= 40;
		fin_speed		= 40;
		mob_endurance	= 5;
		mob_speed		= 5;
		fat_endurance	= 250;
		fat_mind		= 250;
		vic_aura		= 100;
		vic_endurance	= 100;
		defense_mode	= GAME::MENU.DEFENSE.NONE;
		move_mode		= GAME::MENU.MOVE.WALK;
		attack_num		= 2;
		face			= 37;
		skill_deflect	= 0;
		skill_dodge		= 0;
		skill_block		= 0;
	}
	*/

	if (id==4) {
		//init_x			= 240;
		//init_y			= 0;		//Auto Calculated
		//init_z			= 250;
		init_x			= rand() % 32;
		init_z			= rand() % 32;
		init_w			= 20;
		init_h			= 32;
		init_blend		= 0;		//Offset into/out of ground
		init_eyeHeight  = init_h-4;
		mod_weight		= 1;		//Weight Modifier

		init_image		= "manchop.png";		//Sprite image
		init_name		= "Man Chop";
		init_orientation = "Berserk";
		init_state		= "Engaging";
		init_race		= "Human";
		init_class		= "Paladin";

//		armor_head[0]		= GAME::ARMOR.BASE.SKIN;
//		armor_torso[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_arm[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_arm[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_hand[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_hand[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_leg[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_leg[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_foot[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_foot[0]	= GAME::ARMOR.BASE.SKIN;
		armor_head[0]		= -1;
		armor_torso[0]	= -1;
		armor_L_arm[0]	= -1;
		armor_R_arm[0]	= -1;
		armor_L_hand[0]	= -1;
		armor_R_hand[0]	= -1;
		armor_L_leg[0]	= -1;
		armor_R_leg[0]	= -1;
		armor_legs[0]		= -1;
		armor_neck[0]		= -1;
		armor_L_foot[0]	= -1;
		armor_R_foot[0]	= -1;

		armor_head[1]		= -1;
		armor_torso[1]	= -1;
		armor_L_arm[1]	= -1;
		armor_R_arm[1]	= -1;
		armor_L_hand[1]	= -1;
		armor_R_hand[1]	= -1;
		armor_L_leg[1]	= -1;
		armor_R_leg[1]	= -1;
		armor_legs[1]		= -1;
		armor_neck[1]		= -1;
		armor_L_foot[1]	= -1;
		armor_R_foot[1]	= -1;

		armor_head[2]		= -1;
		armor_torso[2]	= -1;
		armor_L_arm[2]	= -1;
		armor_R_arm[2]	= -1;
		armor_L_hand[2]	= -1;
		armor_R_hand[2]	= -1;
		armor_L_leg[2]	= -1;
		armor_R_leg[2]	= -1;
		armor_legs[2]		= -1;
		armor_neck[2]		= -1;
		armor_L_foot[2]	= 19;
		armor_R_foot[2]	= 20;

		armor_head[3]		= -1;
		armor_torso[3]	= 43;
		armor_L_arm[3]	= -1;
		armor_R_arm[3]	= -1;
		armor_L_hand[3]	= -1;
		armor_R_hand[3]	= -1;
		armor_L_leg[3]	= -1;
		armor_R_leg[3]	= -1;
		armor_legs[3]		= -1;
		armor_neck[3]		= -1;
		armor_L_foot[3]	= -1;
		armor_R_foot[3]	= -1;

		armor_head[4]		= 52;
		armor_torso[4]	= -1;
		armor_L_arm[4]	= -1;
		armor_R_arm[4]	= -1;
		armor_L_hand[4]	= -1;
		armor_R_hand[4]	= -1;
		armor_L_leg[4]	= -1;
		armor_R_leg[4]	= -1;
		armor_legs[4]		= -1;
		armor_neck[4]		= -1;
		armor_L_foot[4]	= -1;
		armor_R_foot[4]	= -1;
		weapon					= 62;

		str_aura		= 10;
		str_mind		= 10;
		fin_aura		= 10;
		fin_speed		= 10;
		mob_endurance	= 30;
		mob_speed		= 30;
		fat_endurance	= 25;
		fat_mind		= 25;
		vic_aura		= 20;
		vic_endurance	= 20;
		defense_mode	= GAME::MENU.DEFENSE.DODGE;
		move_mode		= GAME::MENU.MOVE.WALK;
		attack_num		= 1;
		face			= 26;
		skill_deflect	= 5;
		skill_dodge		= 5;
		skill_block		= 5;
	}

	if (id==5) {
		//init_x			= 240;
		//init_y			= 0;		//Auto Calculated
		//init_z			= 250;
		init_x			= rand() % 32;
		init_z			= rand() % 32;
		init_w			= 14;
		init_h			= 32;
		init_blend		= 0;		//Offset into/out of ground
		init_eyeHeight  = init_h-4;
		mod_weight		= 1;		//Weight Modifier

		init_image		= "civhynchen.png";		//Sprite image
		init_name		= "Civhynchen";
		init_orientation = "Neutral";
		init_state		= "Engaging";
		init_race		= "Human";
		init_class		= "Warlock";

//		armor_head[0]		= GAME::ARMOR.BASE.SKIN;
//		armor_torso[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_arm[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_arm[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_hand[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_hand[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_leg[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_leg[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_foot[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_foot[0]	= GAME::ARMOR.BASE.SKIN;
		armor_head[0]		= -1;
		armor_torso[0]	= -1;
		armor_L_arm[0]	= -1;
		armor_R_arm[0]	= -1;
		armor_L_hand[0]	= -1;
		armor_R_hand[0]	= -1;
		armor_L_leg[0]	= -1;
		armor_R_leg[0]	= -1;
		armor_legs[0]		= -1;
		armor_neck[0]		= -1;
		armor_L_foot[0]	= -1;
		armor_R_foot[0]	= -1;

		armor_head[1]		= -1;
		armor_torso[1]	= -1;
		armor_L_arm[1]	= -1;
		armor_R_arm[1]	= -1;
		armor_L_hand[1]	= -1;
		armor_R_hand[1]	= -1;
		armor_L_leg[1]	= -1;
		armor_R_leg[1]	= -1;
		armor_legs[1]		= -1;
		armor_neck[1]		= 8;
		armor_L_foot[1]	= -1;
		armor_R_foot[1]	= -1;

		armor_head[2]		= -1;
		armor_torso[2]	= 33;
		armor_L_arm[2]	= -1;
		armor_R_arm[2]	= -1;
		armor_L_hand[2]	= 24;
		armor_R_hand[2]	= 25;
		armor_L_leg[2]	= -1;
		armor_R_leg[2]	= -1;
		armor_legs[2]		= -1;
		armor_neck[2]		= -1;
		armor_L_foot[2]	= 19;
		armor_R_foot[2]	= 20;

		armor_head[3]		= -1;
		armor_torso[3]	= -1;
		armor_L_arm[3]	= -1;
		armor_R_arm[3]	= -1;
		armor_L_hand[3]	= -1;
		armor_R_hand[3]	= -1;
		armor_L_leg[3]	= -1;
		armor_R_leg[3]	= -1;
		armor_legs[3]		= -1;
		armor_neck[3]		= -1;
		armor_L_foot[3]	= -1;
		armor_R_foot[3]	= -1;

		armor_head[4]		= -1;
		armor_torso[4]	= -1;
		armor_L_arm[4]	= -1;
		armor_R_arm[4]	= -1;
		armor_L_hand[4]	= -1;
		armor_R_hand[4]	= -1;
		armor_L_leg[4]	= -1;
		armor_R_leg[4]	= -1;
		armor_legs[4]		= -1;
		armor_neck[4]		= -1;
		armor_L_foot[4]	= -1;
		armor_R_foot[4]	= -1;
		weapon					= 61;

		str_aura		= 10;
		str_mind		= 10;
		fin_aura		= 50;
		fin_speed		= 50;
		mob_endurance	= 15;
		mob_speed		= 15;
		fat_endurance	= 35;
		fat_mind		= 35;
		vic_aura		= 5;
		vic_endurance	= 5;
		defense_mode	= GAME::MENU.DEFENSE.DODGE;
		move_mode		= GAME::MENU.MOVE.WALK;
		attack_num		= 1;
		face			= 27;
		skill_deflect	= 5;
		skill_dodge		= 5;
		skill_block		= 5;
	}

	if (id==6) {
		//init_x			= 240;
		//init_y			= 0;		//Auto Calculated
		//init_z			= 250;
		init_x			= rand() % 32;
		init_z			= rand() % 32;
		init_w			= 12;
		init_h			= 32;
		init_blend		= 0;		//Offset into/out of ground
		init_eyeHeight  = init_h-4;
		mod_weight		= 1;		//Weight Modifier

		init_image		= "proudnaked.png";		//Sprite image
		init_name		= "Proud Naked";
		init_orientation = "Neutral";
		init_state		= "Engaging";
		init_race		= "Human";
		init_class		= "Thug";

//		armor_head[0]		= GAME::ARMOR.BASE.SKIN;
//		armor_torso[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_arm[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_arm[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_hand[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_hand[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_leg[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_leg[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_L_foot[0]	= GAME::ARMOR.BASE.SKIN;
//		armor_R_foot[0]	= GAME::ARMOR.BASE.SKIN;
		armor_head[0]		= -1;
		armor_torso[0]	= -1;
		armor_L_arm[0]	= -1;
		armor_R_arm[0]	= -1;
		armor_L_hand[0]	= -1;
		armor_R_hand[0]	= -1;
		armor_L_leg[0]	= -1;
		armor_R_leg[0]	= -1;
		armor_legs[0]		= -1;
		armor_neck[0]		= -1;
		armor_L_foot[0]	= -1;
		armor_R_foot[0]	= -1;

		armor_head[1]		= -1;
		armor_torso[1]	= -1;
		armor_L_arm[1]	= -1;
		armor_R_arm[1]	= -1;
		armor_L_hand[1]	= -1;
		armor_R_hand[1]	= -1;
		armor_L_leg[1]	= -1;
		armor_R_leg[1]	= -1;
		armor_legs[1]		= -1;
		armor_neck[1]		= -1;
		armor_L_foot[1]	= -1;
		armor_R_foot[1]	= -1;

		armor_head[2]		= -1;
		armor_torso[2]	= -1;
		armor_L_arm[2]	= -1;
		armor_R_arm[2]	= -1;
		armor_L_hand[2]	= -1;
		armor_R_hand[2]	= -1;
		armor_L_leg[2]	= -1;
		armor_R_leg[2]	= -1;
		armor_legs[2]		= -1;
		armor_neck[2]		= -1;
		armor_L_foot[2]	= -1;
		armor_R_foot[2]	= -1;

		armor_head[3]		= -1;
		armor_torso[3]	= -1;
		armor_L_arm[3]	= -1;
		armor_R_arm[3]	= -1;
		armor_L_hand[3]	= -1;
		armor_R_hand[3]	= -1;
		armor_L_leg[3]	= -1;
		armor_R_leg[3]	= -1;
		armor_legs[3]		= -1;
		armor_neck[3]		= -1;
		armor_L_foot[3]	= -1;
		armor_R_foot[3]	= -1;

		armor_head[4]		= -1;
		armor_torso[4]	= -1;
		armor_L_arm[4]	= -1;
		armor_R_arm[4]	= -1;
		armor_L_hand[4]	= -1;
		armor_R_hand[4]	= -1;
		armor_L_leg[4]	= -1;
		armor_R_leg[4]	= -1;
		armor_legs[4]		= -1;
		armor_neck[4]		= -1;
		armor_L_foot[4]	= -1;
		armor_R_foot[4]	= -1;
		weapon			= 61;		//Equipped Weapon

		str_aura		= 40;
		str_mind		= 40;
		fin_aura		= 50;
		fin_speed		= 50;
		mob_endurance	= 15;
		mob_speed		= 15;
		fat_endurance	= 10;
		fat_mind		= 10;
		vic_aura		= 25;
		vic_endurance	= 25;
		defense_mode	= GAME::MENU.DEFENSE.DODGE;
		move_mode		= GAME::MENU.MOVE.WALK;
		attack_num		= 1;
		face			= 28;
		skill_deflect	= 5;
		skill_dodge		= 5;
		skill_block		= 5;
	}

	data[x][z].idcount++;

	//TEST NPC
	data[x][z].sheet[id].init.id									= id;
	//data[x][z].sheet[id].init.x										= -((init_sx + init_x) + (x * 1024));
	data[x][z].sheet[id].init.y										= 0;
	//data[x][z].sheet[id].init.z										= -((init_sz + init_z) + (z * 1024));

	// TODO: This is temporary to force enemy spawn location
	data[x][z].sheet[id].init.x										= -((300 + init_x) + (x * 1024));
	data[x][z].sheet[id].init.z										= -((200 + init_z) + (z * 1024));

	//cout << "\t\t(" << data[x][z].sheet[id].init.x << "," << data[x][z].sheet[id].init.z << ")" << endl;

	//data[x][z].sheet[id].init[0].r								= 0;
	data[x][z].sheet[id].init.w										= init_w;
	data[x][z].sheet[id].init.h										= init_h;
	data[x][z].sheet[id].init.blend									= init_blend;
	data[x][z].sheet[id].init.image									= init_image;
	data[x][z].sheet[id].init.name									= init_name;

	data[x][z].sheet[id].init.sRole									= init_orientation;
	data[x][z].sheet[id].init.sState								= init_state;
	data[x][z].sheet[id].init.sRace									= init_race;
	data[x][z].sheet[id].init.sProfession							= init_class;

	data[x][z].sheet[id].init.isDead								= false;

	//if (data[x][z].sheet[id].init.isDead) data[x][z].sheet[id].init.isDead	= true;
	//else data[x][z].sheet[id].init.isDead = false;

	data[x][z].sheet[id].transform.pos[0]							= data[x][z].sheet[id].init.x;
	data[x][z].sheet[id].transform.pos[1]							= data[x][z].sheet[id].init.y;
	data[x][z].sheet[id].transform.pos[2]							= data[x][z].sheet[id].init.z;

	data[x][z].sheet[id].transform.eyeHeight						= init_eyeHeight;
	data[x][z].sheet[id].transform.currentHeight					= init_eyeHeight;

	//data[x][z].sheet[id].items.armor.equipped						= armor;
	//data[x][z].sheet[id].items.armor.head							= armor_head;
	//data[x][z].sheet[id].items.armor.torso						= armor_torso;
	//data[x][z].sheet[id].items.armor.left_arm[0]					= armor_L_arm;
	//data[x][z].sheet[id].items.armor.left_arm[1]					= armor_L_hand;
	//data[x][z].sheet[id].items.armor.right_arm[0]					= armor_R_arm;
	//data[x][z].sheet[id].items.armor.right_arm[1]					= armor_R_hand;
	//data[x][z].sheet[id].items.armor.left_leg[0]					= armor_L_leg;
	//data[x][z].sheet[id].items.armor.left_leg[1]					= armor_L_foot;
	//data[x][z].sheet[id].items.armor.right_leg[0]					= armor_R_leg;
	//data[x][z].sheet[id].items.armor.right_leg[1]					= armor_R_foot;

	// TODO: Natural Armor
	// TO BE IMPLEMENTED

	// TODO: Fix these armor references, they are incorrect. See the
	//				player for proper use of these. Armor MUST be in inventory
	//				to be equipped.
	// Vestments
	data[x][z].sheet[id].inventory.equipped.base.iHead						= armor_head[1];
	data[x][z].sheet[id].inventory.equipped.base.iTorso						= armor_torso[1];
	data[x][z].sheet[id].inventory.equipped.base.iLeft_Arm				= armor_L_arm[1];
	data[x][z].sheet[id].inventory.equipped.base.iLeft_Hand				= armor_L_hand[1];
	data[x][z].sheet[id].inventory.equipped.base.iRight_Arm				= armor_R_arm[1];
	data[x][z].sheet[id].inventory.equipped.base.iRight_Hand			= armor_R_hand[1];
	data[x][z].sheet[id].inventory.equipped.base.iLeft_Leg				= armor_L_leg[1];
	data[x][z].sheet[id].inventory.equipped.base.iLeft_Foot				= armor_L_foot[1];
	data[x][z].sheet[id].inventory.equipped.base.iRight_Leg				= armor_R_leg[1];
	data[x][z].sheet[id].inventory.equipped.base.iRight_Foot			= armor_R_foot[1];
	data[x][z].sheet[id].inventory.equipped.base.iLegs						= armor_legs[1];
	data[x][z].sheet[id].inventory.equipped.base.iNeck						= armor_neck[1];


	// Quilted/Leather
	data[x][z].sheet[id].inventory.equipped.quilted.iHead					= armor_head[2];
	data[x][z].sheet[id].inventory.equipped.quilted.iTorso				= armor_torso[2];
	data[x][z].sheet[id].inventory.equipped.quilted.iLeft_Arm			= armor_L_arm[2];
	data[x][z].sheet[id].inventory.equipped.quilted.iLeft_Hand		= armor_L_hand[2];
	data[x][z].sheet[id].inventory.equipped.quilted.iRight_Arm		= armor_R_arm[2];
	data[x][z].sheet[id].inventory.equipped.quilted.iRight_Hand		= armor_R_hand[2];
	data[x][z].sheet[id].inventory.equipped.quilted.iLeft_Leg			= armor_L_leg[2];
	data[x][z].sheet[id].inventory.equipped.quilted.iLeft_Foot		= armor_L_foot[2];
	data[x][z].sheet[id].inventory.equipped.quilted.iRight_Leg		= armor_R_leg[2];
	data[x][z].sheet[id].inventory.equipped.quilted.iRight_Foot		= armor_R_foot[2];
	data[x][z].sheet[id].inventory.equipped.quilted.iLegs						= armor_legs[2];
	data[x][z].sheet[id].inventory.equipped.quilted.iNeck						= armor_neck[2];

	// Maille
	data[x][z].sheet[id].inventory.equipped.maille.iHead					= armor_head[3];
	data[x][z].sheet[id].inventory.equipped.maille.iTorso					= armor_torso[3];
	data[x][z].sheet[id].inventory.equipped.maille.iLeft_Arm			= armor_L_arm[3];
	data[x][z].sheet[id].inventory.equipped.maille.iLeft_Hand			= armor_L_hand[3];
	data[x][z].sheet[id].inventory.equipped.maille.iRight_Arm			= armor_R_arm[3];
	data[x][z].sheet[id].inventory.equipped.maille.iRight_Hand		= armor_R_hand[3];
	data[x][z].sheet[id].inventory.equipped.maille.iLeft_Leg			= armor_L_leg[3];
	data[x][z].sheet[id].inventory.equipped.maille.iLeft_Foot			= armor_L_foot[3];
	data[x][z].sheet[id].inventory.equipped.maille.iRight_Leg			= armor_R_leg[3];
	data[x][z].sheet[id].inventory.equipped.maille.iRight_Foot		= armor_R_foot[3];
	data[x][z].sheet[id].inventory.equipped.maille.iLegs						= armor_legs[3];
	data[x][z].sheet[id].inventory.equipped.maille.iNeck						= armor_neck[3];

	// Plate
	data[x][z].sheet[id].inventory.equipped.plate.iHead						= armor_head[4];
	data[x][z].sheet[id].inventory.equipped.plate.iTorso					= armor_torso[4];
	data[x][z].sheet[id].inventory.equipped.plate.iLeft_Arm				= armor_L_arm[4];
	data[x][z].sheet[id].inventory.equipped.plate.iLeft_Hand			= armor_L_hand[4];
	data[x][z].sheet[id].inventory.equipped.plate.iRight_Arm			= armor_R_arm[4];
	data[x][z].sheet[id].inventory.equipped.plate.iRight_Hand			= armor_R_hand[4];
	data[x][z].sheet[id].inventory.equipped.plate.iLeft_Leg				= armor_L_leg[4];
	data[x][z].sheet[id].inventory.equipped.plate.iLeft_Foot			= armor_L_foot[4];
	data[x][z].sheet[id].inventory.equipped.plate.iRight_Leg			= armor_R_leg[4];
	data[x][z].sheet[id].inventory.equipped.plate.iRight_Foot			= armor_R_foot[4];
	data[x][z].sheet[id].inventory.equipped.plate.iLegs						= armor_legs[4];
	data[x][z].sheet[id].inventory.equipped.plate.iNeck						= armor_neck[4];

	// Weapon
	data[x][z].sheet[id].inventory.equipped.equipment.iRight_Hand	= weapon;

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
	data[x][z].sheet[id].status.iCards[0][0]						= GAME::CARDS.ICON.HEALTHY;
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

	// Starting Inventory
	int t = 0;
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.GENERAL.AUSHAY;								data[x][z].sheet[id].inventory.list[t++].num = 1;		// 0
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.SNAKEMAILLE;						data[x][z].sheet[id].inventory.list[t++].num = 1;		// 1
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.WEAPON.BIGSWORD;							data[x][z].sheet[id].inventory.list[t++].num = 1;		// 2
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.WEAPON.REPARNS_SWORD;					data[x][z].sheet[id].inventory.list[t++].num = 1;		// 3
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.GENERAL.BINYA;								data[x][z].sheet[id].inventory.list[t++].num = 1;		// 4
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.BASEBALL_HAT;						data[x][z].sheet[id].inventory.list[t++].num = 1;		// 5
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.STEEL_GREAVE_LEFT;			data[x][z].sheet[id].inventory.list[t++].num = 1;		// 6
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.LEATHER_GLOVE_RIGHT;		data[x][z].sheet[id].inventory.list[t++].num = 1;		// 7

	// Vestments
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.FORESTERS_CAPE;					data[x][z].sheet[id].inventory.list[t++].num = 1;		// 8
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.FORESTERS_CLOAK;				data[x][z].sheet[id].inventory.list[t++].num = 1;		// 9
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.FORESTERS_GLOVE_LEFT;		data[x][z].sheet[id].inventory.list[t++].num = 1;		// 10
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.FORESTERS_GLOVE_RIGHT;	data[x][z].sheet[id].inventory.list[t++].num = 1;		// 11
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.FORESTERS_HAT;					data[x][z].sheet[id].inventory.list[t++].num = 1;		// 12
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.FORESTERS_KILT;					data[x][z].sheet[id].inventory.list[t++].num = 1;		// 13
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.FORESTERS_PANTS;				data[x][z].sheet[id].inventory.list[t++].num = 1;		// 14
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.FORESTERS_SHIRT;				data[x][z].sheet[id].inventory.list[t++].num = 1;		// 15
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.FORESTERS_SLEEVE_LEFT;	data[x][z].sheet[id].inventory.list[t++].num = 1;		// 16
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.FORESTERS_SLEEVE_RIGHT;	data[x][z].sheet[id].inventory.list[t++].num = 1;		// 17
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.FORESTERS_VEST;					data[x][z].sheet[id].inventory.list[t++].num = 1;		// 18

	// Leather/Quilted
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.FORESTERS_BOOT_LEFT;		data[x][z].sheet[id].inventory.list[t++].num = 1;		// 19
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.FORESTERS_BOOT_RIGHT;		data[x][z].sheet[id].inventory.list[t++].num = 1;		// 20
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.LEATHER_CAP;						data[x][z].sheet[id].inventory.list[t++].num = 1;		// 21
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.LEATHER_CUISSE_LEFT;		data[x][z].sheet[id].inventory.list[t++].num = 1;		// 22
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.LEATHER_CUISSE_RIGHT;		data[x][z].sheet[id].inventory.list[t++].num = 1;		// 23
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.LEATHER_GLOVE_LEFT;			data[x][z].sheet[id].inventory.list[t++].num = 1;		// 24
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.LEATHER_GLOVE_RIGHT;		data[x][z].sheet[id].inventory.list[t++].num = 1;		// 25
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.LEATHER_GREAVE_LEFT;		data[x][z].sheet[id].inventory.list[t++].num = 1;		// 26
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.LEATHER_GREAVE_RIGHT;		data[x][z].sheet[id].inventory.list[t++].num = 1;		// 27
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.LEATHER_SPAULDER_LEFT;	data[x][z].sheet[id].inventory.list[t++].num = 1;		// 28
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.LEATHER_SPAULDER_RIGHT;	data[x][z].sheet[id].inventory.list[t++].num = 1;		// 29
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.QUILTED_KILT;						data[x][z].sheet[id].inventory.list[t++].num = 1;		// 30
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.QUILTED_PANTS;					data[x][z].sheet[id].inventory.list[t++].num = 1;		// 31
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.QUILTED_SHIRT;					data[x][z].sheet[id].inventory.list[t++].num = 1;		// 32
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.QUILTED_VEST;						data[x][z].sheet[id].inventory.list[t++].num = 1;		// 33

	// Maille
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.MAILLE_COIF;						data[x][z].sheet[id].inventory.list[t++].num = 1;		// 34
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.MAILLE_CUISSE_LEFT;			data[x][z].sheet[id].inventory.list[t++].num = 1;		// 35
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.MAILLE_CUISSE_RIGHT;		data[x][z].sheet[id].inventory.list[t++].num = 1;		// 36
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.MAILLE_GLOVE_LEFT;			data[x][z].sheet[id].inventory.list[t++].num = 1;		// 37
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.MAILLE_GLOVE_RIGHT;			data[x][z].sheet[id].inventory.list[t++].num = 1;		// 38
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.MAILLE_GREAVE_LEFT;			data[x][z].sheet[id].inventory.list[t++].num = 1;		// 39
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.MAILLE_GREAVE_RIGHT;		data[x][z].sheet[id].inventory.list[t++].num = 1;		// 40
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.MAILLE_KILT;						data[x][z].sheet[id].inventory.list[t++].num = 1;		// 41
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.MAILLE_PANTS;						data[x][z].sheet[id].inventory.list[t++].num = 1;		// 42
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.MAILLE_SHIRT;						data[x][z].sheet[id].inventory.list[t++].num = 1;		// 43
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.MAILLE_SPAULDER_LEFT;		data[x][z].sheet[id].inventory.list[t++].num = 1;		// 44
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.MAILLE_SPAULDER_RIGHT;	data[x][z].sheet[id].inventory.list[t++].num = 1;		// 45
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.MAILLE_VEST;						data[x][z].sheet[id].inventory.list[t++].num = 1;		// 46

	// Plate
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.IRON_BRACER_LEFT;				data[x][z].sheet[id].inventory.list[t++].num = 1;		// 47
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.IRON_BRACER_RIGHT;			data[x][z].sheet[id].inventory.list[t++].num = 1;		// 48
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.IRON_CUIRASS;						data[x][z].sheet[id].inventory.list[t++].num = 1;		// 49
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.IRON_CUISSE_LEFT;				data[x][z].sheet[id].inventory.list[t++].num = 1;		// 50
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.IRON_CUISSE_RIGHT;			data[x][z].sheet[id].inventory.list[t++].num = 1;		// 51
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.IRON_DUSCK;							data[x][z].sheet[id].inventory.list[t++].num = 1;		// 52
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.IRON_GREAVE_LEFT;				data[x][z].sheet[id].inventory.list[t++].num = 1;		// 53
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.IRON_GREAVE_RIGHT;			data[x][z].sheet[id].inventory.list[t++].num = 1;		// 54
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.IRON_KILT;							data[x][z].sheet[id].inventory.list[t++].num = 1;		// 55
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.IRON_SPAULDER_LEFT;			data[x][z].sheet[id].inventory.list[t++].num = 1;		// 56
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.IRON_SPAULDER_RIGHT;		data[x][z].sheet[id].inventory.list[t++].num = 1;		// 57
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.SOCK_LEFT;							data[x][z].sheet[id].inventory.list[t++].num = 1;		// 58
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.SOCK_RIGHT;							data[x][z].sheet[id].inventory.list[t++].num = 1;		// 59


	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.WEAPON.CERPANNION;						data[x][z].sheet[id].inventory.list[t++].num = 1;		// 60
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.WEAPON.MALSTIFF;							data[x][z].sheet[id].inventory.list[t++].num = 1;		// 61
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.WEAPON.OSTOMOUS;							data[x][z].sheet[id].inventory.list[t++].num = 1;		// 62
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.WEAPON.SHORTARM;							data[x][z].sheet[id].inventory.list[t++].num = 1;		// 63
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.WEAPON.SHORTBOW;							data[x][z].sheet[id].inventory.list[t++].num = 1;		// 64
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.ARMOR.LEATHER_PANTS;					data[x][z].sheet[id].inventory.list[t++].num = 1;		// 65
	data[x][z].sheet[id].inventory.list[t].id = GAME::ITEMS.WEAPON.ARNGRAD;								data[x][z].sheet[id].inventory.list[t++].num = 1;		// 66

	data[x][z].sheet[id].inventory.iCount = t;
}

/*
 * TODO: Load the NPCs that are in the world
 *
 * Currently this loads all available NPCs from the
 * available sheets and is then copied into the
 * battle system when entering battle. Battle should
 * instead reference these existing NPCs.
 */
bool _NPC::load() {
	try {
		//Load NPC Information for current map
		//int x=gameVars->screen.iGridOffset;
		//int z=gameVars->screen.iGridOffset;

		for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
			for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {

				if(data[x][z].idcount == 0) {
					init_sx			= (rand() % (1023-64))+32;
					init_sz			= (rand() % (1023-64))+32;
				}

				LoadNpc(x, z, 0);
				LoadNpc(x, z, 1);
				LoadNpc(x, z, 2);
				LoadNpc(x, z, 3);
				LoadNpc(x, z, 4);
				LoadNpc(x, z, 5);
				LoadNpc(x, z, 6);
				LoadNpc(x, z, 7);
			}
		}

		//cout << "## LOAD NPC ##" << endl;
		//cout << "X: " << x << ", Z: " << z << endl;

		bLoad = true;
		return true;
	}
	catch(...) {
		return false;
	}
}

//bool _NPC::calc(MapData mapData[][9]) {
bool _NPC::calc() {
	try {
		//cout << "## CALC NPC ##" << endl;
		int iItemCount[255]	= {0};		//Current Item count for group

		//Standard Texture Coordinates
		Data2f vCoords[] = {	{1.0, 0.0},
								{0.0, 0.0},
								{0.0, 1.0},

								{1.0, 0.0},
								{0.0, 1.0},
								{1.0, 1.0} };


		//WE ONLY NEED THE CURRENT CHUNK
		for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
			for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {
				for (int count=0; count < data[x][z].idcount; count++) {
					float fW = data[x][z].sheet[count].init.w/2;
					float fH = data[x][z].sheet[count].init.h;
//					int		pX = data[x][z].sheet[count].init.x + (1024*x),
//								pZ = data[x][z].sheet[count].init.z + (1024*z);
					int		pX = data[x][z].sheet[count].init.x,
								pZ = data[x][z].sheet[count].init.z;

					cout << "NPC[" << x << "][" << z << "]:[" << count << "]\t(" << pX << ", " << pZ << ")" << endl;

					//data[x][z].sheet[count].transform.pos[1] = map.getHeight(pX, pZ, x, z);
						data[x][z].sheet[count].transform.pos[1] = map.getHeight(pX, pZ)*gameVars->screen.iScale;

					//cout << "NPC[" << x << "][" << z << "]:[" << count << "] => Height = " << data[x][z].sheet[count].transform.pos[1] << "\t(" << pX << ", " << pZ << ")" << endl;

					Data3f vVerts[]	=	{	{	 fW,	fH,		0.0	},
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
			}
		}
		return true;
	}
	catch(...) {
		return false;
	}
}

/*
 * TODO: Use this to replace the current set of NPCs with
 * new ones possibly.
 */
void _NPC::update() {
	//calc();
}

void _NPC::reload() {
	//int x=gameVars->screen.iGridOffset;
	//int z=gameVars->screen.iGridOffset;

	for (int x=0; x<gameVars->screen.iTerrainGrid; x++) {
		for (int z=0; z<gameVars->screen.iTerrainGrid; z++) {
			data[x][z].idcount = 0;
//			init_sx			= (rand() % (1023-64))+32;
//			init_sz			= (rand() % (1023-64))+32;
		}
	}

	load();
	calc();
}

void _NPC::reload(int x, int z) {
	//int x=gameVars->screen.iGridOffset;
	//int z=gameVars->screen.iGridOffset;
	data[x][z].idcount = 0;

//	init_sx			= (rand() % (1023-64))+32;
//	init_sz			= (rand() % (1023-64))+32;

	load();
	calc();
}

/*
 * TODO: This drawing routine is SLOW, need to fix this.
 * 		- Slow down caused by the function map.getHeight(), removed
 * 			from the function. The height should be set somewhere else.
 */
void _NPC::draw(Atmosphere &a) {
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
			//float iGrid = gameVars->screen.iGridOffset*1024;
				//float iX = x * 1024;
				//float iZ = z * 1024;
				for (int count=0; count < data[x][z].idcount; count++) {
					Core.matrix.Push();
						// Billboarding quicky
						// look = camera_pos - object_pos
						// up = y(normalized)
						// right = up x look (cross product)


						//float fHeight = map.getHeight(data[x][z].sheet[count].transform.pos[0]+iX, data[x][z].sheet[count].transform.pos[2]+iZ, x, z);
						//float fHeight = 0;
						//Vector3f	vObjPos = { float(data[x][z].sheet[count].transform.pos[0]+iX), 0.0f, float(data[x][z].sheet[count].transform.pos[2]+iZ) };
						Vector3f	vObjPos = { -float(data[x][z].sheet[count].transform.pos[0]), 0.0f, -float(data[x][z].sheet[count].transform.pos[2]) };
						//Diff(vLook, vCamPos, vObjPos);
						vLook = vCamPos - vObjPos;
						Normalize(vLook);
						Cross(vRight, vUp, vLook);

						//float fHeight = height(data[x][z].sheet[count].init.x, data[x][z].sheet[count].init.z, x, z);
						//float fHeight = height(data[x][z].sheet[count].transform.pos[0], data[x][z].sheet[count].transform.pos[2], x, z);

						//cout << "Height: " << fHeight << endl;

						Matrix44f	mLook = {	vRight[0],	vRight[1],	vRight[2],	0.0f,
																0.0f,				1.0f,				0.0f,				0.0f,
																vLook[0],		vLook[1],		vLook[2],		0.0f,
																vObjPos[0]*gameVars->screen.iScale,	-data[x][z].sheet[count].transform.pos[1],		vObjPos[2]*gameVars->screen.iScale,	1.0f };
												//vObjPos[0], float(data[x][z].sheet[count].init.y+data[x][z].sheet[count].init.blend), vObjPos[2], 1.0f };

//						if(x==4 && z==4) {
//							cout << "vCamPos: " << vCamPos[0] << ", " << vCamPos[1] << ", " << vCamPos[2] << endl;
//							cout << "vObjPos: " << vObjPos[0] << ", " << vObjPos[1] << ", " << vObjPos[2] << endl;
//						}

						Core.matrix.Apply(mLook);
						//Core.matrix.Scale(10.0f, 10.0f, 10.0f);
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

/*
 * Draw the target waypoint and attack card
 */
void _NPC::draw(Atmosphere &a, CharSheet &sheet, bool bCard=false) {
	glDisable(GL_CULL_FACE);
	Core.shader.use(GLS_FONT);

		Vector3f vCamPos;
		vCamPos[0] = -sheet.status.target->transform.pos[0];
		vCamPos[1] = 0.0f;
		vCamPos[2] = -sheet.status.target->transform.pos[2];
		Vector3f	vUp = { 0.0, 1.0, 0.0};
		Vector3f	vLook, vRight;
		Vector3f	vObjPos = { -float(sheet.transform.pos[0]), 0.0f, -float(sheet.transform.pos[2]) };

		//Diff(vLook, vCamPos, vObjPos);
		vLook = vCamPos - vObjPos;
		Normalize(vLook);
		Cross(vRight, vUp, vLook);

		Matrix44f	mLook = {	vRight[0],		vRight[1],	vRight[2],	0.0f,
												0.0f,					1.0f,				0.0f,				0.0f,
												vLook[0],			vLook[1],		vLook[2],		0.0f,
												vObjPos[0]*gameVars->screen.iScale,	-sheet.transform.pos[1],			vObjPos[2]*gameVars->screen.iScale,	1.0f };

		float fWave;
		if(!bCard) {
				fWave = fabs(sin(gameVars->timer.frameRate.get_ticks()/1000));
				Vector4f vTempColor;

				vTempColor[0] = gameVars->font.vColor[0];
				vTempColor[1] = gameVars->font.vColor[1];
				vTempColor[2] = gameVars->font.vColor[2];
				vTempColor[3] = gameVars->font.vColor[3];

				gameVars->font.vColor[0] = 1.0;
				gameVars->font.vColor[1] = 0.0;
				gameVars->font.vColor[2] = 0.0;
				gameVars->font.vColor[3] = 1.0*fWave;

				glEnable(GL_POLYGON_OFFSET_FILL);
				glPolygonOffset(-0.5f, -0.1f);
				Core.matrix.Push();
					Core.matrix.Apply(mLook);
					Core.matrix.Translate(0.0f, sheet.init.h+20, 0.0f);
					Core.matrix.Scale(10.0f, 50.0f, 10.0f);
					Core.matrix.SetTransform();
					Core.shader.getUniform(GLS_FONT);
					gameVars->texture.sprite.Set("target.png");
					sheet.init.vao.Draw();
				Core.matrix.Pop();

				Core.matrix.Push();
					Core.matrix.Apply(mLook);
					//Core.matrix.Translate(0.0f, sheet.init.h/2, 0.0f);
					//Core.matrix.Scale(1.05f, 1.05f, 1.05f);
					Core.matrix.SetTransform();
					Core.shader.getUniform(GLS_FONT);
					gameVars->texture.sprite.Set(sheet.init.image);
					sheet.init.vao.Draw();
				Core.matrix.Pop();
				glPolygonOffset(1.0f, 1.0f);
				glDisable(GL_POLYGON_OFFSET_FILL);

				gameVars->font.vColor[0] = vTempColor[0];
				gameVars->font.vColor[1] = vTempColor[1];
				gameVars->font.vColor[2] = vTempColor[2];
				gameVars->font.vColor[3] = vTempColor[3];
		}

		if(bCard) {
			/*
			 * TODO: need to add the health level to the battle card.
			 *   Not sure how to do this yet, could be percentage based
			 *   or just draw a black quad using a black icon that is scaled
			 *   to the appropriate sizeas needed.
			 *
			 */
			//glDisable(GL_DEPTH_TEST);
			glEnable(GL_POLYGON_OFFSET_FILL);
			fWave = sin((gameVars->timer.frameRate.get_ticks()/1000)*2)+10;
			mLook[13] += sheet.init.h+fWave;
			Core.matrix.Push();
				Core.matrix.Apply(mLook);
				Core.matrix.Scale(0.10f, 0.10f, 0.0f);
				Core.matrix.SetTransform();
				Core.shader.getUniform(GLS_FONT);

				gameSys.drawCard(0,sheet.status.iCards[0][0], sheet.status.iCards[0][1], sheet.status.iCards[0][2], "cards.png");
			Core.matrix.Pop();
			glDisable(GL_POLYGON_OFFSET_FILL);
			//glEnable(GL_DEPTH_TEST);
		}

	glEnable(GL_CULL_FACE);
}

///*
// * Draw an effect animation on a target
// */
//void _NPC::drawAnimation(CharSheet &sheet) {
//	glDisable(GL_CULL_FACE);
//	glDisable(GL_DEPTH_TEST);
//	glEnable(GL_POLYGON_OFFSET_FILL);
//
//	Core.shader.use(GLS_FONT);
//
//	Vector3f vCamPos;
//	vCamPos[0] = -sheet.status.target->transform.pos[0];
//	vCamPos[1] = 0.0f;
//	vCamPos[2] = -sheet.status.target->transform.pos[2];
//	Vector3f	vUp = { 0.0, 1.0, 0.0};
//	Vector3f	vLook, vRight;
//	Vector3f	vObjPos = { -float(sheet.transform.pos[0]), 0.0f, -float(sheet.transform.pos[2]) };
//
//	Diff(vLook, vCamPos, vObjPos);
//	Normalize(vLook);
//	Cross(vRight, vUp, vLook);
//
//	Matrix44f	mLook = {	vRight[0],		vRight[1],	vRight[2],	0.0f,
//											0.0f,					1.0f,				0.0f,				0.0f,
//											vLook[0],			vLook[1],		vLook[2],		0.0f,
//											vObjPos[0]*gameVars->screen.iScale,	-sheet.transform.pos[1],			vObjPos[2]*gameVars->screen.iScale,	1.0f };
//
//	Core.matrix.Push();
//		Core.matrix.Apply(mLook);
//		Core.matrix.Scale(0.10f, 0.10f, 0.0f);
//		Core.matrix.SetTransform();
//		Core.shader.getUniform(GLS_FONT);
//
//		gameSys.drawCard(0,sheet.status.iCards[0][0], sheet.status.iCards[0][1], sheet.status.iCards[0][2], "cards.png");
//	Core.matrix.Pop();
//
//	glDisable(GL_POLYGON_OFFSET_FILL);
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_CULL_FACE);
//}

/*
 * ???????
 */
void _NPC::draw(Atmosphere &a, CharSheet &sheet, CharSheet &lookAt, bool bCard=true) {
	//if(!sheet.init.bActive) {		//Don't draw if this is the active player
		glDisable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);
		Core.shader.use(GLS_FONT);

		cout << "ALT NPC DRAW" << endl;

			Vector3f	vObjPos = { -sheet.transform.pos[0], -sheet.transform.pos[1]+sheet.init.blend, -sheet.transform.pos[2] };
			Matrix44f	mTemp = {	1.0f, 0.0f, 0.0f, 0.0f,
									0.0f, 1.0f, 0.0f, 0.0f,
									0.0f, 0.0f, 1.0f, 0.0f,
									vObjPos[0], vObjPos[1], vObjPos[2], 1.0f };

			Vector3f vCamPos;
			vCamPos[0] = -lookAt.transform.pos[0];
			vCamPos[1] = vObjPos[1];
			vCamPos[2] = -lookAt.transform.pos[2];
			Vector3f	vUp = { 0.0, 1.0, 0.0};
			Vector3f	vLook, vRight;
			//Diff(vLook, vCamPos, vObjPos);
			vLook = vCamPos - vObjPos;
			Normalize(vLook);
			Cross(vRight, vUp, vLook);

			Matrix44f	mLook = {	vRight[0],	vRight[1],	vRight[2],	0.0f,
									0.0f,		1.0f,		0.0f,		0.0f,
									vLook[0],	vLook[1],	vLook[2],	0.0f,
									0.0f,		0.0f,		0.0f,		1.0f };

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

			mTemp[13] += sheet.init.h+fWave;

			/*
			 * Draw the combat status card
			 */
			if(bCard) {
				Core.matrix.Push();
					Core.matrix.Apply(mTemp);

					//Undo known world rotations, forcing icon to face screen always
					Core.matrix.Rotate(gameVars->player.active->transform.rot[1], 0.0, -1.0, 0.0);
					Core.matrix.Rotate(gameVars->player.active->transform.rot[0], -1.0, 0.0, 0.0);

					//Core.matrix.Translate(0.0f, sheet.init.h+10, 0.0f);
					Core.matrix.Scale(0.10f, 0.15f, 0.0f);
					Core.matrix.SetTransform();
					Core.shader.getUniform(GLS_FONT);

					gameSys.drawCard(0,sheet.status.iCards[0][0], sheet.status.iCards[0][1], sheet.status.iCards[0][2], "cards.png");
				Core.matrix.Pop();
			}

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
	//}
}
#endif /* NPC_H_ */
