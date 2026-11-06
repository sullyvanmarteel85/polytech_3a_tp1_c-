#include"limobot.h"
#include<iostream>
#include<stdio.h>
#include<chrono>


int main(){
	LimoBot robot;

	robot.connect("192.168.1.150");
	std::this_thread::sleep_for(std::chrono::seconds(1));
	robot.speed_up();
	std::this_thread::sleep_for(std::chrono::seconds(1));
	robot.rotate(1);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	robot.stop();
	std::cout << "\n";
	return 0;
}
