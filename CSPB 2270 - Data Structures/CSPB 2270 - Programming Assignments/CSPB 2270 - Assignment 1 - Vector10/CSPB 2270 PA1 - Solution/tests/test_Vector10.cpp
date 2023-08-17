
// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code/Vector10.h"

#include <fstream>
#include <iostream>
#include <cmath>

class test_Vector10 : public ::testing::Test {
protected:
	static void SetUpTestCase(){
	}

	// This function runs only once before any TEST_F function
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open())
		outgrade.clear();

		outgrade << (int)std::ceil(100*total_grade/max_grade);
		outgrade.close();

		std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
	}

	// This function runs after all TEST_F functions have been executed
	void add_points_to_grade(int points){
		max_grade += points;
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after ever TEST_F function
	void TearDown() override {}
	
	static int total_grade;
	static int max_grade;
};

int test_Vector10::total_grade = 0;
int test_Vector10::max_grade = 0;

TEST_F(test_Vector10, Initialization){
    Vector10 testvec;

    for(int ii=0; ii<10; ii++){
        EXPECT_EQ(0,testvec.ValueAt(ii));
    	add_points_to_grade(1);
    }
}

TEST_F(test_Vector10, TestPushBackNoRemoval){
	Vector10 testvec;

	testvec.PushBack(12);
	testvec.PushBack(45);
	testvec.PushBack(93);
	testvec.PushBack(1000);
	testvec.PushBack(0);
	testvec.PushBack(22);

	EXPECT_EQ(12,testvec.ValueAt(0));
	add_points_to_grade(1);
	EXPECT_EQ(22,testvec.ValueAt(5));
	add_points_to_grade(1);
	EXPECT_EQ(93,testvec.ValueAt(2));
	add_points_to_grade(1);
	EXPECT_EQ(45,testvec.ValueAt(1));
	add_points_to_grade(1);
	EXPECT_EQ(0,testvec.ValueAt(4));
	add_points_to_grade(1);
	EXPECT_EQ(1000,testvec.ValueAt(3));
	add_points_to_grade(1);
}

TEST_F(test_Vector10, TestPushBackOverflow){
    Vector10 testvec;

	for(int i=0; i<10; i++){
		EXPECT_EQ(true,testvec.PushBack(i+12));
		add_points_to_grade(0.3);
	}
	for(int i=0; i<10; i++){
		EXPECT_EQ(false,testvec.PushBack(i*3));
		add_points_to_grade(0.3);
	}
}

TEST_F(test_Vector10, TestCountEmpty){
    Vector10 testvec;

	EXPECT_EQ(10,testvec.CountEmpty());
	add_points_to_grade(2);

	testvec.PushBack(1);
	EXPECT_EQ(9,testvec.CountEmpty());
	add_points_to_grade(2);

	testvec.PushBack(22);
	testvec.PushBack(150);
	testvec.PushBack(90);
	EXPECT_EQ(6,testvec.CountEmpty());
	add_points_to_grade(2);
}

TEST_F(test_Vector10, TestSearch){
	Vector10 testvec;
	
	EXPECT_EQ(false,testvec.Search(12));
	add_points_to_grade(5);

	testvec.PushBack(11);
	testvec.PushBack(12);
	testvec.PushBack(13);
	EXPECT_EQ(true,testvec.Search(12));
	add_points_to_grade(5);
}

TEST_F(test_Vector10, TestRemove){
	Vector10 testvec;

	testvec.PushBack(11);
	testvec.PushBack(12);
	testvec.PushBack(13);
	testvec.PushBack(19);
	testvec.PushBack(1000);
	testvec.PushBack(3);

	EXPECT_EQ(false,testvec.Remove(200));
	add_points_to_grade(2);

	EXPECT_EQ(true,testvec.Remove(1));
	add_points_to_grade(2);

	EXPECT_EQ(1000,testvec.ValueAt(3));
	add_points_to_grade(2);
}