/*
 * collision.h
 *
 *  Created on: Feb 27, 2018
 *      Author: bcthund
 */

#ifndef SRC_HEADERS_CORE_COLLISION_H_
#define SRC_HEADERS_CORE_COLLISION_H_

#include "core_functions.h"

namespace Core {
	class _Collision {
		private:
			/*Matrix_System * matrix;*/
			inline Vector3f CalcIntersection(Vector3f p, Vector3f q, float t) { return p + q * t; }
			void SetCData(_BOUNDING_VOLUME &bv, Vector3f d, float t, bool result);

			// Ray intersection tests
			bool Ray_OBB		(	Vector3f p,		Vector3f d,		_BOUNDING_VOLUME &s, bool bUpdateCData);
			bool Ray_AABB		(	Vector3f p,		Vector3f d,		_BOUNDING_VOLUME &a, bool bUpdateCData);
			bool Ray_AABB		(	Vector3f p,		Vector3f d,		_BOUNDING_VOLUME &a, _BOUNDING_VOLUME::_BB &b, bool bUpdateCData);
			bool Ray_Sphere		(	Vector3f p,		Vector3f d,		_BOUNDING_VOLUME &s);
			bool Ray_SphereFast	(	Vector3f p,		Vector3f d,		_BOUNDING_VOLUME &s);
			bool Ray_Cylinder	(	Vector3f vP,	Vector3f vD,	_BOUNDING_VOLUME &bv, bool bUpdateCData);
			//bool Ray_Plane();
			//bool Ray_Quad();
			//bool Ray_Triangle();
			//bool Line_Quad();
			//bool Line_Triangle();

		public:
			_Collision(/*Matrix_System &m*/);
			~_Collision();
			bool Ray(Vector3f p, Vector3f d, _BOUNDING_VOLUME &s, bool bUpdateCData=false);		// Perform a ray intersection test on the active bounding volume

			/*
			 * 32 flags for manual tracking of collision update requests
			 *
			 * For Example: When the mouse is clicked and a new ray
			 * 	is created, a flag can be set here as well. Then
			 * 	where the user wants to do a collision test on that
			 * 	ray they can first check if the update request is
			 * 	needed before wasting time doing a test that has
			 * 	already been done. Then the flag can be reset to false
			 * 	by the user to prevent further updates.
			 *
			 * The flag can also be used as an ongoing flag, as long
			 * 	as it is active the collision tests will continue to
			 * 	be performed until the flag is set to false.
			 *
			 */
			bool bUpdateRequest[32];

			//bool OBB_Point			(_BOUNDING_VOLUME a, Vector3f b);
			//bool OBB_OBB			(_BOUNDING_VOLUME a, _BOUNDING_VOLUME b);
			//bool OBB_Sphere			(_BOUNDING_VOLUME a, _BOUNDING_VOLUME b);
			//bool OBB_Cylinder		(_BOUNDING_VOLUME a, _BOUNDING_VOLUME b);
			//bool Sphere_Point		(_BOUNDING_VOLUME a, Vector3f b);
			//bool Sphere_Sphere		(_BOUNDING_VOLUME a, _BOUNDING_VOLUME b);
			//bool Sphere_Cylinder	(_BOUNDING_VOLUME a, _BOUNDING_VOLUME b);
			//bool Cylinder_Point		(_BOUNDING_VOLUME a, Vector3f b);
			//bool Cylinder_Cylinder	(_BOUNDING_VOLUME a, _BOUNDING_VOLUME b);

			//bool Sphere_Triangle(_BOUNDING_VOLUME s, Vector3f a, Vector3f b, Vector3f c);	//return &Point p
			//bool Sphere_Plane(_BOUNDING_VOLUME s, Vector3f a, Vector3f b, Vector3f n);
			//void ClosestPointOnOBB();

	};

	_Collision::_Collision(/*Matrix_System &m*/) {
		//matrix = &m;

		for (int n=0; n<32; n++) {
			bUpdateRequest[n] = false;
		}
	}

	_Collision::~_Collision() {
	}

	bool _Collision::Ray(Vector3f p, Vector3f d, _BOUNDING_VOLUME &s, bool bUpdateCData) {
		if(s.iType == _BOUNDING_VOLUME::BOUNDING_VOLUME_OBB) return Ray_OBB(p, d, s, bUpdateCData);
		else if(s.iType == _BOUNDING_VOLUME::BOUNDING_VOLUME_AABB) return Ray_AABB(p, d, s, bUpdateCData);
		else if(s.iType == _BOUNDING_VOLUME::BOUNDING_VOLUME_SPHERE) {
			if(bUpdateCData) return Ray_Sphere(p, d, s);
			else return Ray_SphereFast(p, d, s);
		}
		else if(s.iType == _BOUNDING_VOLUME::BOUNDING_VOLUME_CYLINDER) return Ray_Cylinder(p, d, s, bUpdateCData);
		return false;
	}

	bool _Collision::Ray_OBB		(	Vector3f p,		Vector3f d,		_BOUNDING_VOLUME &a, bool bUpdateCData) {
		Vector4f vCPT = Vector4f(-a.vPosition.x-a.vTranslate->x, -a.vPosition.y-a.vTranslate->y, -a.vPosition.z-a.vTranslate->z, 0.0f);
		Vector4f vPT  = Vector4f(p.x, p.y, p.z, 0.0f) + vCPT;
		Vector4f vDT  = Vector4f(d.x, d.y, d.z, 0.0f);

		matrix->Push();
			matrix->SetIdentity();
			matrix->Rotate(Degrees(a.vRotation.z).toRadians(),  0.0,  0.0, 1.0);
			matrix->Rotate(Degrees(a.vRotation.y).toRadians(),  0.0, 1.0,  0.0);
			matrix->Rotate(Degrees(a.vRotation.x).toRadians(), 1.0,  0.0,  0.0);
			Matrix44f mRot = matrix->GetRotView();
			Vector4f vPRT = mRot * vPT;
			Vector4f vDRT = mRot * vDT;
		matrix->Pop();

//		std::cout << "Ray_OBB:" << std::endl;
//		std::cout << "\t          p:" << p.x				<< ", " << p.y					<< ", " << p.z				<< std::endl;
//		std::cout << "\t          d:" << d.x				<< ", " << d.y					<< ", " << d.z				<< std::endl;
//		std::cout << "\t        vPR:" << vPT.x				<< ", " << vPT.y				<< ", " << vPT.z			<< std::endl;
//		std::cout << "\t        vDR:" << vDT.x				<< ", " << vDT.y				<< ", " << vDT.z			<< std::endl;
//		std::cout << "\t       vPRT:" << vPRT.x				<< ", " << vPRT.y				<< ", " << vPRT.z			<< std::endl;
//		std::cout << "\t       vDRT:" << vDRT.x				<< ", " << vDRT.y				<< ", " << vDRT.z			<< std::endl;
//		std::cout << "\t       vCPT:" << vCPT.x				<< ", " << vCPT.y				<< ", " << vCPT.z			<< std::endl;
//		std::cout << "\t a.position:" << a.vPosition.x		<< ", " << a.vPosition.y		<< ", " << a.vPosition.z	<< std::endl;
//		std::cout << "\ta.translate:" << a.vTranslate->x	<< ", " << a.vTranslate->y		<< ", " << a.vTranslate->z	<< std::endl;
//		std::cout << std::endl;

		bool bReturn = Ray_AABB(Vector3f(vPRT.x, vPRT.y, vPRT.z), Vector3f(vDRT.x, vDRT.y, vDRT.z), a, a.OBB, false);
		if(bUpdateCData) SetCData(a, CalcIntersection(p, d, a.cdata.t), a.cdata.t, bReturn);
		return bReturn;
	}

	bool _Collision::Ray_AABB		(	Vector3f p,		Vector3f d,		_BOUNDING_VOLUME &a, bool bUpdateCData) {
		bool bReturn = Ray_AABB(p-(*a.vTranslate), d, a, a.AABB, false);
		if(bUpdateCData) SetCData(a, CalcIntersection(p, d, a.cdata.t), a.cdata.t, bReturn);
		return bReturn;
	}

	bool _Collision::Ray_AABB		(	Vector3f p,		Vector3f d,		_BOUNDING_VOLUME &a, _BOUNDING_VOLUME::_BB &b, bool bUpdateCData) {
		const float EPSILON = 0.0001;
		float tmin = 0.0f;
		float tmax = 1024.0f;
		for(int i=0; i<3; i++) {
			if(fabs(d[i]) < EPSILON) {
				if(p[i] < b.vMinP[i] || p[i] > b.vMaxP[i]) goto ReturnFalse;
			}
			else {
				float ood = 1.0f / d[i];
				float t1 = (b.vMinP[i] - p[i]) * ood;
				float t2 = (b.vMaxP[i] - p[i]) * ood;

				if(t1>t2) std::swap(t1,t2);

				tmin = std::max(tmin, t1);
				tmax = std::min(tmax, t2);

				if(tmin>tmax) goto ReturnFalse;
			}
		}

		if(bUpdateCData) SetCData(a, CalcIntersection(p, d, tmin), tmin, true);
		else a.cdata.t = tmin;	// Always save this in case OBB needs it
		return true;

		ReturnFalse:
		if(bUpdateCData) SetCData(a, Vector3f(0.0f), 0.0f, false);
		return false;
	}

	bool _Collision::Ray_Sphere(Vector3f p, Vector3f d, _BOUNDING_VOLUME &s) {
//		std::cout << "Doing Collistion Test:" << std::endl;
//		std::cout << "\t   p = " << p.x << ", " << p.y << ", " << p.z << std::endl;
//		std::cout << "\t   d = " << d.x << ", " << d.y << ", " << d.z << std::endl;
//		std::cout << "\t s.c = " << s.vCenter.x << ", " << s.vCenter.y << ", " << s.vCenter.z << std::endl;
//		std::cout << "\ts.cp = " << s.vCP.x << ", " << s.vCP.y << ", " << s.vCP.z << std::endl;
//		std::cout << "\t s.r = " << s.fSphereRadius << std::endl << std::endl;

		float discr = 0.0f,
			  t		= 0.0f;

		Vector3f m = (p-(*s.vTranslate)) - s.GetCenterPosition();
		float b = Core::gmath.Dot(m, d);
		float c = Core::gmath.Dot(m, m) - (s.Sphere.radius * s.Sphere.radius);

		if(c > 0.0f && b > 0.0f) goto ReturnFalse;
		discr = b * b - c;

		if(discr < 0.0f) goto ReturnFalse;

		t = -b - std::sqrt(discr);

		if(t < 0.0f) t = 0.0f;

		// Ray has hit sphere otherwise
		SetCData(s, CalcIntersection(p, d, t), t, true);
		return true;

		ReturnFalse:
		SetCData(s, Vector3f(0.0f), 0.0f, false);
		return false;
	}

	bool _Collision::Ray_SphereFast(Vector3f p, Vector3f d, _BOUNDING_VOLUME &s) {
//		std::cout << "Doing Collistion Test:" << std::endl;
//		std::cout << "\t   p = " << p.x << ", " << p.y << ", " << p.z << std::endl;
//		std::cout << "\t   d = " << d.x << ", " << d.y << ", " << d.z << std::endl;
//		std::cout << "\t s.c = " << s.vCenter.x << ", " << s.vCenter.y << ", " << s.vCenter.z << std::endl;
//		std::cout << "\ts.cp = " << s.vCP.x << ", " << s.vCP.y << ", " << s.vCP.z << std::endl;
//		std::cout << "\t s.r = " << s.fSphereRadius << std::endl << std::endl;

		Vector3f m = (p-(*s.vTranslate)) - s.GetCenterPosition();
		float c = Core::gmath.Dot(m, m) - (s.Sphere.radius * s.Sphere.radius);

		// At least one real root, intersection exists
		if(c <= 0.0f) return true;

		float b = Core::gmath.Dot(m, d);

		// Ray origin outside sphere, pointing away
		if(b > 0.0f) return false;

		float disc = b*b - c;

		// Negative discriminant means ray misses sphere
		if(disc < 0.0f) return false;

		// Ray has hit sphere otherwise
		return true;
	}

	bool _Collision::Ray_Cylinder(Vector3f vP, Vector3f vD, _BOUNDING_VOLUME &bv, bool bUpdateCData) {
		float	 fRayLength = 1000,
				 r			= bv.Cylinder.radius,
				 EPSILON	= 0.0001f,
				 t			= 0.0f;

		Vector3f sa			= vP - (*bv.vTranslate),
				 sb			= sa + (vD*fRayLength),
				 p			= bv.Cylinder.p,
				 q			= bv.Cylinder.q,
				 d			= q - p,
				 m			= sa - p,
				 n			= sb - sa;

		bool bReturn = false;

		// Cross-initialization prevention
		float	nn,
				mn,
				a,
				k,
				c,
				b,
				discr,
				t0;

//		std::cout << "Testing Cylinder:" << std::endl;
//		std::cout << "\t        sa:" << sa.x	<< ", " << sb.y		<< ", " << sa.z		<< std::endl;
//		std::cout << "\t        sb:" << sb.x	<< ", " << sa.y		<< ", " << sb.z		<< std::endl;
//		std::cout << "\t         p:" << p.x		<< ", " << p.y		<< ", " << p.z		<< std::endl;
//		std::cout << "\t         q:" << q.x		<< ", " << q.y		<< ", " << q.z		<< std::endl;
//		std::cout << "\t         d:" << d.x		<< ", " << d.y		<< ", " << d.z		<< std::endl;
//		std::cout << "\t         m:" << m.x		<< ", " << m.y		<< ", " << m.z		<< std::endl;
//		std::cout << "\t         n:" << n.x		<< ", " << n.y		<< ", " << n.z		<< std::endl;
//		std::cout << "\t         r:" << r << std::endl << std::endl;

		float md = Core::gmath.Dot(m, d);
		float nd = Core::gmath.Dot(n, d);
		float dd = Core::gmath.Dot(d, d);

		// Segment fully outside of endcap
		if(md < 0.0f && md + nd < 0.0f) goto ReturnFalse;	// Outside p ide
		if(md > dd && md + nd > dd) goto ReturnFalse;		// Outside q side

		nn = Core::gmath.Dot(n, n);
		mn = Core::gmath.Dot(m, n);
		a = dd * nn - nd * nd;
		k = Core::gmath.Dot(m, m) - (r * r);
		c = dd * k - md * md;

		if(std::fabs(a) < EPSILON) {
			// Segment runs parallel to axis
			if(c > 0.0f) goto ReturnFalse;
			// Segment intersects cylinder
			if(md < 0.0f) t = -mn / nn;						// Intersect segment against p endcap
			else if(md > dd) t = (nd - mn) / nn;			// Intersect segment against q endcap
			else t = 0.0f;									// 'a' inside cylinder
			if(bUpdateCData) SetCData(bv, CalcIntersection(vP, vD*fRayLength, t), t, true);
			return true;
		}

		b = dd * mn - nd * md;
		discr = b * b - a * c;
		if(discr < 0.0f) goto ReturnFalse;

		t0 = t = (-b - std::sqrt(discr)) / a;
		// Intersection lies outside segment (commented for RAY intersection)
		//if(t < 0.0f || t > 1.0f) { std::cout << " -* 4" << std::endl; return false; }
		if(md + t * nd < 0.0f) {						// Intersection outside p-side cylinder
				if(nd <= 0.0f) goto ReturnFalse;
				t = -md / nd;
				bReturn = k + t * (2.0f * mn + t * nn) <= 0.0f;
				if(bUpdateCData) SetCData(bv, CalcIntersection(vP, vD*fRayLength, t), t, bReturn);
				return bReturn;
		}
		else if(md + t * nd > dd) {						// Intersection outside q-side cylinder
			if(nd >= 0.0f) goto ReturnFalse;
			t = (dd - md) / nd;
			bReturn = k + dd - 2.0f * md + t * (2.0f * (mn - nd) + t * nn) <= 0.0f;
			if(bUpdateCData) SetCData(bv, CalcIntersection(vP, vD*fRayLength, t), t, bReturn);
			return bReturn;
		}
		t = t0;
		bReturn = t >= 0.0f && t <= 1.0f;
		if(bUpdateCData) SetCData(bv, CalcIntersection(vP, vD*fRayLength, t), t, bReturn);
		return bReturn;

		ReturnFalse:
		if(bUpdateCData) SetCData(bv, Vector3f(0.0f), 0.0f, false);
		return false;
	}

	void _Collision::SetCData(_BOUNDING_VOLUME &bv, Vector3f d, float t, bool result) {

		//std::cout << "Setting Collision Data:\tt = " << t << " \td = (" << d.x << ", " << d.y << ", " << d.z << ") \tresult = " << result << std::endl;

		bv.cdata.t = t;
		bv.cdata.d = d;
		bv.cdata.result = result;
	}
}

#endif /* SRC_HEADERS_CORE_COLLISION_H_ */
