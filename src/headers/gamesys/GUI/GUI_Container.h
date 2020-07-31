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
//#include "GUI_Custom.h"
//#include "GUI_Dialog.h"

namespace Core {
	namespace GUI {
		class GUI_Container : public Object::Window/*, private Object::Base::Interactive_Base*/ {
			public:
				GUI_Container(std::string name, Props_Window &c) : Object::Window(name, c)				{	init();	}
				GUI_Container(std::string name, Props_Window *c) : Object::Window(name, c)				{	init();	}
				GUI_Container(Props &p, std::string name, Props_Window &c) : Object::Window(p, name, c)	{	init();	}
				GUI_Container(Props &p, std::string name, Props_Window *c) : Object::Window(p, name, c)	{	init();	}
				~GUI_Container() {}
				void exec();
				bool isActive() { return Object::Base::Interactive_Base::bFocusPresent; };

			private:
				std::vector<GUI_Container*>			containers;
				Map_si								map;
				void execObjects();
				void execToolTips();
				GUI_Container & pushData(std::string name, GUI_Container *data);
//				bool								bIsActive;

			public:
				GUI_Container & add(std::string containerName, Props_Window &c, Props *p=nullptr);
				GUI_Container & add(std::string containerName, Props_Window *c, Props *p=nullptr);

				GUI_Container & operator[](std::string containerName)			{	if(map.count(containerName)>0) return *containers[map[containerName]]; else throw std::runtime_error("Invalid Container: "+containerName);	}
				Props_Window  & operator()(std::string containerName)			{	if(map.count(containerName)>0) return *containers[map[containerName]]->con; else throw std::runtime_error("Invalid Container: "+containerName);	}

				class WindowInterface {
						friend class GUI_Container;
					private:
						std::vector<Object::Window*>		windows;
						Map_si								map;
						GUI_Container * gui;
						Object::Window & pushData(std::string name, Object::Window *data);

					public:
						Object::Window & add(std::string containerName, Props_Window c, Props *p=nullptr);
						Object::Window & add(std::string containerName, Props_Window *c, Props *p=nullptr);
						Object::Window & operator[](std::string windowName)			{	if(map.count(windowName)>0) return *windows[map[windowName]]; else throw std::runtime_error("Invalid Window: "+windowName);	}
						Props_Window   & operator()(std::string windowName)			{	if(map.count(windowName)>0) return *windows[map[windowName]]->con; else throw std::runtime_error("Invalid Window: "+windowName);	}
						WindowInterface(GUI_Container * parent) { gui = parent; }
						~WindowInterface() { for (auto & window : windows) delete window; }
				};
				WindowInterface Window = WindowInterface(this);

				class LabelInterface {
						friend class GUI_Container;
					private:
						std::vector<Object::Label*>			labels;
						Map_si								map;
						GUI_Container * gui;
						Object::Label & pushData(std::string name, Object::Label *data);

					public:
						Object::Label & add(std::string labelName, Props_Label c, Props *p=nullptr);
						Object::Label & add(std::string labelName, Props_Label *c, Props *p=nullptr);
						Object::Label & operator[](std::string labelName)			{	if(map.count(labelName)>0) return *labels[map[labelName]]; else throw std::runtime_error("Invalid Label: "+labelName);	}
						Props_Label	  & operator()(std::string labelName)			{	if(map.count(labelName)>0) return *labels[map[labelName]]->con; else throw std::runtime_error("Invalid Label: "+labelName);	}
						LabelInterface(GUI_Container * parent) { gui = parent; }
						~LabelInterface() { for (auto & label : labels) delete label; }
				};
				LabelInterface Label = LabelInterface(this);

				class ButtonInterface {
						friend class GUI_Container;
					private:
						std::vector<Object::Button*>	buttons;
						Map_si							map;
						GUI_Container * gui;
						Object::Button & pushData(std::string name, Object::Button *data);

					public:
						Object::Button & add(std::string buttonName, bool  b, Props_Button  c, Props *p=nullptr);
						Object::Button & add(std::string buttonName, bool  b, Props_Button *c, Props *p=nullptr);
						Object::Button & add(std::string buttonName, bool *b, Props_Button  c, Props *p=nullptr);
						Object::Button & add(std::string buttonName, bool *b, Props_Button *c, Props *p=nullptr);

						Object::Button		&operator[](std::string buttonName)			{	if(map.count(buttonName)>0) return *buttons[map[buttonName]]; else throw std::runtime_error("Invalid Button: "+buttonName);	}
						Props_Button	&operator()(std::string buttonName)			{	if(map.count(buttonName)>0) return *buttons[map[buttonName]]->con; else throw std::runtime_error("Invalid Button: "+buttonName);	}
						ButtonInterface(GUI_Container * parent) { gui = parent; }
						~ButtonInterface() { for (auto & button : buttons) delete button; }
				};
				ButtonInterface Button = ButtonInterface(this);

				class SliderInterface {
						friend class GUI_Container;
					private:
						std::vector<Object::AnySlider*>		sliders;
						Map_si								map;
						GUI_Container * gui;
						Object::AnySlider & pushData(std::string name, Object::AnySlider *data);

					public:
						template <typename T> Object::AnySlider & add(std::string sliderName, T *ptr, Props_Slider c, Props *p=nullptr);
						template <typename T> Object::AnySlider & add(std::string sliderName, T *ptr, Props_Slider *c, Props *p=nullptr);

						template <typename T> Object::AnySlider & add(std::string sliderName, T t, Props_Slider c, Props *p=nullptr);
						template <typename T> Object::AnySlider & add(std::string sliderName, T t, Props_Slider *c, Props *p=nullptr);

						Object::AnySlider	&operator[](std::string sliderName)			{	if(map.count(sliderName)>0) return *sliders[map[sliderName]]; else throw std::runtime_error("Invalid Slider: "+sliderName);	}
//						Props_Slider	&operator()(std::string sliderName)			{	return *sliders[map[sliderName]]->con;	}
						SliderInterface(GUI_Container * parent) { gui = parent; }
						~SliderInterface() { for (auto & slider : sliders) delete slider; }
				};
				SliderInterface Slider = SliderInterface(this);

				class FieldInterface {
						friend class GUI_Container;
					private:
						std::vector<Object::AnyField*>		fields;
						Map_si								map;
						GUI_Container * gui;
						Object::AnyField & pushData(std::string name, Object::AnyField *data);

					public:
						template <typename T> Object::AnyField & add(std::string fieldName, T * ptr, Props_Field c, Props *p=nullptr);
						template <typename T> Object::AnyField & add(std::string fieldName, T * ptr, Props_Field *c, Props *p=nullptr);

						Props_Field * get(std::string fieldName);
						Object::AnyField	&operator[](std::string fieldName)			{	if(map.count(fieldName)>0) return *fields[map[fieldName]]; else throw std::runtime_error("Invalid Field: "+fieldName);	}
//						Props_Field	&operator()(std::string fieldName)			{	return *fields[map[fieldName]]->get();	}
						FieldInterface(GUI_Container * parent) { gui = parent; }
						~FieldInterface() { for (auto & field : fields) delete field; }
				};
				FieldInterface Field = FieldInterface(this);

				class TextAreaInterface {
						friend class GUI_Container;
					private:
						std::vector<Object::TextArea*>		textAreas;
						Map_si								map;
						GUI_Container * gui;
						Object::TextArea & pushData(std::string name, Object::TextArea *data);

					public:
						Object::TextArea & add(std::string textAreaName, Props_TextArea c, Props *p=nullptr);
						Object::TextArea & add(std::string textAreaName, Props_TextArea *c, Props *p=nullptr);

						Object::TextArea		&operator[](std::string textAreaName)	{	if(map.count(textAreaName)>0) return *textAreas[map[textAreaName]]; else throw std::runtime_error("Invalid TextArea: "+textAreaName);	}
						Props_TextArea	&operator()(std::string textAreaName)	{	if(map.count(textAreaName)>0) return *textAreas[map[textAreaName]]->con; else throw std::runtime_error("Invalid TextArea: "+textAreaName);	}
						TextAreaInterface(GUI_Container * parent) { gui = parent; }
						~TextAreaInterface() { for (auto & textArea : textAreas) delete textArea; }
				};
				TextAreaInterface TextArea = TextAreaInterface(this);

				class TextEditInterface {
						friend class GUI_Container;
					private:
						std::vector<Object::TextEdit*>		textEdits;
						Map_si								map;
						GUI_Container * gui;
						Object::TextEdit & pushData(std::string name, Object::TextEdit *data);

					public:
						Object::TextEdit & add(std::string textEditName, Props_TextArea c, Props *p=nullptr);
						Object::TextEdit & add(std::string textEditName, Props_TextArea *c, Props *p=nullptr);

						Object::TextEdit		&operator[](std::string textEditName)	{	if(map.count(textEditName)>0) return *textEdits[map[textEditName]]; else throw std::runtime_error("Invalid TextEdit: "+textEditName);	}
						Props_TextArea	&operator()(std::string textEditName)	{	if(map.count(textEditName)>0) return *textEdits[map[textEditName]]->con; else throw std::runtime_error("Invalid TextEdit: "+textEditName);	}
						TextEditInterface(GUI_Container * parent) { gui = parent; }
						~TextEditInterface() { for (auto & textEdit : textEdits) delete textEdit; }
				};
				TextEditInterface TextEdit = TextEditInterface(this);

				class ColorSwatchInterface {
						friend class GUI_Container;
					private:
						std::vector<Object::ColorSwatch*>	colorSwatches;
						Map_si								map;
						GUI_Container * gui;
						Object::ColorSwatch & pushData(std::string name, Object::ColorSwatch *data);

					public:
						Object::ColorSwatch & add(std::string colorSwatchName, Color * ptr, Props_ColorSwatch c, Props *p=nullptr);
						Object::ColorSwatch & add(std::string colorSwatchName, Color * ptr, Props_ColorSwatch *c, Props *p=nullptr);

						Object::ColorSwatch		&operator[](std::string colorSwatchName)	{	if(map.count(colorSwatchName)>0) return *colorSwatches[map[colorSwatchName]]; else throw std::runtime_error("Invalid ColorSwatch: "+colorSwatchName);	}
						Props_ColorSwatch	&operator()(std::string colorSwatchName)	{	if(map.count(colorSwatchName)>0) return *colorSwatches[map[colorSwatchName]]->con; else throw std::runtime_error("Invalid ColorSwatch: "+colorSwatchName);	}
						ColorSwatchInterface(GUI_Container * parent) { gui = parent; }
						~ColorSwatchInterface() { for (auto & colorSwatch : colorSwatches) delete colorSwatch; }
				};
				ColorSwatchInterface ColorSwatch = ColorSwatchInterface(this);

				class CheckBoxInterface {
						friend class GUI_Container;

					private:
						std::vector<Object::CheckBox*>		checkBoxes;
						Map_si								map;
						GUI_Container * gui;
						Object::CheckBox & pushData(std::string name, Object::CheckBox *data);

					public:
						Object::CheckBox & add(std::string checkBoxName, bool b, Props_CheckBox c, Props *p=nullptr);
						Object::CheckBox & add(std::string checkBoxName, bool b, Props_CheckBox *c, Props *p=nullptr);
						Object::CheckBox & add(std::string checkBoxName, bool *b, Props_CheckBox c, Props *p=nullptr);
						Object::CheckBox & add(std::string checkBoxName, bool *b, Props_CheckBox *c, Props *p=nullptr);

						t_BIFS groupState(int iGroup, int n=0);
						t_BIFS groupState(std::string sGroup, int n=0);
//						auto groupState(std::string sGroup, int n);

						Object::CheckBox		&operator[](std::string checkBoxName)	{	if(map.count(checkBoxName)>0) return *checkBoxes[map[checkBoxName]]; else throw std::runtime_error("Invalid CheckBox: "+checkBoxName);	}
						Props_CheckBox	&operator()(std::string checkBoxName)	{	if(map.count(checkBoxName)>0) return *checkBoxes[map[checkBoxName]]->con; else throw std::runtime_error("Invalid CheckBox: "+checkBoxName);	}
						CheckBoxInterface(GUI_Container * parent) { gui = parent; }
						~CheckBoxInterface() { for (auto & checkBox : checkBoxes) delete checkBox; }
				};
				CheckBoxInterface CheckBox = CheckBoxInterface(this);

				class IconInterface {
						friend class GUI_Container;

					private:
						std::vector<Object::Icon*>			icons;
						Map_si								map;
						GUI_Container * gui;
						Object::Icon & pushData(std::string name, Object::Icon *data);

					public:
						Object::Icon & add(std::string iconName, bool b, Props_Icon c, Props *p=nullptr);
						Object::Icon & add(std::string iconName, bool b, Props_Icon *c, Props *p=nullptr);
						Object::Icon & add(std::string iconName, bool *b, Props_Icon c, Props *p=nullptr);
						Object::Icon & add(std::string iconName, bool *b, Props_Icon *c, Props *p=nullptr);

						Object::Icon		&operator[](std::string iconName)			{	if(map.count(iconName)>0) return *icons[map[iconName]]; else throw std::runtime_error("Invalid Icon: "+iconName);	}
						Props_Icon	&operator()(std::string iconName)			{	if(map.count(iconName)>0) return *icons[map[iconName]]->con; else throw std::runtime_error("Invalid Icon: "+iconName);	}
						IconInterface(GUI_Container * parent) { gui = parent; }
						~IconInterface() { for (auto & icon : icons) delete icon; }
				};
				IconInterface Icon = IconInterface(this);

				class SpriteInterface {
						friend class GUI_Container;

					private:
						std::vector<Object::Sprite*>		sprites;
						Map_si								map;
						GUI_Container * gui;
						Object::Sprite & pushData(std::string name, Object::Sprite *data);

					public:
						Object::Sprite & add(std::string spriteName, Props_Sprite c, Props *p=nullptr);
						Object::Sprite & add(std::string spriteName, Props_Sprite *c, Props *p=nullptr);

						Object::Sprite		&operator[](std::string spriteName)			{	if(map.count(spriteName)>0) return *sprites[map[spriteName]]; else throw std::runtime_error("Invalid Sprite: "+spriteName);	}
						Props_Sprite	&operator()(std::string spriteName)			{	if(map.count(spriteName)>0) return *sprites[map[spriteName]]->con; else throw std::runtime_error("Invalid Sprite: "+spriteName);	}
						SpriteInterface(GUI_Container * parent) { gui = parent; }
						~SpriteInterface() { for (auto & sprite : sprites) delete sprite; }
				};
				SpriteInterface Sprite = SpriteInterface(this);

				class ProgressBarInterface {
						friend class GUI_Container;

					private:
						std::vector<Object::ProgressBar*>		progressBars;
						Map_si									map;
						GUI_Container * gui;
						Object::ProgressBar & pushData(std::string name, Object::ProgressBar *data);

					public:
						Object::ProgressBar & add(std::string progressBarName, int progress, Props_ProgressBar c, Props *p=nullptr);
						Object::ProgressBar & add(std::string progressBarName, int progress, Props_ProgressBar *c, Props *p=nullptr);
						Object::ProgressBar & add(std::string progressBarName, int *progress, Props_ProgressBar c, Props *p=nullptr);
						Object::ProgressBar & add(std::string progressBarName, int *progress, Props_ProgressBar *c, Props *p=nullptr);

						Object::ProgressBar		&operator[](std::string progressBarName)			{	if(map.count(progressBarName)>0) return *progressBars[map[progressBarName]]; else throw std::runtime_error("Invalid ProgressBar: "+progressBarName);	}
						Props_ProgressBar		&operator()(std::string progressBarName)			{	if(map.count(progressBarName)>0) return *progressBars[map[progressBarName]]->con; else throw std::runtime_error("Invalid ProgressBar: "+progressBarName);	}
						ProgressBarInterface(GUI_Container * parent) { gui = parent; }
						~ProgressBarInterface() { for (auto & progressBar : progressBars) delete progressBar; }
				};
				ProgressBarInterface ProgressBar = ProgressBarInterface(this);

				class ComboBoxInterface {
						friend class GUI_Container;
					private:
						std::vector<Object::ComboBox*>	comboBoxes;
						Map_si							map;
						GUI_Container * gui;
						Object::ComboBox & pushData(std::string name, Object::ComboBox *data);

					public:
						Object::ComboBox & add(std::string comboBoxName, Props_ComboBox  c, Props *p=nullptr);
						Object::ComboBox & add(std::string comboBoxName, Props_ComboBox *c, Props *p=nullptr);

						Object::ComboBox	&operator[](std::string comboBoxName)	{	if(map.count(comboBoxName)>0) return *comboBoxes[map[comboBoxName]]; else throw std::runtime_error("Invalid ComboBox: "+comboBoxName);	}
						Props_ComboBox		&operator()(std::string comboBoxName)	{	if(map.count(comboBoxName)>0) return *comboBoxes[map[comboBoxName]]->con; else throw std::runtime_error("Invalid ComboBox: "+comboBoxName);	}
						ComboBoxInterface(GUI_Container * parent) { gui = parent; }
						~ComboBoxInterface() { for (auto & comboBox : comboBoxes) delete comboBox; }
				};
				ComboBoxInterface ComboBox = ComboBoxInterface(this);
		};

		/*
		 * ==========================================================
		 *						Container
		 * ==========================================================
		 */
		GUI_Container & GUI_Container::pushData(std::string name, GUI_Container *data) {
//			debug.log("[8]: GUI_Container::pushData()");
			data->init();
//			debug.log("[9]: GUI_Container::pushData()");
			containers.push_back(data);
//			debug.log("[10]: pushData()");
			uint id = containers.size()-1;
//			debug.log("[11]: GUI_Container::pushData()");
			map.insert(make_pair(name, id));
//			debug.log("[12]: GUI_Container::pushData()");
			return *containers[id];
		}

		GUI_Container & GUI_Container::add(std::string containerName, Props_Window &c, Props *p) {
//			debug.log("[0]: GUI_Container::add()");
			GUI_Container * container;
//			debug.log("[1]: GUI_Container::add()");
			if(p!=nullptr) {
//				debug.log("[2]: GUI_Container::add()");
//				Core::debug.logIncreaseIndent();
				container = new GUI_Container(*p, containerName, c);
//				Core::debug.logDecreaseIndent();
//				debug.log("[3]: GUI_Container::add()");
			}
			else {
//				debug.log("[4]: GUI_Container::add()");
//				Core::debug.logIncreaseIndent();
				container = new GUI_Container(*con, containerName, c);
//				Core::debug.logDecreaseIndent();
//				debug.log("[5]: GUI_Container::add()");
			}
			container->con->bNoInput = true;
//			debug.log("[6]: GUI_Container::add()");
			container->init();
//			debug.log("[7]: GUI_Container::add()");
			return pushData(containerName, container);
		}

		GUI_Container & GUI_Container::add(std::string containerName, Props_Window *c, Props *p) {
			GUI_Container * container;
			if(p!=nullptr) container = new GUI_Container(*p, containerName, c);
			else container = new GUI_Container(*con, containerName, c);
			container->con->bNoInput = true;
			container->init();
			return pushData(containerName, container);
		}

		/*
		 * ==========================================================
		 *						Windows
		 * ==========================================================
		 */
		Object::Window & GUI_Container::WindowInterface::pushData(std::string name, Object::Window *data) {
			data->init();
			windows.push_back(data);
			uint id = windows.size()-1;
			map.insert(make_pair(name, id));
			return *windows[id];
		}

		Object::Window & GUI_Container::WindowInterface::add(std::string windowName, Props_Window c, Props *p) {
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
			labels.push_back(data);
			uint id = labels.size()-1;
			map.insert(make_pair(name, id));
			return *labels[id];
		}

		Object::Label & GUI_Container::LabelInterface::add(std::string labelName, Props_Label c, Props *p) {
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
			buttons.push_back(data);
			uint id = buttons.size()-1;
			map.insert(make_pair(name, id));
			return *buttons[id];
		}

		Object::Button & GUI_Container::ButtonInterface::add(std::string buttonName, bool b, Props_Button c, Props *p) {
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

		Object::Button & GUI_Container::ButtonInterface::add(std::string buttonName, bool *b, Props_Button c, Props *p) {
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

		/*
		 * ==========================================================
		 *						Sliders
		 * ==========================================================
		 */
		Object::AnySlider & GUI_Container::SliderInterface::pushData(std::string name, Object::AnySlider *data) {
			data->init();
			sliders.push_back(data);
			uint id = sliders.size()-1;
			map.insert(make_pair(name, id));
			return *sliders[id];
		}

		template <typename T> Object::AnySlider & GUI_Container::SliderInterface::add(std::string sliderName, T *ptr, Props_Slider c, Props *p) {
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

		template <typename T> Object::AnySlider & GUI_Container::SliderInterface::add(std::string sliderName, T t, Props_Slider c, Props *p) {
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
		 *						Fields
		 * ==========================================================
		 */
		Object::AnyField & GUI_Container::FieldInterface::pushData(std::string name, Object::AnyField *data) {
			data->init();
			fields.push_back(data);
			uint id = fields.size()-1;
			map.insert(make_pair(name, id));
			return *fields[id];
		}

		template <typename T> Object::AnyField & GUI_Container::FieldInterface::add(std::string fieldName, T * ptr, Props_Field c, Props *p) {
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
			textAreas.push_back(data);
			uint id = textAreas.size()-1;
			map.insert(make_pair(name, id));
			return *textAreas[id];
		}

		Object::TextArea & GUI_Container::TextAreaInterface::add(std::string textAreaName, Props_TextArea c, Props *p) {
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
			textEdits.push_back(data);
			uint id = textEdits.size()-1;
			map.insert(make_pair(name, id));
			return *textEdits[id];
		}

		Object::TextEdit & GUI_Container::TextEditInterface::add(std::string textEditName, Props_TextArea c, Props *p) {
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
			colorSwatches.push_back(data);
			uint id = colorSwatches.size()-1;
			map.insert(make_pair(name, id));
			return *colorSwatches[id];
		}

		Object::ColorSwatch & GUI_Container::ColorSwatchInterface::add(std::string colorSwatchName, Color * ptr, Props_ColorSwatch c, Props *p) {
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
			checkBoxes.push_back(data);
			uint id = checkBoxes.size()-1;
			map.insert(make_pair(name, id));
			return *checkBoxes[id];
		}

		Object::CheckBox & GUI_Container::CheckBoxInterface::add(std::string checkBoxName, bool b, Props_CheckBox c, Props *p) {
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

		Object::CheckBox & GUI_Container::CheckBoxInterface::add(std::string checkBoxName, bool *b, Props_CheckBox c, Props *p) {
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
			//int iState = 0;
			for (auto & checkBox : checkBoxes) {
				if( (checkBox->con->iGroup == iGroup) && (checkBox->getState()) ) {
					//iState |= checkBox->getDataSetValue(n);
					// FIXME: Duplicates sometimes show up, fix (requires second loop to disable objects that were active before another object was set active)
					//if(iState) break;	// Break at first success
					return checkBox->getDataSetValue(n);
				}

			}
			return 0;
		}

		t_BIFS GUI_Container::CheckBoxInterface::groupState(std::string sGroup, int n) {
			//int iState = 0;
			for (auto & checkBox : checkBoxes) {
				if( (checkBox->con->iGroup == Core::groups[sGroup].index) && (checkBox->getState()) ) {
					//iState |= checkBox->getDataSetValue(n);
					// FIXME: Duplicates sometimes show up, fix (requires second loop to disable objects that were active before another object was set active)
					//if(iState) break;	// Break at first success
					return checkBox->getDataSetValue(n);
				}

			}
			//return iState;
			return 0;
		}

//		auto GUI_Container::CheckBoxInterface::groupState(std::string sGroup, int n) {
//			//int iState = 0;
//			for (auto & checkBox : checkBoxes) {
//				if( (checkBox->con->iGroup == Core::groups[sGroup].index) && (checkBox->getState()) ) {
//					//iState |= checkBox->getDataSetValue(n);
//					// FIXME: Duplicates sometimes show up, fix (requires second loop to disable objects that were active before another object was set active)
//					//if(iState) break;	// Break at first success
//
//					checkBox->getDataSetValue();
//
////					switch(checkBox->getDataSetValue(n).index()) {
////						case 0:
////							return std::get<bool>(checkBox->getDataSetValue(n));
////							break;
////						case 1:
////							return std::get<int>(checkBox->getDataSetValue(n));
////							break;
////						case 2:
////							return std::get<float>(checkBox->getDataSetValue(n));
////							break;
////							return std::get<std::string>(checkBox->getDataSetValue(n));
////						case 3:
////							break;
////					}
//				}
//
//			}
//			//return iState;
//			return 0;
//		}

		/*
		 * ==========================================================
		 *						Icons
		 * ==========================================================
		 */
		Object::Icon & GUI_Container::IconInterface::pushData(std::string name, Object::Icon *data) {
			data->init();
			icons.push_back(data);
			uint id = icons.size()-1;
			map.insert(make_pair(name, id));
			return *icons[id];
		}

		Object::Icon & GUI_Container::IconInterface::add(std::string iconName, bool b, Props_Icon c, Props *p) {
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

		Object::Icon & GUI_Container::IconInterface::add(std::string iconName, bool *b, Props_Icon c, Props *p) {
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

		/*
		 * ==========================================================
		 *						Sprites
		 * ==========================================================
		 */
		Object::Sprite & GUI_Container::SpriteInterface::pushData(std::string name, Object::Sprite *data) {
			data->init();
			sprites.push_back(data);
			uint id = sprites.size()-1;
			map.insert(make_pair(name, id));
			return *sprites[id];
		}

		Object::Sprite & GUI_Container::SpriteInterface::add(std::string spriteName, Props_Sprite c, Props *p) {
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
			progressBars.push_back(data);
			uint id = progressBars.size()-1;
			map.insert(make_pair(name, id));
			return *progressBars[id];
		}

		Object::ProgressBar & GUI_Container::ProgressBarInterface::add(std::string progressBarName, int progress, Props_ProgressBar c, Props *p) {
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

		Object::ProgressBar & GUI_Container::ProgressBarInterface::add(std::string progressBarName, int *progress, Props_ProgressBar c, Props *p) {
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
			comboBoxes.push_back(data);
			uint id = comboBoxes.size()-1;
			map.insert(make_pair(name, id));
			return *comboBoxes[id];
		}

		Object::ComboBox & GUI_Container::ComboBoxInterface::add(std::string comboBoxName, Props_ComboBox c, Props *p) {
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
					con->exec();

					// FIXME: Create a Scissor coordinates stack
					//			[ ] Push onto stack
					//				- Includes enable/disable
					//				- A disable stack does not require x,y,w,h
					//			[ ] Pop from stack
					//			[ ] exec stack
					//				- If nothing on stack, do not enable

					// Always disable scissor before drawing a container
					glDisable(GL_SCISSOR_TEST);
					Object::Window::exec();

					if(con->bScissor) {
						int padLR = con->vPadding.left+con->vPadding.right;
						int padTB = con->vPadding.top+con->vPadding.bottom;

						int w = con->size.x-padLR,
							h = con->size.y-padTB;

						int x = ( (con->pos.x-(con->size.x/2)+con->vPadding.left )) + Core::gameVars->screen.half.x,
							y = ( (con->pos.y-(con->size.y/2)+con->vPadding.bottom )) + Core::gameVars->screen.half.y;

						glEnable(GL_SCISSOR_TEST);
						glScissor(x, y, w, h);
					}

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
					for (auto & container	: containers)					container->execObjects();
				}
				else {
					// Update values for non-visible objects, as doing so may update object state conditions
					for (auto & button		: Button.buttons)				button->updateNoFocus();
					for (auto & field		: Field.fields)					field->updateNoFocus();
					for (auto & checkBox	: CheckBox.checkBoxes)			checkBox->updateNoFocus();
					for (auto & icon		: Icon.icons)					icon->updateNoFocus();
					for (auto & textEdit	: TextEdit.textEdits)			textEdit->updateNoFocus();
					for (auto & slider		: Slider.sliders)				slider->updateNoFocus();
					for (auto & comboBox	: ComboBox.comboBoxes)			comboBox->updateNoFocus();
				}
			}
		}

		void GUI_Container::execToolTips() {
			// Always disable scissor before drawing Tool Tips
			glDisable(GL_SCISSOR_TEST);

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
			for (auto & container	: containers)					container->execToolTips();
		}







	}
} /* namespace Core */

#endif /* HEADERS_GAMESYS_GUI_CONTAINER_H_ */
