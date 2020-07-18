/*
 * gmath.h
 *
 *  Created on: Oct 2, 2018
 *      Author: bcthund
 */

#ifndef HEADERS_CORE_GMATH_H_
#define HEADERS_CORE_GMATH_H_

#include "types.h"

namespace Core {
	static class _gmath {
		/*
		 *		[ ] ray plane
		 *		[ ] half space
		 *		[ ] intersect triangle
		 *		[ ] scalar
		 *		[ ] dot product
		 *		[ ] point in quad
		 *		[ ] sameside
		 *		[ ] point in triangle
		 */

		public:
			inline float sqr			(float f)														{ return f*f; }
			inline float sqr			(int i)															{ return i*i; }
			inline float sqr			(unsigned short int i)											{ return i*i; }
			inline float sqr			(short int i)													{ return i*i; }
			inline void  Average		(Vector3f &out, Vector3f a, Vector3f b)							{ out = ( a + b ) / 2; }
			inline void  Average		(Vector3f &out, Vector3f a, Vector3f b, Vector3f c)				{ out = ( a + b + c ) / 3; }
			inline void  Average		(Vector3f &out, Vector3f a, Vector3f b, Vector3f c, Vector3f d) { out = ( a + b + c + d ) / 4; }
			inline void  Average		(float &out, float a, float b)									{ out = (a + b)/2; }
			inline void  Average		(float &out, float a, float b, float c)							{ out = (a + b + c)/3; }
			inline void  Average		(float &out, float a, float b, float c, float d)				{ out = (a + b + c + d)/4; }
			inline void  Cross			(Vector3f &i, Vector3f u, Vector3f v)							{ i = Vector3f((u[1] * v[2]) - (u[2] * v[1]), -((u[0] * v[2]) - (u[2] * v[0])), (u[0] * v[1]) - (u[1] * v[0])); }
			inline float Dot2f			(Vector2f a, Vector2f b)										{ return (a[0]*b[0])+(a[1]*b[1]); }
			inline float Dot			(Vector3f a, Vector3f b)										{ return (a[0]*b[0])+(a[1]*b[1])+(a[2]*b[2]); }
			inline float ScalarTriple	(Vector3f u, Vector3f v, Vector3f w)							{ Vector3f i; Cross(i, u, v); return Dot(i, w); }
			inline void  Max			(float &in, float fMax)											{ if (in > fMax) in = fMax; }

			Matrix44f LookAt(Vector3f vSource, Vector3f vDest, Vector3f vUp) {
				Vector3f	vLook, vRight;
				vLook = vSource - vDest;
				vLook = vLook.normal();		//Core::gmath.Normalize(vLook);
				Cross(vRight, vUp, vLook);

				Matrix44f	mLookAt = {	vRight[0],		vRight[1],		vRight[2],		0.0f,
										0.0f,			1.0f,			0.0f,			0.0f,
										vLook[0],		vLook[1],		vLook[2],		0.0f,
										vDest[0],		vDest[1],		vDest[2],		1.0f };

				return mLookAt;
			}

			Matrix44f LookAt(Vector3f vSource, Vector3f vDest) {
				Vector3f	vUp = { 0.0, 1.0, 0.0};
				Vector3f	vLook, vRight;
				vLook = vSource - vDest;
				vLook = vLook.normal();		//Core::gmath.Normalize(vLook);
				Cross(vRight, vUp, vLook);

				Matrix44f	mLookAt = {	vRight[0],		vRight[1],		vRight[2],		0.0f,
										0.0f,			1.0f,			0.0f,			0.0f,
										vLook[0],		vLook[1],		vLook[2],		0.0f,
										vDest[0],		vDest[1],		vDest[2],		1.0f };

				return mLookAt;
			}

			inline bool PointQuad2d(Vector2f p, Vector2f u, Vector2f v) {
				if ( (p[0]>u[0]) && (p[0]<v[0]) && (p[1]>u[1]) && (p[1]<v[1])) return true;
				else return false;
			}

			Vector3f Cross(Vector3f u, Vector3f v, bool bNorm=false) {
				Vector3f vReturn;
//				vReturn[0] =  (u[1] * v[2]) - (u[2] * v[1]);
//				vReturn[1] =-((u[0] * v[2]) - (u[2] * v[0]));
//				vReturn[2] =  (u[0] * v[1]) - (u[1] * v[0]);

				vReturn[0] =  (u[1] * v[2]) - (u[2] * v[1]);
				vReturn[1] =  (u[2] * v[0]) - (u[0] * v[2]);
				vReturn[2] =  (u[0] * v[1]) - (u[1] * v[0]);

				if(bNorm) {
					float fMag = sqrt((vReturn[0]*vReturn[0])+(vReturn[1]*vReturn[1])+(vReturn[2]*vReturn[2]));
					vReturn[0] = vReturn[0]/fMag;
					vReturn[1] = vReturn[1]/fMag;
					vReturn[2] = vReturn[2]/fMag;
				}

				return vReturn;
			}

			inline float Hypot(Vector2f a, Vector2f b, bool bGetRoot=false) {
				float out;
				Vector2f i;
				//Diff(i, a, b);
				i = a - b;
				out = (i[0]*i[0]) + (i[1]*i[1]);
				if (bGetRoot) out = sqrt(out);
				return out;
			}

			inline float Hypot(float a1, float a2, float b1, float b2, bool bGetRoot=false) {
				Vector2f a = {a1, a2};
				Vector2f b = {b1, b2};

				float out;
				Vector2f i;
				//Diff(i, a, b);
				i = a - b;
				out = (i[0]*i[0]) + (i[1]*i[1]);
				if (bGetRoot) out = sqrt(out);
				return out;
			}

			inline void Normalize(Vector3f &i) {
				float mag = sqrt(i[0]*i[0]+i[1]*i[1]+i[2]*i[2]);
				i[0] = i[0]/mag;
				i[1] = i[1]/mag;
				i[2] = i[2]/mag;
			}

			inline void BubbleSort(int *array,int length)//Bubble sort function
			{
				int i,j;
				for(i=0;i<length;i++)
				{
					for(j=0;j<i;j++)
					{
						if(array[i]>array[j])
						{
							int temp=array[i]; //swap
							array[i]=array[j];
							array[j]=temp;
						}

					}

				}

			}

			float pyth(Vector3f p) {
			 Vector3f vSquare;
			 vSquare.x = sqr(p.x);
			 vSquare.y = sqr(p.y);
			 vSquare.z = sqr(p.z);

			 return sqrt(vSquare.x+vSquare.y+vSquare.z);
			}
			void calcDistance(Vector3f p, Vector3f q, float &d) {
			 Vector3f pq;

			 pq.x = q.x - p.x;
			 pq.y = q.y - p.y;
			 pq.z = q.z - p.z;

			 d = pyth(pq);
			}

			/*
			 * Get the halfspace calculation
			 * bClamp returns 0 or 1
			 */
			float halfSpace(Vector3f p, Vector3f q, Vector3f a, Vector3f c, bool bClamp=false) {
			 Vector3f pq, pa, pc;
			 pq = q - p;
			 pa = a - p;
			 pc = c - p;
			 Vector3f m;
			 Cross(m, pc, pq);

			 float v = Dot(pa, m);

			 if (bClamp) {
				 if(v < 0.0f) v = 0.0f;
				 else v = 1.0f;
			 }
			 return v;
			}

			/*
			 * Get the halfspace as 0 or 1
			 */
			int halfSpace(Vector2f p, Vector2f a, Vector2f b) {
			/*
			 * Cross([b-a], [p-a]);
			 */

			 Vector2f ba, pa;
			 ba = b - a;
			 pa = p - a;

			 Vector3f m;
			 Cross(m, Vector3f(ba.x, ba.y, 0.0f), Vector3f(pa.x, pa.y, 0.0f));
			 float v = Dot(Vector3f(ba.x, ba.y, 0.0f), Vector3f(pa.x, pa.y, 0.0f));

			 if(v < 0.0f) v = 0.0f;
			 else v = 1.0f;
			 return v;
			}

			int halfSpace(float p1, float p2, float a1, float a2, float b1, float b2, float c1, float c2) {
			/*
			 * Cross([b-a], [p-a]);
			 */

			 Vector3f ba, pa, pc;

			 ba.x = b1 - a1;
			 ba.y = 0.0f;
			 ba.z = b2 - a2;

			 pa.x = p1 - a1;
			 pa.y = 0.0f;
			 pa.z = p2 - a2;

			 pc.x = p1 - c1;
			 pc.y = 0.0f;
			 pc.z = p2 - c2;

			 Vector3f m;
			 Cross(m, ba, pa);

			 float v = Dot(ba, pa);

			 if(v < 0.0f) v = 0.0f;
			 else v = 1.0f;
			 return v;
			}

			int IntersectTri(Vector3f p, Vector3f q, Vector3f a, Vector3f b, Vector3f c, float &u, float &v, float &w, float &t) {
			 Vector3f qp, ab, ac, ap, e;

			 qp = p - q;
			 ab = b - a;
			 ac = c - a;

			 //Compute Normal
			 Vector3f n;
			 Cross(n, ab, ac);

			 //Compute denominator
			 float d = Dot(qp, n);
			 if (d<= 0.0f) return 2; //Ray is parallel to or points away from triangle

			 //Compute Ray Intersection
			 ap = p - a;

			 t = Dot(ap, n);
			 //if (t < 0.0f) return 0;
			 //if (t > d) return 0; //This test for segment only, not ray test

			 //Compute Barycentric Coordinates, and test bounds
			 Cross(e, qp, ap);
			 v = Dot(ac, e);
			 //if (v < 0.0f || v > d) return 0;
			 w = -Dot(ab, e);
			 //if (w < 0.0f || v+w > d) return 0;

			 //Intersection Valid, compute last coordinate
			 float ood = 1.0f / d;
			 t *= ood;
			 v *= ood;
			 w *= ood;
			 u = 1.0f - v - w;
			 return 1;
			}

			/*
			 * 2D sameside calc, height auto set to zero
			 */
			inline bool SameSide(float p1, float p2, float q1, float q2, float a1, float a2, float b1, float b2) {
			 Vector3f p = {p1, 0.0f, p2};
			 Vector3f q = {q1, 0.0f, q2};
			 Vector3f a = {a1, 0.0f, a2};
			 Vector3f b = {b1, 0.0f, b2};

			 Vector3f cp1, cp2;
			 Vector3f ba, p1a, p2a;
			 //Diff(ba, b, a);
			 ba = b - a;
			 //Diff(p1a, p, a);
			 p1a = p - a;
			 //Diff(p2a, q, a);
			 p2a = q - a;
			 Cross(cp1, ba, p1a);
			 Cross(cp2, ba, p2a);

			 if (Dot(cp1, cp2) >= 0) return true;
			 else return false;
			}

			inline bool SameSide(Vector3f p1, Vector3f p2, Vector3f a, Vector3f b) {
			 Vector3f cp1, cp2;
			 Vector3f ba, p1a, p2a;
			 //Diff(ba, b, a);
			 ba = b - a;
			 //Diff(p1a, p, a);
			 p1a = p1 - a;
			 //Diff(p2a, q, a);
			 p2a = p2 - a;
			 Cross(cp1, ba, p1a);
			 Cross(cp2, ba, p2a);

			 if (Dot(cp1, cp2) >= 0) return true;
			 else return false;
			}

			inline bool PointInTriangle(Vector3f p, Vector3f a, Vector3f b, Vector3f c) {
			 if (SameSide(p, a, b, c) && SameSide(p, b, a, c) && SameSide(p,c, a,b)) return true;
			 else return false;
			}
	} gmath;
}

#endif /* HEADERS_CORE_GMATH_H_ */
