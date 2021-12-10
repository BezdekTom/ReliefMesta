#pragma once
#include <list>
#include <vector>
#include <queue>
#include <iostream>

class ReliefCreator
{
private:
	/**
	 *Possibilities, how the new building could overlap already added one.
	 */
	enum class Overlaping
	{
		newOnLeftOfOld,
		newOnRightOfOld,
		newInsideOld,
		oldInsideNew,
		newInAndOnRightOfOld,
		newInAndOnLeftOfOld
	};

	/**
	 * Struct representing a building in he city.
	 *
	 */
	struct Building
	{
		/**
		 * X coordinate of beginning of the building
		 */
		int begin;
		/**
		 * X coordinate of end of the building
		 */
		int end;
		/**
		 * Value representing height of the building
		 */
		int height;

		/**
		 * Finds out how anotherBuilding overlap this building
		 *
		 * \param anotherBuilding
		 * \return one of the overlapping possibilities
		 */
		Overlaping intersects(const Building& anotherBuilding) const;

		/**
		 * Operator compare buildings due to height, higher means bigger.
		 *
		 * \param b second building for comparing
		 * \return
		 */
		bool operator < (const Building& b) const;
	};

	/**
	 * Representing one node in tree of buildings
	 */
	class Node
	{
	public:
		/**
		 * Building in the node
		 */
		Building building;
		/**
		 * Left subtree of this node.
		 * Buildings which are on the left in the relief of the building in this node.
		 */
		Node* leftSubTree = nullptr;
		/**
		 * Right subtree of this node.
		 * Buildings which are on the right in the relief of the building in this node.
		 */
		Node* rightSubTree = nullptr;

		Node(Building _building) :building(_building) {};
		~Node();

	};

	/**
	 * Variable indicates whether the relief was already created.
	 * If the relief is created, only method getRelief does something, other methods do nothing and returning false.
	 */
	bool editable = true;
	/**
	 * Max heap representing buildings, from which relief will be created.
	 */
	std::priority_queue<Building> heapBuilding;
	/**
	 * Represents relief, in format that was given in the assignment.
	 */
	std::vector<int> relief;

	/**
	 * Adds new building, it's part or nothing to the tree(subtree) of buildings, with the root node.
	 * Only building or part of building, which extends the relief, is added.
	 *
	 * \param node root of subtree, the building is being inserted into
	 * \param building the building to insert
	 */
	void insertToTree(Node*& node, const Building& building);

	/**
	 * Converts relief in the tree format to relief in the format that was given in the assignment
	 *
	 * \param root is root of the tree, that represents the relief
	 */
	void treeToVector(Node* root);
	/**
	 * Recursive method called from void treeToVector(Node* root).
	 * Last end is used for adding section with zero height to the relief in the vector form.
	 *
	 * \param root is root of given subtree
	 * \param lastEnd represents X coordinate of the end of the last already processed building
	 * \return X coordinate of the end of the last building processed by this method
	 */
	int treeToVector(Node* root, int lastEnd);

public:
	/**
	 * Adds new building to the vector of Buildings, from which relief is created.
	 *
	 * \param begin is X coordinate of the beginning of the building
	 * \param end is X coordinate of the end of the building
	 * \param height representing height of the building
	 */
	bool addBuilding(int begin, int height, int end);

	/**
	 * Creates relief out of all buildings which were added to the ReliefCreoator.
	 * It could be called just once.
	 * After this method call new buildings cannot be added.
	 *
	 * \return true if it is called the first time, false if the relief is already created
	 */
	bool createRelief();

	/**
	 * Returns the relief in the format that was given in the assignment.
	 *
	 * \return relief, if createRelief was called before or empty vector if createRelief was not called or no building were added.
	 */
	const std::vector<int>& getRelief() const;
};
