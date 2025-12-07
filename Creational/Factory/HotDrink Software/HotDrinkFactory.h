/*
 * Design Patterns - HotDrinkFactory
 * Author: Yehya
 * Description: Implementation of the HotDrinkFactory pattern in C++.
 */

#pragma once
#include "HotDrink.h"
#include <memory>

struct HotDrinkFactory
{
	virtual unique_ptr<HotDrink> make() const = 0;
};

struct TeaFactory : HotDrinkFactory
{
	unique_ptr<HotDrink> make() const override {
		return make_unique<Tea>();
	}
};

struct CoffeeFactory : HotDrinkFactory
{
	unique_ptr<HotDrink> make() const override {
		return make_unique<Coffee>();
	}
};
 
