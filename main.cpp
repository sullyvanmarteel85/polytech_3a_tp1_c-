#include"limobot.h"
#include<iostream>
#include<stdio.h>
#include<chrono>
#include<string>

int main(){
	LimoBot robot;
	std::string ip = "";
	std::cout << "Entrez l'ip:";
	std::cin >> ip;
	robot.connect(ip);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	for(int i = 0; i < 20;i++){
		robot.speed_up();
	}
	std::this_thread::sleep_for(std::chrono::seconds(1));
	for(int i = 0; i < 10;i++){
		robot.speed_down();
	}
	std::this_thread::sleep_for(std::chrono::seconds(1));
	robot.rotate(1);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	robot.rotate(0);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	robot.stop();
	std::cout << "\n";
	return 0;
}
