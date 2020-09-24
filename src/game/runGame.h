/*
 * runVoid.hpp
 *
 *  Created on: Jun 13, 2010
 *      Author: bcthund
 */

#ifndef RUNGAME_HPP_
#define RUNGAME_HPP_

#include <iostream>
//#include "../headers/core/core_functions.h"
//#include "../headers/core/matrix.h"
//#include "../headers/gamesys/animations.h"
//#include "../headers/core/types.h"

class _Game {
	private:
		static const int iPlayerLight = 0;
		Core::_Keyboard keyboard;
		//Core::GameSys::_O2D * o2d;
		//Core::GameSys::_O3D * o3d;
//		Core::GameSys::_WorldMap	* world;
//		Core::GameSys::AnimationSys * animation;
		Core::Sys::_World world;
		Core::t_AnimationInstance<Core::t_AnimationItem3D>	animation2;
		//Core::GameSys::Atmosphere atmosphere;
		//Core::OCCLUSION	occlusion;
		//Core::_Lights lights;
		bool bOneShot[64];		// TODO: Temporary one shots for debugging
		bool bHasFocus;

		float fTest_fScaleOld;

		void GetInput();
		void ProcessInput();
		void Update		();

		friend class _Admin;

	public:
		Core::Vector3f vDebugAttDelta;
		Core::Vector3f vDebugPosDelta;
		int	iDebugLight;
		int iDebugObject;
		bool bDebugDrawMouseRay;
		Core::Vector3f vDebugRotation;

		bool load();
		void Run();

		//_Game() : animation(*Core::matrix, *Core::audioSys) {
		_Game() {
			//o2d	= new Core::GameSys::_O2D(*Core::matrix, *Core::shader);
			//o3d = new Core::GameSys::_O3D(*Core::matrix, *Core::shader, *Core::collision, *Core::helper);
			// Moved to Below light initialization until lights are moved to world class
			//world	= new Core::GameSys::_WorldMap(*Core::matrix, *Core::shader, );

			world.init();

			fTest_fScaleOld = Core::gameVars->screen.fScale;

			bHasFocus = true;

			for(int n=0; n<64; n++) {
				bOneShot[n] = false;
			}

//			animation = new Core::GameSys::AnimationSys(/*Core::matrix, */*Core::audioSys);

			keyboard.calc(Core::_Keyboard::KEYTYPE_REPEAT);
			keyboard.calc(SDLK_c, Core::_Keyboard::KEYTYPE_ONESHOT);
			keyboard.calc(SDLK_DELETE, Core::_Keyboard::KEYTYPE_ONESHOT);
			keyboard.calc(SDLK_5, Core::_Keyboard::KEYTYPE_ONESHOT);
			keyboard.calc(SDLK_6, Core::_Keyboard::KEYTYPE_ONESHOT);
			keyboard.calc(SDLK_7, Core::_Keyboard::KEYTYPE_ONESHOT);
			keyboard.calc(SDLK_8, Core::_Keyboard::KEYTYPE_ONESHOT);
			keyboard.calc(SDLK_9, Core::_Keyboard::KEYTYPE_ONESHOT);
			keyboard.calc(SDLK_0, Core::_Keyboard::KEYTYPE_ONESHOT);
			keyboard.calc(SDLK_MINUS, Core::_Keyboard::KEYTYPE_ONESHOT);
			keyboard.calc(SDLK_EQUALS, Core::_Keyboard::KEYTYPE_ONESHOT);
//			keyboard.calc(SDLK_KP_2, true);
//			keyboard.calc(SDLK_KP_4, true);
//			keyboard.calc(SDLK_KP_6, true);
//			keyboard.calc(SDLK_KP_8, true);

//			keyboard.calc(SDLK_F1, Core::_Keyboard::KEYTYPE_ONESHOT);
//			keyboard.calc(SDLK_F2, Core::_Keyboard::KEYTYPE_ONESHOT);
//			keyboard.calc(SDLK_F3, Core::_Keyboard::KEYTYPE_ONESHOT);

//			keyboard.calc(SDLK_LEFTBRACKET, true);
//			keyboard.calc(SDLK_RIGHTBRACKET, true);

//			keyboard.calc(SDLK_PAGEUP, true);
//			keyboard.calc(SDLK_PAGEDOWN, true);
			keyboard.calc(SDLK_HOME, Core::_Keyboard::KEYTYPE_REPEAT);
			keyboard.calc(SDLK_END, Core::_Keyboard::KEYTYPE_REPEAT);

//			world	= new Core::GameSys::_WorldMap(/*Core::matrix, *Core::shader,*/ *Core::collision, *Core::helper);

			iDebugLight = 0;
			iDebugObject = 3;
			bDebugDrawMouseRay = true;
		}

		~_Game() {
			//delete o2d;
//			delete world;
			//delete o3d;
//			delete animation;
		}
};

//_Game * world = new(_Game);

//bool _Game::load(int mode, int iX, int iZ, bool bUpdate=false) {
bool _Game::load() {
	//o2d->load();
	//o2d->calc();
	//o3d->init();
	//o3d->load();
	//o3d->calc();
//	world->load();
//	world->calc();

	world.load();

	Core::mouse->init(0, Core::gameVars->player.active->transform.pos);
	Core::mouse->init(1, Core::gameVars->player.active->transform.pos);

	//animation(Core::audioSys);
//	animation->init();
//	animation->load();
//	animation->calc();

	//animation->startAnimation(128, 128, Core::gameVars->player.active->transform.pos, Core::Vector3f(100, 0, 100), 0, 10, 100, 0, false);
//	animation2.add("World Animation Test", "slash_00.png", 128, 128, -1, 100, -1).setCameraTarget(&Core::gameVars->player.active->transform.pos, Core::Vector3f(100, 0, 100));
	animation2.add("World Animation Test", "rotate.png", 128, 128, -1, 0, -1);
	animation2.start("World Animation Test");


	vDebugAttDelta.x = 0.0001;
	vDebugAttDelta.y = 0.000001 * (1/Core::gameVars->screen.fScale);
	vDebugAttDelta.z = 0.0000001 * (1/Core::gameVars->screen.fScale);

	vDebugPosDelta.x = 1;
	vDebugPosDelta.y = 1;
	vDebugPosDelta.z = 1;

	// Translate sphere to first light position
	// TODO: Fix light translation
	//			- Need to add access functions
//	Core::Vector3f vTemp = world->lights->GetPos(iDebugLight);
//	world->o3d->data.items[iDebugObject].posMod = vTemp;

//	{
//		// FIXME: This pointer is not deleted anywhere, does it hav eto be a pointer?
//		// FIXME: Make particle class define new pointer data like GUI does so the definition below doesn't need to be a pointer.
//		Core::_ParticleEmitterData *data = new Core::_ParticleEmitterData();
//		data->sName						= "Sparks";
//		data->sTexture					= "burst.png";
//		data->bAdditiveBlending			= true;
//		data->fEmitterLifeTime			= 10.0f;		// seconds (0=infinite)
//		data->fEmitterStartFade			= 8.0f;
//		data->fGravityEffect			= 0.0125f;	// multiplier	(object mass)
//		data->fParticleLifeTime			= 1.0f;		// seconds (0=until floor value)
//		data->fClip						= -10.0f;
//		data->fSpeed					= 10.0f;			// multiplier
//		data->fRotation					= 0.0f;
//		data->fRotationSpeed			= 0.0f;
//		data->vVelocitySpread.x			= Core::Vector2f(-0.25f, 0.25f);
//		data->vVelocitySpread.y			= Core::Vector2f(-0.0f, 0.15f);
//		data->vVelocitySpread.z			= Core::Vector2f(-0.25f, 0.25f);
//		data->fStartingSize				= 16;		// pixels
//		data->vSpawnSpread.x			= Core::Vector2f(-0.0f, 0.0f);
//		data->vSpawnSpread.y			= Core::Vector2f(-0.0f, 0.0f);
//		data->vSpawnSpread.z			= Core::Vector2f(-0.0f, 0.0f);
//		data->vLifeVariation			= Core::Vector2f(-1.0f, 1.0f);
//		data->vGravityVariation			= Core::Vector2f(-0.0f, 0.0f);
//		data->vSizeVariation			= Core::Vector2f(-1.0f, 1.0f);
//		data->fRotation					= 0.0f;
//		data->vRotationVariation		= Core::Vector2f(-0.0f, 0.0f);
//		data->fRotationSpeed			= 0.0f;
//		data->vRotationSpeedVariation	= Core::Vector2f(-2.0f, 2.0f);
//		data->iNum						= 100;				// maxmimum particles
//		data->iPPS						= 250;					// particles per second
//		data->iRate						= 10;				// update rate
//		data->vSource					= new Core::Vector3f(50.0f, 70.0f, 250.0f);
//		data->vTarget					= new Core::Vector3f(50.0f, 100.0f, 250.0f);
//		Core::particles->create(data);
//		Core::particles->calc("Sparks");
//	}

	{
		Core::_ParticleEmitterData *data = new Core::_ParticleEmitterData();
		data->sName						= "Fire";
		data->sTexture					= "fire.png";
		data->bAdditiveBlending			= true;
		data->fEmitterLifeTime			= 0;		// seconds (0=infinite)
		data->fEmitterStartFade			= 0.0f;
		data->fGravityEffect			= -0.000125f;	// multiplier	(object mass)
		data->fParticleLifeTime			= 1.5;		// seconds (0=until floor value)
		data->fClip						= 500.0f;
		data->fSpeed					= 1.0f;				// multiplier
		data->vVelocitySpread.x			= Core::Vector2f(-0.25f, 0.25f);
		data->vVelocitySpread.y			= Core::Vector2f(-0.0f, 0.0f);
		data->vVelocitySpread.z			= Core::Vector2f(-0.25f, 0.25f);
		data->fStartingSize				= 128;		// pixels
		data->vSpawnSpread.x			= Core::Vector2f(-25.0f, 25.0f);
		data->vSpawnSpread.y			= Core::Vector2f(-0.0f, 0.0f);
		data->vSpawnSpread.z			= Core::Vector2f(-25.0f, 25.0f);
		data->vLifeVariation			= Core::Vector2f(-0.0f, 0.0f);
		data->vGravityVariation			= Core::Vector2f(-10.25f, 10.25f);
		data->vSizeVariation			= Core::Vector2f(-0.5f, 1.0f);
		data->fRotation					= 0.0f;
		data->vRotationVariation		= Core::Vector2f(-0.0f, 0.0f);
		data->fRotationSpeed			= 0.01f;
		data->vRotationSpeedVariation	= Core::Vector2f(-2.0f, 2.0f);
		data->iNum						= 250;				// maxmimum particles
		data->iPPS						= 150;					// particles per second
		data->iRate						= 10;				// update rate
		data->vSource					= new Core::Vector3f(500.0f, 150.0f, -75.0f);
		data->vTarget					= new Core::Vector3f(500.0f, 200.0f, -75.0f);
		data->atlas.SetSize(4);		// Create a texture atlas for this particle emitter (texture grid/fading)
		Core::particles->create(data);
		Core::particles->calc("Fire");
	}

	{
		Core::_ParticleEmitterData *data = new Core::_ParticleEmitterData();
		data->sName						= "Smoke";
		data->sTexture					= "smoke.png";
		data->bAdditiveBlending			= false;
		data->fEmitterLifeTime			= 0;		// seconds (0=infinite)
		data->fEmitterStartFade			= 0.0f;
		data->fGravityEffect			= -0.0000125f;	// multiplier	(object mass)
		data->fParticleLifeTime			= 0;		// seconds (0=until floor value)
		data->fClip						= 700.0f;
		data->fSpeed					= 1.0f;				// multiplier
		data->vVelocitySpread.x			= Core::Vector2f(-0.25f, 0.25f);
		data->vVelocitySpread.y			= Core::Vector2f(-0.0f, 0.0f);
		data->vVelocitySpread.z			= Core::Vector2f(-0.25f, 0.25f);
		data->fStartingSize				= 128;		// pixels
		data->vSpawnSpread.x			= Core::Vector2f(-25.0f, 25.0f);
		data->vSpawnSpread.y			= Core::Vector2f(-0.0f, 0.0f);
		data->vSpawnSpread.z			= Core::Vector2f(-25.0f, 25.0f);
		data->vLifeVariation			= Core::Vector2f(-0.0f, 0.0f);
		data->vGravityVariation			= Core::Vector2f(-10.25f, 10.25f);
		data->vSizeVariation			= Core::Vector2f(-0.5f, 1.0f);
		data->fRotation					= 0.0f;
		data->vRotationVariation		= Core::Vector2f(-0.0f, 0.0f);
		data->fRotationSpeed			= 0.01f;
		data->vRotationSpeedVariation	= Core::Vector2f(-2.0f, 2.0f);
		data->iNum						= 1000;				// maxmimum particles
		data->iPPS						= 150;					// particles per second
		data->iRate						= 10;				// update rate
		data->vSource					= new Core::Vector3f(500.0f, 250.0f, -75.0f);
		data->vTarget					= new Core::Vector3f(500.0f, 300.0f, -75.0f);
		Core::particles->create(data);
		Core::particles->calc("Smoke");
	}

//	{
//		Core::_ParticleEmitterData *data = new Core::_ParticleEmitterData();
//		data->sName						= "Water";
//		data->sTexture					= "water3.png";
//		data->bAdditiveBlending			= false;
//		data->fEmitterLifeTime			= 20.0f;		// seconds (0=infinite)
//		data->fEmitterStartFade			= 15.0f;
//		data->fGravityEffect			= 0.00125f;	// multiplier	(object mass)
//		data->fClip						= -10.0f;
//		data->fParticleLifeTime			= 0.0f;		// seconds (0=until floor value)
//		data->vLifeVariation			= Core::Vector2f(-0.0f, 0.0f);
//		data->fSpeed					= 1.0f;			// multiplier
//		data->vVelocitySpread.x 		= Core::Vector2f(-0.25f, 0.25f);
//		data->vVelocitySpread.y	 		= Core::Vector2f(-0.25f, 0.25f);
//		data->vVelocitySpread.z 		= Core::Vector2f(-0.25f, 0.25f);
//		data->fStartingSize				= 128;		// pixels
//		data->vSizeVariation			= Core::Vector2f(-0.0f, 0.0f);
//		data->vGravityVariation			= Core::Vector2f(-0.0f, 0.0f);
//		data->fRotation					= 0.0f;
//		data->vRotationVariation		= Core::Vector2f(-0.0f, 0.0f);
//		data->fRotationSpeed			= 0.01f;
//		data->vRotationSpeedVariation	= Core::Vector2f(-2.0f, 2.0f);
//		data->vSource					= new Core::Vector3f(500.0f, 100.0f, 500.0f);
//		data->vSpawnSpread.x			= Core::Vector2f(-10.0f, 10.0f);
//		data->vSpawnSpread.y			= Core::Vector2f(-5.0f, 5.0f);
//		data->vSpawnSpread.z			= Core::Vector2f(-25.0f, 25.0f);
//		data->vTarget					= new Core::Vector3f(400.0f, 100.0f, 500.0f);
//		data->iNum						= 1000;				// maxmimum particles
//		data->iPPS						= 500;				// particles per second
//		data->iRate						= 10;				// update rate
//		Core::particles->create(data);
//		Core::particles->calc("Water");
//	}

	return 1;
}

//This is the primary function of this class
//This function calls all other functions in the class in the proper order
// TODO: Add games states (main menu, admin, console, world, dungeon, etc)
void _Game::Run() {

//	if(!Mix_PlayingMusic()) Core::audioSys.playMusic(0);

	//glClearColor(	Core::gameVars->screen.vClearColorCurrent[0],
	//				Core::gameVars->screen.vClearColorCurrent[1],
	//				Core::gameVars->screen.vClearColorCurrent[2],
	//				Core::gameVars->screen.vClearColorCurrent[3]	);

	//glClear( Core::gameVars->screen.clear );
	Core::profiles->runProfile(Core::profiles->builtIn.RunGame_GetInput, true);
	if (!Core::gameVars->runState.admin) GetInput();
	Core::profiles->runProfile(Core::profiles->builtIn.RunGame_GetInput, false);

	//Core::profile->timer.a

	//Core::Vector3f mRay = Core::mouse->GetMouseRay();
	//Core::mouse->mouseRay = Core::mouse->GetMouseRay();	// Update mouseRay, return not needed;
	Core::profiles->runProfile(Core::profiles->builtIn.RunGame_GetMouseRay, true);
	Core::mouse->GetMouseRay(Core::gameVars->screen.res.x, Core::gameVars->screen.res.y, Core::gameVars->player.active->transform.rot);	// Update mouseRay, return not needed;
	Core::profiles->runProfile(Core::profiles->builtIn.RunGame_GetMouseRay, false);
	/*
	 * TODO: If a movement was made, do a collision test on O3D's and if
	 * 			a collision is detected, currently just print a message
	 * 			to the screen. To do this we will probably need to set a
	 * 			flag in the bounding volume class that can be used in
	 * 			the debug routine to print a message to the screen. This
	 * 			will be a simple true/false indication for a collision.
	 *
	 * TODO: When a collision is detected we can then proceed to full
	 * 			model collision detection for that O3D. Since the code
	 * 			for collision detection on an entire model might be
	 * 			expensive we want to limit this.
	 *
	 * TODO: Movement creates a movement ray, use that ray for a Ray
	 * 			collision test against bounding volumes. If the test
	 * 			results in a collision, then stop player movement.
	 *
	 * TODO: Instead of stopping player, allow player to slide along
	 * 			the bounding volume. This will be a precurser to
	 * 			possibly the same thing against the object which the
	 * 			bounding volume is tied to.
	 */

	// Update lighting
//	Core::Vector3f vTemp = world->lights->GetPos(iPlayerLight);
//	world->lights->SetPos(iPlayerLight, Core::gameVars->player.active->transform.pos.invert());
//	world->lights->SetPos(iPlayerLight+1, Core::gameVars->player.active->transform.pos.invert());
//	Core::Matrix44f mMatrix;
//	Core::Vector4f vForward = Core::Vector4f(0.0f, 0.0f, -1.0f, 0.0f);
//	Core::matrix->Rotate(mMatrix, Core::gameVars->player.active->transform.rot.x, 1, 0, 0);
//	Core::matrix->Rotate(mMatrix, Core::gameVars->player.active->transform.rot.y, 0, 1, 0);
//	Core::matrix->Rotate(mMatrix, Core::gameVars->player.active->transform.rot.z, 0, 0, 1);
//	Core::Vector4f vLightDir = mMatrix * vForward;
//	world->lights->SetDir(iPlayerLight, Core::Vector3f(vLightDir.x, vLightDir.y, vLightDir.z));

	// Debug draw light on player (ensures correct location)
//	if (iDebugLight == iPlayerLight) {
//		Core::Vector3f vNew = world->lights->GetPos(iPlayerLight);
//		world->o3d->data.items[iDebugObject].translate = vNew;
//	}

	// Update Particles
//	Core::particles->update("Sparks");
//	Core::particles->update("Smoke");
//	Core::particles->update("Water");
	Core::particles->update();		// Update all with emitter sorting

	// TODO: update timer
	// FIXME: SEG FAULT
//	world.update();

	Update();
}

//This function updates the opengl pipeline with our current geometry
void _Game::Update() {

	// Start Post Processing
	if(Core::gameVars->screen.MultiSample) Core::postProcess->RenderLayer("Multisample");
	else Core::postProcess->RenderLayer("Layer0");

	glClear( Core::gameVars->screen.clear );
//	glPolygonMode(GL_FRONT_AND_BACK, Core::gameVars->screen.iPolygonMode);

	// FIXME: [Color] Add PushFront() and SetActive() to all drawing routines (O2D, O3D, World, Atmosphere, etc)

	// Make sure no lingering transforms
	Core::matrix->SetIdentity();

	// Draw world first so other things can be overlayed
	//if(bThirdPerson) Core::matrix->Translate(0, -10, -DEBUG_3PDISTANCE);		//3rd person view

	// KEEP THIS FOR REFERENCE (Used in drawing commands directly)
//	Core::profiles->runProfile(Core::profiles->builtIn.RunGame_Transform);
//	matrix->Rotate(Core::gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
//	matrix->Rotate(Core::gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
//	matrix->Translate(Core::gameVars->player.active->transform.pos[0], Core::gameVars->player.active->transform.pos[1], Core::gameVars->player.active->transform.pos[2]);
//	matrix->SetTransform();
//	Core::profiles->runProfile(Core::profiles->builtIn.RunGame_Transform);

	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// 			World (Map, atmosphere, flora, O2D, O3D, etc)
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	glEnable(GL_DEPTH_TEST);
	Core::profiles->runProfile(Core::profiles->builtIn.RunGame_DrawWorld, true);
	world.draw();
	Core::profiles->runProfile(Core::profiles->builtIn.RunGame_DrawWorld, false);

	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// 			Helpers
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	if(bDebugDrawMouseRay) {
		Core::profiles->runProfile(Core::profiles->builtIn.RunGame_Mouseray, true);
		Core::mouse->draw(0, Core::gameVars->player.active->transform.rot, Core::gameVars->player.active->transform.pos);
		Core::mouse->draw(1, Core::gameVars->player.active->transform.rot, Core::gameVars->player.active->transform.pos, 5.0f, Core::colors[Core::colors().Green], Core::colors[Core::colors().Red]);
		Core::profiles->runProfile(Core::profiles->builtIn.RunGame_Mouseray, false);
	}

	//World origin
	Core::matrix->Push();
		Core::helper->drawPosition(1.0f, 100.0f, Core::gameVars->player.active->transform.pos, Core::gameVars->player.active->transform.rot);
	Core::matrix->Pop();



		// Draw test Skeleton - This will draw the joint and all of its children
//		Core::profiles->runProfile(Core::profiles->builtIn.RunGame_Skeleton);
//		Core::skeleton->children[0]->SetRotation(vDebugRotation);
//		Core::skeleton->DrawJoint();
//		Core::profiles->runProfile(Core::profiles->builtIn.RunGame_Skeleton);
//	Core::matrix->Pop();

	// Flares After Scenery, before PP and GUI
	// Can draw here if bold flares wanted
	//	world->atmosphere->draw(world->atmosphere->MODE_FLARES, "Sun");

	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// 			Particles
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	Core::profiles->runProfile(Core::profiles->builtIn.RunGame_Particles, true);
	Core::matrix->Push();
		Core::matrix->Rotate(Core::gameVars->player.active->transform.rot[0], 1.0, 0.0, 0.0);
		Core::matrix->Rotate(Core::gameVars->player.active->transform.rot[1], 0.0, 1.0, 0.0);
		Core::matrix->Translate(Core::gameVars->player.active->transform.pos[0], Core::gameVars->player.active->transform.pos[1], Core::gameVars->player.active->transform.pos[2]);
		Core::matrix->SetTransform();
//		Core::particles->draw("Sparks");
//		Core::particles->draw("Smoke");
//		Core::particles->draw("Water");
		Core::particles->draw();	// Draw with distance sorting
	Core::matrix->Pop();
	Core::profiles->runProfile(Core::profiles->builtIn.RunGame_Particles, false);

	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// 			Animations
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	/*
	 * Only draws after o3d draws bounding boxes?
	 * Only draws in color of last bounding box drawn?
	 * Possibly not using correct shader? Using last used shader?
	 */
//	Core::mouse->draw();
	Core::profiles->runProfile(Core::profiles->builtIn.RunGame_Animation, true);
//	animation->drawWorld(Core::gameVars->screen.fScale);		// Draw all animations to WORLD
//	animation2["World Animation Test"].setCameraTarget(&Core::gameVars->player.active->transform.pos, Core::Vector3f(100, 0, 100));
//	animation2["World Animation Test"].setCameraTarget(&Core::gameVars->player.active->transform.pos, Core::Vector3f(350, 50, -100));

	//Core::Vector3f vTemp = world->lights->GetPos(iDebugLight);

//	animation2["World Animation Test"].setCameraTarget(&Core::gameVars->player.active->transform.pos, world->lights->GetPosPtr(iDebugLight));
//	animation2.update("World Animation Test");
//	animation2.draw("World Animation Test");
	Core::profiles->runProfile(Core::profiles->builtIn.RunGame_Animation, false);


	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// 			Post Processing
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	Core::profiles->runProfile(Core::profiles->builtIn.RunGame_PostProcess, true);
	GLuint ppWorld = Core::postProcess->EndRenderLayer();
//	Core::postProcess->RenderToScreen();
//	GLuint ppWorld = Core::postProcess->ApplyBrightness(Core::Vector3f(2.0, 2.0, 2.0));
//	GLuint ppWashout = Core::postProcess->ApplyBrightness(world->atmosphere->satellite->getAlpha("Sun")/2.0f);		// TODO: [PP] Add a Screen Post Processing Effect
	GLuint ppWashout = Core::postProcess->ApplyBrightness(0.0f);

	GLuint ppContrast = Core::postProcess->ApplyContrast(2.0f);
	//GLuint ppBrightness = Core::postProcess->ApplyBrightness(Core::Vector3f(2.0, 2.0, 2.0));
	GLuint ppBrightnessFilter = Core::postProcess->ApplyBrightnessFilter(Core::Vector3f(0.75, 0.75, 0.75), 0.125);
	Core::postProcess->ApplyHBlur();
	GLuint ppBlur = Core::postProcess->ApplyVBlur();
	GLuint ppBloom = Core::postProcess->ApplyCombine(ppWashout, 0.5f);

	/*
	 * Clear screen and draw objects for radial blur (scattering) effect
	 *
	 * NOTE: Atmosphere is drawn here for Lens effect ONLY, actual drawing occurs in world->draw() above
	 */
	Core::postProcess->RenderLayer("Multisample");
	Core::postProcess->RenderLayer("Layer1");
	glClearColor(0,0,0,1);
	glClear( Core::gameVars->screen.clear );
//	Core::colors.PushFront(Core::Color(1.0f, 1.0f, 1.0f, world->atmosphere->satellite->getAlpha("Sun")*1.5 ));
	Core::colors.SetActive(Core::colors.COLOR_FRONT);
//	world->atmosphere->draw(world->atmosphere->MODE_SATELLITE, "Moon");
//	world->atmosphere->draw(world->atmosphere->MODE_SATELLITE, "Sun");
	Core::colors.PopFront();
//	world->atmosphere->draw(world->atmosphere->MODE_FLARES, "Sun");

	GLuint ppRadialPrep = Core::postProcess->EndRenderLayer();
	GLuint ppRadial = Core::postProcess->ApplyRadialBlur(ppRadialPrep);
	GLuint ppScatter = Core::postProcess->ApplyCombine(ppBloom, 1.5f);
	Core::glinit->RestoreClearColor();

	Core::postProcess->RenderToScreen(ppScatter);
//	Core::postProcess->RenderToScreen(ppWorld);
//	Core::postProcess->RenderToWindow(ppWorld, Core::Vector3f(-360, -200, 0), 0.25f);
//	Core::postProcess->RenderToWindow(ppRadial, Core::Vector3f( 360, -200, 0), 0.25f);

//	Core::postProcess->RenderToScreen(ppWorld);
//	Core::postProcess->RenderToWindow(ppRadialPrep, Core::Vector3f(-360, -200, 0), 0.25f);
//	Core::postProcess->RenderToWindow(ppRadial, Core::Vector3f( 360, -200, 0), 0.25f);
	Core::profiles->runProfile(Core::profiles->builtIn.RunGame_PostProcess, false);

	// FIXME: Crosshair
//	Core::GameSys::drawSprite(Core::gameVars->screen.half.x-16, Core::gameVars->screen.half.y-16, 32, 32, "crosshair.png", false, false, Core::colors[Core::colors().Green]);
	Core::GameSys::drawSprite(0, 0, 32, 32, "crosshair.png", false, false, Core::colors[Core::colors().Green]);

	// Start orthographic routines (Overlays)
//	uint iX = 0,
//		 iY = 0;
	float iX = 0.0f,
		  iY = 0.0f;

	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// 			2D Orthographic Icons (64x64 Texture Atlas)
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	Core::profiles->runProfile(Core::profiles->builtIn.RunGame_DrawIcon, true);
	//Core::iconSys->draw(iX, iY, 64, 64, 0, "TestPattern.png", true);
//	Core::GameSys::checkIcon(iX,     iY, 64, 64, 0, "TestPattern.png", true, false);
	Core::GameSys::drawIcon(iX,     iY, 64, 64, 0, "TestPattern.png", true, false);
	Core::GameSys::checkIcon(iX+=74, iY, 64, 64, 1, "TestPattern.png", true, false);
	Core::GameSys::checkIcon(iX+=74, iY, 64, 64, 2, "TestPattern.png", true, false);
	Core::GameSys::checkIcon(iX+=74, iY, 64, 64, 3, "TestPattern.png", true, false);
	Core::GameSys::checkIcon(iX+=74, iY, 64, 64, 4, "TestPattern.png", true, false);
	Core::GameSys::checkIcon(iX+=74, iY, 64, 64, 5, "TestPattern.png", true, false);
	Core::profiles->runProfile(Core::profiles->builtIn.RunGame_DrawIcon, false);

	iX = 450;
	iY = 80;
	Core::GameSys::checkIcon(iX,     iY, 20, 20, 0, "1800_icons_2.svg", true, false);
	Core::GameSys::checkIcon(iX+=20, iY, 20, 20, 1, "1800_icons_2.svg", true, false);
	Core::GameSys::checkIcon(iX+=20, iY, 20, 20, 2, "1800_icons_2.svg", true, false);
	Core::GameSys::checkIcon(iX+=20, iY, 20, 20, 3, "1800_icons_2.svg", true, false);
	Core::GameSys::checkIcon(iX+=20, iY, 20, 20, 4, "1800_icons_2.svg", true, false);
	Core::GameSys::checkIcon(iX+=20, iY, 20, 20, 5, "1800_icons_2.svg", true, false);
	Core::GameSys::checkIcon(iX+=20, iY, 20, 20, 6, "1800_icons_2.svg", true, false);
	Core::GameSys::checkIcon(iX+=20, iY, 20, 20, 7, "1800_icons_2.svg", true, false);

	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// 			2D Orthographic Sprites
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	Core::profiles->runProfile(Core::profiles->builtIn.RunGame_DrawSprite, true);

	Core::GUI::Props prop;
	prop.setPos(-Core::gameVars->screen.half.x-115+iX, Core::gameVars->screen.half.y-32);
	prop.setWidth(64);
	prop.setHeight(64);
	prop.exec();
//	Core::spriteSys->draw(iX+=74, iY, 1, 1, "TestPattern.png", false, Core::colors[Core::colors().White]);
	Core::spriteSys->draw(&prop, "TestPattern.png", Core::colors[Core::colors().White]);

	prop.modPos(74, 0);
	prop.setWidth(64);
	prop.setHeight(64);
	prop.exec();
//	Core::spriteSys->draw(iX+=74, iY, 1, 1, "TestPattern.png", true, Core::colors[Core::colors().White]);
	Core::spriteSys->draw(&prop, "TestPattern.png", Core::colors[Core::colors().White]);

	Core::profiles->runProfile(Core::profiles->builtIn.RunGame_DrawSprite, false);

	iX=0;
	iY=74;
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// 			Text Rendering
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	/*
	 * TODO: Being updated
	 * Draw simple text to the screen
	 * Multiple draw routines allow drawing of:
	 * 		- Strings
	 * 		- Floats
	 * 		- Integers
	 * 		- Booleans
	 * 		- String + Float
	 * 		- String + Integer
	 * 		- String + Boolean
	 * 		- pTimer
	 */
	Core::profiles->runProfile(Core::profiles->builtIn.RunGame_TextSys, true);
//	int iResult = (int)Core::occlusion->ReadResultui("Sun");


	/*
	 * Drawing text tied to a constraint
	 *
	 * This should be the correct way to draw text (with constraints)
	 * Even better is to use the GUI system
	 */
//	{
//		Core::GUI::Constraints c;
//		c.setOrigin(Core::GUI::ORIGIN_CENTER);
//		c.setPos(0, 0);
//		c.setWidth(100, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
//		c.setHeight(100, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
//		c.exec();
//
//		c.setAnchor(Core::GUI::ANCHOR_LEFT);
//		Core::textSys->draw(c, "Testing");
//
//		c.setAnchor(Core::GUI::CONSTRAIN_RIGHT);
//		Core::textSys->draw(c, "Testing");
//
//		c.setAnchor(Core::GUI::CONSTRAIN_TOP);
//		Core::textSys->draw(c, "Testing");
//
//		c.setAnchor(Core::GUI::CONSTRAIN_BOTTOM);
//		Core::textSys->draw(c, "Testing");
//	}


	Core::textSys->draw(1*Core::gameVars->font.vSize.x, -8*Core::gameVars->font.vSize.y, "This is a Test 0123456789", Core::GUI::CONSTRAIN_LEFT);
//	Core::textSys->draw(100, -150, "CENTER", Core::GUI::CONSTRAIN_CENTER, Core::GUI::ORIGIN_TOP|Core::GUI::ORIGIN_LEFT);
//	Core::textSys->draw(100, -150, "|--LEFT", Core::GUI::CONSTRAIN_LEFT, Core::GUI::ORIGIN_TOP|Core::GUI::ORIGIN_LEFT);
//	Core::textSys->draw(100, -150, "RIGHT--|", Core::GUI::CONSTRAIN_RIGHT, Core::GUI::ORIGIN_TOP|Core::GUI::ORIGIN_LEFT);
//	Core::textSys->draw(100, -150, "TOP", Core::GUI::CONSTRAIN_TOP, Core::GUI::ORIGIN_TOP|Core::GUI::ORIGIN_LEFT);
//	Core::textSys->draw(100, -150, "BOTTOM", Core::GUI::CONSTRAIN_BOTTOM, Core::GUI::ORIGIN_TOP|Core::GUI::ORIGIN_LEFT);

	Core::textSys->drawVar<float>(500,  -500, "X: ", Core::gameVars->player.active->transform.pos.x, 3, Core::GUI::CONSTRAIN_LEFT);

	Core::textSys->drawVar2<float>(1,  -9, "X: ", Core::gameVars->player.active->transform.pos.x, 3, Core::GUI::CONSTRAIN_LEFT);
	Core::textSys->drawVar2<float>(1,  -10, "Y: ", Core::gameVars->player.active->transform.pos.y, 3, Core::GUI::CONSTRAIN_LEFT);
	Core::textSys->drawVar2<float>(1,  -11, "Z: ", Core::gameVars->player.active->transform.pos.z, 3, Core::GUI::CONSTRAIN_LEFT);
//	Core::textSys->drawVar2<int>(1,    -12, "iResult: ", iResult, 3, Core::GUI::CONSTRAIN_LEFT);
//	float fResult = Core::occlusion->GetRatio("Sun");

//	Core::textSys->drawVar2<float>(1,  -13, "fResult: ", fResult, 3, Core::GUI::CONSTRAIN_LEFT);
	Core::textSys->drawVar2<float>(1,  -14, "Light: ", iDebugLight, 3, Core::GUI::CONSTRAIN_LEFT);

	Core::textSys->drawVar2<float>(1,  -16, "mouseRay: ", Core::mouse->rays[0].dir.x, 3, Core::GUI::CONSTRAIN_LEFT);
	Core::textSys->drawVar2<float>(21, -16, "", Core::mouse->rays[0].dir.y, 3, Core::GUI::CONSTRAIN_LEFT);
	Core::textSys->drawVar2<float>(32, -16, "", Core::mouse->rays[0].dir.z, 3, Core::GUI::CONSTRAIN_LEFT);

	Core::textSys->drawVar2<float>(1,  -17, "mouseRay: ", Core::mouse->rays[1].dir.x, 3, Core::GUI::CONSTRAIN_LEFT);
	Core::textSys->drawVar2<float>(21, -17, "", Core::mouse->rays[1].dir.y, 3, Core::GUI::CONSTRAIN_LEFT);
	Core::textSys->drawVar2<float>(32, -17, "", Core::mouse->rays[1].dir.z, 3, Core::GUI::CONSTRAIN_LEFT);

	//Core::textSys->drawVar2<float>(1,  -18, "mousePos: ", Core::mouse->x, 3, Core::GUI::CONSTRAIN_LEFT);
	//Core::textSys->drawVar2<float>(21, -18, "", Core::gameVars->screen.res.y-Core::mouse->y, 3, Core::GUI::CONSTRAIN_LEFT);

	Core::textSys->drawVar2<float>(1,  -19, "mousePos: ", Core::mouse->x, 3, Core::GUI::CONSTRAIN_LEFT);
	Core::textSys->drawVar2<float>(21, -19, "", Core::mouse->y, 3, Core::GUI::CONSTRAIN_LEFT);

	Core::textSys->drawVar2<float>(1,  -20, "mousePos: ", Core::mouse->x-Core::gameVars->screen.half.x, 3, Core::GUI::CONSTRAIN_LEFT);
	Core::textSys->drawVar2<float>(21, -20, "", -Core::mouse->y+Core::gameVars->screen.half.y, 3, Core::GUI::CONSTRAIN_LEFT);


	Core::textSys->drawVar2<int>(1,  -21,   "Terrain Quads: ", std::pow(world.simplex.res, 2), 3, Core::GUI::CONSTRAIN_LEFT);
	Core::textSys->drawVar2<int>(1,  -22,   " Terrain Tris: ", std::pow(world.simplex.res, 2) * 2, 3, Core::GUI::CONSTRAIN_LEFT);
	Core::textSys->drawVar2<int>(1,  -23,   "Terrain Verts: ", std::pow(world.simplex.res, 2) * 6, 3, Core::GUI::CONSTRAIN_LEFT);

//	Core::textSys->drawVar2<int>(1,  -21,   "Terrain Quads: ", Core::gameVars->debug.noise.simplex[0].res*2, 3, Core::GUI::CONSTRAIN_LEFT);
//	Core::textSys->drawVar2<int>(1,  -22,   " Terrain Tris: ", Core::gameVars->debug.noise.simplex[0].res*2*2, 3, Core::GUI::CONSTRAIN_LEFT);
//	Core::textSys->drawVar2<int>(1,  -23,   "Terrain Verts: ", Core::gameVars->debug.noise.simplex[0].res*2*2*3, 3, Core::GUI::CONSTRAIN_LEFT);

	/*
	 * Draw FPS and Standard Deviation
	 * using special plus-minus character
	 */
	//Core::winSys->draw(95, 0, 30, 3, true, Core::colors[Core::colors().Blue], Core::winSys->DRAWMODE.NORMAL);
	float fFPS = Core::framerate->getFPS<float>();
	int ticks = Core::framerate->getSplitTicks();
	float fStdDev = Core::framerate->getStdDev();

	Core::textSys->drawVar2<float>(96, -1, "   fps: ", fFPS, 3, Core::GUI::CONSTRAIN_LEFT);
	Core::textSys->drawVar2<float>(96, -2, " ticks: ", ticks, 3, Core::GUI::CONSTRAIN_LEFT);
	Core::textSys->drawVar2<float>(96, -3, "stdDev: ", fStdDev, 3, Core::GUI::CONSTRAIN_LEFT);
//	Core::textSys->drawSpecial(111, 1, "±");			// TODO: Fix

	Core::profiles->runProfile(Core::profiles->builtIn.RunGame_TextSys, false);

	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// 			Interactive Text
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	//if (Core::GameSys::menuSys.draw(11, 14, "Options") == Core::mouse->STATE.MOUSE_LEFT) cout << "Click!" << endl;

	// FIXME: Not drawing to screen, Move to GUI system?
//	if (Core::menuSys->draw(96, 45, "Play Sound Effect") == Core::mouse->MOUSE_LEFT) {
//		Core::profiles->runProfile(Core::profiles->builtIn.RunGame_AudioSys, true);
//		Core::audioSys->playSound(0);
//		Core::profiles->runProfile(Core::profiles->builtIn.RunGame_AudioSys, false);
//	}
//	if (Core::menuSys->draw(96, 46, "Play Animation") == Core::mouse->MOUSE_LEFT) {
//		// Add an animation to the queue and play sound effect
//		animation->startAnimation(128, 128, Core::gameVars->player.active->transform.pos, Core::Vector3f(100, 0, 100), 0, 10, 100, 0, false);
//	}

	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// 			Profile Timers for Debugging
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//	float time;
//	int sProfile;
//	int iO = 15;
//	int i1 = 16,
//		i2 = 32,
//		i3 = 48,
//		i4 = 64;
//	iX = 30;
//	iY = -20;
//	int iSamples = 500;
//
//	for (int n=0; n<Core::profiles->builtIn.Last; n++) {
//		Core::textSys->draw2(iX-2, iY, Core::profiles->builtIn.sNames[n], Core::GUI::CONSTRAIN_RIGHT);
//		time = Core::profiles->getSamples(n);			Core::textSys->drawVar2<float>(iX,    iY, "Samples: ", time, 3, Core::GUI::CONSTRAIN_LEFT);
//		time = Core::profiles->getAverage(n, iSamples);	Core::textSys->drawVar2<float>(iX+i1, iY, "    Avg: ", time, 3, Core::GUI::CONSTRAIN_LEFT);
//		time = Core::profiles->getStdDev(n);			Core::textSys->drawVar2<float>(iX+i2, iY, " StdDev: ", time, 3, Core::GUI::CONSTRAIN_LEFT);
//		time = Core::profiles->getMax(n);				Core::textSys->drawVar2<float>(iX+i3, iY, "    Max: ", time, 3, Core::GUI::CONSTRAIN_LEFT);
//		time = Core::profiles->getMin(n);				Core::textSys->drawVar2<float>(iX+i4, iY, "    Min: ", time, 3, Core::GUI::CONSTRAIN_LEFT);
//		iY--;
//	}

	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// 			Time of Day
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	{
		iX = 76;
		Core::textSys->drawVar2<float>(iX, -1, " day: ", Core::timeSys->iDay, 3, Core::GUI::CONSTRAIN_LEFT);
		Core::textSys->drawVar2<float>(iX, -2, "year: ", Core::timeSys->iYear, 3, Core::GUI::CONSTRAIN_LEFT);

		int iHour	= Core::timeSys->GetHour(),
			iMinute	= Core::timeSys->GetMinute(),
			iSecond	= Core::timeSys->GetSecond();

		std::string sTime = std::to_string(iHour) + ":" + std::to_string(iMinute) + ":" + std::to_string(iSecond);
		Core::textSys->draw2(iX,	-3, sTime, Core::GUI::CONSTRAIN_LEFT);
		Core::textSys->draw2(iX,	-4, Core::timeSys->GetSeasonStr(), Core::GUI::CONSTRAIN_LEFT);
	}

	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// 			2D Orthographic lines and points
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	{
		Core::matrix->SetProjection(Core::matrix->MM_ORTHO);
		Core::Vector3f a = { 0, 0, 0 };
		Core::Vector3f b = { -Core::gameVars->screen.half.x, -Core::gameVars->screen.half.y, 0 };
		Core::Color colorA = { 1, 0, 0, 1};
		Core::Color colorB = { 0, 1, 0, 1};
		Core::helper->drawLine(a, b, 1, 1, colorA, colorB);
		//Core::helper->drawPoint(b, 5);	// Not implemented
	}

//	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//	// 			GUI Rendering
//	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
//	// GUI - Master container
//	if (!bOneShot[0]) {
//		Core::gui->addGUI("GameMenu");
//		bOneShot[0] = true;
//	}
//
//	// Blank Window, parameter testing
//	if (!bOneShot[1]) {
//		Core::GUI::Constraints_Window con;
//		con.setOrigin(Core::GUI::ORIGIN_CENTER|Core::GUI::ORIGIN_RIGHT);
//		con.setAnchor(Core::GUI::ANCHOR_RIGHT);
////		con.setX(Core::GUI::ORIGIN_X_RIGHT, -100);
////		con.setY(Core::GUI::ORIGIN_CENTER, 150);
////		con.setX(Core::GUI::ORIGIN_RELATIVE, 25);
//		con.setPos(-100, 150);
//		con.setWidth(250, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
//		con.setHeight(350, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
//		con.setBorder(1, true);
//		con.setRadius(5);
//		con.setColorWindow(Core::colors->grey);
//		Core::gui->addWindow("GameMenu", "Window 1", con);		// MapSys Window
//		con.setVisibility(false);
//		Core::gui->addWindow("GameMenu", "Window 3", con);		// Lighting Window
////		Core::gui->hideWindow("GameMenu", "Window 3");			// Hidden by default
//		bOneShot[1] = true;
//	}
//
//	if (!bOneShot[2]) {
//		Core::GUI::Constraints_Window con;
//		con.setOrigin(Core::GUI::ORIGIN_CENTER|Core::GUI::ORIGIN_RIGHT);
//		con.setAnchor(Core::GUI::ANCHOR_RIGHT);
//		con.setPos(-100, -50);
//		con.setWidth(250, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
//		con.setHeight(50, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
//		con.setBorder(1, true);
//		con.setRadius(5);
//		con.setColorWindow(Core::colors->tan);
//		Core::gui->addWindow("GameMenu", "Window 2", con);		// General Buttons Menu
//		bOneShot[2] = true;
//	}
//
//	// Label Testing
//	if (!bOneShot[3]) {
//		Core::GUI::Constraints_Label con;
//		con.setOrigin(Core::GUI::ORIGIN_TOP|Core::GUI::ORIGIN_CENTER);
//		con.setAnchor(Core::GUI::ANCHOR_TOP);
//		con.setPos(0, -5);
//		con.setWidth(74, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
//		con.setHeight(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
//		con.setBorder(0, false);
//		con.setRadius(0);
//		con.setColorWindow(Core::colors->transparent);
//		con.setColorBorder(Core::colors->black);
//		Core::gui->addLabel("GameMenu", "Window 1", "My Label", con);
//		bOneShot[3] = true;
//	}
//
//	// Field Testing
//	if (!bOneShot[4]) {
//		Core::GUI::Constraints_Field con;
//		con.setOrigin(Core::GUI::ORIGIN_TOP|Core::GUI::ORIGIN_CENTER);
//		con.setAnchor(Core::GUI::ANCHOR_TOP);
//		con.setPos(50, -65);
//		con.setWidth(74, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
//		con.setHeight(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
//		con.setBorder(1, false);
//		con.setRadius(0);
//		con.setColorWindow(Core::colors->white);
//		con.setColorBorder(Core::colors->black);
//		Core::gui->addField("GameMenu", "Window 1", "FloatVal", &Core::gameVars->debug.gui.f, con);
//		bOneShot[4] = true;
//	}
//
//	// Button Testing
//	if (!bOneShot[20]) {
//		// Accept Button
//		Core::GUI::Constraints_Button con_button;
//		con_button.setOrigin(Core::GUI::ORIGIN_CENTER|Core::GUI::ORIGIN_BOTTOM);
//		con_button.setAnchor(Core::GUI::ANCHOR_BOTTOM|Core::GUI::ANCHOR_RIGHT);		// Center of button
//		con_button.setPos(-5, 5);
//		con_button.setWidth(100, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);				// Exact button width
//		con_button.setHeight(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);				// Exact button height
//		con_button.setBorder(1, true);
//		con_button.setRadius(10);
//		con_button.setColorWindow(Core::colors->brown, Core::colors->orange);
//		con_button.setColorText(Core::colors->white, Core::colors->green);
//		Core::gui->addButton("GameMenu", "Window 2", "Hide", con_button);
//
//		// Test component for hideable window
//		con_button.setToggle(true);
//		Core::gui->addButton("GameMenu", "Window 1", "Update Map", con_button);
//
//		// Cancel Button
//		con_button.setToggle(false);
//		con_button.setOrigin(Core::GUI::ORIGIN_CENTER|Core::GUI::ORIGIN_BOTTOM);
//		con_button.setAnchor(Core::GUI::ANCHOR_BOTTOM|Core::GUI::ANCHOR_LEFT);		// Center of button
//		con_button.setPos(-5, 5);
//		con_button.setWidth(100, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);				// Exact button width
//		con_button.setHeight(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);				// Exact button height
//		con_button.setBorder(1, true);
//		con_button.setRadius(10);
//		con_button.setColorWindow(Core::colors->brown, Core::colors->orange);
//		con_button.setColorText(Core::colors->white, Core::colors->green);
//		Core::gui->addButton("GameMenu", "Window 2", "Show", con_button);
//
//		con_button.setToggle(true);
//		con_button.setOrigin(Core::GUI::ORIGIN_CENTER|Core::GUI::ORIGIN_TOP);
//		con_button.setAnchor(Core::GUI::ANCHOR_TOP|Core::GUI::ANCHOR_LEFT);		// Center of button
//		con_button.setPos(-5, -5);
//		con_button.setWidth(100, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);				// Exact button width
//		con_button.setHeight(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);				// Exact button height
//		con_button.setBorder(1, true);
//		con_button.setRadius(10);
//		con_button.setColorWindow(Core::colors->brown, Core::colors->orange);
//		con_button.setColorText(Core::colors->white, Core::colors->green);
//		Core::gui->addButton("GameMenu", "Window 2", "TEST", con_button);
//
//		bOneShot[20] = true;
//	}
//
//	// No parent button (Toggle Menu)
//	if (!bOneShot[21]) {
//		Core::GUI::Constraints_Button con_button;
//		con_button.setOrigin(Core::GUI::ORIGIN_BOTTOM|Core::GUI::ORIGIN_RIGHT);
//		con_button.setAnchor(Core::GUI::ANCHOR_BOTTOM|Core::GUI::ANCHOR_RIGHT);		// Center of button
//		con_button.setPos(-20, 20);
//		con_button.setWidth(120, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);				// Exact button width
//		con_button.setHeight(30, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);				// Exact button height
//		con_button.setBorder(1, true);
//		con_button.setRadius(10);
//		con_button.setColorWindow(Core::colors->brown, Core::colors->orange);
//		con_button.setColorText(Core::colors->white, Core::colors->green);
//		Core::gui->addButton("GameMenu", "Toggle Menu", con_button);
//		bOneShot[21] = true;
//	}
//
//	// Slider Testing
//	if (!bOneShot[22]) {
//		Core::GUI::Constraints_Slider con;
//		con.setOrigin(Core::GUI::ORIGIN_CENTER|Core::GUI::ORIGIN_BOTTOM);
//		//con.setAnchor(Core::GUI::ANCHOR_BOTTOM_CENTER);					// Center of button
//		con.setAnchor(Core::GUI::ANCHOR_CENTER);					// Center of button
//		con.setPos(0, 60);
//		con.setWidth(200, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);			// Exact button width
//		con.setHeight(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);			// Exact button height
//		con.setRatio(0.25f);
//		con.setMinMax(1.0f, 10.0f);
//		con.setShowValue(true);
//		con.setShowLabel(true);
//		con.setColorSlider(Core::colors->white, Core::colors->black);
//		con.setColorControl(Core::colors->brown, Core::colors->black);
//		Core::gui->addSlider("GameMenu", "Window 1", "World Scale", con, Core::gameVars->screen.fScale);
////		Core::gui->addSlider("GameMenu", "Slider 1", con);
//
//		// Delta
//		con.setY(300);
//		con.setMinMax(0.000001f, 10.0f);
//		Core::gui->addSlider("GameMenu", "Window 1", "Delta", con, Core::gameVars->debug.noise.simplex.delta);
//
//		// Frequency
//		con.setY(250);
//		con.setMinMax(0.000001f, 0.001f);
//		Core::gui->addSlider("GameMenu", "Window 1", "Frequency", con, Core::gameVars->debug.noise.simplex.frequency);
//
//		// Amplitude
//		con.setY(225);
//		con.setMinMax(1.0f, 3.0f);
//		Core::gui->addSlider("GameMenu", "Window 1", "Amplitude", con, Core::gameVars->debug.noise.simplex.amplitude);
//
//		// Lacunarity
//		con.setY(200);
//		con.setMinMax(0.01f, 10.0f);
//		Core::gui->addSlider("GameMenu", "Window 1", "Lacunarity", con, Core::gameVars->debug.noise.simplex.lacunarity);
//
//		// Persistance
//		con.setY(175);
//		con.setMinMax(0.01f, 1.0f);
//		Core::gui->addSlider("GameMenu", "Window 1", "Persistance", con, Core::gameVars->debug.noise.simplex.persistance);
//
//		// Power
//		con.setY(150);
//		con.setMinMax(1.0f, 1.0f);
//		Core::gui->addSlider("GameMenu", "Window 1", "Power", con, Core::gameVars->debug.noise.simplex.power);
//
//		// Scale
//		con.setY(125);
//		con.setMinMax(0.1f, 5000.0f);
//		Core::gui->addSlider("GameMenu", "Window 1", "Scale", con, Core::gameVars->debug.noise.simplex.scale);
//
//		// Octaves
//		con.setY(100);
//		con.setMinMax(1.0f, 10.0f);
//		Core::gui->addSlider("GameMenu", "Window 1", "Octaves", con, Core::gameVars->debug.noise.simplex.octaves);
//
//		bOneShot[22] = true;
//	}
//
//	// Slider - Lighting
//	if (!bOneShot[30]) {
//		Core::GUI::Constraints_Slider con;
//		con.setOrigin(Core::GUI::ORIGIN_CENTER|Core::GUI::ORIGIN_BOTTOM);
//		//con.setAnchor(Core::GUI::ANCHOR_BOTTOM_CENTER);					// Center of button
//		con.setAnchor(Core::GUI::ANCHOR_CENTER);					// Center of button
//		con.setPos(0, 75);
//		con.setWidth(200, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);			// Exact button width
//		con.setHeight(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);			// Exact button height
//		con.setRatio(0.25f);
//		con.setShowValue(true);
//		con.setShowLabel(true);
//		con.setColorSlider(Core::colors->white, Core::colors->black);
//		con.setColorControl(Core::colors->brown, Core::colors->black);
//
//		con.setY(75);
//		con.setMinMax(0.0f, 1.0f);
//		Core::gui->addSlider("GameMenu", "Window 3", "Light", con, iDebugLight);
//
//		// Position
//		con.setY(300);
//		con.setMinMax(-1000.0f, 1000.0f);
//		Core::gui->addSlider("GameMenu", "Window 3", "Light Pos X", con, world->lights->GetPos(iDebugLight).x);
//
//		con.setY(275);
//		con.setMinMax(-1000.0f, 1000.0f);
//		Core::gui->addSlider("GameMenu", "Window 3", "Light Pos Y", con, world->lights->GetPos(iDebugLight).y);
//
//		con.setY(250);
//		con.setMinMax(-1000.0f, 1000.0f);
//		Core::gui->addSlider("GameMenu", "Window 3", "Light Pos Z", con, world->lights->GetPos(iDebugLight).z);
//
//		// Direction
//		con.setY(200);
//		con.setMinMax(-1.0f, 1.0f);
//		Core::gui->addSlider("GameMenu", "Window 3", "Light Dir X", con, world->lights->GetDir(iDebugLight).x);
//
//		con.setY(175);
//		con.setMinMax(-1.0f, 1.0f);
//		Core::gui->addSlider("GameMenu", "Window 3", "Light Dir Y", con, world->lights->GetDir(iDebugLight).y);
//
//		con.setY(150);
//		con.setMinMax(-1.0f, 1.0f);
//		Core::gui->addSlider("GameMenu", "Window 3", "Light Dir Z", con, world->lights->GetDir(iDebugLight).z);
//
//		// Color
////		con.setY(100);
////		con.setMinMax(0.000001f, 10.0f);
////		Core::gui->addSlider("GameMenu", "Window 3", "Light X", con, world->lights->GetColor(0).x);
////
////		con.setY(175);
////		con.setMinMax(0.000001f, 0.001f);
////		Core::gui->addSlider("GameMenu", "Window 3", "Light Y", con, world->lights->GetPos(0).y);
////
////		con.setY(150);
////		con.setMinMax(1.0f, 3.0f);
////		Core::gui->addSlider("GameMenu", "Window 3", "Light Z", con, world->lights->GetPos(0).z);
//
////		con.setY(100);
////		con.setMinMax(1.0f, 3.0f);
////		Core::gui->addSlider("GameMenu", "Window 3", "Light Z", con, world->lights->GetPos(0).z);
//
//		bOneShot[30] = true;
//	}
//	Core::gui->exec("GameMenu");
//
//
//	// Update lighting values from sliders
//	//	Core::Vector3f vTemp = world->lights->GetPos(iDebugLight);
//	//	vTemp.y += fMoveModSpeed;
//	//	world->lights->SetPos(iDebugLight, vTemp);
////	world->lights->GetLightData()[0].pos.x
//
////	std::cout << "Light status = [" << Core::gui->getSliderState("GameMenu", "Light") << "]" << std::endl;
//	iDebugLight = Core::gui->getSliderValue("GameManu", "Light");
//
//	if(Core::gui->getSliderState("GameMenu", "Light")==Core::_Mouse::MOUSE_LEFT_DOWN || Core::gui->getSliderState("GameMenu", "Light")==Core::_Mouse::MOUSE_LEFT) {
//		Core::gui->setSlider("GameManu", "Light Pos X", world->lights->GetPos(iDebugLight).x);
//		Core::gui->setSlider("GameManu", "Light Pos Y", world->lights->GetPos(iDebugLight).y);
//		Core::gui->setSlider("GameManu", "Light Pos Z", world->lights->GetPos(iDebugLight).z);
//		Core::gui->setSlider("GameManu", "Light Dir X", world->lights->GetDir(iDebugLight).x);
//		Core::gui->setSlider("GameManu", "Light Dir Y", world->lights->GetDir(iDebugLight).y);
//		Core::gui->setSlider("GameManu", "Light Dir Z", world->lights->GetDir(iDebugLight).z);
//		std::cout << std::endl;
//	}
//	else {
//		world->lights->GetPosPtr(iDebugLight).x = Core::gui->getSliderValue("GameManu", "Light Pos X");
//		world->lights->GetPosPtr(iDebugLight).y = Core::gui->getSliderValue("GameManu", "Light Pos Y");
//		world->lights->GetPosPtr(iDebugLight).z = Core::gui->getSliderValue("GameManu", "Light Pos Z");
//		world->lights->GetDirPtr(iDebugLight).x = Core::gui->getSliderValue("GameManu", "Light Dir X");
//		world->lights->GetDirPtr(iDebugLight).y = Core::gui->getSliderValue("GameManu", "Light Dir Y");
//		world->lights->GetDirPtr(iDebugLight).z = Core::gui->getSliderValue("GameManu", "Light Dir Z");
//	}
//	world->o3d->data.items[iDebugObject].translate = world->lights->GetPos(iDebugLight);
//
//	Core::gameVars->screen.fScale = Core::gui->getSliderValue("GameMenu", "Slider 1");
//
//	// Update MapSys values and regenerate
//	Core::gameVars->debug.noise.simplex.delta 		= Core::gui->getSliderValue("GameMenu", "Delta");
//	Core::gameVars->debug.noise.simplex.frequency	= Core::gui->getSliderValue("GameMenu", "Frequency");
//	Core::gameVars->debug.noise.simplex.amplitude	= Core::gui->getSliderValue("GameMenu", "Amplitude");
//	Core::gameVars->debug.noise.simplex.lacunarity	= Core::gui->getSliderValue("GameMenu", "Lacunarity");
//	Core::gameVars->debug.noise.simplex.persistance	= Core::gui->getSliderValue("GameMenu", "Persistance");
//	Core::gameVars->debug.noise.simplex.power		= Core::gui->getSliderValue("GameMenu", "Power");
//	Core::gameVars->debug.noise.simplex.scale		= Core::gui->getSliderValue("GameMenu", "Scale");
//	Core::gameVars->debug.noise.simplex.octaves		= Core::gui->getSliderValue("GameMenu", "Octaves");
//
//	//if(Core::gameVars->screen.fScale != fTest_fScaleOld) {
//	if(Core::gui->getButtonActive("GameMenu", "Update Map")) {
//		world->map->update();
//	}
//		//fTest_fScaleOld = Core::gameVars->screen.fScale;
//	//}
//
//	// Test mouse states - debug messages
////	std::cout << "Slider Status = " << Core::gui->getSliderState("GameMenu", "Slider 1") << ", value = " << Core::gui->getSliderValue("GameMenu", "Slider 1") << std::endl;
////	std::cout << "Hide Status = " << Core::gui->getButtonState("GameMenu", "Hide") << std::endl;
////	std::cout << "Show Status = " << Core::gui->getButtonState("GameMenu", "Show") << std::endl << std::endl;
//	if(Core::gui->getButtonState("GameMenu", "Hide")==Core::_Mouse::MOUSE_LEFT_DOWN) std::cout << "MOUSE HELD..." << Core::timeSys->get_ticks() << std::endl;
//
//	// Hide/Show Window 1 from Window 2 buttons
//	if(Core::gui->getButtonState("GameMenu", "Hide")==Core::_Mouse::MOUSE_LEFT) Core::gui->hideWindow("GameMenu", "Window 1");
//	if(Core::gui->getButtonState("GameMenu", "Show")==Core::_Mouse::MOUSE_LEFT) Core::gui->showWindow("GameMenu", "Window 1");
//
//	if(Core::gui->getButtonActive("GameMenu", "TEST")) {
//		Core::gui->hideWindow("GameMenu", "Window 1");
//		Core::gui->showWindow("GameMenu", "Window 3");
//	}
//	else {
//		Core::gui->hideWindow("GameMenu", "Window 3");
//	}
//
//	// Get GUI focus state, disable mouse and movement input to world
//	bHasFocus = !Core::gui->hasFocus();
////	std::cout << "Focus = " << bHasFocus << "[" << Core::gui->iGUIFocus << "]" << std::endl;
//
//	if(Core::gui->getButtonState("GameMenu", "Toggle Menu")==Core::_Mouse::MOUSE_LEFT) Core::gui->toggleWindow("GameMenu", "Window 2");
//	if(Core::gui->isHiddenWindow("GameMenu", "Window 2") && !Core::gui->isHiddenWindow("GameMenu", "Window 1")) Core::gui->hideWindow("GameMenu", "Window 1");

	// Safety Catch, make sure we are in perspective mode by default
	Core::matrix->SetProjection(Core::matrix->MM_PERSPECTIVE);

//	Core::colors->PopFront();
}

void _Game::GetInput() {
	SDL_PumpEvents();
	Core::mouse->update(Core::gameVars->screen.half.x, Core::gameVars->screen.half.y);
	//keyboard.event = SDL_GetKeyState(NULL);
	keyboard.event = SDL_GetKeyboardState(NULL);
	keyboard.update();

//	std::cout << "GetInput     - Game" << std::endl;

	if(bHasFocus) ProcessInput();
}

void _Game::ProcessInput() {

//	std::cout << "ProcessInput - Game" << std::endl;

	if (keyboard.keys[SDLK_ESCAPE].bActive) {
		Core::mouse->ToggleMouse(SDL_FALSE);
		Core::gameVars->runState.quit = true;
	}

	if (keyboard.keys[SDLK_DELETE].bActive) {
	}

	if (keyboard.keys[SDLK_PAGEUP].bActive) {
	}

	if (keyboard.keys[SDLK_PAGEDOWN].bActive) {
	}

	if (keyboard.keys[SDLK_TAB].bActive) {
		Core::mouse->ToggleMouse();
	}

	if (keyboard.keys[SDLK_BACKQUOTE].bActive) {
		//Core::gameVars->state.console=true;
	}

	// TODO: Fix Light Control
	if (keyboard.keys[SDLK_F1].bActive) {
		Core::gameVars->runState.admin=true;
		Core::mouse->ToggleMouse(SDL_FALSE);
//		Core::Vector3f vTemp = world->lights->GetAttenuation(iDebugLight);
//		if (Core::gameVars->controls.modSpeed == 1) vTemp.x += vDebugAttDelta.x;
//		else vTemp.x -= vDebugAttDelta.x;
//
//		if(vTemp.x < 0.0f) vTemp.x = 0.0f;
//		world->lights->SetAttenuation(iDebugLight, vTemp);
//		std::cout << vTemp.x << ", " << vTemp.y << ", " << vTemp.z << std::endl;
	}

	if (keyboard.keys[SDLK_F2].bActive) {
//		Core::Vector3f vTemp = world->lights->GetAttenuation(iDebugLight);
//		if (Core::gameVars->controls.modSpeed == 1) vTemp.y += vDebugAttDelta.y;
//		else vTemp.y -= vDebugAttDelta.y;
//
//		if(vTemp.y < 0.0f) vTemp.y = 0.0f;
//		world->lights->SetAttenuation(iDebugLight, vTemp);
//		std::cout << vTemp.x << ", " << vTemp.y << ", " << vTemp.z << std::endl;
	}

	if (keyboard.keys[SDLK_F3].bActive) {
//		Core::Vector3f vTemp = world->lights->GetAttenuation(iDebugLight);
//		if (Core::gameVars->controls.modSpeed == 1) vTemp.z += vDebugAttDelta.z;
//		else vTemp.z -= vDebugAttDelta.z;
//
//		if(vTemp.z < 0.0f) vTemp.z = 0.0f;
//		world->lights->SetAttenuation(iDebugLight, vTemp);
//		std::cout << vTemp.x << ", " << vTemp.y << ", " << vTemp.z << std::endl;
	}

//	if (keyboard.keys[SDLK_F4].bActive) {
//		if(keyboard.keys[SDLK_LCTRL].bActive) {
//			iDebugObject+=1;
//			if(iDebugObject>world->o3d->data.idcount) {
//				iDebugObject = 0;
//			}
//			Core::Vector3f vTemp = world->lights->GetPos(iDebugLight);
//			world->o3d->data.items[iDebugObject].posMod = vTemp;
//		}
//		else {
//			iDebugLight+=1;
//			if(iDebugLight>=world->lights->GetNumLights()) {
//				iDebugLight = 0;
//			}
//			Core::Vector3f vTemp = world->lights->GetPos(iDebugLight);
//			world->o3d->data.items[iDebugObject].posMod = vTemp;
//		}
//	}

//	if (keyboard.keys[SDLK_F5].bActive)		{	Core::gameVars->screen.iPolygonMode = GL_FILL;	}
//	if (keyboard.keys[SDLK_F6].bActive)		{	Core::gameVars->screen.iPolygonMode = GL_LINE;	}
//	if (keyboard.keys[SDLK_F7].bActive)		{	Core::gameVars->screen.iPolygonMode = GL_POINT;	}
	if (keyboard.keys[SDLK_F8].bActive) 	{	Core::toggle(bDebugDrawMouseRay);	}
	if (keyboard.keys[SDLK_F9].bActive) 	{	Core::mouse->SaveRay(Core::gameVars->player.active->transform.pos);	}
	if (keyboard.keys[SDLK_F10].bActive)	{	SDL_WarpMouseInWindow(Core::glinit->window, Core::gameVars->screen.half.x, Core::gameVars->screen.half.y);	}
	if (keyboard.keys[SDLK_F11].bActive)	{	Core::profiles->reset();	}
	if (keyboard.keys[SDLK_F12].bActive)	{	SDL_SetWindowFullscreen(Core::glinit->window, SDL_WINDOW_FULLSCREEN);	}

	if (keyboard.keys[SDLK_LEFTBRACKET].bActive) {
		if(keyboard.keys[SDLK_LCTRL].bActive) {
			vDebugRotation.x -= 0.1;
		}
		else if(keyboard.keys[SDLK_LSHIFT].bActive) {
			vDebugRotation.z -= 0.1;
		}
		else {
			vDebugRotation.y -= 0.1;
		}
	}

	if (keyboard.keys[SDLK_RIGHTBRACKET].bActive) {
		if(keyboard.keys[SDLK_LCTRL].bActive) {
			vDebugRotation.x += 0.1;
		}
		else if(keyboard.keys[SDLK_LSHIFT].bActive) {
			vDebugRotation.z += 0.1;
		}
		else {
			vDebugRotation.y += 0.1;
		}
	}


	// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
	// Speed Limited Input (Movement speed according to framerate)
	// ----------------------------------------------------------------------------------------------------------------------------------------------------
	//if (Core::gameVars->timer.frameRate.get_splitdiff() > 10) {
	{

		if (keyboard.keys[Core::gameVars->controls.key.run].bActive) Core::gameVars->controls.modSpeed = 10;
		else if (keyboard.keys[Core::gameVars->controls.key.sneak].bActive) Core::gameVars->controls.modSpeed = 0.1;
		else Core::gameVars->controls.modSpeed = 1;

		// Framerate speed control
		float fMoveModSpeed = (Core::gameVars->controls.moveSpeed * Core::gameVars->controls.modSpeed) * Core::gameVars->timer.frameRate.get_splitdiff();
		Core::gameVars->timer.frameRate.split();

		// TODO: Fix Light Control
		// ===================
		// Light control
//		if (iDebugLight != iPlayerLight) {
//			if (keyboard.keys[SDLK_UP].bActive) {
//				Core::Vector3f vTemp = world->lights->GetPos(iDebugLight);
//				vTemp.y += fMoveModSpeed;
//				world->lights->SetPos(iDebugLight, vTemp);
//				world->o3d->data.items[iDebugObject].posMod = vTemp;
//				//std::cout << vTemp.x << ", " << vTemp.y << ", " << vTemp.z << std::endl;
//			}
//
//			if (keyboard.keys[SDLK_DOWN].bActive) {
//				Core::Vector3f vTemp = world->lights->GetPos(iDebugLight);
//				vTemp.y -= fMoveModSpeed;
//				world->lights->SetPos(iDebugLight, vTemp);
//				world->o3d->data.items[iDebugObject].posMod = vTemp;
//				//std::cout << vTemp.x << ", " << vTemp.y << ", " << vTemp.z << std::endl;
//			}
//
//			if (keyboard.keys[SDLK_LEFT].bActive) {
//				/*
//				 * TODO: Add in rotation debugging
//				 *
//				 * If this is done right the lights may be able to be saved
//				 * to the map file. Game editing from within the game could
//				 * be a huge bonus rather than rewriting a separate
//				 * renderer.
//				 */
//
//				//if(keyboard.keys[SDLK_LCTRL]) {
//				//	Core::Vector3f vTemp = world->lights->GetDir(iDebugLight);
//				//}
//				//else {
//					Core::Vector3f vTemp = world->lights->GetPos(iDebugLight);
//					vTemp.x -= fMoveModSpeed;
//					world->lights->SetPos(iDebugLight, vTemp);
//					world->o3d->data.items[iDebugObject].posMod = vTemp;
//					//std::cout << vTemp.x << ", " << vTemp.y << ", " << vTemp.z << std::endl;
//				//}
//			}
//
//			if (keyboard.keys[SDLK_RIGHT].bActive) {
//				Core::Vector3f vTemp = world->lights->GetPos(iDebugLight);
//				vTemp.x += fMoveModSpeed;
//				world->lights->SetPos(iDebugLight, vTemp);
//				world->o3d->data.items[iDebugObject].posMod = vTemp;
//				//std::cout << vTemp.x << ", " << vTemp.y << ", " << vTemp.z << std::endl;
//			}
//
//			if (keyboard.keys[SDLK_END].bActive) {
//				Core::Vector3f vTemp = world->lights->GetPos(iDebugLight);
//				vTemp.z += fMoveModSpeed;
//				world->lights->SetPos(iDebugLight, vTemp);
//				world->o3d->data.items[iDebugObject].posMod = vTemp;
//				//std::cout << vTemp.x << ", " << vTemp.y << ", " << vTemp.z << std::endl;
//			}
//
//			if (keyboard.keys[SDLK_HOME].bActive) {
//				Core::Vector3f vTemp = world->lights->GetPos(iDebugLight);
//				vTemp.z -= fMoveModSpeed;
//				world->lights->SetPos(iDebugLight, vTemp);
//				world->o3d->data.items[iDebugObject].posMod = vTemp;
//				//std::cout << vTemp.x << ", " << vTemp.y << ", " << vTemp.z << std::endl;
//			}
//		}

		// ===================
		// Player Control
		if(bHasFocus) {
			if (keyboard.keys[Core::gameVars->controls.key.move_up].bActive) {
				Core::gameVars->player.active->transform.pos[1] -= fMoveModSpeed;
			}

			if (keyboard.keys[Core::gameVars->controls.key.move_down].bActive) {
				Core::gameVars->player.active->transform.pos[1] += fMoveModSpeed;
			}

			if (keyboard.keys[Core::gameVars->controls.key.strafe_left].bActive){
				int iAirControl = 1;
				float fNewX = ((float)cos( Core::gameVars->player.active->transform.rot[1] ) * fMoveModSpeed);
				float fNewZ = ((float)sin( Core::gameVars->player.active->transform.rot[1] ) * fMoveModSpeed);
		//		if (!Core::gameVars->controls.fly) {
					float fTempPosX = Core::gameVars->player.active->transform.pos[0];
					float fTempPosZ = Core::gameVars->player.active->transform.pos[2];
					Core::gameVars->player.active->transform.last[0] += fNewX;
					Core::gameVars->player.active->transform.last[2] += fNewZ;
					Core::gameVars->player.active->transform.pos[0]  += fNewX;
					Core::gameVars->player.active->transform.pos[2]  += fNewZ;
		//		}
		//		else {
		//			float fTempPosX = Core::gameVars->player.active->transform.pos[0];
		//			float fTempPosZ = Core::gameVars->player.active->transform.pos[2];
		//			Core::gameVars->player.active->transform.last[0] += fNewX;
		//			Core::gameVars->player.active->transform.last[2] += fNewZ;
		//			Core::gameVars->player.active->transform.pos[0]  += fNewX;
		//			Core::gameVars->player.active->transform.pos[2]  += fNewZ;
		//
		//			//GetHeight();
		//		}
			}
			if (keyboard.keys[Core::gameVars->controls.key.strafe_right].bActive){
				int iAirControl = 1;
				float fNewX = ((float)cos( Core::gameVars->player.active->transform.rot[1] ) * fMoveModSpeed);
				float fNewZ = ((float)sin( Core::gameVars->player.active->transform.rot[1] ) * fMoveModSpeed);
		//		if (!Core::gameVars->controls.fly) {
					float fTempPosX = Core::gameVars->player.active->transform.pos[0];
					float fTempPosZ = Core::gameVars->player.active->transform.pos[2];
					Core::gameVars->player.active->transform.last[0] -= fNewX;
					Core::gameVars->player.active->transform.last[2] -= fNewZ;
					Core::gameVars->player.active->transform.pos[0]  -= fNewX;
					Core::gameVars->player.active->transform.pos[2]  -= fNewZ;
		//		}
		//		else {
		//			float fTempPosX = Core::gameVars->player.active->transform.pos[0];
		//			float fTempPosZ = Core::gameVars->player.active->transform.pos[2];
		//			Core::gameVars->player.active->transform.last[0] -= fNewX;
		//			Core::gameVars->player.active->transform.last[2] -= fNewZ;
		//			Core::gameVars->player.active->transform.pos[0]  -= fNewX;
		//			Core::gameVars->player.active->transform.pos[2]  -= fNewZ;
		//
		//			//GetHeight();
		//		}
			}

			if (keyboard.keys[Core::gameVars->controls.key.move_forward].bActive) {
				int iAirControl = 1;
				float fNewX = ((float)sin( Core::gameVars->player.active->transform.rot[1] ) * fMoveModSpeed);
				float fNewZ = ((float)cos( Core::gameVars->player.active->transform.rot[1] ) * fMoveModSpeed);
		//		if (!Core::gameVars->controls.fly) {
					float fTempPosX = Core::gameVars->player.active->transform.pos[0];
					float fTempPosZ = Core::gameVars->player.active->transform.pos[2];
					Core::gameVars->player.active->transform.last[0] -= fNewX;;
					Core::gameVars->player.active->transform.last[2] += fNewZ;;
					Core::gameVars->player.active->transform.pos[0]  -= fNewX;
					Core::gameVars->player.active->transform.pos[2]  += fNewZ;
		//		}
		//		else {
		//			float fTempPosX = Core::gameVars->player.active->transform.pos[0];
		//			float fTempPosZ = Core::gameVars->player.active->transform.pos[2];
		//			Core::gameVars->player.active->transform.last[0] -= fNewX;
		//			Core::gameVars->player.active->transform.last[2] += fNewZ;
		//			Core::gameVars->player.active->transform.pos[0]  -= fNewX;
		//			Core::gameVars->player.active->transform.pos[2]  += fNewZ;
		//
		//			//GetHeight();
		//		}
			}
			if (keyboard.keys[Core::gameVars->controls.key.move_back].bActive) {
				int iAirControl = 1;
				float fNewX = ((float)sin( Core::gameVars->player.active->transform.rot[1] ) * fMoveModSpeed);
				float fNewZ = ((float)cos( Core::gameVars->player.active->transform.rot[1] ) * fMoveModSpeed);
		//		if (!Core::gameVars->controls.fly) {
					float fTempPosX = Core::gameVars->player.active->transform.pos[0];
					float fTempPosZ = Core::gameVars->player.active->transform.pos[2];
					Core::gameVars->player.active->transform.last[0] += fNewX;
					Core::gameVars->player.active->transform.last[2] -= fNewZ;
					Core::gameVars->player.active->transform.pos[0]  += fNewX;
					Core::gameVars->player.active->transform.pos[2]  -= fNewZ;
		//		}
		//		else {
		//			float fTempPosX = Core::gameVars->player.active->transform.pos[0];
		//			float fTempPosZ = Core::gameVars->player.active->transform.pos[2];
		//			Core::gameVars->player.active->transform.last[0] += fNewX;
		//			Core::gameVars->player.active->transform.last[2] -= fNewZ;
		//			Core::gameVars->player.active->transform.pos[0]  += fNewX;
		//			Core::gameVars->player.active->transform.pos[2]  -= fNewZ;
		//
		//			//GetHeight();
		//		}
			}

			//Simulate mouse with keys
			if (!SDL_GetRelativeMouseMode()) {
				if (keyboard.keys[Core::gameVars->controls.key.mouse_left].bActive) {
					Core::mouse->relX=-1;
				}
				else if (keyboard.keys[Core::gameVars->controls.key.mouse_right].bActive) {
					Core::mouse->relX=1;
				}
				else Core::mouse->relX=0;
				if (keyboard.keys[Core::gameVars->controls.key.mouse_up].bActive) {
					Core::mouse->relY=-1;
				}
				else if (keyboard.keys[Core::gameVars->controls.key.mouse_down].bActive) {
					Core::mouse->relY=1;
				}
				else Core::mouse->relY=0;
			}
//		}

// TODO: Mouse look controls

	//std::cout << "Mouse movement: " << Core::mouse->relX << ", " << Core::mouse->relY << std::endl;

			if(Core::mouse->button.pressed[SDL_BUTTON_LEFT]) {
				Core::mouse->SaveRay(Core::gameVars->player.active->transform.pos);
				Core::collision->bUpdateRequest[0] = true;
			}

			if (Core::mouse->relX<-Core::mouse->deadX) {
				Core::gameVars->player.active->transform.rot[1]+=(Core::mouse->relX)*Core::mouse->sensX;
				if (Core::Radians(Core::gameVars->player.active->transform.rot[1]).toDegrees()>360) Core::gameVars->player.active->transform.rot[1] = Core::gameVars->player.active->transform.rot[1] - Core::Degrees(360).toRadians();
				if (Core::Radians(Core::gameVars->player.active->transform.rot[1]).toDegrees() < 0) Core::gameVars->player.active->transform.rot[1] = Core::gameVars->player.active->transform.rot[1] = Core::Degrees(360).toRadians() + Core::gameVars->player.active->transform.rot[1];
				//Core::mouse->sdlWarpMouse(Core::gameVars->screen.fHalfW, Core::gameVars->screen.fHalfH);
			}
			if (Core::mouse->relX>Core::mouse->deadX) {
				Core::gameVars->player.active->transform.rot[1]+=(Core::mouse->relX)*Core::mouse->sensX;
				if (Core::Radians(Core::gameVars->player.active->transform.rot[1]).toDegrees()>360) Core::gameVars->player.active->transform.rot[1] = Core::gameVars->player.active->transform.rot[1] - Core::Degrees(360).toRadians();
				if (Core::Radians(Core::gameVars->player.active->transform.rot[1]).toDegrees() < 0) Core::gameVars->player.active->transform.rot[1] = Core::gameVars->player.active->transform.rot[1] = Core::Degrees(360).toRadians() + Core::gameVars->player.active->transform.rot[1];
				//Core::mouse->sdlWarpMouse(Core::gameVars->screen.fHalfW, Core::gameVars->screen.fHalfH);
			}
			if (Core::mouse->relY<-Core::mouse->deadY) {
				if(-Core::gameVars->player.active->transform.rot[0] < Core::Degrees(90).toRadians() ) {
					Core::gameVars->player.active->transform.rot[0]+=(Core::mouse->relY)*Core::mouse->sensY;
				} else {
					Core::gameVars->player.active->transform.rot[0] = Core::Degrees(-90).toRadians();
				}
				//Core::mouse->sdlWarpMouse(Core::gameVars->screen.fHalfW, Core::gameVars->screen.fHalfH);
			}
			if (Core::mouse->relY>Core::mouse->deadY) {
				if(Core::gameVars->player.active->transform.rot[0] < Core::Degrees(90).toRadians() ) {
					Core::gameVars->player.active->transform.rot[0]+=(Core::mouse->relY)*Core::mouse->sensY;
				} else {
					Core::gameVars->player.active->transform.rot[0] = Core::Degrees(90).toRadians();
				}
				//Core::mouse->sdlWarpMouse(Core::gameVars->screen.fHalfW, Core::gameVars->screen.fHalfH);
			}
		}
	}
}
#endif /* RUNGAME_HPP_ */
