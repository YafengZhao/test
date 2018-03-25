/*
 * =====================================================================================
 *
 *       Filename:  decltype.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2018年03月24日 23时02分33秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  zhaoyafeng (), zhaoyafeng0615@163.com
 *   Organization:  GNU
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <cstring>


class Person
{
public:
	virtual ~Person() {}
};

class Employee : public Person
{
};


void testArrayRef(const int a[10])
{
	std::cout << sizeof a << std::endl;
}


// a reference to array
void testArrayRefV2(const int (&a)[10] )
{
	std::cout << sizeof a << std::endl;
}

template <class T>
void size(T &a)
{

	std::cout << sizeof a << std::endl;
}

int main(void)
{
	std::string str("hello");

	//	decltype(str) strtype = str;
	//	int i = 0;
	//	std::cout << typeid(i).name() << "::" <<  typeid(strtype).name() << std::endl;

	std::cout << typeid(str).name() << std::endl;
	Person person;
	Employee employee;
	Person* ptr = &employee;
	Person& ref = employee;
	// The string returned by typeid::name is implementation-defined
	std::cout << typeid(person).name() << std::endl;   // Person (statically known at compile-time)
	std::cout << typeid(employee).name() << std::endl; // Employee (statically known at compile-time)
	std::cout << typeid(ptr).name() << std::endl;      // Person* (statically known at compile-time)
	std::cout << typeid(*ptr).name() << std::endl;     // Employee (looked up dynamically at run-time
	//           because it is the dereference of a
	//           pointer to a polymorphic class)
	std::cout << typeid(ref).name() << std::endl;      // Employee (references can also be polymorphic)

	//   Person* p = nullptr;
	//   try
	//      {
	//       typeid(*p); // not undefined behavior; throws std::bad_typeid
	//      }
	//       catch (...)
	//      {
	//      }
	//
	//   Person& pRef = *p; // Undefined behavior: dereferencing null
	//   typeid(pRef);      // does not meet requirements to throw std::bad_typeid
	// because the expression for typeid is not the result
	// of applying the unary * operator


	const char *name = "hello";
	const char strname[] = "American";

	// 8::9::5::8 sizeof cantain the last '\0'
	std::cout << "-----" << sizeof name << "::" << sizeof strname << "::" << std::strlen(name) << "::" << std::strlen(strname) << std::endl;

	name = strname;

	// test const char * and const char [] if it is the same, especially as function parameter are the same 
	std::cout << name << "::" << std::is_same<decltype(name), decltype(strname)>::value<< std::endl;

	// pass array parameter as reference 
	//
	int a[10];
	testArrayRef(a);
	size(a); // template deduce T as int a[10], but what is  the function paremeter declaration??
	testArrayRefV2(a);
	return 0;
}
