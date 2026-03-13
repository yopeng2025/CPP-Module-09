#ifndef PMERGEME_TPP
#define PMERGEME_TPP

//pow() resturns double
//round() quit 4 get 5 四舍五入
//insert(pos, [begin, end) ) 
template <typename Container>
int PmergeMe<Container>::Jacobsthal(int k)
{
    return round((pow(2, k + 1) + pow(-1, k)) / 3);
}



template <typename Container>
void PmergeMe<Container>::insert(Container &main, Container &pend, ValueType odd,
Container &left, Container &vec, bool is_odd, int order)
{
    Iterator end;

    if (pend.size() == 1)
    {
        end = std::upper_bound(main.begin(), main.end(), *pend.begin());
        main.insert(end, *pend.begin());
    }
    else if (pend.size() > 1)
    {
        size_t jc = 3;
        size_t count = 0;
        size_t idx;
        size_t decrease;

        while (!pend.empty())
        {
            //how many pend elems to insert
            //these no. need the same "interval size" / the first J(K) numbers in main[] 
            idx = Jacobsthal(jc) - Jacobsthal(jc - 1); 

            if (idx > pend.size())
                idx = pend.size();

            decrease = 0;

            while (idx > 0)
            {
                end = main.begin();

                //insert pend[] only need to search J(K)s of main[]
                //decrease: need to --minus the newly inserted numbers
                if (Jacobsthal(jc + count) - decrease <= main.size())
                    end = main.begin() + Jacobsthal(jc + count) - decrease;
                else
                    end = main.end();

                end = std::upper_bound(main.begin(), end,
                        *(pend.begin() + idx - 1));

                main.insert(end, *(pend.begin() + idx - 1));//insert(before position, value)
                pend.erase(pend.begin() + idx - 1);

                idx--;
                decrease++;
                count++;
            }
            jc++;
        }
    }

    Container rebuilder;

    if (is_odd)
    {
        end = std::upper_bound(main.begin(), main.end(), odd);
        main.insert(end, odd);
    }

    for (Iterator i = main.begin(); i != main.end(); i++)
    {
        Iterator it = std::find(vec.begin(), vec.end(), *i);
        rebuilder.insert(rebuilder.end(), it - (order - 1), it + 1);
    }

    rebuilder.insert(rebuilder.end(), left.begin(), left.end());

    vec = rebuilder;
}




template <typename Container>
void PmergeMe<Container>::sort(Container &vec)
{
    static int order = 1;

    int unit_size = vec.size() / order;

    if (unit_size < 2)
        return;

    bool is_odd = unit_size % 2 == 1;

    //only compare even pairs
    Iterator start = vec.begin();
    Iterator end = vec.begin() + ((order * unit_size) - (is_odd * order));

    for (Iterator it = start; it < end; it += (order * 2))
    {
        if (*(it + (order - 1)) > *(it + ((order * 2) - 1)))
        {
            for (int i = 0; i < order; i++)
                std::swap(*(it + i), *(it + i + order));
        }
    }

    order *= 2;

    sort(vec);

    order /= 2;

    Container main;
    Container pend;
    ValueType odd = 0;
    Container left;

    main.push_back(*(start + order - 1));
    main.push_back(*(start + order * 2 - 1));

    for (Iterator it = start + order * 2; it < end; it += order)
    {
        pend.push_back(*(it + order - 1));
        it += order;
        main.push_back(*(it + order - 1));
    }

    if (is_odd)
        odd = *(end + order - 1);

    left.insert(left.end(), end + (order * is_odd), vec.end());

    if (is_odd || !pend.empty())
        insert(main, pend, odd, left, vec, is_odd, order);
}

#endif
