#include <iostream>
#include "TemperatureSensor.hpp"
#include "WarningLight.hpp"
#include "CoolingFan.hpp"

void testObserver() {
	TemperatureSensor sensor;

	WarningLight light;
	CoolingFan fan;

	sensor.attach(&light);
	sensor.attach(&fan);

	sensor.setTemperature(50.0);
	sensor.setTemperature(75.0);
	sensor.setTemperature(95.0);

	sensor.detach(&light);
	std::cout << "\n[WarningLight Detached]" << '\n';
	sensor.setTemperature(100.0);

}