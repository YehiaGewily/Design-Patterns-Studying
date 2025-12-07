/*
 * Design Patterns - EventBroker
 * Author: Yehya
 * Description: Implementation of the EventBroker pattern in C++.
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
#include <boost/signals2.hpp>

using namespace boost::signals2;

struct EventData
{
	virtual void print() const = 0;
};

struct PlayerScoreData : EventData
{
	string player_name;
	int goals_scored;

	PlayerScoreData(const string& player_name, int goals_scored) : player_name(player_name), goals_scored(goals_scored) {}

	void print() const override {
		cout << player_name << " has scored (their "
			<< goals_scored + 1 <<" goal" << endl;
	}
};

struct Game
{
	signal<void(EventData*)> events;
};

struct Player
{
	string name;
	int goals_scored{ 0 };
	Game& game;

	Player(string name, Game& g) :name(name), game(g) {}

	void score()
	{
		goals_scored++;
		PlayerScoreData ps{ name, goals_scored };
		game.events(&ps);
	}
};

struct Coach
{
	Game& game;
	Coach(Game& g) :game(g) {
		game.events.connect([](EventData* e) 
		{
				PlayerScoreData* ps = dynamic_cast<PlayerScoreData*>(e);
				if (ps && ps->goals_scored < 3) {
					cout << "coach says: well done " << ps->player_name << "!\n";
				}
		});
	}

};

int main()
{
	Game game;
	Player player("Meero",game);
	Coach Guardiola(game);

	player.score();
	player.score();
	player.score();

}
