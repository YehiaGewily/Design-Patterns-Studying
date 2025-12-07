/*
 * Design Patterns - GroovyBuilder
 * Author: Yehya
 * Description: Implementation of the GroovyBuilder pattern in C++.
 */

#include <iostream>
#include <vector>
#include <ostream>
#include <sstream>
#include <memory>
#include <fstream>
#include <tuple>
#include <cstdio>
#include <utility>

using namespace std;

struct Tag 
{
	string name;
	string text;
	vector<Tag> children;
	vector<pair<string, string>> attributes;

	friend ostream& operator<<(ostream& os, const Tag& tag)
	{
		os << "<" << tag.name;

		for (const auto& att : tag.attributes)
		{
			os << " " << att.first << "=\"" << att.second << "\"";
		}
		
		if (tag.children.size() == 0 && tag.text.length() == 0)
		{
			os << "/>" << endl;
		}
		else
		{
			os << ">" << endl;

			if (tag.text.length())
				os << tag.text << endl;

			for (const auto& child : tag.children)
				os << child;

			os << "</" << tag.name << ">" << endl;
		}

		return os;
	}

protected:
public:
	Tag(const string& name, const string& text)
	{
		this->name = name;
		this->text = text;
	}

	Tag(const string& name, const vector<Tag> &children)
	{
		this->name = name;
		this->children= children;
	}

};


struct P : Tag
{
	P(const string& text) : Tag("p", text) {}

	P(initializer_list<Tag> children) :
		Tag{ "p",children } {}
};

struct IMG : Tag
{
	explicit IMG(const string& url)
		:Tag{ "img","" }
	{
		attributes.emplace_back("src", url);
	}

};

int main()
{
	cout<<
		P{
		IMG{"http://pokemon.com/pickachi.png"}
		}
	<< endl;
	
	return 0;
}
