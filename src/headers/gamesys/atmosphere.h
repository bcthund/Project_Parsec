/*
 * SpriteSys.h
 *
 *  Created on: Jun 7, 2015
 *      Author: bcthund
 */

#ifndef ATMOSPHERE_H_
#define ATMOSPHERE_H_

/*
 * This is the primary Atmosphere class that handles many different things that
 *   I have deemed releated to the atmosphere. This includes the physical
 *   layers of the atmosphere, the effects of those layers on the world,
 *   and the generated parts of the world including the flora and grass. The
 *   Sun and Moon are also included here.
 *
 * There are bEnable booleans for the Rain, Snow, Hail, Grass, and Flora. For
 *   the grass and flora it simply turns the rendering and updating on and
 *   off. However the Rain, Snow, and Hail overrides the default cloud
 *   texture for this atmosphere instance. Because each can have their
 *   own texture setting there is an order of precedence:
 *     1) Snow
 *     2) Hail
 *     3) Rain
 *
 *
 *
 */

/*
 * TODO:
 * 	Add additional layers that can be added/removed
 * 		- Particle effects?
 * 		- Fog
 * 		- ???
 *
 * 	[ ] Remove Variable Argument list
 */

#include <iostream>
#include <sstream>

#include "../core/core_functions.h"
//#include "../core/ply_loader.h"
#include "./atmosphere/satellite.h"
#include "./atmosphere/flora.h"
#include "gl4_5/glcorearb.h"

namespace Core {
	namespace Sys {
//		struct Atmosphere_Data {
//			struct _Satellite {
//				Vector3f	vPosition;			// Rectangular coordinates of light
//				Vector4f	vAmbientBase;		// Ambient light color
//				Vector4f	vDiffuseBase;		// Diffuse light color
//				Vector4f	vSpecularBase;		// Specular light color
//				GLfloat		fShinyBase;			// Current shininess used by shader
//												// This is an innaccurate use of shininess
//												// but we will use it for now.
//				std::string sImage;				// Texture to use for light sprite (sun in this case)
//				std::string sFlare[9];			// Lens flare textures
//				float		fScale;				// The scale of the sprite, original size in-game is 32x32 pixels
//				float		fLightDistance;		// The distance of the light from the player
//				float		fLightAzimuth;		// The angle from zero degrees along the horizon, south is zero degrees
//				float		fLightAltitude;		// The angle above the horizon (calc modified from standard spherical to measure up instead of down)
//				float		fLightZenith;		// NOT IMPLEMENTED, Tilt of the light path, so the sun doesn't pass at 90 degrees above player
//			};
//
//			/*
//			 * We may not need any of this except the scale value
//			 *  so we should remove the extra data.
//			 */
//			struct _SKYBOX {
//				struct _TROPOSPHERE {
//					Vector4f	vAmbientBase;
//					Vector4f	vDiffuseBase;
//					Vector4f	vSpecularBase;
//					GLfloat		fShiny;
//					std::string sImage;
//					float		fScale;
//				} troposphere;
//
//				struct _STRATOSPHERE {
//					Vector4f	vAmbientBase;
//					Vector4f	vDiffuseBase;
//					Vector4f	vSpecularBase;
//					GLfloat		fShiny;
//					std::string sImage;
//					float		fScale;
//				} stratosphere;
//
//				struct _MESOSPHERE {
//					Vector4f	vAmbientBase;
//					Vector4f	vDiffuseBase;
//					Vector4f	vSpecularBase;
//					GLfloat		fShiny;
//					std::string sImage;
//					float		fScale;
//				} mesosphere;
//
//				struct _THERMOSPHERE {
//					Vector4f	vAmbientBase;
//					Vector4f	vDiffuseBase;
//					Vector4f	vSpecularBase;
//					GLfloat		fShiny;
//					std::string sImage;
//					float		fScale;
//				} thermosphere;
//
//				struct _EXOSPHERE {
//					Vector4f	vAmbientBase;
//					Vector4f	vDiffuseBase;
//					Vector4f	vSpecularBase;
//					GLfloat		fShiny;
//					std::string sImage;
//					float		fScale;
//				} exosphere;
//			} skybox;
//
//			struct _SNOW {
//				Vector4f * vVert;		// Modified over time to create falling effect, and turning effects, we also need distance to allow layering
//				Vector4f vColor;		// Allows for customization
//				std::string sImage;		// Texture
//				float fScale;			// Object scale adjustment
//			} snow;
//
//		};

		class Atmosphere {
			private:
				bool calc(uint mode);
				bool calc(uint mode, bool bUpdate);
				//void update(uint mode);
				void start(int x, int y, float w, float h, std::string sTex, Vector4f fontColor, bool textOffset);
				void stop();
				//std::string	sDirectory;					// Directory of images
				//char * cFilename;						// Binary list of images with id's
				//int			iRecordSize;				// Record size for each binary entry
				static const int	NUM_TEXTURES = 32;	//Number of textures available
				//VAO	vaoPly,
				//	vaoParaboloid;

				//VAO skybox,
					//sun,
					//moon;
					//rain,
					//snow;

			protected:

			public:
				/*
				 * This allows us to setup the atmosphere externally
				 * by using the Atmosphere_Data struct
				 */
				bool init();
				bool load();
				//bool init(Atmosphere_Data data);
				bool calc();
				void update(uint mode);
				void draw(uint mode, ...);

				uint AddSatellite();
				_Satellite	*	satellite;
				//_Flora		*	flora;
				_Particles	* particlesOld;

				/*
				 * SKYBOX draws all atmospheric box layers
				 *
				 * The position ordering is as follows:
				 *  RAIN
				 *  SNOW
				 *  FOG
				 *  TROPOSHERE   = Terrain
				 *  STRATOSPHERE = Clouds
				 *  MESOSPHERE   = Unused (Meteor layer)
				 *  THERMOSPHERE = Sky Tinting (Real Life: Aurora Layer)
				 *  SUN
				 *  MOON
				 *  EXOSPHERE    = Space/Stars
				 */
				enum _MODES {	MODE_SKYBOX,
								MODE_TROPOSPHERE,
								MODE_STRATOSPHERE,
								MODE_MESOSPHERE,
								MODE_THERMOSPHERE,
								MODE_EXOSPHERE,
								MODE_SATELLITE,
								MODE_FLARES,
								//MODE_FOG,
								//MODE_GROUNDFOG,
								//MODE_RAIN,
								//MODE_HAIL,
								//MODE_SNOW,
								MODE_FLORA,
								//MODE_UWFLORA,
								//MODE_GRASS,
								//MODE_WATER,
								MODE_LAST };

				struct _SKYBOX {
					Atmosphere	&parent;
					Texture		tex;

					struct _TROPOSPHERE {
						_SKYBOX		&parent;
						Vector4f	vAmbientBase;
						Vector4f	vDiffuseBase;
						Vector4f	vSpecularBase;
						Vector4f	vAmbientColor;
						Vector4f	vDiffuseColor;
						Vector4f	vSpecularColor;
						GLfloat		fShiny;
						std::string sImage;
						float		fScale;
						VAO			vao;

						void draw()   { parent.parent.draw(MODE_TROPOSPHERE); }
						void update() { parent.parent.update(MODE_TROPOSPHERE); }

						_TROPOSPHERE(_SKYBOX &f) : parent(f), fShiny(0), fScale(0) { };
					} troposphere;

					struct _STRATOSPHERE {
						_SKYBOX		&parent;
						std::string sCloud;		// Cloud texture
						std::string sBump;		// Cloud bumpmap
						Vector4f	vAmbientBase;
						Vector4f	vDiffuseBase;
						Vector4f	vSpecularBase;
						Vector4f	vAmbientColor;
						Vector4f	vDiffuseColor;
						Vector4f	vSpecularColor;
						GLfloat		fShiny;
						std::string sImage;
						float		fScale;
						VAO vao;

						void draw()   { parent.parent.draw(MODE_STRATOSPHERE); }
						void update() { parent.parent.update(MODE_STRATOSPHERE); }

						_STRATOSPHERE(_SKYBOX &f) : parent(f), fShiny(0), fScale(0) { };
					} stratosphere;

					struct _MESOSPHERE {
						_SKYBOX		&parent;
						Vector4f	vAmbientBase;
						Vector4f	vDiffuseBase;
						Vector4f	vSpecularBase;
						Vector4f	vAmbientColor;
						Vector4f	vDiffuseColor;
						Vector4f	vSpecularColor;
						GLfloat		fShiny;
						std::string sImage;
						float		fScale;
						VAO vao;

						void draw()   { parent.parent.draw(MODE_MESOSPHERE); }
						void update() { parent.parent.update(MODE_MESOSPHERE); }

						_MESOSPHERE(_SKYBOX &f) : parent(f), fShiny(0), fScale(0) { };
					} mesosphere;

					struct _THERMOSPHERE {
						_SKYBOX		&parent;
						Vector4f	vAmbientBase;
						Vector4f	vDiffuseBase;
						Vector4f	vSpecularBase;
						Vector4f	vAmbientColor;
						Vector4f	vDiffuseColor;
						Vector4f	vSpecularColor;
						GLfloat		fShiny;
						std::string sImage;
						float		fScale;
						float		fS;				// The alpha level for thermosphere, directly tied to sunrise/sunset texture
						float		fD;				// The mixing level for the daytime texture
						float		fRot;			// Rotation of the thermosphere to line up sunrise/sunset
						VAO vao;

						void draw()   { parent.parent.draw(MODE_THERMOSPHERE); }
						void update() { parent.parent.update(MODE_THERMOSPHERE); }

						_THERMOSPHERE(_SKYBOX &f) : parent(f), fShiny(0), fScale(0), fS(0), fD(0), fRot(0) { };
					} thermosphere;

					struct _EXOSPHERE {
						_SKYBOX		&parent;
						Vector4f	vAmbientBase;
						Vector4f	vDiffuseBase;
						Vector4f	vSpecularBase;
						Vector4f	vAmbientColor;
						Vector4f	vDiffuseColor;
						Vector4f	vSpecularColor;
						GLfloat		fShiny;
						std::string sImage;
						float		fScale;
						bool		bCubeMap;			// Use cubemap instead of spherical map (just changes ply loaded)
						VAO vao;

						void draw()   { parent.parent.draw(MODE_EXOSPHERE); }
						void update() { parent.parent.update(MODE_EXOSPHERE); }

						_EXOSPHERE(_SKYBOX &f) : parent(f), fShiny(0), fScale(0), bCubeMap(1) { };
					} exosphere;

					bool calc()   { return parent.calc(MODE_SKYBOX); }
					void draw()   { parent.draw(MODE_EXOSPHERE);   parent.draw(MODE_THERMOSPHERE);   parent.draw(MODE_MESOSPHERE);   parent.draw(MODE_STRATOSPHERE);   parent.draw(MODE_TROPOSPHERE); }
					void update() { parent.update(MODE_EXOSPHERE); parent.update(MODE_THERMOSPHERE); parent.update(MODE_MESOSPHERE); parent.update(MODE_STRATOSPHERE); parent.update(MODE_TROPOSPHERE); }

					_SKYBOX(Atmosphere &f) : parent(f), troposphere(*this), stratosphere(*this), mesosphere(*this), thermosphere(*this), exosphere(*this) { };
				} skybox;

				Atmosphere() :	skybox(*this) {
					Core::debug.log("Construct Atmosphere {\n");
					Core::debug.logIncreaseIndent();
					satellite = new _Satellite(*this);
					particlesOld = new _Particles(*this, gameVars->screen.fScale);
					Core::debug.logDecreaseIndent();
					Core::debug.log("}\n");
				}
				~Atmosphere() {
					Core::debug.log("Destroy Atmosphere {");
					if(satellite != nullptr) delete satellite;
					if(particlesOld != nullptr) delete particlesOld;
					Core::debug.print(" Done ", Core::debug().GREEN);
					Core::debug.print("}\n");
				}
		};

		/*
		 * Default data
		 */
		bool Atmosphere::init() {
			Core::debug.log("Init Atmosphere {");
//				if (gameVars->debug.load) printf("## LOAD O2D\n");
//				bool bReadResult;
//				MemBlock memBlock;
//				std::string loadFile;
//				std::stringstream *sStream = new std::stringstream;
//				sStream->str("");
//				*sStream << "./void/earth" << "/atmosphere.bin";
//				loadFile=sStream->str();
//				if (gameVars->debug.load) cout << " -Loading " << loadFile << "...";
//				//if (gameVars->debug.load) cout << gameVars->dir.o2d << iX << "-" << iZ << ".o2d" << std::endl;
//				bReadResult = readFile(loadFile, memBlock);		//Read the data file into memory
//				if (!bReadResult) {
					// Load Defaults!
					/*
					 * General Variables
					 */
					//iRecordSize = 32;
					//sDirectory = "./texture/atmosphere/";
					//cFilename = (char*)"atmosphere.bin";

					/*
					 * Atmospheric layers
					 */
					/*skybox.troposphere.fScale	= 5000;
					skybox.stratosphere.fScale	= skybox.troposphere.fScale+100;
					//skybox.mesosphere.fScale	= skybox.stratosphere.fScale+1000;
					skybox.mesosphere.fScale	= sqrt((skybox.stratosphere.fScale*skybox.stratosphere.fScale)+(skybox.stratosphere.fScale*skybox.stratosphere.fScale))+1000.0f;
					skybox.thermosphere.fScale	= skybox.mesosphere.fScale+2000;
					skybox.exosphere.fScale		= sqrt((skybox.thermosphere.fScale*skybox.thermosphere.fScale)+(skybox.thermosphere.fScale*skybox.thermosphere.fScale))+500.0f;
					*/
					//skybox.troposphere.fScale	= 9000;
					//skybox.stratosphere.fScale	= skybox.troposphere.fScale+100;		//Divide by 2 because the stratosphere has a model twice as big
					//skybox.mesosphere.fScale	= skybox.stratosphere.fScale+1000;
					//skybox.thermosphere.fScale	= skybox.mesosphere.fScale+1000;
					//skybox.exosphere.fScale		= skybox.thermosphere.fScale+1000;

					skybox.troposphere.fScale		= 500000;
					skybox.stratosphere.fScale		= skybox.troposphere.fScale;		//Divide by 2 because the stratosphere has a model twice as big
					skybox.mesosphere.fScale		= skybox.stratosphere.fScale;
					skybox.thermosphere.fScale		= skybox.mesosphere.fScale;
					skybox.exosphere.fScale			= skybox.thermosphere.fScale;

					skybox.exosphere.bCubeMap		= true;

					skybox.troposphere.sImage		= "mountain2.png";
					skybox.mesosphere.sImage		= "";
					skybox.thermosphere.sImage		= "thermo_00.png";
					skybox.exosphere.sImage			= "space_01.png";

					skybox.stratosphere.sCloud 		= "sky_00.png";
					skybox.stratosphere.sBump		= "sky_00_bump.png";

					//cout << "=> Setup Atmospheric Layer Distances" << std::endl;
					//cout << "Troposphere:  " << skybox.troposphere.fScale << std::endl;
					//cout << "Stratosphere: " << skybox.stratosphere.fScale << std::endl;
					//cout << "Mesosphere:   " << skybox.mesosphere.fScale << std::endl;
					//cout << "Thermosphere: " << skybox.thermosphere.fScale << std::endl;
					//cout << "Exosphere:    " << skybox.exosphere.fScale << endl << std::endl;

					//_Satellite * newSat = new _Satellite(*this);
					//satellite.push_back(_Satellite(*this));
					//satellite1->init();
					//satellite2->init();
//
//						/*
//						 * Setup the inital moon values
//						 */
//						moon.vPosition[0] 		= 300.0;
//						moon.vPosition[1] 		= 200.0;
//						moon.vPosition[2] 		= 200.0;
//
//						moon.vAmbientBase[0] 	= 0.1f;
//						moon.vAmbientBase[1] 	= 0.1f;
//						moon.vAmbientBase[2] 	= 0.1f;
//						moon.vAmbientBase[3] 	= 1.0f;
//
//						moon.vAmbientColor[0] 	= moon.vAmbientBase[0];
//						moon.vAmbientColor[1] 	= moon.vAmbientBase[1];
//						moon.vAmbientColor[2] 	= moon.vAmbientBase[2];
//						moon.vAmbientColor[3] 	= moon.vAmbientBase[3];
//
//						moon.vDiffuseBase[0] 	= 0.2f;
//						moon.vDiffuseBase[1] 	= 0.2f;
//						moon.vDiffuseBase[2] 	= 0.3f;
//						moon.vDiffuseBase[3]	= 1.0f;
//
//						moon.vDiffuseColor[0] 	= moon.vDiffuseBase[0];
//						moon.vDiffuseColor[1] 	= moon.vDiffuseBase[1];
//						moon.vDiffuseColor[2] 	= moon.vDiffuseBase[2];
//						moon.vDiffuseColor[3] 	= moon.vDiffuseBase[3];
//
//						moon.vSpecularBase[0]	= 0.4f;
//						moon.vSpecularBase[1]	= 0.4f;
//						moon.vSpecularBase[2]	= 0.5f;
//						moon.vSpecularBase[3]	= 1.0f;
//
//						moon.vSpecularColor[0] 	= moon.vSpecularBase[0];
//						moon.vSpecularColor[1] 	= moon.vSpecularBase[1];
//						moon.vSpecularColor[2] 	= moon.vSpecularBase[2];
//						moon.vSpecularColor[3] 	= moon.vSpecularBase[3];
//
//						moon.fShinyBase			= 1.0f;
//						//moon.fShinyBase		= 0.003f;
//						moon.fShiny				= moon.fShinyBase;
//						moon.fLightAzimuth		= -100.0f;
//						//moon.fLightDistance	= sqrt((skybox.stratosphere.fScale*skybox.stratosphere.fScale)+(skybox.stratosphere.fScale*skybox.stratosphere.fScale))+500.0f;
//						moon.fLightDistance		= 100000.0f*gameVars->screen.iScale;
//						moon.fLightZenith		= 30.0f;
//
//						moon.sImage				= "moon_00.png";
//						moon.fScale				= 100.0f*gameVars->screen.iScale;
//
//						/*
//						 * Initial Rain Values
//						 */
//						rain.vColor[0]			= 1.0f;
//						rain.vColor[1]			= 1.0f;
//						rain.vColor[2]			= 1.0f;
//						rain.vColor[3]			= 1.0f;
//						rain.fScale				= 1.0f;
//						rain.sCloud				= "sky_01.png";
//						rain.sBump				= "sky_01_bump.png";
//						rain.iNum				= 50000;
//						rain.fScale				= 2.0f;
//						rain.iRate				= 10;
//						//rain.sImage			= "snow_4.png";
//						rain.iMax				= 512;
//						rain.iMin				= 128;
//						rain.iRange				= 1024;
//						rain.iThreshold			= 1;
//						rain.fFall				= 5.0f;
//						rain.fLength			= 5.0f;
//
//						/*
//						 * Initial Snow Values
//						 */
//						snow.vColor[0]			= 1.0f;
//						snow.vColor[1]			= 1.0f;
//						snow.vColor[2]			= 1.0f;
//						snow.vColor[3]			= 1.0f;
//						snow.fScale				= 1.0f;
//						snow.sCloud				= "sky_01.png";
//						snow.sBump				= "sky_01_bump.png";
//						snow.iNum				= 300000;
//						snow.iRate				= 5;
//						snow.sImage				= "snow_4.png";
//						snow.iMax				= 512;
//						snow.iMin				= 128;
//						snow.iRange				= 1024;
//						snow.iThreshold			= 1;
//						snow.fFall				= 0.25;
//
//						/*
//						 * Initial Hail Values
//						 */
//						hail.fScale				= 1.0f;
//						hail.sCloud				= "sky_01.png";
//						hail.sBump				= "sky_01_bump.png";
//						hail.iNum				= 10000;
//						hail.iRate				= 5;
//						hail.iMax				= 512;
//						hail.iMin				= 128;
//						hail.iRange				= 1024;
//						hail.iThreshold			= 1;
//						hail.fFall				= 5.0f;
//
//						/*
//						 * Initial Flora Values
//						 */
//						//flora.vColor[0]		= 1.0f;
//						//flora.vColor[1]		= 1.0f;
//						//flora.vColor[2]		= 1.0f;
//						//flora.vColor[3]		= 1.0f;
//						flora.fScale			= 2.0f;
//						flora.iMaxWidth			= 10;
//						flora.iMinWidth			= 4;
//						flora.iMaxHeight		= 16;
//						flora.iMinHeight		= 4;
//						flora.iNum				= 500;
//						flora.iRate				= 250;
//						flora.iRange			= 512;
//						flora.iThreshold		= 1;
//						flora.iInstance			= 0;
//						flora.iSpread			= 16;
//						flora.fFloorPlay		= 5.0f;
//						flora.fFloor			= -4.0f;
//						flora.fCeiling			= 1024.0f;
//
//						/*
//						 * Initial Underwater Flora Values
//						 */
//						//flora.vColor[0]		= 1.0f;
//						//flora.vColor[1]		= 1.0f;
//						//flora.vColor[2]		= 1.0f;
//						//flora.vColor[3]		= 1.0f;
//						uwflora.fScale			= 1.0f;
//						uwflora.iMaxWidth		= 4;
//						uwflora.iMinWidth		= 2;
//						uwflora.iMaxHeight		= 6;
//						uwflora.iMinHeight		= 2;
//						uwflora.iNum			= 500;
//						uwflora.iRate			= 250;
//						uwflora.iRange			= 256;
//						uwflora.iThreshold		= 1;
//						uwflora.iInstance		= 0;
//						uwflora.iSpread			= 16;
//						uwflora.fFloorPlay		= 4.0f;
//						uwflora.fFloor			= -4096.0f;
//						uwflora.fCeiling		= -12.0f;
//						uwflora.iFail			= 10;
//
//						/*
//						 * Initial Grass Values
//						 */
//						//grass.vColor[0]		= 1.0f;
//						//grass.vColor[1]		= 1.0f;
//						//grass.vColor[2]		= 1.0f;
//						//grass.vColor[3]		= 1.0f;
//						grass.bEnable			= false;
//						grass.fScale			= 1.0f;
//						grass.iMinHeight		= 0;
//						grass.iMaxHeight		= 4;
//						grass.iVariation		= 2;
//						grass.fThickness		= 0.2f;
//						grass.iNum				= 0;
//						grass.iRate				= 1000;
//						grass.iRange			= 3;
//						grass.iThreshold		= 1;
//						grass.iInstance			= 30000;	//500
//						grass.fSpread			= 8;	//8.5
//						grass.fFloor			= -4;
//						grass.fFloorPlay		= 2;
//						grass.fSkew				= 0.2;
//						grass.bLine				= true;
//
//						/*
//						 * Initial Water Values
//						 */
//						water.sTexture			= "water_tex.jpg";
//						water.sBump 			= "water_bump.png";
//						water.sSpec 			= "water_spec.png";
//						water.sWorld			= "water_world.png";
//						water.fFloor			= gameVars->world.water.iHeight;
//						water.iX				= (gameVars->screen.iTerrainGrid/2)*1024+512;
//						water.iZ				= (gameVars->screen.iTerrainGrid/2)*1024+512;
//						water.fRange			= 64; //(64 meters * 16 units = 1024 units)
//						//water.fScale			= 128;
//						water.fScale			= ((float)gameVars->screen.iTerrainGrid/2)*32*gameVars->screen.iScale;
//						water.vColor[0]			= 0.0;
//						water.vColor[1]			= 0.2;
//						water.vColor[2]			= 0.5;
//						water.vColor[3]			= 1.0;
//						water.iRate				= 100;
//						water.fSpeed			= 0.05;
//						water.bEnable			= true;

//				}
//				else {
//					std::string sText = "";
//
//					skybox.troposphere.fScale	= 10000*gameVars->screen.iScale;
//					skybox.stratosphere.fScale	= skybox.troposphere.fScale;
//					skybox.mesosphere.fScale	= skybox.stratosphere.fScale;
//					skybox.thermosphere.fScale	= skybox.mesosphere.fScale;
//					skybox.exosphere.fScale		= skybox.thermosphere.fScale;
//
//					// Troposphere              (28 bytes)
//					sText = ""; sText = ""; for(int j=0;j<28; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					skybox.troposphere.sImage 	= sText;
//					// Stratosphere             (28 bytes)
//					sText = ""; for(int j=28;j<55; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					skybox.stratosphere.sCloud  = sText;
//					// Stratosphere Bump        (28 bytes)
//					sText = ""; for(int j=55;j<84; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					skybox.stratosphere.sBump		= sText;
//					// Mesosphere               (28 bytes)
//					sText = ""; for(int j=84;j<112; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					skybox.mesosphere.sImage		= sText;
//					// Thermosphere             (28 bytes)
//					sText = ""; for(int j=112;j<140; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					skybox.thermosphere.sImage	= sText;
//					// Exosphere                (28 bytes)
//					sText = ""; for(int j=140;j<168; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					skybox.exosphere.sImage			= sText;
//
//
//					// Sun Texture              (28 bytes)
//					sText = ""; for(int j=168;j<196; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					sun.sImage							= sText;
//					// Scale                    (32 bit)
//					sun.fScale							= (__uint32_t)( (__uint8_t)(memBlock.buffer[196])*65536 + (__uint8_t)(memBlock.buffer[197])*4096 + (__uint8_t)(memBlock.buffer[198])*256 + (__uint8_t)(memBlock.buffer[199]) );
//
//					// Azimuth                  (16 bit)
//					sun.fLightAzimuth				= (__uint16_t)( (__uint8_t)(memBlock.buffer[200])*256 + (__uint8_t)(memBlock.buffer[201]) );
//					// Ambient R                (8 bit)
//					sun.vAmbientBase[0]			= float((__uint8_t)(memBlock.buffer[202]))/255;
//					// Ambient G                (8 bit)
//					sun.vAmbientBase[1]			= float((__uint8_t)(memBlock.buffer[203]))/255;
//					// Ambient B                (8 bit)
//					sun.vAmbientBase[2]			= float((__uint8_t)(memBlock.buffer[204]))/255;
//					sun.vAmbientBase[3]			= 1.0f;
//					// Diffuse R                (8 bit)
//					sun.vDiffuseBase[0]			= float((__uint8_t)(memBlock.buffer[205]))/255;
//					// Diffuse G                (8 bit)
//					sun.vDiffuseBase[1]			= float((__uint8_t)(memBlock.buffer[206]))/255;
//					// Diffuse B                (8 bit)
//					sun.vDiffuseBase[2]			= float((__uint8_t)(memBlock.buffer[207]))/255;
//					sun.vDiffuseBase[3]			= 1.0f;
//					// Specular R               (8 bit)
//					sun.vSpecularBase[0]		= float((__uint8_t)(memBlock.buffer[208]))/255;
//					// Specular G               (8 bit)
//					sun.vSpecularBase[1]		= float((__uint8_t)(memBlock.buffer[209]))/255;
//					// Specular B               (8 bit)
//					sun.vSpecularBase[2]		= float((__uint8_t)(memBlock.buffer[210]))/255;
//					sun.vSpecularBase[3]		=  1.0f;
//					// Shinyness                (32 bit)
//					sun.fShiny							= (__uint32_t)( (__uint8_t)(memBlock.buffer[211]) + (__uint8_t)(memBlock.buffer[212]) + (__uint8_t)(memBlock.buffer[213]) + (__uint8_t)(memBlock.buffer[214]) );
//					// RESERVED                 (8 bit*9)
//					sun.vAmbientColor[0] 	= sun.vAmbientBase[0];
//					sun.vAmbientColor[1] 	= sun.vAmbientBase[1];
//					sun.vAmbientColor[2] 	= sun.vAmbientBase[2];
//					sun.vAmbientColor[3] 	= sun.vAmbientBase[3];
//
//					sun.vDiffuseColor[0] 	= sun.vDiffuseBase[0];
//					sun.vDiffuseColor[1] 	= sun.vDiffuseBase[1];
//					sun.vDiffuseColor[2] 	= sun.vDiffuseBase[2];
//					sun.vDiffuseColor[3] 	= sun.vDiffuseBase[3];
//
//					sun.vSpecularColor[0] 	= sun.vSpecularBase[0];
//					sun.vSpecularColor[1] 	= sun.vSpecularBase[1];
//					sun.vSpecularColor[2] 	= sun.vSpecularBase[2];
//					sun.vSpecularColor[3] 	= sun.vSpecularBase[3];
//
//					sun.fLightAzimuth		= 90.0f;
//					sun.fLightAltitude		= 45.0;
//					sun.fLightDistance		= 100;
//					sun.fScale				= 1000.0f;
//
//					sun.vQuadSize[0]		= 256;
//					sun.vQuadSize[1]		= 256;
//
//					sun.sFlare[0]			= "tex1.png";
//					sun.sFlare[1]			= "tex2.png";
//					sun.sFlare[2]			= "tex3.png";
//					sun.sFlare[3]			= "tex4.png";
//					sun.sFlare[4]			= "tex5.png";
//					sun.sFlare[5]			= "tex6.png";
//					sun.sFlare[6]			= "tex7.png";
//					sun.sFlare[7]			= "tex8.png";
//					sun.sFlare[8]			= "tex9.png";
//			//    (__uint8_t)0), 9);
//
//					//"", 9));
//
//					// Moon Texture             (28 bytes)
//					sText = ""; for(int j=224;j<252; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					moon.sImage				= sText;
//					// Scale                    (32 bit)
//					moon.fScale				= (__uint32_t)( (__uint8_t)(memBlock.buffer[252])*65536 + (__uint8_t)(memBlock.buffer[253])*4096 + (__uint8_t)(memBlock.buffer[254])*256 + (__uint8_t)(memBlock.buffer[255]) );
//					// Azimuth                  (16 bit)
//					moon.fLightAzimuth		= (__uint16_t)( (__uint8_t)(memBlock.buffer[256])*256 + (__uint8_t)(memBlock.buffer[257]) );
//					// Ambient R                (8 bit)
//					moon.vAmbientBase[0]	= float( (__uint8_t)(memBlock.buffer[258]) )/255;
//					// Ambient G                (8 bit)
//					moon.vAmbientBase[1]	= float( (__uint8_t)(memBlock.buffer[259]) )/255;
//					// Ambient B                (8 bit)
//					moon.vAmbientBase[2]	= float( (__uint8_t)(memBlock.buffer[260]) )/255;
//					moon.vAmbientBase[3]	= 1.0f;
//					// Diffuse R                (8 bit)
//					moon.vDiffuseBase[0]	= float( (__uint8_t)(memBlock.buffer[261]) )/255;
//					// Diffuse G                (8 bit)
//					moon.vDiffuseBase[1]	= float( (__uint8_t)(memBlock.buffer[262]) )/255;
//					// Diffuse B                (8 bit)
//					moon.vDiffuseBase[2]	= float( (__uint8_t)(memBlock.buffer[263]) )/255;
//					moon.vDiffuseBase[3]	= 1.0f;
//					// Specular R               (8 bit)
//					moon.vSpecularBase[0]	= float( (__uint8_t)(memBlock.buffer[264]) )/255;
//					// Specular G               (8 bit)
//					moon.vSpecularBase[1]	= float( (__uint8_t)(memBlock.buffer[265]) )/255;
//					// Specular B               (8 bit)
//					moon.vSpecularBase[2]	= float( (__uint8_t)(memBlock.buffer[266]) )/255;
//					moon.vSpecularBase[3]	= 1.0f;
//					// Shinyness                (32 bit)
//					moon.fShiny						= (__uint32_t)( (__uint8_t)(memBlock.buffer[267]) + (__uint8_t)(memBlock.buffer[268]) + (__uint8_t)(memBlock.buffer[269]) + (__uint8_t)(memBlock.buffer[270]) );
//					// RESERVED                 (8 bit*9)
//					moon.vAmbientColor[0] 	= moon.vAmbientBase[0];
//					moon.vAmbientColor[1] 	= moon.vAmbientBase[1];
//					moon.vAmbientColor[2] 	= moon.vAmbientBase[2];
//					moon.vAmbientColor[3] 	= moon.vAmbientBase[3];
//
//					moon.vDiffuseColor[0] 	= moon.vDiffuseBase[0];
//					moon.vDiffuseColor[1] 	= moon.vDiffuseBase[1];
//					moon.vDiffuseColor[2] 	= moon.vDiffuseBase[2];
//					moon.vDiffuseColor[3] 	= moon.vDiffuseBase[3];
//
//					moon.vSpecularColor[0] 	= moon.vSpecularBase[0];
//					moon.vSpecularColor[1] 	= moon.vSpecularBase[1];
//					moon.vSpecularColor[2] 	= moon.vSpecularBase[2];
//					moon.vSpecularColor[3] 	= moon.vSpecularBase[3];
//					moon.fLightDistance		= 100000.0f*gameVars->screen.iScale;
//			//    (__uint8_t)0), 9);
//
//					// Rain Sky Texture         (28 bytes)
//					sText = ""; for(int j=280;j<308; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					rain.sCloud						= sText;
//					// Rain Bump Texture        (28 bytes)
//					sText = ""; for(int j=308;j<336; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					rain.sBump						= sText;
//					// Scale                    (32 bit)
//					rain.fScale						= (__uint32_t)( (__uint8_t)(memBlock.buffer[336])*65536 + (__uint8_t)(memBlock.buffer[337])*4096 + (__uint8_t)(memBlock.buffer[338])*256 + (__uint8_t)(memBlock.buffer[339]) );
//					// Update Rate              (32 bit)
//					rain.iRate						= (__uint32_t)( (__uint8_t)(memBlock.buffer[340])*65536 + (__uint8_t)(memBlock.buffer[341])*4096 + (__uint8_t)(memBlock.buffer[342])*256 + (__uint8_t)(memBlock.buffer[343]) );
//					// Max Height               (32 bit)
//					rain.iMax							= (__uint32_t)( (__uint8_t)(memBlock.buffer[344])*65536 + (__uint8_t)(memBlock.buffer[345])*4096 + (__uint8_t)(memBlock.buffer[346])*256 + (__uint8_t)(memBlock.buffer[347]) );
//					// Min Height               (32 bit)
//					rain.iMin							= (__uint32_t)( (__uint8_t)(memBlock.buffer[348])*65536 + (__uint8_t)(memBlock.buffer[349])*4096 + (__uint8_t)(memBlock.buffer[350])*256 + (__uint8_t)(memBlock.buffer[351]) );
//					// Range                    (32 bit)
//					rain.iRange						= (__uint32_t)( (__uint8_t)(memBlock.buffer[352])*65536 + (__uint8_t)(memBlock.buffer[353])*4096 + (__uint8_t)(memBlock.buffer[354])*256 + (__uint8_t)(memBlock.buffer[355]) );
//					// Threshold                (32 bit)
//					rain.iThreshold					= (__uint32_t)( (__uint8_t)(memBlock.buffer[356])*65536 + (__uint8_t)(memBlock.buffer[357])*4096 + (__uint8_t)(memBlock.buffer[358])*256 + (__uint8_t)(memBlock.buffer[359]) );
//					// Fall                     (32 bit)
//					rain.fFall						= (__uint32_t)( (__uint8_t)(memBlock.buffer[360])*65536 + (__uint8_t)(memBlock.buffer[361])*4096 + (__uint8_t)(memBlock.buffer[362])*256 + (__uint8_t)(memBlock.buffer[363]) );
//					// Max Length               (32 bit)
//					rain.fLength					= (__uint32_t)( (__uint8_t)(memBlock.buffer[364])*65536 + (__uint8_t)(memBlock.buffer[365])*4096 + (__uint8_t)(memBlock.buffer[366])*256 + (__uint8_t)(memBlock.buffer[367]) );
//					// Min Length               (32 bit)
//		//			ui->spinRainMinLength->setValue(        (__uint32_t)( (__uint8_t)(memBlock.buffer[368])*65536 + (__uint8_t)(memBlock.buffer[369])*4096 + (__uint8_t)(memBlock.buffer[370])*256 + (__uint8_t)(memBlock.buffer[371]) );
//					// Number of drops          (32 bit)
//					rain.iNum							= (__uint32_t)( (__uint8_t)(memBlock.buffer[372])*65536 + (__uint8_t)(memBlock.buffer[373])*4096 + (__uint8_t)(memBlock.buffer[374])*256 + (__uint8_t)(memBlock.buffer[375]) );
//					// R                        (8 bit)
//					rain.vColor[0]				= (float)( (__uint8_t)(memBlock.buffer[376]) )/255.0f;
//					// G                        (8 bit)
//					rain.vColor[1]				= (float)( (__uint8_t)(memBlock.buffer[377]) )/255.0f;
//					// B                        (8 bit)
//					rain.vColor[2]				= (float)( (__uint8_t)(memBlock.buffer[378]) )/255.0f;
//					rain.vColor[3]				= 1.0f;
//					// RESERVED                 (8 bit*13)
//			//    (__uint8_t)0), 13);
//
//					rain.vColor[0]			= 1.0f;
//					rain.vColor[1]			= 1.0f;
//					rain.vColor[2]			= 1.0f;
//					rain.vColor[3]			= 1.0f;
//					rain.fScale				= 1.0f;
//					rain.sCloud				= "sky_01.png";
//					rain.sBump				= "sky_01_bump.png";
//					rain.iNum				= 50000;
//					rain.fScale				= 1.0f;
//					rain.iRate				= 10;
//					//rain.sImage			= "snow_4.png";
//					rain.iMax				= 2048;
//					rain.iMin				= 1024;
//					rain.iRange				= 500;		// 1=only spawn at exact player position
//					rain.iThreshold			= 5;
//					rain.fFall				= 25.0f;
//					rain.fLength			= 50.0f;
//
//
//
//
//
//
//
//
//
//					// Snow texture             (28 bytes)
//					sText = ""; for(int j=392;j<420; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					snow.sImage						= sText;
//					// Snow sky texture         (28 bytes)
//					sText = ""; for(int j=420;j<448; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					snow.sCloud						= sText;
//					// Snow sky bump            (28 bytes)
//					sText = ""; for(int j=448;j<476; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					snow.sBump						= sText;
//					// Scale                    (32 bit)
//					snow.fScale						= (__uint32_t)( (__uint8_t)(memBlock.buffer[476])*65536 + (__uint8_t)(memBlock.buffer[477])*4096 + (__uint8_t)(memBlock.buffer[478])*256 + (__uint8_t)(memBlock.buffer[479]) );
//					// Rate                     (32 bit)
//					snow.iRate						= (__uint32_t)( (__uint8_t)(memBlock.buffer[480])*65536 + (__uint8_t)(memBlock.buffer[481])*4096 + (__uint8_t)(memBlock.buffer[482])*256 + (__uint8_t)(memBlock.buffer[483]) );
//					// Max Height               (32 bit)
//					snow.iMax							= (__uint32_t)( (__uint8_t)(memBlock.buffer[484])*65536 + (__uint8_t)(memBlock.buffer[485])*4096 + (__uint8_t)(memBlock.buffer[486])*256 + (__uint8_t)(memBlock.buffer[487]) );
//					// Min Height               (32 bit)
//					snow.iMin							= (__uint32_t)( (__uint8_t)(memBlock.buffer[488])*65536 + (__uint8_t)(memBlock.buffer[489])*4096 + (__uint8_t)(memBlock.buffer[490])*256 + (__uint8_t)(memBlock.buffer[491]) );
//					// Range                    (32 bit)
//					snow.iRange						= (__uint32_t)( (__uint8_t)(memBlock.buffer[492])*65536 + (__uint8_t)(memBlock.buffer[493])*4096 + (__uint8_t)(memBlock.buffer[494])*256 + (__uint8_t)(memBlock.buffer[495]) );
//					// Threshold                (32 bit)
//					snow.iThreshold				= (__uint32_t)( (__uint8_t)(memBlock.buffer[496])*65536 + (__uint8_t)(memBlock.buffer[497])*4096 + (__uint8_t)(memBlock.buffer[498])*256 + (__uint8_t)(memBlock.buffer[499]) );
//					// Fall                     (32 bit)
//					snow.fFall						= (__uint32_t)( (__uint8_t)(memBlock.buffer[500])*65536 + (__uint8_t)(memBlock.buffer[501])*4096 + (__uint8_t)(memBlock.buffer[502])*256 + (__uint8_t)(memBlock.buffer[503]) );
//					// Number                   (32 bit)
//					snow.iNum							= (__uint32_t)( (__uint8_t)(memBlock.buffer[504])*65536 + (__uint8_t)(memBlock.buffer[505])*4096 + (__uint8_t)(memBlock.buffer[506])*256 + (__uint8_t)(memBlock.buffer[507]) );
//					// R                        (8 bit)
//					snow.vColor[0]				= (float)( (__uint8_t)(memBlock.buffer[508]) )/255.0f;
//					// G                        (8 bit)
//					snow.vColor[1]				= (float)( (__uint8_t)(memBlock.buffer[509]) )/255.0f;
//					// B                        (8 bit)
//					snow.vColor[2]				= (float)( (__uint8_t)(memBlock.buffer[510]) )/255.0f;
//					snow.vColor[3]				= 1.0f;
//					// RESERVED                 (8 bit*21)
//			//    (__uint8_t)0), 21);
//
//					/*
//					 * Initial Snow Values
//					 */
//					snow.vColor[0]			= 1.0f;
//					snow.vColor[1]			= 1.0f;
//					snow.vColor[2]			= 1.0f;
//					snow.vColor[3]			= 1.0f;
//					snow.fScale				= 1.0f;
//					snow.sCloud				= "sky_01.png";
//					snow.sBump				= "sky_01_bump.png";
//					snow.iNum				= 300000;
//					snow.iRate				= 5;
//					snow.sImage				= "snow_4.png";
//					snow.iMax				= 1048;
//					snow.iMin				= 128;
//					snow.iRange				= 500;
//					snow.iThreshold			= 10;
//					snow.fFall				= 1;
//
//
//
//
//
//
//
//
//
//
//
//
//					// Hail sky texture         (28 bytes)
//					sText = ""; for(int j=532;j<560; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					hail.sCloud						= sText;
//					// Hail sky bump            (28 bytes)
//					sText = ""; for(int j=560;j<588; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					hail.sBump						= sText;
//					// Scale                    (32 bit)
//					hail.fScale						= (__uint32_t)( (__uint8_t)(memBlock.buffer[588])*65536 + (__uint8_t)(memBlock.buffer[589])*4096 + (__uint8_t)(memBlock.buffer[590])*256 + (__uint8_t)(memBlock.buffer[591]) );
//					// Rate                     (32 bit)
//					hail.iRate						= (__uint32_t)( (__uint8_t)(memBlock.buffer[592])*65536 + (__uint8_t)(memBlock.buffer[593])*4096 + (__uint8_t)(memBlock.buffer[594])*256 + (__uint8_t)(memBlock.buffer[595]) );
//					// Max Height               (32 bit)
//					hail.iMax							= (__uint32_t)( (__uint8_t)(memBlock.buffer[596])*65536 + (__uint8_t)(memBlock.buffer[597])*4096 + (__uint8_t)(memBlock.buffer[598])*256 + (__uint8_t)(memBlock.buffer[599]) );
//					// Min Height               (32 bit)
//					hail.iMin							= (__uint32_t)( (__uint8_t)(memBlock.buffer[600])*65536 + (__uint8_t)(memBlock.buffer[601])*4096 + (__uint8_t)(memBlock.buffer[602])*256 + (__uint8_t)(memBlock.buffer[603]) );
//					// Range                    (32 bit)
//					hail.iRange						= (__uint32_t)( (__uint8_t)(memBlock.buffer[604])*65536 + (__uint8_t)(memBlock.buffer[605])*4096 + (__uint8_t)(memBlock.buffer[606])*256 + (__uint8_t)(memBlock.buffer[607]) );
//					// Threshold                (32 bit)
//					hail.iThreshold				= (__uint32_t)( (__uint8_t)(memBlock.buffer[608])*65536 + (__uint8_t)(memBlock.buffer[609])*4096 + (__uint8_t)(memBlock.buffer[610])*256 + (__uint8_t)(memBlock.buffer[611]) );
//					// Fall                     (32 bit)
//					hail.fFall						= (__uint32_t)( (__uint8_t)(memBlock.buffer[612])*65536 + (__uint8_t)(memBlock.buffer[613])*4096 + (__uint8_t)(memBlock.buffer[614])*256 + (__uint8_t)(memBlock.buffer[615]) );
//					// Number                   (32 bit)
//					hail.iNum							= (__uint32_t)( (__uint8_t)(memBlock.buffer[616])*65536 + (__uint8_t)(memBlock.buffer[617])*4096 + (__uint8_t)(memBlock.buffer[618])*256 + (__uint8_t)(memBlock.buffer[619]) );
//					// R                        (8 bit)
//					hail.vColor[0]				= (float)( (__uint8_t)(memBlock.buffer[620]) )/255.0f;
//					// G                        (8 bit)
//					hail.vColor[1]				= (float)( (__uint8_t)(memBlock.buffer[621]) )/255.0f;
//					// B                        (8 bit)
//					hail.vColor[2]				= (float)( (__uint8_t)(memBlock.buffer[622]) )/255.0f;
//					hail.vColor[3]				= 1.0f;
//					// RESERVED                 (8 bit*21)
//			//    (__uint8_t)0), 21);
//
//					/*
//					 * Initial Hail Values
//					 */
//					hail.fScale				= 1.0f;
//					hail.sCloud				= "sky_01.png";
//					hail.sBump				= "sky_01_bump.png";
//					hail.iNum				= 20000;
//					hail.iRate				= 5;
//					hail.iMax				= 2048;
//					hail.iMin				= 1024;
//					hail.iRange				= 500;
//					hail.iThreshold			= 10;
//					hail.fFall				= 25.0f;
//
//
//
//
//
//
//
//
//
//
//					// Scale                    (32 bit)
//					flora.fScale					= (__uint32_t)( (__uint8_t)(memBlock.buffer[644])*65536 + (__uint8_t)(memBlock.buffer[645])*4096 + (__uint8_t)(memBlock.buffer[646])*256 + (__uint8_t)(memBlock.buffer[647]) );
//					// Max width                (32 bit)
//					flora.iMaxWidth				= (__uint32_t)( (__uint8_t)(memBlock.buffer[648])*65536 + (__uint8_t)(memBlock.buffer[649])*4096 + (__uint8_t)(memBlock.buffer[650])*256 + (__uint8_t)(memBlock.buffer[651]) );
//					// Min width                (32 bit)
//					flora.iMinWidth				= (__uint32_t)( (__uint8_t)(memBlock.buffer[652])*65536 + (__uint8_t)(memBlock.buffer[653])*4096 + (__uint8_t)(memBlock.buffer[654])*256 + (__uint8_t)(memBlock.buffer[655]) );
//					// Max height               (32 bit)
//					flora.iMaxHeight			= (__uint32_t)( (__uint8_t)(memBlock.buffer[656])*65536 + (__uint8_t)(memBlock.buffer[657])*4096 + (__uint8_t)(memBlock.buffer[658])*256 + (__uint8_t)(memBlock.buffer[659]) );
//					// Min height               (32 bit)
//					flora.iMinHeight			= (__uint32_t)( (__uint8_t)(memBlock.buffer[660])*65536 + (__uint8_t)(memBlock.buffer[661])*4096 + (__uint8_t)(memBlock.buffer[662])*256 + (__uint8_t)(memBlock.buffer[663]) );
//					// Number                   (32 bit)
//					flora.iNum						= (__uint32_t)( (__uint8_t)(memBlock.buffer[664])*65536 + (__uint8_t)(memBlock.buffer[665])*4096 + (__uint8_t)(memBlock.buffer[666])*256 + (__uint8_t)(memBlock.buffer[667]) );
//					// Rate                     (32 bit)
//					flora.iRate						= (__uint32_t)( (__uint8_t)(memBlock.buffer[668])*65536 + (__uint8_t)(memBlock.buffer[669])*4096 + (__uint8_t)(memBlock.buffer[670])*256 + (__uint8_t)(memBlock.buffer[671]) );
//					// Range                    (32 bit)
//					flora.iRange					= (__uint32_t)( (__uint8_t)(memBlock.buffer[672])*65536 + (__uint8_t)(memBlock.buffer[673])*4096 + (__uint8_t)(memBlock.buffer[674])*256 + (__uint8_t)(memBlock.buffer[675]) );
//					// Threshold                (32 bit)
//					flora.iThreshold			= (__uint32_t)( (__uint8_t)(memBlock.buffer[676])*65536 + (__uint8_t)(memBlock.buffer[677])*4096 + (__uint8_t)(memBlock.buffer[678])*256 + (__uint8_t)(memBlock.buffer[679]) );
//					// Instance                 (32 bit)
//					flora.iInstance				= (__uint32_t)( (__uint8_t)(memBlock.buffer[680])*65536 + (__uint8_t)(memBlock.buffer[681])*4096 + (__uint8_t)(memBlock.buffer[682])*256 + (__uint8_t)(memBlock.buffer[683]) );
//					// Spread                   (32 bit)
//					flora.iSpread					= (__uint32_t)( (__uint8_t)(memBlock.buffer[684])*65536 + (__uint8_t)(memBlock.buffer[685])*4096 + (__uint8_t)(memBlock.buffer[686])*256 + (__uint8_t)(memBlock.buffer[687]) );
//					// Floorplay                (32 bit)
//					flora.fFloorPlay			= (__uint32_t)( (__uint8_t)(memBlock.buffer[688])*65536 + (__uint8_t)(memBlock.buffer[689])*4096 + (__uint8_t)(memBlock.buffer[690])*256 + (__uint8_t)(memBlock.buffer[691]) );
//					// Floor                    (32 bit)
//					flora.fFloor					= (__int32_t)( (__int8_t)(memBlock.buffer[692])*65536 + (__int8_t)(memBlock.buffer[693])*4096 + (__int8_t)(memBlock.buffer[694])*256 + (__int8_t)(memBlock.buffer[695]) );
//					// Ceiling                  (32 bit)
//					flora.fCeiling				= (__int32_t)( (__int8_t)(memBlock.buffer[696])*65536 + (__int8_t)(memBlock.buffer[697])*4096 + (__int8_t)(memBlock.buffer[698])*256 + (__int8_t)(memBlock.buffer[699]) );
//
//					// Scale                    (32 bit)
//					uwflora.fScale				= (__uint32_t)( (__uint8_t)(memBlock.buffer[700])*65536 + (__uint8_t)(memBlock.buffer[701])*4096 + (__uint8_t)(memBlock.buffer[702])*256 + (__uint8_t)(memBlock.buffer[703]) );
//					// Max width                (32 bit)
//					uwflora.iMaxWidth			= (__uint32_t)( (__uint8_t)(memBlock.buffer[704])*65536 + (__uint8_t)(memBlock.buffer[705])*4096 + (__uint8_t)(memBlock.buffer[706])*256 + (__uint8_t)(memBlock.buffer[707]) );
//					// Min width                (32 bit)
//					uwflora.iMinWidth			= (__uint32_t)( (__uint8_t)(memBlock.buffer[708])*65536 + (__uint8_t)(memBlock.buffer[709])*4096 + (__uint8_t)(memBlock.buffer[710])*256 + (__uint8_t)(memBlock.buffer[711]) );
//					// Max height               (32 bit)
//					uwflora.iMaxHeight		= (__uint32_t)( (__uint8_t)(memBlock.buffer[712])*65536 + (__uint8_t)(memBlock.buffer[713])*4096 + (__uint8_t)(memBlock.buffer[714])*256 + (__uint8_t)(memBlock.buffer[715]) );
//					// Min height               (32 bit)
//					uwflora.iMinHeight		= (__uint32_t)( (__uint8_t)(memBlock.buffer[716])*65536 + (__uint8_t)(memBlock.buffer[717])*4096 + (__uint8_t)(memBlock.buffer[718])*256 + (__uint8_t)(memBlock.buffer[719]) );
//					// Number                   (32 bit)
//					uwflora.iNum					= (__uint32_t)( (__uint8_t)(memBlock.buffer[720])*65536 + (__uint8_t)(memBlock.buffer[721])*4096 + (__uint8_t)(memBlock.buffer[722])*256 + (__uint8_t)(memBlock.buffer[723]) );
//					// Rate                     (32 bit)
//					uwflora.iRate					= (__uint32_t)( (__uint8_t)(memBlock.buffer[724])*65536 + (__uint8_t)(memBlock.buffer[725])*4096 + (__uint8_t)(memBlock.buffer[726])*256 + (__uint8_t)(memBlock.buffer[727]) );
//					// Range                    (32 bit)
//					uwflora.iRange				= (__uint32_t)( (__uint8_t)(memBlock.buffer[728])*65536 + (__uint8_t)(memBlock.buffer[729])*4096 + (__uint8_t)(memBlock.buffer[730])*256 + (__uint8_t)(memBlock.buffer[731]) );
//					// Threshold                (32 bit)
//					uwflora.iThreshold		= (__uint32_t)( (__uint8_t)(memBlock.buffer[732])*65536 + (__uint8_t)(memBlock.buffer[733])*4096 + (__uint8_t)(memBlock.buffer[734])*256 + (__uint8_t)(memBlock.buffer[735]) );
//					// Instance                 (32 bit)
//					uwflora.iInstance			= (__uint32_t)( (__uint8_t)(memBlock.buffer[736])*65536 + (__uint8_t)(memBlock.buffer[737])*4096 + (__uint8_t)(memBlock.buffer[738])*256 + (__uint8_t)(memBlock.buffer[739]) );
//					// Spread                   (32 bit)
//					uwflora.iSpread				= (__uint32_t)( (__uint8_t)(memBlock.buffer[740])*65536 + (__uint8_t)(memBlock.buffer[741])*4096 + (__uint8_t)(memBlock.buffer[742])*256 + (__uint8_t)(memBlock.buffer[743]) );
//					// Floorplay                (32 bit)
//					uwflora.fFloorPlay		= (__uint32_t)( (__uint8_t)(memBlock.buffer[744])*65536 + (__uint8_t)(memBlock.buffer[745])*4096 + (__uint8_t)(memBlock.buffer[746])*256 + (__uint8_t)(memBlock.buffer[747]) );
//					// Floor                    (32 bit)
//					uwflora.fFloor				= (__int32_t)( (__int8_t)(memBlock.buffer[748])*65536 + (__int8_t)(memBlock.buffer[749])*4096 + (__int8_t)(memBlock.buffer[750])*256 + (__int8_t)(memBlock.buffer[751]) );
//					// Ceiling                  (32 bit)
//					uwflora.fCeiling			= (__int32_t)( (__int8_t)(memBlock.buffer[752])*65536 + (__int8_t)(memBlock.buffer[753])*4096 + (__int8_t)(memBlock.buffer[754])*256 + (__int8_t)(memBlock.buffer[755]) );
//
//					// Scale                    (32 bit)
//					grass.fScale					= (__uint32_t)( (__uint8_t)(memBlock.buffer[756])*65536 + (__uint8_t)(memBlock.buffer[757])*4096 + (__uint8_t)(memBlock.buffer[758])*256 + (__uint8_t)(memBlock.buffer[759]) );
//					// Max width                (32 bit)
//			//    (__uint32_t)0));
//					// Min width                (32 bit)
//			//    (__uint32_t)0));
//					// Min height               (32 bit)
//					grass.iMinHeight			= (__uint32_t)( (__uint8_t)(memBlock.buffer[760])*65536 + (__uint8_t)(memBlock.buffer[761])*4096 + (__uint8_t)(memBlock.buffer[762])*256 + (__uint8_t)(memBlock.buffer[763]) );
//					// Max height               (32 bit)
//					grass.iMaxHeight			= (__uint32_t)( (__uint8_t)(memBlock.buffer[764])*65536 + (__uint8_t)(memBlock.buffer[765])*4096 + (__uint8_t)(memBlock.buffer[766])*256 + (__uint8_t)(memBlock.buffer[767]) );
//					// Height Variation         (32 bit)
//					grass.iVariation			= (__uint32_t)( (__uint8_t)(memBlock.buffer[768])*65536 + (__uint8_t)(memBlock.buffer[769])*4096 + (__uint8_t)(memBlock.buffer[770])*256 + (__uint8_t)(memBlock.buffer[771]) );
//					// Thickness                (32 bit)
//					grass.fThickness			= float( (__uint8_t)(memBlock.buffer[772])*65536 + (__uint8_t)(memBlock.buffer[773])*4096 + (__uint8_t)(memBlock.buffer[774])*256 + (__uint8_t)(memBlock.buffer[775]) )/10.0f;
//					// Number                   (32 bit)
//					grass.iNum						= (__uint32_t)( (__uint8_t)(memBlock.buffer[776])*65536 + (__uint8_t)(memBlock.buffer[777])*4096 + (__uint8_t)(memBlock.buffer[778])*256 + (__uint8_t)(memBlock.buffer[779]) );
//					// Rate                     (32 bit)
//					grass.iRate						= (__uint32_t)( (__uint8_t)(memBlock.buffer[780])*65536 + (__uint8_t)(memBlock.buffer[781])*4096 + (__uint8_t)(memBlock.buffer[782])*256 + (__uint8_t)(memBlock.buffer[783]) );
//					// Range                    (32 bit)
//					grass.iRange					= (__uint32_t)( (__uint8_t)(memBlock.buffer[784])*65536 + (__uint8_t)(memBlock.buffer[785])*4096 + (__uint8_t)(memBlock.buffer[786])*256 + (__uint8_t)(memBlock.buffer[787]) );
//					// Threshold                (32 bit)
//					grass.iThreshold			= (__uint32_t)( (__uint8_t)(memBlock.buffer[788])*65536 + (__uint8_t)(memBlock.buffer[789])*4096 + (__uint8_t)(memBlock.buffer[790])*256 + (__uint8_t)(memBlock.buffer[791]) );
//					// Instance                 (32 bit)
//					grass.iInstance				= (__uint32_t)( (__uint8_t)(memBlock.buffer[792])*65536 + (__uint8_t)(memBlock.buffer[793])*4096 + (__uint8_t)(memBlock.buffer[794])*256 + (__uint8_t)(memBlock.buffer[795]) );
//					// Spread                   (32 bit)
//					grass.fSpread					= (__uint32_t)( (__uint8_t)(memBlock.buffer[796])*65536 + (__uint8_t)(memBlock.buffer[797])*4096 + (__uint8_t)(memBlock.buffer[798])*256 + (__uint8_t)(memBlock.buffer[799]) );
//					// Floorplay                (32 bit)
//					grass.fFloorPlay			= (__uint32_t)( (__uint8_t)(memBlock.buffer[800])*65536 + (__uint8_t)(memBlock.buffer[801])*4096 + (__uint8_t)(memBlock.buffer[802])*256 + (__uint8_t)(memBlock.buffer[803]) );
//					// Floor                    (32 bit)
//					grass.fFloor					= (__int32_t)( (signed int)(memBlock.buffer[804])*65536 + (signed int)(memBlock.buffer[805])*4096 + (signed int)(memBlock.buffer[806])*256 + (signed int)(memBlock.buffer[807]) );
//					// Skew                     (32 bit)
//					grass.fSkew						= (__uint32_t)( (__uint8_t)(memBlock.buffer[808])*65536 + (__uint8_t)(memBlock.buffer[809])*4096 + (__uint8_t)(memBlock.buffer[810])*256 + (__uint8_t)(memBlock.buffer[811]) );
//					grass.bLine						= true;
//
//
//					// Water texture            (28 bytes)
//		//			sText = ""; for(int j=812;j<840; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//		//			water.sTexture				= sText;
//		//			// Water bump               (28 bytes)
//		//			sText = ""; for(int j=840;j<868; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//		//			water.sBump						= sText;
//		//			// Water specular           (28 bytes)
//		//			sText = ""; for(int j=868;j<896; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//		//			water.sSpec						= sText;
//		//			// Water world              (28 bytes)
//		//			sText = ""; for(int j=896;j<924; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//		//			water.sWorld					= sText;
//		//			// Ix                       (32 bit)
//		//			water.iX							= (__uint32_t)( (__uint8_t)(memBlock.buffer[924])*65536 + (__uint8_t)(memBlock.buffer[925])*4096 + (__uint8_t)(memBlock.buffer[926])*256 + (__uint8_t)(memBlock.buffer[927]) );
//		//			// Iz                       (32 bit)
//		//			water.iZ							= (__uint32_t)( (__uint8_t)(memBlock.buffer[928])*65536 + (__uint8_t)(memBlock.buffer[929])*4096 + (__uint8_t)(memBlock.buffer[930])*256 + (__uint8_t)(memBlock.buffer[931]) );
//		//			// Range                    (32 bit)
//		//			water.fRange					= (__uint32_t)( (__uint8_t)(memBlock.buffer[932])*65536 + (__uint8_t)(memBlock.buffer[933])*4096 + (__uint8_t)(memBlock.buffer[934])*256 + (__uint8_t)(memBlock.buffer[935]) );
//		//			// Scale                    (32 bit)
//		//			water.fScale					= (__uint32_t)( (__uint8_t)(memBlock.buffer[936])*65536 + (__uint8_t)(memBlock.buffer[937])*4096 + (__uint8_t)(memBlock.buffer[938])*256 + (__uint8_t)(memBlock.buffer[939]) );
//		//			// Rate                     (32 bit)
//		//			water.iRate						= (__uint32_t)( (__uint8_t)(memBlock.buffer[940])*65536 + (__uint8_t)(memBlock.buffer[941])*4096 + (__uint8_t)(memBlock.buffer[942])*256 + (__uint8_t)(memBlock.buffer[943]) );
//		//			// R                        (8 bit)
//		//			water.vColor[0]				= (float)( (__uint8_t)(memBlock.buffer[944]) )/255.0f;
//		//			// G                        (8 bit)
//		//			water.vColor[1]				= (float)( (__uint8_t)(memBlock.buffer[945]) )/255.0f;
//		//			// B                        (8 bit)
//		//			water.vColor[2]				= (float)( (__uint8_t)(memBlock.buffer[946]) )/255.0f;
//		//			water.vColor[3]				= 1.0f;
//					// RESERVED                 (8 bit*5)
//					water.sTexture			= "water_tex.jpg";
//					water.sBump 			= "water_bump.png";
//					water.sSpec 			= "water_spec.png";
//					water.sWorld			= "water_world.png";
//					water.fFloor			= gameVars->world.water.iHeight;
//					water.iX				= (gameVars->screen.iTerrainGrid/2)*1024+512;
//					water.iZ				= (gameVars->screen.iTerrainGrid/2)*1024+512;
//					water.fRange			= 64; //(64 meters * 16 units = 1024 units)
//					//water.fScale			= 128;
//					water.fScale			= ((float)gameVars->screen.iTerrainGrid/2)*32*gameVars->screen.iScale;
//					water.vColor[0]			= 0.0;
//					water.vColor[1]			= 0.2;
//					water.vColor[2]			= 0.5;
//					water.vColor[3]			= 0.5;
//					water.iRate				= 10;
//					water.fSpeed			= 0.0001f;
//					water.bEnable			= true;
//
//					// This needs to be after water so we can use the water floor for calculation
//					grass.bEnable			= false;
//					grass.fScale			= 1.0f;
//					grass.iMinHeight		= 0;
//					grass.iMaxHeight		= 4;
//					grass.iVariation		= 2;
//					grass.fThickness		= 0.2f;
//					grass.iNum				= 0;
//					grass.iRate				= 1000;
//					grass.iRange			= 3;
//					grass.iThreshold		= 1;
//					grass.iInstance			= 30000;	//500
//					grass.fSpread			= 8;	//8.5
//					grass.fFloor			= (water.fFloor*gameVars->screen.iScale)/2.0f;
//					//grass.fFloorPlay		= grass.fFloor/2.0f;
//					grass.fFloorPlay		= grass.fFloor;
//					grass.fSkew				= 0.2;
//					grass.bLine				= true;
//
//					// World Fog: R             (8 bit)
//					fog.world.vColor[0]		= (__uint8_t)( (__uint8_t)(memBlock.buffer[952]) );
//					// World Fog: G             (8 bit)
//					fog.world.vColor[1]		= (__uint8_t)( (__uint8_t)(memBlock.buffer[953]) );
//					// World Fog: B             (8 bit)
//					fog.world.vColor[2]		= (__uint8_t)( (__uint8_t)(memBlock.buffer[954]) );
//					// Start                    (32 bit)
//					fog.world.uiStart			= (__uint32_t)( (__uint8_t)(memBlock.buffer[955])*65536 + (__uint8_t)(memBlock.buffer[956])*4096 + (__uint8_t)(memBlock.buffer[957])*256 + (__uint8_t)(memBlock.buffer[958]) );
//					// End                      (32 bit)
//					fog.world.uiEnd				= (__uint32_t)( (__uint8_t)(memBlock.buffer[959])*65536 + (__uint8_t)(memBlock.buffer[960])*4096 + (__uint8_t)(memBlock.buffer[961])*256 + (__uint8_t)(memBlock.buffer[962]) );
//					// Density                  (32 bit)
//					fog.world.fDensity		= (float)(1/( (__uint8_t)(memBlock.buffer[963])*65536 + (__uint8_t)(memBlock.buffer[964])*4096 + (__uint8_t)(memBlock.buffer[965])*256 + (__uint8_t)(memBlock.buffer[966]) ));
//					// Equation                 (32 bit)
//					fog.world.uiEquation	= (__uint32_t)( (__uint8_t)(memBlock.buffer[967])*65536 + (__uint8_t)(memBlock.buffer[968])*4096 + (__uint8_t)(memBlock.buffer[969])*256 + (__uint8_t)(memBlock.buffer[970]) );
//					// World Fog: Alpha
//					fog.world.vColor[3]		= (__uint8_t)( (__uint8_t)(memBlock.buffer[971]) );
//					// RESERVED                 (8 bit*9)
//			//    (__uint8_t)0), 9);
//					// Water Fog: R             (8 bit)
//					fog.water.vColor[0]		= (__uint8_t)( (__uint8_t)(memBlock.buffer[980]) );
//					// Water Fog: G             (8 bit)
//					fog.water.vColor[1]		= (__uint8_t)( (__uint8_t)(memBlock.buffer[981]) );
//					// Water Fog: B             (8 bit)
//					fog.water.vColor[2]		= (__uint8_t)( (__uint8_t)(memBlock.buffer[982]) );
//					// Start                    (32 bit)
//					fog.water.uiStart			= (__uint32_t)( (__uint8_t)(memBlock.buffer[983])*65536 + (__uint8_t)(memBlock.buffer[984])*4096 + (__uint8_t)(memBlock.buffer[985])*256 + (__uint8_t)(memBlock.buffer[986]) );
//					// End                      (32 bit)
//					fog.water.uiEnd				= (__uint32_t)( (__uint8_t)(memBlock.buffer[987])*65536 + (__uint8_t)(memBlock.buffer[988])*4096 + (__uint8_t)(memBlock.buffer[989])*256 + (__uint8_t)(memBlock.buffer[990]) );
//					// Density                  (32 bit)
//					fog.water.fDensity		= (float)(1/( (__uint8_t)(memBlock.buffer[991])*65536 + (__uint8_t)(memBlock.buffer[992])*4096 + (__uint8_t)(memBlock.buffer[993])*256 + (__uint8_t)(memBlock.buffer[994]) ));
//					// Equation                 (32 bit)
//					fog.water.uiEquation	= (__uint32_t)( (__uint8_t)(memBlock.buffer[995])*65536 + (__uint8_t)(memBlock.buffer[996])*4096 + (__uint8_t)(memBlock.buffer[997])*256 + (__uint8_t)(memBlock.buffer[998]) );
//					// World Fog : Alpha
//					fog.water.vColor[3]		= (__uint8_t)( (__uint8_t)(memBlock.buffer[999]) );
//					// RESERVED                 (8 bit*9)
//			//    (__uint8_t)0), 9);
//
//					// Spring Underwater        (28 bytes)
//					sText = ""; for(int j=1008;j<1036; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Spring Underwater steep  (28 bytes)
//					sText = ""; for(int j=1036;j<1064; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Spring Sea               (28 bytes)
//					sText = ""; for(int j=1064;j<1092; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Spring Sea steep         (28 bytes)
//					sText = ""; for(int j=1092;j<1120; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Spring Low               (28 bytes)
//					sText = ""; for(int j=1120;j<1148; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Spring Low Steep         (28 bytes)
//					sText = ""; for(int j=1148;j<1176; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Spring Mid               (28 bytes)
//					sText = ""; for(int j=1176;j<1204; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Spring Mid Steep         (28 bytes)
//					sText = ""; for(int j=1204;j<1232; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Spring High              (28 bytes)
//					sText = ""; for(int j=1232;j<1260; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Spring High Steep        (28 bytes)
//					sText = ""; for(int j=1260;j<1288; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Spring Mountain          (28 bytes)
//					sText = ""; for(int j=1288;j<1316; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Spring Mountain Steep    (28 bytes)
//					sText = ""; for(int j=1316;j<1344; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//
//					// Summer Underwater        (28 bytes)
//					sText = ""; for(int j=1344;j<1372; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Summer Underwater steep  (28 bytes)
//					sText = ""; for(int j=1372;j<1400; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Summer Sea               (28 bytes)
//					sText = ""; for(int j=1400;j<1428; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Summer Sea steep         (28 bytes)
//					sText = ""; for(int j=1428;j<1456; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Summer Low               (28 bytes)
//					sText = ""; for(int j=1456;j<1484; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Summer Low Steep         (28 bytes)
//					sText = ""; for(int j=1484;j<1512; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Summer Mid               (28 bytes)
//					sText = ""; for(int j=1512;j<1540; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Summer Mid Steep         (28 bytes)
//					sText = ""; for(int j=1540;j<1568; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Summer High              (28 bytes)
//					sText = ""; for(int j=1568;j<1596; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Summer High Steep        (28 bytes)
//					sText = ""; for(int j=1596;j<1624; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Summer Mountain          (28 bytes)
//					sText = ""; for(int j=1624;j<1652; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Summer Mountain Steep    (28 bytes)
//					sText = ""; for(int j=1652;j<1680; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//
//					// Fall Underwater        (28 bytes)
//					sText = ""; for(int j=1680;j<1708; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Fall Underwater steep  (28 bytes)
//					sText = ""; for(int j=1708;j<1736; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Fall Sea               (28 bytes)
//					sText = ""; for(int j=1736;j<1764; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Fall Sea steep         (28 bytes)
//					sText = ""; for(int j=1764;j<1792; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Fall Low               (28 bytes)
//					sText = ""; for(int j=1792;j<1820; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Fall Low Steep         (28 bytes)
//					sText = ""; for(int j=1820;j<1848; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Fall Mid               (28 bytes)
//					sText = ""; for(int j=1848;j<1876; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Fall Mid Steep         (28 bytes)
//					sText = ""; for(int j=1876;j<1904; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Fall High              (28 bytes)
//					sText = ""; for(int j=1904;j<1932; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Fall High Steep        (28 bytes)
//					sText = ""; for(int j=1932;j<1960; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Fall Mountain          (28 bytes)
//					sText = ""; for(int j=1960;j<1988; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Fall Mountain Steep    (28 bytes)
//					sText = ""; for(int j=1988;j<2016; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//
//					// Winter Underwater        (28 bytes)
//					sText = ""; for(int j=2016;j<2044; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Winter Underwater steep  (28 bytes)
//					sText = ""; for(int j=2044;j<2072; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Winter Sea               (28 bytes)
//					sText = ""; for(int j=2072;j<2100; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Winter Sea steep         (28 bytes)
//					sText = ""; for(int j=2100;j<2128; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Winter Low               (28 bytes)
//					sText = ""; for(int j=2128;j<2156; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Winter Low Steep         (28 bytes)
//					sText = ""; for(int j=2156;j<2184; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Winter Mid               (28 bytes)
//					sText = ""; for(int j=2184;j<2212; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Winter Mid Steep         (28 bytes)
//					sText = ""; for(int j=2212;j<2240; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Winter High              (28 bytes)
//					sText = ""; for(int j=2240;j<2268; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Winter High Steep        (28 bytes)
//					sText = ""; for(int j=2268;j<2296; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Winter Mountain          (28 bytes)
//					sText = ""; for(int j=2296;j<2324; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//					// Winter Mountain Steep    (28 bytes)
//					sText = ""; for(int j=2324;j<2352; j++) if (memBlock.buffer[j] != 0) sText = sText + memBlock.buffer[j];
//				}
//			if (gameVars->debug.load) std::cout << "Done." <<  std::endl;

			Core::debug.print(" Done ", Core::debug().GREEN);
			Core::debug.print("}\n");
			return true;
		}

		bool Atmosphere::load() {
			Core::debug.log("Load Atmosphere {\n");
			Core::debug.logIncreaseIndent();

			Core::debug.log("Textures {\n");
			Core::debug.logIncreaseIndent();

			MemBlock memBlock;
			std::string theImage;
			skybox.tex.Begin(NUM_TEXTURES);

			std::string	sDirectory		= "./texture/atmosphere/";
			char * cFilename			= (char*)"./system/skybox.bin";
			int	iRecordSize				= 32;

			readFile(cFilename, memBlock); //Read the data file into memory

			// Iterate through each record in the file
			for (int d=0; d<memBlock.size; d+=iRecordSize) {
				int theId = 0;
				for (int i=0; i<4; i++) theId+=(unsigned char)memBlock.buffer[i+d];
				theImage = "";
				for (int i=4; i<32; i++) if (memBlock.buffer[i+d]!=0) theImage+=(unsigned char)memBlock.buffer[i+d]; else break;
				//if (gameVars->debug.load)
				//std::cout << " [" << theId << "] " <<  theImage << std::endl;
				//skybox.tex.Load(sDirectory, theImage, theId, true, (GLenum)GL_NEAREST, (GLenum)GL_REPEAT);
				skybox.tex.Load(sDirectory, theImage, theId, true, (GLenum)GL_NONE, (GLenum)GL_REPEAT);

				Core::debug.log("["+std::to_string(theId)+"] "+theImage+"\n", Core::debug().YELLOW);
			}

			Core::debug.logDecreaseIndent();
			Core::debug.log("}\n");

			Core::debug.log("Troposphere\n", Core::debug().YELLOW);
			{
				/*
				 * Load the Troposphere
				 */
				std::string loadFile;
				std::stringstream sStream;
				Core::PLY_Loader loadPly;

				sStream.str("./ply/troposphere.ply");
				loadFile=sStream.str();
				//std::cout << "LOADING ATMOSPHERE PLY FILE: " << loadFile << std::endl;
				//if (gameVars->debug.load) std::cout << " -Loading " <<  loadFile << "...";
				loadPly.load(loadFile);
				//if (gameVars->debug.load)
				//std::cout << "[" <<  loadPly.numDrawVerts << "]...";
				skybox.troposphere.vao.Begin(GL_TRIANGLES,	loadPly.numVerts,	loadPly.numDrawVerts, 1);
				skybox.troposphere.vao.CopyData(GLA_VERTEX,		loadPly.vVerts);
				skybox.troposphere.vao.CopyData(GLA_NORMAL,		loadPly.vNorms);
				skybox.troposphere.vao.CopyData(GLA_TEXTURE,	loadPly.vCoords, 0);
				skybox.troposphere.vao.CopyData(GLA_INDEX,		loadPly.vIndex, loadPly.numDrawVerts);
				skybox.troposphere.vao.End();
				//std::cout << "Done" << std::endl;
			}

			Core::debug.log("Stratosphere\n", Core::debug().YELLOW);
			{
				/*
				 * Load the Stratosphere
				 */
				std::string loadFile;
				std::stringstream sStream;
				Core::PLY_Loader loadPly;

				sStream.str("./ply/stratosphere.ply");
				loadFile=sStream.str();
				//if (gameVars->debug.load)
				//std::cout << " -Loading " <<  loadFile << "...";
				loadPly.load(loadFile);
				//if (gameVars->debug.load)
				//std::cout << "[" <<  loadPly.numDrawVerts << "]...";
				skybox.stratosphere.vao.Begin(GL_TRIANGLES,	loadPly.numVerts,	loadPly.numDrawVerts, 1);
				skybox.stratosphere.vao.CopyData(GLA_VERTEX,	loadPly.vVerts);
				skybox.stratosphere.vao.CopyData(GLA_NORMAL,	loadPly.vNorms);
				skybox.stratosphere.vao.CopyData(GLA_TEXTURE,	loadPly.vCoords, 0);
				skybox.stratosphere.vao.CopyData(GLA_INDEX,		loadPly.vIndex, loadPly.numDrawVerts);
				skybox.stratosphere.vao.End();
				//std::cout << "Done" << std::endl;
			}

			Core::debug.log("Thermosphere\n", Core::debug().YELLOW);
			{
				/*
				 * Load the Thermosphere
				 */
				std::string loadFile;
				std::stringstream sStream;
				Core::PLY_Loader loadPly;

				sStream.str("./ply/thermosphere.ply");
				loadFile=sStream.str();
				//if (gameVars->debug.load)
				//std::cout << " -Loading " <<  loadFile << "...";
				loadPly.load(loadFile);
				//if (gameVars->debug.load)
				//std::cout << "[" <<  loadPly.numDrawVerts << "]...";
				skybox.thermosphere.vao.Begin(GL_TRIANGLES,	loadPly.numVerts,	loadPly.numDrawVerts, 1);
				skybox.thermosphere.vao.CopyData(GLA_VERTEX,	loadPly.vVerts);
				skybox.thermosphere.vao.CopyData(GLA_NORMAL,	loadPly.vNorms);
				skybox.thermosphere.vao.CopyData(GLA_TEXTURE,	loadPly.vCoords, 0);
				skybox.thermosphere.vao.CopyData(GLA_INDEX,		loadPly.vIndex, loadPly.numDrawVerts);
				skybox.thermosphere.vao.End();
				//std::cout << "Done" << std::endl;
			}

			Core::debug.log("Exosphere\n", Core::debug().YELLOW);
			{
				/*
				 * Load the Exosphere
				 */
				std::string loadFile;
				std::stringstream sStream;
				Core::PLY_Loader loadPly;

				if (skybox.exosphere.bCubeMap) sStream.str("./ply/exosphere_cube.ply");
				else sStream.str("./ply/exosphere.ply");
				loadFile=sStream.str();
				//if (gameVars->debug.load)
				//std::cout << " -Loading " <<  loadFile << "...";
				loadPly.load(loadFile);
				//if (gameVars->debug.load)
				//std::cout << "[" <<  loadPly.numDrawVerts << "]...";
				skybox.exosphere.vao.Begin(GL_TRIANGLES,		loadPly.numVerts,	loadPly.numDrawVerts, 1);
				skybox.exosphere.vao.CopyData(GLA_VERTEX,		loadPly.vVerts);
				skybox.exosphere.vao.CopyData(GLA_NORMAL,		loadPly.vNorms);
				skybox.exosphere.vao.CopyData(GLA_TEXTURE,		loadPly.vCoords, 0);
				skybox.exosphere.vao.CopyData(GLA_INDEX,		loadPly.vIndex, loadPly.numDrawVerts);
				skybox.exosphere.vao.End();
				//std::cout << "Done" << std::endl;
			}

			Core::debug.log("Sun (Incomplete Loader)\n", Core::debug().RED);
			// Satellite
			{
				// TODO: Instead of Load, create an AddSatellite function
				/*
				 * Read satellite.bin which should contain all of the setup data
				 * for ALL satellites a well as satellite specific textures. Each
				 * satellite will load its own texture and lens flares.
				 *
				 * Put all data into satellite defined struct, then pass
				 * that struct to satellite.load()
				 *
				 * Keep satellites in a vector
				 */
				//_Satellite newSatellite;
				//satellite.push_back(newSatellite);
				_SatelliteData *data = new _SatelliteData();

				// =======================
				//	SUN
				// -----------------------
				data->sName						= "Sun";

				data->bQuery					= true;

				data->vPosition[0] 				= 0.0;
				data->vPosition[1] 				= 200.0;
				data->vPosition[2] 				= 0.0;

				data->vAmbientBase[0] 			= 0.1f;
				data->vAmbientBase[1] 			= 0.1f;
				data->vAmbientBase[2] 			= 0.1f;
				data->vAmbientBase[3] 			= 1.0f;

				data->vAmbientColor[0] 			= data->vAmbientBase[0];
				data->vAmbientColor[1] 			= data->vAmbientBase[1];
				data->vAmbientColor[2] 			= data->vAmbientBase[2];
				data->vAmbientColor[3] 			= data->vAmbientBase[3];

				data->vDiffuseBase[0] 			= 1.0f;
				data->vDiffuseBase[1] 			= 0.0f;
				data->vDiffuseBase[2] 			= 0.0f;
				data->vDiffuseBase[3]			= 1.0f;

				data->vDiffuseColor[0] 			= data->vDiffuseBase[0];
				data->vDiffuseColor[1]		 	= data->vDiffuseBase[1];
				data->vDiffuseColor[2]	 		= data->vDiffuseBase[2];
				data->vDiffuseColor[3]	 		= data->vDiffuseBase[3];

				data->vSpecularBase[0]			= 1.0f;
				data->vSpecularBase[1]			= 1.0f;
				data->vSpecularBase[2]			= 1.0f;
				data->vSpecularBase[3]			= 1.0f;

				data->vSpecularColor[0] 		= data->vSpecularBase[0];
				data->vSpecularColor[1] 		= data->vSpecularBase[1];
				data->vSpecularColor[2] 		= data->vSpecularBase[2];
				data->vSpecularColor[3] 		= data->vSpecularBase[3];

				data->fShinyBase				= 1.0f;
				data->fShiny					= data->fShinyBase;
				data->degAzimuth.degrees		= 0.0f;
				data->fAltitude					= 80.0f;
				data->fQuadSize					= 16;
				data->fDistance					= 1000.0f;
				data->degInclination.degrees	= -23.5f;
//					data->degInclination.degrees	= 0.0f;

				data->sImage					= "sun_00.png";
				data->sFlare[0]					= "tex6.png";
				data->sFlare[1]					= "tex4.png";
				data->sFlare[2]					= "tex2.png";
				data->sFlare[3]					= "tex7.png";
				data->sFlare[4]					= "tex3.png";
				data->sFlare[5]					= "tex5.png";
				data->sFlare[6]					= "tex4.png";
				data->sFlare[7]					= "tex8.png";
				data->sFlare[8]					= "tex9.png";
				data->fSpeed					= 2.0f;
				data->fScale					= 10.0f;

//					data->vFlarePos[0].z			= 100*0.5f;
//					data->vFlarePos[1].z			= 100*0.23f;
//					data->vFlarePos[2].z			= 100*0.1f;
//					data->vFlarePos[3].z			= 100*0.05f;
//					data->vFlarePos[4].z			= 100*0.06f;
//					data.vFlarePos[5].z				= 100*0.07f;
//					data.vFlarePos[6].z				= 100*0.4f;
//					data.vFlarePos[7].z				= 100*0.6f;
//					data.vFlarePos[8].z				= 100*0.05f;

				satellite->add(data);
			}

			Core::debug.log("Moon (Incomplete Loader)\n", Core::debug().RED);
			{
				// =======================
				//	MOON
				// -----------------------
				_SatelliteData *data = new _SatelliteData();

				data->sName						= "Moon";

				data->bQuery					= false;

				data->vPosition[0] 				= 0.0;
				data->vPosition[1] 				= 200.0;
				data->vPosition[2] 				= 0.0;

				data->vAmbientBase[0] 			= 0.1f;
				data->vAmbientBase[1] 			= 0.1f;
				data->vAmbientBase[2] 			= 0.1f;
				data->vAmbientBase[3] 			= 1.0f;

				data->vAmbientColor[0] 			= data->vAmbientBase[0];
				data->vAmbientColor[1] 			= data->vAmbientBase[1];
				data->vAmbientColor[2] 			= data->vAmbientBase[2];
				data->vAmbientColor[3] 			= data->vAmbientBase[3];

				data->vDiffuseBase[0] 			= 1.0f;
				data->vDiffuseBase[1] 			= 0.0f;
				data->vDiffuseBase[2] 			= 0.0f;
				data->vDiffuseBase[3]			= 1.0f;

				data->vDiffuseColor[0] 			= data->vDiffuseBase[0];
				data->vDiffuseColor[1] 			= data->vDiffuseBase[1];
				data->vDiffuseColor[2] 			= data->vDiffuseBase[2];
				data->vDiffuseColor[3] 			= data->vDiffuseBase[3];

				data->vSpecularBase[0]			= 1.0f;
				data->vSpecularBase[1]			= 1.0f;
				data->vSpecularBase[2]			= 1.0f;
				data->vSpecularBase[3]			= 1.0f;

				data->vSpecularColor[0] 		= data->vSpecularBase[0];
				data->vSpecularColor[1] 		= data->vSpecularBase[1];
				data->vSpecularColor[2] 		= data->vSpecularBase[2];
				data->vSpecularColor[3] 		= data->vSpecularBase[3];

				data->fShinyBase				= 1.0f;
				data->fShiny					= data->fShinyBase;
				data->degAzimuth.degrees		= 90.0f;
				data->fAltitude					= 80.0f;
				data->fQuadSize					= 16;
				data->fDistance					= 500.0f;
				data->degInclination.degrees		= 0.0f;

				data->sImage					= "moon_00.png";
				data->sFlare[0]					= "tex1.png";
				data->sFlare[1]					= "tex2.png";
				data->sFlare[2]					= "tex3.png";
				data->sFlare[3]					= "tex4.png";
				data->sFlare[4]					= "tex5.png";
				data->sFlare[5]					= "tex6.png";
				data->sFlare[6]					= "tex7.png";
				data->sFlare[7]					= "tex8.png";
				data->sFlare[8]					= "tex9.png";
				data->fSpeed					= 10.0f;
				data->fScale					= 5.0f;

				satellite->add(data);
			}

			Core::debug.log("Flora (Incomplete/Outdated)\n", Core::debug().RED);
			// Flora
			{
//					_FloraData data;
//					data.sName				= "Flora";
//					data.vColor				= Vector4f(1.0f);
//					data.fScale				= 1.0f;
//					data.iMaxWidth			= 10;
//					data.iMinWidth			= 4;
//					data.iMaxHeight			= 16;
//					data.iMinHeight			= 4;
//					data.iNum				= 100;
//					data.iRate				= 100;
//					data.iRange				= 1024;
//					data.iThreshold			= 1;
//					data.iInstance			= 0;
//					data.iSpread			= 16;
//					data.fFloorPlay			= 5.0f;
//					data.fFloor				= -4.0f;
//					data.fCeiling			= 1024.0f;
//					flora->add(data);

				_ParticleDataOld data;
				data.eSystem			= PARTICLE_QUAD;
				data.eEmitter			= EMITTER_STATIC;
				data.sName				= "Flora";
				data.vTarget			= &gameVars->player.active->transform.pos;
				data.vColor				= Vector4f(1.0f);
				data.fScale				= 1.0f;
				data.iMaxWidth			= 10;
				data.iMinWidth			= 4;
				data.iMaxHeight			= 16;
				data.iMinHeight			= 4;
				data.iNum				= 100;
				data.iRate				= 500;
				data.iRange				= 1024;
				data.iThreshold			= 1;
				data.iInstance			= 0;
				data.iSpread			= 16;
				data.fFloorPlay			= 5.0f;
				data.fFloor				= -4.0f;
				data.fCeiling			= 1024.0f;
				particlesOld->add(data);


//					Core::sOffset = "12345678";
//					std::cout << std::endl;
//					std::cout << "       String = " << Core::sOffset << std::endl;
//					std::cout << "String Length = " << Core::sOffset.length() << std::endl;
//					std::cout << "        Erase = " << Core::sOffset.length()-5 << std::endl;
				//Core::sOffset.erase(Core::sOffset.length()-4, 4);
//					std::cout << "String Length = " << Core::sOffset.length() << std::endl;
//					std::cout << "       String = " << Core::sOffset << std::endl;
				//Core::sOffset = "    ";
			}

//					else if(mode == FOG) {
//						if (gameVars->debug.load) cout << "## LOAD FOG ##" << endl;
//						if (gameVars->debug.load) cout << "Nothing to do." << endl;
//					}
//					else if(mode == RAIN) {
//						if (gameVars->debug.load) cout << "## LOAD RAIN ##" << endl;
//						if (gameVars->debug.load) cout << "Nothing to do." << endl;
//					}
//					else if(mode == HAIL) {
//						if (gameVars->debug.load) cout << "## LOAD HAIL ##" << endl;
//						if (gameVars->debug.load) cout << "Nothing to do." << endl;
//					}
//					else if(mode == SNOW) {
//						if (gameVars->debug.load) cout << "## LOAD SNOW ##" << endl;
//						snow.tex.Begin(NUM_TEXTURES);
//						std::string	sDirectory		= "./texture/atmosphere/";
//						char * cFilename			= (char*)"snow.bin";
//						int	iRecordSize				= 32;
//						readFile(cFilename, memBlock); //Read the data file into memory
//
//						// Iterate through each record in the file
//						for (int d=0; d<memBlock.size; d+=iRecordSize) {
//							int theId = 0;
//							for (int i=0; i<4; i++) theId+=(unsigned char)memBlock.buffer[i+d];
//							theImage = "";
//							for (int i=4; i<32; i++) if (memBlock.buffer[i+d]!=0) theImage+=(unsigned char)memBlock.buffer[i+d]; else break;
//							if (gameVars->debug.load) std::cout << " [" << theId << "] " <<  theImage << endl;
//							snow.tex.Load(sDirectory, theImage, theId, true, (GLenum)GL_NEAREST, (GLenum)GL_CLAMP_TO_BORDER);
//						}
//						//Vector4f * vVert;		// Modified over time to create falling effect, and turning effects, we also need distance to allow layering
//						//Vector4f vColor;		// Allows for customization
//						//std::string sImage;	// Texture
//						//float fScale;			// Object scale adjustment
//					}
//					else if(mode==UWFLORA) {
//						if (gameVars->debug.load) cout << "## LOAD UNDERWATER FLORA ##" << endl;
//						uwflora.tex.Begin(NUM_TEXTURES);
//						std::string	sDirectory		= "./texture/atmosphere/";
//						char * cFilename			= (char*)"uwflora.bin";
//						int	iRecordSize				= 32;
//						readFile(cFilename, memBlock); //Read the data file into memory
//
//						// Iterate through each record in the file
//						for (int d=0; d<memBlock.size; d+=iRecordSize) {
//							int theId = 0;
//							for (int i=0; i<4; i++) theId+=(unsigned char)memBlock.buffer[i+d];
//							theImage = "";
//							for (int i=4; i<32; i++) if (memBlock.buffer[i+d]!=0) theImage+=(unsigned char)memBlock.buffer[i+d]; else break;
//							if (gameVars->debug.load) std::cout << " [" << theId << "] " <<  theImage << endl;
//							uwflora.tex.Load(sDirectory, theImage, theId, true, (GLenum)GL_LINEAR_MIPMAP_LINEAR, (GLenum)GL_CLAMP_TO_BORDER);
//						}
//						cout << "Loaded a total of " << uwflora.tex.iLoaded << " textures." << endl;
//						//for(int i=0; i<flora.tex.iLoaded; i++) {
//						//	cout << "mapImage: " << flora.tex.Get(i) << endl;
//						//}
//						//flora.tex.Get(0);
//					}
//					else if(mode==GRASS) {
//						if (gameVars->debug.load) cout << "## LOAD GRASS ##" << endl;
//					}
//					else if(mode==WATER) {
//						if (gameVars->debug.load) printf("## LOAD WATER ##\n");
//						/*
//						 * Load textures
//						 */
//						water.tex.Begin(NUM_TEXTURES);
//
//						std::string	sDirectory		= "./texture/atmosphere/";
//						char * cFilename			= (char*)"water.bin";
//						int	iRecordSize				= 32;
//
//						readFile(cFilename, memBlock); //Read the data file into memory
//
//						// Iterate through each record in the file
//						for (int d=0; d<memBlock.size; d+=iRecordSize) {
//							int theId = 0;
//							for (int i=0; i<4; i++) theId+=(unsigned char)memBlock.buffer[i+d];
//							theImage = "";
//							for (int i=4; i<32; i++) if (memBlock.buffer[i+d]!=0) theImage+=(unsigned char)memBlock.buffer[i+d]; else break;
//							if (gameVars->debug.load) std::cout << " [" << theId << "] " <<  theImage << endl;
//							water.tex.Load(sDirectory, theImage, theId, true, (GLenum)GL_NEAREST, (GLenum)GL_REPEAT);
//						}
//
//						/*
//						 * Load high res mesh
//						 *
//						 */
//						std::string loadFile;
//						std::stringstream sStream;
//						PLY_Loader loadPly;
//
//						sStream.str("./ply/water.ply");
//						loadFile=sStream.str();
//						cout << "Loading [" << loadFile << "]-";
//						loadPly.load(loadFile);
//						cout << "[" << loadPly.numDrawVerts << "][" << loadPly.numVerts << "][" << loadPly.numFaces << "]...";
//
//						/*
//						 * Apply transformations
//						 *
//						 * Create a matrix in the CALC section
//						 */
//						//for(int i=0; i<loadPly.numVerts; i++) {
//						//}
//
//						water.vao[1].Begin(GL_TRIANGLES,	loadPly.numDrawVerts, 1);
//						water.vao[1].CopyData(GLA_VERTEX,	loadPly.vVerts);
//						water.vao[1].CopyData(GLA_NORMAL,	loadPly.vNorms);
//						water.vao[1].CopyData(GLA_TEXTURE,	loadPly.vCoords, 0);
//						water.vao[1].CopyData(GLA_INDEX,	loadPly.vIndex);
//						water.vao[1].End();
//
//						cout << "Done" << endl;
//						cout << "Setting up FBOs..." << endl;
//
//						/*
//						 * Generate FBOs
//						 */
//						//cout << "ERROR HISTORY: " << glGetError() << endl;
//						cout << "\tError History: " << glCheckFramebufferStatus(GL_FRAMEBUFFER) << endl;
//						cout << "\t-----------------------" << endl;
//						cout << "\tReflection...";
//
//						//cout << "##################################################################################" << endl;
//						//cout << "################################### TEST AREA ####################################" << endl;
//						//cout << "##################################################################################" << endl;
//
//						glGenFramebuffers(1, &water.fboReflect[0]);
//						glGenTextures(1, &water.texReflect);
//						glBindFramebuffer(GL_FRAMEBUFFER, water.fboReflect[0]);
//
//						glBindTexture(GL_TEXTURE_2D, water.texReflect);
//						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, water.vViewportSize[0], water.vViewportSize[1], 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
//						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//						glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, water.texReflect, 0);
//
//						glGenRenderbuffers(1, &water.fboReflect[1]);
//						glBindRenderbuffer(GL_RENDERBUFFER, water.fboReflect[1]);
//						glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, water.vViewportSize[0], water.vViewportSize[1]);
//						glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, water.fboReflect[1]);
//
//						GLenum check = glCheckFramebufferStatus(GL_FRAMEBUFFER);
//						switch (check) {
//							case GL_FRAMEBUFFER_COMPLETE:
//								cout << "GL_FRAMEBUFFER_COMPLETE" << endl;
//							break;
//							case GL_FRAMEBUFFER_UNDEFINED:
//								cout << "GL_FRAMEBUFFER_UNDEFINED" << endl;
//							break;
//							case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
//								cout << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT" << endl;
//							break;
//							case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
//								cout << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT" << endl;
//							break;
//							case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
//								cout << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER" << endl;
//							break;
//							case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
//								cout << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER" << endl;
//							break;
//							case GL_FRAMEBUFFER_UNSUPPORTED:
//								cout << "GL_FRAMEBUFFER_UNSUPPORTED" << endl;
//							break;
//							case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
//								cout << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE" << endl;
//							break;
//							case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
//								cout << "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS" << endl;
//							break;
//							default:
//								cout << "UNDEFINED ERROR! [" << check << "]" << endl;
//							break;
//						}
//
//						//cout << "##################################################################################" << endl;
//
//						cout << "\tRefraction...";
//						glGenFramebuffers(1, &water.fboRefract[0]);
//						glGenTextures(1, &water.texRefract);
//						glBindFramebuffer(GL_FRAMEBUFFER, water.fboRefract[0]);
//
//						// Refraction Texture
//						glBindTexture(GL_TEXTURE_2D, water.texRefract);
//						glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, water.vViewportSize[0], water.vViewportSize[1], 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
//						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//						//glDrawBuffer(GL_COLOR_ATTACHMENT0);
//						//glReadBuffer(GL_NONE);
//						glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, water.texRefract, 0);
//
//						// Depth Buffer
//						//glGenRenderbuffers(1, &water.fboRefract[1]);
//						//glBindRenderbuffer(GL_RENDERBUFFER, water.fboRefract[1]);
//						//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, water.vViewportSize[0], water.vViewportSize[1]);
//						//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, water.fboRefract[1]);
//
//						// Depth Texture
//						glGenTextures(1, &water.texDepth);
//						glBindTexture(GL_TEXTURE_2D, water.texDepth);
//						glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, water.vViewportSize[0], water.vViewportSize[1], 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
//						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//						//glDrawBuffer(GL_NONE);
//						//glReadBuffer(GL_NONE);
//						glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, water.texDepth, 0);
//
//						check = glCheckFramebufferStatus(GL_FRAMEBUFFER);
//						switch (check) {
//							case GL_FRAMEBUFFER_COMPLETE:
//								cout << "GL_FRAMEBUFFER_COMPLETE" << endl;
//							break;
//							case GL_FRAMEBUFFER_UNDEFINED:
//								cout << "GL_FRAMEBUFFER_UNDEFINED" << endl;
//							break;
//							case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
//								cout << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT" << endl;
//							break;
//							case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
//								cout << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT" << endl;
//							break;
//							case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
//								cout << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER" << endl;
//							break;
//							case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
//								cout << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER" << endl;
//							break;
//							case GL_FRAMEBUFFER_UNSUPPORTED:
//								cout << "GL_FRAMEBUFFER_UNSUPPORTED" << endl;
//							break;
//							case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
//								cout << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE" << endl;
//							break;
//							case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
//								cout << "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS" << endl;
//							break;
//							default:
//								cout << "UNDEFINED ERROR! [" << check << "]" << endl;
//							break;
//						}
//
//						glBindTexture(GL_TEXTURE_2D, 0);
//
//						// WORKING CODE
//						//GLuint texShadow, fboShadow;
//						//glGenTextures(1, &texShadow);
//						//glBindTexture(GL_TEXTURE_2D, texShadow);
//						//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//						//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//						//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
//						//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
//						//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
//						//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
//						//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, 1);
//						//glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, 800, 600, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
//						//glBindTexture(GL_TEXTURE_2D, 0);
//						// create shadow fbo
//						//glGenFramebuffers(1, &fboShadow);
//						//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboShadow);
//						//glDrawBuffer(GL_NONE);
//						//glReadBuffer(GL_NONE);
//						//glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texShadow, 0);
//
//						cout << "##################################################################################" << endl;
//						cout << "##################################################################################" << endl;
//						cout << "##################################################################################" << endl;
//
//						glBindFramebuffer(GL_FRAMEBUFFER, 0);
//
//						cout << "Done" << endl;
//					}

			Core::debug.logDecreaseIndent();
			Core::debug.log("}\n");
			return true;
		}

		bool Atmosphere::calc() {
			Core::debug.log("Calc Atmosphere {\n");
			Core::debug.logIncreaseIndent();
			for (int n=0; n<MODE_LAST; n++) {
				try {
					calc(n);
				}
				catch(...) {
					std::cout << "Failed" << std::endl;
					return false;
				}
			}
			Core::debug.logDecreaseIndent();
			Core::debug.log("}\n");
			return true;
		}

		bool Atmosphere::calc(uint mode) {
			Core::debug.log("Calc Atmosphere (mode = "+std::to_string(mode)+") {");
			if(mode == MODE_SKYBOX) {
				//if (gameVars->debug.load) std::cout << "## CALC SKYBOX ##" << std::endl;
			}
			else if(mode == MODE_SATELLITE) {
				satellite->calc();
			}
			else if(mode == MODE_FLORA) {
				//flora->calc();
				particlesOld->calc("Flora");
			}
			Core::debug.print(" Done ", Core::debug().GREEN);
			Core::debug.print("}\n");
			return true;
		}

		void Atmosphere::update(uint mode) {
			if(mode == MODE_SKYBOX) {
			}
			else if(mode == MODE_SATELLITE) {
				satellite->update();
			}
			else if(mode == MODE_FLORA) {
//				flora->update();
				particlesOld->update("Flora", false);
			}
//
		}

		void Atmosphere::draw(uint mode, ...) {
			glDisable(GL_CULL_FACE);
			glDisable(GL_DEPTH_TEST);

//			if(mode == MODE_TROPOSPHERE) {
//				glActiveTexture(GL_TEXTURE0);
//				skybox.tex.Set("mountain2.png");
//				glActiveTexture(GL_TEXTURE1);
//				skybox.tex.Set("mountain2_bump.png");
//				//skybox.troposphere.vao.Draw();
//				//glDisable(GL_CULL_FACE);
//				skybox.troposphere.vao.Draw(GLM_DRAW_ELEMENTS);
//
//				glActiveTexture(GL_TEXTURE0);
//				//glEnable(GL_CULL_FACE);
//			}
//			else if(mode == MODE_STRATOSPHERE) {
//
//				/*
//				 * Set cloud texture
//				 */
//				std::string sCloud, sBump;
////				if (snow.bEnable) {
////					sCloud = snow.sCloud;
////					sBump = snow.sBump;
////				}
////				else if (hail.bEnable) {
////					sCloud = hail.sCloud;
////					sBump = hail.sBump;
////				}
////				else if (rain.bEnable) {
////					sCloud = rain.sCloud;
////					sBump = rain.sBump;
////				}
////				else {
//					sCloud = skybox.stratosphere.sCloud;
//					sBump = skybox.stratosphere.sBump;
////				}
//
//				glActiveTexture(GL_TEXTURE0);
//				skybox.tex.Set(sCloud);
//				glActiveTexture(GL_TEXTURE1);
//				skybox.tex.Set(sBump);
//				//skybox.stratosphere.vao.Draw();
//
//				//glActiveTexture(GL_TEXTURE0);
//				//tex.Set("space_00.png");
//				//glActiveTexture(GL_TEXTURE1);
//				//tex.Set("space_00.png");
//
//				//vaoPly.Draw(GLM_DRAW_ELEMENTS);
//				skybox.stratosphere.vao.Draw(GLM_DRAW_ELEMENTS);
//
//				glActiveTexture(GL_TEXTURE0);
//			}
//			else if(mode == MODE_MESOSPHERE) {
//
//			}
//			else if(mode == MODE_THERMOSPHERE) {
//				glActiveTexture(GL_TEXTURE0);
//				skybox.tex.Set("thermo_00.png");
//				glActiveTexture(GL_TEXTURE1);
//				skybox.tex.Set("thermo_01.png");
//				//skybox.thermosphere.vao.Draw();
//				skybox.thermosphere.vao.Draw(GLM_DRAW_ELEMENTS);
//				//glActiveTexture(GL_TEXTURE0);
//			}
//			else if(mode == MODE_EXOSPHERE) {

			matrix->setProjection(Core::Matrix_System::MM_PERSPECTIVE, "atmosphere");

			if(mode == MODE_EXOSPHERE) {

				matrix->Push();
					matrix->Rotate(Core::gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
					matrix->Rotate(Core::gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
					matrix->Rotate(Core::Degrees(10).toRadians(), 1.0, 0.0, 0.0);
					matrix->Rotate(Core::Degrees(Core::timeSys->fTimeRaw).toRadians(), 0.0, 0.0, 1.0);
					matrix->Scale(skybox.exosphere.fScale);
					matrix->SetTransform();
					shader->use(GLS_EXOSPHERE);
					shader->getUniform(GLS_EXOSPHERE);
					glActiveTexture(GL_TEXTURE0);
					skybox.tex.Set(skybox.exosphere.sImage);
					skybox.exosphere.vao.Draw(GLM_DRAW_ELEMENTS);
				matrix->Pop();

//				glActiveTexture(GL_TEXTURE0);
//				skybox.tex.Set(skybox.exosphere.sImage);
//				//skybox.tex.Set("milky_way.jpg");
//				skybox.exosphere.vao.Draw(GLM_DRAW_ELEMENTS);
			}
			else if(mode == MODE_SATELLITE) {
				va_list attributeList;
				va_start(attributeList, mode);
					std::string sType = va_arg(attributeList, char const *);
				va_end(attributeList);

				matrix->Push();
					matrix->Rotate(Core::gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
					matrix->Rotate(Core::gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);

					if (sType=="Moon") matrix->Translate(satellite->getPosition("Sun"));	// TODO: [Atmosphere] Transplate to target object
					matrix->Translate(satellite->getPosition(sType));	// Translate to satellite position relative to current position
					satellite->draw(sType, true);
				matrix->Pop();
			}
			else if(mode == MODE_FLARES) {
				va_list attributeList;
				va_start(attributeList, mode);
					std::string sType = va_arg(attributeList, char const *);
				va_end(attributeList);

				satellite->drawFlare(sType);
			}
			else if(mode == MODE_FLORA) {
				va_list attributeList;
				va_start(attributeList, mode);
					std::string sType = va_arg(attributeList, char const *);
				va_end(attributeList);

				matrix->Push();
					matrix->Rotate(Core::gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
					matrix->Rotate(Core::gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
					matrix->Translate(Core::gameVars->player.active->transform.pos[0], Core::gameVars->player.active->transform.pos[1], Core::gameVars->player.active->transform.pos[2]);
					matrix->Scale(Core::gameVars->screen.fScale);
					matrix->SetTransform();
					shader->use(GLS_FLORA);
					shader->getUniform(GLS_FLORA);
					particlesOld->draw(sType);
				matrix->Pop();
			}

			matrix->setProjection(Core::Matrix_System::MM_PERSPECTIVE, "standard");
//	else if(mode == MOON) {
//		glActiveTexture(GL_TEXTURE0);
//		moon.tex.Set(moon.sImage);
//		moon.vao.Draw();
//	}
//	else if(mode == FOG) {
//
//	}
//	else if(mode == RAIN) {
//		glLineWidth(rain.fScale);
//		rain.vao.Draw();
//		glLineWidth(1.0f);
//	}
//	else if(mode == HAIL) {
//		hail.vao.Draw();
//	}
//	else if(mode == SNOW) {
//		glActiveTexture(GL_TEXTURE0);
//		snow.tex.Set(snow.sImage);
//		snow.vao.Draw();
//	}
//	else if(mode==FLORA) {
//		glActiveTexture(GL_TEXTURE0);
//		//glDisable(GL_CULL_FACE);
//		for(int i=0; i<flora.tex.iLoaded; i++) {
//			flora.tex.Set(i);
//			flora.vao[i].Draw();
//			//if(flora.iInstance == 0) flora.vao[i].Draw();
//			//else flora.vao[i].Draw(GLM_DRAW_ARRAYS_INSTANCED, 1, flora.iInstance);
//		}
//		//glEnable(GL_CULL_FACE);
//	}
//	else if(mode==UWFLORA) {
//		glActiveTexture(GL_TEXTURE0);
//		//glDisable(GL_CULL_FACE);
//		for(int i=0; i<uwflora.tex.iLoaded; i++) {
//			uwflora.tex.Set(i);
//			//cout << flora.tex.Get(i) << endl;
//			uwflora.vao[i].Draw();
//			//if(flora.iInstance == 0) flora.vao[i].Draw();
//			//else flora.vao[i].Draw(GLM_DRAW_ARRAYS_INSTANCED, 1, flora.iInstance);
//		}
//		//glEnable(GL_CULL_FACE);
//	}
//	else if(mode==GRASS) {
//		if(grass.bLine) glLineWidth(grass.fThickness*10);
//		glDisable(GL_CULL_FACE);
//		//grass.vao.Draw();
//		if(grass.iInstance == 0) grass.vao.Draw();
//		else grass.vao.Draw(GLM_DRAW_ARRAYS_INSTANCED, 0, grass.iInstance);
//		if(grass.bLine) glLineWidth(1.0f);
//		glEnable(GL_CULL_FACE);
//	}
//	else if(mode==WATER) {
//		glDisable(GL_CULL_FACE);
//		if(water.bHighRes) {
//			glActiveTexture(GL_TEXTURE0);
//			glBindTexture(GL_TEXTURE_2D, water.texReflect);
//			glActiveTexture(GL_TEXTURE1);
//			glBindTexture(GL_TEXTURE_2D, water.texRefract);
//			glActiveTexture(GL_TEXTURE2);
//			water.tex.Set(water.sWorld);
//			glActiveTexture(GL_TEXTURE3);
//			water.tex.Set(water.sBump);
//			glActiveTexture(GL_TEXTURE4);
//			glBindTexture(GL_TEXTURE_2D, water.texDepth);
//			//glBindTexture(GL_TEXTURE_2D, water.tex.Set(water.sWorld);
//			//glActiveTexture(GL_TEXTURE0);	water.tex.Set(water.sTexture);
//			//if (iShader==GLS_WATER_DIRECTIONAL) {
//				//glActiveTexture(GL_TEXTURE1);	water.tex.Set(water.sBump);
//				//glActiveTexture(GL_TEXTURE2);	water.tex.Set(water.sSpec);
//				//glActiveTexture(GL_TEXTURE3);	water.tex.Set(water.sWorld);
//				glActiveTexture(GL_TEXTURE0);
//			//}
//
//			//vao.Draw();
//			water.vao[1].Draw(GLM_DRAW_ELEMENTS);
//		}
//		else {
//			/*
//			 * LOW RESOLUTION STIPPLING METHOD
//			 *
//			 * Method 1
//			 *   Use a pixelated texture for the random stipple
//			 *   noise pattern. Then randomize the texture
//			 *   coordinate offset. Restrict the update speed
//			 *   of the water so it doesn't go too fast and
//			 *   bog down computation time.
//			 *
//			 * Method 2
//			 *   Use the random number generator in GLSL and
//			 *   try to apply it as a texture.
//			 *
//			 * Method 3
//			 *   Use a perlin noise generator to create a nice
//			 *   water effect that won't look as bad as
//			 *   random noise. This is a heavy calculation
//			 *   though.
//			 */
//		}
//		glEnable(GL_CULL_FACE);
//	}
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
		}
	}
}
#endif /* ATMOSPHERE_H_ */
