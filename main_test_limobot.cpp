#include"limobot.h"
#include<iostream>
#include<stdio.h>
#include<chrono>


int main(){
	LimoBot robot;
	
	for(int i=0; i<30; i++){
		std::cout << "Thread [main]\n";
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return 0;
}
