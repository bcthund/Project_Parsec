/*
 * Particles.cpp
 *
 *  Created on: Sep 9, 2019
 *      Author: bcthund
 */

#include "Particles.h"
#include "TimeSys.h"

namespace Core {

	bool				_Particles::bTexLoaded			= false;
	Texture				_Particles::tex					= Texture();
	const uint			_Particles::MAX_TEXTURES		= 32;
	const int			_Particles::MAX_OBJECTS			= 16;
	const uint			_Particles::RECORD_SIZE			= 32;
	const std::string	_Particles::DIR					= "./system/";
	const std::string	_Particles::FILENAME			= "particles.bin";
	const std::string	_Particles::TEXDIR				= "./texture/particles/";
	int					_ParticleDataOld::iLoadedTextues	= 0;

	_Particles::_Particles(GameSys::Atmosphere &f, float fScale) : parent(f), fWorldScale(fScale) {
		data.setSource("Particles");
		iNumObjects = 0;
		for (int n=0; n<32; n++) {
			bErrorONS[n] = false;
		}
		//data = new _ParticleDataOld[MAX_OBJECTS];
	}

	_Particles::~_Particles() {
		//delete[] data;
		for (auto & item : data) {
			delete item;
		}
	}

	/*
	 * Load global satellite textures
	 */
	bool _Particles::init() {
		if (!bTexLoaded) {
			Core::debug.log("Init Particles {\n");
			Core::debug.logIncreaseIndent();

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
				//if (bDebug) std::cout << "[" << imageData[n].id << ", " << imageData[n].image << "]";
				Core::debug.log("["+std::to_string(imageData[n].id)+"] "+imageData[n].image+"\n", Core::debug().YELLOW);
				tex.Load(TEXDIR, imageData[n].image, imageData[n].id, true, (GLenum)GL_NEAREST, (GLenum)GL_REPEAT);
			}

			// Let particle data know how many textures were
			// loaded so data can be properly deleted
			_ParticleDataOld::iLoadedTextues = tex.iLoaded;

			bTexLoaded = true;

			Core::debug.logDecreaseIndent();
			Core::debug.log("}\n");

			return true;
		}
		return false;
	}

	/*
	 * load
	 */
	bool _Particles::add(_ParticleDataOld newData)   {
//		std::cout << sOffset << "[" << newData.sName << "]" << std::endl;

//			data[iNumObjects] = _ParticleDataOld(newData);
//			map.insert(make_pair(newData.sName, iNumObjects));
//			rmap.insert(make_pair(iNumObjects, newData.sName));

			data.add(newData.sName, &newData);
			iNumObjects = data.size();
//		}
		return true;
	}

	bool _Particles::calc(bool bUpdate/*bool bMultiSample, uint uiSamples*/)   {
		try {
			for (int n=0; n<iNumObjects; n++) {
				calc(n, bUpdate/*, bMultiSample, uiSamples*/);
			}
		}
		catch(...) {
			std::cout << "Exception occurred:" << std::endl << "     bool _Particles::calc(bool bMultiSample, uint uiSamples)" << std::endl;
			std::exit(0);
		}
		return true;
	}

	bool _Particles::calc(std::string name, bool bUpdate/*, bool bMultiSample, uint uiSamples*/)   {
		return calc(data.getID(name), bUpdate/*, bMultiSample, uiSamples*/);
	}

	bool _Particles::calc(uint id, bool bUpdate/*, bool bMultiSample, uint uiSamples*/)   {
//		std::cout << sOffset << "[" << data.getName(id) << "]" << std::endl;


		// ==================
		//	PARTICLE_QUAD
		// ------------------
		if (data[id]->eSystem == PARTICLE_QUAD) {
			int iVerts = data[id]->iNum*2; //Number of vertices

//			std::cout << "Creating " << tex.iLoaded << " VAO's...";
			data[id]->vao = new VAO[tex.iLoaded];
//			std::cout << "Done." << std::endl;

//			std::cout << "  Creating " << tex.iLoaded << " arrays of " << iVerts << " vVerts...";
			data[id]->vVerts = new Data3f*[tex.iLoaded];
			for(int i=0; i<tex.iLoaded; i++) data[id]->vVerts[i] = new Data3f[iVerts];
//			std::cout << "Done." << std::endl;

//			std::cout << "  Creating " << tex.iLoaded << " arrays of " << iVerts << " vSize...";
			data[id]->vSize = new Data3f*[tex.iLoaded];
			for(int i=0; i<tex.iLoaded; i++) data[id]->vSize[i] = new Data3f[iVerts];
//			std::cout << "Done." << std::endl;

			update(id, true);

//			for(int t=0; t<tex.iLoaded; t++) {
//				for(int i=0; i<(iVerts); i+=2) {
//					/*
//					 * We need to do a weighted randomzer for the distance
//					 * To do this we need to create a tiered randomizer
//					 *   with a percentage chance determining which range
//					 *   to use.
//					 *
//					 * Randomize 1-20:
//					 *   1-2:   Distance = 0-25%   [10% chance to spawn close]
//					 *   3-8:   Distance = 25-50%  [30% chance]
//					 *   9-20:  Distance = 50-100% [60% chance]
//					 *
//					 *  1-2:   0-20%
//					 *  3-5:   10-50%
//					 *  6-10:  25-100%
//					 *  11-20: 50-100%
//					 */
//					int iResult = Core::roll(1, 20);
//					int iMax = 0,
//						iMin = 0;
//
//					if (iResult <= 1) {
//						iMin = data[id]->iThreshold;
//						iMax = 0.2*data[id]->iRange;
//					}
//					else if(iResult > 1 && iResult < 4) {
//						iMin = 0.2*data[id]->iRange;
//						iMax = 0.4*data[id]->iRange;
//					}
//					else if(iResult >= 4 && iResult < 11) {
//						iMin = 0.4*data[id]->iRange;
//						iMax = 0.6*data[id]->iRange;
//					}
//					else {
//						iMin = 0.6*data[id]->iRange;
//						iMax = data[id]->iRange;
//					}
//
//					float fDistance	= roll((float)iMin, (float)iMax);
//					float fAngle	= Core::Degrees(roll(0, 360)).toRadians();
//
//					float fX = (cos(fAngle)*fDistance)-vTarget.x;
//					float fZ = (sin(fAngle)*fDistance)-vTarget.z;
//					float fY = 0.0f;	//fY = -map.getHeight(-fX, -fZ)*gameVars.screen.iScale;		// TODO: [Particles] Implement Flora height checking
//					float sX = roll(data[id]->iMinWidth, data[id]->iMaxWidth);
//					float sY = roll(data[id]->iMinHeight, data[id]->iMaxHeight);
//
//					data[id]->vVerts[t][i][0] = fX*fWorldScale;
//					data[id]->vVerts[t][i][1] = fY+sY*data[id]->fScale;
//					data[id]->vVerts[t][i][2] = fZ*fWorldScale;
//
//					data[id]->vVerts[t][i+1][0] = fX*fWorldScale;
//					data[id]->vVerts[t][i+1][1] = fY;
//					data[id]->vVerts[t][i+1][2] = fZ*fWorldScale;
//
//					data[id]->vSize[t][i][0] = sX*data[id]->fScale;
//					data[id]->vSize[t][i][1] = sY*data[id]->fScale;
//					data[id]->vSize[t][i][2] = data[id]->iRange;
//
//					data[id]->vSize[t][i+1][0] = sX*data[id]->fScale;
//					data[id]->vSize[t][i+1][1] = sY*data[id]->fScale;
//					data[id]->vSize[t][i+1][2] = data[id]->iRange;
//
//					/*
//					 * TODO: [Particles] Retry if we spawned below water
//					 */
//					//if(data[id]->vVerts[t][i+1][1] <= data[id]->fFloor) i-=2;
//					//else if(data[id]->vVerts[t][i+1][1] >= data[id]->fCeiling) i-=2;
//				}
//				std::cout << std::endl;
//
//				std::cout << "  Creating VAO #" << t << "...";
//				//if(data[id]->iInstance>0) data[id]->vao[t].Begin(GL_POINTS, iVerts, 1, data[id]->iInstance);
//				//else data[id]->vao[t].Begin(GL_LINES, iVerts, 1);
//
//				data[id]->vao[t].Begin(GL_LINES, iVerts, iVerts, 1);
//				//data[id]->vao[t].Begin(GL_POINTS, iVerts, iVerts, 1);
//
//				data[id]->vao[t].CopyData(GLA_VERTEX, data[id]->vVerts[t]);
//				data[id]->vao[t].CopyData(GLA_NORMAL, data[id]->vSize[t]);
//				//if(data[id]->iInstance>0) if(!bUpdate) data[id]->vao[t].CopyData(GLA_POSITION, data[id]->vPosition);
//				data[id]->vao[t].End();
//				std::cout << "Done." << std::endl;
//			}
		}
		return true;
	}

	void _Particles::update(bool bCreateVao) {
		try {
			for (int n=0; n<iNumObjects; n++) {
				update(n, bCreateVao);
			}
		}
		catch(...) {
			std::cout << "Exception occurred:" << std::endl << "     void _Particles::update()" << std::endl;
			std::exit(0);
		}
	}

	void _Particles::update(std::string name, bool bCreateVao) {
		update(data.getID(name), bCreateVao);
	}

	void _Particles::update(int id, bool bCreateVao) {
		// ==================
		//	PARTICLE_QUAD
		// ------------------
//		std::cout << "[" << data[id]->eSystem << "][" << bCreateVao << "] vTarget = (" << data[id]->vTarget->x << ", " << data[id]->vTarget->y << ", " << data[id]->vTarget->z << ")" << std::endl;
		if (data[id]->eSystem == PARTICLE_QUAD) updateQuad(id, bCreateVao);
	}

	// ==================
	//	PARTICLE_QUAD
	// ------------------
	void _Particles::updateQuad(int id, bool bCreateVao) {
		if((timeSys->get_ticks() >= (data[id]->fLast+data[id]->iRate)) || bCreateVao) {	// TODO: [Particles] Flora time limiter
			int iVerts = data[id]->iNum*2;
			Vector3f vDist = { data[id]->vTarget->x*fWorldScale, data[id]->vTarget->y*fWorldScale, data[id]->vTarget->z*fWorldScale };

			for(int t=0; t<tex.iLoaded; t++) {
				bool bMod = false;

				for(int i=0; i<iVerts; i+=2) {
					float fTargetDist;

					if (!bCreateVao) {
						fTargetDist = distanceXZpn(Vector3f(data[id]->vVerts[t][i+1][0], data[id]->vVerts[t][i+1][1], data[id]->vVerts[t][i+1][2]), vDist);
//							std::cout << "fDist = " << fTargetDist << std::endl;
					}

					if ((fTargetDist > data[id]->iRange*fWorldScale) || bCreateVao) {
//							do {
							float fDistance;
							if (bCreateVao) {
								/*
								 * For initial spawn we need to do a weighted randomzer
								 *   for the distance.
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

								fDistance	= roll((float)iMin, (float)iMax);
							}
							else fDistance	= roll(0.8f*(float)data[id]->iRange, (float)data[id]->iRange);
							float fAngle	= Core::Degrees(roll(0, 360)).toRadians();

							float fX = (cos(fAngle)*fDistance)-(data[id]->vTarget->x);
							float fZ = (sin(fAngle)*fDistance)-(data[id]->vTarget->z);
							float fY = 0.0f;	//float fY = -map.getHeight(-fX, -fZ)*gameVars.screen.iScale,		// TODO: [Particles] Implement Flora height checking
							float sX = roll(data[id]->iMinWidth, data[id]->iMaxWidth);
							float sY = roll(data[id]->iMinHeight, data[id]->iMaxHeight);

							data[id]->vVerts[t][i][0] = fX*fWorldScale;
							data[id]->vVerts[t][i][1] = fY+sY*data[id]->fScale;
							data[id]->vVerts[t][i][2] = fZ*fWorldScale;

							data[id]->vVerts[t][i+1][0] = fX*fWorldScale;
							data[id]->vVerts[t][i+1][1] = fY;
							data[id]->vVerts[t][i+1][2] = fZ*fWorldScale;

							data[id]->vSize[t][i][0] = sX*data[id]->fScale;
							data[id]->vSize[t][i][1] = sY*data[id]->fScale;
							data[id]->vSize[t][i][2] = data[id]->iRange;

							data[id]->vSize[t][i+1][0] = sX*data[id]->fScale;
							data[id]->vSize[t][i+1][1] = sY*data[id]->fScale;
							data[id]->vSize[t][i+1][2] = data[id]->iRange;

							/*
							 * Retry if we spawned below water
							 */
							//if(data[id]->vVerts[t][i+1][1] <= data[id]->fFloor) bFail=true;
							//else bFail=false;
							bMod = true;
//							} while(bFail);
					}
				}

				if (bCreateVao) {
					//if(data[id]->iInstance>0) data[id]->vao[t].Begin(GL_POINTS, iVerts, 1, data[id]->iInstance);
					//else data[id]->vao[t].Begin(GL_LINES, iVerts, 1);

					data[id]->vao[t].Begin(GL_LINES, iVerts, iVerts, 1);
					//data[id]->vao[t].Begin(GL_POINTS, iVerts, iVerts, 1);

					data[id]->vao[t].CopyData(GLA_VERTEX, data[id]->vVerts[t]);
					data[id]->vao[t].CopyData(GLA_NORMAL, data[id]->vSize[t]);
					//if(data[id]->iInstance>0) if(!bUpdate) data[id]->vao[t].CopyData(GLA_POSITION, data[id]->vPosition);
					data[id]->vao[t].End();
				}
				else if(bMod) {
					data[id]->vao[t].CopyData(GLA_VERTEX, data[id]->vVerts[t]);
					data[id]->vao[t].CopyData(GLA_NORMAL, data[id]->vSize[t]);
					data[id]->vao[t].End();
				}
			}

			data[id]->fLast = timeSys->get_ticks();
		}
	}

	void _Particles::draw()   {
		try {
			for (int n=0; n<iNumObjects; n++) {
				draw(n);
			}
		}
		catch(...) {
			std::cout << "Exception occurred:" << std::endl << "     void _Particles::draw()" << std::endl;
			std::exit(0);
		}
	}

//	void _Particles::draw(_SI siType) {
//		if (siType.bString) draw(siType.name);
//		else draw(siType.id);
//	}

	void _Particles::draw(std::string name) {
		draw(data.getID(name));
	}

	void _Particles::draw(int id) {
		glActiveTexture(GL_TEXTURE0);
		//glDisable(GL_CULL_FACE);

		for(int i=0; i<tex.iLoaded; i++) {
			tex.Set(i);
			data[id]->vao[i].Draw();
			std::cout << ".";
//				if(data[id]->iInstance == 0) data[id]->vao[i].Draw();
//				else data[id]->vao[i].Draw(GLM_DRAW_ARRAYS_INSTANCED, 1, data[id]->iInstance);
		}
		std::cout << std::endl;
		//glEnable(GL_CULL_FACE);
	}

} /* namespace Core */
