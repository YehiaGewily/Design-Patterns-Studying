/*
 * Design Patterns - PointerChain
 * Author: Yehya
 * Description: Implementation of the PointerChain pattern in C++.
 */

#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <cctype>
#include <queue>

using namespace std;

struct Creature
{
	string name;
	int attack, defense;


	Creature() {}
	Creature(const string& name, int attack, int defense) :name(name), attack(attack), defense(defense) {}


	friend ostream& operator<<(ostream& os, const Creature& c)
	{
		os << "name: " << c.name << " attack: " << c.attack
			<< " defense: " << c.defense << endl;

		return os;
	}
};

class CreatureModifier
{
	CreatureModifier* next{ nullptr };


public:
	Creature* creature;

	CreatureModifier(Creature& c):creature(c)
	{
		
	}


	void add(CreatureModifier* cm)
	{
		if (next) {
			next->add(cm);
		}
		else {
			next = cm;
		}
	}

	virtual void handle()
	{
		if (next) next->handle();

	}
};

class DoubleAttackModifier : public CreatureModifier
{
public:
	DoubleAttackModifier(Creature& creature) : CreatureModifier(creature) {}
	
	void handle() override {
		creature->attack *= 2;
		CreatureModifier::handle();
	}
};

class IncreaseDefenseModifier : public CreatureModifier
{
public:

	IncreaseDefenseModifier(Creature& c) :CreatureModifier{ c } {}

	void handle() override
	{
		if (creature->attack <= 2) {
			creature->defense++;
		}
		CreatureModifier::handle();
	}
};

class NoBonusesModifier : public CreatureModifier
{
public:
	NoBonusesModifier(Creature& c) :CreatureModifier(c) {}

	void handle() override {

	}

};

int main()
{
	Creature Goblin{ "Goblin",1,1 };

	CreatureModifier root{ Goblin };

	DoubleAttackModifier rl{ Goblin };
	DoubleAttackModifier rl2{ Goblin };

	IncreaseDefenseModifier r2{ Goblin };

	NoBonusesModifier curse{ Goblin };
	root.add(&curse); //this breaks the chain of responsibility. because the handle is empty


	root.add(&rl);
	root.add(&rl2);
	root.add(&r2);

	root.handle();



}
