/*
 * InputSys.h
 *
 *  Created on: Sep 21, 2010
 *      Author: bcthund
 */

#ifndef INPUTSYS_H_
#define INPUTSYS_H_

//#include "SDL2/SDL.h"
//extern "C++" {
	#include "matrix.h"
	#include "shader.h"
//}

namespace Core {
	class _Mouse {
		private:

		protected:

		public:
			_Mouse();

			typedef int iMouseState;
			enum MOUSE_STATE	{	MOUSE_NONE			= 1,
									MOUSE_HOVER			= 2,
									MOUSE_LEFT			= 4,
									MOUSE_LEFT_DOWN		= 8,
									MOUSE_RIGHT			= 16,
									MOUSE_RIGHT_DOWN	= 32,
									MOUSE_MIDDLE		= 64,
									MOUSE_DOUBLE		= 128,
									MOUSE_WHEEL_UP		= 256,
									MOUSE_WHEEL_DOWN	= 512,
									MOUSE_WHEEL_LEFT	= 1024,
									MOUSE_WHEEL_RIGHT	= 2048
								};

			Vector3f	mouseRay;						// Final calculated mouse ray
			Timer 		timer;							//
			bool 		bToggleMem;						// Enable for mouse capture, used to prevent screen jump
			int 		x, y;							// Current x,y coordinates of mouse
			float 		sensX, sensY;					// Sensitivity of mouse
			int 		deadX, deadY;					// Deadzone for mouse
			int 		relX, relY;						// Current relative mouse movement for captured mouse
			float 		fMouseDelay, fMouseDelayConst;	// Delay for repeat mouse clicksz
			struct {									// Debugging rays
				Vector3f	pos;						// Ray position
				Vector3f	dir;						// Ray direction
				Vector3f	start;						// Final computed ray starting point
				Vector3f	end;						// Final computed ray end point
//				VAO 		vao;
			} rays[2];									// [0] = current ray, [1] = stored ray

			struct _Button {
				bool check[10];
				bool pressed[10];
				bool held[10];
				bool repeat[10];

				_Button() {
					for (int i=0; i<10; i++) {
						check[i] = false;
						pressed[i] = false;
						held[i] = false;
						repeat[i] = false;
					}
				}
			} button;

			struct _Wheel {
				bool up, down, left, right;
				_Wheel() {
					up		= false;
					down	= false;
					left	= false;
					right	= false;
				}
			} wheel;

			void init(uint ray, Vector3f position, bool bUpdate=false);
			void draw(	uint ray,
						Vector3f rotation,
						Vector3f position,
						int iSize=2.0f,
						Color vColorA=Color(1.0),
						Color vColorB=Color(1.0));
			void SaveRay(Vector3f position);
			void update(float fHalfW, float fHalfH);
			void checkButton(int button, bool bRepeat=false);
			void ToggleMouse();
			void ToggleMouse(SDL_bool bShow);
			MOUSE_STATE checkWheel();
			iMouseState checkInput(int x, int y, float w, float h, bool bCentered=true);		// Return mouse state for region (hover, clicked)
			MOUSE_STATE checkOver(int x, int y, float w, float h, bool bCentered=true);			// Return hover state for region
			MOUSE_STATE checkState();

			Vector3f GetMouseRay(float w, float h, Vector3f rotation) {
				// Normalized Device Coordinates
				float 		dx 		= (2.0f * x) / w - 1.0f;
				float 		dy 		= 1.0f - (2.0f * y) / h;
				float		dz 		= 1.0f;
				Vector3f 	ray_nds = Vector3f(dx, dy, dz);

				// Homogeneous Clip Coordinates
				Vector4f ray_clip = Vector4f(ray_nds.x, ray_nds.y, -1.0, 1.0);

				// 4D Eye (Camera) Coordinates
				Matrix44f projection_matrix = matrix->GetProjectionMatrix();
				Matrix44f inverse_projection = projection_matrix.Inverse();
				Vector4f ray_eye = inverse_projection * ray_clip;
				ray_eye = Vector4f(ray_eye.x, ray_eye.y, -1.0, 0.0);

				// World Coordinates
				Matrix44f view_matrix = matrix->GetModelView();
				Matrix44f inverse_view = view_matrix.Inverse();
				Vector4f ray_wor = (inverse_view * ray_eye);

				// Apply rotations
				matrix->Push();
				matrix->SetIdentity();
				matrix->Rotate(rotation[0], 1.0, 0.0, 0.0);
				matrix->Rotate(rotation[1], 0.0, 1.0, 0.0);
				Matrix44f mRot = matrix->GetRotView();
				matrix->Pop();
				Vector4f vTemp = mRot * Vector4f(ray_wor.x, ray_wor.y, ray_wor.z, ray_wor.w);

				// Normalize and return
				mouseRay = Vector3f (vTemp.x, vTemp.y, vTemp.z).normal();
				rays[0].pos = Vector3f(0.0f);
				rays[0].dir = mouseRay;
				return mouseRay;
			}

	//} *mouse = new _Mouse;
	};

	_Mouse::_Mouse() {
		bToggleMem = false;
		x = 0;
		y = 0;
		sensX = 0.005;
		sensY = 0.005;
		deadX = 0;
		deadY = 0;
		relX = 0;
		relY = 0;
		fMouseDelay=0;
		fMouseDelayConst=100;
		timer.start();

		rays[1].pos = Vector3f(0, 0, 0);
		rays[1].dir = Vector3f(1, 0, 0);
	}

	/** ******************************************************************************************************************************
	 *
	 * @param ray
	 * @param position
	 * @param bUpdate
	 * ****************************************************************************************************************************** */
	void _Mouse::init(uint ray, Vector3f position, bool bUpdate) {
		if(ray==0) {
			rays[ray].start = Vector3f(0.0f, 0.0f, 0.0f);
			rays[ray].end = Vector3f(rays[ray].dir.x * 1000, rays[ray].dir.y * 1000, rays[ray].dir.z * 1000);
		}
		else {
			Vector3f vPos = position+rays[ray].pos;
			rays[ray].start = vPos;
			rays[ray].end = Vector3f((rays[ray].dir*1000)+vPos);
		}
	}

	/** ******************************************************************************************************************************
	 *
	 * @param ray
	 * @param rotation
	 * @param position
	 * @param iSize
	 * @param vColorA
	 * @param vColorB
	 * ****************************************************************************************************************************** */
	void _Mouse::draw(uint ray, Vector3f rotation, Vector3f position, int iSize, Color vColorA, Color vColorB) {
		init(ray, position);

		glLineWidth(5.0f);
		matrix->Push();
			matrix->Rotate(rotation[0], 1.0, 0.0, 0.0);
			matrix->Rotate(rotation[1], 0.0, 1.0, 0.0);
			matrix->SetTransform();
			helper->drawLine(rays[ray].start, rays[ray].end, iSize, 1.0f, vColorA, vColorB);
		matrix->Pop();
		glLineWidth(1.0f);
	}

	/** ******************************************************************************************************************************
	 *
	 * @param position
	 * ****************************************************************************************************************************** */
	void _Mouse::SaveRay(Vector3f position) {
		// Save the current ray
		rays[1].pos = Vector3f(-position.x, -position.y, -position.z);
		//rays[1].pos = Vector3f(0.0f);
		rays[1].dir = Vector3f(mouseRay);
	}

	/** ******************************************************************************************************************************
	 *
	 * @param fHalfW
	 * @param fHalfH
	 * ****************************************************************************************************************************** */
	void _Mouse::update(float fHalfW, float fHalfH) {
		// Store the current mouse position for application use
		if (!SDL_GetRelativeMouseMode()) {
			SDL_GetMouseState(&x, &y);
			x = x-1;	// Mouse position appears to be off by 1 pixel [(1 to res.x) vs (0 to res.x-1)]
			y = y-1;	// Mouse position appears to be off by 1 pixel [(1 to res.x) vs (0 to res.x-1)]
		}
		else {
			x = fHalfW;
			y = fHalfH;
		}

		if (SDL_GetRelativeMouseMode() /*&& bEnable*/) {
			SDL_GetRelativeMouseState(&relX, &relY);

//			std::cout << "mouse = (" << relX << ", " << relY << ")";

			// Prevent view warping from mouse toggle
			if(bToggleMem) {
				relX = 0;
				relY = 0;
				bToggleMem = false;
			}

//			std::cout << " -> (" << relX << ", " << relY << ")" << std::endl;
		}

		// Left Mouse button
		if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(SDL_BUTTON_LEFT)) button.check[SDL_BUTTON_LEFT]=true;
		else button.check[SDL_BUTTON_LEFT]=false;
		checkButton(SDL_BUTTON_LEFT);

		// Right Mouse button
		if(SDL_GetMouseState(NULL, NULL)&SDL_BUTTON(SDL_BUTTON_RIGHT)) button.check[SDL_BUTTON_RIGHT]=true;
		else button.check[SDL_BUTTON_RIGHT]=false;
		checkButton(SDL_BUTTON_RIGHT);

		// Scroll Wheel
//		if(Core::sdlEvent->type == SDL_MOUSEWHEEL) {
//			if(Core::sdlEvent->wheel.y > 0) // scroll up
//			{
//				 std::cout << "Scroll Up [" << Core::sdlEvent->wheel.y << "]" << std::endl;
//			}
//			else if(Core::sdlEvent->wheel.y < 0) // scroll down
//			{
//				 std::cout << "Scroll Down [" << Core::sdlEvent->wheel.y << "]" << std::endl;
//			}
//
//			if(Core::sdlEvent->wheel.x > 0) // scroll right
//			{
//				 std::cout << "Scroll Right [" << Core::sdlEvent->wheel.x << "]" << std::endl;
//			}
//			else if(Core::sdlEvent->wheel.x < 0) // scroll left
//			{
//				 std::cout << "Scroll Left [" << Core::sdlEvent->wheel.x << "]" << std::endl;
//			}
//		}
	}

	/** ******************************************************************************************************************************
	 *
	 * @param iButton
	 * @param bRepeat
	 * ****************************************************************************************************************************** */
	void _Mouse::checkButton(int iButton, bool bRepeat) {
		if (button.check[iButton] && !button.repeat[iButton]) {
			button.pressed[iButton] = true;
			button.repeat[iButton] = true;
		}
		else if (button.check[iButton] && button.repeat[iButton]) {
			if (!bRepeat) {
				button.pressed[iButton] = false;
				button.held[iButton] = true;
			}
		}
		else if (!button.check[iButton] && button.repeat[iButton]) {
			button.pressed[iButton] = false;
			button.held[iButton] = false;
			button.repeat[iButton] = false;
		}
	}

	void _Mouse::ToggleMouse() {
		if(SDL_GetRelativeMouseMode()) {
			SDL_SetRelativeMouseMode(SDL_FALSE);
			SDL_SetWindowGrab(Core::glinit->window, SDL_FALSE);
		}
		else {
			SDL_SetRelativeMouseMode(SDL_TRUE);
			SDL_SetWindowGrab(Core::glinit->window, SDL_TRUE);
			bToggleMem = true;
		}
	}

	void _Mouse::ToggleMouse(SDL_bool bShow) {
		SDL_SetWindowGrab(Core::glinit->window, bShow);
		SDL_SetRelativeMouseMode(bShow);
		bToggleMem = bShow;
	}

	/** ******************************************************************************************************************************
	 *
	 * @return
	 * ****************************************************************************************************************************** */
	_Mouse::MOUSE_STATE _Mouse::checkWheel() {
		if (wheel.up) {
			wheel.up = false;
			return MOUSE_WHEEL_UP;
		}
		else if (wheel.down) {
			wheel.down = false;
			return MOUSE_WHEEL_DOWN;
		}
		else if (wheel.left) {
			wheel.left = false;
			return MOUSE_WHEEL_LEFT;
		}
		else if (wheel.right) {
			wheel.right = false;
			return MOUSE_WHEEL_RIGHT;
		}
		return MOUSE_NONE;
	}

	/** ******************************************************************************************************************************
	 *
	 * @param x
	 * @param y
	 * @param w
	 * @param h
	 * @param bCentered
	 * @return
	 *
	 * Returns if mouse clicked in defined region, or
	 * if mouse is hovering over region.
	 *
	 * ****************************************************************************************************************************** */
//	inline _Mouse::MOUSE_STATE _Mouse::checkInput(int x, int y, float w, float h, bool bCentered) {
	_Mouse::iMouseState _Mouse::checkInput(int x, int y, float w, float h, bool bCentered) {
		Vector2f vMouse = { float(this->x), float(this->y) };
		Vector2f vP1;
		Vector2f vP2;
		_Mouse::iMouseState mReturn = MOUSE_NONE;

		// Ignore anything outside the current scissor stack (used for GUI discrimination)
		bool bIgnoreInput = false;
		if(Core::scissor.bEnabled && !Core::scissor.getActive()) {
			bIgnoreInput = true;
		}

		if(!bIgnoreInput) {
			if(bCentered) {
				vP1    = { (float)x-(w/2.0f), (float)y-(h/2.0f) };
				vP2    = { (float)x+(w/2.0f), (float)y+(h/2.0f) };
			}
			else {
				vP1    = { (float)x, (float)y };
				vP2    = { (float)x+w, (float)y+h };
			}

			// Stacking mouse events (bitmask)
			if (Core::gmath.PointQuad2d(vMouse, vP1, vP2)) {
				mReturn = MOUSE_HOVER;
				if (button.pressed[SDL_BUTTON_LEFT]) mReturn |= MOUSE_LEFT;
				else if (button.held[SDL_BUTTON_LEFT]) mReturn |= MOUSE_LEFT_DOWN;

				if (button.pressed[SDL_BUTTON_RIGHT]) mReturn |= MOUSE_RIGHT;
				else if (button.held[SDL_BUTTON_RIGHT]) mReturn |= MOUSE_RIGHT_DOWN;

			}
			return mReturn;
		}
		else return MOUSE_NONE;
	}

	/** ******************************************************************************************************************************
	 *
	 * @param x
	 * @param y
	 * @param w
	 * @param h
	 * @param bCentered
	 * @return
	 * ****************************************************************************************************************************** */
	inline _Mouse::MOUSE_STATE _Mouse::checkOver(int x, int y, float w, float h, bool bCentered) {
		Vector2f vMouse = { float(this->x), float(this->y) };
		Vector2f vP1;
		Vector2f vP2;

		if(bCentered) {
			vP1    = { (float)x-(w/2.0f), (float)y-(h/2.0f) };
			vP2    = { (float)x+(w/2.0f), (float)y+(h/2.0f) };
		}
		else {
			vP1    = { (float)x, (float)y };
			vP2    = { (float)x+w, (float)y+h };
		}

		if (Core::gmath.PointQuad2d(vMouse, vP1, vP2)) return MOUSE_HOVER;
		else return MOUSE_NONE;
	}

	/** ******************************************************************************************************************************
	 *
	 * @return
	 *
	 * Check mouse button state regardless of position
	 *
	 * ****************************************************************************************************************************** */
	inline _Mouse::MOUSE_STATE _Mouse::checkState() {
		if (button.pressed[SDL_BUTTON_LEFT] || button.held[SDL_BUTTON_LEFT]) {
			if (button.pressed[SDL_BUTTON_LEFT]) {
				if (timer.get_ticks()>(fMouseDelay+fMouseDelayConst)) {
					fMouseDelay = timer.get_ticks();
					return MOUSE_LEFT;
				}
			}
			else return MOUSE_LEFT_DOWN;
		}
		return MOUSE_NONE;
	}

	/// #######################################################################################################################################
	/// #######################################################################################################################################
	/** ******************************************************************************************************************************
	 *  \class _Keyboard
	 *  \brief
	 *
	 *
	 *  ****************************************************************************************************************************** */
	class _Keyboard {
		private:

		protected:

		public:
			enum KeyType { KEYTYPE_ONESHOT, KEYTYPE_REPEAT, KEYTYPE_DEBOUNCE, KEYTYPE_TOGGLE };

			enum EditFlags {	EDIT_WRITE		= 1,						// Full write access
								EDIT_DELETE		= 2,						// Delete only (buffer limit detection by external caller)
								EDIT_NUMERIC	= 4,						// Numeric editing only
								EDIT_WD			= EDIT_WRITE|EDIT_DELETE	// Write and delete
							};
			_Keyboard();
			~_Keyboard();
			void AddKey(SDL_Keycode keyCode, KeyType eKeyType);
			void calc(KeyType eKeyType);
			void calc(SDL_Keycode iKey, KeyType eKeyType);
			void editBuffer(std::string &buffer, int flags);
//			void editBufferAt(std::string &buffer, bool bNumeric, int *cursorPos, bool bOverwrite);
			void editBufferAt(std::shared_ptr<std::string> &buffer, bool bNumeric, int *cursorPos, bool bOverwrite);
//			void insertBufferAt(std::string &buffer, int *cursorPos, char cChar, bool bOverwrite);
			void insertBufferAt(std::shared_ptr<std::string> &buffer, int *cursorPos, char cChar, bool bOverwrite);
			void update();
			const static Uint8* event;

			typedef std::map< SDL_Keycode, uint > _KeyMap;
			struct _KeyStruct {
				bool bActive;
				bool bRepeatState;
				bool bToggleState;
				KeyType eKeyType;
				SDL_Keycode keyCode;

				_KeyStruct(SDL_Keycode keyCode, KeyType eKeyType) {
					this->bActive = false;
					this->bRepeatState = false;
					this->bToggleState = false;
					this->eKeyType = eKeyType;
					this->keyCode = keyCode;
				}
			};

			struct _KeyArray {
				friend class _Keyboard;
				private:
					_KeyMap keyMap;
					Timer	repeatTimer;
					std::vector<_KeyStruct> data;
					_KeyStruct& getData(SDL_Keycode keyCode) {
						uint index = keyMap[keyCode];
						if(index>data.size()-1) index=data.size()-1;
						return data[index];
					}

				public:
					_KeyStruct& operator[](SDL_Keycode keyCode)	{ return getData(keyCode); }
					_KeyArray() {
						repeatTimer.start();
					}

					uint insert(SDL_Keycode keyCode, KeyType eKeyType ) {
						data.push_back(_KeyStruct(keyCode, eKeyType));
						keyMap.insert(std::make_pair(keyCode, data.size()-1));
						return data.size()-1;
					}

					void execOneShot(SDL_Keycode sdlKey) {
						if (event[SDL_GetScancodeFromKey(sdlKey)] && !getData(sdlKey).bRepeatState) {
							getData(sdlKey).bActive = true;
							getData(sdlKey).bRepeatState = true;
						}
						else if (event[SDL_GetScancodeFromKey(sdlKey)] && getData(sdlKey).bRepeatState) {
							getData(sdlKey).bActive = false;
						}
						else if (!event[SDL_GetScancodeFromKey(sdlKey)] && getData(sdlKey).bRepeatState) {
							getData(sdlKey).bActive = false;
							getData(sdlKey).bRepeatState = false;
						}
					}

					void execToggle(SDL_Keycode sdlKey) {
						if (event[SDL_GetScancodeFromKey(sdlKey)] && !getData(sdlKey).bToggleState) {
								getData(sdlKey).bActive = !getData(sdlKey).bActive;
								getData(sdlKey).bToggleState = true;
						}
						else if (!event[SDL_GetScancodeFromKey(sdlKey)] && getData(sdlKey).bToggleState) {
								getData(sdlKey).bToggleState = false;
						}
					}

					void execRepeat(SDL_Keycode sdlKey) {
						if (event[SDL_GetScancodeFromKey(sdlKey)] && !getData(sdlKey).bRepeatState) {
							getData(sdlKey).bActive = true;
							getData(sdlKey).bRepeatState = false;
							if(getData(sdlKey).eKeyType==KEYTYPE_DEBOUNCE) {
								getData(sdlKey).bRepeatState = true;
								repeatTimer.start();
							}
						}
						else if (event[SDL_GetScancodeFromKey(sdlKey)] && getData(sdlKey).bRepeatState /*&& repeatTimer.split()>=50*/) {
							getData(sdlKey).bActive = false;

							if(getData(sdlKey).eKeyType==KEYTYPE_DEBOUNCE) {
								if (repeatTimer.split() >= Core::gameVars->font.iRepeatDebounce) getData(sdlKey).bActive = true;
							}
						}
						else if (!event[SDL_GetScancodeFromKey(sdlKey)]) {
							getData(sdlKey).bActive = false;
							getData(sdlKey).bRepeatState = false;
						}
					}
			};
			_KeyArray keys;
	};

	const Uint8 *_Keyboard::event;

	_Keyboard::_Keyboard() {
		//            .................................................................Done
		std::cout << "Construct Keyboard System........................................";
		event = nullptr;
		std::cout << "Done" << std::endl;
	}

	_Keyboard::~_Keyboard() {
		//            .................................................................Done
		std::cout << "Destroy Keyboard System..........................................";
		std::cout << "Done" << std::endl;
	}

	/** ******************************************************************************************************************************
	 *
	 * @param keyCode
	 * @param eKeyType
	 * ****************************************************************************************************************************** */
	void _Keyboard::AddKey(SDL_Keycode keyCode, KeyType eKeyType) {
		keys.insert(keyCode, eKeyType);
	}

	/** ******************************************************************************************************************************
	 *
	 * @param eKeyType
	 * ****************************************************************************************************************************** */
	void _Keyboard::calc(KeyType eKeyType) {
		// Numbers and Letters
		AddKey(SDLK_0,					eKeyType);
		AddKey(SDLK_1,					eKeyType);
		AddKey(SDLK_2,					eKeyType);
		AddKey(SDLK_3,					eKeyType);
		AddKey(SDLK_4,					eKeyType);
		AddKey(SDLK_5,					eKeyType);
		AddKey(SDLK_6,					eKeyType);
		AddKey(SDLK_7,					eKeyType);
		AddKey(SDLK_8,					eKeyType);
		AddKey(SDLK_9,					eKeyType);
		AddKey(SDLK_a,					eKeyType);
		AddKey(SDLK_b,					eKeyType);
		AddKey(SDLK_c,					eKeyType);
		AddKey(SDLK_d,					eKeyType);
		AddKey(SDLK_e,					eKeyType);
		AddKey(SDLK_f,					eKeyType);
		AddKey(SDLK_g,					eKeyType);
		AddKey(SDLK_h,					eKeyType);
		AddKey(SDLK_i,					eKeyType);
		AddKey(SDLK_j,					eKeyType);
		AddKey(SDLK_k,					eKeyType);
		AddKey(SDLK_l,					eKeyType);
		AddKey(SDLK_m,					eKeyType);
		AddKey(SDLK_n,					eKeyType);
		AddKey(SDLK_o,					eKeyType);
		AddKey(SDLK_p,					eKeyType);
		AddKey(SDLK_q,					eKeyType);
		AddKey(SDLK_r,					eKeyType);
		AddKey(SDLK_s,					eKeyType);
		AddKey(SDLK_t,					eKeyType);
		AddKey(SDLK_u, 					eKeyType);
		AddKey(SDLK_v, 					eKeyType);
		AddKey(SDLK_w,					eKeyType);
		AddKey(SDLK_x,					eKeyType);
		AddKey(SDLK_y,					eKeyType);
		AddKey(SDLK_z,					eKeyType);

		// Function Keys
		AddKey(SDLK_F1,					KEYTYPE_ONESHOT);
		AddKey(SDLK_F2,					KEYTYPE_ONESHOT);
		AddKey(SDLK_F3,					KEYTYPE_ONESHOT);
		AddKey(SDLK_F4,					KEYTYPE_ONESHOT);
		AddKey(SDLK_F5,					KEYTYPE_ONESHOT);
		AddKey(SDLK_F6,					KEYTYPE_ONESHOT);
		AddKey(SDLK_F7,					KEYTYPE_ONESHOT);
		AddKey(SDLK_F8,					KEYTYPE_ONESHOT);
		AddKey(SDLK_F9,					KEYTYPE_ONESHOT);
		AddKey(SDLK_F10,				KEYTYPE_ONESHOT);
		AddKey(SDLK_F11,				KEYTYPE_ONESHOT);
		AddKey(SDLK_F12,				KEYTYPE_ONESHOT);
		AddKey(SDLK_F13,				KEYTYPE_ONESHOT);
		AddKey(SDLK_F14,				KEYTYPE_ONESHOT);
		AddKey(SDLK_F15,				KEYTYPE_ONESHOT);
		AddKey(SDLK_F16,				KEYTYPE_ONESHOT);
		AddKey(SDLK_F17,				KEYTYPE_ONESHOT);
		AddKey(SDLK_F18,				KEYTYPE_ONESHOT);
		AddKey(SDLK_F19,				KEYTYPE_ONESHOT);
		AddKey(SDLK_F20,				KEYTYPE_ONESHOT);
		AddKey(SDLK_F21,				KEYTYPE_ONESHOT);
		AddKey(SDLK_F22,				KEYTYPE_ONESHOT);
		AddKey(SDLK_F23,				KEYTYPE_ONESHOT);
		AddKey(SDLK_F24,				KEYTYPE_ONESHOT);

		// Control/Modifier Keys
		AddKey(SDLK_UP, 				eKeyType);
		AddKey(SDLK_DOWN,				eKeyType);
		AddKey(SDLK_LEFT,				eKeyType);
		AddKey(SDLK_RIGHT,				eKeyType);
		AddKey(SDLK_LALT,				KEYTYPE_REPEAT);
		AddKey(SDLK_RALT,				KEYTYPE_REPEAT);
		AddKey(SDLK_LCTRL,				KEYTYPE_REPEAT);
		AddKey(SDLK_RCTRL,				KEYTYPE_REPEAT);
		AddKey(SDLK_LSHIFT,				KEYTYPE_REPEAT);
		AddKey(SDLK_RSHIFT,				KEYTYPE_REPEAT);
		AddKey(SDLK_HOME,				KEYTYPE_ONESHOT);
		AddKey(SDLK_END,				KEYTYPE_ONESHOT);
		AddKey(SDLK_PAGEUP,				KEYTYPE_ONESHOT);
		AddKey(SDLK_PAGEDOWN,			KEYTYPE_ONESHOT);
		AddKey(SDLK_ESCAPE,				KEYTYPE_ONESHOT);
		AddKey(SDLK_RETURN,				KEYTYPE_ONESHOT);
		AddKey(SDLK_TAB,				KEYTYPE_ONESHOT);
		AddKey(SDLK_CAPSLOCK,			KEYTYPE_TOGGLE);
		AddKey(SDLK_INSERT,				KEYTYPE_TOGGLE);
		AddKey(SDLK_PRINTSCREEN,		KEYTYPE_TOGGLE);
		AddKey(SDLK_SCROLLLOCK,			KEYTYPE_TOGGLE);
		AddKey(SDLK_DELETE,				KEYTYPE_ONESHOT);
		AddKey(SDLK_BACKSPACE,			KEYTYPE_ONESHOT);

		// Special Keys
		AddKey(SDLK_QUOTE,				eKeyType);
		AddKey(SDLK_BACKSLASH,			eKeyType);
		AddKey(SDLK_COMMA,				eKeyType);
		AddKey(SDLK_EQUALS,				eKeyType);
		AddKey(SDLK_LEFTBRACKET,		eKeyType);
		AddKey(SDLK_MINUS,				eKeyType);
		AddKey(SDLK_PERIOD,				eKeyType);
		AddKey(SDLK_RIGHTBRACKET,		eKeyType);
		AddKey(SDLK_SEMICOLON,			eKeyType);
		AddKey(SDLK_SLASH,				eKeyType);
		AddKey(SDLK_SPACE,				eKeyType);
		AddKey(SDLK_AMPERSAND,			KEYTYPE_ONESHOT);
		AddKey(SDLK_ASTERISK,			KEYTYPE_ONESHOT);
		AddKey(SDLK_AT,					KEYTYPE_ONESHOT);
		AddKey(SDLK_CARET,				KEYTYPE_ONESHOT);
		AddKey(SDLK_COLON,				KEYTYPE_ONESHOT);
		AddKey(SDLK_DOLLAR,				KEYTYPE_ONESHOT);
		AddKey(SDLK_EXCLAIM,			KEYTYPE_ONESHOT);
		AddKey(SDLK_GREATER,			KEYTYPE_ONESHOT);
		AddKey(SDLK_HASH,				KEYTYPE_ONESHOT);
		AddKey(SDLK_LEFTPAREN,			KEYTYPE_ONESHOT);
		AddKey(SDLK_LESS,				KEYTYPE_ONESHOT);
		AddKey(SDLK_PERCENT,			KEYTYPE_ONESHOT);
		AddKey(SDLK_PLUS,				KEYTYPE_ONESHOT);
		AddKey(SDLK_QUESTION,			KEYTYPE_ONESHOT);
		AddKey(SDLK_QUOTEDBL,			KEYTYPE_ONESHOT);
		AddKey(SDLK_RIGHTPAREN,			KEYTYPE_ONESHOT);
		AddKey(SDLK_UNDERSCORE,			KEYTYPE_ONESHOT);
		AddKey(SDLK_BACKQUOTE,			KEYTYPE_REPEAT);

		// Keypad
		AddKey(SDLK_KP_0,				eKeyType);
		AddKey(SDLK_KP_1,				eKeyType);
		AddKey(SDLK_KP_2,				eKeyType);
		AddKey(SDLK_KP_3,				eKeyType);
		AddKey(SDLK_KP_4,				eKeyType);
		AddKey(SDLK_KP_5,				eKeyType);
		AddKey(SDLK_KP_6,				eKeyType);
		AddKey(SDLK_KP_7,				eKeyType);
		AddKey(SDLK_KP_8,				eKeyType);
		AddKey(SDLK_KP_9,				eKeyType);
		AddKey(SDLK_KP_DIVIDE,			eKeyType);
		AddKey(SDLK_KP_ENTER,			eKeyType);
		AddKey(SDLK_KP_MINUS,			eKeyType);
		AddKey(SDLK_KP_MULTIPLY,		eKeyType);
		AddKey(SDLK_KP_PERIOD,			eKeyType);
		AddKey(SDLK_KP_PLUS,			eKeyType);

		// Unused Keys
		AddKey(SDLK_AC_BACK,			KEYTYPE_ONESHOT);
		AddKey(SDLK_AC_BOOKMARKS,		KEYTYPE_ONESHOT);
		AddKey(SDLK_AC_FORWARD,			KEYTYPE_ONESHOT);
		AddKey(SDLK_AC_HOME,			KEYTYPE_ONESHOT);
		AddKey(SDLK_AC_REFRESH,			KEYTYPE_ONESHOT);
		AddKey(SDLK_AC_SEARCH,			KEYTYPE_ONESHOT);
		AddKey(SDLK_AC_STOP,			KEYTYPE_ONESHOT);
		AddKey(SDLK_AGAIN,				KEYTYPE_ONESHOT);
		AddKey(SDLK_ALTERASE,			KEYTYPE_ONESHOT);
		AddKey(SDLK_APPLICATION,		KEYTYPE_ONESHOT);
		AddKey(SDLK_AUDIOMUTE,			KEYTYPE_ONESHOT);
		AddKey(SDLK_AUDIONEXT,			KEYTYPE_ONESHOT);
		AddKey(SDLK_AUDIOPLAY,			KEYTYPE_ONESHOT);
		AddKey(SDLK_AUDIOPREV,			KEYTYPE_ONESHOT);
		AddKey(SDLK_AUDIOSTOP,			KEYTYPE_ONESHOT);
		AddKey(SDLK_BRIGHTNESSDOWN,		KEYTYPE_ONESHOT);
		AddKey(SDLK_BRIGHTNESSUP,		KEYTYPE_ONESHOT);
		AddKey(SDLK_CALCULATOR,			KEYTYPE_ONESHOT);
		AddKey(SDLK_CANCEL,				KEYTYPE_ONESHOT);
		AddKey(SDLK_CLEAR,				KEYTYPE_ONESHOT);
		AddKey(SDLK_CLEARAGAIN,			KEYTYPE_ONESHOT);
		AddKey(SDLK_COMPUTER,			KEYTYPE_ONESHOT);
		AddKey(SDLK_COPY,				KEYTYPE_ONESHOT);
		AddKey(SDLK_CRSEL,				KEYTYPE_ONESHOT);
		AddKey(SDLK_CURRENCYSUBUNIT,	KEYTYPE_ONESHOT);
		AddKey(SDLK_CURRENCYUNIT,		KEYTYPE_ONESHOT);
		AddKey(SDLK_CUT,				KEYTYPE_ONESHOT);
		AddKey(SDLK_DECIMALSEPARATOR,	KEYTYPE_ONESHOT);
		AddKey(SDLK_DISPLAYSWITCH,		KEYTYPE_ONESHOT);
		AddKey(SDLK_EJECT,				KEYTYPE_ONESHOT);
		AddKey(SDLK_EXECUTE,			KEYTYPE_ONESHOT);
		AddKey(SDLK_EXSEL,				KEYTYPE_ONESHOT);
		AddKey(SDLK_FIND,				KEYTYPE_ONESHOT);
		AddKey(SDLK_HELP,				KEYTYPE_ONESHOT);
		AddKey(SDLK_KBDILLUMDOWN,		KEYTYPE_ONESHOT);
		AddKey(SDLK_KBDILLUMTOGGLE,		KEYTYPE_ONESHOT);
		AddKey(SDLK_KBDILLUMUP,			KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_00,				KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_000,				KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_A,				KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_AMPERSAND,		KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_AT,				KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_B,				KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_BACKSPACE,		KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_BINARY,			KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_C,				KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_CLEAR,			KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_CLEARENTRY,		KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_COLON,			KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_COMMA,			KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_D,				KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_DBLAMPERSAND,	KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_DBLVERTICALBAR,	KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_DECIMAL,			KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_E,				KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_EQUALS,			KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_EQUALSAS400,		KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_EXCLAM,			KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_F,				KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_GREATER,			KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_HASH,			KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_HEXADECIMAL,		KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_LEFTBRACE,		KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_LEFTPAREN,		KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_LESS,			KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_MEMADD,			KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_MEMCLEAR,		KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_MEMDIVIDE,		KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_MEMMULTIPLY,		KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_MEMRECALL,		KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_MEMSTORE,		KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_MEMSUBTRACT,		KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_OCTAL,			KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_PERCENT,			KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_PLUSMINUS,		KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_POWER,			KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_RIGHTBRACE,		KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_RIGHTPAREN,		KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_SPACE,			KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_TAB,				KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_VERTICALBAR,		KEYTYPE_ONESHOT);
		AddKey(SDLK_KP_XOR,				KEYTYPE_ONESHOT);
		AddKey(SDLK_LGUI,				KEYTYPE_ONESHOT);
		AddKey(SDLK_MAIL,				KEYTYPE_ONESHOT);
		AddKey(SDLK_MEDIASELECT,		KEYTYPE_ONESHOT);
		AddKey(SDLK_MENU,				KEYTYPE_ONESHOT);
		AddKey(SDLK_MODE,				KEYTYPE_ONESHOT);
		AddKey(SDLK_MUTE,				KEYTYPE_ONESHOT);
		AddKey(SDLK_NUMLOCKCLEAR,		KEYTYPE_ONESHOT);
		AddKey(SDLK_OPER,				KEYTYPE_ONESHOT);
		AddKey(SDLK_OUT,				KEYTYPE_ONESHOT);
		AddKey(SDLK_PASTE,				KEYTYPE_ONESHOT);
		AddKey(SDLK_PAUSE,				KEYTYPE_ONESHOT);
		AddKey(SDLK_POWER,				KEYTYPE_ONESHOT);
		AddKey(SDLK_PRIOR,				KEYTYPE_ONESHOT);
		AddKey(SDLK_RETURN2,			KEYTYPE_ONESHOT);
		AddKey(SDLK_RGUI,				KEYTYPE_ONESHOT);
		AddKey(SDLK_SELECT,				KEYTYPE_ONESHOT);
		AddKey(SDLK_SEPARATOR,			KEYTYPE_ONESHOT);
		AddKey(SDLK_SLEEP,				KEYTYPE_ONESHOT);
		AddKey(SDLK_STOP,				KEYTYPE_ONESHOT);
		AddKey(SDLK_SYSREQ,				KEYTYPE_ONESHOT);
		AddKey(SDLK_THOUSANDSSEPARATOR,	KEYTYPE_ONESHOT);
		AddKey(SDLK_UNDO, 				KEYTYPE_ONESHOT);
		AddKey(SDLK_UNKNOWN, 			KEYTYPE_ONESHOT);
		AddKey(SDLK_VOLUMEDOWN,			KEYTYPE_ONESHOT);
		AddKey(SDLK_VOLUMEUP,			KEYTYPE_ONESHOT);
		AddKey(SDLK_WWW,				KEYTYPE_ONESHOT);
	}

	void _Keyboard::calc(SDL_Keycode iKey, KeyType eKeyType) {
		keys[iKey].eKeyType = eKeyType;
	}

	/** ********************************************************************************************************************************
	 * \brief Simple editing mode for a buffer. Used for fields of numeric and text types
	 * @param buffer Text to be edited
	 * @param bNumeric Numeric editing only
	 *
	 * Thus function allows a buffer to be edited but has no cursor position. It will edit
	 * from the end of the string only. In numeric mode the + and - keys can be used to
	 * toggle the sign state without erasing the entire buffer. The DEL key can be used
	 * to clear the buffer completely.
	 * ******************************************************************************************************************************* */
	void _Keyboard::editBuffer(std::string &buffer, int flags) {
		if(flags&EDIT_DELETE) {
			if (keys[SDLK_BACKSPACE].bActive) {
				if (buffer.length()>0) {
					buffer.erase(buffer.length()-1, 1);
				}
			}

			if (keys[SDLK_DELETE].bActive) {
				if (buffer.length()>0) {
					buffer = "";
				}
			}
		}

		if(flags&EDIT_WRITE) {
			bool bShift = keys[SDLK_LSHIFT].bActive || keys[SDLK_RSHIFT].bActive;

			if (!(flags&EDIT_NUMERIC)) {
				if (keys[SDLK_SPACE].bActive) buffer.push_back(' ');
				if (bShift) {
					if (keys[SDLK_a].bActive) buffer.push_back('A');
					if (keys[SDLK_b].bActive) buffer.push_back('B');
					if (keys[SDLK_c].bActive) buffer.push_back('C');
					if (keys[SDLK_d].bActive) buffer.push_back('D');
					if (keys[SDLK_e].bActive) buffer.push_back('E');
					if (keys[SDLK_f].bActive) buffer.push_back('F');
					if (keys[SDLK_g].bActive) buffer.push_back('G');
					if (keys[SDLK_h].bActive) buffer.push_back('H');
					if (keys[SDLK_i].bActive) buffer.push_back('I');
					if (keys[SDLK_j].bActive) buffer.push_back('J');
					if (keys[SDLK_k].bActive) buffer.push_back('K');
					if (keys[SDLK_l].bActive) buffer.push_back('L');
					if (keys[SDLK_m].bActive) buffer.push_back('M');
					if (keys[SDLK_n].bActive) buffer.push_back('N');
					if (keys[SDLK_o].bActive) buffer.push_back('O');
					if (keys[SDLK_p].bActive) buffer.push_back('P');
					if (keys[SDLK_q].bActive) buffer.push_back('Q');
					if (keys[SDLK_r].bActive) buffer.push_back('R');
					if (keys[SDLK_s].bActive) buffer.push_back('S');
					if (keys[SDLK_t].bActive) buffer.push_back('T');
					if (keys[SDLK_u].bActive) buffer.push_back('U');
					if (keys[SDLK_v].bActive) buffer.push_back('V');
					if (keys[SDLK_w].bActive) buffer.push_back('W');
					if (keys[SDLK_x].bActive) buffer.push_back('X');
					if (keys[SDLK_y].bActive) buffer.push_back('Y');
					if (keys[SDLK_z].bActive) buffer.push_back('Z');
				}
				else {
					if (keys[SDLK_a].bActive) buffer.push_back('a');
					if (keys[SDLK_b].bActive) buffer.push_back('b');
					if (keys[SDLK_c].bActive) buffer.push_back('c');
					if (keys[SDLK_d].bActive) buffer.push_back('d');
					if (keys[SDLK_e].bActive) buffer.push_back('e');
					if (keys[SDLK_f].bActive) buffer.push_back('f');
					if (keys[SDLK_g].bActive) buffer.push_back('g');
					if (keys[SDLK_h].bActive) buffer.push_back('h');
					if (keys[SDLK_i].bActive) buffer.push_back('i');
					if (keys[SDLK_j].bActive) buffer.push_back('j');
					if (keys[SDLK_k].bActive) buffer.push_back('k');
					if (keys[SDLK_l].bActive) buffer.push_back('l');
					if (keys[SDLK_m].bActive) buffer.push_back('m');
					if (keys[SDLK_n].bActive) buffer.push_back('n');
					if (keys[SDLK_o].bActive) buffer.push_back('o');
					if (keys[SDLK_p].bActive) buffer.push_back('p');
					if (keys[SDLK_q].bActive) buffer.push_back('q');
					if (keys[SDLK_r].bActive) buffer.push_back('r');
					if (keys[SDLK_s].bActive) buffer.push_back('s');
					if (keys[SDLK_t].bActive) buffer.push_back('t');
					if (keys[SDLK_u].bActive) buffer.push_back('u');
					if (keys[SDLK_v].bActive) buffer.push_back('v');
					if (keys[SDLK_w].bActive) buffer.push_back('w');
					if (keys[SDLK_x].bActive) buffer.push_back('x');
					if (keys[SDLK_y].bActive) buffer.push_back('y');
					if (keys[SDLK_z].bActive) buffer.push_back('z');
				}
			}

			/*
			 * Keypad is always in numeric mode
			 */
			if(bShift && !(flags&EDIT_NUMERIC)) {
				if (keys[SDLK_1].bActive) buffer.push_back('!');
				if (keys[SDLK_2].bActive) buffer.push_back('@');
				if (keys[SDLK_3].bActive) buffer.push_back('#');
				if (keys[SDLK_4].bActive) buffer.push_back('$');
				if (keys[SDLK_5].bActive) buffer.push_back('%');
				if (keys[SDLK_6].bActive) buffer.push_back('^');
				if (keys[SDLK_7].bActive) buffer.push_back('&');
				if (keys[SDLK_8].bActive || keys[SDLK_KP_MULTIPLY].bActive) buffer.push_back('*');
				if (keys[SDLK_9].bActive) buffer.push_back('(');
				if (keys[SDLK_0].bActive) buffer.push_back(')');
				if (keys[SDLK_MINUS].bActive) buffer.push_back('_');
				if (keys[SDLK_EQUALS].bActive || keys[SDLK_KP_PLUS].bActive) buffer.push_back('+');
				if (keys[SDLK_LEFTBRACKET].bActive) buffer.push_back('{');
				if (keys[SDLK_RIGHTBRACKET].bActive) buffer.push_back('}');
				if (keys[SDLK_SLASH].bActive) buffer.push_back('?');
				if (keys[SDLK_SEMICOLON].bActive) buffer.push_back(':');
				if (keys[SDLK_QUOTE].bActive) buffer.push_back('"');
				if (keys[SDLK_COMMA].bActive) buffer.push_back('<');
				if (keys[SDLK_PERIOD].bActive) buffer.push_back('>');
				if (keys[SDLK_BACKSLASH].bActive) buffer.push_back('|');
			}
			else {
				if (keys[SDLK_1].bActive || keys[SDLK_KP_1].bActive) buffer.push_back('1');
				if (keys[SDLK_2].bActive || keys[SDLK_KP_2].bActive) buffer.push_back('2');
				if (keys[SDLK_3].bActive || keys[SDLK_KP_3].bActive) buffer.push_back('3');
				if (keys[SDLK_4].bActive || keys[SDLK_KP_4].bActive) buffer.push_back('4');
				if (keys[SDLK_5].bActive || keys[SDLK_KP_5].bActive) buffer.push_back('5');
				if (keys[SDLK_6].bActive || keys[SDLK_KP_6].bActive) buffer.push_back('6');
				if (keys[SDLK_7].bActive || keys[SDLK_KP_7].bActive) buffer.push_back('7');
				if (keys[SDLK_8].bActive || keys[SDLK_KP_8].bActive) buffer.push_back('8');
				if (keys[SDLK_9].bActive || keys[SDLK_KP_9].bActive) buffer.push_back('9');
				if (keys[SDLK_0].bActive || keys[SDLK_KP_0].bActive) buffer.push_back('0');
				if (keys[SDLK_PERIOD].bActive || keys[SDLK_KP_PERIOD].bActive) buffer.push_back('.');
				if(!(flags&EDIT_NUMERIC)) {
					if (keys[SDLK_MINUS].bActive || keys[SDLK_KP_MINUS].bActive) buffer.push_back('-');
					if (keys[SDLK_EQUALS].bActive) buffer.push_back('=');
					if (keys[SDLK_LEFTBRACKET].bActive) buffer.push_back('[');
					if (keys[SDLK_RIGHTBRACKET].bActive) buffer.push_back(']');
					if (keys[SDLK_SLASH].bActive || keys[SDLK_KP_DIVIDE].bActive) buffer.push_back('/');
					if (keys[SDLK_SEMICOLON].bActive) buffer.push_back(';');
					if (keys[SDLK_QUOTE].bActive) buffer.push_back('\'');
					if (keys[SDLK_COMMA].bActive) buffer.push_back(',');
					if (keys[SDLK_BACKSLASH].bActive) buffer.push_back('\\');

					// Keypad specific duplicates
					if (keys[SDLK_KP_PLUS].bActive) buffer.push_back('+');
					if (keys[SDLK_KP_MULTIPLY].bActive) buffer.push_back('*');
				}
				else {
					/*
					 * Special handling of +/- for numeric entry
					 */
					if (keys[SDLK_MINUS].bActive || keys[SDLK_KP_MINUS].bActive) {
						if(buffer.length()>0) {
							if(buffer[0]!='-') buffer = "-"+buffer;
						}
						else buffer = "-";
					}
					if (keys[SDLK_EQUALS].bActive || keys[SDLK_KP_PLUS].bActive) {
						if(buffer.length()>0) {
							if(buffer[0]=='-') buffer.replace(0, 1, "");
						}
					}
				}
			}
		}

	}

	/** ******************************************************************************************************************************
	 * \brief Insert or \p bOverwrite character at \p cursorPos with give \p cChar
	 *
	 * @param buffer
	 * @param cursorPos
	 * @param cChar
	 * @param bOverwrite
	 * ****************************************************************************************************************************** */
//	void _Keyboard::insertBufferAt(std::string &buffer, int *cursorPos, char cChar, bool bOverwrite) {
//		buffer.insert(*cursorPos, 1, cChar);
//		*cursorPos+=1;
//	}

	void _Keyboard::insertBufferAt(std::shared_ptr<std::string> &buffer, int *cursorPos, char cChar, bool bOverwrite) {
		buffer->insert(*cursorPos, 1, cChar);
		*cursorPos+=1;
	}

	/** ********************************************************************************************************************************
	 * \brief Edit a buffer at a specific position indicated by \p index
	 *
	 * @param buffer Text to be edited
	 * @param bNumeric Numeric editing only
	 * @param cursorPos Cursor position, location to edit text at
	 * @param bOverwrite Whether to overwrite text at position or insert
	 *
	 * More advanced text editing function that allows editing at a cursor
	 * position either in insert or overwrite mode. Can still be specified
	 * as numeric only with the - and + keys used to toggle the sign of the
	 * value. DEL erases the entire buffer in Numeric mode only, in text
	 * mode it will erase the character AFTER the current cursor position.
	 *
	 * ******************************************************************************************************************************** */
//	void _Keyboard::editBufferAt(std::string &buffer, bool bNumeric, int *cursorPos, bool bOverwrite) {

	// FIXME: Add editing flags instead of multi-bools
	void _Keyboard::editBufferAt(std::shared_ptr<std::string> &buffer, bool bNumeric, int *cursorPos, bool bOverwrite) {
		if (keys[SDLK_BACKSPACE].bActive) {
			if(buffer->length()>0) {
				if(bNumeric)	buffer->erase(buffer->length()-1, 1);
				else {
					buffer->erase(*cursorPos-1, 1);
					*cursorPos-=1;
				}
			}
		}

		// FIXME: See definition above
		if (keys[SDLK_DELETE].bActive) {
			if(buffer->length()>0) {
				if(bNumeric)	*buffer = "";
				else			buffer->erase(*cursorPos, 1);
			}
		}

		bool bShift = keys[SDLK_LSHIFT].bActive || keys[SDLK_RSHIFT].bActive;

		if(bOverwrite) {
			if (!bNumeric) {
				if (keys[SDLK_SPACE].bActive) { (*buffer)[*cursorPos] = ' '; *cursorPos+=1; }
				if (bShift) {
					if (keys[SDLK_a].bActive) { (*buffer)[*cursorPos] = 'A'; *cursorPos+=1; }
					if (keys[SDLK_b].bActive) { (*buffer)[*cursorPos] = 'B'; *cursorPos+=1; }
					if (keys[SDLK_c].bActive) { (*buffer)[*cursorPos] = 'C'; *cursorPos+=1; }
					if (keys[SDLK_d].bActive) { (*buffer)[*cursorPos] = 'D'; *cursorPos+=1; }
					if (keys[SDLK_e].bActive) { (*buffer)[*cursorPos] = 'E'; *cursorPos+=1; }
					if (keys[SDLK_f].bActive) { (*buffer)[*cursorPos] = 'F'; *cursorPos+=1; }
					if (keys[SDLK_g].bActive) { (*buffer)[*cursorPos] = 'G'; *cursorPos+=1; }
					if (keys[SDLK_h].bActive) { (*buffer)[*cursorPos] = 'H'; *cursorPos+=1; }
					if (keys[SDLK_i].bActive) { (*buffer)[*cursorPos] = 'I'; *cursorPos+=1; }
					if (keys[SDLK_j].bActive) { (*buffer)[*cursorPos] = 'J'; *cursorPos+=1; }
					if (keys[SDLK_k].bActive) { (*buffer)[*cursorPos] = 'K'; *cursorPos+=1; }
					if (keys[SDLK_l].bActive) { (*buffer)[*cursorPos] = 'L'; *cursorPos+=1; }
					if (keys[SDLK_m].bActive) { (*buffer)[*cursorPos] = 'M'; *cursorPos+=1; }
					if (keys[SDLK_n].bActive) { (*buffer)[*cursorPos] = 'N'; *cursorPos+=1; }
					if (keys[SDLK_o].bActive) { (*buffer)[*cursorPos] = 'O'; *cursorPos+=1; }
					if (keys[SDLK_p].bActive) { (*buffer)[*cursorPos] = 'P'; *cursorPos+=1; }
					if (keys[SDLK_q].bActive) { (*buffer)[*cursorPos] = 'Q'; *cursorPos+=1; }
					if (keys[SDLK_r].bActive) { (*buffer)[*cursorPos] = 'R'; *cursorPos+=1; }
					if (keys[SDLK_s].bActive) { (*buffer)[*cursorPos] = 'S'; *cursorPos+=1; }
					if (keys[SDLK_t].bActive) { (*buffer)[*cursorPos] = 'T'; *cursorPos+=1; }
					if (keys[SDLK_u].bActive) { (*buffer)[*cursorPos] = 'U'; *cursorPos+=1; }
					if (keys[SDLK_v].bActive) { (*buffer)[*cursorPos] = 'V'; *cursorPos+=1; }
					if (keys[SDLK_w].bActive) { (*buffer)[*cursorPos] = 'W'; *cursorPos+=1; }
					if (keys[SDLK_x].bActive) { (*buffer)[*cursorPos] = 'X'; *cursorPos+=1; }
					if (keys[SDLK_y].bActive) { (*buffer)[*cursorPos] = 'Y'; *cursorPos+=1; }
					if (keys[SDLK_z].bActive) { (*buffer)[*cursorPos] = 'Z'; *cursorPos+=1; }
				}
				else {
					if (keys[SDLK_a].bActive) { (*buffer)[*cursorPos] = 'a'; *cursorPos+=1; }
					if (keys[SDLK_b].bActive) { (*buffer)[*cursorPos] = 'b'; *cursorPos+=1; }
					if (keys[SDLK_c].bActive) { (*buffer)[*cursorPos] = 'c'; *cursorPos+=1; }
					if (keys[SDLK_d].bActive) { (*buffer)[*cursorPos] = 'd'; *cursorPos+=1; }
					if (keys[SDLK_e].bActive) { (*buffer)[*cursorPos] = 'e'; *cursorPos+=1; }
					if (keys[SDLK_f].bActive) { (*buffer)[*cursorPos] = 'f'; *cursorPos+=1; }
					if (keys[SDLK_g].bActive) { (*buffer)[*cursorPos] = 'g'; *cursorPos+=1; }
					if (keys[SDLK_h].bActive) { (*buffer)[*cursorPos] = 'h'; *cursorPos+=1; }
					if (keys[SDLK_i].bActive) { (*buffer)[*cursorPos] = 'i'; *cursorPos+=1; }
					if (keys[SDLK_j].bActive) { (*buffer)[*cursorPos] = 'j'; *cursorPos+=1; }
					if (keys[SDLK_k].bActive) { (*buffer)[*cursorPos] = 'k'; *cursorPos+=1; }
					if (keys[SDLK_l].bActive) { (*buffer)[*cursorPos] = 'l'; *cursorPos+=1; }
					if (keys[SDLK_m].bActive) { (*buffer)[*cursorPos] = 'm'; *cursorPos+=1; }
					if (keys[SDLK_n].bActive) { (*buffer)[*cursorPos] = 'n'; *cursorPos+=1; }
					if (keys[SDLK_o].bActive) { (*buffer)[*cursorPos] = 'o'; *cursorPos+=1; }
					if (keys[SDLK_p].bActive) { (*buffer)[*cursorPos] = 'p'; *cursorPos+=1; }
					if (keys[SDLK_q].bActive) { (*buffer)[*cursorPos] = 'q'; *cursorPos+=1; }
					if (keys[SDLK_r].bActive) { (*buffer)[*cursorPos] = 'r'; *cursorPos+=1; }
					if (keys[SDLK_s].bActive) { (*buffer)[*cursorPos] = 's'; *cursorPos+=1; }
					if (keys[SDLK_t].bActive) { (*buffer)[*cursorPos] = 't'; *cursorPos+=1; }
					if (keys[SDLK_u].bActive) { (*buffer)[*cursorPos] = 'u'; *cursorPos+=1; }
					if (keys[SDLK_v].bActive) { (*buffer)[*cursorPos] = 'v'; *cursorPos+=1; }
					if (keys[SDLK_w].bActive) { (*buffer)[*cursorPos] = 'w'; *cursorPos+=1; }
					if (keys[SDLK_x].bActive) { (*buffer)[*cursorPos] = 'x'; *cursorPos+=1; }
					if (keys[SDLK_y].bActive) { (*buffer)[*cursorPos] = 'y'; *cursorPos+=1; }
					if (keys[SDLK_z].bActive) { (*buffer)[*cursorPos] = 'z'; *cursorPos+=1; }
				}
			}

			/*
			 * Keypad is always in numeric mode
			 */
			if(bShift && !bNumeric) {
				if (keys[SDLK_1].bActive) { (*buffer)[*cursorPos] = '!'; *cursorPos+=1; }
				if (keys[SDLK_2].bActive) { (*buffer)[*cursorPos] = '@'; *cursorPos+=1; }
				if (keys[SDLK_3].bActive) { (*buffer)[*cursorPos] = '#'; *cursorPos+=1; }
				if (keys[SDLK_4].bActive) { (*buffer)[*cursorPos] = '$'; *cursorPos+=1; }
				if (keys[SDLK_5].bActive) { (*buffer)[*cursorPos] = '%'; *cursorPos+=1; }
				if (keys[SDLK_6].bActive) { (*buffer)[*cursorPos] = '^'; *cursorPos+=1; }
				if (keys[SDLK_7].bActive) { (*buffer)[*cursorPos] = '&'; *cursorPos+=1; }
				if (keys[SDLK_8].bActive || keys[SDLK_KP_MULTIPLY].bActive) { (*buffer)[*cursorPos] = '*'; *cursorPos+=1; }
				if (keys[SDLK_9].bActive) { (*buffer)[*cursorPos] = '('; *cursorPos+=1; }
				if (keys[SDLK_0].bActive) { (*buffer)[*cursorPos] = ')'; *cursorPos+=1; }
				if (keys[SDLK_MINUS].bActive) { (*buffer)[*cursorPos] = '_'; *cursorPos+=1; }
				if (keys[SDLK_EQUALS].bActive || keys[SDLK_KP_PLUS].bActive) { (*buffer)[*cursorPos] = '+'; *cursorPos+=1; }
				if (keys[SDLK_LEFTBRACKET].bActive) { (*buffer)[*cursorPos] = '{'; *cursorPos+=1; }
				if (keys[SDLK_RIGHTBRACKET].bActive) { (*buffer)[*cursorPos] = '}'; *cursorPos+=1; }
				if (keys[SDLK_SLASH].bActive) { (*buffer)[*cursorPos] = '?'; *cursorPos+=1; }
				if (keys[SDLK_SEMICOLON].bActive) { (*buffer)[*cursorPos] = ':'; *cursorPos+=1; }
				if (keys[SDLK_QUOTE].bActive) { (*buffer)[*cursorPos] = '"'; *cursorPos+=1; }
				if (keys[SDLK_COMMA].bActive) { (*buffer)[*cursorPos] = '<'; *cursorPos+=1; }
				if (keys[SDLK_PERIOD].bActive) { (*buffer)[*cursorPos] = '>'; *cursorPos+=1; }
				if (keys[SDLK_BACKSLASH].bActive) { (*buffer)[*cursorPos] = '|'; *cursorPos+=1; }
			}
			else {
				if (keys[SDLK_1].bActive || keys[SDLK_KP_1].bActive) { (*buffer)[*cursorPos] = '1'; *cursorPos+=1; }
				if (keys[SDLK_2].bActive || keys[SDLK_KP_2].bActive) { (*buffer)[*cursorPos] = '2'; *cursorPos+=1; }
				if (keys[SDLK_3].bActive || keys[SDLK_KP_3].bActive) { (*buffer)[*cursorPos] = '3'; *cursorPos+=1; }
				if (keys[SDLK_4].bActive || keys[SDLK_KP_4].bActive) { (*buffer)[*cursorPos] = '4'; *cursorPos+=1; }
				if (keys[SDLK_5].bActive || keys[SDLK_KP_5].bActive) { (*buffer)[*cursorPos] = '5'; *cursorPos+=1; }
				if (keys[SDLK_6].bActive || keys[SDLK_KP_6].bActive) { (*buffer)[*cursorPos] = '6'; *cursorPos+=1; }
				if (keys[SDLK_7].bActive || keys[SDLK_KP_7].bActive) { (*buffer)[*cursorPos] = '7'; *cursorPos+=1; }
				if (keys[SDLK_8].bActive || keys[SDLK_KP_8].bActive) { (*buffer)[*cursorPos] = '8'; *cursorPos+=1; }
				if (keys[SDLK_9].bActive || keys[SDLK_KP_9].bActive) { (*buffer)[*cursorPos] = '9'; *cursorPos+=1; }
				if (keys[SDLK_0].bActive || keys[SDLK_KP_0].bActive) { (*buffer)[*cursorPos] = '0'; *cursorPos+=1; }
				if (keys[SDLK_PERIOD].bActive || keys[SDLK_KP_PERIOD].bActive) { (*buffer)[*cursorPos] = '.'; *cursorPos+=1; }
				if(!bNumeric) {
					if (keys[SDLK_MINUS].bActive || keys[SDLK_KP_MINUS].bActive) { (*buffer)[*cursorPos] = '-'; *cursorPos+=1; }
					if (keys[SDLK_EQUALS].bActive) { (*buffer)[*cursorPos] = '='; *cursorPos+=1; }
					if (keys[SDLK_LEFTBRACKET].bActive) { (*buffer)[*cursorPos] = '['; *cursorPos+=1; }
					if (keys[SDLK_RIGHTBRACKET].bActive) { (*buffer)[*cursorPos] = ']'; *cursorPos+=1; }
					if (keys[SDLK_SLASH].bActive || keys[SDLK_KP_DIVIDE].bActive) { (*buffer)[*cursorPos] = '/'; *cursorPos+=1; }
					if (keys[SDLK_SEMICOLON].bActive) { (*buffer)[*cursorPos] = ';'; *cursorPos+=1; }
					if (keys[SDLK_QUOTE].bActive) { (*buffer)[*cursorPos] = '\''; *cursorPos+=1; }
					if (keys[SDLK_COMMA].bActive) { (*buffer)[*cursorPos] = ','; *cursorPos+=1; }
					if (keys[SDLK_BACKSLASH].bActive) { (*buffer)[*cursorPos] = '\\'; *cursorPos+=1; }

					// Keypad specific duplicates
					if (keys[SDLK_KP_PLUS].bActive) { (*buffer)[*cursorPos] = '+'; *cursorPos+=1; }
					if (keys[SDLK_KP_MULTIPLY].bActive) { (*buffer)[*cursorPos] = '*'; *cursorPos+=1; }
				}
				else {
					/*
					 * Special handling of +/- for numeric entry
					 */
					if (keys[SDLK_MINUS].bActive || keys[SDLK_KP_MINUS].bActive) {
						if(buffer->length()>0) {
							if((*buffer)[0]!='-') (*buffer) = "-"+(*buffer);
						}
						else (*buffer) = "-";
					}
					if (keys[SDLK_EQUALS].bActive || keys[SDLK_KP_PLUS].bActive) {
						if(buffer->length()>0) {
							if((*buffer)[0]=='-') buffer->replace(0, 1, "");
						}
					}
				}
			}
		}
		else {
			if (!bNumeric) {
				if (keys[SDLK_SPACE].bActive) { buffer->insert(*cursorPos, 1, ' '); *cursorPos+=1; }
				if (bShift) {
					if (keys[SDLK_a].bActive) { buffer->insert(*cursorPos, 1, 'A'); *cursorPos+=1; }
					if (keys[SDLK_b].bActive) { buffer->insert(*cursorPos, 1, 'B'); *cursorPos+=1; }
					if (keys[SDLK_c].bActive) { buffer->insert(*cursorPos, 1, 'C'); *cursorPos+=1; }
					if (keys[SDLK_d].bActive) { buffer->insert(*cursorPos, 1, 'D'); *cursorPos+=1; }
					if (keys[SDLK_e].bActive) { buffer->insert(*cursorPos, 1, 'E'); *cursorPos+=1; }
					if (keys[SDLK_f].bActive) { buffer->insert(*cursorPos, 1, 'F'); *cursorPos+=1; }
					if (keys[SDLK_g].bActive) { buffer->insert(*cursorPos, 1, 'G'); *cursorPos+=1; }
					if (keys[SDLK_h].bActive) { buffer->insert(*cursorPos, 1, 'H'); *cursorPos+=1; }
					if (keys[SDLK_i].bActive) { buffer->insert(*cursorPos, 1, 'I'); *cursorPos+=1; }
					if (keys[SDLK_j].bActive) { buffer->insert(*cursorPos, 1, 'J'); *cursorPos+=1; }
					if (keys[SDLK_k].bActive) { buffer->insert(*cursorPos, 1, 'K'); *cursorPos+=1; }
					if (keys[SDLK_l].bActive) { buffer->insert(*cursorPos, 1, 'L'); *cursorPos+=1; }
					if (keys[SDLK_m].bActive) { buffer->insert(*cursorPos, 1, 'M'); *cursorPos+=1; }
					if (keys[SDLK_n].bActive) { buffer->insert(*cursorPos, 1, 'N'); *cursorPos+=1; }
					if (keys[SDLK_o].bActive) { buffer->insert(*cursorPos, 1, 'O'); *cursorPos+=1; }
					if (keys[SDLK_p].bActive) { buffer->insert(*cursorPos, 1, 'P'); *cursorPos+=1; }
					if (keys[SDLK_q].bActive) { buffer->insert(*cursorPos, 1, 'Q'); *cursorPos+=1; }
					if (keys[SDLK_r].bActive) { buffer->insert(*cursorPos, 1, 'R'); *cursorPos+=1; }
					if (keys[SDLK_s].bActive) { buffer->insert(*cursorPos, 1, 'S'); *cursorPos+=1; }
					if (keys[SDLK_t].bActive) { buffer->insert(*cursorPos, 1, 'T'); *cursorPos+=1; }
					if (keys[SDLK_u].bActive) { buffer->insert(*cursorPos, 1, 'U'); *cursorPos+=1; }
					if (keys[SDLK_v].bActive) { buffer->insert(*cursorPos, 1, 'V'); *cursorPos+=1; }
					if (keys[SDLK_w].bActive) { buffer->insert(*cursorPos, 1, 'W'); *cursorPos+=1; }
					if (keys[SDLK_x].bActive) { buffer->insert(*cursorPos, 1, 'X'); *cursorPos+=1; }
					if (keys[SDLK_y].bActive) { buffer->insert(*cursorPos, 1, 'Y'); *cursorPos+=1; }
					if (keys[SDLK_z].bActive) { buffer->insert(*cursorPos, 1, 'Z'); *cursorPos+=1; }
				}
				else {
					if (keys[SDLK_a].bActive) { buffer->insert(*cursorPos, 1, 'a'); *cursorPos+=1; }
					if (keys[SDLK_b].bActive) { buffer->insert(*cursorPos, 1, 'b'); *cursorPos+=1; }
					if (keys[SDLK_c].bActive) { buffer->insert(*cursorPos, 1, 'c'); *cursorPos+=1; }
					if (keys[SDLK_d].bActive) { buffer->insert(*cursorPos, 1, 'd'); *cursorPos+=1; }
					if (keys[SDLK_e].bActive) { buffer->insert(*cursorPos, 1, 'e'); *cursorPos+=1; }
					if (keys[SDLK_f].bActive) { buffer->insert(*cursorPos, 1, 'f'); *cursorPos+=1; }
					if (keys[SDLK_g].bActive) { buffer->insert(*cursorPos, 1, 'g'); *cursorPos+=1; }
					if (keys[SDLK_h].bActive) { buffer->insert(*cursorPos, 1, 'h'); *cursorPos+=1; }
					if (keys[SDLK_i].bActive) { buffer->insert(*cursorPos, 1, 'i'); *cursorPos+=1; }
					if (keys[SDLK_j].bActive) { buffer->insert(*cursorPos, 1, 'j'); *cursorPos+=1; }
					if (keys[SDLK_k].bActive) { buffer->insert(*cursorPos, 1, 'k'); *cursorPos+=1; }
					if (keys[SDLK_l].bActive) { buffer->insert(*cursorPos, 1, 'l'); *cursorPos+=1; }
					if (keys[SDLK_m].bActive) { buffer->insert(*cursorPos, 1, 'm'); *cursorPos+=1; }
					if (keys[SDLK_n].bActive) { buffer->insert(*cursorPos, 1, 'n'); *cursorPos+=1; }
					if (keys[SDLK_o].bActive) { buffer->insert(*cursorPos, 1, 'o'); *cursorPos+=1; }
					if (keys[SDLK_p].bActive) { buffer->insert(*cursorPos, 1, 'p'); *cursorPos+=1; }
					if (keys[SDLK_q].bActive) { buffer->insert(*cursorPos, 1, 'q'); *cursorPos+=1; }
					if (keys[SDLK_r].bActive) { buffer->insert(*cursorPos, 1, 'r'); *cursorPos+=1; }
					if (keys[SDLK_s].bActive) { buffer->insert(*cursorPos, 1, 's'); *cursorPos+=1; }
					if (keys[SDLK_t].bActive) { buffer->insert(*cursorPos, 1, 't'); *cursorPos+=1; }
					if (keys[SDLK_u].bActive) { buffer->insert(*cursorPos, 1, 'u'); *cursorPos+=1; }
					if (keys[SDLK_v].bActive) { buffer->insert(*cursorPos, 1, 'v'); *cursorPos+=1; }
					if (keys[SDLK_w].bActive) { buffer->insert(*cursorPos, 1, 'w'); *cursorPos+=1; }
					if (keys[SDLK_x].bActive) { buffer->insert(*cursorPos, 1, 'x'); *cursorPos+=1; }
					if (keys[SDLK_y].bActive) { buffer->insert(*cursorPos, 1, 'y'); *cursorPos+=1; }
					if (keys[SDLK_z].bActive) { buffer->insert(*cursorPos, 1, 'z'); *cursorPos+=1; }
				}
			}

			/*
			 * Keypad is always in numeric mode
			 */
			if(bShift && !bNumeric) {
				if (keys[SDLK_1].bActive) { buffer->insert(*cursorPos, 1, '!'); *cursorPos+=1; }
				if (keys[SDLK_2].bActive) { buffer->insert(*cursorPos, 1, '@'); *cursorPos+=1; }
				if (keys[SDLK_3].bActive) { buffer->insert(*cursorPos, 1, '#'); *cursorPos+=1; }
				if (keys[SDLK_4].bActive) { buffer->insert(*cursorPos, 1, '$'); *cursorPos+=1; }
				if (keys[SDLK_5].bActive) { buffer->insert(*cursorPos, 1, '%'); *cursorPos+=1; }
				if (keys[SDLK_6].bActive) { buffer->insert(*cursorPos, 1, '^'); *cursorPos+=1; }
				if (keys[SDLK_7].bActive) { buffer->insert(*cursorPos, 1, '&'); *cursorPos+=1; }
				if (keys[SDLK_8].bActive || keys[SDLK_KP_MULTIPLY].bActive) { buffer->insert(*cursorPos, 1, '*'); *cursorPos+=1; }
				if (keys[SDLK_9].bActive) { buffer->insert(*cursorPos, 1, '('); *cursorPos+=1; }
				if (keys[SDLK_0].bActive) { buffer->insert(*cursorPos, 1, ')'); *cursorPos+=1; }
				if (keys[SDLK_MINUS].bActive) { buffer->insert(*cursorPos, 1, '_'); *cursorPos+=1; }
				if (keys[SDLK_EQUALS].bActive || keys[SDLK_KP_PLUS].bActive) { buffer->insert(*cursorPos, 1, '+'); *cursorPos+=1; }
				if (keys[SDLK_LEFTBRACKET].bActive) { buffer->insert(*cursorPos, 1, '{'); *cursorPos+=1; }
				if (keys[SDLK_RIGHTBRACKET].bActive) { buffer->insert(*cursorPos, 1, '}'); *cursorPos+=1; }
				if (keys[SDLK_SLASH].bActive) { buffer->insert(*cursorPos, 1, '?'); *cursorPos+=1; }
				if (keys[SDLK_SEMICOLON].bActive) { buffer->insert(*cursorPos, 1, ':'); *cursorPos+=1; }
				if (keys[SDLK_QUOTE].bActive) { buffer->insert(*cursorPos, 1, '"'); *cursorPos+=1; }
				if (keys[SDLK_COMMA].bActive) { buffer->insert(*cursorPos, 1, '<'); *cursorPos+=1; }
				if (keys[SDLK_PERIOD].bActive) { buffer->insert(*cursorPos, 1, '>'); *cursorPos+=1; }
				if (keys[SDLK_BACKSLASH].bActive) { buffer->insert(*cursorPos, 1, '|'); *cursorPos+=1; }
			}
			else {
				if (keys[SDLK_1].bActive || keys[SDLK_KP_1].bActive) { buffer->insert(*cursorPos, 1, '1'); *cursorPos+=1; }
				if (keys[SDLK_2].bActive || keys[SDLK_KP_2].bActive) { buffer->insert(*cursorPos, 1, '2'); *cursorPos+=1; }
				if (keys[SDLK_3].bActive || keys[SDLK_KP_3].bActive) { buffer->insert(*cursorPos, 1, '3'); *cursorPos+=1; }
				if (keys[SDLK_4].bActive || keys[SDLK_KP_4].bActive) { buffer->insert(*cursorPos, 1, '4'); *cursorPos+=1; }
				if (keys[SDLK_5].bActive || keys[SDLK_KP_5].bActive) { buffer->insert(*cursorPos, 1, '5'); *cursorPos+=1; }
				if (keys[SDLK_6].bActive || keys[SDLK_KP_6].bActive) { buffer->insert(*cursorPos, 1, '6'); *cursorPos+=1; }
				if (keys[SDLK_7].bActive || keys[SDLK_KP_7].bActive) { buffer->insert(*cursorPos, 1, '7'); *cursorPos+=1; }
				if (keys[SDLK_8].bActive || keys[SDLK_KP_8].bActive) { buffer->insert(*cursorPos, 1, '8'); *cursorPos+=1; }
				if (keys[SDLK_9].bActive || keys[SDLK_KP_9].bActive) { buffer->insert(*cursorPos, 1, '9'); *cursorPos+=1; }
				if (keys[SDLK_0].bActive || keys[SDLK_KP_0].bActive) { buffer->insert(*cursorPos, 1, '0'); *cursorPos+=1; }
				if (keys[SDLK_PERIOD].bActive || keys[SDLK_KP_PERIOD].bActive) { buffer->insert(*cursorPos, 1, '.'); *cursorPos+=1; }
				if(!bNumeric) {
					if (keys[SDLK_MINUS].bActive || keys[SDLK_KP_MINUS].bActive) { buffer->insert(*cursorPos, 1, '-'); *cursorPos+=1; }
					if (keys[SDLK_EQUALS].bActive) { buffer->insert(*cursorPos, 1, '='); *cursorPos+=1; }
					if (keys[SDLK_LEFTBRACKET].bActive) { buffer->insert(*cursorPos, 1, '['); *cursorPos+=1; }
					if (keys[SDLK_RIGHTBRACKET].bActive) { buffer->insert(*cursorPos, 1, ']'); *cursorPos+=1; }
					if (keys[SDLK_SLASH].bActive || keys[SDLK_KP_DIVIDE].bActive) { buffer->insert(*cursorPos, 1, '/'); *cursorPos+=1; }
					if (keys[SDLK_SEMICOLON].bActive) { buffer->insert(*cursorPos, 1, ';'); *cursorPos+=1; }
					if (keys[SDLK_QUOTE].bActive) { buffer->insert(*cursorPos, 1, '\''); *cursorPos+=1; }
					if (keys[SDLK_COMMA].bActive) { buffer->insert(*cursorPos, 1, ','); *cursorPos+=1; }
					if (keys[SDLK_BACKSLASH].bActive) { buffer->insert(*cursorPos, 1, '\\'); *cursorPos+=1; }

					// Keypad specific duplicates
					if (keys[SDLK_KP_PLUS].bActive) { buffer->insert(*cursorPos, 1, '+'); *cursorPos+=1; }
					if (keys[SDLK_KP_MULTIPLY].bActive) { buffer->insert(*cursorPos, 1, '*'); *cursorPos+=1; }
				}
				else {
					/*
					 * Special handling of +/- for numeric entry
					 */
					if (keys[SDLK_MINUS].bActive || keys[SDLK_KP_MINUS].bActive) {
						if(buffer->length()>0) {
							if((*buffer)[0]!='-') (*buffer) = "-"+(*buffer);
						}
						else (*buffer) = "-";
					}
					if (keys[SDLK_EQUALS].bActive || keys[SDLK_KP_PLUS].bActive) {
						if(buffer->length()>0) {
							if((*buffer)[0]=='-') buffer->replace(0, 1, "");
						}
					}
				}
			}
		}
	}

	/** ******************************************************************************************************************************
	 *
	 * ****************************************************************************************************************************** */
	void _Keyboard::update() {
		for (auto & key : keys.data) {
			switch(key.eKeyType) {
				case KEYTYPE_ONESHOT:	keys.execOneShot(key.keyCode);	break;
				case KEYTYPE_TOGGLE:	keys.execToggle(key.keyCode);	break;
				default:				keys.execRepeat(key.keyCode);
			}
		}
	}
}
#endif /* INPUTSYS_H_ */
