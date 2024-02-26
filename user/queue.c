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
	if (isFull()){
    	deQueue();
    	back = (back+1) % 10; 
    	char *a = (char *)malloc(strlen(element)+1);
    	strcpy(a, element);
        queue[back] = a;
	}
  	else { //add element to queue
  		//if the queue is empty then update front to 0
    	if (front == -1){
    		front = 0;
    	}
    	//increase the back by 1 but if it reaches end (size) should be start of queue
    	back = (back+1) % 10; 
    	char *a = (char *)malloc(strlen(element)+1);
    	strcpy(a, element);
		queue[back] = a;
  	}
}

//print the queue
void printQueue(){
	int count = 0;
	for (int i = front; i+1 != back; i++) {
		  if (count == 10){
		  	break;
		  }
		  i = (i) % 10;
	      printf("%s ", queue[i]);
	      count++;
	}
}
