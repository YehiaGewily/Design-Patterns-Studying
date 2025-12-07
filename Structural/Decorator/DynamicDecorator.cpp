/*
 * Design Patterns - DynamicDecorator
 * Author: Yehya
 * Description: Implementation of the DynamicDecorator pattern in C++.
 */

#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <sstream>

using namespace std;

struct Shape
{
	virtual string str() const = 0;
};

struct Circle : Shape
{
	float radius;

	Circle(float radius) :radius(radius) {}

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

int main()
{
		
	Square square{ 5 };
	ColoredShape red_square{ square, "red" };
	cout << square.str() << " "<<red_square.str() << endl;

	TransparentShape mySquare{ red_square, 51 };

	cout << mySquare.str() << endl;
}
