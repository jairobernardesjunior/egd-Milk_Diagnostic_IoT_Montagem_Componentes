#include <SoftwareSerial.h>// Import software serial library to interface ESP8266 module
//#include <LiquidCrystal_I2C.h>// Import I2C LCD library to print Email status
//LiquidCrystal_I2C lcd(0x27, 16, 2); // run ic2_scanner sketch and get the IC2 address, which is 0x3f in my case, it could be 0x3f in many cases
#define RX 10 // Define PIN10 for Software Serial RX
#define TX 11 // Define PIN11 For Software Serial TX
String AP = "ixs";       // Set Yout WiFi Network SSID
String PASS = "delzirinha2016"; // Set Yout WiFi Network Password
String HOST = "smtp.gmail.com";
String PORT = "587";; // Define smtp port value
int countTrueCommand;
int countTimeCommand;
boolean found = false;
SoftwareSerial esp8266(RX, TX); // Enable Software Serial port
void setup() {
  Serial.begin(9600); // Initialize Arduino Serial monitor at baud rate 9600
  ////lcd.init(); // Initialize LCD dispaly
  esp8266.begin(115200); // Initialize ESP8266 Software serial at baudrate 115200

  //lcd.backlight();
  //lcd.clear();
  //lcd.print("  MICRODIGISOFT  ");

  delay(20);

  //lcd.clear();
  //lcd.print("  Tutorials  ");


  sendCommand("AT", 5, "OK"); // Set AT command the test the communication between Arduino and ESP8266
  sendCommand("AT+CWMODE=3", 5, "OK"); // Set the WIFI mode for ESP8266 module
  sendCommand("AT+CWQAP", 100, "OK"); // Disconnect for ESP8266
  sendCommand("AT+RST", 100, "OK"); //Restart the ESP8266 module

  //lcd.clear();
  //lcd.print("Connecting WiFi");

  delay(20);
  sendCommand("AT+CWJAP=""+ AP +""""");
  sendCommand("AT + CWJAP = \"" + AP + "\",\"" + PASS + "\"", 20, "OK");// Set SSID and Password

  //lcd.clear();
  //lcd.print("WiFi Connected");

  delay(20);
  sendCommand("AT+CIFSR", 50, "OK");
  delay(200);
}
void loop() {
  sendCommand("AT+CIPMUX=1", 5, "OK");
  sendCommand("AT+CIPSERVER=1,80", 20, "OK");
  delay(500);

  //lcd.print("Sending Email by");
  //lcd.setCursor(0, 1);
  //lcd.print(" Arduino & WIFI ");

  delay(2000);

  //lcd.clear();
  //lcd.print("Finding ESP8266");

  delay(2000);
  sendCommand("AT", 100, "OK");
  delay(20);

  //lcd.clear();
  //lcd.print("ESP-Connected");

  delay(500);

  //lcd.clear();
  //lcd.print("Configuring Email.."); // Configure the Email 

  sendCommand("AT", 100, "OK");
  sendCommand("AT+CIPSTART=4,\"TCP\",\"" + HOST + "\"," + PORT, 15, "OK");
  sendCommand("AT", 100, "OK");
  delay(2000);

  //lcd.clear();
  //lcd.print("Try To Login.....");

  sendCommand("AT+CIPSEND=4", 30, "OK");
  sendCommand("aTR4LmRhdGFAZ21haWwuY29t", 30, "OK"); //base64 code for username
  delay(20);
  sendCommand("AT+CIPSEND=4", 18, "OK");
  sendCommand("eHh4eDIwMjNA", 18, "OK"); ////base64 code for password

  //lcd.clear();
  //lcd.print("Login Success");

  sendCommand("AT+CIPSEND=4", 100, "OK");
  sendCommand("MAIL FROM:< i4x.data@gmail.com >", 100, "OK");
  sendCommand("AT+CIPSEND=4", 100, "OK");
  sendCommand("RCPT To:< jairobernardesjunior@gmail.com >", 100, "OK");
  sendCommand("AT+CIPSEND=4", 100, "OK");
  delay(2000);

  //lcd.clear();
  //lcd.print("Sending Email"); // Send Email
  //lcd.setCursor(0, 1);
  //lcd.print("microdigisoft");

  sendCommand("DATA", 100, "OK");
  sendCommand("AT+CIPSEND=4", 100, "OK");
  delay(2000);

  //lcd.clear();
  //lcd.print("Email Sent...");

  countTimeCommand++;
  sendCommand("AT+CIPCLOSE=0", 5, "OK");
}
void sendCommand(String command, int maxTime, char readReplay[]) {
  Serial.print(countTrueCommand);
  Serial.print(". at command => ");
  Serial.print(command);
  Serial.print(" ");

  while (countTimeCommand < (maxTime * 1))
  {
    esp8266.println(command);//at+cipsend
    if (esp8266.find(readReplay)) //ok
    {
      found = true;
      break;
    }

    countTimeCommand++;
  }

  if (found == true)
  {
    Serial.println("OK");
    countTrueCommand++;
    countTimeCommand = 0;
  }

  if (found == false)
  {
    Serial.println("Fail");
    countTrueCommand = 0;
    countTimeCommand = 0;
  }

  found = false;
}