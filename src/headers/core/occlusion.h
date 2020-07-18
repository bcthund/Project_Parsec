/*
 * occlusion.h
 *
 *  Created on: Jan 29, 2018
 *      Author: bcthund
 */

#ifndef SRC_HEADERS_COREOCCLUSION_H_
#define SRC_HEADERS_COREOCCLUSION_H_

/*
 * TODO:
 * 	- Add bounding volume pointer (occlusion testing on bounding volumes instead of geometry)
 * 	- Possible add occlusion to all O3D objects by default as pointer, if wanted then initialize the pointer, then bounding volume already available
 */

#include <iostream>

namespace Core {
	class _Occlusion {
		private:
			struct _OcclusionData {
				GLuint		*uiQueryId;					// Holds index of query
				GLuint		uiType;						//
				GLuint		uiResult;					//
				bool		bIsAvailable;				//
				bool		bInUse;						// Is the query in use/result available
				bool		bCreated;					// Does the query exist?
				uint		uiSamples;
				_OcclusionData() {
					uiQueryId		= nullptr;
					uiType			= 0;
					uiResult		= 0;
					bIsAvailable	= false;
					bInUse			= false;
					bCreated		= false;
					uiSamples		= 0;
				}
			};
			uint		uiNum;							// Number of queries
			GLuint		*uiQueryIds;					// Holds index of query
			static const int	MAX_QUERIES	= 32;

			_OcclusionData	*data;						//
			//uint	  		uiNumData;					// Number of created _OCCLUSIONs
			//static uint		MAXDATA = 8;				// Maximum number of _OCCLUSIONs
			Map_si			map;						// string<->uint mapping, can specify OCCLUSION by name
			Map_is			rmap;
			//VAO				vao;

		protected:

		public:
			_Occlusion();
			~_Occlusion();
			void	Init();
			//void	CreateQuery(std::string name, GLuint type, uint num=1);		// Generate OCCLUSION, make name pair, make <num> queries
			//void	CreateQuery(GLuint type, uint num=1);		// Generate OCCLUSION, make name pair, make <num> queries
			void	SetSamples(std::string name, uint uiSamples);
			uint	GetSamples(std::string name);
			float	GetRatio(std::string name);
//			GLuint	Add(std::string name, int type, Vector3f v);
//			GLuint	Add(std::string name, int type, int x, int y);
			GLuint	Add(std::string name, int type);
			void	StartQuery(std::string name, GLuint type=GL_SAMPLES_PASSED);						// Start running a query
			bool	ReadAvailable(std::string name);					// Read the query availability result and store
			bool	GetAvailable(std::string name);						// Get the stored availability
			GLuint	ReadResultui(std::string name);						// Read the query result, for samples and store
			bool	ReadResultb(std::string name);						// Read the query result for boolean (all_samples) and store
			GLuint	GetResultui(std::string name);						// Get the STORED query result
			void	EndQuery(std::string name);							// Finish running a query
	};

	_Occlusion::_Occlusion() {
		//       .................................................................Done
		std::cout << "Create Occlusion.................................................";
			data = new _OcclusionData[MAX_QUERIES];
			uiQueryIds = new GLuint[MAX_QUERIES];
//			glGenQueries(MAX_QUERIES, uiQueryIds);
//			for (int n=0; n<MAX_QUERIES; n++) {
//				std::cout << "(" << uiQueryIds[n] << ")";
//			}
			uiNum = 0;
		std::cout << "Done" << std::endl;
	}

	_Occlusion::~_Occlusion() {
		//       .................................................................Done
		std::cout << "Destroy Occlusion................................................";
		glDeleteQueries(MAX_QUERIES,uiQueryIds);
		delete[] uiQueryIds;
		delete[] data;
		std::cout << "Done" << std::endl;
	}

	/*
	 * type can be:
	 * 		GL_SAMPLES_PASSED
	 * 		GL_ANY_SAMPLES_PASSED
	 * 		GL_ANY_SAMPLES_PASSED_CONSERVATIVE
	 * 		GL_PRIMITIVES_GENERATED
	 * 		GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN
	 * 		GL_TIME_ELAPSED
	 */
//	void _Occlusion::CreateQuery(std::string name, GLuint type, uint num) {
	void _Occlusion::Init() {
		std::cout << "Init Occlusion...................................................";
		glGenQueries(MAX_QUERIES, uiQueryIds);
		for (int n=0; n<MAX_QUERIES; n++) {
			//std::cout << "(" << uiQueryIds[n] << ")";
		}
		std::cout << "Done" << std::endl;
//		if (uiNumData < MAXDATA) {
////			map.insert(make_pair(name, uiNumData));
////			int id						= map[name];
////			data[uiNumData].uiQueryId	= new GLuint[num];
////			data[id].uiNum				= num;
////			data[id].uiType				= type;
////			data[id].bIsAvailable		= false;
////			data[id].bInUse				= new bool[num];
////			data[id].uiResult			= new GLuint[num];
////			for (int i=0; i<num; i++) {
////				data[id].bInUse[i]		= false;
////				data[id].uiResult[i]	= 0;
////			}
////			glGenQueries(num, data[uiNumData].uiQueryId);
//
//			data.uiQueryId			= new GLuint;
//			data.uiNum				= num;
//			data.uiType				= GL_SAMPLES_PASSED;
//			data.bIsAvailable		= false;
//			data.bInUse				= false;
//			data.uiResult			= 0;
////			for (int i=0; i<num; i++) {
////				data.bInUse[i]		= false;
////				data.uiResult[i]	= 0;
////			}
//			glGenQueries(num, data.uiQueryId);
//			data.bCreated = true;
//
////			uiNumData++;
////		}
	}

//	GLuint	_Occlusion::Add(std::string name, int type, Vector3f v) {
//
//	}
//
//	GLuint	_Occlusion::Add(std::string name, int type, int x, int y) {
//
//	}

	GLuint _Occlusion::Add(std::string name, int type) {
		if (uiNum < MAX_QUERIES) {
			map.insert(make_pair(name, uiNum));
////			int id						= map[name];
			data[uiNum].uiQueryId		= &uiQueryIds[uiNum];
			data[uiNum].uiType			= type;
			data[uiNum].bIsAvailable	= false;
			data[uiNum].bInUse			= false;
			data[uiNum].uiResult		= 0;
			data[uiNum].uiSamples		= 0;

//			std::cout << "[Add Occlusion: " << name << " (" << uiNum << ", " << uiQueryIds[uiNum] << ", " << *data[uiNum].uiQueryId << ")]";
////			for (int i=0; i<num; i++) {
////				data[id].bInUse[i]		= false;
////				data[id].uiResult[i]	= 0;
////			}
////			glGenQueries(num, data[uiNumData].uiQueryId);
//
//			data.uiQueryId			= new GLuint;
//			data.uiNum				= num;
//			data.uiType				= GL_SAMPLES_PASSED;
//			data.bIsAvailable		= false;
//			data.bInUse				= false;
//			data.uiResult			= 0;
////			for (int i=0; i<num; i++) {
////				data.bInUse[i]		= false;
////				data.uiResult[i]	= 0;
////			}

			data[uiNum].bCreated = true;

			uiNum++;
		}
		return uiQueryIds[uiNum-1];
	}

	void _Occlusion::SetSamples(std::string name, uint uiSamples) {
		//uint id = siMap[name];

//		if(gameVars->screen.MultiSample) {
//				sun.iQuadSamples = (sun.vQuadSize[0] * 0.5) * (sun.vQuadSize[1] * 0.5) * gameVars->screen.uiMultiSamples;
//			} else {
//				sun.iQuadSamples = (sun.vQuadSize[0] * 0.5) * (sun.vQuadSize[1] * 0.5);
//		}

//		std::cout << "[Set Samples: " << name << " (" << uiSamples << ")]";

		int id = map[name];
		data[id].uiSamples = uiSamples;
	}

	uint _Occlusion::GetSamples(std::string name) {
		//uint id = siMap[name];

//		if(gameVars->screen.MultiSample) {
//				sun.iQuadSamples = (sun.vQuadSize[0] * 0.5) * (sun.vQuadSize[1] * 0.5) * gameVars->screen.uiMultiSamples;
//			} else {
//				sun.iQuadSamples = (sun.vQuadSize[0] * 0.5) * (sun.vQuadSize[1] * 0.5);
//		}

		int id = map[name];
		return data[id].uiSamples;
	}

	float _Occlusion::GetRatio(std::string name) {
		int id = map[name];
		float fReturn = 0.0f;
		if (data[id].uiSamples != 0 ) {
			fReturn = fmin((float(data[id].uiResult)/float(data[id].uiSamples))/100.0f, 100.0f);
		}
		return fReturn;
	}

	void _Occlusion::StartQuery(std::string name, GLuint type) {
//		try {
		int id = map[name];
		if (data[id].bCreated) {
			if(!data[id].bInUse) {
				//std::cout << "[Start Query: " << name << " (" << uiNum << ")]";
				data[id].uiType = type;
				glBeginQuery(data[id].uiType, *data[id].uiQueryId);
				//std::cout << "[" << data.uiType << "] Begin Query" << std::endl;
			}
		}
//		else throw std::string("Query has not been initialized!");
//		}
//		catch(std::string &s) {
//			std::cout << "Internal Exception: " << s << std::endl;
//			std::exit(0);
//		}
//		catch(const char* c) {
//			std::cout << "Internal Exception: " << c << std::endl;
//			std::exit(0);
//		}
//		catch(...) {
//			std::exit(0);
//		}
	}

	bool _Occlusion::ReadAvailable(std::string name) {
		int id = map[name];
		uint bResult = GL_FALSE;
		glGetQueryObjectuiv(*data[id].uiQueryId, GL_QUERY_RESULT_AVAILABLE, &bResult);
		if(bResult==GL_TRUE) data[id].bIsAvailable = true;
		else data[id].bIsAvailable = false;
		//cout << "bIsAvailable = " << data[id].bIsAvailable << endl;
		return data[id].bIsAvailable;
	}

	bool _Occlusion::GetAvailable(std::string name) {
		int id = map[name];
		return data[id].bIsAvailable;
	}

	GLuint _Occlusion::ReadResultui(std::string name) {
		int id = map[name];
		if(ReadAvailable(name)) {
			data[id].bInUse = false;
			glGetQueryObjectuiv(*data[id].uiQueryId, GL_QUERY_RESULT, &data[id].uiResult);
			//std::cout << "ReadResultui = " << data.uiResult << std::endl;
		}
		//else std::cout << ".";
		return data[id].uiResult;	// Return stored result
	}

	bool _Occlusion::ReadResultb(std::string name) {
		int id = map[name];
		if(ReadAvailable(name)) {
			glGetQueryObjectuiv(*data[id].uiQueryId, GL_QUERY_RESULT, &data[id].uiResult);
//			return data.uiResult>=GL_TRUE;		// >= to catch if some or all samples passed if type==GL_SAMPLES_PASSED
		}
		return data[id].uiResult>=GL_TRUE;	// Stored result
	}

	GLuint _Occlusion::GetResultui(std::string name) {
		//cout << "GetResultui = " << data[id].uiResult[num] << endl;
		int id = map[name];
		return data[id].uiResult;
	}

	void _Occlusion::EndQuery(std::string name) {
		int id = map[name];
		if (data[id].bCreated) {
			if(!data[id].bInUse) {
				data[id].bInUse = true;			// Only set bInUse after the entire query is complete
				glEndQuery(data[id].uiType);
				//std::cout << "[" << data.uiType << "] Done" << std::endl;
			}
		}
	}
}

#endif /* SRC_HEADERS_COREOCCLUSION_H_ */
