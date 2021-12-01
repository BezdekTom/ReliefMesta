#include <fstream>
#include <string>

#include "CityModel.h"


void loadData(CityModel& cm, const std::string& fileName)
{
	std::fstream file;
	file.open(fileName);
	int begining, end, height = 0;

	while (file >> begining >> height >> end)
	{
		if (begining < end)
		{
			cm.addBuilding(begining, end, height);
		}
	}
	file.close();
}

int main()
{

	CityModel cm;
	cm.addBuilding(1, 5, 8);
	cm.addBuilding(2, 6, 8);
	//cm.addBuilding(3, 7, 8);
	cm.addBuilding(6, 7, 8);
	cm.addBuilding(6, 12, 8);
	cm.addBuilding(15, 20, 8);
	//cm.addBuilding(0, 9, 8);
	//loadData(cm, "testData.txt");
	std::vector<int> panorama;
	cm.createPanorama();
	cm.getPanorama(panorama);
	std::cout << "(";
	for (int n : panorama)
	{
		std::cout << n << " ";
	}
	std::cout << ")" << std::endl;

	cm.printPanorama();


	return 0;
}
