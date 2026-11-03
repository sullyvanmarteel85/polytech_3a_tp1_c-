#include"limobot.h"
LimoBot::LimoBot() : m_order(0, 0){
}

void LimoBot::stop() {
	m_order.set_order(0, 0);
}

void LimoBot::speed_up() {
	m_order.set_order(m_order.get_order_L() + PAS_CONSIGNE_UPDOWN, m_order.get_order_R() + PAS_CONSIGNE_UPDOWN);
}

void LimoBot::speed_down() {
	m_order.set_order(m_order.get_order_L() - PAS_CONSIGNE_UPDOWN, m_order.get_order_R() - PAS_CONSIGNE_UPDOWN);
}

void LimeBot::turn(bool direction){
	m_order.set_order( (short) m_order.get_order_L() * ((direction ? 1 + PAS_TOURNANT : 1 - PAS_TOURNANT), (short) m_order.get_order_R() * (direction ? 1.0 - PAS_TOURNANT : 1.0 + PAS_TOURNANT));
}

void LimeBot::rotate(bool direction){
	stop();
	usleep(1000000);
	m_order.set_order( direction ? 10 : -10, direction ? -10 : 10);
}

Order LimeBot::get_order() const {
	return m_order;
}


