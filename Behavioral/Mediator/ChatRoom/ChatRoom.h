/*
 * Design Patterns - ChatRoom
 * Author: Yehya
 * Description: Implementation of the ChatRoom pattern in C++.
 */

#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <functional>

using namespace std;

#include "Person.h"

struct ChatRoom
{
	vector<Person*> people;

	void broadcast(const string& origin, const string& message);
	
	void join(Person* p);

	void message(const string& origin, const string& who, const string& message)
	{
		auto target = find_if(begin(people), end(people), [&](const Person* p) {return p->name == who; });

		if (target != end(people)) {
			(*target)->recieve(origin, message);
		}
	}
};

