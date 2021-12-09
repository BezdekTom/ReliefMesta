#include "BuildingsLoader.h"

bool BuildingsLoader::loadBuildingsFromFile(ReliefCreator& reliefCreater, const std::string& inputFileName)
{
	try
	{
		std::ifstream file(inputFileName);
		int begin = 0;
		int end = 0;
		int height = 0;

		while (file >> begin >> height >> end)
		{
			if ((begin < end) && (height > 0))
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
		std::cerr << "Problem with BuildingsLoader, because: "<< ex.what() << "!\n";
		return false;
	}
}
