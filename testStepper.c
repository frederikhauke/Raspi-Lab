//Links: Schwarz-Rot, Rechts: Grün-Blau

#include <wiringPi.h>
int main (void)
{
	int dly = 1;
	wiringPiSetup();
	pinMode(6, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(31, OUTPUT);
	
	
	for(;;)
	{
		delay(dly);	
		digitalWrite(6, HIGH) ; 
		digitalWrite(10, LOW) ; 
		digitalWrite(11, LOW) ; 
		digitalWrite(31, LOW) ; 

 		delay(dly);     
                digitalWrite(6, LOW) ; 
                digitalWrite(10, HIGH) ; 
                digitalWrite(11, LOW) ; 
                digitalWrite(31, LOW) ; 
		
		delay(dly);     
                digitalWrite(6, LOW) ; 
                digitalWrite(10, LOW) ; 
                digitalWrite(11, HIGH) ; 
                digitalWrite(31, LOW) ; 
 		
		delay(dly);     
                digitalWrite(6, LOW) ; 
                digitalWrite(10, LOW) ; 
                digitalWrite(11, LOW) ; 
                digitalWrite(31, HIGH) ; 


	}
	return 0;
} 
