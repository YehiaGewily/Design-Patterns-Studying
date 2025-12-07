/*
 * Design Patterns - FunctionalDecorator
 * Author: Yehya
 * Description: Implementation of the FunctionalDecorator pattern in C++.
 */

#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <sstream>
#include <type_traits>
#include <concepts>
#include <boost/concept_check.hpp>
#include <functional>

using namespace std;
using namespace boost;


struct Logger
{
	function<void()> func;
	string name;

	Logger(const function<void()>& func, const string& name)
	{
		this->func= func;
		this->name = name;
	}

	void operator()()const {
		cout << "Entering " << name << endl;
		func();
		cout << "Exiting " << name << endl;
	}

};

template<typename Func>
struct Logger2
{
	Func func;
	string name;

	Logger2(const Func func, const string& name)
	{
		this->func = func;
		this->name = name;
	}

	void operator()()const {
		cout << "Entering " << name << endl;
		func();
		cout << "Exiting " << name << endl;
	}

};

template<typename Func>
auto make_logger2(Func func, const string& name)
{
	return Logger2<Func>(func, name);
}

void print()
{
	cout << "fuck" << endl;
}

double add(double a, double b)
{
	cout << a << "+" << b << "=" << a + b << endl;

	return a + b;
}

template<typename>
struct Logger3;

template<typename R, typename ...Args>
struct Logger3<R(Args...)>
{
	function<R(Args...)> func;
	string name;

	Logger3(const function<R(Args...)>& func, string n)
	{
		this->func = func;
		this->name = n;
	}

	R operator()(Args ...args) {
		cout << "Entering " << name << endl;
		R result = func(args...);
		cout << "Exiting " << name << endl;
		return result;
	}
};

template<typename R, typename ...Args>
auto make_logger3(R(*func)(Args...), const string& name)
{
	return Logger3<R(Args...)>(
		function<R(Args...)>(func),name
	);
}

int main()
{
	Logger(print, "Hello Function")();

	auto log = make_logger2([]() {cout << "Hello world" << endl; }, "Hello function");

	log();

	auto log_add = make_logger3(add, "Add");
	auto result = log_add(5, 6);


}
