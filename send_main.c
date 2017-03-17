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
int checker = 0;
int step_phases[4];
int beamHit;
int count_stepsOnDiode;
int counter_midFound;

//Parameters
int dly = 50;
int slope_loops = 15;



void step(int k, int p)
{
	int stepPin = 0;
	int dirPin = 0;
	if(p == 0){
		pinMode(6, OUTPUT);  stepPin = 6;
		pinMode(10, OUTPUT); dirPin = 10;
	} else{
		pinMode(11, OUTPUT); stepPin = 11;
		pinMode(31, OUTPUT); dirPin = 31; dly = 10;
	}

	if(k<0){
		digitalWrite(dirPin, HIGH);	
	}else{
		digitalWrite(dirPin, LOW);
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
		
				digitalWrite(stepPin, HIGH);
				usleep(500);
				digitalWrite(stepPin, LOW);
				usleep(500);
			
				usleep(dly + dly_slope);
	}
		
}



void *threadFunc(void *arg)
{
	while(1){
		step(-1, 1);
		delay(2000);
	}

	
	printf("Thread thrown");
	/*int i=0;
	int p = 1;
	
	while(1){
			digitalWrite(7, LOW);
			digitalWrite(8, HIGH);
			digitalWrite(9, LOW);
				
			if(beamHit == 0) step(1, p);
			else break;
	}
	step(20, p);
	digitalWrite(7, HIGH);
	digitalWrite(8, HIGH);
	digitalWrite(9, LOW);
	//step(-30, p);
	
	digitalWrite(7, HIGH);
	digitalWrite(8, LOW);
	digitalWrite(9, HIGH);
	
	beamHit =0;
	checker = 1;
	while(checker){
		checker = 0;
		while(1){
				if(beamHit == 0) step(-1, p);
				else break;
			
				delay(100);
		}
	
		while(1){
				step(-1, p);
				if(beamHit == 1) count_stepsOnDiode++;
				else if(count_stepsOnDiode > 1 && beamHit == 0)break;
				beamHit = 0;
				delay(100);
		}
		step( (int)(count_stepsOnDiode / 2), p );
		printf("Go to mid");
		printf("%i\n", count_stepsOnDiode);
		count_stepsOnDiode = 0;
		
		checker = 1;
		while(1){
			if(counter_midFound > 6) { checker = 0; counter_midFound = 0; break;}
		}
		
		if(checker == 1) step(15, p);
	}
	* */
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
	
	printf("Waiting for Bluetooth-Connection ...\n");
	
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
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(9, OUTPUT);
	digitalWrite(0, HIGH);
	
	pthread_t pth;  // this is our thread identifier
        
    pthread_create(&pth,NULL,threadFunc,"processing...");

	while (1){
		
		bytes_read = read(client, buf, sizeof(buf));
        if( bytes_read > 0 ) {
                printf("%i,", counter); counter++;
                printf("received [%s]\n", buf);
                beamHit = 1;
                if(checker == 1) counter_midFound++;
               
        }

	}


	return 0;
} 













