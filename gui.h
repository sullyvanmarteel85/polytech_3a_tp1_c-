#pragma once

#include<gtkmm/window.h>
#include<gtkmm/button.h>
#include<gtkmm/aspectframe.h>
#include<gtkmm/frame.h>
#include<gtkmm/paned.h>
#include<iostream>

class Gui : public Gtk::Window {
	public:
		Gui();
		~Gui();
	private:
		Gtk::AspectFrame m_aspect_frame;
		Gtk::Button m_button_1;
};
