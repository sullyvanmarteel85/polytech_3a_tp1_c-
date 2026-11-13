#include"limobot.h"

//Constructeur, deconstructeur
LimoBot::LimoBot() : m_order(0, 0), m_stop(false), m_p_thread(NULL), m_socket(){
}

LimoBot::~LimoBot() {
	this->disconnect();
}
//Fonctions de mouvement-------------------------------------------------------------------------------------
void LimoBot::stop() {
	m_order.set_order(0, 0);
}

void LimoBot::speed_up() {
	m_order.set_order(m_order.get_order_L() + PAS_CONSIGNE, m_order.get_order_R() + PAS_CONSIGNE);
}

void LimoBot::speed_down() {
	m_order.set_order(m_order.get_order_L() - PAS_CONSIGNE, m_order.get_order_R() - PAS_CONSIGNE);
}

void LimoBot::turn(bool direction){
	m_order.set_order( short(m_order.get_order_L() * ((direction ? 1 + PAS_TOURNANT : 1 - PAS_TOURNANT))), short(m_order.get_order_R() * (direction ? 1.0 - PAS_TOURNANT : 1.0 + PAS_TOURNANT)));
}

void LimoBot::rotate(bool direction){
	stop();
	usleep(1000000);
	m_order.set_order( direction ? ROTATE_SPEED : -ROTATE_SPEED, direction ? -ROTATE_SPEED : ROTATE_SPEED);
}

void LimoBot::print_order_speed(){
	std::cout << "Order L:" << m_order.get_order_L() << "\n";
	std::cout << "Order R:" << m_order.get_order_R() << "\n";
}



//Multithreading---------------------------------------------------------------------------------------------
void LimoBot::run() {
	static int cpt;

	while(m_stop == false) {
		//Calcul du signe de vitesse
		unsigned char sign = 0x00;
		if(m_order.get_order_L() >= 0){
			sign+=2;
		}
		if(m_order.get_order_R() >= 0){
			sign+=1;
		}

		//Calcul de la trame: 0xFF05 pour le début, puis la valeur absolue de la vitesse, puis le CRC16 Modbus.
		unsigned char* p_data = new unsigned char[7]{0xFF, 0x05, static_cast<unsigned char>((m_order.get_order_L()<0) ? -m_order.get_order_L() : m_order.get_order_L()), static_cast<unsigned char>((m_order.get_order_R() < 0) ? -m_order.get_order_R() : m_order.get_order_R()), sign, 0x00, 0x00};
		std::cout << "Thread [send]: computing crc\n";
		
		//Calcul du CRC16 Modbus
		//Polynôme caractéristique du CRC16 Modbus: 0XA001, CRC initial: 0xFFFF
		int crc = 0xFFFF, pol = 0xA001;

		for(int i = 1; i < 5; i++) {
			//XOR avec le i-ième octet de la trame
			crc ^= p_data[i];
			for(int j = 0; j < 8; j++) {
				//Pour chaque bit dans l'octet, si crc est impair, décaler crc de 1 et faire XOR
				if((crc & 0x0001) == 1) crc = (crc >> 1) ^ pol;
				//Sinon, décaler CRC
				else crc = crc >> 1;
			}
		}

		//Ajout des bits de poids faible dans la trame
		p_data[5] = static_cast<unsigned char> (crc & 0xFF);
		//Ajout des bits de poids fort dans la trame
		p_data[6] = static_cast<unsigned char> ((crc >> 8) & 0xFF);
		std::cout << "Thread [send]: sending bytes: 0x";
		for(int i = 0; i < 7;i++){
			std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(*(p_data + i));
		}
		std::cout<<"\n";

		//Envoie de la trame au port LIMOPORT de l'adresse ip entrée lors de la connexion
		m_socket.send(p_data, 7);
		std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_TIME));
	}
	std::cout << "Thread [send]: stop !\n\n";
}


//Connectivite

void LimoBot::connect(std::string ip){
	std::cout << "Connecting to " << ip << ":" << LIMOPORT << "\n";
	m_socket.open(ip,LIMOPORT);
	if(m_socket.is_open()){
		m_p_thread = new std::thread([this] {run();});
	}
}

void LimoBot::disconnect() {
	if(m_socket.is_open()){
		m_socket.close();
	}
	m_stop = true;
	if(m_p_thread->joinable()){
		m_p_thread->join();
	}
	delete m_p_thread;
}
