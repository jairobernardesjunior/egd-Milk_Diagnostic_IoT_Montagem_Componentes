#include<LiquidCrystal.h>

LiquidCrystal lcd(14,15,16,17,18,19);


#include <SoftwareSerial.h>

SoftwareSerial Serial1(2, 3); // RX, TX


boolean No_IP=false;

String IP="";


void check4IP(int t1)

{

  int t2=millis();

  Serial1.flush();

  while(t2+t1>millis())

  {

    while(Serial1.available()>0)

    {

      if(Serial1.find("WIFI GOT IP"))

      {

        No_IP=true;

      }

    }

  }

}


void get_ip()

{

  IP="";

  char ch=0;

  while(1)

  {

    Serial1.println("AT+CIFSR");

    while(Serial1.available()>0)

    {

      if(Serial1.find("STAIP,"))

      {

        delay(1000);

        Serial.print("IP Address:");

        while(Serial1.available()>0)

        {

          ch=Serial1.read();

          if(ch=='+')

          break;

          IP+=ch;

        }

      }

      if(ch=='+')

      break;

    }

    if(ch=='+')

    break;

    delay(1000);

  }

  Serial.print(IP);

  Serial.print("Port:");

  Serial.println(80);

}


void connect_wifi(String cmd, int t)

{

  int temp=0,i=0;

  while(1)

  {

    Serial1.println(cmd); 

    while(Serial1.available())

    {

      if(Serial1.find("OK"))

      i=8;

    }

    delay(t);

    if(i>5)

    break;

    i++;

  }

  if(i==8)

  Serial.println("OK");

  else

  Serial.println("Error");

}



void setup()

{

  Serial1.begin(9600);

    // Serial.begin(9600);

     lcd.begin(16,2);

     lcd.print("Sending Email by");

     lcd.setCursor(0,1);

     lcd.print(" Arduino & WIFI ");

     delay(2000);

     lcd.clear();

     lcd.print("  Circuit Digest  ");

     delay(2000);

     lcd.clear();

     lcd.print("Finding ESP8266");

     connect_wifi("AT",100);

     connect_wifi("ATE1",100);

     lcd.clear();

     lcd.print("Connected");

     delay(1000);

     connect_wifi("AT+CWMODE=3",100);

     connect_wifi("AT+CWQAP",100);  

     connect_wifi("AT+RST",5000);

     lcd.clear();

     lcd.print("Connecting WiFi");

     check4IP(5000);

     if(!No_IP)

     {

        Serial.println("Connecting Wifi....");

        connect_wifi("AT+CWJAP=\"ixs\",\"delzirinha2016\"",7000);    //provide your WiFi username and password here

      }

      else

        {

        }

      lcd.clear();

      lcd.print("WIFI Connected...");

      Serial.println("Wifi Connected");

      delay(1000);

      lcd.clear();

      lcd.print("Getting IP Add.");

      Serial.println("Getting IP Address....");

      get_ip();

      delay(1000);

      lcd.clear();

      lcd.print("IP:");

      lcd.print(IP);

      lcd.setCursor(0,1);

      lcd.print("PORT: 80");

      connect_wifi("AT+CIPMUX=1",100);

      connect_wifi("AT+CIPSERVER=1,80",100);

      delay(2000);

      lcd.clear();

      lcd.print("Configuring Email..");

  Serial1.println("AT+CIPSTART=4,\"TCP\",\"smtp.gmail.com\",465");

  delay(2000);

  Serial1.println("AT+CIPSEND=4,20");

  delay(2000);

  Serial1.println("EHLO 192.168.100.123");

  delay(2000);

  Serial1.println("AT+CIPSEND=4,12");

  delay(2000);

  lcd.clear();

  lcd.print("Try To Login.....");

  Serial1.println("AUTH LOGIN");

  delay(2000);

  Serial1.println("AT+CIPSEND=4,30");

  delay(2000);

  Serial1.println("aTR4LmRhdGFAZ21haWwuY29t=");     //base64 encoded username

  delay(2000);

  Serial1.println("AT+CIPSEND=4,18");

  delay(2000);

  Serial1.println("eHh4eDIwMjNA=");                    //base64 encoded password

  lcd.clear();

  lcd.print("Login Success");

  delay(2000);

  Serial1.println("AT+CIPSEND=4,34");

  delay(2000);

  Serial1.println("MAIL FROM:<ixs.datta@ gmail.com>");  // use your email address

  delay(2000);  

  Serial1.println("AT+CIPSEND=4,32");

  delay(2000);

  lcd.clear();

  lcd.print("Seniding Email 2");

  lcd.setCursor(0,1);

  lcd.print("jairobernardesjunior@gmail");

  Serial1.println("RCPT To:<jairobernardesjunior@gmail.com>");

  delay(2000);

  Serial1.println("AT+CIPSEND=4,6");

  delay(2000);

  Serial1.println("DATA");

  delay(2000);

  Serial1.println("AT+CIPSEND=4,24");

  delay(2000);

  Serial1.println("Testing Success");

  delay(2000);

  Serial1.println("AT+CIPSEND=4,3");

  delay(2000);

  Serial1.println('.');

  delay(10000);

  Serial1.println("AT+CIPSEND=4,6");

  delay(2000);

  Serial1.println("QUIT");

  delay(2000);

  lcd.clear();

  lcd.print("Email Sent...");

}


void loop()

{

   

}