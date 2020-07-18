/*
 * Particles.h
 *
 *  Created on: Sep 9, 2019
 *      Author: bcthund
 */

#ifndef HEADERS_CORE_ParticleEmitter_H_
#define HEADERS_CORE_ParticleEmitter_H_

//#include "extern.h"
//#include "types.h"
//#include <list>
#include <vector>
//#include <iterator>
#include <algorithm>	// sort
#include "core_functions.h"
#include "vao.h"
#include "texture.h"
#include "TextureAtlas.h"
#include "SystemTextures.h"
#include "TimeSys.h"
#include "helper.h"
#include "Colors.h"
#include "glinit.h"
#include "../gamesys/gameVars.h"

namespace Core {

//	enum _ParticleEmitterystem {	PARTICLE_NONE,		// Not set up
//									PARTICLE_QUAD,		// Creates 2D billboarding quads from a single point	(Flora)
//									PARTICLE_POINT_2D,	// Creates 2D point sprites (orthographic)				(Simple Snow/Hail)
//									PARTICLE_POINT_3D,	// Creates 3D point sprites (perspective)				(Snow/Hail in area around player)
//									PARTICLE_LINE_2D,	// Creates 2D lines (orthographic)						(Simple Rain)
//									PARTICLE_LINE_3D,	// Creates 3D lines (perspective)						(Rain in area around player)
//									PARTICLE_LAST };
//
//	// This defines the update routine position logic
//	enum _ParticleEmit {	EMITTER_NONE,		// Not set up
//							EMITTER_STATIC,		// Spawns in stationary positions around player
//							EMITTER_FALLING,	// Spawns around player at a certain height range and falls
//							EMITTER_EMITTER,	// Spawns from a single point with a velocity and direction
//							EMITTER_LAST };

	/*
	 * This defines a SINGLE particle
	 */
	struct _ParticleData {
		Vector3f		vPosition;		// Current Particle position
		Color			vColor;			// Particle Hue
		Vector3f		vVelocity;		// Current velocity (Function of source, target, and emitter speed)

		float			fDistance;		// Distance from camera (for sorting)

		float			fSize;
		float			fRotation;
		float			fRotationSpeed;

		float			fLifeTime;		// Maximum life of particle
		float			fElapsedLife;	// How long particle has been alive
		float			fStartTime;		// When did particle life start
		float			fGravityEffect;	// How much does gravity effect particle (can be negative for things like smoke and fire, positive for waterfall)

		_ParticleData() {
			fDistance		= 0;

			fSize			= 0;
			fRotation		= 0;
			fRotationSpeed	= 0;

			fLifeTime		= 0;
			fElapsedLife	= 0;
			fStartTime		= 0;
			fGravityEffect	= 1;
		};

		_ParticleData(const _ParticleData &data) {
			vPosition		= data.vPosition;
			vColor			= data.vColor;
			vVelocity		= data.vVelocity;

			fDistance		= data.fDistance;

			fSize			= data.fSize;
			fRotation		= data.fRotation;
			fRotationSpeed	= data.fRotationSpeed;

			fLifeTime		= data.fLifeTime;
			fElapsedLife	= data.fElapsedLife;
			fStartTime		= data.fStartTime;
			fGravityEffect	= data.fGravityEffect;
		};

		~_ParticleData() {
		}
	};

	/*
	 * This defines an emitter object, with settings for a list of particles
	 */
	struct _ParticleEmitterData {
		friend class _ParticleEmitter;
		private:
			std::vector<_ParticleData> particles;		// This is essentially a VBO (or data that gets transferred into the VBO)
			float			fElapsedEmitterLife;		// Elapsed time since particle emitter started emitting
			float			fStartTime;
			float			fLastUpdate;				// Last update time for emitter
			float			fLastEmit;					// Last update time for PPS
			float			fDistance;					// Disance of emitter from camera, for sorted drawing
			bool 			bEnable;					// Calc/Update/Draw this particle instance
			bool			bStarted;					// Has the emitter actually started drawing particles?
//			VAO				vao;						// Use helper GLS_POINT_SPRITE shader

		public:
			// Emitter Data
			std::string		sName;						// Unique emitter name
			int				iPPS;						// Spawn rate for particles (also limited by iRate)
			int				iNum;						// Maximum number of particles
			float			fEmitterLifeTime;			// Maximum life for emitter before auto-destruction (no more emitted particles, destroy when all dead)
			float			fEmitterStartFade;			// At what time to start alpha an d PPS fadeout
			int				iRate;						// Particle Update rate (milliseconds) (Faster rate reduces framerate)
			bool			bAdditiveBlending;
			_TextureAtlas	atlas;						// Image atlas coordinates

			// Particle Data
			Vector3f	*	vSource;				// Spawn point of particles
			Vector3f	*	vTarget;				// Initial velocity direction as a world position, not a vector

			std::string		sTexture;					// Texture name

			float			fParticleLifeTime;			// Time in seconds particle is alive (0 for clipping plane and gravity based)
			Vector2f		vLifeVariation;				// Min and Max time variation as a decimal percentage (1.0 = 100%), can be negative

			float			fGravityEffect;				// How much does gravity effect particle (particle mass)
			Vector2f		vGravityVariation;			// Variation in particle mass
			float			fClip;						// Clipping plane when fParticleLifeTime==0. It will be the floor or Ceiling depending on if fGravityEffect is >0 or <0

			float			fStartingSize;				// Base particle size (not max size, linear scaling based on distance)
			Vector2f		vSizeVariation;				// Min and Max variation in size

			float			fRotation;					// Static rotation (fRotationSpeed==0.0f)
			Vector2f		vRotationVariation;			// Variation to static rotation

			float			fRotationSpeed;				// Rotation speed (TODO: Fix rotations in particle emitter shader)
			Vector2f		vRotationSpeedVariation;	// Min and Max variation to rotation

			float			fSpeed;						// Particle base velocity
			struct _SpreadStruct {
				private: Vector2f data[3];
				public:
					float		&x1 = data[0].x,
								&x2 = data[0].y,
								&y1 = data[1].x,
								&y2 = data[1].y,
								&z1 = data[2].x,
								&z2 = data[2].y;
					Vector2f	&x = data[0],
								&y = data[1],
								&z = data[2];


				Vector2f		&operator[] (int i) {
					if(i>2) i=2;
					return data[i];
				}

				_SpreadStruct	operator=   (const _SpreadStruct& rhs) {
					x1 = rhs.x1;
					x2 = rhs.x2;
					y1 = rhs.y1;
					y2 = rhs.y2;
					z1 = rhs.z1;
					z2 = rhs.z2;
					return *this;
				}

			} vVelocitySpread, vSpawnSpread;		// Variation in velocity direction and spawn plane in x, y, and z world coordinates

			void	add(const _ParticleData &data) {
				particles.push_back(data);
			}

			void	remove(int i) {
				particles.erase(particles.begin() + i);
			}

		_ParticleEmitterData() {
//	TODO:		eSystem		= PARTICLE_NONE;
//	TODO:		eEmitter	= EMITTER_NONE;
			sName				= "";
			vSource				= nullptr;
			vTarget				= nullptr;

			sTexture			= "test_pattern.png";

			fStartingSize		= 0;
			fRotation			= 0;
			fRotationSpeed		= 0;

			fSpeed				= 1;
			iPPS				= 10;
			iNum				= 100;

			fParticleLifeTime	= 0;
			fGravityEffect		= 1;
			fClip				= 0.0f;
//			fFloor				= 0.0f;
//			fCeiling			= 1000.0f;

			fEmitterLifeTime	= 10;
			fEmitterStartFade	= 8;
			fElapsedEmitterLife	= 0;
			fStartTime			= 0;
			fLastEmit			= 0;

//			fThreshold			= 0;
//			fSpread				= 0;
			//vSpread[0]			= Vector2f(0.0f);
			//vSpread[1]			= Vector2f(0.0f);
			//vSpread[2]			= Vector2f(0.0f);
			iRate				= 500;
			fLastUpdate			= 0;
			fDistance			= 0.0f;
			bAdditiveBlending	= true;

			bEnable 			= false;
			bStarted			= false;
		};

		_ParticleEmitterData( _ParticleEmitterData &data) {
//		_ParticleEmitterData(const _ParticleEmitterData &data) {
//		_ParticleEmitterData(_ParticleEmitterData *data) {

			//particles			= data.particles;

			sName					= data.sName;
			vSource					= new Vector3f(data.vSource->x, data.vSource->y, data.vSource->z);
			vTarget					= new Vector3f(data.vTarget->x, data.vTarget->y, data.vTarget->z);

			sTexture				= data.sTexture;
			atlas.SetSize(data.atlas.iSize);

			fStartingSize			= data.fStartingSize;
			fRotation				= data.fRotation;
			fRotationSpeed			= data.fRotationSpeed;

			fSpeed					= data.fSpeed;
			iPPS					= data.iPPS;
			iNum					= data.iNum;

			fParticleLifeTime		= data.fParticleLifeTime /* 1000.0f*/; // Convert seconds to milliseconds
			fGravityEffect			= data.fGravityEffect;
			fClip					= data.fClip;
			fLastEmit				= data.fLastEmit;

			vLifeVariation			= data.vLifeVariation;			// time can never be below fParticleLifeTime, this variation adds time only (1+roll(vLifeVariation))
			vGravityVariation		= data.vGravityVariation;
			vSizeVariation			= data.vSizeVariation;
			vRotationVariation		= data.vRotationVariation;
			vRotationSpeedVariation	= data.vRotationSpeedVariation;

			fEmitterLifeTime		= data.fEmitterLifeTime /* 1000.0f*/; // Convert seconds to milliseconds
			fEmitterStartFade		= data.fEmitterStartFade;
			fElapsedEmitterLife 	= data.fElapsedEmitterLife;
			fStartTime				= data.fStartTime;

			vVelocitySpread			= data.vVelocitySpread;
			vSpawnSpread			= data.vSpawnSpread;
			iRate					= data.iRate;
			fLastUpdate				= data.fLastUpdate;
			fDistance				= data.fDistance;
			bAdditiveBlending		= data.bAdditiveBlending;

			bEnable					= false;
			bStarted				= false;
		};

		~_ParticleEmitterData() {
			if (vSource != nullptr) delete vSource;
			if (vTarget != nullptr) delete vTarget;
		};
	};

	/*
	 * Manager for all particle emitters
	 */
	//namespace GameSys {		class Atmosphere; }
	class _ParticleEmitter {
		public:
			_ParticleEmitter(/*float fScale*/);
			~_ParticleEmitter();
			bool		init();				// Loads textures, etc.

//			bool		create(const _ParticleEmitterData &newData);			// Add a new particle emitter
			bool		create(_ParticleEmitterData *newData);			// Add a new particle emitter
			void		remove(std::string name);								// Call remove() on emitter with name
			void		remove(int id);											// Remove a particle emitter

			void		calc();													// Call calc() on all emitters
			void		calc(std::string name);									// Call calc() on emitter with name
			void		calc(int id);											// Add initial particles, create VAO

			void		update(bool bSort=true);								// Call update() on all emitters
			void		update(std::string name);								// Call update() on emitter with name
			void		update(int id);											// Add/remove/disable particles logic

			void		emit(std::string name);									// Call emit() on emitter with name
			void		emit(int id);											// Calculate and add new particle to emitter

			void		move(int id, int n);									// Translate particle position

			void		draw();													// Call draw() on all emitters
			void		draw(std::string name);									// Call draw() on emitter with name
			void		draw(int id);											// Draw emitter to screen

		private:
			std::vector <_ParticleEmitterData*> emitters;
//			GameSys::Atmosphere			&parent;			// Access to parent class
//			float 						fWorldScale;		// Access to world scale

			struct compareParticleDistance
			{
				inline bool operator() (const _ParticleData& struct1, const _ParticleData& struct2)
				{
					return (struct1.fDistance > struct2.fDistance);
				}
			};

			struct compareEmitterDistance
			{
				inline bool operator() (const _ParticleEmitterData* struct1, const _ParticleEmitterData* struct2)
				{
					return (struct1->fDistance > struct2->fDistance);
				}
			};

//			static	int					iLoadedTextues;
			static bool					bTexLoaded;			// Has the textures file been loaded yet
			static Texture				tex;				// Global textures list, prevents copies of textures
			static const uint			MAX_TEXTURES;
			static const uint			RECORD_SIZE;
			static const std::string	DIR;
			static const std::string	FILENAME;
			static const std::string	TEXDIR;
			static const bool			bDebug = false;

	};



} /* namespace Core */

#endif /* HEADERS_CORE_ParticleEmitter_H_ */
