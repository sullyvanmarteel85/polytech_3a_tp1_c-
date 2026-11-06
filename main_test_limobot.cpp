#include"limobot.h"
#include<iostream>
#include<stdio.h>

int main(){
	LimoBot obj;
	obj.print_order_speed();
	
	std::cout << "\nspeed_up...\n";
	obj.speed_up();
	obj.print_order_speed();
	std::cout << "\nspeed_up...\n";
	obj.speed_up();
	obj.print_order_speed();
	std::cout << "speed_down...\n";
	obj.speed_down();
	obj.print_order_speed();

	std::cout << "\nturn(true)...\n";
	obj.turn(true);
	obj.print_order_speed();
	std::cout << "stop...\n";
	obj.stop();
	obj.print_order_speed();
	std::cout << "speed_up...\n";
	obj.speed_up();
	obj.print_order_speed();
	std::cout << "turn(false)...\n";
	obj.turn(false);
	obj.print_order_speed();
	
	std::cout << "\nrotate(true)...\n";
	obj.rotate(true);
	obj.print_order_speed();
	std::cout << "rotate(false)...\n";
	obj.rotate(false);
	obj.print_order_speed();
	std::cout << "stop...\n";
	obj.stop();
	obj.print_order_speed();




	return 0;
}
