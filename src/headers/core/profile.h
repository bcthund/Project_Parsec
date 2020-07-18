/*
 * profile.h
 *
 *  Created on: Jun 17, 2019
 *      Author: bcthund
 */

#ifndef HEADERS_CORE_PROFILE_H_
#define HEADERS_CORE_PROFILE_H_

#include "types.h"
#include "ptimer.h"

// TODO: Add sorting functions

namespace Core {

	class _Profile {
		public:
			_Profile();
			virtual ~_Profile();
			struct _DefaultProfiles {
				enum {	RunGame = 0,
						RunGame_O3D,
						RunGame_O2D,
						RunGame_World,
						RunGame_Atmosphere,
						RunGame_Animation,
						RunGame_Skeleton,
						RunGame_PostProcess,
						RunGame_DrawSprite,
						RunGame_DrawIcon,
						RunGame_WinSys,
						RunGame_TextSys,
						RunGame_AudioSys,
						RunGame_Mouseray,
						RunGame_Transform,
						RunGame_GetInput,
						RunGame_GetMouseRay,
						SwapBuffers,
						MapSys_GeneratePerlin,
						RunGame_Particles,
						RunGame_DrawWorld,
						Last
				};

				std::string sNames[Last];

				_DefaultProfiles() {
					sNames[RunGame]					= "RunGame";
					sNames[RunGame_O3D]				= "RunGame_O3D";
					sNames[RunGame_O2D]				= "RunGame_O2D";
					sNames[RunGame_World]			= "RunGame_World";
					sNames[RunGame_Atmosphere]		= "RunGame_Atmosphere";
					sNames[RunGame_Animation]		= "RunGame_Animation";
					sNames[RunGame_Skeleton]		= "RunGame_Skeleton";
					sNames[RunGame_PostProcess]		= "RunGame_PostProcess";
					sNames[RunGame_DrawSprite]		= "RunGame_DrawSprite";
					sNames[RunGame_DrawIcon]		= "RunGame_DrawIcon";
					sNames[RunGame_WinSys]			= "RunGame_WinSys";
					sNames[RunGame_TextSys]			= "RunGame_TextSys";
					sNames[RunGame_AudioSys]		= "RunGame_AudioSys";
					sNames[RunGame_Mouseray]		= "RunGame_Mouseray";
					sNames[RunGame_Transform]		= "RunGame_Transform";
					sNames[RunGame_GetInput]		= "RunGame_GetInput";
					sNames[RunGame_GetMouseRay]		= "RunGame_GetMouseRay";
					sNames[SwapBuffers]				= "SwapBuffers";
					sNames[MapSys_GeneratePerlin]	= "MapSys_GeneratePerlin";
					sNames[RunGame_Particles]		= "RunGame_Particles";
					sNames[RunGame_DrawWorld]		= "RunGame_DrawWorld";
				}
			} builtIn;

			bool bEnable;

			void addProfile		(std::string s);
			void startProfile	(std::string s);
			void stopProfile	(std::string s);
			uint getTime		(std::string s);
			float getAverage	(std::string s, int n=10);
			float getStdDev		(std::string s);
			uint getSamples		(std::string s);
			uint getMin			(std::string s);
			uint getMax			(std::string s);

			void addProfile		(int p);
			void startProfile	(int p);
			void stopProfile	(int p);
			void runProfile		(int p, bool b);
			uint getTime		(int p);
			float getAverage	(int p, int n=10);
			float getStdDev		(int p);
			uint getSamples		(int p);
			uint getMin			(int p);
			uint getMax			(int p);
			void reset			();

		private:
			Core::PTimer timer;
	};

} /* namespace Core */

#endif /* HEADERS_CORE_PROFILE_H_ */
