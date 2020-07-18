/*
 * joint.cpp
 *
 *  Created on: Dec 19, 2018
 *      Author: bcthund
 */

//#include "../gl4/glcorearb.h"
//#include "core_functions.h"
#include "matrix.h"
#include "shader.h"
#include "gmath.h"
//#include "vao.h"
//#include "./gamesys/O3D.h"
#include "types.h"
#include "helper.h"
#include "joint.h"
#include <vector>

namespace Core {

	_Joint::_Joint() {
		vAxisX = Vector4f(1.0f, 0.0f, 0.0f, 1.0f);
		vAxisY = Vector4f(0.0f, 1.0f, 0.0f, 1.0f);
		vAxisZ = Vector4f(0.0f, 0.0f, 1.0f, 1.0f);
		bFinished = false;
	}

	_Joint::_Joint(Vector3f origin, Vector3f dest, Vector3f rotation, Vector3b rotationRestriction, Vector3b translationRestriction) {
		/*
		 * Create axis representation
		 *
		 * 		- dest-origin points in Y direction
		 * 		- use dot product to find difference in true Y versus joint Y
		 * 		- use diffrence to create rotation matrix
		 * 		- use rotation matrix to transform default axis
		 */
		vAxisX					= Vector4f(1.0f, 0.0f, 0.0f, 1.0f);
		vAxisY					= Vector4f(0.0f, 1.0f, 0.0f, 1.0f);
		vAxisZ					= Vector4f(0.0f, 0.0f, 1.0f, 1.0f);

		mLookAt					= Core::gmath.LookAt(origin, dest);
		vAxisX					= mLookAt * vAxisX;
		vAxisY					= mLookAt * vAxisY;
		vAxisZ					= mLookAt * vAxisZ;

		vOrigin					= origin;
		vDestination			= dest;

		vRotation				= rotation;
		vRotationRestriction	= rotationRestriction;
		vTranslationRestriction = translationRestriction;
		bFinished				= true;
	}

	_Joint::~_Joint() {
		// TODO Auto-generated destructor stub
	}

	void _Joint::SetJoint(Vector3f origin, Vector3f dest, Vector3f rotation, Vector3b rotationRestriction, Vector3b translationRestriction) {
		vAxisX					= Vector4f(1.0f, 0.0f, 0.0f, 1.0f);
		vAxisY					= Vector4f(0.0f, 1.0f, 0.0f, 1.0f);
		vAxisZ					= Vector4f(0.0f, 0.0f, 1.0f, 1.0f);

		mLookAt					= Core::gmath.LookAt(origin, dest);
		vAxisX					= mLookAt * vAxisX;
		vAxisY					= mLookAt * vAxisY;
		vAxisZ					= mLookAt * vAxisZ;

		vOrigin					= origin;
		vDestination			= dest;
		vRotation				= rotation;
		vRotationRestriction	= rotationRestriction;
		vTranslationRestriction = translationRestriction;
		bFinished				= true;
	}

	int _Joint::AddJoint(Vector3f dest, Vector3f rotation, Vector3b rotationRestriction, Vector3b translationRestriction) {
//		_Joint * newJoint = new _Joint(vDestination - vOrigin, dest - vOrigin, rotation, rotationRestriction, translationRestriction);
		_Joint newJoint = _Joint(vDestination - vOrigin, dest - vOrigin, rotation, rotationRestriction, translationRestriction);
		children.push_back(newJoint);
		return children.size()-1;
	}

	void _Joint::SetRotation(Vector3f rotation) {
		vRotation = rotation;
		/*
		 * TODO:
		 */

	}

	void _Joint::DrawJoint(/*Matrix_System &matrix, Shader_System &shader, _Helper &helper*/) {
		if(bFinished) {
			matrix->Push();
				matrix->Translate(vOrigin);
				//mLookAt = Core::gmath.LookAt(vOrigin, vDestination);

				//matrix->Rotate(vRotation.y, 0.0, 1.0, 0.0);
				//matrix->Rotate(vRotation.x, 1.0, 0.0, 0.0);
				//matrix->Rotate(vRotation.z, 1.0, 0.0, 1.0);

				matrix->SetTransform();
				shader->use(Core::GLS_LINES);
				shader->getUniform(Core::GLS_LINES);
				Vector3f dest = Vector3f(vDestination - vOrigin);
				helper->drawLine(Vector3f(0.0f), dest, 3.0f);
				for(int child=0; child<children.size(); child++) {
					children[child].DrawJoint(/*matrix, shader, helper*/);
				}
			matrix->Pop();
		}
	}

} /* namespace Core */
