/*
 * runDebug.h
 *
 *  Created on: Sep 12, 2010
 *      Author: bcthund
 */

#ifndef RUNDEBUG_H_
#define RUNDEBUG_H_

void runDebug(GameVars &gameVars) {
	int temp, theHeight, theWidth;

	/*
	 * Draw Debugging timers
	 */
	//gameSys.drawWindow(2, 1, 41, 18, false, true, gameVars.color.debug);
	//gameSys.drawText(3, 3, gameVars.timer.pTimer.getSplitTicks("Load"));
	//TextSys::timer(int x, int y, Map_si m, int id, int z=20
	int y=2;
//	gameSys.textSys.timer(3, y++, gameVars.timer.pTimer.TimerId, "Load");
//	gameSys.textSys.timer(3, y, gameVars.timer.pTimer.TimerId, "Game Loop");				gameSys.drawText(30, y++, "["+ gameVars.timer.pTimer. +"]");
//	gameSys.textSys.timer(3, y, gameVars.timer.pTimer.TimerId, "Update Atmosphere");
//	gameSys.textSys.timer(3, y, gameVars.timer.pTimer.TimerId, "runVoid");
//	gameSys.textSys.timer(3, y, gameVars.timer.pTimer.TimerId, "runVoid - Update");
//	gameSys.textSys.timer(3, y, gameVars.timer.pTimer.TimerId, "runVoid - Atmosphere");
//	gameSys.textSys.timer(3, y, gameVars.timer.pTimer.TimerId, "runVoid - Water");
//	gameSys.textSys.timer(3, y, gameVars.timer.pTimer.TimerId, "runVoid - Water Prepass");
//	gameSys.textSys.timer(3, y, gameVars.timer.pTimer.TimerId, "runVoid - PostProcess");
//	gameSys.textSys.timer(3, y, gameVars.timer.pTimer.TimerId, "runVoid - Map");
//	gameSys.textSys.timer(3, y, gameVars.timer.pTimer.TimerId, "runVoid - O2D");
//	gameSys.textSys.timer(3, y, gameVars.timer.pTimer.TimerId, "runVoid - Menu");
//	gameSys.textSys.timer(3, y, gameVars.timer.pTimer.TimerId, "runVoid - Debug");
//	gameSys.textSys.timer(3, y, gameVars.timer.pTimer.TimerId, "runBattle");
//	gameSys.textSys.timer(3, y, gameVars.timer.pTimer.TimerId, "SwapBuffers");

//	string name;
//	name = "Game Loop";								gameSys.drawText(3, y, name);		gameSys.drawText(30, y, to_string(gameVars.timer.pTimer.GetAverage(name)));		gameSys.drawText(40, y++, to_string(gameVars.timer.pTimer.GetMax(name)));
//	name = "Update Atmosphere";				gameSys.drawText(3, y, name);		gameSys.drawText(30, y, to_string(gameVars.timer.pTimer.GetAverage(name)));		gameSys.drawText(40, y++, to_string(gameVars.timer.pTimer.GetMax(name)));
//	name = "runVoid";									gameSys.drawText(3, y, name);		gameSys.drawText(30, y, to_string(gameVars.timer.pTimer.GetAverage(name)));		gameSys.drawText(40, y++, to_string(gameVars.timer.pTimer.GetMax(name)));
//	name = "runVoid - Update";				gameSys.drawText(3, y, name);		gameSys.drawText(30, y, to_string(gameVars.timer.pTimer.GetAverage(name)));		gameSys.drawText(40, y++, to_string(gameVars.timer.pTimer.GetMax(name)));
//	name = "runVoid - Atmosphere";		gameSys.drawText(3, y, name);		gameSys.drawText(30, y, to_string(gameVars.timer.pTimer.GetAverage(name)));		gameSys.drawText(40, y++, to_string(gameVars.timer.pTimer.GetMax(name)));
//	name = "runVoid - Water";					gameSys.drawText(3, y, name);		gameSys.drawText(30, y, to_string(gameVars.timer.pTimer.GetAverage(name)));		gameSys.drawText(40, y++, to_string(gameVars.timer.pTimer.GetMax(name)));
//	name = "runVoid - Water Prepass";	gameSys.drawText(3, y, name);		gameSys.drawText(30, y, to_string(gameVars.timer.pTimer.GetAverage(name)));		gameSys.drawText(40, y++, to_string(gameVars.timer.pTimer.GetMax(name)));
//	name = "runVoid - PostProcess";		gameSys.drawText(3, y, name);		gameSys.drawText(30, y, to_string(gameVars.timer.pTimer.GetAverage(name)));		gameSys.drawText(40, y++, to_string(gameVars.timer.pTimer.GetMax(name)));
//	name = "runVoid - Map";						gameSys.drawText(3, y, name);		gameSys.drawText(30, y, to_string(gameVars.timer.pTimer.GetAverage(name)));		gameSys.drawText(40, y++, to_string(gameVars.timer.pTimer.GetMax(name)));
//	name = "runVoid - O2D";						gameSys.drawText(3, y, name);		gameSys.drawText(30, y, to_string(gameVars.timer.pTimer.GetAverage(name)));		gameSys.drawText(40, y++, to_string(gameVars.timer.pTimer.GetMax(name)));
//	name = "runVoid - Menu";					gameSys.drawText(3, y, name);		gameSys.drawText(30, y, to_string(gameVars.timer.pTimer.GetAverage(name)));		gameSys.drawText(40, y++, to_string(gameVars.timer.pTimer.GetMax(name)));
//	name = "runVoid - Debug";					gameSys.drawText(3, y, name);		gameSys.drawText(30, y, to_string(gameVars.timer.pTimer.GetAverage(name)));		gameSys.drawText(40, y++, to_string(gameVars.timer.pTimer.GetMax(name)));
//	name = "runBattle";								gameSys.drawText(3, y, name);		gameSys.drawText(30, y, to_string(gameVars.timer.pTimer.GetAverage(name)));		gameSys.drawText(40, y++, to_string(gameVars.timer.pTimer.GetMax(name)));
//	name = "SwapBuffers";							gameSys.drawText(3, y, name);		gameSys.drawText(30, y, to_string(gameVars.timer.pTimer.GetAverage(name)));		gameSys.drawText(40, y++, to_string(gameVars.timer.pTimer.GetMax(name)));




//	temp=0 + gameVars.debug.time.capture+
//			 gameVars.debug.time.window+
//			 gameVars.debug.time.command+
//			 gameVars.debug.time.buffer;
//	if (temp>0) {
//		theHeight=19;
//		theWidth=26;
//		gameSys.winSys.drawT(1, theHeight, theWidth, gameVars.color.debug);
//		if (gameVars.debug.time.capture) {
//			gameSys.winSys.drawHSpace(1, ++theHeight, theWidth, gameVars.color.debug);
////			gameSys.textSys.timer(2, theHeight, gameSys.textSys.id["Capture"]);
//		}
//		if (gameVars.debug.time.window) {
//			gameSys.winSys.drawHSpace(1, ++theHeight, theWidth, gameVars.color.debug);
////			gameSys.textSys.timer(2, theHeight, gameSys.textSys.id["Window"]);
//		}
//		if (gameVars.debug.time.command) {
//			gameSys.winSys.drawHSpace(1, ++theHeight, theWidth, gameVars.color.debug);
////			gameSys.textSys.timer(2, theHeight, gameSys.textSys.id["Command"]);
//		}
//		if (gameVars.debug.time.buffer) {
//			gameSys.winSys.drawHSpace(1, ++theHeight, theWidth, gameVars.color.debug);
////			gameSys.textSys.timer(2, theHeight, gameSys.textSys.id["Buffer"]);
//		}
//		gameSys.winSys.drawB(1, ++theHeight, theWidth, gameVars.color.debug);
//	}
//
//	if (!gameVars.state.console) {
//		temp=0 + gameVars.debug.time.load+
//				 gameVars.debug.time.gameLoop+
//				 gameVars.debug.time.debug;
//		if (temp>0) {
//			theHeight=1;
//			theWidth=26;
//			gameSys.winSys.drawT(1, theHeight, theWidth, gameVars.color.debug);
//			if (gameVars.debug.time.load) {
//				gameSys.winSys.drawHSpace(1, ++theHeight, theWidth, gameVars.color.debug);
////				gameSys.textSys.timer(2, theHeight, gameSys.textSys.id["Load"]);
//			}
//			if (gameVars.debug.time.gameLoop) {
//				gameSys.winSys.drawHSpace(1, ++theHeight, theWidth, gameVars.color.debug);
////				gameSys.textSys.timer(2, theHeight, gameSys.textSys.id["GameLoop"]);
//			}
//			if (gameVars.debug.time.debug){
//				gameSys.winSys.drawHSpace(1, ++theHeight, theWidth, gameVars.color.debug);
////				gameSys.textSys.timer(2, theHeight, gameSys.textSys.id["Debug"]);
//			}
//			gameSys.winSys.drawB(1, ++theHeight, theWidth, gameVars.color.debug);
//		}
//
//		temp=0 + gameVars.debug.time.runWorld+
//				 gameVars.debug.time.input+
//				 gameVars.debug.time.gameUpdate+
//				 gameVars.debug.time.getHeight+
//				 gameVars.debug.time.gameDraw;
//		if (temp>0) {
//			theHeight=9;
//			theWidth=26;
//			gameSys.winSys.drawT(1, theHeight, theWidth, gameVars.color.debug);
//			if (gameVars.debug.time.runWorld) {
//				gameSys.winSys.drawHSpace(1, ++theHeight, theWidth, gameVars.color.debug);
////				gameSys.textSys.timer(2, theHeight, gameSys.textSys.id["runWorld"]);
//			}
//			if (gameVars.debug.time.input) {
//				gameSys.winSys.drawHSpace(1, ++theHeight, theWidth, gameVars.color.debug);
////				gameSys.textSys.timer(2, theHeight, gameSys.textSys.id["Input"]);
//			}
//			if (gameVars.debug.time.gameUpdate) {
//				gameSys.winSys.drawHSpace(1, ++theHeight, theWidth, gameVars.color.debug);
////				gameSys.textSys.timer(2, theHeight, gameSys.textSys.id["GameUpdate"]);
//			}
//			if (gameVars.debug.time.getHeight) {
//				gameSys.winSys.drawHSpace(1, ++theHeight, theWidth, gameVars.color.debug);
////				gameSys.textSys.timer(2, theHeight, gameSys.textSys.id["getHeight"]);
//			}
//			if (gameVars.debug.time.gameDraw) {
//				gameSys.winSys.drawHSpace(1, ++theHeight, theWidth, gameVars.color.debug);
////				gameSys.textSys.timer(2, theHeight, gameSys.textSys.id["GameDraw"]);
//			}
//			gameSys.winSys.drawB(1, ++theHeight, theWidth, gameVars.color.debug);
//		}
//	}

	//gameSys.textSys.draw(23, 36, "Destroyer-0.1.0 R3");

//	printf("FPS: %f\n", gameVars.timer.fps.frameRate);

	int iX = (gameVars.font.vMax[0]/2)+1;

	gameSys.drawWindow(iX, 1, 20, 8, false, true, gameVars.color.debug);
	gameSys.textSys.draw(++iX, 2, 5, "FPS:", &gameVars.timer.fps.frameRate);
	if (gameVars.state.dungeon) {
		gameSys.textSys.draw(iX++, 3, 5, "  X:", &gameVars.transform.dunPos[0], false);
		gameSys.textSys.draw(iX, 4, 5, "  Y:", &gameVars.transform.dunPos[1], false);
		gameSys.textSys.draw(iX, 5, 5, "  Z:", &gameVars.transform.dunPos[2], false);
		gameSys.textSys.draw(iX, 6, 5, " XR:", &gameVars.transform.dunRot[0]);
		//gameSys.textSys.draw(iX, 7, 5, " YR:", &M_RadToDeg(gameVars.transform.dunRot[1]));
	}
	else {
		/*
		 * Coordinates and Rotations
		 */
		//gameSys.textSys.draw(iX++, 3, 5, "  X:",	&gameVars.player.active->transform.pos[0], true);
		gameSys.drawText(iX++, 3, "X:");	gameSys.drawText(iX+5, 3, std::to_string(gameVars.player.active->transform.pos[0]));

		gameSys.textSys.draw(iX, 4, 5, "  Y:",		&gameVars.player.active->transform.pos[1], true);
		gameSys.textSys.draw(iX, 5, 5, "  Z:",		&gameVars.player.active->transform.pos[2], true);



		int iCompass;
		iCompass = M_RadToDeg(gameVars.player.active->transform.rot[0]);
		gameSys.drawText(iX+1, 6, "XR:");	gameSys.drawText(iX+5, 6, itoa((int)(iCompass), 10));
		iCompass = M_RadToDeg(gameVars.player.active->transform.rot[1]);
		gameSys.drawText(iX+1, 7, "YR:");	gameSys.drawText(iX+5, 7, itoa((int)(iCompass), 10));

		//gameSys.textSys.draw(iX, 6, 5, " XR:",		&gameVars.player.active->transform.rot[0]);
		//gameSys.textSys.draw(iX, 7, 5, " YR:", &gameVars.player.active->transform.rot[1]);
		//gameSys.textSys.draw(iX, 7, 5, " YR:", M_RadToDeg(&gameVars.player.active->transform.rot[1]));
	}

	/*
	 * Time of day Information
	 */
	iX = (gameVars.font.vMax[0]/2)-12;
	gameSys.drawWindow(iX++, 1, 12, 8, false, true, gameVars.color.debug);
	gameSys.textSys.draw(iX, 2, 5, "day:",  &world.atmosphere.gameTime.iDay);
	gameSys.textSys.draw(iX, 3, 5, "Year:", &world.atmosphere.gameTime.iYear);

	int iHour = world.atmosphere.gameTime.GetHour(),
		iMinute = world.atmosphere.gameTime.GetMinute(),
		iSecond = world.atmosphere.gameTime.GetSecond();

	gameSys.textSys.draw(iX, 4, 5, "Hour:", &iHour);
	gameSys.textSys.draw(iX, 5, 5, "Min:",  &iMinute);
	gameSys.textSys.draw(iX, 6, 5, "Sec:",  &iSecond);

	string t;
	int o=1;
//	t = "Query #0 = " + to_string(occlusion.ReadResultui("World Map", 0));	gameSys.drawText(gameVars.font.vMax[0]-30, o++, t);
//	t = "Query #1 = " + to_string(occlusion.ReadResultui("World Map", 1));	gameSys.drawText(gameVars.font.vMax[0]-30, o++, t);
//	t = "Query #2 = " + to_string(occlusion.ReadResultui("World Map", 2));	gameSys.drawText(gameVars.font.vMax[0]-30, o++, t);
//	t = "Query #3 = " + to_string(occlusion.ReadResultui("World Map", 3));	gameSys.drawText(gameVars.font.vMax[0]-30, o++, t);
//	t = "Query #4 = " + to_string(occlusion.ReadResultui("World Map", 4));	gameSys.drawText(gameVars.font.vMax[0]-30, o++, t);
//	t = "Query #5 = " + to_string(occlusion.ReadResultui("World Map", 5));	gameSys.drawText(gameVars.font.vMax[0]-30, o++, t);
//	t = "Query #6 = " + to_string(occlusion.ReadResultui("World Map", 6));	gameSys.drawText(gameVars.font.vMax[0]-30, o++, t);
//	t = "Query #7 = " + to_string(occlusion.ReadResultui("World Map", 7));	gameSys.drawText(gameVars.font.vMax[0]-30, o++, t);
//	t = "Query #8 = " + to_string(occlusion.ReadResultui("World Map", 8));	gameSys.drawText(gameVars.font.vMax[0]-30, o++, t);

	t = "   Total Samples = " + to_string(world.atmosphere.sun.iQuadSamples);		gameSys.drawText(gameVars.font.vMax[0]-30, o++, t);
	float ratio = float(occlusion.GetResultui("ApplyLensFlare"))/float(world.atmosphere.sun.iQuadSamples);
	t = "Detected Samples = " + to_string(occlusion.GetResultui("ApplyLensFlare"));	gameSys.drawText(gameVars.font.vMax[0]-30, o++, t);
	t = "    Sample Ratio = " + to_string(ratio);									gameSys.drawText(gameVars.font.vMax[0]-30, o++, t);
	o++;

	/*
	 * Show Bounding Volume Information
	 */
	/*
	for (int x=0; x<gameVars.screen.iTerrainGrid; x++) {
		for (int z=0; z<gameVars.screen.iTerrainGrid; z++) {
			for (int c=0; c <= world.o3d.data[x][z].idcount; c++) {
				t = world.o3d.data[x][z].file[c];																	gameSys.drawText(gameVars.font.vMax[0]-30, o,   t);
				t = to_string(world.o3d.data[x][z].bV->Test.OBB_Point(gameVars.player.active->transform.pos));		gameSys.drawText(gameVars.font.vMax[0]-10, o++, t);
				//Core.matrix.Translate(data[x][z].x[count]*gameVars->screen.iScale, data[x][z].blend[count], data[x][z].z[count]*gameVars->screen.iScale);
			}
		}
	}
	*/
















//	o++;
//	t = "    Sun Altitude = " + to_string(world.atmosphere.sun.fLightAltitude);		gameSys.drawText(gameVars.font.vMax[0]-30, o++, t);
//	t = "     Sun Azimuth = " + to_string(world.atmosphere.sun.fLightAzimuth);		gameSys.drawText(gameVars.font.vMax[0]-30, o++, t);
//	o++;
//	if(world.atmosphere.sun.fLightAltitude < 90) {
//		t = "Morning";																gameSys.drawText(gameVars.font.vMax[0]-30, o++, t);
//	} else {
//		t = "Evening";																gameSys.drawText(gameVars.font.vMax[0]-30, o++, t);
//	}
//	t = "    fS = " + to_string(world.atmosphere.skybox.thermosphere.fS);			gameSys.drawText(gameVars.font.vMax[0]-30, o++, t);
//	t = "    fD = " + to_string(world.atmosphere.skybox.thermosphere.fD);			gameSys.drawText(gameVars.font.vMax[0]-30, o++, t);
	//skybox.thermosphere.fS

//	try {

//		gameSys.spriteSys.draw(10,          10,     512,  288, gameVars.color.white, world.atmosphere.water.texRefract);
		//gameSys.spriteSys.draw(10,          10,     512,  288, gameVars.color.white, world.texRefract);
//		gameSys.spriteSys.draw(gameVars.screen.w-512-10, 10+288, 512, -288, gameVars.color.white, world.atmosphere.water.texDepth);

		//gameSys.spriteSys.draw(world.atmosphere, 1280-512-10, 10+288, 512, -288, gameVars.color.white, world.texRefract, GLS_OVERLAY_UNDERWATER);
	//gameSys.spriteSys.draw(world.atmosphere, 1280-512-10, 10+288, 512, -288, gameVars.color.white, world.texRefract, GLS_SCATTER);
	//gameSys.spriteSys.draw(world.atmosphere, 10, 10, 10, 512, 288, GLS_SCATTER);
//
//		//gameSys.spriteSys.draw(1366/2-512/2,     10, 512,  288, false, gameVars.color.white, world.atmosphere.water.texReflect);
//		//gameSys.spriteSys.draw(1366/2-512/2, 10+288, 512, -288, false, tempColor, world.atmosphere.water.texRefract);
//	}
//	catch(...) {
//		cout << "Error!" << endl;
//	};
}

#endif /* RUNDEBUG_H_ */
