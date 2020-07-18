/*
 * runVoid.hpp
 *
 *  Created on: Jun 13, 2010
 *      Author: bcthund
 */

#ifndef RUNVOID_HPP_
#define RUNVOID_HPP_

class _TheVoid {
	private:
		Matrix44f mShadow;
		//Vector4f vSkyColor;
		Keyboard keyboard;
		Water water;
		O2D o2d;
		//O3D o3d;
		E2D e2d;
		GLuint fboRefract[2];

		int		DEBUG_index1;		// Index that can be varied with -/+(=) buttons
		int		DEBUG_max1;			// max for DEBUG_index1
		int		DEBUG_min1;			// min for DEBUG_index1
		int		DEBUG_delta1;		// amount to increase by for DEBUG_index1
		int		DEBUG_index2;		// Index that can be varied with 9/0(+/-) buttons
		int		DEBUG_max2;			// max for DEBUG_index2
		int		DEBUG_min2;			// min for DEBUG_index2
		int		DEBUG_delta2;		// amount to increase by for DEBUG_index1
		bool	DEBUG_WATER1;		// Reflection toggle
		bool	DEBUG_WATER2;		// Refraction toggle
		float	DEBUG_3PDISTANCE;	// Distance for 3rd person
		bool	DEBUG_3PENABLE;		// Enable third person (causes some glitches currently)

		bool bFirstLoad;
		int iCurrentVoid;
		void GetInput();
		void ProcessInput();
		void CheckChunk();
		void GetJump();
		void SetVoid(int mode) { iCurrentVoid = mode; }
		bool load(int mode, int iX, int iZ, bool bUpdate);
		void bindFBO()			{ glBindTexture(GL_TEXTURE_2D, 0); glBindFramebuffer(GL_FRAMEBUFFER, fboRefract[0]); glViewport(0,0,gameVars->screen.w,gameVars->screen.h); };
		void unbindFBO()		{ glBindTexture(GL_TEXTURE_2D, 0); glBindFramebuffer(GL_FRAMEBUFFER, 0); glViewport(0,0,gameVars->screen.w,gameVars->screen.h); };


	public:
		O3D o3d;	// Temporarily here for debugging messages for Bounding Volume
		enum _MODES { EARTH, PRIME, DOMELAKE, INK, SUN, HUGOFOREST, QUICKSILVER, THECHAMBER, ECLIPSE, DOOM, INTERMOST, OUDERMOST, CYBOTRON, TWILIGHT };
		Atmosphere atmosphere;
		WorldMap map;
		_Player player;
		_NPC npc;
		//GLuint texRefract;
		void Run		();
		void reload		();
		float GetHeight ();
		void Update		(bool bThirdPerson);
		void Draw		(bool bWater[2]);
		void Draw		(bool bWater[2], bool bThirdPerson, bool bExosphere, bool bThermosphere, bool bSun, bool bMoon, bool bStratosphere, bool bTroposphere, bool bWorld);

		/*
		 * These structs are for holding void specific data
		 * This should inlude positioning and rotation information
		 * and level information if required.
		 *
		 * The atmosphere, map, and water all need to have specific
		 * data for the voids but the data should only be loaded
		 * for the current void not all possible voids, this will
		 * take too much memory.
		 *
		 * Things to do:
		 *   [X] Move atmosphere, map, and water to _TheVoid class
		 *   [ ] Add atmosphere, map, and water settings to individual voids
		 *   [ ] Add special loading routine to load appropriate void data
		 *   [ ] Restructure tranformation data (pos.xyz, rot.xyz) to be contained within WorldMap class.
		 *   		- The active sheet should updated with the WorldMap transformation for shaders
		 *   		- Individual WorldMap reloads active sheet transformations to "rememeber" players location
		 *   		- Once a WorldMap is closed, the position data doesn't matter anymore because we shouldnt be able to return to the exact place we left anyway.
		 *   		- Opening a WorldMap must reload the starting position according to file data or passed data ie: LoadVoid(PRIME, 100, 99);
		 */

		struct _Prime {
			_TheVoid &parent;
			std::string dir;		// Directory of map data
			int startX, startZ;		// The starting map position
			Vector2ui vfBase;		// The normalized starting map position (if 100x100 is the starting position and iGridSize is 5, then this will be 98x98 [startX-((iGridsize-1)/2)])
			Vector3f pos;
			Vector3f rot;
			bool load(int iX=100, int iZ=100) { return parent.load(PRIME, iX, iZ, false); } ;
			_Prime(_TheVoid &p): parent(p) {
				dir = "./void/prime/";
				startX=0;
				startZ=0;
			};
		} Prime;

		struct _DomeLake {
			std::string dir;		// Directory of map data
			int startX, startZ;		// The starting map position
			Vector2ui vfBase;		// The normalized starting map position (if 100x100 is the starting position and iGridSize is 5, then this will be 98x98 [startX-((iGridsize-1)/2)])
			Vector3f pos;
			Vector3f rot;
		} DomeLake;

		struct _Ink {
			std::string dir;		// Directory of map data
			int startX, startZ;		// The starting map position
			Vector2ui vfBase;		// The normalized starting map position (if 100x100 is the starting position and iGridSize is 5, then this will be 98x98 [startX-((iGridsize-1)/2)])
			Vector3f pos;
			Vector3f rot;
		} Ink;

		struct _Sun {
			std::string dir;		// Directory of map data
			int startX, startZ;		// The starting map position
			Vector2ui vfBase;		// The normalized starting map position (if 100x100 is the starting position and iGridSize is 5, then this will be 98x98 [startX-((iGridsize-1)/2)])
			Vector3f pos;
			Vector3f rot;
		} Sun;

		struct _HugoForest {
			std::string dir;		// Directory of map data
			int startX, startZ;		// The starting map position
			Vector2ui vfBase;		// The normalized starting map position (if 100x100 is the starting position and iGridSize is 5, then this will be 98x98 [startX-((iGridsize-1)/2)])
			Vector3f pos;
			Vector3f rot;
		} HugoForest;

		struct _QuickSilver {
			std::string dir;		// Directory of map data
			int startX, startZ;		// The starting map position
			Vector2ui vfBase;		// The normalized starting map position (if 100x100 is the starting position and iGridSize is 5, then this will be 98x98 [startX-((iGridsize-1)/2)])
			Vector3f pos;
			Vector3f rot;
		} QuickSilver;

		struct _TheChamber {
			std::string dir;		// Directory of map data
			int startX, startZ;		// The starting map position
			Vector2ui vfBase;		// The normalized starting map position (if 100x100 is the starting position and iGridSize is 5, then this will be 98x98 [startX-((iGridsize-1)/2)])
			Vector3f pos;
			Vector3f rot;
		} TheChamber;

		struct _Eclipse {
			std::string dir;		// Directory of map data
			int startX, startZ;		// The starting map position
			Vector2ui vfBase;		// The normalized starting map position (if 100x100 is the starting position and iGridSize is 5, then this will be 98x98 [startX-((iGridsize-1)/2)])
			Vector3f pos;
			Vector3f rot;
		} Eclipse;

		struct _Doom {
			std::string dir;		// Directory of map data
			int startX, startZ;		// The starting map position
			Vector2ui vfBase;		// The normalized starting map position (if 100x100 is the starting position and iGridSize is 5, then this will be 98x98 [startX-((iGridsize-1)/2)])
			Vector3f pos;
			Vector3f rot;
		} Doom;

		struct _Intermost {
			std::string dir;		// Directory of map data
			int startX, startZ;		// The starting map position
			Vector2ui vfBase;		// The normalized starting map position (if 100x100 is the starting position and iGridSize is 5, then this will be 98x98 [startX-((iGridsize-1)/2)])
			Vector3f pos;
			Vector3f rot;
		} Intermost;

		struct _Oudermost {
			std::string dir;		// Directory of map data
			int startX, startZ;		// The starting map position
			Vector2ui vfBase;		// The normalized starting map position (if 100x100 is the starting position and iGridSize is 5, then this will be 98x98 [startX-((iGridsize-1)/2)])
			Vector3f pos;
			Vector3f rot;
		} Oudermost;

		struct _Cybotron {
			std::string dir;		// Directory of map data
			int startX, startZ;		// The starting map position
			Vector2ui vfBase;		// The normalized starting map position (if 100x100 is the starting position and iGridSize is 5, then this will be 98x98 [startX-((iGridsize-1)/2)])
			Vector3f pos;
			Vector3f rot;
		} Cybotron;

		struct _Twilight {
			_TheVoid &parent;
			std::string dir;		// Directory of map data
			int startX, startZ;		// The starting map position
			Vector2ui vfBase;		// The normalized starting map position (if 100x100 is the starting position and iGridSize is 5, then this will be 98x98 [startX-((iGridsize-1)/2)])
			Vector3f pos;
			Vector3f rot;
			bool load(int iX=100, int iZ=100) { return parent.load(TWILIGHT, iX, iZ, false); } ;
			_Twilight(_TheVoid &p): parent(p) {
				dir = "./void/twilight/";
				startX=0;
				startZ=0;
			};
		} Twilight;

		struct _Earth {
			_TheVoid &parent;
			std::string dir;		// Directory of map data
			//int startX, startZ;		// The starting map position
			//Vector2ui vfBase;		// The normalized starting map position (if 100x100 is the starting position and iGridSize is 5, then this will be 98x98 [startX-((iGridsize-1)/2)])
			Vector3f pos;
			Vector3f rot;
			bool load(int iX=100, int iZ=100) { return parent.load(EARTH, iX, iZ, false); } ;
			_Earth(_TheVoid &p): parent(p) {
				dir = "./void/earth/";
				//startX=0;
				//startZ=0;
			};
		} Earth;

		_TheVoid():	map(&atmosphere, ""),
								water(atmosphere),
								o2d(map, atmosphere),
								o3d(map, atmosphere),
								e2d(map, atmosphere),
								iCurrentVoid(EARTH),
								Earth(*this),
								Twilight(*this),
								Prime(*this),
								bFirstLoad(true),
								npc(map),
								player(map),
								atmosphere(),
								DEBUG_index1(0),
								DEBUG_min1(0),
								DEBUG_max1(4),
								DEBUG_delta1(1),
								DEBUG_index2(10),
								DEBUG_min2(0),
								DEBUG_max2(200),
								DEBUG_delta2(10),
								DEBUG_WATER1(true),
								DEBUG_WATER2(true),
								DEBUG_3PDISTANCE(100.0f),
								DEBUG_3PENABLE(false){

			//cout << "Create water pointer...";
			//water = new Water(atmosphere);
			//new(water) Water(atmosphere);
			//cout << "Done" << endl;
			keyboard.calc();
			keyboard.calc(SDLK_c, false);
			keyboard.calc(SDLK_DELETE, false);
			keyboard.calc(SDLK_5, false);
			keyboard.calc(SDLK_6, false);
			keyboard.calc(SDLK_7, false);
			keyboard.calc(SDLK_8, false);
			keyboard.calc(SDLK_9, false);
			keyboard.calc(SDLK_0, false);
			keyboard.calc(SDLK_MINUS, false);
			keyboard.calc(SDLK_EQUALS, false);
		}

} world;

//_TheVoid * world = new(_TheVoid);

bool _TheVoid::load(int mode, int iX, int iZ, bool bUpdate=false) {
	iCurrentVoid = mode;

	if(!bUpdate) {
		if (gameVars->debug.load) cout << "\n\n ########################" << endl;
		if(!gameVars->debug.draw.map) {
			map.vStart[0] = 100;
			map.vStart[1] = 100;
			map.vBase[0] = map.vStart[0]-gameVars->screen.iGridOffset;
			map.vBase[1] = map.vStart[1]-gameVars->screen.iGridOffset;
		}

		std::string sMode = "";
		switch(mode) {
			case(EARTH):
				sMode = "Earth Void";
				break;
			case(PRIME):
				sMode = "Prime Void";
				break;
		}

		cout << endl << "Destroying old World...";
		  if(gameVars->debug.draw.atmosphere)	atmosphere.~Atmosphere();
		  //if(gameVars->debug.draw.map)			map.~WorldMap();
		  //if(gameVars->debug.draw.water)		water.~Water();
		  //if(gameVars->debug.draw.o2d)			o2d.~O2D();
		  //if(gameVars->debug.draw.o3d)			o3d.~O3D();
		  //if(gameVars->debug.draw.e2d)			e2d.~E2D();
		cout << "Done" << endl;

		if (gameVars->debug.load) cout << "## LOADING " << sMode << " ##" << endl;
		if(mode==EARTH) {
			if(!gameVars->debug.draw.map) map.dir = Earth.dir;		//For debugging

			if(gameVars->debug.draw.atmosphere) new(&atmosphere) Atmosphere();
			//if(gameVars->debug.draw.map)		new(&map) WorldMap(atmosphere, Earth.dir);
			if(gameVars->debug.draw.map)		map.reset(&atmosphere, Earth.dir);
			if(atmosphere.water.bEnable)		new(&water) Water(atmosphere);
			if(gameVars->debug.draw.o2d)		new(&o2d) O2D(map, atmosphere);
			if(gameVars->debug.draw.o3d)		new(&o3d) O3D(map, atmosphere);
			if(gameVars->debug.draw.e2d)		new(&e2d) E2D(map, atmosphere);

			//myData.gameTime.iDay = 345;
			//myData.gameTime.iYear = 2334;

			if(gameVars->debug.draw.map)		if (!map.init()) { cout << "Error initializing map" << endl; return 0; }
			if(gameVars->debug.draw.atmosphere)	if (!atmosphere.init()) { cout << "Error initializing sky" << endl; return 0; }
		}
		else if(mode==PRIME) {
			if(!gameVars->debug.draw.map) map.dir = Prime.dir;		//For debugging
			if(gameVars->debug.draw.atmosphere) new(&atmosphere) Atmosphere();
			//if(gameVars->debug.draw.map)		new(&map) WorldMap(atmosphere, Prime.dir);
			if(gameVars->debug.draw.map)		map.reset(&atmosphere, Prime.dir);
			if(atmosphere.water.bEnable)		new(&water) Water(atmosphere);
			if(gameVars->debug.draw.o2d)		new(&o2d) O2D(map, atmosphere);
			if(gameVars->debug.draw.o3d)		new(&o3d) O3D(map, atmosphere);
			if(gameVars->debug.draw.e2d)		new(&e2d) E2D(map, atmosphere);

			Atmosphere_Data myData;
			// SUN
			myData.sun.fLightAltitude				= 0.0f;
			myData.sun.fLightAzimuth				= 0.0f;
			myData.sun.fLightDistance				= 10000;
			myData.sun.fLightZenith					= 0.0f;
			myData.sun.fScale								= 50.0f;
			myData.sun.fShinyBase						= 1.0f;
			myData.sun.sImage								= "sun_01.png";

			myData.sun.vAmbientBase[0]			= 0.1f;
			myData.sun.vAmbientBase[1]			= 0.1f;
			myData.sun.vAmbientBase[2]			= 0.1f;
			myData.sun.vAmbientBase[3]			= 1.0f;

			//myData.sun.vDiffuseBase[0]			= 0.392f;
			//myData.sun.vDiffuseBase[1]			= 0.157f;
			//myData.sun.vDiffuseBase[2]			= 0.502f;
			//myData.sun.vDiffuseBase[3]			= 1.0f;

			myData.sun.vDiffuseBase[0]			= 0.8f;
			myData.sun.vDiffuseBase[1]			= 0.0f;
			myData.sun.vDiffuseBase[2]			= 0.0f;
			myData.sun.vDiffuseBase[3]			= 1.0f;

			myData.sun.vSpecularBase[0]			= 1.0f;
			myData.sun.vSpecularBase[1]			= 0.0f;
			myData.sun.vSpecularBase[2]			= 0.0f;
			myData.sun.vSpecularBase[3]			= 1.0f;

			myData.sun.vPosition[0]					= 500.0f;
			myData.sun.vPosition[1]					= 500.0f;
			myData.sun.vPosition[2]					= 500.0f;

			// MOON
			myData.moon.fLightAltitude			= 0.0f;
			myData.moon.fLightAzimuth				= 45.0f;
			myData.moon.fLightDistance			= 10000;
			myData.moon.fLightZenith				= 0.0f;
			myData.moon.fScale							= 30.0f;
			myData.moon.fShinyBase					= 1.0f;
			myData.moon.sImage							= "moon_01.png";

			myData.moon.vAmbientBase[0]			= 0.1f;
			myData.moon.vAmbientBase[1]			= 0.1f;
			myData.moon.vAmbientBase[2]			= 0.1f;
			myData.moon.vAmbientBase[3]			= 1.0f;

			myData.moon.vDiffuseBase[0]			= 0.1f;
			myData.moon.vDiffuseBase[1]			= 0.1f;
			myData.moon.vDiffuseBase[2]			= 0.1f;
			myData.moon.vDiffuseBase[3]			= 1.0f;

			myData.moon.vSpecularBase[0]		= 1.0f;
			myData.moon.vSpecularBase[1]		= 1.0f;
			myData.moon.vSpecularBase[2]		= 0.0f;
			myData.moon.vSpecularBase[3]		= 1.0f;

			myData.moon.vPosition[0]				= 500.0f;
			myData.moon.vPosition[1]				= 500.0f;
			myData.moon.vPosition[2]				= 500.0f;

			myData.skybox.troposphere.fScale	= 5000;

			myData.gameTime.iDay = 345;
			myData.gameTime.iYear = 2334;

			if(gameVars->debug.draw.map)		if (!map.init(100, 100)) { cout << "Error initializing map" << endl; return 0; }
			if(gameVars->debug.draw.atmosphere)	if (!atmosphere.init(myData)) { cout << "Error initializing sky" << endl; return 0; }
		}

		/*
		 * All modes need these
		 */
		if(gameVars->debug.draw.map)	if (!map.load()) { cout << "Error loading map.\n"; return 0; }
		if(gameVars->debug.draw.map)	if (!map.calc()) { cout << "Error calculating map" << endl; return 0; }

		//if (!atmosphere.skybox.init()) { cout << "Error initializing sky" << endl; return 0; }
		if(gameVars->debug.draw.atmosphere)	if (!atmosphere.skybox.load()) { cout << "Error loading sky" << endl; return 0; }
		if(gameVars->debug.draw.atmosphere)	if (!atmosphere.skybox.calc()) { cout << "Error calculating sky" << endl; return 0; }

		//if (!atmosphere.sun.init()) { cout << "Error initializing sky" << endl; return 0; }
		if(gameVars->debug.draw.atmosphere)	if (!atmosphere.sun.load()) { cout << "Error loading sun" << endl; return 0; }
		if(gameVars->debug.draw.atmosphere)	if (!atmosphere.sun.calc()) { cout << "Error calculating sun" << endl; return 0; }

		//if (!atmosphere.moon.init()) { cout << "Error initializing moon" << endl; return 0; }
		if(gameVars->debug.draw.atmosphere)	if (!atmosphere.moon.load()) { cout << "Error loading moon" << endl; return 0; }
		if(gameVars->debug.draw.atmosphere)	if (!atmosphere.moon.calc()) { cout << "Error calculating moon" << endl; return 0; }

		if(gameVars->debug.draw.o2d)	if (!o2d.init()) { cout << "Error initializing o2d" << endl; return 0; }
		if(gameVars->debug.draw.o2d)	if (!o2d.load()) { cout << "Error loading o2d.\n"; return 0; }
		if(gameVars->debug.draw.o2d)	if (!o2d.calc(map.mapData)) { cout << "Error calculating o2d" << endl; return 0; }

		if(gameVars->debug.draw.o3d)	if (!o3d.init()) { cout << "Error initializing o3d" << endl; return 0; }
		if(gameVars->debug.draw.o3d)	if (!o3d.load()) { cout << "Error loading o3d.\n"; return 0; }
		if(gameVars->debug.draw.o3d)	if (!o3d.calc()) { cout << "Error calculating o3d" << endl; return 0; }

		//if (!World.e2d.init(*gameVars)) { cout << "Error initializing e2d" << endl; return 0; }
		if(gameVars->debug.draw.e2d)	if (!e2d.load()) { cout << "Error loading e2d" << endl; return 0; }
		if(gameVars->debug.draw.e2d)	if (!e2d.calc()) { cout << "Error calculating e2d" << endl; return 0; }

		//if(gameVars->debug.draw.water)	if (!water.init()) { cout << "Error initializing water" << endl; return 0; }
		//if(gameVars->debug.draw.water)	if (!water.load()) { cout << "Error loading water" << endl; return 0; }
		//if(gameVars->debug.draw.water)	if (!water.calc()) { cout << "Error calculating water" << endl; return 0; }

		if(atmosphere.water.bEnable) atmosphere.water.load();
		if(atmosphere.water.bEnable) atmosphere.water.calc();
	}

	/*
	 * These items get recalculated
	 * when a map stitch occurrs
	 */
	if(!bUpdate) atmosphere.snow.load();
	atmosphere.snow.calc();

	if(!bUpdate) atmosphere.hail.load();
	atmosphere.hail.calc();

	if(!bUpdate) atmosphere.rain.load();
	atmosphere.rain.calc();

	//if(!bUpdate) npc.load();
	//if(!bUpdate) npc.calc();
	if(!bUpdate) npc.reload();

	if(!bUpdate) {
		atmosphere.flora.load();
		atmosphere.flora.calc(map);
	}
	else atmosphere.flora.calc(map, true);

	if(!bUpdate) {
		atmosphere.uwflora.load();
		atmosphere.uwflora.calc(map);
	}
	else atmosphere.uwflora.calc(map, true);

	if(!bUpdate) {
		atmosphere.grass.load();
		atmosphere.grass.calc(map);
	}
	else atmosphere.grass.calc(map, true);

	// Setup default FOG
	atmosphere.sun.vSpecularColor[0]	=	atmosphere.sun.vSpecularBase[0];
	atmosphere.sun.vSpecularColor[1]	=	atmosphere.sun.vSpecularBase[1];
	atmosphere.sun.vSpecularColor[2]	=	atmosphere.sun.vSpecularBase[2];
	atmosphere.sun.vSpecularColor[3]	=	atmosphere.sun.vSpecularBase[3];

	Core.shader.activeFog.vFogColor[0]	=	Core.shader.worldFog.vFogColor[0];
	Core.shader.activeFog.vFogColor[1]	=	Core.shader.worldFog.vFogColor[1];
	Core.shader.activeFog.vFogColor[2]	=	Core.shader.worldFog.vFogColor[2];
	Core.shader.activeFog.vFogColor[3]	=	Core.shader.worldFog.vFogColor[3];

	Core.shader.activeFog.fStart		=	Core.shader.worldFog.fStart;
	Core.shader.activeFog.fEnd			=	Core.shader.worldFog.fEnd;
	Core.shader.activeFog.fDensity		=	Core.shader.worldFog.fDensity;
	Core.shader.activeFog.iEquation		=	Core.shader.worldFog.iEquation;

//	// Setup FBO for underwater Refraction
//	glGenFramebuffers(1, &fboRefract[0]);
//	glGenTextures(1, &texRefract);
//
//	glBindTexture(GL_TEXTURE_2D, texRefract);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, gameVars->screen.w, gameVars->screen.h, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glBindFramebuffer(GL_FRAMEBUFFER, fboRefract[0]);
//	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texRefract, 0);
//
//	glGenRenderbuffers(1, &fboRefract[1]);
//	glBindRenderbuffer(GL_RENDERBUFFER, fboRefract[1]);
//	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, gameVars->screen.w, gameVars->screen.h);
//	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fboRefract[1]);
//
//
//	int check = glCheckFramebufferStatus(GL_FRAMEBUFFER);
//	cout << "runWorld FBO: ";
//	switch (check) {
//		case GL_FRAMEBUFFER_COMPLETE:
//			cout << "GL_FRAMEBUFFER_COMPLETE" << endl;
//		break;
//		case GL_FRAMEBUFFER_UNDEFINED:
//			cout << "GL_FRAMEBUFFER_UNDEFINED" << endl;
//		break;
//		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
//			cout << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT" << endl;
//		break;
//		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
//			cout << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT" << endl;
//		break;
//		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
//			cout << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER" << endl;
//		break;
//		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
//			cout << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER" << endl;
//		break;
//		case GL_FRAMEBUFFER_UNSUPPORTED:
//			cout << "GL_FRAMEBUFFER_UNSUPPORTED" << endl;
//		break;
//		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
//			cout << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE" << endl;
//		break;
//		case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
//			cout << "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS" << endl;
//		break;
//		default:
//			cout << "UNDEFINED ERROR! [" <<  check << "]" << endl;
//		break;
//	}
//
//	glBindTexture(GL_TEXTURE_2D, 0);
//	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return 1;
}

//This is the primary function of this class
//This function calls all other functions in the class in the proper order
void _TheVoid::Run() {
	//if(!Mix_PlayingMusic()) gameSys.audioSys.playMusic(1);
	gameSys.audioSys.playMusic(1);

	glClearColor(	gameVars->screen.vClearColorCurrent[0],
					gameVars->screen.vClearColorCurrent[1],
					gameVars->screen.vClearColorCurrent[2],
					gameVars->screen.vClearColorCurrent[3]	);

	glClear( gameVars->screen.clear );

	/*
	 * Update the terrain if necessary, this must be done now!
	 * But we only want to do this check IF the map is being drawn
	 */
	if(gameVars->debug.draw.map)	CheckChunk();

	/*
	 *	Set the height according to the currently selected stance
	 */
	if(gameVars->player.active->status.move.iStance == GAME::MENU.MOVE.STANCE.STAND) {
			gameVars->player.active->transform.currentHeight = gameVars->player.active->transform.eyeHeight;
			gameVars->controls.modStance = 1;
	}
	else if(gameVars->player.active->status.move.iStance == GAME::MENU.MOVE.STANCE.KNEEL) {
			gameVars->player.active->transform.currentHeight = gameVars->player.active->transform.eyeHeight/2;
			gameVars->controls.modStance = gameVars->transform.fCrouchDiff;
	}
	else if(gameVars->player.active->status.move.iStance == GAME::MENU.MOVE.STANCE.PRONE) {
			gameVars->player.active->transform.currentHeight = 1;
			gameVars->controls.modStance = gameVars->transform.fProneDiff;
	}

	if (!gameVars->state.battle) {
		//if(!gameVars->state.bChangeState) GetInput();
		GetInput();
	}

	/*
	 * TODO: If a movement was made, do a collision test on O3D's and if
	 * 			a collision is detected, currently just print a message
	 * 			to the screen. To do this we will probably need to set a
	 * 			flag in the bounding volume class that can be used in
	 * 			the debug routine to print a message to the screen. This
	 * 			will be a simple true/false indication for a collision.
	 *
	 * TODO: When a collision is detected we can then proceed to full
	 * 			model collision detection for that O3D. Since the code
	 * 			for collision detection on an entire model might be
	 * 			expensive we want to limit this.
	 */

	if (!gameVars->controls.fly) {
		gameVars->player.active->transform.pos[1] = map.getHeight(gameVars->player.active->transform.pos[0], gameVars->player.active->transform.pos[2])*gameVars->screen.iScale;

		player.updateCohortPlacement();

		//GetHeight();	// Get the height at this location and store it
		//GetJump();		// Set the height based on jump and gravity
	}

	//Update the world content
	Update(DEBUG_3PENABLE);
}

//This function keeps track of our jump as well as gravity for falling.
//Gravity is taken care of here currently because the jump only handles upward movement.
//When upward momentum reaches zero, gravity takes over
void _TheVoid::GetJump() {
	//gameVars->player.active->transform.pos[1] = gameVars->transform.groundHeight;
}

//This function checks what chunk we are on, what chunk is the center and whether we should load a new terrain set
//
void _TheVoid::CheckChunk() {
	int xGrid = -(int)gameVars->player.active->transform.pos[0]/(1024);
	int zGrid = -(int)gameVars->player.active->transform.pos[2]/(1024);
	int iCenter = gameVars->screen.iGridOffset;
	Vector2i iLoadNew = {iCenter-iCenter, iCenter+iCenter};

	if (xGrid==iLoadNew[0] || zGrid==iLoadNew[0] || xGrid==iLoadNew[1] || zGrid==iLoadNew[1]) {
		if(gameVars->debug.loadMap) {
			gameVars->screen.bReload = true;
//		cout << "Reload!" << endl;
			reload();
		}
	}
}

//This function checks what chunk we are on, what chunk is the center and whether we should load a new terrain set
//
void _TheVoid::reload() {
	int xGrid = -(int)gameVars->player.active->transform.pos[0]/(1024);
	int zGrid = -(int)gameVars->player.active->transform.pos[2]/(1024);
	//int iCenter = gameVars.screen.iTerrainGrid;
	int iCenter = gameVars->screen.iGridOffset;
	Vector2i iLoadNew = {iCenter-iCenter, iCenter+iCenter};

	if (xGrid==iLoadNew[0] || zGrid==iLoadNew[0] || xGrid==iLoadNew[1] || zGrid==iLoadNew[1]) {
		float xPos = -(gameVars->player.active->transform.pos[0]+(xGrid*1024));
		float zPos = -(gameVars->player.active->transform.pos[2]+(zGrid*1024));
		int iGrid = gameVars->screen.iGridOffset;

		//Set the characters position on the new layout
		gameVars->player.active->transform.pos[0]=-xPos;
		gameVars->player.active->transform.pos[2]=-zPos;
		gameVars->player.active->transform.pos[0]-=gameVars->screen.iGridOffset*1024;
		gameVars->player.active->transform.pos[2]-=gameVars->screen.iGridOffset*1024;

		/*
		 * SHIFT_LAST is used here to reload everything for the new location. This
		 * 		works because the new location is set when shifting the map first.
		 * SHIFT_X where X is the direction to shift will move data structures
		 * 		and only load new data.
		 * This needs to be added into a background routine, possibly with multithreading?
		 *
		 * We need to remove permanently setting the new location from the map.shift function
		 * 		and instead do it last here. This will allow each shift function for
		 * 		the different objects to use the same code to shift data structures
		 * 		and load new data from file.
		 *
		 */
		if (xGrid==iLoadNew[0]) {
			if(gameVars->debug.draw.map)	map.shift(SHIFT_RIGHT);
			//map.shift(SHIFT_LAST);
			if(gameVars->debug.draw.o2d)	o2d.shift(SHIFT_LAST);
			if(gameVars->debug.draw.e2d)	e2d.shift(SHIFT_LAST);
			if(gameVars->debug.draw.o3d)	o3d.shift(SHIFT_UP);
		}
		if (xGrid==iLoadNew[1]) {
			if(gameVars->debug.draw.map)	map.shift(SHIFT_LEFT);
			//map.shift(SHIFT_LAST);
			if(gameVars->debug.draw.o2d)	o2d.shift(SHIFT_LAST);
			if(gameVars->debug.draw.e2d)	e2d.shift(SHIFT_LAST);
			if(gameVars->debug.draw.o3d)	o3d.shift(SHIFT_UP);
		}
		if (zGrid==iLoadNew[0]) {
			if(gameVars->debug.draw.map)	map.shift(SHIFT_DOWN);
			//map.shift(SHIFT_LAST);
			if(gameVars->debug.draw.o2d)	o2d.shift(SHIFT_LAST);
			if(gameVars->debug.draw.e2d)	e2d.shift(SHIFT_LAST);
			if(gameVars->debug.draw.o3d)	o3d.shift(SHIFT_UP);
		}
		if (zGrid==iLoadNew[1]) {
			if(gameVars->debug.draw.map)	map.shift(SHIFT_UP);
			//map.shift(SHIFT_LAST);
			if(gameVars->debug.draw.o2d)	o2d.shift(SHIFT_LAST);
			if(gameVars->debug.draw.e2d)	e2d.shift(SHIFT_LAST);
			if(gameVars->debug.draw.o3d)	o3d.shift(SHIFT_UP);
		}

		load(iCurrentVoid, map.vStart[0], map.vStart[1], true);
		//atmosphere.flora.calc(map);
	}
}

//This function calculates the height of the terrain under the player and stores the value to be used elsewhere
//The value is not set here because we want to take gravity into account and jumping in the getJump() function
//float _TheVoid::GetHeight() {
//	bool bDeep=false;
////NCURSES
////refresh();
//	//What terrain chunk/grid are we on? (Range depends on size of gameVars.iTerrainGrid)
//	int xGrid = -(int)gameVars->player.active->transform.pos[0]/1024;
//	int zGrid = -(int)gameVars->player.active->transform.pos[2]/1024;
//
//	//xGrid = -xGrid;
//	//zGrid = -zGrid;
//
//	//What is our exact position on the terrain chunk (0-1023)
//		int xPos = -(gameVars->player.active->transform.pos[0]+(xGrid*1024));
//		int yPos = -(gameVars->player.active->transform.pos[1]+(zGrid*1024));
//		int zPos = -(gameVars->player.active->transform.pos[2]+(zGrid*1024));
//
//	//Define variables
//		Vector3f a, b, c, d, p, q;
//		float u, v, w, t;
//		int opp, adj, h;
//		int iResult;
//
//		//Define the player position ray
//		float iRayDepth;
//		if (bDeep) iRayDepth=5000;
//		else iRayDepth=100;
//		p[0] =  xPos;
//		p[1] =  -iRayDepth;
//		p[2] =  zPos;
//
//		q[0] =  xPos;
//		q[1] =  iRayDepth;
//		q[2] =  zPos;
//
//		//Set barycentrics to 0
//		u = 0;
//		v = 0;
//		w = 0;
//		t = 0;
//
//	//Procedure Code Outline
//	bool foundHeight = false;
//	bool legalHeight = false;
//	for (int i=0; i < map.mapData[xGrid][zGrid].numFaces; i++) {
//		//Get Triangle Data for current count
//		//Get the triangle vertex data, for test point
//		a[0] = map.mapData[xGrid][zGrid].vVerts[int(map.mapData[xGrid][zGrid].vGroups[i][0])][0]*16;
//		a[1] = map.mapData[xGrid][zGrid].vVerts[int(map.mapData[xGrid][zGrid].vGroups[i][0])][1]*16;
//		a[2] = map.mapData[xGrid][zGrid].vVerts[int(map.mapData[xGrid][zGrid].vGroups[i][0])][2]*16;
//
//		//Check distance from player, if within 200 units { (Only check one vertex, this will suffice)
//			//Distance Calculations
//			opp = a[0] - xPos;
//			adj = a[2] - zPos;
//			h = sqr(opp) + sqr(adj);
//			h = sqrt(h);
//
//			//If ray is inside triangle {
//			if(h <= 100) {;
//				//Get the rest of the triangle Data
//				b[0] = map.mapData[xGrid][zGrid].vVerts[int(map.mapData[xGrid][zGrid].vGroups[i][1])][0]*16;
//				b[1] = map.mapData[xGrid][zGrid].vVerts[int(map.mapData[xGrid][zGrid].vGroups[i][1])][1]*16;
//				b[2] = map.mapData[xGrid][zGrid].vVerts[int(map.mapData[xGrid][zGrid].vGroups[i][1])][2]*16;
//				c[0] = map.mapData[xGrid][zGrid].vVerts[int(map.mapData[xGrid][zGrid].vGroups[i][2])][0]*16;
//				c[1] = map.mapData[xGrid][zGrid].vVerts[int(map.mapData[xGrid][zGrid].vGroups[i][2])][1]*16;
//				c[2] = map.mapData[xGrid][zGrid].vVerts[int(map.mapData[xGrid][zGrid].vGroups[i][2])][2]*16;
//
//				//Projection of triangle onto the xz plane, we don't care about the height right now
//				Vector3f testA, testB,testC, testP;
//				testA[0] = a[0];
//				testA[1] = 0;
//				testA[2] = a[2];
//				testB[0] = b[0];
//				testB[1] = 0;
//				testB[2] = b[2];
//				testC[0] = c[0];
//				testC[1] = 0;
//				testC[2] = c[2];
//				testP[0] = p[0];
//				testP[1] = 0;
//				testP[2] = p[2];
//
//				/*
//				 * Are we currently inside the projected triangle?
//				 */
//				if (PointInTriangle(testP, testA, testB, testC)) {
//					/*
//					 * We are inside the tested triangle
//					 * Perform the intersection test to find our t value
//					 * The t value is the intersection height of the triangle
//					 * 	on the vertical ray.
//					 */
//					iResult=IntersectTri(p, q, a, c, b, u, v, w, t);
//
//					/*
//					 * Store the height and calculate the difference
//					 * between the current height and the new height
//					 */
//					float newHeight = (iRayDepth-((2*iRayDepth)*t));
//					//float diff = gameVars->transform.groundHeight-newHeight;
////					cout << "Height Diff: " << diff << endl;
//					//cout << "Height: " << newHeight << endl;
//
//
//
//					/*
//					 * Is the new height outside of our climbing threshold?
//					 * Or are we in Deep mode, used when exiting fly mode.
//					 */
////					if (diff<gameVars->transform.maxIncline || bDeep) {
////						gameVars->transform.groundHeight = newHeight;
////						gameVars->controls.modClimb = 1.0f;
//						legalHeight = true;
////					}
////					else
////					{
//						/*
//						 * Routine to set an incline limit
//						 * When the climbing modifer is below this value, do not
//						 *  allow player to climb at all. This might be a good
//						 *  spot to add the players climbing skill.
//						 */
////						float newMod = 1/diff;
//						//if (newMod < 0.1) {
//						//	newMod = 0;
//						//	legalHeight = false;
//						//}
//						//else {
////							gameVars->controls.modClimb = newMod;
//							//gameVars->transform.groundHeight = newHeight;
////							legalHeight = false;
//						//}
////						cout << "MoveMod: [" << newMod << "]" << endl << endl;
////					}
//					foundHeight=true;
//				}
//			}
//		if (foundHeight) break;
//	}
//	return legalHeight;
//}

//This function updates the opengl pipeline with our current geometry
void _TheVoid::Update(bool bThirdPerson) {
	gameVars->timer.pTimer.start("runVoid - Update");
	if(-(gameVars->player.active->transform.pos[1]-gameVars->player.active->transform.eyeHeight) < (gameVars->world.water.iHeight*gameVars->screen.iScale)) {
		//cout << "BELOW WATER!" << endl;
		gameVars->player.active->transform.bBelowWater = true;
		atmosphere.sun.vSpecularColor[0] 	=	Core.shader.waterFog.vFogColor[0]*5;
		atmosphere.sun.vSpecularColor[1] 	=	Core.shader.waterFog.vFogColor[1]*5;
		atmosphere.sun.vSpecularColor[2] 	=	Core.shader.waterFog.vFogColor[2]*5;
		atmosphere.sun.vSpecularColor[3] 	=	Core.shader.waterFog.vFogColor[3]*5;

		Core.shader.activeFog.vFogColor[0]	=	Core.shader.waterFog.vFogColor[0];
		Core.shader.activeFog.vFogColor[1]	=	Core.shader.waterFog.vFogColor[1];
		Core.shader.activeFog.vFogColor[2]	=	Core.shader.waterFog.vFogColor[2];
		Core.shader.activeFog.vFogColor[3]	=	Core.shader.waterFog.vFogColor[3];

		Core.shader.activeFog.fStart		=	Core.shader.waterFog.fStart;
		Core.shader.activeFog.fEnd			=	Core.shader.waterFog.fEnd;
		Core.shader.activeFog.fDensity		=	Core.shader.waterFog.fDensity;
		Core.shader.activeFog.iEquation		=	Core.shader.waterFog.iEquation;
	} else {
		//cout << "Above water." << endl;
		gameVars->player.active->transform.bBelowWater = false;
		atmosphere.sun.vSpecularColor[0]	=	atmosphere.sun.vSpecularBase[0];
		atmosphere.sun.vSpecularColor[1]	=	atmosphere.sun.vSpecularBase[1];
		atmosphere.sun.vSpecularColor[2]	=	atmosphere.sun.vSpecularBase[2];
		atmosphere.sun.vSpecularColor[3]	=	atmosphere.sun.vSpecularBase[3];

		Core.shader.activeFog.vFogColor[0]	=	Core.shader.worldFog.vFogColor[0];
		Core.shader.activeFog.vFogColor[1]	=	Core.shader.worldFog.vFogColor[1];
		Core.shader.activeFog.vFogColor[2]	=	Core.shader.worldFog.vFogColor[2];
		Core.shader.activeFog.vFogColor[3]	=	Core.shader.worldFog.vFogColor[3];

		Core.shader.activeFog.fStart		=	Core.shader.worldFog.fStart;
		Core.shader.activeFog.fEnd			=	Core.shader.worldFog.fEnd;
		Core.shader.activeFog.fDensity		=	Core.shader.worldFog.fDensity;
		Core.shader.activeFog.iEquation		=	Core.shader.worldFog.iEquation;
	}

	gameVars->timer.pTimer.start("runVoid - Water Prepass");
	if(atmosphere.water.bEnable) {
		if(gameVars->player.active->transform.bBelowWater == false) {
			bool bWater[2] = {true, false};
			atmosphere.water.bindReflectFBO();
			Draw(bWater);
			atmosphere.water.unbindFBO();
		}
		{	// Always render refraction
			bool bWater[2] = {false, true};
			atmosphere.water.bindRefractFBO();
			Draw(bWater);
			atmosphere.water.unbindFBO();
		}
	}

	gameVars->timer.pTimer.stop("runVoid - Water Prepass");
	if(postProcess.bEnable) {
		gameVars->timer.pTimer.start("runVoid - PostProcess");
		{	// Always render water
			//bool bWater[2] = {false, false};
			bool bWater[2] = {DEBUG_WATER1, DEBUG_WATER2};		// Allow us to control water rendering

			if(gameVars->screen.ePolyMode == PM_LINE) {
				//glLineWidth(gameVars->screen.fLineWidth);
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			} else if(gameVars->screen.ePolyMode == PM_POINT) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
			} else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}

			if(gameVars->screen.MultiSample) postProcess.RenderLayer("Multisample");
			else postProcess.RenderLayer("Layer0");
			Draw(bWater, bThirdPerson, true, true, true, true, true, true, true);
			postProcess.EndRenderLayer();

			if(gameVars->screen.ePolyMode != PM_FILL) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glClear( gameVars->screen.clear );
			}

			GLuint world = postProcess.ApplyLensFlare();

			postProcess.ApplyContrast();
			postProcess.ApplyBrightness();
			postProcess.ApplyHBlur();
			postProcess.ApplyVBlur();
			postProcess.ApplyCombine(world);	// Combine the latest result with the world (Bloom overlay)
			if(gameVars->player.active->transform.bBelowWater == true) postProcess.ApplyUnderwater();

			//if(gameVars->screen.MultiSample) postProcess.ApplyDepthOfField("Multisample");
			//else postProcess.ApplyDepthOfField("Layer0");

			//postProcess.ApplyCartoon();

			postProcess.RenderToScreen();
			gameSys.drawSprite(gameVars->screen.halfW-16, gameVars->screen.halfH-16, 32, 32, "crosshair.png", false, false, gameVars->color.green);
		}
		gameVars->timer.pTimer.stop("runVoid - PostProcess");
	} else {
		bool bWater[2] = {DEBUG_WATER1, DEBUG_WATER2};
		Draw(bWater, bThirdPerson, true, true, true, true, true, true, true);
		gameSys.drawSprite(gameVars->screen.halfW-16, gameVars->screen.halfH-16, 32, 32, "crosshair.png", false, false, gameVars->color.green);
	}
	gameVars->timer.pTimer.stop("runVoid - Update");
}

void _TheVoid::Draw(bool bWater[2]) {
	Draw(bWater, false, true, true, true, true, true, true, true);
}

void _TheVoid::Draw(bool bWater[2], bool bThirdPerson=false, bool bExosphere=true, bool bThermosphere=true, bool bSun=true, bool bMoon=true, bool bStratosphere=true, bool bTroposphere=true, bool bWorld=true) {
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear( gameVars->screen.clear );

	// Modifications for Water Passes
	float fPosY, fRotY, fCurrentHeight;
	bool 	bDrawAtmosphere,
			bDrawSprites,
			bDrawFlora,
			bDrawWeather,
			bDrawOther,
			bFlareQuery;
	if (bWater[0]==true && bWater[1]==false) {
		// Reflection, Invert Y position, Invert Y Rotation
		fPosY			= -gameVars->player.active->transform.pos[1];
		fRotY			= -gameVars->player.active->transform.rot[0];
		fCurrentHeight	= -gameVars->player.active->transform.currentHeight;
		atmosphere.water.vClipPlane[0] = 0;
		atmosphere.water.vClipPlane[1] = 1;
		atmosphere.water.vClipPlane[2] = 0;
		//atmosphere.water.vClipPlane[3] = atmosphere.water.fFloor;
		atmosphere.water.vClipPlane[3] = 8.0f/16.0f;
		bDrawAtmosphere	= true;
		bDrawSprites	= true;
		bDrawFlora		= false;
		bDrawWeather	= false;
		bDrawOther		= false;
		bFlareQuery		= false;
		glEnable(GL_CLIP_DISTANCE0);
	}
	else if (bWater[0]==false && bWater[1]==true) {
		// Refraction, standard camera angles
		fPosY			= gameVars->player.active->transform.pos[1];
		fRotY			= gameVars->player.active->transform.rot[0];
		fCurrentHeight	= gameVars->player.active->transform.currentHeight;
		atmosphere.water.vClipPlane[0] = 0;
		atmosphere.water.vClipPlane[1] = -1;
		atmosphere.water.vClipPlane[2] = 0;
		//atmosphere.water.vClipPlane[3] = atmosphere.water.fFloor;
		atmosphere.water.vClipPlane[3] = -8.0f/16.0f;
		bDrawAtmosphere	= true;
		bDrawSprites	= true;
		bDrawFlora		= true;
		bDrawWeather	= false;
		bDrawOther		= false;
		bFlareQuery		= false;
		glDisable(GL_CLIP_DISTANCE0);
	}
	else if (bWater[0]==true && bWater[1]==true && gameVars->player.active->transform.bBelowWater == true) {
		// Standard camera angles
		fPosY			= gameVars->player.active->transform.pos[1];
		fRotY			= gameVars->player.active->transform.rot[0];
		fCurrentHeight	= gameVars->player.active->transform.currentHeight;
		atmosphere.water.vClipPlane[0] = 0;
		atmosphere.water.vClipPlane[1] = -1;
		atmosphere.water.vClipPlane[2] = 0;
		//atmosphere.water.vClipPlane[3] = -8.0f/16.0f;
		atmosphere.water.vClipPlane[3] = -8.0f/16.0f;
		bDrawAtmosphere	= false;
		bDrawSprites	= false;
		bDrawFlora		= true;
		bDrawWeather	= false;
		bDrawOther		= true;
		bFlareQuery		= true;
		glEnable(GL_CLIP_DISTANCE0);
	}
	else if (bWater[0]==true && bWater[1]==true && gameVars->player.active->transform.bBelowWater == false) {
		// Standard camera angles
		fPosY			= gameVars->player.active->transform.pos[1];
		fRotY			= gameVars->player.active->transform.rot[0];
		fCurrentHeight	= gameVars->player.active->transform.currentHeight;
		atmosphere.water.vClipPlane[0] = 0;
		atmosphere.water.vClipPlane[1] = 1;
		atmosphere.water.vClipPlane[2] = 0;
		//atmosphere.water.vClipPlane[3] = -8.0f/16.0f;
		atmosphere.water.vClipPlane[3] = 8.0f/16.0f;
		bDrawAtmosphere	= true;
		bDrawSprites	= true;
		bDrawFlora		= true;
		bDrawWeather	= true;
		bDrawOther		= true;
		bFlareQuery		= true;
		//glEnable(GL_CLIP_DISTANCE0);
		glDisable(GL_CLIP_DISTANCE0);
	}
	else {
		// Standard camera angles
		fPosY			= gameVars->player.active->transform.pos[1];
		fRotY			= gameVars->player.active->transform.rot[0];
		fCurrentHeight	= gameVars->player.active->transform.currentHeight;
		atmosphere.water.vClipPlane[0] = 0;
		atmosphere.water.vClipPlane[1] = 0;
		atmosphere.water.vClipPlane[2] = 0;
		atmosphere.water.vClipPlane[3] = 0;
		bDrawAtmosphere	= true;
		bDrawSprites	= true;
		bDrawFlora		= true;
		bDrawWeather	= true;
		bDrawOther		= true;
		bFlareQuery		= true;
		glDisable(GL_CLIP_DISTANCE0);
	}

	//glDisable(GL_CULL_FACE);
	// Draw Space Box
	if(gameVars->debug.draw.atmosphere) {
		gameVars->timer.pTimer.start("runVoid - Atmosphere");
		if (bDrawAtmosphere) {
			Core.matrix.Push();
				Core.matrix.Rotate(fRotY, 1.0, 0.0, 0.0);
				Core.matrix.Rotate(gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
				//Core.matrix.Translate(gameVars->player.active->transform.pos[0]*gameVars->screen.iScale, (fPosY-fCurrentHeight), gameVars->player.active->transform.pos[2]*gameVars->screen.iScale);

				glDisable(GL_DEPTH_TEST);
				if(bExosphere) {
					Core.matrix.Push();
						Core.matrix.Rotate(M_DegToRad(30), 1.0, 0.0, 0.0);
						//Core.matrix.Rotate(M_DegToRad(atmosphere.sun.fLightAltitude), 0.0, 0.0, 1.0);
						Core.matrix.Rotate(atmosphere.gameTime.get_ticks()/500000, 0.0, 0.0, 1.0);		// TODO: Make speed variable in atmosphere class
						Core.matrix.Scale(atmosphere.skybox.exosphere.fScale);
						Core.matrix.SetTransform();
						Core.shader.use(GLS_EXOSPHERE);
						Core.shader.getUniform(atmosphere, GLS_EXOSPHERE);
						atmosphere.skybox.exosphere.draw();
					Core.matrix.Pop();
				}

				if(bThermosphere) {
					Core.matrix.Push();
						Core.matrix.Rotate(M_DegToRad(atmosphere.skybox.thermosphere.fRot), 0.0, 1.0, 0.0);
						Core.matrix.Scale(atmosphere.skybox.thermosphere.fScale);
						Core.matrix.SetTransform();
						Core.shader.use(GLS_THERMOSPHERE);
						Core.shader.getUniform(atmosphere, GLS_THERMOSPHERE);
						atmosphere.skybox.thermosphere.draw();
					Core.matrix.Pop();
				}
				glEnable(GL_DEPTH_TEST);

				// MOON
				if(bMoon) {
					Core.matrix.Push();
						Core.matrix.Translate(atmosphere.moon.vPosition[0], atmosphere.moon.vPosition[1], atmosphere.moon.vPosition[2]);
						//Core.matrix.Translate(0.0f, -500.0f, 0.0f);
						Core.matrix.Rotate(gameVars->player.active->transform.rot[1], 0.0, -1.0, 0.0);
						Core.matrix.Rotate(fRotY, -1.0, 0.0, 0.0);
						Core.matrix.Scale(atmosphere.moon.fScale);
						Core.matrix.SetTransform();
						Core.shader.use(GLS_SUN);
						Core.shader.getUniform(atmosphere, GLS_SUN);
						atmosphere.moon.draw();
					Core.matrix.Pop();
				}


				// CLOUDS!
				// Draw here simply for alpha
				if(bStratosphere) {
					Core.matrix.Push();
						Core.matrix.Scale(atmosphere.skybox.stratosphere.fScale);
						Core.matrix.SetTransform();
						Core.shader.use(GLS_STRATOSPHERE);
						Core.shader.getUniform(atmosphere, GLS_STRATOSPHERE);
						atmosphere.skybox.stratosphere.draw();
					Core.matrix.Pop();
				}

				// Draw here simply for alpha
				if(bTroposphere) {
					Core.matrix.Push();
						Core.matrix.Scale(atmosphere.skybox.troposphere.fScale);
						Core.matrix.SetTransform();
						Core.shader.use(GLS_TROPOSPHERE);
						Core.shader.getUniform(atmosphere, GLS_TROPOSPHERE);
						atmosphere.skybox.troposphere.draw();
					Core.matrix.Pop();
				}
			Core.matrix.Pop();
		}
		gameVars->timer.pTimer.stop("runVoid - Atmosphere");
	}

	if(bWorld) {
		Core.matrix.Push();

			// Ensure Identity matrix at start
			Matrix44f mI;
			mI[0] = 1;	mI[1] = 0;	mI[2] = 0;	mI[3] = 0;
			mI[4] = 0;	mI[5] = 1;	mI[6] = 0;	mI[7] = 0;
			mI[8] = 0;	mI[9] = 0;	mI[10] = 1;	mI[11] = 0;
			mI[12] = 0;	mI[13] = 0;	mI[14] = 0;	mI[15] = 1;
			Core.matrix.SetModelView(mI);

			if(bThirdPerson) Core.matrix.Translate(0, -10, -DEBUG_3PDISTANCE);		//3rd person view
			Core.matrix.Rotate(fRotY, 1.0, 0.0, 0.0);
			Core.matrix.Rotate(gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
			Core.matrix.Translate(gameVars->player.active->transform.pos[0]*gameVars->screen.iScale, (fPosY-fCurrentHeight), gameVars->player.active->transform.pos[2]*gameVars->screen.iScale);
			Core.matrix.SetTransform();

			gameVars->timer.pTimer.start("runVoid - Map");
			//if(gameVars->debug.draw.map)	map.draw(GLS_DIRECTIONAL);							//This shader draw the standard terrain above and below water level

			//if(bWater[0]==true && bWater[1]==true) {
			//	if(gameVars->debug.draw.map)	map.draw(GLS_DIRECTIONAL_TERRAIN, true);		//This shader draw the standard terrain above and below water level
			//} else {
				if(gameVars->debug.draw.map)	map.draw(GLS_DIRECTIONAL_TERRAIN);				//This shader draw the standard terrain above and below water level
			//}

			gameVars->timer.pTimer.stop("runVoid - Map");
			if (bDrawSprites) {
				if(gameVars->debug.draw.o3d)	o3d.draw(GLS_DIRECTIONAL);					//No blending on 3D object, draw first
				if(gameVars->debug.draw.e2d)	e2d.draw(GLS_FLAT_FOG);						//May have blending, draw near last
				if(gameVars->debug.draw.npc)	npc.draw(atmosphere);
				gameVars->timer.pTimer.start("runVoid - O2D");
				if(gameVars->screen.bInstance) {
					if(gameVars->debug.draw.o2d)	o2d.draw(GLS_FLAT_FOG_INSTANCE);						//Often has blending, draw last (Needs distance sorting for self-blending)
				}
				else {
					if(gameVars->debug.draw.o2d)	o2d.draw(GLS_FLAT_FOG_SHEAR);						//Often has blending, draw last (Needs distance sorting for self-blending)
				}
				gameVars->timer.pTimer.stop("runVoid - O2D");
			}

			Core.matrix.Push();
				Core.matrix.SetModelView(mI);
				Core.matrix.Rotate(fRotY, 1.0, 0.0, 0.0);
				Core.matrix.Rotate(gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
				if(bSun) {
					Core.matrix.Push();
						Core.matrix.Translate(atmosphere.sun.vPosition[0], atmosphere.sun.vPosition[1], atmosphere.sun.vPosition[2]);
						Core.matrix.Rotate(gameVars->player.active->transform.rot[1], 0.0, -1.0, 0.0);
						Core.matrix.Rotate(fRotY, -1.0, 0.0, 0.0);
						Core.matrix.SetTransform();
						Core.shader.use(GLS_SUN);
						Core.shader.getUniform(atmosphere, GLS_SUN);
						if(bFlareQuery && bWorld) occlusion.StartQuery("ApplyLensFlare");
							// Draw the sprite at this location
							atmosphere.sun.draw();
						if(bFlareQuery && bWorld) occlusion.EndQuery("ApplyLensFlare");
					Core.matrix.Pop();
				}

//				// CLOUDS!
				if(bStratosphere) {
					Core.matrix.Push();
						Core.matrix.Scale(atmosphere.skybox.stratosphere.fScale);
						Core.matrix.SetTransform();
						Core.shader.use(GLS_STRATOSPHERE);
						Core.shader.getUniform(atmosphere, GLS_STRATOSPHERE);
						atmosphere.skybox.stratosphere.draw();
					Core.matrix.Pop();
				}

				if(bTroposphere) {
					Core.matrix.Push();
						Core.matrix.Scale(atmosphere.skybox.troposphere.fScale);
						Core.matrix.SetTransform();
						Core.shader.use(GLS_TROPOSPHERE);
						Core.shader.getUniform(atmosphere, GLS_TROPOSPHERE);
						atmosphere.skybox.troposphere.draw();
					Core.matrix.Pop();
				}
			Core.matrix.Pop();

			// Underwater flora must be before the water
			if (atmosphere.uwflora.bEnable) {
				if ((bWater[0]==true && bWater[1]==true) || (bWater[0]==false && bWater[1]==false)) {
					if(!atmosphere.uwflora.bFail) {
						Core.shader.use(GLS_UWFLORA);
						Core.shader.getUniform(atmosphere, GLS_UWFLORA);
						atmosphere.uwflora.draw();
					}
				}
			}

			if(atmosphere.water.bEnable) {
				gameVars->timer.pTimer.start("runVoid - Water");
				if(bWater[0]==true && bWater[1]==true) {	// If we are not in a Reflect/Refract pass (or water just disabled)
					Core.matrix.Push();
					Core.matrix.Apply(atmosphere.water.mTransform);
					Core.matrix.SetTransform();
					Core.shader.use(GLS_DIRECTIONAL_WATER);
					Core.shader.getUniform(atmosphere, GLS_DIRECTIONAL_WATER);
					atmosphere.water.draw();
					Core.matrix.Pop();
				}
				gameVars->timer.pTimer.stop("runVoid - Water");
			}

			// Things to ignore when doing water passes
			if (bDrawFlora) {
				if (atmosphere.flora.bEnable) {
					Core.shader.use(GLS_FLORA);
					Core.shader.getUniform(atmosphere, GLS_FLORA);
					atmosphere.flora.draw();
				}

				if (atmosphere.grass.bEnable) {
					uint uiShader;
					if(atmosphere.grass.bLine) uiShader=GLS_GRASS_LINE;
					else uiShader=GLS_GRASS_TRI;
					Core.shader.use(uiShader);
					Core.shader.getUniform(atmosphere, uiShader);
					atmosphere.grass.draw();
				}
			}

			if (bDrawWeather) {
				if (atmosphere.snow.bEnable) {
					Core.shader.use(GLS_SNOW2);
					Core.shader.getUniform(atmosphere, GLS_SNOW2);
					atmosphere.snow.draw();
				}

				if (atmosphere.hail.bEnable) {
					Core.shader.use(GLS_HAIL);
					Core.shader.getUniform(atmosphere, GLS_HAIL);
					atmosphere.hail.draw();
				}

				if (atmosphere.rain.bEnable) {
					Core.shader.use(GLS_RAIN);
					Core.shader.getUniform(atmosphere, GLS_RAIN);
					atmosphere.rain.draw();
				}
			}

			if (bDrawOther) {
				//if(!gameVars->player.sheet.init.bActive) player.draw();
				// TODO: Add Debug to control drawing this
				//			player.drawCohorts();
				if(gameVars->player.sheet.cohort.iSelected != -1) player.draw();
				//npc.draw(atmosphere, *gameVars->player.sheet.cohort.sheet[0], gameVars->player.sheet, false);
				//npc.draw(atmosphere, *gameVars->player.sheet.cohort.sheet[0], false);

				// Draw animations
				gameSys.animationSys.drawWorld();
			}
		Core.matrix.Pop();
	}
}

void _TheVoid::GetInput() {
	if (gameVars->debug.lag) printf("PUMP EVENTS\n");
	//Event capturing
	SDL_PumpEvents();

	if (gameVars->debug.lag) printf("GET MOUSE STATE\n");
	//Get relative mouse movement
	SDL_GetMouseState(&gameVars->controls.mouse.x, &gameVars->controls.mouse.y);

	//Is mouse control enabled?
	if (gameVars->controls.mouse.bEnable) {
		gameVars->controls.mouse.relX=gameVars->controls.mouse.x-gameVars->screen.halfW;
		gameVars->controls.mouse.relY=gameVars->controls.mouse.y-gameVars->screen.halfH;
		if (gameVars->debug.mouse) printf("\nMouse: (%i, %i)", gameVars->controls.mouse.x-gameVars->screen.halfW, gameVars->controls.mouse.y-gameVars->screen.halfH);

//		SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
//		if (gameVars->controls.mouse.lock) SDL_WarpMouse(gameVars->screen.halfW, gameVars->screen.halfH);
//		SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);

		if (gameVars->debug.lag) printf("SHOW/HIDE CURSOR\n");
		if (gameVars->controls.mouse.hide) SDL_ShowCursor(SDL_DISABLE);
		else SDL_ShowCursor(SDL_ENABLE);
	}
	else SDL_ShowCursor(SDL_ENABLE);

	//gameVars->controls.keyboard.event = SDL_GetKeyState(NULL);
	keyboard.event = SDL_GetKeyState(NULL);

	//if(SDL_GetMouseState(&gameVars->controls.mouse.x, &gameVars->controls.mouse.y)&SDL_BUTTON(1)) gameVars->controls.mouse.button.check[0]=true;
	//else gameVars->controls.mouse.button.check[0]=false;
	//gameSys.mouseSys.checkButton(gameVars, 0);

	//Left Mouse button
	if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(1)) gameVars->controls.mouse.button.check[0]=true;
	else gameVars->controls.mouse.button.check[0]=false;

	//Right Mouse button
	if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(3)) gameVars->controls.mouse.button.check[2]=true;
	else gameVars->controls.mouse.button.check[2]=false;

	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch(event.type) {
			case SDL_MOUSEBUTTONDOWN:
				if ( event.button.button == SDL_BUTTON_WHEELUP )
				{
						//cout << "Mousewheel Up!" << endl;
						DEBUG_3PDISTANCE-=100.0f;
						if (DEBUG_3PDISTANCE<0) {
							DEBUG_3PDISTANCE=0;
							DEBUG_3PENABLE = false;
						}
				}
				if ( event.button.button == SDL_BUTTON_WHEELDOWN )
				{
						//cout << "Mousewheel Down!" << endl;
						DEBUG_3PDISTANCE+=100.0f;
						if (DEBUG_3PDISTANCE==0 || DEBUG_3PENABLE==false) {
							DEBUG_3PENABLE=true;
						}
				}
		}
	}

//	if(SDL_GetMouseState(&gameVars->controls.mouse.x, &gameVars->controls.mouse.y)&SDL_BUTTON(4)) gameVars->controls.mouse.button.check[4]=true;
//	else gameVars->controls.mouse.button.check[4]=false;
//	gameSys.mouseSys.checkButton(4);
//
//	if(SDL_GetMouseState(&gameVars->controls.mouse.x, &gameVars->controls.mouse.y)&SDL_BUTTON(5)) gameVars->controls.mouse.button.check[5]=true;
//	else gameVars->controls.mouse.button.check[5]=false;
//	gameSys.mouseSys.checkButton(5);

	if (gameVars->debug.lag) printf("EXECUTE INPUT COMMANDS\n");
	//Execute input commands
	//gameSys.keySys.repeat(gameVars->controls.keyboard.event);
	keyboard.update();
	ProcessInput();
}

void _TheVoid::ProcessInput() {
	if (keyboard.bKey[SDLK_ESCAPE]) {
		//gameVars->state.quit=true;
		gameVars->state.admin=true;
		SDL_ShowCursor(SDL_ENABLE);
	}

	if (keyboard.bKey[SDLK_DELETE]) {
			npc.reload();
	}

	if (keyboard.bKey[SDLK_PAGEUP]) {
		gameVars->controls.moveSpeed += 0.05;

		cout << "moveSpeed = " << gameVars->controls.moveSpeed << endl;
	}

	if (keyboard.bKey[SDLK_PAGEDOWN]) {
		gameVars->controls.moveSpeed -= 0.05;
		if(gameVars->controls.moveSpeed < 0.05) gameVars->controls.moveSpeed = 0.05;

		cout << "moveSpeed = " << gameVars->controls.moveSpeed << endl;
	}

	if (keyboard.bKey[SDLK_TAB]) {
		ToggleMouse();
	}

	if (keyboard.bKey[gameVars->controls.key.open_journal]) {
			//SDL_ShowCursor(SDL_ENABLE);
			gameVars->state.book=S_JOURNAL;
	}

	if (keyboard.bKey[gameVars->controls.key.open_intent]) {
		//SDL_ShowCursor(SDL_ENABLE);
		gameVars->state.menu=true;
		gameVars->menu.bOperations=false;
		gameVars->menu.bIntent=true;
		gameVars->menu.bStatus=true;
		gameVars->menu.bActionIcon=true;
		ToggleMouse(true);
	}

	if (keyboard.bKey[gameVars->controls.key.open_menu]) {
		//SDL_ShowCursor(SDL_ENABLE);
		gameVars->state.menu=true;
		gameVars->menu.bOperations=true;
		gameVars->menu.bIntent=false;
		gameVars->menu.bStatus=false;
		gameVars->menu.bActionIcon=true;
		ToggleMouse(true);
	}

	if (keyboard.bKey[gameVars->controls.key.activate]) {
		e2d.execute();
	}

	if (keyboard.bKey[gameVars->controls.key.sneak]) {
		gameVars->controls.modSpeed=0.40;
	}

	if (keyboard.bKey[gameVars->controls.key.run]) {
		gameVars->controls.modSpeed=10.00;
	}

	if (!keyboard.bKey[gameVars->controls.key.run] && !keyboard.bKey[gameVars->controls.key.sneak]) {
		gameVars->controls.modSpeed=1;
	}

	//PLAYER MOVEMENT
	// TODO: Is this needed? Seems this would clear needed data.
	//gameVars->player.active->transform.last[0] = 0.0f;
	//gameVars->player.active->transform.last[1] = 0.0f;
	//gameVars->player.active->transform.last[2] = 0.0f;

	if (keyboard.bKey[gameVars->controls.key.strafe_left]){
		int iAirControl = 1;
		//if (gameVars->player.active->transform.pos[1] < gameVars->transform.groundHeight) iAirControl = 2;
		float fNewX = ((float)cos( gameVars->player.active->transform.rot[1] ) * ((gameVars->controls.moveSpeed / iAirControl)*gameVars->controls.modSpeed))*gameVars->controls.modStance*gameVars->controls.modClimb;
		float fNewZ = ((float)sin( gameVars->player.active->transform.rot[1] ) * ((gameVars->controls.moveSpeed / iAirControl)*gameVars->controls.modSpeed))*gameVars->controls.modStance*gameVars->controls.modClimb;
		if (!gameVars->controls.fly) {
			float fTempPosX = gameVars->player.active->transform.pos[0];
			float fTempPosZ = gameVars->player.active->transform.pos[2];
			gameVars->player.active->transform.last[0] += fNewX;
			gameVars->player.active->transform.last[2] += fNewZ;
			gameVars->player.active->transform.pos[0]  += fNewX;
			gameVars->player.active->transform.pos[2]  += fNewZ;
			/*
			if (!GetHeight()) {
				gameVars->player.active->transform.pos[0]=fTempPosX;
				gameVars->player.active->transform.pos[2]=fTempPosZ;
			}
			*/
		}
		else {
			float fTempPosX = gameVars->player.active->transform.pos[0];
			float fTempPosZ = gameVars->player.active->transform.pos[2];
			gameVars->player.active->transform.last[0] += fNewX;
			gameVars->player.active->transform.last[2] += fNewZ;
			gameVars->player.active->transform.pos[0]  += fNewX;
			gameVars->player.active->transform.pos[2]  += fNewZ;

			//GetHeight();
		}
	}
	if (keyboard.bKey[gameVars->controls.key.strafe_right]){
		int iAirControl = 1;
		//if (gameVars->player.active->transform.pos[1] < gameVars->transform.groundHeight) iAirControl = 2;
		float fNewX = ((float)cos( gameVars->player.active->transform.rot[1] ) * ((gameVars->controls.moveSpeed / iAirControl)*gameVars->controls.modSpeed))*gameVars->controls.modStance*gameVars->controls.modClimb;
		float fNewZ = ((float)sin( gameVars->player.active->transform.rot[1] ) * ((gameVars->controls.moveSpeed / iAirControl)*gameVars->controls.modSpeed))*gameVars->controls.modStance*gameVars->controls.modClimb;
		if (!gameVars->controls.fly) {
			float fTempPosX = gameVars->player.active->transform.pos[0];
			float fTempPosZ = gameVars->player.active->transform.pos[2];
			gameVars->player.active->transform.last[0] -= fNewX;
			gameVars->player.active->transform.last[2] -= fNewZ;
			gameVars->player.active->transform.pos[0]  -= fNewX;
			gameVars->player.active->transform.pos[2]  -= fNewZ;

			/*
			if (!GetHeight()) {
				gameVars->player.active->transform.pos[0]=fTempPosX;
				gameVars->player.active->transform.pos[2]=fTempPosZ;
			}
			*/
		}
		else {
			float fTempPosX = gameVars->player.active->transform.pos[0];
			float fTempPosZ = gameVars->player.active->transform.pos[2];
			gameVars->player.active->transform.last[0] -= fNewX;
			gameVars->player.active->transform.last[2] -= fNewZ;
			gameVars->player.active->transform.pos[0]  -= fNewX;
			gameVars->player.active->transform.pos[2]  -= fNewZ;

			//GetHeight();
		}
	}

	if (keyboard.bKey[gameVars->controls.key.move_forward]) {
		int iAirControl = 1;
		//if (gameVars->player.active->transform.pos[1] < gameVars->transform.groundHeight) iAirControl = 2;
		float fNewX = ((float)sin( gameVars->player.active->transform.rot[1] ) * ((gameVars->controls.moveSpeed / iAirControl)*gameVars->controls.modSpeed))*gameVars->controls.modStance*gameVars->controls.modClimb;
		float fNewZ = ((float)cos( gameVars->player.active->transform.rot[1] ) * ((gameVars->controls.moveSpeed / iAirControl)*gameVars->controls.modSpeed))*gameVars->controls.modStance*gameVars->controls.modClimb;
		if (!gameVars->controls.fly) {
			float fTempPosX = gameVars->player.active->transform.pos[0];
			float fTempPosZ = gameVars->player.active->transform.pos[2];

			gameVars->player.active->transform.last[0] -= fNewX;;
			gameVars->player.active->transform.last[2] += fNewZ;;
			gameVars->player.active->transform.pos[0]  -= fNewX;
			gameVars->player.active->transform.pos[2]  += fNewZ;

			/*
			if (!GetHeight()) {
				gameVars->player.active->transform.pos[0]=fTempPosX;
				gameVars->player.active->transform.pos[2]=fTempPosZ;
			}
			*/
		}
		else {
			float fTempPosX = gameVars->player.active->transform.pos[0];
			float fTempPosZ = gameVars->player.active->transform.pos[2];
			gameVars->player.active->transform.last[0] -= fNewX;
			gameVars->player.active->transform.last[2] += fNewZ;
			gameVars->player.active->transform.pos[0]  -= fNewX;
			gameVars->player.active->transform.pos[2]  += fNewZ;

			//GetHeight();
		}
	}
	if (keyboard.bKey[gameVars->controls.key.move_back]) {
		int iAirControl = 1;
		//if (gameVars->player.active->transform.pos[1] < gameVars->transform.groundHeight) iAirControl = 2;
		float fNewX = ((float)sin( gameVars->player.active->transform.rot[1] ) * ((gameVars->controls.moveSpeed / iAirControl)*gameVars->controls.modSpeed))*gameVars->controls.modStance*gameVars->controls.modClimb;
		float fNewZ = ((float)cos( gameVars->player.active->transform.rot[1] ) * ((gameVars->controls.moveSpeed / iAirControl)*gameVars->controls.modSpeed))*gameVars->controls.modStance*gameVars->controls.modClimb;
		if (!gameVars->controls.fly) {
			float fTempPosX = gameVars->player.active->transform.pos[0];
			float fTempPosZ = gameVars->player.active->transform.pos[2];
			gameVars->player.active->transform.last[0] += fNewX;
			gameVars->player.active->transform.last[2] -= fNewZ;
			gameVars->player.active->transform.pos[0]  += fNewX;
			gameVars->player.active->transform.pos[2]  -= fNewZ;

			/*
			if (!GetHeight()) {
				gameVars->player.active->transform.pos[0]=fTempPosX;
				gameVars->player.active->transform.pos[2]=fTempPosZ;
			}
			*/
		}
		else {
			float fTempPosX = gameVars->player.active->transform.pos[0];
			float fTempPosZ = gameVars->player.active->transform.pos[2];
			gameVars->player.active->transform.last[0] += fNewX;
			gameVars->player.active->transform.last[2] -= fNewZ;
			gameVars->player.active->transform.pos[0]  += fNewX;
			gameVars->player.active->transform.pos[2]  -= fNewZ;

			//GetHeight();
		}
	}

	if (keyboard.bKey[gameVars->controls.key.change_stance]) {
		if (gameVars->player.active->status.move.iStance == GAME::MENU.MOVE.STANCE.STAND)		gameVars->player.active->status.move.iStance = GAME::MENU.MOVE.STANCE.KNEEL;
		else if (gameVars->player.active->status.move.iStance == GAME::MENU.MOVE.STANCE.KNEEL)	gameVars->player.active->status.move.iStance = GAME::MENU.MOVE.STANCE.PRONE;
		else if (gameVars->player.active->status.move.iStance == GAME::MENU.MOVE.STANCE.PRONE)	gameVars->player.active->status.move.iStance = GAME::MENU.MOVE.STANCE.STAND;

		/*
		switch (gameVars->player.active->status.move.iStance) {
			case G_STAND:
				cout<<"Stand"<<endl;
				//gameVars->transform.currentHeight = gameVars->transform.eyeHeight;
				gameVars->player.active->transform.currentHeight = gameVars->player.active->transform.eyeHeight;
				gameVars->controls.modStance = 1;
				break;
			case G_CROUCH:
				cout<<"Crouch"<<endl;
				//gameVars->transform.currentHeight = gameVars->transform.eyeHeight*gameVars->transform.fCrouchDiff;
				gameVars->player.active->transform.currentHeight = gameVars->player.active->transform.eyeHeight/2;
				gameVars->controls.modStance = gameVars->transform.fCrouchDiff;
				break;
			case G_PRONE:
				cout<<"Prone"<<endl;
				//gameVars->transform.currentHeight = gameVars->transform.eyeHeight*gameVars->transform.fProneDiff;
				gameVars->player.active->transform.currentHeight = 1;
				gameVars->controls.modStance = gameVars->transform.fProneDiff;
				break;
		}
		*/
	}

	if (keyboard.bKey[gameVars->controls.key.move_up]) {
		if (gameVars->controls.fly) gameVars->player.active->transform.pos[1]-=gameVars->controls.moveSpeed*gameVars->controls.modSpeed*4;
	}
	if (keyboard.bKey[gameVars->controls.key.move_down]) {
		if (gameVars->controls.fly) gameVars->player.active->transform.pos[1]+=gameVars->controls.moveSpeed*gameVars->controls.modSpeed*4;
	}


	if (keyboard.bKey[gameVars->controls.key.jump]) {
		//if (gameVars->player.active->transform.pos[1] == gameVars->transform.groundHeight) {
		//	gameVars->player.active->transform.pos[1]-=gameVars->controls.moveSpeed*gameVars->controls.modSpeed;
		//	gameVars->controls.jump = true;
		//}
	}

	if (keyboard.bKey[SDLK_BACKQUOTE]) {
		gameVars->state.console=true;
	}

	if (keyboard.bKey[SDLK_EQUALS]) {
		if (DEBUG_index1<DEBUG_max1) {
			DEBUG_index1+=DEBUG_delta1;
		}
		//atmosphere.sun.fShiny += 0.1;
		//cout << "Sun: " << atmosphere.sun.fShiny << endl;
		//if (atmosphere.sun.fShiny > 20.0f) atmosphere.sun.fShiny=20.00f;
	}

	if (keyboard.bKey[SDLK_MINUS]) {
		if (DEBUG_index1>DEBUG_min1) {
			DEBUG_index1-=DEBUG_delta1;
		}
		//atmosphere.sun.fShiny -= 0.1;
		//cout << "Sun: " << atmosphere.sun.fShiny << endl;
		//if (atmosphere.sun.fShiny < -20.0f) atmosphere.sun.fShiny=-20.00f;
	}

	if (keyboard.bKey[SDLK_1]) {
		atmosphere.sun.fLightAltitude -= 0.1f*gameVars->controls.modSpeed;
		//atmosphere.sun.vPosition[1] -= 0.1f*gameVars->controls.modSpeed;
		//Core.shader.vEyeLight[0]-=10;
	}

	if (keyboard.bKey[SDLK_2]) {
		atmosphere.sun.fLightAltitude += 0.1f*gameVars->controls.modSpeed;
		//atmosphere.sun.vPosition[1] += 0.1f*gameVars->controls.modSpeed;
		//Core.shader.vEyeLight[0]+=10;
	}

	if (keyboard.bKey[SDLK_3]) {
		//Core.shader.vEyeLight[1]-=10;
	}

	if (keyboard.bKey[SDLK_4]) {
		//Core.shader.vEyeLight[1]+=10;
	}

	if (keyboard.bKey[SDLK_5]) {
		DEBUG_WATER1 = false;
		DEBUG_WATER2 = false;
	}


	if (keyboard.bKey[SDLK_6]) {
		DEBUG_WATER1 = true;
		DEBUG_WATER2 = true;
	}

	if (keyboard.bKey[SDLK_7]) {
		DEBUG_WATER1 = false;
		DEBUG_WATER2 = true;
	}

	if (keyboard.bKey[SDLK_8]) {
		DEBUG_WATER1 = true;
		DEBUG_WATER2 = false;
	}

	if (keyboard.bKey[SDLK_9]) {
//		if (DEBUG_index2>DEBUG_min2) {
//			DEBUG_index2-=DEBUG_delta2;
//		}
		//atmosphere.moon.fShiny -= 0.1;
		//cout << "Moon: " << atmosphere.moon.fShiny << endl;
	}

	if (keyboard.bKey[SDLK_0]) {
//		if (DEBUG_index2<DEBUG_max2) {
//			DEBUG_index2+=DEBUG_delta2;
//		}
		//atmosphere.moon.fShiny += 0.1;
		//cout << "Moon: " << atmosphere.moon.fShiny << endl;
		gameVars->timer.pTimer.ResetMax();
	}

	if (keyboard.bKey[SDLK_F1]) {
		gameVars->state.admin=true;
		//atmosphere.snow.calc();
		//atmosphere.snow.update();
	}
	if (keyboard.bKey[SDLK_F2]) {

		gameSys.animationSys.startAnimation(32.0f, 32.0f, gameVars->player.active->transform.pos, npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[0].transform.pos, DEBUG_index1, 1, DEBUG_index2);
		//gameSys.animationSys.startAnimation(32.0f, 32.0f, gameVars->player.active->transform.pos, npc.data[4][4].sheet[0].transform.pos, 1, 2, 80);

		/*
		 * TOGGLE VOID MODES
		 * TODO: BROKEN! Need to fix loading voids
		 */
//		cout << "!!! TOGGLING CURRENT VOID !!!" << endl;
//		if(iCurrentVoid==EARTH) {
//			Prime.load();
//		}
//		else if(iCurrentVoid==PRIME) {
//			Earth.load();
//		}
	}
	if (keyboard.bKey[SDLK_F3]) {
		gameSys.animationSys.startAnimation(32.0f, 32.0f, gameVars->player.active->transform.pos, npc.data[gameVars->screen.iGridOffset][gameVars->screen.iGridOffset].sheet[0].transform.pos, DEBUG_index1, 10, DEBUG_index2);
		//gameSys.animationSys.startAnimation(32.0f, 32.0f, gameVars->player.active->transform.pos, npc.data[4][4].sheet[1].transform.pos, 2, 2, 80);
		// TODO: Broken
		//Toggle(gameVars->state.dungeon);
	}
	if (keyboard.bKey[SDLK_F4]) {
		//gameVars->state.battle = true;
		Toggle(gameVars->state.battle);
		gameSys.audioSys.stopMusic();
		//gameSys.audioSys.fadeOutMusic(gameSys.audioSys.MUSIC_WORLDEXPLORE);
		gameVars->battle.newBattle = true;
	}
	if (keyboard.bKey[SDLK_F5]) {
		//gameVars->screen.clear = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
		glLineWidth(gameVars->screen.fLineWidth);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		gameVars->screen.ePolyMode = PM_FILL;
	}
	if (keyboard.bKey[SDLK_F6]) {
		//gameVars->screen.clear = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
		glLineWidth(1.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		gameVars->screen.ePolyMode = PM_LINE;
	}

	if (!gameVars->screen.ePolyMode == PM_LINE) {
		//if (keyboard.bKey[SDLK_EQUALS])	{ gameVars->screen.fLineWidth+=0.5; glLineWidth(gameVars->screen.fLineWidth); }
		//if (keyboard.bKey[SDLK_MINUS])		{ gameVars->screen.fLineWidth-=0.5; glLineWidth(gameVars->screen.fLineWidth); }
	}

	if (keyboard.bKey[SDLK_F7]) {
		//DEBUG_POLYGON_POINT = true;
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		gameVars->screen.ePolyMode = PM_POINT;
		//npc.calc();
	}
	if (keyboard.bKey[SDLK_F8]) {
		//gameVars->controls.mouse.bEnable
		if (gameVars->controls.mouse.bEnable) {
			gameVars->controls.mouse.bEnable = false;
		}
		else {
			gameVars->controls.mouse.bEnable = true;
		}





		/*
		if (gameVars->screen.blur.enable) {
			if (gameVars->debug.keyboard) printf("BLUR OFF\n");
			gameVars->screen.blur.enable=false;
		}
		else {
			if (gameVars->debug.keyboard) printf("BLUR ON\n");
			gameVars->screen.blur.enable=true;
		}
		*/
	}
	if (keyboard.bKey[SDLK_F9]) {
		if (gameVars->controls.fly) {
			if (gameVars->debug.keyboard) printf("FLY MODE OFF\n");
			gameVars->controls.fly=false;
		}
		else {
			if (gameVars->debug.keyboard) printf("FLY MODE ON\n");
			gameVars->controls.fly=true;
		}
	}

	if (keyboard.bKey[SDLK_F10]) {
		if (gameVars->controls.mouse.lock) {
			if (gameVars->debug.keyboard) printf("MOUSE UNLOCKED\n");
			gameVars->controls.mouse.lock=false;
		}
		else {
			if (gameVars->debug.keyboard) printf("MOUSE LOCKED\n");
			gameVars->controls.mouse.lock=true;
		}
	}

	if (keyboard.bKey[SDLK_F11]) {
		if (gameVars->controls.mouse.hide) {
			if (gameVars->debug.keyboard) printf("MOUSE SHOWN\n");
			gameVars->controls.mouse.hide=false;
		}
		else {
			if (gameVars->debug.keyboard) printf("MOUSE HIDDEN\n");
			gameVars->controls.mouse.hide=true;
		}
	}

	if (keyboard.bKey[SDLK_F12]) SDL_WM_ToggleFullScreen(Core.GlInit.screen);

	//Simulate mouse with keys
	if (!gameVars->controls.mouse.bEnable) {
		if (keyboard.bKey[gameVars->controls.key.mouse_left]) {
			gameVars->controls.mouse.relX=-1;
		}
		else if (keyboard.bKey[gameVars->controls.key.mouse_right]) {
			gameVars->controls.mouse.relX=1;
		}
		else gameVars->controls.mouse.relX=0;
		if (keyboard.bKey[gameVars->controls.key.mouse_up]) {
			gameVars->controls.mouse.relY=-1;
		}
		else if (keyboard.bKey[gameVars->controls.key.mouse_down]) {
			gameVars->controls.mouse.relY=1;
		}
		else gameVars->controls.mouse.relY=0;
	}

	if (gameVars->controls.mouse.relX<-gameVars->controls.mouse.deadX) {
		gameVars->player.active->transform.rot[1]+=(gameVars->controls.mouse.relX)*gameVars->controls.mouse.sensX;
		if (M_RadToDeg(gameVars->player.active->transform.rot[1])>360) gameVars->player.active->transform.rot[1] = gameVars->player.active->transform.rot[1] - M_DegToRad(360);
		if (M_RadToDeg(gameVars->player.active->transform.rot[1]) < 0) gameVars->player.active->transform.rot[1] = gameVars->player.active->transform.rot[1] = M_DegToRad(360) + gameVars->player.active->transform.rot[1];
		gameSys.mouseSys.sdlWarpMouse(gameVars->screen.halfW, gameVars->screen.halfH);
		if (gameVars->debug.mouse) printf("Look LEFT\n");
	}
	if (gameVars->controls.mouse.relX>gameVars->controls.mouse.deadX) {
		gameVars->player.active->transform.rot[1]+=(gameVars->controls.mouse.relX)*gameVars->controls.mouse.sensX;
		if (M_RadToDeg(gameVars->player.active->transform.rot[1])>360) gameVars->player.active->transform.rot[1] = gameVars->player.active->transform.rot[1] - M_DegToRad(360);
		if (M_RadToDeg(gameVars->player.active->transform.rot[1]) < 0) gameVars->player.active->transform.rot[1] = gameVars->player.active->transform.rot[1] = M_DegToRad(360) + gameVars->player.active->transform.rot[1];
		gameSys.mouseSys.sdlWarpMouse(gameVars->screen.halfW, gameVars->screen.halfH);
		if (gameVars->debug.mouse) printf("Look RIGHT\n");
	}
	if (gameVars->controls.mouse.relY<-gameVars->controls.mouse.deadY) {
		if(-gameVars->player.active->transform.rot[0] < M_DegToRad(90) ) {
			gameVars->player.active->transform.rot[0]+=(gameVars->controls.mouse.relY)*gameVars->controls.mouse.sensY;
		} else {
			gameVars->player.active->transform.rot[0] = M_DegToRad(-90);
		}
		gameSys.mouseSys.sdlWarpMouse(gameVars->screen.halfW, gameVars->screen.halfH);
		if (gameVars->debug.mouse) printf("Look UP\n");
	}
	if (gameVars->controls.mouse.relY>gameVars->controls.mouse.deadY) {
		if(gameVars->player.active->transform.rot[0] < M_DegToRad(90) ) {
			gameVars->player.active->transform.rot[0]+=(gameVars->controls.mouse.relY)*gameVars->controls.mouse.sensY;
		} else {
			gameVars->player.active->transform.rot[0] = M_DegToRad(90);
		}
		gameSys.mouseSys.sdlWarpMouse(gameVars->screen.halfW, gameVars->screen.halfH);
		if (gameVars->debug.mouse) printf("Look DOWN\n");
	}
}
#endif /* RUNVOID_HPP_ */
