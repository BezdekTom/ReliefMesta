#pragma once
#include <list>
#include <vector>
#include <iostream>

class CityModel
{
private:
	struct Building
	{
		int beginning;
		int end;
		int height;
		
		int intersects(const Building& anotherBuilding)
		{
			if(beginning >= anotherBuilding.end)//anotherBuildung koncipred touto budovou
			{
				return 0;
			}
			else if (end <= anotherBuilding.beginning) //anotherBuilding lezi az za touto budovou
			{
				return -1;
			}
			else if (beginning < anotherBuilding.beginning)	//anotherBuiding zacina vic v pravo nez tato building
			{
				if (end < anotherBuilding.end)	//b , aB.b , e, aB.e
				{
					return 1;
				}
				else if (end == anotherBuilding.end)	//b, aB.b, e=aB.e
				{
					return 2;
				}
				else	//b, aB.b , aB.e , e
				{
					return 3;
				}
			}
			else if (beginning == anotherBuilding.beginning)	//anotherBuiding zacina stejne jako tato building
			{
				if (end < anotherBuilding.end)	//b=aB.b , e, aB.e
				{
					return 4;
				}
				else if (end == anotherBuilding.end)	//b=aB.b, e=aB.e
				{
					return 5;
				}
				else	//b=aB.b , aB.e , e
				{
					return 6;
				}
			}
			else	//anotherBuiding zacina vic v levo nez tato building
			{
				if (end < anotherBuilding.end)	//aB.b, b, e, aB.e
				{
					return 7;
				}
				else if (end == anotherBuilding.end)	//aB.b, b, e=aB.e
				{
					return 8;
				}
				else	//aB.b, b, aB.e , e
				{
					return 9;
				}
			}
		}
	};

	std::list<Building> buildings;

	void case1(Building& addingBuilding, std::list<Building>::iterator& buildingIterator);
	void case2(Building& addingBuilding, std::list<Building>::iterator& buildingIterator);
	bool case3(Building& addingBuilding, std::list<Building>::iterator& buildingIterator);
	void case4(Building& addingBuilding, std::list<Building>::iterator& buildingIterator);
	void case5(Building& addingBuilding, std::list<Building>::iterator& buildingIterator);
	bool case6(Building& addingBuilding, std::list<Building>::iterator& buildingIterator);
	void case7(Building& addingBuilding, std::list<Building>::iterator& buildingIterator);
	void case8(Building& addingBuilding, std::list<Building>::iterator& buildingIterator);
	bool case9(Building& addingBuilding, std::list<Building>::iterator& buildingIterator);

public:
	CityModel();
	~CityModel();
	void addBuilding(int beginning, int end, int height);
	void getPanorama();


};

