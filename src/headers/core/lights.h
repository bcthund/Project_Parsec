/*
 * lights.h
 *
 *  Created on: Sep 28, 2018
 *      Author: bcthund
 */

#ifndef HEADERS_CORE_LIGHTS_H_
#define HEADERS_CORE_LIGHTS_H_

#include "extern.h"
#include "core_functions.h"
//#include "types.h"

namespace Core {
	/*
	 * USAGE:
	 * Only one copy of this class should exist normally, this primary class is used
	 * 	by the shaders to render those lights on all scene objects. However a custom
	 * 	lights class can be supplied with an O3D for example and only those lights
	 * 	will be used when rendering that object. This would require a copy of the
	 * 	global light source if that light source is also desired (i.e. sun/moon)
	 *
	 * Each light can have their own diffuse, ambient, and specular colors. Diffuse is
	 * 	the only color required. If others are omitted then the ambient is calculated
	 * 	as a percentage below diffuse and the specular as a percentage above diffuse.
	 *
	 * If attenuation is not supplied then a default of Vector3f(1.0f, 0.01f, 0.002f) is
	 * 	applied. However attenuation is only used for OMNI and SPOT type lights.
	 *
	 * Direction only applies to DIRECTIONAL and SPOT types.
	 *
	 * Position is needed for ALL lights
	 */
	class _Lights {
		public:
			enum _LightType { LIGHT_NONE=0, LIGHT_DIRECTIONAL, LIGHT_OMNI, LIGHT_SPOT_HARD, LIGHT_SPOT_SOFT };
			struct _LightData {
				_LightType type;
				float fInnerCone, fOuterCone;	// Cones for spot lights
				bool bLoaded;					// Has the light been fully loaded
				Vector3f dir,					// Direction vector of light
						 pos,					// Position of light source, needed for omni and spot lights
						 diffuse,				// Color of light
						 ambient,				// Ambient color
						 specular,				// Specular color (not implemented)
						 attenuation;			// Attenuation factors for omni light
				_LightData() {

					fInnerCone = cos(Degrees(15.0f).toRadians());
					fOuterCone = cos(Degrees(20.0f).toRadians());
					type = LIGHT_NONE;
					bLoaded = false;
				}
			};
		private:
			uint uiNumLights,
				 uiCurrentLights;
			_LightData *data;
		protected:
		public:
					     _Lights();
					     ~_Lights();
			void 	     init();
			void 	     load();
			void 	     calc(float fScale);
			uint 	     AddLight(Vector3f pos, Vector3f dir, Vector3f diffuse, _LightType type=LIGHT_DIRECTIONAL);
			uint 	     AddLight(Vector3f pos, Vector3f dir, Vector3f diffuse, Degrees fInnerCone, Degrees fOuterCone, _LightType type=LIGHT_SPOT_SOFT);
			uint 	     AddLight(Vector3f pos, Vector3f dir, Vector3f diffuse, float attenuation, _LightType type=LIGHT_OMNI);
			uint 	     AddLight(Vector3f pos, Vector3f dir, Vector3f diffuse, Vector3f attenuation, _LightType type=LIGHT_OMNI);
			uint 	     AddLight(Vector3f pos, Vector3f dir, Vector3f diffuse, Vector3f ambient, Vector3f specular, Vector3f attenuation, Degrees fInnerCone, Degrees fOuterCone, _LightType type=LIGHT_OMNI);
			_LightData * GetLightData() { return data; }
			bool		 GetLightLoaded(uint num) { return data[num].bLoaded; };
			uint         GetNumLights()				{ return uiCurrentLights; }

			Vector3f     GetPos(uint num)			{ if (data[num].bLoaded) { return Vector3f(data[num].pos); 			} return Vector3f(); }
			Vector3f*    GetPosPtr(uint num)		{ if (data[num].bLoaded) { return &data[num].pos; 					} return nullptr; }

			Vector3f     GetDir(uint num)			{ if (data[num].bLoaded) { return Vector3f(data[num].dir); 			} return Vector3f(); }
			Vector3f     GetDirRad(uint num);
			Vector3f*    GetDirPtr(uint num)		{ if (data[num].bLoaded) { return &data[num].dir; 					} return nullptr; }

			Vector3f     GetDiffuse(uint num)		{ if (data[num].bLoaded) { return Vector3f(data[num].diffuse); 		} return Vector3f(); }
			Vector3f     GetAmbient(uint num)		{ if (data[num].bLoaded) { return Vector3f(data[num].ambient); 		} return Vector3f(); }
			Vector3f     GetSpecular(uint num)		{ if (data[num].bLoaded) { return Vector3f(data[num].specular); 	} return Vector3f(); }
			Vector3f     GetAttenuation(uint num)	{ if (data[num].bLoaded) { return Vector3f(data[num].attenuation);	} return Vector3f(); }
			_LightType   GetType(uint num)			{ if (data[num].bLoaded) { return data[num].type;			} return LIGHT_NONE; }

			void		 SetPos(uint num, Vector3f pos)			{ if (data[num].bLoaded) { data[num].pos			= pos;  } }
			void		 SetDir(uint num, Vector3f dir)			{ if (data[num].bLoaded) { data[num].dir			= dir;  } }
			void		 SetDiffuse(uint num, Vector3f dif)		{ if (data[num].bLoaded) { data[num].diffuse		= dif;  } }
			void		 SetAmbient(uint num, Vector3f amb)		{ if (data[num].bLoaded) { data[num].ambient		= amb;  } }
			void		 SetSpecular(uint num, Vector3f spec)	{ if (data[num].bLoaded) { data[num].specular 		= spec; } }
			void		 SetAttenuation(uint num, Vector3f att)	{ if (data[num].bLoaded) { data[num].attenuation	= att;  } }
			void		 SetType(uint num, _LightType type)		{ if (data[num].bLoaded) {  data[num].type			= type; } }
	};
}

#endif /* HEADERS_CORE_LIGHTS_H_ */
