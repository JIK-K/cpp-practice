#include "TrafficLight.hpp"
#include "RedState.hpp"

void testState() {
	TrafficLight light;
	light.setState(new RedState());

	for (int i = 0; i < 6; i++) {
		light.update();
	}
}