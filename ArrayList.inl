//
// Created by Taylor Yowan on 10/10/17.
//
#include <stdexcept>
#include <string>
#include <iostream>
#include "ArrayList.h"
#include "ArrayLib.h"





/**
 * replaces the old array with an array twice the size
 * private method only called within ArrayList when necessary
 * @post: array points to a new array of twice the size with values copied from the old one,
 *        the old array is deleted.
 */
template <class T>
void ArrayList::doubleCapacity(){
    int doubCap = (currCapacity * 2);
    currCapacity = doubCap;
    int timer = 0;
    int* tempArray = copyArray(array, doubCap);
    delete[] array;
    array = tempArray;
    tempArray = nullptr;
}


/**
 * Constructor
 * creates an arrayList
 * @param: initialCapacity (the starting size of the array, defaults to size 5
 */
template <class T>
ArrayList::ArrayList(int initialCapacity){
    this -> currCapacity = initialCapacity;
    array = new int[currCapacity];
    currItemCount = 0;
}

//Copy Constructor
template <class T>
ArrayList::ArrayList(const ArrayList& arrayListToCopy){
    currItemCount = arrayListToCopy.currItemCount;
    currCapacity = arrayListToCopy.currCapacity;
    array = new int[currCapacity];
    for(int i = 0; i < currItemCount; i ++ ){
        array[i] = arrayListToCopy.array[i];
    }
}

//Overloaded Assignment Operator
template <class T>
ArrayList& ArrayList::operator=(const ArrayList& arrayListToCopy){
    if(this != &arrayListToCopy){
        delete[] array;
    }
    currCapacity = arrayListToCopy.currCapacity;
    currItemCount = arrayListToCopy.currItemCount;
    for(int i = 0; i < currItemCount; i++){
        array[i] = arrayListToCopy.array[i];
    }
    return *this;
}

//Destructor
template <class T>
ArrayList::~ArrayList(){
    delete[] array;
}

/**
 * appends the new item to the end of the list
 * @param itemToAdd the item to add to the end of the array
 * @post the list has an additional value in it, at the end
 */
template <class T>
void ArrayList::addToList(T* itemToAdd) {
    if (currItemCount < currCapacity) {
        array[currItemCount] = itemToAdd;
    } else {
        doubleCapacity();
        array[currItemCount] = itemToAdd;
    }
    currItemCount++;
}





/**
 * gets a value from the list
 * @param index the location from which to get the value
 * @returns a copy of the item at index
 * @throws out_of_range exception if index is invalid
 */
int ArrayList::getValueAt(T index){
    if(index < 0){
        throw std::out_of_range("<index not in range>");
    }
    else if(index > currItemCount){
        throw std::out_of_range("<index not in range>");
    }
    else{
        return array[index];
    }
}

/**
 * removes the item at index from the list, and returns a copy of that item
 * @param index the location from which to get the value
 * @post the item at index is removed from the list, everything else is shifted down one
 * @returns a copy of the item at index
 * @throws out_of_range exception if index is invalid
 */
template <class T>
int ArrayList::removeValueAt(T index){
    if(index < 0){
        throw std::out_of_range("<index not in range>");
    }
    else if(index > currItemCount){
        throw std::out_of_range("<index not in range>");
    }
    int in = array[index];
    if(index <= currItemCount){
        if(currItemCount <= currCapacity){
            for(int i = index; i < currItemCount; i++){
                array[i] = array[i+1];
            }
            currItemCount--;
        }
    }
    return in;
}

/**
 * checks if there are any valid items in the list
 * @returns true if there are no valid items in the list, false otherwise
 */
template <class T>
bool ArrayList::isEmpty(){
    if(currItemCount == 0){
        return true;
    }
    else{
        return false;
    }
}

/**
 * returns a count of valid items currently in the list
 * @returns the number of valid items in the list
 */
template <class T>
int ArrayList::itemCount(){
    return currItemCount;
}

/**
 * removes all valid items from the list
 * @post the list is completely clear of valid items
 */
template <class T>
void ArrayList::clearList(){
    for(int i = 0; i < currItemCount; i++){
        array[i] = 0;
    }
    currItemCount = 0;
}

/**
 * gives a string representation of the current list
 * @returns a string representing the given list in the exact format shown below
 * {1, 2, 3, 4, 5}
 */
template <class T>
std::string ArrayList::toString(){
    return toString(array, currItemCount);
}

/*
 * Searches an int array for a certain value
 * @post numLinesRun is updated to include lines run by this function
 * @return the index of the first occurrence of numToFind if it is present, otherwise returns -1
 */
template <class T>
int ArrayList::find(int id){
    int timer = 0;
    return find(array,currItemCount, numToFind,timer);
}

/**
 * Searches an int array for a certain value
 * @post numLinesRun is updated to include lines run by this function
 * @return the index of the last occurrence of numToFind if it is present, otherwise returns -1
 */
template <class T>
int ArrayList::findLast(int numToFind){
    int timer = 0;
    return findLast(array,currItemCount,numToFind,timer);
}