/*
 * Design Patterns - Strategy
 * Author: Yehya
 * Description: Implementation of the Strategy pattern in C++.
 */

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>
using namespace std;

enum class OutputFormat 
{
	markdown,
	html
};

struct ListStrategy
{
	virtual void start(ostringstream& oss) {}
	virtual void add_list_item(ostringstream& oss, const string& item) = 0;
	virtual void end(ostringstream& oss) {}
};


struct MarkdownListStrategy : ListStrategy {
	
	void add_list_item(ostringstream& oss, const string& item) override {
		oss << "* " << item << "\n";
	};

};

struct HTMLListStrategy : ListStrategy {
	void start(ostringstream& oss) {
		oss << "<ul>\n";
	}
	virtual void add_list_item(ostringstream& oss, const string& item) {
		oss << "<li>" << item << "</li>\n";
	}
	virtual void end(ostringstream& oss) {
		oss << "</ul>\n";
	}
};

//dynamic text processor(dynamic strategy)
struct DynamicTextProcessor
{
private:
	ostringstream oss;
	unique_ptr<ListStrategy> list_strategy;

public:

	void set_output_format(const OutputFormat& format)
	{
		switch (format)
		{
		case OutputFormat::markdown:
			list_strategy = make_unique<MarkdownListStrategy>();
				break;
		case OutputFormat::html:
			list_strategy = make_unique<HTMLListStrategy>();
			break;
		}
	}

	void append_list(vector<string> &items)
	{
		list_strategy->start(oss);

		for (auto item : items)
			list_strategy->add_list_item(oss, item);

		list_strategy->end(oss);
	}

	string str() {
		return oss.str();
	}

	void clear()
	{
		oss.str("");
		oss.clear();
	}
};


//static text processor(static strategy)
template<typename LS>
struct StaticTextProcessor
{
private:
	ostringstream oss;
	LS list_strategy;

public:
	void append_list(vector<string>& items)
	{
		list_strategy->start(oss);

		for (auto item : items)
			list_strategy->add_list_item(oss, item);

		list_strategy->end(oss);
	}

	string str() {
		return oss.str();
	}

	void clear()
	{
		oss.str("");
		oss.clear();
	}
};

int main()
{
	vector<string> items{ "foo","bar","baz" };

	cout << "DYNAMIC STRATEGY" << endl;
	DynamicTextProcessor dtp;

	dtp.set_output_format(OutputFormat::markdown);
	dtp.append_list(items);
	cout << dtp.str()<<"\n";
	dtp.clear();

	dtp.set_output_format(OutputFormat::html);
	dtp.append_list(items);
	cout << dtp.str() << "\n";
	dtp.clear();

	cout << "STATIC STRATEGY" << endl;


	StaticTextProcessor<MarkdownListStrategy> mstp;
	mstp.append_list(items);
	cout << mstp.str() << "\n";

	StaticTextProcessor<HTMLListStrategy> hstp;
	hstp.append_list(items);
	cout << hstp.str() << "\n";


}
