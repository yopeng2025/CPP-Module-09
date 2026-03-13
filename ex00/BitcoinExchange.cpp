#include "BitcoinExchange.hpp"
#include <iostream> 
#include <cstdio>   // sscanf()
#include <fstream>  // std::ifstream()
#include <cstring>
#include <map>
#include <iomanip> //setprecision()

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {*this = other;}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other)
        _data = other._data;
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}

bool    BitcoinExchange::isValidDate(const std::string & date) const 
{
    if (date.length() != 10 || date[4] != '-' || date[7] != '-')
    {
        std::cerr << "Error: bad input => " << date << std::endl;
        return false;
    }
    int y= 0, m = 0, d = 0;
    //String Scan Formatted：parse string into three integers and returns the amounts that are extracted
    if (sscanf(date.c_str(), "%d-%d-%d", &y, &m, &d) != 3)
    {
        std::cerr << "Error: bad input => " << date << std::endl;
        return false;
    }
    int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) //leap year
        days[2] = 29;
    if (y < 0 || m > 12 || m < 1 || d < 1 || d > days[m])
    {
        std::cerr << "Error: bad input => " << date << std::endl;
        return false;
    }
    return true;
}

bool    BitcoinExchange::isValidValue(const std::string& value, float& n) const
{
    char*   endptr;                          //char pointer
    n = std::strtof(value.c_str(), &endptr); //string -> float. endptr -> non-number (e.g. \0 or abc)

    if (*endptr != '\0' && !std::isspace(*endptr))
    {
        std::cerr << "Error: bad input => " << value << std::endl;
        return false;
    }
    if (n < 0)
    {
        std::cerr << "Error: not a positive number." << std::endl;
        return false;
    }
    if (n > 1000)
    {
        std::cerr << "Error: too large a number." << std::endl;
        return false;
    }
    return true;
}

void   BitcoinExchange::loadDatabase(const std::string& dbPath)
{
    std::ifstream file(dbPath.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: cannot open file" << std::endl;
        return ;
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
    {
        size_t sep = line.find(',');
        if (sep == std::string::npos)
        {
            std::cerr << "Error: bad input database => " << line << std::endl;
            continue;
        }
        std::string date = line.substr(0, sep);    //[[0],',')
        std::string rateStr = line.substr(sep + 1);//[','+1, '\0')
        if (!isValidDate(date))
            continue;
        
        char *endptr;
        float rate = std::strtof(rateStr.c_str(), &endptr);
        if (*endptr != '\0' && !std::isspace(*endptr))
        {
            std::cerr << "Error: bad input database => " << rateStr << std::endl;
            continue;
        }
        _data[date] = rate;
    }
    file.close();
}

void   BitcoinExchange::processInput(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: cannot open file" << std::endl;
        return ;
    }

    std::string line;
    std::getline(file, line); //get the first line "data | value"
    while (std::getline(file ,line)) // get the next line (real data e.g. 2009-01-01 | 11)
    {
        size_t  sep = line.find(" | "); // return index 10， pointing to " " before "|"
        if (sep == std::string::npos)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue ;
        }

        std::string date = line.substr(0, sep); //get sep(10) characters since index 0
        std::string valueStr = line.substr(sep + 3);//" | " + 3 => real value 11
        float   amount = 0.0f;
        if(!isValidDate(date) || !isValidValue(valueStr, amount))
            continue ;

        std::map<std::string, float>::const_iterator it = _data.lower_bound(date); 
        //lower_bound() return >=
        //begin() cannot be --; end() has nothing so need to be --
        //it->first = date; it->second = exchange_rate
        if (it != _data.begin() && (it == _data.end() || it->first != date)) 
            it--;
        if (it != _data.end() && it->first <= date)
            //stream precision：retain as many digits as possible until reach the upper limit (7).
            std::cout << date << " => " << amount << " = " << std::setprecision(7) << amount * it->second << std::endl;
        else
            std::cerr << "Error: Data not found => " << date << std::endl; //input data is earlier than the first data date
    }
}

void    BitcoinExchange::printDatabase() const
{
    std::map<std::string, float>::const_iterator it;
    for (it = _data.begin(); it != _data.end(); it++)
    {
        std::cout << it->first << "," << std::setprecision(7) << it->second << std::endl;
    }
}