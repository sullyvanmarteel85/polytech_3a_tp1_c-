#include"gui.h"

Gui::Gui() : m_button_1("Click here !"){
	this->set_title("Hello World !");
	this->set_position(Gtk::WIN_POS_CENTER);
	this->resize(250, 70);
	this->set_border_width(10);

	m_button_1.set_can_focus(false);
	this->add(m_button_1);

	this->show_all();

	m_button_1.signal_clicked().connect([this]() {
			std::cout << "Hello World !\n";
			});
}

Gui::~Gui(){
}
