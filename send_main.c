#include <wiringPi.h>
#include <unistd.h>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>


#define NUM_PHOTODIODES 6
int num_photodiodes = NUM_PHOTODIODES;
char buffer[128];
int act_vals[NUM_PHOTODIODES];
int counter;
int phase = 0;
int step_phases[4];

//Parameters
int dly = 1;
int slope_loops = 15;



void step(int k)
{
	pinMode(6, OUTPUT); //Step
	pinMode(10, OUTPUT); //Dir
	
	if(k<0){
		digitalWrite(10, HIGH);	
	}else{
		digitalWrite(10, LOW);
	}
	
	
	int i, dly_slope;
	
	for(i=0; i<abs(k); i++){
		
		if(i <=slope_loops){
			dly_slope = dly *(slope_loops-i);
		}
		if(i > slope_loops){
			dly_slope = 0;
		}
		if(i > (abs(k)-slope_loops)){
			dly_slope = dly * (slope_loops - (abs(k) - i));
		}
		
				digitalWrite(6, HIGH);
				usleep(500);
				digitalWrite(6, LOW);
				usleep(500);
			//delay(dly + dly_slope);
			delay(5);	
	}
	
	
}

void *threadFunc(void *arg)
{
	/*while(1){
		//printf("Hallo ich bin's, der Thread");
		step(1);
		usleep(act_vals[1]);
	}*/
	printf("Thread thrown");
	int i=0;
	for(i=0; i<20; i++){
		digitalWrite(0, HIGH);
		step(-1024);
		digitalWrite(0, LOW);
		delay(1000);
		digitalWrite(0, HIGH);
		step(1024);
		digitalWrite(0, LOW);
		delay(1000);
	
	}

	return NULL;
}





int main (void)
{	
	struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0 };
    char buf[1024] = { 0 };
    int s, client, bytes_read;
    
    socklen_t opt = sizeof(rem_addr);

    // allocate socket
    s = socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);

    // bind socket to port 1 of the first available 
    // local bluetooth adapter
    loc_addr.rc_family = AF_BLUETOOTH;
    loc_addr.rc_bdaddr = *BDADDR_ANY;
    loc_addr.rc_channel = (uint8_t) 1;
    bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));

    // put socket into listening mode
    listen(s, 1);

    // accept one connection
    client = accept(s, (struct sockaddr *)&rem_addr, &opt);

    ba2str( &rem_addr.rc_bdaddr, buf );
    fprintf(stderr, "accepted connection from %s\n", buf);
    memset(buf, 0, sizeof(buf));


	wiringPiSetup();
	printf("main wirft den Thread\n");
	
	pinMode(0, OUTPUT);
	
	pthread_t pth;  // this is our thread identifier
        
    pthread_create(&pth,NULL,threadFunc,"processing...");

	while (1){
		
		bytes_read = read(client, buf, sizeof(buf));
        if( bytes_read > 0 ) {
                printf("received [%s]\n", buf);
        }

	}


	return 0;
} 













