/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "sizeof.h"

/*
 On major 32-bit platforms:

int is 32 bits
long is 32 bits as well
long long is 64 bits
On major 64-bit platforms:

int is 32 bits
long is either 32 or 64 bits
long long is 64 bits as well
Going by the standard:

int must be at least 16 bits
long must be at least 32 bits Win64 is 32-bit and Linux 64-Bit
long long must be at least 64 bits
Correct me if I'm wrong.

If you need a specific integer size for a particular application, rather than trusting the compiler to pick the size you want, #include <stdint.h> (or <cstdint>) so you can use these types:

int8_t and uint8_t
int16_t and uint16_t
int32_t and uint32_t
int64_t and uint64_t
 */

struct A_t {
    
    char a;
    int A;
};

class C_t {
    
    static int G;
    char a;
    int A;
    void show();
};

std::size_t allTypesSize()
{
    char *str = "hello";
    std::cout << "static string size::" <<  sizeof str << " Length:: " << std::strlen(str) << std::endl;
    
    char strArray[] = "hello";
    std::cout << "string array size::" <<  sizeof strArray << " Length:: " << std::strlen(strArray) << std::endl;
    
    int a = 0; int A[8];
    std::cout << "int size:: " << sizeof a << " int Array size:: " << sizeof A << std::endl;
    
    long l = 0;  long L[8];
    std::cout << "long size:: " << sizeof l << "long  Array size:: " << sizeof L << std::endl;
    
    long long ll = 0;  long long LL[8];
    std::cout << "long long size:: " << sizeof ll << " long long Array size:: " << sizeof LL << std::endl;
    
    float f = 0;  float F[8];
    std::cout << "float size:: " << sizeof f << "float  Array size:: " << sizeof F << std::endl;
    
        
    double d = 0;  double D[8];
    std::cout << "double size:: " << sizeof d << " double  Array size:: " << sizeof D << std::endl;
    
    C_t c;
    A_t aa;
    std::cout << "empty struct:: " << sizeof aa << " empty class:: " << sizeof c  << std::endl;;
    
}