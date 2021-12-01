#pragma once
#include <list>
#include <vector>
#include <iostream>

class CityModel
{
private:
	/**
	 * .Posibilities, how could new building overlap already add one.
	 */
	enum class Overlaping
	{newInfrontOld, newBehindOld, newInsideOld, oldInsideNew, newInAndOnRightOfOld, newInAndOnLeftOfOld};
	

	struct Building
	{
		int beginning;
		int end;
		int height;
		
		Overlaping intersects(const Building& anotherBuilding) const
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

	class Node
	{
	public:
		Building building;
		Node* leftSubTree = nullptr;
		Node* rightSubTree = nullptr;

		Node(Building _building) { building = _building; };
		~Node()
		{
			if (rightSubTree)
			{
				delete rightSubTree;
				rightSubTree = nullptr;
			}

			if (leftSubTree)
			{
				delete leftSubTree;
				leftSubTree = nullptr;
			}
		};
	};

	Node* root = nullptr;
	std::vector<Building> loadedBuildings;

	void insertToTree(Node*& node,const Building& building);

	void mergeWithRightSubtree(Node*& node);

	static bool buildingComparator(const Building& b1, const Building& b2);

	void createPanorama();

	int getPanorama(const Node* node, int lastEnd, std::vector<int>& panorama);
	int printPanorama(const Node* node, int lastEnd);
	
public:
	CityModel();
	~CityModel();
	
	/**
	 * .Add new building to the vector of Buildings, from which panorama is created
	 * 
	 * \param beginning is cordinate of beginning of the building.
	 * \param end is cordinate of beginning of the building.
	 * \param height 
	 */
	void addBuilding(int beginning, int end, int height);

	/**
	 * .Create new panorama and write it in the panorama, in format beginning of interval, height of interval, beginning of next interval, ...
	 * 
	 * \param panorama vector which will be filled with panorama, should be empty, oitherwise will be erased adn then filled with panorama
	 */
	void createGetPanorama(std::vector<int>& panorama);

	/**
	 * .Create new panorama and print it to the console, in format beginning of interval, height of interval, beginning of next interval, ...
	 * 
	 */
	void createPrintPanorama();


};

