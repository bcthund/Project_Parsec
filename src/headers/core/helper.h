/*
 * Helper.h
 *
 *  Created on: Dec 19, 2018
 *      Author: bcthund
 *
 *  Description: Provides special features such as drawing object center positions
 *  			 and rotations. This class simply contains the definitions on
 *  			 how to draw the XYZ coordinate or rotation gimbal.
 */

#ifndef HEADERS_CORE_HELPER_H_
#define HEADERS_CORE_HELPER_H_

//#include "../gl4/glcorearb.h"
#include "core_functions.h"
#include "matrix.h"
#include "shader.h"
#include "vao.h"
//#include "joint.h"

namespace Core {
	class _Helper {
		private:
			void SetLine(Vector2f a, Vector2f b, float fScale, Color vColorA=Color(1.0f), Color vColorB=Color(1.0f));
			void SetLine(Vector2i a, Vector2i b, float fScale, Color vColorA=Color(1.0f), Color vColorB=Color(1.0f));
			void SetLine(Vector3f a, Vector3f b, float fScale, Color vColorA=Color(1.0f), Color vColorB=Color(1.0f));
			/*Matrix_System *matrix;
			Shader_System *shader;*/

		public:	// TODO: make private
			VAO vaoPosition;		// Position Gimbbal, XYZ axes as simple lines
			VAO vaoRotation;		// Rotation Gimbal, Circles on the XYZ axes representing a point that rotations are performed about
			VAO vaoLine;			// Draws a simple line
			VAO vaoPoint;			// Draws a single point
			VAO vaoBox;
			VAO	vaoSphere;
			VAO vaoCylinder;

		public:
			_Helper(/*Matrix_System &m, Shader_System &s*/);
			virtual ~_Helper();
			void init();

			enum _PointStyle {	GLPOINT_SQUARE_ALPHA,
								GLPOINT_SQUARE,
								GLPOINT_CIRCLE,
								GLPOINT_ELLIPSE,
								GLPOINT_ROSE,
								GLPOINT_ROSE_OUTLINE,
								GLPOINT_RING,
								GLPOINT_SPIRAL_CLIPPED,
								GLPOINT_SPIRAL,
								GLPOINT_STAR,
								GLPOINT_LAST
			};

			void drawPoint(float fSize=2.0f, float fRotation=0.0, Color vColor=Color(1.0f), _PointStyle eStyle=GLPOINT_SQUARE_ALPHA, int iSpikes=5, float fThickness=0.25);
			void drawPointSprite(float fSize=2.0f, float fRotation=0.0, Color vColor=Color(1.0f), _PointStyle eStyle=GLPOINT_SQUARE_ALPHA, int iSpikes=5, float fThickness=0.25);
			//void drawLine();
			void drawPosition(float fWidth, float fScale);
			void drawPosition(float fWidth, float fScale, Vector3f pos, Vector3f rot);

			void drawRotation();
			//void drawRotation(Vector3f position, Vector3f rotation, float fScale, float fWidth);

			void drawPoint(Vector3f position, float fWidth);
			//void drawLine(_Joint &joint, Matrix_System &matrix, Shader_System &shader);
			void drawLine(Vector2f a, Vector2f b, float fWidth=1.0f, float fScale=1.0f, Color vColorA=Color(1.0f, 0.0f, 0.0f, 1.0f), Color vColorB=Color(0.0f, 0.0f, 1.0f, 1.0f));
			void drawLine(Vector2i a, Vector2i b, float fWidth=1.0f, float fScale=1.0f, Color vColorA=Color(1.0f, 0.0f, 0.0f, 1.0f), Color vColorB=Color(0.0f, 0.0f, 1.0f, 1.0f));
			void drawLine(Vector3f a, Vector3f b, float fWidth=1.0f, float fScale=1.0f, Color vColorA=Color(1.0f, 0.0f, 0.0f, 1.0f), Color vColorB=Color(0.0f, 0.0f, 1.0f, 1.0f));

			// Add overloads
			void drawBox();
			void drawSphere();
			void drawCylinder();

	};

} /* namespace Core */

#endif /* HEADERS_CORE_HELPER_H_ */

