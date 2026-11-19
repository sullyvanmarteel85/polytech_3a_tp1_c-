#include"gui.h"

Gui::Gui() : m_box_main(Gtk::ORIENTATION_HORIZONTAL), m_box_ip(Gtk::ORIENTATION_VERTICAL), m_box_inputs(Gtk::ORIENTATION_VERTICAL), m_entry_ip(), m_label_ip("Put IP here:"), m_grid_button(), m_buttons(new Gtk::Button[BUTTON_NUMBER]{Gtk::Button("Left Rotation"), Gtk::Button("Speed Up"), Gtk::Button("Right Rotation"), Gtk::Button("Left Turn"), Gtk::Button("Speed Down"), Gtk::Button("Right Turn")}){
	//Initialisation des composantes du GUI
	this->set_title("Hello World !");
	this->set_position(Gtk::WIN_POS_CENTER);
	this->resize(250, 250);
	this->set_border_width(10);

	//Initialisation de l'entrée pour l'ip
	m_entry_ip.set_placeholder_text("192.168.1.150");
	m_entry_ip.set_max_length(15);
	m_box_ip.pack_start(m_label_ip, Gtk::PACK_SHRINK);
	m_box_ip.pack_start(m_entry_ip, Gtk::PACK_EXPAND_WIDGET);
	m_box_inputs.pack_start(m_box_ip, Gtk::PACK_SHRINK);


	//Initialisation des boutons
	for(int i = 0;i<BUTTON_NUMBER;i++){
		(m_buttons + i)->set_can_focus(false);
		m_box_inputs.pack_start(*(m_buttons+i), Gtk::PACK_SHRINK);
	}

	//Organisation de la box principale
	m_box_main.pack_start(m_box_inputs, Gtk::PACK_SHRINK);
	this->add(m_box_main);
	m_box_main.set_can_focus(true);
	this->set_focus(m_box_main);
	this->show_all();

	(*m_buttons).signal_clicked().connect([this]() {
			std::cout << "Hello World !\n";
			});


}

Gui::~Gui(){
	delete[] m_buttons;
}
