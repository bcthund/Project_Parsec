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
#include <chrono>
#include "GUI_Container.h"

namespace Core {
	namespace GUI {
		namespace Object {
			namespace Base {
				struct c_ID {
					t_VectorMap<int> list;				///< Unique object IDs (bool specifies in-use, for possible future use)

					c_ID() {
						list.setSource("GUI IDs");
					}

					/**
					 * @brief Will create a new unique ID and assign it to the used ID list, then return the ID
					 * @return The unique ID of this object
					 */
					std::string create() {
						int time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
						std::ostringstream timeStamp;
						timeStamp << std::hex << time;
						list.add(timeStamp.str(), true);
						return timeStamp.str();
					}
					void set(std::string id, int i)		{	list[id] = i;		}
					void remove(std::string id) 		{	list.remove(id);	}
					int & operator[](std::string id)	{	return list[id];	}
				};

//				class FieldBase {
//					public:
//						static Core::_Keyboard keyboard;
//						static bool bKeyboardInit;
//
//						FieldBase() {
//							if(!bKeyboardInit) {
//								keyboard.calc(Core::_Keyboard::KEYTYPE_ONESHOT);
//								bKeyboardInit = true;
//							}
//						}
//				};
//				Core::_Keyboard FieldBase::keyboard	= Core::_Keyboard();
//				bool FieldBase::bKeyboardInit		= false;

				struct c_Generic_Base {
					public:
						static Core::_Keyboard keyboard;
						static bool bKeyboardInit;

						static bool bFocusPresent;				///< An object currently has focus
						static std::string sActiveObject;		///< Global active object, only one object can be active at a time (Field, slider, textedit, etc)

						static bool bScrollFocus;				///< An object has scrolling focus
						static std::string sScrollObject;		///< Object name preventing scrolling

//						static GUI_Container* activeContainer;
						static Props_Window* activeGUI;
						static Props_Window* activeContainer;

						c_Generic_Base() {
							if(!bKeyboardInit) {
								//keyboard.calc(Core::_Keyboard::KEYTYPE_ONESHOT);
								keyboard.calc(Core::_Keyboard::KEYTYPE_DEBOUNCE);
								bKeyboardInit = true;
							}
						}
						~c_Generic_Base() {}
				};
				Core::_Keyboard c_Generic_Base::keyboard		= Core::_Keyboard();
				bool c_Generic_Base::bKeyboardInit				= false;

				bool c_Generic_Base::bFocusPresent				= false;
				std::string c_Generic_Base::sActiveObject		= "";

				bool c_Generic_Base::bScrollFocus				= false;
				std::string c_Generic_Base::sScrollObject		= "";

				Props_Window* c_Generic_Base::activeGUI			= nullptr;
				Props_Window* c_Generic_Base::activeContainer	= nullptr;

				template <class C>
				class Generic : virtual public c_Generic_Base {
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
						friend class ProgressBar;
						friend class ComboBox;

					public:
						//Core::_Mouse::MOUSE_STATE mState;
						Core::_Mouse::iMouseState mState;
						std::string name;						///< Generic object name used for user interaction
						std::string id;							///< Unique object ID used by system
						bool bInit;								///< Object has been initialized and exec() can run
						bool bLocalCon;							///< Are contraints locally defined
						bool bHasParent;						///< Does object have a parent
						bool bIsGrouped;						///< Is object part of a group
						iState eObjectState;					///< Internal state of the object
						Timer timeFocusDebounce;				///< Debounce timer to lose focus (too fast can cause issues at object transistions)
						int iFocusDebounce;						///< Amount of time before losing focus
//						static std::vector<std::string> IDs;	///< Unique object IDs
						int border;
						C			* con;
						Props * parent;
						bool bEnabled;

						Generic() {
//							IDs.list.setSource("GUI IDs");
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
							for (int n=0; n<8; n++) {
								enable.AND(n) = true;
								enable.OR(n) = false;
							}
							enable.OR(0) = true;
							border = 1;
							bEnabled = true;
							iFocusDebounce = 100;
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
							bEnabled			= src.bEnabled;
							iFocusDebounce		= src.iFocusDebounce;

							bLocalCon			= src.bLocalCon;
							if(bLocalCon) con = new C(*src.con);
							else con = src.con;

							bHasParent			= src.bHasParent;
							parent				= src.parent;

							enable				= src.enable;

							return *this;
						}

						void hide()		{	con->visibility = false;	}
						void show()		{	con->visibility = true;	}
						bool visible()	{	return con->visibility;	}
						void setEnabled(bool b) { bEnabled = b; }
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
							return bEnabled && (bAND && bOR);
						}
						iState	getObjectState()	{	return eObjectState;	}

						static c_ID IDs;

					private:
//						bool bCopied;	// FIXME: MEMORY LEAKS HERE: Pointers not getting deleted (probably just remove this)
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

				};

				template <class C>
				c_ID Generic<C>::IDs;
//				std::vector<std::string> Generic<C>::c_ID::IDs;

//				class Interactive_Base {
//					public:
//						static bool bFocusPresent;				///< An object currently has focus
//						static std::string sActiveObject;		///< Global active object, only one object can be active at a time (Field, slider, textedit, etc)
//
//						static bool bScrollFocus;				///< An object has scrolling focus
//						static std::string sScrollObject;		///< Object name preventing scrolling
//
//						Interactive_Base() {}
//						~Interactive_Base() {}
//				};
//				bool Interactive_Base::bFocusPresent			= false;
//				std::string Interactive_Base::sActiveObject		= "";
//				bool Interactive_Base::bScrollFocus				= false;
//				std::string Interactive_Base::sScrollObject		= "";

				template <class C>
				//class Interactive : public Generic<C>, virtual public Interactive_Base {
				class Interactive : public Generic<C> {
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
						friend class ComboBox;
					protected:
						bool *statePtr;
						bool bLocalState;
						bool bStateChanged;
						Timer debounceTimer;

					public:
						t_DataSet dataSet;
						std::string sOnState, sOffState;
						bool bRepeatStatus;					///< Used for oneshot and debounce button types

						Interactive() {
							statePtr		= nullptr;
							bStateChanged	= false;
							bLocalState		= false;
							sOnState		= "ON";
							sOffState		= "OFF";
							bRepeatStatus	= false;
						}

						Interactive(const Interactive &src) {
							//std::cout << "Interactive &operator=() called\n";
							this->mState	= src.mState;
							statePtr		= new bool(src.statePtr);
							bStateChanged	= src.bStateChanged;
							bLocalState		= src.bLocalState;
							bRepeatStatus	= src.bRepeatStatus;

							Generic<C>::operator=(src);
							//this->Interactive_Base::operator=(src);
						}

						Interactive &operator=(const Interactive &src) {
							//std::cout << "Interactive &operator=() called\n";
							this->mState	= src.mState;
							statePtr		= new bool(src.statePtr);
							bStateChanged	= src.bStateChanged;
							bLocalState		= src.bLocalState;

							this->Generic<C>::operator=(src);
							return *this;
						}

						/**
						 * \brief Get the value of this object. For a button it will be the boolean state.
						 * @return Return value of this object
						 */
						bool getState() {	return *statePtr;	}

						/**
						 * \brief Get the value of this object. For a button it will be the boolean state.
						 * @return Return value of this object
						 */
						bool getFocus() {	return this->eObjectState&STATE_FOCUS;	}

						/**
						 * \brief Set the pointer of internal state to an external item
						 * @param ptr The ptr to use instead of internal pointer. Must be managed (deleted) externally.
						 */
						void	setStatePtr(bool *ptr)	{
							if(bLocalState && statePtr != nullptr) delete statePtr;
							bLocalState = false;
							statePtr = ptr;
						}

						/**
						 * \brief Get a pointer to the internal value, which could point to an external value
						 * @return Pointer to internal/external value
						 */
						bool * getStatePtr()		{	return statePtr;	}

						/**
						 * \brief Set the value of the internal state
						 * @param b Value to set state to
						 */
						void setState(bool b) {
							*statePtr = b;
						}

						/**
						 * \brief Get the custom return states
						 * @param n Return state index
						 * @return Value of returnState at index \p n
						 */
						t_BIFS getDataSetValue(int n=0) {
							if(this->eObjectState&STATE_ACTIVE)	return dataSet[sOnState][n];
							else return dataSet[sOffState][n];
						}

						/**
						 * \brief Gets the entire dataset for an object as a reference so it can be modified
						 * @return Return the entire dataset for this object
						 */
						t_DataSet &getDataSet() {
							return dataSet;
						}

						/**
						 * \brief Check if the value has changed since last read. Can only be called once, resets immediately after calling.
						 * @return True if internal value has changed
						 */

						bool	stateChanged() {
							if(bStateChanged) {
								bStateChanged = false;
								return true;
							}
							return false;
						}

						/**
						 * Update the internal/external value according to internal state
						 */
						void updateStatePtr() {
							if(this->eObjectState&STATE_ACTIVE) *statePtr = true;
							else *statePtr = false;
						}

						/**
						 * Update the internal state in case the internal/external value was changed externally
						 */
						void checkStatePtr() {
							if(*statePtr && !(this->eObjectState&STATE_ACTIVE))
								this->eObjectState = STATE_ACTIVE;
							else if(!*statePtr && (this->eObjectState&STATE_ACTIVE))
								this->eObjectState = STATE_NONE;
						}
				};

				class AudioFeedback {
					public:
						bool bRising;
						bool bOneShotOn;
						bool bOneShotOff;
//						int iSampleOn;
//						int iSampleOff;
//						int iLoopOn;
//						int iLoopOff;
//						bool bOverlapOn;
//						bool bOverlapOff;
//						int iChannel;
						t_SoundInstance audio;

						void initSound(int iChannel, int iSampleOn, int iSampleOff, int iLoopOn, int iLoopOff, bool bOverlapOn, bool bOverlapOff);
						void Sound_PlayOn();
						void Sound_AbortState();
						void Sound_StopOn();
						void Sound_StopOff();
						void Sound_PlayOff();
						void Sound_PlayAuto(iState eState, bool bRepeat=false);
						AudioFeedback() {
							bRising		= false;
							bOneShotOn	= false;
							bOneShotOff	= true;
						}
				};

				void AudioFeedback::initSound(int iChannel, int iSampleOn, int iSampleOff, int iLoopOn, int iLoopOff, bool bOverlapOn, bool bOverlapOff) {
					audio.add("SampleOn", iSampleOn, iLoopOn, bOverlapOn, iChannel);
					audio.add("SampleOff", iSampleOff, iLoopOff, bOverlapOff, iChannel);
				}

				void AudioFeedback::Sound_PlayOn() {
//					if(!bOneShotOn) {
						audio.play("SampleOn");
						bOneShotOn = true;
//					}
				}

				void AudioFeedback::Sound_AbortState() {
					bOneShotOn = false;
				}

				void AudioFeedback::Sound_StopOn() {
					audio.stop("SampleOn");
				}

				void AudioFeedback::Sound_StopOff() {
					audio.stop("SampleOff");
				}

				void AudioFeedback::Sound_PlayOff() {
					if(bOneShotOn) {
						audio.play("SampleOff");
						bOneShotOn = false;
					}
				}

				void AudioFeedback::Sound_PlayAuto(iState eState, bool bRepeat) {
					if( (eState&STATE_ACTIVE) && (!bRising || bRepeat) ) {
						audio.play("SampleOn");
						bRising = true;
					}
					else if( !(eState&STATE_ACTIVE) && (bRising) /*&& !Mix_Playing(-1)*/ ) {
						audio.play("SampleOff");
						bRising = false;
					}
				}


			}
		}
	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_OBJECTS_H_ */
