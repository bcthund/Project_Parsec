/*
 * satellite.h
 *
 *  Created on: Aug 31, 2019
 *      Author: bcthund
 *
 * Standard Atmosphere extension
 * 	- Init()	Loads shared image data into the tex class and other object data from file
 * 	- Calc()	Creates geometry data such as quads and puts them into associated VAOs
 * 	- Update()	Changes any necessary values or recalculates geometry for dynamic data or time based data
 */

#ifndef HEADERS_GAMESYS_ATMOSPHERE_SATELLITE_H_
#define HEADERS_GAMESYS_ATMOSPHERE_SATELLITE_H_

//#include "../atmosphere.h"
#include "../../core/types.h"
#include "../../core/texture.h"
#include "../../core/vao.h"
#include "../../core/core_functions.h"
#include "../../core/matrix.h"
//#include "../GameTime.h"

namespace Core {
	namespace Sys {
		struct _SatelliteData {
//			Atmosphere		&parent;			// Access to parent class

			std::string		sName;				// Human readable name mapped to index
			bool			bQuery;				// Does this object have an occlusion query
			Vector3f		vPosition;			// Rectangular coordinates of light
			Vector4f		vAmbientBase;		// Ambient light color
			Vector4f		vDiffuseBase;		// Diffuse light color
			Vector4f		vSpecularBase;		// Specular light color
			Vector4f		vAmbientColor;		// Current ambient light color used in shader
			Vector4f		vDiffuseColor;		// Current diffuse light color used in shader
			Vector4f		vSpecularColor;		// Current specular light color used in shader
			float			fShiny;				// General shininess caused by this light
			float			fShinyBase;			// Current shininess used by shader
												// This is an innaccurate use of shininess
												// but we will use it for now.
			uint			iQuadSamples;		// Number of calculated samples, used for occlusion query
			float			fQuadSize;			// Size of the quad the sun is rendered on. Point sprite based so forced to be square
			std::string 	sImage;				// Texture to use for light sprite (sun in this case)
			std::string 	sFlare[9];			// Lens flare textures
			Vector3f		vFlarePos[9];		// flare position AND size
			float			fFlareAlpha;
			float			fSpeed;
			float			fScale;				// The scale of the sprite, original size in-game is 32x32 pixels
			float			fDistance;			// The distance of the light from the player
			Core::Degrees	degAzimuth;			// The angle from zero degrees along the horizon, south is zero degrees
			float			fAltitude;			// The angle above the horizon (calc modified from standard spherical to measure up instead of down)
			Core::Degrees	degInclination;		// TODO: Tilt of the light path, so the sun doesn't pass at 90 degrees above player
			VAO				vao;				// VAO for storing and drawing this entity
			//_Occlusion		occlusion;

//			_SatelliteData(Atmosphere &f) : parent(0), fShiny(0), fShinyBase(0), fLightAzimuth(0), fLightAltitude(0), fLightDistance(0), fScale(0), fLightZenith(0), fFlareAlpha(0), iQuadSamples(0) { };
//			_SatelliteData() : fShiny(0), fShinyBase(0), fLightAzimuth(0), fLightAltitude(0), fLightDistance(0), fScale(0), fLightZenith(0), fFlareAlpha(0), iQuadSamples(0) { };
			_SatelliteData() :	sName(""),
								bQuery(false),
								fShiny(0),
								fShinyBase(0),
								degAzimuth(0),
								fAltitude(0),
								fDistance(0),
								fSpeed(1.0),
								fQuadSize(16),
								fScale(0),
								degInclination(0),
								fFlareAlpha(0),
								iQuadSamples(0) {

									sFlare[0]		= "tex1.png";
									sFlare[1]		= "tex2.png";
									sFlare[2]		= "tex3.png";
									sFlare[3]		= "tex4.png";
									sFlare[4]		= "tex5.png";
									sFlare[5]		= "tex6.png";
									sFlare[6]		= "tex7.png";
									sFlare[7]		= "tex8.png";
									sFlare[8]		= "tex9.png";

//									vFlarePos[0].z = 10;
//									vFlarePos[1].z = 20;
//									vFlarePos[2].z = 30;
//									vFlarePos[3].z = 40;
//									vFlarePos[4].z = 50;
//									vFlarePos[5].z = 60;
//									vFlarePos[6].z = 70;
//									vFlarePos[7].z = 80;
//									vFlarePos[8].z = 90;

								};

			_SatelliteData(const _SatelliteData &data) {
				sName			= data.sName;
				bQuery			= data.bQuery;
				vPosition		= data.vPosition;
				vAmbientBase	= data.vAmbientBase;
				vAmbientColor	= data.vAmbientColor;
				vDiffuseBase	= data.vDiffuseBase;
				vDiffuseColor	= data.vDiffuseColor;
				vSpecularBase	= data.vSpecularBase;
				vSpecularColor	= data.vSpecularColor;
				fShinyBase		= data.fShinyBase;
				fShiny			= data.fShiny;
				degAzimuth		= data.degAzimuth;
				fAltitude		= data.fAltitude;
				fQuadSize		= data.fQuadSize;
				fDistance		= data.fDistance;
				degInclination	= data.degInclination;
				sImage			= data.sImage;
				sFlare[0]		= data.sFlare[0];
				sFlare[1]		= data.sFlare[1];
				sFlare[2]		= data.sFlare[2];
				sFlare[3]		= data.sFlare[3];
				sFlare[4]		= data.sFlare[4];
				sFlare[5]		= data.sFlare[5];
				sFlare[6]		= data.sFlare[6];
				sFlare[7]		= data.sFlare[7];
				sFlare[8]		= data.sFlare[8];
				fSpeed			= data.fSpeed;
				fScale			= data.fScale;
				fFlareAlpha		= data.fFlareAlpha;
				iQuadSamples	= data.iQuadSamples;

				vFlarePos[0].z		= 500*0.5f;
				vFlarePos[1].z		= 500*0.23f;
				vFlarePos[2].z		= 500*0.1f;
				vFlarePos[3].z		= 500*0.05f;
				vFlarePos[4].z		= 500*0.06f;
				vFlarePos[5].z		= 500*0.07f;
				vFlarePos[6].z		= 500*0.4f;
				vFlarePos[7].z		= 500*0.6f;
				vFlarePos[8].z		= 500*0.05f;
//				vFlarePos[0]		= data.vFlarePos[0];
//				vFlarePos[1]		= data.vFlarePos[1];
//				vFlarePos[2]		= data.vFlarePos[2];
//				vFlarePos[3]		= data.vFlarePos[3];
//				vFlarePos[4]		= data.vFlarePos[4];
//				vFlarePos[5]		= data.vFlarePos[5];
//				vFlarePos[6]		= data.vFlarePos[6];
//				vFlarePos[7]		= data.vFlarePos[7];
//				vFlarePos[8]		= data.vFlarePos[8];
			};
			~_SatelliteData() {};
		};

		class _Satellite {
			public:
				//std::vector<_SatelliteData> data;
				//_SatelliteData * data;
				//Core::Map_si	map;
				//Core::Map_is	rmap;
				t_VectorMap<_SatelliteData*> data;

				_Satellite(Sys::Atmosphere &f);
				~_Satellite();
				bool		add(_SatelliteData *data);

				bool		calc();
				bool		calc(std::string name);
				bool		calc(uint id);

				void		update(bool bLensFlare=false);
				void		update(std::string name, bool bLensFlare=false);
				void		update(int id, bool bLensFlare=false);

				void		draw(bool bOcclusion=false);
//				void		draw(_SI siType, bool bOcclusion=false);
				void		draw(std::string name, bool bOcclusion=false);
				void		draw(int id, bool bOcclusion=false);

//				void		drawFlare(_SI siType);
				void		drawFlare(std::string name);
				void		drawFlare(int id);

				Vector3f&	getPosition(std::string name)				{ return getPosition(data.getID(name)); };
				Vector3f&	getPosition(int id)							{ return data[id]->vPosition; };

				void		setPosition(std::string name, Vector3f v)	{ setPosition(data.getID(name), v); };
				void		setPosition(int id, Vector3f v)				{ data[id]->vPosition = v; };

//				float		getAlpha(_SI siType)						{ if(siType.bString) return getAlpha(map[siType.name]); else return getAlpha(siType.id); };
				float		getAlpha(std::string name)					{ return getAlpha(data.getID(name)); };
				float		getAlpha(int id)							{ return data[id]->fFlareAlpha; };


				//data[id]->fFlareAlpha

				float		getScale(std::string name)					{ return getScale(data.getID(name)); };
				float		getScale(int id)							{ return data[id]->fScale; };

				Core::Degrees	getZenith(std::string name)				{ return getZenith(data.getID(name)); };
				Core::Degrees	getZenith(int id)						{ return data[id]->degInclination; };

			private:
				Sys::Atmosphere		&parent;			// Access to parent class
				static bool		bTexLoaded;			// Has the textures file been loaded yet
				static Texture	tex;				// Global textures list, prevents copies of textures
				bool			init();

				//VAO	vaoPoint;
				bool bErrorONS[32];
				int							iNumObjects;
				static const uint			MAX_TEXTURES;
				static const int			MAX_OBJECTS;
				static const uint			RECORD_SIZE;
				static const std::string	DIR;
				static const std::string	FILENAME;
				static const std::string	TEXDIR;
				static const bool			bDebug = false;
		};


		const uint			_Satellite::MAX_TEXTURES	= 32;
		const int			_Satellite::MAX_OBJECTS		= 16;
		const uint			_Satellite::RECORD_SIZE		= 32;
		const std::string	_Satellite::DIR				= "./system/";
		const std::string	_Satellite::FILENAME		= "satellite.bin";
		const std::string	_Satellite::TEXDIR			= "./texture/atmosphere/satellite/";

		_Satellite::_Satellite(Sys::Atmosphere &f) : parent(f) {
			iNumObjects = 0;
			for (int n=0; n<32; n++) {
				bErrorONS[n] = false;
			}
//			data = new _SatelliteData[MAX_OBJECTS];
			init();
		}

		_Satellite::~_Satellite() {
			//delete[] data;
			for (auto & item : data ) {
				delete item;
			}
		}

		bool _Satellite::bTexLoaded = false;
		Texture _Satellite::tex = Texture();

		/*
		 * Load global satellite textures
		 */
		bool _Satellite::init() {
			if (!bTexLoaded) {
				Core::debug.log("Init Satellite {\n");
				Core::debug.logIncreaseIndent();

				MemBlock memBlock;
				std::string theImage;
				int iCount = 0;
				struct _ImageData {
					std::string image;
					int id;
				} imageData[128];

				readFile((DIR+FILENAME), memBlock);

				// Iterate through each record in the file
				for (int d=0; d<memBlock.size; d+=RECORD_SIZE) {
					imageData[iCount].id = 0;
					for (int i=0; i<4; i++) imageData[iCount].id += (unsigned char)memBlock.buffer[i+d];

					imageData[iCount].image = "";
					for (int i=4; i<32; i++) if (memBlock.buffer[i+d]!=0) imageData[iCount].image+=(unsigned char)memBlock.buffer[i+d]; else break;

					iCount++;
				}

				tex.Begin(iCount);
				for(int n=0; n<iCount; n++) {
					//std::cout << "[" << imageData[n].id << ", " << imageData[n].image << "]";
					if (bDebug) std::cout << "[" << imageData[n].id << ":" << imageData[n].image << "]";
					tex.Load(TEXDIR, imageData[n].image, imageData[n].id, true, (GLenum)GL_NEAREST, (GLenum)GL_REPEAT);

					Core::debug.log("["+std::to_string(imageData[n].id)+"] "+imageData[n].image+"\n", Core::debug().YELLOW);
				}

				bTexLoaded = true;

				// TODO: Prepare point VAO for point sprite occlusion
//				Data3f vVerts[]		= { {  0.0,  0.0,  0.0 } };
//				vao.Begin(GL_POINTS, 1, 1, 0);
//				vao.CopyData(GLA_VERTEX, vVerts);
//				vao.End();

				Core::debug.logDecreaseIndent();
				Core::debug.log("}\n");
				return true;
			}
			return false;
		}

		/*
		 * load
		 */
		bool _Satellite::add(_SatelliteData *newData)   {
//			std::cout << sOffset << "[" << newData->sName << "]" << std::endl;

//			if (iNumObjects < MAX_OBJECTS) {
//				//data.push_back(newData);
//				data[iNumObjects] = _SatelliteData(newData);
//				map.insert(make_pair(newData.sName, iNumObjects));
//				rmap.insert(make_pair(iNumObjects, newData.sName));
//				//map.insert(make_pair(newData.sName, data.size()-1));
//				if (data[iNumObjects].bQuery) occlusion->Add(data[iNumObjects].sName, GL_SAMPLES_PASSED);
//				iNumObjects++;
//			}
			data.add(newData->sName, newData);
			if (newData->bQuery) occlusion->add(newData->sName, GL_SAMPLES_PASSED);
			return true;
		}

		bool _Satellite::calc()   {
			try {
//				for (int n=0; n<iNumObjects; n++) {
//					calc(n);
//				}

				for (int n=0; n<data.size(); n++) {
					calc(n);
				}
			}
			catch(...) {
				std::cout << "Exception occurred:" << std::endl << "     bool _Satellite::calc(bool bMultiSample, uint uiSamples)" << std::endl;
				std::exit(0);
			}
			return true;
		}

		bool _Satellite::calc(std::string name)   {
			return calc(data.getID(name));
		}

		bool _Satellite::calc(uint id)   {
			//std::cout << sOffset << "[" << data.getName(id) << "]" << std::endl;

//			Core::debug.log("["+std::to_string(id)+"] "+data.getName(id)+"\n", Core::debug().YELLOW);

			float iHalf = data[id]->fQuadSize*data[id]->fScale;

			if(gameVars->screen.MultiSample) {
				data[id]->iQuadSamples = (data[id]->fQuadSize * data[id]->fQuadSize) * gameVars->screen.bpp;
			} else {
				data[id]->iQuadSamples = (data[id]->fQuadSize * data[id]->fQuadSize);
			}

			gameVars->screen.fScreenAspect;
			gameVars->screen.fDistanceAspect;

			if (data[id]->bQuery) occlusion->SetSamples(data[id]->sName, data[id]->iQuadSamples);

			Data3f vVerts[] = { {-iHalf, -iHalf, 0},
								{ iHalf,  iHalf, 0},
								{-iHalf,  iHalf, 0},

								{-iHalf, -iHalf, 0},
								{ iHalf, -iHalf, 0},
								{ iHalf,  iHalf, 0 }};

			Data2f vTexture[] = {	{ 0, 0 },
									{ 1, 1 },
									{ 0, 1 },
									{ 0, 0 },
									{ 1, 0 },
									{ 1, 1 } };

			data[id]->vao.Begin(GL_TRIANGLES, 6, 6, 1);
			data[id]->vao.CopyData(GLA_VERTEX, vVerts);
			data[id]->vao.CopyData(GLA_TEXTURE, vTexture, 0);
			data[id]->vao.End();
			return true;
		}

		void _Satellite::update(bool bLensFlare) {
			try {
				for (int n=0; n<data.size(); n++) {
					update(n, bLensFlare);
				}
			}
			catch(...) {
				std::cout << "Exception occurred:" << std::endl << "     void _Satellite::update()" << std::endl;
				std::exit(0);
			}
		}

		void _Satellite::update(std::string name, bool bLensFlare) {
			update(data.getID(name), bLensFlare);
		}

		void _Satellite::update(int id, bool bLensFlare) {
			//std::cout << "[Update Satellite]";
			/*
			 * UPDATE THE SUN LOCATION
			 *
			 * Set location via a distance and two angles
			 * d = distance from player (static)
			 * t = theta, azimuth (static)
			 * p = phi, altitude, angle above horizon (time varying)
			 *
			 * x = d*sin(p)*cos(t)
			 * y = d*sin(p)*sin(t)
			 * z = d*cos(t)
			 */

			data[id]->fAltitude = timeSys->fTimeRaw * data[id]->fSpeed;
			//data[id]->fAltitude = 30;

			float	t = Core::Degrees(data[id]->fAltitude).toRadians();
			float	p = data[id]->degAzimuth.toRadians();
			float	d = data[id]->fDistance*data[id]->fScale;
			//float	d = 1;
			float	x =  d*sin(p)*cos(t),
					y =  d*sin(t),
					z =  d*cos(t)*cos(p);

			//Matrix_System tMatrix;
			//parent.
			Vector4f vTempPos = Vector4f(x, y, z, 1.0f);

			Matrix44f mRot;
			mRot.Rotate(data[id]->degInclination.toRadians(), 1.0f, 0.0f, 0.0f);
			vTempPos = mRot * vTempPos;

			data[id]->vPosition.x = vTempPos.x;
			data[id]->vPosition.y = vTempPos.y;
			data[id]->vPosition.z = vTempPos.z;

//				// TODO: This is stupid, fix this
//				float fSunFactor = y/(sun.fLightDistance/4);
//				if(fSunFactor > 1.0f) fSunFactor=1.0f;
//				else if(fSunFactor < 0.0f) fSunFactor=0.0f;
//
//				// TODO: Implement thermosphere blending algorithm
//				if(sun.fLightAltitude < 90) {
//					skybox.thermosphere.fS = fmin(fmax((sun.fLightAltitude+10)/20 , 0.0f), 1.0f);
//					skybox.thermosphere.fD = fmin(fmax((sun.fLightAltitude-10)/15 , 0.0f), 1.0f);
//					skybox.thermosphere.fRot = sun.fLightAzimuth;
//				} else if(sun.fLightAltitude > 270) {
//					skybox.thermosphere.fS = fmin(fmax((sun.fLightAltitude-350)/20 , 0.0f), 1.0f);		// Capture sunrise when altitude rolls past 360 to 0
//					skybox.thermosphere.fD = 0;
//					skybox.thermosphere.fRot = sun.fLightAzimuth;
//				} else {
//					skybox.thermosphere.fS = 1 - fmin(fmax((sun.fLightAltitude-170)/20 , 0.0f), 1.0f);
//					skybox.thermosphere.fD = 1 - fmin(fmax((sun.fLightAltitude-155)/15 , 0.0f), 1.0f);
//					skybox.thermosphere.fRot = sun.fLightAzimuth+180;
//				}

			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

			// Lens Flare calculations
			if (bLensFlare || data[id]->bQuery) {

				Vector2f CENTER_SCREEN = { 0.0, 0.0 };
				float spacing = 0.25;

				matrix->Push();
					matrix->SetIdentity();
					matrix->Rotate(Core::gameVars->player.active->transform.rot.x, 1.0, 0.0, 0.0);
					matrix->Rotate(Core::gameVars->player.active->transform.rot.y, 0.0, 1.0, 0.0);
					matrix->SetTransform();

					Matrix44f &viewMat = matrix->GetModelView();
					Matrix44f &projMat = matrix->GetProjectionMatrix();
					Matrix44f &mvpMat = matrix->GetModelViewProjection();
//					Matrix44f mvpMat = projMat * viewMat;

					// TODO: [SUN} FIX FLARE, WHY CAN'T I GET SCREEN COORDINATES?

					Vector4f vSunPos;
					vSunPos.x =  data[id]->vPosition.x;
					if (data[id]->vPosition.z <= 0.0f) vSunPos.y =  data[id]->vPosition.y;	// TODO: [SUN] Flare Calc Problem, only works N-S
					else vSunPos.y = -data[id]->vPosition.y;
					vSunPos.z =  data[id]->vPosition.z;
					vSunPos.w =  1.0f;
					std::string t = "vCamPos = " + std::to_string(Core::gameVars->player.active->transform.pos[0]) + ", " + std::to_string(Core::gameVars->player.active->transform.pos[1]) + ", " + std::to_string(Core::gameVars->player.active->transform.pos[2]);
					if (bDebug) std::cout << t << std::endl;

					{
						Core::Vector3f a = { 0, 0, 0 };
						Core::Vector3f b;
						if (data[id]->vPosition.z <= 0.0f) b = Vector3f( vSunPos.x, vSunPos.y, vSunPos.z );			// TODO: [SUN] Flare Calc Problem, only works N-S
						else b = Vector3f( vSunPos.x, -vSunPos.y, vSunPos.z );
						Core::helper->drawLine(a, b, 2);
					}

					t = "vSunPos = " + std::to_string(vSunPos.x) + ", " + std::to_string(vSunPos.y) + ", " + std::to_string(vSunPos.z);
					if (bDebug) std::cout << t << std::endl;
//					std::cout << t << std::endl;

					Vector4f sunCoords = mvpMat * vSunPos;

				matrix->Pop();

//				if (sunCoords.z <= 0.0f) {
//					if (bDebug) std::cout << "NOT ON SCREEN!" << std::endl;
//					sunCoords.x =  0.0f;
//					sunCoords.y =  0.0f;
//					sunCoords.z =  0.0f;
//					sunCoords.w =  0.0f;
//				}

				Vector4f sunCoords_w1, sunCoords_w2;
				float brightness = 0;
				Vector3f sunToCenter, sunToCenterNormal;

//				sunCoords_w1.x	=  sunCoords.x;
//				sunCoords_w1.y	=  sunCoords.y;
//				sunCoords_w1.z	=  sunCoords.z;
//				sunCoords_w1.w	=  sunCoords.w;
//				t = "sunCoords = " + std::to_string(sunCoords_w1.x) + ", " + std::to_string(sunCoords_w1.y) + ", " + std::to_string(sunCoords_w1.z) + ", " + std::to_string(sunCoords_w1.w);	//							gameSys.drawText(7, o++, t, Core::gameVars->color.orange);
//				if (bDebug) std::cout << t << std::endl;

				if (data[id]->vPosition.z <= 0.0f) sunCoords_w2.x	= -(sunCoords.x/(sunCoords.w*0.3));		// TODO: [SUN] Flare Calc Problem, only works N-S
				else sunCoords_w2.x	=  (sunCoords.x/(sunCoords.w*0.3));
				sunCoords_w2.y	= -(sunCoords.y/(sunCoords.w*0.325));
//				sunCoords_w2.y	=  (sunCoords.y/(sunCoords.w*0.325));
				sunCoords_w2.z	=  (sunCoords.z/sunCoords.w);		// Depth buffer
				sunCoords_w2.w	=  1.0f;
				t = "sunCoords/w = " + std::to_string(sunCoords_w2.x) + ", " + std::to_string(sunCoords_w2.y) + ", " + std::to_string(sunCoords_w2.z) /*+ ", " + std::to_string(sunCoords_w[3])*/;	//							gameSys.drawText(7, o++, t, Core::gameVars->color.orange);
				if (bDebug) std::cout << t << std::endl;
//				std::cout << t << std::endl;

//				Vector3f sunCoords_n = Vector3f(sunCoords_w2.x, sunCoords_w2.y, sunCoords_w2.z).normal();
//				Vector2f sunCoords_n2 = Vector2f(sunCoords_n.x, sunCoords_n.y).normal();
//				t = "sunCoords_n = " + std::to_string(sunCoords_n2.x) + ", " + std::to_string(sunCoords_n2.y) /* + ", " + std::to_string(sunCoords_n2.z) /*+ ", " + std::to_string(sunCoords_w[3])*/;	//							gameSys.drawText(7, o++, t, Core::gameVars->color.orange);
//				if (bDebug) std::cout << t << std::endl;

				sunToCenterNormal.x = (CENTER_SCREEN.x-sunCoords_w2.x);
				sunToCenterNormal.y = (CENTER_SCREEN.y-sunCoords_w2.y);
				t = "sunToCenterNormal = " + std::to_string(sunToCenterNormal.x) + ", " + std::to_string(sunToCenterNormal.y)/* + ", " + std::to_string(sunToCenter[2])*/;	//							gameSys.drawText(7, o++, t, Core::gameVars->color.green);
				if (bDebug) std::cout << t << std::endl;

				sunToCenter.x = sunToCenterNormal.x * gameVars->screen.half.x;
				sunToCenter.y = sunToCenterNormal.y * gameVars->screen.half.y;
				t = "sunToCenter = " + std::to_string(sunToCenter.x) + ", " + std::to_string(sunToCenter.y)/* + ", " + std::to_string(sunToCenter[2])*/;	//							gameSys.drawText(7, o++, t, Core::gameVars->color.green);
				if (bDebug) std::cout << t << std::endl;

				float sunToCenterLength = sunToCenter.length()/gameVars->screen.res.length();
				t = "sunToCenterLength = " + std::to_string(sunToCenterLength);										//					gameSys.drawText(1, o++, t, Core::gameVars->color.red);
				if (bDebug) std::cout << t << std::endl;

				brightness = fmax(1 - (sunToCenterLength/0.5f), 0.0f);
				t = "brightness = " + std::to_string(brightness);													//					gameSys.drawText(8, o++, t, c);
				if (bDebug) std::cout << t << std::endl;

				t = "samples = " + std::to_string(occlusion->GetSamples(data[id]->sName));
				if (bDebug) std::cout << t << std::endl;

				float ratio = occlusion->GetRatio(data[id]->sName);
				t = "ratio = " + std::to_string(ratio);
				if (bDebug) std::cout << t << std::endl;
				data[id]->fFlareAlpha = brightness * ratio;
				t = "brightness * ratio = " + std::to_string(brightness * ratio);									//			gameSys.drawText(8, o++, t, c);
				if (bDebug) std::cout << t << std::endl;
//
				// DRAW TEST LINES
				// TODO: Remove debug line drawing for flares
				Core::matrix->Push();
//					Core::matrix->SetIdentity();
//					Core::matrix->SetProjection(Core::matrix->MM_ORTHO);
//					Core::Vector3f a = { 0, 0, 0 };
//					Core::Vector3f b = { sunToCenter.x, sunToCenter.y, 0 };
//					Core::helper->drawLine(a, b, 2);

					if (data[id]->fFlareAlpha > 0.0f) {
						Vector2f direction;
						for (int i = 0; i < 9; i++) {
							Core::matrix->Push();
								direction.x = sunToCenterNormal.x;
								direction.y = sunToCenterNormal.y;

								direction.x *= (i*spacing);
								direction.y *= (i*spacing);

								data[id]->vFlarePos[i].x =  ( (sunCoords_w2.x + direction.x) * Core::gameVars->screen.res.x );
								data[id]->vFlarePos[i].y =  ( (sunCoords_w2.y + direction.y) * Core::gameVars->screen.res.y );

								// Debug drawing
//								Core::matrix->Translate(data[id]->vFlarePos[i].x, data[id]->vFlarePos[i].y, 1.0f);
//								Core::matrix->SetTransform();
//								helper->drawPoint(10.0f, Vector4f(0.0, 1.0, 0.0, data[id]->fFlareAlpha), helper->GLPOINT_CIRCLE);
							Core::matrix->Pop();
						}
					}
					Core::matrix->SetProjection(Core::matrix->MM_PERSPECTIVE);
				Core::matrix->Pop();
				if (bDebug) std::cout << std::endl;
//
			}

			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
			// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

			if (data[id]->fAltitude > (360.0f * data[id]->fSpeed)) {
				timeSys->reset();
				data[id]->fAltitude = 0.0f;
			}
		}

		void _Satellite::draw(bool bOcclusion)   {
			try {
				for (int n=0; n<iNumObjects; n++) {
					draw(n, bOcclusion);
				}
			}
			catch(...) {
				std::cout << "Exception occurred:" << std::endl << "     void _Satellite::draw()" << std::endl;
				std::exit(0);
			}
		}

		void _Satellite::draw(std::string name, bool bOcclusion) {
				draw(data.getID(name), bOcclusion);
		}

		void _Satellite::draw(int id, bool bOcclusion) {
			glActiveTexture(GL_TEXTURE0);
			if (bTexLoaded) {
				tex.Set(data[id]->sImage);
			}
			else {
				sysTex->set(sysTex->TEX_TESTPATTERN);
				if (!bErrorONS[0]) {
					std::cout << "ERROR! Satellite textures not loaded, must call _Satellite::init()" << std::endl;
					bErrorONS[0] = true;
				}
			}

			helper->drawPointSprite(data[id]->fQuadSize*data[id]->fScale, 0.0, colors.GetActive(), helper->GLPOINT_SQUARE);

			if (bOcclusion && data[id]->bQuery) {
				occlusion->StartQuery(data[id]->sName, GL_SAMPLES_PASSED);
				glActiveTexture(GL_TEXTURE0);
				sysTex->set(sysTex->TEX_TESTPATTERN);
				helper->drawPointSprite(data[id]->fQuadSize*data[id]->fScale, 0.0, Color(1.0, 1.0, 1.0, 0.0), helper->GLPOINT_SQUARE);
				occlusion->EndQuery(data[id]->sName);
			}
		}

		void _Satellite::drawFlare(std::string name) {
			drawFlare(data.getID(name));
		}

		void _Satellite::drawFlare(int id) {
			// Only draw if query exists
			if (bDebug) std::cout << "Draw Flares...[" << data[id]->fFlareAlpha << "]";
			if (data[id]->bQuery && data[id]->fFlareAlpha > 0.0f) {

				glActiveTexture(GL_TEXTURE0);

				glinit->EnableAdditiveBlending();
				matrix->Push();
				Core::matrix->SetProjection(Core::matrix->MM_ORTHO);
				Core::matrix->SetIdentity();
				for (int n=0; n<9; n++) {
					matrix->Push();
						matrix->Translate(data[id]->vFlarePos[n].x, data[id]->vFlarePos[n].y, 0.0f);
						matrix->SetTransform();
						tex.Set(data[id]->sFlare[n]);
						helper->drawPointSprite(data[id]->vFlarePos[n].z, 0.0, Color(1.0, 1.0, 1.0, data[id]->fFlareAlpha), helper->GLPOINT_CIRCLE);
					matrix->Pop();
				}
				Core::matrix->SetProjection(Core::matrix->MM_PERSPECTIVE);
				matrix->Pop();
				glinit->DisableAdditiveBlending();
			}
			if (bDebug) std::cout << "Done" << std::endl;
		}

	}
}

#endif /* HEADERS_GAMESYS_ATMOSPHERE_SATELLITE_H_ */
