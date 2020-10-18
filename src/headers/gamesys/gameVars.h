/*
 * structs.hpp
 *
 *  Created on: May 23, 2010
 *      Author: bcthund
 *
 *      This holds all of the settings for the game that is often needed all over the game
 *      It is often passed by reference because it is a large set of data.
 */

#ifndef GAMEVARS_HPP_
#define GAMEVARS_HPP_

//#include "SDL2/SDL.h"
//#include "../core/extern.h"
#include "../core/core_functions.h"
#include "../core/ptimer.h"
#include "CharSheet.h"

namespace Core {
	struct GameVars {
		GLenum errCode;

		/*
		 * Screen Settings
		 * All the information with regards to the screen resolution,
		 * 		the rendering distance, the terrain loading distance,
		 * 		and other rendering options.
		 */
		struct Screen {
			int bpp, frameRate;
			int clear; // Should the screen get cleared every frame
			//int iTerrainGrid;  //Basically the loaded view distance, should be an odd number (1,3,5,7,9 Max)
			float fScale;				// Scale of the world, this effects calculations of EVERYTHING in the world. This makes the terrain cover a larger area.

			// Projection Matrix Data and related dependant data
//			struct t_ProjectionData {
//				Vector2f res;
//				Degrees degFov;
//				float fNear, fFar;
//				float fScreenAspect, fDistanceAspect;
//				Vector2f half;
//				Vector2i origin;
//
//				void init() {
//					fScreenAspect	= res.x/res.y;
//					fDistanceAspect	= fNear/fFar;
//					half.x			= res.x/2;
//					half.y			= res.y/2;
//					origin[0]		= -half.x;
//					origin[1]		= half.y;
//				}
//			};
			t_UMap<std::string, t_ProjectionData*> projectionData;
			t_ProjectionData *activeProjection;

			t_ProjectionData& setActiveProjection(std::string name) {
				activeProjection = projectionData[name];
				return *activeProjection;
			}

			t_ProjectionData& getActiveProjection() {
				return *activeProjection;
			}

			bool MultiSample, bInterlaced;
			uint uiMultiSamples;
			SDL_Surface * surface;
			Vector4f vClearColorBase;
			Vector4f vClearColorCurrent;

			Screen() : bpp(0),
					   frameRate(0),
					   //fHalfW(0),
					   //fHalfH(0),
//					   fScreenAspect(0),
//					   fDistanceAspect(0),
					   clear(1),
					   //iTerrainGrid(0),
					   fScale(1.0f),
//					   fNear(0),
//					   fFar(0),
//					   degFov(0),
					   MultiSample(false),
					   bInterlaced(false),
					   uiMultiSamples(4) {
				activeProjection = nullptr;
				surface = new SDL_Surface;
//				res[0] = 0;
//				res[1] = 0;
//				half[0] = 0;
//				half[1] = 0;
				vClearColorBase[0] = 0;
				vClearColorBase[1] = 0;
				vClearColorBase[2] = 0;
				vClearColorBase[3] = 0;
				vClearColorCurrent[0] = 0;
				vClearColorCurrent[1] = 0;
				vClearColorCurrent[2] = 0;
				vClearColorCurrent[3] = 0;
//				origin[0] = 0;
//				origin[1] = 0;
			}

			~Screen() {
				delete surface;
				for ( auto item : projectionData ) delete item.second;
			}
		} screen;

		/*
		 * The Current execution state
		 *
		 * 	Different modes of the application, these control
		 * 		the main routine of the application. After
		 * 		initialization, one of these modes is called
		 * 		continuously until the mode is changed.
		 */
		struct RunState {
			bool	quit,
					console,
					main_menu,
					admin,
					skill,
					endBattle,
					menu,
					event,
					battle,
					dungeon,
					city,
					world,
					book,
					debug,
					dev;
			//float fTimeout, fTimeoutMax;
			//int book;	//1=journal, 2=battlescroll, 3=grimoire
			RunState() :	quit(false),
							console(false),
							main_menu(false),
							admin(false),
							skill(false),
							endBattle(false),
							book(false),
							menu(false),
							event(false),
							battle(false),
							dungeon(false),
							city(false),
							world(false),
							debug(false),
							dev(false) {}
		} runState;

		struct _Debug {
			struct _Noise {
				struct _Perlin {
					bool bEnable;	// Enable these debug variables
					float octave1, octave2, octave3, octave4, octave5, octave6;
					float power;
					float scale;
					_Perlin() {
						bEnable		= true;
						octave1		= 1.0f;
						octave2		= 0.48f;
						octave3		= 0.23f;
						octave4		= 0.10f;
						octave5		= 0.04f;
						octave6		= 0.02f;
						power		= 3.6f;
						scale		= 10000.0f;
					}
				} perlin;

//				struct _Simplex {
//					bool bEnable;	// Enable these debug variables
//					int res;
//					float tex_scale;
//					int terrain_size;
//					float terrain_height_offset;
//
//					Vector2f offset;
//					float frequency, amplitude, lacunarity, persistance;
//					int octaves;
//					float power;
//					float scale;
//					float delta;
//					_Simplex() {
//						bEnable		= true;
//
//						res = 256;
//						tex_scale = 128.0f;
//						terrain_size = 16384;
//						terrain_height_offset = 0.0f;
//
//						delta		= 32.0f;
//						frequency	= 0.00025f; //0.0006; //0.000076; //0.00025f;
//						amplitude	= 1.0f;
//						lacunarity	= 2.9f; //6.553f; //6.004; //6.75325; //8.0f;
//						persistance	= 0.33f; //0.139f; //0.150; //0.175; //0.175f;
//						power		= 1.0f;
//						scale		= 875.0f; //500.0f; //275.0f; //1750; //2500;
//						octaves		= 3;
//					}
//				} simplex[3];

				struct _Fractal {
					bool bEnable;	// Enable these debug variables
					int res;
					float tex_scale;
					int terrain_size;
					float terrain_height_offset;

					Vector2f offset;
					float frequency, lacunarity, multiplier;
					int layers;
//					float power;
					float scale;
					float delta;
					_Fractal() {
						bEnable		= true;

						res = 64;
						tex_scale = 128.0f;
						terrain_size = 16384;
						terrain_height_offset = 0.0f;

						delta		= 32.0f;
						frequency	= 0.00025f; //0.0006; //0.000076; //0.00025f;
						lacunarity	= 2.9f; //6.553f; //6.004; //6.75325; //8.0f;
						multiplier	= 0.33f; //0.139f; //0.150; //0.175; //0.175f;
//						power		= 1.0f;
						scale		= 875.0f; //500.0f; //275.0f; //1750; //2500;
						layers		= 3;
					}
				} fractal[3];

				int iCurrentSimplex;	// Currently selected simplex index for admin menu
				int iCurrentFractal;	// Currently selected simplex index for admin menu

				_Noise() {
					iCurrentSimplex = 0;
					iCurrentFractal = 0;
					// Base layer
//					simplex[0].res			= 64;
//					simplex[0].terrain_size = 8192.0f;
//					simplex[0].frequency	= 0.00013f; //0.00025f;
//					simplex[0].lacunarity	= 2.6f; //3.3f; //2.9f;
//					simplex[0].persistance	= -0.37f; //0.28f; //0.33f;
//					simplex[0].scale		= 875.0f;
//					simplex[0].octaves		= 3;
//
//					// Mountain layer
//					simplex[1].res			= 64;
//					simplex[1].terrain_size = 8192.0f;
//					simplex[1].frequency	= 0.00002f;
//					simplex[1].lacunarity	= 0.7f;
//					simplex[1].persistance	= 0.11f;
//					simplex[1].scale		= 5000.0f;
//					simplex[1].octaves		= 1;
//
//					// Persistance layer
//					simplex[2].res			= 64;
//					simplex[2].terrain_size = 8192.0f;
//					simplex[2].frequency	= 0.00001f;
//					simplex[2].lacunarity	= 0.7f;
//					simplex[2].persistance	= 0.11f;
//					simplex[2].scale		= 5000.0f;
//					simplex[2].octaves		= 1;
				}

			} noise;

			struct _gui {
				float f, f2;
				bool b1,
					 b2,
					 b3,
					 b4,
					 b5;
				bool bSkillButton;
				bool bDrawTest;
				int i;
				std::string	s;
				Vector4f colors[8];
				std::shared_ptr<std::string> buffer;

				_gui() {
					bDrawTest	= false;
					f = 1.123f;
					b1 = false;
					b2 = false;
					b3 = false;
					b4 = false;
					b5 = true;
					bSkillButton = false;
					i = 456;
					f2 = 1.0f;
					s = "Test";
					colors[0] = Vector4f(1, 0, 0, 1);
					colors[1] = Vector4f(0, 1, 0, 1);
					colors[2] = Vector4f(0, 0, 1, 1);
					colors[3] = Vector4f(0, 0, 0, 1);
					colors[4] = Vector4f(1, 1, 1, 1);
					colors[5] = Vector4f(0.5, 0.5, 0.5, 1);
					colors[6] = Vector4f(0.5, 0.5, 0.5, 0.5);
					colors[7] = Vector4f(1, 1, 0, 1);
					buffer = std::make_shared<std::string>("Test block of text for TextArea remote pointer and editing.");
				}

			} gui;

			struct _audio {
				int volume;
				int iMusicTrack;

				_audio() {
					volume = 128;
					iMusicTrack = 0;
				}
			} audio;

		} debug;

		// FIXME: Pallettes are in the Colors class(not currently used), fix implementation
		struct _Pallette {
			struct _Pallette_GroupBHA { Color base, hover, active; };
			struct _Pallette_GroupBH { Color base, hover; };

			struct {
				// FIXME: Enabled/Disabled colors (Global color scheme for disabled?)
				struct {
					_Pallette_GroupBH base, border, text, stipple;
				} disabled;

				struct {
					_Pallette_GroupBHA border;
				} swatch;

				struct {
					_Pallette_GroupBHA	background,
										border,
										stipple;
				} window;

				struct {
					_Pallette_GroupBHA	background,
										border,
										text;
				} button, field, label, checkBox;

				struct {
					_Pallette_GroupBHA background,
										border;
					Color base, hover, active;
				} icon;

				struct {
					_Pallette_GroupBHA background,
									border;
					Color base;
				} sprite;

				struct {
					_Pallette_GroupBHA bar,
										barBorder,
										control,
										controlBorder,
										text;
				} slider;

				struct {
					struct {
						Color base, border;
					} background;

					struct {
						Color empty, fill, border;
					} progress;

				} progressBar;

				struct {
					struct {
						Color text, background, border;
					} header, textarea;
				} toolTip;

				struct {
					_Pallette_GroupBHA background, border, text, scroll, scrollBorder, scrollText;
				} textArea;

			} gui;

		} pallette;

// #=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#
// #=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#
// Items below here have not been officially adapted // TODO: Put appropriate items into standalone classes
// #=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#
// #=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#


		/*
		 * Data arrays for for different modes
		 *
		 * Each mode requires a basic set of data arrays that
		 * 	are all nearly identical. As new data is needed
		 * 	the array structure is modified to contain the new
		 * 	data regardless if it is needed for all modes.
		 *
		 * 	MapData: Contains the terrain, dungeon layout, city layout, etc
		 * 	O2dData: 2D objects, no interaction
		 * 	O3dData: 3D objects, no interaction
		 * 	E2dData: 2D objects, interaction capable
		 */
//		struct Data {
//			struct World {
//				//MapData		mapData[9][9];
//				//O2dData		o2dData[9][9];
//				//O2DGroups	o2dGroup[256];
//				//O3dData		o3dData[9][9];
//				//E2dData		e2dData[9][9];
//				//E2DGroups	e2dGroup[256];
//			} world;
//
//			struct Dungeon {
//				//MapData		mapData[9][9];
//				//O2dData		o2dData[9][9];
//				//O2DGroups		o2dGroup[256];
//				//O3dData		o3dData[9][9];
//				//E2dData		e2dData[9][9];
//				//E2DGroups		e2dGroup[256];
//			};
//		} data;

		/*
		 * Shader List
		 * Each value determines if that shader is part of the
		 * 		rendering pass. Each enabled shader results in
		 * 		one pass. Most are not used anymore.
		 */
//		struct Shader {
//			 unsigned int currentShader;
//			 bool bCurrent[GLS_LAST];
//	//		 bool bFLAT;
//	//		 bool bNORMAL;
//	//		 bool bNORMAL_LINE;
//	//		 bool bNORMAL_TRI;
//	//		 bool bSHADED;
//	//		 bool bDIFFUSE;
//	//		 bool bDIFFUSE2;
//	//		 bool bGOURAUD;
//	//		 bool bPHONG;
//	//		 bool bSHADED_TEX;
//	//		 bool bADS_TEX;
//	//		 bool bDIRECTIONAL;
//	//		 bool bTYPHOON_DIRECTIONAL;
//			 Shader() :	 currentShader(0) {}
//	//					 bFLAT(false),
//	//					 bNORMAL(false),
//	//					 bNORMAL_LINE(false),
//	//					 bNORMAL_TRI(false),
//	//					 bSHADED(false),
//	//					 bDIFFUSE(false),
//	//					 bDIFFUSE2(false),
//	//					 bGOURAUD(false),
//	//					 bPHONG(false),
//	//					 bSHADED_TEX(false),
//	//					 bADS_TEX(false),
//	//					 bDIRECTIONAL(false),
//	//					 bTYPHOON_DIRECTIONAL(false) {}
//		} shader;

		/*
		 *	System timers
		 *
		 *	Used to track times in between calls to control
		 *		framerates, movement rates, animations, etc.
		 */
		struct Timers {
			//Timer shadow;
			//Timer animation;
			//Timer mouseTimeout;     //Timer for mouse input
			Timer frameRate;        //Timer for the Frame Rate
			//Timer lampTimer;        //Timer for the lamp shading
			PTimer pTimer;          //Timer for tracking process times
			//Timer gameTime;
			//FPS fps;
		} timer;

//		struct SysData {
//			struct _data {
//				int RecordSize;
//				std::string BinFile;
//				std::string TexDir;
//				//std::string DataDir;
//				_data() {
//					RecordSize = 0;
//					TexDir = "";
//					//DataDir = "";
//				}
//			} o2d, o3d, animation, icon, sprite, win, text;
//		} data;
//
//		struct test {
//			struct _data {
//			};
//		};

		/*
		 * Holds the size of each record for the binary file
		 */
//		struct RecordSize {
//			int map, o2d, o3d, e2d, elf, data, animation, image, iconsys, spritesys, winsys, font, system;
//			RecordSize():	map(0),
//							o2d(0),
//							o3d(0),
//							e2d(0),
//							elf(0),
//							data(0),
//							animation(0),
//							image(0),
//							iconsys(0),
//							spritesys(0),
//							winsys(0),
//							font(0),
//							system(0) {}
//		} recordSize;

		/*
		 * Holds the directory that the corresponding data is in
		 */
//		struct Directory {
//			std::string //o2d,
//						//o3d,
//						//e2d,
//						//elf,
//						o3d,
//						o3dtex,
//						text,
//						sprite,
//						win,
//						icon,
//						animation,
//						shaders;
//
//			Directory() :	//o2d(""),
//							//o3d(""),
//							//e2d(""),
//							//elf(""),
//							o3d(""),
//							o3dtex(""),
//							text""),
//							sprite(""),
//							win(""),
//							icon(""),
//							animation(""),
//							shaders("") {}
//		} dir;

		/*
		 * Contains all of the VAO's for all systems
		 */
//		struct Display {
//			//struct Dungeon {
//			//	VAO o3d[256];		// 3D objects in dungeons
//			//} dungeon;
//			//struct Battle {
//				//vao npc;
//			//};
//			struct System {
//				VAO font[96];					// VAO for text rendering
//				//VAO menu[100];				// VAO for menu rendering
//				//VAO console[3];				// ???
//				//VAO icons[64];				// VAO for 64 icons in one image file, swap image for different icons, no change to VAO
//				//VAO animations[64];		// 64 frames
//				//VAO sys_sprite;				// VAO for 2D orthographic sprites
//			} system;
//		} vao;

		/*
		 * Texture set classes, each class has
		 * 		a list of textures loaded and
		 * 		they can be set by either their
		 * 		ID number if known or the file
		 * 		name.
		 */
//		struct TextureSet {
//			//Texture terrain;
//			struct System {
//				Texture font;
//				Texture menu;
//			} system;
//			//Texture sprite;
//			//Texture sys_sprite;
//			//Texture effect;
//			//Texture icons;
//			//int iNumTextures[8];  //Texture allocation values, up to 4 subsystems (0=system, 1=sprite, 2=terrain...)
//			TextureSet() {}
//		} texture;

		/*
		 * Debugging messages
		 * We need to expand this, each value represents a particular
		 * 		part of the engine and debugging messages are printed
		 * 		if the corresponding value is true.
		 *
		 * We want this divided into structs for different areas
		 */
		struct GameDebug {
			bool //init,
				 load;
				 //lamp,
				 //mouse,
				 //keyboard,
				 //temp,
				 //shadow,
				 //bb,
				 //map,
				 //lag,
				 //sky,
				 //fps,
				 //sun,
				 //loadMap,								// Allow new maps to load when walking around world
				 //stitchMap,							// Enable/Disable map stitching (fairly slow when enabled)
				 //mem,
				 //MASTER,
				 //runworld_map_calc,
				 //runworld_o2d_calc,
				 //runworld_o3d_calc,
				 //runworld_e2d_calc,
				 //dungeon_map_calc,
				 //dungeon_o3d_calc,
				 //manual_sun;				//Toggle manual sun direction control

			struct _Draw_Modes {
				//bool	//map,
						//atmosphere,
						//water,
						//e2d,
						//o2d,
						//o3d,
						//npc;
						//snow,
						//rain,
						//hail,
						//flora,
						//grass;

				_Draw_Modes(){};	//map(true),					// Very small increase in memory usage
								//atmosphere(true),		// No apparent increase in memory usage
								//water(true),			// ?
								//e2d(true),					// Probably a memory leak here
								//o2d(true),					// Probably a memory leak here
								//o2d_instance(true),	// Use instancing for 2d objects: BILLBOARDING BROKEN
								//o3d(true),
								//npc(true) {}				// Probably a memory leak here
								//snow(false),
								//rain(false),
								//hail(false),
								//flora(true),
								//grass(true) {}
			} draw;

			//int lines, length;

			GameDebug(): 	//init(false),
							load(true) {}
							//lamp(false),
							//mouse(false),
							//keyboard(false),
							//temp(false),
							//shadow(false),
							//bb(false),
							//map(false),
							//lag(false),
							//sky(false),
							//fps(false),
							//sun(false),
							//mem(false),
							//loadMap(false),
							//stitchMap(false),
							//MASTER(false),
							//runworld_map_calc(false),
							//runworld_o2d_calc(false),
							//runworld_o3d_calc(false),
							//runworld_e2d_calc(false),
							//dungeon_map_calc(false),
							//dungeon_o3d_calc(false),
							//manual_sun(false),
							//iCount(0),
							//lines(0),
							//length(0) {}

			/*
			 * Used to enable/disable debugging timers
			 * These timers track how long the engine is
			 * 		in a certain function call or how
			 * 		long a certain routine is in ms.
			 */
			struct Time {
	//			 bool 	timers,
	//					load,
	//					gameLoop,
	//					debug,
	//					runWorld,
	//					runDungeon,
	//					input,
	//					gameUpdate,
	//					motionBlur,
	//					gameDraw,
	//					getHeight,
	//					temp;
	//
	//			 bool 	capture,
	//					window,
	//					command,
	//					buffer;

				 Time(){} //: 	timers(false),
	//						load(false),
	//						gameLoop(false),
	//						debug(false),
	//						runWorld(false),
	//						runDungeon(false),
	//						input(false),
	//						gameUpdate(false),
	//						motionBlur(false),
	//						gameDraw(false),
	//						getHeight(true),
	//						temp(false),
	//						capture(false),
	//						window(false),
	//						command(false),
	//						buffer(false) {}

			} time;

			/*
			 * This is used to show the position of the sun as a vector
			 * 		for reference purposes. We can use this to setup the
			 * 		moving sun and see the time pass as a vector instead
			 * 		of an image in the sky which can be misleading.
			 */
			//struct Camera {
			//	bool bSunView;
			//	Camera() : bSunView(0) {}
			//} camera;

			//long int iCount;
		} debug_old;

		/*
		 * Contains all of the settings and calculations
		 * 		for the system font.
		 */

		// FIXME: Move into standalone class
		struct Font {
			int iPointSize;
			Vector2i vMax;				// Max characters width[0] and height[1]
			Vector2f vSize;				// Font size, based on vMax and screen resolution
			Vector2f vHalfSize;			// Half of the font size (What did I need this for??)
//			Vector4f vColor;			// Current global font color
//			Vector4f vTempColor;		// Temporary font color
//			Vector4f vHighlight;		// Highlighting color
			Vector2f screenCoords;		// Hold the position of the absolute center of the screen
			int		iTexNum;			// Font texture
			int		spacing;			// Space between line (in pixels)
			char	cCursorI;			// FIXME: This should be in textSys
			char	cCursorO;			// FIXME: This should be in textSys
			int		iRepeatDebounce;	// FIXME: This should be in textSys
//			int consoleLines;			// Number of lines in the console (This should be moved somewhere else)

			void update() {
				setFont();
			}

			void setFont() {
				vSize.x = 0.8*iPointSize;
				vSize.y = iPointSize;
				vHalfSize.x = vSize.x/2.0f;
				vHalfSize.y = vSize.y/2.0f;
//				vMax[0] = screen.res.x/vSize[0];
//				vMax[1]	= screen.res.y/vSize[1];
			}

			void setFont(int h) {
				iPointSize = h;
				vSize.x = 0.8*h;
				vSize.y = h;
				vHalfSize.x = vSize.x/2.0f;
				vHalfSize.y = vSize.y/2.0f;
//				vMax[0] = screen.res.x/vSize[0];
//				vMax[1]	= screen.res.y/vSize[1];
			}

			void setFont(int w, int h) {
				vSize.x = w;
				vSize.y = h;
				vHalfSize.x = vSize.x/2.0f;
				vHalfSize.y = vSize.y/2.0f;
//				vMax[0] = screen.res.x/vSize[0];
//				vMax[1]	= screen.res.y/vSize[1];
			}

			Font() : iTexNum(0)
			{
				iPointSize = 10;

				vMax[0] = {0};
				vMax[1] = {0};

				vSize[0] = {0};
				vSize[1] = {0};

				vHalfSize[0] = {0};
				vHalfSize[1] = {0};

				cCursorI = '\xFE';		// FIXME: This should be in textSys
				cCursorO = '\xFF';		// FIXME: This should be in textSys
				iRepeatDebounce = 500;	// FIXME: This should be in textSys

//				vColor[0] = {0};
//				vColor[1] = {0};
//				vColor[2] = {0};
//				vColor[3] = {0};
//
//				vTempColor[0] = {0};
//				vTempColor[1] = {0};
//				vTempColor[2] = {0};
//				vTempColor[3] = {0};

				screenCoords[0] = {0};
				screenCoords[1] = {0};

				spacing = 2;

//				a[4][2] = {0};
//				A[4][2] = {0};
//				b[4][2] = {0};
//				B[4][2] = {0};
//				c[4][2] = {0};
//				C[4][2] = {0};
//				d[4][2] = {0};
//				D[4][2] = {0};
//				e[4][2] = {0};
//				E[4][2] = {0};
//				f[4][2] = {0};
//				F[4][2] = {0};
//				g[4][2] = {0};
//				G[4][2] = {0};
//				h[4][2] = {0};
//				H[4][2] = {0};
//				i[4][2] = {0};
//				I[4][2] = {0};
//				j[4][2] = {0};
//				J[4][2] = {0};
//				k[4][2] = {0};
//				K[4][2] = {0};
//				l[4][2] = {0};
//				L[4][2] = {0};
//				m[4][2] = {0};
//				M[4][2] = {0};
//				n[4][2] = {0};
//				N[4][2] = {0};
//				o[4][2] = {0};
//				O[4][2] = {0};
//				p[4][2] = {0};
//				P[4][2] = {0};
//				q[4][2] = {0};
//				Q[4][2] = {0};
//				r[4][2] = {0};
//				R[4][2] = {0};
//				s[4][2] = {0};
//				S[4][2] = {0};
//				t[4][2] = {0};
//				T[4][2] = {0};
//				u[4][2] = {0};
//				U[4][2] = {0};
//				v[4][2] = {0};
//				V[4][2] = {0};
//				w[4][2] = {0};
//				W[4][2] = {0};
//				x[4][2] = {0};
//				X[4][2] = {0};
//				y[4][2] = {0};
//				Y[4][2] = {0};
//				z[4][2] = {0};
//				Z[4][2] = {0};
//				num0[4][2] = {0};
//				num5[4][2] = {0};
//				num1[4][2] = {0};
//				num6[4][2] = {0};
//				num2[4][2] = {0};
//				num7[4][2] = {0};
//				num3[4][2] = {0};
//				num8[4][2] = {0};
//				num4[4][2] = {0};
//				num9[4][2] = {0};
//				SPACE[4][2] = {0};
//				LESS[4][2] = {0};
//				EXCLAIM[4][2] = {0};
//				EQUALS[4][2] = {0};
//				QUOTE[4][2] = {0};
//				GREATER[4][2] = {0};
//				COLON[4][2] = {0};
//				SEMICOLON[4][2] = {0};
//				AT[4][2] = {0};
//				QUESTION[4][2] = {0};
//				NULLCHAR[4][2] = {0};
//				PIPE[4][2] = {0};
//				LBRACE[4][2] = {0};
//				RBRACE[4][2] = {0};
//				TILDE[4][2] = {0};
//				BACKSLASH[4][2] = {0};
//				LBRACKET[4][2] = {0};
//				RBRACKET[4][2] = {0};
//				CARET[4][2] = {0};
//				UNDERSCORE[4][2] = {0};
//				QUOTEDBL[4][2] = {0};
//				BACKQUOTE[4][2] = {0};
//				HASH[4][2] = {0};
//				DOLLAR[4][2] = {0};
//				PERCENT[4][2] = {0};
//				AMPERSAND[4][2] = {0};
//				LPAREN[4][2] = {0};
//				RPAREN[4][2] = {0};
//				ASTERISK[4][2] = {0};
//				PLUS[4][2] = {0};
//				COMMA[4][2] = {0};
//				MINUS[4][2] = {0};
//				PERIOD[4][2] = {0};
//				SLASH[4][2] = {0};
			}
		} font;

		/*
		 * This is a list of colors we can use to set the color
		 * 		of the font but can also be used to set the hue
		 * 		of other items in the game.
		 */
//		struct Color {
//
//	//		struct Journal {
//	//			Vector4f inventory_icon;
//	//
//	//			Journal() {
//	////				inventory_icon[0] = {0.73};
//	////				inventory_icon[1] = {0.65};
//	////				inventory_icon[2] = {0.42};
//	////				inventory_icon[3] = {0.5};
//	//
//	//				inventory_icon[0] = {1.0f};
//	//				inventory_icon[1] = {1.0f};
//	//				inventory_icon[2] = {1.0f};
//	//				inventory_icon[3] = {0.25f};
//	//			}
//	//
//	//		} journal;
//
//			Vector4f white, brown, tan, black, red, green, blue, yellow, orange, grey, transparent, debug;
//			Color() {
//				black[0] = {0};
//				black[1] = {0};
//				black[2] = {0};
//				black[3] = {0};
//
//				tan[0] = {0};
//				tan[1] = {0};
//				tan[2] = {0};
//				tan[3] = {0};
//
//				brown[0] = {0};
//				brown[1] = {0};
//				brown[2] = {0};
//				brown[3] = {0};
//
//				white[0] = {0};
//				white[1] = {0};
//				white[2] = {0};
//				white[3] = {0};
//
//				red[0] = {0};
//				red[1] = {0};
//				red[2] = {0};
//				red[3] = {0};
//
//				green[0] = {0};
//				green[1] = {0};
//				green[2] = {0};
//				green[3] = {0};
//
//				blue[0] = {0};
//				blue[1] = {0};
//				blue[2] = {0};
//				blue[3] = {0};
//
//				yellow[0] = {0};
//				yellow[1] = {0};
//				yellow[2] = {0};
//				yellow[3] = {0};
//
//				orange[0] = {0};
//				orange[1] = {0};
//				orange[2] = {0};
//				orange[3] = {0};
//
//				grey[0] = {0};
//				grey[1] = {0};
//				grey[2] = {0};
//				grey[3] = {0};
//
//				transparent[0] = {0};
//				transparent[1] = {0};
//				transparent[2] = {0};
//				transparent[3] = {0};
//
//				debug[0] = {0};
//				debug[1] = {0};
//				debug[2] = {0};
//				debug[3] = {0};
//			}
//		} color;

		/*
		 * Control/Input
		 * Keeps track of the movement speed, whether we are flying
		 * 		or jumping and the character stance.
		 */
		struct Controls {
			bool fly;			// Currently flying
	//		bool jump;			// Currently jumping
			float moveSpeed;	// Base character speed
	//		float modClimb;		// How fast you can move uphill at the current moment, set in GetHeight(), applied in ProcessInput(), separate from moveMod used to run
	//		float modStance;	// Speed change when in a different stance
			float modSpeed;		// Used for sneaking and running
	//		//float climbMod;	// Controls speed when climbing inclines
	//		//int bStance;
	//		bool bThirdPerson;	// Enable/Disable 3rd person view (battle mode)

			Controls() : fly(false),
	//					 jump(false),
						 moveSpeed(0.5),
	//					 modClimb(0),
	//					 modStance(0),
						 modSpeed(1) {}
	//					 bThirdPerson(false) {}

			struct _KeyBinding {
				uint move_forward,
					 move_back,
					 strafe_left,
					 strafe_right,
					 turn_left,
					 turn_right,
					 //jump,
					 //change_stance,
					 move_up,
					 move_down,
					 run,
					 sneak,
					 activate,
					 //open_journal,
					 //open_menu,
					 //open_intent,
					 mouse_left,
					 mouse_right,
					 mouse_up,
					 mouse_down;

				_KeyBinding():	move_forward(SDLK_w),
								move_back(SDLK_s),
								strafe_left(SDLK_a),
								strafe_right(SDLK_d),
								turn_left(0),
								turn_right(0),
								//jump(0),
								//change_stance(0),
								move_up(0),
								move_down(0),
								run(0),
								sneak(0),
								activate(0),
								//open_journal(0),
								//open_menu(0),
								//open_intent(0),
								mouse_left(0),
								mouse_right(0),
								mouse_up(0),
								mouse_down(0) {}
			} key;

//			struct _Mouse {
//				bool bEnable;
//				int x, y;
//				float sensX, sensY;
//				int deadX, deadY;
//				float relX, relY;
//				bool lock;
//				bool hide;
//				//Vector3f rayCast;
//
//				_Mouse() : bEnable(false),
//						   x(0),
//						   y(0),
//						   sensX(0),
//						   sensY(0),
//						   deadX(0),
//						   deadY(0),
//						   relX(0),
//						   relY(0),
//						   lock(false),
//						   hide(false) {
//					//rayCast[0] = 0;
//					//rayCast[1] = 0;
//					//rayCast[2] = 0;
//				}
//
//				struct _Button {
//					bool check[10];
//					bool pressed[10];
//					bool repeat[10];
//
//					_Button() {
//						for (int i=0; i<10; i++) {
//							check[i] = false;
//							pressed[i] = false;
//							repeat[i] = false;
//						}
//					}
//
//				} button;
//			} mouse;

	//		struct Keyboard {
	//			//bool key[323];  //For storing keypress events
	//			//bool repeat[323]; //Keep track of whether key is repeating
	//			//bool bWorld[323]; //What keys are defaulted to repeat and stroke
	//			//bool bConsole[323]; //What keys are defaulted to repeat and stroke
	//			//bool bDungeon[323]; //Dungeon and world should be identical
	//			//Uint8 * event;
	//
	//			Keyboard() {
	//				//for (int i=0; i<323; i++) {
	//					//key[i] = false;
	//					//repeat[i] = false;
	//					//bWorld[i] = false;
	//					//bConsole[i] = false;
	//				//}
	//				//event = new Uint8;
	//			}
	//
	//		} keyboard;
		} controls;

		/*
		 * WE NEED TO MOVE IMPRTANT WORLD VARIABLES INTO
		 * THIS STRUCT SO WE CAN ACCESS THEM FROM OTHER PLACES
		 */
	//	struct _World {
	//		struct _Water {
	//			int iHeight;	//Sea Level
	//		} water;
	//	} world;

	//	struct _Menu {
	//		bool	bOperations,
	//				bStatus,
	//				bIntent,
	//				bActionIcon;		//Which systems to draw, set externally
	//
	//		_Menu() :	bOperations(false),
	//					bStatus(false),
	//					bIntent(false),
	//					bActionIcon(true) {}
	//	} menu;

		 /*
		  * OLD STRUCT
		  * Used to keep track of the shadow
		  */
	//	struct ShadowVar {
	//		bool enable;   // Enable shadows
	//		bool realtime;   // Enable realtime claculation
	//		int res;    // Shadow Resolution
	//		Matrix44f mvLight;   // Model View Matrix of light source for shader
	//		Matrix44f projLight; // Projection Matrix of light source for shader
	//		Matrix44f sbMatrix;  // Scale/Tranlate Matrix for shader
	//
	//		ShadowVar() : enable(false),
	//					  realtime(false),
	//					  res(0) {
	//			for (int i=0;i<16;i++) {
	//					mvLight[i] = 0;
	//					projLight[i] = 0;
	//					sbMatrix[i] = 0;
	//			}
	//		}
	//
	//	} shadow;

		 // Struct for data about the sun
	//	struct Sky {
	//		int num;
	//		float sunDir; //Direction of the sun (controls direction of shadows)
	//
	//		Sky() : num(0),
	//				sunDir(0) {}
	//
	//	} sky;

		/*
		 * Location information for the character including position,
		 * 		height, physical reach for 2D events, eye height, etc.
		 */
		// TODO: This should all be i nthe character sheet
	//	struct Transform {
	//		//Vector3f worldPos;     //X-Y-Z for world
	//		//Vector2f worldRot;     // U/D-L/R rotation for world
	//		Vector3f dunPos;
	//		Vector2f dunRot;
	//		Vector3f cityPos;
	//		Vector2f cityRot;
	//
	//		//float yRotBB;      	// Billboard rotation
	//		//float eyeHeight;		// Character height
	//		float fCrouchDiff;		//Speed Percentage of eyeHeight when in Crouch
	//		float fProneDiff;		//Speed Percentage of eyeHeight when in Prone
	//		//float currentHeight;	// Current Characters Height (sets stance position in battle)
	//		//float stereoX, stereoY, stereoZ; // For storing stereo settings
	//		//int startX, startZ;    // The starting map position
	//		//Vector2ui vfBase;     // The normalized starting map position (if 100x100 is the starting position and iGridSize is 5, then this will be 98x98 [startX-((iGridsize-1)/2)])
	//		//float fReach;      // The players physical 'reach' in the world. How far away events can be for interaction for example.
	//		//int iLoadLimit;
	//
	//		//float groundHeight;
	//		float maxIncline;		//Maximum slope change that can occur
	//
	//		// Jumping values
	//		float jumpHeight;
	//		float jumpPosition;
	//		float jumpVelocity;
	//		float jumpMaxVelocity;
	//
	//		Transform() : fCrouchDiff(0),
	//									fProneDiff(0),
	//									//iLoadLimit(0),
	//									maxIncline(0),
	//									jumpHeight(0),
	//									jumpPosition(0),
	//									jumpVelocity(0),
	//									jumpMaxVelocity(0) {
	//			dunPos[0]	= 0;	dunPos[1]	= 0;	dunPos[2]	= 0;
	//			dunRot[0]	= 0;	dunRot[1]	= 0;
	//			cityPos[0]	= 0;	cityPos[1]	= 0;	cityPos[2]	= 0;
	//			cityRot[0]	= 0;	cityRot[1]	= 0;
	//		}
	//
	//		/*
	//		 * NOT CURRENTLY USED
	//		 */
	//		struct Water {
	//			float x, z;      // Holds current values for water animations
	//			float h;      // Modifier for wave height
	//
	//			Water() : x(0),
	//					  z(0),
	//					  h(0) {}
	//
	//		} water;
	//	} transform;

	//	struct Battle {
	//		bool newBattle;
	//		Battle() : newBattle(false) {}
	//	} battle;

		/*
		 * Armor data structure
		 */
	//	struct Armor {
	//		//Vector5i res[35];
	//
	//		//Armor() {
	//			//for (int i=0;i<16;i++) {
	//			//	res[i][0] = 0;
	//			//	res[i][1] = 0;
	//			//	res[i][2] = 0;
	//			//	res[i][3] = 0;
	//			//	res[i][4] = 0;
	//			//}
	//		//}
	//
	//		//struct Type {
	//			std::string name;
	//			int blade, blunt, axe, spear, arrow, jaw, claw, hand;
	//			int iDurability;
	//			int iFlags[16];
	//			float glance;
	//			int bBonus;				// Bit flags for Bonus when under another armor
	//			//int bFull;			// Bit flags for Half(0) or Full(1) bonus  [00000000]
	//			int bFull[8];			// Bonus levels for each weapon
	//			int iType;				// Armor classification (Maille, Plate, Cloth, etc.)
	//
	//			Armor() : name(""),
	//					 blade(0),
	//					 blunt(0),
	//					 axe(0),
	//					 spear(0),
	//					 arrow(0),
	//					 jaw(0),
	//					 claw(0),
	//					 hand(0),
	//					 glance(0),
	//					 iDurability(0),
	//					 bBonus(0),
	//					 iType(0) {
	//				bFull[0] = 0;
	//				bFull[1] = 0;
	//				bFull[2] = 0;
	//				bFull[3] = 0;
	//				bFull[4] = 0;
	//				bFull[5] = 0;
	//				bFull[6] = 0;
	//				bFull[7] = 0;
	//			};
	//
	//		//} type[48];					//ENUM
	//	} armor[48];

		/*
		 * This apparently isn't used
		 */
	//	struct Names {
	//		std::string battle_damage_status[32];
	//
	//		Names() {
	//			for (int i=0;i<32;i++) {
	//				battle_damage_status[i] = "";
	//			}
	//		}
	//
	//	} names;

		/*
		 * Weapon data structure
		 */
	//	struct Weapon {
	//		std::string name;
	//		//string *		sType;							// Damage type text pointer
	//		int   			type,								// Type of damage
	//								die,								// Number of dice used for limb damage bonus
	//								face,								// Number of faces on dice for limb damage bonus
	//								hand,								// How many hands needed to use
	//								toHit;							// TODO: Base weapon difficulty [UNUSED]
	//		int   			iFlags[16];					// TODO: Unknown [UNUSED]
	//		int	  			limb_1,
	//			  	  		limb_2,
	//								limb_3,
	//								limb_4,							// Base limb damages (1-4)
	//								damage,							// General health damage
	//								critical_static;		// Critical health static damage
	//		float 	  	critical_percent;		// Critical health percentage damage (percent is subtracted from hitpoints, then static)
	//		int   			chop,
	//								swing,
	//								thrust;
	//		int   			range,
	//								speed,
	//								kd;
	//
	//		Weapon() : name(""),
	//				   type(0),
	//				   die(0),
	//				   face(0),
	//				   hand(0),
	//				   limb_1(0),
	//				   limb_2(0),
	//				   limb_3(0),
	//				   limb_4(0),
	//				   damage(0),
	//				   critical_static(0),
	//				   critical_percent(0),
	//				   chop(0),
	//				   swing(0),
	//				   thrust(0),
	//				   range(0),
	//				   speed(0),
	//				   toHit(0),
	//				   kd(0) {
	//		}
	//
	//		//struct Status_Effect {
	//		//	int effect;		//ENUM
	//		//	Status_Effect() : effect(0) {}
	//		//} status_effect[6];
	//	} weapon[256];					//ENUM

		/*
		 * Weapon data structure
		 */
	//	struct Shield {
	//		std::string name;
	//		int   			iFlags[16];					// TODO: Unknown [UNUSED]
	//		float				block,
	//								deflect,
	//								glance;
	//
	//		Shield() :	name(""),
	//								block(0.0f),
	//								deflect(0.0f),
	//								glance(0.0f) {
	//		}
	//	} shield[128];					//ENUM

		/*
		 * Spell database
		 *
		 */
	//	struct Spell {
	//		std::string name;		// Spell name
	//		std::string iTex;		// Texture file
	//		std::string sDes;		// Spell description
	//		int   id;				// Unique spell id number
	//		int   iIcon;			// Icon number from image file
	//		int   base[2];			// Similar to School of magic
	//		int   type;				// Cast type
	//		int   alignment;		// ???
	//		int   source;			// Power source, where you draw your power from to maintain spells
	//		int   restriction[4];	// Restrictions required to cast spell
	//		int   active_rounds;	// Rounds to repeat including the current round, 0 for infinite
	//		int   charging_rounds;	// Rounds before actual cast, 0 for instant cast
	//		int   cost;				// Cost to charge spell per round
	//		int   cast;				// Cost to cast spell (instant cast or finished charging)
	//		int   upkeep;			// Cost for active spells per round
	//		float radius;			// Radius for area effect spells
	//		bool  bStack;			// Is stacking allowed for this spell
	//		int   iPreCast;			// Precast requirement, this spell(id) must preceed this one
	//		int   iItemReq;			// Equipped item(id) requirement, from intention bar
	//		bool  bVoid[19];		// Restricted void, spell cannot be used here
	//		int   iFlags[32];		// Specialty flags, such as Ethereal damage
	//		int   iChance;			// Chance of overall spell success
	//		Weapon weapon;			// Summoned Weapon (Creates in inventory and equips, deletes after spell end)
	//		Armor armor;			// Summoned Armor
	//		//Item pItem;			// Summoned Item
	//		int status_effect[6];
	//
	//		Spell() :	name(""),
	//					id(0),
	//					type(0),
	//					alignment(0),
	//					source(0),
	//					charging_rounds(0),
	//					active_rounds(0),
	//					cost(0),
	//					cast(0),
	//					upkeep(0),
	//					radius(0),
	//					bStack(0),
	//					iPreCast(0),
	//					iItemReq(0),
	//					iChance(0),
	//					iIcon(0) {
	//			base[0] = 0;
	//			base[1] = 0;
	//			restriction[0] = 0;
	//			restriction[1] = 0;
	//			restriction[2] = 0;
	//			restriction[3] = 0;
	//		}
	//	} spell[256];

		/*
		 * Status Effect database
		 * Each array entry corresponds to a status effect id number, the contents includes
		 * 		a static modifier[0] and a percentage modifier[1].
		 */
	//	struct _Status_Effect {
	//		std::string title;
	//		int id;					//Unique id
	//		int iRestriction[4];	//Race restrictions, etc
	//		int iFlags[16];			//Ailments
	//
	//		bool bTarget;			//True if applies to target, false if applies to caster
	//
	//		struct _Weight {
	//			int light[2],
	//				medium[2],
	//				heavy[2];
	//		} weight;
	//
	//		struct _Move {
	//			int raise[2],
	//				lift[2],
	//				push[2];
	//		};
	//
	//		struct _Stats {
	//			int aura[2],
	//				speed[2],
	//				endurance[2],
	//				mind[2];
	//		} stats;
	//
	//		struct _Attributes {
	//			int str[2],
	//				fin[2],
	//				mob[2],
	//				fat[2],
	//				vic[2];
	//		} attributes;
	//
	//		struct _Derived {
	//			int reflex[2],
	//				willpower[2],
	//				fortitude[2],
	//				initiative[2],
	//				intelligence[2],
	//				constitution[2],
	//				charisma[2],
	//				wisdom[2],
	//				weight[2],
	//				max_load[2],
	//				mana[2],
	//				stamina[2],
	//				leadership[2],
	//				dynamism[2],
	//				comprehension[2],
	//				execution[2],
	//				intensity[2];
	//		} derived;
	//
	//		struct Transform {
	//			Vector3f pos;
	//			Vector3f rot;
	//		} transform;
	//
	//		struct Damage {
	//			int hit_points[2];
	//
	//			struct Limb {
	//				int left_arm[2][2];
	//				int right_arm[2][2];
	//				int left_leg[2][2];
	//				int right_leg[2][2];
	//				int torso[2];
	//				int head[2];
	//			} limb;
	//
	//			struct Weapon {
	//				struct Hand {
	//					int left[2];
	//					int right[2];
	//				} hand;
	//			} weapon;
	//
	//			struct Armor {
	//				int left_arm[2][2];
	//				int right_arm[2][2];
	//				int left_leg[2][2];
	//				int right_leg[2][2];
	//				int torso[2];
	//				int head[2];
	//			} armor;
	//
	//		} damage;
	//
	//		struct _ITEM {
	//			struct _ARMOR {
	//					int blade,
	//						blunt,
	//						axe,
	//						spear,
	//						arrow,
	//						jaw,
	//						claw,
	//						hand;
	//					float glance;
	//					int iDurability[2];		//We want to check which part has been hit and lower the durability on that part. 0=static, 1=percent
	//			} armor;
	//
	//			struct _WEAPON {
	//				int type,		// Type of damage
	//					die,		// Number of dice used for limb damage bonus
	//					face,		// Number of faces on dice for limb damage bonus
	//					hand,		// How many hands needed to use
	//					toHit;		// Base weapon difficulty
	//
	//				int iFlags[16];
	//
	//				int	limb_1,
	//					limb_2,
	//					limb_3,
	//					limb_4,	//Base limb damages (1-4)
	//					damage,								//General health damage
	//					critical_static;					//Critical health static damage
	//
	//				float critical_percent;					//Critical health percentage damage (percent is subtracted from hitpoints, then static)
	//
	//				struct _CHOP {
	//					int iBase,		//Maximum critical
	//						iCrit1,		//Bonus to critical one chance
	//						iCrit2,		//Bonus to critical one chance
	//						iCrit3,		//Bonus to critical one chance
	//						iCrit4;		//Bonus to critical one chance
	//				} chop;
	//
	//				struct _SWING {
	//					int iBase,		//Maximum critical
	//						iCrit1,		//Bonus to critical one chance
	//						iCrit2,		//Bonus to critical one chance
	//						iCrit3,		//Bonus to critical one chance
	//						iCrit4;		//Bonus to critical one chance
	//				} swing;
	//
	//				struct _THRUST {
	//					int iBase,		//Maximum critical
	//						iCrit1,		//Bonus to critical one chance
	//						iCrit2,		//Bonus to critical one chance
	//						iCrit3,		//Bonus to critical one chance
	//						iCrit4;		//Bonus to critical one chance
	//				} thrust;
	//
	//				int cost,
	//					weight,
	//					range,
	//					speed,
	//					kd;
	//			} weapon;
	//		} item;
	//
	//		/*
	//		 * DoT should go here
	//		 *
	//		 * We can probably just use some sort of value that
	//		 * 		is applied every round here along with a value
	//		 * 		that determines range and chance of damage per
	//		 * 		round.
	//		 */
	//	} status_effect[256];

		// TODO: Need to update for new system
	//	struct Items {
	//		std::string  name;							// Spell name
	//		std::string  sTex;							// Texture file
	//		std::string  sDes;							// Item description
	//		int          id;								// Unique item id number
	//		int          iIcon;							// Icon number from image file
	//		//int   iType;									// Cast type
	//		int          iWeight;						// Weight of the item
	//		int          iCost;							// Cost of item to purchase/sell
	//		int	         iMaterial;					// Material of item if applicable
	//		int          restriction[4];		// Restrictions required to cast spell
	//		int          active_rounds;			// Rounds to repeat including the current round, 0 for infinite
	//		float        fRadius;						// Radius for area effect spells
	//		int          iPreCast;					// Precast requirement, this spell(id) must preceed this one
	//		bool         bStack;						// Can this item be stacked in inventory? Character sheet tracks number of items
	//		int          iSpellId;					// Spell/Book(id) attached to this item (instant cast for spells)
	//		int          iTypeFlag;					// General Item, Weapon, Armor, bit flag.
	//		int	         iTypeId;						// ID number for weapon or armor type.
	//		unsigned int iBodyPart;					// Allowed location to equip (bit flags)
	//		short int    numUpgrades;				// Available upgrade slots
	//		int          iUpgrade[4];				// Applied upgrade id from available upgrades (25)
	//		int          iFlags[32];				// Specialty flags, such as Ethereal damage [BOOK, SPECIAL, etc]
	//		bool         bVoid[19];					// Restricted void, spell cannot be used here
	//		int	       	 status_effect[6];	//
	//		Weapon *	 	 weapon;
	//		Armor  *	 	 armor;
	//		Shield *	 	 shield;
	//
	//		Items() :	name(""),
	//							id(0),
	//							active_rounds(0),
	//							fRadius(0.0f),
	//							iPreCast(0),
	//							iIcon(0),
	//							iWeight(0),
	//							iCost(0),
	//							iMaterial(0),
	//							iSpellId(0),
	//							bStack(0),
	//							iTypeFlag(0),
	//							iTypeId(0),
	//							numUpgrades(0),
	//							iBodyPart(0),
	//							weapon(nullptr),
	//							armor(nullptr),
	//							shield(nullptr) {
	//			restriction[0] = 0;
	//			restriction[1] = 0;
	//			restriction[2] = 0;
	//			restriction[3] = 0;
	//			iUpgrade[0] = 0;
	//			iUpgrade[1] = 0;
	//			iUpgrade[2] = 0;
	//			iUpgrade[3] = 0;
	//		}
	//	} items[512];

		// TODO: Allow fleets??
		struct Player {
			Core::GameSys::CharSheet sheet;					// Main players character sheet
			Core::GameSys::CharSheet * active;				// Active players pointer to character sheet
			//CharSheet * target;

			Player() {
				active = &sheet;
			}
		} player;
	};

}
#endif /* GAMEVARS_HPP_ */
