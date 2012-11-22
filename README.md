# graph-repl
==========

## Intro
 
graph-repl implements graph algorithms in C++. It's based on the algorithms in ['Algorithms in C++' , 3rd. edition, part 5, Graph Algorithms by Robert Sedgewick.](http://www.amazon.com/Algorithms-Part-Graph-3rd-Pt-5/dp/0201361183/ref=sr_1_6?s=books&ie=UTF8&qid=1353607231&sr=1-6&keywords=sedgewick)  

## Implementation

### Language

This implemention uses the C++11 currently part of the LLVM implemention shipping with Xcode.

### Compiler
Compiles on Xcode v 4.5.2 using llvm.

### Components and Implementation 

#### repl

This is supposed to provide an easy to use scripting interface to the algorithms. This has not been implemented.

#### graph

This contains an implemention of the graph algo's found in Sedgewick's book. These implementations rely heavily on C++ templates. 
I've tried to generalize the types of the vertices and edges. In Sedgewick's implementations the type of a vertex is int. 
I've also replaced the pointers-to-edges used later on in the book in the spanning tree, shortest path and network flow implenentations.

#### test

A set of unit tests for the algo's. It's implemented using recursive templates.

#### implementation notes

##### priority queues

Where possible I've tried to use c++ std library algorithms. The c++ std library provides a priority queue implementation. This implementation does not seem to provide  
the ability to update the queue dynamically. I've provided an other implemention using the c++ std libraries heap algorithms. However those don't support fixups of the heap as new 
elements are added. I've worked around this by rebuiling the heap any time a new element is added after an element has been popped. This does have a performance impact. 

