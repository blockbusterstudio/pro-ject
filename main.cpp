#include <iostream>
#include <string>
#include "TaskLinkedList.h"
#include "Task.h"
#include "List.h"

void PrototypeController(){
    List<Task>* masterList= new TaskLinkedList<Task>();

    //must create empty list of tasks, add first task to that
    int userDirection=-1;
    while(userDirection!=3){
        std::cout<<"Enter 0 to add a new task, 1 to view tasks, 2 to complete tasks, 3 to quit: "<<std::endl;
        std::cin>>userDirection;

        //add to task
        if(userDirection==0){
            std::string inTitle;
            //print directions
            std::cout<<"Enter the name of the task: "<<std::endl;
            std::getline(std::cin>>inTitle,inTitle);
            int dueDate;
            std::cout<<"Enter days until due: "<<std::endl;
            std::cin>>dueDate;
            bool complete=false;
            int ID=0; ///MUST CHANGE TO PRODUCE SOME INTEGER
            Task* newTask= new Task(inTitle,dueDate,complete,ID);
            masterList->addToList(newTask);
        }
            //view tasks
        else if (userDirection==1){

        }
            //complete a task
        else if(userDirection==2){
            //should call view w/ indicies????

            //print tasks and associated numbers

            //for each case do below
            Task* taskPtr;
            bool complete =taskPtr->getComplete();
            if(complete==0){
                std::cout<<"The task "<<taskPtr->getTitle() <<" is not complete."<<std::endl;

            }
            else if(complete==1) {
                std::cout << "The task " << taskPtr->getTitle() << " is complete." << std::endl;
            }


        }
            //quit program
        else if(userDirection==3){
        }
        else{
            while(userDirection<0 || userDirection>3){
                std::cout<<"Invalid entry. Please enter 0 to add task, 1 to view, 2 to complete, 3 to quit"<<std::endl;
                std::cin>>userDirection;
            }
        }

    }

    std::cout<<"\n\nThank you for using the JTC TaskManager."<<std::endl;

    //prompts user with request to add a task


    //prompt user to input field variables (constructor calls set methods to construct new node)


    //add the node to the list


    //prompt user to view list, add new task, complete task, quit


    //do that thing

    //repeat above until quit is entered
}







int main() {
    std::cout << "Welcome to the JTC TaskManager\n" << std::endl;

    PrototypeController();
    //Task::Task(std::string inTitle="newTask", int inDue=1, bool inTaskComplete=false, int inIdNum=-1)
//    Task* myTask = new Task("task1",1,false,-1);
//    std::string title = myTask->getTitle();
//    std::cout<< title <<std::endl;
    return 0;
}