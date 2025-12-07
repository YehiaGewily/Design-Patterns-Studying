/*
 * Design Patterns - BridgePimpl ShrinkWrapped
 * Author: Yehya
 * Description: Implementation of the BridgePimpl ShrinkWrapped pattern in C++.
 */

#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

template<typename T>
class Pimpl
{
	unique_ptr<T> impl;

public:
	Pimpl();
	~Pimpl();

	template<typename ...Args> 
	Pimpl(Args&& ...args);

	T* operator->();
	T* operator*();
};

template<typename T>
Pimpl<T>::Pimpl() :impl{ new T{} } {}

template<typename T>
Pimpl<T>::~Pimpl() {
	//you do not need to delete
	//because smart pointers gets destroyed by default
	//as soon as the execution exits the current scope
}

template<typename T>
template<typename ...Args>
Pimpl<T>::Pimpl(Args&& ...args):impl{new T{std::forward<Args>(args)...}}
{}

template<typename T>
T* Pimpl<T>::operator->() {
	return implt.get();
}

template<typename T>
T* Pimpl<T>::operator*() {
	return *imple.get();
}


class Foo
{
	class impl;
	Pimpl<impl> impl;
public:
	/*
	...
	*/
};


int main()
{

}
