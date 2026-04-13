#include <iostream>
#include <thread>
#include <string>
#include "Logger.hpp"

void threadLog(int id) {
	Logger& logger = Logger::getInstance();
	logger.log("Thread " + std::to_string(id) + " using logger at " +
		std::to_string((size_t)&logger));
}

void testSingleton() {
	Logger& a = Logger::getInstance();
	Logger& b = Logger::getInstance();

	std::cout << "a Address : " << &a << "\n";
	std::cout << "b Address : " << &b << "\n";

	std::thread t1(threadLog, 1);
	std::thread t2(threadLog, 2);
	std::thread t3(threadLog, 3);

	t1.join();
	t2.join();
	t3.join();
}