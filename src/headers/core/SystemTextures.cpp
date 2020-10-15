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

//			for (int d=0; d<memBlock.size; d+=uiRecordSize) {
//				int iData0 = (unsigned char)memBlock.buffer[0+d];
//				e_TEXTURE_FILTER iData1 = (e_TEXTURE_FILTER)memBlock.buffer[1+d];
//				e_TEXTURE_CLAMP iData2 = (e_TEXTURE_CLAMP)memBlock.buffer[2+d];
//				int iData3 = (unsigned char)memBlock.buffer[3+d];
//
//				if (iData0 != iIDVerify) throw  std::runtime_error("Texture ID Mismatch [" + std::to_string(iData0) + "!=" + std::to_string(iIDVerify) + "] @ SystemTextures.cpp Line 42");
//
//				theImage = "";
//				for (int i=4; i<32; i++)
//					if (memBlock.buffer[i+d]!=0) theImage+=(unsigned char)memBlock.buffer[i+d];
//					else break;
//
//				Core::debug.log("["+std::to_string(iData0)+"/"+std::to_string(iIDVerify)+"] "+theImage+"\n", Core::debug().YELLOW);
//
//				texture.Load(sTexDir, theImage, iData0, true, iData1, iData2);
//				iIDVerify++;
//			}

			// TESTING: Find number of 3D textures
			int numLevels[5] = { 0 };
			for (int d=0; d<memBlock.size; d+=uiRecordSize) {
				int iData3 = (unsigned char)memBlock.buffer[3+d];
				if(iData3==1) numLevels[0]++;
				if(iData3==2) numLevels[1]++;
				if(iData3==3) numLevels[2]++;
				if(iData3==4) numLevels[3]++;
				if(iData3==5) numLevels[4]++;
			}
			debug.log("Number of Levels #1 = "+std::to_string(numLevels[0])+"\n");
			debug.log("Number of Levels #2 = "+std::to_string(numLevels[1])+"\n");
			debug.log("Number of Levels #3 = "+std::to_string(numLevels[2])+"\n");
			debug.log("Number of Levels #4 = "+std::to_string(numLevels[3])+"\n");
			debug.log("Number of Levels #5 = "+std::to_string(numLevels[4])+"\n");
			if(numLevels[0]>0) texture.Init3D(TEX_3D, 512, 512, numLevels[0], 0);
			if(numLevels[1]>0) texture.Init3D(TEX_3D+1, 512, 512, numLevels[1], 0);
			if(numLevels[2]>0) texture.Init3D(TEX_3D+2, 512, 512, numLevels[2], 0);
			if(numLevels[3]>0) texture.Init3D(TEX_3D+3, 512, 512, numLevels[3], 0);
			if(numLevels[4]>0) texture.Init3D(TEX_3D+4, 512, 512, numLevels[4], 0);

			// TESTING: Temprary depth value for 3D texture
			int iDepth[5] = { 0 };

			for (int d=0; d<memBlock.size; d+=uiRecordSize) {
				// Texture ID
				int iData0 = (unsigned char)memBlock.buffer[0+d];

				if(iData0!=TEX_NULL) {
					// Filter type (only applies to min filter)
					e_TEXTURE_FILTER iData1 = (e_TEXTURE_FILTER)memBlock.buffer[1+d];

					// Texture clamping type (only last value will apply to 3D textures)
					e_TEXTURE_CLAMP iData2 = (e_TEXTURE_CLAMP)memBlock.buffer[2+d];

					// TESTING: Is a 3D texture (This texture should be added to the 3D list)
					int iData3 = (unsigned char)memBlock.buffer[3+d];

					// Check that ID matches Enumeration
					if(iData0<TEX_NULL) {
						if (iData0 != iIDVerify) throw  std::runtime_error("Texture ID Mismatch [" + std::to_string(iData0) + "!=" + std::to_string(iIDVerify) + "] @ SystemTextures.cpp Line 42");
					}

					theImage = "";
					for (int i=4; i<32; i++)
						if (memBlock.buffer[i+d]!=0) theImage+=(unsigned char)memBlock.buffer[i+d];
						else break;

					Core::debug.log("3D: ["+std::to_string(iData0)+"/"+std::to_string(iIDVerify)+"] "+theImage+"\n", Core::debug().YELLOW);

					// Load 2D or 3D texture according to iData3 value
					if(iData3>0) {
						texture.Load3D(TEX_3D+iData3-1, sTexDir, theImage, iDepth[iData3-1], true, iData1, iData2);
						iDepth[iData3-1]++;
					}
					else texture.Load(sTexDir, theImage, iData0, true, iData1, iData2);
	//				if(iData3==1) texture.Load3D(TEX_3D, sTexDir, theImage, iData0, true, iData1, iData2);
	//				else texture.Load(sTexDir, theImage, iData0, true, iData1, iData2);

					iIDVerify++;
				}
			}


			// TODO: Add a header to bin file to describe 2D/3D settings
//			int numLevels = memBlock.size/uiRecordSize;
//			debug.log("Number of Levels = "+std::to_string(numLevels)+"\n");
//			//texture.Init3D(TEX_3D, 512, 512, numLevels, 0);
//			//texture.Init3D(TEX_3D, 512, 512, 6, 0);
//			texture.Init3D(TEX_3D, 512, 512, numLevels, 0);
//			for (int d=0; d<(uiRecordSize*6); d+=uiRecordSize) {
//				int iData0 = (unsigned char)memBlock.buffer[0+d];
//				e_TEXTURE_FILTER iData1 = (e_TEXTURE_FILTER)memBlock.buffer[1+d];
//				e_TEXTURE_CLAMP iData2 = (e_TEXTURE_CLAMP)memBlock.buffer[2+d];
//				int iData3 = (unsigned char)memBlock.buffer[3+d];
//
////				if (iData0 != iIDVerify) throw  std::runtime_error("Texture ID Mismatch [" + std::to_string(iData0) + "!=" + std::to_string(iIDVerify) + "] @ SystemTextures.cpp Line 42");
//
//				theImage = "";
//				for (int i=4; i<32; i++)
//					if (memBlock.buffer[i+d]!=0) theImage+=(unsigned char)memBlock.buffer[i+d];
//					else break;
//
//				Core::debug.log("3D: ["+std::to_string(iData0)+"] "+theImage+"\n", Core::debug().YELLOW);
//
//				texture.Load3D(TEX_3D, sTexDir, theImage, iData0, true, iData1, iData2);
////				iIDVerify++;
//			}

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
	void _SystemTextures::set(int e) {
		// TODO: Read texture settings to determine 2D or 3D
		if(e>=TEX_3D) {
			texture.Set3D(e);
		}
		else texture.Set(e);
	}

//	GLuint& _SystemTextures::get(eTexList e)	{
//		return texture.Get(e);
//	}

	Texture& _SystemTextures::get()	{
		return texture;
	}

} /* namespace Core */




























































