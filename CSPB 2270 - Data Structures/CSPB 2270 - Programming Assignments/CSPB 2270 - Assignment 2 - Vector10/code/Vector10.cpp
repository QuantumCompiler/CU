#include "Vector10.h"
#include <iostream>

/*
*   Source used: https://www.w3schools.com/cpp/cpp_arrays_size.asp
*   The for loop then sets all elements of the array to zero for the size of the array, hence all elements are now set to zero :)
*   The "arr_size" variable is the size of array as an integer value
*   This is a constructor for our function so it doesn't need to return any values
*/
Vector10::Vector10(){
    arr_add = 0;
    for (int i = 0; i < arr_size; i++) {
        arr[i] = 0; // Set every element of arr to zero
    }
}

/*
*   No code needed
*/
Vector10::~Vector10(){}

/*
*   This function will return the value of our array for a given index
*   This function will first check if the index that is being bassed is greater than or equal to zero and less than our array size
*       This is necessary because we require that a positive index be passed and that we can access a spot in the array that is not out of bounds
*   If the index is out of bounds, it will return 0. If it is in bounds, it will return the value of that array at the given index
*/
int Vector10::ValueAt(int index) const {
    if (index >= 0 && index < arr_size) {
        return arr[index];
    }
    else {
        return 0;
    }
}

/*
*   This function attempts to check if the value that is being passed in as a parameter can be put into the array "arr"
*   The "arr_add" variable is an integer value that counts how many elements have been added to the array
*   If the number of elements that have been added to the array is greater than or equal to the size of the array, the function returns false
*       This is the stipulation that disallows a user to add an element to the array if it is already full
*       If the above condition is met, then the function will return false
*   If "arr_add" is less than 10, then we can proceed to add the parameter "value" to the array
*       If the above condition is met, then the function will add the value to the "arr_add" index of the array
*       The function will then also return true
*/
bool Vector10::PushBack(int value){
    if (arr_add >= arr_size) {
        return false;
    }
    else if (arr_add < 10) {
        arr[arr_add] = value;
        arr_add++;
        return true;
    }
    else { return false; }
}

/*
*   This function counts how many empty values are currently in our array "arr"
*   It begins by initializing the integer value "empty_values" to zero
*   We then use a for loop to iterate through each index of the array to see if the current index is equal to zero
*       If that current index is indeed zero, then the parameter "empty_values" is incremented by one
*   The function then returns the "empty_values" parameter after running through the entire array
*/
int Vector10::CountEmpty(){
    int empty_values = 0;
    for (int i = 0; i < arr_size; i++) {
        if (arr[i] == 0){
            empty_values++;
        }
        else {}
    }
    return empty_values;
}

/*
*   This function searches for a given value in an array
*   The parameter "value" is the integer value that we are searching for in our array
*   The function initializes the return boolean value "result" to be false
*   We then enter a for loop where we begin searching for our given value in our array
*       If the value exists in our array, we change "result" to true and return "result"
*       If the value does not exist in our array, "result" is not changed but is still set to false
*       If the number is not found in the array, then we will return "result" set to false
*/
bool Vector10::Search(int value){
    bool result = false;
    for (int i = 0; i < arr_size; i++) {
        if (arr[i] == value) {
            result = true;
            return result;
        }
        else if (arr[i] != value) {
            result = false;
        }
        else {}
    }
    return result;
}

/*
*   This function removes a value at a given index
*   We first check to see if the index is in the bounds of the array, in our case "arr"
*       If the index that is fed into the function is greater than or equal to zero as well as in the range of the array
*       we shift the elements of the array that proceed the given index one value to the left of the given index
*       The function then returns a value of true, indicating that the value was removed from the array
*   If index is out of bounds or it is less than zero, then the function returns false indicating that it wasn't able to 
*   remove the element from the array because it does not exist in the array "arr"
*/
bool Vector10::Remove(int index){
    bool result = false;
    if (index >= 0 && index < arr_size){
        for (int i = index; i < arr_size; i++){
            arr[i] = arr[i+1];
        }
        return true;
    }
    else { result = false; }
    return result;
}

/*
*   This function prints the elements of an array using a range based for loop for brevity's sake
*/
void Vector10::PrintArr() const {
    std::cout << std::endl;
    for (int i : arr) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}