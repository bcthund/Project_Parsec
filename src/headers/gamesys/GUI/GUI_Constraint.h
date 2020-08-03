/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_CONSTRAINTS_H_
#define HEADERS_GAMESYS_GUI_CONSTRAINTS_H_

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
#include <climits>
#include <memory>
#include "../../core/core_functions.h"
#include "../../core/Stipple.h"
#include "../../core/Groups.h"

namespace Core {
	/** ******************************************************************************************************************************
	 *	\namespace GUI
	 *
	 * Creates GUI instances for particular objects that can be
	 * used as a building block for a full GUI.
	 * ****************************************************************************************************************************** */
	namespace GUI {

		#define FORWARD class Window;\
						class Label;\
						class ToolTip;\
						template <class T>class Field;\
						class Button;\
						template <class T>class Slider;\
						class Text;\
						class TextArea;\
						class TextEdit;\
						class ColorSwatch;\
						class CheckBox;\
						class Icon;\
						class Sprite;\
						class ProgressBar;\
						class ComboBox

		#define FRIENDS friend class GUI_Container;\
						friend class Window;\
						friend class Label;\
						friend class ToolTip;\
						friend class Field;\
						friend class Button;\
						friend class Slider;\
						friend class Text;\
						friend class TextArea;\
						friend class TextEdit;\
						friend class ColorSwatch;\
						friend class CheckBox;\
						friend class Icon;\
						friend class Sprite;\
						friend class ProgressBar;\
						friend class ComboBox



		// Forward declarations for freinds
		namespace Object {
//			class Window;
//			class Label;
//			class ToolTip;
//			template <class T>class Field;
//			class Button;
//			template <class T>class Slider;
//			class Text;
//			class TextArea;
//			class TextEdit;
//			class ColorSwatch;
//			class CheckBox;
//			class Icon;
//			class Sprite;
//			class ProgressBar;

			FORWARD;
		}

		class Props_Window;
		class Props_Buttonclass;
		class Props_Slider;
		class Props_Label;
		class Props_Field;
		class Props_Text;
		class Props_TextArea;
		class Props_ColorSwatch;
		class Props_CheckBox;
		class Props_Icon;
		class Props_Sprite;
		class Props_ProgressBar;
		class Props_ComboBox;

		enum eButtonType {	BUTTON_ONESHOT,		// Button is active for one cycle
							BUTTON_MOMENTARY,	// Button is active as long as pressed
							BUTTON_TOGGLE,		// Button toggles state with each press
							BUTTON_DEBOUNCE		// Button acts as a oneshot initially, but after a debounce time will act as momentary
		};

		enum eSizeConstraint {	SIZE_CONSTRAINT_RELATIVE,
								SIZE_CONSTRAINT_ABSOLUTE
		};

		enum eSlider {		SLIDER_VERTICAL,
							SLIDER_HORIZONTAL
		};

		// States for colors
		// FIXME: Add a STATE_NODRAW, to update data but not draw to screen (use for tooltip autosize calc)
		typedef int iState;
		enum eObjectState  {	STATE_NONE		= 0,	// Nested item state can change freely
								STATE_NOACTION	= 2,	// Nested item is drawn but state cannot change
								STATE_FOCUS		= 4,	// General focus, mouse if over object but doesn't affect coloring
								STATE_HOVER		= 8,
								STATE_ACTIVE	= 16,
								STATE_DISABLED	= 32,
								STATE_UPDATE	= 64,
								STATE_NODRAW	= 128
		};

//		typedef int iPadding;
		enum ePadding { 	PADDING_NONE			= 0,
							PADDING_SIZE			= 1,
							PADDING_POSITION		= 2,
							PADDING_ALL				= PADDING_SIZE|PADDING_POSITION
		};

		typedef int iConstrain;
		enum eConstrain {	CONSTRAIN_CENTER		= 1,
							CONSTRAIN_LEFT			= 2,
							CONSTRAIN_RIGHT			= 4,
							CONSTRAIN_TOP			= 8,
							CONSTRAIN_BOTTOM		= 16,
							// Convenience Labels
							CONSTRAIN_TOP_LEFT		= CONSTRAIN_TOP|CONSTRAIN_LEFT,
							CONSTRAIN_TOP_RIGHT		= CONSTRAIN_TOP|CONSTRAIN_RIGHT,
							CONSTRAIN_BOTTOM_LEFT	= CONSTRAIN_BOTTOM|CONSTRAIN_LEFT,
							CONSTRAIN_BOTTOM_RIGHT	= CONSTRAIN_BOTTOM|CONSTRAIN_RIGHT
		};


		struct GUI_ColorB {
			Color	* base;
			GUI_ColorB()						{	base = nullptr;	}
			GUI_ColorB(const GUI_ColorB *c)		{	base = c->base;	}
			GUI_ColorB(Color *b)				{	base = b;	}
			GUI_ColorB(const GUI_ColorB &src)	{
				base = new Color();
				base = src.base;
			}
			GUI_ColorB &operator=(const GUI_ColorB &src)	{
				base = new Color();
				base = src.base;
				return *this;
			}
		};

		struct GUI_ColorH {
			Color	* highlight;
			GUI_ColorH()						{	highlight = nullptr;	}
			GUI_ColorH(const GUI_ColorH *c)		{	highlight = c->highlight;	}
			GUI_ColorH(Color *h)				{	highlight = h;	}
			GUI_ColorH(const GUI_ColorH &src)	{
				highlight = new Color();
				highlight = src.highlight;
			}
			GUI_ColorH &operator=(const GUI_ColorH &src)	{
				highlight = new Color();
				highlight = src.highlight;
				return *this;
			}
		};

		struct GUI_ColorA {
			Color	* active;
			GUI_ColorA()						{	active = nullptr;	}
			GUI_ColorA(const GUI_ColorA *c)		{	active = c->active;	}
			GUI_ColorA(Color *a)				{	active = a;	}
			GUI_ColorA(const GUI_ColorA &src)	{
				active = new Color();
				active = src.active;
			}
			GUI_ColorA &operator=(const GUI_ColorA &src)	{
				active = new Color();
				active = src.active;
				return *this;
			}
		};

		// Generic and Highlight only
		struct GUI_ColorBH : public GUI_ColorB, public GUI_ColorH {
			GUI_ColorBH()							{	base = nullptr;	highlight = nullptr;	}
			GUI_ColorBH(const GUI_ColorBH *c)		{	base = c->base; highlight = c->highlight;	}
			GUI_ColorBH(Color *b, Color *h)	{	base = b;	highlight = h;	}
//			GUI_ColorBH(const GUI_ColorBH &src)	{
//				GUI_ColorB::GUI_ColorB(src);
//				GUI_ColorH::GUI_ColorH(src);
//			}
			GUI_ColorBH &operator=(const GUI_ColorBH &src)	{
				GUI_ColorB::operator=(src);
				GUI_ColorH::operator=(src);
				return *this;
			}
		};

		// Generic, highlight, and active colors
		struct GUI_ColorBHA : public GUI_ColorB, public GUI_ColorH, public GUI_ColorA {
			GUI_ColorBHA()										{	base = nullptr;	highlight = nullptr;	active = nullptr;	}
			GUI_ColorBHA(const GUI_ColorBHA *c)					{	base = c->base; highlight = c->highlight; active = c->active;	}
			GUI_ColorBHA(Color *b, Color *h, Color *a)	{	base = b;	highlight = h;	active = a;	}
//			GUI_ColorBHA(const GUI_ColorBHA &src)	{
//				GUI_ColorB::GUI_ColorB(src);
//				GUI_ColorH::GUI_ColorH(src);
//				GUI_ColorA::GUI_ColorA(src);
//			}
			GUI_ColorBHA &operator=(const GUI_ColorBHA &src)	{
				GUI_ColorB::operator=(src);
				GUI_ColorH::operator=(src);
				GUI_ColorA::operator=(src);
				return *this;
			}
		};

		/** ******************************************************************************************************************************
		 *  \class Props
		 *  \brief General Props used for all objects
		 *
		 * Generic constraints that all other contraints rely on. This is also the class
		 * that is used for parents to constrain objects to each other.
		 *
		 * ****************************************************************************************************************************** */
		class Props {
			public:
				struct s_Position : Vector2f {
					Vector2f constraint;						///< Size reference constraint used to calculate actual position
					s_Position() {}
				} pos;											///< Actual calculated position from origin and anchor constraints, automatically updated

				struct s_Size : Vector2f {
					struct s_SizeConstraint : Vector2f {
						eSizeConstraint xType,					///< Type of width constraint, relative or absolute
										yType;					///< Type of height constraint, relative or absolute
						bool			xAuto,					///< Auto size x axis
										yAuto;					///< Auto size y axis
						int				xMin,					///< Minimum x size
										xMax,					///< Maximum x size
										yMin,					///< Minimum y size (future)
										yMax;					///< Maximum y size (future)

						s_SizeConstraint() {
							x		= -1;
							y		= -1;
							xType	= SIZE_CONSTRAINT_ABSOLUTE;
							yType	= SIZE_CONSTRAINT_ABSOLUTE;
							xAuto	= false;
							yAuto	= false;
							xMin	= 10;
							xMax	= 250;
							yMin	= 10;
							yMax	= 250;
						}
					} constraint;								///< Width and Height reference constraint used to calculate actual size
					bool isAutoSet() {	return (!constraint.xAuto || (constraint.xAuto && constraint.x>0) ) && ( !constraint.yAuto || (constraint.yAuto && constraint.y>0) );	}
				} size;											///< Actual calculated width(x) and height(y) from origin and anchor constraints, automatically updated

				struct s_Scroll {
					friend class Props;
					friend class Object::Window;
					private:
						bool bScrollable;							///< Master determining if this object is scrollable
						bool *bEnablePtr;							///< Is scrolling enabled for this object
						bool bLocalEn,								///< Is the enable locally defined or external
							 bLocalX,								///< Is the x offset locally defined or external
							 bLocalY;								///< Is the y offset locally defined or external
						int *xOffsetPtr,							///< Used for scrolling (future implementation)
							*yOffsetPtr;							///< Used for scrolling

					public:
						int iMaxScroll;

						bool& getEnabledRef() {
							if(bEnablePtr!=nullptr) return *bEnablePtr;
							else throw std::runtime_error("Cannot access bEnablePtr, did you forget to bind with Props::scroll.bind()?");
						}
						int& getXRef() {
							if(xOffsetPtr!=nullptr) return *xOffsetPtr;
							else throw std::runtime_error("Cannot access xOffsetPtr, did you forget to bind with Props::scroll.bind()?");
						}
						int& getYRef() {
							if(yOffsetPtr!=nullptr) return *yOffsetPtr;
							else throw std::runtime_error("Cannot access yOffsetPtr, did you forget to bind with Props::scroll.bind()?");
						}

						bool isScrollable() {
							return bScrollable;
						}

						bool getEnabled() {
							if(bEnablePtr!=nullptr) return *bEnablePtr;
							else return false;
						}
						int getX() {
							if(xOffsetPtr!=nullptr) return *xOffsetPtr;
							else return 0;
						}
						int getY() {

							if(yOffsetPtr!=nullptr) return *yOffsetPtr;
							else return 0;
						}

						void enable(bool b=true) {
							if(bEnablePtr==nullptr) {
								bEnablePtr = new bool(b);
								bLocalEn = true;
							}
							else *bEnablePtr = b;
							bScrollable = b;
						}

						/**
						 * @brief Define as local values, this is usually when this object will be a parent
						 */
						void makeLocal() {
							if(bLocalEn && bEnablePtr!=nullptr) delete bEnablePtr;
							bLocalEn = true;
							bEnablePtr = new bool(false);

							if(bLocalX && xOffsetPtr!=nullptr) delete xOffsetPtr;
							bLocalX = true;
							xOffsetPtr = new int(0);

							if(bLocalY && yOffsetPtr!=nullptr) delete yOffsetPtr;
							bLocalY = false;
							yOffsetPtr = new int(0);
						}

						/**
						 * @brief Assign external pointer to #bEnablePtr
						 * @param x
						 */
						void bindEnable(bool &b) {
							if(bLocalEn && bEnablePtr!=nullptr) delete bEnablePtr;
							bLocalEn = false;
							bEnablePtr = &b;
						}

						/**
						 * @brief Assign external pointer to #xOffsetPtr
						 * @param x
						 */
						void bindX(int &x) {
							if(bLocalX && xOffsetPtr!=nullptr) delete xOffsetPtr;
							bLocalX = false;
							xOffsetPtr = &x;
						}
						/**
						 * @brief Assign external pointer to #yOffsetPtr
						 * @param y
						 */
						void bindY(int &y) {
							if(bLocalY && yOffsetPtr!=nullptr) delete yOffsetPtr;
							bLocalY = false;
							yOffsetPtr = &y;
						}
						/**
						 * @brief Assign all external pointers
						 * @param b Enable reference
						 * @param x x Offset reference
						 * @param y y Offset reference
						 */
						void bind(bool &b, int &x, int &y) {
							bindEnable(b);
							bindX(x);
							bindY(y);
						}

						/**
						 * @brief Assign all external pointers from a parent object
						 * @param p Parent properties
						 */
						void bind(Props &parent) {
							bindEnable(*parent.scroll.bEnablePtr);
							bindX(*parent.scroll.xOffsetPtr);
							bindY(*parent.scroll.yOffsetPtr);
						}

						void unBind() {
							if(bLocalEn && bEnablePtr!=nullptr) delete bEnablePtr;
							bLocalEn = false;

							if(bLocalX && xOffsetPtr!=nullptr) delete xOffsetPtr;
							bLocalX = false;

							if(bLocalY && yOffsetPtr!=nullptr) delete yOffsetPtr;
							bLocalY = false;
						}

						s_Scroll &operator=(const s_Scroll &src) {
							bScrollable		= src.bScrollable;

							bLocalEn		= src.bLocalEn;
							bEnablePtr		= new bool(*src.bEnablePtr);

							bLocalX			= src.bLocalX;
							xOffsetPtr		= new int(*src.xOffsetPtr);

							bLocalY			= src.bLocalY;
							yOffsetPtr		= new int(*src.yOffsetPtr);
							return *this;
						}

						s_Scroll() {
							iMaxScroll	= 0;
							bScrollable	= true;
							bLocalEn	= false;
							bEnablePtr	= nullptr;
							bLocalX		= false;
							bLocalY		= false;
							xOffsetPtr	= nullptr;
							yOffsetPtr	= nullptr;
						}

						// TODO: Copy constructor

						virtual ~s_Scroll() {
							if(bLocalEn && bEnablePtr!=nullptr) delete bEnablePtr;
							if(bLocalX && xOffsetPtr!=nullptr) delete xOffsetPtr;
							if(bLocalY && yOffsetPtr!=nullptr) delete yOffsetPtr;
						}
				} scroll;

				int						origin;					///< The starting drawing point with respect to the parent, if present, otherwise full screen.
				int						anchor;					///< The point at which this object is offset from the origin.
				Vector4i				vPadding;				///< Extra reserved space taken into account for origin.
				ePadding				eEnablePadding;
				bool 					visibility;				///< Controls if this object is drawn and any of its direct children.
				inline static bool		bGlobalSettings = true;	///< Used externally to allow multiple windows to use identical settings.
				std::string				text;					///< Text to be displayed by object (object name is used by default)
				bool					bFocusLock;				///< Do not lock when another object has focus (required for children that are part of the locking objetc)

				struct ToolTip {
					inline static bool	bShowGlobal = true;		///< Enable tooltips
					inline static int	showDelay = 2000;		///< ms before showing tooltip
					inline static int	hideDelay = 10000;		///< ms before hising tooltip after showing

					std::string			Text;					///< Tooltip text
					int					border;					///< border thickness
					int					radius;					///< border radius
					int					padding;				///< Padding for box around text
					int					margin;					///< Space from mouse location. Applies to both x and y.
					bool				round;					///< Rounded corners
					bool				showLabel;				///< Show name of tooltip (name of object attached to is used)
					bool				bShow;					///< Show this tooltip (automatically set when text applied)

					// FIXME: copy constructor
					// FIXME: assignment operator

					ToolTip() {
						bShow		= false;
						Text		= "No ToolTip set!";
						border		= 1;
						radius		= 0;
						padding		= 4;
						round		= false;
						showLabel	= true;
						margin		= 10;
					}
				} toolTip;

			private:
				void execPos(Vector2f cHalf, Vector2f oPos=Vector2f(0.0f), Vector4i vPad=Vector4i(0));
				void execSize(Vector2f cSize, Vector4i vPad=Vector4i(0));

			public:
				void setPos(Vector2f v)												{	pos.constraint.x = v.x;	pos.constraint.y = v.y;	}
				void setPos(int n1, int n2)											{	pos.constraint.x = n1;	pos.constraint.y = n2;	}
				void modPos(int n1, int n2)											{	pos.constraint.x += n1;	pos.constraint.y += n2;	}
				void setX(int n)													{	pos.constraint.x = n;	}
				void setY(int n)													{	pos.constraint.y = n;	}
				void modX(int n)													{	pos.constraint.x += n;	}
				void modY(int n)													{	pos.constraint.y += n;	}
				void setWidth(int n, eSizeConstraint e=SIZE_CONSTRAINT_ABSOLUTE)	{	size.constraint.x = n; size.constraint.xType = e;	}
				void setHeight(int n, eSizeConstraint e=SIZE_CONSTRAINT_ABSOLUTE)	{	size.constraint.y = n; size.constraint.yType = e;	}
				void modSize(int n1, int n2)										{	size.constraint.x += n1;	size.constraint.y += n2;	}
				void setAnchor(iConstrain e=CONSTRAIN_CENTER)						{	anchor = e;	}
				void setOrigin(iConstrain e=CONSTRAIN_CENTER)						{	origin = e;	}
				void exec()															{	execPos(gameVars->screen.half);	execSize(gameVars->screen.res);	}
				void exec(Props &c)													{	execPos(c.size/2.0f, c.pos, c.vPadding);	execSize(c.size, c.vPadding);	}
				Vector2f getScrollPos()												{
					Vector2f v;
					v.x = pos.x+scroll.getX();
					v.y = pos.y+scroll.getY();
					return v;
				}
				Vector2f getPos()													{	return Vector2f(pos.x, pos.y);	}
				Vector2f getSize()													{	return Vector2f(size.x, size.y);	}
				void setPadding(int i)												{	vPadding.top = i; vPadding.bottom = i; vPadding.left = i; vPadding.right = i; }
				void setPadding(int t, int b, int l, int r)							{	vPadding.top = t; vPadding.bottom = b; vPadding.left = l; vPadding.right = r; }
				void setPadding(Vector4i v)											{	vPadding = v; }
				void enablePadding(ePadding e=PADDING_POSITION)						{	eEnablePadding = e;	}
				void disablePadding()												{	eEnablePadding = PADDING_NONE;	}
				void setVisibility(bool b)											{	visibility = b;	}
				void enableToolTip()												{	toolTip.bShow = true;	}
				void disableToolTip()												{	toolTip.bShow = false;	}
				void setToolTip(std::string s)										{	toolTip.Text = s; toolTip.bShow = true;	}
				void autoWidth(bool b=true)											{	size.constraint.xAuto = b;	if(b) size.constraint.x = -1;	}
				void autoHeight(bool b=true)										{	size.constraint.yAuto = b;	if(b) size.constraint.y = -1;	}
				void setMinMaxWidth(int min, int max)								{	size.constraint.xMin = min; size.constraint.xMax = max;	}
				void setMinWidth(int i)												{	size.constraint.xMin = i;	}
				void setMaxWidth(int i)												{	size.constraint.xMax = i;	}
				void setMinMaxHeight(int min, int max)								{	size.constraint.yMin = min; size.constraint.yMax = max;	}
				void setMinHeight(int i)											{	size.constraint.yMin = i;	}
				void setMaxHeight(int i)											{	size.constraint.yMax = i;	}
				void setText(std::string s)											{	text = s;	}
				void setScrollable()												{	scroll.enable(true); }
				void resetScrollable()												{	scroll.enable(false); }
				void enableFocusLock()												{	bFocusLock = true; }
				void disableFocusLock()												{	bFocusLock = false; }

				Props() {
					bFocusLock			= true;
					text				= "";
					toolTip.bShow		= false;
					toolTip.Text		= "No ToolTip set!";
					toolTip.border		= 1;
					toolTip.radius		= 0;
					toolTip.padding		= 4;
					toolTip.round		= false;
					toolTip.showLabel	= true;

					scroll.makeLocal();

					size.constraint.xType = SIZE_CONSTRAINT_ABSOLUTE;
					size.constraint.x = 0.0f;

					size.constraint.yType = SIZE_CONSTRAINT_ABSOLUTE;
					size.constraint.y = 0.0f;

					origin = CONSTRAIN_CENTER;
					anchor = CONSTRAIN_CENTER;

					enablePadding(PADDING_POSITION);

					visibility	= true;

					setPos(0, 0);
					setWidth(0);
					setHeight(0);
					autoWidth(false);
					autoHeight(false);
					setMinMaxWidth(10, 250);
					setMinMaxHeight(10, 250);
				}

				Props(Props &src) {
					toolTip.bShow			= src.toolTip.bShow;
					toolTip.Text			= src.toolTip.Text;
					toolTip.border			= src.toolTip.border;
					toolTip.radius			= src.toolTip.radius;
					toolTip.padding			= src.toolTip.padding;
					toolTip.round			= src.toolTip.round;
					toolTip.showLabel		= src.toolTip.showLabel;
					toolTip.margin			= src.toolTip.margin;

					origin					= src.origin;
					anchor					= src.anchor;
					vPadding				= src.vPadding;
					visibility				= src.visibility;
					eEnablePadding			= src.eEnablePadding;
					text					= src.text;
					bFocusLock				= src.bFocusLock;

					scroll					= src.scroll;

					pos.x					= src.pos.x;
					pos.y					= src.pos.y;
					pos.constraint.x		= src.pos.constraint.x;
					pos.constraint.y		= src.pos.constraint.y;

					size.x					= src.size.x;
					size.y					= src.size.y;
					size.constraint.x		= src.size.constraint.x;
					size.constraint.xMin	= src.size.constraint.xMin;
					size.constraint.xMax	= src.size.constraint.xMax;
					size.constraint.xType	= src.size.constraint.xType;
					size.constraint.xAuto	= src.size.constraint.xAuto;
					size.constraint.y		= src.size.constraint.y;
					size.constraint.yMin	= src.size.constraint.yMin;
					size.constraint.yMax	= src.size.constraint.yMax;
					size.constraint.yType	= src.size.constraint.yType;
					size.constraint.yAuto	= src.size.constraint.yAuto;
				}

				// FIXME: assignment operator

				~Props() {
				}
		};

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// 			Object Options
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		/**
		 * \brief Allow object to be part of a group with restricted usage
		 *
		 */
		class Props_Addon_Group {
			FRIENDS;

			protected:
				int iGroup;

			public:
				//t_Group *iGroup;
				void setGroup(t_Group group)		{	iGroup = group.index;	}
				void clearGroup()					{	iGroup = 0;				}

				Props_Addon_Group() : iGroup(0) {}
		};

		/**
		 * \brief Object can be toggled
		 *
		 */
		class Props_Addon_Toggle {
			FRIENDS;

			protected:
				bool bToggle;

			public:
				//bool bToggle;
				void setToggle(bool b)									{	bToggle = b;		}
				Props_Addon_Toggle() : bToggle(false)/*, initialState(STATE_NONE)*/ {}
		};

		/**
		 * \brief Object has a stipple pattern
		 *
		 */
		class Props_Addon_Stipple {
			friend class Object::Window;

			public:
				Stipple_Pattern	* stipple;
				GUI_ColorBHA	stippleColor;
				bool bEnableStipple;

				void setStipple(bool b)										{ bEnableStipple = b; }
				void enableStipple()										{ bEnableStipple = true; }
				void disableStipple()										{ bEnableStipple = false; }
				void setStipplePattern(Stipple_Pattern *s)					{ stipple = s; bEnableStipple = true; }
				void setStippleColorB(Color *c)								{ stippleColor.base = c; }
				void setStippleColorH(Color *c)								{ stippleColor.highlight = c; }
				void setStippleColorA(Color *c)								{ stippleColor.active = c; }

				Props_Addon_Stipple() {
					bEnableStipple = false;
					stipple = &Core::stipple[Core::stipple.STIPPLE_SAND];
					stippleColor.base		= &gameVars->pallette.gui.window.stipple.base;
					stippleColor.highlight	= &gameVars->pallette.gui.window.stipple.hover;
					stippleColor.active		= &gameVars->pallette.gui.window.stipple.active;
				}

				// FIXME: copy constructor
				// FIXME: assignment operator
		};

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// 			Windows
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		class Props_Window :	virtual public Props,
								virtual public Props_Addon_Stipple {

			friend class Object::Window;
			friend class GUI;
			friend class GUI_Container;

			private:
				bool			bNoInput;

			public:
				GUI_ColorBHA	colorBack, colorBorder;

				bool			roundBorder;
				int				borderNormal, borderHover;
				int				radius;
				bool			bResizeRadius;
				bool			bScissor;

				void setBorder(int iNormal, int iHover)						{	borderNormal = iNormal; borderHover = iHover;	}
				void setRadius(int i)										{	radius = i;	}
				void setRoundBorder(bool b=true)							{	roundBorder = b;	}
				int  getRadius() 											{	return radius;	}
				bool getRoundBorder()										{	return roundBorder;	}
				void setScissor(bool b)										{	bScissor = b;	}
				void enableScissor()										{	bScissor = true;	}
				void disableScissor()										{	bScissor = false;	}
				void setResizeRadius(bool b=true)							{	bResizeRadius = b; }
				void setNoInput(bool b=true)								{	bNoInput = b;	}
				//void setScrollable(bool b)									{	scroll.bEnable = b;	}

				Props_Window() {
					bScissor				= true;
					bNoInput				= true;
					bResizeRadius			= true;

					roundBorder				= true;
					borderNormal			= 1;
					borderHover				= 1;
					radius					= 0;
					vPadding.top			= 0;
					vPadding.bottom			= 0;
					vPadding.left			= 0;
					vPadding.right			= 0;
					enablePadding(Core::GUI::PADDING_ALL);

					colorBack.base			= &Core::gameVars->pallette.gui.window.background.base;
					colorBack.highlight		= &Core::gameVars->pallette.gui.window.background.hover;
					colorBack.active		= &Core::gameVars->pallette.gui.window.background.active;

					colorBorder.base		= &Core::gameVars->pallette.gui.window.border.base;
					colorBorder.highlight	= &Core::gameVars->pallette.gui.window.border.hover;
					colorBorder.active		= &Core::gameVars->pallette.gui.window.border.active;
				}

				~Props_Window() {
				}
		};

		/**
		 *
		 */
		class Props_Addon_Background {
			public:
				bool bShowBackground;

				Props_Window background;

				void showBackground()										{	bShowBackground = true;		}
				void hideBackground()										{	bShowBackground = false;	}

				Props_Addon_Background() {
					bShowBackground	= true;
				}
		};

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// 			Windows
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		class Props_Container:	virtual public Props_Window,
								virtual public Props,
								virtual public Props_Addon_Stipple {
		};

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		//			Label
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		class Props_Label : public Props_Window {

			friend class Object::Label;

			public:
				GUI_ColorBHA	colorText;

				bool			bShowBackground;
				void showBackground()										{ bShowBackground = true;	}
				void hideBackground()										{ bShowBackground = false;	}

				Props_Label() {
					setMinMaxWidth(50, 200);

					bShowBackground				= false;
					setPadding(2);
					roundBorder					= true;
					radius						= 3;

					colorBack.base				= &Core::gameVars->pallette.gui.label.background.base;
					colorBack.highlight			= &Core::gameVars->pallette.gui.label.background.hover;
					colorBack.active			= &Core::gameVars->pallette.gui.label.background.active;

					colorBorder.base			= &Core::gameVars->pallette.gui.label.border.base;
					colorBorder.highlight		= &Core::gameVars->pallette.gui.label.border.hover;
					colorBorder.active			= &Core::gameVars->pallette.gui.label.border.active;

					colorText.base				= &Core::gameVars->pallette.gui.label.text.base;
					colorText.highlight			= &Core::gameVars->pallette.gui.label.text.hover;
					colorText.active			= &Core::gameVars->pallette.gui.label.text.active;
				}

				~Props_Label() {
				}
		};

		class Props_Addon_Label {
			public:
				bool			bShowLabel;

				Props_Label label;

				void showLabel()											{ bShowLabel = true; }
				void hideLabel()											{ bShowLabel = false; }

				Props_Addon_Label() {
					bShowLabel		= false;
					label.setPos(0, 0);

					label.autoWidth();
					label.autoHeight();
				}
		};

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		//			Field (Text/Numeric)
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		class Props_Field : public Props_Window {

			template <class T>
			friend class Object::Field;

			public:
				GUI_ColorBHA	colorText;

				bool			bNumeric,
								bEditable;
				int				precision;
				float			minValue,
								maxValue;

				void setPrecision(int i)									{ precision = i; }
				void setMinMax(float min, float max)						{ minValue = min; maxValue = max; }
				void setMinMax(Vector2f v)									{ minValue = v.x; maxValue = v.y; }
				void setMin(float f)										{ minValue = f; }
				void setMax(float f)										{ maxValue = f; }
				void setEditable(bool b=true)								{ bEditable = b; }


				Props_Field() {
					bNumeric					= false;
					precision					= 3;
					bEditable					= true;
					minValue					= INT_MIN;
					maxValue					= INT_MAX;

					colorText.base				= &Core::gameVars->pallette.gui.field.text.base;
					colorText.highlight			= &Core::gameVars->pallette.gui.field.text.hover;
					colorText.active			= &Core::gameVars->pallette.gui.field.text.active;

					setPadding(2);
					setMinMaxWidth(10, 250);
					radius						= 0;
					roundBorder					= false;

					colorBack.base				= &Core::gameVars->pallette.gui.field.background.base;
					colorBack.highlight			= &Core::gameVars->pallette.gui.field.background.hover;
					colorBack.active			= &Core::gameVars->pallette.gui.field.background.active;

					colorBorder.base			= &Core::gameVars->pallette.gui.field.border.base;
					colorBorder.highlight		= &Core::gameVars->pallette.gui.field.border.hover;
					colorBorder.active			= &Core::gameVars->pallette.gui.field.border.active;
				}

//				Props_Field& operator=(const Props_Field &src) {
//					bNumeric					= src.bNumeric;
//					precision					= src.precision;
//					bEditable					= src.bEditable;
//					minValue					= src.minValue;
//					maxValue					= src.maxValue;
//
//					colorText.base				= src.colorText.base;
//					colorText.highlight			= src.colorText.highlight;
//					colorText.active			= src.colorText.active;
//
//					radius						= src.radius;
//					roundBorder					= src.roundBorder;
//
//					colorBack.base				= src.colorBack.base;
//					colorBack.highlight			= src.colorBack.highlight;
//					colorBack.active			= src.colorBack.active;
//
//					colorBorder.base			= src.colorBorder.base;
//					colorBorder.highlight		= src.colorBorder.highlight;
//					colorBorder.active			= src.colorBorder.active;
//
//					// TODO:
//					//Props_Window::operator=()
//					return *this;
//				}

				~Props_Field() {
				}
		};

		class Props_Addon_Field {
			public:
				bool			bShowField;

				Props_Field field;

				void showField()											{ bShowField = true; }
				void hideField()											{ bShowField = false; }

				Props_Addon_Field() {
					bShowField		= false;
					field.setPos(0, 0);
					field.setMinMaxWidth(10, 250);
				}

				Props_Addon_Field& operator=(const Props_Addon_Field &src) {
					bShowField		= src.bShowField;
					field			= src.field;
					return *this;
				}

//				Props_Addon_Field(const Props_Addon_Field &src) {
//					bShowField		= false;
//					field.setPos(0, 0);
////					field.disablePadding();
//					field.setMinMaxWidth(10, 250);
//				}
		};

		/** ******************************************************************************************************************************
		 *  \class Slider
		 *  \brief Creates a slider and control with optional label and field for value editing
		 *
		 *
		 *
		 * ****************************************************************************************************************************** */
		class Props_Slider :	virtual public Props_Window,
									public Props_Addon_Label,
									public Props_Addon_Field {

			template <class T>
			friend class Object::Slider;

			public:
				eSlider 	orientation;
				float		minValue,
					  	  	maxValue,
							scrollSpeed;
				int			precision,
							iFieldSize;
				bool 		bExactSize;
				Vector3f	vStep;

				Props_Window control;

				void setOrientation(eSlider e)								{ orientation = e; }
				void setMinMax(Vector2f v)									{ minValue = v.x; maxValue = v.y; }
				void setMinMax(float min, float max)						{ minValue = min; maxValue = max; }
				void setPrecision(int i)									{ precision = i; }
				void setFieldSizeAbsolute(int i)							{ bExactSize = true; iFieldSize = i; }		// iFieldSize = exact size
				void setFieldSizeRelative(int i)							{ bExactSize = false; iFieldSize = i; }		// iFieldSize = minimum size
				void setScrollSpeed(float f)								{ scrollSpeed = f; }
				void setStep(float f)										{ vStep[0] = f; vStep[1] = f; vStep[2] = f; }
				void setStep(float min, float std, float max)				{ vStep[0] = min; vStep[1] = std; vStep[2] = max; }
				void swapOrientation() {
					switch(orientation) {
						case SLIDER_HORIZONTAL:	orientation = SLIDER_VERTICAL;		break;
						case SLIDER_VERTICAL:	orientation = SLIDER_HORIZONTAL;	break;
					}

					{
						int x				= size.constraint.x,
							y				= size.constraint.y;
						eSizeConstraint xt	= size.constraint.xType,
										yt	= size.constraint.yType;

						setWidth(y, yt);
						setHeight(x, xt);
					}

					{
						int x				= control.size.constraint.x,
							y				= control.size.constraint.y;
						eSizeConstraint xt	= control.size.constraint.xType,
										yt	= control.size.constraint.yType;
						control.setWidth(y, yt);
						control.setHeight(x, xt);
					}

					{
						int t = vPadding.top,
							b = vPadding.bottom,
							l = vPadding.left,
							r = vPadding.right;
						setPadding(l, r, t, b);
					}
				}

				Props_Slider(eSlider orientation=SLIDER_HORIZONTAL) {
					this->orientation	= orientation;
					minValue			= 0.0f;
					maxValue			= 100.0f;
					scrollSpeed			= 1.0f;
					vStep[0]			= 1.0f;
					vStep[1]			= 5.0f;
					vStep[2]			= 10.0f;
					precision			= 3;

					// Label
					bShowLabel			= false;
					label.setOrigin(CONSTRAIN_LEFT);
					label.setAnchor(CONSTRAIN_RIGHT);
					label.setPadding(2);
					label.setPos(0, 0);
					label.setMinWidth(0);
					label.colorText.base = &Core::gameVars->pallette.gui.slider.text.base;
					label.colorText.highlight = &Core::gameVars->pallette.gui.slider.text.hover;
					label.colorText.active = &Core::gameVars->pallette.gui.slider.text.active;

					// Field
					bShowField			= false;
					field.setOrigin(CONSTRAIN_RIGHT);
					field.setAnchor(CONSTRAIN_LEFT);
					field.setPadding(2);
					field.setPos(0, 0);
					field.colorText.base = &Core::gameVars->pallette.gui.slider.text.base;
					field.colorText.highlight = &Core::gameVars->pallette.gui.slider.text.hover;
					field.colorText.active = &Core::gameVars->pallette.gui.slider.text.active;

					// Slider
					bExactSize			= false;
					iFieldSize			= 80;
					if(orientation==SLIDER_HORIZONTAL) setPadding(-8, -8, -5, -5);
					else setPadding(-5, -5, -8, -8);
					setBorder(1, 1);
					setRadius(0);
					colorBack.base = &Core::gameVars->pallette.gui.slider.bar.base;
					colorBack.highlight = &Core::gameVars->pallette.gui.slider.bar.hover;
					colorBack.active = &Core::gameVars->pallette.gui.slider.bar.active;

					colorBorder.base = &Core::gameVars->pallette.gui.slider.barBorder.base;
					colorBorder.highlight = &Core::gameVars->pallette.gui.slider.barBorder.hover;
					colorBorder.active = &Core::gameVars->pallette.gui.slider.barBorder.active;

					// Control Handle
					if(orientation==SLIDER_HORIZONTAL) {
						control.setWidth(8, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
						control.setHeight(16, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
					}
					else {
						control.setWidth(16, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
						control.setHeight(8, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
					}
					control.setBorder(1, 1);
					control.setRadius(0);
					control.colorBack.base = &Core::gameVars->pallette.gui.slider.control.base;
					control.colorBack.highlight = &Core::gameVars->pallette.gui.slider.control.hover;
					control.colorBack.active = &Core::gameVars->pallette.gui.slider.control.active;

					control.colorBorder.base = &Core::gameVars->pallette.gui.slider.controlBorder.base;
					control.colorBorder.highlight = &Core::gameVars->pallette.gui.slider.controlBorder.hover;
					control.colorBorder.active = &Core::gameVars->pallette.gui.slider.controlBorder.active;
				}

				~Props_Slider() {
				}
		};

		class Props_Addon_Slider {
			public:
				bool bShowSlider;
				Props_Slider slider;

				void showSlider()											{ bShowSlider = true; }
				void hideSlider()											{ bShowSlider = false; }

				Props_Addon_Slider(eSlider orientation) {
					slider = Props_Slider(orientation);
					bShowSlider		= false;
				}
		};


		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// 			Buttons
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		class Props_Button :	public Props_Window,
								virtual public Props_Addon_Group,
								virtual public Props_Addon_Toggle/*,
								virtual public Props_Addon_DataSet*/ {

			friend class Object::Button;

			public:
				GUI_ColorBHA colorText;

				iConstrain		eLabelAnchor;
				eButtonType		buttonType;
				int				debounceTime;

				void setLabelAnchor(eConstrain e)	{	eLabelAnchor = e;	}
				void setButtonType(eButtonType e)	{	buttonType = e;		}
				void setDebounceTime(int i)			{	debounceTime = i;	}

				Props_Button() {
					setNoInput(true);
					buttonType					= BUTTON_ONESHOT;
					eLabelAnchor				= CONSTRAIN_CENTER;
					debounceTime				= 500;

					colorBack.base				= &Core::gameVars->pallette.gui.button.background.base;
					colorBack.highlight			= &Core::gameVars->pallette.gui.button.background.hover;
					colorBack.active			= &Core::gameVars->pallette.gui.button.background.active;

					colorBorder.base			= &Core::gameVars->pallette.gui.button.border.base;
					colorBorder.highlight		= &Core::gameVars->pallette.gui.button.border.hover;
					colorBorder.active			= &Core::gameVars->pallette.gui.button.border.active;

					colorText.base				= &Core::gameVars->pallette.gui.button.text.base;
					colorText.highlight			= &Core::gameVars->pallette.gui.button.text.hover;
					colorText.active			= &Core::gameVars->pallette.gui.button.text.active;
				}

				~Props_Button() {
				}

//				Props_Button &operator=(const Props_Button &src) {
//					eLabelAnchor	= src.eLabelAnchor;
//					buttonType		= src.buttonType;
//					debounceTime	= src.debounceTime;
//					//color			= src.color;
//
//					this->Props_Window::operator =(src);
//
//					return *this;
//				}
		};

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// 			Text
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		class Props_Text : virtual public Props {

			friend class Core::_TextSys;
			friend class GUI::Object::Text;
			friend class GUI::Object::TextEdit;
			friend class GUI::Object::TextArea;
			friend class GUI::Object::ToolTip;
			friend class Props_TextArea;

			private:
				struct Colors {
					private:
						struct {
							GUI_ColorBHA	text;
						} data;

					public:
						GUI_ColorBHA &text()	{ return data.text; }

					Colors() {}
				} color;

				std::shared_ptr<std::string> bufferPtr;
				bool			bLocalBuffer;
				float			scrollPosition;
				int				iMaxLines;
				int				iCursorPosition;
				bool			bEnableCursor;
				bool			bWordWrap;
				int				iLineSpacing;
				Vector2i		limit;
				int				iUpChars;
				int				iCursorChars;
				int				iDownChars;
				bool			bOverwrite;

			public:
				void scrollUp(int i=1)										{ scrollPosition = std::fmax(scrollPosition-i, 0); }
				void scrollDown(int i=1)									{ scrollPosition += i; }
				void setWordWrap(bool b)									{ bWordWrap = b;	}
				void setLineSpacing(int i)									{ iLineSpacing = i;	}
				void setBuffer(std::shared_ptr<std::string> s)				{ bLocalBuffer = false; bufferPtr = s;	}
				void setBuffer(std::string s)								{ bLocalBuffer = true; bufferPtr = std::make_shared<std::string>(s);	}

				Props_Text() {
					scrollPosition			= 0;
					iMaxLines				= 256;
					bLocalBuffer			= false;
					bWordWrap				= true;
					iLineSpacing			= Core::gameVars->font.spacing;
					bOverwrite				= false;

					iUpChars				= 0;
					iCursorChars			= 0;
					iDownChars				= 0;

					bEnableCursor			= false;
					iCursorPosition			= 0;

					color.text().base			= &Core::gameVars->pallette.gui.textArea.text.base;
					color.text().highlight		= &Core::gameVars->pallette.gui.textArea.text.hover;
					color.text().active			= &Core::gameVars->pallette.gui.textArea.text.active;

					autoWidth();
					autoHeight();
				}

				~Props_Text() {

				}
		};


		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// 			Text Area
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		class Props_TextArea :	public Props_Window,
								public Props_Addon_Label {

			friend class Object::TextArea;
			friend class Object::TextEdit;
			friend class Object::ToolTip;

			private:

			public:
				Props_Text	text;
				bool			enableScrolling;
				int				iScrollSize;
				void setScrolling(bool b)									{ enableScrolling = b; }
				void setScrollSize(int i)									{ iScrollSize = i; }
				void setLineSpacing(int i)									{ text.iLineSpacing = i;	}

				void setBuffer(std::shared_ptr<std::string> s) {
					text.bLocalBuffer = false;
					text.bufferPtr = s;
				}

				void setBuffer(std::string s) {
					text.bLocalBuffer = true;
					text.bufferPtr = std::make_shared<std::string>(s);
				}

				Props_TextArea() {
					enableScrolling				= false;
					iScrollSize					= 20;

					setBorder(1, 1);
					setRadius(0);
					setPadding(0);

					setScrolling(false);
					setScrollSize(20);
					text.setPadding(4);
					text.enablePadding(PADDING_ALL);

					hideLabel();
					label.setOrigin(CONSTRAIN_TOP_LEFT);
					label.setAnchor(CONSTRAIN_BOTTOM_LEFT);
					label.disablePadding();

					colorBack.base				= &Core::gameVars->pallette.gui.textArea.background.base;
					colorBack.highlight			= &Core::gameVars->pallette.gui.textArea.background.hover;
					colorBack.active			= &Core::gameVars->pallette.gui.textArea.background.active;

					colorBorder.base			= &Core::gameVars->pallette.gui.textArea.border.base;
					colorBorder.highlight		= &Core::gameVars->pallette.gui.textArea.border.hover;
					colorBorder.active			= &Core::gameVars->pallette.gui.textArea.border.active;
				}
		};

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// 			Color Swatch
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		class Props_ColorSwatch :	virtual public Props_Window,
										virtual public Props_Addon_Background,
										public Props_Addon_Label,
										public Props_Addon_Slider {

			friend class Object::ColorSwatch;

			public:
				GUI_ColorBHA	colorSwatchBorder;

				int  getRadius() 											{	return radius;	}
				bool getRoundBorder()										{	return roundBorder;	}

				Props_ColorSwatch() : Props_Addon_Slider(SLIDER_HORIZONTAL) {
					colorSwatchBorder.base		= &Core::gameVars->pallette.gui.swatch.border.base;

					showBackground();
					background.colorBack.base = &Core::colors[colors().White];

					bShowSlider		= true;
					slider.setOrigin(CONSTRAIN_RIGHT);
					slider.setAnchor(CONSTRAIN_LEFT);
					slider.setPos(30, 0);
					slider.setWidth(200);
					slider.setMinMax(0.0f, 1.0f);
					slider.setStep(0.001f, 0.01f, 0.1f);
					slider.setPadding(-4);
					slider.setPrecision(2);
					slider.setHeight(4, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
					slider.control.setWidth(5, SIZE_CONSTRAINT_ABSOLUTE);

					slider.showField();
					slider.field.setPadding(2);
					slider.setFieldSizeAbsolute(50);

					slider.showLabel();
					slider.label.setOrigin(CONSTRAIN_LEFT);
					slider.label.setAnchor(CONSTRAIN_RIGHT);
					slider.label.setPadding(2);

					bShowLabel		= true;
					label.setOrigin(CONSTRAIN_TOP);
					label.setAnchor(CONSTRAIN_BOTTOM);
					label.setPos(0, 0);

					roundBorder = false;
					radius = 0;
					setPadding(0);
				}

				~Props_ColorSwatch() {
				}
		};

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		//			Checkbox
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		class Props_CheckBox :	virtual public Props_Window,
										virtual public Props_Addon_Group,
										virtual public Props_Addon_Toggle,
										virtual public Props_Addon_Label {

			friend class Object::CheckBox;

			private:
				Props_Window check;

			public:
				Props_CheckBox() {
					bToggle = true;

					label.setOrigin(CONSTRAIN_LEFT);
					label.setAnchor(CONSTRAIN_RIGHT);
					label.setPadding(2);
					label.setPos(-10, 0);
					label.autoWidth();
					label.autoHeight();
					showLabel();

					setPadding(0);
					setBorder(1, 1);
					setWidth(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
					setHeight(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
					setRadius(10);

					colorBack.base					= &Core::gameVars->pallette.gui.checkBox.background.base;
					colorBack.highlight				= &Core::gameVars->pallette.gui.checkBox.background.hover;
					colorBack.active				= &Core::gameVars->pallette.gui.checkBox.background.base;

					colorBorder.base				= &Core::gameVars->pallette.gui.checkBox.border.base;
					colorBorder.highlight			= &Core::gameVars->pallette.gui.checkBox.border.hover;
					colorBorder.active				= &Core::gameVars->pallette.gui.checkBox.border.active;

					check.colorBack.base			= &Core::gameVars->pallette.gui.checkBox.background.active;
					check.colorBack.highlight		= &Core::gameVars->pallette.gui.checkBox.background.active;
					check.colorBack.active			= &Core::gameVars->pallette.gui.checkBox.background.active;

					check.colorBorder.base			= &Core::gameVars->pallette.gui.checkBox.border.base;
					check.colorBorder.highlight		= &Core::gameVars->pallette.gui.checkBox.border.hover;
					check.colorBorder.active		= &Core::gameVars->pallette.gui.checkBox.border.active;
				}

				~Props_CheckBox() {
				}
		};

		/** ******************************************************************************************************************************
		 *  \class Icons
		 *  \brief Special form of button using an image atlas source
		 *
		 *	Acts just like a button, even has a duplicate of a buttons code with the addition
		 *	of drawing an icon. It does not inherit from a button because that would bring
		 *	some extra settings not used in icons (text).
		 *
		 *	Padding defines how the icon is drawn inside the given dimensions. Therefore padding
		 *	cannot be used to determine field position.
		 *
		 * ****************************************************************************************************************************** */
		class Props_Icon :	public Props,
									virtual public Props_Addon_Background,
									virtual public Props_Addon_Label,
									virtual public Props_Addon_Group,
									virtual public Props_Addon_Toggle {

			friend class Object::Icon;

			public:
				struct Colors {
					private:
						struct {
							GUI_ColorBHA	icon;
						} data;

					public:
						GUI_ColorBHA &icon()	{ return data.icon; }

					Colors() {}
				} color;

				struct {	int base, active, highlight;	} iconID;
				eButtonType		buttonType;
				int				debounceTime;
				std::string		iconAtlas;

				void setIconIDs			(int b, int h, int a)				{	iconID.base = b; iconID.highlight = h; iconID.active = a;  	}
				void setButtonType		(eButtonType e)						{	buttonType = e;		}
				void setDebounceTime	(int i)								{	debounceTime = i;	}
				void setImage			(std::string s)						{	iconAtlas = s;	}

				Props_Icon() {
					buttonType				= BUTTON_ONESHOT;
					debounceTime			= 500;
					iconAtlas				= "TestPattern.png";
					iconID.base				= 0;
					iconID.highlight		= 1;
					iconID.active			= 2;
					setPadding(2);

					color.icon().base			= &Core::gameVars->pallette.gui.icon.base;
					color.icon().highlight	= &Core::gameVars->pallette.gui.icon.hover;
					color.icon().active		= &Core::gameVars->pallette.gui.icon.active;

					showBackground();
					background.setBorder(1, 3);
					background.setRadius(0);
					background.colorBack.base = &gameVars->pallette.gui.icon.background.base;
					background.colorBack.highlight = &gameVars->pallette.gui.icon.background.hover;
					background.colorBack.active = &gameVars->pallette.gui.icon.background.active;
					background.colorBorder.base = &gameVars->pallette.gui.icon.border.base;
					background.colorBorder.highlight = &gameVars->pallette.gui.icon.border.hover;
					background.colorBorder.active = &gameVars->pallette.gui.icon.border.active;

					showLabel();
					label.setOrigin(Core::GUI::CONSTRAIN_TOP_RIGHT);
					label.setAnchor(Core::GUI::CONSTRAIN_TOP_LEFT);
					label.setPos(10, 0);
					label.disablePadding();
				}

				~Props_Icon() {
				}
		};

		/** ******************************************************************************************************************************
		 *  \class Sprite
		 *  \brief Simple image, no user interaction
		 *
		 *
		 *
		 * ****************************************************************************************************************************** */
		class Props_Sprite :	public Props_Window,
								virtual public Props_Addon_Group {

			friend class Object::Sprite;

			public:
				GUI_ColorBHA	colorSprite;

				std::string		spriteImage;

				void setImage			(std::string s)						{	spriteImage = s;	}

				Props_Sprite() {
					enablePadding(PADDING_ALL);

					spriteImage				= "TestPattern.png";

					colorBack.base			= &Core::gameVars->pallette.gui.sprite.background.base;
					colorBack.highlight		= &Core::gameVars->pallette.gui.sprite.background.hover;
					colorBack.active		= &Core::gameVars->pallette.gui.sprite.background.active;

					colorBorder.base		= &Core::gameVars->pallette.gui.sprite.border.base;
					colorBorder.highlight	= &Core::gameVars->pallette.gui.sprite.border.hover;
					colorBorder.active		= &Core::gameVars->pallette.gui.sprite.border.active;

					colorSprite.base		= &Core::gameVars->pallette.gui.sprite.base;
//					colorSprite.highlight	= &Core::gameVars->pallette.gui.sprite.hover;
//					colorSprite.active		= &Core::gameVars->pallette.gui.sprite.active;
				}

				~Props_Sprite() {
				}
		};

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		//			ProgressBar
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// FIXME: Update window constraints to be separate (background component)
		// TODO: [Properties] NoProgress: Border, radius, stipple pattern, enable stipple; Progress: border, height(normally 100% relative); Field: show, width
		class Props_ProgressBar : public Props_Window {
			public:
				Props_Field field;
				Props_Window empty, fill;	// TODO
				bool		bShowField;		// TODO

				Props_ProgressBar() {
					autoWidth(false);
					autoHeight(false);
					setPadding(2);
					roundBorder						= true;
					radius							= 3;
					colorBack.base					= &Core::gameVars->pallette.gui.progressBar.background.base;
					colorBack.highlight				= &Core::gameVars->pallette.gui.progressBar.background.base;
					colorBack.active				= &Core::gameVars->pallette.gui.progressBar.background.base;
					colorBorder.base				= &Core::gameVars->pallette.gui.progressBar.background.border;
					colorBorder.highlight			= &Core::gameVars->pallette.gui.progressBar.background.border;
					colorBorder.active				= &Core::gameVars->pallette.gui.progressBar.background.border;

					empty.setOrigin(CONSTRAIN_CENTER);
					empty.setAnchor(CONSTRAIN_CENTER);
					empty.setWidth(100, SIZE_CONSTRAINT_RELATIVE);
					empty.setHeight(100, SIZE_CONSTRAINT_RELATIVE);
					empty.setBorder(1, 1);
					empty.setRadius(0);
					empty.setPadding(1);
					empty.enablePadding(Core::GUI::PADDING_ALL);
					empty.disableScissor();
					empty.setStipplePattern(&Core::stipple[Core::stipple.STIPPLE_ANSI31]);
					empty.enableStipple();
					empty.colorBack.base			= &Core::gameVars->pallette.gui.progressBar.progress.empty;
					empty.colorBack.highlight		= &Core::gameVars->pallette.gui.progressBar.progress.empty;
					empty.colorBack.active			= &Core::gameVars->pallette.gui.progressBar.progress.empty;
					empty.colorBorder.base			= &Core::gameVars->pallette.gui.progressBar.progress.border;
					empty.colorBorder.highlight		= &Core::gameVars->pallette.gui.progressBar.progress.border;
					empty.colorBorder.active		= &Core::gameVars->pallette.gui.progressBar.progress.border;

					fill.setOrigin(CONSTRAIN_LEFT);
					fill.setAnchor(CONSTRAIN_LEFT);
					fill.setWidth(0, SIZE_CONSTRAINT_RELATIVE);
					fill.setHeight(100, SIZE_CONSTRAINT_RELATIVE);
					fill.setBorder(0, 0);
					fill.setRadius(0);
					fill.setPadding(0);
					fill.setResizeRadius(false);
					fill.colorBack.base				= &Core::gameVars->pallette.gui.progressBar.progress.fill;
					fill.colorBack.highlight		= &Core::gameVars->pallette.gui.progressBar.progress.fill;
					fill.colorBack.active			= &Core::gameVars->pallette.gui.progressBar.progress.fill;
					fill.colorBorder.base			= &Core::gameVars->pallette.gui.progressBar.progress.border;
					fill.colorBorder.highlight		= &Core::gameVars->pallette.gui.progressBar.progress.border;
					fill.colorBorder.active			= &Core::gameVars->pallette.gui.progressBar.progress.border;

					field.setOrigin(CONSTRAIN_CENTER);
					field.setAnchor(CONSTRAIN_CENTER);
					field.autoWidth();
					field.autoHeight();
					field.setEditable(false);
					field.setPadding(5);
					field.setMinWidth(3*Core::gameVars->font.vSize.x+5+5);

					bShowField						= true;
				}

				~Props_ProgressBar() {
				}
		};

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		//			ComboBox
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		class Props_ComboBox : virtual public Props_Button /*virtual public Props*/ {

			friend class Object::Label;

			public:
				Props_Window	itemList;		///< The container for additional items that show up when down arrow pressed
				Props_Button 	itemButton,		///< Style information for each item in the item list
								scrollButton;	///< Style information for scroll buttons

				bool	bAutoHide;
				int		iListLength;

				void setAutoHide(bool b=true)	{	bAutoHide = b;	}
				void setListLength(int i=5)		{	iListLength = i; }

				Props_ComboBox() {
					bAutoHide = true;
					iListLength = 5;

					setOrigin(Core::GUI::CONSTRAIN_TOP);
					setAnchor(Core::GUI::CONSTRAIN_TOP);

					setButtonType(BUTTON_TOGGLE);

					colorBack.base			= &Core::colors[Core::colors().Gray80];
					colorBack.highlight		= &Core::colors[Core::colors().White];
					colorBack.active		= &Core::colors[Core::colors().White];

					colorBorder.base		= &Core::colors[Core::colors().Black];
					colorBorder.highlight	= &Core::colors[Core::colors().Black];
					colorBorder.active		= &Core::colors[Core::colors().Black];

					colorText.base			= &Core::colors[Core::colors().Black];
					colorText.highlight		= &Core::colors[Core::colors().Black];
					colorText.active		= &Core::colors[Core::colors().Black];

					setBorder(1, 1);
					setResizeRadius(5);
					setPadding(5);
					setWidth(150, GUI::SIZE_CONSTRAINT_ABSOLUTE);
					setHeight(20, GUI::SIZE_CONSTRAINT_ABSOLUTE);

					// selectedItem will be parent
					itemList.setOrigin(Core::GUI::CONSTRAIN_BOTTOM);
					itemList.setAnchor(Core::GUI::CONSTRAIN_TOP);
					itemList.setNoInput(false);
					itemList.disablePadding();
					itemList.colorBack.base			= &Core::colors[Core::colors().Gray80];
					itemList.colorBack.highlight	= &Core::colors[Core::colors().White];
					itemList.colorBack.active		= &Core::colors[Core::colors().Yellow];

					itemList.colorBorder.base		= &Core::colors[Core::colors().Black];
					itemList.colorBorder.highlight	= &Core::colors[Core::colors().Black];
					itemList.colorBorder.active		= &Core::colors[Core::colors().Black];

					itemList.setBorder(1, 1);
					itemList.setResizeRadius(5);
					itemList.setPadding(5);
					itemList.setWidth(150, GUI::SIZE_CONSTRAINT_ABSOLUTE);
					itemList.setHeight(20, GUI::SIZE_CONSTRAINT_ABSOLUTE);	// Size set automatically later

					// Settings for ALL items in list
					itemButton.setOrigin(Core::GUI::CONSTRAIN_TOP);
					itemButton.setAnchor(Core::GUI::CONSTRAIN_TOP);
					itemButton.setButtonType(BUTTON_TOGGLE);

					itemButton.colorBack.base				= &Core::colors[Core::colors().Pale_aqua];
					itemButton.colorBack.highlight		= &Core::colors[Core::colors().Yellow];
					itemButton.colorBack.active			= &Core::colors[Core::colors().Green];

					itemButton.colorBorder.base			= &Core::colors[Core::colors().Black];
					itemButton.colorBorder.highlight		= &Core::colors[Core::colors().Black];
					itemButton.colorBorder.active			= &Core::colors[Core::colors().Black];

					itemButton.colorText.base				= &Core::colors[Core::colors().Black];
					itemButton.colorText.highlight		= &Core::colors[Core::colors().Black];
					itemButton.colorText.active			= &Core::colors[Core::colors().Black];

					itemButton.setBorder(0, 1);
					itemButton.setResizeRadius(0);
					itemButton.setPadding(2);
					itemButton.setWidth(100, GUI::SIZE_CONSTRAINT_RELATIVE);
					itemButton.setHeight(20, GUI::SIZE_CONSTRAINT_ABSOLUTE);

					// Settings for scroll buttons
					scrollButton.setOrigin(Core::GUI::CONSTRAIN_TOP);
					scrollButton.setAnchor(Core::GUI::CONSTRAIN_TOP);
					scrollButton.setButtonType(BUTTON_DEBOUNCE);

					scrollButton.colorBack.base			= &Core::colors[Core::colors().Gray40];
					scrollButton.colorBack.highlight		= &Core::colors[Core::colors().Gray60];
					scrollButton.colorBack.active			= &Core::colors[Core::colors().Green];

					scrollButton.colorBorder.base			= &Core::colors[Core::colors().Black];
					scrollButton.colorBorder.highlight	= &Core::colors[Core::colors().Black];
					scrollButton.colorBorder.active		= &Core::colors[Core::colors().Black];

					scrollButton.colorText.base			= &Core::colors[Core::colors().Black];
					scrollButton.colorText.highlight		= &Core::colors[Core::colors().Black];
					scrollButton.colorText.active			= &Core::colors[Core::colors().Black];

					scrollButton.setBorder(0, 1);
					scrollButton.setResizeRadius(0);
					scrollButton.setPadding(1);
					scrollButton.setWidth(100, GUI::SIZE_CONSTRAINT_RELATIVE);
					scrollButton.setHeight(12, GUI::SIZE_CONSTRAINT_ABSOLUTE);
				}

				~Props_ComboBox() {
				}
		};

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// 			General Functions
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		void Props::execPos(Vector2f cHalf, Vector2f oPos, Vector4i vPad) {
			// Default position, based on center. (0, 0) is center of screen.
			pos.x = pos.constraint.x+oPos.x;
			pos.y = pos.constraint.y+oPos.y;

			if(eEnablePadding&PADDING_POSITION) {

				if(origin&CONSTRAIN_LEFT)									pos.x -= (cHalf.x - vPad.left);
				else if(origin&CONSTRAIN_RIGHT)								pos.x += (cHalf.x - vPad.right);
				else if(size.constraint.xType == SIZE_CONSTRAINT_RELATIVE)	pos.x += (vPad.left-vPad.right)/2.0f;

				if(origin&CONSTRAIN_TOP)									pos.y += (cHalf.y - vPad.top);
				else if(origin&CONSTRAIN_BOTTOM)							pos.y -= (cHalf.y - vPad.bottom);
				else if(size.constraint.yType == SIZE_CONSTRAINT_RELATIVE)	pos.y += (vPad.bottom-vPad.top)/2.0f;
			}
			else {
				if(origin&CONSTRAIN_LEFT)				pos.x -= cHalf.x;
				else if(origin&CONSTRAIN_RIGHT)			pos.x += cHalf.x;

				if(origin&CONSTRAIN_TOP)				pos.y += cHalf.y;
				else if(origin&CONSTRAIN_BOTTOM)		pos.y -= cHalf.y;
			}
		}

		void Props::execSize(Vector2f cSize, Vector4i vPad) {

			/*
			 * Constrain size to padding unless padding is negative.
			 * If padding is negative then object is assumed to be anchored outside and padding no longer makes sense for sizeing
			 */
			size.x = 0;
			size.y = 0;

			if(eEnablePadding&PADDING_SIZE) {
				switch (size.constraint.xType) {
					case SIZE_CONSTRAINT_RELATIVE:	size.x = (((float)size.constraint.x/100) * (cSize.x-(vPad.left+vPad.right)));	break;
					default:						size.x = size.constraint.x;
				}

				switch (size.constraint.yType) {
					case SIZE_CONSTRAINT_RELATIVE:	size.y = (((float)size.constraint.y/100) * (cSize.y-(vPad.top+vPad.bottom)));	break;
					default:						size.y = size.constraint.y;
				}
			}
			else {
				switch (size.constraint.xType) {
					case SIZE_CONSTRAINT_ABSOLUTE:	size.x = size.constraint.x;	break;
					default:						size.x = ((float)size.constraint.x/100) * cSize.x;
				}

				switch (size.constraint.yType) {
					case SIZE_CONSTRAINT_ABSOLUTE:	size.y = size.constraint.y;	break;
					default:						size.y = ((float)size.constraint.y/100) * cSize.y;
				}
			}

			// Left/Right
			if(anchor&CONSTRAIN_TOP)		pos.y -= (size.y/2.0f);
			if(anchor&CONSTRAIN_BOTTOM)		pos.y += (size.y/2.0f);
			if(anchor&CONSTRAIN_LEFT)		pos.x += (size.x/2.0f);
			if(anchor&CONSTRAIN_RIGHT)		pos.x -= (size.x/2.0f);

			// If an odd size, make even for pixel alignment
			// This is ABSOLUTELY necessary to prevent artifacts, especially from window borders
//			if(fmod(size.x, 2.0f)>0.0f) size.x += 1.0f;
//			if(fmod(size.y, 2.0f)>0.0f) size.y += 1.0f;

		}




	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_CONSTRAINTS_H_ */
