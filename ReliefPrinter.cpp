#include "ReliefPrinter.h"

bool ReliefPrinter::printRelief(const std::vector<int>& relief, std::ostream& outputStream)
{
    if (relief.size() % 2 == 0)
    {
        outputStream << "( ";
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
    return false;/*wrong format of relief, odd number of elements, number of elements has to be even */
}
