/**
 *  Concept 1: Variable Initialization
 *  Explaining narrowing conversion.
 *  NOTE Comments contain error code
 */

#include <iostream>

int main()
{
  int anInt{ 100 };
  //char aChar{ 512 }; ---> Error: Narrowing conversion.
  char aChar{ static_cast<char>(512) };
  double aDouble{ 1.0 };
  //float aFloat{ aDouble }; ---> Error: Narrowing conversion.
  float aFloat{ static_cast<float>(aDouble) };

  std::cout << anInt << " " << aChar << " "
            << aDouble << " " << aFloat << std::endl;
  return 0;
}
