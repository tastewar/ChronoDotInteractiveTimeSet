#include <Wire.h>
#include <SPI.h>
#include "RTClib.h"               // https://github.com/adafruit/RTClib

RTC_DS1307 RTC;

const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data

boolean newData = false, TimeHasBeenSet=false;
void setup()
{
  Serial.begin(9600);
  initChronoDot();
}

void loop()
{
  if (TimeHasBeenSet)
  {
    PrintTime();
    delay(1000);
  }
  else
  {
    Serial.println("Let's set the time on the ChronoDot.");
    InteractiveTimeSet();
  }
}

void initChronoDot()
{
  // Instantiate the RTC
  Wire.begin();
  RTC.begin();
}

void InteractiveTimeSet()
{
  int z;
  Serial.setTimeout(120000);
  int y=PromptAndGetIntRange("Enter the year:",2000,2100);
  Serial.println(y);
  int mo=PromptAndGetIntRange("Enter the month:",1,12);
  Serial.println(mo);
  int d=PromptAndGetIntRange("Enter the day:",1,31);
  Serial.println(d);
  int h=PromptAndGetIntRange("Enter the hour (24 hour clock):",0,23);
  Serial.println(h);
  int m=PromptAndGetIntRange("Enter the minutes:",0,59);
  Serial.println(m);
  int s=PromptAndGetIntRange("Enter the seconds:",0,59);
  Serial.println(s);

  Serial.print("Press Y to set this time (N to abort): ");
  Serial.print(y);
  Serial.print('/');
  Serial.print(mo);
  Serial.print('/');
  Serial.print(d);
  Serial.print(' ');
  Serial.print(h);
  Serial.print(':');
  Serial.print(m);
  Serial.print(':');
  Serial.print(s);
  Serial.println();

  do
  {
    z=Serial.read();
  } while (z!='Y' && z!='y' && z!='N' && z!='n');
  if(z=='Y' || z=='y')
  {
    RTC.adjust(DateTime(y, mo, d, h, m, s));
    Serial.println("Done.");
    TimeHasBeenSet=true;
  }
  else Serial.println("Aborted.");
}

int PromptAndGetIntRange(char *pmt, int mn, int mx)
{
  int x;
  do
  {
    Serial.println(pmt);
    x=Serial.parseInt();
  } while (x<mn || x>mx);
  return x;
}

void recvWithEndMarker()
{
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void PrintTime()
{
  DateTime t=RTC.now();
  Serial.print(t.year());
  Serial.print('/');
  Serial.print(t.month());
  Serial.print('/');
  Serial.print(t.day());
  Serial.print(' ');
  Serial.print(t.hour());
  Serial.print(':');
  Serial.print(t.minute());
  Serial.print(':');
  Serial.print(t.second());
  Serial.println();
}
