/*
 * Design Patterns - Composite
 * Author: Yehya
 * Description: Implementation of the Composite pattern in C++.
 */

#include <iostream>
#include <vector>
#include <string>
#include "common.h"
using namespace std;

struct GraphicObject
{
	virtual void draw() = 0;
};

struct Circle : GraphicObject
{
	void draw() override {
		cout << "Circle" << endl;
	}
};

struct Group : GraphicObject
{
	string name;
	vector<GraphicObject*> objects;

	Group(string n) :name{ n } {}

	void draw() override {
		cout << "Group " << name.c_str() << " contains: " << endl;

		for (auto&& o : objects)
		{
			o->draw();
		}
	}
};

int main()
{
	Group root("root");
	Circle c1, c2;

	root.objects.push_back(&c1);

	root.draw();

	Group subgroup("sub");
	subgroup.objects.push_back(&c2);

	root.objects.push_back(&subgroup);

	root.draw();


}
