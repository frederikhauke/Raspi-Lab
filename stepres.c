//Links: Schwarz-Rot, Rechts: Grün-Blau

#include <wiringPi.h>

int dly = 4;
	int dlys = 1;
	int dlyl;

void step(int k)
{
	wiringPiSetup();
	pinMode(6, OUTPUT);
	pinMode(10, OUTPUT);
	pinMode(11, OUTPUT);
	pinMode(31, OUTPUT);
	dlyl = dly - dlys;
	
	int i;
	for(i=0; i<k; i++){
			
				digitalWrite(6, HIGH) ; 
				digitalWrite(10, LOW) ; 
				digitalWrite(11, LOW) ; 
				digitalWrite(31, LOW) ; 
		delay(dlys);	
				digitalWrite(6,LOW) ; 
				digitalWrite(10, LOW) ; 
				digitalWrite(11, LOW) ; 
				digitalWrite(31, LOW) ; 
		delay(dlyl);		

 		
 		    
                digitalWrite(6, LOW) ; 
                digitalWrite(10, HIGH) ; 
                digitalWrite(11, LOW) ; 
                digitalWrite(31, LOW) ; 
        delay(dlys);	
				digitalWrite(6,LOW) ; 
				digitalWrite(10, LOW) ; 
				digitalWrite(11, LOW) ; 
				digitalWrite(31, LOW) ; 
		delay(dlyl);
		
	    
                digitalWrite(6, LOW) ; 
                digitalWrite(10, LOW) ; 
                digitalWrite(11, HIGH) ; 
                digitalWrite(31, LOW) ; 
        delay(dlys);	
				digitalWrite(6,LOW) ; 
				digitalWrite(10, LOW) ; 
				digitalWrite(11, LOW) ; 
				digitalWrite(31, LOW) ; 
 		delay(dlyl);
		
    
                digitalWrite(6, LOW) ; 
                digitalWrite(10, LOW) ; 
                digitalWrite(11, LOW) ; 
                digitalWrite(31, HIGH) ; 
        delay(dlys);	
				digitalWrite(6,LOW) ; 
				digitalWrite(10, LOW) ; 
				digitalWrite(11, LOW) ; 
				digitalWrite(31, LOW) ; 
		delay(dlyl);
	}
}

