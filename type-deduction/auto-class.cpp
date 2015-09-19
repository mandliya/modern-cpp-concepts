/**
 * Concept 3 : Deduction of type.
 * Demonstration of auto with user created object
 */

#include <iostream>
#include <typeinfo>

class ExampleClass { };

int main()
{
  auto var = ExampleClass();
  std::cout << "Type of Variable: " << typeid(var).name() << std::endl;
  return 0;
}
