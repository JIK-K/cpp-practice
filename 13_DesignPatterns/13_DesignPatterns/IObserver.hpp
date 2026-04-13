#pragma once

class IObserver {
public:
	virtual void update(double value) = 0;
	virtual ~IObserver() = default;
};