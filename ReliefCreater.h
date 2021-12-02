#pragma once
#include <list>
#include <vector>
#include <queue>
#include <iostream>

class ReliefCreater
{
private:
	/**
	 *Posibilities, how the new building could overlap already added one.
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
		 * X cordinates of begin of the building
		 */
		int begin;
		/**
		 * X cordinates of end of the building
		 */
		int end;
		/**
		 * Value representing height of the building
		 */
		int height;

		/**
		 * Methot, whitch inding out how anotherBuilding overlap this building
		 * 
		 * \param anotherBuilding
		 * \return one of the ovrlaping posibilities
		 */
		Overlaping intersects(const Building& anotherBuilding) const;

		/**
		 * Operator compare buildings due to height, heigher meen bigger. 
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
		 * Bulding in the node
		 */
		Building building;
		/**
		 * Left subtree of this node.
		 * ¨Buildings which are on the left in the relief of building in thi node.
		 */
		Node* leftSubTree = nullptr;
		/**
		 * Right subtree of this node.
		 * Buildings which are on the right in the relief of building in thi node.
		 */
		Node* rightSubTree = nullptr;
		
		Node(Building _building):building(_building){};
		~Node();
		
	};

	/**
	 * Varieble indikates wheather the relief was already created.
	 * If was, only method getRelief do something, other methods do nothing and returning false.
	 */
	bool editable = true;
	/**
	 * Max heap representing buildings, from which relief will be created.
	 */
	std::priority_queue<Building> heapBuilding;
	/**
	 * Represents relief, in format that was given in the assignment
	 */
	std::vector<int> relief;

	/**
	 * Add new building, it's part or nothing to the tree(subtree) of buildings, with the rote node. 
	 * It is added just the part of building, which extends the relief.
	 * 
	 * \param node root of subtree, in which we want insert the building
	 * \param building the building we want to insert
	 */
	void insertToTree(Node*& node, const Building& building);

	/**
	 * If the new building overlap buildings in nodes with same height, this method merge them in one node.
	 * 
	 * \param node represents the new added building, which posibly overlaping buildings in another nodes with same height
	 */
	void mergeWithRightSubtree(Node*& node);

	/**
	 * Convert relief in tree format to relief in format that was given in the assignment
	 * 
	 * \param root is root of the tree, that represents relief
	 */
	void treeToVector(Node* root);
	/**
	 * Rekursive method called in void treeToVector(Node* root).
	 * Last end is using for adding sector with zero height to the relief in vector form.
	 * 
	 * \param root is root of given subtree
	 * \param lastEnd represents X cordinates of end of the last already processed building
	 * \return X cordinates of end of the last, in this method call processed, building
	 */
	int treeToVector(Node* root, int lastEnd);

public:
	ReliefCreater() = default;
	~ReliefCreater() = default;

	/**
	 * Add new building to the vector of Buildings, from which relief is created.
	 *
	 * \param begin is X cordinate of begin of the building
	 * \param end is X cordinate of end of the building
	 * \param height representing height of the building
	 */
	bool addBuilding(int begin, int height, int end);

	/**
	 * Create relif out of all buildings which ewre added to the ReliefMaker.
	 * It could be called just onec.
	 * After the call, no buildigs could be added.
	 * 
	 * \return true if it's call for the first time and create the relief, false if the relief is already created 
	 */
	bool createRelief();

	/**
	 * Return relief in the format that was given in the assignment.
	 * 
	 * \return relief, if createRelief was called before, empty vector if createRelief was not called or there were not added buildings.
	 */
	const std::vector<int>& getRelief() const;
};

