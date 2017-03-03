#include <wiringPi.h>
#include <unistd.h>
#include <stdio.h>
#include <wiringSerial.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define NUM_PHOTODIODES 6
int num_photodiodes = NUM_PHOTODIODES;
char buffer[128];
int act_vals[NUM_PHOTODIODES];
int counter;



void *threadFunc(void *arg)
{
	while(1){
		//printf("Hallo ich bin's, der Thread");
	
		usleep(500000);
	}
	return NULL;
}

void parseInts (void){
	int seperators[num_photodiodes + 1];
	int k = 1;
	int buffer_length = 0;
	int i = 0;
	int j = 0;	
	
	
	for(i = 0; i<sizeof(buffer); i++){
		if(buffer[i] == ';'){
		buffer_length = i;
		}
	}
	
	seperators[0]=0;
	seperators[6]=buffer_length; 
		
	for(j=0; j<sizeof(buffer); j++){
		printf("%c", buffer[j]);
	}
	
	
	
	for(i=1; i<(sizeof(buffer)-1); i++){
		if(buffer[i] == ','){
		seperators[k] = i;  k++;
		}
	}	
	

					
	/*printf("%i\n",counter);
	counter++;
	*/
	
	int bufferValues[num_photodiodes];
	int m;
	int l;
	for(m=0; m<num_photodiodes; m++){
		l=-1;
		int j;
		int bufferString_length = seperators[m+1] - (seperators[m]+1);
		char bufferString[bufferString_length];
		
		for(j=(seperators[m]+1); j<seperators[m+1]; j++){
			l++;   
			bufferString[l] = buffer[j]; 
		}
		
		bufferValues[m] = atoi(bufferString);
		
		for(j=0; j<sizeof(bufferString); j++){
			bufferString[j] = '\0';
		}
		
	}
	
	int z;
	for(z=0; z<num_photodiodes; z++){
		
		printf("%i \t",bufferValues[z]);
	}
	printf("\n");
	
	
}



int main (void)
{
	printf("main wirft den Thread\n");

	pthread_t pth;  // this is our thread identifier
        
        pthread_create(&pth,NULL,threadFunc,"processing...");
		
		int i = 0, j = 0;
		

		int handle = serialOpen("/dev/ttyACM0", 9600);
		printf("Thread startet\n");

		while (1){
					
			char data = serialGetchar(handle);
			
			if(data == '*' && i == 0){ //String has to start with '*'
				for(j=0; j<sizeof(buffer); j++){
					buffer[j] = '\0';
				}
				buffer[i] = data;
				i++;
			} else if(i > 0){
				if(data == ';'){
					buffer[i] = data;	
					i = 0;
					parseInts();
				}else{
					buffer[i] = data; i++;
				}
			}
		

		
		}


	return 0;
} 








