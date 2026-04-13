#include "RedState.hpp"
#include "GreenState.hpp"
#include "TrafficLight.hpp"

void RedState::handle(TrafficLight& light) {
	std::cout << "RED - 정지" << "\n";
	light.setState(new GreenState());
}