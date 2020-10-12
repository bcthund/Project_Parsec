/*
 * texture.h
 *
 *  Created on: Jan 28, 2014
 *      Author: bcthund
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <map>
#include <SDL2/SDL.h>

#include "gl4_5/glcorearb.h"
#include "types.h"
#include "texture.h"

namespace Core {

	/*
	 	 TODO: Fix texture system to allow add/remove with vectormap

	 	 [ ] glImage should be a VectorMap
	 	 [ ] deprecate uiNumLayers
	 	 [ ]


	 */

//	enum e_TEXTURE_FILTER {
//		TEXTURE_FILTER_NEAREST,
//		TEXTURE_FILTER_LINEAR,
//		TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST,
//		TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST,
//		TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR,
//		TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR
//
//	};
//	GLenum gleTexture3DFilter[] = {	GL_NEAREST,
//									GL_LINEAR,
//									GL_NEAREST_MIPMAP_NEAREST,
//									GL_LINEAR_MIPMAP_NEAREST,
//									GL_NEAREST_MIPMAP_LINEAR,
//									GL_LINEAR_MIPMAP_LINEAR };
//
//
//	enum e_TEXTURE_CLAMP {
//		TEXTURE_CLAMP_REPEAT,
//		TEXTURE_CLAMP_MIRRORED,
//		TEXTURE_CLAMP_EDGE,
//		TEXTURE_CLAMP_BORDER
//	};
//
//	GLenum gleTexture3DClamp[] = {	GL_REPEAT,
//									GL_MIRRORED_REPEAT,
//									GL_CLAMP_TO_EDGE,
//									GL_CLAMP_TO_BORDER };

//	struct s_TEXTURE_CLAMP {
//
//	};

	/*
	* Usage:
	*	Texture3D <name>;
	*		Declare a new texture container of <name>
	*
	*	Begin(<value>);
	*		Create space for <value> number of textures
	*
	*	Load(<dir>, <file>, <layer>, <options>);
	*		Load a texture from disk into <layer> where <layer> is less than <value>
	*
	*	Set(<name or layer>);
	*		Set the texture by name or layer number as the active texture, used after glActiveTexture3D()
	*
	*	Get(<name>);
	*		Returns the layer number of the image
	*/
	class Texture3D {
		private:
			GLfloat		fLargest;			// Maximum ANISOTROPY
			GLuint		uiNumLayers;		// Maximum textures that can be loaded
			GLuint		* glImage;			// OpenGL image id
			t_VectorMap<int> mapImage;
			bool		* bFinished;		// Array confirming loaded textures
			bool		bBeginCalled;		// If begin hasn't been called, then abort destruction
//			struct _AtlasData {
//				bool bEnable;
//				int iWidth;
//				int	iHeight;
//
//				_AtlasData::_AtlasData() {
//					bEnable = false;
//					iWidth = 1;
//					iHeight = 1;
//				}
//			} atlas;

		protected:
			void LoadImageFromFile(std::string file, SDL_Surface * sdlImage);
			inline void MakePair(std::string cName, int uiNum) { mapImage.add(cName, uiNum); }

		public:
			int		iLoaded;			// Number of textures loaded, no relation to texture id number (id comes from file)
			bool Begin(int uiRequestedLayers);
//			bool Add(std::string cDir, std::string cFile, int uiLayer, bool bAnisotropy=false, GLenum eFilter=GL_LINEAR, GLenum eWrap=GL_REPEAT);
//			bool Load(std::string cDir, std::string cFile, GLuint uiLayer, bool bAnisotropy=false, GLenum eFilter=GL_LINEAR, GLenum eWrap=GL_CLAMP_TO_EDGE);
			bool Load(std::string cDir, std::string cFile, int uiLayer, bool bAnisotropy=false, GLenum eFilter=GL_LINEAR, GLenum eWrap=GL_REPEAT);
			bool Load(std::string cDir, std::string cFile, int uiLayer, bool bAnisotropy, e_TEXTURE_FILTER eFilterIndex, e_TEXTURE_CLAMP eWrapIndex);
//			void CreateAtlas(int iWidth, int iHeight);
			Texture3D() {
				fLargest = 0.0f;
				uiNumLayers = 0;
				glImage = nullptr;
				bFinished = nullptr;
				iLoaded = 0;
				bBeginCalled = false;
			}
			~Texture3D() {
				if (bBeginCalled) {
					for(uint i=0; i<uiNumLayers; i++) {
						if(bFinished[i]) {
							if(glIsTexture(glImage[i])) {
								glDeleteTextures(1, &glImage[i]);
							}
						}
					}
					delete[] bFinished;
					delete[] glImage;
				}
			}

			inline GLuint&		Get(std::string cName)	{	return glImage[mapImage[cName]];	}
			inline GLuint&		Get(int uiLayer)		{	return glImage[uiLayer];	}

//			inline int			Get(std::string cName)	{	return mapImage[cName];	}
			inline void			Set(std::variant<int, std::string> ref)		{
				if(ref.index()==0) {

					glBindTexture(GL_TEXTURE_2D, glImage[std::get<int>(ref)]);
				}
				else {
					glBindTexture(GL_TEXTURE_2D, glImage[mapImage[std::get<std::string>(ref)]]);
				}
			}

//			inline void			Set(int uiLayer)		{	glBindTexture3D(GL_TEXTURE_2D, glImage[uiLayer]);	}
//			inline void 		Set(std::string cName)	{	glBindTexture3D(GL_TEXTURE_2D, glImage[mapImage[cName]]);	}
//			inline std::string	Get(int uiLayer)		{	return mapImage.getName(uiLayer);	}
	};
}

#endif /* TEXTURE_H_ */
