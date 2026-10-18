/*
* Author: Jakub Chytil
* Login: CHY0105
* File: Observer.h
*/
#pragma once

class Observer
{
public:
	virtual void Update() = 0;
	virtual ~Observer() = default;
};