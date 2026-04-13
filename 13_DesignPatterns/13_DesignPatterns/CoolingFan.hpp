
#include "IObserver.hpp"
#include "Logger.hpp"

class CoolingFan : public IObserver {
public:
	void update(double value) override {
		if (value < 60.0f) {
			Logger::getInstance().log("CoolingFan Speed : LOW");
		}
		else if (value < 90.0f) {
			Logger::getInstance().log("CoolingFan Speed : MEDIUM");
		}
		else {
			Logger::getInstance().log("CoolingFan Speed : HIGH");
		}
	}
};