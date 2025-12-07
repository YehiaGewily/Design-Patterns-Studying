/*
 * Design Patterns - Flyweight
 * Author: Yehya
 * Description: Implementation of the Flyweight pattern in C++.
 */

#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <sstream>
#include <type_traits>
#include <concepts>
#include <boost/concept_check.hpp>
#include <boost/bimap/bimap.hpp>
#include <boost/bimap.hpp>
#include <functional>

using namespace std;
using namespace boost;

typedef uint32_t key; 

struct User{
protected:
	key firstName, lastName;
	static bimap<key, string> names;
	static key seed;

	static key add(const string& s)
	{
		auto it = names.right.find(s);
		if (it == names.right.end())
		{
			key id = ++seed;
			names.insert({ seed,s });
			return id;
		}

		return it->second;
	}



public:
	User(const string& firstName, const string& lastName)
		:firstName(add(firstName)), lastName(add(lastName))
	{
	}

	const string& getFirstName()const {
		return names.left.find(firstName)->second;
	}

	const string& getLastName()const {
		return names.left.find(lastName)->second;
	}
};

key User::seed = 0;
bimap<key, string> User::names{};

ostream& operator<<(ostream& os, const User& user) {
	os << "first name: " << user.getFirstName() << " last name: " << user.getLastName();
	return os;
}


struct User2
{
	flyweight<string> firstName, lastName;

	User2(const string& firstName, const string &lastName)
		:firstName(firstName), lastName(lastName) {}
	
};

int main()
{
	
	User u1{ "John" , "Smith" };
	User u2{ "John" ,"Smith" };

	cout << u1 << endl;
	cout << u2 << endl;

	User2 u11{ "James","Steve" };
	User2 u22{ "James","Steve" };


}
