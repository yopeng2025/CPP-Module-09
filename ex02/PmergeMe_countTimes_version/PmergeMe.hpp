#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <cmath>
#include <algorithm> // std::swap, std::upper_bound, std::find
#include <cstddef>   // size_t

template <typename Container>
class PmergeMe {
public:
    typedef typename Container::iterator Iterator;
    typedef typename Container::value_type ValueType;

    PmergeMe() : comparison_count(0) {}

    void sort(Container &vec);
    void insert(Container &main, Container &pend, ValueType odd,
                Container &left, Container &vec, bool is_odd, int order);
    int Jacobsthal(int k);

    unsigned long long comparison_count;

private:
    // 自定义 round，C++98 没有 round()
    int round_double(double x) {
        return static_cast<int>(x + 0.5);
    }

    Iterator my_lower_bound(Iterator begin, Iterator end, ValueType val) {
    Iterator it;
    while (begin < end) {
        it = begin + (end - begin)/2;
        comparison_count++; // 每次比较计数
        if (*it < val)       // 注意这里是 <
            begin = it + 1;
        else
            end = it;
    }
    return begin;
}
};

#include "PmergeMe.tpp"

#endif
