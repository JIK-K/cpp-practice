#pragma once

#include <iostream>

class Logger {
private:
	Logger() {}
public:
	static Logger& getInstance() {
		static Logger instance;
		return instance;
	}
	
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	void log(const std::string& msg) {
		std::cout << "[LOG] : " << msg << "\n";
	}
};