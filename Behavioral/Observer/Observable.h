/*
 * Design Patterns - Observable
 * Author: Yehya
 * Description: Implementation of the Observable pattern in C++.
 */

#pragma once
#include <vector>
#include <string>
#include "Observer.h"
using namespace std;


template<typename T>
struct Observable
{
	vector<Observer<T>*> observers;

	void notify(T& source, const string& field_name)
	{
		for (auto observer : observers)
		{
			observer->field_changed(source, field_name);
		}
	}
	void subscribe(Observer<T> &observer)
	{
		observers.push_back(observer);
	}

	void unsubscribe(Observer<T>& observer)
	{
		observers.erase(observer);
	}
	
};

