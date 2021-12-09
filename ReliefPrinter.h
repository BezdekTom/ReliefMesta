#pragma once
#include <vector>
#include <fstream>

class ReliefPrinter
{
public:
	/**
	 * Prints relief in vector format into the given output stream
	 *
	 * \param relief is the relief in the format given in assignment
	 * \param outputStream
	 * \return false if data in relief are not in right format (odd number of numbers), otherwise returns true
	 */
	static bool printRelief(const std::vector<int>& relief, std::ostream& outputStream);
};
