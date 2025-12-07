/*
 * Design Patterns - Prototype
 * Author: Yehya
 * Description: Implementation of the Prototype pattern in C++.
 */

#include <iostream>
#include <string>
#include <sstream>
#include <ostream>
#include <memory>
#include <string>
#include <map>
#include <functional>

#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

using namespace boost;
using namespace std;

struct Address
{
	string street, city;
	int suite;

	Address() {}

	Address(const string& s, const string& c, const int su) : street(s), city(c), suite(su) {}
	
	Address(const Address &other) 
		: street{ other.street }, city{ other.city }, suite{ other.suite }
	{}


	friend ostream& operator<<(ostream& os, const Address& address)
	{
		os << "street: " << address.street << " city: " << address.city << " "
			<< "suite: " << address.suite;

		return os;
	}

private:
	friend class serialization::access;

	template<class archive>
	void serialize(archive& ar, const unsigned version)
	{
		ar& street;
		ar& city;
		ar& suite;

	}
};

struct Contact
{
	string name;
	Address* address;

	Contact() {}

	Contact(const string& name, Address* address)
		:name(name), address(address) {}

	Contact(const Contact& other)
		:
		name(other.name), address(new Address{ *other.address })
	{}

	~Contact() { delete address; }

	friend ostream& operator<<(ostream& output, Contact& contact)
	{
		output << "name: " << contact.name << " address: " << *contact.address << endl;
		return output;
	}

private:
	friend class serialization::access;

	template<class archive>
	void serialize(archive& ar, const unsigned version)
	{
		ar& name;
		ar& address;
	}

};

//prototype factory
class EmployeeFactory
{
private:
	static unique_ptr<Contact> newEmployee(
		const string& name, 
		int suite, 
		const Contact& prototype)
	{
		auto result = make_unique<Contact>(prototype);
		result->name = name;
		result->address->suite = suite;
		return result;
	}

public:
	static unique_ptr<Contact> new_main_office_employee(
		const string& name,
		const int suite
	)
	{
		static Contact p{ "",new Address{"123 East Dr","London",0} };
		return newEmployee(name, suite, p);
	}
};

int main()
{
	auto clone = [](const Contact& c) {
		ostringstream oss;

		archive::text_oarchive oa(oss);
		oa << c;

		string s = oss.str();
		cout << s << endl;

		istringstream iss(s);
		archive::text_iarchive ia(iss);

		Contact result;
		ia >> result;

		return result;
	};

	auto john = EmployeeFactory::new_main_office_employee("John", 123);
	auto jane = clone(*john);

	jane.name = "jane";

	cout << *john << endl; 
	cout << jane << endl;
}
