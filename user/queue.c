// Circular Queue implementation
//queue but the last element is connected to the first element
//to implement this g=have two pinters ie. front and back 
//front tracks first element and back tracks the last element 

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

//initialize SIZE
//#define SIZE 10;

//initilaize array
char queue[100];

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
enQueue(char element) {
	/* TODO: we shouldn't check if its full, instead refactor this to remove an 
	element from the end and add the new elenent to the history queue to keep relevance*/
	if (isFull()){
    	printf("Cannot add element. Queue is full\n");
	}
	/*if (back == 0){
		//deQueue the last element
		// add new element --> remove else 
	}*/
  	else { //add element to queue
  		printf("in enqueue\n");
  		//if the queue is empty then update front to 0
    	if (front == -1){
    		front = 0;
    	}
    	//increase the back by 1 but if it reaches end (size) should be start of queue
    	back = (back + 1); //is this right??? not circular 
      	queue[back] = element;
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
void printQueue(){
	//for(int i = front; i != back; i++){ //is this circular tho???
	for(int i = 0; i >= 2; i++){
		printf("in the printqueue for loop\n");
		printf("%s ", queue[i]);
	}
}
