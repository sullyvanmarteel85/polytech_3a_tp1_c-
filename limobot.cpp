#include"limobot.h"

LimoBot::LimoBot() : m_order(0, 0), m_stop(false), m_p_thread(new std::thread([this] {run();})){
}










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
	m_order.set_order( direction ? 10 : -10, direction ? -10 : 10);
}

void LimoBot::print_order_speed(){
	std::cout << "Order L:" << m_order.get_order_L() << "\n";
	std::cout << "Order R:" << m_order.get_order_R() << "\n";
}






void LimoBot::run() {
	static int cpt;

	while(m_stop == false) {
		std::cout << "Thread [send]: " << ++cpt << "\n";
		//Code d'émission de la trame
		std::this_thread::sleep_for(std::chrono::milliseconds(LOOP_TIME));
	}
	std::cout << "Thread [send]: stop !\n\n";
}

LimoBot::~LimoBot() {
	m_stop = true;
	if(m_p_thread->joinable()){
		m_p_thread->join();
	}

	delete m_p_thread;
}
