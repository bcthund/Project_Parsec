/*
 * matrix.h
 *
 *  Created on: Jan 28, 2014
 *      Author: bcthund
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include "core_functions.h"
#include "gl4_5/glcorearb.h"
#include "gmath.h"

namespace Core {
	class Matrix_System {
		private:
		protected:
			int iStackDepth;
			Matrix44f	*	mvpStack;


			// TODO: All Matrix44f can be lumped into t_UMap and then chosen by name rather than enum
			Matrix44f		projMatrix;
			//Matrix44f		perspectiveMatrix;
			t_UMap<std::string, Matrix44f*> perspectiveMatrix;
			Matrix44f		orthographicMatrix;

			Matrix33f		mNormalMatrix;
			Matrix44f		mLookAt;
			Matrix44f		lightMatrix;
		public:
			enum MATRIX_MODES { MM_ORTHO,
								MM_LIGHT,
								MM_PERSPECTIVE // MUST BE LAST! Perspective matrix can by anything at this value or above, so we can use "MM_PERSPECTIVE + n"
							  };
			int				iCurrentStack;
			Matrix44f	*	mvStack;
			Matrix44f	*	mMatrix;		// Model Matrix
			Matrix44f	*	mtvStack;		// Translation matrix stack
			Matrix44f	*	mrvStack;		// Rotation matrix stack

			Matrix_System						();
			~Matrix_System						();
			void		LoadIdentity			(Matrix44f m);
			void		SetIdentity				();		//  Make the current stack an identity matrix
			//void		CopyMatrix				(Matrix44f &src, Matrix44f &dst);
			//void		SetTransform			();

			// Transformations
			void		Scale					(float 		f);
			void		Scale					(float 		x, 			float 			y,		float			z);
			void		Translate				(Vector3f	&v);
			void		Translate				(float 		x, 			float 			y,		float			z);
			void		Translate				(Matrix44f 	&m, 		float 			x,		float			y,	float	z);
			void		RotateAxis				(Vector3f vAxis, Radians theta);
			Matrix44f	GetRotateAxis			(Vector3f vAxis, Radians theta);
			void		Rotate					(Vector3f vRotation);
			void		Rotate					(Radians 	angle, 		float 			x,		float			y,	float	z);
			void		Rotate					(Matrix44f 	&out, 		Radians 		angle,	float			x,	float	y,	float	z);
			void		Skew					(Radians	angle, 		float 			x,		float			y,	float	z);
			//void		Multiply				(Matrix44f	&product, 	const Matrix44f a,		const Matrix44f b);
			//void		MultiplyVec				(Vector4f 	&product, 	const Matrix44f a,		Vector4f b);
			//void		Apply					(Matrix44f 	&mMatrix);

			// Set the matrix states
			void		addPerspective			(std::string name, Degrees degFov, float fAspect, float fNear, float fFar);
			void		SetOrtho				(float fHalfWidth, float fHalfHeight, float fNear, float fFar);
			void		SetLight				(float fHalfWidth, float fHalfHeight, float fNear, float fFar);
			void		setProjection			(GLenum eProj, std::string name);
			void		LookAt					(Vector3f vEye, Vector3f vCenter, Vector3f vUp);
			const		Matrix44f& GetLookAt	(Vector3f vEye, Vector3f vCenter, Vector3f vUp);		//Return a "Look At" matrix (i.e. view matrix)

			// Get matrix states
			void		SetModelView			(Matrix44f &mMatrix)	{ mvStack[iCurrentStack] = mMatrix; SetTransform();	}
			Matrix44f&	GetTransView			(void)					{ return mtvStack[iCurrentStack]; }		// Return translation matrix only
			Matrix44f&	GetRotView				(void)					{ return mrvStack[iCurrentStack]; }		// Return rotation matrix only
			Matrix44f&	GetModelView			(void)					{ return mvStack[iCurrentStack]; }
			Matrix44f&	GetModelViewProjection	(void)					{ return mvpStack[iCurrentStack]; }
			Matrix44f&	GetProjectionMatrix		(void)					{ return projMatrix; }

			inline void Apply(Matrix44f &mMatrix ) {
				Matrix44f mTemp;
				for(int i=0;i<16;i++) {
					mTemp[i] = mvStack[iCurrentStack][i];
				}
				mvStack[iCurrentStack] = mTemp * mMatrix;
			}

			inline void CopyMatrix(Matrix44f &dst, Matrix44f &src) {
				for(int i=0;i<16;i++) {
					dst[i] = src[i];
				}
			}

			inline void SetTransform() {
				mvpStack[iCurrentStack] = projMatrix * mvStack[iCurrentStack];
			}
//			const Matrix33f& GetNormalMatrix33(bool bNormalize = false)
//			{
//				mNormalMatrix[0] = mvStack[iCurrentStack][0];
//				mNormalMatrix[1] = mvStack[iCurrentStack][1];
//				mNormalMatrix[2] = mvStack[iCurrentStack][2];
//				mNormalMatrix[3] = mvStack[iCurrentStack][4];
//				mNormalMatrix[4] = mvStack[iCurrentStack][5];
//				mNormalMatrix[5] = mvStack[iCurrentStack][6];
//				mNormalMatrix[6] = mvStack[iCurrentStack][8];
//				mNormalMatrix[7] = mvStack[iCurrentStack][9];
//				mNormalMatrix[8] = mvStack[iCurrentStack][10];
//
//				if(bNormalize) {
//					NormalizeMatrix3(&mNormalMatrix[0]);
//					NormalizeMatrix3(&mNormalMatrix[3]);
//					NormalizeMatrix3(&mNormalMatrix[6]);
//				}
//
//				Transpose(mNormalMatrix);
//				Inverse(mNormalMatrix);
//
//				return mNormalMatrix;
//			}

			void Push();
			void Pop();
	};

//	Matrix_System::Matrix_System() {
//		//            .................................................................Done
//		std::cout << "Construct Matrix System..........................................";
//		//Setup the Push/Pop matrix stack
//		iStackDepth=32;
//		mvStack = new Matrix44f[iStackDepth];
//		mtvStack = new Matrix44f[iStackDepth];
//		mrvStack = new Matrix44f[iStackDepth];
//		mvpStack = new Matrix44f[iStackDepth];
//		iCurrentStack = 0;
//
//		LoadIdentity(mvStack[iCurrentStack]);
//		LoadIdentity(mtvStack[iCurrentStack]);
//		LoadIdentity(mrvStack[iCurrentStack]);
//		LoadIdentity(mvpStack[iCurrentStack]);
//		std::cout << "Done" << std::endl;
//	}
//
//	Matrix_System::~Matrix_System() {
//		//            .................................................................Done
//		std::cout << "Destroy Matrix System............................................";
//		delete [] mvStack;
//		delete [] mtvStack;
//		delete [] mrvStack;
//		delete [] mvpStack;
//		std::cout << "Done" << std::endl;
//	}
//
//	void Matrix_System::LoadIdentity(Matrix44f m)
//	{
//		static Matrix44f	i = { 1.0f, 0.0f, 0.0f, 0.0f,
//								  0.0f, 1.0f, 0.0f, 0.0f,
//								  0.0f, 0.0f, 1.0f, 0.0f,
//								  0.0f, 0.0f, 0.0f, 1.0f };
//
//		//std::copy(identity, sizeof(identity), m);
//		//memcpy(m, identity, sizeof(Matrix44f));
////		m[0] = i[0];
////		m[1] = i[1];
////		m[2] = i[2];
////		m[3] = i[3];
////		m[4] = i[4];
////		m[5] = i[5];
////		m[6] = i[6];
////		m[7] = i[7];
////		m[8] = i[8];
////		m[9] = i[9];
////		m[10] = i[10];
////		m[11] = i[11];
////		m[12] = i[12];
////		m[13] = i[13];
////		m[14] = i[14];
////		m[15] = i[15];
//		m = i;
//	}
//
//	void Matrix_System::SetIdentity() {
//		LoadIdentity(mvStack[iCurrentStack]);
//	}
//
//	inline void Matrix_System::Apply(Matrix44f &mMatrix ) {
//		Matrix44f mTemp;
//		for(int i=0;i<16;i++) {
//			mTemp[i] = mvStack[iCurrentStack][i];
//		}
//		mvStack[iCurrentStack] = mTemp * mMatrix;
//	}
//
//	inline void Matrix_System::CopyMatrix(Matrix44f &dst, Matrix44f &src) {
//		for(int i=0;i<16;i++) {
//			dst[i] = src[i];
//		}
//	}
//
//	inline void Matrix_System::SetTransform() {
//		mvpStack[iCurrentStack] = projMatrix * mvStack[iCurrentStack];
//	}
//
//	void Matrix_System::Scale(float f) {
//		Matrix44f mTemp, mScale;
//		LoadIdentity(mScale);
//
//		mScale[0] = f;
//		mScale[5] = f;
//		mScale[10] = f;
//
//		for(int i=0;i<16;i++) {
//			mTemp[i] = mvStack[iCurrentStack][i];
//		}
//		mvStack[iCurrentStack] = mTemp * mScale;
//	}
//
//	void Matrix_System::Scale(float x, float y, float z) {
//		Matrix44f mTemp, mScale;
//		LoadIdentity(mScale);
//
//		mScale[0] *= x;
//		mScale[5] *= y;
//		mScale[10] *= z;
//
//		for(int i=0;i<16;i++) {
//			mTemp[i] = mvStack[iCurrentStack][i];
//		}
//		mvStack[iCurrentStack] = mTemp * mScale;
//	}
//
//	void Matrix_System::Translate(Vector3f &v) {
//		Translate(v.x, v.y, v.z);
//	}
//
//	void Matrix_System::Translate(float x, float y, float z) {
//		Matrix44f mTemp, mTranslate;
//		LoadIdentity(mTranslate);
//
//		mTranslate[12] = x;
//		mTranslate[13] = y;
//		mTranslate[14] = z;
//
//		for(int i=0;i<16;i++) {
//			mTemp[i] = mvStack[iCurrentStack][i];
//		}
//		mvStack[iCurrentStack] = mTemp * mTranslate;
//		mtvStack[iCurrentStack] = mTemp * mTranslate;
//	}
//
//void Matrix_System::Translate(Matrix44f &m, float x, float y, float z) {
//		Matrix44f mTemp, mTranslate;
//		LoadIdentity(mTranslate);
//
//		mTranslate[12] = x;
//		mTranslate[13] = y;
//		mTranslate[14] = z;
//
//		for(int i=0;i<16;i++) {
//			mTemp[i] = mvStack[iCurrentStack][i];
//		}
//
//		m = mTemp * mTranslate;
//	}
//
//	void Matrix_System::Rotate(float angle, float x, float y, float z)
//	{
//		Matrix44f mTemp, mRotate;
//		LoadIdentity(mRotate);
//		//angle = M_DegToRad(angle);
//		float mag, s, c;
//		float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;
//
//		s = float(sin(angle));
//		c = float(cos(angle));
//
//		mag = float(sqrt( x*x + y*y + z*z ));
//
//		// Identity matrix
//		if (mag == 0.0f) {
//			LoadIdentity(mRotate);
//			return;
//		}
//
//		// Rotation matrix is normalized
//		x /= mag;
//		y /= mag;
//		z /= mag;
//
//		#define M(row,col)  mRotate[col*4+row]
//			xx = x * x;
//			yy = y * y;
//			zz = z * z;
//			xy = x * y;
//			yz = y * z;
//			zx = z * x;
//			xs = x * s;
//			ys = y * s;
//			zs = z * s;
//			one_c = 1.0f - c;
//
//			M(0,0) = (one_c * xx) + c;
//			M(0,1) = (one_c * xy) - zs;
//			M(0,2) = (one_c * zx) + ys;
//			M(0,3) = 0.0f;
//
//			M(1,0) = (one_c * xy) + zs;
//			M(1,1) = (one_c * yy) + c;
//			M(1,2) = (one_c * yz) - xs;
//			M(1,3) = 0.0f;
//
//			M(2,0) = (one_c * zx) - ys;
//			M(2,1) = (one_c * yz) + xs;
//			M(2,2) = (one_c * zz) + c;
//			M(2,3) = 0.0f;
//
//			M(3,0) = 0.0f;
//			M(3,1) = 0.0f;
//			M(3,2) = 0.0f;
//			M(3,3) = 1.0f;
//		#undef M
//
//		for(int i=0;i<16;i++) {
//			mTemp[i] = mvStack[iCurrentStack][i];
//		}
//		mvStack[iCurrentStack] = mTemp * mRotate;
//		mrvStack[iCurrentStack] = mTemp * mRotate;
//	}
//
//	void Matrix_System::Rotate(Matrix44f &out, float angle, float x, float y, float z)
//	{
//		Matrix44f mTemp, mRotate;
//		LoadIdentity(mRotate);
//		//angle = M_DegToRad(angle);
//		float mag, s, c;
//		float xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;
//
//		s = float(sin(angle));
//		c = float(cos(angle));
//
//		mag = float(sqrt( x*x + y*y + z*z ));
//
//		// Identity matrix
//		if (mag == 0.0f) {
//			LoadIdentity(mRotate);
//			return;
//		}
//
//		// Rotation matrix is normalized
//		x /= mag;
//		y /= mag;
//		z /= mag;
//
//		#define M(row,col)  mRotate[col*4+row]
//			xx = x * x;
//			yy = y * y;
//			zz = z * z;
//			xy = x * y;
//			yz = y * z;
//			zx = z * x;
//			xs = x * s;
//			ys = y * s;
//			zs = z * s;
//			one_c = 1.0f - c;
//
//			M(0,0) = (one_c * xx) + c;
//			M(0,1) = (one_c * xy) - zs;
//			M(0,2) = (one_c * zx) + ys;
//			M(0,3) = 0.0f;
//
//			M(1,0) = (one_c * xy) + zs;
//			M(1,1) = (one_c * yy) + c;
//			M(1,2) = (one_c * yz) - xs;
//			M(1,3) = 0.0f;
//
//			M(2,0) = (one_c * zx) - ys;
//			M(2,1) = (one_c * yz) + xs;
//			M(2,2) = (one_c * zz) + c;
//			M(2,3) = 0.0f;
//
//			M(3,0) = 0.0f;
//			M(3,1) = 0.0f;
//			M(3,2) = 0.0f;
//			M(3,3) = 1.0f;
//		#undef M
//
//		for(int i=0;i<16;i++) {
//			mTemp[i] = out[i];
//		}
//		out = mTemp * mRotate;
//	}
//
//	void Matrix_System::Skew(float angle, float x=0, float y=0, float z=0) {
//		Core::gmath.Max(x, 1);
//		Core::gmath.Max(y, 1);
//		Core::gmath.Max(z, 1);
//
//		Matrix44f mTemp, mSkew;
//		LoadIdentity(mSkew);
//		angle = M_DegToRad(angle);
//
//		float fTan = tan(angle);
//
//		#define M(row,col)  mSkew[col*4+row]
//		M(0,0) = 1.0f;
//		M(0,1) = x*fTan;
//		M(0,2) = 0.0f;
//		M(0,3) = 0.0f;
//
//		M(1,0) = y*fTan;
//		M(1,1) = 1.0f;
//		M(1,2) = 0.0f;
//		M(1,3) = 0.0f;
//
//		M(2,0) = 0.0f;
//		M(2,1) = z*fTan;
//		M(2,2) = 1.0f;
//		M(2,3) = 0.0f;
//
//		M(3,0) = 0.0f;
//		M(3,1) = 0.0f;
//		M(3,2) = 0.0f;
//		M(3,3) = 1.0f;
//
//		for(int i=0;i<16;i++) {
//			mTemp[i] = mvStack[iCurrentStack][i];
//		}
//		mvStack[iCurrentStack] = mTemp * mSkew;
//	}
//
////	void Matrix_System::Multiply(Matrix44f &product, Matrix44f a, Matrix44f b )
////	{
////		#define A(row,col)  a[(col<<2)+row]
////		#define B(row,col)  b[(col<<2)+row]
////		#define P(row,col)  product[(col<<2)+row]
////
////		for (int i = 0; i < 4; i++) {
////			float ai0=A(i,0),  ai1=A(i,1),  ai2=A(i,2),  ai3=A(i,3);
////			P(i,0) = ai0 * B(0,0) + ai1 * B(1,0) + ai2 * B(2,0) + ai3 * B(3,0);
////			P(i,1) = ai0 * B(0,1) + ai1 * B(1,1) + ai2 * B(2,1) + ai3 * B(3,1);
////			P(i,2) = ai0 * B(0,2) + ai1 * B(1,2) + ai2 * B(2,2) + ai3 * B(3,2);
////			P(i,3) = ai0 * B(0,3) + ai1 * B(1,3) + ai2 * B(2,3) + ai3 * B(3,3);
////		}
////
////		#undef A
////		#undef B
////		#undef P
////	}
//
////	void Matrix_System::MultiplyVec(Vector4f &product, const Matrix44f a, Vector4f b) {
//////		product[0] = a[0]*b[0]  + a[1]*b[1]  + a[2]*b[2]  + a[3]*b[3];
//////		product[1] = a[4]*b[0]  + a[5]*b[1]  + a[6]*b[2]  + a[7]*b[3];
//////		product[2] = a[8]*b[0]  + a[9]*b[1]  + a[10]*b[2] + a[11]*b[3];
//////		product[3] = a[12]*b[0] + a[13]*b[1] + a[14]*b[2] + a[15]*b[3];
////
//////		product[0] = a[0]*b[0]  + a[4]*b[1]  + a[8]*b[2]  + a[12]*b[3];
//////		product[1] = a[1]*b[0]  + a[5]*b[1]  + a[9]*b[2]  + a[13]*b[3];
//////		product[2] = a[2]*b[0]  + a[6]*b[1]  + a[10]*b[2] + a[14]*b[3];
//////		product[3] = a[3]*b[0]  + a[7]*b[1]  + a[11]*b[2] + a[15]*b[3];
////
////		product = a * b;
////	}
//
////	Matrix44f Matrix_System::Multiply(const Matrix44f a, const Vector4f b) {
////		Matrix44f result;
////		result[0] = a[0]*b[0]  + a[1]*b[1]  + a[2]*b[2]  + a[3]*b[3];
////		result[1] = a[4]*b[0]  + a[5]*b[1]  + a[6]*b[2]  + a[7]*b[3];
////		result[2] = a[8]*b[0]  + a[9]*b[1]  + a[10]*b[2] + a[11]*b[3];
////		result[3] = a[12]*b[0] + a[13]*b[1] + a[14]*b[2] + a[15]*b[3];
////		return result;
////	}
//
//	void Matrix_System::SetPerspective(float fFov, float fAspect, float fNear, float fFar)
//	{
//		float xmin, xmax, ymin, ymax;       // Dimensions of near clipping plane
//
//		// Do the Math for the near clipping plane
//		ymax = fNear * float(tan( (fFov) * M_PI / 360.0 ));
//		ymin = -ymax;
//		xmax = ymax * fAspect;
//		xmin = -xmax;
//
//		// Construct the projection matrix
//		LoadIdentity(perspectiveMatrix);
////		#define p perspectiveMatrix
////		Matrix44f * p = perspectiveMatrix;
//
////		float l,
////			  r,
////			  t,
////			  b,
////			  n = fNear,
////			  f = fFar,
////			  S,
////			  fov = M_DegToRad(80),
////			  a = fAspect,
////			  zp = fFar + fNear,
////			  zm = fFar - fNear;
//
////		p[0]  = 2/(r-l);		p[1]  = 0;				p[2]  = 0;				p[3]  = 0;
////		p[4]  = 0;				p[5]  = 2/(t-b);		p[6]  = 0;				p[7]  = 0;
////		p[8]  = 0;				p[9]  = 0;				p[10] = -2/(f-n);		p[11] = 0;
////		p[12] = -(r+l)/(r-l);	p[13] = -(t+b)/(t-b);	p[14] = -(f+n)/(f-n);	p[15] = 1;
//
////		S = 1.0f/tan(fov/2.0f);
////
////		p[0]  =  S/a;	p[1]  =  0;		p[2]  =  0;						p[3]  =  0;
////		p[4]  =  0;		p[5]  =  S;		p[6]  =  0;						p[7]  =  0;
////		p[8]  =  0;		p[9]  =  0;		p[10] = -zp/zm;					p[11] = -1;
////		p[12] =  0;		p[13] =  0;		p[14] = -(2*fFar*fNear)/zm;		p[15] =  0;
//
////		p[0]  =  S;		p[1]  =  0;		p[2]  =  0;				p[3]  =  0;
////		p[4]  =  0;		p[5]  =  S;		p[6]  =  0;				p[7]  =  0;
////		p[8]  =  0;		p[9]  =  0;		p[10] = -f/(f-n);		p[11] = -1;
////		p[12] =  0;		p[13] =  0;		p[14] = -(f*n)/(f-n);	p[15] =  0;
//
//		#undef p
//
//		perspectiveMatrix[0]  = (2.0f * fNear)	/ (xmax - xmin);
//		perspectiveMatrix[5]  = (2.0f * fNear) / (ymax - ymin);
//		perspectiveMatrix[8]  = (xmax + xmin) / (xmax - xmin);
//		perspectiveMatrix[9]  = (ymax + ymin) / (ymax - ymin);
//		perspectiveMatrix[10] = -((fFar + fNear) / (fFar - fNear));
//		perspectiveMatrix[11] = -1.0f;
//		perspectiveMatrix[14] = -((2.0f * fFar * fNear)/(fFar - fNear));
//		perspectiveMatrix[15] = 0.0f;
//
////		perspectiveMatrix[0]  = (2.0f * fNear)	/ (xmin - xmax);
////		perspectiveMatrix[5]  = (2.0f * fNear) / (ymin - ymax);
////		perspectiveMatrix[8]  = (xmin + xmax) / (xmin - xmax);
////		perspectiveMatrix[9]  = (ymin + ymax) / (ymin - ymax);
////		perspectiveMatrix[10] = -((fFar + fNear) / (fFar - fNear));
////		perspectiveMatrix[11] = -1.0f;
////		perspectiveMatrix[14] = -((2.0f * fFar * fNear)/(fFar - fNear));
////		perspectiveMatrix[15] = 0.0f;
//	}
//
//	void Matrix_System::SetOrtho(float fHalfWidth, float fHalfHeight, float fNear, float fFar) {
//		LoadIdentity(orthographicMatrix);
//		float	fR =  fHalfWidth,
//				fL = -fHalfWidth,
//				fT =  fHalfHeight,
//				fB = -fHalfHeight,
//				fF =  fFar,
//				fN = -fNear;
//
//		orthographicMatrix[0]  =  2/(fR-fL);
//		orthographicMatrix[5]  =  2/(fT-fB);
//		orthographicMatrix[10] = -2/(fF-fN);
//		orthographicMatrix[12] = -((fR+fL)/(fR-fL));
//		orthographicMatrix[13] = -((fT+fB)/(fT-fB));
//		orthographicMatrix[14] = -((fF+fN)/(fF-fN));
//		orthographicMatrix[15] =  1.0f;
//	}
//
//	void Matrix_System::SetLight(float fHalfWidth, float fHalfHeight, float fNear, float fFar) {
//		LoadIdentity(lightMatrix);
//		float	fR =  fHalfWidth,
//				fL = -fHalfWidth,
//				fT =  fHalfHeight,
//				fB = -fHalfHeight,
//				fF =  fFar,
//				fN = -fNear;
//
//		lightMatrix[0]  =  2/(fR-fL);
//		lightMatrix[5]  =  2/(fT-fB);
//		lightMatrix[10] = -2/(fF-fN);
//		lightMatrix[12] = -((fR+fL)/(fR-fL));
//		lightMatrix[13] = -((fT+fB)/(fT-fB));
//		lightMatrix[14] = -((fF+fN)/(fF-fN));
//		lightMatrix[15] =  1.0f;
//	}
//
//	void Matrix_System::SetProjection(GLenum eProj) {
//		if (eProj == MM_PERSPECTIVE) {
//			//memcpy(projMatrix, perspectiveMatrix, sizeof(Matrix44f));
//			projMatrix = perspectiveMatrix;
////			#define defM projMatrix
////			cout << defM[0]  << "\t" << defM[1]  << "\t" << defM[2]  << "\t" << defM[3]  << endl
////				 << defM[4]  << "\t" << defM[5]  << "\t" << defM[6]  << "\t" << defM[7]  << endl
////				 << defM[8]  << "\t" << defM[9]  << "\t" << defM[10] << "\t" << defM[11] << endl
////				 << defM[12] << "\t" << defM[13] << "\t" << defM[14] << "\t" << defM[15] << endl << endl;
////			#undef defM
//		}
//		if (eProj == MM_ORTHO) {
//			//memcpy(projMatrix, orthographicMatrix, sizeof(Matrix44f));
//			projMatrix = orthographicMatrix;
//		}
//		//if (eProj == MM_LIGHT) memcpy(projMatrix, lightMatrix, sizeof(Matrix44f));
//	}
//
//	void Matrix_System::LookAt(Vector3f vEye, Vector3f vCenter, Vector3f vUp)
//	{
//		Vector3f F;
//		//Diff(F, vCenter, vEye);
//		F = vCenter - vEye;
//		Core::gmath.Normalize(F);
//
//		Vector3f UP = {vUp[0], vUp[1], vUp[2]};
//		Core::gmath.Normalize(UP);
//
//		Vector3f s;
//		Core::gmath.Cross(s, F, UP);
//
//		Vector3f u;
//		Core::gmath.Cross(u, s, F);
//
//		Matrix44f	M =	{	 s[0],	 u[0],  -F[0],	0,
//							 s[1],	 u[1],  -F[1],	0,
//							 s[2],	 u[2],	-F[2],	0,
//								0,		0,		0,	1 };
//
//		Matrix44f mTemp;
//		LoadIdentity(mvStack[iCurrentStack]);
//		//CopyMatrix(mTemp, mvStack[iCurrentStack]);
//		//CopyMatrix44f(mvStack[iCurrentStack], mTemp);
//		for(int i=0;i<16;i++) {
//			mTemp[i] = mvStack[iCurrentStack][i];
//		}
//		//Multiply(mvStack[iCurrentStack], mTemp, M);
//		mvStack[iCurrentStack] = mTemp * M;
//		Translate(-vEye[0], -vEye[1], -vEye[2]);
//		SetTransform();
//	}
//
//	const Matrix44f& Matrix_System::GetLookAt(Vector3f vEye, Vector3f vCenter, Vector3f vUp) {
//		Vector3f F;
//		//Diff(F, vCenter, vEye);
//		F = vCenter - vEye;
//		Core::gmath.Normalize(F);
//
//		Vector3f UP = {vUp[0], vUp[1], vUp[2]};
//		Core::gmath.Normalize(UP);
//
//		Vector3f s;
//		Core::gmath.Cross(s, F, UP);
//
//		Vector3f u;
//		Core::gmath.Cross(u, s, F);
//
//		Matrix44f	M =	{	 s[0],	 u[0],  -F[0],	0,
//							 s[1],	 u[1],  -F[1],	0,
//							 s[2],	 u[2],	-F[2],	0,
//								0,		0,		0,	1 };
//
//		Matrix44f mTemp;
//		LoadIdentity(mLookAt);
//		//CopyMatrix(mTemp, mvStack[iCurrentStack]);
//		//CopyMatrix44f(mvStack[iCurrentStack], mTemp);
//		for(int i=0;i<16;i++) {
//			mTemp[i] = mLookAt[i];
//		}
//		//Multiply(mLookAt, mTemp, M);
//		mLookAt = mTemp * M;
//		Translate(mLookAt, -vEye[0], -vEye[1], -vEye[2]);
//		return mLookAt;
//	}
//
//	void Matrix_System::Push() {
//		if (iCurrentStack < iStackDepth) {
//			iCurrentStack++;
//
//			//memcpy(mvStack[iCurrentStack], mvStack[iCurrentStack-1], sizeof(Matrix44f));
//			//memcpy(mvpStack[iCurrentStack], mvpStack[iCurrentStack-1], sizeof(Matrix44f));
//			//std::copy(mvStack[iCurrentStack-1], mvStack[iCurrentStack-1]+(16*sizeof(float)), mvStack[iCurrentStack]);
//			//std::copy(mvpStack[iCurrentStack-1], mvpStack[iCurrentStack-1]+(16*sizeof(float)), mvpStack[iCurrentStack]);
//
//			for(int i=0;i<16;i++) {
//				mvStack[iCurrentStack][i] = mvStack[iCurrentStack-1][i];
//				mtvStack[iCurrentStack][i] = mtvStack[iCurrentStack-1][i];
//				mrvStack[iCurrentStack][i] = mrvStack[iCurrentStack-1][i];
//			}
//
//			for(int i=0;i<16;i++) {
//				mvpStack[iCurrentStack][i] = mvpStack[iCurrentStack-1][i];
//			}
//			//CopyMatrix44f(mvStack[iCurrentStack-1], mvStack[iCurrentStack]);
//			//CopyMatrix44f(mvpStack[iCurrentStack-1], mvpStack[iCurrentStack]);
//		}
//		else printf("Error: Matrix Stack Overflow.\n");
//	}
//
//	void Matrix_System::Pop() {
//		if (iCurrentStack > 0) iCurrentStack--;
//		else printf("Error: Matrix Stack Underflow.\n");
//	}
}

#endif /* MATRIX_H_ */
