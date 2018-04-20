/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   template.h
 * Author: ubuntu
 *
 * Created on March 27, 2018, 9:45 PM
 */

#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <stdio.h>
#include <type_traits>


template <class T>
void tprint(const T &d) 
{
    std::cout << d << std::endl;
}

template <class T> 
void tprint( T begin,  const T end)
{
  //  std::remove_const<T>::type b = begin;
    T &b = begin;
    for(; b != end; b++)
    {
          std::cout << *b << "----";
    }
    std::cout << "==============\n";
    
    std::cout << std::endl;
}


#endif /* TEMPLATE_H */

