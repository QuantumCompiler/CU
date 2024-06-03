
// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code/PriorityQueue.h"

#include <fstream>
#include <iostream>
#include <math.h>
#include <cmath>
#include <vector>

class test_PriorityQueue : public ::testing::Test {
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

double test_PriorityQueue::total_grade = 0;
double test_PriorityQueue::max_grade = 22;

TEST_F(test_PriorityQueue,InitializeTest) {
	PriorityQueue my_pqueue;
  	shared_ptr<pq> queue = my_pqueue.InitPriorityQueue();
  	ASSERT_TRUE(queue);
	add_points_to_grade(5);
}

TEST_F(test_PriorityQueue,PeekTest) {
	PriorityQueue my_pqueue;
	shared_ptr<pq> queue = my_pqueue.InitPriorityQueue();
  	ASSERT_TRUE(queue);
  	ASSERT_EQ("",my_pqueue.Peek(queue)); // should return empty string for empty list
	add_points_to_grade(5);
}

TEST_F(test_PriorityQueue,InsertTest) {
	PriorityQueue my_pqueue;
	shared_ptr<pq> queue = my_pqueue.InitPriorityQueue();
  	ASSERT_TRUE(queue);

	string origCat = string("Cat Video");
	my_pqueue.Insert(queue, origCat, 3);
	string front = my_pqueue.Peek(queue);
	ASSERT_EQ(front, origCat);
	add_points_to_grade(1);

	string origGame = "Game Packet";
	my_pqueue.Insert(queue, origGame, 5);
	front = my_pqueue.Peek(queue);
	ASSERT_EQ(front, origGame);
	add_points_to_grade(1);

	string origMed = "Medical Packet";
	my_pqueue.Insert(queue, origMed, 10.5);
	front = my_pqueue.Peek(queue);
	ASSERT_EQ(front, origMed);
	add_points_to_grade(1);

	// now insert things less important
	string origCat2 = "Another Cat Video";
	my_pqueue.Insert(queue, origCat2, 3.1);
	front = my_pqueue.Peek(queue);
	ASSERT_EQ(front, origMed); // med packet should win
	add_points_to_grade(1);

	string origGame2 = "Another Game Packet";
	my_pqueue.Insert(queue, origGame2, 1.5);
	front = my_pqueue.Peek(queue);
	ASSERT_EQ(front, origMed);
	add_points_to_grade(1);
}

TEST_F(test_PriorityQueue,RemoveTest) {
  	PriorityQueue my_pqueue;
	shared_ptr<pq> queue = my_pqueue.InitPriorityQueue();
	ASSERT_TRUE(queue);

	my_pqueue.Insert(queue, "Camel", 5.0); // C
	my_pqueue.Insert(queue, "Aardvark", 10); // C A
	my_pqueue.Insert(queue, "Firefly", 2); // F C A
	my_pqueue.Insert(queue, "Doggie", 7); // F C D A
	my_pqueue.Insert(queue, "Gorilla", 5); // F G C D A
	my_pqueue.Insert(queue, "Elephant", 11); // F G C D A E
	my_pqueue.Insert(queue, "Bobcat", 2); // B F G C D A E

  	string popped;
  	popped = my_pqueue.Remove(queue); // B F G C D A
  	ASSERT_EQ("Elephant", popped);
	add_points_to_grade(1);

	popped = my_pqueue.Remove(queue); // B F G C D
	ASSERT_EQ("Aardvark", popped);
	add_points_to_grade(1);

	popped = my_pqueue.Remove(queue); // B F G C
	ASSERT_EQ("Doggie", popped);
	add_points_to_grade(1);

	popped = my_pqueue.Remove(queue); // B F G
	ASSERT_TRUE(popped=="Camel" || popped=="Gorilla");
	add_points_to_grade(1);

	popped = my_pqueue.Remove(queue); // B F
	ASSERT_TRUE(popped=="Camel" || popped=="Gorilla");
	add_points_to_grade(1);

	popped = my_pqueue.Remove(queue); // B
	ASSERT_TRUE(popped=="Firefly" || popped=="Bobcat");
	add_points_to_grade(1);

	popped = my_pqueue.Remove(queue); // empty
	ASSERT_TRUE(popped=="Firefly" || popped=="Bobcat");
	add_points_to_grade(1);
}