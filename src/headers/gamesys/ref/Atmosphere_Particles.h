/*
 * SpriteSys.h
 *
 *  Created on: Jun 7, 2015
 *      Author: bcthund
 */

#ifndef ATMOSPHERE_PARTICLES_H_
#define ATMOSPHERE_PARTICLES_H_

/*
 * This is only here because we want access to the WorldMap class
 *  which is important because we want to get the height that
 *  the particle should disappear at.
 *
 *  We are currently NOT USING THIS, we may add it in the future
 *   so we can have better control over where the snowflakes
 *   are discarded because we need access to either the WorldMap
 *   or the water object contained within _TheVoid, both of which
 *   would require a separate header file such as this to make it
 *   work unless I come up with something better.
 *
 * This is very bad programming practive to do this with the header
 *  but this is a tricky situation and I really want to avoid
 *  global variables for this kind of stuff.
 */

/*
 * Currently only some of these are used:
 * 	CALC:
 * 		RAIN:		NO
 * 		HAIL:		NO
 * 		SNOW:		NO
 * 		FLORA:		YES
 * 		UWFLORA:	YES
 * 		GRASS:		YES
 */
bool Atmosphere::calc(uint mode, WorldMap &map, bool bUpdate=false) {
	try {
		if(mode == RAIN) {
			if (gameVars->debug.load) std::cout << "## CALC RAIN 2 ##" << endl;
		}
		else if(mode == SNOW) {
			if (gameVars->debug.load) std::cout << "## CALC SNOW 2 ##" << endl;
		}
		else if(mode == FLORA) {
			if (gameVars->debug.load) std::cout << "## CALC FLORA 2 ##" << endl;

			/*
			Vector2f vCoords[] = { 0.0, 0.0,
								   0.0, 1.0,
								   1.0, 0.0,
								   1.0, 1.0 };
			*/

			int iVerts = flora.iNum*2; //Number of vertices

			if(!bUpdate) {
				cout << "Creating " << flora.tex.iLoaded << " VAO's...";
				flora.vao = new VAO[flora.tex.iLoaded];
				cout << "Done." << endl;

				cout << "  Creating " << flora.tex.iLoaded << " arrays of " << iVerts << " vVerts...";
				flora.vVerts = new Data3f*[flora.tex.iLoaded];
				for(int i=0; i<flora.tex.iLoaded; i++) flora.vVerts[i] = new Data3f[iVerts];
				cout << "Done." << endl;

				cout << "  Creating " << flora.tex.iLoaded << " arrays of " << iVerts << " vSize...";
				flora.vSize = new Data3f*[flora.tex.iLoaded];
				for(int i=0; i<flora.tex.iLoaded; i++) flora.vSize[i] = new Data3f[iVerts];
				cout << "Done." << endl;
			}

			/*
			 * Create vVerts structures
			 */
			std::uniform_real_distribution<> dist(0, 360);
			std::uniform_real_distribution<> sizeX(flora.iMinWidth, flora.iMaxWidth);
			std::uniform_real_distribution<> sizeY(flora.iMinHeight, flora.iMaxHeight);
			for(int t=0; t<flora.tex.iLoaded; t++) {
				for(int i=0; i<(iVerts); i+=2) {
					/*
					 * We need to do a weighted randomzer for the distance
					 * To do this we need to create a tiered randomizer
					 *   with a percentage chance determining which range
					 *   to use.
					 *
					 * Randomize 1-20:
					 *   1-2:   Distance = 0-25%   [10% chance to spawn close]
					 *   3-8:   Distance = 25-50%  [30% chance]
					 *   9-20:  Distance = 50-100% [60% chance]
					 *
					 *  1-2:   0-20%
					 *  3-5:   10-50%
					 *  6-10:  25-100%
					 *  11-20: 50-100%
					 */
					std::uniform_int_distribution<> range(1, 20);
					int iResult = range(RNG::eng);
					int iMax = 0,
						iMin = 0;

					if (iResult <= 1) {
						iMin = flora.iThreshold;
						iMax = 0.2*flora.iRange;
					}
					else if(iResult > 1 && iResult < 4) {
						iMin = 0.2*flora.iRange;
						iMax = 0.4*flora.iRange;
					}
					else if(iResult >= 4 && iResult < 11) {
						iMin = 0.4*flora.iRange;
						iMax = 0.6*flora.iRange;
					}
					else {
						iMin = 0.6*flora.iRange;
						iMax = flora.iRange;
					}

					std::uniform_real_distribution<> rRange(iMin, iMax);

					float fDistance	= rRange(RNG::eng);
					float fAngle	= M_DegToRad(dist(RNG::eng));
					//float fHeight	= 0.0f;

					float fX = (cos(fAngle)*fDistance)-gameVars->player.active->transform.pos[0],
								fZ = (sin(fAngle)*fDistance)-gameVars->player.active->transform.pos[2],
								fY = -map.getHeight(-fX, -fZ)*gameVars->screen.iScale,
								sX = sizeX(RNG::eng),
								sY = sizeY(RNG::eng);
								//fX = (cos(fAngle)*fDistance)-(gameVars->player.active->transform.pos[0]*gameVars->screen.iScale);
								//fZ = (sin(fAngle)*fDistance)-(gameVars->player.active->transform.pos[2]*gameVars->screen.iScale);

					/*
					Vector4f vVerts[]	=	{	{	-fW,	fH,		0.0, count+1	},
											{		-fW,	0.0f,	0.0, count+1	},
											{		 fW,	fH,		0.0, count+1	},
											{		 fW,	0.0f,	0.0, count+1	}	};
					*/

					flora.vVerts[t][i][0] = fX*gameVars->screen.iScale;
					flora.vVerts[t][i][1] = fY+sY*flora.fScale;
					flora.vVerts[t][i][2] = fZ*gameVars->screen.iScale;

					flora.vVerts[t][i+1][0] = fX*gameVars->screen.iScale;
					flora.vVerts[t][i+1][1] = fY;
					flora.vVerts[t][i+1][2] = fZ*gameVars->screen.iScale;

					flora.vSize[t][i][0] = sX*flora.fScale;
					flora.vSize[t][i][1] = sY*flora.fScale;
					flora.vSize[t][i][2] = flora.iRange;

					flora.vSize[t][i+1][0] = sX*flora.fScale;
					flora.vSize[t][i+1][1] = sY*flora.fScale;
					flora.vSize[t][i+1][2] = flora.iRange;

					/*
					 * Retry if we spawned below water
					 */
					//if(flora.vVerts[t][i+1][1] <= flora.fFloor) i-=2;
					//else if(flora.vVerts[t][i+1][1] >= flora.fCeiling) i-=2;
				}

				cout << "  Creating VAO #" << t << "...";
				//if(flora.iInstance>0) flora.vao[t].Begin(GL_POINTS, iVerts, 1, flora.iInstance);
				//else flora.vao[t].Begin(GL_LINES, iVerts, 1);
				flora.vao[t].Begin(GL_LINES, iVerts, 1);
				flora.vao[t].CopyData(GLA_VERTEX, flora.vVerts[t]);
				flora.vao[t].CopyData(GLA_NORMAL, flora.vSize[t]);
				//if(flora.iInstance>0) if(!bUpdate) flora.vao[t].CopyData(GLA_POSITION, flora.vPosition);
				flora.vao[t].End();
				cout << "Done." << endl;
			}
		}
		else if(mode == UWFLORA) {
			if (gameVars->debug.load) std::cout << "## CALC UNDERWATER FLORA 2 ##" << endl;

			/*
			Vector2f vCoords[] = { 0.0, 0.0,
								   0.0, 1.0,
								   1.0, 0.0,
								   1.0, 1.0 };
			*/

			int iVerts = uwflora.iNum*2; //Number of vertices

			if(!bUpdate) {
				cout << "Creating " << uwflora.tex.iLoaded << " VAO's...";
				uwflora.vao = new VAO[uwflora.tex.iLoaded];
				cout << "Done." << endl;

				cout << "  Creating " << uwflora.tex.iLoaded << " arrays of " << iVerts << " vVerts...";
				uwflora.vVerts = new Data3f*[uwflora.tex.iLoaded];
				for(int i=0; i<uwflora.tex.iLoaded; i++) uwflora.vVerts[i] = new Data3f[iVerts];
				cout << "Done." << endl;

				cout << "  Creating " << uwflora.tex.iLoaded << " arrays of " << iVerts << " vSize...";
				uwflora.vSize = new Data3f*[uwflora.tex.iLoaded];
				for(int i=0; i<uwflora.tex.iLoaded; i++) uwflora.vSize[i] = new Data3f[iVerts];
				cout << "Done." << endl;
			}

			/*
			 * Create vVerts structures
			 */
			std::uniform_real_distribution<> dist(0, 360);
			std::uniform_real_distribution<> sizeX(uwflora.iMinWidth, uwflora.iMaxWidth);
			std::uniform_real_distribution<> sizeY(uwflora.iMinHeight, uwflora.iMaxHeight);

			int iFail;
			uwflora.bFail = false;
			for(int t=0; t<uwflora.tex.iLoaded; t++) {
				iFail = 0;
				for(int i=0; i<(iVerts); i+=2) {
					/*
					 * We need to do a weighted randomzer for the distance
					 * To do this we need to create a tiered randomizer
					 *   with a percentage chance determining which range
					 *   to use.
					 *
					 * Randomize 1-20:
					 *   1-2:   Distance = 0-25%   [10% chance to spawn close]
					 *   3-8:   Distance = 25-50%  [30% chance]
					 *   9-20:  Distance = 50-100% [60% chance]
					 *
					 *  1-2:   0-20%
					 *  3-5:   10-50%
					 *  6-10:  25-100%
					 *  11-20: 50-100%
					 */
					std::uniform_int_distribution<> range(1, 20);
					int iResult = range(RNG::eng);
					int iMax = 0,
						iMin = 0;

					if (iResult <= 1) {
						iMin = uwflora.iThreshold;
						iMax = 0.2*uwflora.iRange;
					}
					else if(iResult > 1 && iResult < 4) {
						iMin = 0.2*uwflora.iRange;
						iMax = 0.4*uwflora.iRange;
					}
					else if(iResult >= 4 && iResult < 11) {
						iMin = 0.4*uwflora.iRange;
						iMax = 0.6*uwflora.iRange;
					}
					else {
						iMin = 0.6*uwflora.iRange;
						iMax = uwflora.iRange;
					}

					std::uniform_real_distribution<> rRange(iMin, iMax);

					float fDistance	= rRange(RNG::eng);
					float fAngle	= M_DegToRad(dist(RNG::eng));
					//float fHeight	= 0.0f;

					float fX = (cos(fAngle)*fDistance)-gameVars->player.active->transform.pos[0],
								fZ = (sin(fAngle)*fDistance)-gameVars->player.active->transform.pos[2],
								fY = -map.getHeight(-fX, -fZ)*gameVars->screen.iScale,
								sX = sizeX(RNG::eng),
								sY = sizeY(RNG::eng);
								//fX = (cos(fAngle)*fDistance)-(gameVars->player.active->transform.pos[0]*gameVars->screen.iScale);
								//fZ = (sin(fAngle)*fDistance)-(gameVars->player.active->transform.pos[2]*gameVars->screen.iScale);

					/*
					Vector4f vVerts[]	=	{	{	-fW,	fH,		0.0, count+1	},
											{		-fW,	0.0f,	0.0, count+1	},
											{		 fW,	fH,		0.0, count+1	},
											{		 fW,	0.0f,	0.0, count+1	}	};
					*/

					uwflora.vVerts[t][i][0] = fX*gameVars->screen.iScale;
					uwflora.vVerts[t][i][1] = fY+sY*uwflora.fScale;
					uwflora.vVerts[t][i][2] = fZ*gameVars->screen.iScale;

					uwflora.vVerts[t][i+1][0] = fX*gameVars->screen.iScale;
					uwflora.vVerts[t][i+1][1] = fY;
					uwflora.vVerts[t][i+1][2] = fZ*gameVars->screen.iScale;

					uwflora.vSize[t][i][0] = sX*uwflora.fScale;
					uwflora.vSize[t][i][1] = sY*uwflora.fScale;
					uwflora.vSize[t][i][2] = uwflora.iRange;

					uwflora.vSize[t][i+1][0] = sX*uwflora.fScale;
					uwflora.vSize[t][i+1][1] = sY*uwflora.fScale;
					uwflora.vSize[t][i+1][2] = uwflora.iRange;

					/*
					 * Retry if we spawned above/below water
					 */
					//if(uwflora.vVerts[t][i+1][1] <= uwflora.fFloor) { i-=2; ++iFail; }
					//else if(uwflora.vVerts[t][i+1][1] >= uwflora.fCeiling) { i-=2; ++iFail; }
					//else iFail=0;

					//if(iFail >= uwflora.iFail) uwflora.bFail = true;
					//if (uwflora.bFail) break;
				}

				cout << "  Creating VAO #" << t << "...";
				//if(uwflora.iInstance>0) uwflora.vao[t].Begin(GL_POINTS, iVerts, 1, uwflora.iInstance);
				//else uwflora.vao[t].Begin(GL_LINES, iVerts, 1);
				uwflora.vao[t].Begin(GL_LINES, iVerts, 1);
				uwflora.vao[t].CopyData(GLA_VERTEX, uwflora.vVerts[t]);
				uwflora.vao[t].CopyData(GLA_NORMAL, uwflora.vSize[t]);
				//if(uwflora.iInstance>0) if(!bUpdate) uwflora.vao[t].CopyData(GLA_POSITION, uwflora.vPosition);
				uwflora.vao[t].End();
				cout << "Done." << endl;
			}
		}
		else if(mode == GRASS) {
			if (gameVars->debug.load) std::cout << "## CALC GRASS 2 ##" << endl;

			float xPos = -gameVars->player.active->transform.pos[0],
						zPos = -gameVars->player.active->transform.pos[2];

			//cout << " Pos1: " 	<< xPos			    << ", "	<< zPos					<< endl;

			// TODO: [Particles:Grass] REPAIR
			Vector2i vChunk   = { int(xPos/(1024)),						int(zPos/(1024)) };				// Chunk that player is standing on
			Vector2i vWorld   = { (vChunk[0]*1024),						(vChunk[1]*1024) };		// Position in the world
			Vector2i vLocal   = { (int)(xPos-vWorld[0]),		(int)(zPos-vWorld[1]) };			// Position on the current grid
								xPos		= ((xPos-vLocal[0]))+vLocal[0];
								zPos		= ((zPos-vLocal[2]))+vLocal[2];
			Vector2i vCenter  = { int(vLocal[0]/16)*16+8,		int(vLocal[1]/16)*16+8 };			// Center of a terrain grid square, first strip decimal with division, then return to full value, plus half a square (1024/64=16)
			Vector2i vOffset  = { vLocal[0]-vCenter[0],			vLocal[1]-vCenter[1] };				// Not used??
			Vector2i vWCenter = { (vWorld[0])+vCenter[0],			(vWorld[1])+vCenter[1]};				//
			int iRange = grass.iRange*16;	//Range in world units
			int iMaxSpawn = (((grass.iRange*2)+1)*((grass.iRange*2)+1))*2;	//Maximum number of elements in a square grid, will convert to circular

			cout << "  Pos: " 			<< xPos			  	<< ", "	<< zPos					<< endl
				   << "  Chunk: "  		<< vChunk[0]		<< ", "	<< vChunk[1]		<< endl
				   << "  World: "   	<< vWorld[0]		<< ", "	<< vWorld[1]		<< endl
				   << "  Local: "   	<< vLocal[0]		<< ", "	<< vLocal[1]		<< endl
				   << "  Center: "  	<< vCenter[0]		<< ", "	<< vCenter[1]		<< endl
				   << "  Offset: "  	<< vOffset[0]		<< ", "	<< vOffset[1]		<< endl
				   << "  WCenter: " 	<< vWCenter[0]	<< ", "	<< vWCenter[1]	<< endl
				   << "  Range: "   	<< iRange				<< endl
				   << "  MaxSpawn: "	<< iMaxSpawn		<< endl;

			Vector2f * vTemp = new Vector2f[iMaxSpawn];
			int iActual = 0;
			bool bSuccess = false;
			for(int x=vWCenter[0]-iRange; x<=vWCenter[0]+iRange; x+=16) {
				for(int z=vWCenter[1]-iRange; z<=vWCenter[1]+iRange; z+=16) {
					bSuccess = false;
					Vector2f vTest = { fabs((float)(x-vWCenter[0])/iRange), fabs((float)(z-vWCenter[1])/iRange) };
					float fTest = Dot(vTest);
					//cout << "vTest: "	<< vTest[0] << ", " << vTest[1]
					//	 << ", fTest: "	<< fTest;
					if(fTest != 0) {
						if(fTest <= 1.0f) bSuccess = true;
					}
					else {
						if((vTest[0]<iRange) && (vTest[1]<iRange)) {
							bSuccess = true;
						}
					}

					if(bSuccess) {
						vTemp[iActual][0] = x;
						vTemp[iActual][1] = z;
						vTemp[iActual+1][0] = x;
						vTemp[iActual+1][1] = z;
						//cout << "Keeping[" << iActual << "]: " << vTemp[iActual][0] << ", " << vTemp[iActual][1] << endl;
						iActual+=2;
						//cout << "Success: " << x << ", " << z << endl;
					}
					//else cout << ", Discard: " << x << ", " << z << endl;
				}
			}

			cout << "  iActual: " << iActual << endl;
			grass.iNum = iActual;
			grass.vVerts = new Data4f[iActual];
			grass.vNorms = new Data4f[iActual];

			cout << "Populating Grass vVerts and vNorms...";
			//std::uniform_real_distribution<> sizeY(grass.iMinHeight, grass.iMaxHeight);
			for(int i=0; i<(iActual-1); i+=2) {
				/*
				 * We are creating GL_LINES but because we are using
				 *   2 triangles of data the elements have some
				 *   special distribution of the data.
				 *
				 *   vVerts[i][0] = center x position
				 *   vVerts[i][1] = center height
				 *   vVerts[i][2] = center z position
				 *   vVerts[i][3] = Alpha fade factor
				 *
				 *   vNorms[i][0] = x slope for halfspace 1
				 *   vNorms[i][1] = z slope for halfspace 1
				 *   vNorms[i][2] = x slope for halfspace 2
				 *   vNorms[i][3] = z slope for halfspace 2
				 *
				 *   vVerts[i+1][0] = center x position COPY
				 *   vVerts[i+1][1] = center height + standard height
				 *   vVerts[i+1][2] = center z position COPY
				 *   vVerts[i+1][3] = Alpha fade factor COPY
				 *
				 *   vNorms[i+1][0] = x slope for halfspace 1 COPY
				 *   vNorms[i+1][1] = z slope for halfspace 1 COPY
				 *   vNorms[i+1][2] = x slope for halfspace 2 COPY
				 *   vNorms[i+1][3] = z slope for halfspace 2 COPY
				 */

				/* Center position */
				grass.vVerts[i][0]   = vTemp[i][0]*gameVars->screen.iScale;
				grass.vVerts[i][2]   = vTemp[i][1]*gameVars->screen.iScale;
				grass.vVerts[i+1][0] = vTemp[i][0]*gameVars->screen.iScale;
				grass.vVerts[i+1][2] = vTemp[i][1]*gameVars->screen.iScale;

				//cout << "xPos: " << xPos*gameVars->screen.iScale << "\tzPos: " << zPos*gameVars->screen.iScale << "\tx: " << grass.vVerts[i][0] << "\tz: " << grass.vVerts[i][2] << endl;

				/* Get center position height */
				grass.vVerts[i][1] = map.getHeight(-vTemp[i][0], -vTemp[i][1])*gameVars->screen.iScale;
				//grass.vVerts[i+1][1] = grass.vVerts[i][1]+float(grass.iMaxHeight-grass.iMinHeight);
				grass.vVerts[i+1][1] = grass.vVerts[i][1]+float(grass.iMaxHeight);

				/* Alpha modifier (Fade with range) */
				grass.vVerts[i][3]   = grass.iRange*gameVars->screen.iScale*4;
				grass.vVerts[i+1][3] = grass.iRange*gameVars->screen.iScale*4;

				//grass.vVerts[i][3]   = 1024;
				//grass.vVerts[i+1][3] = 1024;

				//grass.vVerts[i][3]   = float(grass.iMaxHeight-grass.iMinHeight)/2;
				//grass.vVerts[i+1][3] = float(grass.iMaxHeight-grass.iMinHeight)/2;

				//cout << "Height Calc: " << -grass.vVerts[i][0] << ", " << -grass.vVerts[i][2] << endl;
				//cout << "Tri 1: " << -grass.vVerts[i][0]-4 << ", " << -grass.vVerts[i][2]+4 << endl;
				//cout << "Tri 2: " << -grass.vVerts[i][0]+4 << ", " << -grass.vVerts[i][2]-4 << endl;

				/*
				 * Figure out height factors for triangle one
				 * This will be halfspace 0
				 */
				float * vHN = new float[4];
				vHN = map.getHeight_Normal(-vTemp[i][0]-4, -vTemp[i][1]+4);

				float Nxy, Nxx, Nzy, Nzz;
				if(vHN[0]<0.0f) {
					Nxx = -vHN[1];
					Nxy = -fabs(vHN[0]);
				}
				else {
					Nxx = vHN[1];
					Nxy = -fabs(vHN[0]);
				}

				if(vHN[2]<0.0f) {
					Nzz = -vHN[1];
					Nzy = -fabs(vHN[2]);
				}
				else {
					Nzz = vHN[1];
					Nzy = -fabs(vHN[2]);
				}
				grass.vNorms[i][0] = Nxy/Nxx;
				grass.vNorms[i][1] = Nzy/Nzz;
				grass.vNorms[i+1][0] = Nxy/Nxx;
				grass.vNorms[i+1][1] = Nzy/Nzz;
				//grass.vVerts[i][1]   = -vHN[3];

				/*
				 * Figure out height factors for triangle two
				 * THis will be halfspace 1
				 */
				vHN = map.getHeight_Normal(-vTemp[i][0]+4, -vTemp[i][1]-4);
				if(vHN[0]<0.0f) {
					Nxx = -vHN[1];
					Nxy = -fabs(vHN[0]);
				}
				else {
					Nxx = vHN[1];
					Nxy = -fabs(vHN[0]);
				}

				if(vHN[2]<0.0f) {
					Nzz = -vHN[1];
					Nzy = -fabs(vHN[2]);
				}
				else {
					Nzz = vHN[1];
					Nzy = -fabs(vHN[2]);
				}

				grass.vNorms[i][2] = Nxy/Nxx;
				grass.vNorms[i][3] = Nzy/Nzz;
				grass.vNorms[i+1][2] = Nxy/Nxx;
				grass.vNorms[i+1][3] = Nzy/Nzz;
			}
			cout << "Done" << endl;

			if(!bUpdate) {
				//		  a=(-8, -8) _______ d=( 8, -8)
				//		             |\    |
				//		             | \   |
				//		             |  o  |		o = (0,0)
				//		             | p \ |
				//		             |____\|
				//		  c=(-8,  8)         b=( 8,  8)
				//
				// abc = halfspace 1
				// abd = halfspace 2
				// halfSpace(Vector3f p, Vector3f c, Vector3f a, Vector3f b)
				// 		p = test point
				//		c = reference point
				//		ab = halfspace line

				cout << "Populating Grass Instances...";
				grass.vPosition = new Data4f[grass.iInstance];
				grass.vExtra = new Data4f[grass.iInstance];
				std::uniform_real_distribution<> rRand(-grass.fSpread*gameVars->screen.iScale, grass.fSpread*gameVars->screen.iScale);
				std::uniform_real_distribution<> rRand2(-grass.iVariation, grass.iVariation);
				std::uniform_real_distribution<> rRand3(0, grass.fThickness);
				std::uniform_real_distribution<> rRand4(0.6, 1.4);
				std::uniform_real_distribution<> vary(-grass.fFloorPlay, grass.fFloorPlay);

				for(int i=0; i<grass.iInstance; i++) {
					grass.vPosition[i][0] = rRand(RNG::eng);				// x offset
					grass.vPosition[i][1] = rRand(RNG::eng);				// z offset
					grass.vPosition[i][2] = rRand2(RNG::eng);				// height modifier
					grass.vPosition[i][3] = grass.fFloor+vary(RNG::eng);	// discard height

					grass.vExtra[i][0] = rRand3(RNG::eng);					// width modifier;
					grass.vExtra[i][1] = SameSide(grass.vPosition[i][0], grass.vPosition[i][1], -8, 8, -8, -8, 8, 8)*2;		// Halfspace of new particle
					grass.vExtra[i][2] = rRand4(RNG::eng);		// Color randomizer
					grass.vExtra[i][3] = 0.0f;

					//cout << "Coord: " << grass.vPosition[i][0] << ", " << grass.vPosition[i][1] << endl;
					//cout << "Halfspaces: " << grass.vExtra[0][1] << ", " << grass.vExtra[1][1] << ", " << grass.vExtra[2][1] << ", " << grass.vExtra[3][1] << endl;
					//cout << "Extra: " << grass.vExtra[i][0] << endl;
				}
				cout << "Done" << endl;
			}

			cout << "  Creating VAO...";
			if(bUpdate) {
				grass.vao.Reset();
				grass.vao.Begin(GL_LINES, iActual, 0, grass.iInstance);
				grass.vao.CopyData(GLA_VERTEX, grass.vVerts);
				grass.vao.CopyData(GLA_NORMAL, grass.vNorms);
				grass.vao.CopyData(GLA_POSITION, grass.vPosition);
				grass.vao.CopyData(GLA_EXTRA, grass.vExtra);
				grass.vao.End();
			}
			else {
				grass.vao.Begin(GL_LINES, iActual, 0, grass.iInstance);
				grass.vao.CopyData(GLA_VERTEX, grass.vVerts);
				grass.vao.CopyData(GLA_NORMAL, grass.vNorms);
				grass.vao.CopyData(GLA_POSITION, grass.vPosition);
				grass.vao.CopyData(GLA_EXTRA, grass.vExtra);
				grass.vao.End();
			}
			cout << "Done." << endl;
			//}
		}
		return true;
	}
	catch(...) {
		return false;
	}
}

void Atmosphere::update(uint mode, WorldMap &map) {
	try {
		if(mode == RAIN) {
//			if(gameVars->timer.frameRate.get_ticks() >= (rain.fLast+rain.iRate)) {
//				long int iNumVerts = rain.iNum*2;
//				/*
//				 * Only check one point of the raindrops
//				 */
//				for(int i=0; i<iNumVerts; i+=2) {
//					if (rain.vVerts[i+1][1] < (rain.fFloor[i])) {
//						std::uniform_real_distribution<> dist(0, 360);
//						float fDistance	= (rand() % (rain.iRange-rain.iThreshold))+rain.iThreshold;
//						float fAngle	= M_DegToRad(dist(RNG::eng));
//						float fHeight	= (rand() % (rain.iMax-rain.iMin)) + rain.iMin;
//
//						float fX = (cos(fAngle)*fDistance)-gameVars->player.active->transform.pos[0];
//						float fY = (fHeight*gameVars->screen.iScale)-gameVars->player.active->transform.pos[1];
//						float fZ = (sin(fAngle)*fDistance)-gameVars->player.active->transform.pos[2];
//
//						rain.vVerts[i][0] = fX*gameVars->screen.iScale;
//						rain.vVerts[i][1] = fY*gameVars->screen.iScale;
//						rain.vVerts[i][2] = fZ*gameVars->screen.iScale;
//						rain.fFloor[i] = -8;	//Water should be the floor for ease
//
//						rain.vVerts[i+1][0] = fX*gameVars->screen.iScale;
//						rain.vVerts[i+1][1] = (fY+rain.fLength)*gameVars->screen.iScale;
//						rain.vVerts[i+1][2] = fZ*gameVars->screen.iScale;
//						rain.fFloor[i+1] = -8;	//Water should be the floor
//					}
//					else if (distanceXZpn(rain.vVerts[i+1], gameVars->player.active->transform.pos) > rain.iRange) {
//						std::uniform_real_distribution<> dist(0, 360);
//						float fDistance	= rain.iRange;
//						float fAngle	= 180+M_DegToRad(dist(RNG::eng));
//						float fHeight	= (rand() % rain.iMax);
//
//						float fX = (cos(fAngle)*fDistance)-gameVars->player.active->transform.pos[0];
//						float fY = fHeight;
//						float fZ = (sin(fAngle)*fDistance)-gameVars->player.active->transform.pos[2];
//
//						rain.vVerts[i][0] = fX*gameVars->screen.iScale;
//						rain.vVerts[i][1] = fY*gameVars->screen.iScale;
//						rain.vVerts[i][2] = fZ*gameVars->screen.iScale;
//						rain.fFloor[i] = -8;	//Water should be the floor for ease
//
//						rain.vVerts[i+1][0] = fX*gameVars->screen.iScale;
//						rain.vVerts[i+1][1] = (fY+rain.fLength)*gameVars->screen.iScale;
//						rain.vVerts[i+1][2] = fZ*gameVars->screen.iScale;
//						rain.fFloor[i+1] = -8;	//Water should be the floor
//					}
//					else {
//						rain.vVerts[i][1] -= rain.fFall;				// Move down according to distance
//						rain.vVerts[i+1][1] -= rain.fFall;				// Move down according to distance
//					}
//				}
//
//				rain.vao.CopyData(GLA_VERTEX, rain.vVerts);
//				rain.vao.End();
//				rain.fLast = gameVars->timer.frameRate.get_ticks();
//			}
		}
		else if(mode == HAIL) {
//			if(gameVars->timer.frameRate.get_ticks() >= (hail.fLast+hail.iRate)) {
//				for(int i=0; i<hail.iNum; i++) {
//					if (hail.vVerts[i][1] < (hail.fFloor[i])) {
//						std::uniform_real_distribution<> dist(0, 360);
//						float fDistance	= (rand() % (hail.iRange-hail.iThreshold))+hail.iThreshold;
//						float fAngle	= M_DegToRad(dist(RNG::eng));
//						float fHeight	= (rand() % (hail.iMax-hail.iMin)) + hail.iMin;
//
//						hail.vVerts[i][0] = (cos(fAngle)*fDistance)-gameVars->player.active->transform.pos[0];
//						hail.vVerts[i][1] = fHeight-gameVars->player.active->transform.pos[1];
//						hail.vVerts[i][2] = (sin(fAngle)*fDistance)-gameVars->player.active->transform.pos[2];
//						hail.fFloor[i] = -8;	//Water should be the floor for ease
//					}
//					else if (distanceXZpn(hail.vVerts[i], gameVars->player.active->transform.pos) > hail.iRange) {
//						std::uniform_real_distribution<> dist(0, 360);
//						float fDistance	= hail.iRange;
//						float fAngle	= 180+M_DegToRad(dist(RNG::eng));
//						float fHeight	= (rand() % hail.iMax);
//
//						hail.vVerts[i][0] = (cos(fAngle)*fDistance)-gameVars->player.active->transform.pos[0];
//						//hail.vVerts[i][1] = fHeight-gameVars->player.active->transform.pos[1];
//						hail.vVerts[i][1] = fHeight;
//						hail.vVerts[i][2] = (sin(fAngle)*fDistance)-gameVars->player.active->transform.pos[2];
//						hail.fFloor[i] = -8;	//Water should be the floor for ease
//					}
//					else hail.vVerts[i][1] -= hail.fFall;				// Move down according to distance
//				}
//
//				hail.vao.CopyData(GLA_VERTEX, hail.vVerts);
//				hail.vao.End();
//				hail.fLast = gameVars->timer.frameRate.get_ticks();
//			}
		}
		else if(mode == SNOW) {
//			if(gameVars->timer.frameRate.get_ticks() >= (snow.fLast+snow.iRate)) {
//				for(int i=0; i<snow.iNum; i++) {
//					if (snow.vVerts[i][1] < (snow.fFloor[i])) {
//						std::uniform_real_distribution<> dist(0, 360);
//						float fDistance	= (rand() % (snow.iRange-snow.iThreshold))+snow.iThreshold;
//						float fAngle	= M_DegToRad(dist(RNG::eng));
//						float fHeight	= (rand() % (snow.iMax-snow.iMin)) + snow.iMin;
//
//						snow.vVerts[i][0] = (cos(fAngle)*fDistance)-gameVars->player.active->transform.pos[0];
//						snow.vVerts[i][1] = fHeight-gameVars->player.active->transform.pos[1];
//						snow.vVerts[i][2] = (sin(fAngle)*fDistance)-gameVars->player.active->transform.pos[2];
//						snow.fFloor[i] = -8;	//Water should be the floor for ease
//					}
//					else if (distanceXZpn(snow.vVerts[i], gameVars->player.active->transform.pos) > snow.iRange) {
//						/*
//						 * This should spawn new particles
//						 * in front of the player only and
//						 * at ANY height and max distance
//						 *
//						 * ! REDO !
//						 * We can't base the new particles off of
//						 * the current viewing direction because
//						 * the player may be backpedaling. So we
//						 * should just create particles at any
//						 * random angle but at maximum distance.
//						 *
//						 * There seems to be a problem getting
//						 * the angles to match up anyway. The
//						 * player rotation and the rotation
//						 * of the particles doesn't seem to
//						 * match.
//						 */
//						//std::uniform_real_distribution<> dist(M_RadToDeg(gameVars->player.active->transform.rot[1])+10, M_RadToDeg(gameVars->player.active->transform.rot[1])-10);
//
//						std::uniform_real_distribution<> dist(0, 360);
//						float fDistance	= snow.iRange;
//						float fAngle	= 180+M_DegToRad(dist(RNG::eng));
//						float fHeight	= (rand() % snow.iMax);
//
//						snow.vVerts[i][0] = (cos(fAngle)*fDistance)-gameVars->player.active->transform.pos[0];
//						//snow.vVerts[i][1] = fHeight-gameVars->player.active->transform.pos[1];
//						snow.vVerts[i][1] = fHeight;
//						snow.vVerts[i][2] = (sin(fAngle)*fDistance)-gameVars->player.active->transform.pos[2];
//						snow.fFloor[i] = -8;	//Water should be the floor for ease
//					}
//					else snow.vVerts[i][1] -= snow.fFall;				// Move down according to distance
//				}
//
//				snow.vao.CopyData(GLA_VERTEX, snow.vVerts);
//				snow.vao.End();
//				snow.fLast = gameVars->timer.frameRate.get_ticks();
//			}
		}
		else if(mode == FLORA) {
			if(gameVars->timer.frameRate.get_ticks() >= (flora.fLast+flora.iRate)) {
				int iVerts = flora.iNum*2;
				for(int t=0; t<flora.tex.iLoaded; t++) {
					bool bMod = false;
					for(int i=0; i<iVerts; i+=2) {
						Vector3f fDist = { gameVars->player.active->transform.pos[0]*gameVars->screen.iScale, gameVars->player.active->transform.pos[1]*gameVars->screen.iScale, gameVars->player.active->transform.pos[2]*gameVars->screen.iScale };
						//cout << "\tDistXZpn: " << distanceXZpn(flora.vVerts[t][i+1], fDist) << "\tRange: " << flora.iRange << endl;
						if (distanceXZpn(Vector3f(flora.vVerts[t][i+1][0], flora.vVerts[t][i+1][1], flora.vVerts[t][i+1][2]), fDist) > flora.iRange*gameVars->screen.iScale) {
							//bool bFail=false;
							//do {
								/*
								 * Need to know direction of travel not angle of view
								 */
								float fMove = gameVars->player.active->transform.GetAngle();
								std::uniform_real_distribution<> rRange(0.8f*flora.iRange, flora.iRange);
								std::uniform_real_distribution<> dist(fMove-80, fMove+80);
								//cout << "fMove: " << fMove << endl;
								//std::uniform_real_distribution<> dist(0, 360);
								std::uniform_real_distribution<> sizeX(flora.iMinWidth, flora.iMaxWidth);
								std::uniform_real_distribution<> sizeY(flora.iMinHeight, flora.iMaxHeight);

								float fDistance	= rRange(RNG::eng);
								float fAngle	= M_DegToRad(dist(RNG::eng));

								//cout << "[" << flora.iRange << "] " << fDistance << "\t" << fAngle << endl;

								//cout << "(" << gameVars->player.active->transform.pos[0] << ", " << gameVars->player.active->transform.pos[2] << ")" << endl;
								//cout << "fDistance: " << fDistance << endl;

								float fX = (cos(fAngle)*fDistance)-(gameVars->player.active->transform.pos[0]),
											fZ = (sin(fAngle)*fDistance)-(gameVars->player.active->transform.pos[2]),
											fY = -map.getHeight(-fX, -fZ)*gameVars->screen.iScale,
											sX = sizeX(RNG::eng),
											sY = sizeY(RNG::eng);

								flora.vVerts[t][i][0] = fX*gameVars->screen.iScale;
								flora.vVerts[t][i][1] = fY+sY*flora.fScale;
								flora.vVerts[t][i][2] = fZ*gameVars->screen.iScale;

								flora.vVerts[t][i+1][0] = fX*gameVars->screen.iScale;
								flora.vVerts[t][i+1][1] = fY;
								flora.vVerts[t][i+1][2] = fZ*gameVars->screen.iScale;

								flora.vSize[t][i][0] = sX*flora.fScale;
								flora.vSize[t][i][1] = sY*flora.fScale;
								flora.vSize[t][i][2] = flora.iRange;

								flora.vSize[t][i+1][0] = sX*flora.fScale;
								flora.vSize[t][i+1][1] = sY*flora.fScale;
								flora.vSize[t][i+1][2] = flora.iRange;

								//cout << "(" << flora.vVerts[t][i][0] << ", " << flora.vVerts[t][i][2] << ")" << endl;

								/*
								 * Retry if we spawned below water
								 */
								//if(flora.vVerts[t][i+1][1] <= flora.fFloor) bFail=true;
								//else bFail=false;
								bMod = true;
							//} while(bFail);
						}
					}

					if(bMod) {
						flora.vao[t].CopyData(GLA_VERTEX, flora.vVerts[t]);
						flora.vao[t].CopyData(GLA_NORMAL, flora.vSize[t]);
						flora.vao[t].End();
					}
				}

				flora.fLast = gameVars->timer.frameRate.get_ticks();
			}
		}
		else if(mode == UWFLORA) {
			if(gameVars->timer.frameRate.get_ticks() >= (uwflora.fLast+uwflora.iRate)) {
				int iVerts = uwflora.iNum*2;
				for(int t=0; t<uwflora.tex.iLoaded; t++) {
					bool bMod = false;
					for(int i=0; i<iVerts; i+=2) {
						Vector3f fDist = { gameVars->player.active->transform.pos[0]*gameVars->screen.iScale, gameVars->player.active->transform.pos[1]*gameVars->screen.iScale, gameVars->player.active->transform.pos[2]*gameVars->screen.iScale };
						//cout << "\tDistXZpn: " << distanceXZpn(uwflora.vVerts[t][i+1], fDist) << "\tRange: " << uwflora.iRange << endl;
						if (distanceXZpn(Vector3f(uwflora.vVerts[t][i+1][0], uwflora.vVerts[t][i+1][1], uwflora.vVerts[t][i+1][2]), fDist) > uwflora.iRange*gameVars->screen.iScale) {
							//bool bFail=false;
							//do {
								/*
								 * Need to know direction of travel not angle of view
								 */
								float fMove = gameVars->player.active->transform.GetAngle();
								std::uniform_real_distribution<> rRange(0.8f*uwflora.iRange, uwflora.iRange);
								std::uniform_real_distribution<> dist(fMove-80, fMove+80);
								//cout << "fMove: " << fMove << endl;
								//std::uniform_real_distribution<> dist(0, 360);
								std::uniform_real_distribution<> sizeX(uwflora.iMinWidth, uwflora.iMaxWidth);
								std::uniform_real_distribution<> sizeY(uwflora.iMinHeight, uwflora.iMaxHeight);

								float fDistance	= rRange(RNG::eng);
								float fAngle	= M_DegToRad(dist(RNG::eng));

								//cout << "[" << uwflora.iRange << "] " << fDistance << "\t" << fAngle << endl;

								//cout << "(" << gameVars->player.active->transform.pos[0] << ", " << gameVars->player.active->transform.pos[2] << ")" << endl;
								//cout << "fDistance: " << fDistance << endl;

								float fX = (cos(fAngle)*fDistance)-(gameVars->player.active->transform.pos[0]),
											fZ = (sin(fAngle)*fDistance)-(gameVars->player.active->transform.pos[2]),
											fY = -map.getHeight(-fX, -fZ)*gameVars->screen.iScale,
											sX = sizeX(RNG::eng),
											sY = sizeY(RNG::eng);

								uwflora.vVerts[t][i][0] = fX*gameVars->screen.iScale;
								uwflora.vVerts[t][i][1] = fY+sY*uwflora.fScale;
								uwflora.vVerts[t][i][2] = fZ*gameVars->screen.iScale;

								uwflora.vVerts[t][i+1][0] = fX*gameVars->screen.iScale;
								uwflora.vVerts[t][i+1][1] = fY;
								uwflora.vVerts[t][i+1][2] = fZ*gameVars->screen.iScale;

								uwflora.vSize[t][i][0] = sX*uwflora.fScale;
								uwflora.vSize[t][i][1] = sY*uwflora.fScale;
								uwflora.vSize[t][i][2] = uwflora.iRange;

								uwflora.vSize[t][i+1][0] = sX*uwflora.fScale;
								uwflora.vSize[t][i+1][1] = sY*uwflora.fScale;
								uwflora.vSize[t][i+1][2] = uwflora.iRange;

								//cout << "(" << uwflora.vVerts[t][i][0] << ", " << uwflora.vVerts[t][i][2] << ")" << endl;

								/*
								 * Retry if we spawned below water
								 */
								//if(uwflora.vVerts[t][i+1][1] <= uwflora.fFloor) bFail=true;
								//else bFail=false;
								bMod = true;
							//} while(bFail);
						}
					}

					if(bMod) {
						uwflora.vao[t].CopyData(GLA_VERTEX, uwflora.vVerts[t]);
						uwflora.vao[t].CopyData(GLA_NORMAL, uwflora.vSize[t]);
						uwflora.vao[t].End();
					}
				}

				uwflora.fLast = gameVars->timer.frameRate.get_ticks();
			}
		}
		else if(mode == GRASS) {
			if(gameVars->timer.frameRate.get_ticks() >= (grass.fLast+grass.iRate) && gameVars->player.active->transform.DidMove()) {
				float xPos = -gameVars->player.active->transform.pos[0],
					  zPos = -gameVars->player.active->transform.pos[2];

				Vector2i vChunk   = { int(xPos/(1024)),						int(zPos/(1024)) };				// Chunk that player is standing on
				Vector2i vWorld   = { (vChunk[0]*1024),						(vChunk[1]*1024) };		// Position in the world
				Vector2i vLocal   = { (int)(xPos-vWorld[0]),		(int)(zPos-vWorld[1]) };			// Position on the current grid
									xPos		= ((xPos-vLocal[0]))+vLocal[0];
									zPos		= ((zPos-vLocal[2]))+vLocal[2];
				Vector2i vCenter  = { int(vLocal[0]/16)*16+8,	int(vLocal[1]/16)*16+8 };
				Vector2i vOffset  = { vLocal[0]-vCenter[0],		vLocal[1]-vCenter[1] };
				Vector2i vWCenter = { (vWorld[0])+vCenter[0],		(vWorld[1])+vCenter[1]};
				int iRange = grass.iRange*16;	//Range in world units
				int iMaxSpawn = (((grass.iRange*2)+1)*((grass.iRange*2)+1))*2;	//Maximum number of elements in a square grid, will convert to circular

//				cout << "  Pos: " 			<< xPos			  	<< ", "	<< zPos					<< endl
//						 << "  Chunk: "  		<< vChunk[0]		<< ", "	<< vChunk[1]		<< endl
//						 << "  World: "   	<< vWorld[0]		<< ", "	<< vWorld[1]		<< endl
//						 << "  Local: "   	<< vLocal[0]		<< ", "	<< vLocal[1]		<< endl
//						 << "  Center: "  	<< vCenter[0]		<< ", "	<< vCenter[1]		<< endl
//						 << "  Offset: "  	<< vOffset[0]		<< ", "	<< vOffset[1]		<< endl
//						 << "  WCenter: " 	<< vWCenter[0]	<< ", "	<< vWCenter[1]	<< endl
//						 << "  Range: "   	<< iRange				<< endl
//						 << "  MaxSpawn: "	<< iMaxSpawn		<< endl;

				bool bMod = false;
				for(int i=0; i<(grass.iNum-1); i+=2) {
					if (distanceXZpn(Vector3f(grass.vVerts[i][0], grass.vVerts[i][1], grass.vVerts[i][2]), gameVars->player.active->transform.pos) > grass.iRange) {
						bMod = true;
					}
				}

				if(bMod) {
					Vector2f * vTemp = new Vector2f[iMaxSpawn];
					int iActual = 0;
					bool bSuccess = false;
					for(int x=vWCenter[0]-iRange; x<=vWCenter[0]+iRange; x+=16) {
						for(int z=vWCenter[1]-iRange; z<=vWCenter[1]+iRange; z+=16) {
							bSuccess = false;
							Vector2f vTest = { fabs((float)(x-vWCenter[0])/iRange), fabs((float)(z-vWCenter[1])/iRange) };
							float fTest = Dot(vTest);
							//cout << "vTest: "	<< vTest[0] << ", " << vTest[1]
							//	 << ", fTest: "	<< fTest;
							if(fTest != 0) {
								if(fTest <= 1.0f) bSuccess = true;
							}
							else {
								if((vTest[0]<iRange) && (vTest[1]<iRange)) {
									bSuccess = true;
								}
							}

							if(bSuccess) {
								vTemp[iActual][0] = x;
								vTemp[iActual][1] = z;
								vTemp[iActual+1][0] = x;
								vTemp[iActual+1][1] = z;
								//cout << "Keeping[" << iActual << "]: " << vTemp[iActual][0] << ", " << vTemp[iActual][1] << endl;
								iActual+=2;
								//cout << ", Success: " << x << ", " << z << endl;
							}
							//else cout << ", Discard: " << x << ", " << z << endl;
						}
					}

					if (grass.iNum !=iActual) {
						grass.iNum = iActual;
						grass.vVerts = new Data4f[iActual];
						grass.vNorms = new Data4f[iActual];
					}

					/*
					 * For now, just reload all of the
					 * grass data until we figure out
					 * how to check for new blocks
					 * to load.
					 */
					for(int i=0; i<(iActual-1); i+=2) {
						/* Center position */
						grass.vVerts[i][0]   = vTemp[i][0]*gameVars->screen.iScale;
						grass.vVerts[i][2]   = vTemp[i][1]*gameVars->screen.iScale;
						grass.vVerts[i+1][0] = vTemp[i][0]*gameVars->screen.iScale;
						grass.vVerts[i+1][2] = vTemp[i][1]*gameVars->screen.iScale;

						/* Get center position height */
						grass.vVerts[i][1] = -map.getHeight(-vTemp[i][0], -vTemp[i][1])*gameVars->screen.iScale;
						//grass.vVerts[i+1][1] = grass.vVerts[i][1]+float(grass.iMaxHeight-grass.iMinHeight)/2;
						grass.vVerts[i+1][1] = grass.vVerts[i][1]+float(grass.iMaxHeight);

						/* Alpha modifier (Fade with range) */
						grass.vVerts[i][3]   = grass.iRange*gameVars->screen.iScale*4;
						grass.vVerts[i+1][3] = grass.iRange*gameVars->screen.iScale*4;
						//grass.vVerts[i][3]   = float(grass.iMaxHeight-grass.iMinHeight)/2;
						//grass.vVerts[i+1][3] = float(grass.iMaxHeight-grass.iMinHeight)/2;

						//cout << "Height Check: " << -grass.vVerts[i][0] << ", " << -grass.vVerts[i][2] << endl;
						//cout << "Tri 1: " << -grass.vVerts[i][0]-4 << ", " << -grass.vVerts[i][2]+4 << endl;
						//cout << "Tri 2: " << -grass.vVerts[i][0]+4 << ", " << -grass.vVerts[i][2]-4 << endl;

						/*
						 * Figure out height factors for triangle one
						 * This will be halfspace 0
						 */
						float * vHN = new float[4];
						vHN = map.getHeight_Normal(-vTemp[i][0]-4, -vTemp[i][1]+4);

						float Nxy, Nxx, Nzy, Nzz;
						if(vHN[0]<0.0f) {
							Nxx = -vHN[1];
							Nxy = -fabs(vHN[0]);
						}
						else {
							Nxx = vHN[1];
							Nxy = -fabs(vHN[0]);
						}

						if(vHN[2]<0.0f) {
							Nzz = -vHN[1];
							Nzy = -fabs(vHN[2]);
						}
						else {
							Nzz = vHN[1];
							Nzy = -fabs(vHN[2]);
						}
						grass.vNorms[i][0] = Nxy/Nxx;
						grass.vNorms[i][1] = Nzy/Nzz;
						grass.vNorms[i+1][0] = Nxy/Nxx;
						grass.vNorms[i+1][1] = Nzy/Nzz;
						//grass.vVerts[i][1]   = -vHN[3];

						/*
						 * Figure out height factors for triangle two
						 * THis will be halfspace 1
						 */
						vHN = map.getHeight_Normal(-vTemp[i][0]+4, -vTemp[i][1]-4);
						if(vHN[0]<0.0f) {
							Nxx = -vHN[1];
							Nxy = -fabs(vHN[0]);
						}
						else {
							Nxx = vHN[1];
							Nxy = -fabs(vHN[0]);
						}

						if(vHN[2]<0.0f) {
							Nzz = -vHN[1];
							Nzy = -fabs(vHN[2]);
						}
						else {
							Nzz = vHN[1];
							Nzy = -fabs(vHN[2]);
						}

						grass.vNorms[i][2] = Nxy/Nxx;
						grass.vNorms[i][3] = Nzy/Nzz;
						grass.vNorms[i+1][2] = Nxy/Nxx;
						grass.vNorms[i+1][3] = Nzy/Nzz;
					}

					//cout << "  Creating VAO...";
					//if(!bUpdate) grass.vao.Begin(GL_LINES, iActual, 0, grass.iInstance);
					grass.vao.CopyData(GLA_VERTEX, grass.vVerts);
					grass.vao.CopyData(GLA_NORMAL, grass.vNorms);
					//if(!bUpdate) grass.vao.CopyData(GLA_POSITION, grass.vPosition);
					grass.vao.End();
					//cout << "Done." << endl;
				}
				grass.fLast = gameVars->timer.frameRate.get_ticks();
			}
		}
	}
	catch(...) {
	}
}

#endif /* ATMOSPHERE_PARTICLES_H_ */
