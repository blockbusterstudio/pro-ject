
#include <stdexcept>
#include <string>
#include <iostream>
#include "Task.h"
#include "ArrayList.h"


/**
 * Constructor
 * creates an arrayList
 * @param: initialCapacity (the starting size of the array, defaults to size 5
 */
ArrayList::ArrayList(int initialCapacity){
    this -> currCapacity = initialCapacity;
    array = new Task*[currCapacity];
    currItemCount = 0;
}

////Copy Constructor
//ArrayList::ArrayList(const ArrayList& arrayListToCopy){
//    currItemCount = arrayListToCopy.currItemCount;
//    currCapacity = arrayListToCopy.currCapacity;
//    array = new Task*[currCapacity];
//    for(int i = 0; i < currItemCount; i++){
//        array[i] = arrayListToCopy.array[i];
//    }
//}

////Overloaded Assignment Operator
//ArrayList& operator=(const ArrayList& arrayListToCopy){
//    if( this != &arrayListToCopy){
//        delete[] array;
//    }
//    currCapacity = arrayListToCopy.currCapacity;
//    currItemCount = arrayListToCopy.currItemCount;
//    for(int i = 0; i < currItemCount; i++){
//        array[i] = arrayListToCopy.array[i];
//        }
//    return *this;
//}


//Destructor
ArrayList::~ArrayList(){
    delete[] array;
}


/**
 * replaces the old array with an array twice the size
 * private method only called within ArrayList when necessary
 * @post: array points to a new array of twice the size with values copied from the old one,
 *        the old array is deleted.
 */
void ArrayList::doubleCapacity(){
    int doubCap = (currCapacity * 2);
    currCapacity = doubCap;
    Task** tempArray = copyArray(tempArray,doubCap);
    delete[] array;
    array = tempArray;
    tempArray = nullptr;
}


/**
* adds Task to the list
* @param taskToAdd - pointer to the Task to be added to the List
* @post the List has an additional Task in it, Ordered by Priority (highest to lowest priority)
*/
void ArrayList::addToList(Task* taskToAdd){
    if(array[0] == nullptr){
        insertAtFront(taskToAdd);
    }
    else{
        Task* index = array[0];
        int searchPriority = taskToAdd->getPriority();
        for(int i = 0; i < currItemCount; i++){
            if(searchPriority < index->getPriority()){
                insertAt(taskToAdd,i);
            }
            else if(searchPriority > index->getPriority()){
                insertAtEnd(taskToAdd);
            }
        }
    }
}

/**
 * Extends the end of the List to point at taskToAdd
 * @param taskToAdd - pointer to the Task to be added to the List
 * @post the list has an additional Task in it, at the end

 */
void ArrayList::insertAtEnd(Task* taskToAdd){
    if(currItemCount < currCapacity){
        array[currItemCount] = taskToAdd;
    } else{
        this->doubleCapacity();
        array[currItemCount] = taskToAdd;
    }
    currItemCount++;
}

/**
 * Shifts all Tasks down the List and adds pointer to Task at front
 * @param taskToAdd - pointer to the Task to be added to the List
 * @post the list has an additional Task in it
 */
 void ArrayList::insertAtFront(Task* tasktoAdd){
    if(currItemCount == currCapacity){
        this->doubleCapacity();
    }
    for (int i = currItemCount; i >0; i--){
        array[i] = array[i-1];
    }
    array[0] = tasktoAdd;
    currItemCount++;
}

/**
 * adds Task to the list, at index specified
 * @param taskToAdd - pointer to the Task to be added to the List
 * @param index - the index in the List to add the task, everything after it gets shifted down
 * @post the list has an additional Task in it
 */
 void ArrayList::insertAt(Task* taskToAdd, int index){
    if(index < 0 ){
        throw std::out_of_range("<Error:index not in range>");
    }
    else if (index > currItemCount){
        throw std::out_of_range("<Error:index not in range>");
    }
    else{
        for(int i = currItemCount; i > index; i--){
            array[i] = array[i - 1];
        }
        array[index] = taskToAdd;
        currItemCount++;
    }
}

//    /**
//      * Searches a List for a passed id, returns a pointer to the task with that Id
//      * @returns pointer to the first occurrence of a task with specified id if it is present, otherwise throws Bad_Task_Id error
//      */
//    virtual Task* findTaskById(int id)=0;
//
//    /**
//     * Searches an list for a certain id
//     * @returns pointer to the last occurrence of a task with specified id if it is present, otherwise throws Bad_Task_Id error
//     */
//    virtual Task* findLastTaskById(int id)=0;
//    //todo do we need a findLast or find function? probably good idea to have them just to beable to scan through the id's of the tasks in a list

/**
 * returns the id of the first Task with the passed Priority
 * @param lookFor - the priority to look for
 * @return the id of the first Task in the list with the passed priority
 */
int ArrayList::findFirstPriority(int lookFor){
    for(int i = 0; i < currItemCount; i++){
        if(array[i]->getPriority() == lookFor){
            return i;
        }
    }
    return -1;
}

/**
 * returns the id of the last Task with the passed priority
 //TODO the controller should call this function more often with +1 priority when looking to add a Task.
 * @param lookFor - the priority to look for
 * @return the id of the last Task in the list with the passed priority.
 */
 int ArrayList::findLastPriority(int lookFor){
    for(int i = currItemCount; i>-1; i--){
        if(array[i]->getPriority() == lookFor){
            return i;
        }
    }
}

//todo reverse order?, findFirstDate, findLastDate

/**
 * gets a pointer to a Task in the list
 * @param index the index from which to get the value
 * @returns a pointer to the Task with the passed Id
 * @throws out_of_range exception if index is not in List
 */

 Task* ArrayList::getTaskByIndex(int index){
    if(index < 0 ){
        throw std::out_of_range("<index not in range>");
    }
    else if(index > currItemCount){
        throw std::out_of_range("index not in range");
    }
    else{
        return array[index];
    }
}



/**
 * removes the Task from the List
 * @param id of the task to remove from the List
 * @post the Task with id is removed from the list,
 *      everything else is shifted down one,
 *      whoever catches task needs to delete task.
 *      Task is set to complete.
 * @returns the only pointer to the item at index
 * @throws out_of_range exception if id is not in List
 */
 Task* ArrayList::removeTaskById(int idToFind){
    if(currItemCount == 0){
        return nullptr;
    }
    if(idToFind < 0){
        throw std::out_of_range("<id not in range>");
    }
    else{
        for(int i = 0; i<currItemCount; i++){
            if(array[i]->getId() == idToFind){
                int returnVal = array[i]->getId();
                Task* returnTask = array[i];
                array[i] = array[i+1];
                return returnTask;
            }
            currItemCount--;
        }
        return nullptr;
    }

}

/**
 * checks if there are any valid items in the list
 * @returns true if there are no valid items in the list, false otherwise
 */
 bool ArrayList::isEmpty(){
    if(currItemCount == 0){
        return true;
    }else{
        return false;
    }
}

/**
 * returns a count of un-complete Tasks currently in the list
 * @returns the number of un-complete Tasks in the list
 */
 int ArrayList::itemCount(){
    return itemCount();
}

/**
 * removes and deletes all Tasks from the List
 * @post the List is completely clear of valid items and has values reset to defaults
 */
 void ArrayList::clearList(){
    for(int i = 0; i < currItemCount;i++){
        array[i] = 0;
    }
    currItemCount = 0;
}

/**
 * gives a string representation of the title of each Task in the current list.
 * @returns a string representing the given list, broken by line in the format shown below
 * 1. Task_title1
 * 2. Task_title2
 * 3. Task_title3
 * ...
 */




<<<<<<< HEAD
/**
 * Searches an int array for a certain value
 * @post numLinesRun is updated to include lines run by this function
 * @return the index of the last occurrence of numToFind if it is present, otherwise returns -1
 */

//int ArrayList::findLast(int numToFind) {
//    int timer = 0;
//    return findLast(array, currItemCount, numToFind, timer);
//}


/**
 * returns an arrayList of pointers to tasks, organized by highest priority, within the number of days remaining
 * @param masterList - A Linked node structure with pointers to Tasks to be searched through
 * @param daysRemaining - the number of days till the Task is due. if a Task is <= the daysRemaining it will be added to the retruned ArrayList
 * @return A pointer to an ArrayList of pointers to Tasks, if no tasks are due in daysRemaining range, Arraylist will be empty.
 */
ArrayList *ArrayList::buildView(TaskLinkedList *masterList, int daysRemaining) {
    TaskLinkedList *current = masterList->getFront();
    int currCapacity = masterList->itemCount();
    array = new int[currCapacity];
    //int i = 0;
    if (current == nullptr) {
        return this*;
    } else {
        Task *currTask = current->getFront();
        for (int i = 0; i < currCapacity; i++) {
            if (currTask->getDueDate() <= daysRemaining) {
                array[i] = currTask->getId();
                current = current->getNext(); //should I be calling something else, does TaskLinkedList need a get next??
            }
=======
std::string ArrayList::toString(Task* arrayPtr, const int size){
    std::string printable = "{";
    for(int i = 0; i < size; i++){
        if (i < size-1){
            printable = printable + ((arrayPtr[i].getTitle()) + ", ");
        } else{
            printable = printable + ((arrayPtr[i].getTitle()));
>>>>>>> bbcf4798893a15beff7a65690744adf803265247
        }
    }
    printable += "}";
    return printable;
}
