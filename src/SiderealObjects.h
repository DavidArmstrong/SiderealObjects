/******************************************************************************
SiderealObjects.h
Sidereal Objects Arduino Library Header File
David Armstrong
Version 1.0.0 - August 4, 2021
https://github.com/DavidArmstrong/SiderealObjects

This file prototypes the SiderealObjects class, as implemented in SiderealObjects.cpp

Resources:
Uses math.h for math functions

Development environment specifics:
Arduino IDE 1.8.15

This code is released under the [MIT License](http://opensource.org/licenses/MIT)
Please review the LICENSE.md file included with this example.
Distributed as-is; no warranty is given.

******************************************************************************/

// ensure this library description is only included once
#ifndef __SiderealObjects_h
#define __SiderealObjects_h

//Uncomment the following line for debugging output
//#define debug_sidereal_objects

#include <stdint.h>
//#include <math.h>
#include "SiderealObjectsTables.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

// Structure to hold data
// We need to populate this when we calculate data
struct SiderealObjectsData {
  public:
    double RightAscension;
    double Declination;
    int tableNumber;
	int objectNumber;
};

// Sidereal_Planets library description
class SiderealObjects {
  // user-accessible "public" interface
  public:
    SiderealObjectsData spData;
    boolean begin(void);
	double decimalDegrees(int degrees, int minutes, float seconds);
	void printDegMinSecs(double n);
	boolean setRAdec(double RightAscension, double Declination);
	double getRAdec(void);
    double getDeclinationDec(void);
	float getStarMagnitude(void);
	boolean selectStarTable(int n);
	char* printStarName(int n);
	boolean selectNGCTable(int n);
	boolean selectICTable(int n);
    boolean selectMessierTable(int n);
    boolean selectCaldwellTable(int n);
	boolean selectHershel400Table(int n);
	boolean selectOtherObjectsTable(int n);
	boolean identifyObject(void);
	int getIdentifiedObjectTable(void);
	int getIdentifiedObjectNumber(void);
	int getAltIdentifiedObjectTable(void);
	int getAltIdentifiedObjectNumber(void);
	
  // library-accessible "private" interface
  private:
    const double F2PI = 2.0 * M_PI;
    const double FPI  = M_PI;
    const double FPIdiv2 = M_PI_2;
    const double FminusPIdiv2 = -M_PI_2;
    const double FPIdiv4 = M_PI_4;
	// 2PI/24HR is really 2PI/seconds-in-a-24-hour-day
    const double F2PIdiv24HR = 7.272205217E-5;
    const double F24HRdiv2PI = 13750.9871;
    // 2PI/360 is really 2PI/seconds-in-360-degrees
    const double F2PIdiv360 = 4.8481368111E-6;
    const double F360div2PI = 206264.8062471;
    const double F2to16 = 65536.0;
    // #define F2to16minus1   65535.0
    const double F2to15 = 32768.0;
    const double F2to15minus1 = 32767.0;
	const int NSTARS = 609; // Number of stars in table
    const int NGCNUM = 7840; // Number of NGC objects
    const int ICNUM = 5386; // Number of IC objects

	double RAdec, DeclinationDec;
	double RArad, DeclinationRad;
	double sinRA, sinDec;
	double cosRA, cosDec;
	float magnitude;

	double inRange24(double d);
	double inRange360(double d);
	double inRange2PI(double d);
	double deg2rad(double n);
	double rad2deg(double n);

    int tablenum, alttablenum, objectnum, altobjnum;
	
    union FourByte {
      unsigned long bit32;
      unsigned int bit16[2];
      unsigned char bit8[4];
    };
};
#endif
