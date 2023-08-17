#include "Hash.h"

// implemented for you - don't change this one
unsigned int DJB2(std::string key){
  unsigned int hash = 5381;
  // Leaving the debugging stuff commented out, in case you want to
  // play. It will output the hash at each incremental step so you can
  // see how it takes shape.
  //
  //  cout << "Hashing string \"" << key << "\"" << endl;
  //  cout << bitset<32>(hash) << " " << hash << endl;
  for (size_t i=0; i < key.length(); i++) {
    char c = key[i]; 
    hash = ((hash << 5) + hash) + c;
    // cout << bitset<32>(hash) << " " << hash << endl;
  }
  // cout << "Hashed string \"" << key << "\" to " << hash << endl;
  //
  // for light reading on why djb2 might not be the best
  // production-grade hash function, go to
  // http://dmytry.blogspot.com/2009/11/horrible-hashes.html
  return hash;
}

// implemented for you - don't change this one
unsigned int ModuloBucketFunc(unsigned int hashcode, unsigned int cap){
  unsigned int b = hashcode % cap;
  return b;
}

// constructor, initialize class variables and pointers here if need.
Hash::Hash(){
  // your code here
}

//deconstructor,
Hash::~Hash(){
}

shared_ptr<hash_table> Hash::InitTable(unsigned int cap){
  shared_ptr<hash_table> ret(new hash_table);
  // your code here
  return ret;
}

shared_ptr<hash_node> Hash::InitNode(std::string key, unsigned int hashcode, std::string val){
  shared_ptr<hash_node> ret(new hash_node);
  // your code here
  return ret;
}

bool Hash::SetKVP(shared_ptr<hash_table> tbl, std::string key, std::string value){
  // your code here
  return false;
}

float Hash::Load(shared_ptr<hash_table> tbl){
  // your code here
  return 0;
}

std::string Hash::GetVal(shared_ptr<hash_table> tbl, std::string key){
  // your code here
  return "";
}

bool Hash::Contains(shared_ptr<hash_table> tbl, std::string key){
  // your code here
  return false;
}

bool Hash::Remove(shared_ptr<hash_table> tbl, std::string key){
  // your code here
  return false;
}

void Hash::Resize(shared_ptr<hash_table> tbl, unsigned int new_capacity){
  // your code here
}

// implemented for you - feel free to change this one if you like
void Hash::PrintTable(shared_ptr<hash_table> tbl){
  cout << "Hashtable:" << endl;
  cout << "  capacity: " << tbl->capacity << endl;
  cout << "  size:     " << tbl->size << endl;
  cout << "  occupied: " << tbl->occupied << endl;
  cout << "  load:     " << Load(tbl) << endl;
  if (tbl->capacity < 130) {
    for (unsigned int i=0; i < tbl->capacity; i++) {
      cout << "[" << i << "]    ";
      if (!tbl->table->at(i)) {
        cout << "<empty>" << endl;
      } else if (tbl->table->at(i)->deleted) {
        cout << "<deleted>" << endl;
      } else {
        cout << "\"" << tbl->table->at(i)->key << "\" = \"" << tbl->table->at(i)->value << "\"" << endl;
      }
    }
  } else {
    cout << "    <hashtable too big to print out>" << endl;
  }
}

