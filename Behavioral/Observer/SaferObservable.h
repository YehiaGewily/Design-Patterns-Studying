/*
 * Design Patterns - SaferObservable
 * Author: Yehya
 * Description: Implementation of the SaferObservable pattern in C++.
 */

#pragma once
#include <vector>
#include <string>
#include <mutex>
using namespace std;

template<typename> struct Observer;

template<typename T>
class SaferObservable
{
	vector<Observer<T>*> observers;
	typedef std::recursive_mutex mutex_t;
	mutex_t mtx;
public:

	void notify(T& source, const string& field_name)
	{
		std::scoped_lock<mutex_t> lock(mtx);


		for (auto observer : observers)
		{
			if(observer)
			observer->field_changed(source, field_name);
		}
	}
	void subscribe(Observer<T>& observer)
	{
		observers.push_back(&observer);
	}

	void unsubscribe(Observer<T>& observer)
	{
		auto it = find(observers.begin(), observers.end(), &observer);
		if (it != observers.end())
		{
			*it = nullptr;
		}

		/*observers.erase(
			remove(observers.begin(), observers.end(), observer), observers.end()
		);*/
	}
};

