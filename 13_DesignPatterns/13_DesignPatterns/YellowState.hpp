#include "IState.hpp"
#include <iostream>

class TrafficLight;

class YellowState : public IState {
public:
	void handle(TrafficLight& s) override;
};