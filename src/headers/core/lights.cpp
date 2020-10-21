#include <iostream>

//#include "functions.h"
#include "lights.h"

namespace Core {
	_Lights::_Lights() {
		Core::debug.log("Construct Lights System {");

		uiNumLights = 32;
		data = new _LightData[uiNumLights];
		uiCurrentLights = 0;

		Core::debug.print(" Done ", Core::debug().GREEN);
		Core::debug.print("}\n");
	}

	_Lights::~_Lights() {
		Core::debug.log("Destroy Lights System {");
		delete[] data;
		Core::debug.print(" Done ", Core::debug().GREEN);
		Core::debug.print("}\n");
	}

	void _Lights::init() {
		Core::debug.log("Init Lights System {");
		for(uint i=0;i<uiNumLights;i++) {
			data[i].bLoaded = false;
			data[i].type = LIGHT_NONE;
		}
		Core::debug.print(" Done ", Core::debug().GREEN);
		Core::debug.print("}\n");
	}

	void _Lights::load() {
		Core::debug.log("Load Lights System {");
		Core::debug.print(" Done ", Core::debug().GREEN);
		Core::debug.print("}\n");
	}

	void _Lights::calc(float fScale) {
		Core::debug.log("Calc Lights System {");

		// Add player light
		// Player light should ALWAYS be light 0 and 1
//		AddLight(	Core::Vector3f(0, 0, 0),	// Position
//					Core::Vector3f(0, 0, -1),		// Direction
//					Core::Vector3f(0.8, 1.0, 0.6),	// Color
//					//Core::Vector3f(0.025, 0.00018, 0.0000625),	// attentuation scaling
//					Core::Vector3f(0.1, 0.00018, 0.0000625),	// attentuation scaling
//					LIGHT_SPOT_SOFT);
//
//		AddLight(	Core::Vector3f(0, 0, 0),	// Position
//					Core::Vector3f(0, 0, -1),		// Direction
//					Core::Vector3f(0.8, 1.0, 0.6),	// Color
//					Core::Vector3f(0.025, 0.00018, 0.0000625),	// attentuation scaling
//					LIGHT_OMNI);

		AddLight(	Core::Vector3f(0.0f),			// Position
					Core::Vector3f(1, -0.5, -0.5),		// Direction
//					Core::Vector3f(0.5, 0.5, 0.1),	// Color
					Core::Vector3f(1.0, 1.0, 1.0),	// Color
					1/fScale,	// attentuation scaling
					LIGHT_DIRECTIONAL);

//		AddLight(	Core::Vector3f(100*fScale, 100*fScale, 100*fScale),	// Position
//					Core::Vector3f(0.0f),				// Direction
//					Core::Vector3f(0.8, 1.0, 0.6),	// Color
//					1/fScale,	// attentuation scaling
//					LIGHT_OMNI);
//
//		AddLight(	Core::Vector3f(400*fScale, 60*fScale, 250*fScale),	// Position
//					Core::Vector3f(0, 0, -1),		// Direction
//					Core::Vector3f(3.0, 3.0, 3.0),  //Core::Vector3f(0.7, 0.9, 0.5),	// Color
//					Core::Vector3f(0.1, 0.00018, 0.0000625),	// attentuation scaling
//					LIGHT_SPOT_SOFT);

		Core::debug.print(" Done ", Core::debug().GREEN);
		Core::debug.print("}\n");
	}

	// Default Attenuation from T+E: 0.0500007, 0.000700051, 5.88997e-05
	uint _Lights::AddLight(Vector3f pos, Vector3f dir, Vector3f diffuse, _LightType type) {
		return AddLight(pos, dir, diffuse, diffuse*0.05, diffuse*1.5, Vector3f(0.001f, 0.002f, 0.00016f), 15.0f, 20.0f, type);
	}

	uint _Lights::AddLight(Vector3f pos, Vector3f dir, Vector3f diffuse, Degrees fInnerCone, Degrees fOuterCone, _LightType type) {
		return AddLight(pos, dir, diffuse, diffuse*0.05, diffuse*1.5, Vector3f(0.001f, 0.002f, 0.00016f), fInnerCone, fOuterCone, type);
	}

	uint _Lights::AddLight(Vector3f pos, Vector3f dir, Vector3f diffuse, float attenuation, _LightType type) {
		return AddLight(pos, dir, diffuse, diffuse*0.05, diffuse*1.5, Vector3f(0.001f*attenuation, 0.002f*attenuation, 0.00016f*attenuation), 15.0f, 20.0f, type);
	}

	uint _Lights::AddLight(Vector3f pos, Vector3f dir, Vector3f diffuse, Vector3f attenuation, _LightType type) {
		return AddLight(pos, dir, diffuse, diffuse*0.05, diffuse*1.5, attenuation, 15.0f, 20.0f, type);
	}

	uint _Lights::AddLight(Vector3f pos, Vector3f dir, Vector3f diffuse, Vector3f ambient, Vector3f specular, Vector3f attenuation, Degrees fInnerCone, Degrees fOuterCone, _LightType type) {

		/*
		 * Limit colors to 1.0f max, this mostly
		 * exists for autocalculated ambient and
		 * specular colors.
		 */
		diffuse.x = fmin(diffuse.x, 1.0f);
		diffuse.y = fmin(diffuse.y, 1.0f);
		diffuse.z = fmin(diffuse.z, 1.0f);

		ambient.x = fmin(ambient.x, 1.0f);
		ambient.y = fmin(ambient.y, 1.0f);
		ambient.z = fmin(ambient.z, 1.0f);

		specular.x = fmin(specular.x, 1.0f);
		specular.y = fmin(specular.y, 1.0f);
		specular.z = fmin(specular.z, 1.0f);

		data[uiCurrentLights].pos = pos;
		data[uiCurrentLights].dir = dir;
		data[uiCurrentLights].diffuse = diffuse;
		data[uiCurrentLights].ambient = ambient;
		data[uiCurrentLights].specular = specular;
		data[uiCurrentLights].attenuation = attenuation;
		data[uiCurrentLights].type = type;
		data[uiCurrentLights].fInnerCone = cos(fInnerCone.toRadians());
		data[uiCurrentLights].fOuterCone = cos(fOuterCone.toRadians());
		data[uiCurrentLights].bLoaded = true;
		uiCurrentLights++;

		return uiCurrentLights-1;
	}

	Vector3f _Lights::GetDirRad(uint num) {
		if (data[num].bLoaded) {
			return Vector3f(data[num].dir) * M_PI;
		}
		return Vector3f();
	}

}
