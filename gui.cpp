#include"gui.h"

Gui::Gui() : m_frame(), m_button_1("Click here !"){
	this->set_title("Hello World !");
	this->set_position(Gtk::WIN_POS_CENTER);
	this->resize(250, 70);
	this->set_border_width(10);

	m_button_1.set_can_focus(false);
	m_frame.add(m_button_1);
	this->add(m_frame);

	this->show_all();

	m_button_1.signal_clicked().connect([this]() {
			std::cout << "Hello World !\n";
			});


}

Gui::~Gui(){
}
