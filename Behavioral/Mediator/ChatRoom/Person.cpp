/*
 * Design Patterns - Person
 * Author: Yehya
 * Description: Implementation of the Person pattern in C++.
 */

#include "Person.h"
#include "ChatRoom.h"
#include <iostream>
using namespace std;

Person::Person(const string& name) :name(name)
{

}

void Person::say(const string& message)const {
	room->broadcast(name, message);
}

void Person::pm(const string& who, const string& message) {
	room->message(name, who, message);
}

void Person::recieve(const string& origin, const string& message) {
	string s{ origin + ":\"" + message + "\"" };
	cout << "[" << name << "'s chat session] " << s << "\n";
	chat_log.emplace_back(s);

}
bool Person::operator==(const Person& rhs) const{
	return name == rhs.name;
}

bool Person::operator!=(const Person& rhs) const{
	return name != rhs.name;
}