// Circular Queue implementation
//queue but the last element is connected to the first element
//to implement this g=have two pinters ie. front and back 
//front tracks first element and back tracks the last element 

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

//initialize SIZE
#define SIZE 10;

//initilaize array
int  queue[SIZE];

//initialize front and back to -1 
int front = -1;
int back = -1;

//check if queue is full 
int 
isFull(){
	//if front = 0 and back = 0
	return 0;
}

//check if queue is empty
int 
isEmpty() {
	if (front == -1){
		return 1;
	}
	return 0;
}

//add an element
void 
enQueue(int element) {
	/* TODO: we shouldn't check if its full, instead refactor this to remove an 
	element from the end and add the new elenent to the history queue to keep relevance*/
	if (isFull()){
    	printf("Cannot add element. Queue is full\n");
	}
  	else { //add element to queue
  		//if the queue is empty then update front to 0
    	if (front == -1){
    		front = 0;
    	}
    	//increase the back by 1 but if it reaches end (size) should be start of queue
    	back = (back + 1); //is this right???
      	items[back] = element;
  	}
	
}

//remove an element
int 
deQueue() {
	//cehck if the queue is empty 
	//return the value pointed by front
	// inscrese the front index by 1
	// last element --> resent the values of front and back to -1
	return 0;
}

//print the queue
void printQueue() {
	for (i = front; i != rear; i++ { //is this circular tho???
	      printf("%d ", items[i]);
	    }
	
	
}

int 
main(int agrc, char *argv[])
{
	
}
