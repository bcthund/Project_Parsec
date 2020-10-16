
/*
 * glinit.h
 *
 *  Created on: Jan 28, 2014
 *      Author: bcthund
 */


//#include <iostream>

#include "core_functions.h"
#include "glinit.h"

namespace Core {

//	class GlInit_System {
//		private:
//			Vector4f vClearColor;
//		protected:
//		public:
//			SDL_Window * window;
//			SDL_GLContext context;
//			void init(std::string cCaption, GLuint uiWidth, GLuint uiHeight, GLuint uiBpp, bool bMS, Vector4f vClearColor);
//			void EnableAdditiveBlending();
//			void DisableAdditiveBlending();
//			void RestoreClearColor();
//			~GlInit_System();
//	};

	GlInit_System::~GlInit_System() {
		Core::debug.log("Destroy GlInit {");

		//delete [] mvStack;
		//delete [] mtvStack;
		//delete [] mrvStack;
		//delete [] mvpStack;
		//SDL_FreeSurface(screen);
//		if(vClearColor != nullptr) delete vClearColor;
		SDL_Quit();
		//delete [] screen;

		Core::debug.print(" Done ", Core::debug().GREEN);
		Core::debug.print("}\n");
	}

	void GlInit_System::RestoreClearColor() {
		glClearColor(	vClearColor[0],
						vClearColor[1],
						vClearColor[2],
						vClearColor[3]	);
	}

	void GlInit_System::EnableAdditiveBlending() {
//		glBlendFunc(GL_ONE, GL_ONE);
		//glBlendFunc(GL_SRC_ALPHA, GL_DST_COLOR);
		//glBlendFunc(GL_ONE_MINUS_SRC_COLOR, GL_ONE_MINUS_DST_COLOR);
		//glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
		//glBlendFunc(GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
//		glBlendFunc(GL_SRC_ALPHA, GL_DST_COLOR);
	}

	void GlInit_System::DisableAdditiveBlending() {
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void GlInit_System::init(std::string cCaption, GLuint uiWidth, GLuint uiHeight, GLuint uiBpp, bool bMS, Vector4f vClearColor) {
		Core::debug.log("Init GlInit {");

		this->vClearColor = vClearColor;

		if (SDL_Init(SDL_INIT_VIDEO)!=0) printf("Failed:\n %s\n", SDL_GetError());

		SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
		SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
		SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
		SDL_GL_SetAttribute( SDL_GL_BUFFER_SIZE, 32 );
		SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
		SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

		window = SDL_CreateWindow(cCaption.c_str(),
								  SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								  uiWidth, uiHeight,
								  SDL_WINDOW_OPENGL);

		if (!window) {
			fprintf(stderr, "Couldn't create window: %s\n", SDL_GetError());
			return;
		}

//			SDL_SetWindowResizable(window, SDL_TRUE);

		context = SDL_GL_CreateContext(window);
		if (!context) {
			fprintf(stderr, "Couldn't create context: %s\n", SDL_GetError());
			return;
		}

		// Change z range from -1,1 to 0,1 (this appears to be recommended)
//			glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);

		//Set initial clear color
		glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

		// Blending
		glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		DisableAdditiveBlending();
		glBlendEquation(GL_FUNC_ADD);		//GL_FUNC_ADD   GL_FUNC_SUBTRACT   GL_FUNC_REVERSE_SUBTRACT

		// Polygon Offset
		//glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(1.0f, 1.0f);

		// Stencil Buffer
		//glEnable(GL_STENCIL_TEST);
		//glClearStencil(0);

		// Other Settings
		glEnable(GL_DEPTH_TEST);
//			glEnable(GL_DEPTH_CLAMP);
		glDisable(GL_DEPTH_CLAMP);
		glDepthMask(GL_TRUE);

		// Standard Z Depth
//			glDepthFunc(GL_LEQUAL);
//			glDepthRange(0.0, 1.0);
//			glDepthRange(-1.0, 1.0);

		// Reversed Z Depth
		glDepthFunc(GL_GEQUAL);
		glDepthRange(0.0, 1.0);
		glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);



//			GLint major, minor;
//			glGetIntegerv(GL_MAJOR_VERSION, &major);
//			glGetIntegerv(GL_MINOR_VERSION, &minor);
//			if ((major > 4 || (major == 4 && minor >= 5)) ||
//				SDL_GL_ExtensionSupported("GL_ARB_clip_control"))
//			{
//				glClipControl(GL_LOWER_LEFT, GL_ZERO_TO_ONE);
//			}
//			else
//			{
//				fprintf(stderr, "glClipControl required, sorry.\n");
//				exit(1);
//			}
//			SDL_GL_ExtensionSupported("GL_ARB_clip_control");


		#define GL_POINT_SPRITE 0x8861		// Hack to enable Point Sprites thus enabling gl_PointCoord operation
		glEnable(GL_POINT_SPRITE);
		glEnable(GL_PROGRAM_POINT_SIZE);
		glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_UPPER_LEFT);
		glPointParameteri(GL_POINT_FADE_THRESHOLD_SIZE, 1.0f);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glPointSize(10.0f);
		glLineWidth(1.0f);

		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		//glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

		if (bMS) {
			glEnable(GL_MULTISAMPLE);
			//SDL_GL_SetAttribute( SDL_GL_MULTISAMPLEBUFFERS, 1);
			//SDL_GL_SetAttribute( SDL_GL_MULTISAMPLESAMPLES, 4);
			//glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);
			//glEnable(GL_SAMPLE_ALPHA_TO_ONE);
			//glEnable(GL_SAMPLE_COVERAGE);
			//glSampleCoverage(0.5, GL_FALSE);

			//glEnable(GL_LINE_SMOOTH);
			//glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
			//glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);

			//glEnable(GL_POLYGON_SMOOTH);
			//glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

			//glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//glBlendFunc (GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR);
		}

		//glEnable(GL_PRIMITIVE_RESTART);
		//glPrimitiveRestartIndex(0xFFFF);

		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);

		//glEnable(GL_CLIP_DISTANCE0);		// Clipping plane for water Reflection/Refraction

		//Were there any errors?
//		GLenum isError = glGetError();
//		if( isError != GL_NO_ERROR ) printf("OpenGL Failed to initialize properly. [Error: %i]\n", isError);
		debug.glErrorCheck("glInit", 199);

		SDL_Init(SDL_INIT_EVERYTHING);

		/*
		 * Allow mouse to exit the window
		 */
		//SDL_WM_GrabInput(SDL_GRAB_OFF);
		SDL_SetRelativeMouseMode(SDL_FALSE);

		Core::debug.print(" Done ", Core::debug().GREEN);
		Core::debug.print("}\n");
	}
}
