#ifndef LIMOBOT_H
#define LIMOBOT_H
#define PAS_CONSIGNE 5
#define PAS_TOURNANT 0.2
#include"order.h"
#include<unistd.h>

class LimoBot{
	public:
		LimoBot();
		void stop();
		void speed_up();
		void speed_down();
		void turn(bool direction);
		void rotate(bool direction);
		Order get_order() const;
	private:
		Order m_order;

};

#endif
