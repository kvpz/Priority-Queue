/*
    pqsort.cpp
    04/08/2013
    Chris Lacher

    A sort using PiorityQueue < T , P >

    Copyright 2013, R.C. Lacher
*/

#include <iostream>
#include <fstream>
#include <compare.h>
#include <pq.h>

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cout << "Please enter one filename at the command line - try again\n";
    exit (EXIT_SUCCESS);
  }
  
  std::ifstream ifs;
  ifs.open(argv[1]);
  if (ifs.fail())
  {
    std::cout << "File \"" << argv[1] << "\" not found - try again\n";
    exit (EXIT_SUCCESS);
  }

  pq1::PriorityQueue < int , fsu::GreaterThan < int > > Q1;
  pq2::PriorityQueue < int , fsu::GreaterThan < int > > Q2;
  pq3::PriorityQueue < int , fsu::GreaterThan < int > > Q3;
  pq4::PriorityQueue < int , fsu::GreaterThan < int > > Q4;
  pq5::PriorityQueue < int , fsu::GreaterThan < int > > Q5;
  pq6::PriorityQueue < int , fsu::GreaterThan < int > > Q6;

  int n;
  std::cout << "    Input:";
  while (ifs >> n)
  {
    std::cout << ' ' << n;
    Q1.Push(n);
    Q2.Push(n);
    Q3.Push(n);
    Q4.Push(n);
    Q5.Push(n);
    Q6.Push(n);
  }
  std::cout << '\n';
  ifs.close();

  std::cout << "Q1.Dump(): ";
  Q1.Dump(std::cout, ' ');
  std::cout << '\n';

  std::cout << "Q3.Dump(): ";
  Q3.Dump(std::cout, ' ');
  std::cout << '\n';

  std::cout << "Q4.Dump(): ";
  Q4.Dump(std::cout, ' ');
  std::cout << '\n';

  std::cout << "Q2.Dump(): ";
  Q2.Dump(std::cout, ' ');
  std::cout << '\n';

  std::cout << "Q5.Dump(): ";
  Q5.Dump(std::cout, ' ');
  std::cout << '\n';

  std::cout << "Q6.Dump(): ";
  Q6.Dump(std::cout, ' ');
  std::cout << '\n';

  std::cout << "Q1 Output:";
  while (!Q1.Empty())
  {
    std::cout << ' ' << Q1.Front();
    Q1.Pop();
  }
  std::cout << '\n';

  std::cout << "Q2 Output:";
  while (!Q2.Empty())
  {
    std::cout << ' ' << Q2.Front();
    Q2.Pop();
  }
  std::cout << '\n';

  std::cout << "Q3 Output:";
  while (!Q3.Empty())
  {
    std::cout << ' ' << Q3.Front();
    Q3.Pop();
  }
  std::cout << '\n';

  std::cout << "Q4 Output:";
  while (!Q4.Empty())
  {
    std::cout << ' ' << Q4.Front();
    Q4.Pop();
  }
  std::cout << '\n';

  std::cout << "Q5 Output:";
  while (!Q5.Empty())
  {
    std::cout << ' ' << Q5.Front();
    Q5.Pop();
  }
  std::cout << '\n';

  std::cout << "Q6 Output:";
  while (!Q6.Empty())
  {
    std::cout << ' ' << Q6.Front();
    Q6.Pop();
  }
  std::cout << '\n';

  return 0;
}
