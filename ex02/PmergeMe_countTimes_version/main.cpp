#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <set>
#include <cstdlib>
#include <cctype>
#include <ctime>
#include <string>

bool isNumber(const std::string &s)
{
    if (s.empty()) return false;
    for (size_t i = 0; i < s.size(); i++)
        if (!std::isdigit(s[i]))
            return false;
    return true;
}

int main(int ac, char **av)
{
    if (ac < 2) {
        std::cerr << "Error\n";
        return 1;
    }

    std::vector<int> vec;
    std::deque<int> deq;
    std::set<int> check;

    for (int i = 1; i < ac; i++)
    {
        std::string s(av[i]);
        if (!isNumber(s)) {
            std::cerr << "Error\n";
            return 1;
        }
        int n = std::atoi(av[i]);
        if (check.count(n)) {
            std::cerr << "Error\n";
            return 1;
        }
        check.insert(n);
        vec.push_back(n);
        deq.push_back(n);
    }

    std::cout << "Before: ";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    clock_t start = clock();
    PmergeMe<std::vector<int> > sorterVec;
    sorterVec.sort(vec);
    clock_t end = clock();
    double vecTime = (double)(end - start) / CLOCKS_PER_SEC * 1000000;

    start = clock();
    PmergeMe<std::deque<int> > sorterDeq;
    sorterDeq.sort(deq);
    end = clock();
    double deqTime = (double)(end - start) / CLOCKS_PER_SEC * 1000000;

    std::cout << "After: ";
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;

    std::cout << "Time to process " << vec.size() << " elements with std::vector : "
              << vecTime << " us\n";
    std::cout << "Time to process " << deq.size() << " elements with std::deque  : "
              << deqTime << " us\n";

    std::cout << "Total comparisons (vector): " << sorterVec.comparison_count << std::endl;
    std::cout << "Total comparisons (deque) : " << sorterDeq.comparison_count << std::endl;
}