/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ubuntu
 *
 * Created on March 25, 2018, 12:03 AM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <typeinfo>
#include <cstring>
#include <memory>
#include <vector>
#include <tuple>
#include <set>

#include "sizeof.h"
#include "template.h"
using namespace std;

/*
 * 
 */

void funcToPointer()
{
    
    std::cout << "function to pointer " << std::endl;
}

void funcToRef()
{
    std::cout << "function to Ref" << std::endl;
}

template <class T, std::size_t N>
const std::size_t arraySize(T (&)[N])
{
    return N;
}    

class A {
public:
    A() {
    
        std::cout << "Call no parameter constructor ..." << std::endl;
    }
    A(int a, bool b){ 
    
        std::cout << "Call A constructor ..." << std::endl;
    }
    
    A(std::initializer_list<int> lb) {
    
        std::cout << "A initializer list constructor ..." << std::endl;
    }
};
template <class T>
void show(T &&arg)
{
    std::cout << arg << std::endl;
}

void printReference1 (const string& str)
{
    std::cout << str << std::endl;
}

void printReference2 (std::string && str)
{
    std::cout << str;
}

void TestDelete(int a) {
    std::cout << "Test delete ..." << std::endl;

}

void TestDelete( std::string &a) = delete;



void f(int n){
    
    std::cout << "Call function int ...";
}

void f(void *p) {
 
    std::cout << "Call function void * ..." << std::endl;
}

using Pfun = void (*)(int, std::string);

int main(int argc, char** argv) {

    std::string str;
    
    int iArray[100];
    std::cout << arraySize(iArray) << std::endl;
    
    char *strArray = "Hello";
  //  std::cout << arraySize(strArray) << std::endl; // not const char (&)[] array
    
    // type:: void (*)() && declaration void (*f1)(), f1 is the variable
    // function to pointer;
    void (*f1)()  = funcToPointer;
    
    (*f1)(); // call f1
    
    // type:: void (&)() && declaration void (&f1)(), f1 is the variable
    // function to reference
    void (&f2)() = funcToRef;
    (*f2)();
    
    // array to reference;
    
    
    int (&iRef)[100] = iArray;
    
    allTypesSize();
    
    // pointer to reference
    char *(&strRef) = strArray;
    std::cout << strRef << std::endl;
    
    std::string stdstr("std::string");
    printReference2("123");
    
    std::string &&strrr = "123";
    std::string && strrefref = "111";
    
    auto x(27);
    std::cout << "x type is " << typeid(x).name() << std::endl;

    auto x1 = {27};
    std::cout << "x1 type is " << typeid(x1).name() << std::endl;
    
   // std::cout << decltype(str).name() << std::endl;
    
    int &&t = 10;
    
    int mm = 0;
    std::cout << typeid(decltype(mm)).name() << std::endl;
    
    std::string sssstr{};

    A a{};
    A aa{10, 1, 100};

    A aaa({});
    A a4{{}};
    
    f(0);
    f(nullptr);
    //f(NULL);wrong
    
    Pfun *fp;
    
    tprint(t);
    
    std::string temp("hello");
    tprint(temp.begin(), temp.end());

    std::remove_reference<int>::type tt = t;
    
   std::tuple<int, std::string, float> infos;
   std::get<1>(infos);
   //auto arg = std::get<1>(infos);
    //tprint(arg);
   
   TestDelete(10);
   //TestDelete("233");
    return 0;
}

