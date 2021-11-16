#pragma once
#include <vector>
#include <algorithm>
class CityModel
{
private:
	struct Building
	{
		int beginning;
		int end;
		int height;
	};

	bool compareByBeginning(Building b1, Building b2);
	
	std::vector<Building>* buildings;
	void sortBuildings();

public:
	CityModel();
	~CityModel();
	void addBuilding(int beginning, int end, int height);
	void getPanorama(std::vector<int>& heightChanges);

};

