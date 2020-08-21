/*
 * Colors.cpp
 *
 *  Created on: Sep 16, 2019
 *      Author: bcthund
 */

#include <cmath>
#include "core_functions.h"
#include "Colors.h"

namespace Core {

//	Color &_Colors::operator[](std::string name) {
//		return colors[map[name]];
//	}

	_Colors::_Colors() {
		colors.setSource("Colors");

//		vFrontColorMem		= new Color[STACK_SIZE];
//		vBackColorMem		= new Color[STACK_SIZE];
//		vFrontHighlightMem	= new Color[STACK_SIZE];
//		vBackHighlightMem	= new Color[STACK_SIZE];

		vFrontColor		= new Color[STACK_SIZE];
		vBackColor		= new Color[STACK_SIZE];
		vFrontHighlight	= new Color[STACK_SIZE];
		vBackHighlight	= new Color[STACK_SIZE];
		vDetail1Color	= new Color[STACK_SIZE];

		uiFrontStack			= 0;
		uiBackStack				= 0;
		uiFrontHighlightStack	= 0;
		uiBackHighlightStack	= 0;
		uiDetail1Stack			= 0;

		pallette = new Color[PALETTE_SIZE];
		pallette[PAL_TEXT]				= Color(1.0f, 1.0f, 1.0f, 1.0f);		// Default text color
		pallette[PAL_TEXT_HIGHLIGHT]	= Color(1.0f, 1.0f, 0.5f, 1.0f);		// Default text highlight color
		pallette[PAL_ICON]				= Color(1.0f, 1.0f, 1.0f, 0.25f);	// Default Icon
		pallette[PAL_ICON_HIGHLIGHT]	= Color(0.73, 0.65, 0.42, 0.5);		// Unknown (Icon highlight?)

//		White[0]			=	1.0f;
//		White[1]			=	1.0f;
//		White[2]			=	1.0f;
//		White[3]			=	1.0f;
//
//		Black[0]			=	0.0f;
//		Black[1]			=	0.0f;
//		Black[2]			=	0.0f;
//		Black[3]			=	1.0f;
//
//		Tan[0]				=	0.74f;
//		Tan[1]				=	0.65f;
//		Tan[2]				=	0.45f;
//		Tan[3]				=	1.0f;
//
//		Brown[0]			=	0.54f;
//		Brown[1]			=	0.45f;
//		Brown[2]			=	0.25f;
//		Brown[3]			=	1.0f;
//
//		Red[0]				=	1.0f;
//		Red[1]				=	0.0f;
//		Red[2]				=	0.0f;
//		Red[3]				=	1.0f;
//
//		Green[0]			=	0.0f;
//		Green[1]			=	1.0f;
//		Green[2]			=	0.0f;
//		Green[3]			=	1.0f;
//
//		Blue[0]				=	0.0f;
//		Blue[1]				=	0.0f;
//		Blue[2]				=	1.0f;
//		Blue[3]				=	1.0f;
//
////		lightyellow			=	Color(255.0f, 255.0f, 224.0f, 1.0f);
//		PaleGoldenrod[0]		=	255.0f/255.0f;
//		PaleGoldenrod[1]		=	255.0f/255.0f;
//		PaleGoldenrod[2]		=	170.0f/255.0f;
//		PaleGoldenrod[3]		=	1.0f;
//
//		Yellow[0]			=	1.0f;
//		Yellow[1]			=	1.0f;
//		Yellow[2]			=	0.0f;
//		Yellow[3]			=	1.0f;
//
//		Orange[0]			=	1.0f;
//		Orange[1]			=	0.6f;
//		Orange[2]			=	0.0f;
//		Orange[3]			=	1.0f;
//
//		Gray[0]				=	0.8f;
//		Gray[1]				=	0.8f;
//		Gray[2]				=	0.8f;
//		Gray[3]				=	1.0f;
//
//		Gray10[0]			=	0.1f;
//		Gray10[1]			=	0.1f;
//		Gray10[2]			=	0.1f;
//		Gray10[3]			=	1.0f;
//
//		Gray20[0]			=	0.2f;
//		Gray20[1]			=	0.2f;
//		Gray20[2]			=	0.2f;
//		Gray20[3]			=	1.0f;
//
//		Gray30[0]			=	0.3f;
//		Gray30[1]			=	0.3f;
//		Gray30[2]			=	0.3f;
//		Gray30[3]			=	1.0f;
//
//		Gray40[0]			=	0.4f;
//		Gray40[1]			=	0.4f;
//		Gray40[2]			=	0.4f;
//		Gray40[3]			=	1.0f;
//
//		Gray50[0]			=	0.5f;
//		Gray50[1]			=	0.5f;
//		Gray50[2]			=	0.5f;
//		Gray50[3]			=	1.0f;
//
//		Gray60[0]			=	0.6f;
//		Gray60[1]			=	0.6f;
//		Gray60[2]			=	0.6f;
//		Gray60[3]			=	1.0f;
//
//		Gray70[0]			=	0.7f;
//		Gray70[1]			=	0.7f;
//		Gray70[2]			=	0.7f;
//		Gray70[3]			=	1.0f;
//
//		Gray80[0]			=	0.8f;
//		Gray80[1]			=	0.8f;
//		Gray80[2]			=	0.8f;
//		Gray80[3]			=	1.0f;
//
//		Gray90[0]			=	0.9f;
//		Gray90[1]			=	0.9f;
//		Gray90[2]			=	0.9f;
//		Gray90[3]			=	1.0f;
//
//		Transparent[0]		=	0.0f;
//		Transparent[1]		=	0.0f;
//		Transparent[2]		=	0.0f;
//		Transparent[3]		=	0.0f;
//
//		Debug[0]			=	0.0f;
//		Debug[1]			=	0.0f;
//		Debug[2]			=	0.75f;
//		Debug[3]			=	0.25f;

//		//Pink colors
//			X11.Pinks.Pink					= "Pink";
//			X11.Pinks.LightPink				= "LightPink";
//			X11.Pinks.HotPink					= "HotPink";
//			X11.Pinks.DeepPink				= "DepePink";
//			X11.Pinks.PaleVioletRed			= "PaleVioletRed";
//			X11.Pinks.MediumVioletRed			= "MediumVioletRed";
//
//		//Red colors
//			X11.Reds.LightSalmon				= "LightSalmon";
//			X11.Reds.Salmon					= "Salmon";
//			X11.Reds.DarkSalmon				= "DarkSalmon";
//			X11.Reds.LightCoral				= "LightCoral";
//			X11.Reds.IndianRed				= "IndianRed";
//			X11.Reds.Crimson					= "Crimson";
//			X11.Reds.Firebrick				= "FireBrick";
//			X11.Reds.DarkRed					= "DarkRed";
//			X11.Reds.Red						= "Red";
//
//		//Orange colors
//			X11.Oranges.OrangeRed				= "OrangeRed";
//			X11.Oranges.Tomato					= "Tomato";
//			X11.Oranges.Coral					= "Coral";
//			X11.Oranges.DarkOrange				= "DarkOrange";
//			X11.Oranges.Orange					= "Orange";
//
//		//Yellow colors
//			X11.Yellows.Yellow					= "Yellow";
//			X11.Yellows.LightYellow				= "LightYellow";
//			X11.Yellows.LemonChiffon			= "LemonChiffon";
//			X11.Yellows.LightGoldenrodYellow	= "LightGoldenrodYellow";
//			X11.Yellows.PapayaWhip				= "PapayaWhip";
//			X11.Yellows.Moccasin				= "Moccasin";
//			X11.Yellows.PeachPuff				= "PeachPuff";
//			X11.Yellows.PaleGoldenrod			= "PaleGoldenrod";
//			X11.Yellows.Khaki					= "Khaki";
//			X11.Yellows.DarkKhaki				= "DarkKhaki";
//			X11.Yellows.Gold					= "Gold";
//
//		//Brown colors
//			X11.Browns.Cornsilk				= "Cornsilk";
//			X11.Browns.BlanchedAlmond			= "BlanchedAlmond";
//			X11.Browns.Bisque					= "Bisque";
//			X11.Browns.NavajoWhite				= "NavajoWhite";
//			X11.Browns.Wheat					= "Wheat";
//			X11.Browns.Burlywood				= "Burlywood";
//			X11.Browns.Tan						= "Tan";
//			X11.Browns.RosyBrown				= "RosyBrown";
//			X11.Browns.SandyBrown				= "SandyBrown";
//			X11.Browns.Goldenrod				= "Goldenrod";
//			X11.Browns.DarkGoldenrod			= "DarkGoldenrod";
//			X11.Browns.Peru					= "Peru";
//			X11.Browns.Chocolate				= "Chocolate";
//			X11.Browns.SaddleBrown				= "SaddleBrown";
//			X11.Browns.Sienna					= "Sienna";
//			X11.Browns.Brown					= "Brown";
//			X11.Browns.Maroon					= "Maroon";
//
//		//Green colors
//			X11.Greens.DarkOliveGreen			= "DarkOliveGreen";
//			X11.Greens.Olive					= "Olive";
//			X11.Greens.OliveDrab				= "OliveDrab";
//			X11.Greens.YellowGreen				= "YellowGreen";
//			X11.Greens.LimeGreen				= "LimeGreen";
//			X11.Greens.Lime					= "Lime";
//			X11.Greens.LawnGreen				= "LawnGreen";
//			X11.Greens.Chartreuse				= "Chartreuse";
//			X11.Greens.GreenYellow				= "GreenYellow";
//			X11.Greens.SpringGreen				= "SpringGreen";
//			X11.Greens.MediumSpringGreen		= "MediumSpringGreen";
//			X11.Greens.LightGreen				= "LightGreen";
//			X11.Greens.PaleGreen				= "PaleGreen";
//			X11.Greens.DarkSeaGreen			= "DarkSeaGreen";
//			X11.Greens.MediumAquamarine		= "MediumAquamarine";
//			X11.Greens.MediumSeaGreen			= "MediumSeaGreen";
//			X11.Greens.SeaGreen				= "SeaGreen";
//			X11.Greens.ForestGreen				= "ForestGreen";
//			X11.Greens.Green					= "Green";
//			X11.Greens.DarkGreen				= "DarkGreen";
//
//		//Cyan colors
//			X11.Cyans.Aqua					= "Aqua";
//			X11.Cyans.Cyan					= "Cyan";
//			X11.Cyans.LightCyan				= "LightCyan";
//			X11.Cyans.PaleTurquoise			= "PaleTurquoise";
//			X11.Cyans.Aquamarine				= "Aquamarine";
//			X11.Cyans.Turquoise				= "Turquoise";
//			X11.Cyans.MediumTurquoise			= "MediumTurquoise";
//			X11.Cyans.DarkTurquoise			= "DarkTurquoise";
//			X11.Cyans.LightSeaGreen			= "LightSeaGreen";
//			X11.Cyans.CadetBlue				= "CadetBlue";
//			X11.Cyans.DarkCyan				= "DarkCyan";
//			X11.Cyans.Teal					= "Teal";
//
//		//Blue colors
//			X11.Blues.LightSteelBlue			= "LightSteelBlue";
//			X11.Blues.PowderBlue				= "PowderBlue";
//			X11.Blues.LightBlue				= "LightBlue";
//			X11.Blues.SkyBlue					= "SkyBlue";
//			X11.Blues.LightSkyBlue			= "LightSkyBlue";
//			X11.Blues.DeepSkyBlue				= "DeepSkyBlue";
//			X11.Blues.DodgerBlue				= "DodgerBlue";
//			X11.Blues.CornflowerBlue			= "CornflowerBlue";
//			X11.Blues.SteelBlue				= "SteelBlue";
//			X11.Blues.RoyalBlue				= "RoyalBlue";
//			X11.Blues.Blue					= "Blue";
//			X11.Blues.MediumBlue				= "MediumBlue";
//			X11.Blues.DarkBlue				= "DarkBlue";
//			X11.Blues.Navy					= "Navy";
//			X11.Blues.MidnightBlue			= "MidnightBlue";
//
//		//Purple, violet, and magenta colors
//			X11.Purples.Lavender				= "Lavender";
//			X11.Purples.Thistle					= "Thistle";
//			X11.Purples.Plum					= "Plum";
//			X11.Purples.Violet					= "Violet";
//			X11.Purples.Orchid					= "Orchid";
//			X11.Purples.Fuchsia					= "Fuchsia";
//			X11.Purples.Magenta					= "Magenta";
//			X11.Purples.MediumOrchid			= "MediumOrchid";
//			X11.Purples.MediumPurple			= "MediumPurple";
//			X11.Purples.BlueViolet				= "BlueViolet";
//			X11.Purples.DarkViolet				= "DarkViolet";
//			X11.Purples.DarkOrchid				= "DarkOrchid";
//			X11.Purples.DarkMagenta				= "DarkMagenta";
//			X11.Purples.Purple					= "Purple";
//			X11.Purples.Indigo					= "Indigo";
//			X11.Purples.DarkSlateBlue			= "DarkSlateBlue";
//			X11.Purples.SlateBlue				= "SlateBlue";
//			X11.Purples.MediumSlateBlue			= "MediumSlateBlue";
//
//		//White colors
//			X11.Whites.White					= "White";
//			X11.Whites.Snow					= "Snow";
//			X11.Whites.Honeydew				= "Honeydew";
//			X11.Whites.MintCream				= "MintCream";
//			X11.Whites.Azure					= "Azure";
//			X11.Whites.AliceBlue				= "AliceBlue";
//			X11.Whites.GhostWhite				= "GhostWhite";
//			X11.Whites.WhiteSmoke				= "WhiteSmoke";
//			X11.Whites.Seashell				= "Seashell";
//			X11.Whites.Beige					= "Beige";
//			X11.Whites.OldLace					= "OldLace";
//			X11.Whites.FloralWhite				= "FloralWhite";
//			X11.Whites.Ivory					= "Ivory";
//			X11.Whites.AntiqueWhite			= "AntiqueWhite";
//			X11.Whites.Linen					= "Linen";
//			X11.Whites.LavenderBlush			= "LavenderBlush";
//			X11.Whites.MistyRose				= "MistyRose";
//
//		//Gray and black colors
//			X11.Grays.Gainsboro				= "Gainsboro";
//			X11.Grays.LightGray				= "LightGray";
//			X11.Grays.Silver					= "Silver";
//			X11.Grays.DarkGray				= "DarkGray";
//			X11.Grays.Gray					= "Gray";
//			X11.Grays.DimGray					= "DimGray";
//			X11.Grays.LightSlateGray			= "LightSlateGray";
//			X11.Grays.SlateGray				= "SlateGray";
//			X11.Grays.DarkSlateGray			= "DarkSlateGray";
//			X11.Grays.Black					= "Black";
//
//		// Custom Shades of Gray
//			X11.Grays.Gray10					= "gray10";
//			X11.Grays.Gray20					= "gray20";
//			X11.Grays.Gray30					= "gray30";
//			X11.Grays.Gray40					= "gray40";
//			X11.Grays.Gray50					= "gray50";
//			X11.Grays.Gray60					= "gray60";
//			X11.Grays.Gray70					= "gray70";
//			X11.Grays.Gray80					= "gray80";
//			X11.Grays.Gray90					= "gray90";
//
//		// Other colors
//			X11.Transparent				= "transparent";
//			X11.Debug					= "debug";
//
//		// TODO: Add web colors:
//		//Pink colors
//			AddColor255(X11.Pinks.Pink,					255, 192, 203, 255);
//			AddColor255(X11.Pinks.LightPink,				255, 182, 193, 255);
//			AddColor255(X11.Pinks.HotPink,				255, 105, 180, 255);
//			AddColor255(X11.Pinks.DeepPink,				255,  20, 147, 255);
//			AddColor255(X11.Pinks.PaleVioletRed,			219, 112, 147, 255);
//			AddColor255(X11.Pinks.MediumVioletRed,		199,  21, 133, 255);
//
//		//Red colors
//			AddColor255(X11.Reds.LightSalmon,			255, 160, 122, 255);
//			AddColor255(X11.Reds.Salmon,					250, 128, 114, 255);
//			AddColor255(X11.Reds.DarkSalmon,				233, 150, 122, 255);
//			AddColor255(X11.Reds.LightCoral,				240, 128, 128, 255);
//			AddColor255(X11.Reds.IndianRed,				205,  92,  92, 255);
//			AddColor255(X11.Reds.Crimson,				220,  20,  60, 255);
//			AddColor255(X11.Reds.Firebrick,				178,  34,  34, 255);
//			AddColor255(X11.Reds.DarkRed,				139,   0,   0, 255);
//			AddColor255(X11.Reds.Red,					255,   0,   0, 255);
//
//		//Orange colors
//			AddColor255(X11.Oranges.OrangeRed,				255,  69,   0, 255);
//			AddColor255(X11.Oranges.Tomato,					255,  99,  71, 255);
//			AddColor255(X11.Oranges.Coral,					255, 127,  80, 255);
//			AddColor255(X11.Oranges.DarkOrange,				255, 140,   0, 255);
//			AddColor255(X11.Oranges.Orange,					255, 165,   0, 255);
//
//		//Yellow colors
//			AddColor255(X11.Yellows.Yellow,					255, 255,   0, 255);
//			AddColor255(X11.Yellows.LightYellow,			255, 255, 224, 255);
//			AddColor255(X11.Yellows.LemonChiffon,			255, 250, 205, 255);
//			AddColor255(X11.Yellows.LightGoldenrodYellow,	250, 250, 210, 255);
//			AddColor255(X11.Yellows.PapayaWhip,				255, 239, 213, 255);
//			AddColor255(X11.Yellows.Moccasin,				255, 228, 181, 255);
//			AddColor255(X11.Yellows.PeachPuff,				255, 218, 185, 255);
//			AddColor255(X11.Yellows.PaleGoldenrod,			238, 232, 170, 255);
//			AddColor255(X11.Yellows.Khaki,					240, 230, 140, 255);
//			AddColor255(X11.Yellows.DarkKhaki,				189, 183, 107, 255);
//			AddColor255(X11.Yellows.Gold,					255, 215,   0, 255);
//
//		//Brown colors
//			AddColor255(X11.Browns.Cornsilk,				255, 248, 220, 255);
//			AddColor255(X11.Browns.BlanchedAlmond,			255, 235, 205, 255);
//			AddColor255(X11.Browns.Bisque,					255, 228, 196, 255);
//			AddColor255(X11.Browns.NavajoWhite,			255, 222, 173, 255);
//			AddColor255(X11.Browns.Wheat,					245, 222, 179, 255);
//			AddColor255(X11.Browns.Burlywood,				222, 184, 135, 255);
//			AddColor255(X11.Browns.Tan,					210, 180, 140, 255);
//			AddColor255(X11.Browns.RosyBrown,				188, 143, 143, 255);
//			AddColor255(X11.Browns.SandyBrown,				244, 164,  96, 255);
//			AddColor255(X11.Browns.Goldenrod,				218, 165,  32, 255);
//			AddColor255(X11.Browns.DarkGoldenrod,			184, 134,  11, 255);
//			AddColor255(X11.Browns.Peru,					205, 133,  63, 255);
//			AddColor255(X11.Browns.Chocolate,				210, 105,  30, 255);
//			AddColor255(X11.Browns.SaddleBrown,			139,  69,  19, 255);
//			AddColor255(X11.Browns.Sienna,					160,  82,  45, 255);
//			AddColor255(X11.Browns.Brown,					165,  42,  42, 255);
//			AddColor255(X11.Browns.Maroon,					128,   0,   0, 255);
//
//		//Green colors
//			AddColor255(X11.Greens.DarkOliveGreen,			 85, 107,  47, 255);
//			AddColor255(X11.Greens.Olive,					128, 128,   0, 255);
//			AddColor255(X11.Greens.OliveDrab,				107, 142,  35, 255);
//			AddColor255(X11.Greens.YellowGreen,			154, 205,  50, 255);
//			AddColor255(X11.Greens.LimeGreen,				 50, 205,  50, 255);
//			AddColor255(X11.Greens.Lime,					  0, 255,   0, 255);
//			AddColor255(X11.Greens.LawnGreen,				124, 252,   0, 255);
//			AddColor255(X11.Greens.Chartreuse,				127, 255,   0, 255);
//			AddColor255(X11.Greens.GreenYellow,			173, 255,  47, 255);
//			AddColor255(X11.Greens.SpringGreen,			  0, 255, 127, 255);
//			AddColor255(X11.Greens.MediumSpringGreen,		  0, 250, 154, 255);
//			AddColor255(X11.Greens.LightGreen,				144, 238, 144, 255);
//			AddColor255(X11.Greens.PaleGreen,				152, 251, 152, 255);
//			AddColor255(X11.Greens.DarkSeaGreen,			143, 188, 143, 255);
//			AddColor255(X11.Greens.MediumAquamarine,		102, 205, 170, 255);
//			AddColor255(X11.Greens.MediumSeaGreen,			 60, 179, 113, 255);
//			AddColor255(X11.Greens.SeaGreen,				 46, 139,  87, 255);
//			AddColor255(X11.Greens.ForestGreen,			 34, 139,  34, 255);
//			AddColor255(X11.Greens.Green,					  0, 128,   0, 255);
//			AddColor255(X11.Greens.DarkGreen,				  0, 100,   0, 255);
//
//		//Cyan colors
//			AddColor255(X11.Cyans.Aqua,						  0, 255, 255, 255);
//			AddColor255(X11.Cyans.Cyan,						  0, 255, 255, 255);
//			AddColor255(X11.Cyans.LightCyan,				224, 255, 255, 255);
//			AddColor255(X11.Cyans.PaleTurquoise,			175, 238, 238, 255);
//			AddColor255(X11.Cyans.Aquamarine,				127, 255, 212, 255);
//			AddColor255(X11.Cyans.Turquoise,				 64, 224, 208, 255);
//			AddColor255(X11.Cyans.MediumTurquoise,			 72, 209, 204, 255);
//			AddColor255(X11.Cyans.DarkTurquoise,			  0, 206, 209, 255);
//			AddColor255(X11.Cyans.LightSeaGreen,			 32, 178, 170, 255);
//			AddColor255(X11.Cyans.CadetBlue,				 95, 158, 160, 255);
//			AddColor255(X11.Cyans.DarkCyan,					  0, 139, 139, 255);
//			AddColor255(X11.Cyans.Teal,						  0, 128, 128, 255);
//
//		//Blue colors
//			AddColor255(X11.Blues.LightSteelBlue,			176, 196, 222, 255);
//			AddColor255(X11.Blues.PowderBlue,				176, 224, 230, 255);
//			AddColor255(X11.Blues.LightBlue,				173, 216, 230, 255);
//			AddColor255(X11.Blues.SkyBlue,				135, 206, 235, 255);
//			AddColor255(X11.Blues.LightSkyBlue,			135, 206, 250, 255);
//			AddColor255(X11.Blues.DeepSkyBlue,			  0, 191, 255, 255);
//			AddColor255(X11.Blues.DodgerBlue,				 30, 144, 255, 255);
//			AddColor255(X11.Blues.CornflowerBlue,			100, 149, 237, 255);
//			AddColor255(X11.Blues.SteelBlue,				 70, 130, 180, 255);
//			AddColor255(X11.Blues.RoyalBlue,				 65, 105, 225, 255);
//			AddColor255(X11.Blues.Blue,					  0,   0, 255, 255);
//			AddColor255(X11.Blues.MediumBlue,				  0,   0, 205, 255);
//			AddColor255(X11.Blues.DarkBlue,				  0,   0, 139, 255);
//			AddColor255(X11.Blues.Navy,					  0,   0, 128, 255);
//			AddColor255(X11.Blues.MidnightBlue,			 25,  25, 112, 255);
//
//		//Purple violet and magenta colors
//			AddColor255(X11.Purples.Lavender,				230, 230, 250, 255);
//			AddColor255(X11.Purples.Thistle,				216, 191, 216, 255);
//			AddColor255(X11.Purples.Plum,					221, 160, 221, 255);
//			AddColor255(X11.Purples.Violet,					238, 130, 238, 255);
//			AddColor255(X11.Purples.Orchid,					218, 112, 214, 255);
//			AddColor255(X11.Purples.Fuchsia,				255,   0, 255, 255);
//			AddColor255(X11.Purples.Magenta,				255,   0, 255, 255);
//			AddColor255(X11.Purples.MediumOrchid,			186,  85, 211, 255);
//			AddColor255(X11.Purples.MediumPurple,			147, 112, 219, 255);
//			AddColor255(X11.Purples.BlueViolet,				138,  43, 226, 255);
//			AddColor255(X11.Purples.DarkViolet,				148,   0, 211, 255);
//			AddColor255(X11.Purples.DarkOrchid,				153,  50, 204, 255);
//			AddColor255(X11.Purples.DarkMagenta,			139,   0, 139, 255);
//			AddColor255(X11.Purples.Purple,					128,   0, 128, 255);
//			AddColor255(X11.Purples.Indigo,					 75,   0, 130, 255);
//			AddColor255(X11.Purples.DarkSlateBlue,			 72,  61, 139, 255);
//			AddColor255(X11.Purples.SlateBlue,				106,  90, 205, 255);
//			AddColor255(X11.Purples.MediumSlateBlue,		123, 104, 238, 255);
//
//		//White colors
//			AddColor255(X11.Whites.White,					255, 255, 255, 255);
//			AddColor255(X11.Whites.Snow,					255, 250, 250, 255);
//			AddColor255(X11.Whites.Honeydew,				240, 255, 240, 255);
//			AddColor255(X11.Whites.MintCream,				245, 255, 250, 255);
//			AddColor255(X11.Whites.Azure,					240, 255, 255, 255);
//			AddColor255(X11.Whites.AliceBlue,				240, 248, 255, 255);
//			AddColor255(X11.Whites.GhostWhite,				248, 248, 255, 255);
//			AddColor255(X11.Whites.WhiteSmoke,				245, 245, 245, 255);
//			AddColor255(X11.Whites.Seashell,				255, 245, 238, 255);
//			AddColor255(X11.Whites.Beige,					245, 245, 220, 255);
//			AddColor255(X11.Whites.OldLace,				253, 245, 230, 255);
//			AddColor255(X11.Whites.FloralWhite,			255, 250, 240, 255);
//			AddColor255(X11.Whites.Ivory,					255, 255, 240, 255);
//			AddColor255(X11.Whites.AntiqueWhite,			250, 235, 215, 255);
//			AddColor255(X11.Whites.Linen,					250, 240, 230, 255);
//			AddColor255(X11.Whites.LavenderBlush,			255, 240, 245, 255);
//			AddColor255(X11.Whites.MistyRose,				255, 228, 225, 255);
//
//		//Gray and black colors
//			AddColor255(X11.Grays.Gainsboro,				220, 220, 220, 255);
//			AddColor255(X11.Grays.LightGray,				211, 211, 211, 255);
//			AddColor255(X11.Grays.Silver,					192, 192, 192, 255);
//			AddColor255(X11.Grays.DarkGray,				169, 169, 169, 255);
//			AddColor255(X11.Grays.Gray,					128, 128, 128, 255);
//			AddColor255(X11.Grays.DimGray,				105, 105, 105, 255);
//			AddColor255(X11.Grays.LightSlateGray,			119, 136, 153, 255);
//			AddColor255(X11.Grays.SlateGray,				112, 128, 144, 255);
//			AddColor255(X11.Grays.DarkSlateGray,			 47,  79,  79, 255);
//			AddColor255(X11.Grays.Black,					  0,   0,   0, 255);
//
//		// Custom Shades of Gray
//			AddColor255(X11.Grays.Gray10,					 0.10*255,  0.10*255,  0.10*255, 255);
//			AddColor255(X11.Grays.Gray20,					 0.20*255,  0.20*255,  0.20*255, 255);
//			AddColor255(X11.Grays.Gray30,					 0.30*255,  0.30*255,  0.30*255, 255);
//			AddColor255(X11.Grays.Gray40,					 0.40*255,  0.40*255,  0.40*255, 255);
//			AddColor255(X11.Grays.Gray50,					 0.50*255,  0.50*255,  0.50*255, 255);
//			AddColor255(X11.Grays.Gray60,					 0.60*255,  0.60*255,  0.60*255, 255);
//			AddColor255(X11.Grays.Gray70,					 0.70*255,  0.70*255,  0.70*255, 255);
//			AddColor255(X11.Grays.Gray80,					 0.80*255,  0.80*255,  0.80*255, 255);
//			AddColor255(X11.Grays.Gray90,					 0.90*255,  0.90*255,  0.90*255, 255);
//
//		// Other colors
//			AddColor(X11.Transparent,				0.0f, 0.0f, 0.0f, 0.0f);
//			AddColor(X11.Debug,						0.0f, 0.0f, 0.75f, 0.25f);



















			// System and custom colors
			Extended.Transparent						= "Transparent";						AddColor255(Extended.Transparent, 0, 0, 0, 0);

			Extended.Gray10								= "Gray10";								AddColor255(Extended.Gray10, 0.10*255,  0.10*255,  0.10*255, 255);
			Extended.Gray20								= "Gray20";								AddColor255(Extended.Gray20, 0.20*255,  0.20*255,  0.20*255, 255);
			Extended.Gray30								= "Gray30";								AddColor255(Extended.Gray30, 0.30*255,  0.30*255,  0.30*255, 255);
			Extended.Gray40								= "Gray40";								AddColor255(Extended.Gray40, 0.40*255,  0.40*255,  0.40*255, 255);
			Extended.Gray50								= "Gray50";								AddColor255(Extended.Gray50, 0.50*255,  0.50*255,  0.50*255, 255);
			Extended.Gray60								= "Gray60";								AddColor255(Extended.Gray60, 0.60*255,  0.60*255,  0.60*255, 255);
			Extended.Gray70								= "Gray70";								AddColor255(Extended.Gray70, 0.70*255,  0.70*255,  0.70*255, 255);
			Extended.Gray80								= "Gray80";								AddColor255(Extended.Gray80, 0.80*255,  0.80*255,  0.80*255, 255);
			Extended.Gray90								= "Gray90";								AddColor255(Extended.Gray90, 0.90*255,  0.90*255,  0.90*255, 255);

			// Can be used to find first actual color
			Extended.FIRST = colors.size()-1;

			AddColor(Extended.Black, 0.00, 0.00, 0.00, 1.0);
			AddColor(Extended.Eerie_black, 0.11, 0.11, 0.11, 1.0);
			AddColor(Extended.Seal_brown, 0.20, 0.08, 0.08, 1.0);
			AddColor(Extended.Dark_sienna, 0.24, 0.08, 0.08, 1.0);
			AddColor(Extended.Jet, 0.20, 0.20, 0.20, 1.0);
			AddColor(Extended.Blood_red, 0.40, 0.00, 0.00, 1.0);
			AddColor(Extended.Black_coffee, 0.23, 0.18, 0.18, 1.0);
			AddColor(Extended.Maroon_web, 0.50, 0.00, 0.00, 1.0);
			AddColor(Extended.Persian_plum, 0.44, 0.11, 0.11, 1.0);
			AddColor(Extended.Prune, 0.44, 0.11, 0.11, 1.0);
			AddColor(Extended.Dark_red, 0.55, 0.00, 0.00, 1.0);
			AddColor(Extended.Falu_red, 0.50, 0.09, 0.09, 1.0);
			AddColor(Extended.Davys_grey, 0.33, 0.33, 0.33, 1.0);
			AddColor(Extended.Tuscan_red, 0.49, 0.28, 0.28, 1.0);
			AddColor(Extended.Granite_gray, 0.40, 0.40, 0.40, 1.0);
			AddColor(Extended.Carnelian, 0.70, 0.11, 0.11, 1.0);
			AddColor(Extended.Dim_gray, 0.41, 0.41, 0.41, 1.0);
			AddColor(Extended.Auburn, 0.65, 0.16, 0.16, 1.0);
			AddColor(Extended.Firebrick, 0.70, 0.13, 0.13, 1.0);
			AddColor(Extended.Rosso_corsa, 0.83, 0.00, 0.00, 1.0);
			AddColor(Extended.Sonic_silver, 0.46, 0.46, 0.46, 1.0);
			AddColor(Extended.Rose_taupe, 0.56, 0.36, 0.36, 1.0);
			AddColor(Extended.Middle_red_purple, 0.65, 0.33, 0.33, 1.0);
			AddColor(Extended.Maximum_red, 0.85, 0.13, 0.13, 1.0);
			AddColor(Extended.Gray_web, 0.50, 0.50, 0.50, 1.0);
			AddColor(Extended.Copper_rose, 0.60, 0.40, 0.40, 1.0);
			AddColor(Extended.Persian_red, 0.80, 0.20, 0.20, 1.0);
			AddColor(Extended.Red, 1.00, 0.00, 0.00, 1.0);
			AddColor(Extended.Permanent_Geranium_Lake, 0.88, 0.17, 0.17, 1.0);
			AddColor(Extended.Indian_red, 0.80, 0.36, 0.36, 1.0);
			AddColor(Extended.Spanish_gray, 0.60, 0.60, 0.60, 1.0);
			AddColor(Extended.Quick_Silver, 0.65, 0.65, 0.65, 1.0);
			AddColor(Extended.Rosy_brown, 0.74, 0.56, 0.56, 1.0);
			AddColor(Extended.Silver_chalice, 0.67, 0.67, 0.67, 1.0);
			AddColor(Extended.Tuscany, 0.75, 0.60, 0.60, 1.0);
			AddColor(Extended.Light_coral, 0.94, 0.50, 0.50, 1.0);
			AddColor(Extended.Gray_X11, 0.75, 0.75, 0.75, 1.0);
			AddColor(Extended.Silver, 0.75, 0.75, 0.75, 1.0);
			AddColor(Extended.Light_gray, 0.83, 0.83, 0.83, 1.0);
			AddColor(Extended.Gainsboro, 0.86, 0.86, 0.86, 1.0);
			AddColor(Extended.Baby_pink, 0.96, 0.76, 0.76, 1.0);
			AddColor(Extended.Tea_rose, 0.96, 0.76, 0.76, 1.0);
			AddColor(Extended.Cultured, 0.96, 0.96, 0.96, 1.0);
			AddColor(Extended.Snow, 1.00, 0.98, 0.98, 1.0);
			AddColor(Extended.White, 1.00, 1.00, 1.00, 1.0);
			AddColor(Extended.Pastel_pink, 0.87, 0.65, 0.64, 1.0);
			AddColor(Extended.Spanish_pink, 0.97, 0.75, 0.75, 1.0);
			AddColor(Extended.Brandy, 0.53, 0.25, 0.25, 1.0);
			AddColor(Extended.Candy_apple_red, 1.00, 0.03, 0.00, 1.0);
			AddColor(Extended.Tart_Orange, 0.98, 0.30, 0.27, 1.0);
			AddColor(Extended.International_orange_engineering, 0.73, 0.09, 0.05, 1.0);
			AddColor(Extended.Sweet_Brown, 0.66, 0.22, 0.19, 1.0);
			AddColor(Extended.Deep_chestnut, 0.73, 0.31, 0.28, 1.0);
			AddColor(Extended.Red_orange, 1.00, 0.33, 0.29, 1.0);
			AddColor(Extended.New_York_pink, 0.84, 0.51, 0.50, 1.0);
			AddColor(Extended.Silver_pink, 0.77, 0.68, 0.68, 1.0);
			AddColor(Extended.Barn_red, 0.49, 0.04, 0.01, 1.0);
			AddColor(Extended.Rose_ebony, 0.40, 0.28, 0.27, 1.0);
			AddColor(Extended.International_orange_GGB, 0.75, 0.21, 0.17, 1.0);
			AddColor(Extended.CG_red, 0.88, 0.24, 0.19, 1.0);
			AddColor(Extended.Orange_red_Crayola, 1.00, 0.33, 0.29, 1.0);
			AddColor(Extended.Medium_carmine, 0.69, 0.25, 0.21, 1.0);
			AddColor(Extended.Red_RYB, 1.00, 0.15, 0.07, 1.0);
			AddColor(Extended.Copper_penny, 0.68, 0.44, 0.41, 1.0);
			AddColor(Extended.Cinnabar, 0.89, 0.26, 0.20, 1.0);
			AddColor(Extended.Vermilion, 0.89, 0.26, 0.20, 1.0);
			AddColor(Extended.Congo_pink, 0.97, 0.51, 0.47, 1.0);
			AddColor(Extended.Coral_pink, 0.97, 0.51, 0.47, 1.0);
			AddColor(Extended.Tea_rose_orange, 0.97, 0.51, 0.47, 1.0);
			AddColor(Extended.Old_burgundy, 0.26, 0.19, 0.18, 1.0);
			AddColor(Extended.Redwood, 0.64, 0.35, 0.32, 1.0);
			AddColor(Extended.Fire_opal, 0.91, 0.36, 0.29, 1.0);
			AddColor(Extended.Bittersweet, 1.00, 0.44, 0.37, 1.0);
			AddColor(Extended.Salmon, 0.98, 0.50, 0.45, 1.0);
			AddColor(Extended.Misty_rose, 1.00, 0.89, 0.88, 1.0);
			AddColor(Extended.Caput_mortuum, 0.35, 0.15, 0.13, 1.0);
			AddColor(Extended.Rufous, 0.66, 0.11, 0.03, 1.0);
			AddColor(Extended.Medium_vermilion, 0.85, 0.22, 0.12, 1.0);
			AddColor(Extended.Scarlet, 1.00, 0.14, 0.00, 1.0);
			AddColor(Extended.Burnished_brown, 0.63, 0.48, 0.45, 1.0);
			AddColor(Extended.Cedar_Chest, 0.79, 0.35, 0.29, 1.0);
			AddColor(Extended.Liver, 0.40, 0.30, 0.28, 1.0);
			AddColor(Extended.Burnt_umber, 0.54, 0.20, 0.14, 1.0);
			AddColor(Extended.Bole, 0.47, 0.27, 0.23, 1.0);
			AddColor(Extended.Tomato, 1.00, 0.39, 0.28, 1.0);
			AddColor(Extended.Black_bean, 0.24, 0.05, 0.01, 1.0);
			AddColor(Extended.Chestnut, 0.58, 0.27, 0.21, 1.0);
			AddColor(Extended.Orange_soda, 0.98, 0.36, 0.24, 1.0);
			AddColor(Extended.Terra_cotta, 0.89, 0.45, 0.36, 1.0);
			AddColor(Extended.Melon, 1.00, 0.73, 0.68, 1.0);
			AddColor(Extended.Chinese_red, 0.67, 0.22, 0.12, 1.0);
			AddColor(Extended.Portland_Orange, 1.00, 0.35, 0.21, 1.0);
			AddColor(Extended.Dark_liver_horses, 0.33, 0.24, 0.22, 1.0);
			AddColor(Extended.Liver_organ, 0.42, 0.18, 0.12, 1.0);
			AddColor(Extended.Kobe, 0.53, 0.18, 0.09, 1.0);
			AddColor(Extended.Sienna, 0.53, 0.18, 0.09, 1.0);
			AddColor(Extended.Blast_off_bronze, 0.65, 0.44, 0.39, 1.0);
			AddColor(Extended.Cinereous, 0.60, 0.51, 0.48, 1.0);
			AddColor(Extended.Outrageous_Orange, 1.00, 0.43, 0.29, 1.0);
			AddColor(Extended.Vivid_tangerine, 1.00, 0.63, 0.54, 1.0);
			AddColor(Extended.Coquelicot, 1.00, 0.22, 0.00, 1.0);
			AddColor(Extended.Copper_red, 0.80, 0.43, 0.32, 1.0);
			AddColor(Extended.Burnt_sienna, 0.91, 0.45, 0.32, 1.0);
			AddColor(Extended.Middle_red, 0.90, 0.56, 0.45, 1.0);
			AddColor(Extended.Dark_salmon, 0.91, 0.59, 0.48, 1.0);
			AddColor(Extended.Red_orange_CW, 1.00, 0.27, 0.00, 1.0);
			AddColor(Extended.Coral, 1.00, 0.50, 0.31, 1.0);
			AddColor(Extended.Sinopia, 0.80, 0.25, 0.04, 1.0);
			AddColor(Extended.Flame, 0.89, 0.35, 0.13, 1.0);
			AddColor(Extended.Light_salmon, 1.00, 0.63, 0.48, 1.0);
			AddColor(Extended.Rust, 0.72, 0.25, 0.05, 1.0);
			AddColor(Extended.Orange_Crayola, 1.00, 0.46, 0.22, 1.0);
			AddColor(Extended.Mandarin, 0.95, 0.48, 0.28, 1.0);
			AddColor(Extended.Copper_Crayola, 0.85, 0.54, 0.40, 1.0);
			AddColor(Extended.International_orange_aerospace, 1.00, 0.31, 0.00, 1.0);
			AddColor(Extended.Fuzzy_Wuzzy, 0.53, 0.26, 0.12, 1.0);
			AddColor(Extended.Mahogany, 0.75, 0.25, 0.00, 1.0);
			AddColor(Extended.Brown_sugar, 0.69, 0.43, 0.30, 1.0);
			AddColor(Extended.Orange_red, 1.00, 0.41, 0.12, 1.0);
			AddColor(Extended.Red_orange_Crayola, 1.00, 0.41, 0.12, 1.0);
			AddColor(Extended.Mango_Tango, 1.00, 0.51, 0.26, 1.0);
			AddColor(Extended.Atomic_tangerine, 1.00, 0.60, 0.40, 1.0);
			AddColor(Extended.Umber, 0.39, 0.32, 0.28, 1.0);
			AddColor(Extended.Orange_Pantone, 1.00, 0.35, 0.00, 1.0);
			AddColor(Extended.Pale_silver, 0.79, 0.75, 0.73, 1.0);
			AddColor(Extended.Silver_Crayola, 0.79, 0.75, 0.73, 1.0);
			AddColor(Extended.Persimmon, 0.93, 0.35, 0.00, 1.0);
			AddColor(Extended.Beaver, 0.62, 0.51, 0.44, 1.0);
			AddColor(Extended.Antique_brass, 0.80, 0.58, 0.46, 1.0);
			AddColor(Extended.Unbleached_silk, 1.00, 0.87, 0.79, 1.0);
			AddColor(Extended.Bistre, 0.24, 0.17, 0.12, 1.0);
			AddColor(Extended.Blaze_orange, 1.00, 0.40, 0.00, 1.0);
			AddColor(Extended.Pumpkin, 1.00, 0.46, 0.09, 1.0);
			AddColor(Extended.Raw_sienna, 0.84, 0.54, 0.35, 1.0);
			AddColor(Extended.Tumbleweed, 0.87, 0.67, 0.53, 1.0);
			AddColor(Extended.Apricot, 0.98, 0.81, 0.69, 1.0);
			AddColor(Extended.Van_Dyke_brown, 0.40, 0.26, 0.16, 1.0);
			AddColor(Extended.Saddle_brown, 0.55, 0.27, 0.07, 1.0);
			AddColor(Extended.Coffee, 0.44, 0.31, 0.22, 1.0);
			AddColor(Extended.Tuscan_brown, 0.44, 0.31, 0.22, 1.0);
			AddColor(Extended.Burnt_orange, 0.80, 0.33, 0.00, 1.0);
			AddColor(Extended.Tawny, 0.80, 0.34, 0.00, 1.0);
			AddColor(Extended.Spanish_orange, 0.91, 0.38, 0.00, 1.0);
			AddColor(Extended.Chocolate_web, 0.82, 0.41, 0.12, 1.0);
			AddColor(Extended.Cocoa_brown, 0.82, 0.41, 0.12, 1.0);
			AddColor(Extended.Tan, 0.82, 0.71, 0.55, 1.0);
			AddColor(Extended.Desert_sand, 0.93, 0.79, 0.69, 1.0);
			AddColor(Extended.Champagne_pink, 0.95, 0.87, 0.81, 1.0);
			AddColor(Extended.Seashell, 1.00, 0.96, 0.93, 1.0);
			AddColor(Extended.Russet, 0.50, 0.27, 0.11, 1.0);
			AddColor(Extended.Cafe_au_lait, 0.65, 0.48, 0.36, 1.0);
			AddColor(Extended.French_beige, 0.65, 0.48, 0.36, 1.0);
			AddColor(Extended.Tuscan_tan, 0.65, 0.48, 0.36, 1.0);
			AddColor(Extended.Princeton_orange, 0.96, 0.50, 0.15, 1.0);
			AddColor(Extended.Persian_orange, 0.85, 0.56, 0.35, 1.0);
			AddColor(Extended.Peach_Crayola, 1.00, 0.80, 0.64, 1.0);
			AddColor(Extended.Dark_lava, 0.28, 0.24, 0.20, 1.0);
			AddColor(Extended.Taupe, 0.28, 0.24, 0.20, 1.0);
			AddColor(Extended.Alloy_orange, 0.77, 0.38, 0.06, 1.0);
			AddColor(Extended.Liver_chestnut, 0.60, 0.45, 0.34, 1.0);
			AddColor(Extended.Macaroni_and_Cheese, 1.00, 0.74, 0.53, 1.0);
			AddColor(Extended.Kobicha, 0.42, 0.27, 0.14, 1.0);
			AddColor(Extended.Safety_orange, 1.00, 0.47, 0.00, 1.0);
			AddColor(Extended.Cadmium_orange, 0.93, 0.53, 0.18, 1.0);
			AddColor(Extended.Sandy_brown, 0.96, 0.64, 0.38, 1.0);
			AddColor(Extended.Peach_puff, 1.00, 0.85, 0.73, 1.0);
			AddColor(Extended.Liver_dogs, 0.72, 0.43, 0.16, 1.0);
			AddColor(Extended.Copper, 0.72, 0.45, 0.20, 1.0);
			AddColor(Extended.Heat_Wave, 1.00, 0.48, 0.00, 1.0);
			AddColor(Extended.Rajah, 0.98, 0.67, 0.38, 1.0);
			AddColor(Extended.Smoky_black, 0.06, 0.05, 0.03, 1.0);
			AddColor(Extended.Cafe_noir, 0.29, 0.21, 0.13, 1.0);
			AddColor(Extended.Dark_brown, 0.40, 0.26, 0.13, 1.0);
			AddColor(Extended.Sepia, 0.44, 0.26, 0.08, 1.0);
			AddColor(Extended.Windsor_tan, 0.65, 0.33, 0.01, 1.0);
			AddColor(Extended.Ochre, 0.80, 0.47, 0.13, 1.0);
			AddColor(Extended.Bronze, 0.80, 0.50, 0.20, 1.0);
			AddColor(Extended.Amber_SAE, 1.00, 0.49, 0.00, 1.0);
			AddColor(Extended.Orange, 1.00, 0.50, 0.00, 1.0);
			AddColor(Extended.Deep_saffron, 1.00, 0.60, 0.20, 1.0);
			AddColor(Extended.Fawn, 0.90, 0.67, 0.44, 1.0);
			AddColor(Extended.Middle_yellow_red, 0.93, 0.69, 0.46, 1.0);
			AddColor(Extended.Mellow_apricot, 0.97, 0.72, 0.47, 1.0);
			AddColor(Extended.Light_orange, 1.00, 0.85, 0.69, 1.0);
			AddColor(Extended.Almond, 0.94, 0.87, 0.80, 1.0);
			AddColor(Extended.Isabelline, 0.96, 0.94, 0.93, 1.0);
			AddColor(Extended.Linen, 0.98, 0.94, 0.90, 1.0);
			AddColor(Extended.Chocolate_traditional, 0.48, 0.25, 0.00, 1.0);
			AddColor(Extended.Neon_Carrot, 1.00, 0.64, 0.26, 1.0);
			AddColor(Extended.Coyote_brown, 0.51, 0.38, 0.24, 1.0);
			AddColor(Extended.Pullman_Brown, 0.39, 0.25, 0.09, 1.0);
			AddColor(Extended.Raw_umber, 0.51, 0.40, 0.27, 1.0);
			AddColor(Extended.Tangerine, 0.95, 0.52, 0.00, 1.0);
			AddColor(Extended.Dark_orange, 1.00, 0.55, 0.00, 1.0);
			AddColor(Extended.Middle_grey, 0.55, 0.53, 0.50, 1.0);
			AddColor(Extended.Carrot_orange, 0.93, 0.57, 0.13, 1.0);
			AddColor(Extended.Camel, 0.76, 0.60, 0.42, 1.0);
			AddColor(Extended.Desert, 0.76, 0.60, 0.42, 1.0);
			AddColor(Extended.Fallow, 0.76, 0.60, 0.42, 1.0);
			AddColor(Extended.Lion, 0.76, 0.60, 0.42, 1.0);
			AddColor(Extended.Wood_brown, 0.76, 0.60, 0.42, 1.0);
			AddColor(Extended.Timberwolf, 0.86, 0.84, 0.82, 1.0);
			AddColor(Extended.Bisque, 1.00, 0.89, 0.77, 1.0);
			AddColor(Extended.French_bistre, 0.52, 0.43, 0.30, 1.0);
			AddColor(Extended.Grullo, 0.66, 0.60, 0.53, 1.0);
			AddColor(Extended.Earth_yellow, 0.88, 0.66, 0.37, 1.0);
			AddColor(Extended.Yellow_Orange, 1.00, 0.68, 0.26, 1.0);
			AddColor(Extended.Tan_Crayola, 0.85, 0.60, 0.42, 1.0);
			AddColor(Extended.Burlywood, 0.87, 0.72, 0.53, 1.0);
			AddColor(Extended.Gold_Crayola, 0.90, 0.75, 0.54, 1.0);
			AddColor(Extended.Antique_white, 0.98, 0.92, 0.84, 1.0);
			AddColor(Extended.Brown, 0.53, 0.33, 0.04, 1.0);
			AddColor(Extended.Fulvous, 0.89, 0.52, 0.00, 1.0);
			AddColor(Extended.Indian_yellow, 0.89, 0.66, 0.34, 1.0);
			AddColor(Extended.Deep_champagne, 0.98, 0.84, 0.65, 1.0);
			AddColor(Extended.Sunset, 0.98, 0.84, 0.65, 1.0);
			AddColor(Extended.Tuscan, 0.98, 0.84, 0.65, 1.0);
			AddColor(Extended.Golden_brown, 0.60, 0.40, 0.08, 1.0);
			AddColor(Extended.Yellow_Orange_CW, 1.00, 0.58, 0.02, 1.0);
			AddColor(Extended.Sunray, 0.89, 0.67, 0.34, 1.0);
			AddColor(Extended.Navajo_white, 1.00, 0.87, 0.68, 1.0);
			AddColor(Extended.Blanched_almond, 1.00, 0.92, 0.80, 1.0);
			AddColor(Extended.Shadow, 0.54, 0.47, 0.36, 1.0);
			AddColor(Extended.Orange_peel, 1.00, 0.62, 0.00, 1.0);
			AddColor(Extended.Bright_yellow_Crayola, 1.00, 0.67, 0.11, 1.0);
			AddColor(Extended.Khaki_web, 0.76, 0.69, 0.57, 1.0);
			AddColor(Extended.Champagne, 0.97, 0.91, 0.81, 1.0);
			AddColor(Extended.Papaya_whip, 1.00, 0.94, 0.84, 1.0);
			AddColor(Extended.Light_French_beige, 0.78, 0.68, 0.50, 1.0);
			AddColor(Extended.Magnolia, 0.95, 0.91, 0.84, 1.0);
			AddColor(Extended.Gamboge, 0.89, 0.61, 0.06, 1.0);
			AddColor(Extended.Chrome_yellow, 1.00, 0.65, 0.00, 1.0);
			AddColor(Extended.Orange_web, 1.00, 0.65, 0.00, 1.0);
			AddColor(Extended.Marigold, 0.92, 0.64, 0.13, 1.0);
			AddColor(Extended.Wheat, 0.96, 0.87, 0.70, 1.0);
			AddColor(Extended.Bone, 0.89, 0.85, 0.79, 1.0);
			AddColor(Extended.Peach, 1.00, 0.90, 0.71, 1.0);
			AddColor(Extended.Old_lace, 0.99, 0.96, 0.90, 1.0);
			AddColor(Extended.Harvest_gold, 0.85, 0.57, 0.00, 1.0);
			AddColor(Extended.Maximum_yellow_red, 0.95, 0.73, 0.29, 1.0);
			AddColor(Extended.Platinum, 0.90, 0.89, 0.89, 1.0);
			AddColor(Extended.Floral_white, 1.00, 0.98, 0.94, 1.0);
			AddColor(Extended.Metallic_Sunburst, 0.61, 0.49, 0.22, 1.0);
			AddColor(Extended.Black_chocolate, 0.11, 0.09, 0.07, 1.0);
			AddColor(Extended.Field_drab, 0.42, 0.33, 0.12, 1.0);
			AddColor(Extended.Chinese_yellow, 1.00, 0.70, 0.00, 1.0);
			AddColor(Extended.Dutch_white, 0.94, 0.87, 0.73, 1.0);
			AddColor(Extended.Olive_Drab_7, 0.24, 0.20, 0.12, 1.0);
			AddColor(Extended.Bistre_brown, 0.59, 0.44, 0.09, 1.0);
			AddColor(Extended.Drab, 0.59, 0.44, 0.09, 1.0);
			AddColor(Extended.Mode_beige, 0.59, 0.44, 0.09, 1.0);
			AddColor(Extended.Sand_dune, 0.59, 0.44, 0.09, 1.0);
			AddColor(Extended.Dark_goldenrod, 0.72, 0.53, 0.04, 1.0);
			AddColor(Extended.Gold_Fusion, 0.52, 0.46, 0.31, 1.0);
			AddColor(Extended.Goldenrod, 0.85, 0.65, 0.13, 1.0);
			AddColor(Extended.Satin_sheen_gold, 0.80, 0.63, 0.21, 1.0);
			AddColor(Extended.Banana_Mania, 0.98, 0.91, 0.71, 1.0);
			AddColor(Extended.Cosmic_latte, 1.00, 0.97, 0.91, 1.0);
			AddColor(Extended.Selective_yellow, 1.00, 0.73, 0.00, 1.0);
			AddColor(Extended.Orange_yellow, 0.96, 0.74, 0.12, 1.0);
			AddColor(Extended.Maize_Crayola, 0.95, 0.78, 0.29, 1.0);
			AddColor(Extended.Lemon_curry, 0.80, 0.63, 0.11, 1.0);
			AddColor(Extended.Amber, 1.00, 0.75, 0.00, 1.0);
			AddColor(Extended.Mikado_yellow, 1.00, 0.77, 0.05, 1.0);
			AddColor(Extended.Saffron, 0.96, 0.77, 0.19, 1.0);
			AddColor(Extended.Sunglow, 1.00, 0.80, 0.20, 1.0);
			AddColor(Extended.Ecru, 0.76, 0.70, 0.50, 1.0);
			AddColor(Extended.Sand, 0.76, 0.70, 0.50, 1.0);
			AddColor(Extended.Orange_yellow_Crayola, 0.97, 0.84, 0.41, 1.0);
			AddColor(Extended.Gold, 0.65, 0.49, 0.00, 1.0);
			AddColor(Extended.Golden_poppy, 0.99, 0.76, 0.00, 1.0);
			AddColor(Extended.Mango, 0.99, 0.75, 0.01, 1.0);
			AddColor(Extended.Gold_metallic, 0.83, 0.69, 0.22, 1.0);
			AddColor(Extended.Metallic_gold, 0.83, 0.69, 0.22, 1.0);
			AddColor(Extended.Eggshell, 0.94, 0.92, 0.84, 1.0);
			AddColor(Extended.Mustard, 1.00, 0.86, 0.35, 1.0);
			AddColor(Extended.Jasmine, 0.97, 0.87, 0.49, 1.0);
			AddColor(Extended.Mellow_yellow, 0.97, 0.87, 0.49, 1.0);
			AddColor(Extended.Lemon_meringue, 0.96, 0.92, 0.75, 1.0);
			AddColor(Extended.Naples_yellow, 0.98, 0.85, 0.37, 1.0);
			AddColor(Extended.Royal_yellow, 0.98, 0.85, 0.37, 1.0);
			AddColor(Extended.Stil_de_grain_yellow, 0.98, 0.85, 0.37, 1.0);
			AddColor(Extended.Medium_champagne, 0.95, 0.90, 0.67, 1.0);
			AddColor(Extended.Vanilla, 0.95, 0.90, 0.67, 1.0);
			AddColor(Extended.Cornsilk, 1.00, 0.97, 0.86, 1.0);
			AddColor(Extended.Old_gold, 0.81, 0.71, 0.23, 1.0);
			AddColor(Extended.Jonquil, 0.96, 0.79, 0.09, 1.0);
			AddColor(Extended.Buff, 0.94, 0.86, 0.51, 1.0);
			AddColor(Extended.Cyber_yellow, 1.00, 0.83, 0.00, 1.0);
			AddColor(Extended.Yellow_NCS, 1.00, 0.83, 0.00, 1.0);
			AddColor(Extended.Vegas_gold, 0.77, 0.70, 0.35, 1.0);
			AddColor(Extended.Flax, 0.93, 0.86, 0.51, 1.0);
			AddColor(Extended.Yellow_Crayola, 0.99, 0.91, 0.51, 1.0);
			AddColor(Extended.Blond, 0.98, 0.94, 0.75, 1.0);
			AddColor(Extended.Alabaster, 0.93, 0.92, 0.88, 1.0);
			AddColor(Extended.Yellow_Munsell, 0.94, 0.80, 0.00, 1.0);
			AddColor(Extended.Gold_web, 1.00, 0.84, 0.00, 1.0);
			AddColor(Extended.School_bus_yellow, 1.00, 0.85, 0.00, 1.0);
			AddColor(Extended.Arylide_yellow, 0.91, 0.84, 0.42, 1.0);
			AddColor(Extended.Hansa_yellow, 0.91, 0.84, 0.42, 1.0);
			AddColor(Extended.Spanish_bistre, 0.50, 0.46, 0.20, 1.0);
			AddColor(Extended.Golden_yellow, 1.00, 0.87, 0.00, 1.0);
			AddColor(Extended.Sizzling_Sunrise, 1.00, 0.86, 0.00, 1.0);
			AddColor(Extended.Minion_yellow, 0.96, 0.86, 0.31, 1.0);
			AddColor(Extended.Antique_bronze, 0.40, 0.36, 0.12, 1.0);
			AddColor(Extended.Safety_yellow, 0.93, 0.82, 0.01, 1.0);
			AddColor(Extended.Yellow_Pantone, 1.00, 0.87, 0.00, 1.0);
			AddColor(Extended.Citrine, 0.89, 0.82, 0.04, 1.0);
			AddColor(Extended.Misty_moss, 0.73, 0.71, 0.47, 1.0);
			AddColor(Extended.Straw, 0.89, 0.85, 0.44, 1.0);
			AddColor(Extended.Corn, 0.98, 0.93, 0.36, 1.0);
			AddColor(Extended.Maize, 0.98, 0.93, 0.36, 1.0);
			AddColor(Extended.Khaki_X11, 0.94, 0.90, 0.55, 1.0);
			AddColor(Extended.Lemon_chiffon, 1.00, 0.98, 0.80, 1.0);
			AddColor(Extended.Middle_yellow, 1.00, 0.92, 0.00, 1.0);
			AddColor(Extended.Sage, 0.74, 0.72, 0.54, 1.0);
			AddColor(Extended.Green_yellow_Crayola, 0.94, 0.91, 0.57, 1.0);
			AddColor(Extended.Aureolin, 0.99, 0.93, 0.00, 1.0);
			AddColor(Extended.Canary_yellow, 1.00, 0.94, 0.00, 1.0);
			AddColor(Extended.Yellow_process, 1.00, 0.94, 0.00, 1.0);
			AddColor(Extended.Dark_khaki, 0.74, 0.72, 0.42, 1.0);
			AddColor(Extended.Lemon_yellow, 1.00, 0.96, 0.31, 1.0);
			AddColor(Extended.Cream, 1.00, 0.99, 0.82, 1.0);
			AddColor(Extended.Titanium_yellow, 0.93, 0.90, 0.00, 1.0);
			AddColor(Extended.Cadmium_yellow, 1.00, 0.96, 0.00, 1.0);
			AddColor(Extended.Lemon, 1.00, 0.97, 0.00, 1.0);
			AddColor(Extended.Yellow_Sunshine, 1.00, 0.97, 0.00, 1.0);
			AddColor(Extended.Icterine, 0.99, 0.97, 0.37, 1.0);
			AddColor(Extended.Olive_green, 0.71, 0.70, 0.36, 1.0);
			AddColor(Extended.Pale_spring_bud, 0.93, 0.92, 0.74, 1.0);
			AddColor(Extended.Spring_green_Crayola, 0.93, 0.92, 0.74, 1.0);
			AddColor(Extended.Olive, 0.50, 0.50, 0.00, 1.0);
			AddColor(Extended.Xanthic, 0.93, 0.93, 0.04, 1.0);
			AddColor(Extended.Lemon_glacier, 0.99, 1.00, 0.00, 1.0);
			AddColor(Extended.Yellow, 1.00, 1.00, 0.00, 1.0);
			AddColor(Extended.Battleship_grey, 0.52, 0.52, 0.51, 1.0);
			AddColor(Extended.Old_silver, 0.52, 0.52, 0.51, 1.0);
			AddColor(Extended.Maximum_yellow, 0.98, 0.98, 0.22, 1.0);
			AddColor(Extended.Yellow_RYB, 1.00, 1.00, 0.20, 1.0);
			AddColor(Extended.Laser_lemon, 1.00, 1.00, 0.40, 1.0);
			AddColor(Extended.Unmellow_yellow, 1.00, 1.00, 0.40, 1.0);
			AddColor(Extended.Canary, 1.00, 1.00, 0.60, 1.0);
			AddColor(Extended.Lemon_yellow_Crayola, 1.00, 1.00, 0.62, 1.0);
			AddColor(Extended.Light_goldenrod_yellow, 0.98, 0.98, 0.82, 1.0);
			AddColor(Extended.Beige, 0.96, 0.96, 0.86, 1.0);
			AddColor(Extended.Light_yellow, 1.00, 1.00, 0.88, 1.0);
			AddColor(Extended.Ivory, 1.00, 1.00, 0.94, 1.0);
			AddColor(Extended.Baby_powder, 1.00, 1.00, 0.98, 1.0);
			AddColor(Extended.Citron, 0.62, 0.66, 0.12, 1.0);
			AddColor(Extended.Acid_green, 0.69, 0.75, 0.10, 1.0);
			AddColor(Extended.Maximum_green_yellow, 0.85, 0.90, 0.31, 1.0);
			AddColor(Extended.Bitter_lemon, 0.79, 0.88, 0.05, 1.0);
			AddColor(Extended.Pear, 0.82, 0.89, 0.19, 1.0);
			AddColor(Extended.Key_lime, 0.91, 0.96, 0.55, 1.0);
			AddColor(Extended.Chartreuse_traditional, 0.87, 1.00, 0.00, 1.0);
			AddColor(Extended.Army_green, 0.29, 0.33, 0.13, 1.0);
			AddColor(Extended.Black_olive, 0.23, 0.24, 0.21, 1.0);
			AddColor(Extended.Electric_lime, 0.80, 1.00, 0.00, 1.0);
			AddColor(Extended.Volt, 0.80, 1.00, 0.00, 1.0);
			AddColor(Extended.Arctic_lime, 0.82, 1.00, 0.08, 1.0);
			AddColor(Extended.Middle_green_yellow, 0.67, 0.75, 0.38, 1.0);
			AddColor(Extended.Mindaro, 0.89, 0.98, 0.53, 1.0);
			AddColor(Extended.June_bud, 0.74, 0.85, 0.34, 1.0);
			AddColor(Extended.Apple_green, 0.55, 0.71, 0.00, 1.0);
			AddColor(Extended.Android_green, 0.64, 0.78, 0.22, 1.0);
			AddColor(Extended.Moss_green, 0.54, 0.60, 0.36, 1.0);
			AddColor(Extended.Turtle_green, 0.54, 0.60, 0.36, 1.0);
			AddColor(Extended.Bitter_lime, 0.75, 1.00, 0.00, 1.0);
			AddColor(Extended.Lime_CW, 0.75, 1.00, 0.00, 1.0);
			AddColor(Extended.Artichoke, 0.56, 0.59, 0.47, 1.0);
			AddColor(Extended.Yellow_green_Crayola, 0.77, 0.89, 0.52, 1.0);
			AddColor(Extended.Dark_moss_green, 0.29, 0.36, 0.14, 1.0);
			AddColor(Extended.Olive_Drab_3, 0.42, 0.56, 0.14, 1.0);
			AddColor(Extended.Sheen_green, 0.56, 0.83, 0.00, 1.0);
			AddColor(Extended.Spring_bud, 0.65, 0.99, 0.00, 1.0);
			AddColor(Extended.Yellow_green, 0.60, 0.80, 0.20, 1.0);
			AddColor(Extended.Avocado, 0.34, 0.51, 0.01, 1.0);
			AddColor(Extended.Dark_olive_green, 0.33, 0.42, 0.18, 1.0);
			AddColor(Extended.Rifle_green, 0.27, 0.30, 0.22, 1.0);
			AddColor(Extended.Green_Lizard, 0.65, 0.96, 0.20, 1.0);
			AddColor(Extended.Green_yellow, 0.68, 1.00, 0.18, 1.0);
			AddColor(Extended.Inchworm, 0.70, 0.93, 0.36, 1.0);
			AddColor(Extended.Pine_tree, 0.16, 0.18, 0.14, 1.0);
			AddColor(Extended.Olivine, 0.60, 0.73, 0.45, 1.0);
			AddColor(Extended.French_lime, 0.62, 0.99, 0.22, 1.0);
			AddColor(Extended.Maximum_green, 0.37, 0.55, 0.19, 1.0);
			AddColor(Extended.Lawn_green, 0.49, 0.99, 0.00, 1.0);
			AddColor(Extended.Chartreuse_web, 0.50, 1.00, 0.00, 1.0);
			AddColor(Extended.Sap_green, 0.31, 0.49, 0.16, 1.0);
			AddColor(Extended.Asparagus, 0.53, 0.66, 0.42, 1.0);
			AddColor(Extended.Spring_Frost, 0.53, 1.00, 0.16, 1.0);
			AddColor(Extended.Green_RYB, 0.40, 0.69, 0.20, 1.0);
			AddColor(Extended.Laurel_green, 0.66, 0.73, 0.62, 1.0);
			AddColor(Extended.Bright_green, 0.40, 1.00, 0.00, 1.0);
			AddColor(Extended.Pistachio, 0.58, 0.77, 0.45, 1.0);
			AddColor(Extended.Ebony, 0.33, 0.36, 0.31, 1.0);
			AddColor(Extended.Nyanza, 0.91, 1.00, 0.86, 1.0);
			AddColor(Extended.Tea_green, 0.82, 0.94, 0.75, 1.0);
			AddColor(Extended.Kelly_green, 0.30, 0.73, 0.09, 1.0);
			AddColor(Extended.Bud_green, 0.48, 0.71, 0.38, 1.0);
			AddColor(Extended.Kombu_green, 0.21, 0.26, 0.19, 1.0);
			AddColor(Extended.Harlequin, 0.25, 1.00, 0.00, 1.0);
			AddColor(Extended.Lincoln_green, 0.10, 0.35, 0.02, 1.0);
			AddColor(Extended.Fern_green, 0.31, 0.47, 0.26, 1.0);
			AddColor(Extended.Mantis, 0.45, 0.76, 0.40, 1.0);
			AddColor(Extended.Slimy_green, 0.16, 0.59, 0.09, 1.0);
			AddColor(Extended.Neon_green, 0.22, 1.00, 0.08, 1.0);
			AddColor(Extended.Yellow_green_CW, 0.19, 0.70, 0.10, 1.0);
			AddColor(Extended.May_green, 0.30, 0.57, 0.25, 1.0);
			AddColor(Extended.Granny_Smith_apple, 0.66, 0.89, 0.63, 1.0);
			AddColor(Extended.India_green, 0.07, 0.53, 0.03, 1.0);
			AddColor(Extended.Dark_green_X11, 0.00, 0.39, 0.00, 1.0);
			AddColor(Extended.Pakistan_green, 0.00, 0.40, 0.00, 1.0);
			AddColor(Extended.Ao, 0.00, 0.50, 0.00, 1.0);
			AddColor(Extended.Green_web, 0.00, 0.50, 0.00, 1.0);
			AddColor(Extended.Forest_green_web, 0.13, 0.55, 0.13, 1.0);
			AddColor(Extended.Nickel, 0.45, 0.45, 0.45, 1.0);
			AddColor(Extended.Russian_green, 0.40, 0.57, 0.40, 1.0);
			AddColor(Extended.Lime_green, 0.20, 0.80, 0.20, 1.0);
			AddColor(Extended.Electric_green, 0.00, 1.00, 0.00, 1.0);
			AddColor(Extended.Green, 0.00, 1.00, 0.00, 1.0);
			AddColor(Extended.Lime_web, 0.00, 1.00, 0.00, 1.0);
			AddColor(Extended.Dark_sea_green, 0.56, 0.74, 0.56, 1.0);
			AddColor(Extended.Screamin_Green, 0.40, 1.00, 0.40, 1.0);
			AddColor(Extended.Light_green, 0.56, 0.93, 0.56, 1.0);
			AddColor(Extended.Mint_green, 0.60, 1.00, 0.60, 1.0);
			AddColor(Extended.Honeydew, 0.94, 1.00, 0.94, 1.0);
			AddColor(Extended.Celadon, 0.67, 0.88, 0.69, 1.0);
			AddColor(Extended.Hunter_green, 0.21, 0.37, 0.23, 1.0);
			AddColor(Extended.Middle_green, 0.30, 0.55, 0.34, 1.0);
			AddColor(Extended.Eton_blue, 0.59, 0.78, 0.64, 1.0);
			AddColor(Extended.Erin, 0.00, 1.00, 0.25, 1.0);
			AddColor(Extended.Ash_gray, 0.70, 0.75, 0.71, 1.0);
			AddColor(Extended.Xanadu, 0.45, 0.53, 0.47, 1.0);
			AddColor(Extended.Dark_pastel_green, 0.01, 0.75, 0.24, 1.0);
			AddColor(Extended.Malachite, 0.04, 0.85, 0.32, 1.0);
			AddColor(Extended.Forest_green_Crayola, 0.37, 0.65, 0.47, 1.0);
			AddColor(Extended.Emerald, 0.31, 0.78, 0.47, 1.0);
			AddColor(Extended.Paris_Green, 0.31, 0.78, 0.47, 1.0);
			AddColor(Extended.Cambridge_blue, 0.64, 0.76, 0.68, 1.0);
			AddColor(Extended.Shiny_Shamrock, 0.37, 0.65, 0.47, 1.0);
			AddColor(Extended.Turquoise_green, 0.63, 0.84, 0.71, 1.0);
			AddColor(Extended.Feldgrau, 0.30, 0.36, 0.33, 1.0);
			AddColor(Extended.Green_Pantone, 0.00, 0.68, 0.26, 1.0);
			AddColor(Extended.Sea_green, 0.18, 0.55, 0.34, 1.0);
			AddColor(Extended.Amazon, 0.23, 0.48, 0.34, 1.0);
			AddColor(Extended.Medium_sea_green, 0.24, 0.70, 0.44, 1.0);
			AddColor(Extended.Forest_green_traditional, 0.00, 0.27, 0.13, 1.0);
			AddColor(Extended.UP_Forest_green, 0.00, 0.27, 0.13, 1.0);
			AddColor(Extended.Green_pigment, 0.00, 0.65, 0.31, 1.0);
			AddColor(Extended.Dark_spring_green, 0.09, 0.45, 0.27, 1.0);
			AddColor(Extended.Spring_green, 0.00, 1.00, 0.50, 1.0);
			AddColor(Extended.Mint_cream, 0.96, 1.00, 0.98, 1.0);
			AddColor(Extended.Phthalo_green, 0.07, 0.21, 0.14, 1.0);
			AddColor(Extended.Aero_blue, 0.75, 0.91, 0.84, 1.0);
			AddColor(Extended.Dartmouth_green, 0.00, 0.44, 0.24, 1.0);
			AddColor(Extended.Spanish_green, 0.00, 0.57, 0.31, 1.0);
			AddColor(Extended.Morning_blue, 0.55, 0.64, 0.60, 1.0);
			AddColor(Extended.Magic_mint, 0.67, 0.94, 0.82, 1.0);
			AddColor(Extended.British_racing_green, 0.00, 0.26, 0.15, 1.0);
			AddColor(Extended.Cadmium_green, 0.00, 0.42, 0.24, 1.0);
			AddColor(Extended.Medium_aquamarine, 0.40, 0.87, 0.67, 1.0);
			AddColor(Extended.Shamrock_green, 0.00, 0.62, 0.38, 1.0);
			AddColor(Extended.GO_green, 0.00, 0.67, 0.40, 1.0);
			AddColor(Extended.Medium_spring_green, 0.00, 0.98, 0.60, 1.0);
			AddColor(Extended.Ocean_green, 0.28, 0.75, 0.57, 1.0);
			AddColor(Extended.Dark_green, 0.00, 0.20, 0.13, 1.0);
			AddColor(Extended.Jade, 0.00, 0.66, 0.42, 1.0);
			AddColor(Extended.Green_Crayola, 0.11, 0.67, 0.47, 1.0);
			AddColor(Extended.Mint, 0.24, 0.71, 0.54, 1.0);
			AddColor(Extended.Sacramento_State_green, 0.02, 0.22, 0.15, 1.0);
			AddColor(Extended.Green_cyan, 0.00, 0.60, 0.40, 1.0);
			AddColor(Extended.Green_NCS, 0.00, 0.62, 0.42, 1.0);
			AddColor(Extended.Aquamarine, 0.50, 1.00, 0.83, 1.0);
			AddColor(Extended.Viridian, 0.25, 0.51, 0.43, 1.0);
			AddColor(Extended.Mountain_Meadow, 0.19, 0.73, 0.56, 1.0);
			AddColor(Extended.Dark_jungle_green, 0.10, 0.14, 0.13, 1.0);
			AddColor(Extended.Brunswick_green, 0.11, 0.30, 0.24, 1.0);
			AddColor(Extended.English_green, 0.11, 0.30, 0.24, 1.0);
			AddColor(Extended.Spanish_viridian, 0.00, 0.50, 0.36, 1.0);
			AddColor(Extended.Green_Munsell, 0.00, 0.66, 0.47, 1.0);
			AddColor(Extended.Hookers_green, 0.29, 0.47, 0.42, 1.0);
			AddColor(Extended.Jungle_green, 0.16, 0.67, 0.53, 1.0);
			AddColor(Extended.Castleton_green, 0.00, 0.34, 0.25, 1.0);
			AddColor(Extended.Bottle_green, 0.00, 0.42, 0.31, 1.0);
			AddColor(Extended.Illuminating_emerald, 0.19, 0.57, 0.47, 1.0);
			AddColor(Extended.Opal, 0.66, 0.76, 0.74, 1.0);
			AddColor(Extended.Caribbean_green, 0.00, 0.80, 0.60, 1.0);
			AddColor(Extended.Zomp, 0.22, 0.65, 0.56, 1.0);
			AddColor(Extended.Polished_Pine, 0.36, 0.64, 0.58, 1.0);
			AddColor(Extended.MSU_green, 0.09, 0.27, 0.23, 1.0);
			AddColor(Extended.Wintergreen_Dream, 0.34, 0.53, 0.49, 1.0);
			AddColor(Extended.Blue_green_CW, 0.02, 0.31, 0.25, 1.0);
			AddColor(Extended.Tropical_rainforest, 0.00, 0.46, 0.37, 1.0);
			AddColor(Extended.Generic_viridian, 0.00, 0.50, 0.40, 1.0);
			AddColor(Extended.Paolo_Veronese_green, 0.00, 0.61, 0.49, 1.0);
			AddColor(Extended.Sea_green_Crayola, 0.00, 1.00, 0.80, 1.0);
			AddColor(Extended.Green_Sheen, 0.43, 0.68, 0.63, 1.0);
			AddColor(Extended.Middle_blue_green, 0.55, 0.85, 0.80, 1.0);
			AddColor(Extended.Keppel, 0.23, 0.69, 0.62, 1.0);
			AddColor(Extended.Persian_green, 0.00, 0.65, 0.58, 1.0);
			AddColor(Extended.Celadon_green, 0.18, 0.52, 0.49, 1.0);
			AddColor(Extended.Turquoise, 0.25, 0.88, 0.82, 1.0);
			AddColor(Extended.Pine_green, 0.00, 0.47, 0.44, 1.0);
			AddColor(Extended.Myrtle_green, 0.19, 0.47, 0.45, 1.0);
			AddColor(Extended.Turquoise_blue, 0.00, 1.00, 0.94, 1.0);
			AddColor(Extended.Light_sea_green, 0.13, 0.70, 0.67, 1.0);
			AddColor(Extended.Verdigris, 0.26, 0.70, 0.68, 1.0);
			AddColor(Extended.Deep_jungle_green, 0.00, 0.29, 0.29, 1.0);
			AddColor(Extended.Tiffany_Blue, 0.04, 0.73, 0.71, 1.0);
			AddColor(Extended.Fluorescent_blue, 0.08, 0.96, 0.93, 1.0);
			AddColor(Extended.Medium_turquoise, 0.28, 0.82, 0.80, 1.0);
			AddColor(Extended.Rich_black, 0.00, 0.25, 0.25, 1.0);
			AddColor(Extended.Warm_black, 0.00, 0.26, 0.26, 1.0);
			AddColor(Extended.Charleston_green, 0.14, 0.17, 0.17, 1.0);
			AddColor(Extended.Skobeloff, 0.00, 0.45, 0.45, 1.0);
			AddColor(Extended.Dark_slate_gray, 0.18, 0.31, 0.31, 1.0);
			AddColor(Extended.Teal, 0.00, 0.50, 0.50, 1.0);
			AddColor(Extended.Dark_cyan, 0.00, 0.55, 0.55, 1.0);
			AddColor(Extended.Robin_egg_blue, 0.00, 0.80, 0.80, 1.0);
			AddColor(Extended.Maximum_blue_green, 0.19, 0.75, 0.75, 1.0);
			AddColor(Extended.Aqua, 0.00, 1.00, 1.00, 1.0);
			AddColor(Extended.Cyan, 0.00, 1.00, 1.00, 1.0);
			AddColor(Extended.Spanish_sky_blue, 0.00, 1.00, 1.00, 1.0);
			AddColor(Extended.Celeste, 0.70, 1.00, 1.00, 1.0);
			AddColor(Extended.Italian_sky_blue, 0.70, 1.00, 1.00, 1.0);
			AddColor(Extended.Light_cyan, 0.88, 1.00, 1.00, 1.0);
			AddColor(Extended.Azure_X11, 0.94, 1.00, 1.00, 1.0);
			AddColor(Extended.Viridian_green, 0.00, 0.59, 0.60, 1.0);
			AddColor(Extended.Dark_turquoise, 0.00, 0.81, 0.82, 1.0);
			AddColor(Extended.Steel_Teal, 0.37, 0.54, 0.55, 1.0);
			AddColor(Extended.Cadet_blue, 0.37, 0.62, 0.63, 1.0);
			AddColor(Extended.Electric_blue, 0.49, 0.98, 1.00, 1.0);
			AddColor(Extended.Metallic_Seaweed, 0.04, 0.49, 0.55, 1.0);
			AddColor(Extended.Midnight_green, 0.00, 0.29, 0.33, 1.0);
			AddColor(Extended.Powder_blue, 0.69, 0.88, 0.90, 1.0);
			AddColor(Extended.Ming, 0.21, 0.45, 0.49, 1.0);
			AddColor(Extended.Blizzard_blue, 0.67, 0.90, 0.93, 1.0);
			AddColor(Extended.Outer_space_Crayola, 0.18, 0.22, 0.23, 1.0);
			AddColor(Extended.Blue_Munsell, 0.00, 0.58, 0.69, 1.0);
			AddColor(Extended.Sky_blue_Crayola, 0.46, 0.84, 0.92, 1.0);
			AddColor(Extended.Middle_blue, 0.49, 0.83, 0.90, 1.0);
			AddColor(Extended.Pacific_blue, 0.11, 0.66, 0.79, 1.0);
			AddColor(Extended.Blue_green, 0.05, 0.60, 0.73, 1.0);
			AddColor(Extended.Vivid_sky_blue, 0.00, 0.80, 1.00, 1.0);
			AddColor(Extended.Cyan_process, 0.00, 0.72, 0.92, 1.0);
			AddColor(Extended.Non_photo_blue, 0.64, 0.87, 0.93, 1.0);
			AddColor(Extended.Deep_Space_Sparkle, 0.29, 0.39, 0.42, 1.0);
			AddColor(Extended.Teal_blue, 0.21, 0.46, 0.53, 1.0);
			AddColor(Extended.Cerulean_Crayola, 0.11, 0.67, 0.84, 1.0);
			AddColor(Extended.Onyx, 0.21, 0.22, 0.22, 1.0);
			AddColor(Extended.Capri, 0.00, 0.75, 1.00, 1.0);
			AddColor(Extended.Deep_sky_blue, 0.00, 0.75, 1.00, 1.0);
			AddColor(Extended.Maximum_blue, 0.28, 0.67, 0.80, 1.0);
			AddColor(Extended.Light_blue, 0.68, 0.85, 0.90, 1.0);
			AddColor(Extended.CG_blue, 0.00, 0.48, 0.65, 1.0);
			AddColor(Extended.Celadon_blue, 0.00, 0.48, 0.65, 1.0);
			AddColor(Extended.Cerulean, 0.00, 0.48, 0.65, 1.0);
			AddColor(Extended.Blue_sapphire, 0.07, 0.38, 0.50, 1.0);
			AddColor(Extended.Blue_NCS, 0.00, 0.53, 0.74, 1.0);
			AddColor(Extended.Sky_blue, 0.53, 0.81, 0.92, 1.0);
			AddColor(Extended.Cadet, 0.33, 0.41, 0.45, 1.0);
			AddColor(Extended.Dark_sky_blue, 0.55, 0.75, 0.84, 1.0);
			AddColor(Extended.Baby_blue, 0.54, 0.81, 0.94, 1.0);
			AddColor(Extended.Gunmetal, 0.16, 0.20, 0.22, 1.0);
			AddColor(Extended.Star_command_blue, 0.00, 0.48, 0.72, 1.0);
			AddColor(Extended.Pewter_Blue, 0.55, 0.66, 0.72, 1.0);
			AddColor(Extended.Silver_sand, 0.75, 0.76, 0.76, 1.0);
			AddColor(Extended.Light_cornflower_blue, 0.58, 0.80, 0.92, 1.0);
			AddColor(Extended.Columbia_Blue, 0.73, 0.85, 0.92, 1.0);
			AddColor(Extended.Uranian_blue, 0.69, 0.86, 0.96, 1.0);
			AddColor(Extended.Indigo_dye, 0.00, 0.25, 0.42, 1.0);
			AddColor(Extended.Sapphire_blue, 0.00, 0.40, 0.65, 1.0);
			AddColor(Extended.Honolulu_blue, 0.00, 0.43, 0.69, 1.0);
			AddColor(Extended.Spanish_blue, 0.00, 0.44, 0.72, 1.0);
			AddColor(Extended.French_blue, 0.00, 0.45, 0.73, 1.0);
			AddColor(Extended.Light_sky_blue, 0.53, 0.81, 0.98, 1.0);
			AddColor(Extended.Charcoal, 0.21, 0.27, 0.31, 1.0);
			AddColor(Extended.Green_blue_Crayola, 0.16, 0.53, 0.78, 1.0);
			AddColor(Extended.Carolina_blue, 0.34, 0.63, 0.83, 1.0);
			AddColor(Extended.Prussian_blue, 0.00, 0.19, 0.33, 1.0);
			AddColor(Extended.Air_superiority_blue, 0.45, 0.63, 0.76, 1.0);
			AddColor(Extended.Cadet_grey, 0.57, 0.64, 0.69, 1.0);
			AddColor(Extended.Maya_blue, 0.45, 0.76, 0.98, 1.0);
			AddColor(Extended.Pale_cerulean, 0.61, 0.77, 0.89, 1.0);
			AddColor(Extended.Dark_electric_blue, 0.33, 0.41, 0.47, 1.0);
			AddColor(Extended.Paynes_grey, 0.33, 0.41, 0.47, 1.0);
			AddColor(Extended.Blue_jeans, 0.36, 0.68, 0.93, 1.0);
			AddColor(Extended.Aero, 0.49, 0.73, 0.91, 1.0);
			AddColor(Extended.Beau_blue, 0.74, 0.83, 0.90, 1.0);
			AddColor(Extended.Pale_aqua, 0.74, 0.83, 0.90, 1.0);
			AddColor(Extended.Rich_black_FOGRA29, 0.00, 0.04, 0.07, 1.0);
			AddColor(Extended.True_Blue, 0.00, 0.45, 0.81, 1.0);
			AddColor(Extended.Steel_blue, 0.27, 0.51, 0.71, 1.0);
			AddColor(Extended.Iceberg, 0.44, 0.65, 0.82, 1.0);
			AddColor(Extended.Cerulean_frost, 0.43, 0.61, 0.76, 1.0);
			AddColor(Extended.Alice_blue, 0.94, 0.97, 1.00, 1.0);
			AddColor(Extended.USAFA_blue, 0.00, 0.31, 0.60, 1.0);
			AddColor(Extended.Black_coral, 0.33, 0.38, 0.44, 1.0);
			AddColor(Extended.Green_blue, 0.07, 0.39, 0.71, 1.0);
			AddColor(Extended.Baby_blue_eyes, 0.63, 0.79, 0.95, 1.0);
			AddColor(Extended.Rich_black_FOGRA39, 0.00, 0.01, 0.01, 1.0);
			AddColor(Extended.Yale_Blue, 0.00, 0.21, 0.42, 1.0);
			AddColor(Extended.Lapis_lazuli, 0.15, 0.38, 0.61, 1.0);
			AddColor(Extended.Bright_navy_blue, 0.10, 0.45, 0.82, 1.0);
			AddColor(Extended.Navy_blue_Crayola, 0.10, 0.45, 0.82, 1.0);
			AddColor(Extended.Slate_gray, 0.44, 0.50, 0.56, 1.0);
			AddColor(Extended.Azure, 0.00, 0.50, 1.00, 1.0);
			AddColor(Extended.Light_slate_gray, 0.47, 0.53, 0.60, 1.0);
			AddColor(Extended.Bleu_de_France, 0.19, 0.55, 0.91, 1.0);
			AddColor(Extended.Tufts_blue, 0.24, 0.56, 0.87, 1.0);
			AddColor(Extended.Dodger_blue, 0.12, 0.56, 1.00, 1.0);
			AddColor(Extended.Blue_gray, 0.40, 0.60, 0.80, 1.0);
			AddColor(Extended.Livid, 0.40, 0.60, 0.80, 1.0);
			AddColor(Extended.Queen_blue, 0.26, 0.42, 0.58, 1.0);
			AddColor(Extended.Oxford_blue, 0.00, 0.13, 0.28, 1.0);
			AddColor(Extended.Little_boy_blue, 0.42, 0.63, 0.86, 1.0);
			AddColor(Extended.French_sky_blue, 0.47, 0.71, 1.00, 1.0);
			AddColor(Extended.Denim, 0.08, 0.38, 0.74, 1.0);
			AddColor(Extended.Shadow_blue, 0.47, 0.55, 0.65, 1.0);
			AddColor(Extended.Light_steel_blue, 0.69, 0.77, 0.87, 1.0);
			AddColor(Extended.Cobalt_blue, 0.00, 0.28, 0.67, 1.0);
			AddColor(Extended.Bdazzled_blue, 0.18, 0.35, 0.58, 1.0);
			AddColor(Extended.Sapphire_Crayola, 0.18, 0.36, 0.63, 1.0);
			AddColor(Extended.Celtic_blue, 0.14, 0.42, 0.81, 1.0);
			AddColor(Extended.Sapphire, 0.06, 0.32, 0.73, 1.0);
			AddColor(Extended.Glaucous, 0.38, 0.51, 0.71, 1.0);
			AddColor(Extended.United_Nations_blue, 0.36, 0.57, 0.90, 1.0);
			AddColor(Extended.Absolute_Zero, 0.00, 0.28, 0.73, 1.0);
			AddColor(Extended.Blue_yonder, 0.31, 0.45, 0.65, 1.0);
			AddColor(Extended.Blue_Crayola, 0.12, 0.46, 1.00, 1.0);
			AddColor(Extended.Royal_blue_dark, 0.00, 0.14, 0.40, 1.0);
			AddColor(Extended.YInMn_Blue, 0.18, 0.31, 0.56, 1.0);
			AddColor(Extended.Cornflower_blue, 0.39, 0.58, 0.93, 1.0);
			AddColor(Extended.Cadet_blue_Crayola, 0.66, 0.70, 0.76, 1.0);
			AddColor(Extended.Roman_silver, 0.51, 0.54, 0.59, 1.0);
			AddColor(Extended.UA_blue, 0.00, 0.20, 0.67, 1.0);
			AddColor(Extended.Dark_cornflower_blue, 0.15, 0.26, 0.55, 1.0);
			AddColor(Extended.Han_blue, 0.27, 0.42, 0.81, 1.0);
			AddColor(Extended.Periwinkle_Crayola, 0.76, 0.80, 0.90, 1.0);
			AddColor(Extended.Resolution_blue, 0.00, 0.14, 0.53, 1.0);
			AddColor(Extended.Cerulean_blue, 0.16, 0.32, 0.75, 1.0);
			AddColor(Extended.Blue_RYB, 0.01, 0.28, 1.00, 1.0);
			AddColor(Extended.Bluetiful, 0.24, 0.41, 0.91, 1.0);
			AddColor(Extended.Royal_blue_light, 0.25, 0.41, 0.88, 1.0);
			AddColor(Extended.Space_cadet, 0.11, 0.16, 0.32, 1.0);
			AddColor(Extended.Egyptian_blue, 0.06, 0.20, 0.65, 1.0);
			AddColor(Extended.Wild_blue_yonder, 0.64, 0.68, 0.82, 1.0);
			AddColor(Extended.Denim_blue, 0.13, 0.26, 0.71, 1.0);
			AddColor(Extended.Ultramarine_blue, 0.25, 0.40, 0.96, 1.0);
			AddColor(Extended.Light_periwinkle, 0.77, 0.80, 0.88, 1.0);
			AddColor(Extended.Persian_blue, 0.11, 0.22, 0.73, 1.0);
			AddColor(Extended.Violet_blue, 0.20, 0.29, 0.70, 1.0);
			AddColor(Extended.Cool_grey, 0.55, 0.57, 0.67, 1.0);
			AddColor(Extended.Neon_blue, 0.27, 0.40, 1.00, 1.0);
			AddColor(Extended.Blue_Pantone, 0.00, 0.09, 0.66, 1.0);
			AddColor(Extended.Independence, 0.30, 0.32, 0.43, 1.0);
			AddColor(Extended.Manatee, 0.59, 0.60, 0.67, 1.0);
			AddColor(Extended.Phthalo_blue, 0.00, 0.06, 0.54, 1.0);
			AddColor(Extended.Zaffre, 0.00, 0.08, 0.66, 1.0);
			AddColor(Extended.St_Patricks_blue, 0.14, 0.16, 0.48, 1.0);
			AddColor(Extended.Purple_navy, 0.31, 0.32, 0.50, 1.0);
			AddColor(Extended.Liberty, 0.33, 0.35, 0.65, 1.0);
			AddColor(Extended.Navy_blue, 0.00, 0.00, 0.50, 1.0);
			AddColor(Extended.Midnight_blue, 0.10, 0.10, 0.44, 1.0);
			AddColor(Extended.Duke_blue, 0.00, 0.00, 0.61, 1.0);
			AddColor(Extended.Blue_pigment, 0.20, 0.20, 0.60, 1.0);
			AddColor(Extended.Medium_blue, 0.00, 0.00, 0.80, 1.0);
			AddColor(Extended.Dark_blue_gray, 0.40, 0.40, 0.60, 1.0);
			AddColor(Extended.Blue, 0.00, 0.00, 1.00, 1.0);
			AddColor(Extended.Blue_bell, 0.64, 0.64, 0.82, 1.0);
			AddColor(Extended.Maximum_blue_purple, 0.67, 0.67, 0.90, 1.0);
			AddColor(Extended.Lavender_blue, 0.80, 0.80, 1.00, 1.0);
			AddColor(Extended.Periwinkle, 0.80, 0.80, 1.00, 1.0);
			AddColor(Extended.Lavender_web, 0.90, 0.90, 0.98, 1.0);
			AddColor(Extended.Ghost_white, 0.97, 0.97, 1.00, 1.0);
			AddColor(Extended.Cosmic_cobalt, 0.18, 0.18, 0.53, 1.0);
			AddColor(Extended.Rhythm, 0.47, 0.46, 0.59, 1.0);
			AddColor(Extended.Ultramarine, 0.07, 0.04, 0.56, 1.0);
			AddColor(Extended.Picotee_blue, 0.18, 0.15, 0.53, 1.0);
			AddColor(Extended.Iris, 0.35, 0.31, 0.81, 1.0);
			AddColor(Extended.Lavender_gray, 0.77, 0.76, 0.82, 1.0);
			AddColor(Extended.Violet_blue_Crayola, 0.46, 0.43, 0.78, 1.0);
			AddColor(Extended.Ocean_Blue, 0.31, 0.26, 0.71, 1.0);
			AddColor(Extended.Majorelle_blue, 0.38, 0.31, 0.86, 1.0);
			AddColor(Extended.Trypan_Blue, 0.11, 0.02, 0.70, 1.0);
			AddColor(Extended.Dark_slate_blue, 0.28, 0.24, 0.55, 1.0);
			AddColor(Extended.Slate_blue, 0.42, 0.35, 0.80, 1.0);
			AddColor(Extended.Blue_violet_Crayola, 0.45, 0.40, 0.74, 1.0);
			AddColor(Extended.Medium_slate_blue, 0.48, 0.41, 0.93, 1.0);
			AddColor(Extended.Plump_Purple, 0.35, 0.27, 0.70, 1.0);
			AddColor(Extended.Han_purple, 0.32, 0.09, 0.98, 1.0);
			AddColor(Extended.Silver_Metallic, 0.67, 0.66, 0.68, 1.0);
			AddColor(Extended.Persian_indigo, 0.20, 0.07, 0.48, 1.0);
			AddColor(Extended.Middle_blue_purple, 0.55, 0.45, 0.75, 1.0);
			AddColor(Extended.Medium_purple, 0.58, 0.44, 0.86, 1.0);
			AddColor(Extended.Cyber_grape, 0.35, 0.26, 0.49, 1.0);
			AddColor(Extended.Spanish_violet, 0.30, 0.16, 0.51, 1.0);
			AddColor(Extended.Indigo, 0.29, 0.00, 0.51, 1.0);
			AddColor(Extended.KSU_purple, 0.31, 0.15, 0.51, 1.0);
			AddColor(Extended.Electric_indigo, 0.44, 0.00, 1.00, 1.0);
			AddColor(Extended.Royal_purple, 0.47, 0.32, 0.66, 1.0);
			AddColor(Extended.Purple_mountain_majesty, 0.59, 0.47, 0.71, 1.0);
			AddColor(Extended.Russian_violet, 0.20, 0.09, 0.30, 1.0);
			AddColor(Extended.Blue_violet_CW, 0.30, 0.10, 0.50, 1.0);
			AddColor(Extended.Rebecca_Purple, 0.40, 0.20, 0.60, 1.0);
			AddColor(Extended.Violet_CW, 0.50, 0.00, 1.00, 1.0);
			AddColor(Extended.Amethyst, 0.60, 0.40, 0.80, 1.0);
			AddColor(Extended.Blue_violet, 0.54, 0.17, 0.89, 1.0);
			AddColor(Extended.Electric_violet, 0.56, 0.00, 1.00, 1.0);
			AddColor(Extended.Violet, 0.56, 0.00, 1.00, 1.0);
			AddColor(Extended.Purple, 0.38, 0.00, 0.50, 1.0);
			AddColor(Extended.Lavender_floral, 0.71, 0.49, 0.86, 1.0);
			AddColor(Extended.Mauve, 0.88, 0.69, 1.00, 1.0);
			AddColor(Extended.Vivid_violet, 0.62, 0.00, 1.00, 1.0);
			AddColor(Extended.Purple_X11, 0.63, 0.13, 0.94, 1.0);
			AddColor(Extended.Veronica, 0.63, 0.13, 0.94, 1.0);
			AddColor(Extended.Languid_lavender, 0.84, 0.79, 0.87, 1.0);
			AddColor(Extended.French_violet, 0.53, 0.02, 0.81, 1.0);
			AddColor(Extended.Dark_orchid, 0.60, 0.20, 0.80, 1.0);
			AddColor(Extended.Wisteria, 0.79, 0.63, 0.86, 1.0);
			AddColor(Extended.Dark_violet, 0.58, 0.00, 0.83, 1.0);
			AddColor(Extended.Eminence, 0.42, 0.19, 0.51, 1.0);
			AddColor(Extended.Electric_purple, 0.75, 0.00, 1.00, 1.0);
			AddColor(Extended.Purple_Plum, 0.61, 0.32, 0.71, 1.0);
			AddColor(Extended.Glossy_grape, 0.67, 0.57, 0.70, 1.0);
			AddColor(Extended.Bright_lilac, 0.85, 0.57, 0.94, 1.0);
			AddColor(Extended.Violet_RYB, 0.53, 0.00, 0.69, 1.0);
			AddColor(Extended.Heliotrope, 0.87, 0.45, 1.00, 1.0);
			AddColor(Extended.Purple_Munsell, 0.62, 0.00, 0.77, 1.0);
			AddColor(Extended.Purpureus, 0.60, 0.31, 0.68, 1.0);
			AddColor(Extended.Medium_orchid, 0.73, 0.33, 0.83, 1.0);
			AddColor(Extended.African_violet, 0.70, 0.52, 0.75, 1.0);
			AddColor(Extended.English_violet, 0.34, 0.24, 0.36, 1.0);
			AddColor(Extended.Maximum_purple, 0.45, 0.20, 0.50, 1.0);
			AddColor(Extended.French_lilac, 0.53, 0.38, 0.56, 1.0);
			AddColor(Extended.Pomp_and_Power, 0.53, 0.38, 0.56, 1.0);
			AddColor(Extended.Dark_purple, 0.19, 0.10, 0.20, 1.0);
			AddColor(Extended.Phlox, 0.87, 0.00, 1.00, 1.0);
			AddColor(Extended.Psychedelic_purple, 0.87, 0.00, 1.00, 1.0);
			AddColor(Extended.Chinese_violet, 0.52, 0.38, 0.53, 1.0);
			AddColor(Extended.Raisin_black, 0.14, 0.13, 0.14, 1.0);
			AddColor(Extended.Patriarch, 0.50, 0.00, 0.50, 1.0);
			AddColor(Extended.Purple_web, 0.50, 0.00, 0.50, 1.0);
			AddColor(Extended.Dark_magenta, 0.55, 0.00, 0.55, 1.0);
			AddColor(Extended.Midnight, 0.44, 0.15, 0.44, 1.0);
			AddColor(Extended.Steel_pink, 0.80, 0.20, 0.80, 1.0);
			AddColor(Extended.Fuchsia, 1.00, 0.00, 1.00, 1.0);
			AddColor(Extended.Magenta, 1.00, 0.00, 1.00, 1.0);
			AddColor(Extended.Fuchsia_Crayola, 0.76, 0.33, 0.76, 1.0);
			AddColor(Extended.French_mauve, 0.83, 0.45, 0.83, 1.0);
			AddColor(Extended.Lilac, 0.78, 0.64, 0.78, 1.0);
			AddColor(Extended.Violet_web, 0.93, 0.51, 0.93, 1.0);
			AddColor(Extended.Pink_flamingo, 0.99, 0.45, 0.99, 1.0);
			AddColor(Extended.Shocking_pink_Crayola, 1.00, 0.44, 1.00, 1.0);
			AddColor(Extended.Ultra_pink, 1.00, 0.44, 1.00, 1.0);
			AddColor(Extended.Plum_web, 0.87, 0.63, 0.87, 1.0);
			AddColor(Extended.Thistle, 0.85, 0.75, 0.85, 1.0);
			AddColor(Extended.Pale_purple_Pantone, 0.98, 0.90, 0.98, 1.0);
			AddColor(Extended.Mardi_Gras, 0.53, 0.00, 0.52, 1.0);
			AddColor(Extended.Orchid, 0.85, 0.44, 0.84, 1.0);
			AddColor(Extended.Heliotrope_gray, 0.67, 0.60, 0.66, 1.0);
			AddColor(Extended.Rose_quartz, 0.67, 0.60, 0.66, 1.0);
			AddColor(Extended.Old_lavender, 0.47, 0.41, 0.47, 1.0);
			AddColor(Extended.Japanese_violet, 0.36, 0.20, 0.34, 1.0);
			AddColor(Extended.Plum, 0.56, 0.27, 0.52, 1.0);
			AddColor(Extended.Palatinate_purple, 0.41, 0.16, 0.38, 1.0);
			AddColor(Extended.Razzmic_Berry, 0.55, 0.31, 0.52, 1.0);
			AddColor(Extended.Byzantium, 0.44, 0.16, 0.39, 1.0);
			AddColor(Extended.Byzantine, 0.74, 0.20, 0.64, 1.0);
			AddColor(Extended.Lilac_Luster, 0.68, 0.60, 0.67, 1.0);
			AddColor(Extended.Pink_lavender, 0.85, 0.70, 0.82, 1.0);
			AddColor(Extended.Purple_pizzazz, 1.00, 0.31, 0.85, 1.0);
			AddColor(Extended.Hot_magenta, 1.00, 0.11, 0.81, 1.0);
			AddColor(Extended.Orchid_Crayola, 0.89, 0.61, 0.82, 1.0);
			AddColor(Extended.Dark_byzantium, 0.36, 0.22, 0.33, 1.0);
			AddColor(Extended.Shocking_pink, 0.99, 0.06, 0.75, 1.0);
			AddColor(Extended.Razzle_dazzle_rose, 1.00, 0.20, 0.80, 1.0);
			AddColor(Extended.Violet_Crayola, 0.59, 0.24, 0.50, 1.0);
			AddColor(Extended.Antique_fuchsia, 0.57, 0.36, 0.51, 1.0);
			AddColor(Extended.Pearly_purple, 0.72, 0.41, 0.64, 1.0);
			AddColor(Extended.Opera_mauve, 0.72, 0.52, 0.65, 1.0);
			AddColor(Extended.Pink_lace, 1.00, 0.87, 0.96, 1.0);
			AddColor(Extended.Flirt, 0.64, 0.00, 0.43, 1.0);
			AddColor(Extended.Fandango, 0.71, 0.20, 0.54, 1.0);
			AddColor(Extended.Fashion_fuchsia, 0.96, 0.00, 0.63, 1.0);
			AddColor(Extended.Hollywood_cerise, 0.96, 0.00, 0.63, 1.0);
			AddColor(Extended.Taupe_gray, 0.55, 0.52, 0.54, 1.0);
			AddColor(Extended.Sky_magenta, 0.81, 0.44, 0.69, 1.0);
			AddColor(Extended.Rose_pink, 1.00, 0.40, 0.80, 1.0);
			AddColor(Extended.Medium_violet_red, 0.78, 0.08, 0.52, 1.0);
			AddColor(Extended.Red_violet, 0.78, 0.08, 0.52, 1.0);
			AddColor(Extended.Frostbite, 0.91, 0.21, 0.65, 1.0);
			AddColor(Extended.Mountbatten_pink, 0.60, 0.48, 0.55, 1.0);
			AddColor(Extended.Mulberry_Crayola, 0.78, 0.31, 0.61, 1.0);
			AddColor(Extended.Super_pink, 0.81, 0.42, 0.66, 1.0);
			AddColor(Extended.Red_violet_Crayola, 0.75, 0.27, 0.56, 1.0);
			AddColor(Extended.Tyrian_purple, 0.40, 0.01, 0.24, 1.0);
			AddColor(Extended.Sugar_Plum, 0.57, 0.31, 0.46, 1.0);
			AddColor(Extended.Maximum_red_purple, 0.65, 0.23, 0.47, 1.0);
			AddColor(Extended.Middle_purple, 0.85, 0.51, 0.71, 1.0);
			AddColor(Extended.Magenta_process, 1.00, 0.00, 0.56, 1.0);
			AddColor(Extended.Persian_rose, 1.00, 0.16, 0.64, 1.0);
			AddColor(Extended.Magenta_haze, 0.62, 0.27, 0.46, 1.0);
			AddColor(Extended.Mexican_pink, 0.89, 0.00, 0.49, 1.0);
			AddColor(Extended.Barbie_Pink, 0.85, 0.09, 0.52, 1.0);
			AddColor(Extended.Jazzberry_jam, 0.65, 0.04, 0.37, 1.0);
			AddColor(Extended.Amaranth_MP, 0.62, 0.17, 0.41, 1.0);
			AddColor(Extended.Red_purple, 0.89, 0.00, 0.47, 1.0);
			AddColor(Extended.Magenta_dye, 0.79, 0.12, 0.48, 1.0);
			AddColor(Extended.Mulberry, 0.77, 0.29, 0.55, 1.0);
			AddColor(Extended.Deep_pink, 1.00, 0.08, 0.58, 1.0);
			AddColor(Extended.Pink_Pantone, 0.84, 0.28, 0.58, 1.0);
			AddColor(Extended.Pansy_purple, 0.47, 0.09, 0.29, 1.0);
			AddColor(Extended.Eggplant, 0.38, 0.25, 0.32, 1.0);
			AddColor(Extended.Twilight_lavender, 0.54, 0.29, 0.42, 1.0);
			AddColor(Extended.Mystic_maroon, 0.68, 0.26, 0.47, 1.0);
			AddColor(Extended.Smitten, 0.78, 0.25, 0.53, 1.0);
			AddColor(Extended.Wild_Strawberry, 1.00, 0.26, 0.64, 1.0);
			AddColor(Extended.Magenta_Crayola, 0.96, 0.33, 0.65, 1.0);
			AddColor(Extended.Persian_pink, 0.97, 0.50, 0.75, 1.0);
			AddColor(Extended.Kobi, 0.91, 0.62, 0.77, 1.0);
			AddColor(Extended.Dark_liver, 0.33, 0.29, 0.31, 1.0);
			AddColor(Extended.Rose, 1.00, 0.00, 0.50, 1.0);
			AddColor(Extended.Deep_cerise, 0.85, 0.20, 0.53, 1.0);
			AddColor(Extended.Rose_bonbon, 0.98, 0.26, 0.62, 1.0);
			AddColor(Extended.Wild_orchid, 0.83, 0.44, 0.64, 1.0);
			AddColor(Extended.Hot_pink, 1.00, 0.41, 0.71, 1.0);
			AddColor(Extended.Winter_Sky, 1.00, 0.00, 0.49, 1.0);
			AddColor(Extended.Brilliant_rose, 1.00, 0.33, 0.64, 1.0);
			AddColor(Extended.Fuchsia_purple, 0.80, 0.22, 0.48, 1.0);
			AddColor(Extended.China_pink, 0.87, 0.44, 0.63, 1.0);
			AddColor(Extended.Liseran_purple, 0.87, 0.44, 0.63, 1.0);
			AddColor(Extended.Thulian_pink, 0.87, 0.44, 0.63, 1.0);
			AddColor(Extended.Telemagenta, 0.81, 0.20, 0.46, 1.0);
			AddColor(Extended.Magenta_Pantone, 0.82, 0.25, 0.49, 1.0);
			AddColor(Extended.French_fuchsia, 0.99, 0.25, 0.57, 1.0);
			AddColor(Extended.Cotton_candy, 1.00, 0.74, 0.85, 1.0);
			AddColor(Extended.Rubine_red, 0.82, 0.00, 0.34, 1.0);
			AddColor(Extended.Dogwood_rose, 0.84, 0.09, 0.41, 1.0);
			AddColor(Extended.Old_mauve, 0.40, 0.19, 0.28, 1.0);
			AddColor(Extended.Wine_dregs, 0.40, 0.19, 0.28, 1.0);
			AddColor(Extended.Violet_red, 0.97, 0.33, 0.58, 1.0);
			AddColor(Extended.Carnation_pink, 1.00, 0.65, 0.79, 1.0);
			AddColor(Extended.Queen_pink, 0.91, 0.80, 0.84, 1.0);
			AddColor(Extended.Mimi_pink, 1.00, 0.85, 0.91, 1.0);
			AddColor(Extended.Ruby, 0.88, 0.07, 0.37, 1.0);
			AddColor(Extended.Raspberry, 0.89, 0.04, 0.36, 1.0);
			AddColor(Extended.Fuchsia_rose, 0.78, 0.26, 0.46, 1.0);
			AddColor(Extended.Quinacridone_magenta, 0.56, 0.23, 0.35, 1.0);
			AddColor(Extended.Pictorial_carmine, 0.76, 0.04, 0.31, 1.0);
			AddColor(Extended.Maroon_X11, 0.69, 0.19, 0.38, 1.0);
			AddColor(Extended.Irresistible, 0.70, 0.27, 0.42, 1.0);
			AddColor(Extended.Raspberry_rose, 0.70, 0.27, 0.42, 1.0);
			AddColor(Extended.Razzmatazz, 0.89, 0.15, 0.42, 1.0);
			AddColor(Extended.Mystic, 0.84, 0.32, 0.51, 1.0);
			AddColor(Extended.Fandango_pink, 0.87, 0.32, 0.52, 1.0);
			AddColor(Extended.English_lavender, 0.71, 0.51, 0.58, 1.0);
			AddColor(Extended.French_rose, 0.96, 0.29, 0.54, 1.0);
			AddColor(Extended.Cyclamen, 0.96, 0.44, 0.63, 1.0);
			AddColor(Extended.Amaranth_pink, 0.95, 0.61, 0.73, 1.0);
			AddColor(Extended.UA_red, 0.85, 0.00, 0.30, 1.0);
			AddColor(Extended.Ruber, 0.81, 0.27, 0.46, 1.0);
			AddColor(Extended.French_pink, 0.99, 0.42, 0.62, 1.0);
			AddColor(Extended.Nadeshiko_pink, 0.96, 0.68, 0.78, 1.0);
			AddColor(Extended.Spanish_carmine, 0.82, 0.00, 0.28, 1.0);
			AddColor(Extended.Rose_red, 0.76, 0.12, 0.34, 1.0);
			AddColor(Extended.China_rose, 0.66, 0.32, 0.43, 1.0);
			AddColor(Extended.Charm_pink, 0.90, 0.56, 0.67, 1.0);
			AddColor(Extended.Cameo_pink, 0.94, 0.73, 0.80, 1.0);
			AddColor(Extended.Lavender_blush, 1.00, 0.94, 0.96, 1.0);
			AddColor(Extended.Amaranth_purple, 0.67, 0.15, 0.31, 1.0);
			AddColor(Extended.Carmine_MP, 0.84, 0.00, 0.25, 1.0);
			AddColor(Extended.Blush, 0.87, 0.36, 0.51, 1.0);
			AddColor(Extended.Tickle_Me_Pink, 0.99, 0.54, 0.67, 1.0);
			AddColor(Extended.Orchid_pink, 0.95, 0.74, 0.80, 1.0);
			AddColor(Extended.Claret, 0.50, 0.09, 0.20, 1.0);
			AddColor(Extended.Mauve_taupe, 0.57, 0.37, 0.43, 1.0);
			AddColor(Extended.Raspberry_glace, 0.57, 0.37, 0.43, 1.0);
			AddColor(Extended.Cerise, 0.87, 0.19, 0.39, 1.0);
			AddColor(Extended.Cinnamon_Satin, 0.80, 0.38, 0.49, 1.0);
			AddColor(Extended.Piggy_pink, 0.99, 0.87, 0.90, 1.0);
			AddColor(Extended.Rose_Dust, 0.62, 0.37, 0.44, 1.0);
			AddColor(Extended.Vanilla_ice, 0.95, 0.56, 0.66, 1.0);
			AddColor(Extended.Baker_Miller_pink, 1.00, 0.57, 0.69, 1.0);
			AddColor(Extended.Schauss_pink, 1.00, 0.57, 0.69, 1.0);
			AddColor(Extended.Burgundy, 0.50, 0.00, 0.13, 1.0);
			AddColor(Extended.Oxblood, 0.50, 0.00, 0.13, 1.0);
			AddColor(Extended.Big_dip_o_ruby, 0.61, 0.15, 0.26, 1.0);
			AddColor(Extended.Red_NCS, 0.77, 0.01, 0.20, 1.0);
			AddColor(Extended.Red_Munsell, 0.95, 0.00, 0.24, 1.0);
			AddColor(Extended.Puce, 0.80, 0.53, 0.60, 1.0);
			AddColor(Extended.Bright_maroon, 0.76, 0.13, 0.28, 1.0);
			AddColor(Extended.Maroon_Crayola, 0.76, 0.13, 0.28, 1.0);
			AddColor(Extended.Pink_Sherbet, 0.97, 0.56, 0.65, 1.0);
			AddColor(Extended.Red_Crayola, 0.93, 0.13, 0.30, 1.0);
			AddColor(Extended.Paradise_pink, 0.90, 0.24, 0.38, 1.0);
			AddColor(Extended.Catawba, 0.44, 0.21, 0.26, 1.0);
			AddColor(Extended.Crimson, 0.86, 0.08, 0.24, 1.0);
			AddColor(Extended.Amaranth, 0.90, 0.17, 0.31, 1.0);
			AddColor(Extended.Radical_Red, 1.00, 0.21, 0.37, 1.0);
			AddColor(Extended.Brink_pink, 0.98, 0.38, 0.50, 1.0);
			AddColor(Extended.Mauvelous, 0.94, 0.60, 0.67, 1.0);
			AddColor(Extended.Cherry_blossom_pink, 1.00, 0.72, 0.77, 1.0);
			AddColor(Extended.Crimson_UA, 0.62, 0.11, 0.20, 1.0);
			AddColor(Extended.Vivid_burgundy, 0.62, 0.11, 0.21, 1.0);
			AddColor(Extended.French_raspberry, 0.78, 0.17, 0.28, 1.0);
			AddColor(Extended.Neon_fuchsia, 1.00, 0.25, 0.39, 1.0);
			AddColor(Extended.Shimmering_Blush, 0.85, 0.53, 0.58, 1.0);
			AddColor(Extended.Black_Shadows, 0.75, 0.69, 0.70, 1.0);
			AddColor(Extended.Carmine, 0.59, 0.00, 0.09, 1.0);
			AddColor(Extended.Antique_ruby, 0.52, 0.11, 0.18, 1.0);
			AddColor(Extended.Red_violet_CW, 0.57, 0.17, 0.24, 1.0);
			AddColor(Extended.Cardinal, 0.77, 0.12, 0.23, 1.0);
			AddColor(Extended.Medium_candy_apple_red, 0.89, 0.02, 0.17, 1.0);
			AddColor(Extended.Spanish_red, 0.90, 0.00, 0.15, 1.0);
			AddColor(Extended.Popstar, 0.75, 0.31, 0.38, 1.0);
			AddColor(Extended.Fiery_rose, 1.00, 0.33, 0.44, 1.0);
			AddColor(Extended.Ultra_red, 0.99, 0.42, 0.52, 1.0);
			AddColor(Extended.Wild_watermelon, 0.99, 0.42, 0.52, 1.0);
			AddColor(Extended.Salmon_pink, 1.00, 0.57, 0.64, 1.0);
			AddColor(Extended.Pink, 1.00, 0.75, 0.80, 1.0);
			AddColor(Extended.Cadmium_red, 0.89, 0.00, 0.13, 1.0);
			AddColor(Extended.Sizzling_Red, 1.00, 0.22, 0.33, 1.0);
			AddColor(Extended.Light_pink, 1.00, 0.71, 0.76, 1.0);
			AddColor(Extended.Solid_pink, 0.54, 0.22, 0.26, 1.0);
			AddColor(Extended.Rusty_red, 0.85, 0.17, 0.26, 1.0);
			AddColor(Extended.Brick_red, 0.80, 0.25, 0.33, 1.0);
			AddColor(Extended.Rosewood, 0.40, 0.00, 0.04, 1.0);
			AddColor(Extended.Wine, 0.45, 0.18, 0.22, 1.0);
			AddColor(Extended.Ruby_red, 0.61, 0.07, 0.12, 1.0);
			AddColor(Extended.Pale_pink, 0.98, 0.85, 0.87, 1.0);
			AddColor(Extended.Cordovan, 0.54, 0.25, 0.27, 1.0);
			AddColor(Extended.Japanese_carmine, 0.62, 0.16, 0.20, 1.0);
			AddColor(Extended.Lava, 0.81, 0.06, 0.13, 1.0);
			AddColor(Extended.Rocket_metallic, 0.54, 0.50, 0.50, 1.0);
			AddColor(Extended.Rose_madder, 0.89, 0.15, 0.21, 1.0);
			AddColor(Extended.Imperial_red, 0.93, 0.16, 0.22, 1.0);
			AddColor(Extended.Red_Pantone, 0.93, 0.16, 0.22, 1.0);
			AddColor(Extended.Red_Salsa, 0.99, 0.23, 0.29, 1.0);
			AddColor(Extended.Candy_pink, 0.89, 0.44, 0.48, 1.0);
			AddColor(Extended.Tango_pink, 0.89, 0.44, 0.48, 1.0);
			AddColor(Extended.Upsdell_red, 0.68, 0.13, 0.16, 1.0);
			AddColor(Extended.Venetian_red, 0.78, 0.03, 0.08, 1.0);
			AddColor(Extended.Deep_taupe, 0.49, 0.37, 0.38, 1.0);
			AddColor(Extended.English_red, 0.67, 0.29, 0.32, 1.0);
			AddColor(Extended.Amaranth_red, 0.83, 0.13, 0.18, 1.0);
			AddColor(Extended.Fire_engine_red, 0.81, 0.13, 0.16, 1.0);
			AddColor(Extended.Rose_vale, 0.67, 0.31, 0.32, 1.0);
			AddColor(Extended.Red_pigment, 0.93, 0.11, 0.14, 1.0);
			AddColor(Extended.English_vermillion, 0.80, 0.28, 0.29, 1.0);
			AddColor(Extended.UP_maroon, 0.48, 0.07, 0.07, 1.0);
			AddColor(Extended.Madder_Lake, 0.80, 0.20, 0.21, 1.0);
			AddColor(Extended.Bittersweet_shimmer, 0.75, 0.31, 0.32, 1.0);
			AddColor(Extended.Old_rose, 0.75, 0.50, 0.51, 1.0);
			AddColor(Extended.OU_Crimson_red, 0.52, 0.09, 0.09, 1.0);




































		vFrontColor[0]		=	GetColor(Extended.White);
		vBackColor[0]		=	GetColor(Extended.White);
		vFrontHighlight[0]	=	GetColor(Extended.Orange);
		vBackHighlight[0]	=	GetColor(Extended.Gray_web);

//		std::cout << "Colors = " << colors.size() << "\n";
//		std::cout << "Color: " << X11.White << " = (" << colors[112]->r << ", " << colors[112]->g << ", " << colors[112]->b << ", " << colors[112]->a << ")\n" ;
//		std::cout << "Color: " << X11.White << " = (" << colors[map[X11.White]]->r << ", " << colors[map[X11.White]]->g << ", " << colors[map[X11.White]]->b << ", " << colors[map[X11.White]]->a << ")\n" ;
//		Color temp1 = GetColor(X11.White);
//		std::cout << "Color: " << X11.White << " = (" << temp1.r << ", " << temp1.g << ", " << temp1.b << ", " << temp1.a << ")\n" ;
//
//		for(int n=0; n<colors.size()-1; n++) {
//			std::cout << "Color #" << n << " : " << " = (" << colors[n]->r << ", " << colors[n]->g << ", " << colors[n]->b << ", " << colors[n]->a << ")\n" ;
//		}

		vActiveColor = nullptr;
		eActiveColor = COLOR_FRONT;
	}

	_Colors::~_Colors() {
		delete [] vFrontColor;
		delete [] vBackColor;
		delete [] vFrontHighlight;
		delete [] vBackHighlight;
		delete [] vDetail1Color;
		delete [] pallette;
	}

	/***
	 *
	 * @param name Name of color
	 * @param color Color definition as 4 floats
	 * @return
	 */
	int _Colors::AddColor(std::string name, Color color) {
		Color *temp = new Color(color.r, color.g, color.b, color.a);
		//colors.push_back(temp);
		colors.add(name, temp);
//		colors.emplace_back(Color(color.r, color.g, color.b, color.a));
		//uint id = colors.size()-1;
		//map.insert(make_pair(name, id));
//		if(name == "White") std::cout << "Color: " << name << " [" << id << "]"  << " = (" << color.r << ", " << color.g << ", " << color.b << ", " << color.a << ")\n" ;
//		if(name == "White") std::cout << "Color: " << name << " [" << id << "]"  << " = (" << colors[id]->r << ", " << colors[id]->g << ", " << colors[id]->b << ", " << colors[id]->a << ")\n" ;
//		if(name == "White") std::cout << "Color: " << name << " [" << map[name] << "]" << " = (" << colors[map[name]]->r << ", " << colors[map[name]]->g << ", " << colors[map[name]]->b << ", " << colors[map[name]]->a << ")\n" ;
//		if(name == "White") std::cout << "Color: " << name << " [" << id << "]"  << " = (" << colors[id]->r << ", " << colors[id]->g << ", " << colors[id]->b << ", " << colors[id]->a << ")\n" ;
//		if(name == "White") std::cout << "Color: " << name << " [" << map[name] << "]" << " = (" << colors[map[name]]->r << ", " << colors[map[name]]->g << ", " << colors[map[name]]->b << ", " << colors[map[name]]->a << ")\n" ;
		return colors.getID(name);
	}

	/***
	 *
	 * @param name Name of color
	 * @param r Red component
	 * @param g Green Component
	 * @param b Blue Component
	 * @param a Alpha Component
	 * @return Integer ID of color mapped to \p name
	 */
	int _Colors::AddColor(std::string name, float r, float g, float b, float a) {
		return AddColor(name, Color(r, g, b, a));
	}

	/***
	 *
	 * @param name Name of color
	 * @param r Red component in 0-255 range
	 * @param g green component in 0-255 range
	 * @param b blue component in 0-255 range
	 * @param a alpha component in 0-255 range
	 * @return
	 */
	int _Colors::AddColor255(std::string name, int r, int g, int b, int a) {
		return AddColor(name, Color(r/255.0f, g/255.0f, b/255.0f, a/255.0f));
	}

	/***
	 *
	 * @param name Name of color
	 * @return Color defined by \p name
	 */
	Color & _Colors::GetColor(std::string name) {
		return *colors[name];
	}

	/***
	 *
	 * @param id Integer ID of color
	 * @return Color defined by \p id
	 */
	Color & _Colors::GetColor(int id) {
		return *colors[id];
	}


	/*
	 *
	 */
	Color _Colors::GetPallette(_PALLETTE_COLOR e) {
		return pallette[e];
	}

	/*
	 *
	 */
//	void _Colors::SetFront(Vector3f color, float alpha)				{	vFrontColor[uiFrontStack] = Color(color, alpha);	}
	void _Colors::SetFront(Color color)								{	vFrontColor[uiFrontStack] = color;	}
//	void _Colors::PushFront(Vector3f color, float alpha)			{	PushFront(); SetFront(color, alpha);	}
	void _Colors::PushFront(Color color)							{	PushFront(); SetFront(color);	}
//	void _Colors::PushFront(std::string name)						{	PushFront(); SetFront(colors[map[name]]);	}
	void _Colors::PushFront()										{	uiFrontStack = std::min(++uiFrontStack, STACK_SIZE-1);	}
	void _Colors::PopFront()										{	uiFrontStack = std::max(--uiFrontStack, 0);	}
	Color _Colors::GetFront()										{	return vFrontColor[uiFrontStack];	}
	Color& _Colors::GetFrontPtr()									{	return vFrontColor[uiFrontStack];	}

	/*
	 *
	 */
//	void _Colors::SetBack(Vector3f color, float alpha)				{	vBackColor[uiBackStack] = Color(color, alpha);	}
	void _Colors::SetBack(Color color)								{	vBackColor[uiBackStack] = color;	}
//	void _Colors::PushBack(Vector3f color, float alpha)				{	PushBack(); SetBack(color, alpha);	}
	void _Colors::PushBack(Color color)								{	PushBack(); SetBack(color);	}
	void _Colors::PushBack()										{	uiBackStack = std::min(++uiBackStack, STACK_SIZE-1);	}
	void _Colors::PopBack()											{	uiBackStack = std::max(--uiBackStack, 0);	}
	Color _Colors::GetBack()										{	return vBackColor[uiBackStack];	}

	/*
	 *
	 */
//	void _Colors::SetFrontHighlight(Vector3f color, float alpha)	{	vFrontHighlight[uiFrontHighlightStack] = Color(color, alpha);	}
	void _Colors::SetFrontHighlight(Color color)					{	vFrontHighlight[uiFrontHighlightStack] = color;	}
//	void _Colors::PushFrontHighlight(Vector3f color, float alpha)	{	PushFrontHighlight(); SetFrontHighlight(color, alpha);	}
	void _Colors::PushFrontHighlight(Color color)					{	PushFrontHighlight(); SetFrontHighlight(color);	}
	void _Colors::PushFrontHighlight()								{	uiFrontHighlightStack = std::min(++uiFrontHighlightStack, STACK_SIZE-1);	}
	void _Colors::PopFrontHighlight()								{	uiFrontHighlightStack = std::max(--uiFrontHighlightStack, 0);	}
	Color _Colors::GetFrontHighlight()								{	return vFrontHighlight[uiFrontHighlightStack];	}

	/*
	 *
	 */
//	void _Colors::SetBackHighlight(Vector3f color, float alpha)		{	vBackHighlight[uiBackHighlightStack] = Color(color, alpha);	}
	void _Colors::SetBackHighlight(Color color)						{	vBackHighlight[uiBackHighlightStack] = color;	}
//	void _Colors::PushBackHighlight(Vector3f color, float alpha)	{	PushBackHighlight(); SetBackHighlight(color, alpha);	}
	void _Colors::PushBackHighlight(Color color)					{	PushBackHighlight(); SetBackHighlight(color);	}
	void _Colors::PushBackHighlight()								{	uiBackHighlightStack = std::min(++uiBackHighlightStack, STACK_SIZE-1);	}
	void _Colors::PopBackHighlight()								{	uiBackHighlightStack = std::max(--uiBackHighlightStack, 0);	}
	Color _Colors::GetBackHighlight()								{	return vBackHighlight[uiBackHighlightStack];	}

	/*
	 *
	 */
//	void _Colors::SetDetail1(Vector3f color, float alpha)			{	vDetail1Color[uiDetail1Stack] = Color(color, alpha);	}
	void _Colors::SetDetail1(Color color)							{	vDetail1Color[uiDetail1Stack] = color;	}
//	void _Colors::PushDetail1(Vector3f color, float alpha)			{	PushBack(); SetDetail1(color, alpha);	}
	void _Colors::PushDetail1(Color color)							{	PushBack(); SetDetail1(color);	}
	void _Colors::PushDetail1()										{	uiDetail1Stack = std::min(++uiDetail1Stack, STACK_SIZE-1);	}
	void _Colors::PopDetail1()										{	uiDetail1Stack = std::max(--uiDetail1Stack, 0);	}
	Color _Colors::GetDetail1()										{	return vDetail1Color[uiDetail1Stack];	}

	void _Colors::SetActive(_ACTIVE_COLOR e) {
//		std::cout << "Color Set: ";
		eActiveColor = e;
//		switch(e) {
//			case COLOR_FRONT:
//				vActiveColor = &vFrontColor[uiFrontStack];
//				break;
//			case COLOR_FRONT_HIGHLIGHT:
//				vActiveColor = &vFrontHighlight[uiFrontHighlightStack];
//				break;
//			case COLOR_BACK:
//				vActiveColor = &vBackColor[uiBackStack];
//				break;
//			case COLOR_BACK_HIGHLIGHT:
//				vActiveColor = &vBackHighlight[uiBackHighlightStack];
//				break;
//			default:
//				vActiveColor = &vFrontColor[uiFrontStack];
//		}

//		std::cout << vActiveColor.r << ", " << vActiveColor.g << ", " << vActiveColor.b << std::endl;
	}

	Color _Colors::GetActive() {
		switch(eActiveColor) {
			case COLOR_FRONT:
				vActiveColor = &vFrontColor[uiFrontStack];
				break;
			case COLOR_FRONT_HIGHLIGHT:
				vActiveColor = &vFrontHighlight[uiFrontHighlightStack];
				break;
			case COLOR_BACK:
				vActiveColor = &vBackColor[uiBackStack];
				break;
			case COLOR_BACK_HIGHLIGHT:
				vActiveColor = &vBackHighlight[uiBackHighlightStack];
				break;
			case COLOR_DETAIL1:
				vActiveColor = &vDetail1Color[uiDetail1Stack];
				break;
			default:
				vActiveColor = &vFrontColor[uiFrontStack];
		}

		return *vActiveColor;
	}

} /* namespace Core */





















































