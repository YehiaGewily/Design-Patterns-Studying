/*
 * Design Patterns - Builder
 * Author: Yehya
 * Description: Implementation of the Builder pattern in C++.
 */

#include <iostream>
#include <vector>
#include <ostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <tuple>
#include <cstdio>

using namespace std;

class HtmlElement
{
	friend class HtmlBuilder; //allows HtmlBuilder to access private members hence access the constructors
	string name, text;
	vector<HtmlElement> elements;
	const size_t indent_size = 2;

	HtmlElement() {}

	HtmlElement(const string& name, const string& text) : name(name), text(text) {}

//this way we force the API users to use the builder instead of being able to initialize an html element obj.
public:
	string str(int indent = 0) const {
		
		ostringstream oss;
		string i(indent_size * indent, ' ');
		oss << i << "<" << name << ">" << endl;

		if (text.size() > 0)
			oss << string(indent_size * (indent + 1), ' ') << text << endl;

		for (const auto& e : elements) {
			oss << e.str(indent + 1) << endl;
		}

		oss << i << "</" << name << ">" << endl;
		
		return oss.str();
	}

	static HtmlBuilder build(string root_name)
	{
		return {root_name};
	}

	static unique_ptr<HtmlBuilder> build2(string root_name)
	{
		return make_unique<HtmlBuilder>(root_name);
	}

	static HtmlBuilder create(string root_name)
	{
		return { root_name };
	}
};

//the builder pattern
struct HtmlBuilder
{
	HtmlElement root;

	HtmlBuilder(string root_name)
	{
		root.name = root_name;
	}

	HtmlBuilder& add_child(string child_name, string child_text)
	{
		HtmlElement e{ child_name, child_text };
		root.elements.emplace_back(e);
		return *this; //fluent-builder pattern. 
	}

	//if u want to build up after creating root and adding child
	HtmlElement build() {
		return root;
	}

	string str() const {
		return root.str();
	}

	operator HtmlElement() const {
		return std::move(root);
	}
};

int main()
{

	HtmlBuilder builder{ "ul" };
	builder.add_child("li", "hello").add_child("li", "world"); //fluent-builder allows you to do so

	cout << builder.str() << endl;

	HtmlBuilder elem = HtmlElement::build("ul").add_child("", ""); //because operator HtmlElement returns root

	//optimal way to build
	HtmlElement::create("div").add_child("table","my table").add_child("tr","first row").build();

	return 0;
}
