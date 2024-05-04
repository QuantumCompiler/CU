// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H
#include "Includes.h"

// ----- ----- ----- ----- ----- ----- ----- References ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// https://www.geeksforgeeks.org/stdhash-class-in-c-stl/
// https://cplusplus.com/reference/functional/hash/
// https://en.cppreference.com/w/cpp/utility/hash

/*  Structure Filter - Filter elements for a bloom filter
*   Data Members:
*       bucketIndex - Non negative integer value that represents the bucket index of an element in the bloom filter
*       bucketVal - Non negative integer value that represents the number of buckets a value will be inserted into a bloom filter
*       filter - Vector of boolean values where hashed elements are stored in a bloom filter
*       hashCode - Non negative integer value that represents the container for the bloom filter
*       hashFunctionIterations - Non negative integer value that represents the number of iterations for creating a hash code
*/
struct Filter {
    unsigned int bucketIndex; // Bucket index for a given hash code
    unsigned int bucketVal; // Number of buckets for a given value in a bloom filter
    std::vector<bool> filter; // Vector of boolean values to represent a filter
    unsigned int hashCode; // Final hash value for a given string
    unsigned int hashFunctionIterations; // Number of hash functions used to create a final hash value
};

// Bloom filter class
class BloomFilter {
public:
    // ---- ---- ---- Constructors ---- ---- ---- //
    BloomFilter(int bitSize, int numHashIterations); // Constructor
    ~BloomFilter(); // De-Constructor
    // ---- ---- ---- Member Functions ---- ---- ---- //
    void AddToFilter(const std::string& input); // Add element to filter
    unsigned int CalculateBucketIndex(const unsigned int& input); // Calculates the bucket index of a hash code
    unsigned int CalculateHashCode(const std::string& input); // Calculates the hash code for the filter
    void ClearFilter(); // Clear filter
    bool Contains(const std::string& input); // Check if element exists in filter
    void RemoveElement(const std::string& input); // Removes an element from the filter
    // ---- ---- ---- Mutator Functions ---- ---- ---- //
    // Getter functions
    unsigned int& GetBucket(); // Retrieves "bucketIndex"
    unsigned int& GetBucketVal(); // Retrieves "bucketVal"
    std::vector<bool>& GetFilter(); // Retrieves "filter"
    unsigned int& GetHashCode(); // Retrieves "finalHash"
    unsigned int& GetHashFuncIterations(); // Retrieves "hashFunctionIterations"
    // Setter functions
    void SetBucket(const unsigned int& input); // Mutates "bucketIndex"
    void SetBucketVal(const unsigned int& input); // Mutates "bucketVal"
    void SetFilter(const unsigned int& input); // Mutates "filter"
    void SetHashCode(const std::string& input); // Mutates "hashCode"
    void SetNumHashFunctions(const unsigned int& input); // Mutates "hashFunctionIterations"
private:
    std::shared_ptr<Filter> bloomFilter; // Filter struct
};

#endif