//
// btree_unittest_help.cpp
//
// This is the start of a bunch of helper functions. I'm giving it to
// you so you can use it as a starting point for your own purposes (or
// not, it is up to you).

#include <sstream>
#include <iostream>
#include <string>
#include <climits>
#include <cmath>
#include "BTreeTestHelp.h"

using namespace std;

shared_ptr<btree> init_node() {
  shared_ptr<btree> ret = shared_ptr<btree>(new btree);
  ret->num_keys = 0;
  ret->is_leaf = true;
  for (int i=0; i <= BTREE_ORDER; i++) {
    ret->children[i] = NULL;
  }
  return ret;
}

shared_ptr<btree> build_broken() {
  
  int vals[] = { 10, 20 };
  shared_ptr<btree> root = build_node(2, vals);
  // now we need three children
  int vals2[] = { 2, 8 };
  shared_ptr<btree> left = build_node(2, vals2);
  int vals3[] = { 13, 17 };
  shared_ptr<btree> mid =  build_node(2, vals3);
  int vals4[] = { 28 };
  shared_ptr<btree> right = build_node(1, vals4); // right node is under capacity!
  root->is_leaf = false;
  root->children[0] = left;
  root->children[1] = mid;
  root->children[2] = right;
  return root;  
}

shared_ptr<btree> build_semifull() {
  int vals[] = { 10, 30 };
  shared_ptr<btree> root = build_node(2, vals);
  root->num_keys = 2;
  return root;
}

shared_ptr<btree> build_empty() {
  return init_node();
}

shared_ptr<btree> build_full_leaf_root() {
  int vals[] = { 10, 20, 30, 40 };
  shared_ptr<btree> root = build_node(4, vals);
  root->num_keys = 4;
  return root;
}

shared_ptr<btree> build_small() {
  //       root
  //      10   20
  //    /    |    \
  //  2,8  13,17  24,28
  // left   mid    right
  
  int vals[] = { 10, 20 };
  shared_ptr<btree> root = build_node(2, vals);
  // now we need three children
  int vals2[] = { 2, 8 };
  shared_ptr<btree> left = build_node(2, vals2);
  int vals3[] = { 13, 17 };
  shared_ptr<btree> mid =  build_node(2, vals3);
  int vals4[] = { 24, 28 };
  shared_ptr<btree> right = build_node(2, vals4);
  root->is_leaf = false;
  root->children[0] = left;
  root->children[1] = mid;
  root->children[2] = right;
  return root;
}

shared_ptr<btree> build_two_tier() {
  //        [10,    20,   30]
  //       /     |      \       \
  //     /       |        \       \
  // [5,8] [13,15,17,19] [23,27] [33,35,38]
  int valsRoot[] = { 10, 20, 30 };
  shared_ptr<btree> root = build_node(3, valsRoot);
  int vals1[] = { 5, 8 };
  shared_ptr<btree> ch1 = build_node(2, vals1);
  int vals2[] = { 13, 15, 17, 19 };
  shared_ptr<btree> ch2 = build_node(4, vals2);
  int vals3[] = { 23, 27 };
  shared_ptr<btree> ch3 = build_node(2, vals3);
  int vals4[] = { 33, 35, 38 };
  shared_ptr<btree> ch4 = build_node(3, vals4);
  root->children[0] = ch1;
  root->children[1] = ch2;
  root->children[2] = ch3;
  root->children[3] = ch4;
  root->is_leaf = false;
  root->num_keys = 3;
  return root;
}

shared_ptr<btree> build_full_two_tier() {
  //     [4,    7,        13,        20]
  //     /   |       |           |      \
  //    /    |       |           |       \
  // [1,3] [5,6] [8,11,12] [14,16,17,18] [23,24,25,26]
  int valsRoot[] = { 4, 7, 13, 20 };
  shared_ptr<btree> root = build_node(4, valsRoot);

  int vals_ch0[] = { 1, 3 };
  shared_ptr<btree> ch0 =  build_node(2, vals_ch0);

  int vals_ch1[] = { 5, 6 };
  shared_ptr<btree> ch1 =  build_node(2, vals_ch1);

  int vals_ch2[] = { 8, 11, 12 };
  shared_ptr<btree> ch2 =  build_node(3, vals_ch2);

  int vals_ch3[] = { 14, 16, 17, 18 };
  shared_ptr<btree> ch3 =  build_node(4, vals_ch3);

  int vals_ch4[] = { 23, 24, 25, 26 };
  shared_ptr<btree> ch4 =  build_node(4, vals_ch4);

  root->children[0] = ch0;
  root->children[1] = ch1;
  root->children[2] = ch2;
  root->children[3] = ch3;
  root->children[4] = ch4;
  root->is_leaf = false;
  root->num_keys = 4;
  return root;
}

shared_ptr<btree> build_thin_three_tier() {
  int valsRoot[] = { 13 };
  shared_ptr<btree> root = build_node(1, valsRoot);

  int vals_ch0[] = { 4, 7 };
  shared_ptr<btree> ch0 =  build_node(2, vals_ch0);

  int vals_ch1[] = { 17, 24 };
  shared_ptr<btree> ch1 =  build_node(2, vals_ch1);

  root->is_leaf = false;
  root->children[0] = ch0;
  root->children[1] = ch1;
  ch0->is_leaf = false;
  ch1->is_leaf = false;

  int leaf_ch0[] = { 1, 3 };
  shared_ptr<btree> l0 =  build_node(2, leaf_ch0);
  
  int leaf_ch1[] = { 5, 6 };
  shared_ptr<btree> l1 =  build_node(2, leaf_ch1);
  
  int leaf_ch2[] = { 11, 12 };
  shared_ptr<btree> l2 =  build_node(2, leaf_ch2);

  ch0->children[0] = l0;
  ch0->children[1] = l1;
  ch0->children[2] = l2;
  
  int leaf_r0[] = { 14, 16 };
  shared_ptr<btree> r0 =  build_node(2, leaf_r0);
  
  int leaf_r1[] = { 19, 23 };
  shared_ptr<btree> r1 =  build_node(2, leaf_r1);
  
  int leaf_r2[] = { 25, 26 };
  shared_ptr<btree> r2 =  build_node(2, leaf_r2);
  
  ch1->children[0] = r0;
  ch1->children[1] = r1;
  ch1->children[2] = r2;

  return root;
}

shared_ptr<btree> build_node(int size, int* keys) {
  shared_ptr<btree> node = init_node();
  node->num_keys = size;
  for (int i=0; i < node->num_keys; i++) {
    node->keys[i] = keys[i];
  }
  return node;
}

string get_id_for_dot(shared_ptr<btree> node) {
  stringstream ss;
  ss << node; // address in memory
  string as_addr = ss.str();
  as_addr.replace(0, 2, "BT_");
  return as_addr;
}

string get_label_for_dot(shared_ptr<btree> node) {
  stringstream ss;
  for (int i=0; i < node->num_keys; i++) {
    ss << "" << node->keys[i];
    if (i+1 < node->num_keys) {
      ss << " ";
    }
  }
  return ss.str();
}

void print_dot_label(shared_ptr<btree> node) {
  cout << "    " << get_id_for_dot(node) 
       << " [label=\"" << get_label_for_dot(node) << "\"];" << endl;
}

void print_graphviz_dotfile(shared_ptr<btree> node, int depth) {
  string spaces = "    ";
  if (depth == 0) {
    print_dot_label(node);
  }
  int idx = 0;
  string my_id = get_id_for_dot(node);
  for ( ; idx < node->num_keys; idx++) {
    if (!node->is_leaf) { // don't recurse if this is a leaf.
      print_dot_label(node->children[idx]);
      cout << spaces << my_id << " -- " << get_id_for_dot(node->children[idx]) << ";" << endl;
      print_graphviz_dotfile(node->children[idx], depth + 1);
    }
  }
  // there is always one leftover child, assuming it is not a leaf.
  if (!node->is_leaf) {
    print_dot_label(node->children[idx]);
    cout << spaces << my_id << " -- " << get_id_for_dot(node->children[idx]) << ";" << endl;
    print_graphviz_dotfile(node->children[idx], depth + 1);    
  }
}


// print_tree prints the tree to stdout using the graphviz 'dot'
// format. just copy the generated text and run it through graphviz to
// view it.
//
// there is a web-based viewer at http://www.webgraphviz.com/
void print_tree(shared_ptr<btree> root) {
  cout << "graph btree {" << endl;
  int depth = 0;
  print_graphviz_dotfile(root, depth);
  cout << "}" << endl;
}

bool check_tree(shared_ptr<btree> root) {
  bool ret = false;
  invariants* invars = new invariants;
  check_invariants(invars, root, true);
  ret = !any_false(invars);
  delete invars;
  return ret;  
}

void check_invariants(invariants* &invars, shared_ptr<btree> node, bool is_root) {

  if (is_root && node == NULL) {
    invars->ascending = true;
    invars->not_fat = true;
    invars->not_starving = true;
    invars->good_root = true;
    invars->height_match = true;
    invars->child_key_order = true;
  } else {
    // A node's keys are kept in ascending order, starting at index 0.
    invars->ascending = true;
    int prev = INT_MIN;
    for (int i=0; i < node->num_keys; i++) {
      if (node->keys[i] <= prev) {
	invars->ascending = false;
	break;
      }
    }

    // A node may have at most m children.
    invars->not_fat = node->num_keys < BTREE_ORDER;

    // Non-root nodes have at least round_up(m/2) - 1 keys
    int min_keys = (int) ceil(BTREE_ORDER/2.0) - 1;
    invars->not_starving = is_root;
    if (!is_root) {
      invars->not_starving = node->num_keys >= min_keys;
    }

    // If the root is not a leaf, it has at least two children.
    invars->good_root = true;
    if (is_root && !node->is_leaf) {
      invars->good_root = node->num_keys >= 1;
    }

    // All leaves are at the same level. Only need to check this if you
    // are running the invariant tests on the root of the entire tree.
    invars->height_match = true;
    if (is_root) {
      int res = 0;
      invars->height_match = check_height(node, res);
    }
  
    // child[i] holds keys that are less than key[i]. The final child
    // holds keys that are larger than the final key.
    //  child_key_order = false;
    invars->child_key_order = true;
    if (is_root && !node->is_leaf) {
      invars->child_key_order = check_node_key_range(node, INT_MIN, INT_MAX, true);
    }

    if (any_false(invars)) {
      return;
    } else if (!node->is_leaf) {
      for (int i=0; i <= node->num_keys; i++) {
	check_invariants(invars, node->children[i], false);
	if(any_false(invars)) {
	  return;
	}
      }
    }
  }  
}


void check_leaf_height(shared_ptr<btree> node, vector<int>& depth, int current_depth) {
  if (node->is_leaf) {
    depth.push_back(current_depth);
  } else {
    for (int i=0; i <= node->num_keys; i++) {
      check_leaf_height(node->children[i], depth, current_depth + 1);
    }
  }
}

bool check_height(shared_ptr<btree> node, int& result_height) {
  vector<int> depth;
  check_leaf_height(node, depth, 0);
  int val = 0;
  bool same = false;
  for (size_t i=0; i < depth.size(); i++) {
    if (i == 0) {
      val = depth[i];
      result_height = val;
      same = true;
    } else {
      int other = depth[i];
      if (val != other) {
        same = false;
        break;
      }
    }
  }
  return same;
}

void check_size(shared_ptr<btree> node, int& result_nodes, int& result_keys, bool is_root) {
  if (is_root) {
    result_nodes = 0;
    result_keys = 0;
  }
  if (node == NULL) {
    return;
  }
  result_nodes++;
  result_keys = result_keys + node->num_keys;
  if (!node->is_leaf) {
    for (int i=0; i <= node->num_keys; i++) {
      check_size(node->children[i], result_nodes, result_keys, false);
    }
  }
}

bool check_node_key_range(shared_ptr<btree> node, int low, int high, bool recurse) {

  for (int i=0; i < node->num_keys; i++) {
    if (node->keys[i] <= low || // key is out of low range
	node->keys[i] >= high) {// key is out of high range
      return false;
    }
    if (!node->is_leaf && recurse) {
      bool child_result = check_node_key_range(node->children[i], low, node->keys[i], recurse);
      if (!child_result) {
	return false;
      }
    }
    low = node->keys[i];
  }
  if (!node->is_leaf && recurse) {
    // need to check that last child is in range too
    bool child_result = check_node_key_range(node->children[node->num_keys], 
					     low, high, recurse);
    if (!child_result) {
      return false;
    }
  }
  return true;
}

bool any_false(invariants* &invars) {
  bool wrong = 
    invars->ascending &&
    invars->not_fat &&
    invars->not_starving &&
    invars->good_root &&
    invars->height_match &&
    invars->child_key_order;

  return !wrong;
}

bool private_contains(shared_ptr<btree> node, int key) {
  if (node == NULL) {
    return false;
  }
  for (int i=0; i < node->num_keys; i++) {
    if (node->keys[i] == key) {
      return true;
    } else if (!node->is_leaf && node->keys[i] > key) {
      // if the key is larger than target, answer will be in child i
      return private_contains(node->children[i], key);
    }
  }
  if (!node->is_leaf && node->keys[node->num_keys-1] < key) {
    return private_contains(node->children[node->num_keys], key);
  }
  return false;
}


bool private_search_all(shared_ptr<btree> node, int key) {
  if (private_contains(node, key)) {
    return true; // found it here!
  }
if (!node->is_leaf)
{
  for (int i=0; i <= node->num_keys; i++) {
    // search every child, don't pay attention to sort order
    if (private_search_all(node->children[i], key)) {
      return true;
    }
  }
}
  return false;
}