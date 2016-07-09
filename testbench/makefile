# makefile for pq tests

home    = /home/courses/cop4530p/LIB
cpp     = $(home)/cpp
tcpp    = $(home)/tcpp
proj    = .

incpath = -I$(proj) -I$(cpp) -I$(tcpp)

CC      = clang++ -std=c++11 -Wall -Wextra

all: fpq1.x fpq2.x fpq3.x fpq4.x fpq5.x fpq6.x \
 pqsorttest1.x pqsorttest2.x pqsorttest3.x pqsorttest4.x pqsorttest5.x pqsorttest6.x \
 pqsorttest-all.x

fpq1.x: fpq1.cpp pq.h
	$(CC) $(incpath) -ofpq1.x fpq1.cpp

fpq2.x: fpq2.cpp pq.h
	$(CC) $(incpath) -ofpq2.x fpq2.cpp

fpq3.x: fpq3.cpp pq.h
	$(CC) $(incpath) -ofpq3.x fpq3.cpp

fpq4.x: fpq4.cpp pq.h
	$(CC) $(incpath) -ofpq4.x fpq4.cpp

fpq5.x: fpq5.cpp pq.h
	$(CC) $(incpath) -ofpq5.x fpq5.cpp

fpq6.x: fpq6.cpp pq.h
	$(CC) $(incpath) -ofpq6.x fpq6.cpp

pqsorttest1.x: pqsorttest1.cpp pq.h
	$(CC) $(incpath) -opqsorttest1.x pqsorttest1.cpp

pqsorttest2.x: pqsorttest2.cpp pq.h
	$(CC) $(incpath) -opqsorttest2.x pqsorttest2.cpp

pqsorttest3.x: pqsorttest3.cpp pq.h
	$(CC) $(incpath) -opqsorttest3.x pqsorttest3.cpp

pqsorttest4.x: pqsorttest4.cpp pq.h
	$(CC) $(incpath) -opqsorttest4.x pqsorttest4.cpp

pqsorttest5.x: pqsorttest5.cpp pq.h
	$(CC) $(incpath) -opqsorttest5.x pqsorttest5.cpp

pqsorttest6.x: pqsorttest6.cpp pq.h
	$(CC) $(incpath) -opqsorttest6.x pqsorttest6.cpp

pqsorttest-all.x: pqsorttest-all.cpp pq.h
	$(CC) $(incpath) -opqsorttest-all.x pqsorttest-all.cpp
