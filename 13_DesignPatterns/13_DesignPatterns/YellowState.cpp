#include "YellowState.hpp"
#include "RedState.hpp"
#include "TrafficLight.hpp"

void YellowState::handle(TrafficLight& light) {
	std::cout << "YELLOW - 준비" << "\n";
	light.setState(new RedState());
}