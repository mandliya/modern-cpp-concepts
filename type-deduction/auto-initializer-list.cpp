/**
 *  Concept 3 Deducing object type.
 */

#include <iostream>
#include <typeinfo>

class ExampleClass{ };

int main() {

  auto var1{ 4.5 };
  std::cout << "Type of Variable: " << typeid(var1).name() << std::endl;

  auto var2{ ExampleClass{ } };
  std::cout << "Type of Variable: " << typeid(var2).name() << std::endl;

  return 0;
}
