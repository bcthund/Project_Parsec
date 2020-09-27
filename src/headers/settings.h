/*
 * settings.h
 *
 *  Created on: Jul 25, 2015
 *      Author: bcthund
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "./core/core_functions.h"
#include "./core/types.h"

namespace Core {
	void Setup_GameVars(int argc, char* argv[]) {
		//_CoreFunctions coreFunctions;

		// ###################################################################################################################################
		//Debugging messages
	//	gameVars->debug.lines=100;
	//	gameVars->debug.MASTER						=	true;
	//	gameVars->debug.temp							=	false;
	//	gameVars->debug.keyboard						=	false;
	//	gameVars->debug.mouse						=	false;
	//	gameVars->debug.shadow						=	false;
	//	gameVars->debug.lag							=	false;
	//	gameVars->debug.init							=	false;
//		gameVars->debug.load							=	true;
	//	gameVars->debug.lamp							=	false;
	//	gameVars->debug.map							=	false;
	//	gameVars->debug.sky							=	false;
	//	gameVars->debug.bb							=	false;
	//	gameVars->debug.fps							=	true;	//Also limits game speed
	//	gameVars->debug.sun							=	false;
	//	gameVars->debug.mem							=	false;
	//	gameVars->debug.manual_sun					=	false;
	//	gameVars->debug.stitchMap					=	true;
	//	Core.shader.debug							=	false;
	//	gameVars->debug.temp							=	false;
	//	gameVars->debug.runworld_map_calc			=	true;
	//	gameVars->debug.runworld_o2d_calc			=	false;
	//	gameVars->debug.runworld_o3d_calc			=	true;
	//	gameVars->debug.runworld_e2d_calc			=	true;
	//	gameVars->debug.dungeon_map_calc				=	true;
	//	gameVars->debug.dungeon_o3d_calc				=	true;

		// ###################################################################################################################################
		// 	State
		//
		state->fGravity	= 9.8f;
		state->fWorldScale = 1.0f;	// TODO: Not fully implemented

		// ###################################################################################################################################
		// Controls
		//
		//gameVars->controls.mouse.sensX			=	0.004;			//Sensitivity on X-axis
		//gameVars->controls.mouse.sensY			=	0.004;			//Sensitivity on Y-axis
		//gameVars->controls.mouse.deadX			=	0;			//Mouse deadzone on X-axis
		//gameVars->controls.mouse.deadY			=	0;			//Mouse deadzone on Y-axis
		//gameVars->controls.mouse.relX				=	0;
		//gameVars->controls.mouse.relY				=	0;
		//gameVars->controls.mouse.x				=	0;
		//gameVars->controls.mouse.y				=	0;
		gameVars->controls.fly						=	false;
		//gameVars->controls.modClimb				=	1;
		//gameVars->controls.modStance				=	1;
		gameVars->controls.modSpeed					=	2;
		//gameVars->controls.mouse.lock				=	true;
		//gameVars->controls.mouse.hide				=	true;

		// Set move speed AFTER world scale
		//gameVars->controls.moveSpeed				=	0.25f;			//Character movement adjustment, reset by framerate later
		//gameVars->controls.mouse.bEnable			=	true;			//Enable mouse input, disable to enable keyboard mouse emmulation

		gameVars->controls.key.move_forward			=	SDLK_w;
		gameVars->controls.key.move_back			=	SDLK_s;
		gameVars->controls.key.strafe_left			=	SDLK_a;
		gameVars->controls.key.strafe_right			=	SDLK_d;
		gameVars->controls.key.turn_left			=	SDLK_q;
		gameVars->controls.key.turn_right			=	SDLK_e;
		//gameVars->controls.key.jump				=	SDLK_SPACE;
		//gameVars->controls.key.change_stance		=	SDLK_c;
		gameVars->controls.key.move_up				=	SDLK_r;
		gameVars->controls.key.move_down			=	SDLK_f;
		gameVars->controls.key.run					=	SDLK_LSHIFT;
		gameVars->controls.key.sneak				=	SDLK_LCTRL;
		gameVars->controls.key.activate				=	SDLK_RETURN;
		//gameVars->controls.key.open_journal		=	SDLK_j;
		//gameVars->controls.key.open_menu			=	SDLK_o;
		//gameVars->controls.key.open_intent		=	SDLK_u;
//		gameVars->controls.key.mouse_left			=	SDLK_LEFT;
//		gameVars->controls.key.mouse_right			=	SDLK_RIGHT;
//		gameVars->controls.key.mouse_up				=	SDLK_DOWN;
//		gameVars->controls.key.mouse_down			=	SDLK_UP;
		gameVars->controls.key.mouse_left			=	SDLK_KP_4;
		gameVars->controls.key.mouse_right			=	SDLK_KP_6;
		gameVars->controls.key.mouse_up				=	SDLK_KP_8;
		gameVars->controls.key.mouse_down			=	SDLK_KP_2;

		// ###################################################################################################################################
		// Debug
		//
	//	gameVars->debug.camera.bSunView				=	true;		//Draw the position of the sun
	//	gameVars->debug.time.temp					=	false;
	//	gameVars->debug.time.load					=	true;
	//	gameVars->debug.time.debug					=	false;
	//	gameVars->debug.time.gameLoop				=	true;
	//	gameVars->debug.time.runWorld				=	false;
	//	gameVars->debug.time.runDungeon				=	false;
	//	gameVars->debug.time.input					=	false;
	//	gameVars->debug.time.gameUpdate				=	true;
	//	gameVars->debug.time.motionBlur				=	false;
	//	gameVars->debug.time.gameDraw				=	false;
	//	gameVars->debug.time.capture				=	false;
	//	gameVars->debug.time.window					=	false;
	//	gameVars->debug.time.command				=	false;
	//	gameVars->debug.time.buffer					=	false;

		/* ###################################################################################################################################
		 * Directory and record size settings
		 *
		 * BinFile: The filename for the binary data file for the respective system
		 * 		- Some systems don't used this as they are on a per/map
		 * 		  basis, such as O2D and O3D. These systems only use the
		 * 		  RecordSize and TexDir components.
		 * RecordSize: The number of bytes per record in the bin file
		 * TexDir: The directory for textures related to this system
		 */


//		gameVars->data.icon.RecordSize				= 0;
//		gameVars->data.icon.BinFile					= "icons.bin";
//		gameVars->data.icon.TexDir					= "";
//
//		//gameVars->data.o2d.BinFile					= "";
//		gameVars->data.o2d.RecordSize				= 0;
//		gameVars->data.o2d.TexDir					= "";
//
//		//gameVars->data.o3d.BinFile					= "";
//		gameVars->data.o3d.RecordSize				= 0;
//		gameVars->data.o3d.TexDir					= "";
//
//		gameVars->data.sprite.BinFile				= "sprites.bin";
//		gameVars->data.sprite.RecordSize				= 0;
//		gameVars->data.sprite.TexDir					= "";
//
//		gameVars->data.text.BinFile					= "";
//		gameVars->data.text.RecordSize				= 0;
//		gameVars->data.text.TexDir					= "";
//
//		gameVars->data.win.BinFile					= "";
//		gameVars->data.win.RecordSize				= 0;
//		gameVars->data.win.TexDir					= "";
//
//
//		gameVars->dir.o3d							=	"./ply/";
//		gameVars->dir.o3dtex							=	"./texture/ply/";
//		gameVars->dir.text							=	"./texture/text/";
//		gameVars->dir.animation						=	"./texture/animation/";
//		gameVars->dir.sprite							=	"./texture/sprite/";
//		gameVars->dir.win							=	"./texture/win/";
		//gameVars->dir.o2dtex							=	"./texture/o2d/";
		//gameVars->dir.animated					=	"./texture/ani/";
	//	gameVars->dir.dgn							=	"./dgn/";
	//	gameVars->dir.shaders						=	"./shaders/";
	//	//gameVars->dir.map							=	"./map/";
	//	//gameVars->dir.o2d							=	"./map/o2d/";
	//	//gameVars->dir.o3d							=	"./map/o3d/";
	//	//gameVars->dir.e2d							=	"./map/e2d/";
	//	//gameVars->dir.elf							=	"./map/elf/";
	//	//gameVars->dir.sky							=	"./texture/sky/";

		// ###################################################################################################################################
		// The size of records in bytes
		//
//		gameVars->recordSize.data					=	2;
//		gameVars->recordSize.map						=	18;
//		gameVars->recordSize.o2d						=	60;
//		gameVars->recordSize.o3d						=	96;
//		gameVars->recordSize.e2d						=	128;
//		gameVars->recordSize.elf						=	128;
//		gameVars->recordSize.image					=	32;
//		gameVars->recordSize.animation				=	32;
//		gameVars->recordSize.font					=	32;
//		gameVars->recordSize.system					=	32;
//		gameVars->recordSize.iconsys					=	32;
//		gameVars->recordSize.spritesys				=	32;
//		gameVars->recordSize.winsys					=	32;
	//	gameVars->recordSize.event					=	0;

		// ###################################################################################################################################
		// Audio System
		//
	//	gameSys.audioSys.Mute();

		// ###################################################################################################################################
		// General Screen settings
		//
	//	gameVars->screen.mode="opengl";								//Set the display mode (opengl/sdl)		(Only OpenGL is supported now)

		// MY SUPPORTED RESOLUTIONS
		//	1920 x 1080
		//	1280 x 1024
		//	1024 x 768
		//	800 x 600
		//	640 x 480

		// HD1080
//		gameVars->screen.res.x				=	1920;				//Display width
//		gameVars->screen.res.y				=	1080;				//Display height

	//	gameVars->screen.w					=	1680;				//Display width
	//	gameVars->screen.h					=	1050;				//Display height

	//	gameVars->screen.w					=	1600;				//Display width
	//	gameVars->screen.h					=	900;				//Display height

	//	gameVars->screen.w					=	1360;				//Display width
	//	gameVars->screen.h					=	768;				//Display height

	//	gameVars->screen.w					=	1280;				//Display width
	//	gameVars->screen.h					=	1024;				//Display height

		// HD720
//		gameVars->screen.res.x				=	1280;				//Display width
//		gameVars->screen.res.y				=	720;				//Display height

	//	gameVars->screen.w					=	1152;				//Display width
	//	gameVars->screen.h					=	864;				//Display heigh

	//	gameVars->screen.w					=	1024;				//Display width
	//	gameVars->screen.h					=	576;				//Display height

	//	gameVars->screen.w					=	1024;				//Display width
	//	gameVars->screen.h					=	768;				//Display height


//		gameVars->screen.w					=	854;				//Display width
//		gameVars->screen.h					=	480;				//Display height

	//	gameVars->screen.w					=	320;				//Display width
	//	gameVars->screen.h					=	240;				//Display height

//		gameVars->screen.half.x						=	gameVars->screen.res.x/2;	//To speed up calculations
//		gameVars->screen.half.y						=	gameVars->screen.res.y/2;	//To speed up calculations
		gameVars->screen.bpp							=	16; 					//Display color depth
		gameVars->screen.frameRate					=	120; 					//Set the desired frame rate (fps) (Needs improvement, does not reach value properly)
		//gameVars->screen.iTerrainGrid				=	1;						//Size of the terrain grid to load
		//if (argc>0)	gameVars->screen.iTerrainGrid	=	strtol(argv[1], NULL, 10);				//Size of the terrain grid to load
		//else		gameVars->screen.iTerrainGrid	=	9;						//Size of the terrain grid to load
		//gameVars->screen.iGridOffset				=	gameVars->screen.iTerrainGrid/2;		//Used for loading map files
		gameVars->screen.fScale						=	1.00f;						// TODO: Move to state class (Size of the terrain grid to load)
		gameVars->controls.moveSpeed					=	0.25f * gameVars->screen.fScale;			//Character movement adjustment, reset by framerate later
//		gameVars->screen.fNear						=	1.0f;					//The near clipping plane
//		gameVars->screen.fFar						=	500000.0f;				//The far clipping plane
//		gameVars->screen.fNear						=	250000.0f;					//The near clipping plane
//		gameVars->screen.fFar						=	1.0f;				//The far clipping plane
//		gameVars->screen.fScreenAspect				= 	gameVars->screen.res.x/gameVars->screen.res.y;
//		gameVars->screen.fDistanceAspect			=	gameVars->screen.fNear/gameVars->screen.fFar;

		//float vFov = 90.0f;
//		float hFov = 110.0f;
//		float fX = (float)gameVars->screen.res.x;
//		float fY = (float)gameVars->screen.res.y;
		//float	hFov = M_RadToDeg(2*atan((fX/fY)*tan(vFov/2)))/2;
		//float	vFov = M_RadToDeg(2*atan((fY/fX)*tan(hFov/2)));
		//float	hFov = M_RadToDeg(2*atan((fX/fY)*tan(M_DegToRad(vFov/2))));
		//float	vFov = coreFunctions.M_RadToDeg(2*atan((fY/fX)*tan(coreFunctions.M_DegToRad(hFov/2))));
		//Radians	vFov = 2*atan((fX/fY)*tan(Degrees(80/2).toRadians()));
		//cout << "> hFOV : " << hFov << endl;
		//cout << "> vFOV : " << vFov << endl;

		//gameVars->screen.fFov						=	vFov;					//The field of view
		//gameVars->screen.degFov						=	vFov.toDegrees();						//The field of view
//		gameVars->screen.degFov						=	80;						//The field of view




		gameVars->screen.projectionData.add("standard", new Core::t_ProjectionData());
		gameVars->screen.projectionData["standard"]->res.x				= 1280;
		gameVars->screen.projectionData["standard"]->res.y				= 720;
		gameVars->screen.projectionData["standard"]->fNear				= 50.0f;
		gameVars->screen.projectionData["standard"]->fFar				= 200000.0f;
		gameVars->screen.projectionData["standard"]->degFov				= 80;
		gameVars->screen.setActiveProjection("standard").init();

		gameVars->screen.projectionData.add("close", new Core::t_ProjectionData());
		gameVars->screen.projectionData["close"]->res.x					= 1280;
		gameVars->screen.projectionData["close"]->res.y					= 720;
		gameVars->screen.projectionData["close"]->fNear					= 1.0f;
		gameVars->screen.projectionData["close"]->fFar					= 10000.0f;
		gameVars->screen.projectionData["close"]->degFov				= 80;
		gameVars->screen.projectionData["close"]->init();

		gameVars->screen.projectionData.add("mid", new Core::t_ProjectionData());
		gameVars->screen.projectionData["mid"]->res.x					= 1280;
		gameVars->screen.projectionData["mid"]->res.y					= 720;
		gameVars->screen.projectionData["mid"]->fNear					= 1.0f;
		gameVars->screen.projectionData["mid"]->fFar					= 10000.0f;
		gameVars->screen.projectionData["mid"]->degFov					= 100000;
		gameVars->screen.projectionData["mid"]->init();

		gameVars->screen.projectionData.add("far", new Core::t_ProjectionData());
		gameVars->screen.projectionData["far"]->res.x					= 1280;
		gameVars->screen.projectionData["far"]->res.y					= 720;
		gameVars->screen.projectionData["far"]->fNear					= 1.0f;
		gameVars->screen.projectionData["far"]->fFar					= 100000.0f;
		gameVars->screen.projectionData["far"]->degFov					= 250000;
		gameVars->screen.projectionData["far"]->init();

		gameVars->screen.projectionData.add("atmosphere", new Core::t_ProjectionData());
		gameVars->screen.projectionData["atmosphere"]->res.x			= 1280;
		gameVars->screen.projectionData["atmosphere"]->res.y			= 720;
		gameVars->screen.projectionData["atmosphere"]->fNear			= 1000.0f;
		gameVars->screen.projectionData["atmosphere"]->fFar				= 1000000.0f;
		gameVars->screen.projectionData["atmosphere"]->degFov			= 70;
		gameVars->screen.projectionData["atmosphere"]->init();

		//gameVars->screen.bInstance					=	true;					//Enable object instancing, SLOW!!!
		gameVars->screen.MultiSample					=	true;					//Toggle Multisampling
		gameVars->screen.uiMultiSamples				=	16;
		gameVars->screen.bInterlaced					=	false;					//Toggle interlaced mode
		//gameVars->screen.AutoFlush					=	false;					//Execute glFlush throughout execution
		//gameVars->screen.AutoFinish				=	false;					//Execute glFinish throughout execution
		//gameVars->screen.fLineWidth				=	1.0;
		//gameVars->screen.ePolyMode					=	PM_FILL;
		//gameVars->screen.origin[0]					=	0;
		//gameVars->screen.origin[1]					=	0;

		/*
		 * Color to clear background to (Null space)
		 *
		 * vSkyColor[0] = 0.439f;
		 * vSkyColor[1] = 0.643f;
		 * vSkyColor[2] = 0.859f;
		 * vSkyColor[3] = 1.0f;
		 */

//		gameVars->screen.vClearColorBase[0]			=	0.0f;
//		gameVars->screen.vClearColorBase[1]			=	0.0f;
//		gameVars->screen.vClearColorBase[2]			=	0.0f;
//		gameVars->screen.vClearColorBase[3]			=	1.0f;

		gameVars->screen.vClearColorBase[0]			=	0.2f;
		gameVars->screen.vClearColorBase[1]			=	0.2f;
		gameVars->screen.vClearColorBase[2]			=	0.2f;
		gameVars->screen.vClearColorBase[3]			=	1.0f;

//		gameVars->screen.vClearColorBase[0]			=	0.5f;
//		gameVars->screen.vClearColorBase[1]			=	0.55f;
//		gameVars->screen.vClearColorBase[2]			=	0.8f;
//		gameVars->screen.vClearColorBase[3]			=	1.0f;

		//gameVars->screen.vClearColorBase[0]		=	0.439f;
		//gameVars->screen.vClearColorBase[1]		=	0.643f;
		//gameVars->screen.vClearColorBase[2]		=	0.859f;
		//gameVars->screen.vClearColorBase[3]		=	1.0f;

		gameVars->screen.vClearColorCurrent[0]		=	gameVars->screen.vClearColorBase[0];
		gameVars->screen.vClearColorCurrent[1]		=	gameVars->screen.vClearColorBase[1];
		gameVars->screen.vClearColorCurrent[2]		=	gameVars->screen.vClearColorBase[2];
		gameVars->screen.vClearColorCurrent[3]		=	gameVars->screen.vClearColorBase[3];

		gameVars->screen.clear						=	GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT;

		// ###################################################################################################################################
		//Font

		int iScale									= 1;					// Font scale

		gameVars->font.setFont(8, 10);

//		gameVars->font.vSize[0]						= 8;
//		gameVars->font.vSize[1]						= 10;

//		gameVars->font.vSize[0]						= 10;
//		gameVars->font.vSize[1]						= 12;

//		gameVars->font.vSize[0]						= 12;
//		gameVars->font.vSize[1]						= 14;

//		gameVars->font.vSize[0]						= 16;
//		gameVars->font.vSize[1]						= 20;

//		gameVars->font.vSize[0]						= 32;
//		gameVars->font.vSize[1]						= 40;

		gameVars->font.vMax[0]						= gameVars->screen.activeProjection->res.x/gameVars->font.vSize[0];
		gameVars->font.vMax[1]						= gameVars->screen.activeProjection->res.y/gameVars->font.vSize[1];

		//gameVars->font.vSize[0]		=	gameVars->screen.w/gameVars->font.vMax[0];		// Default font WIDTH based on screen HEIGHT
		//gameVars->font.vSize[1]		=	gameVars->screen.h/gameVars->font.vMax[1];		// Default font HEIGHT based on screen WIDTH

		//Huge
			//gameVars->font.vSize[0]		=	gameVars->screen.w/84;		// Default font WIDTH based on screen HEIGHT
			//gameVars->font.vSize[1]		=	gameVars->screen.h/36;		// Default font HEIGHT based on screen WIDTH
		//Large
			//gameVars->font.vMax[0]			=	96;
			//gameVars->font.vMax[1]			=	48;
			//gameVars->font.vSize[0]		=	gameVars->screen.w/gameVars->font.vMax[0];		// Default font WIDTH based on screen HEIGHT
			//gameVars->font.vSize[1]		=	gameVars->screen.h/gameVars->font.vMax[1];		// Default font HEIGHT based on screen WIDTH
		//Normal
			//gameVars->font.vSize[0]				=	gameVars->screen.w/108;		// Default font WIDTH based on screen HEIGHT
			//gameVars->font.vSize[1]				=	gameVars->screen.h/66;		// Default font HEIGHT based on screen WIDTH
		//Small
			//gameVars->font.vSize[0]		=	gameVars->screen.w/120;		// Default font WIDTH based on screen HEIGHT
			//gameVars->font.vSize[1]		=	gameVars->screen.h/72;		// Default font HEIGHT based on screen WIDTH
		//Very Small
			//gameVars->font.vSize[0]		=	gameVars->screen.w/132;		// Default font WIDTH based on screen HEIGHT
			//gameVars->font.vSize[1]		=	gameVars->screen.h/84;		// Default font HEIGHT based on screen WIDTH
		//MANUAL
			//gameVars->font.vSize[0]		=	14.0f;			// Width
			//gameVars->font.vSize[1]		=	20.0f;			// Height

		//ADD VALUE TO STORE CALCULATED MAX ROWS AND COLUMNS FOR SELECTED FONT SIZE
				//Currently needed for runBattle.h; drawing the window system automatically

			gameVars->font.iTexNum				=	0;				// Font Number (Texture)
			gameVars->font.spacing				= 2;


//			gameVars->font.vHighlight[0]			=	1.0f;
//			gameVars->font.vHighlight[1]			=	1.0f;
//			gameVars->font.vHighlight[2]			=	0.5f;
//			gameVars->font.vHighlight[3]			=	1.0f;
//
//			gameVars->font.vColor[0]				=	1.0f;
//			gameVars->font.vColor[1]				=	1.0f;
//			gameVars->font.vColor[2]				=	1.0f;
//			gameVars->font.vColor[3]				=	1.0f;
//
//			gameVars->color.white[0]				=	1.0f;
//			gameVars->color.white[1]				=	1.0f;
//			gameVars->color.white[2]				=	1.0f;
//			gameVars->color.white[3]				=	1.0f;
//
//			gameVars->color.black[0]				=	0.0f;
//			gameVars->color.black[1]				=	0.0f;
//			gameVars->color.black[2]				=	0.0f;
//			gameVars->color.black[3]				=	1.0f;
//
//			gameVars->color.tan[0]				=	0.74f;
//			gameVars->color.tan[1]				=	0.65f;
//			gameVars->color.tan[2]				=	0.45f;
//			gameVars->color.tan[3]				=	1.0f;
//
//			gameVars->color.brown[0]				=	0.54f;
//			gameVars->color.brown[1]				=	0.45f;
//			gameVars->color.brown[2]				=	0.25f;
//			gameVars->color.brown[3]				=	1.0f;
//
//			gameVars->color.red[0]				=	1.0f;
//			gameVars->color.red[1]				=	0.0f;
//			gameVars->color.red[2]				=	0.0f;
//			gameVars->color.red[3]				=	1.0f;
//
//			gameVars->color.green[0]				=	0.0f;
//			gameVars->color.green[1]				=	1.0f;
//			gameVars->color.green[2]				=	0.0f;
//			gameVars->color.green[3]				=	1.0f;
//
//			gameVars->color.blue[0]				=	0.0f;
//			gameVars->color.blue[1]				=	0.0f;
//			gameVars->color.blue[2]				=	1.0f;
//			gameVars->color.blue[3]				=	1.0f;
//
//			gameVars->color.yellow[0]			=	1.0f;
//			gameVars->color.yellow[1]			=	1.0f;
//			gameVars->color.yellow[2]			=	0.0f;
//			gameVars->color.yellow[3]			=	1.0f;
//
//			gameVars->color.orange[0]			=	1.0f;
//			gameVars->color.orange[1]			=	0.6f;
//			gameVars->color.orange[2]			=	0.0f;
//			gameVars->color.orange[3]			=	1.0f;
//
//			gameVars->color.grey[0]				=	0.8f;
//			gameVars->color.grey[1]				=	0.8f;
//			gameVars->color.grey[2]				=	0.8f;
//			gameVars->color.grey[3]				=	1.0f;
//
//			gameVars->color.transparent[0]		=	0.0f;
//			gameVars->color.transparent[1]		=	0.0f;
//			gameVars->color.transparent[2]		=	0.0f;
//			gameVars->color.transparent[3]		=	0.0f;
//
//			gameVars->color.debug[0]				=	0.0f;
//			gameVars->color.debug[1]				=	0.0f;
//			gameVars->color.debug[2]				=	0.75f;
//			gameVars->color.debug[3]				=	0.25f;

//			gameVars->font.consoleLines			=	16;										// Lines of text in console
//			gameVars->font.consoleLines			=	16;										// Lines of text in console
//			gameVars->font.vHalfSize[0]			=	gameVars->font.vSize[0]/2;				// Half Width
//			gameVars->font.vHalfSize[1]			=	gameVars->font.vSize[1]/2;				// Half Height

			/* Set the (0,0) position for the font bases on screen resolution
			 * NOTE: THIS IS ONLY FOR FONTS!
			 * Use gameVars->screen.origin[0,1] for actual corner of screen
			 */
			//gameVars->font.screenCoords[0] 		= -gameVars->screen.halfW+(gameVars->font.vSize[0]/2);
			//gameVars->font.screenCoords[1] 		= gameVars->screen.halfH-(gameVars->font.vSize[1]/2);

			// This causes scaling/position issues for certain things
			gameVars->font.screenCoords[0] 			= -gameVars->screen.activeProjection->half.x+gameVars->font.vHalfSize[0];
			gameVars->font.screenCoords[1] 			= gameVars->screen.activeProjection->half.y-gameVars->font.vHalfSize[1];
			//gameVars->font.screenCoords[0] 		= -gameVars->screen.halfW+(gameVars->font.vSize[0]/2);
			//gameVars->font.screenCoords[1] 		= gameVars->screen.halfH-(gameVars->font.vSize[1]/2);

			//cout << "SCREENCENTER_X:" << gameVars->font.screenCoords[0] << endl;
			//cout << "SCREENCENTER_Y:" << gameVars->font.screenCoords[1] << endl;


		// ###################################################################################################################################
		// Pallette
		//
//		gameVars->pallette.gui.button.background.base		= colors->Tan;
//		gameVars->pallette.gui.button.background.hover		= colors->Orange;
//		gameVars->pallette.gui.button.background.active		= colors->Green;
//		gameVars->pallette.gui.button.border.base			= colors->Black;
//		gameVars->pallette.gui.button.border.hover			= colors->Black;
//		gameVars->pallette.gui.button.border.active			= colors->Black;
//		gameVars->pallette.gui.button.text.base				= colors->Black;
//		gameVars->pallette.gui.button.text.hover			= colors->Black;
//		gameVars->pallette.gui.button.text.active			= colors->Black;
//
//		gameVars->pallette.gui.field.background.base		= colors->Gray;
//		gameVars->pallette.gui.field.background.hover		= colors->White;
//		gameVars->pallette.gui.field.background.active		= colors->Yellow;
//		gameVars->pallette.gui.field.border.base			= colors->Black;
//		gameVars->pallette.gui.field.border.hover			= colors->Black;
//		gameVars->pallette.gui.field.border.active			= colors->Black;
//		gameVars->pallette.gui.field.text.base				= colors->Black;
//		gameVars->pallette.gui.field.text.hover				= colors->Black;
//		gameVars->pallette.gui.field.text.active			= colors->Black;
//
//		gameVars->pallette.gui.label.background.base		= colors->White;
//		gameVars->pallette.gui.label.background.hover		= colors->White;
//		gameVars->pallette.gui.label.background.active		= colors->White;
//		gameVars->pallette.gui.label.border.base			= colors->Black;
//		gameVars->pallette.gui.label.border.hover			= colors->Black;
//		gameVars->pallette.gui.label.border.active			= colors->Black;
//		gameVars->pallette.gui.label.text.base				= colors->Black;
//		gameVars->pallette.gui.label.text.hover				= colors->Black;
//		gameVars->pallette.gui.label.text.active			= colors->Black;
//
//		gameVars->pallette.gui.checkBox.background.base		= colors->White;
//		gameVars->pallette.gui.checkBox.background.hover	= colors->Yellow;
//		gameVars->pallette.gui.checkBox.background.active	= colors->Black;
//		gameVars->pallette.gui.checkBox.border.base			= colors->Black;
//		gameVars->pallette.gui.checkBox.border.hover		= colors->Black;
//		gameVars->pallette.gui.checkBox.border.active		= colors->Black;
//		gameVars->pallette.gui.checkBox.text.base			= colors->Black;
//		gameVars->pallette.gui.checkBox.text.hover			= colors->Black;
//		gameVars->pallette.gui.checkBox.text.active			= colors->Black;
//
//		gameVars->pallette.gui.slider.bar.base				= colors->Gray;
//		gameVars->pallette.gui.slider.bar.hover				= colors->White;
//		gameVars->pallette.gui.slider.bar.active			= colors->Yellow;
//		gameVars->pallette.gui.slider.barBorder.base		= colors->Black;
//		gameVars->pallette.gui.slider.barBorder.hover		= colors->Black;
//		gameVars->pallette.gui.slider.barBorder.active		= colors->Black;
//		gameVars->pallette.gui.slider.control.base			= colors->Tan;
//		gameVars->pallette.gui.slider.control.hover			= colors->Orange;
//		gameVars->pallette.gui.slider.control.active		= colors->Green;
//		gameVars->pallette.gui.slider.controlBorder.base	= colors->Black;
//		gameVars->pallette.gui.slider.controlBorder.hover	= colors->Black;
//		gameVars->pallette.gui.slider.controlBorder.active	= colors->Black;
//		gameVars->pallette.gui.slider.text.base				= colors->Black;
//		gameVars->pallette.gui.slider.text.hover			= colors->Black;
//		gameVars->pallette.gui.slider.text.active			= colors->Black;
//
//		gameVars->pallette.gui.swatch.border.base			= colors->Black;
//		gameVars->pallette.gui.swatch.border.hover			= colors->Black;
//		gameVars->pallette.gui.swatch.border.active			= colors->Black;
//
//		gameVars->pallette.gui.textArea.background.base		= colors->White;
//		gameVars->pallette.gui.textArea.background.hover	= colors->White;
//		gameVars->pallette.gui.textArea.background.active	= colors->PaleGoldenrod;
//		gameVars->pallette.gui.textArea.border.base			= colors->Black;
//		gameVars->pallette.gui.textArea.border.hover		= colors->Black;
//		gameVars->pallette.gui.textArea.border.active		= colors->Black;
//		gameVars->pallette.gui.textArea.text.base			= colors->Black;
//		gameVars->pallette.gui.textArea.text.hover			= colors->Black;
//		gameVars->pallette.gui.textArea.text.active			= colors->Black;
//		gameVars->pallette.gui.textArea.scroll.base			= colors->Gray;
//		gameVars->pallette.gui.textArea.scroll.hover		= colors->White;
//		gameVars->pallette.gui.textArea.scroll.active		= colors->Yellow;
//		gameVars->pallette.gui.textArea.scrollBorder.base	= colors->Black;
//		gameVars->pallette.gui.textArea.scrollBorder.hover	= colors->Black;
//		gameVars->pallette.gui.textArea.scrollBorder.active	= colors->Black;
//		gameVars->pallette.gui.textArea.scrollText.base		= colors->Black;
//		gameVars->pallette.gui.textArea.scrollText.hover	= colors->Black;
//		gameVars->pallette.gui.textArea.scrollText.active	= colors->Black;
//
//		gameVars->pallette.gui.window.background.base		= colors->Brown;
//		gameVars->pallette.gui.window.background.hover		= colors->Brown;
//		gameVars->pallette.gui.window.background.active		= colors->Brown;
//		gameVars->pallette.gui.window.border.base			= colors->Black;
//		gameVars->pallette.gui.window.border.hover			= colors->Black;
//		gameVars->pallette.gui.window.border.active			= colors->Black;
//		gameVars->pallette.gui.window.stipple.base			= colors->Black;
//		gameVars->pallette.gui.window.stipple.hover			= colors->Black;
//		gameVars->pallette.gui.window.stipple.active		= colors->Black;
//
//		gameVars->pallette.gui.icon.background.base			= colors->White;
//		gameVars->pallette.gui.icon.background.hover		= colors->Yellow;
//		gameVars->pallette.gui.icon.background.active		= colors->Green;
//		gameVars->pallette.gui.icon.border.base				= colors->Black;
//		gameVars->pallette.gui.icon.border.hover			= colors->Black;
//		gameVars->pallette.gui.icon.border.active			= colors->Black;
//		gameVars->pallette.gui.icon.base					= colors->Black;
//		gameVars->pallette.gui.icon.hover					= colors->Black;
//		gameVars->pallette.gui.icon.active					= colors->Black;
//
//		gameVars->pallette.gui.sprite.background.base		= colors->Tan;
//		gameVars->pallette.gui.sprite.background.hover		= colors->Orange;
//		gameVars->pallette.gui.sprite.background.active		= colors->Green;
//		gameVars->pallette.gui.sprite.border.base			= colors->Black;
//		gameVars->pallette.gui.sprite.border.hover			= colors->Black;
//		gameVars->pallette.gui.sprite.border.active			= colors->Black;
//		gameVars->pallette.gui.sprite.base					= colors->White;
//
//		gameVars->pallette.gui.disabled.base.base			= colors->Gray60;
//		gameVars->pallette.gui.disabled.base.hover			= colors->Gray70;
//		gameVars->pallette.gui.disabled.stipple.base		= colors->Gray80;
//		gameVars->pallette.gui.disabled.stipple.hover		= colors->Gray70;
//		gameVars->pallette.gui.disabled.border.base			= colors->Gray30;
//		gameVars->pallette.gui.disabled.border.hover		= colors->Gray20;
//		gameVars->pallette.gui.disabled.text.base			= colors->Gray30;
//		gameVars->pallette.gui.disabled.text.hover			= colors->Gray20;

//		Color cTest = colors["Tan"];
//		eBuiltIn sTest = colors().

		gameVars->pallette.gui.button.background.base		= colors[colors().Tan];
		gameVars->pallette.gui.button.background.hover		= colors[colors().Orange];
		gameVars->pallette.gui.button.background.active		= colors[colors().Green];
		gameVars->pallette.gui.button.border.base			= colors[colors().Black];
		gameVars->pallette.gui.button.border.hover			= colors[colors().Black];
		gameVars->pallette.gui.button.border.active			= colors[colors().Black];
		gameVars->pallette.gui.button.text.base				= colors[colors().Black];
		gameVars->pallette.gui.button.text.hover			= colors[colors().Black];
		gameVars->pallette.gui.button.text.active			= colors[colors().Black];

		gameVars->pallette.gui.field.background.base		= colors[colors().Gray80];
		gameVars->pallette.gui.field.background.hover		= colors[colors().White];
		gameVars->pallette.gui.field.background.active		= colors[colors().Yellow];
		gameVars->pallette.gui.field.border.base			= colors[colors().Black];
		gameVars->pallette.gui.field.border.hover			= colors[colors().Black];
		gameVars->pallette.gui.field.border.active			= colors[colors().Black];
		gameVars->pallette.gui.field.text.base				= colors[colors().Black];
		gameVars->pallette.gui.field.text.hover				= colors[colors().Black];
		gameVars->pallette.gui.field.text.active			= colors[colors().Black];

		gameVars->pallette.gui.label.background.base		= colors[colors().White];
		gameVars->pallette.gui.label.background.hover		= colors[colors().White];
		gameVars->pallette.gui.label.background.active		= colors[colors().White];
		gameVars->pallette.gui.label.border.base			= colors[colors().Black];
		gameVars->pallette.gui.label.border.hover			= colors[colors().Black];
		gameVars->pallette.gui.label.border.active			= colors[colors().Black];
		gameVars->pallette.gui.label.text.base				= colors[colors().Black];
		gameVars->pallette.gui.label.text.hover				= colors[colors().Black];
		gameVars->pallette.gui.label.text.active			= colors[colors().Black];

		gameVars->pallette.gui.checkBox.background.base		= colors[colors().White];
		gameVars->pallette.gui.checkBox.background.hover	= colors[colors().Yellow];
		gameVars->pallette.gui.checkBox.background.active	= colors[colors().Black];
		gameVars->pallette.gui.checkBox.border.base			= colors[colors().Black];
		gameVars->pallette.gui.checkBox.border.hover		= colors[colors().Black];
		gameVars->pallette.gui.checkBox.border.active		= colors[colors().Black];
		gameVars->pallette.gui.checkBox.text.base			= colors[colors().Black];
		gameVars->pallette.gui.checkBox.text.hover			= colors[colors().Black];
		gameVars->pallette.gui.checkBox.text.active			= colors[colors().Black];

		gameVars->pallette.gui.slider.bar.base				= colors[colors().Gray80];
		gameVars->pallette.gui.slider.bar.hover				= colors[colors().White];
		gameVars->pallette.gui.slider.bar.active			= colors[colors().Yellow];
		gameVars->pallette.gui.slider.barBorder.base		= colors[colors().Black];
		gameVars->pallette.gui.slider.barBorder.hover		= colors[colors().Black];
		gameVars->pallette.gui.slider.barBorder.active		= colors[colors().Black];
		gameVars->pallette.gui.slider.control.base			= colors[colors().Tan];
		gameVars->pallette.gui.slider.control.hover			= colors[colors().Orange];
		gameVars->pallette.gui.slider.control.active		= colors[colors().Green];
		gameVars->pallette.gui.slider.controlBorder.base	= colors[colors().Black];
		gameVars->pallette.gui.slider.controlBorder.hover	= colors[colors().Black];
		gameVars->pallette.gui.slider.controlBorder.active	= colors[colors().Black];
		gameVars->pallette.gui.slider.text.base				= colors[colors().Black];
		gameVars->pallette.gui.slider.text.hover			= colors[colors().Black];
		gameVars->pallette.gui.slider.text.active			= colors[colors().Black];

		gameVars->pallette.gui.swatch.border.base			= colors[colors().Black];
		gameVars->pallette.gui.swatch.border.hover			= colors[colors().Black];
		gameVars->pallette.gui.swatch.border.active			= colors[colors().Black];

		gameVars->pallette.gui.textArea.background.base		= colors[colors().White];
		gameVars->pallette.gui.textArea.background.hover	= colors[colors().White];
		gameVars->pallette.gui.textArea.background.active	= colors[colors().Goldenrod];
		gameVars->pallette.gui.textArea.border.base			= colors[colors().Black];
		gameVars->pallette.gui.textArea.border.hover		= colors[colors().Black];
		gameVars->pallette.gui.textArea.border.active		= colors[colors().Black];
		gameVars->pallette.gui.textArea.text.base			= colors[colors().Black];
		gameVars->pallette.gui.textArea.text.hover			= colors[colors().Black];
		gameVars->pallette.gui.textArea.text.active			= colors[colors().Black];
		gameVars->pallette.gui.textArea.scroll.base			= colors[colors().Gray_web];
		gameVars->pallette.gui.textArea.scroll.hover		= colors[colors().White];
		gameVars->pallette.gui.textArea.scroll.active		= colors[colors().Yellow];
		gameVars->pallette.gui.textArea.scrollBorder.base	= colors[colors().Black];
		gameVars->pallette.gui.textArea.scrollBorder.hover	= colors[colors().Black];
		gameVars->pallette.gui.textArea.scrollBorder.active	= colors[colors().Black];
		gameVars->pallette.gui.textArea.scrollText.base		= colors[colors().Black];
		gameVars->pallette.gui.textArea.scrollText.hover	= colors[colors().Black];
		gameVars->pallette.gui.textArea.scrollText.active	= colors[colors().Black];

		gameVars->pallette.gui.window.background.base		= colors[colors().Liver_chestnut];
		gameVars->pallette.gui.window.background.hover		= colors[colors().Liver_chestnut];
		gameVars->pallette.gui.window.background.active		= colors[colors().Liver_chestnut];
		gameVars->pallette.gui.window.border.base			= colors[colors().Black];
		gameVars->pallette.gui.window.border.hover			= colors[colors().Black];
		gameVars->pallette.gui.window.border.active			= colors[colors().Black];
		gameVars->pallette.gui.window.stipple.base			= colors[colors().Black];
		gameVars->pallette.gui.window.stipple.hover			= colors[colors().Black];
		gameVars->pallette.gui.window.stipple.active		= colors[colors().Black];

		gameVars->pallette.gui.icon.background.base			= colors[colors().White];
		gameVars->pallette.gui.icon.background.hover		= colors[colors().Yellow];
		gameVars->pallette.gui.icon.background.active		= colors[colors().Green];
		gameVars->pallette.gui.icon.border.base				= colors[colors().Black];
		gameVars->pallette.gui.icon.border.hover			= colors[colors().Black];
		gameVars->pallette.gui.icon.border.active			= colors[colors().Black];
		gameVars->pallette.gui.icon.base					= colors[colors().Black];
		gameVars->pallette.gui.icon.hover					= colors[colors().Black];
		gameVars->pallette.gui.icon.active					= colors[colors().Black];

		gameVars->pallette.gui.sprite.background.base		= colors[colors().Tan];
		gameVars->pallette.gui.sprite.background.hover		= colors[colors().Orange];
		gameVars->pallette.gui.sprite.background.active		= colors[colors().Green];
		gameVars->pallette.gui.sprite.border.base			= colors[colors().Black];
		gameVars->pallette.gui.sprite.border.hover			= colors[colors().Black];
		gameVars->pallette.gui.sprite.border.active			= colors[colors().Black];
		gameVars->pallette.gui.sprite.base					= colors[colors().White];

		gameVars->pallette.gui.disabled.base.base			= colors[colors().Gray60];
		gameVars->pallette.gui.disabled.base.hover			= colors[colors().Gray70];
		gameVars->pallette.gui.disabled.stipple.base		= colors[colors().Gray80];
		gameVars->pallette.gui.disabled.stipple.hover		= colors[colors().Gray70];
		gameVars->pallette.gui.disabled.border.base			= colors[colors().Gray30];
		gameVars->pallette.gui.disabled.border.hover		= colors[colors().Gray20];
		gameVars->pallette.gui.disabled.text.base			= colors[colors().Gray30];
		gameVars->pallette.gui.disabled.text.hover			= colors[colors().Gray20];

		gameVars->pallette.gui.toolTip.header.text			= colors[colors().Black];
//		gameVars->pallette.gui.toolTip.header.text			= colors[colors().Gray50];
		gameVars->pallette.gui.toolTip.header.background	= colors[colors().Mango];
		gameVars->pallette.gui.toolTip.header.border		= colors[colors().Black];
		gameVars->pallette.gui.toolTip.textarea.text		= colors[colors().Gray10];
		gameVars->pallette.gui.toolTip.textarea.background	= colors[colors().Canary];
		gameVars->pallette.gui.toolTip.textarea.border		= colors[colors().Black];

		gameVars->pallette.gui.progressBar.background.base		= colors[colors().Gray40];
		gameVars->pallette.gui.progressBar.background.border	= colors[colors().Black];
		gameVars->pallette.gui.progressBar.progress.empty		= colors[colors().White];
		gameVars->pallette.gui.progressBar.progress.fill		= colors[colors().Baby_blue];
		gameVars->pallette.gui.progressBar.progress.border		= colors[colors().Black];



		// ###################################################################################################################################
		//Shaders
		//
//		for (int i=0; i<GLS_LAST; i++) {
//			gameVars->shader.bCurrent[i]=false;
//		}
		// Lighting values
	//	Core.shader.vEyeLight[0] =	200.0;
	//	Core.shader.vEyeLight[1] =	100.0;
	//	Core.shader.vEyeLight[2] =	-175.0;
	//	Core.shader.vEyeLight[0] =	0;
	//	Core.shader.vEyeLight[1] =	100;
	//	Core.shader.vEyeLight[2] =	0;

		//world.atmosphere.sun.vPosition[0] = 300;
		//world.atmosphere.sun.vPosition[1] = 200;
		//world.atmosphere.sun.vPosition[2] = 200;

		//Core.shader.vEyeLight[0] =	300.0;
		//Core.shader.vEyeLight[1] =	200.0;
		//Core.shader.vEyeLight[2] =	200.0;

		//Core.shader.vAmbientColor[0] =	0.1f;
		//Core.shader.vAmbientColor[1] =	0.1f;
		//Core.shader.vAmbientColor[2] =	0.1f;
		//Core.shader.vAmbientColor[3] =	1.0f;

	//	Core.shader.vAmbientColor[0] =	0.2f;
	//	Core.shader.vAmbientColor[1] =	0.2f;
	//	Core.shader.vAmbientColor[2] =	0.1f;
	//	Core.shader.vAmbientColor[3] =	0.0f;

		//Core::Shader.vDiffuseColor[0] =	0.7f;
		//Core::Shader.vDiffuseColor[1] =	0.7f;
		//Core::Shader.vDiffuseColor[2] =	0.3f;
		//Core::Shader.vDiffuseColor[3] =	1.0f;

		//Core.shader.vDiffuseColor[0] =	1.0f;
		//Core.shader.vDiffuseColor[1] =	1.0f;
		//Core.shader.vDiffuseColor[2] =	1.0f;
		//Core.shader.vDiffuseColor[3] =	1.0f;

		//Core.shader.vSpecularColor[0] =	1.0f;	//Red
		//Core.shader.vSpecularColor[1] =	1.0f;	//Green
		//Core.shader.vSpecularColor[2] =	1.0f;	//Blue
		//Core.shader.vSpecularColor[3] =	1.0f;	//Unused

		//Core.shader.fShininess = 5.0f;

//		Core.shader.worldFog.vFogColor[0]			=	0.5f;
//		Core.shader.worldFog.vFogColor[1]			=	0.5f;
//		Core.shader.worldFog.vFogColor[2]			=	0.7f;
//		Core.shader.worldFog.vFogColor[3]			=	0.75f;
//
//		Core.shader.worldFog.fStart					=	1200;			//Fog Start (Linear)
//		Core.shader.worldFog.fEnd					=	2000;			//Fog End (Linear)
//		Core.shader.worldFog.fDensity				=	0.00001f;	//Density (Exponential)
//		Core.shader.worldFog.iEquation				=	2;				//Equation (0=Linear, 1=Exp1, 2=Exp2)
//
//		Core.shader.waterFog.vFogColor[0]			=	0.1f;
//		Core.shader.waterFog.vFogColor[1]			=	0.1f;
//		Core.shader.waterFog.vFogColor[2]			=	0.2f;
//		Core.shader.waterFog.vFogColor[3]			=	1.0f;
//
//		Core.shader.waterFog.fStart					=	1200;			//Fog Start (Linear)
//		Core.shader.waterFog.fEnd					=	2000;			//Fog End (Linear)
//		//Core.shader.waterFog.fDensity				=	0.05f;		//Density (Exponential)
//		Core.shader.waterFog.fDensity				=	0.0001f;		//Density (Exponential)
//		Core.shader.waterFog.iEquation				=	2;				//Equation (0=Linear, 1=Exp1, 2=Exp2, 3=off)
//
//		Core.shader.activeFog.vFogColor[0]			=	0.5f;
//		Core.shader.activeFog.vFogColor[1]			=	0.5f;
//		Core.shader.activeFog.vFogColor[2]			=	0.9f;
//		Core.shader.activeFog.vFogColor[3]			=	1.0f;
//
//		Core.shader.activeFog.fStart				=	1200;			//Fog Start (Linear)
//		Core.shader.activeFog.fEnd					=	2000;			//Fog End (Linear)
//		Core.shader.activeFog.fDensity				=	0.0003f;	//Density (Exponential)
//		Core.shader.activeFog.iEquation				=	2;				//Equation (0=Linear, 1=Exp1, 2=Exp2)

		// Screen Rendering Modes (Default shader setting)
		//gameVars->shader.bCurrent[GLS_NORMAL_LINE2]			=	false;	// Shows vertex normals
		//gameVars->shader.bCurrent[GLS_SHADED_TEX]			=	false;	// Textured, NOT shaded										(Used in Dungeon and WinSys)
		//gameVars->shader.bCurrent[GLS_SHADED_TEX_ALPHA]		=	false;	// Textured with alpha, not shaded				(Used in Dungeon)
		//gameVars->shader.bCurrent[GLS_DIRECTIONAL] 			= true;		// Textured Interpolated shading					Single Texture opjects
		//gameVars->shader.bCurrent[GLS_DIRECTIONAL_TERRAIN]	= false;	// Textured Interpolated shading					World Terrain w/ multitexturing

		// ###################################################################################################################################
		// States
		//
//		gameVars->state.debug					= false;
//		gameVars->state.dev						= false;
//		gameVars->state.console					= false;
//		gameVars->state.main_menu				= true;
//		gameVars->state.book						= false;
//		gameVars->state.menu						= false;
//		gameVars->state.admin					= false;
//		gameVars->state.battle					= false;
//		gameVars->state.event					= false;
//		gameVars->state.dungeon					= false;
//		gameVars->state.city						= false;
//		gameVars->state.thevoid					= false;	//This is currently the default
//		gameVars->state.world					= true;		//This is currently the default
//		gameVars->state.quit						= false;


		gameVars->runState.main_menu				= false;
		gameVars->runState.console				= false;
		gameVars->runState.admin					= false;
		gameVars->runState.skill					= false;
		gameVars->runState.endBattle				= false;
		gameVars->runState.book					= false;
		gameVars->runState.menu					= false;
		gameVars->runState.event					= false;
		gameVars->runState.battle				= false;
		gameVars->runState.dungeon				= false;
		gameVars->runState.city					= false;
		gameVars->runState.world					= true;
		gameVars->runState.quit					= false;

		// ###################################################################################################################################
		// Textures
//		#define system 0
//		#define	sprite 1
//		#define terrain 2
//		#define icon 3
//		#define sys_sprite 4
//		#define menu 5
//
//		//Texture Values
//		//gameVars->texture.uiNumTextures				= 64;		//Amount of textures to allocate room for (Temporary holder until below are fully implemented)
//		gameVars->texture.iNumTextures[system]		= 64;		//Amount of textures to allocate room for
//		gameVars->texture.iNumTextures[sprite]		= 64;		//Amount of textures to allocate room for
//		gameVars->texture.iNumTextures[terrain]		= 64;		//Amount of textures to allocate room for
//		gameVars->texture.iNumTextures[icon]		= 64;		//Amount of textures to allocate room for
//		gameVars->texture.iNumTextures[sys_sprite]	= 64;		//Amount of textures to allocate room for
//		gameVars->texture.iNumTextures[menu]		= 64;		//Amount of textures to allocate room for
//
//		#undef system
//		#undef sprite
//		#undef terrain
//		#undef icon
//		#undef sys_sprite
//		#undef menu

		// ###################################################################################################################################
		//Timer settings
//		gameVars->timer.lampTimer.rate				=	20;			//The rate for lamp updates
//		gameVars->timer.shadow.rate					=	0.1;		//Framerate for shadows
//		gameVars->timer.shadow.rateMod				=	0;
//		gameVars->timer.animation.rate				=	10;			//Framerate for animated tiles
//		gameVars->timer.animation.rateMod			=	0;
//		gameVars->timer.mouseTimeout.rate			=	500;			//The rate for timed mouse events (ms)

		// ###################################################################################################################################
		//Initial camera settings (Rotation is CCW)
//		gameVars->transform.fCrouchDiff				=	0.5;									//Change in character height AND speed for crouching
//		gameVars->transform.fProneDiff				=	0.10;									//Change in character height AND speed for prone
//		gameVars->transform.water.x					=	0;
//		gameVars->transform.water.z					=	0;
//		gameVars->transform.water.h					=	10;										//CURRENTLY UNUSED
//		gameVars->transform.jumpPosition 			=	0.0f;
//		gameVars->transform.jumpVelocity 			=	0.1f;
//		gameVars->transform.jumpMaxVelocity			=	-0.1f;
//		gameVars->transform.maxIncline				=	1.5;									//Maximum slope change while walking in world, does not effect decline
		//gameVars->transform.iLoadLimit			=	0;										//DEBUG VARIABLE, LOAD NEW MAP ONLY ONE TIME
		//gameVars->transform.worldRot[1]			=	RADIAN*180;								//Look left-right
		//gameVars->transform.worldRot[0]			=	0;										//Look up-down
		//gameVars->transform.worldPos[0]			=	0;										//Relative stafe left-right
		//gameVars->transform.worldPos[1]			=	0;										//Height Position
		//gameVars->transform.worldPos[2]			=	0;										//Relative forward-back
		//gameVars->transform.eyeHeight				=	-26.8;									//Character height (26.8 = 5.5 feet) [SHOULD NOT CHANGE AFTER LOADING]
		//gameVars->transform.currentHeight			=	gameVars->transform.eyeHeight;
		//gameVars->transform.currentHeight			=	-26.8;
		//gameVars->transform.eyeHeight				=	-26.8;
		//gameVars->transform.fReach				=	16;										//Character reach

		// ###################################################################################################################################
		// GLOBAL WORLD VARIABLES
		//gameVars->world.water.iHeight				=	-8;		//Sea Level
//		gameVars->world.water.iHeight				=	-8;		//Sea Level



		// ###################################################################################################################################
		// Older possibly un-usable data
		//Default light and shadow settings
//		gameVars->sky.sunDir						=	190;
//		gameVars->sky.num							=	2;
//		gameVars->shadow.enable						=	false;
//		gameVars->shadow.realtime					=	false;
//		gameVars->shadow.res						=	16;										// Resolution of shadow map
	}
}
#endif /* SETTINGS_H_ */
