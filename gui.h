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
#include"limobot.h"
#include<thread>
#include<string>

class Gui : public Gtk::Window {
        public:
                Gui(LimoBot& limobot);
                ~Gui();
                void run(LimoBot& limobot);
        private:
                Gtk::Box m_box_main, m_box_inputs, m_box_ip;
                Gtk::Image m_image;
                Gtk::Entry m_entry_ip;
                Gtk::Label m_label_ip;
                Gtk::Grid m_grid_button;
                Gtk::Button* m_direction_buttons;
                Gtk::Button m_connect_button, m_disconnect_button, m_stop_button;
                bool m_connect, m_disconnect, m_stop;
                bool* m_direction;
                std::thread* m_p_thread;
		std::string ip;
};
