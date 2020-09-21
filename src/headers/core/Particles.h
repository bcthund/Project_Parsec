/*
 * Particles.h
 *
 *  Created on: Sep 9, 2019
 *      Author: bcthund
 */

#ifndef HEADERS_CORE_PARTICLES_H_
#define HEADERS_CORE_PARTICLES_H_

//#include "extern.h"
//#include "types.h"
#include "core_functions.h"
#include "vao.h"
#include "texture.h"

namespace Core {

	enum _ParticleSystem {	PARTICLE_NONE,		// Not set up
							PARTICLE_QUAD,		// Creates 2D billboarding quads from a single point	(Flora)
							PARTICLE_POINT_2D,	// Creates 2D point sprites (orthographic)				(Simple Snow/Hail)
							PARTICLE_POINT_3D,	// Creates 3D point sprites (perspective)				(Snow/Hail in area around player)
							PARTICLE_LINE_2D,	// Creates 2D lines (orthographic)						(Simple Rain)
							PARTICLE_LINE_3D,	// Creates 3D lines (perspective)						(Rain in area around player)
							PARTICLE_LAST };

	// This defines the update routine position logic
	enum _ParticleEmit {	EMITTER_NONE,		// Not set up
							EMITTER_STATIC,		// Spawns in stationary positions around player
							EMITTER_FALLING,	// Spawns around player at a certain height range and falls
							EMITTER_EMITTER,	// Spawns from a single point with a velocity and direction
							EMITTER_LAST };

	// TODO: [Particles] Allow grouping of textures and number of VAOs...
	//	Currently a VAO is created for each texture loaded but each particle instance
	//	wont use all the textures.
	struct _ParticleDataOld {
		_ParticleSystem eSystem;
		_ParticleEmit	eEmitter;
		std::string		sName;
		Data3f		**	vVerts;			// Stored particles; first pointer = # of loaded sprites; second pointer = data
//		Vector4f	*	vPosition;		// Offset position
		Data3f		**	vSize;			// Randomize sizes, use texcoord input
		Vector4f		vColor;			// Allows for customization, NOT IMPLEMENTED

		Vector3f	*	vTarget;		// The target position, can be linked to a player or npc for example.

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
		static	int		iLoadedTextues;
		VAO			*	vao;

		_ParticleDataOld() {
			eSystem		= PARTICLE_NONE;
			eEmitter	= EMITTER_NONE;
			sName		= "";
			fScale		= 0;
			vVerts		= nullptr;
			vSize		= nullptr;
//			vPosition	= nullptr;
			vTarget		= nullptr;
			vColor[0]	= 0;
			vColor[1]	= 0;
			vColor[2]	= 0;
			vColor[3]	= 0;
			iMaxWidth	= 0;
			iMinWidth	= 0;
			iMaxHeight	= 0;
			iMinHeight	= 0;
			iNum		= 10;
			iRate		= 500;
			fLast		= 0;
			iRange		= 0;
			iThreshold	= 0;
			iInstance	= 0;
			iSpread		= 0;
			fFloorPlay	= 0;
			fCeiling	= 0;
			fFloor		= 0;
			vao			= nullptr,
			bEnable 	= false;
		};

		_ParticleDataOld(const _ParticleDataOld &data) {
			eSystem		= data.eSystem;
			eEmitter	= data.eEmitter;
			sName		= data.sName;
			fScale		= data.fScale;
			vVerts		= data.vVerts;
			vSize		= data.vSize;
//			vPosition = data;
			vTarget		= data.vTarget;
			vColor		= data.vColor;
			iMaxWidth	= data.iMaxWidth;
			iMinWidth	= data.iMinWidth;
			iMaxHeight	= data.iMaxHeight;
			iMinHeight	= data.iMinHeight;
			iNum		= data.iNum;
			iRate		= data.iRate;
			fLast		= data.fLast;
			iRange		= data.iRange;
			iThreshold	= data.iThreshold;
			iInstance	= data.iInstance;
			iSpread		= data.iSpread;
			fFloorPlay	= data.fFloorPlay;
			fCeiling	= data.fCeiling;
			fFloor		= data.fFloor;
			vao			= nullptr;
			bEnable		= true;
		};

		// FIXME: Particles, this crashes often. Rework to use VectorMap, add bInit like functionality.
		~_ParticleDataOld() {
			for (int n=0; n<iLoadedTextues; n++) {
				if (vVerts[n] != nullptr) delete[] vVerts[n];
				if (vSize[n] != nullptr) delete[] vSize[n];
			}
//			if (vVerts != nullptr) delete[] vVerts;
//			if (vSize != nullptr) delete[] vSize;

//			if (vao != nullptr)	delete vao,
			bEnable = false;
		};
	};

	namespace Sys {		class Atmosphere; }
	class _Particles {
		public:
//			_ParticleDataOld * data;
			//Core::Map_si	map;
			//Core::Map_is	rmap;
			t_VectorMap<_ParticleDataOld*> data;


			_Particles(Sys::Atmosphere &f, float fScale);
			~_Particles();

			bool		add(_ParticleDataOld data);

			bool		calc(bool bUpdate=false/*bool bMultiSample=false, uint uiSamples=0*/);
			bool		calc(std::string name, bool bUpdate=false/*, bool bMultiSample=false, uint uiSamples=0*/);
			bool		calc(uint id, bool bUpdate=false/*, bool bMultiSample=false, uint uiSamples=0*/);

			void		update(bool bCreateVao=false);
			void		update(std::string name, bool bCreateVao=false);
			void		update(int id, bool bCreateVao=false);

			void		draw();
//			void		draw(_SI siType);
			void		draw(std::string name);
			void		draw(int id);

		private:
			Sys::Atmosphere		&parent;			// Access to parent class
//			Vector3f		*vCamPos;			// Access to current camera (player) position
			float 			fWorldScale;		// Access to world scale
			bool			init();

			void		updateQuad(int id, bool bCreateVao=false);

			bool bErrorONS[32];
			int							iNumObjects;
			static bool					bTexLoaded;			// Has the textures file been loaded yet
			static Texture				tex;				// Global textures list, prevents copies of textures
			static const uint			MAX_TEXTURES;
			static const int			MAX_OBJECTS;
			static const uint			RECORD_SIZE;
			static const std::string	DIR;
			static const std::string	FILENAME;
			static const std::string	TEXDIR;
			static const bool			bDebug = false;

	};



} /* namespace Core */

#endif /* HEADERS_CORE_PARTICLES_H_ */
