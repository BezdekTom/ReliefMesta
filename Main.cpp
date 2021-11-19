#include <fstream>
#include <string>
#include "CityModel.h"


void loadData(CityModel& cm, const std::string& fileName)
{
	std::fstream file;
	file.open(fileName);
	int begining, end, height = 0;

	while (file >> begining >> height>> end)
	{
		cm.addBuilding(begining, end, height);
	}
	file.close();
}

int main()
{
	
	CityModel cm;
	//cm.addBuilding(1, 5, 6);
	//cm.addBuilding(2, 4, 8);
	loadData(cm, "testData.txt");
	cm.printTreePanorama();

	return 0;
}
