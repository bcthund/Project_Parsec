/*
 * joint.h
 *
 *  Created on: Dec 19, 2018
 *      Author: bcthund
 *        Desc: Used in the skeleton class to define joints in a skeleton. This
 *        		contains:
 *        			- Origin
 *        			- Origin Orientation (rotation)
 *        			- Connecting Points (Array of locations that children can have their origin attatched to)
 *        			- 3D Object reference (Not O3D, but may used for testing)
 *        			- Axis restriction (What rotations are allowed?)
 *        			- Translation restriction (what translations are allowed?)
 *        			- Parent (reference to the joint this joint is connected to)
 *        			- Children (Array of joints connected to this joint)
 */

#ifndef HEADERS_CORE_JOINT_H_
#define HEADERS_CORE_JOINT_H_

#include <vector>
//#include "../gl4/glcorearb.h"
//#include "core_functions.h"
//#include "texture.h"
#include "matrix.h"
#include "shader.h"
#include "helper.h"
//#include "bounding_volume.h"
//#include "vao.h"
//#include "../gamesys/O3D.h"
#include "types.h"

namespace Core {

	class _JointData {
		friend class _Joint;
		Vector3f	vOrigin;					// Starting point of joint, where all rotations happen
		Vector3f	vDestination;				// Ending point of joint, where the next joint will attach if there is one
		Vector3f	vRotation;					// The current rotation values
		Vector3f	vTranslation;				// The current translation values
		Vector3b	vRotationRestriction;		// Restrictions on which axes can be rotated
		Vector3b	vTranslationRestriction;	// Restrictions on which axes can be translated
		Vector4f	vAxisX;						// The current x-axis
		Vector4f	vAxisY;						// The current y-axis, y always aligns with the joint
		Vector4f	vAxisZ;						// The current z-axis
		Matrix44f	mLookAt;					// The current axis transformation
	};

	class _Joint : _JointData {
		private:
			bool bFinished;

		public:
			std::vector<_Joint>	children;
			_Joint();
			_Joint(Vector3f origin, Vector3f dest, Vector3f rotation, Vector3b rotationRestriction, Vector3b translationRestriction);
			void SetJoint(Vector3f origin, Vector3f dest, Vector3f rotation=Vector3f(0.0f), Vector3b rotationRestriction=Vector3b(false), Vector3b translationRestriction=Vector3b(false));
			int AddJoint(Vector3f dest, Vector3f rotation=Vector3f(0.0f), Vector3b rotationRestriction=Vector3b(false), Vector3b translationRestriction=Vector3b(false));
			void SetRotation(Vector3f rotation);
			void DrawJoint(/*Matrix_System &matrix, Shader_System &shader, _Helper &helper*/);
			virtual ~_Joint();
	};

} /* namespace Core */

#endif /* HEADERS_CORE_JOINT_H_ */
