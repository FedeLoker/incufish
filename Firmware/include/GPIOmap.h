
#ifndef GPIOmap_h
#define GPIOmap_h

/*

    	  	         +---+  
    	  	+--------|USB|--------+
    	  	| 3V3    |   |    VIN |    	
    	  	| GND    +---+    GND |    	
    	  	| TX1      E      RST |    	
     	  	| RX1      S      EN  |    	
     	  	|~D15      P      3V3 |    
     	  	| D13             GND |    
    	  	|~D12      8      D06 |    
    	  	|~D14      2      D07 |    
  		  	| GND      6      D11 |    	
  			| 3V3      6      D08 |    	
  			| D02             D09 |    	
  	    	| D00      M      D10 |    	
  	    	|~D04      C      DNU |    	
  	    	| D05      U      DNU |    
  	    	|~D16             A0  |    		
  	    	+---------------------+	


*/

#include <Arduino.h>

// Temperature Sensors:
#define TEMP_1 D2 
#define TEMP_2 D1 
#define TEMP_3 D3 
#define TEMP_4 D4 

// Output Relay Variables
#define RELAY_1 D5
#define RELAY_2 D6
#define RELAY_3 D7
#define RELAY_4 D0

void GPIO_init();
String activateRelay(uint8_t deviceID, float setTemp, float currentTemp, float hysteresis);

#endif