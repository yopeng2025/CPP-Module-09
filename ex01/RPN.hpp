#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <exception>
#include <list>
class RPN
{
    private:
        std::stack<int, std::list<int> >  _stack; //LIFO
        void              ApplyOperator(char op);
    public:
        RPN();
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);
        ~RPN(); 

        class ErrorException: public std::exception
        {
            public:
                const char* what() const throw();
        };
        int   calculate(const std::string& expression); //&: avoid unnecessary memory allocation
};

#endif