// System includes
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdarg.h>

//OpenGL and SDL
#define GL_GLEXT_PROTOTYPES 1		// Enable core profile
#include "gl4_5/glcorearb.h"

// Core includes
#include "./types.h"
#include "./matrix.h"
#include "./Colors.h"
#include "./lights.h"

// This class include(s)
#include "./shader.h"

namespace Core {
	std::string Shader_System::readShaderFile(std::string filePath, std::string fileName, uint type) {
		std::string content;
		//std::string filePath = Core::gameVars.dir.shaders;

		if(type == TYPE.VERTEX_SHADER) {
			filePath += fileName + ".glslv";
		} else if(type == TYPE.GEOMETRY_SHADER) {
			filePath += fileName + ".glslg";
		} else if(type == TYPE.FRAGMENT_SHADER) {
			filePath += fileName + ".glslf";
		}

		std::ifstream fileStream(filePath, std::ios::in);

		//cout << "------------------------------------------------------------------------------" << endl;
		if(!fileStream.is_open()) {
			std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
			return "";
		}

		std::string line = "";
		while(!fileStream.eof()) {
			std::getline(fileStream, line);
			content.append(line + "\n");
			//cout << line << endl;
		}
		//cout << "------------------------------------------------------------------------------" << endl;

		fileStream.close();

		return content;
	}

//	void Shader_System::init(Vector3f * vPos, Vector4f * vColor) {
	void Shader_System::init(Vector2f * vRes, Vector3f * vPos) {
		data.vRes = vRes;
		data.vPos = vPos;
//		color = vColor;
	}

	void Shader_System::load() {
		Core::debug.log("Init Shaders {\n");
		Core::debug.logIncreaseIndent();
		for (int n=0; n<GLS_LAST; n++) {
			Core::shader->load(SHADER_PROGRAMS(n));
		}
		Core::debug.logDecreaseIndent();
		Core::debug.log("}\n");
	}

	void Shader_System::load(SHADER_PROGRAMS newShader) {
		//            .................................................................Done
		GLenum setShader = newShader;

		std::string	sFileName	= "",
				sShaderFile		= "",
				sVertShader		= "",
				sFragShader		= "",
				sGeoShader		= "";

		struct {
			bool bSet;
			enum {	NONE = 0,
					VERTEX,
					VERTEX_COLOR,
					VERTEX_NORMAL,
					VERTEX_TEXTURE0,
					VERTEX_NORMAL_TEXTURE0,
					VERTEX_NORMAL_POSITION_EXTRA,
					VERTEX_POSITION_EXTRA_TEXTURE0,
					LAST
				 };
		} GLASet;
		if (!GLASet.bSet) { GLASet.bSet = true; }		// This line just gets rid of the "Set but not used warning" for the above struct

		uint	uiGLA = GLASet.NONE;	// What attributes are lodaded?

		switch(newShader) {
			case(Core::GLS_FONT):
				sFileName	= "font";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX_TEXTURE0;
				//if (debug2) cout << "Loading Shader '" << sFileName << "'" << endl;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				//sGeoShader	= readShaderFile("./shaders/", sFileName, TYPE.GEOMETRY_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_MENU):
				sFileName	= "menu";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX_TEXTURE0;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_BOUNDINGVOLUME_OBB):
				sFileName	= "bounding_volume_obb";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX;
				//cout << "Loading Shader '" << sFileName << "'" << endl;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				//sGeoShader	= readShaderFile("./shaders/", sFileName, TYPE.GEOMETRY_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_BOUNDINGVOLUME_AABB):
				sFileName	= "bounding_volume_aabb";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX;
				//cout << "Loading Shader '" << sFileName << "'" << endl;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				//sGeoShader	= readShaderFile("./shaders/", sFileName, TYPE.GEOMETRY_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_BOUNDINGVOLUME_SPHERE):
				sFileName	= "bounding_volume_sphere";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX;
				//cout << "Loading Shader '" << sFileName << "'" << endl;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				//sGeoShader	= readShaderFile("./shaders/", sFileName, TYPE.GEOMETRY_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_BOUNDINGVOLUME_CYLINDER):
				sFileName	= "bounding_volume_cylinder";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX;
				//cout << "Loading Shader '" << sFileName << "'" << endl;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				//sGeoShader	= readShaderFile("./shaders/", sFileName, TYPE.GEOMETRY_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
//			case(Core::GLS_PP_UNDERWATER):
//				sFileName	= "pp_underwater";
//				uiGLA		= GLASet.VERTEX_TEXTURE0;

//				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
//				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
//				break;
			case(Core::GLS_ICON):
				sFileName	= "icon";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX_TEXTURE0;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_MOUSERAY):
				sFileName	= "mouseray";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX_COLOR;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_LINES):
				sFileName	= "lines";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX_COLOR;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_POINTS):
				sFileName	= "points";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_SUN):
				sFileName	= "sun";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX_TEXTURE0;
				//cout << "Loading Shader '" << sFileName << "'" << endl;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_FLAT):
				sFileName	= "flat";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX_NORMAL_TEXTURE0;
				//if (debug2) cout << "Loading Shader '" << sFileName << "'" << endl;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_PHONG):
				sFileName	= "phong";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX_NORMAL_TEXTURE0;
				//if (debug2) cout << "Loading Shader '" << sFileName << "'" << endl;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_PHONG_O2D):
				sFileName	= "phongO2D";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX_NORMAL_TEXTURE0;
				//if (debug2) cout << "Loading Shader '" << sFileName << "'" << endl;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
//			case(Core::GLS_FLAT_FOG):
//				sFileName	= "flat_fog";
//				uiGLA		= GLASet.VERTEX_TEXTURE0;
//				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
//				sGeoShader	= readShaderFile("./shaders/", sFileName, TYPE.GEOMETRY_SHADER);
//				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
//				break;
//			case(Core::GLS_FLAT_FOG_SHEAR):
//				sFileName	= "flat_fog_shear";
//				uiGLA		= GLASet.VERTEX_TEXTURE0;
//				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
//				sGeoShader	= readShaderFile("./shaders/", sFileName, TYPE.GEOMETRY_SHADER);
//				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
//				break;
//			case(Core::GLS_FLAT_FOG_INSTANCE):
//				sFileName	= "flat_fog_instance";
//				uiGLA		= GLASet.VERTEX_POSITION_EXTRA_TEXTURE0;
//				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
//				sGeoShader	= readShaderFile("./shaders/", sFileName, TYPE.GEOMETRY_SHADER);
//				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
//				break;
			case(Core::GLS_NORMAL_LINE2):
				sFileName	= "normal_line2";
				uiGLA		= GLASet.VERTEX_NORMAL;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sGeoShader	= readShaderFile("./shaders/", sFileName, TYPE.GEOMETRY_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
//			case(Core::GLS_SHADED_TEX):
//				sFileName	= "shaded_tex";
//				uiGLA		= GLASet.VERTEX_TEXTURE0;
//				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
//				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
//				break;
//			case(Core::GLS_SHADED_TEX_ALPHA):
//				sFileName	= "shaded_tex_alpha";
//				uiGLA		= GLASet.VERTEX_TEXTURE0;
//				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
//				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
//				break;
//			case(Core::GLS_DIRECTIONAL_TERRAIN):
//				sFileName	= "directional_terrain";
//				uiGLA		= GLASet.VERTEX_NORMAL_TEXTURE0;
//				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
//				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
//				break;
//			case(Core::GLS_DIRECTIONAL):
//				sFileName	= "directional";
//				uiGLA		= GLASet.VERTEX_NORMAL_TEXTURE0;
//				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
//				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
//				break;
//			case(Core::GLS_DIRECTIONAL_WATER):
//				sFileName	= "directional_water";
//				uiGLA		= GLASet.VERTEX_NORMAL_TEXTURE0;
//				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
//				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
//				break;
			case(Core::GLS_TROPOSPHERE):
				sFileName	= "troposphere";
				uiGLA		= GLASet.VERTEX_NORMAL_TEXTURE0;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_STRATOSPHERE):
				sFileName	= "stratosphere";
				uiGLA		= GLASet.VERTEX_NORMAL_TEXTURE0;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_THERMOSPHERE):
				sFileName	= "thermosphere";
				uiGLA		= GLASet.VERTEX_NORMAL_TEXTURE0;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_EXOSPHERE):
				sFileName	= "exosphere";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX_TEXTURE0;

				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_SNOW):
				sFileName	= "snow";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_SNOW_3D):
				sFileName	= "snow_3d";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_POINT_SPRITE):
				sFileName	= "point_sprite";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_PARTICLE_SPRITE):
				sFileName	= "particle_sprite";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
//			case(Core::GLS_HAIL):
//				sFileName	= "hail";
//				uiGLA		= GLASet.VERTEX;
//				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
//				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
//				break;
//			case(Core::GLS_RAIN):
//				sFileName	= "rain";
//				uiGLA		= GLASet.VERTEX;
//				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
//				sGeoShader	= readShaderFile("./shaders/", sFileName, TYPE.GEOMETRY_SHADER);
//				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
//				break;
			case(Core::GLS_FLORA):
				sFileName	= "flora";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX_NORMAL;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sGeoShader	= readShaderFile("./shaders/", sFileName, TYPE.GEOMETRY_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
//			case(Core::GLS_UWFLORA):
//				sFileName	= "uwflora";
//				uiGLA		= GLASet.VERTEX_NORMAL;
//				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
//				sGeoShader	= readShaderFile("./shaders/", sFileName, TYPE.GEOMETRY_SHADER);
//				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
//				break;
//			case(Core::GLS_GRASS_TRI):
//				sFileName	= "grass_tri";
//				uiGLA		= GLASet.VERTEX_NORMAL_POSITION_EXTRA;
//				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
//				sGeoShader	= readShaderFile("./shaders/", sFileName, TYPE.GEOMETRY_SHADER);
//				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
//				break;
//			case(Core::GLS_GRASS_LINE):
//				sFileName	= "grass_line";
//				uiGLA		= GLASet.VERTEX_NORMAL_POSITION_EXTRA;
//				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
//				sGeoShader	= readShaderFile("./shaders/", sFileName, TYPE.GEOMETRY_SHADER);
//				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
//				break;
			case(Core::GLS_PP_CONTRAST):
				sFileName	= "pp_contrast";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX_TEXTURE0;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_PP_BRIGHTNESS):
				sFileName	= "pp_brightness";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX_TEXTURE0;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_PP_BRIGHTNESS_FILTER):
				sFileName	= "pp_brightness_filter";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX_TEXTURE0;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_PP_RADIALBLUR):
				sFileName	= "pp_radial_blur";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX_TEXTURE0;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_PP_HBLUR):
				sFileName	= "pp_hblur";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX_TEXTURE0;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_PP_VBLUR):
				sFileName	= "pp_vblur";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX_TEXTURE0;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
			case(Core::GLS_PP_COMBINE):
				sFileName	= "pp_combine";
//				std::cout << sOffset << "[" << sFileName << "]";
				uiGLA		= GLASet.VERTEX_TEXTURE0;
				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
				break;
//			case(Core::GLS_PP_LENSFLARE):
//				sFileName	= "pp_lensflare";
//				uiGLA		= GLASet.VERTEX_TEXTURE0;
//				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
//				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
//				break;
//			case(Core::GLS_PP_DEPTHOFFIELD):
//				sFileName	= "pp_dof";
//				uiGLA		= GLASet.VERTEX_TEXTURE0;

//				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
//				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
//				break;
//			case(Core::GLS_PP_CARTOON):
//				sFileName	= "pp_cartoon";
//				uiGLA		= GLASet.VERTEX_TEXTURE0;
//				sVertShader	= readShaderFile("./shaders/", sFileName, TYPE.VERTEX_SHADER);
//				sFragShader	= readShaderFile("./shaders/", sFileName, TYPE.FRAGMENT_SHADER);
//				break;
			default:
//				std::cout << sOffset << "[" << newShader << "] Not Defined";
				//sFileName = '\''+newShader+"' Not Defined";
//				sFileName = "'";
//				sFileName.append(newShader+"' Not Defined");
				sFileName = "Not Defined";
		}

		Core::debug.log("["+std::to_string(setShader)+"] "+sFileName+"\n", Core::debug().YELLOW);

		/*
		 * Gawdy but still simplifies the code a lot
		 *
		 * Geometry shader is automatically
		 * 	skipped if it is equal to "".
		 * 	(first char equal to \0)
		 */
		if(uiGLA == GLASet.VERTEX) {
			uiShaders[setShader] = loadShader(	sVertShader.c_str(),
												sGeoShader.c_str(),
												sFragShader.c_str(),
												1,
												GLA_VERTEX,		"vVertex");
		} else if(uiGLA == GLASet.VERTEX_COLOR) {
			uiShaders[setShader] = loadShader(	sVertShader.c_str(),
												sGeoShader.c_str(),
												sFragShader.c_str(),
												2,
												GLA_VERTEX,		"vVertex",
												GLA_COLOR,		"vColor");
		} else if(uiGLA == GLASet.VERTEX_NORMAL) {
			uiShaders[setShader] = loadShader(	sVertShader.c_str(),
												sGeoShader.c_str(),
												sFragShader.c_str(),
												2,
												GLA_VERTEX,		"vVertex",
												GLA_NORMAL,		"vNormal");
		} else if(uiGLA == GLASet.VERTEX_TEXTURE0) {
			uiShaders[setShader] = loadShader(	sVertShader.c_str(),
												sGeoShader.c_str(),
												sFragShader.c_str(),
												2,
												GLA_VERTEX,		"vVertex",
												GLA_TEXTURE0,	"vTexCoords");
		} else if(uiGLA == GLASet.VERTEX_NORMAL_TEXTURE0) {
			uiShaders[setShader] = loadShader(	sVertShader.c_str(),
												sGeoShader.c_str(),
												sFragShader.c_str(),
												3,
												GLA_VERTEX,		"vVertex",
												GLA_NORMAL,		"vNormal",
												GLA_TEXTURE0,	"vTexCoords");
		} else if(uiGLA == GLASet.VERTEX_POSITION_EXTRA_TEXTURE0) {
			uiShaders[setShader] = loadShader(	sVertShader.c_str(),
												sGeoShader.c_str(),
												sFragShader.c_str(),
												4,
												GLA_VERTEX,		"vVertex",
												GLA_POSITION,	"vOffset",
												GLA_EXTRA,		"vExtra",
												GLA_TEXTURE0,	"vTexCoords");
		} else if(uiGLA == GLASet.VERTEX_NORMAL_POSITION_EXTRA) {
			uiShaders[setShader] = loadShader(	sVertShader.c_str(),
												sGeoShader.c_str(),
												sFragShader.c_str(),
												4,
												GLA_VERTEX,		"vVertex",
												GLA_NORMAL,		"vNormal",
												GLA_POSITION,	"vOffset",
												GLA_EXTRA,		"vExtra");
		}

		//std::cout << "Done" << std::endl;
//		std::cout << std::endl;
	}

	/*
	 * Shaders without lighting (menu, overlays)
	 * or shaders with global lights
	 *
	 * Light object [0] is always global "sun"
	 */

	// Variadic
	// TODO: Remove variadic function
	void Shader_System::getUniformVar(SHADER_PROGRAMS eShader, ...) {
		GLint locTexture0,
			  locTexture1,
			  locColor,
			  locMVP;

		try {
//			if(		eShader==Core::GLS_MENU ) {
//				locColor =		glGetUniformLocation(uiShaders[eShader], "vColor");
//				locMVP =		glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
//
//				glUniform4fv(locColor,		1,	colors->GetActiveColor().data);
//				glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection().data);
//
////				std::cout << "3 (" << colors->GetActiveColor().data[0] << ", " << colors->GetActiveColor().data[1] << ", " << colors->GetActiveColor().data[2] << ")" << std::endl;
//
//				va_list attributeList;
//				va_start(attributeList, eShader);
//					int iRadius = va_arg(attributeList, int);
//					GLint locRadius = glGetUniformLocation(uiShaders[eShader], "iRadius");
//					glUniform1i(locRadius, iRadius);
//
//					int iBorder = va_arg(attributeList, int);
//					GLint locBorder = glGetUniformLocation(uiShaders[eShader], "iBorder");
//					glUniform1i(locBorder, iBorder);
//				va_end(attributeList);
//			}

			if( eShader == Core::GLS_POINTS ) {
				locMVP =		glGetUniformLocation(uiShaders[eShader], "mvpMatrix");

				glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection().data);

				va_list attributeList;
				va_start(attributeList, eShader);
					int iStyle = va_arg(attributeList, int);
					GLint locStyle = glGetUniformLocation(uiShaders[eShader], "iStyle");
					glUniform1i(locStyle, iStyle);

					Vector4f vColor = va_arg(attributeList, Vector4f);
					locColor = glGetUniformLocation(uiShaders[eShader], "vColor");
					glUniform4fv(locColor, 1, vColor.data);

					int iSpikes = va_arg(attributeList, int);
					GLint locSpikes = glGetUniformLocation(uiShaders[eShader], "iSpikes");
					glUniform1i(locSpikes, iSpikes);

					float fThickness = va_arg(attributeList, double);
					GLint locThickness = glGetUniformLocation(uiShaders[eShader], "fThickness");
					glUniform1f(locThickness, fThickness);
				va_end(attributeList);

				return;
			}

			if( eShader==Core::GLS_PP_CONTRAST) {
				locTexture0				= glGetUniformLocation(uiShaders[eShader], "colorMap");
				locMVP					= glGetUniformLocation(uiShaders[eShader], "mvpMatrix");

				va_list attributeList;
				va_start(attributeList, eShader);
					float fContrast = va_arg(attributeList, double);
					GLint locContrast = glGetUniformLocation(uiShaders[eShader], "contrast");
					glUniform1f(locContrast, fContrast);
				va_end(attributeList);

				glUniform1i(locTexture0,	0);
				glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection().data);
				return;
			}

			if( eShader==Core::GLS_PP_BRIGHTNESS) {
				locTexture0 =		glGetUniformLocation(uiShaders[eShader], "colorMap");
				locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");

				glUniform1i(locTexture0,	0);
				glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection().data);

				va_list attributeList;
				va_start(attributeList, eShader);
					Vector3f fBrightness = va_arg(attributeList, Vector3f);
					GLint locBrightness = glGetUniformLocation(uiShaders[eShader], "brightness");
					glUniform3fv(locBrightness, 1, fBrightness.data);
				va_end(attributeList);

				return;
			}

			if( eShader==Core::GLS_PP_BRIGHTNESS_FILTER) {
				locTexture0 =		glGetUniformLocation(uiShaders[eShader], "colorMap");
				locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");

				glUniform1i(locTexture0,	0);
				glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection().data);

				va_list attributeList;
				va_start(attributeList, eShader);
					Vector3f fFactor = va_arg(attributeList, Vector3f);
					GLint locFactor = glGetUniformLocation(uiShaders[eShader], "factor");
					glUniform3fv(locFactor, 1, fFactor.data);

					float fMax = va_arg(attributeList, double);
					GLint locMax = glGetUniformLocation(uiShaders[eShader], "fMax");
					glUniform1f(locMax, fMax);
				va_end(attributeList);
				return;
			}

			if( eShader==Core::GLS_PP_HBLUR || eShader==Core::GLS_PP_VBLUR) {
				locTexture0 =		glGetUniformLocation(uiShaders[eShader], "colorMap");
				locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");

				glUniform1i(locTexture0,	0);
				glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection().data);

				va_list attributeList;
				va_start(attributeList, eShader);
					int iResolution = va_arg(attributeList, int);
					GLint locResolution = glGetUniformLocation(uiShaders[eShader], "resolution");
					glUniform1i(locResolution, iResolution);
				va_end(attributeList);

				return;
			}

			if( eShader==Core::GLS_PP_RADIALBLUR) {
				locTexture0 =		glGetUniformLocation(uiShaders[eShader], "colorMap");
				locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");

				glUniform1i(locTexture0,	0);
				glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection().data);

				va_list attributeList;
				va_start(attributeList, eShader);
					int iResolution = va_arg(attributeList, int);
					GLint locResolution = glGetUniformLocation(uiShaders[eShader], "resolution");
					glUniform1i(locResolution, iResolution);
				va_end(attributeList);

				return;
			}

			if( eShader==Core::GLS_PP_COMBINE) {
				locTexture0 =		glGetUniformLocation(uiShaders[eShader], "colorMap0");
				locTexture1 =		glGetUniformLocation(uiShaders[eShader], "colorMap1");
				locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");

				glUniform1i(locTexture0,	0);
				glUniform1i(locTexture1,	1);
				glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection().data);

				va_list attributeList;
				va_start(attributeList, eShader);
					float fIntensity = va_arg(attributeList, double);
					GLint locIntensity = glGetUniformLocation(uiShaders[eShader], "intensity");
					glUniform1f(locIntensity, fIntensity);
				va_end(attributeList);

				return;
			}

//			if(eShader==Core::GLS_POINT_SPRITE) {
//				locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
//				locTexture0 =		glGetUniformLocation(uiShaders[eShader], "colorMap");
//
//				glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection().data);
//				glUniform1i(locTexture0,	0);
//
//				va_list attributeList;
//				va_start(attributeList, eShader);
//					int iStyle = va_arg(attributeList, int);
//					GLint locStyle = glGetUniformLocation(uiShaders[eShader], "iStyle");
//					glUniform1i(locStyle, iStyle);
//
//					Vector4f vColor = va_arg(attributeList, Vector4f);
//					locColor = glGetUniformLocation(uiShaders[eShader], "vColor");
//					glUniform4fv(locColor, 1, vColor.data);
//
//					float fRotation = va_arg(attributeList, double);
//					GLint locRotation = glGetUniformLocation(uiShaders[eShader], "fAngle");
//					glUniform1f(locRotation, fRotation);
//
//					int iSpikes = va_arg(attributeList, int);
//					GLint locSpikes = glGetUniformLocation(uiShaders[eShader], "iSpikes");
//					glUniform1i(locSpikes, iSpikes);
//
//					float fThickness = va_arg(attributeList, double);
//					GLint locThickness = glGetUniformLocation(uiShaders[eShader], "fThickness");
//					glUniform1f(locThickness, fThickness);
//
//				va_end(attributeList);
//			}
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

	}

	// Non-variadic
	void Shader_System::getUniform(SHADER_PROGRAMS eShader) {
		GLint locCamPos,
			  locTexture0,
			  locColor,
			  locMVP,
			  locMV,
			  locMP,
			  locWorldPos;

		try {
			if(		eShader==Core::GLS_FONT ||
					eShader==Core::GLS_ICON ||
					eShader==Core::GLS_EXOSPHERE ||
					eShader==Core::GLS_THERMOSPHERE ||
					eShader==Core::GLS_TROPOSPHERE ||
					eShader==Core::GLS_STRATOSPHERE ||
					eShader==Core::GLS_SUN /*|| eShader==Core::GLS_BASE || eShader==Core::GLS_SHADED_TEX || eShader==Core::GLS_SHADED_TEX_ALPHA*/) {
				locColor =		glGetUniformLocation(uiShaders[eShader], "vColor");
				locWorldPos =	glGetUniformLocation(uiShaders[eShader], "vWorldPos");
				locTexture0 =	glGetUniformLocation(uiShaders[eShader], "colorMap");
				locMVP =		glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
				locMV =			glGetUniformLocation(uiShaders[eShader], "mvMatrix");
				locMP =			glGetUniformLocation(uiShaders[eShader], "mpMatrix");

				//Vector3f vfPos = { -Core::gameVars.player.active->transform.pos[0], 0.0f, -Core::gameVars.player.active->transform.pos[2] };
				glUniform3fv(locWorldPos,	1,	data.vPos->data);
				glUniform4fv(locColor,		1,	colors.GetActive().data);
				glUniform1i(locTexture0,	0);
				glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection().data);
				glUniformMatrix4fv(locMV,	1,	GL_FALSE,	matrix->GetModelView().data);
				glUniformMatrix4fv(locMP,	1,	GL_FALSE,	matrix->GetProjectionMatrix().data);
			}

			if(	eShader==Core::GLS_MENU ) {
				GLint locRes			= glGetUniformLocation(uiShaders[eShader], "vRes");
				GLint locPos			= glGetUniformLocation(uiShaders[eShader], "vPos");
				GLint locSize			= glGetUniformLocation(uiShaders[eShader], "vSize");
				locMVP					= glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
				GLint locRadius 		= glGetUniformLocation(uiShaders[eShader], "iRadius");
				GLint locBorder 		= glGetUniformLocation(uiShaders[eShader], "iBorder");
				GLint locRBorder		= glGetUniformLocation(uiShaders[eShader], "bRoundBorder");
				GLint locWindowColor	= glGetUniformLocation(uiShaders[eShader], "vWindowColor");
				GLint locBorderColor	= glGetUniformLocation(uiShaders[eShader], "vBorderColor");
				GLint locEnableStipple	= glGetUniformLocation(uiShaders[eShader], "bEnableStipple");
				GLint locStippleSize	= glGetUniformLocation(uiShaders[eShader], "stippleSize");
				GLint locStipplePattern	= glGetUniformLocation(uiShaders[eShader], "stipplePattern");
				GLint locStippleColor	= glGetUniformLocation(uiShaders[eShader], "stippleColor");
				GLint locStippleScale	= glGetUniformLocation(uiShaders[eShader], "stippleScale");
				GLint locTextured		= glGetUniformLocation(uiShaders[eShader], "bTextured");
				if(data.GLS_MENU.bTextured) {
					locTexture0			= glGetUniformLocation(uiShaders[eShader], "colorMap");
					GLint locScroll 	= glGetUniformLocation(uiShaders[eShader], "fScroll");
					glUniform1i(locTexture0,	0);
					glUniform1f(locScroll, data.GLS_MENU.fScroll);
				}

				glUniform2fv(locRes,			1,	data.vRes->data);
				glUniform2fv(locPos,			1,	data.GLS_MENU.vPos.data);
				glUniform2fv(locSize,			1,	data.GLS_MENU.vSize.data);
				glUniformMatrix4fv(locMVP,		1,	GL_FALSE,	matrix->GetModelViewProjection().data);
				glUniform1i(locRadius, 			data.GLS_MENU.iRadius);
				glUniform1i(locBorder, 			data.GLS_MENU.iBorder);
				glUniform1i(locRBorder, 		data.GLS_MENU.bRoundBorder);
				glUniform4fv(locWindowColor,	1,	colors.GetFront().data);
				glUniform4fv(locBorderColor,	1,	colors.GetBack().data);
				glUniform1i(locEnableStipple, 	data.GLS_MENU.bEnableStipple);
				glUniform1i(locTextured, 		data.GLS_MENU.bTextured);

				if(data.GLS_MENU.bEnableStipple) {
					glUniform2iv(locStippleSize, 1,	data.GLS_MENU.stipple->size.data);
					glUniform1iv(locStipplePattern, data.GLS_MENU.stipple->size.area(),	data.GLS_MENU.stipple->pattern);
					glUniform4fv(locStippleColor,	1,	data.GLS_MENU.stippleColor->data);
				}
			}

			if(	eShader == Core::GLS_NORMAL_LINE2) {
				locWorldPos =		glGetUniformLocation(uiShaders[eShader], "vWorldPos");
				locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");

				//Vector3f vfPos = { -Core::gameVars.player.active->transform.pos[0], 0.0f, -Core::gameVars.player.active->transform.pos[2] };

				glUniform3fv(locWorldPos,	1,	data.vPos->data);
				glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection().data);
			}

			if( eShader == Core::GLS_MOUSERAY ) {
				locMVP =		glGetUniformLocation(uiShaders[eShader], "mvpMatrix");

				glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection().data);
				return;
			}

			if( eShader == Core::GLS_LINES ) {
				locMVP =		glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
				glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection().data);

				GLint locColorA = glGetUniformLocation(uiShaders[eShader], "vColorA");
				GLint locColorB = glGetUniformLocation(uiShaders[eShader], "vColorB");
				return;
			}

			if( eShader == Core::GLS_BOUNDINGVOLUME_OBB ) {
				locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
				glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection().data);
				return;
			}

			if( eShader == Core::GLS_BOUNDINGVOLUME_AABB ) {
				locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
				glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection().data);
				return;
			}

			if( eShader == Core::GLS_BOUNDINGVOLUME_SPHERE ) {
				locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
				glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection().data);
				return;
			}

			if( eShader == Core::GLS_BOUNDINGVOLUME_CYLINDER ) {
				locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
				glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection().data);
				return;
			}

			if(eShader==Core::GLS_FLORA) {
				// TODO: Add lighting to flora
				locCamPos =			glGetUniformLocation(uiShaders[eShader], "vPos");
				locMP =				glGetUniformLocation(uiShaders[eShader], "mpMatrix");
				locMV =				glGetUniformLocation(uiShaders[eShader], "mvMatrix");
	//			locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
	//			locTime =			glGetUniformLocation(uiShaders[eShader], "fTime");
				locTexture0 =		glGetUniformLocation(uiShaders[eShader], "colorMap");
	//			locMoonDiffuse =	glGetUniformLocation(uiShaders[eShader], "vMoonDiffuse");
	//			locSunDiffuse =		glGetUniformLocation(uiShaders[eShader], "vSunDiffuse");

	//			glUniform4fv(locMoonDiffuse,	1,		a.moon.vDiffuseColor.data);
	//			glUniform4fv(locSunDiffuse,		1,		a.sun.vDiffuseColor.data);



				//Vector3f vfPos = { -Core::gameVars.player.active->transform.pos[0], -Core::gameVars.player.active->transform.pos[1], -Core::gameVars.player.active->transform.pos[2] };
				glUniform3fv(locCamPos,		1,	data.vPos->data);
				glUniformMatrix4fv(locMP,	1,	GL_FALSE,	matrix->GetProjectionMatrix().data);
				glUniformMatrix4fv(locMV,	1,	GL_FALSE,	matrix->GetModelView().data);
	//			glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection());
	//			glUniform1f(locTime,		a.gameTime.get_ticks());
				glUniform1i(locTexture0,	0);
			}

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

	}

	/*
	 * Shader specific calls, without variadic call
	 * Also allows defaults
	 */
	// Point and Particle Point Sprites
	void Shader_System::getUniform(SHADER_PROGRAMS eShader, int iStyle, Color vColor, float fRotation, int iSpikes, float fThickness, float fBlend, int iSize, Vector2f vTexCoord0, Vector2f vTexCoord1) {
		//GLfloat	fTime;
		GLint locTexture0,
			  locColor,
			  locMVP,
			  locTexCoord0,
			  locTexCoord1;

		try {
			if(eShader==Core::GLS_POINT_SPRITE || eShader==Core::GLS_PARTICLE_SPRITE) {
				locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
				locTexture0 =		glGetUniformLocation(uiShaders[eShader], "colorMap");

				glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection().data);
				glUniform1i(locTexture0,	0);

				GLint locStyle = glGetUniformLocation(uiShaders[eShader], "iStyle");
				glUniform1i(locStyle, iStyle);

				locColor = glGetUniformLocation(uiShaders[eShader], "vColor");
				glUniform4fv(locColor, 1, vColor.data);

				GLint locRotation = glGetUniformLocation(uiShaders[eShader], "fAngle");
				glUniform1f(locRotation, fRotation);

				GLint locSpikes = glGetUniformLocation(uiShaders[eShader], "iSpikes");
				glUniform1i(locSpikes, iSpikes);

				GLint locThickness = glGetUniformLocation(uiShaders[eShader], "fThickness");
				glUniform1f(locThickness, fThickness);

				if(eShader==Core::GLS_PARTICLE_SPRITE) {
					GLint locBlend = glGetUniformLocation(uiShaders[eShader], "fBlend");
					glUniform1f(locBlend, fBlend);

					GLint locSize = glGetUniformLocation(uiShaders[eShader], "iSize");
					glUniform1i(locSize, iSize);

					locTexCoord0 = glGetUniformLocation(uiShaders[eShader], "vTexCoord0");
					locTexCoord1 = glGetUniformLocation(uiShaders[eShader], "vTexCoord1");
					glUniform2fv(locTexCoord0, 1, vTexCoord0.data);
					glUniform2fv(locTexCoord1, 1, vTexCoord1.data);
				}
			}
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

	}

	/*
	 * Shaders with lighting
	 */
	void Shader_System::getUniform(SHADER_PROGRAMS eShader, _Lights *lights, int n, ...) {
		GLint //locEyeVec,
			  //locShiny,
			  //locFogColor,
			  //locFogStart,
			  //locFogEnd,
			  //locFogDensity,
			  //locFogEquation,
			  locCamPos,
			  locTexture0,
			  locTexture1,
			  locTexture2,
			  locTexture3,
			  locTexture4,
			  locTexture5,
			  locTexture6,
			  locTexture7,
			  locObjPos,
			  //locShadow,
			  locColor,
			  *locLightPos,
			  *locLightDir,
			  *locLightDiffuse,
			  *locLightAmbient,
			  *locLightSpecular,
			  *locLightAttenuation,
			  *locLightType,
			  locNumLights,
			  //locLightDir,
			  //locClipPlane,
			  locMVP,
			  locMV,
			  locMP,
			  locNM,
			  //locAmbient,
			  //locDiffuse,
			  //locSpecular,
			  //locNM,
			  locWorldPos;

		// Get location pointers for lights ready
		uint uiNumLights = lights->GetNumLights();
		if (uiNumLights>0) {
			locLightPos			= new GLint[uiNumLights];
			locLightDir			= new GLint[uiNumLights];
			locLightDiffuse		= new GLint[uiNumLights];
			locLightAmbient		= new GLint[uiNumLights];
			locLightSpecular	= new GLint[uiNumLights];
			locLightAttenuation = new GLint[uiNumLights];
			locLightType		= new GLint[uiNumLights];
		}
		else {
			locLightPos			= nullptr;
			locLightDir			= nullptr;
			locLightDiffuse		= nullptr;
			locLightAmbient		= nullptr;
			locLightSpecular	= nullptr;
			locLightAttenuation = nullptr;
			locLightType		= nullptr;
		}

		if(eShader==Core::GLS_FLAT || eShader==Core::GLS_PHONG_O2D) {
			locTexture0	= glGetUniformLocation(uiShaders[eShader], "colorMap");
			locMVP		= glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
			locMV		= glGetUniformLocation(uiShaders[eShader], "mvMatrix");
			locMP		= glGetUniformLocation(uiShaders[eShader], "mpMatrix");

			glUniform1i(locTexture0,	0);

			glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection().data);
			glUniformMatrix4fv(locMV,	1,	GL_FALSE,	matrix->GetModelView().data);
			glUniformMatrix4fv(locMP,	1,	GL_FALSE,	matrix->GetProjectionMatrix().data);

			if(eShader==Core::GLS_PHONG_O2D) {
				try {
					va_list attributeList;
					va_start(attributeList, n);
					if (n>=1) {
						locObjPos	= glGetUniformLocation(uiShaders[eShader], "vObjPos");
						Core::Vector3f v1 = va_arg(attributeList, Core::Vector3f);
						glUniform3fv(locObjPos, 			1,	v1.data);
						//std::cout << "ObjPos Set (" << v1.x << ", " << v1.y << ", " << v1.z << ")" << std::endl;
					}

					if (n>=2) {
						locCamPos	= glGetUniformLocation(uiShaders[eShader], "vCamPos");
						Core::Vector3f v2 = va_arg(attributeList, Core::Vector3f);
						glUniform3fv(locCamPos, 			1,	v2.data);
						//std::cout << "CamPos Set (" << v2.x << ", " << v2.y << ", " << v2.z << ")" << std::endl << std::endl;
					}
					va_end(attributeList);
				}
				catch( char * str ) {
					abort();
				}
			}

			locNumLights			= glGetUniformLocation(uiShaders[eShader], "iNumLights");
			glUniform1i(locNumLights,				lights->GetNumLights());
			for(int light=0; light<lights->GetNumLights(); light++) {
				//if(lights->GetLightLoaded(0)) {
					std::string sLight = std::to_string(light);
					locLightPos[light]			= glGetUniformLocation(uiShaders[eShader], std::string("vLightPos["+sLight+"]").c_str());
					locLightDir[light]			= glGetUniformLocation(uiShaders[eShader], std::string("vLightDir["+sLight+"]").c_str());
					locLightDiffuse[light]		= glGetUniformLocation(uiShaders[eShader], std::string("vDiffuseColor["+sLight+"]").c_str());
					locLightAmbient[light]		= glGetUniformLocation(uiShaders[eShader], std::string("vAmbientColor["+sLight+"]").c_str());
					locLightSpecular[light]		= glGetUniformLocation(uiShaders[eShader], std::string("vSpecularColor["+sLight+"]").c_str());
					locLightAttenuation[light]	= glGetUniformLocation(uiShaders[eShader], std::string("vAttenuation["+sLight+"]").c_str());
					locLightType[light]			= glGetUniformLocation(uiShaders[eShader], std::string("iType["+sLight+"]").c_str());

					glUniform3fv(locLightPos[light], 			1,	lights->GetPos(light).data);
					glUniform3fv(locLightDir[light], 			1,	lights->GetDir(light).data);
					glUniform3fv(locLightDiffuse[light],		1,	lights->GetDiffuse(light).data);
					glUniform3fv(locLightAmbient[light],		1,	lights->GetAmbient(light).data);
					glUniform3fv(locLightSpecular[light],		1,	lights->GetSpecular(light).data);
					glUniform3fv(locLightAttenuation[light],	1,	lights->GetAttenuation(light).data);
					glUniform1i(locLightType[light],				lights->GetType(light));

				//}
			}
			goto ExitFunc;
		}

		if(eShader==Core::GLS_PHONG) {
			locTexture0	= glGetUniformLocation(uiShaders[eShader], "texDirt1");
			locTexture1	= glGetUniformLocation(uiShaders[eShader], "texDirt2");
			locTexture2	= glGetUniformLocation(uiShaders[eShader], "texGrass1");
			locTexture3	= glGetUniformLocation(uiShaders[eShader], "texGrass2");
			locTexture4	= glGetUniformLocation(uiShaders[eShader], "texRocky1");
			locTexture5	= glGetUniformLocation(uiShaders[eShader], "texRocky2");
			locTexture6	= glGetUniformLocation(uiShaders[eShader], "texCliff1");
			locTexture7	= glGetUniformLocation(uiShaders[eShader], "texCliff2");

			locMVP		= glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
			locMV		= glGetUniformLocation(uiShaders[eShader], "mvMatrix");
			locMP		= glGetUniformLocation(uiShaders[eShader], "mpMatrix");

			glUniform1i(locTexture0,	0);
			glUniform1i(locTexture1,	1);
			glUniform1i(locTexture2,	2);
			glUniform1i(locTexture3,	3);
			glUniform1i(locTexture4,	4);
			glUniform1i(locTexture5,	5);
			glUniform1i(locTexture6,	6);
			glUniform1i(locTexture7,	7);

			glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection().data);
			glUniformMatrix4fv(locMV,	1,	GL_FALSE,	matrix->GetModelView().data);
			glUniformMatrix4fv(locMP,	1,	GL_FALSE,	matrix->GetProjectionMatrix().data);

			locNumLights			= glGetUniformLocation(uiShaders[eShader], "iNumLights");
			glUniform1i(locNumLights,				lights->GetNumLights());
			for(int light=0; light<lights->GetNumLights(); light++) {
				//if(lights->GetLightLoaded(0)) {
					std::string sLight = std::to_string(light);
					locLightPos[light]			= glGetUniformLocation(uiShaders[eShader], std::string("vLightPos["+sLight+"]").c_str());
					locLightDir[light]			= glGetUniformLocation(uiShaders[eShader], std::string("vLightDir["+sLight+"]").c_str());
					locLightDiffuse[light]		= glGetUniformLocation(uiShaders[eShader], std::string("vDiffuseColor["+sLight+"]").c_str());
					locLightAmbient[light]		= glGetUniformLocation(uiShaders[eShader], std::string("vAmbientColor["+sLight+"]").c_str());
					locLightSpecular[light]		= glGetUniformLocation(uiShaders[eShader], std::string("vSpecularColor["+sLight+"]").c_str());
					locLightAttenuation[light]	= glGetUniformLocation(uiShaders[eShader], std::string("vAttenuation["+sLight+"]").c_str());
					locLightType[light]			= glGetUniformLocation(uiShaders[eShader], std::string("iType["+sLight+"]").c_str());

					glUniform3fv(locLightPos[light], 			1,	lights->GetPos(light).data);
					glUniform3fv(locLightDir[light], 			1,	lights->GetDir(light).data);
					glUniform3fv(locLightDiffuse[light],		1,	lights->GetDiffuse(light).data);
					glUniform3fv(locLightAmbient[light],		1,	lights->GetAmbient(light).data);
					glUniform3fv(locLightSpecular[light],		1,	lights->GetSpecular(light).data);
					glUniform3fv(locLightAttenuation[light],	1,	lights->GetAttenuation(light).data);
					glUniform1i(locLightType[light],				lights->GetType(light));

				//}
			}
			goto ExitFunc;
		}

		ExitFunc:
		if (uiNumLights>0) {
			delete[] locLightPos;
			delete[] locLightDir;
			delete[] locLightDiffuse;
			delete[] locLightAmbient;
			delete[] locLightSpecular;
			delete[] locLightAttenuation;
			delete[] locLightType;
		}

	}
//	void Shader_System::getUniform(Atmosphere &a, GLenum eShader, bool bOne=false, bool bTwo=false, bool bThree=false, bool bFour=false) {
//		//atmosphere = &a;
//
//		//GLfloat	fTime;
//		GLint	locEyeVec,
//				locShiny,
//				locFogColor,
//				locFogStart,
//				locFogEnd,
//				locFogDensity,
//				locFogEquation,
//				locCamPos,
//				locTime,
//				locRot,
//				locRand,
//				locTexture0,
//				locTexture1,
//				locTexture2,
//				locTexture3,
//				locTexture4,
//				locTexture5,
//				locTexture6,
//				locTexture7,
//				locTexture8,
//				locTexture9,
//				locShadow,
//				locColor,
//				locLight,
//				locLightDir,
//				locMVP,
//				locMV,
//				locMV2,
//				locMT,
//				locMR,
//				locMP,
//				locNM,
//				locWorldPos,
//				locBools,
//				locClipPlane,
//				locTexReflect,
//				locTexRefract,
//				locTexDuDv,
//				locTexDepth,
//				locTexNormal,
//				locEnableReflect,
//				locUnderwater,
//				locFloat0,
//				locFloat1,
//				locFloat2,
//				locFloat3,
//				locFloat4,
//				locFloat5,
//				locFloat6,
//				locFloat7;
//
//		GLint	locAmbient,
//				locDiffuse,
//				locSpecular,
//				locShininess,
//				locSunPos,
//				locSunAmbient,
//				locSunDiffuse,
//				locSunSpecular,
//				locSunShiny,
//				locMoonPos,
//				locMoonAmbient,
//				locMoonDiffuse,
//				locMoonSpecular,
//				locMoonShiny;
//
//		//Vector3f vLightPos = {	a.sun.vPosition[0]+(500*Core::gameVars.screen.iTerrainGrid+1),
//			//					a.sun.vPosition[1],
//				//				a.sun.vPosition[2]+(500*Core::gameVars.screen.iTerrainGrid+1) };
//
//		//Vector3f vLightDir = {	0+(500*float(Core::gameVars.screen.iTerrainGrid)+1),
//			//					0,
//				//				0+(500*float(Core::gameVars.screen.iTerrainGrid)+1) };
//		//Vector3f vUp =		 { 0, 1, 0 };
//
//// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
////		if( eShader==Core::GLS_PP_CONTRAST) {
////			locTexture0 =		glGetUniformLocation(uiShaders[eShader], "colorMap");
////			locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
////
////			glUniform1i(locTexture0,	0);
////			glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection());
////		}
//// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//
//		if(eShader==Core::GLS_SCATTER) {
//			//"uniform vec3 vSunPos;" N
//			//"uniform vec3 vPos;" N
//			//"uniform mat4 mvpMatrix;" N
//			//"uniform mat4 mvMatrix;" N
//			locSunPos		= glGetUniformLocation(uiShaders[eShader], "vSunPos");
//			locMVP			= glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
//			locMV			= glGetUniformLocation(uiShaders[eShader], "mvMatrix");
//			locCamPos		= glGetUniformLocation(uiShaders[eShader], "vPos");
//
//			glUniform1i(locTexture0,	0);
//			glUniform3fv(locSunPos,		1,	a.sun.vPosition.data);
//			glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection());
//			glUniformMatrix4fv(locMV,	1,	GL_FALSE,	matrix->GetModelView());
//			Vector3f vfPos = { -Core::gameVars.player.active->transform.pos[0], -Core::gameVars.player.active->transform.pos[1], -Core::gameVars.player.active->transform.pos[2] };
//			glUniform3fv(locCamPos,		1,	vfPos.data);
//		}
//
//		if( eShader==Core::GLS_FONT ||
//			eShader==Core::GLS_SUN ||
//			eShader==Core::GLS_EXOSPHERE ||
//			eShader==Core::GLS_BASE ||
//			eShader==Core::GLS_SHADED_TEX ||
//			eShader==Core::GLS_SHADED_TEX_ALPHA) {
//			locColor =			glGetUniformLocation(uiShaders[eShader], "vColor");
//			//locWorldPos =		glGetUniformLocation(uiShaders[eShader], "vWorldPos");
//			locTexture0 =		glGetUniformLocation(uiShaders[eShader], "colorMap");
//			locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
//			locMV =				glGetUniformLocation(uiShaders[eShader], "mvMatrix");
//			locMP =				glGetUniformLocation(uiShaders[eShader], "mpMatrix");
//
//			//Vector3f vfPos = { -Core::gameVars.player.active->transform.pos[0], 0.0f, -Core::gameVars.player.active->transform.pos[2] };
//			//glUniform3fv(locWorldPos,	1,	vfPos);
//			glUniform4fv(locColor,		1,	Core::gameVars.font.vColor.data);
//			glUniform1i(locTexture0,	0);
//			glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection());
//			glUniformMatrix4fv(locMV,	1,	GL_FALSE,	matrix->GetModelView());
//			glUniformMatrix4fv(locMP,	1,	GL_FALSE,	matrix->GetProjectionMatrix());
//		}

//		if(eShader==Core::GLS_FLORA || Core::GLS_UWFLORA) {
//			locCamPos =			glGetUniformLocation(uiShaders[eShader], "vPos");
//			locMP =				glGetUniformLocation(uiShaders[eShader], "mpMatrix");
//			locMV =				glGetUniformLocation(uiShaders[eShader], "mvMatrix");
//			locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
//			locTime =			glGetUniformLocation(uiShaders[eShader], "fTime");
//			locTexture0 =		glGetUniformLocation(uiShaders[eShader], "colorMap");
//			locMoonDiffuse =	glGetUniformLocation(uiShaders[eShader], "vMoonDiffuse");
//			locSunDiffuse =		glGetUniformLocation(uiShaders[eShader], "vSunDiffuse");
//
//			glUniform4fv(locMoonDiffuse,	1,		a.moon.vDiffuseColor.data);
//			glUniform4fv(locSunDiffuse,		1,		a.sun.vDiffuseColor.data);
//			Vector3f vfPos = { -Core::gameVars.player.active->transform.pos[0], -Core::gameVars.player.active->transform.pos[1], -Core::gameVars.player.active->transform.pos[2] };
//			glUniform3fv(locCamPos,		1,	vfPos.data);
//			glUniformMatrix4fv(locMP,	1,	GL_FALSE,	matrix->GetProjectionMatrix());
//			glUniformMatrix4fv(locMV,	1,	GL_FALSE,	matrix->GetModelView());
//			glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection());
//			glUniform1f(locTime,		a.gameTime.get_ticks());
//			glUniform1i(locTexture0,	0);
//		}
//		if(eShader==Core::GLS_HAIL) {
//			locCamPos =			glGetUniformLocation(uiShaders[eShader], "vPos");
//			locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
//			//locTime =			glGetUniformLocation(uiShaders[eShader], "fTime");
//			//locTexture0 =		glGetUniformLocation(uiShaders[eShader], "colorMap");
//
//			Vector3f vfPos = { -Core::gameVars.player.active->transform.pos[0], -Core::gameVars.player.active->transform.pos[1], -Core::gameVars.player.active->transform.pos[2] };
//			glUniform3fv(locCamPos,		1,	vfPos.data);
//			glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection());
//			//glUniform1f(locTime,		Core::gameVars.timer.gameTime.get_ticks());
//			//glUniform1i(locTexture0,	0);
//		}
//		if(eShader==Core::GLS_RAIN) {
//			locCamPos =			glGetUniformLocation(uiShaders[eShader], "vPos");
//			locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
//			//locTime =			glGetUniformLocation(uiShaders[eShader], "fTime");
//			//locTexture0 =		glGetUniformLocation(uiShaders[eShader], "colorMap");
//
//			Vector3f vfPos = { -Core::gameVars.player.active->transform.pos[0]*Core::gameVars.screen.iScale, -Core::gameVars.player.active->transform.pos[1]*Core::gameVars.screen.iScale, -Core::gameVars.player.active->transform.pos[2]*Core::gameVars.screen.iScale };
//			glUniform3fv(locCamPos,		1,	vfPos.data);
//			glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection());
//			//glUniform1f(locTime,		a.gameTime.get_ticks());
//			//glUniform1i(locTexture0,	0);
//		}
//		if(eShader==Core::GLS_GRASS_TRI || eShader==Core::GLS_GRASS_LINE) {
//			locCamPos =			glGetUniformLocation(uiShaders[eShader], "vPos");
//			locMP =				glGetUniformLocation(uiShaders[eShader], "mpMatrix");
//			locMV =				glGetUniformLocation(uiShaders[eShader], "mvMatrix");
//			locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
//			locTime =			glGetUniformLocation(uiShaders[eShader], "fTime");
//			locMoonDiffuse =	glGetUniformLocation(uiShaders[eShader], "vMoonDiffuse");
//			locSunDiffuse =		glGetUniformLocation(uiShaders[eShader], "vSunDiffuse");
//
//			glUniform4fv(locMoonDiffuse,	1,		a.moon.vDiffuseColor.data);
//			glUniform4fv(locSunDiffuse,		1,		a.sun.vDiffuseColor.data);
//			Vector3f vfPos = { -Core::gameVars.player.active->transform.pos[0]*Core::gameVars.screen.iScale, -Core::gameVars.player.active->transform.pos[1], -Core::gameVars.player.active->transform.pos[2]*Core::gameVars.screen.iScale };
//			glUniform3fv(locCamPos,		1,	vfPos.data);
//			glUniformMatrix4fv(locMP,	1,	GL_FALSE,	matrix->GetProjectionMatrix());
//			glUniformMatrix4fv(locMV,	1,	GL_FALSE,	matrix->GetModelView());
//			glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection());
//			glUniform1f(locTime,		a.gameTime.get_ticks()/10000);
//			//glUniform1i(locTexture0,	0);
//		}
//		if(eShader==Core::GLS_TROPOSPHERE) {
//			//locColor =		glGetUniformLocation(uiShaders[eShader], "vColor");
//			locDiffuse =		glGetUniformLocation(uiShaders[eShader], "vDiffuseColor");
//			locAmbient =		glGetUniformLocation(uiShaders[eShader], "vAmbientColor");
//			//locSpecular =		glGetUniformLocation(uiShaders[eShader], "vSpecularColor");
//			locLight =			glGetUniformLocation(uiShaders[eShader], "vLightPos");
//			//locWorldPos =		glGetUniformLocation(uiShaders[eShader], "vCamPos");
//			locTexture0 =		glGetUniformLocation(uiShaders[eShader], "colorMap");
//			//locTexture1 =		glGetUniformLocation(uiShaders[eShader], "bumpMap");
//			locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
//			//locMV =			glGetUniformLocation(uiShaders[eShader], "mvMatrix");
//			//locMP =			glGetUniformLocation(uiShaders[eShader], "mpMatrix");
//
//			//Vector3f	vLightPos	=	{ a.sun.vPosition[0], a.sun.vPosition[1], a.sun.vPosition[2] };
//			//Vector3f	vfPos		=	{ -Core::gameVars.player.active->transform.pos[0], 0.0f, -Core::gameVars.player.active->transform.pos[2] };
//
//			//glUniform3fv(locCamPos,		1,	vfPos);
//			glUniform3fv(locLight,		1,	a.sun.vPosition.data);
//			glUniform4fv(locDiffuse,	1,	a.sun.vDiffuseColor.data);
//			glUniform4fv(locAmbient,	1,	a.sun.vAmbientColor.data);
//			//glUniform4fv(locSpecular,	1,	a.sun.vSpecularColor.data);
//			//glUniform4fv(locColor,		1,	Core::gameVars.font.vColor);
//			glUniform1i(locTexture0,	0);
//			//glUniform1i(locTexture1,	1);
//			glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection());
//			//glUniformMatrix4fv(locMV,	1,	GL_FALSE,	matrix->GetModelView());
//			//glUniformMatrix4fv(locMP,	1,	GL_FALSE,	matrix->GetProjectionMatrix());
//		}
//		if(eShader==Core::GLS_STRATOSPHERE) {
//			locSunPos =			glGetUniformLocation(uiShaders[eShader], "vSunPos");
//			locSunAmbient =		glGetUniformLocation(uiShaders[eShader], "vSunAmbient");
//			locSunDiffuse =		glGetUniformLocation(uiShaders[eShader], "vSunDiffuse");
//			locSunSpecular =	glGetUniformLocation(uiShaders[eShader], "vSunSpecular");
//			locSunShiny =		glGetUniformLocation(uiShaders[eShader], "fSunShiny");
//
//			locMoonPos =		glGetUniformLocation(uiShaders[eShader], "vMoonPos");
//			locMoonAmbient =	glGetUniformLocation(uiShaders[eShader], "vMoonAmbient");
//			locMoonDiffuse =	glGetUniformLocation(uiShaders[eShader], "vMoonDiffuse");
//			locMoonSpecular =	glGetUniformLocation(uiShaders[eShader], "vMoonSpecular");
//			locMoonShiny =		glGetUniformLocation(uiShaders[eShader], "fMoonShiny");
//
//			//locWorldPos =	 	glGetUniformLocation(uiShaders[eShader], "vCamPos");
//			locTexture0 =	 	glGetUniformLocation(uiShaders[eShader], "colorMap");
//			locTexture1 =	 	glGetUniformLocation(uiShaders[eShader], "bumpMap");
//			locMVP =		 	glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
//			locMV =				glGetUniformLocation(uiShaders[eShader], "mvMatrix");
//			//locMP =			glGetUniformLocation(uiShaders[eShader], "mpMatrix");
//			locTime =		 	glGetUniformLocation(uiShaders[eShader], "fTime");
//
//			//Vector3f	vLightPos	=	{ a.sun.vPosition[0], a.sun.vPosition[1], a.sun.vPosition[2] };
//			Vector3f	vfPos		=	{ -Core::gameVars.player.active->transform.pos[0], -Core::gameVars.player.active->transform.pos[1], -Core::gameVars.player.active->transform.pos[2] };
//
//			glUniform3fv(locSunPos,			1,		a.sun.vPosition.data);
//			glUniform4fv(locSunDiffuse,		1,		a.sun.vDiffuseColor.data);
//			glUniform4fv(locSunAmbient,		1,		a.sun.vAmbientColor.data);
//			glUniform4fv(locSunSpecular,	1,		a.sun.vSpecularColor.data);
//			glUniform1f(locSunShiny,				a.sun.fShiny);
//
//			glUniform3fv(locMoonPos,		1,		a.moon.vPosition.data);
//			glUniform4fv(locMoonDiffuse,	1,		a.moon.vDiffuseColor.data);
//			glUniform4fv(locMoonAmbient,	1,		a.moon.vAmbientColor.data);
//			glUniform4fv(locMoonSpecular,	1,		a.moon.vSpecularColor.data);
//			glUniform1f(locMoonShiny,				a.moon.fShiny);
//
//			glUniform3fv(locCamPos,		1,	vfPos.data);
//			//glUniform3fv(locLight,		1,	a.sun.vPosition);
//			//glUniform4fv(locDiffuse,	1,	a.sun.vDiffuseColor.data);
//			//glUniform4fv(locAmbient,	1,	a.sun.vAmbientColor.data);
//			//glUniform4fv(locSpecular,	1,	a.sun.vSpecularColor.data);
//			//glUniform4fv(locColor,		1,	Core::gameVars.font.vColor);
//			glUniform1i(locTexture0,	0);
//			glUniform1i(locTexture1,	1);
//			//glUniform1f(locTime,		a.gameTime.get_ticks());
//			glUniform1f(locTime,		a.gameTime.get_ticks()/5000);
//			glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection());
//			glUniformMatrix4fv(locMV,	1,	GL_FALSE,	matrix->GetModelView());
//			//glUniformMatrix4fv(locMP,	1,	GL_FALSE,	matrix->GetProjectionMatrix());
//		}
//		if(eShader==Core::GLS_THERMOSPHERE) {
//			//locColor =		glGetUniformLocation(uiShaders[eShader], "vColor");
//			locDiffuse =	 	glGetUniformLocation(uiShaders[eShader], "vDiffuseColor");
//			//locAmbient =	 	glGetUniformLocation(uiShaders[eShader], "vAmbientColor");
//			//locSpecular =	 	glGetUniformLocation(uiShaders[eShader], "vSpecularColor");
//			locLight =		 	glGetUniformLocation(uiShaders[eShader], "vLightPos");
//			//locWorldPos =	 	glGetUniformLocation(uiShaders[eShader], "vCamPos");
//			locTexture0 =	 	glGetUniformLocation(uiShaders[eShader], "texColor0");
//			locTexture1 =	 	glGetUniformLocation(uiShaders[eShader], "texColor1");
//			locMVP =		 	glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
//			//locMV =			glGetUniformLocation(uiShaders[eShader], "mvMatrix");
//			//locMP =			glGetUniformLocation(uiShaders[eShader], "mpMatrix");
//			locFloat0		=	glGetUniformLocation(uiShaders[eShader], "fS");
//			locFloat1		=	glGetUniformLocation(uiShaders[eShader], "fD");
//
//			//Vector3f	vLightPos	=	{ a.sun.vPosition[0], a.sun.vPosition[1], a.sun.vPosition[2] };
//			//Vector3f	vfPos		=	{ -Core::gameVars.player.active->transform.pos[0], 0.0f, -Core::gameVars.player.active->transform.pos[2] };
//
//			//glUniform3fv(locCamPos,		1,	vfPos);
//			glUniform3fv(locLight,		1,	a.sun.vPosition.data);
//			glUniform4fv(locDiffuse,	1,	a.sun.vDiffuseColor.data);
//			//glUniform4fv(locAmbient,	1,	a.sun.vAmbientColor.data);
//			//glUniform4fv(locSpecular,	1,	a.sun.vSpecularColor.data);
//			//glUniform4fv(locColor,		1,	Core::gameVars.font.vColor);
//			glUniform1i(locTexture0,	0);
//			glUniform1i(locTexture1,	1);
//			glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection());
//			//glUniformMatrix4fv(locMV,	1,	GL_FALSE,	matrix->GetModelView());
//			//glUniformMatrix4fv(locMP,	1,	GL_FALSE,	matrix->GetProjectionMatrix());
//			glUniform1f(locFloat0,	a.skybox.thermosphere.fS);
//			glUniform1f(locFloat1,	a.skybox.thermosphere.fD);
//		}
//		if(eShader==Core::GLS_FLAT_FOG || eShader==Core::GLS_FLAT_FOG_SHEAR) {
//			locColor =			glGetUniformLocation(uiShaders[eShader], "vColor");
//			locDiffuse =		glGetUniformLocation(uiShaders[eShader], "vDiffuseColor");
//			locAmbient =		glGetUniformLocation(uiShaders[eShader], "vAmbientColor");
//			locSpecular =		glGetUniformLocation(uiShaders[eShader], "vSpecularColor");
//			locLight =			glGetUniformLocation(uiShaders[eShader], "vLightPos");
//			locWorldPos =		glGetUniformLocation(uiShaders[eShader], "vWorldPos");
//			locBools =			glGetUniformLocation(uiShaders[eShader], "vBools");
//			locTexture0 =		glGetUniformLocation(uiShaders[eShader], "colorMap");
//			locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
//			locMV =				glGetUniformLocation(uiShaders[eShader], "mvMatrix");
//			locMP =				glGetUniformLocation(uiShaders[eShader], "mpMatrix");
//			locTime =			glGetUniformLocation(uiShaders[eShader], "fTime");
//			locClipPlane	=	glGetUniformLocation(uiShaders[eShader], "vClipPlane");
//
//			Vector3f vfPos = { -Core::gameVars.player.active->transform.pos[0], 0.0f, -Core::gameVars.player.active->transform.pos[2] };
//
//			//Vector3f	vLightPos	=	{ a.sun.vPosition[0], a.sun.vPosition[1]-300, a.sun.vPosition[2] };
//			//Vector3f	vfPos		=	{ -Core::gameVars.player.active->transform.pos[0], 0.0f, -Core::gameVars.player.active->transform.pos[2] };
//
//			//glUniform3fv(locCamPos,		1,	vfPos);
//			glUniform3fv(locLight,		1,	a.sun.vPosition.data);
//			glUniform4fv(locDiffuse,	1,	a.sun.vDiffuseColor.data);
//			glUniform4fv(locAmbient,	1,	a.sun.vAmbientColor.data);
//			glUniform4fv(locSpecular,	1,	a.sun.vSpecularColor.data);
//			glUniform4fv(locColor,		1,	Core::gameVars.font.vColor.data);
//			//Vector4i vBools = { bOne, bTwo, bThree, bFour };
//			//glUniform4iv(locBools,	1,	vBools);
//			glUniform4i(locBools,	bOne, bTwo, bThree, bFour);
//			glUniform1i(locTexture0,	0);
//			glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection());
//			glUniformMatrix4fv(locMV,	1,	GL_FALSE,	matrix->GetModelView());
//			glUniformMatrix4fv(locMP,	1,	GL_FALSE,	matrix->GetProjectionMatrix());
//			glUniform1f(locTime,		a.gameTime.get_ticks());
//
//			locFogColor	=		glGetUniformLocation(uiShaders[eShader], "fogParams.vFogColor");
//			locFogStart =		glGetUniformLocation(uiShaders[eShader], "fogParams.fStart");
//			locFogEnd	=		glGetUniformLocation(uiShaders[eShader], "fogParams.fEnd");
//			locFogDensity = 	glGetUniformLocation(uiShaders[eShader], "fogParams.fDensity");
//			locFogEquation =	glGetUniformLocation(uiShaders[eShader], "fogParams.iEquation");
//			glUniform4fv(locFogColor,		1,	Core.shader.activeFog.vFogColor.data);
//			glUniform1f(locFogStart,			Core.shader.activeFog.fStart);
//			glUniform1f(locFogEnd,				Core.shader.activeFog.fEnd);
//			glUniform1f(locFogDensity,			Core.shader.activeFog.fDensity);
//			glUniform1i(locFogEquation,			Core.shader.activeFog.iEquation);
//
//			glUniform4fv(locClipPlane,		1,		a.water.vClipPlane.data);
//		}
//		if(eShader==Core::GLS_FLAT_FOG_INSTANCE) {
//			locColor =			glGetUniformLocation(uiShaders[eShader], "vColor");
//			locDiffuse =		glGetUniformLocation(uiShaders[eShader], "vDiffuseColor");
//			locAmbient =		glGetUniformLocation(uiShaders[eShader], "vAmbientColor");
//			locSpecular =		glGetUniformLocation(uiShaders[eShader], "vSpecularColor");
//			locLight =			glGetUniformLocation(uiShaders[eShader], "vLightPos");
//			locWorldPos =		glGetUniformLocation(uiShaders[eShader], "vWorldPos");
//			//locBools =			glGetUniformLocation(uiShaders[eShader], "vBools");
//			locCamPos =			glGetUniformLocation(uiShaders[eShader], "vCamPois");
//			locTexture0 =		glGetUniformLocation(uiShaders[eShader], "colorMap");
//			locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
//			locMV =				glGetUniformLocation(uiShaders[eShader], "mvMatrix");
//			locMV2 =			glGetUniformLocation(uiShaders[eShader], "mvMatrix2");
//			//locMT =				glGetUniformLocation(uiShaders[eShader], "mtMatrix");
//			//locMR =				glGetUniformLocation(uiShaders[eShader], "mrMatrix");
//			//locMP =				glGetUniformLocation(uiShaders[eShader], "mpMatrix");
//			//locTime =			glGetUniformLocation(uiShaders[eShader], "fTime");
//			//locRot =			glGetUniformLocation(uiShaders[eShader], "fRot");
//			locClipPlane	=	glGetUniformLocation(uiShaders[eShader], "vClipPlane");
//
//			Vector3f vfPos = { -Core::gameVars.player.active->transform.pos[0], 0.0f, -Core::gameVars.player.active->transform.pos[2] };
//
//			//Vector3f	vLightPos	=	{ a.sun.vPosition[0], a.sun.vPosition[1]-300, a.sun.vPosition[2] };
//			//Vector3f	vfPos		=	{ -Core::gameVars.player.active->transform.pos[0], 0.0f, -Core::gameVars.player.active->transform.pos[2] };
//
//			//glUniform3fv(locCamPos,		1,	vfPos);
//			glUniform3fv(locLight,		1,	a.sun.vPosition.data);
//			glUniform4fv(locDiffuse,	1,	a.sun.vDiffuseColor.data);
//			glUniform4fv(locAmbient,	1,	a.sun.vAmbientColor.data);
//			glUniform4fv(locSpecular,	1,	a.sun.vSpecularColor.data);
//			glUniform4fv(locColor,		1,	Core::gameVars.font.vColor.data);
//			//Vector4i vBools = { bOne, bTwo, bThree, bFour };
//			//glUniform4iv(locBools,	1,	vBools);
//			//glUniform4i(locBools,	bOne, bTwo, bThree, bFour);
//			glUniform4f(locCamPos,	-Core::gameVars.player.active->transform.pos[0], 0.0f, -Core::gameVars.player.active->transform.pos[2], 0.0f);
//			glUniform1i(locTexture0,	0);
//			glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection());
//			glUniformMatrix4fv(locMV,	1,	GL_FALSE,	matrix->GetModelView());
//			glUniformMatrix4fv(locMV2,	1,	GL_FALSE,	matrix->GetModelView());
//			//glUniformMatrix4fv(locMT,	1,	GL_FALSE,	matrix->GetTransView());
//			//glUniformMatrix4fv(locMR,	1,	GL_FALSE,	matrix->GetRotView());
//			//glUniformMatrix4fv(locMP,	1,	GL_FALSE,	matrix->GetProjectionMatrix());
//			//glUniform1f(locTime,		a.gameTime.get_ticks());
//			//glUniform1f(locRot,			Core::gameVars.player.active->transform.rot[1]);
//
//			locFogColor	=		glGetUniformLocation(uiShaders[eShader], "fogParams.vFogColor");
//			locFogStart =		glGetUniformLocation(uiShaders[eShader], "fogParams.fStart");
//			locFogEnd	=		glGetUniformLocation(uiShaders[eShader], "fogParams.fEnd");
//			locFogDensity = 	glGetUniformLocation(uiShaders[eShader], "fogParams.fDensity");
//			locFogEquation =	glGetUniformLocation(uiShaders[eShader], "fogParams.iEquation");
//			glUniform4fv(locFogColor,		1,	Core.shader.activeFog.vFogColor.data);
//			glUniform1f(locFogStart,			Core.shader.activeFog.fStart);
//			glUniform1f(locFogEnd,				Core.shader.activeFog.fEnd);
//			glUniform1f(locFogDensity,			Core.shader.activeFog.fDensity);
//			glUniform1i(locFogEquation,			Core.shader.activeFog.iEquation);
//
//			glUniform4fv(locClipPlane,		1,		a.water.vClipPlane.data);
//
//
//			//Matrix44f mTrans = matrix->GetTransView();
//			//cout << "TMAT: " << mTrans[0] << ", " << mTrans[1] << ", " << mTrans[2] << ", " << mTrans[3] <<
//			//		    ", " << mTrans[4] << ", " << mTrans[5] << ", " << mTrans[6] << ", " << mTrans[7] <<
//			//		    ", " << mTrans[8] << ", " << mTrans[9] << ", " << mTrans[10] << ", " << mTrans[11] <<
//			//		    ", " << mTrans[] << ", " << mTrans[] << ", " << mTrans[] << ", " << mTrans[] << endl;
//		}
//		if(	eShader == Core::GLS_NORMAL_LINE2) {
//			locWorldPos =		glGetUniformLocation(uiShaders[eShader], "vWorldPos");
//			locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
//
//			Vector3f vfPos = { -Core::gameVars.player.active->transform.pos[0], 0.0f, -Core::gameVars.player.active->transform.pos[2] };
//
//			glUniform3fv(locWorldPos,	1,	vfPos.data);
//			glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection());
//		}
//
//		if(eShader==Core::GLS_DIRECTIONAL_TERRAIN) {
//
//			// Auto bind textures
//			glActiveTexture(GL_TEXTURE8);	a.water.tex.Set(a.water.sWorld);
//			glActiveTexture(GL_TEXTURE9);	a.water.tex.Set(a.water.sBump);
//			glActiveTexture(GL_TEXTURE0);
//
//			locTexture0 =		glGetUniformLocation(uiShaders[eShader], "texDirt1");
//			locTexture1 =		glGetUniformLocation(uiShaders[eShader], "texGrass1");
//			locTexture2 =		glGetUniformLocation(uiShaders[eShader], "texRocky1");
//			locTexture3 =		glGetUniformLocation(uiShaders[eShader], "texCliff1");
//			locTexture4 =		glGetUniformLocation(uiShaders[eShader], "texDirt2");
//			locTexture5 =		glGetUniformLocation(uiShaders[eShader], "texGrass2");
//			locTexture6 =		glGetUniformLocation(uiShaders[eShader], "texRocky2");
//			locTexture7 =		glGetUniformLocation(uiShaders[eShader], "texCliff2");
//			locTexture8 =		glGetUniformLocation(uiShaders[eShader], "texDuDv");
//			locTexture9 =		glGetUniformLocation(uiShaders[eShader], "texNormal");
//			locSunPos =			glGetUniformLocation(uiShaders[eShader], "vSunPos");
//			locSunAmbient =		glGetUniformLocation(uiShaders[eShader], "vSunAmbient");
//			locSunDiffuse =		glGetUniformLocation(uiShaders[eShader], "vSunDiffuse");
//			locSunSpecular =	glGetUniformLocation(uiShaders[eShader], "vSunSpecular");
//			locSunShiny =		glGetUniformLocation(uiShaders[eShader], "fSunShiny");
//			locMoonPos =		glGetUniformLocation(uiShaders[eShader], "vMoonPos");
//			locMoonAmbient =	glGetUniformLocation(uiShaders[eShader], "vMoonAmbient");
//			locMoonDiffuse =	glGetUniformLocation(uiShaders[eShader], "vMoonDiffuse");
//			locMoonSpecular =	glGetUniformLocation(uiShaders[eShader], "vMoonSpecular");
//			locMoonShiny =		glGetUniformLocation(uiShaders[eShader], "fMoonShiny");
//			locUnderwater =		glGetUniformLocation(uiShaders[eShader], "bUnderwater");
//			locCamPos =			glGetUniformLocation(uiShaders[eShader], "vCamPos");
//			locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
//			locNM =				glGetUniformLocation(uiShaders[eShader], "normalMatrix");
//			locMV =				glGetUniformLocation(uiShaders[eShader], "mvMatrix");
//			locTime =			glGetUniformLocation(uiShaders[eShader], "fTime");
//			locFogColor	=		glGetUniformLocation(uiShaders[eShader], "fogParams.vFogColor");
//			locFogStart =		glGetUniformLocation(uiShaders[eShader], "fogParams.fStart");
//			locFogEnd	=		glGetUniformLocation(uiShaders[eShader], "fogParams.fEnd");
//			locFogDensity = 	glGetUniformLocation(uiShaders[eShader], "fogParams.fDensity");
//			locFogEquation =	glGetUniformLocation(uiShaders[eShader], "fogParams.iEquation");
//			locClipPlane	=	glGetUniformLocation(uiShaders[eShader], "vClipPlane");
//
//			Vector3f	vfPos		=	{ -Core::gameVars.player.active->transform.pos[0], -Core::gameVars.player.active->transform.pos[1]-Core::gameVars.player.active->transform.eyeHeight, -Core::gameVars.player.active->transform.pos[2] };
//
//			glUniform1i(locTexture0,		0);
//			glUniform1i(locTexture1,		1);
//			glUniform1i(locTexture2,		2);
//			glUniform1i(locTexture3,		3);
//			glUniform1i(locTexture4,		4);
//			glUniform1i(locTexture5,		5);
//			glUniform1i(locTexture6,		6);
//			glUniform1i(locTexture7,		7);
//			glUniform1i(locTexture8,		8);
//			glUniform1i(locTexture9,		9);
//			glUniform3fv(locSunPos,			1,		a.sun.vPosition.data);
//			glUniform4fv(locSunDiffuse,		1,		a.sun.vDiffuseColor.data);
//			glUniform4fv(locSunAmbient,		1,		a.sun.vAmbientColor.data);
//			glUniform4fv(locSunSpecular,	1,		a.sun.vSpecularColor.data);
//			glUniform1f(locSunShiny,				a.sun.fShiny);
//			glUniform3fv(locMoonPos,		1,		a.moon.vPosition.data);
//			glUniform4fv(locMoonDiffuse,	1,		a.moon.vDiffuseColor.data);
//			glUniform4fv(locMoonAmbient,	1,		a.moon.vAmbientColor.data);
//			glUniform4fv(locMoonSpecular,	1,		a.moon.vSpecularColor.data);
//			glUniform1f(locMoonShiny,				a.moon.fShiny);
//			glUniform1i(locUnderwater,				Core::gameVars.player.active->transform.bBelowWater);
//			glUniform3fv(locCamPos,			1,		vfPos.data);
//			glUniform1f(locTime,					a.gameTime.get_ticks()/50000);
//			glUniform4fv(locFogColor,		1,		Core.shader.activeFog.vFogColor.data);
//			glUniform1f(locFogStart,				Core.shader.activeFog.fStart);
//			glUniform1f(locFogEnd,					Core.shader.activeFog.fEnd);
//			glUniform1f(locFogDensity,				Core.shader.activeFog.fDensity);
//			glUniform1i(locFogEquation,				Core.shader.activeFog.iEquation);
//			glUniformMatrix4fv(locMVP,		1,		GL_FALSE,	matrix->GetModelViewProjection());
//			glUniformMatrix4fv(locMV,		1,		GL_FALSE,	matrix->GetModelView());
//			glUniformMatrix3fv(locNM,		1,		GL_FALSE,	matrix->GetNormalMatrix33());
//			glUniform4fv(locClipPlane,		1,		a.water.vClipPlane.data);
//		}
//
//		if(eShader==Core::GLS_DIRECTIONAL_WATER) {
//			// Auto bind textures
//			glActiveTexture(GL_TEXTURE4);	glBindTexture(GL_TEXTURE_2D, a.water.texDepth);
//			glActiveTexture(GL_TEXTURE0);
//
//			locSunPos =			glGetUniformLocation(uiShaders[eShader], "vSunPos");
//			locSunAmbient =		glGetUniformLocation(uiShaders[eShader], "vSunAmbient");
//			locSunDiffuse =		glGetUniformLocation(uiShaders[eShader], "vSunDiffuse");
//			locSunSpecular =	glGetUniformLocation(uiShaders[eShader], "vSunSpecular");
//			locSunShiny =		glGetUniformLocation(uiShaders[eShader], "fSunShiny");
//			locMoonPos =		glGetUniformLocation(uiShaders[eShader], "vMoonPos");
//			locMoonAmbient =	glGetUniformLocation(uiShaders[eShader], "vMoonAmbient");
//			locMoonDiffuse =	glGetUniformLocation(uiShaders[eShader], "vMoonDiffuse");
//			locMoonSpecular =	glGetUniformLocation(uiShaders[eShader], "vMoonSpecular");
//			locMoonShiny =		glGetUniformLocation(uiShaders[eShader], "fMoonShiny");
//			locEnableReflect =	glGetUniformLocation(uiShaders[eShader], "bReflect");
//			locCamPos =			glGetUniformLocation(uiShaders[eShader], "vCamPos");
//			locEyeVec =			glGetUniformLocation(uiShaders[eShader], "vEyeVec");
//			locFogColor	=		glGetUniformLocation(uiShaders[eShader], "fogParams.vFogColor");
//			locFogStart =		glGetUniformLocation(uiShaders[eShader], "fogParams.fStart");
//			locFogEnd	=		glGetUniformLocation(uiShaders[eShader], "fogParams.fEnd");
//			locFogDensity = 	glGetUniformLocation(uiShaders[eShader], "fogParams.fDensity");
//			locFogEquation =	glGetUniformLocation(uiShaders[eShader], "fogParams.iEquation");
//			locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
//			locNM =				glGetUniformLocation(uiShaders[eShader], "normalMatrix");
//			locMV =				glGetUniformLocation(uiShaders[eShader], "mvMatrix");
//			locTime =			glGetUniformLocation(uiShaders[eShader], "fTime");
//			locTexReflect	=	glGetUniformLocation(uiShaders[eShader], "texReflect");
//			locTexRefract	=	glGetUniformLocation(uiShaders[eShader], "texRefract");
//			locTexDuDv		=	glGetUniformLocation(uiShaders[eShader], "texDuDv");
//			locTexNormal	=	glGetUniformLocation(uiShaders[eShader], "texNormal");
//			locTexDepth 	=	glGetUniformLocation(uiShaders[eShader], "texDepth");
//
//			Vector3f	vfPos		=	{ -Core::gameVars.player.active->transform.pos[0], -Core::gameVars.player.active->transform.pos[1]-Core::gameVars.player.active->transform.eyeHeight, -Core::gameVars.player.active->transform.pos[2] };
//			float yaw = Core::gameVars.player.active->transform.rot[1];
//			float pitch = Core::gameVars.player.active->transform.rot[0];
//			Vector3f vEyeVec = { -(sin(yaw)*cos(pitch)),
//								  max(sin(pitch), 0.0f),
//								 -(cos(yaw)*cos(pitch)) };
//
//			glUniform1i(locTexReflect,		0);
//			glUniform1i(locTexRefract,		1);
//			glUniform1i(locTexDuDv,			2);
//			glUniform1i(locTexNormal,		3);
//			glUniform1i(locTexDepth,		4);
//			glUniform3fv(locSunPos,			1,		a.sun.vPosition.data);
//			glUniform4fv(locSunDiffuse,		1,		a.sun.vDiffuseColor.data);
//			glUniform4fv(locSunAmbient,		1,		a.sun.vAmbientColor.data);
//			glUniform4fv(locSunSpecular,	1,		a.sun.vSpecularColor.data);
//			glUniform1f(locSunShiny,				a.sun.fShiny);
//			glUniform3fv(locMoonPos,		1,		a.moon.vPosition.data);
//			glUniform4fv(locMoonDiffuse,	1,		a.moon.vDiffuseColor.data);
//			glUniform4fv(locMoonAmbient,	1,		a.moon.vAmbientColor.data);
//			glUniform4fv(locMoonSpecular,	1,		a.moon.vSpecularColor.data);
//			glUniform1f(locMoonShiny,				a.moon.fShiny);
//			glUniform1i(locEnableReflect,			!Core::gameVars.player.active->transform.bBelowWater);
//			glUniform3fv(locCamPos,			1,		vfPos.data);
//			glUniform3fv(locEyeVec,			1,		vEyeVec.data);
//			glUniform1f(locTime,					a.gameTime.get_ticks()/1000000);
//			glUniform4fv(locFogColor,		1,		Core.shader.activeFog.vFogColor.data);
//			glUniform1f(locFogStart,				Core.shader.activeFog.fStart);
//			glUniform1f(locFogEnd,					Core.shader.activeFog.fEnd);
//			glUniform1f(locFogDensity,				Core.shader.activeFog.fDensity);
//			glUniform1i(locFogEquation,				Core.shader.activeFog.iEquation);
//			glUniformMatrix4fv(locMVP,		1,		GL_FALSE,	matrix->GetModelViewProjection());
//			glUniformMatrix4fv(locMV,		1,		GL_FALSE,	matrix->GetModelView());
//			glUniformMatrix3fv(locNM,		1,		GL_FALSE,	matrix->GetNormalMatrix33());
//		}
//
////		if(eShader==Core::GLS_DIRECTIONAL_TERRAIN_UWATER || eShader==Core::GLS_DIRECTIONAL_TERRAIN_LWATER) {
////			locSunPos =			glGetUniformLocation(uiShaders[eShader], "vSunPos");
////			locSunAmbient =		glGetUniformLocation(uiShaders[eShader], "vSunAmbient");
////			locSunDiffuse =		glGetUniformLocation(uiShaders[eShader], "vSunDiffuse");
////			locSunSpecular =	glGetUniformLocation(uiShaders[eShader], "vSunSpecular");
////			locSunShiny =		glGetUniformLocation(uiShaders[eShader], "fSunShiny");
////
////			locMoonPos =		glGetUniformLocation(uiShaders[eShader], "vMoonPos");
////			locMoonAmbient =	glGetUniformLocation(uiShaders[eShader], "vMoonAmbient");
////			locMoonDiffuse =	glGetUniformLocation(uiShaders[eShader], "vMoonDiffuse");
////			locMoonSpecular =	glGetUniformLocation(uiShaders[eShader], "vMoonSpecular");
////			locMoonShiny =		glGetUniformLocation(uiShaders[eShader], "fMoonShiny");
////
////			locCamPos =			glGetUniformLocation(uiShaders[eShader], "vCamPos");
////			locMVP =			glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
////			locNM =				glGetUniformLocation(uiShaders[eShader], "normalMatrix");
////			locMV =				glGetUniformLocation(uiShaders[eShader], "mvMatrix");
////			locTexture0 =		glGetUniformLocation(uiShaders[eShader], "colorMap0");
////			locTexture1 =		glGetUniformLocation(uiShaders[eShader], "colorMap1");
////			locTexture2 =		glGetUniformLocation(uiShaders[eShader], "colorMap2");
////			locTexture3 =		glGetUniformLocation(uiShaders[eShader], "colorMap3");
////
////			locFogColor	=		glGetUniformLocation(uiShaders[eShader], "fogParams.vFogColor");
////			locFogStart =		glGetUniformLocation(uiShaders[eShader], "fogParams.fStart");
////			locFogEnd	=		glGetUniformLocation(uiShaders[eShader], "fogParams.fEnd");
////			locFogDensity = 	glGetUniformLocation(uiShaders[eShader], "fogParams.fDensity");
////			locFogEquation =	glGetUniformLocation(uiShaders[eShader], "fogParams.iEquation");
////
////			locTime =		 	glGetUniformLocation(uiShaders[eShader], "fTime");
////			glUniform1f(locTime,					Core::gameVars.timer.frameRate.get_ticks()/1000);
////
////			glUniform4fv(locFogColor,		1,		Core.shader.activeFog.vFogColor.data);
////			glUniform1f(locFogStart,				Core.shader.activeFog.fStart);
////			glUniform1f(locFogEnd,					Core.shader.activeFog.fEnd);
////			glUniform1f(locFogDensity,				Core.shader.activeFog.fDensity);
////			glUniform1i(locFogEquation,				Core.shader.activeFog.iEquation);
////
////			glUniform3fv(locSunPos,			1,		a.sun.vPosition);
////			glUniform4fv(locSunDiffuse,		1,		a.sun.vDiffuseColor.data);
////			glUniform4fv(locSunAmbient,		1,		a.sun.vAmbientColor.data);
////			glUniform4fv(locSunSpecular,	1,		a.sun.vSpecularColor.data);
////			glUniform1f(locSunShiny,				a.sun.fShiny);
////
////			glUniform3fv(locMoonPos,		1,		a.moon.vPosition);
////			glUniform4fv(locMoonDiffuse,	1,		a.moon.vDiffuseColor.data);
////			glUniform4fv(locMoonAmbient,	1,		a.moon.vAmbientColor.data);
////			glUniform4fv(locMoonSpecular,	1,		a.moon.vSpecularColor.data);
////			glUniform1f(locMoonShiny,				a.moon.fShiny);
////
////			Vector3f	vfPos		=	{ -Core::gameVars.player.active->transform.pos[0], -Core::gameVars.player.active->transform.pos[1]-Core::gameVars.player.active->transform.eyeHeight, -Core::gameVars.player.active->transform.pos[2] };
////
////			glUniform3fv(locCamPos,			1,		vfPos);
////			glUniform1i(locTexture0,		0);
////			glUniform1i(locTexture1,		1);
////			glUniform1i(locTexture2,		2);
////			glUniform1i(locTexture3,		3);
////			glUniformMatrix4fv(locMVP,		1,		GL_FALSE,	matrix->GetModelViewProjection());
////			glUniformMatrix4fv(locMV,		1,		GL_FALSE,	matrix->GetModelView());
////			glUniformMatrix3fv(locNM,		1,		GL_FALSE,	matrix->GetNormalMatrix33());
////		}
//
//		if(eShader==Core::GLS_PP_UNDERWATER) {
//			glActiveTexture(GL_TEXTURE1);
//			a.water.tex.Set(a.water.sWorld);
//			glActiveTexture(GL_TEXTURE0);
//
//			locColor =		glGetUniformLocation(uiShaders[eShader], "vColor");
//			locTexture0 =	glGetUniformLocation(uiShaders[eShader], "colorMap");
//			locTexture1 =	glGetUniformLocation(uiShaders[eShader], "texDuDv");
//			locMVP =		glGetUniformLocation(uiShaders[eShader], "mvpMatrix");
//			locMV =			glGetUniformLocation(uiShaders[eShader], "mvMatrix");
//			locTime =		glGetUniformLocation(uiShaders[eShader], "fTime");
//
//			//a.water.fFrame = Core::gameVars.timer.frameRate.get_ticks()/100000.0f;
//			//Vector4f vColor = {1.0, 1.0, 1.0, 0.5};
//			//glUniform4fv(locColor,		1,	vColor);
//			glUniform4fv(locColor,		1,	a.water.vColor);
//			glUniform1i(locTexture0,	0);
//			glUniform1i(locTexture1,	1);
//			glUniformMatrix4fv(locMVP,	1,	GL_FALSE,	matrix->GetModelViewProjection());
//			glUniformMatrix4fv(locMV,	1,	GL_FALSE,	matrix->GetModelView());
//			glUniform1f(locTime,		a.gameTime.get_ticks()/1000.0f);
//		}
//
//		if (eShader==Core::GLS_PP_CONTRAST) {
//
//		}
//	}

	void Shader_System::readSrc(const char *shaderSrc, GLuint uiShaderNum) {
		GLchar *pString[1];

		pString[0] = (GLchar *)shaderSrc;
		glShaderSource(uiShaderNum, 1, (const GLchar **)pString, NULL);
	}

	GLuint Shader_System::loadShader2(const char *vertSrc, const char *fragSrc, ...) {
		GLuint uiVertShader;
		GLuint uiFragShader;
		GLuint uiReturn=0;
		GLint iTestVal;

		if (debug) printf("\tCreating Shaders...\t\t\t");
		uiVertShader = glCreateShader(GL_VERTEX_SHADER);
		uiFragShader = glCreateShader(GL_FRAGMENT_SHADER);
		if (debug) printf("[Done]\n");

		if (debug) printf("\tLoading Vertex Core.shader...\t\t");
		readSrc((const char *)vertSrc, uiVertShader);
		if (debug) printf("[Done]\n");

		if (debug) printf("\tLoading Fragment Core.shader...\t\t");
		readSrc((const char *)fragSrc, uiFragShader);
		if (debug) printf("[Done]\n");

		if (debug) printf("\tCompiling Shaders...\t\t\t");
		glCompileShader(uiVertShader);
		glCompileShader(uiFragShader);
		if (debug) printf("[Done]\n");

		if (debug) printf("\tCheck Vertex Shader for Errors...\t");
		glGetShaderiv(uiVertShader, GL_COMPILE_STATUS, &iTestVal);
		if (!iTestVal) {
			char infoLog[1024];

			glGetShaderInfoLog(uiVertShader, 4096, NULL, infoLog);
			if (debug2) printf("[Vertex Shader Failure]\n%i\n\n", uiVertShader);
			if (debug2) printf("[Source]\n%s\n\n[Log]\n'%s'\n\n", vertSrc, infoLog);
			abort();
		}
		else if (debug) printf("[No Errors]\n");

		if (debug) printf("\tCheck Fragment Shader for Errors...\t");
		glGetShaderiv(uiFragShader, GL_COMPILE_STATUS, &iTestVal);
		if (!iTestVal) {
			char infoLog[1024];

			glGetShaderInfoLog(uiFragShader, 4096, NULL, infoLog);
			if (debug2) printf("[Fragment Shader Failure]\n%i\n\n", uiFragShader);
			if (debug2) printf("[Source]\n%s\n\n[Log]\n'%s'\n\n", fragSrc, infoLog);
			abort();
		}
		else if (debug) printf("[No Errors]\n");

		if (debug) printf("\tAttaching Shaders...\t\t\t");
		uiReturn = glCreateProgram();
		glAttachShader(uiReturn, uiVertShader);
		glAttachShader(uiReturn, uiFragShader);
		if (debug) printf("[Done]\n");

		if (debug) printf("\tCreate Fragment Argument List...\t");
		va_list attributeList;

		try {
			va_start(attributeList, fragSrc);
			char *szNextArg;
			int iArgCount = va_arg(attributeList, int);
			for (int i=0; i < iArgCount; i++) {
				int index = va_arg(attributeList, int);
				szNextArg = va_arg(attributeList, char*);
				glBindAttribLocation(uiReturn, index, szNextArg);
			}
			va_end(attributeList);
			if (debug) printf("[Done]\n");
		}
		catch( char * str ) {
			if (debug) printf("[Failed]: %s\n", str);
			abort();
		}

		if (debug) printf("\tLink Program...\t\t\t\t");
		glLinkProgram(uiReturn);
		if (debug) printf("[Done]\n");

		if (debug) printf("\tDelete Local Shaders...\t\t\t");
		glDeleteShader(uiVertShader);
		glDeleteShader(uiFragShader);
		if (debug) printf("[Done]\n");

		if (debug) printf("\tCheck Shader Links...\t\t\t");
		glGetProgramiv(uiReturn, GL_LINK_STATUS, &iTestVal);
		if (iTestVal) {
			if (debug) printf("[Done]\n");
		}
		else {
			if (debug) printf("Failed\n");
		}
		if (debug) printf("Success!\n\n");

		return uiReturn;
	}

	GLuint Shader_System::loadShader(const char *vertSrc, const char *geoSrc, const char *fragSrc, ...) {
		GLuint uiVertShader = 0;
		GLuint uiGeoShader	= 0;
		GLuint uiFragShader = 0;
		GLuint uiReturn		= 0;
		GLint iTestVal		= 0;

		if (debug) printf("\tCreating Shaders...\t\t\t");
		uiVertShader = glCreateShader(GL_VERTEX_SHADER);
		if(geoSrc[0] != '\0') {
			uiGeoShader = glCreateShader(GL_GEOMETRY_SHADER);
		}
		uiFragShader = glCreateShader(GL_FRAGMENT_SHADER);
		if (debug) printf("[Done]\n");

		if (debug) printf("\tLoading Vertex Core.shader...\t\t");
		readSrc((const char *)vertSrc, uiVertShader);
		if (debug) printf("[Done]\n");

		if (debug) printf("\tLoading Geometry Core.shader...\t\t");
		if(geoSrc[0] != '\0') readSrc((const char *)geoSrc, uiGeoShader);
		if (debug) printf("[Done]\n");

		if (debug) printf("\tLoading Fragment Core.shader...\t\t");
		readSrc((const char *)fragSrc, uiFragShader);
		if (debug) printf("[Done]\n");

		if (debug) printf("\tCompiling Shaders...\t\t\t");
		glCompileShader(uiVertShader);
		if(geoSrc[0] != '\0') glCompileShader(uiGeoShader);
		glCompileShader(uiFragShader);
		if (debug) printf("[Done]\n");

		if (debug) printf("\tCheck Vertex Shader for Errors...\t");
		glGetShaderiv(uiVertShader, GL_COMPILE_STATUS, &iTestVal);
		if (!iTestVal) {
			char infoLog[1024];

			glGetShaderInfoLog(uiVertShader, 4096, NULL, infoLog);
			if (debug2) printf("Failed:\n\nSource:\n%s\n\nLog:\n'%s'\n\n", vertSrc, infoLog);
			abort();
		}
		else if (debug) printf("[No Errors]\n");

		if(geoSrc[0] != '\0') {
			if (debug) printf("\tCheck Geometry Shader for Errors...\t");
			glGetShaderiv(uiGeoShader, GL_COMPILE_STATUS, &iTestVal);
			if (!iTestVal) {
				char infoLog[1024];
				glGetShaderInfoLog(uiGeoShader, 4096, NULL, infoLog);
				if (debug2) printf("Failed:\n\nSource:\n%s\n\nLog:\n'%s'\n\n", geoSrc, infoLog);
				abort();
			}
			else if (debug) printf("[No Errors]\n");
		}

		if (debug) printf("\tCheck Fragment Shader for Errors...\t");
		glGetShaderiv(uiFragShader, GL_COMPILE_STATUS, &iTestVal);
		if (!iTestVal) {
			char infoLog[1024];
			glGetShaderInfoLog(uiFragShader, 4096, NULL, infoLog);
			if (debug2) printf("Failed:\n\nSource:\n%s\n\nLog:\n'%s'\n\n", fragSrc, infoLog);
			abort();
		}
		else if (debug) printf("[No Errors]\n");

		if (debug) printf("\tAttaching Shaders...\t\t\t");
		uiReturn = glCreateProgram();
		glAttachShader(uiReturn, uiVertShader);
		if(geoSrc[0] != '\0') glAttachShader(uiReturn, uiGeoShader);
		glAttachShader(uiReturn, uiFragShader);
		if (debug) printf("[Done]\n");

		if (debug) printf("\tCreate Fragment Argument List...\t");
		va_list attributeList;

		try {
			va_start(attributeList, fragSrc);
			char *szNextArg;
			int iArgCount = va_arg(attributeList, int);
			for (int i=0; i < iArgCount; i++) {
				int index = va_arg(attributeList, int);
				szNextArg = va_arg(attributeList, char*);
				glBindAttribLocation(uiReturn, index, szNextArg);
			}
			va_end(attributeList);
			if (debug) printf("[Done]\n");
		}
		catch( char * str ) {
			if (debug) printf("[Failed]: %s\n", str);
		}

		if (debug) printf("\tLink Program...\t\t\t\t");
		glLinkProgram(uiReturn);
		if (debug) printf("[Done]\n");

		if (debug) printf("\tDelete Local Shaders...\t\t\t");
		glDeleteShader(uiVertShader);
		if(geoSrc[0] != '\0') glDeleteShader(uiGeoShader);
		glDeleteShader(uiFragShader);
		if (debug) printf("[Done]\n");

		if (debug) printf("\tCheck Shader Links...\t\t\t");
		glGetProgramiv(uiReturn, GL_LINK_STATUS, &iTestVal);
		if (iTestVal) {
			if (debug) printf("[Done]\n");
		}
		else {
			if (debug) printf("Failed\n");
		}
		if (debug) printf("Success!\n\n");

		return uiReturn;
	}
}
