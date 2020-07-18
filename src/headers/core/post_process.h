/*
 * post_process.h
 *
 *  Created on: Jan 28, 2018
 *      Author: bcthund
 */

#ifndef SRC_HEADERS_CORE_POST_PROCESS_H_
#define SRC_HEADERS_CORE_POST_PROCESS_H_

#include <iostream>

#include "gl4_5/glcorearb.h"
#include "matrix.h"
#include "Colors.h"

namespace Core {
	class PostProcess {
		private:
//			Matrix_System * matrix;
//			Shader_System * shader;
			//void Render();			// Draw quad to screen
			void Render();				// Draw quad to screen
			void Render(SHADER_PROGRAMS uiShader);				// Draw quad to screen
			void Render2(SHADER_PROGRAMS uiShader, Vector3f vTranslate=Vector3f(), float fScale=0.25f);				// Draw quad to screen
			void RenderQuad(int x, int y, int w, int h, SHADER_PROGRAMS uiShader=Core::GLS_FONT, bool bCenter=false, bool bClear=false);
			//void Render(std::string name, uint uiShader, uint tex, Atmosphere &a);
			VAO vao;					// Holds quad
			GLuint texResult;			// The result of the most recent post processing shader
			//GLuint * texResultArr;		//
			bool bResult;				// At least one result exists
			//Atmosphere * a;				// Reference to the atmosphere
			std::string name;				// The name for the primary render
			Vector2ui vuiScreenSize;

		protected:

		public:
			PostProcess(/*Matrix_System &m, Shader_System &s*/);
			~PostProcess();
			bool bEnable;
			//_FBO fbo;
			// TODO: Need new atmosphere
			//void init(Atmosphere &a);
			void init(int iW, int iH, uint uiMultisamples);
			void RenderLayer(std::string name)					{ this->name = name; Core::fbo.BindFbo(name);	}
			GLuint EndRenderLayer();
			GLuint Draw											(std::string name);
			GLuint ApplyContrast								(GLuint tex, float fContrast);
			GLuint ApplyUnderwater								(GLuint tex);
			GLuint ApplyBrightness								(GLuint tex, Core::Vector3f vBrightness);
			GLuint ApplyBrightnessFilter						(GLuint tex, Core::Vector3f vFactor, float fMax);
			GLuint ApplyRadialBlur								(GLuint tex);
			GLuint ApplyHBlur									(GLuint tex);
			GLuint ApplyVBlur									(GLuint tex);
			GLuint ApplyGaussian								(GLuint tex);
			GLuint ApplyRayBlur									(GLuint tex);
			GLuint ApplyBloom									(GLuint tex);
			GLuint ApplyDepthOfField							(GLuint tex, std::string sDepthName);
			GLuint ApplyVinette									(GLuint tex);
			GLuint ApplyLensFlare								(GLuint tex);		// Need to provide occlusion query data for best results, but make it optional
			GLuint ApplyCartoon									(GLuint tex);
			GLuint ApplyPixelate								(GLuint tex);
			GLuint ApplyCombine									(GLuint tex0, GLuint tex1, float fIntensity);
			//GLuint ResolveFBO									(std::string name);

			GLuint ApplyContrast(float fContrast)								{ if(bResult) return ApplyContrast(texResult, fContrast);				else return 0; }
			GLuint ApplyUnderwater()											{ if(bResult) return ApplyUnderwater(texResult);						else return 0; }
			GLuint ApplyBrightness(Core::Vector3f vBrightness)					{ if(bResult) return ApplyBrightness(texResult, vBrightness);			else return 0; }
			GLuint ApplyBrightnessFilter(Core::Vector3f vFactor, float fMax)	{ if(bResult) return ApplyBrightnessFilter(texResult, vFactor, fMax);	else return 0; }
			GLuint ApplyRadialBlur()											{ if(bResult) return ApplyRadialBlur(texResult);						else return 0; }
			GLuint ApplyHBlur()													{ if(bResult) return ApplyHBlur(texResult);								else return 0; }
			GLuint ApplyVBlur()													{ if(bResult) return ApplyVBlur(texResult);								else return 0; }
			GLuint ApplyGaussian()												{ if(bResult) return ApplyGaussian(texResult);							else return 0; }
			GLuint ApplyRayBlur()												{ if(bResult) return ApplyRayBlur(texResult);							else return 0; }
			GLuint ApplyBloom()													{ if(bResult) return ApplyBloom(texResult);								else return 0; }
			GLuint ApplyDepthOfField(std::string sDepthName)					{ if(bResult) return ApplyDepthOfField(texResult, name);				else return 0; }
			GLuint ApplyVinette()												{ if(bResult) return ApplyVinette(texResult);							else return 0; }
			//GLuint ApplyLensFlare()											{ if(bResult) return ApplyLensFlare(texResult);							else return 0; }
			GLuint ApplyLensFlare();
			GLuint ApplyCartoon()												{ if(bResult) return ApplyCartoon(texResult);							else return 0; }
			GLuint ApplyPixelate()												{ if(bResult) return ApplyPixelate(texResult);							else return 0; }
			GLuint ApplyCombine(GLuint tex, float fIntensity)					{ if(bResult) return ApplyCombine(tex, texResult, fIntensity);			else return 0; }

			void RenderToWindow(GLuint tex, Vector3f vTranslate, float fScale=0.25f) {	glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, tex);   		Render2(GLS_FONT, vTranslate, fScale);	}
			void RenderToScreen(GLuint tex) 										{	glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, tex);		Render(GLS_FONT);	}
			void RenderToScreen()													{	glActiveTexture(GL_TEXTURE0); glBindTexture(GL_TEXTURE_2D, texResult);	Render(GLS_FONT);	}
			//void End()																{	RenderToScreen();	}
	};
	//} *postProcess = new PostProcess;

	PostProcess::PostProcess(/*Matrix_System &m, Shader_System &s*/) {
		//shader = nullptr;
		//matrix = &m;
		//shader = &s;
		//a = nullptr;
		texResult = 0;
		bResult = false;
		bEnable = true;
		//texResultArr = new GLuint[100];
	}

	PostProcess::~PostProcess() {
		//       .................................................................Done
		std::cout << "Destroy Post Processing..........................................";
		std::cout << "Not Implemented" << std::endl;
	}

	// Need the screen dimensions
	//void PostProcess::init(Atmosphere &a) {
	void PostProcess::init(int iW, int iH, uint uiMultisamples) {
		//       .................................................................Done
		std::cout << "Init Post Processing.............................................";
		//this->a = &a;

		vuiScreenSize = Vector2ui(iW, iH);

		Data3f vVerts[] = { {-1.0, -1.0, 0},
							{ 1.0,  1.0, 0},
							{-1.0,  1.0, 0},

							{-1.0, -1.0, 0},
							{ 1.0, -1.0, 0},
							{ 1.0,  1.0, 0 } };

	//	Vector2f vTexture[] = { { 0, 1 },
	//							{ 1, 0 },
	//							{ 0, 0 },
	//							{ 0, 1 },
	//							{ 1, 1 },
	//							{ 1, 0 } };

		Data2f vTexture[] = { { 0, 0 },
							  { 1, 1 },
							  { 0, 1 },
							  { 0, 0 },
							  { 1, 0 },
							  { 1, 1 } };

		vao.Begin(GL_TRIANGLES, 6, 6, 1);
		vao.CopyData(GLA_VERTEX, vVerts);
		vao.CopyData(GLA_TEXTURE, vTexture, 0);
		vao.End();

		int w = iW,
			h = iH;

		std::string name = "Multisample";
		Core::fbo.CreateFbo(name, w, h, uiMultisamples);
		Core::fbo.AddColorAttachment(name);
		Core::fbo.AddDepthBuffer(name);
		Core::fbo.FinishFbo(name);

		name = "Resolve";
		Core::fbo.CreateFbo(name, w, h);
		Core::fbo.AddColorAttachment(name);
		Core::fbo.AddDepthBuffer(name);
		Core::fbo.FinishFbo(name);

		name = "Layer0";
		Core::fbo.CreateFbo(name, w, h);
		Core::fbo.AddColorAttachment(name, 0);
		Core::fbo.AddDepthTexture(name);
		Core::fbo.FinishFbo(name);

		name = "Layer1";
		Core::fbo.CreateFbo(name, w, h);
		Core::fbo.AddColorAttachment(name, 0);
		Core::fbo.AddDepthTexture(name);
		Core::fbo.FinishFbo(name);

		name = "Layer2";
		Core::fbo.CreateFbo(name, w, h);
		Core::fbo.AddColorAttachment(name, 0);
		Core::fbo.AddDepthBuffer(name);
		Core::fbo.FinishFbo(name);

		name = "Layer3";
		Core::fbo.CreateFbo(name, w, h);
		Core::fbo.AddColorAttachment(name, 0);
		Core::fbo.AddDepthBuffer(name);
		Core::fbo.FinishFbo(name);

		name = "Layer4";
		Core::fbo.CreateFbo(name, w, h);
		Core::fbo.AddColorAttachment(name, 0);
		Core::fbo.AddDepthBuffer(name);
		Core::fbo.FinishFbo(name);

		name = "Layer5";
		Core::fbo.CreateFbo(name, w, h);
		Core::fbo.AddColorAttachment(name, 0);
		Core::fbo.AddDepthBuffer(name);
		Core::fbo.FinishFbo(name);

		name = "Layer6";
		Core::fbo.CreateFbo(name, w, h);
		Core::fbo.AddColorAttachment(name, 0);
		Core::fbo.AddDepthBuffer(name);
		Core::fbo.FinishFbo(name);

		name = "Layer7";
		Core::fbo.CreateFbo(name, w, h);
		Core::fbo.AddColorAttachment(name, 0);
		Core::fbo.AddDepthBuffer(name);
		Core::fbo.FinishFbo(name);

		name = "Layer8";
		Core::fbo.CreateFbo(name, w, h);
		Core::fbo.AddColorAttachment(name, 0);
		Core::fbo.AddDepthBuffer(name);
		Core::fbo.FinishFbo(name);

		name = "Layer9";
		Core::fbo.CreateFbo(name, w, h);
		Core::fbo.AddColorAttachment(name, 0);
		Core::fbo.AddDepthBuffer(name);
		Core::fbo.FinishFbo(name);

		Core::fbo.CreateFbo("ApplyContrast", w, h);
		Core::fbo.AddColorAttachment("ApplyContrast", 0);
		Core::fbo.AddDepthBuffer("ApplyContrast");
		Core::fbo.FinishFbo("ApplyContrast");

		Core::fbo.CreateFbo("ApplyUnderwater", w, h);
		Core::fbo.AddColorAttachment("ApplyUnderwater", 0);
		Core::fbo.AddDepthBuffer("ApplyUnderwater");
		Core::fbo.FinishFbo("ApplyUnderwater");

		Core::fbo.CreateFbo("ApplyBrightness", w, h);
		Core::fbo.AddColorAttachment("ApplyBrightness", 0);
		Core::fbo.AddDepthBuffer("ApplyBrightness");
		Core::fbo.FinishFbo("ApplyBrightness");

		Core::fbo.CreateFbo("ApplyBrightnessFilter", w, h);
		Core::fbo.AddColorAttachment("ApplyBrightnessFilter", 0);
		Core::fbo.AddDepthBuffer("ApplyBrightnessFilter");
		Core::fbo.FinishFbo("ApplyBrightnessFilter");

		Core::fbo.CreateFbo("ApplyRadialBlur", w/2, h/2);
		Core::fbo.AddColorAttachment("ApplyRadialBlur", 0);
		Core::fbo.AddDepthBuffer("ApplyRadialBlur");
		Core::fbo.FinishFbo("ApplyRadialBlur");

		Core::fbo.CreateFbo("ApplyHBlur", w/2, h/2);
		Core::fbo.AddColorAttachment("ApplyHBlur", 0);
		Core::fbo.AddDepthBuffer("ApplyHBlur");
		Core::fbo.FinishFbo("ApplyHBlur");

		Core::fbo.CreateFbo("ApplyVBlur", w/2, h/2);
		Core::fbo.AddColorAttachment("ApplyVBlur", 0);
		Core::fbo.AddDepthBuffer("ApplyVBlur");
		Core::fbo.FinishFbo("ApplyVBlur");

		Core::fbo.CreateFbo("ApplyCombine", w, h);
		Core::fbo.AddColorAttachment("ApplyCombine", 0);
		Core::fbo.AddDepthBuffer("ApplyCombine");
		Core::fbo.FinishFbo("ApplyCombine");

		// TODO: Lens flare is not post processing anymore
		Core::fbo.CreateFbo("ApplyLensFlare", w, h);
		Core::fbo.AddColorAttachment("ApplyLensFlare", 0);
		Core::fbo.AddDepthBuffer("ApplyLensFlare");
		Core::fbo.FinishFbo("ApplyLensFlare");
		//occlusion.CreateQuery("ApplyLensFlare", GL_SAMPLES_PASSED);

		Core::fbo.CreateFbo("ApplyDepthOfField", w, h);
		Core::fbo.AddColorAttachment("ApplyDepthOfField", 0);
		Core::fbo.AddDepthBuffer("ApplyDepthOfField");
		Core::fbo.FinishFbo("ApplyDepthOfField");

		Core::fbo.CreateFbo("ApplyCartoon", w, h);
		Core::fbo.AddColorAttachment("ApplyCartoon", 0);
		Core::fbo.AddDepthBuffer("ApplyCartoon");
		Core::fbo.FinishFbo("ApplyCartoon");

		std::cout << "Done" << std::endl;
	}

	GLuint PostProcess::EndRenderLayer() {
		Core::fbo.UnbindFbo();
		if (!bResult) bResult=true;
		if(Core::fbo.HasMultisample(name)) {
			Core::fbo.ResolveFBO(name, "Resolve");
			texResult = Core::fbo.GetTexture("Resolve", 0);
		} else texResult = Core::fbo.GetTexture(name, 0);
		return texResult;
	}

	GLuint PostProcess::ApplyContrast(GLuint tex, float fContrast) {
		std::string name = "ApplyContrast";
		Core::fbo.BindFbo(name);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);
		shader->use(GLS_PP_CONTRAST);
		shader->getUniformVar(GLS_PP_CONTRAST, fContrast);
		Render();
		Core::fbo.UnbindFbo();
		texResult = Core::fbo.GetTexture(name, 0);
		return texResult;
	}

//	GLuint PostProcess::ApplyUnderwater(GLuint tex) {
//		std::string name = "ApplyUnderwater";
//		Core::fbo.BindFbo(name);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, tex);
//		Render(GLS_PP_UNDERWATER);
//		Core::fbo.UnbindFbo();
//		texResult = Core::fbo.GetTexture(name, 0);
//		return texResult;
//	}

	GLuint PostProcess::ApplyBrightness(GLuint tex, Core::Vector3f vBrightness) {
		std::string name = "ApplyBrightness";
		Core::fbo.BindFbo(name);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);
		shader->use(GLS_PP_BRIGHTNESS);
		shader->getUniformVar(GLS_PP_BRIGHTNESS, vBrightness);
		Render();
		Core::fbo.UnbindFbo();
		texResult = Core::fbo.GetTexture(name, 0);
		return texResult;
	}

	GLuint PostProcess::ApplyBrightnessFilter(GLuint tex, Core::Vector3f vFactor, float fMax) {
		std::string name = "ApplyBrightnessFilter";
		Core::fbo.BindFbo(name);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);
		shader->use(GLS_PP_BRIGHTNESS_FILTER);
		shader->getUniformVar(GLS_PP_BRIGHTNESS_FILTER, vFactor, fMax);
		Render();
		Core::fbo.UnbindFbo();
		texResult = Core::fbo.GetTexture(name, 0);
		return texResult;
	}

	GLuint PostProcess::ApplyRadialBlur(GLuint tex) {
		std::string name = "ApplyRadialBlur";
		Core::fbo.BindFbo(name);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);
		shader->use(GLS_PP_RADIALBLUR);
		shader->getUniformVar(GLS_PP_RADIALBLUR, Core::fbo.GetViewPortWidth(name));
		Render();
		Core::fbo.UnbindFbo();
		texResult = Core::fbo.GetTexture(name, 0);
		return texResult;
	}

	GLuint PostProcess::ApplyHBlur(GLuint tex) {
		std::string name = "ApplyHBlur";
		Core::fbo.BindFbo(name);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);
		shader->use(GLS_PP_HBLUR);
		shader->getUniformVar(GLS_PP_HBLUR, Core::fbo.GetViewPortWidth(name));
		Render();
		Core::fbo.UnbindFbo();
		texResult = Core::fbo.GetTexture(name, 0);
		return texResult;
	}

	GLuint PostProcess::ApplyVBlur(GLuint tex) {
		std::string name = "ApplyVBlur";
		Core::fbo.BindFbo(name);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);
		shader->use(GLS_PP_VBLUR);
		shader->getUniformVar(GLS_PP_VBLUR, Core::fbo.GetViewPortHeight(name));
		Render();
		Core::fbo.UnbindFbo();
		texResult = Core::fbo.GetTexture(name, 0);
		return texResult;
	}

	GLuint PostProcess::ApplyCombine(GLuint tex0, GLuint tex1, float fIntensity) {
		std::string name = "ApplyCombine";
		Core::fbo.BindFbo(name);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, tex1);
		shader->use(GLS_PP_COMBINE);
		shader->getUniformVar(GLS_PP_COMBINE, fIntensity);
		Render();
		Core::fbo.UnbindFbo();
		texResult = Core::fbo.GetTexture(name, 0);
		return texResult;
	}

	GLuint PostProcess::ApplyLensFlare() {
		std::string name = "ApplyLensFlare";
		Core::fbo.BindFbo(name);
		glActiveTexture(GL_TEXTURE0);	glBindTexture(GL_TEXTURE_2D, texResult);
		Render();

//		Vector2f CENTER_SCREEN = { 0.0, 0.0 };
//		float spacing = 0.25;
//		Vector2f flarePos[9];
//
//		Matrix44f mvpMat;
//		matrix->Push();
//			Matrix44f *pmvpMat = &matrix->GetModelViewProjection();
//
//			Matrix44f mI;
//			mI[0] = 1;	mI[1] = 0;	mI[2] = 0;	mI[3] = 0;
//			mI[4] = 0;	mI[5] = 1;	mI[6] = 0;	mI[7] = 0;
//			mI[8] = 0;	mI[9] = 0;	mI[10] = 1;	mI[11] = 0;
//			mI[12] = 0;	mI[13] = 0;	mI[14] = 0;	mI[15] = 1;
//
//			matrix->SetModelView(mI);
//			matrix->Rotate(Core::gameVars.player.active->transform.rot[0], 1.0, 0.0, 0.0);
//			matrix->Rotate(Core::gameVars.player.active->transform.rot[1], 0.0, 1.0, 0.0);
//			matrix->Translate(a->sun.vPosition[0], a->sun.vPosition[1], a->sun.vPosition[2]);
//			matrix->Rotate(Core::gameVars.player.active->transform.rot[1], 0.0, -1.0, 0.0);
//			matrix->Rotate(Core::gameVars.player.active->transform.rot[0], -1.0, 0.0, 0.0);
//			matrix->Scale(1/16.0f);
//			matrix->SetTransform();
//			matrix->CopyMatrix(mvpMat, *pmvpMat);
//		matrix->Pop();

//		Vector4f c = {Core::gameVars.color.white[0], Core::gameVars.color.white[1], Core::gameVars.color.white[2], Core::gameVars.color.white[3]};
//		std::std::string t;
//		int o = 20;
	//	gameSys.drawText(1, o, to_std::string(mvMat[0]), c);		gameSys.drawText(17, o, to_std::string(mvMat[1]), c);	gameSys.drawText(33, o, to_std::string(mvMat[2]), c);	gameSys.drawText(49, o++, to_std::string(mvMat[3]), c);
	//	gameSys.drawText(1, o, to_std::string(mvMat[4]), c);		gameSys.drawText(17, o, to_std::string(mvMat[5]), c);	gameSys.drawText(33, o, to_std::string(mvMat[6]), c);	gameSys.drawText(49, o++, to_std::string(mvMat[7]), c);
	//	gameSys.drawText(1, o, to_std::string(mvMat[8]), c);		gameSys.drawText(17, o, to_std::string(mvMat[9]), c);	gameSys.drawText(33, o, to_std::string(mvMat[10]), c);	gameSys.drawText(49, o++, to_std::string(mvMat[11]), c);
	//	gameSys.drawText(1, o, to_std::string(mvMat[12]), c);	gameSys.drawText(17, o, to_std::string(mvMat[13]), c);	gameSys.drawText(33, o, to_std::string(mvMat[14]), c);	gameSys.drawText(49, o++, to_std::string(mvMat[15]), c);

	//	gameSys.drawText(1, o, to_std::string(pMat[0]), c);	gameSys.drawText(12, o, to_std::string(pMat[1]), c);		gameSys.drawText(23, o, to_std::string(pMat[2]), c);		gameSys.drawText(34, o++, to_std::string(pMat[3]), c);
	//	gameSys.drawText(1, o, to_std::string(pMat[4]), c);	gameSys.drawText(12, o, to_std::string(pMat[5]), c);		gameSys.drawText(23, o, to_std::string(pMat[6]), c);		gameSys.drawText(34, o++, to_std::string(pMat[7]), c);
	//	gameSys.drawText(1, o, to_std::string(pMat[8]), c);	gameSys.drawText(12, o, to_std::string(pMat[9]), c);		gameSys.drawText(23, o, to_std::string(pMat[10]), c);	gameSys.drawText(34, o++, to_std::string(pMat[11]), c);
	//	gameSys.drawText(1, o, to_std::string(pMat[12]), c);	gameSys.drawText(12, o, to_std::string(pMat[13]), c);	gameSys.drawText(23, o, to_std::string(pMat[14]), c);	gameSys.drawText(34, o++, to_std::string(pMat[15]), c);
	//	o++;
	//	gameSys.drawText(1, o, to_std::string(mvpMat[0]), c);	gameSys.drawText(17, o, to_std::string(mvpMat[1]), c);	gameSys.drawText(33, o, to_std::string(mvpMat[2]), c);	gameSys.drawText(49, o++, to_std::string(mvpMat[3]), c);
	//	gameSys.drawText(1, o, to_std::string(mvpMat[4]), c);	gameSys.drawText(17, o, to_std::string(mvpMat[5]), c);	gameSys.drawText(33, o, to_std::string(mvpMat[6]), c);	gameSys.drawText(49, o++, to_std::string(mvpMat[7]), c);
	//	gameSys.drawText(1, o, to_std::string(mvpMat[8]), c);	gameSys.drawText(17, o, to_std::string(mvpMat[9]), c);	gameSys.drawText(33, o, to_std::string(mvpMat[10]), c);	gameSys.drawText(49, o++, to_std::string(mvpMat[11]), c);
	//	gameSys.drawText(1, o, to_std::string(mvpMat[12]), c);	gameSys.drawText(17, o, to_std::string(mvpMat[13]), c);	gameSys.drawText(33, o, to_std::string(mvpMat[14]), c);	gameSys.drawText(49, o++, to_std::string(mvpMat[15]), c);
	//	o++;

//		Vector4f vSunPos;
//		vSunPos[0] =   a->sun.vPosition[0];
//		vSunPos[1] =  -a->sun.vPosition[1];
//		vSunPos[2] =   a->sun.vPosition[2];
//		vSunPos[3] =  1.0;
//	//	t = "vSunPos = " + to_std::string(vSunPos[0]) + ", " + to_std::string(vSunPos[1]) + ", " + to_std::string(vSunPos[2]);				gameSys.drawText(11, o++, t, c);
//
//		Vector4f sunCoords;
//		matrix->MultiplyVec(sunCoords, mvpMat, vSunPos);
//		//sunCoords[3] = sunCoords[3]/1000;
//	//	t = "sunCoords = " + to_std::string(sunCoords[0]) + ", " + to_std::string(sunCoords[1]) + ", " + to_std::string(sunCoords[2]) + ", " + to_std::string(sunCoords[3]);		gameSys.drawText(9, o++, t, Core::gameVars.color.yellow);
//
//		Vector2f sunCoords_w;
//		float brightness = 0;
//		Vector2f sunToCenter;
//		sunCoords_w[0]	=  (sunCoords[0]/sunCoords[3])*1.37428;
//		sunCoords_w[1]	= -(sunCoords[1]/sunCoords[3])*1.14;
//	//	t = "sunCoords/w = " + to_std::string(sunCoords_w[0]) + ", " + to_std::string(sunCoords_w[1]);								gameSys.drawText(7, o++, t, Core::gameVars.color.orange);
//
//		sunToCenter[0] = (CENTER_SCREEN[0]-sunCoords_w[0]);
//		sunToCenter[1] = (CENTER_SCREEN[1]-sunCoords_w[1]);
//	//	t = "sunToCenter = " + to_std::string(sunToCenter[0]) + ", " + to_std::string(sunToCenter[1]);								gameSys.drawText(7, o++, t, Core::gameVars.color.green);
//
//		float sunToCenterLength = sqrtf(sunToCenter[0]*sunToCenter[0] + sunToCenter[1]*sunToCenter[1]);
//	//	t = "sunToCenterLength = " + to_std::string(sunToCenterLength);															gameSys.drawText(1, o++, t, Core::gameVars.color.red);
//		brightness = 1 - (sunToCenterLength/0.4f);
//	//	t = "brightness = " + to_std::string(brightness);																		gameSys.drawText(8, o++, t, c);
//
//		//if(occlusion.GetAvailable("ApplyLensFlare")) {	occlusion.ReadResultui("ApplyLensFlare");	}
//		//float ratio = float(occlusion.GetResultui("ApplyLensFlare"))/float(a->sun.iQuadSamples);
//		float ratio = float(occlusion.ReadResultui("ApplyLensFlare"))/float(a->sun.iQuadSamples);
//		brightness *= ratio;
//	//	t = "brightness * ratio = " + to_std::string(brightness * ratio);	gameSys.drawText(8, o++, t, c);
//
//		for (int i = 0; i < 9; i++) {
//			Vector2f direction;
//			direction[0] = sunToCenter[0];
//			direction[1] = sunToCenter[1];
//
//			direction[0] *= (i*spacing);
//			direction[1] *= (i*spacing);
//
//	//		t = "direction[" + to_std::string(i) + "] = " + to_std::string(direction[0]) + ", " + to_std::string(direction[1]);									gameSys.drawText(10, o++, t, c);
//
//			flarePos[i][0] =  ( (sunCoords_w[0] + direction[0]) * Core::gameVars.screen.w );
//			flarePos[i][1] =  ( (sunCoords_w[1] + direction[1]) * Core::gameVars.screen.h );
//
//			//flarePos[i][0] = -sunCoords[0]*(i+1)*spacing;
//			//flarePos[i][1] = -sunCoords[1]*(i+1)*spacing;
//			//flarePos[i][0] =  ((sunCoords_w[0])*Core::gameVars.screen.w);
//			//flarePos[i][1] =  ((sunCoords_w[1])*Core::gameVars.screen.h);
//		}
	//	o++;
	//	t = "flarePos[0] = " + to_std::string(flarePos[0][0]) + ", " + to_std::string(flarePos[0][1]);									gameSys.drawText(10, o++, t, c);
	//	t = "flarePos[1] = " + to_std::string(flarePos[1][0]) + ", " + to_std::string(flarePos[1][1]);									gameSys.drawText(10, o++, t, c);
	//	t = "flarePos[2] = " + to_std::string(flarePos[2][0]) + ", " + to_std::string(flarePos[2][1]);									gameSys.drawText(10, o++, t, c);
	//	t = "flarePos[3] = " + to_std::string(flarePos[3][0]) + ", " + to_std::string(flarePos[3][1]);									gameSys.drawText(10, o++, t, c);
	//	t = "flarePos[4] = " + to_std::string(flarePos[4][0]) + ", " + to_std::string(flarePos[4][1]);									gameSys.drawText(10, o++, t, c);
	//	t = "flarePos[5] = " + to_std::string(flarePos[5][0]) + ", " + to_std::string(flarePos[5][1]);									gameSys.drawText(10, o++, t, c);
	//	t = "flarePos[6] = " + to_std::string(flarePos[6][0]) + ", " + to_std::string(flarePos[6][1]);									gameSys.drawText(10, o++, t, c);
	//	t = "flarePos[7] = " + to_std::string(flarePos[7][0]) + ", " + to_std::string(flarePos[7][1]);									gameSys.drawText(10, o++, t, c);
	//	t = "flarePos[8] = " + to_std::string(flarePos[8][0]) + ", " + to_std::string(flarePos[8][1]);									gameSys.drawText(10, o++, t, c);

		//if(brightness < 0) brightness = 0;
		//if(brightness > 1) brightness = 1;
		//a->sun.fFlareAlpha = brightness;
		glActiveTexture(GL_TEXTURE0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		//glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
		//glBlendFunc(GL_ONE, GL_ONE);

		//Vector2i s = { Core::gameVars.screen.w, Core::gameVars.screen.h*(Core::gameVars.screen.w/Core::gameVars.screen.h) };
		//a->sun.tex.Set(a->sun.sFlare[5]);	RenderQuad(flarePos[5][0], flarePos[5][1], s[0]*0.5,   s[1]*0.5,	GLS_PP_LENSFLARE, true);
		//a->sun.tex.Set(a->sun.sFlare[3]);	RenderQuad(flarePos[3][0], flarePos[3][1], s[0]*0.23,  s[1]*0.23,	GLS_PP_LENSFLARE, true);
		//a->sun.tex.Set(a->sun.sFlare[1]);	RenderQuad(flarePos[1][0], flarePos[1][1], s[0]*0.1,   s[1]*0.1,	GLS_PP_LENSFLARE, true);
		//a->sun.tex.Set(a->sun.sFlare[6]);	RenderQuad(flarePos[6][0], flarePos[6][1], s[0]*0.05,  s[1]*0.05,	GLS_PP_LENSFLARE, true);
		//a->sun.tex.Set(a->sun.sFlare[0]);	RenderQuad(flarePos[0][0], flarePos[0][1], s[0]*0.012, s[1]*0.012,	GLS_PP_LENSFLARE, true);
		//a->sun.tex.Set(a->sun.sFlare[8]);	RenderQuad(flarePos[8][0], flarePos[8][1], s[0]*0.1,   s[1]*0.1,	GLS_PP_LENSFLARE, true);
		//a->sun.tex.Set(a->sun.sFlare[2]);	RenderQuad(flarePos[2][0], flarePos[2][1], s[0]*0.07,  s[1]*0.07,	GLS_PP_LENSFLARE, true);
		//a->sun.tex.Set(a->sun.sFlare[4]);	RenderQuad(flarePos[4][0], flarePos[4][1], s[0]*0.3,   s[1]*0.3,	GLS_PP_LENSFLARE, true);
		//a->sun.tex.Set(a->sun.sFlare[7]);	RenderQuad(flarePos[7][0], flarePos[7][1], s[0]*0.6,   s[1]*0.6,	GLS_PP_LENSFLARE, true);

		Core::fbo.UnbindFbo();
		texResult = Core::fbo.GetTexture(name, 0);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		return texResult;
	}

	/*
	 * tex: The texture from the previous pass
	 * sDepthName: The name of the FBO whos depth
	 * 							texture should be used. Since
	 * 							post-processing passes are
	 * 							rendered on quads the depth
	 * 							texture is useless. Need to
	 * 							know the first pass Core::fbo.
	 */
//	GLuint PostProcess::ApplyDepthOfField(GLuint tex, std::string sDepthName) {
//		std::string name = "ApplyDepthOfField";
//		Core::fbo.BindFbo(name);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, tex);
//		glActiveTexture(GL_TEXTURE1);
//		if(Core::fbo.HasMultisample(sDepthName)) {
//			Core::fbo.ResolveFBO(sDepthName, "Resolve");
//			glBindTexture(GL_TEXTURE_2D, Core::fbo.GetDepthTexture("Resolve"));
//		} else {
//			glBindTexture(GL_TEXTURE_2D, Core::fbo.GetDepthTexture(sDepthName));
//		}
//		Render(GLS_PP_DEPTHOFFIELD);
//		Core::fbo.UnbindFbo();
//		texResult = Core::fbo.GetTexture(name, 0);
//		return texResult;
//		if(bResult) return 1;
//		else return 0;
//	}

//	GLuint PostProcess::ApplyCartoon(GLuint tex) {
//		std::string name = "ApplyCartoon";
//		Core::fbo.BindFbo(name);
//		glActiveTexture(GL_TEXTURE0);
//		glBindTexture(GL_TEXTURE_2D, tex);
//		Render(GLS_PP_CARTOON);
//		Core::fbo.UnbindFbo();
//		texResult = Core::fbo.GetTexture(name, 0);
//		return texResult;
//	}

	void PostProcess::RenderQuad(int x, int y, int w, int h, SHADER_PROGRAMS uiShader, bool bCenter, bool bClear) {
	//	if (bClear) {
	//		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	//		//glClearColor(0.8, 0.8, 0.8, 0.0);
	//		glClear( Core::gameVars.screen.clear );
	//	}

		float	fX,
				fY,
				fW = w/2,
				fH = h/2;
		// Center screen coordinates or top left coordinates
		if(bCenter) {
			fX =  x;
			fY = -y;		// -y is the up direction in this game
		} else {
			fX = -(vuiScreenSize.x/2)+x;
			fY = (vuiScreenSize.y/2)-y;
		}

		matrix->SetProjection(matrix->MM_ORTHO);
		shader->use(uiShader);

		glDisable(GL_DEPTH_TEST);
		matrix->Push();
			matrix->Translate(fX, fY, 0.0f);
			matrix->Scale(fW, fH, 1);
			matrix->SetTransform();
			//Core::shader->getUniform(*a, uiShader);
			shader->getUniform(uiShader);
			vao.Draw();
			matrix->Pop();
		matrix->SetProjection(matrix->MM_PERSPECTIVE);
		glEnable(GL_DEPTH_TEST);
	}

	void PostProcess::Render(SHADER_PROGRAMS uiShader) {
		shader->use(uiShader);
		shader->getUniform(uiShader);
		Render();
	}

	void PostProcess::Render() {
		// TODO: DEBUG, forces font color to white
		//		 since it doesn't get reset properly
		//		 This seems to have something to
		//		 do with the text system/menu system
		//Core::gameVars.font.vColor = Core::gameVars.color.white;
		Core::colors.PushFront(Core::colors[Core::colors().White]);
		Core::colors.SetActive(Core::colors.COLOR_FRONT);

		matrix->SetProjection(matrix->MM_ORTHO);
//		shader->use(uiShader);

		glDisable(GL_DEPTH_TEST);
		matrix->Push();
			//matrix->Translate(200, -100, 0);
			//matrix->Scale((vuiScreenSize.x/4), (vuiScreenSize.y/4), 1);
			matrix->Scale((vuiScreenSize.x/2), (vuiScreenSize.y/2), 1);
			matrix->SetTransform();
			//shader->getUniform(uiShader);
			vao.Draw();
			matrix->Pop();
		matrix->SetProjection(matrix->MM_PERSPECTIVE);
		glEnable(GL_DEPTH_TEST);
		Core::colors.PopFront();
	}

	void PostProcess::Render2(SHADER_PROGRAMS uiShader, Vector3f vTranslate, float fScale) {
		// TODO: DEBUG, forces font color to white
		//		 since it doesn't get reset properly
		//		 This seems to have something to
		//		 do with the text system/menu system
		//Core::gameVars.font.vColor = Core::gameVars.color.white;
		Core::colors.PushFront(Core::colors[Core::colors().White]);
		Core::colors.SetActive(Core::colors.COLOR_FRONT);

		matrix->SetProjection(matrix->MM_ORTHO);
		shader->use(uiShader);

		glDisable(GL_DEPTH_TEST);
		matrix->Push();
			//matrix->Translate(-300, -150, 0);
			matrix->Translate(vTranslate);
			//matrix->Scale((vuiScreenSize.x/6), (vuiScreenSize.y/6), 1);
			matrix->Scale((vuiScreenSize.x/2)*fScale, (vuiScreenSize.y/2)*fScale, 1);
			//matrix->Scale((vuiScreenSize.x/2), (vuiScreenSize.y/2), 1);
			matrix->SetTransform();
			shader->getUniform(uiShader);
			vao.Draw();
			matrix->Pop();
		matrix->SetProjection(matrix->MM_PERSPECTIVE);
		glEnable(GL_DEPTH_TEST);
		Core::colors.PopFront();
	}
}

#endif /* SRC_HEADERS_CORE_POST_PROCESS_H_ */

