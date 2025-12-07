/*
 * Design Patterns - ChatRoom
 * Author: Yehya
 * Description: Implementation of the ChatRoom pattern in C++.
 */

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>
#include <cmath>
#include <map>
#include <ostream>
#include <cstdint>
#include <functional>

using namespace std;

#include <boost/iterator/iterator_facade.hpp>

#include "Person.h";
#include "ChatRoom.h";

int main()
{
	ChatRoom room;

	Person john{ "John" };
	Person jane{ "John" };

	room.join(&john);
	room.join(&jane);

	john.say("hi guys");
	jane.say("what's up");

	Person meero{ "Meero" };
	room.join(&meero);

	meero.say("hey guys :D");

	jane.pm(meero.name, "hi meero, are you new here?");


}
