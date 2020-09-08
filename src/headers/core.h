/*
 * core.h
 *
 *  Created on: Feb 21, 2011
 *      Author: bcthund
 */

#ifndef CORE_H_
#define CORE_H_


// Unorganized Priority Ideas
/*
 *
 *  - Menu Controls/Graphics
 *  	- Value Slider
 *  	- Numeric Input box
 *  	- Knob
 *
 *  - Perlin noise
 *  	- Maps (elevation, biomes, flora, trees, climate)
 *  	- Make Spherical for planets
 *  	- Draw to set draw distance when on ground
 *  	- When flying, dynamically increase draw distance and lower quality to allow entire planet to show
 *  	- Resources
 *  	- Clouds? (Multiple layers, moving at different speeds)
 *
 *  - World Sphere Handling
 *  	- Stacked sphere used for world
 *  	- World sphere is actually static, never rotates or moves
 *  	- Noise map rotates and moves to simulate planetary movement from player movement
 *  	- When on ground only a certain range of quad sectors are drawn, then transformed to spherical height
 *  	- When above a certain threshhold, quad sectors replaced with entire spherical map
 *  	- Sphereical map grid resolution should match quad grid resolution. Minimum quad resolution same as minimum sphereical quad resolution. (There will be some distortion due to spherical nature)
 *  	- Ground level quads can have varying resolution with distance which should be fairly easy to handle
 *  	- Planetary sphere mya not be easy to have varying resolution with distance without it being global across entire planet
 *
 *  - TEFs (Temporary Enemy Flags)
 *  	- Interacting with opposing factions will flag you against them
 *  	- This flag is only visible to those who saw the act that caused it
 *  	- The flag can become visible to others if someone reacts to your status (attacks you in front of other players)
 *  	- The flag goes away after a cooldown period, secluded from all who know about your status (hotel room? as long as the keeper isn't aware of your status, otherwise you can get ambushed)
 *
 *  - Faction standing (aka reputation)
 *  	- individual races/groups/etc have standing effected by your actions
 *  	- zones have standing as well, such as a city.
 *  		- Murder a bunch of citizens then you lose city faction to the point that the guards will arrest you and call reinforcements.
 *  		- Think of a cross between Elder Scroll guards and Grand Theft Auto escalation.
 *  		- If caught you can pay a HEFTY fine or go to jail for a real amount of time, losing some skills in the process
 *  		- Primary faction battles (think Rebel vs Imperial) do not effect zone standing
 *
 *	- 3D "Flight" navigation
 *		- Quaternions?
 *		- Twitch vs Queue based?
 *
 *	- 3D Characters
 *		- Skeleton
 *		- Joints
 *		- Movement/Animation
 *
 *	- Experience
 *		- Use quest/task based learning (school/college)
 *		- Must pay for your education
 *		- Buy books and study them (like in EVE online)
 *
 *	- Datapad
 *		- Use modern technology ideas where the datapad is not much unlike phones
 *		- Instant messages
 *		- Email (allows attachments)
 *		- Banking (wire transfer)
 *		- Investing
 *			- Allow market investments to allow company stock funding
 *			- IPO
 *			- Stock splits and reverse splits
 *			- Dividends
 *		- Waypoints
 *		- Schematics
 *		- Assets (Vehicles, Houses, Factories, etc)
 *		- Inventory
 *		- Skills
 *
 *	- Trees
 *		- Use 3D trees according to biomes
 *		- Fade into 2D versions at far away up to set draw distance
 *
 *  - A Jedi Saga
 *  	- Create a "Jedi" class that is like the end-game class
 *  	- Use system as described by Raph Koster where increasingly more difficult "bounty hunters" attack you if you are noticed until "Vader" arrives who WILL kill you.
 *  	- Allow a VERY LONG cooldown so as to try and fend off the "Vader" attack
 *  	- "Bounty Hunters" can only appear if you have been seen recently, they will appear physically and search for you
 *  	- Allow player bounty hunters to participate, same visibility rules apply.
 *  	- SWG had the "blue glowie" reward, would need something similar?
 *
 *  - Professions
 *  	- Classless like SWG
 *  	- Different classes have different structures
 *  	- Incorporate SWG based professions (no other game compares!) (*=new professions)
 *  		- Original SWG professions for reference
 *  			- Artisan
 *  				- Architect
 *  				- Armorsmith
 *  				- Droid Engineer
 *  				- Shipwright
 *  				- Weaponsmith
 *  				- Chef
 *  				- Tailor
 *  				- Merchant
 *  			- Brawler
 *  				- (Commando)
 *  				- Teras Kasi Artis
 *  				- (Smuggler)
 *  				- Fencer
 *  				- Swordsman
 *  				- Pikeman
 *  			- Entertainer
 *  				- Image Designer
 *  				- Musician
 *  				- Dancer
 *  			- Marksman
 *  				- (Commando)
 *  				- (Bounty Hunter)
 *  				- (Smuggler)
 *  				- Rifleman
 *  				- Pistoleer
 *  				- Carbineer
 *  				- (Squad Leader)
 *  				- (Combat Medic)
 *  			- Medic
 *  				- Doctor
 *  				- (Combat Medic)
 *  				- (Bio-Engineer)
 *  			- Scout
 *  				- (Bounty Hunter)
 *  				- Creature Handler
 *  				- (Squad Leader)
 *  				- (Bio-Engineer)
 *  				- Ranger
 *  			- Politician (I don't like this one)
 *  			- Pilot
 *  			- Force Sensitive
 *  			- Force Discipline
 *  		- Changes to professions and new professions
 *  			- Artisan (Crafting is the most important part, near everything worth while should be player built like in SWG with few exceptions)
 *  				- Electrical Engineer (electronics components, robots(droids), power distribution)
 *  				- Mechanical Engineer (mechanical components)
 *  					- Automotive
 *  					- Weapons
 *  				- Chemical Engineer (chemical components, similar to materials science and can make specialty materials from natural elements)
 *  				- Aerospace Engineer (like a shipwright)
 *  					- General Technologies (These sub disciplines require parts from general engineers, these components are needed for all other aerospace construction)
 *  						- Life Support
 *  						- Propulsion (Engines, boosters)
 *  						- Hyperdrives
 *  						- Energy Systems (capacitors, batteries, )
 *  						- Flight Computers (Tracking, max targets, signature, scan resolution, targeting range, etc from EVE examples)
 *  						- Weapon Systems
 *  						- Shield Technology
 *  						- Armor Technology
 *  					- Surface/Space disciplines
 *							- Shuttles
 *  						- Frigates
 *  						- Fighters (similar to frigates but better armor/weapons/maneuverability)
 *  					- Space only disciplines (EVE online style classifications)
 *  						- Miners
 *  						- Freighters
 *  						- Destroyers
 *  						- Cruisers
 *  						- Battlecruisers
 *  						- Battleships
 *  						- Carriers
 *  						- Dreadnoughts
 *  						- Supercarriers
 *  						- Titans
 *  					- Space Station (specialty discipline with multiple categories required to assemble a full station)
 *  				- Cival Engineer
 *  					- Roads (Provides faster travel speeds)
 *  					- Municipal buildings (cantina, medical facility, bar, etc)
 *  					- Bridges
 *  					- Ammenities (hotel, outdoor lighting, parks, fountains)
 *  				- Biomedical Engineer (makes components necessary for medicine, creates implants with help of other professions)
 *  				- Materials Science Engineer (ex:steelmaking, can take natural minerals and create advanced materials, but not chemicals/oils)
 *  				- Manufacturing Engineer (With the help of most other professions, can create the facilities necessary for mass production; has sub-dsciplines for other professions otherwise overpowered)
 *  				- Mining Engineer (mining of natural minerals/chemicals/etc, but not oil.)
 *  				- Nuclear Engineer (nuclear power)
 *  				- Petroleum Engineering (oil)
 *  				- Tailor
 *  					- Armorsmith (Better be a good tailor if your making armor)
 *  				- Chef (this doesn't really need to change)
 *  				- Merchant (this doesn't really need to change)
 *  				- *Writer
 *  					- A writer alone can just write books and release them for purchase.
 *  					- A writer with a Master in another profession can write skill books used to train other players
 *  			- Other professions are more or less OK at the moment
 *
 */


// Systems to create/update:
/*	[ ] Unclassified =================================================================================
 *		[ ] Rendering Pipeline -----------------------------------------------------------------------
 *			[ ] Frustrum Culling
 */

//	[ ] Core =========================================================================================
/*		[ ] AudioSys --------------------------------------------------------------------------------- STARTED
 *			[ ] Started, fine tune and finish
 *			[ ] ???
 */
/*		[ ] Bounding Volume -------------------------------------------------------------------------- DONE
 *			[?] No Known Issues
 */
/*	   ![ ] Collision -------------------------------------------------------------------------------- STARTED
 *			[X] System needs to be completely written
 *			[X] Make sure to add handler for O2D
 *			[ ] Add missing collision systems
 *				[ ] Ray Plane
 *				[ ] Ray Quad
 *				[ ] Ray Triangle
 *				[ ] Line Quad
 *				[ ] Line Triangle
 */
/*		[ ] Colors ----------------------------------------------------------------------------------- DONE
 *			[?] No known issues
 */
/*		[ ] Core Functions --------------------------------------------------------------------------- DONE
 *			[?] No known issues
 */
/*		[ ] Extern ----------------------------------------------------------------------------------- ONGOING
 *			[?] No known issues
 */
/*		[X] FBO -------------------------------------------------------------------------------------- DONE
 *			[?] No known issues
 */
/*		[X] FrameRate -------------------------------------------------------------------------------- DONE
 *			[X] Rudimentary implemented
 *			[X] Create timed framerate
 *	 	 	 	 - Monitor for 1000 ticks
 *	 	 	 	 - Record Samples (Frames Drawn)
 *		 	 	 - Determine actual framerate
 *		 	 	 - Limit get output to last 1000 ticks report
 */
/*		[ ] Functions -------------------------------------------------------------------------------- ONGOING
 *			[?] No known issues
 */
/*		[X] glinit ----------------------------------------------------------------------------------- DONE
 *			[?] No known issues
 */
/*		[ ] gmath (vector math, rename class?) ------------------------------------------------------- STARTED
 *			[ ] ray plane
 *			[ ] half space
 *			[ ] intersect triangle
 *			[ ] scalar
 *			[ ] dot product
 *			[ ] point in quad
 *			[ ] sameside
 *			[ ] point in triangle
 */
/*		[X] helper ----------------------------------------------------------------------------------- DONE
 *			[?] No known issues
 */
/*		[X] InputSys --------------------------------------------------------------------------------- DONE
 *			[X] General
 *				[X] Movement speed based on time
 *			[X] Keyboard
 *			[X] Mouse
 *				[X] Mouse raycasting
 *				[X] Mouse picking (detect bounding volume)
 */
/*		[ ] joint ------------------------------------------------------------------------------------ HALTED
 */
/*		[ ] Lights ----------------------------------------------------------------------------------- STARTED
 *			[X] 32 allowed simultaneous lights active
 *			[X] Omni
 *	 		[X] Spot
 *	 		[X] Directional (Sun)
 *	 		[ ] Where are lights loaded from?
 *	 			- World data file? (most likely)
 *	 			- Lighting file?
 */
/*		[X] Matrix ----------------------------------------------------------------------------------- DONE
 */
/*		[ ] Occlusion -------------------------------------------------------------------------------- STARTED
 *			[!] Add to O3D					(Only one occlusion instance can exist)
 *			[!] Tie to bounding volumes		(Only one occlusion instance can exist)
 *			[ ] Implement multisampling
 */
/*		[ ] Physics ---------------------------------------------------------------------------------- NOT STARTED
 *			[ ] Create (probably just basics for use in particles, like gravity)
 */
/*		[ ] Particles -------------------------------------------------------------------------------- STARTED
 *			[X] Doesn't exist, create
 *			[ ] Might need some basic physics component, possibly as separate system
 *			[ ] Data
 *				[ ] Data3f * vVerts
 *				[ ] Number of particles
 *				[ ] Spawn range from emitter (min/max)
 *				[ ] Despawn, two options
 *					[ ] Max range (range for despawn)
 *					[ ] Time for despawn
 *				[ ] Fade out start time
 *				[ ] Initial color
 *				[ ] Final color (Color at fade out)
 *				[ ] Update rate
 *				[ ] Gravity (direction and force in Vector form, pointer so that global gravity can be used or new pointer vector created)
 *				[ ] last update time
 *				[ ] type
 *					[X] Quad
 *					[ ] 2D Line
 *					[ ] 3D Line
 *					[ ] 2D Point
 *					[ ] 3D Point
 *					[ ] 2D Point Sprite
 *					[ ] 3D Point Sprite
 *				[ ] Emitter
 *					[ ] Static (stationary around target)
 *					[ ] Falling (spawns at height)
 *					[ ] Target (direction and velocity)
 *				[ ] Force
 *					[ ] None (spawns and remains in place)
 *					[ ] Target (ex, gravity vector: particles will fall until floor or ceiling reached)
 */
/*		[ ] Path ------------------------------------------------------------------------------------- NOT STARTED
 */
/*		[X] Ply Loader ------------------------------------------------------------------------------- DONE
 */
/*		[ ] Post Process ----------------------------------------------------------------------------- STARTED
 *			[ ] Add useful effects/tune existing
 *				[ ] Depth of field (Requires depth buffer)
 *				[ ] Chromatic Aberration
 *				[ ] Motion Blur
 *				[ ] Deferred Fog (Requires depth buffer)
 *				[ ] Additive Brightness
 *				[ ] Complex Combine
 *					[ ] Screen
 *					[ ] Dodge
 *					[ ] Addition
 *					[ ] Multiply
 *					[ ] Burn
 *					[ ] Overlay
 *					[ ] Difference
 *					[ ] Subtract
 *					[ ] Divide
 */
/*		[ ] Profile ---------------------------------------------------------------------------------- STARTED
 *			[X] Class Based
 *			[X] Timing system
 *				[X] Time
 *				[X] Average
 *				[X] Max
 *				[X] Min
 *				[X] Samples
 *				[X] Standard Deviation
 *				[X] Variance
 *			[ ] Graphs
 *				[ ] Value History
 *				[ ] Bar Average
 *				[ ] Line/Point vs Time
 */
/*		[X] ptimer ----------------------------------------------------------------------------------- DONE
 */
/*		[X] RunningStat ------------------------------------------------------------------------------ DONE
 */
/*		[ ] Shader ----------------------------------------------------------------------------------- ONGOING
 */
/*		[ ] Shadow ----------------------------------------------------------------------------------- NOT STARTED
 *			[ ] Needs to be (re)created
 *			[ ] FBO for depth texture (use new FBO class)
 */
/*		[ ] Skeleton --------------------------------------------------------------------------------- HALTED
 */
/*		[ ] State ------------------------------------------------------------------------------------ ABANDONED
 *			- System meant to have global settings such as font colors, likely to be abandoned
 */
/*		[X] SystemTextures --------------------------------------------------------------------------- DONE
 */
/*		[X] Texture ---------------------------------------------------------------------------------- DONE
 */
/*	   ![ ] Texture Atlas (Inherits Texture class)
 *			[ ] Rows
 *			[ ] Columns
 *			[ ] ConvertIndexToOffset() function
 */
/*		[X] Timer ------------------------------------------------------------------------------------ DONE
 */
/*		[X] TimeSys ---------------------------------------------------------------------------------- DONE
 */
/*		[X] Types ------------------------------------------------------------------------------------ DONE
 */
/*		[ ] VAO -------------------------------------------------------------------------------------- STARTED
 *			[ ] Instanced Rendering
 *				[ ] Add Instanced Attribute
 *				[ ] stride and offset VBO
 */
/*		[ ] VBO -------------------------------------------------------------------------------------- NOT STARTED
 *			[ ] Create class
 *			[ ] Integrate with VAO
 *			[ ] Integrate with Shader
 *				[ ]
 */

//	[ ] Systems ======================================================================================
/*		[ ] Animations -------------------------------------------------------------------------------
 *			[X] Reimplement standard world animations
 *			[ ] Implement billboarding for world animations
 *				- Should be able to use O2D billboarding shader
 *			[ ] Add Orthographic animations
 *				- Can probably just use sprite drawing system
 *			[ ] Implement A2D, and A3D objects as children
 *
 *		DETAILS: General animation tracking system that updates frames according
 *				 to time base. Individual animations are defined in A2D and A3D
 *				 files.
 */
/*		[ ] Atmosphere -------------------------------------------------------------------------------
 *	 		[ ] Reimplement existing, clean up
 *				[ ] Rain/Snow/Hail (Falling particles)
 *				[ ] ???
 *			[ ] Allow adding of particle systems (requires particle system above)
 *			[ ] Add fog
 *			[ ] Update load from bin
 *			[ ] Use a single fScale value
 *	 		[ ] Gametime (needed in atmosphere because it's likely to be used for things such as sun location)
 */
/*		[ ] Charsheet --------------------------------------------------------------------------------
 */
/*		[ ] gameVars ---------------------------------------------------------------------------------
 */
/*		[ ] IconSys ----------------------------------------------------------------------------------
 */
/*		[ ] MenuSys ----------------------------------------------------------------------------------
 */
/*	   ![ ] O2D --------------------------------------------------------------------------------------
 *			[ ] Material properties
 *				[ ] Shinyness
 *				[ ] Reflectivity
 *					[ ] Self Lighting?
 *			[ ] Billboard normal for lighting
 *			[X] Position to light source update
 */
/*	   ![ ] O3D --------------------------------------------------------------------------------------
 *			[ ] Material properties
 *				[ ] Shinyness
 *				[ ] Reflectivity
 *				[ ] Self Lighting?
 *			[X] O3D lighting always acts like O3D is at 0,0,0
 *			[ ] Collision detection
 */
/*	   ![ ] E2D --------------------------------------------------------------------------------------
 *			[ ] Partially started, probably needs to be remade
 *
 *		DETAILS: This is a class that inherits an O2D but contains additional information
 *				 to allow an event script to be called either with direct or proximity
 *				 activation. This can include things such as traps or doors.
 */
/*	   ![ ] E3D --------------------------------------------------------------------------------------
 *			[ ] Doesn't exist, create
 *
 *		DETAILS: This is a class that inherits an O2D but contains additional information
 *				 to allow an event script to be called either with direct or proximity
 *				 activation. This can include things such as traps or doors.
 */
/*	   ![ ] A2D --------------------------------------------------------------------------------------
 *			[ ] Doesn't exist, create
 *
 *		DETAILS: This is a class that inherits multiple O2D objects. It contains additional
 *				 information per O2D to perform animations.
 */
/*	   ![ ] A3D --------------------------------------------------------------------------------------
 *			[ ] Doesn't exist, create
 *
 *		DETAILS: This is a class that inherits multiple O3D objects. It contains additional
 *				 information per O3D to perform animations.
 */
/*		[ ] SpriteSys --------------------------------------------------------------------------------
 */
/*		[ ] TextSys ----------------------------------------------------------------------------------
 */
/*		[ ] WinSys -----------------------------------------------------------------------------------
 */
/*	   ![ ] MenuSys -----------------------------------------------------------------------------------
 */
/*	   ![ ] WorldMap ---------------------------------------------------------------------------------
 *			[ ] Load Start Map
 *			[ ] Procedural Terrain
 *				[ ] Noise
 *				[ ] Elevation
 *				[ ] Biomes
 *				[ ] Climate
 *				[ ] Islands
 *				[ ] Ridged
 *				[ ] Terraced
 *				[ ] Forest/Flora
 *			[ ] Draw Map
 *			[ ] Terrain Collision
 *			[ ] Gravity (Should be part of atmosphere)
 *			[ ] Load Transition Map
 *			[ ] Draw Distance: Allow draw distance to be variable, any triangles outside are not drawn
 *			[ ] World Size: Like iTerrainGrid in past, determines maximum map size to be loaded
 *			[ ] Detail Bias: Controls map tesselation distance
 *
 */
/*		[ ] ScriptSys --------------------------------------------------------------------------------
 *			[ ] LUA scripting (put here because it needs access to everything in gamesys)
 */
/*	   ![ ] NPC --------------------------------------------------------------------------------------
 *			[ ] Doesn't exist, create
 */

	/*
	 * Order of includes is important
	 *
	 * CORE components are classes that are needed
	 * to make other functions work. By themselves
	 * they don't do very much but post processing
	 * for example makes use of types, texture,
	 * vao, and fbo and declares instances in its
	 * own class for these items.
	 *
	 * The audio system is included here because
	 * it makes no sense for there to be multiple
	 * audio systems.
	 */

	//#include "./core/core_functions.h"
	#include <iostream>
	#include "global.h"

//	#define GL_GLEXT_PROTOTYPES 1		// Enable core profile
//	//#define GL_POINT_SPRITE 0x8861		// Hack to enable Point Sprites thus enabling gl_PointCoord operation
//	#include "./gl4/glcorearb.h"
	//#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
	//#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
	//#define GL3_PROTOTYPES 1

	#include "./core/types.h"		// Always first
	#include "./core/functions.h"	// Always second
	#include "./core/gmath.h"
	#include "./core/Groups.h"
	#include "./core/Scissor.h"
	#include "./core/timer.h"
	#include "./core/ptimer.h"
	#include "./core/FrameRate.h"
	#include "./core/glinit.h"
	#include "./core/matrix.h"
	#include "./core/texture.h"
	#include "./core/TextureAtlas.h"
	#include "./core/SystemTextures.h"
//	namespace Core {	_SystemTextures		*	sysTex		= new _SystemTextures();	}
	#include "./core/Colors.h"
	#include "./core/lights.h"		// Before shader.h
//	#include "./core/Stipple.h"		// Before shader.h
	#include "./core/shader.h"
	#include "./core/TimeSys.h"
	#include "./core/Particles.h"
	#include "./core/ParticleEmitter.h"
//	#include "./core/Stipple.h"		// Before shader.h

	//namespace Core {
	//	Shader_System *shader = new Shader_System;
	//}

	#include "./core/vao.h"
	#include "./core/fbo.h"
	//#include ./core/"shadow.h"
	#include "./core/occlusion.h"
	#include "./core/post_process.h"

	#include "./core/bounding_volume.h"
	#include "./core/collision.h"
	#include "./core/ply_loader.h"
	#include "./core/audiosys.h"					// Audio system, must be before animations.h
	#include "./core/InputSys.h"					// Keyboard and mouse input

	// TODO: Headers in testing...
	#include "./core/helper.h"
	#include "./core/path.h"
	#include "./core/profile.h"
	#include "./core/joint.h"
	//#include "./core/skeleton.h"

	// State settings
//	#include "./core/state.h"

	#include "./gamesys/CharSheet.h"		// Must be before gameVars->h
	#include "./gamesys/gameVars.h"			// Loaded with gamesys but contained in Core::

//	#include "./core/glinit.h"

//	namespace Core {
//		Shader_System *shader = new Shader_System;
//		PostProcess * postProcess = new PostProcess();
//		Core::GameSys::_Mouse * mouse = new Core::GameSys::_Mouse();
//	}

/*
	 * These components are mostly standalone
	 * classes that are used to make the game
	 * actually produce results. This includes
	 * things such drawing text and graphics to
	 * the screen, drawing the atmosphere, and
	 * animations.
	 *
	 * Some items are used like core components
	 * but need to be here because they need
	 * access to other class types. These
	 * include O2D, O3D, atmosphere, and
	 * animations.
	 */
//	namespace Core {	static Core::GameSys::_GameTime	*	timeSys = new Core::GameSys::_GameTime();	}
	#include "./gamesys/animations.h"
	#include "./gamesys/TextSys.h"			// Prints text to the screen
//	#include "./gamesys/WinSys.h"			// Base for drawing windows to the screen
	#include "./gamesys/SpriteSys.h"		// Draws orthographic sprites to the screen
	#include "./gamesys/IconSys.h"			// Draws orthographic icons to the screen
	#include "./gamesys/O2D.h"				// Draws perspective sprites to the world
	#include "./gamesys/O3D.h"				// Draws perspective 3D objects to the world
	#include "./gamesys/atmosphere.h"
	#include "./gamesys/MenuSys.h"			// Draws interactable text to the screen. Can detect hover and clicks.
	#include "./gamesys/MapSys.h"
	#include "./gamesys/GUI/GUI.h"
	//#include "./MenuSys/MenuClass.h"

	// Final Game Systems
	#include "./gamesys/WorldMap.h"

	#include "./settings.h"


	//#define MY_NAMESPACE Core	// This is just a test of making the namespace dynamic
	//namespace MY_NAMESPACE {
	namespace Core {

		std::string sOffset = "";

		/*
		 * State management
		 *
		 * This uses OpenGL states concept to
		 * setup options and settings. The
		 * settings contained in Core::State
		 * should be used globally.
		 */
//		template <typename T>
//		T set(T a, T b) {
//			return (T)0;
//		}
//
//		bool bEnable(int id) {
//			return false;
//		}
//
//		bool bDisable(int id) {
//			return false;
//		}

		/*
		 * Create global objects and set references
		 *
		 * Lots of classes require access to other classes, most
		 * 	notably the shader class. To allow separation of the
		 * 	files the objects are declared global here and then
		 * 	set as references when the classes that need them
		 * 	are initialized.
		 */

		//Ptr<Matrix_System> matrix(new Matrix_System());
		c_Scissor			scissor			= c_Scissor();
		_Debug				debug			= _Debug();
		_Groups				groups			= _Groups();
		_Mouse				*	mouse		= new _Mouse();
		_State				*	state		= new _State();
		GlInit_System		*	glinit		= new GlInit_System();
		Matrix_System		*	matrix		= new Matrix_System();	// This is the matrix stack class, it is not meant to be used for basic matrix manipulation
		_SystemTextures		*	sysTex		= new _SystemTextures();
		Shader_System		*	shader		= new Shader_System(*matrix);
		PostProcess			*	postProcess	= new PostProcess();
		_Collision			*	collision	= new _Collision();
		_Helper				*	helper		= new _Helper();
		AudioSys			*	audioSys	= new AudioSys();
		_Joint				*	skeleton	= new _Joint();			// TODO: Test instance, remove
		_Profile			*   profiles	= new _Profile();
		_FrameRate			*	framerate	= new _FrameRate();
		_TimeSys			*	timeSys		= new _TimeSys();
		_Occlusion			*	occlusion	= new _Occlusion();
//		_Colors				*	colors		= new _Colors();
		_Colors				colors			= _Colors();
		_ParticleEmitter	*	particles	= new _ParticleEmitter();
//		SimplexNoise		*	snoise		= new SimplexNoise();
//		Stipple				*	stipple		= new Stipple();
		Stipple				stipple			= Stipple();
		_AnimationSys		animation		= _AnimationSys(*audioSys);

		GameVars			*	gameVars	= new GameVars();

		_IconSys			*	iconSys		= new _IconSys();
		_SpriteSys			*	spriteSys	= new _SpriteSys();
		_TextSys			*	textSys		= new _TextSys();
//		GameSys::_WinSys	*	winSys		= new GameSys::_WinSys();
		GameSys::_MenuSys	*	menuSys		= new GameSys::_MenuSys(*textSys);
//		GUI::GUI			*	gui			= new GUI::GUI();
		GUI::GUI			gui;
		SDL_Event			*	sdlEvent	= new SDL_Event();

		//shader->SetMatrixSystem(matrix);
		//Core::_Mouse * mouse = new Core::_Mouse();

		void Setup(int argc, char* argv[]) {
			//shader = new Shader_System;

			Core::Setup_GameVars(argc, argv);

			// TODO: Get this info from settings file
			std::string sCaption = "Project Parsec";
			Core::glinit->init(	sCaption,
								Core::gameVars->screen.res.x,
								Core::gameVars->screen.res.y,
								Core::gameVars->screen.bpp,
								Core::gameVars->screen.MultiSample,
								Core::gameVars->screen.vClearColorBase);

			// Colors
			Core::colors.SetActive(Core::colors.COLOR_FRONT);

			// Init Occlusion Queries
			Core::occlusion->Init();

			// Load global textures
			Core::sysTex->load();

			// Init particles (load textures)
			Core::particles->init();

			//Core::shader = new Core::Shader_System;
//			Core::shader->init(&Core::gameVars->player.active->transform.pos, &Core::gameVars->font.vColor);	// Must be after GlInit.init
			Core::shader->init(&Core::gameVars->screen.res, &Core::gameVars->player.active->transform.pos);	// Must be after GlInit.init

			// Must be after GlInit.init
			Core::shader->load();	// Load ALL defined shaders
//			for (int n=0; n<GLS_LAST; n++) {
//				Core::shader->load(SHADER_PROGRAMS(n));
//			}
//			Core::shader->load(Core::GLS_MOUSERAY);
//			Core::shader->load(Core::GLS_LINES);
//			Core::shader->load(Core::GLS_POINTS);
//			Core::shader->load(Core::GLS_FONT);
//			Core::shader->load(Core::GLS_ICON);
//			Core::shader->load(Core::GLS_FLAT);
//			Core::shader->load(Core::GLS_PHONG);
//			Core::shader->load(Core::GLS_PHONG_O2D);
//			Core::shader->load(Core::GLS_PP_CONTRAST);
//			Core::shader->load(Core::GLS_PP_BRIGHTNESS);
//			Core::shader->load(Core::GLS_PP_HBLUR);
//			Core::shader->load(Core::GLS_PP_VBLUR);
//			Core::shader->load(Core::GLS_PP_COMBINE);
//			Core::shader->load(Core::GLS_BOUNDINGVOLUME_OBB);
//			Core::shader->load(Core::GLS_BOUNDINGVOLUME_AABB);
//			Core::shader->load(Core::GLS_BOUNDINGVOLUME_SPHERE);
//			Core::shader->load(Core::GLS_BOUNDINGVOLUME_CYLINDER);
//			Core::shader->load(Core::GLS_EXOSPHERE);

			// Post Processing
			Core::postProcess->init(Core::gameVars->screen.res.x, Core::gameVars->screen.res.y, Core::gameVars->screen.uiMultiSamples);

			// Helper Objects
			Core::helper->init();

			// Process timers
			Core::gameVars->timer.frameRate.start();

			// TODO: Test Skeleton
			//skeleton->children
			int child = 0;

			//std::cout << "<---------------------------" << skeleton->vConnection[0]->x << ", " << skeleton->vConnection[0]->y << ", " << skeleton->vConnection[0]->z << std::endl;
//			skeleton->SetJoint(Vector3f(0.0f, 0.0f, -50.0f), Vector3f(0.0f, 0.0f, -100.0f));
//			child = skeleton->AddJoint(Vector3f(0.0f, 0.0f, -100.0f), Vector3f(0.0f, 100.0f, -100.0f));
//			skeleton->children[child]->AddJoint(Vector3f(0.0f, 100.0f, -100.0f), Vector3f(50.0f, 50.0f, -200.0f));
//			skeleton->children[child]->AddJoint(Vector3f(0.0f, 100.0f, -100.0f), Vector3f(-50.0f, 50.0f, -200.0f));
//			skeleton->children[child]->AddJoint(Vector3f(0.0f, 100.0f, -100.0f), Vector3f(0.0f, 150.0f, 0.0f));

			/*
			 * SetJoint creates the initial part with an origin and connection point.
			 * AddJoint creates a new part using the connection point of its parent as the origin.
			 */
			skeleton->SetJoint(Vector3f(0.0f, 0.0f, -50.0f), Vector3f(0.0f, 0.0f, -100.0f));
			child = skeleton->AddJoint(Vector3f(0.0f, 100.0f, -100.0f));
			skeleton->children[child].AddJoint(Vector3f(50.0f, 50.0f, -200.0f));
			skeleton->children[child].AddJoint(Vector3f(-50.0f, 50.0f, -200.0f));
			skeleton->children[child].AddJoint(Vector3f(0.0f, 150.0f, 0.0f));

			// Standard Z Depth
//			matrix->SetPerspective(	Core::gameVars->screen.degFov,
//									(float)Core::gameVars->screen.res.x/(float)Core::gameVars->screen.res.y,
//									Core::gameVars->screen.fFar,
//									Core::gameVars->screen.fNear);
			//matrix->SetOrtho(Core::gameVars->screen.halfW, Core::gameVars->screen.halfH, 1.0f, 1000.0f);
//			matrix->SetOrtho(Core::gameVars->screen.fHalfW, Core::gameVars->screen.fHalfH, 1.0f, 1000.0f);

			// Reverse Z Depth
			matrix->SetPerspective(	Core::gameVars->screen.degFov,
									(float)Core::gameVars->screen.res.x/(float)Core::gameVars->screen.res.y,
									Core::gameVars->screen.fNear,
									Core::gameVars->screen.fFar);
			matrix->SetOrtho(Core::gameVars->screen.half.x, Core::gameVars->screen.half.y, 100.0f, 0.0f);

			// Init/Load/Calc Core Systems
			matrix->SetProjection(matrix->MM_PERSPECTIVE);
			//matrix->SetProjection(matrix->MM_ORTHO);

			audioSys->init();
			audioSys->load();

			textSys->init();
			textSys->load();
			//Core::textSys.calc();

			//Core::GameSys::winSys.init();
//			winSys->load();
//			winSys->calc();

			//Core::iconSys.init();
			iconSys->load();
			iconSys->calc();

			//Core::spriteSys.init();
			spriteSys->load();
			spriteSys->calc();

			animation.init();
			animation.load();
			animation.calc();

			glClearColor(	Core::gameVars->screen.vClearColorCurrent[0],
							Core::gameVars->screen.vClearColorCurrent[1],
							Core::gameVars->screen.vClearColorCurrent[2],
							Core::gameVars->screen.vClearColorCurrent[3]	);

			// Debug
			//Core::occlusion.CreateQuery("TestQuery", GL_SAMPLES_PASSED);
			//Core::occlusion.SetSamples("TestQuery", (255)*(255));
		}

		void glReport() {
			std::cout << std::endl;
			std::cout << "#> OPENGL VERSIONS <#" << std::endl;
			std::cout << "GL_VENDOR: \t\t\t" << glGetString(GL_VENDOR) << std::endl;
			std::cout << "GL_RENDERER: \t\t\t"<< glGetString(GL_RENDERER) << std::endl;
			std::cout << "GL_VERSION: \t\t\t"<< glGetString(GL_VERSION) << std::endl;
			std::cout << "GL_SHADING_LANGUAGE_VERSION: \t" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
			std::cout << "Maximum Texture Units: \t\t" << GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS-1 << std::endl << std::endl;
		}

		void Cleanup() {
//			delete gui;//			= new GUI::GUI();
			delete menuSys;//		= new GameSys::_MenuSys(*textSys);
//			delete winSys;//		= new GameSys::_WinSys();
			delete textSys;//		= new _TextSys();
			delete spriteSys;//		= new GameSys::_SpriteSys();
			delete iconSys;//		= new GameSys::_IconSys();
			delete gameVars;//		= new GameVars();
			delete particles;//		= new _ParticleEmitter();
//			delete colors;//		= new _Colors();
			delete occlusion;//		= new _Occlusion();
			delete timeSys;//		= new _TimeSys();
			delete framerate;//		= new _FrameRate();
			delete profiles;//		= new _Profile();
			delete skeleton;//		= new _Joint();			// TODO: Test instance, remove
			delete audioSys;//		= new AudioSys();
			delete helper;//		= new _Helper();
			delete collision;//		= new _Collision();
			delete postProcess;//	= new PostProcess();
			delete shader;//		= new Shader_System(*matrix);
			delete sysTex;//		= new _SystemTextures();
			delete matrix;//		= new Matrix_System();	// This is the matrix stack class, it is not meant to be used for basic matrix manipulation
			delete glinit;//		= new GlInit_System();
			delete state;//			= new _State();
		}
	}

	// Last, set up helper functions
	#include "./gamesys.h"

#endif /* CORE_H_ */
