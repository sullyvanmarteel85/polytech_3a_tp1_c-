#pragma once

#define BUTTON_NUMBER 6

#include<gtkmm/window.h>
#include<gtkmm/button.h>
#include<gtkmm/box.h>
#include<gtkmm/image.h>
#include<gtkmm/entry.h>
#include<gtkmm/label.h>
#include<gtkmm/grid.h>
#include<iostream>

class Gui : public Gtk::Window {
	public:
		Gui();
		~Gui();
	private:
		Gtk::Box m_box_main, m_box_inputs, m_box_ip;
		Gtk::Image m_image;
		Gtk::Entry m_entry_ip;
		Gtk::Label m_label_ip;
		Gtk::Grid m_grid_button;
		Gtk::Button* m_buttons;
};
