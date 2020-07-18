/*
 * ply_loader.h
 *
 *  Created on: Mar 5, 2011
 *      Author: bcthund
 */

#ifndef PLY_LOADER_H_
#define PLY_LOADER_H_

#include <fstream>
#include "core_functions.h"

namespace Core {
	class PLY_Loader {
		private:
		protected:
		public:
			Core::Data3f * vVerts;
			Core::Data3f * vNorms;
			Core::Data2f * vCoords;
			GLuint * vIndex;
			//Vector3ui * vGroups;
			GLuint numDrawVerts;
			GLuint numVerts;
			GLuint numFaces;

			void init(int vert, int face);
			//void init(int vert, int face, MapData &initMap);
			void load(std::string loadFile);
			//void load(std::string loadFile, MapData &mapData);
			PLY_Loader();
			~PLY_Loader();
	};

	PLY_Loader::PLY_Loader() {
		numDrawVerts = 0;
		numVerts = 0;
		numFaces = 0;
		vVerts = nullptr;
		vNorms = nullptr;
		vCoords = nullptr;
		//vGroups = nullptr;
		vIndex = nullptr;
	}

	PLY_Loader::~PLY_Loader() {
		//       .................................................................Done
	//	cout << "Destroy PLY Loader...............................................";
		delete[] vVerts;
		delete[] vNorms;
		delete[] vCoords;
		//delete[] vGroups;
		delete [] vIndex;
	//	cout << "Not Implemented" << endl;
	}

	void PLY_Loader::load(std::string loadFile) {
		//clean();
		uint vert=0, face=0;
		uint count=0, vertId=0, faceId=0;
		std::string myLine;
		std::string tempData;

		// Get size from file
		//readFile(loadFile, memBlock);		//Read the data file into memory

		std::ifstream myFile(loadFile.c_str(), std::ios::in);
		if (myFile) {
			while (!myFile.eof()) {
				getline(myFile, myLine);
				if (count == 3) {
					tempData="";
					for (uint i=15; i<myLine.length(); i++) tempData += myLine[i];
					vert = stoi(tempData);
				}
				else if (count == 12) {
					tempData="";
					for (uint i=13; i<myLine.length(); i++)
					tempData += myLine[i];
					face = stoi(tempData);
					count++;
					break;
				}
				count++;
			}

			/*
			 * Extract the data from file
			 */
			numVerts = vert;
			numFaces = face;

			std::string dataLine[numVerts];
			std::string indexLine[numFaces];

			count = 0;
			myFile.seekg(0, std::ios::beg);
			while (!myFile.eof()) {
				getline(myFile, myLine);
				if (myLine != "") {
					if (count > 14 && count <= 14+numVerts) {
						dataLine[vertId] = myLine;
						vertId++;
					}
					else if (count > 14+numVerts && count <= (14+numVerts)+numFaces) {
						indexLine[faceId] = myLine;
						faceId++;
					}
				}
				count++;
			}

			/*
			 * Find the actual number of faces
			 * Add 1 face for every quad encountered
			 */
			count=0;
			for (uint i=0; i<faceId; i++) {
				std::string * mySplit = split(indexLine[i].c_str(), ' ');
				if(stoi(mySplit[0]) == 4) {
					face+=1;	// Add a face to the loaded list
					count+=3;
				}
				count+=3;
				delete[] mySplit;
			}

			/*
			 * Create the correct data structures
			 */
			numFaces = face;
			numDrawVerts = numFaces*3;

			vVerts  = new Core::Data3f[numVerts];
			vNorms  = new Core::Data3f[numVerts];
			vCoords = new Core::Data2f[numVerts];
			vIndex  = new GLuint[numDrawVerts];

			/*
			 * Save the vertex, normal, and coordinate data
			 */
			for (uint i=0; i<vertId; i++) {
				std::string * mySplit = split(dataLine[i].c_str(), ' ');
				vVerts[i][0] =   -strtod(mySplit[0].c_str(), nullptr);
				vVerts[i][1] =    strtod(mySplit[2].c_str(), nullptr);
				vVerts[i][2] =    strtod(mySplit[1].c_str(), nullptr);

				vNorms[i][0] =   -strtod(mySplit[3].c_str(), nullptr);
				vNorms[i][1] =    strtod(mySplit[5].c_str(), nullptr);
				vNorms[i][2] =    strtod(mySplit[4].c_str(), nullptr);

				vCoords[i][0] =   strtod(mySplit[6].c_str(), nullptr);
				vCoords[i][1] = 1-strtod(mySplit[7].c_str(), nullptr);		//Correction for blender texcoord difference
				delete[] mySplit;
			}

			/*
			 * Save the index data and convert quads to triangles
			 */
			count=0;
			for (uint i=0; i<faceId; i++) {
				std::string * mySplit = split(indexLine[i].c_str(), ' ');

				if(stoi(mySplit[0]) == 3) {
					vIndex[count] =   stoi(mySplit[1]);
					vIndex[count+1] = stoi(mySplit[2]);
					vIndex[count+2] = stoi(mySplit[3]);
				}
				else if(stoi(mySplit[0]) == 4) {
					face+=1;	// Add a face to the loaded list

					vIndex[count] =   stoi(mySplit[1]);
					vIndex[count+1] = stoi(mySplit[2]);
					vIndex[count+2] = stoi(mySplit[3]);

					count+=3;

					vIndex[count] =   stoi(mySplit[1]);
					vIndex[count+1] = stoi(mySplit[3]);
					vIndex[count+2] = stoi(mySplit[4]);
				}
				count+=3;
				delete[] mySplit;
			}
		}

	}

	//void PLY_Loader::load(std::string loadFile, MapData &newMap) {
	//	//clean();
	//	uint vert=0, face=0;
	//	uint count=0, vertId=0, faceId=0;
	//	std::string myLine;
	//	std::string tempData;
	//
	//	std::ifstream myFile(loadFile.c_str(), std::ios::in);
	//	if (myFile) {
	//		while (!myFile.eof()) {
	//			getline(myFile, myLine);
	//			if (count == 3) {
	//				tempData="";
	//				for (uint i=15; i<myLine.length(); i++) tempData += myLine[i];
	//				vert = stoi(tempData);
	//			}
	//			else if (count == 12) {
	//				tempData="";
	//				for (uint i=13; i<myLine.length(); i++)
	//				tempData += myLine[i];
	//				face = stoi(tempData);
	//				count++;
	//				break;
	//			}
	//			count++;
	//		}
	//
	//		/*
	//		 * We have to manually destroy the old MapData
	//		 * Why??? Calling new apparently doesn't
	//		 *  automatically destruct the old data. THIS IS STUPID!
	//		 *
	//		 * This causes a double free corruption on occasion though
	//		 * so we need to find a better way to do this.
	//		 */
	//		//newMap.~MapData();
	//		//new(&newMap) MapData(vert, face);
	//		newMap.reset(vert, face);
	//
	//		//init(vert, face, newMap);
	//
	//		std::string dataLine[vert];
	//		std::string indexLine[face];
	//
	//		count = 0;
	//		myFile.seekg(0, std::ios::beg);
	//		while (!myFile.eof()) {
	//			getline(myFile, myLine);
	//			if (myLine != "") {
	//				if (count > 14 && count <= 14+newMap.numVerts) {
	//					dataLine[vertId] = myLine;
	//					vertId++;
	//				}
	//				else if (count > 14+newMap.numVerts && count <= (14+newMap.numVerts)+newMap.numFaces) {
	//					indexLine[faceId] = myLine;
	//					faceId++;
	//				}
	//			}
	//			count++;
	//		}
	//
	//		for (uint i=0; i<vertId; i++) {
	//			std::string * mySplit = split(dataLine[i].c_str(), ' ');
	//
	//			newMap.vVerts[i][0] =   -strtod(mySplit[0].c_str(), nullptr);
	//			newMap.vVerts[i][1] =    strtod(mySplit[2].c_str(), nullptr);
	//			newMap.vVerts[i][2] =    strtod(mySplit[1].c_str(), nullptr);
	//
	//			newMap.vNorms[i][0] =   -strtod(mySplit[3].c_str(), nullptr);
	//			newMap.vNorms[i][1] =    strtod(mySplit[5].c_str(), nullptr);
	//			newMap.vNorms[i][2] =    strtod(mySplit[4].c_str(), nullptr);
	//
	//			newMap.vCoords[i][0] =   strtod(mySplit[6].c_str(), nullptr);
	//			newMap.vCoords[i][1] =   strtod(mySplit[7].c_str(), nullptr);		//Correction for blender texcoord difference
	//			delete[] mySplit;
	//		}
	//
	//		count=0;
	//		for (uint i=0; i<faceId; i++) {
	//			std::string * mySplit = split(indexLine[i].c_str(), ' ');
	//
	//			newMap.vIndex[count] =   stoi(mySplit[1]);
	//			newMap.vIndex[count+1] = stoi(mySplit[2]);
	//			newMap.vIndex[count+2] = stoi(mySplit[3]);
	//
	////			newMap.vIndex[count] =   strtod(mySplit[1].c_str(), nullptr);
	////			newMap.vIndex[count+1] = strtod(mySplit[2].c_str(), nullptr);
	////			newMap.vIndex[count+2] = strtod(mySplit[3].c_str(), nullptr);
	//
	//			newMap.vGroups[i][0] =   stoi(mySplit[1]);
	//			newMap.vGroups[i][1] =   stoi(mySplit[2]);
	//			newMap.vGroups[i][2] =   stoi(mySplit[3]);
	//
	//			//std::cout << mySplit[1] << ", " << mySplit[2] << ", " << mySplit[3] << " | " << to_string(newMap.vGroups[i][0]) << ", " << to_string(newMap.vGroups[i][1]) << ", " << to_string(newMap.vGroups[i][2]) << std::endl;
	//
	//			//newMap.vGroups[i][0] =   strtod(mySplit[1].c_str(), nullptr);
	//			//newMap.vGroups[i][1] =   strtod(mySplit[2].c_str(), nullptr);
	//			//newMap.vGroups[i][2] =   strtod(mySplit[3].c_str(), nullptr);
	//			count+=3;
	//			delete[] mySplit;
	//		}
	//	}
	//}
}
#endif /* PLY_LOADER_H_ */
