#include <algorithm>
#include <climits>
#include "CityModel.h"

CityModel::CityModel()
{
}

CityModel::~CityModel()
{
	delete root;
}

void CityModel::addBuilding(int beginning, int end, int height)
{
	heapBuilding.push(Building{ beginning,end,height });
}

void CityModel::getPanorama(std::vector<int>& panorama)
{
	int lastEnd = getPanorama(root, INT_MAX, panorama);
	if (lastEnd < INT_MAX)
	{
		panorama.push_back(lastEnd);
		panorama.push_back(0);
	}
}

void CityModel::printPanorama()
{
	std::cout << "(";

	int lastEnd = printPanorama(root, INT_MAX);
	if (lastEnd < INT_MAX)
	{
		std::cout << lastEnd << ", 0";
	}
	std::cout << ")" << std::endl;
}

void CityModel::insertToTree(Node*& node, const Building& addingBuilding)
{
	if (node == nullptr)
	{
		node = new Node(Building{ addingBuilding.beginning, addingBuilding.end, addingBuilding.height });
	}
	else
	{
		switch (addingBuilding.intersects(node->building))
		{
		case Overlaping::newBehindOld:
			insertToTree(node->rightSubTree, addingBuilding);
			break;
		case Overlaping::newInfrontOld:
			insertToTree(node->leftSubTree, addingBuilding);
			break;
		case Overlaping::newInsideOld:
			break;
		case Overlaping::newInAndOnLeftOfOld:
			insertToTree(node->leftSubTree, Building{ addingBuilding.beginning, node->building.beginning, addingBuilding.height });
			break;
		case Overlaping::newInAndOnRightOfOld:
			if (node->building.height == addingBuilding.height)
			{
				node->building.end = addingBuilding.end;
				mergeWithRightSubtree(node);
			}
			else
			{
				insertToTree(node->rightSubTree, Building{ node->building.end,addingBuilding.end, addingBuilding.height });
			}
			break;
		case Overlaping::oldInsideNew:
			insertToTree(node->leftSubTree, Building{ addingBuilding.beginning, node->building.beginning, addingBuilding.height });
			insertToTree(node->rightSubTree, Building{ node->building.end,addingBuilding.end, addingBuilding.height });
			break;
		default:
			break;
		}
	}
}

void CityModel::mergeWithRightSubtree(Node*& node)
{
	bool merging = true;
	while (merging)
	{
		if (node->rightSubTree != nullptr)
		{
			if (node->rightSubTree->building.beginning <= node->building.end)
			{
				if (node->building.end < node->rightSubTree->building.end)
				{
					node->building.end = node->rightSubTree->building.end;
				}
				Node* rst = node->rightSubTree;
				node->rightSubTree = rst->rightSubTree;
				delete rst;
			}
			else
			{
				merging = false;
			}
		}
		else
		{
			merging = false;
		}
	}
}

bool CityModel::buildingComparator(const Building& b1, const Building& b2)
{
	if (b1.height > b2.height)
	{
		return false;
	}
	else if (b1.height == b2.height)
	{
		if (b1.beginning < b2.beginning)
		{
			return false;
		}
		else if (b1.beginning == b2.beginning)
		{
			if ((b1.end - b1.beginning) >= (b2.end - b2.beginning))
			{
				return false;
			}
		}
	}
	return true;
}

void CityModel::createPanorama()
{
	delete root;
	root = nullptr;

	while (!heapBuilding.empty())
	{
		const Building& addingBuilding = heapBuilding.top();
		insertToTree(root, addingBuilding);
		heapBuilding.pop();
	}
}

int CityModel::getPanorama(const Node* node, int lastEnd, std::vector<int>& panorama)
{
	if (node != nullptr)
	{
		int le = getPanorama(node->leftSubTree, lastEnd, panorama);
		if (le < node->building.beginning)
		{
			panorama.push_back(le);
			panorama.push_back(0);
		}
		panorama.push_back(node->building.beginning);
		panorama.push_back(node->building.height);
		return(getPanorama(node->rightSubTree, node->building.end, panorama));
	}
	return lastEnd;
}

int CityModel::printPanorama(const Node* node, int lastEnd)
{
	if (node != nullptr)
	{
		int le = printPanorama(node->leftSubTree, lastEnd);
		if (le < node->building.beginning)
		{
			std::cout << le << ", 0, ";
		}
		std::cout << node->building.beginning << ", " << node->building.height << ", ";
		return(printPanorama(node->rightSubTree, node->building.end));
	}
	return lastEnd;
}


