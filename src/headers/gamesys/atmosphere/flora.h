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

#ifndef HEADERS_GAMESYS_ATMOSPHERE_Flora_H_
#define HEADERS_GAMESYS_ATMOSPHERE_Flora_H_

//#include "../atmosphere.h"
#include "../../core/types.h"
#include "../../core/texture.h"
#include "../../core/vao.h"
#include "../../core/core_functions.h"
#include "../../core/matrix.h"
//#include "../GameTime.h"

namespace Core {
	namespace GameSys {
		struct t_FloraData {
			std::string		sName;
			Data3f		**	vVerts;			// Stored particles; first pointer = # of loaded sprites; second pointer = data
			Vector4f	*	vPosition;		// Offset position
			Data3f		**	vSize;			// Randomize sizes, use texcoord input
			Vector4f		vColor;			// Allows for customization, NOT IMPLEMENTED
			float			fScale;			// Object scale adjustment, scale of everything (NOT USED)
			int				iMaxWidth;		// Maximum width
			int				iMinWidth;		// Minimum width
			int				iMaxHeight;		// Maximum height
			int				iMinHeight;		// Minimum height
			int				iRange;			// Maximum range from player for particles
			int				iNum;			// Number of particles requested
			int				iRate;			// Particle Update rate (milliseconds) (Faster rate reduces framerate)
			int				iThreshold;		// Deadspace range around player (don't create particles TOO close)
			float			fLast;			// Last update time
			int				iInstance;		// Number of instances
			int				iSpread;		// Spread of instances around original
			float			fCeiling;		// Level above which spawning cannot occur (i.e. high mountains)
			float			fFloor;			// Level below which spawning cannot occur (i.e. water level)
			float			fFloorPlay;		// UNUSED
			bool 			bEnable;		// Show flora
			VAO			*	vao;

			t_FloraData() {
				sName = "";
				fScale = 0;
				vVerts = nullptr;
				vSize = nullptr;
				vPosition = nullptr;
				vColor[0] = 0;
				vColor[1] = 0;
				vColor[2] = 0;
				vColor[3] = 0;
				iMaxWidth = 0;
				iMinWidth = 0;
				iMaxHeight = 0;
				iMinHeight = 0;
				iNum = 10;
				iRate = 500;
				fLast = 0;
				iRange = 0;
				iThreshold = 0;
				iInstance = 0;
				iSpread = 0;
				fFloorPlay = 0;
				fCeiling = 0;
				fFloor = 0;
				vao = nullptr,
				bEnable = false;
			};

			~t_FloraData() {
				delete[] vVerts;
				delete[] vSize;
				delete vPosition;
				delete vao,
				bEnable = false;
			};
		};

		class Atmosphere;
		//class _GameTime;
		class _Flora /*: private _FloraData*/ {
			public:
//				_FloraData * data;
//				Core::Map_si	map;
//				Core::Map_is	rmap;
				t_VectorMap<t_FloraData*> data;

				_Flora(Atmosphere &f);
				~_Flora();
				bool		add(t_FloraData &data);

				bool		calc(bool bUpdate=false/*bool bMultiSample=false, uint uiSamples=0*/);
				bool		calc(std::string name, bool bUpdate=false/*, bool bMultiSample=false, uint uiSamples=0*/);
				bool		calc(uint id, bool bUpdate=false/*, bool bMultiSample=false, uint uiSamples=0*/);

				void		update();
				void		update(std::string name);
				void		update(int id);

				void		draw();
//				void		draw(_SI siType);
				void		draw(std::string name);
				void		draw(int id);

			private:
				Atmosphere		&parent;			// Access to parent class
				static bool		bTexLoaded;			// Has the textures file been loaded yet
				static Texture	tex;				// Global textures list, prevents copies of textures
				bool			init();
				bool bErrorONS[32];
				int							iNumObjects;
				static const uint			MAX_TEXTURES;
				static const int			MAX_OBJECTS;
				static const uint			RECORD_SIZE;
				static const std::string	DIR;
				static const std::string	FILENAME;
				static const std::string	TEXDIR;
		};

		const uint			_Flora::MAX_TEXTURES	= 32;
		const int			_Flora::MAX_OBJECTS		= 16;
		const uint			_Flora::RECORD_SIZE		= 32;
		const std::string	_Flora::DIR				= "./system/";
		const std::string	_Flora::FILENAME		= "flora.bin";
		const std::string	_Flora::TEXDIR			= "./texture/atmosphere/flora/";

		 _Flora::_Flora(Atmosphere &f) : parent(f) {
			iNumObjects = 0;
			for (int n=0; n<32; n++) {
				bErrorONS[n] = false;
			}
			//data = new t_FloraData[MAX_OBJECTS];
			init();
		}

		_Flora::~_Flora() {
			//delete[] data;
			for(auto &item : data) {
				delete item;
			}
		}

		bool _Flora::bTexLoaded = false;
		Texture _Flora::tex = Texture();

		/*
		 * Load global satellite textures
		 */
		bool _Flora::init() {
			if (!bTexLoaded) {
				//std::cout << "[Satellite]";
				std::cout << sOffset << "Init Flora.......................................................";
				MemBlock memBlock;
				std::string theImage;
				int iCount = 0;
				struct _ImageData {
					std::string image;
					int id;
				} imageData[128];

				readFile((DIR+FILENAME), memBlock);
				//readFile(cFilename, memBlock); //Read the data file into memory

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
					std::cout << "[" << imageData[n].id << ", " << imageData[n].image << "]";
					tex.Load(TEXDIR, imageData[n].image, imageData[n].id, true, (GLenum)GL_NEAREST, (GLenum)GL_REPEAT);
				}

				bTexLoaded = true;
				std::cout << "Done" << std::endl;
				return true;
			}
			return false;
		}

		/*
		 * load
		 */
		bool _Flora::add(t_FloraData &newData)   {
			std::cout << "[" << newData.sName << "]";

//			if (iNumObjects < MAX_OBJECTS) {
//				data[iNumObjects] = t_FloraData(newData);
//				map.insert(make_pair(newData.sName, iNumObjects));
//				rmap.insert(make_pair(iNumObjects, newData.sName));
//				iNumObjects++;
//			}
			data.add(newData.sName, &newData);
			return true;
		}

		bool _Flora::calc(bool bUpdate/*bool bMultiSample, uint uiSamples*/)   {
			try {
				for (int n=0; n<iNumObjects; n++) {
					calc(n, bUpdate/*, bMultiSample, uiSamples*/);
				}
			}
			catch(...) {
				std::cout << "Exception occurred:" << std::endl << "     bool _Flora::calc(bool bMultiSample, uint uiSamples)" << std::endl;
				std::exit(0);
			}
			return true;
		}

		bool _Flora::calc(std::string name, bool bUpdate/*, bool bMultiSample, uint uiSamples*/)   {
			return calc(data.getID(name), bUpdate/*, bMultiSample, uiSamples*/);
		}

		bool _Flora::calc(uint id, bool bUpdate/*, bool bMultiSample, uint uiSamples*/)   {
			std::cout << "[" << data.getName(id) << "]";

//			std::cout << std::endl;
//			for (int n=0; n<20; n++) {
//				std::cout << "Int = " << roll(1, 20) << ", Float = " << roll(1.0f, 20.0f) << std::endl;
//			}

//			Vector2f vCoords[] = { 0.0, 0.0,
//								   0.0, 1.0,
//								   1.0, 0.0,
//								   1.0, 1.0 };

			int iVerts = data[id]->iNum*2; //Number of vertices

			if(!bUpdate) {
				std::cout << "Creating " << tex.iLoaded << " VAO's...";
				data[id]->vao = new VAO[tex.iLoaded];
				std::cout << "Done." << std::endl;

				std::cout << "  Creating " << tex.iLoaded << " arrays of " << iVerts << " vVerts...";
				data[id]->vVerts = new Data3f*[tex.iLoaded];
				for(int i=0; i<tex.iLoaded; i++) data[id]->vVerts[i] = new Data3f[iVerts];
				std::cout << "Done." << std::endl;

				std::cout << "  Creating " << tex.iLoaded << " arrays of " << iVerts << " vSize...";
				data[id]->vSize = new Data3f*[tex.iLoaded];
				for(int i=0; i<tex.iLoaded; i++) data[id]->vSize[i] = new Data3f[iVerts];
				std::cout << "Done." << std::endl;
			}

			/*
			 * Create vVerts structures
			 */
			//std::uniform_real_distribution<> dist(0, 360);
			//std::uniform_real_distribution<> sizeX(data[id].iMinWidth, data[id].iMaxWidth);
			//std::uniform_real_distribution<> sizeY(data[id].iMinHeight, data[id].iMaxHeight);
			for(int t=0; t<tex.iLoaded; t++) {
				for(int i=0; i<(iVerts); i+=2) {
					/*
					 * We need to do a weighted randomzer for the distance
					 * To do this we need to create a tiered randomizer
					 *   with a percentage chance determining which range
					 *   to use.
					 *
					 * Randomize 1-20:
					 *   1-2:   Distance = 0-25%   [10% chance to spawn close]
					 *   3-8:   Distance = 25-50%  [30% chance]
					 *   9-20:  Distance = 50-100% [60% chance]
					 *
					 *  1-2:   0-20%
					 *  3-5:   10-50%
					 *  6-10:  25-100%
					 *  11-20: 50-100%
					 */
					std::uniform_int_distribution<> range(1, 20);
//					int iResult = range(RNG::eng);
					int iResult = Core::roll(1, 20);
					int iMax = 0,
						iMin = 0;

					if (iResult <= 1) {
						iMin = data[id]->iThreshold;
						iMax = 0.2*data[id]->iRange;
					}
					else if(iResult > 1 && iResult < 4) {
						iMin = 0.2*data[id]->iRange;
						iMax = 0.4*data[id]->iRange;
					}
					else if(iResult >= 4 && iResult < 11) {
						iMin = 0.4*data[id]->iRange;
						iMax = 0.6*data[id]->iRange;
					}
					else {
						iMin = 0.6*data[id]->iRange;
						iMax = data[id]->iRange;
					}

//					std::uniform_real_distribution<> rRange(iMin, iMax);

					float fDistance	= roll((float)iMin, (float)iMax);
					float fAngle	= Core::Degrees(roll(0, 360)).toRadians();
					//float fHeight	= 0.0f;

					float fX = (cos(fAngle)*fDistance)-gameVars->player.active->transform.pos[0];
					float fZ = (sin(fAngle)*fDistance)-gameVars->player.active->transform.pos[2];
					float fY = 0.0f;	//fY = -map.getHeight(-fX, -fZ)*gameVars->screen.iScale;		// TODO: Implement Flora height checking
					float sX = roll(data[id]->iMinWidth, data[id]->iMaxWidth);
					float sY = roll(data[id]->iMinHeight, data[id]->iMaxHeight);
								//fX = (cos(fAngle)*fDistance)-(gameVars->player.active->transform.pos[0]*gameVars->screen.iScale);
								//fZ = (sin(fAngle)*fDistance)-(gameVars->player.active->transform.pos[2]*gameVars->screen.iScale);

					/*
					Vector4f vVerts[]	=	{	{	-fW,	fH,		0.0, count+1	},
											{		-fW,	0.0f,	0.0, count+1	},
											{		 fW,	fH,		0.0, count+1	},
											{		 fW,	0.0f,	0.0, count+1	}	};
					*/

					data[id]->vVerts[t][i][0] = fX*gameVars->screen.fScale;
					data[id]->vVerts[t][i][1] = fY+sY*data[id]->fScale;
					data[id]->vVerts[t][i][2] = fZ*gameVars->screen.fScale;

					data[id]->vVerts[t][i+1][0] = fX*gameVars->screen.fScale;
					data[id]->vVerts[t][i+1][1] = fY;
					data[id]->vVerts[t][i+1][2] = fZ*gameVars->screen.fScale;

					data[id]->vSize[t][i][0] = sX*data[id]->fScale;
					data[id]->vSize[t][i][1] = sY*data[id]->fScale;
					data[id]->vSize[t][i][2] = data[id]->iRange;

					data[id]->vSize[t][i+1][0] = sX*data[id]->fScale;
					data[id]->vSize[t][i+1][1] = sY*data[id]->fScale;
					data[id]->vSize[t][i+1][2] = data[id]->iRange;

//					std::cout << "Item: " << t << "-" << i << std::endl;
//					std::cout << "(" << data[id].vVerts[t][i][0]   << ", " << data[id].vVerts[t][i][1]   << ", " << data[id].vVerts[t][i][2]   << ")" << std::endl;
//					std::cout << "(" << data[id].vVerts[t][i+1][0] << ", " << data[id].vVerts[t][i+1][1] << ", " << data[id].vVerts[t][i+1][2] << ")" << std::endl;
//					std::cout << "(" << data[id].vSize[t][i][0]    << ", " << data[id].vSize[t][i][1]    << ", " << data[id].vSize[t][i][2]    << ")" << std::endl;
//					std::cout << "(" << data[id].vSize[t][i+1][0]  << ", " << data[id].vSize[t][i+1][1]  << ", " << data[id].vSize[t][i+1][2]  << ")" << std::endl;

					/*
					 * Retry if we spawned below water
					 */
					//if(data[id].vVerts[t][i+1][1] <= data[id].fFloor) i-=2;
					//else if(data[id].vVerts[t][i+1][1] >= data[id].fCeiling) i-=2;
				}
				std::cout << std::endl;

				std::cout << "  Creating VAO #" << t << "...";
				//if(data[id].iInstance>0) data[id].vao[t].Begin(GL_POINTS, iVerts, 1, data[id].iInstance);
				//else data[id].vao[t].Begin(GL_LINES, iVerts, 1);


				data[id]->vao[t].Begin(GL_LINES, iVerts, iVerts, 1);
				//data[id].vao[t].Begin(GL_POINTS, iVerts, iVerts, 1);

				data[id]->vao[t].CopyData(GLA_VERTEX, data[id]->vVerts[t]);
				data[id]->vao[t].CopyData(GLA_NORMAL, data[id]->vSize[t]);
				//if(data[id].iInstance>0) if(!bUpdate) data[id].vao[t].CopyData(GLA_POSITION, data[id].vPosition);
				data[id]->vao[t].End();
				std::cout << "Done." << std::endl;
			}
			return true;
		}

		void _Flora::update() {
			try {
				for (int n=0; n<iNumObjects; n++) {
					update(n);
				}
			}
			catch(...) {
				std::cout << "Exception occurred:" << std::endl << "     void _Flora::update()" << std::endl;
				std::exit(0);
			}
		}

		void _Flora::update(std::string name) {
			update(data.getID(name));
		}

		void _Flora::update(int id) {
			if(timeSys->get_ticks() >= (data[id]->fLast+data[id]->iRate)) {	// TODO: Flora time limiter
				int iVerts = data[id]->iNum*2;
				for(int t=0; t<tex.iLoaded; t++) {
					bool bMod = false;
					for(int i=0; i<iVerts; i+=2) {
						Vector3f fDist = { gameVars->player.active->transform.pos[0]*gameVars->screen.fScale, gameVars->player.active->transform.pos[1]*gameVars->screen.fScale, gameVars->player.active->transform.pos[2]*gameVars->screen.fScale };
//						std::cout << "\tDistXZpn: " << distanceXZpn(data[id].vVerts[t][i+1], fDist) << "\tRange: " << data[id].iRange << std::endl;
						if (distanceXZpn(Vector3f(data[id]->vVerts[t][i+1][0], data[id]->vVerts[t][i+1][1], data[id]->vVerts[t][i+1][2]), fDist) > data[id]->iRange*gameVars->screen.fScale) {
							//bool bFail=false;
							//do {
								/*
								 * Need to know direction of travel not angle of view
								 */
								//float fMove = gameVars->player.active->transform.GetAngle();
								//std::uniform_real_distribution<> rRange(0.8f*data[id].iRange, data[id].iRange);
								//std::uniform_real_distribution<> dist(fMove-80, fMove+80);

								//std::uniform_real_distribution<> sizeX(data[id].iMinWidth, data[id].iMaxWidth);
								//std::uniform_real_distribution<> sizeY(data[id].iMinHeight, data[id].iMaxHeight);

//								float fDistance	= rRange(RNG::eng);
//								float fAngle	= M_DegToRad(dist(RNG::eng));
								float fDistance	= roll(0.8f*(float)data[id]->iRange, (float)data[id]->iRange);
								float fAngle	= Core::Degrees(roll(0, 360)).toRadians();

//								std::cout << "[" << data[id].iRange << "] " << fDistance << "\t" << fAngle << std::endl;

								//cout << "(" << gameVars->player.active->transform.pos[0] << ", " << gameVars->player.active->transform.pos[2] << ")" << endl;
								//cout << "fDistance: " << fDistance << endl;

								float fX = (cos(fAngle)*fDistance)-(gameVars->player.active->transform.pos[0]);
								float fZ = (sin(fAngle)*fDistance)-(gameVars->player.active->transform.pos[2]);
								float fY = 0.0f;	//float fY = -map.getHeight(-fX, -fZ)*gameVars->screen.iScale,		// TODO: Implement Flora height checking
								float sX = roll(data[id]->iMinWidth, data[id]->iMaxWidth);
								float sY = roll(data[id]->iMinHeight, data[id]->iMaxHeight);

								data[id]->vVerts[t][i][0] = fX*gameVars->screen.fScale;
								data[id]->vVerts[t][i][1] = fY+sY*data[id]->fScale;
								data[id]->vVerts[t][i][2] = fZ*gameVars->screen.fScale;

								data[id]->vVerts[t][i+1][0] = fX*gameVars->screen.fScale;
								data[id]->vVerts[t][i+1][1] = fY;
								data[id]->vVerts[t][i+1][2] = fZ*gameVars->screen.fScale;

								data[id]->vSize[t][i][0] = sX*data[id]->fScale;
								data[id]->vSize[t][i][1] = sY*data[id]->fScale;
								data[id]->vSize[t][i][2] = data[id]->iRange;

								data[id]->vSize[t][i+1][0] = sX*data[id]->fScale;
								data[id]->vSize[t][i+1][1] = sY*data[id]->fScale;
								data[id]->vSize[t][i+1][2] = data[id]->iRange;

//								std::cout << "(" << data[id].vVerts[t][i][0] << ", " << data[id].vVerts[t][i][2] << ")" << std::endl;

								/*
								 * Retry if we spawned below water
								 */
								//if(data[id].vVerts[t][i+1][1] <= data[id].fFloor) bFail=true;
								//else bFail=false;
								bMod = true;
							//} while(bFail);
						}
					}

					if(bMod) {
						data[id]->vao[t].CopyData(GLA_VERTEX, data[id]->vVerts[t]);
						data[id]->vao[t].CopyData(GLA_NORMAL, data[id]->vSize[t]);
						data[id]->vao[t].End();
					}
				}

				data[id]->fLast = timeSys->get_ticks();
			}
		}

		void _Flora::draw()   {
			try {
				for (int n=0; n<iNumObjects; n++) {
					draw(n);
				}
			}
			catch(...) {
				std::cout << "Exception occurred:" << std::endl << "     void _Flora::draw()" << std::endl;
				std::exit(0);
			}
		}

//		void _Flora::draw(_SI siType) {
//			if (siType.bString) draw(siType.name);
//			else draw(siType.id);
//		}

		void _Flora::draw(std::string name) {
			draw(data.getID(name));
		}

		void _Flora::draw(int id) {
			glActiveTexture(GL_TEXTURE0);
			//glDisable(GL_CULL_FACE);
			for(int i=0; i<tex.iLoaded; i++) {
				tex.Set(i);
				data[id]->vao[i].Draw();
//				if(data[id].iInstance == 0) data[id].vao[i].Draw();
//				else data[id].vao[i].Draw(GLM_DRAW_ARRAYS_INSTANCED, 1, data[id].iInstance);
			}
			//glEnable(GL_CULL_FACE);
		}

	}
}















// ===============
//	Load
// ---------------
//if (gameVars->debug.load) cout << "## LOAD FLORA ##" << endl;
//flora.tex.Begin(NUM_TEXTURES);
//std::string	sDirectory		= "./texture/atmosphere/";
//char * cFilename			= (char*)"flora.bin";
//int	iRecordSize				= 32;
//readFile(cFilename, memBlock); //Read the data file into memory
//
//// Iterate through each record in the file
//for (int d=0; d<memBlock.size; d+=iRecordSize) {
//	int theId = 0;
//	for (int i=0; i<4; i++) theId+=(unsigned char)memBlock.buffer[i+d];
//	theImage = "";
//	for (int i=4; i<32; i++) if (memBlock.buffer[i+d]!=0) theImage+=(unsigned char)memBlock.buffer[i+d]; else break;
//	if (gameVars->debug.load) std::cout << " [" << theId << "] " <<  theImage << endl;
//	flora.tex.Load(sDirectory, theImage, theId, true, (GLenum)GL_LINEAR_MIPMAP_LINEAR, (GLenum)GL_CLAMP_TO_BORDER);
//}
//cout << "Loaded a total of " << flora.tex.iLoaded << " textures." << endl;
////for(int i=0; i<flora.tex.iLoaded; i++) {
////	cout << "mapImage: " << flora.tex.Get(i) << endl;
////}
////flora.tex.Get(0);






















// ===============
//	CALC
// ---------------
//if (gameVars->debug.load) std::cout << "## CALC FLORA 2 ##" << endl;
//
///*
//Vector2f vCoords[] = { 0.0, 0.0,
//					   0.0, 1.0,
//					   1.0, 0.0,
//					   1.0, 1.0 };
//*/
//
//int iVerts = flora.iNum*2; //Number of vertices
//
//if(!bUpdate) {
//	cout << "Creating " << flora.tex.iLoaded << " VAO's...";
//	flora.vao = new VAO[flora.tex.iLoaded];
//	cout << "Done." << endl;
//
//	cout << "  Creating " << flora.tex.iLoaded << " arrays of " << iVerts << " vVerts...";
//	flora.vVerts = new Data3f*[flora.tex.iLoaded];
//	for(int i=0; i<flora.tex.iLoaded; i++) flora.vVerts[i] = new Data3f[iVerts];
//	cout << "Done." << endl;
//
//	cout << "  Creating " << flora.tex.iLoaded << " arrays of " << iVerts << " vSize...";
//	flora.vSize = new Data3f*[flora.tex.iLoaded];
//	for(int i=0; i<flora.tex.iLoaded; i++) flora.vSize[i] = new Data3f[iVerts];
//	cout << "Done." << endl;
//}
//
///*
// * Create vVerts structures
// */
//std::uniform_real_distribution<> dist(0, 360);
//std::uniform_real_distribution<> sizeX(flora.iMinWidth, flora.iMaxWidth);
//std::uniform_real_distribution<> sizeY(flora.iMinHeight, flora.iMaxHeight);
//for(int t=0; t<flora.tex.iLoaded; t++) {
//	for(int i=0; i<(iVerts); i+=2) {
//		/*
//		 * We need to do a weighted randomzer for the distance
//		 * To do this we need to create a tiered randomizer
//		 *   with a percentage chance determining which range
//		 *   to use.
//		 *
//		 * Randomize 1-20:
//		 *   1-2:   Distance = 0-25%   [10% chance to spawn close]
//		 *   3-8:   Distance = 25-50%  [30% chance]
//		 *   9-20:  Distance = 50-100% [60% chance]
//		 *
//		 *  1-2:   0-20%
//		 *  3-5:   10-50%
//		 *  6-10:  25-100%
//		 *  11-20: 50-100%
//		 */
//		std::uniform_int_distribution<> range(1, 20);
//		int iResult = range(RNG::eng);
//		int iMax = 0,
//			iMin = 0;
//
//		if (iResult <= 1) {
//			iMin = flora.iThreshold;
//			iMax = 0.2*flora.iRange;
//		}
//		else if(iResult > 1 && iResult < 4) {
//			iMin = 0.2*flora.iRange;
//			iMax = 0.4*flora.iRange;
//		}
//		else if(iResult >= 4 && iResult < 11) {
//			iMin = 0.4*flora.iRange;
//			iMax = 0.6*flora.iRange;
//		}
//		else {
//			iMin = 0.6*flora.iRange;
//			iMax = flora.iRange;
//		}
//
//		std::uniform_real_distribution<> rRange(iMin, iMax);
//
//		float fDistance	= rRange(RNG::eng);
//		float fAngle	= M_DegToRad(dist(RNG::eng));
//		//float fHeight	= 0.0f;
//
//		float fX = (cos(fAngle)*fDistance)-gameVars->player.active->transform.pos[0],
//					fZ = (sin(fAngle)*fDistance)-gameVars->player.active->transform.pos[2],
//					fY = -map.getHeight(-fX, -fZ)*gameVars->screen.iScale,
//					sX = sizeX(RNG::eng),
//					sY = sizeY(RNG::eng);
//					//fX = (cos(fAngle)*fDistance)-(gameVars->player.active->transform.pos[0]*gameVars->screen.iScale);
//					//fZ = (sin(fAngle)*fDistance)-(gameVars->player.active->transform.pos[2]*gameVars->screen.iScale);
//
//		/*
//		Vector4f vVerts[]	=	{	{	-fW,	fH,		0.0, count+1	},
//								{		-fW,	0.0f,	0.0, count+1	},
//								{		 fW,	fH,		0.0, count+1	},
//								{		 fW,	0.0f,	0.0, count+1	}	};
//		*/
//
//		flora.vVerts[t][i][0] = fX*gameVars->screen.iScale;
//		flora.vVerts[t][i][1] = fY+sY*flora.fScale;
//		flora.vVerts[t][i][2] = fZ*gameVars->screen.iScale;
//
//		flora.vVerts[t][i+1][0] = fX*gameVars->screen.iScale;
//		flora.vVerts[t][i+1][1] = fY;
//		flora.vVerts[t][i+1][2] = fZ*gameVars->screen.iScale;
//
//		flora.vSize[t][i][0glActiveTexture(GL_TEXTURE0);
//			if (bTexLoaded) tex.Set(data[id].sImage);
//			else {
//				sysTex->set(sysTex->TEX_TESTPATTERN);
//				if (!bErrorONS[0]) {
//					std::cout << "ERROR! Satellite textures not loaded, must call _Flora::init()" << std::endl;
//					bErrorONS[0] = true;
//				}
//			}
//			data[id].vao.Draw();] = sX*flora.fScale;
//		flora.vSize[t][i][1] = sY*flora.fScale;
//		flora.vSize[t][i][2] = flora.iRange;
//
//		flora.vSize[t][i+1][0] = sX*flora.fScale;
//		flora.vSize[t][i+1][1] = sY*flora.fScale;
//		flora.vSize[t][i+1][2] = flora.iRange;
//
//		/*
//		 * Retry if we spawned below water
//		 */
//		//if(flora.vVerts[t][i+1][1] <= flora.fFloor) i-=2;
//		//else if(flora.vVerts[t][i+1][1] >= flora.fCeiling) i-=2;
//	}
//
//	cout << "  Creating VAO #" << t << "...";
//	//if(flora.iInstance>0) flora.vao[t].Begin(GL_POINTS, iVerts, 1, flora.iInstance);
//	//else flora.vao[t].Begin(GL_LINES, iVerts, 1);
//	flora.vao[t].Begin(GL_LINES, iVerts, 1);
//	flora.vao[t].CopyData(GLA_VERTEX, flora.vVerts[t]);
//	flora.vao[t].CopyData(GLA_NORMAL, flora.vSize[t]);
//	//if(flora.iInstance>0) if(!bUpdate) flora.vao[t].CopyData(GLA_POSITION, flora.vPosition);
//	flora.vao[t].End();
//	cout << "Done." << endl;
//}






















// ===============
//	Update
// ---------------
//else if(mode == FLORA) {
//if(gameVars->timer.frameRate.get_ticks() >= (flora.fLast+flora.iRate)) {
//	int iVerts = flora.iNum*2;
//	for(int t=0; t<flora.tex.iLoaded; t++) {
//		bool bMod = false;
//		for(int i=0; i<iVerts; i+=2) {
//			Vector3f fDist = { gameVars->player.active->transform.pos[0]*gameVars->screen.iScale, gameVars->player.active->transform.pos[1]*gameVars->screen.iScale, gameVars->player.active->transform.pos[2]*gameVars->screen.iScale };
//			//cout << "\tDistXZpn: " << distanceXZpn(flora.vVerts[t][i+1], fDist) << "\tRange: " << flora.iRange << endl;
//			if (distanceXZpn(Vector3f(flora.vVerts[t][i+1][0], flora.vVerts[t][i+1][1], flora.vVerts[t][i+1][2]), fDist) > flora.iRange*gameVars->screen.iScale) {
//				//bool bFail=false;
//				//do {
//					/*
//					 * Need to know direction of travel not angle of view
//					 */
//					float fMove = gameVars->player.active->transform.GetAngle();
//					std::uniform_real_distribution<> rRange(0.8f*flora.iRange, flora.iRange);
//					std::uniform_real_distribution<> dist(fMove-80, fMove+80);
//					//cout << "fMove: " << fMove << endl;
//					//std::uniform_real_distribution<> dist(0, 360);
//					std::uniform_real_distribution<> sizeX(flora.iMinWidth, flora.iMaxWidth);
//					std::uniform_real_distribution<> sizeY(flora.iMinHeight, flora.iMaxHeight);
//
//					float fDistance	= rRange(RNG::eng);
//					float fAngle	= M_DegToRad(dist(RNG::eng));
//
//					//cout << "[" << flora.iRange << "] " << fDistance << "\t" << fAngle << endl;
//
//					//cout << "(" << gameVars->player.active->transform.pos[0] << ", " << gameVars->player.active->transform.pos[2] << ")" << endl;
//					//cout << "fDistance: " << fDistance << endl;
//
//					float fX = (cos(fAngle)*fDistance)-(gameVars->player.active->transform.pos[0]),
//								fZ = (sin(fAngle)*fDistance)-(gameVars->player.active->transform.pos[2]),
//								fY = -map.getHeight(-fX, -fZ)*gameVars->screen.iScale,
//								sX = sizeX(RNG::eng),
//								sY = sizeY(RNG::eng);
//
//					flora.vVerts[t][i][0] = fX*gameVars->screen.iScale;
//					flora.vVerts[t][i][1] = fY+sY*flora.fScale;
//					flora.vVerts[t][i][2] = fZ*gameVars->screen.iScale;
//
//					flora.vVerts[t][i+1][0] = fX*gameVars->screen.iScale;
//					flora.vVerts[t][i+1][1] = fY;
//					flora.vVerts[t][i+1][2] = fZ*gameVars->screen.iScale;
//
//					flora.vSize[t][i][0] = sX*flora.fScale;
//					flora.vSize[t][i][1] = sY*flora.fScale;
//					flora.vSize[t][i][2] = flora.iRange;
//
//					flora.vSize[t][i+1][0] = sX*flora.fScale;
//					flora.vSize[t][i+1][1] = sY*flora.fScale;
//					flora.vSize[t][i+1][2] = flora.iRange;
//
//					//cout << "(" << flora.vVerts[t][i][0] << ", " << flora.vVerts[t][i][2] << ")" << endl;
//
//					/*
//					 * Retry if we spawned below water
//					 */
//					//if(flora.vVerts[t][i+1][1] <= flora.fFloor) bFail=true;
//					//else bFail=false;
//					bMod = true;
//				//} while(bFail);
//			}
//		}
//
//		if(bMod) {
//			flora.vao[t].CopyData(GLA_VERTEX, flora.vVerts[t]);
//			flora.vao[t].CopyData(GLA_NORMAL, flora.vSize[t]);
//			flora.vao[t].End();
//		}
//	}
//
//	flora.fLast = gameVars->timer.frameRate.get_ticks();
//}
//}






















































#endif /* HEADERS_GAMESYS_ATMOSPHERE_Flora_H_ */
