/*
 * GUI.h
 *
 *  Created on: Mar 6, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_GAMESYS_GUI_CONTAINER_H_
#define HEADERS_GAMESYS_GUI_CONTAINER_H_

#include <iostream>
//#include "../../core/types.h"
#include "../../core/core_functions.h"
//#include "../../core/vao.h"
//#include "../../core/matrix.h"
//#include "../../core/shader.h"
#include "GUI_Constraint.h"
#include "GUI_Objects.h"
#include "GUI_Window.h"
#include "GUI_Label.h"
#include "GUI_Button.h"
#include "GUI_Slider.h"
#include "GUI_Field.h"
#include "GUI_TextArea.h"
#include "GUI_TextEdit.h"
#include "GUI_ToolTip.h"
#include "GUI_ColorSwatch.h"
#include "GUI_CheckBox.h"
#include "GUI_Icon.h"
#include "GUI_Sprite.h"
#include "GUI_ProgressBar.h"
#include "GUI_ComboBox.h"
#include "GUI_Slider2D.h"
//#include "GUI_Custom.h"
//#include "GUI_Dialog.h"

namespace Core {
	namespace GUI {
		class GUI_Container : public Object::Window {
			public:
				GUI_Container(std::string name, Props_Container &c) : Object::Window(name, c)				{	setSources();	}
				GUI_Container(std::string name, Props_Container *c) : Object::Window(name, c)				{	setSources();	}
				GUI_Container(Props &p, std::string name, Props_Container &c) : Object::Window(p, name, c)	{	setSources();	}
				GUI_Container(Props &p, std::string name, Props_Container *c) : Object::Window(p, name, c)	{	setSources();	}
				void setSources() {
					containers.setSource("["+name+"]: Containers");
					Window.windows.setSource("["+name+"]: Windows");
					Label.labels.setSource("["+name+"]: Labels");
					Button.buttons.setSource("["+name+"]: Buttons");
					Slider.sliders.setSource("["+name+"]: Sliders");
					Field.fields.setSource("["+name+"]: Fields");
					TextArea.textAreas.setSource("["+name+"]: TextAreas");
					TextEdit.textEdits.setSource("["+name+"]: TextEdits");
					ColorSwatch.colorSwatches.setSource("["+name+"]: ColorSwatches");
					CheckBox.checkBoxes.setSource("["+name+"]: CheckBoxes");
					Icon.icons.setSource("["+name+"]: Icons");
					Sprite.sprites.setSource("["+name+"]: Sprites");
					ProgressBar.progressBars.setSource("["+name+"]: ProgressBars");
					ComboBox.comboBoxes.setSource("["+name+"]: ComboBoxes");
				}

				~GUI_Container() {}
				void exec();
				bool isActive() { return bFocusPresent; };

			private:
				Core::t_VectorMap<GUI_Container*> containers;
				void execObjects();
				void execToolTips();
				GUI_Container & pushData(std::string name, GUI_Container *data);

			public:
				GUI_Container & add(std::string containerName, Props_Container &c, Props *p=nullptr);
				GUI_Container & add(std::string containerName, Props_Container *c, Props *p=nullptr);
				GUI_Container & operator[](std::string containerName)			{	return *containers[containerName];			}
				Props_Window  & operator()(std::string containerName)			{	return *containers[containerName]->con;		}

				class WindowInterface {
						friend class GUI_Container;
					private:
						Core::t_VectorMap<Object::Window*> windows;
						GUI_Container * gui;
						Object::Window & pushData(std::string name, Object::Window *data);

					public:
						Object::Window & add(std::string containerName, Props_Window &c, Props *p=nullptr);
						Object::Window & add(std::string containerName, Props_Window *c, Props *p=nullptr);
						Object::Window & operator[](std::string windowName)			{	return *windows[windowName];		}
						Props_Window   & operator()(std::string windowName)			{	return *windows[windowName]->con;	}

						WindowInterface(GUI_Container * parent) { gui = parent; }
						~WindowInterface() { for (auto & window : windows) delete window; }
				};
				WindowInterface Window = WindowInterface(this);

				class LabelInterface {
						friend class GUI_Container;
					private:
						Core::t_VectorMap<Object::Label*> labels;
						GUI_Container * gui;
						Object::Label & pushData(std::string name, Object::Label *data);

					public:
						Object::Label & add(std::string labelName, Props_Label &c, Props *p=nullptr);
						Object::Label & add(std::string labelName, Props_Label *c, Props *p=nullptr);
						Object::Label & operator[](std::string labelName)			{	return *labels[labelName];		}
						Props_Label	  & operator()(std::string labelName)			{	return *labels[labelName]->con;	}
						LabelInterface(GUI_Container * parent) { gui = parent; }
						~LabelInterface() { for (auto & label : labels) delete label; }
				};
				LabelInterface Label = LabelInterface(this);

				class ButtonInterface {
						friend class GUI_Container;
					private:
						Core::t_VectorMap<Object::Button*> buttons;
						GUI_Container * gui;
						Object::Button & pushData(std::string name, Object::Button *data);

					public:
						Object::Button & add(std::string buttonName, bool  b, Props_Button &c, Props *p=nullptr);
						Object::Button & add(std::string buttonName, bool  b, Props_Button *c, Props *p=nullptr);
						Object::Button & add(std::string buttonName, bool *b, Props_Button &c, Props *p=nullptr);
						Object::Button & add(std::string buttonName, bool *b, Props_Button *c, Props *p=nullptr);
						Object::Button & operator[](std::string buttonName)			{	return *buttons[buttonName];		}
						Props_Button   & operator()(std::string buttonName)			{	return *buttons[buttonName]->con;	}
						ButtonInterface(GUI_Container * parent) { gui = parent; }
						~ButtonInterface() { for (auto & button : buttons) delete button; }
				};
				ButtonInterface Button = ButtonInterface(this);

				class SliderInterface {
						friend class GUI_Container;
					private:
						Core::t_VectorMap<Object::AnySlider*> sliders;
						GUI_Container * gui;
						Object::AnySlider & pushData(std::string name, Object::AnySlider *data);

					public:
						template <typename T> Object::AnySlider & add(std::string sliderName, T *ptr, Props_Slider &c, Props *p=nullptr);
						template <typename T> Object::AnySlider & add(std::string sliderName, T *ptr, Props_Slider *c, Props *p=nullptr);
						template <typename T> Object::AnySlider & add(std::string sliderName, T t, Props_Slider &c, Props *p=nullptr);
						template <typename T> Object::AnySlider & add(std::string sliderName, T t, Props_Slider *c, Props *p=nullptr);
						Object::AnySlider & operator[](std::string sliderName)		{	return *sliders[sliderName];	}
//						Props_Slider	&operator()(std::string sliderName)			{	return *sliders[map[sliderName]]->con;	}
						SliderInterface(GUI_Container * parent) { gui = parent; }
						~SliderInterface() { for (auto & slider : sliders) delete slider; }
				};
				SliderInterface Slider = SliderInterface(this);

				template <typename T>
				class Slider2DInterface {
						friend class GUI_Container;
					private:
						Core::t_VectorMap<Object::Slider2D<T>*> slider2Ds;
						GUI_Container * gui;
						Object::Slider2D<T> & pushData(std::string name, Object::Slider2D<T> *data);

					public:
						Object::Slider2D<T> & add(std::string sliderName, T *xPtr, T *yPtr, Props_Slider2D &c, Props *p=nullptr);
						Object::Slider2D<T> & add(std::string sliderName, T *xPtr, T *yPtr, Props_Slider2D *c, Props *p=nullptr);
						Object::Slider2D<T> & add(std::string sliderName, T xVal, T yVal, Props_Slider2D &c, Props *p=nullptr);
						Object::Slider2D<T> & add(std::string sliderName, T xVal, T yVal, Props_Slider2D *c, Props *p=nullptr);
						Object::Slider2D<T> & operator[](std::string sliderName)		{	return *slider2Ds[sliderName];	}
//						Props_Slider	&operator()(std::string sliderName)			{	return *sliders[map[sliderName]]->con;	}
						Slider2DInterface(GUI_Container * parent) { gui = parent; }
						~Slider2DInterface() { for (auto & slider : slider2Ds) delete slider; }
				};
				Slider2DInterface<int> Slider2Di = Slider2DInterface<int>(this);
				Slider2DInterface<float> Slider2Df = Slider2DInterface<float>(this);

				class FieldInterface {
						friend class GUI_Container;
					private:
						Core::t_VectorMap<Object::AnyField*> fields;
						GUI_Container * gui;
						Object::AnyField & pushData(std::string name, Object::AnyField *data);

					public:
						template <typename T> Object::AnyField & add(std::string fieldName, T * ptr, Props_Field &c, Props *p=nullptr);
						template <typename T> Object::AnyField & add(std::string fieldName, T * ptr, Props_Field *c, Props *p=nullptr);
						Props_Field * get(std::string fieldName);
						Object::AnyField & operator[](std::string fieldName)		{	return *fields[fieldName];	}
//						Props_Field	&operator()(std::string fieldName)			{	return *fields[map[fieldName]]->get();	}
						FieldInterface(GUI_Container * parent) { gui = parent; }
						~FieldInterface() { for (auto & field : fields) delete field; }
				};
				FieldInterface Field = FieldInterface(this);

				class TextAreaInterface {
						friend class GUI_Container;
					private:
						Core::t_VectorMap<Object::TextArea*> textAreas;
						GUI_Container * gui;
						Object::TextArea & pushData(std::string name, Object::TextArea *data);

					public:
						Object::TextArea & add(std::string textAreaName, Props_TextArea &c, Props *p=nullptr);
						Object::TextArea & add(std::string textAreaName, Props_TextArea *c, Props *p=nullptr);
						Object::TextArea &operator[](std::string textAreaName)	{	return *textAreas[textAreaName];		}
						Props_TextArea	 &operator()(std::string textAreaName)	{	return *textAreas[textAreaName]->con;	}
						TextAreaInterface(GUI_Container * parent) { gui = parent; }
						~TextAreaInterface() { for (auto & textArea : textAreas) delete textArea; }
				};
				TextAreaInterface TextArea = TextAreaInterface(this);

				class TextEditInterface {
						friend class GUI_Container;
					private:
						Core::t_VectorMap<Object::TextEdit*> textEdits;
						GUI_Container * gui;
						Object::TextEdit & pushData(std::string name, Object::TextEdit *data);

					public:
						Object::TextEdit & add(std::string textEditName, Props_TextArea &c, Props *p=nullptr);
						Object::TextEdit & add(std::string textEditName, Props_TextArea *c, Props *p=nullptr);
						Object::TextEdit &operator[](std::string textEditName)	{	return *textEdits[textEditName];		}
						Props_TextArea	 &operator()(std::string textEditName)	{	return *textEdits[textEditName]->con;	}
						TextEditInterface(GUI_Container * parent) { gui = parent; }
						~TextEditInterface() { for (auto & textEdit : textEdits) delete textEdit; }
				};
				TextEditInterface TextEdit = TextEditInterface(this);

				class ColorSwatchInterface {
						friend class GUI_Container;
					private:
						Core::t_VectorMap<Object::ColorSwatch*> colorSwatches;
						GUI_Container * gui;
						Object::ColorSwatch & pushData(std::string name, Object::ColorSwatch *data);

					public:
						Object::ColorSwatch & add(std::string colorSwatchName, Color * ptr, Props_ColorSwatch &c, Props *p=nullptr);
						Object::ColorSwatch & add(std::string colorSwatchName, Color * ptr, Props_ColorSwatch *c, Props *p=nullptr);
						Object::ColorSwatch &operator[](std::string colorSwatchName)	{	return *colorSwatches[colorSwatchName];			}
						Props_ColorSwatch	&operator()(std::string colorSwatchName)	{	return *colorSwatches[colorSwatchName]->con;	}
						ColorSwatchInterface(GUI_Container * parent) { gui = parent; }
						~ColorSwatchInterface() { for (auto & colorSwatch : colorSwatches) delete colorSwatch; }
				};
				ColorSwatchInterface ColorSwatch = ColorSwatchInterface(this);

				class CheckBoxInterface {
						friend class GUI_Container;

					private:
						Core::t_VectorMap<Object::CheckBox*> checkBoxes;
						GUI_Container * gui;
						Object::CheckBox & pushData(std::string name, Object::CheckBox *data);

					public:
						Object::CheckBox & add(std::string checkBoxName, bool b, Props_CheckBox &c, Props *p=nullptr);
						Object::CheckBox & add(std::string checkBoxName, bool b, Props_CheckBox *c, Props *p=nullptr);
						Object::CheckBox & add(std::string checkBoxName, bool *b, Props_CheckBox &c, Props *p=nullptr);
						Object::CheckBox & add(std::string checkBoxName, bool *b, Props_CheckBox *c, Props *p=nullptr);

						t_BIFS groupState(int iGroup, int n=0);
						t_BIFS groupState(std::string sGroup, int n=0);
//						auto groupState(std::string sGroup, int n);

						Object::CheckBox &operator[](std::string checkBoxName)	{	return *checkBoxes[checkBoxName];		}
						Props_CheckBox	 &operator()(std::string checkBoxName)	{	return *checkBoxes[checkBoxName]->con;	}
						CheckBoxInterface(GUI_Container * parent) { gui = parent; }
						~CheckBoxInterface() { for (auto & checkBox : checkBoxes) delete checkBox; }
				};
				CheckBoxInterface CheckBox = CheckBoxInterface(this);

				class IconInterface {
						friend class GUI_Container;

					private:
						Core::t_VectorMap<Object::Icon*> icons;
						GUI_Container * gui;
						Object::Icon & pushData(std::string name, Object::Icon *data);

					public:
						Object::Icon & add(std::string iconName, bool b, Props_Icon &c, Props *p=nullptr);
						Object::Icon & add(std::string iconName, bool b, Props_Icon *c, Props *p=nullptr);
						Object::Icon & add(std::string iconName, bool *b, Props_Icon &c, Props *p=nullptr);
						Object::Icon & add(std::string iconName, bool *b, Props_Icon *c, Props *p=nullptr);
						Object::Icon & operator[](std::string iconName)			{	return *icons[iconName];		}
						Props_Icon	 & operator()(std::string iconName)			{	return *icons[iconName]->con;	}
						IconInterface(GUI_Container * parent) { gui = parent; }
						~IconInterface() { for (auto & icon : icons) delete icon; }
				};
				IconInterface Icon = IconInterface(this);

				class SpriteInterface {
						friend class GUI_Container;

					private:
						Core::t_VectorMap<Object::Sprite*> sprites;
						GUI_Container * gui;
						Object::Sprite & pushData(std::string name, Object::Sprite *data);

					public:
						Object::Sprite & add(std::string spriteName, Props_Sprite &c, Props *p=nullptr);
						Object::Sprite & add(std::string spriteName, Props_Sprite *c, Props *p=nullptr);
						Object::Sprite &operator[](std::string spriteName)			{	return *sprites[spriteName];		}
						Props_Sprite   &operator()(std::string spriteName)			{	return *sprites[spriteName]->con;	}
						SpriteInterface(GUI_Container * parent) { gui = parent; }
						~SpriteInterface() { for (auto & sprite : sprites) delete sprite; }
				};
				SpriteInterface Sprite = SpriteInterface(this);

				class ProgressBarInterface {
						friend class GUI_Container;

					private:
						Core::t_VectorMap<Object::ProgressBar*> progressBars;
						GUI_Container * gui;
						Object::ProgressBar & pushData(std::string name, Object::ProgressBar *data);

					public:
						Object::ProgressBar & add(std::string progressBarName, int progress, Props_ProgressBar &c, Props *p=nullptr);
						Object::ProgressBar & add(std::string progressBarName, int progress, Props_ProgressBar *c, Props *p=nullptr);
						Object::ProgressBar & add(std::string progressBarName, int *progress, Props_ProgressBar &c, Props *p=nullptr);
						Object::ProgressBar & add(std::string progressBarName, int *progress, Props_ProgressBar *c, Props *p=nullptr);
						Object::ProgressBar &operator[](std::string progressBarName)			{	return *progressBars[progressBarName];		}
						Props_ProgressBar	&operator()(std::string progressBarName)			{	return *progressBars[progressBarName]->con;	}
						ProgressBarInterface(GUI_Container * parent) { gui = parent; }
						~ProgressBarInterface() { for (auto & progressBar : progressBars) delete progressBar; }
				};
				ProgressBarInterface ProgressBar = ProgressBarInterface(this);

				class ComboBoxInterface {
						friend class GUI_Container;
					private:
						Core::t_VectorMap<Object::ComboBox*> comboBoxes;
						GUI_Container * gui;
						Object::ComboBox & pushData(std::string name, Object::ComboBox *data);

					public:
						Object::ComboBox & add(std::string comboBoxName, Props_ComboBox  &c, Props *p=nullptr);
						Object::ComboBox & add(std::string comboBoxName, Props_ComboBox *c, Props *p=nullptr);
						Object::ComboBox & operator[](std::string comboBoxName)	{	return *comboBoxes[comboBoxName];		}
						Props_ComboBox	 & operator()(std::string comboBoxName)	{	return *comboBoxes[comboBoxName]->con;	}
						ComboBoxInterface(GUI_Container * parent) { gui = parent; }
						~ComboBoxInterface() { for (auto & comboBox : comboBoxes) delete comboBox; }
				};
				ComboBoxInterface ComboBox = ComboBoxInterface(this);
		};

//		GUI_Container*	GUI_Container::activeContainer = nullptr;

		/*
		 * ==========================================================
		 *						Container
		 * ==========================================================
		 */
		GUI_Container & GUI_Container::pushData(std::string name, GUI_Container *data) {
			data->init();
			return *containers.add(name, data);
		}

		GUI_Container & GUI_Container::add(std::string containerName, Props_Container &c, Props *p) {
			GUI_Container * container;
			if(p!=nullptr) container = new GUI_Container(*p, containerName, c);
			else container = new GUI_Container(*con, containerName, c);
			container->con->bNoInput = true;
			return pushData(containerName, container);
		}

		GUI_Container & GUI_Container::add(std::string containerName, Props_Container *c, Props *p) {
			GUI_Container * container;
			if(p!=nullptr) container = new GUI_Container(*p, containerName, c);
			else container = new GUI_Container(*con, containerName, c);
			container->con->bNoInput = true;
			return pushData(containerName, container);
		}

		/*
		 * ==========================================================
		 *						Windows
		 * ==========================================================
		 */
		Object::Window & GUI_Container::WindowInterface::pushData(std::string name, Object::Window *data) {
			data->init();
			return *windows.add(name, data);
		}

		Object::Window & GUI_Container::WindowInterface::add(std::string windowName, Props_Window &c, Props *p) {
			Object::Window * window;
			if(p!=nullptr) window = new Object::Window(*p, windowName, c);
			else window = new Object::Window(*gui->con, windowName, c);
			return pushData(windowName, window);
		}

		Object::Window & GUI_Container::WindowInterface::add(std::string windowName, Props_Window *c, Props *p) {
			Object::Window * window;
			if(p!=nullptr) window = new Object::Window(*p, windowName, c);
			else window = new Object::Window(*gui->con, windowName, c);
			return pushData(windowName, window);
		}

		/*
		 * ==========================================================
		 *						Labels
		 * ==========================================================
		 */
		Object::Label & GUI_Container::LabelInterface::pushData(std::string name, Object::Label *data) {
			data->init();
			return *labels.add(name, data);
		}

		Object::Label & GUI_Container::LabelInterface::add(std::string labelName, Props_Label &c, Props *p) {
			Object::Label * label;
			if(p!=nullptr) label = new Object::Label(*p, labelName, c);
			else label = new Object::Label(*gui->con, labelName, c);
			return pushData(labelName, label);
		}

		Object::Label & GUI_Container::LabelInterface::add(std::string labelName, Props_Label *c, Props *p) {
			Object::Label * label;
			if(p!=nullptr) label = new Object::Label(*p, labelName, c);
			else label = new Object::Label(*gui->con, labelName, c);
			return pushData(labelName, label);
		}

		/*
		 * ==========================================================
		 *						Buttons
		 * ==========================================================
		 */
		Object::Button & GUI_Container::ButtonInterface::pushData(std::string name, Object::Button *data) {
			data->init();
			return *buttons.add(name, data);
		}

		Object::Button & GUI_Container::ButtonInterface::add(std::string buttonName, bool b, Props_Button &c, Props *p) {
			Object::Button * button;
			if(p!=nullptr) button = new Object::Button(*p, buttonName, b, c);
			else button = new Object::Button(*gui->con, buttonName, b, c);
			return pushData(buttonName, button);
		}

		Object::Button & GUI_Container::ButtonInterface::add(std::string buttonName, bool b, Props_Button *c, Props *p) {
			Object::Button * button;
			if(p!=nullptr) button = new Object::Button(*p, buttonName, b, c);
			else button = new Object::Button(*gui->con, buttonName, b, c);
			return pushData(buttonName, button);
		}

		Object::Button & GUI_Container::ButtonInterface::add(std::string buttonName, bool *b, Props_Button &c, Props *p) {
			Object::Button * button;
			if(p!=nullptr) button = new Object::Button(*p, buttonName, b, c);
			else button = new Object::Button(*gui->con, buttonName, b, c);
			return pushData(buttonName, button);
		}

		Object::Button & GUI_Container::ButtonInterface::add(std::string buttonName, bool *b, Props_Button *c, Props *p) {
			Object::Button * button;
			if(p!=nullptr) button = new Object::Button(*p, buttonName, b, c);
			else button = new Object::Button(*gui->con, buttonName, b, c);
			return pushData(buttonName, button);
		}

		// TODO:
//		t_BIFS GUI_Container::CheckBoxInterface::groupState(int iGroup, int n) {
//			for (auto & checkBox : checkBoxes) {
//				if( (checkBox->con->iGroup == iGroup) && (checkBox->getState()) ) {
//					return checkBox->getDataSetValue(n);
//				}
//			}
//			return 0;
//		}
//
//		t_BIFS GUI_Container::CheckBoxInterface::groupState(std::string sGroup, int n) {
//			for (auto & checkBox : checkBoxes) {
//				if( (checkBox->con->iGroup == Core::groups[sGroup].index) && (checkBox->getState()) ) {
//					return checkBox->getDataSetValue(n);
//				}
//			}
//			return 0;
//		}

		/*
		 * ==========================================================
		 *						Sliders
		 * ==========================================================
		 */
		Object::AnySlider & GUI_Container::SliderInterface::pushData(std::string name, Object::AnySlider *data) {
			data->init();
			return *sliders.add(name, data);
		}

		template <typename T> Object::AnySlider & GUI_Container::SliderInterface::add(std::string sliderName, T *ptr, Props_Slider &c, Props *p) {
			Object::AnySlider * slider = new Object::AnySlider();
			if(p!=nullptr) slider->set(*p, sliderName, ptr, c);
			else slider->set(*gui->con, sliderName, ptr, c);
			return pushData(sliderName, slider);

		}

		template <typename T> Object::AnySlider & GUI_Container::SliderInterface::add(std::string sliderName, T *ptr, Props_Slider *c, Props *p) {
			Object::AnySlider * slider = new Object::AnySlider();
			if(p!=nullptr) slider->set(*p, sliderName, ptr, c);
			else slider->set(*gui->con, sliderName, ptr, c);
			return pushData(sliderName, slider);
		}

		template <typename T> Object::AnySlider & GUI_Container::SliderInterface::add(std::string sliderName, T t, Props_Slider &c, Props *p) {
			Object::AnySlider * slider = new Object::AnySlider();
			if(p!=nullptr) slider->set(*p, sliderName, t, c);
			else slider->set(*gui->con, sliderName, t, c);
			return pushData(sliderName, slider);

		}

		template <typename T> Object::AnySlider & GUI_Container::SliderInterface::add(std::string sliderName, T t, Props_Slider *c, Props *p) {
			Object::AnySlider * slider = new Object::AnySlider();
			if(p!=nullptr) slider->set(*p, sliderName, t, c);
			else slider->set(*gui->con, sliderName, t, c);
			return pushData(sliderName, slider);
		}

		/*
		 * ==========================================================
		 *						Slider2D<int>
		 * ==========================================================
		 */
		template <typename T> Object::Slider2D<T> & GUI_Container::Slider2DInterface<T>::pushData(std::string name, Object::Slider2D<T> *data) {
			data->init();
			return *slider2Ds.add(name, data);
		}

		template <typename T> Object::Slider2D<T> & GUI_Container::Slider2DInterface<T>::add(std::string sliderName, T *xPtr, T *yPtr, Props_Slider2D &c, Props *p) {
			Object::Slider2D<T> * slider2D;
			if(p!=nullptr) slider2D = new Object::Slider2D<T>(*p, sliderName, xPtr, yPtr, c);
			else slider2D = new Object::Slider2D<T>(*gui->con, sliderName, xPtr, yPtr, c);
			return pushData(sliderName, slider2D);

		}

		template <typename T> Object::Slider2D<T> & GUI_Container::Slider2DInterface<T>::add(std::string sliderName, T *xPtr, T *yPtr, Props_Slider2D *c, Props *p) {
			Object::Slider2D<T> * slider2D;
			if(p!=nullptr) slider2D = new Object::Slider2D<T>(*p, sliderName, xPtr, yPtr, c);
			else slider2D = new Object::Slider2D<T>(*gui->con, sliderName, xPtr, yPtr, c);
			return pushData(sliderName, slider2D);
		}

		template <typename T> Object::Slider2D<T> & GUI_Container::Slider2DInterface<T>::add(std::string sliderName, T xVal, T yVal, Props_Slider2D &c, Props *p) {
			Object::Slider2D<T> * slider2D;
			if(p!=nullptr) slider2D = new Object::Slider2D<T>(*p, sliderName, xVal, yVal, c);
			else slider2D = new Object::Slider2D<T>(*gui->con, sliderName, xVal, yVal, c);
			return pushData(sliderName, slider2D);

		}

		template <typename T> Object::Slider2D<T> & GUI_Container::Slider2DInterface<T>::add(std::string sliderName, T xVal, T yVal, Props_Slider2D *c, Props *p) {
			Object::Slider2D<T> * slider2D;
			if(p!=nullptr) slider2D = new Object::Slider2D<T>(*p, sliderName, xVal, yVal, c);
			else slider2D = new Object::Slider2D<T>(*gui->con, sliderName, xVal, yVal, c);
			return pushData(sliderName, slider2D);
		}

		/*
		 * ==========================================================
		 *						Fields
		 * ==========================================================
		 */
		Object::AnyField & GUI_Container::FieldInterface::pushData(std::string name, Object::AnyField *data) {
			data->init();
			return *fields.add(name, data);
		}

		template <typename T> Object::AnyField & GUI_Container::FieldInterface::add(std::string fieldName, T * ptr, Props_Field &c, Props *p) {
			Object::AnyField * field = new Object::AnyField();
			if(p!=nullptr) field->set(*p, fieldName, ptr, c);
			else field->set(*gui->con, fieldName, ptr, c);
			return pushData(fieldName, field);
		}

		template <typename T> Object::AnyField & GUI_Container::FieldInterface::add(std::string fieldName, T * ptr, Props_Field *c, Props *p) {
			Object::AnyField * field = new Object::AnyField();
			if(p!=nullptr) field->set(*p, fieldName, ptr, c);
			else field->set(*gui->con, fieldName, ptr, c);
			return pushData(fieldName, field);
		}

		/*
		 * ==========================================================
		 *						TextArea
		 * ==========================================================
		 */
		Object::TextArea & GUI_Container::TextAreaInterface::pushData(std::string name, Object::TextArea *data) {
			data->init();
			return *textAreas.add(name, data);
		}

		Object::TextArea & GUI_Container::TextAreaInterface::add(std::string textAreaName, Props_TextArea &c, Props *p) {
			Object::TextArea * textArea;
			if(p!=nullptr) textArea = new Object::TextArea(*p, textAreaName, c);
			else textArea = new Object::TextArea(*gui->con, textAreaName, c);
			return pushData(textAreaName, textArea);
		}

		Object::TextArea & GUI_Container::TextAreaInterface::add(std::string textAreaName, Props_TextArea *c, Props *p) {
			Object::TextArea * textArea;
			if(p!=nullptr) textArea = new Object::TextArea(*p, textAreaName, c);
			else textArea = new Object::TextArea(*gui->con, textAreaName, c);
			return pushData(textAreaName, textArea);
		}

		/*
		 * ==========================================================
		 *						TextEdit
		 * ==========================================================
		 */
		Object::TextEdit & GUI_Container::TextEditInterface::pushData(std::string name, Object::TextEdit *data) {
			data->init();
			return *textEdits.add(name, data);
		}

		Object::TextEdit & GUI_Container::TextEditInterface::add(std::string textEditName, Props_TextArea &c, Props *p) {
			Object::TextEdit * textEdit;
			if(p!=nullptr) textEdit = new Object::TextEdit(*p, textEditName, c);
			else textEdit = new Object::TextEdit(*gui->con, textEditName, c);
			textEdit->init();
			return pushData(textEditName, textEdit);
		}

		Object::TextEdit & GUI_Container::TextEditInterface::add(std::string textEditName, Props_TextArea *c, Props *p) {
			Object::TextEdit * textEdit;
			if(p!=nullptr) textEdit = new Object::TextEdit(*p, textEditName, c);
			else textEdit = new Object::TextEdit(*gui->con, textEditName, c);
			textEdit->init();
			return pushData(textEditName, textEdit);
		}

		/*
		 * ==========================================================
		 *						ColorSwatch
		 * ==========================================================
		 */
		Object::ColorSwatch & GUI_Container::ColorSwatchInterface::pushData(std::string name, Object::ColorSwatch *data) {
			data->init();
			return *colorSwatches.add(name, data);
		}

		Object::ColorSwatch & GUI_Container::ColorSwatchInterface::add(std::string colorSwatchName, Color * ptr, Props_ColorSwatch &c, Props *p) {
			Object::ColorSwatch * colorSwatch;
			if(p!=nullptr) colorSwatch = new Object::ColorSwatch(*p, colorSwatchName, ptr, c);
			else colorSwatch = new Object::ColorSwatch(*gui->con, colorSwatchName, ptr, c);
			return pushData(colorSwatchName, colorSwatch);
		}

		Object::ColorSwatch & GUI_Container::ColorSwatchInterface::add(std::string colorSwatchName, Color * ptr, Props_ColorSwatch *c, Props *p) {
			Object::ColorSwatch * colorSwatch;
			if(p!=nullptr) colorSwatch = new Object::ColorSwatch(*p, colorSwatchName, ptr, c);
			else colorSwatch = new Object::ColorSwatch(*gui->con, colorSwatchName, ptr, c);
			return pushData(colorSwatchName, colorSwatch);
		}

		/*
		 * ==========================================================
		 *						CheckBox
		 * ==========================================================
		 */
		Object::CheckBox & GUI_Container::CheckBoxInterface::pushData(std::string name, Object::CheckBox *data) {
			data->init();
			return *checkBoxes.add(name, data);
		}

		Object::CheckBox & GUI_Container::CheckBoxInterface::add(std::string checkBoxName, bool b, Props_CheckBox &c, Props *p) {
			Object::CheckBox * checkBox;
			if(p!=nullptr) checkBox = new Object::CheckBox(*p, checkBoxName, b, c);
			else checkBox = new Object::CheckBox(*gui->con, checkBoxName, b, c);
			return pushData(checkBoxName, checkBox);
		}

		Object::CheckBox & GUI_Container::CheckBoxInterface::add(std::string checkBoxName, bool b, Props_CheckBox *c, Props *p) {
			Object::CheckBox * checkBox;
			if(p!=nullptr) checkBox = new Object::CheckBox(*p, checkBoxName, b, c);
			else checkBox = new Object::CheckBox(*gui->con, checkBoxName, b, c);
			return pushData(checkBoxName, checkBox);
		}

		Object::CheckBox & GUI_Container::CheckBoxInterface::add(std::string checkBoxName, bool *b, Props_CheckBox &c, Props *p) {
			Object::CheckBox * checkBox;
			if(p!=nullptr) checkBox = new Object::CheckBox(*p, checkBoxName, b, c);
			else checkBox = new Object::CheckBox(*gui->con, checkBoxName, b, c);
			return pushData(checkBoxName, checkBox);
		}

		Object::CheckBox & GUI_Container::CheckBoxInterface::add(std::string checkBoxName, bool *b, Props_CheckBox *c, Props *p) {
			Object::CheckBox * checkBox;
			if(p!=nullptr) checkBox = new Object::CheckBox(*p, checkBoxName, b, c);
			else checkBox = new Object::CheckBox(*gui->con, checkBoxName, b, c);
			return pushData(checkBoxName, checkBox);
		}

		t_BIFS GUI_Container::CheckBoxInterface::groupState(int iGroup, int n) {
			for (auto & checkBox : checkBoxes) {
				if( (checkBox->con->iGroup == iGroup) && (checkBox->getState()) ) {
					return checkBox->getDataSetValue(n);
				}
			}
			return 0;
		}

		t_BIFS GUI_Container::CheckBoxInterface::groupState(std::string sGroup, int n) {
			for (auto & checkBox : checkBoxes) {
				if( (checkBox->con->iGroup == Core::groups[sGroup].index) && (checkBox->getState()) ) {
					return checkBox->getDataSetValue(n);
				}
			}
			return 0;
		}

		/*
		 * ==========================================================
		 *						Icons
		 * ==========================================================
		 */
		Object::Icon & GUI_Container::IconInterface::pushData(std::string name, Object::Icon *data) {
			data->init();
			return *icons.add(name, data);
		}

		Object::Icon & GUI_Container::IconInterface::add(std::string iconName, bool b, Props_Icon &c, Props *p) {
			Object::Icon * icon;
			if(p!=nullptr) icon = new Object::Icon(*p, iconName, b, c);
			else icon = new Object::Icon(*gui->con, iconName, b, c);
			return pushData(iconName, icon);
		}

		Object::Icon & GUI_Container::IconInterface::add(std::string iconName, bool b, Props_Icon *c, Props *p) {
			Object::Icon * icon;
			if(p!=nullptr) icon = new Object::Icon(*p, iconName, b, c);
			else icon = new Object::Icon(*gui->con, iconName, b, c);
			return pushData(iconName, icon);
		}

		Object::Icon & GUI_Container::IconInterface::add(std::string iconName, bool *b, Props_Icon &c, Props *p) {
			Object::Icon * icon;
			if(p!=nullptr) icon = new Object::Icon(*p, iconName, b, c);
			else icon = new Object::Icon(*gui->con, iconName, b, c);
			return pushData(iconName, icon);
		}

		Object::Icon & GUI_Container::IconInterface::add(std::string iconName, bool *b, Props_Icon *c, Props *p) {
			Object::Icon * icon;
			if(p!=nullptr) icon = new Object::Icon(*p, iconName, b, c);
			else icon = new Object::Icon(*gui->con, iconName, b, c);
			return pushData(iconName, icon);
		}

		// TODO:
//		t_BIFS GUI_Container::CheckBoxInterface::groupState(int iGroup, int n) {
//			for (auto & checkBox : checkBoxes) {
//				if( (checkBox->con->iGroup == iGroup) && (checkBox->getState()) ) {
//					return checkBox->getDataSetValue(n);
//				}
//			}
//			return 0;
//		}
//
//		t_BIFS GUI_Container::CheckBoxInterface::groupState(std::string sGroup, int n) {
//			for (auto & checkBox : checkBoxes) {
//				if( (checkBox->con->iGroup == Core::groups[sGroup].index) && (checkBox->getState()) ) {
//					return checkBox->getDataSetValue(n);
//				}
//			}
//			return 0;
//		}

		/*
		 * ==========================================================
		 *						Sprites
		 * ==========================================================
		 */
		Object::Sprite & GUI_Container::SpriteInterface::pushData(std::string name, Object::Sprite *data) {
			data->init();
			return *sprites.add(name, data);
		}

		Object::Sprite & GUI_Container::SpriteInterface::add(std::string spriteName, Props_Sprite &c, Props *p) {
			Object::Sprite * sprite;
			if(p!=nullptr) sprite = new Object::Sprite(*p, spriteName, c);
			else sprite = new Object::Sprite(*gui->con, spriteName, c);
			return pushData(spriteName, sprite);
		}

		Object::Sprite & GUI_Container::SpriteInterface::add(std::string spriteName, Props_Sprite *c, Props *p) {
			Object::Sprite * sprite;
			if(p!=nullptr) sprite = new Object::Sprite(*p, spriteName, c);
			else sprite = new Object::Sprite(*gui->con, spriteName, c);
			return pushData(spriteName, sprite);
		}

		/*
		 * ==========================================================
		 *						ProgressBars
		 * ==========================================================
		 */
		Object::ProgressBar & GUI_Container::ProgressBarInterface::pushData(std::string name, Object::ProgressBar *data) {
			data->init();
			return *progressBars.add(name, data);
		}

		Object::ProgressBar & GUI_Container::ProgressBarInterface::add(std::string progressBarName, int progress, Props_ProgressBar &c, Props *p) {
			Object::ProgressBar * progressBar;
			if(p!=nullptr) progressBar = new Object::ProgressBar(*p, progressBarName, progress, c);
			else progressBar = new Object::ProgressBar(*gui->con, progressBarName, progress, c);
			return pushData(progressBarName, progressBar);
		}

		Object::ProgressBar & GUI_Container::ProgressBarInterface::add(std::string progressBarName, int progress, Props_ProgressBar *c, Props *p) {
			Object::ProgressBar * progressBar;
			if(p!=nullptr) progressBar = new Object::ProgressBar(*p, progressBarName, progress, c);
			else progressBar = new Object::ProgressBar(*gui->con, progressBarName, progress, c);
			return pushData(progressBarName, progressBar);
		}

		Object::ProgressBar & GUI_Container::ProgressBarInterface::add(std::string progressBarName, int *progress, Props_ProgressBar &c, Props *p) {
			Object::ProgressBar * progressBar;
			if(p!=nullptr) progressBar = new Object::ProgressBar(*p, progressBarName, progress, c);
			else progressBar = new Object::ProgressBar(*gui->con, progressBarName, progress, c);
			return pushData(progressBarName, progressBar);
		}

		Object::ProgressBar & GUI_Container::ProgressBarInterface::add(std::string progressBarName, int *progress, Props_ProgressBar *c, Props *p) {
			Object::ProgressBar * progressBar;
			if(p!=nullptr) progressBar = new Object::ProgressBar(*p, progressBarName, progress, c);
			else progressBar = new Object::ProgressBar(*gui->con, progressBarName, progress, c);
			return pushData(progressBarName, progressBar);
		}

		/*
		 * ==========================================================
		 *						ComboBox
		 * ==========================================================
		 */
		Object::ComboBox & GUI_Container::ComboBoxInterface::pushData(std::string name, Object::ComboBox *data) {
			data->init();
			return *comboBoxes.add(name, data);
		}

		Object::ComboBox & GUI_Container::ComboBoxInterface::add(std::string comboBoxName, Props_ComboBox &c, Props *p) {
			Object::ComboBox * comboBoxes;
			if(p!=nullptr) comboBoxes = new Object::ComboBox(*p, comboBoxName, c);
			else comboBoxes = new Object::ComboBox(*gui->con, comboBoxName, c);
			return pushData(comboBoxName, comboBoxes);
		}

		Object::ComboBox & GUI_Container::ComboBoxInterface::add(std::string comboBoxName, Props_ComboBox *c, Props *p) {
			Object::ComboBox * comboBoxes;
			if(p!=nullptr) comboBoxes = new Object::ComboBox(*p, comboBoxName, c);
			else comboBoxes = new Object::ComboBox(*gui->con, comboBoxName, c);
			return pushData(comboBoxName, comboBoxes);
		}

		/*
		 * ==========================================================
		 *						Execute
		 * ==========================================================
		 */
		void GUI_Container::exec() {
			execObjects();
			if (Props::ToolTip::bShowGlobal) execToolTips();
		}

		void GUI_Container::execObjects() {
			if(bInit) {
				if(con->visibility) {
					c_Generic_Base::activeContainer = this->con;
					con->exec();

					if(con->bScissor) {
						int padLR = con->vPadding.left+con->vPadding.right;
						int padTB = con->vPadding.top+con->vPadding.bottom;

						int w = con->size.x-padLR,
							h = con->size.y-padTB;

						int x = ( (con->pos.x-(con->size.x/2)+con->vPadding.left )) + Core::gameVars->screen.half.x,
							y = ( (con->pos.y-(con->size.y/2)+con->vPadding.bottom )) + Core::gameVars->screen.half.y;

						Core::scissor.push(x, y, w, h, false);
						Core::scissor.checkInput(Core::mouse->x, Core::mouse->y, Core::gameVars->screen.res);
					}

					// Always disable scissor before drawing a container
					Core::scissor.disable();
					Object::Window::exec();
					if(con->bScissor) Core::scissor.enable();

					for (auto & window		: Window.windows)				window->exec();
					for (auto & label		: Label.labels)					label->exec();
					for (auto & button		: Button.buttons)				button->exec();
					for (auto & slider		: Slider.sliders)				slider->exec();
					for (auto & field		: Field.fields)					field->exec();
					for (auto & textArea	: TextArea.textAreas)			textArea->exec();
					for (auto & textEdit	: TextEdit.textEdits)			textEdit->exec();
					for (auto & colorSwatch	: ColorSwatch.colorSwatches)	colorSwatch->exec();
					for (auto & checkBox	: CheckBox.checkBoxes)			checkBox->exec();
					for (auto & icon		: Icon.icons)					icon->exec();
					for (auto & sprite		: Sprite.sprites)				sprite->exec();
					for (auto & progressBar	: ProgressBar.progressBars)		progressBar->exec();
					for (auto & comboBox	: ComboBox.comboBoxes)			comboBox->exec();
					for (auto & slider2D	: Slider2Di.slider2Ds)			slider2D->exec();
					for (auto & slider2D	: Slider2Df.slider2Ds)			slider2D->exec();
					for (auto & container	: containers)					container->execObjects();

					if(con->bScissor) {
						Core::scissor.pop();
					}
					Core::scissor.disable();
				}
				else {
					// Update values for non-visible objects, as doing so may update object state conditions
					for (auto & button		: Button.buttons)				button->updateNoFocus();
					for (auto & field		: Field.fields)					field->updateNoFocus();
					for (auto & checkBox	: CheckBox.checkBoxes)			checkBox->updateNoFocus();
					for (auto & icon		: Icon.icons)					icon->updateNoFocus();
					for (auto & textEdit	: TextEdit.textEdits)			textEdit->updateNoFocus();
					for (auto & slider		: Slider.sliders)				slider->updateNoFocus();
					for (auto & slider2D	: Slider2Di.slider2Ds)			slider2D->updateNoFocus();
					for (auto & slider2D	: Slider2Df.slider2Ds)			slider2D->updateNoFocus();
					for (auto & comboBox	: ComboBox.comboBoxes)			comboBox->updateNoFocus();
				}
			}
		}

		void GUI_Container::execToolTips() {
			// Always disable scissor before drawing Tool Tips
			//glDisable(GL_SCISSOR_TEST);
			Core::scissor.disable();

//			for (auto & window		: Window.windows)				window->exec();
//			for (auto & label		: Label.labels)					label->exec();
			for (auto & button		: Button.buttons)				button->execToolTip();		// TODO: Implement execToolTip()
			for (auto & slider		: Slider.sliders)				slider->execToolTip();
			for (auto & field		: Field.fields)					field->execToolTip();
			for (auto & textArea	: TextArea.textAreas)			textArea->toolTip.exec();	// TODO: Implement execToolTip()
//			for (auto & textEdit	: TextEdit.textEdits)			textEdit->exec();
			for (auto & colorSwatch	: ColorSwatch.colorSwatches)	colorSwatch->execToolTip();
//			for (auto & checkBox	: CheckBox.checkBoxes)			checkBox->toolTip.exec();	// TODO: Implement execToolTip()
			for (auto & checkBox	: CheckBox.checkBoxes)			checkBox->execToolTip();
//			for (auto & icon		: Icon.icons)					icon->toolTip.exec();		// TODO: Implement execToolTip()
			for (auto & icon		: Icon.icons)					icon->execToolTip();
//			for (auto & sprite		: Sprite.sprites)				sprite->toolTip.exec();		// TODO: Implement execToolTip()
			for (auto & sprite		: Sprite.sprites)				sprite->execToolTip();
			for (auto & progressBar	: ProgressBar.progressBars)		progressBar->execToolTip();
			for (auto & comboBox	: ComboBox.comboBoxes)			comboBox->execToolTip();
			for (auto & slider2D	: Slider2Di.slider2Ds)			slider2D->execToolTip();
			for (auto & slider2D	: Slider2Df.slider2Ds)			slider2D->execToolTip();
			for (auto & container	: containers)					container->execToolTips();
		}







	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_CONTAINER_H_ */
