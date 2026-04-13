#include "IState.hpp"
#include <iostream>

class TrafficLight;

class GreenState : public IState {
public:
	void handle(TrafficLight& s) override;
};