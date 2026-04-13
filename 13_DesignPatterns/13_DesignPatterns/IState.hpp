#pragma once

class TrafficLight;

class IState {
public:
	virtual void handle(TrafficLight& light) = 0;
	virtual ~IState() = default;
};