#include "CityModel.h"

bool CityModel::compareByBeginning(Building b1, Building b2)
{
	return (b1.beginning > b2.beginning);
}

void CityModel::sortBuildings()
{
	std::sort(buildings->begin(), buildings->end(),compareByBeginning);
}

CityModel::CityModel()
{
	buildings = new std::vector<Building>;
}

CityModel::~CityModel()
{
	delete buildings;
}

void CityModel::addBuilding(int beginning, int end, int height)
{
	buildings->push_back(Building{ beginning,end,height });
}

void CityModel::getPanorama(std::vector<int>& heightChanges)
{
	heightChanges.push_back((*buildings)[0].beginning);
	int actualBuildingIdx = 0;
	for (int i = 1; i < buildings->size(); i++)
	{
		if((*buildings)[actualBuildingIdx].end)
	}
}
