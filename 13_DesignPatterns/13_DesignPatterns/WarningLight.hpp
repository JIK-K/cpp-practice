
#include <string>

#include "IObserver.hpp"
#include "ISubject.hpp"
#include "Logger.hpp"

class WarningLight : public IObserver {
public:
	void update(double value) override {
		if (value >= 90.0f) {
			Logger::getInstance().log("Warning Light ON - TEMP : "
				+ std::to_string(value));
		}
	}
};