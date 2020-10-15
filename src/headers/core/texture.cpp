
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#define GL_GLEXT_PROTOTYPES 1		// Enable core profile
#include "gl4_5/glcorearb.h"
#include "gl4_5/glext.h"
#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF

#include "texture.h"

namespace Core {

//	enum e_TEXTURE_FILTER {
//		TEXTURE_FILTER_NEAREST,
//		TEXTURE_FILTER_LINEAR,
//		TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST,
//		TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST,
//		TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR,
//		TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR
//
//	};
	GLenum gleTextureFilter[] = {	GL_NEAREST,
									GL_LINEAR,
									GL_NEAREST_MIPMAP_NEAREST,
									GL_LINEAR_MIPMAP_NEAREST,
									GL_NEAREST_MIPMAP_LINEAR,
									GL_LINEAR_MIPMAP_LINEAR };

//
//	enum e_TEXTURE_CLAMP {
//		TEXTURE_CLAMP_REPEAT,
//		TEXTURE_CLAMP_MIRRORED,
//		TEXTURE_CLAMP_EDGE,
//		TEXTURE_CLAMP_BORDER
//	};

	GLenum gleTextureClamp[] = {	GL_REPEAT,
									GL_MIRRORED_REPEAT,
									GL_CLAMP_TO_EDGE,
									GL_CLAMP_TO_BORDER };









	bool Texture::Begin(int uiRequestedLayers) {
	   if (uiRequestedLayers <= 0) return false;
	   uiNumLayers = uiRequestedLayers;

	   bFinished = new bool[uiNumLayers];
	   for (uint i=0; i < uiNumLayers; i++) bFinished[i]=false;
//	   localDebug.glErrorCheck("Texture", 57);

	   glImage = new GLuint[uiNumLayers];
	   glGenTextures(uiNumLayers, glImage);
//	   localDebug.glErrorCheck("Texture", 61);

	   glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
//	   localDebug.glErrorCheck("Texture", 64);

	   iLoaded = 0;
	   bBeginCalled = true;
	   return true;
	}

//	bool Texture::Add(std::string cDir, std::string cFile, int uiLayer, bool bAnisotropy, GLenum eFilter, GLenum eWrap) {
//
//		uiRequestedLayers
//
//	   if (uiRequestedLayers <= 0) return false;
//	   uiNumLayers = uiRequestedLayers;
//
//	   bFinished = new bool[uiNumLayers];
//	   for (uint i=0; i < uiNumLayers; i++) bFinished[i]=false;
//
//	   glImage = new GLuint[uiNumLayers];
//	   glGenTextures(uiNumLayers, glImage);
//
//	   glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &fLargest);
//
//	   iLoaded = 0;
//	   bBeginCalled = true;
//	   return true;
//	}

	/*
	 * eWRap = GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER, GL_MIRRORED_REPEAT, GL_REPEAT, or GL_MIRROR_CLAMP_TO_EDGE
	 */

	bool Texture::Init3D(int uiLayer, GLsizei width, GLsizei height, GLsizei layerCount, GLsizei mipLevelCount ) {
		if (uiLayer > uiNumLayers) return false;

//		std::cout << "Init3D Errors:\n";
//		GLenum err;
//		while((err = glGetError()) != GL_NO_ERROR) std::cout << " - GL Error: " << err << "\n";

		glEnable(GL_TEXTURE_3D);
		localDebug.glErrorCheck("Texture", 103);

		// TODO: Create a struct of image data/settings
		// TODO: Use a vector for each image
		// TODO: Get rid of reliance on MakePair()
		// TODO: Set bit that 3D has been initialized
		// TODO: Remember number of 3D layers and check when loading
		// TODO: Remember mipmap level
		// TODO: Use an init for 2D textures as well?
		// TODO: Border?

		settings3d.width = width;
		settings3d.height = height;
		settings3d.layerCount = layerCount;
		settings3d.mipLevelCount = mipLevelCount;

		std::cout << "Bind to " << glImage[uiLayer] << "\n";

		glBindTexture(GL_TEXTURE_3D, glImage[uiLayer] );
		localDebug.glErrorCheck("Texture", 143);

		//glTexStorage3D(GL_TEXTURE_3D, 1, GL_RGBA8, width, height, layerCount);
//		glTexStorage3D(GL_TEXTURE_3D, 1, GL_RGBA8, width, height, layerCount);
		//localDebug.glErrorCheck("Texture", 146);

		GLsizei border = 0;
		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA8, width, height, layerCount, border, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
//		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, 512, 512, 6, 0, texture_format, GL_UNSIGNED_BYTE, sdlImage->pixels);
		localDebug.glErrorCheck("Texture", 150);

		glBindTexture( GL_TEXTURE_3D, 0 );
		settings3d.bInit = true;

		return true;
	}

//	bool Texture::Init3D(int uiLayer, GLsizei width, GLsizei height, GLsizei layerCount, GLsizei mipLevelCount ) {
//		if (uiLayer > uiNumLayers) return false;
//
//		std::cout << "Init3D Errors:\n";
//		GLenum err;
//		while((err = glGetError()) != GL_NO_ERROR) std::cout << " - GL Error: " << err << "\n";
//
//		std::cout << "Enable GL_TEXTURE_3D";
//		glEnable(GL_TEXTURE_3D);
//		while((err = glGetError()) != GL_NO_ERROR) std::cout << " - GL Error: " << err << "\n";
//		std::cout << "\n";
//
//		std::cout << "Enable GL_TEXTURE_2D_ARRAY";
//		glEnable(GL_TEXTURE_2D_ARRAY);
//		while((err = glGetError()) != GL_NO_ERROR) std::cout << " - GL Error: " << err << "\n";
//		std::cout << "\n";
//
////		std::cout << "Enable GL_TEXTURE_2D_MULTISAMPLE";
////		glEnable(GL_TEXTURE_2D_MULTISAMPLE);
////		while((err = glGetError()) != GL_NO_ERROR) std::cout << " - GL Error: " << err << "\n";
////		std::cout << "\n";
//
////		std::cout << "Enable GL_TEXTURE_2D_MULTISAMPLE_ARRAY";
////		glEnable(GL_TEXTURE_2D_MULTISAMPLE_ARRAY);
////		while((err = glGetError()) != GL_NO_ERROR) std::cout << " - GL Error: " << err << "\n";
////		std::cout << "\n";
//
//		// TODO: Create a struct of image data/settings
//		// TODO: Use a vector for each image
//		// TODO: Get rid of reliance on MakePair()
//		// TODO: Set bit that 3D has been initialized
//		// TODO: Remember number of 3D layers and check when loading
//		// TODO: Remember mipmap level
//		// TODO: Use an init for 2D textures as well?
//
//		settings3d.width = width;
//		settings3d.height = height;
//		settings3d.layerCount = layerCount;
//		settings3d.mipLevelCount = mipLevelCount;
//
//		std::cout << "glBindTexture";
//		glBindTexture( GL_TEXTURE_2D_ARRAY, glImage[uiLayer] );
//		while((err = glGetError()) != GL_NO_ERROR) std::cout << " - GL Error: " << err << "\n";
//		std::cout << "\n";
//
////		glTexStorage3D(GL_TEXTURE_2D_ARRAY, mipLevelCount, GL_RGB8, width, height, layerCount);
//
//		std::cout << "glTexStorage3D";
//		glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, width, height, layerCount);
//		while((err = glGetError()) != GL_NO_ERROR) std::cout << " - GL Error: " << err << "\n";
//		std::cout << "\n";
//
////		std::cout << "Errors after Init3D:\n";
////		while((err = glGetError()) != GL_NO_ERROR) std::cout << "GL Error: " << err << "\n";
//
////		for(int i=0; i<layerCount; i++) {
////			glTexImage3D(GL_TEXTURE_2D_ARRAY, mipLevelCount, GL_RGBA, width, height, layerCount, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
////		}
//
//		glBindTexture( GL_TEXTURE_2D_ARRAY, 0 );
//		settings3d.bInit = true;
//
//		return true;
//	}

	bool Texture::Load3D(int uiLayer, std::string cDir, std::string cFile, GLsizei uiDepth, bool bAnisotropy, e_TEXTURE_FILTER eFilterIndex, e_TEXTURE_CLAMP eWrapIndex) {
		localDebug.log("bInit = "+std::to_string(settings3d.bInit)+"\n");
		if(settings3d.bInit) {
			if (uiLayer > uiNumLayers) throw std::runtime_error("[Texture::Load3D] Too many textures allocated.");
			std::string cDirFile = cDir+cFile;
			SDL_Surface * sdlImage; // = new SDL_Surface();

//			if(cFile=="3dtile_01.png") {

			sdlImage = IMG_Load( cDirFile.c_str() );
			if(sdlImage) {
//				MakePair(cFile, uiLayer);

//				std::cout << "Load3D Errors:\n";
//				GLenum err;
//				while((err = glGetError()) != GL_NO_ERROR) std::cout << " - GL Error: " << err << "\n";

				GLenum texture_format;
	//			GLint nOfColors = sdlImage->format->BytesPerPixel;

				if (sdlImage->format->Amask) texture_format = GL_RGBA;
				else texture_format = GL_RGB;
//				texture_format = GL_RGBA;

				// 2D Texture Array
//				glBindTexture(GL_TEXTURE_3D, glImage[uiLayer] );
//				localDebug.glErrorCheck("Texture", 253);

//				glTexSubImage3D(GL_TEXTURE_2D_ARRAY, settings3d.mipLevelCount, 0, 0, uiLevel, settings3d.width, settings3d.height, settings3d.layerCount, GL_RGBA, GL_UNSIGNED_BYTE, sdlImage->pixels);
//				glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, uiLevel, settings3d.width, settings3d.height, settings3d.layerCount, GL_RGBA, GL_UNSIGNED_BYTE, sdlImage->pixels);
//				glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, uiLevel, settings3d.width, settings3d.height, settings3d.layerCount, texture_format, GL_UNSIGNED_BYTE, sdlImage->pixels);
				//glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, uiLevel, settings3d.width, settings3d.height, 1, texture_format, GL_UNSIGNED_BYTE, sdlImage->pixels);
//				glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, uiLevel/settings3d.layerCount, settings3d.width, settings3d.height, 1, texture_format, GL_UNSIGNED_BYTE, sdlImage->pixels);
//				glTexSubImage3D(GL_TEXTURE_3D, 1, 0, 0, uiLevel/settings3d.layerCount, settings3d.width, settings3d.height, 1, texture_format, GL_UNSIGNED_BYTE, sdlImage->pixels);
//				localDebug.glErrorCheck("Texture", 261);

//				glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//				localDebug.glErrorCheck("Texture", 265);

//				glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//				localDebug.glErrorCheck("Texture", 269);

//				glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MIN_FILTER, gleTextureFilter[eFilterIndex]);
//				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, gleTextureClamp[eWrapIndex]);
//				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//				localDebug.glErrorCheck("Texture", 274);

//				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, gleTextureClamp[eWrapIndex]);
//				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//				localDebug.glErrorCheck("Texture", 278);

//				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, gleTextureClamp[eWrapIndex]);
//				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
//				localDebug.glErrorCheck("Texture", 282);

//				if (bAnisotropy) glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
//				if (gleTextureFilter[eFilterIndex]!=GL_LINEAR && gleTextureFilter[eFilterIndex]!=GL_NEAREST) glGenerateMipmap(GL_TEXTURE_2D_ARRAY);

//				glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);

//				glGenerateMipmap(GL_TEXTURE_3D);
//				localDebug.glErrorCheck("Texture", 290);

//				GLint nOfColors = sdlImage->format->BytesPerPixel;
				glBindTexture(GL_TEXTURE_3D, glImage[uiLayer]);
				localDebug.glErrorCheck("Texture", 266);

				glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
				localDebug.glErrorCheck("Texture", 269);

				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				localDebug.glErrorCheck("Texture", 272);

				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				localDebug.glErrorCheck("Texture", 275);

				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_REPEAT);
				localDebug.glErrorCheck("Texture", 278);

				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_REPEAT);
				localDebug.glErrorCheck("Texture", 284);

				glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				localDebug.glErrorCheck("Texture", 281);

				//glTexImage3D(GL_TEXTURE_3D, 0, nOfColors, settings3d.width, settings3d.height/4, 4, 0, texture_format, GL_UNSIGNED_BYTE, sdlImage->pixels);

				// WORKS with glTexImage3D in init(), but requires single texture array image
//				glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, settings3d.width, settings3d.height/4, 4, 0, texture_format, GL_UNSIGNED_BYTE, sdlImage->pixels);
//				if(!settings3d.bStarted) {
//				glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, 512, 512, 6, 0, texture_format, GL_UNSIGNED_BYTE, sdlImage->pixels);
//				settings3d.bStarted = true;
//				}
//				else {

				// IN-PROGRESS - Doesn't work at all currently (Level 0 causes segfault)
				//glTextureSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, 512, 512, 0, texture_format, GL_UNSIGNED_BYTE, sdlImage->pixels);
//				glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, 0, 1024, 1024, 1, texture_format, GL_UNSIGNED_BYTE, sdlImage->pixels);
//				glTexSubImage3D(GL_TEXTURE_3D, 1, 0, 0, uiDepth, 512, 512, 1, texture_format, GL_UNSIGNED_BYTE, sdlImage->pixels);
				localDebug.log("["+std::to_string(uiLayer)+"] SubImage: "+std::to_string(uiDepth)+"/"+std::to_string(settings3d.layerCount)+"\n");
				glTexSubImage3D(GL_TEXTURE_3D, 0, 0, 0, uiDepth, 512, 512, 1, texture_format, GL_UNSIGNED_BYTE, sdlImage->pixels);
//				}
				localDebug.glErrorCheck("Texture", 288);

				glBindTexture(GL_TEXTURE_3D, 0 );
				localDebug.glErrorCheck("Texture", 291);

				SDL_FreeSurface(sdlImage);
				bFinished[uiLayer] = true;
				iLoaded++;
				cDirFile = "";
			}
//			}
			return true;
		}
		else {
			throw std::runtime_error("Failed Binding Texture: "+cDir+cFile);
		}
	}

//	bool Texture::Load3D(std::string cDir, std::string cFile, int uiLayer, bool bAnisotropy, e_TEXTURE_FILTER eFilterIndex, e_TEXTURE_CLAMP eWrapIndex) {
//	bool Texture::Load3D(std::string cDir, std::string cFile, int uiLayer, GLsizei uiLevel, bool bAnisotropy, e_TEXTURE_FILTER eFilterIndex, e_TEXTURE_CLAMP eWrapIndex) {
//		if(settings3d.bInit) {
//			if (uiLayer > uiNumLayers) return false;
//			std::string cDirFile = cDir+cFile;
//			SDL_Surface * sdlImage; // = new SDL_Surface();
//
//			sdlImage = IMG_Load( cDirFile.c_str() );
//			if(sdlImage) {
//				MakePair(cFile, uiLayer);
//
//				std::cout << "Load3D Errors:\n";
//				GLenum err;
//				while((err = glGetError()) != GL_NO_ERROR) std::cout << " - GL Error: " << err << "\n";
//
//				GLenum texture_format;
//	//			GLint nOfColors = sdlImage->format->BytesPerPixel;
//
//				if (sdlImage->format->Amask) texture_format = GL_RGBA8;
//				else texture_format = GL_RGB;
//
//				// 2D Texture Array
//				std::cout << "glBindTexture";
//				glBindTexture( GL_TEXTURE_2D_ARRAY, glImage[uiLayer] );
//				while((err = glGetError()) != GL_NO_ERROR) std::cout << " - GL Error: " << err << "\n";
//				std::cout << "\n";
////				glTexSubImage3D(GL_TEXTURE_2D_ARRAY, settings3d.mipLevelCount, 0, 0, uiLevel, settings3d.width, settings3d.height, settings3d.layerCount, GL_RGBA, GL_UNSIGNED_BYTE, sdlImage->pixels);
////				glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, uiLevel, settings3d.width, settings3d.height, settings3d.layerCount, GL_RGBA, GL_UNSIGNED_BYTE, sdlImage->pixels);
//
//				std::cout << "glTexSubImage3D";
//				glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, uiLevel, settings3d.width, settings3d.height, settings3d.layerCount, GL_RGBA8, GL_UNSIGNED_BYTE, sdlImage->pixels);
//				while((err = glGetError()) != GL_NO_ERROR) std::cout << " - GL Error: " << err << "\n";
//				std::cout << "\n";
//
//				std::cout << "glTexParameteri";
//				glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//				while((err = glGetError()) != GL_NO_ERROR) std::cout << " - GL Error: " << err << "\n";
//				std::cout << "\n";
//
//				std::cout << "glTexParameteri";
//				glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//				while((err = glGetError()) != GL_NO_ERROR) std::cout << " - GL Error: " << err << "\n";
//				std::cout << "\n";
//
////				glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MIN_FILTER, gleTextureFilter[eFilterIndex]);
//				std::cout << "glTexParameteri";
//				glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_S, gleTextureClamp[eWrapIndex]);
//				while((err = glGetError()) != GL_NO_ERROR) std::cout << " - GL Error: " << err << "\n";
//				std::cout << "\n";
//
//				std::cout << "glTexParameteri";
//				glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_T, gleTextureClamp[eWrapIndex]);
//				while((err = glGetError()) != GL_NO_ERROR) std::cout << " - GL Error: " << err << "\n";
//				std::cout << "\n";
//
//				std::cout << "glTexParameteri";
//				glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_R, gleTextureClamp[eWrapIndex]);
//				while((err = glGetError()) != GL_NO_ERROR) std::cout << " - GL Error: " << err << "\n";
//				std::cout << "\n";
//
////				if (bAnisotropy) glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
////				if (gleTextureFilter[eFilterIndex]!=GL_LINEAR && gleTextureFilter[eFilterIndex]!=GL_NEAREST) glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
//				std::cout << "glBindTexture";
//				glBindTexture( GL_TEXTURE_2D_ARRAY, 0 );
//				while((err = glGetError()) != GL_NO_ERROR) std::cout << " - GL Error: " << err << "\n";
//				std::cout << "\n";
//
//				SDL_FreeSurface(sdlImage);
//				bFinished[uiLayer] = true;
//				iLoaded++;
//				cDirFile = "";
//			}
//			return true;
//		}
//		else {
//			throw std::runtime_error("Failed Binding Texture: "+cDir+cFile);
//		}
//	}

	bool Texture::Load(std::string cDir, std::string cFile, int uiLayer, bool bAnisotropy, e_TEXTURE_FILTER eFilterIndex, e_TEXTURE_CLAMP eWrapIndex) {
		if (uiLayer > uiNumLayers) return false;
		std::string cDirFile = cDir+cFile;
		SDL_Surface * sdlImage; // = new SDL_Surface();

		sdlImage = IMG_Load( cDirFile.c_str() );
		if(sdlImage) {
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
			if (gleTextureFilter[eFilterIndex]!=GL_LINEAR && gleTextureFilter[eFilterIndex]!=GL_NEAREST) {
			   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gleTextureFilter[eFilterIndex]);
			   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, eFilter);
			   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gleTextureFilter[eFilterIndex]);
			}
			else {
			   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gleTextureFilter[eFilterIndex]);
			   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gleTextureFilter[eFilterIndex]);
			}
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gleTextureClamp[eWrapIndex]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, gleTextureClamp[eWrapIndex]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gleTextureClamp[eWrapIndex]);
			if (gleTextureFilter[eFilterIndex]!=GL_LINEAR && gleTextureFilter[eFilterIndex]!=GL_NEAREST) glGenerateMipmap(GL_TEXTURE_2D);
			SDL_FreeSurface(sdlImage);
			//delete sdlImage;
			bFinished[uiLayer] = true;
			iLoaded++;
			cDirFile = "";

			localDebug.glErrorCheck("Texture", 444);
			return true;
		}
		else {
			throw std::runtime_error("Failed Binding Texture: "+cDir+cFile);
		}
	}

	bool Texture::Load(std::string cDir, std::string cFile, int uiLayer, bool bAnisotropy, GLenum eFilter, GLenum eWrap) {
		if (uiLayer > uiNumLayers) return false;
		std::string cDirFile = cDir+cFile;
		SDL_Surface * sdlImage; // = new SDL_Surface();

		sdlImage = IMG_Load( cDirFile.c_str() );
		if(sdlImage) {
			MakePair(cFile, uiLayer);

			GLenum texture_format;
			GLint nOfColors = sdlImage->format->BytesPerPixel;

			if (sdlImage->format->Amask) texture_format = GL_RGBA;
			else texture_format = GL_RGB;

			// TODO: nOfColors changed to GL_SRGB_ALPHA, this allows Gamma setting to work correctly
			glBindTexture( GL_TEXTURE_2D, glImage[uiLayer] );
//			localDebug.glErrorCheck("Texture", 451);

			//glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, sdlImage->w, sdlImage->h, 0, texture_format, GL_UNSIGNED_BYTE, sdlImage->pixels );
			glTexImage2D( GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, sdlImage->w, sdlImage->h, 0, texture_format, GL_UNSIGNED_BYTE, sdlImage->pixels );
//			localDebug.glErrorCheck("Texture", 455);

			if (bAnisotropy) glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, fLargest);
//			localDebug.glErrorCheck("Texture", 458);

			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, eFilter);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			if (eFilter!=GL_LINEAR && eFilter!=GL_NEAREST) {
			   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, eFilter);
//			   localDebug.glErrorCheck("Texture", 464);
			   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//			   localDebug.glErrorCheck("Texture", 466);
			}
			else {
			   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, eFilter);
//			   localDebug.glErrorCheck("Texture", 470);
			   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, eFilter);
//			   localDebug.glErrorCheck("Texture", 472);
			}
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, eWrap);
//			localDebug.glErrorCheck("Texture", 475);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, eWrap);
//			localDebug.glErrorCheck("Texture", 477);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, eWrap);
//			localDebug.glErrorCheck("Texture", 479);

			if (eFilter!=GL_LINEAR && eFilter!=GL_NEAREST) glGenerateMipmap(GL_TEXTURE_2D);
//			localDebug.glErrorCheck("Texture", 482);

			SDL_FreeSurface(sdlImage);
			//delete sdlImage;
			bFinished[uiLayer] = true;
			iLoaded++;
			cDirFile = "";
			return true;
		}
		else {
			throw std::runtime_error("Failed Binding Texture: "+cDir+cFile);
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
