/*
 * Design Patterns - StaticDecorator
 * Author: Yehya
 * Description: Implementation of the StaticDecorator pattern in C++.
 */

#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <sstream>
#include <type_traits>
#include <concepts>
#include <boost/concept_check.hpp>

using namespace std;
using namespace boost;

struct Shape
{
	virtual string str() const = 0;
};

struct Circle : Shape
{
	float radius;

	explicit Circle(float radius) :radius(radius) {}

	void resize(float factor) {
		radius *= factor;
	}

	string str() const override {
		ostringstream oss;
		oss << "A circle of radius: " << radius;
		return oss.str();
	}
};

struct Square : Shape
{
	float side;
	Square() {}
	Square(float s) :side(s) {}

	string str() const override {
		ostringstream oss;
		oss << "A square of side: " << side;

		return oss.str();
	}
};

struct ColoredShape : Shape 
{
	Shape& shape;
	string color;

	ColoredShape(Shape &s, string c) : shape(s), color(c) {}

	string str() const override {
		ostringstream oss;
		oss << shape.str() << " has the color " << color;


		return oss.str();
	}
};

struct TransparentShape : Shape
{
	Shape& shape;
	uint8_t transparency;
	TransparentShape(Shape& shape, uint8_t transparency) :shape(shape), transparency(transparency) {}
	
	string str() const override {
		ostringstream oss;
		oss << shape.str() << " has "
			<< static_cast<float>(transparency) / 255.f * 100.f
			<< "% transparency";

		return oss.str();
	}

};

//mixing inheritance
//perfect forwarding

template<typename T>
bool IsAShape = BOOST_CONCEPT_ASSERT((EqualityComparable<T>));

template<typename T>
struct ColoredShape2 : T
{
	string color;
	ColoredShape2() {}

	template<typename ...Args>
	ColoredShape2(const string& color, Args ...args)
		:T(std::forward<Args>(args)...), color(color)
	{

	}

	string str()const override {
		ostringstream oss;
		oss << T::str() << " has the color: " << color;
		return oss.str();
	}
};

template<IsAShape T>
struct TransparentShape2 : T
{
	Shape& shape;
	uint8_t transparency;

	template<typename ...Args>
	TransparentShape2(const uint8_t transparency, Args ...args)
	:T(std::forward<Args>(args)...), transparency(transparency)
	{

	}

	string str() const override {
		ostringstream oss;
		oss << shape.str() << " has "
			<< static_cast<float>(transparency) / 255.f * 100.f
			<< "% transparency";

		return oss.str();
	}

};

int main()
{
		
	Square square{ 5 };
	ColoredShape red_square{ square, "red" };
	cout << square.str() << " "<<red_square.str() << endl;

	TransparentShape mySquare{ red_square, 51 };

	cout << mySquare.str() << endl;

	ColoredShape2<Circle> greenCircle{"green",5};

	cout << greenCircle.str() << endl;

	TransparentShape2<ColoredShape2<Square>> TraSqr{ 0,"blue",10 };
	TraSqr.color = "light blue";
	cout < TraSqr.str() << endl;
}
