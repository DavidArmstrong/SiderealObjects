/* Sidereal Objects Library - Table Lookup Examples
 * Version 1.1.0 - September 3, 2021
 * Example1_TableLookups
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
  Serial.println("Sidereal Objects Table Lookup Functions");
  myAstro.begin();
  Serial.println("We start with the star Sirius, which is star 162 in our table:");
  Serial.println("162  9 Alpha CMa Sirius *  6 45 08.9    -16 42 58    -1.46");
  myAstro.selectStarTable(162);
  Serial.print("Right Ascension = 6:45:08.9  ==> ");
  myAstro.printDegMinSecs(myAstro.getRAdec());
  Serial.println("");
  Serial.print("Declination = -16:42:58  ==> ");
  myAstro.printDegMinSecs(myAstro.getDeclinationDec());
  Serial.println();
  Serial.print("Magnitude = -1.46  ==> ");
  Serial.println(myAstro.getStarMagnitude());
  Serial.println();
  
  Serial.println("Next lookup NGC 457, The Owl Cluster, in our table:");
  Serial.println("457  The Owl Cluster    01h 19m 32.6s    +58 17′ 27");
  myAstro.selectNGCTable(457);
  Serial.print("Right Ascension = 01:19:32.6  ==> ");
  myAstro.printDegMinSecs(myAstro.getRAdec());
  Serial.println("");
  Serial.print("Declination = 58:17:27  ==> ");
  myAstro.printDegMinSecs(myAstro.getDeclinationDec());
  Serial.println("\n");
  
  Serial.println("Now lookup IC 4665 in our table:");
  Serial.println("4665    17h 46m 18s   +05 43′ 00 ");
  myAstro.selectICTable(4665);
  Serial.print("Right Ascension = 17:46:18  ==> ");
  myAstro.printDegMinSecs(myAstro.getRAdec());
  Serial.println("");
  Serial.print("Declination = 05:43:00  ==> ");
  myAstro.printDegMinSecs(myAstro.getDeclinationDec());
  Serial.println("\n");
  
  Serial.println("And M13 in our table:");
  Serial.println("M13      NGC6205   16 41.7    36 28   Hercules Globular");
  myAstro.selectMessierTable(13);
  Serial.print("Right Ascension = 16:41.7  ==> ");
  myAstro.printDegMinSecs(myAstro.getRAdec());
  Serial.println("");
  Serial.print("Declination = 36:28  ==> ");
  myAstro.printDegMinSecs(myAstro.getDeclinationDec());
  Serial.println("\n");
  
  Serial.println("Caldwell C13, The Owl Cluster, in our table:");
  Serial.println("C13  NGC 457 The Owl Cluster    01h 19m 32.6s    +58 17′ 27");
  myAstro.selectCaldwellTable(13);
  Serial.print("Right Ascension = 01:19:32.6  ==> ");
  myAstro.printDegMinSecs(myAstro.getRAdec());
  Serial.println("");
  Serial.print("Declination = 58:17:27  ==> ");
  myAstro.printDegMinSecs(myAstro.getDeclinationDec());
  Serial.println("\n");
  
  Serial.println("And special 'Herschel 400' object H1 in our table:");
  Serial.println("H1    NGC40    0 13.0    72 32  Bow-Tie Nebula");
  myAstro.selectHershel400Table(1);
  Serial.print("Right Ascension = 0:13.0  ==> ");
  myAstro.printDegMinSecs(myAstro.getRAdec());
  Serial.println("");
  Serial.print("Declination = 72:32  ==> ");
  myAstro.printDegMinSecs(myAstro.getDeclinationDec());
  Serial.println("\n");
  
  Serial.println("This leaves the Other objects table. We choose number 20001:");
  Serial.println("20001    1 35.7    61 17  18.0  O  Tr1");
  myAstro.selectOtherObjectsTable(20001);
  Serial.print("Right Ascension = 1:35.7  ==> ");
  myAstro.printDegMinSecs(myAstro.getRAdec());
  Serial.println("");
  Serial.print("Declination = 61:17  ==> ");
  myAstro.printDegMinSecs(myAstro.getDeclinationDec());
  Serial.println("\n");
  Serial.println("");
}

void loop() {
  while(1); //Freeze
}