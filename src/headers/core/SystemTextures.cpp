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

	// TODO:
	bool _SystemTextures::load() {
//		try {
			Core::debug.log("Load Global Textures {\n");
			Core::debug.logIncreaseIndent();
			MemBlock memBlock;
			std::string theImage;
			texture.Begin(uiNumTextures);

			readFile((sDir+sFilename), memBlock);

			// System textures must follow ID order
			int iIDVerify = 0;

			for (int d=0; d<memBlock.size; d+=uiRecordSize) {
//				int theId=0;
//				int iData0=0;

//				for (int i=0; i<4; i++) theId+=(unsigned char)memBlock.buffer[i+d];
//				for (int i=0; i<4; i++) iData0+=(unsigned char)memBlock.buffer[i+d];

				int iData0 = (unsigned char)memBlock.buffer[0+d];
//				e_TEXTURE_FILTER iData1 = (unsigned char)memBlock.buffer[1];
				e_TEXTURE_FILTER iData1 = (e_TEXTURE_FILTER)memBlock.buffer[1+d];
//				e_TEXTURE_FILTER iData1 = TEXTURE_FILTER_LINEAR;
//				e_TEXTURE_CLAMP iData2 = (unsigned char)memBlock.buffer[2];
				e_TEXTURE_CLAMP iData2 = (e_TEXTURE_CLAMP)memBlock.buffer[2+d];
//				e_TEXTURE_CLAMP iData2 = TEXTURE_CLAMP_REPEAT;
				int iData3 = (unsigned char)memBlock.buffer[3+d];
//				int iData3 = 0;

				if (iData0 != iIDVerify) throw  std::runtime_error("Texture ID Mismatch [" + std::to_string(iData0) + "!=" + std::to_string(iIDVerify) + "] @ SystemTextures.cpp Line 42");

				theImage = "";
				for (int i=4; i<32; i++)
					if (memBlock.buffer[i+d]!=0) theImage+=(unsigned char)memBlock.buffer[i+d];
					else break;

				Core::debug.log("["+std::to_string(iData0)+"/"+std::to_string(iIDVerify)+"] "+theImage+"\n", Core::debug().YELLOW);

				texture.Load(sTexDir, theImage, iData0, true, iData1, iData2);
				iIDVerify++;
			}
			Core::debug.logDecreaseIndent();
			Core::debug.log("}\n");
//		}
//		catch(std::string &s) {
//			std::cout << "!!! ERROR !!! Internal exception: " << s << std::endl;
//			std::exit(0);
//		}
//		catch(const char * s) {
//			std::cout << "!!! ERROR !!! Internal exception: " << s << std::endl;
//			std::exit(0);
//		}
//		catch(...) {
//			std::cout << "!!! ERROR !!! Unknown Exception" << std::endl;
//			std::exit(0);
//		}
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




























































