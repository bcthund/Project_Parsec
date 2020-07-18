/////*
//// * global.h
//// *
//// *  Created on: Sep 18, 2010
//// *      Author: bcthund
//// *
//// *      These are global constants, type definitions, and preprocessor declarations needed everywhere
//// */
////#ifndef GLOBAL_H_
////#define GLOBAL_H_
//////No longer used, used to edit maps
////enum MAP_MODE {   MODE_EXPLORE, MODE_LANDSCAPE };
////
//////General Enum Constants
////enum GEN_CONST { G_STAND=0, G_CROUCH=1, G_PRONE=2 };
////
//////Unknown usage
////enum MOD_VAL {   MOD_X, MOD_Y, MOD_Z }; //What value are we modifying? Used for various functions
////
//////Sets the display mode, for debugging
////enum POLYGON_MODE {  PM_LINE, PM_POINT, PM_FILL }; //To set what polygon mode we are in
////
////Matrix modes
////enum MATRIX_MODES {  MM_PERSPECTIVE, MM_ORTHO, MM_LIGHT };
//////
//////enum TYPES { TYPE_BOOL, TYPE_INT, TYPE_FLOAT };
//////
////////VAO drawing modes
////enum DRAWING_MODES { 	GLM_BASE=0,
////						GLM_DRAW,
////						GLM_DRAW_ARRAYS,
////						GLM_DRAW_ELEMENTS,
////						GLM_DRAW_RANGE,
////						GLM_DRAW_RANGE_ELEMENTS,
////						GLM_DRAW_ARRAYS_INSTANCED,
////						GLM_LAST };
//////
////////Shader program names, needs cleanup
///////*
////enum SHADER_PROGRAMS {	GLS_BASE = 0, GLS_IDENTITY, GLS_FLAT, GLS_LINES, GLS_FONT,
////						GLS_NORMAL, GLS_NORMAL_LINE, GLS_NORMAL_LINE2, GLS_NORMAL_TRI, GLS_TEXCOORD,
////						GLS_SHADED, GLS_DIFFUSE, GLS_DIFFUSE2, GLS_PHONG, GLS_GOURAUD,
////						GLS_SHADED_TEX, GLS_SHADED_TEX_ALPHA, GLS_ADS_TEX, GLS_DIRECTIONAL, GLS_DIRECTIONAL_TERRAIN, GLS_WATER,
////						GLS_TYPHOON_DIRECTIONAL, GLS_SHADOW, GLS_DIR_SHADOW, GLS_DIR_PHONG, GLS_DEPTH_VIEW, GLS_DEPTH_ALPHA, GLS_LAST };
////*/
////
//////struct _SHADER_MAP {
//////	uint SHADER;
//////	string NAME;
//////
//////	static uint * LAST;
//////
//////	public:
//////	_SHADER_MAP(uint id, string name, uint * last) {
//////		SHADER = id;
//////		NAME = name;
//////		LAST = last;
//////		last++;
//////	};
//////};
//////
//////struct {
//////	uint LAST;
//////	_SHADER_MAP FONT				= _SHADER_MAP(0, "font",					&LAST);
//////	_SHADER_MAP ICON				= _SHADER_MAP(1, "icon",					&LAST);
//////	_SHADER_MAP FLAT				= _SHADER_MAP(2, "flat",					&LAST);
//////	_SHADER_MAP FLAT_FOG			= _SHADER_MAP(3, "flat_fog",				&LAST);
//////	_SHADER_MAP FLAT_FOG_SHEAR		= _SHADER_MAP(4, "flat_fog_shear",			&LAST);
//////	_SHADER_MAP FLAT_FOG_INSTANCE	= _SHADER_MAP(5, "flat_fog_instance",		&LAST);
//////	_SHADER_MAP SHADED_TEX			= _SHADER_MAP(6, "shaded_tex",				&LAST);
//////	_SHADER_MAP SHADED_TEX_ALPHA	= _SHADER_MAP(7, "shaded_tex_alpha",		&LAST);
//////	_SHADER_MAP NORMAL_LINE2		= _SHADER_MAP(8, "normal_line2",			&LAST);
//////	_SHADER_MAP DIRECTIONAL			= _SHADER_MAP(9, "directional",				&LAST);
//////	_SHADER_MAP DIRECTIONAL_TERRAIN = _SHADER_MAP(10, "directional_terrain",	&LAST);
//////	_SHADER_MAP TROPOSPHERE			= _SHADER_MAP(11, "troposphere",			&LAST);
//////	_SHADER_MAP STRATOSPHERE		= _SHADER_MAP(12, "stratosphere",			&LAST);
//////	_SHADER_MAP THERMOSPHERE		= _SHADER_MAP(13, "thermosphere",			&LAST);
//////	_SHADER_MAP SUN					= _SHADER_MAP(14, "sun",					&LAST);
//////	_SHADER_MAP SUN2				= _SHADER_MAP(15, "sun2",					&LAST);
//////	_SHADER_MAP EXOSPHERE			= _SHADER_MAP(16, "exosphere",				&LAST);
//////	_SHADER_MAP WATER_DIRECTIONAL	= _SHADER_MAP(17, "water_directional",		&LAST);
//////	_SHADER_MAP SNOW				= _SHADER_MAP(18, "snow",					&LAST);
//////	_SHADER_MAP SNOW2				= _SHADER_MAP(19, "snow2",					&LAST);
//////	_SHADER_MAP RAIN				= _SHADER_MAP(20, "rain",					&LAST);
//////	_SHADER_MAP HAIL				= _SHADER_MAP(21, "hail",					&LAST);
//////	_SHADER_MAP FLORA				= _SHADER_MAP(22, "flora",					&LAST);
//////	_SHADER_MAP UWFLORA				= _SHADER_MAP(23, "uwflora",				&LAST);
//////	_SHADER_MAP GRASS_TRI			= _SHADER_MAP(24, "grass_tri",				&LAST);
//////	_SHADER_MAP GRASS_LINE			= _SHADER_MAP(25, "grass_line",				&LAST);
//////	_SHADER_MAP SCATTER				= _SHADER_MAP(26, "scatter",				&LAST);
//////	_SHADER_MAP PP_CONTRAST			= _SHADER_MAP(27, "pp_contrast",			&LAST);
//////	_SHADER_MAP PP_BRIGHTNESS		= _SHADER_MAP(28, "pp_brightness",			&LAST);
//////	_SHADER_MAP PP_UNDERWATER		= _SHADER_MAP(29, "pp_underwater",			&LAST);
//////	_SHADER_MAP PP_HBLUR			= _SHADER_MAP(30, "pp_hblur",				&LAST);
//////	_SHADER_MAP PP_VBLUR			= _SHADER_MAP(31, "bb_vblur",				&LAST);
//////	_SHADER_MAP PP_RAYBLUR			= _SHADER_MAP(32, "pp_rayblur",				&LAST);
//////	_SHADER_MAP PP_BLOOM			= _SHADER_MAP(33, "pp_bloom",				&LAST);
//////	_SHADER_MAP PP_DEPTHOFFIELD		= _SHADER_MAP(34, "pp_depthoffield",		&LAST);
//////	_SHADER_MAP PP_VINETTE			= _SHADER_MAP(35, "pp_vinette",				&LAST);
//////	_SHADER_MAP PP_LENSFLARE		= _SHADER_MAP(36, "pp_lensflare",			&LAST);
//////	_SHADER_MAP PP_EDGEDETECT		= _SHADER_MAP(37, "pp_edgedetect",			&LAST);
//////	_SHADER_MAP PP_CARTOON			= _SHADER_MAP(38, "pp_cartoon",				&LAST);
//////	_SHADER_MAP PP_CELLSHADING		= _SHADER_MAP(39, "pp_cellshading",			&LAST);
//////	_SHADER_MAP PP_COMBINE			= _SHADER_MAP(40, "pp_combine",				&LAST);
//////	_SHADER_MAP PP_PIXELATE			= _SHADER_MAP(41, "pp_pixelate",			&LAST);
//////} GLS;
////
////enum SHADER_PROGRAMS {	GLS_BASE = 0,
////						GLS_FONT,
////						GLS_ICON,
////						GLS_BOUNDINGVOLUME,
////						GLS_FLAT,
////						GLS_FLAT_FOG,
////						GLS_FLAT_FOG_SHEAR,
////						GLS_FLAT_FOG_INSTANCE,
////						GLS_SHADED_TEX,
////						GLS_SHADED_TEX_ALPHA,
////						GLS_NORMAL_LINE2,
////						GLS_DIRECTIONAL,
////						GLS_DIRECTIONAL_TERRAIN,
////						GLS_DIRECTIONAL_WATER,
////						GLS_TROPOSPHERE,
////						GLS_STRATOSPHERE,
////						GLS_THERMOSPHERE,
////						GLS_SUN,
////						GLS_EXOSPHERE,
////						GLS_SNOW,		// 2D Snow
////						GLS_SNOW2,		// 3D Snow
////						GLS_RAIN,		// 3D Rain
////						GLS_HAIL,
////						GLS_FLORA,
////						GLS_UWFLORA,
////						GLS_GRASS_TRI,
////						GLS_GRASS_LINE,
////						GLS_SCATTER,
////						GLS_PP_CONTRAST,
////						GLS_PP_BRIGHTNESS,
////						GLS_PP_UNDERWATER,
////						GLS_PP_HBLUR,
////						GLS_PP_VBLUR,
////						GLS_PP_RAYBLUR,
////						GLS_PP_BLOOM,
////						GLS_PP_DEPTHOFFIELD,
////						GLS_PP_VINETTE,
////						GLS_PP_LENSFLARE,
////						GLS_PP_EDGEDETECT,
////						GLS_PP_CARTOON,
////						GLS_PP_CELLSHADING,
////						GLS_PP_COMBINE,
////						GLS_PP_PIXELATE,
////						GLS_LAST };
////
//////Mouse Labeling
////enum MOUSE_CONTROL			{MOUSE_BUTTON_ONE=0, MOUSE_BUTTON_TWO=1, MOUSE_BUTTON_THREE=2 };
////
//////Shader binding attributes
////enum GLT_SHADER_ATTRIBUTE { GLA_VERTEX	= 0,	// Vertex Data
////							GLA_COLOR,			// Colors
////							GLA_NORMAL,			// Normals
////							GLA_INDEX,			// Index positions
////							GLA_TEXTURE,		//
////                            GLA_TEXTURE0,		//
////                            GLA_TEXTURE1,		//
////                            GLA_TEXTURE2,		//
////                            GLA_TEXTURE3,		//
////                            GLA_POSITION,		// Position data for instanced arrays
////                            GLA_EXTRA,			// Extra data for instaced arrays
////                            GLA_LAST};
////
//////Map loading/Unloading
////enum SHIFT_DIRECTION { SHIFT_UP=0, SHIFT_DOWN, SHIFT_LEFT, SHIFT_RIGHT, SHIFT_LAST };
////enum STITCH_SIDE { STITCH_TOP=0, STITCH_BOTTOM, STITCH_LEFT, STITCH_RIGHT, STITCH_LAST };
////
//////ARRAY_OFFSETS
////enum ARRAY_OFFSETS			{	X=0, Y=1, Z=2, UPPER=0, LOWER=1, NONE=-1, ZERO=0, ONE=1, TWO=2, THREE=3, FOUR=4, FIVE=5, SIX=6, SEVEN=7, EIGHT=8, NINE=9, TEN=10,
////								PLAYER=-1, ENEMY1=0, ENEMY2=1, ENEMY3=2, ENEMY4=3 };
////
//////Possible states of the mouse for use on menu interaction
////enum MOUSE_STATES			{	MOUSE_NONE		=	0,
////								MOUSE_HOVER		=	1,	//We put mouse hover here to keep boolean style functionality for mouse click
////								MOUSE_LEFT		=	2,
////								MOUSE_RIGHT		=	4,
////								MOUSE_MIDDLE	=	8,
////								MOUSE_DOUBLE	=	16};
////
//////Battle Damage types
/////*
//// * These values are used in defining weapons and armor and then used
//// * 		for combat checks. It also stores values that refer to where
//// * 		an attack was made.
//// */
////enum BATTLE_DAMAGE_STATUS	{ 	DAMAGE_NONE=0, DAMAGE_CRITICAL_ZERO=1, DAMAGE_CRITICAL_ONE=2, DAMAGE_CRITICAL_TWO=4, DAMAGE_CRITICAL_THREE=8, DAMAGE_CRITICAL_FOUR=16, DAMAGE_CRITICAL_FIVE=32,
////															DAMAGE_LIMB_HEAD=1, DAMAGE_LIMB_TORSO=2, DAMAGE_LIMB_ARM=4, DAMAGE_LIMB_LEG=8, DAMAGE_LIMB_LEFT=16, DAMAGE_LIMB_RIGHT=32, DAMAGE_LIMB_UPPER=64, DAMAGE_LIMB_LOWER=128};
//////DAMAGE_ONE_HANDED=1, DAMAGE_TWO_HANDED=2,
//////															DAMAGE_TYPE_BLADE=1, DAMAGE_TYPE_BLUNT=2, DAMAGE_TYPE_AXE=4, DAMAGE_TYPE_SPEAR=8, DAMAGE_TYPE_ARROW=16, DAMAGE_TYPE_JAW=32, DAMAGE_TYPE_HAND=64, DAMAGE_TYPE_CLAW=128,
//////
//////string getDamageType(int i) {
//////	switch (i) {
//////		case DAMAGE_TYPE_BLADE:
//////			return "Blade";
//////			break;
//////		case DAMAGE_TYPE_BLUNT:
//////			return "Blunt";
//////			break;
//////		case DAMAGE_TYPE_AXE:
//////			return "Axe";
//////			break;
//////		case DAMAGE_TYPE_SPEAR:
//////			return "Spear";
//////			break;
//////		case DAMAGE_TYPE_ARROW:
//////			return "Arrow";
//////			break;
//////		case DAMAGE_TYPE_JAW:
//////			return "Jaw";
//////			break;
//////		case DAMAGE_TYPE_CLAW:
//////			return "Claw";
//////			break;
//////		case DAMAGE_TYPE_HAND:
//////			return "Hand";
//////			break;
//////	}
//////	return "Error";
//////}
////
////enum BATTLE_ATTACK_TYPES	{	ATTACK_TYPE_NONE=0, ATTACK_TYPE_CHOP=1, ATTACK_TYPE_SWING=2, ATTACK_TYPE_THRUST=4	};
////
////enum _DAMAGE_TYPES { BLADE=0, BLUNT, AXE, SPEAR, ARROW, JAW, CLAW, HAND };
////
////enum ARMOR_BONUS_BIT		{	ARMOR_BONUS_NONE	= 0,
////								ARMOR_BONUS_BLADE	= 1,
////								ARMOR_BONUS_BLUNT	= 2,
////								ARMOR_BONUS_AXE		= 4,
////								ARMOR_BONUS_SPEAR	= 8,
////								ARMOR_BONUS_ARROW	= 16,
////								ARMOR_BONUS_JAW		= 32,
////								ARMOR_BONUS_CLAW	= 64,
////								ARMOR_BONUS_HAND	= 128	};
////
//////enum ARMOR_RESISTANCE_TYPES	{	ARMOR_RES_WATER		= 0,
//////								ARMOR_RES_JELLO		= 1,
//////								ARMOR_RES_SKIN		= 3,
//////								ARMOR_RES_CLOTH		= 6,
//////								ARMOR_RES_PADDED	= 9,
//////								ARMOR_RES_LOWEST	= 12,
//////								ARMOR_RES_LOW		= 15,
//////								ARMOR_RES_MEDLOW	= 18,
//////								ARMOR_RES_MEDHIGH	= 21,
//////								ARMOR_RES_HIGH		= 24,
//////								ARMOR_RES_HIGHEST	= 27,
//////								ARMOR_RES_STONE		= 32,
//////								ARMOR_RES_IMMUNE	= 33,
//////								ARMOR_RES_GOD		= 34 };
////
//////Typical BIT values
////enum						{ BIT_ZERO=0, BIT_ONE=1, BIT_TWO=2, BIT_THREE=4, BIT_FOUR=8, BIT_FIVE=16, BIT_SIX=32, BIT_SEVEN=64, BIT_EIGHT=128, BIT_NINE=256, BIT_TEN=512 };
////
//////ARMOR_TYPES
/////*
////enum ARMOR_TYPES			{	ARMOR_NONE = -1,
////								ARMOR_STONESKIN = 0,
////								ARMOR_SKIN,
////								ARMOR_RINGMAIL,
////								ARMOR_RINGMAIL_LARGE,
////								ARMOR_SCALEMAIL_LEATHER,
////								ARMOR_SCALEMAIL_CLOTH,
////								ARMOR_SHINGLEMAIL,
////								ARMOR_MEDALLIONMAIL_LEATHER,
////								ARMOR_BRIGANDINE,
////								ARMOR_SPLINTED,
////								ARMOR_LEATHER,
////								ARMOR_CLOTH,
////								ARMOR_PADDED,
////								ARMOR_QUILTED,
////								ARMOR_SHARKSKIN,
////								ARMOR_PLATE_STEEL,
////								ARMOR_PLATE_IRON,
////								ARMOR_PLATE_COPPER,
////								ARMOR_PLATE_BRONZE,
////								ARMOR_PLATE_ALUMINIUM,
////								ARMOR_PLATE_BRASS,
////								ARMOR_PLATE_TACHANITE,
////								ARMOR_LORICAT_STEEL,
////								ARMOR_LORICAT_IRON,
////								ARMOR_LORICAT_COPPER,
////								ARMOR_LORICAT_BRONZE,
////								ARMOR_LORICAT_ALUMINIUM,
////								ARMOR_LORICAT_BRASS,
////								ARMOR_LORICAT_TACHANITE,
////								ARMOR_SILK, ARMOR_MITHRIL,
////								ARMOR_FURR_MEDIUM,
////								ARMOR_FURR_THICK,
////								ARMOR_SCALES_MEDIUM,
////								ARMOR_SCALES_THICK,
////								ARMOR_SCALES_SOLID,
////								ARMOR_CRYGATE,
////								ARMOR_BALLHAT,
////								ARMOR_LAST};
////								*/
////
//////WEAPON NAMES
/////*
////enum WEAPON_NAMES			{	WEAPON_NONE,
////								WEAPON_OINK,
////								WEAPON_ARNGRAD,
////								WEAPON_OSTOMOUS,
////								WEAPON_HAULOUS,
////								WEAPON_CERPANNION,
////								WEAPON_LONG_OSTOMOUS,
////								WEAPON_WAR_OSTOMOUS,
////								WEAPON_WORK_HAMMER,
////								WEAPON_MALSTIFF,
////								WEAPON_CLEAVER,
////								WEAPON_SHORTARM,
////								WEAPON_LONGARM,
////								WEAPON_PILUMSLIM,
////								WEAPON_WANG,
////								WEAPON_CRYGATE_TENTACLE,
////								WEAPON_BITE_00,
////								WEAPON_CLAW_00,
////								WEAPON_HAND_00	};
////								*/
////
////enum MAX_CRITICALS			{	CRITICAL_ZERO=0, CRITICAL_ONE=1, CRITICAL_TWO=2, CRITICAL_THREE=3, CRITICAL_FOUR=4	};
////
////enum MATERIAL_TYPES			{
////								MATERIAL_NONE,
////								MATERIAL_GLASS,
////								MATERIAL_FLESH,
////								MATERIAL_IVORY,
////								MATERIAL_BRONZE,
////								MATERIAL_LEAD,
////								MATERIAL_ZINC,
////								MATERIAL_COPPER,
////								MATERIAL_BRASS,
////								MATERIAL_IRON,
////								MATERIAL_STEEL,
////								MATERIAL_COBALT,
////								MATERIAL_WOOL,
////								MATERIAL_BURLAP,
////								MATERIAL_HYDE,
////								MATERIAL_COTTON,
////								MATERIAL_HEMP,
////								MATERIAL_YEW,
////								MATERIAL_BEACH,
////								MATERIAL_OAK,
////								MATERIAL_MAPLE,
////								MATERIAL_LIGNUMVITAE,
////								MATERIAL_TACHANITE};
////
////struct CHAR_SHEET_STRUCT {
////	struct _SKILL {
////		enum e_SKILL	{
////			NONE=0,
////			DODGE,
////			DEFLECT,
////			BLOCK,
////			BLADE,
////			BLUNT,
////			AXE,
////			SPEAR,
////			ARROW,
////			JAW,
////			CLAW,
////			HAND
////		};
////	} SKILL;
////} CS;
////
/////*
//// * Nested menu states
//// */
////int iA = 0;
//
//int iC = 0;
//namespace Core {
//	struct _ID {
////		struct _INVENTORY {
////			struct _TYPE {
////				const int NONE	  = 0;		// Empty slot in inventory
////				const int GENERAL = 1;
////				const int WEAPON  = 2;
////				const int ARMOR   = 3;
////			} TYPE;
////		} INVENTORY;
////
////		struct _MATERIAL {
////			enum {
////					NONE,
////					GLASS,
////					FLESH,
////					IVORY,
////					BRONZE,
////					LEAD,
////					ZINC,
////					COPPER,
////					BRASS,
////					IRON,
////					STEEL,
////					COBALT,
////					WOOL,
////					BURLAP,
////					HYDE,
////					COTTON,
////					MITHRIL,
////					HEMP,
////					YEW,
////					BEACH,
////					OAK,
////					MAPLE,
////					LIGNUMVITAE,
////					TACHANITE };
////
////			string NAMES[32];
////
////			_MATERIAL() {
////				NAMES[NONE] 				= "None";
////				NAMES[GLASS] 				= "Glass";
////				NAMES[FLESH] 				= "Flesh";
////				NAMES[IVORY] 				= "Ivory";
////				NAMES[BRONZE] 			= "Bronze";
////				NAMES[LEAD] 				= "Lead";
////				NAMES[ZINC] 				= "Zinc";
////				NAMES[COPPER] 			= "Copper";
////				NAMES[BRASS] 				= "Brass";
////				NAMES[IRON] 				= "Iron";
////				NAMES[STEEL] 				= "Steel";
////				NAMES[COBALT] 			= "Cobalt";
////				NAMES[WOOL] 				= "Wool";
////				NAMES[BURLAP] 			= "Burlap";
////				NAMES[HYDE] 				= "Hyde";
////				NAMES[COTTON] 			= "Cotton";
////				NAMES[MITHRIL] 			= "Mithril";
////				NAMES[HEMP] 				= "Hemp";
////				NAMES[YEW] 					= "Yew";
////				NAMES[BEACH] 				= "Beach";
////				NAMES[OAK] 					= "Oak";
////				NAMES[MAPLE] 				= "Maple";
////				NAMES[LIGNUMVITAE] 	= "Lignum Vitae";
////			}
////
////		} MATERIAL;
//
//		struct _SYSTEM {
//			struct _WINSYS {
//				struct _DRAWMODE {
//				enum LIST {	NORMAL = 0,			// Draw background with border
//							BORDER_ONLY,		// Draw border only
//							NO_BORDER,			// Draw background only
//							SELECTION	};		// Draw selection border (border only)
//				} DRAWMODE;
//			} WINSYS;
//
//		} SYSTEM;
//
////		struct _WEAPON {
////			struct _TYPE {
////				enum {	BLADE,
////								BLUNT,
////								AXE,
////								SPEAR,
////								ARROW,
////								JAW,
////								CLAW,
////								HAND,
////								OTHER
////				};
////				string NAME[32];
////
////				std::string to_str(int i) {
////					std::string sR = "Null";
////					if( i > 34 ) sR = NAME[BLADE];
////					else {
////						switch (i) {
////							case BLADE: sR	= NAME[BLADE];	break;
////							case BLUNT: sR	= NAME[BLUNT];	break;
////							case AXE: 	sR	= NAME[AXE];		break;
////							case SPEAR: sR	= NAME[SPEAR];	break;
////							case ARROW: sR	= NAME[ARROW];	break;
////							case JAW: 	sR	= NAME[JAW];		break;
////							case CLAW: 	sR	= NAME[CLAW];		break;
////							case HAND: 	sR	= NAME[HAND];		break;
////							case OTHER: sR	= NAME[OTHER];	break;
////						}
////					}
////					return sR;
////				};
////
////				_TYPE() {
////					NAME[BLADE] 				= "Blade";
////					NAME[BLUNT] 				= "Blunt";
////					NAME[AXE] 					= "Axe";
////					NAME[SPEAR] 				= "Spear";
////					NAME[ARROW] 				= "Arrow";
////					NAME[JAW] 					= "Jaw";
////					NAME[CLAW] 					= "Claw";
////					NAME[HAND] 					= "Hand";
////					NAME[OTHER] 				= "Other";
////				}
////			} TYPE;
////
////			struct _HAND {
////				const int ONE 			= 0;
////				const int TWO 			= 1;
////				const int ONEHALF 	= 2;		// TODO: This may not work
////				const int THREE 		= 3;
////			} HAND;
////
////			struct _BASE {
////				enum {	NONE = -1,
////								OINK = 0,
////								ARNGRAD,
////								OSTOMOUS,
////								HAULOUS,
////								CERPANNION,
////								LONG_OSTOMOUS,
////								WAR_OSTOMOUS,
////								WORK_HAMMER,
////								MALSTIFF,
////								CLEAVER,
////								SHORTARM,
////								FULLARM,
////								LONGARM,
////								PILUMSLIM,
////								WANG,
////								CRYGATE_TENTACLE,
////								SHORTBOW,
////								BITE_00,
////								CLAW_00,
////								HAND_00,
////								UGEECHARUS
////				};
////			} BASE;
////
////		} WEAPON;
////
////			struct _SHIELD {
////				struct _BASE {
////					enum {	NONE = -1,
////									BUCKLER = 0,
////									AUNQUEIR,
////									THEIBON,
////									KYTE,
////									HOPLON,
////									PAVIS,
////									GREAT_KYTE,
////									TOWER,
////									GREAT_HOPLON
////					};
////	//				string NAME[32];
////	//
////	//				std::string to_str(int i) {
////	//					std::string sR = "Null";
////	//					if( i > 34 ) sR = NAME[BLADE];
////	//					else {
////	//						switch (i) {
////	//							case : sR	= NAME[];	break;
////	//							case : sR	= NAME[];	break;
////	//							case : 	sR	= NAME[];		break;
////	//							case : sR	= NAME[];	break;
////	//							case : sR	= NAME[];	break;
////	//							case : 	sR	= NAME[];		break;
////	//							case : 	sR	= NAME[];		break;
////	//							case : 	sR	= NAME[];		break;
////	//							case : sR	= NAME[];	break;
////	//						}
////	//					}
////	//					return sR;
////	//				};
////	//
////	//				_BASE() {
////	//					NAME[] 					= "None";
////	//					NAME[] 			= "Buckler";
////	//					NAME[] 			= "Aunqueir";
////	//					NAME[] 			= "Theibon";
////	//					NAME[] 					= "Kyte";
////	//					NAME[] 				= "Hoplon";
////	//					NAME[] 				= "Pavis";
////	//					NAME[] 		= "Great Kyte";
////	//					NAME[] 				= "Tower";
////	//					NAME[]	= "Hoplon";
////	//				}
////			} BASE;
////		} SHIELD;
////
////		struct _ARMOR {
////			struct _TYPE {
////				const int NONE = 0;
////				const int VESTMENT = 1;
////				const int QUILTED  = 2;
////				const int MAILLE   = 3;
////				const int PLATE    = 4;
////			} TYPE;
////
////			struct _BASE {
////				enum {	NONE = -1,
////								STONESKIN = 0,
////								SKIN,
////								RINGMAIL,
////								RINGMAIL_LARGE,
////								SCALEMAIL_LEATHER,
////								SCALEMAIL_CLOTH,
////								SHINGLEMAIL,
////								MEDALLIONMAIL_LEATHER,
////								BRIGANDINE,
////								SPLINTED,
////								LEATHER,
////								CLOTH,
////								PADDED,
////								QUILTED,
////								SHARKSKIN,
////								PLATE,
////								LORICAT,
////								SILK,
////								MITHRIL,
////								FURR_MEDIUM,
////								FURR_THICK,
////								SCALES_MEDIUM,
////								SCALES_THICK,
////								SCALES_SOLID,
////								CRYGATE,
////								BALLHAT,
////								FIN_WROUGHT_MAILLE,
////								LAST};
////	//			string NAME[LAST];
////	//
////	//			_BASE() {
////	//				NAME[STONESKIN]				= "Stone Skin";
////	//				NAME[SKIN]					= "Skin";
////	//				NAME[RINGMAIL]				= "Ring Maille";
////	//				NAME[RINGMAIL_LARGE]		= "Ring Maille Large";
////	//				NAME[SCALEMAIL_LEATHER]		= "Leather backed Scale Maille";
////	//				NAME[SCALEMAIL_CLOTH]		= "Cloth backed Scale Maille";
////	//				NAME[SHINGLEMAIL]			= "Shingle Maille";
////	//				NAME[MEDALLIONMAIL_LEATHER] = "Leather backed Medallion Maille";
////	//				NAME[BRIGANDINE]			= "Brigandine";
////	//				NAME[SPLINTED]				= "Splinted";
////	//				NAME[LEATHER]				= "Leather";
////	//				NAME[CLOTH]					= "Cloth";
////	//				NAME[PADDED]				= "Padded";
////	//				NAME[QUILTED]				= "Quilted";
////	//				NAME[SHARKSKIN]				= "Shark Skin";
////	//				NAME[PLATE]					= "Plate";
////	//				NAME[LORICAT]				= "Loricat";
////	//				NAME[SILK]					= "Silk";
////	//				NAME[MITHRIL]				= "Mithril";
////	//				NAME[FURR_MEDIUM]			= "Medium Density Furr";
////	//				NAME[FURR_THICK]			= "High Density Furr";
////	//				NAME[SCALES_MEDIUM]			= "Medium Scales";
////	//				NAME[SCALES_THICK]			= "Thick Scales";
////	//				NAME[SCALES_SOLID]			= "Solid Scales";
////	//				NAME[CRYGATE]				= "Natural armor of the Crygate";
////	//				NAME[BALLHAT]				= "Ball Hat";
////	//				NAME[FIN_WROUGHT_MAILLE]	= "Finely Wrought Maille";
////	//			};
////			} BASE;
////
////			struct _RESISTANCE {
////				struct _WATER {
////					const int id		= 0;
////					std::string name	= "Water";
////					const int res[5]	= {	0,	0,	0,	0,	100	};
////					int operator()() { return id; }
////				} WATER;
////
////				struct _JELLO {
////					const int id = 1;
////					std::string name = "Jello";
////					const int res[5]	= {	0,	0,	0,	5,	95	};
////					int operator()() { return id; }
////				} JELLO;
////
////				struct _SKIN {
////					const int id = 2;
////					std::string name = "Skin";
////					const int res[5]	= {	0,	1,	6,	10,	83	};
////					int operator()() { return id; }
////				} SKIN;
////
////				struct _CLOTH {
////					const int id = 3;
////					std::string name = "Cloth";
////					const int res[5]	= {	0,	4,	13,	17,	66	};
////					int operator()() { return id; }
////				} CLOTH;
////
////				struct _PADDED {
////					const int id = 4;
////					std::string name = "Padded";
////					const int res[5]	= {	0,	10,	18,	21,	51	};
////					int operator()() { return id; }
////				} PADDED;
////
////				struct _LOWEST {
////					const int id = 5;
////					std::string name = "Lowest";
////					const int res[5]	= {	0,	16,	22,	24,	38	};
////					int operator()() { return id; }
////				} LOWEST;
////
////				struct _LOW {
////					const int id = 6;
////					std::string name = "Low";
////					const int res[5]	= {	0,	25,	25,	25,	25	};
////					int operator()() { return id; }
////				} LOW;
////
////				struct _MEDLOW {
////					const int id = 7;
////					std::string name = "Medium Low";
////					const int res[5]	= {	0,	35,	24,	23,	18	};
////					int operator()() { return id; }
////				} MEDLOW;
////
////				struct _MEDHIGH {
////					const int id = 8;
////					std::string name = "Medium High";
////					const int res[5]	= {	0,	46,	22,	21,	11	};
////					int operator()() { return id; }
////				} MEDHIGH;
////
////				struct _HIGH {
////					const int id = 9;
////					std::string name = "High";
////					const int res[5]	= {	0,	59,	19,	17,	5	};
////					int operator()() { return id; }
////				} HIGH;
////
////				struct _HIGHEST {
////					const int id = 10;
////					std::string name = "Highest";
////					const int res[5]	= {	0,	74,	14,	10,	2	};
////					int operator()() { return id; }
////				} HIGHEST;
////
////				struct _STONE {
////					const int id = 11;
////					std::string name = "Stone";
////					const int res[5]	= {	0,	100,	0,	0,	0	};
////					int operator()() { return id; }
////				} STONE;
////
////				struct _IMMUNE {
////					const int id = 12;
////					std::string name = "Immune";
////					const int res[5]	= {	100,	0,	0,	0,	0	};
////					int operator()() { return id; }
////				} IMMUNE;
////
////				struct _GOD {
////					const int id = 13;
////					std::string name = "God";
////					const int res[5]	= {	0,	0,	0,	0,	0	};
////					int operator()() { return id; }
////				} GOD;
////
////	//			const int WATER		= _WATER.id;
////	//			const int JELLO		= _JELLO.id;
////	//			const int SKIN		= _SKIN.id;
////	//			const int CLOTH		= _CLOTH.id;
////	//			const int PADDED	= _PADDED.id;
////	//			const int LOWEST	= _LOWEST.id;
////	//			const int LOW			= _LOW.id;
////	//			const int MEDLOW	= _MEDLOW.id;
////	//			const int MEDHIGH	= _MEDHIGH.id;
////	//			const int HIGH		= _HIGH.id;
////	//			const int HIGHEST	= _HIGHEST.id;
////	//			const int STONE		= _STONE.id;
////	//			const int IMMUNE	= _IMMUNE.id;
////	//			const int GOD			= _GOD.id;
////
////				const int * operator[](const int i) {
////					//const int * iR = nullptr;
////					if( i > 34 ) return GOD.res;
////					else {
////						switch (i) {
////							case 0: return WATER.res;			break;
////							case 1: return JELLO.res;			break;
////							case 2: return SKIN.res;				break;
////							case 3: return CLOTH.res;			break;
////							case 4: return PADDED.res;			break;
////							case 5: return LOWEST.res;		break;
////							case 6: return LOW.res;				break;
////							case 7: return MEDLOW.res;		break;
////							case 8: return MEDHIGH.res;		break;
////							case 9: return HIGH.res;			break;
////							case 10: return HIGHEST.res;		break;
////							case 11: return STONE.res;			break;
////							case 12: return IMMUNE.res;		break;
////							case 13: return GOD.res;				break;
////						}
////					}
////					return WATER.res;
////				}
////
////	//			const char * to_cstr(int i) {
////	//				std::string sR = "Null";
////	//				if( i > 34 ) sR = _GOD.name;
////	//				else {
////	//					switch (i) {
////	//						case 0: sR	= _WATER.name;		break;
////	//						case 1: sR	= _JELLO.name;		break;
////	//						case 3: sR	= _SKIN.name;			break;
////	//						case 6: sR	= _CLOTH.name;		break;
////	//						case 9: sR	= _PADDED.name;		break;
////	//						case 12: sR	= _LOWEST.name;		break;
////	//						case 15: sR	= _LOW.name;			break;
////	//						case 18: sR	= _MEDLOW.name;		break;
////	//						case 21: sR	= _MEDHIGH.name;	break;
////	//						case 24: sR	= _HIGH.name;			break;
////	//						case 27: sR	= _HIGHEST.name;	break;
////	//						case 32: sR	= _STONE.name;		break;
////	//						case 33: sR	= _IMMUNE.name;		break;
////	//						case 34: sR	= _GOD.name;			break;
////	//					}
////	//				}
////	//				return sR.c_str();
////	//			}
////
////				std::string to_str(int i) {
////					if( i > 34 ) return GOD.name;
////					else {
////						switch (i) {
////							case 0: return WATER.name;		break;
////							case 1: return JELLO.name;		break;
////							case 2: return SKIN.name;			break;
////							case 3: return CLOTH.name;		break;
////							case 4: return PADDED.name;		break;
////							case 5: return LOWEST.name;		break;
////							case 6: return LOW.name;			break;
////							case 7: return MEDLOW.name;		break;
////							case 8: return MEDHIGH.name;	break;
////							case 9: return HIGH.name;			break;
////							case 10: return HIGHEST.name;	break;
////							case 11: return STONE.name;		break;
////							case 12: return IMMUNE.name;		break;
////							case 13: return GOD.name;			break;
////						}
////					}
////					return "Null";
////				};
////
////	//			std::string &operator()(const int i) {
////	//				std::string sR = "Null";
////	//				if( i > 34 ) sR = GOD.name;
////	//				else {
////	//					switch (i) {
////	//						case 0: sR	= WATER.name;	break;
////	//						case 1: sR	= JELLO.name;	break;
////	//						case 3: sR	= SKIN.name;	break;
////	//						case 6: sR	= CLOTH.name;	break;
////	//						case 9: sR	= PADDED.name;	break;
////	//						case 12: sR	= LOWEST.name;	break;
////	//						case 15: sR	= LOW.name;		break;
////	//						case 18: sR	= MEDLOW.name;	break;
////	//						case 21: sR	= MEDHIGH.name;	break;
////	//						case 24: sR	= HIGH.name;	break;
////	//						case 27: sR	= HIGHEST.name;	break;
////	//						case 32: sR	= STONE.name;	break;
////	//						case 33: sR	= IMMUNE.name;	break;
////	//						case 34: sR	= GOD.name;		break;
////	//					}
////	//				}
////	//				return sR;
////	//			}
////
////			} RESISTANCE;
////
////		} ARMOR;
//
//		struct _MENU {
//			struct _STATE {
//				const int INIT			= iC++;
//				const int SKIP			= iC++;
//				const int INTENT		= iC++;
//
//				/*
//				 * THIS is a test item to try and get
//				 *  string values for menu options.
//				 *  Something like this WILL be needed
//				 *  eventually and this might be a good
//				 *  way to take care of this.
//				 *
//				 *  Another method would be to possibly
//				 *   use operator overloading and change
//				 *   all "const int"'s into structs that
//				 *   return the id value if this is
//				 *   possible.
//				 */
//				std::string to_str(int id) {
//					std::string s = "";
//					if(id == this->INIT)		s = "INIT";
//					else if(id == this->SKIP)	s = "SKIP";
//					else if(id == this->INTENT) s = "INTENT";
//					return s;
//				};
//			} STATE;
//
//			struct _MOVE {
//				const int INIT			= iC++;
//				const int RUN			= iC++;
//				const int WALK			= iC++;
//
//				struct _STANCE {
//					const int INIT		= iC++,
//							  STAND		= iC++,
//							  KNEEL		= iC++,
//							  SIT		= iC++,
//							  PRONE		= iC++;
//				} STANCE;
//			} MOVE;
//
//			struct _CAST {
//				const int INIT			= iC++;
//				const int SPELL			= iC++;
//				const int EXEC			= iC++;		//Execute spell
//
//				struct _MAGICAL {
//					const int INIT		= iC++,
//							  WAND		= iC++,
//							  STAFF		= iC++,
//							  IMBUE		= iC++;
//				} MAGICAL;
//
//				struct _ALCHEMY {
//					const int INIT		= iC++,
//							  TOSS		= iC++,
//							  CONSUME	= iC++,
//							  APPLY		= iC++;
//				} ALCHEMY;
//
//			} CAST;
//
//			struct _ENGAGE {
//				const int INIT			= iC++;
//
//				struct _CHOP {
//					const int INIT		= iC++,
//							  HIGH		= iC++,
//							  MID		= iC++,
//							  LOW		= iC++;
//				} CHOP;
//
//				struct _SWING {
//					const int INIT		= iC++,
//							  HIGH		= iC++,
//							  MID		= iC++,
//							  LOW		= iC++;
//				} SWING;
//
//				struct _THRUST {
//					const int INIT		= iC++,
//							  HIGH		= iC++,
//							  MID		= iC++,
//							  LOW		= iC++;
//				} THRUST;
//			} ENGAGE;
//
//			struct _DEFENSE {
//				const int INIT			= iC++,
//						  NONE			= iC++,
//						  DODGE			= iC++,
//						  DEFLECT		= iC++,
//						  BLOCK			= iC++;
//			} DEFENSE;
//
//			struct _INTENT {
//				const int INIT			= iC++,
//						  OBSERVE		= iC++,
//						  CONVERSE		= iC++,
//						  TOUCH			= iC++,
//						  LOITER		= iC++,
//						  SIT			= iC++,
//						  SLEEP			= iC++,
//						  MISSILE		= iC++,
//						  TOSS_NADE		= iC++,
//						  APPLY			= iC++,
//						  CONSUME		= iC++,
//						  CAST_SPELL	= iC++,
//						  CAST_STAFF	= iC++,
//						  CAST_WAND		= iC++,
//						  CAST_IMBUED	= iC++,
//						  WIELD			= iC++,
//						  THREATEN		= iC++,
//						  FIGHT			= iC++,
//						  CLIMB			= iC++,
//						  SPY			= iC++,
//						  PICKPOCKET	= iC++,
//						  NEGATE_LOCK	= iC++,
//						  POISON		= iC++,
//						  ASSASINATE	= iC++,
//
//						  MELEE			= iC++,
//						  STANCE		= iC++;
//			} INTENT;
//		} MENU;
//
//		//struct _MAGIC {
//			/*
//			 * Magic flags for specialty functions
//			 */
//			/*
//			struct _FLAGS {
//				enum FLAG_LIST {
//					NONE,
//					SUMMON_WEAPON,	//Unequip target weapon, create new weapon in inventory, equip new item, delete when spell ends
//					SUMMON_ARMOR,
//					SUMMON_ITEM,
//					DEATH,			//Causes death
//					CATACLYSMA,		//Causes 999,999 to appear above everyones head
//					TARGET,			//Sets a target, precast for another spell
//					DEATH_AT_END,	//When spell ends, the target dies, must have the target set (precast requirement)
//					ANGER			//Targets get angry, changes orientation of target (neutral->aggro)
//				};
//			} FLAGS;
//		} MAGIC;*/
//
//		struct _BATTLE {
//			struct _DAMAGE_TYPE {
//				enum LIST	{ 		BLADE=1,
//									BLUNT=2,
//									AXE=4,
//									SPEAR=8,
//									ARROW=16,
//									JAW=32,
//									HAND=64,
//									CLAW=128 };
//			} DAMAGE_TYPE;
//
//			struct _CRITICAL {
//				enum LIST	{ 		NONE=0,
//									ZERO=1,
//									ONE=2,
//									TWO=4,
//									THREE=8,
//									FOUR=16,
//									FIVE=32 };
//			} CRITICAL;
//
//			struct _HAND {
//				enum HAND_LIST	{ 	ONE_HANDED=1,
//									TWO_HANDED=2 };
//			} HAND;
//
//			struct _LIMB {
//				enum LIMB_LIST	{ 	HEAD=1,
//									TORSO=2,
//									ARM=4,
//									LEG=8,
//									LEFT=16,
//									RIGHT=32,
//									UPPER=64,
//									LOWER=128 };
//			} LIMB;
//		} BATTLE;
//
//		struct _Power_Source {
//			enum SOURCES { NONE, MANA, STAMINA, ELECTRIC, SOUL, LIGHTFORCE, FAITH, ELEMENT, BLOOD };
//		} SOURCE;
//
//		struct _Void {
//			enum VOIDS { NONE, VOID, DOME_LAKE, INK, SUN, HUGO_FOREST, QUICKSILVER, THE_CHAMBER, CYBOTRON };
//		} VOIDS;
//
//		struct _AILMENTS {
//			enum FLAG_LIST {
//				NONE,
//				// items/magic/armor/weapon
//				POISON,
//				CURE_POISON,
//				DISEASE,
//				CURE_DISEASE,
//				DEATH,
//
//				// MAGIC ONLY
//				SUMMON_WEAPON,	//Unequip target weapon, create new weapon in inventory, equip new item, delete when spell ends
//				SUMMON_ARMOR,
//				SUMMON_ITEM,
//				CATACLYSMA,		//Causes 999,999 to appear above everyones head
//				TARGET,			//Sets a target, precast for another spell
//				DEATH_AT_END,	//When spell ends, the target dies, must have the target set (precast requirement)
//				ANGER
//			};
//		} FLAGS;
//
//		struct _CARDS {
//			struct _ICON {
//				enum _ICON_LIST {
//					BASE,
//					BLADE,
//					BLUNT,
//					AXE,
//					SPEAR,
//					ARROW,
//					JAW,
//					CLAW,
//					MAGIC,
//					HAND,
//					ZERO,
//					ONE,
//					TWO,
//					THREE,
//					FOUR,
//					FIVE,
//					MULTI,
//					SIX,
//					ONE_LEFT_ARM_UPPER,
//					ONE_RIGHT_ARM_UPPER,
//					ONE_LEFT_LEG_LOWER,
//					ONE_RIGHT_LEG_LOWER,
//					ONE_TORSO,
//					ONE_HEAD,
//					DODGE,
//					HEALTHY,
//					ONE_LEFT_ARM_LOWER,
//					ONE_RIGHT_ARM_LOWER,
//					ONE_LEFT_LEG_UPPER,
//					ONE_RIGHT_LEG_UPPER,
//					TWO_TORSO,
//					TWO_HEAD,
//					BLOCK,
//					TWO_LEFT_ARM_UPPER,
//					TWO_RIGHT_ARM_UPPER,
//					TWO_LEFT_LEG_UPPER,
//					TWO_RIGHT_LEG_UPPER,
//					THREE_TORSO,
//					THREE_HEAD,
//					THREE_LEFT_ARM_UPPER,
//					DEFLECT,
//					THREE_RIGHT_ARM_UPPER,
//					THREE_LEFT_LEG_UPPER,
//					THREE_RIGHT_LEG_UPPER,
//					FOUR_TORSO,
//					FOUR_HEAD,
//					FOUR_LEFT_ARM_UPPER,
//					FOUR_RIGHT_ARM_UPPER,
//					GLANCE,
//					FOUR_LEFT_LEG_UPPER,
//					FOUR_RIGHT_LEG_UPPER,
//					TWO_LEFT_ARM_LOWER,
//					TWO_RIGHT_ARM_LOWER,
//					TWO_LEFT_LEG_LOWER,
//					TWO_RIGHT_LEG_LOWER,
//					THREE_LEFT_ARM_LOWER,
//					BLANK,
//					THREE_RIGHT_ARM_LOWER,
//					THREE_LEFT_LEG_LOWER,
//					THREE_RIGHT_LEG_LOWER,
//					FOUR_LEFT_ARM_LOWER,
//					FOUR_RIGHT_ARM_LOWER,
//					FOUR_LEFT_LEG_LOWER,
//					FOUR_RIGHT_LEG_LOWER,
//					LAST
//				};
//			} ICON;
//		} CARDS;
//	} ID;
//};
////
////enum STATE_CONST	{ S_JOURNAL=1, S_BATTLESCROLL=2, S_GRIMOIRE=3 };
////
////#endif /* GLOBAL_H_ */
