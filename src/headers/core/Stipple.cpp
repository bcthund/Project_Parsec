/*
 * Stipple.cpp
 *
 *  Created on: Apr 20, 2020
 *      Author: bcthund
 */

#include "Stipple.h"

namespace Core {

	const std::string Stipple::STIPPLE_NONE			= "None";			// 0
	const std::string Stipple::STIPPLE_ANSI31		= "Ansi 31";		// 1
	const std::string Stipple::STIPPLE_ANGLE_THICK	= "Angle Thick";	// 2
	const std::string Stipple::STIPPLE_ANGLE		= "Angle";			// 3
	const std::string Stipple::STIPPLE_BLOCKS		= "Blocks";			// 4
	const std::string Stipple::STIPPLE_CHECKERBOARD	= "Checkerboard";	// 5
	const std::string Stipple::STIPPLE_SAND			= "Sand";			// 6
	const std::string Stipple::STIPPLE_INSULATION	= "Insulation";		// 7
	const std::string Stipple::STIPPLE_BOARD		= "Board";			// 8
	const std::string Stipple::STIPPLE_ZIGZAG		= "Zigzag";			// 9
	const std::string Stipple::STIPPLE_WATER		= "Water";			// 10
	const std::string Stipple::STIPPLE_GRASS		= "Grass";			// 11
	const std::string Stipple::STIPPLE_CHECKER		= "Checker";		// 12
	const std::string Stipple::STIPPLE_OCTAGONS		= "Octagons";		// 13
	const std::string Stipple::STIPPLE_WAFFLE		= "Waffle";			// 14
	const std::string Stipple::STIPPLE_PLUSSES		= "Plusses";		// 15
	const std::string Stipple::STIPPLE_SHAKES		= "Shakes";			// 16
	const std::string Stipple::STIPPLE_EARTH		= "Earth";			// 17
	const std::string Stipple::STIPPLE_HERRING		= "Herring";		// 18
	const std::string Stipple::STIPPLE_DOTS			= "Dots";			// 19
	const std::string Stipple::STIPPLE_GROUT		= "Grout";			// 20
	const std::string Stipple::STIPPLE_CROSSES		= "Crosses";		// 21
	const std::string Stipple::STIPPLE_TILEPAT1		= "Tile Pattern 1";	// 22
	const std::string Stipple::STIPPLE_WOOD			= "Wood";			// 23
	const std::string Stipple::STIPPLE_GRADIENT_V	= "Gradient V";		// 24
	const std::string Stipple::STIPPLE_GRADIENT_H	= "Gradient H";		// 25
	const std::string Stipple::STIPPLE_SHADE_125	= "Shade 125";		// 26
	const std::string Stipple::STIPPLE_SHADE_25		= "Shade 25";		// 27
	const std::string Stipple::STIPPLE_SHADE_50		= "Shade 50";		// 28
	const std::string Stipple::STIPPLE_SHADE_75		= "Shade 75";		// 29
	const std::string Stipple::STIPPLE_SHINGLE		= "Shingle";		// 30
	const std::string Stipple::STIPPLE_TILE_OFFSET	= "Tile Offset";	// 31
	const std::string Stipple::STIPPLE_FENCE		= "Fence";			// 32

	const std::string Stipple::STIPPLE_SHALE		= "Shale";			// 33
	const std::string Stipple::STIPPLE_SANDSTONE	= "Sandstone";		// 34
	const std::string Stipple::STIPPLE_SLOT			= "Slot";			// 35
	const std::string Stipple::STIPPLE_LIMESTONE	= "Limestone";		// 36
	const std::string Stipple::STIPPLE_SALT			= "Salt";			// 37
	const std::string Stipple::STIPPLE_PUMICE		= "Pumice";			// 38


	Stipple::Stipple() {
		stipples.setSource("Stipple");

		{
			int stipple[] = {	0	};

			add(STIPPLE_NONE, Vector2i(1, 1), stipple);
		}

		{
			int stipple[] = {	0,0,0,0,0,0,0,1,
								0,0,0,0,0,0,1,0,
								0,0,0,0,0,1,0,0,
								0,0,0,0,1,0,0,0,
								0,0,0,1,0,0,0,0,
								0,0,1,0,0,0,0,0,
								0,1,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0 };

			add(STIPPLE_ANSI31, Vector2i(8, 8), stipple);
		}

		{
			int stipple[] = {	1,1,0,0,0,0,0,0,
								1,1,0,0,0,0,0,0,
								1,1,0,0,0,0,0,0,
								1,1,0,0,0,0,0,0,
								1,1,1,1,1,1,0,0,
								1,1,1,1,1,1,0,0,
								0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0 };

			add(STIPPLE_ANGLE_THICK, Vector2i(8, 8), stipple);
		}

		{
			int stipple[] = {	1,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,
								1,1,1,1,1,1,1,0,
								0,0,0,0,0,0,0,0 };

			add(STIPPLE_ANGLE, Vector2i(8, 8), stipple);
		}

		{
			int stipple[] = {	0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
								1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
								0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
								1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
								0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 };

			add(STIPPLE_BLOCKS, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
								1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
								1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
								1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
								1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
								1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
								1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
								1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,
								0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,
								0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,
								0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,
								0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,
								0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,
								0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,
								0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1 };

			add(STIPPLE_CHECKERBOARD, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 };

			add(STIPPLE_SAND, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,
								0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,
								0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,
								0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
								0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,
								0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,
								0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
								1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
								0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,
								0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,
								0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
								0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,
								0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,
								0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0 };

			add(STIPPLE_INSULATION, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
								1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0 };

			add(STIPPLE_BOARD, Vector2i(32, 8), stipple);
		}

		{
			int stipple[] = {	0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,
								0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
								1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

			add(STIPPLE_ZIGZAG, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,
								0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,
								0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,
								0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,
								0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,
								0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
								0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,
								1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

			add(STIPPLE_WATER, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,
								0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,
								0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
								0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,
								0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,
								0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0 };

			add(STIPPLE_GRASS, Vector2i(16, 16), stipple);
		}

		{
//			int stipple[] = {	0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//								0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
//								0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,
//								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 };

			int stipple[] = {	0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0 };

			add(STIPPLE_CHECKER, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,
								0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,
								0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,
								0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,
								1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,
								0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,
								0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,
								0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,
								0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0 };

			add(STIPPLE_OCTAGONS, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
								0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
								0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
								0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
								0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
								0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
								0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
								0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
								0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
								0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
								0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
								0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
								0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
								0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

			add(STIPPLE_WAFFLE, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
								0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
								0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
								0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,
								0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

			add(STIPPLE_PLUSSES, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,
								0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,
								1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,
								1,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,
								1,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,
								1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,
								1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,
								1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,
								1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,
								1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,
								1,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,
								1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,
								0,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,
								0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,
								0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,
								0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0 };

			add(STIPPLE_SHAKES, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,
								0,1,0,1,1,1,1,1,1,1,0,1,0,0,1,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,1,0,1,0,0,1,0,0,1,0,1,1,1,1,1,
								0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,
								0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,
								1,1,0,1,0,0,1,0,0,1,0,1,1,1,1,1,
								0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,
								0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,
								1,1,0,1,0,0,1,0,0,1,0,1,1,1,1,1,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,1,0,1,1,1,1,1,1,1,0,1,0,0,1,0,
								0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,
								0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0,
								0,1,0,1,1,1,1,1,1,1,0,1,0,0,1,0,
								0,1,0,0,0,0,0,0,0,0,0,1,0,0,1,0 };

			add(STIPPLE_EARTH, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
								0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,
								0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,
								0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,
								0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
								0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,
								0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,
								0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,
								1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
								0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,
								0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,
								0,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0,
								0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
								0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,0,
								0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,
								0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1 };

			add(STIPPLE_HERRING, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,1,0,0,0,0,0,0,0,1,0,0,0,1,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
								0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
								0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
								0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0 };

			add(STIPPLE_DOTS, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,1,0,0,1,0,0,0,0,1,1,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

			add(STIPPLE_GROUT, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,
								0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,
								0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,
								0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,
								0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

			add(STIPPLE_CROSSES, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
								0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
								1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,
								0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,
								0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
								0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,
								1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
								0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,
								0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,1,
								0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,
								1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1 };

			add(STIPPLE_TILEPAT1, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	0,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,
								0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,
								1,1,1,0,0,0,0,0,0,0,0,0,1,0,0,0,
								0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,0,
								0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,
								1,1,0,0,0,0,0,0,0,0,1,1,1,0,0,0,
								0,0,1,1,1,0,0,0,0,1,0,0,0,0,0,0,
								0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,0,
								0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,
								1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,
								0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,
								1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,
								0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,
								0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,
								0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1 };

			add(STIPPLE_WOOD, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	0,0,1,0,1,1,0,1,0,1,1,0,1,0,0,1,
								0,0,0,1,0,1,1,1,1,1,0,1,0,0,0,0,
								0,1,0,0,1,0,1,1,1,0,1,0,0,1,0,0,
								0,0,0,1,0,1,1,1,1,1,0,1,0,0,0,0,
								0,0,1,0,1,1,0,1,0,1,1,0,1,0,0,0,
								0,0,0,1,0,1,1,1,1,1,0,1,0,0,0,0,
								0,1,0,0,1,0,1,1,1,0,1,0,0,1,0,0,
								0,0,0,1,0,1,1,1,1,1,0,1,0,0,0,0,
								0,0,1,0,1,1,0,1,0,1,1,0,1,0,0,1,
								0,0,0,1,0,1,1,1,1,1,0,1,0,0,0,0,
								0,1,0,0,1,0,1,1,1,0,1,0,0,1,0,0,
								0,0,0,1,0,1,1,1,1,1,0,1,0,0,0,0,
								0,0,1,0,1,1,0,1,0,1,1,0,1,0,0,0,
								0,0,0,1,0,1,1,1,1,1,0,1,0,0,0,0,
								0,1,0,0,1,0,1,1,1,0,1,0,0,1,0,0,
								0,0,0,1,0,1,1,1,1,1,0,1,0,0,0,0 };

			add(STIPPLE_GRADIENT_V, Vector2i(16, 16), stipple);
		}

				{
			int stipple[] = {	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,
								1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,
								0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
								1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,
								0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,
								1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
								0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,
								1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,
								1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
								1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,
								0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0 };

			add(STIPPLE_GRADIENT_H, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

			add(STIPPLE_SHADE_125, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

			add(STIPPLE_SHADE_25, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
								1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
								1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
								1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
								1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
								1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
								1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
								1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1 };

			add(STIPPLE_SHADE_50, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
								0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
								1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
								1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
								0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
								1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
								1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
								0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
								1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
								1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
								1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
								0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
								1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };

			add(STIPPLE_SHADE_75, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,
								0,1,0,0,0,0,0,1,0,1,0,0,0,0,0,1,
								0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,0,
								0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
								0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
								0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
								0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
								0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
								0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,
								0,0,0,1,0,1,0,0,0,0,0,1,0,1,0,0,
								1,1,1,0,0,0,1,1,1,1,1,0,0,0,1,1 };

			add(STIPPLE_SHINGLE, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
								1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,
								1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,
								1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,
								1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,
								1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,
								1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,
								1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,
								1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
								1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
								1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,
								1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0 };

			add(STIPPLE_TILE_OFFSET, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	0,1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,
								0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,
								0,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,
								0,1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,
								0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
								0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0, //
								0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0, //
								0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,
								0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,
								0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,
								0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,
								0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,
								1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
								0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0 };

			add(STIPPLE_FENCE, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

			add(STIPPLE_SHALE, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

			add(STIPPLE_SANDSTONE, Vector2i(32, 8), stipple);
		}

		{
			int stipple[] = {	1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
								1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,
								1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,
								1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,
								1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,
								1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,
								1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

			add(STIPPLE_SLOT, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
								1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,
								1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,
								0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,1,0,0,0,1,0,0,1,0,0,1,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0 };

			add(STIPPLE_LIMESTONE, Vector2i(32, 8), stipple);
		}

		{
			int stipple[] = {	1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
								1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
								1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,
								1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,
								1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,
								0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,
								0,0,0,0,0,0,0,0,1,0,1,0,1,0,0,0,
								0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,0,
								0,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

			add(STIPPLE_SALT, Vector2i(16, 16), stipple);
		}

		{
			int stipple[] = {	0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
								1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,
								0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,
								0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,
								0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,
								0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,
								0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

			add(STIPPLE_PUMICE, Vector2i(16, 16), stipple);
		}

//		{
//			int stipple[] = {	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//								0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
//
//			add(STIPPLE_, Vector2i(16, 16), stipple);
//		}

	}

	Stipple::~Stipple() {
		for(auto stipple : stipples) {
			delete stipple;
		}
	}

	void Stipple::add(std::string name, Vector2i size, int pattern[]) {
		Stipple_Pattern *con = new Stipple_Pattern(name, size, pattern);
		//stipples.push_back(con);
		//uint id = stipples.size()-1;
		//map.insert(make_pair(name, id));
		stipples.add(name, con);
	}

//	void Stipple::setScale(std::string name, float *scale) {
//		uint stippleID = mapStipple[name];
//		if(stipples[stippleID].bLocalScale) delete stipples[stippleID].scale;
//		stipples[stippleID].bLocalScale = false;
//		stipples[stippleID].scale = scale;
//	}

//	void Stipple::setColor(std::string name, Color *color) {
//		uint stippleID = mapStipple[name];
//		stipples[stippleID].color = color;
//	}

	void Stipple::shiftUp(std::string name, int n) {
		// FIXME: implement shift up
//		uint stippleID = mapStipple[name];
//		stipples[stippleID].color = color;
	}

	void Stipple::shiftDown(std::string name, int n) {
		// FIXME: implement shift down
//		uint stippleID = mapStipple[name];
//		stipples[stippleID].color = color;
	}

	void Stipple::shiftLeft(std::string name, int n) {
		// FIXME: implement shift left
//		uint stippleID = mapStipple[name];
//		stipples[stippleID].color = color;
	}

	void Stipple::shiftRight(std::string name, int n) {
		// FIXME: implement shift right
//		uint stippleID = mapStipple[name];
//		stipples[stippleID].color = color;
	}

	Stipple_Pattern * Stipple::get(std::string name) {
		return stipples[name];
	}

	Stipple_Pattern * Stipple::get(int id) {
		if(id<stipples.size())	return stipples[id];
		else return stipples[0];
	}

} /* namespace Core */




























































