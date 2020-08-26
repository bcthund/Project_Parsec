/*
 * SystemTextures.cpp
 *
 *  Created on: Sep 6, 2019
 *      Author: bcthund
 */

#include "SystemTextures.h"

namespace Core {

	_SystemTextures::_SystemTextures() {
		uiNumTextures	= 64;
		uiRecordSize	= 32;
		sFilename		= "system.bin";
		sDir			= "./system/";
		sTexDir			= "./texture/system/global/";
	}

	_SystemTextures::~_SystemTextures() {
	}

	bool _SystemTextures::load() {
		try {
			//            .................................................................Done
			std::cout << "Load Global Textures.............................................";
			MemBlock memBlock;
			std::string theImage;
			texture.Begin(uiNumTextures);

			readFile((sDir+sFilename), memBlock);

			// System textures must follow ID order
			int iIDVerify = 0;

			for (int d=0; d<memBlock.size; d+=uiRecordSize) {
				int theId=0;
				for (int i=0; i<4; i++) theId+=(unsigned char)memBlock.buffer[i+d];

				if (theId != iIDVerify) throw  ("Texture ID Mismatch [" + std::to_string(theId) + "!=" + std::to_string(iIDVerify) + "] @ SystemTextures.cpp Line 42");

				theImage = "";
				for (int i=4; i<32; i++)
					if (memBlock.buffer[i+d]!=0) theImage+=(unsigned char)memBlock.buffer[i+d];
					else break;

				texture.Load(sTexDir, theImage, theId);
				iIDVerify++;
			}
			std::cout << "Done" << std::endl;
		}
		catch(std::string &s) {
			std::cout << "!!! ERROR !!! Internal exception: " << s << std::endl;
			std::exit(0);
		}
		catch(const char * s) {
			std::cout << "!!! ERROR !!! Internal exception: " << s << std::endl;
			std::exit(0);
		}
		catch(...) {
			std::cout << "!!! ERROR !!! Unknown Exception" << std::endl;
			std::exit(0);
		}
		return true;
	}

	bool _SystemTextures::calc() {
		std::cout << "Calc Global Textures.............................................";
		std::cout << "Nothing to do" << std::endl;
		return true;
	}

//	void _SystemTextures::set(uint id) {
//		texture.Set(id);
//	}
//
//	void _SystemTextures::set(std::string s) {
//		texture.Set(s);
//	}
	void _SystemTextures::set(eTexList e) {
		texture.Set(e);
	}

//	GLuint& _SystemTextures::get(eTexList e)	{
//		return texture.Get(e);
//	}

	Texture& _SystemTextures::get()	{
		return texture;
	}

} /* namespace Core */




























































