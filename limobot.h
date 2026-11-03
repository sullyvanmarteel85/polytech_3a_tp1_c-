#ifndef LIMOBOT_H
#define LIMOBOT_H
#define PAS_CONSIGNE 5
#define PAS_TOURNANT 0.2
#define LOOP_TIME 200
#include"order.h"
#include<unistd.h>
#include<thread>
#include<stdio.h>
#include<iostream>

class LimoBot{
	public:
		LimoBot();
		~LimoBot();
		void stop();
		void speed_up();
		void speed_down();
		void turn(bool direction);
		void rotate(bool direction);
		void print_order_speed();
	private:
		Order m_order;
		bool m_stop;
		std::thread m_thread;
		void run();

};

#endif
