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

			t_VectorMap<_OcclusionData*> data;

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
			GLuint	add(std::string name, GLuint type);
			void	StartQuery(std::string name, GLuint type=GL_SAMPLES_PASSED);						// Start running a query
			bool	ReadAvailable(std::string name);					// Read the query availability result and store
			bool	GetAvailable(std::string name);						// Get the stored availability
			GLuint	ReadResultui(std::string name);						// Read the query result, for samples and store
			bool	ReadResultb(std::string name);						// Read the query result for boolean (all_samples) and store
			GLuint	GetResultui(std::string name);						// Get the STORED query result
			void	EndQuery(std::string name);							// Finish running a query
	};

	_Occlusion::_Occlusion() {
		Core::debug.log("Construct Occlusion {");
		data.setSource("Occlusion");
		uiQueryIds = new GLuint[MAX_QUERIES];
		uiNum = 0;
		Core::debug.print(" Done ", Core::debug().GREEN);
		Core::debug.print("}\n");
	}

	_Occlusion::~_Occlusion() {
		Core::debug.log("Destroy Occlusion {");
		glDeleteQueries(MAX_QUERIES,uiQueryIds);
		delete[] uiQueryIds;
		for (auto & item : data) {
			delete item;
		}
		Core::debug.print(" Done ", Core::debug().GREEN);
		Core::debug.print("}\n");
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
		Core::debug.log("Init Occlusion {");
		glGenQueries(MAX_QUERIES, uiQueryIds);
		for (int n=0; n<MAX_QUERIES; n++) {
		}
		Core::debug.print(" Done ", Core::debug().GREEN);
		Core::debug.print("}\n");
	}

	GLuint _Occlusion::add(std::string name, GLuint type) {
		_OcclusionData *newData = new _OcclusionData;
		newData->uiQueryId		= &uiQueryIds[uiNum];
		newData->uiType			= type;
		newData->bIsAvailable	= false;
		newData->bInUse			= false;
		newData->uiResult		= 0;
		newData->uiSamples		= 0;
		newData->bCreated 		= true;
		data.add(name, newData);
		uiNum = data.size();
		return uiNum-1;
	}

	void _Occlusion::SetSamples(std::string name, uint uiSamples) {
		data[name]->uiSamples = uiSamples;
	}

	uint _Occlusion::GetSamples(std::string name) {
		return data[name]->uiSamples;
	}

	float _Occlusion::GetRatio(std::string name) {
		int id = data.getID(name);
		float fReturn = 0.0f;
		if (data[id]->uiSamples != 0 ) {
			fReturn = fmin((float(data[id]->uiResult)/float(data[id]->uiSamples))/100.0f, 100.0f);
		}
		return fReturn;
	}

	void _Occlusion::StartQuery(std::string name, GLuint type) {
		int id = data.getID(name);
		if (data[id]->bCreated) {
			if(!data[id]->bInUse) {
				data[id]->uiType = type;
				glBeginQuery(data[id]->uiType, *data[id]->uiQueryId);
			}
		}
	}

	bool _Occlusion::ReadAvailable(std::string name) {
		int id = data.getID(name);
		uint bResult = GL_FALSE;
		glGetQueryObjectuiv(*data[id]->uiQueryId, GL_QUERY_RESULT_AVAILABLE, &bResult);
		if(bResult==GL_TRUE) data[id]->bIsAvailable = true;
		else data[id]->bIsAvailable = false;
		return data[id]->bIsAvailable;
	}

	bool _Occlusion::GetAvailable(std::string name) {
		int id = data.getID(name);
		return data[id]->bIsAvailable;
	}

	GLuint _Occlusion::ReadResultui(std::string name) {
		int id = data.getID(name);
		if(ReadAvailable(name)) {
			data[id]->bInUse = false;
			glGetQueryObjectuiv(*data[id]->uiQueryId, GL_QUERY_RESULT, &data[id]->uiResult);
		}
		return data[id]->uiResult;	// Return stored result
	}

	bool _Occlusion::ReadResultb(std::string name) {
		int id = data.getID(name);
		if(ReadAvailable(name)) {
			glGetQueryObjectuiv(*data[id]->uiQueryId, GL_QUERY_RESULT, &data[id]->uiResult);
		}
		return data[id]->uiResult>=GL_TRUE;	// Stored result
	}

	GLuint _Occlusion::GetResultui(std::string name) {
		int id = data.getID(name);
		return data[id]->uiResult;
	}

	void _Occlusion::EndQuery(std::string name) {
		int id = data.getID(name);
		if (data[id]->bCreated) {
			if(!data[id]->bInUse) {
				data[id]->bInUse = true;			// Only set bInUse after the entire query is complete
				glEndQuery(data[id]->uiType);
			}
		}
	}
}

#endif /* SRC_HEADERS_COREOCCLUSION_H_ */
