
#include <SD.h>
#include <SPI.h>
#include "Wire.h"
#include "Adafruit_BMP085.h" 
#include <virtuabotixRTC.h>                        
    
int CLK_PIN = 6;                                     
int DAT_PIN = 7;                                      
int RST_PIN = 8;                                       

virtuabotixRTC myRTC(CLK_PIN, DAT_PIN, RST_PIN);  
Adafruit_BMP085 mySensor; 

int CS_PIN = 10;
float Celsius;
float pressure;
float altitude; 
char buf[80];
char dosyad[20];
String s="";
String ds;
File file;

int i=0;
int j=0;

void setup()
{
  mySensor.begin();
  pinMode(2,INPUT);
  Serial.begin(9600);

  initializeSD();
  
  while(true){
    ds="";
    ds+=i;
    ds+=".txt";
    ds.toCharArray(dosyad, 80);
    
    createFile(dosyad);
        
          while(j<15){
             myRTC.updateTime(); 
            Celsius = mySensor.readTemperature();
            //pascal cinsinden
            pressure=mySensor.readPressure();
            altitude=mySensor.readAltitude();
            
            s="";
           
            s+=Celsius;
            s+=",";
            s+=pressure;
            s+=",";
            s+=altitude;
            s+=",";
            s+=myRTC.hours;
            s+=":";
            s+=myRTC.minutes;
            s+=":";
            s+=myRTC.seconds;
            
            s.toCharArray(buf, 80);
            writeToFile(buf);
            j++;
          }          
  i++;
  j=0;
  
  closeFile();
  }
  
}


void loop(){  
}

void initializeSD()
{
  Serial.println("Initializing SD card...");
  pinMode(CS_PIN, OUTPUT);

  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
}

int createFile(char filename[])
{
  file = SD.open(filename, FILE_WRITE);

  if (file)
  {
    Serial.println("File created successfully.");
    return 1;
  } else
  {
    Serial.println("Error while creating file.");
    return 0;
  }
}

int writeToFile(char text[])
{
  if (file)
  {
    file.println(text);
    Serial.println("Writing to file: ");
    Serial.println(text);
    return 1;
  } else
  {
    Serial.println("Couldn't write to file");
    return 0;
  }
}

void closeFile()
{
  if (file)
  {
    file.close();
    Serial.println("File closed");
  }
}



