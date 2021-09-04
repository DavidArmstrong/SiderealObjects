/* Sidereal Objects Library - Identify function
 * Version 1.1.0 - September 3, 2021
 * Example2_Identify
*/

#include <SiderealObjects.h>

// Need the following define for SAMD processors
#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
  #define Serial SERIAL_PORT_USBVIRTUAL
#endif

SiderealObjects myAstro;

void setup() {
  Serial.begin(9600);
  delay(2000); //SAMD boards may need a long time to init SerialUSB
  Serial.println("Sidereal Planets Coordinate Conversion Functions");
  myAstro.begin();
  Serial.println("Identify object closest to a given set of coordinates.\n");
  Serial.println("Star Sirius:");
  Serial.println("We can use the decimalDegrees() function to make this easier.");
  Serial.println("162  9 Alpha CMa Sirius   RA=6h 45m 8.9s    Dec=-16d 42m 58s    Mag=-1.46");
  myAstro.setRAdec(myAstro.decimalDegrees(6,45,8.9), myAstro.decimalDegrees(-16,42,58));
  Serial.print("Right Ascension = 6:45:08.9  ==> ");
  myAstro.printDegMinSecs(myAstro.getRAdec());
  Serial.println("");
  Serial.print("Declination = -16:42:58  ==> ");
  myAstro.printDegMinSecs(myAstro.getDeclinationDec());
  Serial.println();
  myAstro.identifyObject();
  printObject();
  Serial.println();
  
  Serial.println("NGC 892:");
  Serial.println("892	RA=02h 20.7m	 Dec=-23d 07m");
  myAstro.setRAdec(myAstro.decimalDegrees(2,20,35), myAstro.decimalDegrees(-23,07,00));
  myAstro.identifyObject();
  printObject();
  Serial.println();
  
  Serial.println("IC 4665:");
  Serial.println("4665    RA=17h 46m 18s   Dec=+05d 43m 00s");
  myAstro.setRAdec(myAstro.decimalDegrees(17,46,18), myAstro.decimalDegrees(5,43,00));
  myAstro.identifyObject();
  printObject();
  Serial.println();
  
  Serial.println("Other objects 20001:");
  Serial.println("20001    RA=1h 35.7m   Dec=61d 17m    Tr1");
  myAstro.setRAdec(myAstro.decimalDegrees(1,36,0), myAstro.decimalDegrees(61,17,0));
  myAstro.identifyObject();
  printObject();
  Serial.println();
  
  Serial.println("Messier 13:");
  Serial.println("M13    NGC6205   RA=16h 41.7m    Dec=36d 28m   Hercules Globular");
  myAstro.setRAdec(myAstro.decimalDegrees(16,41,40), myAstro.decimalDegrees(36,28,00));
  myAstro.identifyObject();
  printObject();
  Serial.println();
  
  Serial.println("Caldwell C13, The Owl Cluster:");
  Serial.println("C13  NGC 457  The Owl Cluster    RA=01h 19m 32.6s    Dec=+58d 17m 27s");
  myAstro.setRAdec(myAstro.decimalDegrees(1,19,32.6), myAstro.decimalDegrees(58,17,27));
  myAstro.identifyObject();
  printObject();
  Serial.println();
  
  Serial.println("Special 'Herschel 400' object H2:");
  Serial.println("H2  NGC129     79.8    RA=0h 29.9m    Dec=60d 14m");
  myAstro.setRAdec(myAstro.decimalDegrees(0,29,56), myAstro.decimalDegrees(60,14,00));
  myAstro.identifyObject();
  printObject();
  Serial.println();
  
}

void loop() {
  while(1); //Freeze
}

void printObject() {
  Serial.print("Identified Object: ");
  switch(myAstro.getIdentifiedObjectTable()) {
    case(1):
	Serial.print("Star "); break;
	case(2):
	Serial.print("NGC "); break;
	case(3):
	Serial.print("IC "); break;
	case(7):
	Serial.print("Other "); break;
  }
  Serial.print(myAstro.getIdentifiedObjectNumber());
  if (myAstro.getIdentifiedObjectTable() == 1) {
    Serial.print(" ");
	Serial.print(myAstro.printStarName(myAstro.getIdentifiedObjectNumber()));
  }
  Serial.println();
  if (myAstro.getAltIdentifiedObjectTable()) {
    Serial.print("Alternate Object Identification: ");
    switch(myAstro.getAltIdentifiedObjectTable()) {
	  case(4):
	  Serial.print("Messier "); break;
	  case(5):
	  Serial.print("Caldwell "); break;
	  case(6):
	  Serial.print("Herschel 400 number "); break;
    }
	Serial.println(myAstro.getAltIdentifiedObjectNumber());
  }
}
