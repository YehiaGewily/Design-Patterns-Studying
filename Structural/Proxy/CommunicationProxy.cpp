/*
 * Design Patterns - CommunicationProxy
 * Author: Yehya
 * Description: Implementation of the CommunicationProxy pattern in C++.
 */

//install cpprestsdk in Visual Studio
//Go to Tools >> NuGet Package Manager >> Manage Packages for Solution >> browse for cpprestsdk and install it into your project :D

#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <sstream>

#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;


using namespace std;


struct Pingable
{
	virtual wstring ping(const wstring& message) = 0;
};

struct Pong : Pingable
{
	wstring ping(const wstring& message) override
	{
		return message + L" pong";
	}
};

struct RmotePong : Pingable
{
	wstring ping(const wstring& message) override {
		wstring result;
		http_client client(U("http://localhost:9149/"));
		uri_builder builder(U("/api/pingpong"));
		builder.append(message);
		auto task = client.request(method::GET, builder.to_string()).then([=](http_response r) {
			return r.extract_string();
		}
		task.wait();
		return task.get();
	}
};

void tryIt(Pingable& p)
{
	wcout << p.ping(L"ping") << "\n";
}

int main()
{
	RmotePong p;
	for (int i = 0; i < 3; i++)
	{
		tryIt(p);
	}
}
