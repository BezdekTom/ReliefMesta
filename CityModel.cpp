#include "CityModel.h"

CityModel::CityModel()
{
}

CityModel::~CityModel()
{
}

void CityModel::addBuilding(int beginning, int end, int height)
{
	Building addingBuilding = Building{ beginning,end,height };
	auto buildingIterator = buildings.begin();

	for (buildingIterator; buildingIterator != buildings.end(); ++buildingIterator)
	{
		switch (addingBuilding.intersects(*buildingIterator))
		{
		case -1:
			buildings.insert(buildingIterator, addingBuilding);
			return;
		case 0:
			break;
		case 1:	//add.b , aB.b , add.e, aB.e
			case1(addingBuilding, buildingIterator);
			return;
		case 2:	//add.b, aB.b, add.e=aB.e
			case2(addingBuilding, buildingIterator);
			return;
		case 3:	//add.b, aB.b , aB.e , add.e
			if (!case3(addingBuilding, buildingIterator))
				return;
			break;
		case 4:	//add.b=aB.b , add.e, aB.e
			case4(addingBuilding, buildingIterator);
			return;
		case 5:	//add.b=aB.b, add.e=aB.e
			case5(addingBuilding, buildingIterator);
			return;
		case 6:	//add.b=aB.b , aB.e , add.e
			case6(addingBuilding, buildingIterator);
			break;
		case 7:	//aB.b, add.b, add.e, aB.e
			case7(addingBuilding, buildingIterator);
			return;
		case 8:	//aB.b, add.b, add.e=aB.e
			case8(addingBuilding, buildingIterator);
			return;
		case 9:	//aB.b, add.b, aB.e , add.e
			case9(addingBuilding, buildingIterator);
			break;
		default:
			break;
		}
	}

	buildings.push_back(addingBuilding);
}

void CityModel::getPanorama()
{
	auto iterator = buildings.begin();
	for (iterator; iterator != buildings.end(); ++iterator)
	{
		std::cout << iterator->beginning << std::endl;
		std::cout << iterator->height << std::endl;
	}
	
}


void CityModel::case1(Building& addingBuilding, std::list<Building>::iterator& buildingIterator) //correct
{
	if (addingBuilding.height > buildingIterator->height)
	{
		buildingIterator->beginning = addingBuilding.end;
		buildings.insert(buildingIterator, addingBuilding);
	}
	else if (addingBuilding.height == buildingIterator->height)
	{
		buildingIterator->beginning = addingBuilding.beginning;
	}
	else
	{
		addingBuilding.end = buildingIterator->beginning;
		buildings.insert(buildingIterator, addingBuilding);
	}
}

void CityModel::case2(Building& addingBuilding, std::list<Building>::iterator& buildingIterator)	//correct
{
	if (addingBuilding.height > buildingIterator->height)
	{
		buildingIterator->height = addingBuilding.height;
		buildingIterator->beginning = addingBuilding.beginning;
	}
	else if (addingBuilding.height == buildingIterator->height)
	{
		buildingIterator->beginning = addingBuilding.beginning;
	}
	else
	{
		addingBuilding.end = buildingIterator->beginning;
		buildings.insert(buildingIterator, addingBuilding);
	}
}

bool CityModel::case3(Building& addingBuilding, std::list<Building>::iterator& buildingIterator)
{
	if (addingBuilding.height < buildingIterator->height)
	{
		buildings.insert(buildingIterator, Building{ addingBuilding.beginning, buildingIterator->beginning, addingBuilding.height });
		addingBuilding.beginning = buildingIterator->end;
	}
	else if (addingBuilding.height >= buildingIterator->height)
	{
		auto next = buildingIterator;
		next++;
		if (next == buildings.end()--)
		{
			buildingIterator->beginning = addingBuilding.beginning;
			buildingIterator->end = addingBuilding.end;
			buildingIterator->height = addingBuilding.height;
			return false;
		}
		buildingIterator = buildings.erase(buildingIterator);
		return true;
	}
}

void CityModel::case4(Building& addingBuilding, std::list<Building>::iterator& buildingIterator)	//correct
{
	if (addingBuilding.height > buildingIterator->height)
	{
		buildingIterator->beginning = addingBuilding.end;
		buildings.insert(buildingIterator, addingBuilding);
	}
}

void CityModel::case5(Building& addingBuilding, std::list<Building>::iterator& buildingIterator)	//correct
{
	if (addingBuilding.height > buildingIterator->height)
	{
		buildingIterator->height = addingBuilding.height;
	}
}

bool CityModel::case6(Building& addingBuilding, std::list<Building>::iterator& buildingIterator)
{
	if (addingBuilding.height < buildingIterator->height)
	{
		addingBuilding.beginning = buildingIterator->end;
		return true;
	}
	else if (addingBuilding.height >= buildingIterator->height)
	{
		auto next = buildingIterator;
		next++;
		if (next == buildings.end()--)
		{
			buildingIterator->beginning = addingBuilding.beginning;
			buildingIterator->end = addingBuilding.end;
			buildingIterator->height = addingBuilding.height;
			return false;
		}
		
		buildingIterator = buildings.erase(buildingIterator);
		return true;
	}
}

void CityModel::case7(Building& addingBuilding, std::list<Building>::iterator& buildingIterator)	//correct
{
	if (addingBuilding.height > buildingIterator->height)
	{
		buildings.insert(buildingIterator, Building{ buildingIterator->beginning, addingBuilding.beginning,buildingIterator->height });
		buildingIterator->beginning = addingBuilding.end;
		buildings.insert(buildingIterator, addingBuilding);
	}
}

void CityModel::case8(Building& addingBuilding, std::list<Building>::iterator& buildingIterator)	//correct
{
	if (addingBuilding.height > buildingIterator->height)
	{
		buildings.insert(buildingIterator, Building{ buildingIterator->beginning, addingBuilding.beginning,buildingIterator->height });
		buildingIterator->end = addingBuilding.beginning;
		buildingIterator->height = addingBuilding.height;
	}
}

bool CityModel::case9(Building& addingBuilding, std::list<Building>::iterator& buildingIterator)
{
	if (addingBuilding.height < buildingIterator->height)
	{
		addingBuilding.beginning = buildingIterator->end;
		return true;
	}
	else if (addingBuilding.height == buildingIterator->height)
	{
		addingBuilding.beginning = buildingIterator->beginning;
		auto next = buildingIterator;
		next++;
		if (next == buildings.end()--)
		{
			buildingIterator->beginning = addingBuilding.beginning;
			buildingIterator->end = addingBuilding.end;
			buildingIterator->height = addingBuilding.height;
			return false;
		}
		buildingIterator = buildings.erase(buildingIterator);
		return true;
	}
	else
	{
		buildingIterator->end = addingBuilding.beginning;
		return true;
	}
}
