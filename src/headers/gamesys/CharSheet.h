/*
 * CharSheet.h
 *
 *  Created on: Mar 6, 2014
 *      Author: bcthund
 */

#ifndef CHARSHEET_H_
#define CHARSHEET_H_

#include "../core/core_functions.h"

namespace Core {
	namespace GameSys {
		struct CharSheet {
		//	struct Init {
		//		int   blend;    // The depth offset of the object
		//		//float r;    	// Rotation for static objects (events)
		//		float x;   		// X Position of the object on the map (coord)
		//		float y;    	// Y Calculated height
		//		float z;    	// Z Position of the object on the map (coord)
		//		int   id;		// ID number, unique to this object (used for NPC)
		//		float w;		// Image width for the image this object uses
		//		float h;		// Image height for the image this object uses
		//		std::string image;  	// Image name this object requests (texture)
		//		bool isDead;
		//		bool bActive;					// Previously used to enable/disable drawing of the battle card and sprite in battle, now used to enable/disable drawing main character
		//		VAO vao;
		//
		//		std::string file,		// 3D ply file
		//								tex,		// ply texture map
		//								name;		// Characters Name
		//		int	face;				// face id to use from faces.png in the icon system
		//		bool b3dPlayer;
		//		std::string	sRole,
		//					sRace,
		//					sProfession,
		//					sState;
		//
		//
		//		Init() : blend(0),
		//						 x(0),
		//						 y(0),
		//						 z(0),
		//						 id(0),
		//						 w(0),
		//						 h(0),
		//						 image(""),
		//						 isDead(false),
		//						 file(""),
		//						 tex(""),
		//						 b3dPlayer(false),
		//						 face(0),
		//						 name(""),
		//						 bActive(false) {}
		//
		//	} init;
		//
		//	struct Cohort {
		//		short iNum;									// Number of cohorts in group
		//		int iSelected;							// Selected cohort in journal for positioning
		//		short iD,										// Cohort list id number
		//					iX,										// Cohort x position
		//					iY;										// Cohort y position
		//		//short iPlacement[11][11];		// 11x11 cohort position grid
		//		Vector2i vPlacement;					// grid placement for this cohort (-1 for leader)
		//		CharSheet * sheet[12];			// Up to 12 cohorts, pointers to loaded sheets in "player.h"
		//
		//		Cohort() {
		////			for(int x=0; x<11; x++) {
		////				for(int y=0;y<11; y++) {
		////						iPlacement[x][y] = -1;
		////				}
		////			}
		//			iNum					= 12;
		//			vPlacement[0] = 0;
		//			vPlacement[1] = 0;
		//			iSelected			= -1;
		//			iD						= 0;
		//			iX						= 0;
		//			iY						= 0;
		//		}
		//	} cohort;
		//
		//	struct Status {
		//		int iState;						// The menu option selected to execute from iExec
		//		int iExec;						// The execution state, used to process iState in Battle
		//		int	iIntent;					// Currently selected intent, for intent icon and setting iExec
		//		Vector3i iCards[16];			// Attack History on this player from ALL attackers
		//		CharSheet * target;				// This players currently selected target in battle
		//		short unsigned int iTargetId;	// Array index of enemy
		//		//int iTarget;					// The target number (based on iPlayer from runBattle.h)
		//		std::string lastAttack;			// ???
		//
		//		Status() : iState(0),
		//							 lastAttack(""),
		//							 target(NULL),
		//							 iTargetId(0),
		//							 iIntent(GAME::MENU.INTENT.OBSERVE),
		//							 iExec(0)//,
		//							 //iTarget(0)
		//		{}
		//
		//		/*
		//		 * Movement information for battle
		//		 */
		//		struct Move {
		//			bool allow;						//Allow or disallow movement
		//			float x, z;						//???
		//			int max;						//Maximum movement distance
		//			float now;						//Current movement distance left
		//			float fMoveMod;					//Current movement modifier
		//			unsigned int iSpeed;			//Applied Speed Mode (RUN, WALK)
		//			unsigned int iStance;			//Applied Stance (STAND, KNEEL, SIT, PRONE)
		//			//unsigned int iCurrentStance;	//Players current stance
		//
		//			Move() : allow(false),
		//							 x(0),
		//							 z(0),
		//							 max(0),
		//							 now(0),
		//							 fMoveMod(1.0f),
		//							 iSpeed(GAME::MENU.MOVE.WALK),
		//							 iStance(GAME::MENU.MOVE.STANCE.STAND) {}
		//							 //iCurrentStance(GAME.MENU.MOVE.STANCE.STAND) {}
		//
		//		} move;
		//
		//		/*
		//		 * This is old stuff and some of it may not be used
		//		 * anymore, we need to check what is still used and
		//		 * what can be moved out of here.
		//		 */
		//		struct Engage {
		//			unsigned int attack;	//Attack menu selection
		//			unsigned int magic;	//Magic menu selections
		//			int attackNum;			//How many attacks we can make this round (Set by movement selection) [default=1]
		//			unsigned int health;
		//			unsigned int limbHit;
		//			int iCritical;
		//			int iType;
		//			int applyLimbDamage;
		//			int applyHealthDamage;
		//
		//			Engage() : attack(0),
		//								 magic(0),
		//								 attackNum(0),
		//								 health(0),
		//								 limbHit(0),
		//								 iCritical(0),
		//								 applyLimbDamage(0),
		//								 applyHealthDamage(0),
		//								 iType(0) {}
		//		} engage;
		//
		//		struct Defense {
		//			int iMode;		//Applied defense mode
		//				//iCurrentMode;
		//
		//			Defense() : iMode(0) {}
		//						//iCurrentMode(0) {}
		//		} defense;
		//
		//		/*
		//		 * The Effect struct holds status effects and other similar
		//		 * 		items that need to be tracked on some sort of time
		//		 * 		basis, including things that may only last one
		//		 * 		round of battle such as "Off Balance".
		//		 *
		//		 * The list contains the id values of status effects so we can use an enum to refer
		//		 * 		to the status effect and get the proper data.
		//		 *
		//		 * The mode[] and val[] may be used to define how the status effect is applied. We
		//		 * 		may change this and use a single array to hold the number of rounds in effect.
		//		 * 		We could then use a value of -1 for effects that never end.
		//		 */
		//		struct Effect {
		//			uint off_balance;	//Value specifies number of rounds in effect
		//			uint list[256];		//List of applied effect id's
		//			uint mode[256];		//Corresponding mode of effect from list[], 0=rounds, 1=continuous, etc
		//			uint val[256];		//Value holder for effect, in mode 1 this is the number of rounds left in effect
		//			Effect() : off_balance(0) {
		//				for (int i=0;i<255;i++) {
		//					list[i] = 0;
		//					mode[i] = 0;
		//					val[i] = 0;
		//				}
		//			}
		//		} effect;
		//	} status;
		//
			struct Transform {
				Vector3f pos;
				Vector3f rot;	// RADIANS, North = 0 degrees
				Vector3f last;	// Last change in direction, used for functions that need to know the current movement direction vector
				//bool bBelowWater;	// Gets set by world when below water, modifies FOG and water shaders
				float r;
				float d;  // The most current distance from this object
		//		float	eyeHeight,
		//				currentHeight,
		//				reach;

				float GetAngle(bool bRad=false) {
					float fReturn;
					float fFix = 0;
					float fCorrect = -90;
					//if(bRad) fReturn = atan(last[0]/last[2]);
					//else fReturn = M_RadToDeg(atan(last[0]/last[2]));

					if(last[0] < 0.0f && last[2] > 0.0f) fFix = 0;
					else if(last[0] < 0.0f && last[2] < 0.0f) fFix = 180;
					else if(last[0] > 0.0f && last[2] < 0.0f) fFix = 180;
					else if(last[0] > 0.0f && last[2] > 0.0f) fFix = 360;

					fReturn = fFix - Radians(atan(last[0]/last[2])).toDegrees() + fCorrect;
					if(bRad) fReturn = Degrees(fReturn).toRadians();

					if(std::isnan(fReturn)) fReturn = 0.0f;

					return fReturn;
				}

				/*
				 * Is the player moving?
				 */
				bool DidMove() {
					bool bReturn = false;
					if(last[0] != 0.0f || last[2] != 0.0f) bReturn = true;
					else bReturn = false;
					return bReturn;
				}

				Transform() : r(0),
							  d(0) {
							  //eyeHeight(0),
							  //currentHeight(0),
							  //reach(0),
							  //bBelowWater(false) {
					pos[0] = 0;
					pos[1] = 0;
					pos[2] = 0;

					rot[0] = 0;
					rot[1] = 0;
					rot[2] = 0;
				}
			} transform;
		//
		//	/*
		//	 * This is the current state and history information from battle
		//	 */
		//	struct Damage {
		//		int hit_points;
		//
		//		Damage() : hit_points(0) {}
		//
		//		//CURRENTLY UNUSED
		//		struct History {
		//			struct Left_Arm {
		//				unsigned int weapon[4];
		//				Left_Arm() { weapon[0]=0; weapon[1]=0; weapon[2]=0; weapon[3]=0; }
		//			} left_arm[2];
		//			struct Right_Arm {
		//				unsigned int weapon[4];
		//				Right_Arm() { weapon[0]=0; weapon[1]=0; weapon[2]=0; weapon[3]=0; }
		//			} right_arm[2];
		//			struct Left_Leg {
		//				unsigned int weapon[4];
		//				Left_Leg() { weapon[0]=0; weapon[1]=0; weapon[2]=0; weapon[3]=0; }
		//			} left_leg[2];
		//			struct Right_Leg {
		//				unsigned int weapon[4];
		//				Right_Leg() { weapon[0]=0; weapon[1]=0; weapon[2]=0; weapon[3]=0; }
		//			} right_leg[2];
		//			struct Head {
		//				unsigned int weapon[4];
		//				Head() { weapon[0]=0; weapon[1]=0; weapon[2]=0; weapon[3]=0; }
		//			} head;
		//			struct Torso {
		//				unsigned int weapon[4];
		//				Torso() { weapon[0]=0; weapon[1]=0; weapon[2]=0; weapon[3]=0; }
		//			} torso;
		//		} history;
		//
		//		//Holds the damage information from the most recent attack made to this player
		//		struct Limb {
		//			struct Left_Arm {
		//				unsigned int weapon;		//What weapon cause the last attack
		//				unsigned int status[4];		//Holds the weapon that did the damage while at a specific critical range. This is the most recent weapon that did the attack only.
		//				int durability;				//"Health" for limb, starts at 100 points
		//				Left_Arm() : weapon(0), durability(0) { status[0]=0; status[1]=0; status[2]=0; status[3]=0; }
		//			} left_arm[2];
		//
		//			struct Right_Arm {
		//				unsigned int weapon;
		//				unsigned int status[4];
		//				int durability;
		//				Right_Arm() : weapon(0), durability(0) { status[0]=0; status[1]=0; status[2]=0; status[3]=0; }
		//			} right_arm[2];
		//
		//			struct Left_Leg {
		//				unsigned int weapon;
		//				unsigned int status[4];
		//				int durability;
		//				Left_Leg() : weapon(0), durability(0) { status[0]=0; status[1]=0; status[2]=0; status[3]=0; }
		//			} left_leg[2];
		//
		//			struct Right_Leg {
		//				unsigned int weapon;
		//				unsigned int status[4];
		//				int durability;
		//				Right_Leg() : weapon(0), durability(0) { status[0]=0; status[1]=0; status[2]=0; status[3]=0; }
		//			} right_leg[2];
		//
		//			struct Torso {
		//				unsigned int weapon;
		//				unsigned int status[4];
		//				int durability;
		//				Torso() : weapon(0), durability(0) { status[0]=0; status[1]=0; status[2]=0; status[3]=0; }
		//			} torso;
		//
		//			struct Head {
		//				unsigned int weapon;
		//				unsigned int status[4];
		//				int durability;
		//				Head() : weapon(0), durability(0) { status[0]=0; status[1]=0; status[2]=0; status[3]=0; }
		//			} head;
		//		} limb;
		//	} damage;

			/*
			 *
			 */
			/*
			struct Items {
				struct Weapon {
					int equipped;
					Weapon() : equipped(0) {}
				} weapon;

				struct Armor {
					int left_arm[2];
					int right_arm[2];
					int left_leg[2];
					int right_leg[2];
					int torso;
					int head;

					//int equipped;
					Armor() : torso(-1),
							  head(-1) {
							  left_arm[0] = -1;
							  left_arm[1] = -1;

							  right_arm[0] = -1;
							  right_arm[1] = -1;

							  left_leg[0] = -1;
							  left_leg[1] = -1;

							  right_leg[0] = -1;
							  right_leg[1] = -1;
					}
				} armor[5];		// Five Layers of armor: Skin/Base, Clothing, Leather/Quitled, Maille, Plate
			} items;
			*/

			/*
			 * The stats in this struct are the only player modified values
			 */
		//	struct Attributes {
		//		struct Strength {
		//			int max,
		//				strength,
		//				aura,
		//				mind,
		//				limbo,
		//				mod;
		//			Strength() : max(0), strength(0), aura(0), mind(0), limbo(0), mod(0) {}
		//		} str;
		//		struct Finesse {
		//			int max,
		//				finesse,
		//				aura,
		//				speed,
		//				limbo,
		//				mod;
		//			Finesse() : max(0), finesse(0), aura(0), speed(0), limbo(0), mod(0) {}
		//		} fin;
		//		struct Mobility {
		//			int max,
		//				mobility,
		//				speed,
		//				endurance,
		//				limbo,
		//				mod;
		//			Mobility() : max(0), mobility(0), speed(0), endurance(0), limbo(0), mod(0) {}
		//		} mob;
		//		struct Fatique {
		//			int max,
		//				fatigue,
		//				endurance,
		//				mind,
		//				limbo,
		//				mod;
		//			Fatique() : max(0), fatigue(0), endurance(0), mind(0), limbo(0), mod(0) {}
		//		} fat;
		//		struct Vicissitude {
		//			int max,
		//				vicissitude,
		//				aura,
		//				endurance,
		//				limbo,
		//				mod;
		//			Vicissitude() : max(0), vicissitude(0), aura(0), endurance(0), limbo(0), mod(0) {}
		//		} vic;
		//	} attributes;
		//
		//	struct Specialization {
		//		bool strength,
		//			 finesse,
		//			 mobility,
		//			 fatigue;
		//		Specialization() : strength(0), finesse(0), mobility(0), fatigue(0) {}
		//	} specialization;
		//
		//	struct Stats {
		//		int aura,
		//			speed,
		//			endurance,
		//			mind,
		//			auraMod,
		//			speedMod,
		//			enduranceMod,
		//			mindMod;
		//		Stats() : aura(0), speed(0), endurance(0), mind(0), auraMod(0), speedMod(0), enduranceMod(0), mindMod(0) {}
		//	} stats;
		//
		//	struct Combat_Check {
		//		int	reflex,
		//			willpower,
		//			fortitude,
		//			initiative;
		//		Combat_Check() : reflex(0), willpower(0), fortitude(0), initiative(0) {}
		//	} combat_check;
		//
		//	struct Skill_Check {
		//		int	intelligence,
		//			constitution,
		//			charisma,
		//			wisdom,
		//			dynamism,
		//			leadership;
		//		Skill_Check() : intelligence(0), constitution(0), charisma(0), wisdom(0), dynamism(0), leadership(0) {}
		//	} skill_check;
		//
		//	struct Other_Check {
		//		int load, stamina, weight;
		//		Other_Check() : load(0), stamina(0), weight(0) {}
		//	} other_check;
		//
		//	struct Magic_Check {
		//		int comprehension,
		//			mana,
		//			execution,
		//			intensity;
		//		Magic_Check() : comprehension(0), mana(0), execution(0), intensity(0) {}
		//	} magic_check;
		//
		//	struct Skills {
		//		int max, first, per;
		//		int id[50];
		//		int level[50];
		//		int rankMod;	//The denominator to calculate skill percentages
		//
		//		Skills() : max(0), first(0), per(0), rankMod(25) {
		//			for (int i=0;i<50;i++) {
		//				id[i] = 0;
		//				level[i] = 0;
		//			}
		//		}
		//	} skills;
		//
		//	struct Loads {
		//		int	light, medium, heavy, raise, lift, push;
		//		Loads() : light(0), medium(0), heavy(0), raise(0), lift(0), push(0) {}
		//	} load;
		//
		//	struct Mod {
		//		int		level;
		//		int		hit_points;		//Health level
		//		int		attack_bonus;	//
		//		int		combat_bonus;	//Unknown
		//		int		to_hit;			//Unknown
		//		int		weight;			//Starting weight modifer
		//		int		hitDie;			//Starting hit die (Hitpoint minimum)
		//		int		moveDistance;	//The maximum move distance in battle for this player
		//
		//		Mod() : level(0), hit_points(0), attack_bonus(0), combat_bonus(0), to_hit(0), weight(0), hitDie(0), moveDistance(0) {}
		//	} mod;
		//
		//	struct _Magic {
		//		struct _Spells {
		//			int		iMaxBookmark;					// Maximum number of bookmarks, should match array size below
		//			bool	bBookmark[12];				// Unlocked bookmarks
		//			int		iBookmark[12];				// Set bookmarks (spell id)
		//			int		iSelectedSpell;				// Currently selected spell block from bookmarks (-1 = None selected)
		//			bool	bSpellBlock[12][5];		// Unlocked spell block
		//			int		iSpellBlock[12][5];		// Applied spell on each available block (-1 = None )
		//			int		iTargetBlock[12];			// Target block location for targeted spells
		//
		//			/*
		//			 * !!! IMPORTANT !!!  !!! IMPORTANT !!!  !!! IMPORTANT !!!
		//			 *
		//			 * There is not a 1 to 1 correlation with regards to caster
		//			 *  blocks and the target blocks, we know the caster block
		//			 *  from these array structures but we need to track the
		//			 *  block of the target as well somehow. This will need to
		//			 *  be figured out as the system is gradually implemented.
		//			 *
		//			 * !!! IMPORTANT !!!  !!! IMPORTANT !!!  !!! IMPORTANT !!!
		//			 */
		//
		//			//We need both caster and target to manage things such as
		//			// master designation which requires us to know both who
		//			// casted it and who it applies to. Master designation
		//			// will show up on both the target and the casters spell
		//			// block. The caster needs to know if the target has this
		//			// designation before caster other spells that have the
		//			// master designation restriction on his target, but he
		//			// also needs to know if it was casted by himself. The
		//			// target needs to know who casted the master designation
		//			// on himself in case he wants to try a mind hack to
		//			// disable it. If we can simplify this then we really
		//			// should try to do so, maybe with battle character id
		//			// numbers.
		//			CharSheet *  csCaster[12][5];	//Who casted the spell on the block
		//			CharSheet *  csTarget[12][5];	//Who the target is on the block
		//
		//			_Spells() : iSelectedSpell(-1) {
		//				iMaxBookmark = 12;
		//
		//				for(int i=0; i<8;i++) bBookmark[i]=false;
		//				for(int i=0; i<8;i++) iBookmark[i]=-1;
		//
		//				for(int x=0; x<12;x++) {
		//					for(int y=0; y<5;y++) bSpellBlock[x][y]=false;
		//				}
		//
		//				for(int x=0; x<12;x++) {
		//					for(int y=0; y<5;y++) iSpellBlock[x][y]=-1;
		//				}
		//
		//				for(int x=0; x<12;x++) {
		//					for(int y=0; y<5;y++) csCaster[x][y]=NULL;
		//				}
		//
		//				for(int x=0; x<12;x++) {
		//					for(int y=0; y<5;y++) csTarget[x][y]=NULL;
		//				}
		//			}
		//		} spells;
		//	} magic;
		//
		//	// Inventory
		//	struct _INVENTORY {
		//
		//		int iSelected,		// Selected inventory id, for journal/menu system
		//				iCount;				// Number of items currently in inventory
		//
		//		string GetName(int iBodyPart, int iType) {
		//			// iBodyPart is where the item is equipped
		//			// iType is the type of item being one of the following:
		//			//		- Equipment
		//			//		- Base
		//			//		- Vestment
		//			//		- Quilted
		//			//		- Maille
		//			//		- Plate
		////			switch(i) {
		////				case GAME::ITEMS.BODYPART.HEAD:
		////					gameVars->player.active->inventory.equipped.
		////					return list
		////					break;
		////				case GAME::ITEMS.BODYPART.NECK:
		////					break;
		////				case GAME::ITEMS.BODYPART.LEFT_ARM:
		////					break;
		////				case GAME::ITEMS.BODYPART.RIGHT_ARM:
		////					break;
		////				case GAME::ITEMS.BODYPART.LEFT_HAND:
		////					break;
		////				case GAME::ITEMS.BODYPART.RIGHT_HAND:
		////					break;
		////				case GAME::ITEMS.BODYPART.LEFT_LEG:
		////					break;
		////				case GAME::ITEMS.BODYPART.RIGHT_LEG:
		////					break;
		////				case GAME::ITEMS.BODYPART.LEFT_FOOT:
		////					break;
		////				case GAME::ITEMS.BODYPART.RIGHT_FOOT:
		////					break;
		////			}
		//			return "Error, not implemented.";
		//		}
		//
		//		// Items in inventory, max of 1024
		//		struct {
		//			short int id;		// ID number for corresponding item database
		//			short int num;		// number of STACKED items, stacking determined by item database
		//		} list[1024];
		//
		//		// Items equipped on character, item database id number
		//		struct {
		//			struct _EQUIP {
		//				short int iHead,
		//									iNeck,
		//									iTorso,
		//									iLegs,
		//									iLeft_Arm,
		//									iLeft_Hand,
		//									iLeft_Leg,
		//									iLeft_Foot,
		//									iRight_Arm,
		//									iRight_Hand,
		//									iRight_Leg,
		//									iRight_Foot;
		//				bool bPrimary;				// Slot Selected as Primary
		//
		//				_EQUIP() {
		//					iHead = -1;
		//					iNeck = -1;
		//					iTorso = -1;
		//					iLegs = -1;
		//					iLeft_Arm = -1;
		//					iLeft_Hand = -1;
		//					iLeft_Leg = -1;
		//					iLeft_Foot = -1;
		//					iRight_Arm = -1;
		//					iRight_Hand = -1;
		//					iRight_Leg = -1;
		//					iRight_Foot = -1;
		//					bPrimary = 0;
		//				}
		//
		//			} equipment;
		//
		//			struct _BASE {
		//				short int iHead,
		//									iNeck,
		//									iTorso,
		//									iLegs,
		//									iLeft_Arm,
		//									iLeft_Hand,
		//									iLeft_Leg,
		//									iLeft_Foot,
		//									iRight_Arm,
		//									iRight_Hand,
		//									iRight_Leg,
		//									iRight_Foot;
		//
		//				_BASE() {
		//					iHead = -1;
		//					iNeck = -1;
		//					iTorso = -1;
		//					iLegs = -1;
		//					iLeft_Arm = -1;
		//					iLeft_Hand = -1;
		//					iLeft_Leg = -1;
		//					iLeft_Foot = -1;
		//					iRight_Arm = -1;
		//					iRight_Hand = -1;
		//					iRight_Leg = -1;
		//					iRight_Foot = -1;
		//				}
		//
		//			} base;
		//
		//			struct _VESTMENT {
		//				short int iHead,
		//									iNeck,
		//									iTorso,
		//									iLegs,
		//									iLeft_Arm,
		//									iLeft_Hand,
		//									iLeft_Leg,
		//									iLeft_Foot,
		//									iRight_Arm,
		//									iRight_Hand,
		//									iRight_Leg,
		//									iRight_Foot;
		//
		//				_VESTMENT() {
		//					iHead = -1;
		//					iNeck = -1;
		//					iTorso = -1;
		//					iLegs = -1;
		//					iLeft_Arm = -1;
		//					iLeft_Hand = -1;
		//					iLeft_Leg = -1;
		//					iLeft_Foot = -1;
		//					iRight_Arm = -1;
		//					iRight_Hand = -1;
		//					iRight_Leg = -1;
		//					iRight_Foot = -1;
		//				}
		//
		//			} vestment;
		//
		//			struct _QUILTED {
		//				short int iHead,
		//									iNeck,
		//									iTorso,
		//									iLegs,
		//									iLeft_Arm,
		//									iLeft_Hand,
		//									iLeft_Leg,
		//									iLeft_Foot,
		//									iRight_Arm,
		//									iRight_Hand,
		//									iRight_Leg,
		//									iRight_Foot;
		//
		//				_QUILTED() {
		//					iHead = -1;
		//					iNeck = -1;
		//					iTorso = -1;
		//					iLegs = -1;
		//					iLeft_Arm = -1;
		//					iLeft_Hand = -1;
		//					iLeft_Leg = -1;
		//					iLeft_Foot = -1;
		//					iRight_Arm = -1;
		//					iRight_Hand = -1;
		//					iRight_Leg = -1;
		//					iRight_Foot = -1;
		//				}
		//
		//			} quilted;
		//
		//			struct _MAILLE {
		//				short int iHead,
		//									iNeck,
		//									iTorso,
		//									iLegs,
		//									iLeft_Arm,
		//									iLeft_Hand,
		//									iLeft_Leg,
		//									iLeft_Foot,
		//									iRight_Arm,
		//									iRight_Hand,
		//									iRight_Leg,
		//									iRight_Foot;
		//
		//				_MAILLE() {
		//					iHead = -1;
		//					iNeck = -1;
		//					iTorso = -1;
		//					iLegs = -1;
		//					iLeft_Arm = -1;
		//					iLeft_Hand = -1;
		//					iLeft_Leg = -1;
		//					iLeft_Foot = -1;
		//					iRight_Arm = -1;
		//					iRight_Hand = -1;
		//					iRight_Leg = -1;
		//					iRight_Foot = -1;
		//				}
		//
		//			} maille;
		//
		//			struct _PLATE {
		//				short int iHead,
		//									iNeck,
		//									iTorso,
		//									iLegs,
		//									iLeft_Arm,
		//									iLeft_Hand,
		//									iLeft_Leg,
		//									iLeft_Foot,
		//									iRight_Arm,
		//									iRight_Hand,
		//									iRight_Leg,
		//									iRight_Foot;
		//
		//				_PLATE() {
		//					iHead = -1;
		//					iNeck = -1;
		//					iTorso = -1;
		//					iLegs = -1;
		//					iLeft_Arm = -1;
		//					iLeft_Hand = -1;
		//					iLeft_Leg = -1;
		//					iLeft_Foot = -1;
		//					iRight_Arm = -1;
		//					iRight_Hand = -1;
		//					iRight_Leg = -1;
		//					iRight_Foot = -1;
		//				}
		//
		//			} plate;
		//		} equipped;
		//
		//		_INVENTORY() {
		//			iSelected = -1;
		//			iCount = 0;
		//		}
		//
		//	} inventory;
		};

		//struct NPCSheet {
		//	int idcount;		// Number of objects loaded
		//	CharSheet sheet[256];
		//
		//	NPCSheet() : idcount(0) {}
		//};
	}
}
#endif /* CHARSHEET_H_ */
