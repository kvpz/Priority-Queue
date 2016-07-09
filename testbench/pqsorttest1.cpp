/*
    pqsorttesta.cpp
    04/08/2013
    Chris Lacher

    A sort testing PiorityQueue < T , P >

    Copyright 2013, R.C. Lacher
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

#include <pair.h>      // to make pairs <fsu::String, int>
#include <compare.h>   // generic lessthan and greaterthan predicates
#include <xstring.h>   // fsu::String
#include <xstring.cpp> // in lieu of makefile

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

  pq1::PriorityQueue < int , fsu::GreaterThan < int > > Q;
  // pq2::PriorityQueue < int , fsu::GreaterThan < int > > Q;
  // pq3::PriorityQueue < int , fsu::GreaterThan < int > > Q;
  // pq4::PriorityQueue < int , fsu::GreaterThan < int > > Q;
  // pq5::PriorityQueue < int , fsu::GreaterThan < int > > Q;
  // pq6::PriorityQueue < int , fsu::GreaterThan < int > > Q;

  int n;
  std::cout << "   Input:";
  while (ifs >> n)
  {
    std::cout << ' ' << n;
    Q.Push(n);
  }
  std::cout << '\n';
  ifs.close();

  std::cout << "Q.Dump(): ";
  Q.Dump(std::cout, ' ');
  std::cout << '\n';

  std::cout << "Q Output:";
  while (!Q.Empty())
  {
    std::cout << ' ' << Q.Front();
    Q.Pop();
  }
  std::cout << '\n';

  return 0;
}
