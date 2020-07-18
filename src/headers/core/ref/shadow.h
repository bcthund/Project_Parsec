/*
 * shadow.h
 *
 *  Created on: Feb 27, 2011
 *      Author: bcthund
 */

#ifndef SHADOW_H_
#define SHADOW_H_

static const GLenum fboBuffs[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
static const GLenum windowBuff[] = { GL_BACK_LEFT };

void Shadow::init(GameVars &gameVars) {
	bFinished = false;
	iCurrentRes = gameVars.shadow.res;
	glPolygonOffset(1.2f, 5.0f);
	//glEnable(GL_POLYGON_OFFSET_FILL);

    // create shadow map
    glGenTextures(1, &texShadow);
    glBindTexture(GL_TEXTURE_2D, texShadow);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, 1);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, gameVars.screen.w, gameVars.screen.h, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, 512*gameVars.shadow.res, 512*gameVars.shadow.res, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

    // create shadow fbo
    glGenFramebuffers(1, &fboShadow);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboShadow);
    glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
    glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texShadow, 0);

	GLenum check = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (check!=GL_FRAMEBUFFER_COMPLETE) {
		printf("EE\tFailed creating FBO - ");
		switch (check) {
			case GL_FRAMEBUFFER_COMPLETE:
				//printf("GL_FRAMEBUFFER_COMPLETE\n");
			break;
			case GL_FRAMEBUFFER_UNDEFINED:
				printf("GL_FRAMEBUFFER_UNDEFINED\n");
			break;
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
				printf("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT\n");
			break;
			case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
				printf("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT\n");
			break;
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
				printf("GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER\n");
			break;
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
				printf("GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER\n");
			break;
			case GL_FRAMEBUFFER_UNSUPPORTED:
				printf("GL_FRAMEBUFFER_UNSUPPORTED\n");
			break;
			case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
				printf("GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE\n");
			break;
			case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
				printf("GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS\n");
			break;
			default:
				printf("UNDEFINED ERROR! [%i]\n", check);
			break;
		}
	}

	// Reset framebuffer binding
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Shadow::Start(GameVars &gameVars) {
	bFinished = false;
	glEnable(GL_POLYGON_OFFSET_FILL);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, texShadow);
	//glDepthFunc(GL_LESS);
	//glCullFace(GL_FRONT);
	glViewport(0, 0, 512*gameVars.shadow.res, 512*gameVars.shadow.res);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboShadow);
	glDrawBuffer(GL_NONE);
	glClear( GL_DEPTH_BUFFER_BIT );
}

void Shadow::Stop(GameVars &gameVars) {
	glDisable(GL_POLYGON_OFFSET_FILL);
	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_BACK);
	glViewport(0, 0, gameVars.screen.w, gameVars.screen.h);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
	bFinished = true;
}

#endif /* SHADOW_H_ */
