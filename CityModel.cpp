#include <algorithm>
#include <climits>
#include "CityModel.h"

CityModel::CityModel()
{
}

CityModel::~CityModel()
{
	treeDelete(root);
}

void CityModel::addBuilding(int beginning, int end, int height)
{
	loadedBuildings.push_back(Building{ beginning, end, height });
}

std::vector<int> CityModel::getPanorama()
{
	std::list<Building> panoramaBuildings;
	//createPanorama(panoramaBuildings);
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
	//createPanorama(panoramaBuildings);

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

void CityModel::printTreePanorama()
{
	createPanorama();
	std::cout << "(";


	int lastEnd = printTreePanorama(root, INT_MAX);
	if (lastEnd < INT_MAX)
	{
		std::cout << lastEnd << ", 0";
	}
	std::cout <<")" << std::endl;
}

void CityModel::treeDelete(Node* node)
{
	if (node != nullptr)
	{
		treeDelete(node->leftSubTree);
		treeDelete(node->rightSubTree);
		delete node;
	}
}

void CityModel::insertToTree(Node*& node, const Building& addingBuilding)
{
	if (node == nullptr)
	{
		node = new Node(Building{ addingBuilding.beginning, addingBuilding.end, addingBuilding.height});
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
			insertToTree(node->leftSubTree, Building{addingBuilding.beginning, node->building.beginning, addingBuilding.height});
			break;
		case Overlaping::newInAndOnRightOfOld:
			if (node->building.height == addingBuilding.height)
			{
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
				node->building.end = node->rightSubTree->building.beginning;
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
	if(b1.height > b2.height)
	{
		return true;
	}
	else if (b1.height == b2.height)
	{
		if (b1.beginning < b2.beginning)
		{
			return true;
		}
		else if (b1.beginning == b2.beginning)
		{
			if ((b1.end - b1.beginning) >= (b2.end - b2.beginning))
			{
				return true;
			}
		}
	}
	return false;
}

void CityModel::createPanorama()
{
	std::sort(loadedBuildings.begin(), loadedBuildings.end());
	for (Building& addingBuilding : loadedBuildings)
	{
		insertToTree(root, addingBuilding);
	}
}

int CityModel::printTreePanorama(const Node* node, int lastEnd)
{
	if (node != nullptr)
	{
		int le = printTreePanorama(node->leftSubTree, lastEnd);
		if (le < node->building.beginning)
		{
			std::cout << le << ", 0, ";
		}
		std::cout << node->building.beginning<< ", " << node->building.height << ", ";
		return(printTreePanorama(node->rightSubTree, node->building.end));
	}
	return lastEnd;
}


