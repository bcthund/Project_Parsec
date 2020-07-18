/*
 * Colors.h
 *
 *  Created on: Sep 16, 2019
 *      Author: bcthund
 */

#ifndef HEADERS_CORE_COLORS_H_
#define HEADERS_CORE_COLORS_H_

#include <iostream>
#include "core_functions.h"

namespace Core {
	class _Colors {
		public:
			enum _ACTIVE_COLOR {
				COLOR_FRONT,
				COLOR_FRONT_HIGHLIGHT,
				COLOR_BACK,
				COLOR_BACK_HIGHLIGHT,
				COLOR_DETAIL1
			};

			enum _PALLETTE_COLOR {
				PAL_TEXT,
				PAL_TEXT_HIGHLIGHT,
				PAL_ICON,
				PAL_ICON_HIGHLIGHT,
				PAL_LAST
			};

		private:
			static const int PALETTE_SIZE = 32;

			_ACTIVE_COLOR eActiveColor;

			// Active color sent to shader
			Color		*vActiveColor;

			/*
			 * Color stacks
			 */
			Color		*vFrontColor,		// Color of text based items or sprites
						*vBackColor,		// Color of menu and window systems, also color of variables
						*vFrontHighlight,	// Highlight of text and sprites
						*vBackHighlight,	// Highlight of menus and windows
						*vDetail1Color;		// Varies, created for menu border color

			// Current stack colors
			int			uiFrontStack,
						uiBackStack,
						uiFrontHighlightStack,
						uiBackHighlightStack,
						uiDetail1Stack;

			Color * pallette;

			static const int STACK_SIZE = 16;


		public:
			_Colors();
			virtual ~_Colors();

//			std::vector<Color>	colors;
			std::vector<Color*>	colors;
			Map_si	map;

			int AddColor(std::string name, Color color);
			int AddColor(std::string name, float r, float g, float b, float a);
			int AddColor255(std::string name, int r, int g, int b, int a);
			Color & GetColor(std::string name);
			Color & GetColor(int id);
//			Color &operator[](int id)					{	return *colors[id];	}

			struct Colors_Extended {
				std::string Black = "Black";								//0.00, 0.00, 0.00
				std::string Eerie_black = "Eerie_black";								//0.11, 0.11, 0.11
				std::string Seal_brown = "Seal_brown";								//0.20, 0.08, 0.08
				std::string Dark_sienna = "Dark_sienna";								//0.24, 0.08, 0.08
				std::string Jet = "Jet";								//0.20, 0.20, 0.20
				std::string Blood_red = "Blood_red";								//0.40, 0.00, 0.00
				std::string Black_coffee = "Black_coffee";								//0.23, 0.18, 0.18
				std::string Maroon_web = "Maroon_web";								//0.50, 0.00, 0.00
				std::string Persian_plum = "Persian_plum";								//0.44, 0.11, 0.11
				std::string Prune = "Prune";								//0.44, 0.11, 0.11
				std::string Dark_red = "Dark_red";								//0.55, 0.00, 0.00
				std::string Falu_red = "Falu_red";								//0.50, 0.09, 0.09
				std::string Davys_grey = "Davys_grey";								//0.33, 0.33, 0.33
				std::string Tuscan_red = "Tuscan_red";								//0.49, 0.28, 0.28
				std::string Granite_gray = "Granite_gray";								//0.40, 0.40, 0.40
				std::string Carnelian = "Carnelian";								//0.70, 0.11, 0.11
				std::string Dim_gray = "Dim_gray";								//0.41, 0.41, 0.41
				std::string Auburn = "Auburn";								//0.65, 0.16, 0.16
				std::string Firebrick = "Firebrick";								//0.70, 0.13, 0.13
				std::string Rosso_corsa = "Rosso_corsa";								//0.83, 0.00, 0.00
				std::string Sonic_silver = "Sonic_silver";								//0.46, 0.46, 0.46
				std::string Rose_taupe = "Rose_taupe";								//0.56, 0.36, 0.36
				std::string Middle_red_purple = "Middle_red_purple";								//0.65, 0.33, 0.33
				std::string Maximum_red = "Maximum_red";								//0.85, 0.13, 0.13
				std::string Gray_web = "Gray_web";								//0.50, 0.50, 0.50
				std::string Copper_rose = "Copper_rose";								//0.60, 0.40, 0.40
				std::string Persian_red = "Persian_red";								//0.80, 0.20, 0.20
				std::string Red = "Red";								//1.00, 0.00, 0.00
				std::string Permanent_Geranium_Lake = "Permanent_Geranium_Lake";								//0.88, 0.17, 0.17
				std::string Indian_red = "Indian_red";								//0.80, 0.36, 0.36
				std::string Spanish_gray = "Spanish_gray";								//0.60, 0.60, 0.60
				std::string Quick_Silver = "Quick_Silver";								//0.65, 0.65, 0.65
				std::string Rosy_brown = "Rosy_brown";								//0.74, 0.56, 0.56
				std::string Silver_chalice = "Silver_chalice";								//0.67, 0.67, 0.67
				std::string Tuscany = "Tuscany";								//0.75, 0.60, 0.60
				std::string Light_coral = "Light_coral";								//0.94, 0.50, 0.50
				std::string Gray_X11 = "Gray_X11";								//0.75, 0.75, 0.75
				std::string Silver = "Silver";								//0.75, 0.75, 0.75
				std::string Light_gray = "Light_gray";								//0.83, 0.83, 0.83
				std::string Gainsboro = "Gainsboro";								//0.86, 0.86, 0.86
				std::string Baby_pink = "Baby_pink";								//0.96, 0.76, 0.76
				std::string Tea_rose = "Tea_rose";								//0.96, 0.76, 0.76
				std::string Cultured = "Cultured";								//0.96, 0.96, 0.96
				std::string Snow = "Snow";								//1.00, 0.98, 0.98
				std::string White = "White";								//1.00, 1.00, 1.00
				std::string Pastel_pink = "Pastel_pink";								//0.87, 0.65, 0.64
				std::string Spanish_pink = "Spanish_pink";								//0.97, 0.75, 0.75
				std::string Brandy = "Brandy";								//0.53, 0.25, 0.25
				std::string Candy_apple_red = "Candy_apple_red";								//1.00, 0.03, 0.00
				std::string Tart_Orange = "Tart_Orange";								//0.98, 0.30, 0.27
				std::string International_orange_engineering = "International_orange_engineering";								//0.73, 0.09, 0.05
				std::string Sweet_Brown = "Sweet_Brown";								//0.66, 0.22, 0.19
				std::string Deep_chestnut = "Deep_chestnut";								//0.73, 0.31, 0.28
				std::string Red_orange = "Red_orange";								//1.00, 0.33, 0.29
				std::string New_York_pink = "New_York_pink";								//0.84, 0.51, 0.50
				std::string Silver_pink = "Silver_pink";								//0.77, 0.68, 0.68
				std::string Barn_red = "Barn_red";								//0.49, 0.04, 0.01
				std::string Rose_ebony = "Rose_ebony";								//0.40, 0.28, 0.27
				std::string International_orange_GGB = "International_orange_GGB";								//0.75, 0.21, 0.17
				std::string CG_red = "CG_red";								//0.88, 0.24, 0.19
				std::string Orange_red_Crayola = "Orange_red_Crayola";								//1.00, 0.33, 0.29
				std::string Medium_carmine = "Medium_carmine";								//0.69, 0.25, 0.21
				std::string Red_RYB = "Red_RYB";								//1.00, 0.15, 0.07
				std::string Copper_penny = "Copper_penny";								//0.68, 0.44, 0.41
				std::string Cinnabar = "Cinnabar";								//0.89, 0.26, 0.20
				std::string Vermilion = "Vermilion";								//0.89, 0.26, 0.20
				std::string Congo_pink = "Congo_pink";								//0.97, 0.51, 0.47
				std::string Coral_pink = "Coral_pink";								//0.97, 0.51, 0.47
				std::string Tea_rose_orange = "Tea_rose_orange";								//0.97, 0.51, 0.47
				std::string Old_burgundy = "Old_burgundy";								//0.26, 0.19, 0.18
				std::string Redwood = "Redwood";								//0.64, 0.35, 0.32
				std::string Fire_opal = "Fire_opal";								//0.91, 0.36, 0.29
				std::string Bittersweet = "Bittersweet";								//1.00, 0.44, 0.37
				std::string Salmon = "Salmon";								//0.98, 0.50, 0.45
				std::string Misty_rose = "Misty_rose";								//1.00, 0.89, 0.88
				std::string Caput_mortuum = "Caput_mortuum";								//0.35, 0.15, 0.13
				std::string Rufous = "Rufous";								//0.66, 0.11, 0.03
				std::string Medium_vermilion = "Medium_vermilion";								//0.85, 0.22, 0.12
				std::string Scarlet = "Scarlet";								//1.00, 0.14, 0.00
				std::string Burnished_brown = "Burnished_brown";								//0.63, 0.48, 0.45
				std::string Cedar_Chest = "Cedar_Chest";								//0.79, 0.35, 0.29
				std::string Liver = "Liver";								//0.40, 0.30, 0.28
				std::string Burnt_umber = "Burnt_umber";								//0.54, 0.20, 0.14
				std::string Bole = "Bole";								//0.47, 0.27, 0.23
				std::string Tomato = "Tomato";								//1.00, 0.39, 0.28
				std::string Black_bean = "Black_bean";								//0.24, 0.05, 0.01
				std::string Chestnut = "Chestnut";								//0.58, 0.27, 0.21
				std::string Orange_soda = "Orange_soda";								//0.98, 0.36, 0.24
				std::string Terra_cotta = "Terra_cotta";								//0.89, 0.45, 0.36
				std::string Melon = "Melon";								//1.00, 0.73, 0.68
				std::string Chinese_red = "Chinese_red";								//0.67, 0.22, 0.12
				std::string Portland_Orange = "Portland_Orange";								//1.00, 0.35, 0.21
				std::string Dark_liver_horses = "Dark_liver_horses";								//0.33, 0.24, 0.22
				std::string Liver_organ = "Liver_organ";								//0.42, 0.18, 0.12
				std::string Kobe = "Kobe";								//0.53, 0.18, 0.09
				std::string Sienna = "Sienna";								//0.53, 0.18, 0.09
				std::string Blast_off_bronze = "Blast_off_bronze";								//0.65, 0.44, 0.39
				std::string Cinereous = "Cinereous";								//0.60, 0.51, 0.48
				std::string Outrageous_Orange = "Outrageous_Orange";								//1.00, 0.43, 0.29
				std::string Vivid_tangerine = "Vivid_tangerine";								//1.00, 0.63, 0.54
				std::string Coquelicot = "Coquelicot";								//1.00, 0.22, 0.00
				std::string Copper_red = "Copper_red";								//0.80, 0.43, 0.32
				std::string Burnt_sienna = "Burnt_sienna";								//0.91, 0.45, 0.32
				std::string Middle_red = "Middle_red";								//0.90, 0.56, 0.45
				std::string Dark_salmon = "Dark_salmon";								//0.91, 0.59, 0.48
				std::string Red_orange_CW = "Red_orange_CW";								//1.00, 0.27, 0.00
				std::string Coral = "Coral";								//1.00, 0.50, 0.31
				std::string Sinopia = "Sinopia";								//0.80, 0.25, 0.04
				std::string Flame = "Flame";								//0.89, 0.35, 0.13
				std::string Light_salmon = "Light_salmon";								//1.00, 0.63, 0.48
				std::string Rust = "Rust";								//0.72, 0.25, 0.05
				std::string Orange_Crayola = "Orange_Crayola";								//1.00, 0.46, 0.22
				std::string Mandarin = "Mandarin";								//0.95, 0.48, 0.28
				std::string Copper_Crayola = "Copper_Crayola";								//0.85, 0.54, 0.40
				std::string International_orange_aerospace = "International_orange_aerospace";								//1.00, 0.31, 0.00
				std::string Fuzzy_Wuzzy = "Fuzzy_Wuzzy";								//0.53, 0.26, 0.12
				std::string Mahogany = "Mahogany";								//0.75, 0.25, 0.00
				std::string Brown_sugar = "Brown_sugar";								//0.69, 0.43, 0.30
				std::string Orange_red = "Orange_red";								//1.00, 0.41, 0.12
				std::string Red_orange_Crayola = "Red_orange_Crayola";								//1.00, 0.41, 0.12
				std::string Mango_Tango = "Mango_Tango";								//1.00, 0.51, 0.26
				std::string Atomic_tangerine = "Atomic_tangerine";								//1.00, 0.60, 0.40
				std::string Umber = "Umber";								//0.39, 0.32, 0.28
				std::string Orange_Pantone = "Orange_Pantone";								//1.00, 0.35, 0.00
				std::string Pale_silver = "Pale_silver";								//0.79, 0.75, 0.73
				std::string Silver_Crayola = "Silver_Crayola";								//0.79, 0.75, 0.73
				std::string Persimmon = "Persimmon";								//0.93, 0.35, 0.00
				std::string Beaver = "Beaver";								//0.62, 0.51, 0.44
				std::string Antique_brass = "Antique_brass";								//0.80, 0.58, 0.46
				std::string Unbleached_silk = "Unbleached_silk";								//1.00, 0.87, 0.79
				std::string Bistre = "Bistre";								//0.24, 0.17, 0.12
				std::string Blaze_orange = "Blaze_orange";								//1.00, 0.40, 0.00
				std::string Pumpkin = "Pumpkin";								//1.00, 0.46, 0.09
				std::string Raw_sienna = "Raw_sienna";								//0.84, 0.54, 0.35
				std::string Tumbleweed = "Tumbleweed";								//0.87, 0.67, 0.53
				std::string Apricot = "Apricot";								//0.98, 0.81, 0.69
				std::string Van_Dyke_brown = "Van_Dyke_brown";								//0.40, 0.26, 0.16
				std::string Saddle_brown = "Saddle_brown";								//0.55, 0.27, 0.07
				std::string Coffee = "Coffee";								//0.44, 0.31, 0.22
				std::string Tuscan_brown = "Tuscan_brown";								//0.44, 0.31, 0.22
				std::string Burnt_orange = "Burnt_orange";								//0.80, 0.33, 0.00
				std::string Tawny = "Tawny";								//0.80, 0.34, 0.00
				std::string Spanish_orange = "Spanish_orange";								//0.91, 0.38, 0.00
				std::string Chocolate_web = "Chocolate_web";								//0.82, 0.41, 0.12
				std::string Cocoa_brown = "Cocoa_brown";								//0.82, 0.41, 0.12
				std::string Tan = "Tan";								//0.82, 0.71, 0.55
				std::string Desert_sand = "Desert_sand";								//0.93, 0.79, 0.69
				std::string Champagne_pink = "Champagne_pink";								//0.95, 0.87, 0.81
				std::string Seashell = "Seashell";								//1.00, 0.96, 0.93
				std::string Russet = "Russet";								//0.50, 0.27, 0.11
				std::string Cafe_au_lait = "Cafe_au_lait";								//0.65, 0.48, 0.36
				std::string French_beige = "French_beige";								//0.65, 0.48, 0.36
				std::string Tuscan_tan = "Tuscan_tan";								//0.65, 0.48, 0.36
				std::string Princeton_orange = "Princeton_orange";								//0.96, 0.50, 0.15
				std::string Persian_orange = "Persian_orange";								//0.85, 0.56, 0.35
				std::string Peach_Crayola = "Peach_Crayola";								//1.00, 0.80, 0.64
				std::string Dark_lava = "Dark_lava";								//0.28, 0.24, 0.20
				std::string Taupe = "Taupe";								//0.28, 0.24, 0.20
				std::string Alloy_orange = "Alloy_orange";								//0.77, 0.38, 0.06
				std::string Liver_chestnut = "Liver_chestnut";								//0.60, 0.45, 0.34
				std::string Macaroni_and_Cheese = "Macaroni_and_Cheese";								//1.00, 0.74, 0.53
				std::string Kobicha = "Kobicha";								//0.42, 0.27, 0.14
				std::string Safety_orange = "Safety_orange";								//1.00, 0.47, 0.00
				std::string Cadmium_orange = "Cadmium_orange";								//0.93, 0.53, 0.18
				std::string Sandy_brown = "Sandy_brown";								//0.96, 0.64, 0.38
				std::string Peach_puff = "Peach_puff";								//1.00, 0.85, 0.73
				std::string Liver_dogs = "Liver_dogs";								//0.72, 0.43, 0.16
				std::string Copper = "Copper";								//0.72, 0.45, 0.20
				std::string Heat_Wave = "Heat_Wave";								//1.00, 0.48, 0.00
				std::string Rajah = "Rajah";								//0.98, 0.67, 0.38
				std::string Smoky_black = "Smoky_black";								//0.06, 0.05, 0.03
				std::string Cafe_noir = "Cafe_noir";								//0.29, 0.21, 0.13
				std::string Dark_brown = "Dark_brown";								//0.40, 0.26, 0.13
				std::string Sepia = "Sepia";								//0.44, 0.26, 0.08
				std::string Windsor_tan = "Windsor_tan";								//0.65, 0.33, 0.01
				std::string Ochre = "Ochre";								//0.80, 0.47, 0.13
				std::string Bronze = "Bronze";								//0.80, 0.50, 0.20
				std::string Amber_SAE = "Amber_SAE";								//1.00, 0.49, 0.00
				std::string Orange = "Orange";								//1.00, 0.50, 0.00
				std::string Deep_saffron = "Deep_saffron";								//1.00, 0.60, 0.20
				std::string Fawn = "Fawn";								//0.90, 0.67, 0.44
				std::string Middle_yellow_red = "Middle_yellow_red";								//0.93, 0.69, 0.46
				std::string Mellow_apricot = "Mellow_apricot";								//0.97, 0.72, 0.47
				std::string Light_orange = "Light_orange";								//1.00, 0.85, 0.69
				std::string Almond = "Almond";								//0.94, 0.87, 0.80
				std::string Isabelline = "Isabelline";								//0.96, 0.94, 0.93
				std::string Linen = "Linen";								//0.98, 0.94, 0.90
				std::string Chocolate_traditional = "Chocolate_traditional";								//0.48, 0.25, 0.00
				std::string Neon_Carrot = "Neon_Carrot";								//1.00, 0.64, 0.26
				std::string Coyote_brown = "Coyote_brown";								//0.51, 0.38, 0.24
				std::string Pullman_Brown = "Pullman_Brown";								//0.39, 0.25, 0.09
				std::string Raw_umber = "Raw_umber";								//0.51, 0.40, 0.27
				std::string Tangerine = "Tangerine";								//0.95, 0.52, 0.00
				std::string Dark_orange = "Dark_orange";								//1.00, 0.55, 0.00
				std::string Middle_grey = "Middle_grey";								//0.55, 0.53, 0.50
				std::string Carrot_orange = "Carrot_orange";								//0.93, 0.57, 0.13
				std::string Camel = "Camel";								//0.76, 0.60, 0.42
				std::string Desert = "Desert";								//0.76, 0.60, 0.42
				std::string Fallow = "Fallow";								//0.76, 0.60, 0.42
				std::string Lion = "Lion";								//0.76, 0.60, 0.42
				std::string Wood_brown = "Wood_brown";								//0.76, 0.60, 0.42
				std::string Timberwolf = "Timberwolf";								//0.86, 0.84, 0.82
				std::string Bisque = "Bisque";								//1.00, 0.89, 0.77
				std::string French_bistre = "French_bistre";								//0.52, 0.43, 0.30
				std::string Grullo = "Grullo";								//0.66, 0.60, 0.53
				std::string Earth_yellow = "Earth_yellow";								//0.88, 0.66, 0.37
				std::string Yellow_Orange = "Yellow_Orange";								//1.00, 0.68, 0.26
				std::string Tan_Crayola = "Tan_Crayola";								//0.85, 0.60, 0.42
				std::string Burlywood = "Burlywood";								//0.87, 0.72, 0.53
				std::string Gold_Crayola = "Gold_Crayola";								//0.90, 0.75, 0.54
				std::string Antique_white = "Antique_white";								//0.98, 0.92, 0.84
				std::string Brown = "Brown";								//0.53, 0.33, 0.04
				std::string Fulvous = "Fulvous";								//0.89, 0.52, 0.00
				std::string Indian_yellow = "Indian_yellow";								//0.89, 0.66, 0.34
				std::string Deep_champagne = "Deep_champagne";								//0.98, 0.84, 0.65
				std::string Sunset = "Sunset";								//0.98, 0.84, 0.65
				std::string Tuscan = "Tuscan";								//0.98, 0.84, 0.65
				std::string Golden_brown = "Golden_brown";								//0.60, 0.40, 0.08
				std::string Yellow_Orange_CW = "Yellow_Orange_CW";								//1.00, 0.58, 0.02
				std::string Sunray = "Sunray";								//0.89, 0.67, 0.34
				std::string Navajo_white = "Navajo_white";								//1.00, 0.87, 0.68
				std::string Blanched_almond = "Blanched_almond";								//1.00, 0.92, 0.80
				std::string Shadow = "Shadow";								//0.54, 0.47, 0.36
				std::string Orange_peel = "Orange_peel";								//1.00, 0.62, 0.00
				std::string Bright_yellow_Crayola = "Bright_yellow_Crayola";								//1.00, 0.67, 0.11
				std::string Khaki_web = "Khaki_web";								//0.76, 0.69, 0.57
				std::string Champagne = "Champagne";								//0.97, 0.91, 0.81
				std::string Papaya_whip = "Papaya_whip";								//1.00, 0.94, 0.84
				std::string Light_French_beige = "Light_French_beige";								//0.78, 0.68, 0.50
				std::string Magnolia = "Magnolia";								//0.95, 0.91, 0.84
				std::string Gamboge = "Gamboge";								//0.89, 0.61, 0.06
				std::string Chrome_yellow = "Chrome_yellow";								//1.00, 0.65, 0.00
				std::string Orange_web = "Orange_web";								//1.00, 0.65, 0.00
				std::string Marigold = "Marigold";								//0.92, 0.64, 0.13
				std::string Wheat = "Wheat";								//0.96, 0.87, 0.70
				std::string Bone = "Bone";								//0.89, 0.85, 0.79
				std::string Peach = "Peach";								//1.00, 0.90, 0.71
				std::string Old_lace = "Old_lace";								//0.99, 0.96, 0.90
				std::string Harvest_gold = "Harvest_gold";								//0.85, 0.57, 0.00
				std::string Maximum_yellow_red = "Maximum_yellow_red";								//0.95, 0.73, 0.29
				std::string Platinum = "Platinum";								//0.90, 0.89, 0.89
				std::string Floral_white = "Floral_white";								//1.00, 0.98, 0.94
				std::string Metallic_Sunburst = "Metallic_Sunburst";								//0.61, 0.49, 0.22
				std::string Black_chocolate = "Black_chocolate";								//0.11, 0.09, 0.07
				std::string Field_drab = "Field_drab";								//0.42, 0.33, 0.12
				std::string Chinese_yellow = "Chinese_yellow";								//1.00, 0.70, 0.00
				std::string Dutch_white = "Dutch_white";								//0.94, 0.87, 0.73
				std::string Olive_Drab_7 = "Olive_Drab_7";								//0.24, 0.20, 0.12
				std::string Bistre_brown = "Bistre_brown";								//0.59, 0.44, 0.09
				std::string Drab = "Drab";								//0.59, 0.44, 0.09
				std::string Mode_beige = "Mode_beige";								//0.59, 0.44, 0.09
				std::string Sand_dune = "Sand_dune";								//0.59, 0.44, 0.09
				std::string Dark_goldenrod = "Dark_goldenrod";								//0.72, 0.53, 0.04
				std::string Gold_Fusion = "Gold_Fusion";								//0.52, 0.46, 0.31
				std::string Goldenrod = "Goldenrod";								//0.85, 0.65, 0.13
				std::string Satin_sheen_gold = "Satin_sheen_gold";								//0.80, 0.63, 0.21
				std::string Banana_Mania = "Banana_Mania";								//0.98, 0.91, 0.71
				std::string Cosmic_latte = "Cosmic_latte";								//1.00, 0.97, 0.91
				std::string Selective_yellow = "Selective_yellow";								//1.00, 0.73, 0.00
				std::string Orange_yellow = "Orange_yellow";								//0.96, 0.74, 0.12
				std::string Maize_Crayola = "Maize_Crayola";								//0.95, 0.78, 0.29
				std::string Lemon_curry = "Lemon_curry";								//0.80, 0.63, 0.11
				std::string Amber = "Amber";								//1.00, 0.75, 0.00
				std::string Mikado_yellow = "Mikado_yellow";								//1.00, 0.77, 0.05
				std::string Saffron = "Saffron";								//0.96, 0.77, 0.19
				std::string Sunglow = "Sunglow";								//1.00, 0.80, 0.20
				std::string Ecru = "Ecru";								//0.76, 0.70, 0.50
				std::string Sand = "Sand";								//0.76, 0.70, 0.50
				std::string Orange_yellow_Crayola = "Orange_yellow_Crayola";								//0.97, 0.84, 0.41
				std::string Gold = "Gold";								//0.65, 0.49, 0.00
				std::string Golden_poppy = "Golden_poppy";								//0.99, 0.76, 0.00
				std::string Mango = "Mango";								//0.99, 0.75, 0.01
				std::string Gold_metallic = "Gold_metallic";								//0.83, 0.69, 0.22
				std::string Metallic_gold = "Metallic_gold";								//0.83, 0.69, 0.22
				std::string Eggshell = "Eggshell";								//0.94, 0.92, 0.84
				std::string Mustard = "Mustard";								//1.00, 0.86, 0.35
				std::string Jasmine = "Jasmine";								//0.97, 0.87, 0.49
				std::string Mellow_yellow = "Mellow_yellow";								//0.97, 0.87, 0.49
				std::string Lemon_meringue = "Lemon_meringue";								//0.96, 0.92, 0.75
				std::string Naples_yellow = "Naples_yellow";								//0.98, 0.85, 0.37
				std::string Royal_yellow = "Royal_yellow";								//0.98, 0.85, 0.37
				std::string Stil_de_grain_yellow = "Stil_de_grain_yellow";								//0.98, 0.85, 0.37
				std::string Medium_champagne = "Medium_champagne";								//0.95, 0.90, 0.67
				std::string Vanilla = "Vanilla";								//0.95, 0.90, 0.67
				std::string Cornsilk = "Cornsilk";								//1.00, 0.97, 0.86
				std::string Old_gold = "Old_gold";								//0.81, 0.71, 0.23
				std::string Jonquil = "Jonquil";								//0.96, 0.79, 0.09
				std::string Buff = "Buff";								//0.94, 0.86, 0.51
				std::string Cyber_yellow = "Cyber_yellow";								//1.00, 0.83, 0.00
				std::string Yellow_NCS = "Yellow_NCS";								//1.00, 0.83, 0.00
				std::string Vegas_gold = "Vegas_gold";								//0.77, 0.70, 0.35
				std::string Flax = "Flax";								//0.93, 0.86, 0.51
				std::string Yellow_Crayola = "Yellow_Crayola";								//0.99, 0.91, 0.51
				std::string Blond = "Blond";								//0.98, 0.94, 0.75
				std::string Alabaster = "Alabaster";								//0.93, 0.92, 0.88
				std::string Yellow_Munsell = "Yellow_Munsell";								//0.94, 0.80, 0.00
				std::string Gold_web = "Gold_web";								//1.00, 0.84, 0.00
				std::string School_bus_yellow = "School_bus_yellow";								//1.00, 0.85, 0.00
				std::string Arylide_yellow = "Arylide_yellow";								//0.91, 0.84, 0.42
				std::string Hansa_yellow = "Hansa_yellow";								//0.91, 0.84, 0.42
				std::string Spanish_bistre = "Spanish_bistre";								//0.50, 0.46, 0.20
				std::string Golden_yellow = "Golden_yellow";								//1.00, 0.87, 0.00
				std::string Sizzling_Sunrise = "Sizzling_Sunrise";								//1.00, 0.86, 0.00
				std::string Minion_yellow = "Minion_yellow";								//0.96, 0.86, 0.31
				std::string Antique_bronze = "Antique_bronze";								//0.40, 0.36, 0.12
				std::string Safety_yellow = "Safety_yellow";								//0.93, 0.82, 0.01
				std::string Yellow_Pantone = "Yellow_Pantone";								//1.00, 0.87, 0.00
				std::string Citrine = "Citrine";								//0.89, 0.82, 0.04
				std::string Misty_moss = "Misty_moss";								//0.73, 0.71, 0.47
				std::string Straw = "Straw";								//0.89, 0.85, 0.44
				std::string Corn = "Corn";								//0.98, 0.93, 0.36
				std::string Maize = "Maize";								//0.98, 0.93, 0.36
				std::string Khaki_X11 = "Khaki_X11";								//0.94, 0.90, 0.55
				std::string Lemon_chiffon = "Lemon_chiffon";								//1.00, 0.98, 0.80
				std::string Middle_yellow = "Middle_yellow";								//1.00, 0.92, 0.00
				std::string Sage = "Sage";								//0.74, 0.72, 0.54
				std::string Green_yellow_Crayola = "Green_yellow_Crayola";								//0.94, 0.91, 0.57
				std::string Aureolin = "Aureolin";								//0.99, 0.93, 0.00
				std::string Canary_yellow = "Canary_yellow";								//1.00, 0.94, 0.00
				std::string Yellow_process = "Yellow_process";								//1.00, 0.94, 0.00
				std::string Dark_khaki = "Dark_khaki";								//0.74, 0.72, 0.42
				std::string Lemon_yellow = "Lemon_yellow";								//1.00, 0.96, 0.31
				std::string Cream = "Cream";								//1.00, 0.99, 0.82
				std::string Titanium_yellow = "Titanium_yellow";								//0.93, 0.90, 0.00
				std::string Cadmium_yellow = "Cadmium_yellow";								//1.00, 0.96, 0.00
				std::string Lemon = "Lemon";								//1.00, 0.97, 0.00
				std::string Yellow_Sunshine = "Yellow_Sunshine";								//1.00, 0.97, 0.00
				std::string Icterine = "Icterine";								//0.99, 0.97, 0.37
				std::string Olive_green = "Olive_green";								//0.71, 0.70, 0.36
				std::string Pale_spring_bud = "Pale_spring_bud";								//0.93, 0.92, 0.74
				std::string Spring_green_Crayola = "Spring_green_Crayola";								//0.93, 0.92, 0.74
				std::string Olive = "Olive";								//0.50, 0.50, 0.00
				std::string Xanthic = "Xanthic";								//0.93, 0.93, 0.04
				std::string Lemon_glacier = "Lemon_glacier";								//0.99, 1.00, 0.00
				std::string Yellow = "Yellow";								//1.00, 1.00, 0.00
				std::string Battleship_grey = "Battleship_grey";								//0.52, 0.52, 0.51
				std::string Old_silver = "Old_silver";								//0.52, 0.52, 0.51
				std::string Maximum_yellow = "Maximum_yellow";								//0.98, 0.98, 0.22
				std::string Yellow_RYB = "Yellow_RYB";								//1.00, 1.00, 0.20
				std::string Laser_lemon = "Laser_lemon";								//1.00, 1.00, 0.40
				std::string Unmellow_yellow = "Unmellow_yellow";								//1.00, 1.00, 0.40
				std::string Canary = "Canary";								//1.00, 1.00, 0.60
				std::string Lemon_yellow_Crayola = "Lemon_yellow_Crayola";								//1.00, 1.00, 0.62
				std::string Light_goldenrod_yellow = "Light_goldenrod_yellow";								//0.98, 0.98, 0.82
				std::string Beige = "Beige";								//0.96, 0.96, 0.86
				std::string Light_yellow = "Light_yellow";								//1.00, 1.00, 0.88
				std::string Ivory = "Ivory";								//1.00, 1.00, 0.94
				std::string Baby_powder = "Baby_powder";								//1.00, 1.00, 0.98
				std::string Citron = "Citron";								//0.62, 0.66, 0.12
				std::string Acid_green = "Acid_green";								//0.69, 0.75, 0.10
				std::string Maximum_green_yellow = "Maximum_green_yellow";								//0.85, 0.90, 0.31
				std::string Bitter_lemon = "Bitter_lemon";								//0.79, 0.88, 0.05
				std::string Pear = "Pear";								//0.82, 0.89, 0.19
				std::string Key_lime = "Key_lime";								//0.91, 0.96, 0.55
				std::string Chartreuse_traditional = "Chartreuse_traditional";								//0.87, 1.00, 0.00
				std::string Army_green = "Army_green";								//0.29, 0.33, 0.13
				std::string Black_olive = "Black_olive";								//0.23, 0.24, 0.21
				std::string Electric_lime = "Electric_lime";								//0.80, 1.00, 0.00
				std::string Volt = "Volt";								//0.80, 1.00, 0.00
				std::string Arctic_lime = "Arctic_lime";								//0.82, 1.00, 0.08
				std::string Middle_green_yellow = "Middle_green_yellow";								//0.67, 0.75, 0.38
				std::string Mindaro = "Mindaro";								//0.89, 0.98, 0.53
				std::string June_bud = "June_bud";								//0.74, 0.85, 0.34
				std::string Apple_green = "Apple_green";								//0.55, 0.71, 0.00
				std::string Android_green = "Android_green";								//0.64, 0.78, 0.22
				std::string Moss_green = "Moss_green";								//0.54, 0.60, 0.36
				std::string Turtle_green = "Turtle_green";								//0.54, 0.60, 0.36
				std::string Bitter_lime = "Bitter_lime";								//0.75, 1.00, 0.00
				std::string Lime_CW = "Lime_CW";								//0.75, 1.00, 0.00
				std::string Artichoke = "Artichoke";								//0.56, 0.59, 0.47
				std::string Yellow_green_Crayola = "Yellow_green_Crayola";								//0.77, 0.89, 0.52
				std::string Dark_moss_green = "Dark_moss_green";								//0.29, 0.36, 0.14
				std::string Olive_Drab_3 = "Olive_Drab_3";								//0.42, 0.56, 0.14
				std::string Sheen_green = "Sheen_green";								//0.56, 0.83, 0.00
				std::string Spring_bud = "Spring_bud";								//0.65, 0.99, 0.00
				std::string Yellow_green = "Yellow_green";								//0.60, 0.80, 0.20
				std::string Avocado = "Avocado";								//0.34, 0.51, 0.01
				std::string Dark_olive_green = "Dark_olive_green";								//0.33, 0.42, 0.18
				std::string Rifle_green = "Rifle_green";								//0.27, 0.30, 0.22
				std::string Green_Lizard = "Green_Lizard";								//0.65, 0.96, 0.20
				std::string Green_yellow = "Green_yellow";								//0.68, 1.00, 0.18
				std::string Inchworm = "Inchworm";								//0.70, 0.93, 0.36
				std::string Pine_tree = "Pine_tree";								//0.16, 0.18, 0.14
				std::string Olivine = "Olivine";								//0.60, 0.73, 0.45
				std::string French_lime = "French_lime";								//0.62, 0.99, 0.22
				std::string Maximum_green = "Maximum_green";								//0.37, 0.55, 0.19
				std::string Lawn_green = "Lawn_green";								//0.49, 0.99, 0.00
				std::string Chartreuse_web = "Chartreuse_web";								//0.50, 1.00, 0.00
				std::string Sap_green = "Sap_green";								//0.31, 0.49, 0.16
				std::string Asparagus = "Asparagus";								//0.53, 0.66, 0.42
				std::string Spring_Frost = "Spring_Frost";								//0.53, 1.00, 0.16
				std::string Green_RYB = "Green_RYB";								//0.40, 0.69, 0.20
				std::string Laurel_green = "Laurel_green";								//0.66, 0.73, 0.62
				std::string Bright_green = "Bright_green";								//0.40, 1.00, 0.00
				std::string Pistachio = "Pistachio";								//0.58, 0.77, 0.45
				std::string Ebony = "Ebony";								//0.33, 0.36, 0.31
				std::string Nyanza = "Nyanza";								//0.91, 1.00, 0.86
				std::string Tea_green = "Tea_green";								//0.82, 0.94, 0.75
				std::string Kelly_green = "Kelly_green";								//0.30, 0.73, 0.09
				std::string Bud_green = "Bud_green";								//0.48, 0.71, 0.38
				std::string Kombu_green = "Kombu_green";								//0.21, 0.26, 0.19
				std::string Harlequin = "Harlequin";								//0.25, 1.00, 0.00
				std::string Lincoln_green = "Lincoln_green";								//0.10, 0.35, 0.02
				std::string Fern_green = "Fern_green";								//0.31, 0.47, 0.26
				std::string Mantis = "Mantis";								//0.45, 0.76, 0.40
				std::string Slimy_green = "Slimy_green";								//0.16, 0.59, 0.09
				std::string Neon_green = "Neon_green";								//0.22, 1.00, 0.08
				std::string Yellow_green_CW = "Yellow_green_CW";								//0.19, 0.70, 0.10
				std::string May_green = "May_green";								//0.30, 0.57, 0.25
				std::string Granny_Smith_apple = "Granny_Smith_apple";								//0.66, 0.89, 0.63
				std::string India_green = "India_green";								//0.07, 0.53, 0.03
				std::string Dark_green_X11 = "Dark_green_X11";								//0.00, 0.39, 0.00
				std::string Pakistan_green = "Pakistan_green";								//0.00, 0.40, 0.00
				std::string Ao = "Ao";								//0.00, 0.50, 0.00
				std::string Green_web = "Green_web";								//0.00, 0.50, 0.00
				std::string Forest_green_web = "Forest_green_web";								//0.13, 0.55, 0.13
				std::string Nickel = "Nickel";								//0.45, 0.45, 0.45
				std::string Russian_green = "Russian_green";								//0.40, 0.57, 0.40
				std::string Lime_green = "Lime_green";								//0.20, 0.80, 0.20
				std::string Electric_green = "Electric_green";								//0.00, 1.00, 0.00
				std::string Green = "Green";								//0.00, 1.00, 0.00
				std::string Lime_web = "Lime_web";								//0.00, 1.00, 0.00
				std::string Dark_sea_green = "Dark_sea_green";								//0.56, 0.74, 0.56
				std::string Screamin_Green = "Screamin_Green";								//0.40, 1.00, 0.40
				std::string Light_green = "Light_green";								//0.56, 0.93, 0.56
				std::string Mint_green = "Mint_green";								//0.60, 1.00, 0.60
				std::string Honeydew = "Honeydew";								//0.94, 1.00, 0.94
				std::string Celadon = "Celadon";								//0.67, 0.88, 0.69
				std::string Hunter_green = "Hunter_green";								//0.21, 0.37, 0.23
				std::string Middle_green = "Middle_green";								//0.30, 0.55, 0.34
				std::string Eton_blue = "Eton_blue";								//0.59, 0.78, 0.64
				std::string Erin = "Erin";								//0.00, 1.00, 0.25
				std::string Ash_gray = "Ash_gray";								//0.70, 0.75, 0.71
				std::string Xanadu = "Xanadu";								//0.45, 0.53, 0.47
				std::string Dark_pastel_green = "Dark_pastel_green";								//0.01, 0.75, 0.24
				std::string Malachite = "Malachite";								//0.04, 0.85, 0.32
				std::string Forest_green_Crayola = "Forest_green_Crayola";								//0.37, 0.65, 0.47
				std::string Emerald = "Emerald";								//0.31, 0.78, 0.47
				std::string Paris_Green = "Paris_Green";								//0.31, 0.78, 0.47
				std::string Cambridge_blue = "Cambridge_blue";								//0.64, 0.76, 0.68
				std::string Shiny_Shamrock = "Shiny_Shamrock";								//0.37, 0.65, 0.47
				std::string Turquoise_green = "Turquoise_green";								//0.63, 0.84, 0.71
				std::string Feldgrau = "Feldgrau";								//0.30, 0.36, 0.33
				std::string Green_Pantone = "Green_Pantone";								//0.00, 0.68, 0.26
				std::string Sea_green = "Sea_green";								//0.18, 0.55, 0.34
				std::string Amazon = "Amazon";								//0.23, 0.48, 0.34
				std::string Medium_sea_green = "Medium_sea_green";								//0.24, 0.70, 0.44
				std::string Forest_green_traditional = "Forest_green_traditional";								//0.00, 0.27, 0.13
				std::string UP_Forest_green = "UP_Forest_green";								//0.00, 0.27, 0.13
				std::string Green_pigment = "Green_pigment";								//0.00, 0.65, 0.31
				std::string Dark_spring_green = "Dark_spring_green";								//0.09, 0.45, 0.27
				std::string Spring_green = "Spring_green";								//0.00, 1.00, 0.50
				std::string Mint_cream = "Mint_cream";								//0.96, 1.00, 0.98
				std::string Phthalo_green = "Phthalo_green";								//0.07, 0.21, 0.14
				std::string Aero_blue = "Aero_blue";								//0.75, 0.91, 0.84
				std::string Dartmouth_green = "Dartmouth_green";								//0.00, 0.44, 0.24
				std::string Spanish_green = "Spanish_green";								//0.00, 0.57, 0.31
				std::string Morning_blue = "Morning_blue";								//0.55, 0.64, 0.60
				std::string Magic_mint = "Magic_mint";								//0.67, 0.94, 0.82
				std::string British_racing_green = "British_racing_green";								//0.00, 0.26, 0.15
				std::string Cadmium_green = "Cadmium_green";								//0.00, 0.42, 0.24
				std::string Medium_aquamarine = "Medium_aquamarine";								//0.40, 0.87, 0.67
				std::string Shamrock_green = "Shamrock_green";								//0.00, 0.62, 0.38
				std::string GO_green = "GO_green";								//0.00, 0.67, 0.40
				std::string Medium_spring_green = "Medium_spring_green";								//0.00, 0.98, 0.60
				std::string Ocean_green = "Ocean_green";								//0.28, 0.75, 0.57
				std::string Dark_green = "Dark_green";								//0.00, 0.20, 0.13
				std::string Jade = "Jade";								//0.00, 0.66, 0.42
				std::string Green_Crayola = "Green_Crayola";								//0.11, 0.67, 0.47
				std::string Mint = "Mint";								//0.24, 0.71, 0.54
				std::string Sacramento_State_green = "Sacramento_State_green";								//0.02, 0.22, 0.15
				std::string Green_cyan = "Green_cyan";								//0.00, 0.60, 0.40
				std::string Green_NCS = "Green_NCS";								//0.00, 0.62, 0.42
				std::string Aquamarine = "Aquamarine";								//0.50, 1.00, 0.83
				std::string Viridian = "Viridian";								//0.25, 0.51, 0.43
				std::string Mountain_Meadow = "Mountain_Meadow";								//0.19, 0.73, 0.56
				std::string Dark_jungle_green = "Dark_jungle_green";								//0.10, 0.14, 0.13
				std::string Brunswick_green = "Brunswick_green";								//0.11, 0.30, 0.24
				std::string English_green = "English_green";								//0.11, 0.30, 0.24
				std::string Spanish_viridian = "Spanish_viridian";								//0.00, 0.50, 0.36
				std::string Green_Munsell = "Green_Munsell";								//0.00, 0.66, 0.47
				std::string Hookers_green = "Hookers_green";								//0.29, 0.47, 0.42
				std::string Jungle_green = "Jungle_green";								//0.16, 0.67, 0.53
				std::string Castleton_green = "Castleton_green";								//0.00, 0.34, 0.25
				std::string Bottle_green = "Bottle_green";								//0.00, 0.42, 0.31
				std::string Illuminating_emerald = "Illuminating_emerald";								//0.19, 0.57, 0.47
				std::string Opal = "Opal";								//0.66, 0.76, 0.74
				std::string Caribbean_green = "Caribbean_green";								//0.00, 0.80, 0.60
				std::string Zomp = "Zomp";								//0.22, 0.65, 0.56
				std::string Polished_Pine = "Polished_Pine";								//0.36, 0.64, 0.58
				std::string MSU_green = "MSU_green";								//0.09, 0.27, 0.23
				std::string Wintergreen_Dream = "Wintergreen_Dream";								//0.34, 0.53, 0.49
				std::string Blue_green_CW = "Blue_green_CW";								//0.02, 0.31, 0.25
				std::string Tropical_rainforest = "Tropical_rainforest";								//0.00, 0.46, 0.37
				std::string Generic_viridian = "Generic_viridian";								//0.00, 0.50, 0.40
				std::string Paolo_Veronese_green = "Paolo_Veronese_green";								//0.00, 0.61, 0.49
				std::string Sea_green_Crayola = "Sea_green_Crayola";								//0.00, 1.00, 0.80
				std::string Green_Sheen = "Green_Sheen";								//0.43, 0.68, 0.63
				std::string Middle_blue_green = "Middle_blue_green";								//0.55, 0.85, 0.80
				std::string Keppel = "Keppel";								//0.23, 0.69, 0.62
				std::string Persian_green = "Persian_green";								//0.00, 0.65, 0.58
				std::string Celadon_green = "Celadon_green";								//0.18, 0.52, 0.49
				std::string Turquoise = "Turquoise";								//0.25, 0.88, 0.82
				std::string Pine_green = "Pine_green";								//0.00, 0.47, 0.44
				std::string Myrtle_green = "Myrtle_green";								//0.19, 0.47, 0.45
				std::string Turquoise_blue = "Turquoise_blue";								//0.00, 1.00, 0.94
				std::string Light_sea_green = "Light_sea_green";								//0.13, 0.70, 0.67
				std::string Verdigris = "Verdigris";								//0.26, 0.70, 0.68
				std::string Deep_jungle_green = "Deep_jungle_green";								//0.00, 0.29, 0.29
				std::string Tiffany_Blue = "Tiffany_Blue";								//0.04, 0.73, 0.71
				std::string Fluorescent_blue = "Fluorescent_blue";								//0.08, 0.96, 0.93
				std::string Medium_turquoise = "Medium_turquoise";								//0.28, 0.82, 0.80
				std::string Rich_black = "Rich_black";								//0.00, 0.25, 0.25
				std::string Warm_black = "Warm_black";								//0.00, 0.26, 0.26
				std::string Charleston_green = "Charleston_green";								//0.14, 0.17, 0.17
				std::string Skobeloff = "Skobeloff";								//0.00, 0.45, 0.45
				std::string Dark_slate_gray = "Dark_slate_gray";								//0.18, 0.31, 0.31
				std::string Teal = "Teal";								//0.00, 0.50, 0.50
				std::string Dark_cyan = "Dark_cyan";								//0.00, 0.55, 0.55
				std::string Robin_egg_blue = "Robin_egg_blue";								//0.00, 0.80, 0.80
				std::string Maximum_blue_green = "Maximum_blue_green";								//0.19, 0.75, 0.75
				std::string Aqua = "Aqua";								//0.00, 1.00, 1.00
				std::string Cyan = "Cyan";								//0.00, 1.00, 1.00
				std::string Spanish_sky_blue = "Spanish_sky_blue";								//0.00, 1.00, 1.00
				std::string Celeste = "Celeste";								//0.70, 1.00, 1.00
				std::string Italian_sky_blue = "Italian_sky_blue";								//0.70, 1.00, 1.00
				std::string Light_cyan = "Light_cyan";								//0.88, 1.00, 1.00
				std::string Azure_X11 = "Azure_X11";								//0.94, 1.00, 1.00
				std::string Viridian_green = "Viridian_green";								//0.00, 0.59, 0.60
				std::string Dark_turquoise = "Dark_turquoise";								//0.00, 0.81, 0.82
				std::string Steel_Teal = "Steel_Teal";								//0.37, 0.54, 0.55
				std::string Cadet_blue = "Cadet_blue";								//0.37, 0.62, 0.63
				std::string Electric_blue = "Electric_blue";								//0.49, 0.98, 1.00
				std::string Metallic_Seaweed = "Metallic_Seaweed";								//0.04, 0.49, 0.55
				std::string Midnight_green = "Midnight_green";								//0.00, 0.29, 0.33
				std::string Powder_blue = "Powder_blue";								//0.69, 0.88, 0.90
				std::string Ming = "Ming";								//0.21, 0.45, 0.49
				std::string Blizzard_blue = "Blizzard_blue";								//0.67, 0.90, 0.93
				std::string Outer_space_Crayola = "Outer_space_Crayola";								//0.18, 0.22, 0.23
				std::string Blue_Munsell = "Blue_Munsell";								//0.00, 0.58, 0.69
				std::string Sky_blue_Crayola = "Sky_blue_Crayola";								//0.46, 0.84, 0.92
				std::string Middle_blue = "Middle_blue";								//0.49, 0.83, 0.90
				std::string Pacific_blue = "Pacific_blue";								//0.11, 0.66, 0.79
				std::string Blue_green = "Blue_green";								//0.05, 0.60, 0.73
				std::string Vivid_sky_blue = "Vivid_sky_blue";								//0.00, 0.80, 1.00
				std::string Cyan_process = "Cyan_process";								//0.00, 0.72, 0.92
				std::string Non_photo_blue = "Non_photo_blue";								//0.64, 0.87, 0.93
				std::string Deep_Space_Sparkle = "Deep_Space_Sparkle";								//0.29, 0.39, 0.42
				std::string Teal_blue = "Teal_blue";								//0.21, 0.46, 0.53
				std::string Cerulean_Crayola = "Cerulean_Crayola";								//0.11, 0.67, 0.84
				std::string Onyx = "Onyx";								//0.21, 0.22, 0.22
				std::string Capri = "Capri";								//0.00, 0.75, 1.00
				std::string Deep_sky_blue = "Deep_sky_blue";								//0.00, 0.75, 1.00
				std::string Maximum_blue = "Maximum_blue";								//0.28, 0.67, 0.80
				std::string Light_blue = "Light_blue";								//0.68, 0.85, 0.90
				std::string CG_blue = "CG_blue";								//0.00, 0.48, 0.65
				std::string Celadon_blue = "Celadon_blue";								//0.00, 0.48, 0.65
				std::string Cerulean = "Cerulean";								//0.00, 0.48, 0.65
				std::string Blue_sapphire = "Blue_sapphire";								//0.07, 0.38, 0.50
				std::string Blue_NCS = "Blue_NCS";								//0.00, 0.53, 0.74
				std::string Sky_blue = "Sky_blue";								//0.53, 0.81, 0.92
				std::string Cadet = "Cadet";								//0.33, 0.41, 0.45
				std::string Dark_sky_blue = "Dark_sky_blue";								//0.55, 0.75, 0.84
				std::string Baby_blue = "Baby_blue";								//0.54, 0.81, 0.94
				std::string Gunmetal = "Gunmetal";								//0.16, 0.20, 0.22
				std::string Star_command_blue = "Star_command_blue";								//0.00, 0.48, 0.72
				std::string Pewter_Blue = "Pewter_Blue";								//0.55, 0.66, 0.72
				std::string Silver_sand = "Silver_sand";								//0.75, 0.76, 0.76
				std::string Light_cornflower_blue = "Light_cornflower_blue";								//0.58, 0.80, 0.92
				std::string Columbia_Blue = "Columbia_Blue";								//0.73, 0.85, 0.92
				std::string Uranian_blue = "Uranian_blue";								//0.69, 0.86, 0.96
				std::string Indigo_dye = "Indigo_dye";								//0.00, 0.25, 0.42
				std::string Sapphire_blue = "Sapphire_blue";								//0.00, 0.40, 0.65
				std::string Honolulu_blue = "Honolulu_blue";								//0.00, 0.43, 0.69
				std::string Spanish_blue = "Spanish_blue";								//0.00, 0.44, 0.72
				std::string French_blue = "French_blue";								//0.00, 0.45, 0.73
				std::string Light_sky_blue = "Light_sky_blue";								//0.53, 0.81, 0.98
				std::string Charcoal = "Charcoal";								//0.21, 0.27, 0.31
				std::string Green_blue_Crayola = "Green_blue_Crayola";								//0.16, 0.53, 0.78
				std::string Carolina_blue = "Carolina_blue";								//0.34, 0.63, 0.83
				std::string Prussian_blue = "Prussian_blue";								//0.00, 0.19, 0.33
				std::string Air_superiority_blue = "Air_superiority_blue";								//0.45, 0.63, 0.76
				std::string Cadet_grey = "Cadet_grey";								//0.57, 0.64, 0.69
				std::string Maya_blue = "Maya_blue";								//0.45, 0.76, 0.98
				std::string Pale_cerulean = "Pale_cerulean";								//0.61, 0.77, 0.89
				std::string Dark_electric_blue = "Dark_electric_blue";								//0.33, 0.41, 0.47
				std::string Paynes_grey = "Paynes_grey";								//0.33, 0.41, 0.47
				std::string Blue_jeans = "Blue_jeans";								//0.36, 0.68, 0.93
				std::string Aero = "Aero";								//0.49, 0.73, 0.91
				std::string Beau_blue = "Beau_blue";								//0.74, 0.83, 0.90
				std::string Pale_aqua = "Pale_aqua";								//0.74, 0.83, 0.90
				std::string Rich_black_FOGRA29 = "Rich_black_FOGRA29";								//0.00, 0.04, 0.07
				std::string True_Blue = "True_Blue";								//0.00, 0.45, 0.81
				std::string Steel_blue = "Steel_blue";								//0.27, 0.51, 0.71
				std::string Iceberg = "Iceberg";								//0.44, 0.65, 0.82
				std::string Cerulean_frost = "Cerulean_frost";								//0.43, 0.61, 0.76
				std::string Alice_blue = "Alice_blue";								//0.94, 0.97, 1.00
				std::string USAFA_blue = "USAFA_blue";								//0.00, 0.31, 0.60
				std::string Black_coral = "Black_coral";								//0.33, 0.38, 0.44
				std::string Green_blue = "Green_blue";								//0.07, 0.39, 0.71
				std::string Baby_blue_eyes = "Baby_blue_eyes";								//0.63, 0.79, 0.95
				std::string Rich_black_FOGRA39 = "Rich_black_FOGRA39";								//0.00, 0.01, 0.01
				std::string Yale_Blue = "Yale_Blue";								//0.00, 0.21, 0.42
				std::string Lapis_lazuli = "Lapis_lazuli";								//0.15, 0.38, 0.61
				std::string Bright_navy_blue = "Bright_navy_blue";								//0.10, 0.45, 0.82
				std::string Navy_blue_Crayola = "Navy_blue_Crayola";								//0.10, 0.45, 0.82
				std::string Slate_gray = "Slate_gray";								//0.44, 0.50, 0.56
				std::string Azure = "Azure";								//0.00, 0.50, 1.00
				std::string Light_slate_gray = "Light_slate_gray";								//0.47, 0.53, 0.60
				std::string Bleu_de_France = "Bleu_de_France";								//0.19, 0.55, 0.91
				std::string Tufts_blue = "Tufts_blue";								//0.24, 0.56, 0.87
				std::string Dodger_blue = "Dodger_blue";								//0.12, 0.56, 1.00
				std::string Blue_gray = "Blue_gray";								//0.40, 0.60, 0.80
				std::string Livid = "Livid";								//0.40, 0.60, 0.80
				std::string Queen_blue = "Queen_blue";								//0.26, 0.42, 0.58
				std::string Oxford_blue = "Oxford_blue";								//0.00, 0.13, 0.28
				std::string Little_boy_blue = "Little_boy_blue";								//0.42, 0.63, 0.86
				std::string French_sky_blue = "French_sky_blue";								//0.47, 0.71, 1.00
				std::string Denim = "Denim";								//0.08, 0.38, 0.74
				std::string Shadow_blue = "Shadow_blue";								//0.47, 0.55, 0.65
				std::string Light_steel_blue = "Light_steel_blue";								//0.69, 0.77, 0.87
				std::string Cobalt_blue = "Cobalt_blue";								//0.00, 0.28, 0.67
				std::string Bdazzled_blue = "Bdazzled_blue";								//0.18, 0.35, 0.58
				std::string Sapphire_Crayola = "Sapphire_Crayola";								//0.18, 0.36, 0.63
				std::string Celtic_blue = "Celtic_blue";								//0.14, 0.42, 0.81
				std::string Sapphire = "Sapphire";								//0.06, 0.32, 0.73
				std::string Glaucous = "Glaucous";								//0.38, 0.51, 0.71
				std::string United_Nations_blue = "United_Nations_blue";								//0.36, 0.57, 0.90
				std::string Absolute_Zero = "Absolute_Zero";								//0.00, 0.28, 0.73
				std::string Blue_yonder = "Blue_yonder";								//0.31, 0.45, 0.65
				std::string Blue_Crayola = "Blue_Crayola";								//0.12, 0.46, 1.00
				std::string Royal_blue_dark = "Royal_blue_dark";								//0.00, 0.14, 0.40
				std::string YInMn_Blue = "YInMn_Blue";								//0.18, 0.31, 0.56
				std::string Cornflower_blue = "Cornflower_blue";								//0.39, 0.58, 0.93
				std::string Cadet_blue_Crayola = "Cadet_blue_Crayola";								//0.66, 0.70, 0.76
				std::string Roman_silver = "Roman_silver";								//0.51, 0.54, 0.59
				std::string UA_blue = "UA_blue";								//0.00, 0.20, 0.67
				std::string Dark_cornflower_blue = "Dark_cornflower_blue";								//0.15, 0.26, 0.55
				std::string Han_blue = "Han_blue";								//0.27, 0.42, 0.81
				std::string Periwinkle_Crayola = "Periwinkle_Crayola";								//0.76, 0.80, 0.90
				std::string Resolution_blue = "Resolution_blue";								//0.00, 0.14, 0.53
				std::string Cerulean_blue = "Cerulean_blue";								//0.16, 0.32, 0.75
				std::string Blue_RYB = "Blue_RYB";								//0.01, 0.28, 1.00
				std::string Bluetiful = "Bluetiful";								//0.24, 0.41, 0.91
				std::string Royal_blue_light = "Royal_blue_light";								//0.25, 0.41, 0.88
				std::string Space_cadet = "Space_cadet";								//0.11, 0.16, 0.32
				std::string Egyptian_blue = "Egyptian_blue";								//0.06, 0.20, 0.65
				std::string Wild_blue_yonder = "Wild_blue_yonder";								//0.64, 0.68, 0.82
				std::string Denim_blue = "Denim_blue";								//0.13, 0.26, 0.71
				std::string Ultramarine_blue = "Ultramarine_blue";								//0.25, 0.40, 0.96
				std::string Light_periwinkle = "Light_periwinkle";								//0.77, 0.80, 0.88
				std::string Persian_blue = "Persian_blue";								//0.11, 0.22, 0.73
				std::string Violet_blue = "Violet_blue";								//0.20, 0.29, 0.70
				std::string Cool_grey = "Cool_grey";								//0.55, 0.57, 0.67
				std::string Neon_blue = "Neon_blue";								//0.27, 0.40, 1.00
				std::string Blue_Pantone = "Blue_Pantone";								//0.00, 0.09, 0.66
				std::string Independence = "Independence";								//0.30, 0.32, 0.43
				std::string Manatee = "Manatee";								//0.59, 0.60, 0.67
				std::string Phthalo_blue = "Phthalo_blue";								//0.00, 0.06, 0.54
				std::string Zaffre = "Zaffre";								//0.00, 0.08, 0.66
				std::string St_Patricks_blue = "St_Patricks_blue";								//0.14, 0.16, 0.48
				std::string Purple_navy = "Purple_navy";								//0.31, 0.32, 0.50
				std::string Liberty = "Liberty";								//0.33, 0.35, 0.65
				std::string Navy_blue = "Navy_blue";								//0.00, 0.00, 0.50
				std::string Midnight_blue = "Midnight_blue";								//0.10, 0.10, 0.44
				std::string Duke_blue = "Duke_blue";								//0.00, 0.00, 0.61
				std::string Blue_pigment = "Blue_pigment";								//0.20, 0.20, 0.60
				std::string Medium_blue = "Medium_blue";								//0.00, 0.00, 0.80
				std::string Dark_blue_gray = "Dark_blue_gray";								//0.40, 0.40, 0.60
				std::string Blue = "Blue";								//0.00, 0.00, 1.00
				std::string Blue_bell = "Blue_bell";								//0.64, 0.64, 0.82
				std::string Maximum_blue_purple = "Maximum_blue_purple";								//0.67, 0.67, 0.90
				std::string Lavender_blue = "Lavender_blue";								//0.80, 0.80, 1.00
				std::string Periwinkle = "Periwinkle";								//0.80, 0.80, 1.00
				std::string Lavender_web = "Lavender_web";								//0.90, 0.90, 0.98
				std::string Ghost_white = "Ghost_white";								//0.97, 0.97, 1.00
				std::string Cosmic_cobalt = "Cosmic_cobalt";								//0.18, 0.18, 0.53
				std::string Rhythm = "Rhythm";								//0.47, 0.46, 0.59
				std::string Ultramarine = "Ultramarine";								//0.07, 0.04, 0.56
				std::string Picotee_blue = "Picotee_blue";								//0.18, 0.15, 0.53
				std::string Iris = "Iris";								//0.35, 0.31, 0.81
				std::string Lavender_gray = "Lavender_gray";								//0.77, 0.76, 0.82
				std::string Violet_blue_Crayola = "Violet_blue_Crayola";								//0.46, 0.43, 0.78
				std::string Ocean_Blue = "Ocean_Blue";								//0.31, 0.26, 0.71
				std::string Majorelle_blue = "Majorelle_blue";								//0.38, 0.31, 0.86
				std::string Trypan_Blue = "Trypan_Blue";								//0.11, 0.02, 0.70
				std::string Dark_slate_blue = "Dark_slate_blue";								//0.28, 0.24, 0.55
				std::string Slate_blue = "Slate_blue";								//0.42, 0.35, 0.80
				std::string Blue_violet_Crayola = "Blue_violet_Crayola";								//0.45, 0.40, 0.74
				std::string Medium_slate_blue = "Medium_slate_blue";								//0.48, 0.41, 0.93
				std::string Plump_Purple = "Plump_Purple";								//0.35, 0.27, 0.70
				std::string Han_purple = "Han_purple";								//0.32, 0.09, 0.98
				std::string Silver_Metallic = "Silver_Metallic";								//0.67, 0.66, 0.68
				std::string Persian_indigo = "Persian_indigo";								//0.20, 0.07, 0.48
				std::string Middle_blue_purple = "Middle_blue_purple";								//0.55, 0.45, 0.75
				std::string Medium_purple = "Medium_purple";								//0.58, 0.44, 0.86
				std::string Cyber_grape = "Cyber_grape";								//0.35, 0.26, 0.49
				std::string Spanish_violet = "Spanish_violet";								//0.30, 0.16, 0.51
				std::string Indigo = "Indigo";								//0.29, 0.00, 0.51
				std::string KSU_purple = "KSU_purple";								//0.31, 0.15, 0.51
				std::string Electric_indigo = "Electric_indigo";								//0.44, 0.00, 1.00
				std::string Royal_purple = "Royal_purple";								//0.47, 0.32, 0.66
				std::string Purple_mountain_majesty = "Purple_mountain_majesty";								//0.59, 0.47, 0.71
				std::string Russian_violet = "Russian_violet";								//0.20, 0.09, 0.30
				std::string Blue_violet_CW = "Blue_violet_CW";								//0.30, 0.10, 0.50
				std::string Rebecca_Purple = "Rebecca_Purple";								//0.40, 0.20, 0.60
				std::string Violet_CW = "Violet_CW";								//0.50, 0.00, 1.00
				std::string Amethyst = "Amethyst";								//0.60, 0.40, 0.80
				std::string Blue_violet = "Blue_violet";								//0.54, 0.17, 0.89
				std::string Electric_violet = "Electric_violet";								//0.56, 0.00, 1.00
				std::string Violet = "Violet";								//0.56, 0.00, 1.00
				std::string Purple = "Purple";								//0.38, 0.00, 0.50
				std::string Lavender_floral = "Lavender_floral";								//0.71, 0.49, 0.86
				std::string Mauve = "Mauve";								//0.88, 0.69, 1.00
				std::string Vivid_violet = "Vivid_violet";								//0.62, 0.00, 1.00
				std::string Purple_X11 = "Purple_X11";								//0.63, 0.13, 0.94
				std::string Veronica = "Veronica";								//0.63, 0.13, 0.94
				std::string Languid_lavender = "Languid_lavender";								//0.84, 0.79, 0.87
				std::string French_violet = "French_violet";								//0.53, 0.02, 0.81
				std::string Dark_orchid = "Dark_orchid";								//0.60, 0.20, 0.80
				std::string Wisteria = "Wisteria";								//0.79, 0.63, 0.86
				std::string Dark_violet = "Dark_violet";								//0.58, 0.00, 0.83
				std::string Eminence = "Eminence";								//0.42, 0.19, 0.51
				std::string Electric_purple = "Electric_purple";								//0.75, 0.00, 1.00
				std::string Purple_Plum = "Purple_Plum";								//0.61, 0.32, 0.71
				std::string Glossy_grape = "Glossy_grape";								//0.67, 0.57, 0.70
				std::string Bright_lilac = "Bright_lilac";								//0.85, 0.57, 0.94
				std::string Violet_RYB = "Violet_RYB";								//0.53, 0.00, 0.69
				std::string Heliotrope = "Heliotrope";								//0.87, 0.45, 1.00
				std::string Purple_Munsell = "Purple_Munsell";								//0.62, 0.00, 0.77
				std::string Purpureus = "Purpureus";								//0.60, 0.31, 0.68
				std::string Medium_orchid = "Medium_orchid";								//0.73, 0.33, 0.83
				std::string African_violet = "African_violet";								//0.70, 0.52, 0.75
				std::string English_violet = "English_violet";								//0.34, 0.24, 0.36
				std::string Maximum_purple = "Maximum_purple";								//0.45, 0.20, 0.50
				std::string French_lilac = "French_lilac";								//0.53, 0.38, 0.56
				std::string Pomp_and_Power = "Pomp_and_Power";								//0.53, 0.38, 0.56
				std::string Dark_purple = "Dark_purple";								//0.19, 0.10, 0.20
				std::string Phlox = "Phlox";								//0.87, 0.00, 1.00
				std::string Psychedelic_purple = "Psychedelic_purple";								//0.87, 0.00, 1.00
				std::string Chinese_violet = "Chinese_violet";								//0.52, 0.38, 0.53
				std::string Raisin_black = "Raisin_black";								//0.14, 0.13, 0.14
				std::string Patriarch = "Patriarch";								//0.50, 0.00, 0.50
				std::string Purple_web = "Purple_web";								//0.50, 0.00, 0.50
				std::string Dark_magenta = "Dark_magenta";								//0.55, 0.00, 0.55
				std::string Midnight = "Midnight";								//0.44, 0.15, 0.44
				std::string Steel_pink = "Steel_pink";								//0.80, 0.20, 0.80
				std::string Fuchsia = "Fuchsia";								//1.00, 0.00, 1.00
				std::string Magenta = "Magenta";								//1.00, 0.00, 1.00
				std::string Fuchsia_Crayola = "Fuchsia_Crayola";								//0.76, 0.33, 0.76
				std::string French_mauve = "French_mauve";								//0.83, 0.45, 0.83
				std::string Lilac = "Lilac";								//0.78, 0.64, 0.78
				std::string Violet_web = "Violet_web";								//0.93, 0.51, 0.93
				std::string Pink_flamingo = "Pink_flamingo";								//0.99, 0.45, 0.99
				std::string Shocking_pink_Crayola = "Shocking_pink_Crayola";								//1.00, 0.44, 1.00
				std::string Ultra_pink = "Ultra_pink";								//1.00, 0.44, 1.00
				std::string Plum_web = "Plum_web";								//0.87, 0.63, 0.87
				std::string Thistle = "Thistle";								//0.85, 0.75, 0.85
				std::string Pale_purple_Pantone = "Pale_purple_Pantone";								//0.98, 0.90, 0.98
				std::string Mardi_Gras = "Mardi_Gras";								//0.53, 0.00, 0.52
				std::string Orchid = "Orchid";								//0.85, 0.44, 0.84
				std::string Heliotrope_gray = "Heliotrope_gray";								//0.67, 0.60, 0.66
				std::string Rose_quartz = "Rose_quartz";								//0.67, 0.60, 0.66
				std::string Old_lavender = "Old_lavender";								//0.47, 0.41, 0.47
				std::string Japanese_violet = "Japanese_violet";								//0.36, 0.20, 0.34
				std::string Plum = "Plum";								//0.56, 0.27, 0.52
				std::string Palatinate_purple = "Palatinate_purple";								//0.41, 0.16, 0.38
				std::string Razzmic_Berry = "Razzmic_Berry";								//0.55, 0.31, 0.52
				std::string Byzantium = "Byzantium";								//0.44, 0.16, 0.39
				std::string Byzantine = "Byzantine";								//0.74, 0.20, 0.64
				std::string Lilac_Luster = "Lilac_Luster";								//0.68, 0.60, 0.67
				std::string Pink_lavender = "Pink_lavender";								//0.85, 0.70, 0.82
				std::string Purple_pizzazz = "Purple_pizzazz";								//1.00, 0.31, 0.85
				std::string Hot_magenta = "Hot_magenta";								//1.00, 0.11, 0.81
				std::string Orchid_Crayola = "Orchid_Crayola";								//0.89, 0.61, 0.82
				std::string Dark_byzantium = "Dark_byzantium";								//0.36, 0.22, 0.33
				std::string Shocking_pink = "Shocking_pink";								//0.99, 0.06, 0.75
				std::string Razzle_dazzle_rose = "Razzle_dazzle_rose";								//1.00, 0.20, 0.80
				std::string Violet_Crayola = "Violet_Crayola";								//0.59, 0.24, 0.50
				std::string Antique_fuchsia = "Antique_fuchsia";								//0.57, 0.36, 0.51
				std::string Pearly_purple = "Pearly_purple";								//0.72, 0.41, 0.64
				std::string Opera_mauve = "Opera_mauve";								//0.72, 0.52, 0.65
				std::string Pink_lace = "Pink_lace";								//1.00, 0.87, 0.96
				std::string Flirt = "Flirt";								//0.64, 0.00, 0.43
				std::string Fandango = "Fandango";								//0.71, 0.20, 0.54
				std::string Fashion_fuchsia = "Fashion_fuchsia";								//0.96, 0.00, 0.63
				std::string Hollywood_cerise = "Hollywood_cerise";								//0.96, 0.00, 0.63
				std::string Taupe_gray = "Taupe_gray";								//0.55, 0.52, 0.54
				std::string Sky_magenta = "Sky_magenta";								//0.81, 0.44, 0.69
				std::string Rose_pink = "Rose_pink";								//1.00, 0.40, 0.80
				std::string Medium_violet_red = "Medium_violet_red";								//0.78, 0.08, 0.52
				std::string Red_violet = "Red_violet";								//0.78, 0.08, 0.52
				std::string Frostbite = "Frostbite";								//0.91, 0.21, 0.65
				std::string Mountbatten_pink = "Mountbatten_pink";								//0.60, 0.48, 0.55
				std::string Mulberry_Crayola = "Mulberry_Crayola";								//0.78, 0.31, 0.61
				std::string Super_pink = "Super_pink";								//0.81, 0.42, 0.66
				std::string Red_violet_Crayola = "Red_violet_Crayola";								//0.75, 0.27, 0.56
				std::string Tyrian_purple = "Tyrian_purple";								//0.40, 0.01, 0.24
				std::string Sugar_Plum = "Sugar_Plum";								//0.57, 0.31, 0.46
				std::string Maximum_red_purple = "Maximum_red_purple";								//0.65, 0.23, 0.47
				std::string Middle_purple = "Middle_purple";								//0.85, 0.51, 0.71
				std::string Magenta_process = "Magenta_process";								//1.00, 0.00, 0.56
				std::string Persian_rose = "Persian_rose";								//1.00, 0.16, 0.64
				std::string Magenta_haze = "Magenta_haze";								//0.62, 0.27, 0.46
				std::string Mexican_pink = "Mexican_pink";								//0.89, 0.00, 0.49
				std::string Barbie_Pink = "Barbie_Pink";								//0.85, 0.09, 0.52
				std::string Jazzberry_jam = "Jazzberry_jam";								//0.65, 0.04, 0.37
				std::string Amaranth_MP = "Amaranth_MP";								//0.62, 0.17, 0.41
				std::string Red_purple = "Red_purple";								//0.89, 0.00, 0.47
				std::string Magenta_dye = "Magenta_dye";								//0.79, 0.12, 0.48
				std::string Mulberry = "Mulberry";								//0.77, 0.29, 0.55
				std::string Deep_pink = "Deep_pink";								//1.00, 0.08, 0.58
				std::string Pink_Pantone = "Pink_Pantone";								//0.84, 0.28, 0.58
				std::string Pansy_purple = "Pansy_purple";								//0.47, 0.09, 0.29
				std::string Eggplant = "Eggplant";								//0.38, 0.25, 0.32
				std::string Twilight_lavender = "Twilight_lavender";								//0.54, 0.29, 0.42
				std::string Mystic_maroon = "Mystic_maroon";								//0.68, 0.26, 0.47
				std::string Smitten = "Smitten";								//0.78, 0.25, 0.53
				std::string Wild_Strawberry = "Wild_Strawberry";								//1.00, 0.26, 0.64
				std::string Magenta_Crayola = "Magenta_Crayola";								//0.96, 0.33, 0.65
				std::string Persian_pink = "Persian_pink";								//0.97, 0.50, 0.75
				std::string Kobi = "Kobi";								//0.91, 0.62, 0.77
				std::string Dark_liver = "Dark_liver";								//0.33, 0.29, 0.31
				std::string Rose = "Rose";								//1.00, 0.00, 0.50
				std::string Deep_cerise = "Deep_cerise";								//0.85, 0.20, 0.53
				std::string Rose_bonbon = "Rose_bonbon";								//0.98, 0.26, 0.62
				std::string Wild_orchid = "Wild_orchid";								//0.83, 0.44, 0.64
				std::string Hot_pink = "Hot_pink";								//1.00, 0.41, 0.71
				std::string Winter_Sky = "Winter_Sky";								//1.00, 0.00, 0.49
				std::string Brilliant_rose = "Brilliant_rose";								//1.00, 0.33, 0.64
				std::string Fuchsia_purple = "Fuchsia_purple";								//0.80, 0.22, 0.48
				std::string China_pink = "China_pink";								//0.87, 0.44, 0.63
				std::string Liseran_purple = "Liseran_purple";								//0.87, 0.44, 0.63
				std::string Thulian_pink = "Thulian_pink";								//0.87, 0.44, 0.63
				std::string Telemagenta = "Telemagenta";								//0.81, 0.20, 0.46
				std::string Magenta_Pantone = "Magenta_Pantone";								//0.82, 0.25, 0.49
				std::string French_fuchsia = "French_fuchsia";								//0.99, 0.25, 0.57
				std::string Cotton_candy = "Cotton_candy";								//1.00, 0.74, 0.85
				std::string Rubine_red = "Rubine_red";								//0.82, 0.00, 0.34
				std::string Dogwood_rose = "Dogwood_rose";								//0.84, 0.09, 0.41
				std::string Old_mauve = "Old_mauve";								//0.40, 0.19, 0.28
				std::string Wine_dregs = "Wine_dregs";								//0.40, 0.19, 0.28
				std::string Violet_red = "Violet_red";								//0.97, 0.33, 0.58
				std::string Carnation_pink = "Carnation_pink";								//1.00, 0.65, 0.79
				std::string Queen_pink = "Queen_pink";								//0.91, 0.80, 0.84
				std::string Mimi_pink = "Mimi_pink";								//1.00, 0.85, 0.91
				std::string Ruby = "Ruby";								//0.88, 0.07, 0.37
				std::string Raspberry = "Raspberry";								//0.89, 0.04, 0.36
				std::string Fuchsia_rose = "Fuchsia_rose";								//0.78, 0.26, 0.46
				std::string Quinacridone_magenta = "Quinacridone_magenta";								//0.56, 0.23, 0.35
				std::string Pictorial_carmine = "Pictorial_carmine";								//0.76, 0.04, 0.31
				std::string Maroon_X11 = "Maroon_X11";								//0.69, 0.19, 0.38
				std::string Irresistible = "Irresistible";								//0.70, 0.27, 0.42
				std::string Raspberry_rose = "Raspberry_rose";								//0.70, 0.27, 0.42
				std::string Razzmatazz = "Razzmatazz";								//0.89, 0.15, 0.42
				std::string Mystic = "Mystic";								//0.84, 0.32, 0.51
				std::string Fandango_pink = "Fandango_pink";								//0.87, 0.32, 0.52
				std::string English_lavender = "English_lavender";								//0.71, 0.51, 0.58
				std::string French_rose = "French_rose";								//0.96, 0.29, 0.54
				std::string Cyclamen = "Cyclamen";								//0.96, 0.44, 0.63
				std::string Amaranth_pink = "Amaranth_pink";								//0.95, 0.61, 0.73
				std::string UA_red = "UA_red";								//0.85, 0.00, 0.30
				std::string Ruber = "Ruber";								//0.81, 0.27, 0.46
				std::string French_pink = "French_pink";								//0.99, 0.42, 0.62
				std::string Nadeshiko_pink = "Nadeshiko_pink";								//0.96, 0.68, 0.78
				std::string Spanish_carmine = "Spanish_carmine";								//0.82, 0.00, 0.28
				std::string Rose_red = "Rose_red";								//0.76, 0.12, 0.34
				std::string China_rose = "China_rose";								//0.66, 0.32, 0.43
				std::string Charm_pink = "Charm_pink";								//0.90, 0.56, 0.67
				std::string Cameo_pink = "Cameo_pink";								//0.94, 0.73, 0.80
				std::string Lavender_blush = "Lavender_blush";								//1.00, 0.94, 0.96
				std::string Amaranth_purple = "Amaranth_purple";								//0.67, 0.15, 0.31
				std::string Carmine_MP = "Carmine_MP";								//0.84, 0.00, 0.25
				std::string Blush = "Blush";								//0.87, 0.36, 0.51
				std::string Tickle_Me_Pink = "Tickle_Me_Pink";								//0.99, 0.54, 0.67
				std::string Orchid_pink = "Orchid_pink";								//0.95, 0.74, 0.80
				std::string Claret = "Claret";								//0.50, 0.09, 0.20
				std::string Mauve_taupe = "Mauve_taupe";								//0.57, 0.37, 0.43
				std::string Raspberry_glace = "Raspberry_glace";								//0.57, 0.37, 0.43
				std::string Cerise = "Cerise";								//0.87, 0.19, 0.39
				std::string Cinnamon_Satin = "Cinnamon_Satin";								//0.80, 0.38, 0.49
				std::string Piggy_pink = "Piggy_pink";								//0.99, 0.87, 0.90
				std::string Rose_Dust = "Rose_Dust";								//0.62, 0.37, 0.44
				std::string Vanilla_ice = "Vanilla_ice";								//0.95, 0.56, 0.66
				std::string Baker_Miller_pink = "Baker_Miller_pink";								//1.00, 0.57, 0.69
				std::string Schauss_pink = "Schauss_pink";								//1.00, 0.57, 0.69
				std::string Burgundy = "Burgundy";								//0.50, 0.00, 0.13
				std::string Oxblood = "Oxblood";								//0.50, 0.00, 0.13
				std::string Big_dip_o_ruby = "Big_dip_o_ruby";								//0.61, 0.15, 0.26
				std::string Red_NCS = "Red_NCS";								//0.77, 0.01, 0.20
				std::string Red_Munsell = "Red_Munsell";								//0.95, 0.00, 0.24
				std::string Puce = "Puce";								//0.80, 0.53, 0.60
				std::string Bright_maroon = "Bright_maroon";								//0.76, 0.13, 0.28
				std::string Maroon_Crayola = "Maroon_Crayola";								//0.76, 0.13, 0.28
				std::string Pink_Sherbet = "Pink_Sherbet";								//0.97, 0.56, 0.65
				std::string Red_Crayola = "Red_Crayola";								//0.93, 0.13, 0.30
				std::string Paradise_pink = "Paradise_pink";								//0.90, 0.24, 0.38
				std::string Catawba = "Catawba";								//0.44, 0.21, 0.26
				std::string Crimson = "Crimson";								//0.86, 0.08, 0.24
				std::string Amaranth = "Amaranth";								//0.90, 0.17, 0.31
				std::string Radical_Red = "Radical_Red";								//1.00, 0.21, 0.37
				std::string Brink_pink = "Brink_pink";								//0.98, 0.38, 0.50
				std::string Mauvelous = "Mauvelous";								//0.94, 0.60, 0.67
				std::string Cherry_blossom_pink = "Cherry_blossom_pink";								//1.00, 0.72, 0.77
				std::string Crimson_UA = "Crimson_UA";								//0.62, 0.11, 0.20
				std::string Vivid_burgundy = "Vivid_burgundy";								//0.62, 0.11, 0.21
				std::string French_raspberry = "French_raspberry";								//0.78, 0.17, 0.28
				std::string Neon_fuchsia = "Neon_fuchsia";								//1.00, 0.25, 0.39
				std::string Shimmering_Blush = "Shimmering_Blush";								//0.85, 0.53, 0.58
				std::string Black_Shadows = "Black_Shadows";								//0.75, 0.69, 0.70
				std::string Carmine = "Carmine";								//0.59, 0.00, 0.09
				std::string Antique_ruby = "Antique_ruby";								//0.52, 0.11, 0.18
				std::string Red_violet_CW = "Red_violet_CW";								//0.57, 0.17, 0.24
				std::string Cardinal = "Cardinal";								//0.77, 0.12, 0.23
				std::string Medium_candy_apple_red = "Medium_candy_apple_red";								//0.89, 0.02, 0.17
				std::string Spanish_red = "Spanish_red";								//0.90, 0.00, 0.15
				std::string Popstar = "Popstar";								//0.75, 0.31, 0.38
				std::string Fiery_rose = "Fiery_rose";								//1.00, 0.33, 0.44
				std::string Ultra_red = "Ultra_red";								//0.99, 0.42, 0.52
				std::string Wild_watermelon = "Wild_watermelon";								//0.99, 0.42, 0.52
				std::string Salmon_pink = "Salmon_pink";								//1.00, 0.57, 0.64
				std::string Pink = "Pink";								//1.00, 0.75, 0.80
				std::string Cadmium_red = "Cadmium_red";								//0.89, 0.00, 0.13
				std::string Sizzling_Red = "Sizzling_Red";								//1.00, 0.22, 0.33
				std::string Light_pink = "Light_pink";								//1.00, 0.71, 0.76
				std::string Solid_pink = "Solid_pink";								//0.54, 0.22, 0.26
				std::string Rusty_red = "Rusty_red";								//0.85, 0.17, 0.26
				std::string Brick_red = "Brick_red";								//0.80, 0.25, 0.33
				std::string Rosewood = "Rosewood";								//0.40, 0.00, 0.04
				std::string Wine = "Wine";								//0.45, 0.18, 0.22
				std::string Ruby_red = "Ruby_red";								//0.61, 0.07, 0.12
				std::string Pale_pink = "Pale_pink";								//0.98, 0.85, 0.87
				std::string Cordovan = "Cordovan";								//0.54, 0.25, 0.27
				std::string Japanese_carmine = "Japanese_carmine";								//0.62, 0.16, 0.20
				std::string Lava = "Lava";								//0.81, 0.06, 0.13
				std::string Rocket_metallic = "Rocket_metallic";								//0.54, 0.50, 0.50
				std::string Rose_madder = "Rose_madder";								//0.89, 0.15, 0.21
				std::string Imperial_red = "Imperial_red";								//0.93, 0.16, 0.22
				std::string Red_Pantone = "Red_Pantone";								//0.93, 0.16, 0.22
				std::string Red_Salsa = "Red_Salsa";								//0.99, 0.23, 0.29
				std::string Candy_pink = "Candy_pink";								//0.89, 0.44, 0.48
				std::string Tango_pink = "Tango_pink";								//0.89, 0.44, 0.48
				std::string Upsdell_red = "Upsdell_red";								//0.68, 0.13, 0.16
				std::string Venetian_red = "Venetian_red";								//0.78, 0.03, 0.08
				std::string Deep_taupe = "Deep_taupe";								//0.49, 0.37, 0.38
				std::string English_red = "English_red";								//0.67, 0.29, 0.32
				std::string Amaranth_red = "Amaranth_red";								//0.83, 0.13, 0.18
				std::string Fire_engine_red = "Fire_engine_red";								//0.81, 0.13, 0.16
				std::string Rose_vale = "Rose_vale";								//0.67, 0.31, 0.32
				std::string Red_pigment = "Red_pigment";								//0.93, 0.11, 0.14
				std::string English_vermillion = "English_vermillion";								//0.80, 0.28, 0.29
				std::string UP_maroon = "UP_maroon";								//0.48, 0.07, 0.07
				std::string Madder_Lake = "Madder_Lake";								//0.80, 0.20, 0.21
				std::string Bittersweet_shimmer = "Bittersweet_shimmer";								//0.75, 0.31, 0.32
				std::string Old_rose = "Old_rose";								//0.75, 0.50, 0.51
				std::string OU_Crimson_red = "OU_Crimson_red";								//0.52, 0.09, 0.09


				std::string Gray10;								// 10, 10, 10
				std::string Gray20;								// 20, 20, 20
				std::string Gray30;								// 30, 30, 30
				std::string Gray40;								// 40, 40, 40
				std::string Gray50;								// 50, 50, 50
				std::string Gray60;								// 60, 60, 60
				std::string Gray70;								// 70, 70, 70
				std::string Gray80;								// 80, 80, 80
				std::string Gray90;								// 90, 90, 90

				std::string Transparent;
			} Extended;

			Colors_Extended &operator()()				{	return this->Extended;	}
			Color &operator[](std::string name)			{	if(map.count(name)>0) return *colors[map[name]]; else throw std::runtime_error("Invalid Color: "+name);	}

			// FIXME: Create a pallette class (or modify pallette implementation here) (currently implemented into gameVars)
			Color GetPallette(_PALLETTE_COLOR e);

			// Primary object color, font color
//			void SetFront(Vector3f color, float alpha);
			void SetFront(Color color);
//			void PushFront(Vector3f color, float alpha);
			void PushFront(Color color);
			void PushFront(std::string name);
			void PushFront();
			void PopFront();
			Color GetFront();

			// Font background color, etc?
//			void SetBack(Vector3f color, float alpha);
			void SetBack(Color color);
//			void PushBack(Vector3f color, float alpha);
			void PushBack(Color color);
			void PushBack();
			void PopBack();
			Color GetBack();

			// Highlight on mouseover color
//			void SetFrontHighlight(Vector3f color, float alpha);
			void SetFrontHighlight(Color color);
//			void PushFrontHighlight(Vector3f color, float alpha);
			void PushFrontHighlight(Color color);
			void PushFrontHighlight();
			void PopFrontHighlight();
			Color GetFrontHighlight();

//			void SetBackHighlight(Vector3f color, float alpha);
			void SetBackHighlight(Color color);
//			void PushBackHighlight(Vector3f color, float alpha);
			void PushBackHighlight(Color color);
			void PushBackHighlight();
			void PopBackHighlight();
			Color GetBackHighlight();

			// Font background color, etc?
//			void SetDetail1(Vector3f color, float alpha);
			void SetDetail1(Color color);
//			void PushDetail1(Vector3f color, float alpha);
			void PushDetail1(Color color);
			void PushDetail1();
			void PopDetail1();
			Color GetDetail1();

			void SetActive(_ACTIVE_COLOR e);
//			Color GetActiveColor();
//			void Set(Vector3f color, float alpha);
//			void Set(Color color);
//			void Push(Vector3f color, float alpha);
//			void Push(Color color);
//			void Push();
//			void Pop();
			Color GetActive();



	};

} /* namespace Core */

#endif /* HEADERS_CORE_COLORS_H_ */




















































