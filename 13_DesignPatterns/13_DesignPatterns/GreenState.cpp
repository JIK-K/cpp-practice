#include "GreenState.hpp"
#include "YellowState.hpp"
#include "TrafficLight.hpp"

void GreenState::handle(TrafficLight& light) {
	std::cout << "Green - 출발" << "\n";
	light.setState(new YellowState());
}