// ----- ----- ----- ----- ----- ----- ----- Includes ----- ----- ----- ----- ----- ----- ----- ----- ----- //
#include "../Headers/BloomFilter.h"

/*  BloomFilter - Bloom filter constructor
*   Input:
*       bitSize - Integer value that represents the number of bits in the bloom filter
*       numHashIterations - Integer value that represents the number of hash function iterations for calculating a hash value
*   Algorithm:
*       * Allocate the "filter" structure on the heap
*       * Assign default values to data members of the aforementioned filter
*/
BloomFilter::BloomFilter(int bitSize, int numHashIterations) {
    // Allocate "bloomFilter" structure on the heap
    this->bloomFilter = std::make_shared<Filter>();
    // Assign default values to data members of "bloomFilter"
    this->bloomFilter->bucketIndex = 0;
    this->bloomFilter->bucketVal = 0;
    this->bloomFilter->filter.resize(bitSize, false);
    this->bloomFilter->hashCode = 0;
    this->bloomFilter->hashFunctionIterations = numHashIterations;
}

// ~BloomFilter - Bloom filter deconstructor
BloomFilter::~BloomFilter() {}

/*  AddToFilter - Adds element to bloom filter
*   Input:
*       input - Constant string value that is passed by reference to represent the element that will be added to a filter
*   Algorithm:
*       * Calculate the hash code of the input parameter
*       * Calculate the bucket of the given input parameter
*       * Add the element to the container of the filter
*   Output:
*       This function does not return a value, it adds an element to the container in the bloom filter
*/
void BloomFilter::AddToFilter(const std::string& input) {
    // Calculate hash code and bucket index of input value
    this->SetHashCode(input);
    this->SetBucketVal(this->GetHashFuncIterations());
    for (int i = 1; i <= this->GetBucketVal(); i++) {
        this->SetBucket(i * this->GetHashCode());
        this->SetFilter(this->GetBucket());
    }
}

/*  CalculateBucketIndex - Calculates the bucket index for a given input parameter
*   Input:
*       input - Constant non-negative integer that is passed by reference that represents a hash code
*   Algorithm
*       * Calculate the bucket value with the modulus of the size of the container in the filter
*   Output:
*       bucketVal - Non-negative integer that represents the bucket index of the corresponding hash code
*/
unsigned int BloomFilter::CalculateBucketIndex(const unsigned int& input) {
    // Calculate the modulus of the input parameter with the size of the container in the filter
    unsigned int bucketVal = input % this->GetFilter().size();
    return bucketVal;
}

/*  CalculateHashCode - Calculates the hash code of a given input string
*   Input:
*       input - Constant string value that is passed by reference that represents the object being inserted into the filter
*   Algorithm:
*       * Create necessary hash objects for types "string" and "unsigned int"
*       * Update the hash code "finalHashVal" for a given number of iterations retrieved with "GetHashFuncIterations"
*       * Calculate "firstHash" and "secondHash" inside the for loop
*       * Return the hash value after the for loop
*   Output:
*       finalHashVal - Non-negative integer value that represents the hash code of a string value
*/
unsigned int BloomFilter::CalculateHashCode(const std::string& input) {
    // Create a hash object of object type "string"
    std::hash<std::string> stringHash;
    // Create a hash object of object type "unsigned int"
    std::hash<unsigned int> longHash;
    // Create a value for the final hash value 
    unsigned int finalHashVal = 0;
    // Add to "finalHashVal" with the hashed values of "firstHash" and "secondHash"
    unsigned int firstHash = stringHash(input);
    unsigned int secondHash;
    for (int i = 0; i < this->GetHashFuncIterations(); ++i) {
        // Calculate "firstHash" and "secondHash"
        secondHash = longHash(i * firstHash);
        finalHashVal += (firstHash + i * secondHash);
    }
    // Return the final hash value
    return finalHashVal;
}

/*  ClearFilter - Clears the container of a filter
*   Input:
*       This function does not have any input parameters
*   Algorithm:
*       * Reset all values of "filter" to false
*   Output:
*       This function does not return a value, it resets the data member "filter" so that all its elements are false
*/
void BloomFilter::ClearFilter() {
    std::fill(this->bloomFilter->filter.begin(), this->bloomFilter->filter.end(), false);
}

/*  Contains - Checks if a specific element is present inside a bloom filter
*   Input:
*       input - Constant string value that is passed by reference that represents the element that is being searched for
*   Algorithm:
*       * Calculate the hash code and bucket index of "input"
*       * Return the boolean value of that element in the container of the filter
*   Output:
*       This function returns a boolean value that represents if an element is present in a filter
*/
bool BloomFilter::Contains(const std::string& input) {
    // Calculate the hash code and bucket index of "input"
    unsigned int tempHash = this->CalculateHashCode(input);
    this->SetBucketVal(this->GetHashFuncIterations());
    unsigned int tempBucket;
    for (int i = 1; i <= this->GetBucketVal(); i++) {
        tempBucket = this->CalculateBucketIndex(i * tempHash);
        if (this->GetFilter()[tempBucket]) {
            return true;
        }
        else {
            continue;
        }
    }
    return false;
}

/*  RemoveElement - "Removes" an element from a filter
*   Input:
*       input - Constant string value that is passed by reference that represents the element that is to be removed from a filter
*   Algorithm:
*       * Calculate the hash code and bucket index of "input"
*       * Change the elements boolean value to false
*   Output:
*       This function does not return a value, it sets a specific index of the filter to be false for a given input
*/
void BloomFilter::RemoveElement(const std::string& input) {
    // Calculate the hash code and bucket index of "input"
    unsigned int tempHash = this->CalculateHashCode(input);
    this->SetBucketVal(this->GetHashFuncIterations());
    unsigned int tempBucket;
    for (int i = 1; i <= this->GetBucketVal(); i++) {
        tempBucket = this->CalculateBucketIndex(i * tempHash);
        this->GetFilter()[tempBucket] = false;
    }
}

// ----- ----- ----- ----- ----- ----- ----- Mutators ----- ----- ----- ----- ----- ----- ----- ----- ----- //
// GetBucket - Retrieves the private data member "bucketIndex"
unsigned int& BloomFilter::GetBucket() {
    return this->bloomFilter->bucketIndex;
}

// GetBucketVal - Retrieves the private data member "bucketVal"
unsigned int& BloomFilter::GetBucketVal() {
    return this->bloomFilter->bucketVal;
}

// GetFilter - Retrieves the private data member "filter"
std::vector<bool>& BloomFilter::GetFilter() {
    return this->bloomFilter->filter;
}

// GetHashCode - Retrieves the private data member "hashCode"
unsigned int& BloomFilter::GetHashCode() {
    return this->bloomFilter->hashCode;
}

// GetHashFuncIterations - Retrieves the private data member "hashFunctionIterations"
unsigned int& BloomFilter::GetHashFuncIterations() {
    return this->bloomFilter->hashFunctionIterations;
}

// SetBucket - Mutates the private data member "bucketIndex" to that of "input"
void BloomFilter::SetBucket(const unsigned int& input) {
    this->bloomFilter->bucketIndex = this->CalculateBucketIndex(input);
}

// SetBucketVal - Mutates the private data member "bucketVal" to that of "input"
void BloomFilter::SetBucketVal(const unsigned int& input) {
    this->bloomFilter->bucketVal = input % 5;
}

// SetFilter - Mutates the private data member "filter" to that of "input"
void BloomFilter::SetFilter(const unsigned int& input) {
    this->bloomFilter->filter[input] = true;
}

// SetHashCode - Mutates the private data member "hashCode" to that of "input"
void BloomFilter::SetHashCode(const std::string& input) {
    this->bloomFilter->hashCode = this->CalculateHashCode(input);
}

// SetNumHashFunctions - Mutates the private data member "hashFunctionIterations" to that of "input"
void BloomFilter::SetNumHashFunctions(const unsigned int& input) {
    this->bloomFilter->hashFunctionIterations = input;
}