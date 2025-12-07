/*
 * Design Patterns - Multiton
 * Author: Yehya
 * Description: Implementation of the Multiton pattern in C++.
 */

#include <map>
#include <memory>
#include <iostream>


using namespace std;

enum class Importance
{
	primary,
	secondary,
	teritary
};

template<typename T, typename Key = std::string>
class Multiton
{
public:
	static shared_ptr<T> get(const Key& key)
	{
		if (const auto it = instances.find(key);
			it != instances.end()) {
			return it->second;
		}

		auto instance = make_shared<T>();
		instance[key] = instance;
		return instance;
	}
protected:
	Multiton() = default;
	virtual ~Multiton() = default;
	Multiton(Multiton const&) = delete;
	void operator=(Multiton const&) = delete;


private:
	static map<Key, shared_ptr<T>> instances;

};

template<typename T, typename Key>
map<Key, shared_ptr<T>> Multiton<T, Key>::instances;

class Printer
{
	Printer() {
		++Printer::totalInstanceCount;
		cout << "A total of: " << Printer::totalInstanceCount << " instances created" << endl;
	}

private:
	static int totalInstanceCount;
};
int Printer::totalInstanceCount = 0;


int main()
{
	typedef Multiton<Printer, Importance> mt;

	auto main = mt::get(Importance::primary);
	auto aux = mt::get(Importance::secondary);
	auto aux2 = mt::get(Importance::secondary);

}
