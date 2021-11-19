#include <algorithm>
#include <climits>
#include "CityModel.h"

CityModel::CityModel()
{
}

CityModel::~CityModel()
{
}

void CityModel::addBuilding(int beginning, int end, int height)
{
	loadedBuildings.push_back(Building{ beginning, end, height });
}

std::vector<int> CityModel::getPanorama()
{
	std::list<Building> panoramaBuildings;
	createPanorama(panoramaBuildings);
	std::vector<int> panorama;

	auto iterator = panoramaBuildings.begin();
	int lastEnd = INT_MAX;

	for (iterator; iterator != panoramaBuildings.end(); ++iterator)
	{
		if (lastEnd < iterator->beginning)
		{
			panorama.push_back(lastEnd);
			panorama.push_back(0);
		}
		panorama.push_back(iterator->beginning);
		panorama.push_back(iterator->height);
		lastEnd = iterator->end;
	}
	if (lastEnd < INT_MAX)
	{
		panorama.push_back(lastEnd);
		panorama.push_back(0);
	}
	return panorama;
}

void CityModel::printPanorama()
{
	std::list<Building> panoramaBuildings;
	createPanorama(panoramaBuildings);

	std::cout << "(";

	auto iterator = panoramaBuildings.begin();
	int lastEnd = INT_MAX;

	for (iterator; iterator != panoramaBuildings.end(); ++iterator)
	{
		if (lastEnd < iterator->beginning)
		{
			std::cout << lastEnd;
			std::cout << ", 0, ";
		}
		std::cout<< iterator->beginning << ", ";
		std::cout<< iterator->height << ", ";
		lastEnd = iterator->end;
	}
	if (lastEnd < INT_MAX)
	{
		std::cout << lastEnd;
		std::cout << ", 0";
	}
	std::cout << ")" << std::endl;
}


bool CityModel::buildingComparator(const Building& b1, const Building& b2)
{
	if(b1.height > b2.height)
	{
		return true;
	}
	else if (b1.height == b2.height)
	{
		if ((b1.end - b1.beginning) > (b2.end - b2.beginning))
		{
			return true;
		}
		else if ((b1.end - b1.beginning) == (b2.end - b2.beginning))
		{
			return(b1.beginning > b2.beginning);
		}
	}
	return false;
}

void CityModel::createPanorama(std::list<Building>& panoramaBuildings)
{
	std::sort(loadedBuildings.begin(), loadedBuildings.end());
	for (Building& addingBuilding : loadedBuildings)
	{
	label:
		auto buildingIterator = panoramaBuildings.begin();
		for (buildingIterator; buildingIterator != panoramaBuildings.end(); ++buildingIterator)
		{
			switch (addingBuilding.intersects(*buildingIterator))
			{
			case Overlaping::newInfrontOld:
				panoramaBuildings.insert(buildingIterator, addingBuilding);
				goto endloop;
			case Overlaping::newBehindOld:
				break;
			case Overlaping::newInsideOld:
				goto endloop;
			case Overlaping::oldInsideNew:
				if (addingBuilding.height == buildingIterator->height)
				{
					buildingIterator = panoramaBuildings.erase(buildingIterator);
					if (buildingIterator == panoramaBuildings.end())
					{
						goto endloop;
					}
					break;
				}
				else
				{
					panoramaBuildings.insert(buildingIterator, Building{ addingBuilding.beginning, buildingIterator->beginning, addingBuilding.height });
					addingBuilding.beginning = buildingIterator->end;
					break;
				}

			case Overlaping::newInAndOnRightOfOld:
				if (addingBuilding.height == buildingIterator->height)
				{
					addingBuilding.beginning = buildingIterator->beginning;
					buildingIterator = panoramaBuildings.erase(buildingIterator);
					if (buildingIterator == panoramaBuildings.end())
					{
						goto endloop;
					}
					break;
				}
				else
				{
					addingBuilding.beginning = buildingIterator->end;
					break;
				}
			case Overlaping::newInAndOnLeftOfOld:
				if (addingBuilding.height == buildingIterator->height)
				{
					buildingIterator->beginning = addingBuilding.beginning;
				}
				else
				{
					panoramaBuildings.insert(buildingIterator, Building{ addingBuilding.beginning, buildingIterator->beginning, addingBuilding.height });
				}
				goto endloop;
			default:
				break;
			}
		}
		panoramaBuildings.insert(buildingIterator, addingBuilding);
	endloop:
		std::cout << "";
	}
}


