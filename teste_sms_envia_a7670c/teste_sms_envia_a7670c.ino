#include <SoftwareSerial.h>

SoftwareSerial SIM7670Serial(3, 4); // RX, TX

void setup() {
  Serial.begin(9600);
  SIM7670Serial.begin(9600);

  Serial.println("setup");

  sendATCommand("AT", "OK", 1000); // check communication
  sendATCommand("AT+CMGF=1", "OK", 1000); // set SMS format to text
}

void loop() {
  sendSMS("+5534999700463", "Hello from Arduino!");           
  delay(30000);
}

void sendSMS(String number, String message) {

  Serial.println(number);
  Serial.println(message);

  String cmd = "AT+CMGS=\"" + number + "\"\r\n";
  SIM7670Serial.print(cmd);
  delay(100);
  SIM7670Serial.println(message);
  delay(100);
  SIM7670Serial.write(0x1A); // send ctrl-z
  delay(100);
}

void sendATCommand(String cmd, String expectedResponse, int timeout) {
  SIM7670Serial.println(cmd);
  String response = "";
  long timeStart = millis();
  while (millis() - timeStart < timeout) {
    while (SIM7670Serial.available() > 0) {
      char c = SIM7670Serial.read();
      response += c;
    }
    if (response.indexOf(expectedResponse) != -1) {
      break;
    }
  }
  Serial.println(response);
}
