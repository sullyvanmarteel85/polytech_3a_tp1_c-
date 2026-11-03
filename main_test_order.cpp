#include<stdio.h>
#include<iostream>
#include"order.h"
void test_orders(Order obj) {
	std::cout << "Order L:" << obj.get_order_L() << "\n";
	std::cout << "Order R:" << obj.get_order_R() << "\n";
}

int main(){
	Order obj;
	test_orders(obj);
	std::cout << "\nTesting set_order(50, -50)...\n";
	obj.set_order(50, -50);
	test_orders(obj);
	std::cout << "\nTesting set_order (10000, -10000)\n";
	obj.set_order(10000, -10000);
	test_orders(obj);

	return 0;
}
