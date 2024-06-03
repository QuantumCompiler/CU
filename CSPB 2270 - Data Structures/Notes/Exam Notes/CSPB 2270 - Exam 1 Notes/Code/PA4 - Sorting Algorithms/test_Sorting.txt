// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code/Sorting.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class test_Sorting : public ::testing::Test {
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

	void add_points_to_grade(int points){
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
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static int total_grade;
	static int max_grade;
};

int test_Sorting::total_grade = 0;
int test_Sorting::max_grade = 20;


// Forward declarations for helper functions. They are defined after
// the test cases.

vector<int> get_random_data(int how_many, int upper_bound);
bool vector_contains(vector<int> &data, int value);
bool vectors_contain_same(vector<int>& blue, vector<int> &green);
bool is_nondecreasing(vector<int> &data);
vector<int> get_copy(vector<int> &data);
bool is_unprocessed(vector<int>& data, vector<int>& result);

// Test cases

TEST_F(test_Sorting,TestSanityCheck) {

  vector<int> data;
  data.push_back(5);
  data.push_back(25);
  data.push_back(35);
  data.push_back(25);
  data.push_back(55);

  vector<int> response;
  response.push_back(5);
  response.push_back(25);
  response.push_back(30);
  response.push_back(25);
  response.push_back(5);

  vector<int> good_response;
  good_response.push_back(5);
  good_response.push_back(25);
  good_response.push_back(25);
  good_response.push_back(35);
  good_response.push_back(55);

  EXPECT_TRUE(vector_contains(data, 5));
  EXPECT_FALSE(vector_contains(data, 6));
  EXPECT_FALSE(vectors_contain_same(data, response));
  EXPECT_TRUE(vectors_contain_same(data, good_response));
  EXPECT_FALSE(is_nondecreasing(response));
  EXPECT_TRUE(is_nondecreasing(good_response));
  EXPECT_FALSE(is_unprocessed(data, good_response));
	
}

TEST_F(test_Sorting, TestQuickSort) {

  vector<int> input_data = get_random_data(1000, 500);
  vector<int> input_data_orig = get_copy(input_data);
  size_t size_before = input_data.size();
	Sorting mysorting;
  mysorting.quicksort(input_data, 0, (int) size_before-1);
	
  EXPECT_EQ(input_data.size(),size_before);
	add_points_to_grade(1);

  EXPECT_FALSE(is_unprocessed(input_data, input_data_orig));
	
  EXPECT_TRUE(vectors_contain_same(input_data, input_data_orig));
  add_points_to_grade(2);
  EXPECT_TRUE(is_nondecreasing(input_data));
	add_points_to_grade(2);

}

TEST_F(test_Sorting, TestBubbleSort) {

  vector<int> input_data = get_random_data(1000, 500);
  vector<int> input_data_orig = get_copy(input_data);

  size_t size_before = input_data.size();
  Sorting mysorting;
  mysorting.bubblesort(input_data);
	
  EXPECT_FALSE(is_unprocessed(input_data, input_data_orig));
	
  EXPECT_EQ(input_data.size(),size_before);
	add_points_to_grade(1);
  
  EXPECT_FALSE(is_unprocessed(input_data, input_data_orig));

  EXPECT_TRUE(vectors_contain_same(input_data, input_data_orig));
	add_points_to_grade(2);
  EXPECT_TRUE(is_nondecreasing(input_data));
	add_points_to_grade(2);
}

TEST_F(test_Sorting, TestMergeSort) {

  vector<int> input_data = get_random_data(1000, 500);
  vector<int> input_data_orig = get_copy(input_data);

  size_t size_before = input_data.size();
  Sorting mysorting;
  mysorting.mergesort(input_data);
  EXPECT_EQ(input_data.size(),size_before);
	add_points_to_grade(1);
  
  EXPECT_FALSE(is_unprocessed(input_data, input_data_orig));

  EXPECT_TRUE(vectors_contain_same(input_data, input_data_orig));
	add_points_to_grade(2);
  EXPECT_TRUE(is_nondecreasing(input_data));
	add_points_to_grade(2);
}

TEST_F(test_Sorting, TestMysterySort) {
		
  vector<int> input_data = get_random_data(1000, 500);
  vector<int> input_data_orig = get_copy(input_data);

  size_t size_before = input_data.size();
  Sorting mysorting;
  mysorting.mystery_sort(input_data);

  EXPECT_FALSE(is_unprocessed(input_data, input_data_orig));
  
  EXPECT_EQ(input_data.size(), size_before);
	add_points_to_grade(1);
  EXPECT_TRUE(vectors_contain_same(input_data, input_data_orig));
	add_points_to_grade(2);
  EXPECT_TRUE(is_nondecreasing(input_data));
	add_points_to_grade(2);
}

vector<int> get_random_data(int how_many, int upper_bound) {
  vector<int> numbers;
  for (int i=0; i < how_many; i++) {
    int r = rand() % upper_bound;
    numbers.push_back(r);
  }
  return numbers;
}

bool vector_contains(vector<int> &data, int value) {
  bool ret = false;
  for (size_t i = 0; i < data.size(); i++) {
    if (data[i] == value) {
      ret = true;
      break;
    }
  }
  return ret;
}

bool vectors_contain_same(vector<int>& blue, vector<int> &green) {
  bool ret = true;
  if (blue.size() != green.size()) {
    ret = false;
  } else {
    for (size_t i=0; i < blue.size(); i++) {
      int target = blue[i];
      bool found = vector_contains(green, target);
      if (!found) {
				ret = false;
				break;
      }
    }
  }
  return ret;
}

bool is_unprocessed(vector<int>& data, vector<int>& result) {

	if (data.size() != result.size()) return false;
	if (data.size() == 0) return false;  // they are both empty, this is okay 

	// check all values in same locations
	for (size_t i=0 ; i < data.size() ; ++i) {
		if (data[i] != result[i]) return false;
	}
	
	if (data.size() == 1) return false; // only one item, they are same, this is okay

	
	return true;  // cannot find a change in value order
}


bool is_nondecreasing(vector<int>& data) {
  bool ret = true;
  if (data.size() > 1) {
    int prev = data[0];
    for (size_t i=1; i < data.size(); i++) {
      int here = data[i];
      if (prev > here) {
				ret = false;
				break;
      }
      prev = here;
    }
  }
  return ret;
}

vector<int> get_copy(vector<int> &data) {
  vector<int> ret;
  for (size_t i=0; i < data.size(); i++) {
    ret.push_back(data[i]);
  }
  return ret;
}
