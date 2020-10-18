/*
 * Core.shader.h
 *
 *  Created on: Jan 28, 2014
 *      Author: bcthund
 */

#ifndef SHADER_H_
#define SHADER_H_

#include <stdarg.h>
#include <cstring>

#include "gl4_5/glcorearb.h"
#include "lights.h"
#include "Stipple.h"

namespace Core {
// Shader program names, needs cleanup
	enum SHADER_PROGRAMS {	GLS_BASE = 0,
							GLS_FONT,
							GLS_MENU,
							GLS_ICON,
							GLS_MOUSERAY,
							GLS_POINTS,
							GLS_LINES,
							GLS_BOUNDINGVOLUME_OBB,
							GLS_BOUNDINGVOLUME_AABB,
							GLS_BOUNDINGVOLUME_SPHERE,
							GLS_BOUNDINGVOLUME_CYLINDER,
							GLS_FLAT,
							GLS_PHONG,	GLS_WATER,	// SAME SHADER
							GLS_PHONG_O2D,
							GLS_POINT_SPRITE,
							GLS_PARTICLE_SPRITE,
							//GLS_FLAT_FOG,
							//GLS_FLAT_FOG_SHEAR,
							//GLS_FLAT_FOG_INSTANCE,
							//GLS_SHADED_TEX,
							//GLS_SHADED_TEX_ALPHA,
							GLS_NORMAL_LINE2,
							//GLS_DIRECTIONAL,
							//GLS_DIRECTIONAL_TERRAIN,
							//GLS_DIRECTIONAL_WATER,
							GLS_TROPOSPHERE,
							GLS_STRATOSPHERE,
							GLS_THERMOSPHERE,
							GLS_SUN,
							GLS_EXOSPHERE,
							GLS_SNOW,		// 2D Snow
							GLS_SNOW_3D,	// 3D Snow
							//GLS_RAIN,		// 3D Rain
							//GLS_HAIL,
							GLS_FLORA,
							//GLS_UWFLORA,
							//GLS_GRASS_TRI,
							//GLS_GRASS_LINE,
							//GLS_SCATTER,
							GLS_PP_CONTRAST,
							GLS_PP_BRIGHTNESS,
							GLS_PP_BRIGHTNESS_FILTER,
							//GLS_PP_UNDERWATER,
							GLS_PP_RADIALBLUR,
							GLS_PP_HBLUR,
							GLS_PP_VBLUR,
							//GLS_PP_RAYBLUR,
							//GLS_PP_BLOOM,
							//GLS_PP_DEPTHOFFIELD,
							//GLS_PP_VINETTE,
							//GLS_PP_LENSFLARE,
							//GLS_PP_EDGEDETECT,
							//GLS_PP_CARTOON,
							//GLS_PP_CELLSHADING,
							GLS_PP_COMBINE,
							//GLS_PP_PIXELATE,
//							GLS_PARTICLE,
							GLS_LAST };

	struct t_UniformLocations {
		bool bInit;
		SHADER_PROGRAMS shader;

		union u_Type {
			struct t_PHONG {
				GLint	locTexture[32],
						locNumLights,
						*locLightPos,
						*locLightDir,
						*locLightDiffuse,
						*locLightAmbient,
						*locLightSpecular,
						*locLightAttenuation,
						*locLightType;

				GLint	locMVP,
						locMV,
						locMP,
						locWater;
			} phong;

			struct t_PHONG_O2D {
				GLint	locTexture[32],
						locNumLights,
						*locLightPos,
						*locLightDir,
						*locLightDiffuse,
						*locLightAmbient,
						*locLightSpecular,
						*locLightAttenuation,
						*locLightType;

				GLint	locMVP,
						locMV,
						locMP,
						locObjPos,
						locCamPos;
			} phongO2D;
		} shaders;

		void * operator[](SHADER_PROGRAMS getShader) {
		switch(getShader) {
			case GLS_PHONG:
				return &shaders.phong;
				break;
			case GLS_PHONG_O2D:
				return &shaders.phongO2D;
				break;
			default:
				return nullptr;
			}
		}

		t_UniformLocations(SHADER_PROGRAMS newShader=GLS_BASE) {
			shader = newShader;
			bInit = false;
		}
	};

//	struct t_UniformLocation {
//		SHADER_PROGRAMS shader;
//
//		union u_Type {
//			struct t_PHONG {
//				GLint	locTexture,
//						locMVP,
//						locMV,
//						locMP,
//						locWater,
//						locNumLights,
//						*locLightPos,
//						*locLightDir,
//						*locLightDiffuse,
//						*locLightAmbient,
//						*locLightSpecular,
//						*locLightAttenuation,
//						*locLightType;
//			} phong;
//		} shaders;
//
//		void * operator[](SHADER_PROGRAMS getShader) {
//		switch(getShader) {
//			case GLS_PHONG:
//				return &shaders.phong;
//				break;
//			default:
//				return nullptr;
//			}
//		}
//
//		t_UniformLocation(SHADER_PROGRAMS newShader) {
//			shader = newShader;
//		}
//	};

	class Shader_System {
		private:
			Matrix_System	* matrix;
			GLuint uiShaders[GLS_LAST];
//			Vector4f * color;

		protected:
			void readSrc(const char *shaderSrc, GLuint shaderNum);

		public:

			/*
			 * Variable data for passing to shaders
			 *
			 * Different shaders may have settings
			 * that can change. This is here as the
			 * easiest method of accessing that data
			 */
			struct ShaderData {

				Vector2f * vRes;
				Vector3f * vPos;

				struct {
				} GLS_FONT;
				struct GLS_MENU {
					int			iRadius,
								iBorder;
					bool		bRoundBorder,
								bEnableStipple,
								bTextured;
					float		fScroll;
					Vector2f	vPos,
								vSize;

					Stipple_Pattern * stipple;
					Color *stippleColor;

					GLS_MENU() {
						iRadius = 0;
						iBorder = 1;
						bRoundBorder = false;
						bEnableStipple = false;
						bTextured = false;
						fScroll = 0.0f;
						stipple = nullptr;
						stippleColor = nullptr;
					}
				} GLS_MENU;
				struct {
				} GLS_ICON;
				struct {
				} GLS_MOUSERAY;
				struct {
				} GLS_POINTS;
				struct {
				} GLS_LINES;
				struct {
				} GLS_BOUNDINGVOLUME_OBB;
				struct {
				} GLS_BOUNDINGVOLUME_AABB;
				struct {
				} GLS_BOUNDINGVOLUME_SPHERE;
				struct {
				} GLS_BOUNDINGVOLUME_CYLINDER;
				struct {
				} GLS_FLAT;
				struct {
				} GLS_PHONG;
				struct {
					Core::Vector3f vObjPos;
					Core::Vector3f vCamPos;
				} GLS_PHONG_O2D;
				struct {
				} GLS_POINT_SPRITE;
				struct {
				} GLS_PARTICLE_SPRITE;
				//GLS_FLAT_FOG,
				//GLS_FLAT_FOG_SHEAR,
				//GLS_FLAT_FOG_INSTANCE,
				//GLS_SHADED_TEX,
				//GLS_SHADED_TEX_ALPHA,
				//GLS_NORMAL_LINE2,
				//GLS_DIRECTIONAL,
				//GLS_DIRECTIONAL_TERRAIN,
				//GLS_DIRECTIONAL_WATER,
				struct {
				} GLS_TROPOSPHERE;
				struct {
				} GLS_STRATOSPHERE;
				struct {
				} GLS_THERMOSPHERE;
				struct {
				} GLS_SUN;
				struct {
				} GLS_EXOSPHERE;
				struct {
				} GLS_SNOW;
				struct {
				} GLS_SNOW_3D;
				//GLS_RAIN,		// 3D Rain
				//GLS_HAIL,
				struct {
				} GLS_FLORA;
				//GLS_UWFLORA,
				//GLS_GRASS_TRI,
				//GLS_GRASS_LINE,
				//GLS_SCATTER,
				struct {
				} GLS_PP_CONTRAST;
				struct {
				} GLS_PP_BRIGHTNESS;
				struct {
				} GLS_PP_BRIGHTNESS_FILTER;
				//GLS_PP_UNDERWATER,
				struct {
				} GLS_PP_RADIALBLUR;
				struct {
				} GLS_PP_HBLUR;
				struct {
				} GLS_PP_VBLUR;
				//GLS_PP_RAYBLUR,
				//GLS_PP_BLOOM,
				//GLS_PP_DEPTHOFFIELD,
				//GLS_PP_VINETTE,
				//GLS_PP_LENSFLARE,
				//GLS_PP_EDGEDETECT,
				//GLS_PP_CARTOON,
				//GLS_PP_CELLSHADING,
				struct {
				} GLS_PP_COMBINE;
				//GLS_PP_PIXELATE,
				//GLS_PARTICLE,
			} vars;

//			struct t_GL_Attributes {
//				bool bSet;
//				enum {	NONE		= 0,
//						VERTEX,
////						COLOR,
////						NORMAL,
//						VERTEX_NORMAL,
//						VERTEX_TEXTURE0,
//						VERTEX_COLOR,
//						VERTEX_NORMAL_TEXTURE0
////						POSITION,
////						LAST
//					 };
//
//			} GLASet;

			struct t_GL_Attributes {
				bool bSet;
				enum {	NONE		= 0,
						VERTEX		= 1,
						COLOR		= 2,
						NORMAL		= 4,
						TEXTURE0	= 8,
						POSITION	= 16,
						DATA1		= 32,
						DATA2		= 64,
						DATA3		= 128,
						INDEX		= 256,
						LAST
					 };

			} GLASet;

//			struct ShaderData {
//				float * fData;
//				int * iData;
//				Vector2f * v2fData;
//				Vector4f * v4fData;
//			};

			Shader_System(Matrix_System &m) {
				Core::debug.log("Construct Shaders {");
				matrix = &m;
				debug = false;		// Show all shader loading data
				debug2 = true;		// Show only shader errors
				Core::debug.print(" Done ", Core::debug().YELLOW);
				Core::debug.print("}\n");
			}
			~Shader_System() {
				Core::debug.log("Destroy Shaders {");
				Core::debug.print(" Done ", Core::debug().YELLOW);
				Core::debug.print("}\n");
			}
			void SetMatrixSystem(Matrix_System &m) { matrix = &m; }
			bool debug;
			bool debug2;
//			void SetPos(Vector3f * v) { pos = v; }
//			void SetColor(Vector4f * c) { color = c; }

			struct {
				enum { VERTEX_SHADER, GEOMETRY_SHADER, FRAGMENT_SHADER };
			} TYPE;

			// TODO: This should be in the atmosphere
			struct _FogParams {
				Core::Vector4f	vFogColor;
				float		fStart;
				float		fEnd;
				float		fDensity;
				int			iEquation;
			} worldFog, waterFog, activeFog;

			//void init(Vector3f * vPos, Vector4f * vColor);
			void init(Vector2f * vRes, Vector3f * vPos);
			void load();
			void load(SHADER_PROGRAMS newShader);
			inline void use(SHADER_PROGRAMS eShader) { glUseProgram(uiShaders[eShader]); }

			//template<class ... Types> struct _GetUniform {};
			//_GetUniform<GLenum> t0;        		// Types contains one argument: int
			//_GetUniform<GLenum, int, float> t1; // Types contains two arguments: int and float
			//template<class ... Types> void getUniform(Types ... args);
			void getUniformVar(SHADER_PROGRAMS eShader, ...);
//			template <typename T>
			void getUniform(SHADER_PROGRAMS eShader);
			void getUniform(SHADER_PROGRAMS eShader, int iStyle, Color vColor, float fRotation, int iSpikes, float fThickness, float fBlend=0.0f, int iSize=1, Vector2f vTexCoord0=Vector2f(), Vector2f vTexCoord1=Vector2f());
//			void getUniform(SHADER_PROGRAMS eShader, _Lights *lightData, int n=0, ...);

			void getUniform(SHADER_PROGRAMS eShader, _Lights &lights, t_UniformLocations &uniforms);	///< Get uniform locations and store in t_UniformLocations
			void setUniform(SHADER_PROGRAMS eShader, _Lights &lights, t_UniformLocations &uniforms);	///< Read t_UniformLocations and set uniform shader values

			GLuint loadShader2(const char *vertSrc, const char *fragSrc, ...);
//			GLuint loadShader(const char *vertSrc, const char *geoSrc, const char *fragSrc, ...);
			GLuint loadShader(const char *vertSrc, const char *geoSrc, const char *fragSrc, uint uiGLA);
			std::string readShaderFile(std::string filePath, std::string filename, uint type);
	};
}
#endif /* SHADER_H_ */
