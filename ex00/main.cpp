#include "BitcoinExchange.hpp"
#include <iostream>


int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cout << "Usage: ./btc <filename>" << std::endl;
        return 1;
    }
    BitcoinExchange btc;
    btc.loadDatabase("data.csv");
    // btc.printDatabase();
    btc.processInput(argv[1]);
    return 0;
}