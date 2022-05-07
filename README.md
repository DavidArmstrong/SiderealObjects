# SiderealObjects


Sidereal Objects - A strangely named Arduino Library for providing low precision Epoch 2000.0 Astronomical object coordinates.

  Version 1.1.1 - May 7, 2022

  By David Armstrong
  https://github.com/DavidArmstrong/SiderealObjects
  See MIT LICENSE.md file


This library provides a core set of low precision astronomy related tables, and functions to read them. (Accuracy is within +-1 arc minute, or better.)

It is recommended that the user run the example sketches in turn on the target Arduino board, as they show how to use the library functions together to achieve some desired result.

Notes:
  1) The library recommends support for double float numbers.  There are currently a number of boards that support true double type numbers, and use the Arduino IDE.  (i.e. The Sparkfun Redboard Turbo was used as the test platform in development.)  However the original UNO board, and similar derivitives, handle double numbers by mapping them to regular float types, and so these boards have a lower calculation accuracy.
  2) It's not just accuracy that is of concern here. The older Uno boards just don't have enough Flash memory to store all the table data.  On my test system, a simple sketch consumes over 80K of Flash.
  3) The library reduces memory usage by storing each coordinate as 2 integers.  This does introduce some inaccouracy in the coordinates.  Yet its accuracy is more than sufficient for amateur astronomy use.
  4) While there may be better ways to implement some of the functionality of this library, the design makes it easier to verify the outputs, and easier to use.
  5) The library name was chosen to be different from any other astronomy type library that may be out there.  Library name uniqueness is important in Arduino sketches.  (That means that there isn't a function called Sidereal Objects here!)
  6) This library was designed to be used with the SiderealPlanets library, which provides support for most of the mathematical functionality that may be needed in a target system.  (See https://github.com/DavidArmstrong/SiderealPlanets/ )
  7) Files located in the "extra/" directory are text files regarding the objects that are in the tables of this library.

======================================

Basic Library Functions:<br>
-- If a function returns a boolean value of false, it generally means something was wrong with the input given to the function.  Specifics are explained with each function.

boolean begin()<br>
  This initializes the library.

double decimalDegrees(int degrees, int minutes, float seconds)<br>
  Convert a number that is specified in degrees, minutes, and seconds to decimal degrees.  Note that this function will also handle hours as well as degrees.

void printDegMinSecs(double n)<br>
  Prints a double number of degrees to Serial in the form {deg}:{min}:{seconds}. The seconds may include a fractional part of two digits. If needed, a minus sign is printed in front of the number.  This will also work to print hours.  The numbers printed are not further formatted in any way.

boolean setRAdec(double RightAscension, double Declination)<br>
  Sets the Right Ascension and Declination for a sky position that will be used by the library.  This must be called before IdentifyObject(). Right Ascension is in hours, with valid values from 0 to less than 24.  Declination is in degrees, and can range from -90. to +90.
  
double getRAdec()<br>
  Returns a double number of the selected object Right Ascension in hours.

double getDeclinationDec()<br>
  Returns a double number of the selected object Declination in degrees.

float getStarMagnitude()>br>
  Returns magnitude for selected star.

boolean selectStarTable(int n)<br>
  Selects the star table, which includes stars of magnitude 4.0 and brighter.  Valid star number values are between 1 and 609, inclusive.

boolean selectNGCTable(int n)<br>
  Selects the NGC table.  Valid object numbers are between 1 and 7840, inclusive.

boolean selectICTable(int n)<br>
  Selects the IC table.  Valid object numbers are between 1 and 5386, inclusive.

boolean selectMessierTable(int n)<br>
  Selects the Messier table.  Valid object numbers are between 1 and 110, inclusive.

boolean selectCaldwellTable(int n)<br>
  Selects the Caldwell table.  Valid object numbers are between 1 and 109, inclusive.

boolean selectHershel400Table(int n)<br>
  Selects the Hershel 400 table.  Valid object numbers are between 1 and 400, inclusive. Notes: There has been a discrepancy for one object listing between what was published in a manual listing this table, and what was published to a website.  The table here uses the printed version for its contents.

boolean selectOtherObjectsTable(int n)<br>
  Selects the Other Objects table.  Valid object numbers are listed in the Other Objects table.  Any number given that is not in that table will be considered invalid, and returns a false flag.

boolean identifyObject()<br>
  Runs algorithm to find object that is closest to the Right Ascension and Declination coordinates entered via setRAdec().  The best match object parameters are returned in the following functions:
  
int getIdentifiedObjectTable()<br>
  Returns a number corresponding to the table that has the closest object match.  Numbers are as follows:
  
  * 1 - Star
  * 5 - NGC
  * 6 - IC
  * 7 - Other Objects

int getIdentifiedObjectNumber()<br>
  Returns the number in the table for the closest object match.

char\* printStarName(int n)<br>
  If an identified object is a star (table type is '1'), then this function can be called to see if there is a predefined name to go with that star that can be output.  The table only has the most commonly known 81 star names included, but can easily be extended to include any of the other stars in the library's star table.  (See the extras/ folder file Stars.txt)  Refer to the example sketch Example3_Identify.ino to see how this function may be used.

int getAltIdentifiedObjectTable()<br>
  Returns a number corresponding to an alternate table that has the same closest object match.  If no alternate entry was found, a '0' is returned.  This allows the function to also be used as a flag for an if() statement.  Numbers returned are as follows:
  
  * 0 - No alternate object match found
  * 2 - Messier
  * 3 - Caldwell
  * 4 - Hershel 400

int getAltIdentifiedObjectNumber()<br>
  Returns the number in the alternate table for the closest object match.
