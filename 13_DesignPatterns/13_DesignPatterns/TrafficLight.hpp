#pragma once

#include "IState.hpp"

class TrafficLight {
private:
	IState* _state;

public:
	void setState(IState* s) {
		this->_state = s;
	}
	void update() {
		this->_state->handle(*this);
	}
};