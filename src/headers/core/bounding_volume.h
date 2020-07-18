/*
 * bounding_volume.h
 *
 *  Created on: Feb 18, 2018
 *      Author: bcthund
 */

#ifndef SRC_HEADERS_CORE_BOUNDING_VOLUME_H_
#define SRC_HEADERS_CORE_BOUNDING_VOLUME_H_

#include "core_functions.h"
#include "gl4_5/glcorearb.h"
#include "helper.h"
#include "matrix.h"
#include "shader.h"

namespace Core {
	class _BOUNDING_VOLUME {
		private:
			bool bFinished;								// Set to true when End() has been called
			Vector3f		vScale;
			bool			bCollision;					// Has a collision been detected?
			Matrix44f		mOBB;
			Matrix44f		mAABB;
			Matrix44f		mSphere;
			Matrix44f		mCylinder;

			void DrawIntersection		(Matrix_System &matrix, Shader_System &shader, _Helper &helper);
			void DrawOBB				(Matrix_System &matrix, Shader_System &shader, _Helper &helper, Vector3f translate = Vector3f());
			void DrawAABB				(Matrix_System &matrix, Shader_System &shader, _Helper &helper, Vector3f translate = Vector3f());
			void DrawSphere				(Matrix_System &matrix, Shader_System &shader, _Helper &helper, Vector3f translate = Vector3f());
			void DrawCylinder			(Matrix_System &matrix, Shader_System &shader, _Helper &helper, Vector3f translate = Vector3f());

		public:
			Vector3f		vPosition;						///< Translation of O3D
			Vector3f		vRotation;
			Vector3f		vCP;							// The actual world position of the center (needed for collision)
			Vector3f	*	vTranslate;						// Pointer to the objects translation vector

			enum _BOUNDING_VOLUME_TYPE {
				BOUNDING_VOLUME_NONE,
				BOUNDING_VOLUME_OBB,
				BOUNDING_VOLUME_AABB,
				BOUNDING_VOLUME_SPHERE,
				BOUNDING_VOLUME_CYLINDER
			};

			struct _BB {
				float		fWidth,							///< Difference between Min/Max width
							fLength,						///< Difference between Min/Max length
							fHeight;						///< Difference between Min/Max height
				Vector3f	vMin;							///< Minimim plane positions
				Vector3f	vMax;							///< Maximum plane positions
				Vector3f	vMinP;							///< Minimum plane plus actual position
				Vector3f	vMaxP;							///< Maximum plane plus actual position
				Vector3f	vCenter;						///< All bounding volumes use the vCenter

				_BB() {
					fWidth		= 0.0f;
					fLength		= 0.0f;
					fHeight		= 0.0f;
					vCenter		= Vector3f(0.0f);
				}
			} OBB, AABB;

			struct _CollisionData {
				float		t;								///< Intersection value
				Vector3f	d;								///< Intersection point
				bool		result;							///< Result of the last collision test

				_CollisionData() {
					t			= 0.0f;
					result		= false;
				}
			} cdata;

			struct _BBS {
				float		radius;

				_BBS() {
					radius = 0.0f;
				}
			} Sphere;

			struct _BBC : _BBS {
				Vector3f	p,
							q;
			} Cylinder;

			float			fPadding;						///< Bounding volume padding
			int				iType;							// The current bounding volume type

			_BOUNDING_VOLUME(Vector3f &t);
			~_BOUNDING_VOLUME();
			void init					(_Helper helper);
			void Start					(Vector3f s);
			void CheckMinMaxOBB			(Vector3f v);
			void CheckMinMaxAABB		(Vector3f v);
			void CalcCenter				(_BB &bb);
			void CalcOBB				();
			void CalcAABB				();
			void CheckXYZ				(Vector3f v);									// Check w, h, and l with a single vector
			void Finish					(Matrix_System &matrix);	// Finish bounding volume, perform calculations, bOffset is true if bounding volume should have an origin at the bottom
			void SetPosition			(Vector3f p) { vPosition = p; }
			void SetRotation			(Vector3f r) { vRotation = r; }
			Vector3f GetCenterPosition	() { return vCP; };
			void Draw					(Matrix_System &matrix, Shader_System &shader, _Helper &helper, Vector3f translate = Vector3f(), bool bDrawIntersection=false);
	};

	_BOUNDING_VOLUME::_BOUNDING_VOLUME(Vector3f &t) {
		bCollision			= false;
		vTranslate			= &t;
		bFinished			= false;
		iType				= BOUNDING_VOLUME_NONE;
		vPosition[0]		= 0;
		vPosition[1]		= 0;
		vPosition[2]		= 0;
		vRotation			= Vector3f();
		fPadding			= 10.0f;
	}

	_BOUNDING_VOLUME::~_BOUNDING_VOLUME() {
	}

	void _BOUNDING_VOLUME::init(_Helper helper) {
	}

	void _BOUNDING_VOLUME::Start(Vector3f s) {
		vScale = s;
		bFinished = false;
	}

	void _BOUNDING_VOLUME::CheckMinMaxOBB(Vector3f v) {
		if(v[0] > OBB.vMax.x) OBB.vMax.x = v[0];
		if(v[0] < OBB.vMin.x) OBB.vMin.x = v[0];

		if(v[1] > OBB.vMax.y) OBB.vMax.y = v[1];
		if(v[1] < OBB.vMin.y) OBB.vMin.y = v[1];

		if(v[2] > OBB.vMax.z) OBB.vMax.z = v[2];
		if(v[2] < OBB.vMin.z) OBB.vMin.z = v[2];

		CheckXYZ(v);
	}

	void _BOUNDING_VOLUME::CheckMinMaxAABB(Vector3f v) {
		if(v[0] > AABB.vMax.x) AABB.vMax.x = v[0];
		if(v[0] < AABB.vMin.x) AABB.vMin.x = v[0];

		if(v[1] > AABB.vMax.y) AABB.vMax.y = v[1];
		if(v[1] < AABB.vMin.y) AABB.vMin.y = v[1];

		if(v[2] > AABB.vMax.z) AABB.vMax.z = v[2];
		if(v[2] < AABB.vMin.z) AABB.vMin.z = v[2];

		// We use the OBB to determine this data
		//CheckXYZ(v);
	}

	void _BOUNDING_VOLUME::CalcOBB() {
		OBB.fWidth		= (OBB.vMax.x + fabs(OBB.vMin.x));
		OBB.fHeight		= (OBB.vMax.y + fabs(OBB.vMin.y));
		OBB.fLength		= (OBB.vMax.z + fabs(OBB.vMin.z));

		OBB.vCenter[0]		= ((OBB.vMin.x) + (OBB.fWidth /2.0f));
		OBB.vCenter[1]		= ((OBB.vMin.y) + (OBB.fHeight/2.0f));
		OBB.vCenter[2]		= ((OBB.vMin.z) + (OBB.fLength/2.0f));

		OBB.vCenter.x *= vScale.x;
		OBB.vCenter.y *= vScale.y;
		OBB.vCenter.z *= vScale.z;

		OBB.fWidth  *= vScale.x;
		OBB.fHeight *= vScale.y;
		OBB.fLength *= vScale.z;

		OBB.fWidth  += fPadding;
		OBB.fHeight += fPadding;
		OBB.fLength += fPadding;

		OBB.vMinP = (OBB.vMin * vScale) - (fPadding/2);
		OBB.vMaxP = (OBB.vMax * vScale) + (fPadding/2);
	}

	void _BOUNDING_VOLUME::CalcAABB() {
		AABB.fWidth		= (AABB.vMax.x + fabs(AABB.vMin.x));
		AABB.fHeight	= (AABB.vMax.y + fabs(AABB.vMin.y));
		AABB.fLength	= (AABB.vMax.z + fabs(AABB.vMin.z));

		AABB.vCenter.x	= ((AABB.vMin.x) + (AABB.fWidth /2.0f));
		AABB.vCenter.y	= ((AABB.vMin.y) + (AABB.fHeight/2.0f));
		AABB.vCenter.z	= ((AABB.vMin.z) + (AABB.fLength/2.0f));

		AABB.fWidth  += fPadding;
		AABB.fHeight += fPadding;
		AABB.fLength += fPadding;

		AABB.vMinP = AABB.vMin + vPosition - (fPadding/2);
		AABB.vMaxP = AABB.vMax + vPosition + (fPadding/2);
	}

	void _BOUNDING_VOLUME::CheckXYZ(Vector3f v) {
		Vector3f vDist;

		v.x *=vScale.x;
		v.y *=vScale.y;
		v.z *=vScale.z;

		// Default to using OBB center, as it shouldn't matter
		vDist = v - OBB.vCenter;

		float fXZ = (vDist.x*vDist.x)+(vDist.z*vDist.z);
		float fXYZ = fXZ + (vDist.y*vDist.y);

		if (fXZ > Cylinder.radius) {
			Cylinder.radius = fXZ;
		}

		if (fXYZ > Sphere.radius) {
			Sphere.radius = fXYZ;
		}
	}

	void _BOUNDING_VOLUME::Finish(Matrix_System &matrix) {
		Cylinder.radius = sqrtf(Cylinder.radius) + (fPadding/2);
		Sphere.radius = sqrtf(Sphere.radius) + (fPadding/2);

		// Default to using OBB center, as it shouldn't matter
		vCP = vPosition + OBB.vCenter;

		float fPQ = OBB.fHeight/2.0f;
		Cylinder.p = Vector3f(vCP.x, vCP.y + fPQ, vCP.z);
		Cylinder.q = Vector3f(vCP.x, vCP.y - fPQ, vCP.z);

		matrix.Push();
			matrix.SetIdentity();
			//matrix.Translate( vPosition.x+OBB.vCenter[0], vPosition.y+OBB.vCenter[1], vPosition.z+OBB.vCenter[2] );
			matrix.Translate( vCP );
			matrix.Rotate(Degrees(vRotation.x).toRadians(), 1.0, 0.0, 0.0);
			matrix.Rotate(Degrees(vRotation.y).toRadians(), 0.0, 1.0, 0.0);
			matrix.Rotate(Degrees(vRotation.z).toRadians(), 0.0, 0.0, 1.0);

			matrix.Push();
				matrix.Scale( OBB.fWidth, OBB.fHeight, OBB.fLength);
				mOBB = matrix.GetModelView();
			matrix.Pop();

			matrix.Push();
				matrix.Scale(Sphere.radius);
				mSphere = matrix.GetModelView();
			matrix.Pop();

			matrix.Push();
				matrix.Scale(Cylinder.radius, OBB.fHeight-(fPadding/2), Cylinder.radius);
				mCylinder = matrix.GetModelView();
			matrix.Pop();
		matrix.Pop();

		matrix.Push();
			matrix.SetIdentity();
			matrix.Translate( vPosition.x+AABB.vCenter[0], vPosition.y+AABB.vCenter[1], vPosition.z+AABB.vCenter[2] );
			matrix.Scale( AABB.fWidth, AABB.fHeight, AABB.fLength);
			mAABB = matrix.GetModelView();
		matrix.Pop();

		bFinished = true;
	}

	void _BOUNDING_VOLUME::Draw(Matrix_System &matrix, Shader_System &shader, _Helper &helper, Vector3f translate, bool bDrawIntersection) {
		if(iType == BOUNDING_VOLUME_OBB) 			DrawOBB(matrix, shader, helper, translate);
		else if(iType == BOUNDING_VOLUME_AABB) 		DrawAABB(matrix, shader, helper, translate);
		else if(iType == BOUNDING_VOLUME_SPHERE) 	DrawSphere(matrix, shader, helper, translate);
		else if(iType == BOUNDING_VOLUME_CYLINDER) 	DrawCylinder(matrix, shader, helper, translate);

		if(iType != BOUNDING_VOLUME_NONE && bDrawIntersection) {
			DrawIntersection(matrix, shader, helper);
		}
	}

	void _BOUNDING_VOLUME::DrawOBB(Matrix_System &matrix, Shader_System &shader, _Helper &helper, Vector3f translate) {
		if(bFinished) {
			matrix.Push();
				matrix.Translate(translate);
				matrix.Apply(mOBB);
				matrix.SetTransform();
				shader.use(GLS_BOUNDINGVOLUME_OBB);
				shader.getUniform(GLS_BOUNDINGVOLUME_OBB);
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				helper.drawBox();
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			matrix.Pop();
		}
	}

	void _BOUNDING_VOLUME::DrawAABB(Matrix_System &matrix, Shader_System &shader, _Helper &helper, Vector3f translate) {
		if(bFinished) {
			matrix.Push();
				matrix.Translate(translate);
				matrix.Apply(mAABB);
				matrix.SetTransform();
				shader.use(GLS_BOUNDINGVOLUME_AABB);
				shader.getUniform(GLS_BOUNDINGVOLUME_AABB);
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				helper.drawBox();
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			matrix.Pop();
		}
	}

	void _BOUNDING_VOLUME::DrawSphere(Matrix_System &matrix, Shader_System &shader, _Helper &helper, Vector3f translate) {
		if(bFinished) {
			matrix.Push();
				matrix.Translate(translate);
				matrix.Apply(mSphere);
				matrix.SetTransform();
				shader.use(GLS_BOUNDINGVOLUME_SPHERE);
				shader.getUniform(GLS_BOUNDINGVOLUME_SPHERE);
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				helper.drawSphere();
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			matrix.Pop();
		}
	}

	void _BOUNDING_VOLUME::DrawCylinder(Matrix_System &matrix, Shader_System &shader, _Helper &helper, Vector3f translate) {
		if(bFinished) {
			matrix.Push();
				matrix.Translate(translate);
				matrix.Apply(mCylinder);
				matrix.SetTransform();
				shader.use(GLS_BOUNDINGVOLUME_CYLINDER);
				shader.getUniform(GLS_BOUNDINGVOLUME_CYLINDER);
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				helper.drawCylinder();
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			matrix.Pop();
		}
	}

	void _BOUNDING_VOLUME::DrawIntersection(Matrix_System &matrix, Shader_System &shader, _Helper &helper) {
		if(cdata.result) {
			matrix.Push();
				matrix.Translate(cdata.d);
				matrix.SetTransform();
				//shader.use(GLS_POINTS);
				//shader.getUniform(GLS_POINTS);
				//glPointSize(10.0f);

				//helper.drawPoint(50.0f, helper.GLPOINT_RING, colors->yellow, 5, 0.5);
				//helper.drawPoint(200.0f, helper.GLPOINT_SPIRAL_CLIPPED, colors->yellow, 5);

				helper.drawPoint(50.0f, 0.0, colors[colors().Yellow], helper.GLPOINT_ROSE, 6);			// TODO: Add to color pallette
				helper.drawPoint(50.0f, 0.0, colors[colors().Red], helper.GLPOINT_ROSE_OUTLINE, 6);		// TODO: Add to color pallette

				//glPointSize(1.0f);
			matrix.Pop();


//			// TODO: Particle Test (needs a one-shot system)
//			{
//				std::string sName = "Sparks_"+str_rand(4);
//				Core::_ParticleEmitterData *data = new Core::_ParticleEmitterData();
//				data->sName						= sName;
//				data->sTexture					= "burst.png";
//				data->bAdditiveBlending			= true;
//				data->fEmitterLifeTime			= 1.5f;		// seconds (0=infinite)
//				data->fEmitterStartFade			= 8.0f;
//				data->fGravityEffect			= 0.025f;	// multiplier	(object mass)
//				data->fParticleLifeTime			= 0.75f;		// seconds (0=until floor value)
//				data->fClip						= -10.0f;
//				data->fSpeed					= 10.0f;			// multiplier
//				data->fRotation					= 0.0f;
//				data->fRotationSpeed			= 0.0f;
//				data->vVelocitySpread.x			= Core::Vector2f(-0.25f, 0.25f);
//				data->vVelocitySpread.y			= Core::Vector2f(-0.0f, 0.15f);
//				data->vVelocitySpread.z			= Core::Vector2f(-0.25f, 0.25f);
//				data->fStartingSize				= 16;		// pixels
//				data->vSpawnSpread.x			= Core::Vector2f(-0.0f, 0.0f);
//				data->vSpawnSpread.y			= Core::Vector2f(-0.0f, 0.0f);
//				data->vSpawnSpread.z			= Core::Vector2f(-0.0f, 0.0f);
//				data->vLifeVariation			= Core::Vector2f(-1.0f, 1.0f);
//				data->vGravityVariation			= Core::Vector2f(-0.0f, 0.0f);
//				data->vSizeVariation			= Core::Vector2f(-1.0f, 1.0f);
//				data->fRotation					= 0.0f;
//				data->vRotationVariation		= Core::Vector2f(-0.0f, 0.0f);
//				data->fRotationSpeed			= 0.0f;
//				data->vRotationSpeedVariation	= Core::Vector2f(-2.0f, 2.0f);
//				data->iNum						= 100;				// maxmimum particles
//				data->iPPS						= 250;					// particles per second
//				data->iRate						= 10;				// update rate
//				data->vSource					= new Core::Vector3f(cdata.d);
//				data->vTarget					= new Core::Vector3f(0.0f, 1.0f, 0.0f);
//				Core::particles->create(data);
//				Core::particles->calc(sName);
//			}

		}
	}
}

#endif /* SRC_HEADERS_CORE_BOUNDING_VOLUME_H_ */
