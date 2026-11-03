#ifndef LIMOBOT_H
#define LIMOBOT_H
#include"order.h"

class LimoBot{
	public:
		LimoBot();
		void stop();
		void speed_up();
		void speed_down();
		void turn(bool direction);
		void rotate(bool direction);
	private:
		Order m_order;

};

#endif
