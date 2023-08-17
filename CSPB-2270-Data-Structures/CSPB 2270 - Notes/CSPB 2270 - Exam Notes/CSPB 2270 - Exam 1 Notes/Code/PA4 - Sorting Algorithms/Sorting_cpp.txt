#include "Sorting.h"

/*
  Please refer to sorting.h for documentation on each function.

   + ------ N O T E: -- Big scary warning! -----------------------------\
   |                                                                    |
   |    We clearly can't use unit testing to ensure that you're         |
   |    actually implementing the correct algorithm. I suppose we could |
   |    write some complicated static analysis checker. But it is       |
   |    easier to just look at it with our eyeballs.                    |
   |                                                                    |
   |    After the assignment is due, we will look at the most recent    |
   |    version of your implementation that got the highest score and   |
   |    make sure you're not doing something sneaky like using a        |
   |    standard library call to sort a vector.                         |
   |                                                                    |
   |    Anyone caught doing this (even though it is kinda funny) will   |
   |    be given 0 points on the assignment.                            |
   |                                                                    |
   `--------------------------------------------------------------------/ 
*/

// constructor, initialize class variables and pointers here if you need.
Sorting::Sorting(){
  // Your code here
}

//deconstructor,
Sorting::~Sorting(){
}

/*  quicksort - Algorithm that sorts elements in a vector for a given low and high index
*   Input:
*     data - Vector of integers passed by reference that are to be sorted
*     low_idx - Integer value that represents the lower index of the vector that is to be sorted
*     high_idx - Integer value that represents the higher index of the vector that is to be sorted
*   Algorithm:
*     * If the lower index is greater than or equal to that of the higher index, then stop execution
*     * Otherwise, find the pivot point with "quicksort_partition" and assign this as the upper index of the lower partition
*     * Recursively call the algorithm to sort the lower end of the partitioned vector
*     * Recursively call the algorithm to sort the higher end of the partitioned vector
*   Output:
*     This function does not return a value, it modifies the "data" vector
*/
void Sorting::quicksort(vector<int>& data, int low_idx, int high_idx){
  // Check to see if the lower index is greater than or equal to that of higher index
  if (low_idx >= high_idx) {
    return;
  }
  else {
    // Determine the pivot point of the current vector
    int low_end_idx = quicksort_partition(data, low_idx, high_idx);
    // Recursively sort the lower half of the vector
    quicksort(data, low_idx, low_end_idx);
    // Recursively sort the higher half of the vector
    quicksort(data, low_end_idx + 1, high_idx);
  }
}

/*  quicksort_partition - Determines the pivot point inside a given vector and returns the updated highest index value
*   Input:
*     data - Vector of integers that is passed by reference where the pivot index is being found
*     low_idx - Integer value that represents the lower index of the vector for where we will search through
*     high_idx - Integer value that represents the higher index of the vector for where we will search through
*   Algorithm:
*     * Find the middle index of "data" and assign it to "mid_idx"
*     * Find the pivot value by looking at the value in the "data" vector at the middle index "mid_idx"
*     * Traverse through the vector by incrementing "low_idx" until a value is greater than or equal to that of the pivot
*     * Traverse through the vector by decrementing "high_idx" until a value is less than or equal to that of the pivot
*     * If the lower index value "low_idx" is greater than or equal to that of the higher index "high_idx", then we exit the
*       while loop
*     * If the lower index is less than the higher index, then we do the following:
*       * Create a temporary integer "temp_val" for the value in "data" at the "low_idx" element location
*       * Swap the value that is found on the left side of the pivot with the value that is on the right side of the pivot
*       * Assign the value "temp_val" to that of the value at "high_idx" in the "data" array
*       * Increment the lower index by one and decrement the higher index by one
*   Output:
*     high_idx - Integer value that represents the updated higher index value of our vector that we are searching through
*/
int Sorting::quicksort_partition(vector<int>& data, int low_idx, int high_idx){
  // Define variables to track elements in the "data" vector
  int mid_idx = low_idx + (high_idx - low_idx) / 2;
  int pivot = data.at(mid_idx);
  bool finished = false;
  // Begin traversing through the vector
  while (!finished) {
    // Increment lower index until value greater than or equal to that of the pivot is found
    while (data.at(low_idx) < pivot) {
      low_idx += 1;
    }
    // Dectrement hihger index until value less than or equal to that of the pivot is found
    while (pivot < data.at(high_idx)) {
      high_idx -= 1;
    }
    // If no elements remain, then exit the loop
    if (low_idx >= high_idx) {
      finished = true;
    }
    // Begin the process of swapping values
    else {
      // Keep track of the current value at the lower index
      int temp_val = data.at(low_idx);
      // Swap the values of lower and higher indexes
      data.at(low_idx) = data.at(high_idx);
      data.at(high_idx) = temp_val;
      // Increment and decrement index values
      low_idx += 1;
      high_idx -= 1;
    }
  }
  return high_idx;
}

/*  bubblesort - Algorithm that sorts elements utilizing the bubble sort algorithm
*   Input:
*     data - Vector of integers that is passed by reference that is to be sorted
*   Algorithm:
*     * Begin by iterating through the vector "data"
*     * Compare adjacent elements of the vector at the current index
*     * Check to see if the next element in the vector is greater than that of the current element
*       * If it is, swap them, otherwise, move on to the next element
*   Output:
*     This function does not return a value, it sorts the elements in "data" using a bubble sort algorithm
*/
void Sorting::bubblesort(vector<int>& data){
  // Iterate through the vector "data"
  for (int i = 0; i < data.size() - 1; i++) {
    // Compare adjacent elements in the vector
    for (int j = 0; j < data.size() - i - 1; j++) {
      // Check to see if next element in vector is greater than that of the current element
      if (data.at(j) > data.at(j+1)) {
        // Create a temporary integer value for that of the current element
        int temp_val = data.at(j);
        // Assign the current element with that of the next element
        data.at(j) = data.at(j+1);
        // Assign the next element with that of the current element
        data.at(j+1) = temp_val;
      }
      else {}
    }
  }
}

/*  mergesort - Uses the merge sort algorithm to sort elements in a vector
*   Input:
*     data - Vector of integers that is passed by reference that is going to be sorted
*   Algorithm:
*     * First check to see if the vector is empty or has one element
*     * Proceed to calculate the mid point of the vector
*     * Create a vector for the left and right half
*     * Recursively call the mergesort method on the left and right halves of the vector
*     * Merge the two vectors into one by copying the results to data
*   Output:
*     This function does not return a value, it sorts elements from a vector
*/
void Sorting::mergesort(vector<int>& data){
  // The vector is empty or only has one element
  if (data.size() <= 1) {
    return;
  }
  // The vector is greater than 1
  else {
    // Calculate the midpoint of the vector
    int midPoint = data.size() / 2;
    // Create a left half of the vector
    vector<int> leftHalf(data.begin(), data.begin() + midPoint);
    // Create a right half of the vector
    vector<int> rightHalf(data.begin() + midPoint, data.end());
    // Merge the left and right half of the vector, recursively
    mergesort(leftHalf);
    mergesort(rightHalf);
    // Create an empty vector
    vector<int> result;
    // Call the merge method and merge the two halves together
    merge(leftHalf, rightHalf, result);
    // Copy the results to data
    data = result;
  }
}

/*  merge - Merges two vectors into one final vector
*   Input:
*     left - Vector of integers that is passed by reference that is to be inserted into the result vector
*     right - Vector of integers that is passed by reference that is to be inserted into the result vector
*     result - Vector of integers that is passed by reference 
*   Algorithm:
*     * Begin by calculating the size that is needed for the merged vector
*     * Set the positions of each vector that is going to be traversed through
*     * Create a temporary vector that will hold the merged values
*     * Iterate through the elements in the left and right vectors, copy the values into the mergedNumbers vector
*     * Increment the merge position
*     * Merge the left and right vectors into the mergedNumbers vector
*     * Copy the elements from the mergedNumbers vector into the result vector
*   Output:
*     This function does not return a value, it merges two vectors into one, called result
*/
void Sorting::merge(vector<int>& left, vector<int>& right, vector<int>& result) {
  // Calculate the size of the needed vector for the merged vector
  int mergedSize = left.size() + right.size();
  // Set the positions of each vector
  int mergePos = 0;
  int leftPos = 0;
  int rightPos = 0;
  // Create a temporary vector that will hold the merged values
  vector<int> mergedNumbers(mergedSize);
  // Continue while loop as long as there are elements left in each vector to be merged
  while (leftPos < left.size() && rightPos < right.size()) {
    // Insert the element in the left vector into the merged vector if it is less than that of the right vector
    if (left.at(leftPos) <= right.at(rightPos)) {
      mergedNumbers.at(mergePos) = left.at(leftPos);
      ++leftPos;
    }
    // Insert the element in the right vector into the merged vector if it is greater than that of the left vector
    else {
      mergedNumbers.at(mergePos) = right.at(rightPos);
      ++rightPos;
    }
    // Increment the merge position
    ++mergePos;
  }
  // Merge the left vector into the mergedNumbers vector
  while (leftPos < left.size()) {
    mergedNumbers.at(mergePos) = left.at(leftPos);
    ++leftPos;
    ++mergePos;
  }
  // Merge the right vector into the mergedNumbers vector
  while (rightPos < right.size()) {
    mergedNumbers.at(mergePos) = right.at(rightPos);
    ++rightPos;
    ++mergePos;
  }
  // Copy the elements from the mergedNumbers vector into the result vector
  for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
    result.push_back(mergedNumbers.at(mergePos));
  }
}

/*  mystery_sort - This function utilizes the selection sort algorithm to sort elements in a vectors
*   Input:
*     data - Vector of integers that is passed by reference that is to be sorted
*   Algorithm:
*     * Create values that keep track of the smallest values index and a temporary value
*     * Begin iterating through the vector
*     * Set the smallest value index to the current index
*     * Iterate through the rest of the vector to see if there is a smaller value in the vector
*     * Change the smallest index to the current index if the condition is satisfied
*     * Update the temporary value with that of the current indexes value
*     * Swap the values of the current index with that of the smallest value index
*   Output:
*     This function does not return a value, it updates a vector by sorting it's elements
*/
void Sorting::mystery_sort(vector<int>& data){
  // Create values to track the smallest value and a temp value
  int smallestIndex = 0;
  int tempVal = 0;
  // Begin iterating through the elements in the vector
  for (int i = 0; i < data.size(); ++i) {
    // Set the smallest value to the current index
    smallestIndex = i;
    // Compare the elements that come after the current index
    for (int j = i + 1; j < data.size(); ++j) {
      // Iterate through the rest of the vector
      if (data.at(j) < data.at(smallestIndex)) {
        // Change the smallest index to the current index
        smallestIndex = j;
      }
      // Otherwise, keep iterating through the vector
      else {}
    }
    // Update the temporary value to the current value in data
    tempVal = data.at(i);
    // Swap the values of the current index with the smallest index
    data.at(i) = data.at(smallestIndex);
    data.at(smallestIndex) = tempVal;
  }
}