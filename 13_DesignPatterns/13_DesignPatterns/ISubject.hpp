#pragma once

class IObserver;

class ISubject {
public:
	virtual void attach(IObserver* o) = 0;
	virtual void detach(IObserver* o) = 0;
	virtual void notify() = 0;
	virtual ~ISubject() = default;
};