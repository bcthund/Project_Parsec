/*
 * Helper.cpp
 *
 *  Created on: Dec 19, 2018
 *      Author: bcthund
 */

//#include "../gl4/glcorearb.h"

#include "core_functions.h"
#include "matrix.h"
#include "shader.h"
#include "helper.h"

namespace Core {

	_Helper::_Helper(/*Matrix_System &m, Shader_System &s*/) {
//		matrix = &m;
//		shader = &s;
	}

	_Helper::~_Helper() {
		// TODO Auto-generated destructor stub
	}

	void _Helper::init() {
		Core::debug.log("Init Helpers {\n");
		Core::debug.logIncreaseIndent();
		Core::debug.log("Box\n", Core::debug().YELLOW);
		{
			Data3f vVerts[]		= { {  0.5,  0.5,  0.5 },
									{  0.5, -0.5,  0.5 },
									{ -0.5,  0.5,  0.5 },
									{ -0.5, -0.5,  0.5 },
									{ -0.5,  0.5, -0.5 },
									{ -0.5, -0.5, -0.5 },
									{  0.5,  0.5, -0.5 },
									{  0.5, -0.5, -0.5 } };

			GLuint uiIndex[]	=   { 0, 1, 2,
									  2, 1, 3,
									  2, 3, 4,
									  4, 3, 5,
									  4, 5, 6,
									  6, 5, 7,
									  6, 7, 0,
									  0, 7, 1,
									  2, 4, 0,
									  0, 4, 6,
									  5, 3, 7,
									  7, 3, 1 };

			vaoBox.Begin(GL_TRIANGLES, 8, 36, 0);
			vaoBox.CopyData(GLA_VERTEX, vVerts);
			vaoBox.CopyData(GLA_INDEX, uiIndex, 36);	// 36
			vaoBox.End();
		}

		Core::debug.log("Sphere\n", Core::debug().YELLOW);
		{
			Data3f vVerts[] = {
									{	 0.000000,	 0.000000,	-1.000000	},
									{	 0.425323,	-0.309011,	-0.850654	},
									{	-0.162456,	-0.499995,	-0.850654	},
									{	 0.723607,	-0.525725,	-0.447220	},
									{	 0.850648,	 0.000000,	-0.525736	},
									{	-0.525730,	 0.000000,	-0.850652	},
									{	-0.162456,	 0.499995,	-0.850654	},
									{	 0.425323,	 0.309011,	-0.850654	},
									{	 0.951058,	-0.309013,	 0.000000	},
									{	-0.276388,	-0.850649,	-0.447220	},
									{	 0.262869,	-0.809012,	-0.525738	},
									{	 0.000000,	-1.000000,	 0.000000	},
									{	-0.894426,	 0.000000,	-0.447216	},
									{	-0.688189,	-0.499997,	-0.525736	},
									{	-0.951058,	-0.309013,	 0.000000	},
									{	-0.276388,	 0.850649,	-0.447220	},
									{	-0.688189,	 0.499997,	-0.525736	},
									{	-0.587786,	 0.809017,	 0.000000	},
									{	 0.723607,	 0.525725,	-0.447220	},
									{	 0.262869,	 0.809012,	-0.525738	},
									{	 0.587786,	 0.809017,	 0.000000	},
									{	 0.587786,	-0.809017,	 0.000000	},
									{	-0.587786,	-0.809017,	 0.000000	},
									{	-0.951058,	 0.309013,	 0.000000	},
									{	 0.000000,	 1.000000,	 0.000000	},
									{	 0.951058,	 0.309013,	 0.000000	},
									{	 0.276388,	-0.850649,	 0.447220	},
									{	 0.688189,	-0.499997,	 0.525736	},
									{	 0.162456,	-0.499995,	 0.850654	},
									{	-0.723607,	-0.525725,	 0.447220	},
									{	-0.262869,	-0.809012,	 0.525738	},
									{	-0.425323,	-0.309011,	 0.850654	},
									{	-0.723607,	 0.525725,	 0.447220	},
									{	-0.850648,	 0.000000,	 0.525736	},
									{	-0.425323,	 0.309011,	 0.850654	},
									{	 0.276388,	 0.850649,	 0.447220	},
									{	-0.262869,	 0.809012,	 0.525738	},
									{	 0.162456,	 0.499995,	 0.850654	},
									{	 0.894426,	 0.000000,	 0.447216	},
									{	 0.688189,	 0.499997,	 0.525736	},
									{	 0.525730,	 0.000000,	 0.850652	},
									{	 0.000000,	 0.000000,	 1.000000	}
			};

			GLuint uiIndex[]	=   {
										0,	1,	2,
										3,	1,	4,
										0,	2,	5,
										0,	5,	6,
										0,	6,	7,
										3,	4,	8,
										9,	10,	11,
										12,	13,	14,
										15,	16,	17,
										18,	19,	20,
										3,	8,	21,
										9,	11,	22,
										12,	14,	23,
										15,	17,	24,
										18,	20,	25,
										26,	27,	28,
										29,	30,	31,
										32,	33,	34,
										35,	36,	37,
										38,	39,	40,
										40,	37,	41,
										40,	39,	37,
										39,	35,	37,
										37,	34,	41,
										37,	36,	34,
										36,	32,	34,
										34,	31,	41,
										34,	33,	31,
										33,	29,	31,
										31,	28,	41,
										31,	30,	28,
										30,	26,	28,
										28,	40,	41,
										28,	27,	40,
										27,	38,	40,
										25,	39,	38,
										25,	20,	39,
										20,	35,	39,
										24,	36,	35,
										24,	17,	36,
										17,	32,	36,
										23,	33,	32,
										23,	14,	33,
										14,	29,	33,
										22,	30,	29,
										22,	11,	30,
										11,	26,	30,
										21,	27,	26,
										21,	8,	27,
										8,	38,	27,
										20,	24,	35,
										20,	19,	24,
										19,	15,	24,
										17,	23,	32,
										17,	16,	23,
										16,	12,	23,
										14,	22,	29,
										14,	13,	22,
										13,	9,	22,
										11,	21,	26,
										11,	10,	21,
										10,	3,	21,
										8,	25,	38,
										8,	4,	25,
										4,	18,	25,
										7,	19,	18,
										7,	6,	19,
										6,	15,	19,
										6,	16,	15,
										6,	5,	16,
										5,	12,	16,
										5,	13,	12,
										5,	2,	13,
										2,	9,	13,
										4,	7,	18,
										4,	1,	7,
										1,	0,	7,
										2,	10,	9,
										2,	1,	10,
										1,	3,	10
			};

			vaoSphere.Begin(GL_TRIANGLES, 42, 240, 1);
			vaoSphere.CopyData(GLA_VERTEX, vVerts);
			vaoSphere.CopyData(GLA_INDEX, uiIndex, 240);
			vaoSphere.End();
		}

		Core::debug.log("Cylinder\n", Core::debug().YELLOW);
		{
			Data3f vVerts[] = {
								{	0.000000,	0.500000,	1.000000	},
								{	-0.382683,	-0.500000,	0.923880	},
								{	0.000000,	-0.500000,	1.000000	},
								{	-0.382683,	0.500000,	0.923880	},
								{	-0.707107,	-0.500000,	0.707107	},
								{	-0.707107,	0.500000,	0.707107	},
								{	-0.923880,	-0.500000,	0.382683	},
								{	-0.923880,	0.500000,	0.382683	},
								{	-1.000000,	-0.500000,	-0.000000	},
								{	-1.000000,	0.500000,	-0.000000	},
								{	-0.923880,	-0.500000,	-0.382684	},
								{	-0.923880,	0.500000,	-0.382684	},
								{	-0.707107,	-0.500000,	-0.707107	},
								{	-0.707107,	0.500000,	-0.707107	},
								{	-0.382683,	-0.500000,	-0.923880	},
								{	-0.382683,	0.500000,	-0.923880	},
								{	-0.000000,	-0.500000,	-1.000000	},
								{	-0.000000,	0.500000,	-1.000000	},
								{	0.382683,	-0.500000,	-0.923880	},
								{	0.382683,	0.500000,	-0.923880	},
								{	0.707107,	-0.500000,	-0.707107	},
								{	0.707107,	0.500000,	-0.707107	},
								{	0.923880,	-0.500000,	-0.382684	},
								{	0.923880,	0.500000,	-0.382684	},
								{	1.000000,	-0.500000,	0.000000	},
								{	1.000000,	0.500000,	0.000000	},
								{	0.923879,	-0.500000,	0.382684	},
								{	0.923879,	0.500000,	0.382684	},
								{	0.707107,	-0.500000,	0.707107	},
								{	0.707107,	0.500000,	0.707107	},
								{	0.382683,	-0.500000,	0.923880	},
								{	0.382683,	0.500000,	0.923880	}
		};

			GLuint uiIndex[] = {
									0,	1,	2,
									3,	4,	1,
									5,	6,	4,
									7,	8,	6,
									9,	10,	8,
									11,	12,	10,
									13,	14,	12,
									15,	16,	14,
									17,	18,	16,
									19,	20,	18,
									21,	22,	20,
									23,	24,	22,
									25,	26,	24,
									27,	28,	26,
									29,	30,	28,
									31,	2,	30,
									0,	3,	1,
									3,	5,	4,
									5,	7,	6,
									7,	9,	8,
									9,	11,	10,
									11,	13,	12,
									13,	15,	14,
									15,	17,	16,
									17,	19,	18,
									19,	21,	20,
									21,	23,	22,
									23,	25,	24,
									25,	27,	26,
									27,	29,	28,
									29,	31,	30,
									31,	0,	2
			};

			vaoCylinder.Begin(GL_TRIANGLES, 32, 96, 1);
			vaoCylinder.CopyData(GLA_VERTEX, vVerts);
			vaoCylinder.CopyData(GLA_INDEX, uiIndex, 0);
			vaoCylinder.End();

		}

		Core::debug.log("Point\n", Core::debug().YELLOW);
		{
			Data3f vVerts[]		= { {  0.0,  0.0,  0.0 },
									/*{  5.0,  0.0,  0.0 },
									{ -5.0,  0.0,  0.0 },
									{  0.0,  5.0,  0.0 },
									{  0.0, -5.0,  0.0 },
									{  0.0,  0.0,  5.0 },
									{  0.0,  0.0, -5.0 }*/ };

			//vaoPoint->Begin(GL_POINTS, 7, 7, 0);
			vaoPoint.Begin(GL_POINTS, 1, 1, 0);
			vaoPoint.CopyData(GLA_VERTEX, vVerts);
			vaoPoint.End();
		}

		Core::debug.log("Line\n", Core::debug().YELLOW);
		SetLine(Vector3f(0.0f), Vector3f(0.0f), 1.0f);

		Core::debug.log("Origin Coordinate\n", Core::debug().YELLOW);
		{
			Data4f vVerts[]		= {	{	0.0f,	0.0f,	0.0f,	1.0f	},
									{	1.0f,	0.0f,	0.0f,	1.0f	},
									{	0.0f,	0.0f,	0.0f,	1.0f	},
									{	0.0f,	1.0f,	0.0f,	1.0f	},
									{	0.0f,	0.0f,	0.0f,	1.0f	},
									{	0.0f,	0.0f,	1.0f,	1.0f	}	};

			Data4f vColor[]		= {	{	1.0f,	0.0f,	0.0f,	1.0f	},
									{	1.0f,	0.0f,	0.0f,	1.0f	},
									{	0.0f,	1.0f,	0.0f,	1.0f	},
									{	0.0f,	1.0f,	0.0f,	1.0f	},
									{	0.0f,	0.0f,	1.0f,	1.0f	},
									{	0.0f,	0.0f,	1.0f,	1.0f	}	};

			vaoPosition.Begin(GL_LINES, 6, 6, 0);
			vaoPosition.CopyData(GLA_VERTEX, vVerts);
			vaoPosition.CopyData(GLA_COLOR, vColor);
			vaoPosition.End();
		}

		Core::debug.logDecreaseIndent();
		Core::debug.log("}\n");
	}

	void _Helper::drawPoint(float fSize) {
		shader->getUniform(GLS_POINTS, uniforms.points);
		glPointSize(fSize);
		matrix->Push();
			matrix->SetTransform();
			shader->use(GLS_POINTS);
			shader->setUniform(GLS_POINTS, uniforms.points);
			vaoPoint.Draw();
		matrix->Pop();
	}

	/*
	 *	eShader options:
	 *		GLS_POINT_SPRITE (default) - Single textured camera facing quad
	 *		GLS_PARTICLE_SPRITE - Dual blended textured camera facing quad
	 */
	void _Helper::drawPointSprite(float fSize, float fRotation, Color vColor, _PointStyle eStyle, int iSpikes, float fThickness) {
//		if (eShader == GLS_POINT_SPRITE || eShader == GLS_PARTICLE_SPRITE) {
			glPointSize(fSize);
			matrix->Push();
				matrix->SetTransform();
				shader->use(GLS_POINT_SPRITE);
				shader->getUniform(GLS_POINT_SPRITE, eStyle, vColor, fRotation, iSpikes, fThickness);
				vaoPoint.Draw();
			matrix->Pop();
//		}
//		else std::cout << "Invalid shader [" << eShader << "] requested for point sprite, sprite not drawn." << std::endl;
	}

	void _Helper::SetLine(Vector2i a, Vector2i b, float fScale, Color vColorA, Color vColorB) {

		Data4f vVerts[]		= {	{	a.x*fScale,	a.y*fScale,	1.0f,	1.0f	},
								{	b.x*fScale,	b.y*fScale,	1.0f,	1.0f	}	};

		Data4f vColor[]		= {	{	vColorA.r,	vColorA.g,	vColorA.b,	vColorA.a	},
								{	vColorB.r,	vColorB.g,	vColorB.b,	vColorB.a	}	};

		vaoLine.Begin(GL_LINES, 2, 2, 0);
		vaoLine.CopyData(GLA_VERTEX, vVerts);
		vaoLine.CopyData(GLA_COLOR, vColor);
		vaoLine.End();
	}

	void _Helper::SetLine(Vector2f a, Vector2f b, float fScale, Color vColorA, Color vColorB) {

		Data4f vVerts[]		= {	{	a.x*fScale,	a.y*fScale,	1.0f,	1.0f	},
								{	b.x*fScale,	b.y*fScale,	1.0f,	1.0f	}	};

		Data4f vColor[]		= {	{	vColorA.r,	vColorA.g,	vColorA.b,	vColorA.a	},
								{	vColorB.r,	vColorB.g,	vColorB.b,	vColorB.a	}	};

		vaoLine.Begin(GL_LINES, 2, 2, 0);
		vaoLine.CopyData(GLA_VERTEX, vVerts);
		vaoLine.CopyData(GLA_COLOR, vColor);
		vaoLine.End();
	}

	void _Helper::SetLine(Vector3f a, Vector3f b, float fScale, Color vColorA, Color vColorB) {

		Data4f vVerts[]		= {	{	a.x*fScale,	a.y*fScale,	a.z*fScale,	1.0f	},
								{	b.x*fScale,	b.y*fScale,	b.z*fScale,	1.0f	}	};

		Data4f vColor[]		= {	{	vColorA.r,	vColorA.g,	vColorA.b,	vColorA.a	},
								{	vColorB.r,	vColorB.g,	vColorB.b,	vColorB.a	}	};

		vaoLine.Begin(GL_LINES, 2, 2, 0);
		vaoLine.CopyData(GLA_VERTEX, vVerts);
		vaoLine.CopyData(GLA_COLOR, vColor);
		vaoLine.End();
	}

//	void _Helper::drawLine(_Joint &joint, Matrix_System &matrix, Shader_System &shader) {
//		drawLine(joint.vOrigin, joint.vConnections[0], matrix, shader, 5.0f, 1.0f);
//	}

	void _Helper::drawLine(Vector2i a, Vector2i b, float fWidth, float fScale, Color vColorA, Color vColorB) {
		SetLine(a, b, fScale, vColorA, vColorB);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(fWidth);
		matrix->Push();
			matrix->SetTransform();
			shader->use(GLS_LINES);
			shader->getUniform(GLS_LINES);
			vaoLine.Draw();
		matrix->Pop();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void _Helper::drawLine(Vector2f a, Vector2f b, float fWidth, float fScale, Color vColorA, Color vColorB) {
		Core::debug.glErrorCheck("_Helper::drawLine", 407);
		SetLine(a, b, fScale, vColorA, vColorB);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		Core::debug.glErrorCheck("_Helper::drawLine", 410);
		glLineWidth(fWidth);
		Core::debug.glErrorCheck("_Helper::drawLine", 412);
		matrix->Push();
			matrix->SetTransform();
			shader->use(GLS_LINES);
			Core::debug.glErrorCheck("_Helper::drawLine", 416);
			shader->getUniform(GLS_LINES);
			Core::debug.glErrorCheck("_Helper::drawLine", 418);
			vaoLine.Draw();
			Core::debug.glErrorCheck("_Helper::drawLine", 420);
		matrix->Pop();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		Core::debug.glErrorCheck("_Helper::drawLine", 423);
	}

	void _Helper::drawLine(Vector3f a, Vector3f b, float fWidth, float fScale, Color vColorA, Color vColorB) {
		SetLine(a, b, fScale, vColorA, vColorB);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(fWidth);
		matrix->Push();
			matrix->SetTransform();
			shader->use(GLS_LINES);
			shader->getUniform(GLS_LINES);
			vaoLine.Draw();
		matrix->Pop();
//		glLineWidth(1.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void _Helper::drawPosition(float fWidth, float fScale) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(fWidth);
		Core::debug.glErrorCheck("helper", 443);
		matrix->Push();
		matrix->Scale(fScale);
		matrix->SetTransform();
		Core::debug.glErrorCheck("helper", 447);
		shader->use(Core::GLS_LINES);
		Core::debug.glErrorCheck("helper", 449);
		shader->getUniform(Core::GLS_LINES);
		Core::debug.glErrorCheck("helper", 451);
		vaoPosition.Draw();
		Core::debug.glErrorCheck("helper", 453);
		matrix->Pop();
//		glLineWidth(1.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		Core::debug.glErrorCheck("helper", 457);
	}

	void _Helper::drawPosition(float fWidth, float fScale, Vector3f pos, Vector3f rot) {
		matrix->Push();
		matrix->Rotate(rot[0], 1.0, 0.0, 0.0);
		matrix->Rotate(rot[1], 0.0, 1.0, 0.0);
		matrix->Translate(pos[0], pos[1], pos[2]);
		drawPosition(fWidth, fScale);
		matrix->Pop();
	}

//	void _Helper::drawRotation(Vector3f position, Vector3f rotation, float fScale, float sThickness) {
//	}

	void _Helper::drawBox() {
		vaoBox.Draw(GLM_DRAW_ELEMENTS);
	}

	void _Helper::drawSphere() {
		vaoSphere.Draw(GLM_DRAW_ELEMENTS);
	}

	void _Helper::drawCylinder() {
		vaoCylinder.Draw(GLM_DRAW_ELEMENTS);
	}

} /* namespace Core */
