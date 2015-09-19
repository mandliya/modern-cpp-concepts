/**
 *  Concept 3 : type deduction.
 *  Use of auto and typeid demonstrated.
 */

#include <iostream>

int main()
{
  auto variable = 5.5;
  std::cout << "Type of Variable: " << typeid(variable).name() << std::endl;
  return 0;
}
