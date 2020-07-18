/*
 * System.h
 *
 *  Created on: Feb 21, 2011
 *      Author: bcthund
 */

#ifndef ICONS_H_
#define ICONS_H_

#include <iostream>

#include "../core/core_functions.h"
#include "../core/shader.h"
#include "gl4_5/glcorearb.h"

namespace Core {
//	namespace GameSys {
		class _IconSys {
			private:
				Texture texture;
				VAO vao[64];
				Vector4f tempColor,
						 currentColor,
						 gridCoord[64];
				uint uiNumTextures,
					 uiRecordSize;
				std::string sFilename,
							sDir,
							sTexDir;
				float fMouseDelay,
					  fMouseDelayConst;	//Delay for repeat mouse clicks
				void start(int x, int y, float w, float h, std::string sTex, bool textOffset, Core::_Colors::_ACTIVE_COLOR eColor=Core::_Colors::COLOR_FRONT);
				void update();
				void stop();

			public:
				_IconSys();
				bool load();
				bool calc();
				void draw(uint x,	uint y,		float w,	float h,	uint id,			std::string sTex,	bool textOffset);
				void draw(uint x,	uint y,		float w,	float h,	uint id,			std::string sTex,	bool textOffset, Color fontColor);
//				void draw(int id,	std::string	sTex,		SHADER_PROGRAMS iShader);	//DRAWING FOR RELATIVE 3D
//				void draw(int id0,	int id1,	int id2,	int id3,	std::string sTex,	SHADER_PROGRAMS iShader);

				void draw(Core::GUI::Props *con, std::string sTex, uint id, uint scale);
		};

		_IconSys::_IconSys() {
			fMouseDelay=0;
			fMouseDelayConst=100;

			tempColor[0]	= 0;
			tempColor[1]	= 0;
			tempColor[2]	= 0;
			tempColor[3]	= 0;

			uiNumTextures	= 64;
			uiRecordSize	= 32;
			sFilename		= "icons.bin";
			sDir			= "./system/";
			sTexDir			= "./texture/icons/";
		}

		bool _IconSys::load() {
			try {
				//            .................................................................Done
				std::cout << "Load IconSys.....................................................";
				MemBlock memBlock;
				std::string theImage;
				texture.Begin(uiNumTextures);

				readFile((sDir+sFilename), memBlock);

				for (int d=0; d<memBlock.size; d+=uiRecordSize) {
					int theId=0;
					for (int i=0; i<4; i++) theId+=(unsigned char)memBlock.buffer[i+d];

					theImage = "";
					for (int i=4; i<32; i++)
						if (memBlock.buffer[i+d]!=0) theImage+=(unsigned char)memBlock.buffer[i+d];
						else break;

					texture.Load(sTexDir, theImage, theId, false, GL_NEAREST);
				}

				std::cout << "Done" << std::endl;
				return true;
			}
			catch(...) {
				std::cout << "Failed" << std::endl;
				return false;
			}
		}

		bool _IconSys::calc() {
			try {
				/* Icon grid ID and coordinate calculation chart
				 *
				 *         0.000  0.125  0.250  0.375  0.500  0.625  0.750  0.875  1.000
				 *  0.000    |------|------|------|------|------|------|------|------|
				 *           |  00  |  01  |  02  |  03  |  04  |  05  |  06  |  07  |
				 *  0.125    |------|------|------|------|------|------|------|------|
				 *           |  08  |  09  |  10  |  11  |  12  |  13  |  14  |  15  |
				 *  0.250    |------|------|------|------|------|------|------|------|
				 *           |  16  |  17  |  18  |  19  |  20  |  21  |  22  |  23  |
				 *  0.375    |------|------|------|------|------|------|------|------|
				 *           |  24  |  25  |  26  |  27  |  28  |  29  |  30  |  31  |
				 *  0.500    |------|------|------|------|------|------|------|------|
				 *           |  32  |  33  |  34  |  35  |  36  |  37  |  38  |  39  |
				 *  0.625    |------|------|------|------|------|------|------|------|
				 *           |  40  |  41  |  42  |  43  |  44  |  45  |  46  |  47  |
				 *  0.750    |------|------|------|------|------|------|------|------|
				 *           |  48  |  49  |  50  |  51  |  52  |  53  |  54  |  55  |
				 *  0.875    |------|------|------|------|------|------|------|------|
				 *           |  56  |  57  |  58  |  59  |  60  |  61  |  62  |  63  |
				 *  1.000    |------|------|------|------|------|------|------|------|
				 */

				//            .................................................................Done
				std::cout << "Calc IconSys.....................................................";

				float iy1=0.000f,
					  iy2=0.125f;
				for(int i=0;i<64;i++) {
					gridCoord[i][0] = 0.000f;
					gridCoord[i][1] = iy1;
					gridCoord[i][2] = 0.125f;
					gridCoord[i][3] = iy2;

					i++;
					gridCoord[i][0] = 0.125f;
					gridCoord[i][1] = iy1;
					gridCoord[i][2] = 0.250f;
					gridCoord[i][3] = iy2;

					i++;
					gridCoord[i][0] = 0.250f;
					gridCoord[i][1] = iy1;
					gridCoord[i][2] = 0.375f;
					gridCoord[i][3] = iy2;

					i++;
					gridCoord[i][0] = 0.375f;
					gridCoord[i][1] = iy1;
					gridCoord[i][2] = 0.500f;
					gridCoord[i][3] = iy2;

					i++;
					gridCoord[i][0] = 0.500f;
					gridCoord[i][1] = iy1;
					gridCoord[i][2] = 0.625f;
					gridCoord[i][3] = iy2;

					i++;
					gridCoord[i][0] = 0.625f;
					gridCoord[i][1] = iy1;
					gridCoord[i][2] = 0.750f;
					gridCoord[i][3] = iy2;

					i++;
					gridCoord[i][0] = 0.750f;
					gridCoord[i][1] = iy1;
					gridCoord[i][2] = 0.875f;
					gridCoord[i][3] = iy2;

					i++;
					gridCoord[i][0] = 0.875f;
					gridCoord[i][1] = iy1;
					gridCoord[i][2] = 1.000f;
					gridCoord[i][3] = iy2;

					iy1+=0.125f;
					iy2+=0.125f;
				}

				/*
				 * Prints out the set of calculated icon coordinates
				 * For debugging
				 */
				//for(int i=0;i<64;i++) {
				//	cout << "[" << i << "] = (" << gridCoord[i][0] << "," << gridCoord[i][1] << ") - (" << gridCoord[i][2] << "," << gridCoord[i][3] << ")" << endl;
				//}
				//cout << "Calculating Texture Coords" << endl;
				for (int i=0; i<64; i++) {

					//Standard font quad, CCW:CAB-BDC
					// FIXME: Use a normalized quad instead of 64x64
					float iHalf_W = (64/2);
					float iHalf_H = (64/2);
					Data3f vVerts[] = { {-iHalf_W, -iHalf_H, 0},
										  { iHalf_W,  iHalf_H, 0},
										  {-iHalf_W,  iHalf_H, 0},
										  {-iHalf_W, -iHalf_H, 0},
										  { iHalf_W, -iHalf_H, 0},
										  { iHalf_W,  iHalf_H, 0 }};

					Data2f vTexture[11];
					vTexture[0][0] = gridCoord[i][0];
					vTexture[0][1] = gridCoord[i][3];
					vTexture[1][0] = gridCoord[i][2];
					vTexture[1][1] = gridCoord[i][1];
					vTexture[2][0] = gridCoord[i][0];
					vTexture[2][1] = gridCoord[i][1];
					vTexture[3][0] = gridCoord[i][0];
					vTexture[3][1] = gridCoord[i][3];
					vTexture[4][0] = gridCoord[i][2];
					vTexture[4][1] = gridCoord[i][3];
					vTexture[5][0] = gridCoord[i][2];
					vTexture[5][1] = gridCoord[i][1];

					vao[i].Begin(GL_TRIANGLES, 6, 6, 1);
					vao[i].CopyData(GLA_VERTEX, vVerts);
					vao[i].CopyData(GLA_TEXTURE, vTexture, 0);
					vao[i].End();
				}
				std::cout << "Done" << std::endl;
				return true;
			}
			catch(...) {
				std::cout << "Failed" << std::endl;
				return false;
			}
		}

		void _IconSys::start(int x, int y, float w, float h, std::string sTex, bool textOffset, Core::_Colors::_ACTIVE_COLOR eColor) {
			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			glCullFace(false);
			matrix->SetProjection(matrix->MM_ORTHO);
			shader->use(GLS_ICON);

			glDisable(GL_DEPTH_TEST);
			matrix->Push();

			if (textOffset) matrix->Translate( (Core::gameVars->font.vSize[0]*x)-Core::gameVars->screen.half.x+(w/2), (-Core::gameVars->font.vSize[1]*y)+Core::gameVars->screen.half.y-(h/2), 0.0f );
			else matrix->Translate( x+Core::gameVars->screen.origin[0]+(w/2), -y+Core::gameVars->screen.origin[1]-(h/2), 0.0f );

			matrix->Scale(w/64,h/64,1);

			glActiveTexture(0);
			texture.Set(sTex);

			colors.SetActive(eColor);
		}

		void _IconSys::update() {
			matrix->SetTransform();
			shader->getUniform(GLS_ICON);
		}

		void _IconSys::stop() {
			matrix->Pop();
			matrix->SetProjection(matrix->MM_PERSPECTIVE);
			glEnable(GL_DEPTH_TEST);
		}

		/*
		 * textOffset flag tells the start() function id we are using
		 * the position values from the text system.
		 */
//		void _IconSys::draw(int id0, int id1, int id2, int id3, std::string sTex, SHADER_PROGRAMS iShader) {
//			//w=w/64;
//			//h=h/64;
//
//			Color vColor = { 1.0, 1.0, 1.0, 1.0 };
//			colors.PushFront(vColor);
//
//			//glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
//			//matrix->SetProjection(MM_ORTHO);
//			shader->use(iShader);
//		//	glDisable(GL_DEPTH_TEST);
//			glEnable(GL_POLYGON_OFFSET_FILL);
//
//			//matrix->Push();
//			//matrix->Translate( float(x), float(y), float(z) );
//
//			//matrix->Scale(w,h,1);
//
//			texture.Set(sTex);
//			//matrix->SetTransform();
//			//shader->getUniform(*gameVars, GLS_FONT);
//			glPolygonOffset(1.0f, 4.0f);
//			vao[id0].Draw();
//
//			glPolygonOffset(1.0f, 3.0f);
//			vao[id1].Draw();
//
//			glPolygonOffset(1.0f, 2.0f);
//			vao[id2].Draw();
//
//			glPolygonOffset(1.0f, 1.0f);
//			vao[id3].Draw();
////			for (int i=0;i<4;i++) Core::gameVars->font.vColor[i]=tempColor[i];
//
//			colors.PopFront();
//
//			//matrix->Pop();
//			//matrix->SetProjection(MM_PERSPECTIVE);
//			glDisable(GL_POLYGON_OFFSET_FILL);
//		//	glEnable(GL_DEPTH_TEST);
//		}

		/*
		 * Primary draw routine, all others lead here
		 */
		void _IconSys::draw(uint x, uint y, float w, float h, uint id, std::string sTex, bool textOffset, Color fontColor) {
			colors.PushFront(fontColor);
			draw(x, y, w, h, id, sTex, textOffset);
			colors.PopFront();
		}

		void _IconSys::draw(uint x, uint y, float w, float h, uint id, std::string sTex, bool textOffset) {
			start(x, y, w, h, sTex, textOffset);
			update();
			vao[id].Draw();
			stop();

		}

		/** ******************************************************************************************************************************
		 *
		 * @param con
		 * @param sTex
		 * @param id
		 * @param scale
		 * ****************************************************************************************************************************** */
		void _IconSys::draw(Core::GUI::Props *con, std::string sTex, uint id, uint scale) {
			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			glCullFace(false);
			matrix->SetProjection(matrix->MM_ORTHO);
			shader->use(GLS_ICON);

			glDisable(GL_DEPTH_TEST);
			matrix->Push();
				matrix->Translate( con->pos.x, con->pos.y, 0.0f );
				matrix->Scale(((con->size.x-(con->vPadding.left+con->vPadding.right))/64), ((con->size.y-(con->vPadding.top+con->vPadding.bottom))/64), 1);	// FIXME: Make VAO unit normal, get rid of "/64"

				glActiveTexture(0);
				texture.Set(sTex);
				colors.SetActive(Core::colors.COLOR_FRONT);
				matrix->SetTransform();
				shader->getUniform(GLS_ICON);
				vao[id].Draw();

			matrix->Pop();
			matrix->SetProjection(matrix->MM_PERSPECTIVE);
			glEnable(GL_DEPTH_TEST);
		}
//	}
}
#endif /* ICONS_H_ */




































































