#include"limobot.h"
#include<chrono>
#include<iostream>
#include<stdio.h>
#include<gtkmm/main.h>
#include"gui.h"

int main(int argc, char* argv[]) {
	Gtk::Main app(argc, argv);
	Gui gui;

	app.run(gui);
	return 0;
}
