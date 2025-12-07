/*
 * Design Patterns - DependencyInversion
 * Author: Yehya
 * Description: Implementation of the DependencyInversion pattern in C++.
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>
#include <tuple>

using namespace std;

//Dependency Inversion

/*
High level modules should not depend on 
low-level modules. Both should depend on 
abstraction

Abstractions should not depend on details.
Details should depend on abstractions
*/

enum class Relationship
{
	parent,
	child,
	sibling
};

struct Person {
	string name;
};

struct RelationshipBrowser {
	virtual vector<Person> find_all_children_of(const string &name) = 0;
	
};

struct Relationships : RelationshipBrowser//low-level module
{
	vector<tuple<Person, Relationship, Person>> relations;
	
	void add_parent_and_child(const Person& parent, const Person& child)
	{
		relations.push_back({ parent,Relationship::parent,child });
		relations.push_back({ child,Relationship::child,parent });
	}


	// Inherited via RelationshipBrowser
	vector<Person> find_all_children_of(const string& name) override {
		
		vector<Person> result;
		for (auto&& [first, rel, second] : relations)
		{
			if (first.name == name && rel == Relationship::parent) {
				result.push_back(second);
			}
		}
		return result;
	}

};



struct Research //high-level module
{

	Research(RelationshipBrowser& browser)
	{
		for (auto& child : browser.find_all_children_of("John")) {
			cout << "John has a child called: " << child.name << endl;

		}
	}
};

int main()
{
	Person parent{ "John" };
	Person child{ "Chris" }, child2{"Matt" };

	Relationships relationships;
	relationships.add_parent_and_child(parent, child);
	relationships.add_parent_and_child(parent, child2);

	Research rs(relationships);
	


	return 0;
}

