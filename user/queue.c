// Circular Queue implementation
//queue but the last element is connected to the first element
//to implement this g=have two pinters ie. front and back 
//front tracks first element and back tracks the last element 

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

//initilaize array
//int size = 10;
char *queue[10]; //temp

//initialize front and back to -1 
int front = -1;
int back = -1;

//check if queue is full 
int 
isFull(){
	/*if (front = 0 && back = 0 || front = 0 && back = 99){
		return 1;
	}*/
	//when back+1 == front
	if(((back + 1) == front) || ((front == 0) && (back == 10 -1))){
		return 1; //yes it is full;
	}
	
	return 0; //no it is not full
}

//check if queue is empty
int 
isEmpty() {
	if (front == -1){
		return 1;
	}
	return 0;
}

//remove an element
void 
deQueue() {
	/*if(isFull() == 1){
		front++;
		//back == 0;
		return 1; //sucessfully dequeued
	}*/
	//check if the queue is empty 
	/*if(isEmpty() == 0){
		queue[back] == NULL;
		front++;	
	}*/
	
	
	//return the value pointed by front
	// inscrese the front index by 1
	// last element --> resent the values of front and back to -1
	if (front == back){
		front = -1;
		back = -1;
	}
	else{
		front = (front +1) % 10;	
	}
}


//add an element
void 
enQueue(char *element) {
	printf("element to be queued: %s\n", element);
	/* TODO: we shouldn't check if its full, instead refactor this to remove an 
	element from the end and add the new elenent to the history queue to keep relevance*/

	

	if (isFull()){
    	printf("Cannot add element. Queue is full\n");
    	deQueue();
    	char *a = (char *)malloc(strlen(element)+1);
    	strcpy(a, element);
    	    	
        queue[back] = a;
	}
	/*if (back == 0){
		//deQueue the last element
		// add new element --> remove else 
	}*/
  	else { //add element to queue
  		//printf("in enqueue\n");
  		//if the queue is empty then update front to 0
    	if (front == -1){
    		front = 0;
    	}
    	//increase the back by 1 but if it reaches end (size) should be start of queue
    	back = (back+1) % 10; //is this right??? not circular
    	/*if(back == 10){
    	   back = 0;
    	}*/
    	
    	char *a = (char *)malloc(strlen(element)+1);
    	strcpy(a, element);
    	
		queue[back] = a;
		
      	//printf("the queue after enQueue: %s\n", queue);
  	}
}

//print the queue
void printQueue(){
	printf("in printQueue\n");
	printf("front: %d\n", front);
	printf("back: %d\n", back);
	//for(int i = front; i != back; i++){ //is this circular tho???
	//for(int i = front; i < back+1; i++){
	//char *temp[10];
	for (int i = front; i != back; i = (i + 1) % 10) {
	      if (i != '\0'){
	      	printf("in the printqueue for loop\n");
	      	printf("%s ", queue[i]);
	      }
	}
	
	/*for(int i = front; i != back; i++){
		if (i != '\0'){
			printf("in the printqueue for loop\n");
			printf("%s ", queue[i]);
		}
		if(i == 9){
			i = 0;
		}
	}*/
}
