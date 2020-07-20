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

namespace Core {
	/** ******************************************************************************************************************************
	 *	\namespace GUI
	 *
	 * Creates GUI instances for particular objects that can be
	 * used as a building block for a full GUI.
	 * ****************************************************************************************************************************** */
	namespace GUI {

		// Forward declarations for freinds
		namespace Object {
			class Window;
			class Label;
			class ToolTip;
			template <class T>class Field;
			class Button;
			template <class T>class Slider;
			class Text;
			class TextArea;
			class TextEdit;
			class ColorSwatch;
			class CheckBox;
			class Icon;
			class Sprite;
			class ProgressBar;
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
		enum eObjectState  {	STATE_NONE		= 0,
								STATE_HOVER		= 2,
								STATE_ACTIVE	= 4,
								STATE_DISABLED	= 8,
								STATE_UPDATE	= 16,
								STATE_NODRAW	= 32
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
		};

		struct GUI_ColorH {
			Color	* highlight;
			GUI_ColorH()						{	highlight = nullptr;	}
			GUI_ColorH(const GUI_ColorH *c)		{	highlight = c->highlight;	}
			GUI_ColorH(Color *h)				{	highlight = h;	}
		};

		struct GUI_ColorA {
			Color	* active;
			GUI_ColorA()						{	active = nullptr;	}
			GUI_ColorA(const GUI_ColorA *c)		{	active = c->active;	}
			GUI_ColorA(Color *a)				{	active = a;	}
		};

		// Generic and Highlight only
		struct GUI_ColorBH : public GUI_ColorB, public GUI_ColorH {
			GUI_ColorBH()							{	base = nullptr;	highlight = nullptr;	}
			GUI_ColorBH(const GUI_ColorBH *c)		{	base = c->base; highlight = c->highlight;	}
			GUI_ColorBH(Color *b, Color *h)	{	base = b;	highlight = h;	}
		};

		// Generic, highlight, and active colors
		struct GUI_ColorBHA : public GUI_ColorB, public GUI_ColorH, public GUI_ColorA {
			GUI_ColorBHA()										{	base = nullptr;	highlight = nullptr;	active = nullptr;	}
			GUI_ColorBHA(const GUI_ColorBHA *c)					{	base = c->base; highlight = c->highlight; active = c->active;	}
			GUI_ColorBHA(Color *b, Color *h, Color *a)	{	base = b;	highlight = h;	active = a;	}
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
				struct _Position : Vector2f {
					Vector2f constraint;						///< Size reference constraint used to calculate actual position
				} pos;											///< Actual calculated position from origin and anchor constraints, automatically updated

				struct _Size : Vector2f {
					struct _SizeConstraint : Vector2f {
						eSizeConstraint xType,					///< Type of width constraint, relative or absolute
										yType;					///< Type of height constraint, relative or absolute
						bool			xAuto,
										yAuto;
						int				xMin,
										xMax,
										yMin,	// TODO: yMin not implemented
										yMax;	// TODO: yMax not implemented

						_SizeConstraint() {
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

				int						origin;					///< The starting drawing point with respect to the parent, if present, otherwise full screen.
				int						anchor;					///< The point at which this object is offset from the origin.
				Vector4i				vPadding;				///< Extra reserved space taken into account for origin.
				ePadding				eEnablePadding;
				bool 					visibility;				///< Controls if this object is drawn and any of its direct children.

				struct {
					std::string			Text;
					bool				bShow;
					int					border;
					int					radius;
					int					padding;
					bool				round;
					bool				showLabel;
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
				void exec(Props c)											{	execPos(c.size/2.0f, c.pos, c.vPadding);	execSize(c.size, c.vPadding);	}
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

				Props() {
					toolTip.bShow		= true;
					toolTip.Text		= "No ToolTip set!";
					toolTip.border		= 1;
					toolTip.radius		= 0;
					toolTip.padding		= 4;
					toolTip.round		= false;
					toolTip.showLabel	= true;
//					toolTip.color.header.background		= &gameVars->pallette.gui.toolTip.header.background;
//					toolTip.color.header.border			= &gameVars->pallette.gui.toolTip.header.border;
//					toolTip.color.header.text			= &gameVars->pallette.gui.toolTip.header.text;
//					toolTip.color.textarea.background	= &gameVars->pallette.gui.toolTip.textarea.background;
//					toolTip.color.textarea.border		= &gameVars->pallette.gui.toolTip.textarea.border;
//					toolTip.color.textarea.text			= &gameVars->pallette.gui.toolTip.textarea.text;


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

					origin					= src.origin;
					anchor					= src.anchor;
					vPadding				= src.vPadding;
					visibility				= src.visibility;
					eEnablePadding			= src.eEnablePadding;

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
			public:
				int iGroup;
//				std::string sGroup;

				void setGroup(int i)			{	iGroup = i;	}
//				void setGroup(std::string s)	{	sGroup = s;	}

				Props_Addon_Group() : iGroup(0) /*, sGroup("")*/ {}
		};

		/**
		 * \brief Object can be toggled
		 *
		 */
		class Props_Addon_Toggle {
			public:
				bool bToggle;
				void setToggle(bool b)									{	bToggle = b;		}
				Props_Addon_Toggle() : bToggle(false)/*, initialState(STATE_NONE)*/ {}
		};

		/**
		 * \brief Allows an object to return multiple different states
		 *
		 * @tparam T
		 */
		class Props_Addon_ReturnState {
			public:
//				enum eIndexType { NONE, BOOL, INT, FLOAT, STRING };

//				struct s_AnyType {
//					eIndexType type = NONE;
//					union {
//						bool		bOn;
//						int			iOn;
//						float		fOn;
//						std::string sOn;
//					};

//					void set(bool b)		{ type = BOOL;		bOn = b;	}
//					void set(int i)			{ type = INT;		iOn = i;	}
//					void set(float f)		{ type = FLOAT;		fOn = f;	}
//					void set(std::string s) { type = STRING;	sOn = s;	}

//					void get(bool &b)		{	b = bOn;	}
//					void get(int &i)		{	i = iOn;	}
//					void get(float &f)		{	f = fOn;	}
//				};
//				s_AnyType on[8];
//				s_AnyType off[8];
				int on[8];
				int off[8];

//				struct s_On {
//					s_AnyType on[8];
//					Object::Button		&operator[](std::string buttonName)			{	return *buttons[map[buttonName]];	}
//				} on;
//
//				struct s_Off {
//					s_AnyType off[8];
//				} off;

				void setOnState(int i, int n=0)				{ on[n] = i; }
				void setOffState(int i, int n=0)			{ off[n] = i; }

//				void setOnState(bool b, int n=0)			{ on[n].set(b); }
//				void setOnState(int i, int n=0)				{ on[n].set(i); }
//				void setOnState(float f, int n=0)			{ on[n].set(f); }
//				void setOnState(std::string s, int n=0)		{  }

//				void setOffState(bool b, int n=0)			{ off[n].set(b); }
//				void setOffState(int i, int n=0)			{ off[n].set(i); }
//				void setOffState(float f, int n=0)			{ off[n].set(f); }
//				void setOffState(std::string s, int n=0)	{  }

				Props_Addon_ReturnState() {
					for(int n=0; n<8; n++) {
						on[n] = 1;
						off[n] = 0;
					}
				}

				Props_Addon_ReturnState(Props_Addon_ReturnState &src) {
					for(int n=0; n<8; n++) {
						on[n] = src.on[n];
						off[n] = src.off[n];
					}
				}

				Props_Addon_ReturnState &operator=(const Props_Addon_ReturnState &src) {
					for(int n=0; n<8; n++) {
						on[n] = src.on[n];
						off[n] = src.off[n];
					}

					return *this;
				}
		};
//		template <class T> class Props_Addon_ReturnState {
//			public:
//				T on[8];
//				T off[8];
//
//				void setOnState(T t, int n=0)	{ on[std::min(n,7)] = t; }
//				void setOffState(T t, int n=0)	{ off[std::min(n,7)] = t; }
//
//				Props_Addon_ReturnState() {
//					for(int n=0; n<8; n++) {
//						on[n] = 1;
//						off[n] = 0;
//					}
//				}
//		};

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

			private:
				bool			bNoInput;

			public:
//				struct Colors {
//					GUI_ColorBHA	back,
//									border;
//				} color;


				struct Colors {
					private:
						struct {
							GUI_ColorBHA	back,
											border;
						} data;

					public:
						GUI_ColorBHA &back()	{ return data.back; }
						GUI_ColorBHA &border()	{ return data.border; }

					Colors() {}
				} color;



//				class _SetColor {
//					private:
//						Props_Window * parent;
//					public:
//
//						class _Back {
//							private:
//								_SetColor * parent;
//								GUI_ColorBHA * colorPtr;
//							public:
//								void base(Color *color) { parent->parent->color.back.base=color; }
//								void highlight(Color *color) { parent->parent->color.back.highlight=color; }
//								void active(Color *color) { parent->parent->color.back.active=color; }
//								_Back(_SetColor *p, GUI_ColorBHA *ptr) { parent = p; colorPtr=ptr; }
//						};
//						_Back back = _Back(this, &parent->color.back);
//
//						class _Border {
//							private:
//								_SetColor * parent;
//								GUI_ColorBHA * colorPtr;
//							public:
//								void base(Color *color) { parent->parent->color.back.base=color; }
//								void highlight(Color *color) { parent->parent->color.back.highlight=color; }
//								void active(Color *color) { parent->parent->color.back.active=color; }
//								_Border(_SetColor *p, GUI_ColorBHA *ptr) { parent = p; colorPtr=ptr; }
//						};
//						_Border border = _Border(this, &parent->color.border);
//
//						_SetColor(Props_Window * p) { parent = p; }
//				};
//				_SetColor setColor = _SetColor(this);



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

//				int  getBorder()											{	return border;	}

				Props_Window() {
					bScissor				= true;
					bNoInput				= false;
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
//					setPadding(0);

					color.back().base			= &Core::gameVars->pallette.gui.window.background.base;
					color.back().highlight	= &Core::gameVars->pallette.gui.window.background.hover;
					color.back().active		= &Core::gameVars->pallette.gui.window.background.active;

					color.border().base		= &Core::gameVars->pallette.gui.window.border.base;
					color.border().highlight	= &Core::gameVars->pallette.gui.window.border.hover;
					color.border().active		= &Core::gameVars->pallette.gui.window.border.active;
				}

//				Props_Window(Props_Window &src) {
//
//				}

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
		//			Label
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// FIXME: Update window constraints to be separate (background component)
		class Props_Label : public Props_Window {

			friend class Object::Label;

			public:
				struct Colors {
					private:
						struct {
							GUI_ColorBHA	text;
							GUI_ColorBHA	*backPtr,
											*borderPtr;
						} data;

					public:
						GUI_ColorBHA &text()	{ return data.text; }
						GUI_ColorBHA &back()	{ return *data.backPtr; }
						GUI_ColorBHA &border()	{ return *data.borderPtr; }


					Colors(GUI_ColorBHA *backPtr, GUI_ColorBHA *borderPtr) {
						data.backPtr = backPtr;
						data.borderPtr = borderPtr;
					}
				} color = Colors(&Props_Window::color.back(), &Props_Window::color.border());

				bool			bShowBackground;
				void showBackground()										{ bShowBackground = true;	}
				void hideBackground()										{ bShowBackground = false;	}

				Props_Label() {
					setMinMaxWidth(50, 200);

					bShowBackground				= false;
					setPadding(2);
					roundBorder					= true;
					radius						= 3;

					color.back().base				= &Core::gameVars->pallette.gui.label.background.base;
					color.back().highlight		= &Core::gameVars->pallette.gui.label.background.hover;
					color.back().active			= &Core::gameVars->pallette.gui.label.background.active;

					color.border().base			= &Core::gameVars->pallette.gui.label.border.base;
					color.border().highlight		= &Core::gameVars->pallette.gui.label.border.hover;
					color.border().active			= &Core::gameVars->pallette.gui.label.border.active;

					color.text().base				= &Core::gameVars->pallette.gui.label.text.base;
					color.text().highlight		= &Core::gameVars->pallette.gui.label.text.hover;
					color.text().active			= &Core::gameVars->pallette.gui.label.text.active;
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

//					label.bAutoSizeLabelX = true;
//					label.bAutoSizeLabelY = true;

					label.autoWidth();
					label.autoHeight();
				}
		};

		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		//			Field (Text/Numeric)
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
		// FIXME: Update window constraints to be separate (background component)
		class Props_Field : public Props_Window {

			template <class T>
			friend class Object::Field;

			public:

				// TODO: Implement this mapping to all objects
				struct Colors {
					private:
						struct {
							GUI_ColorBHA	text;
							GUI_ColorBHA	*backPtr,
											*borderPtr;
						} data;

					public:
						GUI_ColorBHA &text()	{ return data.text; }
						GUI_ColorBHA &back()	{ return *data.backPtr; }
						GUI_ColorBHA &border()	{ return *data.borderPtr; }


					Colors(GUI_ColorBHA *backPtr, GUI_ColorBHA *borderPtr) {
						data.backPtr = backPtr;
						data.borderPtr = borderPtr;
					}
				} color = Colors(&Props_Window::color.back(), &Props_Window::color.border());

				bool			bNumeric,
								bEditable;
				int				precision;
				float			minValue,
								maxValue;
				//Props_Window 	window;

				void setPrecision(int i)									{ precision = i; }
				void setMinMax(float min, float max)						{ minValue = min; maxValue = max; }
				void setMinMax(Vector2f v)									{ minValue = v.x; maxValue = v.y; }
				void setMin(float f)										{ minValue = f; }
				void setMax(float f)										{ maxValue = f; }
				void setEditable(bool b=true)								{ bEditable = b; }


				Props_Field() {
					//color.back = &colorWindow.back;
					//color.border = &colorWindow.border;

					bNumeric					= false;
					precision					= 3;
					bEditable					= true;
					minValue					= INT_MIN;
					maxValue					= INT_MAX;

					color.text().base				= &Core::gameVars->pallette.gui.field.text.base;
					color.text().highlight		= &Core::gameVars->pallette.gui.field.text.hover;
					color.text().active			= &Core::gameVars->pallette.gui.field.text.active;

					setPadding(2);
					setMinMaxWidth(10, 250);
					radius						= 0;
					roundBorder					= false;

					color.back().base			= &Core::gameVars->pallette.gui.field.background.base;
					color.back().highlight		= &Core::gameVars->pallette.gui.field.background.hover;
					color.back().active			= &Core::gameVars->pallette.gui.field.background.active;

					color.border().base			= &Core::gameVars->pallette.gui.field.border.base;
					color.border().highlight	= &Core::gameVars->pallette.gui.field.border.hover;
					color.border().active		= &Core::gameVars->pallette.gui.field.border.active;
				}

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
//					field.disablePadding();
					field.setMinMaxWidth(10, 250);
				}
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
				float		fMinimumStep;

				Props_Window control;

				void setOrientation(eSlider e)								{ orientation = e; }
				void setMinMax(Vector2f v)									{ minValue = v.x; maxValue = v.y; }
				void setMinMax(float min, float max)						{ minValue = min; maxValue = max; }
				void setPrecision(int i)									{ precision = i; }
				void setFieldSizeAbsolute(int i)							{ bExactSize = true; iFieldSize = i; }		// iFieldSize = exact size
				void setFieldSizeRelative(int i)							{ bExactSize = false; iFieldSize = i; }		// iFieldSize = minimum size
				void setScrollSpeed(float f)								{ scrollSpeed = f; }
				void setMinimumStep(float f)								{ fMinimumStep = f; }
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
					fMinimumStep		= 0.5f;
					precision			= 3;

					// Label
					bShowLabel			= false;
					label.setOrigin(CONSTRAIN_LEFT);
					label.setAnchor(CONSTRAIN_RIGHT);
					label.setPadding(2);
					label.setPos(0, 0);
					label.setMinWidth(0);
					label.color.text().base = &Core::gameVars->pallette.gui.slider.text.base;
					label.color.text().highlight = &Core::gameVars->pallette.gui.slider.text.hover;
					label.color.text().active = &Core::gameVars->pallette.gui.slider.text.active;

					// Field
					bShowField			= false;
					field.setOrigin(CONSTRAIN_RIGHT);
					field.setAnchor(CONSTRAIN_LEFT);
					field.setPadding(2);
					field.setPos(0, 0);
					field.color.text().base = &Core::gameVars->pallette.gui.slider.text.base;
					field.color.text().highlight = &Core::gameVars->pallette.gui.slider.text.hover;
					field.color.text().active = &Core::gameVars->pallette.gui.slider.text.active;

					// Slider
					bExactSize			= false;
					iFieldSize			= 80;
					if(orientation==SLIDER_HORIZONTAL) setPadding(-8, -8, -5, -5);
					else setPadding(-5, -5, -8, -8);
					setBorder(1, 1);
					setRadius(0);
					color.back().base = &Core::gameVars->pallette.gui.slider.bar.base;
					color.back().highlight = &Core::gameVars->pallette.gui.slider.bar.hover;
					color.back().active = &Core::gameVars->pallette.gui.slider.bar.active;

					color.border().base = &Core::gameVars->pallette.gui.slider.barBorder.base;
					color.border().highlight = &Core::gameVars->pallette.gui.slider.barBorder.hover;
					color.border().active = &Core::gameVars->pallette.gui.slider.barBorder.active;

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
					control.color.back().base = &Core::gameVars->pallette.gui.slider.control.base;
					control.color.back().highlight = &Core::gameVars->pallette.gui.slider.control.hover;
					control.color.back().active = &Core::gameVars->pallette.gui.slider.control.active;

					control.color.border().base = &Core::gameVars->pallette.gui.slider.controlBorder.base;
					control.color.border().highlight = &Core::gameVars->pallette.gui.slider.controlBorder.hover;
					control.color.border().active = &Core::gameVars->pallette.gui.slider.controlBorder.active;
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
									virtual public Props_Addon_Toggle,
									virtual public Props_Addon_ReturnState {

			friend class Object::Button;

			public:
				struct Colors {
					private:
						struct {
							GUI_ColorBHA	text;
							GUI_ColorBHA	*backPtr,
											*borderPtr;
						} data;

					public:
						GUI_ColorBHA &text()	{ return data.text; }
						GUI_ColorBHA &back()	{ return *data.backPtr; }
						GUI_ColorBHA &border()	{ return *data.borderPtr; }


					Colors(GUI_ColorBHA *backPtr, GUI_ColorBHA *borderPtr) {
						data.backPtr = backPtr;
						data.borderPtr = borderPtr;
					}
				} color = Colors(&Props_Window::color.back(), &Props_Window::color.border());

				iConstrain		eLabelAnchor;
				eButtonType		buttonType;
				int				debounceTime;

				void setLabelAnchor(eConstrain e)							{	eLabelAnchor = e;	}
				void setButtonType(eButtonType e)							{	buttonType = e;		}
				void setDebounceTime(int i)									{	debounceTime = i;	}

				Props_Button() {
					buttonType				= BUTTON_ONESHOT;
					eLabelAnchor			= CONSTRAIN_CENTER;
					debounceTime			= 500;

					color.back().base		= &Core::gameVars->pallette.gui.button.background.base;
					color.back().highlight	= &Core::gameVars->pallette.gui.button.background.hover;
					color.back().active		= &Core::gameVars->pallette.gui.button.background.active;

					color.border().base		= &Core::gameVars->pallette.gui.button.border.base;
					color.border().highlight	= &Core::gameVars->pallette.gui.button.border.hover;
					color.border().active	= &Core::gameVars->pallette.gui.button.border.active;

					color.text().base			= &Core::gameVars->pallette.gui.button.text.base;
					color.text().highlight	= &Core::gameVars->pallette.gui.button.text.hover;
					color.text().active		= &Core::gameVars->pallette.gui.button.text.active;
				}

				~Props_Button() {
				}
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

			// FIXME: Clean up and make members private as needed
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
//				Vector2i		vAutoSize;

			public:
				void scrollUp(int i=1)										{ scrollPosition = std::fmax(scrollPosition-i, 0); }
				void scrollDown(int i=1)									{ scrollPosition += i; }
				void setWordWrap(bool b)									{ bWordWrap = b;	}
				void setLineSpacing(int i)									{ iLineSpacing = i;	}
				void setBuffer(std::shared_ptr<std::string> s)				{	bLocalBuffer = false; bufferPtr = s;	}
				void setBuffer(std::string s)								{	bLocalBuffer = true; bufferPtr = std::make_shared<std::string>(s);	}

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

//					vAutoSize.x				= -1;
//					vAutoSize.y				= -1;
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
				using Props::enablePadding;
				using Props::disablePadding;

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

				void setPadding(int i)												{	text.setPadding(i); }
				void setPadding(int t, int b, int l, int r)							{	text.setPadding(t, b, l, r); }
				void setPadding(Vector4i v)											{	text.setPadding(v); }

				Props_TextArea() {
					enableScrolling				= false;
					iScrollSize					= 20;

					setBorder(1, 1);
					setRadius(0);
					Props::setPadding(0);
					setScrolling(false);
					setScrollSize(20);
					text.setPadding(4);

					hideLabel();
					label.setOrigin(CONSTRAIN_TOP_LEFT);
					label.setAnchor(CONSTRAIN_BOTTOM_LEFT);
					label.disablePadding();

					color.back().base				= &Core::gameVars->pallette.gui.textArea.background.base;
					color.back().highlight		= &Core::gameVars->pallette.gui.textArea.background.hover;
					color.back().active			= &Core::gameVars->pallette.gui.textArea.background.active;

					color.border().base			= &Core::gameVars->pallette.gui.textArea.border.base;
					color.border().highlight		= &Core::gameVars->pallette.gui.textArea.border.hover;
					color.border().active			= &Core::gameVars->pallette.gui.textArea.border.active;
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
				struct Colors {
					private:
						struct {
							GUI_ColorBHA	swatchBorder;
							GUI_ColorBHA	*backPtr,
											*borderPtr;
						} data;

					public:
						GUI_ColorBHA &swatchBorder()	{ return data.swatchBorder; }
						GUI_ColorBHA &back()			{ return *data.backPtr; }
						GUI_ColorBHA &border()			{ return *data.borderPtr; }


					Colors(GUI_ColorBHA *backPtr, GUI_ColorBHA *borderPtr) {
						data.backPtr = backPtr;
						data.borderPtr = borderPtr;
					}
				} color = Colors(&Props_Window::color.back(), &Props_Window::color.border());

//				GUI_ColorB		colorBackground;

//				void setColorBorderB(Color *v1)								{	colorBorder.base = v1;	}
				int  getRadius() 											{	return radius;	}
				bool getRoundBorder()										{	return roundBorder;	}
//				int  getBorder()											{	return border;	}

				Props_ColorSwatch() : Props_Addon_Slider(SLIDER_HORIZONTAL) {
					color.swatchBorder().base		= &Core::gameVars->pallette.gui.swatch.border.base;

					showBackground();
					background.color.back().base = &Core::colors[colors().White];

					bShowSlider		= true;
					slider.setOrigin(CONSTRAIN_RIGHT);
					slider.setAnchor(CONSTRAIN_LEFT);
					slider.setPos(30, 0);
					slider.setWidth(200);
					slider.setMinMax(0.0f, 1.0f);
					slider.setMinimumStep(0.01f);
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
										virtual public Props_Addon_Label,
										virtual public Props_Addon_ReturnState {

			friend class Object::CheckBox;

			private:
				Props_Window check;

			public:
				Props_CheckBox() {
					bToggle = true;
//					initialState = STATE_NONE;

					label.setOrigin(CONSTRAIN_LEFT);
					label.setAnchor(CONSTRAIN_RIGHT);
					label.setPadding(2);
					label.setPos(-10, 0);
					label.autoWidth();
					label.autoHeight();
//					label.setLabelAutoSize(true, true);
					showLabel();

					setPadding(0);
					setBorder(1, 1);
					setWidth(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
					setHeight(20, Core::GUI::SIZE_CONSTRAINT_ABSOLUTE);
					setRadius(10);

					color.back().base					= &Core::gameVars->pallette.gui.checkBox.background.base;
					color.back().highlight			= &Core::gameVars->pallette.gui.checkBox.background.hover;
					color.back().active				= &Core::gameVars->pallette.gui.checkBox.background.base;

					color.border().base				= &Core::gameVars->pallette.gui.checkBox.border.base;
					color.border().highlight			= &Core::gameVars->pallette.gui.checkBox.border.hover;
					color.border().active				= &Core::gameVars->pallette.gui.checkBox.border.active;

					check.color.back().base			= &Core::gameVars->pallette.gui.checkBox.background.active;
					check.color.back().highlight		= &Core::gameVars->pallette.gui.checkBox.background.active;
					check.color.back().active			= &Core::gameVars->pallette.gui.checkBox.background.active;

					check.color.border().base			= &Core::gameVars->pallette.gui.checkBox.border.base;
					check.color.border().highlight		= &Core::gameVars->pallette.gui.checkBox.border.hover;
					check.color.border().active		= &Core::gameVars->pallette.gui.checkBox.border.active;
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
									virtual public Props_Addon_Toggle,
									virtual public Props_Addon_ReturnState {

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
					background.color.back().base = &gameVars->pallette.gui.icon.background.base;
					background.color.back().highlight = &gameVars->pallette.gui.icon.background.hover;
					background.color.back().active = &gameVars->pallette.gui.icon.background.active;
					background.color.border().base = &gameVars->pallette.gui.icon.border.base;
					background.color.border().highlight = &gameVars->pallette.gui.icon.border.hover;
					background.color.border().active = &gameVars->pallette.gui.icon.border.active;

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
				struct Colors {
					private:
							struct {
							GUI_ColorBHA	sprite;
							GUI_ColorBHA	*backPtr,
											*borderPtr;
						} data;

					public:
						GUI_ColorBHA &sprite()	{ return data.sprite; }
						GUI_ColorBHA &back()	{ return *data.backPtr; }
						GUI_ColorBHA &border()	{ return *data.borderPtr; }


					Colors(GUI_ColorBHA *backPtr, GUI_ColorBHA *borderPtr) {
						data.backPtr = backPtr;
						data.borderPtr = borderPtr;
					}
				} color = Colors(&Props_Window::color.back(), &Props_Window::color.border());

				std::string		spriteImage;

				void setImage			(std::string s)						{	spriteImage = s;	}

				Props_Sprite() {
					enablePadding(PADDING_ALL);

					spriteImage				= "TestPattern.png";

					color.back().base		= &Core::gameVars->pallette.gui.sprite.background.base;
					color.back().highlight	= &Core::gameVars->pallette.gui.sprite.background.hover;
					color.back().active		= &Core::gameVars->pallette.gui.sprite.background.active;

					color.border().base		= &Core::gameVars->pallette.gui.sprite.border.base;
					color.border().highlight	= &Core::gameVars->pallette.gui.sprite.border.hover;
					color.border().active	= &Core::gameVars->pallette.gui.sprite.border.active;

					color.sprite().base		= &Core::gameVars->pallette.gui.sprite.base;
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
//		class Props_ProgressBar {

			public:
//				struct {
//					GUI_ColorB		fill,
//									empty,
//									border;
//				} progressColor;

				Props_Field field;
				Props_Window empty, fill;	// TODO
				bool		bShowField;		// TODO

//				void setColorProgressFill(Color *v1)							{ progressColor.fill.base = v1; }
//				void setColorProgressEmpty(Color *v1)							{ progressColor.empty.base = v1; }
//				void setColorProgressBorder(Color *v1)							{ progressColor.border.base = v1; }

				Props_ProgressBar() {

//					background.autoWidth(false);
//					background.autoHeight(false);
//					background.setPadding(2);
//					background.roundBorder						= true;
//					background.radius							= 3;
//					background.color.back.base			= &Core::gameVars->pallette.gui.progressBar.background.base;
//					background.color.back.highlight		= &Core::gameVars->pallette.gui.progressBar.background.base;
//					background.color.back.active			= &Core::gameVars->pallette.gui.progressBar.background.base;
//					background.color.border.base			= &Core::gameVars->pallette.gui.progressBar.background.border;
//					background.color.border.highlight		= &Core::gameVars->pallette.gui.progressBar.background.border;
//					background.color.border.active		= &Core::gameVars->pallette.gui.progressBar.background.border;

					autoWidth(false);
					autoHeight(false);
					setPadding(2);
					roundBorder						= true;
					radius							= 3;
					color.back().base				= &Core::gameVars->pallette.gui.progressBar.background.base;
					color.back().highlight		= &Core::gameVars->pallette.gui.progressBar.background.base;
					color.back().active			= &Core::gameVars->pallette.gui.progressBar.background.base;
					color.border().base			= &Core::gameVars->pallette.gui.progressBar.background.border;
					color.border().highlight		= &Core::gameVars->pallette.gui.progressBar.background.border;
					color.border().active			= &Core::gameVars->pallette.gui.progressBar.background.border;

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
					empty.color.back().base			= &Core::gameVars->pallette.gui.progressBar.progress.empty;
					empty.color.back().highlight		= &Core::gameVars->pallette.gui.progressBar.progress.empty;
					empty.color.back().active			= &Core::gameVars->pallette.gui.progressBar.progress.empty;
					empty.color.border().base			= &Core::gameVars->pallette.gui.progressBar.progress.border;
					empty.color.border().highlight	= &Core::gameVars->pallette.gui.progressBar.progress.border;
					empty.color.border().active		= &Core::gameVars->pallette.gui.progressBar.progress.border;

					fill.setOrigin(CONSTRAIN_LEFT);
					fill.setAnchor(CONSTRAIN_LEFT);
					fill.setWidth(0, SIZE_CONSTRAINT_RELATIVE);
					fill.setHeight(100, SIZE_CONSTRAINT_RELATIVE);
					fill.setBorder(0, 0);
					fill.setRadius(0);
					fill.setPadding(0);
					fill.setResizeRadius(false);
					fill.color.back().base			= &Core::gameVars->pallette.gui.progressBar.progress.fill;
					fill.color.back().highlight		= &Core::gameVars->pallette.gui.progressBar.progress.fill;
					fill.color.back().active			= &Core::gameVars->pallette.gui.progressBar.progress.fill;
					fill.color.border().base			= &Core::gameVars->pallette.gui.progressBar.progress.border;
					fill.color.border().highlight		= &Core::gameVars->pallette.gui.progressBar.progress.border;
					fill.color.border().active		= &Core::gameVars->pallette.gui.progressBar.progress.border;

					field.setOrigin(CONSTRAIN_CENTER);
					field.setAnchor(CONSTRAIN_CENTER);
					field.autoWidth();
					field.autoHeight();
					field.setEditable(false);
					field.setPadding(5);
					field.setMinWidth(3*Core::gameVars->font.vSize.x+5+5);

//					progressColor.empty.base		= &Core::gameVars->pallette.gui.progressBar.progress.empty;
//					progressColor.fill.base			= &Core::gameVars->pallette.gui.progressBar.progress.fill;
//					progressColor.border.base		= &Core::gameVars->pallette.gui.progressBar.progress.border;

					bShowField						= true;
				}

				~Props_ProgressBar() {
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
