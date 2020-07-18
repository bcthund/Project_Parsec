/*
 * water.h
 *
 *  Created on: Sep 19, 2010
 *      Author: bcthund
 */

#ifndef WATER_H_
#define WATER_H_

class Water {
	private:
		Atmosphere &atmosphere;
		float fWave;		//Water wave function
		VAO vao;

	protected:

	public:
		//int iWidth;
		int iHeight;
		int iX;
		int iZ;
		std::string sTexture;	// Water Texture
		std::string sBump;		// Bump Map
		std::string sSpec;		// Specular Map
		std::string sWorld;		// Environment map
		bool bHighRes;			// Enable high resolution mode
		bool init();
		bool init(int x, int z);
		bool init(int x, int y, int z);
		bool init(std::string tex, std::string bump, std::string spec, int w, int h);
		bool load();
		bool calc(bool bUpdate);
		void update(float fTime, float fSpeed, float fScale);
		void draw();
		Water(Atmosphere &a);
		~Water() {
			//       .................................................................Done
			cout << "Destroy Water....................................................Not Implemented" << endl;
		}
};

Water::Water(Atmosphere &a): atmosphere(a) {
	sTexture	= "";
	sBump 		= "";
	//iWidth		= 0;
	fWave		= 0;
	iHeight		= gameVars->world.water.iHeight;
	iX			= 0;
	iZ			= 0;
	bHighRes	= true;
}

bool Water::init(std::string tex, std::string bump, std::string spec, int w, int h) {
	try
	{
		//cout << "Initializing Water...";
		if (gameVars->debug.load) printf("## INIT WATER ##\n");
		sTexture	= tex;
		sBump 		= bump;
		sSpec 		= spec;
		//iWidth		= w;
		iHeight		= h;
		iX			= w;
		iZ			= w;
		cout << "Done" << endl;
		return true;
	}
	catch(...) {
		return false;
	}
}

bool Water::init(int x, int z) {
	try
	{
		//cout << "Initializing Water...";
		if (gameVars->debug.load) printf("## INIT WATER ##\n");
		sTexture	= "water_tex.png";
		sBump 		= "water_bump.png";
		sSpec 		= "water_spec.png";
		sWorld		= "water_world.png";
		//iWidth		= x;
		iHeight		= 0;
		iX			= x;
		iZ			= z;
		cout << "Done" << endl;
		return true;
	}
	catch(...) {
		return false;
	}
}

bool Water::init(int x, int y, int z) {
	try
	{
		//cout << "Initializing Water...";
		if (gameVars->debug.load) printf("## INIT WATER ##\n");
		sTexture	= "water_tex.png";
		sBump 		= "water_bump.png";
		sSpec 		= "water_spec.png";
		sWorld		= "water_world.png";
		//iWidth		= x;
		iHeight		= y;
		iX			= x;
		iZ			= z;
		cout << "Done" << endl;
		return true;
	}
	catch(...) {
		return false;
	}
}

bool Water::init() {
	try
	{
		//cout << "Initializing Water...";
		if (gameVars->debug.load) printf("## INIT WATER ##\n");
		sTexture	= "water_tex.png";
		sBump 		= "water_bump.png";
		sSpec 		= "water_spec.png";
		sWorld		= "water_world.png";
		//iWidth		= ((gameVars->screen.iTerrainGrid/2)*1024)+512;
		iHeight		= gameVars->world.water.iHeight;
		iX			= (gameVars->screen.iTerrainGrid/2)*1024+512;
		iZ			= (gameVars->screen.iTerrainGrid/2)*1024+512;
		cout << "Done" << endl;
		return true;
	}
	catch(...) {
		return false;
	}
}

bool Water::load() {
	try
	{
		//cout << "Loading Water...";
		if (gameVars->debug.load) printf("## LOAD WATER ##\n");
		/*
		 * Load water grid
		 */
		std::string loadFile;
		std::stringstream sStream;
		PLY_Loader loadPly;

		sStream.str("./ply/water.ply");
		loadFile=sStream.str();
		cout << "Loading [" << loadFile << "]-";
		loadPly.load(loadFile);
		cout << "[" << loadPly.numDrawVerts << "][" << loadPly.numVerts << "][" << loadPly.numFaces << "]...";
		vao.Begin(GL_TRIANGLES,		loadPly.numDrawVerts, 1);
		vao.CopyData(GLA_VERTEX,	loadPly.vVerts);
		vao.CopyData(GLA_NORMAL,	loadPly.vNorms);
		vao.CopyData(GLA_TEXTURE,	loadPly.vCoords, 0);
		vao.CopyData(GLA_INDEX,		loadPly.vIndex);
		vao.End();
		cout << "Done" << endl;
		return true;
	}
	catch(...) {
		return false;
	}
}

bool Water::calc(bool bUpdate=false) {
	try {
		if (gameVars->debug.load) printf("## CALC WATER ##\n");
		//cout << "Calculating Water...";
		/*
		//int		iX=(gameVars->screen.iTerrainGrid/2)*1024+512,
		//		iZ=(gameVars->screen.iTerrainGrid/2)*1024+512;

		cout << "ONE" << endl;

		float	fW = iWidth;
		float	fH = iWidth;
		float	fT = iHeight;

		cout << "TWO" << endl;

		Vector3f vVerts[]	=	{	{	 fW+iX, fT,  fH+iZ  },
									{	-fW+iX, fT,  fH+iZ  },
									{	-fW+iX, fT, -fH+iZ 	},

									{	 fW+iX, fT,  fH+iZ	},
									{	-fW+iX, fT, -fH+iZ	},
									{	 fW+iX, fT, -fH+iZ	}	};

		Vector3f vNorms[]	=	{	{	0.0f, 1.0f, 0.0f	},
									{	0.0f, 1.0f, 0.0f	},
									{	0.0f, 1.0f, 0.0f	},

									{	0.0f, 1.0f, 0.0f	},
									{	0.0f, 1.0f, 0.0f	},
									{	0.0f, 1.0f, 0.0f	}	};

		Vector2f vCoords[]	=	{	1.0, 0.0,
									0.0, 0.0,
									0.0, 1.0,

									1.0, 0.0,
									0.0, 1.0,
									1.0, 1.0 };
cout << "THREE" << endl;
		/*
		 * THIS HAS A SPECIFIC VAO SO MAKING COPIES
		 * OF THIS CLASS DOES NOT CURRENTLY WORK.
		 *
		 * We need to make the VAO as something we can specify
		 * so we can have different water levels in different
		 * locations such as in dungeons.
		 *//*
		if (bUpdate) {
			cout << "FOUR-1" << endl;
			new(&vao) VAO();	//We need to create new VAO objects for this to work
cout << "FOUR-2" << endl;
			vao.Begin(GL_TRIANGLES, 6, 1);
			vao.CopyData(GLA_VERTEX, vVerts);
			vao.CopyData(GLA_NORMAL, vNorms);
			vao.CopyData(GLA_TEXTURE, vCoords, 0);
			vao.End();
			cout << "FOUR-3" << endl;
		}
		else {
cout << "FOUR-4" << endl;
			vao.Begin(GL_TRIANGLES, 6, 1);
cout << "FOUR-5" << endl;
			vao.CopyData(GLA_VERTEX, vVerts);
cout << "FOUR-6" << endl;
			vao.CopyData(GLA_NORMAL, vNorms);
cout << "FOUR-7" << endl;
			vao.CopyData(GLA_TEXTURE, vCoords, 0);
cout << "FOUR-8" << endl;
			vao.End();
cout << "FOUR-9" << endl;
		}
cout << "FIVE" << endl;
*/
		cout << "Nothing to do." << endl;
		return true;
	}
	catch(...) {
		cout << "Failed!" << endl;
		return false;
	}
}

void Water::update(float fTime, float fSpeed=10.0, float fScale=1.0) {

	//float fWave = sin(gameVars->timer.frameRate.get_ticks()*1.0)*1.0;
	//cout << "Time Modifier(" << gameVars->timer.frameRate.get_ticks() << ") : " << fWave << endl;
	//float fTime = gameVars->timer.frameRate.get_ticks()/10000;
	//cout << "Ticks: " << fTime << "Sin: " << sin(fTime*fSpeed)*fScale << endl;

	fWave = sin(fTime*fSpeed)*fScale;

	//cout << "Time Modifier: " << fWave << endl;
}

void Water::draw() {
	glDisable(GL_CULL_FACE);
	int iShader=GLS_DIRECTIONAL_WATER;
	Core.shader.use(iShader);

	Core.matrix.Push();

		//Do wave functionality
		//Core.matrix.Translate(0.0f, fWave, 0.0f);
		Core.matrix.Translate(iX, iHeight, iZ);
		//Core.matrix.Translate(1024+512, iHeight, 1024+512);
		Core.matrix.Scale(48);
		Core.matrix.SetTransform();
		Core.shader.getUniform(atmosphere, iShader);

		if(bHighRes) {
			glActiveTexture(GL_TEXTURE0);	gameVars->texture.terrain.Set(this->sTexture);
			if (iShader==GLS_DIRECTIONAL_WATER) {
				glActiveTexture(GL_TEXTURE1);	gameVars->texture.terrain.Set(this->sBump);
				glActiveTexture(GL_TEXTURE2);	gameVars->texture.terrain.Set(this->sSpec);
				glActiveTexture(GL_TEXTURE3);	gameVars->texture.terrain.Set(this->sWorld);
				glActiveTexture(GL_TEXTURE0);
			}

			//vao.Draw();
			vao.Draw(GLM_DRAW_ELEMENTS);
		}
		else {
			/*
			 * LOW RESOLUTION STIPPLING METHOD
			 *
			 * Method 1
			 *   Use a pixelated texture for the random stipple
			 *   noise pattern. Then randomize the texture
			 *   coordinate offset. Restrict the update speed
			 *   of the water so it doesn't go too fast and
			 *   bog down computation time.
			 *
			 * Method 2
			 *   Use the random number generator in GLSL and
			 *   try to apply it as a texture.
			 *
			 * Method 3
			 *   Use a perlin noise generator to create a nice
			 *   water effect that won't look as bad as
			 *   random noise. This is a heavy calculation
			 *   though.
			 */
		}

	Core.matrix.Pop();

	glEnable(GL_CULL_FACE);
}

#endif /* WATER_H_ */
