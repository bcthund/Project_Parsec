/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_OBJECTS_H_
#define HEADERS_GAMESYS_GUI_OBJECTS_H_

/*
 * Creates GUI instances for particular objects that can be
 * used as a building block for a full GUI.
 *
 * These classes draw the objects and handle IO, as well as
 * 	providing "focus" tracking.
 * 		- Focus may be achieved with a static INT that
 * 			contains an ID. The ID will represent the
 * 			active object.
 * 		- Focus should be handled with a "history" so when
 * 			an object releases focus the previous object in
 * 			history gets focus back.
 */

#include <iostream>
//#include "../../core/core_functions.h"
#include "../../core/InputSys.h"
#include "GUI_Constraint.h"
#include "../../core/timer.h"
#include "../../core/audiosys.h"
//#include "../../core/InputSys.h"
//#include "../../gamesys/gameVars.h"
//#include "../core/vao.h"
//#include "../core/matrix.h"
//#include "../core/shader.h"

namespace Core {
	namespace GUI {
		namespace Object {
			namespace Base {
				template <class C>
				class Generic {
	//					friend class Container;
						friend class Button;
						friend class CheckBox;
						friend class ColorSwatch;
						friend class Field;
						friend class AnyField;
						friend class Icon;
						friend class Label;
						friend class Slider;
						friend class AnySlider;
						friend class Sprite;
						friend class Text;
						friend class TextArea;
						friend class TextEdit;
						friend class Window;

					protected:
						Core::_Mouse::MOUSE_STATE mState;
						std::string name;
						bool bInit;
						bool bLocalCon;
						bool bHasParent;
						bool bIsGrouped;
						bool bRepeatStatus;
						iState eObjectState;

					private:
//						bool bCopied;	// FIXME: Implement copy/assignment constructors
						class _AndOrBase {
							friend class Generic;
							private:
								struct _AndOr {
									bool bLocal;
									bool *b;
									bool &operator()() { return *b; }

									_AndOr() {
										bLocal = false;
										b = nullptr;
									}
								} s_AND[8], s_OR[8];

							public:
								int iAND, iOR;
								bool &AND(int n) { return *s_AND[n].b; }
								bool &OR(int n) { return *s_OR[n].b; }

								_AndOrBase &operator=(const _AndOrBase &src) {

//									std::cout << "_AndOrBase &operator=() called\n\n";

									iAND = src.iAND;
									iOR = src.iOR;

									for (int n=0; n<8; n++) {
										s_AND[n].bLocal = src.s_AND[n].bLocal;
										if(src.s_AND[n].bLocal) s_AND[n].b = new bool(src.s_AND[n].b);
										else s_AND[n].b = src.s_AND[n].b;

										s_OR[n].bLocal = src.s_OR[n].bLocal;
										if(src.s_OR[n].bLocal) s_OR[n].b = new bool(src.s_OR[n].b);
										else s_OR[n].b = src.s_OR[n].b;
									}

									return *this;
								}

								_AndOrBase() {
									iAND = 0;
									iOR = 0;

									for (int n=0; n<8; n++) {
										s_AND[n].bLocal = true;
										s_AND[n].b = new bool(true);

										s_OR[n].bLocal = true;
										s_OR[n].b = new bool(false);
									}
								}

								~_AndOrBase() {
									for (int n=0; n<8; n++) {
										if(s_AND[n].bLocal) delete s_AND[n].b;
										if(s_OR[n].bLocal) delete s_OR[n].b;
									}
								}
						} enable;

					public:
						int border;
						C			* con;
						Props * parent;
						void hide()		{	con->visibility = false;	}
						void show()		{	con->visibility = true;	}
						bool visible()	{	return con->visibility;	}

						void setEnableA(bool b, int n=0) { *enable.s_AND[n].b = b; }

						void setEnableAPtr(bool *b)
						{
							setEnableAPtr(b, enable.iAND);
							enable.iAND = std::min(enable.iAND+1, 7);
						}

						void setEnableAPtr(bool *b, int n)
						{
							enable.iAND = std::min(n, 7);
							if(enable.s_AND[enable.iOR].bLocal) delete enable.s_AND[enable.iOR].b;
							enable.s_AND[enable.iOR].bLocal = false;
							enable.s_AND[enable.iOR].b = b;
						}

						void setEnableO(bool b, int n=0) { enable.s_OR[n].b = b; }

						void setEnableOPtr(bool *b) {
							setEnableOPtr(b, enable.iOR);
							enable.iOR = std::min(enable.iOR+1, 7);
						}

						void setEnableOPtr(bool *b, int n) {
							enable.iOR = std::min(n, 7);
							if(enable.s_OR[enable.iOR].bLocal) delete enable.s_OR[enable.iOR].b;
							enable.s_OR[enable.iOR].bLocal = false;
							enable.s_OR[enable.iOR].b = b;
						}

						bool enabled() {
							bool bAND = true;
							bool bOR = false;
							for (int n=0; n<8; n++) {
								bAND = bAND && enable.AND(n);
								bOR = bOR || enable.OR(n);
							}
							return bAND && bOR;
						}
						iState	getObjectState()	{	return eObjectState;	}

						Generic() {
							mState			= Core::_Mouse::MOUSE_NONE;
//							bCopied			= false;
							con				= nullptr;
							name			= "";
							bInit			= false;
							parent			= nullptr;
							bLocalCon		= false;
							bHasParent		= false;
							bIsGrouped		= false;
							eObjectState	= STATE_NONE;
							bRepeatStatus	= false;
							for (int n=0; n<8; n++) {
								enable.AND(n) = true;
								enable.OR(n) = false;
							}
							enable.OR(0) = true;
							border = 1;
						}

						virtual ~Generic() {
							/*
							 * Do not delete pointers if never initialized
							 *
							 * This is a safety catch to prevent temporary objects
							 * from detroying their pointers after being copied
							 * to another object.
							 */
							if(bInit) {
								// TODO: delete pointers if local
							}
						}

						Generic &operator=(const Generic &src) {
//							std::cout << "Generic &operator=() called\n";
							mState				= src.mState;
							name				= src.name;
							bInit				= src.bInit;
							bIsGrouped			= src.bIsGrouped;
							eObjectState		= src.eObjectState;
							bRepeatStatus		= src.bRepeatStatus;

							bLocalCon			= src.bLocalCon;
							if(bLocalCon) con = new C(*src.con);
							else con = src.con;

							bHasParent			= src.bHasParent;
							parent				= src.parent;

							enable				= src.enable;

							return *this;
						}

				};

				class Interactive_Base {
					public:
						static bool bFocusPresent;				// An object currently has focus
						static std::string sActiveObject;		// Global active object, only one object can be active at a time (Field, slider, textedit, etc)
						static std::string sGroupObject[32];	// Active grouped object
						Interactive_Base() {}
						~Interactive_Base() {}
				};
				bool Interactive_Base::bFocusPresent			= false;
				std::string Interactive_Base::sActiveObject		= "";
				std::string Interactive_Base::sGroupObject[32]	= { "" };

				template <class C, typename T>
				class Interactive : public Generic<C>, virtual public Interactive_Base {
	//					friend class Container;
						friend class Button;
						friend class CheckBox;
						friend class ColorSwatch;
						friend class Field;
						friend class AnyField;
						friend class Icon;
						friend class Label;
						friend class Slider;
						friend class AnySlider;
						friend class Sprite;
						friend class Text;
						friend class TextArea;
						friend class TextEdit;
						friend class Window;
					protected:
						T	*valuePtr;
						bool bLocalValue;
						bool bReturnInit;
						bool bValueChanged;
						Timer debounceTimer;
						Props_Addon_ReturnState *returnState;

					public:
						Interactive() {
							valuePtr		= nullptr;
							bValueChanged	= false;
							bLocalValue		= false;
							returnState		= nullptr;
							bReturnInit		= false;
						}

						Interactive &operator=(const Interactive &src) {
							std::cout << "Interactive &operator=() called\n";
//							mState			= src.mState;
							valuePtr		= src.valuePtr;
							bValueChanged	= src.bValueChanged;
							bLocalValue		= src.bLocalValue;
							returnState		= src.returnState;
							bReturnInit		= src.bReturnInit;
							returnState		= new Props_Addon_ReturnState(*src.returnState);

							this->Generic<C>::operator =(src);
							return *this;
						}

						bool	getPtrValue()		{	return *valuePtr;	}
						void	setPointer(T *ptr)	{
							if(bLocalValue && valuePtr != nullptr) delete valuePtr;
							bLocalValue = false;
							valuePtr = ptr;
						}		// FIXME: What if local value already declared? Need to delete.
						T*		getPointer()		{	return valuePtr;	}

						void init(Props_Addon_ReturnState *ptr) {
							returnState		= ptr;
							bReturnInit		= true;
						}

						int getState(int n=0)  {
							if(bReturnInit) {
								if(this->eObjectState&STATE_ACTIVE)	return returnState->on[n];
								else return returnState->off[n];
							}
							else return 0;
						}

						bool	valueChanged() {
							if(bValueChanged) {
								bValueChanged = false;
								return true;
							}
							return false;
						}

						void	updateValuePtr() {
//							// FIXME: Disconnect between eObjectState and valuePtr. eObjectState should be set from valuePtr, and probably not here.
							if(this->eObjectState&STATE_ACTIVE) *valuePtr = (T)returnState->on[0];
							else *valuePtr = (T)returnState->off[0];
//
////							if(*valuePtr) this->eObjectState = STATE_ACTIVE;
////							else this->eObjectState = STATE_NONE;
						}
				};

				class AudioFeedback {
					public:
						bool bRising;
						bool bOneShotOn;
						bool bOneShotOff;
						int iSampleOn;
						int iSampleOff;
						int iLoopOn;
						int iLoopOff;
						bool bOverlapOn;
						bool bOverlapOff;
						int iChannel;
						void initSound(int iChannel, int iSampleOn, int iSampleOff, int iLoopOn, int iLoopOff, bool bOverlapOn, bool bOverlapOff);
						void Sound_PlayOn();
						void Sound_AbortState();
						void Sound_PlayOff();
						void Sound_PlayAuto(iState eState, bool bRepeat=false);
						AudioFeedback() {
							iChannel	= 0;
							bRising		= false;
							bOneShotOn	= false;
							bOneShotOff	= true;
							iSampleOn	= 1;
							iSampleOff	= 2;
							iLoopOn		= 0;
							iLoopOff	= 0;
							bOverlapOn	= false;
							bOverlapOff	= false;
						}
				};

				void AudioFeedback::initSound(int iChannel, int iSampleOn, int iSampleOff, int iLoopOn, int iLoopOff, bool bOverlapOn, bool bOverlapOff) {
					this->iChannel		= iChannel;
					this->iSampleOn		= iSampleOn;
					this->iSampleOff	= iSampleOff;
					this->iLoopOn		= iLoopOn;
					this->iLoopOff		= iLoopOff;
					this->bOverlapOn	= bOverlapOn;
					this->bOverlapOff	= bOverlapOff;
				}

				void AudioFeedback::Sound_PlayOn() {
//					if(!bOneShotOn) {
						Core::audioSys->playSound(iSampleOn, iLoopOn, bOverlapOn, iChannel);
						bOneShotOn = true;
//					}
				}

				void AudioFeedback::Sound_AbortState() {
					bOneShotOn = false;
				}

				void AudioFeedback::Sound_PlayOff() {
					if(bOneShotOn) {
						Core::audioSys->playSound(iSampleOff, iLoopOff, bOverlapOff, iChannel);
						bOneShotOn = false;
					}
				}

				void AudioFeedback::Sound_PlayAuto(iState eState, bool bRepeat) {
					if( (eState&STATE_ACTIVE) && (!bRising || bRepeat) ) {
//						std::cout << "On\n";
						Core::audioSys->playSound(iSampleOn, iLoopOn, bOverlapOn, iChannel);
						bRising = true;
					}
					else if( !(eState&STATE_ACTIVE) && (bRising) && !Mix_Playing(-1) ) {
//						std::cout << "Off\n";
						Core::audioSys->playSound(iSampleOff, iLoopOff, bOverlapOff, iChannel);
						bRising = false;
					}
				}


			}
		}
	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_OBJECTS_H_ */
