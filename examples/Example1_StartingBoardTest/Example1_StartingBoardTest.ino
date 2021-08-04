/* Sidereal Objects Library Board Test
 * David Armstrong
 * Version 1.0.0 - August 4, 2021
 * Example1_StartingBoardTest
*/

// Need the following define for SAMD processors
#if defined (ARDUINO_ARCH_SAMD)
#define Serial SerialUSB
#endif

void setup() {
  Serial.begin(9600);
  delay(2000); //SAMD boards may need a long time to init SerialUSB
  Serial.println("Sidereal Objects Board Test");
  Serial.println("Check to see if the Sidereal Objects Library is recommended for this processor.\n");

  // Real Number check
  float  fpi = 3.14159265358979;
  double dpi = 3.14159265358979;
  if (dpi == (double)fpi ) { //double and float are the same here!
    Serial.println("Target board does not handle Real Double numbers.");
	Serial.println("A different Arduino platform is recommended.");
  } else {
	Serial.println("Target board will handle real double numbers.");
	Serial.println("Go ahead and use this platform for sketches using the Sidereal Objects Library.");
  }
}

void loop() {
  while(1); //Freeze
}
