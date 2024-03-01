// Circular Queue implementation
//queue but the last element is connected to the first element
//to implement this g=have two pinters ie. front and back 
//front tracks first element and back tracks the last element 

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

//initilaize array

#define SIZE 10 //able to be changed

char *queue[SIZE]; 

//initialize front and back to -1 
int front = -1;
int back = -1;

//check if queue is full 
int 
isFull(){
	if(((back + 1) == front) || ((front == 0) && (back == SIZE -1))){
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
		front = (front +1) % SIZE;	
	}
}


//add an element
void 
enQueue(char *element) {
	if (isFull()){
    	deQueue();
    	back = (back+1) % SIZE; 
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
    	back = (back+1) % SIZE; 
    	char *a = (char *)malloc(strlen(element)+1);
    	strcpy(a, element);
		queue[back] = a;
  	}
}

//print the queue
void printQueue(){

	int j = front;
	for (int count = 0; count < SIZE; count++) {
		  printf("%s ", queue[j]);
		  j = (j+1) % SIZE;
	}
}

//read from the file 
void queueStart(){
	char* filename = "hist.txt";
	char buf[256];
	int fd = open(filename, O_RDONLY);
	read(fd, buf, 256);
	char temp[100];
	int cc = 0;
	char c;
	for(int i = 0; i < SIZE; i++){
		//read from file
		//enqueue
		for(int i=0; i+1 < 100; ){
		    cc = read(fd, &c, 1);
		    if(cc < 1)
		      break;
		    temp[i++] = c;
		    if(c == '\n' || c == '\r')
		      break;
		}
		char *p = temp;
		enQueue(p);
		back++;
	}
	//todo debug -print elms as reading from file
}

//write to the file
void queueWriteFile(){
	int j = front;
	char* filename = "hist.txt";
	int fd = open(filename, O_WRONLY | O_CREATE | O_TRUNC);
	
	for (int i = 0; i < SIZE; i++) {
		char *elem = queue[j];
		write(fd, elem, strlen(elem));
		j = (j+1) % SIZE;
	}
}
