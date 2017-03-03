#include <wiringPi.h>
#include <unistd.h>

int main (void)
{
	int dly = 200;
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
