#include <SoftwareSerial.h>

SoftwareSerial serialGSM(9, 8); // RX, TX

bool temSMS = false;
String telefoneSMS;
String dataHoraSMS;
String mensagemSMS;
String comandoGSM = "";
String ultimoGSM = "";

const int buttonPin = 2;
int buttonState = 0;
int LED1 = 3; 
#define ligaLed "LED1 ON"
#define desligaLed "LED1 OFF"
#define numeroComando "+55XXXXXXXXXXX" //numero para validacao e inicio dos comandos.

void leGSM();
void enviaSMS(String telefone, String mensagem);
void configuraGSM();

void setup() {

  Serial.begin(9600);
  serialGSM.begin(9600); 

  pinMode(buttonPin, INPUT);

  pinMode(LED1, OUTPUT);

  Serial.println("Sketch Iniciado!");
  configuraGSM();
}

void loop() {
  buttonState = digitalRead(buttonPin);
  
  leGSM();  

  if (comandoGSM != "") {
      Serial.println(comandoGSM);
      ultimoGSM = comandoGSM;
      comandoGSM = "";
  }

  if (temSMS) {

     Serial.println("Chegou Mensagem!!");
     Serial.println();
    
     Serial.print("Remetente: ");  
     Serial.println(telefoneSMS);
     Serial.println();
    
     Serial.print("Data/Hora: ");  
     Serial.println(dataHoraSMS);
     Serial.println();
    
     Serial.println("Mensagem:");  
     Serial.println(mensagemSMS);
     Serial.println();
      
     mensagemSMS.trim();
     if(telefoneSMS == numeroComando){ 
         if (mensagemSMS == ligaLed) {
            Serial.println("Ligando LED1");
            digitalWrite(LED1, HIGH);
            enviaSMS(telefoneSMS, "LED ligado!");
         }
    
         if (mensagemSMS == desligaLed) {
            Serial.println("Desligando LED1");
            digitalWrite(LED1, LOW);
            enviaSMS(telefoneSMS, "LED desligado!");
         }
     }

     temSMS = false;
  }

   if (buttonState == HIGH) {
   Serial.println("Botao acionado");
   enviaSMS(numeroComando, "Botao acionado");
   delay(1000);
   }
}

void leGSM()
{
  static String textoRec = "";
  static unsigned long delay1 = 0;
  static int count=0;  
  static unsigned char buffer[64];

  if (serialGSM.available()) {            
 
     while(serialGSM.available()) {         
   
        buffer[count++] = serialGSM.read();     
        if(count == 64)break;
     }

     textoRec += (char*)buffer;
     delay1   = millis();
     
     for (int i=0; i<count; i++) {
         buffer[i]=NULL;
     } 
     count = 0;                       
  }


  if ( ((millis() - delay1) > 100) && textoRec != "" ) {

     if ( textoRec.substring(2,7) == "+CMT:" ) {
        temSMS = true;
     }

     if (temSMS) {
            
        telefoneSMS = "";
        dataHoraSMS = "";
        mensagemSMS = "";

        byte linha = 0;  
        byte aspas = 0;
        for (int nL=1; nL < textoRec.length(); nL++) {

            if (textoRec.charAt(nL) == '"') {
               aspas++;
               continue;
            }                        
          
            if ( (linha == 1) && (aspas == 1) ) {
               telefoneSMS += textoRec.charAt(nL);
            }

            if ( (linha == 1) && (aspas == 5) ) {
               dataHoraSMS += textoRec.charAt(nL);
            }

            if ( linha == 2 ) {
               mensagemSMS += textoRec.charAt(nL);
            }

            if (textoRec.substring(nL - 1, nL + 1) == "\r\n") {
               linha++;
            }
        }
     } else {
       comandoGSM = textoRec;
     }
     
     textoRec = "";  
  }     
}

void enviaSMS(String telefone, String mensagem) {
  serialGSM.print("AT+CMGS=\"" + telefone + "\"\n");
  serialGSM.print(mensagem + "\n");
  serialGSM.print((char)26); 
}

void configuraGSM() {
   serialGSM.print("AT+CMGF=1\n;AT+CNMI=2,2,0,0,0\n;ATX4\n;AT+COLP=1\n"); 
}
