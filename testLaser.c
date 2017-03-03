#include <wiringPi.h>
#include <unistd.h>
#include <stdio.h>

int main (void)
{
	int dly = 1000;
	wiringPiSetup();
	pinMode(0, OUTPUT);

	for(;;)
	{
		digitalWrite(0, HIGH);
		usleep(dly);
		digitalWrite(0, LOW);
		usleep(dly);
	}
	return 0;
} 
