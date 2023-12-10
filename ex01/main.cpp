
#include "RPN.hpp"

int main(int ac, char **av)
{
    if (ac != 2) {
        std::cout << "Usage: " << av[0] << " \"inverted Polish expression\"" << std::endl;
        return 1;
    }

    try
    {
        RPN calculator;
        int result = calculator.calculate(av[1]);
        std::cout << result << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << '\n';
    }
    
    return 0;
}