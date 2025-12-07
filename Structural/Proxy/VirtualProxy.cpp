/*
 * Design Patterns - VirtualProxy
 * Author: Yehya
 * Description: Implementation of the VirtualProxy pattern in C++.
 */

#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <sstream>

using namespace std;

template<typename T>
struct Property
{
	T value;

	Property(T value)
	{
		*this = value;
	}


	operator T() {
		return value;
	}
	
	T operator=(T newValue)
	{
		cout << "Assginemnt!\n";
		return value = newValue;
	}
};
struct Creature
{
	Property<int> strength{ 10 };
	Property<int> agility{ 10 };

};

struct Image
{
	virtual void draw() = 0;
};

struct Bitmap :Image
{
	Bitmap(const string& filename)
	{
		cout << "Loading bitmap from " << filename << endl;

	}

	void draw() override {
		cout << "Drawing bitmap" << endl;
	}
};

struct LazyBitmap : Image
{
	LazyBitmap(const string& filename) :filename(filename) {
		
	}

	void draw() override
	{
		if (!bmp)
			bmp = new Bitmap(filename);
		bmp->draw();
	}

private:
	string filename;
	Bitmap* bmp{ nullptr };


};

int main()
{
	LazyBitmap bmp{ "pokemon.png" };
	bmp.draw(); //the file will be loaded only when someone calls the draw method
	
}
