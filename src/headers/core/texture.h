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

namespace Core {

	/*
	* Usage:
	*	Texture <name>;
	*		Declare a new texture container of <name>
	*
	*	Begin(<value>);
	*		Create space for <value> number of textures
	*
	*	Load(<dir>, <file>, <layer>, <options>);
	*		Load a texture from disk into <layer> where <layer> is less than <value>
	*
	*	Set(<name or layer>);
	*		Set the texture by name or layer number as the active texture, used after glActiveTexture()
	*
	*	Get(<name>);
	*		Returns the layer number of the image
	*/
	class Texture {
		private:
			GLfloat		fLargest;			// Maximum ANISOTROPY
			GLuint		uiNumLayers;		// Maximum textures that can be loaded
			GLuint		* glImage;			// OpenGL image id
			Map_si		mapImage;			// ID/Filename pairing
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
			inline void MakePair(std::string cName, GLuint uiNum) { mapImage.insert( std::make_pair(cName, uiNum) ); }

		public:
			int		iLoaded;			// Number of textures loaded, no relation to texture id number (id comes from file)
			bool Begin(GLuint uiRequestedLayers);
//			bool Load(std::string cDir, std::string cFile, GLuint uiLayer, bool bAnisotropy=false, GLenum eFilter=GL_LINEAR, GLenum eWrap=GL_CLAMP_TO_EDGE);
			bool Load(std::string cDir, std::string cFile, GLuint uiLayer, bool bAnisotropy=false, GLenum eFilter=GL_LINEAR, GLenum eWrap=GL_REPEAT);
//			void CreateAtlas(int iWidth, int iHeight);
			Texture() {
				fLargest = 0.0f;
				uiNumLayers = 0;
				glImage = nullptr;
				bFinished = nullptr;
				iLoaded = 0;
				bBeginCalled = false;
			}
			~Texture() {
				if (bBeginCalled) {
					for(uint i=0; i<uiNumLayers; i++) {
						if(bFinished[i]) {
							if(glIsTexture(glImage[i])) {
								//cout << "Deleting Texture:" << i << ":" << glImage[i] << endl;
								glDeleteTextures(1, &glImage[i]);
							}
						}
					}
					delete[] bFinished;
					delete[] glImage;
				}
			}

			inline int			Get(std::string cName)	{ return mapImage[cName]; }
			inline void			Set(GLuint uiLayer)		{ glBindTexture(GL_TEXTURE_2D, glImage[uiLayer]); }
			inline void 		Set(std::string cName)	{ glBindTexture(GL_TEXTURE_2D, glImage[mapImage[cName]]); }
			inline std::string	Get(GLuint uiLayer)		{ for(auto const &ent1 : mapImage) { if (ent1.second == uiLayer) return ent1.first; } return 0; }
	};
}

#endif /* TEXTURE_H_ */
