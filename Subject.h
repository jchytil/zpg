/*
* Author: Jakub Chytil
* Login: CHY0105
* File: Subject.h
*/
#pragma once
#include <vector>
#include "Observer.h"

class Subject
{
private:
	std::vector<Observer*> observers;

public:
	void Attach(Observer* observer)
	{
		observers.push_back(observer);
	}

	void Notify()
	{
		for (Observer* observer : observers)
		{
			observer->Update();
		}
	}
};