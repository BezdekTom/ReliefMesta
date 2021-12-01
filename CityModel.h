#pragma once
#include <list>
#include <vector>
#include <queue>
#include <iostream>

class CityModel
{
private:
	/**
	 * .Posibilities, how could new building overlap already add one.
	 */
	enum class Overlaping
	{
		newInfrontOld, newBehindOld, newInsideOld, oldInsideNew, newInAndOnRightOfOld, newInAndOnLeftOfOld
	};


	struct Building
	{
		int beginning;
		int end;
		int height;

		Overlaping intersects(const Building& anotherBuilding) const
		{
			if (beginning > anotherBuilding.end)
			{
				return Overlaping::newBehindOld;
			}
			if (end < anotherBuilding.beginning)
			{
				return Overlaping::newInfrontOld;
			}
			if (beginning >= anotherBuilding.beginning && end <= anotherBuilding.end)
			{
				return Overlaping::newInsideOld;
			}
			if (beginning < anotherBuilding.beginning && end > anotherBuilding.end)
			{
				return Overlaping::oldInsideNew;
			}
			if (beginning < anotherBuilding.beginning)
			{
				return Overlaping::newInAndOnLeftOfOld;
			}
			//if (end > anotherBuilding.end)
			return Overlaping::newInAndOnRightOfOld;
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
	std::priority_queue<Building> heapBuilding;

	void insertToTree(Node*& node, const Building& building);

	void mergeWithRightSubtree(Node*& node);

	static bool buildingComparator(const Building& b1, const Building& b2);

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

	void createPanorama();

	/**
	 * .Create new panorama and write it in the panorama, in format beginning of interval, height of interval, beginning of next interval, ...
	 *
	 * \param panorama vector which will be filled with panorama, should be empty, oitherwise will be erased adn then filled with panorama
	 */
	void getPanorama(std::vector<int>& panorama);

	/**
	 * .Create new panorama and print it to the console, in format beginning of interval, height of interval, beginning of next interval, ...
	 *
	 */
	void printPanorama();


};

