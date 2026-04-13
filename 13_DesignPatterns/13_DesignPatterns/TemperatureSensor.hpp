#pragma once

#include <vector>
#include <algorithm>
#include "ISubject.hpp"
#include "IObserver.hpp"

class TemperatureSensor : public ISubject {
private:
	std::vector<IObserver*	> _observers;
	double _temperature;
public:
	void attach(IObserver* o) override {
		this->_observers.push_back(o);
	}
	void detach(IObserver* o) override {
		_observers.erase(
			std::remove(_observers.begin(), _observers.end(), o),
			_observers.end()
		);
	}
	void notify() override {
		for (IObserver* o : this->_observers) {
			o->update(this->_temperature);
		}
	}
	void setTemperature(double temperature) {
		this->_temperature = temperature;
		this->notify();
	}
};