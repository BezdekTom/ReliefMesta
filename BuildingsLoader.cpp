#include "BuildingsLoader.h"

bool BuildingsLoader::loadBuildingsFromFile(ReliefCreater& reliefCreater, const std::string& inputFileName)
{
	try
	{
		std::ifstream file;
		file.open(inputFileName);
		int begin, end, height = 0;

		while (file >> begin >> height >> end)
		{
			if (begin < end)
			{
				if (reliefCreater.addBuilding(begin, height, end) == false)
				{
					file.close();
					return false;
				}
			}
		}
		file.close();
		return true;
	}
	catch (const std::exception& ex)
	{
		std::cout << "Problem with BuildingsLoader, because: "<< ex.what() << "!\n";
		return false;
	}
}
