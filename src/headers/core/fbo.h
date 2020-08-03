/*
 * fbo.h
 *
 *  Created on: Jan 28, 2014
 *      Author: bcthund
 */

#ifndef FBO_H_
#define FBO_H_

#include <iostream>

namespace Core {
	class _FBO {
		private:
			struct _FBO_Struct {
				GLuint	uiFramebuffer;		// Holds index of framebuffer
				bool	bFrameBuffer;		// Has the framebuffer been generated?

				GLuint	uiDepthBuffer;		// Holds index of renderbuffer (used for depth buffer)
				bool	bDepthBuffer;		// Has the depth buffer been attached?

				GLuint	uiColorBuffer;		//
				bool	bColorBuffer;		//

				GLuint	uiTexColor[4];		// Holds up to 4 color attachment texture indexes
				bool	bTexColor[4];		// Has the color attachment been attached to the FBO?

				GLuint	uiTexDepth;			// Holds the index for a depth buffer attachment
				bool	bTexDepth;			// Has the depth texture been attached to the FBO?

				uint	w, h;				// Width and Height of the viewport
				bool	bFinished;			// Has the FBO been finalized and returned a success?

				uint	uiMultisample;		// Is this a multisampled FBO?
			};

			GLint iViewport[4];
			uint	  uiNumBuffers;			// Number of created FBOs
			uint	  uiMaxFbos;			// Maximum number of FBOs

			t_VectorMap<_FBO_Struct*> fbo;

			bool		bDebug;
		protected:
		public:
			_FBO();
			~_FBO();
			void	CreateFbo(std::string name, uint w, uint h, uint uiMultisample=0);					// Generate FBO, make name pair, default color_attachment0, bind framebuffer
			void	AddColorAttachment(std::string name, uint n, GLuint filter, GLuint clamp);			// Add a color attachment to the specified color attachment number
			void	AddDepthBuffer(std::string name);													// Add a depth buffer, renderbuffer
			void	AddDepthTexture(std::string name, GLuint filter, GLuint clamp);						// Add a depth buffer, texture buffer
			void	SetDrawBuffer(std::string name, uint ui, bool bDepth);								//
			void	SetReadBuffer(std::string name, uint ui, bool bDepth);								//
			void	ResolveFBO(std::string s, std::string t, GLuint filter);							// Resolve multisampled fbo to texture
			void	ResolveFBOtoScreen(std::string source, GLuint filter);
			void	FinishFbo(std::string name);														// Run check and set bFinished if success
			void	BindFbo(std::string name);															// Bind the FBO for rendering
			void	UnbindFbo();																		// Unbind all FBOs
			uint	GetTexture(std::string name, uint n)		{	return fbo[name]->uiTexColor[n];	}
			uint	GetDepthTexture(std::string name)			{	return fbo[name]->uiTexDepth;	}
			int		GetViewPortWidth(std::string name)			{	return fbo[name]->w;	}
			int		GetViewPortHeight(std::string name)			{	return fbo[name]->h;	}
			bool	HasMultisample(std::string name);
			uint	GetMultisamples(std::string name);
			void	CheckStatus();
	} fbo;

	_FBO::_FBO() {
		fbo.setSource("FBO");
		bDebug = false;
		uiMaxFbos = 32;
		uiNumBuffers = 0;
//		fbo = new _FBO_Struct[uiMaxFbos];
//		for(uint i=0; i<uiMaxFbos; i++) {
//			fbo[i]->uiFramebuffer = 0;
//			fbo[i]->uiColorBuffer = 0;
//			fbo[i]->uiDepthBuffer = 0;
//			fbo[i]->uiMultisample = 0;
//			fbo[i]->uiTexDepth = 0;
//			fbo[i]->uiTexColor[0] = 0;
//			fbo[i]->uiTexColor[1] = 0;
//			fbo[i]->uiTexColor[2] = 0;
//			fbo[i]->uiTexColor[3] = 0;
//
//			fbo[i]->bColorBuffer = false;
//			fbo[i]->bDepthBuffer = false;
//			fbo[i]->bFinished = false;
//			fbo[i]->bFrameBuffer = false;
//			fbo[i]->bTexDepth = false;
//			fbo[i]->bTexColor[0] = false;
//			fbo[i]->bTexColor[1] = false;
//			fbo[i]->bTexColor[2] = false;
//			fbo[i]->bTexColor[3] = false;
//
//			fbo[i]->w = 0;
//			fbo[i]->h = 0;
//			fbo[i]->bFinished = false;
//		}
	}

	_FBO::~_FBO() {
		//       .................................................................Done
		std::cout << "Destroy FBOs.....................................................";
		for (auto & item : fbo) {
			if(item->bFrameBuffer) glDeleteFramebuffers(1, &item->uiFramebuffer);
			if(item->bDepthBuffer) glDeleteRenderbuffers(1, &item->uiDepthBuffer);
			if(item->bColorBuffer) glDeleteRenderbuffers(1, &item->uiColorBuffer);
			if(item->bTexDepth)    glDeleteTextures(1, &item->uiTexDepth);
			if(item->bTexColor[0]) glDeleteTextures(1, &item->uiTexColor[0]);
			if(item->bTexColor[1]) glDeleteTextures(1, &item->uiTexColor[1]);
			if(item->bTexColor[2]) glDeleteTextures(1, &item->uiTexColor[2]);
			if(item->bTexColor[3]) glDeleteTextures(1, &item->uiTexColor[3]);
			delete item;
		}

//		for(int i=0; i<uiNumBuffers; i++) {
//			if (fbo[i]->bFrameBuffer) glDeleteFramebuffers(1, &fbo[i]->uiFramebuffer);
//			if(fbo[i]->bDepthBuffer) glDeleteRenderbuffers(1, &fbo[i]->uiDepthBuffer);
//			if(fbo[i]->bColorBuffer) glDeleteRenderbuffers(1, &fbo[i]->uiColorBuffer);
//			if(fbo[i]->bTexDepth) 	glDeleteTextures(1, &fbo[i]->uiTexDepth);
//			if(fbo[i]->bTexColor[0]) glDeleteTextures(1, &fbo[i]->uiTexColor[0]);
//			if(fbo[i]->bTexColor[1]) glDeleteTextures(1, &fbo[i]->uiTexColor[1]);
//			if(fbo[i]->bTexColor[2]) glDeleteTextures(1, &fbo[i]->uiTexColor[2]);
//			if(fbo[i]->bTexColor[3]) glDeleteTextures(1, &fbo[i]->uiTexColor[3]);
//		}
//		delete [] fbo;
		std::cout << "Done" << std::endl;
	}

	void _FBO::CreateFbo(std::string name, uint w, uint h, uint uiMultisample) {
//		if (uiNumBuffers < uiMaxFbos) {
			//siMap.insert(make_pair(name, uiNumBuffers));
			//int id = name;

			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LEQUAL);
			glDepthMask(GL_TRUE);

//			glGenFramebuffers(1, &fbo[uiNumBuffers]->uiFramebuffer);
//			glBindFramebuffer(GL_FRAMEBUFFER, fbo[uiNumBuffers]->uiFramebuffer);
//			fbo[id]->w = w;
//			fbo[id]->h = h;
//			fbo[id]->bFrameBuffer = true;
//			fbo[id]->uiMultisample = uiMultisample;
	//		if(uiMultisample>0) std::cout << "Creating Multisampled FBO for " << name << std::endl;

			_FBO_Struct *newData = new _FBO_Struct();
			glGenFramebuffers(1, &newData->uiFramebuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, newData->uiFramebuffer);
			newData->w = w;
			newData->h = h;
			newData->bFrameBuffer = true;
			newData->uiMultisample = uiMultisample;
			fbo.add(name, newData);

			if (bDebug) std::cout << "Creating '" << name << "' FBO..." << std::endl;
			//uiNumBuffers++;
			uiNumBuffers = fbo.size();
//		} else {
//			if (bDebug) std::cout << "! Too many FBOs, Aborting" << std::endl;
//		}
	}

	void _FBO::AddColorAttachment(std::string name, uint n=0, GLuint filter=GL_LINEAR, GLuint clamp=GL_CLAMP_TO_EDGE) {
		int id = fbo.getID(name);
		if(fbo[id]->uiMultisample>0) {
	//		std::cout << "Adding Multisampled Color Buffer for " << name << std::endl;
			glGenRenderbuffers(1, &fbo[id]->uiColorBuffer);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo[id]->uiFramebuffer);
			glBindRenderbuffer(GL_RENDERBUFFER, fbo[id]->uiColorBuffer);
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, fbo[id]->uiMultisample, GL_RGBA8, fbo[id]->w, fbo[id]->h);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, fbo[id]->uiColorBuffer);
			if (bDebug) std::cout << "\t '" << name << "' Color Buffer: ";
			fbo[id]->bColorBuffer = true;
		} else {
			glGenTextures(1, &fbo[id]->uiTexColor[n]);
			glBindTexture(GL_TEXTURE_2D, fbo[id]->uiTexColor[n]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, fbo[id]->w, fbo[id]->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, clamp);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, clamp);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, clamp);
			uint uiAttach = 0;
			switch(n) {
				case 0:  uiAttach = GL_COLOR_ATTACHMENT0; break;
				case 1:  uiAttach = GL_COLOR_ATTACHMENT1; break;
				case 2:  uiAttach = GL_COLOR_ATTACHMENT2; break;
				case 3:  uiAttach = GL_COLOR_ATTACHMENT3; break;
				default: uiAttach = GL_COLOR_ATTACHMENT0;
			}
			glFramebufferTexture(GL_FRAMEBUFFER, uiAttach, fbo[id]->uiTexColor[n], 0);
			if (bDebug) std::cout << "\t '" << name << "' Color Texture: ";
			fbo[id]->bTexColor[n] = true;
		}
		CheckStatus();
	}

	void _FBO::AddDepthBuffer(std::string name) {
		int id = fbo.getID(name);
		glGenRenderbuffers(1, &fbo[id]->uiDepthBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, fbo[id]->uiDepthBuffer);
		if(fbo[id]->uiMultisample>0) {
	//		std::cout << "Adding Multisampled Depth Buffer for " << name << std::endl;
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, fbo[id]->uiMultisample, GL_DEPTH_COMPONENT, fbo[id]->w, fbo[id]->h);
		} else {
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, fbo[id]->w, fbo[id]->h);
		}
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fbo[id]->uiDepthBuffer);
		if (bDebug) std::cout << "\t '" << name << "' Depth Buffer: ";
		CheckStatus();
		fbo[id]->bDepthBuffer = true;
	}

	void _FBO::AddDepthTexture(std::string name, GLuint filter=GL_LINEAR, GLuint clamp=GL_CLAMP_TO_EDGE) {
		int id = fbo.getID(name);
		if(fbo[id]->uiMultisample>0) {
			//Force depth buffer
			if (bDebug) std::cout << "Warning: [" << name << "] Cannot add Depth Texture to multisampled FBO, adding Depth Buffer instead." << std::endl;
			AddDepthBuffer(name);
		} else {
			//glBindFramebuffer(GL_FRAMEBUFFER, fbo[id]->uiFramebuffer);			// Ensure correct framebuffer is bound
			glGenTextures(1, &fbo[id]->uiTexDepth);
			glBindTexture(GL_TEXTURE_2D, fbo[id]->uiTexDepth);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, fbo[id]->w, fbo[id]->h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, clamp);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, clamp);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, clamp);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, fbo[id]->uiTexDepth, 0);
			if (bDebug) std::cout << "\t '" << name << "' Depth Texture: ";
			CheckStatus();
			fbo[id]->bTexDepth = true;
		}
	}

	void _FBO::SetDrawBuffer(std::string name, uint ui, bool bDepth=false) {
		int id = fbo.getID(name);
		if (bDepth) {
			glBindRenderbuffer(GL_RENDERBUFFER, fbo[id]->uiDepthBuffer);
		} else {
			glBindFramebuffer(GL_FRAMEBUFFER, fbo[id]->uiFramebuffer);			// Ensure correct framebuffer is bound
		}
		glDrawBuffer(ui);
	}

	void _FBO::SetReadBuffer(std::string name, uint ui, bool bDepth=false) {
		int id = fbo.getID(name);
		if (bDepth) {
			glBindRenderbuffer(GL_RENDERBUFFER, fbo[id]->uiDepthBuffer);
		} else {
			glBindFramebuffer(GL_FRAMEBUFFER, fbo[id]->uiFramebuffer);			// Ensure correct framebuffer is bound
		}
		glDrawBuffer(ui);
	}

	void _FBO::ResolveFBO(std::string source, std::string destination, GLuint filter=GL_NEAREST) {
//		int s = siMap[source];
//		int d = siMap[destination];
		int s = fbo.getID(source);
		int d = fbo.getID(destination);
			glBindFramebuffer(	GL_DRAW_FRAMEBUFFER, fbo[d]->uiFramebuffer);
			glBindFramebuffer(	GL_READ_FRAMEBUFFER, fbo[s]->uiFramebuffer);
			glBlitFramebuffer(	0, 0, fbo[s]->w, fbo[s]->h,
								0, 0, fbo[d]->w, fbo[d]->h,
								GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT,
								filter);
			UnbindFbo();
	}

	void _FBO::ResolveFBOtoScreen(std::string source, GLuint filter=GL_NEAREST) {
//		int s = siMap[source];
		int s = fbo.getID(source);
		if(fbo[s]->uiMultisample>0) {
	//		std::cout << "Resolving Multispampled FBO..." << std::endl;
	//		std::cout << "\tSource: " << source << "[" << s << ", " << fbo[s].uiFramebuffer << "]" << std::endl;
			glBindFramebuffer(	GL_DRAW_FRAMEBUFFER, 0);
			glBindFramebuffer(	GL_READ_FRAMEBUFFER, fbo[s]->uiFramebuffer);
			glDrawBuffer( GL_BACK );
			glBlitFramebuffer(	0, 0, fbo[s]->w, fbo[s]->h,
								0, 0, fbo[s]->w, fbo[s]->h,
								GL_COLOR_BUFFER_BIT,
								filter);
			//glBindFramebuffer(	GL_FRAMEBUFFER, fbo[d].uiFramebuffer	);
			UnbindFbo();
		} else {
			if (bDebug) std::cout << "Error: [" << source << "Cannot resolve non-multisampled FBO." << std::endl;
		}
	}

	bool _FBO::HasMultisample(std::string name) {
		if(fbo[name]->uiMultisample>0) return true;
		else return false;
	}

	uint _FBO::GetMultisamples(std::string name) {
		return fbo[name]->uiMultisample;
	}

	void _FBO::FinishFbo(std::string name) {
		GLenum check = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (bDebug) {
			std::cout << "\t '" << name << "' FBO Finished: ";
			switch (check) {
				case GL_FRAMEBUFFER_COMPLETE:						std::cout << "GL_FRAMEBUFFER_COMPLETE"						<< std::endl;	break;
				case GL_FRAMEBUFFER_UNDEFINED:						std::cout << "GL_FRAMEBUFFER_UNDEFINED"						<< std::endl;	break;
				case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:			std::cout << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"			<< std::endl;	break;
				case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:	std::cout << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"	<< std::endl;	break;
				case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:			std::cout << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"			<< std::endl;	break;
				case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:			std::cout << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER"			<< std::endl;	break;
				case GL_FRAMEBUFFER_UNSUPPORTED:					std::cout << "GL_FRAMEBUFFER_UNSUPPORTED"					<< std::endl;	break;
				case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:			std::cout << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE"			<< std::endl;	break;
				case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:		std::cout << "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS"		<< std::endl;	break;
				default:											std::cout << "UNDEFINED ERROR! [" << check << "]"			<< std::endl;	break;
			}
		}

		if (check==GL_FRAMEBUFFER_COMPLETE) fbo[name]->bFinished = true;

		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void _FBO::BindFbo(std::string name) {
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo[name]->uiFramebuffer);
		glGetIntegerv( GL_VIEWPORT, iViewport );
		glViewport(0, 0, fbo[name]->w, fbo[name]->h);
	}

	void _FBO::UnbindFbo() {
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(iViewport[0], iViewport[1], iViewport[2], iViewport[3]);
	}

	void _FBO::CheckStatus() {
		GLenum check = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (bDebug) {
			switch (check) {
				case GL_FRAMEBUFFER_COMPLETE:						std::cout << "GL_FRAMEBUFFER_COMPLETE"						<< std::endl;	break;
				case GL_FRAMEBUFFER_UNDEFINED:						std::cout << "GL_FRAMEBUFFER_UNDEFINED"						<< std::endl;	break;
				case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:			std::cout << "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT"			<< std::endl;	break;
				case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:	std::cout << "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT"	<< std::endl;	break;
				case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:			std::cout << "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER"			<< std::endl;	break;
				case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:			std::cout << "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER"			<< std::endl;	break;
				case GL_FRAMEBUFFER_UNSUPPORTED:					std::cout << "GL_FRAMEBUFFER_UNSUPPORTED"					<< std::endl;	break;
				case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:			std::cout << "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE"			<< std::endl;	break;
				case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:		std::cout << "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS"		<< std::endl;	break;
				default:											std::cout << "UNDEFINED ERROR! [" << check << "]"			<< std::endl;	break;
			}
		}
	}
}

#endif /* FBO_H_ */
