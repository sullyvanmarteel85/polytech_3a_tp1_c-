#include"limobot.h"
#include<iostream>
#include<stdio.h>
#include<chrono>


int main(){
	LimoBot robot;

	robot.connect("127.0.0.1");
	for(int i=0; i<8; i++){
		std::cout << "Thread [main]\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	std::cout << "\n";
	return 0;
}
