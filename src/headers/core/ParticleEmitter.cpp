/*
 * Particles.cpp
 *
 *  Created on: Sep 9, 2019
 *      Author: bcthund
 */

#include "ParticleEmitter.h"

namespace Core {

	bool				_ParticleEmitter::bTexLoaded			= false;
	Texture				_ParticleEmitter::tex					= Texture();
	const uint			_ParticleEmitter::MAX_TEXTURES			= 32;
	const uint			_ParticleEmitter::RECORD_SIZE			= 32;
	const std::string	_ParticleEmitter::DIR					= "./system/";
	const std::string	_ParticleEmitter::FILENAME				= "particle_emitter.bin";
	const std::string	_ParticleEmitter::TEXDIR				= "./texture/particle_emitter/";

	_ParticleEmitter::_ParticleEmitter(/*float fScale*/) /*: fWorldScale(fScale)*/ {
//		fWorldScale = 1;
	}

	_ParticleEmitter::~_ParticleEmitter() {

	}

	/*
	 * Load global particle textures
	 */
	bool _ParticleEmitter::init() {
		if (!bTexLoaded) {
			std::cout << sOffset << "Init Particle Emitter {" << std::endl;
			sOffset += "    ";


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
				std::cout << sOffset << "[" << imageData[n].id << "] " << imageData[n].image << std::endl;
				tex.Load(TEXDIR, imageData[n].image, imageData[n].id, true, (GLenum)GL_NEAREST, (GLenum)GL_REPEAT);
			}

			bTexLoaded = true;
			PopStr(sOffset, 4);
			std::cout << sOffset << "}" << std::endl;
			return true;
		}
		return false;
	}

	/*
	 * load
	 */
	//bool _ParticleEmitter::create(const _ParticleEmitterData &newData)   {
	bool _ParticleEmitter::create(_ParticleEmitterData *newData)   {
		std::cout << sOffset << "[" << newData->sName << "]" << std::endl;

//		try {
//			// Don't allow repeat names
//			for (int n=0; n<emitters.size(); n++) {
//				if (emitters[n]->sName == newData.sName) {
//					throw  ("Duplicate particle emitter name [" + newData.sName + "] @ ParticleEmitter.cpp Line 98");
//					return false;
//				}
//			}
//
			emitters.push_back(newData);
//			emitters.back().fStartTime = timeSys->get_ticks();
//		}
//		catch(const char * s) {
//			std::cout << "Exception occurred:" << std::endl << std::endl;
//			std::cout << "\tbool _ParticleEmitter::create()" << std::endl;
//			std::cout << "\t" << s << std::endl;
//			std::exit(0);
//		}
//		catch(std::string &s) {
//			std::cout << "Exception occurred:" << std::endl << std::endl;
//			std::cout << "\tbool _ParticleEmitter::create()" << std::endl;
//			std::cout << "\t" << s << std::endl;
//			std::exit(0);
//		}
//		catch(...) {
//			std::cout << "Exception occurred:" << std::endl << std::endl;
//			std::cout << "\tbool _ParticleEmitter::create()" << std::endl;
//			std::exit(0);
//		}
		return true;
	}

	void _ParticleEmitter::remove(std::string name)   {
		for (int n=0; n<emitters.size(); n++) {
			if (emitters[n]->sName == name) {
				remove(n);
				//emitters.erase(emitters.begin() + n);
				return;
			}
		}
	}

	void _ParticleEmitter::remove(int id)   {
		delete emitters[id];
		emitters.erase(emitters.begin() + id);
	}

	void _ParticleEmitter::calc()   {
		try {
			for (int n=0; n<emitters.size(); n++) {
				calc(n);
			}
		}
		catch(...) {
			std::cout << "Exception occurred:" << std::endl << "     bool _ParticleEmitter::calc()" << std::endl;
			std::exit(0);
		}
	}

	void _ParticleEmitter::calc(std::string name)   {
		for (int n=0; n<emitters.size(); n++) {
			if (emitters[n]->sName == name) {
				calc(n);
				return;
			}
		}
	}

	void _ParticleEmitter::calc(int id)   {

		// Auto convert seconds to milliseconds
		emitters[id]->fEmitterLifeTime *= 1000.0f;
		emitters[id]->fEmitterStartFade *= 1000.0f;
		emitters[id]->fParticleLifeTime *= 1000.0f;

		// Create initial particle
		emit(id);

		emitters[id]->bEnable = true;

//		std::cout << "Calc : " << emitters[id]->sName << ", bEnable = " << emitters[id]->bEnable << std::endl;
	}

	void _ParticleEmitter::update(bool bSort) {
		try {
			for (int n=0; n<emitters.size(); n++) {
//				std::cout << "Update [" << n << "]" << std::endl;
				// update emitter particles
				update(n);

				// Get emitter squared distance
				if (bSort) {
//					std::cout << "Get Distance...";
					Vector3f vDirection = *emitters[n]->vSource + gameVars->player.active->transform.pos;
					emitters[n]->fDistance = vDirection.sudoLength();
//					std::cout << "Done" << std::endl;
				}
			}

			// Sort emitters for alpha (after update in case of removal)
//			std::cout << "Sort...";
			if (bSort) std::sort(emitters.begin(), emitters.end(), compareEmitterDistance());
//			std::cout << "Done" << std::endl;
		}
		catch(...) {
			std::cout << "Exception occurred:" << std::endl << "     void _ParticleEmitter::update()" << std::endl;
			std::exit(0);
		}
	}

	void _ParticleEmitter::update(std::string name) {
		for (int n=0; n<emitters.size(); n++) {
			if (emitters[n]->sName == name) {
				update(n);
				return;
			}
		}
	}

	void _ParticleEmitter::update(int id) {
		// Only update at the preset rate
		if ( (timeSys->get_ticks() - emitters[id]->fLastUpdate) > emitters[id]->iRate) {

			// Update emitter elapsed time and eithe update or remove
			emitters[id]->fElapsedEmitterLife = timeSys->get_ticks() - emitters[id]->fStartTime;

//			if (emitters[id]->sName == "Sparks") {
//				std::cout << "Start = " << emitters[id]->fStartTime << ", Life = " << emitters[id]->fEmitterLifeTime << ", Elapsed = " << emitters[id]->fElapsedEmitterLife << ", Current = " << timeSys->get_ticks() << std::endl;
//				std::cout << (emitters[id]->fEmitterLifeTime > 0.0f) << ", " << (emitters[id]->fElapsedEmitterLife < emitters[id]->fEmitterLifeTime) << ", " << ((emitters[id]->fEmitterLifeTime > 0.0f) && (emitters[id]->fElapsedEmitterLife < emitters[id]->fEmitterLifeTime)) << std::endl << std::endl;
//			}

			if ( ((emitters[id]->fEmitterLifeTime > 0.0f) && (emitters[id]->fElapsedEmitterLife < emitters[id]->fEmitterLifeTime)) || (emitters[id]->fEmitterLifeTime <= 0.0f) ) {

				bool bChange = false;

				// ==============================
				//   Remove and Move particles
				// ------------------------------
				// Update particles from top down so index doesn't become invalid when a dead particle is erased
				for (int n=emitters[id]->particles.size()-1; n>=0; n--) {

					// Update particle elapsed life
					emitters[id]->particles[n].fElapsedLife = timeSys->get_ticks() - emitters[id]->particles[n].fStartTime;

					if ( (emitters[id]->particles[n].fLifeTime > 0.0f) && (emitters[id]->particles[n].fElapsedLife > emitters[id]->particles[n].fLifeTime) ) {
						emitters[id]->remove(n);
						bChange = true;
					}
					else {

						if (emitters[id]->particles[n].fLifeTime <= 0.0f) {
							if ( (emitters[id]->fGravityEffect <= 0) && (emitters[id]->particles[n].vPosition.y > emitters[id]->fClip) ) {
								// Particle rising
								emitters[id]->remove(n);
								bChange = true;
							}
							else if ( (emitters[id]->fGravityEffect > 0) && (emitters[id]->particles[n].vPosition.y < emitters[id]->fClip) ) {
								// Particle Falling
								emitters[id]->remove(n);
								bChange = true;
							}
							else goto moveParticle;
						}
						else {
							moveParticle:
							move(id, n);
							bChange = true;
						}
					}
				}

				// =========================
				//   Emitter Lifetime Factor
				// -------------------------
				float fLifeFactor = 1.0f;
				if (emitters[id]->fEmitterLifeTime > 0.0f) {
//					fLifeFactor -= (emitters[id]->fElapsedEmitterLife / emitters[id]->fEmitterLifeTime);
					float EF = emitters[id]->fElapsedEmitterLife - emitters[id]->fEmitterStartFade;
					float LF = emitters[id]->fEmitterLifeTime - emitters[id]->fEmitterStartFade;
					fLifeFactor -= EF / LF;
				}

				// =========================
				//   Spawn new particles
				// -------------------------
				if ( (timeSys->get_ticks() - emitters[id]->fLastEmit) > (1000.0f/(emitters[id]->iPPS*fLifeFactor))) {
					if (emitters[id]->particles.size() < emitters[id]->iNum) {
						emit(id);
						bChange = true;
					}

					emitters[id]->fLastEmit = timeSys->get_ticks();
				}

				// ========================
				//   Sort particles by distance
				//   Calculate alpha
				//   Calculate size
				// ------------------------
				for (int n=0; n<emitters[id]->particles.size(); n++) {
					Vector3f vDirection = emitters[id]->particles[n].vPosition + gameVars->player.active->transform.pos;
					emitters[id]->particles[n].fDistance = vDirection.length();		// MUST be actual distance so we can calcualte scale based on distance later

					float fAlpha = 1.0f;
					if (emitters[id]->fParticleLifeTime <= 0.0f) {
						if (emitters[id]->fGravityEffect <= 0) {
							// Particle rising
							fAlpha = 1.0f - ( emitters[id]->particles[n].vPosition.y/(emitters[id]->fClip-100.0f) );
						}
						else {
							// Particle Falling
							fAlpha = emitters[id]->particles[n].vPosition.y/(emitters[id]->fClip+100.0f);
						}
					}
					else {
						fAlpha = 1.0f - (emitters[id]->particles[n].fElapsedLife / emitters[id]->particles[n].fLifeTime);
					}
					emitters[id]->particles[n].vColor.a = fAlpha * fLifeFactor;

					// Scale particle with distance
					float a = 0.0f;
					float b = 0.0f;
					float c = 1.0f/gameVars->screen.fFar;
					float d = emitters[id]->particles[n].fDistance;
					float d2 = d*d;
					float fSize = sqrt(1/(a+b*d+c*d2));
					emitters[id]->particles[n].fSize = fmax(fSize * emitters[id]->fStartingSize, 1.0f);
				}
				std::sort(emitters[id]->particles.begin(), emitters[id]->particles.end(), compareParticleDistance());

				emitters[id]->fLastUpdate = timeSys->get_ticks();
			}
			else {
				remove(id);
			}
		}
	}

	void _ParticleEmitter::move(int id, int n) {

		// Translate particle
		emitters[id]->particles[n].vVelocity.y -= state->fGravity * emitters[id]->particles[n].fGravityEffect;
		Vector3f vChange = emitters[id]->particles[n].vVelocity * (emitters[id]->particles[n].fElapsedLife/1000.0f);
		emitters[id]->particles[n].vPosition += vChange;

		// Rotate
		emitters[id]->particles[n].fRotation += emitters[id]->particles[n].fRotationSpeed;
	}

	void _ParticleEmitter::emit(std::string name) {
		for (int n=0; n<emitters.size(); n++) {
			if (emitters[n]->sName == name) {
				emit(n);
				return;
			}
		}
	}

	void _ParticleEmitter::emit(int id) {
		_ParticleData newParticle;
		newParticle.fElapsedLife	= 0;
		newParticle.fStartTime		= timeSys->get_ticks();
		newParticle.fGravityEffect	= emitters[id]->fGravityEffect		+ (emitters[id]->fGravityEffect * roll(emitters[id]->vGravityVariation));
		newParticle.fLifeTime		= (emitters[id]->fParticleLifeTime	+ (emitters[id]->fParticleLifeTime * roll(emitters[id]->vLifeVariation)));
		newParticle.fRotation		= emitters[id]->fRotation			+ (emitters[id]->fRotation * roll(emitters[id]->vRotationVariation));
		newParticle.fRotationSpeed	= emitters[id]->fRotationSpeed		+ (emitters[id]->fRotationSpeed * roll(emitters[id]->vRotationSpeedVariation));
		newParticle.fSize			= emitters[id]->fStartingSize		+ (emitters[id]->fStartingSize * roll(emitters[id]->vSizeVariation));
		newParticle.vColor			= Color(1.0f);
		newParticle.vPosition		= *emitters[id]->vSource				+ Vector3f( roll(emitters[id]->vSpawnSpread.x),
																					roll(emitters[id]->vSpawnSpread.y),
																					roll(emitters[id]->vSpawnSpread.z) );

		Vector3f velocity = (*emitters[id]->vTarget-*emitters[id]->vSource);
		velocity = velocity.normal();
		velocity += Vector3f(	roll(emitters[id]->vVelocitySpread.x),
								roll(emitters[id]->vVelocitySpread.y),
								roll(emitters[id]->vVelocitySpread.z) );
		velocity *= emitters[id]->fSpeed;
		newParticle.vVelocity		= velocity;

		emitters[id]->add(newParticle);
		move(id, emitters[id]->particles.size()-1);	// Make first move now, this will update distance for sorting
	}

	void _ParticleEmitter::draw()   {
		try {
			for (int n=0; n<emitters.size(); n++) {
//				std::cout << emitters[n]->sName << " [" << emitters[n]->fDistance << "]" << std::endl;
				draw(n);
			}
//			std::cout << std::endl;
		}
		catch(...) {
			std::cout << "Exception occurred:" << std::endl << "     void _ParticleEmitter::draw()" << std::endl;
			std::exit(0);
		}
	}

	void _ParticleEmitter::draw(std::string name) {
		for (int n=0; n<emitters.size(); n++) {
			if (emitters[n]->sName == name) {
				draw(n);
				return;
			}
		}
	}

	void _ParticleEmitter::draw(int id) {
		if (emitters[id]->bEnable == true) {

			if (!emitters[id]->bStarted) {
				emitters[id]->fStartTime = timeSys->get_ticks();
				emitters[id]->bStarted = true;
			}

			glActiveTexture(GL_TEXTURE0);
			tex.Set(emitters[id]->sTexture);

			if (emitters[id]->bAdditiveBlending) glinit->EnableAdditiveBlending();
			for (int n=0; n<emitters[id]->particles.size(); n++) {
				matrix->Push();
					matrix->Translate(emitters[id]->particles[n].vPosition);

					// Update texture atlas coordinates
					// TODO: Move to update routine
					Vector2f vTexCoord0, vTexCoord1;
					float fBlend = 0.0f;
					if(emitters[id]->atlas.bEnable) {
						// Get texture coord info (index, blend)
						float fLifeFactor = emitters[id]->particles[n].fElapsedLife/emitters[id]->particles[n].fLifeTime;
						int iStageCount = emitters[id]->atlas.Count();
						float fAtlasProgression = fLifeFactor * iStageCount;
						int iIndex0 = floor(fAtlasProgression);
						int iIndex1  = iIndex0<iStageCount-1?iIndex0+1:iIndex0;
						fBlend = fmod(fAtlasProgression, 1);

						// Get texture coord offsets
						vTexCoord0 = emitters[id]->atlas.GetCoords(iIndex0);
						vTexCoord1 = emitters[id]->atlas.GetCoords(iIndex1);

//						std::cout << "fElapsedLife = " << emitters[id]->particles[n].fElapsedLife << ", fLifeTime = " << emitters[id]->particles[n].fLifeTime << std::endl;
//						std::cout << "fLifeFactor = " << fLifeFactor << std::endl;
//						std::cout << "fAtlasProgression = " << fAtlasProgression << std::endl;
//						std::cout << "vTexCoord0 = " << vTexCoord0.x << ", " << vTexCoord0.y << std::endl;
//						std::cout << "vTexCoord1 = " << vTexCoord1.x << ", " << vTexCoord1.y << std::endl;
//						std::cout << "Blend = " << fBlend << std::endl;
//						std::cout << std::endl;
					}

//					helper->drawPointSprite(emitters[id]->particles[n].fSize,
//											emitters[id]->particles[n].fRotation,
//											emitters[id]->particles[n].vColor,
//											helper->GLPOINT_SQUARE_ALPHA);
					glPointSize(emitters[id]->particles[n].fSize);
//					matrix->Push();
						matrix->SetTransform();
						shader->use(GLS_PARTICLE_SPRITE);
						shader->getUniform(GLS_PARTICLE_SPRITE, helper->GLPOINT_SQUARE_ALPHA, emitters[id]->particles[n].vColor, emitters[id]->particles[n].fRotation, 5, 0.25, fBlend, emitters[id]->atlas.iSize, vTexCoord0, vTexCoord1);
						//vaoPoint.Draw();
						helper->vaoPoint.Draw();
//					matrix->Pop();

				matrix->Pop();
			}
			if (emitters[id]->bAdditiveBlending) glinit->DisableAdditiveBlending();
		}
	}

} /* namespace Core */
