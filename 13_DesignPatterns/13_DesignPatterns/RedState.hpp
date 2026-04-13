#include "IState.hpp"
#include <iostream>

class TrafficLight;

class RedState : public IState {
public:
	void handle(TrafficLight& s) override;
};