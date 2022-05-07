/******************************************************************************
SiderealObjects.cpp
Sidereal Objects Arduino Library C++ source
David Armstrong
Version 1.1.0 - September 3, 2021
https://github.com/DavidArmstrong/SiderealObjects

Resources:
Uses math.h for math function

Development environment specifics:
Arduino IDE 1.8.15

This code is released under the [MIT License](http://opensource.org/licenses/MIT).
Please review the LICENSE.md file included with this example.
Distributed as-is; no warranty is given.
******************************************************************************/

// include this library's description file
#include "SiderealObjects.h"

// Need the following define for SAMD processors
#if defined(ARDUINO_SAMD_ZERO) && defined(SERIAL_PORT_USBVIRTUAL)
  #define Serial SERIAL_PORT_USBVIRTUAL
#endif

// Public Methods //////////////////////////////////////////////////////////
// Start by doing any setup, and verifying that doubles are supported
boolean SiderealObjects::begin(void) {
  //float  fpi = 3.14159265358979;
  //double dpi = 3.14159265358979;
  //if (dpi == (double)fpi ) return false; //double and float are the same here!

  return true;
}

double SiderealObjects::decimalDegrees(int degrees, int minutes, float seconds) {
  int sign = 1;
  if (degrees < 0) {
	degrees = -degrees;
	sign = -1;
  }
  if (minutes < 0) {
	minutes = -minutes;
	sign = -1;
  }
  if (seconds < 0) {
	seconds = -seconds;
	sign = -1;
  }
  double decDeg = degrees + (minutes / 60.0) + (seconds / 3600.);
  return decDeg * sign;
}

void SiderealObjects::printDegMinSecs(double n) {
  boolean sign = (n < 0.);
  if (sign) n = -n;
  long lsec = n * 360000.0;
  long deg = lsec / 360000;
  long min = (lsec - (deg * 360000)) / 6000;
  float secs = (lsec - (deg * 360000) - (min * 6000)) / 100.;
  if (sign) Serial.print("-");
  Serial.print(deg); Serial.print(":");
  Serial.print(min); Serial.print(":");
  Serial.print(abs(secs)); Serial.print(" ");
}

boolean SiderealObjects::setRAdec(double RightAscension, double Declination) {
  if (RAdec == RightAscension && DeclinationDec == Declination) return true; //Already done
  RAdec = RightAscension;
  //RArad = deg2rad(RAdec) * 15.;
  //sinRA = sin(RArad);
  //cosRA = cos(RArad);
  DeclinationDec = Declination;
  //DeclinationRad = deg2rad(DeclinationDec);
  //sinDec = sin(DeclinationRad);
  //cosDec = cos(DeclinationRad);
  return true;
}

double SiderealObjects::getRAdec(void) {
  return RAdec;
}

double SiderealObjects::getDeclinationDec(void) {
  return DeclinationDec;
}

float SiderealObjects::getStarMagnitude(void) {
  return magnitude;
}

boolean SiderealObjects::selectStarTable(int n) {
  if (n < 1 || n > NSTARS) return false; //bad input
  tablenum = 1;
  objectnum = n;
  int index = (n - 1) * 5;
  #if defined(__AVR_ATmega2560__)
  rawRA = (pgm_read_byte_near(SObjectsstars_bin + index) << 8) | (pgm_read_byte_near(SObjectsstars_bin + index + 1));
  rawDec = (pgm_read_byte_near(SObjectsstars_bin + index + 2) << 8) | (pgm_read_byte_near(SObjectsstars_bin + index + 3));
  #else
  rawRA = (SObjectsstars_bin[index] << 8) | SObjectsstars_bin[index + 1];
  rawDec = (SObjectsstars_bin[index + 2] << 8) | SObjectsstars_bin[index + 3];
  #endif
  RAdec = (double)rawRA * 24.0 / F2to16; //decimal hours
  DeclinationDec = (double)rawDec * 90. / F2to15minus1;
  #if defined(__AVR_ATmega2560__)
  magnitude = (float)(pgm_read_byte_near(SObjectsstars_bin + index + 4)) / 24. - 1.5;
  #else
  magnitude = (float)SObjectsstars_bin[index + 4] / 24. - 1.5;
  #endif
  return true;
}

char* SiderealObjects::printStarName(int n) {
  int index;
  for (index=0; index < SObjectsstars_names_num; index++) {
	if (starName[index].starNum == n) {
	  return starName[index].name;
    }
  }
  strcpy(tempStarName, "");
  return tempStarName;
}

boolean SiderealObjects::selectNGCTable(int n) {
  if (n < 1 || n > NGCNUM) return false; //bad input
  tablenum = 2;
  objectnum = n;
  int index = (n - 1) * 4;
  #if defined(__AVR_ATmega2560__)
  rawRA = (pgm_read_byte_near(Cngc_bin + index) << 8) | (pgm_read_byte_near(Cngc_bin + index + 1));
  rawDec = (pgm_read_byte_near(Cngc_bin + index + 2) << 8) | (pgm_read_byte_near(Cngc_bin + index + 3));
  #else
  rawRA = (Cngc_bin[index] << 8) | Cngc_bin[index + 1];
  rawDec = (Cngc_bin[index + 2] << 8) | Cngc_bin[index + 3];
  #endif
  RAdec = (double)rawRA * 24.0 / F2to16; //decimal hours
  DeclinationDec = (double)rawDec * 90. / F2to15minus1;
  return true;
}

boolean SiderealObjects::selectICTable(int n) {
  if (n < 1 || n > ICNUM) return false; //bad input
  tablenum = 3;
  objectnum = n;
  int index = (n - 1) * 4;
  #if defined(__AVR_ATmega2560__)
  rawRA = (pgm_read_byte_near(Ic_bin + index) << 8) | (pgm_read_byte_near(Ic_bin + index + 1));
  rawDec = (pgm_read_byte_near(Ic_bin + index + 2) << 8) | (pgm_read_byte_near(Ic_bin + index + 3));
  #else
  rawRA = (Ic_bin[index] << 8) | Ic_bin[index + 1];
  rawDec = (Ic_bin[index + 2] << 8) | Ic_bin[index + 3];
  #endif
  RAdec = (double)rawRA * 24.0 / F2to16; //decimal hours
  DeclinationDec = (double)rawDec * 90. / F2to15minus1;
  return true;
}

boolean SiderealObjects::selectMessierTable(int n) {
  if (n < 1 || n > 110) return false; //bad input
  bool flag;
  //offset, since only 2 bytes are used per object
  int index = (n - 1) * 2;
  #if defined(__AVR_ATmega2560__)
  int ngcIcIndex = (pgm_read_byte_near(Msrch_bin + index) << 8) | (pgm_read_byte_near(Msrch_bin + index + 1));
  #else
  int ngcIcIndex = (Msrch_bin[index] << 8) | Msrch_bin[index + 1];
  #endif
  // object #s are NGC, IC, or Other objects only
  if (ngcIcIndex > NGCNUM) {
	// Either IC or Other objects
	if ((ngcIcIndex - 10000) > ICNUM) {
      //Other objects
	  flag = selectOtherObjectsTable(ngcIcIndex);
	} else {
      //IC Object
	  flag = selectICTable(ngcIcIndex);
	}
  } else {
    // NGC object
	flag = selectNGCTable(ngcIcIndex);
  }
  tablenum = 4;
  objectnum = n;
  return flag;
}

boolean SiderealObjects::selectCaldwellTable(int n) {
  if (n < 1 || n > 109) return false; //bad input
  bool flag;
  //offset, since only 2 bytes are used per object
  int index = (n - 1) * 2 + 220;
  #if defined(__AVR_ATmega2560__)
  int ngcIcIndex = (pgm_read_byte_near(Msrch_bin + index) << 8) | (pgm_read_byte_near(Msrch_bin + index + 1));
  #else
  int ngcIcIndex = (Msrch_bin[index] << 8) | Msrch_bin[index + 1];
  #endif
  // object #s are NGC, IC, or Other objects only
  if (ngcIcIndex > NGCNUM) {
	// Either IC or Other objects
	if ((ngcIcIndex - 10000) > ICNUM) {
      //Other objects
	  flag = selectOtherObjectsTable(ngcIcIndex);
	} else {
      //IC Object
	  flag = selectICTable(ngcIcIndex);
	}
  } else {
    // NGC object
	flag = selectNGCTable(ngcIcIndex);
  }
  tablenum = 5;
  objectnum = n;
  return flag;
}

boolean SiderealObjects::selectHershel400Table(int n) {
  if (n < 1 || n > 400) return false; //bad input
  bool flag;
  //offset, since 4 bytes are used per object
  //Table has 2 bytes for wierd Hershel number, and 2 bytes for NGC number
  //We only use a regular int number here, instead of the original wierd number
  int index = (n - 1) * 4 + 2;
  #if defined(__AVR_ATmega2560__)
  int ngcIcIndex = (pgm_read_byte_near(h400n_bin + index) << 8) | (pgm_read_byte_near(h400n_bin + index + 1));
  #else
  int ngcIcIndex = (h400n_bin[index] << 8) | h400n_bin[index + 1];
  #endif
  if (ngcIcIndex > NGCNUM) {
	// Either IC or Other objects
	return false; //bad input
  } else {
    // NGC object
	flag = selectNGCTable(ngcIcIndex);
  }
  tablenum = 6;
  objectnum = n;
  return flag;
}

boolean SiderealObjects::selectOtherObjectsTable(int n) {
  tablenum = 7;
  objectnum = n;
  //search, since 6 bytes are used per object
  //int index = (n - 1) * 6;
  int index;
  uint16_t otherobjnum;
  for (index = 0; index < 567 * 6; index += 6) {
    #if defined(__AVR_ATmega2560__)
	otherobjnum = (pgm_read_byte_near(Other_bin + index) << 8) | (pgm_read_byte_near(Other_bin + index + 1));
	#else
    otherobjnum = (Other_bin[index] << 8) | Other_bin[index + 1];
    #endif
	if (otherobjnum == n) break;
  }
  if (otherobjnum != n) return false; // Didn't find it
  #if defined(__AVR_ATmega2560__)
  rawRA = (pgm_read_byte_near(Other_bin + index + 2) << 8) | (pgm_read_byte_near(Other_bin + index + 3));
  rawDec = (pgm_read_byte_near(Other_bin + index + 4) << 8) | (pgm_read_byte_near(Other_bin + index + 5));
  #else
  rawRA = (Other_bin[index + 2] << 8) | Other_bin[index + 3];
  rawDec = (Other_bin[index + 4] << 8) | Other_bin[index + 5];
  #endif
  RAdec = (double)rawRA * 24.0 / F2to16; //decimal hours
  DeclinationDec = (double)rawDec * 90. / F2to15minus1;
  return true;
}

boolean SiderealObjects::identifyObject(void) {
  long int radiff = -1L;
  long int decdiff = -1L;
  long unsigned int totaldiff = 0x7fffffffL;
  long unsigned int comparediff;
  uint16_t targetRA = RAdec * F2to16 / 24.; //convert to integers for faster compares
  int16_t targetDec = DeclinationDec * F2to15minus1 / 90.;
  int index;
  uint16_t tempobjnum;
  alttablenum = 0;
  
  // Check star table first
  for (index = 0; index < NSTARS * 5; index += 5) {
	#if defined(__AVR_ATmega2560__)
    rawRA = (pgm_read_byte_near(SObjectsstars_bin + index) << 8) | (pgm_read_byte_near(SObjectsstars_bin + index + 1));
    rawDec = (pgm_read_byte_near(SObjectsstars_bin + index + 2) << 8) | (pgm_read_byte_near(SObjectsstars_bin + index + 3));
    #else
    rawRA = (SObjectsstars_bin[index] << 8) | SObjectsstars_bin[index + 1];
    rawDec = (SObjectsstars_bin[index + 2] << 8) | SObjectsstars_bin[index + 3];
    #endif
	radiff = rawRA - targetRA;
	decdiff = rawDec - targetDec;
	comparediff = (radiff * radiff) + (decdiff * decdiff);
	if (comparediff < totaldiff) {
      //better match
	  tablenum = 1;
      objectnum = index / 5 + 1;
	  totaldiff = comparediff;
    }
  }
  // Check NGC table next
  for (index = 0; index < NGCNUM * 4; index += 4) {
    #if defined(__AVR_ATmega2560__)
    rawRA = (pgm_read_byte_near(Cngc_bin + index) << 8) | (pgm_read_byte_near(Cngc_bin + index + 1));
    rawDec = (pgm_read_byte_near(Cngc_bin + index + 2) << 8) | (pgm_read_byte_near(Cngc_bin + index + 3));
    #else
    rawRA = (Cngc_bin[index] << 8) | Cngc_bin[index + 1];
    rawDec = (Cngc_bin[index + 2] << 8) | Cngc_bin[index + 3];
    #endif
	radiff = rawRA - targetRA;
	decdiff = rawDec - targetDec;
	comparediff = (radiff * radiff) + (decdiff * decdiff);
	if (comparediff < totaldiff) {
      //better match
	  tablenum = 2;
      objectnum = index / 4 + 1;
	  totaldiff = comparediff;
    }
  }
  // Check IC table next
  for (index = 0; index < ICNUM * 4; index += 4) {
    #if defined(__AVR_ATmega2560__)
    rawRA = (pgm_read_byte_near(Ic_bin + index) << 8) | (pgm_read_byte_near(Ic_bin + index + 1));
    rawDec = (pgm_read_byte_near(Ic_bin + index + 2) << 8) | (pgm_read_byte_near(Ic_bin + index + 3));
    #else
    rawRA = (Ic_bin[index] << 8) | Ic_bin[index + 1];
    rawDec = (Ic_bin[index + 2] << 8) | Ic_bin[index + 3];
    #endif
	radiff = rawRA - targetRA;
	decdiff = rawDec - targetDec;
	comparediff = (radiff * radiff) + (decdiff * decdiff);
	if (comparediff < totaldiff) {
      //better match
	  tablenum = 3;
      objectnum = index / 4 + 1;
	  totaldiff = comparediff;
    }
  }
  // Check Other table next
  for (index = 0; index < 567 * 6; index += 6) {
    #if defined(__AVR_ATmega2560__)
    rawRA = (pgm_read_byte_near(Other_bin + index + 2) << 8) | (pgm_read_byte_near(Other_bin + index + 3));
    rawDec = (pgm_read_byte_near(Other_bin + index + 4) << 8) | (pgm_read_byte_near(Other_bin + index + 5));
    #else
    rawRA = (Other_bin[index + 2] << 8) | Other_bin[index + 3];
    rawDec = (Other_bin[index + 4] << 8) | Other_bin[index + 5];
    #endif
	radiff = rawRA - targetRA;
	decdiff = rawDec - targetDec;
	comparediff = (radiff * radiff) + (decdiff * decdiff);
	if (comparediff < totaldiff) {
      //better match
	  tablenum = 7;
	  #if defined(__AVR_ATmega2560__)
	  objectnum = (pgm_read_byte_near(Other_bin + index) << 8) | (pgm_read_byte_near(Other_bin + index + 1));
	  #else
      objectnum = (Other_bin[index] << 8) | Other_bin[index + 1];
      #endif
	  totaldiff = comparediff;
    }
  }
  // See if it could be Messier, Caldwell, or Hershel object
  if (tablenum != 1) {
    // No further checks if the identified object was a star
    altobjnum = objectnum;
    if (tablenum == 3) altobjnum += 10000; // IC number
    for (index = 0; index < (110 * 2); index +=2) {
      //Messier table check
	  #if defined(__AVR_ATmega2560__)
      tempobjnum = (pgm_read_byte_near(Msrch_bin + index) << 8) | (pgm_read_byte_near(Msrch_bin + index + 1));
      #else
      tempobjnum = (Msrch_bin[index] << 8) | Msrch_bin[index + 1];
      #endif
	  if (tempobjnum == altobjnum) {
        //Match Messier
	    alttablenum = 4;
        altobjnum = index / 2 + 1;
	  }
    }
    // Skip if we found a Messier table match
    if (alttablenum != 4) {
	  for (index = 220; index < (109 * 2 + 220); index +=2) {
        //Caldwell table check
		#if defined(__AVR_ATmega2560__)
        tempobjnum = (pgm_read_byte_near(Msrch_bin + index) << 8) | (pgm_read_byte_near(Msrch_bin + index + 1));
        #else
        tempobjnum = (Msrch_bin[index] << 8) | Msrch_bin[index + 1];
        #endif
	    if (tempobjnum == altobjnum) {
          //Match Caldwell
	      alttablenum = 5;
          altobjnum = index / 2 - 109;
	    }
      }
	  // Skip if we found a Caldwell table match
      if ((tablenum == 2) && (alttablenum != 5)) {
	    //Herchel table only applies to NGC objects
	    for (index = 2; index < (400 * 4); index +=4) {
          //Herschel table check
	      tempobjnum = (h400n_bin[index] << 8) | h400n_bin[index + 1];
		  #if defined(__AVR_ATmega2560__)
          tempobjnum = (pgm_read_byte_near(h400n_bin + index) << 8) | (pgm_read_byte_near(h400n_bin + index + 1));
          #else
          tempobjnum = (h400n_bin[index] << 8) | h400n_bin[index + 1];
          #endif
	      if (tempobjnum == altobjnum) {
            //Match Herschel
	        alttablenum = 6;
            altobjnum = (index - 2) / 4 + 1;
	      }
        }
      }
    }
  }
  return true;
}

int SiderealObjects::getIdentifiedObjectTable(void) {
  return tablenum;
}

int SiderealObjects::getIdentifiedObjectNumber(void) {
  return objectnum;
}

int SiderealObjects::getAltIdentifiedObjectTable(void) {
  return alttablenum;
}

int SiderealObjects::getAltIdentifiedObjectNumber(void) {
  return altobjnum;
}

double SiderealObjects::inRange24(double d) {
  while (d < 0.) {
	d += 24.;
  }
  while (d >= 24.) {
	d -= 24.;
  }
  return d;
}

double SiderealObjects::inRange360(double d) {
  while (d < 0.) {
	d += 360.;
  }
  while (d >= 360.) {
	d -= 360.;
  }
  return d;
}

double SiderealObjects::inRange2PI(double d) {
  while (d < 0.) {
	d += F2PI;
  }
  while (d >= F2PI) {
	d -= F2PI;
  }
  return d;
}

double SiderealObjects::deg2rad(double n) {
  return n * 1.745329252e-2;
}

double SiderealObjects::rad2deg(double n) {
  return n * 5.729577951e1;
}

