#ifndef LIMOBOT_H
#define LIMOBOT_H
#define PAS_CONSIGNE 5
#define PAS_TOURNANT 0.2
#define LOOP_TIME 200
#define LIMOPORT 15020
#include"order.h"
#include<unistd.h>
#include<thread>
#include<stdio.h>
#include<iostream>
#include<string>
#include"socket.h"

class LimoBot{
	public:
		//Constructeur, Destructeur
		LimoBot();
		~LimoBot();
		//Mouvements
		void stop();
		void speed_up();
		void speed_down();
		void turn(bool direction);
		void rotate(bool direction);
		void print_order_speed();
		//Connectivite
		void connect(std::string ip);
		void disconnect();
	private:
		Order m_order;
		bool m_stop;
		std::thread* m_p_thread;
		Socket_TCP m_socket;
		void run();

};

#endif
