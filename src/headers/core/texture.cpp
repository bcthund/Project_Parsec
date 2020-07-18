
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define GL_GLEXT_PROTOTYPES 1		// Enable core profile
#include "gl4_5/glcorearb.h"
#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF

#include "texture.h"

namespace Core {
	bool Texture::Begin(GLuint uiRequestedLayers) {
	   if (uiRequestedLayers <= 0) return false;
	   uiNumLayers = uiRequestedLayers;

	   bFinished = new bool[uiNumLayers];
	   for (uint i=0; i < uiNumLayers; i++) bFinished[i]=false;

	   glImage = new GLuint[uiNumLayers];
	   glGenTextures(uiNumLayers, glImage);

	   glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);

	   iLoaded = 0;
	   bBeginCalled = true;
	   return true;
	}

	/*
	 * eWRap = GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER, GL_MIRRORED_REPEAT, GL_REPEAT, or GL_MIRROR_CLAMP_TO_EDGE
	 */
	bool Texture::Load(std::string cDir, std::string cFile, GLuint uiLayer, bool bAnisotropy, GLenum eFilter, GLenum eWrap) {
	   try  {

	   	    if (uiLayer > uiNumLayers) return false;
		    std::string cDirFile = cDir+cFile;
		    SDL_Surface * sdlImage; // = new SDL_Surface();

			sdlImage = IMG_Load( cDirFile.c_str() );
			MakePair(cFile, uiLayer);

		    GLenum texture_format;
		    GLint nOfColors = sdlImage->format->BytesPerPixel;

		    if (sdlImage->format->Amask) texture_format = GL_RGBA;
		    else texture_format = GL_RGB;

		    // TODO: nOfColors changed to GL_SRGB_ALPHA, this allows Gamma setting to work correctly
		    glBindTexture( GL_TEXTURE_2D, glImage[uiLayer] );
		    //glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, sdlImage->w, sdlImage->h, 0, texture_format, GL_UNSIGNED_BYTE, sdlImage->pixels );
			glTexImage2D( GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, sdlImage->w, sdlImage->h, 0, texture_format, GL_UNSIGNED_BYTE, sdlImage->pixels );
		    if (bAnisotropy) glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
		    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, eFilter);
		    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		    if (eFilter!=GL_LINEAR && eFilter!=GL_NEAREST) {
			   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, eFilter);
			   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, eFilter);
			   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, eFilter);
		    }
		    else {
			   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, eFilter);
			   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, eFilter);
		    }
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, eWrap);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, eWrap);
		    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, eWrap);
		    if (eFilter!=GL_LINEAR && eFilter!=GL_NEAREST) glGenerateMipmap(GL_TEXTURE_2D);
		    SDL_FreeSurface(sdlImage);
		    //delete sdlImage;
		    bFinished[uiLayer] = true;
		    iLoaded++;
		    cDirFile = "";
		    return true;
	   }
	   catch (...)
	   {
		   //SDL_FreeSurface(sdlImage);
		   printf("Failed Binding Texture.\n");
		   //cDirFile = "";
		   return false;
	   }
	}

//	void Texture::SetupAtlas(int iWidth, int iHeight) {
//		if(iWidth>0 && iHeight>0) {
//			atlas.bEnable = true;
//			atlas.iHeight = iHeight;
//			atlas.iWidth = iWidth;
//		}
//		else atlas.bEnable = false;
//	}
//
//	void Texture::SetProgression(float f) {
//		atlas.fProgression = f;
//	}

	//inline void Texture::LoadImageFromFile(std::string file, SDL_Surface * sdlImage) {
	   //SDL_Surface * sdlImage;
	//   sdlImage = IMG_Load( file.c_str() );
	   //return sdlImage;
	//}
}
