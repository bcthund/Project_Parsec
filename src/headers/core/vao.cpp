#include <iostream>
#define GL_GLEXT_PROTOTYPES 1		// Enable core profile
//#define GL_POINT_SPRITE 0x8861		// Hack to enable Point Sprites thus enabling gl_PointCoord operation
#include "gl4_5/glcorearb.h"
//#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
//#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#include "types.h"
#include "vao.h"

namespace Core {
	VAO::VAO():	uiVertexSize(0),
				uiNormalSize(0),
				uiExtraSize(0),
				uiPositionSize(0),
				uiVertexOffset(0),
				uiNormalOffset(0),
				uiColorOffset(0),
				uiIndexOffset(0),
				uiTextureOffset(0),
				uiPositionOffset(0),
				uiExtraOffset(0),
				uiMaxInstances(0),
				uiVertexLength(0),
				uiNormalLength(0),
				uiColorLength(0),
				uiIndexLength(0),
				uiPositionLength(0),
				uiExtraLength(0),
				uiTextureLength(0),
				uiNumDrawVerts(0),
				uiNumVerts(0),
				uiTextureUnits(0),
				bPrime(false),
				bFinished(false),
				primitiveType(0),
				uiVertexArray(0),
				uiNormalArray(0),
				uiColorArray(0),
				uiIndexArray(0),
				uiTextureArray(nullptr),
				uiPositionArray(0),
				uiExtraArray(0),
				bStarted(false)
				 {
		vaoPrime[0] = 0;
		vaoPrime[1] = 0;
	}

	VAO::~VAO() {
		//.....................................................................
//		cout << "Destroy VAOs..................................................";
		if(uiVertexArray != 0)	{
			glDeleteBuffers(		1, &uiVertexArray);
			uiVertexArray = 0;
		}
		if(uiNormalArray != 0)	{
			glDeleteBuffers(		1, &uiNormalArray);
			uiNormalArray = 0;
		}
		if(uiColorArray != 0)	{
			glDeleteBuffers(		1, &uiColorArray);
			uiColorArray = 0;
		}
		if(uiIndexArray != 0)	{
			glDeleteBuffers(		1, &uiIndexArray);
			uiIndexArray = 0;
		}
		if(vaoPrime[0] != 0)	{
			glDeleteVertexArrays(	1, &vaoPrime[0]);
			vaoPrime[0] = 0;
		}
		if(vaoPrime[1] != 0)	{
			glDeleteVertexArrays(	1, &vaoPrime[1]);
			vaoPrime[1] = 0;
		}

		if (uiTextureUnits > 0) {
			for(unsigned int i = 0; i < uiTextureUnits; i++) {
				glDeleteBuffers(1, &uiTextureArray[i]);
				uiTextureArray[i] = 0;
			}
			delete [] uiTextureArray;
		}
//		cout << "Done" << endl;
	}

	void VAO::Begin(GLenum primitive, long uiNum, long uiDraw, GLuint uiSetTexUnits, GLuint uiInstances)
	{
		if (!bStarted) {
			bFinished = false;
			primitiveType = primitive;

			uiNumVerts = uiNum;
			uiNumDrawVerts = uiDraw;
			uiMaxInstances = uiInstances;

			//if(vaoPrime[0] != 0) glGenVertexArrays(1, &vaoPrime[0]);
			glGenVertexArrays(1, &vaoPrime[0]);
			glGenVertexArrays(1, &vaoPrime[1]);

			if(uiSetTexUnits != 0) {
				if (uiSetTexUnits>4) uiTextureUnits = 4;
				else uiTextureUnits = uiSetTexUnits;

				uiTextureArray = new GLuint[uiSetTexUnits];
				for(unsigned int i = 0; i < uiSetTexUnits; i++) {
					uiTextureArray[i] = 0;
				}
			}
			else {
				uiTextureUnits = 0;
				uiTextureArray = nullptr;
				//uiTextureArray = new GLuint[uiSetTexUnits];
				//uiTextureArray[uiSetTexUnits] = 0;
			}
			bStarted = true;
		}
		else {
			bFinished = false;
			primitiveType = primitive;
			uiNumVerts = uiNum;
			uiNumDrawVerts = uiDraw;
			uiMaxInstances = uiInstances;
		}

		glBindVertexArray(vaoPrime[bPrime]);
	}

	void VAO::CopyData(GLenum eAttrib, Core::Data3f *vData) {
		bFinished=false;
		if (eAttrib==Core::GLA_VERTEX) {
			if(uiVertexArray == 0)	//Has a buffer been created yet?
			{
				//cout << "New Data Buffer..." << endl;
				glGenBuffers(1, &uiVertexArray);
				glBindBuffer(GL_ARRAY_BUFFER, uiVertexArray);
				glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, vData, GL_DYNAMIC_DRAW);
				uiVertexSize = 3;
				uiVertexLength = sizeof(*vData) * uiNumVerts;
			}
			else	//Buffer exists, so lets assume we're overwriting the data
			{
				glBindBuffer(GL_ARRAY_BUFFER, uiVertexArray);
				//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(*vData) * uiNumVerts, vData);					// !!! THIS IS WHERE THE FREEZING IS HAPPENING !!!
				glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, vData, GL_DYNAMIC_DRAW);
			}
		}
		else if (eAttrib==Core::GLA_NORMAL) {
			if(uiNormalArray == 0)	//Has a buffer been created yet?
			{
				glGenBuffers(1, &uiNormalArray);
				glBindBuffer(GL_ARRAY_BUFFER, uiNormalArray);
				glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, vData, GL_DYNAMIC_DRAW);
				uiNormalSize = 3;
				uiNormalLength = sizeof(*vData) * uiNumVerts;
			}
			else	//Buffer exists, so lets assume we're overwriting the data
			{
				glBindBuffer(GL_ARRAY_BUFFER, uiNormalArray);
				//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(*vData) * uiNumVerts, vData);
				glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, vData, GL_DYNAMIC_DRAW);
			}
		}
		else if (eAttrib==Core::GLA_POSITION) {
			if (uiMaxInstances > 0) {	//Are we allowed to do instancing?
				if(uiPositionArray == 0)	//Has a buffer been created yet?
				{
					glGenBuffers(1, &uiPositionArray);
					glBindBuffer(GL_ARRAY_BUFFER, uiPositionArray);
					glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiMaxInstances, vData, GL_DYNAMIC_DRAW);
					uiPositionSize = 3;
					uiPositionLength = sizeof(*vData) * uiMaxInstances;
					uiPositionOffset+=sizeof(GLfloat) * 3;
				}
				else	//Buffer exists, so lets assume we're overwriting the data
				{
					glBindBuffer(GL_ARRAY_BUFFER, uiPositionArray);
					//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(*vData) * uiMaxInstances, vData);
					glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiMaxInstances, vData, GL_DYNAMIC_DRAW);
				}
			}
			else std::cout << "ERROR!!! CANNOT DO INSTANCING!!!" << std::endl;
		}
		else if (eAttrib==Core::GLA_EXTRA) {
			if (uiMaxInstances > 0) {	//Are we allowed to do instancing?
				if(uiExtraArray == 0)	//Has a buffer been created yet?
				{
					glGenBuffers(1, &uiExtraArray);
					glBindBuffer(GL_ARRAY_BUFFER, uiExtraArray);
					glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiMaxInstances, vData, GL_DYNAMIC_DRAW);
					uiExtraSize = 3;
					uiExtraLength = sizeof(*vData) * uiMaxInstances;
					uiExtraOffset+=sizeof(GLfloat) * 3;
				}
				else	//Buffer exists, so lets assume we're overwriting the data
				{
					glBindBuffer(GL_ARRAY_BUFFER, uiExtraArray);
					//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(*vData) * uiMaxInstances, vData);
					glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiMaxInstances, vData, GL_DYNAMIC_DRAW);
				}
			}
			else std::cout << "ERROR!!! CANNOT DO INSTANCING!!!" << std::endl;
		}
	}

//	void VAO::CopyData(GLenum eAttrib, GLushort *uiIndex, long lNumIndex) {
//		bFinished=false;
//		if(lNumIndex==0) lNumIndex = uiNumDrawVerts;
//		if (eAttrib==Core::GLA_INDEX) {
//			if(uiIndexArray == 0)	//Has a buffer been created yet?
//			{
//				glGenBuffers(1, &uiIndexArray);
//				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIndexArray);
//				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*uiIndex) * lNumIndex, uiIndex, GL_DYNAMIC_DRAW);
//				uiIndexLength = sizeof(*uiIndex) * lNumIndex;
//			}
//			else	//Buffer exists, so lets assume we're overwriting the data
//			{
//				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIndexArray);
//			//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(*uiIndex) * uiNumVerts, uiIndex);
//				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*uiIndex) * lNumIndex, uiIndex, GL_DYNAMIC_DRAW);
//			}
//		}
//	}

	void VAO::CopyData(GLenum eAttrib, GLuint *uiIndex, long lNumIndex) {
		bFinished=false;
		if(lNumIndex==0) lNumIndex = uiNumDrawVerts;
		if (eAttrib==Core::GLA_INDEX) {
			if(uiIndexArray == 0)	//Has a buffer been created yet?
			{
				glGenBuffers(1, &uiIndexArray);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIndexArray);
				//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*uiIndex) * lNumIndex, uiIndex, GL_DYNAMIC_DRAW);
				//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*uiIndex), uiIndex, GL_DYNAMIC_DRAW);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * lNumIndex, uiIndex, GL_DYNAMIC_DRAW);
				uiIndexLength = sizeof(*uiIndex) * lNumIndex;
			}
			else	//Buffer exists, so lets assume we're overwriting the data
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIndexArray);
			//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(*uiIndex) * uiNumVerts, uiIndex);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*uiIndex) * lNumIndex, uiIndex, GL_DYNAMIC_DRAW);
			}
		}
	}

	void VAO::CopyData(GLenum eAttrib, Core::Data2f *vData, GLuint uiLayer) {
		bFinished=false;
		if (eAttrib==Core::GLA_TEXTURE) {
			if(uiTextureArray[uiLayer] == 0)	//Has a buffer been created yet?
			{
				glGenBuffers(1, &uiTextureArray[uiLayer]);
				glBindBuffer(GL_ARRAY_BUFFER, uiTextureArray[uiLayer]);
				glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, vData, GL_DYNAMIC_DRAW);
				uiTextureLength = sizeof(*vData) * uiNumVerts;
			}
			else	//Buffer exists, so lets assume we're overwriting the data
			{
				glBindBuffer(GL_ARRAY_BUFFER, uiTextureArray[uiLayer]);
			//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(*vData) * uiNumVerts, vData);
				glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, vData, GL_DYNAMIC_DRAW);
			}
		}
	}

	void VAO::CopyData(GLenum eAttrib, Core::Data4f *vData) {
		bFinished=false;
		if (eAttrib==Core::GLA_VERTEX) {
			if(uiVertexArray == 0)	//Has a buffer been created yet?
			{
				glGenBuffers(1, &uiVertexArray);
				glBindBuffer(GL_ARRAY_BUFFER, uiVertexArray);
				glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, vData, GL_DYNAMIC_DRAW);
				uiVertexSize = 4;
				uiVertexLength = sizeof(*vData) * uiNumVerts;
			}
			else	//Buffer exists, so lets assume we're overwriting the data
			{
				glBindBuffer(GL_ARRAY_BUFFER, uiVertexArray);
				//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(*vData) * uiNumVerts, vData);
				glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, vData, GL_DYNAMIC_DRAW);
			}
		}
		else if (eAttrib==Core::GLA_NORMAL) {
			if(uiNormalArray == 0)	//Has a buffer been created yet?
			{
				glGenBuffers(1, &uiNormalArray);
				glBindBuffer(GL_ARRAY_BUFFER, uiNormalArray);
				glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, vData, GL_DYNAMIC_DRAW);
				uiNormalSize = 4;
				uiNormalLength = sizeof(*vData) * uiNumVerts;
			}
			else	//Buffer exists, so lets assume we're overwriting the data
			{
				glBindBuffer(GL_ARRAY_BUFFER, uiNormalArray);
				//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(*vData) * uiNumVerts, vData);
				glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, vData, GL_DYNAMIC_DRAW);
			}
		}
		else if (eAttrib==Core::GLA_COLOR) {
			if(uiColorArray == 0)	//Has a buffer been created yet?
			{
				glGenBuffers(1, &uiColorArray);
				glBindBuffer(GL_ARRAY_BUFFER, uiColorArray);
				glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, vData, GL_DYNAMIC_DRAW);
				uiColorLength = sizeof(*vData) * uiNumVerts;
			}
			else	//Buffer exists, so lets assume we're overwriting the data
			{
				glBindBuffer(GL_ARRAY_BUFFER, uiColorArray);
				//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(*vData) * uiNumVerts, vData);
				glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, vData, GL_DYNAMIC_DRAW);
			}
		}
		else if (eAttrib==Core::GLA_POSITION) {
			if (uiMaxInstances > 0) {	//Are we allowed to do instancing?
				if(uiPositionArray == 0)	//Has a buffer been created yet?
				{
					glGenBuffers(1, &uiPositionArray);
					glBindBuffer(GL_ARRAY_BUFFER, uiPositionArray);
					glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiMaxInstances, vData, GL_DYNAMIC_DRAW);
					uiPositionSize = 4;
					uiPositionLength = sizeof(*vData) * uiMaxInstances;
					uiPositionOffset+=sizeof(GLfloat) * 4;
				}
				else	//Buffer exists, so lets assume we're overwriting the data
				{
					glBindBuffer(GL_ARRAY_BUFFER, uiPositionArray);
					//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(*vData) * uiMaxInstances, vData);
					glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiMaxInstances, vData, GL_DYNAMIC_DRAW);
				}
			}
			else std::cout << "ERROR!!! CANNOT DO INSTANCING!!!" << std::endl;
		}
		else if (eAttrib==Core::GLA_EXTRA) {
			if (uiMaxInstances > 0) {	//Are we allowed to do instancing?
				if(uiExtraArray == 0)	//Has a buffer been created yet?
				{
					glGenBuffers(1, &uiExtraArray);
					glBindBuffer(GL_ARRAY_BUFFER, uiExtraArray);
					glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiMaxInstances, vData, GL_DYNAMIC_DRAW);
					uiExtraSize = 4;
					uiExtraLength = sizeof(*vData) * uiMaxInstances;
					//for (unsigned int y=0; y < 20; y++) {
					//	printf("Item[%i]; (%f, %f)\n", y, vData[y][0], vData[y][2]);
					//}
					//uiPositionOffset = sizeof(vData);
					uiExtraOffset+=sizeof(GLfloat) * 4;
				}
				else	//Buffer exists, so lets assume we're overwriting the data
				{
					//glGenBuffers(1, &uiPositionArray);
					glBindBuffer(GL_ARRAY_BUFFER, uiExtraArray);
					//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(*vData) * uiMaxInstances, vData);
					glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiMaxInstances, vData, GL_DYNAMIC_DRAW);
				}
			}
			else std::cout << "ERROR!!! CANNOT DO INSTANCING!!!" << std::endl;
		}
	}

	void VAO::ReplaceData(GLenum eAttrib, Core::Data3f *vData) {
		bFinished=false;
		if (eAttrib==Core::GLA_VERTEX) {
			glBindBuffer(GL_ARRAY_BUFFER, uiVertexArray);
			glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, NULL, GL_DYNAMIC_DRAW);
			glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, vData, GL_DYNAMIC_DRAW);
		}
		else if (eAttrib==Core::GLA_NORMAL) {
			glBindBuffer(GL_ARRAY_BUFFER, uiNormalArray);
			glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, NULL, GL_DYNAMIC_DRAW);
			glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, vData, GL_DYNAMIC_DRAW);
		}
		else if (eAttrib==Core::GLA_POSITION) {
				glBindBuffer(GL_ARRAY_BUFFER, uiPositionArray);
				glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * uiPositionSize * uiMaxInstances, NULL, GL_DYNAMIC_DRAW);
				glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * uiPositionSize * uiMaxInstances, vData, GL_DYNAMIC_DRAW);
		}
	}

	void VAO::ReplaceData(GLenum eAttrib, Core::Data4f *vData) {
		bFinished=false;
		if (eAttrib==Core::GLA_VERTEX) {
			glBindBuffer(GL_ARRAY_BUFFER, uiVertexArray);
			glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, NULL, GL_DYNAMIC_DRAW);
			glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, vData, GL_DYNAMIC_DRAW);
		}
		else if (eAttrib==Core::GLA_COLOR) {
			glBindBuffer(GL_ARRAY_BUFFER, uiColorArray);
			glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, NULL, GL_DYNAMIC_DRAW);
			//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 4 * uiNumVerts, vData);
			glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, vData, GL_DYNAMIC_DRAW);
		}
	}

	void VAO::ReplaceData(GLenum eAttrib, Core::Data2f *vData, GLuint uiLayer) {
		bFinished=false;
		if (eAttrib==Core::GLA_TEXTURE) {
			glBindBuffer(GL_ARRAY_BUFFER, uiTextureArray[uiLayer]);
		//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 2 * uiNumVerts, vData);
			glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, NULL, GL_DYNAMIC_DRAW);
			glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, vData, GL_DYNAMIC_DRAW);
		}
	}

	void VAO::ReplaceData(GLenum eAttrib, GLushort *uiIndex, long lNumIndex) {
		bFinished=false;
		if(lNumIndex==0) lNumIndex = uiNumDrawVerts;
		if (eAttrib==Core::GLA_INDEX) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIndexArray);
			//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLushort) * 3 * uiNumVerts, uiIndex);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*uiIndex) * lNumIndex, NULL, GL_DYNAMIC_DRAW);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(*uiIndex) * lNumIndex, uiIndex, GL_DYNAMIC_DRAW);
		}
	}

	void VAO::Reset() {
		//bStarted = false;
		bFinished = false;

		// Buffer flipping
		if(bPrime == 0) bPrime = 1;
		else bPrime = 0;

		std::cout << "VAO #" << bPrime << std::endl;

		glBindVertexArray(vaoPrime[bPrime]);

		if(uiVertexArray != 0)	{
			//glDeleteBuffers(		1, &uiVertexArray);
			//uiVertexArray = 0;
			glBindBuffer(GL_ARRAY_BUFFER, uiVertexArray);
			glBufferData(GL_ARRAY_BUFFER, uiVertexLength, NULL, GL_DYNAMIC_DRAW);
		}
		if(uiNormalArray != 0)	{
			//glDeleteBuffers(		1, &uiNormalArray);
			//uiNormalArray = 0;
			glBindBuffer(GL_ARRAY_BUFFER, uiNormalArray);
			glBufferData(GL_ARRAY_BUFFER, uiNormalLength, NULL, GL_DYNAMIC_DRAW);
		}
		if(uiColorArray != 0)	{
			//glDeleteBuffers(		1, &uiColorArray);
			//uiColorArray = 0;
			glBindBuffer(GL_ARRAY_BUFFER, uiColorArray);
			glBufferData(GL_ARRAY_BUFFER, uiColorLength, NULL, GL_DYNAMIC_DRAW);
		}
		if(uiIndexArray != 0)	{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIndexArray);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, uiIndexLength, NULL, GL_DYNAMIC_DRAW);
			//glDeleteBuffers(		1, &uiIndexArray);
			//uiIndexArray = 0;
		}
		if(vaoPrime[0] != 0)	{
			//glDeleteVertexArrays(	1, &vaoPrime[0]);
			//vaoPrime[0] = 0;
		}
		if(vaoPrime[1] != 0)	{
		//	//glDeleteVertexArrays(	1, &vaoPrime[0][1]);
		//	//vaoPrime[0][1] = 0;
		}

		if (uiTextureUnits > 0) {
			//glBufferData(GL_ARRAY_BUFFER, sizeof(*vData) * uiNumVerts, NULL, GL_DYNAMIC_DRAW);
			//for(unsigned int i = 0; i < uiTextureUnits; i++) {
				//glDeleteBuffers(1, &uiTextureArray[i]);
				//uiTextureArray[i] = 0;
			//}
			//delete [] uiTextureArray;
		}

	}

	bool VAO::AddData(GLenum eAttrib, Core::Data3f *vData) {
		if (eAttrib==Core::GLA_VERTEX) {
			if(uiVertexArray == 0) CopyData(eAttrib, vData);	//Has a buffer been created yet?
			else	//Buffer exists, so lets add the data
			{
				if ((uiVertexOffset+sizeof(vData)) < (sizeof(GLfloat) * 3 * uiNumVerts)) {	//Are we going to exceed the buffer size?
					glBindBuffer(GL_ARRAY_BUFFER, uiVertexArray);
					glBufferSubData(GL_ARRAY_BUFFER, uiVertexOffset, sizeof(vData), vData);
					uiVertexOffset+=sizeof(vData);	//Increase our offset for next time
					return 0;
				}
				else return 1;
			}
		}
		else if (eAttrib==Core::GLA_NORMAL) {
			if(uiNormalArray == 0) CopyData(eAttrib, vData);	//Has a buffer been created yet?
			else	//Buffer exists, so lets add the data
			{
				if ((uiNormalOffset+sizeof(vData)) < (sizeof(GLfloat) * 3 * uiNumVerts)) {	//Are we going to exceed the buffer size?
					glBindBuffer(GL_ARRAY_BUFFER, uiNormalArray);
					glBufferSubData(GL_ARRAY_BUFFER, uiNormalOffset, sizeof(vData), vData);
					uiNormalOffset+=sizeof(vData);	//Increase our offset for next time
					return 0;
				}
				else return 1;
			}
		}
		else if (eAttrib==Core::GLA_POSITION) {
				if(uiPositionArray == 0) {
					CopyData(eAttrib, vData);	//Has a buffer been created yet?
				}
				else	//Buffer exists, so lets add the data
				{
					if ((uiPositionOffset+sizeof(vData)) <= (sizeof(GLfloat) * 3 * uiMaxInstances)) {	//Are we going to exceed the buffer size?
						glBindBuffer(GL_ARRAY_BUFFER, uiPositionArray);
						glBufferSubData(GL_ARRAY_BUFFER, uiPositionOffset, sizeof(GLfloat) * 3, vData);
						uiPositionOffset+=sizeof(GLfloat) * 3;	//Increase our offset for next time
					}
				}
		}
		return 0;
	}

	void VAO::AddData(GLenum eAttrib, Core::Data2f *vData, GLuint uiLayer) {
		bFinished=false;
		if (eAttrib==Core::GLA_TEXTURE) {
			if(uiTextureArray[uiLayer] == 0) CopyData(eAttrib, vData, uiLayer);	//Has a buffer been created yet?
			else	//Buffer exists, so lets assume we're overwriting the data
			{
				if ((uiTextureOffset+sizeof(vData)) < (sizeof(GLfloat) * 3 * uiNumVerts)) {	//Are we going to exceed the buffer size?
					glBindBuffer(GL_ARRAY_BUFFER, uiTextureArray[uiLayer]);
					glBufferSubData(GL_ARRAY_BUFFER, uiTextureOffset, sizeof(vData), vData);
					uiTextureOffset+=sizeof(vData);	//Increase our offset for next time
				}
			}
		}
	}

	void VAO::End() {
		bFinished = true;
	}

	void VAO::Draw(GLenum eMode, GLint iStart, GLint iEnd) {
		if(!bFinished) return;
		glBindVertexArray(vaoPrime[bPrime]);

		if(uiVertexArray !=0) {
			glEnableVertexAttribArray(Core::GLA_VERTEX);
			//glVertexAttribDivisor(Core::GLA_VERTEX, 1);
			glBindBuffer(GL_ARRAY_BUFFER, uiVertexArray);
			glVertexAttribPointer(Core::GLA_VERTEX, uiVertexSize, GL_FLOAT, GL_FALSE, 0, 0);
		}

		if(uiColorArray !=0) {
			glEnableVertexAttribArray(Core::GLA_COLOR);
			glBindBuffer(GL_ARRAY_BUFFER, uiColorArray);
			if(uiTextureUnits>0) glVertexAttribPointer(Core::GLA_COLOR, 2, GL_FLOAT, GL_FALSE, 0, 0);
			else glVertexAttribPointer(Core::GLA_COLOR, 4, GL_FLOAT, GL_FALSE, 0, 0);
		}

		if(uiNormalArray != 0) {
			glEnableVertexAttribArray(Core::GLA_NORMAL);
			glBindBuffer(GL_ARRAY_BUFFER, uiNormalArray);
			glVertexAttribPointer(Core::GLA_NORMAL, uiNormalSize, GL_FLOAT, GL_FALSE, 0, 0);
		}

		if(uiIndexArray != 0) {
			glEnableVertexAttribArray(Core::GLA_INDEX);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiIndexArray);
			//glVertexAttribPointer(Core::GLA_INDEX, 1, GL_UNSIGNED_BYTE, GL_FALSE, 0, 0);
			glVertexAttribPointer(Core::GLA_INDEX, 1, GL_UNSIGNED_INT, GL_FALSE, 0, 0);
		}

		if(uiPositionArray != 0) {
			glEnableVertexAttribArray(Core::GLA_POSITION);
			glBindBuffer(GL_ARRAY_BUFFER, uiPositionArray);
			//glVertexAttribPointer(Core::GLA_POSITION, uiPositionSize, GL_FLOAT, GL_FALSE, 0, 0);
			glVertexAttribPointer(Core::GLA_POSITION, uiPositionSize, GL_FLOAT, GL_FALSE, uiPositionSize*sizeof(GLfloat), (GLvoid*)0);
			glVertexAttribDivisor(Core::GLA_POSITION, 1);
		}

		if(uiExtraArray != 0) {
			glEnableVertexAttribArray(Core::GLA_EXTRA);
			glBindBuffer(GL_ARRAY_BUFFER, uiExtraArray);
			//glVertexAttribPointer(Core::GLA_POSITION, uiPositionSize, GL_FLOAT, GL_FALSE, 0, 0);
			glVertexAttribPointer(Core::GLA_EXTRA, uiExtraSize, GL_FLOAT, GL_FALSE, uiExtraSize*sizeof(GLfloat), (GLvoid*)0);
			glVertexAttribDivisor(Core::GLA_EXTRA, 1);
		}

		if(uiTextureUnits > 0) {
			for(unsigned int i = 0; i < uiTextureUnits; i++) {
				if(uiTextureArray[i] != 0) {
					glEnableVertexAttribArray(Core::GLA_TEXTURE0 + i),
					glBindBuffer(GL_ARRAY_BUFFER, uiTextureArray[i]);
					glVertexAttribPointer(Core::GLA_TEXTURE0 + i, 2, GL_FLOAT, GL_FALSE, 0, 0);
				}
			}
		}

		switch (eMode) {
			case Core::GLM_DRAW_ARRAYS:
				glDrawArrays(primitiveType, iStart, uiNumDrawVerts);
			break;
			case Core::GLM_DRAW_ELEMENTS:
				//glDrawElements(primitiveType, uiNumDrawVerts, GL_UNSIGNED_SHORT, 0);
				glDrawElements(primitiveType, uiNumDrawVerts, GL_UNSIGNED_INT, 0);
			break;
			case Core::GLM_DRAW_RANGE_ELEMENTS:
				/*
				 * iStart is the exact starting position of the primitive to start at
				 * iEnd is the number of elements from iStart to draw (i.e. 3 primitives = 9 elements)
				 */
				#define BUFFER_OFFSET(i) ((char *)NULL + (i))
				//glDrawElements(primitiveType, iEnd, GL_UNSIGNED_SHORT, BUFFER_OFFSET(iStart));
				glDrawElements(primitiveType, iEnd, GL_UNSIGNED_INT, BUFFER_OFFSET(iStart));
				//glDrawElements(primitiveType, iStart, iEnd);
			break;
			case Core::GLM_DRAW_RANGE:
				#define BUFFER_OFFSET(i) ((char *)NULL + (i))
				glDrawArrays(primitiveType, iStart, iEnd);
			break;
			case Core::GLM_DRAW_ARRAYS_INSTANCED:
				glDrawArraysInstanced(primitiveType, iStart, uiNumDrawVerts, iEnd);	//iEnd is used as the number of instances here
			break;
		}

		glDisableVertexAttribArray(Core::GLA_VERTEX);
		glDisableVertexAttribArray(Core::GLA_NORMAL);
		glDisableVertexAttribArray(Core::GLA_COLOR);
		glDisableVertexAttribArray(Core::GLA_INDEX);
		glDisableVertexAttribArray(Core::GLA_POSITION);

		if(uiTextureUnits > 0)
			for(unsigned int i = 0; i < uiTextureUnits; i++)
				if(uiTextureArray[i] != 0)
					glDisableVertexAttribArray(Core::GLA_TEXTURE0 + i);

		//glBindBuffer(0);
	//	glBindVertexArray(0);
	}
}
