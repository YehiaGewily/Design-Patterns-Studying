/*
 * Design Patterns - SingletonDependencyInjection
 * Author: Yehya
 * Description: Implementation of the SingletonDependencyInjection pattern in C++.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <fstream>
#include <iomanip>
#include <gtest/gtest.h>


using namespace std;

class Database
{
public:
	virtual  int getPopulation(const string& name) = 0;

};

class SingletonDatabase
{
private:
	map<string, int> m;

	SingletonDatabase() {
		cout << "Database initialized" << endl;

		ifstream ifs("Capitals.txt");

		string s1, s2;

		while (getline(ifs, s1))
		{
			getline(ifs, s2);
			int pop = stoi(s2);
			m[s1] = pop;
		}
	}
public:

	static SingletonDatabase& get()
	{
		static SingletonDatabase db;
		return db;
	}

	int getPopulation(const string& name)
	{
		return m[name];
	}

	SingletonDatabase(SingletonDatabase const&) = delete;
	void operator=(SingletonDatabase const&) = delete;
};

class DummyDatabase : public Database
{
	map<string, int> capitals;
public:
	DummyDatabase()
	{
		capitals["alpha"] = 1;
		capitals["beta"] = 2;
		capitals["gama"] = 3;

	}
	int getPopulation(const string& name)override {
		return capitals[name];
	}
};

struct SingletonRecordFinder
{
	int totalPopulation(vector<string> names)
	{
		int result{ 0 };
		for (auto& name : names)
		{
			result += SingletonDatabase::get().getPopulation(name);
		}
		return result;
	}
};

struct ConfigurableRecordFinder
{
	Database& db;

	ConfigurableRecordFinder(Database& db) :db(db) {}

	int totalPopulation(vector<string> names)
	{
		int result{ 0 };
		for (auto& name : names)
		{
			result += db.getPopulation(name);
		}
		return result;
	}

};

TEST(RecordFinderTests, SingletonTotalPopulationTest)
{
	SingletonRecordFinder rf;
	vector<string> names{ "TOKYO","DELHI" };
	int totalPop = rf.totalPopulation(names);

	EXPECT_EQ(17500000 + 174000000, totalPop);

}

TEST(RecordFinderTests, DependendatTotalPopulationTest)
{
	DummyDatabase db;
	ConfigurableRecordFinder rf{ db };

	EXPECT_EQ(4, rf.totalPopulation(vector<string>{"alpha", "gamma"}));

}

int main(int ac, char* av[])
{
	testing::InitGooglTest(&ac, av);
	return RUN_ALL_TESTS();
}
