#include <fstream>
#include "CityModel.h"


void loadData(CityModel& cm)
{
	std::fstream file;
	file.open("testData.txt");
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
	loadData(cm);
	cm.getPanorama();

	return 0;
}
