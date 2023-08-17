// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code/Huffman.h"

#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include <ctime>
#include <cmath>

using namespace std;

class test_Huffman : public ::testing::Test {
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

double test_Huffman::total_grade = 0;
double test_Huffman::max_grade = 195;


// forward declaration of helpers
map<char, int> monaMap();
map<char, string> monaEncTbl();
shared_ptr<freq_info> monaTree();
string monaEncoded();
string moonmanEncoded();
void debugTree(shared_ptr<freq_info> n, string spaces);
void fullCircuitFile(string fn, string msg, int expected_size_encoded);


TEST_F(test_Huffman, CreateLeafFrequencyNode){
  Huffman myhuff;
  shared_ptr<freq_info> n = myhuff.CreateLeaf('e', 99);
  ASSERT_TRUE(n);
  add_points_to_grade(1);
  ASSERT_EQ(n->symbol, 'e');
  add_points_to_grade(2);
  ASSERT_EQ(n->count, 99);
  add_points_to_grade(2);
  ASSERT_FALSE(n->left);
  add_points_to_grade(1);
  ASSERT_FALSE(n->right);
  add_points_to_grade(1);
  ASSERT_TRUE(n->is_leaf);
  add_points_to_grade(2);
}

TEST_F(test_Huffman, CreateInternalFrequencyNode){
  shared_ptr<freq_info> l(new freq_info);
  l->symbol = 'e';
  l->count = 10;
  l->left = shared_ptr<freq_info>(NULL);
  l->right = shared_ptr<freq_info>(NULL);
  l->is_leaf = true;
  shared_ptr<freq_info> r(new freq_info);
  r->symbol = 'x';
  r->count = 2;
  r->left = shared_ptr<freq_info>(NULL);
  r->right = shared_ptr<freq_info>(NULL);
  r->is_leaf = true;

  Huffman myhuff;
  shared_ptr<freq_info> comb = myhuff.CombineNodes(l, r);
  ASSERT_TRUE(comb);
  add_points_to_grade(2);
  ASSERT_EQ(comb->count, 12);
  add_points_to_grade(2);
  ASSERT_EQ(comb->left, l);
  add_points_to_grade(2);
  ASSERT_EQ(comb->right, r);
  add_points_to_grade(2);
  ASSERT_FALSE(comb->is_leaf);
  add_points_to_grade(2);
}

TEST_F(test_Huffman, CountSymbols){
  // simulate a file with a stringstream, put text in it
  std::stringstream fake_file;
  fake_file << "fake file text fabulous fred";

  Huffman myhuff;
  map<char, int> lookup;
  char ch;
  while (fake_file >> noskipws >> ch) {
    myhuff.IncrementLookup(lookup, ch);
  }
  ASSERT_EQ(lookup['f'], 4);
  add_points_to_grade(2);
  ASSERT_EQ(lookup['s'], 1);
  add_points_to_grade(2);
  ASSERT_EQ(lookup['!'], 0);
  add_points_to_grade(2);
  ASSERT_EQ(lookup['a'], 2);
  add_points_to_grade(2);
}

TEST_F(test_Huffman, LoadQueue){
  map<char, int> lookup = monaMap();
  Huffman myhuff;
  tree_queue q;
  myhuff.LoadQueue(lookup, q);
  // q should now have the same number of elements as the lookup
  // table.
  ASSERT_EQ(q.size(), lookup.size());
  add_points_to_grade(2);
  // the items in the queue should be in the order: n, o, a, m
  shared_ptr<freq_info> n;
  n = q.top(); q.pop();
  ASSERT_TRUE(n); // pointer shouldn't be NULL
  ASSERT_EQ(n->symbol, 'n');
  add_points_to_grade(2);
  ASSERT_EQ(n->count, 1);
  add_points_to_grade(2);
  n = q.top(); q.pop();
  ASSERT_TRUE(n); // pointer shouldn't be NULL
  ASSERT_EQ(n->symbol, 'o');
  add_points_to_grade(2);
  ASSERT_EQ(n->count, 8);
  add_points_to_grade(2);
  n = q.top(); q.pop();
  ASSERT_TRUE(n); // pointer shouldn't be NULL
  ASSERT_EQ(n->symbol, 'a');
  add_points_to_grade(2);
  ASSERT_EQ(n->count, 10);
  add_points_to_grade(2);
  n = q.top(); q.pop();
  ASSERT_TRUE(n); // pointer shouldn't be NULL
  ASSERT_EQ(n->symbol, 'm');
  add_points_to_grade(2);
  ASSERT_EQ(n->count, 15);
  add_points_to_grade(2);
}

TEST_F(test_Huffman, BuildTree){
  // requires load_queue to work
  map<char, int> lookup = monaMap();
  tree_queue q;
  Huffman myhuff;
  myhuff.LoadQueue(lookup, q);
  shared_ptr<freq_info> r = myhuff.BuildTree(q);
  ASSERT_TRUE(r);
  ASSERT_EQ(r->count, (1 + 8 + 10 + 15));
  add_points_to_grade(3);
  ASSERT_TRUE(r->left);
  add_points_to_grade(3);
  ASSERT_EQ(r->left->count, 15);
  add_points_to_grade(3);
  ASSERT_EQ(r->left->symbol,'m');
  add_points_to_grade(3);
  ASSERT_TRUE(r->right);
  add_points_to_grade(3);
  ASSERT_EQ(r->right->count, 19);
  add_points_to_grade(3);
  ASSERT_TRUE(r->right->left);
  add_points_to_grade(3);
  ASSERT_EQ(r->right->left->count,9);
  add_points_to_grade(3);
  ASSERT_TRUE(r->right->right);
  add_points_to_grade(3);
  ASSERT_EQ(r->right->right->symbol,'a');
  add_points_to_grade(3);
  ASSERT_TRUE(r->right->left->left);
  add_points_to_grade(3);
  ASSERT_EQ(r->right->left->left->symbol,'n');
  add_points_to_grade(3);
  ASSERT_TRUE(r->right->left->right);
  add_points_to_grade(3);
  ASSERT_EQ(r->right->left->right->symbol,'o');
  add_points_to_grade(3);
}

TEST_F(test_Huffman, BuildEncodingTable){
  shared_ptr<freq_info> r = monaTree();
  Huffman myhuff;
  map<char, string> enc_tbl = myhuff.BuildEncodingTable(r);
  map<char, string> key = monaEncTbl();
  ASSERT_EQ(key['m'], enc_tbl['m']);
  add_points_to_grade(7);
  ASSERT_EQ(key['a'], enc_tbl['a']);
  add_points_to_grade(7);
  ASSERT_EQ(key['o'], enc_tbl['o']);
  add_points_to_grade(7);
  ASSERT_EQ(key['n'], enc_tbl['n']);
  add_points_to_grade(7);
}

TEST_F(test_Huffman, EncodeString){
  Huffman myhuff;
  map<char, string> tbl = monaEncTbl();
  string orig = "mona"; 
  string encoded = myhuff.Encode(tbl, orig);
  string expected = monaEncoded();
  ASSERT_EQ(encoded, expected);
  add_points_to_grade(20); 
  orig = "moonman";
  encoded = myhuff.Encode(tbl, orig);
  expected = moonmanEncoded();
  ASSERT_EQ(encoded, expected);
  add_points_to_grade(20);
}

TEST_F(test_Huffman, DecodeString){
  shared_ptr<freq_info> r = monaTree();
  Huffman myhuff;
  string encoded = monaEncoded();
  string decoded = myhuff.Decode(r, encoded);
  ASSERT_EQ(decoded, "mona");
  add_points_to_grade(20);
  encoded = moonmanEncoded();
  decoded =  myhuff.Decode(r, encoded);
  ASSERT_EQ(decoded, "moonman");
  add_points_to_grade(20);
}

TEST_F(test_Huffman, FullCircuitMicroFile){
  fullCircuitFile("../tests/micro.txt", "tax does good, all to lists!!", 115);
  fullCircuitFile("../tests/small.txt", "a minute phrase", 67);
  fullCircuitFile("../tests/pkd.txt", "These pretzels are making me thirsty", 166);
}

// Helper functions down here. Take a look.

map<char, int> monaMap() {
  map<char, int> lookup;
  lookup['m'] = 15;
  lookup['n'] = 1;
  lookup['o'] = 8;
  lookup['a'] = 10;
  return lookup;
}

map<char, string> monaEncTbl() {
  //    [root]
  //   m    [19]
  //      [9]   a
  //     n   o
  map<char, string> tbl;
  tbl['n'] = RIGHT_CHAR + LEFT_CHAR + LEFT_CHAR;
  tbl['m'] = LEFT_CHAR;
  tbl['a'] = RIGHT_CHAR + RIGHT_CHAR;
  tbl['o'] = RIGHT_CHAR + LEFT_CHAR + RIGHT_CHAR;
  return tbl;
}

shared_ptr<freq_info> monaTree() {
  Huffman myhuff;
  shared_ptr<freq_info> nodeM  = myhuff.CreateLeaf('m', 15);
  shared_ptr<freq_info> nodeA  = myhuff.CreateLeaf('a', 10);
  shared_ptr<freq_info> nodeO  = myhuff.CreateLeaf('o',  8);
  shared_ptr<freq_info> nodeN  = myhuff.CreateLeaf('n',  1);
  shared_ptr<freq_info> node9  = myhuff.CombineNodes(nodeN, nodeO);
  shared_ptr<freq_info> node19 = myhuff.CombineNodes(node9, nodeA);
  shared_ptr<freq_info> root   = myhuff.CombineNodes(nodeM, node19);
  return root;
}

string monaEncoded() {
  return LEFT_CHAR + RIGHT_CHAR + LEFT_CHAR + RIGHT_CHAR + RIGHT_CHAR + LEFT_CHAR + LEFT_CHAR + RIGHT_CHAR + RIGHT_CHAR;
}

string moonmanEncoded() {
  return LEFT_CHAR + RIGHT_CHAR + LEFT_CHAR + RIGHT_CHAR + RIGHT_CHAR + LEFT_CHAR + RIGHT_CHAR + RIGHT_CHAR + LEFT_CHAR + LEFT_CHAR + LEFT_CHAR + RIGHT_CHAR + RIGHT_CHAR + RIGHT_CHAR + LEFT_CHAR + LEFT_CHAR;
}

void debugTree(shared_ptr<freq_info> n, string spaces) {
  if (n->is_leaf) {
    cout << spaces << "sym: " << n->symbol << ", count: " << n->count << endl;
  } else {
    cout << spaces << "internal count: " << n->count << endl;
    debugTree(n->left, spaces + "  ");
    debugTree(n->right, spaces + "  ");
  }
}

void fullCircuitFile(string fn, string msg, int expected_size_encoded) {
  // open a file for reading
  fstream fin(fn, fstream::in);

  // create a table that maps symbols with counts
  map<char, int> lookup;
  char ch;
  Huffman myhuff;
  while (fin >> noskipws >> ch) {
    myhuff.IncrementLookup(lookup, ch);
  }

  // create a priority queue based on this table
  tree_queue q;
  myhuff.LoadQueue(lookup, q);

  // create a Huffman codec tree using the priority queue
  shared_ptr<freq_info> hufftree = myhuff.BuildTree(q);
  // if you're hung up on this step, consider uncommenting these debugging lines:
  // 
  // cout << "root node has total symbol count: " << hufftree->count << endl;
  // debugTree(hufftree, "");

  // create an encoding table based on the Huffman codec tree
  map<char, string> enc_table = myhuff.BuildEncodingTable(hufftree);


  // encode the text 'tax does good, all to lists!!'
  string encoded = myhuff.Encode(enc_table, msg);

  cout << "Using corpus from '" << fn << "'" << endl;
  cout << "Original: " << msg << endl;
  cout << "Encoded:  " << encoded << endl;
    
  ASSERT_EQ(encoded.size(), expected_size_encoded);

  // finally decode the encoded string, should get the original back.
  string decoded = myhuff.Decode(hufftree, encoded);
  cout << "Decoded:  " << decoded << endl;
  ASSERT_EQ(decoded, msg);

  float uncompressed_size = (float) msg.size() * 8.0; // mult by 8 because we need to compare bit-length
  float compressed_size = (float) encoded.size();
  cout << "Compression ratio (higher is better): " << (uncompressed_size / compressed_size) << endl;

  cout << endl; // blank line for legibilityness.
}
