#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <string>

class   BitcoinExchange
{
    private:
        std::map<std::string, float>    _data;       //store data.csv
        bool                            isValidDate(const std::string& date) const;
        bool                            isValidValue(const std::string& value, float& n) const;
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        void                            loadDatabase(const std::string& dbPath);
        void                            processInput(const std::string& filename);
        void                            printDatabase() const;
};

#endif


/*
BitcoinExchange = vending machine：
    Public Interface (processInput): buttons
    Private Helpers (isValidDate, isValidValue): sensors inside the machine to check if the coins are valid
*/

/*
float: 7 decimal digits of precision 47115.93; occupies 4 bytes of memory
double: 15-17 decimal digits of precision;              8 bytes
*/