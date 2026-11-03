#include"order.h"
Order::Order(short left, short right) {
	m_order_L = left;
	m_order_R = right;
	limit();
}

void Order::limit() {
	//Il faut que m_order_L puisse être négatif, et que la valeur absolue soit majorée par SPEED_MAX.
	
	//Si la valeur absolue est plus grande que SPEED_MAX, on cape.
	m_order_L = (/*Valeur absolue de m_order_L est plus grand que SPEED_MAX ?*/((m_order_L < 0) ? -m_order_L : m_order_L) > SPEED_MAX) ? ( m_order_L < 0 ? -SPEED_MAX : SPEED_MAX) : m_order_L;//Si oui, on cape sans oublier le signe si on le fait.
	m_order_R = (/*Valeur absolue de m_order_R est plus grand que SPEED_MAX ?*/((m_order_R < 0) ? -m_order_L : m_order_L) > SPEED_MAX) ? ( m_order_R < 0 ? -SPEED_MAX : SPEED_MAX) : m_order_R;//Si oui, on cape sans oublier le signe si on le fait.
}

short Order::get_order_R() const {
	return m_order_R;
}

short Order::get_order_L() const {
	return m_order_L;
}

void Order::set_order(short left, short right){
	m_order_L = left;
	m_order_R = right;
	limit();
}
