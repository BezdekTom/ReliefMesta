#pragma once
#include <vector>
#include <fstream>

class ReliefPrinter
{
public:
	/**
	 * Print relief in vector format into the given output stram
	 * 
	 * \param relief is the relief in the format given in assignement
	 * \param outputStream
	 * \return false if data in relief are not in right format (odd number of numbers), otherwise return true
	 */
	static bool printRelief(const std::vector<int>& relief, std::ostream& outputStream);
};

