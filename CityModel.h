#pragma once
#include <list>
#include <vector>
#include <iostream>

class CityModel
{
private:
	enum class Overlaping {newInfrontOld, newBehindOld, newInsideOld, oldInsideNew, newInAndOnRightOfOld, newInAndOnLeftOfOld};
	struct Building
	{
		int beginning;
		int end;
		int height;
		
		Overlaping intersects(const Building& anotherBuilding)
		{
			if(beginning > anotherBuilding.end)//dont care
			{
				return Overlaping::newBehindOld;
			}
			else if (end < anotherBuilding.beginning) //just insert
			{
				return Overlaping::newInfrontOld;
			}
			else if (beginning >= anotherBuilding.beginning && end<= anotherBuilding.end)
			{
				return Overlaping::newInsideOld;
			}
			else if (beginning < anotherBuilding.beginning && end > anotherBuilding.end)
			{
				return Overlaping::oldInsideNew;
			}
			else if (beginning < anotherBuilding.beginning)
			{
				return Overlaping::newInAndOnLeftOfOld;
			}
			else if(end > anotherBuilding.end)	//could be just else
			{
				return Overlaping::newInAndOnRightOfOld;
			}
		}
		bool operator < (const Building& b) const
		{
			return buildingComparator(*this, b);
		}
	};

	static bool buildingComparator(const Building& b1, const Building& b2);

	void createPanorama(std::list<Building>& panoramaBuildings);

	std::vector<Building> loadedBuildings;
	
public:
	CityModel();
	~CityModel();
	void addBuilding(int beginning, int end, int height);
	std::vector<int> getPanorama();
	void printPanorama();


};

