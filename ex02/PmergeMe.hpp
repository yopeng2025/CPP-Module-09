#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>
#include <ctime>

template <typename Container>
class PmergeMe
{
private:
    typedef typename Container::value_type ValueType; // valueType == int in this case
    typedef typename Container::iterator Iterator;

    int Jacobsthal(int k);

    void insert(Container &main, Container &pend, ValueType odd,
                Container &left, Container &vec, bool is_odd, int order);

public:
    void sort(Container &vec);
};

#include "PmergeMe.tpp"

#endif

/*
Merge-Insertion Sort (Ford-Johnson Sort)
    1. Ford-Johnson algorithm employs the Jacobsthal sequence 
       to determine the optimal insertion order, 
       ensuring that the search space for each Binary Insertion remains as close to 
       a power of two as possible. 
    2. This scheduling minimizes the total number of comparisons, 
       allowing the algorithm to achieve information-theoretic efficiency in sorting.

    1. compair & swap in pairs [a1,b1][a2,b2][a3,b3]... (b >= a)

    2. bigger no.-> main chain   = b1 b2 b3 ...
       smaller no. -> pend chain = a1 a2 a3 ...

    3. jacobsthal sequence: decide which [i] in pend chain to insert in main
        interval size of each binary search is as close as possible to 2^k-1, 
        thus minimizing comparisons in the worst case
        e.g. main = b1 b2 b3
             size = 3 = 2 ^ k - 1 = 2 ^ 2 -1 
             k = 2
             k times comparison (in worst case)

             2 ^ k - 1 == balanced binary tree

    4. binary insertion(upper_bound()): put pend no. -> main no.
       
        J(n+1) - J(n) = 2
                        2
                        6
                        10
                        22
                        ...
        ≈ 2 ^ k - 1 
          optimal comparisons
*/

/*
Fibonacci Sequence: 
        F(n)​ = F(n−1) ​+ F(n−2)

​        0,1,1,2,3,5,8,13,21,34,55,89,144,…
        growth rate ≈ 1.6 (too slow)
        1. geometry and biological patterns
        2. models optimal, steady growth often found in nature 
           by summing the two previous terms.
        
Jacobsthal Sequence:
        J(k) ​= J(k−1) ​+ 2 * J(k−2)​ 
        closed-form equation: (2^n - (-1)^n) / 3

        0,1,1,3,5,11,21,43,85,171,341,683,1365,…
        growth rate ≈ 2 (close to 2^k)
        1. primarily used in computing and combinatorics 
           to analyze branching logic and pattern matching.
        2. faster, binary-driven expansion 
           by adding double the value of the term before the previous one。
*/

/*
Vector > Deque > List (memory layout)

CPU Cache:
    1. read in 64 bytes(16 ints) each time

Vector & Deque: random-access iterators

Vector： optimizes access speed through strong cache locality
    1. continuous memory
    2. faster iteration, thus better CPU cache usage
    
    1. insertion in the middle -> move the entire array
    2. resize = reallocate  

    small amount of numbers: > deque  cuz these numbers might already in cache
    huge amount of numbers : < deque  cuz need to copy/reallocation the entire array(too big!)

Deque: optimizes structural stability by avoiding large-scale memory movement
    1. segmented memory -> blocks
    2. fast insertion at front/back, without moving the entire array (allocate new blocks)
    3. stable when deal with large amount of numbers

    small amount of numbers: < vector cuz need to find numbers in different blocks; cache miss
    huge amount of numbers : > vector cuz can allocate new blocks to store inserted numbers
                                      only need to move certain blocks when inserting  
List: 
    1. every element is a node, randomly distributed memory (might use both cache & RAM)
    2. do not support ramdon access (previous node <- pointer -> next node)
    3. nodes are often not in cache



*/