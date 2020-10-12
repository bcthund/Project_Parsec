#ifndef VAO_H_
#define VAO_H_

#include <iostream>
#define GL_GLEXT_PROTOTYPES 1		// Enable core profile
#define GL_POINT_SPRITE 0x8861		// Hack to enable Point Sprites thus enabling gl_PointCoord operation
#include "gl4_5/glcorearb.h"
#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#include "./types.h"

namespace Core {
	class VAO {
		private:
		protected:
			GLuint	uiVertexSize;		//Core::Data3f or Core::Data4f?
			GLuint	uiNormalSize;
			GLuint	uiInstanceSize;
			GLuint	uiPositionSize;
			GLuint	uiDataSize;

			GLuint	uiVertexOffset;
			GLuint	uiNormalOffset;
			GLuint	uiColorOffset;
			GLuint	uiIndexOffset;
			GLuint	uiTextureOffset;
			GLuint	uiPositionOffset;
			GLuint	uiInstanceOffset;
			GLuint	uiDataOffset;

			GLuint	uiMaxInstances;

			GLuint	uiVertexLength,
					uiNormalLength,
					uiColorLength,
					uiIndexLength,
					uiPositionLength,
					uiInstanceLength,
					uiDataLength,
					uiTextureLength;

			long	uiNumDrawVerts;			// Number of verticies drawn
			long	uiNumVerts;				// Number of verticies in this batch
			GLuint	uiTextureUnits;		// Number of texture coordinate sets

			GLuint  vaoPrime[2];
			bool	bPrime;				// VAO Orphaning (manual)
			bool	bFinished;			// Batch has been built

		public:
			GLenum	primitiveType;		// What am I drawing....
			GLuint	uiVertexArray;
			GLuint  uiNormalArray;
			GLuint	uiColorArray;
			GLuint	uiIndexArray;
			GLuint	*uiTextureArray;
			GLuint  uiPositionArray;
			GLuint  uiInstanceArray;
			GLuint  uiDataArray;

			VAO();
			~VAO();
			bool bStarted;				// Has the batch already called Begin();
			void Begin(GLenum primitive, long uiNum, long uiDraw, GLuint nTextureUnits=1, GLuint uiInstances=1);
			void Reset();
			void CopyData(GLenum eAttrib, Core::Data3f *vVerts);				//Copy vertex, color, and normal data in 3f format
			void ReplaceData(GLenum eAttrib, Core::Data3f *vVerts);
			void ReplaceData(GLenum eAttrib, Core::Data4f *vVerts);
			void ReplaceData(GLenum eAttrib, Core::Data2f *vData, GLuint uiLayer);
			void ReplaceData(GLenum eAttrib, GLushort *uiIndex, long lNumIndex=0);
			//void CleanData();
			//void CleanData(GLenum eAttrib);
			void CopyData(GLenum eAttrib, Core::Data4f *vVerts);				//Copy color data in 4f format
			void CopyData(GLenum eAttrib, Core::Data2f *vData, GLuint uiLayer);	//Copy coordinates data in 2f format
//			void CopyData(GLenum eAttrib, GLushort *uiIndex, long lNumIndex=0);				//Copy index list
			void CopyData(GLenum eAttrib, GLuint *uiIndex, long lNumIndex=0);
			bool AddData(GLenum eAttrib, Core::Data3f *vData);
			void AddData(GLenum eAttrib, Core::Data2f *vData, GLuint uiLayer);
			void Clean();
			void End();
			void Draw(GLenum eMode=Core::GLM_DRAW_ARRAYS, GLint iStart=0, GLint iEnd=0);
	};
}
#endif /* VAO_H_ */
