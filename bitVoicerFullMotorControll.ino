#include <BitVoicer11.h>

//Sets up the ins and default variables
const int input1 = 2;
const int input2 = 4;
const int input3 = 7;
const int input4 = 8;
const int enable1 = 3;
const int enable2 = 9;
int rpm = 0;
String direc;

BitVoicerSerial bvSerial = BitVoicerSerial();

void setup()
{
  //Starts serial communication and sets up the inModes
  Serial.begin(9600);
  pinMode(input1, OUTPUT);
  pinMode(input2, OUTPUT);
  pinMode(input3, OUTPUT);
  pinMode(input4, OUTPUT);
  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);
  direc = "forward";
}

void loop()
{
  //Retrieves data from serial buffer 
  bvSerial.getData();
  
  //Quits the loop if no string data was returned from getData
  if (bvSerial.strData == "")
  {
    return;
  }
  else if (bvSerial.strData == "GO")
  {
    rpm = 170;
  }
  else if (bvSerial.strData == "MF")
  {
    direc = "forwards";
  }
  else if (bvSerial.strData == "MB")
  {
    direc = "backwards";
  }
  else if (bvSerial.strData == "DF")
  {
    if (rpm+10<=255){
      rpm = rpm + 10;
    }
    else
    {
      rpm = 255;
    }
  }
  else if (bvSerial.strData == "DS")
  {
    if (rpm-20>=100){
      rpm = rpm - 20;
    }
  }
  else if (bvSerial.strData == "ST")
  {
    rpm = 0;
  } 
  else if (bvSerial.strData == "TL")
  {
    digitalWrite(input3,HIGH);
    digitalWrite(input4,LOW);
  }
   else if (bvSerial.strData == "TR")
  {
    digitalWrite(input3,LOW);
    digitalWrite(input4,HIGH);
  }
    else if (bvSerial.strData == "GS")
  {
    digitalWrite(input3,LOW);
    digitalWrite(input4,LOW);
  }

  if (direc == "forwards"){
    digitalWrite(input1, HIGH);
    digitalWrite(input2, LOW);
  }
  else 
  {
    digitalWrite(input1, LOW);
    digitalWrite(input2, HIGH);
  }
  analogWrite(enable1, rpm);
  analogWrite(enable2, 200);
}
