#include "RPN.hpp"
#include <iostream>
#include <exception>
#include <ctype.h> //isdigit()

RPN::RPN() {}

RPN::RPN(const RPN& other): _stack(other._stack) {}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
        _stack = other._stack;
    return *this;
}

RPN::~RPN() {}

void RPN::ApplyOperator(char op)
{
    if (_stack.size() < 2)
        throw ErrorException();
    int n2 = _stack.top();
    _stack.pop();
    int n1 = _stack.top();
    _stack.pop();
    
    if (op == '+')
        _stack.push(n1 + n2);
    else if (op == '-')
        _stack.push(n1 - n2);
    else if (op == '*')
        _stack.push(n1 * n2);
    else if (op == '/') 
    {
        if (n2 == 0)
            throw ErrorException();
        else
            _stack.push(n1 / n2);
    }
}

int RPN::calculate(const std::string& expression)
{
    while (!_stack.empty())  //bool: check if stack is empty; clear stack from previous run
        _stack.pop();
    for (size_t i = 0; i < expression.size(); i++)
    {
        char c = expression[i];
        {
            if(c == ' ') continue;
            else if (isdigit(c))
                _stack.push(c - '0');
            else if (c == '+' || c == '-' || c == '*' || c == '/')
                ApplyOperator(c);
            else
                throw ErrorException();
        }
    }
    if (_stack.size() != 1)
        throw ErrorException();
    return _stack.top();
}

 const char* RPN::ErrorException::what() const throw() {return "Error";}
