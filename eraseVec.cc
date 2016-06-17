// erasing from vector
#include <iostream>
#include <vector>

int main()
{
  std::vector<int> fullVec;
  for (int i=1; i<=100; i++) fullVec.push_back(i);
  std::cout << "5 % of fullVec.size() = " << 0.05*fullVec.size() << std::endl;  
  int removeElements = 0.05*fullVec.size();
  int presentElements = 0.95*fullVec.size();

  fullVec.erase (fullVec.begin(), fullVec.end()-presentElements);

  std::cout << "reduced vec size() = " << fullVec.size() << endl;
  for (unsigned int i=0; i<fullVec.size(); i++)
  {
    std::cout << "fullVec.at(i) = " << fullVec.at(i) << endl;
  }
  return 0;
}

int method_two()
{  
  std::vector<int> myvector;
  int sum (0);
  myvector.push_back (100);
  myvector.push_back (200);
  myvector.push_back (300);

  while (!myvector.empty())
  {
    sum+=myvector.back();
    myvector.pop_back();
  }

  std::cout << "The elements of myvector add up to " << sum << '\n';

  return 0;
}

bool sortByValueInDescendingOrder(int a, int b)
{
  return (a > b);
}

int method_three()
{
  std::vector<int> myvector;
  for (int i=1; i<=100; i++) myvector.push_back(i);

  int removeElements = 0.05*myvector.size();
  std::sort(myvector.begin(), myvector.end(), sortByValueInDescendingOrder);

  for(int i=0; i<removeElements; i++) 
  {
    myvector.pop_back();
  }
  std::cout << "myvector.size() = " << myvector.size() << std::endl;
  for (unsigned int i=0; i<myvector.size(); i++) std::cout << "myvector.at(i) = " << myvector.at(i) << endl;
  
  return 0;
}

bool sortByValueInAscendingOrder(int a, int b) 
{
  return (a < b);
}
