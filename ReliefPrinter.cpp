#include "ReliefPrinter.h"

bool ReliefPrinter::printRelief(const std::vector<int>& relief, std::ostream& outputStream)
{
    outputStream << "( ";
    if (relief.size() % 2 == 0)
    {
        for (size_t i = 0; i < relief.size()-1; i++)
        {
            outputStream << relief[i] << ", ";
        }
        if (relief.size() >= 2)
        {
            outputStream << relief[relief.size() - 1];
        }
        outputStream << " )" << std::endl;

        return true;
    }
    return false;
}
