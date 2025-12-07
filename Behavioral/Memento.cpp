/*
 * Design Patterns - Memento
 * Author: Yehya
 * Description: Implementation of the Memento pattern in C++.
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <memory>

using namespace std;

class Memento
{
	int balance;
public:
	Memento(int b) :balance(b) {}

	friend class BankAccount;
	friend class BankAccount2;

};

class BankAccount
{
	int balance{ 0 };

public:
	BankAccount(int balance) :balance(balance) {}

	Memento deposit(int amount) {
		balance += amount;
		return {balance};
	}

	void restore(const Memento& m)
	{
		balance = m.balance;
	}

	friend ostream& operator<<(ostream& os, const BankAccount& acc)
	{
		os << "balance: " << acc.balance;
		return os;
	}

};

class BankAccount2
{
	int balance{ 0 };
	vector<shared_ptr<Memento>> changes;
	int current;

public:
	BankAccount2(int balance) :balance(balance)
	{
		changes.emplace_back(make_shared<Memento>(balance));
		current = 0;
	}

	shared_ptr<Memento> deposit(int amount)
	{
		balance += amount;
		auto m = make_shared<Memento>(balance);
		changes.push_back(m);
		current++;
		return m;
	}

	void restore(const shared_ptr<Memento>& m)
	{
		if (m)
		{
			balance = m->balance;
			changes.push_back(m);
			current = changes.size() - 1;
			
		}
	}

	shared_ptr<Memento> undo()
	{
		if (current > 0)
		{
			--current;
			auto m = changes[current];
			balance = m->balance;
		}
		return {};
	}

	shared_ptr<Memento> redo()
	{
		if (current + 1 < changes.size())
		{
			++current;
			auto m = changes[current];
			balance = m->balance;
			return m;
		}
		return {};
	}

	friend ostream& operator<<(ostream& os, const BankAccount2& acc)
	{
		os << "balance: " << acc.balance;
		return os;
	}
};


int main()
{
	
	BankAccount ba{ 100 };
	auto m1 = ba.deposit(50);
	auto m2 = ba.deposit(25);

	cout << ba << "\n";

	ba.restore(m1);
	cout<<"back to m1: " << ba << "\n";
	ba.restore(m2);
	cout << "back to m1: " << ba << "\n";

	BankAccount2 ba2{ 100 };
	ba2.deposit(50);
	ba2.deposit(20);
	cout << ba2 << endl;

	ba2.undo();
	cout<<"undo 1: " << ba2 << endl;
	
	ba2.undo();
	cout << "undo 2: " << ba2 << endl;

	ba2.redo();
	cout << "redo: " << ba2 << endl;

	

}
