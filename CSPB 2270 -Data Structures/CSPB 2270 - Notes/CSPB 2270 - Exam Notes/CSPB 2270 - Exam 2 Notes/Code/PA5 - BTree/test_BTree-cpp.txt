// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code/BTree.h"

#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include "BTreeTestHelp.h"
#include <cmath>

using namespace std;

class test_BTree : public ::testing::Test {
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
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
			std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test_BTree::total_grade = 0;
double test_BTree::max_grade = 3720;

TEST_F(test_BTree, SanityCheck){
  shared_ptr<btree> small = build_small();
  cout << "print_tree writes something like: \"graph btree{ ... }\" to stdout." << endl;
  cout << "use webgraphviz.com to turn that into diagrams of your tree." << endl << endl;
  print_tree(small);
  cout << endl;

  ASSERT_TRUE(check_tree(small));
  ASSERT_TRUE(private_contains(small, 13));
  ASSERT_FALSE(private_contains(small, 14));

  shared_ptr<btree> broken = build_broken(); // invariant should fail
  ASSERT_FALSE(check_tree(broken)); // be sure we catch that
}

TEST_F(test_BTree, CountNodes){
  BTree mybtree;
  shared_ptr<btree> empty = build_empty();
  ASSERT_EQ(1, mybtree.count_nodes(empty)); // not zero, since there's a root node
  add_points_to_grade(20);
  
  shared_ptr<btree> small = build_small();
  ASSERT_EQ(4,mybtree.count_nodes(small));
  add_points_to_grade(20);

  shared_ptr<btree> two_thin = build_two_tier();
  ASSERT_EQ(5,mybtree.count_nodes(two_thin));
  add_points_to_grade(20);

  shared_ptr<btree> two_full = build_full_two_tier();
  ASSERT_EQ(6,mybtree.count_nodes(two_full));
  add_points_to_grade(20);

  shared_ptr<btree> thrice = build_thin_three_tier();
  ASSERT_EQ(9,mybtree.count_nodes(thrice));
  add_points_to_grade(20);
}

TEST_F(test_BTree, CountKeys){
  BTree mybtree;
  shared_ptr<btree> empty = build_empty();
  ASSERT_EQ(0, mybtree.count_keys(empty));
  
  shared_ptr<btree> small = build_small();
  ASSERT_EQ(8, mybtree.count_keys(small));
  add_points_to_grade(20);

  shared_ptr<btree> two_thin = build_two_tier();
  ASSERT_EQ(14, mybtree.count_keys(two_thin));
  add_points_to_grade(20);

  shared_ptr<btree> two_full = build_full_two_tier();
  ASSERT_EQ(19, mybtree.count_keys(two_full));
  add_points_to_grade(30);

  shared_ptr<btree> thrice = build_thin_three_tier();
  ASSERT_EQ(17, mybtree.count_keys(thrice));
  add_points_to_grade(30);
}

TEST_F(test_BTree, FindPresentKeyInLeaf){
  BTree mybtree;

  shared_ptr<btree> small = build_small();
  shared_ptr<btree> node;
  
  node = mybtree.find(small, 17);
  ASSERT_EQ(node,small->children[1]);
  add_points_to_grade(33);

  node = mybtree.find(small, 2);
  ASSERT_EQ(node, small->children[0]);
  add_points_to_grade(33);

  node = mybtree.find(small, 28);
  ASSERT_EQ(node, small->children[2]);
  add_points_to_grade(34);
}

TEST_F(test_BTree, FindPresentKeyInInternalNode){
  BTree mybtree;
  shared_ptr<btree> thrice = build_thin_three_tier();
  shared_ptr<btree> node;

  node = mybtree.find(thrice, 7);
  ASSERT_EQ(node, thrice->children[0]);
  add_points_to_grade(50);

  node = mybtree.find(thrice, 17);
  ASSERT_EQ(node, thrice->children[1]);
  add_points_to_grade(50);
}

TEST_F(test_BTree, FindPresentKeyInRoot){
  BTree mybtree;
  shared_ptr<btree> small = build_small();
  shared_ptr<btree> node;
  
  node = mybtree.find(small, 10);
  ASSERT_EQ(node, small);
  add_points_to_grade(50);

  node = mybtree.find(small, 20);
  ASSERT_EQ(node, small);
  add_points_to_grade(50);
}

TEST_F(test_BTree, FindNotPresentKey){
  BTree mybtree;
  shared_ptr<btree> small = build_small();
  shared_ptr<btree> node;
  
  node = mybtree.find(small, 6);
  ASSERT_EQ(node, small->children[0]);
  add_points_to_grade(25);

  node = mybtree.find(small, 15);
  ASSERT_EQ(node, small->children[1]);
  add_points_to_grade(25);

  node = mybtree.find(small, 21);
  ASSERT_EQ(node, small->children[2]);
  add_points_to_grade(25);
  ASSERT_TRUE(check_tree(small));
  add_points_to_grade(25);
}

TEST_F(test_BTree, InsertKeyIntoEmptyRoot){
  BTree mybtree;
  shared_ptr<btree> empty = build_empty();
  mybtree.insert(empty, 42);
  ASSERT_TRUE(check_tree(empty));
  add_points_to_grade(50);
  ASSERT_TRUE(private_contains(empty, 42));
  add_points_to_grade(50);
}

TEST_F(test_BTree, InsertKeyIntoSemifullRoot){
  BTree mybtree;
  shared_ptr<btree> semi = build_semifull();
  mybtree.insert(semi, 42);
  ASSERT_TRUE(check_tree(semi));
  add_points_to_grade(10);
  ASSERT_TRUE(private_contains(semi, 10));
  add_points_to_grade(10);
  ASSERT_TRUE(private_contains(semi, 30));
  add_points_to_grade(10);
  ASSERT_TRUE(private_contains(semi, 42));
  add_points_to_grade(10);

  mybtree.insert(semi, 7);
  ASSERT_TRUE(check_tree(semi));
  add_points_to_grade(10);
  ASSERT_TRUE(private_contains(semi, 7));
  add_points_to_grade(10);
  ASSERT_TRUE(private_contains(semi, 10));
  add_points_to_grade(10);
  ASSERT_TRUE(private_contains(semi, 30));
  add_points_to_grade(10);
  ASSERT_TRUE(private_contains(semi, 42));
  add_points_to_grade(10);
}

TEST_F(test_BTree, InsertKeyIntoFullRoot){
  BTree mybtree;
  shared_ptr<btree> full = build_full_leaf_root();
  mybtree.insert(full, 15);
  ASSERT_TRUE(check_tree(full));
  add_points_to_grade(50);

  // root should have split and given another level of height
  int height = 0;
  bool leaves_ok = check_height(full, height);
  ASSERT_TRUE(leaves_ok);
  add_points_to_grade(50);
  ASSERT_EQ(1, height);
  add_points_to_grade(300);
}

TEST_F(test_BTree, InsertKeyIntoSemifullLeafNode){
  BTree mybtree;
  // get() a tree with semifull leaf
  shared_ptr<btree> semi = build_two_tier();
  int height = 0;
  bool leaves_ok = check_height(semi, height);
  ASSERT_EQ(1,height);
  add_points_to_grade(20);
  ASSERT_TRUE(leaves_ok);
  add_points_to_grade(20);
  
  // insert a key that would put it in the right spot
  mybtree.insert(semi, 4); // should add to child[0]
  ASSERT_TRUE(check_tree(semi));
  add_points_to_grade(40);
  
  // check that height did not change
  leaves_ok = check_height(semi, height);
  ASSERT_EQ(1, height);
  add_points_to_grade(20);
  ASSERT_TRUE(leaves_ok);
  add_points_to_grade(20);

  // check that key is now present
  ASSERT_TRUE(private_contains(semi->children[0], 4));
  add_points_to_grade(20);

  mybtree.insert(semi, 24); // should add to child[2]
  ASSERT_TRUE(check_tree(semi));
  add_points_to_grade(20);
  leaves_ok = check_height(semi, height);
  ASSERT_EQ(1, height);
  add_points_to_grade(20);
  ASSERT_TRUE(leaves_ok);
  add_points_to_grade(20);
  ASSERT_TRUE(private_contains(semi->children[2], 24));
  add_points_to_grade(20);

  mybtree.insert(semi, 40); // should add to child[3]
  ASSERT_TRUE(check_tree(semi));
  add_points_to_grade(20);
  leaves_ok = check_height(semi, height);
  ASSERT_EQ(1, height);
  add_points_to_grade(20);
  ASSERT_TRUE(leaves_ok);
  add_points_to_grade(20);
  ASSERT_TRUE(private_contains(semi->children[3], 40));
  add_points_to_grade(20);
}

TEST_F(test_BTree, InsertKeyIntoFullLeafNode){
  BTree mybtree;
  shared_ptr<btree> semi = build_two_tier();
  int height = 0;
  bool leaves_ok = check_height(semi, height);
  ASSERT_EQ(1, height);
  add_points_to_grade(50);
  ASSERT_TRUE(leaves_ok);
  add_points_to_grade(50);

  // insert a key that should split child[1]
  mybtree.insert(semi, 18); // should add to child[0]
  ASSERT_TRUE(check_tree(semi));
  add_points_to_grade(100);

  // shouldn't have raised height; parent of insert site had room
  leaves_ok = check_height(semi, height);
  ASSERT_EQ(1, height);
  add_points_to_grade(50);
  ASSERT_TRUE(leaves_ok);  
  add_points_to_grade(50);

  // key 17 should have moved to the root
  ASSERT_TRUE(private_contains(semi, 17));
  add_points_to_grade(50);

  // key 15 should be in child[1]
  ASSERT_TRUE(private_contains(semi->children[1], 15));
  add_points_to_grade(50);

  // and key 19 shoudl be in child[2]
  ASSERT_TRUE(private_contains(semi->children[2], 19));
  add_points_to_grade(100);

  // remember if you're having trouble with this, you can always hack
  // this test file and put some print_tree calls at the trouble
  // spots, then recompile and run to troubleshoot.
}

TEST_F(test_BTree, RemoveNotPresentKeyFromEmptyTree){
  BTree mybtree;
  shared_ptr<btree> semi = build_empty();
  mybtree.remove(semi, 28); // should have no effect
  ASSERT_TRUE(check_tree(semi));
  add_points_to_grade(10);
  ASSERT_FALSE(private_contains(semi, 28)); // no idea why this would be the case
  add_points_to_grade(10);
}

TEST_F(test_BTree, RemoveNotPresentKeyFromNonemptyRoot){
  BTree mybtree;
  shared_ptr<btree> full = build_full_leaf_root();
  ASSERT_TRUE(private_contains(full, 30));
  add_points_to_grade(10);
  mybtree.remove(full, 30);
  ASSERT_TRUE(check_tree(full));
  add_points_to_grade(10);
  ASSERT_FALSE(private_contains(full, 30));
  add_points_to_grade(10);
}

TEST_F(test_BTree, RemoveNotPresentKeyFromLeaf){
  BTree mybtree;
  shared_ptr<btree> semi = build_two_tier();
  mybtree.remove(semi, 28); // should have no effect
  ASSERT_TRUE(check_tree(semi));
  ASSERT_FALSE(private_contains(semi, 28)); // no idea why this would be the case
  add_points_to_grade(100);
}

TEST_F(test_BTree, RemoveKeyFromLeafWithFullSiblings){
  BTree mybtree;
  shared_ptr<btree> semi = build_two_tier();
  mybtree.remove(semi, 27); // should cause a rotate right involving parent and sibling to left
  ASSERT_TRUE(check_tree(semi));
  add_points_to_grade(150);

  // height should remain at 1
  int height = 0;
  bool leaves_ok = check_height(semi, height);
  ASSERT_EQ(1, height);
  add_points_to_grade(50);
  ASSERT_TRUE(leaves_ok);
  add_points_to_grade(150);

  // ensure no node has 27
  ASSERT_FALSE(private_search_all(semi, 27));
  add_points_to_grade(150);
}

TEST_F(test_BTree, RemoveKeyFromLeafWithAtmincapacitySiblings){
  BTree mybtree;
  shared_ptr<btree> thrice = build_thin_three_tier();
  int height = 0;
  bool leaves_ok = check_height(thrice, height);
  ASSERT_EQ(2, height); // just a sanity check
  add_points_to_grade(35);
  ASSERT_TRUE(leaves_ok);
  add_points_to_grade(35);

  mybtree.remove(thrice, 1); // rm 1, smallest value. should result in shorter tree
  leaves_ok = check_height(thrice, height);
  ASSERT_EQ(1, height);
  add_points_to_grade(35);
  ASSERT_TRUE(leaves_ok);
  add_points_to_grade(35);
  ASSERT_TRUE(check_tree(thrice));
  add_points_to_grade(35);
  ASSERT_FALSE(private_search_all(thrice, 1));
  add_points_to_grade(35);

  // reset, do it again but remove 16. this one is on the inside.
  thrice = build_thin_three_tier();
  mybtree.remove(thrice, 16);
  leaves_ok = check_height(thrice, height);
  ASSERT_EQ(1, height);
  add_points_to_grade(35);
  ASSERT_TRUE(leaves_ok);
  add_points_to_grade(35);
  ASSERT_TRUE(check_tree(thrice));
  add_points_to_grade(35);
  ASSERT_FALSE(private_search_all(thrice, 16));
  add_points_to_grade(35);

  // again, remove 26, this is the largest key in the tree
  thrice = build_thin_three_tier();
  mybtree.remove(thrice, 26);
  leaves_ok = check_height(thrice, height);
  ASSERT_EQ(1, height);
  add_points_to_grade(35);
  ASSERT_TRUE(leaves_ok);
  add_points_to_grade(35);
  ASSERT_TRUE(check_tree(thrice));
  add_points_to_grade(40);
  ASSERT_FALSE(private_search_all(thrice, 26));
  add_points_to_grade(40);
}

TEST_F(test_BTree, RemoveKeyFromInternalNodeWithAtmincapacitySiblings){
  BTree mybtree;
  shared_ptr<btree> thrice = build_thin_three_tier();
  int height = 0;
  bool leaves_ok = check_height(thrice, height);
  ASSERT_EQ(2, height); // just a sanity check
  add_points_to_grade(60);
  ASSERT_TRUE(leaves_ok);
  add_points_to_grade(60);

  mybtree.remove(thrice, 4); // rm 4, a key in an internal node.
  leaves_ok = check_height(thrice, height);
  ASSERT_EQ(1,height); // should have shrunk tree by one
  add_points_to_grade(60);
  ASSERT_TRUE(leaves_ok);
  add_points_to_grade(60);
  ASSERT_TRUE(check_tree(thrice));
  add_points_to_grade(60);
  ASSERT_FALSE(private_search_all(thrice, 4));
  add_points_to_grade(60);

  thrice = build_thin_three_tier();
  mybtree.remove(thrice, 24); // rm 24, a key in an internal node.
  leaves_ok = check_height(thrice, height);
  ASSERT_EQ(1, height); // should have shrunk tree by one
  add_points_to_grade(60);
  ASSERT_TRUE(leaves_ok);
  add_points_to_grade(60);
  ASSERT_TRUE(check_tree(thrice));
  add_points_to_grade(60);
  ASSERT_FALSE(private_search_all(thrice, 24));  
  add_points_to_grade(40);
}
