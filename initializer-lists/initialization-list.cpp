/**
 *  Concept 2 : initialization list.
 */

#include <iostream>
#include <vector>

int main()
{
  std::vector<int> vectorA(1);
  std::cout << "vectorA size: " << vectorA.size()
            << " vectorA[0]: " << vectorA[0] << std::endl;

  std::vector<int> vectorB(1, 10);
  std::cout << "vectorB size: " << vectorB.size()
            << " vectorB[0]: " << vectorB[0] << std::endl;

  std::vector<int> vectorC{ 1, 10 };
  std::cout << "vectorC size: " << vectorC.size()
            << " vectorC[0]: " << vectorC[0] << std::endl;

  std::initializer_list<int> aList{ 1, 10 };
  std::vector<int> vectorD{ aList };
  // or std::vector<int> vectorD(aList);
  std::cout << "vectorD size: " << vectorD.size()
            << " vectorD[0]: " << vectorD[0] << std::endl;

  return 0;
}
