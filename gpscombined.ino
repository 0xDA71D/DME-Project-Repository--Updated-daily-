#include <SoftwareSerial.h>
#define txPin 8      //tx pin in GPS connection
#define rxPin 9      //rx pin in GPS connection

SoftwareSerial gps = SoftwareSerial(rxPin, txPin);
///// ^GPS vXbee

//GPS  vars ---------------------
byte byteGPS = 0;  
int i = 0;
int state = 0;
char dataGPG[100]="";
char *pch;
char *GGA[15];
int sat = 0;


float myLatVal = 0, myLonVal = 0;

char* GPSPacketByteValue;
//GPS  vars ---------------------



void setup(){
  Serial.begin(9600);
  Serial.flush(); 
  gps.begin(4800); //setup for GPS Serial Port  
  gps.flush();
  //xbee.begin(9600);
  //xbee.end();
  pinMode(13, OUTPUT); //setup satellites signal
  digitalWrite(13, LOW);     // Turn off the led until a satellite signal
<<<<<<< HEAD:gpscombined.ino
<<<<<<< HEAD:gpscombined.ino
  
}
=======
}

>>>>>>> parent of d1ca6ee... today:gpscombined/gpscombined.ino
=======
}

>>>>>>> parent of d1ca6ee... today:gpscombined/gpscombined.ino
void loop(){
  delay(1000);
  if(getGPS(30000)){
    Serial.print(myLatVal);
    Serial.print("...");
    Serial.print(myLonVal);
    Serial.print("\n");

  }else{
    Serial.print("Hmm.. Not quite there \n");
  }
<<<<<<< HEAD:gpscombined.ino
<<<<<<< HEAD:gpscombined.ino
 /* if((boolean)myLatVal * myLonVal){ // if (Latitude != 0.0f && Longitude != 0.0f) 
    newPacket.Latitude = myLatVal;
    newPacket.Longitude = myLonVal;
    newPacket.magicNumber = 0x7E57; 
    
    //Malloc
    GPSPacketByteValue = (char*) malloc(sizeof(newPacket));
    memcpy(GPSPacketByteValue, &newPacket, sizeof(newPacket));
    Serial.print(GPSPacketByteValue);

  }*/
=======
>>>>>>> parent of d1ca6ee... today:gpscombined/gpscombined.ino
=======
>>>>>>> parent of d1ca6ee... today:gpscombined/gpscombined.ino
}
boolean getGPS(int timeOutTime){
  float timeMillis = millis();
  gps.flush();
  Serial.flush();

  // Prepare all for reading GPS Serial Port
  memset(dataGPG, 0, sizeof(dataGPG));    // Remove previous readings
  byteGPS = 0;                            // Remove data
  byteGPS = gps.read();                   // Read the byte that is in the GPS serial port
  delay(1000);

  // Find the desired string
  while(byteGPS != '$')
  {
    byteGPS = gps.read();
    if((int) (millis()-timeMillis) >= timeOutTime){
      return false;
      
    }
  } 

  i=1;
  dataGPG[0] = '$';

  while(byteGPS != '*' )
  {
    byteGPS = gps.read();
    dataGPG[i]=byteGPS; 
    i++; 
  }

  dataGPG[i]= '\0';
  // Call to the function that manipulates our string
  Serial.print("\n");
  i=0;
  memset(GGA, 0, sizeof(GGA));          // Remove previous readings

  pch = strtok (dataGPG,",");

  if (strcmp(pch,"$GPGGA")==0)
  {  
    while (pch != NULL)
    {
      pch = strtok (NULL, ",");
      GGA[i]=pch;    
      i++;
    }
  }else{
    return false;
  }
  //Serial.println(GGA[3]);
  //Serial.println(GGA[3]);
  //Serial.println(GGA[4]);
  float rawLat = parseDegree(GGA[1]);
  float rawLon = parseDegree(GGA[3]);
  if(rawLat * rawLon == 0){
  return false;
  }
  if(*GGA[2] == 'N'){
    myLatVal = rawLat;
  }else{
    myLatVal = -1 * rawLat;
  }
    if(*GGA[4] == 'E'){
    myLonVal = rawLon;
  }else{
    myLonVal = -1 * rawLon;
  }
  printFloat(myLatVal);
  printFloat(myLonVal);
}


float parseDegree(char* inputString){
  int firstNum, secondNum,degree;
  float minute;
  firstNum = atoi(strtok (inputString, "."));
  secondNum = atoi (strtok (NULL, "."));
  //Serial.print(firstNum);
  //Serial.print (" | ");    For debug use
  //Serial.print(secondNum);
  //Serial.print("\n");
  degree = floor(firstNum/ 100);
  //Serial.println(degree);
  minute = firstNum - 100*degree;
  //Serial.println(minute);
  minute = (float)(minute+ secondNum*.0001);
  //Serial.println(minute);
  return degree + (minute*0.0166666667);
}
void printFloat ( float numToPrint){
  char addChar;
  if(numToPrint < 0){
    addChar = '-';
  }else{
    addChar = NULL;
  }
  numToPrint = abs(numToPrint);
  Serial.print(addChar);
  Serial.print((int)floor(numToPrint));
  Serial.print(".");
  int bigDecimal = 10000 * (numToPrint - floor(numToPrint));
  Serial.println (bigDecimal);
}

/* Obsolete
 void string()
 {
 i=0;
 memset(GGA, 0, sizeof(GGA));          // Remove previous readings
 
 pch = strtok (dataGPG,",");
 
 if (strcmp(pch,"$GPGGA")==0)
 {
 while (pch != NULL)
 {
 pch = strtok (NULL, ",");
 GGA[i]=pch;    
 i++;
 } 
 
 for(int i = 0; i < 15; ++i){
 Serial.println(GGA[i]);
 }
 Serial.println("---------------");
 }
 }*/



