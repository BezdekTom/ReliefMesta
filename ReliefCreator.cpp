#include <algorithm>
#include <climits>
#include "ReliefCreator.h"

bool ReliefCreator::addBuilding(int begin, int height, int end)
{
	if (editable)
	{
		heapBuilding.push(Building{ begin,end,height });
	}
	return editable;
}

void ReliefCreator::insertToTree(Node*& node, const Building& addingBuilding)
{
	if (node == nullptr)
	{
		node = new Node(addingBuilding);
	}
	else
	{
		switch (addingBuilding.intersects(node->building))
		{
		case Overlaping::newOnRightOfOld:
			insertToTree(node->rightSubTree, addingBuilding);
			break;
		case Overlaping::newOnLeftOfOld:
			insertToTree(node->leftSubTree, addingBuilding);
			break;
		case Overlaping::newInsideOld:
			break;
		case Overlaping::newInAndOnLeftOfOld:
			insertToTree(node->leftSubTree, Building{ addingBuilding.begin, node->building.begin, addingBuilding.height });
			break;
		case Overlaping::newInAndOnRightOfOld:
			if (node->building.height == addingBuilding.height)
			{
				node->building.end = addingBuilding.end;
			}
			else
			{
				insertToTree(node->rightSubTree, Building{ node->building.end,addingBuilding.end, addingBuilding.height });
			}
			break;
		case Overlaping::oldInsideNew:
			insertToTree(node->leftSubTree, Building{ addingBuilding.begin, node->building.begin, addingBuilding.height });
			insertToTree(node->rightSubTree, Building{ node->building.end,addingBuilding.end, addingBuilding.height });
			break;
		default:
			break;
		}
	}
}

bool ReliefCreator::createRelief()
{
	if (!editable)
	{
		return false;
	}

	Node* root = nullptr;

	while (!heapBuilding.empty())
	{
		const Building& addingBuilding = heapBuilding.top();
		insertToTree(root, addingBuilding);
		heapBuilding.pop();
	}

	treeToVector(root);
	delete root;

	editable = false;
	return true;
}

const std::vector<int>& ReliefCreator::getRelief() const
{
	return relief;
}


ReliefCreator::Overlaping ReliefCreator::Building::intersects(const Building& anotherBuilding) const
{
	if (begin > anotherBuilding.end)
	{
		return Overlaping::newOnRightOfOld;
	}
	if (end < anotherBuilding.begin)
	{
		return Overlaping::newOnLeftOfOld;
	}
	if (begin >= anotherBuilding.begin && end <= anotherBuilding.end)
	{
		return Overlaping::newInsideOld;
	}
	if (begin < anotherBuilding.begin && end > anotherBuilding.end)
	{
		return Overlaping::oldInsideNew;
	}
	if (begin < anotherBuilding.begin)
	{
		return Overlaping::newInAndOnLeftOfOld;
	}
	//if (end > anotherBuilding.end)
	return Overlaping::newInAndOnRightOfOld;
}

void ReliefCreator::treeToVector(Node* root)
{
	int lastEnd = treeToVector(root, INT_MAX);
	if (lastEnd < INT_MAX)
	{
		relief.push_back(lastEnd);
		relief.push_back(0);
	}
}

int ReliefCreator::treeToVector(Node* node, int lastEnd)
{
	if (node == nullptr)
	{
		return lastEnd;
	}

	int le = treeToVector(node->leftSubTree, lastEnd);
	if (le < node->building.begin)
	{
		relief.push_back(le);
		relief.push_back(0);
	}
	relief.push_back(node->building.begin);
	relief.push_back(node->building.height);
	return(treeToVector(node->rightSubTree, node->building.end));

}


bool ReliefCreator::Building::operator<(const Building& b) const
{
	if (height > b.height)
	{
		return false;
	}

	if (height == b.height)
	{
		if (begin < b.begin)
		{
			return false;
		}
		if (begin == b.begin)
		{
			if ((end - begin) >= (b.end - b.begin))
			{
				return false;
			}
		}
	}
	return true;
}

ReliefCreator::Node::~Node()
{
	if (rightSubTree != nullptr)
	{
		delete rightSubTree;
		rightSubTree = nullptr;
	}

	if (leftSubTree != nullptr)
	{
		delete leftSubTree;
		leftSubTree = nullptr;
	}
};
