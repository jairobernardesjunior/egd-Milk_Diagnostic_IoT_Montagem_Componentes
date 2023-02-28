/*
  -     CONECT E RECEBE DADOS DO GPS6MV2
  =================================================
  ==================================================
*/

//Connect with pin 18 and 19
#include <TinyGPS.h>

#define GPSSerial Serial1

//long   lat,lon; // create variable for latitude and longitude object
float lat,lon;
TinyGPS gps; // create gps object

void setup(){
Serial.begin(9600); // connect serial
Serial.println("The GPS Received Signal:");
Serial1.begin(9600); // connect gps sensor

}
 
void loop(){

/*
   if (Serial.available()) {  //////// p1
    char c = Serial.read();
    GPSSerial.write(c);
  }
  if (GPSSerial.available()) {
    char c = GPSSerial.read();
    Serial.write(c);
  }
*/

  
    while(Serial1.available()){ // check for gps data   p2
    if(gps.encode(Serial1.read()))// encode gps data
    { 
    gps.f_get_position(&lat,&lon); // get latitude and longitude

    Serial.print("Position: ");
    
    //Latitude
    Serial.print("Latitude: ");
    Serial.print(lat,6);
    
    Serial.print(",");
    
    //Longitude
    Serial.print("Longitude: ");
    Serial.println(lon,6); 
    
   }
  }  
}