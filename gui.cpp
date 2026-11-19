#include"gui.h"

//Constructeur et deconstructeur
Gui::Gui(LimoBot& limobot) : m_connect(false), m_disconnect(false), m_stop(false), m_direction(new bool[BUTTON_NUMBER]{false, false, false, false, false, false}), m_image("agilex-limo.jpg"), m_box_main(Gtk::ORIENTATION_HORIZONTAL), m_box_ip(Gtk::ORIENTATION_VERTICAL), m_box_inputs(Gtk::ORIENTATION_VERTICAL), m_entry_ip(), m_label_ip("Put IP here:"), m_grid_button(), m_direction_buttons(new Gtk::Button[BUTTON_NUMBER]{Gtk::Button("Left Rotation"), Gtk::Button("Speed Up"), Gtk::Button("Right Rotation"), Gtk::Button("Left Turn"), Gtk::Button("Speed Down"), Gtk::Button("Right Turn")}), m_connect_button("Connect"), m_disconnect_button("Disconnect"), m_stop_button("Stop"){
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

        //Initialisation de la grille pour les boutons
        m_grid_button.set_row_spacing(4);
        m_grid_button.set_column_spacing(4);
        m_grid_button.set_row_homogeneous(true);
        m_grid_button.set_row_homogeneous(true);
        m_grid_button.set_column_homogeneous(true);


        //Initialisation des boutons et placement de ceux-ci dans la grille
        m_connect_button.set_can_focus(false);
        m_box_inputs.pack_start(m_connect_button, Gtk::PACK_SHRINK);
	m_disconnect_button.set_can_focus(false);
	m_box_inputs.pack_start(m_disconnect_button, Gtk::PACK_SHRINK);
	m_stop_button.set_can_focus(false);
	m_box_inputs.pack_start(m_stop_button, Gtk::PACK_SHRINK);
        for(int i = 0;i<BUTTON_NUMBER;i++){
                (m_direction_buttons + i)->set_can_focus(false);
                m_grid_button.attach(*(m_direction_buttons + i), i%3, i-i%3, 1, 1);
        }

        //Centrage et ajout de la grille dans la box des inputs
        m_grid_button.set_halign(Gtk::ALIGN_CENTER);
        m_grid_button.set_valign(Gtk::ALIGN_CENTER);
        m_box_inputs.pack_start(m_grid_button, Gtk::PACK_EXPAND_WIDGET);
        //Organisation de la box principale
        m_box_main.pack_start(m_image, Gtk::PACK_SHRINK);
        m_box_main.pack_start(m_box_inputs, Gtk::PACK_SHRINK);
        this->add(m_box_main);
        m_box_main.set_can_focus(true);
        this->set_focus(m_box_main);
        this->show_all();

        m_connect_button.signal_clicked().connect([this]() {
			this->ip = m_entry_ip.get_text();
                        this->m_connect = true;
                        });
	m_disconnect_button.signal_clicked().connect([this]() {
			this->m_disconnect = true;
			});
	m_stop_button.signal_clicked().connect([this]() {
			this->m_stop = true;
			});
        for(int i = 0;i<BUTTON_NUMBER;i++){
                (m_direction_buttons + i)->signal_clicked().connect([this, i]() {
                                *(this->m_direction+i) = true;
                                });
        }

        m_p_thread = new std::thread([this, &limobot]() {this->run(limobot);});


}

Gui::~Gui(){
        delete[] m_direction_buttons;
        if(m_p_thread->joinable()){
                m_p_thread->join();
        }
        delete m_p_thread;
}


//Multi-threading
void Gui::run(LimoBot& limobot){
        while(true){
                if(m_connect) {
                        limobot.connect(this->ip);
                        this->m_connect = false;
                }
		if(m_disconnect) {
			limobot.disconnect();
			this->m_disconnect = false;
		}
		if(m_stop) {
			limobot.stop();
			this->m_stop = false;
		}
                if(*(m_direction)){
                        limobot.rotate(0);
                        *(this->m_direction) = false;
                }
                if(*(m_direction+1)){
                        limobot.speed_up();
                        *(this->m_direction+1) = false;
                }
                if(*(m_direction+2)){
                        limobot.rotate(1);
                        *(this->m_direction+2) = false;
                }
                if(*(m_direction+3)){
                        limobot.turn(0);
                        *(this->m_direction+3) = false;
                }
                if(*(m_direction+4)){
                        limobot.speed_down();
                        *(this->m_direction+4) = false;
                }
                if(*(m_direction+5)){
                        limobot.turn(1);
                        *(this->m_direction+5) = false;
                }
        }
}
