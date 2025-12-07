/*
 * Design Patterns - Observer
 * Author: Yehya
 * Description: Implementation of the Observer pattern in C++.
 */

#pragma once
#include <string>

template<typename T>
struct Observer
{
	virtual void field_changed(
		T& source,
		const std::string& field_changed
	) = 0;

};

