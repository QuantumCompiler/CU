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
Hash::Hash(){}

//deconstructor,
Hash::~Hash(){}

/*  InitTable - Initializes a hash table to be of a specific capacity
*   Input:
*     cap - Unsigned integer value that represents the capacity of the hash table
*   Algorithm:
*     * Create a hash table "ret" that is to be returned after modifying it's data members
*     * Assign the data members to their correct initial values
*     * Return the modified hash table
*   Output:
*     ret - Smart pointer of object type "hash_table" that is returned after being assigned to the input parameters of "InitTable"
*/
shared_ptr<hash_table> Hash::InitTable(unsigned int cap){
  // Table to be returned
  shared_ptr<hash_table> ret(new hash_table);
  // Assign input parameters to the data members of the the hash table "ret"
  ret->capacity = cap;
  ret->size = 0;
  ret->occupied = 0;
  ret->table = shared_ptr<htable>(new htable(cap));
  for (int i = 0; i < ret->table->size(); i++) {
    ret->table->at(i) = nullptr;
  }
  ret->hash_func = &DJB2;
  ret->bucket_func = &ModuloBucketFunc;
  // Return the modified hash table
  return ret;
}

/*  InitNode - Initializes a node in a hash table to given values
*   Input:
*     key - String value that represents key associated with the value of the node
*     hashcode - Unsigned integer value that represents the hash code of the key
*     val - String value that represents value that is to be associated with the key
*   Algorithm:
*     * Create an object "hash_node" that is to be returned after modifying it's data members
*     * Assign the data members of "ret" to the input parameters fed to "InitNode"
*     * Return the modified hash node
*   Output:
*     ret - Smart pointer of object type "hash_node" that is returned after being assigned the input parameters of "InitNode"
*/
shared_ptr<hash_node> Hash::InitNode(std::string key, unsigned int hashcode, std::string val){
  // Node to be returned
  shared_ptr<hash_node> ret(new hash_node);
  // Assign input parameters to hash_node data members
  ret->deleted = false;
  ret->key = key;
  ret->hashcode = hashcode;
  ret->value = val;
  // Return node
  return ret;
}

/*  SetKVP - Set key value pair inserts a hash node into a hash table with the given parameters
*   Input:
*     tbl - Smart pointer of object type "hash_table" that represents the hash table that is being modified
*   Algorithm:
*     * Calculate the hash code and the bucket index of key and value that is to be inserted
*     * Create a dummy variable that keeps track of the buckets that have been probed
*     * Create a hash node with the input parameters key and value along with it's calculated hash code
*     * Check to see if the current bucket is empty
*       * If it is, insert the node into that bucket and update the data members of the table
*       * Return true
*     * Check to see if the current buckets key is equal to that of the input parameters key
*       * If it is, update the current index's value with the input parameter "value"
*       * Return true
*     * Modify the bucket index and increment the buckets probed value
*     * Return false if the condition of the while loop is not met
*   Output:
*     This function returns a boolean value indicating if a hash table successfully inserted a node
*/
bool Hash::SetKVP(shared_ptr<hash_table> tbl, std::string key, std::string value){
  // Determine the hash value and bucket index for node
  unsigned int hash = DJB2(key);
  unsigned int bucket_idx = tbl->bucket_func(hash, tbl->capacity);
  // Create a value that indicates if a bucket has been probed to be inserted
  unsigned int buckets_probed = 0;
  // Create a hash node that is to be inserted into the hash table
  shared_ptr<hash_node> node = InitNode(key, hash, value);
  // Repeat process until all possible buckets have been probed
  while (buckets_probed < tbl->table->size()) {
    // Check if the current bucket is empty, if it is, insert the node at that index and update data members
    if (tbl->table->at(bucket_idx) == nullptr) {
      tbl->table->at(bucket_idx) = node;
      tbl->occupied++;
      tbl->size++;
      return true;
    }
    // Check if the current bucket's key is equal to that of the input parameters key, if so, update value
    else if (tbl->table->at(bucket_idx)->key == key) {
      tbl->table->at(bucket_idx)->value = value;
      return true;
    }
    // Increment the bucket index and buckets probed values
    bucket_idx = (bucket_idx + 1) % tbl->table->size();
    buckets_probed++;
  }
  return false;
}

/*  Load - Calculates the load value of a hash table
*   Input:
*     tbl - Smart pointer of object type "hash_table" that represents the table of which the load is being calculated for
*   Algorithm:
*     * Cast the integer values of "tbl" to float values
*     * Calculate the load factor of the table by using size / capacity
*     * Return the load factor
*   Output:
*     load - Float value that represents the load of the given table in the input parameter
*/
float Hash::Load(shared_ptr<hash_table> tbl){
  // Cast the integer values to floats
  float size = static_cast<float>(tbl->size);
  float cap = static_cast<float>(tbl->capacity);
  // Calculate the load factor
  float load = size / cap;
  // Return the load factor
  return load;
}

/*  GetVal - Returns the value of a key if it is present in the hash table
*   Input:
*     tbl - Smart pointer of object type "hash_table" that represents the hash table that we are searching in
*     key - String value that represents the key value of the hash node that we are looking for
*   Algorithm:
*     * Calculate the hash code and bucket index of the given key
*     * Create a dummy variable for the number of buckets that have been probed
*     * Traverse the table until the number of buckets probed equals that of the tables size
*     * Check to see if the current nodes key value matches that of the input parameter "key"
*       * If it does, return its value
*     * Otherwise, increment both buckets probed and bucket index
*     * Return null if the key is not present in the table
*   Output:
*     This function returns a string value indicating a keys value if it is present in the hash table
*/
std::string Hash::GetVal(shared_ptr<hash_table> tbl, std::string key){
  // Calculate the hash code and bucket index of the given key
  unsigned int hash = DJB2(key);
  unsigned int bucket_idx = tbl->bucket_func(hash, tbl->capacity);
  // Create a dummy variable to indicate the buckets that have been probed in the table
  unsigned int buckets_probed = 0;
  // Traverse the table until buckets probed reaches the size of the table
  while (buckets_probed < tbl->size) {
    // If the current nodes key data member matches that of the input parameter "key", return its value
    if (tbl->table->at(bucket_idx)->key == key) {
      return tbl->table->at(bucket_idx)->value;
    }
    // Increment the bucket index and buckets probed values
    bucket_idx = (bucket_idx + 1) % tbl->size;
    buckets_probed++;
  }
  // Return null if nothing was found
  return "";
}

/*  Contains - Returns a boolean value indicating if a key is present in the hash table
*   Input:
*     tbl - Smart pointer of object type "hash_table" that represents the hash table that we are searching in
*     key - String value that represents the key value of the hash node that we are looking for
*   Algorithm:
*     * Calculate the hash code and bucket index of the given key
*     * Create a dummy variable for the number of buckets that have been probed
*     * Traverse the table until the number of buckets probed equals that of the tables size
*     * Check to see if the current nodes key value matches that of the input parameter "key"
*       * If it does, return true
*     * Otherwise, increment both buckets probed and bucket index
*     * Return false if the key is not present in the table
*   Output:
*     This function returns a boolean value indicating a keys value if it is present in the hash table
*/
bool Hash::Contains(shared_ptr<hash_table> tbl, std::string key){
  // Calculate the hash code and bucket index of the given key
  unsigned int hash = DJB2(key);
  unsigned int bucket_idx = tbl->bucket_func(hash, tbl->capacity);
  // Create a dummy variable to indicate the buckets that have been probed in the table
  unsigned int buckets_probed = 0;
  // Traverse the table until buckets probed reaches the size of the table
  while (buckets_probed < tbl->size) {
    // If the current nodes key data member matches that of the input parameter "key", return true
    if (tbl->table->at(bucket_idx)->key == key) {
      return true;
    }
    // Increment the bucket index and buckets probed values
    bucket_idx = (bucket_idx + 1) % tbl->size;
    buckets_probed++;
  }
  // Return false if nothing was found
  return false;
}

/*  Remove - Removes a hash node from a hash table if it is present in the table
*   Input:
*     tbl - Smart pointer of object type "hash_table" that represents the hash table that we are searching in
*     key - String value that represents the key value of the hash node that we are looking for
*   Algorithm:
*     * Calculate the hash code and bucket index of the given key
*     * Create a dummy variable for the number of buckets that have been probed
*     * Traverse the table until the number of buckets probed equals that of the tables size
*     * Check to see if the current nodes key value matches that of the input parameter "key"
*       * If it does, delete the node and return true
*     * Otherwise, increment both buckets probed and bucket index
*     * Return false if the key is not present in the table
*   Output:
*     This function returns a boolean value indicating if a hash node has been removed from a hash table
*/
bool Hash::Remove(shared_ptr<hash_table> tbl, std::string key){
  // Calculate the hash code and bucket index of the given key
  unsigned int hash = DJB2(key);
  unsigned int bucket_idx = tbl->bucket_func(hash, tbl->capacity);
  // Create a dummy variable to indicate the buckets that have been probed in the table
  unsigned int buckets_probed = 0;
  // Traverse the table until buckets probed reaches the size of the table
  while (buckets_probed < tbl->size) {
    // If the current nodes key data member matches that of the input parameter "key", remove the node from the table and return true
    if (tbl->table->at(bucket_idx) != nullptr && tbl->table->at(bucket_idx)->key == key) {
      tbl->table->at(bucket_idx)->deleted = true;
      tbl->size--;
      return true;
    }
    // Increment the bucket index and buckets probed values
    bucket_idx = (bucket_idx + 1) % tbl->size;
    buckets_probed++;
  }
  // Return false if nothing was found
  return false;
}

/*  Resize - Resizes the capacity of a hash table
*   Input:
*     tbl - Smart pointer of object type "hash_table" that is passed by reference that is to be resized
*     new_capacity - Unsigned integer value that represents the new capacity of the table
*   Algorithm:
*     * Create a new hash table with the new capacity
*     * Copy the size and occupied data members of the old table to the new one
*     * Copy the hash nodes of the old table to the new table
*     * Update the old table to be the new table
*   Output:
*     This function does not return a value, it updates the old table with the new tables parameters
*/
void Hash::Resize(shared_ptr<hash_table>& tbl, unsigned int new_capacity){
  // Create a new table that is going to be used to update the old table
  shared_ptr<hash_table> new_table = InitTable(new_capacity);
  // Copy the size and occupied data members of the old table to the new one
  new_table->size = tbl->size;
  new_table->occupied = tbl->occupied;
  // Copy the hash nodes of the old table to the new table
  for (int i = 0; i < tbl->table->size(); i++) {
    if (tbl->table->at(i) != nullptr) {
      // Calculate the hash code and bucket index of the current node for the new table
      unsigned int hash = DJB2(tbl->table->at(i)->key);
      unsigned int bucket_idx = new_table->bucket_func(hash, new_table->capacity);
      new_table->table->at(bucket_idx) = tbl->table->at(i);
    }
  }
  // Update the old table to be the new table
  tbl = new_table;
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

