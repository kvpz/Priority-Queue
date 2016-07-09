/* 
  pq.h
  Kevin Perez
  8/1/15

  Various implementations for PriorityQueue < T , P >
  organized by namespace as follows:

  nmsp  stbl container element order central algorithm      push     pop       front
  ----  ---- --------- ------------- -------------------    ----     ---       -----
  pq1   yes  List      unordered     fsu::g_max_element()   O(1)     O(n)      O(n)
  pq2   yes  MOList    sorted        MOList::Insert()       O(n)     O(1)      O(1)
  pq3   no   Deque     unordered     fsu::g_max_element()   AO(1)    O(n)      O(n)
  pq4   yes  Deque     unordered     fsu::g_max_element()   AO(1)    O(n)      O(n)
  pq5   yes  MOVector  sorted        MOVector::Insert()     O(n)     O(1)      O(1)
  pq6   no   Vector    heap          fsu::g_push/pop_heap() O(log n) O(log n)  O(1)

  The pq3 version just copies the last element over the element
  to be removed, whereas the pq4 version does a leapfrog copy. Note that the
  leapfrog copy version is stable, the 1-element copy version is not.

All of the pq namespaces are defined in this file.

Concept of Priority Queue (Lacher, 2015)
-------------------------
A priority queue stores elements of typename T with a priority determined by an
object of a predicate class P. The operations are syntactically queue-like but
have associative semantics (rather than positional semantics, as in an ordinary
queue). 

-Element type with priority
     typename T t
     predicate class P p
-Associative queue operations
     void Push(t)
     void Pop()
     T& Front()
-Associative property
     Priority value determined by p
     Push(t) inserts t (no position implied), increases size by 1
     Pop() removes element with highest priority value, decreases size by 1
     Front() returns element with highest priority value, no state change

    assumptions on type C
    ---------------------

    CPriorityQueue<C,P> assumes that C::value_type has overloads of
    the following operators and functions:

       insertion  (output) operator    <<  
       equality            operators   ==, !=
       assignment          operator    =
       constructor                     T()
       destructor                      ~T()
       order operators                 <, <=, >=, >

    A copy constructor for T is not used.

    Assumptions on type P
    ---------------------

    P is a "predicate class"; that is, P is assumed to have the operator
    "()" overloaded with the prototype:

      bool P::operator () (const T&, const T&) const;

    A function object p of type P is used for order comparison, where
    "p(a,b) == true" is taken to mean "a < b".

    (See the discussion of predicate objects in gheap.h.)

    The Push/Pop operations for priority queue call the generic heap
    algorithms push_heap(iter,iter,pred) and pop_heap(iter,iter,pred)
    found in gheap.h.

pq6
---
A heap is a partially ordered complete binary tree(POT) stored in a vector. Note that
the largest element( v[0] ) in a heap is the root of the binary tree representation.



The default destructor, copy constructor and assignment operator work for all
six PriorityQueue implementations because they don't contain pointers. 

*/

#include <genalg.h>    // fsu::g_max_element()
#include <gheap.h>     // fsu::g_push_heap()    ,  fsu::g_pop_heap()
#include <list.h>      // fsu::List<>     ,  fsu::List<>::Iterator
#include <vector.h>    // fsu::Vector<>   ,  fsu::Vector<>::Iterator
#include <deque.h>     // fsu::Deque<>    ,  fsu::Deque<>::Iterator
#include <olist.h>     // fsu::MOList<>   ,  fsu::MOList<>::Iterator
#include <ovector.h>   // fsu::MOVector<> ,  fsu::MOVector<>::Iterator

namespace pq1
{
  
 template <typename T, class P >
 class PriorityQueue
 {
    typedef typename fsu::List < T >             ContainerType;
    typedef T                                    ValueType;
    typedef P                                    PredicateType;

    // store elements in unsorted order in list
    // Push(t): PushBack(t)
    // Front(): use fsu::g_max_element() to locate largest, then return element
    // Pop()  : use fsu::g_max_element() to locate largest, then remove element

    PredicateType  p_;
    ContainerType  c_;

  public:
    PriorityQueue() : p_(), c_()
    {}

    explicit PriorityQueue(P p) : p_(p), c_()
    {}

    //O(1)
    void Push (const T& t)
    {
      c_.PushBack(t);
    }

    void Pop ()
    // O(n)
    {
      typedef typename ContainerType::Iterator IteratorType;
      IteratorType i = fsu::g_max_element(c_.Begin(), c_.End(), p_);
      c_.Remove(*i);
    }

    const T& Front () const
    //O (n)
    {
      typedef typename ContainerType::ConstIterator IteratorType;
      IteratorType i = fsu::g_max_element (c_.Begin(), c_.End(), p_);
      return *i;
    }

    void Clear ()
    {
      c_.Clear();
    }

    bool Empty () const
    {
      return c_.Empty();
    }

    size_t Size () const
    {
      return c_.Size();
    }

    const P& GetPredicate() const
    {
      return p_;
    }

    void Dump (std::ostream& os, char ofc = '\0') const
    {
      c_.Display(os,ofc);
    }
 };
} // namespace pq1

namespace pq2
{

  // Note: pq2 is multimodal in terms of the priority number
 template <typename T, class P >
 class PriorityQueue
 {
    
  typedef typename fsu::MOList < T , P >         ContainerType;
  typedef T                                      ValueType;
  typedef P                                      PredicateType;

  // store elements in increasing order in list
  // last element is largest
  // Push(t): use MOList::Insert (t)
  // Front(): return back element of list
  // Pop()  : remove last element of list

  PredicateType  p_;
  ContainerType  c_;

 public:
  PriorityQueue() : p_(), c_()
  {}

  explicit PriorityQueue(P p) : p_(p), c_()
  {}

  void Push (const T& t)
  // O(n)
  {
    c_.Insert(t);
  }

  void Pop ()
  // O(1)
  {
    c_.PopBack();
  }

  const T& Front () const
  // O(1)
  {
    return c_.Back();
  }

  void Clear ()
  {
    c_.Clear();
  }

  bool Empty () const
  {
    return c_.Empty();
  }

  size_t Size () const
  {
    return c_.Size();
  }

  const P& GetPredicate() const
  {
    return p_;
  }

  void Dump (std::ostream& os, char ofc = '\0') const
  {
    c_.Display(os,ofc);
  }
 };
} // namespace pq2

namespace pq3
{

 template <typename T, class P >
 class PriorityQueue
 {
  typedef typename fsu::Deque < T >              ContainerType;
  typedef T                                      ValueType;
  typedef P                                      PredicateType;

  // store elements in unsorted order in vector
  // Push(t): PushBack(t)
  // Front(): use fsu::g_max_element() to locate largest, then return element
  // Pop()  : use fsu::g_max_element() to locate largest, then "remove"
  //   "remove" can be done two ways:
  //     (1) copy last element to popped element, then Popback()
  //         Note that (1) is unstable but O(1)
  //         (1) suggested by Janice Murillo March 2004
  //     (2) "leapfrog" copy elements down one index, starting at popped
  // element, then PopBack()
  //         Note that (2) is stable and O(n)
  //     In either case, both Front() and Pop() are O(n)
  //     due to the call to g_max_element().
  // pq3 uses (1)
  // pq4 uses (2)

  PredicateType  p_;
  ContainerType  c_;

 public:
  PriorityQueue() : p_(), c_()
  {}

  explicit PriorityQueue(P p) : p_(p), c_()
  {}

  void Push (const T& t)
  // Amortized O(1)
  {
    c_.PushBack(t);
  }

  void Pop ()
  // O(n) 
  {
    typedef typename ContainerType::Iterator IteratorType;
    IteratorType i = fsu::g_max_element(c_.Begin(), c_.End(), p_);
    //Since unsorted order, switch largest element with last, then popback()
    if(*i != c_.Back())
    {
      fsu::Swap(*i, c_.Back());
    }
    c_.PopBack();
  }

  const T& Front () const
  // O(n)
  {
    typedef typename ContainerType::ConstIterator IteratorType;
    IteratorType i = fsu::g_max_element (c_.Begin(), c_.End(), p_);
    return *i;
  }

  void Clear ()
  {
    c_.Clear();
  }

  bool Empty () const
  {
    return c_.Empty();
  }

  size_t Size () const
  {
    return c_.Size();
  }

  const P& GetPredicate() const
  {
    return p_;
  }

  void Dump (std::ostream& os, char ofc = '\0') const
  {
    c_.Display(os,ofc);
  }

 };
} // namespace pq3

namespace pq4
{

 template <typename T, class P >
 class PriorityQueue
 {
    
  typedef typename fsu::Deque < T >              ContainerType;
  typedef T                                      ValueType;
  typedef P                                      PredicateType;

  // store elements in unsorted order in vector
  // Push(t): PushBack(t)
  // Front(): use fsu::g_max_element() to locate largest, then return element
  // Pop()  : use fsu::g_max_element() to locate largest, then "remove"
  //   "remove" can be done two ways:
  //     (1) copy last element to popped element, then Popback()
  //         Note that (1) is unstable but O(1)
  //         (1) suggested by Janice Murillo March 2004
  //     (2) "leapfrog" copy elements down one index, starting at popped
  // element, then PopBack()
  //         Note that (2) is stable and O(n)
  //     In either case, both Front() and Pop() are O(n)
  //     due to the call to g_max_element().
  // pq3 uses (1)
  // pq4 uses (2)

  PredicateType  p_;
  ContainerType  c_;

 public:
  PriorityQueue() : p_(), c_()
  {}

  explicit PriorityQueue(P p) : p_(p), c_()
  {}

  void Push (const T& t)
  {
    c_.PushBack(t);
  }

  void Pop ()
  // O(n) implemented using leapfrog method
  {
    typedef typename ContainerType::Iterator IteratorType;
    IteratorType i = fsu::g_max_element(c_.Begin(), c_.End(), p_);
    while(*i != c_.Back())
    {
      fsu::Swap(*i, *(++i));
    }
    c_.PopBack();
  }

  const T& Front () const
  {
    typedef typename ContainerType::ConstIterator IteratorType;
    IteratorType i = fsu::g_max_element (c_.Begin(), c_.End(), p_);
    return *i;
  }

  void Clear ()
  {
    c_.Clear();
  }

  bool Empty () const
  {
    return c_.Empty();
  }

  size_t Size () const
  {
    return c_.Size();
  }

  const P& GetPredicate() const
  {
    return p_;
  }

  void Dump (std::ostream& os, char ofc = '\0') const
  {
    c_.Display(os,ofc);
  }
 };
} // namespace pq4

namespace pq5
{

 template <typename T, class P >
 class PriorityQueue
 {
    
  typedef typename fsu::MOVector < T , P >       ContainerType;
  typedef T                                      ValueType;
  typedef P                                      PredicateType;

  // store elements in increasing order in vector
  // last element is largest
  // Push(t): use MOVector::Insert(t)
  // Front(): return back element of vector
  // Pop()  : remove element from vector

  PredicateType  p_;
  ContainerType  c_;

public:
  PriorityQueue() : p_(), c_()
  {}

  explicit PriorityQueue(P p) : p_(p), c_()
  {}

  void Push (const T& t)
  {
    c_.Insert(t);
  }

  void Pop ()
  {
    c_.PopBack();
  }

  const T& Front () const
  {
    return c_.Back();
  }

  void Clear ()
  {
    c_.Clear();
  }

  bool Empty () const
  {
    return c_.Empty();
  }

  size_t Size () const
  {
    return c_.Size();
  }

  const P& GetPredicate() const
  {
    return p_;
  }

  void Dump (std::ostream& os, char ofc = '\0') const
  {
    c_.Display(os,ofc);
  }
 };
} // namespace pq5

namespace pq6
{
 template <typename T, class P >
 class PriorityQueue
 {
    
  typedef typename fsu::Vector < T >               ContainerType;
  typedef T                                        ValueType;
  typedef P                                        PredicateType;

  // store elements in partial order using heap algorithms
  // first element(root) is largest
  // Push(t): c_.PushBack(t) followed by g_push_heap()
  // Front(): c_.Front()  ( v[0] )
  // Pop()  : g_pop_heap() followed by c_.PopBack()

  PredicateType  p_;
  ContainerType  c_;

 public:
  PriorityQueue() : p_(), c_()
  {}

  explicit PriorityQueue(P p) : p_(p), c_()
  {}

  void Push(const T& t)
  /*
    Description of Push Heap Algorithm (Lacher, 2015)
    Action                 Vector Pseudocode     Comment
    ------                 -----------------     -------
[1] Add data at next leaf  v.push_back(t);       size increased by 1
[2] Repair upward          c = size - 1          v[c] is the new leaf added above
[3] (Repeat)               do {
    locate parent            p = (c - 1)/ 2;     v[p] = parent of v[c]
    if POT not satisfied     if(v[c] > v[p])     parent/child in wrong order 
      swap                     XC(v[c],v[p]);    exchange values between parent, child
                               c = p;            reset child
    else                     else
      stop                     finished = true;  POT property is restored
    Until POT               } until finished;    nothing left to do

[1] is an O(1) operation
[2], [3] is O(log size)      
   */
  
  {
    c_.PushBack(t);
    g_push_heap(c_.Begin(), c_.End(), p_);
    
  }

  void Pop()
  /*
    Action                              Vector Pseudocode       Comment
    ------                              -----------------       -------
[1] Copy last leaf to root              v[0] = v[size - 1];     new root value
    (Alternative) XC last leaf and root  XC(v[0],v[size - 1]);  new root value,
    old root value saved
[2] Remove last leaf                    v.pop_back();           size is reduced by 1
    (Alternative) decrement size        --size;                 range is reduced by 1
[3] Repair downward                     p = 0;                  initialize p = root
    Repeat                              do {
    Identify children                     l = 2*p + 1;          v[l] = left child of v[p]
                                          r = l + 1;            v[r] = right child of v[p]
    Find larger child                     if (v[l] > v[r])
                                            c = l;              v[c = l] is the larger child
                                          else
                                            c = r;              v[c = r] is the larger child
    if POT not satisfied                  if (v[c] > v[p])      parent/child in wrong order
    swap                                    XC(v[c],v[p]);      exchange values between parent, child
                                            p = c;              and reset parent
      else                                 else
    stop                                    finished = true;    POT PROPERTY is restored
    Until POT                            } until finished;      nothing left to do

[1], [2] are O(1)
[3] is O(log size)
   */
  {
    g_pop_heap(c_.Begin(), c_.End(), p_);
    c_.PopBack();
  }

  const T& Front () const
  {
    typedef typename ContainerType::ConstIterator IteratorType;
    IteratorType i = fsu::g_max_element (c_.Begin(), c_.End(), p_);
    return *i;
  }

  void Clear ()
  {
    c_.Clear();
  }

  bool Empty () const
  {
    return c_.Empty();
  }

  size_t Size () const
  {
    return c_.Size();
  }

  const P& GetPredicate() const
  {
    return p_;
  }

  void Dump (std::ostream& os, char ofc = '\0') const
  {
    c_.Display(os,ofc);
  }
 };
} // namespace pq6
