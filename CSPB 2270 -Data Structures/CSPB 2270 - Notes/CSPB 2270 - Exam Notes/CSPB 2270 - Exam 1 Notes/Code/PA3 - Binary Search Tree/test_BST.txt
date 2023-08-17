// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code/BST.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class test_BST : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)(100*total_grade/max_grade);
			outgrade.close();
		
			std::cout << "Total Grade is : " << (int)(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after ever TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test_BST::total_grade = 0;
double test_BST::max_grade = 52;

shared_ptr<bst_node> HandBuildNode( int data )
{
  shared_ptr<bst_node> top(new bst_node);
  top->data = data;
  top->left = NULL;
  top->right = NULL;
  
  return top;
}

shared_ptr<bst_node> HandBuildTree ( )
{
	/* Hand build an unbalanced tree with 0, 1, 2, 3, 4, 5 in it. Looks
	   like this:
	  
	      1
	     / \
	    0   4
	       /  \
	      3    5
	     /
	    2
	*/
	shared_ptr<bst_node> top = HandBuildNode(1);
	top->left = HandBuildNode(0);
	top->right = HandBuildNode(4);
	top->right->left = HandBuildNode(3);
	top->right->left->left = HandBuildNode(2);
	top->right->right = HandBuildNode(5);
	
	return top;
}

TEST_F(test_BST, TestConstructor){
	BST mybst;
	// expect root to be NULL when BST object constructed
	ASSERT_FALSE(mybst.GetRoot());
	add_points_to_grade(2);
}

TEST_F(test_BST, TestInit){
	BST mybst;
	shared_ptr<bst_node> nodeptr = mybst.InitNode(4);  
	ASSERT_TRUE(nodeptr);
	add_points_to_grade(1);
	ASSERT_EQ(4,nodeptr->data);
	add_points_to_grade(1);
	ASSERT_FALSE(nodeptr->left);
	add_points_to_grade(1);
	ASSERT_FALSE(nodeptr->right);
	add_points_to_grade(1);
}

TEST_F(test_BST, TestInsert){
	// hand build four nodes
	shared_ptr<bst_node> top(new bst_node());
	top->data = 2;
	top->left = NULL;
	top->right = NULL;
	shared_ptr<bst_node> one(new bst_node());
	one->data = 1;
	one->left = NULL;
	one->right = NULL;
	shared_ptr<bst_node> three(new bst_node());
	three->data = 3;
	three->left = NULL;
	three->right = NULL;
	shared_ptr<bst_node> four(new bst_node());
	four->data = 4;
	four->left = NULL;
	four->right = NULL;

	// insert them
	BST mybst;
	mybst.Insert(top);
	mybst.Insert(one);
	mybst.Insert(three);
	mybst.Insert(four);

	// expect pointer addresses to be same
	ASSERT_EQ(one.get(),top->left.get());
	add_points_to_grade(2);
	ASSERT_EQ(three.get(),top->right.get());
	add_points_to_grade(2);
	ASSERT_EQ(four.get(),top->right->right.get());
	add_points_to_grade(2);
}

TEST_F(test_BST, TestInsertData){
	// hand build four nodes
	shared_ptr<bst_node> top(new bst_node);
	top->data = 2;
	top->left = NULL;
	top->right = NULL;
	shared_ptr<bst_node> one(new bst_node);
	one->data = 1;
	one->left = NULL;
	one->right = NULL;
	shared_ptr<bst_node> three(new bst_node);
	three->data = 3;
	three->left = NULL;
	three->right = NULL;
	shared_ptr<bst_node> four(new bst_node);
	four->data = 4;
	four->left = NULL;
	four->right = NULL;

	// insert them
	BST mybst;
	mybst.InsertData(2);
	mybst.InsertData(1);
	mybst.InsertData(3);
	mybst.InsertData(4);

	// root shouldn't be null
	ASSERT_TRUE(mybst.GetRoot());
	add_points_to_grade(0.7);

	// check for values in the nodes
	ASSERT_EQ(2,mybst.GetRoot()->data);
	add_points_to_grade(0.7);
	ASSERT_EQ(1,mybst.GetRoot()->left->data);
	add_points_to_grade(0.7);
	ASSERT_EQ(3,mybst.GetRoot()->right->data);
	add_points_to_grade(0.7);
	ASSERT_EQ(4,mybst.GetRoot()->right->right->data);
	add_points_to_grade(0.7);

	// check for NULLs in the leafs
	ASSERT_FALSE(mybst.GetRoot()->left->left);
	add_points_to_grade(0.7);
	ASSERT_FALSE(mybst.GetRoot()->left->right);
	add_points_to_grade(0.7);
	ASSERT_FALSE(mybst.GetRoot()->right->left);
	add_points_to_grade(0.7);
	ASSERT_FALSE(mybst.GetRoot()->right->right->left);
	add_points_to_grade(0.7);
	ASSERT_FALSE(mybst.GetRoot()->right->right->right);
	add_points_to_grade(0.7);
}

TEST_F(test_BST, TestSize){
	// hand build a tree of size 6
	shared_ptr<bst_node> top = HandBuildTree();

	BST mybst;
	ASSERT_EQ(6,mybst.Size(top));
	add_points_to_grade(6);
}

TEST_F(test_BST, TestContains){
	// hand build a tree, check HandBuildTree() function in this file 
	// for how the tree will look like
	shared_ptr<bst_node> top = HandBuildTree();
	
	BST mybst;

	ASSERT_TRUE(mybst.Contains(top, 0));
	ASSERT_TRUE(mybst.Contains(top, 1));
	add_points_to_grade(0.8);
	ASSERT_TRUE(mybst.Contains(top, 2));
	add_points_to_grade(0.8);
	ASSERT_TRUE(mybst.Contains(top, 3));
	add_points_to_grade(0.8);
	ASSERT_TRUE(mybst.Contains(top, 4));
	add_points_to_grade(0.8);
	ASSERT_TRUE(mybst.Contains(top, 5));
	add_points_to_grade(0.8);

	ASSERT_FALSE(mybst.Contains(top, 22));
	add_points_to_grade(0.8);
	ASSERT_FALSE(mybst.Contains(top, -1));
	add_points_to_grade(0.8);
	ASSERT_FALSE(mybst.Contains(top, 10));
	add_points_to_grade(0.8);
	ASSERT_FALSE(mybst.Contains(top, 6));
	add_points_to_grade(0.8);
	ASSERT_FALSE(mybst.Contains(top, 78));
	add_points_to_grade(0.8);
}

TEST_F(test_BST, TestGetNode){

	// test getting a node from empty tree
	{
		BST mybst;
		shared_ptr<bst_node> empty(NULL);
		shared_ptr<bst_node> result = mybst.GetNode(empty,50);
		// result should be NULL
		ASSERT_FALSE(result);
		add_points_to_grade(1);
	}
	// tests getting nodes that we know are NOT there.
	{
		BST mybst;
		shared_ptr<bst_node> top = HandBuildTree();
		ASSERT_FALSE(mybst.GetNode(top,42));
		add_points_to_grade(0.5);
		ASSERT_FALSE(mybst.GetNode(top,-1));
		add_points_to_grade(0.5);
	}
	// tests getting nodes that we know are there.
	{
		BST mybst;
		shared_ptr<bst_node> top = HandBuildTree();
		ASSERT_EQ(mybst.GetNode(top,0),top->left);
		add_points_to_grade(0.5);
		ASSERT_EQ(mybst.GetNode(top,1),top);
		add_points_to_grade(0.5);
		ASSERT_EQ(mybst.GetNode(top,2),top->right->left->left);
		add_points_to_grade(0.5);
		ASSERT_EQ(mybst.GetNode(top,3),top->right->left);
		add_points_to_grade(0.5);
		ASSERT_EQ(mybst.GetNode(top,4),top->right);
		add_points_to_grade(0.5);
		ASSERT_EQ(mybst.GetNode(top,5),top->right->right);
		add_points_to_grade(0.5);
	}
}

TEST_F(test_BST, TestRemove1child){
	// Create separate scopes for this test.
	{
		// Hand build a node with 0, 1, 2, 3, 4, 5 in it.
		shared_ptr<bst_node> top = HandBuildTree();
		
		BST mybst;
		mybst.SetRoot(top);

		// remove the leaf node 5
		// try removing a leaf
		mybst.Remove(5);
		ASSERT_FALSE(top->right->right);
		add_points_to_grade(0.5);

	}	
	{
		// Tests removing a branch with one child.
		// Hand build a node with 0, 1, 2, 3, 4, 5 in it.
		shared_ptr<bst_node> top = HandBuildTree();
		
		BST mybst;
		mybst.SetRoot(top);

		mybst.Remove(3);
		ASSERT_FALSE(top->right->left->left);
		add_points_to_grade(0.5);
		ASSERT_EQ(2,top->right->left->data);
		add_points_to_grade(0.5);
	}
}

TEST_F(test_BST, TestRemovefork){
	{
		shared_ptr<bst_node> top = HandBuildTree();
		BST mybst;
		mybst.SetRoot(top);
		// Remove a node with two children (root)
		mybst.Remove(1);
		ASSERT_EQ(2,mybst.GetRoot()->data);
		add_points_to_grade(0.25);
		ASSERT_FALSE(mybst.GetRoot()->right->left->left);
		add_points_to_grade(0.25);
	}
	{
		shared_ptr<bst_node> top = HandBuildTree();
		BST mybst;
		mybst.SetRoot(top);
		// Remove a node with two children (non-root)
		mybst.Remove(4);
		ASSERT_EQ(5,top->right->data);
		add_points_to_grade(1);
		ASSERT_EQ(1,top->data);
		add_points_to_grade(1);
		ASSERT_FALSE(top->right->right);
		add_points_to_grade(1);
	}
}

bool VectorContains (vector<int>& vec, int value){
	for(unsigned int i = 0; i < vec.size(); i++){
    	if(vec[i] == value){
			return true;
		}
	}
	return false;
}

TEST_F(test_BST, TestToVector){
	
	BST mybst;
	shared_ptr<bst_node> top = HandBuildTree();

	// create a std::vector of size 6 with all values initialized to -1
	vector<int> vec;

	// ToVector function should update all vector indices with values from tree
	mybst.ToVector(top,vec);

	// check if vec was filled in
	ASSERT_EQ(6,vec.size());
	add_points_to_grade(1);

	// check if values were actually from the tree  
	ASSERT_TRUE(VectorContains(vec,0));
	add_points_to_grade(0.5);
	ASSERT_TRUE(VectorContains(vec,1));
	add_points_to_grade(0.5);
	ASSERT_TRUE(VectorContains(vec,2));
	add_points_to_grade(0.7);
	ASSERT_TRUE(VectorContains(vec,3));
	add_points_to_grade(0.7);
	ASSERT_TRUE(VectorContains(vec,4));
	add_points_to_grade(0.7);
	ASSERT_TRUE(VectorContains(vec,5));
	add_points_to_grade(0.7);

	// check if values were from inorder walk of the tree
	ASSERT_EQ(0,vec[0]);
	add_points_to_grade(0.7);
	ASSERT_EQ(1,vec[1]);
	add_points_to_grade(0.7);
	ASSERT_EQ(2,vec[2]);
	add_points_to_grade(0.7);
	ASSERT_EQ(3,vec[3]);
	add_points_to_grade(0.7);
	ASSERT_EQ(4,vec[4]);
	add_points_to_grade(0.7);
	ASSERT_EQ(5,vec[5]);
	add_points_to_grade(0.7);
}