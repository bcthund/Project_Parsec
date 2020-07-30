/*
 * SpriteSys.h
 *
 *  Created on: Jun 7, 2015
 *      Author: bcthund
 */

#ifndef SPRITESYS_H_
#define SPRITESYS_H_

#include <iostream>

#include "../core/matrix.h"
#include "../core/shader.h"
#include "../core/core_functions.h"

namespace Core {
//	namespace GameSys {
		class _SpriteSys {
			private:
//				Matrix_System * matrix;
//				Shader_System  *shader;
				Texture texture;
				VAO vao;
				Vector4f gridCoord;
				uint uiNumTextures,
					 uiRecordSize;
				std::string sFilename,
							sDir,
							sTexDir;
				void start(int x, int y, float w, float h, std::string sTex, bool textOffset, bool bNoTex, Core::_Colors::_ACTIVE_COLOR eColor=Core::_Colors::COLOR_FRONT, SHADER_PROGRAMS uiShader=GLS_FONT);
				void update(SHADER_PROGRAMS uiShader);
				void stop();
				//uint checkInput(int x, int y, float w, float h );
				//uint checkOver(int x, int y, float w, float h );
				//bool gettingInput;	//IS THIS NEEDED?

				void draw(std::string sTex, SHADER_PROGRAMS iShader);	//SPECIAL DRAWING ROUTINE, Used to draw sprites in 3D, Matrix set before call

			protected:
				friend class _GameSys;

			public:

				uint draw(uint x, uint y, float s, std::string sTex, bool textOffset);
				uint draw(uint x, uint y, float s, std::string sTex, bool textOffset, Color fontColor);

				uint draw(uint x, uint y, float w, float h, std::string sTex, bool textOffset);
				uint draw(uint x, uint y, float w, float h, std::string sTex, bool textOffset, Color fontColor);

				_SpriteSys(/*Matrix_System &m, Shader_System &s*/);
				//void draw(Atmosphere &a, uint x, uint y, uint z, float w, float h, GLuint uiShader=GLS_FONT); // Special drawing routine
				void draw(uint x, uint y, float w, float h, GLuint uiTex, SHADER_PROGRAMS uiShader);	// Special drawing routine, specified texture
				void draw(uint x, uint y, float w, float h, Color fontColor, GLuint uiTex, SHADER_PROGRAMS uiShader);	// Special drawing routine, specified texture
				//void draw(Atmosphere &a, uint x, uint y, float w, float h, Vector4f fontColor, GLuint uiTex, GLuint uiShader);	// Special drawing routine, specified texture

				void draw(Core::GUI::Props *con, std::string texture);

				bool load();
				bool calc();
		};

		_SpriteSys::_SpriteSys(/*Matrix_System &m, Shader_System &s*/){
//			matrix = &m;
//			shader = &s;

//			tempColor[0]	= 0;
//			tempColor[1]	= 0;
//			tempColor[2]	= 0;
//			tempColor[3]	= 0;

			uiNumTextures	= 64;
			uiRecordSize	= 32;
			sFilename		= "sprites.bin";
			sDir			= "./system/";
			sTexDir		= "./texture/sprite/";
		}

		bool _SpriteSys::load() {
			try {
				//            .................................................................Done
				std::cout << "Load SpriteSys...................................................";
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

					//if (Core::gameVars->debug.load) cout << theId << ".";
					texture.Load(sTexDir, theImage, theId);
				}
				//if (Core::gameVars->debug.load) cout << "..";
				std::cout << "Done" << std::endl;
				return true;
			}
			catch(...) {
				std::cout << "Failed" << std::endl;
				return false;
			}
		}

		bool _SpriteSys::calc() {
			try {
				//            .................................................................Done
				std::cout << "Calc SpriteSys...................................................";
				//for (int i=0; i<64; i++) {

					//Standard font quad, CCW:CAB-BDC
//					float iHalf_W = (64/2);
//					float iHalf_H = (64/2);

					float iHalf_W = 0.5f;
					float iHalf_H = 0.5f;

					Data3f vVerts[] = { {-iHalf_W, -iHalf_H, 0},
										  { iHalf_W,  iHalf_H, 0},
										  {-iHalf_W,  iHalf_H, 0},

										  {-iHalf_W, -iHalf_H, 0},
										  { iHalf_W, -iHalf_H, 0},
										  { iHalf_W,  iHalf_H, 0 }};

					gridCoord[0] = 0.000f;
					gridCoord[1] = 0.000f;
					gridCoord[2] = 1.000f;
					gridCoord[3] = 1.000f;

					Data2f vTexture[6] = { { gridCoord[0], gridCoord[3] },
										   { gridCoord[2], gridCoord[1] },
										   { gridCoord[0], gridCoord[1] },
										   { gridCoord[0], gridCoord[3] },
										   { gridCoord[2], gridCoord[3] },
										   { gridCoord[2], gridCoord[1] } };

					vao.Begin(GL_TRIANGLES, 6, 6, 1);
					vao.CopyData(GLA_VERTEX, vVerts);
					vao.CopyData(GLA_TEXTURE, vTexture, 0);
					vao.End();
				//}
				std::cout << "Done" << std::endl;
				return true;
			}
			catch(...) {
				std::cout << "Failed" << std::endl;
				return false;
			}
		}

		void _SpriteSys::start(int x, int y, float w, float h, std::string sTex, bool textOffset, bool bNoTex=false, Core::_Colors::_ACTIVE_COLOR eColor, SHADER_PROGRAMS uiShader) {
			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			matrix->SetProjection(matrix->MM_ORTHO);
			shader->use(uiShader);

			glDisable(GL_DEPTH_TEST);
			matrix->Push();

			if (textOffset) {
				matrix->Translate( (Core::gameVars->font.vSize[0]*x)+Core::gameVars->font.screenCoords[0]+(w*32), (-Core::gameVars->font.vSize[1]*y)+Core::gameVars->font.screenCoords[1]-(h*32), 0.0 );
			}
			else {
				matrix->Translate( x+Core::gameVars->screen.origin[0]+(w*32), -y+Core::gameVars->screen.origin[1]-(h*32), 0.0 );
			}

			matrix->Scale(w,h,1);

			colors.SetActive(eColor);

			// Do not set texture if bNoSet true, texture is set elsewhere
			if (!bNoTex) texture.Set(sTex);
		}

		void _SpriteSys::update(SHADER_PROGRAMS uiShader=GLS_FONT) {
			matrix->SetTransform();
			shader->getUniform(uiShader);
		}

		void _SpriteSys::stop() {
			matrix->Pop();
			matrix->SetProjection(matrix->MM_PERSPECTIVE);
			glEnable(GL_DEPTH_TEST);
		}

		/*
		 * textOffset flag tells the start() function id we are using
		 * the position values from the text system.
		 */
		void _SpriteSys::draw(std::string sTex, SHADER_PROGRAMS iShader) {
			glDisable(GL_CULL_FACE);
			shader->use(iShader);
			texture.Set(sTex);
			vao.Draw();
			glEnable(GL_CULL_FACE);
		}

		uint _SpriteSys::draw(uint x, uint y, float s, std::string sTex, bool textOffset) {
			Vector4f fontColor = {1.0, 1.0, 1.0, 1.0};
			return draw(x, y, s*64, s*64, sTex, textOffset);
		}

//		uint _SpriteSys::draw(uint x, uint y, float w, float h, std::string sTex, bool textOffset) {
//			Vector4f fontColor = {1.0, 1.0, 1.0, 1.0};
//			return draw(x, y, w, h, sTex, textOffset, fontColor);
//		}

		uint _SpriteSys::draw(uint x, uint y, float s, std::string sTex, bool textOffset, Color fontColor) {
			colors.PushFront(fontColor);
			return draw(x, y, s*64, s*64, sTex, textOffset);
			colors.PopFront();
		}

		/*
		 * Special drawing routine
		 *
		 * Used to draw specific textures to quads, used
		 * 	primarily for debugging but may also be used
		 * 	as the an effects overlay for the world for:
		 * 		- weather
		 * 		- blurring
		 * 		- bloom
		 * 		- underwater distortion
		 *
		 * Just to name a few options. To do this the
		 * 	shader needs to be specified because the
		 * 	shader determines how the texture will
		 * 	be modified by the fragment shader->
		 *
		 */
		void _SpriteSys::draw(uint x, uint y, float w, float h, Color fontColor, GLuint uiTex, SHADER_PROGRAMS uiShader=GLS_FONT) {
			colors.PushFront(fontColor);
			draw(x, y, w, h, uiTex, uiShader);
			colors.PopFront();
		}

		void _SpriteSys::draw(uint x, uint y, float w, float h, GLuint uiTex, SHADER_PROGRAMS uiShader=GLS_FONT) {

			// We need to disable face culling for quads that need
			//	to get flipped. This is common when working with
			//	FBOs because they are always upside down.
			glDisable(GL_CULL_FACE);

//			w=w/64;
//			h=h/64;

			start(x, y, w, h, "none", false, true, Core::_Colors::COLOR_FRONT, uiShader);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, uiTex);
			update(uiShader);

			vao.Draw();
			stop();

			glEnable(GL_CULL_FACE);
		}

		void _SpriteSys::draw(Core::GUI::Props *con, std::string sTex) {
			glDisable(GL_CULL_FACE);
			glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
			matrix->SetProjection(matrix->MM_ORTHO);
			shader->use(GLS_FONT);

			glDisable(GL_DEPTH_TEST);
			matrix->Push();

			Vector2f vPos = con->getPos();
			if(con->scroll.getEnabled()) {
				vPos.x += con->scroll.getX();
				vPos.y += con->scroll.getY();
			}
			matrix->Translate( vPos.x, vPos.y, 0.0f );
//			matrix->Translate( con->pos.x, con->pos.y, 0.0 );
//			matrix->Scale( con->size.x/64, con->size.y/64, 1);		// FIXME: Make VAO unit normal, get rid of "/64"
			matrix->Scale( con->size.x, con->size.y, 1);			// FIXME: Make VAO unit normal, get rid of "/64"

//			colors.SetActive(eColor);

			// Do not set texture if bNoSet true, texture is set elsewhere
//			if (!bNoTex) texture.Set(sTex);
//			texture.Set(sTex);


			glActiveTexture(GL_TEXTURE0);
//			glBindTexture(GL_TEXTURE_2D, uiTex);
			texture.Set(sTex);

			//update(uiShader);
			matrix->SetTransform();
			shader->getUniform(GLS_FONT);

			vao.Draw();

			// stop();
			matrix->Pop();
			matrix->SetProjection(matrix->MM_PERSPECTIVE);
			glEnable(GL_DEPTH_TEST);

			glEnable(GL_CULL_FACE);
		}

	//	void _SpriteSys::draw(Atmosphere &a, uint x, uint y, uint z, float w, float h, GLuint uiShader) {
	//		glDisable(GL_CULL_FACE);
	//
	//		w=w/64;
	//		h=h/64;
	//
	//		start(x, y, w, h, "none", Core::gameVars->color.white, false, true, uiShader);
	//		matrix->Translate(0.0, 0.0, -z);
	//
	//	//	Vector4f	fontColor	= { Core::gameVars->color.white[0], Core::gameVars->color.white[1], Core::gameVars->color.white[2], Core::gameVars->color.white[3] };
	//	//	bool		textOffset	= false;
	//	//	bool		bNoTex		= true;
	//	//	string		sTex		= "none";
	//	//	for (int i=0;i<4;i++) tempColor[i]=Core::gameVars->font.vColor[i];
	//	//	for (int i=0;i<4;i++) Core::gameVars->font.vColor[i]=fontColor[i];
	//	//	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	//	//	matrix->SetProjection(MM_ORTHO);
	//	//	shader->use(uiShader);
	//	//	glDisable(GL_DEPTH_TEST);
	//	//	matrix->Push();
	//	//	if (textOffset) {
	//	//		matrix->Translate( (Core::gameVars->font.vSize[0]*x)+Core::gameVars->font.screenCoords[0]+(w*32), (-Core::gameVars->font.vSize[1]*y)+Core::gameVars->font.screenCoords[1]-(h*32), 0.0 );
	//	//	}
	//	//	else {
	//	//		matrix->Translate( x+Core::gameVars->screen.origin[0]+(w*32), -y+Core::gameVars->screen.origin[1]-(h*32), 0.0 );
	//	//	}
	//	//	matrix->Scale(w,h,1);
	//	//	// Do not set texture if bNoSet true, texture is set elsewhere
	//	//	if (!bNoTex) texture.Set(sTex);
	//
	//		//for (int i=0;i<4;i++) tempColor[i]=Core::gameVars->font.vColor[i];
	//		//for (int i=0;i<4;i++) Core::gameVars->font.vColor[i]=Core::gameVars->color.white[i];
	//		//glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	//		//matrix->SetProjection(MM_ORTHO);
	//		//shader->use(uiShader);
	//		//glDisable(GL_DEPTH_TEST);
	//		//matrix->Push();
	//		//	matrix->Translate( x+Core::gameVars->screen.origin[0]+(w*32), -y+Core::gameVars->screen.origin[1]-(h*32), 0.0 );
	//		//	matrix->Scale(w, h, 1);
	//
	//			glActiveTexture(GL_TEXTURE0);
	//			glBindTexture(GL_TEXTURE_2D, 0);
	//			matrix->SetTransform();
	//			shader->getUniform(a, uiShader);
	//			vao.Draw();
	//		//matrix->Pop();
	//		//matrix->SetProjection(MM_PERSPECTIVE);
	//		//glEnable(GL_DEPTH_TEST);
	//		stop();
	//		glEnable(GL_CULL_FACE);
	//	}

	//	void _SpriteSys::draw(Atmosphere &a, uint x, uint y, float w, float h, Vector4f fontColor, GLuint uiTex, GLuint uiShader=GLS_FONT) {
	//
	//		// We need to disable face culling for quads that need
	//		//	to get flipped. This is common when working with
	//		//	FBOs because they are always upside down.
	//		glDisable(GL_CULL_FACE);
	//
	//		w=w/64;
	//		h=h/64;
	//
	//		start(x, y, w, h, "none", fontColor, false, true, uiShader);
	//		glActiveTexture(GL_TEXTURE0);
	//		glBindTexture(GL_TEXTURE_2D, uiTex);
	//		//update(uiShader);
	//		matrix->SetTransform();
	//		shader->getUniform(a, uiShader);
	//
	//		vao.Draw();
	//		stop();
	//
	//		glEnable(GL_CULL_FACE);
	//	}

		/*
		 * Primary draw routine, all others lead here
		 */
		uint _SpriteSys::draw(uint x, uint y, float w, float h, std::string sTex, bool textOffset, Color fontColor) {
			colors.PushFront(fontColor);
			uint r = draw(x, y, w, h, sTex, textOffset);
			colors.PopFront();
			return r;
		}

		uint _SpriteSys::draw(uint x, uint y, float w, float h, std::string sTex, bool textOffset) {
			start(x, y, w, h, sTex, textOffset);
			update();
			vao.Draw();
			stop();

			return Core::mouse->MOUSE_NONE;
		}
}
#endif /* SPRITESYS_H_ */
