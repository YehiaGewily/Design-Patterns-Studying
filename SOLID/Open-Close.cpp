/*
 * Design Patterns - Open-Close
 * Author: Yehya
 * Description: Implementation of the Open-Close pattern in C++.
 */

#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

enum Color{green,red,blue};
enum Size{small,medium,large};


struct Product {
	string name;
	Color color;
	Size size;
};

struct ProductFilter
{
	typedef vector<Product*> Items;

	Items filterByColor(Items items, const Color c)
	{
		Items result;
		for (auto& i : items)
		{
			if (i->color == c) {
				result.push_back(i);
			}
		}
		return result;
	}

	Items filterBySize(Items items, Size s)
	{
		Items result;
		for (auto& i : items)
		{
			if (i->size == s)
				result.push_back(i);
		}
		return result;
	}

	Items filterBySizeAndColor(Items items, const Color c, const Size s)
	{
		Items result;
		for (auto& i : items)
		{
			if (i->size == s and i->color == c)
			{
				result.push_back(i);
			}
		}
		return result;
	}
};

template<typename T>
struct AndSpecification;

template<typename T> struct Specification
{
	virtual ~Specification() = default;
	virtual bool isSatisfied(T* item) const = 0;
};

template<typename T> 
AndSpecification<T> operator&&(const Specification<T>& first, const Specification<T>& second)
{
	return { first,second };
}

template<typename T>
struct Filter {
	virtual vector<T*> filter(vector<T*> items, Specification<Product>& spec) = 0;
};

struct BetterFilter : Filter<Product>
{
	vector<Product*> filter(vector<Product*> items, Specification<Product>& spec) override
	{
		vector<Product*> result;
		for (auto& i : items) {
			if (spec.isSatisfied(i))
				result.push_back(i);
		}
		return result;
	}
};

struct ColorSpecification : Specification<Product>
{
	Color color;
	ColorSpecification(Color c)
	{
		color = c;
	}
	bool isSatisfied(Product* item) const override
	{
		return item->color == color;
	}
};


struct SizeSpecification : Specification<Product>
{
	Size size;
	SizeSpecification(Size s) {
		size = s;
	}

	bool isSatisfied(Product* item) const override
	{
		return item->size == size;
	}
};

template <typename T>
struct AndSpecification : Specification<T>
{
	const Specification<T>& first;
	const Specification<T>& second;

	AndSpecification(const Specification<Product*> first, const Specification<Product*> second)
	{
		this->first = first;
		this->second = second;
	}

	bool isSatisfied(T *item)const override
	{
		return  first.isSatisfied(item) && second.isSatisfied(item);
	}
};

int main()
{
	Product apple{ "Apple", Color::green, Size::small };
	Product tree{ "Tree", Color::green, Size::large };
	Product house{ "House",Color::blue, Size::large };

	const vector<Product*> all{ &apple, &tree, &house };

	BetterFilter bf;
	ColorSpecification green(Color::green);
	auto green_things = bf.filter(all, green);
	for (auto& x : green_things) {
		cout << x -> name << " is green\n";
	}

	SizeSpecification large(Size::large);
	AndSpecification<Product> green_and_large(green, large);
	
	auto spec = green && large;
	for (auto& x : bf.filter(all, spec))
		cout << x->name << " is green and large\n";
	
}

