/**
 *  Concept 3 : Deducing type of the object.
 *  Using auto with function.
 */


#include <iostream>

auto doSomething( double parameter )
{
  return parameter;
}

template <typename T>
auto doSomethingAgain( T parameter )
{
  return parameter;
}


template <typename T>
auto doSomethingAgainAgain( T parameter )->decltype(parameter)
{
  return parameter;
}


int main()
{
  std::cout << "Type of Variable: " << typeid(doSomething(1.5)).name() << std::endl;
  std::cout << "Type of Variable: " << typeid(doSomethingAgain(1)).name() << std::endl;
  std::cout << "Type of Variable: " << typeid(doSomethingAgainAgain("Hello")).name() << std::endl;
  return 0;
}
