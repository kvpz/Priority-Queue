/*
    fpq.cpp
    04/07/2013
    Chris Lacher

    functionality test of PiorityQueue < T , P >

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

typedef fsu::Pair        < int, fsu::String > Widget;
typedef fsu::LessThan    < Widget >           PredicateType;
// typedef fsu::GreaterThan < Widget >           PredicateType;

// unordered list with fsu::g_max_element 
typedef pq1::PriorityQueue < Widget , PredicateType > PriorityQueue;
const char * implementation = "List, g_max_element()";
// */

/* // sorted list with MOList::LowerBound
typedef pq2::PriorityQueue < Widget , PredicateType > PriorityQueue;
const char * implementation = "MOList, Insert()";
// */

/* // unordered deque with fsu::g_max_element and XC
typedef pq3::PriorityQueue < Widget , PredicateType > PriorityQueue;
const char * implementation = "Deque, g_max_element(), XC";
// */

/* // unordered deque with fsu::g_max_element and leapfrog copy
typedef pq4::PriorityQueue < Widget , PredicateType > PriorityQueue;
const char * implementation = "Deque, g_max_element(), Leapfrog";
// */

/* // sorted vector with MOVector::LowerBound
typedef pq5::PriorityQueue < Widget , PredicateType > PriorityQueue;
const char * implementation = "MOVector, Insert()";
// */

/* // partially ordered vector with heap algorithms
typedef pq6::PriorityQueue < Widget , PredicateType > PriorityQueue;
const char * implementation = "Vector, g_heap";
// */

void DisplayMenu();

void GetWidget(Widget& w, std::istream& is, bool BATCH )
{
  std::cout << "  enter   string: ";
  is >> w.second_;
  if (BATCH) std::cout << w.second_ << '\n';
  std::cout << "  enter priority: ";
  is >> w.first_;
  if (BATCH) std::cout << w.first_ << '\n';
}

void NullWidget(Widget& w)
{
  w.first_ = 0;
  w.second_ = "0";
}

void PutWidget(const Widget& w)
{
  std::cout << w.first_ << ':' << w.second_;
}

void PutWidgetData(const Widget& w)
{
  std::cout << w.second_;
}

int main(int argc, char* argv[])
{
  std::ifstream ifs;
  std::istream * inptr = &std::cin;
  bool BATCH = 0;
  if (argc > 1)
  {
    BATCH = 1;
    ifs.open(argv[1]);
    if (ifs.fail()) return 0;
    inptr = &ifs;
  }
  if (!BATCH) DisplayMenu();

  PredicateType p;
  PriorityQueue  Q(p);
  // PriorityQueue  Q;
  Widget w;
  char option;

  do
  {
    std::cout << "Enter [command] [string] [priority] ('M' for menu, 'Q' to quit)\n: ";
    *inptr >> option;
    if (BATCH) std::cout << option << '\n';
    switch (option)
    {
      case '+': case '1':  // void Push(T)
	GetWidget(w, *inptr, BATCH);
	Q.Push(w);
	break;

      case '-': case '2':  // void Pop()
	if (!Q.Empty())
        {
	  w = Q.Front();
	  Q.Pop();
	  std::cout << "Popped ";
	  PutWidget(w);
	  NullWidget(w);
	  std::cout << " from Q\n";
	}
	else
	{
	  std::cout << "Q is empty\n";
	}
	break;

      case 'f': case 'F':  // T Front()
	if (!Q.Empty())
        {
	  w = Q.Front();
	  std::cout << "Front of Q == ";
	  PutWidgetData(w);
	  std::cout << '\n';
	}
	else
	{
	  std::cout << "Q is empty\n";
	}
	break;

      case 'e': case 'E':  // int Empty()
	std::cout << "Q is ";
	if (!Q.Empty()) std::cout << "not ";
	std::cout << "empty\n";
	break;

      case 's': case 'S':  // unsigned int Size()
	std::cout << "Q size is " << Q.Size() << '\n';
	break;

      case 'c': case 'C':  // Clear()
	Q.Clear();
	std::cout << "Q has been cleared\n";
	break;

      case 'd': case 'D':  // display contents of priority queue
	std::cout << "Q contents:\n";
	Q.Dump(std::cout, '\n');
	break;

      case 'm': case 'M': // display menu
	DisplayMenu(); break;

      case 'x': case 'X':
	if (BATCH)
	{
	  ifs.close();
	  ifs.clear();
	  inptr = &std::cin ;
	  std::cout << "  ** switched to interactive mode **\n";
	}
	else
	{
	  std::cout << "  ** already in interactive mode **\n";
	}
	break;

      case 'q': case 'Q':
	option = 'q';
	if (BATCH)
	{
	  ifs.close();
	  ifs.clear();
	  inptr = &std::cin ;
	}
	break;
            
      default:
	std::cout << "** Unrecognized command -- please try again.\n";
    }
  }
  while (option != 'q');
  std::cout << "\nHave a nice day." << std::endl;
  return EXIT_SUCCESS;
}

void DisplayMenu()
{
  std::cout << '\n'
	    << "  PriorityQueue < Pair < int , String > , PredicateType > Q\n"
	    << "    Implementation: " << implementation << "\n\n"
	    << "  Push  (string, priority)  ......  + or 1\n"
	    << "  Pop   ()  ......................  - or 2\n"
	    << "  Front ()  ......................  F\n"
	    << "  Clear ()  ......................  C\n"
	    << "  Empty ()  ......................  E\n"
	    << "  Size  ()  ......................  S\n"
	    << "  Display entire queue  ..........  D\n"
	    << "  eXit batch mode  ...............  X\n"
	    << "  Quit program  ..................  Q\n"
	    << "  Display this menu  .............  M\n";
}
